<?php
// ---------------------------------------------------------
// �ڥ�ޥȱ�͢�����������ޥ��������
//
// 2013/07/12 Y.Matsukawa	��������
// 2013/08/16 Y.Matsukawa	IP�ѹ�
// 2016/10/19 Y.Matsukawa	��ޥȱ�͢����ŹƬ����API��ytc_store_nearsearch.cgi���б�
// 2017/05/01 K.Tani		�����Ѥ˥�������IP�ɲ�
// ---------------------------------------------------------
$hostname = trim(`hostname`);

// ����IP
$D_IP_LIST = array();
$D_IP_LIST[] = '218.225.89.15';		// ZDC
$D_IP_LIST[] = '218.225.89.139';	// ZDC
$D_IP_LIST[] = '157.101.254.72';	// ZDC
$D_IP_LIST[] = '172.28.0.115';	// ZDC
$D_IP_LIST[] = '157.101.254.72';	// ZDC
$D_IP_LIST[] = '218.225.89.53';		// ZDC��VPN��
$D_IP_LIST[] = '172.28.192.14';		// ZDC(dnpkanshi01)
$D_IP_LIST[] = '172.28.192.15';		// ZDC(dnpkanshi02)
$D_IP_LIST[] = '210.133.103.162';	// ZDC(dnpkanshi_GIP)
$D_IP_LIST[] = '218.40.12.250';		// YSD��ȯ�Ķ�
//$D_IP_LIST[] = '103.2.27.11';		// YSD��ȯ�Ķ�		mod 2013/08/16 Y.Matsukawa
$D_IP_LIST[] = '103.2.24.41';		// YSD��ȯ�Ķ�
$D_IP_LIST[] = '218.40.14.250';		// YSD���ִĶ�
$D_IP_LIST[] = '103.2.25.31';		// YSD���ִĶ�
$D_IP_LIST[] = '10.41.131*';	// ZDC	add 2017/05/01 K.Tani
$D_IP_LIST[] = '10.41.132*';	// ZDC	add 2017/05/01 K.Tani
$D_IP_LIST = implode(':', $D_IP_LIST);

switch( $hostname ){
//----- ��ȯ�� -----
case "dev-storenaviweb01":
	$D_DEBUG = true;
	$D_CID = 'yamatotest';
	$D_YTC_AUTH_URL = 'http://103.2.24.43/authapi/authAllow';		// add 2016/10/19 Y.Matsukawa
	break;
//----- ���ڵ� -----
case "storenaviweb-v01":
case "storenaviweb-v02":		// add 2016/10/19 Y.Matsukawa
	$D_DEBUG = false;
	$D_CID = 'yamatotest';
	$D_YTC_AUTH_URL = 'http://103.2.24.43/authapi/authAllow';		// add 2016/10/19 Y.Matsukawa
	break;
//----- ���ֵ� -----
default:
	$D_DEBUG = false;
	$D_CID = 'yamato';
	$D_YTC_AUTH_URL = 'https://authapi.kuronekoyamato.co.jp/authapi/authAllow';		// add 2016/10/19 Y.Matsukawa
}

?>