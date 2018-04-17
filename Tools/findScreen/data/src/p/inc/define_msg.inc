<?php
// ------------------------------------------------------------
// 定義ファイル 各種メッセージ
// 
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2012/02/27 Y.Matsukawa	店舗全件リスト画面
// 2013/09/24 Y.Matsukawa	拠点フリーワード（完全一致）検索
// 2014/12/11 Y.Matsukawa	閲覧履歴（拠点）一覧画面
// 2015/04/09 F.Yokoi		ルート検索 歩行者→自動車への切替をアラート表示する際の文言用変数の追加
// 2016/02/03 N.Wada		GPSエラーメッセージをカスタマイズ可能に
// ------------------------------------------------------------
//サイト接続 -----------------------------------------------
if(!isset($D_MSG_EMAPVIEW_NOKID)) $D_MSG_EMAPVIEW_NOKID = "指定された".$D_USER_DEFNAME."は存在しません";
if(!isset($D_MSG_EMAPVIEW_NOSERVICE)) $D_MSG_EMAPVIEW_NOSERVICE = "指定されたページの表示ができませんでした。<br>（サービス利用期間が過ぎています）";
if(!isset($D_MSG_EMAPVIEW_NOCID)) $D_MSG_EMAPVIEW_NOCID = "指定されたページの表示ができませんでした。<br>（cidが登録されていません）";
if(!isset($D_MSG_EMAPVIEW_NOREFERER)) $D_MSG_EMAPVIEW_NOREFERER  = "アクセスが許可されていません";
if(!isset($D_MSG_EMAPVIEW_NOPRM)) $D_MSG_EMAPVIEW_NOPRM      = "パラメータが不正です";
if(!isset($D_MSG_EMAPVIEW_ERRPRM)) $D_MSG_EMAPVIEW_ERRPRM     = "パラメータが不正です";
if(!isset($D_MSG_EMAPVIEW_NGBROWSER)) $D_MSG_EMAPVIEW_NGBROWSER = "申し訳ありませんが、お使いのブラウザでは、ページを表示することができません。";
if(!isset($D_MSG_EMAPVIEW_INVALIDIP)) $D_MSG_EMAPVIEW_INVALIDIP  = "アクセスが許可されていません";		// add 2009/08/24 Y.Matsukawa
if(!isset($D_MSG_EMAPVIEW_HTTPS)) $D_MSG_EMAPVIEW_HTTPS = "アクセスが許可されていません";		// add 2010/07/20 Y.Matsukawa
if(!isset($D_MSG_EMAPVIEW_HTTP)) $D_MSG_EMAPVIEW_HTTP = "アクセスが許可されていません";			// add 2010/07/20 Y.Matsukawa


//位置検索 -------------------------------------------------
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
//郵便番号フリーワード
if(!isset($D_MSG_SEARCH_NODATA["ZipW"])) $D_MSG_SEARCH_NODATA["ZipW"] = "該当する郵便番号がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["ZipW"])) $D_MSG_SEARCH_NULL["ZipW"] = "郵便番号を入力してください。";
if(!isset($D_MSG_SEARCH_LENGTH["ZipW"])) $D_MSG_SEARCH_LENGTH["ZipW"] = "郵便番号を７桁で入力して下さい。";
//拠点フリーワード
if(!isset($D_MSG_SEARCH_NODATA["ShopW"])) $D_MSG_SEARCH_NODATA["ShopW"] = "該当する".$D_USER_DEFNAME."名がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopW"])) $D_MSG_SEARCH_NULL["ShopW"] = $D_USER_DEFNAME."名を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopW"])) $D_MSG_SEARCH_MAXPAGE["ShopW"] = "該当する".$D_USER_DEFNAME."名が多いため<br>入力内容を変えて再度検索してください。<br>";
//拠点フリーワード（完全一致）		add 2013/09/24 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["ShopM"])) $D_MSG_SEARCH_NODATA["ShopM"] = "該当する".$D_USER_DEFNAME."がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopM"])) $D_MSG_SEARCH_NULL["ShopM"] = "検索条件を入力してください。";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopM"])) $D_MSG_SEARCH_MAXPAGE["ShopM"] = "該当する".$D_USER_DEFNAME."が多いため<br>入力内容を変えて再度検索してください。<br>";
// add 2011/06/16 H.osamoto [
//フリーワード複合検索
if(!isset($D_MSG_SEARCH_NULL["Comb"])) $D_MSG_SEARCH_NULL["Comb"] = "フリーワードを入力してください。";
// add 2011/06/16 H.osamoto ]
//住所リスト
if(!isset($D_MSG_SEARCH_NODATA["AddrL"])) $D_MSG_SEARCH_NODATA["AddrL"] = "該当する情報がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//駅リスト
if(!isset($D_MSG_SEARCH_NODATA["StL"])) $D_MSG_SEARCH_NODATA["StL"] = "該当する情報がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//施設リスト
if(!isset($D_MSG_SEARCH_NODATA["PoiL"])) $D_MSG_SEARCH_NODATA["PoiL"] = "該当する情報がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//拠点リスト
if(!isset($D_MSG_SEARCH_NODATA["ShopA"])) $D_MSG_SEARCH_NODATA["ShopA"] = "該当する情報がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//拠点全件リスト		add 2012/02/27 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["KL"])) $D_MSG_SEARCH_NODATA["KL"] = "該当する".$D_SHOP_NAME."がありませんでした。<br>入力内容を変えて再度検索してください。<br>";
//閲覧履歴リスト		add 2014/12/11 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["KLCK"])) $D_MSG_SEARCH_NODATA["KLCK"] = "保存されている閲覧履歴はありません。";
//その他
if(!isset($D_MSG_SEARCH_ERRPRM)) $D_MSG_SEARCH_ERRPRM    = "パラメータが不正です";
//GPS検索		add 2016/02/03 N.Wada
if(!isset($D_MSG_GPS_ERRPRM)) $D_MSG_GPS_ERRPRM = "現在地の取得に失敗しました";


//地図画面 -------------------------------------------------
//最寄拠点
if(!isset($D_MSG_NKYOTEN_NOLIST)) $D_MSG_NKYOTEN_NOLIST = "最寄".$D_USER_DEFNAME."がありませんでした";
if(!isset($D_MSG_NPOI_NOLIST)) $D_MSG_NPOI_NOLIST = "地図内に該当施設がありませんでした";
if(!isset($D_MSG_NEKI_NOLIST)) $D_MSG_NEKI_NOLIST = "最寄駅がありませんでした";



//その他 ---------------------------------------------------
if(!isset($D_MSG_ERR)) $D_MSG_ERR            = "予期しないエラーが発生しました";
if(!isset($D_MSG_ERR_JS_REQUEST)) $D_MSG_ERR_JS_REQUEST = "申し訳ありませんが只今大変混み合っております。TOPページに戻りしばらく時間を置いてからご利用ください";
if(!isset($D_MSG_ERR_JS_RESULT)) $D_MSG_ERR_JS_RESULT  = "検索に失敗しました";
if(!isset($D_MSG_ERR_JS_ROUTE)) $D_MSG_ERR_JS_ROUTE   = "距離が長すぎるか探索に失敗しました。";
if(!isset($D_MSG_ERR_SEARCH_WALK_ALERT)) $D_MSG_ERR_SEARCH_WALK_ALERT = ""; // add 2015/04/09 F.Yokoi
?>
