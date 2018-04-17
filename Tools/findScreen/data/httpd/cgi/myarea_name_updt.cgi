<?php
/*========================================================*/
// ファイル名：myarea_name_updt.cgi
// 処理名：【Myエリア用CGI】Myエリア名更新
//
// 更新履歴
// 2011/04/08 H.Osamoto		新規作成
// 2011/07/04 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
/*========================================================*/


/*==============================================*/
// CGIコード
/*==============================================*/
$CGICD = "m02";

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE',    '00000' );      //正常終了
define( 'DEF_RETCD_DE7',   '00007' );      //Myエリア名称登録文字数オーバー
define( 'DEF_RETCD_DE9',   '00009' );      //機種依存文字エラー
define( 'DEF_RETCD_DERR1', '17900' );      //データベースアクセスエラー
define( 'DEF_RETCD_DERR2', '17901' );      //Myエリア更新エラー

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
$MYAREA_ID		= getCgiParameter('myarea_id','');				/* MyエリアID */
$CORP_ID		= getCgiParameter('corp_id','');				/* 企業ID */
$MYAREA_NAME	= urldecode(getCgiParameter('myarea_name',''));	/* Myエリア名 */

// add 2011/07/05 Y.Nakajima 
if (!isset($USER_ID)) $USER_ID = "";
$USER_ID = str_replace(" ", "+", $USER_ID);

// 半角カナ⇒全角カナに変換
$MYAREA_NAME = mb_convert_kana($MYAREA_NAME, "KV");


/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$log_parms =  'MYAREA_ID:'.$MYAREA_ID;
$log_parms .= ' CORP_ID:'.$CORP_ID;
$log_parms .= ' MYAREA_NAME:'.$MYAREA_NAME;


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
// Myエリア更新
/*==============================================*/
$retcd = myarea_name_update(&$dba, $MYAREA_ID, $MYAREA_NAME, &$rtncd);
if (trim($rtncd) != "0000" || !$retcd) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DERR2;
	exit(0);
}

/*==============================================*/
// DBクローズ
/*==============================================*/
$dba->close();

echo $CGICD.DEF_RETCD_DE;
exit(1);

?>
