<?php
/*========================================================*/
// ファイル名：ytc_store_nearsearch.cgi
// 処理名：【ヤマト運輸様向けカスタマイズ】店舗案内
//
// 更新履歴
// 2016/04/27 T.Yoshino		新規作成
// 2016/08/12 Y.Matsukawa	コンビニ、ロッカー追加
// 2016/12/12 H.Yasunaga	ヤマトロッカー対応
//							パラメータにSDATE(出荷予定日)・HZIP(発地郵便番号)・BSKBN(ボックスサイズ区分)を追加
//							Kパラメータの17バイト目が"1"の場合にSDATE・HZIP・BSKBNが必須になる
// 2017/01/06 H.Yasunaga	/var/tmp/ysn_dbg.logへのログ出力を削除
// 2017/01/17 H.Yasunaga	ENCパラメータに依った文字コードでレスポンスを出力するよう変更
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y01';

	/*==============================================*/
	// CGI名
	/*==============================================*/
	$APICGINM = "store_nearsearch.cgi";
	
	$CGINM = "store_nearsearch";


	/*==============================================*/
	// コード定義
	/*==============================================*/
	/* 入力パラメータ*/
	define( 'DEF_PRM_ENC_UTF8',		'UTF8' );       // 文字コード（UTF8）
	define( 'DEF_PRM_ENC_SJIS',		'SJIS' );       // 文字コード（SJIS）
	define( 'DEF_PRM_ENC_EUC',		'EUC'  );       // 文字コード（EUC）
	define( 'DEF_PRM_PFLG_DNUM',	'1'    );       // ポイントフラグ（十進緯度経度表記）
	define( 'DEF_PRM_PFLG_MSEC',	'2'    );       // ポイントフラグ（ミリ秒緯度経度表記）
	define( 'DEF_PRM_PFLG_DMS',    	'3'    );       // ポイントフラグ（度分秒緯度経度表記）
	define( 'DEF_PRM_DATUM_TOKYO', 	'TOKYO');       // 測地系（日本測地系）
	define( 'DEF_PRM_DATUM_WGS84', 	'WGS84');       // 測地系（世界測地系）
	define( 'DEF_PRM_OUTF_JSON', 	'JSON' );       // 出力形式（JSON）
	define( 'DEF_PRM_OUTF_XML', 	'XML'  );       // 出力形式（XML）
	
	/* リターンコード */
	define( 'SEARCH_RESULT',			'00000' );	// 条件に見合うデータがありました。
	define( 'NO_SEARCH_RESULT',			'00001' );	// 条件に見合うデータはありませんでした。
	define( 'ERROR_TENPO_DB',			'81000' );	// 店舗データベースアクセスエラーです。
	//define( 'ERROR_TENPO_DB',			'01000' );	// 店舗データベースアクセスエラーです。
	define( 'ERROR_AUTH',				'01001' );	// 認証エラーです。
	define( 'INVALID_SEARCH_KBN',		'01002' );	// 検索対象フラグが空、もしくは不正な値です。
	define( 'ERROR_SYSTEM',				'01003' );	// 内部的な予期しない問題により要求を正しく処理できませんでした。
	
	define( 'INVALID_PARAMETER_CID',	'09001' );	// 企業IDが空、もしくは不正な値です。
	
	define( 'ERROR_MAINTENANCE',		'10000' );	// 要求されたAPIは現在、メンテナンス中です。
	define( 'EXPIRY_ACCESS_TOKEN',		'10001' );	// アクセストークンが有効期限切れです。
	define( 'INVALID_ACCESS_TOKEN',		'10002' );	// アクセストークンが空、もしくは不正な値です。
	define( 'URGENT_MAINTENANCE',		'10003' );	// 要求されたAPIは現在、緊急メンテナンス中です。

	define( 'INVALID_PARAMETER_LAT',	'09002' );	// 緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_LON',	'09003' );	// 経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_ZIP',	'09004' );	// 郵便番号が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_NELAT',	'09005' );	// 北東（右上）緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_NELON',	'09006' );	// 北東（右上）経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SWLAT',	'09007' );	// 南西（左下）緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SWLON',	'09008' );	// 南西（左下）経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_EWDIST',	'09009' );	// 東西距離（経度）が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SNDIST',	'09010' );	// 南北距離（緯度）が空、もしくは不正な値です。
	// add start 2016/12/12 H.Yasunaga ロッカー対応 [
	// ytc_ret_def.incに各コード値のメッセージを追記
	define( 'INVALID_PARAMETER_SDATE',	'09011' );	// 出荷予定日が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_HZIP',	'09012' );	// 発地郵便番号が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_BSKBN',	'09013' );	// ボックスサイズ区分が空、もしくは不正な値です。
	// add end ]

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	include('d_serv_emap.inc');
	include('store_def.inc'); 
	include('store_outf.inc');			// 出力クラス定義
	include('ZdcCommonFunc.inc');		// 共通関数
	include('function.inc');			// 共通関数
	include('d_serv_ora.inc');
	include('oraDBAccess.inc');
	include('chk.inc');					// データチェック関連
	include("jkn.inc");					// 絞り込み条件編集
	include('define.inc');
	include('store_kyoten_outf.inc');
	
	require_once('ytc_def.inc');			// ヤマト運輸用定義
	require_once('ytc_cgi_key.inc');		// ヤマト運輸用emapCGIキー他
	require_once('function.inc');			// 共通関数
	require_once('log.inc');				// ログ出力
	require_once('auth.inc');				// 簡易認証
	
	require_once('/home/emap/src/p/inc/xml_util.inc');


	/*==============================================*/
	// ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// 初期化
	/*==============================================*/
	$status 	= DEF_RETCD_DE;		// ログ用ステータスコード（成功）
	$emap_cid	= $D_CID;			// 企業コード固定　ytc_def.incで定義
	$rescode	= "-1";				// レスポンスコード初期値（エラー）
	$errcode	= "";				// エラーコード初期値
	$outdata	= "";				// 出力結果初期値
	$log_parms	= mb_ereg_replace(' ', '_', $dms);
	$log_parms	.= ' ';
	$log_parms	.= mb_ereg_replace(' ', '_', $sid);
	$KEY		= $D_CGI_KEY;		// CGI用キー

	// Kビット番号
	define('K_IDX_YTC', 0);
	define('K_IDX_TRI', 1);
	define('K_IDX_SEJ', 2);
	define('K_IDX_FMT', 3);
	define('K_IDX_COC', 4);
	define('K_IDX_THF', 5);
	define('K_IDX_NWD', 6);
	define('K_IDX_DYM', 7);
	define('K_IDX_PPR', 8);
	define('K_IDX_PP2', 9);
	define('K_IDX_SON', 10);
	define('K_IDX_LST', 11);
	define('K_IDX_CCK', 12);
	define('K_IDX_SKS', 13);
	// 2016/08/12 Y.Matsukawa [
	define('K_IDX_LAW', 14);
	define('K_IDX_NLW', 15);
	define('K_IDX_LOK', 16);
	// 2016/08/12 Y.Matsukawa ]
	
	//検索対象を指定
	$D_YTC_SITE_FILTER_COND[K_IDX_SEJ] = 'COL_39%3A002';
	$D_YTC_SITE_FILTER_COND[K_IDX_FMT] = 'COL_39%3A001';
	$D_YTC_SITE_FILTER_COND[K_IDX_COC] = 'COL_39%3A175';
	$D_YTC_SITE_FILTER_COND[K_IDX_THF] = 'COL_39%3A003';
	$D_YTC_SITE_FILTER_COND[K_IDX_NWD] = 'COL_39%3A418';
	$D_YTC_SITE_FILTER_COND[K_IDX_DYM] = 'COL_39%3A436';
	$D_YTC_SITE_FILTER_COND[K_IDX_PPR] = 'COL_39%3A101';
	$D_YTC_SITE_FILTER_COND[K_IDX_PP2] = 'COL_39%3A171';
	$D_YTC_SITE_FILTER_COND[K_IDX_SON] = 'COL_39%3A207';
	$D_YTC_SITE_FILTER_COND[K_IDX_LST] = 'COL_39%3A189';
	$D_YTC_SITE_FILTER_COND[K_IDX_CCK] = 'COL_39%3AZ98';
	$D_YTC_SITE_FILTER_COND[K_IDX_SKS] = 'COL_39%3AZ99';
	// add 2016/08/12 Y.Matsukawa [
	$D_YTC_SITE_FILTER_COND[K_IDX_LAW] = 'COL_39%3AZ96';
	$D_YTC_SITE_FILTER_COND[K_IDX_NLW] = 'COL_39%3AZ97';
	$D_YTC_SITE_FILTER_COND[K_IDX_LOK] = 'COL_39%3A563';
	// add 2016/08/12 Y.Matsukawa ]
	$tmp = '';
	//for ($i = K_IDX_SEJ; $i <= K_IDX_SKS; $i++) {		mod 2016/08/12 Y.Matsukawa
	for ($i = K_IDX_SEJ; $i <= K_IDX_LOK; $i++) {
		if ($tmp) $tmp .= '%20AND%20';
		$tmp .= str_replace('%3A', '!%3A', $D_YTC_SITE_FILTER_COND[$i]);
	}
	$D_YTC_COND_TRI = '%28%28'.$tmp.'%29%20OR%20COL_39%20is%20null%29';
	

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', '');						/* 企業ID */
	$LAT		= getCgiParameter('lat','');						/* 緯度 必須項目1 */
	$LON		= getCgiParameter('lon','');						/* 経度 必須項目1 */
	$NELAT		= getCgiParameter('nelat','');						/* 北東（右上）緯度 */
	$NELON		= getCgiParameter('nelon','')			;			/* 北東（右上）経度 */
	$SWLAT		= getCgiParameter('swlat','');						/* 南西（左下）緯度 */
	$SWLON		= getCgiParameter('swlon','');						/* 南西（左下）経度 */
	$EWDIST		= getCgiParameter('ewdist','');						/* 東西距離（経度） */
	$SNDIST		= getCgiParameter('sndist','');						/* 南北距離（緯度） */
	$FILTER		= getCgiParameter('filter','');						/* 絞り込み条件 */
	$POS		= getCgiParameter('pos','1');						/* 取得位置 */
	$CNT		= getCgiParameter('cnt','100');						/* 取得件数 */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* 文字コード */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* ポイントフラグ */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* 測地系 */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* 出力形式 */

	$ZIP		= getCgiParameter('zip','');						/* 郵便番号 必須項目1 */
	$ATOKEN		= getCgiParameter('ATOKEN','');						/* アクセストークン 必須項目 */
	$K			= getCgiParameter('K','');							/* 検索対象フラグ 必須項目 */
	
	$SIZE		= getCgiParameter('SIZE','');						/* 荷物サイズ(60,80,100,120,140,160) */
	$SKBN		= getCgiParameter('SKBN','0');						/* 商品判定区分(0：クール便以外(含未選択)、1：クール便) */

	$PMAPURL	= getCgiParameter('pmapurl', '');					/* pc_map_urlタグ出力判断 */
	$SMAPURL	= getCgiParameter('smapurl', '');					/* smt_map_urlタグ出力判断 */
	$SITE_ID	= getCgiParameter('SITE_ID', '');					/* 連携サイトID */
	$CUST		= getCgiParameter('cust', 'YAMATO01');				/* 対象企業ﾊﾟﾗﾒｰﾀ */

	// add start 2016/12/12 H.Yasunaga ロッカー対応 [
	// 出荷予定日・発地郵便番号・ボックスサイズ区分の3パラメータは、満空APIで利用するパラメータ。店舗データのselect条件には影響しない
	$SDATE		= getCgiParameter('SDATE', '');						/* 出荷予定日*/
	$HZIP		= getCgiParameter('HZIP', '');						/* 発地郵便番号*/
	$BSKBN		= getCgiParameter('BSKBN', '');						/* ボックスサイズ区分*/
	// add end ]

	// 課金ログに出力する企業ID
	$OPTION_CD = $CID;

	// ヤマト様要望
	$LAT	 = urlencode($LAT);
	$LON	 = urlencode($LON);
	$NELAT	 = urlencode($NELAT);
	$NELON	 = urlencode($NELON);
	$SWLAT	 = urlencode($SWLAT);
	$EWDIST	 = urlencode($EWDIST);
	$SNDIST	 = urlencode($SNDIST);
	$POS	 = urlencode($POS);
	$CNT	 = urlencode($CNT);
	$ZIP	 = urlencode($ZIP);
	$SIZE	 = urlencode($SIZE);
	$SKBN	 = urlencode($SKBN);
	$PMAPURL = urlencode($PMAPURL);
	$SMAPURL = urlencode($SMAPURL);


	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	
//	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	$CgiOut = new StoreKyotenCgiOutput("", $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST);

	/*==============================================*/
	// クロスドメイン対応
	/*==============================================*/
	
	header('Access-Control-Allow-Origin: *');

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	// del start 2017/01/07 H.Yasunaga /var/tmp/ysn_dbg.logへのログ出力を削除 [
	//error_log($_SERVER['REQUEST_METHOD'] . "\n", 3, "/var/tmp/ysn_dbg.log");
	// del end 2017/01/06 H.Yasunaga ]
	// リクエスト
	if ($_SERVER['REQUEST_METHOD'] != "GET") {
		outputErrStatus( $rescode, "ERR0003", "リクエスト方法が不正です。" );
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}

	// 企業id[CID]
	if ($CID == '') {
		$status = INVALID_PARAMETER_CID;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	
	
	// 検索対象フラグ[k]
	if ($K == "") {
		$status = INVALID_SEARCH_KBN;
		$CgiOut->set_debug('k', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	} else if ( is_numeric($K) == FALSE ) {
		$status = INVALID_SEARCH_KBN;
		$CgiOut->set_debug('k', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	} else if ( strlen($K) != 30 ) {
		$status = INVALID_SEARCH_KBN;
		$CgiOut->set_debug('k', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}

	// アクセストークン[atoken]
	if ($ATOKEN == "") {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	} else if ( strlen($ATOKEN) > 64 ) {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}

	// add start 2016/12/12 H.Yasunaga ロッカー対応 [
	if ($K[K_IDX_LOK] == 1) {
		// Kパラメータの17バイト目が1の場合は、出荷予定日(SDATE)・発地郵便番号(HZIP)・ボックスサイズ区分(BSKBN)パラメータが必須
		// 出荷予定日は8桁固定			桁数確認 数値確認 日付確認
		// 発地郵便番号は7桁固定		桁数確認 数値確認
		// ボックスサイズ区分は2桁固定 	桁数確認
		if ($SDATE == "") {
			// SDATE(出荷予定日)が空
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if(strlen($SDATE) != 8) {
			// SDATE(出荷予定日)が8桁でない
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (preg_match("/^[0-9]{8}+$/", $SDATE) == false) {
			// SDATE(出荷予定日)が数値形式でない
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (checkdate(substr($SDATE, 4, 2), substr($SDATE, 6, 2), substr($SDATE, 0, 4)) == false) {
			// SDATE(出荷予定日)が日付として正しくない
			// checkdate関数の引数は第一引数が"月",第二引数が"日",第三引数が"年"
			$status = INVALID_PARAMETER_SDATE;
			$CgiOut->set_debug('sdate', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		
		if ($HZIP == "") {
			// HZIP(発地郵便番号)が未設定
			$status = INVALID_PARAMETER_HZIP;
			$CgiOut->set_debug('hzip', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (strlen($HZIP) != 7) {
			// HZIP(発地郵便番号)が7桁以外
			$status = INVALID_PARAMETER_HZIP;
			$CgiOut->set_debug('hzip', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (preg_match("/^[0-9]{7}+$/", $HZIP)== false) {
			// HZIP(発地郵便番号)が数値形式でない
			$status = INVALID_PARAMETER_HZIP;
			$CgiOut->set_debug('hzip', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		
		if ($BSKBN == "") {
			// BSKBN(ボックスサイズ区分)が未設定
			$status = INVALID_PARAMETER_BSKBN;
			$CgiOut->set_debug('bskbn', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		} else if (strlen($BSKBN) != 2) {
			// BSKBN(ボックスサイズ区分)が2桁以外
			$status = INVALID_PARAMETER_BSKBN;
			$CgiOut->set_debug('bskbn', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}
	// add end ]

	//返却URL
	if ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev') {
		//★動作確認用
		$D_YTC_ATOKEN_URL = 'http://103.2.24.43/authapi/authAllow';
//		$D_YTC_ATOKEN_URL = 'http://103.2.24.43/authapi/sample/authAllowSuccess.jsp'; //正常終了
//		$D_YTC_ATOKEN_URL = 'http://103.2.24.43/authapi/sample/authAllowError.jsp';   //異常終了
	} else {
		//★本番URLを指定
		// 28日から本番用URLへ
		$D_YTC_ATOKEN_URL = 'https://authapi.kuronekoyamato.co.jp/authapi/authAllow';
	}
	
	
	//認証確認
	$result = YTCAccessCheckATOKEN($D_YTC_ATOKEN_URL, $ATOKEN);

	if($result == "ERROR_MAINTENANCE"){
		// エラー（APIメンテナンス中）
		$status = ERROR_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result == "URGENT_MAINTENANCE"){
		// エラー（API緊急メンテナンス中）
		$status = URGENT_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result == "EXPIRY_ACCESS_TOKEN"){
		// エラー（アクセストークン有効期限切れ）
		$status = EXPIRY_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result == "ERROR_SYSTEM"){
		// エラー（システムエラー）
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
		
	}else if($result != "SUCCESS_AUTH_ALLOW"){
		// エラー（アクセストークンエラー）
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}


	// 荷物サイズ[SIZE]
//	$arr_size = array( '0', 60, 80, 100, 120, 140, 160, '60', '80', '100', '120', '140', '160' );
//	$chkSIZE = array_search( $SIZE, $arr_size );
//	if ( $chkSIZE == "" && $SIZE != 0 ) {
//		$status = DEF_RETCD_PERR2;
//		$CgiOut->set_debug('SIZE', __LINE__);
//		$CgiOut->set_status($status, 0, 0); 
//		$CgiOut->err_output();
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
//		exit;
//	}
	
	// 商品判定区分[SKBN]
//	$SKBN = (isset($SKBN) ? $SKBN : 0);
//	$SKBN = ($SKBN != 1)? 0: 1;


	// pc_map_url、smt_map_urlタグ出力判断
	$arr_opt_flg = array();
	$arr_opt_flg['pc_map']	 = ($PMAPURL != 1)? "": 1;
	$arr_opt_flg['smt_map']	 = ($SMAPURL != 1)? "": 1;
	$arr_opt_flg['site_id']	 = ($SITE_ID != "")? $SITE_ID: "";
	

	/*==============================================*/
	// パラメータ仕分け
	/*==============================================*/

	// 検索対象フラグ[k]
	$cvs_cond = array();
	for ($i = 0; $i < strlen($K); $i++) {
		$flg = substr($K, $i, 1);
		if ($flg == '1') {
			if ($i == K_IDX_YTC) {
				$D_YTC_SITE_FILTER_YTC = 1;
			}
			//SIZEが120,140,160、SKBNが1の場合は検索しない
			if($SIZE != '120' && $SIZE != '140' && $SIZE != '160' && $SKBN != '1'){
				if ($i == K_IDX_TRI) {
					$D_YTC_SITE_FILTER_TRI = 1;
				}
				//if ($i >= K_IDX_SEJ && $i <= K_IDX_SKS) {		mod 2016/08/12 Y.Matsukawa
				if ($i >= K_IDX_SEJ && $i <= K_IDX_LOK) {
					$D_YTC_SITE_FILTER_CVS = 1;
					$cvs_cond[] = $D_YTC_SITE_FILTER_COND[$i];
				}
			}
		} else if ($flg != '0') {
			$status = INVALID_SEARCH_KBN;
			$CgiOut->set_debug('k', __LINE__);
			$CgiOut->set_status($status, 0, 0); 
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}

	}
	if (count($cvs_cond)) {
		$D_YTC_COND_CVS = '%28'.implode('%20OR%20', $cvs_cond).'%29';
	}
	

	// 全部0だったらエラー
	if ($D_YTC_SITE_FILTER_YTC != 1 && $D_YTC_SITE_FILTER_TRI != 1 && $D_YTC_SITE_FILTER_CVS != 1 ) {
			$status = INVALID_SEARCH_KBN;
			$CgiOut->set_debug('k', __LINE__);
			$CgiOut->set_status($status, 0, 0); 
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
	}
	

	/*==============================================*/
	// 郵便番号から位置取得
	/*==============================================*/
	if (($LAT == '' || $LON == '') && $ZIP != '') {
		// 郵便番号検索
		$cgi = $D_SSAPI["searchzip"];
		//	$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s", 1, 1, 'EUC', urlencode($ZIP), $DATUM, 'TSV');
		$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s&sort=%s", 1, 1, 'EUC', urlencode($ZIP), $DATUM, 'TSV', 'adcd');
		$url = sprintf("%s?key=%s&opt=%s&%s", $cgi, $D_SSAPI_KEY, $OPTION_CD, $prm);
		$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
		$status = explode("\t", $dat[0]);
		if(intval($status[2])) {
			$rec = explode("\t", $dat[1]);
			$LAT = $rec[0];
			$LON = $rec[1];
		}
	}

	/*==============================================*/
	// 絞り込み条件
	/*==============================================*/
	$FILTER_sql = '';
	edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
	$log_jkn = implode(' ', $arr_log_jkn);
	
	
	//--------------------------------------------
	// 複数絞り込み条件（チェックボックス、リストボックス）
	//--------------------------------------------
	$cond = '';

	//ヤマト運輸
	if($D_YTC_SITE_FILTER_YTC){
		$cond = '%28COL_01%3A1%20AND%20%28COL_10%3AA%20OR%20COL_10%3AB%29%29';
	}
	//一般取扱店
	if($D_YTC_SITE_FILTER_TRI){
		if(isset($cond) && $cond != ''){
			$cond .= '%20OR%20%28COL_01%3A2%20AND%20'.$D_YTC_COND_TRI.'%29';
		}else{
			$cond = '%28COL_01%3A2%20AND%20'.$D_YTC_COND_TRI.'%29';
		}
	}
	//コンビニ
	if($D_YTC_SITE_FILTER_CVS){
		if(isset($cond) && $cond != ''){
			$cond .= '%20OR%20%28COL_01%3A2%20AND%20'.$D_YTC_COND_CVS.'%29';
		}else{
			$cond = '%28COL_01%3A2%20AND%20'.$D_YTC_COND_CVS.'%29';
		}
	}
	
	// [B2連携用不可フラグ(COL_50)]は0で固定
	$FILTER = 'COL_50%3a0%20AND%20%28'.$cond.'%29';



	/*==============================================*/
	// 実行用にパラメータ値を結合
	/*==============================================*/
	$parms =  '?cid='.		$CID;
	$parms .= '&lat='.		$LAT;
	$parms .= '&lon='.		$LON;
	$parms .= '&zip='.		$ZIP;
	$parms .= '&nelat='.	$NELAT;
	$parms .= '&nelon='.	$NELON;
	$parms .= '&swlat='.	$SWLAT;
	$parms .= '&swlon='.	$SWLON;
	$parms .= '&ewdist='.	$EWDIST;
	$parms .= '&sndist='.	$SNDIST;
	$parms .= '&filter='.	$FILTER;
	$parms .= '&pos='.		$POS;
	$parms .= '&cnt='.		$CNT;
	$parms .= '&enc='.		$ENC;
	$parms .= '&pflg='.		$PFLG;
	$parms .= '&datum='.	$DATUM;
	$parms .= '&outf='.		$OUTF;
	$parms .= '&pmapurl='.	$arr_opt_flg['pc_map'];
	$parms .= '&smapurl='.	$arr_opt_flg['smt_map'];
	$parms .= '&SITE_ID='.	$arr_opt_flg['site_id'];
	$parms .= '&cust='.		"YAMATO01";

	// add start 2016/12/12 H.Yasunaga ロッカー対応 [
	// store_nearsearch.cgi のカスタマイズパラメータ（配列指定）を利用して
	// ytc_storenearseach.cgiからロッカー用のパラメータを渡す
	$parms .= '&carg[SDATE]='.	$SDATE;		// 出荷予定日
	$parms .= '&carg[HZIP]='.	$HZIP;		// 発地郵便番号
	$parms .= '&carg[BSKBN]='.	$BSKBN;		// ボックスサイズ区分
	// add end ]

	/*==============================================*/
	// 住所逆引き検索CGIコール
	/*==============================================*/
	unset($result);
//	$CGI = 'http://'.$D_DOMAIN_G.'/cgi/'.$APICGINM.$parms;
	$CGI = 'http://127.0.0.1/cgi/'.$APICGINM.$parms;
//	$CGI = 'http://127.0.0.1/cgi.ysn/'.$APICGINM.$parms;
	$result = file_get_contents($CGI);


	if (!$result) {
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('DBopen', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	// 結果出力
	if ( $OUTF != 'JSON' ) {
		// mod start 2017/01/17 H.Yasunaga ENCパラメターに合わせたheaderの出力に変更 [
		//header( "Content-type: text/xml; charset=utf-8" );
		switch($ENC) {
			case DEF_PRM_ENC_UTF8:{
				header( "Content-type: text/xml; charset=UTF-8" );
				break;
			}
			case DEF_PRM_ENC_SJIS:{
				header( "Content-type: text/xml; charset=Shift_JIS" );
				break;
			}
			case DEF_PRM_ENC_EUC:{
				header( "Content-type: text/xml; charset=EUC-JP" );
				break;
			}
			default:{
				header( "Content-type: text/xml; charset=UTF-8" );
				break;
			}
		}
		// mod end 2017/01/17 H.Yasunaga ]
	} else {
		// mod start 2017/01/17 H.Yasunaga ENCパラメターに合わせたheaderの出力に変更 [
		//header( "Content-Type: application/json; charset=utf-8" ) ;
		switch($ENC) {
			case DEF_PRM_ENC_UTF8:{
				header( "Content-Type: application/json; charset=UTF-8" );
				break;
			}
			case DEF_PRM_ENC_SJIS:{
				header( "Content-Type: application/json; charset=Shift_JIS" );
				break;
			}
			case DEF_PRM_ENC_EUC:{
				header( "Content-Type: application/json; charset=EUC-JP" );
				break;
			}
			default:{
				header( "Content-Type: application/json; charset=UTF-8" );
				break;
			}
		}
		// mod end 2017/01/17 H.Yasunaga ]
	}
	echo $result;
	exit;

	/*==============================================*/
	// エラー時の出力
	/*==============================================*/
	function outputErrStatus( $rescode, $errcode, $outdata ) {
		header( "Content-Type: text/plain; charset=utf-8" );
		print $rescode.",".$errcode.":".$outdata;
		return true;
	}


	// ------------------------------------------------------------
	// ヤマト運輸 ATOKEN認証
	// ------------------------------------------------------------
	function YTCAccessCheckATOKEN($url, $atoken) {

		global $D_EMAP_ENV;

		// 検証サイト用
		if ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev') {
			global $D_APIPROXY;
			$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];

			$headers = array(
				'Authorization: Bearer '.$atoken,   //認証設定
			); 

			$options = array('http' => array(
			    'method' => 'POST',
			    'header' => implode("\r\n", $headers),
				'ignore_errors' => true,
				'proxy' => "tcp://$host",
				'request_fulluri' => true,
			));
			$contents = file_get_contents($url, false, stream_context_create($options));
			$dat = explode("\r\n\r\n",$contents);

		} //本番サイト用
		else {
			$cmd = 'wget -O - --post-data="" --header="Authorization: Bearer '.$atoken.'" '.$url;
			exec($cmd, $dat);
		}

		if ($dat && is_array($dat)) {
			$xml_arr = LoadXML(&$dat[0]);
			$MSG_ID = GetXMLVal($xml_arr, "MSG_ID");

			return $MSG_ID;
		}
		return null;
	}


?>
