<?php
// ------------------------------------------------------------
// 外部連携API
// 
// 2016/06/14 H.Yasunaga	新規作成
// 2016/06/15 H.Yasunaga	反映日時条件対応
// 2016/06/24 H.Yasunaga	緯度経度の指定ミスの修正
// 2016/06/27 H.Osamoto		店舗情報と認証データの参照先DBを分離
// 2016/06/27 H.Yasunaga	COL_17(表示フラグ)が"t"のもののみ表示する
// 2016/06/28 H.Yasunaga	POST対応
// 2016/08/05 H.Yasunaga	文字コード判別優先順位変更(UTF-8を優先する)
// 2016/08/24 H.Yasunaga	リクエストパラメータに座標種別[coord]を追加
// 2016/12/16 H.Yasunaga	座標種別[coord]パラメータの値に"W"を追加、レスポンスの緯度経度を世界測地系にする
// 2017/01/25 H.Yasunaga	正常時のログ出力を抑止
// 2017/02/21 H.Yasunaga	局所コード[post_code]パラメータをEUC以外指定した際に2回エンコードされてしまうバグの修正
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
	// add start 2016/06/28 H.Yasunaga POST対応 [
	require_once(dirname(__FILE__) . "/inc/function.inc");
	// add end ]

	// クエリ文字列から文字コード判別
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$ENC = mb_detect_encoding( urldecode($_SERVER['QUERY_STRING']), "EUC-JP, UTF-8, SJIS");
	// mod start 2016/08/05 H.Yasunaga 文字コード判別優先順位変更 [
	//$ENC = mb_detect_encoding( urldecode(implode($_REQUEST)), "EUC-JP, UTF-8, SJIS");
	$ENC = mb_detect_encoding( urldecode(implode($_REQUEST)), " UTF-8, EUC-JP, SJIS");
	// mod end ]
	// mod end ]
	require_once(dirname(__FILE__) ."/inc/store_enc.inc");
	// store_enc.inc用に変換
	if ($ENC == "EUC-JP") {
		$ENC = "EUC";
	} else if ($ENC == "UTF-8") {
		$ENC = "UTF8";
	}
	
	// 位置管理ユニークコード		必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_office_id				= isset($_GET['office_id']) ? urldecode($_GET['office_id']) : null;
	$p_office_id				= getCgiParameter('office_id', null);
	// mod end ]
	if ($p_office_id != null) {
		$p_office_id = f_enc_to_EUC($p_office_id);
	}
	
	// 局所コード					必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_post_code				= isset($_GET['post_code']) ? urldecode($_GET['post_code']) : null;
	$p_post_code				= getCgiParameter('post_code', null);
	// mod end ]
	if ($p_post_code != null) {
		$p_post_code = f_enc_to_EUC($p_post_code);
	}
	
	// 取扱店番号					必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_dealer_no				= isset($_GET['dealer_no']) ? urldecode($_GET['dealer_no']) : null;
	$p_dealer_no				= getCgiParameter('dealer_no', null);
	// mod end ]
	if ($p_dealer_no != null) {
		$p_dealer_no = f_enc_to_EUC($p_dealer_no);
	}
	
	// 緯度１						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_max_nl					= isset($_GET['max_nl']) ? urldecode($_GET['max_nl']) : null;
	$p_max_nl					= getCgiParameter('max_nl', null);
	// mod end ]
	if ($p_max_nl != null) {
		$p_max_nl = f_enc_to_EUC($p_max_nl);
	}
	
	// 経度１						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_max_el					= isset($_GET['max_el']) ? urldecode($_GET['max_el']) : null;
	$p_max_el					= getCgiParameter('max_el', null);
	// mod end ]
	if ($p_max_el != null) {
		$p_max_el = f_enc_to_EUC($p_max_el);
	}
	
	// 緯度２						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_min_nl					= isset($_GET['min_nl']) ? urldecode($_GET['min_nl']) : null;
	$p_min_nl					= getCgiParameter('min_nl', null);
	// mod end
	if ($p_min_nl != null) {
		$p_min_nl = f_enc_to_EUC($p_min_nl);
	}
	
	// 経度２						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_min_el					= isset($_GET['min_el']) ? urldecode($_GET['min_el']) : null;
	$p_min_el					= getCgiParameter('min_el', null);
	// mod end
	if ($p_min_el != null) {
		$p_min_el = f_enc_to_EUC($p_min_el);
	}
	
	// 郵便番号						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_zip_code					= isset($_GET['zip_code']) ? urldecode($_GET['zip_code']) : null;
	$p_zip_code					= getCgiParameter('zip_code', null);
	// mod end ]
	if ($p_zip_code != null) {
		$p_zip_code = f_enc_to_EUC($p_zip_code);
	}
	
	// 住所							必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_address					= isset($_GET['address']) ? urldecode($_GET['address']) : null;
	$p_address					= getCgiParameter('address', null);
	// mod end ]
	if ($p_address != null) {
		$p_address = f_enc_to_EUC($p_address);
	}
	
	// 郵便局会社ユニークコード		必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_network_code			= isset($_GET['jp_network_code']) ? urldecode($_GET['jp_network_code']) : null;
	$p_jp_network_code			= getCgiParameter('jp_network_code', null);
	// mod end ]
	if ($p_jp_network_code != null) {
		$p_jp_network_code = f_enc_to_EUC($p_jp_network_code);
	}
	
	// 郵便局名						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_network_name			= isset($_GET['jp_network_name']) ? urldecode($_GET['jp_network_name']) : null;
	$p_jp_network_name			= getCgiParameter('jp_network_name', null);
	// mod end ]
	if ($p_jp_network_name != null) {
		$p_jp_network_name = f_enc_to_EUC($p_jp_network_name);
	}

	
	// ゆうゆう窓口ユニークコード	必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_post_code				= isset($_GET['jp_post_code']) ? urldecode($_GET['jp_post_code']) : null;
	$p_jp_post_code				= getCgiParameter('jp_post_code', null);
	// mod end ]
	// mod 2017/02/21 H.Yasunaga 変数指定ミスによるバグ　局所コードパラメータが全角の際にパラメータエラーになる [
	//if ($p_post_code != null) {
	//	$p_post_code = f_enc_to_EUC($p_post_code);
	//}
	if ($p_jp_post_code != null) {
		$p_jp_post_code = f_enc_to_EUC($p_jp_post_code);
	}
	
	// mod end 2017/02/21 ]
	
	// 郵便局支店名					必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_post_name				= isset($_GET['jp_post_name']) ? urldecode($_GET['jp_post_name']) : null;
	$p_jp_post_name				= getCgiParameter('jp_post_name', null);
	// mod end ]
	if ($p_jp_post_name != null) {
		$p_jp_post_name = f_enc_to_EUC($p_jp_post_name);
	}
	
	// ゆうちょ店ユニークコード		必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_bank_code				= isset($_GET['jp_bank_code']) ? urldecode($_GET['jp_bank_code']) : null;
	$p_jp_bank_code				= getCgiParameter('jp_bank_code', null);
	// mod end
	if ($p_jp_bank_code != null) {
		$p_jp_bank_code = f_enc_to_EUC($p_jp_bank_code);
	}
	
	// 銀行直営店名					必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_bank_name				= isset($_GET['jp_bank_name']) ? urldecode($_GET['jp_bank_name']) : null;
	$p_jp_bank_name				= getCgiParameter('jp_bank_name', null);
	// mod end ]
	if ($p_jp_bank_name != null) {
		$p_jp_bank_name = f_enc_to_EUC($p_jp_bank_name);
	}
	
	// 銀行直営店正式名				必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_bank_official_name	= isset($_GET['jp_bank_official_name']) ? urldecode($_GET['jp_bank_official_name']) : null;
	$p_jp_bank_official_name	= getCgiParameter('jp_bank_official_name', null);
	// mod end ]
	if ($p_jp_bank_official_name != null) {
		$p_jp_bank_official_name = f_enc_to_EUC($p_jp_bank_official_name);
	}
	
	// かんぽユニークコード			必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_jp_insurance_code		= isset($_GET['jp_insurance_code']) ? urldecode($_GET['jp_insurance_code']) : null;
	$p_jp_insurance_code		= getCgiParameter('jp_insurance_code', null);
	// mod end ]
	if ($p_jp_insurance_code != null) {
		$p_jp_insurance_code = f_enc_to_EUC($p_jp_insurance_code);
	}
	
	// add start 2016/06/15 H.Yasunaga 反映日時条件対応 [
	// 反映日時						必須：△
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_reflect_date				= isset($_GET['reflect_date']) ? urldecode($_GET['reflect_date']) : null;
	$p_reflect_date				= getCgiParameter('reflect_date', null);
	// mod end ]
	// add end 2016/06/15 ]
	
	// add start 2016/08/24 H.Yasunaga coordパラメータ追加 [
	// 座標種別						必須：×
	// Z：ゼンリン座標で動作（DBのlat,lonを使用）
	// M：Mapion座標で動作（DBのCOL_194,COL_195を使用）※デフォルト
	// W：世界測地系で動作（DBのlat,lonを世界測地系に変換)	// add 2016/12/16 H.Yasunaga 座標種別[coord]に"W"を追加
	// 指定省略時はデフォルトのcoord=Mで動作(デフォルトの値を入れるのは検索引数設定処理）
	$p_coord					= getCgiParameter('coord', null);
	if ($p_coord != null) {
		$p_coord = f_enc_to_EUC($p_coord);
	}
	// add end 2016/08/24]
	
	// アクセスキー					必須：○
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_key						= isset($_GET['key']) ? urldecode($_GET['key']) : null;
	$p_key						= getCgiParameter('key', null);
	// mod end ]
	if ($p_key != null) {
		$p_key = f_enc_to_EUC($p_key);
	}
	
	// 1ページあたりの表示件数		必須：○
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_result					= isset($_GET['result']) ? urldecode($_GET['result']) : null;
	$p_result					= getCgiParameter('result', null);
	// mod end ]
	if ($p_result != null) {
		$p_result = f_enc_to_EUC($p_result);
	}
	// ページ番号					必須：○
	// mod start 2016/06/28 H.Yasunaga POST対応 [
	//$p_page						= isset($_GET['page']) ? urldecode($_GET['page']) : null;
	$p_page						= getCgiParameter('page', null);
	// mod end ]
	if ($p_page != null) {
		$p_page = f_enc_to_EUC($p_page);
	}
	
	// レスポンス用クラスの生成
	$response = new ResponseXML();

	// 必須：○のチェック
	if (mb_strlen($p_key) == 0) {
		// キーが無い
		// エラーNo2
		CommonUtil::api_log("nothing apiaccesskey.");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_KEY);
		exit;
	}
	if (mb_strlen($p_result) == 0) {
		// 表示件数が無い
		CommonUtil::api_log("nothing result param");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	
	if ($p_result < 1 || $p_result > 50) {
		// 表示件数が0以下か51以上
		CommonUtil::api_log("result param error:[" . $p_result . "]");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}

	if (mb_strlen($p_page) == 0) {
		// ページ番号がない
		CommonUtil::api_log("nothing page param");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	if ($p_page <= 0) {
		// ページ番号が0または0以下
		CommonUtil::api_log("page param error:[" . $p_page . "]");
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	
	// 必須：△のチェック
	// 緯度１経度１緯度２経度２は４つ揃っていること
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
			// add start 2016/06/15 H.Yasunaga 反映日時条件対応 [
			(!isset($p_reflect_date)			|| mb_strlen($p_reflect_date) == 0)				&&
			// add end 2016/06/15 ]
			(!isset($p_max_nl, $p_max_el, $p_min_nl, $p_min_el) ||
			mb_strlen($p_max_nl) == 0 || mb_strlen($p_max_el) == 0 || mb_strlen($p_min_nl) == 0 || mb_strlen($p_min_el) == 0) ){
		
		// パラメータに不備
		CommonUtil::api_log("invalid parameter.");
		// add start 2017/01/24 H.Yasunaga 正常時のログ抑止 エラー時のみQueryStringのデータをログ出力[
		CommonUtil::api_log("Request:[" . urldecode($_SERVER['QUERY_STRING']) ."]");
		// add end 2017/01/24 ]
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
		exit;
	}
	
	// del start 2017/01/24 H.Yasunaga 正常時のログ抑止 [
	//CommonUtil::api_log("Request:[" . urldecode($_SERVER['QUERY_STRING']) ."]");
	// del end 2017/01/24 H.Yasunaga ]

	// DBオープン
	$db = new oraDBAccess();
	if (!$db->open()) {
		$errMsg = oci_error();
		$db->close();
		CommonUtil::api_log("Database open error. code:[" . $errMsg['code'] . "] msg:[" . $errMsg['message'] ."]");
		// No5のエラー
		// 内部エラー
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
		exit;
	}
	// add 2016/06/27 H.Osamoto [
	// 認証DBオープン
	$dba = new oraDBAccess("auth");
	if (!$dba->open()) {
		$errMsg = oci_error();
		$db->close();
		$dba->close();
		CommonUtil::api_log("Database(auth) open error. code:[" . $errMsg['code'] . "] msg:[" . $errMsg['message'] ."]");
		// No5のエラー
		// 内部エラー
		header("Content-Type: text/xml");
		echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
		exit;
	}
	// add 2016/06/27 H.Osamoto ]
	// del start 2016/06/23 H.Yasunaga 不要なため削除 [
	// define.incで設定した許可APIアクセスキー・IPアドレスか確認
	//if (CommonUtil::checkSpecialPermission($p_key, $_SERVER['REMOTE_ADDR']) == false) {
	// del end ]
		//	if (ApiKeyUtil::ExistsApiKey($db, $p_key, &$internalError, &$errorMsg) === false) {		mod 2016/06/27 H.Osamoto
		if (ApiKeyUtil::ExistsApiKey($dba, $p_key, &$internalError, &$errorMsg) === false) {
			// APIアクセスキーの値は入っているが登録されていない
			if ($internalError === true) {
				// 内部エラーあり
				CommonUtil::api_log("ApiKeyUtil::ExistsApiKey error. code:[" . $errorMsg['code'] . "] message:[" . $errorMsg['message'] ."]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
			} else {
				// APIアクセスキーが不正
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
			// APIアクセスキーの値は入っているが無効になっている
			if ($internalError === true) {
				// 内部エラーあり
				CommonUtil::api_log("ApiKeyUtil::apiKeyValidation error. code:[" . $erroMsg['code'] . "] message:[" . $erroMsg['message'] . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
			} else {
				// APIアクセスキーが無効
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
			// APIアクセスキーに紐づいたIPアドレスでない
			if ($internalError === true) {
				// 内部エラーあり
				CommonUtil::api_log("ApiKeyUtil::checkIpAddress error. code:[" . $errorMsg['code'] . "] message:[" . $errorMsg['message'] . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
			} else {
				// APIアクセスキーに登録されていないIPアドレスからのアクセス
				CommonUtil::api_log("invalid ipaddress. apikey:[" . $p_key . "] ipaddress:[" . $_SERVER['REMOTE_ADDR'] . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INVALID_IPADDRESS);
			}
			$db->close();
			$dba->close();	// add 2016/06/27 H.Osamoto
			exit;
		}
		// APIのアクセスログ
		// mod 2016/06/27 H.Osamoto [
		//	ApiLogUtil::putLog($db, $p_key, $_SERVER['REMOTE_ADDR'], f_enc_to_EUC(urldecode($_SERVER['QUERY_STRING'])));
		//	$db->commitTransaction();
		ApiLogUtil::putLog($dba, $p_key, $_SERVER['REMOTE_ADDR'], f_enc_to_EUC(urldecode($_SERVER['QUERY_STRING'])));
		$dba->commitTransaction();
		// mod 2016/06/27 H.Osamoto ]
	// del start 2016/06/23 H.Yasunaga 不要なため削除 [
	//} else {
	//	// define.incで定義した許可APIアクセスキー・IPアドレスに一致
	//	// APIの利用ログは残さない
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
		// del start 2017/01/24 H.Yasunaga ログ出力の抑制 [
		//CommonUtil::api_log("near search flag on lat/lon exist"); 
		// del end 2017/01/24 ]
	}
	// 位置管理ユニークコード
	if (mb_strlen($p_office_id) != 0 && $p_office_id != '%') {
		$filterStr .= "KYOTEN_ID:FW:'" . $p_office_id . "'";
	}
	
	// 局所コード
	if (mb_strlen($p_post_code) != 0 && $p_post_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_02:FW:'" . $p_post_code . "'";
	}
	
	// 取扱店番号
	if (mb_strlen($p_dealer_no) != 0 && $p_dealer_no != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_03:FW:'" . $p_dealer_no . "'";
	}
	
	// 郵便番号
	if (mb_strlen($p_zip_code) != 0 && $p_zip_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_10:FW:'" . $p_zip_code . "'";
	}
	
	// 住所
	if (mb_strlen($p_address) != 0 && $p_address != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "ADDR:FW:'" . $p_address . "'";
		/*
		// ジオコーディング
		$nearseachFlag = true;
		CommonUtil::api_log("nearsearchFlag on exist address");
		// ジオコーディング結果を $center_elと$center_nlにいれる
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
				//緯度経度情報の取得に失敗
				CommonUtil::api_log("Geocoding error");
				CommonUtil::api_log(print_r($rec, true));
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
				exit;
			}
		} else {
			// 緯度経度情報の取得に失敗
			CommonUtil::api_log("Geocoding error");
			CommonUtil::api_log(print_r($dat, true));
			header("Content-Type: text/xml");
			echo $response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
			exit;
		}*/
	}
	
	// 郵便局会社ユニークコード
	if (mb_strlen($p_jp_network_code) != 0 && $p_jp_network_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_19:FW:'" . $p_jp_network_code . "'";
	}
	
	// 郵便局名
	if (mb_strlen($p_jp_network_name) != 0 && $p_jp_network_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_20:FW:'" . $p_jp_network_name . "'";
	}
	
	// ゆうゆう窓口ユニークコード
	if (mb_strlen($p_jp_post_code) != 0 && $p_jp_post_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_27:FW:'" . $p_jp_post_code . "'";
	}
	
	// 郵便支店名
	if (mb_strlen($p_jp_post_name) != 0 && $p_jp_post_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_29:FW:'" . $p_jp_post_name . "'";
	}
	
	// ゆうちょ店ユニークコード
	if (mb_strlen($p_jp_bank_code) != 0 && $p_jp_bank_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_36:FW:'" . $p_jp_bank_code . "'";
	}
	
	// 銀行直営店名
	if (mb_strlen($p_jp_bank_name) != 0 && $p_jp_bank_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_37:FW:'" . $p_jp_bank_name . "'";
	}
	
	// 銀行直営店正式名
	if (mb_strlen($p_jp_bank_official_name) != 0 && $p_jp_bank_official_name != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_39:FW:'" . $p_jp_bank_official_name . "'";
	}
	
	// かんぽユニークコード
	if (mb_strlen($p_jp_insurance_code) != 0 && $p_jp_insurance_code != '%') {
		if (mb_strlen($filterStr) != 0) {
			$filterStr .= " AND ";
		}
		$filterStr .= "COL_43:FW:'" . $p_jp_insurance_code . "'";
	}
	
	// add start 2016/06/27 H.Yasunaga COL_17が"t"のもののみ結果に含める [
	if (mb_strlen($filterStr) != 0) {
		$filterStr .= " AND ";
	}
	$filterStr .= "COL_17:'t'";
	// add end ]
	
	// del start 2017/01/24 H.Yasunaga ログ出力の抑制 [
	//CommonUtil::api_log("FILTER:[" . $filterStr . "]");
	// del end ]


	
	require_once(dirname(__FILE__) . "/inc/StoreNearSearch.inc");
	require_once(dirname(__FILE__) . "/inc/StoreSearch.inc");
	
	// 検索引数設定
	// (1ページあたりの件数× (ページ数 -1)) + 1
	// 1ページ目は"1"
	// 2ページ目は1ページ当たりの件数 + 1
	$POS = ($p_result * ($p_page -1)) + 1;
	$CNT = $p_result;
	
	// add start 2016/06/15 H.Yasunaga 反映日時条件対応 [
	// 反映日時
	// 入力された値からハイフン・コロン・半角スペースを除き、年月日時までの10文字にする
	$REFLECTDATE = "";
	if (empty($p_reflect_date) != true) {
		// '-'・':'・' '(半角スペース)を除去する
		// 「2016-06-15 12:34:56」→ 「20160615123456」
		$refdate_search = array('-', ':', ' ');
		$refdate_rep = array('','','');
		$REFLECTDATE = str_replace($refdate_search, $refdate_rep, $p_reflect_date);
		// 分と秒をカットする（PUB_S_DATEが時までしかないため)
		// 「20160615123456」→ 「2016061512」
		if (mb_strlen($REFLECTDATE) > 10) {
			$REFLECTDATE = mb_substr($REFLECTDATE, 0, 10);
		}
	}
	// add end 2016/06/15 H.Yasunaga ]
	
	// add start 2016/08/24 H.Yasunaga 座標種別[coord]パラメータ追加 [
	// 座標種別[coord]
	// coord=Z or coord=M or coord=W
	$COORD = "";
	// mod start 2016/12/16 H.Yasunaga 座標種別[coord]に"W"を追加 レスポンスの緯度経度を世界測地系にする [
	//if ($p_coord == DEF_COORD_ZENRIN || $p_coord == DEF_COORD_MAPION) {
	if ($p_coord == DEF_COORD_ZENRIN || $p_coord == DEF_COORD_MAPION || $p_coord == DEF_COORD_WORLD) {
	// mod end 2016/12/16 H.Yasunaga ]
		// Z : ゼンリン座標(lat,lon)
		// M : Mapion座標(COL_194[Mapion緯度,COL_195[Mapion経度])
		// W : ゼンリン座標(lat,lon)を世界測地系に変換して返す
		$COORD = $p_coord;
	} else {
		$COORD = DEF_COORD_MAPION;
	}
	// add end 2016/08/24 H.Yasunaga ]
	
	if ($nearseachFlag == true) {
		// 緯度経度がある→最寄り店検索
		$LAT = $center_nl;
		$LON = $center_el;
		
		// mod start 2016/06/24 H.Yasunaga 緯度経度指定ミス修正[
		//$NELAT = $p_min_nl;
		//$NELON = $p_min_el;
		//$SWLAT = $p_max_nl;
		//$SWLON = $p_max_el;
		
		$NELAT = $p_max_nl;	// 北東緯度
		$NELON = $p_max_el;	// 北東経度
		$SWLAT = $p_min_nl;	// 南西緯度
		$SWLON = $p_min_el;	// 南西経度
		// mod end ]
		
		$FILTER = $filterStr;
		// del start 2017/01/24 H.Yasunaga ログ出力の抑制 [
		//CommonUtil::api_log("StoreNearSearch");
		//CommonUtil::api_log("LAT:[" . $LAT . "]\n" .
		//					"LON:[" . $LON . "]\n" .
		//					"NELAT:[" . $NELAT . "]\n" .
		//					"NELON:[" . $NELON . "]\n" .
		//					"SWLAT:[" . $SWLAT . "]\n" .
		//					"SWLON:[" . $SWLON . "]\n" .
		//					"FILTER:[" . $FILTER . "]\n" .
		//					// add start 2016/06/15 H.Yasunaga 反映日時条件対応 [
		//					"REFLECTDATE:[" . $REFLECTDATE . "]\n" .
		//					// add end 2016/06/15 ]
		//					// add start 2016/08/24 H.Yasunaga 座標種別[coord]パラメータ追加 [
		//					"COORD:[" . $COORD . "]\n" .
		//					// add end 2016/08/24 ]
		//					"POS:[" . $POS . "]\n" .
		//					"CNT:[" . $CNT . "]");
		// del end ]
							
		// mod start 2016/06/15 H.Yasunaga 反映日時条件対応 [
		// $searchRes = StoreNearSearch::Search($db, $cid, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN);
		// mod start 2016/08/24 H.Yasunaga 座標種別[coord]追加 [
		//$searchRes = StoreNearSearch::Search($db, $cid, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $REFLECTDATE, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN);
		$searchRes = StoreNearSearch::Search($db, $cid, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $REFLECTDATE, $COORD,$POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN);
		// mod end 2016/08/24 H.Yasunaga ]
		// mod end 2016/06/15 H.Yasunaga ]
	} else {
		// 緯度経度が無い→店舗条件検索
		$FILTER = $filterStr;

		// del start 2017/01/24 H.Yasunaga ログ出力の抑制 [
		//CommonUtil::api_log("StoreSerach");
		//CommonUtil::api_log("FILTER:[" . $FILTER . "]\n" .
		//					// add start 2016/06/15 H.Yasunaga 反映日時条件対応 [
		//					"REFLECTDATE:[" . $REFLECTDATE . "]\n" .
		//					// add end 2016/06/15 ]
		//					// add start 2016/08/24 H.Yasunaga 座標種別[coord]パラメータ追加 [
		//					"COORD:[" . $COORD . "]\n" .
		//					// add end 2016/08/24 ]
		//					"POS:[" . $POS . "]\n" .
		//					"CNT:[" . $CNT . "]");
		// del end ]
							
		// mod start 2016/06/15 H.Yasunaga 反映日時条件対応 [
		// $searchRes = StoreSearch::Search($db, $cid, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN );
		// mod start 2016/08/24 H.Yasunaga 座標種別[coord]追加 [
		//$searchRes = StoreSearch::Search($db, $cid, $FILTER, $REFLECTDATE, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN );
		$searchRes = StoreSearch::Search($db, $cid, $FILTER, $REFLECTDATE, $COORD,$POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN );
		// mod end 2016/08/24 ]
		// mod end 2016/06/15 ]
	}
	
	if ($searchRes == DEF_RETCD_DE || $searchRes == DEF_RETCD_DEND) {
		// データ有
		$response->addData($ARR_KYOTEN);
		$response->setTotalNum($HIT_NUM);
		$response->setReturnNum($REC_NUM);
		$response->setStartPosition($POS);
		header("Content-Type: text/xml");
		echo $response->createXML();
	} else {
		switch($searchRes) {
			case DEF_RETCD_DNE :{
				// 0件
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_ITEM_NOT_FOUND);
				break;
			}
			case DEF_RETCD_DERR1:
			case DEF_RETCD_DERR2:
			case DEF_RETCD_DERR3: {
				// データベースエラー
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
				break;
			}
			case DEF_RETCD_PERR1:
			case DEF_RETCD_PERR2:
			case DEF_RETCD_PERR3: {
				// 入力パラメータエラー
				header("Content-Type: text/xml");
				$response->createErrorResponse(API_ERROR_INVALID_PARAMETER);
				break;
			}
			default: {
				// その他（ありえない）
				CommonUtil::api_log("search return value error. value:[" . $searchRes . "]");
				header("Content-Type: text/xml");
				echo $response->createErrorResponse(API_ERROR_INTERNAL_SERVER);
				break;
			}
		}
	}
	// DB閉じ
	$db->commitTransaction();
	$db->close();
	$dba->close();	// add 2016/06/27 H.Osamoto
	exit;
?>