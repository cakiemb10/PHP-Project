<?php
// ------------------------------------------------------------
// 2010/04/19 Y.Matsukawa	脆弱性対策（logディレクトリ移動）
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// ------------------------------------------------------------

//include ('/home/emap/httpd/log/inc/com_getuseragent.inc');		mod 2010/04/19 Y.Matsukawa
include ('/home/emap/src/log/inc/com_getuseragent.inc');

//define('LOG4PHP_DIR', '/home/emap/httpd/log/log4php');		mod 2010/04/19 Y.Matsukawa
define('LOG4PHP_DIR', '/home/emap/src/log/log4php');
define('LOG4PHP_CONFIGURATION', '/home/emap/httpd/cgi/logs/inc/log4php.properties');


require_once(LOG4PHP_DIR . '/LoggerManager.php');

// mod 2011/07/05 Y.Nakajima
//$log_api     =& LoggerManager::getLogger(basename($_SERVER['SCRIPT_NAME']));
//$log_api     = LoggerManager::getLogger(basename($_SERVER['SCRIPT_NAME']));
$LoggerManager = new LoggerManager();
$log_api     = $LoggerManager->getLogger(basename($_SERVER['SCRIPT_NAME']));

// mod 2011/07/05 Y.Nakajima
//LoggerNDC::push(getenv('REQUEST_METHOD'));
$LoggerNDC = new LoggerNDC();
$LoggerNDC->push(getenv('REQUEST_METHOD'));

//LoggerNDC::push(getenv('REMOTE_ADDR'));

// mod 2011/07/05 Y.Nakajima [
/*
if(isset($_POST["P_REMOTE_ADDR"]) && $_POST["P_REMOTE_ADDR"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_ADDR"];
if(isset($_GET["P_REMOTE_ADDR"]) && $_GET["P_REMOTE_ADDR"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_ADDR"];
LoggerNDC::push($REMOTE_ADDR);
*/
if(isset($_POST["P_REMOTE_ADDR"]) && $_POST["P_REMOTE_ADDR"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_ADDR"];
if(isset($_GET["P_REMOTE_ADDR"]) && $_GET["P_REMOTE_ADDR"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_ADDR"];
if(!isset($REMOTE_ADDR)) {
	if (isset($_SERVER["REMOTE_ADDR"])) {
		$REMOTE_ADDR = $_SERVER["REMOTE_ADDR"];
	} else {
		$REMOTE_ADDR = "";
	}
}
$LoggerNDC->push($REMOTE_ADDR);
// mod 2011/07/05 Y.Nakajima ]

// mod 2011/07/05 Y.Nakajima [
//LoggerNDC::push(getenv('REMOTE_HOST'));
if(!isset($REMOTE_HOST)) {
	if (gethostbyaddr($_SERVER["REMOTE_ADDR"]) != "") {
		$REMOTE_HOST = gethostbyaddr($_SERVER["REMOTE_ADDR"]);
	} else {
		$REMOTE_HOST = "";
	}
}
$LoggerNDC->push($REMOTE_HOST);    //REMOTE_HOSTは取れなくなった
// mod 2011/07/05 Y.Nakajima [

//LoggerNDC::push(com_getuseragent(getenv('HTTP_USER_AGENT')));

// mod 2011/07/05 Y.Nakajima [
/*
if(isset($_POST["P_HTTP_USER_AGENT"]) && $_POST["P_HTTP_USER_AGENT"] != "") $HTTP_USER_AGENT = $_POST["P_HTTP_USER_AGENT"];
if(isset($_GET["P_HTTP_USER_AGENT"]) && $_GET["P_HTTP_USER_AGENT"]  != "") $HTTP_USER_AGENT = $_GET["P_HTTP_USER_AGENT"];
$LoggerNDC->push(com_getuseragent($HTTP_USER_AGENT));
*/
if(isset($_POST["P_HTTP_USER_AGENT"]) && $_POST["P_HTTP_USER_AGENT"] != "") $HTTP_USER_AGENT = $_POST["P_HTTP_USER_AGENT"];
if(isset($_GET["P_HTTP_USER_AGENT"]) && $_GET["P_HTTP_USER_AGENT"]  != "") $HTTP_USER_AGENT = $_GET["P_HTTP_USER_AGENT"];
if(!isset($HTTP_USER_AGENT)) {
	if (isset($_SERVER["HTTP_USER_AGENT"])) {
		$HTTP_USER_AGENT = $_SERVER["HTTP_USER_AGENT"];
	} else {
		$HTTP_USER_AGENT = "";
	}
}

//LoggerNDC::push(com_getuseragent($HTTP_USER_AGENT));
$LoggerNDC->push(com_getuseragent($HTTP_USER_AGENT));
// mod 2011/07/05 Y.Nakajima ]

?>
