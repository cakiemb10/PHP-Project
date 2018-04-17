<?php
/*========================================================*/
// �ե�����̾��kyotenid.cgi
// ����̾������ID����
//
// ��������2007/01/12
// �����ԡ�H.Ueno
//
// ���⡧��������ξ�����֤���
//
// ��������
// 2007/01/12 H.Ueno		��������
// 2007/02/13 H.Ueno		�������Ͻ����ɲ�
// 2007/02/14 H.Ueno		���Ϥ򥿥ֶ��ڤ���ѹ�
// 2007/02/22 H.Ueno		����������ͤ��ɲ�
// 2007/03/01 H.Ueno		���Ϥ�NEWɽ������/��λ�����ɲ�
// 2007/03/01 H.Ueno		���ϤΥ����פ�BO�ǥ����å�����Ƥʤ���硢
//							�ֵ���̾�����ꡢ���ѹ��ܡװʳ�����Ϥ����ͤ˲���
// 2007/03/14 Y.Matsukawa	�������Ϲ��ܤΥ������
// 2007/03/23 Y.Matsukawa	��������CID��$cid����$opt���ѹ�
// 2009/02/16 Y.Matsukawa	Ⱦ���Ѵ���ǽ���ɲá�z2h�ѥ�᡼����
// 2011/03/10 Y.Matsukawa	���ޡ��ȥե������б�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/01/27 K.Masuda		���Ϲ��ܤ˸���/NEWɽ���������ɲ�
// 2012/02/16 Y.Matsukawa	jkn�б�
// 2012/11/13 Y.Matsukawa	JCN�����������
// 2013/07/12 T.Sasaki		������ʣ���˲��������б� (mltimg [1]:ͭ����[̤����][0][1�ʳ�]:̵��)
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2014/05/21 Y.Matsukawa	���ʥޥ����б�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		// add 2012/11/13 Y.Matsukawa
	include("ZdcCommonFunc.inc");	// ���̴ؿ�			add 2009/02/16 Y.Matsukawa
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/sql_collection_kyotenid.inc");
	include("chk.inc");         // �ǡ��������å���Ϣ
	include("log.inc");         // ��������
	include("crypt.inc");       // �Ź沽
	include("jkn.inc");         // ��������Խ�
	require_once('function.inc');		// add 2012/11/13 Y.Matsukawa

	//�������ϳ���
	include("logs/inc/com_log_open.inc");

	// add 2011/07/05 Y.Nakajima [
	if (isset($_GET['kid'])) {
		$kid = $_GET['kid'];
	} else {
		$kid = "";
	}
	// add 2011/07/05 Y.Nakajima ]

	$cgi_kind = "801";	//CGI����
	$enc = "EUC";		//����ʸ��������

	//���ϥѥ�᡼������
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$key    = urldecode($_GET['key']);      //API����
		$cid    = urldecode($_GET['cid']);      //���ID
		$pos    = urldecode($_GET['kid']);      //����ID
		$type   = urldecode($_GET['type']);     //������(1:�����ܺ١�2:�������̡�3:�᤭�Ф����ϡ�4:���ӽ���)
		$opt    = urldecode($_GET['opt']);
		// mod 2011/07/05 Y.Nakajima [
		if (isset($_GET['z2h'])) {
			$z2h    = $_GET['z2h'];					//���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		} else {
			$z2h    = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$jkn = (isset($_GET['jkn']) ? $_GET['jkn'] : '');		// add 2012/02/16 Y.Matsukawa
		$cust = (isset($_GET['cust']) ? $_GET['cust'] : '');		// �������ޥ�������		add 2012/11/13 Y.Matsukawa
		$mltimg = (isset($_GET['mltimg']) ? $_GET['mltimg'] : '');	// ������ʣ���˲�������̵ͭ	add 2013/07/12 T.Sasaki
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$key    = urldecode($_POST['key']);     //API����
		$cid    = urldecode($_POST['cid']);
		$pos    = urldecode($_POST['kid']);
		$type   = urldecode($_POST['type']);
		$opt    = urldecode($_POST['opt']);
		// mod 2011/07/05 Y.Nakajima [
		if (isset($_GET['z2h'])) {
			$z2h    = $_POST['z2h'];				//���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		} else {
			$z2h    = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$jkn = (isset($_POST['jkn']) ? $_POST['jkn'] : '');		// add 2012/02/16 Y.Matsukawa
		$cust = (isset($_POST['cust']) ? $_POST['cust'] : '');		// �������ޥ�������		add 2012/11/13 Y.Matsukawa
		$mltimg = (isset($_POST['mltimg']) ? $_POST['mltimg'] : '');	// ������ʣ���˲�������̵ͭ	add 2013/07/12 T.Sasaki
	}

	/*==============================================*/
	// API�����ǥ�����      ���������Ϥǻ��Ѥ�������ʤΤǡ�ǧ�ڤϹԤäƤ��ޤ���
	/*==============================================*/
	$KEY = f_decrypt_api_key( $key );
	// �ǥ����ɸ��ʸ���󤬲���Ƥ�����ϥ����˽��Ϥ��ʤ�
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}

	// LOG�����Ѥ˥ѥ�᡼���ͤ���
	// mod 2011/07/05 Y.Nakajima [
	if (isset($kid)) {
		$parms = $kid;
	} else {
		$parms = "";
	}
	// mod 2011/07/05 Y.Nakajima ]
	$parms .= " " . $type;

	//���ϥѥ�᡼�������å�
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	// mod 2011/07/05 Y.Nakajima
	if (isset($kid) && $kid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	//if ( intval($type) < 1 || intval($type) > 4 ) {		mod 2011/03/10 Y.Matsukawa
	if ( intval($type) < 1 || intval($type) > 5 ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}

	// jkn		add 2012/02/16 Y.Matsukawa
	//edit_jkn($jkn, &$edited_jkn, &$arr_log_jkn);		mod 2014/05/21 Y.Matsukawa
	edit_jkn($jkn, &$edited_jkn, &$arr_log_jkn, 'A.', '', $cid);

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print   $cgi_kind . "17900\t0\t0\n";
		put_log($cgi_kind."17900", $KEY, $opt, $parms);
		exit;
	}
	//$sql = "alter session set nls_date_format='yyyymmddhh24miss'";
	//$dba->sqlExecute( $sql, $stmt);

	// ¨����ե�å����о���������	add 2013/08/05 N.Wada
	$immref = isIMMREFAvailable( &$dba, $cid );

	//�����̾�ꥹ�ȼ���
	$arr_col_name = Array();
	$retcd = select_col_name( &$dba, $cid, $type, &$arr_col_name, &$err_msg );
	if ( ($retcd != 0) && ($retcd != 1) ) {	//$retcd == 9�ξ��
		$dba->close();
		$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		print $out_retcd . "\t0\t0\n";
		//��������
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}
	
	//���������������ʥ����nn�ˤĤ��Ƥϡ�������Τ�����ܤΤ߼�����
	$retcd = select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, 
		//&$kyoten_data, &$err_msg );		mod 2012/02/16 Y.Matsukawa
		//&$kyoten_data, &$err_msg, $edited_jkn );	mod 2013/08/05 N.Wada
		&$kyoten_data, &$err_msg, $edited_jkn, $immref );
	if ( $retcd != 0 ) {
		$dba->close();
		if ( $retcd == 1 ) {
			$out_retcd = $cgi_kind . "11009";    //������̥ǡ����ʤ�
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		}
		print $out_retcd . "\t0\t0\n";
		//��������
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	// ����������ʣ���˥ǡ�������
	// GET/POST�ѥ�᡼��[mltimg]��[1]�����ꤵ��Ƥ���Ȥ��Τ߼���
	if ( $mltimg == '1' ) {
		//$retcd = select_kyoten_img_tbl( &$dba, $cid, $kid, &$arr_multi_img, &$err_msg );	mod 2013/08/05 N.Wada
		$retcd = select_kyoten_img_tbl( &$dba, $cid, $kid, &$arr_multi_img, &$err_msg, $immref );
		if ( $retcd != 0 && $retcd != 1 ) {
			$dba->close();
			$out_retcd = $cgi_kind . "17999";	 	//����¾DB���顼
			print $out_retcd . "\t0\t0\n";
			//��������
			put_log($out_retcd, $KEY, $opt, $parms);
			exit;
		}
	}

	$dba->close();

	// add 2012/11/13 Y.Matsukawa [
	// JCN�����������
	$kyoten_data['KYOTEN_ID'] = $kid;
	$arr_kyoten = array();
	if ($cust == 'JCN') {
		$arr_kyoten[0] = $kyoten_data;
		JCNGetSpotStatus(&$arr_kyoten);
		$kyoten_data = $arr_kyoten[0];
	}
	// add 2012/11/13 Y.Matsukawa ]

	$out_retcd = $cgi_kind . "00000";
	print   $out_retcd . "\t1\t1\n";

	$buf =  $kyoten_data["LAT"] . "\t" .
			$kyoten_data["LON"] . "\t" .
			$kyoten_data["ICON_ID"] . "\t" .
			$kyoten_data["K_GIF_NUM"] . "\t" .		// ñ�����¸��̵ͭ
			$kyoten_data["BFLG"];					// NEW��Ф��Ф��ʤ�
	if ( count($arr_col_name) > 0 ) {	//���ǤϤʤ����
		foreach( $arr_col_name as $rowdata2 ) {
			//$buf .= "\t" . $kyoten_data[$rowdata2["COL_NAME"]];		mod 2009/02/16 Y.Matsukawa
			// mod 2011/07/05 Y.Nakajima [
			//$buf .= "\t" . ZdcConvZ2H($kyoten_data[$rowdata2["COL_NAME"]], $z2h);
			//�ǡ�����¸�ߤ��ʤ����ϡ�\t�Τߤ򵭽Ҥ���
			if (isset($kyoten_data[$rowdata2["COL_NAME"]])) {
				$str = ZdcConvZ2H($kyoten_data[$rowdata2["COL_NAME"]], $z2h);
				$buf .= "\t" . $str;
			} else {
				$buf .= "\t";
			}
			// mod 2011/07/05 Y.Nakajima ]
		}
	}
	// add 2012/01/27 K.Masuda [
	// add 2012/11/13 Y.Matsukawa [
	// JCN�����������
	if ($cust == 'JCN') {
		$buf .= "\t";
		$buf .= $kyoten_data["JCN_SPOT_STATUS"]."\t";
		$buf .= $kyoten_data["JCN_SPOT_AVL_COUNT"];
	}
	// add 2012/11/13 Y.Matsukawa ]
	
	// ����������ʣ���˥ǡ���
	if ( $mltimg == '1' ) {
		if ( is_array($arr_multi_img) && count( $arr_multi_img ) > 0 ) {
			$parmMltImg = null;
			foreach ( $arr_multi_img as $multi_img ) {
				if ( isset( $parmMltImg ) ) {
					$parmMltImg .=	",";
				}
				$parmMltImg .= $multi_img["IMG_NO"];
			}
			$buf .= "\t";
			$buf .= $parmMltImg;
		} else {
			// ��Ĥ�������ʤ�
			$buf .= "\t";
		}
	}
	
	// �����աۤ���4���ܤϺǸ���ɲä����ΤȤ��롪�ʽ��ѹ��Բġ�
	$buf .= "\t";
	$buf .= $kyoten_data["PUB_S_DATE"] . "\t";
	$buf .= $kyoten_data["PUB_E_DATE"] . "\t";
	$buf .= $kyoten_data["DISP_NEW_S_DATE"] . "\t";
	$buf .= $kyoten_data["DISP_NEW_E_DATE"];
	// add 2012/01/27 K.Masuda ]
	$buf .= "\n";
	if ( $enc != "EUC" ) {
		$buf = mb_convert_encoding($buf, $enc);
	}
	print $buf;

	//��������
	put_log($out_retcd, $KEY, $opt, $parms);

?>