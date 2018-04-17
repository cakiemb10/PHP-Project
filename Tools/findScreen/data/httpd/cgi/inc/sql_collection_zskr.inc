<?php
/*========================================================*/
// �ե�����̾��sql_collection_zskr.inc
// ����̾�������Ѷ�Ʊ�ȹ�Ϣ������ѿ����ȹ縡��SQL����
//
// ��������2016/02/29
// �����ԡ�H.Yasunaga
// �����Ѷ�Ʊ�ȹ�Ϣ�������
//
// ��������
// 2016/02/29 H.Yasunaga		��������
// 2016/03/20 H.Yasunaga		�����ȹ�ꥹ�Ȥ�����ե饰�դ��򥽡��Ƚ�β���
// 2016/08/03 Y.Uesugi			�ַٻ�ģ���������ȹ�ס����������ȹ�פ򸡺����ʤ�
/*========================================================*/

// ���ꥳ���ɤ˳������뿮���ȹ�Υꥹ�Ȥμ���
// ����ե饰��Ω�äƤ��뿮���ȹ���̤˴ޤ��
// �����Ƚ硧�ɤߤ��ʽ硦����ե饰
function select_union_list(&$dba, $prefectures_code, $city_code, &$retdata) {
	$sql  = " SELECT ZSKR_UNION_TBL.* from ZSKR_UNION_TBL, ZSKR_UNION_JURISDICTION_TBL ";
	$sql .= " WHERE ZSKR_UNION_TBL.UNION_ID = ZSKR_UNION_JURISDICTION_TBL.UNION_ID ";
	$sql .= " AND (( ZSKR_UNION_JURISDICTION_TBL.PREFECTURES_CODE = '".$prefectures_code."' ";
	$sql .= " AND ZSKR_UNION_JURISDICTION_TBL.CITY_CODE = '".$city_code."')";
	$sql .= " OR ZSKR_UNION_TBL.NATION_WIDE_FLG = '1' )";
// add 2016/08/02 Y.Uesugi �ַٻ�ģ���������ȹ�ס����������ȹ�פ򸡺����ʤ� [
	$sql .= " AND ZSKR_UNION_TBL.UNION_ID NOT IN ('2271','2581')";
// add 2016/08/02 Y.Uesugi �ַٻ�ģ���������ȹ�ס����������ȹ�פ򸡺����ʤ� ]
	// mod 2016/03/20 H.Yasunaga �����Ƚ���ѹ� [
	//$sql .= " ORDER by ZSKR_UNION_TBL.NATION_WIDE_FLG, NLSSORT(ZSKR_UNION_TBL.UNION_NAME_KANA,  'NLS_SORT=JAPANESE_M') ";
	$sql .= " ORDER by ZSKR_UNION_TBL.NATION_WIDE_FLG desc , NLSSORT(ZSKR_UNION_TBL.UNION_NAME_KANA,  'NLS_SORT=JAPANESE_M') ";
	// mod 2016/03/20 H.Yasunaga ]
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}
// �����ȹ缱�̻Ҥ��鿮���ȹ�ξ���μ���
function select_union_id(&$dba, $union_id, &$retdata) {
	$sql  = " SELECT * ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE UNION_ID = '" . $union_id . "' ";
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}
// �����ȹ�δɳ�����Զ�Į¼̾�μ����ʷ����ǤΤ߻��ѡ�
// �����Ƚ�:��ƻ�ܸ������ɡ��Զ�Į¼������ �ʿ��ͽ��
function select_union_jurisdiction(&$dba, $union_id, &$retdata) {
	$sql  = " SELECT ZSKR_PREFECTURES_TBL.*, ZSKR_BUSINESS_CATEGORY_TBL.DISPLAY_NAME as BC_DISPLAY_NAME ";
	$sql .= " FROM ZSKR_PREFECTURES_TBL, ZSKR_UNION_JURISDICTION_TBL, ZSKR_BUSINESS_CATEGORY_TBL ";
	$sql .= " WHERE ZSKR_UNION_JURISDICTION_TBL.UNION_ID = '" . $union_id . "' ";
	$sql .= " AND ZSKR_UNION_JURISDICTION_TBL.PREFECTURES_CODE = ZSKR_PREFECTURES_TBL.PREFECTURES_CODE ";
	$sql .= " AND ZSKR_UNION_JURISDICTION_TBL.CITY_CODE = ZSKR_PREFECTURES_TBL.CITY_CODE ";
	$sql .= " AND ZSKR_UNION_JURISDICTION_TBL.BUSINESS_CATEGORY_CODE = ZSKR_BUSINESS_CATEGORY_TBL.BUSINESS_CATEGORY_CODE ";
	$sql .= " ORDER BY ZSKR_PREFECTURES_TBL.PREFECTURES_CODE, ZSKR_PREFECTURES_TBL.CITY_CODE ";
	
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

// ���ʹ��̤ο����ȹ�Υꥹ�Ȥμ���
// �����Ƚ硧�ɤߥ���
function select_union_kana(&$dba, $kana, &$retdata) {
	// KANA_CODE
	// ���ԡ���
	// ���ԡ���
	// ���ԡ���
	// ���ԡ���
	// �ʹԡ���
	// �Ϲԡ���
	// �޹ԡ���
	// ��ԡ���
	// ��ԡ���
	// ��ԡ�����
	$sql  = " SELECT * ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = ";
	switch($kana) {
		case '10': {
			// ����
			$sql .= "1";
			break;
		}
		case '11': {
			// ����
			$sql .= "2";
			break;
		}
		case '12':{
			// ����
			$sql .= "3";
			break;
		}
		case '13':{
			// ����
			$sql .= "4";
			break;
		}
		case '14':{
			// �ʹ�
			$sql .= "5";
			break;
		}
		case '15':{
			// �Ϲ�
			$sql .= "6";
			break;
		}
		case '16':{
			// �޹�
			$sql .= "7";
			break;
		}
		case '17':{
			// ���
			$sql .= "8";
			break;
		}
		case '18':{
			// ���
			$sql .= "9";
			break;
		}
		case '19': {
			// ���
			$sql .= "10";
			break;
		}
	}
	$sql .= " ORDER BY NLSSORT(ZSKR_UNION_TBL.UNION_NAME_KANA,  'NLS_SORT=JAPANESE_M') ";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

// ���ʹ���ο����ȹ�ο��μ���
function select_union_kana_cnt(&$dba, &$retdata) {
	// KANA_CODE
	// ���ԡ���
	// ���ԡ���
	// ���ԡ���
	// ���ԡ���
	// �ʹԡ���
	// �Ϲԡ���
	// �޹ԡ���
	// ��ԡ���
	// ��ԡ���
	// ��ԡ�����

	$sql  = " SELECT ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 1";		// ����
	$sql .= " ) as AROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 2";		// ����
	$sql .= " ) as KROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 3";		// ����
	$sql .= " ) as SROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 4";		// ����
	$sql .= " ) as TROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 5";		// �ʹ�
	$sql .= " ) as NROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 6";		// �Ϲ�
	$sql .= " ) as HROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 7";		// �޹�
	$sql .= " ) as MROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 8";		// ���
	$sql .= " ) as YROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 9";		// ���
	$sql .= " ) as RROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 10";	// ���
	$sql .= " ) as WROW ";
	$sql .= " FROM DUAL ";

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

?>