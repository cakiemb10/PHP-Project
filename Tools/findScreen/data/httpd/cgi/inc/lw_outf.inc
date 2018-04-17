<?php
/**********************************************************************
// 更新履歴：
// 2010/12/10 Y.Matsukawa	新規作成
/*********************************************************************/
//-----------------------------------------------------------
// 出力クラス
//-----------------------------------------------------------
class KyotenCgiOutput {
	var $CgiCd = '';
	var $CgiNm = '';
	var $Enc = '';
	var $EncStr = '';
	var $LineSep = '';
	var $LineSepEsc = '';
	var $Outf = '';
	var $Pflg = '';
	var $RetCode = null;
	var $RecCount = null;
	var $HitCount = null;
	var $ResultSet = array();
	//-------------------------------------------
	// コンストラクタ
	//-------------------------------------------
	function KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf) {
		$this->CgiCd = $cgicd;
		$this->CgiNm = $cginm;
		$this->Outf = $outf;
		$this->LineSep = $retcd;
		$this->LineSepEsc = $retcd_e;
		$this->Pflg = $pflg;
		switch ($enc) {
			case 'SJIS':
				$this->Enc = 'SJIS';
				$this->EncStr = 'Shift_JIS';
				break;
			case 'EUC':
				$this->Enc = 'EUC-JP';
				$this->EncStr = 'EUC-JP';
				break;
			default:
				$this->Enc = 'UTF-8';
				$this->EncStr = 'UTF-8';
		}
	}
	//-------------------------------------------
	// set_status
	// statusセット
	//-------------------------------------------
	function set_status($retCode, $recCount=null, $hitCount=null) {
		$this->RetCode = substr(trim($retCode), -5);
		$this->RecCount = $recCount;
		$this->HitCount = $hitCount;
	}
	//-------------------------------------------
	// set_data
	// 出力データ値セット
	//-------------------------------------------
	function set_data($recordNo, $itemName, $value) {
		if (!$this->ResultSet[$recordNo]) {
			$this->ResultSet[$recordNo] = array();
		}
		$this->ResultSet[$recordNo][$itemName] = $value;
	}
	//-------------------------------------------
	// set_data
	// 出力データ値配列セット
	//-------------------------------------------
	function set_data_arr(&$arrData) {
		$this->ResultSet = &$arrData;
	}
	//-------------------------------------------
	// output_header
	// レスポンスヘッダ出力
	//-------------------------------------------
	function output_header() {
		switch ($this->Outf) {
			case 'XML':
				Header('Content-type: text/xml; charset='.$this->EncStr);
				break;
			default:
				Header('Content-type: application/json; charset='.$this->EncStr);
		}
	}
	//-------------------------------------------
	// output_body_start
	// レスポンスボディ出力開始
	//-------------------------------------------
	function output_body_start() {
		switch ($this->Outf) {
			case 'XML':
				echo '<?xml version="1.0" encoding="'.$this->EncStr.'" ?>'.$this->LineSep;
				echo '<'.$this->CgiNm.'>'.$this->LineSep;
				break;
			default:
				echo '{';
		}
	}
	//-------------------------------------------
	// output_status
	// ステータス出力
	//-------------------------------------------
	function output_status() {
		switch ($this->Outf) {
			case 'XML':
				echo '<status>'.$this->LineSep;
				echo '<returnCode>'.$this->CgiCd.$this->RetCode.'</returnCode>'.$this->LineSep;
				echo '<recCount>'.$this->RecCount.'</recCount>'.$this->LineSep;
				echo '<hitCount>'.$this->HitCount.'</hitCount>'.$this->LineSep;
				echo '</status>'.$this->LineSep;
				break;
			default:
				echo '"returnCode":"'.$this->CgiCd.$this->RetCode.'"';
				echo ',';
				echo '"recCount":"'.$this->RecCount.'"';
				echo ',';
				echo '"hitCount":"'.$this->HitCount.'"';
		}
	}
	//-------------------------------------------
	// output_body_end
	// レスポンスボディ出力終了
	//-------------------------------------------
	function output_body_end() {
		switch ($this->Outf) {
			case 'XML':
				echo '</'.$this->CgiNm.'>'.$this->LineSep;
				break;
			default:
				echo '}';
		}
	}

	//-------------------------------------------
	// escapeJSON
	// JSON出力文字列のエスケープ処理
	//-------------------------------------------
	function escapeJSON($str) {
		$ret = $str;
		$ret = mb_ereg_replace("\"", "\\\"", $ret);		// 「"」 → 「\"」
		return $ret;
	}

	//-------------------------------------------
	// escapeXML
	// XML出力文字列のエスケープ処理
	//-------------------------------------------
	function escapeXML($str) {
		$ret = $str;
		$ret = htmlspecialchars($ret);
		return $ret;
	}
}

?>
