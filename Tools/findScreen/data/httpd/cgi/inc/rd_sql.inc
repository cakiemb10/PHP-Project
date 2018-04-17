<?php
/*========================================================*/
// ��������
// 2013/02/20 Y.Matsukawa	��������
// 2015/01/16 F.Yokoi		RD��������ǡ�������

/*========================================================*/
/*==============================================*/
// RD������������
/*==============================================*/
function isRDAvailable(&$dba, $CID) {
	$sql = "select VALUE from EMAP_PARM_TBL";
	$sql .= " where CORP_ID = '".$CID."'";
	$sql .= " and KBN = 'USE_RD'";
	$stmt = null;
	dbl($sql);
	if ($dba->sqlExecute($sql, $stmt)) {
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if($data['VALUE'] == '1') {
				$dba->free($stmt);
				return true;
			}
		}
	}
	$dba->free($stmt);
	return false;
}
/*==============================================*/
// ɽ����ʬ��RD���롼�פ򸡺�
/*==============================================*/
function selectRDGroupByView(&$dba, $CID, $view) {
	$arr_grp = array();
	$sql  = "select";
	$sql .= " GROUP_NO";
	$sql .= " from RD_GROUP_DEF_TBL";
	$sql .= " where CORP_ID = '".$CID."'";
	switch ($view) {
		case 1:		// PC�ܺ�
			$sql .= " and VIS_PCDTL = '1'";
			break;
		case 2:		// PC����
			$sql .= " and VIS_PCPRT = '1'";
			break;
		case 3:		// �ե�����
			$sql .= " and VIS_MSG = '1'";
			break;
		case 4:		// ���Ӿܺ�
			$sql .= " and VIS_MBDTL = '1'";
			break;
		case 5:		// ���ޥ۾ܺ�
			$sql .= " and VIS_SMDTL = '1'";
			break;
		case 6:		// ����
			$sql .= " and VIS_LIST = '1'";
			break;
		default:
			return $arr_grp;
	}
	dbl($sql);
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return $arr_grp;
	}
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$arr_grp[] = $data['GROUP_NO'];
	}
	$dba->free($stmt);
	dbl("--> ".implode(',', $arr_grp));
	
	return $arr_grp;
}

/*==============================================*/
// RD�ǡ�������
/*==============================================*/
function selectRDData(&$dba, $CID, &$arr_kid, &$arr_grp) {
	$sql  = "select";
	$sql .= " G.KYOTEN_ID, G.GROUP_NO, I.ITEM_NO, I.ITEM_NAME, I.VAL_KBN";
	$sql .= " , D.TXT_DATA, D.FLG_DATA, D.IMG_W, D.IMG_H";
	$sql .= " from RD_ITEM_DEF_TBL I, RD_GROUP_DEF_TBL F, RD_DATA_TBL D, RD_GROUP_TBL G";
	$sql .= " where G.CORP_ID = '".$CID."'";
	$sql .= " and F.CORP_ID = '".$CID."'";
	$sql .= " and D.CORP_ID = '".$CID."'";
	$sql .= " and I.CORP_ID = '".$CID."'";
	$sql .= " and G.GROUP_NO = F.GROUP_NO";
	$sql .= " and G.GROUP_NO = D.GROUP_NO";
	$sql .= " and G.GROUP_NO = I.GROUP_NO";
	$sql .= " and D.KYOTEN_ID = G.KYOTEN_ID";
	$sql .= " and I.ITEM_NO = D.ITEM_NO";
	$sql .= " and I.DEL_FLG = '0'";
	$sql .= " and (";
	$sql .=		" F.USE_KIKAN = '0'";
	$sql .=		" or (";
	$sql .=			" nvl(to_char(G.ST_DT,'yyyymmddhh24'),'0') <= to_char(sysdate,'yyyymmddhh24')";
	$sql .=			" and nvl(to_char(G.ED_DT,'yyyymmddhh24'),'9999999999') > to_char(sysdate,'yyyymmddhh24')";
	$sql .=		" )";
	$sql .= " )";
	// ���롼��ID����
	if (count($arr_grp)) {
		if (count($arr_grp) == 1) {
			$sql .= " and G.GROUP_NO = ".$arr_grp[0];
		} else {
			$sql .= " and G.GROUP_NO in (".implode(',', $arr_grp).")";
		}
	}
	unset($arr_grp);
	// ����ID����
	foreach ($arr_kid as $i => $kyotenid) {
		$arr_kid[$i] = "'".escapeOra($kyotenid)."'";
	}
	if (count($arr_kid) == 1) {
		$sql .= " and G.KYOTEN_ID = ".$arr_kid[0];
	} else if (count($arr_kid) > 0) {
		$sql .= " and G.KYOTEN_ID in (".implode(',', $arr_kid).")";
	}
	unset($arr_kid);
	// ������
	$sql .= " order by G.KYOTEN_ID, G.GROUP_NO, I.DISP_NUM";
	// �ǡ�������
	dbl($sql);
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return false;
	}
	$arr_kyoten = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$kyotenid = $data['KYOTEN_ID'];
		$group_no = $data['GROUP_NO'];
		$item_no  = $data['ITEM_NO'];
		$arr_kyoten[$kyotenid]['GROUP_LIST'][$group_no][$item_no] = array(
			'ITEM_NAME'=>$data['ITEM_NAME'],
			'VAL_KBN'=>$data['VAL_KBN'],
			'TXT_DATA'=>$data['TXT_DATA'],
			'FLG_DATA'=>$data['FLG_DATA'],
			'IMG_W'=>$data['IMG_W'],
			'IMG_H'=>$data['IMG_H']
		);
	}
	$dba->free($stmt);
	
	return $arr_kyoten;
}

// add 2015/01/16 F.Yoko [
/*==============================================*/
// RD��������ǡ�������
/*==============================================*/
function selectRDItemDef(&$dba, $CID) {
	$sql  = "select";
	$sql .= " I.GROUP_NO,";
	$sql .= " I.ITEM_NO, ";
	$sql .= " I.VAL_KBN, ";
	$sql .= " I.TEXT_MAXLEN ";
	$sql .= " from RD_ITEM_DEF_TBL I, RD_GROUP_DEF_TBL F ";
	$sql .= " where I.CORP_ID = '".$CID."'";
	$sql .= " and F.CORP_ID = '".$CID."'";
	$sql .= " and I.DEL_FLG = '0'";
	$sql .= " and I.GROUP_NO = F.GROUP_NO";
	$sql .= " and (";
	$sql .=		" F.USE_KIKAN = '0'";
	$sql .= " )";

	// �ǡ�������
	dbl($sql);
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return false;
	}
	$arr_kyoten = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$group_no = $data['GROUP_NO'];
		$item_no  = $data['ITEM_NO'];
		$val_kbn = $data['VAL_KBN'];
		$text_maxlen = $data['TEXT_MAXLEN'];

		$arr_kyoten[$group_no][$item_no]['kbn'] = $val_kbn;
		$arr_kyoten[$group_no][$item_no]['maxlen'] = $text_maxlen;
	}
	$dba->free($stmt);
	
	return $arr_kyoten;
}
// add 2015/01/16 F.Yoko ]

// add 2015/01/16 F.Yoko [
/*==============================================*/
// ���եǡ�������
/*==============================================*/
function select_near_kyoten_rd( &$dba, $key, $lat, $lon, $arr_latlon, $rad,
	$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg, $absdist, &$exArea, $immref=false, $polycol, $arr_rd_item ,$rd_jkn ){
	//�Ǵ������ꥹ�Ȥ�������롣
	//  pos         �������ϰ���
	//  cnt         �������
	//  hit_num     �ҥåȷ��

	$sql = "SELECT KYOTEN_ID, LAT, LON, ICON_ID, KYORI, BFLG ";
	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
		foreach( $arr_col_name as $rowdata ) {
			// mod 2011/07/05 Y.Nakajima
			$sql .= "," . $rowdata['COL_NAME'];
		}
		$sql .= " ";
	}

	if (count($arr_rd_item) > 0) {
		foreach ($arr_rd_item as $g_no => $glist_array) {
			foreach ($glist_array as $item_no => $item_flg) {
				$sql .= ",RT".$g_no."_".$item_no.".RDATA ";
			}
		}
	}

	$sql .= "FROM ";
	$sql .= "( ";
	$sql .= "SELECT KYOTEN_ID, LAT, LON, ICON_ID, ";
	$sql .= "POWER( ABS( LAT - $lat ) * (  9 / 300000 * 1000 ), 2 ) + ";
	$sql .= "POWER( ABS( LON - $lon ) * ( 11 / 450000 * 1000 ), 2 ) AS KYORI, ";
	// Ǥ����������ε�Υ		add 2013/08/02 Y.Matsukawa
	if (is_array($exArea)) {
		$sql .= "POWER( ABS( LAT - ".$exArea[lat]." ) * (  9 / 300000 * 1000 ), 2 ) + ";
		$sql .= "POWER( ABS( LON - ".$exArea[lon]." ) * ( 11 / 450000 * 1000 ), 2 ) AS EX_KYORI, ";
	}
	//NEW��������ɽ���ե饰
	//  ����������λ������NULL�ξ�硧'0'
	//  SYSDATE�����������齪λ�������äƤ����硧'1'
	//  SYSDATE�����������齪λ�������äƤ��ʤ���硧'0'
	//  ��â�����㤨��SYSDATE��20070306�ǡ���������NULL����λ����20070305�ξ��ϡ�'0'��
	$sql .= "CASE ";
	$sql .= "WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0' ";
	$sql .= "WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "NVL(DISP_NEW_E_DATE, SYSDATE) THEN '1' ";
	$sql .= "ELSE '0' ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
		foreach( $arr_col_name as $rowdata ) {
			$sql .= "," . $rowdata['COL_NAME'];
		}
		$sql .= " ";
	}

	//$sql .= "FROM KYOTEN_TBL ";	mod 2013/08/05 N.Wada [
	if ( $immref ) {
		$sql .= "FROM IM_KYOTEN_TBL ";
	} else {
		$sql .= "FROM KYOTEN_TBL ";
	}
	$sql .= "WHERE CORP_ID = '$key' ";
	// ���ϰϤǵ�Υ��¬�����ϰϤǤη�¬���ѹ�
	if ($rad) {		// 2007/06/27 add Y.Matsukawa
		$sql = $sql . "AND LAT >= (".$lat." - ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LAT <= (".$lat." + ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON >= (".$lon." - ((450000 / (11 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON <= (".$lon." + ((450000 / (11 * 1000)) * ".$rad.")) ";
	}
	
	if ( $jkn != "" ) { //������ͭ��ξ��
		$sql .= "AND $jkn ";
	}
	
	if ( $exkid != "") {
		$sql .= "AND KYOTEN_ID != '$exkid' ";
	}

	$sql .= "AND NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE ";

	$num = count( $arr_latlon );
	if ( $num > 0 ) {
		$sql .= "AND LAT >= '$arr_latlon[0]' AND LAT <= '$arr_latlon[2]' ";
		$sql .= "AND LON >= '$arr_latlon[1]' AND LON <= '$arr_latlon[3]' ";
	}

	$sql .= "ORDER BY KYORI,KYOTEN_ID ";
	$sql .= ") ";

	if (count($arr_rd_item) > 0) {
		foreach ($arr_rd_item as $g_no => $glist_array) {
			foreach ($glist_array as $item_no => $item_flg) {

				if ($rd_jkn != "") {
					$sql .= " INNER JOIN (SELECT ";
				} else {
					$sql .= " LEFT OUTER JOIN (SELECT ";
				}

				$sql .= "G.KYOTEN_ID AS KID,";
				$sql .= "G.GROUP_NO AS GNO,";
				$sql .= "I.ITEM_NO,";
				$sql .= "I.ITEM_NAME,";
				$sql .= "I.VAL_KBN,";
				$sql .= "D.TXT_DATA AS RDATA,";
				$sql .= "D.FLG_DATA,";
				$sql .= "D.IMG_W,";
				$sql .= "D.IMG_H ";

				$sql .= "FROM RD_ITEM_DEF_TBL I, RD_GROUP_DEF_TBL F, RD_DATA_TBL D, RD_GROUP_TBL G ";

				$sql .= "WHERE G.GROUP_NO = '".$g_no."' and I.ITEM_NO = '".$item_no."' ";
				$sql .= "and G.CORP_ID = '".$key."' ";
				$sql .= "and F.CORP_ID = '".$key."' ";
				$sql .= "and D.CORP_ID = '".$key."' ";
				$sql .= "and I.CORP_ID = '".$key."' ";
				$sql .= "and G.GROUP_NO = F.GROUP_NO ";
				$sql .= "and G.GROUP_NO = D.GROUP_NO ";
				$sql .= "and G.GROUP_NO = I.GROUP_NO ";
				$sql .= "and D.KYOTEN_ID = G.KYOTEN_ID ";
				$sql .= "and I.ITEM_NO = D.ITEM_NO ";
				$sql .= "and I.DEL_FLG = '0' ";
				$sql .= "and ( F.USE_KIKAN = '0' or ( nvl(to_char(G.ST_DT,'yyyymmddhh24'),'0') <= to_char(sysdate,'yyyymmddhh24') and nvl(to_char(G.ED_DT,'yyyymmddhh24'),'9999999999') > to_char(sysdate,'yyyymmddhh24') ) ) ";
				$sql .= "and G.GROUP_NO = ".$g_no.") ";
				$sql .= "RT".$g_no."_".$item_no." ON (KYOTEN_ID = RT".$g_no."_".$item_no.".KID) ";
			}
		}
	}

	$sql .= "WHERE ROWNUM <= $knsu";
	if ($absdist) {
		$sql .= " AND SQRT(KYORI) <= $absdist";
	}
	// Ǥ����������Ǥ���ϰϳ��ε��������
	if (is_array($exArea)) {
		$sql .= " AND SQRT(EX_KYORI) <= ".$exArea['rad'];
	}
	// �ꥢ�륿����ǡ����ιʤꤳ�߾����ɲä���
	if ($rd_jkn != "") {
		$sql .= " AND $rd_jkn ";
	}

	$stmt = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata_all = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata_all[] = $data;
	}
	
	if ($polycol) {
		// �ݥꥴ���⳰Ƚ��
		convexHullPoly($retdata_all, $polycol, $lat, $lon);
	}
	
	$hit_num = count ($retdata_all);

	if ( $hit_num <= 0 ) {
		$dba->free($stmt);
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);

	$retdata = array();
	for ( $ctr=$pos; $ctr<=$hit_num; $ctr++ ) {
		$retdata[] = $retdata_all[$ctr-1];
		if ( $ctr == ($pos + ($cnt-1)) ) {
			break;
		}
	}

	return  0;
}
// add 2015/01/16 F.Yoko ]

?>