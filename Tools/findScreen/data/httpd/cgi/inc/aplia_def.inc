<?php
/**********************************************************************
// Aplia API �ƤӽФ�������ե�����
//
// ��������
// 2012/12/10 H.Iijima	��������
/*********************************************************************/
$hostname = trim(`hostname`);

switch( $hostname ){
//----- ��ȯ�� -----
//case "devemapweb": mod 2011/09/29 K.Masuda
case "dev-storenaviweb01":
	$D_DEBUG = true;
	break;
//----- ���ڵ� -----
//case "emapweb00":	mod 2011/09/29 K.Masuda
case "storenaviweb-v01":
	$D_DEBUG = false;
	break;
//----- ���ֵ� -----
default:
	$D_DEBUG = false;
}

// ---------------------------------------------------------
// ����ե����� API����
// ---------------------------------------------------------
switch( $hostname ){//----- ��ȯ�� -----
     case "dev-storenaviweb01":
     case "emapweb00":   //----- ���ڵ� -----
          $API_APLIA_SRV  = "10.47.30.41";
          break;
     case "storenaviweb-v01": //----- VM���ڵ� -----
          $API_APLIA_SRV  = "172.24.6.223";
          break;
//----- ���ֵ� -----
     default:
          $API_APLIA_SRV  = "172.24.6.222";
}

$API_APLIA_PATH = '/v1_0/checkin/';


?>