<?php
// ------------------------------------------------------------
// ����ե����� �ǥ�����˴ؤ������
// 
// ��ȯ����
// 2011/10/15 Y.Matsukawa	��������
// 2012/02/27 Y.Matsukawa	Ź������ꥹ�Ȳ���
// 2012/03/19 Y.Matsukawa	�Ͽޥ���ȥ�����Υ����פ��ѹ���ǽ��
// 2012/10/01 Y.Matsukawa	Maplink�б�
// 2013/08/01 Y.Matsukawa	��ǽ�ɲá�ϩ������
// 2013/09/18 Y.Matsukawa	�����ե꡼��ɡʴ������ס˸���
// 2014/10/06 Y.Matsukawa	Ϣ�֥�������
// 2014/11/28 Y.Matsukawa	Ź�ޥ������󥯥�å��ǰ����γ���Ź�ޤ�Ƭ�Ф�
// 2015/01/28 Y.Matsukawa	�Ǵ�ء��Ǵ���ߤʤɤ�ѥ󤯤����ɲ�
// 2015/03/18 N.Wada		������������˽Ťͤ�Ϣ�֥�������
// 2015/10/20 N.Wada		Google Maps�ǿ᤭�Ф��������ޥ���
//							Google Maps��MarkerClusterer��������Υ�����������
//							Google Maps�ǥ���ȥ��������ɽ��
// 2015/11/19 Y.Matsukawa	����������ɥ��ˡָ������ɽ��
// 2016/02/24 Y.Matsukawa	Ʊ�������ξ���Ϣ�֥��������ޤȤ��
// 2016/03/22 N.Wada		���������������������������֤�ؤ��ѥ������ɲ�
// 2016/03/23 N.Wada		Google Maps�ǵ��������Ѥ��ȼ�UI�ɲ�
// 2016/03/25 N.Wada		��������������������������������������⤵�ɲ�
// 2016/08/15 H.Yasunaga	����͹���б� p_f99(�������ѥե饰)��PC¦�Ǥ�������뤿��
//							���Ѥ��ѥ�᡼��(p_f��p_s)�κ������smt¦�ȹ�碌��
// 2017/02/23 N.Wada		�롼����������ż��Ѥ����������ɲ�
// ------------------------------------------------------------
//��Ź�ޡפ�ɸ��θƤ���
if(!isset($D_USER_DEFNAME)) $D_USER_DEFNAME = "Ź��";
//�֥����ӥ��פ�ɸ��θƤ���
if(!isset($D_USER_SERVICENAME)) $D_USER_SERVICENAME = "�����ӥ�";

// �Ͽ� ----------------------------------------------------
//�̾�⡼�� or �����⡼��
if(!isset($D_MAP_PRINT_MODE)) $D_MAP_PRINT_MODE = 0;//0���̾�⡼�ɡ�1�������⡼��
//�����ॳ��ȥ����� �桼��������ȥ����뤬̵�����-1���ȽФ��ʤ�
//if(!isset($D_MAP_CONTROL)) $D_MAP_CONTROL = 3;		mod 2012/03/19 Y.Matsukawa
if(!isset($D_MAP_CONTROL)) $D_MAP_CONTROL = 1;	// 1���̾2���̼ܥС��ʤ���3��+-�ܥ���Τ�
//�濴����������� -1���ȽФ��ʤ�
if(!isset($D_MAP_CENTER)) $D_MAP_CENTER = -1;
//��������С����� 0���ȽФ��ʤ�
if(!isset($D_MAP_SCALEBAR)) $D_MAP_SCALEBAR = 1;
//����ܥå������� -1���ȽФ��ʤ�
if(!isset($D_MAP_INFO)) $D_MAP_INFO = -1;
//�ϿޤΥ쥤�䡼
if(!isset($D_MAP_LAYER_KBN)) $D_MAP_LAYER_KBN = 1;
//�ɤ߹������ɽ��
if(!isset($D_MAP_WAIT_OFFSETX)) $D_MAP_WAIT_OFFSETX = -60;
if(!isset($D_MAP_WAIT_OFFSETY)) $D_MAP_WAIT_OFFSETY = -12;
if(!isset($D_MAP_WAIT_MSG)) $D_MAP_WAIT_MSG  = "�ɤ߹�����Ǥ�";
//Google Maps�ǵ��������Ѥ��ȼ�UI	add 2016/03/23 N.Wada
if(!isset($D_GOOGLEMAPS_EMAP_ORIGINAL_UI)) $D_GOOGLEMAPS_EMAP_ORIGINAL_UI = 0;	//0:�Ȥ�ʤ���1:�Ȥ�
//Google Maps�ǥ���ȥ��������ɽ��	add 2015/10/20
if(!isset($D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE = 0;	//�ޥåץ������ڤ��ؤ�����ȥ�����
if(!isset($D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE = 0;	//�ʥӥ�������󥳥�ȥ�����
if(!isset($D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE = 0;	//�������륳��ȥ�����
if(!isset($D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE = 0;	//�����ॳ��ȥ�����
if(!isset($D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE = 0;	//�ѥ󥳥�ȥ�����
//Google Maps�ǿ᤭�Ф��������ޥ�������infobox.js��	add 2015/10/20
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM)) $D_GOOGLEMAPS_MSG_CUSTOM = 0;
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM_OPTION)) $D_GOOGLEMAPS_MSG_CUSTOM_OPTION  = "";


// ���ָ����� ----------------------------------------------
//���ڡ�������
if(!isset($D_SEARCH_LIST_PAGE))         $D_SEARCH_LIST_PAGE         = 10;//�ꥹ�ȷ���
if(!isset($D_SEARCH_TABLE_PAGE))        $D_SEARCH_TABLE_PAGE        = 16;//�ơ��֥����
if(!isset($D_SEARCH_SHOPLIST_PAGE))     $D_SEARCH_SHOPLIST_PAGE     = 5;//�����ꥹ��
if(!isset($D_SEARCH_FROUTE_LIST_PAGE))  $D_SEARCH_FROUTE_LIST_PAGE  = 10;//��ȯ�ϻ���롼�Ȥθ����ꥹ��
//�ơ��֥�����Σ��Ԥ����
if(!isset($D_SEARCH_TABLE_COLS))        $D_SEARCH_TABLE_COLS        = 4;
//����̾
if(!isset($D_HISTORY_NAME["AddrW"]))    $D_HISTORY_NAME["AddrW"]    = "����ե꡼���";
if(!isset($D_HISTORY_NAME["StW"]))      $D_HISTORY_NAME["StW"]      = "�إե꡼���";
if(!isset($D_HISTORY_NAME["PoiW"]))     $D_HISTORY_NAME["PoiW"]     = "���ߥե꡼���";
if(!isset($D_HISTORY_NAME["ZipW"]))     $D_HISTORY_NAME["ZipW"]     = "͹���ֹ�ե꡼���";
if(!isset($D_HISTORY_NAME["ShopW"]))    $D_HISTORY_NAME["ShopW"]    = $D_USER_DEFNAME."�ե꡼���";
if(!isset($D_HISTORY_NAME["ShopM"]))    $D_HISTORY_NAME["ShopM"]    = $D_USER_DEFNAME."�ե꡼���";		// add 2013/09/18 Y.Matsukawa
if(!isset($D_HISTORY_NAME["AddrL"]))    $D_HISTORY_NAME["AddrL"]    = "����ꥹ��";
if(!isset($D_HISTORY_NAME["StL"]))      $D_HISTORY_NAME["StL"]      = "�إꥹ��";
if(!isset($D_HISTORY_NAME["LineL"]))    $D_HISTORY_NAME["LineL"]    = "ϩ���ꥹ��";		// add 2013/08/01 Y.Matsukawa
if(!isset($D_HISTORY_NAME["LineStL"]))  $D_HISTORY_NAME["LineStL"]  = "�إꥹ��";		// add 2013/08/01 Y.Matsukawa
if(!isset($D_HISTORY_NAME["PoiL"]))     $D_HISTORY_NAME["PoiL"]     = "���ߥꥹ��";
if(!isset($D_HISTORY_NAME["ShopA"]))    $D_HISTORY_NAME["ShopA"]    = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_2"]))  $D_HISTORY_NAME["ShopA_2"]  = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_3"]))  $D_HISTORY_NAME["ShopA_3"]  = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_4"]))  $D_HISTORY_NAME["ShopA_4"]  = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["ShopA_5"]))  $D_HISTORY_NAME["ShopA_5"]  = $D_USER_DEFNAME."���ꥢ";
if(!isset($D_HISTORY_NAME["Rail"]))     $D_HISTORY_NAME["Rail"]     = "ϩ���޸���";
if(!isset($D_HISTORY_NAME["Area"]))     $D_HISTORY_NAME["Area"]     = "�ϰ�޸���";
if(!isset($D_HISTORY_NAME["List"]))     $D_HISTORY_NAME["List"]     = "�������";
if(!isset($D_HISTORY_NAME["Detail"]))   $D_HISTORY_NAME["Detail"]   = "�ܺ�ɽ��";
//if(!isset($D_HISTORY_NAME["Npoi"]))     $D_HISTORY_NAME["Npoi"]     = "�Ǵ���߸���";		mod 2015/01/28 Y.Matsukawa
if(!isset($D_HISTORY_NAME["Npoi"]))     $D_HISTORY_NAME["Npoi"]     = "���ջ���";
//if(!isset($D_HISTORY_NAME["Neki"]))     $D_HISTORY_NAME["Neki"]     = "�Ǵ�ظ���";		mod 2015/01/28 Y.Matsukawa
if(!isset($D_HISTORY_NAME["Neki"]))     $D_HISTORY_NAME["Neki"]     = "�Ǵ���";
if(!isset($D_HISTORY_NAME["Nshop"]))    $D_HISTORY_NAME["Nshop"]    = $D_USER_DEFNAME."�ꥹ��";
if(!isset($D_HISTORY_NAME["FRoute"]))   $D_HISTORY_NAME["FRoute"]   = "��ȯ�ϻ���롼��";
if(!isset($D_HISTORY_NAME["SPRoute"]))  $D_HISTORY_NAME["SPRoute"]  = "�������֤���롼��";		// add 2015/01/28 Y.Matsukawa
if(!isset($D_HISTORY_NAME["Comb"]))     $D_HISTORY_NAME["Comb"]     = "�ե꡼��ɸ���";
if(!isset($D_HISTORY_NAME["KList"]))    $D_HISTORY_NAME["KList"]    = "��Ź�ް���";		// add 2012/02/27 Y.Matsukawa
//����̾
if(!isset($D_SEL_NAME["AddrW"]))    $D_SEL_NAME["AddrW"]    = "����";
if(!isset($D_SEL_NAME["StW"]))      $D_SEL_NAME["StW"]      = "��";
if(!isset($D_SEL_NAME["PoiW"]))     $D_SEL_NAME["PoiW"]     = "����";
if(!isset($D_SEL_NAME["ZipW"]))     $D_SEL_NAME["ZipW"]     = "����";
if(!isset($D_SEL_NAME["ShopW"]))    $D_SEL_NAME["ShopW"]    = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["ShopM"]))    $D_SEL_NAME["ShopM"]    = $D_USER_DEFNAME;		// add 2013/09/18 Y.Matsukawa
if(!isset($D_SEL_NAME["AddrL"]))    $D_SEL_NAME["AddrL"]    = "����";
if(!isset($D_SEL_NAME["StL"]))      $D_SEL_NAME["StL"]      = "��";
if(!isset($D_SEL_NAME["LineL"]))    $D_SEL_NAME["LineL"]    = "ϩ��";		// add 2013/08/01 Y.Matsukawa
if(!isset($D_SEL_NAME["LineStL"]))  $D_SEL_NAME["LineStL"]  = "��";			// add 2013/08/01 Y.Matsukawa
if(!isset($D_SEL_NAME["PoiL"]))     $D_SEL_NAME["PoiL"]     = "����";
if(!isset($D_SEL_NAME["ShopA"]))    $D_SEL_NAME["ShopA"]    = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["PoiJnr"]))   $D_SEL_NAME["PoiJnr"]   = "������";
if(!isset($D_SEL_NAME["Nshop"]))    $D_SEL_NAME["Nshop"]    = $D_USER_DEFNAME;
//�������ꥢ����ɽ��̾��
if(!$D_SEARCH_SHOPA_DISPNM[1]) $D_SEARCH_SHOPA_DISPNM[1]    = $D_SEL_NAME["AddrL"];//��1����
if(!$D_SEARCH_SHOPA_DISPNM[2]) $D_SEARCH_SHOPA_DISPNM[2]    = $D_SEL_NAME["AddrL"];//��2����
if(!$D_SEARCH_SHOPA_DISPNM[3]) $D_SEARCH_SHOPA_DISPNM[3]    = $D_SEL_NAME["AddrL"];//��1����    ���ꥢ������
if(!$D_SEARCH_SHOPA_DISPNM[4]) $D_SEARCH_SHOPA_DISPNM[4]    = $D_SEL_NAME["AddrL"];//��2����
if(!$D_SEARCH_SHOPA_DISPNM[5]) $D_SEARCH_SHOPA_DISPNM[5]    = $D_SEL_NAME["AddrL"];//��1����    ���ꥢ������
if(!$D_SEARCH_SHOPA_DISPNM[6]) $D_SEARCH_SHOPA_DISPNM[6]    = $D_SEL_NAME["AddrL"];//��2����
if(!$D_SEARCH_SHOPA_DISPNM[7]) $D_SEARCH_SHOPA_DISPNM[7]    = $D_SEL_NAME["AddrL"];//��1����    ���ꥢ������
if(!$D_SEARCH_SHOPA_DISPNM[8]) $D_SEARCH_SHOPA_DISPNM[8]    = $D_SEL_NAME["AddrL"];//��2����
if(!$D_SEARCH_SHOPA_DISPNM[9]) $D_SEARCH_SHOPA_DISPNM[9]    = $D_SEL_NAME["AddrL"];//��1����    ���ꥢ������
if(!$D_SEARCH_SHOPA_DISPNM[10]) $D_SEARCH_SHOPA_DISPNM[10]  = $D_SEL_NAME["AddrL"];//��2����
//����
if(!isset($D_EKI_LANG)) $D_EKI_LANG = '';//��
if(!isset($D_POI_LANG)) $D_POI_LANG = '';//����
//����������ɥ�
if(!isset($D_SEARCHWIN_WAIT_HTML)) $D_SEARCHWIN_WAIT_HTML = '';//�ָ������ɽ��HTML	�����󥰥륯�����ơ������ϴޤ�ʤ��ǲ�����		add 2015/11/19 Y.Matsukawa


// ������ --------------------------------------------------
//���������������
if(!isset($D_ICON_MSGOFFSETX)) $D_ICON_MSGOFFSETX = 0;
if(!isset($D_ICON_MSGOFFSETY)) $D_ICON_MSGOFFSETY = -8;
//������������ȵ������֤δط�	add 2016/03/22 N.Wada
if(!isset($D_ICON_ANCHOR_CENTER_BOTTOM)) $D_ICON_ANCHOR_CENTER_BOTTOM = 0;	// ���������������������ΰ��֤�ؤ�
//�ǥե���ȵ��������������
if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_SHOP_W)) $D_ICON_SHOP_W = 11;
if(!isset($D_ICON_SHOP_H)) $D_ICON_SHOP_H = 11;
//���������������-NEW
if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE_G."img/new.gif";
if(!isset($D_ICON_NEW_W)) $D_ICON_NEW_W = 23;
if(!isset($D_ICON_NEW_H)) $D_ICON_NEW_H = 10;
//�������륢���������
if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE_G."img/icon_cursor/0000.gif";
if(!isset($D_ICON_CURSOR_W)) $D_ICON_CURSOR_W = 51;
if(!isset($D_ICON_CURSOR_H)) $D_ICON_CURSOR_H = 50;
//�ե������������������
if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE_G."img/icon_cursor/0003.gif";
if(!isset($D_ICON_FOCUS_W)) $D_ICON_FOCUS_W = 51;
if(!isset($D_ICON_FOCUS_H)) $D_ICON_FOCUS_H = 50;
//Ʃ�������������		add 2012/10/01 Y.Matsukawa
if(!isset($D_ICON_TP_IMG)) $D_ICON_TP_IMG = $D_DIR_BASE_G."img/tp11.gif";
if(!isset($D_ICON_TP_W)) $D_ICON_TP_W = 11;
if(!isset($D_ICON_TP_H)) $D_ICON_TP_H = 11;
//�Ǵ�ظ���
if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE_G."img/icon_eki/0000.gif";
if(!isset($D_ICON_EKI_W)) $D_ICON_EKI_W = 19;
if(!isset($D_ICON_EKI_H)) $D_ICON_EKI_H = 24;
if(!isset($D_ICON_EKI_OFFSET_X)) $D_ICON_EKI_OFFSET_X = -10;
if(!isset($D_ICON_EKI_OFFSET_Y)) $D_ICON_EKI_OFFSET_Y = -12;
//�Ǵ���߸���
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
// icn��ά���Υǥե���ȥ�������ʡ���0��ɽ�����ʤ���1��ɽ������
if(!isset($D_DEFAULT_ICN)) $D_DEFAULT_ICN = 0;
// Ϣ�֥����������		add 2014/10/06 Y.Matsukawa
if(!isset($D_SEQ_ICON_INFO)) $D_SEQ_ICON_INFO = null;
if(!isset($D_SEQ_ICON_COL)) $D_SEQ_ICON_COL = null;
// ����Ƭ�Ф��طʿ�		add 2014/11/28 Y.Matsukawa
if(!isset($D_NLIST_POP_COLOR)) $D_NLIST_POP_COLOR = '';
// ������������˽Ťͤ�Ϣ�֥�������		add 2015/03/18 N.Wada
if(!isset($D_LAYER_SEQ_ICON)) $D_LAYER_SEQ_ICON = 0;	// 0��ɽ�����ʤ���1��ɽ������
if(!isset($D_LAYER_SEQ_ICON_NAME)) $D_LAYER_SEQ_ICON_NAME = "";
if(!isset($D_LAYER_SEQ_ICON_EXT)) $D_LAYER_SEQ_ICON_EXT = "";
if(!isset($D_LAYER_SEQ_ICON_W)) $D_LAYER_SEQ_ICON_W = 0;
if(!isset($D_LAYER_SEQ_ICON_H)) $D_LAYER_SEQ_ICON_H = 0;
if(!isset($D_LAYER_SEQ_ICON_OX)) $D_LAYER_SEQ_ICON_OX = 0;
if(!isset($D_LAYER_SEQ_ICON_OY)) $D_LAYER_SEQ_ICON_OY = 0;
if(!isset($D_LAYER_SEQ_SAMEPOINT_CLUSTER)) $D_LAYER_SEQ_SAMEPOINT_CLUSTER = 0;	// Ʊ������Ź�ޤ�Ϣ�֤�ޤȤ��		add 2016/02/24 Y.Matsukawa
// Google Maps��MarkerClusterer��������Υ��������������markerclustere.js��	add 2015/10/20 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES)) $D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES  = "";


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
if(!isset($D_ROUTE_TRAIN_WIDTH)) $D_ROUTE_TRAIN_WIDTH   = "5";// �����ż��ѡ�	add 2017/02/23 N.Wada
if(!isset($D_ROUTE_TRAIN_OPACITY)) $D_ROUTE_TRAIN_OPACITY = "0.5";// Ʃ���١��ż��ѡ�	add 2017/02/23 N.Wada
if(!isset($D_ROUTE_TRAIN_COLOR)) $D_ROUTE_TRAIN_COLOR   = "#0000ff";//�����ż��ѡ�	add 2017/02/23 N.Wada
//��������������������
if(!isset($D_ROUTE_START_IMAGE)) $D_ROUTE_START_IMAGE = $D_DIR_BASE_G."img/route/RouteStart.png";
if(!isset($D_ROUTE_START_GIF)) $D_ROUTE_START_GIF = $D_DIR_BASE_G."img/route/RouteStart.gif";
if(!isset($D_ROUTE_START_WIDTH)) $D_ROUTE_START_WIDTH = 54;		// ��	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_START_HEIGHT)) $D_ROUTE_START_HEIGHT = 36;	// �⤵	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_START_OFFSET_X)) $D_ROUTE_START_OFFSET_X = -4;
if(!isset($D_ROUTE_START_OFFSET_Y)) $D_ROUTE_START_OFFSET_Y = -36;
//������������������
if(!isset($D_ROUTE_GOAL_IMAGE)) $D_ROUTE_GOAL_IMAGE = $D_DIR_BASE_G."img/route/RouteEnd.png";
if(!isset($D_ROUTE_GOAL_GIF)) $D_ROUTE_GOAL_GIF = $D_DIR_BASE_G."img/route/RouteEnd.gif";
if(!isset($D_ROUTE_GOAL_WIDTH)) $D_ROUTE_GOAL_WIDTH = 54;		// ��	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_GOAL_HEIGHT)) $D_ROUTE_GOAL_HEIGHT = 36;		// �⤵	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_GOAL_OFFSET_X)) $D_ROUTE_GOAL_OFFSET_X = -4;
if(!isset($D_ROUTE_GOAL_OFFSET_Y)) $D_ROUTE_GOAL_OFFSET_Y = -36;


// �������� ------------------------------------------------
//���ڤ�ʸ��
if(!isset($D_HISTORY_SEP)) $D_HISTORY_SEP = "&nbsp;&gt;&nbsp;";
//TOP����
if(!isset($D_HISTORY_TOP_NAME)) $D_HISTORY_TOP_NAME = $D_USER_DEFNAME."����TOP";


// Maplink ------------------------------------------------
//����ʸ������³�Υޥå��󥰽����ɽ������
if(!isset($D_ADDR_MATCH_DISP)) $D_ADDR_MATCH_DISP = 0;
//����ʸ������³�Υޥå��󥰽��� ����ʸ��
if(!isset($D_ADDR_MATCH_HEAD)) $D_ADDR_MATCH_HEAD = '';
//����ʸ������³�Υޥå��󥰽��� ����ʸ��
if(!isset($D_ADDR_MATCH_TAIL)) $D_ADDR_MATCH_TAIL = '';
//����ʸ������³�Υޥå��󥰽��� ����ʸ��
if(!isset($D_ADDR_MATCH_EXP)) $D_ADDR_MATCH_EXP = '';

// add start 2016/08/15 H.Yasunaga	p_s��p_f�κ������smt¦�˹�碌�� [
//									smt¦��p_s��p_f�κ���������������pc�ϣ��ĤΥ롼�פ�ξ���������뤿��
//									������������1�ĤΤ�
if (!isset($D_P_MAX)) $D_P_MAX = 100;
// add end ]
?>