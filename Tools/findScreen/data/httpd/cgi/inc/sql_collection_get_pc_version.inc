<?php
/*========================================================*/
// ��������
//   ��2012/07/25 H.Osamoto		��������
/*========================================================*/

function select_pc_version(&$dba, $cid, &$retdata, &$err_msg){

	$sql = "select VALUE";
	$sql .= " from EMAP_PARM_TBL ";
	$sql .= " where CORP_ID = '$cid'";
	$sql .= " and KBN = 'PC_VER'";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	$retdata = array();
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);

	// ������NULL�ξ��ϡָ�����̥ǡ����ʤ��פȤ���
	if (!strlen($retdata['VALUE'])) {
		return 1;   //������̥ǡ����ʤ�
	}
	
	return  0;
}

?>