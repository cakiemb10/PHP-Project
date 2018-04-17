<?php
// ------------------------------------------------------------
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/05/12 Y.Matsukawa	テンプレート生成対応
// 2011/05/23 Y.Matsukawa	テンプレート生成対応
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/07/13 Y.Matsukawa	機能追加（ルート探索、最寄駅）
// 2011/09/26 H.Osamoto		フリーURLを追加
// 2012/01/10 N.Wada		テンプレート設定ファイル内でエラーメッセージがセットされたらエラー画面表示
// 2012/01/19 N.Wada		別CID参照
// 2012/03/17 N.Wada		d_serv_emap.inc内でcidを参照したいため、その前に企業IDを取得
// 2012/04/24 Y.Matsukawa	施設リスト検索
// 2012/05/23 Y.Matsukawa	formN.plfilterがhiddenの場合に対応
// 2012/07/18 Y.Matsukawa	最寄施設
// 2012/07/30 Y.Matsukawa	error_reporting記述削除
// 2012/08/16 K.Masuda		地図縮尺変更+-ボタン対応
// 2012/09/10 Y.Matsukawa	【不具合修正】任意パラメータに「&」を含めると正しく引き継がれない、任意パラメータに半角スペース指定すると消える
// 2013/07/10 Y.Matsukawa	ヤマト運輸向けカスタマイズ（CGI呼び出し）
// 2014/02/10 Y.Matsukawa	脆弱性対策（XSS等）
// 2014/03/21 Y.Matsukawa	カスタムエラー画面にPATH情報を引き渡し
// 2014/08/18 AnPham		SiteIconOverlapping
// 2014/09/11 Y.Matsukawa	Android2.1判定
// 2014/11/05 Khuong Truong Check V2 and set Map level
// 2015/01/08 Y.Matsukawa	年をテンプレートに渡す
// 2015/02/25 Y.Matsukawa	ローカル参照先のドメイン定義を$D_DOMAIN_Lに変更
// 2015/09/06 Y.Matsukawa	セキュリティ対応（SQL Injection）
// 2015/10/30 N.Wada		Google Maps版対応
// 							HTMLファイル名をテンプレートに渡す
// 2015/11/19 Y.Uesugi		現在地取得後、最寄り一覧と分布地図両方への遷移を用意(フッタ対応)
// 2016/05/02 N.Wada		Google Maps APIの読み込みをhttpsに対応
// 2016/05/16 Y.Matsukawa	Google Maps API channel指定
// 2016/11/10 Y.Uesugi		Google Maps APIキー設定
// 2016/01/04 N.Wada		テンプレートに任意の変数を引き渡す
// 2017/05/14 Y.Matsukawa	XSS対策
// 2017/05/19 Y.Matsukawa	SQLインジェクション対策
// ------------------------------------------------------------
//debug
//error_reporting(E_ALL | E_STRICT);

$script_name = basename($_SERVER['SCRIPT_NAME']);		// add 2012/05/23 Y.Matsukawa
// HTMLファイル名		add 2015/10/30 N.Wada
if ($script_name) {
	$tpl_htmlflg = str_replace('.', '_', $script_name);
	$tpl[$tpl_htmlflg] = 1;
}

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off対応
//入力パラメータを取り込む処理を追加
//post,get
//同じ名称でパラメータがあった場合は？
//POSTを優先する
extract($_GET);
extract($_POST);
// add 2011/07/05 Y.Nakajima ]

// add 2015/09/06 Y.Matsukawa [
//// サニタイズ		add 2014/02/10 Y.Matsukawa
//$arr_sanitize = array('lat','lon','area','mode','kid','adcd','klat','klon','tod','kn');
//foreach ($arr_sanitize as $tmp) {
//	if (isset($$tmp) && $$tmp != '') {
//		$$tmp = ereg_replace("[\"']", '', $$tmp);
//	}
//}
// add 2015/09/06 Y.Matsukawa ]

// add 2012/03/17 N.Wada [
//------------------------------------------
// 企業ID
//------------------------------------------
/*
 ※d_serv_emap.inc内でcidを参照したいためここで企業IDを取得
 　下でコーディングしているベースディレクトリ、企業IDの設定ロジックを移植
 */
$wk = explode('/', dirname($_SERVER['SCRIPT_NAME']));
$tmp = implode('/', $wk).'/';
$cid = array_pop($wk);
if(strpos($cid,'_prev') > -1){
	$cid = substr($cid, 0, strpos($cid,'_prev'));
}
$D_CID = $cid;
${'_'.$_SERVER['REQUEST_METHOD']}['cid'] = $cid;/* ※d_serv_emap.inc内でcidを再取得してしまうので */
// add 2012/03/17 N.Wada ]

$tpl['D_YEAR'] = date('Y');		// add 2015/01/08 Y.Matsukawa

$D_SMT = true;
require_once('d_serv_emap.inc');

require_once('ZdcCommonFunc.inc');
require_once('htmltemplate.inc');
require_once("/home/emap/src/smt/inc/xml_util.inc");		// add 2013/07/10 Y.Matsukawa
require_once('/home/emap/src/smt/inc/define_system.inc');
require_once("/home/emap/src/smt/inc/function.inc");
require_once("/home/emap/src/smt/inc/crypt.inc");		// add 2011/05/23 Y.Matsukawa

//------------------------------------------
// デバッグ
//------------------------------------------
if($D_EMAP_ENV == 'dev')
	$debug = true;
else
	$debug = false;
//if($debug){ error_reporting (E_ALL^E_NOTICE); } else { error_reporting (0); }		del 2012/07/30 Y.Matsukawa

define('D_DEBUG_LOG_FILE', '/var/tmp/smt_debug_'.date('Ymd').'.log');
define('D_ERROR_LOG_FILE', '/var/tmp/smt_error_'.date('Ymd').'.log');

//------------------------------------------
// 機種判定
//------------------------------------------
require_once('/home/emap/src/smt/inc/carrier.inc');
$carrier = new CARRIER($_SERVER['HTTP_USER_AGENT']);

//------------------------------------------
// パラメータ取得（サニタイズ）
//------------------------------------------
// del 2015/09/06 Y.Matsukawa [
//// シングルクォートを除去すべきパラメータ
//$D_REMOVE_QUOTE_PARAMS = array(
//'type',
//'adcd',
//'area'
//);
//// POST
//// mod 2011/07/05 Y.Nakajima
//if (isset($_POST['enc']) && $_POST['enc']) {
//	switch ($_POST['enc']) {
//		case 'EUC':
//		case 'SJIS':
//		case 'UTF8':
//			$enc = $_POST['enc'];
//			break;
//		default:
//			$enc = 'UTF8';
//	}
//}
//foreach($_POST as $key=>$val) {
//	if (is_string($key) && is_string($val)) {
//		//$val = ZdcConvertEncoding(trim($val));		mod 2012/09/10 Y.Matsukawa
//		$val = ZdcConvertEncoding($val);
//		//$val = htmlspecialchars($val);
//		if($key != '') {
//			// シングルクォート除去
//			if ($val != '' && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
//				$val = mb_ereg_replace("'", '', $val);
//			}
//			${$key} = $val;
//			$_POST[$key] = $val;
//			$_VARS[$key] = $val;
//		}
//	}
//}
//// GET
//// mod 2011/07/05 Y.Nakajima 
//if (isset($_GET['enc']) && $_GET['enc']) {
//	switch ($_GET['enc']) {
//		case 'EUC':
//		case 'SJIS':
//		case 'UTF8':
//			$enc = $_GET['enc'];
//			break;
//		default:
//			$enc = 'UTF8';
//	}
//}
//foreach($_GET as $key=>$val) {
//	if (is_string($key) && is_string($val)) {
//		//$val = ZdcConvertEncoding(trim($val));		mod 2012/09/10 Y.Matsukawa
//		$val = ZdcConvertEncoding($val);
//		//$val = htmlspecialchars($val);
//		if($key != '') {
//			// シングルクォート除去
//			if ($val != '' && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
//				$val = mb_ereg_replace("'", '', $val);
//			}
//			${$key} = $val;
//			$_GET[$key] = $val;
//			$_VARS[$key] = $val;
//		}
//	}
//}
// del 2015/09/06 Y.Matsukawa ]
// add 2015/09/06 Y.Matsukawa [
// ダブルクォートとシングルクォートを除去すべきパラメータ
$D_REMOVE_XSS_SIGN = array(
'type',
'adcd',
'area',
'lat',
'lon',
'area',
'mode',
'kid',
'adcd',
'klat',
'klon',
'tod',
'kn'
);
// HTML特殊文字（&、<、>、"、'）をエスケープすべきパラメータ		add 2017/05/14 Y.Matsukawa
$D_HTMLSPECIALCHARS = array(
'fromname'
);
// JavaScript特殊文字（\、"、'、/、<、>、0x0D(CR)、0x0A(LF)）を除去すべきパラメータ		add 2017/05/14 Y.Matsukawa
$D_REMOVE_JSCHARS = array(
'naviid',
'line'
);
// SQL特殊文字（'、\、|）を除去すべきパラメータ		add 2017/05/19 Y.Matsukawa
$D_REMOVE_SQLCHARS = array(
'tod'
);
// 半角スペースを除去すべきパラメータ		add 2017/05/19 Y.Matsukawa
$D_REMOVE_BLANK = array(
'tod'
);
// パイプを除去すべきパラメータ
$D_REMOVE_PIPE_SIGN = array(
'kid'
);
$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
if (isset($_VARS['enc']) && $_VARS['enc']) {
	switch ($_VARS['enc']) {
		case 'EUC':
		case 'SJIS':
		case 'UTF8':
			$enc = $_VARS['enc'];
			break;
		default:
			$enc = 'UTF8';
	}
}
foreach($_VARS as $key=>$val) {
	if (is_string($key) && is_string($val)) {
		$val = ZdcConvertEncoding($val);
		if($key != '') {
			// ダブルクォートとシングルクォートを除去
			if ($val != '' && in_array($key, $D_REMOVE_XSS_SIGN)) {
				$val = mb_ereg_replace("['\"]", '', $val);
			}
			// HTML特殊文字（&、<、>、"、'）をエスケープ		add 2017/05/14 Y.Matsukawa
			if ($val != '' && in_array($key, $D_HTMLSPECIALCHARS)) {
				$val = htmlspecialchars($val, ENT_QUOTES);
			}
			// JavaScript特殊文字（\、"、'、/、<、>、0x0D(CR)、0x0A(LF)）を除去		add 2017/05/14 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_JSCHARS)) {
				$val = mb_ereg_replace("[\\\"'\/<>\r\n]", '', $val);
			}
			// SQL特殊文字（'、\、|）を除去		add 2017/05/19 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_SQLCHARS)) {
				$val = mb_ereg_replace("[\\\'\|]", '', $val);
			}
			// 半角スペースを除去		add 2017/05/19 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_BLANK)) {
				$val = mb_ereg_replace(" ", '', $val);
			}
			// パイプを除去
			if ($val != '' && in_array($key, $D_REMOVE_PIPE_SIGN)) {
				$val = mb_ereg_replace("\|", '', $val);
			}
			${$key} = $val;
			$_VARS[$key] = $val;
		}
	}
}
${'_'.$_SERVER['REQUEST_METHOD']} = $_VARS;
// add 2015/09/06 Y.Matsukawa ]

// mod 2011/07/05 Y.Nakajima [
//$_SERVER関係置き換え
if (isset($_SERVER['HTTP_REFERER'])) {
	$HTTP_REFERER = $_SERVER['HTTP_REFERER'];
	$tpl['HTTP_REFERER'] = $HTTP_REFERER;		// add 2016/04/12 Y.Matsukawa
} else {
	$HTTP_REFERER = "";
}
if (isset($_SERVER['REMOTE_ADDR'])) {
	$REMOTE_ADDR = $_SERVER['REMOTE_ADDR'];
} else {
	$REMOTE_ADDR = "";
}
if (isset($_SERVER['HTTP_USER_AGENT'])) {
	$HTTP_USER_AGENT = $_SERVER['HTTP_USER_AGENT'];
} else {
	$HTTP_USER_AGENT = "";
}
if (isset($_SERVER['HTTP_USER_AGENT'])) {
	$HTTP_USER_AGENT = $_SERVER['HTTP_USER_AGENT'];
} else {
	$HTTP_USER_AGENT = "";
}
// mod 2011/07/05 Y.Nakajima ]

//------------------------------------------
// 基本設定
//------------------------------------------
$wk = parse_url($_SERVER['REQUEST_URI']);
$_SERVER['HTTP_HOST'] = ($_SERVER['HTTP_HOST'] == '' ? $wk['host'] : $_SERVER['HTTP_HOST']);

//------------------------------------------
// 脆弱性対策（クロスサイトスクリプティング）
//------------------------------------------
// Hostヘッダ改変に対応
$_SERVER['HTTP_HOST'] = htmlspecialchars($_SERVER['HTTP_HOST'], ENT_QUOTES);

//------------------------------------------
// ベースディレクトリ
//------------------------------------------
//$req_uri = (substr($_SERVER['REQUEST_URI'], -1) == '/' ? $_SERVER['REQUEST_URI'].'dummy.htm' : $_SERVER['REQUEST_URI']);
//$wk = explode('/', dirname($req_uri));
$wk = explode('/', dirname($_SERVER['SCRIPT_NAME']));
$tmp = implode('/', $wk).'/';
$cid = array_pop($wk);
$D_DIR_BASE_G = "$protocol://".$D_DOMAIN_G.$tmp;
//$D_DIR_BASE_L = "http://".$EMAP_SSAPI_SRV.$tmp;		mod 2015/02/25 Y.Matsukawa
$D_DIR_BASE_L = "http://".$D_DOMAIN_L.$tmp;
$D_DIR_COMPANY = "$protocol://".$D_DOMAIN_G.$tmp.'company/'.$cid.'/';

//------------------------------------------
// 企業ID
//------------------------------------------
$D_LOG_CID = $cid;
if(strpos($cid,'_prev') > -1){
	// 企業IDに「_prev」のキーワードがある場合は、テンプレートカスタマイザーのプレビュー
	$cid = substr($cid, 0, strpos($cid,'_prev'));
	$D_PREVIEW = true;
} else {
	$D_PREVIEW = false;
}
$D_CID = $cid;

//------------------------------------------
// テンプレートディレクトリ
//------------------------------------------
if($D_PREVIEW){
	$D_TEMPLATE_DIR = "/home/emap/httpd/emap_tpl/tpl_edit_smt/company/$cid/";
	$D_HTTP_DIR_COMPANY = "/emap_tpl/tpl_edit_smt/company/$cid/";
} else {
	$D_TEMPLATE_DIR = "./company/$cid/";
	$D_HTTP_DIR_COMPANY = dirname($_SERVER['SCRIPT_NAME'])."/company/$cid/";
}
if(!file_exists($D_TEMPLATE_DIR)){
	header('Content-Type: text/html;charset=UTF-8');
	erl("$cid - template dir NOT FOUND [$D_TEMPLATE_DIR]");
	echo mb_convert_encoding('不正なアクセスです。','UTF-8','EUC-JP');
	exit;
}
$D_SYSDIR_COMPANY = $D_TEMPLATE_DIR;

//------------------------------------------
// その他設定
//------------------------------------------
$D_PFLG = 2;
$D_DATUM = 'TOKYO';
define('D_PL_TYPE_LOC',   1);
define('D_PL_TYPE_ADDRL', 2);
define('D_PL_TYPE_FW',    3);
define('D_PL_TYPE_EKIL',  4);	// add 2012/04/24 Y.Matsukawa
define('D_PL_TYPE_POIL',  5);	// add 2012/04/24 Y.Matsukawa
// ログ関係
$LOG_MODE = 'SMT';
// 通信のタイムアウト時間
$D_AJAX_TIMEOUT   = 10000;
$D_SOCKET_TIMEOUT = 10000;
// 最寄り検索半径上限値（APIの制限）
$API_RAD_MAX = 50000;


//------------------------------------------
// テンプレートの設定ファイル
//------------------------------------------
include($D_SYSDIR_COMPANY . 'setting.inc');		// 設定ファイル
include($D_SYSDIR_COMPANY . 'setting_option.inc');

//--------------------------------------------
// その他
//--------------------------------------------
require_once('/home/emap/src/smt/inc/define_design.inc');
require_once('/home/emap/src/smt/inc/define_action.inc');
require_once('/home/emap/src/smt/inc/define_msg.inc');

// del 2014/03/21 Y.Matsukawa [
//// add 2012/01/10 N.Wada
////--------------------------------------------
//// カスタムエラー
////--------------------------------------------
//if ($D_CUST_ERRMSG != '') {
//	$tpl['err'] = $D_CUST_ERRMSG;
//	ZdcLogPut(1);
//	htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
//	exit;
//}
// del 2014/03/21 Y.Matsukawa ]

// add 2011/07/13 Y.Matsukawa
//--------------------------------------------
// 追加JS
//--------------------------------------------
if($D_LOC_ROUTE_TYPE || $D_NEKI_ROUTE_TYPE || $D_SEARCH_ROUTE_TYPE) {
	$D_JSAPI_SMT["map"] .= ',zdcroute.js';
	$D_JSAPI_SMT["map"] .= ',zdcproute.js';
}
// add 2014/08/18 AnPham [
if( $D_KYO_ICON_OVERLAP == 1) {
	$D_JSAPI_SMT["map"] .= ',zdcmapgeometric.js';
}
// add 2014/08/18 AnPham ]

// add 2015/10/30 N.Wada [
if ($D_GOOGLEMAPS) {
	//$D_GOOGLEMAPS_JS = 'http://maps.google.com/maps/api/js?v=3';	mod 2016/05/02 N.Wada
	$D_GOOGLEMAPS_JS = $protocol.'://maps.google.com/maps/api/js?v=3';
	if (isset($D_GOOGLEMAPS_CID) && $D_GOOGLEMAPS_CID)
		$D_GOOGLEMAPS_JS .= '&client='.$D_GOOGLEMAPS_CID;
	// add 2016/05/16 Y.Matsukawa [
	if (isset($D_GOOGLEMAPS_CHANNEL) && $D_GOOGLEMAPS_CHANNEL)
		$D_GOOGLEMAPS_JS .= '&channel='.$D_GOOGLEMAPS_CHANNEL;
	// add 2016/05/16 Y.Matsukawa ]
}
// add 2015/10/30 N.Wada ]

// add 2016/11/10 Y.Uesugi [
if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) {
	$D_GOOGLEMAPS_API_KEY_JS = $protocol.'://maps.googleapis.com/maps/api/js?key=';
	$D_GOOGLEMAPS_API_KEY_JS .= $D_GOOGLEMAPS_API_KEY;
}
// add 2016/11/10 Y.Uesugi ]

// add 2012/01/19 N.Wada
//--------------------------------------------
// データ参照先CID
//--------------------------------------------
// 拠点データ
if (isset($D_DATA_CID) && $D_DATA_CID != '') {
	$D_DATA_CID .= (strpos($D_CID, 'test') ? 'test' : '');
} else {
	$D_DATA_CID = $D_CID;
}
// 拠点アイコン
if (isset($D_ICON_CID) && $D_ICON_CID != '') {
	$D_ICON_CID .= (strpos($D_CID, 'test') ? 'test' : '');
} else {
	$D_ICON_CID = $D_CID;
}

// システムアイコン画像パス
$tpl['_cgiSysIconimg'] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI['sys_icon_select'], $D_DATA_CID);

//--------------------------------------------
// テンプレートに引渡し
//--------------------------------------------
//$tpl["D_USER_DEFNAME"]      = $D_USER_DEFNAME;		del 2011/05/23 Y.Matsukawa
//$tpl["D_USER_SERVICENAME"]  = $D_USER_SERVICENAME;	del 2011/05/23 Y.Matsukawa
$tpl["D_SHOP_NAME"]         = $D_SHOP_NAME;			// add 2011/05/23 Y.Matsukawa
$tpl["D_DIR_BASE"]          = $D_DIR_BASE_G;
$tpl["D_DIR_COMPANY"]       = $D_DIR_COMPANY;
$tpl['D_TITLE']             = $D_TITLE;
$tpl['D_URL_SEARCH_TOP']    = $D_DIR_BASE_G;
$tpl['D_WAIT_MSG']          = $D_WAIT_MSG;
$tpl['D_FILTER_TITLE']      = $D_FILTER_TITLE;
$tpl['D_COPYRIGHT']         = $D_COPYRIGHT;			// add 2011/05/12 Y.Matsukawa
$tpl['D_PLBTN_TXT']         = $D_PLBTN_TXT;			// add 2011/05/12 Y.Matsukawa
$tpl['D_SEARCH_AVAILABLE']  = $D_SEARCH_AVAILABLE;	// add 2011/05/12 Y.Matsukawa
$tpl['D_FLG_NAME']          = $D_FLG_NAME;			// add 2011/05/23 Y.Matsukawa
$tpl['D_HP_URL']            = $D_HP_URL;			// add 2011/05/23 Y.Matsukawa
$tpl['D_HP_LINK_NAME']      = $D_HP_LINK_NAME;		// add 2011/05/23 Y.Matsukawa
$tpl['D_COND_BTN']          = $D_COND_BTN;			// add 2011/08/08 Y.Matsukawa
$tpl['D_COND_BTN_ON']       = $D_COND_BTN_ON;		// add 2011/08/08 Y.Matsukawa
$tpl['D_SHOP_FW_INIT']      = $D_SHOP_FW_INIT;		// add 2014/09/11 Y.Matsukawa
$tpl['D_SHOP_FW_INIT_COL']  = $D_SHOP_FW_INIT_COL;	// add 2014/09/11 Y.Matsukawa
$tpl['D_PL_FW_INIT']        = $D_PL_FW_INIT;		// add 2014/09/11 Y.Matsukawa
$tpl['D_ADDR_FW_INIT']      = $D_ADDR_FW_INIT;		// add 2014/09/11 Y.Matsukawa
$tpl['D_ST_FW_INIT']        = $D_ST_FW_INIT;		// add 2014/09/11 Y.Matsukawa
$tpl['D_POI_FW_INIT']       = $D_POI_FW_INIT;		// add 2014/09/11 Y.Matsukawa
// add 2011/07/13 Y.Matsukawa [
if($D_SRCH_NEKI) $tpl['D_SRCH_NEKI'] = $D_SRCH_NEKI;
if($D_LOC_ROUTE_TYPE) $tpl['D_LOC_ROUTE_TYPE'] = $D_LOC_ROUTE_TYPE;
if($D_NEKI_ROUTE_TYPE) $tpl['D_NEKI_ROUTE_TYPE'] = $D_LOC_ROUTE_TYPE;
if($D_SEARCH_ROUTE_TYPE) $tpl['D_SEARCH_ROUTE_TYPE'] = $D_LOC_ROUTE_TYPE;
// add 2011/07/13 Y.Matsukawa ]
if($D_SRCH_NPOI) $tpl['D_SRCH_NPOI'] = $D_SRCH_NPOI;		// add 2012/07/18 Y.Matsukawa
if($D_NPOI_ROUTE_TYPE) $tpl['D_NPOI_ROUTE_TYPE'] = $D_NPOI_ROUTE_TYPE;		// add 2012/07/18 Y.Matsukawa
if($D_POST_MODE) $tpl['D_POST_MODE'] = $D_POST_MODE;		// add 2016/09/28 Y.Matsukawa

// add 2016/01/04 N.Wada [
if (isset($D_FREE_VAR) && is_array($D_FREE_VAR)) {
	foreach ($D_FREE_VAR as $l => $wk) {
		$key = 'D_FREE_VAR'.$l;
		$tpl[$key] = $wk;
	}
}
// add 2016/01/04 N.Wada ]
// add 2011/09/26 H.Osamoto [
if (isset($D_FREE_URL) && is_array($D_FREE_URL)) {
	foreach ($D_FREE_URL as $l => $wk) {
		$key = 'FREE_URL'.$l;
		$tpl[$key] = $wk;
	}
}
// add 2011/09/26 H.Osamoto ]
// add 2011/05/23 Y.Matsukawa [
$i = 0;
// #BEGIN Add - Check V2 and set Map level by Truong Khuong
if(isset($D_SMT_API_V2) && $D_SMT_API_V2 == 1){
	$D_MAP_LVL = $D_MAP_LVL_V2;
}
// #END Add - Check V2 and set Map level by Truong Khuong

foreach ($D_MAP_LVL as $l => $wk) {
	if ($l >= $D_MAX_LVL && $l <= $D_MIN_LVL) {
		$tpl['map_lvl'][$i]['lvl'] = $l;
		$tpl['map_lvl'][$i]['txt'] = $wk;
		$i++;
	}
}
// add 2011/05/23 Y.Matsukawa ]
$tpl[$carrier->G_AGENT_TYPE] = 1;
if ($carrier->isANDROID()) $tpl["Android"] = 1;
if ($carrier->isSmartPhone()) $tpl["SmartPhone"] = 1;
if ($carrier->G_ANDROID_2_1) $tpl["Android_2_1"] = 1;		// add 2014/09/11 Y.Matsukawa
// 施設ジャンルメニュー		add 2012/07/18 Y.Matsukawa
foreach ($D_POI_JNRMN as $i => $arr) {
	$tpl["D_POI_JNRMN_CD_$i"] = $arr[0];
	$tpl["D_POI_JNRMN_NM_$i"] = $arr[1];
}
// add 2012/08/16 K.Masuda [
if($D_SCALE_TYPE){
	$tpl['scale_type'] = $D_SCALE_TYPE;
}
// add 2012/08/16 K.Masuda ]

// add 2015/11/19 Y.Uesugi [
// 最寄り一覧へ遷移する現在地取得
if(isset($carrier)){
	// js
	$j = 0;
	$tpl['js'][$j]['src'] = $D_DIR_BASE_G.'search.js';
	$tpl['js'][$j]['charset'] = 'EUC-JP';

	$tmp = $D_DIR_BASE_G.'n.htm?pltype='.D_PL_TYPE_LOC.$pl_prm_enc['cond'].($freeparms_enc?'&'.$freeparms_enc:'');
	$tpl['_jsLocCallbackNList'] = $carrier->MakeLocationCallbackFunc($tmp, 'NL');
	$tpl['_jsLocNList'] = $carrier->MakeLocationSearchScript('NL');
	// 分布地図へ遷移する現在地取得
	$tmp = $D_DIR_BASE_G.'nmap.htm?pltype='.D_PL_TYPE_LOC.$pl_prm_enc['cond'].($freeparms_enc?'&'.$freeparms_enc:'');
	$tpl['_jsLocCallbackNMap'] = $carrier->MakeLocationCallbackFunc($tmp, 'NM');
	$tpl['_jsLocNMap'] = $carrier->MakeLocationSearchScript('NM');
}
// add 2015/11/19 Y.Uesugi ]

// add 2014/03/21 Y.Matsukawa
//--------------------------------------------
// カスタムエラー
//--------------------------------------------
if ($D_CUST_ERRMSG != '') {
	$tpl['err'] = $D_CUST_ERRMSG;
	ZdcLogPut(1);
	htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
	exit;
}

// add 2011/04/26 Y.Matsukawa
//--------------------------------------------
// サービス種別チェック
//--------------------------------------------
$D_HTML_BLACKLIST['S'] = array('maplink.htm');
$D_HTML_BLACKLIST['L'] = array(
							'index.htm',
							'seach.htm',
							'search_pl.htm',
							//'search_addr.htm',		del 2011/08/10 Y.Matsukawa
							//'search_fw.htm',			del 2011/08/10 Y.Matsukawa
							'n.htm',
							'nmap.htm',
							'fw.htm',
							'maplink.htm',
);
$D_HTML_BLACKLIST['N'] = array(
							'index.htm',
							'seach.htm',
							'search_pl.htm',
							//'search_addr.htm',		del 2011/08/10 Y.Matsukawa
							//'search_fw.htm',			del 2011/08/10 Y.Matsukawa
							'n.htm',
							'nmap.htm',
							'fw.htm',
							'shop_inf.htm',
							'shop_map.htm',
);
if (in_array(basename($_SERVER['SCRIPT_NAME']), $D_HTML_BLACKLIST[$D_SERVICE_TYPE])) {
	header('Content-Type: text/html;charset=UTF-8');
	erl("$cid - SERVICE TYPE ERROR [$D_SERVICE_TYPE]");
	echo mb_convert_encoding('不正なアクセスです。','UTF-8','EUC-JP');
	exit;
}

// add 2017/05/14 Y.Matsukawa [
if (strpos($script_name, '.htm')) {
	if ($D_RESPONSE_CHARSET) {
		header('Content-Type: text/html;charset=UTF-8');
	}
	header('X-Content-Type-Options: nosniff');
}
// add 2017/05/14 Y.Matsukawa ]

?>
