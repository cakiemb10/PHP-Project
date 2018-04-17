<?php
/*========================================================*/
// ファイル名：search_reachable.cgi
// 処理名：到達件ポリゴン作成CGI（自動車ルート）
//
// 更新履歴
// 2014/01/28 H.Osamoto		新規作成
// 2014/10/09 H.Osamoto		ルート距離算出時に有料道路を利用しないよう変更
/*========================================================*/

	// エラー出力を明示的にOFF
	error_reporting(0);
	//error_reporting(E_ALL ^ E_NOTICE);

	/*==============================================*/
	// ライブラリ
	/*==============================================*/
	include('d_serv_emap.inc');
	include('ZdcCommonFuncAPI.inc');	// 共通関数
	
	// geosライブラリ
	if (!extension_loaded('geos')) {
		if (!dl('geos.so')) {
			echo "system error";
			exit;
		}
	}

	/*==============================================*/
	// 定義情報
	/*==============================================*/
	// 基準点
	$base_lat = 128380190;
	$base_lon = 503147440;
	
	// 基準点での1kmの緯度経度差
	$base_lat_dist = 32365;
	$base_lon_dist = 39835;
	$base_lat_dist_m = $base_lat_dist/1000;
	$base_lon_dist_m = $base_lon_dist/1000;
	
	// 経度から緯度変換係数
	$lon2lat = $base_lat_dist / $base_lon_dist;
	
	// 分割文字
	$delimiter = ";";
	
	/*==============================================*/
	// ファンクション
	/*==============================================*/
	// 緯度経度に角度付与
	function point_rotate($r, $angle){
		$angle = deg2rad($angle);
		$x = round($r * cos($angle));
		$y = round($r * sin($angle));
		return array($x, $y);
	}
	
	// 緯度経度から距離を算出
	function getDistFromLatLon($p_latM, $p_lonM, $p_latS, $p_lonS, $p_latE, $p_lonE){
		$tmp_lat = abs($p_latS - $p_latE);
		$tmp_lon = abs($p_lonS - $p_lonE);
		
		$dist_lat_m = $tmp_lat / $p_latM;
		$dist_lon_m = $tmp_lon / $p_lonM;
		
		$ret = sqrt(pow($dist_lat_m, 2) + pow($dist_lon_m, 2));
		
		return $ret;
	}
	
	// 凸包生成
	function getConvexHull($p_poly_str, $p_delimiter=",") {
		$reader = new GEOSWKTReader();
		$writer = new GEOSWKTWriter();
		$writer->setRoundingPrecision(0);

		$g = $reader->read('POLYGON(('.$p_poly_str.'))');
		$retConvexHull = $g->convexHull();
		$retConvexHull_str = $writer->write($retConvexHull);

		// 不要文字列除去
		$retConvexHull_str = str_replace('))', '', str_replace('POLYGON ((', '', $retConvexHull_str));
		$retConvexHull_str = str_replace(')', '', str_replace('LINESTRING (', '', $retConvexHull_str));

		$tmp_arr = explode(",", $retConvexHull_str);

		foreach($tmp_arr as $tmp_point){
			$tmp_latlon = explode(" ", trim($tmp_point));
			
			$ret_arr[] = $tmp_latlon[0].$p_delimiter.$tmp_latlon[1];
		}
		return $ret_arr;
	}
	
	// 内外判定
	function checkContains($p_poly_str, $p_check_lat, $p_check_lon) {
		$reader = new GEOSWKTReader();
		$writer = new GEOSWKTWriter();
		$writer->setRoundingPrecision(0);
		
		$g1 = $reader->read('POLYGON(('.$p_poly_str.'))');
		$g2 = $reader->read('POINT('.$p_check_lon.' '.$p_check_lat.')');
		
		// 判定
		$retAssert = $g1->contains($g2);
		
		if ($retAssert == "") {
			return false;
		} else {
			return true;
		}
	}

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$LAT   = $_GET['lat'];
	$LON   = $_GET['lon'];
	$DIST  = $_GET['dist'];
	$PART  = $_GET['part'];
	$LVL  = $_GET['lvl'];
	if (isset($_GET['datum']) && strlen($_GET['datum'])>0) {
		$DATUM = $_GET['datum'];
	} else {
		$DATUM = DEF_PRM_DATUM_TOKYO;
	}

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	// 緯度
	if (!$LAT) {
		echo "parameter error LAT[$LAT]";
		exit;
	}
	// 経度
	if (!$LON) {
		echo "parameter error LON[$LON]";
		exit;
	}
	// 検索範囲
	if (!$DIST) {
		echo "parameter error DIST[$DIST]";
		exit;
	}
	// 頂点数
	if (!$PART) {
		echo "parameter error PART[$PART]";
		exit;
	}
	// 表示縮尺
	if (!$LVL) {
		$LVL = 9;
	}
	/* 測地系 */
	if ($DATUM != DEF_PRM_DATUM_TOKYO && $DATUM != DEF_PRM_DATUM_WGS84) {
		echo "parameter error DATUM[$DATUM]";
		exit;
	}

	// 緯度経度変換
	$res = cnv_ll2lldms($LAT, $LON, $DATUM, $LAT_MS, $LON_MS);
	if (!$res) {
		// 緯度経度不正
		echo "parameter error LAT[$LAT] LON[$LON]";
		exit;
	}

	// 分割ピッチ
	$dist_pitch = $DIST / 10;

	/*==============================================*/
	// メイン処理
	/*==============================================*/
	for ($k = $DIST; $k > 0; $k-=$dist_pitch) {
		
		// 距離(緯度経度換算での真東)
		$r = $base_lon_dist * ($k / 1000);
		
		// 頂点間の角度
		$angle_base = 360 / $PART;
		
		for($i = 0; $i < $PART; $i++) {
			$angle = $angle_base * $i;
			// 角度分移動した際の座標
			list($x, $y) = point_rotate($r, $angle);
			
			// 緯度経度の比率を考慮して目標の緯度経度を算出
			$LAT_MS_D = round($LAT_MS - ($y * $lon2lat));
			$LON_MS_D = round($LON_MS + $x);
			
			// 2週目以降に処理を省略するかチェック
			if ($k < $DIST) {
				// チェック用geosポリゴン文字列
				$check_poly_str = implode(", ", $dest_point);
				$check_poly_str .= ", ".$dest_point[0];
			
				// チェック用ポリゴンの凸包生成
				$checkConvexHull_arr = getConvexHull($check_poly_str, " ");
				
				// ポリゴンとして成立している場合、検索位置の内外判定
				if (count($checkConvexHull_arr) > 2) {
					$check_poly_str = implode(", ", $checkConvexHull_arr);
					if(checkContains($check_poly_str, $LAT_MS_D, $LON_MS_D)) {
						// 現時点までのポリゴンに内包される場合は省略する
						continue;
					}
				}
			}
			
			// ルート検索
			//	$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $LAT_MS, $LON_MS, $LAT_MS_D, $LON_MS_D);	mod 2014/10/09 H.Osamoto
			$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s&chg=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $LAT_MS, $LON_MS, $LAT_MS_D, $LON_MS_D, 0);
			$xml = file_get_contents($url);
			$dat = simplexml_load_string($xml);
			
			if(!$dat) {
				// ルート探索エラー
				echo "searchroute error";
				exit;
			}
			
			// ルート解析
			// distanceを加算しDISTに達する緯度経度を算出
			$route_dist = 0;
			foreach ($dat->links->link as $route_array) {
				$route_dist += $route_array->info->distance;
				if ($route_dist > $k) {
					// 指定距離を超えた場合、ルートを分割して距離算出
					$route_dist -= $route_array->info->distance;
					
					// $kまでの残距離
					$rest_dist = $k - $route_dist;
					
					// ルートの緯度経度点列を配列に格納
					$point_array = explode(",", $route_array->path);
					
					for ($j = 2; $j < count($point_array); $j+=2) {
						
						$latS = $point_array[$j-1];		// ルート開始緯度
						$lonS = $point_array[$j-2];		// ルート開始経度
						$latE = $point_array[$j+1];		// ルート終了緯度
						$lonE = $point_array[$j];		// ルート終了緯度
						
						// 緯度経度点間の距離を算出
						$tmp_dist = getDistFromLatLon($base_lat_dist_m, $base_lon_dist_m, $latS, $lonS, $latE, $lonE);
						
						// ルート距離に加算
						$route_dist += $tmp_dist;
						
						if (($route_dist > $k) || ($j == count($point_array) - 2)) {
							// 指定距離を超えた場合、ルートの緯度経度間にてDISTとなるポイントを算出
							$route_dist -= $tmp_dist;
							
							// $kまでの残距離
							$rest_dist = $k - $route_dist;
							
							// 道のりで$kの緯度経度
							$route_lat = round($latS + (($latE - $latS) * ($rest_dist / $tmp_dist)));
							$route_lon = round($lonS + (($lonE - $lonS) * ($rest_dist / $tmp_dist)));
							
							// 到達地点をデータを配列に格納
							$dest_point[] = $route_lon." ".$route_lat;
							break;
						}
					}
					break;
				}
			}
		}
	}


	// geos用ポリゴン文字列
	$geos_poly_str = implode(", ", $dest_point);
	$geos_poly_str .= ", ".$dest_point[0];

	// 凸包生成
	$convexHull_arr = getConvexHull($geos_poly_str, ",");

	$retStr = "";
	
	// 出力用文字列整形
	foreach($convexHull_arr as $point) {
		$latlon = explode(",", $point);
		if($retStr) {
			$retStr .= $delimiter;
		}
		$retStr .= $latlon[1]." ".$latlon[0];
	}

	// 結果出力
	echo $retStr;

?>
