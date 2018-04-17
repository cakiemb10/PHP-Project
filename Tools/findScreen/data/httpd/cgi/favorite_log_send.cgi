<?php
/*========================================================*/
// �ե�����̾��favorite_log_send.cgi
// ����̾�������������������
//
// ��������
// 2014/11/07 H.Osamoto		��������
// 2014/12/01 C.Eguchi		����������³��
// 2014/12/04 H.Osamoto		DB��³����ѹ�(PUB��MST)
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'f01';

	/*==============================================*/
	// ���������
	/*==============================================*/
	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
	define( 'DEF_RETCD_AERR', '12009' );       // �ץ�ȥ��륨�顼
	define( 'DEF_RETCD_DERR1','17900' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR2','17002' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR3','17999' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_PERR1','19100' );       // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19101' );       // ���ϥѥ�᡼�����顼(ǧ�ڥ��顼)

	define( 'RET_ENC' , 'UTF8');				// headerʸ��������

	/* ǧ�ڥ��� */
	define( 'AUTH_KEY','emxINzp1exRgemQRG3paCmsFcemyp6Im4JKSs' );       // ǧ�ڥ���(����)

	/*==============================================*/
	// ����ե�����
	/*==============================================*/
	include('d_serv_emap.inc');
	include('store_def.inc'); 
	include('store_outf.inc');			// ���ϥ��饹���
	include('ZdcCommonFuncAPI.inc');	// ���̴ؿ�
	include('function.inc');			// ���̴ؿ�
	include('d_serv_ora.inc');
	//	include('oraDBAccess.inc');		// mod 2014/12/04 H.Osamoto
	include('oraDBAccessMst.inc');
	include('chk.inc');				// �ǡ��������å���Ϣ
	include('log.inc');				// ������
	include('auth.inc');			// �ʰ�ǧ��
	include("jkn.inc");				// �ʤ���߾���Խ�
	include('apl_outf.inc');		// JSON������

	/*==============================================*/
	// ���顼���Ϥ�����Ū��OFF
	/*==============================================*/
	//error_reporting(E_ALL^E_NOTICE);
	//error_reporting(0);
	if ($D_DEBUG) ini_set('display_errors', '1');

	/*==============================================*/
	// �����
	/*==============================================*/
	// ���ơ�����(�꥿���󥳡���)
	if (!isset($status)){
		 $status = DEF_RETCD_DE;
	}

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');		/* ���ID */
	$UID		= getCgiParameter('uid', 	'');		/* �桼��ID */
	$KID		= getCgiParameter('kid', 	'');		/* ����ID */
	$KEY		= getCgiParameter('key',	'');		/* ǧ�ڥ��� */

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* ���ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	
	/* �桼��ID */
	if ($UID == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* ����ID */
	if ($KID == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* ǧ�ڥ��� */
	if ($KEY == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// ǧ�ڥ����Υ����å�
	/*==============================================*/
	if($KEY !== AUTH_KEY) {
		$status = DEF_RETCD_PERR2;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// HTTPSɬ�ܥ����å�
	/*==============================================*/
	if($_SERVER['HTTPS'] != 'on') {
		$status = DEF_RETCD_AERR;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	//	$dba = new oraDBAccess();		// mod 2014/12/04 H.Osamoto
	$dba = new oraDBAccessMst();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// [EMAP_APL_FAVORITE_LOG_TBL]�ơ��֥�˥ǡ�����Ǽ
	/*==============================================*/

	$sql  = " INSERT INTO EMAP_APL_FAVORITE_LOG_TBL(";
	$sql .= " CORP_ID, USER_ID, KYOTEN_ID, INS_DT";
	$sql .= " ) VALUES ( ";
	$sql .= "'" .  $CID . "' , '" .$UID . "' , '" .$KID . "' , SYSDATE";
	$sql .= " )";

	$stmt = null;

	if (!$dba->sqlExecute($sql, $stmt)) {
		//����Хå�
		$dba->rollbackTransaction();
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	else {
		// ���ߥå�
		$res = $dba->commitTransaction();
		if (!$res) {
			$status = DEF_RETCD_DERR3;
			output_json(RET_ENC, array("return_code" => $CGICD.$status));
			exit;
		}
	}
	/*==============================================*/
	// ���ｪλ
	/*==============================================*/
	output_json(RET_ENC, array("return_code" => $CGICD.$status));
	exit;

	/*==============================================*/
	// ����
	/*==============================================*/
	$dba->close();

?>
