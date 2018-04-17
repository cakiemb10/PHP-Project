<?PHP
// ------------------------------------------------------------
// 2011/01/11 Y.Matsukawa	リファラーに含まれる半角スペースを除去、REFERERを255バイトに丸める
// 2011/05/06 Y.Matsukawa	【不具合修正】改行コード混入
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// ------------------------------------------------------------
/**
* 関数名 ：  put_log
* 概  要 ：  ログ出力
* 引  数 ：  $retcd     - リターンコード（例）80419200
*            $key       - APIキー（デコード済）
             $emap_cid  - e-map企業コード
             $parms     - パラメータ文字列（半角スペース区切り）
* 戻り値 ：  なし
**/
function put_log($retcd, $key, $emap_cid, $parms) {
	global $log_api;
	
	// mod 2011/07/05 Y.Nakajima [
	if (isset($_SERVER["HTTP_REFERER"]) && $_SERVER["HTTP_REFERER"] != "") {
	$REFERER = $_SERVER["HTTP_REFERER"];
	} else {
	$REFERER = "";
	}
	if(isset($_POST["P_HTTP_REFERER"]) && $_POST["P_HTTP_REFERER"] != "") $REFERER = $_POST["P_HTTP_REFERER"];
	if(isset($_GET["P_HTTP_REFERER"]) && $_GET["P_HTTP_REFERER"]  != "") $REFERER = $_GET["P_HTTP_REFERER"];
	$W_REFERER = "";
	$W_PARM = "";
	
	if (count(explode("?", $REFERER, 2)) == 2 ) {
		list($W_REFERER, $W_PARM) = explode("?", $REFERER, 2);
	} else {
		//?が存在しないとき
		$W_REFERER = $REFERER;
	}
	// mod 2011/07/05 Y.Nakajima ]
	//$REFERER = dirname($W_REFERER . "*");		del 2011/01/11 Y.Matsukawa
	// add 2011/01/11 Y.Matsukawa [
	$REFERER = $W_REFERER;
	$REFERER = str_replace(' ', '', $REFERER);
	$REFERER = mb_strimwidth($REFERER, 0, 255, '...');
	// add 2011/01/11 Y.Matsukawa ]
	$CID  = format_log_string(trim(substr($key, 15, 15)));
	$SERVICE_CODE = format_log_string(trim(substr($key, 14, 1)));
	// add 2011/05/06 Y.Matsukawa [
	$parms = mb_ereg_replace("\r\n", "", $parms);
	$parms = mb_ereg_replace("\r",   "", $parms);
	$parms = mb_ereg_replace("\n",   "", $parms);
	// add 2011/05/06 Y.Matsukawa ]
	
	// ログ出力
	$log_api->info($CID.' '.$emap_cid.' '.$REFERER.' '.$retcd.' '.$SERVICE_CODE.' '.$parms);

	// ログ出力終了
	include("logs/inc/com_log_close.inc");
}

/**
* 関数名 ：  format_log_string
* 概  要 ：  文字列をログ出力用に整形
* 引  数 ：  $str - 文字列
* 戻り値 ：  整形後文字列
**/
function format_log_string($str) {
	// 前後の空白を除去
	$str = trim($str);
	// 改行コードを"_"に置換
	$str = str_replace("\r\n", "_", $str);
	$str = str_replace("\r",   "_", $str);
	$str = str_replace("\n",   "_", $str);
	// 半角スペースを除去
	$str = str_replace(" ",    "_", $str);
	
	return $str;
}

/**
* 関数名 ：  put_query_log
* 概  要 ：  ログ出力
* 引  数 ：  $query     - 実行query
* 戻り値 ：  なし

// 更新履歴
// 2011/07/05 Y.Nakajima	新規作成
**/
function put_query_log($query) {
	global $log_api;
	if ($query != "") {
		$parms = mb_ereg_replace("\r\n", "", $query);
		$parms = mb_ereg_replace("\r",   "", $query);
		$parms = mb_ereg_replace("\n",   "", $query);
	
		// ログ出力
		$log_api->info($query.' ');

	}
}


?>
