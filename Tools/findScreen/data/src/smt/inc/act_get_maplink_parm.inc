<?PHP
//------------------------------------------
// 引き回しパラメータ
//
// 2011/09/02 Y.Matsukawa	Maplinkルート探索対応
// 2012/03/23 SKC			住所接続対応
// 2012/09/10 Y.Matsukawa	【不具合修正】任意パラメータに「&」を含めると正しく引き継がれない、任意パラメータに半角スペース指定すると消える
//------------------------------------------
// add 2011/09/02 Y.Matsukawa [
$maplink_prm = array();
$maplink_prm_all = '';
$maplink_point_prm = array();
$maplink_point_prm_all = '';
$maplink_ex_prm = array();
$maplink_ex_prm_all = '';
// add 2011/09/02 Y.Matsukawa ]
// add 2012/09/10 Y.Matsukawa [
$maplink_prm_enc = array();
$maplink_prm_enc_all = '';
$maplink_prm_enc_enc = array();
$maplink_prm_enc_enc_all = '';
// add 2012/09/10 Y.Matsukawa ]
//$MAPLINK_PARMS = array('lat','lon','datum','lv','icon','nm');
// add 2012/03/23 SKC [
$MAPLINK_PARMS = array('lat','lon','datum','lv','icon','nm','addr');
// add 2012/03/23 SKC ]
if ($args != '') {
	$arr_args = explode(',', $args);
	foreach ($arr_args as $i => $arg) {
		list($p, $v) = explode('=', $arg);
		if (in_array($p, $MAPLINK_PARMS) && $v != '') {
			$$p = $v;
		}
	}
}

if ($lat && $lon) {
	$cnvdatum = '';
	//  dbl("datum=$datum");
	if ($datum != '') {
		if (isset($D_PRM_DATNUM[$datum])) {
			$cnvdatum = $D_PRM_DATNUM[$datum];
			$datum = '';
		}
	} else {
		$cnvdatum = $D_PRM_DATNUM['TOKYO'];
	}
	//  dbl("$lat,$lon");
	//  dbl("cnvdatum=$cnvdatum");
	cnv_ll2lldms($lat, $lon, $cnvdatum, $lat, $lon);
	//  dbl("cnv_ll2lldms=>$lat,$lon");
}
if ($lat != '') {
	$tpl['lat'] = $lat;
	$tpl['html_lat'] = htmlspecialchars($lat);
	$maplink_prm[] = "lat=$lat";		// add 2011/09/02 Y.Matsukawa
	$maplink_point_prm[] = "lat=$lat";		// add 2011/09/02 Y.Matsukawa
	$maplink_prm_enc[] = "lat=$lat";		// add 2012/09/10 Y.Matsukawa
	$maplink_prm_enc_enc[] = "lat=$lat";	// add 2012/09/10 Y.Matsukawa
}
if ($lon != '') {
	$tpl['lon'] = $lon;
	$tpl['html_lon'] = htmlspecialchars($lon);
	$maplink_prm[] = "lon=$lon";		// add 2011/09/02 Y.Matsukawa
	$maplink_point_prm[] = "lon=$lon";		// add 2011/09/02 Y.Matsukawa
	$maplink_prm_enc[] = "lon=$lon";		// add 2012/09/10 Y.Matsukawa
	$maplink_prm_enc_enc[] = "lon=$lon";	// add 2012/09/10 Y.Matsukawa
}
$maplink_point_prm[] = 'datum=TOKYO';		// add 2011/09/02 Y.Matsukawa
if ($lv != '') {
	$tpl['lv'] = $lv;
	$tpl['html_lv'] = htmlspecialchars($lv);
	$maplink_prm[] = "lv=$lv";		// add 2011/09/02 Y.Matsukawa
	$maplink_ex_prm[] = "lv=$lv";		// add 2011/09/02 Y.Matsukawa
	$maplink_prm_enc[] = "lv=$lv";		// add 2012/09/10 Y.Matsukawa
	$maplink_prm_enc_enc[] = "lv=$lv";	// add 2012/09/10 Y.Matsukawa
}
if ($icn != '') {
	$tpl['icn'] = $icn;
	$tpl['html_icn'] = htmlspecialchars($icn);
	$maplink_prm[] = "icn=$icn";		// add 2011/09/02 Y.Matsukawa
	$maplink_ex_prm[] = "icn=$icn";			// add 2011/09/02 Y.Matsukawa
	$maplink_prm_enc[] = "icn=$icn";			// add 2012/09/10 Y.Matsukawa
	$maplink_prm_enc_enc[] = "icn=$icn";			// add 2012/09/10 Y.Matsukawa
}
if ($nm != '') {
dbl("nm=$nm");
	$tpl['nm'] = $nm;
	$tpl['html_nm'] = htmlspecialchars($nm);
	$tpl['enc_nm'] = urlencode($nm);		// add 2011/09/02 Y.Matsukawa
	$parm_nm .= 'enc_nm='.urlencode($nm);
	$maplink_prm[] = 'nm='.$nm;		// add 2011/09/02 Y.Matsukawa
	$maplink_ex_prm[] = 'nm='.urlencode($nm);		// add 2011/09/02 Y.Matsukawa
	$maplink_prm_enc[] = 'nm='.urlencode(mb_convert_encoding($nm, 'UTF-8', 'EUC-JP'));		// add 2012/09/10 Y.Matsukawa
	$maplink_prm_enc_enc[] = 'nm='.urlencode(mb_convert_encoding($nm, 'UTF-8', 'EUC-JP'));	// add 2012/09/10 Y.Matsukawa
}
// add 2012/03/23 SKC [
if ($addr != '') {
	$tpl['addr'] = $addr;
	$tpl['html_addr'] = htmlspecialchars($addr);
	$maplink_prm[] = "addr=$addr";
	$maplink_ex_prm[] = "addr=$addr";
	$maplink_prm_enc[] = 'addr='.urlencode(mb_convert_encoding($addr, 'UTF-8', 'EUC-JP'));		// add 2012/09/10 Y.Matsukawa
	$maplink_prm_enc_enc[] = 'addr='.urlencode(mb_convert_encoding($addr, 'UTF-8', 'EUC-JP'));	// add 2012/09/10 Y.Matsukawa
}
// add 2012/03/23 SKC ]

if (count($maplink_prm)) $maplink_prm_all = implode('&', $maplink_prm);		// add 2011/09/02 Y.Matsukawa
if (count($maplink_point_prm)) $maplink_point_prm_all = implode(',', $maplink_point_prm);		// add 2011/09/02 Y.Matsukawa
if (count($maplink_ex_prm)) $maplink_ex_prm_all = implode('&', $maplink_ex_prm);		// add 2011/09/02 Y.Matsukawa
if (count($maplink_prm_enc)) $maplink_prm_enc_all = implode('&', $maplink_prm_enc);		// add 2012/09/10 Y.Matsukawa
if (count($maplink_prm_enc_enc)) $maplink_prm_enc_enc_all = implode('&', $maplink_prm_enc_enc);		// add 2012/09/10 Y.Matsukawa

?>
