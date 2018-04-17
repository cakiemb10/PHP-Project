<?PHP
// ------------------------------------------------------------
// ư����ĥ����å�
// 
// 2011/03/10 Y.Matsukawa	��������
// 2011/12/21 Y.Matsukawa	��ե�������å�����https/http����̤��ʤ��⡼��
// 2013/02/13 K.Masuda		�����ӥ����֤�Ƚ����������ӥ����̤�Ƚ�ꤹ��
// ------------------------------------------------------------
// �����ӥ�����
//$url = sprintf("%s?cid=%s&opt=%s", $D_SSAPI['getsdate'], $D_CID, $cid);	// mod 2013/02/13 K.Masuda
$url = sprintf("%s?cid=%s&opt=%s&sys=%s", $D_SSAPI['getsdate'], $D_CID, $cid, "Q");
$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
$status = explode("\t", $dat[0]);
if($status[0] == '89000000') {
	$rec = explode("\t", $dat[1]);
	$flg = intval($rec[0]);
}
if($flg == 0) {
	$err = $D_MSG_EMAPVIEW_NOSERVICE;
}
// ��ե�������å�
if($HTTP_REFERER && $D_ALLOW_REFERER && $D_ALLOW_REFERER != '*') {
	$arr = explode(';', $D_ALLOW_REFERER.';');
	$arr[] = $D_DIR_BASE_G;
	$ok = 0;
	for ($i = 0; $i < count($arr); $i++) {
		// del 2011/12/21 Y.Matsukawa [
		//		if ($arr[$i])
		//			if (strpos(' '.$HTTP_REFERER, $arr[$i]) == 1) $ok = 1;
		// del 2011/12/21 Y.Matsukawa ]
		// add 2011/12/21 Y.Matsukawa [
		if ($arr[$i]) {
			if ($D_ALLOW_REFERER_PROTOCOL) {
				// �ץ��ȥ�����̤�����Ϥ��Τޤ����
				$user_ref = $HTTP_REFERER;
				$allw_ref = $arr[$i];
			} else {
				// �ץ��ȥ�����̤��ʤ�����https��http���ִ��������
				$user_ref = mb_ereg_replace('https:', 'http:', $HTTP_REFERER);
				$allw_ref = mb_ereg_replace('https:', 'http:', $arr[$i]);
			}
			if (strpos(' '.$user_ref, $allw_ref) == 1) {
				$ok = 1;
				break;
			}
		}
		// add 2011/12/21 Y.Matsukawa [
	}
	if (!$ok) $err = $D_MSG_EMAPVIEW_NOREFERER;
} else if (!$HTTP_REFERER && $D_ALLOW_REFERER_NULL != 1) {
	// NULL�Υ����å�
	$err = $D_MSG_EMAPVIEW_NOREFERER;
}
// �ǥ��쥯�ȥ�̵ͭ
if(!file_exists($D_SYSDIR_COMPANY)) {
	echo $D_MSG_EMAPVIEW_NOCID;
	exit;
}
// IP���¥����å�
if (!ip_check()) {
	$err = $D_MSG_EMAPVIEW_INVALIDIP;
}
// SSL���ĥ����å�
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