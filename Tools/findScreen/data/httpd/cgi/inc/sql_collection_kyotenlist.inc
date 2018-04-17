<?php
/*========================================================*/
// �ե�����̾��sql_collection_kyotenlist.inc
// ����̾�������ꥹ�ȸ���SQL����
//
// ��������2007/01/12
// �����ԡ�H.Ueno
//
// ���⡧kyotenlist.cgi��SQL������
//
// ��������
// 2007/01/12 H.Ueno		��������
// 2007/03/20 Y.Matsukawa	����������˽��ä������Ƚ�Ǽ�������褦����
// 2007/07/11 Y.Matsukawa	������̤ʤ��λ��˥꥽�����������Ƥ��ʤ��ä�
// 2009/09/04 Y.Matsukawa	�����̼�
// 2010/04/02 Y.Matsukawa	�����ȹ��ܻ�������裲�����ȥ��������ID�ˤ���
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/12/15 Y.Matsukawa	���꡼���顼�б�
// 2012/06/18 Y.Matsukawa	����ID��ʣ���˻��긡��
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
/*========================================================*/

/*==============================================*/
// select_col_name
//
// CORP_ID�򥭡���KYOTEN_ITEM_TBL����COL_NAME��select����
/*==============================================*/
function select_col_name(&$dba, $cid, &$retdata, &$err_msg) {
	// del 2009/09/04 Y.Matsukawa [
	//	$sql = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	//	$sql .= "WHERE CORP_ID = '$cid' AND ";
	// del 2009/09/04 Y.Matsukawa [
	// add 2009/09/04 Y.Matsukawa [
	$sql0 = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	$sql0 .= "WHERE CORP_ID = '$cid' AND ";
	$sql = $sql0;
	// add 2009/09/04 Y.Matsukawa ]
	$sql .= "LIST_KBN = '1' ";
	$sql .= "ORDER BY DISP_NUM ";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	// add 2009/09/04 Y.Matsukawa [
	$dba->free($stmt);

	//PC�̼ܥ����
	$sql = $sql0." OPT_03 = 'P'";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		$retdata[] = $data;
	else
		$retdata[] = array('COL_NAME'=>'null PLVL');
	$dba->free($stmt);

	//���ӽ̼ܥ����
	$sql = $sql0." OPT_03 = 'M'";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		$retdata[] = $data;
	else
		$retdata[] = array('COL_NAME'=>'null MLVL');
	$dba->free($stmt);
	// add 2009/09/04 Y.Matsukawa ]

	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //������̥ǡ����ʤ�
	}
	//$dba->free($stmt);		del 2009/09/04 Y.Matsukawa

	return  0;
}

/*==============================================*/
// select_sort_col_name
//
// CORP_ID�򥭡���KYOTEN_ITEM_TBL����SORT_KBN=1��COL_NAME��select����
/*==============================================*/
function select_sort_col_name(&$dba, $cid, &$retdata, &$err_msg) {
	$sql = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	$sql .= "WHERE CORP_ID = '$cid' AND ";
	$sql .= "SORT_KBN = '1' ";
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

/*==============================================*/
// select_kyoten_list
//
// �����ꥹ�Ȥ�������롣
//  pos         �������ϰ���
//  cnt         �������
//  hit_num     �ҥåȷ��
/*==============================================*/
function select_kyoten_list(&$dba, $cid, $arr_col_name, $jkn, $arr_latlon, $sort_col_name, $pos, $cnt,
							$arr_kid,			// add 2012/06/18 Y.Matsukawa
							//&$hit_num, &$retdata, &$err_msg) {	mod 2013/08/05 N.Wada
							&$hit_num, &$retdata, &$err_msg, $immref=false) {

	$sql = "SELECT KYOTEN_ID, LAT, LON, ICON_ID, ";
	//NEW��������ɽ���ե饰
	//  ����������λ������NULL�ξ�硧'0'
	//  SYSDATE�����������齪λ�������äƤ����硧'1'
	//  SYSDATE�����������齪λ�������äƤ��ʤ���硧'0'
	//  ��â�����㤨��SYSDATE��20070306�ǡ���������NULL����λ����20070305�ξ��ϡ�'0'��
	$sql .= "CASE ";
	$sql .= "WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0' ";
	$sql .= "WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "NVL(DISP_NEW_E_DATE, SYSDATE) THEN '1' ";
	$sql .= "ELSE '0' ";
	//$sql .= "END AS BFLG, ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
		//		$first_flg = 0;
		foreach($arr_col_name as $rowdata) {
			//			if ($first_flg == 0) {
			//				$sql .= $rowdata[COL_NAME];
			//				$first_flg = 1;
			//			} else {
			//				$sql .= ", " . $rowdata[COL_NAME];
			//			}
			// mod 2011/07/05 Y.Nakajima
			$sql .= ", " . $rowdata['COL_NAME'];
		}
	}
	// del 2011/12/15 Y.Matsukawa [
	//	$sql .= " ";
	//	$sql .= "FROM KYOTEN_TBL ";
	//	$sql .= "WHERE CORP_ID = '$cid' ";
	//	if ($jkn != "") {   //������ͭ��ξ��
	//		$sql .= "AND $jkn ";
	//	}
	//	$sql .= "AND NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE ";
	//	$num = count($arr_latlon);
	//	if ($num > 0) {
	//		$sql .= "AND LAT >= '$arr_latlon[0]' AND LAT <= '$arr_latlon[2]' ";
	//		$sql .= "AND LON >= '$arr_latlon[1]' AND LON <= '$arr_latlon[3]' ";
	//	}
	// del 2011/12/15 Y.Matsukawa ]
	// add 2011/12/15 Y.Matsukawa [
	//$sql_where = "FROM KYOTEN_TBL ";	mod 2013/08/05 N.Wada [
	if ( $immref ) {
		$sql_where = "FROM IM_KYOTEN_TBL ";
	} else {
		$sql_where = "FROM KYOTEN_TBL ";
	}
	// mod 2013/08/05 N.Wada ]
	$sql_where .= "WHERE CORP_ID = '$cid' ";
	if ($jkn != "") {   //������ͭ��ξ��
		$sql_where .= "AND $jkn ";
	}
	// add 2012/06/18 Y.Matsukawa [
	// ����ID�����ʣ����
	if (is_array($arr_kid) && count($arr_kid)) {
		foreach ($arr_kid as $i => $kid) {
			$arr_kid[$i] = "'".$kid."'";
		}
		if (count($arr_kid) == 1) {
			$sql_where .= "AND KYOTEN_ID = ".$arr_kid[0]." ";
		} else {
			$sql_where .= "AND KYOTEN_ID IN (".implode(',', $arr_kid).") ";
		}
	}
	// add 2012/06/18 Y.Matsukawa ]
	$sql_where .= "AND NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE ";
	$num = count($arr_latlon);
	if ($num > 0) {
		$sql_where .= "AND LAT >= '$arr_latlon[0]' AND LAT <= '$arr_latlon[2]' ";
		$sql_where .= "AND LON >= '$arr_latlon[1]' AND LON <= '$arr_latlon[3]' ";
	}
	$sql .= " ".$sql_where;
	$sql_count = "select count(*) CNT ".$sql_where;
	// add 2011/12/15 Y.Matsukawa ]
	//$sql .= "ORDER BY KYOTEN_ID";
	if ($sort_col_name) {
		$sql .= "ORDER BY $sort_col_name";
		$sql .= ",KYOTEN_ID";		// add 2010/04/02 Y.Matsukawa
	} else {
		$sql .= "ORDER BY KYOTEN_ID";
	}
	// add 2011/12/15 Y.Matsukawa [
	$sql = "SELECT * FROM ("
			."SELECT S.*, ROWNUM RN FROM ($sql) S"
			.") "
			."WHERE RN >= $pos AND RN <= ".($pos + $cnt -1)
	;
	// add 2011/12/15 Y.Matsukawa ]

	// add 2011/12/15 Y.Matsukawa [
	// ���ҥåȷ������
	$stmt = null;
	if (!$dba->sqlExecute($sql_count, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$hit_num = 0;
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['CNT'];
	}
	// add 2011/12/15 Y.Matsukawa ]

	// �ǡ�������
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	// del 2011/12/15 Y.Matsukawa [
	//	$retdata_all = array();
	//	while($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
	//		$retdata_all[] = $data;
	//	}
	//	$hit_num = count($retdata_all);
	//	if ($hit_num <= 0) {
	//		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
	//		return 1;   //������̥ǡ����ʤ�
	//	}
	//	$dba->free($stmt);
	//	$retdata = array();
	//	for ($ctr=$pos; $ctr<=$hit_num; $ctr++) {
	//		$retdata[] = $retdata_all[$ctr-1];
	//		if ($ctr == ($pos + ($cnt-1))) {
	//			break;
	//		}
	//	}
	// del 2011/12/15 Y.Matsukawa ]
	// add 2011/12/15 Y.Matsukawa [
	$retdata = array();
	while($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	// add 2011/12/15 Y.Matsukawa ]

	return  0;
}
?>