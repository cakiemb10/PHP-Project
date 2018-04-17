<?php
/*========================================================*/
// ファイル名：sql_collection_kyotenlist.inc
// 処理名：拠点リスト検索SQL実装
//
// 作成日：2007/01/12
// 作成者：H.Ueno
//
// 解説：kyotenlist.cgiのSQL実装部
//
// 更新履歴
// 2007/01/12 H.Ueno		新規作成
// 2007/03/20 Y.Matsukawa	ソート設定に従ったソート順で取得するよう修正
// 2007/07/11 Y.Matsukawa	検索結果なしの時にリソース解放していなかった
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2010/04/02 Y.Matsukawa	ソート項目指定時、第２ソートキーを拠点IDにする
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/12/15 Y.Matsukawa	メモリーエラー対応
// 2012/06/18 Y.Matsukawa	拠点ID（複数）指定検索
// 2013/08/05 N.Wada		即時反映対象企業対応
/*========================================================*/

/*==============================================*/
// select_col_name
//
// CORP_IDをキーにKYOTEN_ITEM_TBLからCOL_NAMEをselectする
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
		return 9;   //sqlExecute()エラー
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	// add 2009/09/04 Y.Matsukawa [
	$dba->free($stmt);

	//PC縮尺カラム
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

	//携帯縮尺カラム
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
		return 1;   //検索結果データなし
	}
	//$dba->free($stmt);		del 2009/09/04 Y.Matsukawa

	return  0;
}

/*==============================================*/
// select_sort_col_name
//
// CORP_IDをキーにKYOTEN_ITEM_TBLからSORT_KBN=1のCOL_NAMEをselectする
/*==============================================*/
function select_sort_col_name(&$dba, $cid, &$retdata, &$err_msg) {
	$sql = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	$sql .= "WHERE CORP_ID = '$cid' AND ";
	$sql .= "SORT_KBN = '1' ";
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

/*==============================================*/
// select_kyoten_list
//
// 拠点リストを取得する。
//  pos         取得開始位置
//  cnt         取得件数
//  hit_num     ヒット件数
/*==============================================*/
function select_kyoten_list(&$dba, $cid, $arr_col_name, $jkn, $arr_latlon, $sort_col_name, $pos, $cnt,
							$arr_kid,			// add 2012/06/18 Y.Matsukawa
							//&$hit_num, &$retdata, &$err_msg) {	mod 2013/08/05 N.Wada
							&$hit_num, &$retdata, &$err_msg, $immref=false) {

	$sql = "SELECT KYOTEN_ID, LAT, LON, ICON_ID, ";
	//NEWアイコン表示フラグ
	//  開始日、終了日共にNULLの場合：'0'
	//  SYSDATEが開始日から終了日に入っている場合：'1'
	//  SYSDATEが開始日から終了日に入っていない場合：'0'
	//  ※但し、例えばSYSDATEが20070306で、開始日がNULL、終了日が20070305の場合は、'0'。
	$sql .= "CASE ";
	$sql .= "WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0' ";
	$sql .= "WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "NVL(DISP_NEW_E_DATE, SYSDATE) THEN '1' ";
	$sql .= "ELSE '0' ";
	//$sql .= "END AS BFLG, ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//空ではない場合
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
	//	if ($jkn != "") {   //条件指定有りの場合
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
	if ($jkn != "") {   //条件指定有りの場合
		$sql_where .= "AND $jkn ";
	}
	// add 2012/06/18 Y.Matsukawa [
	// 拠点ID指定（複数）
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
	// 総ヒット件数取得
	$stmt = null;
	if (!$dba->sqlExecute($sql_count, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$hit_num = 0;
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['CNT'];
	}
	// add 2011/12/15 Y.Matsukawa ]

	// データ取得
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	// del 2011/12/15 Y.Matsukawa [
	//	$retdata_all = array();
	//	while($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
	//		$retdata_all[] = $data;
	//	}
	//	$hit_num = count($retdata_all);
	//	if ($hit_num <= 0) {
	//		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
	//		return 1;   //検索結果データなし
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
