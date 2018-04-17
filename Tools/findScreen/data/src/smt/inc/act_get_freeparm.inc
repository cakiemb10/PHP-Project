<?PHP
// ------------------------------------------------------------
// 任意パラメータ
// 2012/01/11 Y.Matsukawa	新規作成
// 2012/01/24 Y.Matsukawa	任意パラメータを引き継がないモード
// 2012/02/23 Y.Matsukawa	店舗全件リスト画面
// 2012/03/04 K.Masuda		自由項目最大数を変数に改修、自由フラググループ化
// 2012/09/10 Y.Matsukawa	【不具合修正】任意パラメータに「&」を含めると正しく引き継がれない、任意パラメータに半角スペース指定すると消える
// 2013/03/01 H.Osamoto		神奈川電通緯度経度変換対応
// 2016/10/05 Y.Matsukawa	任意パラメータをurlエンコード
// 2017/03/14 H.Yasunaga	日本郵便カスタマイズ
// 2017/04/19 H.Yasunaga	日本郵便カスタマイズ
// ------------------------------------------------------------

//------------------------------------------
// 任意パラメータ
//------------------------------------------
$arr_freeparms = array();
$arr_freeparms_enc = array();
$arr_freeparms_enc_enc = array();		// add 2012/09/10 Y.Matsukawa

// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
$arr_freeparams_sjis = array();
$arr_freeparams_utf = array();
$arr_freeparams_euc = array();
// add 2017/03/14 H.Yasunaga ]

$freeparms = '';
$freeparms_enc = '';
$freeparms_enc_enc = '';		// add 2012/09/10 Y.Matsukawa

// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
$freeparams_sjis = '';
$freeparams_utf = '';
$freeparams_euc = '';
// add 2017/03/14 H.Yasunaga ]

$i = -1;
// add 2013/03/01 H.Osamoto [
if (isset($D_KANA_DEN) && $D_KANA_DEN) {
	$p_s1 = mb_ereg_replace('[^0-9\.]', '', $p_s1);
	$p_s2 = mb_ereg_replace('[^0-9\.]', '', $p_s2);
	cnv_ll2lldms($p_s1, $p_s2, "", $p_s1, $p_s2);
}
// add 2013/03/01 H.Osamoto ]
//for ($pno = 1; $pno <= 50; $pno++) {	// mod 2012/03/04 K.Masuda
for ($pno = 1; $pno <= $D_P_S_MAX; $pno++) {
	$parmnm = 'p_s'.$pno;
	if (isset($$parmnm) && $$parmnm != '') {
		$$parmnm = urldecode($$parmnm);
		${$parmnm.'_utf8'} = mb_convert_encoding($$parmnm, 'UTF-8', 'EUC-JP');
		$tpl['P_STRING_'.$pno] = $$parmnm;
		$tpl['P_STRING_'.$pno.'_ENC'] = urlencode($$parmnm);		// add 2016/10/05 Y.Matsukawa
		$tpl['P_STRING_'.$pno.'_HTML_SQ'] = htmlspecialchars($$parmnm, ENT_QUOTES);		// add 2015/09/06 Y.Matsukawa
		if (!$D_NOT_TRANSFER_FREEPARMS) {		// add 2012/01/24 Y.Matsukawa
			$arr_freeparms[] .= $parmnm.'='.$$parmnm;
			$arr_freeparms_enc[] .= $parmnm.'='.urlencode(${$parmnm.'_utf8'});
			$arr_freeparms_enc_enc[] .= $parmnm.'='.urlencode(urlencode(${$parmnm.'_utf8'}));		// add 2012/09/10 Y.Matsukawa
			// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
			$arr_freeparams_sjis[] .= $parmnm.'='.rawurlencode(mb_convert_encoding($$parmnm,'SJIS','UTF-8,EUC-JP,SJIS'));
			$arr_freeparams_utf[]  .= $parmnm.'='.rawurlencode(mb_convert_encoding($$parmnm,'UTF-8','UTF-8,EUC-JP,SJIS'));
			$arr_freeparams_euc[]  .= $parmnm.'='.rawurlencode(mb_convert_encoding($$parmnm,'EUC-JP','UTF-8,EUC-JP,SJIS'));
			// add 2017/03/14 H.Yasunaga ]
			$i++;
			$tpl['freeparms'][$i]['name'] = $parmnm;
			$tpl['freeparms'][$i]['val'] = $$parmnm;
		}
	}
// add 2012/03/04 K.Masuda [
}
for ($pno = 1; $pno <= $D_P_F_MAX; $pno++) {
// add 2012/03/04 K.Masuda ]
	$parmnm = 'p_f'.$pno;
	if (isset($$parmnm) && $$parmnm != '') {
		$tpl['P_FLG_'.$pno] = $$parmnm;
		$tpl['P_FLG_'.$pno.'_HTML_SQ'] = htmlspecialchars($$parmnm, ENT_QUOTES);		// add 2015/09/06 Y.Matsukawa
		if (!$D_NOT_TRANSFER_FREEPARMS) {		// add 2012/01/24 Y.Matsukawa
			$arr_freeparms[] .= $parmnm.'='.$$parmnm;
			$arr_freeparms_enc[] .= $parmnm.'='.$$parmnm;
			$arr_freeparms_enc_enc[] .= $parmnm.'='.$$parmnm;		// add 2012/09/10 Y.Matsukawa
			// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
			$arr_freeparams_sjis[] .= $parmnm.'='.rawurlencode(mb_convert_encoding($$parmnm,'SJIS','EUC-JP'));
			$arr_freeparams_utf[]  .= $parmnm.'='.rawurlencode(mb_convert_encoding($$parmnm,'UTF-8','EUC-JP'));
			$arr_freeparams_euc[]  .= $parmnm.'='.rawurlencode($$parmnm);
			// add 2017/03/14 H.Yasunaga ]
			$i++;
			$tpl['freeparms'][$i]['name'] = $parmnm;
			$tpl['freeparms'][$i]['val'] = $$parmnm;
		}
	}
}
if (count($arr_freeparms)) {
	$freeparms = implode('&', $arr_freeparms);
	$freeparms_enc = implode('&', $arr_freeparms_enc);
	$tpl['freeparms_enc'] = $freeparms_enc;		// add 2012/02/23 Y.Matsukawa
	// add 2012/09/10 Y.Matsukawa [
	$freeparms_enc_enc = implode('&', $arr_freeparms_enc_enc);
	$tpl['freeparms_enc_enc'] = $freeparms_enc_enc;
	// add 2012/09/10 Y.Matsukawa ]
}
// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
if (count($arr_freeparams_sjis)) $freeparams_sjis = implode('&', $arr_freeparams_sjis);
if (count($arr_freeparams_utf)) $freeparams_utf = implode('&', $arr_freeparams_utf);
if (count($arr_freeparams_euc)) $freeparams_euc = implode('&', $arr_freeparams_euc);
// mod 2017/04/19 H.Yasunaga 日本郵便カスタマイズ [
//if ($cid == 'jppost15' || $cid == 'jppost15test') {
if ($D_JPOST_CUSTOM_ENCODE) {
// mod 2017/04/19 H.Yasunaga ]
	if (strpos($script_name, ".htm") || $script_name == "search_area.js") {
		switch($tpl['jp_param_enc']) {
			case "SJIS": {
				$freeparms_enc = $freeparams_sjis . "&enc=SJIS";
				break;
			}
			case "EUC":{
				$freeparms_enc = $freeparams_euc . "&enc=EUC";
				break;
			}
			case "UTF8":{
				$freeparms_enc = $freeparams_utf . "&enc=UTF8";
				break;
			}
		}
	}
	// 詳細画面の表示用に拠点の情報をcgiでとるが、文字コード変換されてしまうので戻す
	if ($script_name == "shop_inf.htm") {
		$enc = "EUC";
	}
}
// add 2017/03/14 H.Yasunaga ]

// 2012/03/04 K.Masuda add [
if( isset($D_P_F_GRP) && is_array($D_P_F_GRP) && count($D_P_F_GRP) ){
	foreach($D_P_F_GRP as $g => $grp){
		$arr_grp = explode(",", $grp);
		foreach($arr_grp as $grp) {
			$GRP_TMP[$g][] = $grp;
		}
	}
	foreach( $GRP_TMP as $one_k => $one_v ){
		foreach( $one_v as $value ){
			if( !isset(${"p_f".$value}) || (${"p_f".$value} == "") ){
				$tpl["p_f_grp".$one_k] = NULL;
			} else {
				$tpl["p_f_grp".$one_k] = 1;
				break;
			}
		}
	}
}
// 2012/03/04 K.Masuda add ]
?>
