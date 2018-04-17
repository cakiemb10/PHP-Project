<?php
/*========================================================*/
// ファイル名：get_cond_pattern.cgi
// 処理名：絞込み条件取得
//
// 解説：指定企業の絞込み条件を返す。
//
// 更新履歴
// 2013/02/20 H.Osamoto		新規作成
/*========================================================*/
//	header( "Content-Type: Text/html; charset=UTF-8" );

	include('d_serv_ora.inc');
	include('inc/oraDBAccessMst.inc');
	include('inc/sql_collection_cond_pattern.inc');
	require_once('function.inc');
	require_once('/home/emap/src/Jsphon/Encoder.php');

	define("D_STATUS_NO_MATCH", "11");	// 該当データなし（絞込み条件なし）
	define("D_STATUS_DB_ERR",   "17");	// DBエラーステータスベースコード
	define("D_STATUS_PRM_ERR",  "19");	// パラメータエラーステータスベースコード

	define("D_DEF_JOIN_GRP", "AND");		// グループのデフォルト結合条件
	define("D_DEF_JOIN_LST", "AND");		// リスト項目のデフォルト結合条件
	define("D_DEF_JOIN_FLG", "OR");			// フラグ項目のデフォルト結合条件

	// JSON用タグ定義
	define("D_RET_CODE", "return_code");
	define("D_COND",     "cond");
	define("D_JOIN",     "join");
	define("D_GRP",      "grp");
	define("D_ITEM",     "item");

	$cgi_kind = "c01";	// CGI種別
	$enc = "UTF-8";		// 出力文字コード
	$status = "";		// ステータスコード

	// 入力パラメータ取得
	$cid = getCgiParameter('cid','');	// 企業ID

	while(1) {
		// 入力パラメータチェック
		if ( $cid == "" ) {
			$status = $cgi_kind . D_STATUS_PRM_ERR . "001";
			break;
		}

		// DB接続
		$dba = new oraDBAccessMst();
		if ( ! $dba->open() ) {
			$dba->close();
			$status = $cgi_kind . D_STATUS_DB_ERR . "900";	// DB接続エラー
			break;
		}

		// 絞込み条件取得(データ部)
		$retcd = getCondPattern( &$dba, $cid, &$json_cond_data );
		$dba->close();
		if ( $retcd != 0 ) {
			if ($retcd == "1") {
				// 該当データなし
				$status = $cgi_kind . D_STATUS_NO_MATCH . "009";	// 絞込み条件なし
			} else {
				// SQL実行エラー
				$status = $cgi_kind . D_STATUS_DB_ERR . "999";	// その他DBエラー
			}
			break;
		}

		$status = $cgi_kind . "00000";	// 正常ステータスコード

		break;
	}
	
	// ステータス部結合（エラー時はステータス部のみ出力）
	$output_str = outputJsonStatus($json_cond_data, $status);

	// 出力データの文字コード変換(EUC⇒UTF8)
	mb_convert_variables( $enc, 'EUC', $output_str);


	// json出力
	header( "Content-type: application/json charset=utf-8" );
	echo $output_str;

?>
