<?PHP
// ------------------------------------------------------------
// ���Ѵؿ�php
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2009/02/23 Y.Matsukawa	�����ܺ٤˼�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/06/17 Y.Matsukawa	����URL�ʾܺٲ��̡ˤ��ɲ�
// 2009/08/24 Y.Matsukawa	IP����
// 2009/09/04 Y.Matsukawa	�����̼�
// 2009/09/08 Y.Matsukawa	��������256�Х��ȴݤ�
// 2009/09/14 Y.Matsukawa	�������פ�256�Х��ȤǤ�ޤ����顼�ˤʤ�Τ�128�Х��Ȥ��ѹ�
// 2009/11/07 Y.Matsukawa	�������ܳ�ĥ��50��200��
// 2010/01/18 Y.Matsukawa	���Զ�罤���ۥե꡼��ɤ˥��ڡ������ޤޤ�Ƥ����硢Ⱦ�ѥ��ڡ������ߤΤޤޥ������Ϥ���Ƥ��ޤ����������ܶ��ڤ꤬�����ˤʤ�
// 2010/02/10 Y.Matsukawa	�������ϡ��ե꡼���128�Х��ȴݤ�
// 2010/04/08 Y.Matsukawa	�ȼ����к��ʥ����������ȥ�����ץƥ��󥰡�
// 2010/04/19 Y.Matsukawa	�ȼ����к���log�ǥ��쥯�ȥ��ư��
// 2010/05/17 Y.Matsukawa	function.incñ�Τ�include���Ƥ⥨�顼�ˤʤ�ʤ��褦��$D_REMOVE_QUOTE_PARAMS�����
// 2010/06/16 Y.Matsukawa	��ȯ�Ϥ���ꤷ�ƥ롼��õ��
// 2010/07/06 Y.Matsukawa	��812SH�Զ���б���812SH��URL��������ȡ�������=���դ��Ƥ��ޤ��Τǡ�URL������&�ǽ���餻��褦�˲���
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2010/09/07 Y.Matsukawa	��ȯ�Ϥ���ꤷ�ƥ롼��õ����Light��Maplink��
// 2010/09/13 Y.Matsukawa	�����ܺ�ɽ�����˵���ID��Cookie��¸
// 2010/10/01 Y.Matsukawa	�������ϻ������ƤΥѥ�᡼���Υ��ڡ����ִ��ȷ��·����»ܡ��������������б���
// 2011/02/22 Y.Matsukawa	���Զ�罤������������������GET�ѥ�᡼����������ꤵ�줿���������ʥ��������Ϥ����
// 2011/04/18 H.Osamoto		�����¸ʸ�������å�(IzonSearch)���ɲ�
// 2011/05/23 K.Masuda		��ͳ���ܳ�ĥ��p_f,p_s��50�ޤǡ�
// 2011/06/21 Y.Matsukawa	���ID��ƥ�ץ졼�Ȥ˰��Ϥ�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/08/15 Y.Matsukawa	�������̤�Ǥ�եѥ�᡼������Ϥ�
// 2011/10/28 K.Masuda		Cookie�ɤ߹���
// 2011/11/25 Y.Matsukawa	�ԡ������ǥ��б��ʺǴ��롼�����ѥ⡼�ɡ�
// 2012/03/19 SKC			UA���饭��ꥢȽ���ɲ�
// 2012/05/28 K.Masuda		�����̼ܼ�����������
// 2012/06/19 Y.Matsukawa	Ź�޾ܺ�Cookie��¸��ǽ�ɲá�Ǥ�ե����ߥ󥰤���¸�����ꥢ�������ؿ���
// 2012/07/06 Y.Matsukawa	���Զ�罤����IP�����å������֥ͥåȥޥ����б������å����ǥ���
// 2012/08/03 H.osamoto		��§ʸ�������б�(��'�ס�"�ס�>�ס�\�ס�`�סʥХå��������ȡ�)�����
// 2013/02/07 H.osamoto		��§ʸ�����¤��Զ���б�
// 2013/07/19 T.Sasaki		������ʣ���˲����б�
// 2014/02/07 F.Yokoi		QR�����ɤ�URL�����URL��Ǥ�ե������(col_**)���ѹ����뤿����ѿ����ɲ�
// 2015/05/22 H.osamoto		�����̼ܤ˥�����ɤ���Ϳ������ư���ɤ�
// ------------------------------------------------------------
// ------------------------------------------------------------
//
// �������Х��ɬ���¹Ԥ�����
//
// ------------------------------------------------------------
// �����ͤ�̷����� -----------------------------------------
// �ƽ̼ܤ����硦�Ǿ���Ķ���Ƥ��ޤäƤ�����
//
// mod 2011/07/05 Y.Nakajima [
//define_action.inc�����Ƥ򥳥ԡ�
if(!isset($D_INIT_LVL))        $D_INIT_LVL        = 1;//���ɽ��
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH = -1;//���ָ���������-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = -1;//�ܺ�������-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
if(!isset($D_INIT_LVL_PRINT))  $D_INIT_LVL_PRINT   = -1;//�������̡�-1��$D_INIT_LVL�˽स���

if (isset($D_MAP_SCALE_MAX)) {
if($D_INIT_LVL < $D_MAP_SCALE_MAX)                                    $D_INIT_LVL = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_SEARCH != -1 && $D_INIT_LVL_SEARCH < $D_MAP_SCALE_MAX) $D_INIT_LVL_SEARCH = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_DETAIL != -1 && $D_INIT_LVL_DETAIL < $D_MAP_SCALE_MAX) $D_INIT_LVL_DETAIL = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_PRINT != -1 && $D_INIT_LVL_PRINT < $D_MAP_SCALE_MAX)   $D_INIT_LVL_PRINT = $D_MAP_SCALE_MAX;
}
if (isset($D_MAP_SCALE_MIN)) {
if($D_INIT_LVL > $D_MAP_SCALE_MIN)                                    $D_INIT_LVL = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_SEARCH != -1 && $D_INIT_LVL_SEARCH > $D_MAP_SCALE_MIN) $D_INIT_LVL_SEARCH = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_DETAIL != -1 && $D_INIT_LVL_DETAIL > $D_MAP_SCALE_MIN) $D_INIT_LVL_DETAIL = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_PRINT != -1 && $D_INIT_LVL_PRINT > $D_MAP_SCALE_MIN)   $D_INIT_LVL_PRINT = $D_MAP_SCALE_MIN;
}
// mod 2011/07/05 Y.Nakajima ]

if (!isset($D_REMOVE_QUOTE_PARAMS)) $D_REMOVE_QUOTE_PARAMS = array();		// add 2010/05/17 Y.Matsukawa
// �ѥ�᡼���δ������� ------------------------------------
foreach( $_POST as $key=>$val) {
	if (is_string($key) && is_string($val)) {		// add 2011/02/22 Y.Matsukawa
		$val = htmlspecialchars($val);
		//$val = addslashes($val);
		if($key!="") {
			// add 2010/04/08 Y.Matsukawa [
			// ���󥰥륯�����Ƚ���
			if ($val != "" && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
				//error_log("remove quote [$key][$val]", 3, "/var/tmp/php_debug.log");
				$val = mb_ereg_replace("'", "", $val);
				//error_log("->[$val] (".$_SERVER["SCRIPT_FILENAME"].")\n", 3, "/var/tmp/php_debug.log");
			}
			// add 2010/04/08 Y.Matsukawa ]
			${$key} = $val;
			$_POST[$key] = $val;
			$_VARS[$key] = $val;
		}
	}
}
foreach( $_GET as $key=>$val) {
	if (is_string($key) && is_string($val)) {		// add 2011/02/22 Y.Matsukawa
		$val = htmlspecialchars($val);
		//$val = addslashes($val);
		if($key!="") {
			// add 2010/04/08 Y.Matsukawa [
			// ���󥰥륯�����Ƚ���
			if ($val != "" && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
				//error_log("remove quote [$key][$val]", 3, "/var/tmp/php_debug.log");
				$val = mb_ereg_replace("'", "", $val);
				//error_log("->[$val] (".$_SERVER["SCRIPT_FILENAME"].")\n", 3, "/var/tmp/php_debug.log");
			}
			// add 2010/04/08 Y.Matsukawa ]
			${$key} = $val;
			$_GET[$key] = $val;
			$_VARS[$key] = $val;
		}
	}
}
if (isset($_VARS) && is_array($_VARS)) {
	$_VARS = array_merge($_VARS,$_SERVER);
} else {
	$_VARS = $_SERVER;
}

// �ƥ�ץ졼�Ƚ���� --------------------------------------
//asp/�Υե����뤫��ƤФ줿�Ȥ��ϡ�define.inc��call���Ƥ��ʤ��Τ������̵��
//asp/�Υե���������ƽ�������Τϡ���֤ʤΤǡ���������б�
// mod 2011/07/05 Y.Nakajima [
if (isset($D_CID)) {
$tpl["D_CID"] = $D_CID;		// add 2011/06/21 Y.Matsukawa
} else {
$tpl["D_CID"] = "";
}
if (isset($D_USER_DEFNAME)) {
$tpl["D_USER_DEFNAME"]      = $D_USER_DEFNAME;
} else {
$tpl["D_USER_DEFNAME"]      = "";
}
if (isset($D_USER_SERVICENAME)) {
$tpl["D_USER_SERVICENAME"]  = $D_USER_SERVICENAME;
} else {
$tpl["D_USER_SERVICENAME"]  = "";
}
// mod 2011/07/05 Y.Nakajima ]
//$tpl["D_DIR_BASE"]          = $D_DIR_BASE;		mod 2010/07/20 Y.Matsukawa
// mod 2011/07/05 Y.Nakajima [
if (isset($D_DIR_BASE_G)) {
$tpl["D_DIR_BASE"]          = $D_DIR_BASE_G;
} else {
$tpl["D_DIR_BASE"]          = "";
}
if (isset($D_DIR_COMPANY)) {
$tpl["D_DIR_COMPANY"]       = $D_DIR_COMPANY;
} else {
$tpl["D_DIR_COMPANY"]       = "";
}
if (isset($D_HISTORY_TOP_LINK)) {
$tpl["D_HISTORY_TOP_LINK"]  = $D_HISTORY_TOP_LINK;
} else {
$tpl["D_HISTORY_TOP_LINK"]  = "";
}
// mod 2011/07/05 Y.Nakajima ]
$tpl["_jsSearchWindow"]     = "ZdcEmapSearchClick()";
//��ͳ����(�����˻��ꤷ�ƻȤ�)
// mod 2011/05/23 K.Masuda [
//$tpl["P_STRING_1"]  = $p_s1;
//$tpl["P_STRING_2"]  = $p_s2;
//$tpl["P_STRING_3"]  = $p_s3;
//$tpl["P_STRING_4"]  = $p_s4;
//$tpl["P_STRING_5"]  = $p_s5;
//$tpl["P_STRING_6"]  = $p_s6;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_7"]  = $p_s7;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_8"]  = $p_s8;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_9"]  = $p_s9;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_10"] = $p_s10;		// add 2010/05/11 Y.Matsukawa
for($pcnt=1;$pcnt<=50;$pcnt++){
    // mod 2011/07/05 Y.Nakajima [
	if (isset(${"p_s".$pcnt})) {
		$tpl["P_STRING_".$pcnt]  = ${"p_s".$pcnt};
	} else {
		$tpl["P_STRING_".$pcnt]  = "";
	}
    // mod 2011/07/05 Y.Nakajima ]
}
//$tpl["P_FLG_1"]  = $p_f1;
//$tpl["P_FLG_2"]  = $p_f2;
//$tpl["P_FLG_3"]  = $p_f3;
//$tpl["P_FLG_4"]  = $p_f4;
//$tpl["P_FLG_5"]  = $p_f5;
//$tpl["P_FLG_6"]  = $p_f6;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_7"]  = $p_f7;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_8"]  = $p_f8;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_9"]  = $p_f9;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_10"] = $p_f10;		// add 2010/05/11 Y.Matsukawa
for($pcnt=1;$pcnt<=50;$pcnt++){
    // mod 2011/07/05 Y.Nakajima [
	if (isset(${"p_f".$pcnt})) {
		$tpl["P_FLG_".$pcnt]  = ${"p_f".$pcnt};
	} else {
		$tpl["P_FLG_".$pcnt]  = "";
	}
    // mod 2011/07/05 Y.Nakajima ]
}
// mod 2011/05/23 K.Masuda ]
//��ͳ���ܡʰ����Ϥ��ѡ�		add 2009/02/23 Y.Matsukawa
//add 2011/07/05 Y.Nakajima [
if (!isset($p_s1)) $p_s1 = "";
if (!isset($p_s2)) $p_s2 = "";
if (!isset($p_s3)) $p_s3 = "";
if (!isset($p_s4)) $p_s4 = "";
if (!isset($p_s5)) $p_s5 = "";
if (!isset($p_f1)) $p_f1 = "";
if (!isset($p_f2)) $p_f2 = "";
if (!isset($p_f3)) $p_f3 = "";
if (!isset($p_f4)) $p_f4 = "";
if (!isset($p_f5)) $p_f5 = "";
//add 2011/07/05 Y.Nakajima ]

$P_FREEPARAMS = sprintf("p_s1=%s&p_s2=%s&p_s3=%s&p_s4=%s&p_s5=%s&p_f1=%s&p_f2=%s&p_f3=%s&p_f4=%s&p_f5=%s"
,urldecode(ZdcConvertEncoding($p_s1))
,urldecode(ZdcConvertEncoding($p_s2))
,urldecode(ZdcConvertEncoding($p_s3))
,urldecode(ZdcConvertEncoding($p_s4))
,urldecode(ZdcConvertEncoding($p_s5))
,urldecode(ZdcConvertEncoding($p_f1))
,urldecode(ZdcConvertEncoding($p_f2))
,urldecode(ZdcConvertEncoding($p_f3))
,urldecode(ZdcConvertEncoding($p_f4))
,urldecode(ZdcConvertEncoding($p_f5))
);
// mod 2011/05/23 K.Masuda [
//// add 2010/05/11 Y.Matsukawa [
//if($p_s6)  $P_FREEPARAMS .= "&p_s6=". urldecode(ZdcConvertEncoding($p_s6));
//if($p_s7)  $P_FREEPARAMS .= "&p_s7=". urldecode(ZdcConvertEncoding($p_s7));
//if($p_s8)  $P_FREEPARAMS .= "&p_s8=". urldecode(ZdcConvertEncoding($p_s8));
//if($p_s9)  $P_FREEPARAMS .= "&p_s9=". urldecode(ZdcConvertEncoding($p_s9));
//if($p_s10) $P_FREEPARAMS .= "&p_s10=".urldecode(ZdcConvertEncoding($p_s10));
for($pcnt=6;$pcnt<=50;$pcnt++){
    // mod 2011/07/05 Y.Nakajima
	//if(${p_s.$pcnt}) $P_FREEPARAMS .= "&p_s".$pcnt."=".urldecode(ZdcConvertEncoding(${p_s.$pcnt}));
	if(isset(${"p_s".$pcnt})) $P_FREEPARAMS .= "&p_s".$pcnt."=".urldecode(ZdcConvertEncoding(${"p_s".$pcnt}));
}
//if($p_f6)  $P_FREEPARAMS .= "&p_f6=". urldecode(ZdcConvertEncoding($p_f6));
//if($p_f7)  $P_FREEPARAMS .= "&p_f7=". urldecode(ZdcConvertEncoding($p_f7));
//if($p_f8)  $P_FREEPARAMS .= "&p_f8=". urldecode(ZdcConvertEncoding($p_f8));
//if($p_f9)  $P_FREEPARAMS .= "&p_f9=". urldecode(ZdcConvertEncoding($p_f9));
//if($p_f10) $P_FREEPARAMS .= "&p_f10=".urldecode(ZdcConvertEncoding($p_f10));
for($pcnt=6;$pcnt<=50;$pcnt++){
    // mod 2011/07/05 Y.Nakajima
	//if(${p_f.$pcnt}) $P_FREEPARAMS .= "&p_f".$pcnt."=".urldecode(ZdcConvertEncoding(${p_f.$pcnt}));
	if(isset(${"p_f".$pcnt})) $P_FREEPARAMS .= "&p_f".$pcnt."=".urldecode(ZdcConvertEncoding(${"p_f".$pcnt}));
}
// mod 2011/05/23 K.Masuda ]
// mod 2011/07/05 Y.Nakajima
if(isset($lm) && $lm && isset($D_MYAREA_USE) && $D_MYAREA_USE)    $P_FREEPARAMS .= "&lm=".urldecode(ZdcConvertEncoding($lm));	// add 2011/04/18 H.osamoto
// add 2010/05/11 Y.Matsukawa ]
// add 2010/05/13 Y.Matsukawa [
$wk_freeparams = array();
// mod 2011/05/23 K.Masuda [
//if($p_s1)  $wk_freeparams[] = "p_s1=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s1),'SJIS','EUC-JP'));
//if($p_s2)  $wk_freeparams[] = "p_s2=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s2),'SJIS','EUC-JP'));
//if($p_s3)  $wk_freeparams[] = "p_s3=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s3),'SJIS','EUC-JP'));
//if($p_s4)  $wk_freeparams[] = "p_s4=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s4),'SJIS','EUC-JP'));
//if($p_s5)  $wk_freeparams[] = "p_s5=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s5),'SJIS','EUC-JP'));
//if($p_s6)  $wk_freeparams[] = "p_s6=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s6),'SJIS','EUC-JP'));
//if($p_s7)  $wk_freeparams[] = "p_s7=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s7),'SJIS','EUC-JP'));
//if($p_s8)  $wk_freeparams[] = "p_s8=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s8),'SJIS','EUC-JP'));
//if($p_s9)  $wk_freeparams[] = "p_s9=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s9),'SJIS','EUC-JP'));
//if($p_s10) $wk_freeparams[] = "p_s10=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s10),'SJIS','EUC-JP'));
for($pcnt=1;$pcnt<=50;$pcnt++){
    // mod 2011/07/05 Y.Nakajima
	//if(${p_s.$pcnt}) $wk_freeparams[] = "p_s".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${p_s.$pcnt}),'SJIS','EUC-JP'));
	if(isset(${"p_s".$pcnt})) $wk_freeparams[] = "p_s".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${"p_s".$pcnt}),'SJIS','eucJP-win'));
}
//if($p_f1)  $wk_freeparams[] = "p_f1=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f1),'SJIS','EUC-JP'));
//if($p_f2)  $wk_freeparams[] = "p_f2=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f2),'SJIS','EUC-JP'));
//if($p_f3)  $wk_freeparams[] = "p_f3=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f3),'SJIS','EUC-JP'));
//if($p_f4)  $wk_freeparams[] = "p_f4=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f4),'SJIS','EUC-JP'));
//if($p_f5)  $wk_freeparams[] = "p_f5=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f5),'SJIS','EUC-JP'));
//if($p_f6)  $wk_freeparams[] = "p_f6=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f6),'SJIS','EUC-JP'));
//if($p_f7)  $wk_freeparams[] = "p_f7=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f7),'SJIS','EUC-JP'));
//if($p_f8)  $wk_freeparams[] = "p_f8=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f8),'SJIS','EUC-JP'));
//if($p_f9)  $wk_freeparams[] = "p_f9=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f9),'SJIS','EUC-JP'));
//if($p_f10) $wk_freeparams[] = "p_f10=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f10),'SJIS','EUC-JP'));
for($pcnt=1;$pcnt<=50;$pcnt++){
    // mod 2011/07/05 Y.Nakajima
	//if(${p_f.$pcnt}) $wk_freeparams[] = "p_f".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${p_f.$pcnt}),'SJIS','EUC-JP'));
	if(isset(${"p_f".$pcnt})) $wk_freeparams[] = "p_f".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${"p_f".$pcnt}),'SJIS','eucJP-win'));
}
// mod 2011/05/23 K.Masuda ]
// mod 2011/07/05 Y.Nakajima 
if(isset($lm) && $lm && isset($D_MYAREA_USE) && $D_MYAREA_USE) $wk_freeparams[] = "lm=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding($lm),'SJIS','eucJP-win'));	// add 2011/04/18 H.osamoto
$P_FREEPARAMS_SJIS = '';
if (count($wk_freeparams)) $P_FREEPARAMS_SJIS = implode("&", $wk_freeparams);
unset($wk_freeparams);
// add 2010/05/13 Y.Matsukawa ]

// ------------------------------------------------------------
//
// �����ط�
//
// ------------------------------------------------------------
//�ܺ�ɽ���ѥǡ����μ���
function ZdcSearchCgiKyotenid($kid,$type = 1,$putLog = true){
	GLOBAL $cid,$D_CID,$D_SSAPI,$D_SSAPI_KEY,$D_MOBILE_URL,$D_QRIMG_URL,$D_QRIMG_E,$D_QRIMG_V,$D_QRIMG_S,$D_KYO_COL_NAME,$D_SOCKET_TIMEOUT;
	global $P_FREEPARAMS_SJIS, $D_FREEPARAMS_TO_MBURL;		// 2010/05/13 Y.Matsukawa
	global $D_FREEPARAMS_PRINT, $P_FREEPARAMS;		// add 2011/08/15 Y.Matsukawa
	global $D_KYOTEN_LVL;	// add 2012/05/28 K.Masuda
	global $D_SHOPDATA_TRIM_WIDTH, $D_SHOPDATA_TRIM_MARKER, $D_SHOPDATA_TRIM_TYPE;		// add 2012/06/21 Y.Matsukawa
	global $D_KYOTEN_IMG_DEF;		// add 2013/07/12 T.Sasaki
	global $D_QRIMG_URL_CUST;		// add 2014/02/07 F.Yokoi
	global $D_QRIMG_URL_EX;			// add 2014/02/07 F.Yokoi

	//CGI�إ�������
	if ($putLog) {
		$cgi = $D_SSAPI["kyotenid"];
	} else {
		$cgi = $D_SSAPI["kyotenid_nolog"];
	}
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&kid=%s&type=%s",$cgi,$D_SSAPI_KEY,$D_CID,$cid,$kid,$type);
	$url .= '&mltimg=1';	// ������ʣ���˲����������ץ����	2013/07/12 T.Sasaki

	$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
	//����ͤβ��
	$cnt = count($dat);
	if($cnt < 2) return false;//���顼
	$rec = ZdcConvertEncoding($dat[1]);
	$rec = explode("\t",$rec);
	//�ͤκ���
	$tpl["kid"]  = $kid;
	$tpl["lat"]  = $rec[0];
	$tpl["lon"]  = $rec[1];
	$tpl["icon"] = $rec[2];
	// mod 2011/07/05 Y.Nakajima [
	if(isset($rec[3]) && intval($rec[3])) {
		$tpl["gifflg"]= "1";
	} else {
		$tpl["gifflg"]= "";
	}
	if(isset($rec[4]) && intval($rec[4])) {
		$tpl["new"] = "1";
	} else {
		$tpl["new"] = "";
	}
	// mod 2011/07/05 Y.Nakajima ]
	//for($i = 0;$i < 52;$i ++) {		mod 2010/03/09 Y.Matsukawa
	for($i = 0;$i < 202;$i ++) {
		// add 2011/07/05 Y.Nakajima [
		if (isset($D_KYO_COL_NAME[$type][$i])) {
		// add 2011/07/05 Y.Nakajima ]
		$col = $D_KYO_COL_NAME[$type][$i];
		// mod 2011/07/05 Y.Nakajima [
		if (isset($rec[5+$i])) {
			$d = $rec[5+$i];
		} else {
			$d = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		if ($col != '') {		// add 2009/09/04 Y.Matsukawa
			// del 2011/07/05 Y.Nakajima
			//$d = $rec[5+$i];
			$tpl[$col] = $d;
			if($d) $tpl[$col."l".$d] = "1";
			if(intval($d) == 1) $tpl[$col."b"] = "1";
			if($col == 'name') $tpl['name_enc'] = urlencode($d);		// add 2010/09/13 Y.Matsukawa
			// �ȥ�ߥ�		add 2012/06/21 Y.Matsukawa
			if (count($D_SHOPDATA_TRIM_WIDTH)) {
				foreach ($D_SHOPDATA_TRIM_WIDTH as $ii => $wid) {
					$mrk = $D_SHOPDATA_TRIM_MARKER[$ii];
					switch ($D_SHOPDATA_TRIM_TYPE[$ii]) {
						case 1:
							$tpl[$col.'_trim'.$wid] = mb_strimwidth($d, 0, $wid, $mrk);
							break;
						case 2:
							if (mb_strwidth($d) > $wid) {
								$tpl[$col.'_trim'.$wid] = mb_strimwidth($d, 0, $wid).$mrk;
							} else {
								$tpl[$col.'_trim'.$wid] = $d;
							}
							break;
					}
				}
			}
		// add 2009/09/04 Y.Matsukawa [
		} else {
			// del 2011/07/05 Y.Nakajima
			//$d = $rec[5+$i];
			if (ctype_digit($d) && 1 <= $d && $d <= 18) {
				$tpl['kyoten_lvl'] = $d;
				if($d) $tpl['kyoten_lvl'.$d] = "1";
			}
			break;
		}
		// add 2011/07/05 Y.Nakajima [
		}
		// add 2011/07/05 Y.Nakajima ]
		// add 2009/09/04 Y.Matsukawa ]
	}
	// add 2011/07/05 Y.Nakajima
	// mod 2012/05/28 K.Masuda [
	//if (!isset($tpl['kyoten_lvl'])) $tpl['kyoten_lvl'] = "";
	if($D_KYOTEN_LVL){
		if($putLog){
			// mod 2015/05/22 H.Osamoto [
			//	if(isset($rec[count($rec)-5]))$tpl['kyoten_lvl'] = $rec[count($rec)-5];
			if(isset($rec[count($rec)-6])) {
				if (preg_match('/^@@KYOTEN_LEVEL@@:/', $rec[count($rec)-6])) {
					$wk_lvl = explode(":", $rec[count($rec)-6]);
					$kyoten_lvl = $wk_lvl[1];
					if (ctype_digit($kyoten_lvl) && 1 <= $kyoten_lvl && $kyoten_lvl <= 18) {
						$tpl['kyoten_lvl'] = $kyoten_lvl;
					}
				}
			}
			// mod 2015/05/22 H.Osamoto ]
		} else {
			// mod 2015/05/22 H.Osamoto [
			//	if(isset($rec[count($rec)-1]))$tpl['kyoten_lvl'] = $rec[count($rec)-1];
			if(isset($rec[count($rec)-1])) {
				if (preg_match('/^@@KYOTEN_LEVEL@@:/', $rec[count($rec)-1])) {
					$wk_lvl = explode(":", $rec[count($rec)-1]);
					$kyoten_lvl = $wk_lvl[1];
					if (ctype_digit($kyoten_lvl) && 1 <= $kyoten_lvl && $kyoten_lvl <= 18) {
						$tpl['kyoten_lvl'] = $kyoten_lvl;
					}
				}
			}
			// mod 2015/05/22 H.Osamoto ]
		}
	} else {
		if (!isset($tpl['kyoten_lvl'])) $tpl['kyoten_lvl'] = "";
	}
	// mod 2012/05/28 K.Masuda ]

	// ������ʣ���˲���	add 2013/07/12 Add T.Sasaki
	if( isset($rec[count($rec)-5]) && $rec[count($rec)-5] != '' ) {
		$arr_mlt_img_no = explode(",", $rec[count($rec)-5]);
		if ( is_array( $arr_mlt_img_no ) && count( $arr_mlt_img_no ) ) {
			foreach ( $arr_mlt_img_no as $mlt_img_no) {
				// mlt_img_no����setting.inc�β���̾���������
				$mlt_img_name = "";
				if ( is_array( $D_KYOTEN_IMG_DEF ) ) {
					foreach( $D_KYOTEN_IMG_DEF as $item ) {
						if ( $item["IMG_NO"] == $mlt_img_no ) {
							$mlt_img_name = $item["IMG_NAME"];
							break;
						}
					}
				}
				$tpl["mltflg$mlt_img_no"] = "1";
				$tpl["mltimg$mlt_img_no"] = sprintf("%s?cid=%s&kid=%s&no=%s", $D_SSAPI["img_select"], $cid , $kid , $mlt_img_no );
				$tpl["mltnameE$mlt_img_no"] = $mlt_img_name;
			}
		}
	}


	//$tpl["iconimg"]   = sprintf("%s?cid=%s&icon_id=%s",$D_SSAPI["icon_select"],$D_CID,$tpl["icon"]);		mod 2010/07/20 Y.Matsukawa
	$tpl["iconimg"]   = sprintf("%s?cid=%s&icon_id=%s",$D_SSAPI["icon_select_g"],$D_CID,$tpl["icon"]);
	$tpl["gifimg"]    = sprintf("%s?cid=%s&kid=%s",$D_SSAPI["gif_select"],$D_CID,$kid);
	//$tpl["mobileurl"] = sprintf("%s?kid=%s",$D_MOBILE_URL,$kid);		mod 2010/07/06 Y.Matsukawa
	$tpl["mobileurl"] = sprintf("%s?kid=%s&",$D_MOBILE_URL,$kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobileurl"] .= "&".$P_FREEPARAMS_SJIS;		// add 2010/05/13 Y.Matsukawa
	$tpl["mobileurl_encode"] = urlencode($tpl["mobileurl"]);
	//$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode($tpl["mobileurl"]));		mod 2010/05/13 Y.Matsukawa

	// add 2014/02/07 F.Yokoi [
	if (isset($D_QRIMG_URL_CUST) && $D_QRIMG_URL_CUST != '') {
		if (isset($D_QRIMG_URL_EX) && $D_QRIMG_URL_EX != '') {
			$_qrimgurl = $tpl[$D_QRIMG_URL_CUST].$D_QRIMG_URL_EX;
		} else {
			$_qrimgurl = $tpl[$D_QRIMG_URL_CUST];
		}

		$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s", $D_QRIMG_URL, $D_CID, urlencode(urlencode($_qrimgurl)));
	} else {
		$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode(urlencode($tpl["mobileurl"])));
	}
	// add 2014/02/07 F.Yokoi ]

	// add 2009/06/17 Y.Matsukawa [
	$tpl["mobiledtlurl"] = sprintf("%s?ksid=%s",$D_MOBILE_URL,$kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobiledtlurl"] .= "&".$P_FREEPARAMS_SJIS;		// add 2010/05/13 Y.Matsukawa
	$tpl["mobiledtlurl_encode"] = urlencode($tpl["mobiledtlurl"]);
	//$tpl["qrimgdtlurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode($tpl["mobiledtlurl"]));		mod 2010/05/13 Y.Matsukawa
	$tpl["qrimgdtlurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode(urlencode($tpl["mobiledtlurl"])));
	// add 2009/06/17 Y.Matsukawa ]
	//$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["icon_select"],$D_CID);		mod 2010/07/20 Y.Matsukawa
	$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["icon_select_g"],$D_CID);
	$tpl["_cgiSysIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["sys_icon_select"],$D_CID);
	$tpl["_cgiGifimg"]  = sprintf("%s?cid=%s&kid=",$D_SSAPI["gif_select"],$D_CID);
	$tpl["_jsMsg"]    = sprintf("ZdcEmapShopMsg(null)",$kid);
	$tpl["_jsMove"]   = sprintf("ZdcEmapMapMove('%s','%s')",$rec[0],$rec[1]);
	$tpl["_jsScroll"] = sprintf("ZdcEmapMapScroll('%s','%s')",$rec[0],$rec[1]);
	//$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s');",$kid,$rec[0],$rec[1],$rec[2],$tpl["new"]);		mod 2009/09/04 Y.Matsukawa
	$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s','%s');",$kid,$rec[0],$rec[1],$rec[2],$tpl["new"],$tpl['kyoten_lvl']);
	$tpl["_jsFixRoute"] = sprintf("ZdcEmapFixRouteSelectShop('%s')",$kid);	// add 2011/11/25 Y.Matsukawa
	$tpl["_jsNeki"]   = sprintf("ZdcEmapStationClick('%s','%s')",$rec[0],$rec[1]);
	$tpl["_jsFreeRoute"] = sprintf("ZdcEmapFreeRouteClick('%s','%s')",$rec[0],$rec[1]);		// add 2010/06/16 Y.Matsukawa
	$tpl["_jsFreeRouteLight"] = sprintf("ZdcEmapFreeRouteClickLight('%s','%s')",$rec[0],$rec[1]);		// add 2010/09/07 Y.Matsukawa
	$tpl["_jsPrint"]  = sprintf("ZdcEmapShopPrintClick('%s')",$kid);
	$tpl["_urlPrint"] = sprintf("./print.htm?cid=%s&kid=%s",$cid,$kid);
	if($D_FREEPARAMS_PRINT) $tpl["_urlPrint"] .= "&".$P_FREEPARAMS;		// add 2011/08/15 Y.Matsukawa
	$tpl["_jsSearch"] = "ZdcEmapSearchNpoi()";
	$tpl["_jsDetailNpoi"]   = "ZdcEmapShopDetailNpoiClick()";
	
	return $tpl;
}


// ------------------------------------------------------------
//
// ʸ���������Ѵ� 
//  mb_convert_encoding�˥Х������ä����ĥ���Ƥ���
//
// ------------------------------------------------------------
function ZdcConvertEncoding($text) {
	GLOBAL $enc;

	// mod 2011/07/05 Y.Nakajima [
	// ����~���֤���������
	//if($enc) $tmp = $enc;
		//else $tmp = "EUC-JP,UTF-8,SJIS,auto";
	//return mb_convert_encoding($text,"EUC",$tmp);
	if(isset($enc) && $enc != "") $tmp = $enc;
		else $tmp = "eucJP-win,UTF-8,SJIS-win,auto";
	if ($tmp == "EUC" || $tmp == "euc" || $tmp == "EUC-JP") $tmp ="eucJP-win";
	return mb_convert_encoding($text,"eucJP-win",$tmp);
	// mod 2011/07/05 Y.Nakajima ]
}

// ------------------------------------------------------------
//
// �ü��HTML����ƥ��ƥ���ʸ�����᤹
//  htmlspecialchars_decode(PHP5)������
//  �������Ȥˤ����б�
//
// ------------------------------------------------------------
function zdc_htmlspecialchars_decode($text) {
	$ret = $text;
	$ret = str_replace("&amp;", "&", $ret);
	$ret = str_replace("&lt;",  "<", $ret);
	$ret = str_replace("&gt;",  ">", $ret);
	return $ret;
}

// ------------------------------------------------------------
//
// JavaScript�Υ�ƥ�����ѥ��������׽���
//
// ------------------------------------------------------------
function zdc_js_encode($text) {
	$ret = $text;
	$ret = str_replace("\\", "\\\\", $ret);
	$ret = str_replace("'",  "\\'",  $ret);
	$ret = str_replace('"',  '\\"',  $ret);
	return $ret;
}

// ------------------------------------------------------------
//
// ����ե꡼��ɸ�����̥����ȴؿ�
//
//
// ------------------------------------------------------------
function GEOAccess_cmp_sflg($a,$b){
	// full��� 1:�������פ�ͥ��
	if( $a["full"] > $b["full"] ) return -1;
	if( $a["full"] < $b["full"] ) return 1;

	// adidʸ����Ĺ���
	// adid�ˤ�AB����16����椬���Ѥ���Ƥ���ΤǤޤ�ʸ����Ĺ����Ӥ�Ԥ�
	if( strlen($a["adid"]) > strlen($b["adid"]) )		return 1;
	if( strlen($a["adid"]) < strlen($b["adid"]) )		return -1;

	// adid�������
	// adid��ʸ����Ȥ��ư�����Ӥ򤹤�� strcmp ����Ѥ������
	// ��ӷ�̤Ϥ��Τޤ�return
	return strcmp( $a['adid'], $b['adid'] );
}

// ------------------------------------------------------------
//
// �����ط�
// ��������
//  1.����
//    script cid opt refferer status service
//  2.emapview
//    kid lat lon type keyword adcd area col nm no cond
//  3.search
//    page jnrmn jnr jkn 
//
// ------------------------------------------------------------
function ZdcLogPut($status) {
	GLOBAL $_VARS,$LOG_MODE;
	//include_once("/home/emap/httpd/log/inc/com_log_open.inc");		mod 2010/04/19 Y.Matsukawa
	include_once("/home/emap/src/log/inc/com_log_open.inc");
	// add 2011/07/05 Y.Nakajima
	if (!isset($cond)) $cond = "";
	
	//�ʹ��߾��βù�
	//for($i = 0;$i < 50;$i ++) {		mod 2009/11/07 Y.Matsukawa
	for($i = 1;$i <= 200;$i ++) {
		// mod 2011/07/05 Y.Nakajima
		if(isset($_VARS["cond".$i]) && $_VARS["cond".$i]) {
			// mod 2011/07/05 Y.Nakajima
			if($cond != "") $cond .= ",";
			$cond .= sprintf("cond%d=%s",$i,$_VARS["cond".$i]);
		}
	}
	//128�Х��Ȥ˴ݤ��
	//$cond = mb_strimwidth($cond, 0, 256, '...');		// add 2009/09/08 Y.Matsukawa	mod 2009/09/14 Y.Matsukawa
	$cond = mb_strimwidth($cond, 0, 128, '...');
	$cond = mb_ereg_replace(' ','_',$cond);			// add 2010/10/01 Y.Matsukawa
	//��������
	//$prm  = sprintf("%s %s %s %s %s ",$status,$_VARS["kid"],$_VARS["lat"],$_VARS["lon"],$_VARS["zpoint"]);	mod 2010/10/01 Y.Matsukawa
	// add 2011/07/05 Y.Nakajima [
	if (!isset($_VARS["kid"]))     $_VARS["kid"] = "";
	if (!isset($_VARS["lat"]))     $_VARS["lat"] = "";
	if (!isset($_VARS["lon"]))     $_VARS["lon"] = "";
	if (!isset($_VARS["zpoint"]))  $_VARS["zpoint"] = "";
	if (!isset($_VARS["type"]))    $_VARS["type"] = "";
	if (!isset($_VARS["keyword"])) $_VARS["keyword"] = "";
	if (!isset($_VARS["adcd"]))    $_VARS["adcd"] = "";
	if (!isset($_VARS["area"]))    $_VARS["area"] = "";
	if (!isset($_VARS["col"]))     $_VARS["col"] = "";
	if (!isset($_VARS["nm"]))      $_VARS["nm"] = "";
	if (!isset($_VARS["icn"]))     $_VARS["icn"] = "";
	if (!isset($_VARS["page"]))    $_VARS["page"] = "";
	if (!isset($_VARS["slogflg"])) $_VARS["slogflg"] = "";
	// add 2011/07/05 Y.Nakajima ]
	$prm  = sprintf("%s %s %s %s %s "
					,$status
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["kid"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["lat"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["lon"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["zpoint"]), 0, 128, '...')
	);
	// del 2010/01/18 Y.Matsukawa [
	//	$prm .= sprintf("%s %s %s %s %s ",$_VARS["type"],$_VARS["keyword"],$_VARS["adcd"],$_VARS["area"],$_VARS["col"]);
	//	//$prm .= sprintf("%s %s %s %s %s ",$_VARS["nm"],$_VARS["icn"],$cond,$_VARS["page"],"");
	//	$prm .= sprintf("%s %s %s %s %s ",$_VARS["nm"],$_VARS["icn"],$cond,$_VARS["page"],$_VARS["slogflg"]);
	// del 2010/01/18 Y.Matsukawa ]
	// del 2010/10/01 Y.Matsukawa [
	//	// add 2010/01/18 Y.Matsukawa ]
	//	$prm .= sprintf("%s %s %s %s %s "
	//					,$_VARS["type"]
	//					//,mb_ereg_replace(' ','_',$_VARS["keyword"])		mod 2010/02/10 Y.Matsukawa
	//					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["keyword"]), 0, 128, '...')
	//					,$_VARS["adcd"]
	//					,$_VARS["area"]
	//					,$_VARS["col"]
	//	);
	//	$prm .= sprintf("%s %s %s %s %s "
	//					//,mb_ereg_replace(' ','_',$_VARS["nm"])		mod 2010/02/10 Y.Matsukawa
	//					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["nm"]), 0, 128, '...')
	//					,$_VARS["icn"]
	//					,$cond
	//					,$_VARS["page"]
	//					,$_VARS["slogflg"]
	//	);
	//	// add 2010/01/18 Y.Matsukawa ]
	// del 2010/10/01 Y.Matsukawa ]
	// add 2010/10/01 Y.Matsukawa [
	$prm .= sprintf("%s %s %s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["type"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["keyword"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["adcd"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["area"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["col"]), 0, 128, '...')
	);
	$prm .= sprintf("%s %s %s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["nm"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["icn"]), 0, 128, '...')
					,$cond
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["page"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["slogflg"]), 0, 128, '...')
	);
	// add 2010/10/01 Y.Matsukawa ]
	$prm = str_replace("\n","",$prm);
	$prm = str_replace("\r","",$prm);
	
	// ��������
	// mod 2011/07/05 Y.Nakajima [
	if (isset($log_pc)) {
		$log_pc->info($prm);
	}
	// mod 2011/07/05 Y.Nakajima ]

	//include_once("/home/emap/httpd/log/inc/com_log_close.inc");		mod 2010/04/19 Y.Matsukawa
	include_once("/home/emap/src/log/inc/com_log_close.inc");
}

// add 2009/08/24 Y.Matsukawa
// ------------------------------------------------------------
// IP�����å�
// ------------------------------------------------------------
function ip_check() {
	global $D_ALLOW_IP;
	global $D_DEFAULT_ALLOW_IP;
	
	if ($D_ALLOW_IP == '') return true;
	
	$REMOTE_ADDR = $_SERVER['REMOTE_ADDR'];
	
	$ip_list = array_merge(explode(';', $D_ALLOW_IP), $D_DEFAULT_ALLOW_IP);

	foreach ($ip_list as $i=>$ip) {
		// IP���ɥ쥹�����xxx.xxx.xxx.xxx��
		if (preg_match("/^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$/", $ip)) {
			if (strcmp($REMOTE_ADDR, $ip) == 0) return true;
		// IP���ɥ쥹�����֥ͥåȥޥ��������xxx.xxx.xxx.xxx/xx��
		} else if (preg_match("/^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\/([0-9]{1,2})$/", $ip)) {
			// mod 2011/07/05 Y.Nakajima
			//$res = split('[/.]', $ip);
			//$res = explode('[/.]', $ip);		mod 2012/07/06 Y.Matsukawa
			$res = preg_split("/[\/.]/", $ip);
//error_log(date("Y/m/d H:i:s")." ALLOW_IP preg_split(/[./]/)=\n".print_r($res,true)."\n", 3, "/var/tmp/pc_debug_".date("Ymd").".log");
			$w_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			$mask = intval($res[4]);
			$shift = 32 - $mask;
			// mod 2011/07/05 Y.Nakajima
			//$res = split('[/.]', $REMOTE_ADDR);
			//$res = explode('[/.]', $REMOTE_ADDR);		mod 2012/07/06 Y.Matsukawa
			$res = explode(".", $REMOTE_ADDR);
//error_log(date("Y/m/d H:i:s")." REMOTE_ADDR explode(.)=\n".print_r($res,true)."\n", 3, "/var/tmp/pc_debug_".date("Ymd").".log");
			$r_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			if (($w_ip >> $shift) == ($r_ip >> $shift)) return true;
		}
	}

	return false;
}
// add 2011/04/18 H.Osamoto
// ------------------------------------------------------------
// �����¸ʸ�������å�
// (EUC-JP������ࡢ������Τߵ���)
// ------------------------------------------------------------
function IzonSearch( $str ) {

	// ���Х���ʸ����JIS X 212 ��������ˤ��ޤޤ�Ƥ����饨�顼
	// ��������������Τޤ���������Ƥ������ϡ������ǥեå�����ޤ�
	// ��IE�ʳ��Υ֥饦������������䡢CSV�ե����륢�åץ���������
	if (preg_match('/(\x8F[\xA1-\xFE][\xA1-\xFE])/', $str)) {
		return false;
	}

	// �ѡ�����ȥ��󥳡��ɤ��줿���Х���ʸ����JIS X 212 ��������ˤ��ޤޤ�Ƥ����饨�顼
	// ��IE�ʤɤ��顢������������󥳡��ɤ������������Ƥ������ϡ������ǥեå�����ޤ�
	// ����ˡ�&#28583;�ס�&AElig;��
	if (preg_match('/(&#[0-9]{1,};|&[a-zA-Z]{1,};)/', $str)) {
		return false;
	}

	// Ⱦ�ѥ��ʤ����ѥ��ʤ��Ѵ���Ⱦ�ѥ��ʤ����ߤ��Ƥ���ȡ�����ʸ��ȴ���Ф��˼��Ԥ��뤿��� 2007/08/13 add Y.Matsukawa
	$w_str = mb_convert_kana($str, 'K');

	// ����ʸ����ȴ���Ф�
	preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $w_str, $matchword );

	for ( $i=0; $i < count( $matchword[0] ) ; $i++) {
		if ( $matchword[0][$i] ) {
			// EUC-JP  ����ࡢ�������ʸ�������å�
			if ( ! preg_match( '/^(([\xA1-\xA8]|[\xB0-\xF4])[\xA1-\xFE])*$/', $matchword[0][$i]) ) {
				return false;
			}
		}
	}
	return true;
}

// add 2011/10/28 K.Masuda
// ------------------------------------------------------------
// Cookie�ɤ߹���
// ------------------------------------------------------------
function CookieRead( $id, &$carr){
	if ($_COOKIE[$id] != '') {
		$cookiedtl = explode(',', $_COOKIE[$id]);
		$cnt = floor(count($cookiedtl)/2);
		for ($i = 0; $i < $cnt; $i++) {
			$cookie_dt[] = array('cdt1'=>$cookiedtl[$i*2], 'cdt2'=>urldecode($cookiedtl[$i*2+1]));
		}
	}
	$carr = $cookie_dt;
	return true;
}

// add 2012/03/19 SKC [
// ------------------------------------------------------------
// UA���饭��ꥢȽ��
// ------------------------------------------------------------
function getCarrierAgent($P_USER_AGENT){
	// �����Ǥ�Android��iPhone�Ͻ�������Ƥ���(PC�����Ӥ���Ƚ��)
	// ����ꥢȽ��
	if( strpos($P_USER_AGENT, D_DOCOMO   ) !== false ){ return D_DOCOMO;   }
	if( strpos($P_USER_AGENT, D_SOFTBANK ) !== false ){ return D_SOFTBANK; }
	if( strpos($P_USER_AGENT, D_SOFTBANK2) !== false ){ return D_SOFTBANK; }
	if( strpos($P_USER_AGENT, D_KDDI     ) !== false ){ return D_KDDI;     }
	if( strpos($P_USER_AGENT, D_HDML     ) !== false ){ return D_HDML;     }
	if( strpos($P_USER_AGENT, D_REG_WILL ) !== false ){ return D_WILL;     }
	if( strpos($P_USER_AGENT, D_WILL     ) !== false ){ return D_WILL;     }
	return D_PC;
}
// add 2012/03/19 SKC ]

// add 2012/06/19 Y.Matsukawa
// ------------------------------------------------------------
// ��¸Ź�ޤ�Cookie�ɤ߹���
// ���꤬�������Ź�޾����CGI�������
// ------------------------------------------------------------
function getShopDtlFromCookie($cgidata = false) {
	global $D_SSAPI, $D_CID, $D_SSAPI_KEY, $D_SOCKET_TIMEOUT, $D_KYO_COL_NAME;
	global $D_COOKIE_SHOPDTL_MAX, $D_COOKIE_SHOPDTL_KEY;
	global $D_SHOPDATA_TRIM_WIDTH, $D_SHOPDATA_TRIM_MARKER, $D_SHOPDATA_TRIM_TYPE;		// add 2012/06/21 Y.Matsukawa
	$shop_dtl = array();
	$shop_id = array();
	if ($D_COOKIE_SHOPDTL_MAX > 0) {
		if (isset($_COOKIE[$D_COOKIE_SHOPDTL_KEY]) && $_COOKIE[$D_COOKIE_SHOPDTL_KEY] != '') {
			// Cookie��¸���������
			$ckval = explode(',', $_COOKIE[$D_COOKIE_SHOPDTL_KEY]);
			$cnt = floor(count($ckval)/2);
			$cnt = ($cnt<=$D_COOKIE_SHOPDTL_MAX ? $cnt : $D_COOKIE_SHOPDTL_MAX);
			for ($i = 0; $i < $cnt; $i++) {
				$shop_dtl_no[$ckval[$i*2]] = $i;
				$shop_dtl[$i] = array('kyoten_id'=>$ckval[$i*2], 'name'=>urldecode($ckval[$i*2+1]));
				$shop_id[] = $ckval[$i*2];
			}
			// CGI����ǡ�������
			if (count($shop_id) && $cgidata) {
				$cgi = $D_SSAPI['kyotenlist'];
				$prm = sprintf('&cid=%s&pos=%d&cnt=%d', $D_CID, 1, $D_COOKIE_SHOPDTL_MAX);
				$prm .= sprintf('&kid=%s', urlencode(implode(',', $shop_id)));
				$url = sprintf('%s?key=%s&opt=%s%s', $cgi, $D_SSAPI_KEY, $D_CID, $prm);
				$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
				$status  = explode("\t", $dat[0]);
				if(!isset($status[2]) || !intval($status[2])) {
					return $shop_dtl;
				}
				$datacnt = intval($status[1]);
				for($i = 0; $i < $datacnt; $i++) {
					$rec = explode("\t", $dat[$i + 1]);
					$kid = $rec[0];
					if (isset($shop_dtl_no[$kid])) {
						$shop_dtl[$shop_dtl_no[$kid]]['kid'] = $kid;
						if (isset($D_KYO_COL_NAME[0])) {
							foreach ($D_KYO_COL_NAME[0] as $j => $colnm) {
								if ($colnm != '') {
									if (isset($rec[5+$j])) {
										$d = $rec[5+$j];
									} else {
										$d = '';
									}
									$shop_dtl[$shop_dtl_no[$kid]][$colnm] = $d;
									// �ȥ�ߥ�		add 2012/06/21 Y.Matsukawa
									if (count($D_SHOPDATA_TRIM_WIDTH)) {
										foreach ($D_SHOPDATA_TRIM_WIDTH as $ii => $wid) {
											$mrk = $D_SHOPDATA_TRIM_MARKER[$ii];
											switch ($D_SHOPDATA_TRIM_TYPE[$ii]) {
												case 1:
													$shop_dtl[$shop_dtl_no[$kid]][$colnm.'_trim'.$wid] = mb_strimwidth($d, 0, $wid, $mrk);
													break;
												case 2:
													if (mb_strwidth($d) > $wid) {
														$shop_dtl[$shop_dtl_no[$kid]][$colnm.'_trim'.$wid] = mb_strimwidth($d, 0, $wid).$mrk;
													} else {
														$shop_dtl[$shop_dtl_no[$kid]][$colnm.'_trim'.$wid] = $d;
													}
													break;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return $shop_dtl;
}

// add 2012/08/03 H.Osamoto
// ------------------------------------------------------------
// HTMLɽ�����Ѵ�����
// ------------------------------------------------------------
function zdcHtmlspecialchars_arr($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/^name$|^addr$/', $key)) {
			$obj[$key] = zdcHtmlspecialchars_nameaddr($val);
		} else if (preg_match('/^col_[0-9][0-9]+$/', $key)) {
			$obj[$key] = zdcHtmlspecialchars_col($val);
		} else {
			$obj[$key] = $val;
		}
	}
	
	return $obj;
}

function zdcHtmlspecialchars($target, $col_name) {
	
	if (preg_match('/^name$|^addr$/', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr($target);
	} else if (preg_match('/^col_[0-9][0-9]+$/', $col_name)) {
		$ret = zdcHtmlspecialchars_col($target);
	} else {
		$ret = $target;
	}
	
	return $ret;
}

function zdcHtmlspecialchars_nameaddr($target) {
	
	$ret = htmlreplace($target);
	
	return $ret;
}

function zdcHtmlspecialchars_col($target) {
	
	$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// ���ĥ����ꥹ��
	$arr_rep = array();
	$rep_cnt = 0;
	
	$target;
	
	foreach ($tag_list as $key => $tag) {
		$start = 0;
		$stop = 0;
		while(1) {
			if (strpos($target, '<', $start) === false) break;	// ��<�פ�¸�ߤ��ʤ����Ͻ������ʤ�
			
			// ���ĥ��������å�
			$start = strpos(strtolower($target), strtolower($tag), $start);
			
			if ($start !== false) {
				// ���ĥ�����¸�ߤ�����
				$stop = strpos(strtolower($target), ">", $start);
				$rep_cnt++;
				
				// �ִ��оݤ���Ū������˳�Ǽ
				$arr_rep[$rep_cnt] = substr($target, $start, $stop - $start + 1);
				
				// �Ѵ����ʤ����ĥ�������Ū���ִ�
				$target = substr($target, 0, $start) . "@REP" . $rep_cnt . "@" . substr($target, $stop + 1);
				
				// 2013/02/07 H.osamoto mod [
				//	// ���ϰ��֤򤺤餷��³����¹�
				//	$start = $stop;
				// ���٥ꥻ�åȤ��ƺƼ¹�
				$start = 0;
				// 2013/02/07 H.osamoto mod ]
			} else {
				// ���ĥ�����¸�ߤ��ʤ����
				// ���Υ��������å�
				break;
			}
		}
	}
	
	$target = htmlreplace($target);
	
	// �Ѵ����Ƥ��������ĥ����򸵤��᤹
	for ($i = 1; $i <= $rep_cnt; $i++) {
		$target = str_replace("@REP".$i."@", $arr_rep[$i], $target);
	}
	
	return $target;
}

function htmlreplace($target) {
	// HTMLɽ���Ѥ��ִ�
	$search  = array('&', '"', '\'', '\\', '<', '>');	// �ִ��о�
	$replace = array('&amp;', '&quot;', '&#039;', '&yen;', '&lt;', '&gt;');	// �ִ���ʸ����
	
	$target = str_replace($search, $replace, $target);
	
	return $target;
}

?>