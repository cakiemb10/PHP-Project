<?php
// ---------------------------------------------------------
// Ź�ް���CGI�Ѷ�������ե�����
//
// 2012/11/13 Y.Matsukawa	��������
// ---------------------------------------------------------
$hostname = trim(`hostname`);

//**********************************************************
//* �Ķ��ˤ���������Ƥ�����
//**********************************************************
switch( $hostname ){
//----- ��ȯ�� -----
case "dev-storenaviweb01":
	// apiproxy
	$D_APIPROXY['HOST'] = '10.253.0.8';
	$D_APIPROXY['PORT'] = '3128';
	// JCN�����������
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://localhost/cgi/JCNChargingSpotStatusZDC_Stub.cgi';			//������
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.com:10080/wwwap/ChargingSpotStatusZDC';	// ����
	$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.co.jp/wwwap/ChargingSpotStatusZDC';		// ����
	$D_JCN_PXY['ChargingSpotStatusZDC'] = 1;
	break;

//----- ���ڵ� -----
case "storenaviweb-v01":
case "storenaviweb-v02":
	// apiproxy
	$D_APIPROXY['HOST'] = '172.28.0.3';
	$D_APIPROXY['PORT'] = '3128';
	// JCN�����������
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://localhost/cgi/JCNChargingSpotStatusZDC_Stub.cgi';			//������
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.com:10080/wwwap/ChargingSpotStatusZDC';	// ����
	$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.co.jp/wwwap/ChargingSpotStatusZDC';		// ����
	$D_JCN_PXY['ChargingSpotStatusZDC'] = 1;
	break;

//----- ���ֵ� -----
default:
	// apiproxy
	$D_APIPROXY['HOST'] = '172.28.0.3';
	$D_APIPROXY['PORT'] = '3128';
	// JCN�����������
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://localhost/cgi/JCNChargingSpotStatusZDC_Stub.cgi';			//������
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.com:10080/wwwap/ChargingSpotStatusZDC';	// ����
	$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.co.jp/wwwap/ChargingSpotStatusZDC';		// ����
	$D_JCN_PXY['ChargingSpotStatusZDC'] = 1;
	break;
}

?>