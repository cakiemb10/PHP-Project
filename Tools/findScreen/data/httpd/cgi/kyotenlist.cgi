<?php
/*========================================================*/
// ファイル名：kyotenlist.cgi
// 処理名：拠点リスト検索
//
// 作成日：2007/01/12
// 作成者：H.Ueno
//
// 解説：拠点リストを返す。
//
// 更新履歴
// 2007/01/12 H.Ueno		新規作成
// 2007/02/13 H.Ueno		ログ出力処理追加
// 2007/02/14 H.Ueno		出力をタブ区切りに変更
// 2007/02/22 H.Ueno		ログに戻り値を追加
// 2007/03/01 H.Ueno		出力にNEW表示開始/終了日を追加
// 2007/03/14 Y.Matsukawa	ログ出力項目のズレを修正
// 2007/03/20 Y.Matsukawa	ソート設定に従ったソート順で取得するよう修正
// 2007/03/23 Y.Matsukawa	ログ出力CIDを$cidから$optに変更
// 2007/08/15 Y.Matsukawa	URLパラメータを２重にurldecodeしていた
// 2009/02/16 Y.Matsukawa	半角変換機能を追加（z2hパラメータ）
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/25 H.osamoto		任意のソート指定を追加（sortパラメータ）
// 2012/06/18 Y.Matsukawa	拠点ID（複数）指定検索
// 2012/11/13 Y.Matsukawa	JCN満空情報取得
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2014/05/13 Y.Matsukawa	商品で絞り込み
// 2017/4/21 H.Yasunaga		ローソンキャンペーン対応
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		// add 2012/11/13 Y.Matsukawa
	include("ZdcCommonFunc.inc");	// 共通関数			add 2009/02/16 Y.Matsukawa
	include("d_serv_ora.inc");
	include("oraDBAccess.inc");
	include("sql_collection_kyotenlist.inc");
	include("chk.inc");         // データチェック関連
	include("log.inc");         // ログ出力
	include("crypt.inc");       // 暗号化
	include("jkn.inc");         // 検索条件編集
	// add 2011/07/05 Y.Nakajima
	include("../pc/inc/function.inc");         // 文字エンコード処理
	require_once('function.inc');		// add 2012/11/13 Y.Matsukawa

	//ログ出力開始
	include("logs/inc/com_log_open.inc");

	// CGI種別
	$cgi_kind = "802";
	
	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	if ($_SERVER['REQUEST_METHOD'] == "GET") {
		// 2007/08/15 mod Y.Matsukawa
		//		$key    = urldecode($_GET['key']);      //APIキー
		//		$cid    = urldecode($_GET['cid']);      //企業ID
		//		$pos    = urldecode($_GET['pos']);      //取得位置
		//		$cnt    = urldecode($_GET['cnt']);      //取得件数
		//		$jkn    = urldecode($_GET['jkn']);      //条件(ex."COL_01:'1' AND COL_02:FW:'中央口'")
		//		$latlon = urldecode($_GET['latlon']);   //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		//		$opt    = urldecode($_GET['opt']);
		// mod 2011/07/05 Y.Nakajima [
		/*
		$key    = $_GET['key'];      //APIキー
		$cid    = $_GET['cid'];      //企業ID
		$pos    = $_GET['pos'];      //取得位置
		$cnt    = $_GET['cnt'];      //取得件数
		$jkn    = $_GET['jkn'];      //条件(ex."COL_01:'1' AND COL_02:FW:'中央口'")
		$latlon = $_GET['latlon'];   //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		$opt    = $_GET['opt'];
		$z2h    = $_GET['z2h'];		//全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		*/
		if (isset($_GET['key'])) {
			$key = $_GET['key'];    //APIキー
		} else {
			$key = "";
		}
		if (isset($_GET['cid'])) {
			$cid = $_GET['cid'];    //企業ID
		} else {
			$cid = "";
		}
		if (isset($_GET['pos'])) {
			$pos = $_GET['pos'];    //取得位置
		} else {
			$pos = "";
		}
		if (isset($_GET['cnt'])) {
			$cnt = $_GET['cnt'];    //取得件数
		} else {
			$cnt = "";
		}
		if (isset($_GET['jkn'])) {
			$jkn = $_GET['jkn'];    //条件(ex."COL_01:'1' AND COL_02:FW:'中央口'")
		} else {
			$jkn = "";
		}
		if (isset($_GET['latlon'])) {
			$latlon = $_GET['latlon'];    //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		} else {
			$latlon = "";
		}
		if (isset($_GET['opt'])) {
			$opt = $_GET['opt'];
		} else {
			$opt = "";
		}
		if (isset($_GET['z2h'])) {
			$z2h = $_GET['z2h'];    //全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		} else {
			$z2h = "";
		}
		if (isset($_GET['sort'])) {
			$sort   = $_GET['sort'];	//ソート指定						add 2011/08/25 H.osamoto
		} else {
			$sort   = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$kid = (isset($_GET['kid']) ? $_GET['kid'] : '');		// add 2012/06/18 Y.Matsukawa
		$cust = (isset($_GET['cust']) ? $_GET['cust'] : '');		// add 2012/11/13 Y.Matsukawa

	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
		// 2007/08/15 mod Y.Matsukawa
		//		$key    = urldecode($_POST['key']);     //APIキー
		//		$cid    = urldecode($_POST['cid']);     //企業ID
		//		$pos    = urldecode($_POST['pos']);     //取得位置
		//		$cnt    = urldecode($_POST['cnt']);     //取得件数
		//		$jkn    = urldecode($_POST['jkn']);     //条件
		//		$latlon = urldecode($_POST['latlon']);  //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		//		$opt    = urldecode($_POST['opt']);
		// mod 2011/07/05 Y.Nakajima [
		/*
		$key    = $_POST['key'];     //APIキー
		$cid    = $_POST['cid'];     //企業ID
		$pos    = $_POST['pos'];     //取得位置
		$cnt    = $_POST['cnt'];     //取得件数
		$jkn    = $_POST['jkn'];     //条件
		$latlon = $_POST['latlon'];  //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		$opt    = $_POST['opt'];
		$z2h    = $_POST['z2h'];	//全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		*/
		if (isset($_POST['key'])) {
			$key = $_POST['key'];     //APIキー
		} else {
			$key = "";
		}
		if (isset($_POST['cid'])) {
			$cid = $_POST['cid'];     //企業ID
		} else {
			$cid = "";
		}
		if (isset($_POST['pos'])) {
			$pos = $_POST['pos'];     //取得位置
		} else {
			$pos = "";
		}
		if (isset($_POST['cnt'])) {
			$cnt = $_POST['cnt'];     //取得件数
		} else {
			$cnt = "";
		}
		if (isset($_POST['jkn'])) {
			$jkn = $_POST['jkn'];     //条件
		} else {
			$jkn = "";
		}
		if (isset($_POST['latlon'])) {
			$latlon = $_POST['latlon'];  //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		} else {
			$latlon = "";
		}
		if (isset($_POST['opt'])) {
			$opt = $_POST['opt'];
		} else {
			$opt = "";
		}
		if (isset($_POST['z2h'])) {
			$z2h = $_POST['z2h'];    //全角→半角変換オプション
		} else {
			$z2h = "";
		}
		if (isset($_POST['sort'])) {
			$sort   = $_POST['sort'];	//ソート指定						add 2011/08/25 H.osamoto
		} else {
			$sort   = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$kid = (isset($_POST['kid']) ? $_POST['kid'] : '');		// add 2012/06/18 Y.Matsukawa
		$cust = (isset($_POST['cust']) ? $_POST['cust'] : '');		// add 2012/11/13 Y.Matsukawa
	}

	/*==============================================*/
	// APIキーデコード      ※ログ出力で使用するだけなので、認証は行っていません。
	/*==============================================*/
	$KEY = f_decrypt_api_key($key);
	// デコード後の文字列が壊れている場合はログに出力しない
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}
	
	/*==============================================*/
	// 検索条件
	/*==============================================*/
	//edit_jkn($jkn, $edited_jkn, $arr_log_jkn);		mod 2014/05/13 Y.Matsukawa
	edit_jkn($jkn, $edited_jkn, $arr_log_jkn, '', '', $cid);
	$log_jkn = implode(" ", $arr_log_jkn);

	/*==============================================*/
	// LOG出力用にパラメータ値を結合（※緯度経度展開後にもう１回やってます↓）
	/*==============================================*/
	$parms = "";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;

	/*==============================================*/
	// 入力パラメータチェック
	/*==============================================*/
	// 企業ID
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	// 取得位置
	if ($pos == "") {
		$pos = 1;
	}
	// 取得件数
	if ($cnt == "") {
		$cnt = 100;
	}
	// 緯度経度
	$arr_latlon = array();
	if ($latlon != "") {
		if (!preg_match('/[0-9]*[\,][0-9]*[\,][0-9]*[\,][0-9]*/', $latlon)) {
			print $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		$arr_latlon = explode(",", $latlon);
		if (count($arr_latlon) != 4) {
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		foreach ($arr_latlon as $rowdata) {
			//if ( strlen( $rowdata ) != 9 ) {
			if (strlen( $rowdata ) > 9) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		}
	}
	$log_latlon = "";
	for ($ctr=0; $ctr<4; $ctr++) {
		// mod 2011/07/05 Y.Nakajima [
		if (isset($arr_latlon[$ctr])) {
			$log_latlon .= $arr_latlon[$ctr];
		}
		// mod 2011/07/05 Y.Nakajima ]
		if ($ctr < 3) {
			$log_latlon .= " ";
		}
	}
	// 拠点ID（複数指定可）		add 2012/06/18 Y.Matsukawa
	$arr_kid = array();
	if ($kid != '') {
		$arr_kid = explode(',', $kid);
	}

	/*==============================================*/
	// LOG出力用にパラメータ値を結合
	/*==============================================*/
	$parms = "";
	$parms .= " ";
	$parms .= " " . $log_latlon;
	$parms .= " " . $log_jkn;

	/*==============================================*/
	// DB接続
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $cgi_kind . "17900\t0\t0\n";
		put_log($cgi_kind."17900", $KEY, $opt, $parms);
		exit;
	}

	// add 2013/08/05 N.Wada
	/*==============================================*/
	// 即時リフレッシュ対象設定を取得
	/*==============================================*/
	$immref = isIMMREFAvailable( &$dba, $cid );

	/*==============================================*/
	// カラム名リスト取得
	/*==============================================*/
	$arr_col_name = Array();
	$retcd = select_col_name(&$dba, $cid, &$arr_col_name, &$err_msg);
	//if ($retcd != 0) {
	if ( ($retcd != 0) && ($retcd != 1) ) {	//$retcd == 9の場合
		$dba->close();
		if ($retcd == 1) {
			$out_retcd = $cgi_kind . "11009";    //検索結果データなし
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		}
		print $out_retcd . "\t0\t0\n";
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}
	
	/*==============================================*/
	// ソート設定カラム取得
	/*==============================================*/
	$arr_sort = Array();
	$retcd = select_sort_col_name(&$dba, $cid, &$arr_sort, &$err_msg);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$out_retcd = $cgi_kind . "11009";    //検索結果データなし
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		}
		print $out_retcd . "\t0\t0\n";
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}
	// add 2011/08/25 H.osamoto [
	// mod 2011/09/09 Y.Nakajima
	if ($sort != "") {
		$arr_sort[0]["COL_NAME"] = $sort;
	}
	// add 2011/08/25 H.osamoto ]
	
	// add 2017/4/21 H.Yasunaga ローソンキャンペーン対応 [
	if ($cust == "lowsoncampaign") {
		// パラメータの値取り出し
		$campaignid = getCgiParameter("campaignid", '');
		if (strlen($campaignid) == 0) {
			// パラメータエラー
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		// カスタマイズ用incファイルの読み込み
		require_once("./inc/function_LAWSONCAMPAIGN.inc");
		// キャンペーンテーブルにキャンペーンIDが登録されているか確認
		$is_exist_campaignid = exist_campaignid($dba, $campaignid);
		if ($is_exist_campaignid == false) {
			// キャンペーンIDが存在しないエラー
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		// SQL条件式に検索結果がキャンペーン対象の店舗IDのみになる式の追加
		// kyoten_id in (select 店舗ID from キャンペーンテーブル where キャンペーンID = 'CGIパラメータのキャンペーンID')
		$edited_jkn = edit_jkn_campaign($edited_jkn, $campaignid);
	
	}
	// add 2017/04/21 H.Yasunaga ]
	
	/*==============================================*/
	// 拠点リスト取得（カラムnnについては、値設定のある項目のみ取得）
	/*==============================================*/
	$arr_kyoten_list = Array();
	$retcd = select_kyoten_list(&$dba, $cid, $arr_col_name, $edited_jkn, $arr_latlon, $arr_sort[0]["COL_NAME"],
								intval($pos), intval($cnt),
								$arr_kid,		// add 2012/06/18 Y.Matsukawa
								//&$hit_num, &$arr_kyoten_list, &$err_msg );
								&$hit_num, &$arr_kyoten_list, &$err_msg, $immref );	// mod 2013/08/05 N.Wada
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			$out_retcd = $cgi_kind . "11009";    //検索結果データなし
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		}
		print $out_retcd . "\t0\t0\n";
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	/*==============================================*/
	// DB切断
	/*==============================================*/
	$dba->close();

	// JCN満空情報取得		add 2012/11/13 Y.Matsukawa
	if ($cust == 'JCN') {
		JCNGetSpotStatus(&$arr_kyoten_list);
	}

	/*==============================================*/
	// 拠点リスト出力
	/*==============================================*/
	$rec_num = count($arr_kyoten_list);
	if (($pos+$rec_num-1) < $hit_num) {   //後続データ有り
		$out_retcd = $cgi_kind . "00001";
	} else {                                //後続データ無し
		$out_retcd = $cgi_kind . "00000";
	}
	print "$out_retcd\t$rec_num\t$hit_num\r\n";
	foreach($arr_kyoten_list as $rowdata){
		$buf =  $rowdata["KYOTEN_ID"] . "\t" .
				$rowdata["LAT"]       . "\t" .
				$rowdata["LON"]       . "\t" .
				$rowdata["ICON_ID"]   . "\t" .
				$rowdata["BFLG"];
		if ( count($arr_col_name) > 0 ) {   //空ではない場合
			foreach($arr_col_name as $rowdata2) {
				//$buf .= "\t" . $rowdata[$rowdata2["COL_NAME"]];		mod 2009/02/16 Y.Matsukawa
				// mod 2011/07/05 Y.Nakajima [
				//$buf .= "\t" . ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
				//データが存在しない時は、\tのみを記述する
				if (isset($rowdata2["COL_NAME"]) && isset($rowdata[$rowdata2["COL_NAME"]])) {
					$str = ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
					//〜の変換処理追加(kyotenid.cgiデータ受取後のpc/inc/function.inc::ZdcSearchCgiKyotenid()と同様に)
					$str = ZdcConvertEncoding($str);
					$buf .= "\t" . $str;
				} else {
					$buf .= "\t";
				}
				// mod 2011/07/05 Y.Nakajima ]
			}
		}
		$buf .= "\n";
		print $buf;
	}

	// ログ出力
	put_log($out_retcd, $KEY, $opt, $parms);
?>
