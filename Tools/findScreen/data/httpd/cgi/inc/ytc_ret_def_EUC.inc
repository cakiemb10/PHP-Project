<?php
// ---------------------------------------------------------
// 【ヤマト運輸向けカスタマイズ】return_code定義
//
// 2016/04/25 T.Yoshino		yamatoCGI用	store_nearserch用リターンコード
// 2016/10/19 Y.Matsukawa	ヤマト運輸向け店頭受取API（ytc_store_nearsearch.cgi）対応
// ---------------------------------------------------------

function getYamatoRetCd( $RetKey ){
	
	// YAMATO専用status用意
	switch ( $RetKey ) {
		case "10000";
			$RetMsg = "要求されたAPIは現在、メンテナンス中です。";
			$RetMsgID = "ERROR_MAINTENANCE";
			$RetCd = "1";
			break;
			
		case "10001";
			$RetMsg = "認証キーが有効期限切れです。";
			$RetMsgID = "EXPIRY_ACCESS_TOKEN";
			$RetCd = "2";
			break;
			
		case "10002";
			$RetMsg = "アクセストークンが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_ACCESS_TOKEN";
			$RetCd = "3";
			break;
			
		case "10003";
			$RetMsg = "要求されたAPIは現在、緊急メンテナンス中です。";
			$RetMsgID = "URGENT_MAINTENANCE";
			$RetCd = "5";
			break;
			
		case "10004";
			$RetMsg = "検索対象フラグが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "00000";
			$RetMsg = "条件に見合うデータがありました。";
			$RetMsgID = "SEARCH_RESULT";
			$RetCd = "0";
			break;
			
		case "00001";
			$RetMsg = "条件に見合うデータはありませんでした。";
			$RetMsgID = "NO_SEARCH_RESULT";
			$RetCd = "0";
			break;
			
		case "01000";
			$RetMsg = "店舗データベースアクセスエラーです。";
			$RetMsgID = "ERROR_TENPO_DB";
			$RetCd = "-1";
			break;
			
		case "01001";
			$RetMsg = "認証エラーです。";
			$RetMsgID = "ERROR_AUTH";
			$RetCd = "4";
			break;
			
		case "01002";
			$RetMsg = "検索対象フラグが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_SEARCH_KBN";
			$RetCd = "3";
			break;
			
		case "01003";
			$RetMsg = "内部的な予期しない問題により要求を正しく処理できませんでした。";
			$RetMsgID = "ERROR_SYSTEM";
			$RetCd = "-1";
			break;
			
		case "09000";
			$RetMsg = "検索必須項目（郵便番号及び緯度・経度）が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09001";
			$RetMsg = "企業IDが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09002";
			$RetMsg = "検索必須項目（郵便番号及び緯度・経度）が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09003";
			$RetMsg = "検索必須項目（郵便番号及び緯度・経度）が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09004";
			$RetMsg = "郵便番号が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09005";
			$RetMsg = "北東（右上）緯度が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09006";
			$RetMsg = "北東（右上）経度が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09007";
			$RetMsg = "南西（左下）緯度が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09008";
			$RetMsg = "南西（左下）経度が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09009";
			$RetMsg = "東西距離（経度）が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09010";
			$RetMsg = " 南北距離（緯度）が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		// add 2016/10/19 Y.Matsukawa [
		case "99001";
			$RetMsg = "配達担当店の店舗コードが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99002";
			$RetMsg = "店舗種別が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99003";
			$RetMsg = "商品判定区分が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99004";
			$RetMsg = "受取可能日時の起算日が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99005";
			$RetMsg = "到着便数が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99006";
			$RetMsg = "取得件数が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99007";
			$RetMsg = "ソート順が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99008";
			$RetMsg = "文字コードが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99009";
			$RetMsg = "ポイントフラグが空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99010";
			$RetMsg = "測地系が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99011";
			$RetMsg = "出力形式が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99012";
			$RetMsg = "クール便の保管期限を過ぎています。";
			$RetMsgID = "EXPIRE_COOL";
			$RetCd = "3";
			break;
			
		// add 2016/10/19 Y.Matsukawa ]
	}
	
	return array($RetMsg,$RetMsgID,$RetCd);

}
?>
