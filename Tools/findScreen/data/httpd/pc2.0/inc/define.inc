<?php
// ------------------------------------------------------------
// ����ե����� �ᥤ��
// 
// ��ȯ����
// 2007/03/01 bando@D&I		������ȯ
// 2008/10/22 Y.Matsukawa	���Ѥ��ʤ�JS�ϥ����ɤ��ʤ�
// 2009/11/10 Y.Matsukawa	��ȯ��VM��
// 2010/04/08 Y.Matsukawa	�ȼ����к��ʥ����������ȥ�����ץƥ��󥰡�
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2010/07/27 Y.Matsukawa	����URL��https��ɽ��
// 2010/08/13 Y.Matsukawa	iPhone����Υ�����������Ӥإ�����쥯��
// 2010/11/03 K.Masuda		���ꥢ����ʣ���б�
// 2011/10/03 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����  
// ------------------------------------------------------------

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off�б�
//���ϥѥ�᡼���������������ɲ�
//post,get
//Ʊ��̾�Τǥѥ�᡼�������ä����ϡ�
//POST��ͥ�褹��
extract($_GET);
extract($_POST);

if (isset($_SERVER['SCRIPT_NAME']) && $_SERVER['SCRIPT_NAME'] != "") {
	$SCRIPT_NAME = $_SERVER['SCRIPT_NAME'];
}
if (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] != "") {
	$https_req = $_SERVER['HTTPS'];
} else {
	$https_req = "";
}
if (isset($_SERVER['HTTP_REFERER']) && $_SERVER['HTTP_REFERER'] != "") {
	$HTTP_REFERER = $_SERVER['HTTP_REFERER'];
} else {
	$HTTP_REFERER = "";
}

// add 2011/07/05 Y.Nakajima ]

// add 2009/11/10 Y.Matsukawa [
$hostname = trim(`hostname`);

switch( $hostname ){
//----- ��ȯ�� -----
case "devemapweb":
	// ��ȯ��VM�ϥץ�������ͳ�ˤʤ�Τǡ�HTTP_HOST����������IP�ˤʤäƤ��ޤ���
	$_SERVER["HTTP_HOST"] = "218.225.89.139";
	break;
// add 2011/02/09 Y.Matsukawa [

// add 2011/09/09 c_hanajima [
case "dev-storenaviweb01":
    // VM�ܹԸ峫ȯ����������
    //$_SERVER["HTTP_HOST"] = "10.47.50.79";	//��꡼���ޤǤϤ�����
	$_SERVER["HTTP_HOST"] = "218.225.89.139";    //��꡼����ϳ�ȯ��������򤳤���ˤ���
    break;
// mod 2011/09/09 c_hanajima ]

//----- ���ڵ��ʻ��굡�� -----
case "emapweb06":
	$_SERVER["HTTP_HOST"] = "test.e-map.ne.jp";
	break;
//----- ���ڵ� -----
case "emapweb00":
	$_SERVER["HTTP_HOST"] = "test.e-map.ne.jp";
	break;
// add 2011/07/05 Y.Nakajima [
//----- ���ڵ� -----
case "storenaviweb-v01":
case "storenaviweb-v02":    //ͽ����
//2011/09/02 VM�����Х�꡼�����ϡ�host̾���ѹ��ˤʤ뤬�����ֵ��˷Ҥ��Τǡ����ڵ���case���ɲäϤ��ʤ�
    //$_SERVER["HTTP_HOST"] = "172.29.0.35";	//��꡼���ޤǤϤ�����
	$_SERVER["HTTP_HOST"] = "test.e-map.ne.jp";    //��꡼����ϸ��ڵ�������򤳤���ˤ���
    break;
// add 2011/07/05 Y.Nakajima ]
//----- ���ֵ� -----
default:
	$_SERVER["HTTP_HOST"] = "www.e-map.ne.jp";
// add 2011/02/09 Y.Matsukawa ]
}
// add 2009/11/10 Y.Matsukawa ]

// add 2010/04/08 Y.Matsukawa [
// �ȼ����к��ʥ����������ȥ�����ץƥ��󥰡�
// Host�إå����Ѥ��б�
$_SERVER["HTTP_HOST"] = htmlspecialchars($_SERVER["HTTP_HOST"], ENT_QUOTES);
// ���󥰥륯�����Ȥ����٤��ѥ�᡼��
$D_REMOVE_QUOTE_PARAMS = array(
'type',
'adcd',
'area',
);
// add 2010/04/08 Y.Matsukawa ]

// add 2010/07/20 Y.Matsukawa [
// mod 2011/07/05 Y.Nakajima [
if (!isset($https_req)) {
	if (isset($_SERVER['HTTPS'])) {
		$https_req = $_SERVER['HTTPS'];
	} else {
		$https_req = "";
	}
}
if ($https_req != "") {
// mod 2011/07/05 Y.Nakajima ]
	$protocol = 'https';
} else {
	$protocol = 'http';
}
// add 2010/07/20 Y.Matsukawa ]

// �١����ǥ��쥯�ȥ� --------------------------------------
// mod 2011/07/05 Y.Nakajima [
//$tmp = substr($SCRIPT_NAME, 0, strrpos($SCRIPT_NAME, "/"))."/";
if (isset($SCRIPT_NAME)) {
	$tmp = substr($SCRIPT_NAME, 0, strrpos($SCRIPT_NAME, "/"))."/";
} else {
	$tmp = "/";
}
// mod 2011/07/05 Y.Nakajima ]

$D_DIR_BASE = "http://".$_SERVER["HTTP_HOST"].$tmp;
$D_DIR_BASE_G = "$protocol://".$_SERVER["HTTP_HOST"].$tmp;		// add 2010/07/20 Y.Matsukawa

// ��� ������ ---------------------------------------------
if(isset($cid)) $D_CID = $cid;
	else $D_CID = "00000000";
//$D_DIR_COMPANY = $D_DIR_BASE."company/".$D_CID."/";		mod 2010/07/20 Y.Matsukawa
$D_DIR_COMPANY = $D_DIR_BASE_G."company/".$D_CID."/";
$D_SYSDIR_COMPANY = "./company/".$D_CID."/";


// �Ƽ�����ե����� ----------------------------------------
include("../inc/ZdcCommonFunc.inc");
include("./inc/define_system.inc");
include("d_serv_emap.inc");

$D_DIR_BASE_L = "http://".$EMAP_SSAPI_SRV.$tmp;		// add 2011/02/09 Y.Matsukawa

//��������
@include("./company/".$cid."/setting.inc");			//�Хå����ե��������ꤵ���
@include("./company/".$cid."/setting_option.inc");	//�Хå����ե���̤�б�����

//ɬ�פ�JS���������ɤ���		2008/10/22 Y.Matsukawa add
include("./inc/define_jsload.inc");

//����URL		2010/07/27 Y.Matsukawa
// mod 2011/07/05 Y.Nakajima 
if (isset($D_MBURL_HTTPS) && $D_MBURL_HTTPS) {
	$D_MOBILE_URL = str_replace('http://', 'https://', $D_MOBILE_URL);
}

//����URL�Υǥ��쥯�ȥ�		add 2010/08/13 Y.Matsukawa
$D_MOBILE_URL_DIR = dirname($D_MOBILE_URL);
if (substr($D_MOBILE_URL_DIR, -1) != '/') $D_MOBILE_URL_DIR .= '/';

// add 2010/11/03 K.Masuda [
// ���ꥢ����MAX��
define("D_AREA_MAX", 5);
// add 2010/11/03 K.Masuda ]

//��������
include("./inc/define_design.inc");
include("./inc/define_action.inc");
include("./inc/define_msg.inc");
include("./inc/define_js.inc");

//�ؿ���
include("./inc/function.inc");
include("./inc/crypt.inc");

?>