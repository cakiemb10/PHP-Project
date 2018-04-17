<?php

/*========================================================*/
// �ե�����̾��gif_select.cgi
// ����̾�����������ǡ�������
//
// ��������2007/02/01
// �����ԡ�K.Masuda
//
// ���⡧���ID������ID���������
//       ���������Х��ʥ�ǡ������֤�
//
// �ѥ�᡼����(IN)cid  -  ���ID
//             (IN)kid  -  ����ID
// ��������
// 2007/02/01 K.Masuda		��������
// 2007/02/28 K.Masuda		�ե����륿����Ƚ���ɲ�
// 2007/03/30 Y.Matsukawa	�꥿���󥳡��ɽ��ϻ����ղä���Ƥ������������
// 2007/07/11 Y.Matsukawa	���饯�륨�顼ȯ������connection�����Ǥ��Ƥ��ʤ��ä�
// 2012/10/16 Y.Matsukawa	error_reporting()���
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	
	include( "d_serv_ora.inc" );

	//CGI����
	$cgi_kind = "806";

	// ���顼����OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid    =  urldecode( $_GET['cid'] );
		$kid    =  urldecode( $_GET['kid'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid    =  urldecode( $_POST['cid'] );
		$kid    =  urldecode( $_POST['kid'] );
	}

	//���ϥѥ�᡼�������å�
	if ( $cid == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	if ( $kid == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}

	// DB��³
	$conn = OCILogon( ORA_USER , ORA_PASS , ORA_TNS );
	$err = OCIError();
	if ( $err ) {
		// 2007/07/11 add Y.Matsukawa ��
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		// 2007/07/11 add Y.Matsukawa ��
		print $cgi_kind . "17900" . "\n";
		exit;
	}

	// add 2013/08/05 N.Wada
	/**
	 * ¨����ե�å����о���������
	 */
	$immref = false;
	if (strtolower(ORA_TNS) == 'pub') {
		$sql = "select VALUE from EMAP_PARM_TBL";
		$sql .= " where CORP_ID = '".$cid."'";
		$sql .= " and KBN = 'IMMREF'";

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

		OCIFetchInto($stmt, $arr_param, OCI_ASSOC);
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if ($arr_param) {
			$immref = ($arr_param['VALUE']=='1'?true:false);
		}
	}

	/**
	 * SQL�κ���
	 */
	// add 2013/08/05 N.Wada [
	if ( $immref ) {
		$from = " FROM IM_KYOTEN_GIF_TBL ";
	} else {
		$from = " FROM KYOTEN_GIF_TBL ";
	}
	// add 2013/08/05 N.Wada ]

	$sql  = 'SELECT GIF_DATA '
		  //. ' FROM KYOTEN_GIF_TBL '	mod 2013/08/05 N.Wada
		  .  $from
		  . ' WHERE corp_id = \''  . $cid . '\'' 
		  . ' AND kyoten_id = \''  . $kid . '\'';

	$stmt = OCIParse($conn, $sql);
	OCIExecute($stmt, OCI_DEFAULT);
	$err = OCIError($stmt);
	if ( $err ) {
		// 2007/07/11 add Y.Matsukawa ��
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		// 2007/07/11 add Y.Matsukawa ��
		print $cgi_kind . "17999" . "\n";
		exit;
	}

	OCIFetchInto($stmt, $arr, OCI_ASSOC);
	if ( ! $arr ) {
		// 2007/07/11 add Y.Matsukawa ��
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		// 2007/07/11 add Y.Matsukawa ��
		print $cgi_kind . "11009" . "\n";
		exit;
	}

	$data = $arr['GIF_DATA'];

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
