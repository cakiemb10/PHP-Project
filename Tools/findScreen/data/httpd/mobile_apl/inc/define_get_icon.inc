<?php
// ------------------------------------------------------------
// �������������cgi�����������
// 
// �ѹ�����
// 2007/09/26 matsukawa		��������
// 2012/01/04 Y.Matsukawa	�̴��ID����
// 2012/11/19 Y.Matsukawa	JCN�����������
// ------------------------------------------------------------
//�ǥե������
$D_ICON["@SEL"]["IMG"] = $D_WAKU_IMAGE;
$D_ICON["@TP"]["IMG"] = $D_TP_IMAGE;		// add 2012/11/19 Y.Matsukawa
//$url = sprintf("%s?cid=%s",$D_SSAPI["get_icon_info"],$cid);
$url = sprintf("%s?cid=%s", $D_SSAPI["get_icon_info"], $D_ICON_CID);
$dat = ZdcHttpRead($url, 0, D_SOCKET_TIMEOUT);
// mod 2011/07/05 Y.Nakajima [
if(isset($dat)) {
	//������������񤭴���
	$cgi = $D_SSAPI["icon_select"];
	//$status = explode("\t",$dat[0]);
	// del 2012/11/19 Y.Matsukawa [
	//	$data_list = explode("\n", $dat[0]);
	//	$status = explode("\t", $data_list[0]);
	// del 2012/11/19 Y.Matsukawa ]
	$status = explode("\t",$dat[0]);		// add 2012/11/19 Y.Matsukawa
	if($status[0] = "89100000") {
		$cnt = $status[1];
		for($i = 0; $i < $cnt; $i++) {
			//$rec = explode("\t",$dat[$i+1]);
			//$rec = explode("\t", $data_list[$i+1]);		del 2012/11/19 Y.Matsukawa
			$rec = explode("\t",$dat[$i+1]);		// add 2012/11/19 Y.Matsukawa
			$tmp = $rec[1];
			//$D_ICON[$tmp]["IMG"] = sprintf("%s?cid=%s&icon_id=%s", $cgi, $cid, $tmp);
			$D_ICON[$tmp]["IMG"] = sprintf("%s?cid=%s&icon_id=%s", $cgi, $D_ICON_CID, $tmp);
		}
	}
}

?>