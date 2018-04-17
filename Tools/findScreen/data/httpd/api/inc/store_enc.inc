<?php
	/***************************************************************************
	// 更新履歴：
	// 2011/11/10 H.Nakamura	新規作成
	/***************************************************************************/
	mb_language('Japanese');
/*
	// SJIS
	if ($ENC == "SJIS") {
	
		$RETCD = "\r\n";		// CRLF
		$RETCD_ESC = "\\r\\n";	// CRLF
	// UTF8
	} else if ($ENC == "UTF8") {
	
		$RETCD = "\n";			// LF
		$RETCD_ESC = "\\n";		// LF
	// EUC
	} else if ($ENC == "EUC") {

		$RETCD = "\n";			// LF
		$RETCD_ESC = "\\n";		// LF
	// その他（不正な値）
	} else {
		$ENC = "UTF8";

		$RETCD = "\n";			// LF
		$RETCD_ESC = "\\n";		// LF
	}
*/
	/**
	 * 関数名  ：  f_enc_to_EUC
	 * 概  要  ：  文字列をEUC-JPへ変換する
	 * 引  数  ：  $str - 変換する文字列
	 * 戻り値  ：  EUC-JPに変換された文字列
	 **/
	function f_enc_to_EUC($str) {
		global $ENC;
		// SJIS
		if ($ENC == "SJIS") {
			// ※SJISのダメ文字（「表」「十」「ソ」等）を変換すると、後ろに「\」が付いてしまうので、除去してます
			//return mb_ereg_replace("\\", "", mb_convert_encoding($str, "EUC-JP", "SJIS"));
			return mb_convert_encoding($str, "EUC-JP", "SJIS");
		// UTF8
		} else if ($ENC == "UTF8") {
			return mb_convert_encoding($str, "EUC-JP", "UTF-8");
		// EUC
		} else if ($ENC == "EUC") {
			return $str;
		// その他（通常はありえない）
		} else {
			return $str;
		}
	}

	/**
	 * 関数名  ：  f_enc_convert
	 * 概  要  ：  文字列を指定されたエンコードへ変換する
	 * 引  数  ：  $str - 変換する文字列
	 * 戻り値  ：  変換された文字列
	 **/
	function f_enc_convert($str) {
		global $ENC;

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
		// その他（通常はありえない）
		} else {
			return $str;
		}
	}


	/**
	 * 関数名  ：  f_dec_convert
	 * 概  要  ：  文字列をeucJP-winにデコードする
	 * 引  数  ：  $str - 変換する文字列
	 * 戻り値  ：  変換された文字列
	 **/
	function f_dec_convert($str) {
		global $ENC;
		return mb_convert_encoding($str, "eucJP-win", $ENC);
	}
?>
