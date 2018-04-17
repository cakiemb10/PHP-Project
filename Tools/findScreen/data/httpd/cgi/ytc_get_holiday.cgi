<?php
/*========================================================*/
// ファイル名：ytc_get_holiday.cgi
// 処理名：【ヤマト運輸様向けカスタマイズ】祝日マスタ取得
//
// 更新履歴
// 2015/12/15 Y.Uesugi		新規作成
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_ora.inc');
	require_once('inc/oraDBAccess.inc');
	require_once('log.inc');

	// ログ出力開始
	include('logs/inc/com_log_open.inc');

	$CGICD = 'y01';
	$enc = 'EUC';

	$KEY = '';
	$OPTION_CD = $D_CID;
	$parms = '';

	// 今日の日付
	$year = date('Y');
	$month = date('m');
	$day = date('d');

	// SQL
	$sql = "select count(*) as CNT";
	$sql .= " from HOLIDAY_MST_YMT_TBL";
	$sql .= " where YEAR = '$year'";
	$sql .= " and MONTH = '$month'";
	$sql .= " and DAY = '$day'";

	// DB接続
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17900", $KEY, $opt, $parms);
		exit;
	}

	// SQL問い合わせ実行処理
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17999", $KEY, $opt, $parms);
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
		$weekno = 7;
	}else {
		$weekno = date('w');
	}

	$weekno = mb_convert_encoding($weekno, 'eucJP-win', 'eucJP-win');
	printf( "%02s", $weekno);
?>
