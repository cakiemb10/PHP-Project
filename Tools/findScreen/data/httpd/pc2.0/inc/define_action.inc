<?php
// ------------------------------------------------------------
// ����ե����� ư��˴ؤ������
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2009/10/13 Y.Matsukawa	�Ǵ����������˾ܺٵ�����Ф��ʤ�
// 2009/10/14 Y.Matsukawa	�ޥ��������Ȥǿ᤭�Ф���ä�
// 2010/06/16 Y.Matsukawa	Standard������³I/F
// 2010/09/13 Y.Matsukawa	�����ܺ�ɽ�����˵���ID��Cookie��¸
// ------------------------------------------------------------
// ���ư��/��������³ -------------------------------------
//�����ӥ�����
if(!isset($D_SEVICE_TYPE)) $D_SEVICE_TYPE ="S";//S:standard L:light N:maplink

//TOP�ڡ���
if(!isset($D_HISTORY_TOP_LINK)) $D_HISTORY_TOP_LINK = "ZdcEmapSearchOpen('','','');";

//JSAPI�Υ����ɤʤɤǥ��顼��ȯ����������������
if(!isset($D_URL_JSAPIERROR)) $D_URL_JSAPIERROR = "http://".$EMAP_SSAPI_SRV."/error/jsapierror.html";

//���ĥ�ե��顼
if(!isset($D_ALLOW_REFERER)) $D_ALLOW_REFERER  = "*";
if(!isset($D_ALLOW_REFERER_NULL)) $D_ALLOW_REFERER_NULL  = 1;//������Ĥ��뤫�ݤ� 0:�Բ� 1:����

//Basicǧ��
if(!isset($D_BASIC_AUTH["dev"])) $D_BASIC_AUTH["dev"] = 0;  //��ȯ�Ķ���Basicǧ��On/Off
if(!isset($D_BASIC_AUTH["test"])) $D_BASIC_AUTH["test"] = 0;//���ڴĶ���Basicǧ��On/Off
if(!isset($D_BASIC_AUTH["www"])) $D_BASIC_AUTH["www"] = 0;  //���ִĶ���Basicǧ��On/Off

//Maplink������³
if(!isset($D_MAPLINK_ADDR_IF)) $D_MAPLINK_ADDR_IF = 0;

//Standard������³			add 2010/06/16 Y.Matsukawa
if(!isset($D_STANDARD_ADDR_IF)) $D_STANDARD_ADDR_IF = 0;

//�Ͽޤν������
if(!isset($D_INIT_LAT)) $D_INIT_LAT = 128456476;
if(!isset($D_INIT_LON)) $D_INIT_LON = 503030954;

//���������
if(!isset($D_INIT_LVL)) $D_INIT_LVL        = 1;//���ɽ��
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH = -1;//���ָ���������-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = -1;//�ܺ�������-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
if(!isset($D_INIT_LVL_PRINT)) $D_INIT_LVL_PRINT   = -1;//�������̡�-1��$D_INIT_LVL�˽स���

//���������ɽ���������Ǿ��̼�
if(!isset($D_VIEW_ICON_MAX)) $D_VIEW_ICON_MAX = 4;
if(!isset($D_VIEW_ICON_MIN)) $D_VIEW_ICON_MIN = 18;

//����Ǿ��̼�
if(!isset($D_MAP_SCALE_MAX)) $D_MAP_SCALE_MAX = 0;
if(!isset($D_MAP_SCALE_MIN)) $D_MAP_SCALE_MIN = 18;

//��������ʳ���ɽ����ʬ
if(!isset($D_DSP_OTHER_KBN)) $D_DSP_OTHER_KBN = 0;

//�Ͽް�ư��ˡ ���󥰥륯��å��Ȥ����֥륯��å��Ȥ���
if(!isset($D_MAP_CLICK_KBN)) $D_MAP_CLICK_KBN = 0;

//�ۥ����륹��������ˤ�륺���� 0:̵�� 1:ͭ��
if(!isset($D_MAP_WHEEL_KBN)) $D_MAP_WHEEL_KBN = 0;


//�������������Ǥ�ư��
if(!isset($D_KYO_ICON_MO)) $D_KYO_ICON_MO = 0;
if(!isset($D_KYO_ICON_CLK)) $D_KYO_ICON_CLK = 1;
if(!isset($D_KYO_ICON_MOUT)) $D_KYO_ICON_MOUT = 0;	// �ޥ��������ȡ�1���᤭�Ф���ä���		add 2009/10/14 Y.Matsukawa



// ���ָ����� ----------------------------------------------
//����ꥹ�ȡ��إꥹ�ȤǤΤ��ʹʹ��ߤ�̵ͭ 0:̵�� 1:ͭ��
if(!isset($D_SEARCH_KANA)) $D_SEARCH_KANA = 0;

//����ꥹ�Ȥ�ɤγ��ؤޤǷ��겼���뤫��1����ƻ�ܸ���2���Զ�Į¼��3�������4�������ܡ�5�����衢6�����֡ʻ��֡�
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 6;

//���縡���ڡ�����
if(!isset($D_SEARCH_MAXPAGE["AddrW"])) $D_SEARCH_MAXPAGE["AddrW"] = 9;
if(!isset($D_SEARCH_MAXPAGE["StW"])) $D_SEARCH_MAXPAGE["StW"]   = 9;
//���� if(!isset($D_SEARCH_MAXPAGE["PoiW"])) $D_SEARCH_MAXPAGE["PoiW"]  = 9;
//���� if(!isset($D_SEARCH_MAXPAGE["ZipW"])) $D_SEARCH_MAXPAGE["ZipW"]  = 9;
if(!isset($D_SEARCH_MAXPAGE["ShopW"])) $D_SEARCH_MAXPAGE["ShopW"] = 9;
//���� if(!isset($D_SEARCH_MAXPAGE["AddrL"])) $D_SEARCH_MAXPAGE["AddrL"] = 9;
//���� if(!isset($D_SEARCH_MAXPAGE["StL"])) $D_SEARCH_MAXPAGE["StL"]   = 9;
//���� if(!isset($D_SEARCH_MAXPAGE["PoiL"])) $D_SEARCH_MAXPAGE["PoiL"]  = 9;
//���� if(!isset($D_SEARCH_MAXPAGE["ShopA"])) $D_SEARCH_MAXPAGE["ShopA"] = 9;

//�ե꡼��ɤǤ���ʸ����ʬ����
if(!isset($D_SEARCH_SRCHMODE_STW)) $D_SEARCH_SRCHMODE_STW = 0;

//���߸��� -------------------
//���ID CORPID
if(!isset($D_SEARCH_CORPID)) $D_SEARCH_CORPID = 'ZDC';
//�����ӥ�ID SRVSID
if(!isset($D_SRARCH_SRVSID)) $D_SRARCH_SRVSID = 'API001';
//�ʹ���ȯ�����
if(!isset($D_SEARCH_POI_SCNT)) $D_SEARCH_POI_SCNT = $D_SEARCH_TABLE_PAGE * 10;
//���ߥե꡼��ɡ����ߥꥹ�Ȥǽ������른���륳���� ��CGI��̤�б��Τ���ư��ʤ�
if(!isset($D_SEARCH_POI_JNRMN_NG)) $D_SEARCH_POI_JNRMN_NG = "";//����  "00140,00160,00270,00280";
if(!isset($D_SEARCH_POI_JNR_NG)) $D_SEARCH_POI_JNR_NG   = "";//����  "00290:00010,00290:00080,00290:00090,00290:00100";



// ���������� ----------------------------------------------
//�Ǵ���� -------------------
//���ڡ�������
if(!isset($D_SHOP_PAGE)) $D_SHOP_PAGE = 10;//�ꥹ�ȤΤ�
if(!isset($D_SHOP_PAGE_DETAIL)) $D_SHOP_PAGE_DETAIL = 3;//�ܺ�ɽ����
//������
if(!isset($D_SHOP_MAX)) $D_SHOP_MAX= 30;
//�������(�����å��ܥå���Ʊ��)
if(!isset($D_SHOP_COND)) $D_SHOP_COND = "OR";
//�������(�����Ʊ��)
if(!isset($D_SHOP_COND_COL)) $D_SHOP_COND_COL = "AND";
//�ܺ�ɽ��������ꥹ�Ⱦä���
if(!isset($D_SHOP_CLOSELIST)) $D_SHOP_CLOSELIST = 0;
//�������̤ǺǴ������򸡺����뤫
if(!isset($D_SHOP_PRINT_SEARCH)) $D_SHOP_PRINT_SEARCH = 1;
//����ԥ�����ʾ��ư�����Ȥ��Τ߸��� -1�ξ��Ƹ������ʤ�
if(!isset($D_SHOP_SEARCHPIX)) $D_SHOP_SEARCHPIX = 5;
//���ַ����θ����ϰ�(m)  0���Ȳ����ϰ�����
if(!isset($D_SHOP_RAD)) $D_SHOP_RAD = 50000;
//�Ƹ������θ����ϰ�(m) 0���Ȳ����ϰ�����
if(!isset($D_SHOP_RAD_RE)) $D_SHOP_RAD_RE = 0;
//�Ǵ����������˾ܺٵ�����ɽ�����ʤ�		add 2009/10/13 Y.Matsukawa
if(!isset($D_SHOP_LIST_NO_DTLSHOP)) $D_SHOP_LIST_NO_DTLSHOP = 0;

//�Ǵ���� -------------------
//�����ϰ�(��������κǴ󸡺���)
if(!isset($D_POI_RAD)) $D_POI_RAD = 10000;
//���ڡ�������
if(!isset($D_POI_PAGE)) $D_POI_PAGE = 5;
//������
if(!isset($D_POI_MAX)) $D_POI_MAX = 50;
//������̤������˸����оݤȤ��륳����
if(!isset($D_POI_JNRMN)) $D_POI_JNRMN = "00160,00250,00140,00170,00220,00240,00130,00110,00120";


//�Ǵ��  -------------------
//�����ϰ�
if(!isset($D_ST_RAD)) $D_ST_RAD = 10000;
//���ڡ�������
if(!isset($D_ST_PAGE)) $D_ST_PAGE = 5;
//������
if(!isset($D_ST_MAX)) $D_ST_MAX = 5;
//�ꥹ����ɽ��
if(!isset($D_HIDE_NEKI_LIST)) $D_HIDE_NEKI_LIST = 1;



// �롼��õ���� --------------------------------------------
if(!isset($D_ROUTE_TIMEOUT)) $D_ROUTE_TIMEOUT = 5000;// �����ॢ���Ȼ���
if(!isset($D_ROUTE_TYPE)) $D_ROUTE_TYPE = 1;// 0:̤���� 1:��Լ�+��ư�� 2:��ư�� 3:��Լ�
if(!isset($D_ROUTE_WALK_PSC)) $D_ROUTE_WALK_PSC = 0;//�������
if(!isset($D_ROUTE_WALK_FLOORFLG)) $D_ROUTE_WALK_FLOORFLG = 0;//���إե饰
if(!isset($D_ROUTE_WALK_DEP_FLOOR)) $D_ROUTE_WALK_DEP_FLOOR = 0;//��ȯ�����إե饰
if(!isset($D_ROUTE_WALK_DEP_STATIONFLG)) $D_ROUTE_WALK_DEP_STATIONFLG = 0;//��ȯ���إե饰
if(!isset($D_ROUTE_WALK_ARR_FLOORFLG)) $D_ROUTE_WALK_ARR_FLOORFLG = 0;//���塧���إե饰
if(!isset($D_ROUTE_WALK_ARR_STATIONFLG)) $D_ROUTE_WALK_ARR_STATIONFLG = 0;//���塧�إե饰
if(!isset($D_ROUTE_WALK_ARR_FLOOR)) $D_ROUTE_WALK_ARR_FLOOR = 0;//���塧����


//����å��Ͽ��������� ----------------------------------------------
//���յ���
if(!isset($D_CLK_SHOP_MAX)) $D_CLK_SHOP_MAX = 50;	//����� �����ޤ�����¿���ȡ���������ž������ǥ��顼�ˤʤä��ꡢIE���Ͽޤ�ɽ������ʤ��ʤä��ꤷ�ޤ���
//�Ǵ��
if(!isset($D_CLK_ST_PAGE)) $D_CLK_ST_PAGE = 5;		//���ڡ������
if(!isset($D_CLK_ST_MAX)) $D_CLK_ST_MAX = 5;		//�����
//�Ǵ����
if(!isset($D_CLK_POI_PAGE)) $D_CLK_POI_PAGE = 5;	//���ڡ������
if(!isset($D_CLK_POI_MAX)) $D_CLK_POI_MAX = 100;	//�����
if(!isset($D_CLK_NPOI_DARKICON_MAX)) $D_CLK_NPOI_DARKICON_MAX = 100;		//���졼�������������ʤ��ޤ�¿���Ȳ�����������
if(!isset($D_CLK_NPOI_DARKICON_MIN_LV)) $D_CLK_NPOI_DARKICON_MIN_LV = 10;	//���졼���������ɽ������Ǿ��̼ܡʤ��ν̼ܤ�ꥺ���ॢ���Ȥ���ȡ����졼���������ɽ������ޤ����


//Cookie��¸ ----------------------------------------------		add 2010/09/13 Y.Matsukawa
if(!isset($D_COOKIE_SHOPDTL_MAX)) $D_COOKIE_SHOPDTL_MAX = 0;		//�����ܺ���¸���
if(!isset($D_COOKIE_SHOPDTL_EXPIRE)) $D_COOKIE_SHOPDTL_EXPIRE = 365;	//�����ܺ���¸���¡�������

?>