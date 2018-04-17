<?php
/*========================================================*/
// �ե�����̾��ytc_securtycode_check.cgi
// ����̾���������ƥ������ɳ�ǧ
//
// ��������2017/05/08
// �����ԡ�H.Yasunaga
//
// ���⡧��ޥ��ͥ�å����������ƥ������ɤγ�ǧ��
//
// ��������
// 2017/05/08 H.Yasunaga	��������
// 2017/05/29 H.Yasunaga	rd_store_id.cgi�θƤӽФ����Υץ�ȥ����http�˸���
/*========================================================*/
	include('d_serv_emap.inc');
	require_once('d_serv_cgi.inc');
	include("log.inc");         // ������
	require_once('function.inc');
	
	// JSON�򰷤��饤�֥��
	require_once("/home/emap/src/Jsphon/Decoder.php");
	require_once("/home/emap/src/Jsphon/Encoder.php");
	
	//�����ϳ���
	include("logs/inc/com_log_open.inc");
	
	$enc = "EUC";		//����ʸ��������
	
	$cid = "";		// ���ID
	$kid = "";		// �оݵ���ID
	$grpid = "";	// RD�ǡ����Υ������ƥ������ɤΥ��롼��ID
	$itmid = "";	// RD�ǡ����Υ������ƥ������ɤΥ����ƥ�ID
	$scode = "";	// �������ƥ�������
	
	
	$APICGINM = "rd_store_id.cgi";	// rd�ǡ�������cgi
	
	// �����ɥᥤ���б�
	header("Access-Control-Allow-Origin: *");
	header('content-type: application/json; charset=utf-8');
	
	// rd_store_id.cgi��ƤӽФ�
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
		// POST�᥽�åɤǤʤ����顼
		echo createErrorJson('methodError');
		exit;
		
	}
	
	if (strlen($cid) == 0 || strlen($kid) == 0 || strlen($scode) == 0 || strlen($grpid) == 0 || strlen($itmid) == 0 ) {
		// �ѥ�᡼���Υ��顼
		// ����
		echo createErrorJson('parameterError');
		exit;
	}
	
	// rd_store_id.cgi�ѥѥ�᡼���κ���
	$param = "?";
	// ���ID
	$param .= "cid=" . $cid;
	// ����ID
	$param .= "&kid=" . $kid;
	// ���롼���ֹ�
	$param .= "&grp=" . $grpid;
	// ʸ��������
	$param .= "&enc=EUC";
	// ���Ϸ���
	$param .= "&outf=JSON";
	
	// rd_store_id.cgi
	// mod 2017/05/29 H.Yasunaga �ץ�ȥ�����ѹ� [
	//$CGI = "$protocol://127.0.0.1/cgi/".$APICGINM.$param;
	$CGI = "http://127.0.0.1/cgi/".$APICGINM.$param;
	// mod 2017/05/29 H.Yasunaga ]

	$result = file_get_contents($CGI);
	if (!$result) {
		// file_get_content�Υ��顼
		// ����
		echo createErrorJson('cgiError');
		exit;
	}
	
	// JSON���ɤ߹���
	// json�ǥ�����������
	$decoder = new Jsphon_Decoder();
	$json = $decoder->decode($result);
	$decoder = null;

	// �꥿���󥳡���
	$return_code = $json["return_code"];

	if ($return_code != "y1100000") {
		// rd_store_id.cgi�Υ꥿���󥳡��ɤ�����Ǥʤ�
		// ����
		echo createErrorJson('cgiError[' . $return_code . ']');
		exit;
	}
	// ������
	$store_count = $json["store_count"];
	// �����ꥹ��
	$store_list = $json["store_list"];
	
	// RD�ǡ����Υ������ƥ�������
	$kyoten_securitycode = null;
	for($i = 0; $i < count($store_list); $i++) {
		// "store_list"��ǻ��ꤷ������ID�Ȱ��פ����Τ�õ��
		if ($store_list[$i]["store_id"] == $kid) {
			for($j = 0; $j < count($store_list[$i]["group_list"]); $j++) {
				// group_list��ǻ��ꤷ�����롼��ID�Ȱ��פ����Τ�õ��
				if ($store_list[$i]["group_list"][$j]["group_id"] == $grpid) {
					for($k = 0; $k < count($store_list[$i]["group_list"][$j]["item_list"]); $k++) {
						// item_list��ǻ��ꤷ������ID�Ȱ��פ����Τ�õ��
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
	
	// POST���줿�������ƥ������ɤȼ��������������ƥ������ɤγ�ǧ
	if ($kyoten_securitycode != null && strcmp($scode, $kyoten_securitycode) === 0) {
		// �������ƥ������ɤ�����
		$out_json = createJson(true);
	}else {
		// �������ƥ������ɤ��԰���
		$out_json = createJson(false);
	}
	
	// ����
	echo $out_json;
	exit;
	
	// �쥹�ݥ�JSON�κ���
	// $matchflg:post���줿�������ƥ������ɤȡ�RD�ǡ����Υ������ƥ������ɤΰ��פ������ɤ����Υե饰
	//   true:���� false:�԰���
	function createJson($matchflg) {
		$message = $matchflg ? "match":"mismatch";
		$output = array('status'=>true, 'match'=>$matchflg, 'message'=>$message);
		$json_encoder = new Jsphon_Encoder();
		$value = $json_encoder->encode($output);
		$json_encoder = null;
		return $value;
	}
	
	// �쥹�ݥ�JSON�κ����ʥ��顼�ǡ�
	// $errMsg:�쥹�ݥ󥹤˴ޤ�륨�顼��å�����
	function createErrorJson($errMsg) {
		$output = array('status'=>false, 'match'=>false, 'message'=>$errMsg);
		$json_encoder = new Jsphon_Encoder();
		$value = $json_encoder->encode($output);
		$json_encoder = null;
		return $value;
	}
?>