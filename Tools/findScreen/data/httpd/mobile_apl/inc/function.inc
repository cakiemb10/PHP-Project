<?PHP
// ------------------------------------------------------------
// 2009/02/16 Y.Matsukawa	全角→半角コンバート機能（$D_Z2H_OPTION）追加
// 2009/08/27 Y.Matsukawa	拠点縮尺設定
// 2010/01/18 Y.Matsukawa	【不具合修正】フリーワードにスペースが含まれている場合、半角スペース混在のままログ出力されてしまい、ログ項目区切りが不正になる
// 2010/03/17 Y.Matsukawa	オートGPSリマインド
// 2010/04/19 Y.Matsukawa	脆弱性対策（logディレクトリ移動）
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/10/01 Y.Matsukawa	ログ出力時、全てのパラメータのスペース置換と桁数揃えを実施（不正アクセス対応）
// 2011/04/11 Y.Matsukawa	【不具合修正】オプションコード桁あふれ対応（不正アクセス）
// 2011/05/09 H.Osamoto		Myエリア機能追加
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/25 Y.Matsukawa	特定の検索でopt指定を無効化する
// 2012/01/04 Y.Matsukawa	別企業ID参照
// 2012/01/13 N.Wada		拠点データ取得時に、SJISに変換しかつURLエンコードしたものをセットする
// 2012/01/26 H.osamoto		拠点詳細テンプレートに拠点ID(@KID@)を渡す
// 2012/01/30 K.Masuda		拠点情報取得に公開開始・終了日、NEW表示開始・終了日の追加
// 2012/02/14 Y.Matsukawa	日時項目の分割表示
// 2012/02/16 Y.Matsukawa	店舗詳細＆地図でoptcd絞り込み利用
// 2012/08/03 H.osamoto		禁則文字緩和対応(「'」「"」「>」「\」「`」（バッククォート）)を許可
// 2012/08/15 H.osamoto		拠点データ取得時に、UTF8に変換しかつURLエンコードしたものをセットする
// 2012/09/21 H.osamoto		任意カラムのアイコンIDを使用できるようにする
// 2012/11/21 H.osamoto		専用区分の名称を設定
// 2013/02/07 H.osamoto		禁則文字緩和の不具合対応
// 2013/03/26 H.Iijima		リアルタイムデータ
// 2013/07/19 T.Sasaki		拠点（複数）画像対応
// 2013/07/31 H.Osamoto		ヤマト運輸向けカスタマイズ：営業時間、定休日サマリ表示
// 2013/08/28 Y.Matsukawa	【ヤマト運輸】任意カラムの値判定
// 2015/05/22 H.osamoto		拠点縮尺にキーワードを付与し誤作動を防ぐ
// 2015/09/06 Y.Matsukawa	セキュリティ対応（SQL Injection）
// 2015/10/08 N.Wada		任意カラムの値判定にLT,GT,LTE,GTEを追加
// 2015/12/10 Y.Uesugi		ヤマト運輸向けカスタマイズ：営業日サマリ
// 2016/03/30 Y.Matsukawa	アイコンID部分一致判定
// 2016/06/01 Y.Matsukawa	最寄りアイコン10個表示
// 2016/06/13 Y.Matsukawa	フラグ項目グループ判定
// 2016/06/13 Y.Matsukawa	時刻書式整形
// 2016/06/15 Y.Matsukawa	許可タグ追加
// 2016/09/26 N.Wada		値グループ判定（どれか１つ以上、任意の値と一致する）
// 2016/09/30 N.Wada		任意カラム（時刻）同士の比較
// 2016/10/06 N.Wada		値グループ判定
// 2016/10/25 N.Wada		フラグ項目グループ判定（フラグ項目すべてON）
// 2016/11/01 N.Wada		郵便番号の数値7桁にハイフンをつけて「111-0000」の形式にする
// 2016/11/16 Y.Matsukawa	日本郵政向けマップタイプ対応
// ------------------------------------------------------------
include_once("inc/define_cmdn.inc");

// add 2010/07/20 Y.Matsukawa [
// mod 2011/07/05 Y.Nakajima [
/*
if (!$https_req) {
	$https_req = $_SERVER['HTTPS'];
}
*/
if (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] != "") {
	$https_req = $_SERVER['HTTPS'];
} else {
	$https_req = "";
}
// mod 2011/07/05 Y.Nakajima ]
// mod 2011/07/05 Y.Nakajima 
if (isset($https_req) && $https_req != "") {
	$protocol = 'https';
} else {
	$protocol = 'http';
}
// add 2010/07/20 Y.Matsukawa ]

//********************************************************************
//
// ログ関係
// 出力内容
//  1.基本
//    script cid opt refferer status service
//  2.emapview
//    kid lat lon type keyword adcd area col nm no cond
//  3.search
//    page jnrmn jnr jkn
//
//   2008/09/09 Y.Matsukawa 英字対応
//   2009/03/13 Y.Matsukawa 【不具合修正】フリーワード検索で半角スペースが正しく渡らない不具合に対処
//                          ZdcSanitizeKeyword：半角スペース→「+」置換を廃止（但し$sprep指定時は$sprepに置換）
//********************************************************************
function ZdcMobileLogPut($cid, $cgistatus, $mobilestatus, $mode) {
	$LOG_MODE = "MOBILE";
	//include("/home/emap/httpd/log/inc/com_log_open.inc");		mod 2010/04/19 Y.Matsukawa
	include("/home/emap/src/log/inc/com_log_open.inc");

	global $_SERVER;
	global $_GET;
	global $_POST;
	global $D_LOG_NORMAL_CD;
	global $D_SSAPI_KEY;
	global $D_LOG_CID;

	if($cgistatus != ""){
	   $log_status = $cgistatus;
	} else {
		if($D_LOG_NORMAL_CD == $D_LOG_NORMAL_CD){
			$ok = 0;
		} else {
			$ok = 1;
		}
		if(strpos($_SERVER["SCRIPT_NAME"],"s.htm") > -1){
			$cgi_no = 750;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"a.htm") > -1){
			$cgi_no = 751;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"c.htm") > -1){
			$cgi_no = 752;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"cl.htm") > -1){
			$cgi_no = 753;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"cp.htm") > -1){
			$cgi_no = 754;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"d.htm") > -1){
			$cgi_no = 755;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"e.htm") > -1){
			$cgi_no = 756;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"nm.htm") > -1){
			$cgi_no = 757;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"ne.htm") > -1){
			$cgi_no = 758;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"z.htm") > -1){
			$cgi_no = 759;
		} else if(strpos($_SERVER["SCRIPT_NAME"],"m.htm") > -1){
			$cgi_no = 760;
		} else {
			$cgi_no = 790;
		}
		$log_status = sprintf("%03d%d%04d", $cgi_no, $ok, $mobilestatus);
	}

	// ログ出力
	//$prm1 = sprintf("%s %s %s %s %s %s ","EmapSsM", $D_LOG_CID , "", $log_status, "", $D_SSAPI_KEY);		mod 2011/04/11 Y.Matsukawa
	$prm1 = sprintf("%s %s %s %s %s %s "
					,"EmapSsM"
					,mb_strimwidth(mb_ereg_replace(' ','_',$D_LOG_CID), 0, 20)
					,""
					,$log_status
					,""
					,mb_strimwidth(mb_ereg_replace(' ','_',$D_SSAPI_KEY), 0, 255)
	);
	$prm2 = sprintf("%s %s ", $_SERVER["SCRIPT_NAME"], $mode);
	// del 2010/10/01 Y.Matsukawa [
	//	$prm3 = sprintf("%s %s %s %s %s ",
	//					mb_convert_encoding(($_GET["p"]  != "" ? $_GET["p"] : $_POST["p"]) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					mb_convert_encoding(($_GET["id"] != "" ? $_GET["id"] : $_POST["id"]) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					//mb_convert_encoding($_GET["key"],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),		mod 2010/01/18 Y.Matsukawa
	//					mb_ereg_replace(' ','_',mb_convert_encoding($_GET["key"],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")),
	//					mb_convert_encoding($_GET["adcd"],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					mb_convert_encoding($_GET["pg"],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")
	//				   );
	//	$prm4 = sprintf("%s %s %s %s %s ",
	//					mb_convert_encoding($_GET["tod"],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					mb_convert_encoding($_GET["shk"],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					mb_convert_encoding(($_GET["pos"] != "" ? $_GET["pos"] : $_POST["pos"]),"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					//mb_convert_encoding(($_GET["z"]   != "" ? $_GET["z"]   : $_POST["z"])  ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),		mod 2010/01/18 Y.Matsukawa
	//					mb_ereg_replace(' ','_',mb_convert_encoding(($_GET["z"]   != "" ? $_GET["z"]   : $_POST["z"])  ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")),
	//					//mb_convert_encoding(($_GET["nm"]  != "" ? $_GET["nm"]  : $_POST["nm"]) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")		mod 2010/01/18 Y.Matsukawa
	//					mb_ereg_replace(' ','_',mb_convert_encoding(($_GET["nm"]  != "" ? $_GET["nm"]  : $_POST["nm"]) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"))
	//				   );
	//	$prm5 = sprintf("%s %s %s %s %s ",
	//					mb_convert_encoding(($_GET["bl"]  != "" ? $_GET["bl"]  : $_POST["bl"]) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS"),
	//					$_GET["slg"],
	//					$_GET["fr"],
	//					"",
	//					""
	//				   );
	// del 2010/10/01 Y.Matsukawa ]
	// add 2010/10/01 Y.Matsukawa [
	// add 2011/07/05 Y.Nakajima [
	if (isset($_GET['p']) && $_GET['p'] != "") $p = $_GET['p'];
	 else if (isset($_POST['p'])) $p = $_POST['p'];
	 else $p = "";
	if (isset($_GET['id']) && $_GET['id'] != "") $id = $_GET['id'];
	 else if (isset($_POST['id'])) $id = $_POST['id'];
	 else $id = "";
	
	if (isset($_GET["key"])) $key = $_GET["key"];
	 else $key = "";
	
	if (isset($_GET["adcd"])) $adcd = $_GET["adcd"];
	 else $adcd = "";
	
	if (isset($_GET["pg"])) $pg = $_GET["pg"];
	 else $pg = "";
	
	if (isset($_GET["tod"])) $tod = $_GET["tod"];
	 else $tod = "";
	
	if (isset($_GET["shk"])) $shk = $_GET["shk"];
	 else $shk = "";
	
	if (isset($_GET['pos']) && $_GET['pos'] != "") $pos = $_GET['pos'];
	 else if (isset($_POST['pos'])) $pos = $_POST['pos'];
	 else $pos = "";
	
	if (isset($_GET['z']) && $_GET['z'] != "") $z = $_GET['z'];
	 else if (isset($_POST['z'])) $z = $_POST['z'];
	 else $z = "";
	
	if (isset($_GET['nm']) && $_GET['nm'] != "") $nm = $_GET['nm'];
	 else if (isset($_POST['nm'])) $nm = $_POST['nm'];
	 else $nm = "";
	
	if (isset($_GET['bl']) && $_GET['bl'] != "") $bl = $_GET['bl'];
	 else if (isset($_POST['bl'])) $bl = $_POST['bl'];
	 else $bl = "";
	
	if (isset($_GET["slg"])) $slg = $_GET["slg"];
	 else $slg = "";
	
	if (isset($_GET["fr"])) $fr = $_GET["fr"];
	 else $fr = "";
	
	// add 2011/07/05 Y.Nakajima ]

	$prm3 = sprintf("%s %s %s %s %s "
	// mod 2011/07/05 Y.Nakajima [
					,mb_strimwidth(mb_ereg_replace(' ','_',($p)), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',($id)), 0, 128, '...')
					//,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding($key,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding($key,"eucJP-win","ASCII,JIS,UTF-8,eucJP-win,SJIS-win")), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$adcd), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$pg), 0, 128, '...')
	// mod 2011/07/05 Y.Nakajima ]
	);
	$prm4 = sprintf("%s %s %s %s %s "
	// mod 2011/07/05 Y.Nakajima [
					,mb_strimwidth(mb_ereg_replace(' ','_',$tod), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$shk), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',($pos)), 0, 128, '...')
					//,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding(($z)  ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding(($z)  ,"eucJP-win","ASCII,JIS,UTF-8,eucJP-win,SJIS-win")), 0, 128, '...')
					//,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding(($nm) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding(($nm) ,"eucJP-win","ASCII,JIS,UTF-8,eucJP-win,SJIS-win")), 0, 128, '...')
	// mod 2011/07/05 Y.Nakajima ]
	);
	$prm5 = sprintf("%s %s %s %s %s "
	// mod 2011/07/05 Y.Nakajima [
					//,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding(($bl) ,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS")), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',mb_convert_encoding(($bl) ,"eucJP-win","ASCII,JIS,UTF-8,eucJP-win,SJIS-win")), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$slg), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$fr), 0, 128, '...')
					,""
					,""
	// mod 2011/07/05 Y.Nakajima ]
	);
	// add 2010/10/01 Y.Matsukawa ]
	$prm = $prm1.$prm2.$prm3.$prm4.$prm5;
	$prm = str_replace("\n","",$prm);
	$prm = str_replace("\r","",$prm);
	$log_mobile->info($prm);
	//include("/home/emap/httpd/log/inc/com_log_close.inc");		mod 2010/04/19 Y.Matsukawa
	include("/home/emap/src/log/inc/com_log_close.inc");
}

//********************************************************************
//* 画面を遷移させる
//********************************************************************
function pageRedirector($url){
	global $protocol;		// add 2010/07/20 Y.Matsukawa
	// リダイレクト先のＵＲＬを生成
	//$sv = "http://".$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];		mod 2010/07/20 Y.Matsukawa
	$sv = "$protocol://".$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
	$sv = str_replace(basename($_SERVER['SCRIPT_NAME']), "", $sv). $url;

	// 原状のＨＴＴＰヘッダで必要なもののみ取得する。
	// HTTP_X_〜
	// USER_AGENT
	$param = "";
	foreach($_SERVER as $key => $val){
		// mod 2011/07/05 Y.Nakajima
		if (!is_array($key) && !is_array($val)) {    // add 2011/07/05 Y.Nakajima
		//if(ereg("^HTTP_X_", $val)){
		if(preg_match("/^HTTP_X_/", $val, $matches)){
			$param .= $key.": ".$val."\n";
		} else if($key == "HTTP_USER_AGENT"){
			$agent = $val."\r\n";
		}
		}    // add 2011/07/05 Y.Nakajima
	}

	// HTTPヘッダを送信するように一時変更
	ini_set('user_agent', $agent.$param);

	// リダイレクト先のページを読み込み
	// Locationヘッダを利用すると、使えない端末があるため、
	// 通信させる
	header("Location: ".$sv);
//	include($sv);
exit;

//	header("Location: ".$sv);
//	exit;
//	$param = "";
//	foreach($_SERVER as $key => $val){
//		if(ereg("^HTTP_X_", $val)){
//			$param .= $key.": ".$val."\n";
//		} else if($key == "HTTP_USER_AGENT"){
//			$agent = $val."\r\n";
//		}
//	}
//
//	global $carrier;
//	ini_set('user_agent', $agent.$param);
//	dbl("PARAM=[".$agent.$param."]");
//	$content=file_get_contents($sv);
//	$content=ZdcHttpRead($sv, true, 5);
//	header("Content-Type: text/html;charset=Shift_JIS");
//	echo $carrier->ConvertPictString($content, "SJIS", "ASCII,JIS,UTF-8,EUC-JP,SJIS");
//	exit;
//
//	$url_array = parse_url($sv);
//	//User-Agent
//	//HTTP_X_*
//	//HTTP_HOST
//	include($sv);
///exit;
//dbl("REDIRECT TO :[".$sv."]");
//	$line="";
//	$fp = fsockopen($url_array['host'], 80, $errno, $errstr, 5);
//dbl("SOCKET OPEN [$errstr]");
//	if (!$fp) {
//		erl("pageRedirector Error ERR[$errstr] ERRNO[$errno]");
//		$line="";
//	} else {
//		$len=strlen($url_array['query']);
//dbl("SEND LENGTH [$len]");
//dbl("SEND PARAMS [".$url_array['query']."]");
//		fputs ($fp, "POST ".$url['path']." HTTP/1.0\r\n".$url_array['query']."\r\n\r\n");
//		while (!feof($fp)) {
//			$line .= fgets ($fp,1024);
//		}
//		fclose ($fp);
//	}
//dbl("RETURN HTML [$line]");
//	return $line;
//	global $carrier;
//	ini_set('user_agent', $carrier->G_USER_AGENT);
//	$content=file_get_contents($sv.$url);
//	$content=ZdcHttpRead($sv.$url, true);
//	header("Content-Type: text/html;charset=Shift_JIS");
//	echo $carrier->ConvertPictString($content, "SJIS", "ASCII,JIS,UTF-8,EUC-JP,SJIS");
//	exit;
}

//********************************************************************
//* ２点間の距離を求める。
//********************************************************************
function getDistance($lttd1, $lgtd1, $lttd2, $lgtd2){
	$lttd2 = abs($lttd1 - $lttd2) * 9000 / 300000;
    $lgtd2 = abs($lgtd1 - $lgtd2) * 11000 / 450000;
    return intval( sqrt(($lttd2*$lttd2) + ($lgtd2*$lgtd2)) );
}
//********************************************************************
//* 緯度経度チェック
//* cnvll2dms.inc参照
//********************************************************************
function checkLatLon($wgs84, $lat, $lon, &$latms, &$lonms){
	if($wgs84){ $type = WGS84_TO_TKY; } else { $type = TKY_TO_TKY; }
	return cnv_ll2lldms($lat, $lon, $type, &$latms, &$lonms);
}

//********************************************************************
//* 緯度経度チェックのチェックを行いミリ秒形式で返却
//* cnvll2dms.inc参照
//********************************************************************
function checkZLatLon($wgs84, $prm, &$lat, &$lon){
	if($wgs84){ $type = WGS84_TO_TKY; } else { $type = TKY_TO_TKY; }
	return cnv_zill2lldms($prm, $type, &$lat, &$lon);
}

//********************************************************************
//* ルート探索の結果から地図上に重畳するためのルート情報緯度経度を
//* 地図左上基準からのピクセル座標に変換する。
//********************************************************************
function convLatLon2PolylinePx(
	$ROUTE_INFO, $NODE_CNT, 
	$CENTER_LAT, $CENTER_LON, 
	$MAP_WIDTH_PX, $MAP_HEIGHT_PX, 
	$ONE_PX_MS_LON, $ONE_PX_MS_LAT
){
	$P_XY = array();

	for($i = 0 ; $i < $NODE_CNT ; $i++){
		// mod 2011/07/05 Y.Nakajima
		//$node_array = split("/", $ROUTE_INFO[$i]);
		$node_array = explode("/", $ROUTE_INFO[$i]);
		$poly_data = substr($node_array[3], 1, strlen($node_array[3]) - 2);
		$poly_data = str_replace("),(", "##", $poly_data);
		$poly_data = ereg_replace("(\)|\()", "", $poly_data);
		$point_array = explode("##", $poly_data);

		$roadtyp  = $node_array[4];
		$kozo     = $node_array[6];

		$point_array_cnt = count($point_array);

		// 地図範囲内に座標を補正しつつ格納
		for($l = 0 ; $l < $point_array_cnt ; $l+=1){
			$latlon = explode(",", $point_array[$l]);

			// ピクセル座標を求める
			// 左下からの相対位置で、Ｙの値は左上を基準に
			$x = ($MAP_WIDTH_PX /2) - round((($CENTER_LON - $latlon[0]) / $ONE_PX_MS_LON));
			$y = ($MAP_HEIGHT_PX/2) - round((($CENTER_LAT - $latlon[1]) / $ONE_PX_MS_LAT));
			$y = $MAP_HEIGHT_PX - $y;

			// 同一ピクセルの点は間引き対象
			if($x == $ox && $y == $oy) continue;
			$ox = $x; $oy = $y;

			array_push($P_XY, "$x#$y#$roadtyp#$kozo");
		}
	}
	return $P_XY;
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
//* 企業アイコン画像取得
//********************************************************************
function getUserIconImage($icon_no){
	global $D_SSAPI;
	//global $D_CID;		del 2012/01/04 Y.Matsukawa
	global $D_ICON_CID, $D_LOG_CID;		// add 2012/01/04 Y.Matsukawa
	//$cgi = sprintf("%s?cid=%s&icon_id=%s&opt=%s",$D_SSAPI["icon_select"],$D_CID,$icon_no,$D_LOG_CID);		mod 2012/01/04 Y.Matsukawa
	$cgi = sprintf("%s?cid=%s&icon_id=%s&opt=%s", $D_SSAPI["icon_select"], $D_ICON_CID, $icon_no, $D_LOG_CID);
	$img = ZdcHttpRead($cgi, true, 5);
	return $img;
}

//********************************************************************
//* 地図画像イメージ取得
//********************************************************************
//function getMapImage($lat, $lng, $level, $width, $height, $type, $layer = "", $marktyp = ""){		mod 2008/09/09 Y.Matsukawa
function getMapImage($lat, $lng, $level, $width, $height, $type, $layer = "", $marktyp = "", $lang = ""){
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_LOG_CID;

	$url = $D_SSAPI["getmap"]."?env=1&key=".$D_SSAPI_KEY;
	$url .= "&type=".$type;						// 画像タイプ 0:GIF 7:PNG
	$url .= "&zoom=".f_get_zoom($level);		// ズームレベル
	$url .= "&lat=".$lat;						// 緯度
	$url .= "&lon=".$lng;						// 経度
	$url .= "&w=".$width;						// 地図幅
	$url .= "&h=".$height;						// 地図高さ
	$url .= "&cpflg=1";							// コピーライト描写（なし）
	$url .= "&opt=".$D_LOG_CID;						// ログ用の企業ＩＤ

	if($layer != ""){							// レイヤーオプション
		$url .= "&layer=$layer";
	}
	if($marktyp != ""){							// マークタイプ 1:カラー 2:グレー 3:なし
		$url .= "&mtype=$marktyp";
	}
	if($lang != ""){							// 言語		add 2008/09/09 Y.Matsukawa
		$url .= "&lang=$lang";
	}
	// add 2016/11/16 Y.Matsukawa [
	// 日本郵政向けマップタイプ
	if ($marktyp == '45') {
		$url .= '&cid=00010';
	}
	// add 2016/11/16 Y.Matsukawa ]

	$ret = ZdcHttpRead($url, true, 5);

	if($ret == false){
		$ret = "40099999\t0\t0";
	}

	return $ret;
}


//********************************************************************
//* 地図画像イメージ取得
//********************************************************************
function getMapImage2($lat, $lng, $level, $width, $height, $type, $layer = "", $marktyp = ""){

$ic = 1003;
$ix=0;

$LP_Mark = array();
$LP_Mark["lati"][$ix] = 128441348; $LP_Mark["logi"][$ix] = 503183613; $LP_Mark["mrkn"][$ix] = $ic; $ix++; $MarkCnt = $MarkCnt+1;
$LP_Mark["lati"][$ix] = 128435674; $LP_Mark["logi"][$ix] = 503182460; $LP_Mark["mrkn"][$ix] = $ic; $ix++; $MarkCnt = $MarkCnt+1;
$LP_Mark["lati"][$ix] = 128422521; $LP_Mark["logi"][$ix] = 503156626; $LP_Mark["mrkn"][$ix] = $ic; $ix++; $MarkCnt = $MarkCnt+1;
$LP_Mark["lati"][$ix] = 128417751; $LP_Mark["logi"][$ix] = 503156880; $LP_Mark["mrkn"][$ix] = $ic; $ix++; $MarkCnt = $MarkCnt+1;
$LP_Mark["lati"][$ix] = 128411744; $LP_Mark["logi"][$ix] = 503153706; $LP_Mark["mrkn"][$ix] = $ic; $ix++; $MarkCnt = $MarkCnt+1;
$LP_Mark["lati"][$ix] = 128444890; $LP_Mark["logi"][$ix] = 503158670; $LP_Mark["mrkn"][$ix] = $ic; $ix++; $MarkCnt = $MarkCnt+1;

$LP_Map = array();
$LP_Map["host"] = "192.168.1.20";
$LP_Map["port"] = 5670;
$LP_Map["myid"] = 0;
$LP_Map["corp"] = "00010";
$LP_Map["pass"] = "";
$LP_Map["lati"] = $lat;            // 中心座標：緯度(ms)
$LP_Map["logi"] = $lng;           // 中心座標：経度(ms)
$LP_Map["wdth"] = $width;        // 画像サイズ：横幅(PIXEL)
$LP_Map["hght"] = $height;        // 画像サイズ：高さ(PIXEL)
$LP_Map["mlvl"] = 99;            // 縮尺レベル
$LP_Map["ityp"] = 7;                // 出力画像形式(7:8bitPNG)
$LP_Map["mtyp"] = 3;        // マークタイプ
$LP_Map["envn"] = 1;        // 地図利用環境番号
$LP_Map["layr"] = 0;
$LP_Map["nmrk"] = $MarkCnt;         // マーク数
$LP_Map["nrec"] = 0;         // 矩形
$LP_Map["nova"] = 0;         // 円　
$LP_Map["nlin"] = 0;         // 折れ線
$LP_Map["nply"] = 0;         // ポリゴン
$LP_Map["ntxt"] = 0;         // 文字
$LP_Map["nlay"] = 0;        // レイヤー
$LP_Map["layr"] = 7;        // レイヤー
$LP_Map["exst"] = 0;             // 地図存在結果
$LP_Map["kein"] = 5;            // 使用地図系統番号(系No)

$LP_Map["zoom"] = f_get_zoom($level);

$im = cmdn_get_map($LP_Map,$LP_Mark);

  return $im[0];
}

//********************************************************************
//* 地図四隅緯度経度情報取得
//********************************************************************
function getMapInfo($lat, $lng, $level, $width, $height){
	global $D_ZOOM2PXMS_LAT;
	global $D_ZOOM2PXMS_LON;

	$zoom = f_get_zoom($level);

	$pxlat = $D_ZOOM2PXMS_LAT["$zoom"];
	$pxlon = $D_ZOOM2PXMS_LON["$zoom"];

	$MAPHLAT = (($height * $pxlat)/2);
	$MAPHLON = (($width  * $pxlon)/2);

	return array(($lat-$MAPHLAT), ($lng-$MAPHLON), ($lat+$MAPHLAT), ($lng+$MAPHLON), $pxlat, $pxlon);
}

//********************************************************************
//* フリーワードから不正な文字を消去する
//********************************************************************
//function ZdcSanitizeKeyword($val, $enc = ""){		mod 2009/03/13 Y.Matsukawa
function ZdcSanitizeKeyword($val, $sprep){
	//$val = str_replace(" ","+",$val);		mod 2009/03/13 Y.Matsukawa
	if (isset($sprep)) $val = str_replace(" ",$sprep,$val);
	//$val = str_replace("'","",$val);		mod 2015/09/06 Y.Matsukawa
	$val = mb_ereg_replace("['\"\|]", '', $val);
	$val = htmlspecialchars($val);

	return $val;
}

//********************************************************************
//* 拠点ＩＤからカラムの連想配列を生成して返却
//* このキーについては、固定キーとするため変更不可
//********************************************************************
//function ZdcGetDetailInfoToArray($id){		mod 2010/03/17 Y.Matsukawa
//function ZdcGetDetailInfoToArray($id, &$carrier){		mod 2012/02/16 Y.Matsukawa
//function ZdcGetDetailInfoToArray($id, &$carrier, $jkn=''){		mod 2013/09/02 Y.Matsukawa
function ZdcGetDetailInfoToArray($id, &$carrier, $jkn='', $putLog=true){
	global $D_SSAPI;
	//global $D_CID;		del 2012/01/04 Y.Matsukawa
	global $D_DATA_CID;		// add 2012/01/04 Y.Matsukawa
	global $D_LOG_CID;
	global $D_KYO_COL_NAME;
	global $D_COL_COUNT;
	global $D_SSAPI_KEY;
	global $D_Z2H_OPTION;		// add 2009/02/16 Y.Matsukawa
	global $D_ICONCIE_REMIND;	// add 2010/03/17 Y.Matsukawa
	global $D_ICONCIE_REMIND_Q;	// add 2010/03/17 Y.Matsukawa
	global $D_URL_BASE;			// add 2010/03/17 Y.Matsukawa
	global $protocol;			// add 2010/07/20 Y.Matsukawa
	global $D_ICONID_COL;		// add 2012/09/21 H.osamoto
	global $D_ICON;		// add 2012/11/19 Y.Matsukawa
	global $D_ORG_KBN_COL, $D_ORG_KBN_NAME_LIST;		// add 2012/11/06 H.osamoto
	global $D_KYOTENID_CUST;		// add 2012/11/19 Y.Matsukawa
	global $D_KYOTEN_IMG_DEF;		// add 2013/07/12 T.Sasaki
	// add 2013/07/31 H.Osamoto [
	global $D_YTC_TIMESUMM, $D_YTC_24_LBL, $D_YTC_ALL_TITLE;
	global $D_YTC_WD_LBL, $D_YTC_TIMECOL_WD_FR, $D_YTC_TIMECOL_WD_TO;
	global $D_YTC_OT_LBL, $D_YTC_TIMECOL_OT_FR, $D_YTC_TIMECOL_OT_TO;
	global $D_YTC_HLDYCOL_DAY_LBL, $D_YTC_HLDYCOL_OTH_LBL;
	global $D_YTC_WKDYCOL_DAY_LBL;		// add 2015/12/10 Y.Uesugi
	// add 2013/07/31 H.Osamoto ]
	global $D_COL_VAL_CHK;		// add 2013/08/28 Y.Matsukawa
	global $D_CUST_CNV_FLG;		// add 2015/12/10 Y.Uesugi
	global $D_COL_VAL_CHK_POS;	// add 2016/03/30 Y.Matsukawa
	global $D_FLAGS_ANY_ON, $D_KYOTEN_ITEM_TIME;		// add 2016/06/13 Y.Matsukawa
	global $D_COLUMNS_ANY_MATCH_VALUE;		// add 2016/09/26 N.Wada
	global $D_TIME_COMP_COLS;		// add 2016/09/30 N.Wada
	global $D_COLUMNS_ANY_VALUE;			// add 2016/10/06 N.Wada
	global $D_FLAGS_ALL_ON;			// add 2016/10/25 N.Wada
	global $D_KYOTEN_ITEM_ZIP;			// add 2016/11/01 N.Wada

	//$cgi = $D_SSAPI["kyotenid"];		del 2013/09/02 Y.Matsukawa
	// add 2013/09/02 Y.Matsukawa [
	if ($putLog) {
		$cgi = $D_SSAPI["kyotenid"];
	} else {
		$cgi = $D_SSAPI["kyotenid_nolog"];
	}
	// add 2013/09/02 Y.Matsukawa ]
	//$url = sprintf("%s?cid=%s&kid=%s&key=%s&type=4&opt=%s",$cgi,$D_CID,$id,$D_SSAPI_KEY,$D_LOG_CID);		mod 2009/02/16 Y.Matsukawa
	//$url = sprintf("%s?cid=%s&kid=%s&key=%s&type=4&opt=%s&z2h=%s",$cgi,$D_CID,$id,$D_SSAPI_KEY,$D_LOG_CID, $D_Z2H_OPTION);		mod 2012/01/04 Y.Matsukawa
	$url = sprintf("%s?cid=%s&kid=%s&key=%s&type=4&opt=%s&z2h=%s", $cgi, $D_DATA_CID, $id, $D_SSAPI_KEY, $D_LOG_CID, $D_Z2H_OPTION);
	if ($jkn) $url .= '&jkn='.urlencode($jkn);		// add 2012/02/16 Y.Matsukawa
	if(isset($D_KYOTENID_CUST) && $D_KYOTENID_CUST) $url .= "&cust=$D_KYOTENID_CUST";// カスタマイズ仕様		add 2012/11/19 Y.Matsukawa
	$url .= '&mltimg=1';	// 拠点（複数）画像取得オプション	2013/07/12 T.Sasaki

	$dat = ZdcHttpRead($url);
	// mod 2011/07/05 Y.Nakajima [
	$status  = explode("\t",$dat[0]);
	//$cnt = count($dat)-1;
	$cnt = $status[1];
	$i = 0;
	// mod 2011/07/05 Y.Nakajima ]
	$ret_array = array();

	if($cnt == 1){
		$rec = explode("\t",$dat[$i + 1]);
		$ret_array["@KID@"] = $id;		// add 2012/01/26 H.osamoto
		$ret_array["@LAT@"] = $rec[0];
		$ret_array["@LON@"] = $rec[1];
		if (isset($D_ICON[$rec[2]])) {		// add 2012/11/19 Y.Matsukawa
			$ret_array["@ICON_ID@"] = $rec[2];
			$ret_array["@ICON_ID_".$rec[2]."@"] = 1;		// add 2012/11/19 Y.Matsukawa
			$ret_array["icon_".$rec[2]] = 1;		// add 2014/12/21 Y.Matsukawa
		}
		$ret_array["@ICON_NUM@"] = $rec[3];
		if($rec[4] == "1"){
			$ret_array["@ICON_NEW@"] = true;
		}
		// add 2013/08/28 Y.Matsukawa [
		//---------------------------------------------
		// 拠点IDの値判定
		// （例）$D_COL_VAL_CHK['kid'][] = array('0001', 'A');
		//  → 拠点ID='0001' ならば、{def kid_EQ_A}が真になる
		//---------------------------------------------
		if (isset($D_COL_VAL_CHK['kid']) && is_array($D_COL_VAL_CHK['kid'])) {
			foreach ($D_COL_VAL_CHK['kid'] as $cvc) {
				$cvc_val = $cvc[0];
				$cvc_lbl = $cvc[1];
				if ($ret_array["@KID@"] == $cvc_val) {
					$ret_array['kid_EQ_'.$cvc_lbl] = 1;
				}
			}
		}
		// add 2013/08/28 Y.Matsukawa ]
		// add 2016/03/30 Y.Matsukawa
		//---------------------------------------------
		// アイコンIDの値判定(比較位置指定)
		// （例）$D_COL_VAL_CHK_POS['icon'][] = array('000', 'A', 0, 3);
		//  → アイコンID='000123'
		//     スタート位置：0文字目
		//     比較終了位置：3文字（文字数）
		//   ならば、{def list/icon_EQP_A}が真になる
		//---------------------------------------------
		if (isset($D_COL_VAL_CHK_POS['icon']) && is_array($D_COL_VAL_CHK_POS['icon'])) {
			foreach ($D_COL_VAL_CHK_POS['icon'] as $cvc) {
				$cvc_val = $cvc[0];
				$cvc_lbl = $cvc[1];
				$iid_val = substr($ret_array["@ICON_ID@"], $cvc[2], $cvc[3]);
				if ($cvc_val == $iid_val) {
					$ret_array['icon_EQP_'.$cvc_lbl] = 1;
				}
			}
		}
		// add 2013/07/31 H.osamoto [
		$ytc_time_wd = array();
		$ytc_time_oh = array();
		$ytc_hldy_lbl = array();
		$ytc_wkdy_lbl = array();	// add 2015/12/10 Y.Uesugi
		$ytc_hldy_oth_lbl = '';
		// add 2013/07/31 H.Osamoto ]
		foreach($D_KYO_COL_NAME[4] as $key => $val){
			$key_name = strtoupper($val);
			//	if($rec[$key+5] == "0"){	mod 2013/07/31 H.Osamoto
			if($rec[$key+5] === "0"){
			} else {
				// mod 2011/07/05 Y.Nakajima
				//$det_value =  mb_convert_encoding($rec[$key+5],"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS");		2007/10/04 mod matsukawa 画面上の文字化け（「11店」→「11?」）を回避
				$det_value =  mb_convert_encoding($rec[$key+5],"eucJP-win","eucJP-win,ASCII,JIS,UTF-8,SJIS-win");
				if($det_value != ""){
					$ret_array["@".$key_name."@"] = $det_value;
					$ret_array[$key_name."l".$det_value] = true;
					$ret_array["@".$key_name."_SJIS_ENC@"] = urlencode(mb_convert_encoding($det_value,"SJIS","eucJP-win"));	// add 2012/01/13 N.Wada
					$ret_array["@".$key_name."_UTF8_ENC@"] = urlencode(mb_convert_encoding($det_value,"UTF-8","eucJP-win"));	// add 2012/08/15 H.Osamoto
					// add 2012/09/21 H.Osamoto [
					// 別カラムのアイコンIDを使用
					if ($key_name == $D_ICONID_COL && $det_value) {
						$ret_array["@ICON_ID@"] = $det_value;
					}
					// add 2012/09/21 H.Osamoto ]
					// add 2012/11/06 H.Osamoto [
					// 専用区分定義を適用
					if ($key_name == $D_ORG_KBN_COL && $det_value && $D_ORG_KBN_NAME_LIST[$det_value]) {
						$ret_array["@".$key_name."_NAME@"] = $D_ORG_KBN_NAME_LIST[$det_value];
					}
					// add 2012/11/06 H.Osamoto ]
					// add 2016/06/13 Y.Matsukawa
					//---------------------------------------------
					// 時刻書式
					//---------------------------------------------
					if (isset($D_KYOTEN_ITEM_TIME[$key_name]) && $D_KYOTEN_ITEM_TIME[$key_name]) {
						formatTimeCol($key_name, $det_value, &$ret_array);
					}
					// add 2015/12/10 Y.Uesugi [
					//---------------------------------------------
					// 特定の値の場合にフラグを立てる
					//---------------------------------------------
					$T_val =  strtoupper($val);
					if (is_array($D_CUST_CNV_FLG[$T_val]) && isset($D_CUST_CNV_FLG[$T_val][$det_value])) {
						$ret_array[$T_val.'_'.$D_CUST_CNV_FLG[$T_val][$det_value]] = 1;
					}
					// add 2015/12/10 Y.Uesugi ]
					// add 2013/08/28 Y.Matsukawa [
					//---------------------------------------------
					// 任意カラムの値判定
					// （例）$D_COL_VAL_CHK['col_01'][] = array('あ', 'A');
					//  → col_01='あ' ならば、{def col_01_EQ_A}が真になる
					//---------------------------------------------
					if (isset($D_COL_VAL_CHK[$val]) && is_array($D_COL_VAL_CHK[$val])) {
						foreach ($D_COL_VAL_CHK[$val] as $cvc) {
							$cvc_val = $cvc[0];
							$cvc_lbl = $cvc[1];
							if ($det_value == $cvc_val) {
								$ret_array[$val.'_EQ_'.$cvc_lbl] = 1;
							}
							// add 2015/10/08 N.Wada [
							if ($det_value < $cvc_val) {
								$ret_array[$val.'_LT_'.$cvc_lbl] = 1;
							}
							if ($det_value > $cvc_val) {
								$ret_array[$val.'_GT_'.$cvc_lbl] = 1;
							}
							if ($det_value <= $cvc_val) {
								$ret_array[$val.'_LTE_'.$cvc_lbl] = 1;
							}
							if ($det_value >= $cvc_val) {
								$ret_array[$val.'_GTE_'.$cvc_lbl] = 1;
							}
							// add 2015/10/08 N.Wada ]
						}
					}
					// add 2013/08/28 Y.Matsukawa ]
					// add 2016/11/01 N.Wada [
					//---------------------------------------------
					// 郵便番号を111-0000の形に成型
					//---------------------------------------------
					if (isset($D_KYOTEN_ITEM_ZIP) && $D_KYOTEN_ITEM_ZIP) {
						if (strlen($ret_array["@".$D_KYOTEN_ITEM_ZIP."@"]) == 7 && is_numeric($ret_array["@".$D_KYOTEN_ITEM_ZIP."@"])){
							$ret_array["@".$D_KYOTEN_ITEM_ZIP."@"] = substr($ret_array["@".$D_KYOTEN_ITEM_ZIP."@"], 0, 3).'-'.substr($ret_array["@".$D_KYOTEN_ITEM_ZIP."@"], 3, 4);
						}
					}
					// add 2016/11/01 N.Wada ]
					// add 2013/07/31 H.Osamoto [
					//---------------------------------------------
					// ヤマト運輸向け：営業時間情報をサマリ
					//---------------------------------------------
					if (isset($D_YTC_TIMESUMM) && $D_YTC_TIMESUMM) {
						// 平日（月〜金）
						if (isset($D_YTC_TIMECOL_WD_FR) && isset($D_YTC_TIMECOL_WD_TO)) {
							// 開始時刻
							if (isset($D_YTC_TIMECOL_WD_FR[$key_name])) {
								if (isset($det_value)) {
									$ytc_time_wd[$D_YTC_TIMECOL_WD_FR[$key_name]][0] = $det_value;
								} else {
									$ytc_time_wd[$D_YTC_TIMECOL_WD_FR[$key_name]][0] = "0000";
								}
							}
							// 終了時刻
							if (isset($D_YTC_TIMECOL_WD_TO[$key_name])) {
								if (isset($det_value)) {
									$ytc_time_wd[$D_YTC_TIMECOL_WD_TO[$key_name]][1] = $det_value;
								} else {
									$ytc_time_wd[$D_YTC_TIMECOL_WD_TO[$key_name]][1] = "0000";
								}
							}
						}
						// その他（土、日、祝）
						if (isset($D_YTC_TIMECOL_OT_FR) && isset($D_YTC_TIMECOL_OT_TO)) {
							// 開始時刻
							if (isset($D_YTC_TIMECOL_OT_FR[$key_name])) {
								if (isset($det_value)) {
									$ytc_time_oh[$D_YTC_TIMECOL_OT_FR[$key_name]][0] = $det_value;
								} else {
									$ytc_time_oh[$D_YTC_TIMECOL_OT_FR[$key_name]][0] = "0000";
								}
							}
							// 終了時刻
							if (isset($D_YTC_TIMECOL_OT_TO[$key_name])) {
								if (isset($det_value)) {
									$ytc_time_oh[$D_YTC_TIMECOL_OT_TO[$key_name]][1] = $det_value;
								} else {
									$ytc_time_oh[$D_YTC_TIMECOL_OT_TO[$key_name]][1] = "0000";
								}
							}
						}
					}
					//---------------------------------------------
					// ヤマト運輸向け：定休日情報をサマリ
					//---------------------------------------------
					// 月〜祝
					if (isset($D_YTC_HLDYCOL_DAY_LBL)) {
						if (isset($D_YTC_HLDYCOL_DAY_LBL[$key_name]) && $det_value == '1') {
							$ytc_hldy_lbl[] = $D_YTC_HLDYCOL_DAY_LBL[$key_name];
						}
					}
					// 不定休、年中無休
					if (isset($D_YTC_HLDYCOL_OTH_LBL)) {
						if (isset($D_YTC_HLDYCOL_OTH_LBL[$key_name]) && $det_value == '1') {
							$ytc_hldy_oth_lbl = $D_YTC_HLDYCOL_OTH_LBL[$key_name];
						}
					}
					// add 2013/07/31 H.Osamoto ]
				}
			}
			// add 2015/12/10 Y.Uesugi [
			$dval =  mb_convert_encoding($rec[$key+5],"eucJP-win","eucJP-win,ASCII,JIS,UTF-8,SJIS-win");
			if($dval != ""){
				//---------------------------------------------
				// ヤマト運輸向け：平日営業日情報をサマリ
				//---------------------------------------------
				// 月〜金
				if (isset($D_YTC_WKDYCOL_DAY_LBL)) {
					if (isset($D_YTC_WKDYCOL_DAY_LBL[$key_name]) && $dval != '1') {
						$ytc_wkdy_lbl[] = $D_YTC_WKDYCOL_DAY_LBL[$key_name];
					}
				}
			}
			// add 2015/12/10 Y.Uesugi ]
		}

		//拠点縮尺		add 2009/08/27 Y.Matsukawa
		$key++;
		// mod 2015/05/22 H.Osamoto [
		//	if (ctype_digit($rec[$key+5]) && 1 <= $rec[$key+5] && $rec[$key+5] <= 9) {
		//		$ret_array['LVL'] = $rec[$key+5];
		//	}
		if (preg_match('/^@@KYOTEN_LEVEL@@:/', $rec[$key+5])) {
			$wk_lvl = explode(":", $rec[$key+5]);
			$kyoten_lvl = $wk_lvl[1];
			if (ctype_digit($kyoten_lvl) && 1 <= $kyoten_lvl && $kyoten_lvl <= 9) {
				$ret_array['LVL'] = $kyoten_lvl;
			}
		}
		// mod 2015/05/22 H.Osamoto ]
		
		//JCNカスタマイズ		add 2012/11/19 Y.Matsukawa
		if (isset($D_KYOTENID_CUST) && $D_KYOTENID_CUST == 'JCN') {
			$key++;
			if (isset($rec[$key+5]) && $rec[$key+5] != '') {
				$ret_array['@JCN_SPOT_STATUS@'] = $rec[$key+5];
			}
			$key++;
			if (isset($rec[$key+5]) && $rec[$key+5] != '') {
				$ret_array['@JCN_SPOT_AVL_COUNT@'] = $rec[$key+5];
			}
		}
		
		// 拠点（複数）画像	add 2013/07/12 Add T.Sasaki
		$key++;
		if (isset($rec[$key+5]) && $rec[$key+5] != '') {
			$arr_mlt_img_no = explode(",", $rec[$key+5]);
			if ( is_array( $arr_mlt_img_no ) && count( $arr_mlt_img_no ) ) {
				foreach ( $arr_mlt_img_no as $mlt_img_no) {
					// mlt_img_noからsetting.incの画像名を取得する
					$mlt_img_name = "";
					if ( is_array( $D_KYOTEN_IMG_DEF ) ) {
						foreach( $D_KYOTEN_IMG_DEF as $item ) {
							if ( $item["IMG_NO"] == $mlt_img_no ) {
								$mlt_img_name = $item["IMG_NAME"];
								break;
							}
						}
					}
					$ret_array["@MLTFLG$mlt_img_no@"] = "1";
					$ret_array["@MLTIMG$mlt_img_no@"] = sprintf("%s?cid=%s&kid=%s&no=%s", $D_SSAPI["img_select"], $D_DATA_CID , $id , $mlt_img_no );
					$ret_array["@MLTNAME$mlt_img_no@"] = $mlt_img_name;
				}
			}
		}
		// add 2016/09/30 N.Wada
		//---------------------------------------------
		// 任意カラム（時刻）同士の比較
		//---------------------------------------------
		if (isset($D_TIME_COMP_COLS)) {
			foreach($D_TIME_COMP_COLS as $g => $pair) {
				$col1 = $pair[0];
				$col2 = $pair[1];
				if ($ret_array['@'.$col1.'@'] == "" || $ret_array['@'.$col2.'@'] == "") continue;
				$val1 = (int)str_replace(":", "", $ret_array['@'.$col1.'@']);
				$val2 = (int)str_replace(":", "", $ret_array['@'.$col2.'@']);
				if ($val1 == $val2) {
					$ret_array['@'.$col1.'_EQ_'.$col2.'_TIME@'] = 1;
				} else {
					$ret_array['@'.$col1.'_NEQ_'.$col2.'_TIME@'] = 1;
				}
				if ($val1 >= $val2) {
					$ret_array['@'.$col1.'_GTE_'.$col2.'_TIME@'] = 1;
				} else {
					$ret_array['@'.$col1.'_LT_'.$col2.'_TIME@'] = 1;
				}
				if ($val1 <= $val2) {
					$ret_array['@'.$col1.'_LTE_'.$col2.'_TIME@'] = 1;
				} else {
					$ret_array['@'.$col1.'_GT_'.$col2.'_TIME@'] = 1;
				}
			}
		}

		// add 2016/06/13 Y.Matsukawa
		//---------------------------------------------
		// フラグ項目グループ判定（どれか１つ以上ON）
		//---------------------------------------------
		if (isset($D_FLAGS_ANY_ON)) {
			foreach($D_FLAGS_ANY_ON as $g => $flags) {
				foreach ($flags as $c) {
					if ($ret_array['@'.$c.'@']) {
						$ret_array['@FLAGS_'.$g.'_ANY_ON@'] = 1;
						break;
					}
				}
			}
		}
		// add 2016/10/25 N.Wada
		//---------------------------------------------
		// フラグ項目グループ判定（すべてON）
		//---------------------------------------------
		if (isset($D_FLAGS_ALL_ON)) {
			foreach($D_FLAGS_ALL_ON as $g => $flags) {
				$flag_on_cnt = 0;
				foreach ($flags as $c) {
					if ($ret_array['@'.$c.'@']) {
						$flag_on_cnt++;
					}
				}
				if ($flag_on_cnt && count($flags) == $flag_on_cnt) {
					$ret_array['@FLAGS_'.$g.'_ALL_ON@'] = 1;
				}
			}
		}
		// add 2016/10/06 N.Wada
		//---------------------------------------------
		// 値グループ判定（どれか１つ以上値がある）
		//---------------------------------------------
		if (isset($D_COLUMNS_ANY_VALUE)) {
			foreach($D_COLUMNS_ANY_VALUE as $g => $cols) {
				foreach ($cols as $c) {
					if ($ret_array['@'.$c.'@'] != "") {
						$ret_array['@COLUMNS_'.$g.'_ANY_VALUE@'] = 1;
						break;
					}
				}
			}
		}
		// add 2016/09/26 N.Wada
		//---------------------------------------------
		// 値グループ判定（どれか１つ以上、任意の値と一致する）
		//---------------------------------------------
		if (isset($D_COLUMNS_ANY_MATCH_VALUE)) {
			foreach($D_COLUMNS_ANY_MATCH_VALUE as $g => $cols) {
				foreach ($cols as $c => $v) {
					if ($ret_array['@'.$c.'@'] == $v) {
						$ret_array['@COLUMNS_'.$g.'_ANY_MATCH_VALUE@'] = 1;
						break;
					}
				}
			}
		}
		// add 2013/07/31 H.Osamoto [
		//---------------------------------------------
		// ヤマト運輸向け：営業時間情報をサマリ
		//---------------------------------------------
		if (isset($D_YTC_TIMESUMM) && $D_YTC_TIMESUMM) {
			$sum_time_str = array();
			// 平日（月〜金）サマリ
			if (count($ytc_time_wd)) {
				$wd_time_str = '';
				foreach ($ytc_time_wd as $wd=>$tm) {
					if ($tm[0] != '' && $tm[1] != '') {
						$tm[0] = substr($tm[0], 0, 2).':'.substr($tm[0], 2, 2);
						$tm[1] = substr($tm[1], 0, 2).':'.substr($tm[1], 2, 2);
						if ($tm[0] == '00:00' && $tm[1] == '24:00') {
							$time_str = $D_YTC_24_LBL;
						} else {
							$time_str = $tm[0].'　〜　'.$tm[1];
						}
						$sum_time_str[$time_str][] = $D_YTC_WD_LBL[$wd];
						if ($wd_time_str == '') $wd_time_str = $time_str;
						if ($wd_time_str != $time_str) {
							$wd_time_str = 'UNMATCH';
						}
					}
				}
				if ($wd_time_str != '' && $wd_time_str != 'UNMATCH') {
					// 平日（月〜金）が全て同じなら１つにまとめる
					$sum_time_str = array();// 曜日をセットしたものは消す
					$sum_time_str[$wd_time_str][] = '平日';
				}
			}
			// その他（土、日、祝）サマリ
			if (count($ytc_time_oh)) {
				foreach ($ytc_time_oh as $oh=>$tm) {
					if ($tm[0] != '' && $tm[1] != '') {
						$tm[0] = substr($tm[0], 0, 2).':'.substr($tm[0], 2, 2);
						$tm[1] = substr($tm[1], 0, 2).':'.substr($tm[1], 2, 2);
						if ($tm[0] == '00:00' && $tm[1] == '24:00') {
							$time_str = $D_YTC_24_LBL;
						} else {
							$time_str = $tm[0].'　〜　'.$tm[1];
						}
						$sum_time_str[$time_str][] = $D_YTC_OT_LBL[$oh];
					}
				}
			}
			// サマリ結果をテンプレートにセット
			if (count($sum_time_str)) {
				$ret_array["rowspan"] = count($sum_time_str) + 1;
				$tt = 0;
				foreach ($sum_time_str as $time_val => $arr_time_ttl) {
					if (count($sum_time_str) == 1) {
						$ret_array["timelist"][$tt]["title"] = $D_YTC_ALL_TITLE;//全日
					} else {
						$ret_array["timelist"][$tt]["title"] = implode('、', $arr_time_ttl);
					}
					$ret_array["timelist"][$tt]["value"] = $time_val;
					if ($tt == 0) $ret_array["timelist"][$tt]["row1"] = 1;
					$tt++;
				}
			}
		}
		//---------------------------------------------
		// ヤマト運輸向け：定休日情報をサマリ
		//---------------------------------------------
		// 月〜祝
		if ($ytc_hldy_oth_lbl != '') {
			$ret_array["@hldy@"] = $ytc_hldy_oth_lbl;
		} else if (count($ytc_hldy_lbl)) {
			$ret_array["@hldy@"] = implode('、', $ytc_hldy_lbl);
		}
		// add 2013/07/31 H.Osamoto ]
		
		// 公開開始、終了日、NEW表示開始、終了日	add 2012/01/30 K.Masuda [
		$reccnt = count($rec);
		for( $lc=4; $lc>0; $lc-- ){
			if( $lc == 4 ){ $date_colnm = "PUB_S_DATE_"; }
			else if( $lc == 3 ){ $date_colnm = "PUB_E_DATE_"; }
			else if( $lc == 2 ){ $date_colnm = "DISP_NEW_S_DATE_"; }
			else if( $lc == 1 ){ $date_colnm = "DISP_NEW_E_DATE_"; }
			if( $rec[$reccnt-$lc] != "" ){
				$ret_array["@".$date_colnm."YYYY@"] = substr($rec[$reccnt-$lc],0,4);	// 年
				$ret_array["@".$date_colnm."MM@"]   = mb_ereg_replace("^0", "", substr($rec[$reccnt-$lc],4,2));	// 月
				$ret_array["@".$date_colnm."DD@"]   = mb_ereg_replace("^0", "", substr($rec[$reccnt-$lc],6,2));	// 日
				$ret_array["@".$date_colnm."HH@"]   = mb_ereg_replace("^0", "", substr($rec[$reccnt-$lc],8,2));	// 時
			}
		}
		// add 2012/01/30 K.Masuda ]

		// add 2015/12/10 Y.Uesugi [
		//---------------------------------------------
		// ヤマト運輸向け：平日営業日情報をサマリ
		//---------------------------------------------
		// 月〜金
		if (count($ytc_wkdy_lbl)) {
			if (count($ytc_wkdy_lbl) != count($D_YTC_WKDYCOL_DAY_LBL)) {
				// 平日定休日が存在する場合のみ設定
				$ret_array["@wkdy@"] = implode('・', $ytc_wkdy_lbl);
			}
		}
		// add 2015/12/10 Y.Uesugi ]

		// add 2010/03/17 Y.Matsukawa [
		// iコンシェルオートGPSお知らせメモ連携
		//if ($carrier->G_AUTOGPS) {		mod 2013/09/02 Y.Matsukawa
		if ($carrier && $carrier->G_AUTOGPS) {
			if ($D_ICONCIE_REMIND && is_array($D_ICONCIE_REMIND_Q) && $D_ICONCIE_REMIND_Q['LOCATION'] && $D_ICONCIE_REMIND_Q['CONTENT']) {
				$remind_q = array();
				// 緯度
				$remind_q[] = $ret_array["@LAT@"];
				// 経度n
				$remind_q[] = $ret_array["@LON@"];
				// 測地系
				$remind_q[] = '1';
				// 場所名
				$remind_loc = $D_ICONCIE_REMIND_Q['LOCATION'];
				if (substr($remind_loc, 0, 4) == 'COL:') {
					$remind_loc = $ret_array['@'.substr($remind_loc, 4).'@'];
				}
				// mod 2011/07/05 Y.Nakajima [
				if (isset($D_Z2H_OPTION)) $remind_loc = ZdcConvZ2H($remind_loc, $D_Z2H_OPTION);
				$remind_loc = mb_convert_encoding($remind_loc, 'SJIS-win', 'eucJP-win');
				$remind_q[] = rawurlencode(mb_strimwidth($remind_loc, 0, 54, '', 'SJIS-win'));
				// mod 2011/07/05 Y.Nakajima ]
				
				// お知らせ内容
				$remind_cont = $D_ICONCIE_REMIND_Q['CONTENT'];
				if (substr($remind_cont, 0, 4) == 'COL:') {
					$remind_cont = $ret_array['@'.substr($remind_cont, 4).'@'];
				}
				if ($D_Z2H_OPTION) $remind_cont = ZdcConvZ2H($remind_cont, $D_Z2H_OPTION);
				// mod 2011/07/05 Y.Nakajima [
				$remind_cont = mb_convert_encoding($remind_cont, 'SJIS-win', 'eucJP-win');
				$remind_q[] = rawurlencode(mb_strimwidth($remind_cont, 0, 136, '', 'SJIS-win'));//※140だとオーバーすることがあるので少し小さくしてます
				// mod 2011/07/05 Y.Nakajima [
				// 開始日
				$remind_q[] = '';
				// 期間
				$remind_q[] = $D_ICONCIE_REMIND_Q['PERIOD'];
				// 時間帯
				$remind_q[] = $D_ICONCIE_REMIND_Q['TIME'];
				// 半径
				$remind_q[] = $D_ICONCIE_REMIND_Q['RAD'];
				// 戻り先リンク名
				// mod 2011/07/05 Y.Nakajima
				//$remind_q[] = rawurlencode(mb_convert_encoding($D_ICONCIE_REMIND_Q['OFFERLINK'], 'SJIS', 'EUC-JP'));
				$remind_q[] = rawurlencode(mb_convert_encoding($D_ICONCIE_REMIND_Q['OFFERLINK'], 'SJIS-win', 'eucJP-win'));
				// 戻り先URL
				//$remind_url = "http://".$_SERVER["HTTP_HOST"].$D_URL_BASE."d.htm?";		mod 2010/07/20 Y.Matsukawa
				$remind_url = "$protocol://".$_SERVER["HTTP_HOST"].$D_URL_BASE."d.htm?";
				switch ($D_ICONCIE_REMIND_Q['OFFERURL']) {
					case 'D':
						$remind_q[] = rawurlencode($remind_url."ksid=".$id);
						break;
					case 'M':
						$remind_q[] = rawurlencode($remind_url."kid=".$id);
						break;
					default:
						$remind_q[] = '';
				}
				// URL作成
				$ret_array['@ICONCIE_REMIND_URL@'] = D_ICONCIE_REMIND_URL.implode("&", $remind_q);
				$ret_array['@ICONCIE_REMIND_EXP_URL@'] = D_ICONCIE_REMIND_EXP_URL;
			}
		}
		// add 2010/03/17 Y.Matsukawa ]
	}

	return $ret_array;
}

// add 2014/05/22 Y.Matsukawa
// ------------------------------------------------------------
// 商品マスタデータ取得
// ------------------------------------------------------------
function ZdcPrdSelect($pid) {
	global $D_LOG_CID, $D_CID, $D_DATA_CID, $D_SSAPI, $D_SSAPI_KEY;

	$cgi = $D_SSAPI['prd_select'];
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&pid=%s", $cgi, $D_SSAPI_KEY, $D_DATA_CID, $D_LOG_CID, $pid);
	$dat = ZdcHttpRead($url);
	$cnt = count($dat);
	if($cnt < 2) return false;//エラー
	$rec = explode("\t", $dat[1]);

	$ret_array = array();
	$ret_array['@PRD_ID@']  = $pid;
	$ret_array['@PRD_NAME@']  = $rec[1];

	return $ret_array;
}

//********************************************************************
//* アイコン緯度経度から中心座標と最適レベルを求める
//********************************************************************
function ZdcGetZoomLevel($mapw, $maph, $prm_lng, $prm_lat, &$cent_lng, &$cent_lat, &$level, $center=0){

	global $mode;
	global $D_MAXZOOM;
	global $D_MINZOOM;

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
		$now_cent_lng = ($maxlng + $minlng) / 2;
		$now_cent_lat = ($maxlat + $minlat) / 2;
	}

	$diff_lng = $maxlng - $minlng;
	$diff_lat = $maxlat - $minlat;

	// 地図範囲に入りきらない場合を考慮して最大ズームをあらかじめセット
	$level = $D_MINZOOM;

	// 全てのアイコンの中心（検索中心も含んでいるので、検索中心を除いたものにするのが正しい）
	$cent_lng = ($maxlng + $minlng) / 2;
	$cent_lat = ($maxlat + $minlat) / 2;

	// ルート探索モードの場合、旗なので左下が基準になるようにオフセットを調整
	if($mode == 5 || $mode == 6){
		$topoffset_px = 30;
		$botoffset_px = 2;
	} else {
		$topoffset_px = 15;
		$botoffset_px = 15;
	}

	// 最大のズームから検索
	for($i = $D_MAXZOOM ; $i >= $D_MINZOOM ;  $i--){
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
//* 地図取得エラー時の画像を表示
//********************************************************************
function ZdcMapErrorImage($ext) {
		$fp = fopen("img/maperr.".$ext,"r","1");
		if(!$fp) {
			return False;
		}
		while(!feof($fp)) {
			print fread($fp,1024);
		}
		fclose($fp);
		return True;
}

//********************************************************************
//* アイコン表示用の緯度経度を保持する
// MODE
// 1:通常のアイコン位置のみ保持（１番目のみ）
// 2:分布アイコン位置を保持（最大５箇所）
// 3:最寄駅分布アイコン位置を保持（２箇所）
// 4:最寄駅ルート始点・終点を保持（２箇所）
//********************************************************************
function ZdcMakePackLatLng(
	$prm_mode,
	$prm_icon_num,
	$prm_lati1, $prm_longi1, $prm_icon_1,
	$prm_lati2 = "", $prm_longi2 = "", $prm_icon_2 = "",
	$prm_lati3 = "", $prm_longi3 = "", $prm_icon_3 = "",
	$prm_lati4 = "", $prm_longi4 = "", $prm_icon_4 = "",
	$prm_lati5 = "", $prm_longi5 = "", $prm_icon_5 = "",
	// add 2016/06/01 Y.Matsukawa [
	$prm_lati6 = "", $prm_longi6 = "", $prm_icon_6 = "",
	$prm_lati7 = "", $prm_longi7 = "", $prm_icon_7 = "",
	$prm_lati8 = "", $prm_longi8 = "", $prm_icon_8 = "",
	$prm_lati9 = "", $prm_longi9 = "", $prm_icon_9 = "",
	$prm_lati10 = "", $prm_longi10 = "", $prm_icon_10 = ""
	// add 2016/06/01 Y.Matsukawa ]
){
	$pack = "";
	$wk   = "";
	// add 2011/07/05 Y.Nakajima 
	$ico  = "";

	for($i = 0 ; $i < $prm_icon_num ; $i++){
		$lat = "prm_lati".($i+1);
		$lat = sprintf("%09d", $$lat);
		$lng = "prm_longi".($i+1);
		$lng = sprintf("%09d", $$lng);
		for($j = 0 ; $j < 9 ; $j++){
			$wk .= substr($lat, $j, 1) . substr($lng, $j, 1);
		}
		$wk .= $ico;
	}
	$pos = 0;
	$out = "";
	for($i = 0 ; $i < $prm_icon_num ; $i++){
		for($j = 0 ; $j < 6 ; $j++ ){	// 緯度経度の9桁を足して以下の割る３バイトで６回
			$out .= sprintf("%02s", base_convert(substr($wk, $pos, 3),10,36));
			$pos += 3;
		}
		$ico = "prm_icon_".($i+1);
		$out .= (substr($$ico,0,1) == "@" ? $$ico : (strlen($$ico) < 6 ? "@".(substr($$ico."@@@@@@",0,5)) : sprintf("%06d",$$ico)));
	}
	return $prm_mode.$out;
}

//********************************************************************
//* アイコン表示用の緯度経度を復号する
//********************************************************************
function ZdcMakeUnPackLatLng(
	$prm_pack, 
	$prm_mode,
	$prm_icon_num,
	$prm_lati1, $prm_longi1, $prm_icon_1,
	$prm_lati2 = "", $prm_longi2 = "", $prm_icon_2 = "",
	$prm_lati3 = "", $prm_longi3 = "", $prm_icon_3 = "",
	$prm_lati4 = "", $prm_longi4 = "", $prm_icon_4 = "",
	$prm_lati5 = "", $prm_longi5 = "", $prm_icon_5 = "",
	// add 2016/06/01 Y.Matsukawa [
	$prm_lati6 = "", $prm_longi6 = "", $prm_icon_6 = "",
	$prm_lati7 = "", $prm_longi7 = "", $prm_icon_7 = "",
	$prm_lati8 = "", $prm_longi8 = "", $prm_icon_8 = "",
	$prm_lati9 = "", $prm_longi9 = "", $prm_icon_9 = "",
	$prm_lati10 = "", $prm_longi10 = "", $prm_icon_10 = ""
	// add 2016/06/01 Y.Matsukawa ]
){
	$pos = 0;
	$wk = "";
	
	$prm_mode = substr($prm_pack, 0, 1);
	$str = substr($prm_pack, 1, strlen($prm_pack)-1);

	for($i = 0 ; $i < strlen($str) / 18; $i++){
		for($j = 0 ; $j < 6 ; $j++ ){
			$wk .= sprintf("%03d", base_convert(substr($str, $pos, 2),36,10));
			$pos += 2;
		}
		$wk .= substr($str, $pos, 6);
		$pos += 6;
	}
	$pos = 0;
	$cnt = 0;

	for($i = 0 ; $i < (strlen($wk) / 24) ; $i++){
		$lat = "";
		$lng = "";
		$ico = "";
		for($j = 0 ; $j < 9 ; $j++){
			$lat .= substr($wk, $pos, 1); $pos++;
			$lng .= substr($wk, $pos, 1); $pos++;
		}
		$ico = substr($wk, $pos, 6); $pos += 6;
		$ret_lat = "prm_lati".($i+1);
		$ret_lng = "prm_longi".($i+1);
		$ret_ico = "prm_icon_".($i+1);
		$$ret_lat = $lat;
		$$ret_lng = $lng;
		$$ret_ico = $ico;
		$cnt++;
	}
	$prm_icon_num = $cnt;
	return true;
}

//********************************************************************
//* 緯度、経度、期限、レベルを暗号化する
//********************************************************************
function ZdcMakeMobileEnc($prm_lati, $prm_longi, $prm_level){
	// add 2011/07/05 Y.Nakajima [
	$chk = "";
	$out = "";
	$o   = "";
	$ico = "";
	// add 2011/07/05 Y.Nakajima ]
	$P = rand(1,8);
	$P_C = date("Ymd");
	$P_A = sprintf("%010d", $prm_lati);
	$P_B = sprintf("%010d", $prm_longi);
	$P_C = sprintf("%02d%08d", $prm_level, $P_C);
	
	if($P == 1 || $P == 5){
			$A = $P_A; $B = $P_B; $C = $P_C;
	} else if($P == 2 || $P == 6){
			$A = $P_B; $B = $P_A; $C = $P_C;
	} else if($P == 3 || $P == 7){
			$A = $P_C; $B = $P_B; $C = $P_A;
	} else if($P == 4 || $P == 8){
			$A = $P_C; $B = $P_A; $C = $P_B;
	}
	if($P == 5){ $A = strrev($A); }
	if($P == 6){ $B = strrev($B); }
	if($P == 7){ $C = strrev($C); }
	if($P == 8){ $A = strrev($A); $B = strrev($B);}
	for($i = 0; $i < 10 ; $i++){
			$wk = substr($A,$i,1) . substr($B,$i,1) . substr($C,$i,1);
			$chk += $wk;
			$out .= $wk;
	}
	$chk = ($chk%100);
	$pos = 0;
	for($i = 0; $i < 10 ; $i++){
			$o .= sprintf("%02s", base_convert(substr($out, $pos, 3),10,36));
			$pos += 3;
	}
	return $P.$o.$chk;
}

//********************************************************************
//* 緯度、経度、期限、レベルを復号化する
//********************************************************************
function ZdcMakeMobileDec($prm_enc, &$prm_lati, &$prm_longi, &$prm_level, &$prm_limit){
	$pos = 1;
	$b = "";
	for($i = 0 ; $i < 10; $i++){
			$b .= sprintf("%03d", base_convert(substr($prm_enc, $pos, 2),36,10));
			$pos += 2;
	}
	$pos = 0;
	$AA = "";
	$BB = "";
	$CC = "";
	$chk = 0;
	for($i = 0 ; $i < 10 ; $i++){
			$aa = substr($b, $pos  , 1);
			$bb = substr($b, $pos+1, 1);
			$cc = substr($b, $pos+2, 1);
			$chk += intval($aa.$bb.$cc);
			$AA .= $aa; $BB .= $bb; $CC .= $cc;
			$pos += 3;
	}
	if($chk%100 != substr($prm_enc,21)){
			return false;
	}
	$P = substr($prm_enc,0,1);

	if($P == 5){ $AA = strrev($AA); }
	if($P == 6){ $BB = strrev($BB); }
	if($P == 7){ $CC = strrev($CC); }
	if($P == 8){ $AA = strrev($AA); $BB = strrev($BB);}
	if($P == 1 || $P == 5){
			$P_AA = $AA; $P_BB = $BB; $P_CC = $CC;
	} else if($P == 2 || $P == 6){
			$P_AA = $BB; $P_BB = $AA; $P_CC = $CC;
	} else if($P == 3 || $P == 7){
			$P_AA = $CC; $P_BB = $BB; $P_CC = $AA;
	} else if($P == 4 || $P == 8){
			$P_AA = $BB; $P_BB = $CC; $P_CC = $AA;
	}
	$prm_level = substr($P_CC,0,2);
	$prm_limit = substr($P_CC,2);
	$prm_lati  = intval($P_AA);
	$prm_longi = intval($P_BB);
	return true;
}

// ------------------------------------------------------------
// 機種依存文字チェック
// (EUC-JP：第一水準、第二水準のみ許容)
// ------------------------------------------------------------
function IzonSearch( $str ) {

	// ３バイト文字（JIS X 212 補助漢字）が含まれていたらエラー
	// ※補助漢字がそのまま送信されてきた場合は、ここでフックされます
	// （IE以外のブラウザからの送信や、CSVファイルアップロード等）
	if (preg_match('/(\x8F[\xA1-\xFE][\xA1-\xFE])/', $str)) {
		return false;
	}

	// パーセントエンコードされた３バイト文字（JIS X 212 補助漢字）が含まれていたらエラー
	// ※IEなどから、補助漢字がエンコードされて送信されてきた場合は、ここでフックされます
	// （例）「&#28583;」「&AElig;」
	if (preg_match('/(&#[0-9]{1,};|&[a-zA-Z]{1,};)/', $str)) {
		return false;
	}

	// 半角カナを全角カナに変換（半角カナが混在していると、全角文字抜き出しに失敗するため） 2007/08/13 add Y.Matsukawa
	$w_str = mb_convert_kana($str, 'K');

	// 全角文字の抜き出し
	preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $w_str, $matchword );

	for ( $i=0; $i < count( $matchword[0] ) ; $i++) {
		if ( $matchword[0][$i] ) {
			// EUC-JP  第一水準、第二水準の文字チェック
			if ( ! preg_match( '/^(([\xA1-\xA8]|[\xB0-\xF4])[\xA1-\xFE])*$/', $matchword[0][$i]) ) {
				return false;
			}
		}
	}
	return true;
}

// add 2011/08/25 Y.Matsukawa
// ------------------------------------------------------------
// opt指定を無効化する検索かどうか判定
// ------------------------------------------------------------
function is_opt_null_srch($type) {
	global $D_OPT_NULL_SRCH;
	if (isset($D_OPT_NULL_SRCH) && is_array($D_OPT_NULL_SRCH) && count($D_OPT_NULL_SRCH)) {
		if (in_array($type, $D_OPT_NULL_SRCH)) return true;
	}
	return false;
}

// add 2012/02/14 Y.Matsukawa
// ------------------------------------------------------------
// 日時項目分割
// ------------------------------------------------------------
function splitDateTimeCol($col_name, $value, &$arr_val) {
	$YOUBI[0] = '日';
	$YOUBI[1] = '月';
	$YOUBI[2] = '火';
	$YOUBI[3] = '水';
	$YOUBI[4] = '木';
	$YOUBI[5] = '金';
	$YOUBI[6] = '土';

	$yyyy = substr($value, 0, 4);
	if ($yyyy != '' && is_numeric($yyyy)) {
		$arr_val[$col_name."_YYYY"] = $yyyy;
	}
	$mm = substr($value, 4, 2);
	if ($mm != '' && is_numeric($mm)) {
		$arr_val[$col_name."_MM"] = $mm;
		$arr_val[$col_name."_M"] = intval($mm);
	}
	$dd = substr($value, 6, 2);
	if ($dd != '' && is_numeric($dd)) {
		$arr_val[$col_name."_DD"] = $dd;
		$arr_val[$col_name."_D"] = intval($dd);
	}
	if ($yyyy != '' && is_numeric($yyyy) && $mm != '' && is_numeric($mm) && $dd != '' && is_numeric($dd)) {
		$tm = mktime(0, 0, 0, $mm, $dd, $yyyy);
		if ($tm) {
			$arr_val[$col_name."_DW"] = date('w', $tm);
			$arr_val[$col_name."_DWJP"] = $YOUBI[$arr_val[$col_name."_DW"]];
		}
	}
	$hh = substr($value, 8, 2);
	if ($hh != '' && is_numeric($hh)) {
		$arr_val[$col_name."_HH"] = $hh;
		$arr_val[$col_name."_H"] = intval($hh);
	}
	$nn = substr($value, 10, 2);
	if ($nn != '' && is_numeric($nn)) {
		$arr_val[$col_name."_NN"] = $nn;
		$arr_val[$col_name."_N"] = intval($nn);
	}
}

// add 2016/06/13 Y.Matsukawa
// ------------------------------------------------------------
// 日時項目分割
// ------------------------------------------------------------
function formatTimeCol($col_name, $value, &$arr_val) {
	if ($value == '') return '';
	list($h, $n, $s) = explode(':', $value);
	$arr_val['@'.$col_name.'_TIME'.'@'] = intval($h).':'.$n;
}

// add 2012/08/03 H.Osamoto
// ------------------------------------------------------------
// HTML表示用変換処理
// ------------------------------------------------------------
function zdcHtmlspecialchars_arr($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/_ENC@$/', $key)) {
			$obj[$key] = $val;
		} else if (preg_match('/^@NAME@$|^@ADDR@$/i', $key)) {
			$obj[$key] = zdcHtmlspecialchars_nameaddr($val);
		} else {
			$obj[$key] = zdcHtmlspecialchars_col($val);
		}
	}
	
	return $obj;
}

function zdcHtmlspecialchars($target, $col_name) {
	
	if (preg_match('/^NAME$|^ADDR$/i', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr($target);
	} else {
		$ret = zdcHtmlspecialchars_col($target);
	}
	
	return $ret;
}

function zdcHtmlspecialchars_nameaddr($target) {
	
	$ret = htmlreplace($target);
	
	return $ret;
}

function zdcHtmlspecialchars_col($target) {
	
	//$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// 許可タグリスト		mod 2016/06/15 Y.Matsukawa
	$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>', '<u>', '</u>', '<font ', '</font>', '<strong>', '</strong>');	// 許可タグリスト
	$arr_rep = array();
	$rep_cnt = 0;
	
	$target;
	
	foreach ($tag_list as $key => $tag) {
		$start = 0;
		$stop = 0;
		while(1) {
			if (strpos($target, '<', $start) === false) break;	// 「<」が存在しない場合は処理しない
			
			// 許可タグチェック
			$start = strpos(strtolower($target), strtolower($tag), $start);
			
			if ($start !== false) {
				// 許可タグが存在する場合
				$stop = strpos(strtolower($target), ">", $start);
				$rep_cnt++;
				
				// 置換対象を一時的に配列に格納
				$arr_rep[$rep_cnt] = substr($target, $start, $stop - $start + 1);
				
				// 変換しない許可タグを一時的に置換
				$target = substr($target, 0, $start) . "@REP" . $rep_cnt . "@" . substr($target, $stop + 1);
				
				// 2013/02/07 H.osamoto mod [
				//	// 開始位置をずらして続きを実行
				//	$start = $stop;
				// 都度リセットして再実行
				$start = 0;
				// 2013/02/07 H.osamoto mod ]
			} else {
				// 許可タグが存在しない場合
				// 次のタグチェック
				break;
			}
		}
	}
	
	$target = htmlreplace($target);
	
	// 変換しておいた許可タグを元に戻す
	for ($i = 1; $i <= $rep_cnt; $i++) {
		$target = str_replace("@REP".$i."@", $arr_rep[$i], $target);
	}
	
	return $target;
}

function htmlreplace($target) {
	// HTML表示用に置換
	$search  = array('&', '"', '\'', '\\', '<', '>');	// 置換対象
	$replace = array('&amp;', '&quot;', '&#039;', '&yen;', '&lt;', '&gt;');	// 置換後文字列
	
	$target = str_replace($search, $replace, $target);
	
	return $target;
}

// ------------------------------------------------------------
// リアルタイムデータ取得
// ------------------------------------------------------------
function ZdcSearchCgiRd($kid,$rd_grp,$rdtype=null){
	global $cid, $D_CID, $D_SSAPI, $D_SOCKET_TIMEOUT,$D_DATA_CID ;
	require_once('/home/emap/src/Jsphon/Decoder.php');

	//CGIへアクセス
	$cgi = $D_SSAPI["rd_store_id"];
	$url = sprintf("%s?cid=%s&kid=%s&grp=%s&intid=%s", $cgi,  $D_DATA_CID, $kid, $rd_grp,"@EMAPMB@");
//echo $url;
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$tpl ='';
	$i=0;
	//戻り値の解釈
	if ($dat != '') {
		// JSONデコード
		$json = new Jsphon_Decoder();
		$arr_data = $json->decode($dat[0]);
		if (!$arr_data || !is_array($arr_data)) return false;
		if ($arr_data['return_code'] != "y1100000") return false;
		foreach ($arr_data as $key1 => $arr1) {
			foreach ($arr1 as $key2 => $arr2) {
				foreach ($arr2 as $key3 => $arr3) {

							${$key3} =$arr3;
							if($key3 =='store_id'){
								if($rdtype){
									 $tpl[$i]['rd_'.$key3]=${$key3};
								}
							}

					foreach ($arr3 as $key4 => $arr4) {
						foreach ($arr4 as $key5 => $arr5) {
							${$key5} =$arr5;
							if($group_id){
								if($rdtype){
									 $tpl[$i]['rd_'.$group_id]=1;
								}else{
									 $tpl['rd_'.$group_id]=1;
								}
							}
							foreach ($arr5 as $key6 => $arr6) {
								foreach ($arr6 as $key7 => $arr7) {
									${$key7} =str_replace("\n","<br>",mb_convert_encoding($arr7,"EUC-JP","UTF-8"));
//									${$key7} =$arr7;
									if($type == "TEXT"){
										if($key7 == "text"){
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id] = ${$key7};
											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id] = ${$key7};
											}
										}
									}elseif($type == "FLAG"){
										if($key7 == "flag"){
											${$key7}=$arr7;
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id] = ${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id] = ${$key7};
											}	
										}elseif($key7 == "text") {
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};
											}
										}
									}elseif($type == "IMG"){
										if($key7 == "img_url"){
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id] =${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id] =${$key7};
											}
										}elseif($key7 == "img_w" || $key7 == "img_h"){
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};

											}
										}
									}
								}
							}
						}
					}
				}
				$i=$i+1;
			}
		}
	}
	return $tpl;
}

?>
