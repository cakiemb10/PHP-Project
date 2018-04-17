<?php
/*========================================================*/
// ��������
// 2013/02/20 H.osamoto		��������
// 2013/11/12 H.Osamoto		�������ޥ������ơ��֥�̾�ѹ�(TEST_JSON_TBL��APL_COND_TBL)
/*========================================================*/

// �������ޥ��������������
// CORP_ID�򥭡��ˡ�APL_COND_TBL����DATA(�������ޥ����ʹ��߾��)���֤���
// ���ξ��ϡ�KYOTEN_ITEM_TBL��KYOTEN_ITEM_VAL_TBL����ǥե���Ȥιʹ��߾����������ֵѤ��롣
function select_cstm_cond_ptn( &$dba, $cid, &$retdata){

	$col_name = "DATA";
	
	$sql  = "SELECT ".$col_name." ";
	//	$sql .= "FROM TEST_JSON_TBL ";	mod 2013/11/12 H.Osamoto
	$sql .= "FROM APL_COND_TBL ";
	$sql .= "WHERE CORP_ID='".$cid."' ";

	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   // sqlExecute()���顼
	}
	$dba->getRecInto( $stmt,$data,OCI_ASSOC);
	$retdata = $data[$col_name];
	if ( $retdata == "" ) {
		$dba->free($stmt);
		return 1;   // ������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

// �ʹ��߾��Υ���������ǡ�������̾�ơ��֥뤫�����
function select_cond_kyoten_item_tbl( &$dba, $cid, &$retdata ){
	
	$sql  = "SELECT case VAL_KBN when 'B' then 'F' when 'L' then 'L' else null end \"type\", ITEM_NAME \"text\", COL_NAME \"val\" ";
	$sql .= "FROM KYOTEN_ITEM_TBL ";
	$sql .= "WHERE CORP_ID='".$cid."' ";
	$sql .= "AND SRCH_KBN='S' ";
	$sql .= "ORDER BY DISP_NUM ";

	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   // sqlExecute()���顼
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[] = $data;
	}
	$hit_num = count ($retdata);
	if ( $hit_num <= 0 ) {
		$dba->free($stmt);
		return 1;   // ������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

// �ʹ��߾��Υꥹ�ȥ����ι����ͤ�����ǡ��������ͥơ��֥뤫�����
function select_cond_kyoten_item_val_tbl( &$dba, $cid, $col, &$retdata ){
	
	$sql  = "SELECT ITEM_VAL_NAME \"text\", COL_NAME || ':' || ITEM_VAL \"val\" ";
	$sql .= "FROM KYOTEN_ITEM_VAL_TBL ";
	$sql .= "WHERE CORP_ID='".$cid."' ";
	$sql .= "AND COL_NAME='".$col."' ";
	$sql .= "ORDER BY ITEM_VAL ";

	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   // sqlExecute()���顼
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[] = $data;
	}
	$hit_num = count ($retdata);
	if ( $hit_num <= 0 ) {
		$dba->free($stmt);
		return 1;   // ������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}
?>