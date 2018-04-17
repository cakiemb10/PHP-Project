<?php
/*========================================================*/
// �ե�����̾��icon_select.cgi
// ����̾����������ǡ�������
//
// ��������2007/02/01
// �����ԡ�K.Masuda
//
// ���⡧���ID����������ID���������
//       ��������Х��ʥ�ǡ������֤�
//
// �ѥ�᡼����(IN)cid      -  ���ID
//             (IN)icon_id  -  ��������ID
//
// ��������
// 2007/02/01 K.Masuda		��������
// 2007/03/30 Y.Matsukawa	�꥿���󥳡��ɽ��ϻ����ղä���Ƥ������������
// 2007/06/15 Y.Matsukawa	��������ID�˳�ĥ�Ҥ��դ��Ƥ��������ʥ��˥᡼�����GIF�б��ǡ�����Ū�ˡ�.gif�פ��դ���ɬ�פ����뤿���
// 2007/07/11 Y.Matsukawa	���饯�륨�顼ȯ������connection�����Ǥ��Ƥ��ʤ��ä�
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2014/02/04 Y.Matsukawa	SQL���󥸥���������к�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );

	//CGI����
	$cgi_kind = "805";

	// ���顼����OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid          =  urldecode( $_GET['cid'] );
		$icon_id      =  urldecode( $_GET['icon_id'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid          =  urldecode( $_POST['cid'] );
		$icon_id      =  urldecode( $_POST['icon_id'] );
	}
	
	// ��ĥ�Ҥ����		
	$icon_id_e = explode(".", $icon_id);
	$icon_id = $icon_id_e[0];

	//���ϥѥ�᡼�������å�
	if ( $cid == "" || $icon_id == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	
	// SQL���󥸥���������к�		add 2014/02/04 Y.Matsukawa
	$cid = mb_ereg_replace("'", "''", $cid);
	$icon_id = mb_ereg_replace("'", "''", $icon_id);

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
		$from = " FROM IM_ICON_TBL ";
	} else {
		$from = " FROM ICON_TBL ";
	}
	// add 2013/08/05 N.Wada ]

	$sql  = 'SELECT ICON_DATA '
		  //. ' FROM ICON_TBL '	mod 2013/08/05 N.Wada
		  .  $from
		  . ' WHERE corp_id = \''  . $cid      . '\'' 
		  . ' AND   icon_id = \''  . $icon_id  . '\'';

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

	$data = $arr['ICON_DATA'];

	/**
	 * �����������Τν���
	 */
	header( "Content-type: image/gif" );
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);

?>
