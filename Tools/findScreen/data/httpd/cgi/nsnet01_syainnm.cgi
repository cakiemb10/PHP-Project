<?php
// ---------------------------------------------------------
// ������������ �Ұ�̾����CGI��åѡ�
// 
// �ե�����̾��nsnet01_syainnm.cgi
// ����̾���Ұ�̾����
//
// ��������2015/05/08
// �����ԡ�N.Wada
//
// ���⡧�����������ȸ���WEB API���ͳ���ƼҰ��ֹ椫��Ұ�̾�����
//
// ���ϥѥ�᡼����
// empno	GET		�Ұ��ֹ�ʥ���޶��ڤ��ʣ���ġ�
// ���
// empno=100001,100010,100015
//
// ���ϥե����ޥåȡ�
// 1���ܤϷ����2���ܰʹߤϼҰ��ֹ�\t�Ұ�̾
// ���
// 2
// 000001	�Ұ�̾000001
// 000002	�Ұ�̾000002
//
// ��������
// 2015/05/08 N.Wada		��������
// 2015/05/15 N.Wada		�Ϥ����⤫ʸ���������Ƥ�������ʸ�������ɤ�'CP51932'���ѹ�
// ---------------------------------------------------------
header("Content-Type: text/html; charset=EUC-JP");

require_once('/home/emap/src/Jsphon/Decoder.php');
require_once('d_serv_cgi.inc');
require_once('d_serv_emap.inc');
require_once('auth.inc');				// �ʰ�ǧ��
include("ZdcCommonFunc.inc");

// �����������ȸ���WEB API
$url = 'http://www.nihonsetsubi.co.jp/webapi/karte/json.php';

// ����IP
$D_IP_LIST = array();
$D_IP_LIST[] = '127.0.0.1';
$D_IP_LIST[] = '10.47.50.*';
$D_IP_LIST[] = '172.16.162.*';
$D_IP_LIST[] = '153.122.23.244';
$D_IP_LIST = implode(':', $D_IP_LIST);

// �ʰ�ǧ�ڡ�IP�����å���
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	header('HTTP/1.1 403 Forbidden');
	exit;
}

// �Ұ��ֹ��GET�������
$empnos = explode(",", htmlspecialchars($_GET['empno']));

// CGI���Ϥ��ѥ�᡼��������
$cnt = 0;
foreach ( $empnos as $empno ) {
	if ( ! ctype_digit($empno) ) continue;
	$url .= ($cnt ? '&' : '?') . 'id[]=' . $empno;
	$cnt++;
}
// �ץ�����ɬ���̤�
$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];

$buf = "";
if ($cnt) {
	$dat = ZdcHttpSimpleRead($url, $host);
	if ($dat != '') {
		// JSON�ǥ�����
		$json = new Jsphon_Decoder();
		$arr_data = $json->decode($dat[0]);
		if ($arr_data && is_array($arr_data)) {
			// EUC���Ѵ�
			//mb_convert_variables('EUC-JP', 'UTF-8', $arr_data);	mod 2015/05/15 N.Wada
			// CP51932���Ѵ�
			mb_convert_variables('CP51932', 'UTF-8', $arr_data);
			$buf = count($arr_data) . "\n";
			foreach ( $arr_data as $work ) {
				$buf .= $work['id'] . "\t" . $work['name'] . "\n";
			}
		}
	}
}
if ($buf == "") {
	$buf = "0\n";
}

print($buf);
?>
