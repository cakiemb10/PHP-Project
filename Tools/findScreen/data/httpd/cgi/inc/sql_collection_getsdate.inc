<?php
/*========================================================*/
// ��������
//   ��2007/07/11 Y.Matsukawa   ������̤ʤ��λ��˥꥽�����������Ƥ��ʤ��ä�
//   ��2007/09/14 Y.Matsukawa   �����ӥ����������Ǥ⥢�ץ�ư���ǽ��
/*========================================================*/

function select_serv_date( &$dba, $cid, &$retdata, &$err_msg ){
	//CORP_ID�򥭡���KYOTEN_ITEM_TBL����COL_NAME��select����

	$sql    =   "SELECT ";
	//$sql    .=  "CASE WHEN TRUNC(SYSDATE) BETWEEN S_DATE AND E_DATE ";	2007/09/14 mod Y.Matsukawa
	$sql    .=  "CASE WHEN SYSDATE <= E_DATE ";
	$sql    .=  "THEN '1' ELSE '0' END AS SFLG, ";
	$sql    .=  "       TO_CHAR(S_DATE,'YYYYMMDD') AS S_DATE,";
	$sql    .=  "       TO_CHAR(E_DATE,'YYYYMMDD') AS E_DATE ";
	$sql    .=  "FROM EMAP_CORP_MST ";
	$sql    .=  "WHERE CORP_ID = '$cid'";

	$stmt   = null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata = $data;
	}
	$result = count ($retdata);
	if ( $result <= 0 ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

?>