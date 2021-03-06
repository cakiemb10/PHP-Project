<?php
// ------------------------------------------------------------
// 2009/10/15 Y.Matsukawa	REFERERを255バイトに丸める
// 2010/04/19 Y.Matsukawa	脆弱性対策（logディレクトリ移動）
// 2011/01/05 Y.Matsukawa	【不具合修正】リファラーに含まれる半角スペースを除去
// 2011/04/11 Y.Matsukawa	【不具合修正】オプションコード桁あふれ対応（不正アクセス）
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/11/02 K.Masuda 		【不具合修正】オプションコード桁あふれ対応（20→15桁）  
// 2012/06/13 Y.Matsukawa	ASPログ：PC2対応
// 2012/07/30 Y.Matsukawa	error_reporting記述削除
// ------------------------------------------------------------
// mod 2011/07/05 Y.Nakajima
//strictlevel非表示
//error_reporting(E_ALL);		del 2012/07/30 Y.Matsukawa

//define('LOG4PHP_DIR', '/home/emap/httpd/log/log4php');		mod 2010/04/19 Y.Matsukawa
define('LOG4PHP_DIR', '/home/emap/src/log/log4php');
//define('LOG4PHP_CONFIGURATION', '/home/emap/httpd/log/inc/log4php.properties.asp');		mod 2010/04/19 Y.Matsukawa
define('LOG4PHP_CONFIGURATION', '/home/emap/src/log/inc/log4php.properties.asp');

require_once(LOG4PHP_DIR . '/LoggerManager.php');

$log_pc     =& LoggerManager::getLogger(basename($_SERVER['SCRIPT_NAME']));
//include ('/home/emap/httpd/log/inc/com_getuseragent.inc');		mod 2010/04/19 Y.Matsukawa
include ('/home/emap/src/log/inc/com_getuseragent.inc');

//リクエスト種別
LoggerNDC::push(getenv('REQUEST_METHOD'));

//ユーザーIPアドレス
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_REMOTE_ADDR"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_ADDR"];
//if($_GET["P_REMOTE_ADDR"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_ADDR"];
//if(!$REMOTE_ADDR) $REMOTE_ADDR = $_SERVER["REMOTE_ADDR"];
if(isset($_POST["P_REMOTE_ADDR"]) && $_POST["P_REMOTE_ADDR"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_ADDR"];
if(isset($_GET["P_REMOTE_ADDR"]) && $_GET["P_REMOTE_ADDR"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_ADDR"];
if(!isset($REMOTE_ADDR) || $REMOTE_ADDR == "") $REMOTE_ADDR = $_SERVER["REMOTE_ADDR"];
// mod 2011/07/05 Y.Nakajima ]

$REMOTE_ADDR = mb_strimwidth(mb_ereg_replace(' ','_',$REMOTE_ADDR), 0, 20);		// add 2011/04/11 Y.Matsukawa
LoggerNDC::push($REMOTE_ADDR);

//ユーザーホスト
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_REMOTE_HOST"] != "") $REMOTE_ADDR = $_POST["P_REMOTE_HOST"];
//if($_GET["P_REMOTE_HOST"]  != "") $REMOTE_ADDR = $_GET["P_REMOTE_HOST"];
//if(!$REMOTE_HOST) $REMOTE_HOST = $_SERVER["REMOTE_HOST"];
//REMOTE_ADDR?
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

//ユーザーエージェント
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

//企業コード
global $ASP_MODE;
if($ASP_MODE == "PC"){
	LoggerNDC::push("EmapSsP");
// add 2012/06/13 Y.Matsukawa [
} else if($ASP_MODE == "PC2"){
	LoggerNDC::push("EmapSsQ");
// add 2012/06/13 Y.Matsukawa ]
}else if($ASP_MODE == "MOBILE"){
	LoggerNDC::push("EmapSsM");
// add 2012/06/13 Y.Matsukawa [
} else if($ASP_MODE == "SMT"){
	LoggerNDC::push("EmapSsS");
// add 2012/06/13 Y.Matsukawa ]
}else{
	LoggerNDC::push("zdcemap");
}

//オプションコード(emap企業コード)
$OPT = $_SERVER['SCRIPT_NAME'];
$OPT = substr($OPT,strpos($OPT,'/asp/')+5);
$OPT = substr($OPT,0,strpos($OPT,'/'.basename($OPT)));
// mod 2011/11/02 K.Masuda [
//$OPT = mb_strimwidth(mb_ereg_replace(' ','_',$OPT), 0, 20);		// add 2011/04/11 Y.Matsukawa
if( substr($OPT, -5) == "_prev" && strlen($OPT) <= 20 ){
	// 何もしない
} else {
	$OPT = mb_strimwidth(mb_ereg_replace(' ','_',$OPT), 0, 15);
}
// mod 2011/11/02 K.Masuda ]
LoggerNDC::push($OPT);

//リファラ
// mod 2011/07/05 Y.Nakajima [
//if($_POST["P_HTTP_REFERER"] != "") $HTTP_REFERER = $_POST["P_HTTP_REFERER"];
//if($_GET["P_HTTP_REFERER"]  != "") $HTTP_REFERER = $_GET["P_HTTP_REFERER"];
//if(!$HTTP_REFERER) $HTTP_REFERER = trim($_SERVER["HTTP_REFERER"]);
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
if(strpos($HTTP_REFERER,'?')) $HTTP_REFERER=substr($HTTP_REFERER,0,strpos($HTTP_REFERER,'?'));//?以降はカット
$HTTP_REFERER = str_replace(' ', '', $HTTP_REFERER);		// add 2011/01/05 Y.Matsukawa
$HTTP_REFERER = mb_strimwidth($HTTP_REFERER, 0, 255, '...');		// add 2009/10/15 Y.Matsukawa
LoggerNDC::push($HTTP_REFERER);

//リターンコード
LoggerNDC::push("");

//サービス種類
LoggerNDC::push("");

//サービス自由枠
?>
