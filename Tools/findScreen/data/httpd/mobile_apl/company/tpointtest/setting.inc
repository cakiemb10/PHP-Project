<?PHP
//------------------------------------------
//    �������
//------------------------------------------
//********* �Хå����ե���������� *********
$D_CORP_NAME = "�������CCC";

//�����ӥ�������
$D_SEARVICE_START = "20090522";

//�����ӥ���λ��
$D_SEARVICE_END   = "20180521";

//--------------------------------------------
//BASICǧ��
//--------------------------------------------
$D_BASIC_AUTH["dev"]  = 0;
$D_BASIC_AUTH["test"] = 0;
$D_BASIC_AUTH["www"]  = 0;

//--------------------------------------------
// SSL��³��https����������
//--------------------------------------------
$D_SSL_ACCESS = 1;

//--------------------------------------------
// Standard��³
//--------------------------------------------
// ������³
$D_STANDARD_ADDR_IF = 0;

//--------------------------------------------
// Maplink��³
//--------------------------------------------
// ������³
$D_MAPLINK_ADDR_IF = 0;
// ������³���Υޥå������ɽ��
$D_ADDR_MATCH_DISP = 0;
// �ޥå�����ɽ��������ʸ��
//$D_ADDR_MATCH_HEAD = "";
// �ޥå�����ɽ���θ���ʸ��
//$D_ADDR_MATCH_TAIL = "";
// �ޥå�����ɽ��������
//$D_ADDR_MATCH_EXP = "";
// icn��ά���Υǥե���ȥ�������ʡ���0��ɽ�����롢1��ɽ�����ʤ�
$D_NO_DEFAULT_ICN = 0;
// ����հ���
$D_GET_ADDRSTR = 0;

//------------------------------------------
//    �����ե꡼��ɥ����
//------------------------------------------
$D_FREEWD_COLUMN="COL_04";

//------------------------------------------
//    �ʹ��߾�︡��
//------------------------------------------
$D_WHERE_NAME = array('w1' => '','w2' => '');
$D_WHERE_VAL  = array('w1' => 'COL_04=0','w2' => 'COL_04=1');
$D_WHERE_ALL  = "����";

//------------------------------------------
//    ���ָ�����
//------------------------------------------
$D_SEARCH_LIST_PAGE=15;
//����ꥹ�Ȥ�ɤγ��ؤޤǷ��겼���뤫��1����ƻ�ܸ���2���Զ�Į¼��3�������4�������ܡ�5�����衢6�����֡ʻ��֡�
$D_ADDRL_BOTTOM_LVL = 6;

//------------------------------------------
//    ������
//------------------------------------------
//�Ǵ󸡺����
$D_SEARCH_NEAR_LIST_PAGE=20;
$D_DEFAULT_LEVEL=6;

//------------------------------------------
//    �Ǵ󸡺���
//------------------------------------------
// �Ǵ󸡺��ϰϡ�Ⱦ�¡�
$D_SHOP_RAD=3000;
$D_ST_RAD=5000;
// �ե꡼��ɤιʹ��ߥե�������Ϸ��
$D_FILTER_CNT=50;

$SETTING["animation"]    =1;				// �����������Ǥ����뤫��
$SETTING["access_key"]   =1;				// ������������
$SETTING["optsearch"]    =1;				// �����긡����̵ͭ
$SETTING["location"]     =1;				// �������꤫�鸡����̵ͭ
$SETTING["addrlist"]     =0;				// ����ꥹ�ȸ�����̵ͭ
$SETTING["arealist"]     =0;				// ���ꥢ������̵ͭ
$SETTING["arealist_2"]   =0;				// ���ꥢ������̵ͭ
$SETTING["arealist_3"]   =0;				// ���ꥢ������̵ͭ
$SETTING["arealist_4"]   =0;				// ���ꥢ������̵ͭ
$SETTING["arealist_5"]   =0;				// ���ꥢ������̵ͭ
$SETTING["eki-free"]     =1;				// �إե꡼��ɤ�̵ͭ
$SETTING["add-free"]     =1;				// ����ե꡼��ɤ�̵ͭ
$SETTING["zip-free"]     =0;				// ͹���ֹ渡����̵ͭ
$SETTING["cpn-free"]     =1;				// �����ե꡼��ɸ�����̵ͭ
$SETTING["nearmap"]      =2;				// �Ǵ��Ͽ޸���������̵ͭ
$SETTING["nearstation"]  =1;				// �Ǵ�ظ���������̵ͭ
$SETTING["routesearch"]  =0;				// �����Ϥ���Υ롼��õ����ž����뤫�ɤ���
$SETTING["ssroutesearch"]=0;				// ��ȯ�Ϥ����򤷤ƥ롼��õ��
$SETTING["nsroutesearch"]=0;				// �Ǵ�ؤ���Υ롼��õ����ž����뤫�ɤ���
$SETTING["noncpdata"]    ="S";				// �����ʤ��ե饰
$SETTING["detailmap"]    =1;				// �ܺ�ɽ�����Ͽޤˤ��뤫�ɤ�����
$SETTING["showcolonlist"]=0;				// ����������name�ʳ���ɽ��
$SETTING["showcolonmapl"]=0;				// �Ͽ޺Ǵ�����������name�ʳ���ɽ��

// �����ܺ�ɽ��������ܡʣģ¤�����ȥ�󥯡�
//��������
$D_KYO_COL_NAME[0][0] = "col_02";
$D_KYO_COL_NAME[0][1] = "name";
$D_KYO_COL_NAME[0][2] = "addr";
$D_KYO_COL_NAME[0][3] = "col_01";
//�᤭�Ф�
$D_KYO_COL_NAME[3][0] = "col_02";
$D_KYO_COL_NAME[3][1] = "name";
$D_KYO_COL_NAME[3][2] = "addr";
$D_KYO_COL_NAME[3][3] = "col_01";
//�����ܺ�
$D_KYO_COL_NAME[1][0] = "col_02";
$D_KYO_COL_NAME[1][1] = "name";
$D_KYO_COL_NAME[1][2] = "addr";
$D_KYO_COL_NAME[1][3] = "col_01";
//����
$D_KYO_COL_NAME[2][0] = "col_02";
$D_KYO_COL_NAME[2][1] = "name";
$D_KYO_COL_NAME[2][2] = "addr";
$D_KYO_COL_NAME[2][3] = "col_01";
//�����ܺ�(�����ѡ�
$D_KYO_COL_NAME[4][0] = "col_02";
$D_KYO_COL_NAME[4][1] = "name";
$D_KYO_COL_NAME[4][2] = "addr";
$D_KYO_COL_NAME[4][3] = "col_01";
//�����ܺ�(���ޡ��ȥե����ѡ�
$D_KYO_COL_NAME[5][0] = "col_02";
$D_KYO_COL_NAME[5][1] = "name";
$D_KYO_COL_NAME[5][2] = "addr";
$D_KYO_COL_NAME[5][3] = "col_01";

$D_ZOOM[1] = 76;
$D_ZOOM[2] = 70;
$D_ZOOM[3] = 63;
$D_ZOOM[4] = 59;
$D_ZOOM[5] = 55;
$D_ZOOM[6] = 49;
$D_ZOOM[7] = 44;
$D_ZOOM[8] = 40;
$D_ZOOM[9] = 38;

$D_MAXZOOM=9;
$D_MINZOOM=1;

$D_PROUTE_DIST = 4000;
//------------------------------------------
//    �Ͽ޾���ط�
//------------------------------------------
// �Ͽޥ쥤�䡼�ֹ�
$D_LAYER_NO = 201;

// �Ͽޥޡ���������(1:���顼 2:��� 3:ɽ���ʤ���
$D_MARK_TYPE = 2;

//------------------------------------------
//    ����¾
//------------------------------------------
// iPhone�б�
//$D_IPHONE_ACCESS = ;
// Android�б�
//$D_ANDROID_ACCESS = ;
// iPhone���ޥۤإ�����쥯��
//$D_IPHONE_REDIRECT = ;
// Android���ޥۤإ�����쥯��
//$D_ANDROID_REDIRECT = ;

//--------------------------------------------
//������ʣ���˲�������ꥹ��
//--------------------------------------------

//--------------------------------------------
//����GPS��������
//--------------------------------------------
//$D_MGPS_LOG = ;
?>