<?php
/*========================================================*/
// �ե�����̾��lw_listadcd.cgi
// ����̾���ڥ���������������ޥ����۽���ꥹ�ȸ���
//
// ��������
// 2010/12/20 H.Osamoto	��������
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/11/28 H.Osamoto	�������Զ�罤��
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
$APICGINM = "listadcd.cgi";

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
$KEY		= $D_CGI_KEY;
$POS		= getCgiParameter('pos','1');			/* �������� */
$CNT		= getCgiParameter('cnt','100');			/* ������� */
$ENC		= getCgiParameter('enc','SJIS');		/* ʸ�������� (OUT) */
$SORT		= getCgiParameter('sort','1');			/* �����Ƚ� */
$SEP		= getCgiParameter('sep','0');			/* ������ڤ� */
$ADCD		= getCgiParameter('adcd','');			/* ���ꥳ���� */
$PFLG		= getCgiParameter('pflg','2');			/* �ݥ���ȥե饰 */
$DATUM		= getCgiParameter('datum','TOKYO');		/* ¬�Ϸ� */
$OUTF		= getCgiParameter('outf','TSV');		/* ���Ϸ��� */

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
$parms .= '&pos='.$POS;
$parms .= '&cnt='.$CNT;
$parms .= '&enc='.$ENC;
$parms .= '&sort='.$SORT;
$parms .= '&sep='.$SEP;
$parms .= '&adcd='.$ADCD;
$parms .= '&pflg='.$PFLG;
$parms .= '&datum='.$DATUM;
$parms .= '&outf='.$OUTF;

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$log_parms = 'POS:'.$POS;
$log_parms .= ' CNT:'.$CNT;
$log_parms .= ' ENC:'.$ENC;
$log_parms .= ' SORT:'.$SORT;
$log_parms .= ' SEP:'.$SEP;
$log_parms .= ' ADCD:'.$ADCD;
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
		header("Content-Type: zdc-api/listadcd");
		echo $result;
}

exit;

?>
