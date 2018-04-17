<?php
/*========================================================*/
// ファイル名：711OMNI_sales_nearsearch.cgi
// 処理名：711OMNI用最寄拠点検索
//
// 更新履歴
// 2016/07/19 T.Yoshino		新規作成
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y01';

	/*==============================================*/
	// CGI名
	/*==============================================*/
//	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));
	$CGINM = "711OMNI_sales_nearsearch";

	
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
	define( 'DEF_RETCD_DE',   '00000' );       //条件に見合うデータあり（正常終了）
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
	include('chk.inc');					// データチェック関連
	include('log.inc');					// ログ出力
	include('auth.inc');				// 簡易認証
	include("jkn.inc");					// 絞り込み条件編集
//	include('store_kyoten_outf.inc');
	include('711OMNI_outf.inc');

	/*==============================================*/
	// エラー出力を明示的にOFF
	/*==============================================*/
	//error_reporting(E_ALL^E_NOTICE);
	//error_reporting(0);
	if ($D_DEBUG) ini_set('display_errors', '1');

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
	$CID		= "711OMNI";										/* 企業ID */
	$LAT		= "";												/* 緯度 */
	$LON		= "";												/* 経度 */
	$POS		= "1";												/* 取得位置 */
	$CNT		= "1";												/* 取得件数 */
	
	$ADDR		= getCgiParameter('addr','');						/* 住所 */
	$ADDRNO		= getCgiParameter('addrno','');						/* 郵便番号 */
	$PRCF		= getCgiParameter('prfctr_cd','');					/* 都道府県コード */
	$DLIQ		= getCgiParameter('dealing_liquor_flg','');			/* 絞り込み条件 */
	$ENC		= getCgiParameter('enc', DEF_PRM_ENC_UTF8);			/* 文字コード */
	
	$INTID		= '';												/* 内部利用時のID */
	$PFLG		= DEF_PRM_PFLG_MSEC;								/* ポイントフラグ */
	$DATUM		= DEF_PRM_DATUM_TOKYO;								/* 測地系 */
	$OUTF		= DEF_PRM_OUTF_XML;									/* 出力形式 */
	
	$CUST		= getCgiParameter('cust', '711OMNICGI');			/* 対象企業ﾊﾟﾗﾒｰﾀ */
	
	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	// 課金ログに出力する企業ID
	$OPTION_CD = ($INTID != '')?$OPT:$CID;

	include('store_enc.inc');			// 文字コード変換

	// 企業ID補正
	$hostname = trim(`hostname`);
	if( $hostname == "dev-storenaviweb0" || $hostname == "storenaviweb-v01" ) {
		$CID .= "test";
	}


	/*==============================================*/
	// 緯度経度取得
	/*==============================================*/

	// 住所検索
	if ( $ADDR != '' ) {
		$addr_e = urlencode( $ADDR );
		//ジオコーディング
		$url = sprintf("%s?key=%s&opt=%s&enc=%s&mclv=%d&sep=&tod=&frewd=%s", $D_SSAPI["selectaddr"], $D_SSAPI_KEY, $CID, $ENC, 6, $addr_e);
		$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
		$status = explode("\t", $dat[0]);

		if($status[0] == "21300000") {
			$rec = explode("\t", $dat[1]);
			$LAT = intval($rec[5]);
			$LON = intval($rec[6]);
			switch ($rec[0]) {
				case 'KEN':
					$M_LEVEL = "1";
					break;
				case 'SHK':
					$M_LEVEL = "2";
					break;
				case 'OAZ':
					$M_LEVEL = "3";
					break;
				case 'AZC':
					$M_LEVEL = "4";
					break;
				case 'GIK':
					$M_LEVEL = "5";
					break;
				case 'TBN':
					$M_LEVEL = "6";
					break;
				case 'EBN':
					$M_LEVEL = "7";
					break;
				default:
					$M_LEVEL = "0";
			}
		}
	}

	// 郵便番号検索
	if ( ( $ADDR == ''  && $ADDRNO != '' ) || ( $ADDRNO != '' && $M_LEVEL != '' && ( $M_LEVEL == 1 || $M_LEVEL == 0 ) ) ) {
		$cgi = $D_SSAPI["searchzip"];
		$prm = sprintf("&pos=%d&cnt=%d&enc=%s&zip=%s&datum=%s&outf=%s&sort=%s", 1, 1, 'EUC', urlencode($ADDRNO), $DATUM, 'TSV', 'adcd');
		$url = sprintf("%s?key=%s&opt=%s&%s", $cgi, $D_SSAPI_KEY, $OPTION_CD, $prm);
		$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
		$status = explode("\t", $dat[0]);

		if(intval($status[2])) {
			$rec = explode("\t", $dat[1]);
			$LAT = $rec[0];
			$LON = $rec[1];
		}
		$M_LEVEL = "";
	}


	/*==============================================*/
	// LOG出力用にパラメータ値を結合
	/*==============================================*/
	$parms = $LAT;
	$parms .= ' '.$LON;

	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	$CgiOut = new StoreKyotenCgiOutput($CGICD, "store_nearsearch", $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF, $CUST );
	
	
	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 内部接続フラグ */
	if ($INTID != '') {
		if(!in_array($INTID, $D_STORE_INTID)) {
			$status = DEF_RETCD_PERR2;
			$CgiOut->set_debug('intid', __LINE__);
			$CgiOut->set_status($status, 0, "");
			$CgiOut->err_output();
//			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}
	}
	/* ログ出力用キー */
	if ($INTID != '') {
		$log_key = '299912312359592'.$INTID;
	} else {
		$log_key = D_LOG_CGIKEY;
	}

	/* 緯度 */
	if ($LAT == '' ) {
		$status = DEF_RETCD_PERR1;
//		$status = INVALID_PARAMETER_LAT;
		$CgiOut->set_debug('lat', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 経度 */
	if ($LON == '' ) {
		$status = DEF_RETCD_PERR1;
//		$status = INVALID_PARAMETER_LON;
		$CgiOut->set_debug('lon', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 文字コード */
	if ($INPUT_ENC  != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC  != DEF_PRM_ENC_EUC &&
		$INPUT_ENC  != DEF_PRM_ENC_UTF8) {

		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('enc', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	/* 都道府県コード */
	if ($PRCF == '' || $PRCF >= 48 ) {
		$status = DEF_RETCD_PERR1;
//		$status = INVALID_PARAMETER_LON;
		$CgiOut->set_debug('lon', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}
	
	/* 酒取扱い有無指定 */
	if ($DLIQ == '' || $DLIQ >= 2 ) {
		$status = DEF_RETCD_PERR1;
//		$status = INVALID_PARAMETER_LON;
		$CgiOut->set_debug('lon', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
		//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}


	/*==============================================*/
	// SSL認証、IPチェック、リファラチェック
	/*==============================================*/
	if ($INTID == '') {		// 内部接続の場合はチェックしない
		$sql  = " SELECT"; 
		//	$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER";
		$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER, REFERER_NULL";
		$sql .= " FROM";
		$sql .= "    EMAP_CGI_CONF_TBL";
		$sql .= " WHERE";
		$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_DERR3 . 1;
			$CgiOut->set_debug('SSL認証許可', __LINE__);
			$CgiOut->set_status($status, 0, "");
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
							$CgiOut->set_status($status, 0, "");
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
							$CgiOut->set_status($status, 0, "");
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
				$CgiOut->set_status($status, 0, ""); 
				$CgiOut->err_output();
				//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
							$CgiOut->set_status($status, 0, "");
							$CgiOut->err_output();
							//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//							put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
							exit;
						}
					}
				}
			}
		} else {
			$status = DEF_RETCD_AERR;
			$CgiOut->set_debug('認証エラー', __LINE__);
			$CgiOut->set_status($status, 0, "");
			$CgiOut->err_output();
			//put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
//			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
			exit;
		}
		$dba->free($stmt);
	}


	/*==============================================*/
	// データ参照先企業ID取得
	/*==============================================*/
	$CID = getDataCid($dba, $CID);

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
		$status = DEF_RETCD_PERR2 . 5;
//		$status = INVALID_PARAMETER;	// mod 2016/04/25 T.Yoshino 
		$CgiOut->set_status($status, 0, "");
		$CgiOut->set_debug('緯度経度', __LINE__);
		$CgiOut->err_output();
//			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
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
	$sql .= " AND LIST_KBN = 1";
	$sql .= " ORDER BY DISP_NUM";
	/* クエリ発行 */
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3 . 2;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
				$status = DEF_RETCD_DERR3 . 3;
				$CgiOut->set_debug('DB検索', __LINE__);
				$CgiOut->set_status($status, 0, "");
				$CgiOut->err_output();
//				put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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


	/*==============================================*/
	// 最寄拠点検索
	/*==============================================*/
	/* サブクエリ生成 */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID, COL_55, COL_04";

	$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $LAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
	$sql_sub_near .= " + POWER( ABS( LON - $LON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI ";

	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    KYOTEN_TBL K";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";

	// 売上計上指定(固定)
	$sql_sub_near .= " AND COL_38  = '1'";
	// 都道府県コード指定
	$sql_sub_near .= " AND COL_04  = '" . $PRCF . "'";
	// 酒取扱い有無指定
	if ( $DLIQ == 1 ) {
		$sql_sub_near .= " AND COL_21  = '" . $DLIQ . "'";
	}

	$sql_sub_near .= " order by KYORI, KYOTEN_ID";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";

	// ヒット件数取得
	$hit_num = 0;
	$stmt = null;
	$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql_near.")";
	
	if (!$dba->sqlExecute($sql_count, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3 . 4;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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
			$status = DEF_RETCD_DERR3 . 5;
			$CgiOut->set_debug('DB検索', __LINE__);
			$CgiOut->set_status($status, 0, "");
			$CgiOut->err_output();
	//			put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
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

			$arr_kyoten[] = $data;

		}
	} else if ($hit_num == 0) {
		$arr_kyoten[0]['COL_55'] = 185726;
	}

	$dba->free($stmt);
	$rec_num = count($arr_kyoten);
	
	if (!$rec_num) {
		// 該当データ無し
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, "");
		$CgiOut->err_output();
//		put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
		exit;
	}

	// 正常終了
	$status = DEF_RETCD_DE;

	// DBクローズ
	$dba->close();
	
	
	/*==============================================*/
	// 出力
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $M_LEVEL);
	$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val, "", $arr_opt_flg);

	// ログ出力
//	put_log($CGICD.$status, $log_key, $OPTION_CD, $parms);
?>
