<?PHP
//------------------------------------------
// BASICǧ��
//
// ��������
// 2013/04/11 H.Osamoto		�ƥ�ץ졼�ȥ������ޥ�����Basicǧ��ͭ�Υץ�ӥ塼�б�

//------------------------------------------
function AuthenticateUser($u, $p, $pw) {
	global $cid;
	// mod 2013/04/11 H.Osamoto [
	//	$uid = str_replace("test", "", $cid);
	if(strpos($cid,"_prev") > -1){
		// ��ȣɣĤˡ���_prev�פΥ�����ɤ�������ϡ�
		// �ƥ�ץ졼�ȥ������ޥ������Υץ�ӥ塼
		$uid = str_replace("test", "", substr($cid, 0, strpos($cid,"_prev")));
	} else {
		$uid = str_replace("test", "", $cid);
	}
	// mod 2013/04/11 H.Osamoto ]

	if ($uid == "") return false;
	if ($pw == "") return false;
	if ($u != $uid) return false;
	if ($p != $pw) return false;
	return true;
} 
if ($D_BASIC_AUTH[$D_EMAP_ENV]) {
	// Basicǧ�ڥѥ���ɼ���
	$pw = "";
	$url = sprintf("%s?cid=%s&opt=%s", $D_SSAPI["get_basic_pw"], $D_CID, $cid);
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if($status[0] == "89300000") {
		$rec = explode("\t", $dat[1]);
		$encpw = $rec[0];
		$pw = f_decrypt_api_key($encpw);//����
		list($dummy, $pw) = explode("=", $pw);//���ߡ�ʸ��������
		$realm = 'e-map '.str_replace('test', '', $D_CID);
		// ID̤���ϡʽ���
		if (!isset($_SERVER["PHP_AUTH_USER"])) {
			header("WWW-Authenticate: Basic realm=\"$realm\"");
			header("HTTP/1.0 401 Unauthorized");
			// ����󥻥����ɽ��
			$tpl["err"] = "���Υڡ�����ɽ�����븢�¤�����ޤ���";
			@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error.tpl",$tpl);
			for($i = 0;$i < 10;$i ++)
				@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error_".$i.".tpl",$tpl);
			exit;
		// ID����
		} else {
			// ǧ��
			if (AuthenticateUser($_SERVER["PHP_AUTH_USER"], $_SERVER["PHP_AUTH_PW"], $pw)) {
				// OK
			} else {
				// ���顼
				header("WWW-Authenticate: Basic realm=\"$realm\"");
				header("HTTP/1.0 401 Unauthorized");
				// ����󥻥����ɽ��
				$tpl["err"] = "���Υڡ�����ɽ�����븢�¤�����ޤ���";
				@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error.tpl",$tpl);
				for($i = 0;$i < 10;$i ++)
					@HtmlTemplate::t_include($D_SYSDIR_COMPANY."emapview_error_".$i.".tpl",$tpl);
				exit;
			}
		}
	}
}
?>