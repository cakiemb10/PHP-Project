<?php
//========================================================
// �ޥ����ƥ�ץ졼��ID
//========================================================
$MST_ID	= "EasyDesign01";
//========================================================
// �����ӥ�����
//		"S"������������ɡ�"L"���饤�ȡ�"N"�������ʤ��ʥޥåץ�󥯡�
//========================================================
$PC_EMAP_KBN = "S";
//========================================================
// �ƥ�ץ졼�ȥե��������
//		key:�ƥ�ץ졼�ȥե�����̾
//		val(array):
//			"NM"=>Template Customizer ɽ��̾
//			"CR"=>Template Engine ���楳����̵ͭ("N"�����楳���ɤʤ�)
//			"ED"=>Template Customizer ������������("W"���Խ��ġ�"R"�����ȤΤ�)
//			"GP"=>Template Engine �������롼��("S"������ե�����Τߡ�"D"���ǥ���������ȿ��)
//========================================================
$TPL_FILE_DEF = array(
 "emapview_0.tpl"			=> array("NM"=>"���ܥ쥤������(TOP)",		"CR"=>"N",	"ED"=>"W")
,"emapview_1.tpl"			=> array("NM"=>"���ܥ쥤������(�إå�)",	"CR"=>"N",	"ED"=>"W")
,"emapview_5.tpl"			=> array("NM"=>"���ܥ쥤������",						"ED"=>"W")
,"emapview_8.tpl"			=> array("NM"=>"���ܥ쥤������(�եå�)",	"CR"=>"N",	"ED"=>"W")
,"emapview_9.tpl"			=> array("NM"=>"���ܥ쥤������(BOTTOM)",	"CR"=>"N",	"ED"=>"W")
,"emapview_shop_detail.tpl"	=> array("NM"=>"�����ܺ�",								"ED"=>"W")
,"emapview_shop_detail_nomap.tpl"	=> array("NM"=>"�����ܺ١��Ͽޤʤ���",			"ED"=>"W")
,"emapview_shop_list.tpl"	=> array("NM"=>"�����ꥹ��",							"ED"=>"W")
,"emapview_msg.tpl"			=> array("NM"=>"�������",								"ED"=>"W")
,"emapview_cond.tpl"		=> array("NM"=>"�����ʹ����",							"ED"=>"W")
,"emapview_npoi_list.tpl"	=> array("NM"=>"���ջ��ߥꥹ��",			"CR"=>"N",	"ED"=>"W")
,"emapview_jnr.tpl"			=> array("NM"=>"���ߥ�������",						"ED"=>"W")
,"emapview_neki.tpl"		=> array("NM"=>"�Ǵ�إꥹ��",							"ED"=>"W")
,"emapview_froute.tpl"		=> array("NM"=>"��ȯ�ϻ���롼��õ��",					"ED"=>"W")
,"emapview_error.tpl"		=> array("NM"=>"���顼����",							"ED"=>"W")
,"print_0.tpl"				=> array("NM"=>"��������(TOP)",				"CR"=>"N",	"ED"=>"W")
,"print_1.tpl"				=> array("NM"=>"��������(�إå�)",			"CR"=>"N",	"ED"=>"W")
,"print_5.tpl"				=> array("NM"=>"��������",								"ED"=>"W")
,"print_8.tpl"				=> array("NM"=>"��������(�եå�)",			"CR"=>"N",	"ED"=>"W")
,"print_9.tpl"				=> array("NM"=>"��������(BOTTOM)",			"CR"=>"N",	"ED"=>"W")
,"search_shop_list_print.tpl"=> array("NM"=>"�����ꥹ�Ȱ�������",					"ED"=>"W")
,"search_top.tpl"			=> array("NM"=>"��������",								"ED"=>"W")
,"search_rail.tpl"			=> array("NM"=>"ϩ���޸���",				"CR"=>"N",	"ED"=>"W")
,"search_area.tpl"			=> array("NM"=>"�ϰ�޸���",				"CR"=>"N",	"ED"=>"W")
,"search_shop_list.tpl"		=> array("NM"=>"������̵�������",						"ED"=>"W")
,"search_list.tpl"			=> array("NM"=>"������̹��ܰ���",			"CR"=>"N",	"ED"=>"W")
,"search_table.tpl"			=> array("NM"=>"�������ʬ��ɽ",			"CR"=>"N",	"ED"=>"W")
,"search_addrtable.tpl"		=> array("NM"=>"���������ƻ�ܸ�ɽ",		"CR"=>"N",	"ED"=>"W")
,"search_error.tpl"			=> array("NM"=>"�������顼����",			"CR"=>"N",	"ED"=>"W")
,"setting.inc"				=> array("NM"=>"����ե�����",							"ED"=>"R", "GP"=>"S")
,"setting_option.inc"		=> array("NM"=>"���ץ��������ե�����",	"CR"=>"N",	"ED"=>"W")
,"css/default.css"			=> array("NM"=>"default.css",				"CR"=>"N",	"ED"=>"W")
,"css/layout.css"			=> array("NM"=>"layout.css",							"ED"=>"W", "GP"=>"D")
,"css/base.css"				=> array("NM"=>"base.css",								"ED"=>"W", "GP"=>"D")
,"css/print_page.css"		=> array("NM"=>"print_page.css",						"ED"=>"W", "GP"=>"D")
,"css/print.css"			=> array("NM"=>"print.css",					"CR"=>"N",	"ED"=>"W")
,"css/print2.css"			=> array("NM"=>"print2.css",				"CR"=>"N",	"ED"=>"W")
,"css/print_list.css"		=> array("NM"=>"print_list.css",						"ED"=>"W", "GP"=>"D")
,"css/custom.css"			=> array("NM"=>"custom.css",				"CR"=>"N",	"ED"=>"W")
,"js/custom.js"				=> array("NM"=>"custom.js",					"CR"=>"N",	"ED"=>"W")
);
?>