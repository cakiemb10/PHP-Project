<?php

/*========================================================*/
// ファイル名：gif_select2.cgi
// 処理名：拠点画像データ取得
//
// 作成日：2013/07/01
// 作成者：T.Sasaki
//
// 解説：企業ID、拠点ID、画像No.をKeyにKYOTEN_IMG_TBLより、
//		 拠点画像バイナリデータを返す
//
// パラメータ：(IN)cid	-  企業ID
//			   (IN)kid	-  拠点ID
//			   (IN)no	-  画像NO
// 更新履歴
// 2013/07/01 T.Sasaki		gif_select.cgiを流用して新規作成
// 2013/08/05 N.Wada		即時反映対象企業対応
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	
	include( "d_serv_ora.inc" );

	//CGI種別
	$cgi_kind = "806";

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid	=  urldecode( $_GET['cid'] );
		$kid	=  urldecode( $_GET['kid'] );
		$no		=  urldecode( $_GET['no'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid	=  urldecode( $_POST['cid'] );
		$kid	=  urldecode( $_POST['kid'] );
		$no		=  urldecode( $_POST['no'] );
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
	if ( $no == "" ) {
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
		$from = " FROM IM_KYOTEN_IMG_TBL ";
	} else {
		$from = " FROM KYOTEN_IMG_TBL ";
	}
	// add 2013/08/05 N.Wada ]

	$sql  = 'SELECT GIF_DATA '
		  //. ' FROM KYOTEN_IMG_TBL '	mod 2013/08/05 N.Wada
		  .  $from
		  . ' WHERE corp_id = \''  . $cid . '\'' 
		  . ' AND kyoten_id = \''  . $kid . '\''
		  . ' AND img_no = \''	   . $no  . '\'';

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
