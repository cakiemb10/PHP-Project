<?php
/*========================================================*/
// ファイル名：lw_searchpoi.cgi
// 処理名：【ローソン向けカスタマイズ】施設検索
//
// 更新履歴
// 2010/12/21 H.Osamoto	新規作成
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/11/28 H.Osamoto	ログ出力不具合修正
// 2012/10/17 Y.Matsukawa	error_reporting()削除
// 2012/11/21 K.Masuda		UTF-8でFREWD文字化け不具合対応（「大宮」「山」など）
// 2015/10/29 H.Osamoto		検索対象ジャンルから「買い物(00140)」を除外
/*========================================================*/

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off対応
//入力パラメータを取り込む処理を追加
//get
extract($_GET);

/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = 'w04';

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));
$APICGINM = "searchpoi.cgi";

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_AERR', '12009' );       //認証エラー

/*==============================================*/
// 定義ファイル
/*==============================================*/
require_once('lw_def.inc');				// ローソン用定義
require_once('function.inc');			// 共通関数
require_once('log.inc');				// ログ出力
require_once('auth.inc');				// 簡易認証
require_once('cgi_key.inc');			// emapCGIキー他

/*==============================================*/
// エラー出力を明示的にOFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
//error_reporting(0);		del 2012/10/17 Y.Matsukawa

/*==============================================*/
//ログ出力開始
/*==============================================*/
include('logs/inc/com_log_open.inc');

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// 初期化
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
if (!isset($status)) $status = 00000;
$emap_cid = $D_CID;    //企業コード固定　lw_def.incで定義
// add 2011/09/29 Y.Nakajima ]


/*==============================================*/
// パラメータ取得
/*==============================================*/
$KEY		= $D_CGI_KEY;							/* CGIキー */
$CID		= getCgiParameter('cid','');			/* 企業ID */
$SID		= getCgiParameter('sid','');			/* サービスID */
$POS		= getCgiParameter('pos','1');			/* 取得位置 */
$CNT		= getCgiParameter('cnt','100');			/* 取得件数 */
$ENC		= getCgiParameter('enc','SJIS');		/* 文字コード (OUT) */
$TOD		= getCgiParameter('tod','00');			/* 都道府県コード */
$SHK		= getCgiParameter('shk','000');			/* 市区町村コード */
$JNRNM		= getCgiParameter('jnrmn','');			/* ジャンルメニューコード */
$JNR		= getCgiParameter('jnr','');			/* ジャンルコード */
$SRCHMODE	= getCgiParameter('srchmode','0');		/* 検索モード */
$SRCHTARGET	= getCgiParameter('srchtarget','0');	/* フリーワード検索対象 */
$SRCHTYPE	= getCgiParameter('srchtype','0');		/* キーワード結合条件 */
$FREWD		= getCgiParameter('frewd','');			/* フリーワード */
$PFLG		= getCgiParameter('pflg','2');			/* ポイントフラグ */
$DATUM		= getCgiParameter('datum','TOKYO');		/* 測地系 */
$OUTF		= getCgiParameter('outf','TSV');		/* 出力形式 */

// add 2015/10/29 H.Osamoto [
// 「買い物(00140)」以外をすべてを固定で指定
$JNRNM = "00110,00120,00130,00160,00170,00220,00240,00250";
// add 2015/10/29 H.Osamoto ]

/*==============================================*/
// フリーワードエンコード
/*==============================================*/
switch ($ENC) {
	case "EUC":
		$frewd_org = mb_convert_encoding($FREWD, "EUC-JP", "EUC-JP, UTF-8, SJIS, auto");
		$FREWD = urlencode($frewd_org);
		break;
	case "SJIS":
		$frewd_org = mb_convert_encoding($FREWD, "SJIS", "EUC-JP, UTF-8, SJIS, auto");
		$FREWD = urlencode($frewd_org);
		break;
	case "UTF8":
		//$frewd_org = mb_convert_encoding($FREWD, "UTF-8", "EUC-JP, UTF-8, SJIS, auto");	// mod 2012/11/21 K.Masuda
		$frewd_org = mb_convert_encoding($FREWD, "UTF-8", "auto");
		$FREWD = urlencode($frewd_org);
		break;
	default:
		$frewd_org = mb_convert_encoding($FREWD, "SJIS", "EUC-JP, UTF-8, SJIS, auto");
		$FREWD = urlencode($frewd_org);
	break;
}


/*==============================================*/
// 簡易認証（IPチェック／リファラチェック）
/*==============================================*/
//if (!ip_check($D_IP_LIST, "218.225.89.14")) {
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	if (!referer_check(&$D_REFERER_LIST, $_SERVER['HTTP_REFERER'])) {
		$status = DEF_RETCD_AERR;
		$KEY = '';		/* キーを空にして意図的に認証エラーにさせる */ 
		// mod 2011/09/29 Y.Nakajima
		//put_log($CGICD.$status, $parms);
		put_log($CGICD.$status, $KEY,$emap_cid,$status);
	}
}

/*==============================================*/
// 実行用にパラメータ値を結合
/*==============================================*/
$parms =  '?key='.$KEY;
$parms .= '&cid='.$CID;
$parms .= '&sid='.$SID;
$parms .= '&pos='.$POS;
$parms .= '&cnt='.$CNT;
$parms .= '&enc='.$ENC;
$parms .= '&tod='.$TOD;
$parms .= '&shk='.$SHK;
$parms .= '&jnrmn='.$JNRNM;
$parms .= '&jnr='.$JNR;
$parms .= '&srchmode='.$SRCHMODE;
$parms .= '&srchtarget='.$SRCHTARGET;
$parms .= '&srchtype='.$SRCHTYPE;
$parms .= '&frewd='.$FREWD;
$parms .= '&pflg='.$PFLG;
$parms .= '&datum='.$DATUM;
$parms .= '&outf='.$OUTF;

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
// mod 2011/11/28 H.Osamoto [
//	$log_parms  = 'KEY:'.$KEY;
//	$log_parms .= ' CID:'.$CID;
$log_parms  = 'CID:'.$CID;
// mod 2011/11/28 H.Osamoto ]
$log_parms .= ' POS:'.$POS;
$log_parms .= ' CNT:'.$CNT;
$log_parms .= ' ENC:'.$ENC;
$log_parms .= ' TOD:'.$TOD;
$log_parms .= ' SHK:'.$SHK;
$log_parms .= ' JNRNM:'.$JNRNM;
$log_parms .= ' JNR:'.$JNR;
$log_parms .= ' SRCHMODE:'.$SRCHMODE;
$log_parms .= ' SRCHTARGET:'.$SRCHTARGET;
$log_parms .= ' SRCHTYPE:'.$SRCHTYPE;
//$log_parms .= ' FREWD:'.$FREWD;	// mod 2011/11/28 H.osamoto
$log_parms .= mb_strimwidth(' FREWD:'.$FREWD, 0, 255, '...');
$log_parms .= ' PFLG:'.$PFLG;
$log_parms .= ' DATUM:'.$DATUM;
$log_parms .= ' OUTF:'.$OUTF;


unset($result);
$CGI = 'http://'.$API_SSAPI_SRV.'/ssapi/'.$APICGINM.$parms;

// e-mapCGI
$result = file_get_contents($CGI);
// ログ出力
// mod 2011/09/29 Y.Nakajima
//put_log($CGICD.$status, $parms);
//put_log($CGICD.$status, $KEY,$emap_cid, $parms);	// mod 2011/11/28 H.Osamoto
put_log($CGICD.$status, $KEY,$emap_cid, $log_parms);

switch ($OUTF) {
	case 'XML':
		// XML出力
		header ("Content-Type: text/xml; charset=$ENC");
		echo $result;
		break;
	default:
		// TSV出力
		header("Content-Type: zdc-api/searchpoi");
		echo $result;
}

exit;

?>
