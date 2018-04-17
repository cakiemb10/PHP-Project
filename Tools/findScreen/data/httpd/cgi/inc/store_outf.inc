<?php
/**********************************************************************
// 更新履歴：
// 2011/11/01 H.Nakamura	新規作成
// 2013/03/11 Y.Matsukawa	リアルタイムデータ
// 2016/04/28 T.Yoshino		出力項目を追加(yamato)
// 2016/07/19 T.Yoshino		出力項目を追加(711OMNI用CGI)
// 2016/10/19 Y.Matsukawa	ヤマト運輸向け店頭受取API（ytc_store_nearsearch.cgi）対応
// 2017/01/17 H.Yasunaga	ヤマト運輸向けの<msg>タグの内容を文字コード変換して出力するよう変更
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
	var $cust = '';	// add 2016/04/28 T.Yoshino
	var $RetCode = null;
	var $RecCount = null;
	var $HitCount = null;
	var $ResultSet = array();
	var $CenterLatLon = array('', '');		// add 2016/10/19 Y.Matsukawa
	
	// デバッグ用
	var $detail = '';
	var $line = '';
	
	//-------------------------------------------
	// コンストラクタ
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
	// statusセット
	//-------------------------------------------
	function set_status($retCode, $recCount=null, $hitCount=null) {
		$this->RetCode = substr(trim($retCode), -5);
		$this->RecCount = $recCount;
		$this->HitCount = $hitCount;
	}
	
	//-------------------------------------------
	// set_debug
	// デバッグメッセージセット
	//-------------------------------------------
	function set_debug($detail, $line) {
		$this->detail = $detail;
		$this->line = $line;
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
	// add 2016/10/19 Y.Matsukawa
	//-------------------------------------------
	// set_centerlatlon
	// 中心緯度経度をセット
	//-------------------------------------------
	function set_centerlatlon($lat, $lon, $datum) {
		if ($datum == DEF_PRM_DATUM_WGS84) {
			// 測地系の変換（TOKYO=>WGS84）
			$res = cnv_transDatum($lat, $lon, TKY_TO_WGS84, $w_lat, $w_lon);
			if ($res) {
				$lat = $w_lat;
				$lon = $w_lon;
			}
		}
		switch ($this->Pflg)  {
			/* 十進 */
			case '1':
				$this->CenterLatLon[0] = cnv_dms2hour($lat);
				$this->CenterLatLon[1] = cnv_dms2hour($lon);
				break;
			/* ミリ秒 */
			case '2':
				$this->CenterLatLon[0] = $lat;
				$this->CenterLatLon[1] = $lon;
				break;
			/* 度分秒 */
			case '3':
				$this->CenterLatLon[0] = cnv_dms2deg($lat);
				$this->CenterLatLon[1] = cnv_dms2deg($lon);
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
		include('store_def.inc');
	
		// mod 2016/04/28 T.Yoshino [
		// 通常時
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
					// デバッグモード時
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
					// デバッグモード時
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

		// ヤマト運輸専用
		} else if ( $this->Cust == "YAMATO01" ) {
			
			// 専用status用意
			include('ytc_ret_def.inc');
			list( $RetMsg, $RetMsgID, $RetCd ) = getYamatoRetCd($this->RetCode);
			// add start 2017/01/17 H.Yasunaga <msg>タグの内容を出力エンコードに合わせて変換する [
			$RetMsg = mb_convert_encoding($RetMsg, $this->Enc, "EUC-jp");
			// add end 2017/01/17 H.Yasunaga ]

			$ArrMicro = explode('.',microtime(true));
			$intMicro = sprintf('%03d', substr($ArrMicro[1], 0, 3));
			
			switch ($this->Outf) {
				case 'XML':
					// デバッグモード時
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
					// デバッグモード時
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
		// ヤマト運輸（店頭受取API）
		} else if ($this->Cust == "YAMATO03") {
			// 専用status用意
			include('ytc_ret_def_EUC.inc');
			list( $RetMsg, $RetMsgID, $RetCd ) = getYamatoRetCd($this->RetCode);
			$ArrMicro = explode('.',microtime(true));
			$intMicro = sprintf('%03d', substr($ArrMicro[1], 0, 3));
			switch ($this->Outf) {
				case 'XML':
					// デバッグモード時
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
					// デバッグモード時
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
		// 711OMNI様用CGI
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
	// XML出力文字列のエスケープ処理
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

	// add 2013/03/11 Y.Matsukawa
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
	// add 2013/03/11 Y.Matsukawa
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

	// add 2013/03/11 Y.Matsukawa
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
	// add 2013/03/11 Y.Matsukawa
	//-------------------------------------------
	// 連想配列開始タグ（JSONもname出力）
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

	// add 2013/03/11 Y.Matsukawa
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

}

?>
