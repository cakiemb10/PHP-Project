<?php
/*========================================================*/
// �ե�����̾��ymt_api_json_function.inc
// ����̾����ޥȥ��å�������API�Υꥯ�����Ƚ���
//
// ��������2016/12/12
// �����ԡ�H.Yasunaga
//
// ���⡧��ޥȥ��å�������API�Υꥯ�����Ȥ�Ԥ�
//
// ��������
// 2016/12/12 H.Yasunaga		��������
// 2016/12/15 H.Yasunaga		PHP4�ǥ��顼�ˤʤ뤿�ᡢJsphon�饤�֥��Υե������require_once����
//								�ץ��������ͳ�����˥�ޥȥ��å���API�ؤΥ����������ѹ�
// 2017/03/22 H.Yasunaga		���å�������API��URL��hostname�ˤ�ä��ڤ��ؤ���
//								���ִĶ�����API�Υ���������wget���ޥ�ɤ����Ѥ���
/*========================================================*/
	// JSON�򰷤��饤�֥��
	require_once("/home/emap/src/Jsphon/Decoder.php");
	require_once("/home/emap/src/Jsphon/Encoder.php");
	// del 2016/12/15 H.Yasunaga PHP5�Ǥ�ɬ�פ�����PHP4�Ǥϥ��顼�ˤʤ뤿���� [
	//require_once("/home/emap/src/Jsphon/Error.php");
	//require_once("/home/emap/src/Jsphon/Exception.php");
	// del 2016/12/15 H.Yasunaga ]
	
	// ������ǧAPI JSON�Υ������
	define("YMT_API_KEY_PARAMETER", 			"checkEmptyParameter");	// �ꥯ������TOP��٥�Υ���	[�ꥯ������]
	define("YMT_API_KEY_REQUEST_HEADER",		"requestHeader");		// �ꥯ�����ȶ��̾���Υ���		[�ꥯ������]
	define("YMT_API_KEY_SYSTEM_ID",				"systemId");			// �����ƥ�ID�Υ���				[�ꥯ������]
	define("YMT_API_KEY_RESERVE_TIMESTAMP",		"reserveTimestamp");	// ���������Υ���				[�ꥯ������]
	define("YMT_API_KEY_REQUEST_INFO",			"requestInfo");			// ������ͭ���Υ���				[�ꥯ������]
	define("YMT_API_KEY_SEARCH_FLG",			"searchFlg");			// �����ե饰�Υ���				[�ꥯ������]
	define("YMT_API_KEY_LOCKER_LIST",			"lockerList");			// ���å�������ꥹ�ȤΥ���		[�ꥯ������]
	define("YMT_API_KEY_COMPANY_ID",			"companyId");			// ���ID�Υ���					[����]
	define("YMT_API_KEY_LOCKER_ID",				"lockerId");			// ���å���ID�Υ���				[����]
	define("YMT_API_KEY_KOKYAKU_CD",			"kokyakuCd");			// �ܵ�CD�Υ���					[����]
	define("YMT_API_KEY_SHUKKA_YOTEI_DATE",		"shukkaYoteiDate");		// �в�ͽ�����Υ���				[�ꥯ������]
	define("YMT_API_KEY_NOHIN_YOTEI_DATE",		"nohinYoteiDate");		// Ǽ��ͽ�����Υ���				[�ꥯ������]
	define("YMT_API_KEY_HATCHI_YUBIN_NO",		"hatchiYubinNo");		// ȯ��͹���ֹ�Υ���			[�ꥯ������]
	define("YMT_API_KEY_CHAKUCHI_YUBIN_NO",		"chakuchiYubinNo");		// ����͹���ֹ�Υ���			[�ꥯ������]
	define("YMT_API_KEY_HOKAN_NISSU",			"hokanNissu");			// �ݴ������Υ���				[�ꥯ������]
	define("YMT_API_KEY_BOX_SIZE_KBN",			"boxSizeKbn");			// �ܥå�����������ʬ�Υ���		[�ꥯ������]
	define("YMT_API_KEY_RESULT",				"checkEmptyResult");	// �쥹�ݥ�TOP��٥�Υ���	[�쥹�ݥ�]
	define("YMT_API_KEY_RESPONSE_HEADER",		"responseHeader");		// �쥹�ݥ󥹶��̾���Υ���		[�쥹�ݥ�]
	define("YMT_API_KEY_RETURN_CODE",			"returnCode");			// �꥿���󥳡��ɤΥ���			[�쥹�ݥ�]
	define("YMT_API_KEY_ERROR_CODE",			"errorCode");			// ���顼�����ɤΥ���			[�쥹�ݥ�]
	define("YMT_API_KEY_ERROR_MESSAGE",			"errorMessage");		// ���顼��å������Υ���		[�쥹�ݥ�]
	define("YMT_API_KEY_RESPONSE_INFO",			"responseInfo");		// ������ͭ���Υ���				[�쥹�ݥ�]
	define("YMT_API_KEY_EMPTY_INFO_LIST",		"emptyInfoList");		// ��������ꥹ�ȤΥ���			[�쥹�ݥ�]
	define("YMT_API_KEY_LATITUDE",				"latitudeDms");			// ���٤Υ���					[�쥹�ݥ�]
	define("YMT_API_KEY_LONGITUDE",				"longitudeDms");		// ���٤Υ���					[�쥹�ݥ�]
	define("YMT_API_KEY_BOX_COUNT",				"boxCount");			// �ܥå��������Ŀ��Υ���		[�쥹�ݥ�]
	define("YMT_API_KEY_AKI_BOX_SIZE_KBN",		"akiBoxSizeKbn");		// �ܥå�����������ʬ�Υ���		[�쥹�ݥ�]
	define("YMT_API_KEY_BOX_MAX_COUNT",			"boxMaxCount");			// �ܥå������Υ���				[�쥹�ݥ�]
	define("YMT_API_KEY_NOHIN_KANO_DATE",		"nohinKanoDate");		// Ǽ�ʲ�ǽ���Υ���				[�쥹�ݥ�]
	define("YMT_API_KEY_SHUKKA_DATE",			"shukkaDate");			// �в����Υ���					[�쥹�ݥ�]
	define("YMT_API_KEY_HOKAN_END_DATE",		"hokanEndDate");		// �ݴɴ��������Υ���			[�쥹�ݥ�]
	// ������ǧAPI JSON�θ��������
	define("YMT_API_VAL_SYSTEM_ID",					"ZENCGI");			// �����ƥ�ID
	define("YMT_API_VAL_SEARCH_FLG_SHORTEST",		"1");				// �����ե饰�κ�ûǼ��������
	define("YMT_API_VAL_SEARCH_FLG_DELIVERABLE",	"2");				// �����ե饰��Ǽ�ʲ�ǽ���ָ���
	define("YMT_API_VAL_COMPANY_ID",				"0001");			// ���ID

	// mod 2017/03/22 H.Yasunaga ���å�������API��URL���ڤ��ؤ���hostname�ˤ�ä��ڤ��ؤ��� [
	// ���å�������API��URL(������)
	//define("YMT_API_URL", "http://219.100.33.52/locker_system/CheckEmptyInfoAction.action");
	
	$hostname = trim(`hostname`);
	switch( $hostname ){
	//----- ��ȯ�� -----
	case "dev-storenaviweb01":
	//----- ���ڵ� -----
	case "storenaviweb-v01":
	case "storenaviweb-v02":
		define("YMT_API_URL", "http://219.100.33.52/locker_system/CheckEmptyInfoAction.action");
		break;
	//----- ���ֵ� -----
	default:
		define("YMT_API_URL", "https://lockersystem.kuronekoyamato.co.jp/locker_system/CheckEmptyInfoAction.action");
		break;
	}
	// mod 2017/03/22 H.Yasunaga ]
	
	// json�Υǥ�����(ʸ��������)
	// ���Ի���null
	function Decode_JSON($target) {
		$json_decoder = new Jsphon_Decoder();
		$value = $json_decoder->decode($target);
		return $value;
	}
	
	// json�Υ��󥳡���(����ʸ����)
	function Encode_JSON($target) {
		$json_encoder = new Jsphon_Encoder();
		$value = $json_encoder->encode($target);
		return unicode_encode($value);
	}
	
	// �ꥯ������JSON����
	// $searchFlg		:�����ե饰 1:��ûǼ�������� 2:Ǽ�ʲ�ǽ���ָ���
	// $kokyakuCsd		:�ܵ�CD������
	// $shukkaYoteiDate	:�в�ͽ������ʸ����(yyyymmdd)
	// $hatchiYubinNo	:ȯ��͹���ֹ�(7��ϥ��ե�ʤ�)
	// $chakuchiYubinNos:����͹���ֹ������
	// $boxSizeKbn		:�ܥå�����������ʬ
	// �����			:�ꥯ��������JSONʸ����
	function CreateRequest($searchFlg, $kokyakuCds, $shukkaYoteiDate, $hatchiYubinNo, $chakuchiYubinNos, $boxSizeKbn) {

		// ������ʸ����ξ�硢1��ʬ������Ȥ��ư���
		if (is_array($kokyakuCds) == false && is_string($kokyakuCds) == true) {
			$kokyakuCds = array($kokyakuCds);
		}
		
		// ������ʸ����ξ�硢1��ʬ������Ȥ��ư���
		if (is_array($chakuchiYubinNos) == false && is_string($chakuchiYubinNos) == true) {
			$chakuchiYubinNos = array($chakuchiYubinNos);
		}

		$value = array();
		// TOP��٥�[������ǧAPI�ѥ�᡼��]
		$value[YMT_API_KEY_PARAMETER] = array();
		// �ꥯ�����ȶ��̾���
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_HEADER] = array();
		// �����ƥ�ID
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_SYSTEM_ID] = YMT_API_VAL_SYSTEM_ID;
		// ��������
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_RESERVE_TIMESTAMP] = CreateReserveTimestamp();
		// ������ͭ��
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO] = array();
		// �����ե饰
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_SEARCH_FLG] = $searchFlg;
		// �в�ͽ����
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_SHUKKA_YOTEI_DATE] = $shukkaYoteiDate;
		// ȯ��͹���ֹ�
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_HATCHI_YUBIN_NO] = $hatchiYubinNo;
		// Ǽ��ͽ����
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_NOHIN_YOTEI_DATE] = "";
		// �ܥå�����������ʬ
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_BOX_SIZE_KBN] = $boxSizeKbn;

		// ���å�������ꥹ��
		$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_LOCKER_LIST] = array();
		for($i = 0; $i < count($kokyakuCds); $i++) {
			$locker = array();
			// ���ID
			$locker[YMT_API_KEY_COMPANY_ID] = YMT_API_VAL_COMPANY_ID;
			// ���å���ID
			$locker[YMT_API_KEY_LOCKER_ID] = "";
			// �ܵ�CD
			$locker[YMT_API_KEY_KOKYAKU_CD] = $kokyakuCds[$i];
			// ����͹���ֹ�
			$locker[YMT_API_KEY_CHAKUCHI_YUBIN_NO] = $chakuchiYubinNos[$i];
			
			// ������ɲ�
			$value[YMT_API_KEY_PARAMETER][YMT_API_KEY_REQUEST_INFO][YMT_API_KEY_LOCKER_LIST][$i] = $locker;
		}
		
		return Encode_JSON($value);
	}
	
	// ������ǧAPI�ؤγ�ǧ�ꥯ�����Ȥ�Ԥ�
	// $url			:�ꥯ��������URL
	// $json		:�ꥯ��������JSONʸ����
	// $retrymax	:�ꥯ�����ȥ�ȥ饤���
	function DoRequest($url, $json, $retryMax = 3) {
		// del 2016/12/15 H.Yasunaga ��ޥȥ��å���API�ؤΥ����������Υץ������������ [
		//global $D_APIPROXY;
		//$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];
		// del 2016/12/15 H.Yasunaga ]

		// del 2016/12/26 H.Yasunaga ������� [
		// add 2016/12/15 H.Yasunaga �������� [
		//error_log("ymt_api_json_function DoRequest url:[" . $url . "]\n");
		//error_log("ymt_api_json_function DoRequest json:[" . $json . "]\n");
		// add 2016/12/15 H.Yasunaga]
		// del 2016/12/26 H.Yasunaga]

		// add 2017/03/22 H.Yasunaga ���ִĶ�����wget���ޥ�ɤ���API�����Ѥ��� [
		$hostname = trim(`hostname`);
		switch( $hostname ){
			//----- ��ȯ�� -----
			case "dev-storenaviweb01":
			//----- ���ڵ� -----
			case "storenaviweb-v01":
			case "storenaviweb-v02":
		// add 2017/03/22 H.Yasunaga ]
				// �ץ�������ͳ��JSON��POST����
				$context_options = array(
					'http' => array(
						'method'  => 'POST',				// HTTP�᥽�åɤλ���
						'content' => $json,					// �����ǡ���
						'header'=>	"Content-Type: application/json;charset=UTF-8\r\n" .
									"Accept: application/json\r\n",
						'ignore_errors' => true,			// TRUE����ꤹ��ȡ����ơ����������ɤ����Ԥ��̣������Ǥ⥳��ƥ�Ĥμ�����Ԥ�
						// del 2016/12/15 H.Yasunaga ��ޥȥ��å���API�ؤΥ����������Υץ������������ [
						//'proxy' => "tcp://$host",			// proxy������
						// del 2016/12/15 H.Yasunaga ]
						'request_fulluri' => true,			// TRUE����ꤹ��ȥꥯ�����Ȥ���������ݤ˴�����URI���Ȥ���
					)
				);
				// ���ȥ꡼�ॳ��ƥ����Ȥκ���
				$context = stream_context_create($context_options);
				
				$stream = null;
				for($i = 0; $i <= $retryMax; $i++) {
					if ($i == $retryMax) {
						return false;
					}
					
					$stream = fopen($url, 'r', false, $context);
					if ($stream !== FALSE) {
						// HTTP�إå��μ���
						$header = stream_get_meta_data($stream);
						// del 2016/12/26 H.Yasunaga �������[
						// add 2016/12/15 H.Yasunaga �������� [
						//error_log("ymt_api_json_function DoRequest header:[" . print_r($header, true) . "]\n");
						// add 2016/12/15 H.Yasunaga ]
						// del 2016/12/26 H.Yasunaga ]
						if (strpos($header["wrapper_data"][0], "200") === false) {
							fclose($stream);
							continue;
						}
						// �Ĥ�����Ƽ���
						$contents = stream_get_contents($stream);
						fclose($stream);
						break;
					}
				}
		// add 2017/03/22 H.Yasunaga ���ִĶ�����wget���ޥ�ɤ���API�����Ѥ���
				break;
			//----- ���ֵ� -----
			default:
				// �����Ѥ�wget���ޥ�ɤ����Ѥ���
				$cmd = "wget -q -O - --header='Content-Type: application/json;charset=UTF-8' --header='Accept: application/json'" . " --post-data='" . $json . "'" . " " . $url;
				exec($cmd,  $contents);
				if (is_array($contents) == true) {
					$contents = implode("", $contents);
				}
				break;
		}
		// add 2017/03/22 H.Yasunaga ]
		
		// del 2016/12/26 H.Yasunaga ������� [
		// add 2016/12/15 H.Yasunaga �������� [
		//error_log("ymt_api_json_function DoRequest contents:[" . $contents . "]\n");
		// add 2016/12/15 H.Yasunaga ]
		// del 2016/12/26 H.Yasunaga ]
		return $contents;
	}
	
	// �ǥ����ɤ������JSON�Υ����å�
	function CheckResponseError($value, &$hasApiError, &$errorCode, &$errorMessage) {
		$hasApiError = false;
		if (is_array($value) == false || is_null($value) == true) {
			// ����Ǥʤ� or null�Ǥ���
			// �ǥ����ɤ˼��Ԥ��Ƥ���
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		if (isset($value[YMT_API_KEY_RESULT]) == false) {
			// �쥹�ݥ󥹤�TOP��٥�Υ��������åȤ���Ƥ��ʤ� or �������㤦
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		if (isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER]) == false) { 
			// �쥹�ݥ󥹶��̾���Υ��������åȤ���Ƥ��ʤ� or �������㤦
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		if ( isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_RETURN_CODE]) == false) {
			// �꥿���󥳡���̤����
			$errorCode = "";
			$errorMessage = "";
			return false;
		}
		
		$ret_code = $value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_RETURN_CODE];
		if ($ret_code != 0 || !strlen($ret_code)) {
			// �꥿���󥳡��ɤ�0�ʳ�
			// ���顼�����ɤμ���
			$errorCode = isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_ERROR_CODE]) ? 
									$value[YMT_API_KEY_RESULT][YMT_API_KEY_REQUEST_HEADER][YMT_API_KEY_ERROR_CODE] : "";
			// ���顼��å������μ���
			$errorMessage = isset($value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_MESSAGE]) ?
									$value[YMT_API_KEY_RESULT][YMT_API_KEY_RESPONSE_HEADER][YMT_API_KEY_ERROR_MESSAGE] :"";
			$hasApiError = true;
			return false;
		}
		return true;
	}
	
	// ���������Ѥθ������դκ���
	// �ե����ޥåȡ�yyyy-mm-dd hh:mm:ss.fff
	function CreateReserveTimestamp() {
		list($usec, $sec) = explode(" ", microtime());
		$mtime = ((float)$usec + (float)$sec);
		$arrTime = explode(".", $mtime);
		return date("Y-m-d H:i:s", $arrTime[0]) . "." . substr($arrTime[1], 0, 3);
	}
	
	/**
	 * Unicode���������פ��줿ʸ�����UTF-8ʸ������᤹��
	 * ����:http://d.hatena.ne.jp/iizukaw/20090422
	 * @param unknown_type $str
	 */
	function unicode_encode($str) {
		return preg_replace_callback("/\\\\u([0-9a-zA-Z]{4})/", "unicode_encode_callback", $str);
	}

	function unicode_encode_callback($matches) {
		return mb_convert_encoding(pack("H*", $matches[1]), "UTF-8", "UTF-16"); 
	}
?>