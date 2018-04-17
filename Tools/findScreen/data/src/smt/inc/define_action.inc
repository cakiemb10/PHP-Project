<?php
// ------------------------------------------------------------
// ����ե����� ư��˴ؤ������
// 
// 2011/03/10 Y.Matsukawa	��������
// 2011/05/23 Y.Matsukawa	�ƥ�ץ졼�������б�
// 2011/07/13 Y.Matsukawa	��ǽ�ɲáʥ롼��õ�����Ǵ�ء�
// 2011/08/08 Y.Matsukawa	��ǽ�ɲáʹʤ���߳�ĥ���������ꥢ�������إꥹ�ȸ�����
// 2012/01/10 N.Wada		�Ͽ������˺Ƹ������ʤ��⡼��
// 2012/01/10 N.Wada		�ƥ�ץ졼������ե�������ǥ��顼��å����������åȤ��줿�饨�顼����ɽ��
// 2012/01/10 N.Wada		��ե�������å�����https/http����̤��ʤ��⡼��
// 2012/01/10 N.Wada		Standard������³
// 2012/01/24 Y.Matsukawa	Ǥ�եѥ�᡼��������Ѥ��ʤ��⡼��
// 2012/03/23 SKC			Maplink������³�б�
// 2012/04/24 Y.Matsukawa	���ߥꥹ�ȸ���
// 2012/05/14 Y.Matsukawa	��������ڡ�����
// 2012/05/23 Y.Matsukawa	��ǽ�ɲá����ָ����塢�Ǵ�����ǤϤʤ����Ǵ��Ͽޤ����ܤ���⡼��
// 2012/07/18 Y.Matsukawa	�Ǵ����
// 2012/10/10 H.Osamoto		Ǥ�ե����Υ�������ID�����
// 2012/11/15 Y.Matsukawa	JCN�����������
// 2012/12/03 Y.Matsukawa	��긡������TOP�����ݤ˥��󥫡���ư
// 2012/12/17 H.Osamoto		���������̹�������������ޥ���
// 2013/01/31 H.Osamoto		��Υɽ���Ѵ���ǽ�ɲ�
// 2013/04/15 H.Osamoto		�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ������������굡ǽ�ɲ�
// 2013/05/30 Y.Matsukawa	����ꥹ�ȡ�adcdʣ����ƻ�ܸ�����
// 2013/07/10 Y.Matsukawa	��ޥȱ�͢�����������ޥ�����CGI�ƤӽФ���
// 2013/07/19 Y.Matsukawa	����ꥹ�Ȥκǲ��̳��ؤ�����ǽ�ˤ���
// 2013/07/29 Y.Matsukawa	�ҥåȷ����¿����票�顼�ˤ���
// 2014/03/07 H.Osamoto		�ݥꥴ���⳰Ƚ�ꥫ����ɲ�
// 2014/07/08 Y.Matsukawa	͹���ֹ渡�������������åסʺǴ�������ľ�����ܡ�
// 2014/08/18 AnPham		SiteIconOverlapping
// 2014/08/26 AnPham		BrowsingHistoryDisplay
// 2014/12/18 Y.Matsukawa	�ڥ�ޥȱ�͢�ۡ����굡���Զ���б��۳��������Ͽޥڡ����򳫤��Ȳ��̥����������˼��Ԥ���
// 2015/01/13 Y.Matsukawa	ϩ���ꥹ�ȸ��� ���������
// 2015/01/26 Y.Matsukawa	�����ȹ��ܤη夢�碌
// 2015/02/02 Y.Matsukawa	jQuery���ɤ߹������
// 2015/03/17 Y.Matsukawa	Ź�ޤ���ξ���nmap�إ�����쥯��
// 2015/04/03 H.Osamoto		�Ǵ��Ͽ�ɽ�����Υǥ��쥤������ɲ�
// 2015/09/29 H.Osamoto		�Ͽ�ɽ�����Υǥ��쥤����ν���ͤ��ѹ�(0��500) iOS9�б�
// 2015/10/30 N.Wada		Google Maps���б�
//							Google Maps��POI�������������ɲ�
//							Google Maps�ǥޡ��������饹���������ɲ�
//							����FW������̰����������������ɲ�
//							�ڥɥ���iD���Ͽޥ������������js�ǹԤ��Τ�̵����
// 							�Ƹ������˽���ʹ�����Ȥ�ʤ��褦�ˤ��뵡ǽ���ɲ�
// 2015/11/18 Xuan Chien	GPS���������б�
// 2015/11/26 N.Wada		Google Maps�ǥޡ��������饹�����Υ��饹����󥰤����ϰ��ɲ�
// 2016/01/20 N.Wada		�����ϼ�������³I/F�Ѳ��̡ˤǺǴ����̤����ܤ���⡼��
// 2016/01/26 H.Osamoto		711map�˥å�������������ޥ���
// 2016/02/15 N.Wada		�����ܺ��Ͽ�ɽ���ε����ǡ����������˵�����������Ϥ���
// 2016/02/22 Y.Matsukawa	�Ǵ��Ͽޤ˺Ǵ����ɽ��
// 2016/03/03 Y.Matsukawa	�Ǵ������Ǥ�ե����ǥ��롼�ԥ�
// 2016/03/03 N.Wada		�������֤˥ޡ�����ɽ��
// 2016/03/06 N.Wada		Ź�޸����Ǿ�����ɲ�
// 2016/03/15 Y.Matsukawa	�����ϼ������顼�������������
// 2016/04/08 Y.Matsukawa	�Ǵ��������Ͽޤκ���������̻���
// 2016/04/26 N.Wada		�����ϼ������顼�����������Ǥ�եѥ�᡼��(freeparms)����Ѥ�
// 2016/06/22 Y.Matsukawa	���롼�ԥ�2�ڡ����ܰʹߤη����������
// 2016/09/28 Y.Matsukawa	POST����
// 2016/11/10 Y.Uesugi		Google Maps API��������
// 2016/11/21 T.Yoshino		���饯��ȯ����������ǽ�ɲ�(����б�)
// 2017/01/17 N.Wada		�롼�ȸ�������FW������Ź�޾ܺپ�������������Υ�����ʣ��롼�ȸ������ڤ��ؤ���
// 2017/01/18 N.Wada		��ȯ�ϻ���ʣ��롼�Ȥΰ�ư���ʤ˥Х�����̵ͭ
// 2017/01/19 N.Wada		����¬�Ϸ��ݻ�
// 2017/02/02 K.Tani		711apl�ѥ������ޥ��� 800m��5km��1�濫��ޤ��б�
// 2017/02/03 K.Tani		711apl�ѥ������ޥ��� ���ɽ�����Ͽ��ϰϤ��ݻ�
//							�Ͽޥ�����������˺Ǵ��ꥹ�Ȥ򹹿����ʤ�
// 2017/03/14 K.Tani		���̥������ѹ������Ͽޥꥵ������Ԥ�ʤ�
// 2017/04/14 H.Yasunaga	����͹�ظ����������ޥ���
// 2017/04/14 N.Wada		�Ǵ������������ե꡼��ɸ������ȼ��ѥ�᡼���ɲ�
// 2017/04/21 N.Wada		ϩ��̾FW�����Σ��ڡ���������η�����������ɲ�
// 2017/04/21 H.Yasunaga	�������󥭥��ڡ����б��������ޥ���
// 2017/04/27 Y.Matsukawa	Google POI�ʤ�Ź��ɽ��
// 2017/05/14 Y.Matsukawa	XSS�к�
// 2017/05/11 H.Yasunaga	��ޥȥ��å����������ƥ��������б�
// ------------------------------------------------------------
// ���ư��/��������³ -------------------------------------
//�����ӥ�����
if(!isset($D_SERVICE_TYPE)) $D_SERVICE_TYPE ="S";//S:standard L:light N:maplink

//�쥹�ݥ󥹥إå�charset����		add 2017/05/14 Y.Matsukawa
if(!isset($D_RESPONSE_CHARSET)) $D_RESPONSE_CHARSET = 0;

// POST����		add 2016/09/28 Y.Matsukawa
if(!isset($D_POST_MODE)) $D_POST_MODE = 0;

//Google Maps��		add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS)) $D_GOOGLEMAPS = 0;	// Google Maps��
if(!isset($D_GOOGLEMAPS_CID)) $D_GOOGLEMAPS_CID = 0;	// ���饤�����ID
if(!isset($D_GOOGLEMAPS_JS)) $D_GOOGLEMAPS_JS = '';		// js�ѥ�
if(!isset($D_GOOGLEMAPS_ICON_CUSTOM)) $D_GOOGLEMAPS_ICON_CUSTOM = 0;	// 0��Google�ǥե���ȥޡ�������1��������������
if(!isset($D_GOOGLEMAPS_WIN_SIZE_SET_DISABLE)) $D_GOOGLEMAPS_WIN_SIZE_SET_DISABLE = 0;		// �Ͽޥ�����������̵����

// add 2016/11/10 Y.Uesugi [
if(!isset($D_GOOGLEMAPS_API_KEY)) $D_GOOGLEMAPS_API_KEY = '';	// Google Maps API Key
if(!isset($D_GOOGLEMAPS_API_KEY_JS)) $D_GOOGLEMAPS_API_KEY_JS = '';		// js�ѥ�
// add 2016/11/10 Y.Uesugi ]

//Google Maps��POI��������	add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS_POI_INVISIBLE)) $D_GOOGLEMAPS_POI_INVISIBLE = 0;	// POI����������ɽ��
if(!isset($D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE)) $D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE = 0;	// ����å����˿᤭�Ф���ɽ�����ʤ�
if(!isset($D_GOOGLEMAPS_POI_BUSINESS)) $D_GOOGLEMAPS_POI_BUSINESS = 0;	// POI�ʤ�Ź��ɽ��

//Google Maps�ǥޡ��������饹��������markerclustere.js��	add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER)) $D_GOOGLEMAPS_MARKER_CLUSTERER = 0;
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE = 0;	// ����å����Υ�����̵��
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG = 0;		// ����å����˿᤭�Ф���ɽ��
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE = 0;	// ���饹����󥰤����ϰ�	add 2015/11/26 N.Wada

//�������२�顼������ե�������Ǥ����ѿ��˥��顼��å����������åȤ����ȡ����顼���̤����ܤ��ޤ���	add 2012/01/10 N.Wada
if(!isset($D_CUST_ERRMSG)) $D_CUST_ERRMSG = '';

//���ĥ�ե��顼
if(!isset($D_ALLOW_REFERER)) $D_ALLOW_REFERER  = "*";
if(!isset($D_ALLOW_REFERER_NULL)) $D_ALLOW_REFERER_NULL  = 1;//������Ĥ��뤫�ݤ� 0:�Բ� 1:����
if(!isset($D_ALLOW_REFERER_PROTOCOL)) $D_ALLOW_REFERER_PROTOCOL = 1;//�ץ��ȥ����https/http�� 0:���̤��ʤ� 1:���̤���		add 2012/01/10 N.Wada

//Basicǧ��
if(!isset($D_BASIC_AUTH["dev"])) $D_BASIC_AUTH["dev"] = 0;  //��ȯ�Ķ���Basicǧ��On/Off
if(!isset($D_BASIC_AUTH["test"])) $D_BASIC_AUTH["test"] = 0;//���ڴĶ���Basicǧ��On/Off
if(!isset($D_BASIC_AUTH["www"])) $D_BASIC_AUTH["www"] = 0;  //���ִĶ���Basicǧ��On/Off

//Standard������³	add 2012/01/10 N.Wada
if(!isset($D_STANDARD_ADDR_IF)) $D_STANDARD_ADDR_IF = 0;

//Maplink������³	add 2012/03/23 SKC
if(!isset($D_MAPLINK_ADDR_IF)) $D_MAPLINK_ADDR_IF = 0;

//���������
if(!isset($D_INIT_LVL)) $D_INIT_LVL = 7;//���ɽ��
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH =  7;//ʬ���Ͽ�
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = 14;//Ź���Ͽ�

//����Ǿ��̼�			add 2011/05/23 Y.Matsukawa
if(!isset($D_MAX_LVL)) $D_MAX_LVL = 1;
if(!isset($D_MIN_LVL)) $D_MIN_LVL = 15;

//�Ͽ�ɽ���ǥ��쥤		add 2014/12/18 Y.Matsukawa
//	if(!isset($D_MAPINIT_DELAY_MS)) $D_MAPINIT_DELAY_MS = 0;//�ߥ���	mod 2015/09/29 H.Osamoto
if(!isset($D_MAPINIT_DELAY_MS)) $D_MAPINIT_DELAY_MS = 500;//�ߥ���

//�Ǵ��Ͽ�ɽ���ǥ��쥤		add 2015/04/03 H.Osamoto
//	if(!isset($D_NMAPINIT_DELAY_MS)) $D_NMAPINIT_DELAY_MS = 0;//�ߥ���	mod 2015/09/29 H.Osamoto
if(!isset($D_NMAPINIT_DELAY_MS)) $D_NMAPINIT_DELAY_MS = 500;//�ߥ���

//�Ͽޥꥵ�������ǥ��쥤		add 2016/03/28 Y.Matsukawa
if(!isset($D_MAP_RESIZE_DELAY_MS)) $D_MAP_RESIZE_DELAY_MS = 500;//�ߥ���

//���̥������ѹ������Ͽޥꥵ�������ʤ�		add 2017/03/14 K.Tani
if(!isset($D_MAP_NO_ORIENTATION_RESIZE_ANDROID)) $D_MAP_NO_ORIENTATION_RESIZE_ANDROID = 0;

//�Ǵ��Ͽ�(nmap.htm)�˺Ǵ������ɽ��		add 2016/02/22 Y.Matsukawa
if(!isset($D_NMAP_AND_NLIST)) $D_NMAP_AND_NLIST = 0;

// �������ݻ���������¬�Ϸϰ��ٷ��٤����		2017/01/19 N.Wada
if(!isset($D_KYOTEN_WGS_COL)) $D_KYOTEN_WGS_COL = null;

// ���ָ����� ----------------------------------------------
//�ե꡼��ɸ������ѡ�1���ء�2�����ꡢ3�����ߡ�
if(!isset($D_SEARCH_AVAILABLE)) $D_SEARCH_AVAILABLE = '1|2|3';

//����ꥹ�Ȥ�ɤγ��ؤޤǷ��겼���뤫��1����ƻ�ܸ���2���Զ�Į¼��3�������4�������ܡ�5�����衢7���ʺǲ��ءˢ�2.0
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 7;

//������塢TOP����餺�Ǵ������ɽ������		add 2012/04/24 Y.Matsukawa
if(!isset($D_DIRECT_SEARCH)) $D_DIRECT_SEARCH = 0;
if(!isset($D_DIRECT_SEARCH_NOTPL)) $D_DIRECT_SEARCH_NOTPL = 0;		//��������ʸ����ϡ�
if(!isset($D_DIRECT_SEARCH_NOTADDR)) $D_DIRECT_SEARCH_NOTADDR = 0;	//��������ʽ���ꥹ�ȡ�
if(!isset($D_DIRECT_SEARCH_NOTEKI)) $D_DIRECT_SEARCH_NOTEKI = 0;	//��������ʱإꥹ�ȡ�
if(!isset($D_DIRECT_SEARCH_NOTPOI)) $D_DIRECT_SEARCH_NOTPOI = 0;	//��������ʻ��ߥꥹ�ȡ�
if(!isset($D_DIRECT_SEARCH_NOTFW)) $D_DIRECT_SEARCH_NOTFW = 0;		//��������ʥե꡼��ɡ�
if(!isset($D_DIRECT_SEARCH_NOTROSEN)) $D_DIRECT_SEARCH_NOTROSEN = 0;	//���������ϩ����		add 2014/03/12 Y.Matsukawa

//������塢�Ǵ�����ǤϤʤ��Ǵ��Ͽޤ����ܤ���		add 2012/05/23 Y.Matsukawa
if(!isset($D_LOCGPS_NMAP)) $D_LOCGPS_NMAP = 0;		//�����ϼ�������³I/F�Ѳ��̡�	add 2016/01/20 N.Wada
if(!isset($D_TOPGPS_NMAP)) $D_TOPGPS_NMAP = 0;		//TOP�����ϼ���
if(!isset($D_PLGPS_NMAP)) $D_PLGPS_NMAP = 0;		//������TOP�����ϼ���
if(!isset($D_TOPPL_NMAP)) $D_TOPPL_NMAP = 0;		//�����긡��
if(!isset($D_ADDRL_NMAP)) $D_ADDRL_NMAP = 0;		//����ꥹ�ȸ���
if(!isset($D_EKIL_NMAP)) $D_EKIL_NMAP = 0;			//�إꥹ�ȸ���
if(!isset($D_POIL_NMAP)) $D_POIL_NMAP = 0;			//���ߥꥹ�ȸ���
if(!isset($D_NLIST_NMAP)) $D_NLIST_NMAP = 0;		//�ե꡼��ɸ���

// ���߸������顼����������		add 2016/03/15 Y.Matsukawa
if(!isset($D_LOC_ERR_URL)) $D_LOC_ERR_URL = '';	// loc.htm
// ���߸������顼�����������Ǥ�եѥ�᡼���ɲ�	add 2016/04/26 N.Wada
if(!isset($D_LOC_ERR_FREE_PRM)) $D_LOC_ERR_FREE_PRM = 0;

//���ڡ���������η��
if(!isset($D_SEARCH_EKIL_PAGE)) $D_SEARCH_EKIL_PAGE = 20;//�إꥹ��		add 2011/08/08 Y.Matsukawa
if(!isset($D_SEARCH_ADDRL_PAGE)) $D_SEARCH_ADDRL_PAGE = 10;//����ꥹ��
if(!isset($D_SEARCH_POIL_PAGE)) $D_SEARCH_POIL_PAGE = 20;//���ߥꥹ��		add 2012/04/24 Y.Matsukawa
if(!isset($D_SEARCH_EKIW_PAGE)) $D_SEARCH_EKIW_PAGE = 10;//�إե꡼���
if(!isset($D_SEARCH_ADDRW_PAGE)) $D_SEARCH_ADDRW_PAGE = 10;//����ե꡼���
if(!isset($D_SEARCH_POIW_PAGE)) $D_SEARCH_POIW_PAGE = 10;//���ߥե꡼���
if(!isset($D_SEARCH_ROSENL_PAGE)) $D_SEARCH_ROSENL_PAGE = 10;//ϩ���ꥹ��		add 2014/03/12 Y.Matsukawa
if(!isset($D_SEARCH_ROSEN_EKIL_PAGE)) $D_SEARCH_ROSEN_EKIL_PAGE = 20;//ϩ���إꥹ��		add 2014/03/12 Y.Matsukawa
if(!isset($D_SEARCH_ROSENW_PAGE)) $D_SEARCH_ROSENW_PAGE = 10;//ϩ���ե꡼���		add 2017/04/21 N.Wada

//������		add 2013/07/29 Y.Matsukawa
if(!isset($D_SEARCH_EKIW_MAXCOUNT))  $D_SEARCH_EKIW_MAXCOUNT  = 10000;
if(!isset($D_SEARCH_ADDRW_MAXCOUNT)) $D_SEARCH_ADDRW_MAXCOUNT = 10000;
if(!isset($D_SEARCH_POIW_MAXCOUNT))  $D_SEARCH_POIW_MAXCOUNT  = 10000;
if(!isset($D_SEARCH_ROSENW_MAXCOUNT))$D_SEARCH_ROSENW_MAXCOUNT= 10000;	// add 2017/04/21 N.Wada

if(!isset($D_SELECT_TODS)) $D_SELECT_TODS = '';//��ƻ�ܸ������|���ڤ������		add 2013/05/30 Y.Matsukawa
if(!isset($D_ADDRLIST_AREA_SKIP)) $D_ADDRLIST_AREA_SKIP = 0;// ����ꥹ�ȸ����������ꥹ����ɽ��		add 2013/05/30 Y.Matsukawa

//͹���ֹ渡�����������åסʺǴ���Ͽޤ�ľ�����ܡ�		add 2014/07/08 Y.Matsukawa
if(!isset($D_ZIPW_SKIP_LIST)) $D_ZIPW_SKIP_LIST = 0;

//���߸���
//���ID CORPID
if(!isset($D_SEARCH_CORPID)) $D_SEARCH_CORPID = 'ZDC';
//�����ӥ�ID SRVSID
if(!isset($D_SRARCH_SRVSID)) $D_SRARCH_SRVSID = 'API001';

// ϩ���ꥹ�ȸ���
if(!isset($D_ROSENLIST_TOP)) $D_ROSENLIST_TOP = 'AREA';// AREA������������TOP������TOP		add 2015/01/13 Y.Matsukawa

//�������֤˥ޡ�����ɽ��		add 2016/03/03 N.Wada
if(!isset($D_SEARCH_MAP_ICON))      $D_SEARCH_MAP_ICON = 0;			// �Ǵ���Ͽޤ˸������֥ޡ�������ɽ��
if(!isset($D_SEARCH_MAP_ICON_IMG))  $D_SEARCH_MAP_ICON_IMG = '';	// �ޡ���������URL
if(!isset($D_SEARCH_MAP_ICON_W))    $D_SEARCH_MAP_ICON_W = 0;		// �ޡ���������width
if(!isset($D_SEARCH_MAP_ICON_H))    $D_SEARCH_MAP_ICON_H = 0;		// �ޡ���������height
if(!isset($D_SEARCH_MAP_ICON_OFX))  $D_SEARCH_MAP_ICON_OFX = 0;		// �ޡ�����������offset
if(!isset($D_SEARCH_MAP_ICON_OFY))  $D_SEARCH_MAP_ICON_OFY = 0;		// �ޡ�����������offset

// ���������� ----------------------------------------------
// �����ե꡼��ɸ��� -------------------
//���ڡ���������η��
if(!isset($D_SEARCH_LIST_PAGE)) $D_SEARCH_LIST_PAGE = 10;
// �����ꥹ�ȸ��� -------------------		add 2011/08/08 Y.Matsukawa
//���ڡ���������η��
if(!isset($D_SEARCH_SHOPLIST_PAGE)) $D_SEARCH_SHOPLIST_PAGE = 10;
//�Ǵ���� -------------------
//���ڡ���������η��
if(!isset($D_NSHOP_LIST_PAGE)) $D_NSHOP_LIST_PAGE = 10;
//�Ǿ����
if(!isset($D_SHOP_MIN)) $D_SHOP_MIN= 1;	//add 2016/03/06 N.Wada
//������
if(!isset($D_SHOP_MAX)) $D_SHOP_MAX= 30;
if(!isset($D_SHOP_MAP_MAX)) $D_SHOP_MAP_MAX = $D_SHOP_MAX;		// �Ͽ޷��		add 2016/04/08 Y.Matsukawa
if(!isset($D_SHOP_LIST_MAX)) $D_SHOP_LIST_MAX = $D_SHOP_MAX;	// �������		add 2016/04/08 Y.Matsukawa
//����ԥ�����ʾ��ư�����Ȥ��Τ߸��� -1�ξ��Ƹ������ʤ�
if(!isset($D_SHOP_SEARCHPIX)) $D_SHOP_SEARCHPIX = 15;
//���ַ����θ����ϰ�(m)  0���Ȳ����ϰ�����
if(!isset($D_SHOP_RAD)) $D_SHOP_RAD = 50000;
if(!isset($D_SHOP_RAD_RE)) $D_SHOP_RAD_RE = 50000;
//�Ͽ����ǺǴ��Ƹ������ʤ�		add 2012/01/10 N.Wada
if(!isset($D_SHOP_NO_SEARCH_USER_ACT)) $D_SHOP_NO_SEARCH_USER_ACT = 0;
//�Ͽ����ǺǴ��ꥹ�Ȥ򹹿����ʤ�		add 2017/02/03 K.Tani
if(!isset($D_SHOP_NO_UPDATE_LIST_USER_ACT)) $D_SHOP_NO_UPDATE_LIST_USER_ACT = 0;
//ʬ���Ͽޤν��ɽ�������ҥåȤ������������꤭��̼ܤ��ѹ�����		add 2012/10/24 Y.Matsukawa
if(!isset($D_SHOP_SCALE_OPT)) $D_SHOP_SCALE_OPT = 1;
//ʬ���Ͽޡʽ̼ܸ���ˤν��ɽ�������Ͽ��ϰϤ˵��������ä���硢����Ⱦ�¤ǺƸ�������	add 2012/10/24 Y.Matsukawa
if(!isset($D_SHOP_SEARCH_RETRY)) $D_SHOP_SEARCH_RETRY = 0;
//ʬ���Ͽ޺Ƹ����塢�ǽ��n�郎���꤭��̼ܤ��ѹ�����		add 2012/10/24 Y.Matsukawa
if(!isset($D_SHOP_SEARCH_RETRY_VCNT)) $D_SHOP_SEARCH_RETRY_VCNT = 0;
//���ꥢ�����Υ����ȷ夢�碌		add // 2015/01/26 Y.Matsukawa	�����Ȼ��ˣ���ᤷ�Ʒ夢�碌
if(!isset($D_AREA_SORT_LPAD)) $D_AREA_SORT_LPAD = array();
//�Ǵ��Ź�ޤ���ξ����Ͽޤ�����		add 2015/03/17 Y.Matsukawa
if(!isset($D_N_0_GOTO_NMAP)) $D_N_0_GOTO_NMAP = 0;
//���ꥢ����NULL�ξ���ɽ��ʸ��		add 2015/05/07 Y.Matsukawa
if(!isset($D_SEARCH_SHOPA_DISPNM_NULL)) $D_SEARCH_SHOPA_DISPNM_NULL = "(����¾)";
//Ź�ް��������Ƚ����		add 2015/05/08 Y.Matsukawa
if(!isset($D_SHOPW_KYOTEN_SORT)) $D_SHOPW_KYOTEN_SORT = "";//Ź�ޥե꡼��ɸ���
if(!isset($D_SHOPA_KYOTEN_SORT)) $D_SHOPA_KYOTEN_SORT = "";//���ꥢ����
if(!isset($D_NLIST_KYOTEN_SORT)) $D_NLIST_KYOTEN_SORT = "";//�Ǵ����		add 2016/03/03 Y.Matsukawa
//Ź�ް������롼�ԥ󥰻���		add 2016/03/03 Y.Matsukawa
if(!isset($D_NLIST_KYOTEN_GRP_COL)) $D_NLIST_KYOTEN_GRP_COL = "";//�Ǵ����
//Ź�ް������롼��̾�Ρ������		add 2016/03/03 Y.Matsukawa
if(!isset($D_NLIST_KYOTEN_GRP_NM)) $D_NLIST_KYOTEN_GRP_NM = null;//�Ǵ����
//Ź�ް������롼����Υڡ������		add 2016/05/23 Y.Matsukawa
if(!isset($D_NLIST_KYOTEN_GRP_CNT_PP)) $D_NLIST_KYOTEN_GRP_CNT_PP = 0;//�Ǵ������1�ڡ����ܡ�
if(!isset($D_NLIST_KYOTEN_GRP_NEXT_CNT_PP)) $D_NLIST_KYOTEN_GRP_NEXT_CNT_PP = $D_NLIST_KYOTEN_GRP_CNT_PP;//�Ǵ������2�ڡ����ܰʹߡ�		add 2016/06/22 Y.Matsukawa
//�Ƹ������˽���ʹ�����Ȥ�ʤ�		add 2015/10/30 N.Wada
if(!isset($D_RESARCH_INIT_COND_UNUSED)) $D_RESARCH_INIT_COND_UNUSED = 0;
//�Ǵ�긡���ˤ���Ŭ�Ѥ���cond		add 2016/02/18 Y.Matsukawa
if(!isset($D_N_COND)) $D_N_COND = "";
//�Ǵ������߸���		add 2016/03/10 Y.Matsukawa
if(!isset($D_NKYOTEN_CIRCLE)) $D_NKYOTEN_CIRCLE = 0;// 1�����ꤷ��Ⱦ��(rad)��ߤ򸡺��ϰϤȤ��롢0�����ꤷ��Ⱦ��(rad)�αߤ����񤹤����򸡺��ϰϤȤ���
//�������ܻ���cond������Ѥ��ʤ���Ĺ��URL�б���		add 2016/03/18 Y.Matsukawa
if(!isset($D_NO_COND_PRM)) $D_NO_COND_PRM = 0;
//Ź�ް����ȼ��ѥ�᡼��ʸ����		add 2017/04/14 N.Wada
if(!isset($D_NLIST_PRM_STR)) $D_NLIST_PRM_STR = "";		//�Ǵ����
if(!isset($D_FWLIST_PRM_STR)) $D_FWLIST_PRM_STR = "";	//Ź�ޥե꡼��ɸ���

// �Ǵ��		add 2011/07/13 Y.Matsukawa
if(!isset($D_SRCH_NEKI)) $D_SRCH_NEKI = 0;
if(!isset($D_NEKI_RAD)) $D_NEKI_RAD = 5000;//�����ϰ�
if(!isset($D_NEKI_ROWS)) $D_NEKI_ROWS = 10;//���ڡ������
if(!isset($D_NEKI_MAX)) $D_NEKI_MAX = 10;//������

// �Ǵ����		add 2012/07/18 Y.Matsukawa
if(!isset($D_SRCH_NPOI)) $D_SRCH_NPOI = 0;
if(!isset($D_NPOI_RAD)) $D_NPOI_RAD = 5000;//�����ϰ�
if(!isset($D_NPOI_ROWS)) $D_NPOI_ROWS = 10;//���ڡ������
if(!isset($D_NPOI_MAX)) $D_NPOI_MAX = 10;//������
//������̤������˸����оݤȤ��륳����
if(!isset($D_NPOI_JNRMN)) $D_NPOI_JNRMN = "00160,00250,00140,00170,00220,00240,00130,00110,00120";


// �������� ----------------------------------------------
// �������������������
if(!isset($D_SHOP_LIST_DIST)) $D_SHOP_LIST_DIST = 'inf';
//�������
if(!isset($D_KLIST_PAGE)) $D_KLIST_PAGE = 10;		//���ڡ����Կ�		2012/05/14 Y.Matsukawa

// �ʤ���߾�� ----------------------------------------------
// filterʣ�����ܻ����COL_xx=1@COL_xx=1�ˤ�Ϣ�����
if (!isset($D_FILTER_U_COND)) $D_FILTER_U_COND = "AND";
// filterʣ�����ܻ����AND�����Ϣ�뤹�����
if (!isset($D_FILTER_EX_AND_COND)) $D_FILTER_EX_AND_COND = array();
// �ꥹ�ȥܥå������
if (!isset($D_FILTER_VAL_LIST)) $D_FILTER_VAL_LIST = array();
if (!isset($D_FILTER_NAME_LIST)) $D_FILTER_NAME_LIST = array();

// add 2011/07/13 Y.Matsukawa
// �롼��õ�� ----------------------------------------------
if(!isset($D_LOC_ROUTE_TYPE)) $D_LOC_ROUTE_TYPE = 0;//�����Ϥ���롼�ȡ�0���ʤ���1����Լԡ�2����ư�֡�
if(!isset($D_NEKI_ROUTE_TYPE)) $D_NEKI_ROUTE_TYPE = 0;//�Ǵ�ؤ���롼�ȡ�0���ʤ���1����Լԡ�2����ư�֡�
if(!isset($D_NPOI_ROUTE_TYPE)) $D_NPOI_ROUTE_TYPE = 0;//�Ǵ���ߤ���롼�ȡ�0���ʤ���1����Լԡ�2����ư�֡�		add 2012/07/18 Y.Matsukawa
if(!isset($D_SEARCH_ROUTE_TYPE)) $D_SEARCH_ROUTE_TYPE = 0;//��ȯ�ϻ���롼�ȡ�0���ʤ���1����Լԡ�2����ư�֡�
if(!isset($D_ROUTE_TIMEOUT)) $D_ROUTE_TIMEOUT = 5000;// �����ॢ���Ȼ���
if(!isset($D_ROUTE_WALK_PSC)) $D_ROUTE_WALK_PSC = 0;//��������0����Υͥ�衢1������ͥ�衢3���ڤ�ƻͥ�衢5�������Τ���ƻͥ���
if(!isset($D_ROUTE_WALK_FLOORFLG)) $D_ROUTE_WALK_FLOORFLG = 0;//���إե饰
if(!isset($D_ROUTE_WALK_DEP_FLOOR)) $D_ROUTE_WALK_DEP_FLOOR = 0;//��ȯ�����إե饰
if(!isset($D_ROUTE_WALK_DEP_STATIONFLG)) $D_ROUTE_WALK_DEP_STATIONFLG = 0;//��ȯ���إե饰
if(!isset($D_ROUTE_WALK_ARR_FLOORFLG)) $D_ROUTE_WALK_ARR_FLOORFLG = 0;//���塧���إե饰
if(!isset($D_ROUTE_WALK_ARR_STATIONFLG)) $D_ROUTE_WALK_ARR_STATIONFLG = 0;//���塧�إե饰
if(!isset($D_ROUTE_WALK_ARR_FLOOR)) $D_ROUTE_WALK_ARR_FLOOR = 0;//���塧����
if(!isset($D_SEARCH_COMB_ROUTE_USE_BUS)) $D_SEARCH_COMB_ROUTE_USE_BUS = 0;//��ȯ�ϻ���ʣ��롼�ȡ�0���Х���Ȥ�ʤ���1���Х���Ȥ���	add 2017/01/18 N.Wada

// Ǥ�եѥ�᡼�� ----------------------------------------------
if(!isset($D_NOT_TRANSFER_FREEPARMS)) $D_NOT_TRANSFER_FREEPARMS = 0;//���̴ְ��Ѥ���0�������Ѥ���1�������Ѥ��ʤ���		add 2012/01/24 Y.Matsukawa

// Ǥ�ե����Υ�������ID�����		add 2012/10/10 H.Osamoto
if(!isset($D_ICONID_COL)) $D_ICONID_COL = '';	// ��������ID���Ǽ���Ƥ��륫���̾�����'col_01' �����������ǡ֥ꥹ��ɽ���ס֥��ޥ۾ܺ١�����ɬ�פǤ�

// ���Ѷ�ʬ���		add 2012/10/10 H.Osamoto
if(!isset($D_ORG_KBN_COL)) $D_ORG_KBN_COL = '';
if(!isset($D_ORG_KBN_NAME_LIST)) $D_ORG_KBN_NAME_LIST = array();

// �����ǡ����������Υ������ޥ�������		add 2012/11/15 Y.Matsukawa
if(!isset($D_NKYOTEN_CUST)) $D_NKYOTEN_CUST = '';			// �Ǵ����
if(!isset($D_KYOTENID_CUST)) $D_KYOTENID_CUST = '';			// ����ID
if(!isset($D_KYOTENLIST_CUST)) $D_KYOTENLIST_CUST = '';		// ��������

// JCN�͸����������ޥ����ʱ��پ���ɽ����		add 2012/11/15 Y.Matsukawa
if(!isset($D_JCN_UNKYU_TOP)) $D_JCN_UNKYU_TOP = 0;			// ���پ���ɽ��
if(!isset($D_JCN_UNKYU_JKN)) $D_JCN_UNKYU_JKN = '';			// ���پ���ɽ�����

// ��긡������TOP����ä����Υ��󥫡�		add 2012/12/03 Y.Matsukawa
if(!isset($D_PL_RETURN_HASH)) $D_PL_RETURN_HASH = '';
if(!isset($D_PL_GPS_RETURN_HASH)) $D_PL_GPS_RETURN_HASH = '';		// �����Ϥξ������̥��󥫡�����

// ���������̹�������������ޥ���		add 2012/12/17 H.Osamoto
if(!isset($D_KANA_DEN)) $D_KANA_DEN = '';			// ���������̹���ե饰

// ��Υɽ���Ѵ�		add 2013/01/31 H.Osamoto
if(!isset($D_DIST_DISP_VARIABLE)) $D_DIST_DISP_VARIABLE = '';

//�Ƹ���
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;	//�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ�������������		add 2013/04/15 H.Osamoto

// ����FW������̰������������Ǵ���Ͽޤˤ���		add 2015/10/30 N.Wada
if(!isset($D_SHOP_FW_TO_NMAP)) $D_SHOP_FW_TO_NMAP = 0;

// ��ޥȱ�͢ �ĶȽ긡������		add 2013/07/10 Y.Matsukawa
if(!isset($D_YTC_GET_JIGYOCD['INF'])) $D_YTC_GET_JIGYOCD['INF'] = 0;//�ܺٲ���

// �ݥꥴ���⳰Ƚ�ꥫ���		add 2014/03/07 H.Osamoto
if(!isset($D_POLY_COL)) $D_POLY_COL = '';

// For SiteIconOverLapping
if(!isset($D_KYO_ICON_OVERLAP)) $D_KYO_ICON_OVERLAP ="";// add 2014/08/18 AnPham

// add 2014/08/26 AnPham [
if(!isset($D_COOKIE_SHOPDTL_MAX)) $D_COOKIE_SHOPDTL_MAX = 0;
if(!isset($D_COOKIE_SHOPDTL_EXPIRE)) $D_COOKIE_SHOPDTL_EXPIRE = 365;
if(!isset($D_COOKIE_SHOPDTL_CGI)) $D_COOKIE_SHOPDTL_CGI = '';
// add 2014/08/26 AnPham ]

// jQuery�ɤ߹������		add 2015/02/02 Y.Matsukawa
if(!isset($D_DISABLE_JQUERY)) $D_DISABLE_JQUERY = 0;

// ���֥�&����OMNI�ѥ����å�		add 2015/05/01 Y.Matsukawa
if(!isset($D_711OMNI_INIT_JKN)) $D_711OMNI_INIT_JKN = "";	// �Ǵ���������ξ��
if(!isset($D_711OMNI_INIT_RAD)) $D_711OMNI_INIT_RAD = 0;	// �Ǵ�����������ϰ�(m)
if(!isset($D_711OMNI_ALT_RAD)) $D_711OMNI_ALT_RAD = 0;		// �Ǵ����긡���ϰ�(m)

// ���֥�&���� 711apl�ѥ����å�		add 2017/02/02 K.Tani
if(!isset($D_711APL_INIT_RAD)) $D_711APL_INIT_RAD = 0;	// �Ǵ�����������ϰ�(m)
if(!isset($D_711APL_ALT_RAD)) $D_711APL_ALT_RAD = 0;	// �Ǵ�������ʳ��������ϰ�(m)

// GPS�������� add 2015/11/18 Xuan Chien
if(!isset($D_SGPS_LOG)) $D_SGPS_LOG = '';

// �����ܺ��Ͽ�ɽ���ε����ǡ����������˵�����������Ϥ���		add 2016/02/15 N.Wada
if(!isset($D_SHOPDTL_MAP_LOG)) $D_SHOPDTL_MAP_LOG = 0;

// 711map�˥å�����������å�		add 2016/01/26 H.Osamoto
if(!isset($D_711NISSEN_FIX_ZOOM)) $D_711NISSEN_FIX_ZOOM = "";

// ����ꥹ�Ȱ��ٷ��ٻ���	add 2016/11/21 T.Yoshino
if(!isset($D_LIST_ADDR_CUST))	 $D_LIST_ADDR_CUST	 = array();

// �롼�ȸ�������FW��������Ź�޾ܺپ������	add 2017/01/17 N.Wada
if(!isset($D_SRCH_FW_GET_SHOPINFO)) $D_SRCH_FW_GET_SHOPINFO = 0;
// �롼�ȸ�������FW��̰����Υ�����ʣ��롼�ȸ������ڤ��ؤ���	add 2017/01/17 N.Wada
if(!isset($D_SRCH_FWLIST_TO_SRCH_ROUTE_COMB)) $D_SRCH_FWLIST_TO_SRCH_ROUTE_COMB = 0;

// �����ϥ롼��õ��������¬�ϷϤǼ¹�		add 2017/01/20 N.Wada
if(!isset($D_ROUTE_SEARCH_MYLOC_WGS)) $D_ROUTE_SEARCH_MYLOC_WGS = 0;

// add 2017/04/14 H.Yasunaga ����͹�ظ����������ޥ��� [
// jppost15����͹�ظ����������ޥ���
if (!isset($D_JPOST_CUSTOM_ENCODE)) $D_JPOST_CUSTOM_ENCODE = 0;
// add 2017/04/14 H.Yasunaga ]

// �������󥭥��ڡ����б��������ޥ���	add 2017/04/21 H.Yasunaga
if (!isset($D_LOWSON_CAM_CUST))	$D_LOWSON_CAM_CUST = 0;

// ��ޥ� ���å����������ƥ��������б� add 2017/05/11 H.Yasunaga
if (!isset($D_YTC_SECURITY_CODE)) $D_YTC_SECURITY_CODE = 0;

?>