<?php
/*========================================================*/
// �ե�����̾��store_search.cgi
// ����̾��������︡��
//
// ��������
// 2011/11/04 H.Nakamura	��������
// 2013/03/11 Y.Matsukawa	�ꥢ�륿����ǡ���
// 2014/01/06 H.Osamoto		���ĥ�ե����null�׵�ǽ�ɲ�
// 2014/12/03 H.Osamoto		FILTER��2�Х���ʸ�����󥳡����б�
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'y02';

	/*==============================================*/
	// CGI̾
	/*==============================================*/
	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

	/*==============================================*/
	// �꥿���󥳡������
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
	define( 'DEF_RETCD_DE',   '00000' );       //���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
	define( 'DEF_RETCD_DEND', '00001' );       //���˸��礦�ǡ�������ʸ�³�ǡ��������
	define( 'DEF_RETCD_DNE',  '11009' );       //���˸��礦�ǡ����ʤ�
	define( 'DEF_RETCD_AERR', '12009' );       //ǧ�ڥ��顼
	define( 'DEF_RETCD_DERR1','17900' );       //�ǡ����١��������������顼
	define( 'DEF_RETCD_DERR2','17002' );       //�ǡ����١��������������顼
	define( 'DEF_RETCD_DERR3','17999' );       //�ǡ����١��������������顼
	define( 'DEF_RETCD_PERR1','19100' );       //���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19200' );       //���ϥѥ�᡼�����顼(��ʸ���顼)
	define( 'DEF_RETCD_PERR3','19200' );       //���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)

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
	//�����ϳ���
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');		/* ���ID */
	$LAT		= getCgiParameter('lat','');			/* ���� */
	$LON		= getCgiParameter('lon','');			/* ���� */
	$FREWD		= getCgiParameter('freeword','');			/* �ե꡼��� */
	$FILTER		= getCgiParameter('filter','');			/* �ʤ���߾�� */
	$POS		= getCgiParameter('pos','1');			/* �������� */
	$CNT		= getCgiParameter('cnt','100');			/* ������� */
	$SORT		= getCgiParameter('sort','');			/* �����Ƚ� */
	$ENC		= getCgiParameter('enc', DEF_PRM_ENC_UTF8);		/* ʸ�������� */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* �ݥ���ȥե饰 */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* ¬�Ϸ� */
	$OUTF		= getCgiParameter('outf',DEF_PRM_OUTF_JSON);		/* ���Ϸ��� */

	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// ʸ���������Ѵ�

	$SORT = mb_ereg_replace("'", "", $SORT);

	/*==============================================*/
	// �ʤ���߾��
	/*==============================================*/
	$FILTER_sql = '';
	$FILTER = f_dec_convert($FILTER);	// add 2014/12/03 H.Osamoto
	edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
	$log_frewd = f_dec_convert($FREWD);
	$log_frewd = mb_ereg_replace(' ', '_', $log_frewd);
	$log_frewd = mb_ereg_replace('��', '_', $log_frewd);
	$arr_log_jkn[53] = mb_strimwidth($log_frewd, 0, 128, '...');
	$log_jkn = implode(' ', $arr_log_jkn);

	/*==============================================*/
	// LOG�����Ѥ˥ѥ�᡼���ͤ���
	/*==============================================*/
	$parms = '';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' '.$log_jkn;

	/*==============================================*/
	// ���ϥ��饹
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* e-map���ID */
	if ($CID == '') {
		// ���Ĵ�Ȥʤ�
		$status = DEF_RETCD_PERR1;// �����ǡ���̵��
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* ¬�Ϸ� */
	if ($DATUM != DATUM_TOKYO && $DATUM != DATUM_WGS84) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* �������� */
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* ������� */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT > 1000) {
		$CNT = 1000;
	}

	/* ʸ�������� */
	if ($INPUT_ENC != 'SJIS' && $INPUT_ENC != 'EUC' && $INPUT_ENC != 'UTF8') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('enc', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* �ݥ���ȥե饰 */
	if ($PFLG != '1' && $PFLG != '2' && $PFLG != '3') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pflg', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* ���Ϸ��� */
	if ($OUTF != 'JSON' && $OUTF != 'XML') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		$CgiOut->set_debug('dbopen', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// �����ӥ�����
	/*==============================================*/
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// CGI���ѵ���
	/*==============================================*/
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
	} else {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_AERR;
		$CgiOut->set_debug('CGI���ѵ���', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	$dba->free($stmt);

	/*==============================================*/
	// SSLǧ�ڡ�IP�����å�����ե�������å�
	/*==============================================*/
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	$dba->free($stmt);

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
	$arr_item = array();
	$sql  = " SELECT";
	$sql .= "    COL_NAME,ITEM_NAME,VAL_KBN";
	$sql .= " FROM";
	$sql .= "    KYOTEN_ITEM_TBL";
	$sql .= " WHERE"; 
	$sql .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql .= " AND LIST_KBN = 1";
	$sql .= " ORDER BY DISP_NUM";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
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
			if ($item['VAL_KBN'] == 'L') {
				$sql_kbn  = " SELECT";
				$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
				$sql_kbn .= " FROM";
				$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
				$sql_kbn .= " WHERE";
				$sql_kbn .= "    CORP_ID = '".escapeOra($CID)."'";
				$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
				$sql_kbn .= " ORDER BY ITEM_VAL";
				if (!$dba->sqlExecute($sql_kbn, $stmt)) {
					$dba->free($stmt);
					$dba->close();
					$status = DEF_RETCD_DERR3;
					$CgiOut->set_debug('DB����', __LINE__);
					$CgiOut->set_status($status, 0, 0);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
	}

	/*==============================================*/
	// ������︡��
	/*==============================================*/
	$sql  = " SELECT";
	$sql .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID,";
	$sql .= " CASE";
	$sql .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
	$sql .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
	$sql .= "         THEN '1'";
	$sql .= "         ELSE '0'";
	$sql .= " END AS BFLG ";
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			$sql .= ", ".$item['COL_NAME'];
		}
	}
	$sql .= " FROM";
	$sql .= "    KYOTEN_TBL K";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	if ($FREWD != '') {
		$frewd_sql = array();
		$FREWD = f_dec_convert($FREWD);
		$FREWD = mb_ereg_replace('��',' ',$FREWD);
		$words = explode(' ', $FREWD);
		foreach ($words as $w) {
			if ($w != '') {
				$frewd_sql[] = "INSTR(FREE_SRCH, '" . fw_normalize($w) . "') <> 0";
			}
		}
		if (count($frewd_sql)) {
			$sql .= " AND (".implode(' AND ', $frewd_sql).")";
		}
	}
	if ($FILTER_sql != '') {
		$sql .= " AND ".$FILTER_sql;
	}
	$FILTER_sql = f_dec_convert($FILTER_sql);
	// �����ȥ�������
	$sql_order = '';
	if ($SORT != '') {
		$sql_order .= $SORT;
	}
	if ($SORT != '') {
		 $sql_order .= ',';
	}
	$sql_order .= 'KYOTEN_ID';
	$sql .= " ORDER BY ".$sql_order;
	$sql = "SELECT S.*, rownum rn FROM (".$sql.") s";

	// �ҥåȷ������
	$hit_num = 0;
	$stmt = null;
	$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql.")";
	if (!$dba->sqlExecute($sql_count, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['HITCNT'];
	}
	$dba->free($stmt);

	// �ǡ�������
	$rec_num = 0;
	$arr_kid = array();		// add 2013/03/11 Y.Matsukawa
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data = " SELECT";
		$sql_data .= "       *";
		$sql_data .= " FROM (".$sql.")";
		$sql_data .= " where rn >= ".$POS;
		$to = $POS+$CNT-1;
		$sql_data .= " AND rn <= ".$to;
		$stmt = null;
		if (!$dba->sqlExecute($sql_data, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('DB����', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
		while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if ($DATUM == DATUM_WGS84) {
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
					if ($item['VAL_KBN'] == 'L') {
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
			}
			$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		$rec_num = count($arr_kyoten);
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

	$dba->close();

	if (!$rec_num) {
		// �����ǡ���̵��
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if (($POS+$rec_num-1) < $hit_num) {
		// ��³�ǡ���ͭ��
		$status = DEF_RETCD_DEND;
	} else {
		// ��³�ǡ���̵��
		$status = DEF_RETCD_DE;
	}

	/*==============================================*/
	// ����(����)
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $hit_num);
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);

	// ������
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
?>
