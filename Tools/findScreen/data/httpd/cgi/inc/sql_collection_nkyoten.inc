<?php 
/*========================================================*/
// 更新履歴
// 2007/04/12 Y.Matsukawa	距離計測方法を、円範囲から矩形範囲に変更
// 2007/06/27 Y.Matsukawa	radに0を指定した場合は半径を考慮しない
// 2007/07/11 Y.Matsukawa	検索結果なしの時にリソース解放していなかった
// 2008/08/05 Y.Matsukawa	第２ソートキー（拠点ID）指定
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2009/10/13 Y.Matsukawa	最寄り拠点一覧に詳細拠点を出さない
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/10/15 H.Osamoto		検索範囲の指定を実距離で指定可能に変更
// 2013/08/02 Y.Matsukawa	任意地点から任意範囲外の拠点を除外
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2014/02/21 H.Osamoto		ポリゴン内外判定処理追加
// 2016/03/17 Y.Matsukawa	ソート指定
// 2016/03/10 Y.Matsukawa	円検索フラグ
/*========================================================*/

function select_col_name( &$dba, $cid, &$retdata, &$err_msg ){
	//CORP_IDをキーにKYOTEN_ITEM_TBLからCOL_NAMEをselectする

	// del 2009/09/04 Y.Matsukawa [
	//	$sql = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	//	$sql .= "WHERE CORP_ID = '$cid' AND ";
	// del 2009/09/04 Y.Matsukawa ]
	// add 2009/09/04 Y.Matsukawa [
	$sql0 = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	$sql0 .= "WHERE CORP_ID = '$cid' AND ";
	$sql = $sql0;
	// add 2009/09/04 Y.Matsukawa ]
	$sql .= "LIST_KBN = '1' ";
	$sql .= "ORDER BY DISP_NUM";
	$stmt = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[]  =   $data;
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

	$result = count ($retdata);
	if ( $result <= 0 ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //検索結果データなし
	}
	//$dba->free($stmt);		del 2009/09/04 Y.Matsukawa
	return  0;
}

function select_near_kyoten( &$dba, $key, $lat, $lon, $arr_latlon, $rad,
	//$arr_col_name, $jkn, $pos, $cnt, $knsu, &$hit_num, &$retdata, &$err_msg ){		mod 2009/10/13 Y.Matsukawa
	//$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg ){	mod 2012/10/15 H.Osamoto
	//$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg, $absdist ){		mod 2013/08/02 Y.Matsukawa
	//$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg, $absdist, &$exArea){		mod 2013/08/05 N.Wada
	//$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg, $absdist, &$exArea, $immref=false){		mod 2014/02/21 H.osamoto
	$arr_col_name, $jkn, $pos, $cnt, $knsu, $exkid, &$hit_num, &$retdata, &$err_msg, $absdist, &$exArea, $immref=false, $polycol
	, $sort		// add 2016/03/17 Y.Matsukawa
	, $circle	// add 2016/03/10 Y.Matsukawa
){
	//最寄り拠点リストを取得する。
	//  pos         取得開始位置
	//  cnt         取得件数
	//  hit_num     ヒット件数

	// mod 2011/07/05 Y.Nakajima [
	//$sql = "SELECT * ";
	$sql = "SELECT KYOTEN_ID, LAT, LON, ICON_ID, KYORI, BFLG ";
	if ( count($arr_col_name) > 0 ) {	//空ではない場合
		foreach( $arr_col_name as $rowdata ) {
			// mod 2011/07/05 Y.Nakajima
			$sql .= "," . $rowdata['COL_NAME'];
		}
		$sql .= " ";
	}
	// mod 2011/07/05 Y.Nakajima ]
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
	//$sql .= "END AS BFLG, ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//空ではない場合
		//$first_flg = 0;
		foreach( $arr_col_name as $rowdata ) {
			//	        if ( $first_flg == 0 ) {
			//	            $sql .= $rowdata[COL_NAME];
			//	            $first_flg = 1;
			//	        } else {
			//	            $sql .= "," . $rowdata[COL_NAME];
			//	        }
			// mod 2011/07/05 Y.Nakajima
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
	// mod 2013/08/05 N.Wada ]
	$sql .= "WHERE CORP_ID = '$key' ";
	// 円範囲で距離計測を矩形範囲での計測に変更
	//$sql    .=   "AND POWER( ABS( LAT - $lat ) * (  9 / 300000 * 1000 ), 2 ) + POWER( ABS( LON - $lon ) * ( 11 / 450000 * 1000 ), 2 ) < POWER( $rad, 2 ) ";
	if ($rad) {		// 2007/06/27 add Y.Matsukawa
		$sql = $sql . "AND LAT >= (".$lat." - ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LAT <= (".$lat." + ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON >= (".$lon." - ((450000 / (11 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON <= (".$lon." + ((450000 / (11 * 1000)) * ".$rad.")) ";
	}
	
	if ( $jkn != "" ) { //条件指定有りの場合
		$sql .= "AND $jkn ";
	}
	
	// add 2009/10/13 Y.Matsukawa [
	if ( $exkid != "") {
		$sql .= "AND KYOTEN_ID != '$exkid' ";
	}
	// add 2009/10/13 Y.Matsukawa ]

	$sql .= "AND NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE ";

	$num = count( $arr_latlon );
	if ( $num > 0 ) {
		$sql .= "AND LAT >= '$arr_latlon[0]' AND LAT <= '$arr_latlon[2]' ";
		$sql .= "AND LON >= '$arr_latlon[1]' AND LON <= '$arr_latlon[3]' ";
	}

	//$sql    .=   "ORDER BY KYORI ";		mod 2008/08/05 Y.Matsukawa
	$sql .= "ORDER BY KYORI,KYOTEN_ID ";
	$sql .= ") ";
	$sql .= "WHERE ROWNUM <= $knsu";
	if ($absdist) {
		$sql .= " AND SQRT(KYORI) <= $absdist";
	}
	// 指定半径の円で検索		add 2016/03/10 Y.Matsukawa
	if ($circle && $rad) {
		$sql .= " AND SQRT(KYORI) <= $rad";
	}
	// 任意地点から任意範囲外の拠点を除外		add 2013/08/02 Y.Matsukawa
	if (is_array($exArea)) {
		$sql .= " AND SQRT(EX_KYORI) <= ".$exArea['rad'];
	}
	if ($sort != '') $sql .= " ORDER BY ".$sort.",KYORI";		// add 2016/03/17 Y.Matsukawa

	$stmt = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$retdata_all = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata_all[] = $data;
	}
	
	// add 2014/02/21 H.Osamoto [
	if ($polycol) {
		// ポリゴン内外判定		add 2014/02/21 H.Osamoto
		convexHullPoly($retdata_all, $polycol, $lat, $lon);
	}
	// add 2014/02/21 H.Osamoto ]
	
	$hit_num = count ($retdata_all);

	if ( $hit_num <= 0 ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
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
?>
