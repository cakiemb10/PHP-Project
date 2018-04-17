<?php
/*========================================================*/
// �ե�����̾��nkyoten.cgi
// ����̾���Ǵ���������
//
// ��������2007/01/12
// �����ԡ�H.Ueno
//
// ���⡧�Ǵ������ꥹ�Ȥ��֤���
//
// ��������
// 2007/01/12 H.Ueno		��������
// 2007/02/13 H.Ueno		�����Ͻ����ɲ�
// 2007/02/14 H.Ueno		���Ϥ򥿥ֶ��ڤ���ѹ�
// 2007/02/22 H.Ueno		��������ͤ��ɲ�
// 2007/03/01 H.Ueno		���Ϥ�NEWɽ������/��λ�����ɲ�
// 2007/03/14 Y.Matsukawa	�����Ϲ��ܤΥ������
// 2007/03/23 Y.Matsukawa	������CID��$cid����$opt���ѹ�
// 2007/04/12 Y.Matsukawa	knsu,rad�ξ���ͥ����å����ɲ�
// 2007/06/27 Y.Matsukawa	rad�ξ���ͥ����å����ѻ�
// 2009/02/16 Y.Matsukawa	Ⱦ���Ѵ���ǽ���ɲá�z2h�ѥ�᡼����
// 2009/10/13 Y.Matsukawa	�Ǵ����������˾ܺٵ�����Ф��ʤ�
// 2009/11/24 Y.Matsukawa	�������ܳ�ĥ��50��200��
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/07/07 H.Osamoto		hour�ѥ�᡼���ɲ� ��1: ���ٷ��٤򽽿ʤǰ��� any�����ٷ��٤�ߥ��äǰ�����
// 2012/08/07 H.Osamoto		latlon��̤������Υ�������Υե����ޥå��̤�˽��Ϥ���ʤ��Զ�����
// 2012/10/15 H.Osamoto		�����ϰϤλ����µ�Υ�ǻ����ǽ���ѹ�
// 2012/11/13 Y.Matsukawa	JCN�����������
// 2013/08/02 Y.Matsukawa	Ǥ����������Ǥ���ϰϳ��ε��������
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2014/02/21 H.Osamoto		�ݥꥴ���⳰Ƚ������ɲ�
// 2014/05/13 Y.Matsukawa	���ʤǹʤ����
// 2014/10/02 H.Osamoto		�롼�ȵ�Υ���л��˽�ȯ�Ϥ���Ū�Ϥ������ؤ�
// 2015/02/10 F.Yokoi		�ꥢ�륿����ǡ����Ǥιʤ�����ɲ�
// 2015/03/23 F.Yokoi		�ʹ��߾�����˥ꥢ�륿����ǡ����򻲾Ȥ������Ƥ��ޤޤ�Ƥ��뤫��ǧ����check_jkn_rd()���ɲä���
// 2016/03/03 Y.Matsukawa	�����Ȼ���
// 2016/03/10 Y.Matsukawa	�߸����ե饰
// 2016/12/12 H.Yasunaga	��ޥȥ�å����б�	��ޥȥ�å�������API��Ȥäƥ�å����κ�ûǼ��������������ꤹ��
// 2017/04/12 H.Yasunaga	�����󥭥��ڡ���ڡ����б�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		// add 2012/11/13 Y.Matsukawa
	require_once('d_serv_emap.inc');	// add 2014/04/28 H.Osamoto
	include("ZdcCommonFunc.inc");	// ���̴ؿ�			add 2009/02/16 Y.Matsukawa
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/sql_collection_nkyoten.inc");
	include("chk.inc");         // �ǡ��������å���Ϣ
	include("log.inc");         // ������
	include("crypt.inc");       // �Ź沽
	include("jkn.inc");         // ��������Խ�
	// add 2011/07/05 Y.Nakajima
	include("../pc/inc/function.inc");         // ʸ�����󥳡��ɽ���
	require_once('function.inc');		// add 2012/11/13 Y.Matsukawa
	include("jkn_rd.inc");				// add 2015/02/10 F.Yokoi
	include("inc/rd_sql.inc");			// add 2015/02/10 F.Yokoi

	//�����ϳ���
	include("logs/inc/com_log_open.inc");

	$cgi_kind = "803";  //CGI����

	// add 2011/07/05 Y.Nakajima [
	//�����
	$key    = "";
	$cid    = "";
	$pos    = "";
	$cnt    = "";
	$lat    = "";
	$lon    = "";
	$latlon = "";
	$knsu   = "";
	$rad    = "";
	$jkn    = "";
	$opt    = "";
	$z2h    = "";
	$hour   = "";
	$absdist   = "";	// add 2012/10/15 H.Osamoto
	$exarea = "";		// add 2013/08/02 Y.Matsukawa
	$polycol   = "";	// add 2014/02/21 H.Osamoto
	// add 2011/07/05 Y.Nakajima ]
	$cust   = "";		// add 2012/11/13 Y.Matsukawa
	$sort   = "";		// add 2016/03/03 Y.Matsukawa
	$circle = "";		// add 2016/03/10 Y.Matsukawa

	// mod 2011/07/05 Y.Nakajima [
	if ( isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] == "GET" ) {
		foreach($_GET AS $key=>$value) {
			$key = str_replace("amp;", "", $key);
			$_GET[$key] = $value;
		}
	
		if (isset($_GET['key'])) {
			$key    = urldecode($_GET['key']);      //API����
		} 
		if (isset($_GET['cid'])) {
			$cid    = urldecode($_GET['cid']);
		} 
		if (isset($_GET['pos'])) {
			$pos    = urldecode($_GET['pos']);
		} 
		if (isset($_GET['cnt'])) {
			$cnt    = urldecode($_GET['cnt']);
		} 
		if (isset($_GET['lat'])) {
			$lat    = urldecode($_GET['lat']);
		} 
		if (isset($_GET['lon'])) {
			$lon    = urldecode($_GET['lon']);
		} 
		if (isset($_GET['latlon'])) {
			$latlon = urldecode($_GET['latlon']);   //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		} 
		if (isset($_GET['knsu'])) {
			$knsu   = urldecode($_GET['knsu']);
		}
		if (isset($_GET['rad'])) {
			$rad    = urldecode($_GET['rad']);
		}
		if (isset($_GET['jkn'])) {
			$jkn    = urldecode($_GET['jkn']);      //���(ex."COL_01:'1' AND COL_03:FW:'�����'")
		}
		if (isset($_GET['opt'])) {
			$opt    = urldecode($_GET['opt']);
		}
		if (isset($_GET['z2h'])) {
			$z2h    = $_GET['z2h'];		//���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		}
		if (isset($_GET['exkid'])) {
			$exkid  = $_GET['exkid'];	//��������		add 2009/10/13 Y.Matsukawa
		}
		if (isset($_GET['hour'])) {
			$hour   = $_GET['hour'];		//���ٷ��ٽ��ʼ����ե饰	add 2011/07/07 H.Osamoto
		}
		if (isset($_GET['absdist'])) {
			$absdist   = $_GET['absdist'];		//�µ�Υ����ե饰	add 2012/10/15 H.Osamoto
		}
		if (isset($_GET['exarea'])) $exarea = $_GET['exarea'];		// add 2013/08/02 Y.Matsukawa
		// �������ޥ�������		add 2012/11/13 Y.Matsukawa
		if (isset($_GET['cust'])) {
			$cust = $_GET['cust'];
		}
		if (isset($_GET['polycol'])) {
			$polycol   = $_GET['polycol'];		//�ݥꥴ�󥫥��	add 2014/02/21 H.Osamoto
		}
		// �����Ȼ���		add 2016/03/03 Y.Matsukawa
		if (isset($_GET['sort'])) {
			$sort = $_GET['sort'];
		}
		// �߸���		add 2016/03/10 Y.Matsukawa
		if (isset($_GET['circle'])) {
			$circle = $_GET['circle'];
		}

	} else if ( isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] == "POST" ) {
		if (isset($_POST['key'])) {
			$key    = urldecode($_POST['key']);     //API����
		}
		if (isset($_POST['cid'])) {
			$cid    = urldecode($_POST['cid']);     //as corp_id
		}
		if (isset($_POST['pos'])) {
			$pos    = urldecode($_POST['pos']);
		}
		if (isset($_POST['cnt'])) {
			$cnt    = urldecode($_POST['cnt']);
		}
		if (isset($_POST['lat'])) {
			$lat    = urldecode($_POST['lat']);
		}
		if (isset($_POST['lon'])) {
			$lon    = urldecode($_POST['lon']);
		}
		if (isset($_POST['latlon'])) {
			$latlon = urldecode($_POST['latlon']);  //���ٷ���(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		}
		if (isset($_POST['knsu'])) {
			$knsu   = urldecode($_POST['knsu']);
		}
		if (isset($_POST['rad'])) {
			$rad    = urldecode($_POST['rad']);
		}
		if (isset($_POST['jkn'])) {
			$jkn    = urldecode($_POST['jkn']);     //���
		}
		if (isset($_POST['opt'])) {
			$opt    = urldecode($_POST['opt']);
		}
		if (isset($_POST['z2h'])) {
			$z2h    = $_POST['z2h'];	//���Ѣ�Ⱦ���Ѵ����ץ����			add 2009/02/16 Y.Matsukawa
		}
		if (isset($_POST['exkid'])) {
			$exkid  = $_POST['exkid'];	//��������		add 2009/10/13 Y.Matsukawa
		}
		if (isset($_POST['hour'])) {
			$hour   = $_POST['hour'];		//���ٷ��ٽ��ʼ����ե饰	add 2011/07/07 H.Osamoto
		}
		if (isset($_POST['absdist'])) {
			$absdist   = $_POST['absdist'];		//�µ�Υ����ե饰	add 2012/10/15 H.Osamoto
		}
		if (isset($_POST['exarea'])) $exarea = $_POST['exarea'];		// add 2013/08/02 Y.Matsukawa
		// mod 2011/07/05 Y.Nakajima ]
		// �������ޥ�������		add 2012/11/13 Y.Matsukawa
		if (isset($_POST['cust'])) {
			$cust = $_POST['cust'];
		if (isset($_POST['polycol'])) {
			$polycol   = $_POST['polycol'];		//�ݥꥴ�󥫥��	add 2014/02/21 H.Osamoto
		}
		}
		// �����Ȼ���		add 2016/03/03 Y.Matsukawa
		if (isset($_POST['sort'])) {
			$sort = $_POST['sort'];
		}
		// �߸���		add 2016/03/10 Y.Matsukawa
		if (isset($_POST['circle'])) {
			$circle = $_POST['circle'];
		}
	}
	/*==============================================*/
	// API�����ǥ�����      �������Ϥǻ��Ѥ�������ʤΤǡ�ǧ�ڤϹԤäƤ��ޤ���
	/*==============================================*/
	$KEY = f_decrypt_api_key( $key );
	// �ǥ����ɸ��ʸ���󤬲���Ƥ�����ϥ��˽��Ϥ��ʤ�
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}

	// �������
	//edit_jkn($jkn, $edited_jkn, $arr_log_jkn);		mod 2009/11/24 Y.Matsukawa
	//edit_jkn($jkn, $edited_jkn, $arr_log_jkn, "", $rad);		mod 2014/05/13 Y.Matsukawa
	edit_jkn($jkn, $edited_jkn, $arr_log_jkn, "", $rad, $cid);
	$log_jkn = implode(" ", $arr_log_jkn);

	// LOG�����Ѥ˥ѥ�᡼���ͤ���ʢ����ٷ���Ÿ����ˤ⤦�����äƤޤ�����
	$parms = $lat;
	$parms .= " " . $lon;
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;
	//$parms .= " " . $rad;		del 2009/11/24 Y.Matsukawa

	//���ϥѥ�᡼�������å�
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	if ( $pos == "" ) {
		$pos = 1;
	} else {
		$pos = intval( $pos );
	}
	if ( $cnt == "" ) {
		$cnt = 100;
	} else {
		$cnt = intval( $cnt );
	}
	if ( $lat == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	if ( $lon == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	// add 2011/07/07 H.osamoto [
	if ($hour) {
		cnv_auto2dms($lat, $rtnlat);
		$lat = $rtnlat;
		cnv_auto2dms($lon, $rtnlon);
		$lon = $rtnlon;
	}
	// add 2011/07/07 H.osamoto ]
	$arr_latlon = array();
	if ( $latlon != "" ) {
		// mod 2011/07/07 H.Osamoto [
		//	if ( ! preg_match( '/[0-9]*[\,][0-9]*[\,][0-9]*[\,][0-9]*/', $latlon ) ) {
		//		print   $cgi_kind . "19100\t0\t0\n";
		//		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		//		exit;
		//	}
		if ($hour) {
			if ( ! preg_match( '/[0-9]*[\.][0-9]*[\,][0-9]*[\.][0-9]*[\,][0-9]*[\.][0-9]*[\,][0-9]*[\.][0-9]*/', $latlon ) ) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		} else {
			if ( ! preg_match( '/[0-9]*[\,][0-9]*[\,][0-9]*[\,][0-9]*/', $latlon ) ) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		}
		// mod 2011/07/07 H.Osamoto ]
		$arr_latlon = explode( ",", $latlon );
		if ( count($arr_latlon) != 4 ) {
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		// add 2011/07/07 H.osamoto [
		if ($hour) {
			for ( $ctr=0; $ctr<4; $ctr++ ) {
				cnv_auto2dms($arr_latlon[$ctr], $rtnpos);
				$arr_latlon[$ctr] = $rtnpos;
			}
		}
		// add 2011/07/07 H.osamoto ]
		foreach ( $arr_latlon as $rowdata ) {
			//if ( strlen( $rowdata ) != 9 ) {
			if ( strlen( $rowdata ) > 9 ) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		}
	}
	//--- �� for log �� -----
	$log_latlon = "";
	for ( $ctr=0; $ctr<4; $ctr++ ) {
		// mod 2012/08/07 H.Osamoto [
		//	// mod 2011/07/05 Y.Nakajima [
		//	if (isset($arr_latlon[$ctr])) {
		//		$log_latlon .= $arr_latlon[$ctr];
		//		if ( $ctr < 3 ) {
		//			$log_latlon .= " ";
		//		}
		//	}
		//	// mod 2011/07/05 Y.Nakajima ]
		if (isset($arr_latlon[$ctr])) {
			$log_latlon .= $arr_latlon[$ctr];
		}
		if ( $ctr < 3 ) {
			$log_latlon .= " ";
		}
		// mod 2012/08/07 H.Osamoto ]
	}
	//--- �� for log �� -----

	// LOG�����Ѥ˥ѥ�᡼���ͤ���
	$parms = $lat;
	$parms .= " " . $lon;
	$parms .= " " . $log_latlon;
	$parms .= " " . $log_jkn;
	//$parms .= " " . $rad;		del 2009/11/24 Y.Matsukawa

	if ( $knsu == "" ) {
		$knsu = 5;
	} else {
		$knsu = intval( $knsu );
	}
	if (!chk_knsu_max($knsu)) {
		// �����Ķ�ᥨ�顼
		print $cgi_kind . "19200\t0\t0\n";
		put_log($cgi_kind."19200", $KEY, $opt, $parms);
		exit;
	}
	if ( $rad == "" ) {
		$rad = 2000;
	}
	// 2007/06/27 del Y.Matsukawa
	//	if (!chk_rad_max($rad)) {
	//		// �����Ķ�ᥨ�顼
	//		print   $cgi_kind . "19200\t0\t0\n";
	//		put_log($cgi_kind."19200", $KEY, $opt, $parms);
	//		exit;
	//	}

	// Ǥ����������Ǥ���ϰϳ������		add 2013/08/02 Y.Matsukawa
	$exArea = false;
	if ($exarea) {
		list($exlat, $exlon, $exrad) = explode(',', $exarea);
		if ($exlat && $exlon && $exrad) {
			$exArea['lat'] = $exlat;
			$exArea['lon'] = $exlon;
			$exArea['rad'] = $exrad;
		}
	}

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print $cgi_kind . "17900\t0\t0\n";
		put_log($cgi_kind."17900", $KEY, $opt, $parms);
		exit;
	}

	// add 2013/08/05 N.Wada
	// ¨����ե�å����о���������
	$immref = isIMMREFAvailable( &$dba, $cid );

	//�����̾�ꥹ�ȼ���
	$arr_col_name = Array();
	$retcd = select_col_name( &$dba, $cid, &$arr_col_name, &$err_msg );
	//if ( $retcd != 0 ) {
	if ( ($retcd != 0) && ($retcd != 1) ) {	//$retcd == 9�ξ��
		$msg_err = "select_col_name error. errno=";
		$msg_err .= $o_rtncd;
		$dba->close();
		if ( $retcd == 1 ) {
			$out_retcd = $cgi_kind . "11009";    //������̥ǡ����ʤ�
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		}
		print $out_retcd . "\t0\t0\n";
		//������
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	//�Ǵ������ꥹ�ȼ����ʥ����nn�ˤĤ��Ƥϡ�������Τ�����ܤΤ߼�����
	$arr_near_kyoten = Array();
	if (!isset($exkid)) {
		$exkid ="";
	}

	// add 2015/02/10 F.Yokoi [
	// �ꥢ�륿������ܥǡ�������
	$arr_rd_item = Array();
	$arr_rd_item = selectRDItemDef(&$dba, $cid);
	// add 2015/02/10 F.Yokoi ]

	// add 2017/04/12 H.Yasunaga �����󥭥��ڡ��� [
	// �����ڡ����ѥơ��֥�򻲾Ȥ��������ڡ���ID�˰��פ���Ź��ID���������
	// ��������Ź��ID�Τ��оݤˤʤ�褦��sql�ξ��($edited_jkn)���Խ�����
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
	// add 2017/04/12 H.Yasunaga ]

	// mod 2015/02/10 F.Yokoi [
	// �ꥢ�륿����ξ��
	if (count($arr_rd_item) > 0 && check_jkn_rd($jkn)) { // mod 2015/03/23 F.Yokoi
	//if (count($arr_rd_item) > 0) {
		edit_jkn_rd($jkn, $edited_jkn, $arr_log_jkn, "", $rad, $cid);

		$retcd = select_near_kyoten_rd( &$dba, $cid, $lat, $lon, $arr_latlon, $rad,
			$arr_col_name, "",
			$pos, $cnt, $knsu, $exkid, &$hit_num,
			&$arr_near_kyoten, &$err_msg, $absdist, &$exArea, $immref, $polycol, $arr_rd_item, $edited_jkn);
	} else {
		$retcd = select_near_kyoten( &$dba, $cid, $lat, $lon, $arr_latlon, $rad,
			$arr_col_name, $edited_jkn,
			//$pos, $cnt, $knsu, &$hit_num,		mod 2009/10/13 Y.Matsukawa
			$pos, $cnt, $knsu, $exkid, &$hit_num,
			//	&$arr_near_kyoten, &$err_msg );	mod 2012/10/15 H.Osamoto
			//&$arr_near_kyoten, &$err_msg, $absdist );		mod 2013/08/02 Y.Matsukawa
			//&$arr_near_kyoten, &$err_msg, $absdist, &$exArea);	mod 2013/08/05 N.Wada
			//&$arr_near_kyoten, &$err_msg, $absdist, &$exArea, $immref);		mod 2014/02/21 H.osamoto
			&$arr_near_kyoten, &$err_msg, $absdist, &$exArea, $immref, $polycol
			, $sort		// add 2016/03/03 Y.Matsukawa
			, $circle	// add 2016/03/10 Y.Matsukawa
			);
	}
	// mod 2015/02/10 F.Yokoi ]

	if ( $retcd != 0 ) {
		$dba->close();
		if ( $retcd == 1 ) {
			$out_retcd = $cgi_kind . "11009";    //������̥ǡ����ʤ�
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //����¾DB���顼
		}
		print $out_retcd . "\t0\t0\n";
		//������
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	$dba->close();
	
	// JCN�����������		add 2012/11/13 Y.Matsukawa
	if ($cust == 'JCN') {
		JCNGetSpotStatus(&$arr_near_kyoten);
	}
	// add 2016/12/12 H.Yasunaga ��å����б� [
	// ��å����������
	// del 2016/12/26 H.Yasunaga ����� [
	// add 2016/12/15 H.Yasunaga ������ [
	//error_log(" nkyoten.cgi cust param:[" . $cust ."]\n");
	// add 2016/12/15 H.Yasunaga]
	// del 2016/12/26 H.Yasunaga]
	if ($cust == 'YTC_LOCKER') {
		$sdate = getCgiParameter('SDATE', '');	// �в�ͽ����
		$hzip = getCgiParameter('HZIP', '');	// ȯ��͹���ֹ�
		$bskbn = getCgiParameter('BSKBN', '');	// �ܥå�����������ʬ
		// del 2016/12/26 H.Yasunaga ����� [
		// add 2016/12/15 H.Yasunaga ������ [
		//error_log("nkyoten.cgi SDATE:[" . $sdate ."]\n");
		//error_log("nkyoten.cgi HZIP:[" . $hzip . "]\n");
		//error_log("nkyoten.cgi BSKBN:[" . $bskbn . "]\n");
		// add 2016/12/15 H.Yasunaga]
		// del 2016/12/26 H.Yasunaga]

		if (empty($sdate) != true && empty($hzip) != true && empty($bskbn) != true) {
			require_once("./inc/function_YAMATO01.inc");	// ����API��Ȥ��������ޥ���
			$pflg = "2";		// �ݥ���ȥե饰
			$datum = "TOKYO";	// ¬�Ϸ�
			$yamato01 = new YAMATO01($sdate, $hzip, $bskbn, $pflg, $datum);
			$arr_near_kyoten = $yamato01->getApiData($arr_near_kyoten);
		}
		$arrtmp = array_slice($arr_col_name, 0, count($arr_col_name) -2);
		$arr_lvl = array_slice($arr_col_name, count($arr_col_name) -2);
		$arrtmp[] = array("COL_NAME" => "YAMATO01_UKETORIKANODATE");
		$arr_col_name = array_merge($arrtmp, $arr_lvl);
	}
	// add 2016/12/12 H.Yasunaga ]
	
	// SMS��̳�ٱ�ƻ�Τ��Υ�б�		add 2014/04/28 H.Osamoto
	if ($cust == 'SMSG') {
		foreach($arr_near_kyoten as $key => $rowdata){
			$dist =sqrt($rowdata["KYORI"]);
			if ($dist <= 8000) {
				//	$route_dist = getRouteDistance($lat, $lon, $rowdata["LAT"], $rowdata["LON"]);	mod 2014/10/02 H.Osamoto
				$route_dist = getRouteDistance($rowdata["LAT"], $rowdata["LON"], $lat, $lon);
				$arr_near_kyoten[$key]["KYORI"] = $route_dist;
			} else {
				$arr_near_kyoten[$key]["KYORI"] = "@@ERR@@_".$dist;
			}
		}
		// ƻ�Τ��Υ��˥�����
		foreach ($arr_near_kyoten as $key => $value) {
			if (preg_match('/^@@ERR@@/', $value["KYORI"])) {
				$tmp = explode('_', $value["KYORI"]);
				$key_dist[] = "99999999".$tmp[1];
				$arr_near_kyoten[$key]["KYORI"] = "@@ERR@@";
			} else {
				$key_dist[] = intval($value["KYORI"]);
			}
		}
		array_multisort($key_dist, SORT_ASC, $arr_near_kyoten);
	}
	
	$rec_num = count( $arr_near_kyoten );
	if ( ($pos+$rec_num-1) < $hit_num ) {   //��³�ǡ���ͭ��
		$out_retcd = $cgi_kind . "00001";
	} else {                            //��³�ǡ���̵��
		$out_retcd = $cgi_kind . "00000";
	}
	print "$out_retcd\t$rec_num\t$hit_num\r\n";
	foreach( $arr_near_kyoten as $rowdata){
		// mod 2011/07/07 H.osamoto [
		//	$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
		//			$rowdata["LAT"]         . "\t" .
		//			$rowdata["LON"]         . "\t" .
		//			$rowdata["ICON_ID"]     . "\t" .
		//			sqrt($rowdata["KYORI"])	. "\t" .
		//			$rowdata["BFLG"];
		if ($hour) {
			// add 2014/04/28 H.Osamoto [
			if ($cust == 'SMSG') {
				$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
						cnv_dms2hour($rowdata["LAT"])         . "\t" .
						cnv_dms2hour($rowdata["LON"])         . "\t" .
						$rowdata["ICON_ID"]     . "\t" .
						$rowdata["KYORI"]	. "\t" .
						$rowdata["BFLG"];
			} else {
			// add 2014/04/28 H.Osamoto ]
				$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
						cnv_dms2hour($rowdata["LAT"])         . "\t" .
						cnv_dms2hour($rowdata["LON"])         . "\t" .
						$rowdata["ICON_ID"]     . "\t" .
						sqrt($rowdata["KYORI"])	. "\t" .
						$rowdata["BFLG"];
			// add 2014/04/28 H.Osamoto [
			}
			// add 2014/04/28 H.Osamoto ]
		} else {
			$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
					$rowdata["LAT"]         . "\t" .
					$rowdata["LON"]         . "\t" .
					$rowdata["ICON_ID"]     . "\t" .
					sqrt($rowdata["KYORI"])	. "\t" .
					$rowdata["BFLG"];
		}
		// mod 2011/07/07 H.osamoto ]
		if ( count($arr_col_name) > 0 ) {   //���ǤϤʤ����
			foreach( $arr_col_name as $rowdata2 ) {
				//$buf .= "\t" . $rowdata[$rowdata2["COL_NAME"]];		mod 2009/02/16 Y.Matsukawa
				// mod 2011/07/05 Y.Nakajima [
				//�ǡ�����̵�����Ǥ⡢���ڤ��tab��ɬ��
				$buf .= "\t";
				if (isset($rowdata2["COL_NAME"]) && isset($rowdata[$rowdata2["COL_NAME"]])) {
					//$buf .= ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
					$str = ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
					//�����Ѵ������ɲ�(kyotenid.cgi�ǡ���������pc/inc/function.inc::ZdcSearchCgiKyotenid()��Ʊ�ͤ�)
					$str = ZdcConvertEncoding($str);
					$buf .= $str;
				}
				// mod 2011/07/05 Y.Nakajima ]
			}
		}
		$buf .= "\n";
		print $buf;
	}

	//������
	put_log($out_retcd, $KEY, $opt, $parms);
?>
