<?php
/*========================================================*/
// �ե�����̾��ytc_getadstr.cgi
// ����̾���ڥ�ޥȱ�͢�͸����������ޥ����۽���հ�������
//
// ��������
// 2013/07/16 Y.Arai		��������
// 2013/08/06 Y.Matsukawa	���������Ƥ�Ĵ��
/*========================================================*/
extract($_GET);

/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = 'y01';

/*==============================================*/
// CGI̾
/*==============================================*/
$APICGINM = "getadstr_gik.cgi";

/*==============================================*/
// �꥿���󥳡������
/*==============================================*/
define( 'DEF_RETCD_DE',   '00000' );       //���˸��礦�ǡ�������
define( 'DEF_RETCD_DNE',  '11009' );       //���˸��礦�ǡ����ʤ�
define( 'DEF_RETCD_AERR', '12009' );       //ǧ�ڥ��顼
define( 'DEF_RETCD_PERR1','19100' );       //���ϥѥ�᡼�����顼��ɬ�ܥѥ�᡼����̤�����
define( 'DEF_RETCD_PERR2','19200' );       //���ϥѥ�᡼�����顼�ʥѥ�᡼�������ͤ�������

/*==============================================*/
// ����ե�����
/*==============================================*/
require_once('ytc_def.inc');			// ��ޥȱ�͢�����
require_once('ytc_cgi_key.inc');		// ��ޥȱ�͢��emapCGI����¾
require_once('function.inc');			// ���̴ؿ�
require_once('log.inc');				// ������
require_once('auth.inc');				// �ʰ�ǧ��

/*==============================================*/
//�����ϳ���
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// �����
/*==============================================*/
$status 	= DEF_RETCD_DE;		// ���ѥ��ơ����������ɡ�������
$emap_cid	= $D_CID;			// ��ȥ����ɸ��ꡡytc_def.inc�����
$rescode	= "-1";				// �쥹�ݥ󥹥����ɽ���͡ʥ��顼��
$errcode	= "";				// ���顼�����ɽ����
$outdata	= "";				// ���Ϸ�̽����
//$log_parms	= $dms." ".$sid;	// ��������ʸ����ʥѥ�᡼����	mod 2013/08/06 Y.Matsukawa
$log_parms	= mb_ereg_replace(' ', '_', $dms);
$log_parms	.= ' ';
$log_parms	.= mb_ereg_replace(' ', '_', $sid);
$KEY		= $D_CGI_KEY;		// CGI�ѥ���

/*==============================================*/
// �ʰ�ǧ�ڡ�IP�����å���HTTPS�̿������å���
/*==============================================*/
// IP�����å�
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	put_log($CGICD.DEF_RETCD_AERR, $KEY, $emap_cid, $log_parms);
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=Shift_JIS");
	echo mb_convert_encoding("���������ϵ��Ĥ���Ƥ��ޤ���:IP���ɥ쥹�����ݤ���ޤ�����", "SJIS", "EUC-JP");
	exit;
}

// HTTPS�̿������å�
if($_SERVER['HTTPS'] != 'on') {
	put_log($CGICD.DEF_RETCD_AERR, $KEY, $emap_cid, $log_parms);
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=Shift_JIS");
	echo mb_convert_encoding("���������ϵ��Ĥ���Ƥ��ޤ���:SSL��ɬ�פǤ���", "SJIS", "EUC-JP");
	exit;
}

/*==============================================*/
// �ѥ�᡼�������å�
/*==============================================*/
// �ꥯ������
if ($_SERVER['REQUEST_METHOD'] != "GET") {
	outputErrStatus( $rescode, "ERR0003", "�ꥯ��������ˡ�������Ǥ���" );
	put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
	exit;
}

// ���ٷ���[dms]
if ($dms == "") {
	outputErrStatus( $rescode, "ERR0001", "ɬ�ܥѥ�᥿�����ꤵ��Ƥ��ޤ���[dms]" );
	put_log($CGICD.DEF_RETCD_PERR1, $KEY, $emap_cid, $log_parms);
	exit;
} else {
	// �ե����ޥåȥ����å���Eddd.mm.ss.sNdd.mm.ss.s��
	if (preg_match("/^E([0-9]{3})\.([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{1})N([0-9]{2})\.([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{1})$/s",$dms) !== 1) {
		outputErrStatus( $rescode, "ERR0002", "ɬ�ܥѥ�᥿�������Ǥ���[dms]");
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}
	$dms_arr = explode("N", $dms);
	$lon = str_replace("E", "", $dms_arr[0]);
	$lat = $dms_arr[1];
	
	// �ϰϥ����å������120�١�160�١��̰�20�١�60�٤��ϰϡ�
	$lon_arr = explode(".", $lon);
	$lat_arr = explode(".", $lat);
	if ($lon_arr[0] < 120 || $lon_arr[0] > 160 || $lat_arr[0] < 20 || $lat_arr[0] > 60) {
		outputErrStatus( $rescode, "ERR0002", "ɬ�ܥѥ�᥿�������Ǥ���[dms]");
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}
}

// �����ӥ�ID[sid]
if ($sid == "") {
	outputErrStatus( $rescode, "ERR0001", "ɬ�ܥѥ�᥿�����ꤵ��Ƥ��ޤ���[sid]" );
	put_log($CGICD.DEF_RETCD_PERR1, $KEY, $emap_cid, $log_parms);
	exit;
} else {
	if ($sid != "ytc" && $sid != "ysd") {
		outputErrStatus( $rescode, "ERR0002", "ɬ�ܥѥ�᥿�������Ǥ���[sid]" );
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}
}

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$LAT		= getCgiParameter('lat', $lat);			/* ���� */
$LON		= getCgiParameter('lon', $lon);			/* ���� */
$MCLV		= getCgiParameter('mclv','3');			/* �ޥå��󥰥�٥�ʻ����ܤޤǡ� */
$ENC		= getCgiParameter('enc','SJIS');		/* ʸ�������� (OUT) */
$SEP		= getCgiParameter('sep','1');			/* ������ڤ�ʤ���� */
$PFLG		= getCgiParameter('pflg','3');			/* �ݥ���ȥե饰����ʬ�á� */
$DATUM		= getCgiParameter('datum','WGS84');		/* ¬�Ϸϡ�����¬�Ϸϡ� */
$OUTF		= getCgiParameter('outf','TSV');		/* ���Ϸ��� */

/*==============================================*/
// �¹��Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$parms =  '?key='.	$KEY;
$parms .= '&lat='.	$LAT;
$parms .= '&lon='.	$LON;
$parms .= '&mclv='.	$MCLV;
//$parms .= '&enc='.	$ENC;		mod 2013/08/21 Y.Matsukawa
$parms .= '&enc=EUC';
$parms .= '&sep='.	$SEP;
$parms .= '&pflg='.	$PFLG;
$parms .= '&datum='.$DATUM;
$parms .= '&outf='.	$OUTF;

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
// del 2013/08/06 Y.Matsukawa [
//$log_parms = 'KEY:'.	$KEY;
//$log_parms .= ' LAT:'.	$LAT;
//$log_parms .= ' LON:'.	$LON;
//$log_parms .= ' MCLV:'.	$MCLV;
//$log_parms .= ' ENC:'.	$ENC;
//$log_parms .= ' SEP:'.	$SEP;
//$log_parms .= ' PFLG:'.	$PFLG;
//$log_parms .= ' DATUM:'.$DATUM;
//$log_parms .= ' OUTF:'.	$OUTF;
// del 2013/08/06 Y.Matsukawa ]
// add 2013/08/06 Y.Matsukawa [
$log_parms .= ' ';
$log_parms .= $LAT;
$log_parms .= ' ';
$log_parms .= $LON;
// add 2013/08/06 Y.Matsukawa ]

/*==============================================*/
// ����հ�������CGI������
/*==============================================*/
unset($result);
$CGI = 'http://'.$API_SSAPI_SRV.'/ssapi/'.$APICGINM.$parms;
$result = file_get_contents($CGI);

if (!$result) {
	outputErrStatus( $rescode, "ERR1002", "�̿����顼�Τ��ᡢ����ʸ����μ����˼��Ԥ��ޤ�����" );
	put_log($CGICD.DEF_RETCD_DNE, $KEY, $emap_cid, $log_parms);
	exit;
}

// ����
$res_arr = explode("\n", $result);
$statcd = explode("\t", $res_arr[0]);

if ($statcd[0] == "21600000" || $statcd[0] == "21600001") {
// �����
	$rescode = "0";
	$add_arr = explode("\t", $res_arr[1]);
	// ������ڤ��|�����ѥ��ڡ������Ѵ�
	//$outdata = str_replace("|", mb_convert_encoding("��", "SJIS", "EUC-JP"), $add_arr[1]);		del 2013/08/21 Y.Matsukawa
	// add 2013/08/21 Y.Matsukawa [
	$add = explode('|', $add_arr[1]);
	//$add[count($add)-1] = mb_ereg_replace('����', '', $add[count($add)-1]);		del 2013/08/22 Y.Matsukawa
	//$outdata = mb_convert_encoding(implode('��', $add), 'SJIS', 'EUC-JP');		del 2013/08/22 Y.Matsukawa
	// add 2013/08/22 Y.Matsukawa [
	$add_last = '';
	if (strpos($add[count($add)-1], '����')) {
		$add_last = array_pop(&$add);
		$add_last = mb_ereg_replace('����', '', $add_last);
	}
	$outdata = implode('��', $add).$add_last;
	$outdata = mb_convert_encoding($outdata, 'SJIS', 'EUC-JP');
	// add 2013/08/22 Y.Matsukawa ]
	// add 2013/08/21 Y.Matsukawa ]

} else {
// ���顼�ֵѻ���
	if ($statcd[0] == "21611009") {		// ���˸��礦�ǡ����ʤ�
		outputErrStatus( $rescode, "ERR1001", "����ʸ���󤬼����Ǥ��ʤ�����Ǥ���" );
	} else {		// ����¾�Υ��顼
		outputErrStatus( $rescode, "ERR1003", "����¾�Υ��顼�Τ��ᡢ����ʸ����μ����˼��Ԥ��ޤ�����");
	}
	put_log($CGICD.DEF_RETCD_DNE, $KEY, $emap_cid, $log_parms);
	exit;
}

// ������
put_log($CGICD.$status, $KEY,$emap_cid, $log_parms);

// ��̽���
header ("Content-Type: text/plain; charset=Shift_JIS");
echo $rescode.",".$outdata;
exit;

/*==============================================*/
// ���顼���ν���
/*==============================================*/
function outputErrStatus( $rescode, $errcode, $outdata ) {
	header("Content-Type: text/plain; charset=Shift_JIS");
	print $rescode.",".$errcode.":".mb_convert_encoding($outdata, "SJIS", "EUC-JP");
	return true;
}

?>
