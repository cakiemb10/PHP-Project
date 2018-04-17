<?php
/*========================================================*/
// �ե�����̾��kyotenlist.cgi
// ����̾�������ꥹ�ȸ���
//
// ��������2007/01/12
// �����ԡ�H.Ueno
//
// ���⡧�����ꥹ�Ȥ��֤���
//
// ��������
// 2007/01/12 H.Ueno		��������
// 2007/02/13 H.Ueno		�����Ͻ����ɲ�
// 2007/02/14 H.Ueno		���Ϥ򥿥ֶ��ڤ���ѹ�
// 2007/02/22 H.Ueno		��������ͤ��ɲ�
// 2007/03/01 H.Ueno		���Ϥ�NEWɽ������/��λ�����ɲ�
// 2007/03/14 Y.Matsukawa	�����Ϲ��ܤΥ������
// 2007/03/20 Y.Matsukawa	����������˽��ä������Ƚ�Ǽ�������褦����
// 2007/03/23 Y.Matsukawa	������CID��$cid����$opt���ѹ�
// 2007/08/15 Y.Matsukawa	URL�ѥ�᡼���򣲽Ť�urldecode���Ƥ���
// 2009/02/16 Y.Matsukawa	Ⱦ���Ѵ���ǽ���ɲá�z2h�ѥ�᡼����
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/08/25 H.osamoto		Ǥ�դΥ����Ȼ�����ɲá�sort�ѥ�᡼����
// 2012/06/18 Y.Matsukawa	����ID��ʣ���˻��긡��
// 2012/11/13 Y.Matsukawa	JCN�����������
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2014/05/13 Y.Matsukawa	���ʤǹʤ����
// 2017/4/21 H.Yasunaga		�����󥭥��ڡ����б�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		// add 2012/11/13 Y.Matsukawa
	include("ZdcCommonFunc.inc");	// ���̴ؿ�			add 2009/02/16 Y.Matsukawa
	include("d_serv_ora.inc");
	include("oraDBAccess.inc");
	include("sql_collection_kyotenlist.inc");
	include("chk.inc");         // �ǡ��������å���Ϣ
	include("log.inc");         // ������
	include("crypt.inc");       // �Ź沽
	include("jkn.inc");         // ��������Խ�
	// add 2011/07/05 Y.Nakajima
	include("../pc/inc/function.inc");         // ʸ�����󥳡��ɽ���
	require_once('function.inc');		// add 2012/11/13 Y.Matsukawa

	//�����ϳ���
	include("logs/inc/com_log_open.inc");

	// CGI����
	$cgi_kind = "802";
	
	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		// 2007/08/15 mod Y.Matsukawa
		//		$key    = urldecode($_GET['key']);      //API����
		//		$cid    = urldecode($_GET['cid']);      //���ID
		//		$pos    = urldecode($_GET['pos']);      //��������
		//		$cnt    = urldecode($_GET['cnt']);      //�������
		//		$jkn    = urldecode($_GET['jkn']);      //���(ex."COL_01:'1' AND COL_02:FW:'�����'")
		//		$latlon = urldecode($_GET['latlon']);   //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		//		$opt    = urldecode($_GET['opt']);
		// mod 2011/07/05 Y.Nakajima [
		/*
		$key    = $_GET['key'];      //API����
		$cid    = $_GET['cid'];      //���ID
		$pos    = $_GET['pos'];      //��������
		$cnt    = $_GET['cnt'];      //�������
		$jkn    = $_GET['jkn'];      //���(ex."COL_01:'1' AND COL_02:FW:'�����'")
		$latlon = $_GET['latlon'];   //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		$opt    = $_GET['opt'];
		$z2h    = $_GET['z2h'];		//���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		*/
		if (isset($_GET['key'])) {
			$key = $_GET['key'];    //API����
		} else {
			$key = "";
		}
		if (isset($_GET['cid'])) {
			$cid = $_GET['cid'];    //���ID
		} else {
			$cid = "";
		}
		if (isset($_GET['pos'])) {
			$pos = $_GET['pos'];    //��������
		} else {
			$pos = "";
		}
		if (isset($_GET['cnt'])) {
			$cnt = $_GET['cnt'];    //�������
		} else {
			$cnt = "";
		}
		if (isset($_GET['jkn'])) {
			$jkn = $_GET['jkn'];    //���(ex."COL_01:'1' AND COL_02:FW:'�����'")
		} else {
			$jkn = "";
		}
		if (isset($_GET['latlon'])) {
			$latlon = $_GET['latlon'];    //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		} else {
			$latlon = "";
		}
		if (isset($_GET['opt'])) {
			$opt = $_GET['opt'];
		} else {
			$opt = "";
		}
		if (isset($_GET['z2h'])) {
			$z2h = $_GET['z2h'];    //���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		} else {
			$z2h = "";
		}
		if (isset($_GET['sort'])) {
			$sort   = $_GET['sort'];	//�����Ȼ���						add 2011/08/25 H.osamoto
		} else {
			$sort   = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$kid = (isset($_GET['kid']) ? $_GET['kid'] : '');		// add 2012/06/18 Y.Matsukawa
		$cust = (isset($_GET['cust']) ? $_GET['cust'] : '');		// add 2012/11/13 Y.Matsukawa

	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		// 2007/08/15 mod Y.Matsukawa
		//		$key    = urldecode($_POST['key']);     //API����
		//		$cid    = urldecode($_POST['cid']);     //���ID
		//		$pos    = urldecode($_POST['pos']);     //��������
		//		$cnt    = urldecode($_POST['cnt']);     //�������
		//		$jkn    = urldecode($_POST['jkn']);     //���
		//		$latlon = urldecode($_POST['latlon']);  //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		//		$opt    = urldecode($_POST['opt']);
		// mod 2011/07/05 Y.Nakajima [
		/*
		$key    = $_POST['key'];     //API����
		$cid    = $_POST['cid'];     //���ID
		$pos    = $_POST['pos'];     //��������
		$cnt    = $_POST['cnt'];     //�������
		$jkn    = $_POST['jkn'];     //���
		$latlon = $_POST['latlon'];  //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		$opt    = $_POST['opt'];
		$z2h    = $_POST['z2h'];	//���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		*/
		if (isset($_POST['key'])) {
			$key = $_POST['key'];     //API����
		} else {
			$key = "";
		}
		if (isset($_POST['cid'])) {
			$cid = $_POST['cid'];     //���ID
		} else {
			$cid = "";
		}
		if (isset($_POST['pos'])) {
			$pos = $_POST['pos'];     //��������
		} else {
			$pos = "";
		}
		if (isset($_POST['cnt'])) {
			$cnt = $_POST['cnt'];     //�������
		} else {
			$cnt = "";
		}
		if (isset($_POST['jkn'])) {
			$jkn = $_POST['jkn'];     //���
		} else {
			$jkn = "";
		}
		if (isset($_POST['latlon'])) {
			$latlon = $_POST['latlon'];  //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		} else {
			$latlon = "";
		}
		if (isset($_POST['opt'])) {
			$opt = $_POST['opt'];
		} else {
			$opt = "";
		}
		if (isset($_POST['z2h'])) {
			$z2h = $_POST['z2h'];    //���Ѣ�Ⱦ���Ѵ����ץ����
		} else {
			$z2h = "";
		}
		if (isset($_POST['sort'])) {
			$sort   = $_POST['sort'];	//�����Ȼ���						add 2011/08/25 H.osamoto
		} else {
			$sort   = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$kid = (isset($_POST['kid']) ? $_POST['kid'] : '');		// add 2012/06/18 Y.Matsukawa
		$cust = (isset($_POST['cust']) ? $_POST['cust'] : '');		// add 2012/11/13 Y.Matsukawa
	}

	/*==============================================*/
	// API�����ǥ�����      �������Ϥǻ��Ѥ�������ʤΤǡ�ǧ�ڤϹԤäƤ��ޤ���
	/*==============================================*/
	$KEY = f_decrypt_api_key($key);
	// �ǥ����ɸ��ʸ���󤬲���Ƥ�����ϥ��˽��Ϥ��ʤ�
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}
	
	/*==============================================*/
	// �������
	/*==============================================*/
	//edit_jkn($jkn, $edited_jkn, $arr_log_jkn);		mod 2014/05/13 Y.Matsukawa
	edit_jkn($jkn, $edited_jkn, $arr_log_jkn, '', '', $cid);
	$log_jkn = implode(" ", $arr_log_jkn);

	/*==============================================*/
	// LOG�����Ѥ˥ѥ�᡼���ͤ���ʢ����ٷ���Ÿ����ˤ⤦�����äƤޤ�����
	/*==============================================*/
	$parms = "";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;

	/*==============================================*/
	// ���ϥѥ�᡼�������å�
	/*==============================================*/
	// ���ID
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	// ��������
	if ($pos == "") {
		$pos = 1;
	}
	// �������
	if ($cnt == "") {
		$cnt = 100;
	}
	// ���ٷ���
	$arr_latlon = array();
	if ($latlon != "") {
		if (!preg_match('/[0-9]*[\,][0-9]*[\,][0-9]*[\,][0-9]*/', $latlon)) {
			print $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		$arr_latlon = explode(",", $latlon);
		if (count($arr_latlon) != 4) {
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		foreach ($arr_latlon as $rowdata) {
			//if ( strlen( $rowdata ) != 9 ) {
			if (strlen( $rowdata ) > 9) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		}
	}
	$log_latlon = "";
	for ($ctr=0; $ctr<4; $ctr++) {
		// mod 2011/07/05 Y.Nakajima [
		if (isset($arr_latlon[$ctr])) {
			$log_latlon .= $arr_latlon[$ctr];
		}
		// mod 2011/07/05 Y.Nakajima ]
		if ($ctr < 3) {
			$log_latlon .= " ";
		}
	}
	// ����ID��ʣ������ġ�		add 2012/06/18 Y.Matsukawa
	$arr_kid = array();
	if ($kid != '') {
		$arr_kid = explode(',', $kid);
	}

	/*==============================================*/
	// LOG�����Ѥ˥ѥ�᡼���ͤ���
	/*==============================================*/
	$parms = "";
	$parms .= " ";
	$parms .= " " . $log_latlon;
	$parms .= " " . $log_jkn;

	/*==============================================*/
	// DB��³
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $cgi_kind . "17900\t0\t0\n";
		put_log($cgi_kind."17900", $KEY, $opt, $parms);
		exit;
	}

	// add 2013/08/05 N.Wada
	/*==============================================*/
	// ¨����ե�å����о���������
	/*==============================================*/
	$immref = isIMMREFAvailable( &$dba, $cid );

	/*==============================================*/
	// �����̾�ꥹ�ȼ���
	/*==============================================*/
	$arr_col_name = Array();
	$retcd = select_col_name(&$dba, $cid, &$arr_col_name, &$err_msg);
	//if ($retcd != 0) {
	if ( ($retcd != 0) && ($retcd != 1) ) {	//$retcd == 9�ξ��
		$dba->close();
		if ($retcd == 1) {
			$out_retcd = $cgi_kind . "11009";    //������̥ǡ����ʤ�
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		}
		print $out_retcd . "\t0\t0\n";
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}
	
	/*==============================================*/
	// ���������ꥫ������
	/*==============================================*/
	$arr_sort = Array();
	$retcd = select_sort_col_name(&$dba, $cid, &$arr_sort, &$err_msg);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$out_retcd = $cgi_kind . "11009";    //������̥ǡ����ʤ�
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		}
		print $out_retcd . "\t0\t0\n";
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}
	// add 2011/08/25 H.osamoto [
	// mod 2011/09/09 Y.Nakajima
	if ($sort != "") {
		$arr_sort[0]["COL_NAME"] = $sort;
	}
	// add 2011/08/25 H.osamoto ]
	
	// add 2017/4/21 H.Yasunaga �����󥭥��ڡ����б� [
	if ($cust == "lowsoncampaign") {
		// �ѥ�᡼�����ͼ��Ф�
		$campaignid = getCgiParameter("campaignid", '');
		if (strlen($campaignid) == 0) {
			// �ѥ�᡼�����顼
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		// �������ޥ�����inc�ե�������ɤ߹���
		require_once("./inc/function_LAWSONCAMPAIGN.inc");
		// �����ڡ���ơ��֥�˥����ڡ���ID����Ͽ����Ƥ��뤫��ǧ
		$is_exist_campaignid = exist_campaignid($dba, $campaignid);
		if ($is_exist_campaignid == false) {
			// �����ڡ���ID��¸�ߤ��ʤ����顼
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		// SQL��Ｐ�˸�����̤������ڡ����оݤ�Ź��ID�Τߤˤʤ뼰���ɲ�
		// kyoten_id in (select Ź��ID from �����ڡ���ơ��֥� where �����ڡ���ID = 'CGI�ѥ�᡼���Υ����ڡ���ID')
		$edited_jkn = edit_jkn_campaign($edited_jkn, $campaignid);
	
	}
	// add 2017/04/21 H.Yasunaga ]
	
	/*==============================================*/
	// �����ꥹ�ȼ����ʥ����nn�ˤĤ��Ƥϡ�������Τ�����ܤΤ߼�����
	/*==============================================*/
	$arr_kyoten_list = Array();
	$retcd = select_kyoten_list(&$dba, $cid, $arr_col_name, $edited_jkn, $arr_latlon, $arr_sort[0]["COL_NAME"],
								intval($pos), intval($cnt),
								$arr_kid,		// add 2012/06/18 Y.Matsukawa
								//&$hit_num, &$arr_kyoten_list, &$err_msg );
								&$hit_num, &$arr_kyoten_list, &$err_msg, $immref );	// mod 2013/08/05 N.Wada
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$out_retcd = $cgi_kind . "11009";    //������̥ǡ����ʤ�
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		}
		print $out_retcd . "\t0\t0\n";
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	/*==============================================*/
	// DB����
	/*==============================================*/
	$dba->close();

	// JCN�����������		add 2012/11/13 Y.Matsukawa
	if ($cust == 'JCN') {
		JCNGetSpotStatus(&$arr_kyoten_list);
	}

	/*==============================================*/
	// �����ꥹ�Ƚ���
	/*==============================================*/
	$rec_num = count($arr_kyoten_list);
	if (($pos+$rec_num-1) < $hit_num) {   //��³�ǡ���ͭ��
		$out_retcd = $cgi_kind . "00001";
	} else {                                //��³�ǡ���̵��
		$out_retcd = $cgi_kind . "00000";
	}
	print "$out_retcd\t$rec_num\t$hit_num\r\n";
	foreach($arr_kyoten_list as $rowdata){
		$buf =  $rowdata["KYOTEN_ID"] . "\t" .
				$rowdata["LAT"]       . "\t" .
				$rowdata["LON"]       . "\t" .
				$rowdata["ICON_ID"]   . "\t" .
				$rowdata["BFLG"];
		if ( count($arr_col_name) > 0 ) {   //���ǤϤʤ����
			foreach($arr_col_name as $rowdata2) {
				//$buf .= "\t" . $rowdata[$rowdata2["COL_NAME"]];		mod 2009/02/16 Y.Matsukawa
				// mod 2011/07/05 Y.Nakajima [
				//$buf .= "\t" . ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
				//�ǡ�����¸�ߤ��ʤ����ϡ�\t�Τߤ򵭽Ҥ���
				if (isset($rowdata2["COL_NAME"]) && isset($rowdata[$rowdata2["COL_NAME"]])) {
					$str = ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
					//�����Ѵ������ɲ�(kyotenid.cgi�ǡ���������pc/inc/function.inc::ZdcSearchCgiKyotenid()��Ʊ�ͤ�)
					$str = ZdcConvertEncoding($str);
					$buf .= "\t" . $str;
				} else {
					$buf .= "\t";
				}
				// mod 2011/07/05 Y.Nakajima ]
			}
		}
		$buf .= "\n";
		print $buf;
	}

	// ������
	put_log($out_retcd, $KEY, $opt, $parms);
?>
