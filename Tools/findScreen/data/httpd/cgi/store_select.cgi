<?php
/*========================================================*/
// �ե�����̾��store_select.cgi
// ����̾��Ź��ID����
//
// ��������
// 2011/12/16 H.Nakamura	��������
// 2013/03/11 Y.Matsukawa	�ꥢ�륿����ǡ���
// 2013/12/20 H.Osamoto		�ǡ�����������ID����
// 2014/01/06 H.Osamoto		���ĥ�ե����null�׵�ǽ�ɲ�
// 2014/10/29 H.Osamoto		�������������Զ�罤��
// 2016/01/14 Y.Matsukawa	¿���쥵���Ȥ���θƤӽФ����б���������³��
// 2016/01/28 T.Yoshino		����������ʣ���ξ��ι�θ���ɲ�
// 2017/01/20 Y.Matsukawa	filter����
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'y03';

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
	include('oraDBAccessMst.inc');
	include('chk.inc');				// �ǡ��������å���Ϣ
	include('log.inc');				// ������
	include('auth.inc');				// �ʰ�ǧ��
	include("jkn.inc");				// �ʤ���߾���Խ�
	include('store_kyoten_outf.inc');
	include('rd_sql.inc');		// add 2013/03/11 Y.Matsukawa

	/*==============================================*/
	// ���顼���Ϥ�����Ū��OFF
	/*==============================================*/
	//error_reporting(E_ALL^E_NOTICE);
	//error_reporting(0);
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
	$CID		= getCgiParameter('cid', 	'');					/* ���ID */
	$ID			= getCgiParameter('id', 	'');					/* ����ID */
	if ($ID == '') $ID = getCgiParameter('kid', '');		// add 2016/01/14 Y.Matsukawa
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* ʸ�������� */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* �ݥ���ȥե饰 */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* ¬�Ϸ� */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* ���Ϸ��� */
	// add 2016/01/14 Y.Matsukawa [
	$INTID		= getCgiParameter('intid',	'');					/* �������ѻ���ID */
	$OPT		= getCgiParameter('opt', '');						/* �������ѻ��δ��ID */
	$TYPE		= getCgiParameter('type', '');						/* ������ */
	$NOLOG		= getCgiParameter('nolog', '');						/* No logging */
	// add 2016/01/14 Y.Matsukawa ]
	$FILTER		= getCgiParameter('filter','');			/* �ʤ���߾�� */	// add 2017/01/20 Y.Matsukawa

	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	//$OPTION_CD = $CID;		mod 2016/01/14 Y.Matsukawa
	$OPTION_CD = ($INTID != '')?$OPT:$CID;

	include('store_enc.inc');			// ʸ���������Ѵ�

	// add 2017/01/20 Y.Matsukawa
	/*==============================================*/
	// �ʤ���߾��
	/*==============================================*/
	$FILTER_sql = '';
	$FILTER = f_dec_convert($FILTER);
	edit_jkn($FILTER, $FILTER_sql, $arr_log_jkn);

	/*==============================================*/
	// LOG�����Ѥ˥ѥ�᡼���ͤ�����
	/*==============================================*/
	$parms = $ID;
	$parms .= ' '.'1';

	/*==============================================*/
	// �����ѥ��饹������
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	
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
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	
	/* Ź��ID */
	if ($ID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('id', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/* ���ܥ����� */		// add 2016/01/14 Y.Matsukawa
	if ($TYPE != '') {
		$TYPE = intval(urldecode($TYPE));
		if ($TYPE < 1 && $TYPE > 5) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('type', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}

	/* ʸ�������� */
	if ($INPUT_ENC != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC != DEF_PRM_ENC_EUC &&
		$INPUT_ENC != DEF_PRM_ENC_UTF8) {
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
	if ($DATUM != DEF_PRM_DATUM_TOKYO&& 
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
	
	$dbaMst = new oraDBAccessMst();
	if (!$dbaMst->open()) {
		$dbaMst->close();
		$status = DEF_RETCD_DERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
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
			$CgiOut->set_debug('SSLǧ��', __LINE__);
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
							$CgiOut->set_debug('SSLǧ��', __LINE__);
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
							$CgiOut->set_debug('SSLǧ��', __LINE__);
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
				$CgiOut->set_debug('SSLǧ��', __LINE__);
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
	// �����̾�ꥹ�ȼ��� 
	/*==============================================*/
	$sql  = " SELECT"; 
	$sql .= "    COL_NAME, VAL_KBN, ITEM_NAME";
	$sql .= " FROM";
	$sql .= "    KYOTEN_ITEM_TBL";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
	//$sql .= " AND SYOUSAI_KBN = 1";		del 2016/01/14 Y.Matsukawa
	// add 2016/01/14 Y.Matsukawa [
	switch ($TYPE) {
		case '1':
			$sql .= " AND SYOUSAI_KBN = '1'";
			break;
		case '2':
			$sql .= " AND INSATSU_KBN = '1'";
			break;
		case '3':
			$sql .= " AND FUKIDASI_KBN = '1'";
			break;
		case '4':
			$sql .= " AND M_SYOUSAI_KBN = '1'";
			break;
		case '5':
			$sql .= " AND OPT_06 = '1'";
			break;
		default:
			$sql .= " AND SYOUSAI_KBN = '1'";
			break;
	}
	// add 2016/01/14 Y.Matsukawa ]
	$sql .= " ORDER BY DISP_NUM";
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
			$sql_kbn  = " SELECT";
			$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
			$sql_kbn .= " FROM";
			$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
			$sql_kbn .= " WHERE";
			$sql_kbn .= " CORP_ID = '".escapeOra($CID)."'";
			$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
			$sql_kbn .= " ORDER BY ITEM_VAL";
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
			$arr_kbn[$item['COL_NAME']] = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
				$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
			}
			$dba->free($stmt);
		}
	}

	/*==============================================*/
	// ����ID����
	/*==============================================*/
	$subsql  = " SELECT";
	$subsql .= "    CORP_ID, KYOTEN_ID, LAT, LON";
	$subsql .= " FROM";
	$subsql .= "    KYOTEN_TBL";
	$subsql .= " WHERE";
	$subsql .= "    CORP_ID = '".escapeOra($CID)."'";
	$subsql .= " AND KYOTEN_ID = '".escapeOra($ID)."'";
	$subsql .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	// add 2017/01/20 Y.Matsukawa [
	if ($FILTER_sql != '') {
		$subsql .= " AND ".$FILTER_sql;
	}
	// add 2017/01/20 Y.Matsukawa ]

	/* �ҥåȷ������ */
	$sql  = " SELECT ";
	$sql .= "    s.*, rownum rn";
	$sql .= " FROM"; 
	$sql .= "    (".$subsql.") s";
	$hit_num = 0;
	$stmt = null;
	$sql_count  = " SELECT";
	$sql_count .= "    count(*) HITCNT";
	$sql_count .= " FROM";
	$sql_count .= "    (".$sql.")";
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

	/* �����ǡ������� */
	$rec_num = 0;
	$arr_kid = array();		// add 2013/03/11 Y.Matsukawa
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data  = " SELECT";
		$sql_data  .= "     *";
		$sql_data  .= " FROM(";
		//  ��������NEW��������ɽ���ե饰 
		//  ����������λ������NULL�ξ�硧'0'
		//  SYSDATE�����������齪λ�������äƤ����硧'1'
		//  SYSDATE�����������齪λ�������äƤ��ʤ���硧'0'
		// mod 2014/10/29 H.Osamoto [
		//	$sql_data .= " SELECT";
		//	$sql_data .= "     CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID,"; 
		//	$sql_data .= " CASE";
		//	$sql_data .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
		//	$sql_data .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
		//	$sql_data .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
		//	$sql_data .= "         THEN '1'";
		//	$sql_data .= "         ELSE '0'";
		//	$sql_data .= " END AS BFLG ";
		//	if ( count($arr_item) > 0 ) {	//���ǤϤʤ����
		//		//$first_flg = 0;
		//		foreach( $arr_item as $rowdata ) {
		//			$sql_data .= ", " . $rowdata['COL_NAME'];
		//		}
		//		$sql_data .= " ";
		//	}
		//	$sql_data .= " FROM ";
		//	$sql_data .= "     KYOTEN_TBL)";
		//	//  �����ޤ� 
		//	$sql_data .= " WHERE";
		//	$sql_data .= "     CORP_ID = '".escapeOra($CID)."'";
		//	$sql_data .= " AND KYOTEN_ID = '".escapeOra($ID)."'";
		$sql_data .= " SELECT";
		$sql_data .= "     A.CORP_ID, A.KYOTEN_ID, A.LAT, A.LON, A.ICON_ID,"; 
		$sql_data .= "     DECODE(B.INS_DT, NULL, '0', '1') AS K_GIF_NUM,"; 
		$sql_data .= " CASE";
		$sql_data .= "     WHEN A.DISP_NEW_S_DATE IS NULL AND A.DISP_NEW_E_DATE IS NULL THEN '0'";
		$sql_data .= "     WHEN SYSDATE BETWEEN NVL(A.DISP_NEW_S_DATE, SYSDATE) AND ";
		$sql_data .= "         NVL(A.DISP_NEW_E_DATE, SYSDATE)";
		$sql_data .= "         THEN '1'";
		$sql_data .= "         ELSE '0'";
		$sql_data .= " END AS BFLG ";
		if ( count($arr_item) > 0 ) {	//���ǤϤʤ����
			//$first_flg = 0;
			foreach( $arr_item as $rowdata ) {
				$sql_data .= ", A." . $rowdata['COL_NAME'];
			}
			$sql_data .= " ";
		}
		$sql_data .= " FROM ";
		$sql_data .= "     KYOTEN_TBL A, KYOTEN_GIF_TBL B ";
		//  �����ޤ� 
		$sql_data .= " WHERE A.CORP_ID = B.CORP_ID(+) AND A.KYOTEN_ID = B.KYOTEN_ID(+) ";
		$sql_data .= " AND A.CORP_ID = '".escapeOra($CID)."'";
		$sql_data .= " AND A.KYOTEN_ID = '".escapeOra($ID)."'";
		$sql_data .= " ) ";
		// mod 2014/10/29 H.Osamoto ]
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
			$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		$rec_num = count($arr_kyoten);


		// add 2013/03/11 Y.Matsukawa
		/*==============================================*/
		// RD�ǡ�������
		/*==============================================*/
		$arr_rd_kyoten = array();
		if ($use_rd && $rec_num) {
			// �������롼�׼���
			$arr_grp = selectRDGroupByView($dba, $CID, 1);
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

		// add 2016/01/28 T.Yoshino[
		/*==============================================*/
		// ���߲����ǡ�������
		/*==============================================*/
		$arr_img	 = array();
		$arr_img_def = array();
		$arr_img['CNT']	 = 0;

		$sql_img_def  = " SELECT";
		$sql_img_def .= "    MAX(IMG_NO) AS IMG_CNT";
		$sql_img_def .= " FROM";
		$sql_img_def .= "    KYOTEN_IMG_DEF_TBL";
		$sql_img_def .= " WHERE";
		$sql_img_def .= "    CORP_ID = '".escapeOra($CID)."'";

		$stmt = null;

		if (!$dbaMst->sqlExecute($sql_img_def, $stmt)) {
			$dbaMst->free($stmt);
			$dbaMst->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('DB����', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}

		if ($dbaMst->getRecInto($stmt, $data, OCI_ASSOC)) {
			$arr_img['CNT'] = $data['IMG_CNT'];
		}
		$dbaMst->free($stmt);


		if( $arr_img['CNT'] != "0" && $arr_img['CNT'] != "" ){
			$sql_img  = " SELECT";
			$sql_img .= "    IMG_NO, GIF_DATA";
			$sql_img .= " FROM";
			$sql_img .= "    KYOTEN_IMG_TBL";
			$sql_img .= " WHERE";
			$sql_img .= "    CORP_ID = '".escapeOra($CID)."'";
			$sql_img .= "    AND KYOTEN_ID = '".escapeOra($ID)."'";

			$stmt = null;

			if (!$dba->sqlExecute($sql_img, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('DB����', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
			
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				foreach( $data as $key => $val ){
					$arr_img[$data['IMG_NO']]['IMG_NO']	 = $data['IMG_NO'];
				}
			}
			$dba->free($stmt);

		}
		// add 2016/01/28 T.Yoshino]


		/*==============================================*/
		// ����(����)
		/*==============================================*/
		$CgiOut->set_status($status, $rec_num, $hit_num);
		//$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);			// mod 2016/01/28 T.Yoshino
		$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val, $arr_img);
	}

	// DB������
	$dba->close();
	$dbaMst->close();

	/*==============================================*/
	// ����(�����ǡ����ʤ�)
	/*==============================================*/
	if (!$rec_num) {
		// �����ǡ���̵��
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	// ������
	if (!$NOLOG) {		// add 2016/01/14 Y.Matsukawa
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
	}
?>
