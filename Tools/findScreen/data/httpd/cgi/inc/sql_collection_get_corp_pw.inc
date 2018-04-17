<?php
/*========================================================*/
// 更新履歴
//   ・2008/07/01 Y.Matsukawa   新規作成
/*========================================================*/

function select_corp_pw(&$dba, $cid, &$retdata, &$err_msg){

	$sql = "select PASSWD";
	$sql .= " from EMAP_CORP_MST ";
	$sql .= " where CORP_ID = '$cid'";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	$retdata = array();
	if ($dba->getRecInto($stmt,$data,OCI_ASSOC)) {
		$retdata = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);

	return  0;
}

?>
