<?php
// ------------------------------------------------------------
// テンプレート($header,$body,$footer)に設定可能な共通処理
//
// 2012/03/04 K.Masuda		新規作成
// 2012/09/18 Y.Matsukawa	テンプレートからHTMLファイル名を参照
// ------------------------------------------------------------
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
					$body["p_f_grp".$one_k] = NULL;
				} else {
					$body["p_f_grp".$one_k] = 1;
					break;
			}
		}
	}
}

// HTMLファイル名		add 2012/09/18 Y.Matsukawa
$tpl_htmlflg = str_replace('.', '_', basename($SCRIPT_NAME));
$header[$tpl_htmlflg] = 1;
$body[$tpl_htmlflg] = 1;
$footer[$tpl_htmlflg] = 1;

?>
