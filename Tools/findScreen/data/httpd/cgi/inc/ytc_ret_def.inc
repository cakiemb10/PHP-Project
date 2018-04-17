<?php
// ---------------------------------------------------------
// 【ヤマト運輸向けカスタマイズ】return_code定義
//
// 2016/04/25 T.Yoshino		yamatoCGI用	store_nearserch用リターンコード
// 2016/12/12 H.Yasunaga	ヤマトロッカー対応用のstatusを追加
// 2017/01/17 H.Yasunaga	ytc_ret_def.incファイルの文字コードをUTF-8からEUCに変更
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
			$RetMsg = "アクセストークンが有効期限切れです。";
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
			
		// add 2016/12/12 H.Yasunaga ロッカー対応 [
		case "09011";
			// Kパラメータ(17バイト目)が"1"の場合に出荷予定日が必須になり、出荷予定日パラメータが無いor不正
			$RetMsg = "出荷予定日が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
		case "09012";
			// Kパラメータ(17バイト目)が"1"の場合に発地郵便番号が必須になり、発地郵便番号パラメータが無いor不正
			$RetMsg = "発地郵便番号が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
		case "09013";
			// Kパラメータ(17バイト目)が"1"の場合にボックスサイズ区分が必須になり、ボックスサイズ区分パラメータが無いor不正
			$RetMsg = "ボックスサイズ区分が空、もしくは不正な値です。";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
		// add ]
			
	}
	
	return array($RetMsg,$RetMsgID,$RetCd);

}
?>
