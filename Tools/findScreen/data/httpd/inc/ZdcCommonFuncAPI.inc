<?PHP
/*********************************************************************
// 更新履歴：
// 2009/12/25 Y.Matsukawa	新規作成（apiwebからコピー）
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2013/04/10 Y.Matsukawa	共通エラーログファイル名ローテート
// 2013/04/23 H.osamoto		ZdcHttpRead, ZdcHttpSimpleReadにリトライ処理追加
**********************************************************************/

// 測地系
define("DATUM_WGS84", "WGS84");
define("DATUM_TOKYO", "TOKYO");

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
	// 2007/05/28 mod matsukawa
	//	$eleLat = explode("/", cnv_dms2deg($ido_i));
	//	$eleLon = explode("/", cnv_dms2deg($kdo_i));
	$eleLat = explode("/", cnv_dms2deg($ido_i, "/"));
	$eleLon = explode("/", cnv_dms2deg($kdo_i, "/"));

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
// ミリ秒 -> 度分秒（XX.XX.XX.XXX 又は XX/XX/XX.XXX）
//********************************************************************
//function cnv_dms2deg($msec) {		2007/05/28 mod matsukawa
function cnv_dms2deg($msec, $sep = ".") {
	$p_lttd = $msec;

	$d = floor($p_lttd / 3600000);
	$p_lttd -= $d * 3600000;
	$m = floor($p_lttd / 60000);
	$p_lttd -= $m * 60000;
	$ms = $p_lttd;

	//$p_dms = $d . "/" . $m . "/" . $ms / 1000;	2007/05/28 mod matsukawa
	$p_dms = $d . $sep . $m . $sep . $ms / 1000;

	//1000で割り切れた場合
	$p_lttd -= floor($ms / 1000) * 1000;
	if( $p_lttd == 0 ){
		//$p_dms = $p_dms . "/0";		2007/05/28 mod matsukawa
		$p_dms = $p_dms . ".0";
	}

	return $p_dms;
}

//********************************************************************
// ミリ秒 -> 度
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
	//if($type == DATUM_WGS84){
	if($type === DATUM_WGS84){
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
		if($type == DATUM_WGS84){
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
//* $prm : lati or longi ( MS / XX.XX.XX.XXX / XX[.XXXXX] )
//* &$ms : lati or longi ( MS )
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:true 異常:false
//********************************************************************
function cnv_auto2dms($prm, &$ms){
	// add 2010/01/08 Y.Matsukawa [
	// +符号を除去
	$prm = str_replace('+', '', $prm);
	// -符号付きはエラー
	if (strpos($prm, '-') !== false) return false;
	// add 2010/01/08 Y.Matsukawa ]
	// 小数点区切り度分秒
	// mod 2011/07/05 Y.Nakajima
	//if(ereg("^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$", $prm, $ret)){
	if(preg_match("/^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$ms = ceil($ret[1]*3600000 + $ret[2]*60*1000 + $ret[3]*1000);
		return true;
	// 小数点区切り度(XXX.XXXX)
	// mod 2011/07/05 Y.Nakajima
	//} if(ereg("^([0-9]{2,3}\.[0-9]{1,})$", $prm, $ret)){
	} if(preg_match("/^([0-9]{2,3}\.[0-9]{1,})$/", $prm, $ret)){
		$ms = round($ret[1] * 3600 * 1000);
		return true;
	// 小数点区切り度(XXX)  2007/09/14 この形式に対応
	// mod 2011/07/05 Y.Nakajima
	//} if(ereg("^([0-9]{2,3})$", $prm, $ret)){
	} if(preg_match("/^([0-9]{2,3})$/", $prm, $ret)){
		$ms = round($ret[1] * 3600 * 1000);
		return true;
	// ミリ秒
	// mod 2011/07/05 Y.Nakajima
	//} if(ereg("^[0-9]{8,9}$", $prm, $ret)){
	} if(preg_match("/^[0-9]{8,9}$/", $prm, $ret)){
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
function ZdcHttpRead($url, $binary = 0, $timeout = ""){
	global $D_SOCKET_TIMEOUT;
	// 2013/04/23 add H.Osamoto [
	global $D_PUBDB_RETRY_COUNT;
	if (!$D_PUBDB_RETRY_COUNT) $D_PUBDB_RETRY_COUNT = 0;
	// 2013/04/23 add H.Osamoto ]

	$url_array = parse_url($url);
	$socket_timeout = ($timeout != "" ? $timeout : 30);

	// 2013/04/23 add H.Osamoto [
	$retry = 0;
	while ($retry <= $D_PUBDB_RETRY_COUNT) {
	// 2013/04/23 add H.Osamoto ]

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

				// 2013/04/23 add H.Osamoto [
				// DBエラーの場合はリトライ
				if (substr($ret[0],3,2) == "17" && $retry < $D_PUBDB_RETRY_COUNT) {
				} else {
				// 2013/04/23 add H.Osamoto ]
					$dat = Array();
					for($i = 0;$i < count($ret); $i++) {
						if(!trim($ret[$i])) break;
						$dat[$i] = $ret[$i];
					}
					return $dat;
				// 2013/04/23 add H.Osamoto [
				}
				// 2013/04/23 add H.Osamoto ]
			}
		} else {
			ZdcCommonErrorLog("BODY SEPARATOR IS NOT FOUND....");
			return false;
		}
	// 2013/04/23 add H.Osamoto [
		$retry++;
		if ($retry <= $D_PUBDB_RETRY_COUNT) {
			ZdcCommonErrorLog("RETRY[$retry] ZdcHttpRead() DB ERROR STATUS[".trim($ret[0])."] URL[$url]");
		} else {
			ZdcCommonErrorLog("RETRY FAILED ZdcHttpRead() DB ERROR STATUS[".trim($ret[0])."] URL[$url]");
		}
	}
	// 2013/04/23 add H.Osamoto ]
}

//********************************************************************
//* 文字列判定(記号)
//********************************************************************
function zdc_ctype_kigou( $string ){
	return	( preg_match( '/[\!-\/\:-\@\[-\`\{-\~]/',$string ) ) ? true : false;
}

//********************************************************************
//* エラーログ情報出力
//********************************************************************
function ZdcCommonErrorLog($str){
	//error_log(date("Y/m/d H:i:s")." ".$_SERVER["SCRIPT_NAME"]." ERR ".$str."\n", 3, "/var/tmp/ZdcCommonError.log");		mod 2013/04/10 Y.Matsukawa
	@error_log(date("Y/m/d H:i:s")." ".$_SERVER["SCRIPT_NAME"]." ERR ".$str."\n", 3, "/var/tmp/ZdcCommonError_".date("Ym").".log");
}
?>
