<?php
/**********************************************************************
// Aplia API 呼び出し用定義ファイル
//
// 更新履歴：
// 2012/12/10 H.Iijima	新規作成
/*********************************************************************/
$hostname = trim(`hostname`);

switch( $hostname ){
//----- 開発機 -----
//case "devemapweb": mod 2011/09/29 K.Masuda
case "dev-storenaviweb01":
	$D_DEBUG = true;
	break;
//----- 検証機 -----
//case "emapweb00":	mod 2011/09/29 K.Masuda
case "storenaviweb-v01":
	$D_DEBUG = false;
	break;
//----- 本番機 -----
default:
	$D_DEBUG = false;
}

// ---------------------------------------------------------
// 定義ファイル APIキー
// ---------------------------------------------------------
switch( $hostname ){//----- 開発機 -----
     case "dev-storenaviweb01":
     case "emapweb00":   //----- 検証機 -----
          $API_APLIA_SRV  = "10.47.30.41";
          break;
     case "storenaviweb-v01": //----- VM検証機 -----
          $API_APLIA_SRV  = "172.24.6.223";
          break;
//----- 本番機 -----
     default:
          $API_APLIA_SRV  = "172.24.6.222";
}

$API_APLIA_PATH = '/v1_0/checkin/';


?>
