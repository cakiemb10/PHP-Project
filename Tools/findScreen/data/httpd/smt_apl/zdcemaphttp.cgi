<?PHP
// ------------------------------------------------------------
// ����PHP AJAX�̿��⥸�塼��
// 
// ��ȯ����
//   2007/03/01 bando@D&I
//     JSAPI��call.cgi(2007/02/23����)��١����˿�������
//   2007/08/16 matsukawa
//     target-url�⡢�ѥ�᡼������Ρ�&�ס�=�ס�?�פ��б�
// 2011/07/05 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/10/12 Y.Matsukawa	error_reporting���
// 2013/08/02 F.Yokoi   	�����������ؤΥ���������IP���ɥ쥹���顼�б�
// 2014/02/10 Y.Matsukawa	�ȼ����к���XSS����
// 2016/03/18 Y.Matsukawa	Ĺ��URL�б��ʥ�ե��顼�����ղä��ʤ���
// ------------------------------------------------------------
// ����
// target�����Ϥ��줿URL�ϡ��ѥ�᡼������Ρ�&�ס�=�ס�?�פ��ͤȤ���ǧ��������٤ˡ�
// �̾�Ȥϰۤʤ�ѥ�����ǲ�ᤵ��ޤ���
// ������������դ��Ƥ���������
// ���ѥ�᡼�����ڤ�Ȥ��ƤΡ�&�פϡ�ɬ���֥ѥ�᡼��̾=�פȥ��åȤǵ��Ҥ��뤳�ȡ�
//   ��������Τ褦�ˡ���&�פ�ñ�Ȥ�¸�ߤ��Ƥ����硢���Ρ�&�פ��ͤΰ����ȸ��ʤ���ޤ���
//   �����http://myhost/index.html?cid=xxx&&kid=999&icn=001&
//         ��cid���͡��xxx&�פȤ��ư����Ƥ��ޤ��ޤ�
//         ��icn���͡��001&�פȤ��ư����Ƥ��ޤ��ޤ�
//
// �פ�̥Х���ư���Զ��ˤʤ�Τǡ������̿���URL�Ͻ�ʬ��դ��Ƥ���������
// �ä˥롼�פ�URL����Ȥ������դ��Ƥ���������
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
// �����ʳ����������ϻ��ϥ��顼
if (!ctype_digit($_GET["zdccnt"])) {
	exit;
}
if ($_GET["encodeflg"] != "" && !ctype_digit($_GET["encodeflg"])) {
	exit;
}
// ��������å�
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

//URL���¥����å�
//if (!check_domain_list(&$tgt)){
//	$js_content = "ZdcEmapHttpTimeoutCnt[$zdccnt] = 'domain error';";
//	header("Content-Type: application/x-javascript");
//	echo $js_content;
//	exit;
//}

//�ѥ�᡼����Υ��󥳡��ɽ���
$prm_vars = explode("&", $prm);
$prm = "";
foreach( $prm_vars as $pval ){
	//	list($key,$val) = explode("=", $pval);
	//	$key = str_replace(" ", "", $key);
	//	//��������ʸ��������"EUC-JP"�˴󤻤�
	//	$prm .= (($prm != "")?"&":"") . $key . "=" . urlencode(mb_convert_encoding($val, "EUC-JP", "auto"));
	if (strpos($pval, "=") === false) {
		// mod 2011/07/05 Y.Nakajima
		//$prm .= urlencode("&".mb_convert_encoding($pval, "EUC-JP", "auto"));
		$prm .= urlencode("&".mb_convert_encoding($pval, "eucJP-win", "auto"));
	} else {
		list($key,$val) = explode("=", $pval, 2);
		$key = str_replace(" ", "", $key);
		//��������ʸ��������"EUC-JP"�˴󤻤�
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
