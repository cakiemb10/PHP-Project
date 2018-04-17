<?php
/*========================================================*/
// ファイル名：kyotenid_nolog.cgi
// 処理名：拠点ID検索（ログ出力なし）
//
// 作成日：2007/11/15
// 作成者：Y.Matsukawa
//
// 解説：指定拠点の情報を返す。
//
// kyotenid.cgiからログ出力機能を削除して作成。
// ■作成の経緯
//   拠点ID接続でアクセスした際、kyotenid.cgiが２回呼ばれていた。
//   （emapview.htmで１回、emapview_shop_detail.htmで１回）
//   この為、拠点別ログ集計で回数の２重カウントになってしまっていた。
//   →ログ出力しないkyotenid.cgi（当CGI）を作成し、emapview.htmからこれを呼び出すように変更しました。
//
// ※ログにカウントされずに拠点詳細を取得したい場合、このCGIを使用してください。
//
// 更新履歴
// 2007/11/15 Y.Matsukawa	新規作成
// 2009/02/16 Y.Matsukawa	半角変換機能を追加（z2hパラメータ）
// 2011/03/10 Y.Matsukawa	スマートフォン版対応
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/03/08 Y.Matsukawa	jkn対応
// 2012/11/13 Y.Matsukawa	JCN満空情報取得
// 2013/07/12 T.Sasaki		拠点（複数）画像取得対応 (mltimg [1]:有効、[未設定][0][1以外]:無効)
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2014/05/21 Y.Matsukawa	商品マスタ対応
// 2016/04/18 Y.Matsukawa	公開開始日等を出力
/*========================================================*/

	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		// add 2012/11/13 Y.Matsukawa
	include("ZdcCommonFunc.inc");	// 共通関数			add 2009/02/16 Y.Matsukawa
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/sql_collection_kyotenid.inc");
	include("chk.inc");         // データチェック関連
	//	include("log.inc");         // ログ出力
	include("crypt.inc");       // 暗号化
	include("jkn.inc");         // 検索条件編集
	require_once('function.inc');		// add 2012/11/13 Y.Matsukawa

	//	//ログ出力開始
	//	include("logs/inc/com_log_open.inc");

	$cgi_kind = "801";	//CGI種別
	$enc = "EUC";		//出力文字コード

	//入力パラメータ取得
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		$key    = urldecode($_GET['key']);      //APIキー
		$cid    = urldecode($_GET['cid']);      //企業ID
		$pos    = urldecode($_GET['kid']);      //拠点ID
		$type   = urldecode($_GET['type']);     //タイプ(1:拠点詳細、2:印刷画面、3:吹き出し出力、4:携帯出力)
		$opt    = urldecode($_GET['opt']);
		// mod 2011/07/05 Y.Nakajima [
		if (isset($_GET['z2h'])) {
			$z2h    = $_GET['z2h'];					//全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		} else {
			$z2h    = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$jkn = (isset($_GET['jkn']) ? $_GET['jkn'] : '');		// add 2012/03/08 Y.Matsukawa
		$cust = (isset($_GET['cust']) ? $_GET['cust'] : '');		// カスタマイズ指定		add 2012/11/13 Y.Matsukawa
		$mltimg = (isset($_GET['mltimg']) ? $_GET['mltimg'] : '');	// 拠点（複数）画像取得有無	add 2013/07/12 T.Sasaki
	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		$key    = urldecode($_POST['key']);     //APIキー
		$cid    = urldecode($_POST['cid']);
		$pos    = urldecode($_POST['kid']);
		$type   = urldecode($_POST['type']);
		$opt    = urldecode($_POST['opt']);
		// mod 2011/07/05 Y.Nakajima [
		if (isset($_POST['z2h'])) {
			$z2h    = $_POST['z2h'];				//全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		} else {
			$z2h    = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$jkn = (isset($_POST['jkn']) ? $_POST['jkn'] : '');		// add 2012/03/08 Y.Matsukawa
		$cust = (isset($_POST['cust']) ? $_POST['cust'] : '');		// カスタマイズ指定		add 2012/11/13 Y.Matsukawa
		$mltimg = (isset($_POST['mltimg']) ? $_POST['mltimg'] : '');	// 拠点（複数）画像取得有無	add 2013/07/12 T.Sasaki
	}

	//	/*==============================================*/
	//	// APIキーデコード      ※ログ出力で使用するだけなので、認証は行っていません。
	//	/*==============================================*/
	//	$KEY = f_decrypt_api_key( $key );
	//	// デコード後の文字列が壊れている場合はログに出力しない
	//	if (!chk_sb_anmb($KEY)){
	//		$KEY = "";
	//	}
	//
	//	// LOG出力用にパラメータ値を結合
	//	$parms = $kid;
	//	$parms .= " " . $type;

	//入力パラメータチェック
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		//		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	// mod 2011/07/05 Y.Nakajima [
	if (isset($_POST['kid']) && $_POST['kid'] != "") {
		$kid = $_POST['kid'];
	} else if (isset($_GET['kid']) && $_GET['kid'] != "") {
		$kid = $_GET['kid'];
	} else {
		$kid = "";
	}
	// mod 2011/07/05 Y.Nakajima ]
	
	if ( $kid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		//		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	//if ( intval($type) < 1 || intval($type) > 4 ) {		mod 2011/03/10 Y.Matsukawa
	if ( intval($type) < 1 || intval($type) > 5 ) {
		print   $cgi_kind . "19100\t0\t0\n";
		//		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}

	// jkn		add 2012/03/08 Y.Matsukawa
	//edit_jkn($jkn, &$edited_jkn, &$arr_log_jkn);		mod 2014/05/21 Y.Matsukawa
	edit_jkn($jkn, &$edited_jkn, &$arr_log_jkn, 'A.', '', $cid);

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print   $cgi_kind . "17900\t0\t0\n";
		//		put_log($cgi_kind."17900", $KEY, $opt, $parms);
		exit;
	}

	// 即時リフレッシュ対象設定を取得	add 2013/08/05 N.Wada
	$immref = isIMMREFAvailable( &$dba, $cid );

	//カラム名リスト取得
	$arr_col_name = Array();
	$retcd = select_col_name( &$dba, $cid, $type, &$arr_col_name, &$err_msg );
	if ( ($retcd != 0) && ($retcd != 1) ) {	//$retcd == 9の場合
		$dba->close();
		
		$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		print $out_retcd . "\t0\t0\n";
		//		//ログ出力
		//		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}
	
	//指定拠点情報取得（カラムnnについては、値設定のある項目のみ取得）
	$retcd = select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, 
		//&$kyoten_data, &$err_msg );		mod 2012/03/08 Y.Matsukawa
		//&$kyoten_data, &$err_msg, $edited_jkn );	mod 2013/08/05 N.Wada
		&$kyoten_data, &$err_msg, $edited_jkn, $immref );
	if ( $retcd != 0 ) {
		$dba->close();
		if ( $retcd == 1 ) {
			$out_retcd = $cgi_kind . "11009";    //検索結果データなし
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		}
		print $out_retcd . "\t0\t0\n";
		//		//ログ出力
		//		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	// 拠点画像（複数）データ取得
	// GET/POSTパラメータ[mltimg]に[1]が設定されているときのみ取得
	if ( $mltimg == '1' ) {
		//$retcd = select_kyoten_img_tbl( &$dba, $cid, $kid, &$arr_multi_img, &$err_msg );	mod 2013/08/05 N.Wada
		$retcd = select_kyoten_img_tbl( &$dba, $cid, $kid, &$arr_multi_img, &$err_msg, $immref );
		if ( $retcd != 0 && $retcd != 1 ) {
			$dba->close();
			$out_retcd = $cgi_kind . "17999";	 	//その他DBエラー
			print $out_retcd . "\t0\t0\n";
			//	//ログ出力
			//	put_log($out_retcd, $KEY, $opt, $parms);
			exit;
		}
	}

	$dba->close();

	// add 2012/11/13 Y.Matsukawa [
	// JCN満空情報取得
	$kyoten_data['KYOTEN_ID'] = $kid;
	$arr_kyoten = array();
	if ($cust == 'JCN') {
		$arr_kyoten[0] = $kyoten_data;
		JCNGetSpotStatus(&$arr_kyoten);
		$kyoten_data = $arr_kyoten[0];
	}
	// add 2012/11/13 Y.Matsukawa ]

	$out_retcd = $cgi_kind . "00000";
	print   $out_retcd . "\t1\t1\n";

	$buf =  $kyoten_data["LAT"]         	. "\t" .
			$kyoten_data["LON"]         	. "\t" .
			$kyoten_data["ICON_ID"]     	. "\t" .
			$kyoten_data["K_GIF_NUM"]     	. "\t" .
			$kyoten_data["BFLG"];
	if ( count($arr_col_name) > 0 ) {   //空ではない場合
		foreach( $arr_col_name as $rowdata2 ) {
			//$buf .= "\t" . $kyoten_data[$rowdata2["COL_NAME"]];		mod 2009/02/16 Y.Matsukawa
			// mod 2011/07/05 Y.Nakajima [
			if (isset($kyoten_data[$rowdata2["COL_NAME"]])) {
				$buf .= "\t" . ZdcConvZ2H($kyoten_data[$rowdata2["COL_NAME"]], $z2h);
			} else {
				$buf .= "\t";
			}
			// mod 2011/07/05 Y.Nakajima ]
		}
	}
	// add 2012/11/13 Y.Matsukawa [
	// JCN満空情報取得
	if ($cust == 'JCN') {
		$buf .= "\t";
		$buf .= $kyoten_data["JCN_SPOT_STATUS"]."\t";
		$buf .= $kyoten_data["JCN_SPOT_AVL_COUNT"];
	}
	
	// 拠点画像（複数）データ
	if ( $mltimg == '1' ) {
		if ( is_array($arr_multi_img) && count( $arr_multi_img ) > 0 ) {
			$parmMltImg = null;
			foreach ( $arr_multi_img as $multi_img ) {
				if ( isset( $parmMltImg ) ) {
					$parmMltImg .=	",";
				}
				$parmMltImg .= $multi_img["IMG_NO"];
			}
			$buf .= "\t";
			$buf .= $parmMltImg;
		} else {
			// 一つも画像がない
			$buf .= "\t";
		}
	}

	// add 2012/11/13 Y.Matsukawa ]
	// add 2016/04/18 Y.Matsukawa [
	// 【注意】この4項目は最後に追加するものとする！（順変更不可）
	$buf .= "\t";
	$buf .= $kyoten_data["PUB_S_DATE"] . "\t";
	$buf .= $kyoten_data["PUB_E_DATE"] . "\t";
	$buf .= $kyoten_data["DISP_NEW_S_DATE"] . "\t";
	$buf .= $kyoten_data["DISP_NEW_E_DATE"];
	// add 2016/04/18 Y.Matsukawa ]
	$buf .= "\n";
	if ( $enc != "EUC" ) {
		$buf    = mb_convert_encoding( $buf, $enc );
	}
	print $buf;

	//	//ログ出力
	//	put_log($out_retcd, $KEY, $opt, $parms);
?>
