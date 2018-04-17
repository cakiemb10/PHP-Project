<?php 
/*========================================================*/
// ��������
// 2007/04/12 Y.Matsukawa	��Υ��¬��ˡ�򡢱��ϰϤ������ϰϤ��ѹ�
// 2007/06/27 Y.Matsukawa	rad��0����ꤷ������Ⱦ�¤��θ���ʤ�
// 2007/07/11 Y.Matsukawa	������̤ʤ��λ��˥꥽�����������Ƥ��ʤ��ä�
// 2008/08/05 Y.Matsukawa	�裲�����ȥ����ʵ���ID�˻���
// 2009/09/04 Y.Matsukawa	�����̼�
// 2009/10/13 Y.Matsukawa	�Ǵ����������˾ܺٵ�����Ф��ʤ�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/10/15 H.Osamoto		�����ϰϤλ����µ�Υ�ǻ����ǽ���ѹ�
// 2013/08/02 Y.Matsukawa	Ǥ����������Ǥ���ϰϳ��ε��������
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2014/02/21 H.Osamoto		�ݥꥴ���⳰Ƚ������ɲ�
// 2016/03/17 Y.Matsukawa	�����Ȼ���
// 2016/03/10 Y.Matsukawa	�߸����ե饰
/*========================================================*/

function select_col_name( &$dba, $cid, &$retdata, &$err_msg ){
	//CORP_ID�򥭡���KYOTEN_ITEM_TBL����COL_NAME��select����

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
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata[]  =   $data;
	}
	// add 2009/09/04 Y.Matsukawa [
	$dba->free($stmt);

	//PC�̼ܥ����
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

	//���ӽ̼ܥ����
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
		return 1;   //������̥ǡ����ʤ�
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
	//�Ǵ������ꥹ�Ȥ�������롣
	//  pos         �������ϰ���
	//  cnt         �������
	//  hit_num     �ҥåȷ��

	// mod 2011/07/05 Y.Nakajima [
	//$sql = "SELECT * ";
	$sql = "SELECT KYOTEN_ID, LAT, LON, ICON_ID, KYORI, BFLG ";
	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
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
	//$sql .= "END AS BFLG, ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
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
	// ���ϰϤǵ�Υ��¬�����ϰϤǤη�¬���ѹ�
	//$sql    .=   "AND POWER( ABS( LAT - $lat ) * (  9 / 300000 * 1000 ), 2 ) + POWER( ABS( LON - $lon ) * ( 11 / 450000 * 1000 ), 2 ) < POWER( $rad, 2 ) ";
	if ($rad) {		// 2007/06/27 add Y.Matsukawa
		$sql = $sql . "AND LAT >= (".$lat." - ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LAT <= (".$lat." + ((300000 / (9 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON >= (".$lon." - ((450000 / (11 * 1000)) * ".$rad.")) ";
		$sql = $sql . "AND LON <= (".$lon." + ((450000 / (11 * 1000)) * ".$rad.")) ";
	}
	
	if ( $jkn != "" ) { //������ͭ��ξ��
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
	// ����Ⱦ�¤αߤǸ���		add 2016/03/10 Y.Matsukawa
	if ($circle && $rad) {
		$sql .= " AND SQRT(KYORI) <= $rad";
	}
	// Ǥ����������Ǥ���ϰϳ��ε��������		add 2013/08/02 Y.Matsukawa
	if (is_array($exArea)) {
		$sql .= " AND SQRT(EX_KYORI) <= ".$exArea['rad'];
	}
	if ($sort != '') $sql .= " ORDER BY ".$sort.",KYORI";		// add 2016/03/17 Y.Matsukawa

	$stmt = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata_all = array();
	while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
		$retdata_all[] = $data;
	}
	
	// add 2014/02/21 H.Osamoto [
	if ($polycol) {
		// �ݥꥴ���⳰Ƚ��		add 2014/02/21 H.Osamoto
		convexHullPoly($retdata_all, $polycol, $lat, $lon);
	}
	// add 2014/02/21 H.Osamoto ]
	
	$hit_num = count ($retdata_all);

	if ( $hit_num <= 0 ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
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
?>