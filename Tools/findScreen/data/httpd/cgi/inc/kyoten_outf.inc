<?php
/**********************************************************************
// 更新履歴：
// 2010/01/08 Y.Matsukawa	新規作成
// 2016/04/28 T.Yoshino		出力項目を追加
/*********************************************************************/
//-----------------------------------------------------------
// 出力クラス
//-----------------------------------------------------------
class KyotenCgiOutput {
	var $CgiCd = "";
	var $CgiNm = "";
	var $Enc = "";
	var $EncStr = "";
	var $LineSep = "";
	var $LineSepEsc = "";
	var $Outf = "";
	var $Pflg = "";
	var $cust = '';	// add 2016/04/28 T.Yoshino
	var $RetCode = null;
	var $RecCount = null;
	var $HitCount = null;
	var $ResultSet = array();
	//-------------------------------------------
	// コンストラクタ
	//-------------------------------------------
	function KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf, $cust="") {	// mod 2016/04/28 T.Yoshino
//	function KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf) {
		$this->CgiCd = $cgicd;
		$this->CgiNm = $cginm;
		$this->Outf = $outf;
		$this->LineSep = $retcd;
		$this->LineSepEsc = $retcd_e;
		$this->Pflg = $pflg;
		$this->Cust = $cust;	// add 2016/04/28 T.Yoshino
		switch ($enc) {
			case "UTF8":
				$this->Enc = "UTF-8";
				$this->EncStr = "UTF-8";
				break;
			case "EUC":
				$this->Enc = "EUC-JP";
				$this->EncStr = "EUC-JP";
				break;
			default:
				$this->Enc = "SJIS";
				$this->EncStr = "Shift_JIS";
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
			case "XML":
				Header("Content-type: text/xml; charset=$this->EncStr");
				break;
			default:
				Header("Content-type: application/json; charset=$this->EncStr");
		}
	}
	//-------------------------------------------
	// output_body_start
	// レスポンスボディ出力開始
	//-------------------------------------------
	function output_body_start() {
		switch ($this->Outf) {
			case "XML":
				echo "<?xml version=\"1.0\" encoding=\"$this->EncStr\" ?>" . $this->LineSep;
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
				case "XML":
					break;
				default:
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

			$ArrMicro = explode('.',microtime(true));
			$intMicro = sprintf('%03d', substr($ArrMicro[1], 0, 3));
			
			switch ($this->Outf) {
				case "XML":
					break;
				default:
					echo '"msg":"			'.$RetMsg.'"';
					echo ',';
					echo '"msg_id":"		'.$RetMsgID.'"';
					echo ',';
					echo '"return_code":"	'.$RetCd.'"';
					echo ',';
					echo '"rtn_Date":"		'. date("Y-m-d") . "T" . date( "H:i:s.") . $intMicro . date("O") . '"';
					echo ',';
					echo '"rec_count":"		'.$this->RecCount.'"';
					echo ',';
					echo '"hit_count":"		'.$this->HitCount.'"';
			}

		}

	}
	//-------------------------------------------
	// output_body_end
	// レスポンスボディ出力終了
	//-------------------------------------------
	function output_body_end() {
		switch ($this->Outf) {
			case "XML":
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
}

// ------------------------------------------------------------
//
// 文字コード変換 
//  mb_convert_encodingにバグがあったら拡張していく
//
// ------------------------------------------------------------
function ZdcConvertEncoding($text) {
	GLOBAL $enc;

	// mod 2011/07/05 Y.Nakajima [
	// 〜が~に置き換えられる
	//if($enc) $tmp = $enc;
		//else $tmp = "EUC-JP,UTF-8,SJIS,auto";
	//return mb_convert_encoding($text,"EUC",$tmp);
	if(isset($enc) && $enc != "") $tmp = $enc;
		else $tmp = "eucJP-win,UTF-8,SJIS-win,auto";
	if ($tmp == "EUC" || $tmp == "euc" || $tmp == "EUC-JP") $tmp ="eucJP-win";
	return mb_convert_encoding($text,"eucJP-win",$tmp);
	// mod 2011/07/05 Y.Nakajima ]
}


?>
