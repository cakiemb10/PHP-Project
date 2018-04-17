<?php
/*========================================================*/
// ファイル名：store_select.cgi
// 処理名：店舗ID検索
//
// 更新履歴
// 2011/12/16 H.Nakamura	新規作成
// 2013/03/11 Y.Matsukawa	リアルタイムデータ
// 2013/12/20 H.Osamoto		データ参照先企業ID取得
// 2014/01/06 H.Osamoto		許可リファラ「null」機能追加
// 2014/10/29 H.Osamoto		拠点画像取得不具合修正
// 2016/01/14 Y.Matsukawa	多言語サイトからの呼び出しに対応（内部接続）
// 2016/01/28 T.Yoshino		拠点画像が複数の場合の考慮を追加
// 2017/01/20 Y.Matsukawa	filter実装
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y03';

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
	define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19200' );       // 入力パラメータエラー(構文エラー)
	define( 'DEF_RETCD_PERR3','19200' );       // 入力パラメータエラー(組み合わせエラー)

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
	include('oraDBAccessMst.inc');
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
	// ログ出力開始
	/*==============================================*/
	include('logs/inc/com_log_open.inc');

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');					/* 企業ID */
	$ID			= getCgiParameter('id', 	'');					/* 拠点ID */
	if ($ID == '') $ID = getCgiParameter('kid', '');		// add 2016/01/14 Y.Matsukawa
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);		/* 文字コード */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* ポイントフラグ */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* 測地系 */
	$OUTF		= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);		/* 出力形式 */
	// add 2016/01/14 Y.Matsukawa [
	$INTID		= getCgiParameter('intid',	'');					/* 内部利用時のID */
	$OPT		= getCgiParameter('opt', '');						/* 内部利用時の企業ID */
	$TYPE		= getCgiParameter('type', '');						/* タイプ */
	$NOLOG		= getCgiParameter('nolog', '');						/* No logging */
	// add 2016/01/14 Y.Matsukawa ]
	$FILTER		= getCgiParameter('filter','');			/* 絞り込み条件 */	// add 2017/01/20 Y.Matsukawa

	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	//$OPTION_CD = $CID;		mod 2016/01/14 Y.Matsukawa
	$OPTION_CD = ($INTID != '')?$OPT:$CID;

	include('store_enc.inc');			// 文字コード変換

	// add 2017/01/20 Y.Matsukawa
	/*==============================================*/
	// 絞り込み条件
	/*==============================================*/
	$FILTER_sql = '';
	$FILTER = f_dec_convert($FILTER);
	edit_jkn($FILTER, $FILTER_sql, $arr_log_jkn);

	/*==============================================*/
	// LOG出力用にパラメータ値を設定
	/*==============================================*/
	$parms = $ID;
	$parms .= ' '.'1';

	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);
	
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
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	
	/* 店舗ID */
	if ($ID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('id', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	/* 項目タイプ */		// add 2016/01/14 Y.Matsukawa
	if ($TYPE != '') {
		$TYPE = intval(urldecode($TYPE));
		if ($TYPE < 1 && $TYPE > 5) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('type', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
	}

	/* 文字コード */
	if ($INPUT_ENC != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC != DEF_PRM_ENC_EUC &&
		$INPUT_ENC != DEF_PRM_ENC_UTF8) {
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
	if ($DATUM != DEF_PRM_DATUM_TOKYO&& 
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
	
	$dbaMst = new oraDBAccessMst();
	if (!$dbaMst->open()) {
		$dbaMst->close();
		$status = DEF_RETCD_DERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
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
			$CgiOut->set_debug('SSL認証', __LINE__);
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
							$CgiOut->set_debug('SSL認証', __LINE__);
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
							$CgiOut->set_debug('SSL認証', __LINE__);
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
				$CgiOut->set_debug('SSL認証', __LINE__);
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
	// カラム名リスト取得 
	/*==============================================*/
	$sql  = " SELECT"; 
	$sql .= "    COL_NAME, VAL_KBN, ITEM_NAME";
	$sql .= " FROM";
	$sql .= "    KYOTEN_ITEM_TBL";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
	//$sql .= " AND SYOUSAI_KBN = 1";		del 2016/01/14 Y.Matsukawa
	// add 2016/01/14 Y.Matsukawa [
	switch ($TYPE) {
		case '1':
			$sql .= " AND SYOUSAI_KBN = '1'";
			break;
		case '2':
			$sql .= " AND INSATSU_KBN = '1'";
			break;
		case '3':
			$sql .= " AND FUKIDASI_KBN = '1'";
			break;
		case '4':
			$sql .= " AND M_SYOUSAI_KBN = '1'";
			break;
		case '5':
			$sql .= " AND OPT_06 = '1'";
			break;
		default:
			$sql .= " AND SYOUSAI_KBN = '1'";
			break;
	}
	// add 2016/01/14 Y.Matsukawa ]
	$sql .= " ORDER BY DISP_NUM";
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
			$sql_kbn  = " SELECT";
			$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
			$sql_kbn .= " FROM";
			$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
			$sql_kbn .= " WHERE";
			$sql_kbn .= " CORP_ID = '".escapeOra($CID)."'";
			$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
			$sql_kbn .= " ORDER BY ITEM_VAL";
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
			$arr_kbn[$item['COL_NAME']] = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
				$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
			}
			$dba->free($stmt);
		}
	}

	/*==============================================*/
	// 拠点ID検索
	/*==============================================*/
	$subsql  = " SELECT";
	$subsql .= "    CORP_ID, KYOTEN_ID, LAT, LON";
	$subsql .= " FROM";
	$subsql .= "    KYOTEN_TBL";
	$subsql .= " WHERE";
	$subsql .= "    CORP_ID = '".escapeOra($CID)."'";
	$subsql .= " AND KYOTEN_ID = '".escapeOra($ID)."'";
	$subsql .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
	// add 2017/01/20 Y.Matsukawa [
	if ($FILTER_sql != '') {
		$subsql .= " AND ".$FILTER_sql;
	}
	// add 2017/01/20 Y.Matsukawa ]

	/* ヒット件数取得 */
	$sql  = " SELECT ";
	$sql .= "    s.*, rownum rn";
	$sql .= " FROM"; 
	$sql .= "    (".$subsql.") s";
	$hit_num = 0;
	$stmt = null;
	$sql_count  = " SELECT";
	$sql_count .= "    count(*) HITCNT";
	$sql_count .= " FROM";
	$sql_count .= "    (".$sql.")";
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

	/* 拠点データ取得 */
	$rec_num = 0;
	$arr_kid = array();		// add 2013/03/11 Y.Matsukawa
	$arr_kyoten = array();
	if ($hit_num > 0) {
		$sql_data  = " SELECT";
		$sql_data  .= "     *";
		$sql_data  .= " FROM(";
		//  ここからNEWアイコン表示フラグ 
		//  開始日、終了日共にNULLの場合：'0'
		//  SYSDATEが開始日から終了日に入っている場合：'1'
		//  SYSDATEが開始日から終了日に入っていない場合：'0'
		// mod 2014/10/29 H.Osamoto [
		//	$sql_data .= " SELECT";
		//	$sql_data .= "     CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID,"; 
		//	$sql_data .= " CASE";
		//	$sql_data .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
		//	$sql_data .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
		//	$sql_data .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
		//	$sql_data .= "         THEN '1'";
		//	$sql_data .= "         ELSE '0'";
		//	$sql_data .= " END AS BFLG ";
		//	if ( count($arr_item) > 0 ) {	//空ではない場合
		//		//$first_flg = 0;
		//		foreach( $arr_item as $rowdata ) {
		//			$sql_data .= ", " . $rowdata['COL_NAME'];
		//		}
		//		$sql_data .= " ";
		//	}
		//	$sql_data .= " FROM ";
		//	$sql_data .= "     KYOTEN_TBL)";
		//	//  ここまで 
		//	$sql_data .= " WHERE";
		//	$sql_data .= "     CORP_ID = '".escapeOra($CID)."'";
		//	$sql_data .= " AND KYOTEN_ID = '".escapeOra($ID)."'";
		$sql_data .= " SELECT";
		$sql_data .= "     A.CORP_ID, A.KYOTEN_ID, A.LAT, A.LON, A.ICON_ID,"; 
		$sql_data .= "     DECODE(B.INS_DT, NULL, '0', '1') AS K_GIF_NUM,"; 
		$sql_data .= " CASE";
		$sql_data .= "     WHEN A.DISP_NEW_S_DATE IS NULL AND A.DISP_NEW_E_DATE IS NULL THEN '0'";
		$sql_data .= "     WHEN SYSDATE BETWEEN NVL(A.DISP_NEW_S_DATE, SYSDATE) AND ";
		$sql_data .= "         NVL(A.DISP_NEW_E_DATE, SYSDATE)";
		$sql_data .= "         THEN '1'";
		$sql_data .= "         ELSE '0'";
		$sql_data .= " END AS BFLG ";
		if ( count($arr_item) > 0 ) {	//空ではない場合
			//$first_flg = 0;
			foreach( $arr_item as $rowdata ) {
				$sql_data .= ", A." . $rowdata['COL_NAME'];
			}
			$sql_data .= " ";
		}
		$sql_data .= " FROM ";
		$sql_data .= "     KYOTEN_TBL A, KYOTEN_GIF_TBL B ";
		//  ここまで 
		$sql_data .= " WHERE A.CORP_ID = B.CORP_ID(+) AND A.KYOTEN_ID = B.KYOTEN_ID(+) ";
		$sql_data .= " AND A.CORP_ID = '".escapeOra($CID)."'";
		$sql_data .= " AND A.KYOTEN_ID = '".escapeOra($ID)."'";
		$sql_data .= " ) ";
		// mod 2014/10/29 H.Osamoto ]
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
			$arr_kyoten[] = $data;
		}
		$dba->free($stmt);
		$rec_num = count($arr_kyoten);


		// add 2013/03/11 Y.Matsukawa
		/*==============================================*/
		// RDデータ検索
		/*==============================================*/
		$arr_rd_kyoten = array();
		if ($use_rd && $rec_num) {
			// 該当グループ取得
			$arr_grp = selectRDGroupByView($dba, $CID, 1);
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

		// add 2016/01/28 T.Yoshino[
		/*==============================================*/
		// 施設画像データ検索
		/*==============================================*/
		$arr_img	 = array();
		$arr_img_def = array();
		$arr_img['CNT']	 = 0;

		$sql_img_def  = " SELECT";
		$sql_img_def .= "    MAX(IMG_NO) AS IMG_CNT";
		$sql_img_def .= " FROM";
		$sql_img_def .= "    KYOTEN_IMG_DEF_TBL";
		$sql_img_def .= " WHERE";
		$sql_img_def .= "    CORP_ID = '".escapeOra($CID)."'";

		$stmt = null;

		if (!$dbaMst->sqlExecute($sql_img_def, $stmt)) {
			$dbaMst->free($stmt);
			$dbaMst->close();
			$status = DEF_RETCD_DERR3;
			$CgiOut->set_debug('DB検索', __LINE__);
			$CgiOut->set_status($status, 0, 0);
			$CgiOut->err_output();
			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}

		if ($dbaMst->getRecInto($stmt, $data, OCI_ASSOC)) {
			$arr_img['CNT'] = $data['IMG_CNT'];
		}
		$dbaMst->free($stmt);


		if( $arr_img['CNT'] != "0" && $arr_img['CNT'] != "" ){
			$sql_img  = " SELECT";
			$sql_img .= "    IMG_NO, GIF_DATA";
			$sql_img .= " FROM";
			$sql_img .= "    KYOTEN_IMG_TBL";
			$sql_img .= " WHERE";
			$sql_img .= "    CORP_ID = '".escapeOra($CID)."'";
			$sql_img .= "    AND KYOTEN_ID = '".escapeOra($ID)."'";

			$stmt = null;

			if (!$dba->sqlExecute($sql_img, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_debug('DB検索', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
				exit;
			}
			
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				foreach( $data as $key => $val ){
					$arr_img[$data['IMG_NO']]['IMG_NO']	 = $data['IMG_NO'];
				}
			}
			$dba->free($stmt);

		}
		// add 2016/01/28 T.Yoshino]


		/*==============================================*/
		// 出力(正常)
		/*==============================================*/
		$CgiOut->set_status($status, $rec_num, $hit_num);
		//$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);			// mod 2016/01/28 T.Yoshino
		$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val, $arr_img);
	}

	// DBクローズ
	$dba->close();
	$dbaMst->close();

	/*==============================================*/
	// 出力(該当データなし)
	/*==============================================*/
	if (!$rec_num) {
		// 該当データ無し
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	// ログ出力
	if (!$NOLOG) {		// add 2016/01/14 Y.Matsukawa
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);		mod 2016/01/14 Y.Matsukawa
		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
	}
?>
