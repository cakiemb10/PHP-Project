<?php
// ------------------------------------------------------------
// 定義ファイル メイン
// 
// 開発履歴
// 2007/03/01 bando@D&I		新規開発
// 2008/10/22 Y.Matsukawa	使用しないJSはロードしない
// 2009/11/10 Y.Matsukawa	開発機VM化
// 2010/04/08 Y.Matsukawa	脆弱性対策（クロスサイトスクリプティング）
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/07/27 Y.Matsukawa	携帯URLをhttpsで表示
// 2010/08/13 Y.Matsukawa	iPhoneからのアクセスを携帯へリダイレクト
// 2010/11/03 K.Masuda		エリア検索複数対応
// 2011/07/04 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/12/13 H.osamoto		SSL接続時(https)にパラメータ「$https_req」を引き継ぐように修正
// 2012/03/19 SKC			キャリア判定用設定追加
// 2012/10/26 K.Masuda		PC->スマホリダイレクト用縮尺レベル変換表追加
// 2014/08/13 F.Yokoi		オリジナルのドメイン名が上書きされないように修正
// 2016/06/20 Y.Matsukawa	日本郵政専リダイレクト対応
// ------------------------------------------------------------

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off対応
//入力パラメータを取り込む処理を追加
//post,get
//同じ名称でパラメータがあった場合は？
//POSTを優先する
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
// 日本郵政リダイレクト対応（旧サイトURL）
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
//----- 開発機 -----
case "devemapweb":
	// 開発機VMはプロキシ経由になるので、HTTP_HOSTがローカルIPになってしまう為
	$_SERVER["HTTP_HOST"] = "218.225.89.139";
	break;
// add 2011/02/09 Y.Matsukawa [

// add 2011/09/09 c_hanajima [
case "dev-storenaviweb01":
    // VM移行後開発サーバ設定
    //$_SERVER["HTTP_HOST"] = "10.47.50.79";	//リリースまではこちら
	$_SERVER["HTTP_HOST"] = "218.225.89.139";    //リリース後は開発機の設定をこちらにする
    break;
// mod 2011/09/09 c_hanajima ]

//----- 検証機（暫定機） -----
case "emapweb06":
	$_SERVER["HTTP_HOST"] = "test.e-map.ne.jp";
	break;
//----- 検証機 -----
case "emapweb00":
	$_SERVER["HTTP_HOST"] = "test.e-map.ne.jp";
	break;
// add 2011/07/05 Y.Nakajima [
//----- 検証機 -----
case "storenaviweb-v01":
case "storenaviweb-v02":    //予備機
//2011/09/02 VMサーバリリース時は、host名が変更になるが、本番機に繋ぐので、検証機のcaseを追加はしない
    //$_SERVER["HTTP_HOST"] = "172.29.0.35";	//リリースまではこちら
	$_SERVER["HTTP_HOST"] = "test.e-map.ne.jp";    //リリース後は検証機の設定をこちらにする
    break;
// add 2011/07/05 Y.Nakajima ]
//----- 本番機 -----
default:
	$_SERVER["HTTP_HOST"] = "www.e-map.ne.jp";
// add 2011/02/09 Y.Matsukawa ]
}
// add 2009/11/10 Y.Matsukawa ]

// add 2010/04/08 Y.Matsukawa [
// 脆弱性対策（クロスサイトスクリプティング）
// Hostヘッダ改変に対応
$_SERVER["HTTP_HOST"] = htmlspecialchars($_SERVER["HTTP_HOST"], ENT_QUOTES);
// シングルクォートを除去すべきパラメータ
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

// ベースディレクトリ --------------------------------------
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

// 企業 コード ---------------------------------------------
if(isset($cid)) $D_CID = $cid;
	else $D_CID = "00000000";
//$D_DIR_COMPANY = $D_DIR_BASE."company/".$D_CID."/";		mod 2010/07/20 Y.Matsukawa
$D_DIR_COMPANY = $D_DIR_BASE_G."company/".$D_CID."/";
$D_SYSDIR_COMPANY = "./company/".$D_CID."/";


// 各種設定ファイル ----------------------------------------
include("../inc/ZdcCommonFunc.inc");
include("./inc/define_system.inc");
include("d_serv_emap.inc");

$D_DIR_BASE_L = "http://".$EMAP_SSAPI_SRV.$tmp;		// add 2011/02/09 Y.Matsukawa

//個別設定
@include("./company/".$cid."/setting.inc");			//バックオフィスで設定される
@include("./company/".$cid."/setting_option.inc");	//バックオフィス未対応項目

//必要なJSだけロードする		2008/10/22 Y.Matsukawa add
include("./inc/define_jsload.inc");

//携帯URL		2010/07/27 Y.Matsukawa
// mod 2011/07/05 Y.Nakajima 
if (isset($D_MBURL_HTTPS) && $D_MBURL_HTTPS) {
	$D_MOBILE_URL = str_replace('http://', 'https://', $D_MOBILE_URL);
}

//携帯URLのディレクトリ		add 2010/08/13 Y.Matsukawa
$D_MOBILE_URL_DIR = dirname($D_MOBILE_URL);
if (substr($D_MOBILE_URL_DIR, -1) != '/') $D_MOBILE_URL_DIR .= '/';

// add 2010/11/03 K.Masuda [
// エリア検索MAX数
define("D_AREA_MAX", 5);
// add 2010/11/03 K.Masuda ]

//共通設定
include("./inc/define_design.inc");
include("./inc/define_action.inc");
include("./inc/define_msg.inc");
include("./inc/define_js.inc");

//関数群
include("./inc/function.inc");
include("./inc/crypt.inc");

// add 2012/03/19 SKC [
//キャリア判定
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
// PC->スマホリダイレクト用縮尺レベル変換表
$D_LV_PCTOSMT = array(	// PC			->	スマホ
	'1'  => '1',		// 1:1/1300万	->	1:1/1500万
	'2'  => '2',		// 2:1/650万	->	2:1/650万
	'3'  => '3',		// 3:1/300万	->	3:1/300万
	'4'  => '4',		// 4:1/150万	->	4:1/150万
	'5'  => '5',		// 5:1/100万	->	5:1/100万
	'6'  => '6',		// 6:1/50万		->	6:1/50万
	'7'  => '7',		// 7:1/25万		->	7:1/25万
	'8'  => '8',		// 8:1/15万		->	8:1/10万
	'9'  => '8',		// 9:1/10万		->	8:1/10万
	'10' => '9',		// 10:1/5万		->	9:1/5万
	'11' => '10',		// 11:1/2万		->	10:1/2万
	'12' => '11',		// 12:1/1万5000	->	11:1/1万5000
	'13' => '12',		// 13:1/1万		->	12:1/1万
	'14' => '13',		// 14:1/7500	->	13:1/7500
	'15' => '14',		// 15:1/5000	->	14:1/3500
	'16' => '14',		// 16:1/3500	->	14:1/3500
	'17' => '15',		// 17:1/2500	->	15:1/1500
	'18' => '15'		// 18:1/1500	->	15:1/1500
);
// add 2012/10/26 K.Masuda ]

//--------------------------------------------
// テンプレートに引渡し
//--------------------------------------------
if (isset($D_CID)) $tpl["D_CID"] = $D_CID;		// add 2016/02/20 Y.Matsukawa

?>
