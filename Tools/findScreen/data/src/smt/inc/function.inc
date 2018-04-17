<?PHP
// ------------------------------------------------------------
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/26 Y.Matsukawa	スマホ用拠点縮尺カラム対応
// 2012/01/19 N.Wada		拠点データ取得時に、SJISに変換しかつURLエンコードしたものをセットする
//							別CID参照
// 2012/02/23 Y.Matsukawa	店舗全件リスト画面
// 2012/03/04 K.Masuda 		フリーワード検索文字化け対応
// 2012/07/27 Y.Matsukawa	リスト検索：検索利用回数ログの判定フラグ出力
// 2012/08/03 H.Osamoto		禁則文字緩和対応(「'」「"」「>」「\」「`」（バッククォート）)を許可
// 2012/08/15 H.Osamoto		拠点データ取得時に、UTF8に変換しかつURLエンコードしたものをセットする
// 2012/10/10 H.Osamoto		任意カラムのアイコンIDを使用
// 2013/01/31 H.Osamoto		1000mを超える場合、距離表示をkmに変換
// 2013/02/07 H.osamoto		禁則文字緩和の不具合対応
// 2013/03/26 H.Iijima		リアルタイムデータ
// 2013/07/18 Y.Matsukawa	任意のカラムが特定の値の場合にフラグを立てる
// 2013/07/19 T.Sasaki		拠点（複数）画像対応
// 2014/02/10 Y.Matsukawa	脆弱性対策（XSS等）
// 2014/03/12 Y.Matsukawa	ヤマト運輸向けカスタマイズ：営業時間・定休日サマリ表示
// 2014/03/12 Y.Matsukawa	任意カラム同士の一致判定
// 2014/03/12 Y.Matsukawa	任意カラムの値判定
// 2014/03/12 Y.Matsukawa	任意のカラムが特定の値の場合にフラグを立てる
// 2014/03/17 Y.Matsukawa	店舗詳細でも絞り込みを有効にする
// 2014/05/29 Y.Matsukawa	商品マスタ対応
// 2014/08/26 AnPham		BrowsingHistoryDisplay
// 2014/10/27 H.osamoto		Cookie情報取得時に店舗情報を取得する際の企業IDを修正
// 2015/03/25 Y.Matsukawa	詳細画面に10進書式の緯度経度を渡す
// 2015/05/22 H.osamoto		拠点縮尺にキーワードを付与し誤作動を防ぐ
// 2015/09/25 H.Yasunaga	公開開始日時・公開終了日時・NEW表示開始日時・NEW表示終了日時を$tplに含める
// 2015/10/08 N.Wada		任意カラムの値判定にLT,GT,LTE,GTEを追加
// 2015/11/16 Y.Uesugi		郵便番号の数値7桁にハイフンをつけて「111-0000」の形式にする
// 2015/11/30 Y.Uesugi		任意カラムの値判定(比較位置指定)
// 2015/12/08 Y.Uesugi		ヤマト運輸向けカスタマイズ：平日営業日サマリ表示
// 2015/12/18 F.Yokoi		登録されたHTMLエンティティ文字が正常に表示されるように、別関数を追加する
// 2015/12/22 Y.Uesugi		ヤマト運輸 営業所検索（祝日情報取得）
// 2016/12/19 N.Wada		フラグ項目グループ判定
// 2016/12/19 N.Wada		時刻書式整形
// 2016/12/19 N.Wada		値グループ判定
// 2016/12/19 N.Wada		値グループ判定（どれか１つ以上、任意の値と一致する）
// 2016/12/19 N.Wada		任意カラム（時刻）同士の比較
// 2016/12/19 N.Wada		フラグ項目グループ判定（フラグ項目すべてON）
// 2016/12/19 N.Wada		電話番号から-を取り除く（aタグのtel:用）
// 2017/01/11 N.Wada		許可タグリスト追加
// 2017/01/25 N.Wada		拠点の世界測地系の緯度経度を、世界測地系カラムの値で上書き
// 2017/02/09 N.Wada		PC詳細画面へのリンク追加
// ------------------------------------------------------------
// ------------------------------------------------------------
// HTML出力
// ------------------------------------------------------------
function htmloutput($tplfile, &$tpl) {
	if (!is_file($tplfile)) return;
	// mod 2011/07/05 Y.Nakajima [
/*
	$html = @HtmlTemplate::t_buffer($tplfile, $tpl);
	$html = mb_convert_encoding($html, 'UTF-8', 'EUC-JP');
*/

	$HtmlTemplate = new HtmlTemplate();
	$html = $HtmlTemplate->t_buffer($tplfile, $tpl);
	$html = mb_convert_encoding($html, 'UTF-8', 'eucJP-win');
	// mod 2011/07/05 Y.Nakajima ]
	echo $html;
}

// ------------------------------------------------------------
// 文字コード変換
// ------------------------------------------------------------
function ZdcConvertEncoding($text) {
	global $enc;
	// mod 2011/07/05 Y.Nakajima [
/*
	if($enc) $tmp = $enc;
	else $tmp = 'UTF-8,EUC-JP,SJIS,auto';
	return mb_convert_encoding($text, 'EUC', $tmp);
*/

	if(isset($enc) && $enc != "") $tmp = $enc;
	else $tmp = "UTF-8,eucJP-win,SJIS-win,auto";
	if ($tmp == "EUC" || $tmp == "euc" || $tmp == "EUC-JP") $tmp ="eucJP-win";
	$ret = mb_convert_encoding($text,"eucJP-win",$tmp);
	return $ret;

	// mod 2011/07/05 Y.Nakajima ]

}

// ------------------------------------------------------------
// JSリテラル指定用のエスケープ関数
// 「"」→「\"」
// ------------------------------------------------------------
function ZdcEsc4JsLiteral($text) {
	//return mb_ereg_replace('"', '\"', $text);		del 2014/02/10 Y.Matsukawa
	// add 2014/02/10 Y.Matsukawa [
	$str = $text;
	$str = mb_ereg_replace('"', '\"', $str);
	$str = mb_ereg_replace("'", "\\'", $str);
	return $str;
	// add 2014/02/10 Y.Matsukawa ]
}

// ------------------------------------------------------------
// IPチェック
// ------------------------------------------------------------
function ip_check() {
	global $D_ALLOW_IP;
	global $D_DEFAULT_ALLOW_IP;
	
	if ($D_ALLOW_IP == '') return true;
	
	$REMOTE_ADDR = $_SERVER['REMOTE_ADDR'];
	
	$ip_list = array_merge(explode(';', $D_ALLOW_IP), $D_DEFAULT_ALLOW_IP);

	foreach ($ip_list as $i=>$ip) {
		// IPアドレス指定（xxx.xxx.xxx.xxx）
		if (preg_match("/^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$/", $ip)) {
			if (strcmp($REMOTE_ADDR, $ip) == 0) return true;
		// IPアドレス＆サブネットマスク指定（xxx.xxx.xxx.xxx/xx）
		} else if (preg_match("/^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\/([0-9]{1,2})$/", $ip)) {
			// mod 2011/07/05 Y.Nakajima
			//$res = split('[/.]', $ip);
			$res = explode('[/.]', $ip);
			$w_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			$mask = intval($res[4]);
			$shift = 32 - $mask;
			// mod 2011/07/05 Y.Nakajima
			//$res = split('[/.]', $REMOTE_ADDR);
			$res = explode('[/.]', $REMOTE_ADDR);
			$r_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			if (($w_ip >> $shift) == ($r_ip >> $shift)) return true;
		}
	}

	return false;
}

// ------------------------------------------------------------
//
// ログ関係
// 出力内容
//  1.基本
//    script cid opt refferer status service
//  2.emapview
//    kid lat lon type keyword adcd area col nm no cond
//  3.search
//    page jnrmn jnr jkn 
//
// ------------------------------------------------------------
function ZdcLogPut($status) {
	global $_VARS,$LOG_MODE,$D_CID;
	include_once('/home/emap/src/log/inc/com_log_open.inc');
	
	// add 2011/07/05 Y.Nakajima [
	//初期化
	$cond ="";
	// add 2011/07/05 Y.Nakajima ]
	//絞込み条件の加工
	for($i = 1;$i <= 200;$i ++) {
		// mod 2011/07/05 Y.Nakajima [
		if(isset($_VARS['cond'.$i])) {
			if(isset($cond) && $cond != "") $cond .= ',';
		// mod 2011/07/05 Y.Nakajima ]
			$cond .= sprintf("cond%d=%s",$i,$_VARS['cond'.$i]);
		}
	}
	//128バイトに丸める
	$cond = mb_strimwidth($cond, 0, 128, '...');
	$cond = mb_ereg_replace(' ','_',$cond);
	// add 2011/07/05 Y.Nakajima [
	if (!isset($_VARS['kid'])) $_VARS['kid'] = "";
	if (!isset($_VARS['lat'])) $_VARS['lat'] = "";
	if (!isset($_VARS['lon'])) $_VARS['lon'] = "";
	if (!isset($_VARS['keyword'])) $_VARS['keyword'] = "";
	if (!isset($_VARS['filter'])) $_VARS['filter'] = "";
	if (!isset($_VARS['loc'])) $_VARS['loc'] = "";
	// add 2011/07/05 Y.Nakajima ]
	if (!isset($_VARS['start'])) $_VARS['start'] = "";		// add 2012/07/27 Y.Matsukawa

	//ログ内容
	$prm  = sprintf("%s %s %s %s %s "
					,$status
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['kid']), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['lat']), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['lon']), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['keyword']), 0, 128, '...')
	);
	//$prm .= sprintf("%s %s "		mod 2012/07/27 Y.Matsukawa
	$prm .= sprintf("%s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['filter']), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['loc']), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS['start']), 0, 128, '...')		// add 2012/07/27 Y.Matsukawa
	);
	$prm = str_replace("\n","",$prm);
	$prm = str_replace("\r","",$prm);
	
	// ログ出力
	$log_smt->info($prm);

	include_once('/home/emap/src/log/inc/com_log_close.inc');
}

// ------------------------------------------------------------
// 拠点データ取得
// ------------------------------------------------------------
//function ZdcSearchCgiKyotenid($kid, $type = 5, $putLog = true){		mod 2014/03/17 Y.Matsukawa
function ZdcSearchCgiKyotenid($kid, $type = 5, $putLog = true, $jkn=''){
	global $cid,$D_CID,$D_SSAPI,$D_SSAPI_KEY,$D_MOBILE_URL,$D_QRIMG_URL,$D_QRIMG_E,$D_QRIMG_V,$D_QRIMG_S,$D_KYO_COL_NAME,$D_SOCKET_TIMEOUT;
	global $P_FREEPARAMS_SJIS, $D_FREEPARAMS_TO_MBURL;
	global $D_DATA_CID, $D_ICON_CID;		// add 2012/01/19 N.Wada
	global $D_ICONID_COL, $D_ICON;		// add 2012/04/16 Y.Matsukawa
	global $D_ORG_KBN_COL, $D_ORG_KBN_NAME_LIST;		// add 2012/04/16 Y.Matsukawa
	global $D_KYOTENID_CUST;		// add 2012/11/15 Y.Matsukawa
	global $D_CUST_CNV_FLG;		// add 2013/07/18 Y.Matsukawa
	global $D_KYOTEN_IMG_DEF;		// add 2013/07/12 T.Sasaki
	// 2014/03/12 Y.Matsukawa [
	global $D_YTC_TIMESUMM, $D_YTC_24_LBL, $D_YTC_ALL_TITLE;
	global $D_YTC_WD_LBL, $D_YTC_TIMECOL_WD_FR, $D_YTC_TIMECOL_WD_TO;
	global $D_YTC_OT_LBL, $D_YTC_TIMECOL_OT_FR, $D_YTC_TIMECOL_OT_TO;
	global $D_YTC_HLDYCOL_DAY_LBL, $D_YTC_HLDYCOL_OTH_LBL;
	global $D_YTC_WKDYCOL_DAY_LBL;		// add 2015/12/08 Y.Uesugi
	global $D_STR_DIFF_COLS;
	global $D_COL_VAL_CHK;
	global $D_COL_VAL_CHK_POS;		// add 2015/10/28 Y.Uesugi
	global $D_CUST_CNV_FLG;
	// 2014/03/12 Y.Matsukawa ]
	global $D_KYOTEN_ITEM_ZIP;			// add 2015/11/16 Y.Uesugi
	global $D_FLAGS_ANY_ON, $D_KYOTEN_ITEM_TIME;		// add 2016/12/19 N.Wada
	global $D_COLUMNS_ANY_VALUE;			// add 2016/12/19 N.Wada
	global $D_COLUMNS_ANY_MATCH_VALUE;		// add 2016/12/19 N.Wada
	global $D_FLAGS_ALL_ON;			// add 2016/12/19 N.Wada
	global $D_TIME_COMP_COLS;		// add 2016/12/19 N.Wada
	global $D_KYOTEN_ITEM_TEL_ATAG;		// add 2016/12/19 N.Wada
	global $D_KYOTEN_WGS_COL;		// add 2017/01/25 N.Wada
	global $D_PC2_URL;		// add 2017/02/09 N.Wada

	//CGIへアクセス
	if ($putLog) {
		$cgi = $D_SSAPI["kyotenid"];
	} else {
		$cgi = $D_SSAPI["kyotenid_nolog"];
	}
	//$url = sprintf("%s?key=%s&cid=%s&opt=%s&kid=%s&type=%s",$cgi,$D_SSAPI_KEY,$D_CID,$cid,$kid,$type);		mod 2012/01/19 N.Wada
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&kid=%s&type=%s", $cgi, $D_SSAPI_KEY, $D_DATA_CID, $cid, $kid, $type);
	if (isset($D_KYOTENID_CUST) && $D_KYOTENID_CUST) $url .= '&cust='.$D_KYOTENID_CUST;		// add 2012/11/15 Y.Matsukawa
	$url .= '&mltimg=1';	// 拠点（複数）画像取得オプション	2013/07/12 T.Sasaki
	if ($jkn) $url .= '&jkn='.urlencode($jkn);		// add 2014/03/17 Y.Matsukawa

	$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
	//戻り値の解釈
	$cnt = count($dat);
	if($cnt < 2) return false;//エラー
	$rec = ZdcConvertEncoding($dat[1]);
	$rec = explode("\t",$rec);
	//値の作成
	$tpl["kid"]  = $kid;
	$tpl["lat"]  = $rec[0];
	$tpl["lon"]  = $rec[1];
	// add 2015/03/25 Y.Matsukawa [
	// 日本測地系（10進）
	$tpl['lat_dec'] = cnv_dms2hour($rec[0]);
	$tpl['lon_dec'] = cnv_dms2hour($rec[1]);
	// 世界測地系（ミリ秒）
	if (cnv_transDatum($rec[0], $rec[1], TKY_TO_WGS84, &$lat_wgs, &$lon_wgs)) {
		$tpl['lat_wgs'] = $lat_wgs;
		$tpl['lon_wgs'] = $lon_wgs;
		// 世界測地系（10進）
		$tpl['lat_wgs_dec'] = cnv_dms2hour($lat_wgs);
		$tpl['lon_wgs_dec'] = cnv_dms2hour($lon_wgs);
		// add 2015/03/25 Y.Matsukawa ]
	}
	$tpl["icon"] = $rec[2];
	$tpl["icon_".$rec[2]] = 1;		// add 2012/11/15 Y.Matsukawa
	// add 2016/03/14 Y.Matsukawa [
	//---------------------------------------------
	// アイコンIDの値判定(比較位置指定)
	// （例）$D_COL_VAL_CHK_POS['icon'][] = array('000', 'A', 0, 3);
	//  → アイコンID='000123'
	//     スタート位置：0文字目
	//     比較終了位置：3文字（文字数）
	//   ならば、{def list/icon_EQP_A}が真になる
	//---------------------------------------------
	if (isset($D_COL_VAL_CHK_POS['icon']) && is_array($D_COL_VAL_CHK_POS['icon'])) {
		foreach ($D_COL_VAL_CHK_POS['icon'] as $cvc) {
			$cvc_val = $cvc[0];
			$cvc_lbl = $cvc[1];
			$kid_val = substr($tpl["icon"], $cvc[2], $cvc[3]);
			if ($cvc_val == $kid_val) {
				$tpl['icon_EQP_'.$cvc_lbl] = 1;
			}
		}
	}
	// add 2016/03/14 Y.Matsukawa ]
	if(intval($rec[3])) $tpl["gifflg"]= "1";
	if(intval($rec[4])) $tpl["new"] = "1";

	// add 2014/03/12 Y.Matsukawa [
	//---------------------------------------------
	// 任意カラムの値判定
	// （例）$D_COL_VAL_CHK['kid'][] = array('0001', 'A');
	//  → 拠点ID='0001' ならば、{def list/kid_EQ_A}が真になる
	//---------------------------------------------
	if (isset($D_COL_VAL_CHK['kid']) && is_array($D_COL_VAL_CHK['kid'])) {
		foreach ($D_COL_VAL_CHK['kid'] as $cvc) {
			$cvc_val = $cvc[0];
			$cvc_lbl = $cvc[1];
			if ($tpl["kid"] == $cvc_val) {
				$tpl['kid_EQ_'.$cvc_lbl] = 1;
			}
		}
	}
	// add 2014/03/12 Y.Matsukawa ]

	// add 2015/11/30 Y.Uesugi [
	//---------------------------------------------
	// 任意カラムの値判定(比較位置指定)
	// （例）$D_YTC_OKINAWA['kid'][] = array('000', 'A', 0, 3);
	//  → 拠点ID='000123'
	//     スタート位置：0文字目
	//     比較終了位置：3文字（文字数）
	//   ならば、{def list/kid_EQP_A}が真になる
	//---------------------------------------------
	if (isset($D_COL_VAL_CHK_POS['kid']) && is_array($D_COL_VAL_CHK_POS['kid'])) {
		foreach ($D_COL_VAL_CHK_POS['kid'] as $cvc) {
			$cvc_val = $cvc[0];
			$cvc_lbl = $cvc[1];
			$kid_val = substr($tpl["kid"], $cvc[2], $cvc[3]);
			if ($cvc_val == $kid_val) {
				$tpl['kid_EQP_'.$cvc_lbl] = 1;
			}
		}
	}
	// add 2015/11/30 Y.Uesugi ]

	// add 2012/11/15 Y.Matsukawa [
	$kyo_col_count = count($D_KYO_COL_NAME[$type]);
	$last = $kyo_col_count - 1;
	// 拠点縮尺カラム
	$last++;
	$kyo_lvl_col_idx = $last;
	// JCN向けカスタマイズ（満空情報）
	$jcn_stt_col_idx = 0;
	$jcn_avl_col_idx = 0;
	if (isset($D_KYOTENID_CUST) && $D_KYOTENID_CUST == 'JCN') {
		$last++;
		$jcn_stt_col_idx = $last;
		$last++;
		$jcn_avl_col_idx = $last;
	}
	// add 2012/11/15 Y.Matsukawa ]

	// 拠点（複数）画像	add 2013/07/12 Add T.Sasaki
	$last++;
	$multi_img_col_idx = $last;

	// 2014/03/12 Y.Matsukawa [
	$ytc_time_wd = array();
	$ytc_time_oh = array();
	$ytc_hldy_lbl = array();
	$ytc_wkdy_lbl = array();	// add 2015/12/08 Y.Uesugi
	$ytc_hldy_oth_lbl = '';
	// 2014/03/12 Y.Matsukawa ]

	for($i = 0;$i < 202;$i ++) {
		// mod 2011/07/05 Y.Nakajima [
		if (isset($D_KYO_COL_NAME[$type][$i])) {
			$col = $D_KYO_COL_NAME[$type][$i];
		} else {
			$col = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$vnm = strtoupper($col);		// add 2013/07/18 Y.Matsukawa
		// add 2011/07/05 Y.Nakajima [
		if (isset($rec[5+$i])) {
			$d = $rec[5+$i];
		} else {
			$d ="";
		}
		// add 2011/07/05 Y.Nakajima ]
		//---------------------------------------------------------------------
		// 表示項目
		//---------------------------------------------------------------------
		if ($col != '') {
			// mod 2011/07/05 Y.Nakajima
			//$d = $rec[5+$i];
			$tpl[$col] = $d;
			$tpl[$col."_SJIS_ENC"] = urlencode(mb_convert_encoding($d,"SJIS","eucJP-win"));	// add 2012/01/19 N.Wada
			$tpl[$col."_UTF8_ENC"] = urlencode(mb_convert_encoding($d,"UTF-8","eucJP-win"));	// add 2012/08/15 H.Osamoto
			if($d) $tpl[$col."l".$d] = "1";
			// add 2013/07/18 Y.Matsukawa [
			// 特定の値の場合にフラグを立てる
			if (is_array($D_CUST_CNV_FLG[$vnm]) && isset($D_CUST_CNV_FLG[$vnm][$d])) {
				$tpl[$vnm.'_'.$D_CUST_CNV_FLG[$vnm][$d]] = 1;
			}
			// add 2013/07/18 Y.Matsukawa ]
			if(intval($d) == 1) $tpl[$col."b"] = "1";
			if($col == 'name') $tpl['name_enc'] = urlencode($d);
			// add 2012/10/10 H.Osamoto [
			// 別カラムのアイコンIDを使用
			if ($col == $D_ICONID_COL && $d && $D_ICON[$d]) {
				$tpl["icon"] = $d;
			}
			// 専用区分定義を適用
			if ($col == $D_ORG_KBN_COL && $d && $D_ORG_KBN_NAME_LIST[$d]) {
				$tpl[$col."_name"] = $D_ORG_KBN_NAME_LIST[$d];
			}
			// add 2012/10/10 H.Osamoto ]
			// add 2014/03/12 Y.Matsukawa [
			//---------------------------------------------
			// 特定の値の場合にフラグを立てる
			//---------------------------------------------
			if (is_array($D_CUST_CNV_FLG[$vnm]) && isset($D_CUST_CNV_FLG[$vnm][$d])) {
				$tpl[$vnm.'_'.$D_CUST_CNV_FLG[$vnm][$d]] = 1;
			}
			//---------------------------------------------
			// 任意カラムの値判定
			// （例）$D_COL_VAL_CHK['col_01'][] = array('あ', 'A');
			//  → col_01='あ' ならば、{def list/col_01_EQ_A}が真になる
			//---------------------------------------------
			if (isset($D_COL_VAL_CHK[$vnm]) && is_array($D_COL_VAL_CHK[$vnm])) {
				foreach ($D_COL_VAL_CHK[$vnm] as $cvc) {
					$cvc_val = $cvc[0];
					$cvc_lbl = $cvc[1];
					if ($d == $cvc_val) {
						$tpl[$vnm.'_EQ_'.$cvc_lbl] = 1;
					}
					// add 2015/10/08 N.Wada [
					if ($d < $cvc_val) {
						$tpl[$vnm.'_LT_'.$cvc_lbl] = 1;
					}
					if ($d > $cvc_val) {
						$tpl[$vnm.'_GT_'.$cvc_lbl] = 1;
					}
					if ($d <= $cvc_val) {
						$tpl[$vnm.'_LTE_'.$cvc_lbl] = 1;
					}
					if ($d >= $cvc_val) {
						$tpl[$vnm.'_GTE_'.$cvc_lbl] = 1;
					}
					// add 2015/10/08 N.Wada ]
				}
			}
			// add 2016/12/19 N.Wada
			//---------------------------------------------
			// 時刻書式
			//---------------------------------------------
			if (isset($D_KYOTEN_ITEM_TIME[$vnm]) && $D_KYOTEN_ITEM_TIME[$vnm]) {
				formatTimeCol($vnm, $d, &$tpl);
			}
			// add 2016/12/19 N.Wada
			//---------------------------------------------
			// 電話番号から-を取り除く（aタグのtel:用）
			//---------------------------------------------
			if (isset($D_KYOTEN_ITEM_TEL_ATAG[$vnm]) && $D_KYOTEN_ITEM_TEL_ATAG[$vnm]) {
				$tpl[$col.'_tel_atag'] = str_replace("-", "", $tpl[$col]);
			}
			// add 2015/11/16 Y.Uesugi [
			//---------------------------------------------
			// 郵便番号を111-0000の形に成型
			//---------------------------------------------
			if (isset($D_KYOTEN_ITEM_ZIP) && $D_KYOTEN_ITEM_ZIP) {
				if (strlen($tpl[$D_KYOTEN_ITEM_ZIP]) == 7 && is_numeric($tpl[$D_KYOTEN_ITEM_ZIP])){
					$tpl[$D_KYOTEN_ITEM_ZIP] = substr($tpl[$D_KYOTEN_ITEM_ZIP], 0, 3).'-'.substr($tpl[$D_KYOTEN_ITEM_ZIP], 3, 4);
				}
			}
			//---------------------------------------------
			// ヤマト運輸向け：営業時間情報をサマリ
			//---------------------------------------------
			if (isset($D_YTC_TIMESUMM) && $D_YTC_TIMESUMM) {
				// 平日（月〜金）
				if (isset($D_YTC_TIMECOL_WD_FR) && isset($D_YTC_TIMECOL_WD_TO)) {
					// 開始時刻
					if (isset($D_YTC_TIMECOL_WD_FR[$vnm])) {
						$ytc_time_wd[$D_YTC_TIMECOL_WD_FR[$vnm]][0] = $d;
					}
					// 終了時刻
					if (isset($D_YTC_TIMECOL_WD_TO[$vnm])) {
						$ytc_time_wd[$D_YTC_TIMECOL_WD_TO[$vnm]][1] = $d;
					}
				}
				// その他（土・日・祝）
				if (isset($D_YTC_TIMECOL_OT_FR) && isset($D_YTC_TIMECOL_OT_TO)) {
					// 開始時刻
					if (isset($D_YTC_TIMECOL_OT_FR[$vnm])) {
						$ytc_time_oh[$D_YTC_TIMECOL_OT_FR[$vnm]][0] = $d;
					}
					// 終了時刻
					if (isset($D_YTC_TIMECOL_OT_TO[$vnm])) {
						$ytc_time_oh[$D_YTC_TIMECOL_OT_TO[$vnm]][1] = $d;
					}
				}
			}
			//---------------------------------------------
			// ヤマト運輸向け：定休日情報をサマリ
			//---------------------------------------------
			// 月〜祝
			if (isset($D_YTC_HLDYCOL_DAY_LBL)) {
				if (isset($D_YTC_HLDYCOL_DAY_LBL[$vnm]) && $d == '1') {
					$ytc_hldy_lbl[] = $D_YTC_HLDYCOL_DAY_LBL[$vnm];
				}
			}
			// 不定休・年中無休
			if (isset($D_YTC_HLDYCOL_OTH_LBL)) {
				if (isset($D_YTC_HLDYCOL_OTH_LBL[$vnm]) && $d == '1') {
					$ytc_hldy_oth_lbl = $D_YTC_HLDYCOL_OTH_LBL[$vnm];
				}
			}
			// add 2014/03/12 Y.Matsukawa ]
			// add 2015/12/08 Y.Uesugi [
			//---------------------------------------------
			// ヤマト運輸向け：平日営業日情報をサマリ
			//---------------------------------------------
			// 月〜金
			if (isset($D_YTC_WKDYCOL_DAY_LBL)) {
				if (isset($D_YTC_WKDYCOL_DAY_LBL[$vnm]) && $d != '1') {
					$ytc_wkdy_lbl[] = $D_YTC_WKDYCOL_DAY_LBL[$vnm];
				}
			}
			// add 2015/12/08 Y.Uesugi ]

		//---------------------------------------------------------------------
		// 拠点縮尺
		//---------------------------------------------------------------------
		//} else {		mod 2012/11/15 Y.Matsukawa
		} else if ($kyo_lvl_col_idx > 0 && $kyo_lvl_col_idx == $i) {
			// mod 2011/07/05 Y.Nakajima
			//$d = $rec[5+$i];
			//if (ctype_digit($d) && 1 <= $d && $d <= 18) {		mod 2011/08/26 Y.Matsukawa
			// mod 2015/05/22 H.Osamoto [
			if (preg_match('/^@@KYOTEN_LEVEL@@:/', $d)) {
				$wk_lvl = explode(":", $d);
				$d = $wk_lvl[1];
			// mod 2015/05/22 H.Osamoto ]
				if (ctype_digit($d) && 1 <= $d && $d <= 15) {
					$tpl['kyoten_lvl'] = $d;
					// mod 2011/07/05 Y.Nakajima
					if(isset($d) && $d) $tpl['kyoten_lvl'.$d] = "1";
				}
			// mod 2015/05/22 H.Osamoto [
			}
			// mod 2015/05/22 H.Osamoto ]
			//break;		del 2012/11/15 Y.Matsukawa
		// add 2012/11/15 Y.Matsukawa [
		// JCN向けカスタマイズ（満空情報）満空状態
		} else if ($jcn_stt_col_idx > 0 && $jcn_stt_col_idx == $i) {
			if ($d != '') {
				$tpl['JCN_SPOT_STATUS'] = $d;
			}
		// JCN向けカスタマイズ（満空情報）利用可能台数
		} else if ($jcn_avl_col_idx > 0 && $jcn_avl_col_idx == $i) {
			if ($d != '') {
				$tpl['JCN_SPOT_AVL_COUNT'] = $d;
			}
		// add 2012/11/15 Y.Matsukawa ]
		// 拠点（複数）画像	add 2013/07/12 Add T.Sasaki
		} else if ($multi_img_col_idx > 0 && $multi_img_col_idx == $i) {
			if ($d != '') {
				$arr_mlt_img_no = explode(",", $d);
				if ( is_array( $arr_mlt_img_no ) && count( $arr_mlt_img_no ) ) {
					foreach ( $arr_mlt_img_no as $mlt_img_no) {
						// mlt_img_noからsetting.incの画像名を取得する
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
						$tpl["mltimg$mlt_img_no"] = sprintf("%s?cid=%s&kid=%s&no=%s", $D_SSAPI["img_select"], $D_DATA_CID , $kid , $mlt_img_no );
						$tpl["mltname$mlt_img_no"] = $mlt_img_name;
					}
				}
			}
		}
	}
	
	// add 2017/01/25 N.Wada [
	// 世界測地系カラムが用意されている場合、世界測地系の緯度経度をそのカラムで上書き
	if ($D_KYOTEN_WGS_COL) {
		$wgslat_col = strtolower($D_KYOTEN_WGS_COL['LAT']);
		$wgslon_col = strtolower($D_KYOTEN_WGS_COL['LON']);
		$tpl['lat_wgs'] = $tpl[$wgslat_col];
		$tpl['lon_wgs'] = $tpl[$wgslon_col];
		// 世界測地系（10進）
		$tpl['lat_wgs_dec'] = cnv_dms2hour($tpl[$wgslat_col]);
		$tpl['lon_wgs_dec'] = cnv_dms2hour($tpl[$wgslon_col]);
	}
	// add 2017/01/25 N.Wada ]

	// add 2015/09/25 H.Yasunaga[
	// 公開開始日時・公開終了日時・NEW表示開始日時・NEW表示終了日時を$tplに含める
	$tpl['PUB_S_DATE'] = $rec[count($rec)-4];
	$tpl['PUB_E_DATE'] = $rec[count($rec)-3];
	$tpl['DISP_NEW_S_DATE'] = $rec[count($rec)-2];
	$tpl['DISP_NEW_E_DATE'] = $rec[count($rec)-1];
	// add 2015/09/25 H.Yasunaga]

	// add 2014/03/12 Y.Matsukawa [
	//---------------------------------------------
	// 任意カラム同士の一致判定
	//---------------------------------------------
	if (isset($D_STR_DIFF_COLS)) {
		$col1 = $D_STR_DIFF_COLS[0];
		$col2 = $D_STR_DIFF_COLS[1];
		if ($tpl[$col1] == $tpl[$col2]) {
			$tpl[$col1.'_EQ_'.$col2] = 1;
		} else {
			$tpl[$col1.'_NEQ_'.$col2] = 1;
		}
	}

	// add 2016/12/19 N.Wada
	//---------------------------------------------
	// 任意カラム（時刻）同士の比較
	//---------------------------------------------
	if (isset($D_TIME_COMP_COLS)) {
		foreach($D_TIME_COMP_COLS as $g => $pair) {
			$col1 = $pair[0];
			$col2 = $pair[1];
			if ($tpl[$col1] == "" || $tpl[$col2] == "") continue;
			$val1 = (int)str_replace(":", "", $tpl[$col1]);
			$val2 = (int)str_replace(":", "", $tpl[$col2]);
			if ($val1 == $val2) {
				$tpl[$col1.'_EQ_'.$col2.'_TIME'] = 1;
			} else {
				$tpl[$col1.'_NEQ_'.$col2.'_TIME'] = 1;
			}
			if ($val1 >= $val2) {
				$tpl[$col1.'_GTE_'.$col2.'_TIME'] = 1;
			} else {
				$tpl[$col1.'_LT_'.$col2.'_TIME'] = 1;
			}
			if ($val1 <= $val2) {
				$tpl[$col1.'_LTE_'.$col2.'_TIME'] = 1;
			} else {
				$tpl[$col1.'_GT_'.$col2.'_TIME'] = 1;
			}
		}
	}

	// add 2016/12/19 N.Wada
	//---------------------------------------------
	// フラグ項目グループ判定（どれか１つ以上ON）
	//---------------------------------------------
	if (isset($D_FLAGS_ANY_ON)) {
		foreach($D_FLAGS_ANY_ON as $g => $flags) {
			foreach ($flags as $c) {
				if ($tpl[$c]) {
					$tpl['FLAGS_'.$g.'_ANY_ON'] = 1;
					break;
				}
			}
		}
	}

	// add 2016/12/19 N.Wada
	//---------------------------------------------
	// フラグ項目グループ判定（すべてON）
	//---------------------------------------------
	if (isset($D_FLAGS_ALL_ON)) {
		foreach($D_FLAGS_ALL_ON as $g => $flags) {
			$flag_on_cnt = 0;
			foreach ($flags as $c) {
				if ($tpl[$c]) {
					$flag_on_cnt++;
				}
			}
			if ($flag_on_cnt && count($flags) == $flag_on_cnt) {
				$tpl['FLAGS_'.$g.'_ALL_ON'] = 1;
			}
		}
	}

	// add 2016/09/20 N.Wada
	//---------------------------------------------
	// 値グループ判定（どれか１つ以上値がある）
	//---------------------------------------------
	if (isset($D_COLUMNS_ANY_VALUE)) {
		foreach($D_COLUMNS_ANY_VALUE as $g => $flags) {
			foreach ($flags as $c) {
				if ($tpl[$c] != "") {
					$tpl['COLUMNS_'.$g.'_ANY_VALUE'] = 1;
					break;
				}
			}
		}
	}

	// add 2016/09/26 N.Wada
	//---------------------------------------------
	// 値グループ判定（どれか１つ以上、任意の値と一致する）
	//---------------------------------------------
	if (isset($D_COLUMNS_ANY_MATCH_VALUE)) {
		foreach($D_COLUMNS_ANY_MATCH_VALUE as $g => $cols) {
			foreach ($cols as $c => $v) {
				if ($tpl[$c] == $v) {
					$tpl['COLUMNS_'.$g.'_ANY_MATCH_VALUE'] = 1;
					break;
				}
			}
		}
	}

	//---------------------------------------------
	// ヤマト運輸向け：営業時間情報をサマリ
	//---------------------------------------------
	if (isset($D_YTC_TIMESUMM) && $D_YTC_TIMESUMM) {
		$sum_time_str = array();
		// 平日（月〜金）サマリ
		if (count($ytc_time_wd)) {
			$wd_time_str = '';
			foreach ($ytc_time_wd as $wd=>$tm) {
				if ($tm[0] != '' && $tm[1] != '') {
					$tm[0] = substr($tm[0], 0, 2).':'.substr($tm[0], 2, 2);
					$tm[1] = substr($tm[1], 0, 2).':'.substr($tm[1], 2, 2);
					if ($tm[0] == '00:00' && $tm[1] == '24:00') {
						$time_str = $D_YTC_24_LBL;
					} else {
						$time_str = $tm[0].'　〜　'.$tm[1];
					}
					$sum_time_str[$time_str][] = $D_YTC_WD_LBL[$wd];
					if ($wd_time_str == '') $wd_time_str = $time_str;
					if ($wd_time_str != $time_str) {
						$wd_time_str = 'UNMATCH';
					}
				}
			}
			if ($wd_time_str != '' && $wd_time_str != 'UNMATCH') {
				// 平日（月〜金）が全て同じなら１つにまとめる
				$sum_time_str = array();// 曜日をセットしたものは消す
				$sum_time_str[$wd_time_str][] = '平日';
			}
		}
		// その他（土・日・祝）サマリ
		if (count($ytc_time_oh)) {
			foreach ($ytc_time_oh as $oh=>$tm) {
				if ($tm[0] != '' && $tm[1] != '') {
					$tm[0] = substr($tm[0], 0, 2).':'.substr($tm[0], 2, 2);
					$tm[1] = substr($tm[1], 0, 2).':'.substr($tm[1], 2, 2);
					if ($tm[0] == '00:00' && $tm[1] == '24:00') {
						$time_str = $D_YTC_24_LBL;
					} else {
						$time_str = $tm[0].'　〜　'.$tm[1];
					}
					$sum_time_str[$time_str][] = $D_YTC_OT_LBL[$oh];
				}
			}
		}
		// サマリ結果をテンプレートにセット
		if (count($sum_time_str)) {
			$tpl["rowspan"] = count($sum_time_str) + 1;
			$tt = 0;
			foreach ($sum_time_str as $time_val => $arr_time_ttl) {
				if (count($sum_time_str) == 1) {
					$tpl["timelist"][$tt]["title"] = $D_YTC_ALL_TITLE;//全日
				} else {
					$tpl["timelist"][$tt]["title"] = implode('・', $arr_time_ttl);
				}
				$tpl["timelist"][$tt]["value"] = $time_val;
				if ($tt == 0) $tpl["timelist"][$tt]["row1"] = 1;
				$tt++;
			}
		}
	}
	//---------------------------------------------
	// ヤマト運輸向け：定休日情報をサマリ
	//---------------------------------------------
	// 月〜祝
	if ($ytc_hldy_oth_lbl != '') {
		$tpl["hldy"] = $ytc_hldy_oth_lbl;
	} else if (count($ytc_hldy_lbl)) {
		$tpl["hldy"] = implode('・', $ytc_hldy_lbl);
	}
	// add 2014/03/12 Y.Matsukawa ]
	// add 2015/12/08 Y.Uesugi [
	//---------------------------------------------
	// ヤマト運輸向け：平日営業日情報をサマリ
	//---------------------------------------------
	// 月〜金
	if (count($ytc_wkdy_lbl)) {
		if (count($ytc_wkdy_lbl) != count($D_YTC_WKDYCOL_DAY_LBL)) {
			// 平日定休日が存在する場合のみ設定
			$tpl["wkdy"] = implode('・', $ytc_wkdy_lbl);
		}
	}
	// add 2015/12/08 Y.Uesugi ]

	if (isset($D_ICON[$tpl["icon"]])) {		// add 2012/11/15 Y.Matsukawa
		//$tpl["iconimg"]   = sprintf("%s?cid=%s&icon_id=%s",$D_SSAPI["icon_select_g"],$D_CID,$tpl["icon"]);		mod 2012/01/19 N.Wada
		$tpl["iconimg"]   = sprintf("%s?cid=%s&icon_id=%s", $D_SSAPI["icon_select_g"], $D_ICON_CID, $tpl["icon"]);
	// add 2012/11/15 Y.Matsukawa [
	} else {
		$tpl["iconimg"] = $D_ICON["@TP"]["IMG"];
	}
	// add 2012/11/15 Y.Matsukawa ]
	//$tpl["gifimg"]    = sprintf("%s?cid=%s&kid=%s",$D_SSAPI["gif_select"],$D_CID,$kid);		mod 2012/01/19 N.Wada
	$tpl["gifimg"]    = sprintf("%s?cid=%s&kid=%s", $D_SSAPI["gif_select"], $D_DATA_CID, $kid);
	$tpl["mobileurl"] = sprintf("%s?kid=%s&",$D_MOBILE_URL,$kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobileurl"] .= "&".$P_FREEPARAMS_SJIS;
	$tpl["mobileurl_encode"] = urlencode($tpl["mobileurl"]);
	$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode(urlencode($tpl["mobileurl"])));
	$tpl["mobiledtlurl"] = sprintf("%s?ksid=%s",$D_MOBILE_URL,$kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobiledtlurl"] .= "&".$P_FREEPARAMS_SJIS;
	$tpl["mobiledtlurl_encode"] = urlencode($tpl["mobiledtlurl"]);
	// add 2017/02/09 N.Wada [
	$tpl["pcdtlurl"] = sprintf("%sdtl/%s/",$D_PC2_URL,$kid);
	$tpl["pcdtlurl_encode"] = urlencode($tpl["pcdtlurl"]);
	// add 2017/02/09 N.Wada ]
	$tpl["qrimgdtlurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode(urlencode($tpl["mobiledtlurl"])));
	//$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["icon_select_g"],$D_CID);		mod 2012/01/19 N.Wada
	$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI["icon_select_g"], $D_ICON_CID);
	//$tpl["_cgiSysIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["sys_icon_select"],$D_CID);		mod 2012/01/19 N.Wada
	$tpl["_cgiSysIconimg"] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI["sys_icon_select"], $D_DATA_CID);
	//$tpl["_cgiGifimg"]  = sprintf("%s?cid=%s&kid=",$D_SSAPI["gif_select"],$D_CID);		mod 2012/01/19 N.Wada
	$tpl["_cgiGifimg"]  = sprintf("%s?cid=%s&kid=", $D_SSAPI["gif_select"], $D_DATA_CID);
	$tpl["_jsMsg"]    = sprintf("ZdcEmapShopMsg(null)",$kid);
	$tpl["_jsMove"]   = sprintf("ZdcEmapMapMove('%s','%s')",$rec[0],$rec[1]);
	$tpl["_jsScroll"] = sprintf("ZdcEmapMapScroll('%s','%s')",$rec[0],$rec[1]);
	// add 2011/07/05 Y.Nakajima 
	if (!isset($tpl['new'])) $tpl['new'] = "";
	if (!isset($tpl['kyoten_lvl'])) $tpl['kyoten_lvl'] = "";
	// add 2011/07/05 Y.Nakajima ]
	$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s','%s');",$kid,$rec[0],$rec[1],$rec[2],$tpl["new"],$tpl['kyoten_lvl']);
	$tpl["_jsNeki"]   = sprintf("ZdcEmapStationClick('%s','%s')",$rec[0],$rec[1]);
	$tpl["_jsFreeRoute"] = sprintf("ZdcEmapFreeRouteClick('%s','%s')",$rec[0],$rec[1]);
	$tpl["_jsFreeRouteLight"] = sprintf("ZdcEmapFreeRouteClickLight('%s','%s')",$rec[0],$rec[1]);
	$tpl["_jsPrint"]  = sprintf("ZdcEmapShopPrintClick('%s')",$kid);
	$tpl["_urlPrint"] = sprintf("./print.htm?cid=%s&kid=%s",$cid,$kid);
	$tpl["_jsSearch"] = "ZdcEmapSearchNpoi()";
	$tpl["_jsDetailNpoi"]   = "ZdcEmapShopDetailNpoiClick()";
	
	return $tpl;
}

// add 2014/05/29 Y.Matsukawa
// ------------------------------------------------------------
// 商品マスタデータ取得
// ------------------------------------------------------------
function ZdcPrdSelect($pid) {
	global $cid, $D_CID, $D_DATA_CID, $D_SSAPI, $D_SSAPI_KEY, $D_SOCKET_TIMEOUT;

	$cgi = $D_SSAPI['prd_select'];
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&pid=%s", $cgi, $D_SSAPI_KEY, $D_DATA_CID, $cid, $pid);
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$cnt = count($dat);
	if($cnt < 2) return false;//エラー
	$rec = ZdcConvertEncoding($dat[1]);
	$rec = explode("\t", $rec);

	$tpl['prd_id']  = $pid;
	$tpl['prd_name']  = $rec[1];
	$tpl['prd_name_HTML'] = htmlspecialchars($rec[1]);
	$tpl['prd_name_URL'] = urlencode($rec[1]);
	$tpl['prd_name_SJIS_URL'] = urlencode(mb_convert_encoding($rec[1], 'SJIS', 'EUC'));
	$tpl['prd_name_UTF8_URL'] = urlencode(mb_convert_encoding($rec[1], 'UTF-8', 'EUC'));

	return $tpl;
}

// add 2013/07/10 Y.Matsukawa
// ------------------------------------------------------------
// ヤマト運輸 営業所検索（サービスセンター情報取得）
// ------------------------------------------------------------
function YTCGetJigyoCd($kid) {
	global $D_YTC_API_URL;
	global $D_APIPROXY;

	$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];

	$url = $D_YTC_API_URL['JGCD'];
	$url = str_replace('@@KYOTEN_ID@@', $kid, $url);
	$dat = ZdcHttpSimpleRead($url, $host);
	if ($dat && is_array($dat)) {
		$xml_arr = LoadXML(&$dat[0]);
		$Header = GetXMLNode($xml_arr, "Header");
		if (!$Header) return null;
		$ErrorCd = GetXMLVal($Header, "ErrorCd");
		if ($ErrorCd == '000000') {
			$Jigyosho_Info = GetXMLNode($xml_arr, "Jigyosho_Info");
			if (!$Jigyosho_Info) return null;
			$jigyo = array();
			foreach ($Jigyosho_Info as $node) {
				if ($node["type"] == "complete") {
					$jigyo['YTC_'.$node["tag"]] = $node["value"];
				}
			}
			return $jigyo;
		} else {
			erl('YTC API ERROR['.$ErrorCd.']['.$url.']');
		}
	}
	return null;
}

// add 2015/12/22 Y.Uesugi [
// ------------------------------------------------------------
// ヤマト運輸 営業所検索（祝日情報取得）
// ------------------------------------------------------------
function YTCGetHoliday() {
	global $D_SSAPI;

	$y_cgi = $D_SSAPI["ytc_get_holiday"];
	$y_dat = ZdcHttpRead($y_cgi, 0, $D_SOCKET_TIMEOUT);
	$weekNo = $y_dat[1];

	if (isset($weekNo) && $weekNo) {
		return $weekNo;
	}
	return null;
}
// add 2015/12/22 Y.Uesugi ]

// add 2012/02/23 Y.Matsukawa
// ------------------------------------------------------------
// 日時項目分割
// ------------------------------------------------------------
function splitDateTimeCol($col_name, $value, &$arr_val) {
	$YOUBI[0] = '日';
	$YOUBI[1] = '月';
	$YOUBI[2] = '火';
	$YOUBI[3] = '水';
	$YOUBI[4] = '木';
	$YOUBI[5] = '金';
	$YOUBI[6] = '土';

	$yyyy = substr($value, 0, 4);
	if ($yyyy != '' && is_numeric($yyyy)) {
		$arr_val[$col_name."_YYYY"] = $yyyy;
	}
	$mm = substr($value, 4, 2);
	if ($mm != '' && is_numeric($mm)) {
		$arr_val[$col_name."_MM"] = $mm;
		$arr_val[$col_name."_M"] = intval($mm);
	}
	$dd = substr($value, 6, 2);
	if ($dd != '' && is_numeric($dd)) {
		$arr_val[$col_name."_DD"] = $dd;
		$arr_val[$col_name."_D"] = intval($dd);
	}
	if ($yyyy != '' && is_numeric($yyyy) && $mm != '' && is_numeric($mm) && $dd != '' && is_numeric($dd)) {
		$tm = mktime(0, 0, 0, $mm, $dd, $yyyy);
		if ($tm) {
			$arr_val[$col_name."_DW"] = date('w', $tm);
			$arr_val[$col_name."_DWJP"] = $YOUBI[$arr_val[$col_name."_DW"]];
		}
	}
	$hh = substr($value, 8, 2);
	if ($hh != '' && is_numeric($hh)) {
		$arr_val[$col_name."_HH"] = $hh;
		$arr_val[$col_name."_H"] = intval($hh);
	}
	$nn = substr($value, 10, 2);
	if ($nn != '' && is_numeric($nn)) {
		$arr_val[$col_name."_NN"] = $nn;
		$arr_val[$col_name."_N"] = intval($nn);
	}
}

// add 2016/12/19 N.Wada
// ------------------------------------------------------------
// 日時項目分割
// ------------------------------------------------------------
function formatTimeCol($col_name, $value, &$arr_val) {
	if ($value == '') return '';
	list($h, $n, $s) = explode(':', $value);
	$arr_val[$col_name.'_TIME'] = intval($h).':'.$n;
}

// ------------------------------------------------------------
// デバッグ情報出力
// ------------------------------------------------------------
function dbl($str){
	global $debug;
	if(!$debug){ return; }
	@error_log(date('Y/m/d H:i:s').'['.$_SERVER['SCRIPT_NAME'].']'.$str."\n", 3, '/var/tmp/smt_debug_'.date('Ymd').'.log');
}
// ------------------------------------------------------------
// エラーログ情報出力
// ------------------------------------------------------------
function erl($str){
	@error_log(date('Y/m/d H:i:s').'['.$_SERVER['SCRIPT_NAME'].']'.$str."\n", 3, '/var/tmp/smt_error_'.date('Ymd').'.log');
}

// add 2012/03/04 K.Masuda [
// ------------------------------------------------------------
// フリーワード検索文字化け対応（八幡など）
// ------------------------------------------------------------
function unescape($source, $iconv_to = 'UTF-8') {
	$decodedStr = '';
	$pos = 0;
	$len = strlen ($source);
	while ($pos < $len) {
		$charAt = substr ($source, $pos, 1);
		if ($charAt == '%') {
			$pos++;
			$charAt = substr ($source, $pos, 1);
			if ($charAt == 'u') {
				$pos++;
				$unicodeHexVal = substr ($source, $pos, 4);
				$unicode = hexdec ($unicodeHexVal);
				$decodedStr .= code2utf($unicode);
				$pos += 4;
			} else {
				$hexVal = substr ($source, $pos, 2);
				$decodedStr .= chr (hexdec ($hexVal));
				$pos += 2;
			}
		} else {
			$decodedStr .= $charAt;
			$pos++;
		}
	}
	if ($iconv_to != "UTF-8") {
		$decodedStr = iconv("UTF-8", $iconv_to, $decodedStr);
	}
	return $decodedStr;
}
function code2utf($num){
	if($num<128)return chr($num);
	if($num<2048)return chr(($num>>6)+192).chr(($num&63)+128);
	if($num<65536)return chr(($num>>12)+224).chr((($num>>6)&63)+128).chr(($num&63)+128);
	if($num<2097152)return chr(($num>>18)+240).chr((($num>>12)&63)+128).chr((($num>>6)&63)+128) .chr(($num&63)+128);
	return '';
}
// add 2012/03/04 K.Masuda ]

// add 2012/08/03 H.Osamoto
// ------------------------------------------------------------
// HTML表示用変換処理
// ------------------------------------------------------------
function zdcHtmlspecialchars_arr($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/_enc$|_ENC$/', $key)) {
			$obj[$key] = $val;
		} else if (preg_match('/^name$|^addr$/i', $key)) {
			$obj[$key] = zdcHtmlspecialchars_nameaddr($val);
		} else if (preg_match('/^col_[0-9][0-9]+$/i', $key)) {
			$obj[$key] = zdcHtmlspecialchars_col($val);
		} else {
			$obj[$key] = $val;
		}
	}
	
	return $obj;
}

function zdcHtmlspecialchars($target, $col_name) {
	
	if (preg_match('/^NAME$|^ADDR$/i', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr($target);
	} else if (preg_match('/^COL_[0-9][0-9]+$/i', $col_name)) {
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
	
	//$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// 許可タグリスト		mod 2017/01/11 N.Wada
	$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>', '<u>', '</u>', '<font ', '</font>', '<strong>', '</strong>');	// 許可タグリスト
	$arr_rep = array();
	$rep_cnt = 0;
	
	$target;
	
	foreach ($tag_list as $key => $tag) {
		$start = 0;
		$stop = 0;
		while(1) {
			if (strpos($target, '<', $start) === false) break;	// 「<」が存在しない場合は処理しない
			
			// 許可タグチェック
			$start = strpos(strtolower($target), strtolower($tag), $start);
			
			if ($start !== false) {
				// 許可タグが存在する場合
				$stop = strpos(strtolower($target), ">", $start);
				$rep_cnt++;
				
				// 置換対象を一時的に配列に格納
				$arr_rep[$rep_cnt] = substr($target, $start, $stop - $start + 1);
				
				// 変換しない許可タグを一時的に置換
				$target = substr($target, 0, $start) . "@REP" . $rep_cnt . "@" . substr($target, $stop + 1);
				
				// 2013/02/07 H.osamoto mod [
				//	// 開始位置をずらして続きを実行
				//	$start = $stop;
				// 都度リセットして再実行
				$start = 0;
				// 2013/02/07 H.osamoto mod ]
			} else {
				// 許可タグが存在しない場合
				// 次のタグチェック
				break;
			}
		}
	}
	
	$target = htmlreplace($target);
	
	// 変換しておいた許可タグを元に戻す
	for ($i = 1; $i <= $rep_cnt; $i++) {
		$target = str_replace("@REP".$i."@", $arr_rep[$i], $target);
	}
	
	return $target;
}

function htmlreplace($target) {
	// HTML表示用に置換
	$search  = array('&', '"', '\'', '\\', '<', '>');	// 置換対象
	$replace = array('&amp;', '&quot;', '&#039;', '&yen;', '&lt;', '&gt;');	// 置換後文字列
	
	$target = str_replace($search, $replace, $target);
	
	return $target;
}

// add 2015/12/18 F.Yokoi [
function zdcHtmlspecialchars_arr_raw($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/_enc$|_ENC$/', $key)) {

		} else if (preg_match('/^name$|^addr$/i', $key)) {
			$obj[$key."_raw"] = zdcHtmlspecialchars_nameaddr_raw($val);
		} else if (preg_match('/^col_[0-9][0-9]+$/i', $key)) {
			$obj[$key."_raw"] = zdcHtmlspecialchars_col_raw($val);
		} else {

		}
	}
	
	return $obj;
}

function zdcHtmlspecialchars_raw($target, $col_name) {
	
	if (preg_match('/^NAME$|^ADDR$/i', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr_raw($target);
	} else if (preg_match('/^COL_[0-9][0-9]+$/i', $col_name)) {
		$ret = zdcHtmlspecialchars_col_raw($target);
	} else {
		$ret = $target;
	}
	
	return $ret;
}

function zdcHtmlspecialchars_nameaddr_raw($target) {
	
	$ret = htmlreplace_raw($target);
	
	return $ret;
}

function zdcHtmlspecialchars_col_raw($target) {
	
	//$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// 許可タグリスト		mod 2017/01/11 N.Wada
	$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>', '<u>', '</u>', '<font ', '</font>', '<strong>', '</strong>');	// 許可タグリスト
	$arr_rep = array();
	$rep_cnt = 0;
	
	$target;
	
	foreach ($tag_list as $key => $tag) {
		$start = 0;
		$stop = 0;
		while(1) {
			if (strpos($target, '<', $start) === false) break;	// 「<」が存在しない場合は処理しない
			
			// 許可タグチェック
			$start = strpos(strtolower($target), strtolower($tag), $start);
			
			if ($start !== false) {
				// 許可タグが存在する場合
				$stop = strpos(strtolower($target), ">", $start);
				$rep_cnt++;
				
				// 置換対象を一時的に配列に格納
				$arr_rep[$rep_cnt] = substr($target, $start, $stop - $start + 1);
				
				// 変換しない許可タグを一時的に置換
				$target = substr($target, 0, $start) . "@REP" . $rep_cnt . "@" . substr($target, $stop + 1);
				
				//	// 開始位置をずらして続きを実行
				//	$start = $stop;
				// 都度リセットして再実行
				$start = 0;
			} else {
				// 許可タグが存在しない場合
				// 次のタグチェック
				break;
			}
		}
	}
	
	$target = htmlreplace_raw($target);
	
	// 変換しておいた許可タグを元に戻す
	for ($i = 1; $i <= $rep_cnt; $i++) {
		$target = str_replace("@REP".$i."@", $arr_rep[$i], $target);
	}
	
	return $target;
}

function htmlreplace_raw($target) {
	// HTML表示用に置換
	$search  = array('"', '\'', '\\', '<', '>');	// 置換対象
	$replace = array('&quot;', '&#039;', '&yen;', '&lt;', '&gt;');	// 置換後文字列
	
	$target = str_replace($search, $replace, $target);
	
	return $target;
}
// add 2015/12/18 F.Yokoi ]

// ------------------------------------------------------------
// 距離表示変換（1000mを超える場合にkm表記に変更）	add 2012/08/03 H.Osamoto
// ------------------------------------------------------------
function cnv_dist($distance) {
	$w_dist = round($distance);
	if ($w_dist < 1000) {
		$ret = $w_dist.'m';
	} else {
		$ret = round($w_dist/1000,2).'km';
	}
	return $ret;
}
// ------------------------------------------------------------
// リアルタイムデータ取得
// ------------------------------------------------------------
function ZdcSearchCgiRd($kid,$rd_grp,$rdtype=null){
	global $cid, $D_CID, $D_SSAPI, $D_SOCKET_TIMEOUT,$D_DATA_CID ;
	require_once('/home/emap/src/Jsphon/Decoder.php');

	//CGIへアクセス
	$cgi = $D_SSAPI["rd_store_id"];
	$url = sprintf("%s?cid=%s&kid=%s&grp=%s&intid=%s", $cgi,  $D_DATA_CID, $kid, $rd_grp,"@EMAPSM@");
//echo $url;
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$tpl ='';
	$i=0;
	//戻り値の解釈
	if ($dat != '') {
		// JSONデコード
		$json = new Jsphon_Decoder();
		$arr_data = $json->decode($dat[0]);
		if (!$arr_data || !is_array($arr_data)) return false;
		if ($arr_data['return_code'] != "y1100000") return false;
		foreach ($arr_data as $key1 => $arr1) {
			foreach ($arr1 as $key2 => $arr2) {
				foreach ($arr2 as $key3 => $arr3) {

							${$key3} =$arr3;
							if($key3 =='store_id'){
								if($rdtype){
									 $tpl[$i]['rd_'.$key3]=${$key3};
								}
							}

					foreach ($arr3 as $key4 => $arr4) {
						foreach ($arr4 as $key5 => $arr5) {
							${$key5} =$arr5;
							if($group_id){
								if($rdtype){
									 $tpl[$i]['rd_'.$group_id]=1;
								}else{
									 $tpl['rd_'.$group_id]=1;
								}
							}
							foreach ($arr5 as $key6 => $arr6) {
								foreach ($arr6 as $key7 => $arr7) {
									${$key7} =str_replace("\n","<br>",mb_convert_encoding($arr7,"EUC-JP","UTF-8"));
//									${$key7} =$arr7;
									if($type == "TEXT"){
										if($key7 == "text"){
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id] = ${$key7};
											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id] = ${$key7};
											}
										}
									}elseif($type == "FLAG"){
										if($key7 == "flag"){
											${$key7}=$arr7;
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id] = ${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id] = ${$key7};
											}	
										}elseif($key7 == "text") {
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};
											}
										}
									}elseif($type == "IMG"){
										if($key7 == "img_url"){
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id] =${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id] =${$key7};
											}
										}elseif($key7 == "img_w" || $key7 == "img_h"){
											if($rdtype){
												$tpl[$i]['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};

											}else{
												$tpl['rd_'.$group_id.'_item_'.$item_id.'_'.$key7] = ${$key7};

											}
										}
									}
								}
							}
						}
					}
				}
				$i=$i+1;
			}
		}
	}
	return $tpl;
}

// add 2014/08/26 AnPham [
// ------------------------------------------------------------
// 保存店舗をCookie読み込み
// 指定がある場合は店舗情報をCGIから取得
// ------------------------------------------------------------
/**
 * Get data from cookie.
 * @param  string $freeparms_enc Custom parameter on the end of link URL
 * @return array                 Shop detail.
 */
function getShopDtlFromCookie( $freeparms_enc) {
	global $D_SSAPI, $D_CID, $D_SSAPI_KEY, $D_SOCKET_TIMEOUT, $D_KYO_COL_NAME, $D_DIR_BASE_G;
	global $D_COOKIE_SHOPDTL_MAX, $D_COOKIE_SHOPDTL_KEY, $D_COOKIE_SHOPDTL_CGI;
	global $D_SHOPDATA_TRIM_WIDTH, $D_SHOPDATA_TRIM_MARKER, $D_SHOPDATA_TRIM_TYPE;		// add 2012/06/21 Y.Matsukawa
	global $D_DATA_CID;		// add 2014/10/27 H.Osamoto
	$shop_dtl = array();
	$shop_id = array();

	// need check.
	$D_COOKIE_SHOPDTL_KEY = "PC_SHOPDTL_{$D_CID}";

	if ($D_COOKIE_SHOPDTL_MAX > 0) {
		if (isset($_COOKIE[$D_COOKIE_SHOPDTL_KEY]) && $_COOKIE[$D_COOKIE_SHOPDTL_KEY] != '') {
			// Cookie保存拠点を取得
			$ckval = explode(',', $_COOKIE[$D_COOKIE_SHOPDTL_KEY]);
			$cnt = floor(count($ckval)/2);
			$cnt = ($cnt<=$D_COOKIE_SHOPDTL_MAX ? $cnt : $D_COOKIE_SHOPDTL_MAX);
			for ($i = 0; $i < $cnt; $i++) {
				$shop_dtl_no[$ckval[$i*2]] = $i;
				$shop_dtl[$i] = array('kyoten_id'=>$ckval[$i*2], 'name'=>urldecode($ckval[$i*2+1]));
				$shop_dtl[$i]['_urlDetail'] = $D_DIR_BASE_G.'inf/'.$ckval[$i*2].'/?'.($freeparms_enc?'&'.$freeparms_enc:'');
				$shop_id[] = $ckval[$i*2];
			}
			// CGIからデータ取得
			if (count($shop_id) && $D_COOKIE_SHOPDTL_CGI > 0) {
				$cgi = $D_SSAPI['kyotenlist'];
				//	$prm = sprintf('&cid=%s&pos=%d&cnt=%d', $D_CID, 1, $D_COOKIE_SHOPDTL_MAX);		mod 2014/10/27 H.Osamoto
				$prm = sprintf('&cid=%s&pos=%d&cnt=%d', $D_DATA_CID, 1, $D_COOKIE_SHOPDTL_MAX);
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
					// var_dump( $kid);die;
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
									// トリミング		add 2012/06/21 Y.Matsukawa
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

/**
 * Set data to cookie
 * @param string $cid    Company ID
 * @param number $kid    Shop ID
 * @param string $knmenc Shop name
 */
function setShopDtlToCookie($cid, $kid, $knmenc) {
	global $D_COOKIE_SHOPDTL_MAX, $D_COOKIE_SHOPDTL_EXPIRE, $D_COOKIE_SHOPDTL_CGI;
	$save_value = '';
	$new_value = "{$kid},{$knmenc}";
	$pc_shopdtl = '';
	$key = "PC_SHOPDTL_{$cid}";
	$_cookie = $_COOKIE;
	if( !empty( $_cookie)) {
		$pc_shopdtl = $_cookie[$key];

		// add new data to the end of cookie
		if( !empty( $pc_shopdtl)) {
			$vals = explode(',', $pc_shopdtl);

			$max = floor ( count( $vals)/2);
			if( $max > $D_COOKIE_SHOPDTL_MAX - 1)
				$max = $D_COOKIE_SHOPDTL_MAX - 1;

			$oc = 0;
			for( $i=0; $i < $max*2; $i++) {
				if ( isset( $vals[$i*2])) {
					if ( empty( $vals[$i*2+1])) $vals[$i*2+1] = '';

					$old_value = $vals[$i*2] . "," . $vals[$i*2+1];
					if ($old_value != $new_value) {
						$save_value .= ",{$old_value}";
						$oc++;
						if ( $oc >= $max) break;
					}
				}
			}
			$D_COOKIE_SHOPDTL_CGI = $oc;// set cgi
		}
	}
	$save_value = $new_value . $save_value;
	$cookie_expire_time = strtotime( "+ {$D_COOKIE_SHOPDTL_EXPIRE} days");
	setcookie( $key, $save_value, $cookie_expire_time, "/;");
}
// add 2014/08/26 AnPham ]
?>
