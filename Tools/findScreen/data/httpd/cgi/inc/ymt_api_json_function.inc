<?php
/*========================================================*/
// ファイル名：ymt_api_json_function.inc
// 処理名：ヤマトロッカー満空APIのリクエスト処理
//
// 作成日：2016/12/12
// 作成者：H.Yasunaga
//
// 解説：ヤマトロッカー満空APIのリクエストを行う
//
// 更新履歴
// 2016/12/12 H.Yasunaga		新規作成
// 2016/12/15 H.Yasunaga		PHP4でエラーになるため、Jsphonライブラリのファイルのrequire_onceを削除
//								プロキシを経由せずにヤマトロッカーAPIへのアクセスに変更
// 2017/03/22 H.Yasunaga		ロッカー満空APIのURLをhostnameによって切り替える
//								本番環境時はAPIのアクセスをwgetコマンドを利用する
/*========================================================*/
	// JSONを扱うライブラリ
	require_once("/home/emap/src/Jsphon/Decoder.php");
	require_once("/home/emap/src/Jsphon/Encoder.php");
	// del 2016/12/15 H.Yasunaga PHP5では必要だが、PHP4ではエラーになるため削除 [
	//require_once("/home/emap/src/Jsphon/Error.php");
	//require_once("/home/emap/src/Jsphon/Exception.php");
	// del 2016/12/15 H.Yasunaga ]
	
	// 満空確認API JSONのキー定義
	define("YMT_API_KEY_PARAMETER", 			"checkEmptyParameter");	// リクエストTOPレベルのキー	[リクエスト]
	define("YMT_API_KEY_REQUEST_HEADER",		"requestHeader");		// リクエスト共通情報のキー		[リクエスト]
	define("YMT_API_KEY_SYSTEM_ID",				"systemId");			// システムIDのキー				[リクエスト]
	define("YMT_API_KEY_RESERVE_TIMESTAMP",		"reserveTimestamp");	// 依頼日時のキー				[リクエスト]
	define("YMT_API_KEY_REQUEST_INFO",			"requestInfo");			// 処理固有部のキー				[リクエスト]
	define("YMT_API_KEY_SEARCH_FLG",			"searchFlg");			// 検索フラグのキー				[リクエスト]
	define("YMT_API_KEY_LOCKER_LIST",			"lockerList");			// ロッカー情報リストのキー		[リクエスト]
	define("YMT_API_KEY_COMPANY_ID",			"companyId");			// 企業IDのキー					[共通]
	define("YMT_API_KEY_LOCKER_ID",				"lockerId");			// ロッカーIDのキー				[共通]
	define("YMT_API_KEY_KOKYAKU_CD",			"kokyakuCd");			// 顧客CDのキー					[共通]
	define("YMT_API_KEY_SHUKKA_YOTEI_DATE",		"shukkaYoteiDate");		// 出荷予定日のキー				[リクエスト]
	define("YMT_API_KEY_NOHIN_YOTEI_DATE",		"nohinYoteiDate");		// 納品予定日のキー				[リクエスト]
	define("YMT_API_KEY_HATCHI_YUBIN_NO",		"hatchiYubinNo");		// 発地郵便番号のキー			[リクエスト]
	define("YMT_API_KEY_CHAKUCHI_YUBIN_NO",		"chakuchiYubinNo");		// 着地郵便番号のキー			[リクエスト]
	define("YMT_API_KEY_HOKAN_NISSU",			"hokanNissu");			// 保管日数のキー				[リクエスト]
	define("YMT_API_KEY_BOX_SIZE_KBN",			"boxSizeKbn");			// ボックスサイズ区分のキー		[リクエスト]
	define("YMT_API_KEY_RESULT",				"checkEmptyResult");	// レスポンスTOPレベルのキー	[レスポンス]
	define("YMT_API_KEY_RESPONSE_HEADER",		"responseHeader");		// レスポンス共通情報のキー		[レスポンス]
	define("YMT_API_KEY_RETURN_CODE",			"returnCode");			// リターンコードのキー			[レスポンス]
	define("YMT_API_KEY_ERROR_CODE",			"errorCode");			// エラーコードのキー			[レスポンス]
	define("YMT_API_KEY_ERROR_MESSAGE",			"errorMessage");		// エラーメッセージのキー		[レスポンス]
	define("YMT_API_KEY_RESPONSE_INFO",			"responseInfo");		// 処理固有部のキー				[レスポンス]
	define("YMT_API_KEY_EMPTY_INFO_LIST",		"emptyInfoList");		// 満空情報リストのキー			[レスポンス]
	define("YMT_API_KEY_LATITUDE",				"latitudeDms");			// 緯度のキー					[レスポンス]
	define("YMT_API_KEY_LONGITUDE",				"longitudeDms");		// 経度のキー					[レスポンス]
	define("YMT_API_KEY_BOX_COUNT",				"boxCount");			// ボックス空き個数のキー		[レスポンス]
	define("YMT_API_KEY_AKI_BOX_SIZE_KBN",		"akiBoxSizeKbn");		// ボックスサイズ区分のキー		[レスポンス]
	define("YMT_API_KEY_BOX_MAX_COUNT",			"boxMaxCount");			// ボックス数のキー				[レスポンス]
	define("YMT_API_KEY_NOHIN_KANO_DATE",		"nohinKanoDate");		// 納品可能日のキー				[レスポンス]
	define("YMT_API_KEY_SHUKKA_DATE",			"shukkaDate");			// 出荷日のキー					[レスポンス]
	define("YMT_API_KEY_HOKAN_END_DATE",		"hokanEndDate");		// 保管期限日時のキー			[レスポンス]
	// 満空確認API JSONの固定値定義
	define("YMT_API_VAL_SYSTEM_ID",					"ZENCGI");			// システムID
	define("YMT_API_VAL_SEARCH_FLG_SHORTEST",		"1");				// 検索フラグの最短納品日検索
	define("YMT_API_VAL_SEARCH_FLG_DELIVERABLE",	"2");				// 検索フラグの納品可能期間検索
	define("YMT_API_VAL_COMPANY_ID",				"0001");			// 企業ID

	// mod 2017/03/22 H.Yasunaga ロッカー満空APIのURLの切り替えをhostnameによって切り替える [
	// ロッカー満空APIのURL(検証用)
	//define("YMT_API_URL", "http://219.100.33.52/locker_system/CheckEmptyInfoAction.action");
	
	$hostname = trim(`hostname`);
	switch( $hostname ){
	//----- 開発機 -----
	case "dev-storenaviweb01":
	//----- 検証機 -----
	case "storenaviweb-v01":
	case "storenaviweb-v02":
		define("YMT_API_URL", "http://219.100.33.52/locker_system/CheckEmptyInfoAction.action");
		break;
	//----- 本番機 -----
	default:
		define("YMT_API_URL", "https://lockersystem.kuronekoyamato.co.jp/locker_system/CheckEmptyInfoAction.action");
		break;
	}
	// mod 2017/03/22 H.Yasunaga ]
	
	// jsonのデコード(文字列→配列)
	// 失敗時はnull
	function Decode_JSON($target) {
		$json_decoder = new Jsphon_Decoder();
		$value = $json_decoder->decode($target);
		return $value;
	}
	
	// jsonのエンコード(配列→文字列)
	function Encode_JSON($target) {
		$json_encoder = new Jsphon_Encoder();
		$value = $json_encoder->encode($target);
		return unicode_encode($value);
	}
	
	// リクエストJSON作成
	// $searchFlg		:検索フラグ 1:最短納品日検索 2:納品可能期間検索
	// $kokyakuCsd		:顧客CDの配列
	// $shukkaYoteiDate	:出荷予定日の文字列(yyyymmdd)
	// $hatchiYubinNo	:発地郵便番号(7桁ハイフンなし)
	// $chakuchiYubinNos:着地郵便番号の配列
	// $boxSizeKbn		:ボックスサイズ区分
	// 戻り値			:リクエスト用JSON文字列
	function CreateRequest($searchFlg, $kokyakuCds, $shukkaYoteiDate, $hatchiYubinNo, $chakuchiYubinNos, $boxSizeKbn) {

		// 引数が文字列の場合、1件分の配列として扱う
		if (is_array($kokyakuCds) == false && is_string($kokyakuCds) == true) {
			$kokyakuCds = array($kokyakuCds);
		}
		
		// 引数が文字列の場合、1件分の配列として扱う
		if (is_array($chakuchiYubinNos) == false && is_string($chakuchiYubinNos) == true) {
			$chakuchiYubinNos = array($chakuchiYubinNos);
		}

		$value = array();
		// TOPレベル[満空確認APIパラメータ]
		$value[YMT_API_KEY_PARAMETER] = array();
		// リクエスト共通情報
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_HEADER] = array();
		// システムID
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_SYSTEM_ID] = YMT_API_VAL_SYSTEM_ID;
		// 依頼日時
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_RESERVE_TIMESTAMP] = CreateReserveTimestamp();
		// 処理固有部
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO] = array();
		// 検索フラグ
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_SEARCH_FLG] = $searchFlg;
		// 出荷予定日
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_SHUKKA_YOTEI_DATE] = $shukkaYoteiDate;
		// 発地郵便番号
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_HATCHI_YUBIN_NO] = $hatchiYubinNo;
		// 納品予定日
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_NOHIN_YOTEI_DATE] = "";
		// ボックスサイズ区分
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_BOX_SIZE_KBN] = $boxSizeKbn;

		// ロッカー情報リスト
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_LOCKER_LIST] = array();
		for($i = 0; $i < count($kokyakuCds); $i++) {
			$locker = array();
			// 企業ID
			$locker[YMT_API_KEY_COMPANY_ID] = YMT_API_VAL_COMPANY_ID;
			// ロッカーID
			$locker[YMT_API_KEY_LOCKER_ID] = "";
			// 顧客CD
			$locker[YMT_API_KEY_KOKYAKU_CD] = $kokyakuCds[$i];
			// 着地郵便番号
			$locker[YMT_API_KEY_CHAKUCHI_YUBIN_NO] = $chakuchiYubinNos[$i];
			
			// 配列に追加
			$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_LOCKER_LIST][$i] = $locker;
		}
		
		return Encode_JSON($value);
	}
	
	// 満空確認APIへの確認リクエストを行う
	// $url			:リクエスト先URL
	// $json		:リクエスト用JSON文字列
	// $retrymax	:リクエストリトライ回数
	function DoRequest($url, $json, $retryMax = 3) {
		// del 2016/12/15 H.Yasunaga ヤマトロッカーAPIへのアクセス時のプロキシ設定を削除 [
		//global $D_APIPROXY;
		//$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];
		// del 2016/12/15 H.Yasunaga ]

		// del 2016/12/26 H.Yasunaga ログ削除 [
		// add 2016/12/15 H.Yasunaga ログ挿入 [
		//error_log("ymt_api_json_function DoRequest url:[" . $url . "]\n");
		//error_log("ymt_api_json_function DoRequest json:[" . $json . "]\n");
		// add 2016/12/15 H.Yasunaga]
		// del 2016/12/26 H.Yasunaga]

		// add 2017/03/22 H.Yasunaga 本番環境時はwgetコマンドからAPIを利用する [
		$hostname = trim(`hostname`);
		switch( $hostname ){
			//----- 開発機 -----
			case "dev-storenaviweb01":
			//----- 検証機 -----
			case "storenaviweb-v01":
			case "storenaviweb-v02":
		// add 2017/03/22 H.Yasunaga ]
				// プロキシ経由でJSONをPOSTする
				$context_options = array(
					'http' => array(
						'method'  => 'POST',				// HTTPメソッドの指定
						'content' => $json,					// 送信データ
						'header'=>	"Content-Type: application/json;charset=UTF-8\r\n" .
									"Accept: application/json\r\n",
						'ignore_errors' => true,			// TRUEを指定すると、ステータスコードが失敗を意味する場合でもコンテンツの取得を行う
						// del 2016/12/15 H.Yasunaga ヤマトロッカーAPIへのアクセス時のプロキシ設定を削除 [
						//'proxy' => "tcp://$host",			// proxyの設定
						// del 2016/12/15 H.Yasunaga ]
						'request_fulluri' => true,			// TRUEを指定するとリクエストを生成する際に完全なURIが使われる
					)
				);
				// ストリームコンテキストの作成
				$context = stream_context_create($context_options);
				
				$stream = null;
				for($i = 0; $i <= $retryMax; $i++) {
					if ($i == $retryMax) {
						return false;
					}
					
					$stream = fopen($url, 'r', false, $context);
					if ($stream !== FALSE) {
						// HTTPヘッダの取得
						$header = stream_get_meta_data($stream);
						// del 2016/12/26 H.Yasunaga ログ削除[
						// add 2016/12/15 H.Yasunaga ログ挿入 [
						//error_log("ymt_api_json_function DoRequest header:[" . print_r($header, true) . "]\n");
						// add 2016/12/15 H.Yasunaga ]
						// del 2016/12/26 H.Yasunaga ]
						if (strpos($header["wrapper_data"][0], "200") === false) {
							fclose($stream);
							continue;
						}
						// 残りの内容取得
						$contents = stream_get_contents($stream);
						fclose($stream);
						break;
					}
				}
		// add 2017/03/22 H.Yasunaga 本番環境時はwgetコマンドからAPIを利用する
				break;
			//----- 本番機 -----
			default:
				// 本番用はwgetコマンドを利用する
				$cmd = "wget -q -O - --header='Content-Type: application/json;charset=UTF-8' --header='Accept: application/json'" . " --post-data='" . $json . "'" . " " . $url;
				exec($cmd,  $contents);
				if (is_array($contents) == true) {
					$contents = implode("", $contents);
				}
				break;
		}
		// add 2017/03/22 H.Yasunaga ]
		
		// del 2016/12/26 H.Yasunaga ログ削除 [
		// add 2016/12/15 H.Yasunaga ログ挿入 [
		//error_log("ymt_api_json_function DoRequest contents:[" . $contents . "]\n");
		// add 2016/12/15 H.Yasunaga ]
		// del 2016/12/26 H.Yasunaga ]
		return $contents;
	}
	
	// デコードした後のJSONのチェック
	function CheckResponseError($value, &$hasApiError, &$errorCode, &$errorMessage) {
		$hasApiError = false;
		if (is_array($value) == false || is_null($value) == true) {
			// 配列でない or nullである
			// デコードに失敗している
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		if (isset($value[YMT_API_KEY_RESULT]) == false) {
			// レスポンスのTOPレベルのキーがセットされていない or キーが違う
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		if (isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER]) == false) { 
			// レスポンス共通情報のキーがセットされていない or キーが違う
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		if ( isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_RETURN_CODE]) == false) {
			// リターンコード未設定
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		$ret_code = $value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_RETURN_CODE];
		if ($ret_code != 0 || !strlen($ret_code)) {
			// リターンコードが0以外
			// エラーコードの取得
			$errorCode = isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_ERROR_CODE]) ? 
									$value[YMT_API_KEY_RESULT][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_ERROR_CODE] : "";
			// エラーメッセージの取得
			$errorMessage = isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_MESSAGE]) ?
									$value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_MESSAGE] :"";
			$hasApiError = true;
			return false;
		}
		return true;
	}
	
	// 依頼日時用の現在日付の作成
	// フォーマット：yyyy-mm-dd hh:mm:ss.fff
	function CreateReserveTimestamp() {
		list($usec, $sec) = explode(" ", microtime());
		$mtime = ((float)$usec + (float)$sec);
		$arrTime = explode(".", $mtime);
		return date("Y-m-d H:i:s", $arrTime[0]) . "." . substr($arrTime[1], 0, 3);
	}
	
	/**
	 * Unicodeエスケープされた文字列をUTF-8文字列に戻す。
	 * 参考:http://d.hatena.ne.jp/iizukaw/20090422
	 * @param unknown_type $str
	 */
	function unicode_encode($str) {
		return preg_replace_callback("/\\\\u([0-9a-zA-Z]{4})/", "unicode_encode_callback", $str);
	}

	function unicode_encode_callback($matches) {
		return mb_convert_encoding(pack("H*", $matches[1]), "UTF-8", "UTF-16"); 
	}
?>