<?php
// ------------------------------------------------------------
// �������������cgi�����������
// 
// 2011/03/10 Y.Matsukawa	��������
// 2012/01/19 N.Wada		��CID����
// 2012/11/15 Y.Matsukawa	JCN�����������
// ------------------------------------------------------------
//-------------------
// �����������
//-------------------
//$url = sprintf("%s?cid=%s",$D_SSAPI["get_icon_info"],$D_CID);		mod 2012/01/19 N.Wada
$url = sprintf("%s?cid=%s", $D_SSAPI["get_icon_info"], $D_ICON_CID);
$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
if($dat) {
	//�ǥե������
	$D_ICON["@SHOP"]["IMG"] = $D_ICON_SHOP_IMG;
	$D_ICON["@SHOP"]["W"] = $D_ICON_SHOP_W;
	$D_ICON["@SHOP"]["H"] = $D_ICON_SHOP_H;
	$D_ICON["@NEW"]["IMG"] = $D_ICON_NEW_IMG;
	$D_ICON["@NEW"]["W"] = $D_ICON_NEW_W;
	$D_ICON["@NEW"]["H"] = $D_ICON_NEW_H;
	$D_ICON["@SEL"]["IMG"] = $D_ICON_FOCUS_IMG;
	$D_ICON["@SEL"]["W"] = $D_ICON_FOCUS_W;
	$D_ICON["@SEL"]["H"] = $D_ICON_FOCUS_H;
	$D_ICON["@SELB"]["IMG"] = $D_ICON_CURSOR_IMG;
	$D_ICON["@SELB"]["W"] = $D_ICON_CURSOR_W;
	$D_ICON["@SELB"]["H"] = $D_ICON_CURSOR_H;
	// add 2012/11/15 Y.Matsukawa [
	$D_ICON["@TP"]["IMG"] = $D_ICON_TP_IMG;
	$D_ICON["@TP"]["W"] = $D_ICON_TP_W;
	$D_ICON["@TP"]["H"] = $D_ICON_TP_H;
	// add 2012/11/15 Y.Matsukawa ]
	//������������񤭴���
	$cgi = $D_SSAPI["icon_select_g"];
	// mod 2011/07/05 Y.Nakajima [
	$status = explode("\t",$dat[0]);
	//$data_list = explode("\n",$dat[0]);
	//$status = explode("\t",$data_list[0]);
	// mod 2011/07/05 Y.Nakajima ]
	$cnt = $status[1];
	for($i = 0;$i < $cnt;$i ++) {
		// mod 2011/07/05 Y.Nakajima
		$rec = explode("\t",$dat[$i+1]);
		//$rec = explode("\t",$data_list[$i+1]);
		$tmp = $rec[1];
		//$D_ICON[$tmp]["IMG"] = sprintf("%s?cid=%s&icon_id=%s",$cgi,$D_CID,$tmp);		mod 2012/01/19 N.Wada
		$D_ICON[$tmp]["IMG"] = sprintf("%s?cid=%s&icon_id=%s", $cgi, $D_ICON_CID, $tmp);
		if($rec[0] != 0) $D_ICON[$tmp]["IMG"] .= ".gif";//��.gif�פ��դ��ʤ���API��GIF��Ƚ�Ǥ��ʤ����� �������Ͻ���
		$D_ICON[$tmp]["W"]   = $rec[2];
		$D_ICON[$tmp]["H"]   = $rec[3];
		//��ǡ������б����뤿��̵�����ǥե�����ͤ�Ĥä��� ���Τ����ä���
		if(!intval($D_ICON[$tmp]["W"])) $D_ICON[$tmp]["W"]   = 28;
		if(!intval($D_ICON[$tmp]["H"])) $D_ICON[$tmp]["H"]   = 28;
	}
}
?>