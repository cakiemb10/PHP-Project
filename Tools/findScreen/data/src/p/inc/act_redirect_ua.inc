<?php
// ------------------------------------------------------------
// 2012/03/12 Y.Matsukawa	新規作成
// 2012/10/01 Y.Matsukawa	Maplink対応
// 2015/02/20 H.Osamoto		携帯からのアクセスをリダイレクト
//							スマホMaplinkへのリダイレクト不具合修正
// 2015/08/17 Y.Matsukawa	iPadリダイレクト対応
// 2015/08/25 Y.Matsukawa	スマホリダイレクト（top.location変更）
// ------------------------------------------------------------
//--------------------------------------------
// カスタムリダイレクト（top.location変更による画面遷移）		add 2015/08/25 Y.Matsukawa
//--------------------------------------------
if ($CUST_JUMP_LOCATION) {
	$tpl['JUMP_LOCATION'] = $CUST_JUMP_LOCATION;
	htmloutput($D_SYSDIR_COMPANY."jump.tpl", $tpl);
	exit;
}

//--------------------------------------------
// スマホからのアクセス時のリダイレクト
//--------------------------------------------
$UA_IPHONE = false;
$UA_IPAD = false;		// add 2015/08/17 Y.Matsukawa
$UA_ANDROID = false;
if (strpos($_SERVER['HTTP_USER_AGENT'], 'iPhone')) {
	$UA_IPHONE = true;
// add 2015/08/17 Y.Matsukawa [
} else if (strpos($_SERVER['HTTP_USER_AGENT'], 'iPad')) {
	$UA_IPAD = true;
// add 2015/08/17 Y.Matsukawa ]
} else if (strpos($_SERVER['HTTP_USER_AGENT'], 'Android')) {
	$UA_ANDROID = true;
}
//if (($UA_IPHONE && $D_IPHONE_REDIRECT_SMT) || ($UA_ANDROID && $D_ANDROID_REDIRECT_SMT)) {		mod 2015/08/17 Y.Matsukawa
if (($UA_IPHONE && $D_IPHONE_REDIRECT_SMT)
||  ($UA_IPAD && $D_IPAD_REDIRECT_SMT)
||  ($UA_ANDROID && $D_ANDROID_REDIRECT_SMT)) {
	$REDIRECT_SMT_URL = "http://$D_DOMAIN_G/smt/$D_CID/";
	// 拠点ID接続のリダイレクト
	if ($D_REDIRECT_SMT_KYO_ID) {
		if ($script_name == 'shop_dtl.htm' && isset($kid) && $kid != '') {
			$REDIRECT_SMT_URL .= "$D_REDIRECT_SMT_KYO_ID/$kid/";
		}
	}
	// 住所リストのリダイレクト
	if ($D_REDIRECT_SMT_ADDR_LIST) {
		if ($script_name == 'search.htm' && isset($type) && $type == 'AddrL') {
			$REDIRECT_SMT_URL .= 'search_addr.htm';
			if (isset($adcd)) $REDIRECT_SMT_URL .= "?adcd=$adcd";
		}
	}
	// 駅リストのリダイレクト
	if ($D_REDIRECT_SMT_EKI_LIST) {
		if ($script_name == 'search.htm' && isset($type) && $type == 'StL') {
			$REDIRECT_SMT_URL .= 'search_eki.htm';
			if (isset($adcd)) $REDIRECT_SMT_URL .= "?tod=$adcd";
		}
	}
	// 住所フリーワード検索のリダイレクト
	if ($D_REDIRECT_SMT_ADDR_FW) {
		if ($script_name == 'search.htm' && isset($type) && $type == 'AddrW' && isset($keyword)) {
			$REDIRECT_SMT_URL .= 'search_fw.htm';
			$REDIRECT_SMT_URL .= '?keyword='.urlencode($keyword);
			$REDIRECT_SMT_URL .= '&init_view=2';
		}
	}
	// 駅フリーワード検索のリダイレクト
	if ($D_REDIRECT_SMT_EKI_FW) {
		if ($script_name == 'search.htm' && isset($type) && $type == 'StW' && isset($keyword)) {
			$REDIRECT_SMT_URL .= 'search_fw.htm';
			$REDIRECT_SMT_URL .= '?keyword='.urlencode($keyword);
		}
	}
	// 郵便番号検索のリダイレクト
	if ($D_REDIRECT_SMT_ZIP_FW) {
		if ($D_REDIRECT_TO_ZIPW && $REDIRECT_ZIPW_KW) {
			$script_name = 'search.htm';
			$type = 'ZipW';
			$keyword = $REDIRECT_ZIPW_KW;
		}
		if ($script_name == 'search.htm' && isset($type) && $type == 'ZipW' && isset($keyword)) {
			$REDIRECT_SMT_URL .= 'search_fw.htm';
			$REDIRECT_SMT_URL .= '?keyword='.urlencode($keyword);
			$REDIRECT_SMT_URL .= '&init_view=2';
		}
	}
	// 拠点フリーワード検索のリダイレクト
	if ($D_REDIRECT_SMT_KYO_FW) {
		if ($script_name == 'search.htm' && isset($type) && $type == 'ShopW' && isset($keyword)) {
			$REDIRECT_SMT_URL .= 'fw.htm';
			$REDIRECT_SMT_URL .= '?keyword='.urlencode($keyword);
		}
	}
	// 拠点リスト検索のリダイレクト
	if ($D_REDIRECT_SMT_KYO_LIST) {
		if ($script_name == 'search.htm' && isset($type) && $type == 'ShopA') {
			$REDIRECT_SMT_URL .= 'sl.htm?';
			if (isset($areaptn)) $REDIRECT_SMT_URL .= "&ltype=".$areaptn;
			if (isset($area1)) $REDIRECT_SMT_URL .= "&area1=".urlencode($area1);
			if (isset($area2)) $REDIRECT_SMT_URL .= "&area2=".urlencode($area2);
		}
	}
	// Maplinkのリダイレクト		add 2012/10/01 Y.Matsukawa
	if ($script_name == 'maplink.htm') {
		if ($lat && $lon) {
			//	$REDIRET_SMT_URL .= 'link/lat='.$lat.',lon='.$lon	mod 2015/02/20 H.Osamoto
			$REDIRECT_SMT_URL .= 'link/lat='.$lat.',lon='.$lon
								.'/?nm='.urlencode($nm).'&lv='.$lv.'&icn='.$icn.'&enc=EUC';
		} else if ($addr) {
			//	$REDIRET_SMT_URL .= 'link/addr='.urlencode($addr)	mod 2015/02/20 H.Osamoto
			$REDIRECT_SMT_URL .= 'link/addr='.urlencode($addr)
								.'/?nm='.urlencode($nm).'&lv='.$lv.'&icn='.$icn.'&enc=EUC';
		}
	}

	if (!strpos($REDIRECT_SMT_URL, '?')) $REDIRECT_SMT_URL .= '?';
	else $REDIRECT_SMT_URL .= '&';
	$REDIRECT_SMT_URL .= 'enc=EUC';

	// 追加パラメータ（カスタマイズ）
	if (isset($D_SMT_REDIRECT_ADDPARAM) && $D_SMT_REDIRECT_ADDPARAM) {
		$REDIRECT_SMT_URL .= '&'.$D_SMT_REDIRECT_ADDPARAM;
	}
	// 任意パラメータ
	if (isset($D_REDIRECT_SMT_FREEPARAMS) && $D_REDIRECT_SMT_FREEPARAMS && $P_FREEPARAMS_ENC) {
		$REDIRECT_SMT_URL .= '&'.$P_FREEPARAMS_ENC;
	}

	header('Location: '.$REDIRECT_SMT_URL);
	exit;
}

// 2015/02/20 H.Osamoto add [
//--------------------------------------------
// 携帯からのアクセス時のリダイレクト
//--------------------------------------------

// CARRIER判別文字列定義
define("D_DOCOMO"  , "DoCoMo");
define("D_SOFTBANK", "SOFTBANK");
define("D_KDDI"    , "KDDI");

$UA_MOBILE = false;

if ($D_MOBILE_REDIRECT_MB) {

	// 端末情報取得
	$mobile_carrier = getMobileInfo($_SERVER['HTTP_USER_AGENT']);

	if ($mobile_carrier) {
		$REDIRECT_MB_URL = "http://$D_DOMAIN_G/mobile/$D_CID/";
		// 拠点ID接続のリダイレクト
		if ($D_REDIRECT_MB_KYO_ID) {
			if ($script_name == 'shop_dtl.htm' && isset($kid) && $kid != '') {
				$REDIRECT_MB_URL .= "d.htm?$D_REDIRECT_MB_KYO_ID=$kid";
			}
		}
		// Maplinkのリダイレクト
		if ($script_name == 'maplink.htm') {
			if ($lat && $lon) {
				$REDIRECT_MB_URL .= 'd.htm?lat='.$lat.',lon='.$lon
									.'&nm='.urlencode($nm).'&lv='.$lv.'&icn='.$icn;
			} else if ($addr) {
				$REDIRECT_MB_URL .= 'd.htm?addr='.urlencode($addr)
									.'&nm='.urlencode($nm).'&lv='.$lv.'&icn='.$icn;
			}
		}

		if (!strpos($REDIRECT_MB_URL, '?')) $REDIRECT_MB_URL .= '?';
		
		$REDIRECT_MB_URL .= '&enc=EUC';

		// 追加パラメータ（カスタマイズ）
		if (isset($D_MB_REDIRECT_ADDPARAM) && $D_MB_REDIRECT_ADDPARAM) {
			$REDIRECT_MB_URL .= '&'.$D_MB_REDIRECT_ADDPARAM;
		}
		// 任意パラメータ
		if (isset($D_REDIRECT_MB_FREEPARAMS) && $D_REDIRECT_MB_FREEPARAMS && $P_FREEPARAMS_ENC) {
			$REDIRECT_MB_URL .= '&'.$P_FREEPARAMS_ENC;
		}

		header('Location: '.$REDIRECT_MB_URL);
		exit;
	}
}

//---------------------------------------------------------------
// 端末情報マスタからキャリア情報、画面情報取得
//---------------------------------------------------------------
function getMobileInfo($P_USER_AGENT){
	// 戻り配列の初期化
	$carrier = "";

	global $D_SSAPI;
	global $D_SOCKET_TIMEOUT;

	// 端末情報取得ＣＧＩ
	$url = $D_SSAPI["getmobileinfo"]."?ua=".urlencode($P_USER_AGENT);

	$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);

	$status_str = array_shift($dat);
	$status  = explode("\t", $status_str);

	$mobile_array = explode("\t", $dat[0]);
	$info = Array(
		"CARRIER"=>$mobile_array[0],
		"GENERATION"=>$mobile_array[1],
		"HEIGHT"=>$mobile_array[2],
		"WIDTH"=>$mobile_array[3],
		"IMAGE_TYPE"=>$mobile_array[4],
		"GPS_FLG"=>$mobile_array[5],
		"COLOR"=>$mobile_array[9],
		"AUTOGPS"=>$mobile_array[19]
	);


	// 取得したキャリア毎の判定処理
	switch($info["CARRIER"]){
		case "1":
			//DOCOMO
			$carrier = D_DOCOMO;
			break;
		case "2":
			//AU
			$carrier = D_KDDI;
			break;
		case "3":
			//SOFTBANK
			$carrier = D_SOFTBANK;
			break;
		default:
			// 上記以外
			$carrier = "";
	}

	return $carrier;
}

// 2015/02/20 H.Osamoto add ]
?>
