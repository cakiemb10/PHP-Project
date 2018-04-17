<?PHP
// ------------------------------------------------------------
// 2011/01/11 Y.Matsukawa	��ե��顼�˴ޤޤ��Ⱦ�ѥ��ڡ�������REFERER��255�Х��Ȥ˴ݤ��
// 2011/05/06 Y.Matsukawa	���Զ�罤���۲��ԥ����ɺ���
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// ------------------------------------------------------------
/**
* �ؿ�̾ ��  put_log
* ��  �� ��  ��������
* ��  �� ��  $retcd     - �꥿���󥳡��ɡ����80419200
*            $key       - API�����ʥǥ����ɺѡ�
             $emap_cid  - e-map��ȥ�����
             $parms     - �ѥ�᡼��ʸ�����Ⱦ�ѥ��ڡ������ڤ��
* ����� ��  �ʤ�
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
		//?��¸�ߤ��ʤ��Ȥ�
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
	
	// ��������
	$log_api->info($CID.' '.$emap_cid.' '.$REFERER.' '.$retcd.' '.$SERVICE_CODE.' '.$parms);

	// �������Ͻ�λ
	include("logs/inc/com_log_close.inc");
}

/**
* �ؿ�̾ ��  format_log_string
* ��  �� ��  ʸ�������������Ѥ�����
* ��  �� ��  $str - ʸ����
* ����� ��  ������ʸ����
**/
function format_log_string($str) {
	// ����ζ�������
	$str = trim($str);
	// ���ԥ����ɤ�"_"���ִ�
	$str = str_replace("\r\n", "_", $str);
	$str = str_replace("\r",   "_", $str);
	$str = str_replace("\n",   "_", $str);
	// Ⱦ�ѥ��ڡ��������
	$str = str_replace(" ",    "_", $str);
	
	return $str;
}

/**
* �ؿ�̾ ��  put_query_log
* ��  �� ��  ��������
* ��  �� ��  $query     - �¹�query
* ����� ��  �ʤ�

// ��������
// 2011/07/05 Y.Nakajima	��������
**/
function put_query_log($query) {
	global $log_api;
	if ($query != "") {
		$parms = mb_ereg_replace("\r\n", "", $query);
		$parms = mb_ereg_replace("\r",   "", $query);
		$parms = mb_ereg_replace("\n",   "", $query);
	
		// ��������
		$log_api->info($query.' ');

	}
}


?>