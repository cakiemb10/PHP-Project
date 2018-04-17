<?php
/*========================================================*/
// ファイル名：lw_searchkyoten.cgi
// 処理名：【ローソン向けカスタマイズ】拠点条件検索
//
// 更新履歴
// 2010/12/10 Y.Matsukawa	新規作成
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/01/26 K.Masuda		NEW表示(開始/終了)日時の追加
// 2012/10/17 Y.Matsukawa	error_reporting()削除
/*========================================================*/

// add 2011/07/05 Y.Nakajima [
//php.ini regsiterGlobals off対応
//入力パラメータを取り込む処理を追加
//get
extract($_GET);

/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = 'w02';

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE',   '00000' );       //条件に見合うデータあり（後続データなし）
define( 'DEF_RETCD_DEND', '00001' );       //条件に見合うデータあり（後続データあり）
define( 'DEF_RETCD_DNE',  '11009' );       //条件に見合うデータなし
define( 'DEF_RETCD_AERR', '12009' );       //認証エラー
define( 'DEF_RETCD_DERR1','17900' );       //データベースアクセスエラー
define( 'DEF_RETCD_DERR2','17002' );       //データベースアクセスエラー
define( 'DEF_RETCD_DERR3','17999' );       //データベースアクセスエラー
define( 'DEF_RETCD_PERR1','19100' );       //入力パラメータエラー(必須項目NULL)
define( 'DEF_RETCD_PERR2','19200' );       //入力パラメータエラー(構文エラー)
define( 'DEF_RETCD_PERR3','19200' );       //入力パラメータエラー(組み合わせエラー)

/*==============================================*/
// 定義ファイル
/*==============================================*/
require_once('lw_outf.inc');			// 出力クラス定義（ローソン用）
require_once('ZdcCommonFuncAPI.inc');	// 共通関数
require_once('function.inc');			// 共通関数
require_once('d_serv_ora.inc');
require_once('oraDBAccess.inc');
require_once('chk.inc');				// データチェック関連
require_once('log.inc');				// ログ出力
require_once('auth.inc');				// 簡易認証
require_once("jkn.inc");				// 絞り込み条件編集
require_once('lw_def.inc');				// ローソン用定義

/*==============================================*/
// エラー出力を明示的にOFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
//error_reporting(0);		del 2012/10/17 Y.Matsukawa

/*==============================================*/
//ログ出力開始
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// パラメータ取得
/*==============================================*/
$CID		= $D_CID;								/* e-map企業ID */
$KEY		= '              2'.$CID;
$LAT		= getCgiParameter('lat','');			/* 緯度 */
$LON		= getCgiParameter('lon','');			/* 経度 */
$FREWD		= getCgiParameter('frewd','');			/* フリーワード */
$FILTER		= getCgiParameter('filter','');			/* 絞り込み条件 */
$POS		= getCgiParameter('pos','1');			/* 取得位置 */
$CNT		= getCgiParameter('cnt','100');			/* 取得件数 */
$SORT		= getCgiParameter('sort','');			/* ソート順 */
$PFLG		= '1';									/* ポイントフラグ */
$DATUM		= DATUM_WGS84;							/* 測地系 */
$OUTF		= getCgiParameter('outf','JSON');		/* 出力形式 */
$ENC		= getCgiParameter('enc','UTF8');		/* 文字コード */

$OPTION_CD = $CID;

require_once('lw_enc.inc');			// 文字コード変換

$SORT = mb_ereg_replace("'", "", $SORT);

if ($FREWD != '') {
if($D_DEBUG) error_log("FREWD($ENC)=[".$FREWD."]\n", 3, "/var/tmp/lwcgi.".date('Ymd').".debug.log");
	$FREWD = f_enc_to_EUC($FREWD);
if($D_DEBUG) error_log("FREWD=[".$FREWD."]\n", 3, "/var/tmp/lwcgi.".date('Ymd').".debug.log");
	$FREWD = trim($FREWD);
	$FREWD = mb_ereg_replace("　", " ", $FREWD);		// 全角スペース→半角スペース
}

/*==============================================*/
// 絞り込み条件
/*==============================================*/
$FILTER_sql = '';
edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
$log_jkn = implode(' ', $arr_log_jkn);

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// 初期化
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
//if (!isset($swlat)) $swlat = "";
//if (!isset($swlon)) $swlon = "";
//if (!isset($nelat)) $nelat = "";
//if (!isset($nelon)) $nelon = "";
// add 2011/09/29 Y.Nakajima ]


/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$parms = $lat;
$parms .= ' '.$lon;
$parms .= ' ';
$parms .= ' ';
$parms .= ' ';
$parms .= ' ';
$parms .= ' '.$log_jkn;

/*==============================================*/
// 出力クラス
/*==============================================*/
require_once('lw_outf_json.inc');		// 出力クラス定義（ローソン）
require_once('lw_outf_xml.inc');		// 出力クラス定義（ローソン）
switch ($OUTF) {
	case 'XML':
		$CgiOut = new KyotenCgiOutputXML($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG);
		break;
	default:
		$CgiOut = new KyotenCgiOutputJSON($CGICD, $CGINM, $ENC, $RETCD, $RETCD_ESC, $PFLG);
}

/*==============================================*/
// 簡易認証（IPチェック／リファラチェック）
/*==============================================*/
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	if (!referer_check(&$D_REFERER_LIST, $_SERVER['HTTP_REFERER'])) {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status, 0, 0); $CgiOut->output();
		put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
		exit;
	}
}

/*==============================================*/
// パラメータチェック
/*==============================================*/
/* e-map企業ID */
if ($CID == '') {
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
if ($ENC != 'SJIS' && $ENC != 'EUC' && $ENC != 'UTF8') {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 取得位置 */
if (NumChk($POS) != 'OK') {
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
if (NumChk($CNT) != 'OK') {
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
/* ポイントフラグ */
if ($PFLG != '1' && $PFLG != '2' && $PFLG != '3') {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 出力形式 */
if ($OUTF != 'JSON' && $OUTF != 'XML') {
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
$arr_item = array();
$sql = "select COL_NAME,ITEM_NAME,VAL_KBN from KYOTEN_ITEM_TBL";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " order by DISP_NUM";
$stmt = null;
if (!$dba->sqlExecute($sql, $stmt)) {
	$dba->free($stmt);
	$dba->close();
	$status = DEF_RETCD_DERR3;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
$arr_item = array();
while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
	$arr_item[] = $data;
}
$dba->free($stmt);

/*==============================================*/
// 区分項目の名称取得
/*==============================================*/
$arr_kbn = array();
if (count($arr_item) > 0) {
	foreach ($arr_item as $item) {
		if ($item['VAL_KBN'] == 'L') {
			$sql_kbn = "select ITEM_VAL, ITEM_VAL_NAME from KYOTEN_ITEM_VAL_TBL";
			$sql_kbn .= " where CORP_ID = '".escapeOra($CID)."'";
			$sql_kbn .= " and COL_NAME = '".$item['COL_NAME']."'";
			$sql_kbn .= " order by ITEM_VAL";
			if (!$dba->sqlExecute($sql_kbn, $stmt)) {
				$dba->free($stmt);
				$dba->close();
				$status = DEF_RETCD_DERR3;
				$CgiOut->set_status($status, 0, 0); $CgiOut->output();
				put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
				exit;
			}
			$arr_kbn[$item['COL_NAME']] = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
			}
			$dba->free($stmt);
		}
	}
}

/*==============================================*/
// 拠点条件検索
/*==============================================*/
$sql = "";
$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON";
if (count($arr_item) > 0) {
	foreach ($arr_item as $item) {
		$sql .= ", ".$item['COL_NAME'];
	}
}
$sql .= " , TO_CHAR(DISP_NEW_S_DATE,'yyyymmddhh24') as DISP_NEW_S_DATE, TO_CHAR(DISP_NEW_E_DATE,'yyyymmddhh24') as DISP_NEW_E_DATE ";	// add 2012/01/26 K.Masuda
$sql .= " from KYOTEN_TBL K";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " and nvl(PUB_E_DATE, sysdate+1) >= sysdate";
if ($FREWD != '') {
	$frewd_sql = array();
	$words = explode(' ', $FREWD);
	foreach ($words as $w) {
		if ($w != '') {
			$frewd_sql[] = "INSTR(FREE_SRCH, '" . fw_normalize($w) . "') <> 0";
		}
	}
	if (count($frewd_sql)) {
		$sql .= " and (".implode(' and ', $frewd_sql).")";
	}
}
if ($FILTER_sql != '') {
	$sql .= " and ".$FILTER_sql;
}
$sql_order = '';
if ($SORT != '') $sql_order .= $SORT;
if ($SORT != '') $sql_order .= ',';
$sql_order .= 'KYOTEN_ID,CORP_ID';
$sql .= " order by ".$sql_order;
$sql = "select s.*, rownum rn from (".$sql.") s";
// ヒット件数取得
$hit_num = 0;
$stmt = null;
$sql_count = "select count(*) HITCNT from (".$sql.")";
if($D_DEBUG) error_log("$sql_count\n", 3, "/var/tmp/lwcgi.".date('Ymd').".debug.log");
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
if($D_DEBUG) error_log("$sql_data\n", 3, "/var/tmp/lwcgi.".date('Ymd').".debug.log");
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
		
		// 区分項目の名称をセット
		if (count($arr_item) > 0) {
			foreach ($arr_item as $item) {
				if ($item['VAL_KBN'] == 'L') {
					$colnm = $item['COL_NAME'];
					// mod 2011/09/29 Y.Nakajima [
					if (isset($data[$colnm])) {
						$val = $data[$colnm];
						if ($val != '') {
							if ($arr_kbn[$colnm][$val] != '') {
								$data[$colnm.'_name'] = $arr_kbn[$colnm][$val];
							}
						}
					}
					// mod 2011/09/29 Y.Nakajima ]
				}
			}
		}
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
