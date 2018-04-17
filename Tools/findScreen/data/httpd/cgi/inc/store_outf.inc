<?php
/**********************************************************************
// ��������
// 2011/11/01 H.Nakamura	��������
// 2013/03/11 Y.Matsukawa	�ꥢ�륿����ǡ���
// 2016/04/28 T.Yoshino		���Ϲ��ܤ��ɲ�(yamato)
// 2016/07/19 T.Yoshino		���Ϲ��ܤ��ɲ�(711OMNI��CGI)
// 2016/10/19 Y.Matsukawa	��ޥȱ�͢����ŹƬ����API��ytc_store_nearsearch.cgi���б�
// 2017/01/17 H.Yasunaga	��ޥȱ�͢������<msg>���������Ƥ�ʸ���������Ѵ����ƽ��Ϥ���褦�ѹ�
/*********************************************************************/
//-----------------------------------------------------------
// ���ϥ��饹
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
	var $cust = '';	// add 2016/04/28 T.Yoshino
	var $RetCode = null;
	var $RecCount = null;
	var $HitCount = null;
	var $ResultSet = array();
	var $CenterLatLon = array('', '');		// add 2016/10/19 Y.Matsukawa
	
	// �ǥХå���
	var $detail = '';
	var $line = '';
	
	//-------------------------------------------
	// ���󥹥ȥ饯��
	//-------------------------------------------
	function KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf, $cust="") {	// mod 2016/04/28 T.Yoshino
	//function KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf) {
		$this->CgiCd = $cgicd;
		$this->CgiNm = $cginm;
		$this->Outf = $outf;
		$this->LineSep = $retcd;
		$this->LineSepEsc = $retcd_e;
		$this->Pflg = $pflg;
		$this->Cust = $cust;	// add 2016/04/28 T.Yoshino
		$this->RetMsg = "";		// add 2016/04/28 T.Yoshino
		$this->RetMsgID = "";	// add 2016/04/28 T.Yoshino
		$this->RetCd = "";		// add 2016/04/28 T.Yoshino
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
	function set_status($retCode, $recCount=null, $hitCount=null) {
		$this->RetCode = substr(trim($retCode), -5);
		$this->RecCount = $recCount;
		$this->HitCount = $hitCount;
	}
	
	//-------------------------------------------
	// set_debug
	// �ǥХå���å��������å�
	//-------------------------------------------
	function set_debug($detail, $line) {
		$this->detail = $detail;
		$this->line = $line;
	}

	//-------------------------------------------
	// set_data
	// ���ϥǡ����ͥ��å�
	//-------------------------------------------
	function set_data($recordNo, $itemName, $value) {
		if (!$this->ResultSet[$recordNo]) {
			$this->ResultSet[$recordNo] = array();
		}
		$this->ResultSet[$recordNo][$itemName] = $value;
	}
	//-------------------------------------------
	// set_data
	// ���ϥǡ��������󥻥å�
	//-------------------------------------------
	function set_data_arr(&$arrData) {
		$this->ResultSet = &$arrData;
	}
	// add 2016/10/19 Y.Matsukawa
	//-------------------------------------------
	// set_centerlatlon
	// �濴���ٷ��٤򥻥å�
	//-------------------------------------------
	function set_centerlatlon($lat, $lon, $datum) {
		if ($datum == DEF_PRM_DATUM_WGS84) {
			// ¬�ϷϤ��Ѵ���TOKYO=>WGS84��
			$res = cnv_transDatum($lat, $lon, TKY_TO_WGS84, $w_lat, $w_lon);
			if ($res) {
				$lat = $w_lat;
				$lon = $w_lon;
			}
		}
		switch ($this->Pflg)  {
			/* ���� */
			case '1':
				$this->CenterLatLon[0] = cnv_dms2hour($lat);
				$this->CenterLatLon[1] = cnv_dms2hour($lon);
				break;
			/* �ߥ��� */
			case '2':
				$this->CenterLatLon[0] = $lat;
				$this->CenterLatLon[1] = $lon;
				break;
			/* ��ʬ�� */
			case '3':
				$this->CenterLatLon[0] = cnv_dms2deg($lat);
				$this->CenterLatLon[1] = cnv_dms2deg($lon);
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
			default:
				Header('Content-type: application/json; charset='.$this->EncStr);
		}
	}
	//-------------------------------------------
	// output_body_start
	// �쥹�ݥ󥹥ܥǥ����ϳ���
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
	// ���ơ���������
	//-------------------------------------------
	function output_status() {
		include('store_def.inc');
	
		// mod 2016/04/28 T.Yoshino [
		// �̾��
		if($this->Cust == "") {
			
			switch ($this->RetCode) {
				case "09000";
				case "09001";
				case "09002";
				case "09003";
				case "09004";
				case "09005";
				case "09006";
				case "09007";
				case "09008";
				case "09009";
				case "09010";
					$this->RetCode = "19100";
					break;
				default:
			}

			switch ($this->Outf) {
				case 'XML':
					// �ǥХå��⡼�ɻ�
					if ($D_DEBUG && $this->line != '') {
						echo '<debug_detail>'.f_enc_convert($this->detail).'</debug_detail>'.$this->LineSep;
						echo '<debug_line>'.$this->line.'</debug_line>'.$this->LineSep;
					}
								
					echo '<status>'.$this->LineSep;
					echo '<return_code>'.$this->CgiCd.$this->RetCode.'</return_code>'.$this->LineSep;
					echo '<rec_count>'.$this->RecCount.'</rec_count>'.$this->LineSep;
					echo '<hit_count>'.$this->HitCount.'</hit_count>'.$this->LineSep;
					echo '</status>'.$this->LineSep;
					break;
				default:
					// �ǥХå��⡼�ɻ�
					if ($D_DEBUG && $this->line != '') {
						echo '"debug_detail":"'.f_enc_convert($this->detail).'"';
						echo ',';
						echo '"debug_line":"'.$this->line.'"';
						echo ',';
					}

					echo '"return_code":"'.$this->CgiCd.$this->RetCode.'"';
					echo ',';
					echo '"rec_count":"'.$this->RecCount.'"';
					echo ',';
					echo '"hit_count":"'.$this->HitCount.'"';
			}

		// ��ޥȱ�͢����
		} else if ( $this->Cust == "YAMATO01" ) {
			
			// ����status�Ѱ�
			include('ytc_ret_def.inc');
			list( $RetMsg, $RetMsgID, $RetCd ) = getYamatoRetCd($this->RetCode);
			// add start 2017/01/17 H.Yasunaga <msg>���������Ƥ���ϥ��󥳡��ɤ˹�碌���Ѵ����� [
			$RetMsg = mb_convert_encoding($RetMsg, $this->Enc, "EUC-jp");
			// add end 2017/01/17 H.Yasunaga ]

			$ArrMicro = explode('.',microtime(true));
			$intMicro = sprintf('%03d', substr($ArrMicro[1], 0, 3));
			
			switch ($this->Outf) {
				case 'XML':
					// �ǥХå��⡼�ɻ�
					if ($D_DEBUG && $this->line != '') {
						echo '<debug_detail>'.f_enc_convert($this->detail).'</debug_detail>'.$this->LineSep;
						echo '<debug_line>'.$this->line.'</debug_line>'.$this->LineSep;
					}
					
					echo '<status>'.$this->LineSep;
					echo '<msg>'.$RetMsg.'</msg>'.$this->LineSep;
					echo '<msg_id>'.$RetMsgID.'</msg_id>'.$this->LineSep;
					echo '<return_code>'.$RetCd.'</return_code>'.$this->LineSep;
					echo '<rtn_date>'. date("Y-m-d") . "T" . date( "H:i:s.") . $intMicro . date("O") . '</rtn_date>'.$this->LineSep;
					echo '<rec_count>'.$this->RecCount.'</rec_count>'.$this->LineSep;
					echo '<hit_count>'.$this->HitCount.'</hit_count>'.$this->LineSep;
					echo '</status>'.$this->LineSep;
					break;
				default:
					// �ǥХå��⡼�ɻ�
					if ($D_DEBUG && $this->line != '') {
						echo '"debug_detail":"'.f_enc_convert($this->detail).'"';
						echo ',';
						echo '"debug_line":"'.$this->line.'"';
						echo ',';
					}

					echo '"msg":"'.$RetMsg.'"';
					echo ',';
					echo '"msg_id":"'.$RetMsgID.'"';
					echo ',';
					echo '"return_code":"'.$RetCd.'"';
					echo ',';
					echo '"rtn_date":"' . date("Y-m-d") . "T" . date( "H:i:s.") . $intMicro . date("O") . '"';
					echo ',';
					echo '"rec_count":"'.$this->RecCount.'"';
					echo ',';
					echo '"hit_count":"'.$this->HitCount.'"';
			}

		// add 2016/10/19 Y.Matsukawa [
		// ��ޥȱ�͢��ŹƬ����API��
		} else if ($this->Cust == "YAMATO03") {
			// ����status�Ѱ�
			include('ytc_ret_def_EUC.inc');
			list( $RetMsg, $RetMsgID, $RetCd ) = getYamatoRetCd($this->RetCode);
			$ArrMicro = explode('.',microtime(true));
			$intMicro = sprintf('%03d', substr($ArrMicro[1], 0, 3));
			switch ($this->Outf) {
				case 'XML':
					// �ǥХå��⡼�ɻ�
					if ($D_DEBUG && $this->line != '') {
						echo '<debug_detail>'.f_enc_convert($this->detail).'</debug_detail>'.$this->LineSep;
						echo '<debug_line>'.$this->line.'</debug_line>'.$this->LineSep;
					}
					echo '<status>'.$this->LineSep;
					echo '<msg>'.f_enc_convert($RetMsg).'</msg>'.$this->LineSep;
					echo '<msg_id>'.$RetMsgID.'</msg_id>'.$this->LineSep;
					echo '<return_code>'.$RetCd.'</return_code>'.$this->LineSep;
					echo '<rtn_date>'. date("Y-m-d") . "T" . date( "H:i:s.") . $intMicro . date("O") . '</rtn_date>'.$this->LineSep;
					echo '<rec_count>'.$this->RecCount.'</rec_count>'.$this->LineSep;
					echo '<hit_count>'.$this->HitCount.'</hit_count>'.$this->LineSep;
					echo '<center_lat>'.$this->CenterLatLon[0].'</center_lat>'.$this->LineSep;
					echo '<center_lon>'.$this->CenterLatLon[1].'</center_lon>'.$this->LineSep;
					echo '</status>'.$this->LineSep;
					break;
				default:
					// �ǥХå��⡼�ɻ�
					if ($D_DEBUG && $this->line != '') {
						echo '"debug_detail":"'.f_enc_convert($this->detail).'"';
						echo ',';
						echo '"debug_line":"'.$this->line.'"';
						echo ',';
					}
					echo '"msg":"'.f_enc_convert($RetMsg).'"';
					echo ',';
					echo '"msg_id":"'.$RetMsgID.'"';
					echo ',';
					echo '"return_code":"'.$RetCd.'"';
					echo ',';
					echo '"rtn_date":"' . date("Y-m-d") . "T" . date( "H:i:s.") . $intMicro . date("O") . '"';
					echo ',';
					echo '"rec_count":"'.$this->RecCount.'"';
					echo ',';
					echo '"hit_count":"'.$this->HitCount.'"';
					echo ',';
					echo '"center_lat":"'.$this->CenterLatLon[0].'"';
					echo ',';
					echo '"center_lon":"'.$this->CenterLatLon[1].'"';
			}
		// add 2016/10/19 Y.Matsukawa [

		// mod 2016/07/19 T.Yoshino [
		// 711OMNI����CGI
		} else if ( $this->Cust == "711OMNICGI" ) {
		
			$intStCd = ( $this->RetCode == "00000" )? 0: 1;
		
			echo '<status>'.$this->LineSep;
			echo '<status_code>'.$intStCd.'</status_code>'.$this->LineSep;
			echo '<return_code>'.$this->CgiCd.$this->RetCode.'</return_code>'.$this->LineSep;
			echo '<match_rank>'.$this->HitCount.'</match_rank>'.$this->LineSep;
			echo '</status>'.$this->LineSep;
		
		}
		// mod 2016/07/19 T.Yoshino ]
		// mod 2016/04/28 T.Yoshino ]
	}

	//-------------------------------------------
	// output_body_end
	// �쥹�ݥ󥹥ܥǥ����Ͻ�λ
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
	// JSON����ʸ����Υ��������׽���
	//-------------------------------------------
	function escapeJSON($str) {
		$ret = $str;
		$ret = mb_ereg_replace("\"", "\\\"", $ret);
		// add 2013/03/11 Y.Matsukawa [
		$ret = mb_ereg_replace("\r\n", "\\n", $ret);
		$ret = mb_ereg_replace("\n", "\\n", $ret);
		$ret = mb_ereg_replace("\r", "\\n", $ret);
		// add 2013/03/11 Y.Matsukawa ]
		return $ret;
	}

	//-------------------------------------------
	// escapeXML
	// XML����ʸ����Υ��������׽���
	//-------------------------------------------
	function escapeXML($str) {
		$ret = $str;
		$ret = htmlspecialchars($ret);
		// add 2013/03/11 Y.Matsukawa [
		$ret = mb_ereg_replace("\r\n", "\\n", $ret);
		$ret = mb_ereg_replace("\n", "\\n", $ret);
		$ret = mb_ereg_replace("\r", "\\n", $ret);
		// add 2013/03/11 Y.Matsukawa ]
		return $ret;
	}

	// add 2013/03/11 Y.Matsukawa
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

	// add 2013/03/11 Y.Matsukawa
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
	// add 2013/03/11 Y.Matsukawa
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

	// add 2013/03/11 Y.Matsukawa
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
	// add 2013/03/11 Y.Matsukawa
	//-------------------------------------------
	// Ϣ�����󳫻ϥ�����JSON��name���ϡ�
	//-------------------------------------------
	function output_hash_start_with_name($name, $id='') {
		switch ($this->Outf) {
			case 'XML':
				echo '<'.$name.($id!=''?' id="'.$id.'"':'').'>';
				break;
			case 'JSON':
				echo '"'.$name.'":';
				echo '{';
				break;
		}
	}
	// add 2013/03/11 Y.Matsukawa
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

	// add 2013/03/11 Y.Matsukawa
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

}

?>