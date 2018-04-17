<?php
/*========================================================*/
// �ե�����̾��pc_tpl_css_setting.cgi
// ����̾��PC�ƥ�ץ졼�ȥǥ������������
//
// ��������2007/11/14
// �����ԡ�Y.Matsukawa
//
// ���⡧PC�ƥ�ץ졼�ȥǥ����������serialize����PHP�ѿ��ˤ����
//
// ��������
// 2007/11/14 Y.Matsukawa	��������
// 2012/10/16 Y.Matsukawa	error_reporting()���
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );

	//CGI����
	$cgi_kind = "811";

	// ���顼����OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	// �ѥ�᡼������
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$cid = $_GET['cid'];
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$cid = $_POST['cid'];
	}
	
	//���ϥѥ�᡼�������å�
	if ($cid == "") {
		print $cgi_kind . "19100" . "\n";
		exit;
	}

	// DB��³
	$conn = OCILogon( ORA_USER , ORA_PASS , ORA_TNS );
	$err = OCIError();
	if ( $err ) {
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		print $cgi_kind . "17900" . "\n";
		exit;
	}

	// SQLʸ
	$sql = 'select SETTINGS'
		. ' from EMAP_PC_TPL_DESIGN'
		. ' WHERE CORP_ID = \''  . $cid . '\'';

	$stmt = OCIParse($conn, $sql);
	OCIExecute($stmt, OCI_DEFAULT);
	$err = OCIError($stmt);
	if ( $err ) {
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		print $cgi_kind . "17999" . "\n";
		exit;
	}

	OCIFetchInto($stmt, $arr, OCI_ASSOC);
	if ( ! $arr ) {
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		print $cgi_kind . "11009" . "\n";
		exit;
	}

	print $cgi_kind . "00000" . "\n";
	$data = $arr['SETTINGS'];
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);

?>
