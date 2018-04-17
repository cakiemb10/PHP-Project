<?php
/*========================================================*/
// �ե�����̾��zskr_union.cgi
// ����̾�������ȹ縡��
//
// ��������2016/02/29
// �����ԡ�H.Yasunaga
//
// ���⡧�����ȹ���֤���
//
// ��������
// 2016/02/29 H.Yasunaga		��������
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');
	include("ZdcCommonFunc.inc");	// ���̴ؿ�
	include("d_serv_ora.inc");
	include("oraDBAccess.inc");
	include("sql_collection_kyotenlist.inc");
	include("sql_collection_zskr.inc");
	include("chk.inc");         // �ǡ��������å���Ϣ
	include("log.inc");         // ������
	include("crypt.inc");       // �Ź沽
	include("jkn.inc");         // ��������Խ�
	include("../pc/inc/function.inc");         // ʸ�����󥳡��ɽ���
	require_once('function.inc');

	//�����ϳ���
	include("logs/inc/com_log_open.inc");

	// CGI����
	$cgi_kind = "881";
	
	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	if ($_SERVER['REQUEST_METHOD'] == "GET") {

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
		if (isset($_GET['union_id'])) {
			$union_id = $_GET['union_id'];	// �����ȹ缱�̻�
		} else {
			$union_id = "";
		}

	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
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
		
		if (isset($_POST['union_id'])) {
			$union_id = $_POST['union_id'];	// �����ȹ缱�̻�
		} else {
			$union_id = "";
		}
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

	
	/*==============================================*/
	// �����ȹ����
	/*==============================================*/
	$arr_kyoten_list = Array();
	$retdata;
	$retcd = select_union_id(&$dba, $union_id, &$retdata);
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


	/*==============================================*/
	// �����ȹ����
	/*==============================================*/
	$rec_num = count($arr_kyoten_list);
	if (($pos+$rec_num-1) < $hit_num) {   //��³�ǡ���ͭ��
		$out_retcd = $cgi_kind . "00001";
	} else {                                //��³�ǡ���̵��
		$out_retcd = $cgi_kind . "00000";
	}
	$out_retcd = $cgi_kind . "00000";
	
	print "$out_retcd\r\n";
	foreach($retdata as $rowdata){
		$buf =  $rowdata["UNION_ID"]        . "\t" .	// ��ͻ���إ�����
				$rowdata["UNION_NAME"]      . "\t" .	// �����ȹ�̾��
				$rowdata["NATION_WIDE_FLG"] . "\t" .	// ����ե饰
				$rowdata["LAT"]             . "\t" .	// ����
				$rowdata["LON"]             . "\t" .	// ����
				$rowdata["JURISDICTION_FILE"];			// �ɳ��ꥢ�����ե�����̾
		$buf .= "\n";
		print $buf;
	}

	// ������
	put_log($out_retcd, $KEY, $opt, $parms);
?>
