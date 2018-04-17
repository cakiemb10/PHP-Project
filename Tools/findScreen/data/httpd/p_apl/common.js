<?PHP
// ------------------------------------------------------------
// 汎用共通javascriptモジュール
// 
// 開発履歴
// 2015/10/20 N.Wada	新規作成
// 2016/02/03 N.Wada	現在地取得エラーメッセージ
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
?>

var ZdcEmapGPSErrMsg="<?php echo $D_MSG_GPS_ERRPRM; ?>";		<?php // add 2016/02/03 N.Wada ?>

//HTML読み込み用ajax通信関数
function ZdcEmapCmnHttpRequestHtmlAjax(url, func, nowaitmsg, typ) {
	if(typ == undefined) typ = 1;
	//通信処理
	var ZdcEmapHttpRequestObj = new ZdcEmapHttpRequest('EUC', 'EUC');
	ZdcEmapHttpRequestObj.request(url, function(html,status) {
		if(status == 3) status = 0;//タイムアウトは無視 連続呼び出し時の動作が安定しないので
		if(status == 9) status = 0;//テンプレートが無い場合に対応
		if(html == null) html = "";//nullは出さない
		if(status == 0) {
			func(html,status);
		} else {
			//エラー処理
			func(html,status);
		}
	},<?PHP echo $D_AJAX_TIMEOUT; ?>,typ);
}

