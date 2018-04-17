<?php
/**********************************************************************
// ��������Ź�޸���������ե�����
//
// ��������
// 2011/11/04 H.Nakamura	��������
// 2011/11/25 K.Akiyama		����IP�ɲ�
// 2013/02/20 Y.Matsukawa	�ꥢ�륿����ǡ���
// 2016/01/14 Y.Matsukawa	¿���쥵���Ȥ���θƤӽФ����б���������³��
// 2016/07/04 H.Osamoto		OAuthǧ��(coreweb)IP�ɲ�
/*********************************************************************/

	/* �ǥХå��⡼�� */
	if ($D_EMAP_ENV == 'dev') $D_DEBUG = true;
	else $D_DEBUG = false;

	/* ���� CGI���� */
	define('D_LOG_CGIKEY','299912312359592EmapSsC');
	
	/* ����IP */
	$D_IP_LIST = array();
	$D_IP_LIST[] = '127.0.0.1';			// ��������
	$D_IP_LIST[] = '218.225.89.15';		// ZDC
	$D_IP_LIST[] = '218.225.89.139';	// ZDC
	$D_IP_LIST[] = '157.101.254.72';	// ZDC
	$D_IP_LIST[] = '172.28.0.115';	// ZDC
	$D_IP_LIST[] = '218.225.89.53';		// ZDC��VPN��
	$D_IP_LIST[] = '172.28.192.14';		// ZDC(dnpkanshi01)
	$D_IP_LIST[] = '172.28.192.15';		// ZDC(dnpkanshi02)
	$D_IP_LIST[] = '210.133.103.162';	// ZDC(dnpkanshi_GIP)
	// add 2016/07/04 H.Osamoto [
	// mod 2016/07/06 H.Osamoto [
	//	$D_IP_LIST[] = '10.82.8.*';		// OAuthǧ��(coreweb)
	//	$D_IP_LIST[] = '10.82.16.*';	// OAuthǧ��(coreweb)
	//	$D_IP_LIST[] = '10.102.8.*';	// OAuthǧ��(coreweb)
	//	$D_IP_LIST[] = '10.102.16.*';	// OAuthǧ��(coreweb)
	$D_IP_LIST[] = '10.82.*.*';			// OAuthǧ��(coreweb)
	$D_IP_LIST[] = '10.102.*.*';		// OAuthǧ��(coreweb)
	// mod 2016/07/06 H.Osamoto ]
	// add 2016/07/04 H.Osamoto ]
	$D_IP_LIST = implode(':', $D_IP_LIST);
	
	/* �������ѻ���ID */
	$D_INTID = array();
	$D_INTID[] = '@EMAPP1@';//PC1.0
	$D_INTID[] = '@EMAPP2@';//PC2.0
	$D_INTID[] = '@EMAPMB@';//����
	$D_INTID[] = '@EMAPSM@';//���ޥ�
	$D_INTID[] = '@EMAPCG@';//CGI
	$D_INTID[] = '@EMAPAP@';//���ޥۥ��ץ�

	/* RD���ܥ����� */
	$D_RD_VAL_KBN['T'] = 'TEXT';
	$D_RD_VAL_KBN['I'] = 'IMG';
	$D_RD_VAL_KBN['F'] = 'FLAG';
	
	/* CGI */
	$D_RD_CGI['rd_img'] = "http://$D_DOMAIN_G/cgi/rd_img.cgi";
	
	/* �������ѻ���ID */		// add 2016/01/14 Y.Matsukawa
	$D_STORE_INTID = array( 
		'EmapMlSsQ', 'EmapMlSsM', 'EmapMlSsS', 'EmapMlSsA'
	);
?>