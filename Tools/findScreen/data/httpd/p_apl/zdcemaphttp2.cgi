<?PHP
// ------------------------------------------------------------
// 汎用PHP AJAX通信モジュール
// ※target URL中のパラメータ値はEUCでURLエンコード済みの前提
// ※当モジュール内で、各パラメータ値のエンコード処理は行わない
// 
// 開発履歴
// 2012/09/07 Y.Matsukawa	新規作成
// 2013/11/28 Y.Matsukawa	セキュリティ対応（MHTML XSS）
// 2015/08/27 Y.Matsukawa	セキュリティ対応（OS Command Injection）
// ------------------------------------------------------------
ini_set("display_errors", "False");

if( $_GET["target"] == "" ){
	exit;
}
if( $_GET["zdccnt"] == "" ){
	exit;
}
// add 2013/11/28 Y.Matsukawa [
// 数字以外の不正入力時はエラー
if (!ctype_digit($_GET["zdccnt"])) {
	exit;
}
// add 2013/11/28 Y.Matsukawa ]

$zdccnt = $_GET["zdccnt"];
$URL = $_GET["target"];

// target不正		add 2015/08/27 Y.Matsukawa
$urlerr = false;
$u = parse_url($URL);
if (!$u) {
	$urlerr = true;
} else if ($u['scheme'] != 'http' && $u['scheme'] != 'https') {
	$urlerr = true;
} else if ($u['host'] != '127.0.0.1' && $u['host'] != 'localhost') {
	$urlerr = true;
}
if ($urlerr) {
	error_log(date("Y/m/d H:i:s")." ".$_SERVER['SCRIPT_NAME']." Invalid target [".$URL."]\n", 3, "/var/tmp/p_err_".date("Ymd").".log");
	exit;
}

if (isset($_SERVER["REMOTE_ADDR"])) {
	$URL = $URL."&P_REMOTE_ADDR=".urlencode($_SERVER["REMOTE_ADDR"]);
} else {
	$URL = $URL."&P_REMOTE_ADDR=";
}
if (isset($_SERVER["HTTP_REFERER"])) {
	$URL = $URL."&P_HTTP_REFERER=".urlencode($_SERVER["HTTP_REFERER"]);
} else {
	$URL = $URL."&P_HTTP_REFERER=";
}
if (isset($_SERVER["HTTP_USER_AGENT"])) {
	$URL = $URL."&P_HTTP_USER_AGENT=".urlencode($_SERVER["HTTP_USER_AGENT"]);
} else {
	$URL = $URL."&P_HTTP_USER_AGENT=";
}

//error_log(date("Y/m/d H:i:s")." URL=$URL"."\n", 3, "/var/tmp/p_debug_".date("Ymd").".log");

// URL呼び出し
$contents = "";
$handle = fopen($URL, "rb");
if($handle){
	while (!feof($handle)) {
	  $contents .= fread($handle, 8192);
	}
	fclose($handle);
}

//error_log(date("Y/m/d H:i:s")." contents=$contents"."\n", 3, "/var/tmp/p_debug_".date("Ymd").".log");

if(strlen($contents) > 0){
	$contents = str_replace("\r", "\\r", $contents);
	$contents = str_replace("\n", "\\n", $contents);
	$contents = str_replace("\t", "\\t", $contents);
	$contents = str_replace("'", "\\'", $contents);
	$js_content = "ZdcEmapHttpResult[$zdccnt] = '". $contents . "';";
}else{
	$js_content = "ZdcEmapHttpTimeoutCnt[$zdccnt] = 'no file';";
}

header("Content-Type: application/x-javascript");

echo $js_content;

?>
