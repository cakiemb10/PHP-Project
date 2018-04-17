<?php
/*========================================================*/
// ファイル名：kyoten_nearsearch.cgi
// 処理名：最寄り拠点検索
//
// 作成日：2010/01/08
// 作成者：Y.Matsukawa
//
// 解説：最寄り拠点リストを返す。
//
// 更新履歴
// 2010/01/08 Y.Matsukawa	新規作成
// 2010/01/25 Y.Matsukawa	出力項目追加（created,modified,comment_count）
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/10/17 Y.Matsukawa	error_reporting()削除
/*========================================================*/
// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off対応
//入力パラメータを取り込む処理を追加
//post,get
//同じ名称でパラメータがあった場合は？
//POSTを優先する
extract($_GET);
extract($_POST);
// add 2011/07/05 Y.Nakajima ]


/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = "k02";

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER["SCRIPT_FILENAME"], ".cgi"));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( "DEF_RETCD_DE",   "00000" );       //条件に見合うデータあり（後続データなし）
define( "DEF_RETCD_DEND", "00001" );       //条件に見合うデータあり（後続データあり）
define( "DEF_RETCD_DNE",  "11009" );       //条件に見合うデータなし
define( "DEF_RETCD_AERR", "12009" );       //認証エラー
define( "DEF_RETCD_DERR1","17900" );       //データベースアクセスエラー
define( "DEF_RETCD_DERR2","17002" );       //データベースアクセスエラー
define( "DEF_RETCD_DERR3","17999" );       //データベースアクセスエラー
define( "DEF_RETCD_PERR1","19100" );       //入力パラメータエラー(必須項目NULL)
define( "DEF_RETCD_PERR2","19200" );       //入力パラメータエラー(構文エラー)
define( "DEF_RETCD_PERR3","19200" );       //入力パラメータエラー(組み合わせエラー)

/*==============================================*/
// 上限値
/*==============================================*/
define("RAD_MAX",  100000);
define("KNSU_MAX", 1000);

/*==============================================*/
// 定義ファイル
/*==============================================*/
require_once("kyoten_outf.inc");		// 出力クラス定義
require_once("ZdcCommonFuncAPI.inc");	// 共通関数
require_once("function.inc");			// 共通関数
require_once("d_serv_ora.inc");
require_once("oraDBAccess.inc");
require_once("chk.inc");				// データチェック関連
require_once("log.inc");				// ログ出力
require_once("crypt.inc");				// 暗号化
require_once("auth.inc");				// 簡易認証

// ↓セカイカメラ専用ロジック
require_once("kyoten_def_sekaicamera.inc");	// セカイカメラ用定義
// ↑セカイカメラ専用ロジック

/*==============================================*/
// エラー出力を明示的にOFF
/*==============================================*/
//error_reporting(0);		del 2012/10/17 Y.Matsukawa

/*==============================================*/
//ログ出力開始
/*==============================================*/
include("logs/inc/com_log_open.inc");

/*==============================================*/
// パラメータ取得cgi/inc/function.inc内
/*==============================================*/
$KEY		= getCgiParameter("key","");			/* 認証キー */
$POS		= getCgiParameter("pos","1");			/* 取得位置 */
$CNT		= getCgiParameter("cnt","100");			/* 取得件数 */
$CID		= getCgiParameter("cid","");			/* e-map企業ID */
$LAT		= getCgiParameter("lat","");			/* 緯度 */
$LON		= getCgiParameter("lon","");			/* 経度 */
$KNSU		= getCgiParameter("knsu","100");		/* 指定件数 */
$RAD		= getCgiParameter("rad","2000");		/* 半径(m) */
$PFLG		= getCgiParameter("pflg","2");			/* ポイントフラグ */
$DATUM		= getCgiParameter("datum",DATUM_TOKYO);	/* 測地系 */
$OUTF		= getCgiParameter("outf","JSON");		/* 出力形式 */
$ENC		= getCgiParameter("enc","SJIS");		/* 文字コード */
//$DTYPE		= getCgiParameter("dtype","7");			/* 表示項目パターン */
//$ND			= getCgiParameter("nd","SKIP");			/* 未入力項目返却指定 */

$OPTION_CD = mb_strimwidth($CID, 0, 20, '...');

$CID_LIST = array();

if ($CID != "") {
	$CID_LIST = explode(',', $CID);
	//$CID_LIST = array_intersect($CID_LIST, $EMAP_CID);
	// ↓セカイカメラ専用ロジック
	// セカイカメラID→e-map企業IDに変換
	$w_uid_list = $CID_LIST;
	$CID_LIST = array();
	foreach ($w_uid_list as $w_uid) {
		if ($EMAP_CID[$w_uid] != "") {
			$CID_LIST[] = $EMAP_CID[$w_uid];
		}
	}
	$OPTION_CD = mb_strimwidth(implode(",", $CID_LIST), 0, 20, '...');
	// ↑セカイカメラ専用ロジック
} else {
	foreach ($EMAP_CID as $w_cid)
		$CID_LIST[] = $w_cid;
}

require_once("kyoten_enc.inc");			// 文字コード変換

/*==============================================*/
// APIキーデコード
/*==============================================*/
$KEY = f_decrypt_api_key( $KEY );
// デコード後の文字列が壊れている場合はログに出力しない
if (!chk_sb_anmb($KEY)){
	$KEY = "";
}

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$parms = $lat;
$parms .= " " . $lon;

/*==============================================*/
// 出力クラス
/*==============================================*/
// ↓セカイカメラ専用ロジック
require_once("kyoten_outf_sekaicamera.inc");	// 出力クラス定義（セカイカメラ）
$CgiOut = new KyotenCgiOutputJSON($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, SEKAI_AIRTAG);
// ↑セカイカメラ専用ロジック

/*==============================================*/
// 簡易認証（IPチェック）
/*==============================================*/
$ERRCD = api_key_check( $KEY );

if ($ERRCD != "0000") {
	$status = DEF_RETCD_AERR;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}


/*==============================================*/
// パラメータチェック
/*==============================================*/
/* e-map企業ID */
if (count($CID_LIST) == 0) {
	// 許可企業なし
	$status = DEF_RETCD_DNE;// 該当データ無し
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 測地系 */
if ($DATUM != DATUM_TOKYO && $DATUM != DATUM_WGS84) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 文字コード */
if ($ENC != "SJIS" && $ENC != "EUC" && $ENC != "UTF8") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 緯度 */
if ($LAT == "") {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 経度 */
if ($LON == "") {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 半径 */
if (NumChk($RAD) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($RAD < 0 || $RAD > RAD_MAX) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 指定件数 */
if (NumChk($KNSU) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($KNSU < 0 || $KNSU > KNSU_MAX) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 指定件数と半径チェック */
if ($KNSU == 0 && $RAD == 0) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($KNSU != 0 && $RAD == 0) {
	$RAD = RAD_MAX;
}
/* 取得位置 */
if (NumChk($POS) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($POS < 1) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 取得件数 */
if (NumChk($CNT) != "OK") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($CNT < 1) {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($CNT > 1000) {
	$CNT = 1000;
}
///* 表示項目パターン */
//if (NumChk($DTYPE) != "OK") {
//	$status = DEF_RETCD_PERR2;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
//if ($DTYPE < 1 || $DTYPE > 7) {
//	$status = DEF_RETCD_PERR2;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
///* 未入力項目返却指定 */
//if ($ND != "SKIP" && $ND != "PUT") {
//	$status = DEF_RETCD_PERR2;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
/* ポイントフラグ */
if ($PFLG != "1" && $PFLG != "2" && $PFLG != "3") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 出力形式 */
//if ($OUTF != "JSON" && $OUTF != "XML") {
if ($OUTF != "JSON") {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// 座標表記形式及び測地系の変換
/*==============================================*/
$res = cnv_ll2lldms($LAT, $LON, $DATUM, &$LAT, &$LON);
if (!$res) {
	// 緯度経度不正
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// DB接続オープン
/*==============================================*/
$dba = new oraDBAccess();
if (!$dba->open()) {
	$dba->close();
	$status = DEF_RETCD_DERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// カラム名リスト取得
/*==============================================*/
//$arr_item_list = array();
//$max_item_count = 0;
//foreach ($CID_LIST as $w_cid) {
//	$sql = "select COL_NAME,ITEM_NAME,VAL_KBN,ICON_KBN from KYOTEN_ITEM_TBL";
//	$sql .= " where CORP_ID = '".escapeOra($w_cid)."'";
//	switch ($DTYPE) {
//		case "1":
//			$sql .= " and SYOUSAI_KBN = '1'";
//			break;
//		case "2":
//			$sql .= " and INSATSU_KBN = '1'";
//			break;
//		case "3":
//			$sql .= " and FUKIDASI_KBN = '1'";
//			break;
//		case "4":
//			$sql .= " and M_SYOUSAI_KBN = '1'";
//			break;
//		case "5":
//			$sql .= " and LIST_KBN = '1'";
//			break;
//		case "6":
//			$sql .= " and OPT_04 = '1'";
//			break;
//		case "7":
//			$sql .= " and OPT_05 = '1'";
//			break;
//	}
//	$sql .= " and COL_NAME != 'NAME'";
//	$sql .= " order by DISP_NUM";
//	$stmt = null;
//	if (!$dba->sqlExecute($sql, $stmt)) {
//		$dba->free($stmt);
//		$dba->close();
//		$status = DEF_RETCD_DERR3;
//		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//		exit;
//	}
//	$arr_item_list[$w_cid] = array();
//	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
//		$arr_item_list[$w_cid][] = $data;
//	}
//	$dba->free($stmt);
//	if ($max_item_count < count($arr_item_list[$w_cid]))
//		$max_item_count = count($arr_item_list[$w_cid]);
//}
//foreach ($arr_item_list as $c => $arr_item) {
//	for ($i = 0; $i < $max_item_count; $i++) {
//		if ($arr_item[$i]['COL_NAME']) {
//			$arr_item_list[$c][$i]['COL_NAME_LBL'] = $arr_item[$i]['COL_NAME']." C$i";
//		} else {
//			$arr_item_list[$c][$i]['COL_NAME_LBL'] = "null C$i";
//		}
//	}
//}

/*==============================================*/
// 最寄拠点検索
/*==============================================*/
$sql = "";
foreach ($CID_LIST as $i => $w_cid) {
	if ($i > 0) $sql .= " union all ";
	$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
	$sql .= ", power( abs( LAT - $LAT ) * (  9 / 300000 * 1000 ), 2 )";
	$sql .= " + power( abs( LON - $LON ) * ( 11 / 450000 * 1000 ), 2 ) as KYORI";
	// add 2010/01/25 Y.Matsukawa [
	$sql .= ", to_char(PUB_S_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_S_DATE";
	$sql .= ", to_char(PUB_E_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_E_DATE";
	$sql .= ", to_char(INS_DT, 'yyyy/mm/dd hh24:mi:ss') INS_DT";
	$sql .= ", to_char(UPD_DT, 'yyyy/mm/dd hh24:mi:ss') UPD_DT";
	// add 2010/01/25 Y.Matsukawa ]
	$sql .= ", NAME";
//	$arr_item = $arr_item_list[$w_cid];
//	if (is_array($arr_item) && count($arr_item) > 0) {
//		foreach ($arr_item as $item) {
//			$sql .= ", ".$item['COL_NAME_LBL'];
//		}
//	}
	$sql .= " from KYOTEN_TBL";
	$sql .= " where CORP_ID = '".escapeOra($w_cid)."'";
	if ($KYOTEN_FILTER[$w_cid]) {
		$sql .= " and ".$KYOTEN_FILTER[$w_cid];
	}
	if ($RAD) {
		$sql .= " and LAT >= (".$LAT." - ((300000 / ( 9 * 1000)) * ".$RAD."))";
		$sql .= " and LAT <= (".$LAT." + ((300000 / ( 9 * 1000)) * ".$RAD."))";
		$sql .= " and LON >= (".$LON." - ((450000 / (11 * 1000)) * ".$RAD."))";
		$sql .= " and LON <= (".$LON." + ((450000 / (11 * 1000)) * ".$RAD."))";
	}
	$sql .= " and nvl(PUB_E_DATE, sysdate) >= sysdate";
}
$sql .= " order by KYORI, KYOTEN_ID, CORP_ID";
$sql = "select s.*, rownum rn from (".$sql.") s";
if ($KNSU) {
	$sql .= " where rownum <= $KNSU";
}
// ヒット件数取得
$hit_num = 0;
$stmt = null;
$sql_count = "select count(*) HITCNT from (".$sql.")";

if (!$dba->sqlExecute($sql_count, $stmt)) {
	$dba->free($stmt);
	$dba->close();
	$status = DEF_RETCD_DERR3;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
	$hit_num = $data['HITCNT'];
}
$dba->free($stmt);


// データ取得
$rec_num = 0;
$arr_kyoten = array();
if ($hit_num > 0) {
	$sql_data = "select * from (".$sql.")";
	$sql_data .= " where rn >= ".$POS;
	$to = $POS+$CNT-1;
	$sql_data .= " and rn <= ".$to;
	$stmt = null;

	if (!$dba->sqlExecute($sql_data, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
		exit;
	}
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		if ($DATUM == DATUM_WGS84) {
			// 測地系の変換（TOKYO=>WGS84）
			$res = cnv_transDatum($data['LAT'], $data['LON'], TKY_TO_WGS84, $w_lat, $w_lon);
			if ($res) {
				$data['LAT'] = $w_lat;
				$data['LON'] = $w_lon;
			}
		}
		// add 2010/01/25 Y.Matsukawa [
		list($w_ymd, $w_tim) = explode(' ', $data['PUB_S_DATE']);
		$data['PUB_S_DATE_YMD'] = explode('/', $w_ymd);
		$data['PUB_S_DATE_TIM'] = explode(':', $w_tim);
		// mod 2011/07/05 Y.Nakajima [
		if (isset($data['PUB_E_DATE'])) {
			list($w_ymd, $w_tim) = explode(' ', $data['PUB_E_DATE']);
		} else {
			$w_ymd = "";
			$w_tim = "";
		}
		// mod 2011/07/05 Y.Nakajima ]
		$data['PUB_E_DATE_YMD'] = explode('/', $w_ymd);
		$data['PUB_E_DATE_TIM'] = explode(':', $w_tim);
		list($w_ymd, $w_tim) = explode(' ', $data['INS_DT']);
		$data['INS_DT_YMD'] = explode('/', $w_ymd);
		$data['INS_DT_TIM'] = explode(':', $w_tim);
		list($w_ymd, $w_tim) = explode(' ', $data['UPD_DT']);
		$data['UPD_DT_YMD'] = explode('/', $w_ymd);
		$data['UPD_DT_TIM'] = explode(':', $w_tim);
		// add 2010/01/25 Y.Matsukawa ]
		$arr_kyoten[] = $data;
	}
	$dba->free($stmt);
	$rec_num = count($arr_kyoten);
}
$dba->close();

if (!$rec_num) {
	// 該当データ無し
	$status = DEF_RETCD_DNE;
	$CgiOut->set_status($status, 0, $hit_num); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
if (($POS+$rec_num-1) < $hit_num) {
	// 後続データ有り
	$status = DEF_RETCD_DEND;
} else {
	// 後続データ無し
	$status = DEF_RETCD_DE;
}

// データ出力
$CgiOut->set_status($status, $rec_num, $hit_num);
$CgiOut->set_data_arr(&$arr_kyoten);
$CgiOut->output();

// ログ出力
put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
?>
