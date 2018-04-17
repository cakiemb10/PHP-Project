<?php
// ---------------------------------------------------------
// 日本設備工業 社員名取得CGIラッパー
// 
// ファイル名：nsnet01_syainnm.cgi
// 処理名：社員名取得
//
// 作成日：2015/05/08
// 作成者：N.Wada
//
// 解説：日本設備工業公開WEB APIを経由して社員番号から社員名を取得
//
// 入力パラメータ：
// empno	GET		社員番号（カンマ区切りで複数可）
// 例）
// empno=100001,100010,100015
//
// 出力フォーマット：
// 1行目は件数、2行目以降は社員番号\t社員名
// 例）
// 2
// 000001	社員名000001
// 000002	社員名000002
//
// 更新履歴
// 2015/05/08 N.Wada		新規作成
// 2015/05/15 N.Wada		はしご高か文字化けしていたため文字コードを'CP51932'に変更
// ---------------------------------------------------------
header("Content-Type: text/html; charset=EUC-JP");

require_once('/home/emap/src/Jsphon/Decoder.php');
require_once('d_serv_cgi.inc');
require_once('d_serv_emap.inc');
require_once('auth.inc');				// 簡易認証
include("ZdcCommonFunc.inc");

// 日本設備工業公開WEB API
$url = 'http://www.nihonsetsubi.co.jp/webapi/karte/json.php';

// 許可IP
$D_IP_LIST = array();
$D_IP_LIST[] = '127.0.0.1';
$D_IP_LIST[] = '10.47.50.*';
$D_IP_LIST[] = '172.16.162.*';
$D_IP_LIST[] = '153.122.23.244';
$D_IP_LIST = implode(':', $D_IP_LIST);

// 簡易認証（IPチェック）
if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
	header('HTTP/1.1 403 Forbidden');
	exit;
}

// 社員番号をGETから取得
$empnos = explode(",", htmlspecialchars($_GET['empno']));

// CGIに渡すパラメータを設定
$cnt = 0;
foreach ( $empnos as $empno ) {
	if ( ! ctype_digit($empno) ) continue;
	$url .= ($cnt ? '&' : '?') . 'id[]=' . $empno;
	$cnt++;
}
// プロキシを必ず通す
$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];

$buf = "";
if ($cnt) {
	$dat = ZdcHttpSimpleRead($url, $host);
	if ($dat != '') {
		// JSONデコード
		$json = new Jsphon_Decoder();
		$arr_data = $json->decode($dat[0]);
		if ($arr_data && is_array($arr_data)) {
			// EUCに変換
			//mb_convert_variables('EUC-JP', 'UTF-8', $arr_data);	mod 2015/05/15 N.Wada
			// CP51932に変換
			mb_convert_variables('CP51932', 'UTF-8', $arr_data);
			$buf = count($arr_data) . "\n";
			foreach ( $arr_data as $work ) {
				$buf .= $work['id'] . "\t" . $work['name'] . "\n";
			}
		}
	}
}
if ($buf == "") {
	$buf = "0\n";
}

print($buf);
?>
