<?php
/*========================================================*/
// �ե�����̾��recommended_route.cgi
// ����̾����������롼�ȼ���
//
// ��������
// 2015/01/07 t.yoshino		��������
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = 'y06';

	/*==============================================*/
	// CGI̾
	/*==============================================*/
	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

	/*==============================================*/
	// ���������
	/*==============================================*/
	
	/* ���ϥѥ�᡼��*/
	define( 'DEF_PRM_OUTF_JSON', 	'JSON' );       // ���Ϸ�����JSON��
	define( 'DEF_PRM_OUTF_XML', 	'XML'  );       // ���Ϸ�����XML��
	define( 'DEF_PRM_PFLG_DNUM',	'1'    );       // �ݥ���ȥե饰�ʽ��ʰ��ٷ���ɽ����
	define( 'DEF_PRM_PFLG_MSEC',	'2'    );       // �ݥ���ȥե饰�ʥߥ��ð��ٷ���ɽ����
	define( 'DEF_PRM_PFLG_DMS',    	'3'    );       // �ݥ���ȥե饰����ʬ�ð��ٷ���ɽ����

	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
	define( 'DEF_RETCD_DEND', '00001' );       // ���˸��礦�ǡ�������ʸ�³�ǡ��������
	define( 'DEF_RETCD_DNE',  '11009' );       // ���˸��礦�ǡ����ʤ�
	define( 'DEF_RETCD_AERR', '12009' );       // ǧ�ڥ��顼
	define( 'DEF_RETCD_RERR', '16009' );       // �롼��õ�����顼
	define( 'DEF_RETCD_DERR1','17900' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR2','17002' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR3','17999' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_PERR1','19100' );       // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19200' );       // ���ϥѥ�᡼�����顼(��ʸ���顼)

	// PC2.0�Υ����ǥ롼��õ����Ԥ��٤Υե饰
	$D_PC2 = true;

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
	include('chk.inc');					// �ǡ��������å���Ϣ
	include('log.inc');					// ������
	include('auth.inc');				// �ʰ�ǧ��
	include("jkn.inc");					// �ʤ���߾���Խ�
	include('recommended_route_outf.inc');
	include('rd_sql.inc');

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
	$NELAT = 0;	/* ����ʱ���˰��� */
	$NELON = 0;	/* ����ʱ���˷��� */
	$SWLAT = 200000000;	/* �����ʺ����˰��� */
	$SWLON = 550000000;	/* �����ʺ����˷��� */

	/*==============================================*/
	// �����ϳ���
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$CID	= getCgiParameter('cid', '');							/* ���ID */
	$RID	= getCgiParameter('rid', '');							/* �롼��ID */
	$PFLG	= getCgiParameter('pflg', DEF_PRM_PFLG_MSEC);			/* �ݥ���ȥե饰 */
	$OUTF	= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);			/* ���Ϸ��� */
		
	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// ʸ���������Ѵ�
	

	/*==============================================*/
	// �����ѥ��饹������
	/*==============================================*/
	$CgiOut = new ReccRouteCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);

	
	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* ���ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		exit;
	}
	/* �롼��ID */
	if ($RID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('rid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
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
		exit;
	}
	/* ���Ϸ��� */
	if ($OUTF != DEF_PRM_OUTF_JSON && $OUTF != DEF_PRM_OUTF_XML) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
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
			exit;
		}
	} else {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_AERR;
		$CgiOut->set_debug('CGI���ѵ���', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
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
			exit;
		}
		
		$referer_list = explode(";",  $data['ALLOW_REFERER']);
		
		/* IP�����å� */
		if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
			if (!ip_check2($data['ALLOW_IP'], $_SERVER['REMOTE_ADDR'], ';')) {
				/* ��ե�������å� */
				if (!referer_check(&$referer_list, $_SERVER['HTTP_REFERER'])) {
					/* ��ե���null���ĥ����å� */
					if (!referer_null_check($data['REFERER_NULL'], $_SERVER['HTTP_REFERER'])) {
						$dba->free($stmt);
						$dba->close();
						$status = DEF_RETCD_AERR;
						$CgiOut->set_debug('IP�����å�', __LINE__);
						$CgiOut->set_status($status, 0, 0);
						$CgiOut->err_output();
						exit;
					}
				}
			}
		}
	} else {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_debug('ǧ�ڥ��顼', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	$dba->free($stmt);

	/*==============================================*/
	// �ǡ�����������ID����
	/*==============================================*/
	$CID = getDataCid($dba, $CID);

	/*==============================================*/
	// RD��������
	/*==============================================*/
	$use_rd = isRDAvailable($dba, $CID);
	

	/*==============================================*/
	// �ֵ��ѥǡ�������
	/*==============================================*/
	$arr_route_output = array();
	/* ���֥��������� */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    CORP_ID, ROUTE_ID, ROUTE_INFO ";
	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    RECOMMENDED_ROUTE_TBL R";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql_sub_near .= " AND ROUTE_ID = '".escapeOra($RID)."'";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
	$sql_data = "SELECT * FROM (".$sql_near.")";
	$stmt = null;

	if (!$dba->sqlExecute($sql_data, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$arr_route_output[] = $data;
	}
	$dba->free($stmt);
	$rec_num = count($arr_route_output);

	if (!$rec_num) {
		// �����ǡ���̵��
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, $hit_num);
		$CgiOut->err_output();
		exit;
	}


	/*==============================================*/
	// �롼�Ⱦ������
	/*==============================================*/
	$target_route_array = explode(";", $arr_route_output[0]['ROUTE_INFO']);

	foreach( $target_route_array as $key => $val ){
		$target_point_array[$key] = explode(" ", $val);
		$arr_kyoten_output[$key+1]['LAT']	 = $target_point_array[$key][0];
		$arr_kyoten_output[$key+1]['LON']	 = $target_point_array[$key][1];
	}

	// �ǡ����������
	$hit_num = count($target_route_array);

	// DB������
	$dba->close();


	/*==============================================*/
	// ����
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $hit_num);
//	$CgiOut->output($CID, $ID, $PFLG, $arr_kyoten_output);
	$CgiOut->output($CID, $ID, $PFLG, "", $arr_kyoten_output, "");
	// ������
	
	
?>
