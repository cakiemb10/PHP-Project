<?php
/*========================================================*/
// �ե�����̾��lw_idkyoten.cgi
// ����̾���ڥ���������������ޥ����۵���ID����
//
// ��������
// 2011/09/09 K.Masuda		��������
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/01/26 K.Masuda		NEWɽ��(����/��λ)�������ɲ�
// 2012/10/17 Y.Matsukawa	error_reporting()���
/*========================================================*/

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off�б�
//���ϥѥ�᡼���������������ɲ�
//get
extract($_GET);

/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = 'w03';

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// �꥿���󥳡������
/*==============================================*/
define( 'DEF_RETCD_DE',   '00000' );       //���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
define( 'DEF_RETCD_DEND', '00001' );       //���˸��礦�ǡ�������ʸ�³�ǡ��������
define( 'DEF_RETCD_DNE',  '11009' );       //���˸��礦�ǡ����ʤ�
define( 'DEF_RETCD_AERR', '12009' );       //ǧ�ڥ��顼
define( 'DEF_RETCD_DERR1','17900' );       //�ǡ����١��������������顼
define( 'DEF_RETCD_DERR2','17002' );       //�ǡ����١��������������顼
define( 'DEF_RETCD_DERR3','17999' );       //�ǡ����١��������������顼
define( 'DEF_RETCD_PERR1','19100' );       //���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
define( 'DEF_RETCD_PERR2','19200' );       //���ϥѥ�᡼�����顼(��ʸ���顼)
define( 'DEF_RETCD_PERR3','19200' );       //���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)
// add 2011/07/05 Y.Nakajima 
require_once('cgi_key.inc');			// emapCGI����¾($D_CGI_KEY)


/*==============================================*/
// ����ե�����
/*==============================================*/
require_once('lw_outf.inc');			// ���ϥ��饹����ʥ������ѡ�
require_once('ZdcCommonFuncAPI.inc');	// ���̴ؿ�
require_once('function.inc');			// ���̴ؿ�
require_once('d_serv_ora.inc');
require_once('oraDBAccess.inc');
require_once('chk.inc');				// �ǡ��������å���Ϣ
require_once('log.inc');				// ������
require_once('auth.inc');				// �ʰ�ǧ��
require_once("jkn.inc");				// �ʤ���߾���Խ�
require_once('lw_def.inc');				// �����������

/*==============================================*/
// ���顼���Ϥ�����Ū��OFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
//error_reporting(0);		del 2012/10/17 Y.Matsukawa

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// �����
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
if (!isset($status)) $status = 00000;
if (!isset($params)) $params = "";
if (!isset($PFLG)) $PFLG = "";
$emap_cid = $D_CID;    //��ȥ����ɸ��ꡡlw_def.inc�����
// add 2011/09/29 Y.Nakajima ]


/*==============================================*/
//�����ϳ���
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$CID		= $D_CID;								/* e-map���ID */
$KEY		= $D_CGI_KEY;
$ID			= getCgiParameter('id','');				/* ����ID */
$OUTF		= getCgiParameter('outf','JSON');		/* ���Ϸ��� */
$ENC		= getCgiParameter('enc','UTF8');		/* ʸ�������� */

$OPTION_CD = $CID;

require_once('lw_enc.inc');			// ʸ���������Ѵ�

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$parms = $ID;

/*==============================================*/
// ���ϥ��饹
/*==============================================*/
require_once('lw_outf_json.inc');		// ���ϥ��饹����ʥ������
require_once('lw_outf_xml.inc');		// ���ϥ��饹����ʥ������
switch ($OUTF) {
	case 'XML':
		$CgiOut = new KyotenCgiOutputXML($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG);
		break;
	default:
		$CgiOut = new KyotenCgiOutputJSON($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG);
}

/*==============================================*/
// �ʰ�ǧ�ڡ�IP�����å�����ե�������å���
/*==============================================*/
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	if (!referer_check(&$D_REFERER_LIST, $_SERVER['HTTP_REFERER'])) {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
		exit;
	}
}

/*==============================================*/
// �ѥ�᡼�������å�
/*==============================================*/
/* e-map���ID */
if ($CID == '') {
	// ���Ĵ�Ȥʤ�
	$status = DEF_RETCD_DNE;// �����ǡ���̵��
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ʸ�������� */
if ($ENC != 'SJIS' && $ENC != 'EUC' && $ENC != 'UTF8') {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ����ID */
if ($ID == '') {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* ���Ϸ��� */
if ($OUTF != 'JSON' && $OUTF != 'XML') {
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
$arr_item = array();
$sql = "select COL_NAME,ITEM_NAME,VAL_KBN from KYOTEN_ITEM_TBL";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " order by DISP_NUM";
$stmt = null;
if (!$dba->sqlExecute($sql, $stmt)) {
	$dba->free($stmt);
	$dba->close();
	$status = DEF_RETCD_DERR3;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
$arr_item = array();
while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
	$arr_item[] = $data;
}
$dba->free($stmt);

/*==============================================*/
// ��ʬ���ܤ�̾�μ���
/*==============================================*/
$arr_kbn = array();
if (count($arr_item) > 0) {
	foreach ($arr_item as $item) {
		if ($item['VAL_KBN'] == 'L') {
			$sql_kbn = "select ITEM_VAL, ITEM_VAL_NAME from KYOTEN_ITEM_VAL_TBL";
			$sql_kbn .= " where CORP_ID = '".escapeOra($CID)."'";
			$sql_kbn .= " and COL_NAME = '".$item['COL_NAME']."'";
			$sql_kbn .= " order by ITEM_VAL";
			if (!$dba->sqlExecute($sql_kbn, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_status($status, 0, 0); $CgiOut->output();
				put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
				exit;
			}
			$arr_kbn[$item['COL_NAME']] = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
			}
			$dba->free($stmt);
		}
	}
}

/*==============================================*/
// ����ID����
/*==============================================*/
$sql = "";
$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON from KYOTEN_TBL";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " and KYOTEN_ID = '".escapeOra($ID)."'";
$sql .= " and NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE";  // add 2013/07/25 F.Yokoi
$sql = "select s.*, rownum rn from (".$sql.") s";
// �ҥåȷ������
$hit_num = 0;
$stmt = null;
$sql_count = "select count(*) HITCNT from (".$sql.")";
if($D_DEBUG) error_log("$sql_count\n", 3, "/var/tmp/lwcgi.".date('Ymd').".debug.log");
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
	// mod 2012/01/26 K.Masuda [
	//$sql_data = "select * from KYOTEN_TBL";
	$sql_data = "select CORP_ID, KYOTEN_ID, LAT, LON";
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			$sql_data .= ", ".$item['COL_NAME'];
		}
	}
	$sql_data .= " , TO_CHAR(DISP_NEW_S_DATE,'yyyymmddhh24') as DISP_NEW_S_DATE, TO_CHAR(DISP_NEW_E_DATE,'yyyymmddhh24') as DISP_NEW_E_DATE ";
	$sql_data .= " from KYOTEN_TBL";
	// mod 2012/01/26 K.Masuda ]
	$sql_data .= " where CORP_ID = '".escapeOra($CID)."'";
	$sql_data .= " and KYOTEN_ID = '".escapeOra($ID)."'";
	$sql_data .= " and NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE"; // add 2013/07/25 F.Yokoi
	$stmt = null;
if($D_DEBUG) error_log("$sql_data\n", 3, "/var/tmp/lwcgi.".date('Ymd').".debug.log");
	if (!$dba->sqlExecute($sql_data, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
		exit;
	}
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		// ��ʬ���ܤ�̾�Τ򥻥å�
		if (count($arr_item) > 0) {
			foreach ($arr_item as $item) {
				if ($item['VAL_KBN'] == 'L') {
					$colnm = $item['COL_NAME'];
					// mod 2011/09/29 Y.Nakajima [
					if (isset($data[$colnm])) {
						$val = $data[$colnm];
						if ($val != '') {
							if ($arr_kbn[$colnm][$val] != '') {
								$data[$colnm.'_name'] = $arr_kbn[$colnm][$val];
							}
						}
					}
					// mod 2011/09/29 Y.Nakajima ]
				}
			}
		}
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

// ��³�ǡ���̵��
$status = DEF_RETCD_DE;

// �ǡ�������
$CgiOut->set_status($status, $rec_num, $hit_num);
$CgiOut->set_data_arr(&$arr_kyoten);
$CgiOut->output();

// ������
put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
?>
