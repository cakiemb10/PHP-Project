<?php
// ------------------------------------------------------------
// 2011/10/15 Y.Matsukawa	新規作成
// 2011/12/05 Y.Matsukawa	別CID参照
// 2011/12/20 Y.Matsukawa	テンプレート設定ファイル内でエラーメッセージがセットされたらエラー画面表示
// 2011/12/21 Y.Matsukawa	リファラチェック時、https/httpを区別しないモード
// 2012/02/03 N.Wada		スマホからのアクセス時のリダイレクト
// 2012/03/12 Y.Matsukawa	スマホリダイレクト（各種接続I/F対応）
// 2012/05/21 H.osamoto		【不具合修正】住所リスト検索を行った際にパンくずの履歴が文字化けする
// 2012/07/04 H.osamoto		テンプレートにドメインを引き渡す
// 2012/07/06 H.Osamoto		テンプレートに任意の変数を引き渡す
// 2012/07/30 Y.Matsukawa	error_reporting記述削除
// 2012/09/07 Y.Matsukawa	【不具合修正】任意パラメータ指定値が半角スペースのみの場合、値が消える
// 2012/11/01 Y.Matsukawa	テンプレートからHTMLファイル名を参照
// 2013/04/11 H.Osamoto		プレビュー機能を利用可能に修正
// 2013/07/23 Y.Matsukawa	【不具合修正】https動作時、最寄店舗一覧から詳細へのリンクがhttpになってしまう
// 2013/07/26 Y.Matsukawa	カスタムエラー画面表示のタイミングを、全定義完了後に変更
// 2013/11/28 Y.Matsukawa	セキュリティ対応（XSS）
// 2014/05/20 Y.Matsukawa	テンプレートからCID参照
// 2014/10/06 Y.Matsukawa	連番アイコン
// 2015/01/08 Y.Matsukawa	年をテンプレートに渡す
// 2015/02/25 Y.Matsukawa	ローカル参照先のドメイン定義を$D_DOMAIN_Lに変更
// 2015/03/16 Y.Matsukawa	絞り込み：任意カラムの部分一致
// 2015/08/27 Y.Matsukawa	セキュリティ対応（SQL Injection）
// 2015/10/28 Y.Uesugi		ヤマト運輸向け センター情報取得
// 2015/11/11 Y.Matsukawa	ヘッダーでcharset出力
// 2015/11/13 N.Wada		ウェイトメッセージ
// 2016/02/03 N.Wada		機種判定
// 2016/05/13 N.Wada		パンくずCookieのキーに任意の文字列を追加
// 2016/07/27 Y.Uesugi		SSL許可時のアイコンCGI SSL対応
// 2017/03/14 H.Yasunaga	日本郵便カスタマイズ
// 2017/04/19 H.Yasunaga	日本郵便カスタマイズ
// 2017/05/14 Y.Matsukawa	XSS対策
// ------------------------------------------------------------
$script_name = basename($_SERVER['SCRIPT_NAME']);
// HTMLファイル名		add 2012/11/01 Y.Matsukawa
if ($script_name) {
	$tpl_htmlflg = str_replace('.', '_', $script_name);
	$tpl[$tpl_htmlflg] = 1;
}

//------------------------------------------
// HOMEディレクトリ
//------------------------------------------
$arr_dir = explode('/', dirname($_SERVER['SCRIPT_NAME']));
$homedir = implode('/', $arr_dir).'/';

// add 2011/12/21 Y.Matsukawa
//------------------------------------------
// リファラ
//------------------------------------------
if (isset($_SERVER['HTTP_REFERER']) && $_SERVER['HTTP_REFERER'] != '') {
	$HTTP_REFERER = $_SERVER['HTTP_REFERER'];
} else {
	$HTTP_REFERER = '';
}

//------------------------------------------
// 企業ID
//------------------------------------------
$cid = array_pop($arr_dir);
$D_LOG_CID = $cid;
if(strpos($cid,'_prev') > -1){
	// 企業IDに「_prev」のキーワードがある場合は、テンプレートカスタマイザーのプレビュー
	$cid = substr($cid, 0, strpos($cid,'_prev'));
	$D_PREVIEW = true;
} else {
	$D_PREVIEW = false;
}
$D_CID = $cid;
${'_'.$_SERVER['REQUEST_METHOD']}['cid'] = $cid;/* ※d_serv_emap.inc内でcidを再取得してしまうので */

$D_PC2 = true;

$tpl['D_YEAR'] = date('Y');		// add 2015/01/08 Y.Matsukawa

//------------------------------------------
// 環境定義
//------------------------------------------
require_once('d_serv_emap.inc');
require_once("/home/emap/src/p/inc/xml_util.inc");	// add 2015/11/09 Y.Uesugi

//------------------------------------------
// ベースディレクトリ
//------------------------------------------
// add 2013/07/23 Y.Matsukawa [
// https動作時、最寄店舗一覧がhttpで呼び出されるせいで一覧のリンクもhttpになってしまうのを回避
if (isset($_GET['https_req']) && $_GET['https_req'] && $protocol != 'https') {
	$protocol = 'https';
}
// add 2013/07/23 Y.Matsukawa [
$D_DIR_BASE_G  = "$protocol://".$D_DOMAIN_G.$homedir;
//$D_DIR_BASE_L  = "http://".$EMAP_SSAPI_SRV.$homedir;		mod 2015/02/25 Y.Matsukawa
$D_DIR_BASE_L  = "http://".$D_DOMAIN_L.$homedir;
$D_DIR_COMPANY = "$protocol://".$D_DOMAIN_G.$homedir.'company/'.$cid.'/';

//------------------------------------------
// パンくず（Cookie）定義
//------------------------------------------
$D_COOKIENAME_HISTORY = 'EMAP_P_HISTORY_'.$D_CID;

$err = false;
//------------------------------------------
// デバッグ
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
// 機種判定
//------------------------------------------
require_once('/home/emap/src/p/inc/carrier.inc');
$carrier = new CARRIER($_SERVER['HTTP_USER_AGENT']);

//------------------------------------------
// 共通定義
//------------------------------------------
require_once('ZdcCommonFunc.inc');
require_once('htmltemplate.inc');
require_once('/home/emap/src/p/inc/function.inc');
require_once('/home/emap/src/p/inc/crypt.inc');

//dbl("homedir=$homedir");
//dbl("cid=$cid");
//dbl("D_CID=$D_CID");

//------------------------------------------
// パラメータ取得（サニタイズ）
//------------------------------------------
// シングルクォートを除去すべきパラメータ
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
// ダブルクォートとシングルクォートを除去すべきパラメータ		add 2013/11/28 Y.Matsukawa
$D_REMOVE_XSS_SIGN = array(
'area1',
'area2'		// add 2015/08/27 Y.Matsukawa
);
// ダブルクォートとシングルクォートを全角置換すべきパラメータ		add 2013/11/28 Y.Matsukawa
$D_CNV2W_XSS_SIGN = array(
'keyword',
);
// HTML特殊文字（&、<、>、"、'）をエスケープすべきパラメータ		add 2017/05/14 Y.Matsukawa
$D_HTMLSPECIALCHARS = array(
'areaptn',
'adcd'
);
// JavaScript特殊文字（\、"、'、/、<、>、0x0D(CR)、0x0A(LF)）を除去すべきパラメータ		add 2017/05/14 Y.Matsukawa
$D_REMOVE_JSCHARS = array(
's_lat',
's_lon',
'e_lat',
'e_lon',
'srchplace'
);
// フラグ項目のサニタイズ（数字以外が含まれていたら0に置換）		add 2013/11/28 Y.Matsukawa
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
	// add 2017/03/13 H.Yasunaga 日本郵便カスタマイズ [
	// 最寄り一覧が化けるのでnlistを除外
	// mod 2017/04/19 H.Yasunaga 日本郵便カスタマイズ [
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
		// nlist.htmのjknパラメータはjsから渡されるのでUTF-8として解釈
		if ($script_name == 'nlist.htm' && $key == 'jkn') {
			$val = mb_convert_encoding($val, 'eucJP-win', 'UTF-8');
		// add 2015/03/17 Y.Matsukawa [
		// nlist.htm,msg.htmのcondパラメータはjsから渡されるのでUTF-8として解釈
		} else if (($script_name == 'nlist.htm' || $script_name == 'msg.htm') && strpos($key, 'cond')===0) {
			$val = mb_convert_encoding($val, 'eucJP-win', 'UTF-8');
		// add 2015/03/17 Y.Matsukawa ]
		} else {
		// add 2015/03/16 Y.Matsukawa ]
			//$val = ZdcConvertEncoding(trim($val));		mod 2012/09/07 Y.Matsukawa
			$val = ZdcConvertEncoding($val);
		}
		if($key != '') {
			// シングルクォート除去
			if ($val != '' && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
				$val = mb_ereg_replace("'", '', $val);
			}
			// ダブルクォートとシングルクォートを除去		add 2013/11/28 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_XSS_SIGN)) {
				$val = mb_ereg_replace('"', '', $val);
				$val = mb_ereg_replace("'", '', $val);
			}
			// ダブルクォートとシングルクォートを全角置換		add 2013/11/28 Y.Matsukawa
			if ($val != '' && in_array($key, $D_CNV2W_XSS_SIGN)) {
				$val = mb_ereg_replace('"', '”', $val);
				$val = mb_ereg_replace("'", '’', $val);
			}
			// HTML特殊文字（&、<、>、"、'）をエスケープ		add 2017/05/14 Y.Matsukawa
			if ($val != '' && in_array($key, $D_HTMLSPECIALCHARS)) {
				$val = htmlspecialchars($val, ENT_QUOTES);
			}
			// JavaScript特殊文字（\、"、'、/、<、>、0x0D(CR)、0x0A(LF)）を除去		add 2017/05/14 Y.Matsukawa
			if ($val != '' && in_array($key, $D_REMOVE_JSCHARS)) {
				$val = mb_ereg_replace("[\\\"'\/<>\r\n]", '', $val);
			}
			// フラグ項目のサニタイズ（数字以外が含まれていたら0に置換）		add 2013/11/28 Y.Matsukawa
			if ($val != '' && in_array($key, $D_SANITIZE_FLAG_PARAMS)) {
				if (!ctype_digit($val)) $val = '0';
			}
			${$key} = $val;
			$_VARS[$key] = $val;
		}
	}
}

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
// システム定義
//------------------------------------------
require_once('/home/emap/src/p/inc/define_system.inc');

//------------------------------------------
// テンプレートディレクトリ
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
	echo mb_convert_encoding('不正なアクセスです。','UTF-8','EUC-JP');
	exit;
}
$D_SYSDIR_COMPANY = $D_TEMPLATE_DIR;

//------------------------------------------
// その他設定
//------------------------------------------
$D_PFLG = 2;
$D_DATUM = 'TOKYO';
// ログ関係
$LOG_MODE = 'PC2';
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
require_once('/home/emap/src/p/inc/define_design.inc');
require_once('/home/emap/src/p/inc/define_action.inc');
require_once('/home/emap/src/p/inc/define_msg.inc');

// P3Pコンパクトポリシー		2012/05/10 Y.Matsukawa
if(isset($D_P3P_HEADER) && $D_P3P_HEADER) header('P3P: CP="'.$D_P3P_HEADER.'"');

// 連番アイコン情報デフォルト値		2014/10/06 Y.Matsukawa
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

// del 2013/07/26 Y.Matsukawa [		※↓下へ移動
// add 2011/12/20 Y.Matsukawa
//--------------------------------------------
// カスタムエラー
//--------------------------------------------
//if ($D_CUST_ERRMSG != '') {
//	$tpl['err'] = $D_CUST_ERRMSG;
//	ZdcLogPut(1);
//	htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
//	exit;
//}
// del 2013/07/26 Y.Matsukawa ]

// del 2012/03/12 Y.Matsukawa [		※act_redirect_ua.incへ移動
// add 2012/02/03 N.Wada
//--------------------------------------------
// スマホからのアクセス時のリダイレクト
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
// 必要なJSだけロードする
//--------------------------------------------
include("/home/emap/src/p/inc/define_jsload.inc");

// add 2011/12/05 Y.Matsukawa
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
$tpl['_cgiSysIconimgSSL'] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI['sys_icon_select_ssl'], $D_DATA_CID);	//add 2016/07/27 Y.Uesugi

// ------------------------------------------------------------
// パンくず（Cookie）
// ------------------------------------------------------------
$ZdcHistory = array();
$ZdcHistoryParm = '';
// 遷移履歴追加
function ZdcHistoryAdd($id, $name, $url, $hislist) {
	global $D_COOKIENAME_HISTORY, $ZdcHistory, $ZdcHistoryParm;
	global $D_HISTORY_TOP_LINK, $D_HISTORY_TOP_NAME;
	global $D_COOKIE_HISTORY_KEY_ADD;		// add 2016/05/13 N.Wada
	
	//dbl("ZdcHistoryAdd($id, $name, $url, $hislist)");
	$exist = false;
	// パラメータ指定された上位履歴
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
						// パラメータ指定された上位履歴がCookieに保存されている
						if ($his_id == $saved_his['id']) {
							$ZdcHistory[] = $saved_his;
							$arr_his_new[] = $his_id;
							// 追加しようとしているページがすでに上位履歴に存在する
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
// 遷移履歴削除		add 2014/07/07 Y.Matsukawa
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
// テンプレートに引渡し
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

// add 2013/07/26 Y.Matsukawa	※↓上から移動
//--------------------------------------------
// カスタムエラー
//--------------------------------------------
if ($D_CUST_ERRMSG != '') {
	$tpl['err'] = $D_CUST_ERRMSG;
	ZdcLogPut(1);
	htmloutput($D_SYSDIR_COMPANY.'errorview.tpl', $tpl);
	erl($D_CUST_ERRMSG);
	exit;
}

//--------------------------------------------
// サービス種別チェック
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
	echo mb_convert_encoding('不正なアクセスです。','UTF-8','EUC-JP');
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
