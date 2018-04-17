<?php
// ---------------------------------------------------------
// 【ヤマト運輸向けカスタマイズ】APIキー定義
//
// 2013/07/12 Y.Matsukawa	新規作成
// ---------------------------------------------------------
$hostname = trim(`hostname`);
switch( $hostname ){
//----- 開発機 -----
case "dev-storenaviweb01":

	$API_SSAPI_SRV  = "172.28.0.156";
	$D_CGI_KEY = '41nQOzCDmwvz7sng9fBFnAkf97mgXPBJjg4zDGngUme4nQryn0nger5NlgIfCLngozF7mw4XFmmggzFSmAiPTj';
    break;

//----- 検証機 -----
case "storenaviweb-v01":

	$API_SSAPI_SRV  = "172.28.0.156";
	$D_CGI_KEY = "40nQdP9vlg3vBQnASvB7nAhf96mg3PBWidP5SgXuMmAdfxNzT9rxvzT5rxIzTOngsXBnoQZr9coQVzFupRszTy";
	break;

//----- 本番機 -----
default:

	$API_SSAPI_SRV  = "172.28.0.56";
	$D_CGI_KEY = '40nQsP9LlgyvBnnADvBYnAkf9Umg7PBCjgqzDgngIme7nQuynTngZr5IlgtfCingoXBXoQFr8MoQPzFppRAzTb';
}
?>
