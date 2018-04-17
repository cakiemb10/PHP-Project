<?php
/*========================================================*/
// 更新履歴
//   ・2007/07/11 Y.Matsukawa   検索結果なしの時にリソース解放していなかった
//   ・2007/09/14 Y.Matsukawa   サービス開始日前でもアプリ動作可能に
/*========================================================*/

function select_serv_date( &$dba, $cid, &$retdata, &$err_msg ){
	//CORP_IDをキーにKYOTEN_ITEM_TBLからCOL_NAMEをselectする

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
		return 9;   //sqlExecute()エラー
	}
	$retdata = array();
	if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata = $data;
	}
	$result = count ($retdata);
	if ( $result <= 0 ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

?>
