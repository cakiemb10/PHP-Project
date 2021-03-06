<?php
/*========================================================*/
// ファイル名：myarea_select.cgi
// 処理名：【Myエリア用CGI】Myエリア取得
//
// 更新履歴
// 2011/04/08 H.Osamoto		新規作成
/*========================================================*/
header( "Content-Type: Text/html; charset=euc-jp" );

/*==============================================*/
// CGIコード
/*==============================================*/
$CGICD = "m05";

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE1',    '00000' );      //正常終了（データ有り）
define( 'DEF_RETCD_DE2',    '00001' );      //正常終了（データ無し）
define( 'DEF_RETCD_DERR1', '17900' );      //データベースアクセスエラー
define( 'DEF_RETCD_DERR2', '17901' );      //Myエリア取得エラー

/*==============================================*/
// 定義ファイル
/*==============================================*/
include("d_serv_ora.inc");
include("oraDBAccess.inc");
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
$CORP_ID		= getCgiParameter('corp_id','');		/* 企業ID */
$USER_ID		= urldecode(getCgiParameter('user_id',''));		/* 内部管理番号 */

$USER_ID = str_replace(" ", "+", $USER_ID);

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$log_parms =  'CORP_ID:'.$CORP_ID;
$log_parms .= ' USER_ID:'.$USER_ID;


/*==============================================*/
// DB接続
/*==============================================*/
$dba = new oraDBAccess();
if (!$dba->open()) {
	$dba->close();
	exit(0);
}


/*==============================================*/
// Myエリアデータ取得
/*==============================================*/
$hit_num;			 // Myエリア登録数
$retdata = array();	 // Myエリアデータ

$retcd = select_myarea(&$dba, $CORP_ID, $USER_ID, &$hit_num, &$retdata);
if ($retcd != 0) {
	$dba->close();
	exit(0);
}

/*==============================================*/
// DBクローズ
/*==============================================*/
$dba->close();

/*==============================================*/
// Myエリアデータ出力
/*==============================================*/
print "$hit_num\n";
foreach($retdata as $rowdata){
	$buf = "";
	$buf =  $rowdata["MYAREA_ID"]   . "\t" .
			$rowdata["CORP_ID"]     . "\t" .
			$rowdata["USER_ID"]     . "\t" .
			$rowdata["MYAREA_NAME"] . "\t" .
			$rowdata["LAT"]         . "\t" .
			$rowdata["LON"]         . "\t" .
			$rowdata["DISP_ORDER"]  . "\t" .
	$buf .= "\n";
	print $buf;
}


exit(1);

?>
