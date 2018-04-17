<?php
/*========================================================*/
// ファイル名：kyotenarea.cgi
// 処理名：拠点エリア検索
//
// 作成日：2006/12/05
// 作成者：T.Tamagawa
//
// 解説：入力パラメータを取得後、パラメータの整合
//       チェックをして、データ検索用のSQLを生成後、
//       DBよりデータを取得し、CSVデータとして
//       ヘッダ情報およびリスト情報を返す。
//
// 更新履歴
// 2006/12/05 T.Tamagawa	新規作成
// 2006/12/22 T.Tamagawa	出力データに生データ追加
// 2007/01/12 H.Ueno		検索条件に公開終了日を追加
//							エラーコード変更
// 2007/01/17 Y.Matsukawa	オラクルアクセス方法を変更（ora.inc -> oraDBAccess.inc)
// 2007/02/13 H.Ueno		ログ出力処理追加
// 2007/02/22 H.Ueno		ログに戻り値を追加
// 2007/03/14 Y.Matsukawa	ログ出力項目のズレを修正
// 2007/03/23 Y.Matsukawa	ログ出力CIDを$cidから$optに変更
// 2007/03/30 Y.Matsukawa	encパラメータ廃止
// 2007/07/11 Y.Matsukawa	オラクルエラー発生時にconnectionを切断していなかった
// 2009/02/03 Y.Matsukawa	エリア検索カラム（文字列）がnullのデータを除外する（ひとまず第１階層のみ対応）
// 2009/02/16 Y.Matsukawa	半角変換機能を追加（z2hパラメータ）
// 2009/12/16 Y.Matsukawa	拠点項目拡張（50→200）
// 2010/11/03 K.Masuda		エリア検索複数対応
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2014/05/13 Y.Matsukawa	商品で絞り込み
// 2015/01/26 Y.Matsukawa	ソート項目の桁あわせ（sortlpad）「指定桁数,埋め込み文字」で指定（例）sortlpad=2,0
//							※ひとまず区分項目にだけ対応しました
// 2017/5/11 H.Yasunaga		ローソンキャンペーン対応
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	/*==============================================*/
	// ログ出力開始
	/*==============================================*/
	include("logs/inc/com_log_open.inc");

	// CGI番号
	$CGICD = "804";
	
	// 改行コード(LF)
	$RETCD = "\n";

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	include("ZdcCommonFunc.inc");	// 共通関数			add 2009/02/16 Y.Matsukawa
	include("chk.inc");         // データチェック関連
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("log.inc");         // ログ出力
	include("crypt.inc");       // 暗号化
	include("jkn.inc");         // 検索条件編集
	require_once("function.inc");			// 共通関数	add 2013/08/05 N.Wada

	/*==============================================*/
	// エラー出力を明示的にOFF
	/*==============================================*/
	error_reporting(0);

	/*==============================================*/
	// 初期化
	/*==============================================*/
	$status = $CGICD . "00000";
	$count = 0;
	$datacnt = 0;

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	/* APIキー */
	if ($_POST["key"] != "") {
		$KEY = $_POST["key"];
	}
	if ($_GET["key"] != "") {
		$KEY = $_GET["key"];
	}

	/* 取得位置 */
	if ($_POST["pos"] != "") {
		$POS = $_POST["pos"];
	}
	if ($_GET["pos"] != "") {
		$POS = $_GET["pos"];
	}
	if ($POS == "") {
		$POS = 1;
	}

	/* 取得件数 */
	if ($_POST["cnt"] != "") {
		$CNT = $_POST["cnt"];
	}
	if ($_GET["cnt"] != "") {
		$CNT = $_GET["cnt"];
	}
	if ($CNT == "") {
		$CNT = 100;
	}

	/* 企業ID */
	if ($_POST["cid"] != "") {
		$CID = $_POST["cid"];
	}
	if ($_GET["cid"] != "") {
		$CID = $_GET["cid"];
	}
	
	/* エリア検索条件 */
	if ($_POST["area"] != "") {
		$AREA = $_POST["area"];
	}
	if ($_GET["area"] != "") {
		$AREA = $_GET["area"];
	}

	/* 検索条件 */
	if ($_POST["jkn"] != "") {
		$JKN = $_POST["jkn"];
	}
	if ($_GET["jkn"] != "") {
		$JKN = $_GET["jkn"];
	}

	/* opt */
	if ($_POST["opt"] != "") {
		$OPT = $_POST["opt"];
	}
	if ($_GET["opt"] != "") {
		$OPT = $_GET["opt"];
	}
	
	if ($_POST["cust"] != "") {
		$CUST = $_POST["cust"];
	}
	if ($_GET["cust"] != "") {
		$CUST = $_GET["cust"];
	}

	// add 2010/11/03 K.Masuda [
	/* エリア検索パターン */
	// mod 2011/07/05 Y.Nakajima
	if (isset($_POST["areaptn"]) && $_POST["areaptn"] != "") {
		$AREAPTN = $_POST["areaptn"];
	} else
	// mod 2011/07/05 Y.Nakajima
	if (isset($_GET["areaptn"]) && $_GET["areaptn"] != "") {
		$AREAPTN = $_GET["areaptn"];
	}
	// mod 2011/07/05 Y.Nakajima
	if(!isset($AREAPTN))$AREAPTN=1;
	// add 2010/11/03 K.Masuda ]
	
	// ソート時桁あわせ		add 2015/01/26 Y.Matsukawa
	$SORTLPAD = ${'_'.$_SERVER['REQUEST_METHOD']}['sortlpad'];
	if ($SORTLPAD != '') {
		list($lpadlen, $lpadchar) = explode(',', $SORTLPAD);
		if (is_numeric($lpadlen) || $lpadchar != '') {
			$SORTLPAD = "$lpadlen,'$lpadchar'";
		} else {
			$SORTLPAD = '';
		}
	}

	/*==============================================*/
	// APIキーデコード      ※ログ出力で使用するだけなので、認証は行っていません。
	/*==============================================*/
	$KEY = f_decrypt_api_key( $KEY );
	// デコード後の文字列が壊れている場合はログに出力しない
	if (!chk_sb_anmb($KEY)){
		$KEY = "";
	}
	
	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 取得位置チェック */
	$Flg = NumChk($POS);
	if ($Flg != "OK") {
		$status = $CGICD . "19200";
		//      echo "取得位置 numエラー" . $RETCD; /* DEBUG */
	}
	if ($POS < 1) {
		//$status = $CGICD . "192001";
		$status = $CGICD . "19200";
		//      echo "取得位置 ゼロエラー" . $RETCD; /* DEBUG */
	}

	/* 取得件数チェック */
	$Flg = NumChk($CNT);
	if ($Flg != "OK") {
		$status = $CGICD . "19200";
		//      echo "取得件数 numエラー" . $RETCD; /* DEBUG */
	}
	if ($CNT < 1) {
		$status = $CGICD . "19200";
		//      echo "取得件数 ゼロエラー" . $RETCD; /* DEBUG */
	}

	/* 企業ID */
	if ($CID == "") {
		// 企業ID指定無しエラー
		$status = $CGICD . "19200";
	}

	/* 検索条件 */
	//edit_jkn($JKN, $edited_jkn, $arr_log_jkn, "k.");		mod 2014/05/13 Y.Matsukawa
	edit_jkn($JKN, $edited_jkn, $arr_log_jkn, "k.", '', $CID);
	$log_jkn = implode(" ", $arr_log_jkn);

	// LOG出力用にパラメータ値を結合（※エリア条件展開後にもう１回やってます↓）
	$parms = "";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;

	// エラー
	if ($status != $CGICD . "00000") {
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	
	/*==============================================*/
	// データベースに接続
	/*==============================================*/
	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		$status = $CGICD . "17900";
	}
	if ($status != $CGICD . "00000") {
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	
	// add 2017/5/11 H.Yasunaga ローソンキャンペーン対応 [
	if ($CUST == "lowsoncampaign") {
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
	// add 2017/05/11 H.Yasunaga ]


	// add 2013/08/05 N.Wada
	/*==============================================*/
	// 即時リフレッシュ対象設定を取得
	/*==============================================*/
	$immref = isIMMREFAvailable( &$dba, $CID );

	/*==============================================*/
	// データ項目名取得
	/*==============================================*/
	// add 2010/11/03 K.Masuda [
	$underbar = "";
	for($ucnt=0;$ucnt<$AREAPTN-2;$ucnt++){
		$underbar .= "_";
	}
	$out1ptn = $underbar."1%";
	$out2ptn = $underbar."2%";
	// add 2010/11/03 K.Masuda ]

	// mod 2011/07/05 Y.Nakajima
	if (!isset($AREA) || (isset($AREA) && $AREA == "")) {
		// mod 2010/11/03 K.Masuda [
		//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
		if( $AREAPTN == 1 ){
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
		} else {
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out1ptn . "' and corp_id='" . $CID . "'";
		}
		// mod 2010/11/03 K.Masuda ]
	} else {
		// mod 2010/11/03 K.Masuda [
		//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
		// mod 2011/07/05 Y.Nakajima
		if( isset($AREAPTN) && $AREAPTN == 1 ){
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
		} else {
			$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out2ptn . "' and corp_id='" . $CID . "'";
		}
		// mod 2010/11/03 K.Masuda ]
	}
	//echo $sql . $RETCD; /* DEBUG用 */
	
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME = $data["ITEM_NAME"];
			$COL_NAME  = $data["COL_NAME"];
			$VAL_KBN   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME = "";
			$COL_NAME  = "";
			$VAL_KBN   = "";
		}
		$dba->free($stmt);
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}

	// mod 2010/11/03 K.Masuda [
	//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
	if( $AREAPTN == 1 ){
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
	} else {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out1ptn . "' and corp_id='" . $CID . "'";
	}
	// mod 2010/11/03 K.Masuda ]
	//echo $sql . $RETCD; /* DEBUG用 */
	
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME_1 = $data["ITEM_NAME"];
			$COL_NAME_1  = $data["COL_NAME"];
			$VAL_KBN_1   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME_1 = "";
			$COL_NAME_1  = "";
			$VAL_KBN_1   = "";
		}
		$dba->free($stmt);
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}

	// 2007/05/14 add Y.Matsukawa ↓
	// mod 2010/11/03 K.Masuda [
	//$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
	if( $AREAPTN == 1 ){
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
	} else {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where opt_04 like '" . $out2ptn . "' and corp_id='" . $CID . "'";
	}
	// mod 2010/11/03 K.Masuda ]
	//echo $sql . $RETCD; /* DEBUG用 */

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	} else {
		if( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$ITEM_NAME_2 = $data["ITEM_NAME"];
			$COL_NAME_2  = $data["COL_NAME"];
			$VAL_KBN_2   = $data["VAL_KBN"];
		} else {
			$ITEM_NAME_2 = "";
			$COL_NAME_2  = "";
			$VAL_KBN_2   = "";
		}
		$dba->free($stmt);
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	// 2007/05/14 add Y.Matsukawa ↑

	if ($ITEM_NAME == "" or $ITEM_NAME_1 == "") {
		// エリア検索指定無しエラー
		$status = $CGICD . "11008";
	}

	// エリア検索指定条件をログ出力用JKNに入れる
	// mod 2011/07/05 Y.Nakajima [
	if (isset($AREA) && $AREA != "") {
		if (isset($COL_NAME_1) && $COL_NAME_1 != "") {
	// mod 2011/07/05 Y.Nakajima ]
			switch ($COL_NAME_1) {
				case "NAME":
					$idx = 1;
					break;
				case "ADDR":
					$idx = 2;
					break;
				case "FREE_SRCH":
					$idx = 53;
					break;
				default:
					//$idx = intval(substr($COL_NAME_1, 4, 2)) + 2;		del 2009/12/16 Y.Matsukawa
					// add 2009/12/16 Y.Matsukawa [
					$idx = intval(substr($COL_NAME_1, 4));
					if ($idx <= 50)
						$idx += 2;
					else
						$idx += 4;
					// add 2009/12/16 Y.Matsukawa ]
			}
			// mod 2011/07/05 Y.Nakajima
			if (isset($idx) && $idx != "") {
				$arr_log_jkn[$idx] = $AREA;
				$log_jkn = implode(" ", $arr_log_jkn);
			}
		}
	}

	// LOG出力用にパラメータ値を結合（エリア検索条件指定を反映）
	$parms = "";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " ";
	$parms .= " " . $log_jkn;
	
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	// mod 2011/07/05 Y.Nakajima
	if (!isset($AREA) || (isset($AREA) && $AREA == "") ) {
		/* 2007/05/14 mod Y.Matsukawa
		$head2 = $COL_NAME   . "\t" . $ITEM_NAME   . "\t" . ""    . "\t" . ""         . "\t" . ""; */
		$head2 = $COL_NAME   . "\t" . $ITEM_NAME   . "\t" . ""    . "\t" . $COL_NAME_2 . "\t" . $ITEM_NAME_2;
	} else {
		$AREA = mb_convert_encoding($AREA, "EUC-JP", "auto");
		$head2 = $COL_NAME_1 . "\t" . $ITEM_NAME_1 . "\t" . $AREA . "\t" . $COL_NAME . "\t" . $ITEM_NAME;
	}
	$head2 = ZdcConvZ2H($head2, $z2h);		// add 2009/02/16 Y.Matsukawa

	/*==============================================*/
	// 対象データ取得
	/*==============================================*/
	// add 2013/08/05 N.Wada [
	if ( $immref ) {
		$kyoten_tbl_name = "im_kyoten_tbl";
	} else {
		$kyoten_tbl_name = "kyoten_tbl";
	}
	// add 2013/08/05 N.Wada ]
	
	// ソート順（桁あわせ）		add 2015/01/26 Y.Matsukawa
	if ($SORTLPAD != '') {
		$SORT = "lpad($COL_NAME, $SORTLPAD)";
	} else {
		$SORT = $COL_NAME;
	}
	
	// 第１階層
	// mod 2011/07/05 Y.Nakajima
	if (!isset($AREA)  || (isset($AREA) && $AREA == "")) {
		// 区分項目
		if ($VAL_KBN == "L") {
			//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";	mod 2013/08/05 N.Wada
			$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
			$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
			$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
			$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //条件指定有りの場合
				$sql .= " and $edited_jkn ";
			}
			//$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;		mod 2015/01/26 Y.Matsukawa
			$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $SORT;
		// 文字列
		} else {
			$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
			$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
			//$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from kyoten_tbl k";	mod 2013/08/05 N.Wada
			$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
			//$sql = $sql . " where corp_id='" . $CID . "' group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			$sql = $sql . " where corp_id='" . $CID . "' ";
			$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //条件指定有りの場合
				$sql .= " and $edited_jkn ";
			}
			$sql = $sql . " and " . $COL_NAME . " is not null";		// add 2009/02/03 Y.Matsukawa
			$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
		}
	// 第２階層
	} else {
		$AREA = mb_convert_encoding($AREA, "EUC-JP", "auto");
		// 区分項目
		if ($VAL_KBN == "L") {
			// 第１階層が区分項目
			if ($VAL_KBN_1 == "L") {
				//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				//$sql = $sql . " and " . $COL_NAME_1 . "='" . $AREA;
				//$sql = $sql . "' group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
				$sql = $sql . " and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //条件指定有りの場合
					$sql .= " and $edited_jkn ";
				}
				//$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;		mod 2015/01/26 Y.Matsukawa
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $SORT;
			// 第１階層が文字列
			} else {
				//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				$sql = $sql . " and k." . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //条件指定有りの場合
					$sql .= " and $edited_jkn ";
				}
				//$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;		mod 2015/01/26 Y.Matsukawa
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $SORT;
			}
		// 文字列
		} else {
			// 第１階層が区分項目
			if ($VAL_KBN_1 == "L") {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				//$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
				//$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA;
				//$sql = $sql . "' group by " . $COL_NAME . " order by " . $COL_NAME . ")";
				$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //条件指定有りの場合
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			// 第１階層が文字列
			} else {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				//$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from kyoten_tbl k";	mod 2013/08/05 N.Wada
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
				//$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA;
				//$sql = $sql . "' group by " . $COL_NAME . " order by " . $COL_NAME . ")";
				$sql = $sql . " where corp_id='" . $CID . "' and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //条件指定有りの場合
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
			}
		}
	}

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = $CGICD . "17900";
	}
	if ($status != $CGICD . "00000") {
		$dba->close();		// 2007/07/11 add Y.Matsukawa
		$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
		$ords = $head . $RETCD;
		echo $ords;
		put_log($status, $KEY, $OPT, $parms);
		exit;
	}
	
	$count = 0;
	$datacnt = 0;
	$kyoten_cnt = 0;
	$ret = "";
	$dbflg = 0;

	// pos位置まで読み飛ばし
	for ($n = 1;$n<=$POS - 1;$n++) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$target3 = $data[2];
			$kyoten_cnt = $kyoten_cnt + $target3;
			$datacnt = $datacnt + 1;
		} else {
			$dbflg = 1;
			break;
		}
	}

	// 取得データ読み込み
	if ( $dbflg == 0 ) {
		for ($n=1; $n<=$CNT; $n++) {
			if( $dba->getRecInto( $stmt,$data ) ) {
				//$target1 = $data[0];		mod 2009/02/16 Y.Matsukawa
				$target1 = ZdcConvZ2H($data[0], $z2h);
				//$target2 = $data[1];		mod 2009/02/16 Y.Matsukawa
				$target2 = ZdcConvZ2H($data[1], $z2h);
				$target3 = $data[2];
				$ret = $ret . $target1 . "\t" . $target2 . "\t" . $target3 . $RETCD;;
				$count = $count + 1;
				$kyoten_cnt = $kyoten_cnt + $target3;
				$datacnt = $datacnt + 1;
			} else {
				$dbflg = 1;
				break;
			}
		}
	}

	// 後続データ確認
	if ( $dbflg == 0 ) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$status = $CGICD . "00001";
			$target3 = $data[2];
			$kyoten_cnt = $kyoten_cnt + $target3;
			$datacnt = $datacnt + 1;
		}
	}

	// 残りを全件取得
	while ($dba->getRecInto( $stmt,$data )) {
		$target3 = $data[2];
		$kyoten_cnt = $kyoten_cnt + $target3;
		$datacnt = $datacnt + 1;
	}

	$dba->free($stmt);

	/*==============================================*/
	// データ出力
	/*==============================================*/
	/* ヘッダ情報１出力 */
	if (strlen($ret) == 0) {
		/* ステータス */
		$status = $CGICD . "11009"; /* 該当データなし */
		$count = 0;
	}
	$head = sprintf("%08d\t%d\t%d", $status, $count, $datacnt); /* 10進表記 */
	$ords = $head . $RETCD;
	echo $ords;

	/* ヘッダ情報２出力 */
	$head2 = $head2 . "\t" . $kyoten_cnt . $RETCD;
	echo $head2;

	/* 検索情報出力 */
	echo $ret;

	/*==============================================*/
	// 切断
	/*==============================================*/
	$dba->close();

	/*==============================================*/
	// ログ出力
	/*==============================================*/
	put_log($status, $KEY, $OPT, $parms);
?>
