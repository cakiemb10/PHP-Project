<?PHP
//��Ĵ����
//$D_BASIC_AUTH['test'] = 0;	// debug

if (ereg('test', $cid)) {
	// ������
	
	// T������TOP
	$D_HP_URL = "http://stg.tsite.jp/";

	// �����ݥ�URL
	$D_FREE_URL[] = 'https://stg.tsite.jp/coupon/index.pl';

	// iPad������쥯����URL
	$D_IPAD_REDIRECT = "https://stg.tsite.jp/t-map/index.pl";
} else {
	// ������

	// T������TOP
	$D_HP_URL = "http://tsite.jp/";

	// �����ݥ�URL
	$D_FREE_URL[] = 'https://tsite.jp/coupon/index.pl';

	// iPad������쥯����URL
	$D_IPAD_REDIRECT = "https://tsite.jp/t-map/index.pl";
}

// �Ǵ��إꥹ�Ȥθ���TOP�ܥ���ɽ������
$D_NEKI_SEARCH_TOP_LINK = 1;

// ���ַ����TOP����餺����ɽ��
$D_DIRECT_SEARCH = 1;

// �����ݥ󥢥������������
$D_TOOLTIP_W = 26;
$D_TOOLTIP_H = 26;
$D_TOOLTIP_OFFSET_X = -8;
$D_TOOLTIP_OFFSET_Y = -35;

// �Ͽްʳ�ɽ���ΰ�ʺǴ��Ź���Ͽޡ�
$D_NMAP_ANY_DISP_PX = 65;

// �Ͽްʳ�ɽ���ΰ��Ź���Ͽޡ�
$D_MAP_ANY_DISP_PX = 31;

// �����ݥ�ͭ�ꥢ������
$D_ICON_NEW_IMG = "{$D_DIR_COMPANY}img/A-2a.gif";


//--------------------------------------------
// �ʤ���߾��
//--------------------------------------------
$D_FILTER_VAL_LIST[] = '';
$D_FILTER_VAL_LIST[] = 'COL_87=1';  // �����ե�ۡ��� add 20160425
$D_FILTER_VAL_LIST[] = 'COL_12=1';  // ����
$D_FILTER_VAL_LIST[] = 'COL_83=1';  // �Ŀ���� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_68=1';  // ������Ź add 20151008
$D_FILTER_VAL_LIST[] = 'COL_104=1'; // ­����� add 20161221
$D_FILTER_VAL_LIST[] = 'COL_106=1'; // �����å��� add 20170117
$D_FILTER_VAL_LIST[] = 'COL_98=1';  // ALOOK add 20160701
$D_FILTER_VAL_LIST[] = 'COL_22=1';  // ����ڥ�
$D_FILTER_VAL_LIST[] = 'COL_92=1';  // ERA����ѥ� add 20160526 
$D_FILTER_VAL_LIST[] = 'COL_56=1';  // ����ð add 20160512
$D_FILTER_VAL_LIST[] = 'COL_118=1';  // ISETAN MiRROR add 20170428
$D_FILTER_VAL_LIST[] = 'COL_58=1';  // ���Ĳ� add 20160512
//$D_FILTER_VAL_LIST[] = 'COL_20=1'; del 20150821
//$D_FILTER_VAL_LIST[] = 'COL_58=1'; del 20160425
$D_FILTER_VAL_LIST[] = 'COL_28=1';  // �����륷��
$D_FILTER_VAL_LIST[] = 'COL_38=1';  // �������륷������ ���ե�
$D_FILTER_VAL_LIST[] = 'COL_19=1';  // ���ǥ�����
$D_FILTER_VAL_LIST[] = 'COL_08=1';  // ENEOS
$D_FILTER_VAL_LIST[] = 'COL_72=1';  // ����ȥ�ڥå� add 20160205
$D_FILTER_VAL_LIST[] = 'COL_14=1';  // �����ȥХå������롼��
$D_FILTER_VAL_LIST[] = 'COL_107=1'; // ���˥ĥ��������� add 20170117
$D_FILTER_VAL_LIST[] = 'COL_75=1';  // ��Ǽ�ޥ��ӥ塼�ѥ쥹 add 20160318
$D_FILTER_VAL_LIST[] = 'COL_77=1';  // ��������ҥ���ȥ꡼����� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_09=1';  // ������/���ơ��������� mod 20150615
$D_FILTER_VAL_LIST[] = 'COL_103=1'; // ���ĵ� add 20161012
$D_FILTER_VAL_LIST[] = 'COL_59=1';  // �������
$D_FILTER_VAL_LIST[] = 'COL_121=1'; // ���ե� �쥯���� add 20170601
$D_FILTER_VAL_LIST[] = 'COL_06=1';  // �����Υ������
$D_FILTER_VAL_LIST[] = 'COL_78=1';  // ��������ȥ꡼����� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_76=1';  // �����ӡ����ѥ쥹 add 20160318
//$D_FILTER_VAL_LIST[] = 'COL_56=1'; del 20160425
$D_FILTER_VAL_LIST[] = 'COL_25=1';  // ����饸��
$D_FILTER_VAL_LIST[] = 'COL_17=1';  // ����
$D_FILTER_VAL_LIST[] = 'COL_122=1'; // ����䤫��� add 20170601
$D_FILTER_VAL_LIST[] = 'COL_101=1'; // �������󥺰���ð/�������󥺰���ð������ add 20160719
$D_FILTER_VAL_LIST[] = 'COL_13=1';  // ����å��������ǥ�
$D_FILTER_VAL_LIST[] = 'COL_44=1';  // GREEN DOG
$D_FILTER_VAL_LIST[] = 'COL_120=1'; // ��ǽ���Ѷ�� add 20170515
$D_FILTER_VAL_LIST[] = 'COL_23=1';  // �����5
$D_FILTER_VAL_LIST[] = 'COL_35=1';  // ���󥿥��ȤΥ������ƥ�
$D_FILTER_VAL_LIST[] = 'COL_69=1';  // ���󥿥��ȥ��� add 20160120
$D_FILTER_VAL_LIST[] = 'COL_55=1';  // THE SUIT COMPANY
$D_FILTER_VAL_LIST[] = 'COL_36=1';  // THANKS ON THE TABLE��
$D_FILTER_VAL_LIST[] = 'COL_89=1';  // GL�ۡ��� add 20160425
$D_FILTER_VAL_LIST[] = 'COL_85=1';  // ����ȥ�ڥå� add 20160406
$D_FILTER_VAL_LIST[] = 'COL_18=1';  // ����ǥ����������
$D_FILTER_VAL_LIST[] = 'COL_110=1'; // ������� add 20170117
$D_FILTER_VAL_LIST[] = 'COL_32=1';  // �峤�������ץ쥹
//$D_FILTER_VAL_LIST[] = 'COL_20=1';
$D_FILTER_VAL_LIST[] = 'COL_95=1';  // ���祤�ե�����/���祤�ե�2/����ƥ���������å� ��������' add 20161018
$D_FILTER_VAL_LIST[] = 'COL_84=1';  // ���۶�� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_24=1';  // ����ʥ���
$D_FILTER_VAL_LIST[] = 'COL_86=1';  // ������� add 20160413
$D_FILTER_VAL_LIST[] = 'COL_94=1';  // ����Ʋ add 20160624
//$D_FILTER_VAL_LIST[] = 'COL_53=1'; del 20160425
$D_FILTER_VAL_LIST[] = 'COL_31=1';  // ��������ǥ����ʡ�
$D_FILTER_VAL_LIST[] = 'COL_07=1';  // ���������ޥꥪ
$D_FILTER_VAL_LIST[] = 'COL_114=1'; // ���ơ����Τɤ� add20170301
$D_FILTER_VAL_LIST[] = 'COL_21=1';  // ���ݡ��ĥǥ�
$D_FILTER_VAL_LIST[] = 'COL_16=1';  // ���꡼����/gooz/q��s mart
$D_FILTER_VAL_LIST[] = 'COL_123=1'; // ������ add 20170601
$D_FILTER_VAL_LIST[] = 'COL_71=1';  // ���н����� add 20160205
$D_FILTER_VAL_LIST[] = 'COL_61=1';  // ���եȥХ� add 20150615
$D_FILTER_VAL_LIST[] = 'COL_49=1';  // ������
$D_FILTER_VAL_LIST[] = 'COL_79=1';  // ������ץ饶���ͤҤ� add 20160318
//$D_FILTER_VAL_LIST[] = 'COL_57=1'; // del 20160425
$D_FILTER_VAL_LIST[] = 'COL_125=1';  // â�϶�� add 20170613
$D_FILTER_VAL_LIST[] = 'COL_04=1';  // TSUTAYA/�ӥǥ�100
$D_FILTER_VAL_LIST[] = 'COL_90=1';  // T-SITEŹ�� add 20160512
$D_FILTER_VAL_LIST[] = 'COL_64=1';  // �ǥѡ��ȥꥦ�ܥ� add 20150421
$D_FILTER_VAL_LIST[] = 'COL_33=1';  // ��ޥۥƥ륺
$D_FILTER_VAL_LIST[] = 'COL_20=1';  // ���𥹥ȥ�/�ե���� add 20150908
$D_FILTER_VAL_LIST[] = 'COL_37=1';  // �ɥȡ��륳���ҡ�����å�
$D_FILTER_VAL_LIST[] = 'COL_27=1';  // �ɥ�å�����֥�
$D_FILTER_VAL_LIST[] = 'COL_42=1';  // �ɥ�å����ȥ�mac
$D_FILTER_VAL_LIST[] = 'COL_39=1';  // �ɥ�å��楿��/�楿��Ĵ������
$D_FILTER_VAL_LIST[] = 'COL_102=1'; // �Ȥ󤫤��� add 20161012
$D_FILTER_VAL_LIST[] = 'COL_117=1'; // don�����ꥢ����/�ѥ����ꥢ���� add 20170301
$D_FILTER_VAL_LIST[] = 'COL_115=1'; // �ɤ��� add 20170301
$D_FILTER_VAL_LIST[] = 'COL_66=1';  // �ȡ����Х��� add 20150514
$D_FILTER_VAL_LIST[] = 'COL_26=1';  // �˥åݥ��󥿥���
$D_FILTER_VAL_LIST[] = 'COL_60=1';  // NEXT BLUE
//$D_FILTER_VAL_LIST[] = 'COL_19=1';
$D_FILTER_VAL_LIST[] = 'COL_51=1';  // �ѥ��ե��å�����եޥ͡�������
$D_FILTER_VAL_LIST[] = 'COL_73=1';  // �ϥå��ɥ�å� add 20160218
$D_FILTER_VAL_LIST[] = 'COL_65=1';  // �ϥԥʥ� add 20150421
$D_FILTER_VAL_LIST[] = 'COL_10=1';  // �С��ߥ��
//$D_FILTER_VAL_LIST[] = 'COL_30=1';
$D_FILTER_VAL_LIST[] = 'COL_46=1';  // ��Ω�������󥹥ȡ���
$D_FILTER_VAL_LIST[] = 'COL_91=1';  // B.B.ON add 20160526 
$D_FILTER_VAL_LIST[] = 'COL_112=1'; // �ե��ߥꥢ add 20170117
$D_FILTER_VAL_LIST[] = 'COL_03=1';  // �ե��ߥ꡼�ޡ���
$D_FILTER_VAL_LIST[] = 'COL_88=1';  // �ե������ۡ��� add 20160425
$D_FILTER_VAL_LIST[] = 'COL_116=1'; // �ե��륯�� add 20170301
$D_FILTER_VAL_LIST[] = 'COL_15=1';  // �ٻΥ��ƥ���
$D_FILTER_VAL_LIST[] = 'COL_50=1';  // �ץ�å�������
$D_FILTER_VAL_LIST[] = 'COL_108=1'; // �ۥ����ե� add 20170117
$D_FILTER_VAL_LIST[] = 'COL_96=1';  // Polo Ralph Lauren Factory Store add 20160624
$D_FILTER_VAL_LIST[] = 'COL_74=1';  // WHITE THE SUIT COMPANY add 20160218
$D_FILTER_VAL_LIST[] = 'COL_63=1';  // Honya Club With
$D_FILTER_VAL_LIST[] = 'COL_67=1';  // MADO����å�/MADO����åץѡ��ȥʡ� add 20150514
$D_FILTER_VAL_LIST[] = 'COL_62=1';  // �ޥߡ��ޡ���
$D_FILTER_VAL_LIST[] = 'COL_57=1';  // �ݰ溣�� add 20160512
$D_FILTER_VAL_LIST[] = 'COL_48=1';  // �ޥ륨��/�ޥ륨�� �ץ�/��󥳥�/����
$D_FILTER_VAL_LIST[] = 'COL_109=1'; // �ޥ륨�ɥ�å�/�ޥ륨���� add 20170117
//$D_FILTER_VAL_LIST[] = 'COL_43=1'; del 20150821
$D_FILTER_VAL_LIST[] = 'COL_40=1';  // ����Υ�ѡ���
$D_FILTER_VAL_LIST[] = 'COL_53=1';  // ���� add 20160512
$D_FILTER_VAL_LIST[] = 'COL_41=1';  // �ߥ˥ߥ�
$D_FILTER_VAL_LIST[] = 'COL_43=1';  // �ߥե� add 20150924
$D_FILTER_VAL_LIST[] = 'COL_105=1'; // �ܺ����۶�� add 20161221
$D_FILTER_VAL_LIST[] = 'COL_111=1'; // �व���ο����� add 20170117
$D_FILTER_VAL_LIST[] = 'COL_97=1';  // ����Ծ� add 20160701
$D_FILTER_VAL_LIST[] = 'COL_47=1';  // �䥪�ޥ�/�������󥺥ޡ���/������
$D_FILTER_VAL_LIST[] = 'COL_11=1';  // ̴��/��ᤢ��Ʋ
$D_FILTER_VAL_LIST[] = 'COL_119=1'; // ��᥿����/���ޡ���/LECT add 20170428
$D_FILTER_VAL_LIST[] = 'COL_54=1';  // �������Ļ�
$D_FILTER_VAL_LIST[] = 'COL_70=1';  // ����� add 20160205
$D_FILTER_VAL_LIST[] = 'COL_124=1';  // �顡���ϥ� add 20170613
$D_FILTER_VAL_LIST[] = 'COL_30=1';  // �ꥦ�ܥ����ȥ� add 20150421
$D_FILTER_VAL_LIST[] = 'COL_80=1';  // LIXIL���硼�롼�� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_81=1';  // LIXIL��ե����ॷ��å� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_82=1';  // LIXIL��ե�����ͥå� add 20160318
$D_FILTER_VAL_LIST[] = 'COL_29=1';  // ΰ����
$D_FILTER_VAL_LIST[] = 'COL_45=1';  // ��åɥ���٥�
$D_FILTER_VAL_LIST[] = 'COL_99=1';  // ��󥺥������� add 20160701
$D_FILTER_VAL_LIST[] = 'COL_100=1'; // ��󥺥����쥯�� add 20160701
$D_FILTER_VAL_LIST[] = 'COL_34=1';  // ���åƥꥢ
$D_FILTER_VAL_LIST[] = 'COL_93=1';  // WonderGOO add 20160624
$D_FILTER_VAL_LIST[] = 'COL_05=1';  // ���Τ�Ź




$D_FILTER_NAME_LIST[] = $D_FILTER_LIST_FIRST;
$D_FILTER_NAME_LIST[] = '�����ե�ۡ���'; // add 20160425
$D_FILTER_NAME_LIST[] = '����';
$D_FILTER_NAME_LIST[] = '�Ŀ����'; // add 20160318
$D_FILTER_NAME_LIST[] = '������Ź'; // add 20151008
$D_FILTER_NAME_LIST[] = '­�����'; // add 20161221
$D_FILTER_NAME_LIST[] = '�����å���'; // add 20170117
$D_FILTER_NAME_LIST[] = 'ALOOK'; // add 20160701
$D_FILTER_NAME_LIST[] = '����ڥ�';
$D_FILTER_NAME_LIST[] = 'ERA����ѥ�'; // add 20160526
$D_FILTER_NAME_LIST[] = '����ð'; // add 20160512
$D_FILTER_NAME_LIST[] = 'ISETAN MiRROR'; // add 20170428
$D_FILTER_NAME_LIST[] = '���Ĳ�'; // add 20160512
//$D_FILTER_NAME_LIST[] = '�����ɤ��º� ������'; del 20150821
//$D_FILTER_NAME_LIST[] = 'WinBe'; del 20160425
$D_FILTER_NAME_LIST[] = '�����륷��';
$D_FILTER_NAME_LIST[] = '�������륷������ ���ե�';
$D_FILTER_NAME_LIST[] = '���ǥ�����';
$D_FILTER_NAME_LIST[] = 'ENEOS';
$D_FILTER_NAME_LIST[] = '����ȥ�ڥå�'; // add 20160205
$D_FILTER_NAME_LIST[] = '�����ȥХå������롼��';
$D_FILTER_NAME_LIST[] = '���˥ĥ���������';
$D_FILTER_NAME_LIST[] = '��Ǽ�ޥ��ӥ塼�ѥ쥹'; // add 20160318
$D_FILTER_NAME_LIST[] = '��������ҥ���ȥ꡼�����'; // add 20160318
$D_FILTER_NAME_LIST[] = '������/���ơ���������'; // mod 20150615
$D_FILTER_NAME_LIST[] = '���ĵ�'; // add 20161012
$D_FILTER_NAME_LIST[] = '�������';
$D_FILTER_NAME_LIST[] = '���ե� �쥯����'; // add 20170601
$D_FILTER_NAME_LIST[] = '�����Υ������';
$D_FILTER_NAME_LIST[] = '��������ȥ꡼�����'; // add 20160318
$D_FILTER_NAME_LIST[] = '�����ӡ����ѥ쥹'; // add 20160318
//$D_FILTER_NAME_LIST[] = '���å��ǥ奪'; del 20160425
$D_FILTER_NAME_LIST[] = '����饸��';
$D_FILTER_NAME_LIST[] = '����';
$D_FILTER_NAME_LIST[] = '����䤫���'; // add 20170601
$D_FILTER_NAME_LIST[] = '�������󥺰���ð/�������󥺰���ð������'; // add 20160719
$D_FILTER_NAME_LIST[] = '����å��������ǥ�';
$D_FILTER_NAME_LIST[] = 'GREEN DOG';
$D_FILTER_NAME_LIST[] = '��ǽ���Ѷ��'; // add 20170515
$D_FILTER_NAME_LIST[] = '�����5';
$D_FILTER_NAME_LIST[] = '���󥿥��ȤΥ������ƥ�';
$D_FILTER_NAME_LIST[] = '���󥿥��ȥ���'; // add 20160120
$D_FILTER_NAME_LIST[] = 'THE SUIT COMPANY';
$D_FILTER_NAME_LIST[] = 'THANKS ON THE TABLE��';
$D_FILTER_NAME_LIST[] = 'GL�ۡ���'; // add 20160425
$D_FILTER_NAME_LIST[] = '����ȥ�ڥå�'; // add 20160406
$D_FILTER_NAME_LIST[] = '����ǥ����������';
$D_FILTER_NAME_LIST[] = '�������'; // add 20170117
$D_FILTER_NAME_LIST[] = '�峤�������ץ쥹';
//$D_FILTER_NAME_LIST[] = 'SHOO��LA��RUE';
$D_FILTER_NAME_LIST[] = '���祤�ե�����/���祤�ե�2/����ƥ���������å� ��������'; // mod 20161018
$D_FILTER_NAME_LIST[] = '���۶��'; // add 20160318
$D_FILTER_NAME_LIST[] = '����ʥ���';
$D_FILTER_NAME_LIST[] = '�������'; // add 20160413
$D_FILTER_NAME_LIST[] = '����Ʋ'; // add 20160624
//$D_FILTER_NAME_LIST[] = '��������IE'; del 20160425
$D_FILTER_NAME_LIST[] = '��������ǥ����ʡ�';
$D_FILTER_NAME_LIST[] = '���������ޥꥪ';
$D_FILTER_NAME_LIST[] = '���ơ����Τɤ�'; //add 20170301
$D_FILTER_NAME_LIST[] = '���ݡ��ĥǥ�';
$D_FILTER_NAME_LIST[] = '���꡼����/gooz/q��s mart';
$D_FILTER_NAME_LIST[] = '������'; // add 20170601
$D_FILTER_NAME_LIST[] = '���н�����'; // add 20160205
$D_FILTER_NAME_LIST[] = '���եȥХ�'; // mod 20150615
$D_FILTER_NAME_LIST[] = '������';
$D_FILTER_NAME_LIST[] = '������ץ饶���ͤҤ�'; // add 20160318
//$D_FILTER_NAME_LIST[] = '���㥤��ɥ�����'; del 20160425
$D_FILTER_NAME_LIST[] = 'â�϶��';            // add 20170613
$D_FILTER_NAME_LIST[] = 'TSUTAYA/�ӥǥ�100';
$D_FILTER_NAME_LIST[] = 'T-SITEŹ��'; // add 20160512
$D_FILTER_NAME_LIST[] = '�ǥѡ��ȥꥦ�ܥ�'; // add 20150421
$D_FILTER_NAME_LIST[] = '��ޥۥƥ륺';
$D_FILTER_NAME_LIST[] = '���𥹥ȥ�/�ե����'; // add 20150908
$D_FILTER_NAME_LIST[] = '�ɥȡ��륳���ҡ�����å�';
$D_FILTER_NAME_LIST[] = '�ɥ�å�����֥�';
$D_FILTER_NAME_LIST[] = '�ɥ�å����ȥ�mac';
$D_FILTER_NAME_LIST[] = '�ɥ�å��楿��/�楿��Ĵ������';
$D_FILTER_NAME_LIST[] = '�Ȥ󤫤���'; // add 20161012
$D_FILTER_NAME_LIST[] = 'don�����ꥢ����/�ѥ����ꥢ����'; // add 20170301
$D_FILTER_NAME_LIST[] = '�ɤ���'; // add 20170301
$D_FILTER_NAME_LIST[] = '�ȡ����Х���'; // add 20150514
$D_FILTER_NAME_LIST[] = '�˥åݥ��󥿥���';
$D_FILTER_NAME_LIST[] = 'NEXT BLUE';
//$D_FILTER_NAME_LIST[] = 'HusHusH';
$D_FILTER_NAME_LIST[] = '�ѥ��ե��å�����եޥ͡�������';
$D_FILTER_NAME_LIST[] = '�ϥå��ɥ�å�'; // add 20160218
$D_FILTER_NAME_LIST[] = '�ϥԥʥ�'; // add 20150421
$D_FILTER_NAME_LIST[] = '�С��ߥ��';
//$D_FILTER_NAME_LIST[] = '��޺�����ۥƥ륰�롼��';
$D_FILTER_NAME_LIST[] = '��Ω�������󥹥ȡ���';
$D_FILTER_NAME_LIST[] = 'B.B.ON'; // add 20160526
$D_FILTER_NAME_LIST[] = '�ե��ߥꥢ'; // add 20170117
$D_FILTER_NAME_LIST[] = '�ե��ߥ꡼�ޡ���';
$D_FILTER_NAME_LIST[] = '�ե������ۡ���'; // add 20160425
$D_FILTER_NAME_LIST[] = '�ե��륯��'; // add 20170301
$D_FILTER_NAME_LIST[] = '�ٻΥ��ƥ���';
$D_FILTER_NAME_LIST[] = '�ץ�å�������';
$D_FILTER_NAME_LIST[] = '�ۥ����ե�'; // add 20170117
$D_FILTER_NAME_LIST[] = 'Polo Ralph Lauren Factory Store'; // add 20160624
$D_FILTER_NAME_LIST[] = 'WHITE THE SUIT COMPANY'; // add 20160218
$D_FILTER_NAME_LIST[] = 'Honya Club With';
$D_FILTER_NAME_LIST[] = 'MADO����å�/MADO����åץѡ��ȥʡ�'; // add 20150514
$D_FILTER_NAME_LIST[] = '�ޥߡ��ޡ���';
$D_FILTER_NAME_LIST[] = '�ݰ溣��'; // add 20160512
$D_FILTER_NAME_LIST[] = '�ޥ륨��/�ޥ륨�� �ץ�/��󥳥�/����';
$D_FILTER_NAME_LIST[] = '�ޥ륨�ɥ�å�/�ޥ륨����'; //add 20170117
//$D_FILTER_NAME_LIST[] = '���楬���ǥ�ۥƥ륺'; del 20150821
$D_FILTER_NAME_LIST[] = '����Υ�ѡ���';
$D_FILTER_NAME_LIST[] = '����'; // add 20160512
$D_FILTER_NAME_LIST[] = '�ߥ˥ߥ�';
$D_FILTER_NAME_LIST[] = '�ߥե�'; // add 20150924
$D_FILTER_NAME_LIST[] = '�ܺ����۶��'; // add 20161221
$D_FILTER_NAME_LIST[] = '�व���ο�����'; // add 20170117
$D_FILTER_NAME_LIST[] = '����Ծ�'; // add 20160701
$D_FILTER_NAME_LIST[] = '�䥪�ޥ�/�������󥺥ޡ���/������';
$D_FILTER_NAME_LIST[] = '̴��/��ᤢ��Ʋ'; // mod 20150924
$D_FILTER_NAME_LIST[] = '��᥿����/���ޡ���/LECT'; // add 20170428
$D_FILTER_NAME_LIST[] = '�������Ļ�';
$D_FILTER_NAME_LIST[] = '�����'; // add 20160205
$D_FILTER_NAME_LIST[] = '�顡���ϥ�'; // add 20170613
$D_FILTER_NAME_LIST[] = '�ꥦ�ܥ����ȥ�'; // add 20150421
$D_FILTER_NAME_LIST[] = 'LIXIL���硼�롼��'; // add 20160318
$D_FILTER_NAME_LIST[] = 'LIXIL��ե����ॷ��å�'; // add 20160318
$D_FILTER_NAME_LIST[] = 'LIXIL��ե�����ͥå�'; // add 20160318
$D_FILTER_NAME_LIST[] = 'ΰ����';
$D_FILTER_NAME_LIST[] = '��åɥ���٥�';
$D_FILTER_NAME_LIST[] = '��󥺥�������'; // add 20160701
$D_FILTER_NAME_LIST[] = '��󥺥����쥯��'; // add 20160701
$D_FILTER_NAME_LIST[] = '���åƥꥢ';
$D_FILTER_NAME_LIST[] = 'WonderGOO'; // add 20160624
$D_FILTER_NAME_LIST[] = '���Τ�Ź';


// �����᤭�Ф�
if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
	ZdcEmapMsg.setImage('{$D_DIR_BASE_G}img/msg/0002.png',new ZdcSize(242,95),
	                    '{$D_DIR_BASE_G}img/msg/0002-t.png',new ZdcSize(194,67),
	                    '{$D_DIR_BASE_G}img/msg/0003-x.gif',new ZdcSize(13,20),
	                    '{$D_DIR_BASE_G}img/msg/0002-s.png',new ZdcSize(13,13),
	                    null);
	ZdcEmapMsg.setDocPosition(0,0,4,8,11,214,55,0);
	ZdcEmapMsg.setDocOffset(-110,-90);
	ZdcEmapMsg.setTextClass('UserMsgWindowTextStyle');
EOF;

?>