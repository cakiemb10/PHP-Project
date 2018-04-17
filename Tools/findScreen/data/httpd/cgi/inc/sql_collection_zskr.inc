<?php
/*========================================================*/
// ファイル名：sql_collection_zskr.inc
// 処理名：全国信用協同組合連合会専用信用組合検索SQL実装
//
// 作成日：2016/02/29
// 作成者：H.Yasunaga
// 全国信用協同組合連合会専用
//
// 更新履歴
// 2016/02/29 H.Yasunaga		新規作成
// 2016/03/20 H.Yasunaga		信用組合リストの全国フラグ付きをソート順の下に
// 2016/08/03 Y.Uesugi			「警察庁職員信用組合」「毎日信用組合」を検索しない
/*========================================================*/

// 住所コードに該当する信用組合のリストの取得
// 全国フラグが立っている信用組合も結果に含める
// ソート順：読みかな順・全国フラグ
function select_union_list(&$dba, $prefectures_code, $city_code, &$retdata) {
	$sql  = " SELECT ZSKR_UNION_TBL.* from ZSKR_UNION_TBL, ZSKR_UNION_JURISDICTION_TBL ";
	$sql .= " WHERE ZSKR_UNION_TBL.UNION_ID = ZSKR_UNION_JURISDICTION_TBL.UNION_ID ";
	$sql .= " AND (( ZSKR_UNION_JURISDICTION_TBL.PREFECTURES_CODE = '".$prefectures_code."' ";
	$sql .= " AND ZSKR_UNION_JURISDICTION_TBL.CITY_CODE = '".$city_code."')";
	$sql .= " OR ZSKR_UNION_TBL.NATION_WIDE_FLG = '1' )";
// add 2016/08/02 Y.Uesugi 「警察庁職員信用組合」「毎日信用組合」を検索しない [
	$sql .= " AND ZSKR_UNION_TBL.UNION_ID NOT IN ('2271','2581')";
// add 2016/08/02 Y.Uesugi 「警察庁職員信用組合」「毎日信用組合」を検索しない ]
	// mod 2016/03/20 H.Yasunaga ソート順の変更 [
	//$sql .= " ORDER by ZSKR_UNION_TBL.NATION_WIDE_FLG, NLSSORT(ZSKR_UNION_TBL.UNION_NAME_KANA,  'NLS_SORT=JAPANESE_M') ";
	$sql .= " ORDER by ZSKR_UNION_TBL.NATION_WIDE_FLG desc , NLSSORT(ZSKR_UNION_TBL.UNION_NAME_KANA,  'NLS_SORT=JAPANESE_M') ";
	// mod 2016/03/20 H.Yasunaga ]
	
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
		$dba->free($stmt);		
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}
// 信用組合識別子から信用組合の情報の取得
function select_union_id(&$dba, $union_id, &$retdata) {
	$sql  = " SELECT * ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE UNION_ID = '" . $union_id . "' ";
	
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
		$dba->free($stmt);		
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}
// 信用組合の管轄する市区町村名の取得（携帯版のみ使用）
// ソート順:都道府県コード・市区町村コード （数値順）
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
		return 9;   //sqlExecute()エラー
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

// カナ行別の信用組合のリストの取得
// ソート順：読みカナ
function select_union_kana(&$dba, $kana, &$retdata) {
	// KANA_CODE
	// あ行：１
	// か行：２
	// さ行：３
	// た行：４
	// な行：５
	// は行：６
	// ま行：７
	// や行：８
	// ら行：９
	// わ行：１０
	$sql  = " SELECT * ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = ";
	switch($kana) {
		case '10': {
			// あ行
			$sql .= "1";
			break;
		}
		case '11': {
			// か行
			$sql .= "2";
			break;
		}
		case '12':{
			// さ行
			$sql .= "3";
			break;
		}
		case '13':{
			// た行
			$sql .= "4";
			break;
		}
		case '14':{
			// な行
			$sql .= "5";
			break;
		}
		case '15':{
			// は行
			$sql .= "6";
			break;
		}
		case '16':{
			// ま行
			$sql .= "7";
			break;
		}
		case '17':{
			// や行
			$sql .= "8";
			break;
		}
		case '18':{
			// ら行
			$sql .= "9";
			break;
		}
		case '19': {
			// わ行
			$sql .= "10";
			break;
		}
	}
	$sql .= " ORDER BY NLSSORT(ZSKR_UNION_TBL.UNION_NAME_KANA,  'NLS_SORT=JAPANESE_M') ";
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
		$dba->free($stmt);		
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

// カナ行毎の信用組合の数の取得
function select_union_kana_cnt(&$dba, &$retdata) {
	// KANA_CODE
	// あ行：１
	// か行：２
	// さ行：３
	// た行：４
	// な行：５
	// は行：６
	// ま行：７
	// や行：８
	// ら行：９
	// わ行：１０

	$sql  = " SELECT ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 1";		// あ行
	$sql .= " ) as AROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 2";		// か行
	$sql .= " ) as KROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 3";		// さ行
	$sql .= " ) as SROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 4";		// た行
	$sql .= " ) as TROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 5";		// な行
	$sql .= " ) as NROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 6";		// は行
	$sql .= " ) as HROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 7";		// ま行
	$sql .= " ) as MROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 8";		// や行
	$sql .= " ) as YROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 9";		// ら行
	$sql .= " ) as RROW, ";
	$sql .= " ( ";
	$sql .= " SELECT COUNT(*) ";
	$sql .= " FROM ZSKR_UNION_TBL ";
	$sql .= " WHERE KANA_CODE = 10";	// わ行
	$sql .= " ) as WROW ";
	$sql .= " FROM DUAL ";

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
		$dba->free($stmt);		
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return  0;
}

?>
