<?php
/*========================================================*/
// 更新履歴
// 2013/02/20 H.osamoto		新規作成
// 2013/11/12 H.Osamoto		カスタマイズ条件テーブル名変更(TEST_JSON_TBL⇒APL_COND_TBL)
/*========================================================*/

// カスタマイズ条件を取得する
// CORP_IDをキーに、APL_COND_TBLからDATA(カスタマイズ絞込み条件)を返す。
// 空の場合は、KYOTEN_ITEM_TBLとKYOTEN_ITEM_VAL_TBLからデフォルトの絞込み条件を生成し返却する。
function select_cstm_cond_ptn( &$dba, $cid, &$retdata){

	$col_name = "DATA";
	
	$sql  = "SELECT ".$col_name." ";
	//	$sql .= "FROM TEST_JSON_TBL ";	mod 2013/11/12 H.Osamoto
	$sql .= "FROM APL_COND_TBL ";
	$sql .= "WHERE CORP_ID='".$cid."' ";

	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   // sqlExecute()エラー
	}
	$dba->getRecInto( $stmt,$data,OCI_ASSOC);
	$retdata = $data[$col_name];
	if ( $retdata == "" ) {
		$dba->free($stmt);
		return 1;   // 検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

// 絞込み条件のカラムを拠点データ項目名テーブルから取得
function select_cond_kyoten_item_tbl( &$dba, $cid, &$retdata ){
	
	$sql  = "SELECT case VAL_KBN when 'B' then 'F' when 'L' then 'L' else null end \"type\", ITEM_NAME \"text\", COL_NAME \"val\" ";
	$sql .= "FROM KYOTEN_ITEM_TBL ";
	$sql .= "WHERE CORP_ID='".$cid."' ";
	$sql .= "AND SRCH_KBN='S' ";
	$sql .= "ORDER BY DISP_NUM ";

	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   // sqlExecute()エラー
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[] = $data;
	}
	$hit_num = count ($retdata);
	if ( $hit_num <= 0 ) {
		$dba->free($stmt);
		return 1;   // 検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

// 絞込み条件のリストカラムの項目値を拠点データ項目値テーブルから取得
function select_cond_kyoten_item_val_tbl( &$dba, $cid, $col, &$retdata ){
	
	$sql  = "SELECT ITEM_VAL_NAME \"text\", COL_NAME || ':' || ITEM_VAL \"val\" ";
	$sql .= "FROM KYOTEN_ITEM_VAL_TBL ";
	$sql .= "WHERE CORP_ID='".$cid."' ";
	$sql .= "AND COL_NAME='".$col."' ";
	$sql .= "ORDER BY ITEM_VAL ";

	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   // sqlExecute()エラー
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[] = $data;
	}
	$hit_num = count ($retdata);
	if ( $hit_num <= 0 ) {
		$dba->free($stmt);
		return 1;   // 検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}
?>
