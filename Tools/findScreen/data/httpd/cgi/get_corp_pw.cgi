<?php
/*========================================================*/
// ファイル名：get_corp_pw.cgi
// 処理名：企業パスワード取得
//
// 作成日：2008/07/01
// 作成者：Y.Matsukawa
//
// 解説：EMAP(拠点案内サービス)の企業パスワードを取得する
//
// 更新履歴
//   ・2008/07/01 Y.Matsukawa		新規作成
/*========================================================*/
	header("Content-Type: text/plain; charset=euc-jp");
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/sql_collection_get_corp_pw.inc");
	include("inc/crypt.inc");

	$cgi_kind = "892";

	//入力パラメータ取得
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$cid = urldecode( $_GET['cid'] );
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$cid = urldecode( $_POST['cid'] );
	}

	//入力パラメータチェック
	if ($cid == "") {
		print $cgi_kind . "19100\n";
		exit;
	}

	// DB接続
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $cgi_kind . "17900\n";
		exit;
	}

	//カラム名リスト取得
	$arr_col = Array();
	$retcd = select_corp_pw(&$dba, $cid, &$arr_col, &$err_msg);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			print $cgi_kind . "11009\n";    //検索結果データなし
		} else {
			print $cgi_kind . "17999\n";    //その他DBエラー
		}
		exit;
	}
	
	// DB切断
	$dba->close();

	// パスワード暗号化（10バイト以上ないと正常に暗号／復号できないので、ダミー文字列を付加）
	$encpw = f_encrypt_api_key("PASSWORD=".$arr_col["PASSWD"]);

	// 出力
	print $cgi_kind . "00000\n";
	print $encpw."\n";
?>
