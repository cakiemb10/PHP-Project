<?php
// ------------------------------------------------------------
// ����ե����� �ǥ�����˴ؤ������
// 
// 2011/03/10 Y.Matsukawa	��������
// 2011/05/12 Y.Matsukawa	�ƥ�ץ졼�������б�
// 2011/05/23 Y.Matsukawa	�ƥ�ץ졼�������б�
// 2011/07/13 Y.Matsukawa	��ǽ�ɲáʥ롼��õ�����Ǵ�ء�
// 2011/08/08 Y.Matsukawa	��ǽ�ɲáʹʤ���߳�ĥ���������ꥢ�������إꥹ�ȸ�����
// 2011/08/11 H.Osamoto		�Ͽްʳ�ɽ���ΰ���������
// 2011/12/26 K.Masuda 		�Ͽްʳ�ɽ���ΰ���������ʲ���������
// 2012/03/04 K.Masuda		p_f��p_s�ѥ�᡼������������ɲ�
// 2012/07/18 Y.Matsukawa	�Ǵ����
// 2012/11/15 Y.Matsukawa	JCN�����������
// 2012/12/17 H.Osamoto		���������̹�������������ޥ���
// 2014/09/11 Y.Matsukawa	�̼ܥܥ���ʾ���������
// 2015/02/10 Y.Matsukawa	Ź�ޥꥹ�ȸ���TOP
// 2015/10/30 N.Wada		�᤭�Ф��������ޥ���
//							MarkerClusterer��������Υ�����������
//							Google Maps�ǥ���ȥ��������ɽ��
// 2016/03/03 Y.Matsukawa	�Ͽޥ�����������
// 2016/03/22 N.Wada		���������������������������֤�ؤ��ѥ������ɲ�
// 2016/03/23 N.Wada		Google Maps�ǵ��������Ѥ��ȼ�UI�ɲ�
// 2016/03/25 N.Wada		��������������������������������������⤵�ɲ�
// 2016/12/19 N.Wada		Google Maps��ɸ�ॺ����ܥ���ΰ����ɲ�
// 2017/01/21 N.Wada		�롼����������ż��Ѥ����������ɲ�
// ------------------------------------------------------------

//��Ź�ޡפ�ɸ��θƤ���
//if(!isset($D_USER_DEFNAME)) $D_USER_DEFNAME = 'Ź��';		mod 2011/05/23 Y.Matsukawa
if(!isset($D_SHOP_NAME)) $D_SHOP_NAME = 'Ź��';

// HTML�����ȥ�
//if(!isset($D_TITLE)) $D_TITLE = $D_USER_DEFNAME.'����';	mod 2011/05/23 Y.Matsukawa
if(!isset($D_TITLE)) $D_TITLE = $D_SHOP_NAME.'����';

// Ź�ޥե꡼������ϥ�����ɽ��
if(!isset($D_SHOP_FW_INIT)) $D_SHOP_FW_INIT = 'Ź��̾';
// ���ָ����ե꡼������ϥ�����ɽ��
if(!isset($D_PL_FW_INIT)) $D_PL_FW_INIT = '�ء����ꡦ����';

// �־������ץܥ���ɽ��		add 2011/05/12 Y.Matsukawa
if(!isset($D_PLBTN_TXT)) $D_PLBTN_TXT = '������ꤹ��';

// �ʤ���߾�勵���ȥ�
if(!isset($D_FILTER_TITLE)) $D_FILTER_TITLE = '���ƥ������ꤹ��';
if(!isset($D_COND_BTN))    $D_COND_BTN = '�ʤ���߾�����ꤹ��';		// add 2011/08/08 Y.Matsukawa
if(!isset($D_COND_BTN_ON)) $D_COND_BTN_ON = '�ʤ���߾�� ����Ѥ�';	// add 2011/08/08 Y.Matsukawa

// �Ͽ� ----------------------------------------------
// �Ͽޥ�����		add 2011/05/23 Y.Matsukawa
if(!isset($D_MAP_TYPE)) $D_MAP_TYPE = 9;
// �Ͽްʳ�ɽ���ΰ�ʺǴ��Ź���Ͽޡ�	add 2011/08/11 H.osamoto
if(!isset($D_NMAP_ANY_DISP_PX)) $D_NMAP_ANY_DISP_PX = 0;
if(!isset($D_NMAP_ANY_DISP_PY)) $D_NMAP_ANY_DISP_PY = 0;	// add 2011/12/26 K.Masuda
// �Ͽްʳ�ɽ���ΰ��Ź���Ͽޡ�	add 2011/08/11 H.osamoto
if(!isset($D_MAP_ANY_DISP_PX)) $D_MAP_ANY_DISP_PX = 0;
if(!isset($D_MAP_ANY_DISP_PY)) $D_MAP_ANY_DISP_PY = 0;	// add 2011/12/26 K.Masuda
// �Ͽޥ����������ʾ����ǻ����		add 2016/03/03 Y.Matsukawa
if(!isset($D_NMAP_SIZE_PER_H)) $D_NMAP_SIZE_PER_H = 0.0;
// �̼ܥܥ��󥵥���		add 2014/09/11 Y.Matsukawa
if(!isset($D_LVL_BTN_SIZE)) $D_LVL_BTN_SIZE = '';
//Google Maps�ǵ��������Ѥ��ȼ�UI	add 2016/03/23 N.Wada
if(!isset($D_GOOGLEMAPS_EMAP_ORIGINAL_UI)) $D_GOOGLEMAPS_EMAP_ORIGINAL_UI = 0;	//0:�Ȥ�ʤ���1:�Ȥ�
//Google Maps�ǥ���ȥ��������ɽ��	add 2015/10/30
if(!isset($D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE = 0;	//�ޥåץ������ڤ��ؤ�����ȥ�����
if(!isset($D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE = 0;	//�ʥӥ�������󥳥�ȥ�����
if(!isset($D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE = 0;	//�������륳��ȥ�����
if(!isset($D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE = 0;	//�����ॳ��ȥ�����
if(!isset($D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE = 0;	//�ѥ󥳥�ȥ�����
if(!isset($D_GOOGLEMAPS_ZOOM_CONTROL_POSITION)) $D_GOOGLEMAPS_ZOOM_CONTROL_POSITION = '';	//�����ॳ��ȥ�������� add 2016/12/19 N.Wada
//�᤭�Ф��������ޥ�������infobox.js��	add 2015/10/30
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM)) $D_GOOGLEMAPS_MSG_CUSTOM = 0;
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM_OPTION)) $D_GOOGLEMAPS_MSG_CUSTOM_OPTION  = "";

// ���ָ����� ----------------------------------------------
// ���ڡ�������
if(!isset($D_SEARCH_LIST_PAGE)) $D_SEARCH_LIST_PAGE  = 10;//�ꥹ�ȷ���

// add 2011/07/13 Y.Matsukawa
// �롼��õ���� --------------------------------------------
if(!isset($D_ROUTE_CAR_WIDTH)) $D_ROUTE_CAR_WIDTH   = "5";// ��
if(!isset($D_ROUTE_CAR_OPACITY)) $D_ROUTE_CAR_OPACITY = "0.5";// Ʃ����
if(!isset($D_ROUTE_CAR_COLOR)) $D_ROUTE_CAR_COLOR   = "#0000ff";//��
if(!isset($D_ROUTE_WALK_WIDTH)) $D_ROUTE_WALK_WIDTH   = "5";// ��
if(!isset($D_ROUTE_WALK_OPACITY)) $D_ROUTE_WALK_OPACITY = "0.5";// Ʃ����
if(!isset($D_ROUTE_WALK_COLOR)) $D_ROUTE_WALK_COLOR   = "#0000ff";//��
if(!isset($D_ROUTE_TRAIN_WIDTH)) $D_ROUTE_TRAIN_WIDTH   = "5";// �����ż��ѡ�	add 2017/01/21 N.Wada
if(!isset($D_ROUTE_TRAIN_OPACITY)) $D_ROUTE_TRAIN_OPACITY = "0.5";// Ʃ���١��ż��ѡ�	add 2017/01/21 N.Wada
if(!isset($D_ROUTE_TRAIN_COLOR)) $D_ROUTE_TRAIN_COLOR   = "#0000ff";//�����ż��ѡ�	add 2017/01/21 N.Wada
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

// ������ --------------------------------------------------
// ���������������
if(!isset($D_ICON_MSGOFFSETX)) $D_ICON_MSGOFFSETX = 0;
if(!isset($D_ICON_MSGOFFSETY)) $D_ICON_MSGOFFSETY = -8;
//������������ȵ������֤δط�	add 2016/03/22 N.Wada
if(!isset($D_ICON_ANCHOR_CENTER_BOTTOM)) $D_ICON_ANCHOR_CENTER_BOTTOM = 0;	// ���������������������ΰ��֤�ؤ�
// �ǥե���ȵ��������������
if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_SHOP_W)) $D_ICON_SHOP_W = 11;
if(!isset($D_ICON_SHOP_H)) $D_ICON_SHOP_H = 11;
// ���������������-NEW
if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE_G."img/new.gif";
if(!isset($D_ICON_NEW_W)) $D_ICON_NEW_W = 23;
if(!isset($D_ICON_NEW_H)) $D_ICON_NEW_H = 10;
// �������륢���������
if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE_G."img/icon_cursor/0000.gif";
if(!isset($D_ICON_CURSOR_W)) $D_ICON_CURSOR_W = 51;
if(!isset($D_ICON_CURSOR_H)) $D_ICON_CURSOR_H = 50;
// �ե������������������
if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE_G."img/icon_cursor/0003.gif";
if(!isset($D_ICON_FOCUS_W)) $D_ICON_FOCUS_W = 51;
if(!isset($D_ICON_FOCUS_H)) $D_ICON_FOCUS_H = 50;
//Ʃ�������������		add 2012/11/15 Y.Matsukawa
if(!isset($D_ICON_TP_IMG)) $D_ICON_TP_IMG = $D_DIR_BASE_G."img/tp11.gif";
if(!isset($D_ICON_TP_W)) $D_ICON_TP_W = 11;
if(!isset($D_ICON_TP_H)) $D_ICON_TP_H = 11;
// �����ꥹ�ȸ���		add 2015/02/10 Y.Matsukawa
if(!isset($D_SHOPA_DISPNM[1])) {
	$D_SHOPA_DISPNM[1][1] = '��ƻ�ܸ�';
	$D_SHOPA_DISPNM[1][2] = '�Զ�Į¼';
}
if(!isset($D_SHOPA_DISPNM[2])) {
	$D_SHOPA_DISPNM[2][1] = '';
	$D_SHOPA_DISPNM[2][2] = '';
}
if(!isset($D_SHOPA_DISPNM[3])) {
	$D_SHOPA_DISPNM[3][1] = '';
	$D_SHOPA_DISPNM[3][2] = '';
}
if(!isset($D_SHOPA_DISPNM[4])) {
	$D_SHOPA_DISPNM[4][1] = '';
	$D_SHOPA_DISPNM[4][2] = '';
}
if(!isset($D_SHOPA_DISPNM[5])) {
	$D_SHOPA_DISPNM[5][1] = '';
	$D_SHOPA_DISPNM[5][2] = '';
}

//�Ǵ�ظ���		add 2011/07/13 Y.Matsukawa
if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE_G."img/icon_eki/0000.gif";
if(!isset($D_ICON_EKI_W)) $D_ICON_EKI_W = 19;
if(!isset($D_ICON_EKI_H)) $D_ICON_EKI_H = 24;
if(!isset($D_ICON_EKI_OFFSET_X)) $D_ICON_EKI_OFFSET_X = -10;
if(!isset($D_ICON_EKI_OFFSET_Y)) $D_ICON_EKI_OFFSET_Y = -12;

//�Ǵ���߸���		add 2012/07/18 Y.Matsukawa
if(!isset($D_ICON_POI_IMAGE_DIR)) $D_ICON_POI_IMAGE_DIR = $D_DIR_BASE_G."img/icon_poi/";
if(!isset($D_ICON_POI_W)) $D_ICON_POI_W = 16;
if(!isset($D_ICON_POI_H)) $D_ICON_POI_H = 16;
if(!isset($D_ICON_POI_OFFSET_X)) $D_ICON_POI_OFFSET_X = -8;
if(!isset($D_ICON_POI_OFFSET_Y)) $D_ICON_POI_OFFSET_Y = -8;

//���������̹����Ѹ����ϥ�������	add 2012/12/17 H.Osamoto
if(!isset($D_ICON_NOW_IMAGE)) $D_ICON_NOW_IMAGE = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_NOW_W)) $D_ICON_NOW_W = 11;
if(!isset($D_ICON_NOW_H)) $D_ICON_NOW_H = 11;
if(!isset($D_ICON_NOW_OFFSET_X)) $D_ICON_NOW_OFFSET_X = 0;
if(!isset($D_ICON_NOW_OFFSET_Y)) $D_ICON_NOW_OFFSET_Y = 0;

// �ɤ߹������å�����
if(!isset($D_WAIT_MSG)) $D_WAIT_MSG = "�ɤ߹�����Ǥ�";

// MarkerClusterer��������Υ��������������markerclustere.js��	add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES)) $D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES  = "";

// ��å�����������ɥ��ط� --------------------------------
// �����᤭�Ф�
if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
	ZdcEmapMsg.setImage('{$D_DIR_BASE_G}img/msg/0002.png',new ZdcSize(242,95),
	                    '{$D_DIR_BASE_G}img/msg/0002-t.png',new ZdcSize(194,67),
	                    '{$D_DIR_BASE_G}img/msg/0002-x.png',new ZdcSize(13,13),
	                    '{$D_DIR_BASE_G}img/msg/0002-s.png',new ZdcSize(13,13),
	                    null);
	ZdcEmapMsg.setDocPosition(0,0,11,8,11,224,55,0);
	ZdcEmapMsg.setDocOffset(-110,-90);
	ZdcEmapMsg.setTextClass('UserMsgWindowTextStyle');
EOF;

// add 2012/03/04 K.Masuda [
if (!isset($D_P_F_MAX)) $D_P_F_MAX = 100;
if (!isset($D_P_S_MAX)) $D_P_S_MAX = 100;
// add 2012/03/04 K.Masuda ]
?>