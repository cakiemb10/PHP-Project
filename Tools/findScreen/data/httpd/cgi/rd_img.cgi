<?php
/*========================================================*/
// ファイル名：rd_img.cgi
// 処理名：RD画像データ取得
//
// 更新履歴
// 2013/02/18 Y.Matsukawa	新規作成
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );

	$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
	$cid = urldecode($_VARS['cid']);
	$kid = urldecode($_VARS['kid']);
	$grp = urldecode($_VARS['grp']);
	$itm = urldecode($_VARS['itm']);

	//入力パラメータチェック
	if ($cid == "") {
		header("HTTP/1.0 404 Not Found");
		exit;
	}
	if ($kid == "") {
		header("HTTP/1.0 404 Not Found");
		exit;
	}

	// DB接続
	$conn = OCILogon(ORA_USER, ORA_PASS, ORA_TNS);
	$err = OCIError();
	if ($err) {
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		header("HTTP/1.0 404 Not Found");
		exit;
	}

	/**
	 * SQLの作成
	 */
	$sql  = "SELECT IMG_DATA"
		. " FROM RD_DATA_TBL"
		. " WHERE corp_id = '" . $cid . "'"
		. " AND kyoten_id = '" . $kid . "'"
		. " AND group_no = " . $grp
		. " AND item_no = " . $itm
		. " AND val_kbn = 'I'"
		. " AND img_data IS NOT NULL"
	;

	$stmt = OCIParse($conn, $sql);
	OCIExecute($stmt, OCI_DEFAULT);
	$err = OCIError($stmt);
	if ($err) {
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		header("HTTP/1.0 404 Not Found");
		exit;
	}

	OCIFetchInto($stmt, $arr, OCI_ASSOC);
	if (!$arr) {
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if($conn){
			OCILogOff($conn);
			$conn = false;
		}
		header("HTTP/1.0 404 Not Found");
		exit;
	}

	$data = $arr['IMG_DATA'];

	/**
	 * ファイルタイプの判定
	 */
	$file_typ_str = substr( $data->load() , 0 , 15 );
	if ( strpos( $file_typ_str , "PNG" ) ) {
		header( "Content-type: image/png" );
	} else if ( strpos( $file_typ_str , "GIF" ) ) {
		header( "Content-type: image/gif" );
	} else {
		header( "Content-type: image/jpeg" );
	}

	/**
	 * 画像本体の出力
	 */
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);
?>
