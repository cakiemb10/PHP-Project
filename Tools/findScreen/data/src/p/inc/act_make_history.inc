<?PHP
//------------------------------------------
// パンくず生成
//
// 2014/12/11 Y.Matsukawa	新規作成（※act_get_parm.incから移植）
// 2015/01/28 Y.Matsukawa	最寄駅、最寄施設などをパンくずに追加
// 2015/03/17 Y.Matsukawa	絞り込み：任意カラムの部分一致
// 2015/03/25 Y.Matsukawa	【不具合】TOPがaspだとパンくずTOPがエラーになる
// 2015/08/27 Y.Matsukawa	セキュリティ対応（Cross-Site Scripting）
// 2016/01/26 Y.Uesugi		ヤマト運輸対応：店舗一覧での絞り込み条件を反映する
// 2017/05/14 Y.Matsukawa	XSS対策
//------------------------------------------

// パンくずTOP
$ZdcHistoryTop = array('name'=>$D_HISTORY_TOP_NAME,
	'url'=>$D_HISTORY_TOP_LINK
		.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'')
		//.($condprm?'&'.$condprm:'')		mod 2015/03/17 Y.Matsukawa
		.($condprm_enc?'&'.$condprm_enc:'')
);
$his_count = count($ZdcHistory);
$i = 0;
$tpl['history'][$i]['first'] = 1;
$tpl['history'][$i]['index'] = $i+1;		// add 2015/01/28 Y.Matsukawa
$tpl['history'][$i]['name'] = $D_HISTORY_TOP_NAME;
if ($his_count > 0) {
	switch($D_TOP_PAGE_KBN) {
		// 標準TOP
		case 0:
			//$tpl['history'][$i]['url'] = $D_DIR_BASE_G.'?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm?'&'.$condprm:'');		mod 2015/03/17 Y.Matsukawa
			$tpl['history'][$i]['url'] = $D_DIR_BASE_G.'?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm_enc?'&'.$condprm_enc:'');
			break;
		// 客先TOP
		case 1:
			$tpl['history'][$i]['url'] = $D_HISTORY_TOP_LINK;
			break;
		// ZDC預り（asp）
		case 2:
			$tpl['history'][$i]['url'] = $D_HISTORY_TOP_LINK;
			if (strpos(strtolower($D_HISTORY_TOP_LINK), 'javascript:') === false) {		// add 2015/03/25 Y.Matsukawa
				if (!strpos($tpl['history'][$i]['url'], '?')) $tpl['history'][$i]['url'] .= '?';
				//$tpl['history'][$i]['url'] .= ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm?'&'.$condprm:'');		mod 2015/03/17 Y.Matsukawa
				$tpl['history'][$i]['url'] .= ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm_enc?'&'.$condprm_enc:'');
			}
			break;
	}
	$tpl["D_HISTORY_TOP_LINK_PRM"] = $tpl['history'][$i]['url'];		// add 2012/09/20 Y.Matsukawa
	if (isset($tpl['history'][$i]['url']) && $tpl['history'][$i]['url']) $tpl['history_last_url'] = $tpl['history'][$i]['url'];		// add 2011/12/13 Y.Matsukawa
	foreach ($ZdcHistory as $h => $his_inf) {
		$i++;
		$tpl['history'][$i]['index'] = $i+1;		// add 2015/01/28 Y.Matsukawa
		//$tpl['history'][$i]['name'] = $his_inf['name'];		mod 2017/05/14 Y.Matsukawa
		$tpl['history'][$i]['name'] = htmlspecialchars($his_inf['name'], ENT_QUOTES);
		if ($h < $his_count - 1) {
			//$tpl['history'][$i]['url'] = $his_inf['url'];		mod 2015/08/27 Y.Matsukawa
			$tpl['history'][$i]['url'] = htmlspecialchars($his_inf['url']);
			//$tpl['history_last_url'] = $his_inf['url'];		// add 2011/12/13 Y.Matsukawa	mod 2015/08/27 Y.Matsukawa
			$tpl['history_last_url'] = htmlspecialchars($his_inf['url']);

			// add 2016/01/26 Y.Uesugi [
			if (isset($D_NLIST_COND_CHECK_UPDATE) && $D_NLIST_COND_CHECK_UPDATE != '') {
				//?の前までを切り取って、それ以降を付け替える
				$url_q = explode('?', $his_inf['url']);
				$his_url = $url_q[0].'?';
				$url_a = explode('&', $url_q[1]);
				foreach ($url_a as $prm) {
					if((strpos($prm, 'cond') === false) && $prm != ""){
						$his_url .= '&'.$prm;
					}
				}
				$tpl['history'][$i]['url'] = htmlspecialchars($his_url).($condprm_enc?'&'.$condprm_enc:'');
				$tpl['history_last_url'] = htmlspecialchars($his_url).($condprm_enc?'&'.$condprm_enc:'');
			}
			// add 2016/01/26 Y.Uesugi ]

		// add 2015/01/28 Y.Matsukawa [
		} else {
			//$tpl['history'][$i]['hidden_url'] = $his_inf['url'];		mod 2015/08/27 Y.Matsukawa
			$tpl['history'][$i]['hidden_url'] = htmlspecialchars($his_inf['url']);
		// add 2015/01/28 Y.Matsukawa ]

			// add 2016/01/26 Y.Uesugi [
			if (isset($D_NLIST_COND_CHECK_UPDATE) && $D_NLIST_COND_CHECK_UPDATE != '') {
				//?の前までを切り取って、それ以降を付け替える
				$url_q = explode('?', $his_inf['url']);
				$his_url = $url_q[0].'?';
				$url_a = explode('&', $url_q[1]);
				foreach ($url_a as $prm) {
					if(strpos($prm, 'cond') === false){
						$his_url .= '&'.$prm;
					}
				}
				$tpl['history'][$i]['hidden_url'] = htmlspecialchars($his_url).($condprm_enc?'&'.$condprm_enc:'');
			}
			// add 2016/01/26 Y.Uesugi ]

		}
	}
}

$tpl['history_count'] = count($tpl['history']);		// add 2015/01/28 Y.Matsukawa

?>
