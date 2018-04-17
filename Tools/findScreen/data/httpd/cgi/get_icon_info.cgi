<?php
/*========================================================*/
// ファイル名：get_icon_info.cgi
// 処理名：アイコン情報を取得する
//
// 作成日：2007/06/11
// 作成者：Y.Matsukawa
//
// 解説：アイコン情報を取得する
//
// 更新履歴
//   ・2007/06/11 Y.Matsukawa	新規作成
//   ・2013/08/05 N.Wada        即時反映対象企業対応
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	include( "d_serv_ora.inc" );
	include( "inc/oraDBAccess.inc" );
	include( "inc/sql_collection_get_icon_info.inc" );
	require_once('function.inc');		// add 2013/08/05 N.Wada

	$cgi_kind = "891";	//CGI種別

	// 入力パラメータ取得
	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid = urldecode( $_GET['cid'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid = urldecode( $_POST['cid'] );
	}

	// 入力パラメータチェック
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		exit;
	}

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print   $cgi_kind . "17900\t0\t0\n";
		exit;
	}

	// 即時リフレッシュ対象設定を取得	add 2013/08/05 N.Wada
	$immref = isIMMREFAvailable( &$dba, $cid );

	// アイコン情報取得
	//$retcd = select_icon_info( &$dba, $cid, &$retdata, &$err_msg );	mod 2013/08/05 N.Wada
	$retcd = select_icon_info( &$dba, $cid, &$retdata, &$err_msg, $immref );
	if ( $retcd != 0 ) {
		$dba->close();
		if ( $retcd == 1 ) {
			print   $cgi_kind . "11009\t0\t0\n";    //検索結果データなし
		} else {    //9
			print   $cgi_kind . "17999\t0\t0\n";    //その他DBエラー
		}
		exit;
	}
	
	$dba->close();

	$reccount = count($retdata);
	print $cgi_kind . "00000\t$reccount\t$reccount\n";
	foreach($retdata as $rowdata){
		$buf =  $rowdata["KBN"]."\t".$rowdata["ICON_ID"]."\t".$rowdata["ICON_W"]."\t".$rowdata["ICON_H"];
		$buf .= "\n";
		print $buf;
	}
?>
