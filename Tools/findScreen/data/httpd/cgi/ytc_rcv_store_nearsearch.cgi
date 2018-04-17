<?php
/*========================================================*/
// ファイル名：ytc_rcv_store_nearsearch.cgi
// 処理名：【ヤマト運輸様向け】店頭受取API
//
// 更新履歴
// 2016/10/19 Y.Matsukawa	新規作成（ytc_store_nearsearch.cgiをコピーして作成）
/*========================================================*/

	ini_set('display_errors', '0');

	$CGICD = 'y01';
	$NEARSEARCH_CGI = 'store_nearsearch.cgi';
	$CGINM = 'store_nearsearch';

	/*==============================================*/
	// コード定義
	/*==============================================*/
	/* 入力パラメータ*/
	define( 'DEF_PRM_ENC_UTF8',		'UTF8' );       // 文字コード（UTF8）
	define( 'DEF_PRM_ENC_SJIS',		'SJIS' );       // 文字コード（SJIS）
	define( 'DEF_PRM_ENC_EUC',		'EUC'  );       // 文字コード（EUC）
	define( 'DEF_PRM_PFLG_DNUM',	'1'    );       // ポイントフラグ（十進緯度経度表記）
	define( 'DEF_PRM_PFLG_MSEC',	'2'    );       // ポイントフラグ（ミリ秒緯度経度表記）
	define( 'DEF_PRM_PFLG_DMS',		'3'    );       // ポイントフラグ（度分秒緯度経度表記）
	define( 'DEF_PRM_DATUM_TOKYO', 	'TOKYO');       // 測地系（日本測地系）
	define( 'DEF_PRM_DATUM_WGS84', 	'WGS84');       // 測地系（世界測地系）
	define( 'DEF_PRM_OUTF_JSON', 	'JSON' );       // 出力形式（JSON）
	define( 'DEF_PRM_OUTF_XML', 	'XML'  );       // 出力形式（XML）

	/* リターンコード */
	define( 'ERROR_SYSTEM',				'01003' );	// 内部的な予期しない問題により要求を正しく処理できませんでした。
	define( 'ERROR_MAINTENANCE',		'10000' );	// 要求されたAPIは現在、メンテナンス中です。
	define( 'EXPIRY_ACCESS_TOKEN',		'10001' );	// アクセストークンが有効期限切れです。
	define( 'INVALID_ACCESS_TOKEN',		'10002' );	// アクセストークンが空、もしくは不正な値です。
	define( 'URGENT_MAINTENANCE',		'10003' );	// 要求されたAPIは現在、緊急メンテナンス中です。
	define( 'ERROR_TENPO_DB',			'01000' );	// データベースアクセスエラー

	define( 'INVALID_PARAMETER_LAT',	'09002' );	// 緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_LON',	'09003' );	// 経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_ZIP',	'09004' );	// 郵便番号が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_NELAT',	'09005' );	// 北東（右上）緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_NELON',	'09006' );	// 北東（右上）経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SWLAT',	'09007' );	// 南西（左下）緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SWLON',	'09008' );	// 南西（左下）経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_EWDIST',	'09009' );	// 東西距離（経度）が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SNDIST',	'09010' );	// 南北距離（緯度）が空、もしくは不正な値です。

	define( 'YAMATO03_INVALID_PARAMETER_YTC',	'99001' );	// 【ヤマト店頭受取専用】配達担当店の店舗コードが空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_F',		'99002' );	// 【ヤマト店頭受取専用】店舗種別が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_SKBN',	'99003' );	// 【ヤマト店頭受取専用】商品判定区分が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_YMD',	'99004' );	// 【ヤマト店頭受取専用】受取可能日時の起算日が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_DLV',	'99005' );	// 【ヤマト店頭受取専用】到着便数が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_CNT',	'99006' );	// 【ヤマト店頭受取専用】取得件数が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_SORT',	'99007' );	// 【ヤマト店頭受取専用】ソート順が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_ENC',	'99008' );	// 【ヤマト店頭受取専用】文字コードが空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_PFLG',	'99009' );	// 【ヤマト店頭受取専用】ポイントフラグが空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_DATUM',	'99010' );	// 【ヤマト店頭受取専用】測地系が空、もしくは不正な値です。
	define( 'YAMATO03_INVALID_PARAMETER_OUTF',	'99011' );	// 【ヤマト店頭受取専用】出力形式が空、もしくは不正な値です。
	define( 'YAMATO03_EXPIRE_COOL',				'99012' );	// 【ヤマト店頭受取専用】クール便の保管期限を過ぎています。

	define( 'YAMATO03_DIST', 30000 );		// 検索距離

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	include('d_serv_emap.inc');
	include('d_serv_ora.inc');
	include('oraDBAccess.inc');
	include('ZdcCommonFunc.inc');
	include('function.inc');
	include('xml_util.inc');
	include('chk.inc');
	include('jkn.inc');
	include('log.inc');

	require_once('store_def.inc');
	require_once('store_outf.inc');
	require_once('store_kyoten_outf.inc');

	require_once('ytc_def.inc');		// ヤマト運輸用定義
	require_once('ytc_cgi_key.inc');	// ヤマト運輸用emapCGIキー他
	require_once('function_ytc.inc');
	require_once('function_YAMATO03.inc');

	/*==============================================*/
	// ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// 初期化
	/*==============================================*/
	$status 	= DEF_RETCD_DE;		// ログ用ステータスコード（成功）
	$rescode	= '-1';				// レスポンスコード初期値（エラー）
	$errcode	= '';				// エラーコード初期値
	$outdata	= '';				// 出力結果初期値
	$log_key	= D_LOG_CGIKEY;

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$ATOKEN		= getCgiParameter('ATOKEN','');						/* アクセストークン */
	$ZIP		= getCgiParameter('ZIP','');						/* 郵便番号 */
	$LAT		= getCgiParameter('lat','');						/* 緯度 */
	$LON		= getCgiParameter('lon','');						/* 経度 */
	$YTC		= getCgiParameter('YTC','');						/* 配達担当店の店舗コード */
	$F			= getCgiParameter('F','');							/* 店舗種別 */
	$HCD		= getCgiParameter('HCD','');						/* 店舗指定 */
	$SKBN		= getCgiParameter('SKBN','0');						/* 商品判定区分(0：クール便以外(含未選択)、1：クール便) */
	$YMD		= getCgiParameter('YMD','');						/* 受取可能日時の起算日 */
	$DLV		= getCgiParameter('DLV','');						/* 到着便数 */
	$POS		= getCgiParameter('pos','1');						/* 取得位置 */
	$CNT		= intval(getCgiParameter('cnt','5'));				/* 取得件数 */
	$SORT		= getCgiParameter('sort','');						/* ソート順 */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* 文字コード */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* ポイントフラグ */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* 測地系 */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* 出力形式 */

	$suffix = ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev' ? 'test' : '');		// 検証or本番
	$CID        = 'yamato01'.$suffix;	// データ取得先企業ID
	$OPTION_CD  = 'yamato03'.$suffix;	// 課金ログに出力する企業ID
	$CUST       = 'YAMATO03';			// store_nearsearch.cgiのcustパラメータ

	/*==============================================*/
	// LOG出力用にパラメータ値を結合
	/*==============================================*/
	$parms = $LAT;
	$parms .= ' '.$LON;

	/*==============================================*/
	// enc：文字コード
	/*==============================================*/
	include('store_enc.inc');
	switch ($ENC) {
		case 'SJIS':
			$CHARSET = 'Shift_JIS';
			break;
		case 'EUC':
			$CHARSET = 'EUC-JP';
			break;
		case 'UTF8':
			$CHARSET = 'UTF-8';
			break;
	}

	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	//$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	$CgiOut = new StoreKyotenCgiOutput('', $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST);

	/*==============================================*/
	// クロスドメイン対応
	/*==============================================*/
	header('Access-Control-Allow-Origin: *');

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	// ATOKEN：アクセストークン
	if ($ATOKEN == '') {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else if (strlen($ATOKEN) > 64) {
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// YTC：配達担当店の店舗コード
	if ($YTC == '') {
		// 必須
		$status = YAMATO03_INVALID_PARAMETER_YTC;
		$CgiOut->set_debug('ytc', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else if (strlen($YTC) != 6) {
		// 6桁
		$status = YAMATO03_INVALID_PARAMETER_YTC;
		$CgiOut->set_debug('ytc', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// F：店舗種別
	if ($F == '') {
		$status = YAMATO03_INVALID_PARAMETER_F;
		$CgiOut->set_debug('f', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else if (!in_array($F, array('0', '1', '9'), true)) {
		$status = YAMATO03_INVALID_PARAMETER_F;
		$CgiOut->set_debug('f', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// SKBN：商品判定区分
	if (!in_array($SKBN, array('0', '1'), true)) {
		$status = YAMATO03_INVALID_PARAMETER_SKBN;
		$CgiOut->set_debug('skbn', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// YMD：受取可能日時の起算日
	if ($YMD == '') {
		if ($SKBN == '1') {
			// クール便の場合はYMD必須
			$status = YAMATO03_INVALID_PARAMETER_YMD;
			$CgiOut->set_debug('ymd', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	} else if (strlen($YMD) != 12 || !ctype_digit($YMD)) {
		// 12桁の半角数値のみ可
		$status = YAMATO03_INVALID_PARAMETER_YMD;
		$CgiOut->set_debug('ymd', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	} else {
		$ymd_chk = mktime(substr($YMD, 8, 2), substr($YMD, 10, 2), 0, substr($YMD, 4, 2), substr($YMD, 6, 2), substr($YMD, 0, 4));
		$ymd_chk = date('YmdHi', $ymd_chk);
		if ($ymd_chk != $YMD) {
			// 不正な日時はNG
			$status = YAMATO03_INVALID_PARAMETER_YMD;
			$CgiOut->set_debug('ymd', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		if ($SKBN == '1') {
			if (YAMATO03::dayPlus($YMD, 2) < date('Ymd')) {
				// クール便の場合、保管期限（YMD+2）を過ぎていたらエラー
				$status = YAMATO03_EXPIRE_COOL;
				$CgiOut->set_debug('ymd', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
	}
	// DLV：到着便数
	if ($DLV != '') {
		if (!in_array($DLV, array('1','2','3'), true)) {
			$status = YAMATO03_INVALID_PARAMETER_DLV;
			$CgiOut->set_debug('dlv', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}
	// cnt：取得件数
	if ($CNT < 1 || $CNT > 100) {
		$status = YAMATO03_INVALID_PARAMETER_CNT;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// sort：ソート順
	if ($SORT != '' && $SORT != '1') {
		$status = YAMATO03_INVALID_PARAMETER_SORT;
		$CgiOut->set_debug('sort', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// pflg：ポイントフラグ
	if (!in_array($PFLG, array(DEF_PRM_PFLG_DNUM, DEF_PRM_PFLG_MSEC, DEF_PRM_PFLG_DMS), true)) {
		$status = YAMATO03_INVALID_PARAMETER_PFLG;
		$CgiOut->set_debug('pflg', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// datum：ポイントフラグ
	if (!in_array($DATUM, array(DEF_PRM_DATUM_TOKYO, DEF_PRM_DATUM_WGS84), true)) {
		$status = YAMATO03_INVALID_PARAMETER_DATUM;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// outf：ポイントフラグ
	if (!in_array($OUTF, array(DEF_PRM_OUTF_JSON, DEF_PRM_OUTF_XML), true)) {
		$status = YAMATO03_INVALID_PARAMETER_OUTF;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// ATOKEN認証
	/*==============================================*/
	$result = YTC::authToken($ATOKEN);
	//$result = 'SUCCESS_AUTH_ALLOW';//※※Debug※※
	if($result == 'ERROR_MAINTENANCE'){
		// エラー（APIメンテナンス中）
		$status = ERROR_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result == 'URGENT_MAINTENANCE'){
		// エラー（API緊急メンテナンス中）
		$status = URGENT_MAINTENANCE;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result == 'EXPIRY_ACCESS_TOKEN'){
		// エラー（アクセストークン有効期限切れ）
		$status = EXPIRY_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result == 'ERROR_SYSTEM'){
		// エラー（システムエラー）
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;

	}else if($result != 'SUCCESS_AUTH_ALLOW'){
		// エラー（アクセストークンエラー）
		$status = INVALID_ACCESS_TOKEN;
		$CgiOut->set_debug('atoken', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// DB接続オープン
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('DBopen', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// 配達担当店の緯度経度を取得
	/*==============================================*/
	$sql = 'select LAT,LON';
	$sql .= ' from KYOTEN_TBL';
	$sql .= ' where CORP_ID = :CORP_ID';
	$sql .= ' and KYOTEN_ID = :KYOTEN_ID';
	$stmt = oci_parse($dba->conn, $sql);
	if (!$stmt) {
		//$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('配達担当店取得', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (!oci_bind_by_name($stmt, ':CORP_ID', $CID, 15)) {
		$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('配達担当店取得', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (!oci_bind_by_name($stmt, ':KYOTEN_ID', $YTC, 15)) {
		$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('配達担当店取得', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (!oci_execute($stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = ERROR_TENPO_DB;
		$CgiOut->set_debug('配達担当店取得', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	$result = oci_fetch_assoc($stmt);
	$dba->free($stmt);
	if (!$result) {
		$dba->close();
		$status = YAMATO03_INVALID_PARAMETER_YTC;
		$CgiOut->set_debug('sort', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	$YTC_LAT = $result['LAT'];
	$YTC_LON = $result['LON'];
	$YTC_DIST = 150000;

	/*==============================================*/
	// DB接続クローズ
	/*==============================================*/
	$dba->close();

	/*==============================================*/
	// 絞り込み条件
	/*==============================================*/
	$FILTER = '';
	$cond_ytc = 'COL_01:1 AND (COL_10:A OR COL_10:B)';
	$cond_shp = 'COL_01:2 AND ((COL_39!:Z96 AND COL_39!:Z97) OR COL_39:@@NULL@@)';
	switch ($F) {
		// 直営店
		case '1':
			$FILTER = $cond_ytc;
			break;
		// 取扱店
		case '0':
			if ($SKBN == '1') {
				// 取扱店でクール便はNG
				$FILTER = '('.$cond_ytc.') AND ('.$cond_shp.')';//※0件になる
			} else {
				$FILTER = $cond_shp;
			}
			break;
		// 全店舗
		default:
			if ($SKBN == '1') {
				$FILTER = $cond_ytc;
			} else {
				$FILTER = '('.$cond_ytc.') OR ('.$cond_shp.')';
			}
			break;
	}
	if ($HCD != '') {
		$FILTER = '('.$FILTER.') AND KYOTEN_ID:'.$HCD;
	}

	/*==============================================*/
	// 実行用にパラメータ値を結合
	/*==============================================*/
	$parms =  '?cid='.		$CID;
	if ($HCD == '') {
		$parms .= '&lat='.		urlencode($LAT);
		$parms .= '&lon='.		urlencode($LON);
		$parms .= '&zip='.		urlencode($ZIP);
		$parms .= '&ewdist='.	YAMATO03_DIST;
		$parms .= '&sndist='.	YAMATO03_DIST;
		$parms .= '&absdist='.	YAMATO03_DIST;
	} else {
		$LAT = 128441320;
		$LON = 503169540;
		$NELAT = 163998619;
		$NELON = 554348015;
		$SWLAT = 73514227;
		$SWLON = 442566224;
		if ($DATUM == DEF_PRM_DATUM_WGS84) {
			cnv_transDatum($LAT, $LON, TKY_TO_WGS84, $LAT, $LON);
			cnv_transDatum($NELAT, $NELON, TKY_TO_WGS84, $NELAT, $NELON);
			cnv_transDatum($SWLAT, $SWLON, TKY_TO_WGS84, $SWLAT, $SWLON);
		}
		$parms .= '&lat='.$LAT;
		$parms .= '&lon='.$LON;
		$parms .= '&nelat='.$NELAT;
		$parms .= '&nelon='.$NELON;
		$parms .= '&swlat='.$SWLAT;
		$parms .= '&swlon='.$SWLON;
	}
	$parms .= '&filter='.	urlencode($FILTER);
	$parms .= '&pos='.		$POS;
	$parms .= '&cnt='.		$CNT;
	$parms .= '&knsu='.		$CNT;
	$parms .= '&enc='.		urlencode($ENC);
	$parms .= '&pflg='.		urlencode($PFLG);
	$parms .= '&datum='.	urlencode($DATUM);
	$parms .= '&outf='.		urlencode($OUTF);
	$parms .= '&cust='.		'YAMATO03';
	$parms .= '&logcid='.	$OPTION_CD;
	$parms .= '&exarea='.	$YTC_LAT.','.$YTC_LON.','.$YTC_DIST;
	$parms .= '&carg[ytc]='.urlencode($YTC);
	$parms .= '&carg[skbn]='.urlencode($SKBN);
	$parms .= '&carg[ymd]='.urlencode($YMD);
	$parms .= '&carg[dlv]='.urlencode($DLV);
	$parms .= '&carg[sort]='.urlencode($SORT);

	/*==============================================*/
	// store_nearsearch.cgiコール
	/*==============================================*/
	unset($result);
	$CGI = 'http://127.0.0.1/cgi/'.$NEARSEARCH_CGI.$parms;
	$result = file_get_contents($CGI);
	if (!$result) {
		$status = ERROR_SYSTEM;
		$CgiOut->set_debug('CGI call', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	// 結果出力
	if ( $OUTF != 'JSON' ) {
		header( 'Content-type: text/xml; charset='.$CHARSET );
	} else {
		header( 'Content-Type: application/json; charset='.$CHARSET ) ;
	}
	echo $result;

	exit;
?>
