<?php
/*========================================================*/
// �ե�����̾��ytc_get_holiday.cgi
// ����̾���ڥ�ޥȱ�͢�͸����������ޥ����۽����ޥ�������
//
// ��������
// 2015/12/15 Y.Uesugi		��������
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_ora.inc');
	require_once('inc/oraDBAccess.inc');
	require_once('log.inc');

	// �����ϳ���
	include('logs/inc/com_log_open.inc');

	$CGICD = 'y01';
	$enc = 'EUC';

	$KEY = '';
	$OPTION_CD = $D_CID;
	$parms = '';

	// ����������
	$year = date('Y');
	$month = date('m');
	$day = date('d');

	// SQL
	$sql = "select count(*) as CNT";
	$sql .= " from HOLIDAY_MST_YMT_TBL";
	$sql .= " where YEAR = '$year'";
	$sql .= " and MONTH = '$month'";
	$sql .= " and DAY = '$day'";

	// DB��³
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17900", $KEY, $opt, $parms);
		exit;
	}

	// SQL�䤤��碌�¹Խ���
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17999", $KEY, $opt, $parms);
		exit;
	}

	// �ǡ�������
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

	//�����ֹ����:0 ��:1 ��:2 ��:3 ��:4 ��:5 ��:6 / ��:7�ˤ��ֵ�
	if($ret['CNT'] > 0){
		$weekno = 7;
	}else {
		$weekno = date('w');
	}

	$weekno = mb_convert_encoding($weekno, 'eucJP-win', 'eucJP-win');
	printf( "%02s", $weekno);
?>
