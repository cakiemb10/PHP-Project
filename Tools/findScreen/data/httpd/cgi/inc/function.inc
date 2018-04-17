<?php
/*=========================================================*/
// �ե�����̾��function.inc
//
// ���̴ؿ�
//
// ��������2010/01/08
// �����ԡ�Y.Matsukawa
//
// ���⡧���̴ؿ�
//
// ��������
// 2010/01/08 Y.Matsukawa	��������
// 2012/11/13 Y.Matsukawa	JCN�����������
// 2013/02/20 H.Osamoto		���ޥۥ��ץ�����ʹ��߾����������ɲ�
// 2013/08/05 N.Wada		¨����ե�å����о���������
// 2013/11/13 H.Osamoto		���ޥۥ��ץ�����ʹ��߾����������ѹ��ʥ������ޥ������ʤ��ξ�硢DB���꤫��μ�ư����������
// 2013/12/20 H.Osamoto		�ǡ�����������ID����
// 2014/02/21 H.Osamoto		�ݥꥴ���⳰Ƚ������ɲ�
// 2014/04/28 H.Osamoto		�롼�ȵ�Υ���н����ɲ�
// 2014/10/02 H.Osamoto		�롼�ȵ�Υ���л���ͭ��ƻϩ�����Ѥ��ʤ��褦�ѹ�
/*=========================================================*/
require_once('/home/emap/src/Jsphon/Decoder.php');		// add 2012/11/13 Y.Matsukawa

// add 2013/02/27 Y.Matsukawa
// ------------------------------------------------------------
// �ǥХå��������
// ------------------------------------------------------------
function dbl($str){
	global $D_DEBUG;
	if(!$D_DEBUG){ return; }
	@error_log(date('Y/m/d H:i:s').'['.$_SERVER['SCRIPT_NAME'].']'.$str."\n", 3, '/var/tmp/cgi_debug_'.date('Ymd').'.log');
}

/*==============================================*/
// POST, GET �ν�ǥѥ�᡼������������֤�
/*==============================================*/
function getCgiParameter($name, $defaultValue) {
	if (isset($_POST[$name])&&strlen($_POST[$name])>0) {
		return $_POST[$name];
	}
	if (isset($_GET[$name])&&strlen($_GET[$name])>0) {
		return $_GET[$name];
	}
	return $defaultValue;
}

/*==============================================*/
// Oracle���������סʥ��󥰥륯�����ȡ�
/*==============================================*/
function escapeOra($str) {
	return mb_ereg_replace("'", "''", $str);
}

// add 2012/11/13 Y.Matsukawa
/*==============================================*/
// JCN�����������
/*==============================================*/
function JCNGetSpotStatus(&$arr_kyoten) {
	global $D_JCN_URL, $D_JCN_PXY;
	global $D_APIPROXY;
	$cnt = count($arr_kyoten);
	if (!$cnt) return false;
	// �����оݤε���ID
	$arr_kid = array();
	for ($i = 0; $i < $cnt; $i++) {
		$arr_kid[] = $arr_kyoten[$i]['KYOTEN_ID'];
	}
	// JCN�����������
	if ($D_JCN_PXY['ChargingSpotStatusZDC']) {
		$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];
	} else {
		$host = '';
	}
	$url = $D_JCN_URL['ChargingSpotStatusZDC'];
	$url .= '?spotId='.implode(',', $arr_kid);
	$dat = ZdcHttpSimpleRead($url, $host);
	if ($dat != '') {
		// JSON�ǥ�����
		$json = new Jsphon_Decoder();
		$arr_data = $json->decode($dat[0]);
		if (!$arr_data || !is_array($arr_data)) return false;
		if ($arr_data['retCode'] != 0) return false;
		$arr_spot = $arr_data['spotList'];
		if (!isset($arr_spot) || !is_array($arr_spot) || !count($arr_spot)) return false;
		unset($arr_data);
		$spot = array();
		foreach ($arr_spot as $i => $sp) {
			$spot[$sp['spotId']] = $sp;
		}
		unset($arr_spot);
		for ($i = 0; $i < $cnt; $i++) {
			$sp = $spot[$arr_kyoten[$i]['KYOTEN_ID']];
			if ($sp) {
				$arr_kyoten[$i]['JCN_SPOT_STATUS'] = $sp['spotStatus'];
				if ($sp['spotStatusIcon'] != '') $arr_kyoten[$i]['ICON_ID'] = $sp['spotStatusIcon'];
				// ���Ѳ�ǽ����򻻽�
				$avl_count = 0;
				$chargerList = $sp['chargerList'];
				if ($chargerList && is_array($chargerList) && count($chargerList)) {
					foreach ($chargerList as $charger) {
						if (isset($charger['chargerStatus']) && $charger['chargerStatus'] == '0') {
							$avl_count++;
						}
					}
				}
				$arr_kyoten[$i]['JCN_SPOT_AVL_COUNT'] = $avl_count;
			}
		}
	} else {
		return false;
	}
	return true;
}

// add 2013/02/20 H.Osamoto
/*==============================================*/
// �ʹ��߾�����
/*==============================================*/
function getCondPattern( &$dba, $cid, &$retdata ) {
	// �������ޥ���������
	$retcd = select_cstm_cond_ptn( $dba, $cid, $retdata );

	// del 2013/11/13 H.Osamoto [
	//	if ( $retcd != 0 ) {
	//		if ( $retcd == 9 ) {
	//			return $retcd;
	//		} else {
	//			// �������ޥ������ʤ��ξ�硢DB���꤫������
	//			$retcd = getCondCol( &$dba, $cid, &$retdata );
	//		}
	//	}
	// del 2013/11/13 H.Osamoto ]
	return $retcd;
}

// del 2013/11/13 H.Osamoto [
//	// add 2013/02/20 H.Osamoto
//	/*==============================================*/
//	// ������參������
//	/*==============================================*/
//	function getCondCol( &$dba, $cid, &$retdata ) {
//		// ������參������
//		$retcd = select_cond_kyoten_item_tbl( $dba, $cid, $a_conddata );
//		if ( $retcd != 0 ) {
//			return $retcd;
//		}
//		
//		foreach ($a_conddata as $key => $dat) {
//			if ($dat['type'] == "L") {
//				// �ꥹ�ȹ��ܤξ��
//				
//				// �ꥹ�ȹ��ܼ����ˤƻ��Ѥ���Τ�����
//				$col = $dat['val'];
//				
//				// �����̾�����פʤΤǺ��
//				unset($a_conddata[$key]['val']);
//				
//				// �ꥹ�ȹ��ܼ���
//				$retcd = select_cond_kyoten_item_val_tbl( $dba, $cid, $col, $a_itemvaldata );
//				if ( $retcd != 0 ) {
//					return $retcd;
//				}
//				
//				// �������Ƭ�˥ǥե���ȤΥ����ƥ�ʥꥹ�ȥܥå����ιʹ��ߤʤ��ˤ��ɲ�
//				array_unshift($a_itemvaldata, array("text" => "���ꤷ�ʤ�", "val" => ""));
//				
//				// �ǡ�������˥��å�
//				$a_conddata[$key]['opts'] = $a_itemvaldata;
//				
//				// �ֵ�����˥��å�
//				$a_itemdata['list'][] = $a_conddata[$key];
//			} else if ($dat['type'] == "F") {
//				// �ե饰���ܤξ��
//				
//				// �����ͤ򥻥å�
//				$a_conddata[$key]['val'] .= ":1";
//				
//				// �ֵ�����˥��å�
//				$a_itemdata['flg'][] = $a_conddata[$key];
//			}
//		}
//
//		// ����ǡ���������ѥե����ޥåȤ��Ѵ�
//		$a_tmp = cnvOutputJsonFormat($a_itemdata);
//		
//		// json���饹
//		$json = new Jsphon_Encoder(false, false);
//		
//		// �ʹ��߾�������ˤ�JSON�������Ѵ�
//		$retdata = $json->encode($a_tmp);
//		$retdata = trimJson($retdata);
//		
//		return 0;
//	}
//
//	// add 2013/02/20 H.Osamoto
//	/*==============================================*/
//	// ����ǡ���������ѥե����ޥåȤ��Ѵ�������������
//	/*==============================================*/
//	function cnvOutputJsonFormat( $a_data ) {
//		
//		$wdata = array();
//		$retdata = array();
//		$cnt = 0;
//		
//		
//		foreach ($a_data as $key => $dat) {
//			if ($key == "flg") {
//				//
//				$wdata[$cnt][D_JOIN] = D_DEF_JOIN_FLG;
//				$wdata[$cnt][D_ITEM] = $dat;
//				$cnt++;
//			} else if ($key == "list") {
//				//
//				$wdata[$cnt][D_JOIN] = D_DEF_JOIN_LST;
//				$wdata[$cnt][D_ITEM] = $dat;
//				$cnt++;
//			}
//		}
//		
//		$retdata[D_COND] = array(D_JOIN => D_DEF_JOIN_GRP, D_GRP => $wdata);
//		
//		
//		return $retdata;
//	}
//
//	// add 2013/02/20 H.Osamoto
//	/*==============================================*/
//	// JSON��������Ƭ�Ƚ�ü�Ϥ�ʸ������
//	/*==============================================*/
//	function trimJson( $s_data ) {
//
//		return substr($s_data, 1, (strlen($s_data) -2));
//	}
// del 2013/11/13 H.Osamoto ]

// add 2013/02/20 H.Osamoto
/*==============================================*/
// JSON�Υ��ơ������������
/*==============================================*/
function outputJsonStatus( $s_data, $status ) {

	$tmpstr1 = "{\"".D_RET_CODE."\":\"".$status."\"";
	$tmpstr2 = "}";
	
	if ($s_data) {
		$tmpstr1 .= ",";
		$retstr = $tmpstr1.$s_data.$tmpstr2;
	} else {
		$retstr = $tmpstr1.$tmpstr2;
	}
	return $retstr;
}

// add 2013/08/05 N.Wada
/*==============================================*/
// ¨����ե�å����о���������
/*==============================================*/
function isIMMREFAvailable(&$dba, $CID) {
	if (strtolower($dba->tns) != 'pub') return false;
	$sql = "select VALUE from EMAP_PARM_TBL";
	$sql .= " where CORP_ID = '".$CID."'";
	$sql .= " and KBN = 'IMMREF'";
	$stmt = null;
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
// add 2013/12/20 H.Osamoto
/*==============================================*/
// �ǡ�����������ID����
/*==============================================*/
function getDataCid(&$dba, $CID) {
	$retCID = $CID;
	$sql = "select VALUE from EMAP_PARM_TBL";
	$sql .= " where CORP_ID = '".$CID."'";
	$sql .= " and KBN = 'DATA_CID'";
	$stmt = null;
	if ($dba->sqlExecute($sql, $stmt)) {
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if($data['VALUE'] != '') {
				$retCID = $data['VALUE'];
				if (strpos($CID, 'test')) {
					$retCID .= 'test';
				}
			}
		}
	}
	$dba->free($stmt);
	
	return $retCID;
}

// add 2014/02/21 H.Osamoto
/*==============================================*/
// �ݥꥴ���⳰Ƚ��
/*==============================================*/
function convexHullPoly(&$arr_kyoten, $poly_col, $lat, $lon) {
	$cnt = count($arr_kyoten);
	if (!$cnt) return false;

	$reader = new GEOSWKTReader();
	$writer = new GEOSWKTWriter();
	$writer->setRoundingPrecision(0);
	
	foreach($arr_kyoten as $key => $kyoten) {
		// �ݥꥴ��ǡ������ʤ����Ͻ���
		if (!isset($kyoten[$poly_col])) {
			unset($arr_kyoten[$key]);
			continue;
		}
		// Ƚ���ѥݥꥴ������Ѵ�
		$poly_str = str_replace(';', ',', $kyoten[$poly_col]);
		
		$g1 = $reader->read('POLYGON(('.$poly_str.'))');
		$g2 = $reader->read('POINT('.$lat.' '.$lon.')');
		
		// �⳰Ƚ��
		$retAssert = $g1->contains($g2);
		
		if ($retAssert == "") {
			unset($arr_kyoten[$key]);
		}
	}
	
	// ������������ͤ�
	$arr_kyoten = array_values($arr_kyoten);
	
	return true;
}

// add 2014/04/28 H.Osamoto
// �롼�ȵ�Υ����
function getRouteDistance($slat, $slon, $elat, $elon) {
	global $D_SSAPI;
	global $D_SSAPI_KEY;
	// �롼��CGI
	//	$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $slat, $slon, $elat, $elon);	mod 2014/10/02 H.osamoto
	$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s&chg=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $slat, $slon, $elat, $elon, 0);
	$xml = file_get_contents($url);
	$dat = simplexml_load_string($xml);
	
	return $dat->status->distance;
}

?>