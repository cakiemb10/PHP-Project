<?php
/*========================================================*/
// 更新履歴：
// 2013/02/20 Y.Matsukawa	新規作成
/*========================================================*/
//-----------------------------------------------------------
// 出力クラス
//-----------------------------------------------------------
class RdCgiOutput {
	var $CgiCd = '';
	var $CgiNm = '';
	var $Enc = '';
	var $EncStr = '';
	var $Outf = '';
	var $RetCode = null;
	
	//-------------------------------------------
	// コンストラクタ
	//-------------------------------------------
	function RdCgiOutput($cgicd, $cginm, $enc, $outf) {
		$this->CgiCd = $cgicd;
		$this->CgiNm = $cginm;
		$this->Outf = $outf;
		switch ($enc) {
			case 'SJIS':
				$this->Enc = 'SJIS';
				$this->EncStr = 'Shift_JIS';
				break;
			case 'EUC':
				$this->Enc = 'EUC-JP';
				$this->EncStr = 'EUC-JP';
				break;
			case 'UTF8':
				$this->Enc = 'UTF-8';
				$this->EncStr = 'UTF-8';
				break;
			default:
				$this->Enc = '';
				$this->EncStr = '';
		}
	}
	//-------------------------------------------
	// set_status
	// statusセット
	//-------------------------------------------
	function set_status($retCode) {
		$this->RetCode = substr(trim($retCode), -5);
	}
	
	//-------------------------------------------
	// 配列開始タグ
	//-------------------------------------------
	function output_list_start($name) {
		switch ($this->Outf) {
			case 'XML':
				echo '<'.$name.'>';
				break;
			case 'JSON':
				echo '"'.$name.'":';
				echo '[';
				break;
		}
	}
	//-------------------------------------------
	// 配列終了タグ
	//-------------------------------------------
	function output_list_end($name) {
		switch ($this->Outf) {
			case 'XML':
				echo '</'.$name.'>';
				break;
			case 'JSON':
				echo ']';
				break;
		}
	}

	//-------------------------------------------
	// 連想配列開始タグ
	//-------------------------------------------
	function output_hash_start($name, $id='') {
		switch ($this->Outf) {
			case 'XML':
				echo '<'.$name.($id!=''?' id="'.$id.'"':'').'>';
				break;
			case 'JSON':
				//echo '"'.$name.'":';
				echo '{';
				break;
		}
	}
	//-------------------------------------------
	// 連想配列終了タグ
	//-------------------------------------------
	function output_hash_end($name) {
		switch ($this->Outf) {
			case 'XML':
				echo '</'.$name.'>';
				break;
			case 'JSON':
				echo '}';
				break;
		}
	}
	
	//-------------------------------------------
	// 連想配列要素
	//-------------------------------------------
	function output_hash_item($name, $value) {
		switch ($this->Outf) {
			case 'XML':
				echo '<'.$name.'>'.f_enc_convert($this->escapeXML($value)).'</'.$name.'>';
				break;
			case 'JSON':
				echo '"'.$name.'":"'.f_enc_convert($this->escapeJSON($value)).'"';
				break;
		}
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
			case 'JSON':
				Header('Content-type: application/json; charset='.$this->EncStr);
				break;
		}
	}
	//-------------------------------------------
	// output_body_start
	// レスポンスボディ出力開始
	//-------------------------------------------
	function output_body_start() {
		switch ($this->Outf) {
			case 'XML':
				echo '<?xml version="1.0" encoding="'.$this->EncStr.'" ?>';
				echo '<'.$this->CgiNm.'>';
				break;
			case 'JSON':
				echo '{';
				break;
		}
	}
	//-------------------------------------------
	// output_status
	// ステータス出力
	//-------------------------------------------
	function output_status() {
		switch ($this->Outf) {
			case 'XML':
				echo '<status>';
				echo '<return_code>'.$this->CgiCd.$this->RetCode.'</return_code>';
				echo '</status>';
				break;
			case 'JSON':
				echo '"return_code":"'.$this->CgiCd.$this->RetCode.'"';
				break;
		}
	}
	//-------------------------------------------
	// output_body_end
	// レスポンスボディ出力終了
	//-------------------------------------------
	function output_body_end() {
		switch ($this->Outf) {
			case 'XML':
				echo '</'.$this->CgiNm.'>';
				break;
			case 'JSON':
				echo '}';
				break;
		}
	}

	//-------------------------------------------
	// output_sep
	// セパレーター出力
	//-------------------------------------------
	function output_sep() {
		switch ($this->Outf) {
			case 'XML':
				break;
			case 'JSON':
				echo ',';
				break;
		}
	}

	//-------------------------------------------
	// escapeJSON
	// JSON出力文字列のエスケープ処理
	//-------------------------------------------
	function escapeJSON($str) {
		$ret = $str;
		$ret = mb_ereg_replace("\"", "\\\"", $ret);
		$ret = mb_ereg_replace("\r\n", "\\n", $ret);
		$ret = mb_ereg_replace("\n", "\\n", $ret);
		$ret = mb_ereg_replace("\r", "\\n", $ret);
		return $ret;
	}

	//-------------------------------------------
	// escapeXML
	// XML出力文字列のエスケープ処理
	//-------------------------------------------
	function escapeXML($str) {
		$ret = $str;
		$ret = htmlspecialchars($ret);
		$ret = mb_ereg_replace("\r\n", "\\n", $ret);
		$ret = mb_ereg_replace("\n", "\\n", $ret);
		$ret = mb_ereg_replace("\r", "\\n", $ret);
		return $ret;
	}
}

?>
