<?php
/*========================================================*/
// ファイル名：cp_img.cgi
// 処理名：企業画像データ取得
//
// 作成日：2012/02/13
// 作成者：Y.Matsukawa
//
// 解説：企業ID、媒体区分（PC／携帯／スマホ）、画像Noに該当する画像バイナリデータを返す
//
// パラメータ：(IN)cid  -  企業ID
//             (IN)kbn  -  媒体区分（P：PC／M：携帯／S：スマホ）
//             (IN)n    -  画像No.
// 更新履歴
// 2012/02/13 Y.Matsukawa	新規作成
// 2012/10/16 Y.Matsukawa	error_reporting()削除
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	
	include( "d_serv_ora.inc" );

	//CGI種別
	$cgi_kind = "809";

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
	if(isset($_VARS['cid']))		$cid = $_VARS['cid'];
	if(isset($_VARS['kbn']))		$kbn = $_VARS['kbn'];
	if(isset($_VARS['n']))			$n   = $_VARS['n'];

	//入力パラメータチェック
	if ( $cid == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	if ( $kbn == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	if ( $n == "" ) {
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

	/**
	 * SQLの作成
	 */
	$sql  = "select IMG_DATA"
			. " from CORP_IMG_TBL"
			. " where CORP_ID = '".$cid."'"
			. " and MEDIA_KBN = '". $kbn."'"
			. " and IMG_NO = ".$n
	;

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
