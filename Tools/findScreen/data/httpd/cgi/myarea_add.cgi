<?php
/*========================================================*/
// ファイル名：myarea_add.cgi
// 処理名：【Myエリア用CGI】Myエリア追加
//
// 更新履歴
// 2011/04/08 H.Osamoto		新規作成
/*========================================================*/


/*==============================================*/
// CGIコード
/*==============================================*/
$CGICD = "m01";

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE',    '00000' );      //正常終了
define( 'DEF_RETCD_DE7',   '00007' );      //Myエリア名称登録文字数オーバー
define( 'DEF_RETCD_DE8',   '00008' );      //Myエリア登録可能数オーバー
define( 'DEF_RETCD_DE9',   '00009' );      //機種依存文字エラー
define( 'DEF_RETCD_DERR1', '17900' );      //データベースアクセスエラー
define( 'DEF_RETCD_DERR2', '17901' );      //Myエリア登録数取得エラー
define( 'DEF_RETCD_DERR3', '17902' );      //Myエリア追加登録エラー

/*==============================================*/
// 登録可能文字数
/*==============================================*/
$MAX_NM_LEN = 100;	// 100byte

/*==============================================*/
// 定義ファイル
/*==============================================*/
include("d_serv_ora.inc");
include("oraDBAccess.inc");
include("oraDBAccessMst.inc");	// mstDB専用
include("function.inc");		// 共通関数
include("myarea_func.inc");		// Myエリア用関数
include("log.inc");				// ログ出力

/*==============================================*/
// エラー出力を明示的にOFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
error_reporting(0);

/*==============================================*/
//ログ出力開始
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// パラメータ取得
/*==============================================*/
$CORP_ID		= getCgiParameter('corp_id','');				/* 企業ID */
$USER_ID		= urldecode(getCgiParameter('user_id',''));				/* 内部管理番号 */
$MYAREA_NAME	= urldecode(getCgiParameter('myarea_name',''));	/* Myエリア名 */
$LAT			= getCgiParameter('lat','');					/* 緯度 */
$LON			= getCgiParameter('lon','');					/* 経度 */

$USER_ID = str_replace(" ", "+", $USER_ID);

// 半角カナ⇒全角カナに変換
$MYAREA_NAME = mb_convert_kana($MYAREA_NAME, "KV");


/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$log_parms =  'CORP_ID:'.$CORP_ID;
$log_parms .= ' USER_ID:'.$USER_ID;
$log_parms .= ' MYAREA_NAME:'.$MYAREA_NAME;
$log_parms .= ' LAT:'.$LAT;
$log_parms .= ' LON:'.$LON;


// 文字数チェックチェック
$str_len = strlen($MYAREA_NAME);
if (strlen($MYAREA_NAME) > $MAX_NM_LEN){
	// Myエリア名称文字数オーバー
	echo $CGICD.DEF_RETCD_DE7;
	exit(0);
}

// 機種依存文字チェック
if (!IzonSearch($MYAREA_NAME)){
	// 機種依存文字有り
	echo $CGICD.DEF_RETCD_DE9;
	exit(0);
}

/*==============================================*/
// DB接続
/*==============================================*/
$dba = new oraDBAccessMst();
if (!$dba->open()) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DERR1;
	exit(0);
}

/*==============================================*/
// Myエリアデータ取得
/*==============================================*/
$hit_num;			 // Myエリア登録数
$retdata = array();	 // Myエリアデータ

$retcd = select_myarea(&$dba, $CORP_ID, $USER_ID, &$hit_num, &$retdata);
if ($retcd != 0 && $retcd != 1) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DERR2;
	exit(0);
}

if ($hit_num >= 5) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DE8;
	exit(0);
}

/*==============================================*/
// Myエリア追加登録
/*==============================================*/
$retcd = myarea_add(&$dba, $CORP_ID, $USER_ID, $MYAREA_NAME, $LAT, $LON, &$rtncd);
if (trim($rtncd) != "0000" || !$retcd) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DERR3;
	exit(0);
}

/*==============================================*/
// DBクローズ
/*==============================================*/
$dba->close();

echo $CGICD.DEF_RETCD_DE;
exit(1);

?>
