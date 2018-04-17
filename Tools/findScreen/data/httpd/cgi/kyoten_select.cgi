<?php
/*========================================================*/
// ファイル名：kyoten_select.cgi
// 処理名：拠点ID検索
//
// 作成日：2010/01/08
// 作成者：Y.Matsukawa
//
// 解説：拠点IDを受け取り、該当する拠点情報を取得する
//
// 更新履歴
// 2010/01/08 Y.Matsukawa	新規作成
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/10/17 Y.Matsukawa	error_reporting()削除
/*========================================================*/
/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = "k01";

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

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// 初期化
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
// add 2011/09/29 Y.Nakajima ]

/*==============================================*/
// パラメータ取得
/*==============================================*/
$KEY		= getCgiParameter("key","");			/* 認証キー */
$CID		= getCgiParameter("cid","");			/* e-map企業ID */
$KID		= getCgiParameter("kid","");			/* 拠点ID */
$PFLG		= getCgiParameter("pflg","2");			/* ポイントフラグ */
$DATUM		= getCgiParameter("datum",DATUM_TOKYO);	/* 測地系 */
$OUTF		= getCgiParameter("outf","JSON");		/* 出力形式 */
$ENC		= getCgiParameter("enc","SJIS");		/* 文字コード */
//$DTYPE		= getCgiParameter("dtype","6");			/* 表示項目パターン */
//$ND			= getCgiParameter("nd","SKIP");			/* 未入力項目返却指定 */

$OPTION_CD = mb_strimwidth($CID, 0, 20, '...');

// ↓セカイカメラ専用ロジック
// セカイカメラID→e-map企業IDに変換
if ($CID != "") {
	$UID = $CID;
	$OPTION_CD = $EMAP_CID[$CID];
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
$CgiOut = new KyotenCgiOutputJSON($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG, SEKAI_DTLTAG);
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
if (strlen($CID) == 0) {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// ↓セカイカメラ専用ロジック
$CID = $EMAP_CID[$CID];
// ↑セカイカメラ専用ロジック
if (!in_array($CID, $EMAP_CID)) {
	// 許可されていない企業ID
	$status = DEF_RETCD_DNE;// 該当データ無し
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 拠点ID */
if (strlen($KID) == 0) {
	$status = DEF_RETCD_PERR1;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// セカイカメラ拠点ID→e-map拠点IDに変換
$KID = sekaiId2KyotenId($UID, $KID);
if (strlen($KID) == 0) {
	// 変換失敗（正しいフォーマットでない）
	$status = DEF_RETCD_DNE;// 該当データ無し
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// ↑セカイカメラ専用ロジック
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
/* 文字コード */
if ($ENC != "SJIS" && $ENC != "EUC" && $ENC != "UTF8") {
	$status = DEF_RETCD_PERR2;
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
//$sql = "select COL_NAME,ITEM_NAME,VAL_KBN,ICON_KBN from KYOTEN_ITEM_TBL";
//$sql .= " where CORP_ID = '".escapeOra($CID)."'";
//switch ($DTYPE) {
//	case "1":
//		$sql .= " and SYOUSAI_KBN = '1'";
//		break;
//	case "2":
//		$sql .= " and INSATSU_KBN = '1'";
//		break;
//	case "3":
//		$sql .= " and FUKIDASI_KBN = '1'";
//		break;
//	case "4":
//		$sql .= " and M_SYOUSAI_KBN = '1'";
//		break;
//	case "5":
//		$sql .= " and LIST_KBN = '1'";
//		break;
//	case "6":
//		$sql .= " and OPT_04 = '1'";
//		break;
//	case "7":
//		$sql .= " and OPT_05 = '1'";
//		break;
//}
//$sql .= " and COL_NAME != 'NAME'";
//$sql .= " order by DISP_NUM";
//$stmt = null;
//if (!$dba->sqlExecute($sql, $stmt)) {
//	$dba->free($stmt);
//	$dba->close();
//	$status = DEF_RETCD_DERR3;
//	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
//	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
//	exit;
//}
//$arr_item = array();
//$i = 0;
//while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
//	$data['COL_NAME_LBL'] = $data['COL_NAME']." C$i";
//	$arr_item[] = $data;
//}
//$dba->free($stmt);

$arr_item = $KYOTEN_ITEM[$CID];
/*==============================================*/
// 最寄拠点検索
/*==============================================*/
$sql = "";
$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID";
$sql .= ", to_char(PUB_S_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_S_DATE";
$sql .= ", to_char(PUB_E_DATE, 'yyyy/mm/dd hh24:mi:ss') PUB_E_DATE";
$sql .= ", to_char(INS_DT, 'yyyy/mm/dd hh24:mi:ss') INS_DT";
$sql .= ", to_char(UPD_DT, 'yyyy/mm/dd hh24:mi:ss') UPD_DT";
$sql .= ", NAME";
if (is_array($arr_item) && count($arr_item) > 0) {
	foreach ($arr_item as $item) {
		$sql .= ", ".$item['COL_NAME_LBL'];
	}
}
$sql .= " from KYOTEN_TBL";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " and KYOTEN_ID = '".escapeOra($KID)."'";
if ($KYOTEN_FILTER[$CID]) {
	$sql .= " and ".$KYOTEN_FILTER[$CID];
}
$sql .= " and nvl(PUB_E_DATE, sysdate) >= sysdate";
// データ取得
$rec_num = 0;
$arr_kyoten = array();
$stmt = null;
if (!$dba->sqlExecute($sql, $stmt)) {
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

	list($w_ymd, $w_tim) = explode(' ', $data['PUB_S_DATE']);
	$data['PUB_S_DATE_YMD'] = explode('/', $w_ymd);
	$data['PUB_S_DATE_TIM'] = explode(':', $w_tim);
	// mod 2011/07/05 Y.Nakajima [
	//list($w_ymd, $w_tim) = explode(' ', $data['PUB_E_DATE']);
	if (isset($data['PUB_E_DATE'])) {
		list($w_ymd, $w_tim) = explode(' ', $data['PUB_E_DATE']);
	} else {
		$w_ymd = "";
		$w_tim = "";
	}
	$data['PUB_E_DATE_YMD'] = explode('/', $w_ymd);
	$data['PUB_E_DATE_TIM'] = explode(':', $w_tim);
	list($w_ymd, $w_tim) = explode(' ', $data['INS_DT']);
	$data['INS_DT_YMD'] = explode('/', $w_ymd);
	$data['INS_DT_TIM'] = explode(':', $w_tim);
	list($w_ymd, $w_tim) = explode(' ', $data['UPD_DT']);
	$data['UPD_DT_YMD'] = explode('/', $w_ymd);
	$data['UPD_DT_TIM'] = explode(':', $w_tim);
	$arr_kyoten[] = $data;
}
$dba->free($stmt);
$dba->close();

$hit_num = count($arr_kyoten);
$rec_num = count($arr_kyoten);
if (!$rec_num) {
	// 該当データ無し
	$status = DEF_RETCD_DNE;
	$CgiOut->set_status($status, 0, $hit_num); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
// 後続データ無し
$status = DEF_RETCD_DE;

// データ出力
$CgiOut->set_status($status, $rec_num, $hit_num);
$CgiOut->set_data_arr(&$arr_kyoten);
$CgiOut->output();

// ログ出力
put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
?>
