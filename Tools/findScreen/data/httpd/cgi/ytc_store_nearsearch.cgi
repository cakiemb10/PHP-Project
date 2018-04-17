<?php
/*========================================================*/
// �ե�����̾��ytc_store_nearsearch.cgi
// ����̾���ڥ�ޥȱ�͢�͸����������ޥ�����Ź�ް���
//
// ��������
// 2016/04/27 T.Yoshino		��������
// 2016/08/12 Y.Matsukawa	����ӥˡ���å����ɲ�
// 2016/12/12 H.Yasunaga	��ޥȥ�å����б�
//							�ѥ�᡼����SDATE(�в�ͽ����)��HZIP(ȯ��͹���ֹ�)��BSKBN(�ܥå�����������ʬ)���ɲ�
//							K�ѥ�᡼����17�Х����ܤ�"1"�ξ���SDATE��HZIP��BSKBN��ɬ�ܤˤʤ�
// 2017/01/06 H.Yasunaga	/var/tmp/ysn_dbg.log�ؤΥ����Ϥ���
// 2017/01/17 H.Yasunaga	ENC�ѥ�᡼���˰ͤä�ʸ�������ɤǥ쥹�ݥ󥹤���Ϥ���褦�ѹ�
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'y01';

	/*==============================================*/
	// CGI̾
	/*==============================================*/
	$APICGINM = "store_nearsearch.cgi";
	
	$CGINM = "store_nearsearch";


	/*==============================================*/
	// ���������
	/*==============================================*/
	/* ���ϥѥ�᡼��*/
	define( 'DEF_PRM_ENC_UTF8',		'UTF8' );       // ʸ�������ɡ�UTF8��
	define( 'DEF_PRM_ENC_SJIS',		'SJIS' );       // ʸ�������ɡ�SJIS��
	define( 'DEF_PRM_ENC_EUC',		'EUC'  );       // ʸ�������ɡ�EUC��
	define( 'DEF_PRM_PFLG_DNUM',	'1'    );       // �ݥ���ȥե饰�ʽ��ʰ��ٷ���ɽ����
	define( 'DEF_PRM_PFLG_MSEC',	'2'    );       // �ݥ���ȥե饰�ʥߥ��ð��ٷ���ɽ����
	define( 'DEF_PRM_PFLG_DMS',    	'3'    );       // �ݥ���ȥե饰����ʬ�ð��ٷ���ɽ����
	define( 'DEF_PRM_DATUM_TOKYO', 	'TOKYO');       // ¬�Ϸϡ�����¬�Ϸϡ�
	define( 'DEF_PRM_DATUM_WGS84', 	'WGS84');       // ¬�Ϸϡ�����¬�Ϸϡ�
	define( 'DEF_PRM_OUTF_JSON', 	'JSON' );       // ���Ϸ�����JSON��
	define( 'DEF_PRM_OUTF_XML', 	'XML'  );       // ���Ϸ�����XML��
	
	/* �꥿���󥳡��� */
	define( 'SEARCH_RESULT',			'00000' );	// ���˸��礦�ǡ���������ޤ�����
	define( 'NO_SEARCH_RESULT',			'00001' );	// ���˸��礦�ǡ����Ϥ���ޤ���Ǥ�����
	define( 'ERROR_TENPO_DB',			'81000' );	// Ź�ޥǡ����١��������������顼�Ǥ���
	//define( 'ERROR_TENPO_DB',			'01000' );	// Ź�ޥǡ����١��������������顼�Ǥ���
	define( 'ERROR_AUTH',				'01001' );	// ǧ�ڥ��顼�Ǥ���
	define( 'INVALID_SEARCH_KBN',		'01002' );	// �����оݥե饰�������⤷�����������ͤǤ���
	define( 'ERROR_SYSTEM',				'01003' );	// ����Ū��ͽ�����ʤ�����ˤ���׵�������������Ǥ��ޤ���Ǥ�����
	
	define( 'INVALID_PARAMETER_CID',	'09001' );	// ���ID�������⤷�����������ͤǤ���
	
	define( 'ERROR_MAINTENANCE',		'10000' );	// �׵ᤵ�줿API�ϸ��ߡ����ƥʥ���Ǥ���
	define( 'EXPIRY_ACCESS_TOKEN',		'10001' );	// ���������ȡ�����ͭ�������ڤ�Ǥ���
	define( 'INVALID_ACCESS_TOKEN',		'10002' );	// ���������ȡ����󤬶����⤷�����������ͤǤ���
	define( 'URGENT_MAINTENANCE',		'10003' );	// �׵ᤵ�줿API�ϸ��ߡ��۵ޥ��ƥʥ���Ǥ���

	define( 'INVALID_PARAMETER_LAT',	'09002' );	// ���٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_LON',	'09003' );	// ���٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_ZIP',	'09004' );	// ͹���ֹ椬�����⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_NELAT',	'09005' );	// ����ʱ���˰��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_NELON',	'09006' );	// ����ʱ���˷��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SWLAT',	'09007' );	// �����ʺ����˰��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SWLON',	'09008' );	// �����ʺ����˷��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_EWDIST',	'09009' );	// ������Υ�ʷ��١ˤ������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SNDIST',	'09010' );	// ���̵�Υ�ʰ��١ˤ������⤷�����������ͤǤ���
	// add start 2016/12/12 H.Yasunaga ��å����б� [
	// ytc_ret_def.inc�˳ƥ������ͤΥ�å��������ɵ�
	define( 'INVALID_PARAMETER_SDATE',	'09011' );	// �в�ͽ�����������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_HZIP',	'09012' );	// ȯ��͹���ֹ椬�����⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_BSKBN',	'09013' );	// �ܥå�����������ʬ�������⤷�����������ͤǤ���
	// add end ]

	/*==============================================*/
	// ����ե�����
	/*==============================================*/
	include('d_serv_emap.inc');
	include('store_def.inc'); 
	include('store_outf.inc');			// ���ϥ��饹���
	include('ZdcCommonFunc.inc');		// ���̴ؿ�
	include('function.inc');			// ���̴ؿ�
	include('d_serv_ora.inc');
	include('oraDBAccess.inc');
	include('chk.inc');					// �ǡ��������å���Ϣ
	include("jkn.inc");					// �ʤ���߾���Խ�
	include('define.inc');
	include('store_kyoten_outf.inc');
	
	require_once('ytc_def.inc');			// ��ޥȱ�͢�����
	require_once('ytc_cgi_key.inc');		// ��ޥȱ�͢��emapCGI����¾
	require_once('function.inc');			// ���̴ؿ�
	require_once('log.inc');				// ������
	require_once('auth.inc');				// �ʰ�ǧ��
	
	require_once('/home/emap/src/p/inc/xml_util.inc');


	/*==============================================*/
	// �����ϳ���
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// �����
	/*==============================================*/
	$status 	= DEF_RETCD_DE;		// ���ѥ��ơ����������ɡ�������
	$emap_cid	= $D_CID;			// ��ȥ����ɸ��ꡡytc_def.inc�����
	$rescode	= "-1";				// �쥹�ݥ󥹥����ɽ���͡ʥ��顼��
	$errcode	= "";				// ���顼�����ɽ����
	$outdata	= "";				// ���Ϸ�̽����
	$log_parms	= mb_ereg_replace(' ', '_', $dms);
	$log_parms	.= ' ';
	$log_parms	.= mb_ereg_replace(' ', '_', $sid);
	$KEY		= $D_CGI_KEY;		// CGI�ѥ���

	// K�ӥå��ֹ�
	define('K_IDX_YTC', 0);
	define('K_IDX_TRI', 1);
	define('K_IDX_SEJ', 2);
	define('K_IDX_FMT', 3);
	define('K_IDX_COC', 4);
	define('K_IDX_THF', 5);
	define('K_IDX_NWD', 6);
	define('K_IDX_DYM', 7);
	define('K_IDX_PPR', 8);
	define('K_IDX_PP2', 9);
	define('K_IDX_SON', 10);
	define('K_IDX_LST', 11);
	define('K_IDX_CCK', 12);
	define('K_IDX_SKS', 13);
	// 2016/08/12 Y.Matsukawa [
	define('K_IDX_LAW', 14);
	define('K_IDX_NLW', 15);
	define('K_IDX_LOK', 16);
	// 2016/08/12 Y.Matsukawa ]
	
	//�����оݤ����
	$D_YTC_SITE_FILTER_COND[K_IDX_SEJ] = 'COL_39%3A002';
	$D_YTC_SITE_FILTER_COND[K_IDX_FMT] = 'COL_39%3A001';
	$D_YTC_SITE_FILTER_COND[K_IDX_COC] = 'COL_39%3A175';
	$D_YTC_SITE_FILTER_COND[K_IDX_THF] = 'COL_39%3A003';
	$D_YTC_SITE_FILTER_COND[K_IDX_NWD] = 'COL_39%3A418';
	$D_YTC_SITE_FILTER_COND[K_IDX_DYM] = 'COL_39%3A436';
	$D_YTC_SITE_FILTER_COND[K_IDX_PPR] = 'COL_39%3A101';
	$D_YTC_SITE_FILTER_COND[K_IDX_PP2] = 'COL_39%3A171';
	$D_YTC_SITE_FILTER_COND[K_IDX_SON] = 'COL_39%3A207';
	$D_YTC_SITE_FILTER_COND[K_IDX_LST] = 'COL_39%3A189';
	$D_YTC_SITE_FILTER_COND[K_IDX_CCK] = 'COL_39%3AZ98';
	$D_YTC_SITE_FILTER_COND[K_IDX_SKS] = 'COL_39%3AZ99';
	// add 2016/08/12 Y.Matsukawa [
	$D_YTC_SITE_FILTER_COND[K_IDX_LAW] = 'COL_39%3AZ96';
	$D_YTC_SITE_FILTER_COND[K_IDX_NLW] = 'COL_39%3AZ97';
	$D_YTC_SITE_FILTER_COND[K_IDX_LOK] = 'COL_39%3A563';
	// add 2016/08/12 Y.Matsukawa ]
	$tmp = '';
	//for ($i = K_IDX_SEJ; $i <= K_IDX_SKS; $i++) {		mod 2016/08/12 Y.Matsukawa
	for ($i = K_IDX_SEJ; $i <= K_IDX_LOK; $i++) {
		if ($tmp) $tmp .= '%20AND%20';
		$tmp .= str_replace('%3A', '!%3A', $D_YTC_SITE_FILTER_COND[$i]);
	}
	$D_YTC_COND_TRI = '%28%28'.$tmp.'%29%20OR%20COL_39%20is%20null%29';
	

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$CID		= getCgiParameter('cid', '');						/* ���ID */
	$LAT		= getCgiParameter('lat','');						/* ���� ɬ�ܹ���1 */
	$LON		= getCgiParameter('lon','');						/* ���� ɬ�ܹ���1 */
	$NELAT		= getCgiParameter('nelat','');						/* ����ʱ���˰��� */
	$NELON		= getCgiParameter('nelon','')			;			/* ����ʱ���˷��� */
	$SWLAT		= getCgiParameter('swlat','');						/* �����ʺ����˰��� */
	$SWLON		= getCgiParameter('swlon','');						/* �����ʺ����˷��� */
	$EWDIST		= getCgiParameter('ewdist','');						/* ������Υ�ʷ��١� */
	$SNDIST		= getCgiParameter('sndist','');						/* ���̵�Υ�ʰ��١� */
	$FILTER		= getCgiParameter('filter','');						/* �ʤ���߾�� */
	$POS		= getCgiParameter('pos','1');						/* �������� */
	$CNT		= getCgiParameter('cnt','100');						/* ������� */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* ʸ�������� */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* �ݥ���ȥե饰 */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* ¬�Ϸ� */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* ���Ϸ��� */

	$ZIP		= getCgiParameter('zip','');						/* ͹���ֹ� ɬ�ܹ���1 */
	$ATOKEN		= getCgiParameter('ATOKEN','');						/* ���������ȡ����� ɬ�ܹ��� */
	$K			= getCgiParameter('K','');							/* �����оݥե饰 ɬ�ܹ��� */
	
	$SIZE		= getCgiParameter('SIZE','');						/* ��ʪ������(60,80,100,120,140,160) */
	$SKBN		= getCgiParameter('SKBN','0');						/* ����Ƚ���ʬ(0���������ذʳ�(��̤����)��1����������) */

	$PMAPURL	= getCgiParameter('pmapurl', '');					/* pc_map_url��������Ƚ�� */
	$SMAPURL	= getCgiParameter('smapurl', '');					/* smt_map_url��������Ƚ�� */
	$SITE_ID	= getCgiParameter('SITE_ID', '');					/* Ϣ�ȥ�����ID */
	$CUST		= getCgiParameter('cust', 'YAMATO01');				/* �оݴ�Ȏʎߎ׎Ҏ��� */

	// add start 2016/12/12 H.Yasunaga ��å����б� [
	// �в�ͽ������ȯ��͹���ֹ桦�ܥå�����������ʬ��3�ѥ�᡼���ϡ�����API�����Ѥ���ѥ�᡼����Ź�ޥǡ�����select���ˤϱƶ����ʤ�
	$SDATE		= getCgiParameter('SDATE', '');						/* �в�ͽ����*/
	$HZIP		= getCgiParameter('HZIP', '');						/* ȯ��͹���ֹ�*/
	$BSKBN		= getCgiParameter('BSKBN', '');						/* �ܥå�����������ʬ*/
	// add end ]

	// �ݶ���˽��Ϥ�����ID
	$OPTION_CD = $CID;

	// ��ޥ�����˾
	$LAT	 = urlencode($LAT);
	$LON	 = urlencode($LON);
	$NELAT	 = urlencode($NELAT);
	$NELON	 = urlencode($NELON);
	$SWLAT	 = urlencode($SWLAT);
	$EWDIST	 = urlencode($EWDIST);
	$SNDIST	 = urlencode($SNDIST);
	$POS	 = urlencode($POS);
	$CNT	 = urlencode($CNT);
	$ZIP	 = urlencode($ZIP);
	$SIZE	 = urlencode($SIZE);
	$SKBN	 = urlencode($SKBN);
	$PMAPURL = urlencode($PMAPURL);
	$SMAPURL = urlencode($SMAPURL);


	/*==============================================*/
	// �����ѥ��饹������
	/*==============================================*/
	
//	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	$CgiOut = new StoreKyotenCgiOutput("", $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST);

	/*==============================================*/
	// �����ɥᥤ���б�
	/*==============================================*/
	
	header('Access-Control-Allow-Origin: *');

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	// del start 2017/01/07 H.Yasunaga /var/tmp/ysn_dbg.log�ؤΥ����Ϥ��� [
	//error_log($_SERVER['REQUEST_METHOD'] . "\n", 3, "/var/tmp/ysn_dbg.log");
	// del end 2017/01/06 H.Yasunaga ]
	// �ꥯ������
	if ($_SERVER['REQUEST_METHOD'] != "GET") {
		outputErrStatus( $rescode, "ERR0003", "�ꥯ��������ˡ�������Ǥ���" );
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}

	// ���id[CID]
	if ($CID == '') {
		$status = INVALID_PARAMETER_CID;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	
	
	// �����оݥե饰[k]
	if ($K == "") {
		$status = INVALID_SEARCH_KBN;
		$CgiOut->set_debug('k', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	} else if ( is_numeric($K) == FALSE ) {
		$status = INVALID_SEARCH_KBN;
		$CgiOut->set_debug('k', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	} else if ( strlen($K) != 30 ) {
		$status = INVALID_SEARCH_KBN;
		$CgiOut->set_debug('k', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}

	// ���������ȡ�����[atoken]
	if ($ATOKEN == "") {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	} else if ( strlen($ATOKEN) > 64 ) {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}

	// add start 2016/12/12 H.Yasunaga ��å����б� [
	if ($K[K_IDX_LOK] == 1) {
		// K�ѥ�᡼����17�Х����ܤ�1�ξ��ϡ��в�ͽ����(SDATE)��ȯ��͹���ֹ�(HZIP)���ܥå�����������ʬ(BSKBN)�ѥ�᡼����ɬ��
		// �в�ͽ������8�����			�����ǧ ���ͳ�ǧ ���ճ�ǧ
		// ȯ��͹���ֹ��7�����		�����ǧ ���ͳ�ǧ
		// �ܥå�����������ʬ��2����� 	�����ǧ
		if ($SDATE == "") {
			// SDATE(�в�ͽ����)����
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if(strlen($SDATE) != 8) {
			// SDATE(�в�ͽ����)��8��Ǥʤ�
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (preg_match("/^[0-9]{8}+$/", $SDATE) == false) {
			// SDATE(�в�ͽ����)�����ͷ����Ǥʤ�
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (checkdate(substr($SDATE, 4, 2), substr($SDATE, 6, 2), substr($SDATE, 0, 4)) == false) {
			// SDATE(�в�ͽ����)�����դȤ����������ʤ�
			// checkdate�ؿ��ΰ�������������"��",���������"��",�軰������"ǯ"
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		
		if ($HZIP == "") {
			// HZIP(ȯ��͹���ֹ�)��̤����
			$status = INVALID_PARAMETER_HZIP;
			$CgiOut->set_debug('hzip', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (strlen($HZIP) != 7) {
			// HZIP(ȯ��͹���ֹ�)��7��ʳ�
			$status = INVALID_PARAMETER_HZIP;
			$CgiOut->set_debug('hzip', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (preg_match("/^[0-9]{7}+$/", $HZIP)== false) {
			// HZIP(ȯ��͹���ֹ�)�����ͷ����Ǥʤ�
			$status = INVALID_PARAMETER_HZIP;
			$CgiOut->set_debug('hzip', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		
		if ($BSKBN == "") {
			// BSKBN(�ܥå�����������ʬ)��̤����
			$status = INVALID_PARAMETER_BSKBN;
			$CgiOut->set_debug('bskbn', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (strlen($BSKBN) != 2) {
			// BSKBN(�ܥå�����������ʬ)��2��ʳ�
			$status = INVALID_PARAMETER_BSKBN;
			$CgiOut->set_debug('bskbn', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}
	// add end ]

	//�ֵ�URL
	if ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev') {
		//��ư���ǧ��
		$D_YTC_ATOKEN_URL = 'http://103.2.24.43/authapi/authAllow';
//		$D_YTC_ATOKEN_URL = 'http://103.2.24.43/authapi/sample/authAllowSuccess.jsp'; //���ｪλ
//		$D_YTC_ATOKEN_URL = 'http://103.2.24.43/authapi/sample/authAllowError.jsp';   //�۾ｪλ
	} else {
		//������URL�����
		// 28������������URL��
		$D_YTC_ATOKEN_URL = 'https://authapi.kuronekoyamato.co.jp/authapi/authAllow';
	}
	
	
	//ǧ�ڳ�ǧ
	$result = YTCAccessCheckATOKEN($D_YTC_ATOKEN_URL, $ATOKEN);

	if($result == "ERROR_MAINTENANCE"){
		// ���顼��API���ƥʥ����
		$status = ERROR_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result == "URGENT_MAINTENANCE"){
		// ���顼��API�۵ޥ��ƥʥ����
		$status = URGENT_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result == "EXPIRY_ACCESS_TOKEN"){
		// ���顼�ʥ��������ȡ�����ͭ�������ڤ��
		$status = EXPIRY_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result == "ERROR_SYSTEM"){
		// ���顼�ʥ����ƥ२�顼��
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result != "SUCCESS_AUTH_ALLOW"){
		// ���顼�ʥ��������ȡ����󥨥顼��
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}


	// ��ʪ������[SIZE]
//	$arr_size = array( '0', 60, 80, 100, 120, 140, 160, '60', '80', '100', '120', '140', '160' );
//	$chkSIZE = array_search( $SIZE, $arr_size );
//	if ( $chkSIZE == "" && $SIZE != 0 ) {
//		$status = DEF_RETCD_PERR2;
//		$CgiOut->set_debug('SIZE', __LINE__);
//		$CgiOut->set_status($status, 0, 0); 
//		$CgiOut->err_output();
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
//		exit;
//	}
	
	// ����Ƚ���ʬ[SKBN]
//	$SKBN = (isset($SKBN) ? $SKBN : 0);
//	$SKBN = ($SKBN != 1)? 0: 1;


	// pc_map_url��smt_map_url��������Ƚ��
	$arr_opt_flg = array();
	$arr_opt_flg['pc_map']	 = ($PMAPURL != 1)? "": 1;
	$arr_opt_flg['smt_map']	 = ($SMAPURL != 1)? "": 1;
	$arr_opt_flg['site_id']	 = ($SITE_ID != "")? $SITE_ID: "";
	

	/*==============================================*/
	// �ѥ�᡼����ʬ��
	/*==============================================*/

	// �����оݥե饰[k]
	$cvs_cond = array();
	for ($i = 0; $i < strlen($K); $i++) {
		$flg = substr($K, $i, 1);
		if ($flg == '1') {
			if ($i == K_IDX_YTC) {
				$D_YTC_SITE_FILTER_YTC = 1;
			}
			//SIZE��120,140,160��SKBN��1�ξ��ϸ������ʤ�
			if($SIZE != '120' && $SIZE != '140' && $SIZE != '160' && $SKBN != '1'){
				if ($i == K_IDX_TRI) {
					$D_YTC_SITE_FILTER_TRI = 1;
				}
				//if ($i >= K_IDX_SEJ && $i <= K_IDX_SKS) {		mod 2016/08/12 Y.Matsukawa
				if ($i >= K_IDX_SEJ && $i <= K_IDX_LOK) {
					$D_YTC_SITE_FILTER_CVS = 1;
					$cvs_cond[] = $D_YTC_SITE_FILTER_COND[$i];
				}
			}
		} else if ($flg != '0') {
			$status = INVALID_SEARCH_KBN;
			$CgiOut->set_debug('k', __LINE__);
			$CgiOut->set_status($status, 0, 0); 
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}

	}
	if (count($cvs_cond)) {
		$D_YTC_COND_CVS = '%28'.implode('%20OR%20', $cvs_cond).'%29';
	}
	

	// ����0���ä��饨�顼
	if ($D_YTC_SITE_FILTER_YTC != 1 && $D_YTC_SITE_FILTER_TRI != 1 && $D_YTC_SITE_FILTER_CVS != 1 ) {
			$status = INVALID_SEARCH_KBN;
			$CgiOut->set_debug('k', __LINE__);
			$CgiOut->set_status($status, 0, 0); 
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
	}
	

	/*==============================================*/
	// ͹���ֹ椫����ּ���
	/*==============================================*/
	if (($LAT == '' || $LON == '') && $ZIP != '') {
		// ͹���ֹ渡��
		$cgi = $D_SSAPI["searchzip"];
		//	$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s", 1, 1, 'EUC', urlencode($ZIP), $DATUM, 'TSV');
		$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s&sort=%s", 1, 1, 'EUC', urlencode($ZIP), $DATUM, 'TSV', 'adcd');
		$url = sprintf("%s?key=%s&opt=%s&%s", $cgi, $D_SSAPI_KEY, $OPTION_CD, $prm);
		$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
		$status = explode("\t", $dat[0]);
		if(intval($status[2])) {
			$rec = explode("\t", $dat[1]);
			$LAT = $rec[0];
			$LON = $rec[1];
		}
	}

	/*==============================================*/
	// �ʤ���߾��
	/*==============================================*/
	$FILTER_sql = '';
	edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
	$log_jkn = implode(' ', $arr_log_jkn);
	
	
	//--------------------------------------------
	// ʣ���ʤ���߾��ʥ����å��ܥå������ꥹ�ȥܥå�����
	//--------------------------------------------
	$cond = '';

	//��ޥȱ�͢
	if($D_YTC_SITE_FILTER_YTC){
		$cond = '%28COL_01%3A1%20AND%20%28COL_10%3AA%20OR%20COL_10%3AB%29%29';
	}
	//���̼谷Ź
	if($D_YTC_SITE_FILTER_TRI){
		if(isset($cond) && $cond != ''){
			$cond .= '%20OR%20%28COL_01%3A2%20AND%20'.$D_YTC_COND_TRI.'%29';
		}else{
			$cond = '%28COL_01%3A2%20AND%20'.$D_YTC_COND_TRI.'%29';
		}
	}
	//����ӥ�
	if($D_YTC_SITE_FILTER_CVS){
		if(isset($cond) && $cond != ''){
			$cond .= '%20OR%20%28COL_01%3A2%20AND%20'.$D_YTC_COND_CVS.'%29';
		}else{
			$cond = '%28COL_01%3A2%20AND%20'.$D_YTC_COND_CVS.'%29';
		}
	}
	
	// [B2Ϣ�����Բĥե饰(COL_50)]��0�Ǹ���
	$FILTER = 'COL_50%3a0%20AND%20%28'.$cond.'%29';



	/*==============================================*/
	// �¹��Ѥ˥ѥ�᡼���ͤ���
	/*==============================================*/
	$parms =  '?cid='.		$CID;
	$parms .= '&lat='.		$LAT;
	$parms .= '&lon='.		$LON;
	$parms .= '&zip='.		$ZIP;
	$parms .= '&nelat='.	$NELAT;
	$parms .= '&nelon='.	$NELON;
	$parms .= '&swlat='.	$SWLAT;
	$parms .= '&swlon='.	$SWLON;
	$parms .= '&ewdist='.	$EWDIST;
	$parms .= '&sndist='.	$SNDIST;
	$parms .= '&filter='.	$FILTER;
	$parms .= '&pos='.		$POS;
	$parms .= '&cnt='.		$CNT;
	$parms .= '&enc='.		$ENC;
	$parms .= '&pflg='.		$PFLG;
	$parms .= '&datum='.	$DATUM;
	$parms .= '&outf='.		$OUTF;
	$parms .= '&pmapurl='.	$arr_opt_flg['pc_map'];
	$parms .= '&smapurl='.	$arr_opt_flg['smt_map'];
	$parms .= '&SITE_ID='.	$arr_opt_flg['site_id'];
	$parms .= '&cust='.		"YAMATO01";

	// add start 2016/12/12 H.Yasunaga ��å����б� [
	// store_nearsearch.cgi �Υ������ޥ����ѥ�᡼�����������ˤ����Ѥ���
	// ytc_storenearseach.cgi�����å����ѤΥѥ�᡼�����Ϥ�
	$parms .= '&carg[SDATE]='.	$SDATE;		// �в�ͽ����
	$parms .= '&carg[HZIP]='.	$HZIP;		// ȯ��͹���ֹ�
	$parms .= '&carg[BSKBN]='.	$BSKBN;		// �ܥå�����������ʬ
	// add end ]

	/*==============================================*/
	// ����հ�������CGI������
	/*==============================================*/
	unset($result);
//	$CGI = 'http://'.$D_DOMAIN_G.'/cgi/'.$APICGINM.$parms;
	$CGI = 'http://127.0.0.1/cgi/'.$APICGINM.$parms;
//	$CGI = 'http://127.0.0.1/cgi.ysn/'.$APICGINM.$parms;
	$result = file_get_contents($CGI);


	if (!$result) {
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('DBopen', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	// ��̽���
	if ( $OUTF != 'JSON' ) {
		// mod start 2017/01/17 H.Yasunaga ENC�ѥ�᥿���˹�碌��header�ν��Ϥ��ѹ� [
		//header( "Content-type: text/xml; charset=utf-8" );
		switch($ENC) {
			case DEF_PRM_ENC_UTF8:{
				header( "Content-type: text/xml; charset=UTF-8" );
				break;
			}
			case DEF_PRM_ENC_SJIS:{
				header( "Content-type: text/xml; charset=Shift_JIS" );
				break;
			}
			case DEF_PRM_ENC_EUC:{
				header( "Content-type: text/xml; charset=EUC-JP" );
				break;
			}
			default:{
				header( "Content-type: text/xml; charset=UTF-8" );
				break;
			}
		}
		// mod end 2017/01/17 H.Yasunaga ]
	} else {
		// mod start 2017/01/17 H.Yasunaga ENC�ѥ�᥿���˹�碌��header�ν��Ϥ��ѹ� [
		//header( "Content-Type: application/json; charset=utf-8" ) ;
		switch($ENC) {
			case DEF_PRM_ENC_UTF8:{
				header( "Content-Type: application/json; charset=UTF-8" );
				break;
			}
			case DEF_PRM_ENC_SJIS:{
				header( "Content-Type: application/json; charset=Shift_JIS" );
				break;
			}
			case DEF_PRM_ENC_EUC:{
				header( "Content-Type: application/json; charset=EUC-JP" );
				break;
			}
			default:{
				header( "Content-Type: application/json; charset=UTF-8" );
				break;
			}
		}
		// mod end 2017/01/17 H.Yasunaga ]
	}
	echo $result;
	exit;

	/*==============================================*/
	// ���顼���ν���
	/*==============================================*/
	function outputErrStatus( $rescode, $errcode, $outdata ) {
		header( "Content-Type: text/plain; charset=utf-8" );
		print $rescode.",".$errcode.":".$outdata;
		return true;
	}


	// ------------------------------------------------------------
	// ��ޥȱ�͢ ATOKENǧ��
	// ------------------------------------------------------------
	function YTCAccessCheckATOKEN($url, $atoken) {

		global $D_EMAP_ENV;

		// ���ڥ�������
		if ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev') {
			global $D_APIPROXY;
			$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];

			$headers = array(
				'Authorization: Bearer '.$atoken,   //ǧ������
			); 

			$options = array('http' => array(
			    'method' => 'POST',
			    'header' => implode("\r\n", $headers),
				'ignore_errors' => true,
				'proxy' => "tcp://$host",
				'request_fulluri' => true,
			));
			$contents = file_get_contents($url, false, stream_context_create($options));
			$dat = explode("\r\n\r\n",$contents);

		} //���֥�������
		else {
			$cmd = 'wget -O - --post-data="" --header="Authorization: Bearer '.$atoken.'" '.$url;
			exec($cmd, $dat);
		}

		if ($dat && is_array($dat)) {
			$xml_arr = LoadXML(&$dat[0]);
			$MSG_ID = GetXMLVal($xml_arr, "MSG_ID");

			return $MSG_ID;
		}
		return null;
	}


?>
