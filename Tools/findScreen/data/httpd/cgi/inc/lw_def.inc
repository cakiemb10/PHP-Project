<?php
/**********************************************************************
// �ڥ�����������������ޥ���������ե�����
//
// ��������
// 2010/12/10 Y.Matsukawa	��������
// 2011/01/11 Y.Matsukawa	����IP�����ĥ�ե��顼�ɲ�
// 2011/08/12 K.Masuda		����IP�ɲ�
// 2011/09/06 K.Masuda		����IP�ɲ�
// 2011/09/29 Y.Nakajima	����IP�ɲ�
// 2011/09/29 K.Masuda 		��ȯ�����ڥ�����̾�ѹ�
// 2012/10/27 K.Masuda 		����IP�ɲ�
// 2016/04/04 H.Osamoto		����IP�ɲ�
/*********************************************************************/
$hostname = trim(`hostname`);

// ����IP
$D_IP_LIST = array();
$D_IP_LIST[] = '218.225.89.15';	// ZDC
$D_IP_LIST[] = '218.225.89.139';	// ZDC
$D_IP_LIST[] = '157.101.254.72';	// ZDC
$D_IP_LIST[] = '172.28.0.115';	// ZDC
$D_IP_LIST[] = '218.225.89.53';	// ZDC��VPN��
$D_IP_LIST[] = '172.28.192.14';		// ZDC(dnpkanshi01)		add 2011/04/19 c_hanajima
$D_IP_LIST[] = '172.28.192.15';     	// ZDC(dnpkanshi02)		add 2011/04/19 c_hanajima
$D_IP_LIST[] = '210.133.103.162';       // ZDC(dnpkanshi_GIP)     add 2011/04/25 c_hanajima
$D_IP_LIST[] = '113.32.139.68';		// Sonicjam
$D_IP_LIST[] = '113.32.139.66';		// Sonicjam
$D_IP_LIST[] = '61.192.220.4';		// Sonicjam		add 2011/01/11 Y.Matsukawa
$D_IP_LIST[] = '202.61.22.57';		// ���������ƥ�			add 2011/08/12 K.Masuda
$D_IP_LIST[] = '59.106.183.57';		// �ԥ����륰��å�		add 2011/08/12 K.Masuda
$D_IP_LIST[] = '124.41.85.21';		// �ԥ����륰��å�		add 2011/08/12 K.Masuda
$D_IP_LIST[] = '210.248.202.32';	// �ԥ����륰��å�		add 2011/08/12 K.Masuda
$D_IP_LIST[] = '59.106.158.165';	// ���������ƥ�			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '59.106.158.166';	// ���������ƥ�			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '59.106.158.167';	// ���������ƥ�			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '59.106.158.169';	// ���������ƥ�			add 2011/09/06 K.Masuda
$D_IP_LIST[] = '157.101.254.72';	// ZDC			add 2011/09/29 Y.Nakajima
$D_IP_LIST[] = '180.43.41.94';		// SKC			add 2012/10/27 K.Masuda
$D_IP_LIST[] = '111.87.51.245';		// ��������GIP	add 2016/04/04 H.Osamoto
$D_IP_LIST[] = '111.87.51.251';		// ��������GIP	add 2016/04/04 H.Osamoto
$D_IP_LIST = implode(':', $D_IP_LIST);

// ���ĥ�ե���
$D_REFERER_LIST = array();
//$D_REFERER_LIST[] = 'http://218.225.89.139/test_form_cgi/';		// ZDC
$D_REFERER_LIST[] = 'http://lwsapp_map.sonicjam.jp';
$D_REFERER_LIST[] = 'lwsapp_map.sonicjam.jp';		// add 2011/01/11 Y.Matsukawa

switch( $hostname ){
//----- ��ȯ�� -----
//case "devemapweb": mod 2011/09/29 K.Masuda
case "dev-storenaviweb01":
	$D_DEBUG = true;
	$D_CID = 'lawsontest';
	break;
//----- ���ڵ� -----
//case "emapweb00":	mod 2011/09/29 K.Masuda
case "storenaviweb-v01":
	$D_DEBUG = false;
	$D_CID = 'lawsontest';
	break;
//----- ���ֵ� -----
default:
	$D_DEBUG = false;
	$D_CID = 'lawson';
}

?>