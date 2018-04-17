<?php
/*========================================================*/
// �ե�����̾��get_holiday.cgi
// ����̾�������ޥ�������
//
// ��������
// 2016/10/17 Y.Uesugi		��������
// 2016/10/25 Y.Uesugi		�ѥ�᡼��(ymd)������ǽ�˽���
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_ora.inc');
	require_once('inc/oraDBAccess.inc');
	require_once('log.inc');

	/*==============================================*/
	// �����ϳ���
	/*==============================================*/
	include('logs/inc/com_log_open.inc');
	include('function.inc');			// ���̴ؿ�

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = "h01";

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');		/* ���ID */
	$YMD		= getCgiParameter('ymd', 	'');		/* ���� */				// add 2016/10/25 Y.Uesugi

	$KEY = '';
	$OPTION_CD = $D_CID;
	$parms = '';

	// mod 2016/10/25 Y.Uesugi [
	// ����Ƚ���»ܤ����������
	if(($YMD != "") && strlen($YMD) == 8 ){
		// ����������
		$year = substr($YMD, 0, 4);
		$month = substr($YMD, 4, 2);
		$day = substr($YMD, 6, 2);
	} else {
		// ����������
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

	// DB��³
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17900", $KEY, $OPTION_CD, $parms);
		exit;
	}

	// SQL�䤤��碌�¹Խ���
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17999", $KEY, $OPTION_CD, $parms);
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
		$bool = true;
	}else {
		$bool = false;
	}

	$bool = mb_convert_encoding($bool, 'eucJP-win', 'eucJP-win');
	printf( "%d", $bool);
?>
