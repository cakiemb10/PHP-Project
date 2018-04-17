<?php
/*========================================================*/
// ファイル名：zskr_union.cgi
// 処理名：信用組合リスト検索
//
// 作成日：2016/02/29
// 作成者：H.Yasunaga
//
// 解説：信用組合リストを返す。
//       信用組合の読み仮名の行毎の総数を返す。
//
// 更新履歴
// 2016/02/29 H.Yasunaga		新規作成
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	require_once('d_serv_cgi.inc');		
	include("ZdcCommonFunc.inc");	// 共通関数
	include("d_serv_ora.inc");
	include("oraDBAccess.inc");
	include("sql_collection_kyotenlist.inc");
	include("sql_collection_zskr.inc");
	include("chk.inc");         // データチェック関連
	include("log.inc");         // ログ出力
	include("crypt.inc");       // 暗号化
	include("jkn.inc");         // 検索条件編集
	include("../pc/inc/function.inc");         // 文字エンコード処理
	require_once('function.inc');

	//ログ出力開始
	include("logs/inc/com_log_open.inc");

	// CGI種別
	$cgi_kind = "882";
	
	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	if ($_SERVER['REQUEST_METHOD'] == "GET") {

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
		if (isset($_GET['pcd'])) {
			$pcd = $_GET['pcd'];	// 都道府県コード
		} else {
			$pcd = "";
		}
		if (isset($_GET['ccd'])) {
			$ccd = $_GET['ccd'];	// 市区町村コード
		} else {
			$ccd = "";
		}
		if (isset($_GET['kana'])) {
			$kana = $_GET['kana'];	// カナ絞り込み
		} else {
			$kana = "";
		}
		
		if (isset($_GET['req_kana_cnt'])) {
			$req_kana_cnt = $_GET['req_kana_cnt'];	// かな別信用組合カウント
		} else {
			$req_kana_cnt = "";
		}

	} else if ($_SERVER['REQUEST_METHOD'] == "POST") {
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
		
		if (isset($_POST['pcd'])) {
			$pcd = $_POST['pcd'];	// 都道府県コード
		} else {
			$pcd = "";
		}
		
		if (isset($_POST['ccd'])) {
			$ccd = $_POST['ccd'];	// 市区町村コード
		} else {
			$ccd = "";
		}
		
		if (isset($_POST['kana'])) {
			$kana = $_POST['kana'];	// カナ絞り込み
		} else {
			$kana = $_POST['kana'];
		}
		
		if (isset($_POST['req_kana_cnt'])) {
			$req_kana_cnt = $_POST['req_kana_cnt'];	// かな別信用組合カウント
		} else {
			$req_kana_cnt = "";
		}

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

	
	/*==============================================*/
	// 信用組合リスト取得
	/*==============================================*/
	$arr_kyoten_list = Array();
	$retdata;
	if ($pcd != "" && $ccd != "") {
		// 住所コード指定のリスト
		$retcd = select_union_list(&$dba, $pcd, $ccd, &$retdata);
	} else if ($kana != ""){
		// カナの行指定のリスト
		$retcd = select_union_kana(&$dba, $kana, &$retdata);
	} else if ($req_kana_cnt != "") {
		// 50音の行のカウント
		$output_req_kana_cnt = true;
		$retcd = select_union_kana_cnt(&$dba, &$retdata);
	}
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
	
	if ($output_req_kana_cnt == false) {
		/*==============================================*/
		// 信用組合リスト出力
		/*==============================================*/
		$rec_num = count($arr_kyoten_list);
		if (($pos+$rec_num-1) < $hit_num) {   //後続データ有り
			$out_retcd = $cgi_kind . "00001";
		} else {                                //後続データ無し
			$out_retcd = $cgi_kind . "00000";
		}
		$out_retcd = $cgi_kind . "00000";
		
		print "$out_retcd\r\n";
		foreach($retdata as $rowdata){
			$buf =  $rowdata["UNION_ID"]        . "\t" .	// 金融機関コード
					$rowdata["UNION_NAME"]      . "\t" .	// 信用組合名称
					$rowdata["UNION_NAME_KANA"] . "\t" .	// 信用組合カナ名称
					$rowdata["NATION_WIDE_FLG"] . "\t" .	// 全国フラグ
					$rowdata["LAT"]             . "\t" .	// 緯度
					$rowdata["LON"]             . "\t" .	// 経度
					$rowdata["JURISDICTION_FILE"];			// 管轄エリア画像ファイル名
			$buf .= "\n";
			print $buf;
		}
	} else {
		/*==============================================*/
		// 信用組合50音行カウント出力
		/*==============================================*/
		$out_retcd = $cgi_kind . "00000";
		print "$out_retcd\r\n";
		$buf =  $retdata[0]["AROW"]	. "\t" .	// あ行
				$retdata[0]["KROW"]	. "\t" .	// か行
				$retdata[0]["SROW"]	. "\t" .	// さ行
				$retdata[0]["TROW"]	. "\t" .	// た行
				$retdata[0]["NROW"]	. "\t" .	// な行
				$retdata[0]["HROW"]	. "\t" .	// は行
				$retdata[0]["MROW"]	. "\t" .	// ま行
				$retdata[0]["YROW"]	. "\t" .	// や行
				$retdata[0]["RROW"]	. "\t" .	// ら行
				$retdata[0]["WROW"];			// わ行
		$buf .= "\n";
		print $buf;
	}

	// ログ出力
	put_log($out_retcd, $KEY, $opt, $parms);
?>
