<?php
/*========================================================*/
// �ե�����̾��kyotenarea.cgi
// ����̾���������ꥢ����
//
// ��������2006/12/05
// �����ԡ�T.Tamagawa
//
// ���⡧���ϥѥ�᡼��������塢�ѥ�᡼��������
//       �����å��򤷤ơ��ǡ��������Ѥ�SQL�������塢
//       DB���ǡ������������CSV�ǡ����Ȥ���
//       �إå����󤪤�ӥꥹ�Ⱦ�����֤���
//
// ��������
// 2006/12/05 T.Tamagawa	��������
// 2006/12/22 T.Tamagawa	���ϥǡ��������ǡ����ɲ�
// 2007/01/12 H.Ueno		�������˸�����λ�����ɲ�
//							���顼�������ѹ�
// 2007/01/17 Y.Matsukawa	���饯�륢��������ˡ���ѹ���ora.inc -> oraDBAccess.inc)
// 2007/02/13 H.Ueno		�����Ͻ����ɲ�
// 2007/02/22 H.Ueno		��������ͤ��ɲ�
// 2007/03/14 Y.Matsukawa	�����Ϲ��ܤΥ������
// 2007/03/23 Y.Matsukawa	������CID��$cid����$opt���ѹ�
// 2007/03/30 Y.Matsukawa	enc�ѥ�᡼���ѻ�
// 2007/07/11 Y.Matsukawa	���饯�륨�顼ȯ������connection�����Ǥ��Ƥ��ʤ��ä�
// 2009/02/03 Y.Matsukawa	���ꥢ����������ʸ����ˤ�null�Υǡ������������ʤҤȤޤ��裱���ؤΤ��б���
// 2009/02/16 Y.Matsukawa	Ⱦ���Ѵ���ǽ���ɲá�z2h�ѥ�᡼����
// 2009/12/16 Y.Matsukawa	�������ܳ�ĥ��50��200��
// 2010/11/03 K.Masuda		���ꥢ����ʣ���б�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2013/08/05 N.Wada		¨��ȿ���оݴ���б�
// 2014/05/13 Y.Matsukawa	���ʤǹʤ����
// 2015/01/26 Y.Matsukawa	�����ȹ��ܤη夢�碌��sortlpad�ˡֻ�����,������ʸ���פǻ�������sortlpad=2,0
//							���ҤȤޤ���ʬ���ܤˤ����б����ޤ���
// 2017/5/11 H.Yasunaga		�����󥭥��ڡ����б�
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	/*==============================================*/
	// �����ϳ���
	/*==============================================*/
	include("logs/inc/com_log_open.inc");

	// CGI�ֹ�
	$CGICD = "804";
	
	// ���ԥ�����(LF)
	$RETCD = "\n";

	/*==============================================*/
	// ����ե�����
	/*==============================================*/
	include("ZdcCommonFunc.inc");	// ���̴ؿ�			add 2009/02/16 Y.Matsukawa
	include("chk.inc");         // �ǡ��������å���Ϣ
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("log.inc");         // ������
	include("crypt.inc");       // �Ź沽
	include("jkn.inc");         // ��������Խ�
	require_once("function.inc");			// ���̴ؿ�	add 2013/08/05 N.Wada

	/*==============================================*/
	// ���顼���Ϥ�����Ū��OFF
	/*==============================================*/
	error_reporting(0);

	/*==============================================*/
	// �����
	/*==============================================*/
	$status = $CGICD . "00000";
	$count = 0;
	$datacnt = 0;

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	/* API���� */
	if ($_POST["key"] != "") {
		$KEY = $_POST["key"];
	}
	if ($_GET["key"] != "") {
		$KEY = $_GET["key"];
	}

	/* �������� */
	if ($_POST["pos"] != "") {
		$POS = $_POST["pos"];
	}
	if ($_GET["pos"] != "") {
		$POS = $_GET["pos"];
	}
	if ($POS == "") {
		$POS = 1;
	}

	/* ������� */
	if ($_POST["cnt"] != "") {
		$CNT = $_POST["cnt"];
	}
	if ($_GET["cnt"] != "") {
		$CNT = $_GET["cnt"];
	}
	if ($CNT == "") {
		$CNT = 100;
	}

	/* ���ID */
	if ($_POST["cid"] != "") {
		$CID = $_POST["cid"];
	}
	if ($_GET["cid"] != "") {
		$CID = $_GET["cid"];
	}
	
	/* ���ꥢ������� */
	if ($_POST["area"] != "") {
		$AREA = $_POST["area"];
	}
	if ($_GET["area"] != "") {
		$AREA = $_GET["area"];
	}

	/* ������� */
	if ($_POST["jkn"] != "") {
		$JKN = $_POST["jkn"];
	}
	if ($_GET["jkn"] != "") {
		$JKN = $_GET["jkn"];
	}

	/* opt */
	if ($_POST["opt"] != "") {
		$OPT = $_POST["opt"];
	}
	if ($_GET["opt"] != "") {
		$OPT = $_GET["opt"];
	}
	
	if ($_POST["cust"] != "") {
		$CUST = $_POST["cust"];
	}
	if ($_GET["cust"] != "") {
		$CUST = $_GET["cust"];
	}

	// add 2010/11/03 K.Masuda [
	/* ���ꥢ�����ѥ����� */
	// mod 2011/07/05 Y.Nakajima
	if (isset($_POST["areaptn"]) && $_POST["areaptn"] != "") {
		$AREAPTN = $_POST["areaptn"];
	} else
	// mod 2011/07/05 Y.Nakajima
	if (isset($_GET["areaptn"]) && $_GET["areaptn"] != "") {
		$AREAPTN = $_GET["areaptn"];
	}
	// mod 2011/07/05 Y.Nakajima
	if(!isset($AREAPTN))$AREAPTN=1;
	// add 2010/11/03 K.Masuda ]
	
	// �����Ȼ��夢�碌		add 2015/01/26 Y.Matsukawa
	$SORTLPAD = ${'_'.$_SERVER['REQUEST_METHOD']}['sortlpad'];
	if ($SORTLPAD != '') {
		list($lpadlen, $lpadchar) = explode(',', $SORTLPAD);
		if (is_numeric($lpadlen) || $lpadchar != '') {
			$SORTLPAD = "$lpadlen,'$lpadchar'";
		} else {
			$SORTLPAD = '';
		}
	}

	/*==============================================*/
	// API�����ǥ�����      �������Ϥǻ��Ѥ�������ʤΤǡ�ǧ�ڤϹԤäƤ��ޤ���
	/*==============================================*/
	$KEY = f_decrypt_api_key( $KEY );
	// �ǥ����ɸ��ʸ���󤬲���Ƥ�����ϥ��˽��Ϥ��ʤ�
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}
	
	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	/* �������֥����å� */
	$Flg = NumChk($POS);
	if ($Flg != "OK") {
		$status = $CGICD . "19200";
		//      echo "�������� num���顼" . $RETCD; /* DEBUG */
	}
	if ($POS < 1) {
		//$status = $CGICD . "192001";
		$status = $CGICD . "19200";
		//      echo "�������� �����顼" . $RETCD; /* DEBUG */
	}

	/* ������������å� */
	$Flg = NumChk($CNT);
	if ($Flg != "OK") {
		$status = $CGICD . "19200";
		//      echo "������� num���顼" . $RETCD; /* DEBUG */
	}
	if ($CNT < 1) {
		$status = $CGICD . "19200";
		//      echo "������� �����顼" . $RETCD; /* DEBUG */
	}

	/* ���ID */
	if ($CID == "") {
		// ���ID����̵�����顼
		$status = $CGICD . "19200";
	}

	/* ������� */
	//edit_jkn($JKN, $edited_jkn, $arr_log_jkn, "k.");		mod 2014/05/13 Y.Matsukawa
	edit_jkn($JKN, $edited_jkn, $arr_log_jkn, "k.", '', $CID);
	$log_jkn = implode(" ", $arr_log_jkn);

	// LOG�����Ѥ˥ѥ�᡼���ͤ���ʢ����ꥢ���Ÿ����ˤ⤦�����äƤޤ�����
	$parms = "";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;

	// ���顼
	if ($status != $CGICD . "00000") {
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	
	/*==============================================*/
	// �ǡ����١�������³
	/*==============================================*/
	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		$status = $CGICD . "17900";
	}
	if ($status != $CGICD . "00000") {
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	
	// add 2017/5/11 H.Yasunaga �����󥭥��ڡ����б� [
	if ($CUST == "lowsoncampaign") {
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
	// add 2017/05/11 H.Yasunaga ]


	// add 2013/08/05 N.Wada
	/*==============================================*/
	// ¨����ե�å����о���������
	/*==============================================*/
	$immref = isIMMREFAvailable( &$dba, $CID );

	/*==============================================*/
	// �ǡ�������̾����
	/*==============================================*/
	// add 2010/11/03 K.Masuda [
	$underbar = "";
	for($ucnt=0;$ucnt<$AREAPTN-2;$ucnt++){
		$underbar .= "_";
	}
	$out1ptn = $underbar."1%";
	$out2ptn = $underbar."2%";
	// add 2010/11/03 K.Masuda ]

	// mod 2011/07/05 Y.Nakajima
	if (!isset($AREA) || (isset($AREA) && $AREA == "")) {
		// mod 2010/11/03 K.Masuda [
		//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
		if( $AREAPTN == 1 ){
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
		} else {
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out1ptn . "' and corp_id='" . $CID . "'";
		}
		// mod 2010/11/03 K.Masuda ]
	} else {
		// mod 2010/11/03 K.Masuda [
		//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
		// mod 2011/07/05 Y.Nakajima
		if( isset($AREAPTN) && $AREAPTN == 1 ){
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
		} else {
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out2ptn . "' and corp_id='" . $CID . "'";
		}
		// mod 2010/11/03 K.Masuda ]
	}
	//echo $sql . $RETCD; /* DEBUG�� */
	
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME = $data["ITEM_NAME"];
			$COL_NAME  = $data["COL_NAME"];
			$VAL_KBN   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME = "";
			$COL_NAME  = "";
			$VAL_KBN   = "";
		}
		$dba->free($stmt);
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}

	// mod 2010/11/03 K.Masuda [
	//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
	if( $AREAPTN == 1 ){
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
	} else {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out1ptn . "' and corp_id='" . $CID . "'";
	}
	// mod 2010/11/03 K.Masuda ]
	//echo $sql . $RETCD; /* DEBUG�� */
	
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME_1 = $data["ITEM_NAME"];
			$COL_NAME_1  = $data["COL_NAME"];
			$VAL_KBN_1   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME_1 = "";
			$COL_NAME_1  = "";
			$VAL_KBN_1   = "";
		}
		$dba->free($stmt);
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}

	// 2007/05/14 add Y.Matsukawa ��
	// mod 2010/11/03 K.Masuda [
	//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
	if( $AREAPTN == 1 ){
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
	} else {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out2ptn . "' and corp_id='" . $CID . "'";
	}
	// mod 2010/11/03 K.Masuda ]
	//echo $sql . $RETCD; /* DEBUG�� */

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME_2 = $data["ITEM_NAME"];
			$COL_NAME_2  = $data["COL_NAME"];
			$VAL_KBN_2   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME_2 = "";
			$COL_NAME_2  = "";
			$VAL_KBN_2   = "";
		}
		$dba->free($stmt);
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	// 2007/05/14 add Y.Matsukawa ��

	if ($ITEM_NAME == "" or $ITEM_NAME_1 == "") {
		// ���ꥢ��������̵�����顼
		$status = $CGICD . "11008";
	}

	// ���ꥢ������������������JKN�������
	// mod 2011/07/05 Y.Nakajima [
	if (isset($AREA) && $AREA != "") {
		if (isset($COL_NAME_1) && $COL_NAME_1 != "") {
	// mod 2011/07/05 Y.Nakajima ]
			switch ($COL_NAME_1) {
				case "NAME":
					$idx = 1;
					break;
				case "ADDR":
					$idx = 2;
					break;
				case "FREE_SRCH":
					$idx = 53;
					break;
				default:
					//$idx = intval(substr($COL_NAME_1, 4, 2)) + 2;		del 2009/12/16 Y.Matsukawa
					// add 2009/12/16 Y.Matsukawa [
					$idx = intval(substr($COL_NAME_1, 4));
					if ($idx <= 50)
						$idx += 2;
					else
						$idx += 4;
					// add 2009/12/16 Y.Matsukawa ]
			}
			// mod 2011/07/05 Y.Nakajima
			if (isset($idx) && $idx != "") {
				$arr_log_jkn[$idx] = $AREA;
				$log_jkn = implode(" ", $arr_log_jkn);
			}
		}
	}

	// LOG�����Ѥ˥ѥ�᡼���ͤ���ʥ��ꥢ�����������ȿ�ǡ�
	$parms = "";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;
	
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	// mod 2011/07/05 Y.Nakajima
	if (!isset($AREA) || (isset($AREA) && $AREA == "") ) {
		/* 2007/05/14 mod Y.Matsukawa
		$head2 = $COL_NAME   . "\t" . $ITEM_NAME   . "\t" . ""    . "\t" . ""         . "\t" . ""; */
		$head2 = $COL_NAME   . "\t" . $ITEM_NAME   . "\t" . ""    . "\t" . $COL_NAME_2 . "\t" . $ITEM_NAME_2;
	} else {
		$AREA = mb_convert_encoding($AREA, "EUC-JP", "auto");
		$head2 = $COL_NAME_1 . "\t" . $ITEM_NAME_1 . "\t" . $AREA . "\t" . $COL_NAME . "\t" . $ITEM_NAME;
	}
	$head2 = ZdcConvZ2H($head2, $z2h);		// add 2009/02/16 Y.Matsukawa

	/*==============================================*/
	// �оݥǡ�������
	/*==============================================*/
	// add 2013/08/05 N.Wada [
	if ( $immref ) {
		$kyoten_tbl_name = "im_kyoten_tbl";
	} else {
		$kyoten_tbl_name = "kyoten_tbl";
	}
	// add 2013/08/05 N.Wada ]
	
	// �����Ƚ�ʷ夢�碌��		add 2015/01/26 Y.Matsukawa
	if ($SORTLPAD != '') {
		$SORT = "lpad($COL_NAME, $SORTLPAD)";
	} else {
		$SORT = $COL_NAME;
	}
	
	// �裱����
	// mod 2011/07/05 Y.Nakajima
	if (!isset($AREA)  || (isset($AREA) && $AREA == "")) {
		// ��ʬ����
		if ($VAL_KBN == "L") {
			//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";	mod 2013/08/05 N.Wada
			$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
			$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
			$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
			$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //������ͭ��ξ��
				$sql .= " and $edited_jkn ";
			}
			//$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;		mod 2015/01/26 Y.Matsukawa
			$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $SORT;
		// ʸ����
		} else {
			$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
			$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
			//$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from kyoten_tbl k";	mod 2013/08/05 N.Wada
			$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
			//$sql = $sql . " where corp_id='" . $CID . "' group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			$sql = $sql . " where corp_id='" . $CID . "' ";
			$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //������ͭ��ξ��
				$sql .= " and $edited_jkn ";
			}
			$sql = $sql . " and " . $COL_NAME . " is not null";		// add 2009/02/03 Y.Matsukawa
			$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
		}
	// �裲����
	} else {
		$AREA = mb_convert_encoding($AREA, "EUC-JP", "auto");
		// ��ʬ����
		if ($VAL_KBN == "L") {
			// �裱���ؤ���ʬ����
			if ($VAL_KBN_1 == "L") {
				//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				//$sql = $sql . " and " . $COL_NAME_1 . "='" . $AREA;
				//$sql = $sql . "' group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
				$sql = $sql . " and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				//$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;		mod 2015/01/26 Y.Matsukawa
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $SORT;
			// �裱���ؤ�ʸ����
			} else {
				//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				$sql = $sql . " and k." . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				//$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;		mod 2015/01/26 Y.Matsukawa
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $SORT;
			}
		// ʸ����
		} else {
			// �裱���ؤ���ʬ����
			if ($VAL_KBN_1 == "L") {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				//$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
				//$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA;
				//$sql = $sql . "' group by " . $COL_NAME . " order by " . $COL_NAME . ")";
				$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			// �裱���ؤ�ʸ����
			} else {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				//$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
				//$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA;
				//$sql = $sql . "' group by " . $COL_NAME . " order by " . $COL_NAME . ")";
				$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //������ͭ��ξ��
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			}
		}
	}

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	
	$count = 0;
	$datacnt = 0;
	$kyoten_cnt = 0;
	$ret = "";
	$dbflg = 0;

	// pos���֤ޤ��ɤ����Ф�
	for ($n = 1;$n<=$POS - 1;$n++) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$target3 = $data[2];
			$kyoten_cnt = $kyoten_cnt + $target3;
			$datacnt = $datacnt + 1;
		} else {
			$dbflg = 1;
			break;
		}
	}

	// �����ǡ����ɤ߹���
	if ( $dbflg == 0 ) {
		for ($n=1; $n<=$CNT; $n++) {
			if( $dba->getRecInto( $stmt,$data ) ) {
				//$target1 = $data[0];		mod 2009/02/16 Y.Matsukawa
				$target1 = ZdcConvZ2H($data[0], $z2h);
				//$target2 = $data[1];		mod 2009/02/16 Y.Matsukawa
				$target2 = ZdcConvZ2H($data[1], $z2h);
				$target3 = $data[2];
				$ret = $ret . $target1 . "\t" . $target2 . "\t" . $target3 . $RETCD;;
				$count = $count + 1;
				$kyoten_cnt = $kyoten_cnt + $target3;
				$datacnt = $datacnt + 1;
			} else {
				$dbflg = 1;
				break;
			}
		}
	}

	// ��³�ǡ�����ǧ
	if ( $dbflg == 0 ) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$status = $CGICD . "00001";
			$target3 = $data[2];
			$kyoten_cnt = $kyoten_cnt + $target3;
			$datacnt = $datacnt + 1;
		}
	}

	// �Ĥ���������
	while ($dba->getRecInto( $stmt,$data )) {
		$target3 = $data[2];
		$kyoten_cnt = $kyoten_cnt + $target3;
		$datacnt = $datacnt + 1;
	}

	$dba->free($stmt);

	/*==============================================*/
	// �ǡ�������
	/*==============================================*/
	/* �إå����󣱽��� */
	if (strlen($ret) == 0) {
		/* ���ơ����� */
		$status = $CGICD . "11009"; /* �����ǡ����ʤ� */
		$count = 0;
	}
	$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10��ɽ�� */
	$ords = $head . $RETCD;
	echo $ords;

	/* �إå����󣲽��� */
	$head2 = $head2 . "\t" . $kyoten_cnt . $RETCD;
	echo $head2;

	/* ����������� */
	echo $ret;

	/*==============================================*/
	// ����
	/*==============================================*/
	$dba->close();

	/*==============================================*/
	// ������
	/*==============================================*/
	put_log($status, $KEY, $OPT, $parms);
?>
