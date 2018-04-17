<?php
/*========================================================*/
// 拠点CSVアップロード（分割処理）ワークテーブルI/O
//
// 更新履歴
//   ・2012/05/31 H.Osamoto   新規作成
//   ・2013/03/18 H.Osamoto   店渡しのみカラム追加
/*========================================================*/

// ワークデータ（CLOB）一括登録
function hsearch_ins_all(&$dba, $batch_id, &$file_obj_arr) {
	// LOBロケータの初期化
	$lob = oci_new_descriptor($dba->conn, OCI_D_LOB);
	// SQL作成
	$sql = "insert into HSEARCH_DATA_TBL"
	. " (BATCH_ID, SEQNO, FILE_OBJ)"
	. " values(:BATCH_ID, :SEQNO, EMPTY_CLOB())"
	. " returning FILE_OBJ into :FILE_OBJ"
	;
	$stmt = OCIParse($dba->conn, $sql);
	OCIBindByName($stmt, ":BATCH_ID",   $batch_id);
	OCIBindByName($stmt, ":SEQNO",      $seqno, 8);
	OCIBindByName($stmt, ":FILE_OBJ",   $lob, -1, OCI_B_CLOB);
	$seqno = 0;
	foreach ($file_obj_arr as $i=>$file_obj) {
		$seqno++;
		// 実行
		OCIExecute($stmt, OCI_DEFAULT);
		// CLOBへの格納
		$file_obj_c = base64_encode(serialize($file_obj));
		if ($lob->save($file_obj_c)) {
		} else {
			OCIFreeStatement($stmt);
			$dba->close();
			return false;
		}
	}
	OCICommit($dba->conn);
	OCIFreeStatement($stmt);
	return true;
}

// ワークデータ（CLOB）取得
function hsearch_work_read(&$dba, $batch_id, $seqno, &$file_obj) {

	$CHUNK = 30000;
	$file_obj_c = '';
	$file_obj = array();
	$totalsize = 0;

	$sql = "declare v_clob_data clob;";
	$sql .= " begin";
	$sql .= " SELECT FILE_OBJ into v_clob_data from HSEARCH_DATA_TBL";
	$sql .= " WHERE BATCH_ID = :bid";
	$sql .= " and SEQNO = :sno;";
	$sql .= " :totalsize := dbms_lob.getlength(v_clob_data);";
	$sql .= " dbms_lob.read(v_clob_data, :len, :pos, :obj);";
	$sql .= " end;";

	$lob = oci_new_descriptor($dba->conn, OCI_D_LOB);
	$stmt = oci_parse($dba->conn, $sql);

	oci_bind_by_name($stmt, ":bid", $batch_id);
	oci_bind_by_name($stmt, ":sno", $seqno);
	oci_bind_by_name($stmt, ":len", $CHUNK);
	oci_bind_by_name($stmt, ":obj", $OBJ, $CHUNK);
	oci_bind_by_name($stmt, ":pos", $POS, 10);
	oci_bind_by_name($stmt, ":totalsize", $totalsize, 20);

	$POS = 1;
	$SIZE = 0;
	do {
		@oci_execute($stmt, OCI_DEFAULT);
		if (!$totalsize) break;
		$file_obj_c .= $OBJ;
		$SIZE += strlen($OBJ);
		if ($SIZE >= $totalsize) break;
		$POS_W = $POS;
		$POS = $POS_W + $CHUNK;
	} while ($SIZE < $totalsize);

	oci_free_statement($stmt);
	if ($file_obj_c) {
		$file_obj = unserialize(base64_decode($file_obj_c));
	}
	return true;
}

// 検索結果データ一括登録
function hsearch_result_ins(&$dba, $batch_id, $seqno, &$resultlist, $shop_cnt) {

	// SQL作成
	$sql  = "insert into HSEARCH_RSLT_TBL";
	$sql .= " (BATCH_ID, SEQNO, LINE_NO, ERR_CODE, ERR_MSG, NO,";
	//	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, SHOP_DIST, MATCH_LVL";		mod 2013/03/18 H.Osamoto
	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, SHOP_DIST, SHOP_SMSFLG, MATCH_LVL";
	$sql .= "  ,  NSHOP_DIST20";		// add 2014/03/26 H.Osamoto
	
	for ($i=1; $i <= $shop_cnt; $i++) {
		$k = $i + 20;	// add 2014/03/26 H.Osamoto
		//	$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i;		mod 2013/03/18 H.Osamoto
		//	$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i;		mod 2014/03/26 H.Osamoto
		$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i.",NSHOP_DIST".$k;
	}
	$sql .= ")";
	$sql .= " values";
	$sql .= " (:BATCH_ID, :SEQNO, :LINE_NO, :ERR_CODE, :ERR_MSG, :NO,";
	//	$sql .= "  :ADDR, :SHOP_NO, :SHOP_NAME, :SHOP_SAKE, :SHOP_DIST, :MATCH_LVL";		mod 2013/03/18 H.Osamoto
	$sql .= "  :ADDR, :SHOP_NO, :SHOP_NAME, :SHOP_SAKE, :SHOP_DIST, :SHOP_SMSFLG, :MATCH_LVL";
	$sql .= ",  :NSHOP_DIST20";		// add 2014/03/26 H.Osamoto
	for ($i=1; $i <= $shop_cnt; $i++) {
		$k = $i + 20;	// add 2014/03/26 H.Osamoto
		//	$sql .= ",    :NSHOP_NO".$i.", :NSHOP_NAME".$i.", :NSHOP_SAKE".$i.", :NSHOP_DIST".$i;		mod 2013/03/18 H.Osamoto
		//	$sql .= ",    :NSHOP_NO".$i.", :NSHOP_NAME".$i.", :NSHOP_SAKE".$i.", :NSHOP_DIST".$i.", :NSHOP_SMSFLG".$i;		mod 2014/03/26 H.Osamoto
		$sql .= ",    :NSHOP_NO".$i.", :NSHOP_NAME".$i.", :NSHOP_SAKE".$i.", :NSHOP_DIST".$i.", :NSHOP_SMSFLG".$i.", :NSHOP_DIST".$k;
	}
	$sql .= ")";

	$stmt = oci_parse($dba->conn, $sql);

	oci_bind_by_name($stmt, ":BATCH_ID",    $batch_id);
	oci_bind_by_name($stmt, ":SEQNO",       $seqno);
	oci_bind_by_name($stmt, ":LINE_NO",     $line_no,     15);
	oci_bind_by_name($stmt, ":ERR_CODE",    $err_code,    15);
	oci_bind_by_name($stmt, ":ERR_MSG",     $err_msg,     256);
	oci_bind_by_name($stmt, ":NO",          $no,          30);
	oci_bind_by_name($stmt, ":ADDR",        $addr,        200);
	oci_bind_by_name($stmt, ":SHOP_NO",     $shop_no,     15);
	oci_bind_by_name($stmt, ":SHOP_NAME",   $shop_name,   128);
	oci_bind_by_name($stmt, ":SHOP_SAKE",   $shop_sake,   15);
	oci_bind_by_name($stmt, ":SHOP_DIST",   $shop_dist,   15);
	oci_bind_by_name($stmt, ":SHOP_SMSFLG", $shop_smsflg, 15);		// add 2013/03/18 H.Osamoto
	oci_bind_by_name($stmt, ":MATCH_LVL",   $match_lvl,   10);
	oci_bind_by_name($stmt, ":NSHOP_DIST20",$shop_delidist,   15);	//add 2014/03/26 H.Osamoto
	
	for ($i=1; $i <= $shop_cnt; $i++) {
		$k = $i + 20;	// add 2014/03/26 H.Osamoto
		$nshop_no_name = "nshop_no".$i;
		$nshop_name_name = "nshop_name".$i;
		$nshop_sake_name = "nshop_sake".$i;
		$nshop_dist_name = "nshop_dist".$i;
		$nshop_smsflg_name = "nshop_smsflg".$i;		// add 2013/03/18 H.Osamoto
		$nshop_delidist = "nshop_delidist".$i;		// add 2014/03/26 H.Osamoto
		oci_bind_by_name($stmt, ":NSHOP_NO".$i,   $$nshop_no_name,   15);
		oci_bind_by_name($stmt, ":NSHOP_NAME".$i, $$nshop_name_name, 128);
		oci_bind_by_name($stmt, ":NSHOP_SAKE".$i, $$nshop_sake_name, 15);
		oci_bind_by_name($stmt, ":NSHOP_DIST".$i, $$nshop_dist_name, 15);
		oci_bind_by_name($stmt, ":NSHOP_SMSFLG".$i, $$nshop_smsflg_name, 15);		// add 2013/03/18 H.Osamoto
		oci_bind_by_name($stmt, ":NSHOP_DIST".$k, $$nshop_delidist, 15);		// add 2014/03/26 H.Osamoto
	}

	foreach ($resultlist as $cnt=>$result) {
		$line_no		= $result["line_no"];
		$err_code		= $result["err_code"];
		$err_msg		= $result["err_msg"];
		$no				= $result["no"];
		$addr			= $result["addr"];
		$shop_no		= $result["shop_no"];
		$shop_name		= $result["shop_name"];
		$shop_sake		= $result["shop_sake"];
		$shop_dist		= $result["shop_dist"];
		$shop_smsflg	= $result["shop_smsflg"];		// add 2013/03/18 H.Osamoto
		$match_lvl		= $result["match_lvl"];
		$shop_delidist	= $result["shop_delidist"];		// add 2014/03/26 H.Osamoto
		for ($j=1; $j <= $shop_cnt; $j++) {
			$nshop_no_name = "nshop_no".$j;
			$nshop_name_name = "nshop_name".$j;
			$nshop_sake_name = "nshop_sake".$j;
			$nshop_dist_name = "nshop_dist".$j;
			$nshop_smsflg_name = "nshop_smsflg".$j;		// add 2013/03/18 H.Osamoto
			$nshop_delidist = "nshop_delidist".$j;		// add 2014/03/26 H.Osamoto
			
			$$nshop_no_name		= $result["nshop_no".$j];
			$$nshop_name_name	= $result["nshop_name".$j];
			$$nshop_sake_name	= $result["nshop_sake".$j];
			$$nshop_dist_name	= $result["nshop_dist".$j];
			$$nshop_smsflg_name	= $result["nshop_smsflg".$j];		// add 2013/03/18 H.Osamoto
			$$nshop_delidist	= $result["nshop_delidist".$j];		// add 2014/03/26 H.Osamoto
		}

		// 実行
		if (!oci_execute($stmt, OCI_DEFAULT)) {
			$e = oci_error($stmt);
			oci_rollback($dba->conn);
			oci_free_statement($stmt);
			return false;
		}
	}

	oci_commit($dba->conn);
	oci_free_statement($stmt);
	return true;
}

// 検索結果データ確認
function hsearch_result_check(&$dba, $batch_id, $seqno) {

	$sql .= "select COUNT(LINE_NO) as CNT from HSEARCH_RSLT_TBL"
	. " where BATCH_ID = '{$batch_id}'"
	. "   and SEQNO    = '{$seqno}'"
	;

	$stmt = oci_parse($dba->conn, $sql);

	@oci_execute($stmt, OCI_DEFAULT);

	if (!$dba->getRecInto($stmt, $data, OCI_ASSOC)) return false;
	if ($data['CNT'] == 0) return false;

	oci_free_statement($stmt);

	return true;
}

// 検索結果データ取得
function hsearch_result_read(&$dba, $batch_id, &$result_list, $shop_cnt) {

	$sql  = "select * from (";
	$sql .= "  select ";
	$sql .= "  SEQNO, LINE_NO, ERR_CODE, ERR_MSG, NO,";
	//	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, SHOP_DIST, MATCH_LVL";		mod 2013/03/18 H.Osamoto
	//	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, SHOP_DIST, SHOP_SMSFLG, MATCH_LVL";		mod 2014/03/26 H.Osamoto
	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, NSHOP_DIST20, SHOP_DIST, SHOP_SMSFLG, MATCH_LVL";
	for ($i=1; $i <= $shop_cnt; $i++) {
		$k = $i + 20;	// add 2014/03/26 H.Osamoto
		//	$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i;		mod 2013/03/18 H.Osamoto
		//	$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i;
		//	$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i;		mod 2014/03/26 H.Osamoto
		$sql .= ",  NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$k.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i;
	}
	$sql .= " from HSEARCH_RSLT_TBL ";
	$sql .= " where BATCH_ID = '{$batch_id}' and ERR_CODE is not null ";
	$sql .= " order by LINE_NO";
	$sql .= " ) ";
	$sql .= " UNION ALL ";
	$sql .= " select * from (";
	$sql .= "  select ";
	$sql .= "  SEQNO, LINE_NO, ERR_CODE, ERR_MSG, NO,";
	//	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, SHOP_DIST, MATCH_LVL";		mod 2013/03/18 H.Osamoto
	//	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, SHOP_DIST, SHOP_SMSFLG, MATCH_LVL";		mod 2014/03/26 H.Osamoto
	$sql .= "  ADDR, SHOP_NO, SHOP_NAME, SHOP_SAKE, NSHOP_DIST20, SHOP_DIST, SHOP_SMSFLG, MATCH_LVL";
	for ($i=1; $i <= $shop_cnt; $i++) {
		$k = $i + 20;	// add 2014/03/26 H.Osamoto
		//	$sql .= ",    NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i;		mod 2013/03/18 H.Osamoto
		//	$sql .= ",    NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i;		mod 2014/03/26 H.Osamoto
		$sql .= ",    NSHOP_NO".$i.", NSHOP_NAME".$i.", NSHOP_SAKE".$i.", NSHOP_DIST".$k.", NSHOP_DIST".$i.", NSHOP_SMSFLG".$i;
	}
	$sql .= " from HSEARCH_RSLT_TBL ";
	$sql .= " where BATCH_ID = '{$batch_id}' and ERR_CODE is null ";
	$sql .= " order by LINE_NO";
	$sql .= " ) ";

	$stmt = oci_parse($dba->conn, $sql);

	@oci_execute($stmt, OCI_DEFAULT);

	while ($row = oci_fetch_array($stmt, OCI_ASSOC)) {
		$result_list[] = $row;
	}

	oci_free_statement($stmt);

	return true;
}

// ワークデータ削除
function hsearch_work_delete(&$dba, $batch_id) {

	$sql = "delete from HSEARCH_DATA_TBL"
	. " where BATCH_ID = '$batch_id'"
	;
	
	$stmt = null;
	
	if (!$dba->sqlExecute($sql, $stmt)) {
		
		$err_msg = "DB アクセスエラー";
		$err_msg .= " hsearch_work_delete($batch_id)";
		error_log($err_msg."\n", 3, $LOG_FILE);
		
		$dba->free($stmt);
		
		return false;
	}
	
	return true;
}

// 検索結果データ削除
function hsearch_result_delete(&$dba, $batch_id) {

	$sql = "delete from HSEARCH_RSLT_TBL"
	. " where BATCH_ID = '$batch_id'"
	;
	
	$stmt = null;
	
	if (!$dba->sqlExecute($sql, $stmt)) {
		
		$err_msg = "DB アクセスエラー";
		$err_msg .= " hsearch_result_delete($batch_id)";
		error_log($err_msg."\n", 3, $LOG_FILE);
		
		$dba->free($stmt);
		
		return false;
	}
	
	return true;
}

# バッチID生成
function createBatchId() {
	$m    = (float)microtime();
	$miri = "." . substr( (string)$m, 2, 3 );
	$timestamp = date( "YmdHis" ) . $miri;
	$r = sprintf("%04d", rand(1,9999));

	return $timestamp.'.'.$r;
}

?>
