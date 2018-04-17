<?PHP
//------------------------------------------
// 引き継ぎパラメータ
//
// 2011/10/15 Y.Matsukawa	新規作成
// 2011/12/13 Y.Matsukawa	戻るリンクURL
// 2012/02/09 Y.Matsukawa	区分項目絞り込み条件不具合修正
// 2012/02/29 Y.Matsukawa	任意パラメータをテンプレートに渡す
// 2012/04/02 K.Masuda		縮尺レベルをテンプレートに渡す
// 2012/09/20 Y.Matsukawa	テンプレートからTOP画面URL（パラメータ付き）を参照
// 2012/10/01 Y.Matsukawa	Maplink対応
// 2013/02/05 K.Masuda		cond条件を括れるように改修
// 2013/09/24 Y.Matsukawa	P_STRINGのhtmlエスケープ文字列
// 2013/11/28 Y.Matsukawa	セキュリティ対応（XSS）
// 2014/12/11 Y.Matsukawa	パンくず生成を別ファイル化（act_make_history.inc）
// 2015/03/30 H.Osamoto		テキスト項目の引継ぎ追加
// 2015/05/14 Y.Matsukawa	condをnmap/shop_dtlに直接記述（cond.htm未使用）モード
// 2015/08/27 Y.Matsukawa	セキュリティ対応（Cross-Site Scripting）
// 2016/08/15 H.Yasunaga	日本郵便対応 p_f99(閲覧専用フラグ)をPC側でも実装するため
//							引継ぎパラメータ(p_fとp_s)の最大数をsmt側と合わせる
// 2017/03/14 H.Yasunaga	日本郵便カスタマイズ
// 2017/03/27 H.Yasunaga	日本郵便カスタマイズ 吹き出し表示の文字化け修正
// 2017/04/19 H.Yasunaga	日本郵便カスタマイズ
//------------------------------------------

// Maplinkパラメータ		add 2012/10/01 Y.Matsukawa
$MAPLINK_PARMS = array('lat','lon','datum','lv','icon','nm','addr');
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
	if ($datum != '') {
		if (isset($D_PRM_DATNUM[$datum])) {
			$cnvdatum = $D_PRM_DATNUM[$datum];
			$datum = '';
		}
	} else {
		$cnvdatum = $D_PRM_DATNUM['TOKYO'];
	}
	cnv_ll2lldms($lat, $lon, $cnvdatum, $lat, $lon);
}
if ($lat != '') {
	$tpl['lat'] = $lat;
	$tpl['html_lat'] = htmlspecialchars($lat);
}
if ($lon != '') {
	$tpl['lon'] = $lon;
	$tpl['html_lon'] = htmlspecialchars($lon);
}
// add 2012/04/02 K.Masuda [
if ($lvl != '') {
	$tpl['lvl'] = $lvl;
	$tpl['html_lvl'] = htmlspecialchars($lvl);
}
// add 2012/04/02 K.Masuda ]
// add 2012/10/01 Y.Matsukawa [
if ($lv != '') {
	if (ctype_digit($lv) && $lv >= 1 && $lv <= 18) {
		$tpl['lv'] = $lv;
		$tpl['html_lv'] = htmlspecialchars($lv);
	} else {
		$lv = '';
	}
}
if ($icn != '') {
	$tpl['icn'] = $icn;
	$tpl['html_icn'] = htmlspecialchars($icn);
}
if ($nm != '') {
	$tpl['nm'] = $nm;
	$tpl['html_nm'] = htmlspecialchars($nm);
	$tpl['enc_nm'] = urlencode($nm);
}
if ($addr != '') {
	$tpl['addr'] = $addr;
	$tpl['html_addr'] = htmlspecialchars($addr);
	$tpl['enc_addr'] = urlencode($addr);
}
// add 2012/10/01 Y.Matsukawa ]

// 絞り込みcond
$condprm = '';
$condprm_js = '';		// add 2014/02/05 Y.Matsukawa
for($i = 1; $i <= 200; $i++) {
	$cnm = 'cond'.$i;
	if(isset($_VARS[$cnm]) && $_VARS[$cnm] != '') {
		$_VARS[$cnm] = mb_ereg_replace('"', '', $_VARS[$cnm]);		// ダブルクォート除去	add 2013/11/28 Y.Matsukawa
		$_VARS[$cnm] = mb_ereg_replace("'", "", $_VARS[$cnm]);		// シングルクォート除去	add 2014/02/04 Y.Matsukawa
		$tpl[$cnm] = $_VARS[$cnm];
		$tpl[$cnm.'_'.$_VARS[$cnm]] = 1;
		$condprm .= sprintf('cond%d=%s&', $i, $_VARS[$cnm]);
		$condprm_enc .= sprintf('cond%d=%s&', $i, urlencode($_VARS[$cnm]));		// add 2014/02/04 Y.Matsukawa
	}
}
if ($condprm) $condprm_js = mb_ereg_replace('"', '\\"', ($condprm));		// add 2014/02/05 Y.Matsukawa

$arr_cond_jkn = array();
$cond_jkn = '';
$cond_prm = '';
$cond_prm_enc = '';
$user_cond_jkn = false;
if($D_COND_GRP && count($D_COND_GRP) > 0){
	foreach($D_COND_GRP as $gno => $cnolist) {
		$arr_cond_jkn_wk = array();
		foreach($cnolist as $cno) {
			if(isset($_VARS['cond'.$cno]) && $_VARS['cond'.$cno] != '') {
				$prmval = $_VARS['cond'.$cno];
				$condinf = $D_COND[$cno];
				if ($condinf) {
					$condval = '';
					if ($condinf['type'] == 'CB') {
						$condval = $condinf['val'];
						$user_cond_jkn = true;
						if ($prmval) {
							$tpl['cond'.$cno.'_sel'] = 'checked';
							$tpl['cond'.$cno.'chk'] = 1;
							if($D_COND_STATIC) $tpl['cond'.$cno.'chk'] = 'checked';		// add 2015/05/14 Y.Matsukawa
						}
					} else if ($condinf['type'] == 'SL') {
						$user_cond_jkn = true;
						$o = $condinf['opts'][$prmval];
						if ($o) {
							//$condval = $o['val'];		mod 2012/02/09 Y.Matsukawa
							$condval = $o[0];
							$tpl['cond'.$cno.'_'.$prmval.'_sel'] = 'selected';
							$tpl['cond'.$cno.'_'.$prmval.'sel'] = 'selected';		// add 2015/05/14 Y.Matsukawa
						}
					// add 2015/03/30 H.Osamoto [
					} else if ($condinf['type'] == 'TXT') {
						$condval = $condinf['val'];
						$user_cond_jkn = true;
						if ($prmval) {
							$tpl['cond'.$cno.'_text'] = $prmval;
						}
					} else if ($condinf['type'] == 'TXTMULTI') {
						$condval = str_replace('@@@val@@@', $prmval, $condinf['val']);
						$user_cond_jkn = true;
						if ($prmval) {
							$tpl['cond'.$cno.'_text'] = $prmval;
						}
					// add 2015/03/30 H.Osamoto ]
					}
					if ($condval) {
						// CGIに渡すjkn
						// ※スペースが含まれる場合（COL_01:1 OR COL_02:1等）はカッコで囲む
						$arr_cond_jkn_wk[] = (strpos($condval, ' ')===false ? $condval : '('.$condval.')');
					}
				}
				//				// URLパラメータ
				//				$cond_prm .= '&cond'.$cno.'='.$condval;
				//				$cond_prm_enc .= '&cond'.$cno.'='.urlencode(mb_convert_encoding($condval, 'UTF-8', 'EUC-JP'));
			}
		}
		if (count($arr_cond_jkn_wk)) {
			$arr_cond_jkn[] = '('.implode(' '.$D_COND_ANDOR[$gno].' ', $arr_cond_jkn_wk).')';
		}
	}
	if (count($arr_cond_jkn)) {
		$cond_jkn = implode(' '.$D_COND_GRP_ANDOR.' ', $arr_cond_jkn);
		$tpl['cond_jkn'] = $cond_jkn;
		if ($user_cond_jkn) $tpl['user_cond_jkn'] = 1;
	}
}
// add 2013/02/05 K.Masuda [
if(isset($D_COND_APPEND[0]) && $D_COND_APPEND[0]){
	if($cond_jkn != ''){
		$cond_jkn = '('.$cond_jkn.') '.$D_COND_APPEND[1].' '.$D_COND_APPEND[0];
	} else {
		$cond_jkn = $D_COND_APPEND[0];
	}
	$tpl['cond_jkn'] = $cond_jkn;
}
// add 2013/02/05 K.Masuda ]

// 任意パラメータ
$P_FREEPARAMS = '';
$P_FREEPARAMS_ENC = '';
$P_FREEPARAMS_SJIS = '';
$P_FREEPARAMS_JS = '';		// add 2014/02/05 Y.Matsukawa
$wk_freeparams = array();
$wk_freeparams_enc = array();
$wk_freeparams_sjis = array();

// add start 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
$P_FREEPARAMS_UTF = '';
$wk_freeparams_utf = array();
// add end 2017/03/14 H.Yasunaga ]

// mod start 2016/08/15 H.Yasunaga p_sとp_fの最大数をsmt側に合わせる
//for ($pcnt=1; $pcnt<=50; $pcnt++) {
for ($pcnt=1; $pcnt<=$D_P_MAX; $pcnt++) {
// mod end ]
	if (isset(${"p_s".$pcnt})) {
		$val = ${"p_s".$pcnt};
		${"p_s".$pcnt."_html"} = htmlspecialchars($val);		// add 2014/02/04 Y.Matsukawa
		${"p_s".$pcnt."_html_sq"} = htmlspecialchars($val, ENT_QUOTES);		// add 2015/08/27 Y.Matsukawa
		${"p_s".$pcnt."_js"} = mb_ereg_replace('"', '\\"', ($val));		// add 2014/02/04 Y.Matsukawa
		$tpl["P_STRING_".$pcnt] = $val;
		$tpl["P_STRING_".$pcnt."_HTML"] = htmlspecialchars($val);		// add 2013/09/24 Y.Matsukawa
		$tpl["P_STRING_".$pcnt."_HTML_SQ"] = htmlspecialchars($val, ENT_QUOTES);		// add 2015/08/27 Y.Matsukawa
		$wk_freeparams[] = "p_s".$pcnt."=".$val;
		$wk_freeparams_enc[] = "p_s".$pcnt."=".urlencode($val);
		$wk_freeparams_sjis[] = "p_s".$pcnt."=".rawurlencode(mb_convert_encoding($val,'SJIS','eucJP-win'));
		// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
		$wk_freeparams_utf[] = "p_s".$pcnt."=".rawurlencode(mb_convert_encoding($val,'UTF8','eucJP-win'));
		// add 2017/03/14 H.Yasunaga ]
		// add 2012/02/29 Y.Matsukawa [
		$tpl['freeparams'][$i]['name'] = "p_s".$pcnt;
		$tpl['freeparams'][$i]['val'] = htmlspecialchars($val);
		// add 2012/02/29 Y.Matsukawa ]
	}
	if (isset(${"p_f".$pcnt})) {
		$val = ${"p_f".$pcnt};
		${"p_f".$pcnt."_html"} = htmlspecialchars($val);		// add 2014/02/04 Y.Matsukawa
		${"p_f".$pcnt."_html_sq"} = htmlspecialchars($val, ENT_QUOTES);		// add 2015/08/27 Y.Matsukawa
		${"p_f".$pcnt."_js"} = mb_ereg_replace('"', '\\"', ($val));		// add 2014/02/04 Y.Matsukawa
		$tpl["P_FLG_".$pcnt] = ${"p_f".$pcnt};
		$tpl["P_FLG_".$pcnt."_HTML"] = htmlspecialchars($val);		// add 2015/08/27 Y.Matsukawa
		$tpl["P_FLG_".$pcnt."_HTML_SQ"] = htmlspecialchars($val, ENT_QUOTES);		// add 2015/08/27 Y.Matsukawa
		$wk_freeparams[] = "p_f".$pcnt."=".$val;
		$wk_freeparams_enc[] = "p_f".$pcnt."=".urlencode($val);
		$wk_freeparams_sjis[] = "p_f".$pcnt."=".rawurlencode(mb_convert_encoding($val,'SJIS','eucJP-win'));
		// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
		$wk_freeparams_utf[] = "p_f".$pcnt."=".rawurlencode(mb_convert_encoding($val,'UTF8','eucJP-win'));
		// add 2017/03/14 H.Yasunaga ]
		// add 2012/02/29 Y.Matsukawa [
		$tpl['freeparams'][$i]['name'] = "p_f".$pcnt;
		$tpl['freeparams'][$i]['val'] = htmlspecialchars($val);
		// add 2012/02/29 Y.Matsukawa ]
	}
}
if (count($wk_freeparams)) $P_FREEPARAMS = implode("&", $wk_freeparams);
if (count($wk_freeparams_enc)) $P_FREEPARAMS_ENC = implode("&", $wk_freeparams_enc);
if (count($wk_freeparams_sjis)) $P_FREEPARAMS_SJIS = implode("&", $wk_freeparams_sjis);
// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
if (count($wk_freeparams_utf)) $P_FREEPARAMS_UTF = implode("&", $wk_freeparams_utf);
// add 2017/03/14 H.Yasunaga ]
unset($wk_freeparams);
unset($wk_freeparams_enc);
unset($wk_freeparams_sjis);
// add 2017/03/14 H.Yasunaga 日本郵便カスタマイズ [
unset($wk_freeparams_utf);
// add 2017/03/14 H.Yasunaga ]
if ($P_FREEPARAMS) $P_FREEPARAMS_JS = mb_ereg_replace('"', '\\"', ($P_FREEPARAMS));		// add 2014/02/05 Y.Matsukawa
if ($P_FREEPARAMS_ENC) $tpl['P_FREEPARAMS_ENC'] = $P_FREEPARAMS_ENC;		// add 2012/02/28 Y.Matsukawa

// add start 2017/03/14 H.Yasunaga 日本郵便カスタマイズ
// mod start 2017/04/19 H.Yasunaga 日本郵便カスタマイズ [
//if ($cid == 'jppost15' || $cid == 'jppost15test') {
if ($cid == 'jppost15' || $cid == 'jppost15test' || $cid == 'jppost17' || $cid == 'jppost17test') {
// mod end 2017/04/19 H.Yasunaga ]
	if (strpos($script_name, ".htm") || $script_name == "search_area.js") {
		switch($tpl['jp_param_enc']) {
			case "SJIS": {
				$P_FREEPARAMS_ENC = $P_FREEPARAMS_SJIS . "&enc=SJIS";
				break;
			}
			case "EUC":{
				$P_FREEPARAMS_ENC .= "&enc=EUC";
				break;
			}
			case "UTF8":{
				$P_FREEPARAMS_ENC = $P_FREEPARAMS_UTF . "&enc=UTF8";
				break;
			}
		}
	}
	// 詳細画面の表示用に拠点の情報をcgiでとるが、文字コード変換されてしまうので戻す
	// mod 2017/03/27 H.Yasunaga 吹き出し表示が文字化けするため [
	//if ($script_name == "shop_dtl.htm") {
	if ($script_name == "shop_dtl.htm" || $script_name == "msg.htm") {
	// mod 2017/03/27 H.Yasunaga ]
		$enc = "EUC";
	}
}
// add end 2017/03/14 H.Yasunaga]

// del 2014/12/11 Y.Matsukawa [
// パンくずTOP
//$ZdcHistoryTop = array('name'=>$D_HISTORY_TOP_NAME,
//	'url'=>$D_HISTORY_TOP_LINK
//		.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'')
//		.($condprm?'&'.$condprm:'')
//);
//$his_count = count($ZdcHistory);
//$i = 0;
//$tpl['history'][$i]['first'] = 1;
//$tpl['history'][$i]['name'] = $D_HISTORY_TOP_NAME;
//if ($his_count > 0) {
//	switch($D_TOP_PAGE_KBN) {
//		// 標準TOP
//		case 0:
//			$tpl['history'][$i]['url'] = $D_DIR_BASE_G.'?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm?'&'.$condprm:'');
//			break;
//		// 客先TOP
//		case 1:
//			$tpl['history'][$i]['url'] = $D_HISTORY_TOP_LINK;
//			break;
//		// ZDC預り（asp）
//		case 2:
//			$tpl['history'][$i]['url'] = $D_HISTORY_TOP_LINK;
//			if (!strpos($tpl['history'][$i]['url'], '?')) $tpl['history'][$i]['url'] .= '?';
//			$tpl['history'][$i]['url'] .= ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm?'&'.$condprm:'');
//			break;
//	}
//	$tpl["D_HISTORY_TOP_LINK_PRM"] = $tpl['history'][$i]['url'];		// add 2012/09/20 Y.Matsukawa
//	if (isset($tpl['history'][$i]['url']) && $tpl['history'][$i]['url']) $tpl['history_last_url'] = $tpl['history'][$i]['url'];		// add 2011/12/13 Y.Matsukawa
//	foreach ($ZdcHistory as $h => $his_inf) {
//		$i++;
//		$tpl['history'][$i]['name'] = $his_inf['name'];
//		if ($h < $his_count - 1) {
//			$tpl['history'][$i]['url'] = $his_inf['url'];
//			$tpl['history_last_url'] = $his_inf['url'];		// add 2011/12/13 Y.Matsukawa
//		}
//	}
//}
// del 2014/12/11 Y.Matsukawa ]

// パンくず生成		add 2014/12/11 Y.Matsukawa
include('/home/emap/src/p/inc/act_make_history.inc');

?>
