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
// 2011/07/04 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/12/13 H.osamoto		SSL��³��(https)�˥ѥ�᡼����$https_req�פ�����Ѥ��褦�˽���
// 2012/03/19 SKC			����ꥢȽ���������ɲ�
// 2012/10/26 K.Masuda		PC->���ޥۥ�����쥯���ѽ̼ܥ�٥��Ѵ�ɽ�ɲ�
// 2014/08/13 F.Yokoi		���ꥸ�ʥ�Υɥᥤ��̾����񤭤���ʤ��褦�˽���
// 2016/06/20 Y.Matsukawa	����͹���������쥯���б�
// ------------------------------------------------------------

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off�б�
//���ϥѥ�᡼���������������ɲ�
//post,get
//Ʊ��̾�Τǥѥ�᡼�������ä����ϡ�
//POST��ͥ�褹��
extract($_GET);
extract($_POST);

$script_name = basename($_SERVER['SCRIPT_NAME']);		// add 2016/02/20 Y.Matsukawa

//error_log(date("Y/m/d H:i:s")." [$script_name] ".$_SERVER["QUERY_STRING"]."\n", 3, "/var/tmp/pc_debug_".date("Ymd").".log");

if (isset($_SERVER['SCRIPT_NAME']) && $_SERVER['SCRIPT_NAME'] != "") {
	$SCRIPT_NAME = $_SERVER['SCRIPT_NAME'];
}
if (!isset($https_req)) {	// add 2011/12/13 H.osamoto
	if (isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] != "") {
		$https_req = $_SERVER['HTTPS'];
	} else {
		$https_req = "";
	}
} 							// add 2011/12/13 H.osamoto
if (isset($_SERVER['HTTP_REFERER']) && $_SERVER['HTTP_REFERER'] != "") {
	$HTTP_REFERER = $_SERVER['HTTP_REFERER'];
} else {
	$HTTP_REFERER = "";
}
// add 2011/07/05 Y.Nakajima ]

// add 2016/06/20 Y.Matsukawa
// ����͹��������쥯���б��ʵ쥵����URL��
if ($_SERVER["HTTP_HOST"] == 'map.japanpost.jp') {
	$url = 'http://' . $_SERVER["HTTP_HOST"] . '/p/search/';
	header('Location: '.$url);
	exit;
}

// add 2014/08/13 F.Yokoi [
$PC_HTTP_HOST_ORG = $_SERVER["HTTP_HOST"];
// add 2014/08/13 F.Yokoi ]

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

//echo($_SERVER["HTTP_HOST"]);
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

// add 2012/03/19 SKC [
//����ꥢȽ��
define("D_REG_WILL"    , "DDIPOCKET");
define("D_REG_PC"      , "Mozilla");
define("D_DOCOMO"      , "DoCoMo");
define("D_SOFTBANK"    , "SOFTBANK");
define("D_SOFTBANK2"   , "SoftBank");
define("D_KDDI"        , "KDDI");
define("D_HDML"        , "HDML");
define("D_WILL"        , "WILLCOM");
define("D_PC"          , "PC");
// add 2012/03/19 SKC ]

// add 2012/10/26 K.Masuda [
// PC->���ޥۥ�����쥯���ѽ̼ܥ�٥��Ѵ�ɽ
$D_LV_PCTOSMT = array(	// PC			->	���ޥ�
	'1'  => '1',		// 1:1/1300��	->	1:1/1500��
	'2'  => '2',		// 2:1/650��	->	2:1/650��
	'3'  => '3',		// 3:1/300��	->	3:1/300��
	'4'  => '4',		// 4:1/150��	->	4:1/150��
	'5'  => '5',		// 5:1/100��	->	5:1/100��
	'6'  => '6',		// 6:1/50��		->	6:1/50��
	'7'  => '7',		// 7:1/25��		->	7:1/25��
	'8'  => '8',		// 8:1/15��		->	8:1/10��
	'9'  => '8',		// 9:1/10��		->	8:1/10��
	'10' => '9',		// 10:1/5��		->	9:1/5��
	'11' => '10',		// 11:1/2��		->	10:1/2��
	'12' => '11',		// 12:1/1��5000	->	11:1/1��5000
	'13' => '12',		// 13:1/1��		->	12:1/1��
	'14' => '13',		// 14:1/7500	->	13:1/7500
	'15' => '14',		// 15:1/5000	->	14:1/3500
	'16' => '14',		// 16:1/3500	->	14:1/3500
	'17' => '15',		// 17:1/2500	->	15:1/1500
	'18' => '15'		// 18:1/1500	->	15:1/1500
);
// add 2012/10/26 K.Masuda ]

//--------------------------------------------
// �ƥ�ץ졼�Ȥ˰��Ϥ�
//--------------------------------------------
if (isset($D_CID)) $tpl["D_CID"] = $D_CID;		// add 2016/02/20 Y.Matsukawa

?>