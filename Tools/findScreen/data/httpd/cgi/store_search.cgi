<?php
/*========================================================*/
// ファイル名：store_search.cgi
// 処理名：拠点条件検索
//
// 更新履歴
// 2011/11/04 H.Nakamura	新規作成
// 2013/03/11 Y.Matsukawa	リアルタイムデータ
// 2014/01/06 H.Osamoto		許可リファラ「null」機能追加
// 2014/12/03 H.Osamoto		FILTERの2バイト文字エンコード対応
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y02';

	/*==============================================*/
	// CGI名
	/*==============================================*/
	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

	/*==============================================*/
	// リターンコード定義
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
	define( 'DEF_RETCD_DE',   '00000' );       //条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_DEND', '00001' );       //条件に見合うデータあり（後続データあり）
	define( 'DEF_RETCD_DNE',  '11009' );       //条件に見合うデータなし
	define( 'DEF_RETCD_AERR', '12009' );       //認証エラー
	define( 'DEF_RETCD_DERR1','17900' );       //データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       //データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       //データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       //入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19200' );       //入力パラメータエラー(構文エラー)
	define( 'DEF_RETCD_PERR3','19200' );       //入力パラメータエラー(組み合わせエラー)

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

	/*==============================================*/
	// エラー出力を明示的にOFF
	/*==============================================*/
	//error_reporting(E_ALL^E_NOTICE);
	//error_reporting(0);
	if ($D_DEBUG) ini_set('display_errors', '1');		// add 2013/03/11 Y.Matsukawa

	/*==============================================*/
	// 初期化
	/*==============================================*/
	// ステータス(リターンコード)
	if (!isset($status)){
		 $status = '00000';
	}

	/*==============================================*/
	//ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');		/* 企業ID */
	$LAT		= getCgiParameter('lat','');			/* 緯度 */
	$LON		= getCgiParameter('lon','');			/* 経度 */
	$FREWD		= getCgiParameter('freeword','');			/* フリーワード */
	$FILTER		= getCgiParameter('filter','');			/* 絞り込み条件 */
	$POS		= getCgiParameter('pos','1');			/* 取得位置 */
	$CNT		= getCgiParameter('cnt','100');			/* 取得件数 */
	$SORT		= getCgiParameter('sort','');			/* ソート順 */
	$ENC		= getCgiParameter('enc', DEF_PRM_ENC_UTF8);		/* 文字コード */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* ポイントフラグ */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* 測地系 */
	$OUTF		= getCgiParameter('outf',DEF_PRM_OUTF_JSON);		/* 出力形式 */

	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// 文字コード変換

	$SORT = mb_ereg_replace("'", "", $SORT);

	/*==============================================*/
	// 絞り込み条件
	/*==============================================*/
	$FILTER_sql = '';
	$FILTER = f_dec_convert($FILTER);	// add 2014/12/03 H.Osamoto
	edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
	$log_frewd = f_dec_convert($FREWD);
	$log_frewd = mb_ereg_replace(' ', '_', $log_frewd);
	$log_frewd = mb_ereg_replace('　', '_', $log_frewd);
	$arr_log_jkn[53] = mb_strimwidth($log_frewd, 0, 128, '...');
	$log_jkn = implode(' ', $arr_log_jkn);

	/*==============================================*/
	// LOG出力用にパラメータ値を結合
	/*==============================================*/
	$parms = '';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' ';
	$parms .= ' '.$log_jkn;

	/*==============================================*/
	// 出力クラス
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* e-map企業ID */
	if ($CID == '') {
		// 許可企業なし
		$status = DEF_RETCD_PERR1;// 該当データ無し
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* 測地系 */
	if ($DATUM != DATUM_TOKYO && $DATUM != DATUM_WGS84) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('datum', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* 取得位置 */
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
	if ($CNT > 1000) {
		$CNT = 1000;
	}

	/* 文字コード */
	if ($INPUT_ENC != 'SJIS' && $INPUT_ENC != 'EUC' && $INPUT_ENC != 'UTF8') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('enc', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* ポイントフラグ */
	if ($PFLG != '1' && $PFLG != '2' && $PFLG != '3') {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('pflg', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}

	/* 出力形式 */
	if ($OUTF != 'JSON' && $OUTF != 'XML') {
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
		$CgiOut->set_debug('dbopen', __LINE__);
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
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
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
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	$dba->free($stmt);

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
	// カラム名リスト取得
	/*==============================================*/
	$arr_item = array();
	$sql  = " SELECT";
	$sql .= "    COL_NAME,ITEM_NAME,VAL_KBN";
	$sql .= " FROM";
	$sql .= "    KYOTEN_ITEM_TBL";
	$sql .= " WHERE"; 
	$sql .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql .= " AND LIST_KBN = 1";
	$sql .= " ORDER BY DISP_NUM";
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
			if ($item['VAL_KBN'] == 'L') {
				$sql_kbn  = " SELECT";
				$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
				$sql_kbn .= " FROM";
				$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
				$sql_kbn .= " WHERE";
				$sql_kbn .= "    CORP_ID = '".escapeOra($CID)."'";
				$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
				$sql_kbn .= " ORDER BY ITEM_VAL";
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
				$arr_kbn[$item['COL_NAME']] = array();
				while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
					$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
					$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
				}
				$dba->free($stmt);
			}
		}
	}

	/*==============================================*/
	// 拠点条件検索
	/*==============================================*/
	$sql  = " SELECT";
	$sql .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID,";
	$sql .= " CASE";
	$sql .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
	$sql .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
	$sql .= "         THEN '1'";
	$sql .= "         ELSE '0'";
	$sql .= " END AS BFLG ";
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			$sql .= ", ".$item['COL_NAME'];
		}
	}
	$sql .= " FROM";
	$sql .= "    KYOTEN_TBL K";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	if ($FREWD != '') {
		$frewd_sql = array();
		$FREWD = f_dec_convert($FREWD);
		$FREWD = mb_ereg_replace('　',' ',$FREWD);
		$words = explode(' ', $FREWD);
		foreach ($words as $w) {
			if ($w != '') {
				$frewd_sql[] = "INSTR(FREE_SRCH, '" . fw_normalize($w) . "') <> 0";
			}
		}
		if (count($frewd_sql)) {
			$sql .= " AND (".implode(' AND ', $frewd_sql).")";
		}
	}
	if ($FILTER_sql != '') {
		$sql .= " AND ".$FILTER_sql;
	}
	$FILTER_sql = f_dec_convert($FILTER_sql);
	// ソートオーダー
	$sql_order = '';
	if ($SORT != '') {
		$sql_order .= $SORT;
	}
	if ($SORT != '') {
		 $sql_order .= ',';
	}
	$sql_order .= 'KYOTEN_ID';
	$sql .= " ORDER BY ".$sql_order;
	$sql = "SELECT S.*, rownum rn FROM (".$sql.") s";

	// ヒット件数取得
	$hit_num = 0;
	$stmt = null;
	$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql.")";
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

	// データ取得
	$rec_num = 0;
	$arr_kid = array();		// add 2013/03/11 Y.Matsukawa
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data = " SELECT";
		$sql_data .= "       *";
		$sql_data .= " FROM (".$sql.")";
		$sql_data .= " where rn >= ".$POS;
		$to = $POS+$CNT-1;
		$sql_data .= " AND rn <= ".$to;
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
			if ($DATUM == DATUM_WGS84) {
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
					if ($item['VAL_KBN'] == 'L') {
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
			}
			$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		$rec_num = count($arr_kyoten);
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

	$dba->close();

	if (!$rec_num) {
		// 該当データ無し
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, 0);
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

	/*==============================================*/
	// 出力(正常)
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $hit_num);
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);

	// ログ出力
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
?>
