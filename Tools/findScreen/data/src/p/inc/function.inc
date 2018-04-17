<?PHP
// ------------------------------------------------------------
// 2011/10/15 Y.Matsukawa	新規作成
// 2011/12/05 Y.Matsukawa	別CID参照
// 2012/01/10 Y.Matsukawa	【不具合修正】POSTの場合、遷移履歴のリンクからパラメータが消える
// 2012/01/19 N.Wada		拠点データ取得時に、SJISに変換しかつURLエンコードしたものをセットする
// 2012/03/08 Y.Matsukawa	店舗詳細取得時にcond絞り込みを有効にする
// 2012/04/16 Y.Matsukawa	任意カラムのアイコンIDを使用
// 2012/08/03 H.osamoto		禁則文字緩和対応(「'」「"」「>」「\」「`」（バッククォート）)を許可
// 2012/08/15 H.osamoto		拠点データ取得時に、UTF8に変換しかつURLエンコードしたものをセットする
// 2012/09/19 H.osamoto		専用区分の名称を設定
// 2012/09/26 Y.Matsukawa	【不具合修正】住所フリーワード結果のソートが効いてない
// 2012/11/13 Y.Matsukawa	JCN満空情報取得
// 2012/11/27 Y.Matsukawa	拠点縮尺項目未設定の場合は縮尺設定を採用しない
// 2013/02/07 H.osamoto		禁則文字緩和の不具合対応
// 2013/03/26 H.Iijima		リアルタイムデータ
// 2013/07/19 T.Sasaki		拠点（複数）画像対応
// 2013/07/24 Y.Matsukawa	ヤマト運輸向けカスタマイズ：営業時間・定休日サマリ表示
// 2013/08/07 Y.Matsukawa	任意カラム同士の一致判定
// 2013/08/08 Y.Matsukawa	任意カラムの値判定
// 2013/09/06 Y.Matsukawa	任意のカラムが特定の値の場合にフラグを立てる
// 2013/10/07 Y.Matsukawa	複数画像シーケンス参照
// 2014/05/16 Y.Matsukawa	商品マスタ対応
// 2014/08/29 Q.Dai 		BrowsingHistoryDisplay
// 2014/10/27 H.osamoto		Cookie情報取得時に店舗情報を取得する際の企業IDを修正
// 2014/12/08 Y.Matsukawa	検索位置からのルート表示
// 2014/12/11 Y.Matsukawa	最寄り地図に住所文字列接続した際のパンくずを緯度経度接続に変換したURLにする
// 2015/02/20 H.osamoto		QRコード用PCサイト変数追加
// 2015/03/13 Y.Matsukawa	年月日項目を分割
// 2015/05/22 H.osamoto		拠点縮尺にキーワードを付与し誤作動を防ぐ
// 2015/05/26 H.Osamoto		ヤマト運輸向けカスタマイズ：平日営業日サマリ表示
// 2015/09/25 H.Yasunaga	公開開始日時・公開終了日時・NEW表示開始日時・NEW表示終了日時を$tplに含める
// 2015/10/20 N.Wada		任意カラムの値判定にLT,GT,LTE,GTEを追加
// 2015/10/23 Y.Uesugi		ヤマト運輸 営業所検索（サービスセンター情報取得）
// 2015/10/28 Y.Uesugi		任意カラムの値判定(比較位置指定)
// 2015/11/16 Y.Uesugi		郵便番号の数値7桁にハイフンをつけて「111-0000」の形式にする
// 2015/12/21 Y.Uesugi		ヤマト運輸 営業所検索（祝日情報取得）
// 2015/12/24 F.Yokoi		登録されたHTMLエンティティ文字が正常に表示されるように、別関数を追加する
// 2016/02/05 N.Wada		QRコード用SMTサイト変数追加
// 2016/02/16 F.Yokoi		GoogleMaps連携用に世界測地系の緯度・経度データを追加
// 2016/03/11 Y.Matsukawa	アイコンIDの値判定
// 2016/05/06 N.Wada		QRコード用SMTサイト変数をHTTP,HTTPS両対応版に修正
// 2016/05/13 N.Wada		閲覧履歴（複数）Cookieのキーに任意の文字列を追加
// 2016/06/10 Y.Matsukawa	フラグ項目グループ判定
// 2016/06/10 Y.Matsukawa	時刻書式整形
// 2016/06/10 Y.Matsukawa	別ID接続
// 2016/07/27 Y.Uesugi		SSL許可時のアイコンCGI SSL対応
// 2016/09/20 N.Wada		値グループ判定
// 2016/09/26 N.Wada		値グループ判定（どれか１つ以上、任意の値と一致する）
// 2016/09/30 N.Wada		任意カラム（時刻）同士の比較
// 2016/10/25 N.Wada		フラグ項目グループ判定（フラグ項目すべてON）
// 2017/02/16 N.Wada		拠点の世界測地系の緯度経度を、世界測地系カラムの値で上書き
// 2017/02/22 N.Wada		複合ルート検索結果の整形
// ------------------------------------------------------------
// ------------------------------------------------------------
// HTML出力
// ------------------------------------------------------------
function htmloutput($tplfile, &$tpl) {
	if (!is_file($tplfile)) return;
	$html = @HtmlTemplate::t_buffer($tplfile, $tpl);
	//$html = mb_convert_encoding($html, 'UTF-8', 'EUC-JP');
	echo $html;
}

// ------------------------------------------------------------
// 文字コード変換
// ------------------------------------------------------------
function ZdcConvertEncoding($text) {
	global $enc;
	if($enc) $tmp = $enc;
	//else $tmp = 'UTF-8,EUC-JP,SJIS,auto';		mod 2013/01/21 Y.Matsukawa
	else $tmp = 'UTF-8,eucJP-win,SJIS-win,auto';
	if ($tmp == "EUC" || $tmp == "euc" || $tmp == "EUC-JP") $tmp ="eucJP-win";		// add 2013/01/21 Y.Matsukawa
	//return mb_convert_encoding($text, 'EUC', $tmp);		mod 2013/01/21 Y.Matsukawa
	return mb_convert_encoding($text, 'eucJP-win', $tmp);
}

// ------------------------------------------------------------
// JSリテラル指定用のエスケープ関数
// 「"」→「\"」
// ------------------------------------------------------------
function ZdcEsc4JsLiteral($text) {
	return mb_ereg_replace('"', '\"', $text);
}

// ------------------------------------------------------------
//
// 特殊なHTMLエンティティを文字に戻す
//  htmlspecialchars_decode(PHP5)の代替
//  クォートには非対応
//
// ------------------------------------------------------------
function zdc_htmlspecialchars_decode($text) {
	$ret = $text;
	$ret = str_replace("&amp;", "&", $ret);
	$ret = str_replace("&lt;",  "<", $ret);
	$ret = str_replace("&gt;",  ">", $ret);
	return $ret;
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
			$res = split('[/.]', $ip);
			$w_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			$mask = intval($res[4]);
			$shift = 32 - $mask;
			$res = split('[/.]', $REMOTE_ADDR);
			$r_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			if (($w_ip >> $shift) == ($r_ip >> $shift)) return true;
		}
	}

	return false;
}

// add 2012/09/26 Y.Matsukawa
// ------------------------------------------------------------
//
// 住所フリーワード検索結果ソート関数
//
//
// ------------------------------------------------------------
function GEOAccess_cmp_sflg($a,$b){
	// full比較 1:完全一致が優先
	if( $a["full"] > $b["full"] ) return -1;
	if( $a["full"] < $b["full"] ) return 1;

	// adid文字列長比較
	// adidにはAB等の16進符号が使用されているのでまず文字列長の比較を行う
	if( strlen($a["adid"]) > strlen($b["adid"]) )		return 1;
	if( strlen($a["adid"]) < strlen($b["adid"]) )		return -1;

	// adid内容比較
	// adidを文字列として扱い比較をする為 strcmp を使用して比較
	// 比較結果はそのままreturn
	return strcmp( $a['adid'], $b['adid'] );
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
	
	//絞込み条件の加工
	$cond = '';		// add 2011/12/13 Y.Matsukawa
	for($i = 1;$i <= 200;$i ++) {
		if(isset($_VARS["cond".$i]) && $_VARS["cond".$i]) {
			if($cond) $cond .= ",";
			$cond .= sprintf("cond%d=%s",$i,$_VARS["cond".$i]);
		}
	}
	//128バイトに丸める
	$cond = mb_strimwidth($cond, 0, 128, '...');
	$cond = mb_ereg_replace(' ','_',$cond);
	//ログ内容
	// add 2011/12/13 Y.Matsukawa [
	if (!isset($_VARS["kid"])) $_VARS["kid"] = '';
	if (!isset($_VARS["lat"])) $_VARS["lat"] = '';
	if (!isset($_VARS["lon"])) $_VARS["lon"] = '';
	if (!isset($_VARS["zpoint"])) $_VARS["zpoint"] = '';
	if (!isset($_VARS["type"])) $_VARS["type"] = '';
	if (!isset($_VARS["keyword"])) $_VARS["keyword"] = '';
	if (!isset($_VARS["adcd"])) $_VARS["adcd"] = '';
	if (!isset($_VARS["area"])) $_VARS["area"] = '';
	if (!isset($_VARS["col"])) $_VARS["col"] = '';
	if (!isset($_VARS["nm"])) $_VARS["nm"] = '';
	if (!isset($_VARS["icn"])) $_VARS["icn"] = '';
	if (!isset($_VARS["page"])) $_VARS["page"] = '';
	if (!isset($_VARS["slogflg"])) $_VARS["slogflg"] = '';
	// add 2011/12/13 Y.Matsukawa ]
	$prm  = sprintf("%s %s %s %s %s "
					,$status
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["kid"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["lat"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["lon"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["zpoint"]), 0, 128, '...')
	);
	$prm .= sprintf("%s %s %s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["type"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["keyword"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["adcd"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["area"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["col"]), 0, 128, '...')
	);
	$prm .= sprintf("%s %s %s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["nm"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["icn"]), 0, 128, '...')
					,$cond
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["page"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["slogflg"]), 0, 128, '...')
	);
	$prm = str_replace("\n","",$prm);
	$prm = str_replace("\r","",$prm);
	
	// ログ出力
	$log_pc->info($prm);
	
	include_once('/home/emap/src/log/inc/com_log_close.inc');
}

// ------------------------------------------------------------
// 拠点データ取得
// ------------------------------------------------------------
//function ZdcSearchCgiKyotenid($kid, $type = 1, $putLog = true){		mod 2012/03/08 Y.Matsukawa
function ZdcSearchCgiKyotenid($kid, $type = 1, $putLog = true, $jkn=''){
	global $cid, $D_CID, $D_SSAPI, $D_SSAPI_KEY, $D_MOBILE_URL, $D_QRIMG_URL, $D_QRIMG_E, $D_QRIMG_V, $D_QRIMG_S, $D_KYO_COL_NAME, $D_SOCKET_TIMEOUT;
	global $P_FREEPARAMS_ENC, $P_FREEPARAMS_SJIS, $D_FREEPARAMS_TO_MBURL;
	global $condprm, $his;
	global $condprm_enc;
	global $D_DIR_BASE_G;
	global $D_DATA_CID, $D_ICON_CID;		// add 2011/12/05 Y.Matsukawa
	global $D_MBURL_EX;		// add 2012/01/06 Y.Matsukawa
	global $D_ICONID_COL, $D_ICON;		// add 2012/04/16 Y.Matsukawa
	global $D_ORG_KBN_COL, $D_ORG_KBN_NAME_LIST;		// add 2012/09/19 H.Osamoto
	global $D_KYO_LVL_COL_NAME_P;		// add 2012/11/13 Y.Matsukawa
	global $D_KYOTENID_CUST;		// add 2012/11/13 Y.Matsukawa
	global $D_KYOTENLVL_COL_P;		// add 2012/11/27 Y.Matsukawa
	global $D_KYOTEN_IMG_DEF;		// add 2013/07/12 T.Sasaki
	// add 2013/07/24 Y.Matsukawa [
	global $D_YTC_TIMESUMM, $D_YTC_24_LBL, $D_YTC_ALL_TITLE;
	global $D_YTC_WD_LBL, $D_YTC_TIMECOL_WD_FR, $D_YTC_TIMECOL_WD_TO;
	global $D_YTC_OT_LBL, $D_YTC_TIMECOL_OT_FR, $D_YTC_TIMECOL_OT_TO;
	global $D_YTC_HLDYCOL_DAY_LBL, $D_YTC_HLDYCOL_OTH_LBL;
	// add 2013/07/24 Y.Matsukawa ]
	global $D_YTC_WKDYCOL_DAY_LBL;		// add 2015/05/26 H.Osamoto
	global $D_STR_DIFF_COLS;		// add 2013/08/07 Y.Matsukawa
	global $D_COL_VAL_CHK;		// add 2013/08/08 Y.Matsukawa
	global $D_COL_VAL_CHK_POS;		// add 2015/10/28 Y.Uesugi
	global $D_CUST_CNV_FLG;		// add 2013/09/06 Y.Matsukawa
	global $D_PC2_URL;		// add 2015/02/20 H.Osamoto
	//global $D_SMT_URL;		// add 2016/02/05 N.Wada	mod 2016/05/06 N.Wada
	global $D_SMT_URL_PRCL;
	global $D_KYOTEN_ITEM_DATETIME;		// add 2015/03/13 Y.Matsukawa
	global $D_KYOTEN_ITEM_ZIP;			// add 2015/11/16 Y.Uesugi
	global $D_FLAGS_ANY_ON, $D_KYOTEN_ITEM_TIME;		// add 2016/06/10 Y.Matsukawa
	global $D_COLUMNS_ANY_VALUE;			// add 2016/09/20 N.Wada
	global $D_COLUMNS_ANY_MATCH_VALUE;		// add 2016/09/26 N.Wada
	global $D_TIME_COMP_COLS;		// add 2016/09/30 N.Wada
	global $D_FLAGS_ALL_ON;			// add 2016/10/25 N.Wada
	global $D_KYOTEN_WGS_COL;		// add 2017/02/16 N.Wada

	//CGIへアクセス
	if ($putLog) {
		$cgi = $D_SSAPI["kyotenid"];
	} else {
		$cgi = $D_SSAPI["kyotenid_nolog"];
	}
	//$url = sprintf("%s?key=%s&cid=%s&opt=%s&kid=%s&type=%s", $cgi, $D_SSAPI_KEY, $D_CID, $cid, $kid, $type);		mod 2011/12/05 Y.Matsukawa
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&kid=%s&type=%s", $cgi, $D_SSAPI_KEY, $D_DATA_CID, $cid, $kid, $type);
	if ($jkn) $url .= '&jkn='.urlencode($jkn);		// add 2012/03/08 Y.Matsukawa
	if (isset($D_KYOTENID_CUST) && $D_KYOTENID_CUST) $url .= '&cust='.$D_KYOTENID_CUST;		// add 2012/11/13 Y.Matsukawa
	$url .= '&mltimg=1';	// 拠点（複数）画像取得オプション	2013/07/12 T.Sasaki

	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	//戻り値の解釈
	$cnt = count($dat);
	if($cnt < 2) return false;//エラー
	$rec = ZdcConvertEncoding($dat[1]);
	$rec = explode("\t", $rec);
	
	//値の作成
	$tpl["kid"]  = $kid;
	$tpl["lat"]  = $rec[0];
	$tpl["lon"]  = $rec[1];

	// add 2016/02/16 F.Yokoi [
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
	}
	// add 2016/02/16 F.Yokoi ]

	$tpl["icon"] = $rec[2];
	$tpl["icon_".$rec[2]] = 1;		// add 2012/11/13 Y.Matsukawa
	// add 2016/03/11 Y.Matsukawa [
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
	// add 2016/03/11 Y.Matsukawa ]

	if(isset($rec[3]) && intval($rec[3])) {
		$tpl["gifflg"]= "1";
	} else {
		$tpl["gifflg"]= "";
	}
	if(isset($rec[4]) && intval($rec[4])) {
		$tpl["new"] = "1";
	} else {
		$tpl["new"] = "";
	}
	// add 2013/08/08 Y.Matsukawa [
	//---------------------------------------------
	// 拠点IDの値判定
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
	// add 2013/08/08 Y.Matsukawa ]

	// add 2015/10/28 Y.Uesugi [
	//---------------------------------------------
	// 拠点IDの値判定(比較位置指定)
	// （例）$D_COL_VAL_CHK_POS['kid'][] = array('000', 'A', 0, 3);
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
	// add 2015/10/28 Y.Uesugi ]

	// add 2012/11/13 Y.Matsukawa [
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
	// add 2012/11/13 Y.Matsukawa ]
	
	// 拠点（複数）画像	add 2013/07/12 Add T.Sasaki
	$last++;
	$multi_img_col_idx = $last;

	// add 2013/07/24 Y.Matsukawa [
	$ytc_time_wd = array();
	$ytc_time_oh = array();
	$ytc_hldy_lbl = array();
	$ytc_hldy_oth_lbl = '';
	// add 2013/07/24 Y.Matsukawa ]
	$ytc_wkdy_lbl = array();	// add 2015/05/26 H.Osamoto

	for($i = 0;$i < 202;$i ++) {
		// add 2012/11/13 Y.Matsukawa [
		if (isset($rec[5+$i])) {
			$d = $rec[5+$i];
		} else {
			$d = "";
		}
		// add 2012/11/13 Y.Matsukawa ]
		if (isset($D_KYO_COL_NAME[$type][$i])) {
			$col = $D_KYO_COL_NAME[$type][$i];
			// del 2012/11/13 Y.Matsukawa [
			//			if (isset($rec[5+$i])) {
			//				$d = $rec[5+$i];
			//			} else {
			//				$d = "";
			//			}
			// del 2012/11/13 Y.Matsukawa ]
			// 表示項目
			if ($col != '') {
				$tpl[$col] = $d;
				$tpl[$col."_SJIS_ENC"] = urlencode(mb_convert_encoding($d,"SJIS","EUC"));	// add 2012/01/19 N.Wada
				$tpl[$col."_UTF8_ENC"] = urlencode(mb_convert_encoding($d,"UTF-8","EUC"));	// add 2012/08/15 H.Osamoto
				if($d) $tpl[$col."l".$d] = "1";
				if(intval($d) == 1) $tpl[$col."b"] = "1";
				if($col == 'name') $tpl['name_enc'] = urlencode($d);
				// add 2012/04/16 Y.Matsukawa [
				// 別カラムのアイコンIDを使用
				if ($col == $D_ICONID_COL && $d && $D_ICON[$d]) {
					$tpl["icon"] = $d;
				}
				// add 2012/04/16 Y.Matsukawa ]
				// add 2012/09/19 H.Osamoto [
				// 専用区分定義を適用
				if ($col == $D_ORG_KBN_COL && $d && $D_ORG_KBN_NAME_LIST[$d]) {
					$tpl[$col."_name"] = $D_ORG_KBN_NAME_LIST[$d];
				}
				// add 2012/09/19 H.Osamoto ]
				// del 2012/11/13 Y.Matsukawa [
				//			} else {
				//				if (ctype_digit($d) && 1 <= $d && $d <= 18) {
				//					$tpl['kyoten_lvl'] = $d;
				//					if($d) $tpl['kyoten_lvl'.$d] = "1";
				//				}
				//				break;
				// del 2012/11/13 Y.Matsukawa ]
				// add 2013/09/06 Y.Matsukawa [
				// 特定の値の場合にフラグを立てる
				if (is_array($D_CUST_CNV_FLG[$col]) && isset($D_CUST_CNV_FLG[$col][$d])) {
					$tpl[$col.'_'.$D_CUST_CNV_FLG[$col][$d]] = 1;
				}
				// add 2013/09/06 Y.Matsukawa ]
				// add 2013/08/08 Y.Matsukawa [
				//---------------------------------------------
				// 任意カラムの値判定
				// （例）$D_COL_VAL_CHK['col_01'][] = array('あ', 'A');
				//  → col_01='あ' ならば、{def list/col_01_EQ_A}が真になる
				//---------------------------------------------
				if (isset($D_COL_VAL_CHK[$col]) && is_array($D_COL_VAL_CHK[$col])) {
					foreach ($D_COL_VAL_CHK[$col] as $cvc) {
						$cvc_val = $cvc[0];
						$cvc_lbl = $cvc[1];
						if ($d == $cvc_val) {
							$tpl[$col.'_EQ_'.$cvc_lbl] = 1;
						}
						// add 2015/10/20 N.Wada [
						if ($d < $cvc_val) {
							$tpl[$col.'_LT_'.$cvc_lbl] = 1;
						}
						if ($d > $cvc_val) {
							$tpl[$col.'_GT_'.$cvc_lbl] = 1;
						}
						if ($d <= $cvc_val) {
							$tpl[$col.'_LTE_'.$cvc_lbl] = 1;
						}
						if ($d >= $cvc_val) {
							$tpl[$col.'_GTE_'.$cvc_lbl] = 1;
						}
						// add 2015/10/20 N.Wada ]
					}
				}
				// add 2013/08/08 Y.Matsukawa ]
				// add 2015/03/13 Y.Matsukawa [
				//---------------------------------------------
				// 日時を分割
				//---------------------------------------------
				if (isset($D_KYOTEN_ITEM_DATETIME[$col]) && $D_KYOTEN_ITEM_DATETIME[$col]) {
					splitDateTimeCol($col, $d, &$tpl);
				}
				// add 2015/03/13 Y.Matsukawa ]
				// add 2016/06/10 Y.Matsukawa
				//---------------------------------------------
				// 時刻書式
				//---------------------------------------------
				if (isset($D_KYOTEN_ITEM_TIME[$col]) && $D_KYOTEN_ITEM_TIME[$col]) {
					formatTimeCol($col, $d, &$tpl);
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
				// add 2015/11/16 Y.Uesugi ]
				// add 2013/07/24 Y.Matsukawa [
				//---------------------------------------------
				// ヤマト運輸向け：営業時間情報をサマリ
				//---------------------------------------------
				if (isset($D_YTC_TIMESUMM) && $D_YTC_TIMESUMM) {
					// 平日（月〜金）
					if (isset($D_YTC_TIMECOL_WD_FR) && isset($D_YTC_TIMECOL_WD_TO)) {
						// 開始時刻
						if (isset($D_YTC_TIMECOL_WD_FR[$col])) {
							$ytc_time_wd[$D_YTC_TIMECOL_WD_FR[$col]][0] = $d;
						}
						// 終了時刻
						if (isset($D_YTC_TIMECOL_WD_TO[$col])) {
							$ytc_time_wd[$D_YTC_TIMECOL_WD_TO[$col]][1] = $d;
						}
					}
					// その他（土・日・祝）
					if (isset($D_YTC_TIMECOL_OT_FR) && isset($D_YTC_TIMECOL_OT_TO)) {
						// 開始時刻
						if (isset($D_YTC_TIMECOL_OT_FR[$col])) {
							$ytc_time_oh[$D_YTC_TIMECOL_OT_FR[$col]][0] = $d;
						}
						// 終了時刻
						if (isset($D_YTC_TIMECOL_OT_TO[$col])) {
							$ytc_time_oh[$D_YTC_TIMECOL_OT_TO[$col]][1] = $d;
						}
					}
				}
				//---------------------------------------------
				// ヤマト運輸向け：定休日情報をサマリ
				//---------------------------------------------
				// 月〜祝
				if (isset($D_YTC_HLDYCOL_DAY_LBL)) {
					if (isset($D_YTC_HLDYCOL_DAY_LBL[$col]) && $d == '1') {
						$ytc_hldy_lbl[] = $D_YTC_HLDYCOL_DAY_LBL[$col];
					}
				}
				// 不定休・年中無休
				if (isset($D_YTC_HLDYCOL_OTH_LBL)) {
					if (isset($D_YTC_HLDYCOL_OTH_LBL[$col]) && $d == '1') {
						$ytc_hldy_oth_lbl = $D_YTC_HLDYCOL_OTH_LBL[$col];
					}
				}
				// add 2013/07/24 Y.Matsukawa ]
				// add 2015/05/26 H.Osamoto [
				//---------------------------------------------
				// ヤマト運輸向け：平日営業日情報をサマリ
				//---------------------------------------------
				// 月〜金
				if (isset($D_YTC_WKDYCOL_DAY_LBL)) {
					if (isset($D_YTC_WKDYCOL_DAY_LBL[$col]) && $d != '1') {
						$ytc_wkdy_lbl[] = $D_YTC_WKDYCOL_DAY_LBL[$col];
					}
				}
				// add 2015/05/26 H.Osamoto ]
			}
		// add 2012/11/13 Y.Matsukawa [
		// 拠点縮尺
		//} else if ($kyo_lvl_col_idx > 0 && $kyo_lvl_col_idx == $i) {		mod 2012/11/27 Y.Matsukawa
		} else if ($D_KYOTENLVL_COL_P && $kyo_lvl_col_idx > 0 && $kyo_lvl_col_idx == $i) {
			// mod 2015/05/22 H.Osamoto [
			if (preg_match('/^@@KYOTEN_LEVEL@@:/', $d)) {
				$wk_lvl = explode(":", $d);
				$d = $wk_lvl[1];
			// mod 2015/05/22 H.Osamoto ]
				if ($d && ctype_digit($d) && 1 <= $d && $d <= 18) {
					$tpl['kyoten_lvl'] = $d;
					$tpl['kyoten_lvl'.$d] = "1";
				}
			// mod 2015/05/22 H.Osamoto [
			}
			// mod 2015/05/22 H.Osamoto ]
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
		// add 2012/11/13 Y.Matsukawa ]
		// 拠点（複数）画像	add 2013/07/12 Add T.Sasaki
		} else if ($multi_img_col_idx > 0 && $multi_img_col_idx == $i) {
			if ($d != '') {
				$arr_mlt_img_no = explode(",", $d);
				if ( is_array( $arr_mlt_img_no ) && count( $arr_mlt_img_no ) ) {
					$multi_img_seq = array();		// add 2013/10/04 Y.Matsukawa
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
						// シーケンス参照		add 2013/10/04 Y.Matsukawa
						$multi_img_seq[] = array('img'=>$tpl["mltimg$mlt_img_no"], 'name'=>$tpl["mltname$mlt_img_no"]);
					}
					// シーケンス参照		add 2013/10/04 Y.Matsukawa
					if (count($multi_img_seq)) {
						$tpl['multi_img_seq_count'] = count($multi_img_seq);
						foreach ($multi_img_seq as $q=>$mim) {
							$mim["seq"] = $q+1;		// add 2013/10/07 Y.Matsukawa
							$mim["seq".($q+1)] = 1;		// add 2013/10/07 Y.Matsukawa
							$tpl['multi_img_seq'][$q] = $mim;
							$tpl['multi_img_seq'.($q+1)] = $mim;		// add 2013/10/07 Y.Matsukawa
						}
					}
				}
			}
		}
	}
	
	// add 2017/02/16 N.Wada [
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
	// add 2017/02/16 N.Wada ]

	// add 2015/09/25 H.Yasunaga[
	// 公開開始日時・公開終了日時・NEW表示開始日時・NEW表示終了日時を$tplに含める
	$tpl['PUB_S_DATE'] = $rec[count($rec)-4];
	$tpl['PUB_E_DATE'] = $rec[count($rec)-3];
	$tpl['DISP_NEW_S_DATE'] = $rec[count($rec)-2];
	$tpl['DISP_NEW_E_DATE'] = $rec[count($rec)-1];
	// add 2015/09/25 H.Yasunaga]

	// add 2013/08/07 Y.Matsukawa
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

	// add 2016/09/30 N.Wada
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

	// add 2016/06/10 Y.Matsukawa
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

	// add 2016/10/25 N.Wada
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

	// add 2013/07/24 Y.Matsukawa [
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
	// add 2013/07/24 Y.Matsukawa ]
	// add 2015/05/26 H.Osamoto [
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
	// add 2015/05/26 H.Osamoto ]

	if (!isset($tpl['kyoten_lvl'])) $tpl['kyoten_lvl'] = "";
	if (isset($D_ICON[$tpl["icon"]])) {		// add 2012/11/13 Y.Matsukawa
		//$tpl["iconimg"] = sprintf("%s?cid=%s&icon_id=%s", $D_SSAPI["icon_select_g"], $D_CID, $tpl["icon"]);		mod 2011/12/05 Y.Matsukawa
		$tpl["iconimg"] = sprintf("%s?cid=%s&icon_id=%s", $D_SSAPI["icon_select_g"], $D_ICON_CID, $tpl["icon"]);
	// add 2012/11/13 Y.Matsukawa [
	} else {
		$tpl["iconimg"] = $D_ICON["@TP"]["IMG"];
	}
	// add 2012/11/13 Y.Matsukawa ]
	//$tpl["gifimg"]    = sprintf("%s?cid=%s&kid=%s", $D_SSAPI["gif_select"], $D_CID, $kid);		mod 2011/12/05 Y.Matsukawa
	$tpl["gifimg"]    = sprintf("%s?cid=%s&kid=%s", $D_SSAPI["gif_select"], $D_DATA_CID, $kid);
	$tpl["mobileurl"] = sprintf("%s?kid=%s&", $D_MOBILE_URL, $kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobileurl"] .= "&".$P_FREEPARAMS_SJIS;
	// add 2012/01/06 Y.Matsukawa [
	if (isset($D_MBURL_EX) && $D_MBURL_EX != '') {
		$tpl["mobileurl"] .= $D_MBURL_EX;
	}
	// add 2012/01/06 Y.Matsukawa ]
	$tpl["mobileurl_encode"] = urlencode($tpl["mobileurl"]);
	$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s", $D_QRIMG_URL, $D_CID, urlencode(urlencode($tpl["mobileurl"])));
	$tpl["mobiledtlurl"] = sprintf("%s?ksid=%s", $D_MOBILE_URL, $kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobiledtlurl"] .= "&".$P_FREEPARAMS_SJIS;
	// add 2012/01/06 Y.Matsukawa [
	if (isset($D_MBURL_EX) && $D_MBURL_EX != '') {
		$tpl["mobiledtlurl"] .= $D_MBURL_EX;
	}
	// add 2012/01/06 Y.Matsukawa ]
	$tpl["mobiledtlurl_encode"] = urlencode($tpl["mobiledtlurl"]);
	$tpl["qrimgdtlurl"]  = sprintf("%s?cid=%s&d=%s", $D_QRIMG_URL, $D_CID, urlencode(urlencode($tpl["mobiledtlurl"])));
	
	// add 2015/02/20 H.Osamoto [
	$tpl["pcurl"] = sprintf("%sdtl/%s/?", $D_PC2_URL, $kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS) $tpl["pcurl"] .= "&".$P_FREEPARAMS;
	if (isset($D_MBURL_EX) && $D_MBURL_EX != '') {
		$tpl["pcurl"] .= $D_MBURL_EX;
	}
	$tpl["pcurl_encode"] = urlencode($tpl["pcurl"]);
	$tpl["qrimgpcurl"]  = sprintf("%s?cid=%s&d=%s", $D_QRIMG_URL, $D_CID, urlencode(urlencode($tpl["pcurl"])));
	// add 2015/02/20 H.Osamoto ]
	
	// add 2016/02/05 N.Wada [
	// スマホ詳細地図画面
	//$tpl["smturl"] = sprintf("%smap/%s/?", $D_SMT_URL, $kid);	mod 2016/05/06 N.Wada
	$tpl["smturl"] = sprintf("%smap/%s/?", $D_SMT_URL_PRCL, $kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_ENC) $tpl["smturl"] .= "&".$P_FREEPARAMS_ENC;
	if (isset($D_MBURL_EX) && $D_MBURL_EX != '') {
		$tpl["smturl"] .= $D_MBURL_EX;
	}
	$tpl["smturl_encode"] = urlencode($tpl["smturl"]);
	$tpl["qrimgsmturl"]  = sprintf("%s?cid=%s&d=%s", $D_QRIMG_URL, $D_CID, urlencode(urlencode($tpl["smturl"])));
	// add 2016/02/05 N.Wada ]
	
	//$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI["icon_select_g"], $D_CID);		mod 2011/12/05 Y.Matsukawa
	$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI["icon_select_g"], $D_ICON_CID);
	//$tpl["_cgiSysIconimg"] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI["sys_icon_select"], $D_CID);		mod 2011/12/05 Y.Matsukawa
	$tpl["_cgiSysIconimg"] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI["sys_icon_select"], $D_DATA_CID);
	$tpl['_cgiSysIconimgSSL'] = sprintf("%s?cid=%s&icon_id=", $D_SSAPI['sys_icon_select_ssl'], $D_DATA_CID);	//add 2016/07/27 Y.Uesugi
	//$tpl["_cgiGifimg"]  = sprintf("%s?cid=%s&kid=", $D_SSAPI["gif_select"], $D_CID);		mod 2011/12/05 Y.Matsukawa
	$tpl["_cgiGifimg"]  = sprintf("%s?cid=%s&kid=", $D_SSAPI["gif_select"], $D_DATA_CID);
	$tpl["_jsMsg"]    = sprintf("ZdcEmapShopMsg(null)", $kid);
	$tpl["_jsMove"]   = sprintf("ZdcEmapMapMove('%s','%s')", cnv_dms2hour($rec[0]), cnv_dms2hour($rec[1]));
	$tpl["_jsScroll"] = sprintf("ZdcEmapMapScroll('%s','%s')", cnv_dms2hour($rec[0]), cnv_dms2hour($rec[1]));
	//$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s','%s');",$kid,cnv_dms2hour($rec[0]),cnv_dms2hour($rec[1]),$rec[2],$tpl["new"],$tpl['kyoten_lvl']);
	//$tpl["_urlDetail"] = $D_DIR_BASE_G.'dtl/'.$kid.'/?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm?'&'.$condprm:'').($his?'&his='.$his:'');		mod 2015/03/17 Y.Matsukawa
	$tpl["_urlDetail"] = $D_DIR_BASE_G.'dtl/'.$kid.'/?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm_enc?'&'.$condprm_enc:'').($his?'&his='.$his:'');
	$tpl["_urlDetailNoParam"] = $D_DIR_BASE_G.'dtl/'.$kid.'/';		// add 
	$tpl["_jsNeki"]   = sprintf("ZdcEmapStationClick('%s','%s')", cnv_dms2hour($rec[0]), cnv_dms2hour($rec[1]));
	$tpl["_jsFreeRoute"] = sprintf("ZdcEmapFreeRouteClick('%s','%s')", cnv_dms2hour($rec[0]), cnv_dms2hour($rec[1]));
	$tpl["_jsFreeRouteLight"] = sprintf("ZdcEmapFreeRouteClickLight('%s','%s')", cnv_dms2hour($rec[0]), cnv_dms2hour($rec[1]));
	$tpl["_jsSearchPlaceRoute"] = sprintf("ZdcEmapRouteFromSearchPlace('%s','%s')", cnv_dms2hour($rec[0]), cnv_dms2hour($rec[1]));		// add 2014/12/08 Y.Matsukawa
	$tpl["_jsPrint"]  = sprintf("ZdcEmapShopPrintClick('%s')", $kid);
	//$tpl["_urlPrint"] = $D_DIR_BASE_G.'prt/'.$kid.'/?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm?'&'.$condprm:'');		mod 2015/03/17 Y.Matsukawa
	$tpl["_urlPrint"] = $D_DIR_BASE_G.'prt/'.$kid.'/?'.($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:'').($condprm_enc?'&'.$condprm_enc:'');
	$tpl["_urlPrintNoParam"] = $D_DIR_BASE_G.'prt/'.$kid.'/';
	$tpl["_jsSearch"] = "ZdcEmapSearchNpoi()";
	$tpl["_jsDetailNpoi"]   = "ZdcEmapShopDetailNpoiClick()";
	
	return $tpl;
}

// add 2016/06/10 Y.Matsukawa
// ------------------------------------------------------------
// 任意項目の値（ユニーク値）から拠点IDを取得
// ------------------------------------------------------------
function ZdcFindKyotenById($col, $id) {
	global $cid, $D_DATA_CID, $D_SSAPI, $D_SSAPI_KEY, $D_SOCKET_TIMEOUT;

	$cgi = $D_SSAPI["kyotenlist"];
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&pos=%d&cnt=%d&jkn=%s:'%s'",
					$cgi, $D_SSAPI_KEY, $D_DATA_CID, $cid, 1, 1, $col, urlencode($id));
	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if(!intval($status[2])) return '';//エラー
	$rec = ZdcConvertEncoding($dat[1]);
	$rec = explode("\t", $rec);
	return $rec[0];
}


// add 2014/05/16 Y.Matsukawa
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

// add 2015/10/23 Y.Uesugi
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

// add 2015/12/21 Y.Uesugi [
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
// add 2015/12/21 Y.Uesugi ]

// add 2012/01/10 Y.Matsukawa
// ------------------------------------------------------------
// リクエストURI返却（POST対応）
// ------------------------------------------------------------
function ZdcGetRequestURI() {
	global $_VARS;
	if ($_SERVER['REQUEST_METHOD'] == 'POST') {
		if ($_VARS && count($_VARS)) {
			$prms = 'enc=EUC';
			foreach ($_VARS as $key=>$val) {
				switch ($key) {
					case '&':
					case 'enc':
						break;
					default:
						$prms .= '&'.$key.'='.urlencode($val);
				}
			}
			return $_SERVER['REQUEST_URI'].'?'.$prms;
		}
	}
	return $_SERVER['REQUEST_URI'];
}
// add 2014/12/11 Y.Matsukawa
// ------------------------------------------------------------
// 住所接続URLを緯度経度接続URLに変換
// ------------------------------------------------------------
function ZdcAddrIF2LatlonIF($url, $lat, $lon) {
	$newparms = array();
	list($u, $p) = explode('?', $url);
	if ($p) {
		$parms = explode('&', $p);
		foreach ($parms as $parm) {
			if (strpos($parm, 'addr=') !== 0) {
				$newparms[] = $parm;
			}
		}
	}
	return $u.'?'.(count($newparms)?implode('&', $newparms).'&':'')."lat=$lat&lon=$lon";
}

// 2012/02/29 Y.Matsukawa
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

// add 2016/06/10 Y.Matsukawa
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
	@error_log(date('Y/m/d H:i:s').'['.$_SERVER['SCRIPT_NAME'].']'.$str."\n", 3, D_DEBUG_LOG_FILE);
}
// ------------------------------------------------------------
// エラーログ情報出力
// ------------------------------------------------------------
function erl($str){
	@error_log(date('Y/m/d H:i:s').'['.$_SERVER['SCRIPT_NAME'].']'.$str."\n", 3, D_ERROR_LOG_FILE);
}

// add 2012/08/03 H.Osamoto
// ------------------------------------------------------------
// HTML表示用変換処理
// ------------------------------------------------------------
function zdcHtmlspecialchars_arr($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/_enc$|_ENC$/i', $key)) {
			$obj[$key] = $val;
		} if (preg_match('/^name$|^addr$/i', $key)) {
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
	
	if (preg_match('/^name$|^addr$/i', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr($target);
	} else if (preg_match('/^col_[0-9][0-9]+$/i', $col_name)) {
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
	
	//$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// 許可タグリスト		mod 2016/06/15 Y.Matsukawa
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

// add 2015/12/24 F.Yokoi [
function zdcHtmlspecialchars_arr_raw($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/_enc$|_ENC$/i', $key)) {

		} if (preg_match('/^name$|^addr$/i', $key)) {
			$obj[$key."_raw"] = zdcHtmlspecialchars_nameaddr_raw($val);
		} else if (preg_match('/^col_[0-9][0-9]+$/i', $key)) {
			$obj[$key."_raw"] = zdcHtmlspecialchars_col_raw($val);
		} else {

		}
	}
	
	return $obj;
}

function zdcHtmlspecialchars_raw($target, $col_name) {
	
	if (preg_match('/^name$|^addr$/i', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr_raw($target);
	} else if (preg_match('/^col_[0-9][0-9]+$/i', $col_name)) {
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
	
	//$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// 許可タグリスト		mod 2016/06/15 Y.Matsukawa
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
// add 2015/12/24 F.Yokoi ]

// ------------------------------------------------------------
// リアルタイムデータ取得
// ------------------------------------------------------------
function ZdcSearchCgiRd($kid,$rd_grp,$rdtype=null){
	global $cid, $D_CID, $D_SSAPI, $D_SOCKET_TIMEOUT,$D_DATA_CID ;
	require_once('/home/emap/src/Jsphon/Decoder.php');

	//CGIへアクセス
	$cgi = $D_SSAPI["rd_store_id"];
	$url = sprintf("%s?cid=%s&kid=%s&grp=%s&intid=%s", $cgi,  $D_DATA_CID, $kid, $rd_grp,"@EMAPP2@");
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

// Get cookie add 2014/08/29 Q.Dai [
// ------------------------------------------------------------
// 保存店舗をCookie読み込み
// 指定がある場合は店舗情報をCGIから取得
// ------------------------------------------------------------
function getShopDtlFromCookie( $freeparms_enc) {
	global $D_SSAPI, $D_CID, $D_SSAPI_KEY, $D_SOCKET_TIMEOUT, $D_KYO_COL_NAME;
	global $D_COOKIE_SHOPDTL_MAX, $D_COOKIE_SHOPDTL_KEY, $D_COOKIE_SHOPDTL_CGI;
	global $D_SHOPDATA_TRIM_WIDTH, $D_SHOPDATA_TRIM_MARKER, $D_SHOPDATA_TRIM_TYPE;		// add 2012/06/21 Y.Matsukawa
	global $D_DATA_CID;		// add 2014/10/27 H.Osamoto
	global $D_COOKIE_SHOPDTL_KEY_ADD;		// add 2016/05/13 N.Wada

	// need check.
	$D_COOKIE_SHOPDTL_KEY = "PC_SHOPDTL_{$D_CID}";
	// add 2016/05/13 N.Wada [
	if (isset($D_COOKIE_SHOPDTL_KEY_ADD) && $D_COOKIE_SHOPDTL_KEY_ADD) {
		$D_COOKIE_SHOPDTL_KEY .= "_".$D_COOKIE_SHOPDTL_KEY_ADD;
	}
	// add 2016/05/13 N.Wada ]

	$shop_dtl = array();
	$shop_id = array();
	if ($D_COOKIE_SHOPDTL_MAX > 0) {
		if (isset($_COOKIE[$D_COOKIE_SHOPDTL_KEY]) && $_COOKIE[$D_COOKIE_SHOPDTL_KEY] != '') {
			// Cookie保存拠点を取得
			$ckval = explode(',', $_COOKIE[$D_COOKIE_SHOPDTL_KEY]);
			$cnt = floor(count($ckval)/2);
			$cnt = ($cnt<=$D_COOKIE_SHOPDTL_MAX ? $cnt : $D_COOKIE_SHOPDTL_MAX);
			for ($i = 0; $i < $cnt; $i++) {
				$shop_dtl_no[$ckval[$i*2]] = $i;
				$shop_dtl[$i] = array('kyoten_id'=>$ckval[$i*2], 'name'=>urldecode($ckval[$i*2+1]));
				$shop_dtl[$i]['_urlDetail'] = $D_DIR_BASE_G.'dtl/'.$ckval[$i*2].'/?'.($freeparms_enc?'&'.$freeparms_enc:'');
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
// add 2014/08/29 Q.Dai ]

// Cookieクリア		add 2014/12/09 Y.Matsukawa
function ZdcCookieShopDtlClear($cid) {
	global $D_COOKIE_SHOPDTL_KEY_ADD;		// add 2016/05/13 N.Wada
	// add 2016/05/13 N.Wada [
	if (isset($D_COOKIE_SHOPDTL_KEY_ADD) && $D_COOKIE_SHOPDTL_KEY_ADD) {
		setcookie("PC_SHOPDTL_{$cid}_".$D_COOKIE_SHOPDTL_KEY_ADD, "", time() + ($D_COOKIE_SHOPDTL_EXPIRE * (24*60*60)), "/");
	} else {
	// add 2016/05/13 N.Wada ]
		setcookie("PC_SHOPDTL_{$cid}", "", time() + ($D_COOKIE_SHOPDTL_EXPIRE * (24*60*60)), "/");
	}
}

// add 2017/02/22 N.Wada
// ------------------------------------------------------------
// 複合ルート検索結果の整形
// ------------------------------------------------------------
function ZdcShapingRouteSrchCombResult($route) {
	// ナビゲーションID
	$record['naviid'] = $route['naviid'];
	// 所用時間(分単位)
	$record['total_time'] = $route['total_time'];
	if ($route['total_time'] >= 60) {
		$record['total_time_hour'] = floor($route['total_time'] / 60);	// 時間
		$record['total_time_min'] = $route['total_time'] % 60;			// 分
	} else {
		$record['total_time_min'] = $route['total_time'];				// 分
	}
	// 出発地
	$record['from']['lat'] = $route['from']['lat'];
	$record['from']['lon'] = $route['from']['lon'];
	// 目的地
	$record['to']['lat'] = $route['to']['lat'];
	$record['to']['lon'] = $route['to']['lon'];
	// 乗換回数
	if (isset($route['transcnt'])) {
		$record['transcnt'] = $route['transcnt'];
	}
	// ルートの種別情報
	if (isset($route['routetype'])) {
		if (isset($route['routetype']['code'])) {
			$record['routetype_code'] = $route['routetype']['code'];
		}
		if (isset($route['routetype']['text'])) {
			$record['routetype_text'] = $route['routetype']['text'];
		}
	}
	// 車種情報
	if (isset($route['cartype'])) {
		if (isset($route['cartype']['code'])) {
			$record['cartype_code'] = $route['cartype']['code'];
		}
		if (isset($route['cartype']['text'])) {
			$record['cartype_text'] = $route['cartype']['text'];
		}
	}
	// 金額
	if (isset($route['fare'])) {
		$record['fare'] = $route['fare'];
		$record['fare_format'] = number_format($route['fare']);			// カンマ入り
	}
	// IC利用時の金額
	if (isset($route['ic_fare'])) {
		$record['ic_fare'] = $route['ic_fare'];
		$record['ic_fare_format'] = number_format($route['ic_fare']);	// カンマ入り
	}
	// 総距離(ｍ単位)
	if (isset($route['distance'])) {
		$record['distance'] = $route['distance'];
		if ($route['distance'] >= 1000) {
			$record['distance_km'] = round($route['distance'] / 1000, 1);	// (ｋｍ単位)小数点第２位を四捨五入
		}
	}
	// ルート内の移動手段情報
	foreach($route['nodes'] as $idx2 => $nodes) {
		$list = array();
		$list_no = ($idx2 + 1);
		// 移動手段番号
		$list['no'] = $list_no;
		$list['no_'.$list_no] = 1;
		// 移動種別情報
		$list['nodetype_code'] = $nodes['nodetype']['code'];
		$list['nodetype_text'] = $nodes['nodetype']['text'];
		// 出発地名称
		$list['start_name'] = $nodes['start_info']['name'];
		// 出発時刻
		$tmp_start_datetime = splitDatetime($nodes['start_info']['date'], $prefix='start_');
		$list = array_merge($list, $tmp_start_datetime);
		// 到着地名称
		$list['end_name'] = $nodes['end_info']['name'];
		// 到着時刻
		$tmp_end_datetime = splitDatetime($nodes['end_info']['date'], $prefix='end_');
		$list = array_merge($list, $tmp_end_datetime);
		// 金額
		if (isset($nodes['fare'])) {
			$list['fare'] = $nodes['fare'];
			$list['fare_format'] = number_format($nodes['fare']);		// カンマ入り
		}
		// IC利用時の金額
		if (isset($nodes['ic_fare'])) {
			$list['ic_fare'] = $nodes['ic_fare'];
			$list['ic_fare_format'] = number_format($nodes['ic_fare']);	// カンマ入り
		}
		// 距離(ｍ単位)
		if (isset($nodes['distance'])) {
			$list['distance'] = $nodes['distance'];
			if ($nodes['distance'] >= 1000) {
				$list['distance_km'] = round($nodes['distance'] / 1000, 1);	// (ｋｍ単位)小数点第２位を四捨五入
			}
		}
		switch ($nodes['nodetype']['code']) {
			case 2:		// 電車
				$record['train'] = 1;
				$list['train'] = 1;
				// 出発駅コード
				$list['start_stcd'] = $nodes['start_info']['stcd'];
				// 到着駅コード
				$list['end_stcd'] = $nodes['end_info']['stcd'];
				// 路線種別
				$list['railkind'] = $nodes['railkind'];
				// 路線名称
				$list['linenm'] = $nodes['linenm'];
				// 列車区分
				if (isset($nodes['trainkind'])) {
					$list['trainkind'] = $nodes['trainkind'];
				}
				// 乗車時間
				$list['time_ride'] = $nodes['time_ride'];
				// 待ち時間
				$list['time_wait'] = $nodes['time_wait'];
				// 直通電車ならばtrue
				$list['join'] = $nodes['join'];
				// 方面名称
				$list['dir_name'] = $nodes['dir_name'];
				// 乗車位置情報
				if (isset($nodes['position'])) {
					// 乗車駅名称
					$list['position_stnm'] = $nodes['position']['stnm'];
					// 車両編成数乗車位置情報
					foreach($nodes['position']['detail'] as $idx3 => $info) {
						$work = array();
						$info_no = ($idx3 + 1);
						// 車両編成数乗車位置番号
						$work['no'] = $info_no;
						$work['no_'.$info_no] = 1;
						// 車両編成数
						$work['train_form'] = $info['train_form'];
						// 乗車位置
						$work['ride_pos'] = $info['ride_pos'];
						$list['position_detail'][] = $work;
					}
				}
				// 路線色
				$list['linecolor'] = $nodes['linecolor'];
				// 発車番線
				if (isset($nodes['platformfrom'])) {
					$list['platformfrom'] = $nodes['platformfrom'];
				}
				// 到着番線
				if (isset($nodes['platformto'])) {
					$list['platformto'] = $nodes['platformto'];
				}
				// 途中停車駅数
				if (isset($nodes['passingcnt'])) {
					$list['passingcnt'] = $nodes['passingcnt'];
				}
				// 停車駅情報
				if (isset($nodes['passing_stations'])) {
					foreach($nodes['passing_stations'] as $idx3 => $info) {
						$work = array();
						$info_no = ($idx3 + 1);
						// 停車駅情報番号
						$work['no'] = $info_no;
						$work['no_'.$info_no] = 1;
						// 停車駅コード
						$work['stcd'] = $info['stcd'];
						// 停車駅到着時刻
						$work['arrive_time'] = $info['arrive_time'];
						// 停車駅名称
						$work['name'] = $info['name'];
						$list['passing_stations'][] = $work;
					}
				}
				break;
			case 3:		// 徒歩
				$record['walk'] = 1;
				$list['walk'] = 1;
				// 出入口名称
				$list['doorways'] = $nodes['doorways'];
				break;
			case 4:		// 車
				$record['drive'] = 1;
				$list['drive'] = 1;
				// 乗車時間
				$list['time_ride'] = $nodes['time_ride'];
				// 経路情報
				foreach($nodes['route_info'] as $idx3 => $info) {
					$work = array();
					$info_no = ($idx3 + 1);
					// 経路情報番号
					$work['no'] = $info_no;
					$work['no_'.$info_no] = 1;
					// 経路種別コード
					$work['code'] = $info['code'];
					// 道路名称
					$work['name'] = $info['name'];
					// 料金
					$work['fare'] = $info['fare'];
					$work['fare_format'] = number_format($info['fare']);		// カンマ入り
					// 有料区間ならばtrue
					$work['pay'] = $info['pay'];
					$list['route_info'][] = $work;
				}
				break;
			case 5:		// 飛行機
				$record['airplane'] = 1;
				$list['airplane'] = 1;
				// 路線名称
				$list['linenm'] = $nodes['linenm'];
				// 乗車時間
				$list['time_ride'] = $nodes['time_ride'];
				// 待ち時間
				$list['time_wait'] = $nodes['time_wait'];
				break;
			case 6:		// バス
				$record['bus'] = 1;
				$list['bus'] = 1;
				// 路線名称
				$list['linenm'] = $nodes['linenm'];
				// 乗車時間
				$list['time_ride'] = $nodes['time_ride'];
				// 待ち時間
				$list['time_wait'] = $nodes['time_wait'];
				// 途中停車駅数
				if (isset($nodes['passingcnt'])) {
					$list['passingcnt'] = $nodes['passingcnt'];
				}
				// 停車駅情報
				if (isset($nodes['passing_stations'])) {
					foreach($nodes['passing_stations'] as $idx3 => $info) {
						$work = array();
						$info_no = ($idx3 + 1);
						// 停車駅情報番号
						$work['no'] = $info_no;
						$work['no_'.$info_no] = 1;
						// 停車駅到着時刻
						$work['arrive_time'] = $info['arrive_time'];
						// 停車駅名称
						$work['name'] = $info['name'];
						$list['passing_stations'][] = $work;
					}
				}
				break;
		}
		// 最初の移動手段情報
		if ($list_no == 1) {
			// ルートの最初を示すフラグ
			$list['route_start'] = 1;
			// ルートの出発時間
			$record = array_merge($record, $tmp_start_datetime);
		}
		// 最後の移動手段情報
		if ($list_no == count($route['nodes'])) {
			// ルートの最後を示すフラグ
			$list['route_end'] = 1;
			// ルートの到着時間
			$record = array_merge($record, $tmp_end_datetime);
		}
		$record['list'][] = $list;
	}
	return $record;
}

//-------------------
// 日時分割関数
// YYYYMMDD HH:MI:SS形式を以下のように分割
//	$prefix.year:  YYYY
//	$prefix.month: MM
//	$prefix.day:   DD
//	$prefix.hour:  HH
//	$prefix.min:   MI
//	$prefix.sec:   SS
//-------------------
function splitDatetime($datetime, $prefix='') {
	list($tmp_date, $tmp_time) = explode(" ", $datetime);
	list($tmp_year, $tmp_month, $tmp_day) = explode("-", $tmp_date);
	list($tmp_hour, $tmp_min, $tmp_sec) = explode(":", $tmp_time);
	return array(
		$prefix.'year'	=> $tmp_year,
		$prefix.'month'	=> $tmp_month,
		$prefix.'day'	=> $tmp_day,
		$prefix.'hour'	=> $tmp_hour,
		$prefix.'min'	=> $tmp_min,
		$prefix.'sec'	=> $tmp_sec
	);
}
?>
