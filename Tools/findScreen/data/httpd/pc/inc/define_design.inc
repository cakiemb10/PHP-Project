<?php
// ------------------------------------------------------------
// ����ե����� �ǥ�����˴ؤ������
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2008/09/02 Y.Matsukawa	Maplink����ʸ������³���ˡ��ҥåȤ�������ʸ�������̤�ɽ��
// 2008/12/18 Y.Matsukawa	Maplink�Υǥե���ȥ�������ʡ��ˤ��ɲ�
// 2010/03/09 Y.Matsukawa	����FW������������ꥹ�ȡ��Ͽޤʤ��ˤ�����
// 2010/06/16 Y.Matsukawa	��ȯ�Ϥ���ꤷ�ƥ롼��õ��
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2010/11/03 K.Masuda		���ꥢ����ʣ���б�
// 2011/04/14 H.Osamoto		My���ꥢ�б�
// 2011/06/02 H.Osamoto		�ե꡼���ʣ�縡���б�
// 2011/07/05 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/06/12 Y.Matsukawa	IE7�ߴ��⡼�ɤ�̵���ˤǤ���褦�ˤ���
// ------------------------------------------------------------

// IE7�ߴ��⡼��		add 2012/06/12 Y.Matsukawa
if(!isset($D_EMULATE_IE7_VIEW)) $D_EMULATE_IE7_VIEW = 1;
if(!isset($D_EMULATE_IE7_PRINT)) $D_EMULATE_IE7_PRINT = 1;

//�ֵ����פ�ɸ��θƤ���
if(!isset($D_USER_DEFNAME)) $D_USER_DEFNAME = "����";
//�֥����ӥ��פ�ɸ��θƤ���
if(!isset($D_USER_SERVICENAME)) $D_USER_SERVICENAME = "�����ӥ�";


// �Ͽ� ----------------------------------------------------
//�̾�⡼�� or �����⡼��
if(!isset($D_MAP_PRINT_MODE)) $D_MAP_PRINT_MODE = 0;//0���̾�⡼�ɡ�1�������⡼��
//�����ॳ��ȥ����� �桼��������ȥ����뤬̵�����-1���ȽФ��ʤ�
if(!isset($D_MAP_CONTROL)) $D_MAP_CONTROL = 3;
//�濴����������� -1���ȽФ��ʤ�
if(!isset($D_MAP_CENTER)) $D_MAP_CENTER = -1;
//��������С����� -1���ȽФ��ʤ�
if(!isset($D_MAP_SCALEBAR)) $D_MAP_SCALEBAR = 1;
//����ܥå������� -1���ȽФ��ʤ�
if(!isset($D_MAP_INFO)) $D_MAP_INFO = -1;
//�ϿޤΥ쥤�䡼
if(!isset($D_MAP_LAYER_KBN)) $D_MAP_LAYER_KBN = 1;
//�ɤ߹������ɽ��
if(!isset($D_MAP_WAIT_OFFSETX)) $D_MAP_WAIT_OFFSETX = -60;
if(!isset($D_MAP_WAIT_OFFSETY)) $D_MAP_WAIT_OFFSETY = -12;
if(!isset($D_MAP_WAIT_MSG)) $D_MAP_WAIT_MSG  = "�ɤ߹�����Ǥ�";


// ���ָ����� ----------------------------------------------
//���ڡ�������
if(!isset($D_SEARCH_LIST_PAGE)) $D_SEARCH_LIST_PAGE  = 10;//�ꥹ�ȷ���
if(!isset($D_SEARCH_TABLE_PAGE)) $D_SEARCH_TABLE_PAGE = 16;//�ơ��֥����
if(!isset($D_SEARCH_SHOPLIST_PAGE)) $D_SEARCH_SHOPLIST_PAGE  = 5;//�����ꥹ��
if(!isset($D_SEARCH_FROUTE_LIST_PAGE)) $D_SEARCH_FROUTE_LIST_PAGE  = 10;//��ȯ�ϻ���롼�Ȥθ����ꥹ��		add 2010/06/16 Y.Matsukawa
//�ơ��֥�����Σ��Ԥ����
if(!isset($D_SEARCH_TABLE_COLS)) $D_SEARCH_TABLE_COLS = 4;
//����̾
if(!isset($D_HISTORY_NAME["AddrW"])) $D_HISTORY_NAME["AddrW"] = "����ե꡼���";
if(!isset($D_HISTORY_NAME["StW"])) $D_HISTORY_NAME["StW"]   = "�إե꡼���";
if(!isset($D_HISTORY_NAME["PoiW"])) $D_HISTORY_NAME["PoiW"]  = "���ߥե꡼���";
if(!isset($D_HISTORY_NAME["ZipW"])) $D_HISTORY_NAME["ZipW"]  = "͹���ֹ�ե꡼���";
if(!isset($D_HISTORY_NAME["ShopW"])) $D_HISTORY_NAME["ShopW"] = $D_USER_DEFNAME."�ե꡼���";
if(!isset($D_HISTORY_NAME["AddrL"])) $D_HISTORY_NAME["AddrL"] = "����ꥹ��";
if(!isset($D_HISTORY_NAME["StL"])) $D_HISTORY_NAME["StL"]   = "�إꥹ��";
if(!isset($D_HISTORY_NAME["PoiL"])) $D_HISTORY_NAME["PoiL"]  = "���ߥꥹ��";
// mod 2010/11/03 K.Masuda [
if(!isset($D_HISTORY_NAME["ShopA"])) $D_HISTORY_NAME["ShopA"] = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_2"])) $D_HISTORY_NAME["ShopA_2"] = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_3"])) $D_HISTORY_NAME["ShopA_3"] = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_4"])) $D_HISTORY_NAME["ShopA_4"] = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_5"])) $D_HISTORY_NAME["ShopA_5"] = $D_USER_DEFNAME."���ꥢ";
// mod 2010/11/03 K.Masuda ]
if(!isset($D_HISTORY_NAME["Rail"])) $D_HISTORY_NAME["Rail"]  = "ϩ���޸���";
if(!isset($D_HISTORY_NAME["Area"])) $D_HISTORY_NAME["Area"]  = "�ϰ�޸���";
if(!isset($D_HISTORY_NAME["List"])) $D_HISTORY_NAME["List"]  = "�������";
if(!isset($D_HISTORY_NAME["Detail"])) $D_HISTORY_NAME["Detail"] = "�ܺ�ɽ��";
if(!isset($D_HISTORY_NAME["Npoi"])) $D_HISTORY_NAME["Npoi"]  = "�Ǵ���߸���";
if(!isset($D_HISTORY_NAME["Neki"])) $D_HISTORY_NAME["Neki"]  = "�Ǵ�ظ���";
if(!isset($D_HISTORY_NAME["Nshop"])) $D_HISTORY_NAME["Nshop"]  = $D_USER_DEFNAME."�ꥹ��";		// add 2010/03/09 Y.Matsukawa
if(!isset($D_HISTORY_NAME["FRoute"])) $D_HISTORY_NAME["FRoute"]  = "��ȯ�ϻ���롼��";		// add 2010/06/16 Y.Matsukawa
if(!isset($D_HISTORY_NAME["MyArea"])) $D_HISTORY_NAME["MyAreaEdit"]  = "My���ꥢ���Խ������";		// add 2011/04/14 H.Osamoto
if(!isset($D_HISTORY_NAME["MyArea"])) $D_HISTORY_NAME["MyArea"]  = "My���ꥢ";		// add 2011/04/14 H.Osamoto
if(!isset($D_HISTORY_NAME["Comb"])) $D_HISTORY_NAME["Comb"]  = "�ե꡼��ɸ���";		// add 2011/06/02 H.Osamoto
//����̾
if(!isset($D_SEL_NAME["AddrW"])) $D_SEL_NAME["AddrW"] = "����";
if(!isset($D_SEL_NAME["StW"])) $D_SEL_NAME["StW"]   = "��";
if(!isset($D_SEL_NAME["PoiW"])) $D_SEL_NAME["PoiW"]  = "����";
if(!isset($D_SEL_NAME["ZipW"])) $D_SEL_NAME["ZipW"]  = "����";
if(!isset($D_SEL_NAME["ShopW"])) $D_SEL_NAME["ShopW"] = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["AddrL"])) $D_SEL_NAME["AddrL"] = "����";
if(!isset($D_SEL_NAME["StL"])) $D_SEL_NAME["StL"]   = "��";
if(!isset($D_SEL_NAME["PoiL"])) $D_SEL_NAME["PoiL"]  = "����";
if(!isset($D_SEL_NAME["ShopA"])) $D_SEL_NAME["ShopA"] = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["PoiJnr"])) $D_SEL_NAME["PoiJnr"]  = "������";
if(!isset($D_SEL_NAME["Nshop"])) $D_SEL_NAME["Nshop"] = $D_USER_DEFNAME;		// add 2010/03/09 Y.Matsukawa
if(!isset($D_SEL_NAME["Err"])) $D_SEL_NAME["Err"] = "���顼";		// add 2011/07/05 Y.Nakajima
//�������ꥢ����ɽ��̾��
if(!isset($D_SEARCH_SHOPA_DISPNM[1])) $D_SEARCH_SHOPA_DISPNM[1]  = $D_SEL_NAME["AddrL"];//��1����
if(!isset($D_SEARCH_SHOPA_DISPNM[2])) $D_SEARCH_SHOPA_DISPNM[2]  = $D_SEL_NAME["AddrL"];//��2����
// add 2010/11/03 K.Masuda [
// mod 2011/07/05 Y.Nakajima [
if(!isset($D_SEARCH_SHOPA_DISPNM[3])) $D_SEARCH_SHOPA_DISPNM[3]  = $D_SEL_NAME["AddrL"];//��1����	���ꥢ������
if(!isset($D_SEARCH_SHOPA_DISPNM[4])) $D_SEARCH_SHOPA_DISPNM[4]  = $D_SEL_NAME["AddrL"];//��2����
if(!isset($D_SEARCH_SHOPA_DISPNM[5])) $D_SEARCH_SHOPA_DISPNM[5]  = $D_SEL_NAME["AddrL"];//��1����	���ꥢ������
if(!isset($D_SEARCH_SHOPA_DISPNM[6])) $D_SEARCH_SHOPA_DISPNM[6]  = $D_SEL_NAME["AddrL"];//��2����
if(!isset($D_SEARCH_SHOPA_DISPNM[7])) $D_SEARCH_SHOPA_DISPNM[7]  = $D_SEL_NAME["AddrL"];//��1����	���ꥢ������
if(!isset($D_SEARCH_SHOPA_DISPNM[8])) $D_SEARCH_SHOPA_DISPNM[8]  = $D_SEL_NAME["AddrL"];//��2����
if(!isset($D_SEARCH_SHOPA_DISPNM[9])) $D_SEARCH_SHOPA_DISPNM[9]  = $D_SEL_NAME["AddrL"];//��1����	���ꥢ������
if(!isset($D_SEARCH_SHOPA_DISPNM[10])) $D_SEARCH_SHOPA_DISPNM[10]  = $D_SEL_NAME["AddrL"];//��2����
// mod 2011/07/05 Y.Nakajima ]
// add 2010/11/03 K.Masuda ]
//����
if(!isset($D_EKI_LANG)) $D_EKI_LANG = '';//��
if(!isset($D_POI_LANG)) $D_POI_LANG = '';//����



// ������ --------------------------------------------------
//���������������
if(!isset($D_ICON_MSGOFFSETX)) $D_ICON_MSGOFFSETX = 0;
if(!isset($D_ICON_MSGOFFSETY)) $D_ICON_MSGOFFSETY = -8;
//�ǥե���ȵ��������������		add 2008/12/18 Y.Matsukawa
//if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE."img/000000.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_SHOP_W)) $D_ICON_SHOP_W = 11;
if(!isset($D_ICON_SHOP_H)) $D_ICON_SHOP_H = 11;
//���������������-NEW
//if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE."img/new.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE_G."img/new.gif";
if(!isset($D_ICON_NEW_W)) $D_ICON_NEW_W = 23;
if(!isset($D_ICON_NEW_H)) $D_ICON_NEW_H = 10;
//�������륢���������
//if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE."img/icon_cursor/0000.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE_G."img/icon_cursor/0000.gif";
if(!isset($D_ICON_CURSOR_W)) $D_ICON_CURSOR_W = 51;
if(!isset($D_ICON_CURSOR_H)) $D_ICON_CURSOR_H = 50;
//�ե������������������
//if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE."img/icon_cursor/0003.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE_G."img/icon_cursor/0003.gif";
if(!isset($D_ICON_FOCUS_W)) $D_ICON_FOCUS_W = 51;
if(!isset($D_ICON_FOCUS_H)) $D_ICON_FOCUS_H = 50;
//�Ǵ�ظ���
//if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE."img/icon_eki/0000.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE_G."img/icon_eki/0000.gif";
if(!isset($D_ICON_EKI_W)) $D_ICON_EKI_W = 19;
if(!isset($D_ICON_EKI_H)) $D_ICON_EKI_H = 24;
if(!isset($D_ICON_EKI_OFFSET_X)) $D_ICON_EKI_OFFSET_X = -10;
if(!isset($D_ICON_EKI_OFFSET_Y)) $D_ICON_EKI_OFFSET_Y = -12;
//�Ǵ���߸���
//if(!isset($D_ICON_POI_IMAGE_DIR)) $D_ICON_POI_IMAGE_DIR = $D_DIR_BASE."img/icon_poi/";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_POI_IMAGE_DIR)) $D_ICON_POI_IMAGE_DIR = $D_DIR_BASE_G."img/icon_poi/";
if(!isset($D_ICON_POI_W)) $D_ICON_POI_W = 16;
if(!isset($D_ICON_POI_H)) $D_ICON_POI_H = 16;
if(!isset($D_ICON_POI_OFFSET_X)) $D_ICON_POI_OFFSET_X = -8;
if(!isset($D_ICON_POI_OFFSET_Y)) $D_ICON_POI_OFFSET_Y = -8;
//������������ʥ���å��Ͽ����ѡ�
if(!isset($D_ICON_NUM_POINT_IMAGE)) $D_ICON_NUM_POINT_IMAGE = $D_DIR_BASE."img/icon_num/mi%02d.gif";	//�ݥ����
if(!isset($D_ICON_NUM_CUBE_IMAGE)) $D_ICON_NUM_CUBE_IMAGE = $D_DIR_BASE."img/icon_num/li%02d.gif";	//�ͳ�
if(!isset($D_ICON_NUM_POINT_OFFSET_X)) $D_ICON_NUM_POINT_OFFSET_X = 0;
if(!isset($D_ICON_NUM_POINT_OFFSET_Y)) $D_ICON_NUM_POINT_OFFSET_Y = -14;
// icn��ά���Υǥե���ȥ�������ʡ���0��ɽ�����ʤ���1��ɽ������		add 2008/12/18 Y.Matsukawa
if(!isset($D_DEFAULT_ICN)) $D_DEFAULT_ICN = 0;
// �����ǡ����ȥ�ߥ�		add 2012/06/21 Y.Matsukawa
if(!isset($D_SHOPDATA_TRIM_WIDTH)) $D_SHOPDATA_TRIM_WIDTH = array();	// �ȥ�ߥ����ʥХ��ȿ���
if(!isset($D_SHOPDATA_TRIM_MARKER)) $D_SHOPDATA_TRIM_MARKER = array();	// �ȥ�ߥ󥰸���Ϳʸ����
if(!isset($D_SHOPDATA_TRIM_TYPE)) $D_SHOPDATA_TRIM_TYPE = array();		// 1:�ޡ������ޤ�ƻ������ȥ�ࡢ2���������˥ȥ���ޡ�������Ϳ


//TIPSɽ�� -------------------------------------------------
if(!isset($D_TIPS_OFFSET_X)) $D_TIPS_OFFSET_X    = 15;
if(!isset($D_TIPS_OFFSET_Y)) $D_TIPS_OFFSET_Y    = 15;
if(!isset($D_TIPS_FONT)) $D_TIPS_FONT        = "10pt serif";
if(!isset($D_TIPS_BGCOLOR)) $D_TIPS_BGCOLOR     = "white";
if(!isset($D_TIPS_BORDERWIDTH)) $D_TIPS_BORDERWIDTH = 1;
if(!isset($D_TIPS_SHADOWFLG)) $D_TIPS_SHADOWFLG = "true";
if(!isset($D_TIPS_SHADOWX)) $D_TIPS_SHADOWX = 3;
if(!isset($D_TIPS_SHADOWY)) $D_TIPS_SHADOWY = 3;
if(!isset($D_TIPS_OPACITY)) $D_TIPS_OPACITY = 30;


// �롼��õ���� --------------------------------------------
if(!isset($D_ROUTE_CAR_WIDTH)) $D_ROUTE_CAR_WIDTH   = "5";// ��
if(!isset($D_ROUTE_CAR_OPACITY)) $D_ROUTE_CAR_OPACITY = "0.5";// Ʃ����
if(!isset($D_ROUTE_CAR_COLOR)) $D_ROUTE_CAR_COLOR   = "#0000ff";//��
if(!isset($D_ROUTE_WALK_WIDTH)) $D_ROUTE_WALK_WIDTH   = "5";// ��
if(!isset($D_ROUTE_WALK_OPACITY)) $D_ROUTE_WALK_OPACITY = "0.5";// Ʃ����
if(!isset($D_ROUTE_WALK_COLOR)) $D_ROUTE_WALK_COLOR   = "#0000ff";//��
//��������������������
//if(!isset($D_ROUTE_START_IMAGE)) $D_ROUTE_START_IMAGE = $D_DIR_BASE."img/route/RouteStart.png";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_START_IMAGE)) $D_ROUTE_START_IMAGE = $D_DIR_BASE_G."img/route/RouteStart.png";
//if(!isset($D_ROUTE_START_GIF)) $D_ROUTE_START_GIF = $D_DIR_BASE."img/route/RouteStart.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_START_GIF)) $D_ROUTE_START_GIF = $D_DIR_BASE_G."img/route/RouteStart.gif";
if(!isset($D_ROUTE_START_OFFSET_X)) $D_ROUTE_START_OFFSET_X = -4;
if(!isset($D_ROUTE_START_OFFSET_Y)) $D_ROUTE_START_OFFSET_Y = -36;
//������������������
//if(!isset($D_ROUTE_GOAL_IMAGE)) $D_ROUTE_GOAL_IMAGE = $D_DIR_BASE."img/route/RouteEnd.png";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_GOAL_IMAGE)) $D_ROUTE_GOAL_IMAGE = $D_DIR_BASE_G."img/route/RouteEnd.png";
//if(!isset($D_ROUTE_GOAL_GIF)) $D_ROUTE_GOAL_GIF = $D_DIR_BASE."img/route/RouteEnd.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_GOAL_GIF)) $D_ROUTE_GOAL_GIF = $D_DIR_BASE_G."img/route/RouteEnd.gif";
if(!isset($D_ROUTE_GOAL_OFFSET_X)) $D_ROUTE_GOAL_OFFSET_X = -4;
if(!isset($D_ROUTE_GOAL_OFFSET_Y)) $D_ROUTE_GOAL_OFFSET_Y = -36;


// �������� ------------------------------------------------
//���ڤ�ʸ��
if(!isset($D_HISTORY_SEP)) $D_HISTORY_SEP = "&nbsp;&gt;&nbsp;";
//TOP����
if(!isset($D_HISTORY_TOP_NAME)) $D_HISTORY_TOP_NAME = $D_USER_DEFNAME."����TOP";


// Maplink ------------------------------------------------
//����ʸ������³�Υޥå��󥰽����ɽ������			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_DISP)) $D_ADDR_MATCH_DISP = 0;
//����ʸ������³�Υޥå��󥰽��� ����ʸ��			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_HEAD)) $D_ADDR_MATCH_HEAD = '';
//����ʸ������³�Υޥå��󥰽��� ����ʸ��			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_TAIL)) $D_ADDR_MATCH_TAIL = '';
//����ʸ������³�Υޥå��󥰽��� ����ʸ��			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_EXP)) $D_ADDR_MATCH_EXP = '';

?>