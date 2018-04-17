<?php
/*========================================================*/
// 更新履歴
// 2013/02/20 Y.Matsukawa	新規作成
// 2015/01/16 F.Yokoi		RD項目設定データ取得

/*========================================================*/
/*==============================================*/
// RD利用設定を取得
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
// 表示区分でRDグループを検索
/*==============================================*/
function selectRDGroupByView(&$dba, $CID, $view) {
	$arr_grp = array();
	$sql  = "select";
	$sql .= " GROUP_NO";
	$sql .= " from RD_GROUP_DEF_TBL";
	$sql .= " where CORP_ID = '".$CID."'";
	switch ($view) {
		case 1:		// PC詳細
			$sql .= " and VIS_PCDTL = '1'";
			break;
		case 2:		// PC印刷
			$sql .= " and VIS_PCPRT = '1'";
			break;
		case 3:		// フキダシ
			$sql .= " and VIS_MSG = '1'";
			break;
		case 4:		// 携帯詳細
			$sql .= " and VIS_MBDTL = '1'";
			break;
		case 5:		// スマホ詳細
			$sql .= " and VIS_SMDTL = '1'";
			break;
		case 6:		// 一覧
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
// RDデータ検索
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
	// グループID指定
	if (count($arr_grp)) {
		if (count($arr_grp) == 1) {
			$sql .= " and G.GROUP_NO = ".$arr_grp[0];
		} else {
			$sql .= " and G.GROUP_NO in (".implode(',', $arr_grp).")";
		}
	}
	unset($arr_grp);
	// 拠点ID指定
	foreach ($arr_kid as $i => $kyotenid) {
		$arr_kid[$i] = "'".escapeOra($kyotenid)."'";
	}
	if (count($arr_kid) == 1) {
		$sql .= " and G.KYOTEN_ID = ".$arr_kid[0];
	} else if (count($arr_kid) > 0) {
		$sql .= " and G.KYOTEN_ID in (".implode(',', $arr_kid).")";
	}
	unset($arr_kid);
	// ソート
	$sql .= " order by G.KYOTEN_ID, G.GROUP_NO, I.DISP_NUM";
	// データ取得
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
// RD項目設定データ取得
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

	// データ取得
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
// 周辺データ取得
/*==============================================*/
function select_near_kyoten_rd( &$dba, $key, $lat, $lon, $arr_latlon, $rad,
	$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg, $absdist, &$exArea, $immref=false, $polycol, $arr_rd_item ,$rd_jkn ){
	//最寄り拠点リストを取得する。
	//  pos         取得開始位置
	//  cnt         取得件数
	//  hit_num     ヒット件数

	$sql = "SELECT KYOTEN_ID, LAT, LON, ICON_ID, KYORI, BFLG ";
	if ( count($arr_col_name) > 0 ) {	//空ではない場合
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
	// 任意地点からの距離		add 2013/08/02 Y.Matsukawa
	if (is_array($exArea)) {
		$sql .= "POWER( ABS( LAT - ".$exArea[lat]." ) * (  9 / 300000 * 1000 ), 2 ) + ";
		$sql .= "POWER( ABS( LON - ".$exArea[lon]." ) * ( 11 / 450000 * 1000 ), 2 ) AS EX_KYORI, ";
	}
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
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//空ではない場合
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
	// 円範囲で距離計測を矩形範囲での計測に変更
	if ($rad) {		// 2007/06/27 add Y.Matsukawa
		$sql = $sql . "AND LAT >= (".$lat." - ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LAT <= (".$lat." + ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON >= (".$lon." - ((450000 / (11 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON <= (".$lon." + ((450000 / (11 * 1000)) * ".$rad.")) ";
	}
	
	if ( $jkn != "" ) { //条件指定有りの場合
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
	// 任意地点から任意範囲外の拠点を除外
	if (is_array($exArea)) {
		$sql .= " AND SQRT(EX_KYORI) <= ".$exArea['rad'];
	}
	// リアルタイムデータの絞りこみ条件を追加する
	if ($rd_jkn != "") {
		$sql .= " AND $rd_jkn ";
	}

	$stmt = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$retdata_all = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata_all[] = $data;
	}
	
	if ($polycol) {
		// ポリゴン内外判定
		convexHullPoly($retdata_all, $polycol, $lat, $lon);
	}
	
	$hit_num = count ($retdata_all);

	if ( $hit_num <= 0 ) {
		$dba->free($stmt);
		return 1;   //検索結果データなし
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
