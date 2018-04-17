<?PHP
// ------------------------------------------------------------
// ����PHP AJAX�̿��⥸�塼��
// ��target URL��Υѥ�᡼���ͤ�EUC��URL���󥳡��ɺѤߤ�����
// �����⥸�塼����ǡ��ƥѥ�᡼���ͤΥ��󥳡��ɽ����ϹԤ�ʤ�
// 
// ��ȯ����
// 2012/09/10 Y.Matsukawa	��������
// 2013/08/30 F.Yokoi   	�����������ؤΥ���������IP���ɥ쥹���顼�б�
// 2014/02/10 Y.Matsukawa	�ȼ����к���XSS����
// 2016/03/18 Y.Matsukawa	Ĺ��URL�б��ʥ�ե��顼�����ղä��ʤ���
// ------------------------------------------------------------
ini_set("display_errors", "False");

if( $_GET["target"] == "" ){
	exit;
}
if( $_GET["zdccnt"] == "" ){
	exit;
}
// add 2014/02/10 Y.Matsukawa [
// �����ʳ����������ϻ��ϥ��顼
if (!ctype_digit($_GET["zdccnt"])) {
	exit;
}
// add 2014/02/10 Y.Matsukawa ]
if( $_GET["zdccnt"] == "" ){
	$encodeflg = false;
}else{
	$encodeflg = $_GET["encodeflg"];
}
$zdccnt = $_GET["zdccnt"];
$enc    = $_GET["enc"];
if ($enc == "EUC"){
	$ENC = "EUC-JP";
} else if ($enc == "SJIS"){
	$ENC = "SJIS";
} else if ($enc == "UTF8"){
	$ENC = "UTF-8";
} else {
	$ENC = $enc;
}
// enc���������å�		add 2014/02/10 Y.Matsukawa
if (preg_match("/.*[^a-zA-Z0-9\\-_].*/", $ENC)) {
	exit;
}

$URL = $_GET["target"];
if (!isset($_GET['NOREF']) || $_GET['NOREF'] == '') {		// add 2016/03/18 Y.Matsukawa
	//mod 2013/08/30 F.Yokoi [
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
	//$URL = $URL."&P_REMOTE_ADDR=".urlencode($REMOTE_ADDR);
	//$URL = $URL."&P_HTTP_REFERER=".urlencode($_SERVER["HTTP_REFERER"]);
	//$URL = $URL."&P_HTTP_USER_AGENT=".urlencode($_SERVER["HTTP_USER_AGENT"]);
	//mod 2013/08/30 F.Yokoi ]
}
//URL�ƤӽФ�
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
