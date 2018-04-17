<?php
/*========================================================*/
// 更新履歴
// 2013/03/4 H.Iijima 新規作成
/*========================================================*/
//**********************************************************************
//
//   function   :   DBOpen
//
//   機能       :   データベースオープン処理
//
//   パラメータ :  (  OUT)  -- カーソルID (null)
//
//   戻り値     :  エラーメッセージ(成功時はNULL)
//
//**********************************************************************
function DBOpen( &$dba ) {
	$err_msg = null;

	$dba  =  new oraDBAccess();
	if ( ! $dba->open() ) {
		$err_msg    =  "DataBase Open Error ! ";
		return $err_msg;
	}
	$sql = "alter session set nls_date_format='yyyymmddhh24miss'";
	$dba->sqlExecute( $sql, $stmt);

	return $err_msg;
}

//**********************************************************************
//
//   function   :   RdLogin                    
//
//   機能       :   ログイン
//
//   パラメータ :  (INOUT)  -- カーソルID
//                 (INOUT)  -- EMAP_CORP_MSTテーブルの配列
//                 (  OUT)  -- エラー番号
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************

function RdLogin( &$dba, &$arr_emap_corp,$kyoten_id,&$o_rtncd ) {	
	// add start 2010/06/30 T.Kamino		セッションテーブルによる排他制御へ変更
	// add 2010/08/04 Y.Matsukawa [
	// セッションタイムアウト時間取得
	global $rd_tmout;
	SelectEmapParmTbl(&$dba, $arr_emap_corp['CORP_ID'], &$arr_pram, &$sql_err);
	$rd_tmout = $arr_pram[CPARM_RDTMOUT];
	// タイムアウトしているセッションを削除
	if ($rd_tmout) {
		delete_timeout_sessions(&$dba, $arr_emap_corp['CORP_ID'],$kyoten_id, $rd_tmout, &$err_msg);
	}
	// add 2010/08/04 Y.Matsukawa ]
	// add 2010/10/26 H.Osamoto [
	global $user_logout;
	$user_logout = $arr_pram[CPARM_USERLOGOUT_KBN];
	if ( count($retdata) == 0 ) {
		//-----------------------------------------------
		// セッションテーブル登録
		//-----------------------------------------------
		global $corp_user_login;//?
		global $login_userid;//?
		global $session_id;

		$userid = ($corp_user_login ? $login_userid : '@CID@');
		$ret = RdSessionCreate(&$dba, $arr_emap_corp['CORP_ID'], $kyoten_id,&$session_id ,&$o_rtncd);
		if ( ! $ret || ( $o_rtncd != 0 ) ) {
			$o_rtncd = 9;
			return false;
		}
	// add end 2010/06/30 T.Kamino
	} else {
		$o_rtncd = 0;
		return false;
	}
	return true;
}

//**********************************************************************
//
//   function   :   RdLogout
//
//   機能       :   ログアウト
//
//   パラメータ :  (INOUT)  -- カーソルID
//                 (INOUT)  -- EMAP_CORP_MSTテーブルの配列
//                 (  OUT)  -- エラー番号
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function RdLogout( &$dba, &$arr_emap_corp,$kyoten_id, &$o_rtncd ) {
	global $corp_id_t;
	global $login_userid;
	global $session_id;

	$retcd = RdSessionRemove( &$dba, $arr_emap_corp['CORP_ID'], $kyoten_id, &$session_id, &$o_rtncd );
	if (!$retcd){
		include( "template/error.tpl" );
		$dba->close();
		exit;
	}
	// add end 2010/06/30 T.Kamino

	if ( ! $retcd || ( $o_rtncd != 0 ) ) {
		return false;
	}

	return true;
}


//**********************************************************************
//
//   function   :   SelectServDate                    
//
//   機能       :   拠点IDログイン可能チェック
//
//   パラメータ :  (INOUT)  -- カーソルID
//                 (IN   )  -- 企業ID
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  0(検索結果データあり) / 1(検索結果データなし)
//
//   変更履歴   :  2007/06/08 k.Masuda  サービス開始日の判定を削除
//
//**********************************************************************
function SelectServDate( &$dba, $cid, &$retdata, &$err_msg ){

	//    $sql    =   "SELECT TO_CHAR(S_DATE,'yyyymmdd') AS S_DATE,";
	//    $sql    .=  "       TO_CHAR(E_DATE,'yyyymmdd') AS E_DATE,";
	//    $sql    .=  " CASE WHEN SYSDATE BETWEEN S_DATE AND E_DATE ";
	$sql    =   "SELECT E_DATE, ";
	$sql    .=  " CASE WHEN SYSDATE <= E_DATE ";
	$sql    .=  "      THEN '1' ELSE '0' END AS SFLG ";
	$sql    .=  " FROM EMAP_CORP_MST ";
	$sql    .=  " WHERE CORP_ID = '$cid'";

	$stmt   = null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$retdata = array();
	if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata    =   $data;
	}
	$result = count ($retdata);
	if ( $result <= 0 ) {
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

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

	//$sql = "SELECT col_name, item_name, val_kbn, html_lnk_flg ";		2007/06/14 mod Y.Matsukawa
	$sql = "SELECT col_name, item_name, val_kbn, HTML_TAG_FLG ";
	$sql .= ", SRCH_KBN";		// add 2009/04/10 Y.Matsukawa
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

// add 2010/09/17 add K.Masuda ]

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
						,$arr_authDef				// add 2010/10/26 H.Osamoto
						,$sch_kyoten_id = null
						,$sch_kyoten_name = null
						,$sch_kyoten_addr = null
						,$sch_m_level = null		// add 2009/04/06 Y.Matsukawa
						,$sch_kyoten_fw = null		// add 2009/04/10 Y.Matsukawa
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
	// add  2010/10/26 H.Osamoto [
	if ($arr_authDef->PRMS_COL && $arr_authDef->DEF_PRMS && $arr_authDef->DEF_PRMS != "@NULL@") {
		$sql  .=  "         AND " . $arr_authDef->PRMS_COL . " = '" . $arr_authDef->DEF_PRMS . "' ";
	}
	// add  2010/10/26 H.Osamoto ]
	// add 2009/02/09 Y.Matsukawa [
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
					//$fws[] = " func_normalize(name) like '%'||func_normalize('" . Escape4Like($v, "\\") . "')||'%' escape '\\' ";		mod 2009/04/07 Y.Matsukawa
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
					//$fws[] = " func_normalize(addr) like '%'||func_normalize('" . Escape4Like($v, "\\") . "')||'%' escape '\\' ";		mod 2009/04/07 Y.Matsukawa
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
	// add 2009/02/09 Y.Matsukawa ]
	// add 2009/04/10 Y.Matsukawa [
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
	// add 2009/04/10 Y.Matsukawa ]
	// add 2009/04/06 Y.Matsukawa [
	// マッチングレベル
	if ($sch_m_level) {
		$sql .= " and M_LEVEL <= '" . $sch_m_level . "' ";
		$sql .= " and M_LEVEL != '0' ";
	} else if ($sch_m_level === '0') {
		$sql .= " and M_LEVEL <= '0' ";
	}
	// add 2009/04/06 Y.Matsukawa ]
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
//   function   :   ExecSql
//
//   機能       :   SQL実行
//                  (commitあり)
//
//   パラメータ :  (INOUT)  -- カーソルID
//                 (IN   )  -- SQL
//
//   戻り値     :   エラーメッセージ
//
//**********************************************************************
function ExecSql( &$dba , $sql ) {

	$stmt   =  null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$err_msg    =   $dba->getError($stmt);
		$dba->free($stmt);
		include( "template/error.tpl" );
		return $err_msg;
	}
	$dba->commitTransaction();
	return $err_msg;
}

//**********************************************************************
//
//   function   :   LoadFile 
//
//   機能       :   テンポラリファイル読込関数
//
//   パラメータ :  (IN   )  -- ファイル名
//
//   戻り値     :   BLOBデータ
//
//**********************************************************************
function LoadFile( $filename ) {
	$fp   =  fopen( $filename, 'r' );
	$buf  =  fread( $fp, filesize( $filename ) );
	fclose( $fp );
	return $buf;
}

// add 2009/02/20 Y.Matsukawa
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
	$t_cid = (substr($corp_id,-4)=='test' ? $corp_id : $corp_id.'test');	// add 2009/12/08 Y.Matsukawa
	$sql = "select KBN, VALUE"
		. " from EMAP_PARM_TBL"
		//. " where CORP_ID='" . $corp_id . "'"		mod 2009/12/08 Y.Matsukawa
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

// add 2012/04/23 N.Wada
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

// add 2010/03/26 Y.Matsukawa
//------------------------------------------------------------
//
// select_opelog
//
// 操作ログデータを取得＜ｎ件＞
//
//------------------------------------------------------------
function select_opelog(&$dba, $cid, $from_ymd, $to_ymd, &$retdata, &$err_msg){
	$sql = "select CORP_ID, CORP_USERID, to_char(OP_DT, 'yyyy/mm/dd hh24:mi:ss') OP_DT_F, FO_KBN, FUNC, OPE, REMOTE_ADDR, USER_AGENT";
	$sql .= " from FO_OPERATION_LOG";
	$sql .= " where CORP_ID = '".$cid."'";
	$sql .= " and trunc(OP_DT) between to_date('".$from_ymd."','yyyymmdd') and to_date('".$to_ymd."','yyyymmdd')";
	$sql .= " order by OP_DT, SEQ";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		$dba->free($stmt);
		$dba->close();
		include("template/error.tpl");
		exit;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	$dba->free($stmt);
	return true;
}

// add 2011/04/04 Y.Matsukawa
//------------------------------------------------------------
//
// delete_rd_opelog_expired
//
// 保持期限（1年）を過ぎた操作ログデータを削除
//
//------------------------------------------------------------
function delete_rd_opelog_expired(&$dba, &$err_msg) {
	$y = date('Y');
	$m = date('m');
	$d = date('d');
	$dt = date('Ymd', mktime(0, 0, 0, $m, $d, $y-1));
	$sql = "delete from RD_OPERATION_LOG"
		. " where trunc(OP_DT) < to_date('$dt','yyyymmdd')"
	;
//error_log("$sql\n", 3, "/var/tmp/emapRD.".date('Ymd').".debug.log");
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		$dba->free($stmt);
		include( "template/error.tpl" );
		return $err_msg;
	}
	$dba->commitTransaction();
	return $err_msg;
}

// add 2010/06/30 T.Kamino
//------------------------------------------------------------
//
// select_session_list
//
// セッションデータを取得＜ｎ件＞
//
//------------------------------------------------------------
function select_rd_session(&$dba,$cid,$kyoten_id,$session_id, &$retdata, &$err_msg){
	$sql = "select  CORP_ID, KYOTEN_ID, SESSION_ID,";
	$sql .= " to_char(LOGIN_DT, 'yyyy/mm/dd hh24:mi:ss') LOGIN_DT_F,";
	$sql .= " to_char(ACC_DT, 'yyyy/mm/dd hh24:mi:ss') ACC_DT_F,";
	$sql .= " to_char(SYSDATE, 'yyyy/mm/dd hh24:mi:ss') NOW_DT_F";
	$sql .= " from RD_SESSION";
	$sql .= " where CORP_ID = '".$cid."'";
	if(strlen($kyoten_id))
	$sql .= " and KYOTEN_ID = '".$kyoten_id."'";
	if(strlen($session_id))
	$sql .= " and SESSION_ID = '".$session_id."'";
	$sql .= " order by LOGIN_DT";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		return false;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$dba->free($stmt);
	return true;
}

// add 2010/10/26 H.Osamoto
//------------------------------------------------------------
//
// select_session_list
//
// セッションデータを取得＜ｎ件＞ ログイン時専用
//
//------------------------------------------------------------
function select_fo_session_login(&$dba,$fo_kbn, $cid, $arr_authDef, &$retdata, &$err_msg){
	if ($arr_authDef->DEF_PRMS && $arr_authDef->DEF_PRMS != "@NULL@") {
		$kyoten_permission = true;
	}
	$sql = "select  M.FO_KBN, M.CORP_ID, M.CORP_USERID, M.SESSION_ID,";
	$sql .= " M.LOGIN_DT_F, M.ACC_DT_F, M.NOW_DT_F, R.REF, P.PRMS ";
	$sql .= " from ( ";
	
	$sql .= " ( select F.FO_KBN, F.CORP_ID, F.CORP_USERID, F.SESSION_ID, ";
	$sql .= " to_char(F.LOGIN_DT, 'yyyy/mm/dd hh24:mi:ss') LOGIN_DT_F, ";
	$sql .= " to_char(F.ACC_DT, 'yyyy/mm/dd hh24:mi:ss') ACC_DT_F, ";
	$sql .= " to_char(SYSDATE, 'yyyy/mm/dd hh24:mi:ss') NOW_DT_F ";
	$sql .= " from RD_SESSION F ";
	$sql .= " where F.CORP_ID = '".$cid."' and F.FO_KBN = '".$fo_kbn."'";
	$sql .= " ) M left join ";

	$sql .= " (select A1.CORP_ID, U1.CORP_USERID, A1.AUTH_DEF REF ";
	$sql .= " from EMAP_CORP_AUTH_DEF A1, EMAP_CORP_USER_MST U1 ";
	$sql .= " where A1.CORP_ID = '".$cid."' and A1.CORP_ID = U1.CORP_ID ";
	$sql .= " and A1.AUTH_KBN='REF' and A1.AUTH_ID = U1.AUTH_ID ";
	$sql .= " ) R on M.CORP_USERID = R.CORP_USERID ";
	
	$sql .= " ) left join ";
	$sql .= " ( select A2.CORP_ID, U2.CORP_USERID, A2.AUTH_DEF PRMS ";
	$sql .= " from EMAP_CORP_AUTH_DEF A2, EMAP_CORP_USER_MST U2 ";
	$sql .= " where A2.CORP_ID = '".$cid."' and A2.CORP_ID = U2.CORP_ID ";
	$sql .= " and AUTH_KBN='PRMS' and A2.AUTH_ID = U2.AUTH_ID ";
	$sql .= " ) P on M.CORP_USERID = P.CORP_USERID ";
	
	$sql .= " order by M.LOGIN_DT_F";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		return false;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		if ($data['REF'] && $data['REF'] == 1 ) {
			// 参照IDは除外
			continue;
		}
		if ($kyoten_permission && $data['PRMS'] && $data['PRMS'] != "@NULL@" && $data['PRMS'] != $arr_authDef->DEF_PRMS) {
			// 拠点制限子IDの場合は同権限以外を除外
			continue;
		}
		$retdata[] = $data;
	}
	$dba->free($stmt);
	return true;
}

// add 2010/08/04 Y.Matsukawa
//------------------------------------------------------------
//
// delete_timeout_sessions
//
// タイムアウトしているセッションデータを全削除
//
//------------------------------------------------------------
function delete_timeout_sessions(&$dba, $corp_id,$kyoten_id, $minutes, &$err_msg) {

	$lim = date("Y/m/d H:i:s", strtotime("-".$minutes." minute"));
	$sql = "delete from RD_SESSION"
		. " where CORP_ID = '" . $corp_id . "'"
		. " and KYOTEN_ID = '" . $kyoten_id . "'"
		. " and ACC_DT <= to_date('" . $lim . "','yyyy/mm/dd hh24:mi:ss')"
	;
//error_log($sql."\n", 3, "/var/tmp/emapFO.".date('Ymd').".debug.log");
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$err_msg = $dba->getError($stmt);
		$dba->free($stmt);
		include( "template/error.tpl" );
		return $err_msg;
	}
	$dba->commitTransaction();
	return $err_msg;
}

/**
* 関数名 ：  fw_normalize
* 概  要 ：  フリーワード正規化（オラクル関数func_normalizeと同一の正規化ロジックを実装）
* 引  数 ：  $str       - フリーワード文字列（EUC-JP）
* 戻り値 ：  正規化後のフリーワード文字列
**/
function fw_normalize($str) {
	$str = mb_convert_kana( $str, "KVC");		// 半角カナ→全角カナ、ひらがな→全角カナ、濁音を１文字に
	$str = mb_convert_kana( $str, "rn"  );		// 全角英字→半角英字、全角数字→半角数字
	$str = strtoupper($str);					// 英小文字→英大文字
	$str = mb_ereg_replace( "　", "", $str );	// 全角スペース除去
	$str = mb_ereg_replace( " ",  "", $str );	// 半角スペース除去
	$str = mb_ereg_replace( "ウ゛", "ヴ", $str );
	$str = mb_ereg_replace( "ァ", "ア", $str );
	$str = mb_ereg_replace( "ィ", "イ", $str );
	$str = mb_ereg_replace( "ゥ", "ウ", $str );
	$str = mb_ereg_replace( "ェ", "エ", $str );
	$str = mb_ereg_replace( "ォ", "オ", $str );
	$str = mb_ereg_replace( "ッ", "ツ", $str );
	$str = mb_ereg_replace( "ャ", "ヤ", $str );
	$str = mb_ereg_replace( "ュ", "ユ", $str );
	$str = mb_ereg_replace( "ョ", "ヨ", $str );
	$str = mb_ereg_replace( "ヮ", "ワ", $str );
	$str = mb_ereg_replace( "ヵ", "カ", $str );
	$str = mb_ereg_replace( "ヶ", "ケ", $str );
	$str = mb_ereg_replace( "ー", "−", $str );
	$str = mb_ereg_replace( "-",  "−", $str );
	$str = mb_ereg_replace( "ﾞ",  "゛", $str );
	$str = mb_ereg_replace( "／",  "/", $str );
	$str = mb_ereg_replace( "＊",  "*", $str );
	$str = mb_ereg_replace( "%",  "％", $str );
	$str = mb_ereg_replace( "&",  "＆", $str );
	$str = mb_ereg_replace( "\|",  "｜", $str );
	$str = mb_ereg_replace( "#",  "＃", $str );
	$str = mb_ereg_replace( "\+",  "＋", $str );
	$str = mb_ereg_replace( "[（）\(\)\[\]＠@'’・･〜]",  "", $str );
	return $str;
}



//**********************************************************************
//
//   function   :   SelectRdGroupDefTblByCorpID 
//
//   機能       :   RD - 　グループ定義情報取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectRdGroupDefTblByCorpID(&$dba, $corp_id, &$retdata, &$err_msg) {
	$sql = "select GROUP_NO,GROUP_NAME,DISP_NUM,USE_SYONIN,USE_KIKAN "
		. " from RD_GROUP_DEF_TBL"
		. " where CORP_ID='" . $corp_id . "'"
		. " ORDER BY disp_num ";
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
//   function   :   SelectRdItemDefTblByGroupNO
//
//   機能       :   RD - 　項目定義情報取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (IN   )  -- グループＮＯ
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectRdItemDefTblByGroupNO(&$dba, $corp_id,$group_no,&$retdata, &$err_msg) {
	$sql = "select * "
		. " from RD_ITEM_DEF_TBL"
		. " where CORP_ID='" . $corp_id . "'"
		. " and GROUP_NO='" . $group_no . "'"
		. " and DEL_FLG='0' "
		. " ORDER BY disp_num ";
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
//   function   :   SelectRdGroupTblByKyotenID 
//
//   機能       :   RD - 　グループ情報取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (IN   )  -- 拠点ID
//                 (IN   )  -- グループＮＯ
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectRdGroupTblByKyotenID(&$dba, $corp_id,$kyoten_id,$group_no,&$retdata, &$err_msg) {
	$sql = "select * "
		. " from RD_GROUP_TBL"
		. " where CORP_ID='" . $corp_id . "'"
		. " and KYOTEN_ID='" . $kyoten_id . "'"
		. " and GROUP_NO='" . $group_no . "'";
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
//   function   :   SelectRdDataTblByKyotenID 
//
//   機能       :   RD - 　データ情報取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (IN   )  -- 拠点ID
//                 (IN   )  -- グループＮＯ
//                 (INOUT)  -- テーブル取得情報
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************
function SelectRdDataTblByKyotenID(&$dba, $corp_id,$kyoten_id,$group_no,&$retdata, &$err_msg) {
	$sql = "select CORP_ID,KYOTEN_ID ,GROUP_NO, ITEM_NO ,VAL_KBN ,TXT_DATA ,FLG_DATA ,IMG_W,IMG_H "
		. " from RD_DATA_TBL"
		. " where CORP_ID='" . $corp_id . "'"
		. " and KYOTEN_ID='" . $kyoten_id . "'"
		. " and GROUP_NO='" . $group_no . "'";
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
//		$retdata[] = $data;
		$retdata[$data['ITEM_NO']] = $data;
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
//   function   :   DeleteRdDataTblByItemNo 
//
//   機能       :   RD - 　データ情報取得
//
//   パラメータ :  (INOUT)  -- DB接続
//                 (IN   )  -- 企業ID
//                 (IN   )  -- 拠点ID
//                 (IN   )  -- グループＮＯ
//                 (IN   )  -- 項目番号
//                 (INOUT)  -- エラー情報
//
//   戻り値     :  true(成功時) / false(失敗時)
//
//**********************************************************************

function DeleteRdDataTblByItemNo(&$dba, $corp_id,$kyoten_id,$group_no,$item_no, &$err_msg) {
	$sql = "Delete from RD_DATA_TBL "
		. " where CORP_ID='" . $corp_id . "'"
		. " and KYOTEN_ID='" . $kyoten_id . "'"
		. " and GROUP_NO='" . $group_no . "'"
		. " and ITEM_NO='" . $item_no . "'";
	$stmt  =  null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$err_msg    =   $dba->getError($stmt);
		$dba->free($stmt);
//		include( "template/error.tpl" );
		return false;
	}
	return ture;

}


?>
