<?php
//========================================================
// �ޥ����ƥ�ץ졼��ID
//========================================================
$MST_ID = "P2EasyDesign01";
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
 "pageview_0.tpl"			=> array("NM"=>"���ܥ쥤������(TOP)",		"CR"=>"N",	"ED"=>"W")
,"pageview_1.tpl"			=> array("NM"=>"���ܥ쥤������(�إå�)",	"CR"=>"N",	"ED"=>"W")
,"pageview_2.tpl"			=> array("NM"=>"���ܥ쥤������(�ᥤ�����)",			"ED"=>"W")
,"pageview_7.tpl"			=> array("NM"=>"���ܥ쥤������(�ᥤ����)","CR"=>"N",	"ED"=>"W")
,"pageview_8.tpl"			=> array("NM"=>"���ܥ쥤������(�եå�)",	"CR"=>"N",	"ED"=>"W")
,"pageview_9.tpl"			=> array("NM"=>"���ܥ쥤������(BOTTOM)",	"CR"=>"N",	"ED"=>"W")
,"nmap.tpl"					=> array("NM"=>"�Ǵ��Ź���Ͽ�",						"ED"=>"W")
,"nlist.tpl"				=> array("NM"=>"�Ǵ��Ź�ޥꥹ��",						"ED"=>"W")
,"msg.tpl"					=> array("NM"=>"�ե�����",								"ED"=>"W")
,"cond.tpl"					=> array("NM"=>"�ʹ����",								"ED"=>"W")
,"shop_dtl.tpl"				=> array("NM"=>"Ź�޾ܺ�(�Ͽ�)",						"ED"=>"W")
,"neki.tpl"					=> array("NM"=>"�Ǵ�إꥹ��",							"ED"=>"W")
,"npoi.tpl"					=> array("NM"=>"���ջ��ߥꥹ��",			"CR"=>"N",	"ED"=>"W")
,"npoi_jnr.tpl"				=> array("NM"=>"���ջ��ߥ�����",						"ED"=>"W")
,"froute.tpl"				=> array("NM"=>"��ȯ�ϻ���롼��",						"ED"=>"W")
,"errorview.tpl"			=> array("NM"=>"���顼����",							"ED"=>"W")
,"shop_print_0.tpl"			=> array("NM"=>"��������(TOP)",				"CR"=>"N",	"ED"=>"W")
,"shop_print_1.tpl"			=> array("NM"=>"��������(�إå�)",			"CR"=>"N",	"ED"=>"W")
,"shop_print_5.tpl"			=> array("NM"=>"��������",								"ED"=>"W")
,"shop_print_8.tpl"			=> array("NM"=>"��������(�եå�)",			"CR"=>"N",	"ED"=>"W")
,"shop_print_9.tpl"			=> array("NM"=>"��������(BOTTOM)",			"CR"=>"N",	"ED"=>"W")
,"search_top.tpl"			=> array("NM"=>"��������",								"ED"=>"W")
,"search_rail.tpl"			=> array("NM"=>"ϩ����",					"CR"=>"N",	"ED"=>"W")
,"search_area.tpl"			=> array("NM"=>"�ϰ��",					"CR"=>"N",	"ED"=>"W")
,"search_shop_list.tpl"		=> array("NM"=>"Ź�޸����ꥹ��",						"ED"=>"W")
,"search_list.tpl"			=> array("NM"=>"�����ꥹ��",				"CR"=>"N",	"ED"=>"W")
,"search_list_comb.tpl"		=> array("NM"=>"ʣ��FW�ꥹ��",				"CR"=>"N",	"ED"=>"W")
,"search_table.tpl"			=> array("NM"=>"�����ơ��֥�",				"CR"=>"N",	"ED"=>"W")
,"search_addrtable.tpl"		=> array("NM"=>"���긡���ơ��֥�",			"CR"=>"N",	"ED"=>"W")
,"search_error.tpl"			=> array("NM"=>"�������顼����",			"CR"=>"N",	"ED"=>"W")
,"jump.tpl"					=> array("NM"=>"top.location�ѹ���",		"CR"=>"N",	"ED"=>"W")
,"setting.inc"				=> array("NM"=>"����ե�����",							"ED"=>"R", "GP"=>"S")
,"setting_option.inc"		=> array("NM"=>"���ץ��������ե�����",	"CR"=>"N",	"ED"=>"W")
,"css/default.css"			=> array("NM"=>"default.css",				"CR"=>"N",	"ED"=>"W")
,"css/layout.css"			=> array("NM"=>"layout.css",							"ED"=>"W", "GP"=>"D")
,"css/base.css"				=> array("NM"=>"base.css",								"ED"=>"W", "GP"=>"D")
,"css/print_page.css"		=> array("NM"=>"print_page.css",						"ED"=>"W", "GP"=>"D")
,"css/print.css"			=> array("NM"=>"print.css",					"CR"=>"N",	"ED"=>"W")
,"css/custom.css"			=> array("NM"=>"custom.css",				"CR"=>"N",	"ED"=>"W")
,"js/custom.js"				=> array("NM"=>"custom.js",					"CR"=>"N",	"ED"=>"W")
);
?>