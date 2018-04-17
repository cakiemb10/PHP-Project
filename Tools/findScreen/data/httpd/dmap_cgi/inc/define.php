<?php
//------------------------------------------
// 環境別設定
//
// 2016/08/05 H.Osamoto		iDC移行対応
//------------------------------------------
$hostname = trim(`hostname`);
switch( $hostname ){

//--------
// avant-code開発機
//--------
case "sub0000526554.hmk-temp.com":
	// === いつもNAVICGI定義 ===
	// プロトコル
	define("ITUMO_CGI_PROTOCOL","http");
	// ドメイン
	define("ITUMO_CGI_DOMAIN","test.cgi.e-map.ne.jp");
	// サブディレクトリ
	define("ITUMO_CGI_API_DIR","dmap_cgi/");
	// 認証キー
	define("ITUMO_CGI_KEY", "44nQTzBUnwJvBwnADvBMnAkf9EmgaPByitMe6Xidq5S2XukmAOfhezTJrxxzTIngmfA3oQ7vBRnRu8BznBj8BNmwojT1");
	// エラー表示
	ini_set( 'display_errors', 1 );
	error_reporting(E_ALL^E_NOTICE);

	break;

//--------
// 開発機
//--------
case 'dev-storenaviweb01':
	// === いつもNAVICGI定義 ===
	// プロトコル
	define("ITUMO_CGI_PROTOCOL","http");
	// ドメイン
	//	define("ITUMO_CGI_DOMAIN","172.16.204.200");	mod 2016/08/05 H.Osamoto
	define("ITUMO_CGI_DOMAIN","172.28.0.156");
	// サブディレクトリ
	define("ITUMO_CGI_API_DIR","dmap_cgi/");
	// 認証キー
	define("ITUMO_CGI_KEY", "41nQYzCtmglz4LnwDrBTnAyf9smgRPBejgqzDIngRj4JnQ2yjIngOP5dmgsf8Lng2zFjmwdXFVmgOzFMmAUPT5");
	// エラー表示
	ini_set( 'display_errors', 1 );
	error_reporting(E_ALL^E_NOTICE);

	break;

//--------
// 検証機
//--------
case 'storenaviweb-v01':
case "storenaviweb-v02":
	// === いつもNAVICGI定義 ===
	// プロトコル
	define("ITUMO_CGI_PROTOCOL","http");
	// ドメイン
	//	define("ITUMO_CGI_DOMAIN","172.16.204.200");	mod 2016/08/05 H.Osamoto
	define("ITUMO_CGI_DOMAIN","172.28.0.156");
	// 認証キー
	//	define("ITUMO_CGI_KEY","42nQLzCJmgnz4unwnrBBnAUf91mgpPBrjgYzDXng6j4wnQvyjEngCP5Vmgdf8cngNXBOoQMv6xoQnv6OnR28Jy");	mod 2016/08/05 H.Osamoto
	define("ITUMO_CGI_KEY","40nQOP9llgevBQnA8vBPnARf9SmguPBpjgmzDeng3j4inQ5yj9ng2P5Jmgmf8kngSXBdoQvr9OoQHzFDpRXzT9");

	break;

//--------
// 本番機
//--------
default:
	// === いつもNAVICGI定義 ===
	// プロトコル
	define("ITUMO_CGI_PROTOCOL","http");
	// ドメイン
	//	define("ITUMO_CGI_DOMAIN","172.16.204.201");	mod 2016/08/05 H.Osamoto
	define("ITUMO_CGI_DOMAIN","172.28.0.56");
	// 認証キー
	//	define("ITUMO_CGI_KEY","42nQLzCJmgnz4unwnrBBnAUf91mgpPBrjgYzDXng6j4wnQvyjEngCP5Vmgdf8cngNXBOoQMv6xoQnv6OnR28Jy");	mod 2016/08/05 H.Osamoto
	define("ITUMO_CGI_KEY","40nQLP9HlgcvBFnA8vBXnAsf9FmgMPB4jgOzDingVj4YnQvyjungsP5SmgBf8inglXBDoQZr8DoQxzFkpRmzTP");

}

// === いつもNAVICGI定義 ===
define("ITUMO_CGI_API_SEARCH_NEAR_STATION",	ITUMO_CGI_PROTOCOL."://".ITUMO_CGI_DOMAIN."/cgi/nekitan.cgi");
define("ITUMO_CGI_API_SEARCH_TRAIN_ROUTE",	ITUMO_CGI_PROTOCOL."://".ITUMO_CGI_DOMAIN."/cgi/search_ekitan_route.cgi");
define("ITUMO_CGI_API_SEARCH_WALK_ROUTE",	ITUMO_CGI_PROTOCOL."://".ITUMO_CGI_DOMAIN."/cgi/route/search_proute.cgi");


define("ITUMO_CGI_ENC", "UTF8");			// 文字コード（UTF8）
define("ITUMO_CGI_DATUM", "TOKYO");			// 測地系（日本測地系）
define("ITUMO_CGI_OUTF", "XML");			// 出力形式（XML）
define("ITUMO_CGI_NEAR_STATION_KNSU", 1);	// 最寄駅検索：取得件数
define("ITUMO_CGI_NEAR_STATION_RAD", 3000);	// 最寄駅検索：半径(m)
define("ITUMO_CGI_NEAR_STATION_PFLAG", 1);	// 最寄駅検索：ポイントフラグ（十進緯度経度表記）
define("ITUMO_CGI_TRAIN_ROUTE_KNSU", 3);	// 乗換ルート探索：取得件数
define("ITUMO_CGI_TRAIN_ROUTE_PATHF", 1);	// 乗換ルート探索：経路座標出力フラグ（経路座標情報を出力する）
//define("ITUMO_CGI_WALK_ROUTE_TYPE", "0000");// 歩行者ルート探索：始点、終点タイプ（駅出入口を経由しない）
define("ITUMO_CGI_WALK_ROUTE_TYPE", "2000");// 歩行者ルート探索：始点、終点タイプ（駅出入口を経由する）
//define("ITUMO_CGI_WALK_ROUTE_PSC", 1);		// 歩行者ルート探索：探索条件（時間優先）
define("ITUMO_CGI_WALK_ROUTE_PSC", 0);		// 歩行者ルート探索：探索条件（距離優先）
define("ITUMO_CGI_WALK_ROUTE_LINK", 1);		// 歩行者ルート探索：リンク情報フラグ（取得する）

define("RETURN_CODE_SUCCESS",		"000");	// 成功
define("RETURN_CODE_ERROR_PARAMS",	"100");	// パラメータエラー
define("RETURN_CODE_ERROR_INTERNAL","101");	// 内部エラー
define("RETURN_CODE_ERROR_OTHER",	"102");	// その他のエラー

define("WALK_SPEED_METER_PER_MIN", (4.8 * 1000 / 60));	// 歩行者分速(m)
?>
