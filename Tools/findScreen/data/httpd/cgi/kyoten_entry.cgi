<?php
/*========================================================*/
// 更新履歴
// 2015/09/29 F.Yokoi		新規作成
/*========================================================*/
//	error_reporting(0);

	/*==============================================*/
	// リターンコード定義
	/*==============================================*/
	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );       //初期値
	define( 'DEF_RETCD_DEND', '00001' );       //登録完了
	define( 'DEF_RETCD_DERR1','17900' );       //データベースアクセスエラー(DB接続エラー、設定取得エラー)
	define( 'DEF_RETCD_DERR2','17002' );       //データベースアクセスエラー(OCIExecute実行エラー)
	define( 'DEF_RETCD_DERR3','17999' );       //データベースアクセスエラー(ストアドリターンコードエラー)
	define( 'DEF_RETCD_PERR1','19100' );       //入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19200' );       //入力パラメータエラー(構文エラー)
	define( 'DEF_RETCD_PERR3','19300' );       //入力パラメータエラー(チェックエラー)

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	header('Content-Type: Text/html; charset=euc-jp');

	require_once('d_serv_cgi.inc');
	require_once('d_serv_emap.inc');
	include("ZdcCommonFunc.inc");         // 共通関数
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/oraDBAccessMst.inc");
	include("chk.inc");                   // データチェック関連
	include("log.inc");                   // ログ出力
	include("../pc/inc/function.inc");    // 文字エンコード処理
	require_once('function.inc');
	include("inc/ora_procif_kyoten_add.inc");
	include("inc/sql_collection_kyoten_add.inc");

	// ログ出力開始
	include("logs/inc/com_log_open.inc");

	ini_set('memory_limit', '64M');

	$status = DEF_RETCD_DE;
	$cgi_kind = "kyoten_entry";

	$corp_id = "";
	$lat = "";
	$lon = "";
	$icon_id = "";
	$kyoten_name = "";
	$kyoten_addr = "";
	$kyoten_pub_s_date = "";
	$kyoten_pub_e_date = "";
	$kyoten_new_s_date = "";
	$kyoten_new_e_date = "";

	$arr_entry_item = array();
	$arr_item_dtl = array();
	$arr_kyoten = array();

	if ($_SERVER['REQUEST_METHOD'] == 'GET') {
		$status = DEF_RETCD_PERR1;
		fwd_error_page("", $status);
	} else if ($_SERVER['REQUEST_METHOD'] == 'POST') {
		if ($_POST['corp_id'] != '') $corp_id = urldecode($_POST['corp_id']);
		if ($_POST['lat'] != '') $lat = urldecode($_POST['lat']);
		if ($_POST['lon'] != '') $lon = urldecode($_POST['lon']);
		if ($_POST['icon_id'] != '') $icon_id = urldecode($_POST['icon_id']);
		if ($_POST['kyoten_name'] != '') $kyoten_name = mb_convert_encoding (urldecode($_POST['kyoten_name']), "EUC-JP", "UTF-8");
		if ($_POST['kyoten_addr'] != '') $kyoten_addr = mb_convert_encoding (urldecode($_POST['kyoten_addr']), "EUC-JP", "UTF-8");
		if ($_POST['pub_s_date'] != '') $kyoten_pub_s_date = urldecode($_POST['pub_s_date']);
		if ($_POST['pub_e_date'] != '') $kyoten_pub_e_date = urldecode($_POST['pub_e_date']);
		if ($_POST['new_s_date'] != '') $kyoten_new_s_date = urldecode($_POST['new_s_date']);
		if ($_POST['new_e_date'] != '') $kyoten_new_e_date = urldecode($_POST['new_e_date']);

		foreach ($_POST as $key => $value) {
			if (preg_match('/COL[0-9]+/', $key)) {
				$col_no = preg_replace('/COL/', '', $key);
				$arr_entry_item[$col_no] = mb_convert_encoding (urldecode($value), "EUC-JP", "UTF-8");
			}
		}
	}

	// データ有無チェック
	if ($corp_id == "") { // 企業ID
		$status = DEF_RETCD_PERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":empty_corp_id ".join(" ", $_POST));
		exit;
	}
	if ($lat == "") { // 緯度
		$status = DEF_RETCD_PERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":empty_lat ".join(" ", $_POST));
		exit;
	}
	if ($lon == "") { // 経度
		$status = DEF_RETCD_PERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":empty_lon ".join(" ", $_POST));
		exit;
	}
	if ($icon_id == "") { // アイコンID
		$status = DEF_RETCD_PERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":empty_icon_id ".join(" ", $_POST));
		exit;
	}
	if ($kyoten_name == "") { // 拠点名
		$status = DEF_RETCD_PERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":empty_kyoten_name ".join(" ", $_POST));
		exit;
	}
	if ($kyoten_addr == "") { // 住所
		$status = DEF_RETCD_PERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":empty_kyoten_addr ".join(" ", $_POST));
		exit;
	}

	// 指定が無いときはすぐに表示できるように過去の日時を登録
	if ($kyoten_pub_s_date == '') {
		$kyoten_pub_s_date = "20010101000000";
	}

	// データベースオープン
	$dba = new oraDBAccess();
	if (! $dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", "", "Pub ".DEF_RETCD_DERR1);
		exit;
	}

	// 項目定義情報取得
	$ret = SelectKyotenItemTbl(&$dba, "", $corp_id, $retdata, $errMsg);
	if ($ret < 1) {
		$status = DEF_RETCD_DERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", "", "SelectKyotenItemTbl() ".DEF_RETCD_DERR1);
		exit;
	}
	else {
		foreach ($retdata as $key => $value) {
			$arr_item_dtl[$value["COL_NAME"]]["ITEM_NAME"] = $value["ITEM_NAME"];
			$arr_item_dtl[$value["COL_NAME"]]["VAL_KBN"] = $value["VAL_KBN"];
			$arr_item_dtl[$value["COL_NAME"]]["HTML_TAG_FLG"] = $value["HTML_TAG_FLG"];
			$arr_item_dtl[$value["COL_NAME"]]["SRCH_KBN"] = $value["SRCH_KBN"];
			$arr_item_dtl[$value["COL_NAME"]]["OPT_07"] = $value["OPT_07"];
		}
	}
	$dba->close();

	// データの登録
	// データベースオープン(MstDB)
	$dba_mst = new oraDBAccessMst();
	if (! $dba_mst->open()) {
		$dba_mst->close();
		$status = DEF_RETCD_DERR1;
		print $status;
		kyoten_entry_errorlog($corp_id, "", "", "Mst ".DEF_RETCD_DERR1);
		exit;
	}

	// 各COLの初期化
	for ($i = 1; $i <= 200; $i++) {
		$col_no = '';
		if ($i < 10) {
			$col_no = sprintf("%02d", $i);
		}
		else {
			$col_no = $i;
		}

		$arr_kyoten["COL_$col_no"] = '';
	}

	// 区分に合わせたデータチェック
	foreach ($arr_entry_item as $col_no => $value) {
		if ($arr_item_dtl["COL_$col_no"]['OPT_07'] == 1 && $arr_entry_item[$col_no] == "") {
			$status = DEF_RETCD_PERR3;
			print $status;
			kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":opt_07err ".join(" ", $_POST));
			exit;
		} else {
			switch($arr_item_dtl["COL_$col_no"]['VAL_KBN']) {
				case "B": // 区分がフラグの時
					if ($arr_entry_item[$col_no] != "") {
						if (preg_match('/^0|1$/', $arr_entry_item[$col_no])) { // フラグは0 or 1のみ
							$arr_kyoten["COL_$col_no"] = $arr_entry_item[$col_no];
						}
						else {
							$status = DEF_RETCD_PERR3;
							print $status;
							kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status." ".join(" ", $_POST));
							exit;
						}
					}
					break;
				case "L": // 区分が"区分"の時
					if ($arr_entry_item[$col_no] != "") {
						if (!preg_match('/[^a-zA-Z0-9]+/', $arr_entry_item[$col_no])) { // 半角英数のみ
							$arr_kyoten["COL_$col_no"] = $arr_entry_item[$col_no];
						}
						else {
							$status = DEF_RETCD_PERR3;
							print $status;
							kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status." ".join(" ", $_POST));
							exit;
						}
					}
					break;
				case "C": // 区分が"文字列"の時
					$arr_kyoten["COL_$col_no"] = $arr_entry_item[$col_no];
					break;
			}
		}
	}

	// 値を各配列に代入する
	$arr_kyoten['CORP_ID'] = $corp_id;
	$arr_kyoten['LAT'] = $lat;
	$arr_kyoten['LON'] = $lon;
	$arr_kyoten['ICON_ID'] = $icon_id;
	$arr_kyoten['NAME'] = $kyoten_name;
	$arr_kyoten['ADDR'] = $kyoten_addr;
	$arr_kyoten['PUB_S_DATE'] = $kyoten_pub_s_date;
	$arr_kyoten['PUB_E_DATE'] = $kyoten_pub_e_date;
	$arr_kyoten['DISP_NEW_S_DATE'] = $kyoten_new_s_date;
	$arr_kyoten['DISP_NEW_E_DATE'] = $kyoten_new_e_date;

	$arr_kyoten['REFRESH_FLG'] = "";
	$arr_kyoten['URL'] = "";
	$arr_kyoten['M_URL'] = "";
	$arr_kyoten['M_LEVEL'] = "";
	$arr_kyoten['E_FLG'] = "";
	$arr_kyoten['INS_DT'] = "";
	$arr_kyoten['UPD_DT'] = "";

	$i_kbn = "I";
	$i_commit_mode = 1;
	$i_uid = "kyety";
	$status = 1;

	$o_ins_dt = "";
	$o_upd_dt = "";
	$o_rtncd = "";

	if (!spif_p_kyoten_data_add_autonum(&$dba_mst, $i_kbn, $i_uid, $arr_kyoten, $o_rtncd, $i_commit_mode)) {
		$dba_mst->rollbackTransaction();
		$dba_mst->close();

		$status = DEF_RETCD_DERR2;
		print $status;
		kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status." ".join(" ", $_POST));
		exit;

	}
	else {
		if ((int) $o_rtncd > 0) {
			$dba_mst->rollbackTransaction();
			$dba_mst->close();

			$status = DEF_RETCD_DERR3;
			print $status;
			kyoten_entry_errorlog($corp_id, "", $kyoten_name, "spif_p_kyoten_data_add_autonum:".$status.":".$o_rtncd." ".join(" ", $_POST));
			exit;
		}
	}

	$dba_mst->commitTransaction();
	$dba_mst->close();
	$status = DEF_RETCD_DEND;

	print $status;
	exit;

// ------------------------------------------------------------
// エラー情報出力
// ------------------------------------------------------------
function kyoten_entry_errorlog($corp_id, $kyoten_id, $kyoten_name, $str){
	@error_log(date('Y/m/d H:i:s')." ".$corp_id." ".$kyoten_id." ".$kyoten_name." ".$str."\n", 3, '/var/tmp/kyoten_entry_error_'.date('Ymd').'.log');
}

?>
