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
	$CGICD = 'y05';

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
	include('store_kyoten_outf.inc');
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
	$CID	= getCgiParameter('cid', '');					/* ���ID */
	$RID	= getCgiParameter('rid', '');					/* �롼��ID */
	$BUFFER	= getCgiParameter('buffer','100');				/* �롼�Ȥ���θ�����Υ */
	$FILTER	= getCgiParameter('filter','');					/* �ʤ���߾�� */
	$POS	= getCgiParameter('pos','1');					/* �������� */
	$CNT	= getCgiParameter('cnt','100');					/* ������� */
	$PFLG	= getCgiParameter('pflg', DEF_PRM_PFLG_MSEC);	/* �ݥ���ȥե饰 */
	$OUTF	= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);	/* ���Ϸ��� */
		
	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// ʸ���������Ѵ�
	

	/*==============================================*/
	// �ʤ���߾��
	/*==============================================*/
	$FILTER_sql = '';
	edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
	$log_jkn = implode(' ', $arr_log_jkn);
	

	/*==============================================*/
	// �����ѥ��饹������
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);


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
	/* �롼�Ȥ���θ�����Υ */
	if ($BUFFER < 1 || $BUFFER >= 100000) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('buffer', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	/* �������ϰ���*/
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	/* ������� */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	if ($CNT > 200) {
		$CNT = 200;
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
	$arr_kyoten_output = array();
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
		$arr_kyoten_output[] = $data;
	}
	$dba->free($stmt);
	$rec_num = count($arr_kyoten_output);

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
	$target_route_array = explode(";", $arr_kyoten_output[0]['ROUTE_INFO']);


	$route_line = "";

	foreach( $target_route_array as $key => $val ){
		$target_point_array[$key] = explode(" ", $val);
		$target_lat_array[] = $target_point_array[$key][0];
		$target_lon_array[] = $target_point_array[$key][1];
		
		if ($route_line == "") {
			$route_line .= $target_point_array[$key][1] . " " . $target_point_array[$key][0];
		} else {
			$route_line .= "," . $target_point_array[$key][1] . " " . $target_point_array[$key][0];
		}
	}

	// �롼�Ⱦ��󤬼����Ǥ��ʤ����ϥ��顼
	if (!$route_line) {
		$status = DEF_RETCD_RERR;
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->set_debug('�롼��õ�����顼', __LINE__);
		$CgiOut->err_output();
		exit;
	}


	/*==============================================*/
	// �롼�ȥݥꥴ������
	/*==============================================*/
	$reader = new GEOSWKTReader();
	$writer = new GEOSWKTWriter();
	$writer->setRoundingPrecision(0);

	// BUFFER����ٷ���ñ�̤��ͤ��Ѵ��ʰ��ٷ��٤��Ѵ���Ψ���Ϲ�θ���ʤ���
	$latlon_buffer = $BUFFER * 40;

	// ����
	$g = $reader->read('LINESTRING('.$route_line.')');
	$retRoutePoly = $g->buffer($latlon_buffer, array('quad_segs' => 1, 'endcap' => GEOSBUF_CAP_ROUND));
	$retRoutePoly_str = $writer->write($retRoutePoly);

	// ����ʸ�������
	$retRoutePoly_str = str_replace('))', '', str_replace('POLYGON ((', '', $retRoutePoly_str));
	$tmp_arr = explode(",", $retRoutePoly_str);

	foreach($tmp_arr as $tmp_point) {
		$tmp_point = trim($tmp_point);
		
		list($tmp_lon, $tmp_lat) = explode(" ", $tmp_point);
		
		// ����ʸ�������ʵ��˥ޥ���ݥꥴ����ֵѤ�����礬����١�
		$tmp_lat = trim(preg_replace('/[\(\)]/', '', $tmp_lat));
		$tmp_lon = trim(preg_replace('/[\(\)]/', '', $tmp_lon));
		
		$route_poly_arr[] = cnv_dms2hour($tmp_lat).",".cnv_dms2hour($tmp_lon);
		
		// �����ϰ�
		if ($NELAT < $tmp_lat) $NELAT = $tmp_lat;
		if ($NELON < $tmp_lon) $NELON = $tmp_lon;
		if ($SWLAT > $tmp_lat) $SWLAT = $tmp_lat;
		if ($SWLON > $tmp_lon) $SWLON = $tmp_lon;
	}

	// ���פˤʤä��롼�Ⱦ������
	unset($route_xml);
	unset($route_dat);
	unset($point_array);
	unset($point);
	unset($route_line);

	// ���פˤʤä��ݥꥴ��������
	unset($retRoutePoly);
	unset($tmp_arr);
	unset($tmp_point);


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
	$sql .= " AND LIST_KBN = 1";
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
	// �����Ѥ�ɬ�׺���¤Υ����Τ��������
	/*==============================================*/
	/* ���֥��������� */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    KYOTEN_ID, LAT, LON";
	//	$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $STLAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
	//	$sql_sub_near .= " + POWER( ABS( LON - $STLON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI ";
	$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $target_lat_array[0] ) * (  9 / 300000 * 1000 ), 2 )";
	$sql_sub_near .= " + POWER( ABS( LON - $target_lon_array[0] ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI ";
	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    KYOTEN_TBL K";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql_sub_near .= " AND LAT >= ".$SWLAT;
	$sql_sub_near .= " AND LAT <= ".$NELAT;
	$sql_sub_near .= " AND LON >= ".$SWLON;
	$sql_sub_near .= " AND LON <= ".$NELON;
	$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	if ($FILTER_sql != '') {
		$sql_sub_near .= " AND ".$FILTER_sql;
	}
	$FILTER_sql = f_dec_convert($FILTER_sql);
	$sql_sub_near .= " order by KYORI, KYOTEN_ID";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";

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
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['HITCNT'];
	}
	$dba->free($stmt);
	
	
	// �����Ѥ�ɬ�׺���¤Υ����Τ߼���
	$rec_num = 0;
	$arr_kyoten = array();
	if ($hit_num > 0) {
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
		
		
		/*==============================================*/
		// �⳰Ƚ��
		/*==============================================*/
		$reader = new GEOSWKTReader();
		$writer = new GEOSWKTWriter();
		$writer->setRoundingPrecision(0);
		
		$g1 = $reader->read('POLYGON(('.$retRoutePoly_str.'))');
		
		foreach($arr_kyoten as $key => $kyoten_data) {
			$check_lat = $kyoten_data['LAT'];
			$check_lon = $kyoten_data['LON'];
			
			$g2 = $reader->read('POINT('.$check_lon.' '.$check_lat.')');
			
			$retAssert = $g1->contains($g2);
			
			if ($retAssert == "") {
				unset($arr_kyoten[$key]);
			}
		}

	// ������������ͤ�
	$arr_kyoten = array_values($arr_kyoten);
		
	// �ǡ����������
	$hit_num = count($arr_kyoten);
	
	// ����POS�������ʤ����ϥ��顼
	if ($hit_num < $POS) {
		// �����ǡ���̵��
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB����', __LINE__);
		$CgiOut->set_status($status, 0, $hit_num);
		$CgiOut->err_output();
		exit;
	}
	
	// �����о�����
	$kyotenid_str = "";
	for($i = $POS; $i < $CNT+$POS; $i++) {
		if ($arr_kyoten[$i-1]['KYOTEN_ID']) {
			if ($kyotenid_str) {
				$kyotenid_str .= ",";
			}
			// SQL�ѵ���IDʸ�������
			$kyotenid_str .= $arr_kyoten[$i-1]['KYOTEN_ID'];
		}
	}
	
	// ���פˤʤä������������
	unset($arr_kyoten);
		
		/*==============================================*/
		// �ֵ��ѥǡ�������
		/*==============================================*/
		$arr_kyoten_output = array();
		if ($hit_num > 0) {
			/* ���֥��������� */
			$sql_sub_near  = " SELECT";
			$sql_sub_near .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
//			$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $STLAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
//			$sql_sub_near .= " + POWER( ABS( LON - $STLON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
			$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $target_lat_array[0] ) * (  9 / 300000 * 1000 ), 2 )";
			$sql_sub_near .= " + POWER( ABS( LON - $target_lon_array[0] ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
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
			$sql_sub_near .= " AND LAT >= ".$SWLAT;
			$sql_sub_near .= " AND LAT <= ".$NELAT;
			$sql_sub_near .= " AND LON >= ".$SWLON;
			$sql_sub_near .= " AND LON <= ".$NELON;
			$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
			if ($FILTER_sql != '') {
				$sql_sub_near .= " AND ".$FILTER_sql;
			}
			$FILTER_sql = f_dec_convert($FILTER_sql);
			$sql_sub_near .= " order by KYORI, KYOTEN_ID, CORP_ID";
			$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
			$sql_data = "SELECT * FROM (".$sql_near.")";
			$sql_data .= " where kyoten_id in (".$kyotenid_str.")";
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
				$arr_kyoten_output[] = $data;
			}
			$dba->free($stmt);
			$rec_num = count($arr_kyoten_output);
		}
		
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
					foreach ($arr_kyoten_output as $k=>$kyoten) {
						$kyoid = $kyoten['KYOTEN_ID'];
						if ($arr_rd_kyoten[$kyoid]) {
							$arr_kyoten_output[$k]['RD'] = $arr_rd_kyoten[$kyoid];
						}
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
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten_output, $arr_item_val);
	// ������
//	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
?>
