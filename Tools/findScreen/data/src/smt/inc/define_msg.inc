<?php
// ------------------------------------------------------------
// 定義ファイル 各種メッセージ
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/07/13 Y.Matsukawa	機能追加（ルート探索、最寄駅）
// 2011/08/08 Y.Matsukawa	機能追加（絞り込み拡張、拠点エリア検索、駅リスト検索）
// 2011/08/15 K.Masuda 		拠点FW検索カラム指定のメッセージ追加
// 2012/02/23 Y.Matsukawa	店舗全件リスト画面
// 2012/07/18 Y.Matsukawa	最寄施設
// 2012/07/20 Y.Matsukawa	GPSエラーメッセージをカスタマイズ可能に
// 2017/04/21 N.Wada		路線フリーワードのメッセージ追加
// ------------------------------------------------------------
//サイト接続 -----------------------------------------------
if(!isset($D_MSG_EMAPVIEW_NOKID)) $D_MSG_EMAPVIEW_NOKID = "指定された".$D_SHOP_NAME."は存在しません";
if(!isset($D_MSG_EMAPVIEW_NOSERVICE)) $D_MSG_EMAPVIEW_NOSERVICE = "指定されたページの表示ができませんでした。<br>（サービス利用期間が過ぎています）";
if(!isset($D_MSG_EMAPVIEW_NOCID)) $D_MSG_EMAPVIEW_NOCID = "指定されたページの表示ができませんでした。<br>（cidが登録されていません）";
if(!isset($D_MSG_EMAPVIEW_NOREFERER)) $D_MSG_EMAPVIEW_NOREFERER  = "アクセスが許可されていません";
if(!isset($D_MSG_EMAPVIEW_NOPRM)) $D_MSG_EMAPVIEW_NOPRM      = "パラメータが不正です";
if(!isset($D_MSG_EMAPVIEW_ERRPRM)) $D_MSG_EMAPVIEW_ERRPRM     = "パラメータが不正です";
if(!isset($D_MSG_EMAPVIEW_NGBROWSER)) $D_MSG_EMAPVIEW_NGBROWSER = "申し訳ありませんが、お使いのブラウザでは、ページを表示することができません。";
if(!isset($D_MSG_EMAPVIEW_INVALIDIP)) $D_MSG_EMAPVIEW_INVALIDIP  = "アクセスが許可されていません";
if(!isset($D_MSG_EMAPVIEW_HTTPS)) $D_MSG_EMAPVIEW_HTTPS = "アクセスが許可されていません";
if(!isset($D_MSG_EMAPVIEW_HTTP)) $D_MSG_EMAPVIEW_HTTP = "アクセスが許可されていません";	


//位置検索 -------------------------------------------------
if(!isset($D_MSG_SEARCH_NULL["FW"])) $D_MSG_SEARCH_NULL["FW"] = "駅名・住所・施設名を入力して再度検索してください。";
//住所フリーワード
if(!isset($D_MSG_SEARCH_NODATA["AddrW"])) $D_MSG_SEARCH_NODATA["AddrW"] = "該当する住所がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["AddrW"])) $D_MSG_SEARCH_NULL["AddrW"] = "住所を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["AddrW"])) $D_MSG_SEARCH_MAXPAGE["AddrW"] = "該当する住所が多いため<br>入力内容を変えて再度検索してください。<br>";
//駅フリーワード
if(!isset($D_MSG_SEARCH_NODATA["StW"])) $D_MSG_SEARCH_NODATA["StW"] = "該当する駅名がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["StW"])) $D_MSG_SEARCH_NULL["StW"] = "駅名を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["StW"])) $D_MSG_SEARCH_MAXPAGE["StW"] = "該当する駅名が多いため<br>入力内容を変えて再度検索してください。<br>";
//施設フリーワード
if(!isset($D_MSG_SEARCH_NODATA["PoiW"])) $D_MSG_SEARCH_NODATA["PoiW"] = "該当する施設名がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["PoiW"])) $D_MSG_SEARCH_NULL["PoiW"] = "施設名を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["PoiW"])) $D_MSG_SEARCH_MAXPAGE["PoiW"] = "該当する施設名が多いため<br>入力内容を変えて再度検索してください。<br>";
//拠点フリーワード
if(!isset($D_MSG_SEARCH_NODATA["ShopW"])) $D_MSG_SEARCH_NODATA["ShopW"] = "該当する".$D_SHOP_NAME."名がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopW"])) $D_MSG_SEARCH_NULL["ShopW"] = $D_SHOP_NAME."名を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopW"])) $D_MSG_SEARCH_MAXPAGE["ShopW"] = "該当する".$D_SHOP_NAME."名が多いため<br>入力内容を変えて再度検索してください。<br>";
// add 2011/08/15 K.Masuda [
if(!isset($D_MSG_SEARCH_NODATA["ShopW_col"])) $D_MSG_SEARCH_NODATA["ShopW_col"] = "該当する".$D_SHOP_NAME_COL."がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopW_col"])) $D_MSG_SEARCH_NULL["ShopW_col"] = $D_SHOP_NAME_COL."を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopW_col"])) $D_MSG_SEARCH_MAXPAGE["ShopW_col"] = "該当する".$D_SHOP_NAME_COL."が多いため<br>入力内容を変えて再度検索してください。<br>";
// add 2011/08/15 K.Masuda ]
//路線フリーワード	add 2017/04/21 N.Wada
if(!isset($D_MSG_SEARCH_NODATA["RoW"])) $D_MSG_SEARCH_NODATA["RoW"] = "該当する路線名がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["RoW"])) $D_MSG_SEARCH_NULL["RoW"] = "路線名を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["RoW"])) $D_MSG_SEARCH_MAXPAGE["RoW"] = "該当する路線名が多いため<br>入力内容を変えて再度検索してください。<br>";
//拠点リスト		add 2011/08/08 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["ShopA"])) $D_MSG_SEARCH_NODATA["ShopA"] = "該当する".$D_SHOP_NAME."がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//拠点全件リスト		add 2012/02/23 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["KL"])) $D_MSG_SEARCH_NODATA["KL"] = "該当する".$D_SHOP_NAME."がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//住所リスト
if(!isset($D_MSG_SEARCH_NODATA["AddrL"])) $D_MSG_SEARCH_NODATA["AddrL"] = "該当する情報がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//駅リスト		add 2011/08/08 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["StL"])) $D_MSG_SEARCH_NODATA["StL"] = "該当する情報がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//その他
if(!isset($D_MSG_SEARCH_ERRPRM)) $D_MSG_SEARCH_ERRPRM    = "パラメータが不正です";
//GPS検索		add 2012/07/20 Y.Matsukawa
if(!isset($D_MSG_GPS_ERRPRM)) $D_MSG_GPS_ERRPRM = "現在地の取得に失敗しました";

//最寄駅		add 2011/07/13 Y.Matsukawa
if(!isset($D_MSG_NEKI_NOLIST)) $D_MSG_NEKI_NOLIST = "最寄り駅がありませんでした";
if(!isset($D_MSG_NEKI_MSG)) $D_MSG_NEKI_MSG = $D_SHOP_NAME."の最寄り駅を近い順に表示しています。";
if(!isset($D_MSG_NEKI_COUNT)) $D_MSG_NEKI_COUNT = "件ヒット";

//最寄施設		add 2012/07/18 Y.Matsukawa
if(!isset($D_MSG_NPOI_NOLIST)) $D_MSG_NPOI_NOLIST = "最寄り施設がありませんでした";
if(!isset($D_MSG_NPOI_MSG)) $D_MSG_NPOI_MSG = $D_SHOP_NAME."の最寄り施設を近い順に表示しています。";
if(!isset($D_MSG_NPOI_COUNT)) $D_MSG_NPOI_COUNT = "件ヒット";

//地図画面 -------------------------------------------------
//最寄拠点
if(!isset($D_MSG_NKYOTEN_NOLIST)) $D_MSG_NKYOTEN_NOLIST = "最寄り".$D_SHOP_NAME."がありませんでした";
if(!isset($D_MSG_NKYOTEN_MSG)) $D_MSG_NKYOTEN_MSG = "の最寄り".$D_SHOP_NAME."を近い順に表示しています。";
if(!isset($D_MSG_NKYOTEN_COUNT)) $D_MSG_NKYOTEN_COUNT = "件ヒット";

// add 2011/07/13 Y.Matsukawa
//ルート -------------------------------------------------
if(!isset($D_MSG_ERR_JS_ROUTE)) $D_MSG_ERR_JS_ROUTE   = "ルート探索に失敗しました。";

//その他 ---------------------------------------------------
if(!isset($D_MSG_ERR)) $D_MSG_ERR            = "予期しないエラーが発生しました";
if(!isset($D_MSG_ERR_JS_REQUEST)) $D_MSG_ERR_JS_REQUEST = "申し訳ありませんが只今大変混み合っております。TOPページに戻りしばらく時間を置いてからご利用ください";
if(!isset($D_MSG_ERR_JS_RESULT)) $D_MSG_ERR_JS_RESULT  = "検索に失敗しました";

?>
