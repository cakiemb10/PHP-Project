<?php
// ------------------------------------------------------------
// �ƥ�ץ졼��($header,$body,$footer)�������ǽ�ʶ��̽���
//
// 2012/03/04 K.Masuda		��������
// 2012/09/18 Y.Matsukawa	�ƥ�ץ졼�Ȥ���HTML�ե�����̾�򻲾�
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

// HTML�ե�����̾		add 2012/09/18 Y.Matsukawa
$tpl_htmlflg = str_replace('.', '_', basename($SCRIPT_NAME));
$header[$tpl_htmlflg] = 1;
$body[$tpl_htmlflg] = 1;
$footer[$tpl_htmlflg] = 1;

?>