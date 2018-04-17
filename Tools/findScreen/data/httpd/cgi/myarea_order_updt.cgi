<?php
/*========================================================*/
// ファイル名：myarea_order_updt.cgi
// 処理名：【Myエリア用CGI】Myエリア表示順序更新
//
// 更新履歴
// 2011/04/08 H.Osamoto		新規作成
/*========================================================*/


/*==============================================*/
// CGIコード
/*==============================================*/
$CGICD = "m03";

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE',    '00000' );      //正常終了
define( 'DEF_RETCD_DERR1', '17900' );      //データベースアクセスエラー
define( 'DEF_RETCD_DERR2', '17901' );      //Myエリア更新エラー

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
$MYAREA_ID		= getCgiParameter('myarea_id','');		/* MyエリアID */
$CORP_ID		= getCgiParameter('corp_id','');		/* 企業ID */
$USER_ID		= urldecode(getCgiParameter('user_id',''));		/* 内部管理番号 */
$DISP_ORDER		= getCgiParameter('disp_order','');		/* 表示順序 */

$USER_ID = str_replace(" ", "+", $USER_ID);

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$log_parms =  'MYAREA_ID:'.$MYAREA_ID;
$log_parms .= ' CORP_ID:'.$CORP_ID;
$log_parms .= ' USER_ID:'.$USER_ID;
$log_parms .= ' DISP_ORDER:'.$DISP_ORDER;


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
$retcd = myarea_order_update(&$dba, $MYAREA_ID, $CORP_ID, $USER_ID, $DISP_ORDER, &$rtncd);
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
