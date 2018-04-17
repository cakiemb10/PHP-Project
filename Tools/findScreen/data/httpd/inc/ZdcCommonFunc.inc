<?PHP

// 測地系変換種別( FUNCTION PARAMETER : type )
define("WGS84_TO_TKY", 0);
define("TKY_TO_WGS84", 1);
define("TKY_TO_TKY"  , 2);

/* Function List =====================================================
function cnv_transDatum($ido_i, $kdo_i, $type, &$ido_o, &$kdo_o)      測地系変換
function cnv_llh2xyz($b, $l, $h, $a, $e2)                             楕円体座標 -> 直交座標
function cnv_xyz2llh($x, $y, $z, $a, $e2)                             直交座標 -> 楕円体座標
function cnv_deg2dms($d)                                              度分秒 -> ミリ秒
function cnv_dms2deg($msec)                                           ミリ秒 -> 度分秒
function cnv_dms2hour($msec)                                          ミリ秒 -> 度
function cnv_ll2lldms($lat, $lon, $type, &$latms, &$lonms)            緯度経度チェック＆ミリ秒変換
function cnv_zill2lldms($prm, $type, &$latms, &$lonms)                緯度経度チェックのチェックを行いミリ秒形式で返却
function cnv_auto2dms($prm, &$ms)                                     緯度・経度のチェックを行いミリ秒形式で返却
function ZdcHttpRead($url, $binary = false, $timeout = "")            URLのコンテンツ内容を読み込む
function ZdcCommonErrorLog($str)                                      この関数内で発生したエラーログ出力
====================================================================*/
// ------------------------------------------------------------
// 開発履歴
// 2008/04/24 Y.Matsukawa	ZdcHttpRead DBエラー時にリトライ
// 2009/02/18 Y.Matsukawa	ZdcHttpRead 半角変換機能を追加
// 2009/02/25 Y.Matsukawa	ZdcHttpSimpleRead追加
// 2009/03/24 Y.Matsukawa	cnv_auto2dms：「+」付き緯度経度に対応
// 2010/08/03 Y.Matsukawa	緯度経度接続10進書式の場合、小数部4桁未満だとエラーになる
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/07/07 H.osamoto		cnv_dms2hourを追加
// 2012/11/13 Y.Matsukawa	ZdcHttpSimpleRead：port指定対応
// 2013/04/23 H.osamoto		ZdcHttpRead, ZdcHttpSimpleReadにリトライ処理追加
// 2016/03/10 Y.Matsukawa	zdc_json_decode
// 2016/03/31 F.Yokoi		ZdcHttpReadCoreIF, ZdcCoreIFResultName追加
// 2016/11/16 N.Wada		祝日判定
// ------------------------------------------------------------

//********************************************************************
// 測地系変換
//********************************************************************
function cnv_transDatum($ido_i, $kdo_i, $type, &$ido_o, &$kdo_o) {
	// データム諸元
	// (WGS 84)
	$a_w = 6378137;					// 赤道半径
	$f_w = 1 / 298.257223;			// 扁平率
	$e2_w = 2 * $f_w - $f_w * $f_w;	// 第1離心率
	// (Tokyo)
	$a_t = 6377397.155;
	$f_t = 1 / 299.152813;
	$e2_t = 2 * $f_t - $f_t * $f_t;
	// 並行移動量 [m]
	$dx_t = -148;
	$dy_t =  507;
	$dz_t =  681;

	// 緯度経度（ミリ秒）を度分秒に変換して配列に格納
	$eleLat = explode("/", cnv_dms2deg($ido_i));
	$eleLon = explode("/", cnv_dms2deg($kdo_i));

	$b = $eleLat[0] + $eleLat[1] / 60 + $eleLat[2] / 3600;
	$l = $eleLon[0] + $eleLon[1] / 60 + $eleLon[2] / 3600;

	// 測地系変換
	$h = 0;

	// WGS 84 -> Tokyo
	if ($type == WGS84_TO_TKY) {
		$pvec = cnv_llh2xyz($b, $l, $h, $a_w, $e2_w);
		$pvec = cnv_xyz2llh($pvec[0] - $dx_t, $pvec[1] - $dy_t, $pvec[2] - $dz_t, $a_t, $e2_t);

	// Tokyo -> WGS 84
	} else if ($type == TKY_TO_WGS84) {
		$pvec = cnv_llh2xyz($b, $l, $h, $a_t, $e2_t);
		$pvec = cnv_xyz2llh($pvec[0] + $dx_t, $pvec[1] + $dy_t, $pvec[2] + $dz_t, $a_w, $e2_w);
	} else {
		return false;
	}

	// 結果返却
	$ido_o = cnv_deg2dms($pvec[0]);
	$kdo_o = cnv_deg2dms($pvec[1]);

	return true;
}

//********************************************************************
// 楕円体座標 -> 直交座標
//********************************************************************
function cnv_llh2xyz($b, $l, $h, $a, $e2) {
	$rd = pi() / 180;
	$b *= $rd;
	$l *= $rd;
	$sb = sin($b);
	$cb = cos($b);
	$rn = $a / sqrt(1 - $e2 * $sb * $sb);

	$x = ($rn + $h) * $cb * cos($l);
	$y = ($rn + $h) * $cb * sin($l);
	$z = ($rn * (1 - $e2) + $h) * $sb;

	return array($x, $y, $z);
}

//********************************************************************
// 直交座標 -> 楕円体座標
//********************************************************************
function cnv_xyz2llh($x, $y, $z, $a, $e2) {
	$rd = pi() / 180;
	$bda = sqrt(1 - $e2);

	$p = sqrt($x * $x + $y * $y);
	$t = atan2($z, $p * $bda);
	$st = sin($t);
	$ct = cos($t);
	$b = atan2($z + $e2 * $a / $bda * $st * $st * $st, $p - $e2 * $a * $ct * $ct * $ct);
	$l = atan2($y, $x);

	$sb = sin($b);
	$rn = $a / sqrt(1 - $e2 * $sb * $sb);
	$h = $p / cos($b) - $rn;

	return array($b / $rd, $l / $rd, $h);
}

//********************************************************************
// 度分秒 -> ミリ秒
//********************************************************************
function cnv_deg2dms($d) {
	$p_ms = round($d * 3600000);
	return $p_ms;
}

//********************************************************************
// ミリ秒 -> 度分秒
//********************************************************************
function cnv_dms2deg($msec) {
	$p_lttd = $msec;

	$d = floor($p_lttd / 3600000);
	$p_lttd -= $d * 3600000;
	$m = floor($p_lttd / 60000);
	$p_lttd -= $m * 60000;
	$ms = $p_lttd;

	$p_dms = $d . "/" . $m . "/" . $ms / 1000;

	//1000で割り切れた場合
	$p_lttd -= floor($ms / 1000) * 1000;
	if( $p_lttd == 0 ){
		$p_dms = $p_dms . "/0";
	}

	return $p_dms;
}

//********************************************************************
// ミリ秒 -> 度		add 2011/07/07 H.osamoto
//********************************************************************
function cnv_dms2hour($msec) {
	$p = $msec / 3600 / 1000;
	$p = round($p * 10000000)/10000000;
	return $p;
}

//********************************************************************
//* 緯度経度チェック＆ミリ秒変換
//*
//*-INPUT-------------------------------------------------------------
//*
//* $lat   : lati  ( MS / XX.XX.XX.XXX / XX.XXXXX )
//* $lon   : longi ( MS / XX.XX.XX.XXX / XX.XXXXX )
//* $type  : WGS84_TO_TKY or TKY_TO_WGS84  ※define
//* &latms : lati  ( MS )
//* &lonms : longi ( MS )
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:true 異常:false
//********************************************************************
function cnv_ll2lldms($lat, $lon, $type, &$latms, &$lonms){
	if(!cnv_auto2dms($lat,&$latms)) return false;
	if(!cnv_auto2dms($lon,&$lonms)) return false;
	//mod 2011/09/09 Y.Nakajima
	//文字列が違うのに通してしまうので===に
	if($type === WGS84_TO_TKY){
		cnv_transDatum($latms, $lonms, WGS84_TO_TKY, &$tkylatms, &$tkylonms);
		$latms = $tkylatms;
		$lonms = $tkylonms;
	}

	return true;
}

//********************************************************************
//* 緯度経度チェックのチェックを行いミリ秒形式で返却
//*
//*-INPUT-------------------------------------------------------------
//*
//* $prm   : Zi形式緯度経度
//* $type  : WGS84_TO_TKY or TKY_TO_WGS84  ※define
//* &latms : lati  ( MS )
//* &lonms : longi ( MS )
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:true 異常:false
//********************************************************************
function cnv_zill2lldms($prm, $type, &$latms, &$lonms){
	$prm = mb_convert_encoding($prm,"EUC-JP","ASCII,JIS,UTF-8,EUC-JP,SJIS");

	// E139.45.56.14N35.40.23.89
	// mod 2011/07/05 Y.Nakajima
	//if(ereg("^E([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})N([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$", $prm, $ret)){
	if(preg_match("/^E([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})N([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$lonms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
		$latms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
	// E139°45′56.14″N35°40′23.89″もしくは
	// E139°45′56.14″ N35°40′23.89″※Nの前にスペースがあるかないか（昔のＺか・・・）
	// mod 2011/07/05 Y.Nakajima
	//} else if(ereg("^E([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″[ ]*N([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″$", $prm, $ret)){
	} else if(preg_match("/^E([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″[ ]*N([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″$/", $prm, $ret)){
		$lonms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
		$latms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
	// N139.45.56.14E35.40.23.89
	// mod 2011/07/05 Y.Nakajima
	//} else if(ereg("^N([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})E([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$", $prm, $ret)){
	} else if(preg_match("/^N([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})E([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$lonms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
		$latms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
	// N35°40′23.89″E139°45′56.14″もしくは
	// N35°40′23.89″ E139°45′56.14″※Eの前にスペースがあるかないか（昔のＺか・・・）
	// mod 2011/07/05 Y.Nakajima
	//} else if(ereg("^N([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″[ ]*E([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″$", $prm, $ret)){
	} else if(preg_match("/^N([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″[ ]*E([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″$/", $prm, $ret)){
		$lonms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
		$latms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
	} else {
		ZdcCommonErrorLog("Zi LatLon Is Invalid [$prm]");
		return false;
	}
	if($latms != "" && $lonms != ""){
		if($type == WGS84_TO_TKY){
			cnv_transDatum($latms, $lonms, WGS84_TO_TKY, &$tkylatms, &$tkylonms);
			$latms = $tkylatms;
			$lonms = $tkylonms;
		}
		return true;
	}

	ZdcCommonErrorLog("Zi LatLon Is Not Convert [$prm]");

	return false;
}

//********************************************************************
//* 緯度・経度のチェックを行いミリ秒形式で返却
//*
//*-INPUT-------------------------------------------------------------
//*
//* $prm : lati or longi ( MS / XX.XX.XX.XXX / XX.XXXXX )
//* &$ms : lati or longi ( MS )
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:true 異常:false
//********************************************************************
function cnv_auto2dms($prm, &$ms){
	// add 2009/03/24 Y.Matsukawa [
	// +符号を除去
	$prm = str_replace('+', '', $prm);
	// -符号付きはエラー
	if (strpos($prm, '-') !== false) return false;
	// add 2009/03/24 Y.Matsukawa ]
	// 小数点区切り度分秒
	// mod 2011/07/05 Y.Nakajima 
	//if(ereg("^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$", $prm, $ret)){
	//if(preg_match("/^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){		mod 2015/03/25 Y.Matsukawa
	if(preg_match("/^([0-9]{1,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$ms = ceil($ret[1]*3600000 + $ret[2]*60*1000 + $ret[3]*1000);
		return true;
	// 小数点区切り度
	//} if(ereg("^([0-9]{2,3}\.[0-9]{4,})$", $prm, $ret)){		mod 2010/08/03 Y.Matsukawa
	// mod 2011/07/05 Y.Nakajima 
	//} if(ereg("^([0-9]{2,3}\.[0-9]{1,})$", $prm, $ret)){
	//} if(preg_match("/^([0-9]{2,3}\.[0-9]{1,})$/", $prm, $ret)){		mod 2015/03/25 Y.Matsukawa
	} if(preg_match("/^([0-9]{1,3}\.[0-9]{1,})$/", $prm, $ret)){
		$ms = round($ret[1] * 3600 * 1000);
		return true;
	// ミリ秒
	// mod 2011/07/05 Y.Nakajima 
	//} if(ereg("^[0-9]{8,9}$", $prm, $ret)){
	//} if(preg_match("/^[0-9]{8,9}$/", $prm, $ret)){		mod 2015/03/25 Y.Matsukawa
	} if(preg_match("/^[0-9]{1,9}$/", $prm, $ret)){
		$ms = $ret[0];
		return true;
	} else {
		$ms = 0;
		ZdcCommonErrorLog("LatLon Is Invalid [$prm]");
		return false;
	}
}

//********************************************************************
//*
//* ストリーム内容を読み込んで返却する。（テキストバージョン）
//* ※但し汎用的ではなく、SSAPI専用のため、一般的なものは取得不可
//*
//*-INPUT-------------------------------------------------------------
//*
//* $utl     : "http://SERVER/CGI.HTM..."
//* $binary  : 取得対象がバイナリの場合True （省略時：テキスト）
//* $timeout : タイムアウトを設定したい場合の秒数（省略時：３０もしくは$D_SOCKET_TIMEOUT値）
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:コンテンツ内容 異常:false
//*
//* ※バイナリの場合、BODY部をそのまま返却し、テキストの場合、
//* 　配列にて返却する（行単位）
//*
//********************************************************************
//function ZdcHttpRead($url, $binary = 0, $timeout = ""){		mod 2009/02/18 Y.Matsukawa
function ZdcHttpRead($url, $binary = 0, $timeout = "", $z2h = ""){
	global $D_SOCKET_TIMEOUT;
	// 2008/04/24 add Y.Matsukawa ↓
	global $D_PUBDB_RETRY_COUNT;
	if (!$D_PUBDB_RETRY_COUNT) $D_PUBDB_RETRY_COUNT = 0;
	// 2008/04/24 add Y.Matsukawa ↑

	$url_array = parse_url($url);
	$socket_timeout = ($timeout != "" ? $timeout : 30);

	// 2008/04/24 add Y.Matsukawa ↓
	$retry = 0;
	while ($retry <= $D_PUBDB_RETRY_COUNT) {
	// 2008/04/24 add Y.Matsukawa ↑

		// ソケット作成
		if(!$fp = @fsockopen($url_array["host"], "80", $errno, $errstr, $socket_timeout)){
			// mod 2013/04/23 H.Osamoto [
			//	ZdcCommonErrorLog("Socket Open Error URL[$url] ERRNO[$errno] ERRMSG[$errstr] TIMEOUT[$socket_timeout]");
			//	return false;
			$retry++;
			if ($retry <= $D_PUBDB_RETRY_COUNT) {
				ZdcCommonErrorLog("RETRY[$retry] ZdcHttpRead() Socket Open Error URL[$url] ERRNO[$errno] ERRMSG[$errstr] TIMEOUT[$socket_timeout]");
			} else {
				ZdcCommonErrorLog("RETRY FAILED ZdcHttpRead() Socket Open Error URL[$url] ERRNO[$errno] ERRMSG[$errstr] TIMEOUT[$socket_timeout]");
			}
			continue;
			// mod 2013/04/23 H.Osamoto ]
		}
		
		// 取得
		@fputs($fp, "GET $url HTTP/1.0\r\n\r\n");

		$line = "";
		$http_state = "";

		if($fp){
			while(!feof($fp)){
				// mod 2011/07/05 Y.Nakajima
				//$getline = @fgets($fp, 4000);
				$getline = @fread($fp, 4000);
				if(!$getline) break;
				if(!$http_state) $http_state = $getline;
				$line .= $getline;
			}
		}
		@fclose($fp);

		// mod 2011/07/05 Y.Nakajima
		//$ret = split(" ",$http_state);
		$ret = explode(" ",$http_state);
		if($ret[1] != "200"){
			// mod 2013/04/23 H.Osamoto [
			//	ZdcCommonErrorLog("SERVER ERROR STATUS[".trim($http_state)."] URL[$url]");
			//	return false;
			$retry++;
			if ($retry <= $D_PUBDB_RETRY_COUNT) {
				ZdcCommonErrorLog("RETRY[$retry] ZdcHttpRead() SERVER ERROR STATUS[".trim($ret[1])."] URL[$url]");
			} else {
				ZdcCommonErrorLog("RETRY FAILED ZdcHttpRead() SERVER ERROR STATUS[".trim($ret[1])."] URL[$url]");
			}
			continue;
			// mod 2013/04/23 H.Osamoto ]
		}

		// HTTPヘッダ以降を取得
	 	//2011.07.04 PHP5.3対応
		//$ret = split("\r\n\r\n",$line);
		$ret = explode("\r\n\r\n",$line);
		
		// 戻り値処理
		if(is_array($ret)){
			$out = "";
			
			// インデックスはHTTPヘッダ以降の１から始まるので注意
			$j = 0;
			for($i = 1 ; $i < count($ret) ; $i++){
				$out .= $ret[$i].($binary == true ? "" : "\n");
			}

			if($binary == true){
				return $out;
			} else { 
				// 取得したHTMLを出力
				// mod 2011/07/05 Y.Nakajima
				//\r\nを最初に指定しないと、それぞれで分割してしまい、空白データが作成され、そこで処理が終了してしまう
				//$ret = split("(\r|\r\n|\n)",$out);
				$ret = preg_split("/\r\n|\r|\n/",$out);    //もしくはこれ
				// DBエラーの場合はリトライ
				if (substr($ret[0],3,2) == "17" && $retry < $D_PUBDB_RETRY_COUNT) {
				} else {
					$dat = Array();
					for($i = 0;$i < count($ret); $i++) {
						if(!trim($ret[$i])) break;
						//$dat[$i] = $ret[$i];		mod 2009/02/18 Y.Matsukawa
						$dat[$i] = ZdcConvZ2H($ret[$i], $z2h);
					}
					return $dat;
				}
			}
		} else {
			ZdcCommonErrorLog("BODY SEPARATOR IS NOT FOUND....");
			return false;
		}

	// 2008/04/24 add Y.Matsukawa ↓
		$retry++;
		// add 2013/04/23 H.Osamoto [
		if ($retry <= $D_PUBDB_RETRY_COUNT) {
			ZdcCommonErrorLog("RETRY[$retry] ZdcHttpRead() DB ERROR STATUS[".trim($ret[0])."] URL[$url]");
		} else {
			ZdcCommonErrorLog("RETRY FAILED ZdcHttpRead() DB ERROR STATUS[".trim($ret[0])."] URL[$url]");
		}
		// add 2013/04/23 H.Osamoto ]
	}
	// 2008/04/24 add Y.Matsukawa ↑
}

// add 2009/02/25 Y.Matsukawa
//********************************************************************
//*
//* ストリーム内容を読み込んで返却する。（テキストバージョン）
//* ※汎用版
//*
//*-INPUT-------------------------------------------------------------
//*
//* $utl     : "http://SERVER/CGI.HTM..."
//* $binary  : 取得対象がバイナリの場合True （省略時：テキスト）
//* $timeout : タイムアウトを設定したい場合の秒数（省略時：３０もしくは$D_SOCKET_TIMEOUT値）
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:コンテンツ内容 異常:false
//*
//* ※バイナリの場合、BODY部をそのまま返却し、テキストの場合、
//* 　配列にて返却する（行単位）
//*
//********************************************************************
//function ZdcHttpSimpleRead($url, $host = "", $binary = 0, $timeout = "", $z2h = ""){		mod 2016/03/10 Y.Matsukawa
function ZdcHttpSimpleRead($url, $host = "", $binary = 0, $timeout = "", $z2h = "", $enc = ""){

	global $D_SOCKET_TIMEOUT;
	global $D_PUBDB_RETRY_COUNT;
	if (!$D_PUBDB_RETRY_COUNT) $D_PUBDB_RETRY_COUNT = 0;

	if (!$host) {
		$url_array = parse_url($url);
		$host = $url_array["host"];
	}
	// add 2012/11/13 Y.Matsukawa [
	list($host, $port) = explode(':', $host);
	if (!$port) $port = '80';
	// add 2012/11/13 Y.Matsukawa ]
	
	$socket_timeout = ($timeout != "" ? $timeout : 30);

	$retry = 0;
	while ($retry <= $D_PUBDB_RETRY_COUNT) {

		// ソケット作成
		//if(!$fp = @fsockopen($host, "80", $errno, $errstr, $socket_timeout)){		mod 2012/11/13 Y.Matsukawa
		if(!$fp = @fsockopen($host, $port, $errno, $errstr, $socket_timeout)){
			// mod 2013/04/23 H.Osamoto [
			//	ZdcCommonErrorLog("Socket Open Error URL[$url] ERRNO[$errno] ERRMSG[$errstr] TIMEOUT[$socket_timeout]");
			//	return false;
			$retry++;
			if ($retry <= $D_PUBDB_RETRY_COUNT) {
				ZdcCommonErrorLog("RETRY[$retry] ZdcHttpSimpleRead() Socket Open Error URL[$url] ERRNO[$errno] ERRMSG[$errstr] TIMEOUT[$socket_timeout]");
			} else {
				ZdcCommonErrorLog("RETRY FAILED ZdcHttpSimpleRead() Socket Open Error URL[$url] ERRNO[$errno] ERRMSG[$errstr] TIMEOUT[$socket_timeout]");
			}
			continue;
			// mod 2013/04/23 H.Osamoto ]
		}
		
		// 取得
		@fputs($fp, "GET $url HTTP/1.0\r\n\r\n");

		$line = "";
		$http_state = "";

		if($fp){
			while(!feof($fp)){
				$getline = @fgets($fp, 4000);
				if(!$getline) break;
				if(!$http_state) $http_state = $getline;
				$line .= $getline;
			}
		}
		@fclose($fp);

	 	//2011.07.04 PHP5.3対応
		//$ret = split(" ",$http_state);
		$ret = explode(" ",$http_state);
		if($ret[1] != "200"){
			// mod 2013/04/23 H.Osamoto [
			//	ZdcCommonErrorLog("SERVER ERROR STATUS[".trim($http_state)."] URL[$url]");
			//	return false;
			$retry++;
			if ($retry <= $D_PUBDB_RETRY_COUNT) {
				ZdcCommonErrorLog("RETRY[$retry] ZdcHttpSimpleRead() SERVER ERROR STATUS[".trim($ret[1])."] URL[$url]");
			} else {
				ZdcCommonErrorLog("RETRY FAILED ZdcHttpSimpleRead() SERVER ERROR STATUS[".trim($ret[1])."] URL[$url]");
			}
			continue;
			// mod 2013/04/23 H.Osamoto ]
		}

		// HTTPヘッダ以降を取得
	 	//2011.07.04 PHP5.3対応
		//$ret = split("\r\n\r\n",$line);
		$ret = explode("\r\n\r\n",$line);
		
		// 戻り値処理
		if(is_array($ret)){
			$out = "";
			// インデックスはHTTPヘッダ以降の１から始まるので注意
			$j = 0;
			for($i = 1 ; $i < count($ret) ; $i++){
				$out .= $ret[$i].($binary == true ? "" : "\n");
			}
			if($binary == true){
				return $out;
			} else { 
				// 取得したHTMLを出力
			 	//2011.07.04 PHP5.3対応
				//$ret = split("(\r|\r\n|\n)",$out);
				$ret = explode("(\r|\r\n|\n)",$out);
				$dat = Array();
				for($i = 0;$i < count($ret); $i++) {
					if(!trim($ret[$i])) break;
					//if ($enc) $ret[$i] = mb_convert_encoding($ret[$i], "EUC-JP", $enc);		// add 2016/03/10 Y.Matsukawa
					$dat[$i] = ZdcConvZ2H($ret[$i], $z2h);
				}
				return $dat;
			}
		} else {
			ZdcCommonErrorLog("BODY SEPARATOR IS NOT FOUND....");
			return false;
		}

		$retry++;
	}
}

//********************************************************************
//* エラーログ情報出力
//********************************************************************
function ZdcCommonErrorLog($str){
	//error_log(date("Y/m/d H:i:s")." ".$_SERVER["SCRIPT_NAME"]." ERR ".$str."\n", 3, "/var/tmp/ZdcCommonError.log");		mod 2013/04/10 Y.Matsukawa
	@error_log(date("Y/m/d H:i:s")." ".$_SERVER["SCRIPT_NAME"]." ERR ".$str."\n", 3, "/var/tmp/ZdcCommonError_".date("Ym").".log");
}

//********************************************************************
//* 全角→半角コンバート
//   ・2009/02/16 Y.Matsukawa 新規作成
//********************************************************************
function ZdcConvZ2H($str, $option) {
	if (!strlen($option)) return $str;
	if (mb_ereg("[^a-z]", $option)) return $str;

	// mod 2011/07/05 Y.Nakajima 
	//if (ereg("m", $option)) {
	if (strpos($option, "m")) {
		$str = mb_ereg_replace('”', '&quot;', $str);
		//		$zmarks = '！”＃＄％＆’（）＊＋，−．／：；＜＝＞？＠［￥］＾＿｀｛｜｝〜';
		//		$hmarks = '!"#$%&\'()*+,-./:;<=>?@[\]^_`{|}~';
		$zmarks = '！＃＄％＆’（）＊＋，−．／：；＜＝＞？＠［￥］＾＿｀｛｜｝〜';
		$hmarks = '!#$%&\'()*+,-./:;<=>?@[\]^_`{|}~';
		for ($i = 0; $i < mb_strlen($zmarks); $i++) {
			$z = mb_substr($zmarks, $i, 1);
			$h = mb_substr($hmarks, $i, 1);
			$str = mb_ereg_replace($z, $h, $str);
		}
		$option = str_replace('m', '', $option);
	}
	
	
	return mb_convert_kana($str, $option);
}

//********************************************************************
//* ミリ秒→地図アプリ用フォーマット
//********************************************************************
function cnv_dms2chizuappdms($msec) {
	$p_dms = cnv_dms2deg($msec);
	$p_dms = str_replace('/', '.', $p_dms);
	$p_dms = '+'.$p_dms;
	return $p_dms;
}

// add 2016/03/10 Y.Matsukawa
function zdc_json_decode($json_string) {
	require_once('/home/emap/src/Jsphon/Decoder.php');
	$json = new Jsphon_Decoder();
	$arr_data = $json->decode($json_string);
	return $arr_data;
}

// add 2016/03/31 F.Yokoi
function ZdcHttpReadCoreIF($url) {
	$opts = array(
		'http'=>array('header' => 'Accept: application/json')
	);
	$context = stream_context_create($opts);
	$fp = @fopen($url, 'r', false, $context);
	$line = '';
	$http_state = '';
	if ($fp) {
		while (!feof($fp)) {
			$getline = @fgets($fp, 4000);
			if(!$getline) break;
			$line .= $getline;
		}
		fclose($fp);
		if ($line) {
			return zdc_json_decode($line, true);
		} else {
			return false;
		}
	} else {
		return false;
	}
}

// add 2016/03/31 F.Yokoi
function ZdcCoreIFResultName($item, $lang) {
	if (!$item) return '';
	$name = '';
	switch ($lang) {
		case 'ja':
			$name = $item['poi']['text'];
			break;
		case 'cn':
		case 'tw':
			$name = $item['poi']['language']['zh-'.$lang]['text'];
			break;
		default:
			$name = $item['poi']['language'][$lang]['text'];
			break;
	}
	return $name;
}

// add 2016/11/16 N.Wada
//********************************************************************
//*
//* 祝日判定（祝日マスタから取得）
//*
//*-INPUT-------------------------------------------------------------
//* $ymd     : YYYYMMDD形式の日付（例：2016/09/01）（省略時：今日の日付）
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 祝日:true not祝日:false
//*
//* ※データ管理ツールで祝日マスタ編集
//*
//********************************************************************
function ZdcIsHoliday($ymd) {
	global $D_SSAPI;
	global $D_CID;

	$cgi = $D_SSAPI["get_holiday"]."?cid=".$D_CID;
	if ($ymd) {
		$cgi .= "&ymd=".$ymd;
	}
	$dat = ZdcHttpRead($cgi);

	if ($dat[1] == "1") {
		return true;
	} else {
		return false;
	}
}

?>
