<?PHP
$D_DATA_CID = 'zen000';
$D_ICON_CID = 'zen000';

$D_SHOP_RAD = 10000;
//$D_SHOP_RAD_RE = 10000;
// �Ǵ��Ƹ������������
$D_RESEARCH_CNT = 1;

// �ޥ��������С��ǥե�����
$D_KYO_ICON_MO = 1;

// $D_AREA_SORT_LPAD[�ѥ������ֹ�1-5][�����ֹ�1-2]['len' or 'char']
$D_AREA_SORT_LPAD[1][1]['len'] = 2;		// ���
$D_AREA_SORT_LPAD[1][1]['char'] = "0";	// ������ʸ��

// ��쳬�ء���ƻ�ܸ����Ͽޥ��
$D_AREA_LVL1_NMAP_LINK = 1;

// ���ޥۥ�����쥯�ȡ�Ź�޾ܺ٢�Ź���Ͽ�
$D_REDIRECT_SMT_KYO_ID = 'map';

//--------------------------------------------
// ʣ���ʤ���߾��ʥ����å��ܥå������ꥹ�ȥܥå�����
//--------------------------------------------
// ��setting.inc��������񤭤�����ϡ�ɬ�������������ԤʤäƤ������ꤷ�Ƥ���������
$D_COND = array();
$D_COND_GRP = array();
$D_COND_ANDOR = array();

$D_COND_GRP_ANDOR = 'AND';

$D_COND[1] = array('type'=>'CB', 'val'=>'COL_02:1');//�����ե饰
$D_COND[2] = array('type'=>'CB', 'val'=>'COL_04:11');//�����ȶ�ʬ�ʤʤ�����
$D_COND[3] = array('type'=>'CB', 'val'=>'COL_26:1');//�ɥ��
$D_COND[4] = array('type'=>'CB', 'val'=>'COL_27:1');//�����ͥ�˥塼
$D_COND[5] = array('type'=>'CB', 'val'=>'COL_28:1');//�ǥ�����
$D_COND[6] = array('type'=>'CB', 'val'=>'COL_29:1');//ī��
$D_COND[7] = array('type'=>'CB', 'val'=>'COL_33:1');//�ɥ�󥯥С�
$D_COND[8] = array('type'=>'CB', 'val'=>'COL_34:1');//������С�
$D_COND[9] = array('type'=>'CB', 'val'=>'COL_35:1');//������˥塼
$D_COND[10] = array('type'=>'CB', 'val'=>'COL_36:1');//�꿩
$D_COND[11] = array('type'=>'CB', 'val'=>'COL_37:2');//����֤����
$D_COND[12] = array('type'=>'CB', 'val'=>'COL_38:2');//����
$D_COND[13] = array('type'=>'CB', 'val'=>'COL_39:1');//24���ֱĶ�
$D_COND[14] = array('type'=>'CB', 'val'=>'COL_42:1');//�ơ��֥��ʤ���
$D_COND[15] = array('type'=>'CB', 'val'=>'COL_43:1');//�٥ӡ�������
$D_COND[16] = array('type'=>'CB', 'val'=>'COL_44:1');//¿��Ū�ȥ���
$D_COND[17] = array('type'=>'CB', 'val'=>'COL_45:1');//�������ס�����١�����
$D_COND[18] = array('type'=>'CB', 'val'=>'COL_46:1');//Ź�ޥե���1F
$D_COND[19] = array('type'=>'CB', 'val'=>'COL_48:1');//��־�
$D_COND[20] = array('type'=>'CB', 'val'=>'COL_49:1');//�ɥ饤�֥��롼
$D_COND[21] = array('type'=>'CB', 'val'=>'COL_50:1');//���쥸�åȥ��������Ѳ�
$D_COND[22] = array('type'=>'CB', 'val'=>'COL_72:1');//ZENSHO CooCa�谷Ź
$D_COND[23] = array('type'=>'CB', 'val'=>'COL_57:1');//QUICPay���Ѳ�
$D_COND[24] = array('type'=>'CB', 'val'=>'COL_58:1');//iD
$D_COND[25] = array('type'=>'CB', 'val'=>'COL_74:1');//���̷��Żҥޥ͡� 
$D_COND[26] = array('type'=>'CB', 'val'=>'COL_78:1');//Edy

$D_COND_GRP[0] = array(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26);
$D_COND_ANDOR[0] = 'AND';

$D_COND[41] = array('type'=>'CB', 'val'=>'COL_41:2');//�ر�
$D_COND[42] = array('type'=>'CB', 'val'=>'COL_41:1');//ʬ��
$D_COND[43] = array('type'=>'CB', 'val'=>'COL_41:3');//����ʬ��

$D_COND_GRP[1] = array(41,42,43);
$D_COND_ANDOR[1] = 'OR';

/* ����Ū��URL�Ǹ����˾����Ϳ */
$_VARS['cond1']=1; // ������������ե饰
$_VARS['cond2']=1; // �����ȶ�ʬ

//--------------------------------------------
//��������
//--------------------------------------------
//�������̤ǺǴ��������������ɽ�����뤫��0��ɽ�����ʤ���1��ɽ�������
$D_SHOP_PRINT_SEARCH = 0;

//--------------------------------------------
//�������
//--------------------------------------------
//����ꥹ�ȡ��إꥹ�Ȥǥ��ʹʤ���ߤ���ѡ�0�����Ѥ��ʤ���1�����Ѥ����
$D_SEARCH_KANA = 1;

//--------------------------------------------
//������̡ʥơ��֥�����ˤΥ쥤�����Ⱦ���
//--------------------------------------------
//���
//������������ѹ�������硢search_table.tpl��search_addrtable.tpl��HTML��Ĵ������ɬ�פ�����ޤ���
$D_SEARCH_TABLE_COLS = 3;
//�Կ�
$D_SEARCH_TABLE_ROWS = 8;
//���ڡ�����ɽ������ʢ��Խ��Բġ�
$D_SEARCH_TABLE_PAGE = $D_SEARCH_TABLE_COLS * $D_SEARCH_TABLE_ROWS;

//--------------------------------------------
// �ե꡼��ɸ���
//--------------------------------------------
//�ե꡼���ʣ�縡���ѥե饰
$D_COMB_FW_ZIP  = 1;	//͹���ֹ�ե꡼���
$D_COMB_FW_ADDR = 1;	//����ե꡼���
$D_COMB_FW_ST   = 1;	//�إե꡼���
$D_COMB_FW_POI  = 0;	//���ߥե꡼���
$D_COMB_FW_SHOP = 1;	//�����ե꡼���
//�ե꡼���ʣ�縡�����Ϸ��
$D_COMB_FW_ZIP_MAX  = 5;	//͹���ֹ�ե꡼���
$D_COMB_FW_ADDR_MAX = 5;	//����ե꡼���
$D_COMB_FW_ST_MAX   = 5;	//�إե꡼���
$D_COMB_FW_POI_MAX  = 5;	//���ߥե꡼���
$D_COMB_FW_SHOP_MAX = 5;	//�����ե꡼���

?>