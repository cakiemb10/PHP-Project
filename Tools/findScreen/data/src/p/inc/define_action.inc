<?php
// ------------------------------------------------------------
// ����ե����� ư��˴ؤ������
// 
// ��ȯ����
// 2011/10/15 Y.Matsukawa	��������
// 2011/12/20 Y.Matsukawa	�Ͽ������˺Ƹ������ʤ��⡼��
// 2011/12/20 Y.Matsukawa	�ƥ�ץ졼������ե�������ǥ��顼��å����������åȤ��줿�饨�顼����ɽ��
// 2011/12/21 Y.Matsukawa	��ե�������å�����https/http����̤��ʤ��⡼��
// 2012/01/06 Y.Matsukawa	����URL��Ǥ�եѥ�᡼��ʸ������ղ�
// 2012/01/10 Y.Matsukawa	�ܺ�Ź�ޤ�Ǵ������˽Ф��ʤ��Τ������ͤȤ���
// 2012/02/27 Y.Matsukawa	����ID��Cookie��¸��Ǥ�ե��롼�ԥ󥰡�
// 2012/03/08 Y.Matsukawa	Ź�޾ܺټ�������cond�ʤ���ߤ�ͭ���ˤ���
// 2012/03/12 Y.Matsukawa	���ޥۥ�����쥯�ȡʳƼ���³I/F�б���
// 2012/04/16 Y.Matsukawa	Ǥ�ե����Υ�������ID�����
// 2012/08/17 Y.Matsukawa	�롼��õ���ؽи���θ�ʤ���ǥե���Ȳ�
// 2012/11/13 Y.Matsukawa	JCN�����������
// 2012/11/27 Y.Matsukawa	�����̼ܹ���̤����ξ��Ͻ̼��������Ѥ��ʤ�
// 2013/04/19 H.Osamoto		����������������������Ǥ���褦�ѹ�
// 2013/05/14 H.Osamoto		���ɽ���̼ܤ�����Ǥ���褦�ѹ�
// 2013/05/22 H.Osamoto		�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ������������굡ǽ�ɲ�
// 2013/06/13 Y.Matsukawa	Google Maps��
// 2013/07/22 Y.Matsukawa	�ڥ�ޥȱ�͢�����������ޥ�����͹���ֹ渡��0��ξ�硢����TOP������
// 2013/08/09 Y.Matsukawa	͹���ֹ渡����Ǥ�դ������ɽ��
// 2013/09/19 H.Osamoto		����FW������̰�����������򽻽�ꥹ�ȸ����ˤ���
//							����FW������̤�1����ä����˰������̤򥹥��åפ���
// 2013/09/24 Y.Matsukawa	�����ե꡼��ɡʴ������ס˸���
// 2014/02/21 H.Osamoto		�ݥꥴ���⳰Ƚ�ꥫ����ɲ�
// 2014/05/16 Y.Matsukawa	���ʥޥ����б�
// 2014/06/06 Y.Matsukawa	�Ƹ��������Ͽ�ɽ���ϰϳ��⸡���оݤȤ��롣�ʺǴ��Ź�ް�����
// 2014/07/07 Y.Matsukawa	͹���ֹ渡�������������åסʺǴ���Ͽޤ�ľ�����ܡ�
// 2014/08/18 Q.Dai			SiteIconOverlapping
// 2014/08/29 Q.Dai 		BrowsingHistoryDisplay
// 2014/09/08 H.Osamoto		�Ͽ�ɽ���̼��ϰ����µ�ǽ�ɲ�
// 2014/10/08 Y.Matsukawa	�Ǵ��ؤ����Ǥ�յ�Υ�α�ɽ��
// 2014/11/28 Y.Matsukawa	�������֤˥ޡ�����ɽ��
// 2014/12/09 Y.Matsukawa	������������μ�ư��¸��ե饰������
// 2014/12/11 Y.Matsukawa	�Ǵ���Ͽޤ˽���ʸ������³�����ݤΥѥ󤯤�����ٷ�����³���Ѵ�����URL�ˤ���
// 2015/01/26 Y.Matsukawa	�����ȹ��ܤη夢�碌
// 2015/03/18 N.Wada		�����������󤬽Ťʤä����κ����ؤ��ѽ�ʣ��������ID
// 2015/04/09 F.Yokoi		�롼��õ�� �Ͽ޾�ؤΰ�ư��Υ������ɽ���ط��������ѿ����ɲ�
// 2015/05/01 Y.Matsukawa	���֥�&����OMNI���ѺǴ�긡��
// 2015/05/07 Y.Matsukawa	���ꥢ�����裲����NULL�б�
// 2015/05/08 Y.Matsukawa	Ź�ް��������Ƚ����
// 2015/05/14 Y.Matsukawa	cond��nmap/shop_dtl��ľ�ܵ��ҡ�cond.htm̤���ѡ˥⡼��
// 2015/06/08 N.Wada		Google�ǥǥ��ѵ�ǽ�ɲ�
// 2015/08/17 Y.Matsukawa	iPad������쥯���б�
// 2015/08/25 Y.Matsukawa	���ޥۥ�����쥯�ȡ�top.location�ѹ���
// 2015/09/30 Y.Uesugi		Ź�޸����Ǿ�����ɲ�
// 2015/10/20 N.Wada		Google Maps�Ǥ�Ź�޸������ϤΥ��٥���ڤ��ؤ����ɲ�
//							Google Maps��POI�������������ɲ�
//							Google Maps�ǥޡ��������饹���������ɲ�
//							����FW������̰����������������ɲ�
//							����ꥹ�ȸ����ʥ��ꥢ�������������ϡ����ʹ��̡���������ɲá�
//							�������顼�Υƥ�ץ졼�ȤΤ�ɽ�����б�
// 2015/10/23 Y.Uesugi		��ޥȱ�͢ �ĶȽ긡������
// 2015/11/11 Y.Matsukawa	�إå�����charset����
// 2015/11/26 N.Wada		Google Maps�ǥޡ��������饹�����Υ��饹����󥰤����ϰ��ɲ�
// 2016/01/08 Y.Uesugi		�Ͽ��濴�ޡ����β������ѹ���ǽ�ɲ�
// 2016/01/22 H.Yasunaga	711map�˥å�������������ޥ���
// 2016/03/10 Y.Matsukawa	�Ѹ����б��ʽ���ե꡼��ɸ�����
// 2016/03/14 Y.Matsukawa	�᤭�Ф���ʣ���ꥹ�ȡˤ�Ϣ��ɽ��
// 2016/03/17 H.Osamoto		�Ǵ�Ƹ����Զ���б�
// 2016/04/21 H.Osamoto		�̼ܤˤ�륢������ɽ���������
// 2016/04/26 N.Wada		�����ϼ������顼�������������
// 2016/05/13 N.Wada		���������ʣ����Cookie�Υ�����Ǥ�դ�ʸ������ɲ�
//							�ѥ󤯤�Cookie�Υ�����Ǥ�դ�ʸ������ɲ�
// 2016/06/14 Y.Matsukawa	����͹����͹���ֹ渡��
// 2016/06/30 N.Wada		�ܺ٥��顼���Υ�����쥯����URL�ɲ�
// 2016/08/16 Y.Matsukawa	����¬�Ϸ��ݻ�
// 2016/08/25 Y.Uesugi		�롼�Ȥ˥ޡ���ɽ�����ɲ�
// 2016/09/29 Y.Uesugi		������SEO�к�
// 2016/11/10 N.Wada		���ߥ������˥塼��ʣ�����ꤷ�Ƥ�����ϡ��������˥塼������̤�ɽ��
// 2016/11/14 Y.Uesugi		ʣ��ե꡼��ɸ��� ���ꥫ�ʸ����б�
// 2016/11/21 T.Yoshino		���饯��ȯ����������ǽ�ɲ�(����б�)
// 2017/03/13 K.Tani		�Ͽ��濴�ޡ�������offset����
// 2017/02/23 N.Wada		��ȯ�ϻ���ʣ��롼�Ȥΰ�ư���ʤ˥Х�����̵ͭ
// 2017/03/06 N.Wada		��ȯ��ʣ�縡���ѥѥ�᡼�����ɲ�
// 2017/04/14 Y.Matsukawa	Google POI�ʤ�Ź��ɽ��
// 2017/04/21 H.Yasunaga	�������󥭥��ڡ����б��������ޥ���
// 2017/05/11 H.Yasunaga	��ޥȥ��å����������ƥ��������б�
// 2017/05/30 H.Yasunaga	��ޥȥ��å����������ƥ��������б�
// 2017/06/06 Y.Matsukawa	Google POI�ʤ�Ź�˾ܺ٥��ƥ��꡼����
// ------------------------------------------------------------

//�����ڤ��ؤ�		add 2016/03/10 Y.Matsukawa
if(!isset($D_LANG)) $D_LANG = '';

//�쥹�ݥ󥹥إå�charset����		add 2015/11/11 Y.Matsukawa
if(!isset($D_RESPONSE_CHARSET)) $D_RESPONSE_CHARSET = 0;

//�����ӥ�����
if(!isset($D_SERVICE_TYPE)) $D_SERVICE_TYPE ="S";//S:standard L:light N:maplink

//Google Maps��		add 2013/06/13 Y.Matsukawa
if(!isset($D_GOOGLEMAPS)) $D_GOOGLEMAPS = 0;	// Google Maps��
if(!isset($D_GOOGLEMAPS_ICON_CUSTOM)) $D_GOOGLEMAPS_ICON_CUSTOM = 0;	// 0��Google�ǥե���ȥޡ�������1��������������		add 2015/06/08 N.Wada
if(!isset($D_GOOGLEMAPS_SEARCH_EVENT_IDLE)) $D_GOOGLEMAPS_SEARCH_EVENT_IDLE = 0;	// 0��center_changed��zoom_changed���٥�ȡ�1��idle���٥��		add 2015/10/20 N.Wada

//Google Maps��POI��������	add 2015/10/20 N.Wada
if(!isset($D_GOOGLEMAPS_POI_INVISIBLE)) $D_GOOGLEMAPS_POI_INVISIBLE = 0;	// POI����������ɽ��
if(!isset($D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE)) $D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE = 0;	// ����å����˿᤭�Ф���ɽ�����ʤ�
if(!isset($D_GOOGLEMAPS_POI_BUSINESS)) $D_GOOGLEMAPS_POI_BUSINESS = 0;	// POI�ʤ�Ź��ɽ��
if(!isset($D_GOOGLEMAPS_POI_BUSINESS_DETAILS)) $D_GOOGLEMAPS_POI_BUSINESS_DETAILS = null;	// POI�ʤ�Ź�˾ܺ٥��ƥ��꡼����
if(!isset($D_GOOGLEMAPS_POI_EXCLUDE_BUSINESS)) $D_GOOGLEMAPS_POI_EXCLUDE_BUSINESS = 0;	// POI��BUSINESS�ʳ���ɽ��

//Google Maps�ǥޡ��������饹��������markerclustere.js��	add 2015/10/20 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER)) $D_GOOGLEMAPS_MARKER_CLUSTERER = 0;
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE = 0;	// ����å����Υ�����̵��
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG = 0;		// ����å����˿᤭�Ф���ɽ��
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE = 0;	// ���饹����󥰤����ϰ�	add 2015/11/26 N.Wada

// �������ݻ���������¬�Ϸϰ��ٷ��٤����		add 2016/08/16 Y.Matsukawa
if(!isset($D_KYOTEN_WGS_COL)) $D_KYOTEN_WGS_COL = null;

//TOP�ڡ���
if(!isset($D_TOP_PAGE_KBN)) $D_TOP_PAGE_KBN = 0;/*2.0*/
if(!isset($D_HISTORY_TOP_LINK)) $D_HISTORY_TOP_LINK = $D_DIR_BASE_G;/*2.0*/

//�������२�顼������ե�������Ǥ����ѿ��˥��顼��å����������åȤ����ȡ����顼���̤����ܤ��ޤ���	add 2011/12/20 Y.Matsukawa
if(!isset($D_CUST_ERRMSG)) $D_CUST_ERRMSG = '';

//JSAPI�Υ����ɤʤɤǥ��顼��ȯ����������������
if(!isset($D_URL_JSAPIERROR)) $D_URL_JSAPIERROR = "http://".$EMAP_SSAPI_SRV."/error/jsapierror.html";

//���ĥ�ե��顼
if(!isset($D_ALLOW_REFERER)) $D_ALLOW_REFERER  = "*";
if(!isset($D_ALLOW_REFERER_NULL)) $D_ALLOW_REFERER_NULL  = 1;//������Ĥ��뤫�ݤ� 0:�Բ� 1:����
if(!isset($D_ALLOW_REFERER_PROTOCOL)) $D_ALLOW_REFERER_PROTOCOL = 1;//�ץ��ȥ����https/http�� 0:���̤��ʤ� 1:���̤���		add 2011/12/21 Y.Matsukawa

//Basicǧ��
if(!isset($D_BASIC_AUTH["dev"])) $D_BASIC_AUTH["dev"] = 0;  //��ȯ�Ķ���Basicǧ��On/Off
if(!isset($D_BASIC_AUTH["test"])) $D_BASIC_AUTH["test"] = 0;//���ڴĶ���Basicǧ��On/Off
if(!isset($D_BASIC_AUTH["www"])) $D_BASIC_AUTH["www"] = 0;  //���ִĶ���Basicǧ��On/Off

//Maplink������³
if(!isset($D_MAPLINK_ADDR_IF)) $D_MAPLINK_ADDR_IF = 0;

//Standard������³
if(!isset($D_STANDARD_ADDR_IF)) $D_STANDARD_ADDR_IF = 0;

//�Ͽޤν������
if(!isset($D_INIT_LAT)) $D_INIT_LAT = 128456476;
if(!isset($D_INIT_LON)) $D_INIT_LON = 503030954;

//���������
if(!isset($D_INIT_LVL)) $D_INIT_LVL        = 1;//���ɽ��
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH = -1;//���ָ���������-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = -1;//�ܺ�������-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
if(!isset($D_INIT_LVL_PRINT)) $D_INIT_LVL_PRINT   = -1;//�������̡�-1��$D_INIT_LVL�˽स���

// del 2016/04/21 H.Osamoto [
//	//���������ɽ���������Ǿ��̼�
//	if(!isset($D_VIEW_ICON_MAX)) $D_VIEW_ICON_MAX = 4;
//	if(!isset($D_VIEW_ICON_MIN)) $D_VIEW_ICON_MIN = 18;
// del 2016/04/21 H.Osamoto ]

//����Ǿ��̼�
if(!isset($D_MAP_SCALE_MAX)) $D_MAP_SCALE_MAX = 0;
if(!isset($D_MAP_SCALE_MIN)) $D_MAP_SCALE_MIN = 18;

//ɽ���̼��ϰ�	add 2014/09/08 H.Osamoto
if(!isset($D_MAP_ZOOM_RANGE)) $D_MAP_ZOOM_RANGE = '';

//��������ʳ���ɽ����ʬ
if(!isset($D_DSP_OTHER_KBN)) $D_DSP_OTHER_KBN = 0;

//�Ͽް�ư��ˡ ���󥰥륯��å��Ȥ����֥륯��å��Ȥ���
if(!isset($D_MAP_CLICK_KBN)) $D_MAP_CLICK_KBN = 0;

//�ۥ����륹��������ˤ�륺���� 0:̵�� 1:ͭ��
if(!isset($D_MAP_WHEEL_KBN)) $D_MAP_WHEEL_KBN = 0;


//�������������Ǥ�ư��
if(!isset($D_KYO_ICON_MO)) $D_KYO_ICON_MO = 0;
if(!isset($D_KYO_ICON_CLK)) $D_KYO_ICON_CLK = 1;
if(!isset($D_KYO_ICON_MOUT)) $D_KYO_ICON_MOUT = 0;	// �ޥ��������ȡ�1���᤭�Ф���ä���



// ���ָ����� ----------------------------------------------
//����ꥹ�ȡ��إꥹ�ȤǤΤ��ʹʹ��ߤ�̵ͭ 0:̵�� 1:ͭ��
if(!isset($D_SEARCH_KANA)) $D_SEARCH_KANA = 0;

//����ꥹ�Ȥ�ɤγ��ؤޤǷ��겼���뤫��1����ƻ�ܸ���2���Զ�Į¼��3�������4�������ܡ�5�����衢7���ʺǲ��ءˢ�2.0
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 7;

//����ꥹ�ȸ���
if(!isset($D_SEARCH_ADDR_LIST_AREA)) $D_SEARCH_ADDR_LIST_AREA = 0;											// ���ꥢ���� add 2015/10/20 N.Wada
if(!isset($D_SEARCH_ADDR_LIST_OUTPUT_ALL)) $D_SEARCH_ADDR_LIST_OUTPUT_ALL = 0;								// ����ɽ�� add 2015/10/20 N.Wada
if(!isset($D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP)) $D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP = 0;				// ���ʹ��̽��� add 2015/10/20 N.Wada
if(!isset($D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP_ADD_23)) $D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP_ADD_23 = 0;	// ���ʹ��̤�23��Ԥ��ɲ� add 2015/10/20 N.Wada

//����ꥹ�ȸ���(SEO�к�)
if(!isset($D_SEARCH_ADDR_LIST_SEO)) $D_SEARCH_ADDR_LIST_SEO = 0;											// ���ꥢ���� add 2016/0928 Y.Uesugi

//���縡���ڡ�����
if(!isset($D_SEARCH_MAXPAGE["AddrW"])) $D_SEARCH_MAXPAGE["AddrW"] = 9;
if(!isset($D_SEARCH_MAXPAGE["StW"])) $D_SEARCH_MAXPAGE["StW"]   = 9;
if(!isset($D_SEARCH_MAXPAGE["ShopW"])) $D_SEARCH_MAXPAGE["ShopW"] = 9;
if(!isset($D_SEARCH_MAXPAGE["ShopM"])) $D_SEARCH_MAXPAGE["ShopM"] = 9;		// add 2013/09/24 Y.Matsukawa

//�ե꡼��ɤǤ���ʸ����ʬ����
if(!isset($D_SEARCH_SRCHMODE_STW)) $D_SEARCH_SRCHMODE_STW = 0;

//ʣ�縡����2.0
if(!isset($D_COMB_FW_ZIP))  $D_COMB_FW_ZIP  = 1;	//͹���ֹ�ե꡼���
if(!isset($D_COMB_FW_ADDR)) $D_COMB_FW_ADDR = 1;	//����ե꡼���
if(!isset($D_COMB_FW_ADDR_KANA)) $D_COMB_FW_ADDR_KANA = 0;	//����ե꡼���(����)	add 2016/11/14 Y.Uesugi
if(!isset($D_COMB_FW_ST))   $D_COMB_FW_ST   = 1;	//�إե꡼���
if(!isset($D_COMB_FW_POI))  $D_COMB_FW_POI  = 0;	//���ߥե꡼���
if(!isset($D_COMB_FW_SHOP)) $D_COMB_FW_SHOP = 1;	//�����ե꡼���
//ʣ�縡��ɽ�����
if(!isset($D_COMB_FW_ZIP_MAX))  $D_COMB_FW_ZIP_MAX  = 5;	//͹���ֹ�ե꡼���
if(!isset($D_COMB_FW_ADDR_MAX)) $D_COMB_FW_ADDR_MAX = 5;	//����ե꡼���
if(!isset($D_COMB_FW_ST_MAX))   $D_COMB_FW_ST_MAX   = 5;	//�إե꡼���
if(!isset($D_COMB_FW_POI_MAX))  $D_COMB_FW_POI_MAX  = 5;	//���ߥե꡼���
if(!isset($D_COMB_FW_SHOP_MAX)) $D_COMB_FW_SHOP_MAX = 5;	//�����ե꡼���

//��ȯ��ʣ�縡����2.0		add 2017/03/06 N.Wada
if(!isset($D_DEPT_FW_ZIP))  $D_DEPT_FW_ZIP  = 1;	//͹���ֹ�ե꡼���
if(!isset($D_DEPT_FW_ADDR)) $D_DEPT_FW_ADDR = 1;	//����ե꡼���
if(!isset($D_DEPT_FW_ST))   $D_DEPT_FW_ST   = 1;	//�إե꡼���
if(!isset($D_DEPT_FW_POI))  $D_DEPT_FW_POI  = 0;	//���ߥե꡼���
if(!isset($D_DEPT_FW_SHOP)) $D_DEPT_FW_SHOP = 1;	//�����ե꡼���
//��ȯ��ʣ�縡��ɽ�����	add 2017/03/06 N.Wada
if(!isset($D_DEPT_FW_ZIP_MAX))  $D_DEPT_FW_ZIP_MAX  = 5;	//͹���ֹ�ե꡼���
if(!isset($D_DEPT_FW_ADDR_MAX)) $D_DEPT_FW_ADDR_MAX = 5;	//����ե꡼���
if(!isset($D_DEPT_FW_ST_MAX))   $D_DEPT_FW_ST_MAX   = 5;	//�إե꡼���
if(!isset($D_DEPT_FW_POI_MAX))  $D_DEPT_FW_POI_MAX  = 5;	//���ߥե꡼���
if(!isset($D_DEPT_FW_SHOP_MAX)) $D_DEPT_FW_SHOP_MAX = 5;	//�����ե꡼���

//���ꤢ���ޤ����� �����ޤ��������ʤ�:F
if(!isset($D_COMB_FW_ADDR_KANA_AMB)) $D_COMB_FW_ADDR_KANA_AMB = 'T';	//����ե꡼���(����)	add 2016/11/14 Y.Uesugi

// ͹���ֹ渡��0����˸���TOP���ܡʥ�ޥȱ�͢�������ޥ�����		add 2013/07/22 Y.Matsukawa
if(!isset($D_ZIPW0_GOTO_PAGE)) $D_ZIPW0_GOTO_PAGE = '';

// Ǥ�դ�����ǰ���ɽ��		add 2013/08/09 Y.Matsukawa
if(!isset($D_LIST_COLS['ZipW'])) $D_LIST_COLS['ZipW'] = 1;

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
//���ߥե꡼��ɡ����ߥꥹ�Ȥǥ������˥塼������
if(!isset($D_SEARCH_POI_JNRMN_SELECT)) $D_SEARCH_POI_JNRMN_SELECT = 0;	// add 2016/11/14 N.Wada

//�������֤˥ޡ�����ɽ��		add 2014/11/28 Y.Matsukawa
if(!isset($D_SEARCH_MAP_ICON))      $D_SEARCH_MAP_ICON = 0;			// �Ǵ���Ͽޤ˸������֥ޡ�������ɽ��
if(!isset($D_SEARCH_MAP_ICON_DTL))  $D_SEARCH_MAP_ICON_DTL = 0;		// Ź���Ͽޤ˸������֥ޡ�������ɽ��
if(!isset($D_SEARCH_MAP_CENTER))    $D_SEARCH_MAP_CENTER = 0;		// Ź���Ͽޤ򸡺������濴��ɽ��
if(!isset($D_SEARCH_MAP_ICON_IMG))  $D_SEARCH_MAP_ICON_IMG = '';	// �ޡ���������URL
if(!isset($D_SEARCH_MAP_ICON_W))    $D_SEARCH_MAP_ICON_W = 0;		// �ޡ���������width
if(!isset($D_SEARCH_MAP_ICON_H))    $D_SEARCH_MAP_ICON_H = 0;		// �ޡ���������height
if(!isset($D_SEARCH_MAP_ICON_OFX))  $D_SEARCH_MAP_ICON_OFX = 0;		// �ޡ�����������offset
if(!isset($D_SEARCH_MAP_ICON_OFY))  $D_SEARCH_MAP_ICON_OFY = 0;		// �ޡ�����������offset

//�Ͽ��濴�ޡ���		add 2016/01/08 Y.Uesugi
if(!isset($D_MAPCENTER_MARK_IMG))  $D_MAPCENTER_MARK_IMG = '';		// �濴�ޡ�������URL

//�Ͽ��濴�ޡ�������offset	add 2017/03/13 K.Tani
if(!isset($D_MAPCENTER_MARK_IMG_OFX))  $D_MAPCENTER_MARK_IMG_OFX = 0;		// �Ͽ��濴�ޡ������� ��offset
if(!isset($D_MAPCENTER_MARK_IMG_OFY))  $D_MAPCENTER_MARK_IMG_OFY = 0;		// �Ͽ��濴�ޡ������� ��offset

// ���������� ----------------------------------------------
//�Ǵ���� -------------------
//���ڡ�������
if(!isset($D_SHOP_PAGE)) $D_SHOP_PAGE = 10;//�ꥹ�ȤΤ�
if(!isset($D_SHOP_PAGE_DETAIL)) $D_SHOP_PAGE_DETAIL = 3;//�ܺ�ɽ����
if(!isset($D_NSHOPLIST_EXT)) $D_NSHOPLIST_EXT = 0;//�Ƹ��������Ͽ�ɽ���ϰϳ��⸡���оݤȤ���		add 2014/06/06 Y.Matsukawa
//�Ǿ����
//	if(!isset($D_SHOP_MIN)) $D_SHOP_MIN= 0;	//add 2015/09/30 Y.Uesugi	// mod 2016/03/17 H.Osamoto
if(!isset($D_SHOP_MIN)) $D_SHOP_MIN= 1;
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
//if(!isset($D_SHOP_LIST_NO_DTLSHOP)) $D_SHOP_LIST_NO_DTLSHOP = 0;		del 2012/01/10 Y.Matsukawa
//�Ͽ����ǺǴ��Ƹ������ʤ�		add 2011/12/20 Y.Matsukawa
if(!isset($D_SHOP_NO_SEARCH_USER_ACT)) $D_SHOP_NO_SEARCH_USER_ACT = 0;
//Ź�޾ܺټ�������cond�ʤ���ߤ�ͭ���ˤ���		add 2012/03/08 Y.Matsukawa
if(!isset($D_USE_COND_DETAIL)) $D_USE_COND_DETAIL = 0;
//�������
if(!isset($D_KLIST_PAGING)) $D_KLIST_PAGING = 0;	//�ڡ�����̵ͭ	add 2012/05/11 Y.Matsukawa
if(!isset($D_KLIST_PAGE)) $D_KLIST_PAGE = 10;		//���ڡ����Կ�		add 2012/05/11 Y.Matsukawa
//���ꥢ�����Υ����ȷ夢�碌		add // 2015/01/26 Y.Matsukawa	�����Ȼ��ˣ���ᤷ�Ʒ夢�碌
if(!isset($D_AREA_SORT_LPAD)) $D_AREA_SORT_LPAD = array();
//���ꥢ����NULL�ξ���ɽ��ʸ��		add 2015/05/07 Y.Matsukawa
if(!isset($D_SEARCH_SHOPA_DISPNM_NULL)) $D_SEARCH_SHOPA_DISPNM_NULL = "(����¾)";
//Ź�ް��������Ƚ����		add 2015/05/08 Y.Matsukawa
if(!isset($D_SHOPW_KYOTEN_SORT)) $D_SHOPW_KYOTEN_SORT = "";//Ź�ޥե꡼��ɸ���
if(!isset($D_SHOPA_KYOTEN_SORT)) $D_SHOPA_KYOTEN_SORT = "";//���ꥢ����
//cond��nmap/shop_dtl��ľ�ܵ��ҡ�cond.htm̤���ѡ�		add 2015/05/14 Y.Matsukawa
if(!isset($D_COND_STATIC)) $D_COND_STATIC = 0;
// �Ǵ�긡���塢�����ܤ�Ź�ޤΥե�������ɽ������		add 2015/06/08 N.Wada
if(!isset($D_SEARCH_FINISHED_MSG_SHOW)) $D_SEARCH_FINISHED_MSG_SHOW = 0;
// �ե�����ɽ����˺Ƹ��������ݡ�������˥ե�������Ф�ľ��		add 2016/03/14 Y.Matsukawa
if(!isset($D_REFRESH_FUKIDASHI_SEARCH_COMPLETE)) $D_REFRESH_FUKIDASHI_SEARCH_COMPLETE = 0;

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
//���ձؤ���α�����Ⱦ��		add 2014/10/08 Y.Matsukawa
if(!isset($D_STT_CIRCLE_RAD)) $D_STT_CIRCLE_RAD = 1000;	//Ⱦ��
if(!isset($D_STT_CIRCLE_INFO['strokeColor'])) $D_STT_CIRCLE_INFO['strokeColor'] = '#3366FF';	//���ο�
if(!isset($D_STT_CIRCLE_INFO['strokeWeight'])) $D_STT_CIRCLE_INFO['strokeWeight'] = 1;	//��������
if(!isset($D_STT_CIRCLE_INFO['fillColor'])) $D_STT_CIRCLE_INFO['fillColor'] = '#D4E7FB';	//�ɤ�Ĥ֤��ο�
if(!isset($D_STT_CIRCLE_INFO['fillOpacity'])) $D_STT_CIRCLE_INFO['fillOpacity'] = 0.5;	//�ɤ�Ĥ֤���Ʃ����
if(!isset($D_STT_CIRCLE_INFO['lineStyle'])) $D_STT_CIRCLE_INFO['lineStyle'] = 'solid';	//���μ���
if(!isset($D_STT_CIRCLE_INFO['lineOpacity'])) $D_STT_CIRCLE_INFO['lineOpacity'] = 1.0;	//����Ʃ����


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
if(!isset($D_ROUTE_EKI_EXIT)) $D_ROUTE_EKI_EXIT = 0;//�ؽи���θ		add 2012/08/17 Y.Matsukawa
if(!isset($D_ROUTE_DISTANCE_DSP_MAP)) $D_ROUTE_DISTANCE_DSP_MAP = '';// �Ͽ޾�ؤΰ�ư��Υ������ɽ���ե饰		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_LINE_TOLL_FALSE)) $D_ROUTE_LINE_TOLL_FALSE = 0;	//ͭ��ƻϩ��롼�ȸ����оݳ��Ȥ���		add 2016/08/25 Y.Uesugi
if(!isset($D_ROUTE_LINE_PROPERTY_DSP_MAP_WALK)) $D_ROUTE_LINE_PROPERTY_DSP_MAP_WALK = 0;	//�ޡ�����ɽ���������		add 2016/08/25 Y.Uesugi
if(!isset($D_ROUTE_LINE_PROPERTY_DSP_MAP_DRIVE)) $D_ROUTE_LINE_PROPERTY_DSP_MAP_DRIVE = 0;	//�ޡ�����ɽ���ʼ�ư�֡�		add 2016/08/25 Y.Uesugi
if(!isset($D_ROUTE_DISTANCE_DSP_STYLE)) $D_ROUTE_DISTANCE_DSP_STYLE = '';// �Ͽ޾�ؤΰ�ư��Υ������ɽ���ѥ�����������		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_W)) $D_ROUTE_DISTANCE_DSP_W = '';// �Ͽ޾�ؤΰ�ư��Υ�����֤�ɽ��������������		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_H)) $D_ROUTE_DISTANCE_DSP_H = '';// �Ͽ޾�ؤΰ�ư��Υ�����֤�ɽ���������ʹ⤵��	add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_X)) $D_ROUTE_DISTANCE_DSP_X = '';// �Ͽ޾�ؤΰ�ư��Υ�����֤�ɽ�����֡�X������		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_Y)) $D_ROUTE_DISTANCE_DSP_Y = '';// �Ͽ޾�ؤΰ�ư��Υ�����֤�ɽ�����֡�Y������		add 2015/04/09 F.Yokoi
if(!isset($D_SEARCH_COMB_ROUTE_USE_BUS)) $D_SEARCH_COMB_ROUTE_USE_BUS = 0;//��ȯ�ϻ���ʣ��롼�ȡ�0���Х���Ȥ�ʤ���1���Х���Ȥ���	add 2017/02/23 N.Wada


//Cookie��¸ ----------------------------------------------
// ���������ʣ���ˤ���¸��
if(!isset($D_COOKIE_SHOPDTL_AUTOSAVE)) $D_COOKIE_SHOPDTL_AUTOSAVE = 0;		//�����ܺ�ɽ�����˼�ư��¸		add 2014/12/09 Y.Matsukawa
if(!isset($D_COOKIE_SHOPDTL_MAX)) $D_COOKIE_SHOPDTL_MAX = 0;		//�����ܺ���¸���
if(!isset($D_COOKIE_SHOPDTL_EXPIRE)) $D_COOKIE_SHOPDTL_EXPIRE = 365;	//�����ܺ���¸���¡�������
if(!isset($D_COOKIE_SHOPDTL_CGI)) $D_COOKIE_SHOPDTL_CGI = '';
if(!isset($D_COOKIE_SHOPDTL_KEY_ADD)) $D_COOKIE_SHOPDTL_KEY_ADD = '';	//�����ܺ���¸������Ǥ�դ�ʸ�����ɲ�	add 2016/05/13 N.Wada
// add 2012/02/27 Y.Matsukawa [
// �Ǹ�˱�����������������¸
if(!isset($D_COOKIE_KID)) $D_COOKIE_KID = 0;					//����ID��¸
if(!isset($D_COOKIE_KID_DIR)) $D_COOKIE_KID_DIR = "/p/";		//����ID��¸�ǥ��쥯�ȥ�
if(!isset($D_COOKIE_KID_KEY)) $D_COOKIE_KID_KEY = "";			//����ID��¸����ʸ����
if(!isset($D_COOKIE_KID_EXPIRE)) $D_COOKIE_KID_EXPIRE = 365;	//����ID��¸���¡�������
if(!isset($D_COOKIE_KID_REDIRECT)) $D_COOKIE_KID_REDIRECT = 0;	//����ID��¸���˾ܺ٤إ�����쥯��
// add 2012/02/27 Y.Matsukawa ]
// �ѥ󤯤�����¸
if(!isset($D_COOKIE_HISTORY_KEY_ADD)) $D_COOKIE_HISTORY_KEY_ADD = '';	//�ѥ󤯤���¸������Ǥ�դ�ʸ�����ɲ�	add 2016/05/13 N.Wada
$D_P3P_HEADER = 'NOI CUR OUR';			// P3P����ѥ��ȥݥꥷ��	add 2012/06/20 N.Wada
// ===IE���̥ɥᥤ���iframe���ɤ߹���Ǥ⡢����iframe���cookie��ͭ���ˤʤ�=== 

//����ID�����ξ���TOP�إ�����쥯��		add 2012/02/27 Y.Matsukawa
if(!isset($D_KID_NF_REDIRECT)) $D_KID_NF_REDIRECT = 0;

//͹���ֹ渡���إ�����쥯��		add 2012/02/29 Y.Matsukawa
if(!isset($D_REDIRECT_TO_ZIPW)) $D_REDIRECT_TO_ZIPW = 0;
if(!isset($REDIRECT_ZIPW_KW)) $REDIRECT_ZIPW_KW = '';

//͹���ֹ渡�����������åסʺǴ���Ͽޤ�ľ�����ܡ�		add 2014/07/07 Y.Matsukawa
if(!isset($D_ZIPW_SKIP_LIST)) $D_ZIPW_SKIP_LIST = 0;

//���ޥۥ�����쥯��		add 2012/03/12 Y.Matsukawa
if(!isset($D_REDIRECT_SMT_KID)) $D_REDIRECT_SMT_KID = '';			// ����ID��³ 'inf' or 'map'
if(!isset($D_REDIRECT_SMT_ADDR_FW)) $D_REDIRECT_SMT_ADDR_FW = 0;	// ����ե꡼�����³
if(!isset($D_REDIRECT_SMT_EKI_FW)) $D_REDIRECT_SMT_EKI_FW = 0;		// �إե꡼�����³
if(!isset($D_REDIRECT_SMT_ZIP_FW)) $D_REDIRECT_SMT_ZIP_FW = 0;		// ͹���ֹ���³

//���ޥۥ�����쥯�ȡ�top.location�ѹ���		add 2015/08/25 Y.Matsukawa
if(!isset($CUST_JUMP_LOCATION)) $CUST_JUMP_LOCATION = '';		// ������URL


//����URL ----------------------------------------------
if(!isset($D_MBURL_EX)) $D_MBURL_EX = '';		//����URL���ղä���URL�ѥ�᡼��ʸ����		add 2012/01/06 Y.Matsukawa

// Ǥ�ե����Υ�������ID�����		add 2012/04/16 Y.Matsukawa
if(!isset($D_ICONID_COL)) $D_ICONID_COL = '';	// ��������ID���Ǽ���Ƥ��륫���̾�����'col_01' �����������ǡ֥ꥹ��ɽ���ס�PC�ܺ١סְ������̡�����ɬ�פǤ�

// �����ǡ����������Υ������ޥ�������		add 2012/11/13 Y.Matsukawa
if(!isset($D_NKYOTEN_CUST)) $D_NKYOTEN_CUST = '';			// �Ǵ����
if(!isset($D_KYOTENID_CUST)) $D_KYOTENID_CUST = '';			// ����ID
if(!isset($D_KYOTENLIST_CUST)) $D_KYOTENLIST_CUST = '';		// ��������

// JCN�͸����������ޥ����ʱ��پ���ɽ����		add 2012/11/13 Y.Matsukawa
if(!isset($D_JCN_UNKYU_TOP)) $D_JCN_UNKYU_TOP = 0;			// ���پ���ɽ��
if(!isset($D_JCN_UNKYU_JKN)) $D_JCN_UNKYU_JKN = '';			// ���پ���ɽ�����

// �����̼ܥ����		add 2012/11/27 Y.Matsukawa
if(!isset($D_KYOTENLVL_COL_P)) $D_KYOTENLVL_COL_P = '';

// ������������		add 2013/04/19 H.Osamoto
if(!isset($D_NUM_ICON_GIF)) $D_NUM_ICON_GIF = $D_DIR_BASE_G.'img/icon_num/icon_num_';

// ���ɽ���̼�		add 2013/05/14 H.Osamoto
if(!isset($D_INIT_LVL_CSTM)) $D_INIT_LVL_CSTM = 0;

//�Ƹ���
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;	//�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ�������������		add 2013/05/22 H.Osamoto

// ��ޥȱ�͢ �ĶȽ긡������		add 2015/10/23 Y.Uesugi
if(!isset($D_YTC_GET_JIGYOCD['INF'])) $D_YTC_GET_JIGYOCD['INF'] = 0;//�ܺٲ���

// ����FW������̰�����������򽻽�ꥹ�ȸ����ˤ���		add 2013/09/19 H.Osamoto
if(!isset($D_ADDR_FW_TO_LIST)) $D_ADDR_FW_TO_LIST = 0;

// ����FW������̤�1����ä����˰������̤򥹥��åפ���		add 2013/09/19 H.Osamoto
if(!isset($D_ADDR_FW_MONO_RESULT_REDIRECT)) $D_ADDR_FW_MONO_RESULT_REDIRECT = 0;

// ����FW������̰������������Ǵ���Ͽޤˤ���		add 2015/10/20 N.Wada
if(!isset($D_SHOP_FW_TO_NMAP)) $D_SHOP_FW_TO_NMAP = 0;

// �ݥꥴ���⳰Ƚ�ꥫ���		add 2014/02/21 H.Osamoto
if(!isset($D_POLY_COL)) $D_POLY_COL = '';

// ���ʥޥ�������		add 2014/05/16 Y.Matsukawa
if(!isset($D_PRD)) $D_PRD = 0;

//add 2014/08/18 Q.Dai
if(!isset($D_KYO_ICON_OVERLAP)) $D_KYO_ICON_OVERLAP = ''; //Variable set icon on map overlapped.
//add 2014/08/29 Q.Dai
if(!isset($D_KYO_ICON_OVERLAP_ICON_ID)) $D_KYO_ICON_OVERLAP_ICON_ID = ''; // ��ʣ��������ID		add 2015/03/18 N.Wada

// �Ǵ���Ͽޤ˽���ʸ������³�����ݤΥѥ󤯤�����ٷ�����³���Ѵ�����URL�ˤ���		add 2014/12/11 Y.Matsukawa
if(!isset($D_HIS_NMAP_ADDRIF2LLIF)) $D_HIS_NMAP_ADDRIF2LLIF = 0;
// �Ǵ���Ͽޤ˽���ʸ������³�����ݤΥѥ󤯤��˽���ʸ�����ɽ������		add 2015/01/26 Y.Matsukawa
if(!isset($D_HIS_NMAP_ADDRIF_SHOWADDR)) $D_HIS_NMAP_ADDRIF_SHOWADDR = 0;

// ���֥�&����OMNI�ѥ����å�		add 2015/05/01 Y.Matsukawa
if(!isset($D_711OMNI_INIT_JKN)) $D_711OMNI_INIT_JKN = "";	// �Ǵ���������ξ��
if(!isset($D_711OMNI_INIT_RAD)) $D_711OMNI_INIT_RAD = 0;	// �Ǵ�����������ϰ�(m)
if(!isset($D_711OMNI_ALT_RAD)) $D_711OMNI_ALT_RAD = 0;		// �Ǵ����긡���ϰ�(m)

// Ajax��		add 2015/06/08 N.Wada
if(!isset($D_SEARCH_RESULT_AJAX)) $D_SEARCH_RESULT_AJAX = 0;	// ����������search.htm�ˤ�Ajaxɽ������
if(!isset($D_SEARCH_RESULT_TEMPLATE_ONLY)) $D_SEARCH_RESULT_TEMPLATE_ONLY = 0;	// ����������search.htm�˥ƥ�ץ졼�Ȥ�HTML�ΰ���ʬ�Ȥ���ɽ����Ajaxɽ���б���
if(!isset($D_SEARCH_ERROR_TEMPLATE_ONLY)) $D_SEARCH_ERROR_TEMPLATE_ONLY = 0;	// �������顼��search_error.htm�˥ƥ�ץ졼�Ȥ�HTML�ΰ���ʬ�Ȥ���ɽ����Ajaxɽ���б���	add 2015/10/20 N.Wada
if(!isset($D_DETAIL_AJAX)) $D_DETAIL_AJAX = 0;	// �����ܺ١�shop_dtl.htm�ˤ�Ajaxɽ������
if(!isset($D_DETAIL_TEMPLATE_ONLY)) $D_DETAIL_TEMPLATE_ONLY = 0;	// �����ܺ١�shop_dtl.htm�˥ƥ�ץ졼�Ȥ�HTML�ΰ���ʬ�Ȥ���ɽ����Ajaxɽ���б���

// ������쥯��		add 2015/08/17 Y.Matsukawa
if(!isset($D_IPHONE_REDIRECT_SMT))  $D_IPHONE_REDIRECT_SMT = 0;
if(!isset($D_IPAD_REDIRECT_SMT))    $D_IPAD_REDIRECT_SMT = 0;
if(!isset($D_ANDROID_REDIRECT_SMT)) $D_ANDROID_REDIRECT_SMT = 0;

// 711map�˥å�����������å�		add 2016/01/26 H.Osamoto
if(!isset($D_711NISSEN_FIX_ZOOM)) $D_711NISSEN_FIX_ZOOM = "";

// ���߸������顼����������		add 2016/04/26 N.Wada
if(!isset($D_LOC_ERR_URL)) $D_LOC_ERR_URL = '';	// loc.htm

// ����͹����͹���ֹ渡��		add 2016/06/14 Y.Matsukawa
if(!isset($D_JPPOST_SEARCH_ZIP)) $D_JPPOST_SEARCH_ZIP = 0;

// �ܺ٥��顼���Υ�����쥯����URL		add 2016/06/30 N.Wada
if(!isset($D_KID_NOTFOUND_REDIRECT_URL)) $D_KID_NOTFOUND_REDIRECT_URL = "";

// ����ꥹ�Ȱ��ٷ��ٻ���	add 2016/11/21 T.Yoshino
if(!isset($D_LIST_ADDR_CODE))	 $D_LIST_ADDR_CODE	 = array();
if(!isset($D_LIST_ADDR_NAME))	 $D_LIST_ADDR_NAME	 = array();
if(!isset($D_LIST_ADDR_LAT))	 $D_LIST_ADDR_LAT	 = array();
if(!isset($D_LIST_ADDR_LON))	 $D_LIST_ADDR_LON	 = array();

// ����ꥹ�Ȱ��ٷ��ٻ���(FW����)	add 2016/11/21 T.Yoshino
if(!isset($D_LIST_ADDR_CUST))	 $D_LIST_ADDR_CUST	 = array();

// �������󥭥��ڡ����б��������ޥ���	add 2017/04/21 H.Yasunaga
if (!isset($D_LOWSON_CAM_CUST))	$D_LOWSON_CAM_CUST = 0;

// ��ޥ� ���å����������ƥ��������б� add 2017/05/11 H.Yasunaga
if (!isset($D_YTC_SECURITY_CODE)) $D_YTC_SECURITY_CODE = 0;

// ��ޥ� ���å����������ƥ��������б� ľ�ܾܺٲ��̤����ܤ��ʤ� add 2017/05/30 H.Yasunaga
if (!isset($D_YTC_SECURITY_CODE_NO_DIRECT_DTL)) $D_YTC_SECURITY_CODE_NO_DIRECT_DTL = 0;
?>