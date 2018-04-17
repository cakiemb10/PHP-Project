<?php
// ------------------------------------------------------------
// 管理ツールログイン処理
// 
// 2016/06/14 H.Yasunaga	新規作成
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/crypt.inc");
	require_once(dirname(__FILE__) . "/ora_procif.inc");
	class ApiManageUtil{
		
		// ログイン
		public static function login($db, $userid, $password, &$internalErrorFlg, &$errorMsg) {
			
			// text-fo\inc\function_collection.incのAuthUserのユーザー・パスワードの確認部分を抜粋
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