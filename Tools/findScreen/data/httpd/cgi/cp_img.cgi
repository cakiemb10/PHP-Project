<?php
/*========================================================*/
// �ե�����̾��cp_img.cgi
// ����̾����Ȳ����ǡ�������
//
// ��������2012/02/13
// �����ԡ�Y.Matsukawa
//
// ���⡧���ID�����ζ�ʬ��PC�����ӡ����ޥۡˡ�����No�˳�����������Х��ʥ�ǡ������֤�
//
// �ѥ�᡼����(IN)cid  -  ���ID
//             (IN)kbn  -  ���ζ�ʬ��P��PC��M�����ӡ�S�����ޥۡ�
//             (IN)n    -  ����No.
// ��������
// 2012/02/13 Y.Matsukawa	��������
// 2012/10/16 Y.Matsukawa	error_reporting()���
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	
	include( "d_serv_ora.inc" );

	//CGI����
	$cgi_kind = "809";

	// ���顼����OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
	if(isset($_VARS['cid']))		$cid = $_VARS['cid'];
	if(isset($_VARS['kbn']))		$kbn = $_VARS['kbn'];
	if(isset($_VARS['n']))			$n   = $_VARS['n'];

	//���ϥѥ�᡼�������å�
	if ( $cid == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	if ( $kbn == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	if ( $n == "" ) {
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

	/**
	 * SQL�κ���
	 */
	$sql  = "select IMG_DATA"
			. " from CORP_IMG_TBL"
			. " where CORP_ID = '".$cid."'"
			. " and MEDIA_KBN = '". $kbn."'"
			. " and IMG_NO = ".$n
	;

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

	$data = $arr['IMG_DATA'];

	/**
	 * �ե����륿���פ�Ƚ��
	 */
	$file_typ_str = substr( $data->load() , 0 , 15 );
	if ( strpos( $file_typ_str , "PNG" ) ) {
		header( "Content-type: image/png" );
	} else if ( strpos( $file_typ_str , "GIF" ) ) {
		header( "Content-type: image/gif" );
	} else {
		header( "Content-type: image/jpeg" );
	}

	/**
	 * �������Τν���
	 */
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);

?>
