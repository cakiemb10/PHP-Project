<?php
/*========================================================*/
// ファイル名：icon_select.cgi
// 処理名：アイコンデータ取得
//
// 作成日：2007/02/01
// 作成者：K.Masuda
//
// 解説：企業ID、アイコンIDを取得し、
//       アイコンバイナリデータを返す
//
// パラメータ：(IN)cid      -  企業ID
//             (IN)icon_id  -  アイコンID
//
// 更新履歴
// 2007/02/01 K.Masuda		新規作成
// 2007/03/30 Y.Matsukawa	リターンコード出力時に付加されていたタグを除去
// 2007/06/15 Y.Matsukawa	アイコンIDに拡張子が付いていたら除去（アニメーションGIF対応で、擬似的に「.gif」を付ける必要があるため）
// 2007/07/11 Y.Matsukawa	オラクルエラー発生時にconnectionを切断していなかった
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2014/02/04 Y.Matsukawa	SQLインジェクション対策
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );

	//CGI種別
	$cgi_kind = "805";

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
		$cid          =  urldecode( $_GET['cid'] );
		$icon_id      =  urldecode( $_GET['icon_id'] );
	} else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
		$cid          =  urldecode( $_POST['cid'] );
		$icon_id      =  urldecode( $_POST['icon_id'] );
	}
	
	// 拡張子を除去		
	$icon_id_e = explode(".", $icon_id);
	$icon_id = $icon_id_e[0];

	//入力パラメータチェック
	if ( $cid == "" || $icon_id == "" ) {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	
	// SQLインジェクション対策		add 2014/02/04 Y.Matsukawa
	$cid = mb_ereg_replace("'", "''", $cid);
	$icon_id = mb_ereg_replace("'", "''", $icon_id);

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
		$from = " FROM IM_ICON_TBL ";
	} else {
		$from = " FROM ICON_TBL ";
	}
	// add 2013/08/05 N.Wada ]

	$sql  = 'SELECT ICON_DATA '
		  //. ' FROM ICON_TBL '	mod 2013/08/05 N.Wada
		  .  $from
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
	header( "Content-type: image/gif" );
	echo $data->load();

	OCIFreeStatement($stmt);
	OCILogoff($conn);

?>
