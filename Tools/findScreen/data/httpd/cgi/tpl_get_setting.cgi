<?php
/*========================================================*/
// �ե�����̾��tpl_get_setting.cgi
// ����̾���ƥ�ץ졼���������
//
// ��������2009/08/28
// �����ԡ�Y.Matsukawa
//
// ���⡧�����ѤߤΥƥ�ץ졼�Ȥ��顢���ꤵ�줿�ѿ�����������
//
// ��������
// 2009/08/28 Y.Matsukawa	��������
// 2012/10/16 Y.Matsukawa	error_reporting()���
/*========================================================*/
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	header( "Content-Type: Text/html; charset=euc-jp" );

	define("PC_COMPANY_DIR", "../pc/company/");
	define("MB_COMPANY_DIR", "../mobile_apl/company/");

	// CGI����
	$cgi_kind = "812";

	// �ѥ�᡼������
	$cid = ${'_'.$_SERVER['REQUEST_METHOD']}['cid'];
	$pm = ${'_'.$_SERVER['REQUEST_METHOD']}['pm'];
	$v = ${'_'.$_SERVER['REQUEST_METHOD']}['v'];
	
	// ���ϥѥ�᡼�������å�
	if ($cid == "" || $pm == "" || $v == "") {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	
	// PC�ƥ�ץ졼�Ȥ�setting.inc���ɤ߹���
	if ($pm == 'P') {
		@include(PC_COMPANY_DIR.$cid.'/setting.inc');
		@include(PC_COMPANY_DIR.$cid.'/setting_option.inc');
	} else if ($pm == 'M') {
		// ���ӥƥ�ץ졼�Ȥ�setting.inc���ɤ߹���
		@include(MB_COMPANY_DIR.$cid.'/setting.inc');
		@include(MB_COMPANY_DIR.$cid.'/setting_option.inc');
	}

	print $cgi_kind . "00000" . "\n";
	print $$v . "\n";

?>
