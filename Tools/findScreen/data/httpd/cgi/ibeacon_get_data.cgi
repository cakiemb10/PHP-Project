<?php
/*========================================================*/
// ファイル名：ibeacon_get_data.cgi
// 処理名：iBeacon情報取得
//
// 更新履歴
// 2014/11/17 H.Osamoto		新規作成
// 2014/12/01 C.Eguchi      新規作成の続き
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = 'b02';

	/*==============================================*/
	// コード定義
	/*==============================================*/
	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり
	define( 'DEF_RETCD_DNE'  ,'11009' );	   // 条件に見合うデータなし
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
	include('oraDBAccess.inc');
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
	$BID		= getCgiParameter('bid', 	'');		/* BeaconID */
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

	/* BeaconID */
	if ($BID == '') {
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
	// 認証チェック
	/*==============================================*/
	if($KEY !== AUTH_KEY) {
		$status = DEF_RETCD_PERR2;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// DB接続オープン
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
		exit;
	}

	/*==============================================*/
	// 対象データ取得
	/*==============================================*/
	$sql  = " SELECT ";
	$sql .= " CORP_ID, BEACON_ID, INS_DT, MSG, DISP_TYPE, FUNC, KYOTEN_ID ";	// とりあえず、全カラム取得
	$sql .= " FROM EMAP_APL_BEACON_DATA_TBL ";
	$sql .= " WHERE ";
	$sql .= " CORP_ID = '" . $CID . "'";
	$sql .= " AND ";
	$sql .= " BEACON_ID = '" . $BID . "'";

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR2;
	}
	else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			// CORP_ID,BEACON_IDで必ず1件
			$beacon['beacon_id'] = $data["BEACON_ID"];
			$beacon['msg']       = $data["MSG"];
			$beacon['kyoten_id'] = $data["KYOTEN_ID"];
			$beacon['disp_type'] = $data["DISP_TYPE"];
			$beacon['func']      = $data["FUNC"];
		}
		else {
			$status = DEF_RETCD_DNE;
		}
		$dba->free($stmt);
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json(RET_ENC, array("return_code" => $CGICD.$status));
        exit;
    }
	
	/*==============================================*/
	// 正常終了
	/*==============================================*/


	$out_data = array("return_code" => $CGICD.$status, "beacon" => $beacon);
	output_json(RET_ENC, $out_data);
	exit;

?>
