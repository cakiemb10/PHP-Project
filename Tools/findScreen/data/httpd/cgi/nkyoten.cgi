<?php
/*========================================================*/
// ファイル名：nkyoten.cgi
// 処理名：最寄り拠点検索
//
// 作成日：2007/01/12
// 作成者：H.Ueno
//
// 解説：最寄り拠点リストを返す。
//
// 更新履歴
// 2007/01/12 H.Ueno		新規作成
// 2007/02/13 H.Ueno		ログ出力処理追加
// 2007/02/14 H.Ueno		出力をタブ区切りに変更
// 2007/02/22 H.Ueno		ログに戻り値を追加
// 2007/03/01 H.Ueno		出力にNEW表示開始/終了日を追加
// 2007/03/14 Y.Matsukawa	ログ出力項目のズレを修正
// 2007/03/23 Y.Matsukawa	ログ出力CIDを$cidから$optに変更
// 2007/04/12 Y.Matsukawa	knsu,radの上限値チェックを追加
// 2007/06/27 Y.Matsukawa	radの上限値チェックを廃止
// 2009/02/16 Y.Matsukawa	半角変換機能を追加（z2hパラメータ）
// 2009/10/13 Y.Matsukawa	最寄り拠点一覧に詳細拠点を出さない
// 2009/11/24 Y.Matsukawa	拠点項目拡張（50→200）
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/07/07 H.Osamoto		hourパラメータ追加 （1: 緯度経度を十進で扱う any：緯度経度をミリ秒で扱う）
// 2012/08/07 H.Osamoto		latlonが未指定時のログが規定のフォーマット通りに出力されない不具合を修正
// 2012/10/15 H.Osamoto		検索範囲の指定を実距離で指定可能に変更
// 2012/11/13 Y.Matsukawa	JCN満空情報取得
// 2013/08/02 Y.Matsukawa	任意地点から任意範囲外の拠点を除外
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2014/02/21 H.Osamoto		ポリゴン内外判定処置追加
// 2014/05/13 Y.Matsukawa	商品で絞り込み
// 2014/10/02 H.Osamoto		ルート距離算出時に出発地と目的地を入れ替え
// 2015/02/10 F.Yokoi		リアルタイムデータでの絞り込み追加
// 2015/03/23 F.Yokoi		絞込み条件の中にリアルタイムデータを参照する内容が含まれているか確認するcheck_jkn_rd()を追加する
// 2016/03/03 Y.Matsukawa	ソート指定
// 2016/03/10 Y.Matsukawa	円検索フラグ
// 2016/12/12 H.Yasunaga	ヤマトロッカー対応	ヤマトロッカー満空APIを使ってロッカーの最短納品日を取得し設定する
// 2017/04/12 H.Yasunaga	ローソンキャンペーンページ対応
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		// add 2012/11/13 Y.Matsukawa
	require_once('d_serv_emap.inc');	// add 2014/04/28 H.Osamoto
	include("ZdcCommonFunc.inc");	// 共通関数			add 2009/02/16 Y.Matsukawa
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("inc/sql_collection_nkyoten.inc");
	include("chk.inc");         // データチェック関連
	include("log.inc");         // ログ出力
	include("crypt.inc");       // 暗号化
	include("jkn.inc");         // 検索条件編集
	// add 2011/07/05 Y.Nakajima
	include("../pc/inc/function.inc");         // 文字エンコード処理
	require_once('function.inc');		// add 2012/11/13 Y.Matsukawa
	include("jkn_rd.inc");				// add 2015/02/10 F.Yokoi
	include("inc/rd_sql.inc");			// add 2015/02/10 F.Yokoi

	//ログ出力開始
	include("logs/inc/com_log_open.inc");

	$cgi_kind = "803";  //CGI種別

	// add 2011/07/05 Y.Nakajima [
	//初期化
	$key    = "";
	$cid    = "";
	$pos    = "";
	$cnt    = "";
	$lat    = "";
	$lon    = "";
	$latlon = "";
	$knsu   = "";
	$rad    = "";
	$jkn    = "";
	$opt    = "";
	$z2h    = "";
	$hour   = "";
	$absdist   = "";	// add 2012/10/15 H.Osamoto
	$exarea = "";		// add 2013/08/02 Y.Matsukawa
	$polycol   = "";	// add 2014/02/21 H.Osamoto
	// add 2011/07/05 Y.Nakajima ]
	$cust   = "";		// add 2012/11/13 Y.Matsukawa
	$sort   = "";		// add 2016/03/03 Y.Matsukawa
	$circle = "";		// add 2016/03/10 Y.Matsukawa

	// mod 2011/07/05 Y.Nakajima [
	if ( isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] == "GET" ) {
		foreach($_GET AS $key=>$value) {
			$key = str_replace("amp;", "", $key);
			$_GET[$key] = $value;
		}
	
		if (isset($_GET['key'])) {
			$key    = urldecode($_GET['key']);      //APIキー
		} 
		if (isset($_GET['cid'])) {
			$cid    = urldecode($_GET['cid']);
		} 
		if (isset($_GET['pos'])) {
			$pos    = urldecode($_GET['pos']);
		} 
		if (isset($_GET['cnt'])) {
			$cnt    = urldecode($_GET['cnt']);
		} 
		if (isset($_GET['lat'])) {
			$lat    = urldecode($_GET['lat']);
		} 
		if (isset($_GET['lon'])) {
			$lon    = urldecode($_GET['lon']);
		} 
		if (isset($_GET['latlon'])) {
			$latlon = urldecode($_GET['latlon']);   //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		} 
		if (isset($_GET['knsu'])) {
			$knsu   = urldecode($_GET['knsu']);
		}
		if (isset($_GET['rad'])) {
			$rad    = urldecode($_GET['rad']);
		}
		if (isset($_GET['jkn'])) {
			$jkn    = urldecode($_GET['jkn']);      //条件(ex."COL_01:'1' AND COL_03:FW:'中央口'")
		}
		if (isset($_GET['opt'])) {
			$opt    = urldecode($_GET['opt']);
		}
		if (isset($_GET['z2h'])) {
			$z2h    = $_GET['z2h'];		//全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		}
		if (isset($_GET['exkid'])) {
			$exkid  = $_GET['exkid'];	//除外拠点		add 2009/10/13 Y.Matsukawa
		}
		if (isset($_GET['hour'])) {
			$hour   = $_GET['hour'];		//緯度経度十進取得フラグ	add 2011/07/07 H.Osamoto
		}
		if (isset($_GET['absdist'])) {
			$absdist   = $_GET['absdist'];		//実距離指定フラグ	add 2012/10/15 H.Osamoto
		}
		if (isset($_GET['exarea'])) $exarea = $_GET['exarea'];		// add 2013/08/02 Y.Matsukawa
		// カスタマイズ指定		add 2012/11/13 Y.Matsukawa
		if (isset($_GET['cust'])) {
			$cust = $_GET['cust'];
		}
		if (isset($_GET['polycol'])) {
			$polycol   = $_GET['polycol'];		//ポリゴンカラム	add 2014/02/21 H.Osamoto
		}
		// ソート指定		add 2016/03/03 Y.Matsukawa
		if (isset($_GET['sort'])) {
			$sort = $_GET['sort'];
		}
		// 円検索		add 2016/03/10 Y.Matsukawa
		if (isset($_GET['circle'])) {
			$circle = $_GET['circle'];
		}

	} else if ( isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] == "POST" ) {
		if (isset($_POST['key'])) {
			$key    = urldecode($_POST['key']);     //APIキー
		}
		if (isset($_POST['cid'])) {
			$cid    = urldecode($_POST['cid']);     //as corp_id
		}
		if (isset($_POST['pos'])) {
			$pos    = urldecode($_POST['pos']);
		}
		if (isset($_POST['cnt'])) {
			$cnt    = urldecode($_POST['cnt']);
		}
		if (isset($_POST['lat'])) {
			$lat    = urldecode($_POST['lat']);
		}
		if (isset($_POST['lon'])) {
			$lon    = urldecode($_POST['lon']);
		}
		if (isset($_POST['latlon'])) {
			$latlon = urldecode($_POST['latlon']);  //緯度経度(xxxxxxxxx,yyyyyyyyy,XXXXXXXXX,YYYYYYYYY)
		}
		if (isset($_POST['knsu'])) {
			$knsu   = urldecode($_POST['knsu']);
		}
		if (isset($_POST['rad'])) {
			$rad    = urldecode($_POST['rad']);
		}
		if (isset($_POST['jkn'])) {
			$jkn    = urldecode($_POST['jkn']);     //条件
		}
		if (isset($_POST['opt'])) {
			$opt    = urldecode($_POST['opt']);
		}
		if (isset($_POST['z2h'])) {
			$z2h    = $_POST['z2h'];	//全角→半角変換オプション			add 2009/02/16 Y.Matsukawa
		}
		if (isset($_POST['exkid'])) {
			$exkid  = $_POST['exkid'];	//除外拠点		add 2009/10/13 Y.Matsukawa
		}
		if (isset($_POST['hour'])) {
			$hour   = $_POST['hour'];		//緯度経度十進取得フラグ	add 2011/07/07 H.Osamoto
		}
		if (isset($_POST['absdist'])) {
			$absdist   = $_POST['absdist'];		//実距離指定フラグ	add 2012/10/15 H.Osamoto
		}
		if (isset($_POST['exarea'])) $exarea = $_POST['exarea'];		// add 2013/08/02 Y.Matsukawa
		// mod 2011/07/05 Y.Nakajima ]
		// カスタマイズ指定		add 2012/11/13 Y.Matsukawa
		if (isset($_POST['cust'])) {
			$cust = $_POST['cust'];
		if (isset($_POST['polycol'])) {
			$polycol   = $_POST['polycol'];		//ポリゴンカラム	add 2014/02/21 H.Osamoto
		}
		}
		// ソート指定		add 2016/03/03 Y.Matsukawa
		if (isset($_POST['sort'])) {
			$sort = $_POST['sort'];
		}
		// 円検索		add 2016/03/10 Y.Matsukawa
		if (isset($_POST['circle'])) {
			$circle = $_POST['circle'];
		}
	}
	/*==============================================*/
	// APIキーデコード      ※ログ出力で使用するだけなので、認証は行っていません。
	/*==============================================*/
	$KEY = f_decrypt_api_key( $key );
	// デコード後の文字列が壊れている場合はログに出力しない
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}

	// 検索条件
	//edit_jkn($jkn, $edited_jkn, $arr_log_jkn);		mod 2009/11/24 Y.Matsukawa
	//edit_jkn($jkn, $edited_jkn, $arr_log_jkn, "", $rad);		mod 2014/05/13 Y.Matsukawa
	edit_jkn($jkn, $edited_jkn, $arr_log_jkn, "", $rad, $cid);
	$log_jkn = implode(" ", $arr_log_jkn);

	// LOG出力用にパラメータ値を結合（※緯度経度展開後にもう１回やってます↓）
	$parms = $lat;
	$parms .= " " . $lon;
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;
	//$parms .= " " . $rad;		del 2009/11/24 Y.Matsukawa

	//入力パラメータチェック
	if ( $cid == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	if ( $pos == "" ) {
		$pos = 1;
	} else {
		$pos = intval( $pos );
	}
	if ( $cnt == "" ) {
		$cnt = 100;
	} else {
		$cnt = intval( $cnt );
	}
	if ( $lat == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	if ( $lon == "" ) {
		print   $cgi_kind . "19100\t0\t0\n";
		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		exit;
	}
	// add 2011/07/07 H.osamoto [
	if ($hour) {
		cnv_auto2dms($lat, $rtnlat);
		$lat = $rtnlat;
		cnv_auto2dms($lon, $rtnlon);
		$lon = $rtnlon;
	}
	// add 2011/07/07 H.osamoto ]
	$arr_latlon = array();
	if ( $latlon != "" ) {
		// mod 2011/07/07 H.Osamoto [
		//	if ( ! preg_match( '/[0-9]*[\,][0-9]*[\,][0-9]*[\,][0-9]*/', $latlon ) ) {
		//		print   $cgi_kind . "19100\t0\t0\n";
		//		put_log($cgi_kind."19100", $KEY, $opt, $parms);
		//		exit;
		//	}
		if ($hour) {
			if ( ! preg_match( '/[0-9]*[\.][0-9]*[\,][0-9]*[\.][0-9]*[\,][0-9]*[\.][0-9]*[\,][0-9]*[\.][0-9]*/', $latlon ) ) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		} else {
			if ( ! preg_match( '/[0-9]*[\,][0-9]*[\,][0-9]*[\,][0-9]*/', $latlon ) ) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		}
		// mod 2011/07/07 H.Osamoto ]
		$arr_latlon = explode( ",", $latlon );
		if ( count($arr_latlon) != 4 ) {
			print   $cgi_kind . "19100\t0\t0\n";
			put_log($cgi_kind."19100", $KEY, $opt, $parms);
			exit;
		}
		// add 2011/07/07 H.osamoto [
		if ($hour) {
			for ( $ctr=0; $ctr<4; $ctr++ ) {
				cnv_auto2dms($arr_latlon[$ctr], $rtnpos);
				$arr_latlon[$ctr] = $rtnpos;
			}
		}
		// add 2011/07/07 H.osamoto ]
		foreach ( $arr_latlon as $rowdata ) {
			//if ( strlen( $rowdata ) != 9 ) {
			if ( strlen( $rowdata ) > 9 ) {
				print   $cgi_kind . "19100\t0\t0\n";
				put_log($cgi_kind."19100", $KEY, $opt, $parms);
				exit;
			}
		}
	}
	//--- ↓ for log ↓ -----
	$log_latlon = "";
	for ( $ctr=0; $ctr<4; $ctr++ ) {
		// mod 2012/08/07 H.Osamoto [
		//	// mod 2011/07/05 Y.Nakajima [
		//	if (isset($arr_latlon[$ctr])) {
		//		$log_latlon .= $arr_latlon[$ctr];
		//		if ( $ctr < 3 ) {
		//			$log_latlon .= " ";
		//		}
		//	}
		//	// mod 2011/07/05 Y.Nakajima ]
		if (isset($arr_latlon[$ctr])) {
			$log_latlon .= $arr_latlon[$ctr];
		}
		if ( $ctr < 3 ) {
			$log_latlon .= " ";
		}
		// mod 2012/08/07 H.Osamoto ]
	}
	//--- ↑ for log ↑ -----

	// LOG出力用にパラメータ値を結合
	$parms = $lat;
	$parms .= " " . $lon;
	$parms .= " " . $log_latlon;
	$parms .= " " . $log_jkn;
	//$parms .= " " . $rad;		del 2009/11/24 Y.Matsukawa

	if ( $knsu == "" ) {
		$knsu = 5;
	} else {
		$knsu = intval( $knsu );
	}
	if (!chk_knsu_max($knsu)) {
		// 上限値超過エラー
		print $cgi_kind . "19200\t0\t0\n";
		put_log($cgi_kind."19200", $KEY, $opt, $parms);
		exit;
	}
	if ( $rad == "" ) {
		$rad = 2000;
	}
	// 2007/06/27 del Y.Matsukawa
	//	if (!chk_rad_max($rad)) {
	//		// 上限値超過エラー
	//		print   $cgi_kind . "19200\t0\t0\n";
	//		put_log($cgi_kind."19200", $KEY, $opt, $parms);
	//		exit;
	//	}

	// 任意地点から任意範囲外を除外		add 2013/08/02 Y.Matsukawa
	$exArea = false;
	if ($exarea) {
		list($exlat, $exlon, $exrad) = explode(',', $exarea);
		if ($exlat && $exlon && $exrad) {
			$exArea['lat'] = $exlat;
			$exArea['lon'] = $exlon;
			$exArea['rad'] = $exrad;
		}
	}

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print $cgi_kind . "17900\t0\t0\n";
		put_log($cgi_kind."17900", $KEY, $opt, $parms);
		exit;
	}

	// add 2013/08/05 N.Wada
	// 即時リフレッシュ対象設定を取得
	$immref = isIMMREFAvailable( &$dba, $cid );

	//カラム名リスト取得
	$arr_col_name = Array();
	$retcd = select_col_name( &$dba, $cid, &$arr_col_name, &$err_msg );
	//if ( $retcd != 0 ) {
	if ( ($retcd != 0) && ($retcd != 1) ) {	//$retcd == 9の場合
		$msg_err = "select_col_name error. errno=";
		$msg_err .= $o_rtncd;
		$dba->close();
		if ( $retcd == 1 ) {
			$out_retcd = $cgi_kind . "11009";    //検索結果データなし
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		}
		print $out_retcd . "\t0\t0\n";
		//ログ出力
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	//最寄り拠点リスト取得（カラムnnについては、値設定のある項目のみ取得）
	$arr_near_kyoten = Array();
	if (!isset($exkid)) {
		$exkid ="";
	}

	// add 2015/02/10 F.Yokoi [
	// リアルタイム項目データ取得
	$arr_rd_item = Array();
	$arr_rd_item = selectRDItemDef(&$dba, $cid);
	// add 2015/02/10 F.Yokoi ]

	// add 2017/04/12 H.Yasunaga ローソンキャンペーン [
	// キャンペーン用テーブルを参照し、キャンペーンIDに一致する店舗IDを取得する
	// 取得した店舗IDのみ対象になるようにsqlの条件($edited_jkn)を編集する
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
	// add 2017/04/12 H.Yasunaga ]

	// mod 2015/02/10 F.Yokoi [
	// リアルタイムの場合
	if (count($arr_rd_item) > 0 && check_jkn_rd($jkn)) { // mod 2015/03/23 F.Yokoi
	//if (count($arr_rd_item) > 0) {
		edit_jkn_rd($jkn, $edited_jkn, $arr_log_jkn, "", $rad, $cid);

		$retcd = select_near_kyoten_rd( &$dba, $cid, $lat, $lon, $arr_latlon, $rad,
			$arr_col_name, "",
			$pos, $cnt, $knsu, $exkid, &$hit_num,
			&$arr_near_kyoten, &$err_msg, $absdist, &$exArea, $immref, $polycol, $arr_rd_item, $edited_jkn);
	} else {
		$retcd = select_near_kyoten( &$dba, $cid, $lat, $lon, $arr_latlon, $rad,
			$arr_col_name, $edited_jkn,
			//$pos, $cnt, $knsu, &$hit_num,		mod 2009/10/13 Y.Matsukawa
			$pos, $cnt, $knsu, $exkid, &$hit_num,
			//	&$arr_near_kyoten, &$err_msg );	mod 2012/10/15 H.Osamoto
			//&$arr_near_kyoten, &$err_msg, $absdist );		mod 2013/08/02 Y.Matsukawa
			//&$arr_near_kyoten, &$err_msg, $absdist, &$exArea);	mod 2013/08/05 N.Wada
			//&$arr_near_kyoten, &$err_msg, $absdist, &$exArea, $immref);		mod 2014/02/21 H.osamoto
			&$arr_near_kyoten, &$err_msg, $absdist, &$exArea, $immref, $polycol
			, $sort		// add 2016/03/03 Y.Matsukawa
			, $circle	// add 2016/03/10 Y.Matsukawa
			);
	}
	// mod 2015/02/10 F.Yokoi ]

	if ( $retcd != 0 ) {
		$dba->close();
		if ( $retcd == 1 ) {
			$out_retcd = $cgi_kind . "11009";    //検索結果データなし
		} else {    //9
			$out_retcd = $cgi_kind . "17999";    //その他DBエラー
		}
		print $out_retcd . "\t0\t0\n";
		//ログ出力
		put_log($out_retcd, $KEY, $opt, $parms);
		exit;
	}

	$dba->close();
	
	// JCN満空情報取得		add 2012/11/13 Y.Matsukawa
	if ($cust == 'JCN') {
		JCNGetSpotStatus(&$arr_near_kyoten);
	}
	// add 2016/12/12 H.Yasunaga ロッカー対応 [
	// ロッカー情報取得
	// del 2016/12/26 H.Yasunaga ログ削除 [
	// add 2016/12/15 H.Yasunaga ログ挿入 [
	//error_log(" nkyoten.cgi cust param:[" . $cust ."]\n");
	// add 2016/12/15 H.Yasunaga]
	// del 2016/12/26 H.Yasunaga]
	if ($cust == 'YTC_LOCKER') {
		$sdate = getCgiParameter('SDATE', '');	// 出荷予定日
		$hzip = getCgiParameter('HZIP', '');	// 発地郵便番号
		$bskbn = getCgiParameter('BSKBN', '');	// ボックスサイズ区分
		// del 2016/12/26 H.Yasunaga ログ削除 [
		// add 2016/12/15 H.Yasunaga ログ挿入 [
		//error_log("nkyoten.cgi SDATE:[" . $sdate ."]\n");
		//error_log("nkyoten.cgi HZIP:[" . $hzip . "]\n");
		//error_log("nkyoten.cgi BSKBN:[" . $bskbn . "]\n");
		// add 2016/12/15 H.Yasunaga]
		// del 2016/12/26 H.Yasunaga]

		if (empty($sdate) != true && empty($hzip) != true && empty($bskbn) != true) {
			require_once("./inc/function_YAMATO01.inc");	// 満空APIを使うカスタマイズ
			$pflg = "2";		// ポイントフラグ
			$datum = "TOKYO";	// 測地系
			$yamato01 = new YAMATO01($sdate, $hzip, $bskbn, $pflg, $datum);
			$arr_near_kyoten = $yamato01->getApiData($arr_near_kyoten);
		}
		$arrtmp = array_slice($arr_col_name, 0, count($arr_col_name) -2);
		$arr_lvl = array_slice($arr_col_name, count($arr_col_name) -2);
		$arrtmp[] = array("COL_NAME" => "YAMATO01_UKETORIKANODATE");
		$arr_col_name = array_merge($arrtmp, $arr_lvl);
	}
	// add 2016/12/12 H.Yasunaga ]
	
	// SMS業務支援道のり距離対応		add 2014/04/28 H.Osamoto
	if ($cust == 'SMSG') {
		foreach($arr_near_kyoten as $key => $rowdata){
			$dist =sqrt($rowdata["KYORI"]);
			if ($dist <= 8000) {
				//	$route_dist = getRouteDistance($lat, $lon, $rowdata["LAT"], $rowdata["LON"]);	mod 2014/10/02 H.Osamoto
				$route_dist = getRouteDistance($rowdata["LAT"], $rowdata["LON"], $lat, $lon);
				$arr_near_kyoten[$key]["KYORI"] = $route_dist;
			} else {
				$arr_near_kyoten[$key]["KYORI"] = "@@ERR@@_".$dist;
			}
		}
		// 道のり距離順にソート
		foreach ($arr_near_kyoten as $key => $value) {
			if (preg_match('/^@@ERR@@/', $value["KYORI"])) {
				$tmp = explode('_', $value["KYORI"]);
				$key_dist[] = "99999999".$tmp[1];
				$arr_near_kyoten[$key]["KYORI"] = "@@ERR@@";
			} else {
				$key_dist[] = intval($value["KYORI"]);
			}
		}
		array_multisort($key_dist, SORT_ASC, $arr_near_kyoten);
	}
	
	$rec_num = count( $arr_near_kyoten );
	if ( ($pos+$rec_num-1) < $hit_num ) {   //後続データ有り
		$out_retcd = $cgi_kind . "00001";
	} else {                            //後続データ無し
		$out_retcd = $cgi_kind . "00000";
	}
	print "$out_retcd\t$rec_num\t$hit_num\r\n";
	foreach( $arr_near_kyoten as $rowdata){
		// mod 2011/07/07 H.osamoto [
		//	$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
		//			$rowdata["LAT"]         . "\t" .
		//			$rowdata["LON"]         . "\t" .
		//			$rowdata["ICON_ID"]     . "\t" .
		//			sqrt($rowdata["KYORI"])	. "\t" .
		//			$rowdata["BFLG"];
		if ($hour) {
			// add 2014/04/28 H.Osamoto [
			if ($cust == 'SMSG') {
				$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
						cnv_dms2hour($rowdata["LAT"])         . "\t" .
						cnv_dms2hour($rowdata["LON"])         . "\t" .
						$rowdata["ICON_ID"]     . "\t" .
						$rowdata["KYORI"]	. "\t" .
						$rowdata["BFLG"];
			} else {
			// add 2014/04/28 H.Osamoto ]
				$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
						cnv_dms2hour($rowdata["LAT"])         . "\t" .
						cnv_dms2hour($rowdata["LON"])         . "\t" .
						$rowdata["ICON_ID"]     . "\t" .
						sqrt($rowdata["KYORI"])	. "\t" .
						$rowdata["BFLG"];
			// add 2014/04/28 H.Osamoto [
			}
			// add 2014/04/28 H.Osamoto ]
		} else {
			$buf =  $rowdata["KYOTEN_ID"]   . "\t" .
					$rowdata["LAT"]         . "\t" .
					$rowdata["LON"]         . "\t" .
					$rowdata["ICON_ID"]     . "\t" .
					sqrt($rowdata["KYORI"])	. "\t" .
					$rowdata["BFLG"];
		}
		// mod 2011/07/07 H.osamoto ]
		if ( count($arr_col_name) > 0 ) {   //空ではない場合
			foreach( $arr_col_name as $rowdata2 ) {
				//$buf .= "\t" . $rowdata[$rowdata2["COL_NAME"]];		mod 2009/02/16 Y.Matsukawa
				// mod 2011/07/05 Y.Nakajima [
				//データが無い場合でも、区切りのtabは必要
				$buf .= "\t";
				if (isset($rowdata2["COL_NAME"]) && isset($rowdata[$rowdata2["COL_NAME"]])) {
					//$buf .= ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
					$str = ZdcConvZ2H($rowdata[$rowdata2["COL_NAME"]], $z2h);
					//〜の変換処理追加(kyotenid.cgiデータ受取後のpc/inc/function.inc::ZdcSearchCgiKyotenid()と同様に)
					$str = ZdcConvertEncoding($str);
					$buf .= $str;
				}
				// mod 2011/07/05 Y.Nakajima ]
			}
		}
		$buf .= "\n";
		print $buf;
	}

	//ログ出力
	put_log($out_retcd, $KEY, $opt, $parms);
?>
