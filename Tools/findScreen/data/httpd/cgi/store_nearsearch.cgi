<?php
/*========================================================*/
// �ե�����̾��store_nearsearch.cgi
// ����̾��Ź��ID����
//
// ��������
// 2011/12/16 H.Nakamura	��������
// 2013/03/11 Y.Matsukawa	�ꥢ�륿����ǡ���
// 2013/12/20 H.Osamoto		�ǡ�����������ID����
// 2014/01/06 H.Osamoto		���ĥ�ե����null�׵�ǽ�ɲ�
// 2015/02/26 Y.Matsukawa	�ꥯ�����ȥѥ�᡼����zip���ɲ�
// 2015/06/11 H.Osamoto		searchzip.cgi�ƤӽФ����˥����ȥѥ�᡼������
// 2016/01/14 Y.Matsukawa	¿���쥵���Ȥ���θƤӽФ����б���������³��
// 2016/04/25 T.Yoshino		���Ϥ���륿�����ɲäΤ���Υѥ�᡼�����ɲá�yamato01�ѥ������б�
// 2016/10/19 Y.Matsukawa	��ޥȱ�͢����ŹƬ����API��ytc_store_nearsearch.cgi���б�
// 2016/12/12 H.Yasunaga	��ޥȥ�å����б�
//							��å���Ź�ޤ��Ф��ƥ�ޥȥ�å�������API�Υꥯ�����Ȥ�Ԥ�����̤����ꤹ��
// 2017/02/13 Y.Matsukawa	������������
// 2017/03/23 Y.Matsukawa	�Զ�罤����1000��������˥��꡼���顼
// 2017/05/11 H.Yasunaga	��ޥȥ�å����������ƥ��������б�
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'y01';

	/*==============================================*/
	// CGI̾
	/*==============================================*/
	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

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
	// mod 2016/04/25 T.Yoshino [
	//if ( $_GET['cust'] == "YAMATO01" ) {		mod 2016/10/19 Y.Matsukawa
	if ($_GET['cust'] == 'YAMATO01' || $_GET['cust'] == 'YAMATO03') {
		$CGICD = "";
		define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
		define( 'DEF_RETCD_DEND', '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ��������
		define( 'DEF_RETCD_DNE',  '00001' );       // ���˸��礦�ǡ����ʤ�
		define( 'DEF_RETCD_AERR', '01001' );       // ǧ�ڥ��顼
		define( 'DEF_RETCD_DERR1','17900' );       // �ǡ����١��������������顼
		define( 'DEF_RETCD_DERR2','17002' );       // �ǡ����١��������������顼
		define( 'DEF_RETCD_DERR3','17999' );       // �ǡ����١��������������顼
		define( 'DEF_RETCD_PERR1','01002' );       // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
		define( 'DEF_RETCD_PERR2','19200' );       // ���ϥѥ�᡼�����顼(��ʸ���顼)
		define( 'DEF_RETCD_PERR3','19200' );       // ���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)
		define( 'ERROR_SYSTEM',   '01003' );       // ����Ū��ͽ�����ʤ�����ˤ���׵�������������Ǥ��ޤ���Ǥ�����
	} else {
		define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
		define( 'DEF_RETCD_DEND', '00001' );       // ���˸��礦�ǡ�������ʸ�³�ǡ��������
		define( 'DEF_RETCD_DNE',  '11009' );       // ���˸��礦�ǡ����ʤ�
		define( 'DEF_RETCD_AERR', '12009' );       // ǧ�ڥ��顼
		define( 'DEF_RETCD_DERR1','17900' );       // �ǡ����١��������������顼
		define( 'DEF_RETCD_DERR2','17002' );       // �ǡ����١��������������顼
		define( 'DEF_RETCD_DERR3','17999' );       // �ǡ����١��������������顼
		define( 'DEF_RETCD_PERR1','19100' );       // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
		define( 'DEF_RETCD_PERR2','19200' );       // ���ϥѥ�᡼�����顼(��ʸ���顼)
		define( 'DEF_RETCD_PERR3','19200' );       // ���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)
	}
	define( 'INVALID_PARAMETER',		'09000' );	// �������������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_CID',	'09001' );	// ���ID�������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_LAT',	'09002' );	// ���٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_LON',	'09003' );	// ���٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_ZIP',	'09004' );	// ͹���ֹ椬�����⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_NELAT',	'09005' );	// ����ʱ���˰��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_NELON',	'09006' );	// ����ʱ���˷��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SWLAT',	'09007' );	// �����ʺ����˰��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SWLON',	'09008' );	// �����ʺ����˷��٤������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_EWDIST',	'09009' );	// ������Υ�ʷ��١ˤ������⤷�����������ͤǤ���
	define( 'INVALID_PARAMETER_SNDIST',	'09010' );	// ���̵�Υ�ʰ��١ˤ������⤷�����������ͤǤ���
	// mod 2016/04/25 T.Yoshino ]

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
	include('auth.inc');				// �ʰ�ǧ��
	include("jkn.inc");				// �ʤ���߾���Խ�
	include('store_kyoten_outf.inc');
	include('rd_sql.inc');		// add 2013/03/11 Y.Matsukawa
	@include('function_'.$_GET['cust'].'.inc');			// �������ޥ����ؿ�		add 2016/10/19 Y.Matsukawa

	/*==============================================*/
	// ���顼���Ϥ�����Ū��OFF
	/*==============================================*/
	//	error_reporting(E_ALL^E_NOTICE);
	//	error_reporting(0);
	if ($D_DEBUG) ini_set('display_errors', '1');		// add 2013/03/11 Y.Matsukawa

	/*==============================================*/
	// �����
	/*==============================================*/
	// ���ơ�����(�꥿���󥳡���)
	if (!isset($status)){
		 $status = '00000';
	}

	/*==============================================*/
	// �����ϳ���
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$CID		= getCgiParameter('cid','');						/* ���ID */
	$LAT		= getCgiParameter('lat','');						/* ���� */
	$LON		= getCgiParameter('lon','');						/* ���� */
	$ZIP		= getCgiParameter('zip','');						/* ͹���ֹ� */		// add 2015/02/26 Y.Matsukawa
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
	// add 2016/01/14 Y.Matsukawa [
	$INTID		= getCgiParameter('intid', '');						/* �������ѻ���ID */
	$OPT		= getCgiParameter('opt', '');						/* �������ѻ��δ��ID */
	$KNSU		= getCgiParameter('knsu', '');						/* ������ */
	$ABSDIST	= getCgiParameter('absdist', '');					/* ���ϰϸ��� */
	$EXKID		= getCgiParameter('exkid', '');						/* ����Ź�޻��� */
	// add 2016/01/14 Y.Matsukawa ]
	// add 2016/10/19 Y.Matsukawa [
	$EXAREA		= getCgiParameter('exarea', '');					/* �������ꥢ����(����,����,��Υ) */
	if ($EXAREA != '') {
		$EXAREA = explode(',', $EXAREA);
	}
	// add 2016/10/19 Y.Matsukawa ]
	// add 2016/04/25 T.Yoshino [
	$PMAPURL	= getCgiParameter('pmapurl', '');					/* pc_map_url��������Ƚ�� */
	$SMAPURL	= getCgiParameter('smapurl', '');					/* smt_map_url��������Ƚ�� */
	$SITE_ID	= getCgiParameter('SITE_ID', '');					/* Ϣ�ȥ�����ID */
	$CUST		= getCgiParameter('cust', '');						/* �оݴ�Ȏʎߎ׎Ҏ��� */
	// add 2016/04/25 T.Yoshino ]
	// add 2016/10/19 Y.Matsukawa [
	// �������ޥ����ѥ�᡼������������
	// �����&carg[id]=123&carg[name]=ABC �� $c_id, $c_name
	if (isset($_GET['carg'])) {
		$arr = $_GET['carg'];
		foreach ($arr as $an => $av) {
			${'c_'.$an} = $av;
		}
	}
	// �����ϴ��ID
	$LOGCID		= getCgiParameter('logcid', '');
	// add 2016/10/19 Y.Matsukawa ]
	$COLS		= getCgiParameter('cols', '');						/* ������������ */		// add 2017/02/13 Y.Matsukawa

	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	// �ݶ���˽��Ϥ�����ID
	//$OPTION_CD = $CID;		mod 2016/01/14 Y.Matsukawa
	$OPTION_CD = ($INTID != '')?$OPT:$CID;
	if ($LOGCID != '') $OPTION_CD = $LOGCID;		// add 2016/10/19 Y.Matsukawa
	
	// add 2016/04/25 T.Yoshino [
	// pc_map_url��smt_map_url��������Ƚ��
	$arr_opt_flg = array();
	$arr_opt_flg['pc_map']	 = ($PMAPURL != '')? 1: "";
	$arr_opt_flg['smt_map']	 = ($SMAPURL != '')? 1: "";
	$arr_opt_flg['site_id']	 = $SITE_ID;
	$arr_opt_flg['cust']	 = $CUST;
	// add 2016/04/25 T.Yoshino ]

	include('store_enc.inc');			// ʸ���������Ѵ�

	// add 2016/10/19 Y.Matsukawa
	/*==============================================*/
	// ��ޥȱ�͢ŹƬ����API�����ޥ���
	/*==============================================*/
	if ($CUST == 'YAMATO03') {
		$yamato03 = new YAMATO03($c_ytc, $c_skbn, $c_ymd, $c_dlv);
	}

	// add start 2016/12/12 H.Yasunaga ��å����б� [
	/*==============================================*/
	// ��ޥȱ�͢����API�������ޥ���
	/*==============================================*/
	if ($CUST == 'YAMATO01') {
		// carg�ѥ�᡼��������Ǽ������ѿ�Ÿ�������ͤ�Ȥ�
		// ytc_store_nearsearch�� &carg[SDATA]=xxx&carg[HZIP]=yyy&carg[BSKBN]=zzz �η��ǥꥯ�����Ȥ��äƤ���
		// $c_SDATA	:�в�ͽ����
		// $c_HZIP	:ȯ��͹���ֹ�
		// $c_BSKBN	:�ܥå�����������ʬ
		// $PFLG	:�ݥ���ȥե饰(͹���ֹ�հ����ǻ��Ѥ��뤿��)
		// $DATUM	:¬�Ϸ�(͹���ֹ�հ����ǻ��Ѥ��뤿��)
		// �����Ǥϥ��󥹥��󥹤������Τ� �����θ���������ä���ǥ�å�������API�����Ѥ���
		if (empty($c_SDATE) != ture && empty($c_HZIP) != true && empty($c_BSKBN) != true) {
			// �в�ͽ������ȯ��͹���ֹ桦�ܥå�����������ʬ�������������
			$yamato01 = new YAMATO01($c_SDATE, $c_HZIP, $c_BSKBN, $PFLG, $DATUM);
		}
	}
	
	// add 2015/02/26 Y.Matsukawa
	/*==============================================*/
	// ͹���ֹ椫����ּ���
	/*==============================================*/
	if (($LAT == '' || $LON == '') && $ZIP != '') {
		// ͹���ֹ渡��
		$cgi = $D_SSAPI["searchzip"];
		//	$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s", 1, 1, 'EUC', urlencode($ZIP), $DATUM, 'TSV');	mod 2015/06/11 H.Osamoto
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

	/*==============================================*/
	// LOG�����Ѥ˥ѥ�᡼���ͤ���
	/*==============================================*/
	$parms = $LAT;
	$parms .= ' '.$LON;
	$parms .= ' '.$SWLAT;
	$parms .= ' '.$SWLON;
	$parms .= ' '.$NELAT;
	$parms .= ' '.$NELON;
	$parms .= ' '.$log_jkn;

	/*==============================================*/
	// �����ѥ��饹������
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST );
	
	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* ������³�ե饰 */		// add 2016/01/14 Y.Matsukawa
	if ($INTID != '') {
		if(!in_array($INTID, $D_STORE_INTID)) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('intid', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
	}
	/* �������ѥ��� */		// add 2016/01/14 Y.Matsukawa
	if ($INTID != '') {
		$log_key = '299912312359592'.$INTID;
	} else {
		$log_key = D_LOG_CGIKEY;
	}
	/* ���ID */
	if ($CID == '') {
//		$status = DEF_RETCD_PERR1;
		$status = INVALID_PARAMETER_CID;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ���� */
	if ($LAT == '') {
//		$status = DEF_RETCD_PERR1;
		$status = INVALID_PARAMETER_LAT;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_debug('lat', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ���� */
	if ($LON == '') {
//		$status = DEF_RETCD_PERR1;
		$status = INVALID_PARAMETER_LON;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_debug('lon', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* �ϰ� or ��Υ */
	if ($NELAT != '' || $NELON != '' || $SWLAT != '' || $SWLON != '') {
		/* ����(����)���� */
		if ($NELAT == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_NELAT;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('nelat', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* ����(����)���� */
		if ($NELON == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_NELON;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('nelon', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* ����(����)����*/
		if ($SWLAT == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_SWLAT;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('swlat', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* ����(����)����*/
		if ($SWLON == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_SWLON;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('swlon', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$EWDIST = '';
		$SNDIST = '';
	} else {
		/* ������Υ */
		if ($EWDIST == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_EWDIST;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('ewdist', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* ������Υ 1�� 50000 */
		if ($INTID == '') {		// add 2016/01/14 Y.Matsukawa
			if(!($EWDIST > 0 && $EWDIST <= 50000)) {
//				$status = DEF_RETCD_PERR2;
				$status = INVALID_PARAMETER_EWDIST;	// mod 2016/04/25 T.Yoshino 
				$CgiOut->set_debug('ewdest', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
		/* ���̵�Υ */
		if ($SNDIST == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_SNDIST;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('sndist', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* ���̵�Υ 1�� 50000 */
		if ($INTID == '') {		// add 2016/01/14 Y.Matsukawa
			if(!($SNDIST > 0 && $SNDIST <= 50000)) {
//				$status = DEF_RETCD_PERR2;
				$status = INVALID_PARAMETER_SNDIST;	// mod 2016/04/25 T.Yoshino 
				$CgiOut->set_debug('sndist', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
	}
	/* �������ϰ���*/
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ������� */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT > 1000) {
		$CNT = 1000;
	}
	/* ������ */		// add 2016/01/14 Y.Matsukawa
	if ($KNSU != '') {
		$KNSU = intval($KNSU);
		if (!chk_knsu_max($KNSU)) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('knsu', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}	
	}
	/* ʸ�������� */
	if ($INPUT_ENC  != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC  != DEF_PRM_ENC_EUC &&
		$INPUT_ENC  != DEF_PRM_ENC_UTF8) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('enc', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* �ݥ���ȥե饰 */
	if ($PFLG != DEF_PRM_PFLG_DNUM && 
		$PFLG != DEF_PRM_PFLG_MSEC &&
		$PFLG != DEF_PRM_PFLG_DMS) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pflg', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ¬�Ϸ� */
	if ($DATUM != DEF_PRM_DATUM_TOKYO && 
		$DATUM != DEF_PRM_DATUM_WGS84) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ���Ϸ��� */
	if ($OUTF != DEF_PRM_OUTF_JSON && $OUTF != DEF_PRM_OUTF_XML) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		$CgiOut->set_debug('DBopen', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// �����ӥ�����
	/*==============================================*/
	if ($INTID == '') {		// ������³�ξ��ϥ����å����ʤ�	add 2016/01/14 Y.Matsukawa
		$url = sprintf("%s?cid=%s&opt=%s",$D_SSAPI["getsdate"], $D_CID, $CID);
		$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
		$service = explode("\t",$dat[0]);
		if($service[0] == "89000000") {
			$rec = explode("\t",$dat[1]);
			$flg = intval($rec[0]);
		}
		if(!isset($flg) || (isset($flg) && $flg == 0)) {	
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('�����ӥ�����', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}

	/*==============================================*/
	// CGI���ѵ���
	/*==============================================*/
	if ($INTID == '') {		// ������³�ξ��ϥ����å����ʤ�	add 2016/01/14 Y.Matsukawa
		$sql  = " SELECT"; 
		$sql .= "    VALUE";
		$sql .= " FROM";
		$sql .= "    EMAP_PARM_TBL";
		$sql .= " WHERE";
		$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
		$sql .= " AND KBN  = 'C_EMAP_KBN'";
		$sql .= " AND VALUE  = 'S'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('CGI���ѵ���', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if($data['VALUE'] == '0') {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('CGI���ѵ���', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		} else {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('CGI���ѵ���', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$dba->free($stmt);
	}

	/*==============================================*/
	// SSLǧ�ڡ�IP�����å�����ե�������å�
	/*==============================================*/
	if ($INTID == '') {		// ������³�ξ��ϥ����å����ʤ�	add 2016/01/14 Y.Matsukawa
		$sql  = " SELECT"; 
		//	$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER";	mod 2014/01/06 H.Osamoto
		$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER, REFERER_NULL";
		$sql .= " FROM";
		$sql .= "    EMAP_CGI_CONF_TBL";
		$sql .= " WHERE";
		$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('SSLǧ�ڵ���', __LINE__);
			$CgiOut->set_status($status, 0, 0); 
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			/* SSL��³���� */
			if (isset($data['SSL_ACCESS'])) {
				switch($data['SSL_ACCESS']) {
					// SSL��³�Ե���
					case '0' :
						if($_SERVER['HTTPS'] == 'on') {
							$dba->free($stmt);
							$dba->close();
							$status = DEF_RETCD_AERR;
							$CgiOut->set_debug('SSLǧ�ڵ���', __LINE__);
							$CgiOut->set_status($status, 0, 0);
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						}
						break;
					// SSL��³����
					case '1' :
						break;
					// SSL��³ɬ��
					case '2' :
						if($_SERVER['HTTPS'] != 'on') {
							$dba->free($stmt);
							$dba->close();
							$status = DEF_RETCD_AERR;
							$CgiOut->set_debug('SSLǧ�ڵ���', __LINE__);
							$CgiOut->set_status($status, 0, 0); 
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						}
						break;
					defailt:
						brak;
				}
			} else {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_AERR;
				$CgiOut->set_debug('SSLǧ�ڵ���', __LINE__);
				$CgiOut->set_status($status, 0, 0); 
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}

			$referer_list = explode(";",  $data['ALLOW_REFERER']);

			/* IP�����å� */
			if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
				if (!ip_check2($data['ALLOW_IP'], $_SERVER['REMOTE_ADDR'], ';')) {
					/* ��ե�������å� */
					if (!referer_check(&$referer_list, $_SERVER['HTTP_REFERER'])) {
						// add 2014/01/06 H.Osamoto [
						/* ��ե���null���ĥ����å� */
						if (!referer_null_check($data['REFERER_NULL'], $_SERVER['HTTP_REFERER'])) {
						// add 2014/01/06 H.Osamoto ]
							$dba->free($stmt);
							$dba->close();
							$status = DEF_RETCD_AERR;
							$CgiOut->set_debug('IP�����å�', __LINE__);
							$CgiOut->set_status($status, 0, 0);
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						// add 2014/01/06 H.Osamoto [
						}
						// add 2014/01/06 H.Osamoto ]
					}
				}
			}
		} else {
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('ǧ�ڥ��顼', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$dba->free($stmt);
	}

	// add 2013/12/20 H.Osamoto
	/*==============================================*/
	// �ǡ�����������ID����
	/*==============================================*/
	$CID = getDataCid($dba, $CID);

	// add 2013/03/11 Y.Matsukawa
	/*==============================================*/
	// RD��������
	/*==============================================*/
	$use_rd = isRDAvailable($dba, $CID);

	/*==============================================*/
	// ��ɸɽ�������ڤ�¬�ϷϤ��Ѵ�
	/*==============================================*/
	$LAT_DEC = $LAT;
	$LON_DEC = $LON;
	$LAT_MS;
	$LON_MS;
	$res = cnv_ll2lldms($LAT, $LON, $DATUM, &$LAT_MS, &$LON_MS);
	if (!$res) {
		// ���ٷ�������
//		$status = DEF_RETCD_PERR2;
		$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->set_debug('���ٷ���', __LINE__);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($NELAT != '' && $NELON != '') {
		$res = cnv_ll2lldms($NELAT, $NELON, $DATUM, &$NELAT, &$NELON);
		if (!$res) {
			// ���ٷ�������
//			$status = DEF_RETCD_PERR2;
			$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('���ٷ���', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}
	if ($SWLAT != '' && $SWLON != '') {
		$res = cnv_ll2lldms($SWLAT, $SWLON, $DATUM, &$SWLAT, &$SWLON);
		if (!$res) {
			// ���ٷ�������
//			$status = DEF_RETCD_PERR2;
			$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('���ٷ���', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}

	// add 2016/10/19 Y.Matsukawa
	/*==============================================*/
	// �濴���ٷ��٤����
	/*==============================================*/
	if ($CUST == 'YAMATO03') {
		$CgiOut->set_centerlatlon($LAT_MS, $LON_MS, $DATUM);
	}

	/*==============================================*/
	// �����̾�ꥹ�ȼ��� 
	/*==============================================*/
	/* ���������� */
	$sql  = " SELECT"; 
	$sql .= "    COL_NAME, VAL_KBN, ITEM_NAME";
	$sql .= " FROM";
	$sql .= "    KYOTEN_ITEM_TBL";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
	// add 2017/02/13 Y.Matsukawa [
	if ($COLS != '') {
		$COLS = explode(',', $COLS);
		for ($i = 0; $i < count($COLS); $i++) {
			$COLS[$i] = "'".str_replace("'", "", $COLS[$i])."'";
		}
		$sql .= " AND COL_NAME in (".implode(',', $COLS).")";
	} else {
	// add 2017/02/13 Y.Matsukawa ]
		$sql .= " AND LIST_KBN = 1";
	}
	$sql .= " ORDER BY DISP_NUM";
	/* ������ȯ�� */
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ��̥��å��ݻ� */
	$arr_item = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$arr_item[] = $data;
	}
	$dba->free($stmt);

	/*==============================================*/
	// ��ʬ���ܤ�̾�μ���
	/*==============================================*/
	$arr_kbn = array();
	$arr_item_val[$item['COL_NAME']] = array();
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			/* ���������� */
			$sql_kbn  = " SELECT";
			$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
			$sql_kbn .= " FROM";
			$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
			$sql_kbn .= " WHERE";
			$sql_kbn .= " CORP_ID = '".escapeOra($CID)."'";
			$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
			$sql_kbn .= " ORDER BY ITEM_VAL";
			/* ������ȯ�� */
			if (!$dba->sqlExecute($sql_kbn, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('DB����', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
			/* ��̥��åȳ�Ǽ */
			$arr_kbn[$item['COL_NAME']] = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
				$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
			}
			$dba->free($stmt);
		}
	}

	$arr_kid = array();		// add 2013/03/11 Y.Matsukawa

	/*==============================================*/
	// �Ǵ��������
	/*==============================================*/
	/* ���֥��������� */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
	$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $LAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
	$sql_sub_near .= " + POWER( ABS( LON - $LON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
	/*  new ɽ���ե饰ʬ */
	$sql_sub_near .= " CASE";
	$sql_sub_near .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
	$sql_sub_near .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql_sub_near .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
	$sql_sub_near .= "         THEN '1'";
	$sql_sub_near .= "         ELSE '0'";
	$sql_sub_near .= " END AS BFLG";
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			$sql_sub_near .= ", ".$item['COL_NAME'];
		}
	}
	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    KYOTEN_TBL K";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
	// add 2016/01/14 Y.Matsukawa [
	if ($EXKID != '') {
		$sql_sub_near .= " AND KYOTEN_ID != '$EXKID' ";
	}
	// add 2016/01/14 Y.Matsukawa ]
	
	// add 2017/05/11 H.Yasunaga ��ޥȥ�å����������ƥ��������б� [
	if ($CUST == 'YAMATO01' && $yamato01) {
		$securityCodeGroupNO = "1";	// RD�ǡ����Υ������ƥ������ɤΥ��롼���ֹ�
		$securityCodeItemNo = "1";	// RD�ǡ����Υ������ƥ������ɤι����ֹ�
		$sql_sub_near .= " AND KYOTEN_ID NOT IN (";
		$sql_sub_near .= " SELECT G.KYOTEN_ID ";
		$sql_sub_near .= " FROM RD_ITEM_DEF_TBL I, RD_GROUP_DEF_TBL F, RD_DATA_TBL D, RD_GROUP_TBL G ";
		$sql_sub_near .= " WHERE G.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND F.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND D.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND I.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND G.GROUP_NO = F.GROUP_NO ";
		$sql_sub_near .= " AND G.GROUP_NO = D.GROUP_NO ";
		$sql_sub_near .= " AND G.GROUP_NO = I.GROUP_NO ";
		$sql_sub_near .= " AND D.KYOTEN_ID = G.KYOTEN_ID ";
		$sql_sub_near .= " AND I.ITEM_NO = D.ITEM_NO ";
		$sql_sub_near .= " AND I.DEL_FLG = '0' ";
		$sql_sub_near .= " AND ( ";
		$sql_sub_near .= 		" F.USE_KIKAN = '0' ";
		$sql_sub_near .= 		" or ( ";
		$sql_sub_near .= 				" nvl(to_char(G.ST_DT,'yyyymmddhh24'),'0') <= to_char(sysdate,'yyyymmddhh24') ";
		$sql_sub_near .= 				" and nvl(to_char(G.ED_DT,'yyyymmddhh24'),'9999999999') > to_char(sysdate,'yyyymmddhh24') ";
		$sql_sub_near .= 			" ) ";
		$sql_sub_near .= 	" ) ";
		$sql_sub_near .= " AND G.GROUP_NO = '" . escapeOra($securityCodeGroupNO) . "'";
		$sql_sub_near .= " AND I.ITEM_NO = '" . escapeOra($securityCodeItemNo) . "'";
		$sql_sub_near .= " AND D.TXT_DATA IS NOT NULL ";
		$sql_sub_near .= ") ";
	}
	// add 2017/05/11 H.Yasunaga ]
	
	if ($SWLAT) {
		$sql_sub_near .= " AND LAT >= ".$SWLAT;
		$sql_sub_near .= " AND LAT <= ".$NELAT;
		$sql_sub_near .= " AND LON >= ".$SWLON;
		$sql_sub_near .= " AND LON <= ".$NELON;
	} else {
		$sql_sub_near .= " AND LAT >= (".$LAT_MS." - ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
		$sql_sub_near .= " AND LAT <= (".$LAT_MS." + ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
		$sql_sub_near .= " AND LON >= (".$LON_MS." - ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
		$sql_sub_near .= " AND LON <= (".$LON_MS." + ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
	}
	// add 2016/10/19 Y.Matsukawa [
	// �������ꥢ
	if (is_array($EXAREA)) {
		$sql_sub_near .= " AND LAT >= (".$EXAREA[0]." - ((300000 / (9 * 1000)) * ".$EXAREA[2].")) ";
		$sql_sub_near .= " AND LAT <= (".$EXAREA[0]." + ((300000 / (9 * 1000)) * ".$EXAREA[2].")) ";
		$sql_sub_near .= " AND LON >= (".$EXAREA[1]." - ((450000 / (11 * 1000)) * ".$EXAREA[2].")) ";
		$sql_sub_near .= " AND LON <= (".$EXAREA[1]." + ((450000 / (11 * 1000)) * ".$EXAREA[2].")) ";
	}
	// add 2016/10/19 Y.Matsukawa ]
	$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	if ($FILTER_sql != '') {
		$sql_sub_near .= " AND ".$FILTER_sql;
	}
	$FILTER_sql = f_dec_convert($FILTER_sql);
	$sql_sub_near .= " order by KYORI, KYOTEN_ID, CORP_ID";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
	// add 2016/01/14 Y.Matsukawa [
	$sql_near_whr = '';
	if ($KNSU != '') {
		$sql_near_whr .= " WHERE ROWNUM <= $KNSU";
	}
	if ($ABSDIST != '') {
		$sql_near_whr .= ($sql_near_whr == '' ? " WHERE " : " AND ");
		//$sql_near_whr .= "SQRT(KYORI) <= $ABSDIST";		mod 2016/10/19 Y.Matsukawa
		$sql_near_whr .= "KYORI <= $ABSDIST";
	}
	$sql_near .= $sql_near_whr;
	// add 2016/01/14 Y.Matsukawa ]
	// �ҥåȷ������
	$hit_num = 0;
	$stmt = null;
	$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql_near.")";
	if (!$dba->sqlExecute($sql_count, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['HITCNT'];
	}
	$dba->free($stmt);
	// �ǡ�������
	$rec_num = 0;
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data = "SELECT * FROM (".$sql_near.")";
		$sql_data .= " where rn >= ".$POS;
		$to = $POS+$CNT-1;
		$sql_data .= " and rn <= ".$to;
		$stmt = null;
		if (!$dba->sqlExecute($sql_data, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('DB����', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		// add 2017/03/23 Y.Matsukawa [
		// ���̥ǡ����ֵѻ��Υ��꡼��­����
		if ($CNT > 500 && $hit_num > 500) ini_set('memory_limit', '16M');
		dbl("memory_limit=".ini_get('memory_limit'));
		// add 2017/03/23 Y.Matsukawa ]
		while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if ($DATUM == DEF_PRM_DATUM_WGS84) {
				// ¬�ϷϤ��Ѵ���TOKYO=>WGS84��
				$res = cnv_transDatum($data['LAT'], $data['LON'], TKY_TO_WGS84, $w_lat, $w_lon);
				if ($res) {
					$data['LAT'] = $w_lat;
					$data['LON'] = $w_lon;
				}
			}
			// ��ʬ���ܤ�̾�Τ򥻥å�
			if (count($arr_item) > 0) {
				foreach ($arr_item as $item) {
					$colnm = $item['COL_NAME'];
					if (isset($data[$colnm])) {
						$val = $data[$colnm];
						if ($val != '') {
							if ($arr_kbn[$colnm][$val] != '') {
								$data[$colnm.'_name'] = $arr_kbn[$colnm][$val];
							}
						}
					}
				}
			}
			// add 2016/04/25 T.Yoshino [
			// yamatoECϢ��
			if ( $CUST == "YAMATO01" ) {
				if( $data['COL_01'] == '1' ){										//ľ��Ź�������
					$data['COL_11'] = $data['KYOTEN_ID'];
					$strB2Name = mb_convert_kana($data['NAME'], "rns", "EUC-JP");	// ���ѱѿ���Ⱦ�Ѥ�
					$data['COL_47'] = str_replace( " ", "", $strB2Name );
					$strB2Addr = mb_convert_kana($data['ADDR'], "rns", "EUC-JP");	// ���ѱѿ���Ⱦ�Ѥ�
					$data['COL_48'] = str_replace( " ", "", $strB2Addr );
					$data['COL_49'] = $data['KYOTEN_ID'];
					if ( ( strlen( $data['NAME'] ) + strlen( $data['ADDR'] ) ) >= 77 ) {
						$data['COL_50'] = "1";
					} else {
						$data['COL_50'] = "0";
					}
				}
			}
			// add 2016/04/25 T.Yoshino ]
			// add 2016/10/19 Y.Matsukawa [
			// �ڥ�ޥȱ�͢��ŹƬ����API
			if ($CUST == 'YAMATO03' && $yamato03) {
				$data['YAMATO03_DYMD'] = $yamato03->getRcvDate($data);	// �����ǽ����
				$data['YAMATO03_KYMD'] = $yamato03->getKeepDate($data);	// �ݴɴ���
			}
			// add 2016/10/19 Y.Matsukawa ]
			$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		$rec_num = count($arr_kyoten);
		// 2016/10/19 Y.Matsukawa [
		// �ڥ�ޥȱ�͢��ŹƬ����API
		if ($CUST == 'YAMATO03' && $yamato03 && $c_sort == '1') {
			// �����ǽ�����ʾ���ˤ��¤��ؤ�
			usort($arr_kyoten, function ($a, $b) {
				if ($a['YAMATO03_DYMD'] == $b['YAMATO03_DYMD']) {
					if (intval($a['KYORI']) == intval($b['KYORI'])) return 0;
					return (intval($a['KYORI']) < intval($b['KYORI'])) ? -1 : 1;
				}
				return ($a['YAMATO03_DYMD'] < $b['YAMATO03_DYMD']) ? -1 : 1;
			});
		}
		// 2016/10/19 Y.Matsukawa ]

		// add start 2016/12/12 H.Yasunaga ��å����б� [
		if ($CUST == 'YAMATO01' && $yamato01) {
			// ����API��Ȥäƥ�å����ξ���(�����ǽ�����в������ݴɴ��¡ˤ���������ꤹ��
			// �����ǡ����˰ʲ���ź�������ͤ����ꤹ��
			// �����ǽ��	: YAMATO01_UKETORIKANODATE
			// �в���		: YAMATO01_SHUKKADATA
			// �ݴɴ���		: YAMATO01_HOKANKIGEN
			// ����API�ǻ��Ѥ���в�ͽ������ȯ��͹���ֹ桦�ܥå�����������ʬ�ϥ��󥹥ȥ饯��������Ѥ�
			// CGI���᤹�ͤ�����ϡ�inc/store_kyoten_outf.inc
			$arr_kyoten = $yamato01->getApiData($arr_kyoten);
			if (is_null($arr_kyoten) == true) {
				$status = ERROR_SYSTEM;
				$CgiOut->set_debug('����API', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
		// add end ]
	}

	// add 2013/03/11 Y.Matsukawa
	/*==============================================*/
	// RD�ǡ�������
	/*==============================================*/
	$arr_rd_kyoten = array();
	if ($use_rd && $rec_num) {
		// �������롼�׼���
		$arr_grp = selectRDGroupByView($dba, $CID, 6);
		if (count($arr_grp)) {
			// RD�ǡ�������
			$arr_rd_kyoten = selectRDData($dba, $CID, $arr_kid, $arr_grp);
			if ($arr_rd_kyoten === false) {
				$arr_rd_kyoten = array();
			}
			// �����ǡ����˥ޡ���
			if (count($arr_rd_kyoten)) {
				foreach ($arr_kyoten as $k=>$kyoten) {
					$kyoid = $kyoten['KYOTEN_ID'];
					if ($arr_rd_kyoten[$kyoid]) {
						$arr_kyoten[$k]['RD'] = $arr_rd_kyoten[$kyoid];
					}
				}
			}
		}
	}

	if (!$rec_num) {
		// �����ǡ���̵��
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, $hit_num);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (($POS+$rec_num-1) < $hit_num) {
		// ��³�ǡ���ͭ��
		$status = DEF_RETCD_DEND;
	} else {
		// ��³�ǡ���̵��
		$status = DEF_RETCD_DE;
	}

	// DB������
	$dba->close();
	
	/*==============================================*/
	// ����
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $hit_num);
	//	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);				// mod 2016/04/28 T.Yoshino
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val, "", $arr_opt_flg);

	// ������
	//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
	put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
?>
