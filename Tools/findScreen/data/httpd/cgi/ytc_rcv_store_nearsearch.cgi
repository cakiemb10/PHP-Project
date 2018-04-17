<?php
/*========================================================*/
// �ե�����̾��ytc_rcv_store_nearsearch.cgi
// ����̾���ڥ�ޥȱ�͢�͸�����ŹƬ����API
//
// ��������
// 2016/10/19 Y.Matsukawa	����������ytc_store_nearsearch.cgi�򥳥ԡ����ƺ�����
/*========================================================*/

	ini_set('display_errors', '0');

	$CGICD = 'y01';
	$NEARSEARCH_CGI = 'store_nearsearch.cgi';
	$CGINM = 'store_nearsearch';

	/*==============================================*/
	// ���������
	/*==============================================*/
	/* ���ϥѥ�᡼��*/
	define( 'DEF_PRM_ENC_UTF8',		'UTF8' );       // ʸ�������ɡ�UTF8��
	define( 'DEF_PRM_ENC_SJIS',		'SJIS' );       // ʸ�������ɡ�SJIS��
	define( 'DEF_PRM_ENC_EUC',		'EUC'  );       // ʸ�������ɡ�EUC��
	define( 'DEF_PRM_PFLG_DNUM',	'1'    );       // �ݥ���ȥե饰�ʽ��ʰ��ٷ���ɽ����
	define( 'DEF_PRM_PFLG_MSEC',	'2'    );       // �ݥ���ȥե饰�ʥߥ��ð��ٷ���ɽ����
	define( 'DEF_PRM_PFLG_DMS',		'3'    );       // �ݥ���ȥե饰����ʬ�ð��ٷ���ɽ����
	define( 'DEF_PRM_DATUM_TOKYO', 	'TOKYO');       // ¬�Ϸϡ�����¬�Ϸϡ�
	define( 'DEF_PRM_DATUM_WGS84', 	'WGS84');       // ¬�Ϸϡ�����¬�Ϸϡ�
	define( 'DEF_PRM_OUTF_JSON', 	'JSON' );       // ���Ϸ�����JSON��
	define( 'DEF_PRM_OUTF_XML', 	'XML'  );       // ���Ϸ�����XML��

	/* �꥿���󥳡��� */
	define( 'ERROR_SYSTEM',				'01003' );	// ����Ū��ͽ�����ʤ�����ˤ���׵�������������Ǥ��ޤ���Ǥ�����
	define( 'ERROR_MAINTENANCE',		'10000' );	// �׵ᤵ�줿API�ϸ��ߡ����ƥʥ���Ǥ���
	define( 'EXPIRY_ACCESS_TOKEN',		'10001' );	// ���������ȡ�����ͭ�������ڤ�Ǥ���
	define( 'INVALID_ACCESS_TOKEN',		'10002' );	// ���������ȡ����󤬶����⤷�����������ͤǤ���
	define( 'URGENT_MAINTENANCE',		'10003' );	// �׵ᤵ�줿API�ϸ��ߡ��۵ޥ��ƥʥ���Ǥ���
	define( 'ERROR_TENPO_DB',			'01000' );	// �ǡ����١��������������顼

	define( 'INVALID_PARAMETER_LAT',	'09002' );	// ���٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_LON',	'09003' );	// ���٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_ZIP',	'09004' );	// ͹���ֹ椬�����⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_NELAT',	'09005' );	// ����ʱ���˰��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_NELON',	'09006' );	// ����ʱ���˷��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SWLAT',	'09007' );	// �����ʺ����˰��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SWLON',	'09008' );	// �����ʺ����˷��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_EWDIST',	'09009' );	// ������Υ�ʷ��١ˤ������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SNDIST',	'09010' );	// ���̵�Υ�ʰ��١ˤ������⤷�����������ͤǤ���

	define( 'YAMATO03_INVALID_PARAMETER_YTC',	'99001' );	// �ڥ�ޥ�ŹƬ�������ѡ���ãô��Ź��Ź�ޥ����ɤ������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_F',		'99002' );	// �ڥ�ޥ�ŹƬ�������ѡ�Ź�޼��̤������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_SKBN',	'99003' );	// �ڥ�ޥ�ŹƬ�������ѡ۾���Ƚ���ʬ�������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_YMD',	'99004' );	// �ڥ�ޥ�ŹƬ�������ѡۼ����ǽ�����ε������������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_DLV',	'99005' );	// �ڥ�ޥ�ŹƬ�������ѡ������ؿ��������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_CNT',	'99006' );	// �ڥ�ޥ�ŹƬ�������ѡۼ�������������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_SORT',	'99007' );	// �ڥ�ޥ�ŹƬ�������ѡۥ����Ƚ礬�����⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_ENC',	'99008' );	// �ڥ�ޥ�ŹƬ�������ѡ�ʸ�������ɤ������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_PFLG',	'99009' );	// �ڥ�ޥ�ŹƬ�������ѡۥݥ���ȥե饰�������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_DATUM',	'99010' );	// �ڥ�ޥ�ŹƬ�������ѡ�¬�ϷϤ������⤷�����������ͤǤ���
	define( 'YAMATO03_INVALID_PARAMETER_OUTF',	'99011' );	// �ڥ�ޥ�ŹƬ�������ѡ۽��Ϸ����������⤷�����������ͤǤ���
	define( 'YAMATO03_EXPIRE_COOL',				'99012' );	// �ڥ�ޥ�ŹƬ�������ѡۥ������ؤ��ݴɴ��¤�᤮�Ƥ��ޤ���

	define( 'YAMATO03_DIST', 30000 );		// ������Υ

	/*==============================================*/
	// ����ե�����
	/*==============================================*/
	include('d_serv_emap.inc');
	include('d_serv_ora.inc');
	include('oraDBAccess.inc');
	include('ZdcCommonFunc.inc');
	include('function.inc');
	include('xml_util.inc');
	include('chk.inc');
	include('jkn.inc');
	include('log.inc');

	require_once('store_def.inc');
	require_once('store_outf.inc');
	require_once('store_kyoten_outf.inc');

	require_once('ytc_def.inc');		// ��ޥȱ�͢�����
	require_once('ytc_cgi_key.inc');	// ��ޥȱ�͢��emapCGI����¾
	require_once('function_ytc.inc');
	require_once('function_YAMATO03.inc');

	/*==============================================*/
	// �����ϳ���
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// �����
	/*==============================================*/
	$status 	= DEF_RETCD_DE;		// ���ѥ��ơ����������ɡ�������
	$rescode	= '-1';				// �쥹�ݥ󥹥����ɽ���͡ʥ��顼��
	$errcode	= '';				// ���顼�����ɽ����
	$outdata	= '';				// ���Ϸ�̽����
	$log_key	= D_LOG_CGIKEY;

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$ATOKEN		= getCgiParameter('ATOKEN','');						/* ���������ȡ����� */
	$ZIP		= getCgiParameter('ZIP','');						/* ͹���ֹ� */
	$LAT		= getCgiParameter('lat','');						/* ���� */
	$LON		= getCgiParameter('lon','');						/* ���� */
	$YTC		= getCgiParameter('YTC','');						/* ��ãô��Ź��Ź�ޥ����� */
	$F			= getCgiParameter('F','');							/* Ź�޼��� */
	$HCD		= getCgiParameter('HCD','');						/* Ź�޻��� */
	$SKBN		= getCgiParameter('SKBN','0');						/* ����Ƚ���ʬ(0���������ذʳ�(��̤����)��1����������) */
	$YMD		= getCgiParameter('YMD','');						/* �����ǽ�����ε����� */
	$DLV		= getCgiParameter('DLV','');						/* �����ؿ� */
	$POS		= getCgiParameter('pos','1');						/* �������� */
	$CNT		= intval(getCgiParameter('cnt','5'));				/* ������� */
	$SORT		= getCgiParameter('sort','');						/* �����Ƚ� */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* ʸ�������� */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* �ݥ���ȥե饰 */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* ¬�Ϸ� */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* ���Ϸ��� */

	$suffix = ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev' ? 'test' : '');		// ����or����
	$CID        = 'yamato01'.$suffix;	// �ǡ�����������ID
	$OPTION_CD  = 'yamato03'.$suffix;	// �ݶ���˽��Ϥ�����ID
	$CUST       = 'YAMATO03';			// store_nearsearch.cgi��cust�ѥ�᡼��

	/*==============================================*/
	// LOG�����Ѥ˥ѥ�᡼���ͤ���
	/*==============================================*/
	$parms = $LAT;
	$parms .= ' '.$LON;

	/*==============================================*/
	// enc��ʸ��������
	/*==============================================*/
	include('store_enc.inc');
	switch ($ENC) {
		case 'SJIS':
			$CHARSET = 'Shift_JIS';
			break;
		case 'EUC':
			$CHARSET = 'EUC-JP';
			break;
		case 'UTF8':
			$CHARSET = 'UTF-8';
			break;
	}

	/*==============================================*/
	// �����ѥ��饹������
	/*==============================================*/
	//$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	$CgiOut = new StoreKyotenCgiOutput('', $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST);

	/*==============================================*/
	// �����ɥᥤ���б�
	/*==============================================*/
	header('Access-Control-Allow-Origin: *');

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	// ATOKEN�����������ȡ�����
	if ($ATOKEN == '') {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else if (strlen($ATOKEN) > 64) {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// YTC����ãô��Ź��Ź�ޥ�����
	if ($YTC == '') {
		// ɬ��
		$status = YAMATO03_INVALID_PARAMETER_YTC;
		$CgiOut->set_debug('ytc', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else if (strlen($YTC) != 6) {
		// 6��
		$status = YAMATO03_INVALID_PARAMETER_YTC;
		$CgiOut->set_debug('ytc', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// F��Ź�޼���
	if ($F == '') {
		$status = YAMATO03_INVALID_PARAMETER_F;
		$CgiOut->set_debug('f', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else if (!in_array($F, array('0', '1', '9'), true)) {
		$status = YAMATO03_INVALID_PARAMETER_F;
		$CgiOut->set_debug('f', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// SKBN������Ƚ���ʬ
	if (!in_array($SKBN, array('0', '1'), true)) {
		$status = YAMATO03_INVALID_PARAMETER_SKBN;
		$CgiOut->set_debug('skbn', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// YMD�������ǽ�����ε�����
	if ($YMD == '') {
		if ($SKBN == '1') {
			// �������ؤξ���YMDɬ��
			$status = YAMATO03_INVALID_PARAMETER_YMD;
			$CgiOut->set_debug('ymd', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	} else if (strlen($YMD) != 12 || !ctype_digit($YMD)) {
		// 12���Ⱦ�ѿ��ͤΤ߲�
		$status = YAMATO03_INVALID_PARAMETER_YMD;
		$CgiOut->set_debug('ymd', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else {
		$ymd_chk = mktime(substr($YMD, 8, 2), substr($YMD, 10, 2), 0, substr($YMD, 4, 2), substr($YMD, 6, 2), substr($YMD, 0, 4));
		$ymd_chk = date('YmdHi', $ymd_chk);
		if ($ymd_chk != $YMD) {
			// ������������NG
			$status = YAMATO03_INVALID_PARAMETER_YMD;
			$CgiOut->set_debug('ymd', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		if ($SKBN == '1') {
			if (YAMATO03::dayPlus($YMD, 2) < date('Ymd')) {
				// �������ؤξ�硢�ݴɴ��¡�YMD+2�ˤ�᤮�Ƥ����饨�顼
				$status = YAMATO03_EXPIRE_COOL;
				$CgiOut->set_debug('ymd', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
	}
	// DLV�������ؿ�
	if ($DLV != '') {
		if (!in_array($DLV, array('1','2','3'), true)) {
			$status = YAMATO03_INVALID_PARAMETER_DLV;
			$CgiOut->set_debug('dlv', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}
	// cnt���������
	if ($CNT < 1 || $CNT > 100) {
		$status = YAMATO03_INVALID_PARAMETER_CNT;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// sort�������Ƚ�
	if ($SORT != '' && $SORT != '1') {
		$status = YAMATO03_INVALID_PARAMETER_SORT;
		$CgiOut->set_debug('sort', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// pflg���ݥ���ȥե饰
	if (!in_array($PFLG, array(DEF_PRM_PFLG_DNUM, DEF_PRM_PFLG_MSEC, DEF_PRM_PFLG_DMS), true)) {
		$status = YAMATO03_INVALID_PARAMETER_PFLG;
		$CgiOut->set_debug('pflg', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// datum���ݥ���ȥե饰
	if (!in_array($DATUM, array(DEF_PRM_DATUM_TOKYO, DEF_PRM_DATUM_WGS84), true)) {
		$status = YAMATO03_INVALID_PARAMETER_DATUM;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// outf���ݥ���ȥե饰
	if (!in_array($OUTF, array(DEF_PRM_OUTF_JSON, DEF_PRM_OUTF_XML), true)) {
		$status = YAMATO03_INVALID_PARAMETER_OUTF;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// ATOKENǧ��
	/*==============================================*/
	$result = YTC::authToken($ATOKEN);
	//$result = 'SUCCESS_AUTH_ALLOW';//����Debug����
	if($result == 'ERROR_MAINTENANCE'){
		// ���顼��API���ƥʥ����
		$status = ERROR_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result == 'URGENT_MAINTENANCE'){
		// ���顼��API�۵ޥ��ƥʥ����
		$status = URGENT_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result == 'EXPIRY_ACCESS_TOKEN'){
		// ���顼�ʥ��������ȡ�����ͭ�������ڤ��
		$status = EXPIRY_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result == 'ERROR_SYSTEM'){
		// ���顼�ʥ����ƥ२�顼��
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result != 'SUCCESS_AUTH_ALLOW'){
		// ���顼�ʥ��������ȡ����󥨥顼��
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('DBopen', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// ��ãô��Ź�ΰ��ٷ��٤����
	/*==============================================*/
	$sql = 'select LAT,LON';
	$sql .= ' from KYOTEN_TBL';
	$sql .= ' where CORP_ID = :CORP_ID';
	$sql .= ' and KYOTEN_ID = :KYOTEN_ID';
	$stmt = oci_parse($dba->conn, $sql);
	if (!$stmt) {
		//$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('��ãô��Ź����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (!oci_bind_by_name($stmt, ':CORP_ID', $CID, 15)) {
		$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('��ãô��Ź����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (!oci_bind_by_name($stmt, ':KYOTEN_ID', $YTC, 15)) {
		$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('��ãô��Ź����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (!oci_execute($stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('��ãô��Ź����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	$result = oci_fetch_assoc($stmt);
	$dba->free($stmt);
	if (!$result) {
		$dba->close();
		$status = YAMATO03_INVALID_PARAMETER_YTC;
		$CgiOut->set_debug('sort', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	$YTC_LAT = $result['LAT'];
	$YTC_LON = $result['LON'];
	$YTC_DIST = 150000;

	/*==============================================*/
	// DB��³������
	/*==============================================*/
	$dba->close();

	/*==============================================*/
	// �ʤ���߾��
	/*==============================================*/
	$FILTER = '';
	$cond_ytc = 'COL_01:1 AND (COL_10:A OR COL_10:B)';
	$cond_shp = 'COL_01:2 AND ((COL_39!:Z96 AND COL_39!:Z97) OR COL_39:@@NULL@@)';
	switch ($F) {
		// ľ��Ź
		case '1':
			$FILTER = $cond_ytc;
			break;
		// �谷Ź
		case '0':
			if ($SKBN == '1') {
				// �谷Ź�ǥ������ؤ�NG
				$FILTER = '('.$cond_ytc.') AND ('.$cond_shp.')';//��0��ˤʤ�
			} else {
				$FILTER = $cond_shp;
			}
			break;
		// ��Ź��
		default:
			if ($SKBN == '1') {
				$FILTER = $cond_ytc;
			} else {
				$FILTER = '('.$cond_ytc.') OR ('.$cond_shp.')';
			}
			break;
	}
	if ($HCD != '') {
		$FILTER = '('.$FILTER.') AND KYOTEN_ID:'.$HCD;
	}

	/*==============================================*/
	// �¹��Ѥ˥ѥ�᡼���ͤ���
	/*==============================================*/
	$parms =  '?cid='.		$CID;
	if ($HCD == '') {
		$parms .= '&lat='.		urlencode($LAT);
		$parms .= '&lon='.		urlencode($LON);
		$parms .= '&zip='.		urlencode($ZIP);
		$parms .= '&ewdist='.	YAMATO03_DIST;
		$parms .= '&sndist='.	YAMATO03_DIST;
		$parms .= '&absdist='.	YAMATO03_DIST;
	} else {
		$LAT = 128441320;
		$LON = 503169540;
		$NELAT = 163998619;
		$NELON = 554348015;
		$SWLAT = 73514227;
		$SWLON = 442566224;
		if ($DATUM == DEF_PRM_DATUM_WGS84) {
			cnv_transDatum($LAT, $LON, TKY_TO_WGS84, $LAT, $LON);
			cnv_transDatum($NELAT, $NELON, TKY_TO_WGS84, $NELAT, $NELON);
			cnv_transDatum($SWLAT, $SWLON, TKY_TO_WGS84, $SWLAT, $SWLON);
		}
		$parms .= '&lat='.$LAT;
		$parms .= '&lon='.$LON;
		$parms .= '&nelat='.$NELAT;
		$parms .= '&nelon='.$NELON;
		$parms .= '&swlat='.$SWLAT;
		$parms .= '&swlon='.$SWLON;
	}
	$parms .= '&filter='.	urlencode($FILTER);
	$parms .= '&pos='.		$POS;
	$parms .= '&cnt='.		$CNT;
	$parms .= '&knsu='.		$CNT;
	$parms .= '&enc='.		urlencode($ENC);
	$parms .= '&pflg='.		urlencode($PFLG);
	$parms .= '&datum='.	urlencode($DATUM);
	$parms .= '&outf='.		urlencode($OUTF);
	$parms .= '&cust='.		'YAMATO03';
	$parms .= '&logcid='.	$OPTION_CD;
	$parms .= '&exarea='.	$YTC_LAT.','.$YTC_LON.','.$YTC_DIST;
	$parms .= '&carg[ytc]='.urlencode($YTC);
	$parms .= '&carg[skbn]='.urlencode($SKBN);
	$parms .= '&carg[ymd]='.urlencode($YMD);
	$parms .= '&carg[dlv]='.urlencode($DLV);
	$parms .= '&carg[sort]='.urlencode($SORT);

	/*==============================================*/
	// store_nearsearch.cgi������
	/*==============================================*/
	unset($result);
	$CGI = 'http://127.0.0.1/cgi/'.$NEARSEARCH_CGI.$parms;
	$result = file_get_contents($CGI);
	if (!$result) {
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('CGI call', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// ��̽���
	if ( $OUTF != 'JSON' ) {
		header( 'Content-type: text/xml; charset='.$CHARSET );
	} else {
		header( 'Content-Type: application/json; charset='.$CHARSET ) ;
	}
	echo $result;

	exit;
?>
