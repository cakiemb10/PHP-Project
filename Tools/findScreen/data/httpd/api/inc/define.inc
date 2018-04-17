<?php
// ------------------------------------------------------------
// API�������ġ������
// 
// 2016/06/14 H.Yasunaga	��������
// 2016/08/24 H.Yasunaga	��ɸ����[coord]�ѥ�᡼���ɲ�
// 2016/12/16 H.Yasunaga	��ɸ����[coord]�ѥ�᡼�����ͤ�"W"���ɲá��쥹�ݥ󥹤ΰ��ٷ��٤�����¬�ϷϤˤ���
// ------------------------------------------------------------
	// ����͹��API�Υ����ѥơ��֥�̾
	define("API_LOG_TABLE",			"JPOST_API_LOG_TBL");
	// ����͹��API��API�������������ѤΥơ��֥�̾
	define("API_KEY_TABLE",			"JPOST_API_KEY_TBL");
	// ����͹��API���������������ơ��֥�̾
	define("API_MANAGE_LOG_TABLE",	"JPOST_API_MANAGE_LOG_TBL");
	
	// API���顼 �ꥯ�����ȹ��ܤ���������
	define("API_ERROR_INVALID_PARAMETER", 1);
	// API���顼 ���������������ͤ����äƤ��ʤ�������
	define("API_ERROR_INVALID_KEY", 2);
	// API���顼 IP���ɥ쥹����������������ɳ�Ť����ͤǤʤ���������
	define("API_ERROR_INVALID_IPADDRESS", 3);
	// API���顼 ��������ǡ�����1���ʤ�
	define("API_ERROR_ITEM_NOT_FOUND", 4);
	// API���顼 ����¾�Υ��顼(��������λ�Ǥ��ʤ�)
	define("API_ERROR_INTERNAL_SERVER", 5);
	
	
	/* �꥿���󥳡��� */
	define( 'DEF_RETCD_DE',   '00000' );       // ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
	define( 'DEF_RETCD_DEND', '00001' );       // ���˸��礦�ǡ�������ʸ�³�ǡ��������
	define( 'DEF_RETCD_DNE',  '11009' );       // ���˸��礦�ǡ����ʤ�
	define( 'DEF_RETCD_DERR1','17900' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR2','17002' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_DERR3','17999' );       // �ǡ����١��������������顼
	define( 'DEF_RETCD_PERR1','19100' );       // ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	define( 'DEF_RETCD_PERR2','19200' );       // ���ϥѥ�᡼�����顼(��ʸ���顼)
	define( 'DEF_RETCD_PERR3','19200' );       // ���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)
	
	// ¬�Ϸ�
	define("DATUM_WGS84", "WGS84");
	define("DATUM_TOKYO", "TOKYO");
	define( 'DEF_PRM_DATUM_TOKYO', 	'TOKYO');       // ¬�Ϸϡ�����¬�Ϸϡ�
	define( 'DEF_PRM_DATUM_WGS84', 	'WGS84');       // ¬�Ϸϡ�����¬�Ϸϡ�
	
	// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
	define("DEF_COORD_ZENRIN", "Z");	// �������ɸ
	define("DEF_COORD_MAPION", "M");	// Mapion��ɸ
	// add end 2016/08/24 ]
	// add start 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"����¬�Ϸ�
	define("DEF_COORD_WORLD", "W");
	// add end 2016/12/16 ]
?>