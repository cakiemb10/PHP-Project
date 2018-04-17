<?php
/*========================================================*/
// ファイル名：geofence_log_send.cgi
// 処理名：ジオフェンス通知情報送信
//
// 更新履歴
// 2014/11/17 H.Osamoto		新規作成
// 2014/12/01 C.Eguchi      新規作成の続き
// 2014/12/04 H.Osamoto		DB接続先を変更(PUB⇒MST)
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'g01';

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

	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_AERR', '12009' );       // プロトコルエラー
	define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19101' );       // 入力パラメータエラー(認証エラー)
	define( 'DEF_RETCD_PERR3','19103' );       // 入力パラメータエラー(緯度経度不正)

	/* 認証キー */
	define( 'AUTH_KEY','emxINzp1exRgemQRG3paCmsFcemyp6Im4JKSs' );       // 認証キー(固定)

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	include('d_serv_emap.inc');
	include('store_def.inc'); 
	include('store_outf.inc');			// 出力クラス定義
	include('ZdcCommonFuncAPI.inc');	// 共通関数
	include('function.inc');			// 共通関数
	include('d_serv_ora.inc');
	//	include('oraDBAccess.inc');		// mod 2014/12/04 H.Osamoto
	include('oraDBAccessMst.inc');
	include('chk.inc');				// データチェック関連
	include('log.inc');				// ログ出力
	include('auth.inc');			// 簡易認証
	include("jkn.inc");				// 絞り込み条件編集
	include('apl_outf.inc');		// JSON出力用

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
		 $status = DEF_RETCD_DE;
	}

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');		/* 企業ID */
	$UID		= getCgiParameter('uid', 	'');		/* ユーザID */
	$KID		= getCgiParameter('kid', 	'');		/* 拠点ID */
	$KEY		= getCgiParameter('key',	'');		/* 認証キー */
	$LAT		= getCgiParameter('lat',	'');		/* 緯度 */
	$LON		= getCgiParameter('lon',	'');		/* 経度 */
	$MSG		= getCgiParameter('msg',	'');		/* 通知メッセージ */
	$ENC		= getCgiParameter('enc',	DEF_PRM_ENC_UTF8);		/* 文字コード */
	$PFLG		= getCgiParameter('pflg',	DEF_PRM_PFLG_MSEC);		/* ポイントフラグ */
	$DATUM		= getCgiParameter('datum',	DEF_PRM_DATUM_TOKYO);	/* 測地系 */

	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	include('store_enc.inc');                       // 文字コード変換

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 企業ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	
	/* ユーザID */
	if ($UID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 拠点ID */
	if ($KID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 認証キー */
	if ($KEY == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 緯度 */
	if ($LAT == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 経度 */
	if ($LON == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 通知メッセージ */
	if ($MSG == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 文字コード */
	if ($INPUT_ENC  != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC  != DEF_PRM_ENC_EUC &&
		$INPUT_ENC  != DEF_PRM_ENC_UTF8) {
		
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* ポイントフラグ */
	if ($PFLG != DEF_PRM_PFLG_DNUM && 
		$PFLG != DEF_PRM_PFLG_MSEC &&
		$PFLG != DEF_PRM_PFLG_DMS) {

		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 測地系 */
	if ($DATUM != DEF_PRM_DATUM_TOKYO && 
		$DATUM != DEF_PRM_DATUM_WGS84) {

		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// 認証チェック
	/*==============================================*/
	if($KEY !== AUTH_KEY) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// https必須必須チェック
	/*==============================================*/
	if($_SERVER['HTTPS'] != 'on') {
		$status = DEF_RETCD_AERR;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// 座標表記形式及び測地系の変換
	//   入力データ->日本測地系 ミリ秒
	/*==============================================*/
	$res = cnv_ll2lldms($LAT, $LON, $DATUM, &$CNV_LAT, &$CNV_LON);
	if (!$res) {
		// 緯度経度不正
		$status = DEF_RETCD_PERR3;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	
	/*==============================================*/
	// メッセージの文字コード変換
	/*==============================================*/
	if ($MSG != '') {
		$MSG = f_enc_to_EUC($MSG);
	}

	/*==============================================*/
	// DB接続オープン
	/*==============================================*/
	//	$dba = new oraDBAccess();		// mod 2014/12/04 H.Osamoto
	$dba = new oraDBAccessMst();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// [EMAP_APL_GEOFENCE_LOG_TBL]テーブルにデータ格納
	/*==============================================*/
	$sql  = " INSERT INTO EMAP_APL_GEOFENCE_LOG_TBL(";
	$sql .= " CORP_ID, USER_ID, KYOTEN_ID, INS_DT, LAT, LON, MSG";
	$sql .= " ) VALUES ( ";
	$sql .= "'" .  $CID . "' , '" .$UID . "' , '" .$KID . "' , SYSDATE" . "," . $CNV_LAT . "," . $CNV_LON . ", '" . $MSG . "'";
	$sql .= " )";

	$stmt = null;

	if (!$dba->sqlExecute($sql, $stmt)) {
		//ロールバック
		$dba->rollbackTransaction();
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	else {
		// コミット
		$res = $dba->commitTransaction();
		if (!$res) {
			$status = DEF_RETCD_DERR3;
			output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
    	    exit;
		}
	}

	/*==============================================*/
	// 正常終了
	/*==============================================*/
	output_json($INPUT_ENC, array("return_code" => $CGICD.$status));
	exit;

	/*==============================================*/
	// 切断
	/*==============================================*/
	$dba->close();

?>
