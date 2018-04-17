<?PHP
// ------------------------------------------------------------
// 汎用PHP AJAX通信モジュール
// 
// 開発履歴
//   2007/03/01 bando@D&I
//     JSAPIのcall.cgi(2007/02/23時点)をベースに新規作成
//   2007/08/16 matsukawa
//     target-url内、パラメータ値中の「&」「=」「?」に対応
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/10/12 Y.Matsukawa	error_reporting削除
// 2013/08/02 F.Yokoi   	アクセスログへのアクセス元IPアドレスエラー対応
// 2014/02/10 Y.Matsukawa	脆弱性対策（XSS等）
// 2016/03/18 Y.Matsukawa	長尺URL対応（リファラー等を付加しない）
// ------------------------------------------------------------
// ※注※
// targetに入力されたURLは、パラメータ値中の「&」「=」「?」を値として認識させる為に、
// 通常とは異なるパターンで解釈されます。
// 下記の点に注意してください。
// ■パラメータ区切りとしての「&」は、必ず「パラメータ名=」とセットで記述すること。
//   下記の例のように、「&」が単独で存在している場合、その「&」は値の一部と見なされます。
//   （例）http://myhost/index.html?cid=xxx&&kid=999&icn=001&
//         →cidの値＝「xxx&」として扱われてしまいます
//         →icnの値＝「001&」として扱われてしまいます
//
// 思わぬバグや動作不具合になるので、内部通信のURLは充分注意してください。
// 特にループでURLを作るところは注意してください。
//

//include("domain.inc");

//error_reporting(E_PARSE );		del 2012/10/12 Y.Matsukawa
ini_set("display_errors", "False");

//if( $HTTP_GET_VARS["target"] == "" ){
if( $_GET["target"] == "" ){
	exit;
}

//if( $HTTP_GET_VARS["zdccnt"] == "" ){
if( $_GET["zdccnt"] == "" ){
	exit;
}

// add 2014/02/10 Y.Matsukawa [
// 数字以外の不正入力時はエラー
if (!ctype_digit($_GET["zdccnt"])) {
	exit;
}
if ($_GET["encodeflg"] != "" && !ctype_digit($_GET["encodeflg"])) {
	exit;
}
// 桁数チェック
if (strlen($_GET["encodeflg"]) > 1) {
	exit;
}
// add 2014/02/10 Y.Matsukawa ]

//if( $HTTP_GET_VARS["zdccnt"] == "" ){
if( $_GET["zdccnt"] == "" ){
	$encodeflg = false;
}else{
	//$encodeflg = $HTTP_GET_VARS["encodeflg"];
	$encodeflg = $_GET["encodeflg"];
}

//$zdccnt = $HTTP_GET_VARS["zdccnt"];
//$enc = $HTTP_GET_VARS["enc"];
$zdccnt = $_GET["zdccnt"];
$enc    = $_GET["enc"];
//$ENC = ($enc) ? $enc : "auto";
if ($enc == "EUC"){
	$ENC = "EUC-JP";
} else if ($enc == "SJIS"){
	$ENC = "SJIS";
} else if ($enc == "UTF8"){
	$ENC = "UTF-8";
} else {
	$ENC = $enc;
}

//$url = $HTTP_GET_VARS["target"];
$url = $_GET["target"];
list($tgt, $prm) = explode("?", $url, 2);

//URL制限チェック
//if (!check_domain_list(&$tgt)){
//	$js_content = "ZdcEmapHttpTimeoutCnt[$zdccnt] = 'domain error';";
//	header("Content-Type: application/x-javascript");
//	echo $js_content;
//	exit;
//}

//パラメータ毎のエンコード処理
$prm_vars = explode("&", $prm);
$prm = "";
foreach( $prm_vars as $pval ){
	//	list($key,$val) = explode("=", $pval);
	//	$key = str_replace(" ", "", $key);
	//	//内部処理文字コード"EUC-JP"に寄せる
	//	$prm .= (($prm != "")?"&":"") . $key . "=" . urlencode(mb_convert_encoding($val, "EUC-JP", "auto"));
	if (strpos($pval, "=") === false) {
		// mod 2011/07/05 Y.Nakajima
		//$prm .= urlencode("&".mb_convert_encoding($pval, "EUC-JP", "auto"));
		$prm .= urlencode("&".mb_convert_encoding($pval, "eucJP-win", "auto"));
	} else {
		list($key,$val) = explode("=", $pval, 2);
		$key = str_replace(" ", "", $key);
		//内部処理文字コード"EUC-JP"に寄せる
		// mod 2011/07/05 Y.Nakajima
		//$prm .= (($prm != "")?"&":"") . $key . "=" . urlencode(mb_convert_encoding($val, "EUC-JP", "auto"));
		$prm .= (($prm != "")?"&":"") . $key . "=" . urlencode(mb_convert_encoding($val, "eucJP-win", "auto"));
	}
}
$URL = $tgt."?".$prm;

if (!isset($_GET['NOREF']) || $_GET['NOREF'] == '') {		// add 2016/03/18 Y.Matsukawa
//mod 2013/08/02 F.Yokoi [
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
}		// add 2016/03/18 Y.Matsukawa
//$URL = $URL."&P_REMOTE_ADDR=".urlencode($REMOTE_ADDR);
//$URL = $URL."&P_HTTP_REFERER=".urlencode($_SERVER["HTTP_REFERER"]);
//$URL = $URL."&P_HTTP_USER_AGENT=".urlencode($_SERVER["HTTP_USER_AGENT"]);
//mod 2013/08/02 F.Yokoi ]

//URL呼び出し
$contents = "";
$handle = fopen($URL, "rb");
if($handle){
	while (!feof($handle)) {
	    $contents .= fread($handle, 8192);
	}
	fclose($handle);
}

if(strlen($contents) > 0)
{
	if($encodeflg){
		if(strcasecmp($ENC, "UTF-8") != 0)
		{
			$contents = i18n_convert($contents, "UTF-8", $ENC);
			$contents = str_replace("\0", '', $contents);
		}
		$contents = rawurlencode($contents);
	}else{
		$contents = str_replace("\r", "\\r", $contents);
		$contents = str_replace("\n", "\\n", $contents);
		$contents = str_replace("\t", "\\t", $contents);
		$contents = str_replace("'", "\\'", $contents);
	}
	$js_content = "ZdcEmapHttpResult[$zdccnt] = '". $contents . "';";
}else
{
	$js_content = "ZdcEmapHttpTimeoutCnt[$zdccnt] = 'no file';";
}

header("Content-Type: application/x-javascript");

echo $js_content;

?>
