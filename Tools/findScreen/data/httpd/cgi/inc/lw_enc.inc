<?php
/***************************************************************************
// ��������
// 2010/12/10 Y.Matsukawa	��������
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
/***************************************************************************/
mb_language('Japanese');

// SJIS
if ($ENC == "SJIS") {
//	mb_http_output("SJIS");
	$RETCD = "\r\n";		// CRLF
	$RETCD_ESC = "\\r\\n";	// CRLF
// UTF8
} else if ($ENC == "UTF8") {
//	mb_http_output("UTF-8");
	$RETCD = "\n";			// LF
	$RETCD_ESC = "\\n";		// LF
// EUC
} else if ($ENC == "EUC") {
//	mb_http_output("EUC-JP");
	$RETCD = "\n";			// LF
	$RETCD_ESC = "\\n";		// LF
// ����¾���������͡�
} else {
	$ENC = "UTF8";
//	mb_http_output("UTF-8");
	$RETCD = "\n";			// LF
	$RETCD_ESC = "\\n";		// LF
}

/**
 * �ؿ�̾  ��  f_enc_to_EUC
 * ��  ��  ��  ʸ�����EUC-JP���Ѵ�����
 * ��  ��  ��  $str - �Ѵ�����ʸ����
 * �����  ��  EUC-JP���Ѵ����줿ʸ����
 **/
function f_enc_to_EUC($str) {
	global $ENC;
	// SJIS
	if ($ENC == "SJIS") {
		// ��SJIS�Υ���ʸ���ʡ�ɽ�סֽ��ס֥������ˤ��Ѵ�����ȡ�����ˡ�\�פ��դ��Ƥ��ޤ��Τǡ�����Ƥޤ�
		//return mb_ereg_replace("\\", "", mb_convert_encoding($str, "EUC-JP", "SJIS"));
		return mb_convert_encoding($str, "EUC-JP", "SJIS");
	// UTF8
	} else if ($ENC == "UTF8") {
		return mb_convert_encoding($str, "EUC-JP", "UTF-8");
	// EUC
	} else if ($ENC == "EUC") {
		return $str;
	// ����¾���̾�Ϥ��ꤨ�ʤ���
	} else {
		return $str;
	}
}

/**
 * �ؿ�̾  ��  f_enc_convert
 * ��  ��  ��  ʸ�������ꤵ�줿���󥳡��ɤ��Ѵ�����
 * ��  ��  ��  $str - �Ѵ�����ʸ����
 * �����  ��  �Ѵ����줿ʸ����
 **/
function f_enc_convert($str) {
	global $ENC;
	// mod 2011/09/29 Y.Nakajima [
	//ʸ���ǡ������Ѵ�
	// ����~���֤����������б�
	// SJIS
	if ($ENC == "SJIS") {
		//return mb_convert_encoding($str, "SJIS", "EUC-JP");
		return mb_convert_encoding($str, "SJIS", "eucJP-win");
	// UTF8
	} else if ($ENC == "UTF8") {
		//return mb_convert_encoding($str, "UTF-8", "EUC-JP");
		return mb_convert_encoding($str, "UTF-8", "eucJP-win");
	// EUC
	} else if ($ENC == "EUC") {
		//return $str;
		return mb_convert_encoding($str, "EUC-JP", "eucJP-win");
	// mod 2011/09/29 Y.Nakajima ]
	// ����¾���̾�Ϥ��ꤨ�ʤ���
	} else {
		return $str;
	}
}
?>