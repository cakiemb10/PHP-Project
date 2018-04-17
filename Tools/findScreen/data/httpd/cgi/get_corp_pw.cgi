<?php
/*========================================================*/
// �ե�����̾��get_corp_pw.cgi
// ����̾����ȥѥ���ɼ���
//
// ��������2008/07/01
// �����ԡ�Y.Matsukawa
//
// ���⡧EMAP(�������⥵���ӥ�)�δ�ȥѥ���ɤ��������
//
// ��������
//   ��2008/07/01 Y.Matsukawa		��������
/*========================================================*/
	header("Content-Type: text/plain; charset=euc-jp");
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/sql_collection_get_corp_pw.inc");
	include("inc/crypt.inc");

	$cgi_kind = "892";

	//���ϥѥ�᡼������
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$cid = urldecode( $_GET['cid'] );
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$cid = urldecode( $_POST['cid'] );
	}

	//���ϥѥ�᡼�������å�
	if ($cid == "") {
		print $cgi_kind . "19100\n";
		exit;
	}

	// DB��³
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $cgi_kind . "17900\n";
		exit;
	}

	//�����̾�ꥹ�ȼ���
	$arr_col = Array();
	$retcd = select_corp_pw(&$dba, $cid, &$arr_col, &$err_msg);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			print $cgi_kind . "11009\n";    //������̥ǡ����ʤ�
		} else {
			print $cgi_kind . "17999\n";    //����¾DB���顼
		}
		exit;
	}
	
	// DB����
	$dba->close();

	// �ѥ���ɰŹ沽��10�Х��Ȱʾ�ʤ�������˰Ź桿����Ǥ��ʤ��Τǡ����ߡ�ʸ������ղá�
	$encpw = f_encrypt_api_key("PASSWORD=".$arr_col["PASSWD"]);

	// ����
	print $cgi_kind . "00000\n";
	print $encpw."\n";
?>
