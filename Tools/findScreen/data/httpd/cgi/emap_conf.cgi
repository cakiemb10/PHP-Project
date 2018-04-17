<?php
/*========================================================*/
// �ե�����̾��emap_conf.cgi
// ����̾������������
//
// ��������2007/01/12
// �����ԡ�H.Ueno
//
// ���⡧e-map���������֤���
//
// ��������
// 2007/01/12 H.Ueno		��������
// 2007/03/20 Y.Matsukawa	���URL�����ĥ�ե��顼�ν��ϻ���HTML�ü�ʸ���򥨥�ƥ��ƥ��Ѵ�����
// 2008/03/12 Y.Matsukawa	emap_pc_conf��opt_10�򡢥���޶��ڤ�ζ��ѥ����Ȥ����<OPT_10_1>��<OPT_10_n>��ʬ�䤷���֤���
// 2008/09/02 Y.Matsukawa	emap_pc_conf��opt_09�򡢥���޶��ڤ�ζ��ѥ����Ȥ����<OPT_09_1>��<OPT_09_n>��ʬ�䤷���֤���
// 2009/07/15 Y.Matsukawa	AD Maplink�б�
// 2011/05/24 Y.Matsukawa	���ޡ��ȥե������б�
// 2013/07/19 T.Sasaki		������ʣ���˲����б�
/*========================================================*/
	header("Content-Type: Text/html; charset=euc-jp");

	include("d_serv_ora.inc");
	include("oraDBAccess.inc");
	include("sql_collection_emap_conf.inc");

	// CGI����
	$cgi_kind = "807";
	
	// ����ʸ��������
	$enc = "EUC";

	// ���ϥѥ�᡼������
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$corp_id = urldecode($_GET['cid']);   //���ID
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$corp_id = urldecode($_POST['cid']);  //���ID
	}

	// ���ϥǡ������꣱
	$buf  = "<?xml version=\"1.0\" encoding=\"EUC-JP\" standalone=\"yes\" ?>\n";
	$buf .= "<EMAP>\n";

	// ���ϥѥ�᡼�������å�
	if ($corp_id == "") {
		$buf .= "<RETCODE>" . $cgi_kind . "19100</RETCODE>\n";
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}

	// DB�����ץ�
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17900</RETCODE>\n";
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	$sql = "alter session set nls_date_format='yyyymmdd'";
	$dba->sqlExecute($sql, $stmt);

	// EMAP_CORP_MST��������
	$cols_emap_corp_mst = array();
	$retcd = get_colnames(&$dba, "EMAP_CORP_MST", &$cols_emap_corp_mst);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_PC_CONF_TBL��������
	$cols_emap_pc_conf_tbl = array();
	$retcd = get_colnames(&$dba, "EMAP_PC_CONF_TBL", &$cols_emap_pc_conf_tbl);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_M_CONF_TBL��������
	$cols_emap_m_conf_tbl = array();
	$retcd = get_colnames(&$dba, "EMAP_M_CONF_TBL", &$cols_emap_m_conf_tbl);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_SMT_CONF_TBL��������		add 2011/05/24 Y.Matsukawa
	$cols_emap_smt_conf_tbl = array();
	$retcd = get_colnames(&$dba, "EMAP_SMT_CONF_TBL", &$cols_emap_smt_conf_tbl);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// KYOTEN_ITEM_TBL��������
	$cols_kyoten_item_tbl = array();
	$retcd = get_colnames(&$dba, "KYOTEN_ITEM_TBL", &$cols_kyoten_item_tbl);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// KYOTEN_ITEM_VAL_TBL��������
	$cols_kyoten_item_val_tbl = array();
	$retcd = get_colnames(&$dba, "KYOTEN_ITEM_VAL_TBL", &$cols_kyoten_item_val_tbl);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	
	// EMAP_CORP_MST�ǡ�������
	$arr_emap_corp_mst = array();
	$retcd = select_emap_corp_mst(&$dba, $corp_id, &$arr_emap_corp_mst);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$buf .= "<RETCODE>" . $cgi_kind . "11009</RETCODE>\n";  //������̥ǡ����ʤ�
		} else {    //9
			$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		}
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_PC_CONF_TBL�ǡ�������
	$arr_emap_pc_conf_tbl = array();
	$retcd = select_emap_pc_conf_tbl(&$dba, $corp_id, &$arr_emap_pc_conf_tbl);
	if (($retcd != 0) && ($retcd != 1)) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_M_CONF_TBL�ǡ�������
	$arr_emap_m_conf_tbl = array();
	$retcd = select_emap_m_conf_tbl(&$dba, $corp_id, &$arr_emap_m_conf_tbl);
	if (($retcd != 0) && ($retcd != 1)) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_SMT_CONF_TBL�ǡ�������		add 2011/05/24 Y.Matsukawa
	$arr_emap_smt_conf_tbl = array();
	$retcd = select_emap_smt_conf_tbl(&$dba, $corp_id, &$arr_emap_smt_conf_tbl);
	if (($retcd != 0) && ($retcd != 1)) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// KYOTEN_ITEM_TBL�ǡ�������
	$arr_kyoten_item_tbl = array();
	$retcd = select_kyoten_item_tbl(&$dba, $corp_id, &$arr_kyoten_item_tbl);
	if (($retcd != 0) && ($retcd != 1)) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// EMAP_PARM_TBL�ǡ�������			add 2009/07/15 Y.Matsukawa
	$arr_emap_parm_tbl = array();
	$retcd = select_emap_parm_tbl(&$dba, $corp_id, &$arr_emap_parm_tbl);
	if (($retcd != 0) && ($retcd != 1)) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// KYOTEN_IMG_DEF_TBL ����������ʣ���˥ǡ������� add start 2013/07/11 T.Sasaki
	$arr_kyoten_img_def_tbl = array();
	$retcd = select_kyoten_img_def_tbl( &$dba , $corp_id , &$arr_kyoten_img_def_tbl );
	if (($retcd != 0) && ($retcd != 1)) {
		$dba->close();
		$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";	//����¾DB���顼
		$buf .= "</EMAP>\n";
		print $buf;
		exit;
	}
	// KYOTEN_IMG_DEF_TBL ����������ʣ���˥ǡ������� add end

	// ���ϥǡ������ꣲ
	$buf .= "<RETCODE>" . $cgi_kind . "00000</RETCODE>\n";

	$buf .= "<EMAP_CORP_MST>\n";
	foreach ($cols_emap_corp_mst as $colnm) {
		$buf .= "<".$colnm.">".htmlspecialchars($arr_emap_corp_mst[$colnm])."</".$colnm.">\n";
	}
	// add 2011/05/24 Y.Matsukawa [
	// EMAP_PARM_TBL���ͤ�EMAP_CORP_MST���ݻ�
	if (count($arr_emap_parm_tbl)) {
		foreach ($arr_emap_parm_tbl as $rowdata) {
			$buf .= "<".$rowdata["KBN"].">".htmlspecialchars($rowdata["VALUE"])."</".$rowdata["KBN"].">\n";
		}
	}
	// add 2011/05/24 Y.Matsukawa ]
	$buf .= "</EMAP_CORP_MST>\n";

	$buf .= "<EMAP_PC_CONF_TBL>\n";
	foreach ($cols_emap_pc_conf_tbl as $colnm) {
		// OPT_05,OPT_09,OPT_10��ʣ�����ܤ򥿥ֶ��ڤ���ݻ����Ƥ���Τǡ�ʬ�򤷤ƽ���
		if (strtoupper($colnm) == "OPT_05" || strtoupper($colnm) == "OPT_09" || strtoupper($colnm) == "OPT_10") {
			$values = explode("\t", $arr_emap_pc_conf_tbl[$colnm]);
			if (count($values)) {
				foreach ($values as $i => $val) {
					$n = $i + 1;
					$buf .= "<".$colnm."_".$n.">".htmlspecialchars($val)."</".$colnm."_".$n.">\n";
				}
			} else {
				$buf .= "<".$colnm."></".$colnm.">\n";
			}
		// ����ʳ��ι��ܤϤ��Τޤ޽���
		} else {
			$buf .= "<".$colnm.">".htmlspecialchars($arr_emap_pc_conf_tbl[$colnm])."</".$colnm.">\n";
		}
	}
	$buf .= "</EMAP_PC_CONF_TBL>\n";
	
	$buf .= "<EMAP_M_CONF_TBL>\n";
	foreach ($cols_emap_m_conf_tbl as $colnm) {
		// OPT_07��ʣ�����ܤ򥿥ֶ��ڤ���ݻ����Ƥ���Τǡ�ʬ�򤷤ƽ���
		if (strtoupper($colnm) == "OPT_07") {
			$values = explode("\t", $arr_emap_m_conf_tbl[$colnm]);
			if (count($values)) {
				foreach ($values as $i => $val) {
					$n = $i + 1;
					$buf .= "<".$colnm."_".$n.">".htmlspecialchars($val)."</".$colnm."_".$n.">\n";
				}
			} else {
				$buf .= "<".$colnm."></".$colnm.">\n";
			}
		// ����ʳ��ι��ܤϤ��Τޤ޽���
		} else {
			$buf .= "<".$colnm.">".htmlspecialchars($arr_emap_m_conf_tbl[$colnm])."</".$colnm.">\n";
		}
	}
	$buf .= "</EMAP_M_CONF_TBL>\n";
	
	// add 2011/05/24 Y.Matsukawa [
	$buf .= "<EMAP_SMT_CONF_TBL>\n";
	foreach ($cols_emap_smt_conf_tbl as $colnm) {
		$buf .= "<".$colnm.">".htmlspecialchars($arr_emap_smt_conf_tbl[$colnm])."</".$colnm.">\n";
	}
	$buf .= "</EMAP_SMT_CONF_TBL>\n";
	// add 2011/05/24 Y.Matsukawa ]
	
	$buf .= "<KYOTEN_ITEM_TBL>\n";
	$buf .= "<ITEMLIST>\n";
	foreach ( $arr_kyoten_item_tbl as $rowdata ) {
		$buf .= "<ITEM>\n";
		foreach ($cols_kyoten_item_tbl as $colnm) {
			$buf .= "<".$colnm.">".htmlspecialchars($rowdata[$colnm])."</".$colnm.">\n";
		}
		// �����ǡ��������ͥơ��֥����
		$arr_kyoten_item_val_tbl = array();
		$retcd = select_kyoten_item_val_tbl(&$dba, $rowdata["CORP_ID"], $rowdata["COL_NAME"], &$arr_kyoten_item_val_tbl);
		if ($retcd != 0) {
			if ($retcd == 1) {
				$buf .= "</ITEM>\n";
				continue;   //������̥ǡ����ʤ��ʵ��������ͥơ��֥��ɽ�����ʤ�����
			} else {    //9
				$dba->close();
				$buf .= "<RETCODE>" . $cgi_kind . "17999</RETCODE>\n";  //����¾DB���顼
				$buf .= "</EMAP>\n";
				print $buf;
				exit;
			}
		}
		$buf .= "<ITEM_VAL_LIST>\n";
		foreach ($arr_kyoten_item_val_tbl as $rowdata2) {
			$buf .= "<ITEM_VAL>\n";
			foreach ($cols_kyoten_item_val_tbl as $colnm) {
				$buf .= "<".$colnm.">".htmlspecialchars($rowdata2[$colnm])."</".$colnm.">\n";
			}
			$buf .= "</ITEM_VAL>\n";
		}
		$buf .= "</ITEM_VAL_LIST>\n";
		$buf .= "</ITEM>\n";
	}
	$buf .= "</ITEMLIST>\n";
	$buf .= "</KYOTEN_ITEM_TBL>\n";
	
	// EMAP_PARM_TBL			add 2009/07/15 Y.Matsukawa
	if (count($arr_emap_parm_tbl)) {
		$buf .= "<EMAP_PARM_TBL>\n";
		foreach ($arr_emap_parm_tbl as $rowdata) {
			$buf .= "<".$rowdata["KBN"].">".htmlspecialchars($rowdata["VALUE"])."</".$rowdata["KBN"].">\n";
		}
		$buf .= "</EMAP_PARM_TBL>\n";
	}
	
	// KYOTEN_IMG_DEF_TBL ����������ʣ���˥ǡ������� add start 2013/07/11 T.Sasaki
	if ( count( $arr_kyoten_img_def_tbl ) ) {
		$buf .= "<KYOTEN_IMG_DEF_TBL>\n";
		foreach ( $arr_kyoten_img_def_tbl as $rowdata ) {
			$buf .= "<ITEM>\n";
				$buf .= "<IMG_NO>"	.htmlspecialchars($rowdata["IMG_NO"])  ."</IMG_NO>\n";
				$buf .= "<IMG_NAME>".htmlspecialchars($rowdata["IMG_NAME"])."</IMG_NAME>\n";
			$buf .= "</ITEM>\n";
		}
		$buf .= "</KYOTEN_IMG_DEF_TBL>\n";
	}
	// KYOTEN_IMG_DEF_TBL ����������ʣ���˥ǡ������� add end
	
	$buf .= "</EMAP>\n";
	
	if ( $enc != "EUC" ) {
		$buf = mb_convert_encoding( $buf, $enc );
	}

	// DB������
	$dba->close();
	
	// �ǡ�������
	print $buf;

?>

