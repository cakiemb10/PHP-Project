<?php
/*========================================================*/
// �ե�����̾��poi_search.cgi
// ����̾�������å�����-POI����(��åѡ�CGI��
//
// ��������
// 2012/12/12 H.Iijima	��������
// 
// 
/*========================================================*/
//get
extract($_GET);

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));


$APICGINM = $CGINM;
/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = $CGINM;



/*==============================================*/
// ����ե�����
/*==============================================*/
require_once('aplia_def.inc');			// ��������ե�����
require_once('function.inc');			// ���̴ؿ�
//require_once('log.inc');				// ������

/*==============================================*/
// ���顼���Ϥ�����Ū��OFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
error_reporting(E_ALL);
//error_reporting(0);

/*==============================================*/
//�����ϳ���
/*==============================================*/
//include('logs/inc/com_log_open.inc');

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$SID		= getCgiParameter('sid','');		/* ��������̾ */
$CK			= getCgiParameter('ck','');			/* ����ƥ�Ķ�ʬ */
$LATLON		= getCgiParameter('latlon','');		/* ���ٷ��� */
$FREEWD		= getCgiParameter('freewd','');		/* �ե꡼��� */
$RAD		= getCgiParameter('rad','');		/* Ⱦ�� */
$SORT		= getCgiParameter('sort','');		/* ������ */
$POS		= getCgiParameter('pos','');		/* �������� */
$CNT		= getCgiParameter('cnt','');		/* ������� */


/*==============================================*/
// �¹��Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$parms = '?sid='.$SID;
$parms .= '&ck='.$CK;
$parms .= '&latlon='.$LATLON;
$parms .= '&freewd='.$FREEWD;
$parms .= '&rad='.$RAD;
$parms .= '&sort='.$SORT;
$parms .= '&pos='.$POS;
$parms .= '&cnt='.$CNT;

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
/*
$log_parms  = ' SID:'.$SID;
$log_parms .= ' CK:'.$CK;
$log_parms .= ' LATLON:'.$LATLON;
$log_parms .=  mb_strimwidth(' FREEWD:'.mb_convert_encoding($FREEWD,'EUC-JP','auto'), 0, 255, '...');
$log_parms .= ' RAD:'.$RAD;
$log_parms .= ' SORT:'.$SORT;
$log_parms .= ' POS:'.$POS;
$log_parms .= ' CNT:'.$CNT;
*/
/*==============================================*/
// APLIA CGI �ƤӽФ�
/*==============================================*/

unset($result);
$CGIURL ='http://'.$API_APLIA_SRV.$API_APLIA_PATH;
$CGI = $CGIURL.$APICGINM.$parms;
$result = file_get_contents($CGI);

// ������
//put_log($CGICD, $SID,$http_response_header[0]."(".$CGIURL.")", $log_parms);

header($http_response_header[0], FALSE);
Header("Content-type: application/json; charset=utf-8");
echo $result;
exit;

?>
