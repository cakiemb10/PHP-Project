<?php
/*========================================================*/
// �ե�����̾��cp_img_inf.cgi
// ����̾����Ȳ���������������
//
// ��������2012/02/13
// �����ԡ�Y.Matsukawa
//
// ���⡧���ID�����ζ�ʬ��PC�����ӡ����ޥۡˤ˳����������������֤�
//
// �ѥ�᡼����(IN)cid  -  ���ID
//             (IN)kbn  -  ���ζ�ʬ��P��PC��M�����ӡ�S�����ޥۡ�
// ��������
// 2012/02/13 Y.Matsukawa	��������
// 2012/10/16 Y.Matsukawa	error_reporting()���
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );
	include( "inc/oraDBAccess.inc" );

	$cgi_kind = "810";	//CGI����

	// ���顼����OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	// ���ϥѥ�᡼������
	$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
	if(isset($_VARS['cid']))		$cid = $_VARS['cid'];
	if(isset($_VARS['kbn']))		$kbn = $_VARS['kbn'];

	// ���ϥѥ�᡼�������å�
	if ( $cid == "" ) {
		print $cgi_kind . "19100\t0\t0\n";
		exit;
	}

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print $cgi_kind . "17900\t0\t0\n";
		exit;
	}

	// ��������������
	$sql  = "select IMG_NO,IMG_NAME,IMG_W,IMG_H,URL"
			. " from CORP_IMG_TBL"
			. " where CORP_ID = '".$cid."'"
			. " and MEDIA_KBN = '". $kbn."'"
			. " and nvl(PUB_E_DATE, SYSDATE) >= SYSDATE "
			. " order by IMG_NO"
	;
	$stmt   = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		print $cgi_kind . "17999\t0\t0\n";		//����¾DB���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$reccount = count($retdata);
	if ($reccount <= 0) {
		$dba->free($stmt);
		print $cgi_kind . "11009\t0\t0\n";		//������̥ǡ����ʤ�
		exit;
	}
	$dba->free($stmt);
	$dba->close();

	print $cgi_kind . "00000\t$reccount\t$reccount\n";

	foreach($retdata as $rowdata){
		$buf = '';
		$buf .= $rowdata["IMG_NO"];
		$buf .= "\t";
		$buf .= $rowdata["IMG_NAME"];
		$buf .= "\t";
		$buf .= $rowdata["IMG_W"];
		$buf .= "\t";
		$buf .= $rowdata["IMG_H"];
		$buf .= "\t";
		$buf .= $rowdata["URL"];
		$buf .= "\n";
		print $buf;
	}
?>
