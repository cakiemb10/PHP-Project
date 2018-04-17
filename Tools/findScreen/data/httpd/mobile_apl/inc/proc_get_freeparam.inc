<?PHP
//==============================================================================
// 任意パラメータの取得
// ※proc_param_dec.incを使用している場合、必ずその後でincludeする
//
// 2009/06/29 Y.Matsukawa	新規作成
// 2010/02/19 Y.Matsukawa	規約画面に検索TOPへのリンクを表示
// 2010/02/23 Y.Matsukawa	任意パラメータをurlencodeしてテンプレートに渡す
// 2010/03/11 Y.Matsukawa	任意パラメータ２バイト文字対応
// 2010/08/23 Y.Matsukawa	カスタマイズ絞り込み検索（optcd）
// 2011/05/23 H.Osamoto		Myエリア機能追加
// 2011/05/23 K.Masuda		自由項目拡張（p_s,p_fを50に）
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/02/14 Y.Matsukawa	top2任意パラメータ引継ぎ
// 2012/03/04 K.Masuda		自由項目最大数を変数に改修
// 2013/03/01 H.Osamoto		神奈川電通緯度経度変換対応
// 2013/08/16 H.Osamoto		p_sパラメータに「0」が設定されていた場合に引き継がれない不具合対応
// 2016/02/24 H.Osamoto		セキュリティ対応（Cross-Site Scripting）
// 2016/03/29 Y.Matsukawa	optcd複数時の連結指定
// 2017/03/14 H.Yasunaga	日本郵便カスタマイズ
// 2017/04/19 Y.Koishi		日本郵便カスタマイズ
//==============================================================================
// add 2010/03/11 Y.Matsukawa [
//for ($i = 1; $i <= 50; $i++) {	mod 2012/03/04 K.Masuda
for ($i = 1; $i <= $D_P_S_MAX; $i++) {
	$parmnm = "p_s".$i;
	if (isset($$parmnm)) {		// add 2010/08/23 Y.Matsukawa
		$$parmnm = urldecode($$parmnm);
		// add 2011/05/23 H.Osamoto [
		// mod 2011/07/05 Y.Nakajima
		if (isset($D_MYAREA_USE) && $D_MYAREA_USE && ($parmnm == "p_s2" || $parmnm == "p_s3")) {
			$$parmnm = str_replace(" ", "+", $$parmnm);
		}
		// mod 2011/07/05 Y.Nakajima
		if (isset($D_MYAREA_USE) && $D_MYAREA_USE && isset($p) && $p == "ibf"){
			$$parmnm = urldecode($$parmnm);
		}
		// add 2011/05/23 H.Osamoto ]
		${$parmnm."_sjis"} = $$parmnm;
		$$parmnm = mb_convert_encoding($$parmnm, "EUC-JP", "SJIS,EUC-JP,ASCII,JIS,UTF-8");
	}
}
// add 2010/03/11 Y.Matsukawa ]
// add 2013/03/01 H.Osamoto [
if (isset($D_KANA_DEN) && $D_KANA_DEN) {
	$p_s1 = mb_ereg_replace('[^0-9\.]', '', $p_s1);
	$p_s2 = mb_ereg_replace('[^0-9\.]', '', $p_s2);
	cnv_ll2lldms($p_s1, $p_s2, $cnvdatum, $p_s1, $p_s2);
	$p_s1_sjis = $p_s1;
	$p_s2_sjis = $p_s2;
}
// add 2013/03/01 H.Osamoto ]
//--------------------------------------------
// 任意パラメータをテンプレートに引渡し
//--------------------------------------------
//$arr_htmfnm = array("a.htm","c.htm","cl2.htm","cl.htm","d.htm","e.htm","m.htm","mi.htm","n.htm","ne.htm","nm.htm","s.htm","z.htm");		mod 2010/02/19 Y.Matsukawa
$arr_htmfnm = array("a.htm","c.htm","cl2.htm","cl.htm","cp.htm","d.htm","e.htm","m.htm","mi.htm","n.htm","ne.htm","nm.htm","s.htm","z.htm");
foreach ($arr_htmfnm as $htmfnm) {
	$i = -1;		// add 2016/03/29 Y.Matsukawa
	//for($pcnt=1;$pcnt<=50;$pcnt++){	// mod 2012/03/04 K.Masuda
	for($pcnt=1;$pcnt<=$D_P_S_MAX;$pcnt++){
		//	if (isset(${'p_s'.$pcnt}) && ${'p_s'.$pcnt}) {	mod 2013/08/16 H.Osamoto
		if (isset(${'p_s'.$pcnt})) {
			$D_CAPTION[$htmfnm]["P_STRING_".$pcnt] = ${'p_s'.$pcnt};
			$D_CAPTION[$htmfnm]["P_STRING_".$pcnt."_ENC"] = urlencode(${'p_s'.$pcnt.'_sjis'});
			$D_CAPTION[$htmfnm]["P_STRING_".$pcnt."_HTML_SQ"] = htmlspecialchars(${'p_s'.$pcnt}, ENT_QUOTES);	// add 2016/02/24 H.Osamoto
			// add 2016/03/29 Y.Matsukawa [
			$i++;
			$D_CAPTION[$htmfnm]['freeparms'][$i]['name'] = 'p_s'.$pcnt;
			$D_CAPTION[$htmfnm]['freeparms'][$i]['val'] = ${'p_s'.$pcnt};
			// add 2016/03/29 Y.Matsukawa ]
		}
	}
	//for($pcnt=1;$pcnt<=50;$pcnt++){	// mod 2012/03/04 K.Masuda
	for($pcnt=1;$pcnt<=$D_P_F_MAX;$pcnt++){
		if (isset(${'p_f'.$pcnt}) && ${'p_f'.$pcnt}) {
			$D_CAPTION[$htmfnm]["P_FLG_".$pcnt] = ${'p_f'.$pcnt};
			// add 2016/03/29 Y.Matsukawa [
			$i++;
			$D_CAPTION[$htmfnm]['freeparms'][$i]['name'] = 'p_f'.$pcnt;
			$D_CAPTION[$htmfnm]['freeparms'][$i]['val'] = ${'p_f'.$pcnt};
			// add 2016/03/29 Y.Matsukawa ]
		}
	}
	// mod 2011/05/23 K.Masuda ]
}
//--------------------------------------------
// 任意パラメータ引き回し用
//--------------------------------------------
$freeparms_enc = "";
// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
$freeparms_euc = "";
$freeparms_utf = "";
// add 2017/03/14 H.Yasunaga ]

//for($pcnt=1;$pcnt<=50;$pcnt++){	// mod 2012/03/04 K.Masuda
for($pcnt=1;$pcnt<=$D_P_S_MAX;$pcnt++){
	// mod 2011/07/05 Y.Nakajima
	//	if (isset(${'p_s'.$pcnt}) && ${'p_s'.$pcnt}) $freeparms_enc .= "p_s".$pcnt."=".urlencode(${'p_s'.$pcnt.'_sjis'})."&";	mod 2013/08/16 H.Osamoto
	if (isset(${'p_s'.$pcnt})) $freeparms_enc .= "p_s".$pcnt."=".urlencode(${'p_s'.$pcnt.'_sjis'})."&";
	// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
	if (isset(${'p_s'.$pcnt})) $freeparms_euc .= "p_s".$pcnt."=".urlencode(mb_convert_encoding(${'p_s'.$pcnt.'_sjis'}, "EUC-JP", "UTF8, EUC-JP,SJIS" ))."&";
	if (isset(${'p_s'.$pcnt})) $freeparms_utf .= "p_s".$pcnt."=".urlencode(mb_convert_encoding(${'p_s'.$pcnt.'_sjis'}, "UTF8", "UTF8, EUC-JP,SJIS" ))."&";
	// add 2017/03/14 H.Yasunaga ]
}
//for($pcnt=1;$pcnt<=50;$pcnt++){	// mod 2012/03/04 K.Masuda
for($pcnt=1;$pcnt<=$D_P_F_MAX;$pcnt++){
	// mod 2011/07/05 Y.Nakajima
	if (isset(${'p_f'.$pcnt}) && ${'p_f'.$pcnt}) $freeparms_enc .= "p_f".$pcnt."=".urlencode(${'p_f'.$pcnt})."&";
	// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
	if (isset(${'p_f'.$pcnt}) && ${'p_f'.$pcnt}) $freeparms_euc .= "p_f".$pcnt."=".urlencode(mb_convert_encoding(${'p_f'.$pcnt}, "EUC-JP", "UTF8,EUC-JP,SJIS"))."&";
	if (isset(${'p_f'.$pcnt}) && ${'p_f'.$pcnt}) $freeparms_utf .= "p_f".$pcnt."=".urlencode(mb_convert_encoding(${'p_f'.$pcnt}, "UTF8", "UTF8,EUC-JP,SJIS"))."&";
	// add 2017/03/14 H.Yasunaga ]
}
//// add 2010/05/12 Y.Matsukawa ]

// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
// mod 2017/04/19 Y.Koishi 日本郵便カスタマイズ [
//if ($cid == 'jppost15' || $cid == 'jppost15test') {
if ($cid == 'jppost15' || $cid == 'jppost15test' || $cid == 'jppost17' || $cid == 'jppost17test') {
// mod 2017/04/19 Y.Koishi ]
	switch($body_cst['jp_param_enc']) {
		case "SJIS":{
			$freeparms_enc .= 'enc=SJIS&';
			break;
		}
		case "EUC":{
			$freeparms_enc = $freeparms_euc . 'enc=EUC&';
			break;
		}
		case "UTF8":{
			$freeparms_enc = $freeparms_utf . 'enc=UTF8&';
			break;
		}
	}
}

// add 2017/03/14 H.Yasunaga ]

// add 2011/05/23 H.Osamoto [
// mod 2011/07/05 Y.Nakajima
if (!isset($freeparms_enc_ibf)) $freeparms_enc_ibf = "";
if (!isset($freeparms_enc_ibf_KDDI)) $freeparms_enc_ibf_KDDI = "";
if (isset($D_MYAREA_USE) && $D_MYAREA_USE) {
	//for($pcnt=1;$pcnt<=50;$pcnt++){	mod 2012/03/04 K.Masuda
	for($pcnt=1;$pcnt<=$D_P_S_MAX;$pcnt++){
		// mod 2011/07/05 Y.Nakajima [
		//if (isset(${p_s.$pcnt})) {
			//$freeparms_enc_ibf .= "p_s".$pcnt."=".urlencode(urlencode(${p_s.$pcnt._sjis}))."&";
			//$freeparms_enc_ibf_KDDI .= "p_s".$pcnt."=".urlencode(urlencode(urlencode(${p_s.$pcnt._sjis})))."&";
		if (isset(${'p_s'.$pcnt})) {
			$freeparms_enc_ibf .= "p_s".$pcnt."=".urlencode(urlencode(${'p_s'.$pcnt.'_sjis'}))."&";
			$freeparms_enc_ibf_KDDI .= "p_s".$pcnt."=".urlencode(urlencode(urlencode(${'p_s'.$pcnt.'_sjis'})))."&";
		// mod 2011/07/05 Y.Nakajima ]
		}
	}
}
// add 2011/05/23 H.Osamoto ]

// add 2010/08/23 Y.Matsukawa
//--------------------------------------------
// カスタマイズ絞り込み条件
//--------------------------------------------
$optcd_where = '';
// mod 2011/07/05 Y.Nakajima
if (isset($optcd) && $optcd != '' && isset($D_OPTCD_DEF) && $D_OPTCD_DEF) {
	$arr_optcd = explode('@', $optcd);
	for ($i = 0; $i < count($arr_optcd); $i++) {
		$w_whe = $D_OPTCD_DEF[$arr_optcd[$i]];
		if ($w_whe) {
			//if (isset($optcd_where) && $optcd_where != "") $optcd_where .= ' OR ';		mod 2016/03/29 Y.Matsukawa
			if (isset($optcd_where) && $optcd_where != "") $optcd_where .= " $D_OPTCD_U_COND ";
			$optcd_where .= $w_whe;
		}
	}
}

?>
