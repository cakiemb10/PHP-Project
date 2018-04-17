<?PHP
// ------------------------------------------------------------
// クリック版関数
// 
// 開発履歴
//   2008/02/15 Y.Matsukawa 新規作成
//   2008/08/22 Y.Matsukawa 英字対応
// ------------------------------------------------------------
//********************************************************************
//* 地図四隅緯度経度情報取得
//********************************************************************
function getMapInfo($lat, $lon, $level, $width, $height){
	global $D_ZOOM2PXMS_LAT;
	global $D_ZOOM2PXMS_LON;

	$zoom = f_get_zoom($level);

	$pxlat = $D_ZOOM2PXMS_LAT["$zoom"];
	$pxlon = $D_ZOOM2PXMS_LON["$zoom"];

	$MAPHLAT = (($height * $pxlat)/2);
	$MAPHLON = (($width  * $pxlon)/2);

	return array(($lat-$MAPHLAT), ($lon-$MAPHLON), ($lat+$MAPHLAT), ($lon+$MAPHLON), $pxlat, $pxlon);
}

//********************************************************************
//* 地図レベルからCMDNのズーム取得
//********************************************************************
function f_get_zoom($level) {
	global $D_ZOOM;

	// この定数は、cmdn.incにて記述（おかしいと思ったらfunctin.incの末尾の関数参照）
	return $D_ZOOM[$level];
}

//********************************************************************
//* アイコン画像取得
//********************************************************************
function getUserIconImage($icon_no){
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;
	
	$cgi = sprintf("%s?cid=%s&icon_id=%s&opt=%s",$D_SSAPI["icon_select"],$D_CID,$icon_no,$D_LOG_CID);
	
	$img = ZdcHttpRead($cgi, true, $D_SOCKET_TIMEOUT);
	
	return $img;
}

//********************************************************************
//* 地図画像取得
//********************************************************************
function getMapImage($lat, $lon, $level, $width, $height, $type, $layer = "", $marktyp = ""){
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;
	global $D_MAP_LAYER_KBN;	// add 2008/08/22 Y.Matsukawa

	$url = $D_SSAPI["getmap"]."?env=1&key=".$D_SSAPI_KEY;
	$url .= "&type=".$type;						// 画像タイプ 0:GIF 7:PNG
	$url .= "&zoom=".f_get_zoom($level);		// ズームレベル
	$url .= "&lat=".$lat;						// 緯度
	$url .= "&lon=".$lon;						// 経度
	$url .= "&w=".$width;						// 地図幅
	$url .= "&h=".$height;						// 地図高さ
	$url .= "&cpflg=1";							// コピーライト（あり）
	$url .= "&opt=".$D_CID;						// 企業ＩＤ
	if($layer != ""){							// レイヤーオプション
		$url .= "&layer=$layer";
	}
	if($marktyp != ""){							// マークタイプ 1:カラー 2:グレー 3:なし
		$url .= "&mtype=$marktyp";
	}
	if ($D_MAP_LAYER_KBN == '5') {				// 英字		add 2008/08/22 Y.Matsukawa
		$url .= "&lang=eng";
	}

	$img = ZdcHttpRead($url, true, $D_SOCKET_TIMEOUT);

	return $img;
}

//********************************************************************
//* 地図ルート画像取得
//********************************************************************
function getRouteMapImage($stlat, $stlon, $edlat, $edlon, $lat, $lon, $level, $width, $height, $type, $layer="", $marktyp="", $rtyp=3){
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;
	global $D_MAP_LAYER_KBN;	// add 2008/08/22 Y.Matsukawa

	$url = $D_SSAPI["getroutemap"]."?env=1&key=".$D_SSAPI_KEY;
	$url .= "&type=".$type;						// 画像タイプ 0:GIF 7:PNG
	$url .= "&rtyp=".$rtyp;						// ルートタイプ 2：自動車 3：自動判別
	$url .= "&sty=".$stlat;						// 始点緯度
	$url .= "&stx=".$stlon;						// 始点経度
	$url .= "&edy=".$edlat;						// 終点緯度
	$url .= "&edx=".$edlon;						// 終点経度
	$url .= "&zoom=".f_get_zoom($level);		// ズームレベル
	$url .= "&lat=".$lat;						// 緯度
	$url .= "&lon=".$lon;						// 経度
	$url .= "&w=".$width;						// 地図幅
	$url .= "&h=".$height;						// 地図高さ
	$url .= "&icprm=00";						// アイコン（非表示）
	$url .= "&cpflg=1";							// コピーライト（なし）
	$url .= "&opt=".$D_CID;						// 企業ＩＤ
	if($layer != ""){							// レイヤーオプション
		$url .= "&layer=$layer";
	}
	if($marktyp != ""){							// マークタイプ 1:カラー 2:グレー 3:なし
		$url .= "&mtype=$marktyp";
	}
	if ($D_MAP_LAYER_KBN == '5') {				// 英字		add 2008/08/22 Y.Matsukawa
		$url .= "&lang=eng";
	}
	
	$img = ZdcHttpRead($url, true, $D_SOCKET_TIMEOUT);
	
	if (substr($img, 0, 3) == "404") {
		$img .= $url;
	}

	return $img;
}

//********************************************************************
//* 地図クリック位置の緯度経度取得
//********************************************************************
function getMapClickLL($lat, $lon, $x, $y, $level, $width, $height) {
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;

	$url = $D_SSAPI["cvtxy2ll"]."?key=".$D_SSAPI_KEY;
	$url .= "&zoom=".f_get_zoom($level);		// ズームレベル
	$url .= "&lat=".$lat;						// 緯度
	$url .= "&lon=".$lon;						// 経度
	$url .= "&w=".$width;						// 地図幅
	$url .= "&h=".$height;						// 地図高さ
	$url .= "&x=".$x;							// クリック位置（x）
	$url .= "&y=".$y;							// クリック位置（x）
	$url .= "&opt=".$D_CID;						// 企業ＩＤ

	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if (substr($status, 3) == 0) {
		$d = explode("\t", $dat[1]);
		return array($d[0], $d[1]);		// array(緯度,経度)
	}
	
	return null;
}

//********************************************************************
//* アイコン緯度経度から中心座標と最適レベルを求める
//********************************************************************
function ZdcGetZoomLevel($mapw, $maph, $prm_lng, $prm_lat, &$cent_lng, &$cent_lat, &$level, $center=0, $route=0){

	// 初期値設定
	$ret = false;

	$minlng = 9999999999;
	$minlat = 9999999999;
	$maxlng = 0;
	$maxlat = 0;

	for($i = 0 ; $i < count($prm_lng) ; $i++){
		if($minlng > $prm_lng[$i]) $minlng = $prm_lng[$i];
		if($minlat > $prm_lat[$i]) $minlat = $prm_lat[$i];
		if($maxlng < $prm_lng[$i]) $maxlng = $prm_lng[$i];
		if($maxlat < $prm_lat[$i]) $maxlat = $prm_lat[$i];
	}

	// 配列の最後が検索中心のはず
	if($center == 1){
		$now_cent_lng = $prm_lng[count($prm_lng)-1];
		$now_cent_lat = $prm_lat[count($prm_lat)-1];
	} else {
		$now_cent_lng = round(($maxlng + $minlng) / 2);
		$now_cent_lat = round(($maxlat + $minlat) / 2);
	}
	
	$diff_lng = $maxlng - $minlng;
	$diff_lat = $maxlat - $minlat;

	// 地図範囲に入りきらない場合を考慮して最大ズームをあらかじめセット
	$level = 1;

	//	// 全てのアイコンの中心（検索中心も含んでいるので、検索中心を除いたものにするのが正しい）
	//	$cent_lng = round(($maxlng + $minlng) / 2);
	//	$cent_lat = round(($maxlat + $minlat) / 2);
	$cent_lng = $now_cent_lng;
	$cent_lat = $now_cent_lat;
	
	// ルート探索モードの場合、旗なので左下が基準になるようにオフセットを調整
	if($route){
		$topoffset_px = 30;
		$botoffset_px = 2;
	} else {
		$topoffset_px = 15;
		$botoffset_px = 15;
	}

	// 最大のズームから検索
	for($i = 18; $i >= 1 ;  $i--){
		// 指定レベルの左下、右上の緯度経度及び１ピクセル辺りのＭＳを取得
		list($LBL, $LBG, $RTL, $RTG, $px2ms_lat, $px2ms_lon) = getMapInfo($now_cent_lat, $now_cent_lng, $i, $mapw, $maph);

		$LBL = round($LBL);
		$LBG = round($LBG);
		$RTL = round($RTL);
		$RTG = round($RTG);

		// アイコンオフセット分の計算
		$topoffsetWidth = ($px2ms_lon * $topoffset_px);
		$topoffsetHeight= ($px2ms_lat * $topoffset_px);
		$botoffsetWidth = ($px2ms_lon * $botoffset_px);
		$botoffsetHeight= ($px2ms_lat * $botoffset_px);

		// 地図範囲に入るかどうか判定
		if( ($LBG + $botoffsetWidth  ) < $minlng &&
			($LBL + $botoffsetHeight ) < $minlat &&
			($RTG - $topoffsetWidth  ) > $maxlng &&
			($RTL - $topoffsetHeight ) > $maxlat ){

			// 入った縮尺を返却
			$level = $i;
			$ret = true;
			break;
		}
	}

	return $ret;
}

//********************************************************************
//* 地図上のアイコン用クリッカブルマップ情報を取得
//********************************************************************
function ZdcGetMapIconCoords($lat, $lon, $lv, $mapw, $maph, $icon_type, &$icon_file, &$icon_lat, &$icon_lon, $xoffse=0, $yoffset=0) {
	
	$coords = null;
	
	list($LBL, $LBG, $RTL, $RTG) = getMapInfo($lat, $lon, intval($lv), $mapw, $maph);

	$px2ms_lon = ($RTG - $LBG) / $mapw;
	$px2ms_lat = ($RTL - $LBL) / $maph;

	// 地図の中心とレベルから１ピクセル当たりのＭＳを算出
	$px = ($mapw * $px2ms_lon);
	$py = ($maph * $px2ms_lat);

	// 地図左下緯度経度を算出
	$left_side = $lon - ($px / 2);
	$left_under= $lat - ($py / 2);
	
	for ($i = 0; $i < count($icon_lat); $i++) {
		if ($icon_type == "ID") {
			$icon_img = @ImageCreateFromString(getUserIconImage($icon_file[$i]));
		} if ($icon_type == "GIF") {
			$icon_img = @ImageCreateFromGif($icon_file[$i]);
		}
		if ($icon_img) {
			$x[0] = ($icon_lon[$i] - $left_side) / $px2ms_lon;
			$y[0] = $maph - (($icon_lat[$i] - $left_under) / $px2ms_lat);
			$x[0] = round($x[0] - (imagesx($icon_img)/2));
			$y[0] = round($y[0] - (imagesy($icon_img)/2));
			$x[1] = $x[0] + imagesx($icon_img);
			$y[1] = $y[0] + imagesy($icon_img);
			$x[0] += $xoffset;
			$y[0] += $yoffset;
			$x[1] += $xoffset;
			$y[1] += $yoffset;
			$coords[]["coords"] = $x[0].",".$y[0].",".$x[1].",".$y[1];
		}
	}
	
	return $coords;
}

?>
