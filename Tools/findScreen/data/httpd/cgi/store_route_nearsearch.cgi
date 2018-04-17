<?php
/*========================================================*/
// ファイル名：store_route_nearsearch.cgi
// 処理名：ルート沿い店舗検索
//
// 更新履歴
// 2014/01/16 H.Osamoto		新規作成
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y04';

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
	define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_DEND', '00001' );       // 条件に見合うデータあり（後続データあり）
	define( 'DEF_RETCD_DNE',  '11009' );       // 条件に見合うデータなし
	define( 'DEF_RETCD_AERR', '12009' );       // 認証エラー
	define( 'DEF_RETCD_RERR', '16009' );       // ルート探索エラー
	define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19200' );       // 入力パラメータエラー(構文エラー)

	// PC2.0のキーでルート探索を行う為のフラグ
	$D_PC2 = true;

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
	include('auth.inc');			// 簡易認証
	include("jkn.inc");				// 絞り込み条件編集
	include('store_kyoten_outf.inc');
	include('rd_sql.inc');

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
	$NELAT = 0;	/* 北東（右上）緯度 */
	$NELON = 0;	/* 北東（右上）経度 */
	$SWLAT = 200000000;	/* 南西（左下）緯度 */
	$SWLON = 550000000;	/* 南西（左下）経度 */

	/*==============================================*/
	// ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', '');						/* 企業ID */
	$STLAT		= getCgiParameter('stlat','');						/* ルート探索開始緯度 */
	$STLON		= getCgiParameter('stlon','');						/* ルート探索開始経度 */
	$EDLAT		= getCgiParameter('edlat','');						/* ルート探索終了緯度 */
	$EDLON		= getCgiParameter('edlon','');						/* ルート探索終了経度 */
	$BUFFER		= getCgiParameter('buffer','1000');					/* ルートからの検索距離 */
	$FILTER		= getCgiParameter('filter','');						/* 絞り込み条件 */
	$POS		= getCgiParameter('pos','1');						/* 取得位置 */
	$CNT		= getCgiParameter('cnt','100');						/* 取得件数 */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* 文字コード */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* ポイントフラグ */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* 測地系 */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* 出力形式 */

	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// 文字コード変換
	

	/*==============================================*/
	// 絞り込み条件
	/*==============================================*/
	$FILTER_sql = '';
	edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
	$log_jkn = implode(' ', $arr_log_jkn);

	/*==============================================*/
	// LOG出力用にパラメータ値を結合
	/*==============================================*/
	$parms = $STLAT;
	$parms .= ' '.$STLON;
	$parms .= ' '.$EDLAT;
	$parms .= ' '.$EDLON;
	$parms .= ' '.$BUFFER;
	$parms .= ' '.$log_jkn;

	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	
	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 企業ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* ルート探索開始緯度 */
	if ($STLAT == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('stlat', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* ルート探索開始経度 */
	if ($STLON == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('stlon', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* ルート探索終了緯度 */
	if ($EDLAT == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('edlat', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* ルート探索終了経度 */
	if ($EDLON == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('edlon', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* ルートからの検索距離 */
	if ($BUFFER < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('buffer', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* 取得開始位置*/
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pos', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* 取得件数 */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('cnt', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if ($CNT > 200) {
		$CNT = 200;
	}
	/* 文字コード */
	if ($INPUT_ENC  != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC  != DEF_PRM_ENC_EUC &&
		$INPUT_ENC  != DEF_PRM_ENC_UTF8) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('enc', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* 測地系 */
	if ($DATUM != DEF_PRM_DATUM_TOKYO && 
		$DATUM != DEF_PRM_DATUM_WGS84) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	/* 出力形式 */
	if ($OUTF != DEF_PRM_OUTF_JSON && $OUTF != DEF_PRM_OUTF_XML) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// サービス期間
	/*==============================================*/
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// CGI利用許可
	/*==============================================*/
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
	} else {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_AERR;
		$CgiOut->set_debug('CGI利用許可', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	$dba->free($stmt);

	/*==============================================*/
	// SSL認証、IPチェック、リファラチェック
	/*==============================================*/
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
		
		$referer_list = explode(";",  $data['ALLOW_REFERER']);
		
		/* IPチェック */
		if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
			if (!ip_check2($data['ALLOW_IP'], $_SERVER['REMOTE_ADDR'], ';')) {
				/* リファラチェック */
				if (!referer_check(&$referer_list, $_SERVER['HTTP_REFERER'])) {
					/* リファラnull許可チェック */
					if (!referer_null_check($data['REFERER_NULL'], $_SERVER['HTTP_REFERER'])) {
						$dba->free($stmt);
						$dba->close();
						$status = DEF_RETCD_AERR;
						$CgiOut->set_debug('IPチェック', __LINE__);
						$CgiOut->set_status($status, 0, 0);
						$CgiOut->err_output();
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
						exit;
					}
				}
			}
		}
	} else {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_debug('認証エラー', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	$dba->free($stmt);

	/*==============================================*/
	// データ参照先企業ID取得
	/*==============================================*/
	$CID = getDataCid($dba, $CID);

	/*==============================================*/
	// RD利用設定
	/*==============================================*/
	$use_rd = isRDAvailable($dba, $CID);

	/*==============================================*/
	// 座標表記形式及び測地系の変換
	/*==============================================*/
	$STLAT_MS;
	$STLON_MS;
	$EDLAT_MS;
	$EDLON_MS;
	$res = cnv_ll2lldms($STLAT, $STLON, $DATUM, &$STLAT_MS, &$STLON_MS);
	if (!$res) {
		// ルート探索開始緯度経度不正
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->set_debug('ルート探索開始緯度経度', __LINE__);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	$res = cnv_ll2lldms($EDLAT, $EDLON, $DATUM, &$EDLAT_MS, &$EDLON_MS);
	if (!$res) {
		// ルート探索終了緯度経度不正
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->set_debug('ルート探索終了緯度経度', __LINE__);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// ルート情報取得
	/*==============================================*/
	$route_url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $STLAT_MS, $STLON_MS, $EDLAT_MS, $EDLON_MS);
	$route_xml = file_get_contents($route_url);
	$route_dat = simplexml_load_string($route_xml);

	$route_line = "";

	foreach ($route_dat->links->link as $route_array) {
		
		// GEOS用に緯度経度の区切りを半角スペースに変更し結合
		$point_array = explode(",", $route_array->path);
		foreach($point_array as $key => $point) {
			if ($route_line == "") {
				$route_line = $point;
			} else if ($key % 2 == 0) {
				$route_line .= ",".$point;
			} else {
				$route_line .= " ".$point;
			}
		}
	}

	// ルート情報が取得できない場合はエラー
	if (!$route_line) {
		$status = DEF_RETCD_RERR;
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->set_debug('ルート探索エラー', __LINE__);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/*==============================================*/
	// ルートポリゴン生成
	/*==============================================*/
	$reader = new GEOSWKTReader();
	$writer = new GEOSWKTWriter();
	$writer->setRoundingPrecision(0);

	// BUFFERを緯度経度単位の値に変換（緯度経度の変換比率誤差は考慮しない）
	$latlon_buffer = $BUFFER * 40;

	// 生成
	$g = $reader->read('LINESTRING('.$route_line.')');
	$retRoutePoly = $g->buffer($latlon_buffer, array('quad_segs' => 1, 'endcap' => GEOSBUF_CAP_ROUND));
	$retRoutePoly_str = $writer->write($retRoutePoly);

	// 不要文字列除去
	$retRoutePoly_str = str_replace('))', '', str_replace('POLYGON ((', '', $retRoutePoly_str));

	$tmp_arr = explode(",", $retRoutePoly_str);

	foreach($tmp_arr as $tmp_point) {
		$tmp_point = trim($tmp_point);
		
		list($tmp_lon, $tmp_lat) = explode(" ", $tmp_point);
		
		// 不要文字列除去（稀にマルチポリゴンで返却される場合がある為）
		$tmp_lat = trim(preg_replace('/[\(\)]/', '', $tmp_lat));
		$tmp_lon = trim(preg_replace('/[\(\)]/', '', $tmp_lon));
		
		$route_poly_arr[] = cnv_dms2hour($tmp_lat).",".cnv_dms2hour($tmp_lon);
		
		// 検索範囲
		if ($NELAT < $tmp_lat) $NELAT = $tmp_lat;
		if ($NELON < $tmp_lon) $NELON = $tmp_lon;
		if ($SWLAT > $tmp_lat) $SWLAT = $tmp_lat;
		if ($SWLON > $tmp_lon) $SWLON = $tmp_lon;
	}

	// 不要になったルート情報解放
	unset($route_xml);
	unset($route_dat);
	unset($point_array);
	unset($point);
	unset($route_line);

	// 不要になったポリゴン情報解放
	unset($retRoutePoly);
	unset($tmp_arr);
	unset($tmp_point);


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
	$sql .= " AND LIST_KBN = 1";
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
	// 選定用に必要最低限のカラムのみ全件取得
	/*==============================================*/
	/* サブクエリ生成 */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    KYOTEN_ID, LAT, LON";
	$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $STLAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
	$sql_sub_near .= " + POWER( ABS( LON - $STLON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI ";
	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    KYOTEN_TBL K";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql_sub_near .= " AND LAT >= ".$SWLAT;
	$sql_sub_near .= " AND LAT <= ".$NELAT;
	$sql_sub_near .= " AND LON >= ".$SWLON;
	$sql_sub_near .= " AND LON <= ".$NELON;
	$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	if ($FILTER_sql != '') {
		$sql_sub_near .= " AND ".$FILTER_sql;
	}
	$FILTER_sql = f_dec_convert($FILTER_sql);
	$sql_sub_near .= " order by KYORI, KYOTEN_ID";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";

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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$hit_num = $data['HITCNT'];
	}
	$dba->free($stmt);
	
	
	// 選定用に必要最低限のカラムのみ取得
	$rec_num = 0;
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data = "SELECT * FROM (".$sql_near.")";
		$stmt = null;
		if (!$dba->sqlExecute($sql_data, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('DB検索', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
		while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
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
			$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		
		
		/*==============================================*/
		// 内外判定
		/*==============================================*/
		$reader = new GEOSWKTReader();
		$writer = new GEOSWKTWriter();
		$writer->setRoundingPrecision(0);
		
		$g1 = $reader->read('POLYGON(('.$retRoutePoly_str.'))');
		
		foreach($arr_kyoten as $key => $kyoten_data) {
			$check_lat = $kyoten_data['LAT'];
			$check_lon = $kyoten_data['LON'];
			
			$g2 = $reader->read('POINT('.$check_lon.' '.$check_lat.')');
			
			$retAssert = $g1->contains($g2);
			
			if ($retAssert == "") {
				unset($arr_kyoten[$key]);
			}
		}
		
		// 削除したキー詰め
		$arr_kyoten = array_values($arr_kyoten);
		
		
		// データ件数更新
		$hit_num = count($arr_kyoten);
		
		// 指定POSに満たない場合はエラー
		if ($hit_num < $POS) {
			// 該当データ無し
			$status = DEF_RETCD_DNE;
			$CgiOut->set_debug('DB検索', __LINE__);
			$CgiOut->set_status($status, 0, $hit_num);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
		
		// 取得対象選定
		$kyotenid_str = "";
		for($i = $POS; $i < $CNT+$POS; $i++) {
			if ($arr_kyoten[$i-1]['KYOTEN_ID']) {
				if ($kyotenid_str) {
					$kyotenid_str .= ",";
				}
				// SQL用拠点ID文字列作成
				$kyotenid_str .= $arr_kyoten[$i-1]['KYOTEN_ID'];
			}
		}
		
		// 不要になった拠点情報解放
		unset($arr_kyoten);
		
		/*==============================================*/
		// 返却用データ取得
		/*==============================================*/
		$arr_kyoten_output = array();
		if ($hit_num > 0) {
			/* サブクエリ生成 */
			$sql_sub_near  = " SELECT";
			$sql_sub_near .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
			$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $STLAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
			$sql_sub_near .= " + POWER( ABS( LON - $STLON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
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
			$sql_sub_near .= " AND LAT >= ".$SWLAT;
			$sql_sub_near .= " AND LAT <= ".$NELAT;
			$sql_sub_near .= " AND LON >= ".$SWLON;
			$sql_sub_near .= " AND LON <= ".$NELON;
			$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
			if ($FILTER_sql != '') {
				$sql_sub_near .= " AND ".$FILTER_sql;
			}
			$FILTER_sql = f_dec_convert($FILTER_sql);
			$sql_sub_near .= " order by KYORI, KYOTEN_ID, CORP_ID";
			$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
			$sql_data = "SELECT * FROM (".$sql_near.")";
			$sql_data .= " where kyoten_id in (".$kyotenid_str.")";
			$stmt = null;
			if (!$dba->sqlExecute($sql_data, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('DB検索', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
				exit;
			}
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
				$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
				$arr_kyoten_output[] = $data;
			}
			$dba->free($stmt);
			$rec_num = count($arr_kyoten_output);
		}
		
		/*==============================================*/
		// RDデータ取得
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
					foreach ($arr_kyoten_output as $k=>$kyoten) {
						$kyoid = $kyoten['KYOTEN_ID'];
						if ($arr_rd_kyoten[$kyoid]) {
							$arr_kyoten_output[$k]['RD'] = $arr_rd_kyoten[$kyoid];
						}
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten_output, $arr_item_val);
	// ログ出力
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
?>
