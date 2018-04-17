<?php
// ------------------------------------------------------------
// 2009/06/29 Y.Matsukawa	Maplinkに現在地取得機能を追加
//							任意パラメータ追加
// 2009/07/15 Y.Matsukawa	AD Maplink対応
// 2009/11/10 Y.Matsukawa	開発機VM化
// 2010/03/17 Y.Matsukawa	オートGPSリマインド
// 2010/04/06 Y.Matsukawa	エリア検索（固定仕様）の都道府県一覧に大分県が表示されない
// 2010/05/17 Y.Matsukawa	opt複数指定時にOR連結を可能にする
// 2010/05/28 Y.Matsukawa	ブランド変更（e-mapAD→いつもNAVI）
// 2010/06/21 Y.Matsukawa	最寄り拠点検索の件数設定
// 2010/07/20 Y.Matsukawa	SSL対応
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/25 Y.Matsukawa	特定の検索でopt指定を無効化する
// 2011/09/28 K.Masuda		スマホへリダイレクト
// 2012/02/13 Y.Matsukawa	企業画像（CORP_IMG_TBL）対応
// 2012/03/04 K.Masuda		p_f、p_sパラメータ最大数設定追加
// 2012/03/17 N.Wada		d_serv_emap.inc内でcidを参照したいため、その前に企業IDを取得
// 2012/03/29 K.Masuda		住所接続のスマホリダイレクト対応
// 2012/05/14 Y.Matsukawa	全件一覧ページング
// 2012/08/07 Y.Matsukawa	error_reporting記述削除
// 2012/10/25 Y.Matsukawa	d.htmをd.htmlでもアクセス可能にする
// 2012/10/26 K.Masuda		携帯->スマホリダイレクト用縮尺レベル変換表追加
// 2012/11/19 Y.Matsukawa	JCN満空情報取得
// 2012/12/17 H.Osamoto		神奈川電通広告向けカスタマイズ
// 2013/02/13 K.Masuda		サービス期間の判定時、サービス種別も判定する
// 2013/04/11 H.Osamoto		テンプレートカスタマイザのプレビュー表示時はBasic認証を行わない
// 2013/04/15 H.Osamoto		最寄検索結果が0件の場合再検索で取得する件数指定機能追加
// 2013/06/06 Y.Matsukawa	エリア検索固定版：１階層のみに対応
// 2013/07/31 Y.Matsukawa	【不具合回避】住所FW「東十条」が「東」と同じ検索結果になる（GEO仕様）
// 2013/07/31 H.Osamoto		ヤマト運輸向けカスタマイズ：郵便番号検索0件の場合、住所リスト検索へ遷移
// 2014/02/06 Y.Matsukawa	脆弱性対策（XSS等）
// 2014/03/10 H.Osamoto		ポリゴン内外判定カラム追加
// 2014/07/10 Y.Matsukawa	郵便番号検索：一覧スキップ（最寄り一覧へ直接遷移）
// 2015/01/08 Y.Matsukawa	年をテンプレートに渡す
// 2015/06/01 Y.Uesugi		店舗一覧ソート順指定
// 2015/06/02 Y.Uesugi		エリア検索第２階層NULL対応
// 2015/09/06 Y.Matsukawa	セキュリティ対応（SQL Injection）
// 2015/11/18 Xuan Chien	GPSログ出力対応
// 2016/03/28 Y.Uesugi		スマホリダイレクト不具合修正
// 2016/03/29 Y.Matsukawa	optcd複数時の連結指定
// 2016/06/01 Y.Matsukawa	最寄り地図へ遷移
// 2016/06/13 Y.Matsukawa	日本郵政用郵便番号検索
// 2016/07/04 Y.Matsukawa	スマホアクセス時にPCへリダイレクト
// 2016/07/04 N.Wada		詳細エラー時のリダイレクト先URL追加
// 2016/07/05 N.Wada		PC、不明端末からのアクセス時のリダイレクト先URL追加
// 2016/07/28 N.Wada		詳細のヘッダーテンプレートに、拠点データカラムのフラグを渡す
// 2016/12/05 Y.Uesugi		スマホリダイレクトSSL追加
// 2017/03/24 N.Wada		canonicalタグに出力するURL
// 2017/05/11 H.Yasunaga	ヤマトロッカーセキュリティコード対応
// 2017/05/30 H.Yasunaga	ヤマトロッカーセキュリティコード対応
// ------------------------------------------------------------
$script_name = basename($_SERVER['SCRIPT_NAME']);		// add 2013/08/29 Y.Matsukawa
// add 2016/03/31 Y.Matsukawa [
if ($script_name) {
	$tpl_htmlflg = str_replace('.', '_', $script_name);
	$body_cst[$tpl_htmlflg] = 1;
}
// add 2016/03/31 Y.Matsukawa [

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off対応
//入力パラメータを取り込む処理を追加
//post,get
//同じ名称でパラメータがあった場合は？
//POSTを優先する
extract($_GET);
extract($_POST);

// サニタイズ（"'）		add 2014/02/06 Y.Matsukawa
//$arr_sanitize = array('p','pos','ssr','spos','id');		mod 2015/09/06 Y.Matsukawa
$arr_sanitize = array('pos','ssr','spos','id');
foreach ($arr_sanitize as $tmp) {
	if (isset($$tmp) && $$tmp != '') {
		//$$tmp = ereg_replace("[\"']", '', $$tmp);		mod 2015/09/06 Y.Matsukawa
		$$tmp = mb_ereg_replace("[\"']", '', $$tmp);
	}
}

// サニタイズ（"'| ）		add 2015/09/06 Y.Matsukawa
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
//----- 開発機 -----
case "devemapweb":
	// 開発機VMはプロキシ経由になるので、HTTP_HOSTがローカルIPになってしまう為
	$_SERVER["HTTP_HOST"] = "218.225.89.139";
	break;
}
// add 2009/11/10 Y.Matsukawa ]

// add 2012/03/17 N.Wada [
//////////////////////////////////////////////
// 企業ID
//////////////////////////////////////////////
/*
 ※d_serv_emap.inc内でcidを参照したいためここで企業IDを取得
 　下でコーディングしているベースディレクトリ、企業IDの設定ロジックを移植
 */
// d.htmlでもアクセス可能にする（d.htmとして動作）		add 2012/10/25 Y.Matsukawa
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
${'_'.$_SERVER['REQUEST_METHOD']}['cid'] = $cid;/* ※d_serv_emap.inc内でcidを再取得してしまうので */
// add 2012/03/17 N.Wada ]

$D_MOBILE = true;
define("D_SOCKET_TIMEOUT", 10);
include("ZdcCommonFunc.inc");  // 基本設定
include("htmltemplate.inc");  // テンプレート関数
include("d_serv_emap.inc");  // 基本設定
include("crypt.inc");

//////////////////////////////////////////////
// ログ用
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
// デバッグ用
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
// 基本設定
//////////////////////////////////////////////
$wk = parse_url($_SERVER["REQUEST_URI"]);
$_SERVER["HTTP_HOST"] = ($_SERVER["HTTP_HOST"] == "" ? $wk["host"] : $_SERVER["HTTP_HOST"]);

// ベースディレクトリ
$D_DIR_BASE = substr($SCRIPT_NAME, 0, strpos($SCRIPT_NAME, "/mob")+8);
$cid = substr($SCRIPT_NAME, strpos($SCRIPT_NAME, "/mob")+8 );
$cid = substr($cid, 0, strpos($cid,"/"));
$D_LOG_CID = $cid;

$D_URL_BASE = $D_DIR_BASE.$cid."/";

if(strpos($cid,"_prev") > -1){
	// 企業ＩＤに、「_prev」のキーワードがある場合は、
	// テンプレートカスタマイザーのプレビュー
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
	echo mb_convert_encoding("不正なアクセスです。[999]","SJIS","EUC-JP");
	exit;
}

$D_CID = $cid;

$D_PFLG = 2;
$D_DATUM = "TOKYO";
$D_SEARCH_CORPID = $D_CID;
$D_SRARCH_SRVSID = '00010';

$D_DIR_COMPANY = $D_TEMPLATE_DIR;

// icn省略時のデフォルトアイコン（☆）0：表示する、1：表示しない		add 2008/12/15 Y.Matsukawa
$D_NO_DEFAULT_ICN = 0;

$body_cst['D_YEAR'] = date('Y');		// add 2015/01/08 Y.Matsukawa

//////////////////////////////////////////////
// e-mapAD Maplink デフォルト値			add 2009/07/15 Y.Matsukawa
//////////////////////////////////////////////
// 広告種別
$D_AD_API = "rt001";
// 広告表示件数
$D_AD_COUNT = 3;
//// 広告表示文字列最大長
//$D_AD_MAXLEN = 100;
//$D_AD_TTL_MAXLEN = 50;
// 仕切り線色指定
$D_AD_HR = "FF0000";
// クレジット
//$D_AD_CREDIT = "Ads by ドコイク？<br>Powered by e-mapAD";		2010/05/28 Y.Matsukawa
$D_AD_CREDIT = "Ads by ドコイク？<br>Powered by いつもNAVI";
// AD Debug LOG
define("D_DEBUG_AD_LOG_FILE", "/var/tmp/mobile_ad_".date('Ymd').".log");

//////////////////////////////////////////////
//企業ごとの設定を読み込む
//////////////////////////////////////////////
include($D_DIR_COMPANY . "setting.inc");		// 定数定義
include($D_DIR_COMPANY . "design.inc");			// デザイン定義

$D_TP_IMAGE = $D_IMAGE_BASE."tp11.gif";		// 透明画像		add 2012/11/19 Y.Matsukawa

//////////////////////////////////////////////
// アクセスチェック
//////////////////////////////////////////////
foreach($_GET as $chk_key => $chk_val){
    $_GET[$chk_key] = (strlen($chk_val) > 128 ? substr($chk_val, 0, 128)."..." : $chk_val);
}

foreach($_POST as $chk_key => $chk_val){
    $_POST[$chk_key] = (strlen($chk_val) > 128 ? substr($chk_val, 0, 128)."..." : $chk_val);
}

//--------------------------------------------
// LIGHTチェック
//--------------------------------------------
//if($SETTING["noncpdata"] == "N" || $SETTING["noncpdata"] == "L"){		mod 2009/07/15 Y.Matsukawa
if($SETTING["noncpdata"] == "N" || $SETTING["noncpdata"] == "A" || $SETTING["noncpdata"] == "L"){
	//if(!ereg("(d\.htm|mi\.htm|m\.htm|ne\.htm|cp\.htm)", $SCRIPT_NAME)){		del 2009/06/29 Y.Matsukawa
	// add 2009/06/29 Y.Matsukawa [
	// mod 2011/07/05 Y.Nakajima
	//if (ereg("(s\.htm|index\.htm)", $SCRIPT_NAME) && $SETTING["noncpdata"] == "N" && $SETTING["location"]) {
	if (preg_match("/(s\.htm|index\.htm)/", $SCRIPT_NAME, $matches) && $SETTING["noncpdata"] == "N" && $SETTING["location"]) {
		// Maplinkで「今いる場所」有効な場合はs.htmを許可
	// mod 2011/07/05 Y.Nakajima
	//} else if(!ereg("(d\.htm|mi\.htm|m\.htm|ne\.htm|cp\.htm)", $SCRIPT_NAME)){
	} else if(!preg_match("/(d\.htm|mi\.htm|m\.htm|ne\.htm|cp\.htm)/", $SCRIPT_NAME, $matches)){
	// add 2009/06/29 Y.Matsukawa ]
		header("Content-Type: text/html;charset=Shift_JIS");
		echo mb_convert_encoding("ご利用になれません。[100]","SJIS","EUC-JP");
		erl("ACCESS CHECK ERROR [$SCRIPT_NAME]");
		exit;
	}
}


// 2007/09/14 del matsukawa			※サービス期間前でも動作可に
////--------------------------------------------
//// サービス期間チェック
////--------------------------------------------
//$now_date = date("Ymd");
//if($D_SEARVICE_START > $now_date){
//	header("Content-Type: text/html;charset=Shift_JIS");
//	echo mb_convert_encoding("ご利用になれません。[101]","SJIS","EUC-JP");
//	erl("ACCESS LIMIT CHECK ERROR [$SCRIPT_NAME]");
//	exit;
//}

//------------------------------------------
// BASIC認証
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
	// Basic認証パスワード取得
	$pw = "";
	$url = sprintf("%s?cid=%s&opt=%s", $D_SSAPI["get_basic_pw"], $cid, $cid);
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if($status[0] == "89300000") {
		$rec = explode("\t", $dat[1]);
		$encpw = $rec[0];
		$pw = f_decrypt_api_key($encpw);//復号
		list($dummy, $pw) = explode("=", $pw);//ダミー文字列を除去
		$realm = 'e-map '.str_replace('test', '', $cid);
		// ID未入力（初回）
		if (!isset($_SERVER["PHP_AUTH_USER"])) {
			header("WWW-Authenticate: Basic realm=\"$realm\"");
			header("HTTP/1.0 401 Unauthorized");
			// キャンセル時の表示
			header("Content-Type: text/html;charset=Shift_JIS");
			echo mb_convert_encoding("このページを表示する権限がありません。","SJIS","EUC-JP");
			exit;
		// ID入力
		} else {
			// 認証
			if (AuthenticateUser($_SERVER["PHP_AUTH_USER"], $_SERVER["PHP_AUTH_PW"], $pw)) {
				// OK
			} else {
				// エラー
				header("WWW-Authenticate: Basic realm=\"$realm\"");
				header("HTTP/1.0 401 Unauthorized");
				// キャンセル時の表示
				header("Content-Type: text/html;charset=Shift_JIS");
				echo mb_convert_encoding("このページを表示する権限がありません。","SJIS","EUC-JP");
				exit;
			}
		}
	}
}

//--------------------------------------------
// サービス期間チェック
//--------------------------------------------
//-------------------
// 動作許可チェック
//-------------------
// サービス期間
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
	echo mb_convert_encoding("ご利用になれません。[102]","SJIS","EUC-JP");
	erl("SERVICE LIMIT CHECK ERROR [$SCRIPT_NAME][".$dat[0]."]");
	exit;
}

//--------------------------------------------
// SSL許可チェック		add 2010/07/20 Y.Matsukawa
//--------------------------------------------
// mod 2011/07/05 Y.Nakajima
if (isset($https_req) && $https_req) {
	//$D_SSL_ACCESSの設定が無い、もしくは、設定は有るが値が？
	if (!$D_SSL_ACCESS) {
		header("Content-Type: text/html;charset=Shift_JIS");
		echo mb_convert_encoding("ご利用になれません。[103]","SJIS","EUC-JP");
		erl("HTTPS ACCESS ERROR [$SCRIPT_NAME]");
		exit;
	}
} else {
	// mod 2011/07/05 Y.Nakajima
	if (isset($D_SSL_ACCESS) && $D_SSL_ACCESS == 2) {
		header("Content-Type: text/html;charset=Shift_JIS");
		echo mb_convert_encoding("ご利用になれません。[104]","SJIS","EUC-JP");
		erl("HTTP ACCESS ERROR [$SCRIPT_NAME]");
		exit;
	}
}

//////////////////////////////////////////////
//
// その他
//
//////////////////////////////////////////////
//都道府県
$D_TOD= array ( 
      "01" => "北海道", "02" => "青森県",
      "03" => "岩手県", "04" => "宮城県",
      "05" => "秋田県", "06" => "山形県",
      "07" => "福島県", "08" => "茨城県",
      "09" => "栃木県", "10" => "群馬県",
      "11" => "埼玉県", "12" => "千葉県",
      "13" => "東京都", "14" => "神奈川県",
      "15" => "新潟県", "16" => "富山県",
      "17" => "石川県", "18" => "福井県",
      "19" => "山梨県", "20" => "長野県",
      "21" => "岐阜県", "22" => "静岡県",
      "23" => "愛知県", "24" => "三重県",
      "25" => "滋賀県", "26" => "京都府",
      "27" => "大阪府", "28" => "兵庫県",
      "29" => "奈良県", "30" => "和歌山県",
      "31" => "鳥取県", "32" => "島根県",
      "33" => "岡山県", "34" => "広島県",
      "35" => "山口県", "36" => "徳島県",
      "37" => "香川県", "38" => "愛媛県",
      "39" => "高知県", "40" => "福岡県",
      "41" => "佐賀県", "42" => "長崎県",
      "43" => "熊本県", "44" => "大分県",
      "45" => "宮崎県", "46" => "鹿児島県",
      "47" => "沖縄県");

//住所レベル
$D_ADCD_LVL["KEN"] = 1;
$D_ADCD_LVL["SHK"] = 2;
$D_ADCD_LVL["OAZ"] = 3;
$D_ADCD_LVL["AZC"] = 4;
$D_ADCD_LVL["GIK"] = 5;
$D_ADCD_LVL["TBN"] = 6;
//住所レベル：住所コードの桁数
$D_ADCD_LEN[1] = 2;
$D_ADCD_LEN[2] = 5;
$D_ADCD_LEN[3] = 8;
$D_ADCD_LEN[4] = 11;
$D_ADCD_LEN[5] = 16;
$D_ADCD_LEN[6] = 99;

//住所リストをどの階層まで掘り下げるか（1：都道府県、2：市区町村、3：大字、4：字丁目、5：街区、6：地番（枝番）
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 6;

// iコンシェル オートGPSリマインド		add 2010/03/17 Y.Matsukawa
define("D_ICONCIE_REMIND_URL", "http://remind.its-mo.com/simple.php?uid=NULLGWDOCOMO&DCMPAKEHO=ON&q=");
define("D_ICONCIE_REMIND_EXP_URL", "http://docomo.ne.jp/service/r/iconcier/exp-remind.xhtml");

// add 2012/03/04 K.Masuda [
if (!isset($D_P_F_MAX)) $D_P_F_MAX = 100;
if (!isset($D_P_S_MAX)) $D_P_S_MAX = 100;
// add 2012/03/04 K.Masuda ]

//////////////////////////////////////////////
//
// エリア検索用設定
//
//////////////////////////////////////////////
$AREA_INFO[0]["name"] = '北海道・東北地方';
$AREA_INFO[1]["name"] = '関東地方';
$AREA_INFO[2]["name"] = '北陸地方';
$AREA_INFO[3]["name"] = '中部地方';
$AREA_INFO[4]["name"] = '関西地方';
$AREA_INFO[5]["name"] = '中国地方';
$AREA_INFO[6]["name"] = '四国地方';
$AREA_INFO[7]["name"] = '九州地方';

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
// デフォルト設定
//
//////////////////////////////////////////////
$D_DEFAULT_W = 180;
$D_DEFAULT_H = 160;

//////////////////////////////////////////////
//
// アイコン範囲マージン
//
//////////////////////////////////////////////
$D_MARGIN_PX = 32;

// add 2013/07/31 Y.Matsukawa
//------------------------------------------
// GEO仕様（「東十条」検索が「東」検索と同じになる）を回避
//------------------------------------------
$D_GEO_ESC_JO['東十条'] = 'ヒガシジュウジョウ';


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
//* デバッグ情報出力
//********************************************************************
function dbl($str){
	global $debug;
	// mod 2011/07/05 Y.Nakajima
	if(!isset($debug) || !$debug){ return; }
	log_rotate();
	@error_log(date("Y/m/d H:i:s").":".$_SERVER["SCRIPT_NAME"].":".$str."\n", 3, "/var/tmp/mobile.log");
}
//********************************************************************
//* エラーログ情報出力
//********************************************************************
function erl($str){
	log_rotate();
	@error_log(date("Y/m/d H:i:s").":".$_SERVER["SCRIPT_NAME"].":ERR:".$str."\n", 3, "/var/tmp/mobile.log");
}
//********************************************************************
//* ログローテーション
//********************************************************************
function log_rotate(){
	// 出力ログファイルサイズが１０Ｍを越えたらリネームしてバックアップ
	// 世代管理は、１世代のみ保持することにしておく。
	if(filesize("/var/tmp/mobile.log") > (10 * 1024 * 1000)){
		if(file_exists("/var/tmp/mobile_bef.log")){
			@unlink("/var/tmp/mobile_bef.log");
		}
		@rename("/var/tmp/mobile.log", "/var/tmp/mobile_bef.log");
	}
}

//////////////////////////////////////////////
//カスタマイズ設定を読み込む
//////////////////////////////////////////////
@include($D_DIR_COMPANY . "setting_option.inc");	// add 2008/08/22 matsukawa

// add 2012/01/10 Y.Matsukawa
//--------------------------------------------
// カスタムエラー
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
// リダイレクト関連
//--------------------------------------------
// add 2012/10/26 K.Masuda [
$D_LV_MOBTOSMT = array(	// 携帯			->	スマホ
	'1'  => '6',		// 1:33,129m	->	6:1/50万
	'2'  => '8',		// 2:11,388m	->	8:1/10万
	'3'  => '9',		// 3:4,658m		->	9:1/5万
	'4'  => '10',		// 4:2,458m		->	10:1/2万
	'5'  => '11',		// 5:1,100m		->	11:1/1万5000
	'6'  => '13',		// 6:485m		->	13:1/7500
	'7'  => '14',		// 7:242m		->	14:1/3500
	'8'  => '15',		// 8:129m		->	15:1/1500
	'9'  => '15',		// 9:97m		->	15:1/1500
);
// add 2012/10/26 K.Masuda ]

// スマホへリダイレクト先を地図ではなく詳細にするオプション		add 2012/12/17 H.Osamoto
if(!isset($REDIRECT_SMT_DETAIL)) $REDIRECT_SMT_DETAIL = '';
// 神奈川電通広告向けカスタマイズ		add 2012/12/17 H.Osamoto
if(!isset($D_KANA_DEN)) $D_KANA_DEN = '';			// 神奈川電通広告フラグ

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
// スマホアクセス時にPCへリダイレクト
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

// opt複数項目指定（COL_xx=1@COL_xx=1）の連結指定		add 2010/05/17 Y.Matsukawa
if (!isset($D_OPT_U_COND)) $D_OPT_U_COND = "AND";
// opt複数項目指定にAND固定で連結する項目				add 2010/05/17 Y.Matsukawa
if (!isset($D_OPT_EX_AND_COND)) $D_OPT_EX_AND_COND = array();
// 特定の検索でopt指定を無効化する		add 2011/08/25 Y.Matsukawa
if (!isset($D_OPT_NULL_SRCH)) $D_OPT_NULL_SRCH = array();

// optcd複数指定（optcd=1@2@3）の連結指定		add 2016/03/29 Y.Matsukawa
if (!isset($D_OPTCD_U_COND)) $D_OPTCD_U_COND = "OR";

// add 2010/06/21 Y.Matsukawa [
// 最寄り拠点検索件数（地図なし）
if (!isset($D_NSHOP_KNSU)) $D_NSHOP_KNSU = $D_SEARCH_LIST_PAGE;
// 最寄り拠点検索件数（地図付き）
if (!isset($D_NSHOP_MAP_KNSU)) $D_NSHOP_MAP_KNSU = 5;
if (!isset($D_NSHOP_MAP_LIST_PAGE)) $D_NSHOP_MAP_LIST_PAGE = 5;//1ページあたり件数	add 2016/06/01 Y.Matsukawa
// 最寄り遷移先（n：最寄り一覧、nm：最寄り地図）		add 2016/06/01 Y.Matsukawa
if (!isset($D_NSHOP_DIST)) $D_NSHOP_DIST = 'n';
// add 2010/06/21 Y.Matsukawa ]
// 企業画像使用		add 2012/02/13 Y.Matsukawa
if (!isset($D_USE_CP_IMG)) $D_USE_CP_IMG = 0;
//全件一覧
if(!isset($D_KLIST_PAGING)) $D_KLIST_PAGING = 0;	//ページング有無	add 2012/05/14 Y.Matsukawa
if(!isset($D_KLIST_PAGE)) $D_KLIST_PAGE = 10;		//１ページ行数		add 2012/05/14 Y.Matsukawa
// 最寄り施設検索件数	add 2012/12/17 H.Osamoto
if (!isset($D_NPOI_KNSU)) $D_NPOI_KNSU = 20;
if (!isset($D_NPOI_RAD)) $D_NPOI_RAD = 2000;

// 拠点データ取得時のカスタマイズ仕様		add 2012/11/19 Y.Matsukawa
if(!isset($D_NKYOTEN_CUST)) $D_NKYOTEN_CUST = '';			// 最寄拠点
if(!isset($D_KYOTENID_CUST)) $D_KYOTENID_CUST = '';			// 拠点ID
if(!isset($D_KYOTENLIST_CUST)) $D_KYOTENLIST_CUST = '';		// 拠点検索

//エリア検索NULLの場合の表示文言		add 2015/06/02 Y.Uesugi
if(!isset($D_SEARCH_SHOPA_DISPNM_NULL)) $D_SEARCH_SHOPA_DISPNM_NULL = "(その他)";

//店舗一覧ソート順指定		add 2015/06/01 Y.Uesugi
if(!isset($D_SHOPW_KYOTEN_SORT)) $D_SHOPW_KYOTEN_SORT = "";//店舗フリーワード検索
if(!isset($D_SHOPA_KYOTEN_SORT)) $D_SHOPA_KYOTEN_SORT = "";//エリア検索

// JCN様向けカスタマイズ（運休情報表示）		add 2012/11/19 Y.Matsukawa
if(!isset($D_JCN_UNKYU_TOP)) $D_JCN_UNKYU_TOP = 0;			// 運休情報表示
if(!isset($D_JCN_UNKYU_JKN)) $D_JCN_UNKYU_JKN = '';			// 運休情報表示条件

// 最寄検索結果が0件の場合再検索で取得する件数指定		add 2013/04/15 H.Osamoto
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;
// 住所リスト検索：エリア一覧		add 2013/05/30 Y.Matsukawa
if(!isset($D_ADDRLIST_AREA)) $D_ADDRLIST_AREA = 0;
// 都道府県限定（|区切りで列挙）		add 2013/05/30 Y.Matsukawa
if(!isset($D_SELECT_TODS)) $D_SELECT_TODS = '';
// エリア検索固定版を１階層（市区町村なし）で動作させる		add 2013/06/06 Y.Matsukawa
if(!isset($D_CL_NO_SHK)) $D_CL_NO_SHK = 0;

// 郵便番号検索0件時に住所リストへ遷移（ヤマト運輸カスタマイズ）		add 2013/07/31 H.Osamoto
if(!isset($D_ZIPW0_GOTO_PAGE)) $D_ZIPW0_GOTO_PAGE = '';
// 郵便番号検索一覧スキップ（最寄り一覧へ直接遷移）		add 2014/07/10 Y.Matsukawa
if(!isset($D_ZIPW_SKIP_LIST)) $D_ZIPW_SKIP_LIST = 0;

// 戻るボタン設置（ヤマト運輸カスタマイズ）		add 2013/07/31 H.Osamoto
if(!isset($D_YTC_BACK_BUTTON)) $D_YTC_BACK_BUTTON = '';

// ポリゴン内外判定カラム		add 2014/03/10 H.Osamoto
if(!isset($D_POLY_COL)) $D_POLY_COL = '';

// GPSログ出力		add 2015/11/18 Xuan Chien
if(!isset($D_MGPS_LOG)) $D_MGPS_LOG = '';

// 日本郵政版郵便番号検索		add 2016/06/13 Y.Matsukawa
if(!isset($D_JPPOST_SEARCH_ZIP)) $D_JPPOST_SEARCH_ZIP = 0;

// 詳細エラー時のリダイレクト先URL		add 2016/07/04 N.Wada
if(!isset($D_KID_NOTFOUND_REDIRECT_URL)) $D_KID_NOTFOUND_REDIRECT_URL = "";

// PC端末のリダイレクト先URL		add 2016/07/05 N.Wada
if(!isset($D_UA_PC_REDIRECT_URL)) $D_UA_PC_REDIRECT_URL = "";
// 不明端末のリダイレクト先URL		add 2016/07/05 N.Wada
if(!isset($D_UA_UNKOWN_REDIRECT_URL)) $D_UA_UNKOWN_REDIRECT_URL = "";

// 詳細のヘッダーテンプレートに、拠点データカラムのフラグを渡す(0:渡さない／1:渡す)		add 2016/07/28 N.Wada
if(!isset($D_DTL_HEADER_TEMPLATE_COL_EXIST_FLG)) $D_DTL_HEADER_TEMPLATE_COL_EXIST_FLG = 0;

// canonicalタグに出力するURL		add 2017/03/24 N.Wada
if(!isset($D_CANONICAL_URL)) $D_CANONICAL_URL = "";

// add 2017/05/11 H.Yasunaga ヤマト ロッカーセキュリティコード対応 [
if (!isset($D_YTC_SECURITY_CODE)) $D_YTC_SECURITY_CODE = 0;
// add 2017/05/11 H.Yasunaga ]

// add 2017/05/30 H.Yasunaga ヤマト ロッカーセキュリティコード対応 直接詳細画面に遷移しない [
if (!isset($D_YTC_SECURITY_CODE_NO_DIRECT_DTL)) $D_YTC_SECURITY_CODE_NO_DIRECT_DTL = 0;
// add 2017/05/30 H.Yasunaga ]
?>
