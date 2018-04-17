<?php
/*========================================================*/
// 更新履歴
// 2015/09/30 F.Yokoi sql_collection_rd.incより新規作成
/*========================================================*/

//**********************************************************************
//
//   function   :   SelectKyotenItemTbl                            
//
//   機能       :   拠点データ項目名テーブル取得
//
//   パラメータ :  (INOUT)  -- カーソルID
//                 (IN   )  -- 企業ID
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectKyotenItemTbl( &$dba, $inact, $corp_id, &$retdata, &$err_msg ){

	$sql = "SELECT col_name, item_name, val_kbn, HTML_TAG_FLG ";
	$sql .= ", SRCH_KBN, OPT_07 ";
	$sql .= " FROM KYOTEN_ITEM_TBL ";
	$sql .= " WHERE corp_id = '" . $corp_id . "' ";
	if ( $inact ) {
		$sql .= " AND col_name IN ( 'ADDR' , 'NAME' ) ";
	} else {
		$sql .= " ORDER BY disp_num ";
	}

	$stmt = null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$err_msg = $dba->getError($stmt);
		$dba->free($stmt);
		$dba->close();
		include( "template/error.tpl" );
		exit;
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[] = $data;
	}
	$result = count( $retdata );
	if ( $result <= 0 ) {
		$err_msg = "検索結果データなし";
		return false;
	}
	$dba->free($stmt);
	return  true;
}

//**********************************************************************
//
//   function   :   SelectKyotenTbl                             
//
//   機能       :   拠点データテーブル取得
//
//   パラメータ :  (INOUT)  -- カーソルID
//                 (IN   )  -- 取得カラム(指定なしはnull -> "kyoten_id"のみ)
//                 (IN   )  -- 企業ID
//                 (IN   )  -- 拠点ID(指定なしはnull)
//                 (IN   )  -- アイコンID(指定なしはnull)
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectKyotenTbl(&$dba, $getcol, $corp_id, $kyoten_id, $icon_id,
						&$retdata, &$err_msg 
						,$arr_authDef
						,$sch_kyoten_id = null
						,$sch_kyoten_name = null
						,$sch_kyoten_addr = null
						,$sch_m_level = null
						,$sch_kyoten_fw = null
						) {
	if ( $getcol ) {
		$sql  =  "SELECT " . $getcol ;
	} else {
		$sql  =  "SELECT kyoten_id ";
	}
	$sql  .= " FROM KYOTEN_TBL ";
	$sql  .= " WHERE corp_id = '" . $corp_id   . "' ";
	if ( $kyoten_id || $kyoten_id == '0' ) {
		$sql  .= " AND kyoten_id = '" . $kyoten_id . "' ";
	}
	if ( $icon_id || $icon_id == '0' ) {
		$sql  .= " AND icon_id = '" . $icon_id . "' ";
	}
	if ($arr_authDef->PRMS_COL && $arr_authDef->DEF_PRMS && $arr_authDef->DEF_PRMS != "@NULL@") {
		$sql  .=  "         AND " . $arr_authDef->PRMS_COL . " = '" . $arr_authDef->DEF_PRMS . "' ";
	}
	// 拠点ID
	$val = trim($sch_kyoten_id);
	if (strlen($val)) {
		$sql .= " and kyoten_id like '" . Escape4Like($val, "\\") . "%' escape '\\' ";
	}
	// 拠点名
	$val = trim($sch_kyoten_name);
	if (strlen($val)) {
		$val = mb_ereg_replace("　", " ", $val);		// 全角スペース→半角スペース
		$vals = explode(" ", $val);
		if (count($vals) > 0) {
			$fws = array();
			foreach ($vals as $v) {
				if (mb_strlen($v)) {
					$v = fw_normalize($v);
					$fws[] = " func_normalize(name) like '%" . Escape4Like($v, "\\") . "%' escape '\\' ";
				}
			}
			if (count($fws)) {
				$sql .= " and (";
				$sql .= implode(" and ", $fws);
				$sql .= ")";
			}
		}
	}
	// 住所
	$val = trim($sch_kyoten_addr);
	if (strlen($val)) {
		$val = mb_ereg_replace("　", " ", $val);		// 全角スペース→半角スペース
		$vals = explode(" ", $val);
		if (count($vals) > 0) {
			$fws = array();
			foreach ($vals as $v) {
				if (mb_strlen($v)) {
					$v = fw_normalize($v);
					$fws[] = " func_normalize(addr) like '%" . Escape4Like($v, "\\") . "%' escape '\\' ";
				}
			}
			if (count($fws)) {
				$sql .= " and (";
				$sql .= implode(" and ", $fws);
				$sql .= ")";
			}
		}
	}
	// フリーワード
	$val = trim($sch_kyoten_fw);
	if (strlen($val)) {
		$val = mb_ereg_replace("　", " ", $val);		// 全角スペース→半角スペース
		$vals = explode(" ", $val);
		if (count($vals) > 0) {
			$fws = array();
			foreach ($vals as $v) {
				if (mb_strlen($v)) {
					$v = fw_normalize($v);
					$fws[] = " instr(FREE_SRCH, '" . $v . "')<>0 ";
				}
			}
			if (count($fws)) {
				$sql .= " and (";
				$sql .= implode(" and ", $fws);
				$sql .= ")";
			}
		}
	}
	// マッチングレベル
	if ($sch_m_level) {
		$sql .= " and M_LEVEL <= '" . $sch_m_level . "' ";
		$sql .= " and M_LEVEL != '0' ";
	} else if ($sch_m_level === '0') {
		$sql .= " and M_LEVEL <= '0' ";
	}
	$sql  .=  " ORDER BY kyoten_id ";

	$stmt =  null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$err_msg    =   $dba->getError($stmt);
		$dba->free($stmt);
		$dba->close();
		include( "template/error.tpl" );
		exit;
	}
	$retdata    =   array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[]  =   $data;
	}
	$result = count( $retdata );
	if ( $result <= 0 ) {
		$err_msg = "検索結果データなし";
		return false;
	}
	$dba->free($stmt);
	return  true;
}

//**********************************************************************
//
//   function   :   SelectEmapParmTbl
//
//   機能       :   企業パラメータ取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectEmapParmTbl(&$dba, $corp_id, &$retdata, &$err_msg) {
	$t_cid = (substr($corp_id,-4)=='test' ? $corp_id : $corp_id.'test');
	$sql = "select KBN, VALUE"
		. " from EMAP_PARM_TBL"
		. " where CORP_ID='" . $t_cid . "'"
	;
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		$dba->free($stmt);
		$dba->close();
		include( "template/error.tpl" );
		exit;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[$data['KBN']] = $data['VALUE'];
	}
	$dba->free($stmt);
	return true;
}

//**********************************************************************
//
//   function   :   SelectEmapParmTblByCorpID                 
//
//   機能       :   企業パラメータ取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectEmapParmTblByCorpID(&$dba, $corp_id, &$retdata, &$err_msg) {
	$sql = "select KBN, VALUE"
		. " from EMAP_PARM_TBL"
		. " where CORP_ID='" . $corp_id . "'"
	;
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		$dba->free($stmt);
		$dba->close();
		include( "template/error.tpl" );
		exit;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[$data['KBN']] = $data['VALUE'];
	}
	$dba->free($stmt);
	return true;
}

?>
