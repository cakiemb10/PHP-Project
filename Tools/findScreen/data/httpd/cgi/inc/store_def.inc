<?php
/**********************************************************************
// 【汎用版店舗検索】定義ファイル
//
// 更新履歴：
// 2011/11/04 H.Nakamura	新規作成
// 2011/11/25 K.Akiyama		許可IP追加
// 2013/02/20 Y.Matsukawa	リアルタイムデータ
// 2016/01/14 Y.Matsukawa	多言語サイトからの呼び出しに対応（内部接続）
// 2016/07/04 H.Osamoto		OAuth認証(coreweb)IP追加
/*********************************************************************/

	/* デバッグモード */
	if ($D_EMAP_ENV == 'dev') $D_DEBUG = true;
	else $D_DEBUG = false;

	/* ログ CGIキー */
	define('D_LOG_CGIKEY','299912312359592EmapSsC');
	
	/* 許可IP */
	$D_IP_LIST = array();
	$D_IP_LIST[] = '127.0.0.1';			// ローカル
	$D_IP_LIST[] = '218.225.89.15';		// ZDC
	$D_IP_LIST[] = '218.225.89.139';	// ZDC
	$D_IP_LIST[] = '157.101.254.72';	// ZDC
	$D_IP_LIST[] = '172.28.0.115';	// ZDC
	$D_IP_LIST[] = '218.225.89.53';		// ZDC（VPN）
	$D_IP_LIST[] = '172.28.192.14';		// ZDC(dnpkanshi01)
	$D_IP_LIST[] = '172.28.192.15';		// ZDC(dnpkanshi02)
	$D_IP_LIST[] = '210.133.103.162';	// ZDC(dnpkanshi_GIP)
	// add 2016/07/04 H.Osamoto [
	// mod 2016/07/06 H.Osamoto [
	//	$D_IP_LIST[] = '10.82.8.*';		// OAuth認証(coreweb)
	//	$D_IP_LIST[] = '10.82.16.*';	// OAuth認証(coreweb)
	//	$D_IP_LIST[] = '10.102.8.*';	// OAuth認証(coreweb)
	//	$D_IP_LIST[] = '10.102.16.*';	// OAuth認証(coreweb)
	$D_IP_LIST[] = '10.82.*.*';			// OAuth認証(coreweb)
	$D_IP_LIST[] = '10.102.*.*';		// OAuth認証(coreweb)
	// mod 2016/07/06 H.Osamoto ]
	// add 2016/07/04 H.Osamoto ]
	$D_IP_LIST = implode(':', $D_IP_LIST);
	
	/* 内部利用時のID */
	$D_INTID = array();
	$D_INTID[] = '@EMAPP1@';//PC1.0
	$D_INTID[] = '@EMAPP2@';//PC2.0
	$D_INTID[] = '@EMAPMB@';//携帯
	$D_INTID[] = '@EMAPSM@';//スマホ
	$D_INTID[] = '@EMAPCG@';//CGI
	$D_INTID[] = '@EMAPAP@';//スマホアプリ

	/* RD項目タイプ */
	$D_RD_VAL_KBN['T'] = 'TEXT';
	$D_RD_VAL_KBN['I'] = 'IMG';
	$D_RD_VAL_KBN['F'] = 'FLAG';
	
	/* CGI */
	$D_RD_CGI['rd_img'] = "http://$D_DOMAIN_G/cgi/rd_img.cgi";
	
	/* 内部利用時のID */		// add 2016/01/14 Y.Matsukawa
	$D_STORE_INTID = array( 
		'EmapMlSsQ', 'EmapMlSsM', 'EmapMlSsS', 'EmapMlSsA'
	);
?>
