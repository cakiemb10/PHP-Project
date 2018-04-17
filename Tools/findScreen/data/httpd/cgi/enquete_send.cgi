<?php
/*========================================================*/
// ファイル名：enquete_send.cgi
// 処理名：第3章  アンケート結果送信
//
// 更新履歴
// 2014/11/07 H.Osamoto		新規作成
// 2014/12/02 C.Eguchi      新規作成の続き
// 2014/12/04 H.Osamoto		DB接続先を変更(PUB⇒MST)
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'e01';

	/*==============================================*/
	// コード定義
	/*==============================================*/
	/* 入力パラメータ*/
	define( 'DEF_PRM_ENC_UTF8',		'UTF8' );       // 文字コード（UTF8）
	define( 'DEF_PRM_ENC_SJIS',		'SJIS' );       // 文字コード（SJIS）
	define( 'DEF_PRM_ENC_EUC',		'EUC'  );       // 文字コード（EUC）
	
	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_ERR1' ,'11009' );       // アンケート結果登録済みエラー
	define( 'DEF_RETCD_AERR' ,'12009' );       // プロトコルエラー
	define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19101' );       // 入力パラメータエラー(認証エラー)

	/* 認証キー */
	define( 'AUTH_KEY','emxINzp1exRgemQRG3paCmsFcemyp6Im4JKSs' );       // 認証キー(固定)
	
	/* 項目最大項目数 */
	define( 'TEXT_MAX', 30 );       // テキスト項目
	define( 'LIST_MAX', 30 );       // リスト項目
	define( 'FLG_MAX' , 50 );       // フラグ項目

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
	$KEY		= getCgiParameter('key',	'');		/* 認証キー */
	$ENC		= getCgiParameter('enc',	DEF_PRM_ENC_UTF8);		/* 文字コード */

	for ($t = 1; $t <= TEXT_MAX; $t++) {
		$TEXT[$t] = getCgiParameter('text' . $t,	'');		/* テキスト項目 */
	}
	for ($l = 1; $l <= LIST_MAX; $l++) {
		$LIST[$l] = getCgiParameter('list' . $l,	'');		/* リスト項目 */
	}
	for ($f = 1; $f <= FLG_MAX; $f++) {
		$FLG[$f] = getCgiParameter('flg' . $f,	'');		/* フラグ項目 */
	}

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

	/* 認証キー */
	if ($KEY == '') {
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
	// TEXTの文字コード変換
	/*==============================================*/
	for ($t = 1; $t <= TEXT_MAX; $t++) {
		if ($TEXT[$t] != '') {
			$TEXT[$t] = f_enc_to_EUC($TEXT[$t]);
		}
	}

	/*==============================================*/
	// LISTの文字コード変換
	/*==============================================*/
	for ($l = 1; $l <= LIST_MAX; $l++) {
		if ($LIST [$l] != '') {
			$LIST [$l] = f_enc_to_EUC($LIST[$l]);
		}
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
	// [EMAP_APL_BEACON_LOG_TBL]テーブルにデータ格納
	/*==============================================*/
	$sql  = " INSERT INTO EMAP_APL_ENQUETE_LOG_TBL (";
	$sql .= " CORP_ID, USER_ID, INS_DT";
	// TEXT
	for ($t = 1; $t <= TEXT_MAX; $t++) {
		$sql .= ", TEXT_" . sprintf("%02d", $t);
	}
	// LIST
	for ($l = 1; $l <= LIST_MAX; $l++) {
		$sql .= ", LIST_" . sprintf("%02d", $l);
	}
	// FLG
	for ($f = 1; $f <= FLG_MAX; $f++) {
		$sql .= ",  FLG_" . sprintf("%02d", $f);
	}
	$sql .= " ) VALUES ( ";
	$sql .= "'" .  $CID . "' , '" .$UID . "' , SYSDATE";
	// TEXT
	for ($t = 1; $t <= TEXT_MAX; $t++) {
		$sql .= ", '" . $TEXT[$t] . "'";
	}
	// LIST
	for ($l = 1; $l <= LIST_MAX; $l++) {
		$sql .= ", '" . $LIST[$l] . "'";
	}
	// FLG
	for ($f = 1; $f <= FLG_MAX; $f++) {
		$sql .= ", '" . $FLG[$f] . "'";
	}
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
