<?php
/*=========================================================*/
// �ե�����̾��function_YAMATO01.inc
//
// ��ޥȥ��å����б���YAMATO01�ۥ������ޥ����ؿ�
// store_nearsearch.cgi�ǻ���
// 
// ��������
// 2016/12/12 H.Yasunaga	��������
// 2016/12/20 H.Yasunaga	API���顼����Ź�޾�����֤��褦�ˤ���
// 2017/01/17 H.Yasunaga	���å�������API���ֵѥǡ����������10���ѹ����б�
/*=========================================================*/
	require_once(dirname(__FILE__) . "/ymt_api_json_function.inc");
	require_once("xml_util.inc");
	// ���Ѥ��뤽��¾�Υե�����
	//xml_util.inc				// ���ٷ��٤���͹���ֹ���������cgi����꤬xml�Τ���
	//ZdcCommonFuncAPI.inc		// ���ٷ��٤���͹���ֹ���������cgi���ɤ߹��ߤΤ���
	
	class YAMATO01 {
		// �в�ͽ����(CGI�Υѥ�᡼��)
		var $shukkaYoteiDate;
		// ȯ��͹���ֹ�(CGI�Υѥ�᡼��)
		var $hatchiYubinNo;
		// �ܥå�����������ʬ(CGI�Υѥ�᡼��)
		var $boxSizeKbn;
		// �ݴɴ��¤�Ƴ�Ф��뤿�����(Ǽ�ʲ�ǽ���˥ץ饹����������
		var $hokanNissu = 2;
		// ͹���ֹ�հ����ǻȤ�pflg�ѥ�᡼��(store_nearsearch.cgi�ǻ��ꤵ�줿��)
		var $pflgValue = 1;
		// ͹���ֹ�հ����ǻȤ�datum�ѥ�᡼��(store_nearsearch.cgi�ǻ��ꤵ�줿��)
		var $datumValue = "TOKYO";
		
		// ���󥹥ȥ饯��
		// $shukkaYoteiDate	:�в�ͽ����(CGI�Υѥ�᡼������)
		// $hatchiYubinNo	:ȯ��͹���ֹ�(CGI�Υѥ�᡼�������
		// $boxSizeKbn		:�ܥå�����������ʬ(CGI�Υѥ�᡼������)
		// $pflg			:�ݥ���ȥե饰(CGI�Υѥ�᡼������)
		// $datum			:¬�Ϸ�(CGI�Υѥ�᡼������)
		function YAMATO01($shukkaYoteiDate, $hatchiYubinNo, $boxSizeKbn, $pflg, $datum) {
			// �в�ͽ����
			$this->shukkaYoteiDate = $shukkaYoteiDate;
			// ȯ��͹���ֹ�
			$this->hatchiYubinNo = $hatchiYubinNo;
			// �ܥå�����������ʬ
			$this->boxSizeKbn = $boxSizeKbn;
			// �ݥ���ȥե饰
			$this->pflgValue = $pflg;
			// ¬�Ϸ�
			$this->datumValue = $datum;
		}
		
		// ���顼����null���֤�
		function getApiData($arrKyotenData) {
			// ���å����ε����ǡ����򤤤������
			$arrLockerKyotenData = array();
			
			for($i = 0; $i < count($arrKyotenData); $i++) {
				// �����ǡ������椫����å����ε�����õ��
				// Ź�޼��̤��谷Ź(2)�Ǽ���Ź����ʬ�ब���å���(563)�Υǡ���
				if ($arrKyotenData[$i]["COL_01"] == "2" && $arrKyotenData[$i]["COL_39"] == "563") {
					// ����ID��͹���ֹ����Ф�
					$arrLockerKyotenData[] = array(
												"KYOTEN_ID"	=> $arrKyotenData[$i]["KYOTEN_ID"],
												"COL_08"	=> $arrKyotenData[$i]["COL_08"],
												"ADDR"		=> $arrKyotenData[$i]["ADDR"],
												"LAT"		=> $arrKyotenData[$i]["LAT"],
												"LON"		=> $arrKyotenData[$i]["LON"],
											);
				}
			}
			// COL_08(͹���ֹ�)��̵�����ϵհ��������ͤ�COL_08�ˤ����
			for($i = 0; $i < count($arrLockerKyotenData); $i++) {
				if (empty($arrLockerKyotenData[$i]["COL_08"]) == true) {
					$lat = $arrLockerKyotenData[$i]["LAT"];
					$lon = $arrLockerKyotenData[$i]["LON"];
					$zipCode = self::getZipCode($lat, $lon, $this->pflgValue, $this->datumValue);
					if ($zipCode !== false) {
						$arrLockerKyotenData[$i]["COL_08"] = $zipCode;
					} else {
						// ���ٷ��٤���͹���ֹ�μ����˼���
						return null;
					}
				}
			}
			
			// API�ꥯ�����Ȥη�̤򤤤������
			// $arrAPIData[����ID] = array(Ǽ�ʲ�ǽ���Υ��� => Ǽ�ʲ�ǽ��, �в�ͽ�����Υ��� => �в�ͽ����)
			$arrAPIData = array();
			// ���å����ε������ޤޤ�Ƥ������API�ꥯ������(��ûǼ��������)��Ԥ�
			if (count($arrLockerKyotenData) > 0) {
				// mod start 2017/01/17 H.Yasunaga 1��Υꥯ�����ȷ������10���ѹ����б� [
				// API�Υꥯ�����Ȥ�����10��ʤΤ�ʣ����(����100��)�Ԥ�
				// 10�ǳ�ä�ü�����ڤ�夲
				// �ꥯ�����Ȥβ����Ƴ��
				//$apiRequestMax = ceil(count($arrLockerKyotenData) / 100);
				$apiRequestMax = ceil(count($arrLockerKyotenData) / 10);
				// mod end 2017/01/17 H.Yasunaga ]
				for($i = 0; $i < $apiRequestMax; $i++) {
					// �ꥯ�����Ȥ����ꤹ�����ID������
					$arrKyotenIds = array();
					// �ꥯ�����Ȥ����ꤹ������͹���ֹ�
					$arrChakutiYubinNos = array();
					// mod start 2017/01/17 H.Yasunaga 1��Υꥯ�����ȷ������10���ѹ����б� [
					// API�ꥯ�����Ȥ�ɬ�פʵ���ID��͹���ֹ��MAX100����Ф�
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
					
					// API�ꥯ�����Ȥ�JSON�����
					$requestJson = CreateRequest(YMT_API_VAL_SEARCH_FLG_SHORTEST,
													$arrKyotenIds,
													$this->shukkaYoteiDate,
													$this->hatchiYubinNo,
													$arrChakutiYubinNos,
													$this->boxSizeKbn);
					// add 2016/12/20 H.Yasunaga ���å���API���顼����Ź�޾�����֤� [
					// ���å���API���顼�����ѤΥե饰
					$lockerApiErrorFlg = false;
					// add 2016/12/20 H.Yasunaga ]
													
					// API�ꥯ�����Ȥμ¹�
					$response =  DoRequest(YMT_API_URL, $requestJson);
					// del 2016/12/26 H.Yasunaga ������� [
					// add 2016/12/15 H.Yasunaga �������� [
					//error_log("YAMATO01 getApiData response:[" . $response . "]");
					// add 2016/12/15 H.Yasunaga]
					// del 2016/12/26 H.Yasunaga]
					if ($response !== null && $response !== false) {
						// �쥹�ݥ󥹤�JSON��ǥ�����
						$responseJson = Decode_JSON($response);
						if ($responseJson != null) {
							// �꥿���󥳡��ɤγ�ǧ
							if ($responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_RETURN_CODE] == "0") {
								$emptyInfoList = $responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_INFO][YMT_API_KEY_EMPTY_INFO_LIST];
								for($k = 0; $k < count($emptyInfoList); $k++) {
									// �쥹�ݥ󥹤��� Ǽ�ʲ�ǽ�����в������ݴɴ����������������
									// �ܥå��������Ŀ���0�ξ��ϥ��åȤ��ʤ�
									if ($emptyInfoList[$k][YMT_API_KEY_BOX_COUNT] != 0) {
										$arrAPIData[$emptyInfoList[$k][YMT_API_KEY_KOKYAKU_CD]] = array(
																								YMT_API_KEY_NOHIN_KANO_DATE => $emptyInfoList[$k][YMT_API_KEY_NOHIN_KANO_DATE],
																								YMT_API_KEY_SHUKKA_DATE => $emptyInfoList[$k][YMT_API_KEY_SHUKKA_DATE],
																								YMT_API_KEY_HOKAN_END_DATE => $emptyInfoList[$k][YMT_API_KEY_HOKAN_END_DATE],
																							);
									}
								}
							} else {
								// �꥿���󥳡��ɤ��۾�
								$errorCode = $responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_CODE];
								$errorMessage = $responseJson[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_MESSAGE];
								// ʸ���������Ѵ�
								$errorMessage = mb_convert_encoding($errorMessage, "EUC-jp", "UTF-8");
								// mod 2016/12/20 H.Yasunaga ���å���API���顼����Ź�޾�����֤� [
								// Ź�޾�����֤�����null���֤��ΤǤϤʤ��ե饰��Ω�Ƥ�
								//return null;
								$lockerApiErrorFlg = true;
								// mod 2016/12/20 H.Yasunaga ]
								// del 2016/12/26 H.Yasunaga ������� [
								// add 2016/12/15 H.Yasunaga �������� [
								//error_log("YAMATO01 getApiData returnCode error\n");
								//error_log("YAMATO01 getApiData errorCode:[" . $errorCode . "]\n");
								//error_log("YAMATO01 getApiData errorMessage:[" . $errorMessage . "]\n");
								// add 2016/12/15 H.Yasunaga]
								// del 2016/12/26 H.Yasunaga]
								// del 2016/12/21 H.Yasunaga �����������ߥ� [
								//return null;
								// del 2016/12/21 H.Yasunaga ]
							}
						} else {
							// JSON�Υǥ����ɤ˼���
							// mod 2016/12/20 H.Yasunaga ���å���API���顼����Ź�޾�����֤� [
							// Ź�޾�����֤�����null���֤��ΤǤϤʤ��ե饰��Ω�Ƥ�
							//return null;
							$lockerApiErrorFlg = true;
							// mod 2016/12/20 H.Yasunaga ]
							// del 2016/12/26 H.Yasunaga ������� [
							// add 2016/12/15 H.Yasunaga �������� [
							//error_log("YAMATO01 getApiData json decode error\n");
							// add 2016/12/15 H.Yasunaga]
							// del 2016/12/26 H.Yasunaga]
							// del 2016/12/21 H.Yasunaga �����������ߥ� [
							//return null;
							// del 2016/12/21 H.Yasunaga ]
						}
					} else {
						// API�ꥯ�����Ȥ˼���
						// mod 2016/12/20 H.Yasunaga ���å���API���顼����Ź�޾�����֤� [
						// Ź�޾�����֤�����null���֤��ΤǤϤʤ��ե饰��Ω�Ƥ�
						//return null;
						$lockerApiErrorFlg = true;
						// mod 2016/12/20 H.Yasunaga ]
						// del 2016/12/26 H.Yasunaga ������� [
						// add 2016/12/15 H.Yasunaga �������� [
						//error_log("YAMATO01 getApiData request failed\n");
						// add 2016/12/15 H.Yasunaga]
						// del 2016/12/26 H.Yasunaga]
					}
				}
			}
			// API�ꥯ�����ȷ�̤Υޡ���
			for($i = 0; $i < count($arrKyotenData); $i++) {
				$uketoriKanoDate = "";	// �����ǽ��
				$shukkaDate = "";		// �в���
				$hokanKigen = "";		// �ݴɴ���
				// API�Υꥯ�����ȷ�̤˥ǡ�����¸�ߤ��������ͤ�����
				// mod 2016/12/20 H.Yasunaga ���å���API���顼����Ź�޾�����֤� [
				//if (isset($arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]]) == true) {
				if (isset($arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]]) == true && $lockerApiErrorFlg == false) {
				// mod 2016/12/20 H.Yasunaga ]
					// �����μ����ǽ������Ф�
					$uketoriKanoDate = $arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]][YMT_API_KEY_NOHIN_KANO_DATE];
					// �����νв�������Ф�
					$shukkaDate = $arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]][YMT_API_KEY_SHUKKA_DATE];
					// API���֤��ݴɴ���
					$hokanKigenFromApi = $arrAPIData[$arrKyotenData[$i]["KYOTEN_ID"]][YMT_API_KEY_HOKAN_END_DATE];
					// �в�ͽ��������n����û���������
					$hokanKigen = self::dayPlus($uketoriKanoDate, $this->hokanNissu);
				}
				// add 2016/12/20 H.Yasunaga ���å���API���顼����Ź�޾�����֤� [
				if ($lockerApiErrorFlg == true) {
					// �����ǽ�������в������ݴɴ��¤�'error'������
					$uketoriKanoDate = "error";
					$shukkaDate = "error";
					$hokanKigen = "error";
				}
				// add 2016/12/20 H.Yasunaga ]
				
				// �����ǽ��
				$arrKyotenData[$i]["YAMATO01_UKETORIKANODATE"] = $uketoriKanoDate;
				// �в���
				$arrKyotenData[$i]["YAMATO01_SHUKKADATE"] = $shukkaDate;
				// �ݴɴ���
				$arrKyotenData[$i]["YAMATO01_HOKANKIGEN"] = $hokanKigen;
			}
			
			return $arrKyotenData;
		}
		
		// �����û�
		static function dayPlus($ymd, $plus=1) {
			if (strlen($ymd) != 8) {
				return "";
			}
			$y = substr($ymd, 0, 4);
			$m = substr($ymd, 4, 2);
			$d = substr($ymd, 6, 2);
			return date('Ymd', mktime(0, 0, 0, $m, $d+$plus, $y));
		}
		
		
		// ͹���ֹ�εհ���
		// $lat		:����
		// $lon		:����
		// $pflg	:�ݥ���ȥե饰
		// $datum	:¬�Ϸ�
		static function getZipCode($lat, $lon, $pflg, $datum) {
			global $API_SSAPI_SRV;
			global $D_SSAPI_KEY;
			$cgiUrl = "http://" . $API_SSAPI_SRV . "/ssapi/getzipcode.cgi?";
			
			$ll = $lat . "," . $lon;
			// getzipcode.cgi�Υѥ�᡼��
			// key	:CGI�Υ���
			// ll	:���٤ȷ��٤򥫥�޶��ڤ�ˤ���ʸ����
			// enc	:ʸ��������
			// pflg	:�ݥ���ȥե饰
			// datum:¬�Ϸ�
			$query = sprintf("key=%s&ll=%s&enc=UTF8&pflg=%s&datum=%s",$D_SSAPI_KEY, $ll, $pflg, $datum);
			
			$url = $cgiUrl . $query;
			$strXml = ZdcHttpRead($url);
			if ($strXml === false) {
				return false;
			}
			// ZdcHttpRead��������֤�������
			if (is_array($strXml) == true) {
				$strXml = implode($strXml);
			}
			
			$arrXml = LoadXml($strXml);
			if (is_array($arrXml) == false) {
				// XML�Υѡ����˼���
				return false;
			}
			// �꥿���󥳡���
			$returnCode = GetXMLVal($arrXml, "returnCode");
			// �����쥳���ɿ�
			$recCount = GetXMLVal($arrXml, "recCount");
			// �ҥåȷ��
			$hitCount = GetXMLVal($arrXml, "hitCount");
			
			if ($returnCode != "21900000") {
				// �꥿���󥳡��ɤ�����ʳ�
				return false;
			}
			
			if ($recCount == 0 || $hitCount == 0) {
				// �����쥳���ɿ���0
				return false;
			}
			
			$zipCode = GetXMLVal($arrXml, "zipCode");
			return is_null($zipCode) ? false : $zipCode;
		}
	}
?>