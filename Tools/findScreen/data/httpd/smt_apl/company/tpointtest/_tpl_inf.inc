<?php
//========================================================
// �ޥ����ƥ�ץ졼��ID
//========================================================
$MST_ID	= "Standard01";
//========================================================
// �����ӥ�����
//		"S"������������ɡ�"L"���饤�ȡ�"N"�������ʤ��ʥޥåץ�󥯡�
//========================================================
$SMT_EMAP_KBN = "S";
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
,"pageview_2.tpl"			=> array("NM"=>"���ܥ쥤������",			"CR"=>"N",	"ED"=>"W")
,"pageview_8.tpl"			=> array("NM"=>"���ܥ쥤������(�եå�)",	"CR"=>"N",	"ED"=>"W")
,"pageview_9.tpl"			=> array("NM"=>"���ܥ쥤������(BOTTOM)",	"CR"=>"N",	"ED"=>"W")
,"mapview_0.tpl"			=> array("NM"=>"�Ͽޥ쥤������(TOP)",		"CR"=>"N",	"ED"=>"W")
,"mapview_9.tpl"			=> array("NM"=>"�Ͽޥ쥤������(BOTTOM)",	"CR"=>"N",	"ED"=>"W")
,"inf.tpl"					=> array("NM"=>"Ź�޾ܺ�",								"ED"=>"W")
,"map.tpl"					=> array("NM"=>"Ź���Ͽ�",					"CR"=>"N",	"ED"=>"W")
,"msg.tpl"					=> array("NM"=>"�ե�����",					"CR"=>"N",	"ED"=>"W")
,"search.tpl"				=> array("NM"=>"����TOP",								"ED"=>"W")
,"search_pl.tpl"			=> array("NM"=>"����(���)",							"ED"=>"W")
,"search_addr.tpl"			=> array("NM"=>"����ꥹ��",				"CR"=>"N",	"ED"=>"W")
,"search_addr_list.tpl"		=> array("NM"=>"����ꥹ��(����)",			"CR"=>"N",	"ED"=>"W")
,"search_eki.tpl"			=> array("NM"=>"�إꥹ��",					"CR"=>"N",	"ED"=>"W")
,"search_eki_list.tpl"		=> array("NM"=>"�إꥹ��(����)",			"CR"=>"N",	"ED"=>"W")
,"search_rosen.tpl"			=> array("NM"=>"ϩ���ꥹ��",				"CR"=>"N",	"ED"=>"W")
,"search_rosen_list.tpl"	=> array("NM"=>"ϩ���ꥹ��(����)",			"CR"=>"N",	"ED"=>"W")
,"search_poi.tpl"			=> array("NM"=>"���ߥꥹ��",				"CR"=>"N",	"ED"=>"W")
,"search_poi_list.tpl"		=> array("NM"=>"���ߥꥹ��(����)",			"CR"=>"N",	"ED"=>"W")
,"search_fw.tpl"			=> array("NM"=>"�ե꡼��ɸ���",			"CR"=>"N",	"ED"=>"W")
,"search_fw_list.tpl"		=> array("NM"=>"�ե꡼��ɸ���(����)",	"CR"=>"N",	"ED"=>"W")
,"loc.tpl"					=> array("NM"=>"��������³",				"CR"=>"N",	"ED"=>"W")
,"n.tpl"					=> array("NM"=>"�Ǵ��Ź�ޥꥹ��",			"CR"=>"N",	"ED"=>"W")
,"n_list.tpl"				=> array("NM"=>"�Ǵ��Ź�ޥꥹ��(����)",	"CR"=>"N",	"ED"=>"W")
,"nmap.tpl"					=> array("NM"=>"�Ǵ��Ź���Ͽ�",			"CR"=>"N",	"ED"=>"W")
,"sl.tpl"					=> array("NM"=>"Ź�ޥꥹ�ȸ���",			"CR"=>"N",	"ED"=>"W")
,"sl_list.tpl"				=> array("NM"=>"Ź�ޥꥹ�ȸ���(����)",		"CR"=>"N",	"ED"=>"W")
,"fw.tpl"					=> array("NM"=>"Ź�ޥե꡼��ɸ���",		"CR"=>"N",	"ED"=>"W")
,"fw_list.tpl"				=> array("NM"=>"Ź�ޥե꡼��ɸ���(����)","CR"=>"N",	"ED"=>"W")
,"ne.tpl"					=> array("NM"=>"�Ǵ��إꥹ��",			"CR"=>"N",	"ED"=>"W")
,"ne_list.tpl"				=> array("NM"=>"�Ǵ��إꥹ��(����)",		"CR"=>"N",	"ED"=>"W")
,"np.tpl"					=> array("NM"=>"�Ǵ����ߥꥹ��",			"CR"=>"N",	"ED"=>"W")
,"np_list.tpl"				=> array("NM"=>"�Ǵ����ߥꥹ��(����)",	"CR"=>"N",	"ED"=>"W")
,"route_srch_pl.tpl"		=> array("NM"=>"��ȯ�ϻ���롼��(��긡��)",			"ED"=>"W")
,"errorview.tpl"			=> array("NM"=>"���顼����",				"CR"=>"N",	"ED"=>"W")
,"error.tpl"				=> array("NM"=>"���顼��å�����",			"CR"=>"N",	"ED"=>"W")
,"setting.inc"				=> array("NM"=>"����ե�����",							"ED"=>"R", "GP"=>"S")
,"setting_option.inc"		=> array("NM"=>"���ץ��������ե�����",	"CR"=>"N",	"ED"=>"W")
,"css/reset.css"			=> array("NM"=>"reset.css",					"CR"=>"N",	"ED"=>"W")
,"css/smart.css"			=> array("NM"=>"smart.css",					"CR"=>"N",	"ED"=>"W")
,"css/map.css"				=> array("NM"=>"map.css",					"CR"=>"N",	"ED"=>"W")
,"css/custom.css"			=> array("NM"=>"custom.css",				"CR"=>"N",	"ED"=>"W")
,"js/custom.js"				=> array("NM"=>"custom.js",					"CR"=>"N",	"ED"=>"W")
);
?>