<?php
/*========================================================*/
// ��������
// 2013/03/4 H.Iijima ��������
/*========================================================*/
//**********************************************************************
//
//   function   :   DBOpen
//
//   ��ǽ       :   �ǡ����١��������ץ����
//
//   �ѥ�᡼�� :  (  OUT)  -- ��������ID (null)
//
//   �����     :  ���顼��å�����(��������NULL)
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
//   ��ǽ       :   ��������
//
//   �ѥ�᡼�� :  (INOUT)  -- ��������ID
//                 (INOUT)  -- EMAP_CORP_MST�ơ��֥������
//                 (  OUT)  -- ���顼�ֹ�
//
//   �����     :  true(������) / false(���Ի�)
//
//**********************************************************************

function RdLogin( &$dba, &$arr_emap_corp,$kyoten_id,&$o_rtncd ) {	
	// add start 2010/06/30 T.Kamino		���å����ơ��֥�ˤ����¾������ѹ�
	// add 2010/08/04 Y.Matsukawa [
	// ���å���󥿥��ॢ���Ȼ��ּ���
	global $rd_tmout;
	SelectEmapParmTbl(&$dba, $arr_emap_corp['CORP_ID'], &$arr_pram, &$sql_err);
	$rd_tmout = $arr_pram[CPARM_RDTMOUT];
	// �����ॢ���Ȥ��Ƥ��륻�å�������
	if ($rd_tmout) {
		delete_timeout_sessions(&$dba, $arr_emap_corp['CORP_ID'],$kyoten_id, $rd_tmout, &$err_msg);
	}
	// add 2010/08/04 Y.Matsukawa ]
	// add 2010/10/26 H.Osamoto [
	global $user_logout;
	$user_logout = $arr_pram[CPARM_USERLOGOUT_KBN];
	if ( count($retdata) == 0 ) {
		//-----------------------------------------------
		// ���å����ơ��֥���Ͽ
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
//   ��ǽ       :   ����������
//
//   �ѥ�᡼�� :  (INOUT)  -- ��������ID
//                 (INOUT)  -- EMAP_CORP_MST�ơ��֥������
//                 (  OUT)  -- ���顼�ֹ�
//
//   �����     :  true(������) / false(���Ի�)
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
//   ��ǽ       :   ����ID���������ǽ�����å�
//
//   �ѥ�᡼�� :  (INOUT)  -- ��������ID
//                 (IN   )  -- ���ID
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  0(������̥ǡ�������) / 1(������̥ǡ����ʤ�)
//
//   �ѹ�����   :  2007/06/08 k.Masuda  �����ӥ���������Ƚ�����
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
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata    =   $data;
	}
	$result = count ($retdata);
	if ( $result <= 0 ) {
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

//**********************************************************************
//
//   function   :   SelectKyotenItemTbl                            
//
//   ��ǽ       :   �����ǡ�������̾�ơ��֥����
//
//   �ѥ�᡼�� :  (INOUT)  -- ��������ID
//                 (IN   )  -- ���ID
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
		$err_msg = "������̥ǡ����ʤ�";
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
//   ��ǽ       :   �����ǡ����ơ��֥����
//
//   �ѥ�᡼�� :  (INOUT)  -- ��������ID
//                 (IN   )  -- ���������(����ʤ���null -> "kyoten_id"�Τ�)
//                 (IN   )  -- ���ID
//                 (IN   )  -- ����ID(����ʤ���null)
//                 (IN   )  -- ��������ID(����ʤ���null)
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
	// ����ID
	$val = trim($sch_kyoten_id);
	if (strlen($val)) {
		$sql .= " and kyoten_id like '" . Escape4Like($val, "\\") . "%' escape '\\' ";
	}
	// ����̾
	$val = trim($sch_kyoten_name);
	if (strlen($val)) {
		$val = mb_ereg_replace("��", " ", $val);		// ���ѥ��ڡ�����Ⱦ�ѥ��ڡ���
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
	// ����
	$val = trim($sch_kyoten_addr);
	if (strlen($val)) {
		$val = mb_ereg_replace("��", " ", $val);		// ���ѥ��ڡ�����Ⱦ�ѥ��ڡ���
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
	// �ե꡼���
	$val = trim($sch_kyoten_fw);
	if (strlen($val)) {
		$val = mb_ereg_replace("��", " ", $val);		// ���ѥ��ڡ�����Ⱦ�ѥ��ڡ���
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
	// �ޥå��󥰥�٥�
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
		$err_msg = "������̥ǡ����ʤ�";
		return false;
	}
	$dba->free($stmt);
	return  true;
}


//**********************************************************************
//
//   function   :   ExecSql
//
//   ��ǽ       :   SQL�¹�
//                  (commit����)
//
//   �ѥ�᡼�� :  (INOUT)  -- ��������ID
//                 (IN   )  -- SQL
//
//   �����     :   ���顼��å�����
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
//   ��ǽ       :   �ƥ�ݥ��ե������ɹ��ؿ�
//
//   �ѥ�᡼�� :  (IN   )  -- �ե�����̾
//
//   �����     :   BLOB�ǡ���
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
//   ��ǽ       :   ��ȥѥ�᡼������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
//   ��ǽ       :   ��ȥѥ�᡼������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
// �������ǡ�������������
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
// �ݻ����¡�1ǯ�ˤ�᤮���������ǡ�������
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
// ���å����ǡ�������������
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
// ���å����ǡ������������� �������������
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
			// ����ID�Ͻ���
			continue;
		}
		if ($kyoten_permission && $data['PRMS'] && $data['PRMS'] != "@NULL@" && $data['PRMS'] != $arr_authDef->DEF_PRMS) {
			// �������»�ID�ξ���Ʊ���°ʳ������
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
// �����ॢ���Ȥ��Ƥ��륻�å����ǡ����������
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
* �ؿ�̾ ��  fw_normalize
* ��  �� ��  �ե꡼����������ʥ��饯��ؿ�func_normalize��Ʊ��������������å��������
* ��  �� ��  $str       - �ե꡼���ʸ�����EUC-JP��
* ����� ��  ��������Υե꡼���ʸ����
**/
function fw_normalize($str) {
	$str = mb_convert_kana( $str, "KVC");		// Ⱦ�ѥ��ʢ����ѥ��ʡ��Ҥ餬�ʢ����ѥ��ʡ�������ʸ����
	$str = mb_convert_kana( $str, "rn"  );		// ���ѱѻ���Ⱦ�ѱѻ������ѿ�����Ⱦ�ѿ���
	$str = strtoupper($str);					// �Ѿ�ʸ��������ʸ��
	$str = mb_ereg_replace( "��", "", $str );	// ���ѥ��ڡ�������
	$str = mb_ereg_replace( " ",  "", $str );	// Ⱦ�ѥ��ڡ�������
	$str = mb_ereg_replace( "����", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "-",  "��", $str );
	$str = mb_ereg_replace( "��",  "��", $str );
	$str = mb_ereg_replace( "��",  "/", $str );
	$str = mb_ereg_replace( "��",  "*", $str );
	$str = mb_ereg_replace( "%",  "��", $str );
	$str = mb_ereg_replace( "&",  "��", $str );
	$str = mb_ereg_replace( "\|",  "��", $str );
	$str = mb_ereg_replace( "#",  "��", $str );
	$str = mb_ereg_replace( "\+",  "��", $str );
	$str = mb_ereg_replace( "[�ʡ�\(\)\[\]��@'�ǡ�����]",  "", $str );
	return $str;
}



//**********************************************************************
//
//   function   :   SelectRdGroupDefTblByCorpID 
//
//   ��ǽ       :   RD - �����롼������������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
		$err_msg = "������̥ǡ����ʤ�";
		return false;
	}
	$dba->free($stmt);
	return  true;
}



//**********************************************************************
//
//   function   :   SelectRdItemDefTblByGroupNO
//
//   ��ǽ       :   RD - ����������������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (IN   )  -- ���롼�ףΣ�
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
		$err_msg = "������̥ǡ����ʤ�";
		return false;
	}
	$dba->free($stmt);
	return  true;
}
//**********************************************************************
//
//   function   :   SelectRdGroupTblByKyotenID 
//
//   ��ǽ       :   RD - �����롼�׾������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (IN   )  -- ����ID
//                 (IN   )  -- ���롼�ףΣ�
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
		$err_msg = "������̥ǡ����ʤ�";
		return false;
	}
	$dba->free($stmt);
	return  true;
}

//**********************************************************************
//
//   function   :   SelectRdDataTblByKyotenID 
//
//   ��ǽ       :   RD - ���ǡ����������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (IN   )  -- ����ID
//                 (IN   )  -- ���롼�ףΣ�
//                 (INOUT)  -- �ơ��֥��������
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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
		$err_msg = "������̥ǡ����ʤ�";
		return false;
	}
	$dba->free($stmt);
	return  true;
}


//**********************************************************************
//
//   function   :   DeleteRdDataTblByItemNo 
//
//   ��ǽ       :   RD - ���ǡ����������
//
//   �ѥ�᡼�� :  (INOUT)  -- DB��³
//                 (IN   )  -- ���ID
//                 (IN   )  -- ����ID
//                 (IN   )  -- ���롼�ףΣ�
//                 (IN   )  -- �����ֹ�
//                 (INOUT)  -- ���顼����
//
//   �����     :  true(������) / false(���Ի�)
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