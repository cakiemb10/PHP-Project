<?php
/*========================================================*/
// ��������
// 2013/02/20 Y.Matsukawa	��������
/*========================================================*/
//-----------------------------------------------------------
// ���ϥ��饹
//-----------------------------------------------------------
class RdCgiOutput {
	var $CgiCd = '';
	var $CgiNm = '';
	var $Enc = '';
	var $EncStr = '';
	var $Outf = '';
	var $RetCode = null;
	
	//-------------------------------------------
	// ���󥹥ȥ饯��
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
	// status���å�
	//-------------------------------------------
	function set_status($retCode) {
		$this->RetCode = substr(trim($retCode), -5);
	}
	
	//-------------------------------------------
	// ���󳫻ϥ���
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
	// ����λ����
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
	// Ϣ�����󳫻ϥ���
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
	// Ϣ������λ����
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
	// Ϣ����������
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
	// �쥹�ݥ󥹥إå�����
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
	// �쥹�ݥ󥹥ܥǥ����ϳ���
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
	// ���ơ���������
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
	// �쥹�ݥ󥹥ܥǥ����Ͻ�λ
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
	// ���ѥ졼��������
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
	// JSON����ʸ����Υ��������׽���
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
	// XML����ʸ����Υ��������׽���
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