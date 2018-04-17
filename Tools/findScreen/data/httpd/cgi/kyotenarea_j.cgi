<?php
/*========================================================*/
// ファイル名：kyotenarea_j.cgi
// 処理名：店舗エリア検索
//
// 更新履歴
// 2014/11/27 C.Eguchi	新規作成
/*========================================================*/

	/*==============================================*/
	// エラーコード用CGI識別数 設定
	/*==============================================*/
	$CGICD = "a01";

	/*==============================================*/
	// コード定義
	/*==============================================*/
	/* 入力パラメータ*/
	define( 'DEF_PRM_ENC_UTF8',			 'UTF8' );	   // 文字コード（UTF8）
	define( 'DEF_PRM_ENC_SJIS',			 'SJIS' );	   // 文字コード（SJIS）
	define( 'DEF_PRM_ENC_EUC',			  'EUC'  );	   // 文字コード（EUC）

	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );	   // 条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_DEND', '00001' );	   // 条件に見合うデータあり（後続データあり）
	define( 'DEF_RETCD_DNE1', '11008' );	   // エリア検索指定無しエラー
	define( 'DEF_RETCD_DNE2', '11009' );	   // 条件に見合うデータなし
	define( 'DEF_RETCD_DERR1','17900' );	   // データベース接続エラー
	define( 'DEF_RETCD_PERR1','19100' );	   // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19200' );	   // 入力パラメータエラー(構文エラー)

	/*==============================================*/
	// 定義ファイル
	/*==============================================*/
	include("ZdcCommonFunc.inc");	// 共通関数
	include("chk.inc");		 	// データチェック関連
	include("d_serv_ora.inc");
	include("inc/oraDBAccess.inc");
	include("jkn.inc");	   		// 検索条件編集
	require_once("function.inc");	// 共通関数
	include('apl_outf.inc');		// JSON出力用

	/*==============================================*/
	// エラー出力を明示的にOFF
	/*==============================================*/
	//error_reporting(E_ALL^E_NOTICE);
	//error_reporting(0);
	if ($D_DEBUG) ini_set('display_errors', '1');

	/*==============================================*/
	// 初期化
	/*==============================================*/
	// ステータス(リターンコード)
	if (!isset($status)){
		 $status = DEF_RETCD_DE;
	}

	/*==============================================*/
	// パラメータ取得
	/*==============================================*/
	$CID		= getCgiParameter('cid', 	'');				/* 企業ID */
	$AREA		= getCgiParameter('area', 	'');				/* エリア検索条件 */
	$FILTER		= getCgiParameter('filter', '');				/* 絞り込み条件 */
	$POS		= getCgiParameter('pos', 	1);					/* 取得位置(デフォルト1) */
	$CNT		= getCgiParameter('cnt', 	100);				/* 取得件数(デフォルト100) */
	$ENC		= getCgiParameter('enc', 	DEF_PRM_ENC_UTF8);	/* 文字コード(デフォルトUTF8) */


	// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
	$INPUT_ENC = $ENC ;

	$OPTION_CD = $CID;

	include('store_enc.inc');			// 文字コード変換

	/*==============================================*/
	// パラメータチェック
	/*==============================================*/
	/* 企業ID */
	if ($CID == '') {
		$status = DEF_RETCD_PERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	/* 取得開始位置*/
	if (NumChk($POS) != 'OK') {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	if ($POS < 1) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	/* 取得件数 */
	if (NumChk($CNT) != 'OK') {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	if ($CNT < 1) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	if ($CNT > 1000) {
		$CNT = 1000;
	}

	/* 文字コード */
	if ($INPUT_ENC != DEF_PRM_ENC_SJIS && 
		$INPUT_ENC != DEF_PRM_ENC_EUC &&
		$INPUT_ENC != DEF_PRM_ENC_UTF8) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}


	/* 絞り込み条件 */
	edit_jkn($FILTER, $edited_jkn, $arr_log_jkn, "k.", '', $CID);

	// エラー
	if ($status != DEF_RETCD_DE) {
		$status = DEF_RETCD_PERR2;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	
	/*==============================================*/
	// DB接続オープン
	/*==============================================*/
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		$status = DEF_RETCD_DERR1;
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	/*==============================================*/
	// 即時リフレッシュ対象設定を取得
	/*==============================================*/
	$immref = isIMMREFAvailable( &$dba, $CID );

	/*==============================================*/
	// データ項目名取得
	/*==============================================*/
	if (!isset($AREA) || (isset($AREA) && $AREA == "")) {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";
	}
	else {
		$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";
	}

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
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

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	// 第1階層
	$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=1 and corp_id='" . $CID . "'";

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
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

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}


	// 第2階層
	$sql = "select item_name,col_name,val_kbn from kyoten_item_tbl where area_use=2 and corp_id='" . $CID . "'";

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		$status = DEF_RETCD_DERR1;
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

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	if ($ITEM_NAME == "" or $ITEM_NAME_1 == "") {
		// エリア検索指定無しエラー
		$status = DEF_RETCD_DNE1;
	}

	// エリア検索指定条件をログ出力用JKNに入れる
	if (isset($AREA) && $AREA != "") {
		if (isset($COL_NAME_1) && $COL_NAME_1 != "") {
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
					$idx = intval(substr($COL_NAME_1, 4));
					if ($idx <= 50)
						$idx += 2;
					else
						$idx += 4;
			}
		}
	}

	if ($status != DEF_RETCD_DE) {
		$dba->close();
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}

	/*==============================================*/
	// 対象データ取得
	/*==============================================*/

	if ( $immref ) {
		$kyoten_tbl_name = "im_kyoten_tbl";
	} else {
		$kyoten_tbl_name = "kyoten_tbl";
	}

	if (!isset($AREA)  || (isset($AREA) && $AREA == "")) {
		// 区分項目
		if ($VAL_KBN == "L") {
			$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
			$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
			$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
			$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //条件指定有りの場合
				$sql .= " and $edited_jkn ";
			}
			$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
		// 文字列
		} else {
			$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
			$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
			$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
			$sql = $sql . " where corp_id='" . $CID . "' ";
			$sql = $sql . " and nvl( PUB_E_DATE, sysdate ) >= sysdate";
			if ( $edited_jkn != "" ) { //条件指定有りの場合
				$sql .= " and $edited_jkn ";
			}
			$sql = $sql . " and " . $COL_NAME . " is not null";
			$sql = $sql . " group by " . $COL_NAME . " order by " . $COL_NAME . ")";
		}
	// 第２階層
	} else {
		$AREA = mb_convert_encoding($AREA, "EUC-JP", "auto");
		// 区分項目
		if ($VAL_KBN == "L") {
			// 第１階層が区分項目
			if ($VAL_KBN_1 == "L") {
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				$sql = $sql . " and " . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //条件指定有りの場合
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
			// 第１階層が文字列
			} else {
				//$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v,kyoten_tbl k";
				$sql ="select " . $COL_NAME . ",ITEM_VAL_NAME,count(1) from kyoten_item_val_tbl v," . $kyoten_tbl_name . " k";
				$sql = $sql . " where k.corp_id='" . $CID . "' and k.corp_id=v.corp_id";
				$sql = $sql . " and v.col_name='" . $COL_NAME . "' and k." . $COL_NAME . "=v.ITEM_VAL";
				$sql = $sql . " and k." . $COL_NAME_1 . "='" . $AREA . "'";
				$sql = $sql . " and nvl( k.PUB_E_DATE, sysdate ) >= sysdate";
				if ( $edited_jkn != "" ) { //条件指定有りの場合
					$sql .= " and $edited_jkn ";
				}
				$sql = $sql . " group by ITEM_VAL_NAME," . $COL_NAME . " order by " . $COL_NAME;
			}
		// 文字列
		} else {
			// 第１階層が区分項目
			if ($VAL_KBN_1 == "L") {
				$sql ="select " . $COL_NAME . ",decode(instr(" . $COL_NAME . ",'##'),0," . $COL_NAME;
				$sql = $sql . ",substr(" . $COL_NAME . ",instr(" . $COL_NAME . ",'##')+2)),cnt";
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
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
				$sql = $sql . " from (select " . $COL_NAME . ",sum(1) as cnt from " . $kyoten_tbl_name . " k";
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
		$status = DEF_RETCD_DERR1;
	}
	if ($status != DEF_RETCD_DE) {
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}
	
	$rec_count  = 0;
	$hit_count  = 0;
	$data_count = 0;
	unset($area_list);
	$dbflg	  = 0;

	// pos位置まで読み飛ばし
	for ($n = 1;$n<=$POS - 1;$n++) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$target3 = $data[2];
			$data_count = $data_count + $target3;
			$hit_count = $hit_count + 1;
		} else {
			$dbflg = 1;
			break;
		}
	}

	// 取得データ読み込み
	if ( $dbflg == 0 ) {
		for ($n=1; $n<=$CNT; $n++) {
			if( $dba->getRecInto( $stmt,$data ) ) {
				$target1 = ZdcConvZ2H($data[0], $z2h);
				$target2 = ZdcConvZ2H($data[1], $z2h);
				$target3 = $data[2];
				$area_list[] = array(  "area_val"  => $target1
                                     , "disp_val"  => $target2
                                     , "val_count" => $target3);
				$rec_count = $rec_count + 1;
				$data_count = $data_count + $target3;
				$hit_count = $hit_count + 1;
			} else {
				$dbflg = 1;
				break;
			}
		}
	}

	// 後続データ確認
	if ( $dbflg == 0 ) {
		if( $dba->getRecInto( $stmt,$data ) ) {
			$status = DEF_RETCD_DEND;
			$target3 = $data[2];
			$data_count = $data_count + $target3;
			$hit_count = $hit_count + 1;
		}
	}

	// 残りを全件取得
	while ($dba->getRecInto( $stmt,$data )) {
		$target3 = $data[2];
		$data_count = $data_count + $target3;
		$hit_count = $hit_count + 1;
	}

	$dba->free($stmt);

	if (!isset($area_list)) {
		/* ステータス */
		$status = DEF_RETCD_DNE2; // 条件に見合うデータなし
		output_json($INPUT_ENC, array("return_code" => $CGICD.$status, "rec_count" => 0, "hit_count" => 0));
		exit;
	}


	/*==============================================*/
	// データ出力(正常)
	/*==============================================*/
	/* 検索データ部作成 */
	if (!isset($AREA) || (isset($AREA) && $AREA == "")) {
	
		$area_info = array(  "area1_col"	 => $COL_NAME
						   , "area1_name"	 => $ITEM_NAME
						   , "selected_area" => ""
						   , "area2_col"	 => $COL_NAME_2
						   , "area2_name"	 => $ITEM_NAME_2
						   , "data_count"	 => $data_count
						  );
	}
	else {
		$area_info = array(  "area1_col"	 => $COL_NAME_1
						   , "area1_name"	 => $ITEM_NAME_1
						   , "selected_area" => $AREA
						   , "area2_col"	 => $COL_NAME
						   , "area2_name"	 => $ITEM_NAME
						   , "data_count"	 => $data_count
						  );
	}

	output_json($INPUT_ENC, array(  "return_code" => $CGICD.$status
	                              , "rec_count"   => $rec_count
	                              , "hit_count"   => $hit_count
	                              , "area_info"   => $area_info
	                              , "area_list"   => $area_list
	                              ));

	exit;

	/*==============================================*/
	// 切断
	/*==============================================*/
	$dba->close();

?>
