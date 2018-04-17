<?php
/*========================================================*/
// �ե�����̾��kyoten_nearsearch.cgi
// ����̾���Ǵ���������
//
// ��������2010/01/08
// �����ԡ�Y.Matsukawa
//
// ���⡧�Ǵ������ꥹ�Ȥ��֤���
//
// ��������
// 2010/01/08 Y.Matsukawa	��������
// 2010/01/25 Y.Matsukawa	���Ϲ����ɲá�created,modified,comment_count��
// 2011/07/05 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/10/17 Y.Matsukawa	error_reporting()���
/*========================================================*/
// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off�б�
//���ϥѥ�᡼���������������ɲ�
//post,get
//Ʊ��̾�Τǥѥ�᡼�������ä����ϡ�
//POST��ͥ�褹��
extract($_GET);
extract($_POST);
// add 2011/07/05 Y.Nakajima ]


/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = "k02";

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER["SCRIPT_FILENAME"], ".cgi"));

/*==============================================*/
// �꥿���󥳡������
/*==============================================*/
define( "DEF_RETCD_DE",   "00000" );       //���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
define( "DEF_RETCD_DEND", "00001" );       //���˸��礦�ǡ�������ʸ�³�ǡ��������
define( "DEF_RETCD_DNE",  "11009" );       //���˸��礦�ǡ����ʤ�
define( "DEF_RETCD_AERR", "12009" );       //ǧ�ڥ��顼
define( "DEF_RETCD_DERR1","17900" );       //�ǡ����١��������������顼
define( "DEF_RETCD_DERR2","17002" );       //�ǡ����١��������������顼
define( "DEF_RETCD_DERR3","17999" );       //�ǡ����١��������������顼
define( "DEF_RETCD_PERR1","19100" );       //���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
define( "DEF_RETCD_PERR2","19200" );       //���ϥѥ�᡼�����顼(��ʸ���顼)
define( "DEF_RETCD_PERR3","19200" );       //���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)

/*==============================================*/
// �����
/*==============================================*/
define("RAD_MAX",  100000);
define("KNSU_MAX", 1000);

/*==============================================*/
// ����ե�����
/*==============================================*/
require_once("kyoten_outf.inc");		// ���ϥ��饹���
require_once("ZdcCommonFuncAPI.inc");	// ���̴ؿ�
require_once("function.inc");			// ���̴ؿ�
require_once("d_serv_ora.inc");
require_once("oraDBAccess.inc");
require_once("chk.inc");				// �ǡ��������å���Ϣ
require_once("log.inc");				// ������
require_once("crypt.inc");				// �Ź沽
require_once("auth.inc");				// �ʰ�ǧ��

// ����������������ѥ��å�
require_once("kyoten_def_sekaicamera.inc");	// ����������������
// ����������������ѥ��å�

/*==============================================*/
// ���顼���Ϥ�����Ū��OFF
/*==============================================*/
//error_reporting(0);		del 2012/10/17 Y.Matsukawa

/*==============================================*/
//�����ϳ���
/*==============================================*/
include("logs/inc/com_log_open.inc");

/*==============================================*/
// �ѥ�᡼������cgi/inc/function.inc��
/*==============================================*/
$KEY		= getCgiParameter("key","");			/* ǧ�ڥ��� */
$POS		= getCgiParameter("pos","1");			/* �������� */
$CNT		= getCgiParameter("cnt","100");			/* ������� */
$CID		= getCgiParameter("cid","");			/* e-map���ID */
$LAT		= getCgiParameter("lat","");			/* ���� */
$LON		= getCgiParameter("lon","");			/* ���� */
$KNSU		= getCgiParameter("knsu","100");		/* ������ */
$RAD		= getCgiParameter("rad","2000");		/* Ⱦ��(m) */
$PFLG		= getCgiParameter("pflg","2");			/* �ݥ���ȥե饰 */
$DATUM		= getCgiParameter("datum",DATUM_TOKYO);	/* ¬�Ϸ� */
$OUTF		= getCgiParameter("outf","JSON");		/* ���Ϸ��� */
$ENC		= getCgiParameter("enc","SJIS");		/* ʸ�������� */
//$DTYPE		= getCgiParameter("dtype","7");			/* ɽ�����ܥѥ����� */
//$ND			= getCgiParameter("nd","SKIP");			/* ̤���Ϲ����ֵѻ��� */

$OPTION_CD = mb_strimwidth($CID, 0, 20, '...');

$CID_LIST = array();

if ($CID != "") {
	$CID_LIST = explode(',', $CID);
	//$CID_LIST = array_intersect($CID_LIST, $EMAP_CID);
	// ����������������ѥ��å�
	// �����������ID��e-map���ID���Ѵ�
	$w_uid_list = $CID_LIST;
	$CID_LIST = array();
	foreach ($w_uid_list as $w_uid) {
		if ($EMAP_CID[$w_uid] != "") {
			$CID_LIST[] = $EMAP_CID[$w_uid];
		}
	}
	$OPTION_CD = mb_strimwidth(implode(",", $CID_LIST), 0, 20, '...');
	// ����������������ѥ��å�
} else {
	foreach ($EMAP_CID as $w_cid)
		$CID_LIST[] = $w_cid;
}

require_once("kyoten_enc.inc");			// ʸ���������Ѵ�

/*==============================================*/
// API�����ǥ�����
/*==============================================*/
$KEY = f_decrypt_api_key( $KEY );
// �ǥ����ɸ��ʸ���󤬲���Ƥ�����ϥ��˽��Ϥ��ʤ�
if (!chk_sb_anmb($KEY)){
	$KEY = "";
}

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$parms = $lat;
$parms .= " " . $lon;

/*==============================================*/
// ���ϥ��饹
/*==============================================*/
// ����������������ѥ��å�
require_once("kyoten_outf_sekaicamera.inc");	// ���ϥ��饹����ʥ�����������
$CgiOut = new KyotenCgiOutputJSON($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, SEKAI_AIRTAG);
// ����������������ѥ��å�

/*==============================================*/
// �ʰ�ǧ�ڡ�IP�����å���
/*==============================================*/
$ERRCD = api_key_check( $KEY );

if ($ERRCD != "0000") {
	$status = DEF_RETCD_AERR;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}


/*==============================================*/
// �ѥ�᡼�������å�
/*==============================================*/
/* e-map���ID */
if (count($CID_LIST) == 0) {
	// ���Ĵ�Ȥʤ�
	$status = DEF_RETCD_DNE;// �����ǡ���̵��
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ¬�Ϸ� */
if ($DATUM != DATUM_TOKYO && $DATUM != DATUM_WGS84) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ʸ�������� */
if ($ENC != "SJIS" && $ENC != "EUC" && $ENC != "UTF8") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ���� */
if ($LAT == "") {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ���� */
if ($LON == "") {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* Ⱦ�� */
if (NumChk($RAD) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($RAD < 0 || $RAD > RAD_MAX) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ������ */
if (NumChk($KNSU) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($KNSU < 0 || $KNSU > KNSU_MAX) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ��������Ⱦ�¥����å� */
if ($KNSU == 0 && $RAD == 0) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($KNSU != 0 && $RAD == 0) {
	$RAD = RAD_MAX;
}
/* �������� */
if (NumChk($POS) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($POS < 1) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ������� */
if (NumChk($CNT) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($CNT < 1) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($CNT > 1000) {
	$CNT = 1000;
}
///* ɽ�����ܥѥ����� */
//if (NumChk($DTYPE) != "OK") {
//	$status = DEF_RETCD_PERR2;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
//if ($DTYPE < 1 || $DTYPE > 7) {
//	$status = DEF_RETCD_PERR2;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
///* ̤���Ϲ����ֵѻ��� */
//if ($ND != "SKIP" && $ND != "PUT") {
//	$status = DEF_RETCD_PERR2;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
/* �ݥ���ȥե饰 */
if ($PFLG != "1" && $PFLG != "2" && $PFLG != "3") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ���Ϸ��� */
//if ($OUTF != "JSON" && $OUTF != "XML") {
if ($OUTF != "JSON") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// ��ɸɽ�������ڤ�¬�ϷϤ��Ѵ�
/*==============================================*/
$res = cnv_ll2lldms($LAT, $LON, $DATUM, &$LAT, &$LON);
if (!$res) {
	// ���ٷ�������
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// DB��³�����ץ�
/*==============================================*/
$dba = new oraDBAccess();
if (!$dba->open()) {
	$dba->close();
	$status = DEF_RETCD_DERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// �����̾�ꥹ�ȼ���
/*==============================================*/
//$arr_item_list = array();
//$max_item_count = 0;
//foreach ($CID_LIST as $w_cid) {
//	$sql = "select COL_NAME,ITEM_NAME,VAL_KBN,ICON_KBN from KYOTEN_ITEM_TBL";
//	$sql .= " where CORP_ID = '".escapeOra($w_cid)."'";
//	switch ($DTYPE) {
//		case "1":
//			$sql .= " and SYOUSAI_KBN = '1'";
//			break;
//		case "2":
//			$sql .= " and INSATSU_KBN = '1'";
//			break;
//		case "3":
//			$sql .= " and FUKIDASI_KBN = '1'";
//			break;
//		case "4":
//			$sql .= " and M_SYOUSAI_KBN = '1'";
//			break;
//		case "5":
//			$sql .= " and LIST_KBN = '1'";
//			break;
//		case "6":
//			$sql .= " and OPT_04 = '1'";
//			break;
//		case "7":
//			$sql .= " and OPT_05 = '1'";
//			break;
//	}
//	$sql .= " and COL_NAME != 'NAME'";
//	$sql .= " order by DISP_NUM";
//	$stmt = null;
//	if (!$dba->sqlExecute($sql, $stmt)) {
//		$dba->free($stmt);
//		$dba->close();
//		$status = DEF_RETCD_DERR3;
//		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//		exit;
//	}
//	$arr_item_list[$w_cid] = array();
//	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
//		$arr_item_list[$w_cid][] = $data;
//	}
//	$dba->free($stmt);
//	if ($max_item_count < count($arr_item_list[$w_cid]))
//		$max_item_count = count($arr_item_list[$w_cid]);
//}
//foreach ($arr_item_list as $c => $arr_item) {
//	for ($i = 0; $i < $max_item_count; $i++) {
//		if ($arr_item[$i]['COL_NAME']) {
//			$arr_item_list[$c][$i]['COL_NAME_LBL'] = $arr_item[$i]['COL_NAME']." C$i";
//		} else {
//			$arr_item_list[$c][$i]['COL_NAME_LBL'] = "null C$i";
//		}
//	}
//}

/*==============================================*/
// �Ǵ��������
/*==============================================*/
$sql = "";
foreach ($CID_LIST as $i => $w_cid) {
	if ($i > 0) $sql .= " union all ";
	$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
	$sql .= ", power( abs( LAT - $LAT ) * (  9 / 300000 * 1000 ), 2 )";
	$sql .= " + power( abs( LON - $LON ) * ( 11 / 450000 * 1000 ), 2 ) as KYORI";
	// add 2010/01/25 Y.Matsukawa [
	$sql .= ", to_char(PUB_S_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_S_DATE";
	$sql .= ", to_char(PUB_E_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_E_DATE";
	$sql .= ", to_char(INS_DT, 'yyyy/mm/dd hh24:mi:ss') INS_DT";
	$sql .= ", to_char(UPD_DT, 'yyyy/mm/dd hh24:mi:ss') UPD_DT";
	// add 2010/01/25 Y.Matsukawa ]
	$sql .= ", NAME";
//	$arr_item = $arr_item_list[$w_cid];
//	if (is_array($arr_item) && count($arr_item) > 0) {
//		foreach ($arr_item as $item) {
//			$sql .= ", ".$item['COL_NAME_LBL'];
//		}
//	}
	$sql .= " from KYOTEN_TBL";
	$sql .= " where CORP_ID = '".escapeOra($w_cid)."'";
	if ($KYOTEN_FILTER[$w_cid]) {
		$sql .= " and ".$KYOTEN_FILTER[$w_cid];
	}
	if ($RAD) {
		$sql .= " and LAT >= (".$LAT." - ((300000 / ( 9 * 1000)) * ".$RAD."))";
		$sql .= " and LAT <= (".$LAT." + ((300000 / ( 9 * 1000)) * ".$RAD."))";
		$sql .= " and LON >= (".$LON." - ((450000 / (11 * 1000)) * ".$RAD."))";
		$sql .= " and LON <= (".$LON." + ((450000 / (11 * 1000)) * ".$RAD."))";
	}
	$sql .= " and nvl(PUB_E_DATE, sysdate) >= sysdate";
}
$sql .= " order by KYORI, KYOTEN_ID, CORP_ID";
$sql = "select s.*, rownum rn from (".$sql.") s";
if ($KNSU) {
	$sql .= " where rownum <= $KNSU";
}
// �ҥåȷ������
$hit_num = 0;
$stmt = null;
$sql_count = "select count(*) HITCNT from (".$sql.")";

if (!$dba->sqlExecute($sql_count, $stmt)) {
	$dba->free($stmt);
	$dba->close();
	$status = DEF_RETCD_DERR3;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
	$hit_num = $data['HITCNT'];
}
$dba->free($stmt);


// �ǡ�������
$rec_num = 0;
$arr_kyoten = array();
if ($hit_num > 0) {
	$sql_data = "select * from (".$sql.")";
	$sql_data .= " where rn >= ".$POS;
	$to = $POS+$CNT-1;
	$sql_data .= " and rn <= ".$to;
	$stmt = null;

	if (!$dba->sqlExecute($sql_data, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
		exit;
	}
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		if ($DATUM == DATUM_WGS84) {
			// ¬�ϷϤ��Ѵ���TOKYO=>WGS84��
			$res = cnv_transDatum($data['LAT'], $data['LON'], TKY_TO_WGS84, $w_lat, $w_lon);
			if ($res) {
				$data['LAT'] = $w_lat;
				$data['LON'] = $w_lon;
			}
		}
		// add 2010/01/25 Y.Matsukawa [
		list($w_ymd, $w_tim) = explode(' ', $data['PUB_S_DATE']);
		$data['PUB_S_DATE_YMD'] = explode('/', $w_ymd);
		$data['PUB_S_DATE_TIM'] = explode(':', $w_tim);
		// mod 2011/07/05 Y.Nakajima [
		if (isset($data['PUB_E_DATE'])) {
			list($w_ymd, $w_tim) = explode(' ', $data['PUB_E_DATE']);
		} else {
			$w_ymd = "";
			$w_tim = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$data['PUB_E_DATE_YMD'] = explode('/', $w_ymd);
		$data['PUB_E_DATE_TIM'] = explode(':', $w_tim);
		list($w_ymd, $w_tim) = explode(' ', $data['INS_DT']);
		$data['INS_DT_YMD'] = explode('/', $w_ymd);
		$data['INS_DT_TIM'] = explode(':', $w_tim);
		list($w_ymd, $w_tim) = explode(' ', $data['UPD_DT']);
		$data['UPD_DT_YMD'] = explode('/', $w_ymd);
		$data['UPD_DT_TIM'] = explode(':', $w_tim);
		// add 2010/01/25 Y.Matsukawa ]
		$arr_kyoten[] = $data;
	}
	$dba->free($stmt);
	$rec_num = count($arr_kyoten);
}
$dba->close();

if (!$rec_num) {
	// �����ǡ���̵��
	$status = DEF_RETCD_DNE;
	$CgiOut->set_status($status, 0, $hit_num); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if (($POS+$rec_num-1) < $hit_num) {
	// ��³�ǡ���ͭ��
	$status = DEF_RETCD_DEND;
} else {
	// ��³�ǡ���̵��
	$status = DEF_RETCD_DE;
}

// �ǡ�������
$CgiOut->set_status($status, $rec_num, $hit_num);
$CgiOut->set_data_arr(&$arr_kyoten);
$CgiOut->output();

// ������
put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
?>
