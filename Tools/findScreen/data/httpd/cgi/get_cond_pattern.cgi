<?php
/*========================================================*/
// �ե�����̾��get_cond_pattern.cgi
// ����̾���ʹ��߾�����
//
// ���⡧�����Ȥιʹ��߾����֤���
//
// ��������
// 2013/02/20 H.Osamoto		��������
/*========================================================*/
//	header( "Content-Type: Text/html; charset=UTF-8" );

	include('d_serv_ora.inc');
	include('inc/oraDBAccessMst.inc');
	include('inc/sql_collection_cond_pattern.inc');
	require_once('function.inc');
	require_once('/home/emap/src/Jsphon/Encoder.php');

	define("D_STATUS_NO_MATCH", "11");	// �����ǡ����ʤ��ʹʹ��߾��ʤ���
	define("D_STATUS_DB_ERR",   "17");	// DB���顼���ơ������١���������
	define("D_STATUS_PRM_ERR",  "19");	// �ѥ�᡼�����顼���ơ������١���������

	define("D_DEF_JOIN_GRP", "AND");		// ���롼�פΥǥե���ȷ����
	define("D_DEF_JOIN_LST", "AND");		// �ꥹ�ȹ��ܤΥǥե���ȷ����
	define("D_DEF_JOIN_FLG", "OR");			// �ե饰���ܤΥǥե���ȷ����

	// JSON�ѥ������
	define("D_RET_CODE", "return_code");
	define("D_COND",     "cond");
	define("D_JOIN",     "join");
	define("D_GRP",      "grp");
	define("D_ITEM",     "item");

	$cgi_kind = "c01";	// CGI����
	$enc = "UTF-8";		// ����ʸ��������
	$status = "";		// ���ơ�����������

	// ���ϥѥ�᡼������
	$cid = getCgiParameter('cid','');	// ���ID

	while(1) {
		// ���ϥѥ�᡼�������å�
		if ( $cid == "" ) {
			$status = $cgi_kind . D_STATUS_PRM_ERR . "001";
			break;
		}

		// DB��³
		$dba = new oraDBAccessMst();
		if ( ! $dba->open() ) {
			$dba->close();
			$status = $cgi_kind . D_STATUS_DB_ERR . "900";	// DB��³���顼
			break;
		}

		// �ʹ��߾�����(�ǡ�����)
		$retcd = getCondPattern( &$dba, $cid, &$json_cond_data );
		$dba->close();
		if ( $retcd != 0 ) {
			if ($retcd == "1") {
				// �����ǡ����ʤ�
				$status = $cgi_kind . D_STATUS_NO_MATCH . "009";	// �ʹ��߾��ʤ�
			} else {
				// SQL�¹ԥ��顼
				$status = $cgi_kind . D_STATUS_DB_ERR . "999";	// ����¾DB���顼
			}
			break;
		}

		$status = $cgi_kind . "00000";	// ���凉�ơ�����������

		break;
	}
	
	// ���ơ����������ʥ��顼���ϥ��ơ��������Τ߽��ϡ�
	$output_str = outputJsonStatus($json_cond_data, $status);

	// ���ϥǡ�����ʸ���������Ѵ�(EUC��UTF8)
	mb_convert_variables( $enc, 'EUC', $output_str);


	// json����
	header( "Content-type: application/json charset=utf-8" );
	echo $output_str;

?>
