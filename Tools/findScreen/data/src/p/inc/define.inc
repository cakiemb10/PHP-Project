<?php
// ------------------------------------------------------------
// 2011/10/15 Y.Matsukawa	��������
// 2011/12/05 Y.Matsukawa	��CID����
// 2011/12/20 Y.Matsukawa	�ƥ�ץ졼������ե�������ǥ��顼��å����������åȤ��줿�饨�顼����ɽ��
// 2011/12/21 Y.Matsukawa	��ե�������å�����https/http����̤��ʤ��⡼��
// 2012/02/03 N.Wada		���ޥۤ���Υ����������Υ�����쥯��
// 2012/03/12 Y.Matsukawa	���ޥۥ�����쥯�ȡʳƼ���³I/F�б���
// 2012/05/21 H.osamoto		���Զ�罤���۽���ꥹ�ȸ�����Ԥä��ݤ˥ѥ󤯤�������ʸ����������
// 2012/07/04 H.osamoto		�ƥ�ץ졼�Ȥ˥ɥᥤ�������Ϥ�
// 2012/07/06 H.Osamoto		�ƥ�ץ졼�Ȥ�Ǥ�դ��ѿ�������Ϥ�
// 2012/07/30 Y.Matsukawa	error_reporting���Һ��
// 2012/09/07 Y.Matsukawa	���Զ�罤����Ǥ�եѥ�᡼�������ͤ�Ⱦ�ѥ��ڡ����Τߤξ�硢�ͤ��ä���
// 2012/11/01 Y.Matsukawa	�ƥ�ץ졼�Ȥ���HTML�ե�����̾�򻲾�
// 2013/04/11 H.Osamoto		�ץ�ӥ塼��ǽ�����Ѳ�ǽ�˽���
// 2013/07/23 Y.Matsukawa	���Զ�罤����httpsư������Ǵ�Ź�ް�������ܺ٤ؤΥ�󥯤�http�ˤʤäƤ��ޤ�
// 2013/07/26 Y.Matsukawa	�������२�顼����ɽ���Υ����ߥ󥰤��������λ����ѹ�
// 2013/11/28 Y.Matsukawa	�������ƥ��б���XSS��
// 2014/05/20 Y.Matsukawa	�ƥ�ץ졼�Ȥ���CID����
// 2014/10/06 Y.Matsukawa	Ϣ�֥�������
// 2015/01/08 Y.Matsukawa	ǯ��ƥ�ץ졼�Ȥ��Ϥ�
// 2015/02/25 Y.Matsukawa	�������뻲����Υɥᥤ�������$D_DOMAIN_L���ѹ�
// 2015/03/16 Y.Matsukawa	�ʤ���ߡ�Ǥ�ե�������ʬ����
// 2015/08/27 Y.Matsukawa	�������ƥ��б���SQL Injection��
// 2015/10/28 Y.Uesugi		��ޥȱ�͢���� ���󥿡��������
// 2015/11/11 Y.Matsukawa	�إå�����charset����
// 2015/11/13 N.Wada		�������ȥ�å�����
// 2016/02/03 N.Wada		����Ƚ��
// 2016/05/13 N.Wada		�ѥ󤯤�Cookie�Υ�����Ǥ�դ�ʸ������ɲ�
// 2016/07/27 Y.Uesugi		SSL���Ļ��Υ�������CGI SSL�б�
// 2017/03/14 H.Yasunaga	����͹�إ������ޥ���
// 2017/04/19 H.Yasunaga	����͹�إ������ޥ���
// 2017/05/14 Y.Matsukawa	XSS�к�
// ------------------------------------------------------------
$script_name = basename($_SERVER['SCRIPT_NAME']);
// HTML�ե�����̾		add 2012/11/01 Y.Matsukawa
if ($script_name) {
	$tpl_htmlflg = str_replace('.', '_', $script_name);
	$tpl[$tpl_htmlflg] = 1;
}

//------------------------------------------
// HOME�ǥ��쥯�ȥ�
//------------------------------------------
$arr_dir = explode('/', dirname($_SERVER['SCRIPT_NAME']));
$homedir = implode('/', $arr_dir).'/';

// add 2011/12/21 Y.Matsukawa
//------------------------------------------
// ��ե���
//------------------------------------------
if (isset($_SERVER['HTTP_REFERER']) && $_SERVER['HTTP_REFERER'] != '') {
	$HTTP_REFERER = $_SERVER['HTTP_REFERER'];
} else {
	$HTTP_REFERER = '';
}

//------------------------------------------
// ���ID
//------------------------------------------
$cid = array_pop($arr_dir);
$D_LOG_CID = $cid;
if(strpos($cid,'_prev') > -1){
	// ���ID�ˡ�_prev�פΥ�����ɤ�������ϡ��ƥ�ץ졼�ȥ������ޥ������Υץ�ӥ塼
	$cid = substr($cid, 0, strpos($cid,'_prev'));
	$D_PREVIEW = true;
} else {
	$D_PREVIEW = false;
}
$D_CID = $cid;
${'_'.$_SERVER['REQUEST_METHOD']}['cid'] = $cid;/* ��d_serv_emap.inc���cid��Ƽ������Ƥ��ޤ��Τ� */

$D_PC2 = true;

$tpl['D_YEAR'] = date('Y');		// add 2015/01/08 Y.Matsukawa

//------------------------------------------
// �Ķ����
//------------------------------------------
require_once('d_serv_emap.inc');
require_once("/home/emap/src/p/inc/xml_util.inc");	// add 2015/11/09 Y.Uesugi

//------------------------------------------
// �١����ǥ��쥯�ȥ�
//------------------------------------------
// add 2013/07/23 Y.Matsukawa [
// httpsư������Ǵ�Ź�ް�����http�ǸƤӽФ���뤻���ǰ����Υ�󥯤�http�ˤʤäƤ��ޤ��Τ����
if (isset($_GET['https_req']) && $_GET['https_req'] && $protocol != 'https') {
	$protocol = 'https';
}
// add 2013/07/23 Y.Matsukawa [
$D_DIR_BASE_G  = "$protocol://".$D_DOMAIN_G.$homedir;
//$D_DIR_BASE_L  = "http://".$EMAP_SSAPI_SRV.$homedir;		mod 2015/02/25 Y.Matsukawa
$D_DIR_BASE_L  = "http://".$D_DOMAIN_L.$homedir;
$D_DIR_COMPANY = "$protocol://".$D_DOMAIN_G.$homedir.'company/'.$cid.'/';

//------------------------------------------
// �ѥ󤯤���Cookie�����
//------------------------------------------
$D_COOKIENAME_HISTORY = 'EMAP_P_HISTORY_'.$D_CID;

$err = false;
//------------------------------------------
// �ǥХå�
//------------------------------------------
if($D_EMAP_ENV == 'dev')
	$debug = true;
else
	$debug = false;
//if($debug){ error_reporting (E_ALL^E_NOTICE); } else { error_reporting (0); }		del 2012/07/30 Y.Matsukawa

define('D_DEBUG_LOG_FILE', '/var/tmp/p_debug_'.date('Ymd').'.log');
define('D_ERROR_LOG_FILE', '/var/tmp/p_error_'.date('Ymd').'.log');

// add 2016/02/03 N.Wada
//------------------------------------------
// ����Ƚ��
//------------------------------------------
require_once('/home/emap/src/p/inc/carrier.inc');
$carrier = new CARRIER($_SERVER['HTTP_USER_AGENT']);

//------------------------------------------
// �������
//------------------------------------------
require_once('ZdcCommonFunc.inc');
require_once('htmltemplate.inc');
require_once('/home/emap/src/p/inc/function.inc');
require_once('/home/emap/src/p/inc/crypt.inc');

//dbl("homedir=$homedir");
//dbl("cid=$cid");
//dbl("D_CID=$D_CID");

//------------------------------------------
// �ѥ�᡼�������ʥ��˥�������
//------------------------------------------
// ���󥰥륯�����Ȥ����٤��ѥ�᡼��
$D_REMOVE_QUOTE_PARAMS = array(
'type',
'adcd',
'area',
'kid',
'lat',
'lon',
'lv',
'icn',
'datum',
);
// ���֥륯�����Ȥȥ��󥰥륯�����Ȥ����٤��ѥ�᡼��		add 2013/11/28 Y.Matsukawa
$D_REMOVE_XSS_SIGN = array(
'area1',
'area2'		// add 2015/08/27 Y.Matsukawa
);
// ���֥륯�����Ȥȥ��󥰥륯�����Ȥ������ִ����٤��ѥ�᡼��		add 2013/11/28 Y.Matsukawa
$D_CNV2W_XSS_SIGN = array(
'keyword',
);
// HTML�ü�ʸ����&��<��>��"��'�ˤ򥨥������פ��٤��ѥ�᡼��		add 2017/05/14 Y.Matsukawa
$D_HTMLSPECIALCHARS = array(
'areaptn',
'adcd'
);
// JavaScript�ü�ʸ����\��"��'��/��<��>��0x0D(CR)��0x0A(LF)�ˤ����٤��ѥ�᡼��		add 2017/05/14 Y.Matsukawa
$D_REMOVE_JSCHARS = array(
's_lat',
's_lon',
'e_lat',
'e_lon',
'srchplace'
);
// �ե饰���ܤΥ��˥������ʿ����ʳ����ޤޤ�Ƥ�����0���ִ���		add 2013/11/28 Y.Matsukawa
$D_SANITIZE_FLAG_PARAMS = array(
'slogflg',
'printflg',
'detailflg',
);
$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
if ($_VARS['enc']) {
	switch ($_VARS['enc']) {
		case 'EUC':
		case 'EUC-JP':
		case 'SJIS':
		case 'UTF8':
		case 'UTF-8':
			$enc = $_VARS['enc'];
			break;
		default:
			$enc = 'EUC';

	}
	$_VARS['enc'] = $enc;
// add 2012/05/21 H.osamoto [
} else {
	$enc = 'EUC';
	// add 2017/03/13 H.Yasunaga ����͹�إ������ޥ��� [
	// �Ǵ�������������Τ�nlist�����
	// mod 2017/04/19 H.Yasunaga ����͹�إ������ޥ��� [
	//if (($cid == 'jppost15' || $cid == 'jppost15test') && ($script_name != "nlist.htm") ) {
	if (($cid == 'jppost15' || $cid == 'jppost15test' || $cid == 'jppost17' || $cid == 'jppost17test' ) && ($script_name != "nlist.htm") ) {
	// mod 2017/04/19 H.Yasunaga ]
		$enc = 'UTF8';
	}
	// add 2017/03/13 H.Yasunaga ]
	$_VARS['enc'] = $enc;
// add 2012/05/21 H.osamoto ]
}
foreach($_VARS as $key=>$val) {
	if ($key == 'cid') continue;
	if (is_string($key) && is_string($val)) {
		// add 2015/03/16 Y.Matsukawa [
		// nlist.htm��jkn�ѥ�᡼����js�����Ϥ����Τ�UTF-8�Ȥ��Ʋ��
		if ($script_name == 'nlist.htm' && $key == 'jkn') {
			$val = mb_convert_encoding($val, 'eucJP-win', 'UTF-8');
		// add 2015/03/17 Y.Matsukawa [
		// nlist.htm,msg.htm��cond�ѥ�᡼����js�����Ϥ����Τ�UTF-8�Ȥ��Ʋ��
		} else if (($script_name == 'nlist.htm' || $script_name == 'msg.htm') && strpos($key, 'cond')===0) {
			$val = mb_convert_encoding($val, 'eucJP-win', 'UTF-8');
		// add 2015/03/17 Y.Matsukawa ]
		} else {
		// add 2015/03/16 Y.Matsukawa ]
			//$val = ZdcConvertEncoding(trim($val));		mod 2012/09/07 Y.Matsukawa
			$val = ZdcConvertEncoding($val);
		}
		if($key != '') {
			// ���󥰥륯�����Ƚ���
			if ($val != '' && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
				$val = mb_ereg_replace("'", '', $val);
			}
			// ���֥륯�����Ȥȥ��󥰥륯�����Ȥ����		add 2013/11/28 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_XSS_SIGN)) {
				$val = mb_ereg_replace('"', '', $val);
				$val = mb_ereg_replace("'", '', $val);
			}
			// ���֥륯�����Ȥȥ��󥰥륯�����Ȥ������ִ�		add 2013/11/28 Y.Matsukawa
			if ($val != '' && in_array($key, $D_CNV2W_XSS_SIGN)) {
				$val = mb_ereg_replace('"', '��', $val);
				$val = mb_ereg_replace("'", '��', $val);
			}
			// HTML�ü�ʸ����&��<��>��"��'�ˤ򥨥�������		add 2017/05/14 Y.Matsukawa
			if ($val != '' && in_array($key, $D_HTMLSPECIALCHARS)) {
				$val = htmlspecialchars($val, ENT_QUOTES);
			}
			// JavaScript�ü�ʸ����\��"��'��/��<��>��0x0D(CR)��0x0A(LF)�ˤ����		add 2017/05/14 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_JSCHARS)) {
				$val = mb_ereg_replace("[\\\"'\/<>\r\n]", '', $val);
			}
			// �ե饰���ܤΥ��˥������ʿ����ʳ����ޤޤ�Ƥ�����0���ִ���		add 2013/11/28 Y.Matsukawa
			if ($val != '' && in_array($key, $D_SANITIZE_FLAG_PARAMS)) {
				if (!ctype_digit($val)) $val = '0';
			}
			${$key} = $val;
			$_VARS[$key] = $val;
		}
	}
}

//------------------------------------------
// ��������
//------------------------------------------
$wk = parse_url($_SERVER['REQUEST_URI']);
$_SERVER['HTTP_HOST'] = ($_SERVER['HTTP_HOST'] == '' ? $wk['host'] : $_SERVER['HTTP_HOST']);

//------------------------------------------
// �ȼ����к��ʥ����������ȥ�����ץƥ��󥰡�
//------------------------------------------
// Host�إå����Ѥ��б�
$_SERVER['HTTP_HOST'] = htmlspecialchars($_SERVER['HTTP_HOST'], ENT_QUOTES);

//------------------------------------------
// �����ƥ����
//------------------------------------------
require_once('/home/emap/src/p/inc/define_system.inc');

//------------------------------------------
// �ƥ�ץ졼�ȥǥ��쥯�ȥ�
//------------------------------------------
if($D_PREVIEW){
	// mod 2013/04/11 H.Osamoto [
	//	$D_TEMPLATE_DIR = "/home/emap/httpd/emap_tpl/tpl_edit_p/company/$cid/";
	//	$D_HTTP_DIR_COMPANY = "/emap_tpl/tpl_edit_p/company/$cid/";
	$D_TEMPLATE_DIR = "/home/emap/httpd/emap_tpl/tpl_edit_pc2/company/$cid/";
	$D_HTTP_DIR_COMPANY = "/emap_tpl/tpl_edit_pc2/company/$cid/";
	// mod 2013/04/11 H.Osamoto ]
} else {
	$D_TEMPLATE_DIR = "./company/$cid/";
	$D_HTTP_DIR_COMPANY = dirname($_SERVER['SCRIPT_NAME'])."/company/$cid/";
}
if(!file_exists($D_TEMPLATE_DIR)){
	header('Content-Type: text/html;charset=UTF-8');
	erl("$cid - template dir NOT FOUND [$D_TEMPLATE_DIR]");
	echo mb_convert_encoding('�����ʥ��������Ǥ���','UTF-8','EUC-JP');
	exit;
}
$D_SYSDIR_COMPANY = $D_TEMPLATE_DIR;

//------------------------------------------
// ����¾����
//------------------------------------------
$D_PFLG = 2;
$D_DATUM = 'TOKYO';
// �����ط�
$LOG_MODE = 'PC2';
// �̿��Υ����ॢ���Ȼ���
$D_AJAX_TIMEOUT   = 10000;
$D_SOCKET_TIMEOUT = 10000;
// �Ǵ�긡��Ⱦ�¾���͡�API�����¡�
$API_RAD_MAX = 50000;

//------------------------------------------
// �ƥ�ץ졼�Ȥ�����ե�����
//------------------------------------------
include($D_SYSDIR_COMPANY . 'setting.inc');		// ����ե�����
include($D_SYSDIR_COMPANY . 'setting_option.inc');

//--------------------------------------------
// ����¾
//--------------------------------------------
require_once('/home/emap/src/p/inc/define_design.inc');
require_once('/home/emap/src/p/inc/define_action.inc');
require_once('/home/emap/src/p/inc/define_msg.inc');

// P3P����ѥ��ȥݥꥷ��		2012/05/10 Y.Matsukawa
if(isset($D_P3P_HEADER) && $D_P3P_HEADER) header('P3P: CP="'.$D_P3P_HEADER.'"');

// Ϣ�֥����������ǥե������		2014/10/06 Y.Matsukawa
if (is_array($D_SEQ_ICON_INFO) && count($D_SEQ_ICON_INFO)) {
	foreach ($D_SEQ_ICON_INFO as $k=>$a) {
		if (!$D_SEQ_ICON_INFO[$k]['width']) $D_SEQ_ICON_INFO[$k]['width'] = 24;
		if (!$D_SEQ_ICON_INFO[$k]['height']) $D_SEQ_ICON_INFO[$k]['height'] = 24;
		if (!$D_SEQ_ICON_INFO[$k]['fontWeight']) $D_SEQ_ICON_INFO[$k]['fontWeight'] = 'normal';
		if (!$D_SEQ_ICON_INFO[$k]['fontFamily']) $D_SEQ_ICON_INFO[$k]['fontFamily'] = 'Arial,sans-serif';
		if (!$D_SEQ_ICON_INFO[$k]['fontSize']) $D_SEQ_ICON_INFO[$k]['fontSize'] = '10pt';
		if (!$D_SEQ_ICON_INFO[$k]['borderColor']) $D_SEQ_ICON_INFO[$k]['borderColor'] = 'black';
		if (!$D_SEQ_ICON_INFO[$k]['borderWidth']) $D_SEQ_ICON_INFO[$k]['borderWidth'] = 2;
		if (!$D_SEQ_ICON_INFO[$k]['circle']) $D_SEQ_ICON_INFO[$k]['circle'] = 0;
		if (!$D_SEQ_ICON_INFO[$k]['backgroundColor']) $D_SEQ_ICON_INFO[$k]['backgroundColor'] = 'white';
	}
}

// del 2013/07/26 Y.Matsukawa [		�������ذ�ư
// add 2011/12/20 Y.Matsukawa
//--------------------------------------------
// �������२�顼
//--------------------------------------------
//if ($D_CUST_ERRMSG != '') {
//	$tpl['err'] = $D_CUST_ERRMSG;
//	ZdcLogPut(1);
//	htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
//	exit;
//}
// del 2013/07/26 Y.Matsukawa ]

// del 2012/03/12 Y.Matsukawa [		��act_redirect_ua.inc�ذ�ư
// add 2012/02/03 N.Wada
//--------------------------------------------
// ���ޥۤ���Υ����������Υ�����쥯��
//--------------------------------------------
//$REDIRET_SMT_URL = "http://$D_DOMAIN_G/smt/$cid/";
//if (strpos($_SERVER['HTTP_USER_AGENT'], 'iPhone')) {
//	$UA_IPHONE = true;
//} else if (strpos($_SERVER['HTTP_USER_AGENT'], 'Android')) {
//	$UA_ANDROID = true;
//}
//if (($UA_IPHONE && $D_IPHONE_REDIRECT_SMT) || ($UA_ANDROID && $D_ANDROID_REDIRECT_SMT)) {
//	header('Location: '.$REDIRET_SMT_URL);
//	exit;
//}
// del 2012/03/12 Y.Matsukawa ]

//--------------------------------------------
// ɬ�פ�JS���������ɤ���
//--------------------------------------------
include("/home/emap/src/p/inc/define_jsload.inc");

// add 2011/12/05 Y.Matsukawa
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

// �����ƥॢ����������ѥ�
$tpl['_cgiSysIconimg'] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI['sys_icon_select'], $D_DATA_CID);
$tpl['_cgiSysIconimgSSL'] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI['sys_icon_select_ssl'], $D_DATA_CID);	//add 2016/07/27 Y.Uesugi

// ------------------------------------------------------------
// �ѥ󤯤���Cookie��
// ------------------------------------------------------------
$ZdcHistory = array();
$ZdcHistoryParm = '';
// ���������ɲ�
function ZdcHistoryAdd($id, $name, $url, $hislist) {
	global $D_COOKIENAME_HISTORY, $ZdcHistory, $ZdcHistoryParm;
	global $D_HISTORY_TOP_LINK, $D_HISTORY_TOP_NAME;
	global $D_COOKIE_HISTORY_KEY_ADD;		// add 2016/05/13 N.Wada
	
	//dbl("ZdcHistoryAdd($id, $name, $url, $hislist)");
	$exist = false;
	// �ѥ�᡼�����ꤵ�줿�������
	$arr_his = array();
	if ($hislist) $arr_his = explode(',', $hislist);
	$arr_his_new = array();
	
	// add 2016/05/13 N.Wada [
	$cookie_key = $D_COOKIENAME_HISTORY;
	if (isset($D_COOKIE_HISTORY_KEY_ADD) && $D_COOKIE_HISTORY_KEY_ADD) {
		$cookie_key .= "_".$D_COOKIE_HISTORY_KEY_ADD;
	}
	// add 2016/05/13 N.Wada ]
	if (count($arr_his)) {
		//if (isset($_COOKIE[$D_COOKIENAME_HISTORY]) && $_COOKIE[$D_COOKIENAME_HISTORY] != '') {	mod 2016/05/13 N.Wada
		if (isset($_COOKIE[$cookie_key]) && $_COOKIE[$cookie_key] != '') {
			//$arr_saved_his = unserialize($_COOKIE[$D_COOKIENAME_HISTORY]);	mod 2016/05/13 N.Wada
			$arr_saved_his = unserialize($_COOKIE[$cookie_key]);
			if ($arr_saved_his && is_array($arr_saved_his) && count($arr_saved_his)) {
				foreach ($arr_his as $i => $his_id) {
					foreach ($arr_saved_his as $h => $saved_his) {
						// �ѥ�᡼�����ꤵ�줿�������Cookie����¸����Ƥ���
						if ($his_id == $saved_his['id']) {
							$ZdcHistory[] = $saved_his;
							$arr_his_new[] = $his_id;
							// �ɲä��褦�Ȥ��Ƥ���ڡ��������Ǥ˾�������¸�ߤ���
							if ($his_id == $id) {
								$exist = true;
								break 2;
							}
						}
					}
				}
			}
		}
	}
	if (!$exist) {
		$ZdcHistory[] = array('id'=>$id, 'name'=>$name, 'url'=>$url);
		$arr_his_new[] = $id;
	}

	$ZdcHistoryParm = urlencode(implode(',', $arr_his_new));

	//setcookie($D_COOKIENAME_HISTORY, serialize($ZdcHistory), 0, '/');	mod 2016/05/13 N.Wada
	setcookie($cookie_key, serialize($ZdcHistory), 0, '/');
}
// ����������		add 2014/07/07 Y.Matsukawa
function ZdcHistoryRemove($id) {
	global $D_COOKIENAME_HISTORY, $ZdcHistory, $ZdcHistoryParm;
	global $D_COOKIE_HISTORY_KEY_ADD;		// add 2016/05/13 N.Wada
	// add 2016/05/13 N.Wada [
	$cookie_key = $D_COOKIENAME_HISTORY;
	if (isset($D_COOKIE_HISTORY_KEY_ADD) && $D_COOKIE_HISTORY_KEY_ADD) {
		$cookie_key .= "_".$D_COOKIE_HISTORY_KEY_ADD;
	}
	// add 2016/05/13 N.Wada ]
	$arr = array();
	if (isset($ZdcHistory) && count($ZdcHistory)) {
		foreach ($ZdcHistory as $his) {
			if ($his['id'] != $id) {
				$arr[] = $his;
			}
		}
	}
	$ZdcHistory = $arr;

	//setcookie($D_COOKIENAME_HISTORY, serialize($ZdcHistory), 0, '/');	mod 2016/05/13 N.Wada
	setcookie($cookie_key, serialize($ZdcHistory), 0, '/');
}

//--------------------------------------------
// �ƥ�ץ졼�Ȥ˰��Ϥ�
//--------------------------------------------
if (isset($D_CID))				$tpl["D_CID"] = $D_CID;
if (isset($D_DATA_CID))			$tpl["D_DATA_CID"] = $D_DATA_CID;		// add 2014/05/20 Y.Matsukawa
if (isset($D_ICON_CID))			$tpl["D_ICON_CID"] = $D_ICON_CID;		// add 2014/05/20 Y.Matsukawa
if (isset($D_USER_DEFNAME))		$tpl["D_USER_DEFNAME"] = $D_USER_DEFNAME;
if (isset($D_USER_SERVICENAME))	$tpl["D_USER_SERVICENAME"] = $D_USER_SERVICENAME;
if (isset($D_DIR_BASE_G))		$tpl["D_DIR_BASE"] = $D_DIR_BASE_G;
if (isset($D_DIR_COMPANY))		$tpl["D_DIR_COMPANY"] = $D_DIR_COMPANY;
if (isset($D_HISTORY_TOP_LINK))	$tpl["D_HISTORY_TOP_LINK"] = $D_HISTORY_TOP_LINK;
if (isset($D_DOMAIN_G))			$tpl["D_DOMAIN_G"] = $D_DOMAIN_G;		// add 2012/07/04 H.Osamoto
if (isset($D_MAP_WAIT_MSG))		$tpl["D_MAP_WAIT_MSG"] = $D_MAP_WAIT_MSG;		// add 2015/11/13 N.Wada
// add 2012/07/06 H.Osamoto [
if (isset($D_FREE_VAR) && is_array($D_FREE_VAR)) {
	foreach ($D_FREE_VAR as $l => $wk) {
		$key = 'D_FREE_VAR'.$l;
		$tpl[$key] = $wk;
	}
}
// add 2012/07/06 H.Osamoto ]

// add 2013/07/26 Y.Matsukawa	�����夫���ư
//--------------------------------------------
// �������२�顼
//--------------------------------------------
if ($D_CUST_ERRMSG != '') {
	$tpl['err'] = $D_CUST_ERRMSG;
	ZdcLogPut(1);
	htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
	erl($D_CUST_ERRMSG);
	exit;
}

//--------------------------------------------
// �����ӥ����̥����å�
//--------------------------------------------
$D_HTML_BLACKLIST['S'] = array('maplink.htm');
$D_HTML_BLACKLIST['L'] = array(
							'index.htm',
							'top.htm',
							'maplink.htm',
);
$D_HTML_BLACKLIST['N'] = array(
							'index.htm',
							'top.htm',
							'shop_inf.htm',
							'shop_map.htm',
);
if (in_array($script_name, $D_HTML_BLACKLIST[$D_SERVICE_TYPE])) {
	header('Content-Type: text/html;charset=UTF-8');
	erl("$cid - SERVICE TYPE ERROR [$D_SERVICE_TYPE]");
	echo mb_convert_encoding('�����ʥ��������Ǥ���','UTF-8','EUC-JP');
	exit;
}

// add 2015/11/11 Y.Matsukawa [
if ($D_RESPONSE_CHARSET && strpos($script_name, '.htm')) {
	header('Content-Type: text/html;charset=EUC-JP');
}
// add 2015/11/11 Y.Matsukawa ]
// add 2017/05/14 Y.Matsukawa [
if (strpos($script_name, '.htm')) {
	header('X-Content-Type-Options: nosniff');
}
// add 2017/05/14 Y.Matsukawa ]

?>