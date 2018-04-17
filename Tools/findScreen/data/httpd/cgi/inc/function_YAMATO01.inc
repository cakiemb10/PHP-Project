<?php
/*=========================================================*/
// ファイル名：function_YAMATO01.inc
//
// ヤマトロッカー対応【YAMATO01】カスタマイズ関数
// store_nearsearch.cgiで使用
// 
// 更新履歴
// 2016/12/12 H.Yasunaga	新規作成
// 2016/12/20 H.Yasunaga	APIエラー時も店舗情報を返すようにする
// 2017/01/17 H.Yasunaga	ロッカー満空APIの返却データ最大数を10件変更の対応
/*=========================================================*/
	require_once(dirname(__FILE__) . "/ymt_api_json_function.inc");
	require_once("xml_util.inc");
	// 利用するその他のファイル
	//xml_util.inc				// 緯度経度から郵便番号を取得するcgiの戻りがxmlのため
	//ZdcCommonFuncAPI.inc		// 緯度経度から郵便番号を取得するcgiの読み込みのため
	
	class YAMATO01 {
		// 出荷予定日(CGIのパラメータ)
		var $shukkaYoteiDate;
		// 発地郵便番号(CGIのパラメータ)
		var $hatchiYubinNo;
		// ボックスサイズ区分(CGIのパラメータ)
		var $boxSizeKbn;
		// 保管期限を導出するための値(納品可能日にプラスする日数）
		var $hokanNissu = 2;
		// 郵便番号逆引きで使うpflgパラメータ(store_nearsearch.cgiで指定された値)
		var $pflgValue = 1;
		// 郵便番号逆引きで使うdatumパラメータ(store_nearsearch.cgiで指定された値)
		var $datumValue = "TOKYO";
		
		// コンストラクタ
		// $shukkaYoteiDate	:出荷予定日(CGIのパラメータから)
		// $hatchiYubinNo	:発地郵便番号(CGIのパラメータから）
		// $boxSizeKbn		:ボックスサイズ区分(CGIのパラメータから)
		// $pflg			:ポイントフラグ(CGIのパラメータから)
		// $datum			:測地系(CGIのパラメータから)
		function YAMATO01($shukkaYoteiDate, $hatchiYubinNo, $boxSizeKbn, $pflg, $datum) {
			// 出荷予定日
			$this->shukkaYoteiDate = $shukkaYoteiDate;
			// 発地郵便番号
			$this->hatchiYubinNo = $hatchiYubinNo;
			// ボックスサイズ区分
			$this->boxSizeKbn = $boxSizeKbn;
			// ポイントフラグ
			$this->pflgValue = $pflg;
			// 測地系
			$this->datumValue = $datum;
		}
		
		// エラー時はnullを返す
		function getApiData($arrKyotenData) {
			// ロッカーの拠点データをいれる配列
			$arrLockerKyotenData = array();
			
			for($i = 0; $i < count($arrKyotenData); $i++) {
				// 拠点データの中からロッカーの拠点を探す
				// 店舗種別が取扱店(2)で受取店ロゴ分類がロッカー(563)のデータ
				if ($arrKyotenData[$i]["COL_01"] == "2" && $arrKyotenData[$i]["COL_39"] == "563") {
					// 拠点IDと郵便番号を取り出す
					$arrLockerKyotenData[] = array(
												"KYOTEN_ID"	=> $arrKyotenData[$i]["KYOTEN_ID"],
												"COL_08"	=> $arrKyotenData[$i]["COL_08"],
												"ADDR"		=> $arrKyotenData[$i]["ADDR"],
												"LAT"		=> $arrKyotenData[$i]["LAT"],
												"LON"		=> $arrKyotenData[$i]["LON"],
											);
				}
			}
			// COL_08(郵便番号)が無い場合は逆引きして値をCOL_08にいれる
			for($i = 0; $i < count($arrLockerKyotenData); $i++) {
				if (empty($arrLockerKyotenData[$i]["COL_08"]) == true) {
					$lat = $arrLockerKyotenData[$i]["LAT"];
					$lon = $arrLockerKyotenData[$i]["LON"];
					$zipCode = self::getZipCode($lat, $lon, $this->pflgValue, $this->datumValue);
					if ($zipCode !== false) {
						$arrLockerKyotenData[$i]["COL_08"] = $zipCode;
					} else {
						// 緯度経度から郵便番号の取得に失敗
						return null;
					}
				}
			}
			
			// APIリクエストの結果をいれる配列
			// $arrAPIData[拠点ID] = array(納品可能日のキー => 納品可能日, 出荷予定日のキー => 出荷予定日)
			$arrAPIData = array();
			// ロッカーの拠点が含まれている場合はAPIリクエスト(最短納品日検索)を行う
			if (count($arrLockerKyotenData) > 0) {
				// mod start 2017/01/17 H.Yasunaga 1回のリクエスト件数最大10件変更の対応 [
				// APIのリクエストが最大10件なので複数回(最大100回)行う
				// 10で割って端数を切り上げ
				// リクエストの回数の導出
				//$apiRequestMax = ceil(count($arrLockerKyotenData) / 100);
				$apiRequestMax = ceil(count($arrLockerKyotenData) / 10);
				// mod end 2017/01/17 H.Yasunaga ]
				for($i = 0; $i < $apiRequestMax; $i++) {
					// リクエストに設定する拠点IDの配列
					$arrKyotenIds = array();
					// リクエストに設定する着地郵便番号
					$arrChakutiYubinNos = array();
					// mod start 2017/01/17 H.Yasunaga 1回のリクエスト件数最大10件変更の対応 [
					// APIリクエストに必要な拠点IDと郵便番号をMAX100件取り出す
					//for($j = ($i * 100); $j < (($i + 1) * 100); $j++) {
					for($j = ($i * 10); $j < (($i + 1) * 10); $j++) {
					// mod end 2017/01/17 H.Yasunaga ]
						if (isset($arrLockerKyotenData[$j]) == true){
							$arrKyotenIds[] = $arrLockerKyotenData[$j]["KYOTEN_ID"];
							$arrChakutiYubinNos[] = $arrLockerKyotenData[$j]["COL_08"];
						} else {
							break;
						}
					}
					
					// APIリクエストのJSONを作成
					$requestJson = CreateRequest(YMT_API_VAL_SEARCH_FLG_SHORTEST,
													$arrKyotenIds,
													$this->shukkaYoteiDate,
													$this->hatchiYubinNo,
													$arrChakutiYubinNos,
													$this->boxSizeKbn);
					// add 2016/12/20 H.Yasunaga ロッカーAPIエラー時も店舗情報を返す [
					// ロッカーAPIエラー識別用のフラグ
					$lockerApiErrorFlg = false;
					// add 2016/12/20 H.Yasunaga ]
													
					// APIリクエストの実行
					$response =  DoRequest(YMT_API_URL, $requestJson);
					// del 2016/12/26 H.Yasunaga ログ削除 [
					// add 2016/12/15 H.Yasunaga ログ挿入 [
					//error_log("YAMATO01 getApiData response:[" . $response . "]");
					// add 2016/12/15 H.Yasunaga]
					// del 2016/12/26 H.Yasunaga]
					if ($response !== null && $response !== false) {
						// レスポンスのJSONをデコード
						$responseJson = Decode_JSON($response);
						if ($responseJson != null) {
							// リターンコードの確認
							if ($responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_RETURN_CODE] == "0") {
								$emptyInfoList = $responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_INFO][YMT_API_KEY_EMPTY_INFO_LIST];
								for($k = 0; $k < count($emptyInfoList); $k++) {
									// レスポンスから 納品可能日・出荷日・保管期限日時を取得する
									// ボックス空き個数が0の場合はセットしない
									if ($emptyInfoList[$k][YMT_API_KEY_BOX_COUNT] != 0) {
										$arrAPIData[$emptyInfoList[$k][YMT_API_KEY_KOKYAKU_CD]] = array(
																								YMT_API_KEY_NOHIN_KANO_DATE => $emptyInfoList[$k][YMT_API_KEY_NOHIN_KANO_DATE],
																								YMT_API_KEY_SHUKKA_DATE => $emptyInfoList[$k][YMT_API_KEY_SHUKKA_DATE],
																								YMT_API_KEY_HOKAN_END_DATE => $emptyInfoList[$k][YMT_API_KEY_HOKAN_END_DATE],
																							);
									}
								}
							} else {
								// リターンコードが異常
								$errorCode = $responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_CODE];
								$errorMessage = $responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_MESSAGE];
								// 文字コード変換
								$errorMessage = mb_convert_encoding($errorMessage, "EUC-jp", "UTF-8");
								// mod 2016/12/20 H.Yasunaga ロッカーAPIエラー時も店舗情報を返す [
								// 店舗情報を返すためnullを返すのではなくフラグを立てる
								//return null;
								$lockerApiErrorFlg = true;
								// mod 2016/12/20 H.Yasunaga ]
								// del 2016/12/26 H.Yasunaga ログ削除 [
								// add 2016/12/15 H.Yasunaga ログ挿入 [
								//error_log("YAMATO01 getApiData returnCode error\n");
								//error_log("YAMATO01 getApiData errorCode:[" . $errorCode . "]\n");
								//error_log("YAMATO01 getApiData errorMessage:[" . $errorMessage . "]\n");
								// add 2016/12/15 H.Yasunaga]
								// del 2016/12/26 H.Yasunaga]
								// del 2016/12/21 H.Yasunaga ソース修正ミス [
								//return null;
								// del 2016/12/21 H.Yasunaga ]
							}
						} else {
							// JSONのデコードに失敗
							// mod 2016/12/20 H.Yasunaga ロッカーAPIエラー時も店舗情報を返す [
							// 店舗情報を返すためnullを返すのではなくフラグを立てる
							//return null;
							$lockerApiErrorFlg = true;
							// mod 2016/12/20 H.Yasunaga ]
							// del 2016/12/26 H.Yasunaga ログ削除 [
							// add 2016/12/15 H.Yasunaga ログ挿入 [
							//error_log("YAMATO01 getApiData json decode error\n");
							// add 2016/12/15 H.Yasunaga]
							// del 2016/12/26 H.Yasunaga]
							// del 2016/12/21 H.Yasunaga ソース修正ミス [
							//return null;
							// del 2016/12/21 H.Yasunaga ]
						}
					} else {
						// APIリクエストに失敗
						// mod 2016/12/20 H.Yasunaga ロッカーAPIエラー時も店舗情報を返す [
						// 店舗情報を返すためnullを返すのではなくフラグを立てる
						//return null;
						$lockerApiErrorFlg = true;
						// mod 2016/12/20 H.Yasunaga ]
						// del 2016/12/26 H.Yasunaga ログ削除 [
						// add 2016/12/15 H.Yasunaga ログ挿入 [
						//error_log("YAMATO01 getApiData request failed\n");
						// add 2016/12/15 H.Yasunaga]
						// del 2016/12/26 H.Yasunaga]
					}
				}
			}
			// APIリクエスト結果のマージ
			for($i = 0; $i < count($arrKyotenData); $i++) {
				$uketoriKanoDate = "";	// 受取可能日
				$shukkaDate = "";		// 出荷日
				$hokanKigen = "";		// 保管期限
				// APIのリクエスト結果にデータが存在した場合は値を設定
				// mod 2016/12/20 H.Yasunaga ロッカーAPIエラー時も店舗情報を返す [
				//if (isset($arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]]) == true) {
				if (isset($arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]]) == true && $lockerApiErrorFlg == false) {
				// mod 2016/12/20 H.Yasunaga ]
					// 該当の受取可能日を取り出し
					$uketoriKanoDate = $arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]][YMT_API_KEY_NOHIN_KANO_DATE];
					// 該当の出荷日を取り出し
					$shukkaDate = $arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]][YMT_API_KEY_SHUKKA_DATE];
					// APIが返す保管期限
					$hokanKigenFromApi = $arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]][YMT_API_KEY_HOKAN_END_DATE];
					// 出荷予定日からn日を加算した日付
					$hokanKigen = self::dayPlus($uketoriKanoDate, $this->hokanNissu);
				}
				// add 2016/12/20 H.Yasunaga ロッカーAPIエラー時も店舗情報を返す [
				if ($lockerApiErrorFlg == true) {
					// 受取可能日時・出荷日・保管期限に'error'を設定
					$uketoriKanoDate = "error";
					$shukkaDate = "error";
					$hokanKigen = "error";
				}
				// add 2016/12/20 H.Yasunaga ]
				
				// 受取可能日
				$arrKyotenData[$i]["YAMATO01_UKETORIKANODATE"] = $uketoriKanoDate;
				// 出荷日
				$arrKyotenData[$i]["YAMATO01_SHUKKADATE"] = $shukkaDate;
				// 保管期限
				$arrKyotenData[$i]["YAMATO01_HOKANKIGEN"] = $hokanKigen;
			}
			
			return $arrKyotenData;
		}
		
		// 日数加算
		static function dayPlus($ymd, $plus=1) {
			if (strlen($ymd) != 8) {
				return "";
			}
			$y = substr($ymd, 0, 4);
			$m = substr($ymd, 4, 2);
			$d = substr($ymd, 6, 2);
			return date('Ymd', mktime(0, 0, 0, $m, $d+$plus, $y));
		}
		
		
		// 郵便番号の逆引き
		// $lat		:緯度
		// $lon		:経度
		// $pflg	:ポイントフラグ
		// $datum	:測地系
		static function getZipCode($lat, $lon, $pflg, $datum) {
			global $API_SSAPI_SRV;
			global $D_SSAPI_KEY;
			$cgiUrl = "http://" . $API_SSAPI_SRV . "/ssapi/getzipcode.cgi?";
			
			$ll = $lat . "," . $lon;
			// getzipcode.cgiのパラメータ
			// key	:CGIのキー
			// ll	:緯度と経度をカンマ区切りにした文字列
			// enc	:文字コード
			// pflg	:ポイントフラグ
			// datum:測地系
			$query = sprintf("key=%s&ll=%s&enc=UTF8&pflg=%s&datum=%s",$D_SSAPI_KEY, $ll, $pflg, $datum);
			
			$url = $cgiUrl . $query;
			$strXml = ZdcHttpRead($url);
			if ($strXml === false) {
				return false;
			}
			// ZdcHttpReadは配列で返すから結合
			if (is_array($strXml) == true) {
				$strXml = implode($strXml);
			}
			
			$arrXml = LoadXml($strXml);
			if (is_array($arrXml) == false) {
				// XMLのパースに失敗
				return false;
			}
			// リターンコード
			$returnCode = GetXMLVal($arrXml, "returnCode");
			// 取得レコード数
			$recCount = GetXMLVal($arrXml, "recCount");
			// ヒット件数
			$hitCount = GetXMLVal($arrXml, "hitCount");
			
			if ($returnCode != "21900000") {
				// リターンコードが正常以外
				return false;
			}
			
			if ($recCount == 0 || $hitCount == 0) {
				// 取得レコード数が0
				return false;
			}
			
			$zipCode = GetXMLVal($arrXml, "zipCode");
			return is_null($zipCode) ? false : $zipCode;
		}
	}
?>