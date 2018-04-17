<?php
/*========================================================*/
// ��������
// 2015/01/20 F.Yokoi		��������
// 2015/05/29 F.Yokoi		�Զ�罤���ʥǡ�����Ͽ��DB���ѹ��˵ڤӥ��顼����������ѹ�
/*========================================================*/
//	error_reporting(0);

	/*==============================================*/
	// �꥿���󥳡������
	/*==============================================*/
	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );       //�����
	define( 'DEF_RETCD_DEND', '00001' );       //��Ͽ��λ
	define( 'DEF_RETCD_DERR1','17900' );       //�ǡ����١��������������顼
	define( 'DEF_RETCD_DERR2','17002' );       //�ǡ����١��������������顼
	define( 'DEF_RETCD_DERR3','17999' );       //�ǡ����١��������������顼
	define( 'DEF_RETCD_PERR1','19100' );       //���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19200' );       //���ϥѥ�᡼�����顼(��ʸ���顼)
	define( 'DEF_RETCD_PERR3','19300' );       //���ϥѥ�᡼�����顼(�����å����顼)

	/*==============================================*/
	// ����ե�����
	/*==============================================*/
	header('Content-Type: Text/html; charset=euc-jp');

	require_once('d_serv_cgi.inc');
	require_once('d_serv_emap.inc');
	include("ZdcCommonFunc.inc");	// ���̴ؿ�
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/oraDBAccessMst.inc"); // add 20150529 F.Yokoi
	include("chk.inc");         // �ǡ��������å���Ϣ
	include("log.inc");         // ������
	//include("crypt.inc");       // �Ź沽
	//include("jkn.inc");         // ��������Խ�
	include("../pc/inc/function.inc");         // ʸ�����󥳡��ɽ���
	require_once('function.inc');
	include("inc/rd_sql.inc");
	//include('inc/sql_collection.inc');
	include('inc/rd_ora_procif.inc');

	//�����ϳ���
	include("logs/inc/com_log_open.inc");

	$status = DEF_RETCD_DE;
	$cgi_kind = "rd_entry";

	if ($_SERVER['REQUEST_METHOD'] == 'GET') {
		$status = DEF_RETCD_PERR1;
		fwd_error_page("", $status);
	} else if ($_SERVER['REQUEST_METHOD'] == 'POST') {
		$corp_id = urldecode($_POST['corp_id']);
		$kyoten_id = urldecode($_POST['kyoten_id']);

		$arr_entry_item = array();

		foreach ($_POST as $key => $value) {
			if (preg_match('/RD[0-9]+\_[0-9]+/', $key)) {
				$rd_no = preg_replace('/RD/', '', $key);
				list($g_no, $item_no) = explode("_", $rd_no);
				$arr_entry_item[$g_no][$item_no] = mb_convert_encoding (urldecode($value), "EUC-JP", "UTF-8");
			}
		}
	}

	// �ǡ���̵ͭ�����å�
	if ($corp_id == "") { // ���ID
		$status = DEF_RETCD_PERR1;
		fwd_error_page("", $status);
	}
	if ($kyoten_id == "") { // ����ID
		$status = DEF_RETCD_PERR1;
		fwd_error_page("", $status);
	}

	// �ǡ����١��������ץ�
	$dba = new oraDBAccess();
	if (! $dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1; // mod 20150529 F.Yokoi [
		print $status;
		rd_entry_errorlog($corp_id, $kyoten_id, "", "", "Pub ".DEF_RETCD_DERR1); // mod 20150529 F.Yokoi ]
		exit;
	}

	$arr_item_dtl ="";
		
	//��������������
	$ret = SelectRDItemDef(&$dba, $corp_id);
	if ($ret == false) {
		$status = DEF_RETCD_DNE;
		fwd_error_page("", $status);
	}
	else {
		$arr_item_dtl = $ret;
	}
	$dba->close(); // mod 20150529 F.Yokoi

	// �ǡ�������Ͽ������
	$i_kbn = "A";
	$i_commit_mode = 1;
	$i_uid = "rdety";
	$status = 1;

	$arr_opt = array(
				"OPT_01" => "",
				"OPT_02" => "",
				"OPT_03" => "",
				"OPT_04" => "",
				"OPT_05" => "",
				"OPT_06" => "",
				"OPT_07" => "",
				"OPT_08" => "",
				"OPT_09" => "",
				"OPT_10" => ""
				);

	// �ǡ����١��������ץ� add 20150529 F.Yokoi [
	$dba_mst = new oraDBAccessMst();
	if (! $dba_mst->open()) {
		$dba_mst->close();
		$status = DEF_RETCD_DERR1;
		print $status;
		rd_entry_errorlog($corp_id, $kyoten_id, "", "", "Mst ".DEF_RETCD_DERR1);
		exit;
	}
	// add 20150529 F.Yokoi ]

	foreach ($arr_entry_item as $g_no => $gvalue) {
		// ���롼�פ���Ͽ������
		if(!spif_p_rd_group_updt(&$dba_mst, $i_kbn, $i_commit_mode, $i_uid, $corp_id, $kyoten_id, $g_no, $status, $st_dt, $ed_dt, &$arr_opt, &$o_ins_dt, &$o_upd_dt, &$o_rtncd)){
			//���顼
			$dba_mst->rollbackTransaction(); // mod 20150529 F.Yokoi
			$dba_mst->close(); // mod 20150529 F.Yokoi

			$status = DEF_RETCD_DERR2;
			print $status;
			rd_entry_errorlog($corp_id, $kyoten_id, $g_no, "", "spif_p_rd_group_updt:".$status." ".join(" ", $_POST)); // mod 20150529 F.Yokoi 
			exit;
		}

		// �����ƥ����Ͽ������
		foreach ($arr_entry_item[$g_no] as $item_no => $ivalue) {

			$flg_data = "";
			$img_w  = "";
			$img_h  = "";
			$arr_opt = array(
						"OPT_01" => "",
						"OPT_02" => "",
						"OPT_03" => "",
						"OPT_04" => "",
						"OPT_05" => "",
						"OPT_06" => "",
						"OPT_07" => "",
						"OPT_08" => "",
						"OPT_09" => "",
						"OPT_10" => ""
						);
			$o_ins_dt = "";
			$o_upd_dt = "";
			$o_rtncd = "";

			if ($arr_item_dtl[$g_no][$item_no]['kbn'] === "T") { // ��ʬ�����å�
				if ($arr_item_dtl[$g_no][$item_no]['maxlen'] != "") {
					if (strlen($arr_entry_item[$g_no][$item_no]) <= intval($arr_item_dtl[$g_no][$item_no]['maxlen'])) { // ʸ���������å�
						if (!spif_p_rd_data_updt(&$dba_mst, $i_kbn, $i_commit_mode, $i_uid, $corp_id, $kyoten_id, $g_no, $item_no, $arr_item_dtl[$g_no][$item_no]['kbn'], $ivalue, $flg_data, $img_w, $img_h, &$arr_opt, &$o_ins_dt, &$o_upd_dt, &$o_rtncd)) {
							$dba_mst->rollbackTransaction(); // mod 20150529 F.Yokoi
							$dba_mst->close(); // mod 20150529 F.Yokoi

							$status = DEF_RETCD_DERR2;
							print $status;
							rd_entry_errorlog($corp_id, $kyoten_id, $g_no, $item_no, "spif_p_rd_data_updt:".$status." ".join(" ", $_POST)); // mod 20150529 F.Yokoi 
							exit;

						}
					}
				}
				else {
					if (!spif_p_rd_data_updt(&$dba_mst, $i_kbn, $i_commit_mode, $i_uid, $corp_id, $kyoten_id, $g_no, $item_no, $arr_item_dtl[$g_no][$item_no]['kbn'], $ivalue, $flg_data, $img_w, $img_h, &$arr_opt, &$o_ins_dt, &$o_upd_dt, &$o_rtncd)) {
						$dba_mst->rollbackTransaction(); // mod 20150529 F.Yokoi
						$dba_mst->close(); // mod 20150529 F.Yokoi

						$status = DEF_RETCD_DERR2;
						print $status;
						rd_entry_errorlog($corp_id, $kyoten_id, $g_no, $item_no, "spif_p_rd_data_updt:".$status." ".join(" ", $_POST)); // mod 20150529 F.Yokoi 
						exit;
					}
				}
			}
			else {
				$dba_mst->rollbackTransaction(); // mod 20150529 F.Yokoi
				$dba_mst->close(); // mod 20150529 F.Yokoi

				$status = DEF_RETCD_PERR3;
				print $status;
				rd_entry_errorlog($corp_id, $kyoten_id, $g_no, $item_no, $status." ".join(" ", $_POST)); // mod 20150529 F.Yokoi [
				exit;
			}
		}
	}

	$dba_mst->commitTransaction(); // mod 20150529 F.Yokoi
	$dba_mst->close(); // mod 20150529 F.Yokoi
	$status = DEF_RETCD_DEND;

	echo $status;
	exit;

// add 20150529 F.Yokoi [
// ------------------------------------------------------------
// ���顼�������
// ------------------------------------------------------------
function rd_entry_errorlog($corp_id, $kyoten_id, $group_no, $item_no, $str){
	@error_log(date('Y/m/d H:i:s')." ".$corp_id." ".$kyoten_id." ".$group_no." ".$item_no." ".$str."\n", 3, '/var/tmp/rd_entry_error_'.date('Ymd').'.log');
}
// add 20150529 F.Yokoi ]

?>
