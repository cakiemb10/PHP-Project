<?php
/*========================================================*/
// ファイル名：ytc_securtycode_check.cgi
// 処理名：セキュリティコード確認
//
// 作成日：2017/05/08
// 作成者：H.Yasunaga
//
// 解説：ヤマト様ロッカーセキュリティコードの確認用
//
// 更新履歴
// 2017/05/08 H.Yasunaga	新規作成
// 2017/05/29 H.Yasunaga	rd_store_id.cgiの呼び出し時のプロトコルをhttpに固定
/*========================================================*/
	include('d_serv_emap.inc');
	require_once('d_serv_cgi.inc');
	include("log.inc");         // ログ出力
	require_once('function.inc');
	
	// JSONを扱うライブラリ
	require_once("/home/emap/src/Jsphon/Decoder.php");
	require_once("/home/emap/src/Jsphon/Encoder.php");
	
	//ログ出力開始
	include("logs/inc/com_log_open.inc");
	
	$enc = "EUC";		//出力文字コード
	
	$cid = "";		// 企業ID
	$kid = "";		// 対象拠点ID
	$grpid = "";	// RDデータのセキュリティコードのグループID
	$itmid = "";	// RDデータのセキュリティコードのアイテムID
	$scode = "";	// セキュリティコード
	
	
	$APICGINM = "rd_store_id.cgi";	// rdデータ取得cgi
	
	// クロスドメイン対応
	header("Access-Control-Allow-Origin: *");
	header('content-type: application/json; charset=utf-8');
	
	// rd_store_id.cgiを呼び出す
	if ( isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] == "POST" ) {
		if (isset($_POST["cid"])) {
			$cid = $_POST["cid"];
		}
		if (isset($_POST["kid"])) { 
			$kid = $_POST["kid"];
			$kid = str_replace(' ', '', $kid);
		}
		if (isset($_POST["grpid"])) {
			$grpid = $_POST["grpid"];
			$grpid = str_replace(' ', '', $grpid);
		}
		if (isset($_POST["itmid"])) {
			$itmid = $_POST["itmid"];
			$itmid = str_replace(' ', '', $itmid);
		}
		if (isset($_POST["scode"])) {
			$scode = $_POST["scode"];
		}
	} else {
		// POSTメソッドでないエラー
		echo createErrorJson('methodError');
		exit;
		
	}
	
	if (strlen($cid) == 0 || strlen($kid) == 0 || strlen($scode) == 0 || strlen($grpid) == 0 || strlen($itmid) == 0 ) {
		// パラメータのエラー
		// 出力
		echo createErrorJson('parameterError');
		exit;
	}
	
	// rd_store_id.cgi用パラメータの作成
	$param = "?";
	// 企業ID
	$param .= "cid=" . $cid;
	// 拠点ID
	$param .= "&kid=" . $kid;
	// グループ番号
	$param .= "&grp=" . $grpid;
	// 文字コード
	$param .= "&enc=EUC";
	// 出力形式
	$param .= "&outf=JSON";
	
	// rd_store_id.cgi
	// mod 2017/05/29 H.Yasunaga プロトコルを変更 [
	//$CGI = "$protocol://127.0.0.1/cgi/".$APICGINM.$param;
	$CGI = "http://127.0.0.1/cgi/".$APICGINM.$param;
	// mod 2017/05/29 H.Yasunaga ]

	$result = file_get_contents($CGI);
	if (!$result) {
		// file_get_contentのエラー
		// 出力
		echo createErrorJson('cgiError');
		exit;
	}
	
	// JSONの読み込み
	// jsonデコーダの生成
	$decoder = new Jsphon_Decoder();
	$json = $decoder->decode($result);
	$decoder = null;

	// リターンコード
	$return_code = $json["return_code"];

	if ($return_code != "y1100000") {
		// rd_store_id.cgiのリターンコードが正常でない
		// 出力
		echo createErrorJson('cgiError[' . $return_code . ']');
		exit;
	}
	// 拠点数
	$store_count = $json["store_count"];
	// 拠点リスト
	$store_list = $json["store_list"];
	
	// RDデータのセキュリティコード
	$kyoten_securitycode = null;
	for($i = 0; $i < count($store_list); $i++) {
		// "store_list"内で指定した拠点IDと一致するものを探す
		if ($store_list[$i]["store_id"] == $kid) {
			for($j = 0; $j < count($store_list[$i]["group_list"]); $j++) {
				// group_list内で指定したグループIDと一致するものを探す
				if ($store_list[$i]["group_list"][$j]["group_id"] == $grpid) {
					for($k = 0; $k < count($store_list[$i]["group_list"][$j]["item_list"]); $k++) {
						// item_list内で指定した項目IDと一致するものを探す
						if ($store_list[$i]["group_list"][$j]["item_list"][$k]["item_id"] == $itmid) {
							if ($store_list[$i]["group_list"][$j]["item_list"][$k]["type"] == "TEXT") {
								$kyoten_securitycode = $store_list[$i]["group_list"][$j]["item_list"][$k]["text"];
							}
						}
					}
				}
			}
		}
	}
	
	// POSTされたセキュリティコードと取得したセキュリティコードの確認
	if ($kyoten_securitycode != null && strcmp($scode, $kyoten_securitycode) === 0) {
		// セキュリティコードが一致
		$out_json = createJson(true);
	}else {
		// セキュリティコードが不一致
		$out_json = createJson(false);
	}
	
	// 出力
	echo $out_json;
	exit;
	
	// レスポンスJSONの作成
	// $matchflg:postされたセキュリティコードと、RDデータのセキュリティコードの一致したかどうかのフラグ
	//   true:一致 false:不一致
	function createJson($matchflg) {
		$message = $matchflg ? "match":"mismatch";
		$output = array('status'=>true, 'match'=>$matchflg, 'message'=>$message);
		$json_encoder = new Jsphon_Encoder();
		$value = $json_encoder->encode($output);
		$json_encoder = null;
		return $value;
	}
	
	// レスポンスJSONの作成（エラー版）
	// $errMsg:レスポンスに含めるエラーメッセージ
	function createErrorJson($errMsg) {
		$output = array('status'=>false, 'match'=>false, 'message'=>$errMsg);
		$json_encoder = new Jsphon_Encoder();
		$value = $json_encoder->encode($output);
		$json_encoder = null;
		return $value;
	}
?>