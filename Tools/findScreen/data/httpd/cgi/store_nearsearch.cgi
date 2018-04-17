<?php
/*========================================================*/
// ファイル名：store_nearsearch.cgi
// 処理名：店舗ID検索
//
// 更新履歴
// 2011/12/16 H.Nakamura	新規作成
// 2013/03/11 Y.Matsukawa	リアルタイムデータ
// 2013/12/20 H.Osamoto		データ参照先企業ID取得
// 2014/01/06 H.Osamoto		許可リファラ「null」機能追加
// 2015/02/26 Y.Matsukawa	リクエストパラメータ（zip）追加
// 2015/06/11 H.Osamoto		searchzip.cgi呼び出し時にソートパラメータ指定
// 2016/01/14 Y.Matsukawa	多言語サイトからの呼び出しに対応（内部接続）
// 2016/04/25 T.Yoshino		出力されるタグの追加のためのパラメータの追加、yamato01用タグの対応
// 2016/10/19 Y.Matsukawa	ヤマト運輸向け店頭受取API（ytc_store_nearsearch.cgi）対応
// 2016/12/12 H.Yasunaga	ヤマトロッカー対応
//							ロッカー店舗に対してヤマトロッカー満空APIのリクエストを行い、結果を設定する
// 2017/02/13 Y.Matsukawa	取得カラム指定
// 2017/03/23 Y.Matsukawa	不具合修正：1000件取得時にメモリーエラー
// 2017/05/11 H.Yasunaga	ヤマトロッカーセキュリティコード対応
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y01';

	/*==============================================*/
	// CGI名
	/*==============================================*/
	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

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
	// mod 2016/04/25 T.Yoshino [
	//if ( $_GET['cust'] == "YAMATO01" ) {		mod 2016/10/19 Y.Matsukawa
	if ($_GET['cust'] == 'YAMATO01' || $_GET['cust'] == 'YAMATO03') {
		$CGICD = "";
		define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
		define( 'DEF_RETCD_DEND', '00000' );       // 条件に見合うデータあり（後続データあり）
		define( 'DEF_RETCD_DNE',  '00001' );       // 条件に見合うデータなし
		define( 'DEF_RETCD_AERR', '01001' );       // 認証エラー
		define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
		define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
		define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
		define( 'DEF_RETCD_PERR1','01002' );       // 入力パラメータエラー(必須項目NULL)
		define( 'DEF_RETCD_PERR2','19200' );       // 入力パラメータエラー(構文エラー)
		define( 'DEF_RETCD_PERR3','19200' );       // 入力パラメータエラー(組み合わせエラー)
		define( 'ERROR_SYSTEM',   '01003' );       // 内部的な予期しない問題により要求を正しく処理できませんでした。
	} else {
		define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
		define( 'DEF_RETCD_DEND', '00001' );       // 条件に見合うデータあり（後続データあり）
		define( 'DEF_RETCD_DNE',  '11009' );       // 条件に見合うデータなし
		define( 'DEF_RETCD_AERR', '12009' );       // 認証エラー
		define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
		define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
		define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
		define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
		define( 'DEF_RETCD_PERR2','19200' );       // 入力パラメータエラー(構文エラー)
		define( 'DEF_RETCD_PERR3','19200' );       // 入力パラメータエラー(組み合わせエラー)
	}
	define( 'INVALID_PARAMETER',		'09000' );	// ｘｘｘが空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_CID',	'09001' );	// 企業IDが空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_LAT',	'09002' );	// 緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_LON',	'09003' );	// 経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_ZIP',	'09004' );	// 郵便番号が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_NELAT',	'09005' );	// 北東（右上）緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_NELON',	'09006' );	// 北東（右上）経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SWLAT',	'09007' );	// 南西（左下）緯度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SWLON',	'09008' );	// 南西（左下）経度が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_EWDIST',	'09009' );	// 東西距離（経度）が空、もしくは不正な値です。
	define( 'INVALID_PARAMETER_SNDIST',	'09010' );	// 南北距離（緯度）が空、もしくは不正な値です。
	// mod 2016/04/25 T.Yoshino ]

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	include('d_serv_emap.inc');
	include('store_def.inc'); 
	include('store_outf.inc');			// 出力クラス定義
	include('ZdcCommonFuncAPI.inc');	// 共通関数
	include('function.inc');			// 共通関数
	include('d_serv_ora.inc');
	include('oraDBAccess.inc');
	include('chk.inc');				// データチェック関連
	include('log.inc');				// ログ出力
	include('auth.inc');				// 簡易認証
	include("jkn.inc");				// 絞り込み条件編集
	include('store_kyoten_outf.inc');
	include('rd_sql.inc');		// add 2013/03/11 Y.Matsukawa
	@include('function_'.$_GET['cust'].'.inc');			// カスタマイズ関数		add 2016/10/19 Y.Matsukawa

	/*==============================================*/
	// エラー出力を明示的にOFF
	/*==============================================*/
	//	error_reporting(E_ALL^E_NOTICE);
	//	error_reporting(0);
	if ($D_DEBUG) ini_set('display_errors', '1');		// add 2013/03/11 Y.Matsukawa

	/*==============================================*/
	// 初期化
	/*==============================================*/
	// ステータス(リターンコード)
	if (!isset($status)){
		 $status = '00000';
	}

	/*==============================================*/
	// ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid','');						/* 企業ID */
	$LAT		= getCgiParameter('lat','');						/* 緯度 */
	$LON		= getCgiParameter('lon','');						/* 経度 */
	$ZIP		= getCgiParameter('zip','');						/* 郵便番号 */		// add 2015/02/26 Y.Matsukawa
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
	// add 2016/01/14 Y.Matsukawa [
	$INTID		= getCgiParameter('intid', '');						/* 内部利用時のID */
	$OPT		= getCgiParameter('opt', '');						/* 内部利用時の企業ID */
	$KNSU		= getCgiParameter('knsu', '');						/* 最大件数 */
	$ABSDIST	= getCgiParameter('absdist', '');					/* 円範囲検索 */
	$EXKID		= getCgiParameter('exkid', '');						/* 除外店舗指定 */
	// add 2016/01/14 Y.Matsukawa ]
	// add 2016/10/19 Y.Matsukawa [
	$EXAREA		= getCgiParameter('exarea', '');					/* 除外エリア指定(緯度,経度,距離) */
	if ($EXAREA != '') {
		$EXAREA = explode(',', $EXAREA);
	}
	// add 2016/10/19 Y.Matsukawa ]
	// add 2016/04/25 T.Yoshino [
	$PMAPURL	= getCgiParameter('pmapurl', '');					/* pc_map_urlタグ出力判断 */
	$SMAPURL	= getCgiParameter('smapurl', '');					/* smt_map_urlタグ出力判断 */
	$SITE_ID	= getCgiParameter('SITE_ID', '');					/* 連携サイトID */
	$CUST		= getCgiParameter('cust', '');						/* 対象企業ﾊﾟﾗﾒｰﾀ */
	// add 2016/04/25 T.Yoshino ]
	// add 2016/10/19 Y.Matsukawa [
	// カスタマイズパラメータ（配列指定）
	// （例）&carg[id]=123&carg[name]=ABC → $c_id, $c_name
	if (isset($_GET['carg'])) {
		$arr = $_GET['carg'];
		foreach ($arr as $an => $av) {
			${'c_'.$an} = $av;
		}
	}
	// ログ出力企業ID
	$LOGCID		= getCgiParameter('logcid', '');
	// add 2016/10/19 Y.Matsukawa ]
	$COLS		= getCgiParameter('cols', '');						/* 取得カラム指定 */		// add 2017/02/13 Y.Matsukawa

	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	// 課金ログに出力する企業ID
	//$OPTION_CD = $CID;		mod 2016/01/14 Y.Matsukawa
	$OPTION_CD = ($INTID != '')?$OPT:$CID;
	if ($LOGCID != '') $OPTION_CD = $LOGCID;		// add 2016/10/19 Y.Matsukawa
	
	// add 2016/04/25 T.Yoshino [
	// pc_map_url、smt_map_urlタグ出力判断
	$arr_opt_flg = array();
	$arr_opt_flg['pc_map']	 = ($PMAPURL != '')? 1: "";
	$arr_opt_flg['smt_map']	 = ($SMAPURL != '')? 1: "";
	$arr_opt_flg['site_id']	 = $SITE_ID;
	$arr_opt_flg['cust']	 = $CUST;
	// add 2016/04/25 T.Yoshino ]

	include('store_enc.inc');			// 文字コード変換

	// add 2016/10/19 Y.Matsukawa
	/*==============================================*/
	// ヤマト運輸店頭受取APIカスマイザ
	/*==============================================*/
	if ($CUST == 'YAMATO03') {
		$yamato03 = new YAMATO03($c_ytc, $c_skbn, $c_ymd, $c_dlv);
	}

	// add start 2016/12/12 H.Yasunaga ロッカー対応 [
	/*==============================================*/
	// ヤマト運輸満空APIカスタマイザ
	/*==============================================*/
	if ($CUST == 'YAMATO01') {
		// cargパラメータを配列で取得し変数展開した値を使う
		// ytc_store_nearsearchで &carg[SDATA]=xxx&carg[HZIP]=yyy&carg[BSKBN]=zzz の形でリクエストを作っている
		// $c_SDATA	:出荷予定日
		// $c_HZIP	:発地郵便番号
		// $c_BSKBN	:ボックスサイズ区分
		// $PFLG	:ポイントフラグ(郵便番号逆引きで使用するため)
		// $DATUM	:測地系(郵便番号逆引きで使用するため)
		// ここではインスタンスの生成のみ 拠点の検索が終わった後でロッカー満空APIを利用する
		if (empty($c_SDATE) != ture && empty($c_HZIP) != true && empty($c_BSKBN) != true) {
			// 出荷予定日・発地郵便番号・ボックスサイズ区分がある場合に生成
			$yamato01 = new YAMATO01($c_SDATE, $c_HZIP, $c_BSKBN, $PFLG, $DATUM);
		}
	}
	
	// add 2015/02/26 Y.Matsukawa
	/*==============================================*/
	// 郵便番号から位置取得
	/*==============================================*/
	if (($LAT == '' || $LON == '') && $ZIP != '') {
		// 郵便番号検索
		$cgi = $D_SSAPI["searchzip"];
		//	$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s", 1, 1, 'EUC', urlencode($ZIP), $DATUM, 'TSV');	mod 2015/06/11 H.Osamoto
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

	/*==============================================*/
	// LOG出力用にパラメータ値を結合
	/*==============================================*/
	$parms = $LAT;
	$parms .= ' '.$LON;
	$parms .= ' '.$SWLAT;
	$parms .= ' '.$SWLON;
	$parms .= ' '.$NELAT;
	$parms .= ' '.$NELON;
	$parms .= ' '.$log_jkn;

	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST );
	
	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 内部接続フラグ */		// add 2016/01/14 Y.Matsukawa
	if ($INTID != '') {
		if(!in_array($INTID, $D_STORE_INTID)) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('intid', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
	}
	/* ログ出力用キー */		// add 2016/01/14 Y.Matsukawa
	if ($INTID != '') {
		$log_key = '299912312359592'.$INTID;
	} else {
		$log_key = D_LOG_CGIKEY;
	}
	/* 企業ID */
	if ($CID == '') {
//		$status = DEF_RETCD_PERR1;
		$status = INVALID_PARAMETER_CID;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 緯度 */
	if ($LAT == '') {
//		$status = DEF_RETCD_PERR1;
		$status = INVALID_PARAMETER_LAT;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_debug('lat', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 経度 */
	if ($LON == '') {
//		$status = DEF_RETCD_PERR1;
		$status = INVALID_PARAMETER_LON;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_debug('lon', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 範囲 or 距離 */
	if ($NELAT != '' || $NELON != '' || $SWLAT != '' || $SWLON != '') {
		/* 北東(右上)緯度 */
		if ($NELAT == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_NELAT;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('nelat', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* 北東(右上)経度 */
		if ($NELON == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_NELON;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('nelon', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* 南西(左下)緯度*/
		if ($SWLAT == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_SWLAT;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('swlat', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* 南西(左下)経度*/
		if ($SWLON == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_SWLON;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('swlon', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$EWDIST = '';
		$SNDIST = '';
	} else {
		/* 東西距離 */
		if ($EWDIST == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_EWDIST;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('ewdist', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* 東西距離 1〜 50000 */
		if ($INTID == '') {		// add 2016/01/14 Y.Matsukawa
			if(!($EWDIST > 0 && $EWDIST <= 50000)) {
//				$status = DEF_RETCD_PERR2;
				$status = INVALID_PARAMETER_EWDIST;	// mod 2016/04/25 T.Yoshino 
				$CgiOut->set_debug('ewdest', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
		/* 南北距離 */
		if ($SNDIST == '') {
//			$status = DEF_RETCD_PERR1;
			$status = INVALID_PARAMETER_SNDIST;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('sndist', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		/* 南北距離 1〜 50000 */
		if ($INTID == '') {		// add 2016/01/14 Y.Matsukawa
			if(!($SNDIST > 0 && $SNDIST <= 50000)) {
//				$status = DEF_RETCD_PERR2;
				$status = INVALID_PARAMETER_SNDIST;	// mod 2016/04/25 T.Yoshino 
				$CgiOut->set_debug('sndist', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
	}
	/* 取得開始位置*/
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 取得件数 */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT > 1000) {
		$CNT = 1000;
	}
	/* 最大件数 */		// add 2016/01/14 Y.Matsukawa
	if ($KNSU != '') {
		$KNSU = intval($KNSU);
		if (!chk_knsu_max($KNSU)) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('knsu', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}	
	}
	/* 文字コード */
	if ($INPUT_ENC  != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC  != DEF_PRM_ENC_EUC &&
		$INPUT_ENC  != DEF_PRM_ENC_UTF8) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('enc', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* ポイントフラグ */
	if ($PFLG != DEF_PRM_PFLG_DNUM && 
		$PFLG != DEF_PRM_PFLG_MSEC &&
		$PFLG != DEF_PRM_PFLG_DMS) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pflg', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 測地系 */
	if ($DATUM != DEF_PRM_DATUM_TOKYO && 
		$DATUM != DEF_PRM_DATUM_WGS84) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 出力形式 */
	if ($OUTF != DEF_PRM_OUTF_JSON && $OUTF != DEF_PRM_OUTF_XML) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// DB接続オープン
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		$CgiOut->set_debug('DBopen', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// サービス期間
	/*==============================================*/
	if ($INTID == '') {		// 内部接続の場合はチェックしない	add 2016/01/14 Y.Matsukawa
		$url = sprintf("%s?cid=%s&opt=%s",$D_SSAPI["getsdate"], $D_CID, $CID);
		$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
		$service = explode("\t",$dat[0]);
		if($service[0] == "89000000") {
			$rec = explode("\t",$dat[1]);
			$flg = intval($rec[0]);
		}
		if(!isset($flg) || (isset($flg) && $flg == 0)) {	
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('サービス期間', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}

	/*==============================================*/
	// CGI利用許可
	/*==============================================*/
	if ($INTID == '') {		// 内部接続の場合はチェックしない	add 2016/01/14 Y.Matsukawa
		$sql  = " SELECT"; 
		$sql .= "    VALUE";
		$sql .= " FROM";
		$sql .= "    EMAP_PARM_TBL";
		$sql .= " WHERE";
		$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
		$sql .= " AND KBN  = 'C_EMAP_KBN'";
		$sql .= " AND VALUE  = 'S'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('CGI利用許可', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if($data['VALUE'] == '0') {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('CGI利用許可', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		} else {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('CGI利用許可', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$dba->free($stmt);
	}

	/*==============================================*/
	// SSL認証、IPチェック、リファラチェック
	/*==============================================*/
	if ($INTID == '') {		// 内部接続の場合はチェックしない	add 2016/01/14 Y.Matsukawa
		$sql  = " SELECT"; 
		//	$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER";	mod 2014/01/06 H.Osamoto
		$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER, REFERER_NULL";
		$sql .= " FROM";
		$sql .= "    EMAP_CGI_CONF_TBL";
		$sql .= " WHERE";
		$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('SSL認証許可', __LINE__);
			$CgiOut->set_status($status, 0, 0); 
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			/* SSL接続許可 */
			if (isset($data['SSL_ACCESS'])) {
				switch($data['SSL_ACCESS']) {
					// SSL接続不許可
					case '0' :
						if($_SERVER['HTTPS'] == 'on') {
							$dba->free($stmt);
							$dba->close();
							$status = DEF_RETCD_AERR;
							$CgiOut->set_debug('SSL認証許可', __LINE__);
							$CgiOut->set_status($status, 0, 0);
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						}
						break;
					// SSL接続許可
					case '1' :
						break;
					// SSL接続必須
					case '2' :
						if($_SERVER['HTTPS'] != 'on') {
							$dba->free($stmt);
							$dba->close();
							$status = DEF_RETCD_AERR;
							$CgiOut->set_debug('SSL認証許可', __LINE__);
							$CgiOut->set_status($status, 0, 0); 
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						}
						break;
					defailt:
						brak;
				}
			} else {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_AERR;
				$CgiOut->set_debug('SSL認証許可', __LINE__);
				$CgiOut->set_status($status, 0, 0); 
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}

			$referer_list = explode(";",  $data['ALLOW_REFERER']);

			/* IPチェック */
			if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
				if (!ip_check2($data['ALLOW_IP'], $_SERVER['REMOTE_ADDR'], ';')) {
					/* リファラチェック */
					if (!referer_check(&$referer_list, $_SERVER['HTTP_REFERER'])) {
						// add 2014/01/06 H.Osamoto [
						/* リファラnull許可チェック */
						if (!referer_null_check($data['REFERER_NULL'], $_SERVER['HTTP_REFERER'])) {
						// add 2014/01/06 H.Osamoto ]
							$dba->free($stmt);
							$dba->close();
							$status = DEF_RETCD_AERR;
							$CgiOut->set_debug('IPチェック', __LINE__);
							$CgiOut->set_status($status, 0, 0);
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						// add 2014/01/06 H.Osamoto [
						}
						// add 2014/01/06 H.Osamoto ]
					}
				}
			}
		} else {
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('認証エラー', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$dba->free($stmt);
	}

	// add 2013/12/20 H.Osamoto
	/*==============================================*/
	// データ参照先企業ID取得
	/*==============================================*/
	$CID = getDataCid($dba, $CID);

	// add 2013/03/11 Y.Matsukawa
	/*==============================================*/
	// RD利用設定
	/*==============================================*/
	$use_rd = isRDAvailable($dba, $CID);

	/*==============================================*/
	// 座標表記形式及び測地系の変換
	/*==============================================*/
	$LAT_DEC = $LAT;
	$LON_DEC = $LON;
	$LAT_MS;
	$LON_MS;
	$res = cnv_ll2lldms($LAT, $LON, $DATUM, &$LAT_MS, &$LON_MS);
	if (!$res) {
		// 緯度経度不正
//		$status = DEF_RETCD_PERR2;
		$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->set_debug('緯度経度', __LINE__);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($NELAT != '' && $NELON != '') {
		$res = cnv_ll2lldms($NELAT, $NELON, $DATUM, &$NELAT, &$NELON);
		if (!$res) {
			// 緯度経度不正
//			$status = DEF_RETCD_PERR2;
			$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('緯度経度', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}
	if ($SWLAT != '' && $SWLON != '') {
		$res = cnv_ll2lldms($SWLAT, $SWLON, $DATUM, &$SWLAT, &$SWLON);
		if (!$res) {
			// 緯度経度不正
//			$status = DEF_RETCD_PERR2;
			$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
			$CgiOut->set_debug('緯度経度', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}

	// add 2016/10/19 Y.Matsukawa
	/*==============================================*/
	// 中心緯度経度を出力
	/*==============================================*/
	if ($CUST == 'YAMATO03') {
		$CgiOut->set_centerlatlon($LAT_MS, $LON_MS, $DATUM);
	}

	/*==============================================*/
	// カラム名リスト取得 
	/*==============================================*/
	/* クエリ生成 */
	$sql  = " SELECT"; 
	$sql .= "    COL_NAME, VAL_KBN, ITEM_NAME";
	$sql .= " FROM";
	$sql .= "    KYOTEN_ITEM_TBL";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
	// add 2017/02/13 Y.Matsukawa [
	if ($COLS != '') {
		$COLS = explode(',', $COLS);
		for ($i = 0; $i < count($COLS); $i++) {
			$COLS[$i] = "'".str_replace("'", "", $COLS[$i])."'";
		}
		$sql .= " AND COL_NAME in (".implode(',', $COLS).")";
	} else {
	// add 2017/02/13 Y.Matsukawa ]
		$sql .= " AND LIST_KBN = 1";
	}
	$sql .= " ORDER BY DISP_NUM";
	/* クエリ発行 */
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 結果セット保持 */
	$arr_item = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$arr_item[] = $data;
	}
	$dba->free($stmt);

	/*==============================================*/
	// 区分項目の名称取得
	/*==============================================*/
	$arr_kbn = array();
	$arr_item_val[$item['COL_NAME']] = array();
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			/* クエリ生成 */
			$sql_kbn  = " SELECT";
			$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
			$sql_kbn .= " FROM";
			$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
			$sql_kbn .= " WHERE";
			$sql_kbn .= " CORP_ID = '".escapeOra($CID)."'";
			$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
			$sql_kbn .= " ORDER BY ITEM_VAL";
			/* クエリ発行 */
			if (!$dba->sqlExecute($sql_kbn, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('DB検索', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
			/* 結果セット格納 */
			$arr_kbn[$item['COL_NAME']] = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
				$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
			}
			$dba->free($stmt);
		}
	}

	$arr_kid = array();		// add 2013/03/11 Y.Matsukawa

	/*==============================================*/
	// 最寄拠点検索
	/*==============================================*/
	/* サブクエリ生成 */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
	$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $LAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
	$sql_sub_near .= " + POWER( ABS( LON - $LON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
	/*  new 表示フラグ分 */
	$sql_sub_near .= " CASE";
	$sql_sub_near .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
	$sql_sub_near .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql_sub_near .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
	$sql_sub_near .= "         THEN '1'";
	$sql_sub_near .= "         ELSE '0'";
	$sql_sub_near .= " END AS BFLG";
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			$sql_sub_near .= ", ".$item['COL_NAME'];
		}
	}
	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    KYOTEN_TBL K";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
	// add 2016/01/14 Y.Matsukawa [
	if ($EXKID != '') {
		$sql_sub_near .= " AND KYOTEN_ID != '$EXKID' ";
	}
	// add 2016/01/14 Y.Matsukawa ]
	
	// add 2017/05/11 H.Yasunaga ヤマトロッカーセキュリティコード対応 [
	if ($CUST == 'YAMATO01' && $yamato01) {
		$securityCodeGroupNO = "1";	// RDデータのセキュリティコードのグループ番号
		$securityCodeItemNo = "1";	// RDデータのセキュリティコードの項目番号
		$sql_sub_near .= " AND KYOTEN_ID NOT IN (";
		$sql_sub_near .= " SELECT G.KYOTEN_ID ";
		$sql_sub_near .= " FROM RD_ITEM_DEF_TBL I, RD_GROUP_DEF_TBL F, RD_DATA_TBL D, RD_GROUP_TBL G ";
		$sql_sub_near .= " WHERE G.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND F.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND D.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND I.CORP_ID = '".escapeOra($CID)."'";
		$sql_sub_near .= " AND G.GROUP_NO = F.GROUP_NO ";
		$sql_sub_near .= " AND G.GROUP_NO = D.GROUP_NO ";
		$sql_sub_near .= " AND G.GROUP_NO = I.GROUP_NO ";
		$sql_sub_near .= " AND D.KYOTEN_ID = G.KYOTEN_ID ";
		$sql_sub_near .= " AND I.ITEM_NO = D.ITEM_NO ";
		$sql_sub_near .= " AND I.DEL_FLG = '0' ";
		$sql_sub_near .= " AND ( ";
		$sql_sub_near .= 		" F.USE_KIKAN = '0' ";
		$sql_sub_near .= 		" or ( ";
		$sql_sub_near .= 				" nvl(to_char(G.ST_DT,'yyyymmddhh24'),'0') <= to_char(sysdate,'yyyymmddhh24') ";
		$sql_sub_near .= 				" and nvl(to_char(G.ED_DT,'yyyymmddhh24'),'9999999999') > to_char(sysdate,'yyyymmddhh24') ";
		$sql_sub_near .= 			" ) ";
		$sql_sub_near .= 	" ) ";
		$sql_sub_near .= " AND G.GROUP_NO = '" . escapeOra($securityCodeGroupNO) . "'";
		$sql_sub_near .= " AND I.ITEM_NO = '" . escapeOra($securityCodeItemNo) . "'";
		$sql_sub_near .= " AND D.TXT_DATA IS NOT NULL ";
		$sql_sub_near .= ") ";
	}
	// add 2017/05/11 H.Yasunaga ]
	
	if ($SWLAT) {
		$sql_sub_near .= " AND LAT >= ".$SWLAT;
		$sql_sub_near .= " AND LAT <= ".$NELAT;
		$sql_sub_near .= " AND LON >= ".$SWLON;
		$sql_sub_near .= " AND LON <= ".$NELON;
	} else {
		$sql_sub_near .= " AND LAT >= (".$LAT_MS." - ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
		$sql_sub_near .= " AND LAT <= (".$LAT_MS." + ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
		$sql_sub_near .= " AND LON >= (".$LON_MS." - ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
		$sql_sub_near .= " AND LON <= (".$LON_MS." + ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
	}
	// add 2016/10/19 Y.Matsukawa [
	// 除外エリア
	if (is_array($EXAREA)) {
		$sql_sub_near .= " AND LAT >= (".$EXAREA[0]." - ((300000 / (9 * 1000)) * ".$EXAREA[2].")) ";
		$sql_sub_near .= " AND LAT <= (".$EXAREA[0]." + ((300000 / (9 * 1000)) * ".$EXAREA[2].")) ";
		$sql_sub_near .= " AND LON >= (".$EXAREA[1]." - ((450000 / (11 * 1000)) * ".$EXAREA[2].")) ";
		$sql_sub_near .= " AND LON <= (".$EXAREA[1]." + ((450000 / (11 * 1000)) * ".$EXAREA[2].")) ";
	}
	// add 2016/10/19 Y.Matsukawa ]
	$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	if ($FILTER_sql != '') {
		$sql_sub_near .= " AND ".$FILTER_sql;
	}
	$FILTER_sql = f_dec_convert($FILTER_sql);
	$sql_sub_near .= " order by KYORI, KYOTEN_ID, CORP_ID";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
	// add 2016/01/14 Y.Matsukawa [
	$sql_near_whr = '';
	if ($KNSU != '') {
		$sql_near_whr .= " WHERE ROWNUM <= $KNSU";
	}
	if ($ABSDIST != '') {
		$sql_near_whr .= ($sql_near_whr == '' ? " WHERE " : " AND ");
		//$sql_near_whr .= "SQRT(KYORI) <= $ABSDIST";		mod 2016/10/19 Y.Matsukawa
		$sql_near_whr .= "KYORI <= $ABSDIST";
	}
	$sql_near .= $sql_near_whr;
	// add 2016/01/14 Y.Matsukawa ]
	// ヒット件数取得
	$hit_num = 0;
	$stmt = null;
	$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql_near.")";
	if (!$dba->sqlExecute($sql_count, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['HITCNT'];
	}
	$dba->free($stmt);
	// データ取得
	$rec_num = 0;
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data = "SELECT * FROM (".$sql_near.")";
		$sql_data .= " where rn >= ".$POS;
		$to = $POS+$CNT-1;
		$sql_data .= " and rn <= ".$to;
		$stmt = null;
		if (!$dba->sqlExecute($sql_data, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('DB検索', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		// add 2017/03/23 Y.Matsukawa [
		// 大量データ返却時のメモリー不足回避
		if ($CNT > 500 && $hit_num > 500) ini_set('memory_limit', '16M');
		dbl("memory_limit=".ini_get('memory_limit'));
		// add 2017/03/23 Y.Matsukawa ]
		while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			if ($DATUM == DEF_PRM_DATUM_WGS84) {
				// 測地系の変換（TOKYO=>WGS84）
				$res = cnv_transDatum($data['LAT'], $data['LON'], TKY_TO_WGS84, $w_lat, $w_lon);
				if ($res) {
					$data['LAT'] = $w_lat;
					$data['LON'] = $w_lon;
				}
			}
			// 区分項目の名称をセット
			if (count($arr_item) > 0) {
				foreach ($arr_item as $item) {
					$colnm = $item['COL_NAME'];
					if (isset($data[$colnm])) {
						$val = $data[$colnm];
						if ($val != '') {
							if ($arr_kbn[$colnm][$val] != '') {
								$data[$colnm.'_name'] = $arr_kbn[$colnm][$val];
							}
						}
					}
				}
			}
			// add 2016/04/25 T.Yoshino [
			// yamatoEC連携
			if ( $CUST == "YAMATO01" ) {
				if( $data['COL_01'] == '1' ){										//直営店限定処理
					$data['COL_11'] = $data['KYOTEN_ID'];
					$strB2Name = mb_convert_kana($data['NAME'], "rns", "EUC-JP");	// 全角英数を半角に
					$data['COL_47'] = str_replace( " ", "", $strB2Name );
					$strB2Addr = mb_convert_kana($data['ADDR'], "rns", "EUC-JP");	// 全角英数を半角に
					$data['COL_48'] = str_replace( " ", "", $strB2Addr );
					$data['COL_49'] = $data['KYOTEN_ID'];
					if ( ( strlen( $data['NAME'] ) + strlen( $data['ADDR'] ) ) >= 77 ) {
						$data['COL_50'] = "1";
					} else {
						$data['COL_50'] = "0";
					}
				}
			}
			// add 2016/04/25 T.Yoshino ]
			// add 2016/10/19 Y.Matsukawa [
			// 【ヤマト運輸】店頭受取API
			if ($CUST == 'YAMATO03' && $yamato03) {
				$data['YAMATO03_DYMD'] = $yamato03->getRcvDate($data);	// 受取可能日時
				$data['YAMATO03_KYMD'] = $yamato03->getKeepDate($data);	// 保管期限
			}
			// add 2016/10/19 Y.Matsukawa ]
			$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		$rec_num = count($arr_kyoten);
		// 2016/10/19 Y.Matsukawa [
		// 【ヤマト運輸】店頭受取API
		if ($CUST == 'YAMATO03' && $yamato03 && $c_sort == '1') {
			// 受取可能日時（昇順）で並べ替え
			usort($arr_kyoten, function ($a, $b) {
				if ($a['YAMATO03_DYMD'] == $b['YAMATO03_DYMD']) {
					if (intval($a['KYORI']) == intval($b['KYORI'])) return 0;
					return (intval($a['KYORI']) < intval($b['KYORI'])) ? -1 : 1;
				}
				return ($a['YAMATO03_DYMD'] < $b['YAMATO03_DYMD']) ? -1 : 1;
			});
		}
		// 2016/10/19 Y.Matsukawa ]

		// add start 2016/12/12 H.Yasunaga ロッカー対応 [
		if ($CUST == 'YAMATO01' && $yamato01) {
			// 満空APIを使ってロッカーの情報(受取可能日・出荷日・保管期限）を取得し設定する
			// 拠点データに以下の添え字で値を設定する
			// 受取可能日	: YAMATO01_UKETORIKANODATE
			// 出荷日		: YAMATO01_SHUKKADATA
			// 保管期限		: YAMATO01_HOKANKIGEN
			// 満空APIで使用する出荷予定日・発地郵便番号・ボックスサイズ区分はコンストラクタで設定済み
			// CGIが戻す値の設定は、inc/store_kyoten_outf.inc
			$arr_kyoten = $yamato01->getApiData($arr_kyoten);
			if (is_null($arr_kyoten) == true) {
				$status = ERROR_SYSTEM;
				$CgiOut->set_debug('満空API', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
		}
		// add end ]
	}

	// add 2013/03/11 Y.Matsukawa
	/*==============================================*/
	// RDデータ検索
	/*==============================================*/
	$arr_rd_kyoten = array();
	if ($use_rd && $rec_num) {
		// 該当グループ取得
		$arr_grp = selectRDGroupByView($dba, $CID, 6);
		if (count($arr_grp)) {
			// RDデータ取得
			$arr_rd_kyoten = selectRDData($dba, $CID, $arr_kid, $arr_grp);
			if ($arr_rd_kyoten === false) {
				$arr_rd_kyoten = array();
			}
			// 拠点データにマージ
			if (count($arr_rd_kyoten)) {
				foreach ($arr_kyoten as $k=>$kyoten) {
					$kyoid = $kyoten['KYOTEN_ID'];
					if ($arr_rd_kyoten[$kyoid]) {
						$arr_kyoten[$k]['RD'] = $arr_rd_kyoten[$kyoid];
					}
				}
			}
		}
	}

	if (!$rec_num) {
		// 該当データ無し
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, $hit_num);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	if (($POS+$rec_num-1) < $hit_num) {
		// 後続データ有り
		$status = DEF_RETCD_DEND;
	} else {
		// 後続データ無し
		$status = DEF_RETCD_DE;
	}

	// DBクローズ
	$dba->close();
	
	/*==============================================*/
	// 出力
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $hit_num);
	//	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);				// mod 2016/04/28 T.Yoshino
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val, "", $arr_opt_flg);

	// ログ出力
	//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
	put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
?>
