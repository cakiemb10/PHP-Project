<?PHP
// ------------------------------------------------------------
// 動作許可チェック
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/01/10 N.Wada		リファラチェック時、https/httpを区別しないモード
// 2013/02/13 K.Masuda		サービス期間の判定時、サービス種別も判定する
// ------------------------------------------------------------
// サービス期間
//$url = sprintf("%s?cid=%s&opt=%s",$D_SSAPI['getsdate'],$D_CID,$cid);
$url = sprintf("%s?cid=%s&opt=%s&sys=%s",$D_SSAPI['getsdate'],$D_CID,$cid,"S");
$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
$status = explode("\t",$dat[0]);

if($status[0] == '89000000') {
	$rec = explode("\t",$dat[1]);
	$flg = intval($rec[0]);
}
// mod 2011/07/05 Y.Nakajima
//if(isset($flg) && $flg == 0) {	// mod 2013/02/13 K.Masuda
if($flg == 0) {
	$err = $D_MSG_EMAPVIEW_NOSERVICE;
}
// リファラチェック
// mod 2011/07/05 Y.Nakajima
if(isset($HTTP_REFERER) && $HTTP_REFERER != "" && isset($D_ALLOW_REFERER) && $D_ALLOW_REFERER != '*') {
	$arr = explode(';',$D_ALLOW_REFERER.';');
	$arr[] = $D_DIR_BASE_G;
	$ok = 0;
	for($i = 0;$i < count($arr);$i ++) {
		// del 2012/01/10 N.Wada [
		//if($arr[$i])
			//if(strpos(' '.$HTTP_REFERER,$arr[$i]) == 1) $ok = 1;
		// del 2012/01/10 N.Wada ]
		// add 2012/01/10 N.Wada [
		if ($arr[$i]) {
			if ($D_ALLOW_REFERER_PROTOCOL) {
				// プロトコル区別する場合はそのまま比較
				$user_ref = $HTTP_REFERER;
				$allw_ref = $arr[$i];
			} else {
				// プロトコル区別しない場合はhttpsをhttpに置換して比較
				$user_ref = mb_ereg_replace('https:', 'http:', $HTTP_REFERER);
				$allw_ref = mb_ereg_replace('https:', 'http:', $arr[$i]);
			}
			if (strpos(' '.$user_ref, $allw_ref) == 1) {
				$ok = 1;
				break;
			}
		}
		// add 2012/01/10 N.Wada ]
	}
	if(!$ok) $err = $D_MSG_EMAPVIEW_NOREFERER;
// mod 2011/07/05 Y.Nakajima
} else if(!isset($HTTP_REFERER) && $D_ALLOW_REFERER_NULL != 1) {
	// NULLのチェック
	$err = $D_MSG_EMAPVIEW_NOREFERER;
}
// ディレクトリ有無
if(!file_exists($D_SYSDIR_COMPANY)) {
	echo $D_MSG_EMAPVIEW_NOCID;
	exit;
}
// IP制限チェック
if (!ip_check()) {
	$err = $D_MSG_EMAPVIEW_INVALIDIP;
}
// SSL許可チェック
if ($https_req) {
	if (!$D_SSL_ACCESS) {
		$err = $D_MSG_EMAPVIEW_HTTPS;
	}
} else {
	if ($D_SSL_ACCESS == 2) {
		$err = $D_MSG_EMAPVIEW_HTTP;
	}
}
?>
