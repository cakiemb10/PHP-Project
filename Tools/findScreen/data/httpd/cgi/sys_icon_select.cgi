<?php
/*========================================================*/
//
//   cgi        :   sys_icon_select.cgi
//
//   機能       :   e-map SYS_ICON_TBL よりアイコンデータ取得
//                  (img タグ出力)
//
//   パラメータ :  (IN   )  -- cid     : 企業ID
//                 (IN   )  -- icon_id : アイコンID
//
// 更新履歴
// 2007/03/30 Y.Matsukawa	リターンコード出力時に付加されていたタグを除去
// 2007/07/11 Y.Matsukawa	オラクルエラー発生時にconnectionを切断していなかった
// 2012/10/16 Y.Matsukawa	error_reporting()削除
// 2015/09/06 Y.Matsukawa	セキュリティ対応（SQL Injection）
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );

	//CGI種別
	$cgi_kind = "808";

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid          =  urldecode( $_GET['cid'] );
		$icon_id      =  urldecode( $_GET['icon_id'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid          =  urldecode( $_POST['cid'] );
		$icon_id      =  urldecode( $_POST['icon_id'] );
	}

	// サニタイズ		add 2015/09/06 Y.Matsukawa
	$cid = mb_ereg_replace("['\"\|]", '', $cid);
	$icon_id = mb_ereg_replace("['\"\|]", '', $icon_id);

	//入力パラメータチェック
	if ( $cid == "" || $icon_id == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}

	// DB接続
	$conn = OCILogon( ORA_USER , ORA_PASS , ORA_TNS );
	$err = OCIError();
	if ( $err ) {
		// 2007/07/11 add Y.Matsukawa ↓
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		// 2007/07/11 add Y.Matsukawa ↑
		print $cgi_kind . "17900" . "\n";
		exit;
	}

	/**
	 * SQLの作成
	 */
	$sql  = 'SELECT ICON_DATA '
		  . ' FROM SYS_ICON_TBL '
		  . ' WHERE corp_id = \''  . $cid      . '\'' 
		  . ' AND   icon_id = \''  . $icon_id  . '\'';

	$stmt = OCIParse($conn, $sql);
	OCIExecute($stmt, OCI_DEFAULT);
	$err = OCIError($stmt);
	if ( $err ) {
		// 2007/07/11 add Y.Matsukawa ↓
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		// 2007/07/11 add Y.Matsukawa ↑
		print $cgi_kind . "17999" . "\n";
		exit;
	}

	OCIFetchInto($stmt, $arr, OCI_ASSOC);
	if ( ! $arr ) {
		// 2007/07/11 add Y.Matsukawa ↓
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		// 2007/07/11 add Y.Matsukawa ↑
		print $cgi_kind . "11009" . "\n";
		exit;
	}

	$data = $arr['ICON_DATA'];

	/**
	 * アイコン本体の出力
	 */
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);

?>
