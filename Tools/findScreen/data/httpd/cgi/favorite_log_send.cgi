<?php
/*========================================================*/
// ファイル名：favorite_log_send.cgi
// 処理名：お気に入り情報送信
//
// 更新履歴
// 2014/11/07 H.Osamoto		新規作成
// 2014/12/01 C.Eguchi		新規作成の続き
// 2014/12/04 H.Osamoto		DB接続先を変更(PUB⇒MST)
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'f01';

	/*==============================================*/
	// コード定義
	/*==============================================*/
	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_AERR', '12009' );       // プロトコルエラー
	define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19101' );       // 入力パラメータエラー(認証エラー)

	define( 'RET_ENC' , 'UTF8');				// header文字コード

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

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 企業ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	
	/* ユーザID */
	if ($UID == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 拠点ID */
	if ($KID == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/* 認証キー */
	if ($KEY == '') {
		$status = DEF_RETCD_PERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// 認証キーのチェック
	/*==============================================*/
	if($KEY !== AUTH_KEY) {
		$status = DEF_RETCD_PERR2;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// HTTPS必須チェック
	/*==============================================*/
	if($_SERVER['HTTPS'] != 'on') {
		$status = DEF_RETCD_AERR;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// DB接続オープン
	/*==============================================*/
	//	$dba = new oraDBAccess();		// mod 2014/12/04 H.Osamoto
	$dba = new oraDBAccessMst();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// [EMAP_APL_FAVORITE_LOG_TBL]テーブルにデータ格納
	/*==============================================*/

	$sql  = " INSERT INTO EMAP_APL_FAVORITE_LOG_TBL(";
	$sql .= " CORP_ID, USER_ID, KYOTEN_ID, INS_DT";
	$sql .= " ) VALUES ( ";
	$sql .= "'" .  $CID . "' , '" .$UID . "' , '" .$KID . "' , SYSDATE";
	$sql .= " )";

	$stmt = null;

	if (!$dba->sqlExecute($sql, $stmt)) {
		//ロールバック
		$dba->rollbackTransaction();
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}
	else {
		// コミット
		$res = $dba->commitTransaction();
		if (!$res) {
			$status = DEF_RETCD_DERR3;
			output_json(RET_ENC, array("return_code" => $CGICD.$status));
			exit;
		}
	}
	/*==============================================*/
	// 正常終了
	/*==============================================*/
	output_json(RET_ENC, array("return_code" => $CGICD.$status));
	exit;

	/*==============================================*/
	// 切断
	/*==============================================*/
	$dba->close();

?>
