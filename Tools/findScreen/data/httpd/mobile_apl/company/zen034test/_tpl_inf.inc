<?php
//========================================================
// �ޥ����ƥ�ץ졼��ID
//========================================================
$MST_ID = "01";
//========================================================
// �ƥ�ץ졼�ȥե��������
//      key:�ƥ�ץ졼�ȥե�����̾
//      val(array):
//          "NM"=>Template Customizer ɽ��̾
//          "CR"=>Template Engine ���楳����̵ͭ("N"�����楳���ɤʤ�)
//          "ED"=>Template Customizer ������������("W"���Խ��ġ�"R"�����ȤΤ�)
//          "GP"=>Template Engine �������롼��("S"������ե�����Τ�)
//          "MS"=>(����)�����ӥ���ʬ("S"������������ɡ�"L"���饤�ȡ�"N"�������ʤ��饤��)
//========================================================
$TPL_FILE_DEF = array(
 "top.tpl"              => array("NM"=>"TOP����",              "CR"=>"N", "ED"=>"W",            "MS"=>"S|N")
,"top2.tpl"             => array("NM"=>"TOP����2",             "CR"=>"N", "ED"=>"W",            "MS"=>"S|N")
,"header.tpl"           => array("NM"=>"�إå�",               "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"header_light.tpl"     => array("NM"=>"�إå�(Light)",        "CR"=>"N", "ED"=>"W",            "MS"=>"L|N")
,"footer.tpl"           => array("NM"=>"�եå�",               "CR"=>"N", "ED"=>"W",            "MS"=>"S|N")
,"footer_light.tpl"     => array("NM"=>"�եå�(Light)",        "CR"=>"N", "ED"=>"W",            "MS"=>"L|N")
,"list.tpl"             => array("NM"=>"��������",                        "ED"=>"W",            "MS"=>"S|L|N")
,"dt.tpl"               => array("NM"=>"�����ܺٲ���",                    "ED"=>"W",            "MS"=>"S|L|N")
,"map.tpl"              => array("NM"=>"�Ͽ޲���",                        "ED"=>"W",            "MS"=>"S|L|N")
,"topssr.tpl"           => array("NM"=>"��ȯ������롼�Ȱ���", "CR"=>"N", "ED"=>"W",            "MS"=>"S")
,"help.tpl"             => array("NM"=>"�Ͽް�ư�إ�ײ���",   "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"err.tpl"              => array("NM"=>"���顼����",           "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"loc.tpl"              => array("NM"=>"���־������",         "CR"=>"N", "ED"=>"W",            "MS"=>"S")
,"copyright.tpl"        => array("NM"=>"���ɽ��"   ,        "CR"=>"N", "ED"=>"R",            "MS"=>"S|L|N")
,"setting.inc"          => array("NM"=>"����ե�����",                    "ED"=>"W", "GP"=>"S", "MS"=>"S|L|N")
,"setting_option.inc"   => array("NM"=>"���ץ��������",       "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"design.inc"           => array("NM"=>"�ǥ���������ե�����",            "ED"=>"W",            "MS"=>"S|L|N")
);
?>