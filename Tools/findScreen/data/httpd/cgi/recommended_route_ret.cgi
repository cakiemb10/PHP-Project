<?php
/*========================================================*/
// ファイル名：recommended_route.cgi
// 処理名：オススメルート取得
//
// 更新履歴
// 2015/01/07 t.yoshino		新規作成
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'y06';

	/*==============================================*/
	// CGI名
	/*==============================================*/
	$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

	/*==============================================*/
	// コード定義
	/*==============================================*/
	
	/* 入力パラメータ*/
	define( 'DEF_PRM_OUTF_JSON', 	'JSON' );       // 出力形式（JSON）
	define( 'DEF_PRM_OUTF_XML', 	'XML'  );       // 出力形式（XML）
	define( 'DEF_PRM_PFLG_DNUM',	'1'    );       // ポイントフラグ（十進緯度経度表記）
	define( 'DEF_PRM_PFLG_MSEC',	'2'    );       // ポイントフラグ（ミリ秒緯度経度表記）
	define( 'DEF_PRM_PFLG_DMS',    	'3'    );       // ポイントフラグ（度分秒緯度経度表記）

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
	include('chk.inc');					// データチェック関連
	include('log.inc');					// ログ出力
	include('auth.inc');				// 簡易認証
	include("jkn.inc");					// 絞り込み条件編集
	include('recommended_route_outf.inc');
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
	$CID	= getCgiParameter('cid', '');							/* 企業ID */
	$RID	= getCgiParameter('rid', '');							/* ルートID */
	$PFLG	= getCgiParameter('pflg', DEF_PRM_PFLG_MSEC);			/* ポイントフラグ */
	$OUTF	= getCgiParameter('outf',	DEF_PRM_OUTF_JSON);			/* 出力形式 */
		
	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// 文字コード変換
	

	/*==============================================*/
	// 出力用クラスを生成
	/*==============================================*/
	$CgiOut = new ReccRouteCgiOutput($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, $OUTF);

	
	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 企業ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('cid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
		exit;
	}
	/* ルートID */
	if ($RID == '') {
		$status = DEF_RETCD_PERR1;
		$CgiOut->set_debug('rid', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
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
		exit;
	}
	/* 出力形式 */
	if ($OUTF != DEF_PRM_OUTF_JSON && $OUTF != DEF_PRM_OUTF_XML) {
		$status = DEF_RETCD_PERR2;
		$CgiOut->set_debug('outf', __LINE__);
		$CgiOut->set_status($status, 0, 0); 
		$CgiOut->err_output();
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
			exit;
		}
	} else {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_AERR;
		$CgiOut->set_debug('CGI利用許可', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
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
	// 返却用データ取得
	/*==============================================*/
	$arr_route_output = array();
	/* サブクエリ生成 */
	$sql_sub_near  = " SELECT";
	$sql_sub_near .= "    CORP_ID, ROUTE_ID, ROUTE_INFO ";
	$sql_sub_near .= " FROM";
	$sql_sub_near .= "    RECOMMENDED_ROUTE_TBL R";
	$sql_sub_near .= " WHERE";
	$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
	$sql_sub_near .= " AND ROUTE_ID = '".escapeOra($RID)."'";
	$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
	$sql_data = "SELECT * FROM (".$sql_near.")";
	$stmt = null;

	if (!$dba->sqlExecute($sql_data, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, 0);
		$CgiOut->err_output();
		exit;
	}
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$arr_route_output[] = $data;
	}
	$dba->free($stmt);
	$rec_num = count($arr_route_output);

	if (!$rec_num) {
		// 該当データ無し
		$status = DEF_RETCD_DNE;
		$CgiOut->set_debug('DB検索', __LINE__);
		$CgiOut->set_status($status, 0, $hit_num);
		$CgiOut->err_output();
		exit;
	}


	/*==============================================*/
	// ルート情報取得
	/*==============================================*/
	$target_route_array = explode(";", $arr_route_output[0]['ROUTE_INFO']);

	foreach( $target_route_array as $key => $val ){
		$target_point_array[$key] = explode(" ", $val);
		$arr_kyoten_output[$key+1]['LAT']	 = $target_point_array[$key][0];
		$arr_kyoten_output[$key+1]['LON']	 = $target_point_array[$key][1];
	}

	// データ件数更新
	$hit_num = count($target_route_array);

	// DBクローズ
	$dba->close();


	/*==============================================*/
	// 出力
	/*==============================================*/
	$CgiOut->set_status($status, $rec_num, $hit_num);
//	$CgiOut->output($CID, $ID, $PFLG, $arr_kyoten_output);
	$CgiOut->output($CID, $ID, $PFLG, "", $arr_kyoten_output, "");
	// ログ出力
	
	
?>
