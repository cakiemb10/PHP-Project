<?php
/*========================================================*/
// �ե�����̾��ibeacon_get_data.cgi
// ����̾��iBeacon�������
//
// ��������
// 2014/11/17 H.Osamoto		��������
// 2014/12/01 C.Eguchi      ����������³��
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'b02';

	/*==============================================*/
	// ���������
	/*==============================================*/
	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������
	define( 'DEF_RETCD_DNE'  ,'11009' );	   // ���˸��礦�ǡ����ʤ�
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
	include('oraDBAccess.inc');
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
	$BID		= getCgiParameter('bid', 	'');		/* BeaconID */
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

	/* BeaconID */
	if ($BID == '') {
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
	// ǧ�ڥ����å�
	/*==============================================*/
	if($KEY !== AUTH_KEY) {
		$status = DEF_RETCD_PERR2;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// �оݥǡ�������
	/*==============================================*/
	$sql  = " SELECT ";
	$sql .= " CORP_ID, BEACON_ID, INS_DT, MSG, DISP_TYPE, FUNC, KYOTEN_ID ";	// �Ȥꤢ����������������
	$sql .= " FROM EMAP_APL_BEACON_DATA_TBL ";
	$sql .= " WHERE ";
	$sql .= " CORP_ID = '" . $CID . "'";
	$sql .= " AND ";
	$sql .= " BEACON_ID = '" . $BID . "'";

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR2;
	}
	else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			// CORP_ID,BEACON_ID��ɬ��1��
			$beacon['beacon_id'] = $data["BEACON_ID"];
			$beacon['msg']       = $data["MSG"];
			$beacon['kyoten_id'] = $data["KYOTEN_ID"];
			$beacon['disp_type'] = $data["DISP_TYPE"];
			$beacon['func']      = $data["FUNC"];
		}
		else {
			$status = DEF_RETCD_DNE;
		}
		$dba->free($stmt);
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
        exit;
    }
	
	/*==============================================*/
	// ���ｪλ
	/*==============================================*/


	$out_data = array("return_code" => $CGICD.$status, "beacon" => $beacon);
	output_json(RET_ENC, $out_data);
	exit;

?>
