<?PHP
$D_DATA_CID = 'zen000';
$D_ICON_CID = 'zen000';

$D_Z2H_OPTION = "rnsk";

$D_CAPTION["s.htm"]["AREA_TITLE"]   = "#HOME#��ƻ�ܸ�����õ��";

$optcd = 1;
$D_OPTCD_USE_DETAIL = 1;
$D_OPTCD_USE_SHOP_AREA = 1;
$D_OPTCD_USE_SHOP_WORD = 1;
$D_OPTCD_DEF[1] = " COL_02:1 AND COL_04:8 ";//�����ե饰�������ȶ�ʬ

$SETTING["checkboxopt"] = 1;
$SETTING["tplptn"] = 2;
$OPTION = array(
	0=>array(
		4=>array('name'=>'K5','value'=>'1','jkn'=>'COL_33:1','title'=>'�Ďގ؎ݎ��ʎގ�'),
		12=>array('name'=>'K13','value'=>'1','jkn'=>'COL_43:1','title'=>'�͎ގˎގ�������'),
		13=>array('name'=>'K14','value'=>'1','jkn'=>'COL_44:1','title'=>'¿��Ū�Ď���'),
		14=>array('name'=>'K15','value'=>'1','jkn'=>'COL_45:1','title'=>'���ێ��̎�/���ڎ͎ގ�����'),
		15=>array('name'=>'K16','value'=>'1','jkn'=>'COL_46:1','title'=>'Ź�ގ̎ێ�1F'),
		16=>array('name'=>'K17','value'=>'1','jkn'=>'COL_48:1','title'=>'��־�'),
		18=>array('name'=>'K19','value'=>'1','jkn'=>'COL_50:1','title'=>'���ڎ��ގ��Ď����Ď����Ѳ�'),
		20=>array('name'=>'K21','value'=>'1','jkn'=>'COL_30:1 OR COL_30:2','title'=>'ī���ʎގ����ݎ���'),
		21=>array('name'=>'K22','value'=>'1','jkn'=>'COL_31:1','title'=>'��������'),
		22=>array('name'=>'K23','value'=>'1','jkn'=>'COL_72:1','title'=>'ZENSHO CooCa�谷Ź'),
		23=>array('name'=>'K24','value'=>'1','jkn'=>'COL_74:1','title'=>'���̷��Żҥޥ͡�'),
		24=>array('name'=>'K25','value'=>'1','jkn'=>'COL_78:1','title'=>'Edy���Ѳ�'),
		25=>array('name'=>'K26','value'=>'1','jkn'=>'COL_58:1','title'=>'iD���Ѳ�'),
		26=>array('name'=>'K27','value'=>'1','jkn'=>'COL_57:1','title'=>'QUICPay���Ѳ�'),
		'attribu'=>'AND'
	),
	1=>array(
		0=>array('name'=>'M1','value'=>'1','jkn'=>'COL_41:2','title'=>'�ر�'),
		1=>array('name'=>'M2','value'=>'1','jkn'=>'COL_41:1','title'=>'ʬ��'),
		2=>array('name'=>'M3','value'=>'1','jkn'=>'COL_41:3','title'=>'����ʬ��'),
		'attribu'=>'OR'
	),
	2=>array(
		54=>array('name'=>'C54','value'=>'1','jkn'=>'COL_03:8','title'=>'�ڲ�Ϳʼ��'),
		55=>array('name'=>'C55','value'=>'1','jkn'=>'COL_03:9','title'=>'�¿���ؤ�'),
		'attribu'=>'OR'
	),
	'attribu'=>'AND'
);
$SETTING["loc_optcheck"] = 1;

$D_TOP_TXT="�����Ď��̎ߤ����";
$D_CAPTION["s.htm"]["KEYWD_TITLE"]  = "#SEARCH#�����܎��Ďޤ�õ��";
$D_CAPTION["s.htm"]["LOCATIONMSG"]  = "���־����������뤿��ʲ��Ύ؎ݎ��򎸎؎������Ʋ�������";
$D_CAPTION["cl.htm"]["WARNING_TITLE"]= "<font color=\"red\">���؎��Ĥˤʤ���玤�����϶��@WORD@���������ޤ���</font>";
$D_AREA_TITLE = "���؎�����";
$D_FILTER_TITLE="�����܎��Ď��ѹ�";
$D_PAGE_AFTER="���͎ߎ�����";
$D_PAGE_BEFORE="���͎ߎ�����";

$AREA_INFO[0]["tod"] = '1|2|3|4|5|6|7';
$AREA_INFO[1]["tod"] = '13|14|11|12|10|9|8';
$AREA_INFO[2]["tod"] = '15|16|17|18';
$AREA_INFO[3]["tod"] = '23|19|22|20|21';
$AREA_INFO[4]["tod"] = '27|26|28|25|29|30|24';
$AREA_INFO[5]["tod"] = '34|33|35|31|32';
$AREA_INFO[6]["tod"] = '37|36|38|39';
$AREA_INFO[7]["tod"] = '40|41|42|43|44|45|46|47';
?>