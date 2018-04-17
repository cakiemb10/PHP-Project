<?php
/*========================================================*/
// �ե�����̾��sql_collection_emap_conf.inc
// ����̾������������SQL����
//
// ��������2007/01/12
// �����ԡ�H.Ueno
//
// ���⡧emap_conf.cgi��SQL������
//
// ��������
// 2007/01/12 H.Ueno		��������
// 2007/03/20 Y.Matsukawa	�ơ��֥륫���������ɲ�
// 2009/07/15 Y.Matsukawa	AD Maplink�б�
// 2011/05/24 Y.Matsukawa	���ޡ��ȥե������б�
// 2013/02/13 K.Masuda		EMAP_CORP_MST�ǡ��������Υ��ޥ۶�ʬ����
// 2013/07/19 T.Sasaki		������ʣ���˲����б�
/*========================================================*/

/*==============================================*/
// get_colnames
//
// �ơ��֥륫������
/*==============================================*/
function get_colnames(&$dba, $table_name, &$retdata){
	$sql = "SELECT COLUMN_NAME FROM USER_TAB_COLUMNS ";
	$sql .= "WHERE TABLE_NAME = '$table_name' ";
	$sql .= "ORDER BY COLUMN_ID";
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$dbdata[] = $data["COLUMN_NAME"];
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata;
	
	return  0;
}

/*==============================================*/
// select_emap_corp_mst
//
// EMAP_CORP_MST�ǡ�������
/*==============================================*/
function select_emap_corp_mst(&$dba, $corp_id, &$retdata){
	$sql = "SELECT * FROM EMAP_CORP_MST ";
	$sql .= "WHERE CORP_ID = '$corp_id'";
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$dbdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata[0];
	
	// EMAP_PARM_TBL�������		add 2011/05/24 Y.Matsukawa
	$sql = "select * from EMAP_PARM_TBL ";
	$sql .= "where CORP_ID = '$corp_id'";
	$sql .= "and KBN = 'S_EMAP_KBN'";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	$dbdata = array();
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		//$retdata['S_EMAP_KBN'] = $data['S_EMAP_KBN'];	// mod 2013/02/13 K.Masuda
		$retdata['S_EMAP_KBN'] = $data['VALUE'];
	}
	$dba->free($stmt);
	
	return  0;
}

/*==============================================*/
// select_emap_pc_conf_tbl
//
// EMAP_PC_CONF_TBL�ǡ�������
/*==============================================*/
function select_emap_pc_conf_tbl(&$dba, $corp_id, &$retdata){
	$sql = "SELECT * FROM EMAP_PC_CONF_TBL ";
	$sql .= "WHERE CORP_ID = '$corp_id'";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt,$data,OCI_ASSOC)) {
		$dbdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata[0];
	
	return  0;
}

/*==============================================*/
// select_emap_m_conf_tbl
//
// EMAP_M_CONF_TBL�ǡ�������
/*==============================================*/
function select_emap_m_conf_tbl(&$dba, $corp_id, &$retdata){
	$sql = "SELECT * FROM EMAP_M_CONF_TBL ";
	$sql .= "WHERE CORP_ID = '$corp_id'";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt,$data,OCI_ASSOC)) {
		$dbdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata[0];
	
	return  0;
}

// add 2011/05/24 Y.Matsukawa
/*==============================================*/
// select_emap_smt_conf_tbl
//
// EMAP_SMT_CONF_TBL�ǡ�������
/*==============================================*/
function select_emap_smt_conf_tbl(&$dba, $corp_id, &$retdata){
	$sql = "SELECT * FROM EMAP_SMT_CONF_TBL ";
	$sql .= "WHERE CORP_ID = '$corp_id'";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt,$data,OCI_ASSOC)) {
		$dbdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata[0];
	
	return  0;
}

/*==============================================*/
// select_kyoten_item_tbl
//
// KYOTEN_ITEM_TBL�ǡ�������
/*==============================================*/
function select_kyoten_item_tbl(&$dba, $corp_id, &$retdata){
	$sql = "SELECT * FROM KYOTEN_ITEM_TBL ";
	$sql .= "WHERE CORP_ID = '$corp_id' ";
	$sql .= "ORDER BY DISP_NUM";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$dbdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata;
	
	return  0;
}

/*==============================================*/
// select_kyoten_item_val_tbl
//
// KYOTEN_ITEM_VAL_TBL�ǡ�������
/*==============================================*/
function select_kyoten_item_val_tbl(&$dba, $corp_id, $col_name, &$retdata){
	$sql = "SELECT * FROM KYOTEN_ITEM_VAL_TBL ";
	$sql .= "WHERE CORP_ID = '$corp_id' AND ";
	$sql .= "COL_NAME = '$col_name'";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$dbdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$dbdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($dbdata);
	if ($result <= 0) {
		return 1;   //������̥ǡ����ʤ�
	}
	$retdata = array();
	$retdata = $dbdata;
	
	return  0;
}

// add 2009/07/15 Y.Matsukawa
/*==============================================*/
// select_emap_parm_tbl
//
// EMAP_PARM_TBL�ǡ�������
/*==============================================*/
function select_emap_parm_tbl(&$dba, $corp_id, &$retdata){
	$sql = "SELECT KBN, VALUE FROM EMAP_PARM_TBL ";
	$sql .= "WHERE CORP_ID = '$corp_id'";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt,$data,OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($retdata);
	if ($result <= 0) {
		return 1;	//������̥ǡ����ʤ�
	}
	return 0;
}

// add 2013/07/11 T.Sasaki
/*==============================================*/
// select_kyoten_img_def_tbl
//
// KYOTEN_IMG_DEF_TBL�ǡ�������
/*==============================================*/
function select_kyoten_img_def_tbl( &$dba , $corp_id , &$retdata ) {
	$sql = "SELECT IMG_NO, IMG_NAME "
		. " FROM KYOTEN_IMG_DEF_TBL "
		. " WHERE CORP_ID = '$corp_id' "
		. " ORDER BY CORP_ID ";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;	//sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt,$data,OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$dba->free($stmt);
	$result = count($retdata);
	if ($result <= 0) {
		return 1;	//������̥ǡ����ʤ�
	}
	return 0;
}

?>