<?php
/*========================================================*/
// ファイル名：pc_tpl_css_setting.cgi
// 処理名：PCテンプレートデザイン設定取得
//
// 作成日：2007/11/14
// 作成者：Y.Matsukawa
//
// 解説：PCテンプレートデザイン設定（serializeしたPHP変数）を取得
//
// 更新履歴
// 2007/11/14 Y.Matsukawa	新規作成
// 2012/10/16 Y.Matsukawa	error_reporting()削除
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );

	//CGI種別
	$cgi_kind = "811";

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	// パラメータ取得
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$cid = $_GET['cid'];
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$cid = $_POST['cid'];
	}
	
	//入力パラメータチェック
	if ($cid == "") {
		print $cgi_kind . "19100" . "\n";
		exit;
	}

	// DB接続
	$conn = OCILogon( ORA_USER , ORA_PASS , ORA_TNS );
	$err = OCIError();
	if ( $err ) {
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		print $cgi_kind . "17900" . "\n";
		exit;
	}

	// SQL文
	$sql = 'select SETTINGS'
		. ' from EMAP_PC_TPL_DESIGN'
		. ' WHERE CORP_ID = \''  . $cid . '\'';

	$stmt = OCIParse($conn, $sql);
	OCIExecute($stmt, OCI_DEFAULT);
	$err = OCIError($stmt);
	if ( $err ) {
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		print $cgi_kind . "17999" . "\n";
		exit;
	}

	OCIFetchInto($stmt, $arr, OCI_ASSOC);
	if ( ! $arr ) {
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		print $cgi_kind . "11009" . "\n";
		exit;
	}

	print $cgi_kind . "00000" . "\n";
	$data = $arr['SETTINGS'];
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);

?>
