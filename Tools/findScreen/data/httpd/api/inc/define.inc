<?php
// ------------------------------------------------------------
// API・管理ツール定義
// 
// 2016/06/14 H.Yasunaga	新規作成
// 2016/08/24 H.Yasunaga	座標種別[coord]パラメータ追加
// 2016/12/16 H.Yasunaga	座標種別[coord]パラメータの値に"W"を追加、レスポンスの緯度経度を世界測地系にする
// ------------------------------------------------------------
	// 日本郵政APIのログ用テーブル名
	define("API_LOG_TABLE",			"JPOST_API_LOG_TBL");
	// 日本郵政APIのAPIアクセスキー用のテーブル名
	define("API_KEY_TABLE",			"JPOST_API_KEY_TBL");
	// 日本郵政API管理画面操作ログテーブル名
	define("API_MANAGE_LOG_TABLE",	"JPOST_API_MANAGE_LOG_TBL");
	
	// APIエラー リクエスト項目が空か不正
	define("API_ERROR_INVALID_PARAMETER", 1);
	// APIエラー アクセスキーの値が入っていないか不正
	define("API_ERROR_INVALID_KEY", 2);
	// APIエラー IPアドレスがアクセスキーに紐づいた値でないか、不正
	define("API_ERROR_INVALID_IPADDRESS", 3);
	// APIエラー 該当するデータが1件もない
	define("API_ERROR_ITEM_NOT_FOUND", 4);
	// APIエラー その他のエラー(処理が完了できない)
	define("API_ERROR_INTERNAL_SERVER", 5);
	
	
	/* リターンコード */
	define( 'DEF_RETCD_DE',   '00000' );       // 条件に見合うデータあり（後続データなし）
	define( 'DEF_RETCD_DEND', '00001' );       // 条件に見合うデータあり（後続データあり）
	define( 'DEF_RETCD_DNE',  '11009' );       // 条件に見合うデータなし
	define( 'DEF_RETCD_DERR1','17900' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR2','17002' );       // データベースアクセスエラー
	define( 'DEF_RETCD_DERR3','17999' );       // データベースアクセスエラー
	define( 'DEF_RETCD_PERR1','19100' );       // 入力パラメータエラー(必須項目NULL)
	define( 'DEF_RETCD_PERR2','19200' );       // 入力パラメータエラー(構文エラー)
	define( 'DEF_RETCD_PERR3','19200' );       // 入力パラメータエラー(組み合わせエラー)
	
	// 測地系
	define("DATUM_WGS84", "WGS84");
	define("DATUM_TOKYO", "TOKYO");
	define( 'DEF_PRM_DATUM_TOKYO', 	'TOKYO');       // 測地系（日本測地系）
	define( 'DEF_PRM_DATUM_WGS84', 	'WGS84');       // 測地系（世界測地系）
	
	// add start 2016/08/24 H.Yasunaga 座標種別[coord]追加 [
	define("DEF_COORD_ZENRIN", "Z");	// ゼンリン座標
	define("DEF_COORD_MAPION", "M");	// Mapion座標
	// add end 2016/08/24 ]
	// add start 2016/12/16 H.Yasunaga 座標種別[coord]の"W"世界測地系
	define("DEF_COORD_WORLD", "W");
	// add end 2016/12/16 ]
?>