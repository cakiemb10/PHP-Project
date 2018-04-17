<?php
// ------------------------------------------------------------
// ����Ϣ��API
// 
// 2016/06/14 H.Yasunaga	��������
// 2016/06/15 H.Yasunaga	ȿ����������б�
// 2016/06/24 H.Yasunaga	���ٷ��٤λ���ߥ��ν���
// 2016/06/27 H.Osamoto		Ź�޾����ǧ�ڥǡ����λ�����DB��ʬΥ
// 2016/06/27 H.Yasunaga	COL_17(ɽ���ե饰)��"t"�Τ�ΤΤ�ɽ������
// 2016/06/28 H.Yasunaga	POST�б�
// 2016/08/05 H.Yasunaga	ʸ��������Ƚ��ͥ�����ѹ�(UTF-8��ͥ�褹��)
// 2016/08/24 H.Yasunaga	�ꥯ�����ȥѥ�᡼���˺�ɸ����[coord]���ɲ�
// 2016/12/16 H.Yasunaga	��ɸ����[coord]�ѥ�᡼�����ͤ�"W"���ɲá��쥹�ݥ󥹤ΰ��ٷ��٤�����¬�ϷϤˤ���
// 2017/01/25 H.Yasunaga	������Υ����Ϥ��޻�
// 2017/02/21 H.Yasunaga	�ɽꥳ����[post_code]�ѥ�᡼����EUC�ʳ����ꤷ���ݤ�2�󥨥󥳡��ɤ���Ƥ��ޤ��Х��ν���
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/inc/define.inc");
	require_once(dirname(__FILE__) . "/inc/define_zdc.inc");
	require_once(dirname(__FILE__) . "/inc/ZdcCommonFunc.inc");
	require_once(dirname(__FILE__) . "/oracle/ora_def.inc");
	require_once(dirname(__FILE__) . "/inc/oraDBAccess.inc");
	require_once(dirname(__FILE__) . "/inc/ResponseXML.inc");
	require_once(dirname(__FILE__) . "/inc/ApiLogUtil.inc");
	require_once(dirname(__FILE__) . "/inc/ApiKeyUtil.inc");
	require_once(dirname(__FILE__) . "/inc/CommonUtil.inc");
	// add start 2016/06/28 H.Yasunaga POST�б� [
	require_once(dirname(__FILE__) . "/inc/function.inc");
	// add end ]

	// ������ʸ���󤫤�ʸ��������Ƚ��
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$ENC = mb_detect_encoding( urldecode($_SERVER['QUERY_STRING']), "EUC-JP, UTF-8, SJIS");
	// mod start 2016/08/05 H.Yasunaga ʸ��������Ƚ��ͥ�����ѹ� [
	//$ENC = mb_detect_encoding( urldecode(implode($_REQUEST)), "EUC-JP, UTF-8, SJIS");
	$ENC = mb_detect_encoding( urldecode(implode($_REQUEST)), " UTF-8, EUC-JP, SJIS");
	// mod end ]
	// mod end ]
	require_once(dirname(__FILE__) ."/inc/store_enc.inc");
	// store_enc.inc�Ѥ��Ѵ�
	if ($ENC == "EUC-JP") {
		$ENC = "EUC";
	} else if ($ENC == "UTF-8") {
		$ENC = "UTF8";
	}
	
	// ���ִ�����ˡ���������		ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_office_id				= isset($_GET['office_id']) ? urldecode($_GET['office_id']) : null;
	$p_office_id				= getCgiParameter('office_id', null);
	// mod end ]
	if ($p_office_id != null) {
		$p_office_id = f_enc_to_EUC($p_office_id);
	}
	
	// �ɽꥳ����					ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_post_code				= isset($_GET['post_code']) ? urldecode($_GET['post_code']) : null;
	$p_post_code				= getCgiParameter('post_code', null);
	// mod end ]
	if ($p_post_code != null) {
		$p_post_code = f_enc_to_EUC($p_post_code);
	}
	
	// �谷Ź�ֹ�					ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_dealer_no				= isset($_GET['dealer_no']) ? urldecode($_GET['dealer_no']) : null;
	$p_dealer_no				= getCgiParameter('dealer_no', null);
	// mod end ]
	if ($p_dealer_no != null) {
		$p_dealer_no = f_enc_to_EUC($p_dealer_no);
	}
	
	// ���٣�						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_max_nl					= isset($_GET['max_nl']) ? urldecode($_GET['max_nl']) : null;
	$p_max_nl					= getCgiParameter('max_nl', null);
	// mod end ]
	if ($p_max_nl != null) {
		$p_max_nl = f_enc_to_EUC($p_max_nl);
	}
	
	// ���٣�						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_max_el					= isset($_GET['max_el']) ? urldecode($_GET['max_el']) : null;
	$p_max_el					= getCgiParameter('max_el', null);
	// mod end ]
	if ($p_max_el != null) {
		$p_max_el = f_enc_to_EUC($p_max_el);
	}
	
	// ���٣�						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_min_nl					= isset($_GET['min_nl']) ? urldecode($_GET['min_nl']) : null;
	$p_min_nl					= getCgiParameter('min_nl', null);
	// mod end
	if ($p_min_nl != null) {
		$p_min_nl = f_enc_to_EUC($p_min_nl);
	}
	
	// ���٣�						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_min_el					= isset($_GET['min_el']) ? urldecode($_GET['min_el']) : null;
	$p_min_el					= getCgiParameter('min_el', null);
	// mod end
	if ($p_min_el != null) {
		$p_min_el = f_enc_to_EUC($p_min_el);
	}
	
	// ͹���ֹ�						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_zip_code					= isset($_GET['zip_code']) ? urldecode($_GET['zip_code']) : null;
	$p_zip_code					= getCgiParameter('zip_code', null);
	// mod end ]
	if ($p_zip_code != null) {
		$p_zip_code = f_enc_to_EUC($p_zip_code);
	}
	
	// ����							ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_address					= isset($_GET['address']) ? urldecode($_GET['address']) : null;
	$p_address					= getCgiParameter('address', null);
	// mod end ]
	if ($p_address != null) {
		$p_address = f_enc_to_EUC($p_address);
	}
	
	// ͹�ضɲ�ҥ�ˡ���������		ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_network_code			= isset($_GET['jp_network_code']) ? urldecode($_GET['jp_network_code']) : null;
	$p_jp_network_code			= getCgiParameter('jp_network_code', null);
	// mod end ]
	if ($p_jp_network_code != null) {
		$p_jp_network_code = f_enc_to_EUC($p_jp_network_code);
	}
	
	// ͹�ض�̾						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_network_name			= isset($_GET['jp_network_name']) ? urldecode($_GET['jp_network_name']) : null;
	$p_jp_network_name			= getCgiParameter('jp_network_name', null);
	// mod end ]
	if ($p_jp_network_name != null) {
		$p_jp_network_name = f_enc_to_EUC($p_jp_network_name);
	}

	
	// �椦�椦�����ˡ���������	ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_post_code				= isset($_GET['jp_post_code']) ? urldecode($_GET['jp_post_code']) : null;
	$p_jp_post_code				= getCgiParameter('jp_post_code', null);
	// mod end ]
	// mod 2017/02/21 H.Yasunaga �ѿ�����ߥ��ˤ��Х����ɽꥳ���ɥѥ�᡼�������Ѥκݤ˥ѥ�᡼�����顼�ˤʤ� [
	//if ($p_post_code != null) {
	//	$p_post_code = f_enc_to_EUC($p_post_code);
	//}
	if ($p_jp_post_code != null) {
		$p_jp_post_code = f_enc_to_EUC($p_jp_post_code);
	}
	
	// mod end 2017/02/21 ]
	
	// ͹�ضɻ�Ź̾					ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_post_name				= isset($_GET['jp_post_name']) ? urldecode($_GET['jp_post_name']) : null;
	$p_jp_post_name				= getCgiParameter('jp_post_name', null);
	// mod end ]
	if ($p_jp_post_name != null) {
		$p_jp_post_name = f_enc_to_EUC($p_jp_post_name);
	}
	
	// �椦����Ź��ˡ���������		ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_bank_code				= isset($_GET['jp_bank_code']) ? urldecode($_GET['jp_bank_code']) : null;
	$p_jp_bank_code				= getCgiParameter('jp_bank_code', null);
	// mod end
	if ($p_jp_bank_code != null) {
		$p_jp_bank_code = f_enc_to_EUC($p_jp_bank_code);
	}
	
	// ���ľ��Ź̾					ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_bank_name				= isset($_GET['jp_bank_name']) ? urldecode($_GET['jp_bank_name']) : null;
	$p_jp_bank_name				= getCgiParameter('jp_bank_name', null);
	// mod end ]
	if ($p_jp_bank_name != null) {
		$p_jp_bank_name = f_enc_to_EUC($p_jp_bank_name);
	}
	
	// ���ľ��Ź����̾				ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_bank_official_name	= isset($_GET['jp_bank_official_name']) ? urldecode($_GET['jp_bank_official_name']) : null;
	$p_jp_bank_official_name	= getCgiParameter('jp_bank_official_name', null);
	// mod end ]
	if ($p_jp_bank_official_name != null) {
		$p_jp_bank_official_name = f_enc_to_EUC($p_jp_bank_official_name);
	}
	
	// ����ݥ�ˡ���������			ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_jp_insurance_code		= isset($_GET['jp_insurance_code']) ? urldecode($_GET['jp_insurance_code']) : null;
	$p_jp_insurance_code		= getCgiParameter('jp_insurance_code', null);
	// mod end ]
	if ($p_jp_insurance_code != null) {
		$p_jp_insurance_code = f_enc_to_EUC($p_jp_insurance_code);
	}
	
	// add start 2016/06/15 H.Yasunaga ȿ����������б� [
	// ȿ������						ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_reflect_date				= isset($_GET['reflect_date']) ? urldecode($_GET['reflect_date']) : null;
	$p_reflect_date				= getCgiParameter('reflect_date', null);
	// mod end ]
	// add end 2016/06/15 ]
	
	// add start 2016/08/24 H.Yasunaga coord�ѥ�᡼���ɲ� [
	// ��ɸ����						ɬ�ܡ���
	// Z���������ɸ��ư���DB��lat,lon����ѡ�
	// M��Mapion��ɸ��ư���DB��COL_194,COL_195����ѡˢ��ǥե����
	// W������¬�ϷϤ�ư���DB��lat,lon������¬�ϷϤ��Ѵ�)	// add 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"���ɲ�
	// �����ά���ϥǥե���Ȥ�coord=M��ư��(�ǥե���Ȥ��ͤ������Τϸ����������������
	$p_coord					= getCgiParameter('coord', null);
	if ($p_coord != null) {
		$p_coord = f_enc_to_EUC($p_coord);
	}
	// add end 2016/08/24]
	
	// ������������					ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_key						= isset($_GET['key']) ? urldecode($_GET['key']) : null;
	$p_key						= getCgiParameter('key', null);
	// mod end ]
	if ($p_key != null) {
		$p_key = f_enc_to_EUC($p_key);
	}
	
	// 1�ڡ����������ɽ�����		ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_result					= isset($_GET['result']) ? urldecode($_GET['result']) : null;
	$p_result					= getCgiParameter('result', null);
	// mod end ]
	if ($p_result != null) {
		$p_result = f_enc_to_EUC($p_result);
	}
	// �ڡ����ֹ�					ɬ�ܡ���
	// mod start 2016/06/28 H.Yasunaga POST�б� [
	//$p_page						= isset($_GET['page']) ? urldecode($_GET['page']) : null;
	$p_page						= getCgiParameter('page', null);
	// mod end ]
	if ($p_page != null) {
		$p_page = f_enc_to_EUC($p_page);
	}
	
	// �쥹�ݥ��ѥ��饹������
	$response = new ResponseXML();

	// ɬ�ܡ����Υ����å�
	if (mb_strlen($p_key) == 0) {
		// ������̵��
		// ���顼No2
		CommonUtil::api_log("nothing apiaccesskey.");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_KEY);
		exit;
	}
	if (mb_strlen($p_result) == 0) {
		// ɽ�������̵��
		CommonUtil::api_log("nothing result param");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	
	if ($p_result < 1 || $p_result > 50) {
		// ɽ�������0�ʲ���51�ʾ�
		CommonUtil::api_log("result param error:[" . $p_result . "]");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}

	if (mb_strlen($p_page) == 0) {
		// �ڡ����ֹ椬�ʤ�
		CommonUtil::api_log("nothing page param");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	if ($p_page <= 0) {
		// �ڡ����ֹ椬0�ޤ���0�ʲ�
		CommonUtil::api_log("page param error:[" . $p_page . "]");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	
	// ɬ�ܡ����Υ����å�
	// ���٣����٣����٣����٣��ϣ���·�äƤ��뤳��
	if (	(!isset($p_office_id)				|| mb_strlen($p_office_id) == 0)				&&
			(!isset($p_post_code)				|| mb_strlen($p_post_code) == 0)				&&
			(!isset($p_dealer_no)				|| mb_strlen($p_dealer_no) == 0)				&&
			(!isset($p_zip_code)				|| mb_strlen($p_zip_code) == 0)					&&
			(!isset($p_address)					|| mb_strlen($p_address) == 0)					&&
			(!isset($p_jp_network_code)			|| mb_strlen($p_jp_network_code) == 0)			&&
			(!isset($p_jp_network_name)			|| mb_strlen($p_jp_network_name) == 0)			&&
			(!isset($p_jp_post_code)			|| mb_strlen($p_jp_post_code) == 0)				&&
			(!isset($p_jp_post_name)			|| mb_strlen($p_jp_post_name) == 0)				&&
			(!isset($p_jp_bank_code)			|| mb_strlen($p_jp_bank_code) == 0)				&&
			(!isset($p_jp_bank_name)			|| mb_strlen($p_jp_bank_name) == 0)				&&
			(!isset($p_jp_bank_official_name)	|| mb_strlen($p_jp_bank_official_name) == 0)	&&
			(!isset($p_jp_insurance_code)		|| mb_strlen($p_jp_insurance_code) == 0)		&&
			// add start 2016/06/15 H.Yasunaga ȿ����������б� [
			(!isset($p_reflect_date)			|| mb_strlen($p_reflect_date) == 0)				&&
			// add end 2016/06/15 ]
			(!isset($p_max_nl, $p_max_el, $p_min_nl, $p_min_el) ||
			mb_strlen($p_max_nl) == 0 || mb_strlen($p_max_el) == 0 || mb_strlen($p_min_nl) == 0 || mb_strlen($p_min_el) == 0) ){
		
		// �ѥ�᡼��������
		CommonUtil::api_log("invalid parameter.");
		// add start 2017/01/24 H.Yasunaga ������Υ��޻� ���顼���Τ�QueryString�Υǡ����������[
		CommonUtil::api_log("Request:[" . urldecode($_SERVER['QUERY_STRING']) ."]");
		// add end 2017/01/24 ]
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	
	// del start 2017/01/24 H.Yasunaga ������Υ��޻� [
	//CommonUtil::api_log("Request:[" . urldecode($_SERVER['QUERY_STRING']) ."]");
	// del end 2017/01/24 H.Yasunaga ]

	// DB�����ץ�
	$db = new oraDBAccess();
	if (!$db->open()) {
		$errMsg = oci_error();
		$db->close();
		CommonUtil::api_log("Database open error. code:[" . $errMsg['code'] . "] msg:[" . $errMsg['message'] ."]");
		// No5�Υ��顼
		// �������顼
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
		exit;
	}
	// add 2016/06/27 H.Osamoto [
	// ǧ��DB�����ץ�
	$dba = new oraDBAccess("auth");
	if (!$dba->open()) {
		$errMsg = oci_error();
		$db->close();
		$dba->close();
		CommonUtil::api_log("Database(auth) open error. code:[" . $errMsg['code'] . "] msg:[" . $errMsg['message'] ."]");
		// No5�Υ��顼
		// �������顼
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
		exit;
	}
	// add 2016/06/27 H.Osamoto ]
	// del start 2016/06/23 H.Yasunaga ���פʤ����� [
	// define.inc�����ꤷ������API��������������IP���ɥ쥹����ǧ
	//if (CommonUtil::checkSpecialPermission($p_key, $_SERVER['REMOTE_ADDR']) == false) {
	// del end ]
		//	if (ApiKeyUtil::ExistsApiKey($db, $p_key, &$internalError, &$errorMsg) === false) {		mod 2016/06/27 H.Osamoto
		if (ApiKeyUtil::ExistsApiKey($dba, $p_key, &$internalError, &$errorMsg) === false) {
			// API���������������ͤ����äƤ��뤬��Ͽ����Ƥ��ʤ�
			if ($internalError === true) {
				// �������顼����
				CommonUtil::api_log("ApiKeyUtil::ExistsApiKey error. code:[" . $errorMsg['code'] . "] message:[" . $errorMsg['message'] ."]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
			} else {
				// API������������������
				CommonUtil::api_log("invalid apikey. apikey:[" . $p_key . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INVALID_KEY);
			}
			$db->close();
			$dba->close();	// add 2016/06/27 H.Osamoto
			exit;
		}
		
		//	if (ApiKeyUtil::apiKeyValidation($db, $p_key, &$internalError, &$errorMsg) === false) {		mod 2016/06/27 H.Osamoto
		if (ApiKeyUtil::apiKeyValidation($dba, $p_key, &$internalError, &$errorMsg) === false) {
			// API���������������ͤ����äƤ��뤬̵���ˤʤäƤ���
			if ($internalError === true) {
				// �������顼����
				CommonUtil::api_log("ApiKeyUtil::apiKeyValidation error. code:[" . $erroMsg['code'] . "] message:[" . $erroMsg['message'] . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
			} else {
				// API��������������̵��
				CommonUtil::api_log("invalid apikey. apikey:[" . $p_key . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INVALID_KEY);
			}
			$db->close();
			$dba->close();	// add 2016/06/27 H.Osamoto
			exit;
		}
		
		//	if (ApiKeyUtil::checkIpAddress($db, $p_key, $_SERVER['REMOTE_ADDR'], &$internalError, &$errorMsg) === false) {	mod 2016/06/27 H.Osamoto
		if (ApiKeyUtil::checkIpAddress($dba, $p_key, $_SERVER['REMOTE_ADDR'], &$internalError, &$errorMsg) === false) {
			// API��������������ɳ�Ť���IP���ɥ쥹�Ǥʤ�
			if ($internalError === true) {
				// �������顼����
				CommonUtil::api_log("ApiKeyUtil::checkIpAddress error. code:[" . $errorMsg['code'] . "] message:[" . $errorMsg['message'] . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
			} else {
				// API����������������Ͽ����Ƥ��ʤ�IP���ɥ쥹����Υ�������
				CommonUtil::api_log("invalid ipaddress. apikey:[" . $p_key . "] ipaddress:[" . $_SERVER['REMOTE_ADDR'] . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INVALID_IPADDRESS);
			}
			$db->close();
			$dba->close();	// add 2016/06/27 H.Osamoto
			exit;
		}
		// API�Υ���������
		// mod 2016/06/27 H.Osamoto [
		//	ApiLogUtil::putLog($db, $p_key, $_SERVER['REMOTE_ADDR'], f_enc_to_EUC(urldecode($_SERVER['QUERY_STRING'])));
		//	$db->commitTransaction();
		ApiLogUtil::putLog($dba, $p_key, $_SERVER['REMOTE_ADDR'], f_enc_to_EUC(urldecode($_SERVER['QUERY_STRING'])));
		$dba->commitTransaction();
		// mod 2016/06/27 H.Osamoto ]
	// del start 2016/06/23 H.Yasunaga ���פʤ����� [
	//} else {
	//	// define.inc�������������API��������������IP���ɥ쥹�˰���
	//	// API�����ѥ��ϻĤ��ʤ�
	//	CommonUtil::api_log("Special Permission. key:[" . $p_key . "] ipaddress:[" . $_SERVER['REMOTE_ADDR'] . "]");
	//}
	// del end ]
	
	$center_nl;
	$center_el;
	$nearseachFlag = false;
	$filterStr = "";
	if (isset($p_max_nl, $p_max_el, $p_min_nl, $p_min_el) && 
		mb_strlen($p_max_nl) != 0 && mb_strlen($p_max_el) != 0 &&
		mb_strlen($p_min_nl) != 0 && mb_strlen($p_min_el) != 0 &&
		is_numeric($p_max_nl) == true && is_numeric($p_max_el) == true &&
		is_numeric($p_min_nl) == true && is_numeric($p_min_el) == true) {
		$center_el = ($p_min_el + $p_max_el) / 2;
		$center_nl = ($p_min_nl + $p_max_nl) / 2;
		$nearseachFlag = true;
		// del start 2017/01/24 H.Yasunaga �����Ϥ����� [
		//CommonUtil::api_log("near search flag on lat/lon exist"); 
		// del end 2017/01/24 ]
	}
	// ���ִ�����ˡ���������
	if (mb_strlen($p_office_id) != 0 && $p_office_id != '%') {
		$filterStr .= "KYOTEN_ID:FW:'" . $p_office_id . "'";
	}
	
	// �ɽꥳ����
	if (mb_strlen($p_post_code) != 0 && $p_post_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_02:FW:'" . $p_post_code . "'";
	}
	
	// �谷Ź�ֹ�
	if (mb_strlen($p_dealer_no) != 0 && $p_dealer_no != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_03:FW:'" . $p_dealer_no . "'";
	}
	
	// ͹���ֹ�
	if (mb_strlen($p_zip_code) != 0 && $p_zip_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_10:FW:'" . $p_zip_code . "'";
	}
	
	// ����
	if (mb_strlen($p_address) != 0 && $p_address != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "ADDR:FW:'" . $p_address . "'";
		/*
		// ���������ǥ���
		$nearseachFlag = true;
		CommonUtil::api_log("nearsearchFlag on exist address");
		// ���������ǥ��󥰷�̤� $center_el��$center_nl�ˤ����
		$addr_e = urlencode($p_address);
		$url = sprintf("%s?key=%s&opt=%s&enc=%s&mclv=%d&sep=&tod=&frewd=%s", $D_SSAPI["selectaddr"], $D_SSAPI_KEY, $cid, "EUC", 6, $addr_e);
		for($j = 0; $j < $RETRY_MAX; $j++) {
			$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
			$status = explode("\t", $dat[0]);
			if($status[0] == "21300000") {
				break;
			}
		}
		if($status[0] == "21300000") {
			$rec = explode("\t", $dat[1]);
			if (count($rec) >= 7) {
				$lat = intval($rec[5]);
				$lon = intval($rec[6]);
				$center_nl = cnv_dms2hour($lat);
				$center_el = cnv_dms2hour($lon);
			} else {
				//���ٷ��پ���μ����˼���
				CommonUtil::api_log("Geocoding error");
				CommonUtil::api_log(print_r($rec, true));
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
				exit;
			}
		} else {
			// ���ٷ��پ���μ����˼���
			CommonUtil::api_log("Geocoding error");
			CommonUtil::api_log(print_r($dat, true));
			header("Content-Type: text/xml");
			echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
			exit;
		}*/
	}
	
	// ͹�ضɲ�ҥ�ˡ���������
	if (mb_strlen($p_jp_network_code) != 0 && $p_jp_network_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_19:FW:'" . $p_jp_network_code . "'";
	}
	
	// ͹�ض�̾
	if (mb_strlen($p_jp_network_name) != 0 && $p_jp_network_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_20:FW:'" . $p_jp_network_name . "'";
	}
	
	// �椦�椦�����ˡ���������
	if (mb_strlen($p_jp_post_code) != 0 && $p_jp_post_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_27:FW:'" . $p_jp_post_code . "'";
	}
	
	// ͹�ػ�Ź̾
	if (mb_strlen($p_jp_post_name) != 0 && $p_jp_post_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_29:FW:'" . $p_jp_post_name . "'";
	}
	
	// �椦����Ź��ˡ���������
	if (mb_strlen($p_jp_bank_code) != 0 && $p_jp_bank_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_36:FW:'" . $p_jp_bank_code . "'";
	}
	
	// ���ľ��Ź̾
	if (mb_strlen($p_jp_bank_name) != 0 && $p_jp_bank_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_37:FW:'" . $p_jp_bank_name . "'";
	}
	
	// ���ľ��Ź����̾
	if (mb_strlen($p_jp_bank_official_name) != 0 && $p_jp_bank_official_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_39:FW:'" . $p_jp_bank_official_name . "'";
	}
	
	// ����ݥ�ˡ���������
	if (mb_strlen($p_jp_insurance_code) != 0 && $p_jp_insurance_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_43:FW:'" . $p_jp_insurance_code . "'";
	}
	
	// add start 2016/06/27 H.Yasunaga COL_17��"t"�Τ�ΤΤ߷�̤˴ޤ�� [
	if (mb_strlen($filterStr) != 0) {
		$filterStr .= " AND ";
	}
	$filterStr .= "COL_17:'t'";
	// add end ]
	
	// del start 2017/01/24 H.Yasunaga �����Ϥ����� [
	//CommonUtil::api_log("FILTER:[" . $filterStr . "]");
	// del end ]


	
	require_once(dirname(__FILE__) . "/inc/StoreNearSearch.inc");
	require_once(dirname(__FILE__) . "/inc/StoreSearch.inc");
	
	// ������������
	// (1�ڡ���������η���� (�ڡ����� -1)) + 1
	// 1�ڡ����ܤ�"1"
	// 2�ڡ����ܤ�1�ڡ���������η�� + 1
	$POS = ($p_result * ($p_page -1)) + 1;
	$CNT = $p_result;
	
	// add start 2016/06/15 H.Yasunaga ȿ����������б� [
	// ȿ������
	// ���Ϥ��줿�ͤ���ϥ��ե󡦥����Ⱦ�ѥ��ڡ����������ǯ�������ޤǤ�10ʸ���ˤ���
	$REFLECTDATE = "";
	if (empty($p_reflect_date) != true) {
		// '-'��':'��' '(Ⱦ�ѥ��ڡ���)������
		// ��2016-06-15 12:34:56�ע� ��20160615123456��
		$refdate_search = array('-', ':', ' ');
		$refdate_rep = array('','','');
		$REFLECTDATE = str_replace($refdate_search, $refdate_rep, $p_reflect_date);
		// ʬ���ä򥫥åȤ����PUB_S_DATE�����ޤǤ����ʤ�����)
		// ��20160615123456�ע� ��2016061512��
		if (mb_strlen($REFLECTDATE) > 10) {
			$REFLECTDATE = mb_substr($REFLECTDATE, 0, 10);
		}
	}
	// add end 2016/06/15 H.Yasunaga ]
	
	// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ѥ�᡼���ɲ� [
	// ��ɸ����[coord]
	// coord=Z or coord=M or coord=W
	$COORD = "";
	// mod start 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"���ɲ� �쥹�ݥ󥹤ΰ��ٷ��٤�����¬�ϷϤˤ��� [
	//if ($p_coord == DEF_COORD_ZENRIN || $p_coord == DEF_COORD_MAPION) {
	if ($p_coord == DEF_COORD_ZENRIN || $p_coord == DEF_COORD_MAPION || $p_coord == DEF_COORD_WORLD) {
	// mod end 2016/12/16 H.Yasunaga ]
		// Z : �������ɸ(lat,lon)
		// M : Mapion��ɸ(COL_194[Mapion����,COL_195[Mapion����])
		// W : �������ɸ(lat,lon)������¬�ϷϤ��Ѵ������֤�
		$COORD = $p_coord;
	} else {
		$COORD = DEF_COORD_MAPION;
	}
	// add end 2016/08/24 H.Yasunaga ]
	
	if ($nearseachFlag == true) {
		// ���ٷ��٤����뢪�Ǵ��Ź����
		$LAT = $center_nl;
		$LON = $center_el;
		
		// mod start 2016/06/24 H.Yasunaga ���ٷ��ٻ���ߥ�����[
		//$NELAT = $p_min_nl;
		//$NELON = $p_min_el;
		//$SWLAT = $p_max_nl;
		//$SWLON = $p_max_el;
		
		$NELAT = $p_max_nl;	// �������
		$NELON = $p_max_el;	// �������
		$SWLAT = $p_min_nl;	// ��������
		$SWLON = $p_min_el;	// ��������
		// mod end ]
		
		$FILTER = $filterStr;
		// del start 2017/01/24 H.Yasunaga �����Ϥ����� [
		//CommonUtil::api_log("StoreNearSearch");
		//CommonUtil::api_log("LAT:[" . $LAT . "]\n" .
		//					"LON:[" . $LON . "]\n" .
		//					"NELAT:[" . $NELAT . "]\n" .
		//					"NELON:[" . $NELON . "]\n" .
		//					"SWLAT:[" . $SWLAT . "]\n" .
		//					"SWLON:[" . $SWLON . "]\n" .
		//					"FILTER:[" . $FILTER . "]\n" .
		//					// add start 2016/06/15 H.Yasunaga ȿ����������б� [
		//					"REFLECTDATE:[" . $REFLECTDATE . "]\n" .
		//					// add end 2016/06/15 ]
		//					// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ѥ�᡼���ɲ� [
		//					"COORD:[" . $COORD . "]\n" .
		//					// add end 2016/08/24 ]
		//					"POS:[" . $POS . "]\n" .
		//					"CNT:[" . $CNT . "]");
		// del end ]
							
		// mod start 2016/06/15 H.Yasunaga ȿ����������б� [
		// $searchRes = StoreNearSearch::Search($db, $cid, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN);
		// mod start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
		//$searchRes = StoreNearSearch::Search($db, $cid, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $REFLECTDATE, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN);
		$searchRes = StoreNearSearch::Search($db, $cid, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $REFLECTDATE, $COORD,$POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN);
		// mod end 2016/08/24 H.Yasunaga ]
		// mod end 2016/06/15 H.Yasunaga ]
	} else {
		// ���ٷ��٤�̵����Ź�޾�︡��
		$FILTER = $filterStr;

		// del start 2017/01/24 H.Yasunaga �����Ϥ����� [
		//CommonUtil::api_log("StoreSerach");
		//CommonUtil::api_log("FILTER:[" . $FILTER . "]\n" .
		//					// add start 2016/06/15 H.Yasunaga ȿ����������б� [
		//					"REFLECTDATE:[" . $REFLECTDATE . "]\n" .
		//					// add end 2016/06/15 ]
		//					// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ѥ�᡼���ɲ� [
		//					"COORD:[" . $COORD . "]\n" .
		//					// add end 2016/08/24 ]
		//					"POS:[" . $POS . "]\n" .
		//					"CNT:[" . $CNT . "]");
		// del end ]
							
		// mod start 2016/06/15 H.Yasunaga ȿ����������б� [
		// $searchRes = StoreSearch::Search($db, $cid, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN );
		// mod start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
		//$searchRes = StoreSearch::Search($db, $cid, $FILTER, $REFLECTDATE, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN );
		$searchRes = StoreSearch::Search($db, $cid, $FILTER, $REFLECTDATE, $COORD,$POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN );
		// mod end 2016/08/24 ]
		// mod end 2016/06/15 ]
	}
	
	if ($searchRes == DEF_RETCD_DE || $searchRes == DEF_RETCD_DEND) {
		// �ǡ���ͭ
		$response->addData($ARR_KYOTEN);
		$response->setTotalNum($HIT_NUM);
		$response->setReturnNum($REC_NUM);
		$response->setStartPosition($POS);
		header("Content-Type: text/xml");
		echo $response->createXML();
	} else {
		switch($searchRes) {
			case DEF_RETCD_DNE :{
				// 0��
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_ITEM_NOT_FOUND);
				break;
			}
			case DEF_RETCD_DERR1:
			case DEF_RETCD_DERR2:
			case DEF_RETCD_DERR3: {
				// �ǡ����١������顼
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
				break;
			}
			case DEF_RETCD_PERR1:
			case DEF_RETCD_PERR2:
			case DEF_RETCD_PERR3: {
				// ���ϥѥ�᡼�����顼
				header("Content-Type: text/xml");
				$response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
				break;
			}
			default: {
				// ����¾�ʤ��ꤨ�ʤ���
				CommonUtil::api_log("search return value error. value:[" . $searchRes . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
				break;
			}
		}
	}
	// DB�Ĥ�
	$db->commitTransaction();
	$db->close();
	$dba->close();	// add 2016/06/27 H.Osamoto
	exit;
?>