<?php
/*========================================================*/
// �ե�����̾��get_icon_info.cgi
// ����̾���������������������
//
// ��������2007/06/11
// �����ԡ�Y.Matsukawa
//
// ���⡧�������������������
//
// ��������
//   ��2007/06/11 Y.Matsukawa	��������
//   ��2013/08/05 N.Wada        ¨��ȿ���оݴ���б�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	include( "d_serv_ora.inc" );
	include( "inc/oraDBAccess.inc" );
	include( "inc/sql_collection_get_icon_info.inc" );
	require_once('function.inc');		// add 2013/08/05 N.Wada

	$cgi_kind = "891";	//CGI����

	// ���ϥѥ�᡼������
	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid = urldecode( $_GET['cid'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid = urldecode( $_POST['cid'] );
	}

	// ���ϥѥ�᡼�������å�
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		exit;
	}

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print   $cgi_kind . "17900\t0\t0\n";
		exit;
	}

	// ¨����ե�å����о���������	add 2013/08/05 N.Wada
	$immref = isIMMREFAvailable( &$dba, $cid );

	// ��������������
	//$retcd = select_icon_info( &$dba, $cid, &$retdata, &$err_msg );	mod 2013/08/05 N.Wada
	$retcd = select_icon_info( &$dba, $cid, &$retdata, &$err_msg, $immref );
	if ( $retcd != 0 ) {
		$dba->close();
		if ( $retcd == 1 ) {
			print   $cgi_kind . "11009\t0\t0\n";    //������̥ǡ����ʤ�
		} else {    //9
			print   $cgi_kind . "17999\t0\t0\n";    //����¾DB���顼
		}
		exit;
	}
	
	$dba->close();

	$reccount = count($retdata);
	print $cgi_kind . "00000\t$reccount\t$reccount\n";
	foreach($retdata as $rowdata){
		$buf =  $rowdata["KBN"]."\t".$rowdata["ICON_ID"]."\t".$rowdata["ICON_W"]."\t".$rowdata["ICON_H"];
		$buf .= "\n";
		print $buf;
	}
?>
