<?php
/*========================================================*/
// �ե�����̾��enquete_send.cgi
// ����̾����3��  ���󥱡��ȷ������
//
// ��������
// 2014/11/07 H.Osamoto		��������
// 2014/12/02 C.Eguchi      ����������³��
// 2014/12/04 H.Osamoto		DB��³����ѹ�(PUB��MST)
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'e01';

	/*==============================================*/
	// ���������
	/*==============================================*/
	/* ���ϥѥ�᡼��*/
	define( 'DEF_PRM_ENC_UTF8',		'UTF8' );       // ʸ�������ɡ�UTF8��
	define( 'DEF_PRM_ENC_SJIS',		'SJIS' );       // ʸ�������ɡ�SJIS��
	define( 'DEF_PRM_ENC_EUC',		'EUC'  );       // ʸ�������ɡ�EUC��
	
	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
	define( 'DEF_RETCD_ERR1' ,'11009' );       // ���󥱡��ȷ����Ͽ�Ѥߥ��顼
	define( 'DEF_RETCD_AERR' ,'12009' );       // �ץ�ȥ��륨�顼
	define( 'DEF_RETCD_DERR1','17900' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR2','17002' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR3','17999' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_PERR1','19100' );       // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19101' );       // ���ϥѥ�᡼�����顼(ǧ�ڥ��顼)

	/* ǧ�ڥ��� */
	define( 'AUTH_KEY','emxINzp1exRgemQRG3paCmsFcemyp6Im4JKSs' );       // ǧ�ڥ���(����)
	
	/* ���ܺ�����ܿ� */
	define( 'TEXT_MAX', 30 );       // �ƥ����ȹ���
	define( 'LIST_MAX', 30 );       // �ꥹ�ȹ���
	define( 'FLG_MAX' , 50 );       // �ե饰����

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
	$KEY		= getCgiParameter('key',	'');		/* ǧ�ڥ��� */
	$ENC		= getCgiParameter('enc',	DEF_PRM_ENC_UTF8);		/* ʸ�������� */

	for ($t = 1; $t <= TEXT_MAX; $t++) {
		$TEXT[$t] = getCgiParameter('text' . $t,	'');		/* �ƥ����ȹ��� */
	}
	for ($l = 1; $l <= LIST_MAX; $l++) {
		$LIST[$l] = getCgiParameter('list' . $l,	'');		/* �ꥹ�ȹ��� */
	}
	for ($f = 1; $f <= FLG_MAX; $f++) {
		$FLG[$f] = getCgiParameter('flg' . $f,	'');		/* �ե饰���� */
	}

	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	include('store_enc.inc');                       // ʸ���������Ѵ�

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* ���ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	
	/* �桼��ID */
	if ($UID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* ǧ�ڥ��� */
	if ($KEY == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* ʸ�������� */
	if ($INPUT_ENC  != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC  != DEF_PRM_ENC_EUC &&
		$INPUT_ENC  != DEF_PRM_ENC_UTF8) {
		
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// ǧ�ڥ����å�
	/*==============================================*/
	if($KEY !== AUTH_KEY) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// httpsɬ��ɬ�ܥ����å�
	/*==============================================*/
	if($_SERVER['HTTPS'] != 'on') {
		$status = DEF_RETCD_AERR;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// TEXT��ʸ���������Ѵ�
	/*==============================================*/
	for ($t = 1; $t <= TEXT_MAX; $t++) {
		if ($TEXT[$t] != '') {
			$TEXT[$t] = f_enc_to_EUC($TEXT[$t]);
		}
	}

	/*==============================================*/
	// LIST��ʸ���������Ѵ�
	/*==============================================*/
	for ($l = 1; $l <= LIST_MAX; $l++) {
		if ($LIST [$l] != '') {
			$LIST [$l] = f_enc_to_EUC($LIST[$l]);
		}
	}

	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	//	$dba = new oraDBAccess();		// mod 2014/12/04 H.Osamoto
	$dba = new oraDBAccessMst();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// [EMAP_APL_BEACON_LOG_TBL]�ơ��֥�˥ǡ�����Ǽ
	/*==============================================*/
	$sql  = " INSERT INTO EMAP_APL_ENQUETE_LOG_TBL (";
	$sql .= " CORP_ID, USER_ID, INS_DT";
	// TEXT
	for ($t = 1; $t <= TEXT_MAX; $t++) {
		$sql .= ", TEXT_" . sprintf("%02d", $t);
	}
	// LIST
	for ($l = 1; $l <= LIST_MAX; $l++) {
		$sql .= ", LIST_" . sprintf("%02d", $l);
	}
	// FLG
	for ($f = 1; $f <= FLG_MAX; $f++) {
		$sql .= ",  FLG_" . sprintf("%02d", $f);
	}
	$sql .= " ) VALUES ( ";
	$sql .= "'" .  $CID . "' , '" .$UID . "' , SYSDATE";
	// TEXT
	for ($t = 1; $t <= TEXT_MAX; $t++) {
		$sql .= ", '" . $TEXT[$t] . "'";
	}
	// LIST
	for ($l = 1; $l <= LIST_MAX; $l++) {
		$sql .= ", '" . $LIST[$l] . "'";
	}
	// FLG
	for ($f = 1; $f <= FLG_MAX; $f++) {
		$sql .= ", '" . $FLG[$f] . "'";
	}
	$sql .= " )";

	$stmt = null;

	if (!$dba->sqlExecute($sql, $stmt)) {
		//����Хå�
		$dba->rollbackTransaction();
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	else {
		// ���ߥå�
		$res = $dba->commitTransaction();
		if (!$res) {
			$status = DEF_RETCD_DERR3;
			output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
    	    exit;
		}
	}

	/*==============================================*/
	// ���ｪλ
	/*==============================================*/
	output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
	exit;

	/*==============================================*/
	// ����
	/*==============================================*/
	$dba->close();

?>
