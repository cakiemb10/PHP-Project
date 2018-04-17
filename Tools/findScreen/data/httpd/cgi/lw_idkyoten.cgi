<?php
/*========================================================*/
// ファイル名：lw_idkyoten.cgi
// 処理名：【ローソン向けカスタマイズ】拠点ID検索
//
// 更新履歴
// 2011/09/09 K.Masuda		新規作成
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
$CGICD = 'w03';

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
// add 2011/07/05 Y.Nakajima 
require_once('cgi_key.inc');			// emapCGIキー他($D_CGI_KEY)


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

// add 2011/09/29 Y.Nakajima [
/*==============================================*/
// 初期化
/*==============================================*/
if (!isset($lat)) $lat = "";
if (!isset($lon)) $lon = "";
if (!isset($status)) $status = 00000;
if (!isset($params)) $params = "";
if (!isset($PFLG)) $PFLG = "";
$emap_cid = $D_CID;    //企業コード固定　lw_def.incで定義
// add 2011/09/29 Y.Nakajima ]


/*==============================================*/
//ログ出力開始
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// パラメータ取得
/*==============================================*/
$CID		= $D_CID;								/* e-map企業ID */
$KEY		= $D_CGI_KEY;
$ID			= getCgiParameter('id','');				/* 拠点ID */
$OUTF		= getCgiParameter('outf','JSON');		/* 出力形式 */
$ENC		= getCgiParameter('enc','UTF8');		/* 文字コード */

$OPTION_CD = $CID;

require_once('lw_enc.inc');			// 文字コード変換

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$parms = $ID;

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
/* 文字コード */
if ($ENC != 'SJIS' && $ENC != 'EUC' && $ENC != 'UTF8') {
	$status = DEF_RETCD_PERR2;
	$CgiOut->set_status($status, 0, 0); $CgiOut->output();
	put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
	exit;
}
/* 拠点ID */
if ($ID == '') {
	$status = DEF_RETCD_PERR1;
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
// 拠点ID検索
/*==============================================*/
$sql = "";
$sql .= "select CORP_ID, KYOTEN_ID, LAT, LON from KYOTEN_TBL";
$sql .= " where CORP_ID = '".escapeOra($CID)."'";
$sql .= " and KYOTEN_ID = '".escapeOra($ID)."'";
$sql .= " and NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE";  // add 2013/07/25 F.Yokoi
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
	// mod 2012/01/26 K.Masuda [
	//$sql_data = "select * from KYOTEN_TBL";
	$sql_data = "select CORP_ID, KYOTEN_ID, LAT, LON";
	if (count($arr_item) > 0) {
		foreach ($arr_item as $item) {
			$sql_data .= ", ".$item['COL_NAME'];
		}
	}
	$sql_data .= " , TO_CHAR(DISP_NEW_S_DATE,'yyyymmddhh24') as DISP_NEW_S_DATE, TO_CHAR(DISP_NEW_E_DATE,'yyyymmddhh24') as DISP_NEW_E_DATE ";
	$sql_data .= " from KYOTEN_TBL";
	// mod 2012/01/26 K.Masuda ]
	$sql_data .= " where CORP_ID = '".escapeOra($CID)."'";
	$sql_data .= " and KYOTEN_ID = '".escapeOra($ID)."'";
	$sql_data .= " and NVL( PUB_E_DATE, SYSDATE ) >= SYSDATE"; // add 2013/07/25 F.Yokoi
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

// 後続データ無し
$status = DEF_RETCD_DE;

// データ出力
$CgiOut->set_status($status, $rec_num, $hit_num);
$CgiOut->set_data_arr(&$arr_kyoten);
$CgiOut->output();

// ログ出力
put_log($CGICD.$status, $KEY, $OPTION_CD, $parms);
?>
