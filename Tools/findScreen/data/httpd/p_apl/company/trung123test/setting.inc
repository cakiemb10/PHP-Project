<?PHP
//--------------------------------------------
// E-MAP��ʬ��S������������ɡ�L���饤�ȡ�N���ޥåץ�󥯡�
//--------------------------------------------
$D_SERVICE_TYPE = "S";

//--------------------------------------------
//�쥹�ݥ󥹥إå�charset����
//--------------------------------------------
$D_RESPONSE_CHARSET = 0;

//--------------------------------------------
//��ե��顼ǧ��
//--------------------------------------------
//���ĥ�ե��顼
$D_ALLOW_REFERER  = "*";
//NULL����
$D_ALLOW_REFERER_NULL = 1;

//--------------------------------------------
// ����������IPǧ��
//--------------------------------------------
//����IP
//$D_ALLOW_IP = "";

//--------------------------------------------
//BASICǧ��
//--------------------------------------------
$D_BASIC_AUTH["dev"]  = 0;
$D_BASIC_AUTH["test"] = 0;
$D_BASIC_AUTH["www"]  = 0;

//--------------------------------------------
// SSL��³��https����������
//--------------------------------------------
$D_SSL_ACCESS = 0;

//--------------------------------------------
// iPhone����Υ�����������Ӥإ�����쥯��
//--------------------------------------------
$D_IPHONE_REDIRECT = 0;
//--------------------------------------------
// Android����Υ�����������Ӥإ�����쥯��
//--------------------------------------------
$D_ANDROID_REDIRECT = 0;

//--------------------------------------------
// iPhone����Υ��������򥹥ޥۤإ�����쥯��
//--------------------------------------------
//$D_IPHONE_REDIRECT_SMT = ;
//--------------------------------------------
// iPad����Υ��������򥹥ޥۤإ�����쥯��
//--------------------------------------------
//$D_IPAD_REDIRECT_SMT = ;
//--------------------------------------------
// Android����Υ��������򥹥ޥۤإ�����쥯��
//--------------------------------------------
//$D_ANDROID_REDIRECT_SMT = ;

//--------------------------------------------
// ����URL��https��ɽ��
//--------------------------------------------
//$D_MBURL_HTTPS = ;

//--------------------------------------------
// TOP�ڡ�����ʬ
//--------------------------------------------
$D_TOP_PAGE_KBN = '0';// 0��ɸ��TOP��1������TOP��2��ZDC�¤��asp��

//--------------------------------------------
// TOP�ڡ����Υ��
//--------------------------------------------
//$D_HISTORY_TOP_LINK = "javascript:parent.location.href='';";

//--------------------------------------------
//ɽ��
//--------------------------------------------
//����̾ɽ��ʸ����
$D_USER_DEFNAME = "Ź��";
//�ե饰����ɽ����
$D_USER_SERVICENAME = "�����ӥ�";

//--------------------------------------------
//�Ͽ�ɽ��
//--------------------------------------------
//����Ͽ�ɽ������(����)
$D_INIT_LAT = 128440300;
//����Ͽ�ɽ������(����)
$D_INIT_LON = 503173140;

//���ɽ���̼�
$D_INIT_LVL = 16;
//���ָ��������
//��-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
$D_INIT_LVL_SEARCH = 16;
//�ܺ������
//��-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
$D_INIT_LVL_DETAIL = 16;
//��������
//��-1��$D_INIT_LVL�˽स���
$D_INIT_LVL_PRINT  = 16;

//����ɽ���Ǿ��̼�
$D_VIEW_ICON_MAX = 1;
//��������ʳ���ɽ����ʬ
$D_DSP_OTHER_KBN = 0;
//�쥤�䡼��ʬ
$D_MAP_LAYER_KBN = 4;
//�Ͽ��濴�ޡ���
$D_MAPCENTER_MARK = "0";
//�Ͽ��濴�ޡ����ʰ������̡�
$D_MAPCENTER_MARK_P = "0";

//--------------------------------------------
//��������
//--------------------------------------------
//�������(AND,OR)
$D_SHOP_COND = "OR";
//�����ꥹ�ȹԿ�
$D_SHOP_PAGE = 5;
//������
$D_SHOP_MAX  = 30;
//�ܺ�ɽ��������ꥹ�Ⱦä�����0:�ä��ʤ���1:�ä���
$D_SHOP_CLOSELIST = "0";


//--------------------------------------------
//������
//--------------------------------------------
//�ƥꥹ�ȹԿ�
$D_SEARCH_SHOPLIST_PAGE = 5;
//����ꥹ�Ȥ�ɤγ��ؤޤǷ��겼���뤫��1����ƻ�ܸ���2���Զ�Į¼��3�������4�������ܡ�5�����衢6�����֡ʻ��֡�
$D_ADDRL_BOTTOM_LVL = 6;

//--------------------------------------------
//�������ꥢ������ɽ��̾��
//--------------------------------------------
// ���ꥢ����
$D_HISTORY_NAME["ShopA"]   = "Ź�ޥꥹ��";	// ̾��
$D_SEARCH_SHOPA_DISPNM[1]  = "����";	// ��1����
$D_SEARCH_SHOPA_DISPNM[2]  = "����";	// ��2����
// ���ꥢ������
$D_HISTORY_NAME["ShopA_2"] = "Ź�ޥꥹ��";	// ̾��
$D_SEARCH_SHOPA_DISPNM[3]  = "����";	// ��1����
$D_SEARCH_SHOPA_DISPNM[4]  = "����";	// ��2����
// ���ꥢ������
$D_HISTORY_NAME["ShopA_3"] = "Ź�ޥꥹ��";	// ̾��
$D_SEARCH_SHOPA_DISPNM[5]  = "����";	// ��1����
$D_SEARCH_SHOPA_DISPNM[6]  = "����";	// ��2����
// ���ꥢ������
$D_HISTORY_NAME["ShopA_4"] = "Ź�ޥꥹ��";	// ̾��
$D_SEARCH_SHOPA_DISPNM[7]  = "����";	// ��1����
$D_SEARCH_SHOPA_DISPNM[8]  = "����";	// ��2����
// ���ꥢ������
$D_HISTORY_NAME["ShopA_5"] = "Ź�ޥꥹ��";	// ̾��
$D_SEARCH_SHOPA_DISPNM[9]  = "����";	// ��1����
$D_SEARCH_SHOPA_DISPNM[10] = "����";	// ��2����

//--------------------------------------------
//�Ǵ�ظ���
//--------------------------------------------
$D_ST_RAD = 5000;

//--------------------------------------------
//�Ǵ���߸���
//--------------------------------------------
//������
$D_POI_MAX = 50;
//���������
$arr_D_POI_JNRMN = array();
$arr_D_POI_JNRMN[] = '00160';
$arr_D_POI_JNRMN[] = '00250';
$arr_D_POI_JNRMN[] = '00140';
$arr_D_POI_JNRMN[] = '00170';
$arr_D_POI_JNRMN[] = '00220';
$arr_D_POI_JNRMN[] = '00240';
$arr_D_POI_JNRMN[] = '00130';
$arr_D_POI_JNRMN[] = '00110';
$arr_D_POI_JNRMN[] = '00120';
if (count($arr_D_POI_JNRMN)) $D_POI_JNRMN = implode(',', $arr_D_POI_JNRMN);

//--------------------------------------------
//ư��
//--------------------------------------------
//�롼�ȸ���
$D_ROUTE_TYPE	 = 1;
//�����������󥯥�å�
$D_KYO_ICON_CLK  = 1;
// ������������Ťʤ���˿᤭�Ф��ˤޤȤ��ɽ��
$D_KYO_ICON_OVERLAP = 0;

//--------------------------------------------
//��³I/F
//--------------------------------------------
//Standard������³I/F
$D_STANDARD_ADDR_IF = 0;

//--------------------------------------------
//����̾
//--------------------------------------------
//��������
$D_KYO_COL_NAME[0][0] = "name";
$D_KYO_COL_NAME[0][1] = "addr";
$D_KYO_COL_NAME[0][2] = "col_01";
//�᤭�Ф�
$D_KYO_COL_NAME[3][0] = "name";
$D_KYO_COL_NAME[3][1] = "addr";
$D_KYO_COL_NAME[3][2] = "col_01";
//�����ܺ�
$D_KYO_COL_NAME[1][0] = "name";
$D_KYO_COL_NAME[1][1] = "addr";
$D_KYO_COL_NAME[1][2] = "col_01";
//����
$D_KYO_COL_NAME[2][0] = "name";
$D_KYO_COL_NAME[2][1] = "addr";
$D_KYO_COL_NAME[2][2] = "col_01";
//�����ܺ�(�����ѡ�
$D_KYO_COL_NAME[4][0] = "name";
$D_KYO_COL_NAME[4][1] = "addr";
$D_KYO_COL_NAME[4][2] = "col_01";
//�����ܺ�(���ޡ��ȥե����ѡ�
$D_KYO_COL_NAME[5][0] = "name";
$D_KYO_COL_NAME[5][1] = "addr";
$D_KYO_COL_NAME[5][2] = "col_01";

//--------------------------------------------
//��ʬ����̾��
//--------------------------------------------
//��ʬ����̾�Υꥹ��

//--------------------------------------------
// �ʤ���߾��ʥ����å��ܥå������ꥹ�ȥܥå�����
//--------------------------------------------
$D_COND_GRP_ANDOR = 'AND';
$cond_g_cnt = -1;


//--------------------------------------------
//������ʣ���˲�������ꥹ��
//--------------------------------------------

//--------------------------------------------
//Ź�ޱ��������Cookie��¸
//--------------------------------------------
$D_COOKIE_SHOPDTL_MAX = 0; //�����ܺ���¸���

?>