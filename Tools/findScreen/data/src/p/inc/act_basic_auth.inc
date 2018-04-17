<?PHP
//------------------------------------------
// BASIC認証
//
// 2011/12/20 Y.Matsukawa	エラー画面表示の実装ミス
//------------------------------------------
function AuthenticateUser($u, $p, $pw) {
	global $cid;
	$uid = str_replace("test", "", $cid);
	if ($uid == "") return false;
	if ($pw == "") return false;
	if ($u != $uid) return false;
	if ($p != $pw) return false;
	return true;
} 
// add 2012/01/10 H.osamoto [
function AuthenticateUserMulti($uid, $pass, $arr_id, $arr_pass) {

	if ($uid == "") return false;
	if ($pass == "") return false;

	for($i = 0; $i < count($arr_id); $i++){
		if ($uid == $arr_id[$i]) {
			if ($pass == $arr_pass[$i]) {
				// 認証OK
				return true;
			}
		}
	}
	return false;
}
// add 2012/01/10 H.osamoto ]

// add 2012/01/10 H.osamoto [
if ($D_BASIC_AUTH_MULTI) {
	// ID未入力（初回）
	if (!isset($_SERVER["PHP_AUTH_USER"])) {
		header("WWW-Authenticate: Basic realm=\"$realm\"");
		header("HTTP/1.0 401 Unauthorized");
		// キャンセル時の表示
		$tpl["err"] = "このページを表示する権限がありません";
		ZdcLogPut(1);
		htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
		exit;
	// ID入力
	} else {
		// 認証
		if (AuthenticateUserMulti($_SERVER["PHP_AUTH_USER"], $_SERVER["PHP_AUTH_PW"], $D_BASIC_AUTH_ID, $D_BASIC_AUTH_PASS)) {
			// OK
		} else {
			// エラー
			header("WWW-Authenticate: Basic realm=\"$realm\"");
			header("HTTP/1.0 401 Unauthorized");
			// キャンセル時の表示
			$tpl["err"] = "このページを表示する権限がありません";
			ZdcLogPut(1);
			htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
			exit;
		}
	}
}
// add 2012/01/10 H.osamoto ]
//	if ($D_BASIC_AUTH[$D_EMAP_ENV]) {	mod 2012/01/10 H.Osamoto
else if ($D_BASIC_AUTH[$D_EMAP_ENV]) {
	// Basic認証パスワード取得
	$pw = "";
	$url = sprintf("%s?cid=%s&opt=%s", $D_SSAPI["get_basic_pw"], $D_CID, $cid);
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if($status[0] == "89300000") {
		$rec = explode("\t", $dat[1]);
		$encpw = $rec[0];
		$pw = f_decrypt_api_key($encpw);//復号
		list($dummy, $pw) = explode("=", $pw);//ダミー文字列を除去
		$realm = 'e-map '.str_replace('test', '', $D_CID);
		// ID未入力（初回）
		if (!isset($_SERVER["PHP_AUTH_USER"])) {
			header("WWW-Authenticate: Basic realm=\"$realm\"");
			header("HTTP/1.0 401 Unauthorized");
			// キャンセル時の表示
			$tpl["err"] = "このページを表示する権限がありません";
			// del 2011/12/20 Y.Matsukawa [
			//			@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error.tpl",$tpl);
			//			for($i = 0;$i < 10;$i ++)
			//				@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error_".$i.".tpl",$tpl);
			// del 2011/12/20 Y.Matsukawa ]
			// add 2011/12/20 Y.Matsukawa [
			ZdcLogPut(1);
			htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
			// add 2011/12/20 Y.Matsukawa ]
			exit;
		// ID入力
		} else {
			// 認証
			if (AuthenticateUser($_SERVER["PHP_AUTH_USER"], $_SERVER["PHP_AUTH_PW"], $pw)) {
				// OK
			} else {
				// エラー
				header("WWW-Authenticate: Basic realm=\"$realm\"");
				header("HTTP/1.0 401 Unauthorized");
				// キャンセル時の表示
				$tpl["err"] = "このページを表示する権限がありません";
				// del 2011/12/20 Y.Matsukawa [
				//				@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error.tpl",$tpl);
				//				for($i = 0;$i < 10;$i ++)
				//					@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error_".$i.".tpl",$tpl);
				// del 2011/12/20 Y.Matsukawa ]
				// add 2011/12/20 Y.Matsukawa [
				ZdcLogPut(1);
				htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
				// add 2011/12/20 Y.Matsukawa ]
				exit;
			}
		}
	}
}
?>
