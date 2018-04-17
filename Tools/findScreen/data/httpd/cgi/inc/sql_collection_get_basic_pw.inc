<?php
/*========================================================*/
// 更新履歴
//   ・2008/07/24 Y.Matsukawa	新規作成
/*========================================================*/

function select_basic_pw(&$dba, $cid, &$retdata, &$err_msg){

	$sql = "select VALUE";
	$sql .= " from EMAP_PARM_TBL ";
	$sql .= " where CORP_ID = '$cid'";
	$sql .= " and KBN = 'BASICPW'";
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
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);

	// 万が一NULLの場合は「検索結果データなし」とする
	if (!strlen($retdata['VALUE'])) {
		return 1;   //検索結果データなし
	}
	
	return  0;
}

?>
