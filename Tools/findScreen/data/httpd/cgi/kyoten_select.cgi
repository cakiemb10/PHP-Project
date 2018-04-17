<?php
/*========================================================*/
// �ե�����̾��kyoten_select.cgi
// ����̾������ID����
//
// ��������2010/01/08
// �����ԡ�Y.Matsukawa
//
// ���⡧����ID�������ꡢ�����������������������
//
// ��������
// 2010/01/08 Y.Matsukawa	��������
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/10/17 Y.Matsukawa	error_reporting()���
/*========================================================*/
/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = "k01";

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

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// �����
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
// add 2011/09/29 Y.Nakajima ]

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$KEY		= getCgiParameter("key","");			/* ǧ�ڥ��� */
$CID		= getCgiParameter("cid","");			/* e-map���ID */
$KID		= getCgiParameter("kid","");			/* ����ID */
$PFLG		= getCgiParameter("pflg","2");			/* �ݥ���ȥե饰 */
$DATUM		= getCgiParameter("datum",DATUM_TOKYO);	/* ¬�Ϸ� */
$OUTF		= getCgiParameter("outf","JSON");		/* ���Ϸ��� */
$ENC		= getCgiParameter("enc","SJIS");		/* ʸ�������� */
//$DTYPE		= getCgiParameter("dtype","6");			/* ɽ�����ܥѥ����� */
//$ND			= getCgiParameter("nd","SKIP");			/* ̤���Ϲ����ֵѻ��� */

$OPTION_CD = mb_strimwidth($CID, 0, 20, '...');

// ����������������ѥ��å�
// �����������ID��e-map���ID���Ѵ�
if ($CID != "") {
	$UID = $CID;
	$OPTION_CD = $EMAP_CID[$CID];
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
$CgiOut = new KyotenCgiOutputJSON($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, SEKAI_DTLTAG);
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
if (strlen($CID) == 0) {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// ����������������ѥ��å�
$CID = $EMAP_CID[$CID];
// ����������������ѥ��å�
if (!in_array($CID, $EMAP_CID)) {
	// ���Ĥ���Ƥ��ʤ����ID
	$status = DEF_RETCD_DNE;// �����ǡ���̵��
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ����ID */
if (strlen($KID) == 0) {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// ��������������ID��e-map����ID���Ѵ�
$KID = sekaiId2KyotenId($UID, $KID);
if (strlen($KID) == 0) {
	// �Ѵ����ԡ��������ե����ޥåȤǤʤ���
	$status = DEF_RETCD_DNE;// �����ǡ���̵��
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// ����������������ѥ��å�
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
/* ʸ�������� */
if ($ENC != "SJIS" && $ENC != "EUC" && $ENC != "UTF8") {
	$status = DEF_RETCD_PERR2;
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
//$sql = "select COL_NAME,ITEM_NAME,VAL_KBN,ICON_KBN from KYOTEN_ITEM_TBL";
//$sql .= " where CORP_ID = '".escapeOra($CID)."'";
//switch ($DTYPE) {
//	case "1":
//		$sql .= " and SYOUSAI_KBN = '1'";
//		break;
//	case "2":
//		$sql .= " and INSATSU_KBN = '1'";
//		break;
//	case "3":
//		$sql .= " and FUKIDASI_KBN = '1'";
//		break;
//	case "4":
//		$sql .= " and M_SYOUSAI_KBN = '1'";
//		break;
//	case "5":
//		$sql .= " and LIST_KBN = '1'";
//		break;
//	case "6":
//		$sql .= " and OPT_04 = '1'";
//		break;
//	case "7":
//		$sql .= " and OPT_05 = '1'";
//		break;
//}
//$sql .= " and COL_NAME != 'NAME'";
//$sql .= " order by DISP_NUM";
//$stmt = null;
//if (!$dba->sqlExecute($sql, $stmt)) {
//	$dba->free($stmt);
//	$dba->close();
//	$status = DEF_RETCD_DERR3;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
//$arr_item = array();
//$i = 0;
//while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
//	$data['COL_NAME_LBL'] = $data['COL_NAME']." C$i";
//	$arr_item[] = $data;
//}
//$dba->free($stmt);

$arr_item = $KYOTEN_ITEM[$CID];
/*==============================================*/
// �Ǵ��������
/*==============================================*/
$sql = "";
$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
$sql .= ", to_char(PUB_S_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_S_DATE";
$sql .= ", to_char(PUB_E_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_E_DATE";
$sql .= ", to_char(INS_DT, 'yyyy/mm/dd hh24:mi:ss') INS_DT";
$sql .= ", to_char(UPD_DT, 'yyyy/mm/dd hh24:mi:ss') UPD_DT";
$sql .= ", NAME";
if (is_array($arr_item) && count($arr_item) > 0) {
	foreach ($arr_item as $item) {
		$sql .= ", ".$item['COL_NAME_LBL'];
	}
}
$sql .= " from KYOTEN_TBL";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " and KYOTEN_ID = '".escapeOra($KID)."'";
if ($KYOTEN_FILTER[$CID]) {
	$sql .= " and ".$KYOTEN_FILTER[$CID];
}
$sql .= " and nvl(PUB_E_DATE, sysdate) >= sysdate";
// �ǡ�������
$rec_num = 0;
$arr_kyoten = array();
$stmt = null;
if (!$dba->sqlExecute($sql, $stmt)) {
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

	list($w_ymd, $w_tim) = explode(' ', $data['PUB_S_DATE']);
	$data['PUB_S_DATE_YMD'] = explode('/', $w_ymd);
	$data['PUB_S_DATE_TIM'] = explode(':', $w_tim);
	// mod 2011/07/05 Y.Nakajima [
	//list($w_ymd, $w_tim) = explode(' ', $data['PUB_E_DATE']);
	if (isset($data['PUB_E_DATE'])) {
		list($w_ymd, $w_tim) = explode(' ', $data['PUB_E_DATE']);
	} else {
		$w_ymd = "";
		$w_tim = "";
	}
	$data['PUB_E_DATE_YMD'] = explode('/', $w_ymd);
	$data['PUB_E_DATE_TIM'] = explode(':', $w_tim);
	list($w_ymd, $w_tim) = explode(' ', $data['INS_DT']);
	$data['INS_DT_YMD'] = explode('/', $w_ymd);
	$data['INS_DT_TIM'] = explode(':', $w_tim);
	list($w_ymd, $w_tim) = explode(' ', $data['UPD_DT']);
	$data['UPD_DT_YMD'] = explode('/', $w_ymd);
	$data['UPD_DT_TIM'] = explode(':', $w_tim);
	$arr_kyoten[] = $data;
}
$dba->free($stmt);
$dba->close();

$hit_num = count($arr_kyoten);
$rec_num = count($arr_kyoten);
if (!$rec_num) {
	// �����ǡ���̵��
	$status = DEF_RETCD_DNE;
	$CgiOut->set_status($status, 0, $hit_num); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// ��³�ǡ���̵��
$status = DEF_RETCD_DE;

// �ǡ�������
$CgiOut->set_status($status, $rec_num, $hit_num);
$CgiOut->set_data_arr(&$arr_kyoten);
$CgiOut->output();

// ������
put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
?>
