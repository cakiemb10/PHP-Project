<?php
/*========================================================*/
// �ե�����̾��kyotenarea_j.cgi
// ����̾��Ź�ޥ��ꥢ����
//
// ��������
// 2014/11/27 C.Eguchi	��������
/*========================================================*/

	/*==============================================*/
	// ���顼��������CGI���̿� ����
	/*==============================================*/
	$CGICD = "a01";

	/*==============================================*/
	// ���������
	/*==============================================*/
	/* ���ϥѥ�᡼��*/
	define( 'DEF_PRM_ENC_UTF8',			 'UTF8' );	   // ʸ�������ɡ�UTF8��
	define( 'DEF_PRM_ENC_SJIS',			 'SJIS' );	   // ʸ�������ɡ�SJIS��
	define( 'DEF_PRM_ENC_EUC',			  'EUC'  );	   // ʸ�������ɡ�EUC��

	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );	   // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
	define( 'DEF_RETCD_DEND', '00001' );	   // ���˸��礦�ǡ�������ʸ�³�ǡ��������
	define( 'DEF_RETCD_DNE1', '11008' );	   // ���ꥢ��������̵�����顼
	define( 'DEF_RETCD_DNE2', '11009' );	   // ���˸��礦�ǡ����ʤ�
	define( 'DEF_RETCD_DERR1','17900' );	   // �ǡ����١�����³���顼
	define( 'DEF_RETCD_PERR1','19100' );	   // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19200' );	   // ���ϥѥ�᡼�����顼(��ʸ���顼)

	/*==============================================*/
	// ����ե�����
	/*==============================================*/
	include("ZdcCommonFunc.inc");	// ���̴ؿ�
	include("chk.inc");		 	// �ǡ��������å���Ϣ
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("jkn.inc");	   		// ��������Խ�
	require_once("function.inc");	// ���̴ؿ�
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
	$CID		= getCgiParameter('cid', 	'');				/* ���ID */
	$AREA		= getCgiParameter('area', 	'');				/* ���ꥢ������� */
	$FILTER		= getCgiParameter('filter', '');				/* �ʤ���߾�� */
	$POS		= getCgiParameter('pos', 	1);					/* ��������(�ǥե����1) */
	$CNT		= getCgiParameter('cnt', 	100);				/* �������(�ǥե����100) */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);	/* ʸ��������(�ǥե����UTF8) */


	// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// ʸ���������Ѵ�

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* ���ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	/* �������ϰ���*/
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	/* ������� */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	if ($CNT > 1000) {
		$CNT = 1000;
	}

	/* ʸ�������� */
	if ($INPUT_ENC != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC != DEF_PRM_ENC_EUC &&
		$INPUT_ENC != DEF_PRM_ENC_UTF8) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}


	/* �ʤ���߾�� */
	edit_jkn($FILTER, $edited_jkn, $arr_log_jkn, "k.", '', $CID);

	// ���顼
	if ($status != DEF_RETCD_DE) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	
	/*==============================================*/
	// DB��³�����ץ�
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	/*==============================================*/
	// ¨����ե�å����о���������
	/*==============================================*/
	$immref = isIMMREFAvailable( &$dba, $CID );

	/*==============================================*/
	// �ǡ�������̾����
	/*==============================================*/
	if (!isset($AREA) || (isset($AREA) && $AREA == "")) {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
	}
	else {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
	}

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME = $data["ITEM_NAME"];
			$COL_NAME  = $data["COL_NAME"];
			$VAL_KBN   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME = "";
			$COL_NAME  = "";
			$VAL_KBN   = "";
		}
		$dba->free($stmt);
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	// ��1����
	$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME_1 = $data["ITEM_NAME"];
			$COL_NAME_1  = $data["COL_NAME"];
			$VAL_KBN_1   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME_1 = "";
			$COL_NAME_1  = "";
			$VAL_KBN_1   = "";
		}
		$dba->free($stmt);
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}


	// ��2����
	$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME_2 = $data["ITEM_NAME"];
			$COL_NAME_2  = $data["COL_NAME"];
			$VAL_KBN_2   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME_2 = "";
			$COL_NAME_2  = "";
			$VAL_KBN_2   = "";
		}
		$dba->free($stmt);
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	if ($ITEM_NAME == "" or $ITEM_NAME_1 == "") {
		// ���ꥢ��������̵�����顼
		$status = DEF_RETCD_DNE1;
	}

	// ���ꥢ������������������JKN�������
	if (isset($AREA) && $AREA != "") {
		if (isset($COL_NAME_1) && $COL_NAME_1 != "") {
			switch ($COL_NAME_1) {
				case "NAME":
					$idx = 1;
					break;
				case "ADDR":
					$idx = 2;
					break;
				case "FREE_SRCH":
					$idx = 53;
					break;
				default:
					$idx = intval(substr($COL_NAME_1, 4));
					if ($idx <= 50)
						$idx += 2;
					else
						$idx += 4;
			}
		}
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	/*==============================================*/
	// �оݥǡ�������
	/*==============================================*/

	if ( $immref ) {
		$kyoten_tbl_name = "im_kyoten_tbl";
	} else {
		$kyoten_tbl_name = "kyoten_tbl";
	}

	if (!isset($AREA)  || (isset($AREA) && $AREA == "")) {
		// ��ʬ����
		if ($VAL_KBN == "L") {
			$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
			$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
			$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
			$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //������ͭ��ξ��
				$sql .= " and $edited_jkn ";
			}
			$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
		// ʸ����
		} else {
			$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
			$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
			$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
			$sql = $sql . " where corp_id='" . $CID . "' ";
			$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //������ͭ��ξ��
				$sql .= " and $edited_jkn ";
			}
			$sql = $sql . " and " . $COL_NAME . " is not null";
			$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
		}
	// �裲����
	} else {
		$AREA = mb_convert_encoding($AREA, "EUC-JP", "auto");
		// ��ʬ����
		if ($VAL_KBN == "L") {
			// �裱���ؤ���ʬ����
			if ($VAL_KBN_1 == "L") {
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				$sql = $sql . " and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
			// �裱���ؤ�ʸ����
			} else {
				//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				$sql = $sql . " and k." . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
			}
		// ʸ����
		} else {
			// �裱���ؤ���ʬ����
			if ($VAL_KBN_1 == "L") {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
				$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			// �裱���ؤ�ʸ����
			} else {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
				$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			}
		}
	}

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
	}
	if ($status != DEF_RETCD_DE) {
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	
	$rec_count  = 0;
	$hit_count  = 0;
	$data_count = 0;
	unset($area_list);
	$dbflg	  = 0;

	// pos���֤ޤ��ɤ����Ф�
	for ($n = 1;$n<=$POS - 1;$n++) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$target3 = $data[2];
			$data_count = $data_count + $target3;
			$hit_count = $hit_count + 1;
		} else {
			$dbflg = 1;
			break;
		}
	}

	// �����ǡ����ɤ߹���
	if ( $dbflg == 0 ) {
		for ($n=1; $n<=$CNT; $n++) {
			if( $dba->getRecInto( $stmt,$data ) ) {
				$target1 = ZdcConvZ2H($data[0], $z2h);
				$target2 = ZdcConvZ2H($data[1], $z2h);
				$target3 = $data[2];
				$area_list[] = array(  "area_val"  => $target1
                                     , "disp_val"  => $target2
                                     , "val_count" => $target3);
				$rec_count = $rec_count + 1;
				$data_count = $data_count + $target3;
				$hit_count = $hit_count + 1;
			} else {
				$dbflg = 1;
				break;
			}
		}
	}

	// ��³�ǡ�����ǧ
	if ( $dbflg == 0 ) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$status = DEF_RETCD_DEND;
			$target3 = $data[2];
			$data_count = $data_count + $target3;
			$hit_count = $hit_count + 1;
		}
	}

	// �Ĥ���������
	while ($dba->getRecInto( $stmt,$data )) {
		$target3 = $data[2];
		$data_count = $data_count + $target3;
		$hit_count = $hit_count + 1;
	}

	$dba->free($stmt);

	if (!isset($area_list)) {
		/* ���ơ����� */
		$status = DEF_RETCD_DNE2; // ���˸��礦�ǡ����ʤ�
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}


	/*==============================================*/
	// �ǡ�������(����)
	/*==============================================*/
	/* �����ǡ��������� */
	if (!isset($AREA) || (isset($AREA) && $AREA == "")) {
	
		$area_info = array(  "area1_col"	 => $COL_NAME
						   , "area1_name"	 => $ITEM_NAME
						   , "selected_area" => ""
						   , "area2_col"	 => $COL_NAME_2
						   , "area2_name"	 => $ITEM_NAME_2
						   , "data_count"	 => $data_count
						  );
	}
	else {
		$area_info = array(  "area1_col"	 => $COL_NAME_1
						   , "area1_name"	 => $ITEM_NAME_1
						   , "selected_area" => $AREA
						   , "area2_col"	 => $COL_NAME
						   , "area2_name"	 => $ITEM_NAME
						   , "data_count"	 => $data_count
						  );
	}

	output_json($INPUT_ENC, array(  "return_code" => $CGICD.$status
	                              , "rec_count"   => $rec_count
	                              , "hit_count"   => $hit_count
	                              , "area_info"   => $area_info
	                              , "area_list"   => $area_list
	                              ));

	exit;

	/*==============================================*/
	// ����
	/*==============================================*/
	$dba->close();

?>
