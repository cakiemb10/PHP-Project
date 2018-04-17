<?php
/*========================================================*/
// �ե�����̾��lw_searchpoi.cgi
// ����̾���ڥ���������������ޥ����ۻ��߸���
//
// ��������
// 2010/12/21 H.Osamoto	��������
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/11/28 H.Osamoto	�������Զ�罤��
// 2012/10/17 Y.Matsukawa	error_reporting()���
// 2012/11/21 K.Masuda		UTF-8��FREWDʸ�������Զ���б��ʡ���ܡסֻ��פʤɡ�
// 2015/10/29 H.Osamoto		�����оݥ����뤫����㤤ʪ(00140)�פ����
/*========================================================*/

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off�б�
//���ϥѥ�᡼���������������ɲ�
//get
extract($_GET);

/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = 'w04';

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));
$APICGINM = "searchpoi.cgi";

/*==============================================*/
// �꥿���󥳡������
/*==============================================*/
define( 'DEF_RETCD_AERR', '12009' );       //ǧ�ڥ��顼

/*==============================================*/
// ����ե�����
/*==============================================*/
require_once('lw_def.inc');				// �����������
require_once('function.inc');			// ���̴ؿ�
require_once('log.inc');				// ������
require_once('auth.inc');				// �ʰ�ǧ��
require_once('cgi_key.inc');			// emapCGI����¾

/*==============================================*/
// ���顼���Ϥ�����Ū��OFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
//error_reporting(0);		del 2012/10/17 Y.Matsukawa

/*==============================================*/
//�����ϳ���
/*==============================================*/
include('logs/inc/com_log_open.inc');

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// �����
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
if (!isset($status)) $status = 00000;
$emap_cid = $D_CID;    //��ȥ����ɸ��ꡡlw_def.inc�����
// add 2011/09/29 Y.Nakajima ]


/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$KEY		= $D_CGI_KEY;							/* CGI���� */
$CID		= getCgiParameter('cid','');			/* ���ID */
$SID		= getCgiParameter('sid','');			/* �����ӥ�ID */
$POS		= getCgiParameter('pos','1');			/* �������� */
$CNT		= getCgiParameter('cnt','100');			/* ������� */
$ENC		= getCgiParameter('enc','SJIS');		/* ʸ�������� (OUT) */
$TOD		= getCgiParameter('tod','00');			/* ��ƻ�ܸ������� */
$SHK		= getCgiParameter('shk','000');			/* �Զ�Į¼������ */
$JNRNM		= getCgiParameter('jnrmn','');			/* �������˥塼������ */
$JNR		= getCgiParameter('jnr','');			/* �����륳���� */
$SRCHMODE	= getCgiParameter('srchmode','0');		/* �����⡼�� */
$SRCHTARGET	= getCgiParameter('srchtarget','0');	/* �ե꡼��ɸ����о� */
$SRCHTYPE	= getCgiParameter('srchtype','0');		/* ������ɷ���� */
$FREWD		= getCgiParameter('frewd','');			/* �ե꡼��� */
$PFLG		= getCgiParameter('pflg','2');			/* �ݥ���ȥե饰 */
$DATUM		= getCgiParameter('datum','TOKYO');		/* ¬�Ϸ� */
$OUTF		= getCgiParameter('outf','TSV');		/* ���Ϸ��� */

// add 2015/10/29 H.Osamoto [
// ���㤤ʪ(00140)�װʳ��򤹤٤Ƥ����ǻ���
$JNRNM = "00110,00120,00130,00160,00170,00220,00240,00250";
// add 2015/10/29 H.Osamoto ]

/*==============================================*/
// �ե꡼��ɥ��󥳡���
/*==============================================*/
switch ($ENC) {
	case "EUC":
		$frewd_org = mb_convert_encoding($FREWD, "EUC-JP", "EUC-JP, UTF-8, SJIS, auto");
		$FREWD = urlencode($frewd_org);
		break;
	case "SJIS":
		$frewd_org = mb_convert_encoding($FREWD, "SJIS", "EUC-JP, UTF-8, SJIS, auto");
		$FREWD = urlencode($frewd_org);
		break;
	case "UTF8":
		//$frewd_org = mb_convert_encoding($FREWD, "UTF-8", "EUC-JP, UTF-8, SJIS, auto");	// mod 2012/11/21 K.Masuda
		$frewd_org = mb_convert_encoding($FREWD, "UTF-8", "auto");
		$FREWD = urlencode($frewd_org);
		break;
	default:
		$frewd_org = mb_convert_encoding($FREWD, "SJIS", "EUC-JP, UTF-8, SJIS, auto");
		$FREWD = urlencode($frewd_org);
	break;
}


/*==============================================*/
// �ʰ�ǧ�ڡ�IP�����å�����ե�������å���
/*==============================================*/
//if (!ip_check($D_IP_LIST, "218.225.89.14")) {
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	if (!referer_check(&$D_REFERER_LIST, $_SERVER['HTTP_REFERER'])) {
		$status = DEF_RETCD_AERR;
		$KEY = '';		/* ��������ˤ��ưտ�Ū��ǧ�ڥ��顼�ˤ����� */ 
		// mod 2011/09/29 Y.Nakajima
		//put_log($CGICD.$status, $parms);
		put_log($CGICD.$status, $KEY,$emap_cid,$status);
	}
}

/*==============================================*/
// �¹��Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$parms =  '?key='.$KEY;
$parms .= '&cid='.$CID;
$parms .= '&sid='.$SID;
$parms .= '&pos='.$POS;
$parms .= '&cnt='.$CNT;
$parms .= '&enc='.$ENC;
$parms .= '&tod='.$TOD;
$parms .= '&shk='.$SHK;
$parms .= '&jnrmn='.$JNRNM;
$parms .= '&jnr='.$JNR;
$parms .= '&srchmode='.$SRCHMODE;
$parms .= '&srchtarget='.$SRCHTARGET;
$parms .= '&srchtype='.$SRCHTYPE;
$parms .= '&frewd='.$FREWD;
$parms .= '&pflg='.$PFLG;
$parms .= '&datum='.$DATUM;
$parms .= '&outf='.$OUTF;

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
// mod 2011/11/28 H.Osamoto [
//	$log_parms  = 'KEY:'.$KEY;
//	$log_parms .= ' CID:'.$CID;
$log_parms  = 'CID:'.$CID;
// mod 2011/11/28 H.Osamoto ]
$log_parms .= ' POS:'.$POS;
$log_parms .= ' CNT:'.$CNT;
$log_parms .= ' ENC:'.$ENC;
$log_parms .= ' TOD:'.$TOD;
$log_parms .= ' SHK:'.$SHK;
$log_parms .= ' JNRNM:'.$JNRNM;
$log_parms .= ' JNR:'.$JNR;
$log_parms .= ' SRCHMODE:'.$SRCHMODE;
$log_parms .= ' SRCHTARGET:'.$SRCHTARGET;
$log_parms .= ' SRCHTYPE:'.$SRCHTYPE;
//$log_parms .= ' FREWD:'.$FREWD;	// mod 2011/11/28 H.osamoto
$log_parms .= mb_strimwidth(' FREWD:'.$FREWD, 0, 255, '...');
$log_parms .= ' PFLG:'.$PFLG;
$log_parms .= ' DATUM:'.$DATUM;
$log_parms .= ' OUTF:'.$OUTF;


unset($result);
$CGI = 'http://'.$API_SSAPI_SRV.'/ssapi/'.$APICGINM.$parms;

// e-mapCGI
$result = file_get_contents($CGI);
// ������
// mod 2011/09/29 Y.Nakajima
//put_log($CGICD.$status, $parms);
//put_log($CGICD.$status, $KEY,$emap_cid, $parms);	// mod 2011/11/28 H.Osamoto
put_log($CGICD.$status, $KEY,$emap_cid, $log_parms);

switch ($OUTF) {
	case 'XML':
		// XML����
		header ("Content-Type: text/xml; charset=$ENC");
		echo $result;
		break;
	default:
		// TSV����
		header("Content-Type: zdc-api/searchpoi");
		echo $result;
}

exit;

?>
