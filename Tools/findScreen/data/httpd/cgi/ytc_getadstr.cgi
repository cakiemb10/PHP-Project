<?php
/*========================================================*/
// ファイル名：ytc_getadstr.cgi
// 処理名：【ヤマト運輸様向けカスタマイズ】住所逆引き検索
//
// 更新履歴
// 2013/07/16 Y.Arai		新規作成
// 2013/08/06 Y.Matsukawa	ログ出力内容を調整
/*========================================================*/
extract($_GET);

/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = 'y01';

/*==============================================*/
// CGI名
/*==============================================*/
$APICGINM = "getadstr_gik.cgi";

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE',   '00000' );       //条件に見合うデータあり
define( 'DEF_RETCD_DNE',  '11009' );       //条件に見合うデータなし
define( 'DEF_RETCD_AERR', '12009' );       //認証エラー
define( 'DEF_RETCD_PERR1','19100' );       //入力パラメータエラー（必須パラメータの未指定）
define( 'DEF_RETCD_PERR2','19200' );       //入力パラメータエラー（パラメータ指定値の不正）

/*==============================================*/
// 定義ファイル
/*==============================================*/
require_once('ytc_def.inc');			// ヤマト運輸用定義
require_once('ytc_cgi_key.inc');		// ヤマト運輸用emapCGIキー他
require_once('function.inc');			// 共通関数
require_once('log.inc');				// ログ出力
require_once('auth.inc');				// 簡易認証

/*==============================================*/
//ログ出力開始
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// 初期化
/*==============================================*/
$status 	= DEF_RETCD_DE;		// ログ用ステータスコード（成功）
$emap_cid	= $D_CID;			// 企業コード固定　ytc_def.incで定義
$rescode	= "-1";				// レスポンスコード初期値（エラー）
$errcode	= "";				// エラーコード初期値
$outdata	= "";				// 出力結果初期値
//$log_parms	= $dms." ".$sid;	// ログ出力用文字列（パラメータ）	mod 2013/08/06 Y.Matsukawa
$log_parms	= mb_ereg_replace(' ', '_', $dms);
$log_parms	.= ' ';
$log_parms	.= mb_ereg_replace(' ', '_', $sid);
$KEY		= $D_CGI_KEY;		// CGI用キー

/*==============================================*/
// 簡易認証（IPチェック／HTTPS通信チェック）
/*==============================================*/
// IPチェック
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	put_log($CGICD.DEF_RETCD_AERR, $KEY, $emap_cid, $log_parms);
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=Shift_JIS");
	echo mb_convert_encoding("アクセスは許可されていません:IPアドレスが拒否されました。", "SJIS", "EUC-JP");
	exit;
}

// HTTPS通信チェック
if($_SERVER['HTTPS'] != 'on') {
	put_log($CGICD.DEF_RETCD_AERR, $KEY, $emap_cid, $log_parms);
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=Shift_JIS");
	echo mb_convert_encoding("アクセスは許可されていません:SSLが必要です。", "SJIS", "EUC-JP");
	exit;
}

/*==============================================*/
// パラメータチェック
/*==============================================*/
// リクエスト
if ($_SERVER['REQUEST_METHOD'] != "GET") {
	outputErrStatus( $rescode, "ERR0003", "リクエスト方法が不正です。" );
	put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
	exit;
}

// 緯度経度[dms]
if ($dms == "") {
	outputErrStatus( $rescode, "ERR0001", "必須パラメタが指定されていません。[dms]" );
	put_log($CGICD.DEF_RETCD_PERR1, $KEY, $emap_cid, $log_parms);
	exit;
} else {
	// フォーマットチェック（Eddd.mm.ss.sNdd.mm.ss.s）
	if (preg_match("/^E([0-9]{3})\.([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{1})N([0-9]{2})\.([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{1})$/s",$dms) !== 1) {
		outputErrStatus( $rescode, "ERR0002", "必須パラメタが不正です。[dms]");
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}
	$dms_arr = explode("N", $dms);
	$lon = str_replace("E", "", $dms_arr[0]);
	$lat = $dms_arr[1];
	
	// 範囲チェック（東経120度〜160度、北緯20度〜60度の範囲）
	$lon_arr = explode(".", $lon);
	$lat_arr = explode(".", $lat);
	if ($lon_arr[0] < 120 || $lon_arr[0] > 160 || $lat_arr[0] < 20 || $lat_arr[0] > 60) {
		outputErrStatus( $rescode, "ERR0002", "必須パラメタが不正です。[dms]");
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}
}

// サービスID[sid]
if ($sid == "") {
	outputErrStatus( $rescode, "ERR0001", "必須パラメタが指定されていません。[sid]" );
	put_log($CGICD.DEF_RETCD_PERR1, $KEY, $emap_cid, $log_parms);
	exit;
} else {
	if ($sid != "ytc" && $sid != "ysd") {
		outputErrStatus( $rescode, "ERR0002", "必須パラメタが不正です。[sid]" );
		put_log($CGICD.DEF_RETCD_PERR2, $KEY, $emap_cid, $log_parms);
		exit;
	}
}

/*==============================================*/
// パラメータ取得
/*==============================================*/
$LAT		= getCgiParameter('lat', $lat);			/* 緯度 */
$LON		= getCgiParameter('lon', $lon);			/* 経度 */
$MCLV		= getCgiParameter('mclv','3');			/* マッチングレベル（字丁目まで） */
$ENC		= getCgiParameter('enc','SJIS');		/* 文字コード (OUT) */
$SEP		= getCgiParameter('sep','1');			/* 住所区切り（あり） */
$PFLG		= getCgiParameter('pflg','3');			/* ポイントフラグ（度分秒） */
$DATUM		= getCgiParameter('datum','WGS84');		/* 測地系（世界測地系） */
$OUTF		= getCgiParameter('outf','TSV');		/* 出力形式 */

/*==============================================*/
// 実行用にパラメータ値を結合
/*==============================================*/
$parms =  '?key='.	$KEY;
$parms .= '&lat='.	$LAT;
$parms .= '&lon='.	$LON;
$parms .= '&mclv='.	$MCLV;
//$parms .= '&enc='.	$ENC;		mod 2013/08/21 Y.Matsukawa
$parms .= '&enc=EUC';
$parms .= '&sep='.	$SEP;
$parms .= '&pflg='.	$PFLG;
$parms .= '&datum='.$DATUM;
$parms .= '&outf='.	$OUTF;

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
// del 2013/08/06 Y.Matsukawa [
//$log_parms = 'KEY:'.	$KEY;
//$log_parms .= ' LAT:'.	$LAT;
//$log_parms .= ' LON:'.	$LON;
//$log_parms .= ' MCLV:'.	$MCLV;
//$log_parms .= ' ENC:'.	$ENC;
//$log_parms .= ' SEP:'.	$SEP;
//$log_parms .= ' PFLG:'.	$PFLG;
//$log_parms .= ' DATUM:'.$DATUM;
//$log_parms .= ' OUTF:'.	$OUTF;
// del 2013/08/06 Y.Matsukawa ]
// add 2013/08/06 Y.Matsukawa [
$log_parms .= ' ';
$log_parms .= $LAT;
$log_parms .= ' ';
$log_parms .= $LON;
// add 2013/08/06 Y.Matsukawa ]

/*==============================================*/
// 住所逆引き検索CGIコール
/*==============================================*/
unset($result);
$CGI = 'http://'.$API_SSAPI_SRV.'/ssapi/'.$APICGINM.$parms;
$result = file_get_contents($CGI);

if (!$result) {
	outputErrStatus( $rescode, "ERR1002", "通信エラーのため、住所文字列の取得に失敗しました。" );
	put_log($CGICD.DEF_RETCD_DNE, $KEY, $emap_cid, $log_parms);
	exit;
}

// 整形
$res_arr = explode("\n", $result);
$statcd = explode("\t", $res_arr[0]);

if ($statcd[0] == "21600000" || $statcd[0] == "21600001") {
// 正常時
	$rescode = "0";
	$add_arr = explode("\t", $res_arr[1]);
	// 住所区切りの|を全角スペースに変換
	//$outdata = str_replace("|", mb_convert_encoding("　", "SJIS", "EUC-JP"), $add_arr[1]);		del 2013/08/21 Y.Matsukawa
	// add 2013/08/21 Y.Matsukawa [
	$add = explode('|', $add_arr[1]);
	//$add[count($add)-1] = mb_ereg_replace('丁目', '', $add[count($add)-1]);		del 2013/08/22 Y.Matsukawa
	//$outdata = mb_convert_encoding(implode('　', $add), 'SJIS', 'EUC-JP');		del 2013/08/22 Y.Matsukawa
	// add 2013/08/22 Y.Matsukawa [
	$add_last = '';
	if (strpos($add[count($add)-1], '丁目')) {
		$add_last = array_pop(&$add);
		$add_last = mb_ereg_replace('丁目', '', $add_last);
	}
	$outdata = implode('　', $add).$add_last;
	$outdata = mb_convert_encoding($outdata, 'SJIS', 'EUC-JP');
	// add 2013/08/22 Y.Matsukawa ]
	// add 2013/08/21 Y.Matsukawa ]

} else {
// エラー返却時時
	if ($statcd[0] == "21611009") {		// 条件に見合うデータなし
		outputErrStatus( $rescode, "ERR1001", "住所文字列が取得できない海域です。" );
	} else {		// その他のエラー
		outputErrStatus( $rescode, "ERR1003", "その他のエラーのため、住所文字列の取得に失敗しました。");
	}
	put_log($CGICD.DEF_RETCD_DNE, $KEY, $emap_cid, $log_parms);
	exit;
}

// ログ出力
put_log($CGICD.$status, $KEY,$emap_cid, $log_parms);

// 結果出力
header ("Content-Type: text/plain; charset=Shift_JIS");
echo $rescode.",".$outdata;
exit;

/*==============================================*/
// エラー時の出力
/*==============================================*/
function outputErrStatus( $rescode, $errcode, $outdata ) {
	header("Content-Type: text/plain; charset=Shift_JIS");
	print $rescode.",".$errcode.":".mb_convert_encoding($outdata, "SJIS", "EUC-JP");
	return true;
}

?>
