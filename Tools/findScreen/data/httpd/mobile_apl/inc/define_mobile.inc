<?php
// ------------------------------------------------------------
// 2009/06/29 Y.Matsukawa	Maplink�˸����ϼ�����ǽ���ɲ�
//							Ǥ�եѥ�᡼���ɲ�
// 2009/07/15 Y.Matsukawa	AD Maplink�б�
// 2009/11/10 Y.Matsukawa	��ȯ��VM��
// 2010/03/17 Y.Matsukawa	������GPS��ޥ����
// 2010/04/06 Y.Matsukawa	���ꥢ�����ʸ�����͡ˤ���ƻ�ܸ���������ʬ����ɽ������ʤ�
// 2010/05/17 Y.Matsukawa	optʣ���������ORϢ����ǽ�ˤ���
// 2010/05/28 Y.Matsukawa	�֥����ѹ���e-mapAD�����Ĥ�NAVI��
// 2010/06/21 Y.Matsukawa	�Ǵ����������η������
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/08/25 Y.Matsukawa	����θ�����opt�����̵��������
// 2011/09/28 K.Masuda		���ޥۤإ�����쥯��
// 2012/02/13 Y.Matsukawa	��Ȳ�����CORP_IMG_TBL���б�
// 2012/03/04 K.Masuda		p_f��p_s�ѥ�᡼������������ɲ�
// 2012/03/17 N.Wada		d_serv_emap.inc���cid�򻲾Ȥ��������ᡢ�������˴��ID�����
// 2012/03/29 K.Masuda		������³�Υ��ޥۥ�����쥯���б�
// 2012/05/14 Y.Matsukawa	��������ڡ�����
// 2012/08/07 Y.Matsukawa	error_reporting���Һ��
// 2012/10/25 Y.Matsukawa	d.htm��d.html�Ǥ⥢��������ǽ�ˤ���
// 2012/10/26 K.Masuda		����->���ޥۥ�����쥯���ѽ̼ܥ�٥��Ѵ�ɽ�ɲ�
// 2012/11/19 Y.Matsukawa	JCN�����������
// 2012/12/17 H.Osamoto		���������̹�������������ޥ���
// 2013/02/13 K.Masuda		�����ӥ����֤�Ƚ����������ӥ����̤�Ƚ�ꤹ��
// 2013/04/11 H.Osamoto		�ƥ�ץ졼�ȥ������ޥ����Υץ�ӥ塼ɽ������Basicǧ�ڤ�Ԥ�ʤ�
// 2013/04/15 H.Osamoto		�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ������������굡ǽ�ɲ�
// 2013/06/06 Y.Matsukawa	���ꥢ���������ǡ������ؤΤߤ��б�
// 2013/07/31 Y.Matsukawa	���Զ�����۽���FW���콽��פ�����פ�Ʊ��������̤ˤʤ��GEO���͡�
// 2013/07/31 H.Osamoto		��ޥȱ�͢�����������ޥ�����͹���ֹ渡��0��ξ�硢����ꥹ�ȸ���������
// 2014/02/06 Y.Matsukawa	�ȼ����к���XSS����
// 2014/03/10 H.Osamoto		�ݥꥴ���⳰Ƚ�ꥫ����ɲ�
// 2014/07/10 Y.Matsukawa	͹���ֹ渡�������������åסʺǴ�������ľ�����ܡ�
// 2015/01/08 Y.Matsukawa	ǯ��ƥ�ץ졼�Ȥ��Ϥ�
// 2015/06/01 Y.Uesugi		Ź�ް��������Ƚ����
// 2015/06/02 Y.Uesugi		���ꥢ�����裲����NULL�б�
// 2015/09/06 Y.Matsukawa	�������ƥ��б���SQL Injection��
// 2015/11/18 Xuan Chien	GPS���������б�
// 2016/03/28 Y.Uesugi		���ޥۥ�����쥯���Զ�罤��
// 2016/03/29 Y.Matsukawa	optcdʣ������Ϣ�����
// 2016/06/01 Y.Matsukawa	�Ǵ���Ͽޤ�����
// 2016/06/13 Y.Matsukawa	����͹����͹���ֹ渡��
// 2016/07/04 Y.Matsukawa	���ޥۥ�����������PC�إ�����쥯��
// 2016/07/04 N.Wada		�ܺ٥��顼���Υ�����쥯����URL�ɲ�
// 2016/07/05 N.Wada		PC������ü������Υ����������Υ�����쥯����URL�ɲ�
// 2016/07/28 N.Wada		�ܺ٤Υإå����ƥ�ץ졼�Ȥˡ������ǡ��������Υե饰���Ϥ�
// 2016/12/05 Y.Uesugi		���ޥۥ�����쥯��SSL�ɲ�
// 2017/03/24 N.Wada		canonical�����˽��Ϥ���URL
// 2017/05/11 H.Yasunaga	��ޥȥ��å����������ƥ��������б�
// 2017/05/30 H.Yasunaga	��ޥȥ��å����������ƥ��������б�
// ------------------------------------------------------------
$script_name = basename($_SERVER['SCRIPT_NAME']);		// add 2013/08/29 Y.Matsukawa
// add 2016/03/31 Y.Matsukawa [
if ($script_name) {
	$tpl_htmlflg = str_replace('.', '_', $script_name);
	$body_cst[$tpl_htmlflg] = 1;
}
// add 2016/03/31 Y.Matsukawa [

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off�б�
//���ϥѥ�᡼���������������ɲ�
//post,get
//Ʊ��̾�Τǥѥ�᡼�������ä����ϡ�
//POST��ͥ�褹��
extract($_GET);
extract($_POST);

// ���˥�������"'��		add 2014/02/06 Y.Matsukawa
//$arr_sanitize = array('p','pos','ssr','spos','id');		mod 2015/09/06 Y.Matsukawa
$arr_sanitize = array('pos','ssr','spos','id');
foreach ($arr_sanitize as $tmp) {
	if (isset($$tmp) && $$tmp != '') {
		//$$tmp = ereg_replace("[\"']", '', $$tmp);		mod 2015/09/06 Y.Matsukawa
		$$tmp = mb_ereg_replace("[\"']", '', $$tmp);
	}
}

// ���˥�������"'| ��		add 2015/09/06 Y.Matsukawa
$arr_sanitize = array('p','slg','optcd');
foreach ($arr_sanitize as $tmp) {
	if (isset($$tmp) && $$tmp != '') {
		$$tmp = mb_ereg_replace("[\"'\| ]", '', $$tmp);
	}
}


/////////////////////////////////////////
if (isset($_SERVER['REQUEST_URI'])) {
	$REQUEST_URI = $_SERVER['REQUEST_URI'];
} else {
	$REQUEST_URI = "";
}

if (isset($_SERVER['prm'])) {
	$prm = $_SERVER['prm'];
} else if (isset($_POST['prm'])) {
	$prm = $_POST['prm'];
} else if (isset($_GET['prm'])) {
	$prm = $_GET['prm'];
} else {
	$prm = "";
}

if (isset($_SERVER['HTTP_USER_AGENT'])) {
	$HTTP_USER_AGENT = $_SERVER['HTTP_USER_AGENT'];
} else {
	$HTTP_USER_AGENT = "";
}
/////////////////////////////////////////
// add 2011/07/05 Y.Nakajima ]

// add 2009/11/10 Y.Matsukawa [
$hostname = trim(`hostname`);		// add 2009/11/10 Y.Matsukawa
switch( $hostname ){
//----- ��ȯ�� -----
case "devemapweb":
	// ��ȯ��VM�ϥץ�������ͳ�ˤʤ�Τǡ�HTTP_HOST����������IP�ˤʤäƤ��ޤ���
	$_SERVER["HTTP_HOST"] = "218.225.89.139";
	break;
}
// add 2009/11/10 Y.Matsukawa ]

// add 2012/03/17 N.Wada [
//////////////////////////////////////////////
// ���ID
//////////////////////////////////////////////
/*
 ��d_serv_emap.inc���cid�򻲾Ȥ��������ᤳ���Ǵ��ID�����
 �����ǥ����ǥ��󥰤��Ƥ���١����ǥ��쥯�ȥꡢ���ID����������å���ܿ�
 */
// d.html�Ǥ⥢��������ǽ�ˤ����d.htm�Ȥ���ư���		add 2012/10/25 Y.Matsukawa
if (strpos($_SERVER['SCRIPT_NAME'], '/d.html') !== false) {
	$_SERVER['SCRIPT_NAME'] = str_replace('/d.html', '/d.htm', $_SERVER['SCRIPT_NAME']);
}
$SCRIPT_NAME = $_SERVER['SCRIPT_NAME'];
$D_DIR_BASE = substr($SCRIPT_NAME, 0, strpos($SCRIPT_NAME, "/mob")+8);
$cid = substr($SCRIPT_NAME, strpos($SCRIPT_NAME, "/mob")+8 );
$cid = substr($cid, 0, strpos($cid,"/"));
if(strpos($cid,"_prev") > -1){
	$cid = substr($cid, 0, strpos($cid,"_prev"));
}
$D_CID = $cid;
${'_'.$_SERVER['REQUEST_METHOD']}['cid'] = $cid;/* ��d_serv_emap.inc���cid��Ƽ������Ƥ��ޤ��Τ� */
// add 2012/03/17 N.Wada ]

$D_MOBILE = true;
define("D_SOCKET_TIMEOUT", 10);
include("ZdcCommonFunc.inc");  // ��������
include("htmltemplate.inc");  // �ƥ�ץ졼�ȴؿ�
include("d_serv_emap.inc");  // ��������
include("crypt.inc");

//////////////////////////////////////////////
// ������
//////////////////////////////////////////////
$D_LOG_SYSTEMERR_CD = "0999";
$D_LOG_LIMITERR_CD = "2100";
$D_LOG_SVRERR_CD = "0999";
$D_LOG_NOTFOUND_CD = "1000";
$D_LOG_NOTKEYWORD_CD = "9100";
$D_LOG_PARAMETERERR_CD = "0100";
$D_LOG_ROUTEERR_CD = "6009";
$D_LOG_NORMAL_CD = "0000";

// ex)
//    ZdcMobileLogPut($D_SEARCH_CORPID, $D_LOG_NORMAL_CD, 0);

//////////////////////////////////////////////
// �ǥХå���
//////////////////////////////////////////////
$hostname = trim(`hostname`);
if($hostname == "devemapweb" || $hostname == "emapweb00" || $hostname == "emapweb06"){
	$debug = true;
} else {
	$debug = false;
}
//if($debug){ error_reporting (E_ERROR); } else { error_reporting (0); }		del 2012/08/07 Y.Matsukawa
define("D_DEBUG_LOG_FILE", "/var/tmp/mobile_debug.log");
//////////////////////////////////////////////
// ��������
//////////////////////////////////////////////
$wk = parse_url($_SERVER["REQUEST_URI"]);
$_SERVER["HTTP_HOST"] = ($_SERVER["HTTP_HOST"] == "" ? $wk["host"] : $_SERVER["HTTP_HOST"]);

// �١����ǥ��쥯�ȥ�
$D_DIR_BASE = substr($SCRIPT_NAME, 0, strpos($SCRIPT_NAME, "/mob")+8);
$cid = substr($SCRIPT_NAME, strpos($SCRIPT_NAME, "/mob")+8 );
$cid = substr($cid, 0, strpos($cid,"/"));
$D_LOG_CID = $cid;

$D_URL_BASE = $D_DIR_BASE.$cid."/";

if(strpos($cid,"_prev") > -1){
	// ��ȣɣĤˡ���_prev�פΥ�����ɤ�������ϡ�
	// �ƥ�ץ졼�ȥ������ޥ������Υץ�ӥ塼
	$cid = substr($cid, 0, strpos($cid,"_prev"));
	$D_PREVIEW = true;
} else {
	$D_PREVIEW = false;
}

if($D_PREVIEW){
	$D_TEMPLATE_DIR = "/home/emap/httpd/emap_tpl/tpl_edit_m/company/$cid/";
	$D_HTTP_DIR_COMPANY = dirname($_SERVER['SCRIPT_NAME'])."/emap_tpl/tpl_edit_m/company/$cid/";	//add 2008/08/07 matsukawa
} else {
	$D_TEMPLATE_DIR = "./company/$cid/";
	$D_HTTP_DIR_COMPANY = dirname($_SERVER['SCRIPT_NAME'])."/company/$cid/";	//add 2008/08/07 matsukawa
}

if(!file_exists($D_TEMPLATE_DIR)){
	header("Content-Type: text/html;charset=Shift_JIS");
	echo mb_convert_encoding("�����ʥ��������Ǥ���[999]","SJIS","EUC-JP");
	exit;
}

$D_CID = $cid;

$D_PFLG = 2;
$D_DATUM = "TOKYO";
$D_SEARCH_CORPID = $D_CID;
$D_SRARCH_SRVSID = '00010';

$D_DIR_COMPANY = $D_TEMPLATE_DIR;

// icn��ά���Υǥե���ȥ�������ʡ���0��ɽ�����롢1��ɽ�����ʤ�		add 2008/12/15 Y.Matsukawa
$D_NO_DEFAULT_ICN = 0;

$body_cst['D_YEAR'] = date('Y');		// add 2015/01/08 Y.Matsukawa

//////////////////////////////////////////////
// e-mapAD Maplink �ǥե������			add 2009/07/15 Y.Matsukawa
//////////////////////////////////////////////
// �������
$D_AD_API = "rt001";
// ����ɽ�����
$D_AD_COUNT = 3;
//// ����ɽ��ʸ�������Ĺ
//$D_AD_MAXLEN = 100;
//$D_AD_TTL_MAXLEN = 50;
// ���ڤ���������
$D_AD_HR = "FF0000";
// ���쥸�å�
//$D_AD_CREDIT = "Ads by �ɥ�������<br>Powered by e-mapAD";		2010/05/28 Y.Matsukawa
$D_AD_CREDIT = "Ads by �ɥ�������<br>Powered by ���Ĥ�NAVI";
// AD Debug LOG
define("D_DEBUG_AD_LOG_FILE", "/var/tmp/mobile_ad_".date('Ymd').".log");

//////////////////////////////////////////////
//��Ȥ��Ȥ�������ɤ߹���
//////////////////////////////////////////////
include($D_DIR_COMPANY . "setting.inc");		// ������
include($D_DIR_COMPANY . "design.inc");			// �ǥ��������

$D_TP_IMAGE = $D_IMAGE_BASE."tp11.gif";		// Ʃ������		add 2012/11/19 Y.Matsukawa

//////////////////////////////////////////////
// �������������å�
//////////////////////////////////////////////
foreach($_GET as $chk_key => $chk_val){
    $_GET[$chk_key] = (strlen($chk_val) > 128 ? substr($chk_val, 0, 128)."..." : $chk_val);
}

foreach($_POST as $chk_key => $chk_val){
    $_POST[$chk_key] = (strlen($chk_val) > 128 ? substr($chk_val, 0, 128)."..." : $chk_val);
}

//--------------------------------------------
// LIGHT�����å�
//--------------------------------------------
//if($SETTING["noncpdata"] == "N" || $SETTING["noncpdata"] == "L"){		mod 2009/07/15 Y.Matsukawa
if($SETTING["noncpdata"] == "N" || $SETTING["noncpdata"] == "A" || $SETTING["noncpdata"] == "L"){
	//if(!ereg("(d\.htm|mi\.htm|m\.htm|ne\.htm|cp\.htm)", $SCRIPT_NAME)){		del 2009/06/29 Y.Matsukawa
	// add 2009/06/29 Y.Matsukawa [
	// mod 2011/07/05 Y.Nakajima
	//if (ereg("(s\.htm|index\.htm)", $SCRIPT_NAME) && $SETTING["noncpdata"] == "N" && $SETTING["location"]) {
	if (preg_match("/(s\.htm|index\.htm)/", $SCRIPT_NAME, $matches) && $SETTING["noncpdata"] == "N" && $SETTING["location"]) {
		// Maplink�ǡֺ��������ͭ���ʾ���s.htm�����
	// mod 2011/07/05 Y.Nakajima
	//} else if(!ereg("(d\.htm|mi\.htm|m\.htm|ne\.htm|cp\.htm)", $SCRIPT_NAME)){
	} else if(!preg_match("/(d\.htm|mi\.htm|m\.htm|ne\.htm|cp\.htm)/", $SCRIPT_NAME, $matches)){
	// add 2009/06/29 Y.Matsukawa ]
		header("Content-Type: text/html;charset=Shift_JIS");
		echo mb_convert_encoding("�����Ѥˤʤ�ޤ���[100]","SJIS","EUC-JP");
		erl("ACCESS CHECK ERROR [$SCRIPT_NAME]");
		exit;
	}
}


// 2007/09/14 del matsukawa			�������ӥ��������Ǥ�ư��Ĥ�
////--------------------------------------------
//// �����ӥ����֥����å�
////--------------------------------------------
//$now_date = date("Ymd");
//if($D_SEARVICE_START > $now_date){
//	header("Content-Type: text/html;charset=Shift_JIS");
//	echo mb_convert_encoding("�����Ѥˤʤ�ޤ���[101]","SJIS","EUC-JP");
//	erl("ACCESS LIMIT CHECK ERROR [$SCRIPT_NAME]");
//	exit;
//}

//------------------------------------------
// BASICǧ��
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
// mod 2011/07/05 Y.Nakajima
//	if (isset($D_BASIC_AUTH[$D_EMAP_ENV]) && $D_BASIC_AUTH[$D_EMAP_ENV]) {		mod 2013/04/11 H.Osamoto
if (isset($D_BASIC_AUTH[$D_EMAP_ENV]) && $D_BASIC_AUTH[$D_EMAP_ENV] && !$D_PREVIEW) {
	// Basicǧ�ڥѥ���ɼ���
	$pw = "";
	$url = sprintf("%s?cid=%s&opt=%s", $D_SSAPI["get_basic_pw"], $cid, $cid);
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if($status[0] == "89300000") {
		$rec = explode("\t", $dat[1]);
		$encpw = $rec[0];
		$pw = f_decrypt_api_key($encpw);//����
		list($dummy, $pw) = explode("=", $pw);//���ߡ�ʸ��������
		$realm = 'e-map '.str_replace('test', '', $cid);
		// ID̤���ϡʽ���
		if (!isset($_SERVER["PHP_AUTH_USER"])) {
			header("WWW-Authenticate: Basic realm=\"$realm\"");
			header("HTTP/1.0 401 Unauthorized");
			// ����󥻥����ɽ��
			header("Content-Type: text/html;charset=Shift_JIS");
			echo mb_convert_encoding("���Υڡ�����ɽ�����븢�¤�����ޤ���","SJIS","EUC-JP");
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
				header("Content-Type: text/html;charset=Shift_JIS");
				echo mb_convert_encoding("���Υڡ�����ɽ�����븢�¤�����ޤ���","SJIS","EUC-JP");
				exit;
			}
		}
	}
}

//--------------------------------------------
// �����ӥ����֥����å�
//--------------------------------------------
//-------------------
// ư����ĥ����å�
//-------------------
// �����ӥ�����
//$url = sprintf("%s?cid=%s&opt=%s",$D_SSAPI["getsdate"],$cid,$cid);	// mod 20130213 K.Masuda
$url = sprintf("%s?cid=%s&opt=%s&sys=%s",$D_SSAPI["getsdate"],$cid,$cid,"M");
$dat = ZdcHttpRead($url,0,D_SOCKET_TIMEOUT);
$status  = explode("\t",$dat[0]);

if($status[0] = "89000000") {
    $rec  = explode("\t",$dat[1]);
    $flg = intval($rec[0]);
}

if(!$flg) {
	header("Content-Type: text/html;charset=Shift_JIS");
	echo mb_convert_encoding("�����Ѥˤʤ�ޤ���[102]","SJIS","EUC-JP");
	erl("SERVICE LIMIT CHECK ERROR [$SCRIPT_NAME][".$dat[0]."]");
	exit;
}

//--------------------------------------------
// SSL���ĥ����å�		add 2010/07/20 Y.Matsukawa
//--------------------------------------------
// mod 2011/07/05 Y.Nakajima
if (isset($https_req) && $https_req) {
	//$D_SSL_ACCESS�����̵꤬�����⤷���ϡ������ͭ�뤬�ͤ���
	if (!$D_SSL_ACCESS) {
		header("Content-Type: text/html;charset=Shift_JIS");
		echo mb_convert_encoding("�����Ѥˤʤ�ޤ���[103]","SJIS","EUC-JP");
		erl("HTTPS ACCESS ERROR [$SCRIPT_NAME]");
		exit;
	}
} else {
	// mod 2011/07/05 Y.Nakajima
	if (isset($D_SSL_ACCESS) && $D_SSL_ACCESS == 2) {
		header("Content-Type: text/html;charset=Shift_JIS");
		echo mb_convert_encoding("�����Ѥˤʤ�ޤ���[104]","SJIS","EUC-JP");
		erl("HTTP ACCESS ERROR [$SCRIPT_NAME]");
		exit;
	}
}

//////////////////////////////////////////////
//
// ����¾
//
//////////////////////////////////////////////
//��ƻ�ܸ�
$D_TOD= array ( 
      "01" => "�̳�ƻ", "02" => "�Ŀ���",
      "03" => "��긩", "04" => "�ܾ븩",
      "05" => "���ĸ�", "06" => "������",
      "07" => "ʡ�縩", "08" => "��븩",
      "09" => "���ڸ�", "10" => "���ϸ�",
      "11" => "��̸�", "12" => "���ո�",
      "13" => "�����", "14" => "�����",
      "15" => "���㸩", "16" => "�ٻ���",
      "17" => "���", "18" => "ʡ�温",
      "19" => "������", "20" => "Ĺ�",
      "21" => "���츩", "22" => "�Ų���",
      "23" => "���θ�", "24" => "���Ÿ�",
      "25" => "���츩", "26" => "������",
      "27" => "�����", "28" => "ʼ�˸�",
      "29" => "���ɸ�", "30" => "�²λ���",
      "31" => "Ļ�踩", "32" => "�纬��",
      "33" => "������", "34" => "���縩",
      "35" => "������", "36" => "���縩",
      "37" => "���", "38" => "��ɲ��",
      "39" => "���θ�", "40" => "ʡ����",
      "41" => "���츩", "42" => "Ĺ�긩",
      "43" => "���ܸ�", "44" => "��ʬ��",
      "45" => "�ܺ긩", "46" => "�����縩",
      "47" => "���츩");

//�����٥�
$D_ADCD_LVL["KEN"] = 1;
$D_ADCD_LVL["SHK"] = 2;
$D_ADCD_LVL["OAZ"] = 3;
$D_ADCD_LVL["AZC"] = 4;
$D_ADCD_LVL["GIK"] = 5;
$D_ADCD_LVL["TBN"] = 6;
//�����٥롧���ꥳ���ɤη��
$D_ADCD_LEN[1] = 2;
$D_ADCD_LEN[2] = 5;
$D_ADCD_LEN[3] = 8;
$D_ADCD_LEN[4] = 11;
$D_ADCD_LEN[5] = 16;
$D_ADCD_LEN[6] = 99;

//����ꥹ�Ȥ�ɤγ��ؤޤǷ��겼���뤫��1����ƻ�ܸ���2���Զ�Į¼��3�������4�������ܡ�5�����衢6�����֡ʻ��֡�
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 6;

// i���󥷥��� ������GPS��ޥ����		add 2010/03/17 Y.Matsukawa
define("D_ICONCIE_REMIND_URL", "http://remind.its-mo.com/simple.php?uid=NULLGWDOCOMO&DCMPAKEHO=ON&q=");
define("D_ICONCIE_REMIND_EXP_URL", "http://docomo.ne.jp/service/r/iconcier/exp-remind.xhtml");

// add 2012/03/04 K.Masuda [
if (!isset($D_P_F_MAX)) $D_P_F_MAX = 100;
if (!isset($D_P_S_MAX)) $D_P_S_MAX = 100;
// add 2012/03/04 K.Masuda ]

//////////////////////////////////////////////
//
// ���ꥢ����������
//
//////////////////////////////////////////////
$AREA_INFO[0]["name"] = '�̳�ƻ����������';
$AREA_INFO[1]["name"] = '��������';
$AREA_INFO[2]["name"] = '��Φ����';
$AREA_INFO[3]["name"] = '��������';
$AREA_INFO[4]["name"] = '��������';
$AREA_INFO[5]["name"] = '�������';
$AREA_INFO[6]["name"] = '�͹�����';
$AREA_INFO[7]["name"] = '�彣����';

$AREA_INFO[0]["tod"] = '01|02|03|04|05|06|07';
$AREA_INFO[1]["tod"] = '13|14|11|12|10|09|08';
$AREA_INFO[2]["tod"] = '15|16|17|18';
$AREA_INFO[3]["tod"] = '23|19|22|20|21';
$AREA_INFO[4]["tod"] = '27|26|28|25|29|30|24';
$AREA_INFO[5]["tod"] = '34|33|35|31|32';
$AREA_INFO[6]["tod"] = '37|36|38|39';
//$AREA_INFO[7]["tod"] = '40|41|42|43|45|46|47';		mod 2010/04/06 Y.Matsukawa
$AREA_INFO[7]["tod"] = '40|41|42|43|44|45|46|47';

//////////////////////////////////////////////
//
// �ǥե��������
//
//////////////////////////////////////////////
$D_DEFAULT_W = 180;
$D_DEFAULT_H = 160;

//////////////////////////////////////////////
//
// ���������ϰϥޡ�����
//
//////////////////////////////////////////////
$D_MARGIN_PX = 32;

// add 2013/07/31 Y.Matsukawa
//------------------------------------------
// GEO���͡ʡ��콽��׸���������׸�����Ʊ���ˤʤ�ˤ����
//------------------------------------------
$D_GEO_ESC_JO['�콽��'] = '�ҥ������奦���祦';


//==========================================================
if($debug){
//	$http_header = apache_request_headers(); //getallheaders();
//	foreach ($http_header as $hash_key => $tmp) {
//		dbl("APACHE_HEADER[$hash_key]=[$tmp]");
//	}
//	dbl("----------------------------");
	foreach ($_SERVER as $hash_key => $tmp) {
		// mod 2011/07/05 Y.Nakajima
		//if(ereg("^HTTP_X_",$hash_key)) dbl("_SERVER[$hash_key]=[$tmp]");
		if(preg_match("^HTTP_X_",$hash_key, $matches)) dbl("_SERVER[$hash_key]=[$tmp]");
	}
	dbl("----------------------------");
	foreach ($_POST as $hash_key => $tmp) {
		dbl("_POST[$hash_key]=[$tmp]");
	}
//	dbl("----------------------------");
}
//==========================================================
//********************************************************************
//* �ǥХå��������
//********************************************************************
function dbl($str){
	global $debug;
	// mod 2011/07/05 Y.Nakajima
	if(!isset($debug) || !$debug){ return; }
	log_rotate();
	@error_log(date("Y/m/d H:i:s").":".$_SERVER["SCRIPT_NAME"].":".$str."\n", 3, "/var/tmp/mobile.log");
}
//********************************************************************
//* ���顼�����������
//********************************************************************
function erl($str){
	log_rotate();
	@error_log(date("Y/m/d H:i:s").":".$_SERVER["SCRIPT_NAME"].":ERR:".$str."\n", 3, "/var/tmp/mobile.log");
}
//********************************************************************
//* ���������ơ������
//********************************************************************
function log_rotate(){
	// ���ϥ����ե����륵�����������ͤ�ۤ������͡��ष�ƥХå����å�
	// ��������ϡ�������Τ��ݻ����뤳�Ȥˤ��Ƥ�����
	if(filesize("/var/tmp/mobile.log") > (10 * 1024 * 1000)){
		if(file_exists("/var/tmp/mobile_bef.log")){
			@unlink("/var/tmp/mobile_bef.log");
		}
		@rename("/var/tmp/mobile.log", "/var/tmp/mobile_bef.log");
	}
}

//////////////////////////////////////////////
//�������ޥ���������ɤ߹���
//////////////////////////////////////////////
@include($D_DIR_COMPANY . "setting_option.inc");	// add 2008/08/22 matsukawa

// add 2012/01/10 Y.Matsukawa
//--------------------------------------------
// �������२�顼
//--------------------------------------------
if (isset($D_CUST_ERRMSG) && $D_CUST_ERRMSG != '') {
	header("Content-Type: text/html;charset=Shift_JIS");
	// del 2013/08/30 Y.Matsukawa [
	//	echo mb_convert_encoding($D_CUST_ERRMSG, "SJIS", "EUC-JP");
	//	erl("CUSTOM ERROR [$SCRIPT_NAME]");
	// del 2013/08/30 Y.Matsukawa ]
	// add 2013/08/30 Y.Matsukawa [
	erl($D_CUST_ERRMSG);
	$HtmlTemplate = new HtmlTemplate();
	$errbody['errmsg'] = $D_CUST_ERRMSG;
	if (isset($body_cst)) $errbody = array_merge($errbody, $body_cst);
	$err_html = $HtmlTemplate->t_buffer($D_DIR_COMPANY.'err.tpl', $errbody);
	echo mb_convert_encoding($err_html, 'SJIS', 'EUC-JP');
	// add 2013/08/30 Y.Matsukawa ]
	exit;
}

//--------------------------------------------
// ������쥯�ȴ�Ϣ
//--------------------------------------------
// add 2012/10/26 K.Masuda [
$D_LV_MOBTOSMT = array(	// ����			->	���ޥ�
	'1'  => '6',		// 1:33,129m	->	6:1/50��
	'2'  => '8',		// 2:11,388m	->	8:1/10��
	'3'  => '9',		// 3:4,658m		->	9:1/5��
	'4'  => '10',		// 4:2,458m		->	10:1/2��
	'5'  => '11',		// 5:1,100m		->	11:1/1��5000
	'6'  => '13',		// 6:485m		->	13:1/7500
	'7'  => '14',		// 7:242m		->	14:1/3500
	'8'  => '15',		// 8:129m		->	15:1/1500
	'9'  => '15',		// 9:97m		->	15:1/1500
);
// add 2012/10/26 K.Masuda ]

// ���ޥۤإ�����쥯������ϿޤǤϤʤ��ܺ٤ˤ��륪�ץ����		add 2012/12/17 H.Osamoto
if(!isset($REDIRECT_SMT_DETAIL)) $REDIRECT_SMT_DETAIL = '';
// ���������̹�������������ޥ���		add 2012/12/17 H.Osamoto
if(!isset($D_KANA_DEN)) $D_KANA_DEN = '';			// ���������̹���ե饰

// add 2011/03/31 Y.Matsukawa [
$REDIRET_SMT_URL = "http://$D_DOMAIN_G/smt/$cid/";
$REDIRECT_PC_URL = "http://$D_DOMAIN_G/p/$cid/";		// add 2016/07/04 Y.Matsukawa
// mod 2011/07/05 Y.Nakajima

// add 2016/12/05 Y.Uesugi [
if ($D_REDIRECT_URL_SSL) {
	$REDIRET_SMT_URL = "https://$D_DOMAIN_G/smt/$cid/";
	$REDIRECT_PC_URL = "https://$D_DOMAIN_G/p/$cid/";
}
// add 2016/12/05 Y.Uesugi ]

//if (ereg('iPhone', $_SERVER['HTTP_USER_AGENT'])) {
if (strpos($_SERVER['HTTP_USER_AGENT'], 'iPhone')) {
	$UA_IPHONE = true;
// mod 2011/07/05 Y.Nakajima
//} else if (ereg('Android', $_SERVER['HTTP_USER_AGENT'])) {
} else if (strpos($_SERVER['HTTP_USER_AGENT'], 'Android')) {
	$UA_ANDROID = true;
}

// add 2016/07/04 Y.Matsukawa [
// ���ޥۥ�����������PC�إ�����쥯��
if (($UA_IPHONE && $D_IPHONE_REDIRECT_TO_PC) || ($UA_ANDROID && $D_ANDROID_REDIRECT_TO_PC)) {
	if(isset($id) && $id)		$REDIRECT_PC_URL .= "dtl/".$id."/";
	if(isset($kid) && $kid)		$REDIRECT_PC_URL .= "dtl/".$kid."/";
	if(isset($ksid) && $ksid)	$REDIRECT_PC_URL .= "dtl/".$ksid."/";
	header('Location: '.$REDIRECT_PC_URL);
	exit;
}
// add 2016/07/04 Y.Matsukawa ]

if (($UA_IPHONE && $D_IPHONE_REDIRECT) || ($UA_ANDROID && $D_ANDROID_REDIRECT)) {
	// add 2011/09/28 K.masuda [
	// mod 2011/11/02 Y.Nakajima [
	// mod 2012/12/17 H.Osamoto [
	//	if(isset($id) && $id)$REDIRET_SMT_URL = $REDIRET_SMT_URL."map/".$id."/";
	//	if(isset($kid) && $kid)$REDIRET_SMT_URL = $REDIRET_SMT_URL."map/".$kid."/";
	//	if(isset($ksid) && $ksid)$REDIRET_SMT_URL = $REDIRET_SMT_URL."map/".$ksid."/";
	if(isset($REDIRECT_SMT_DETAIL) && $REDIRECT_SMT_DETAIL) {
		if(isset($id) && $id)$REDIRET_SMT_URL = $REDIRET_SMT_URL."inf/".$id."/";
		if(isset($kid) && $kid)$REDIRET_SMT_URL = $REDIRET_SMT_URL."inf/".$kid."/";
		if(isset($ksid) && $ksid)$REDIRET_SMT_URL = $REDIRET_SMT_URL."inf/".$ksid."/";
	} else {
		if(isset($id) && $id)$REDIRET_SMT_URL = $REDIRET_SMT_URL."map/".$id."/";
		if(isset($kid) && $kid)$REDIRET_SMT_URL = $REDIRET_SMT_URL."map/".$kid."/";
		if(isset($ksid) && $ksid)$REDIRET_SMT_URL = $REDIRET_SMT_URL."map/".$ksid."/";
	}
	// mod 2012/12/17 H.Osamoto ]
	//	if(isset($lat) && isset($lon) && $lat && $lon)$REDIRET_SMT_URL = $REDIRET_SMT_URL."link/lat=".$lat.",lon=".$lon."/?nm=".$nm."&lv=".$lv."&icn=".$icn;	2012/07/18 H.Osamoto mod
	//if(isset($lat) && isset($lon) && $lat && $lon)$REDIRET_SMT_URL = $REDIRET_SMT_URL."link/lat=".$lat.",lon=".$lon."/?nm=".urlencode($nm)."&lv=".$lv."&icn=".$icn;	mod 2012/10/26 K.Masuda
	if(isset($lat) && isset($lon) && $lat && $lon)$REDIRET_SMT_URL = $REDIRET_SMT_URL."link/lat=".$lat.",lon=".$lon."/?nm=".urlencode($nm)."&lv=".$D_LV_MOBTOSMT[$lv]."&icn=".$icn;
	// add 2012/03/29 K.Masuda [
	//if(isset($addr) && $addr)$REDIRET_SMT_URL = $REDIRET_SMT_URL."link/addr=".urlencode($addr)."/?nm=".urlencode($nm)."&lv=".$lv."&icn=".$icn;	mod 2012/10/26 K.Masuda
	if(isset($addr) && $addr)$REDIRET_SMT_URL = $REDIRET_SMT_URL."link/addr=".urlencode($addr)."/?nm=".urlencode($nm)."&lv=".$D_LV_MOBTOSMT[$lv]."&icn=".$icn;
	// add 2012/03/29 K.Masuda ]
	// mod 2011/11/02 Y.Nakajima ]
	// add 2011/09/28 K.masuda ]
	// add 2012/03/04 K.masuda [
	for($pcnt=1,$all_p_f="";$pcnt<=$D_P_F_MAX;$pcnt++){
		if (isset(${'p_f'.$pcnt}) && ${'p_f'.$pcnt}) {
			$all_p_f .= "&p_f".$pcnt."=".${'p_f'.$pcnt};
		}
	}
	if( $all_p_f != "" ){
		$all_p_f = trim($all_p_f, "&");

		// mod 2016/03/28 Y.Uesugi [
		if(strpos($REDIRET_SMT_URL, '?') !== false){
			$REDIRET_SMT_URL .= "&";
		} else {
			$REDIRET_SMT_URL .= "?";
		}

		if(isset($id) && $id){$REDIRET_SMT_URL .= $all_p_f;}
		else if(isset($kid) && $kid){$REDIRET_SMT_URL .= $all_p_f;}
		else if(isset($ksid) && $ksid){$REDIRET_SMT_URL .= $all_p_f;}
		else if(isset($lat) && isset($lon) && $lat && $lon){$REDIRET_SMT_URL .= $all_p_f;}
		else {$REDIRET_SMT_URL .= $all_p_f;}
		// mod 2016/03/28 Y.Uesugi ]
	}
	// add 2012/03/04 K.masuda ]
	// add 2012/12/17 H.Osamoto [ 
	for($pcnt=1,$all_p_s="";$pcnt<=$D_P_S_MAX;$pcnt++){
		if (isset(${'p_s'.$pcnt}) && ${'p_s'.$pcnt}) {
			$all_p_s .= "&p_s".$pcnt."=".${'p_s'.$pcnt};
		}
	}
	if( $all_p_s != "" ){
		$all_p_s = trim($all_p_s, "&");

		// mod 2016/03/28 Y.Uesugi [
		if(strpos($REDIRET_SMT_URL,'?') !== false){
			$REDIRET_SMT_URL .= "&";
		} else {
			$REDIRET_SMT_URL .= "?";
		}

		if(isset($id) && $id){$REDIRET_SMT_URL .= $all_p_s;}
		else if(isset($kid) && $kid){$REDIRET_SMT_URL .= $all_p_s;}
		else if(isset($ksid) && $ksid){$REDIRET_SMT_URL .= $all_p_s;}
		else if(isset($lat) && isset($lon) && $lat && $lon){$REDIRET_SMT_URL .= $all_p_s;}
		else {$REDIRET_SMT_URL .= $all_p_s;}
		// mod 2016/03/28 Y.Uesugi ]
	}
	
	if(isset($D_KANA_DEN) && $D_KANA_DEN) $REDIRET_SMT_URL = $REDIRET_SMT_URL."&p_s3=".$kid;
	// add 2012/12/17 H.Osamoto ] 

	header('Location: '.$REDIRET_SMT_URL);
	exit;
}
// add 2011/03/31 Y.Matsukawa [

// add 2012/01/04 Y.Matsukawa
//--------------------------------------------
// �ǡ���������CID
//--------------------------------------------
// �����ǡ���
if (isset($D_DATA_CID) && $D_DATA_CID != '') {
	$D_DATA_CID .= (strpos($D_CID, 'test') ? 'test' : '');
} else {
	$D_DATA_CID = $D_CID;
}
// ������������
if (isset($D_ICON_CID) && $D_ICON_CID != '') {
	$D_ICON_CID .= (strpos($D_CID, 'test') ? 'test' : '');
} else {
	$D_ICON_CID = $D_CID;
}

// optʣ�����ܻ����COL_xx=1@COL_xx=1�ˤ�Ϣ�����		add 2010/05/17 Y.Matsukawa
if (!isset($D_OPT_U_COND)) $D_OPT_U_COND = "AND";
// optʣ�����ܻ����AND�����Ϣ�뤹�����				add 2010/05/17 Y.Matsukawa
if (!isset($D_OPT_EX_AND_COND)) $D_OPT_EX_AND_COND = array();
// ����θ�����opt�����̵��������		add 2011/08/25 Y.Matsukawa
if (!isset($D_OPT_NULL_SRCH)) $D_OPT_NULL_SRCH = array();

// optcdʣ�������optcd=1@2@3�ˤ�Ϣ�����		add 2016/03/29 Y.Matsukawa
if (!isset($D_OPTCD_U_COND)) $D_OPTCD_U_COND = "OR";

// add 2010/06/21 Y.Matsukawa [
// �Ǵ���������������Ͽޤʤ���
if (!isset($D_NSHOP_KNSU)) $D_NSHOP_KNSU = $D_SEARCH_LIST_PAGE;
// �Ǵ���������������Ͽ��դ���
if (!isset($D_NSHOP_MAP_KNSU)) $D_NSHOP_MAP_KNSU = 5;
if (!isset($D_NSHOP_MAP_LIST_PAGE)) $D_NSHOP_MAP_LIST_PAGE = 5;//1�ڡ�����������	add 2016/06/01 Y.Matsukawa
// �Ǵ���������n���Ǵ�������nm���Ǵ���Ͽޡ�		add 2016/06/01 Y.Matsukawa
if (!isset($D_NSHOP_DIST)) $D_NSHOP_DIST = 'n';
// add 2010/06/21 Y.Matsukawa ]
// ��Ȳ�������		add 2012/02/13 Y.Matsukawa
if (!isset($D_USE_CP_IMG)) $D_USE_CP_IMG = 0;
//�������
if(!isset($D_KLIST_PAGING)) $D_KLIST_PAGING = 0;	//�ڡ�����̵ͭ	add 2012/05/14 Y.Matsukawa
if(!isset($D_KLIST_PAGE)) $D_KLIST_PAGE = 10;		//���ڡ����Կ�		add 2012/05/14 Y.Matsukawa
// �Ǵ����߸������	add 2012/12/17 H.Osamoto
if (!isset($D_NPOI_KNSU)) $D_NPOI_KNSU = 20;
if (!isset($D_NPOI_RAD)) $D_NPOI_RAD = 2000;

// �����ǡ����������Υ������ޥ�������		add 2012/11/19 Y.Matsukawa
if(!isset($D_NKYOTEN_CUST)) $D_NKYOTEN_CUST = '';			// �Ǵ����
if(!isset($D_KYOTENID_CUST)) $D_KYOTENID_CUST = '';			// ����ID
if(!isset($D_KYOTENLIST_CUST)) $D_KYOTENLIST_CUST = '';		// ��������

//���ꥢ����NULL�ξ���ɽ��ʸ��		add 2015/06/02 Y.Uesugi
if(!isset($D_SEARCH_SHOPA_DISPNM_NULL)) $D_SEARCH_SHOPA_DISPNM_NULL = "(����¾)";

//Ź�ް��������Ƚ����		add 2015/06/01 Y.Uesugi
if(!isset($D_SHOPW_KYOTEN_SORT)) $D_SHOPW_KYOTEN_SORT = "";//Ź�ޥե꡼��ɸ���
if(!isset($D_SHOPA_KYOTEN_SORT)) $D_SHOPA_KYOTEN_SORT = "";//���ꥢ����

// JCN�͸����������ޥ����ʱ��پ���ɽ����		add 2012/11/19 Y.Matsukawa
if(!isset($D_JCN_UNKYU_TOP)) $D_JCN_UNKYU_TOP = 0;			// ���پ���ɽ��
if(!isset($D_JCN_UNKYU_JKN)) $D_JCN_UNKYU_JKN = '';			// ���پ���ɽ�����

// �Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ�������������		add 2013/04/15 H.Osamoto
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;
// ����ꥹ�ȸ��������ꥢ����		add 2013/05/30 Y.Matsukawa
if(!isset($D_ADDRLIST_AREA)) $D_ADDRLIST_AREA = 0;
// ��ƻ�ܸ������|���ڤ������		add 2013/05/30 Y.Matsukawa
if(!isset($D_SELECT_TODS)) $D_SELECT_TODS = '';
// ���ꥢ���������Ǥ򣱳��ءʻԶ�Į¼�ʤ��ˤ�ư�����		add 2013/06/06 Y.Matsukawa
if(!isset($D_CL_NO_SHK)) $D_CL_NO_SHK = 0;

// ͹���ֹ渡��0����˽���ꥹ�Ȥ����ܡʥ�ޥȱ�͢�������ޥ�����		add 2013/07/31 H.Osamoto
if(!isset($D_ZIPW0_GOTO_PAGE)) $D_ZIPW0_GOTO_PAGE = '';
// ͹���ֹ渡�����������åסʺǴ�������ľ�����ܡ�		add 2014/07/10 Y.Matsukawa
if(!isset($D_ZIPW_SKIP_LIST)) $D_ZIPW_SKIP_LIST = 0;

// ���ܥ������֡ʥ�ޥȱ�͢�������ޥ�����		add 2013/07/31 H.Osamoto
if(!isset($D_YTC_BACK_BUTTON)) $D_YTC_BACK_BUTTON = '';

// �ݥꥴ���⳰Ƚ�ꥫ���		add 2014/03/10 H.Osamoto
if(!isset($D_POLY_COL)) $D_POLY_COL = '';

// GPS��������		add 2015/11/18 Xuan Chien
if(!isset($D_MGPS_LOG)) $D_MGPS_LOG = '';

// ����͹����͹���ֹ渡��		add 2016/06/13 Y.Matsukawa
if(!isset($D_JPPOST_SEARCH_ZIP)) $D_JPPOST_SEARCH_ZIP = 0;

// �ܺ٥��顼���Υ�����쥯����URL		add 2016/07/04 N.Wada
if(!isset($D_KID_NOTFOUND_REDIRECT_URL)) $D_KID_NOTFOUND_REDIRECT_URL = "";

// PCü���Υ�����쥯����URL		add 2016/07/05 N.Wada
if(!isset($D_UA_PC_REDIRECT_URL)) $D_UA_PC_REDIRECT_URL = "";
// ����ü���Υ�����쥯����URL		add 2016/07/05 N.Wada
if(!isset($D_UA_UNKOWN_REDIRECT_URL)) $D_UA_UNKOWN_REDIRECT_URL = "";

// �ܺ٤Υإå����ƥ�ץ졼�Ȥˡ������ǡ��������Υե饰���Ϥ�(0:�Ϥ��ʤ���1:�Ϥ�)		add 2016/07/28 N.Wada
if(!isset($D_DTL_HEADER_TEMPLATE_COL_EXIST_FLG)) $D_DTL_HEADER_TEMPLATE_COL_EXIST_FLG = 0;

// canonical�����˽��Ϥ���URL		add 2017/03/24 N.Wada
if(!isset($D_CANONICAL_URL)) $D_CANONICAL_URL = "";

// add 2017/05/11 H.Yasunaga ��ޥ� ���å����������ƥ��������б� [
if (!isset($D_YTC_SECURITY_CODE)) $D_YTC_SECURITY_CODE = 0;
// add 2017/05/11 H.Yasunaga ]

// add 2017/05/30 H.Yasunaga ��ޥ� ���å����������ƥ��������б� ľ�ܾܺٲ��̤����ܤ��ʤ� [
if (!isset($D_YTC_SECURITY_CODE_NO_DIRECT_DTL)) $D_YTC_SECURITY_CODE_NO_DIRECT_DTL = 0;
// add 2017/05/30 H.Yasunaga ]
?>