<?php
/*========================================================*/
// ファイル名：get_holiday.cgi
// 処理名：祝日マスタ取得
//
// 更新履歴
// 2016/10/17 Y.Uesugi		新規作成
// 2016/10/25 Y.Uesugi		パラメータ(ymd)を指定可能に修正
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_ora.inc');
	require_once('inc/oraDBAccess.inc');
	require_once('log.inc');

	/*==============================================*/
	// ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');
	include('function.inc');			// 共通関数

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = "h01";

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');		/* 企業ID */
	$YMD		= getCgiParameter('ymd', 	'');		/* 日付 */				// add 2016/10/25 Y.Uesugi

	$KEY = '';
	$OPTION_CD = $D_CID;
	$parms = '';

	// mod 2016/10/25 Y.Uesugi [
	// 祝日判定を実施する日を指定
	if(($YMD != "") && strlen($YMD) == 8 ){
		// 今日の日付
		$year = substr($YMD, 0, 4);
		$month = substr($YMD, 4, 2);
		$day = substr($YMD, 6, 2);
	} else {
		// 今日の日付
		$year = date('Y');
		$month = date('m');
		$day = date('d');
	}
	// mod 2016/10/25 Y.Uesugi ]

	// SQL
	$sql = "select count(*) as CNT";
	$sql .= " from HOLIDAY_MST_TBL";
	$sql .= " where CORP_ID = '" .escapeOra($CID) ."'";
	$sql .= " and YEAR = '$year'";
	$sql .= " and MONTH = '$month'";
	$sql .= " and DAY = '$day'";

	// DB接続
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17900", $KEY, $OPTION_CD, $parms);
		exit;
	}

	// SQL問い合わせ実行処理
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17999", $KEY, $OPTION_CD, $parms);
		exit;
	}

	// データ取得
	$ret = null;
	if(!$dba->getRecInto($stmt, $ret, OCI_ASSOC)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."11009\t0\t0\n";
		put_log($CGICD."11009", $KEY, $opt, $parms);
		exit;
	}
	$dba->free($stmt);
	$dba->close();

	print $CGICD."00000\t$reccount\t$reccount\n";
	put_log($CGICD."00000", $KEY, $opt, $parms);

	//曜日番号（日:0 月:1 火:2 水:3 木:4 金:5 土:6 / 祝:7）を返却
	if($ret['CNT'] > 0){
		$bool = true;
	}else {
		$bool = false;
	}

	$bool = mb_convert_encoding($bool, 'eucJP-win', 'eucJP-win');
	printf( "%d", $bool);
?>
