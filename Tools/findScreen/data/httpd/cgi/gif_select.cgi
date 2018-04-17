<?php

/*========================================================*/
// ファイル名：gif_select.cgi
// 処理名：拠点画像データ取得
//
// 作成日：2007/02/01
// 作成者：K.Masuda
//
// 解説：企業ID、拠点IDを取得し、
//       拠点画像バイナリデータを返す
//
// パラメータ：(IN)cid  -  企業ID
//             (IN)kid  -  拠点ID
// 更新履歴
// 2007/02/01 K.Masuda		新規作成
// 2007/02/28 K.Masuda		ファイルタイプ判定追加
// 2007/03/30 Y.Matsukawa	リターンコード出力時に付加されていたタグを除去
// 2007/07/11 Y.Matsukawa	オラクルエラー発生時にconnectionを切断していなかった
// 2012/10/16 Y.Matsukawa	error_reporting()削除
// 2013/08/05 N.Wada		即時反映対象企業対応
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	
	include( "d_serv_ora.inc" );

	//CGI種別
	$cgi_kind = "806";

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid    =  urldecode( $_GET['cid'] );
		$kid    =  urldecode( $_GET['kid'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid    =  urldecode( $_POST['cid'] );
		$kid    =  urldecode( $_POST['kid'] );
	}

	//入力パラメータチェック
	if ( $cid == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	if ( $kid == "" ) {
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

	// add 2013/08/05 N.Wada
	/**
	 * 即時リフレッシュ対象設定を取得
	 */
	$immref = false;
	if (strtolower(ORA_TNS) == 'pub') {
		$sql = "select VALUE from EMAP_PARM_TBL";
		$sql .= " where CORP_ID = '".$cid."'";
		$sql .= " and KBN = 'IMMREF'";

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

		OCIFetchInto($stmt, $arr_param, OCI_ASSOC);
		if($stmt){
			OCIFreeStatement($stmt);
		}
		if ($arr_param) {
			$immref = ($arr_param['VALUE']=='1'?true:false);
		}
	}

	/**
	 * SQLの作成
	 */
	// add 2013/08/05 N.Wada [
	if ( $immref ) {
		$from = " FROM IM_KYOTEN_GIF_TBL ";
	} else {
		$from = " FROM KYOTEN_GIF_TBL ";
	}
	// add 2013/08/05 N.Wada ]

	$sql  = 'SELECT GIF_DATA '
		  //. ' FROM KYOTEN_GIF_TBL '	mod 2013/08/05 N.Wada
		  .  $from
		  . ' WHERE corp_id = \''  . $cid . '\'' 
		  . ' AND kyoten_id = \''  . $kid . '\'';

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

	$data = $arr['GIF_DATA'];

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
