<?PHP
// ------------------------------------------------------------
// 汎用PHP AJAX通信モジュール
// 
// 開発履歴
//   2007/03/01 bando@D&I
//     JSAPIのcall.cgi(2007/02/23時点)をベースに新規作成
//   2007/08/16 matsukawa
//     target-url内、パラメータ値中の「&」「=」「?」に対応
// 2012/08/08 Y.Matsukawa	error_reporting記述削除
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

//error_reporting(E_PARSE );		del 2012/08/08 Y.Matsukawa
ini_set("display_errors", "False");

//mod 2011/10/03 Y.Nakajima
//if( $HTTP_GET_VARS["target"] == "" ){
if( $_GET["target"] == "" ){
	exit;
}

//mod 2011/10/03 Y.Nakajima
//if( $HTTP_GET_VARS["zdccnt"] == "" ){
if( $_GET["zdccnt"] == "" ){
	exit;
}

//mod 2011/10/03 Y.Nakajima
//if( $HTTP_GET_VARS["zdccnt"] == "" ){
if( $_GET["zdccnt"] == "" ){
	$encodeflg = false;
}else{
//mod 2011/10/03 Y.Nakajima
	//$encodeflg = $HTTP_GET_VARS["encodeflg"];
	$encodeflg = $_GET["encodeflg"];
}

//mod 2011/10/03 Y.Nakajima [
//$zdccnt = $HTTP_GET_VARS["zdccnt"];
//$enc = $HTTP_GET_VARS["enc"];
$zdccnt = $_GET["zdccnt"];
$enc    = $_GET["enc"];
//mod 2011/10/03 Y.Nakajima ]
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

//mod 2011/10/03 Y.Nakajima
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
		$prm .= urlencode("&".mb_convert_encoding($pval, "EUC-JP", "auto"));
	} else {
		list($key,$val) = explode("=", $pval, 2);
		$key = str_replace(" ", "", $key);
		//内部処理文字コード"EUC-JP"に寄せる
		$prm .= (($prm != "")?"&":"") . $key . "=" . urlencode(mb_convert_encoding($val, "EUC-JP", "auto"));
	}
}
$URL = $tgt."?".$prm;
//mod 2011/10/03 Y.Nakajima [
//$URL = $URL."&P_REMOTE_ADDR=".urlencode($REMOTE_ADDR);
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
//mod 2011/10/03 Y.Nakajima ]


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
