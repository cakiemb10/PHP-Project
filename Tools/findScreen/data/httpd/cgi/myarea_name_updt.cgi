<?php
/*========================================================*/
// �ե�����̾��myarea_name_updt.cgi
// ����̾����My���ꥢ��CGI��My���ꥢ̾����
//
// ��������
// 2011/04/08 H.Osamoto		��������
// 2011/07/04 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
/*========================================================*/


/*==============================================*/
// CGI������
/*==============================================*/
$CGICD = "m02";

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// �꥿���󥳡������
/*==============================================*/
define( 'DEF_RETCD_DE',    '00000' );      //���ｪλ
define( 'DEF_RETCD_DE7',   '00007' );      //My���ꥢ̾����Ͽʸ���������С�
define( 'DEF_RETCD_DE9',   '00009' );      //�����¸ʸ�����顼
define( 'DEF_RETCD_DERR1', '17900' );      //�ǡ����١��������������顼
define( 'DEF_RETCD_DERR2', '17901' );      //My���ꥢ�������顼

/*==============================================*/
// ��Ͽ��ǽʸ����
/*==============================================*/
$MAX_NM_LEN = 100;	// 100byte

/*==============================================*/
// ����ե�����
/*==============================================*/
include("d_serv_ora.inc");
include("oraDBAccess.inc");
include("oraDBAccessMst.inc");	// mstDB����
include("function.inc");		// ���̴ؿ�
include("myarea_func.inc");		// My���ꥢ�Ѵؿ�
include("log.inc");				// ������

/*==============================================*/
// ���顼���Ϥ�����Ū��OFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
error_reporting(0);

/*==============================================*/
//�����ϳ���
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$MYAREA_ID		= getCgiParameter('myarea_id','');				/* My���ꥢID */
$CORP_ID		= getCgiParameter('corp_id','');				/* ���ID */
$MYAREA_NAME	= urldecode(getCgiParameter('myarea_name',''));	/* My���ꥢ̾ */

// add 2011/07/05 Y.Nakajima 
if (!isset($USER_ID)) $USER_ID = "";
$USER_ID = str_replace(" ", "+", $USER_ID);

// Ⱦ�ѥ��ʢ����ѥ��ʤ��Ѵ�
$MYAREA_NAME = mb_convert_kana($MYAREA_NAME, "KV");


/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
$log_parms =  'MYAREA_ID:'.$MYAREA_ID;
$log_parms .= ' CORP_ID:'.$CORP_ID;
$log_parms .= ' MYAREA_NAME:'.$MYAREA_NAME;


// ʸ���������å������å�
$str_len = strlen($MYAREA_NAME);
if (strlen($MYAREA_NAME) > $MAX_NM_LEN){
	// My���ꥢ̾��ʸ���������С�
	echo $CGICD.DEF_RETCD_DE7;
	exit(0);
}

// �����¸ʸ�������å�
if (!IzonSearch($MYAREA_NAME)){
	// �����¸ʸ��ͭ��
	echo $CGICD.DEF_RETCD_DE9;
	exit(0);
}

/*==============================================*/
// DB��³
/*==============================================*/
$dba = new oraDBAccessMst();
if (!$dba->open()) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DERR1;
	exit(0);
}


/*==============================================*/
// My���ꥢ����
/*==============================================*/
$retcd = myarea_name_update(&$dba, $MYAREA_ID, $MYAREA_NAME, &$rtncd);
if (trim($rtncd) != "0000" || !$retcd) {
	$dba->close();
	echo $CGICD.DEF_RETCD_DERR2;
	exit(0);
}

/*==============================================*/
// DB������
/*==============================================*/
$dba->close();

echo $CGICD.DEF_RETCD_DE;
exit(1);

?>
