<?php
/*========================================================*/
// �ե�����̾��tpl_get_maplayer.cgi
// ����̾���Ͽޥ쥤�䡼����
//
// ��������2008/10/27
// �����ԡ�Y.Matsukawa
//
// ���⡧�����ѤߤΥƥ�ץ졼�Ȥ����Ͽޥ쥤�䡼�ֹ�����
//       ��PC�ƥ�ץ졼�Ȥ��������PCͥ��
//
// ��������
// 2008/10/27 Y.Matsukawa	��������
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
	
	// ���ϥѥ�᡼�������å�
	if ($cid == "") {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	
	// PC�ƥ�ץ졼�Ȥ�setting.inc���ɤ߹���
	@include(PC_COMPANY_DIR.$cid.'/setting.inc');
	@include(PC_COMPANY_DIR.$cid.'/setting_option.inc');
	if (!$D_MAP_LAYER_KBN) {
		// ���ӥƥ�ץ졼�Ȥ�setting.inc���ɤ߹���
		@include(MB_COMPANY_DIR.$cid.'/setting.inc');
		@include(MB_COMPANY_DIR.$cid.'/setting_option.inc');
		if ($D_MAP_LANG == 'eng') {
			$D_MAP_LAYER_KBN = 5;
		} else {
			$D_MAP_LAYER_KBN = 4;	// �ǥե���ȡ����ܸ�glaf��
		}
	}

	print $cgi_kind . "00000" . "\n";
	print $D_MAP_LAYER_KBN . "\n";

?>
