<?php
// ---------------------------------------------------------
// 店舗案内CGI用共通定義ファイル
//
// 2012/11/13 Y.Matsukawa	新規作成
// ---------------------------------------------------------
$hostname = trim(`hostname`);

//**********************************************************
//* 環境により設定内容を切替
//**********************************************************
switch( $hostname ){
//----- 開発機 -----
case "dev-storenaviweb01":
	// apiproxy
	$D_APIPROXY['HOST'] = '10.253.0.8';
	$D_APIPROXY['PORT'] = '3128';
	// JCN満空情報取得
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://localhost/cgi/JCNChargingSpotStatusZDC_Stub.cgi';			//スタブ
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.com:10080/wwwap/ChargingSpotStatusZDC';	// 検証
	$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.co.jp/wwwap/ChargingSpotStatusZDC';		// 本番
	$D_JCN_PXY['ChargingSpotStatusZDC'] = 1;
	break;

//----- 検証機 -----
case "storenaviweb-v01":
case "storenaviweb-v02":
	// apiproxy
	$D_APIPROXY['HOST'] = '172.28.0.3';
	$D_APIPROXY['PORT'] = '3128';
	// JCN満空情報取得
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://localhost/cgi/JCNChargingSpotStatusZDC_Stub.cgi';			//スタブ
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.com:10080/wwwap/ChargingSpotStatusZDC';	// 検証
	$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.co.jp/wwwap/ChargingSpotStatusZDC';		// 本番
	$D_JCN_PXY['ChargingSpotStatusZDC'] = 1;
	break;

//----- 本番機 -----
default:
	// apiproxy
	$D_APIPROXY['HOST'] = '172.28.0.3';
	$D_APIPROXY['PORT'] = '3128';
	// JCN満空情報取得
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://localhost/cgi/JCNChargingSpotStatusZDC_Stub.cgi';			//スタブ
	//$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.com:10080/wwwap/ChargingSpotStatusZDC';	// 検証
	$D_JCN_URL['ChargingSpotStatusZDC'] = 'http://www.charge-net.co.jp/wwwap/ChargingSpotStatusZDC';		// 本番
	$D_JCN_PXY['ChargingSpotStatusZDC'] = 1;
	break;
}

?>
