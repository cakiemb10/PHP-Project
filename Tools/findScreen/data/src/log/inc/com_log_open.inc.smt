<?php
// ------------------------------------------------------------
// 2011/03/10 Y.Matsukawa	�V�K�쐬
// 2011/04/11 Y.Matsukawa	�y�s��C���z�I�v�V�����R�[�h�����ӂ�Ή��i�s���A�N�Z�X�j
// 2011/07/05 Y.Nakajima	VM���ɔ���apache,phpVerUP�Ή����C
// 2012/07/30 Y.Matsukawa	error_reporting�L�q�폜
// ------------------------------------------------------------
// mod 2011/07/05 Y.Nakajima
//strictlevel��\��
//error_reporting(E_ALL);		del 2012/07/30 Y.Matsukawa

define('LOG4PHP_DIR', '/home/emap/src/log/log4php');
define('LOG4PHP_CONFIGURATION', '/home/emap/src/log/inc/log4php.properties.smt');

require_once(LOG4PHP_DIR . '/LoggerManager.php');

$log_smt     =& LoggerManager::getLogger(basename($_SERVER['SCRIPT_NAME']));
include ('/home/emap/src/log/inc/com_getuseragent.inc');

//���N�G�X�g���
LoggerNDC::push(getenv('REQUEST_METHOD'));

//���[�U�[IP�A�h���X
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_REMOTE_ADDR"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_ADDR"];
//if($_GET["P_REMOTE_ADDR"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_ADDR"];
//if(!$REMOTE_ADDR) $REMOTE_ADDR = $_SERVER["REMOTE_ADDR"];
if(isset($_POST["P_REMOTE_ADDR"]) && $_POST["P_REMOTE_ADDR"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_ADDR"];
if(isset($_GET["P_REMOTE_ADDR"]) && $_GET["P_REMOTE_ADDR"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_ADDR"];
if(!isset($REMOTE_ADDR)) {
	if (isset($_SERVER["REMOTE_ADDR"])) {
		$REMOTE_ADDR = $_SERVER["REMOTE_ADDR"];
	} else {
		$REMOTE_ADDR = "";
	}
}
// mod 2011/07/05 Y.Nakajima ]
$REMOTE_ADDR = mb_strimwidth(mb_ereg_replace(' ','_',$REMOTE_ADDR), 0, 20);		// add 2011/04/11 Y.Matsukawa
LoggerNDC::push($REMOTE_ADDR);

//���[�U�[�z�X�g
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_REMOTE_HOST"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_HOST"];
//if($_GET["P_REMOTE_HOST"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_HOST"];
//if(!$REMOTE_HOST) $REMOTE_HOST = $_SERVER["REMOTE_HOST"];
if(isset($_POST["P_REMOTE_HOST"]) && $_POST["P_REMOTE_HOST"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_HOST"];
if(isset($_GET["P_REMOTE_HOST"]) && $_GET["P_REMOTE_HOST"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_HOST"];
if(!isset($REMOTE_HOST)) {
	if (isset($_SERVER["REMOTE_HOST"])) {
		$REMOTE_HOST = $_SERVER["REMOTE_HOST"];
	} else {
		$REMOTE_HOST = "";
	}
}
// mod 2011/07/05 Y.Nakajima ]
$REMOTE_HOST = mb_strimwidth(mb_ereg_replace(' ','_',$REMOTE_HOST), 0, 100);		// add 2011/04/11 Y.Matsukawa
LoggerNDC::push($REMOTE_HOST);

//���[�U�[�G�[�W�F���g
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_HTTP_USER_AGENT"] != "") $HTTP_USER_AGENT = $_POST["P_HTTP_USER_AGENT"];
//if($_GET["P_HTTP_USER_AGENT"]  != "") $HTTP_USER_AGENT = $_GET["P_HTTP_USER_AGENT"];
//if(!$HTTP_USER_AGENT) $HTTP_USER_AGENT = $_SERVER["HTTP_USER_AGENT"];
if(isset($_POST["P_HTTP_USER_AGENT"]) && $_POST["P_HTTP_USER_AGENT"] != "") $HTTP_USER_AGENT = $_POST["P_HTTP_USER_AGENT"];
if(isset($_GET["P_HTTP_USER_AGENT"]) && $_GET["P_HTTP_USER_AGENT"]  != "") $HTTP_USER_AGENT = $_GET["P_HTTP_USER_AGENT"];
if(!isset($HTTP_USER_AGENT)) {
	if (isset($_SERVER["HTTP_USER_AGENT"])) {
		$HTTP_USER_AGENT = $_SERVER["HTTP_USER_AGENT"];
	} else {
		$HTTP_USER_AGENT = "";
	}
}
// mod 2011/07/05 Y.Nakajima ]
LoggerNDC::push(com_getuseragent($HTTP_USER_AGENT));


//��ƃR�[�h
LoggerNDC::push("EmapSsS");

//�I�v�V�����R�[�h(emap��ƃR�[�h)
//if($_POST["cid"] != "") $OPT = $_POST["cid"];
//if($_GET["cid"]  != "") $OPT = $_GET["cid"];
$OPT = $D_CID;
$OPT = mb_strimwidth(mb_ereg_replace(' ','_',$OPT), 0, 20);		// add 2011/04/11 Y.Matsukawa
LoggerNDC::push($OPT);

//���t�@��
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_HTTP_REFERER"] != "") $HTTP_REFERER = $_POST["P_HTTP_REFERER"];
//if($_GET["P_HTTP_REFERER"]  != "") $HTTP_REFERER = $_GET["P_HTTP_REFERER"];
//if(!$HTTP_REFERER) $HTTP_REFERER = trim($_SERVER["HTTP_REFERER"]);
//if(strpos($HTTP_REFERER,'?')) $HTTP_REFERER=substr($HTTP_REFERER,0,strpos($HTTP_REFERER,'?'));//?�ȍ~�̓J�b�g
if(isset($_POST["P_HTTP_REFERER"]) && $_POST["P_HTTP_REFERER"] != "") $HTTP_REFERER = $_POST["P_HTTP_REFERER"];
if(isset($_GET["P_HTTP_REFERER"]) && $_GET["P_HTTP_REFERER"]  != "") $HTTP_REFERER = $_GET["P_HTTP_REFERER"];
if(!isset($HTTP_REFERER)) {
	if(isset($_SERVER["HTTP_REFERER"])) {
		$HTTP_REFERER = trim($_SERVER["HTTP_REFERER"]);
	} else {
		$HTTP_REFERER = "";
	}
}

// mod 2011/07/05 Y.Nakajima ]
$HTTP_REFERER = str_replace(' ', '', $HTTP_REFERER);
$HTTP_REFERER = mb_strimwidth($HTTP_REFERER, 0, 255, '...');
LoggerNDC::push($HTTP_REFERER);

//���^�[���R�[�h
LoggerNDC::push("");

//�T�[�r�X���
LoggerNDC::push("");

//�T�[�r�X���R�g
//�A�v���ŋL�q
?>
