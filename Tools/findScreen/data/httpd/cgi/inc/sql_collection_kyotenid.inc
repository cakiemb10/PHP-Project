<?php
/*========================================================*/
// ��������
// 2007/07/11 Y.Matsukawa	������̤ʤ��λ��˥꥽�����������Ƥ��ʤ��ä�
// 2009/08/27 Y.Matsukawa	�����̼�����
// 2011/03/10 Y.Matsukawa	���ޡ��ȥե������б�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/08/26 Y.Matsukawa	���ޥ��ѵ����̼ܥ�����б�
// 2012/01/27 K.Masuda		���������������˸���/NEWɽ���������ɲ�
// 2012/02/16 Y.Matsukawa	jkn�б�
// 2013/07/19 T.Sasaki		������ʣ���˲����б�
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2015/05/22 H.osamoto		�����̼ܤ˥�����ɤ���Ϳ������ư���ɤ�
/*========================================================*/

function select_col_name( &$dba, $cid, $type, &$retdata, &$err_msg ){
	//CORP_ID�򥭡���KYOTEN_ITEM_TBL����COL_NAME��select����

	// del 2009/08/27 Y.Matsukawa [
	//	$sql = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	//	$sql .= "WHERE CORP_ID = '$cid' AND ";
	// del 2009/08/27 Y.Matsukawa ]
	// add 2009/08/27 Y.Matsukawa [
	$sql0 = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	$sql0 .= "WHERE CORP_ID = '$cid' ";
	// add 2009/08/27 Y.Matsukawa ]

	switch ( $type ) {
		// PC�ܺ�
		case "1":
			$buf = "SYOUSAI_KBN";
			break;
		// ����
		case "2":
			$buf = "INSATSU_KBN";
			break;
		// �ե�����
		case "3":
			$buf = "FUKIDASI_KBN";
			break;
		// ���Ӿܺ�
		//default:		mod 2011/03/10 Y.Matsukawa
		case "4":
			$buf = "M_SYOUSAI_KBN";
			break;
		// add 2011/03/10 Y.Matsukawa [
		// ���ޡ��ȥե���ܺ�
		case "5":
			$buf = "OPT_06";
			break;
		// add 2011/03/10 Y.Matsukawa ]
	}
	
	// ɽ������
	//$sql .= "$buf = '1' ";		mod 2009/08/27 Y.Matsukawa
	$sql = $sql0." AND $buf = '1' ";
	$sql .= "ORDER BY DISP_NUM ";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$dba->free($stmt);

	// add 2009/08/27 Y.Matsukawa [
	if ($type == 1 || $type == 2 || $type == 3) {		// PC�ܺ١��������᤭�Ф�
		//PC�̼ܥ����
		$sql = $sql0." AND OPT_03 = 'P'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			return 9;
		}
		// mod 2015/05/22 H.Osamoto [
		//	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		//		$retdata[] = $data;
		//	else
		//		$retdata[] = null;
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			$data["COL_NAME"] = "'@@KYOTEN_LEVEL@@:'||A.".$data["COL_NAME"];
			$retdata[] = $data;
		} else {
			$retdata[] = null;
		}
		// mod 2015/05/22 H.Osamoto ]
		$dba->free($stmt);
	}

	//���ӽ̼ܥ����
	if ($type == 4) {		// ���Ӿܺ�
		$sql = $sql0." AND OPT_03 = 'M'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			return 9;
		}
		// mod 2015/05/22 H.Osamoto [
		//	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		//		$retdata[] = $data;
		//	else
		//		$retdata[] = null;
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			$data["COL_NAME"] = "'@@KYOTEN_LEVEL@@:'||A.".$data["COL_NAME"];
			$retdata[] = $data;
		} else {
			$retdata[] = null;
		}
		// mod 2015/05/22 H.Osamoto ]
		$dba->free($stmt);
	}
	// add 2009/08/27 Y.Matsukawa ]

	//���ޥ۽̼ܥ����		add 2011/08/26 Y.Matsukawa
	if ($type == 5) {		// ���ޥ۾ܺ�
		$sql = $sql0." AND OPT_03 = 'S'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			return 9;
		}
		// mod 2015/05/22 H.Osamoto [
		//	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		//		$retdata[] = $data;
		//	else
		//		$retdata[] = null;
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			$data["COL_NAME"] = "'@@KYOTEN_LEVEL@@:'||A.".$data["COL_NAME"];
			$retdata[] = $data;
		} else {
			$retdata[] = null;
		}
		// mod 2015/05/22 H.Osamoto ]
		$dba->free($stmt);
	}

	$result = count($retdata);
	if ($result <= 0) {
		//$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa	del 2009/08/27 Y.Matsukawa
		return 1;	//������̥ǡ����ʤ�(���Ϥ�CID�˥ޥå�����ǡ������ʤ���� or ���Ϥ�CID�˥ޥå�����ǡ����Ϥ��뤬���ϤΥ����פ˥����å������äƤ��ʤ����)
	}
	//$dba->free($stmt);		del 2009/08/27 Y.Matsukawa
	return 0;
}

//function select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, &$retdata, &$err_msg ){		mod 2012/02/16 Y.Matsukawa
//function select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, &$retdata, &$err_msg, $jkn='' ){	mod 2013/08/05 N.Wada
function select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, &$retdata, &$err_msg, $jkn='', $immref=false ){
	//������������������롣
	//CORP_ID��KYOTEN_ID�򥭡��ˡ�
	//KYOTEN_TBL����LAT��LON��ICON_ID��$arr_col_name(�ֵ���̾�����ꡢ���ѹ��ܡ�)��
	//KYOTEN_GIF_TBL������������ơ��֥�η����K_GIF_NUM�ˡ�������NEW��������ɽ�����Ǥ��뤫��
	//�֤���
	//$arr_col_name�����ξ��ϡ��ֵ���̾�����ꡢ���ѹ��ܡפ��֤��ʤ���

	$sql  = "SELECT A.LAT, A.LON, A.ICON_ID, DECODE(B.INS_DT, NULL, '0', '1') AS K_GIF_NUM, ";

	//NEW��������ɽ���ե饰
	//  ����������λ������NULL�ξ�硧'0'
	//  SYSDATE�����������齪λ�������äƤ����硧'1'
	//  SYSDATE�����������齪λ�������äƤ��ʤ���硧'0'
	//  ��â�����㤨��SYSDATE��20070306�ǡ���������NULL����λ����20070305�ξ��ϡ�'0'��
	$sql .= "CASE ";
	$sql .= "WHEN A.DISP_NEW_S_DATE IS NULL AND A.DISP_NEW_E_DATE IS NULL THEN '0' ";
	$sql .= "WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "NVL(DISP_NEW_E_DATE, SYSDATE) THEN '1' ";
	$sql .= "ELSE '0' ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
		$first_flg = 0;
		foreach( $arr_col_name as $rowdata ) {
			if (is_array($rowdata)) {			// add 2009/08/27 Y.Matsukawa
				if ( $first_flg == 0 ) {
					// mod 2011/07/05 Y.Nakajima
					$sql .= ", A." . $rowdata['COL_NAME'];
					$first_flg = 1;
				} else {
					// mod 2011/07/05 Y.Nakajima
					// mod 2015/05/22 H.Osamoto [
					//	$sql .= "," .  " A." . $rowdata['COL_NAME'];
					if (preg_match('/@@KYOTEN_LEVEL@@/', $rowdata['COL_NAME'])) {
						$sql .= "," . $rowdata['COL_NAME'];
					} else {
						$sql .= "," .  " A." . $rowdata['COL_NAME'];
					}
					// mod 2015/05/22 H.Osamoto ]
				}
			// add 2009/08/27 Y.Matsukawa [
			} else {
				$sql .= ",null";
			// add 2009/08/27 Y.Matsukawa ]
			}
		}
		$sql .= " ";
	}

	// add 2012/01/27 K.Masuda [
	// �����աۤ���4���ܤϺǸ���ɲä����ΤȤ��롪�ʽ��ѹ��Բġ�
	$sql .= ",TO_CHAR(A.PUB_S_DATE,'yyyymmddhh24') AS PUB_S_DATE ";
	$sql .= ",TO_CHAR(A.PUB_E_DATE,'yyyymmddhh24') AS PUB_E_DATE ";
	$sql .= ",TO_CHAR(A.DISP_NEW_S_DATE,'yyyymmddhh24') AS DISP_NEW_S_DATE ";
	$sql .= ",TO_CHAR(A.DISP_NEW_E_DATE,'yyyymmddhh24') AS DISP_NEW_E_DATE ";
	// add 2012/01/27 K.Masuda ]
	//$sql .= "FROM KYOTEN_TBL A, KYOTEN_GIF_TBL B ";	mod 2013/08/05 N.Wada [
	if ( $immref ) {
		$sql .= "FROM IM_KYOTEN_TBL A, IM_KYOTEN_GIF_TBL B ";
	} else {
		$sql .= "FROM KYOTEN_TBL A, KYOTEN_GIF_TBL B ";
	}
	// mod 2013/08/05 N.Wada ]
	$sql .= "WHERE A.CORP_ID = B.CORP_ID(+) AND A.KYOTEN_ID = B.KYOTEN_ID(+) AND ";
	$sql .= "A.CORP_ID = '$cid' AND A.KYOTEN_ID = '$kid' ";
	$sql .= "AND NVL( A.PUB_E_DATE, SYSDATE ) >= SYSDATE";
	// add 2012/02/16 Y.Matsukawa [
	if ($jkn != "") {
		$sql .= " AND $jkn ";
	}
	// add 2012/02/16 Y.Matsukawa ]
	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dba->getRecInto( $stmt,$retdata,OCI_ASSOC);
	if ( $retdata == "" ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return	0;
}

// ����������ʣ���˥ơ��֥�ǡ�������
//function select_kyoten_img_tbl( &$dba , $cid , $kid , &$retdata , &$err_msg ) {	mod 2013/08/05 N.Wada
function select_kyoten_img_tbl( &$dba , $cid , $kid ,  &$retdata , &$err_msg , $immref=false ) {

	// add 2013/08/05 N.Wada [
	if ( $immref ) {
		$from = " FROM IM_KYOTEN_TBL A, IM_KYOTEN_IMG_TBL B ";
	} else {
		$from = " FROM KYOTEN_TBL A, KYOTEN_IMG_TBL B ";
	}
	// add 2013/08/05 N.Wada ]

	$sql = " SELECT B.IMG_NO "
		//.  " FROM KYOTEN_TBL A, "		mod 2013/08/05 N.Wada
		//.  " KYOTEN_IMG_TBL B "
		.  $from
		.  " WHERE A.CORP_ID = '$cid' "
		.  " AND A.KYOTEN_ID = '$kid' "
		.  " AND NVL(A.PUB_E_DATE, SYSDATE) >= SYSDATE "
		.  " AND A.CORP_ID = B.CORP_ID "
		.  " AND A.KYOTEN_ID = B.KYOTEN_ID "
		.  " AND B.GIF_DATA IS NOT NULL "
		.  " ORDER BY B.IMG_NO";
	$stmt	= null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;	//sqlExecute()���顼
	}
	$retdata = array();
	while ( $dba->getRecInto( $stmt , $data , OCI_ASSOC ) ) {
		$retdata[] = $data;
	}
	if ( count( $retdata ) <= 0 ) {
		$dba->free($stmt);
		return 1;	//������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return	0;
}
?>