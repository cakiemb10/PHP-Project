<?php
// ------------------------------------------------------------
// �����ġ�������������
// 
// 2016/06/14 H.Yasunaga	��������
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/crypt.inc");
	require_once(dirname(__FILE__) . "/ora_procif.inc");
	class ApiManageUtil{
		
		// ��������
		public static function login($db, $userid, $password, &$internalErrorFlg, &$errorMsg) {
			
			// text-fo\inc\function_collection.inc��AuthUser�Υ桼�������ѥ���ɤγ�ǧ��ʬ��ȴ��
			$passwd_dec = f_pw_dec($password);
			
			$arr_emap_corp['CORP_ID'] = $userid;
			//$arr_emap_corp['PASSWD'] = $password;
			$arr_emap_corp['PASSWD'] = $passwd_dec;
			
			$retcd = SpifPEmapCorpUpdt( &$db, "S", "front", &$arr_emap_corp, &$o_rtncd );
			if ( ! $retcd || ($o_rtncd != 0) ) {
				//$err_msg = "Authentication error ! ";
				return false;
			}
			return true;
			
		}
	}
?>