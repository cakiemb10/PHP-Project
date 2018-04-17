<?php
/*========================================================*/
// ファイル名：poi_search.cgi
// 処理名：チェックイン-POI検索(ラッパーCGI）
//
// 更新履歴
// 2012/12/12 H.Iijima	新規作成
// 
// 
/*========================================================*/
//get
extract($_GET);

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));


$APICGINM = $CGINM;
/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = $CGINM;



/*==============================================*/
// 定義ファイル
/*==============================================*/
require_once('aplia_def.inc');			// 共通定義ファイル
require_once('function.inc');			// 共通関数
//require_once('log.inc');				// ログ出力

/*==============================================*/
// エラー出力を明示的にOFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
error_reporting(E_ALL);
//error_reporting(0);

/*==============================================*/
//ログ出力開始
/*==============================================*/
//include('logs/inc/com_log_open.inc');

/*==============================================*/
// パラメータ取得
/*==============================================*/
$SID		= getCgiParameter('sid','');		/* スキーマ名 */
$CK			= getCgiParameter('ck','');			/* コンテンツ区分 */
$LATLON		= getCgiParameter('latlon','');		/* 緯度経度 */
$FREEWD		= getCgiParameter('freewd','');		/* フリーワード */
$RAD		= getCgiParameter('rad','');		/* 半径 */
$SORT		= getCgiParameter('sort','');		/* ソート */
$POS		= getCgiParameter('pos','');		/* 取得位置 */
$CNT		= getCgiParameter('cnt','');		/* 取得件数 */


/*==============================================*/
// 実行用にパラメータ値を結合
/*==============================================*/
$parms = '?sid='.$SID;
$parms .= '&ck='.$CK;
$parms .= '&latlon='.$LATLON;
$parms .= '&freewd='.$FREEWD;
$parms .= '&rad='.$RAD;
$parms .= '&sort='.$SORT;
$parms .= '&pos='.$POS;
$parms .= '&cnt='.$CNT;

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
/*
$log_parms  = ' SID:'.$SID;
$log_parms .= ' CK:'.$CK;
$log_parms .= ' LATLON:'.$LATLON;
$log_parms .=  mb_strimwidth(' FREEWD:'.mb_convert_encoding($FREEWD,'EUC-JP','auto'), 0, 255, '...');
$log_parms .= ' RAD:'.$RAD;
$log_parms .= ' SORT:'.$SORT;
$log_parms .= ' POS:'.$POS;
$log_parms .= ' CNT:'.$CNT;
*/
/*==============================================*/
// APLIA CGI 呼び出し
/*==============================================*/

unset($result);
$CGIURL ='http://'.$API_APLIA_SRV.$API_APLIA_PATH;
$CGI = $CGIURL.$APICGINM.$parms;
$result = file_get_contents($CGI);

// ログ出力
//put_log($CGICD, $SID,$http_response_header[0]."(".$CGIURL.")", $log_parms);

header($http_response_header[0], FALSE);
Header("Content-type: application/json; charset=utf-8");
echo $result;
exit;

?>
