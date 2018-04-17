<?php
/**********************************************************************
// 【ローソン向けカスタマイズ】定義ファイル
//
// 更新履歴：
// 2010/12/10 Y.Matsukawa	新規作成
// 2011/01/11 Y.Matsukawa	許可IP、許可リファラー追加
// 2011/08/12 K.Masuda		許可IP追加
// 2011/09/06 K.Masuda		許可IP追加
// 2011/09/29 Y.Nakajima	許可IP追加
// 2011/09/29 K.Masuda 		開発・検証サーバ名変更
// 2012/10/27 K.Masuda 		許可IP追加
// 2016/04/04 H.Osamoto		許可IP追加
/*********************************************************************/
$hostname = trim(`hostname`);

// 許可IP
$D_IP_LIST = array();
$D_IP_LIST[] = '218.225.89.15';	// ZDC
$D_IP_LIST[] = '218.225.89.139';	// ZDC
$D_IP_LIST[] = '157.101.254.72';	// ZDC
$D_IP_LIST[] = '172.28.0.115';	// ZDC
$D_IP_LIST[] = '218.225.89.53';	// ZDC（VPN）
$D_IP_LIST[] = '172.28.192.14';		// ZDC(dnpkanshi01)		add 2011/04/19 c_hanajima
$D_IP_LIST[] = '172.28.192.15';     	// ZDC(dnpkanshi02)		add 2011/04/19 c_hanajima
$D_IP_LIST[] = '210.133.103.162';       // ZDC(dnpkanshi_GIP)     add 2011/04/25 c_hanajima
$D_IP_LIST[] = '113.32.139.68';		// Sonicjam
$D_IP_LIST[] = '113.32.139.66';		// Sonicjam
$D_IP_LIST[] = '61.192.220.4';		// Sonicjam		add 2011/01/11 Y.Matsukawa
$D_IP_LIST[] = '202.61.22.57';		// 三幸システム			add 2011/08/12 K.Masuda
$D_IP_LIST[] = '59.106.183.57';		// ピクセルグリッド		add 2011/08/12 K.Masuda
$D_IP_LIST[] = '124.41.85.21';		// ピクセルグリッド		add 2011/08/12 K.Masuda
$D_IP_LIST[] = '210.248.202.32';	// ピクセルグリッド		add 2011/08/12 K.Masuda
$D_IP_LIST[] = '59.106.158.165';	// 三幸システム			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '59.106.158.166';	// 三幸システム			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '59.106.158.167';	// 三幸システム			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '59.106.158.169';	// 三幸システム			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '157.101.254.72';	// ZDC			add 2011/09/29 Y.Nakajima
$D_IP_LIST[] = '180.43.41.94';		// SKC			add 2012/10/27 K.Masuda
$D_IP_LIST[] = '111.87.51.245';		// ローソン新GIP	add 2016/04/04 H.Osamoto
$D_IP_LIST[] = '111.87.51.251';		// ローソン新GIP	add 2016/04/04 H.Osamoto
$D_IP_LIST = implode(':', $D_IP_LIST);

// 許可リファラ
$D_REFERER_LIST = array();
//$D_REFERER_LIST[] = 'http://218.225.89.139/test_form_cgi/';		// ZDC
$D_REFERER_LIST[] = 'http://lwsapp_map.sonicjam.jp';
$D_REFERER_LIST[] = 'lwsapp_map.sonicjam.jp';		// add 2011/01/11 Y.Matsukawa

switch( $hostname ){
//----- 開発機 -----
//case "devemapweb": mod 2011/09/29 K.Masuda
case "dev-storenaviweb01":
	$D_DEBUG = true;
	$D_CID = 'lawsontest';
	break;
//----- 検証機 -----
//case "emapweb00":	mod 2011/09/29 K.Masuda
case "storenaviweb-v01":
	$D_DEBUG = false;
	$D_CID = 'lawsontest';
	break;
//----- 本番機 -----
default:
	$D_DEBUG = false;
	$D_CID = 'lawson';
}

?>
