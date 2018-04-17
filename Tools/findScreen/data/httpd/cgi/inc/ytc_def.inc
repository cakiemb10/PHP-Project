<?php
// ---------------------------------------------------------
// 【ヤマト運輸向けカスタマイズ】定義
//
// 2013/07/12 Y.Matsukawa	新規作成
// 2013/08/16 Y.Matsukawa	IP変更
// 2016/10/19 Y.Matsukawa	ヤマト運輸向け店頭受取API（ytc_store_nearsearch.cgi）対応
// 2017/05/01 K.Tani		検証用にローカルIP追加
// ---------------------------------------------------------
$hostname = trim(`hostname`);

// 許可IP
$D_IP_LIST = array();
$D_IP_LIST[] = '218.225.89.15';		// ZDC
$D_IP_LIST[] = '218.225.89.139';	// ZDC
$D_IP_LIST[] = '157.101.254.72';	// ZDC
$D_IP_LIST[] = '172.28.0.115';	// ZDC
$D_IP_LIST[] = '157.101.254.72';	// ZDC
$D_IP_LIST[] = '218.225.89.53';		// ZDC（VPN）
$D_IP_LIST[] = '172.28.192.14';		// ZDC(dnpkanshi01)
$D_IP_LIST[] = '172.28.192.15';		// ZDC(dnpkanshi02)
$D_IP_LIST[] = '210.133.103.162';	// ZDC(dnpkanshi_GIP)
$D_IP_LIST[] = '218.40.12.250';		// YSD開発環境
//$D_IP_LIST[] = '103.2.27.11';		// YSD開発環境		mod 2013/08/16 Y.Matsukawa
$D_IP_LIST[] = '103.2.24.41';		// YSD開発環境
$D_IP_LIST[] = '218.40.14.250';		// YSD本番環境
$D_IP_LIST[] = '103.2.25.31';		// YSD本番環境
$D_IP_LIST[] = '10.41.131*';	// ZDC	add 2017/05/01 K.Tani
$D_IP_LIST[] = '10.41.132*';	// ZDC	add 2017/05/01 K.Tani
$D_IP_LIST = implode(':', $D_IP_LIST);

switch( $hostname ){
//----- 開発機 -----
case "dev-storenaviweb01":
	$D_DEBUG = true;
	$D_CID = 'yamatotest';
	$D_YTC_AUTH_URL = 'http://103.2.24.43/authapi/authAllow';		// add 2016/10/19 Y.Matsukawa
	break;
//----- 検証機 -----
case "storenaviweb-v01":
case "storenaviweb-v02":		// add 2016/10/19 Y.Matsukawa
	$D_DEBUG = false;
	$D_CID = 'yamatotest';
	$D_YTC_AUTH_URL = 'http://103.2.24.43/authapi/authAllow';		// add 2016/10/19 Y.Matsukawa
	break;
//----- 本番機 -----
default:
	$D_DEBUG = false;
	$D_CID = 'yamato';
	$D_YTC_AUTH_URL = 'https://authapi.kuronekoyamato.co.jp/authapi/authAllow';		// add 2016/10/19 Y.Matsukawa
}

?>
