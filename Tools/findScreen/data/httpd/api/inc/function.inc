<?php
/*=========================================================*/
// ファイル名：function.inc
//
// 共通関数
//
// 作成日：2010/01/08
// 作成者：Y.Matsukawa
//
// 解説：共通関数
//
// 更新履歴
// 2010/01/08 Y.Matsukawa	新規作成
// 2012/11/13 Y.Matsukawa	JCN満空情報取得
// 2013/02/20 H.Osamoto		スマホアプリ向け絞込み条件取得処理追加
// 2013/08/05 N.Wada		即時リフレッシュ対象設定を取得
// 2013/11/13 H.Osamoto		スマホアプリ向け絞込み条件取得処理変更（カスタマイズ条件なしの場合、DB設定からの自動生成をやめる）
// 2013/12/20 H.Osamoto		データ参照先企業ID取得
// 2014/02/21 H.Osamoto		ポリゴン内外判定処理追加
// 2014/04/28 H.Osamoto		ルート距離算出処理追加
// 2014/10/02 H.Osamoto		ルート距離算出時に有料道路を利用しないよう変更
/*=========================================================*/
require_once('/home/emap/src/Jsphon/Decoder.php');		// add 2012/11/13 Y.Matsukawa

// add 2013/02/27 Y.Matsukawa
// ------------------------------------------------------------
// デバッグ情報出力
// ------------------------------------------------------------
function dbl($str){
	global $D_DEBUG;
	if(!$D_DEBUG){ return; }
	@error_log(date('Y/m/d H:i:s').'['.$_SERVER['SCRIPT_NAME'].']'.$str."\n", 3, '/var/tmp/cgi_debug_'.date('Ymd').'.log');
}

/*==============================================*/
// POST, GET の順でパラメータを取得して返す
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
// Oracleエスケープ（シングルクォート）
/*==============================================*/
function escapeOra($str) {
	return mb_ereg_replace("'", "''", $str);
}

// add 2012/11/13 Y.Matsukawa
/*==============================================*/
// JCN満空情報取得
/*==============================================*/
function JCNGetSpotStatus(&$arr_kyoten) {
	global $D_JCN_URL, $D_JCN_PXY;
	global $D_APIPROXY;
	$cnt = count($arr_kyoten);
	if (!$cnt) return false;
	// 取得対象の拠点ID
	$arr_kid = array();
	for ($i = 0; $i < $cnt; $i++) {
		$arr_kid[] = $arr_kyoten[$i]['KYOTEN_ID'];
	}
	// JCN満空情報取得
	if ($D_JCN_PXY['ChargingSpotStatusZDC']) {
		$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];
	} else {
		$host = '';
	}
	$url = $D_JCN_URL['ChargingSpotStatusZDC'];
	$url .= '?spotId='.implode(',', $arr_kid);
	$dat = ZdcHttpSimpleRead($url, $host);
	if ($dat != '') {
		// JSONデコード
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
				// 利用可能台数を算出
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
// 絞込み条件取得
/*==============================================*/
function getCondPattern( &$dba, $cid, &$retdata ) {
	// カスタマイズ条件取得
	$retcd = select_cstm_cond_ptn( $dba, $cid, $retdata );

	// del 2013/11/13 H.Osamoto [
	//	if ( $retcd != 0 ) {
	//		if ( $retcd == 9 ) {
	//			return $retcd;
	//		} else {
	//			// カスタマイズ条件なしの場合、DB設定から生成
	//			$retcd = getCondCol( &$dba, $cid, &$retdata );
	//		}
	//	}
	// del 2013/11/13 H.Osamoto ]
	return $retcd;
}

// del 2013/11/13 H.Osamoto [
//	// add 2013/02/20 H.Osamoto
//	/*==============================================*/
//	// 検索条件カラム取得
//	/*==============================================*/
//	function getCondCol( &$dba, $cid, &$retdata ) {
//		// 検索条件カラム取得
//		$retcd = select_cond_kyoten_item_tbl( $dba, $cid, $a_conddata );
//		if ( $retcd != 0 ) {
//			return $retcd;
//		}
//		
//		foreach ($a_conddata as $key => $dat) {
//			if ($dat['type'] == "L") {
//				// リスト項目の場合
//				
//				// リスト項目取得にて使用するので退避
//				$col = $dat['val'];
//				
//				// カラム名は不要なので削除
//				unset($a_conddata[$key]['val']);
//				
//				// リスト項目取得
//				$retcd = select_cond_kyoten_item_val_tbl( $dba, $cid, $col, $a_itemvaldata );
//				if ( $retcd != 0 ) {
//					return $retcd;
//				}
//				
//				// 配列の先頭にデフォルトのアイテム（リストボックスの絞込みなし）を追加
//				array_unshift($a_itemvaldata, array("text" => "指定しない", "val" => ""));
//				
//				// データ配列にセット
//				$a_conddata[$key]['opts'] = $a_itemvaldata;
//				
//				// 返却配列にセット
//				$a_itemdata['list'][] = $a_conddata[$key];
//			} else if ($dat['type'] == "F") {
//				// フラグ項目の場合
//				
//				// 固定値をセット
//				$a_conddata[$key]['val'] .= ":1";
//				
//				// 返却配列にセット
//				$a_itemdata['flg'][] = $a_conddata[$key];
//			}
//		}
//
//		// 配列データを出力用フォーマットに変換
//		$a_tmp = cnvOutputJsonFormat($a_itemdata);
//		
//		// jsonクラス
//		$json = new Jsphon_Encoder(false, false);
//		
//		// 絞込み条件（配列）をJSON形式に変換
//		$retdata = $json->encode($a_tmp);
//		$retdata = trimJson($retdata);
//		
//		return 0;
//	}
//
//	// add 2013/02/20 H.Osamoto
//	/*==============================================*/
//	// 配列データを出力用フォーマットに変換（配列⇒配列）
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
//	// JSON形式の先頭と終端囲み文字を削除
//	/*==============================================*/
//	function trimJson( $s_data ) {
//
//		return substr($s_data, 1, (strlen($s_data) -2));
//	}
// del 2013/11/13 H.Osamoto ]

// add 2013/02/20 H.Osamoto
/*==============================================*/
// JSONのステータス部を出力
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
// 即時リフレッシュ対象設定を取得
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
// データ参照先企業ID取得
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
// ポリゴン内外判定
/*==============================================*/
function convexHullPoly(&$arr_kyoten, $poly_col, $lat, $lon) {
	$cnt = count($arr_kyoten);
	if (!$cnt) return false;

	$reader = new GEOSWKTReader();
	$writer = new GEOSWKTWriter();
	$writer->setRoundingPrecision(0);
	
	foreach($arr_kyoten as $key => $kyoten) {
		// ポリゴンデータがない場合は除外
		if (!isset($kyoten[$poly_col])) {
			unset($arr_kyoten[$key]);
			continue;
		}
		// 判定用ポリゴン取得変換
		$poly_str = str_replace(';', ',', $kyoten[$poly_col]);
		
		$g1 = $reader->read('POLYGON(('.$poly_str.'))');
		$g2 = $reader->read('POINT('.$lat.' '.$lon.')');
		
		// 内外判定
		$retAssert = $g1->contains($g2);
		
		if ($retAssert == "") {
			unset($arr_kyoten[$key]);
		}
	}
	
	// 削除したキー詰め
	$arr_kyoten = array_values($arr_kyoten);
	
	return true;
}

// add 2014/04/28 H.Osamoto
// ルート距離算出
function getRouteDistance($slat, $slon, $elat, $elon) {
	global $D_SSAPI;
	global $D_SSAPI_KEY;
	// ルートCGI
	//	$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $slat, $slon, $elat, $elon);	mod 2014/10/02 H.osamoto
	$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s&chg=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $slat, $slon, $elat, $elon, 0);
	$xml = file_get_contents($url);
	$dat = simplexml_load_string($xml);
	
	return $dat->status->distance;
}

?>
