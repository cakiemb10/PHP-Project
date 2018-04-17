<?PHP
// 測地系変換種別( FUNCTION PARAMETER : type )
define("WGS84_TO_TKY", 0);
define("TKY_TO_WGS84", 1);
define("TKY_TO_TKY"  , 2);

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
// 度 -> ミリ秒
//********************************************************************
function cnv_hour2dms($d) {
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
	if(preg_match("/^E([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})N([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$lonms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
		$latms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
	// E139°45′56.14″N35°40′23.89″もしくは
	// E139°45′56.14″ N35°40′23.89″※Nの前にスペースがあるかないか（昔のＺか・・・）
	} else if(preg_match("/^E([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″[ ]*N([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″$/", $prm, $ret)){
		$lonms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
		$latms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
	// N139.45.56.14E35.40.23.89
	} else if(preg_match("/^N([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})E([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$lonms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
		$latms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
	// N35°40′23.89″E139°45′56.14″もしくは
	// N35°40′23.89″ E139°45′56.14″※Eの前にスペースがあるかないか（昔のＺか・・・）
	} else if(preg_match("/^N([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″[ ]*E([0-9]{2,3})°([0-9]{1,2})′([0-9]{1,2}\.[0-9]{1,3})″$/", $prm, $ret)){
		$lonms=($ret[4] * 3600 * 1000) + ($ret[5] * 60 * 1000) + $ret[6] * 1000;
		$latms=($ret[1] * 3600 * 1000) + ($ret[2] * 60 * 1000) + $ret[3] * 1000;
	} else {
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
	if(preg_match("/^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/", $prm, $ret)){
		$ms = ceil($ret[1]*3600000 + $ret[2]*60*1000 + $ret[3]*1000);
		return true;
	// 小数点区切り度
	} if(preg_match("/^([0-9]{2,3}\.[0-9]{1,})$/", $prm, $ret)){
		$ms = round($ret[1] * 3600 * 1000);
		return true;
	// ミリ秒
	} if(preg_match("/^[0-9]{8,9}$/", $prm, $ret)){
		$ms = $ret[0];
		return true;
	} else {
		$ms = 0;
		return false;
	}
}

//********************************************************************
//*
//* ストリーム内容を読み込んで返却する。（テキストバージョン）
//* ※汎用版
//*
//*-INPUT-------------------------------------------------------------
//* $utl     : "http://SERVER/CGI.HTM..."
//* $timeout : タイムアウトを設定したい場合の秒数（省略時：３０）
//*
//*-OUTPUT------------------------------------------------------------
//* retrun : 正常:コンテンツ内容 異常:false
//*
//********************************************************************
function ZdcHttpSimpleRead($url, $host = "") {
	if ($host) {
		$proxy = array(
			"http" => array(
				"proxy" => "tcp://$host",
				'request_fulluri' => true,
			),
		);
		$proxy_context = stream_context_create($proxy);
	} else {
		$proxy_context = null;
	}
	error_log(date("Y/m/d H:i:s")." ZdcHttpSimpleRead url[".$url."]\n", 3, "/var/tmp/debug_".date("Ymd").".log");
	return file_get_contents($url,false,$proxy_context);
}

?>
