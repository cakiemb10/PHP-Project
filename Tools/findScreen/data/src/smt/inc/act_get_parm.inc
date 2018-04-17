<?PHP
//------------------------------------------
// 引き回しパラメータ
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/08 Y.Matsukawa	機能追加（絞り込み拡張、拠点エリア検索、駅リスト検索）
// 2011/08/25 Y.Matsukawa	cond条件hidden対応
// 2012/02/21 Y.Matsukawa	店舗一覧にチェックボックス設置
// 2012/09/10 Y.Matsukawa	【不具合修正】任意パラメータに「&」を含めると正しく引き継がれない、任意パラメータに半角スペース指定すると消える
// 2013/04/10 Y.Matsukawa	無駄なエラーログ出力を抑制（lat,lonチェック）
// 2015/02/13 Y.Matsukawa	絞り込み変更再検索
// 2017/03/21 H.Yasunaga	日本郵便カスタマイズ
// 2017/04/19 H.Yasunaga	日本郵便カスタマイズ
//------------------------------------------
$pl_prm = array();
$pl_prm_enc = array();
$pl_prm_enc_enc = array();		// add 2012/09/10 Y.Matsukawa
// del 2012/09/10 Y.Matsukawa [
//	// mod 2011/07/05 Y.Nakajima [
//	if (!isset($pl_prm['pl']) ) {
//		$pl_prm['pl'] = "";
//	}
//	if (!isset($pl_prm_enc['pl']) ) {
//		$pl_prm_enc['pl'] = "";
//	}
//	if (!isset($pl_prm['cond']) ) {
//		$pl_prm['cond'] = "";
//	}
//	if (!isset($pl_prm_enc['cond']) ) {
//		$pl_prm_enc['cond'] = "";
//	}
//	// mod 2011/07/05 Y.Nakajima ]
// del 2012/09/10 Y.Matsukawa ]
// add 2012/09/10 Y.Matsukawa [
$pl_prm['pl'] = '';
$pl_prm_enc['pl'] = '';
$pl_prm_enc_enc['pl'] = '';
$pl_prm['cond'] = '';
$pl_prm_enc['cond'] = '';
$pl_prm_enc_enc['cond'] = '';
$pl_prm_plfilter = '';
$pl_prm_plfilter_enc = '';
// add 2012/09/10 Y.Matsukawa ]

// mod 2011/07/05 Y.Nakajima
if (isset($pltype) && $pltype != '') {
	$tpl['pltype'] = $pltype;
	$tpl['pltype'.$pltype] = 1;
	$tpl['html_pltype'] = htmlspecialchars($pltype);
	$pl_prm['pl'] .= '&pltype='.$pltype;
	$pl_prm_enc['pl'] = '&pltype='.urlencode(mb_convert_encoding($pltype, 'UTF-8', 'EUC-JP'));
	$pl_prm_enc_enc['pl'] = '&pltype='.urlencode(urlencode(mb_convert_encoding($pltype, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
}
// mod 2011/07/05 Y.Nakajima
if (isset($plname) && $plname != '') {
	$tpl['plname'] = $plname;
	$tpl['html_plname'] = htmlspecialchars($plname);
	$tpl['plname_enc'] = urlencode(mb_convert_encoding($plname, 'UTF-8', 'EUC-JP'));		// add 2015/02/13 Y.Matsukawa
	$pl_prm['pl'] .= '&plname='.$plname;

	// mod 2017/03/21 H.Yasunaga 日本郵便カスタマイズ [
	//$pl_prm_enc['pl'] .= '&plname='.urlencode(mb_convert_encoding($plname, 'UTF-8', 'EUC-JP'));
	// mod 2017/04/19 H.Yasunaga 日本郵便カスタマイズ [
	//if($cid == 'jppost15' || $cid == 'jppost15test') {
	//if ($D_JPOST_CUSTOM_ENCODE) {
	if($cid == 'jppost15' || $cid == 'jppost15test' || $cid == 'jppost17' || $cid == 'jppost17test') {
	// mod end ]
		$pl_prm_enc['pl'] .= '&plname='.urlencode(mb_convert_encoding($plname, $tpl['jp_param_enc_charset'], 'EUC-JP'));
	} else {
		$pl_prm_enc['pl'] .= '&plname='.urlencode(mb_convert_encoding($plname, 'UTF-8', 'EUC-JP'));
	}
	// mod 2017/03/21 H.Yasunaga 日本郵便カスタマイズ ]

	$pl_prm_enc_enc['pl'] .= '&plname='.urlencode(urlencode(mb_convert_encoding($plname, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
}
// mod 2011/07/05 Y.Nakajima
//if (isset($lat) && isset($lon)) {		mod 2013/04/10 Y.Matsukawa
if (isset($lat) && isset($lon) && $lat && $lon) {
	$cnvdatum = '';
	// mod 2011/07/05 Y.Nakajima
	if (isset($datum) && $datum != '') {
		dbl("datum=$datum");
		if (isset($D_PRM_DATNUM[$datum])) {
			$cnvdatum = $D_PRM_DATNUM[$datum];
			$datum = '';
		}
	} else {
		$cnvdatum = $D_PRM_DATNUM['TOKYO'];
		dbl("datum=");
	}
	dbl("$lat,$lon");
	dbl("cnvdatum=$cnvdatum");
	cnv_ll2lldms($lat, $lon, $cnvdatum, $lat, $lon);
	dbl("cnv_ll2lldms=>$lat,$lon");
}
// mod 2011/07/05 Y.Nakajima
if (isset($lat) && $lat != '') {
	$tpl['lat'] = $lat;
	$tpl['html_lat'] = htmlspecialchars($lat);
	$pl_prm['pl'] .= '&lat='.$lat;
	$pl_prm_enc['pl'] .= '&lat='.urlencode(mb_convert_encoding($lat, 'UTF-8', 'EUC-JP'));
	$pl_prm_enc_enc['pl'] .= '&lat='.urlencode(urlencode(mb_convert_encoding($lat, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
}
// mod 2011/07/05 Y.Nakajima
if (isset($lon) && $lon != '') {
	$tpl['lon'] = $lon;
	$tpl['html_lon'] = htmlspecialchars($lon);
	$pl_prm['pl'] .= '&lon='.$lon;
	$pl_prm_enc['pl'] .= '&lon='.urlencode(mb_convert_encoding($lon, 'UTF-8', 'EUC-JP'));
	$pl_prm_enc_enc['pl'] .= '&lon='.urlencode(urlencode(mb_convert_encoding($lon, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
}
// mod 2011/07/05 Y.Nakajima
if (isset($plfilter) && $plfilter != '') {
	$tpl['plfilter'] = $plfilter;
	$tpl['html_plfilter'] = htmlspecialchars($plfilter);
	$pl_prm_plfilter = '&plfilter='.$plfilter;		// add 2012/02/21 Y.Matsukawa
	$pl_prm_plfilter_enc = '&plfilter='.urlencode(mb_convert_encoding($plfilter, 'UTF-8', 'EUC-JP'));		// add 2012/09/10 Y.Matsukawa
	$pl_prm['cond'] .= '&plfilter='.$plfilter;
	$pl_prm_enc['cond'] .= '&plfilter='.urlencode(mb_convert_encoding($plfilter, 'UTF-8', 'EUC-JP'));
	$pl_prm_enc_enc['cond'] .= '&plfilter='.urlencode(urlencode(mb_convert_encoding($plfilter, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
}
//if ($condidx != '') {
//	$tpl['condidx'] = $condidx;
//	$tpl['condidx'.$condidx] = 1;
//	$tpl['html_condidx'] = htmlspecialchars($condidx);
//	$pl_prm_enc['cond'] .= '&condidx='.urlencode(mb_convert_encoding($condidx, 'UTF-8', 'EUC-JP'));
//	$condval = $D_FILTER_VAL_LIST[$condidx];
//	$tpl['condval'] = $condval;
//	$tpl['html_condval'] = htmlspecialchars($condval);
//	$condname = $D_FILTER_NAME_LIST[$condidx];
//	$tpl['condname'] = $condname;
//	$tpl['html_condname'] = htmlspecialchars($condname);
//}

// 絞り込みcond		add 2011/08/08 Y.Matsukawa
$arr_cond_jkn = array();
$cond_jkn = '';
$cond_prm = '';
$cond_prm_enc = '';
$cond_prm_enc_enc = '';		// add 2012/09/10 Y.Matsukawa
$user_cond_jkn = false;		// add 2011/08/25 Y.Matsukawa
//mod 2011/09/09 Y.nakajima
if(isset($D_COND_GRP) && count($D_COND_GRP) > 0){
	foreach($D_COND_GRP as $gno => $cnolist) {
		$arr_cond_jkn_wk = array();
		foreach($cnolist as $cno) {
			//mod 2011/09/09 Y.nakajima [
			if (isset(${'cond'.$cno})) {
				$condval = ${'cond'.$cno};
			} else {
				$condval = "";
			}
			//mod 2011/09/09 Y.nakajima ]
			if ($condval != '') {
				// CGIに渡すjkn
				// ※スペースが含まれる場合（COL_01:1 OR COL_02:1等）はカッコで囲む
				$arr_cond_jkn_wk[] = (strpos($condval, ' ')===false ? $condval : '('.$condval.')');
				// テンプレートへcond指定を渡す
				$tpl['cond'.$cno] = $condval;
				$condinf = $D_COND[$cno];
				if ($condinf) {
					if ($condinf['type'] == 'CB') {
						$user_cond_jkn = true;		// add 2011/08/25 Y.Matsukawa
						$tpl['cond'.$cno.'_sel'] = 'checked';
					} else if ($condinf['type'] == 'SL') {
						$user_cond_jkn = true;		// add 2011/08/25 Y.Matsukawa
						$condopts = $condinf['opts'];
						if ($condopts) {
							foreach ($condopts as $i=>$o) {
								if ($condval == $o[0]) {
									$tpl['cond'.$cno.'_'.$i.'_sel'] = 'selected';
								}
							}
						}
					}
				}
				// URLパラメータ
				$pl_prm['cond'] .= '&cond'.$cno.'='.$condval;
				$pl_prm_enc['cond'] .= '&cond'.$cno.'='.urlencode(mb_convert_encoding($condval, 'UTF-8', 'EUC-JP'));
				$pl_prm_enc_enc['cond'] .= '&cond'.$cno.'='.urlencode(urlencode(mb_convert_encoding($condval, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
				$cond_prm .= '&cond'.$cno.'='.$condval;
				$cond_prm_enc .= '&cond'.$cno.'='.urlencode(mb_convert_encoding($condval, 'UTF-8', 'EUC-JP'));
				$cond_prm_enc_enc .= '&cond'.$cno.'='.urlencode(urlencode(mb_convert_encoding($condval, 'UTF-8', 'EUC-JP')));		// add 2012/09/10 Y.Matsukawa
			}
		}
		if (count($arr_cond_jkn_wk)) {
			$arr_cond_jkn[] = '('.implode(' '.$D_COND_ANDOR[$gno].' ', $arr_cond_jkn_wk).')';
		}
	}
	if (count($arr_cond_jkn)) {
		$cond_jkn = implode(' '.$D_COND_GRP_ANDOR.' ', $arr_cond_jkn);
		$tpl['cond_jkn'] = $cond_jkn;
		if ($user_cond_jkn) $tpl['user_cond_jkn'] = 1;		// add 2011/08/25 Y.Matsukawa
	}
}

$pl_prm_all = implode('', $pl_prm);
$pl_prm_enc_all = implode('', $pl_prm_enc);
$pl_prm_enc_enc_all = implode('', $pl_prm_enc_enc);		// add 2012/09/10 Y.Matsukawa
?>
