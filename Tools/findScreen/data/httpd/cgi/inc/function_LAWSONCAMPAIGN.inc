<?php
/*=========================================================*/
// ファイル名：function_LAWSONCAMPAIGN.inc
//
// ローソンキャンペーン対応【ｘｘｘｘ】カスタマイズ関数
// 
// 更新履歴
// 2017/04/12 H.Yasunaga	新規作成
/*=========================================================*/

	// ローソンキャンペーンのキャンペーンIDの存在チェック
	function exist_campaignid(&$dba, $campaignid) {
		$sql = "SELECT count(*) as CNT FROM LAWSON_CAMPAIGN_TBL where CPNID = '" . escapeOra($campaignid) . "'";
		$stmt = null;
		if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
			$dba->free($stmt);
			return null;   //sqlExecute()エラー
		}
		$retdata = 0;
		while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$retdata = $data['CNT'];
		}
		
		$dba->free($stmt);
		
		if (intval($retdata) > 0) {
			// キャンペーンIDが存在する
			return true;
		} else {
			// キャンペーンIDが存在しない
			return false;
		}
	}
	
	// 拠点検索時の条件にキャンペーンIDに紐づく店舗IDを対象にする
	function edit_jkn_campaign($edit_jkn, $campaignid) {
		
		$ret = "";
		if (strlen($edit_jkn) > 0) {
			$ret = $edit_jkn;
			$ret .= " AND ";
		}
		$ret .= "( kyoten_id in (select STOREID from LAWSON_CAMPAIGN_TBL where CPNID = '" . escapeOra($campaignid) . "') )";
		return $ret;
	}
?>