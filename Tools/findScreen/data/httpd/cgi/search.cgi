<?php
/*========================================================*/
// �ե�����̾��search.cgi
// ����̾�������å�������󸡺�(��åѡ�CGI��
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
//error_reporting(E_ALL);
error_reporting(0);

/*==============================================*/
//�����ϳ���
/*==============================================*/
//include('logs/inc/com_log_open.inc');

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$SID		= getCgiParameter('sid','');			/* ��������̾ */
$UID		= getCgiParameter('uid','');			/* �桼����ID */
$S_TIMESTAMP= getCgiParameter('s_timestamp','');	/* �о������ʳ��ϡ� */
$E_TIMESTAMP= getCgiParameter('e_timestamp','');	/* �о������ʽ�λ�� */
$POI_ID		= getCgiParameter('poi_id','');				/* POI ID */
$LATLON		= getCgiParameter('latlon','');		/* ���ٷ��� */
$RAD		= getCgiParameter('rad','');		/* Ⱦ�� */
$SORT		= getCgiParameter('sort','');		/* ������ */
$POS		= getCgiParameter('pos','');		/* �������� */
$CNT		= getCgiParameter('cnt','');		/* ������� */

/*==============================================*/
// �¹��Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$parms = '?sid='.$SID;
$parms .= '&uid='.$UID;
$parms .= '&s_timestamp='.$S_TIMESTAMP;
$parms .= '&e_timestamp='.$E_TIMESTAMP;
$parms .= '&poi_id='.$POI_ID;
$parms .= '&latlon='.$LATLON;
$parms .= '&rad='.$RAD;
$parms .= '&sort='.$SORT;
$parms .= '&pos='.$POS;
$parms .= '&cnt='.$CNT;

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
/*
$log_parms  = ' SID:'.$SID;
$log_parms .= ' UID:'.$UID;
$log_parms .= ' S_TIMESTAMP:'.$S_TIMESTAMP;
$log_parms .= ' E_TIMESTAMP:'.$E_TIMESTAMP;
$log_parms .= ' POI_ID:'.$POI_ID;
$log_parms .= ' LATLON:'.$LATLON;
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
$CGI = $CGIURL .$APICGINM.$parms;

//echo $CGI;
$result = file_get_contents($CGI);

// ������
//put_log($CGICD, $SID,$http_response_header[0]."(".$CGIURL.")", $log_parms);


header($http_response_header[0], FALSE);
Header("Content-type: application/json; charset=utf-8");
echo $result;
exit;
?>
