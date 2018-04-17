<?php
// ------------------------------------------------------------
// 定義ファイル デザインに関する項目
// 
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2012/02/27 Y.Matsukawa	店舗全件リスト画面
// 2012/03/19 Y.Matsukawa	地図コントローラのタイプを変更可能に
// 2012/10/01 Y.Matsukawa	Maplink対応
// 2013/08/01 Y.Matsukawa	機能追加：路線検索
// 2013/09/18 Y.Matsukawa	拠点フリーワード（完全一致）検索
// 2014/10/06 Y.Matsukawa	連番アイコン
// 2014/11/28 Y.Matsukawa	店舗アイコンクリックで一覧の該当店舗を頭出し
// 2015/01/28 Y.Matsukawa	最寄駅、最寄施設などをパンくずに追加
// 2015/03/18 N.Wada		拠点アイコンに重ねる連番アイコン
// 2015/10/20 N.Wada		Google Maps版吹き出しカスタマイズ
//							Google Maps版MarkerClustererアイコンのスタイル設定
//							Google Maps版コントローラの非表示
// 2015/11/19 Y.Matsukawa	検索ウィンドウに「検索中」表示
// 2016/02/24 Y.Matsukawa	同一地点の場合に連番アイコンをまとめる
// 2016/03/22 N.Wada		拠点アイコンの中央下が拠点位置を指すパターン追加
// 2016/03/23 N.Wada		Google Maps版拠点案内用の独自UI追加
// 2016/03/25 N.Wada		スタート地点、ゴール地点アイコンの幅・高さ追加
// 2016/08/15 H.Yasunaga	日本郵便対応 p_f99(閲覧専用フラグ)をPC側でも実装するため
//							引継ぎパラメータ(p_fとp_s)の最大数をsmt側と合わせる
// 2017/02/23 N.Wada		ルート描画時の電車用の線の設定追加
// ------------------------------------------------------------
//「店舗」の標準の呼び方
if(!isset($D_USER_DEFNAME)) $D_USER_DEFNAME = "店舗";
//「サービス」の標準の呼び方
if(!isset($D_USER_SERVICENAME)) $D_USER_SERVICENAME = "サービス";

// 地図 ----------------------------------------------------
//通常モード or 印刷モード
if(!isset($D_MAP_PRINT_MODE)) $D_MAP_PRINT_MODE = 0;//0：通常モード、1：印刷モード
//ズームコントロール ユーザーコントロールが無い場合-1だと出さない
//if(!isset($D_MAP_CONTROL)) $D_MAP_CONTROL = 3;		mod 2012/03/19 Y.Matsukawa
if(!isset($D_MAP_CONTROL)) $D_MAP_CONTROL = 1;	// 1：通常、2：縮尺バーなし、3：+-ボタンのみ
//中心アイコン種別 -1だと出さない
if(!isset($D_MAP_CENTER)) $D_MAP_CENTER = -1;
//スケールバー種別 0だと出さない
if(!isset($D_MAP_SCALEBAR)) $D_MAP_SCALEBAR = 1;
//情報ボックス種別 -1だと出さない
if(!isset($D_MAP_INFO)) $D_MAP_INFO = -1;
//地図のレイヤー
if(!isset($D_MAP_LAYER_KBN)) $D_MAP_LAYER_KBN = 1;
//読み込み中の表示
if(!isset($D_MAP_WAIT_OFFSETX)) $D_MAP_WAIT_OFFSETX = -60;
if(!isset($D_MAP_WAIT_OFFSETY)) $D_MAP_WAIT_OFFSETY = -12;
if(!isset($D_MAP_WAIT_MSG)) $D_MAP_WAIT_MSG  = "読み込み中です";
//Google Maps版拠点案内用の独自UI	add 2016/03/23 N.Wada
if(!isset($D_GOOGLEMAPS_EMAP_ORIGINAL_UI)) $D_GOOGLEMAPS_EMAP_ORIGINAL_UI = 0;	//0:使わない、1:使う
//Google Maps版コントローラの非表示	add 2015/10/20
if(!isset($D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE = 0;	//マップタイプ切り替えコントローラ
if(!isset($D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE = 0;	//ナビゲーションコントローラ
if(!isset($D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE = 0;	//スケールコントローラ
if(!isset($D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE = 0;	//ズームコントローラ
if(!isset($D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE = 0;	//パンコントローラ
//Google Maps版吹き出しカスタマイズ（要infobox.js）	add 2015/10/20
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM)) $D_GOOGLEMAPS_MSG_CUSTOM = 0;
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM_OPTION)) $D_GOOGLEMAPS_MSG_CUSTOM_OPTION  = "";


// 位置検索系 ----------------------------------------------
//１ページの量
if(!isset($D_SEARCH_LIST_PAGE))         $D_SEARCH_LIST_PAGE         = 10;//リスト形式
if(!isset($D_SEARCH_TABLE_PAGE))        $D_SEARCH_TABLE_PAGE        = 16;//テーブル形式
if(!isset($D_SEARCH_SHOPLIST_PAGE))     $D_SEARCH_SHOPLIST_PAGE     = 5;//拠点リスト
if(!isset($D_SEARCH_FROUTE_LIST_PAGE))  $D_SEARCH_FROUTE_LIST_PAGE  = 10;//出発地指定ルートの検索リスト
//テーブル形式の１行の列数
if(!isset($D_SEARCH_TABLE_COLS))        $D_SEARCH_TABLE_COLS        = 4;
//検索名
if(!isset($D_HISTORY_NAME["AddrW"]))    $D_HISTORY_NAME["AddrW"]    = "住所フリーワード";
if(!isset($D_HISTORY_NAME["StW"]))      $D_HISTORY_NAME["StW"]      = "駅フリーワード";
if(!isset($D_HISTORY_NAME["PoiW"]))     $D_HISTORY_NAME["PoiW"]     = "施設フリーワード";
if(!isset($D_HISTORY_NAME["ZipW"]))     $D_HISTORY_NAME["ZipW"]     = "郵便番号フリーワード";
if(!isset($D_HISTORY_NAME["ShopW"]))    $D_HISTORY_NAME["ShopW"]    = $D_USER_DEFNAME."フリーワード";
if(!isset($D_HISTORY_NAME["ShopM"]))    $D_HISTORY_NAME["ShopM"]    = $D_USER_DEFNAME."フリーワード";		// add 2013/09/18 Y.Matsukawa
if(!isset($D_HISTORY_NAME["AddrL"]))    $D_HISTORY_NAME["AddrL"]    = "住所リスト";
if(!isset($D_HISTORY_NAME["StL"]))      $D_HISTORY_NAME["StL"]      = "駅リスト";
if(!isset($D_HISTORY_NAME["LineL"]))    $D_HISTORY_NAME["LineL"]    = "路線リスト";		// add 2013/08/01 Y.Matsukawa
if(!isset($D_HISTORY_NAME["LineStL"]))  $D_HISTORY_NAME["LineStL"]  = "駅リスト";		// add 2013/08/01 Y.Matsukawa
if(!isset($D_HISTORY_NAME["PoiL"]))     $D_HISTORY_NAME["PoiL"]     = "施設リスト";
if(!isset($D_HISTORY_NAME["ShopA"]))    $D_HISTORY_NAME["ShopA"]    = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_2"]))  $D_HISTORY_NAME["ShopA_2"]  = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_3"]))  $D_HISTORY_NAME["ShopA_3"]  = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_4"]))  $D_HISTORY_NAME["ShopA_4"]  = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_5"]))  $D_HISTORY_NAME["ShopA_5"]  = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["Rail"]))     $D_HISTORY_NAME["Rail"]     = "路線図検索";
if(!isset($D_HISTORY_NAME["Area"]))     $D_HISTORY_NAME["Area"]     = "地域図検索";
if(!isset($D_HISTORY_NAME["List"]))     $D_HISTORY_NAME["List"]     = "検索結果";
if(!isset($D_HISTORY_NAME["Detail"]))   $D_HISTORY_NAME["Detail"]   = "詳細表示";
//if(!isset($D_HISTORY_NAME["Npoi"]))     $D_HISTORY_NAME["Npoi"]     = "最寄施設検索";		mod 2015/01/28 Y.Matsukawa
if(!isset($D_HISTORY_NAME["Npoi"]))     $D_HISTORY_NAME["Npoi"]     = "周辺施設";
//if(!isset($D_HISTORY_NAME["Neki"]))     $D_HISTORY_NAME["Neki"]     = "最寄駅検索";		mod 2015/01/28 Y.Matsukawa
if(!isset($D_HISTORY_NAME["Neki"]))     $D_HISTORY_NAME["Neki"]     = "最寄り駅";
if(!isset($D_HISTORY_NAME["Nshop"]))    $D_HISTORY_NAME["Nshop"]    = $D_USER_DEFNAME."リスト";
if(!isset($D_HISTORY_NAME["FRoute"]))   $D_HISTORY_NAME["FRoute"]   = "出発地指定ルート";
if(!isset($D_HISTORY_NAME["SPRoute"]))  $D_HISTORY_NAME["SPRoute"]  = "検索位置からルート";		// add 2015/01/28 Y.Matsukawa
if(!isset($D_HISTORY_NAME["Comb"]))     $D_HISTORY_NAME["Comb"]     = "フリーワード検索";
if(!isset($D_HISTORY_NAME["KList"]))    $D_HISTORY_NAME["KList"]    = "全店舗一覧";		// add 2012/02/27 Y.Matsukawa
//項目名
if(!isset($D_SEL_NAME["AddrW"]))    $D_SEL_NAME["AddrW"]    = "住所";
if(!isset($D_SEL_NAME["StW"]))      $D_SEL_NAME["StW"]      = "駅";
if(!isset($D_SEL_NAME["PoiW"]))     $D_SEL_NAME["PoiW"]     = "施設";
if(!isset($D_SEL_NAME["ZipW"]))     $D_SEL_NAME["ZipW"]     = "住所";
if(!isset($D_SEL_NAME["ShopW"]))    $D_SEL_NAME["ShopW"]    = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["ShopM"]))    $D_SEL_NAME["ShopM"]    = $D_USER_DEFNAME;		// add 2013/09/18 Y.Matsukawa
if(!isset($D_SEL_NAME["AddrL"]))    $D_SEL_NAME["AddrL"]    = "住所";
if(!isset($D_SEL_NAME["StL"]))      $D_SEL_NAME["StL"]      = "駅";
if(!isset($D_SEL_NAME["LineL"]))    $D_SEL_NAME["LineL"]    = "路線";		// add 2013/08/01 Y.Matsukawa
if(!isset($D_SEL_NAME["LineStL"]))  $D_SEL_NAME["LineStL"]  = "駅";			// add 2013/08/01 Y.Matsukawa
if(!isset($D_SEL_NAME["PoiL"]))     $D_SEL_NAME["PoiL"]     = "施設";
if(!isset($D_SEL_NAME["ShopA"]))    $D_SEL_NAME["ShopA"]    = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["PoiJnr"]))   $D_SEL_NAME["PoiJnr"]   = "ジャンル";
if(!isset($D_SEL_NAME["Nshop"]))    $D_SEL_NAME["Nshop"]    = $D_USER_DEFNAME;
//拠点エリア検索表示名称
if(!$D_SEARCH_SHOPA_DISPNM[1]) $D_SEARCH_SHOPA_DISPNM[1]    = $D_SEL_NAME["AddrL"];//第1階層
if(!$D_SEARCH_SHOPA_DISPNM[2]) $D_SEARCH_SHOPA_DISPNM[2]    = $D_SEL_NAME["AddrL"];//第2階層
if(!$D_SEARCH_SHOPA_DISPNM[3]) $D_SEARCH_SHOPA_DISPNM[3]    = $D_SEL_NAME["AddrL"];//第1階層    エリア検索２
if(!$D_SEARCH_SHOPA_DISPNM[4]) $D_SEARCH_SHOPA_DISPNM[4]    = $D_SEL_NAME["AddrL"];//第2階層
if(!$D_SEARCH_SHOPA_DISPNM[5]) $D_SEARCH_SHOPA_DISPNM[5]    = $D_SEL_NAME["AddrL"];//第1階層    エリア検索３
if(!$D_SEARCH_SHOPA_DISPNM[6]) $D_SEARCH_SHOPA_DISPNM[6]    = $D_SEL_NAME["AddrL"];//第2階層
if(!$D_SEARCH_SHOPA_DISPNM[7]) $D_SEARCH_SHOPA_DISPNM[7]    = $D_SEL_NAME["AddrL"];//第1階層    エリア検索４
if(!$D_SEARCH_SHOPA_DISPNM[8]) $D_SEARCH_SHOPA_DISPNM[8]    = $D_SEL_NAME["AddrL"];//第2階層
if(!$D_SEARCH_SHOPA_DISPNM[9]) $D_SEARCH_SHOPA_DISPNM[9]    = $D_SEL_NAME["AddrL"];//第1階層    エリア検索５
if(!$D_SEARCH_SHOPA_DISPNM[10]) $D_SEARCH_SHOPA_DISPNM[10]  = $D_SEL_NAME["AddrL"];//第2階層
//言語
if(!isset($D_EKI_LANG)) $D_EKI_LANG = '';//駅
if(!isset($D_POI_LANG)) $D_POI_LANG = '';//施設
//検索ウィンドウ
if(!isset($D_SEARCHWIN_WAIT_HTML)) $D_SEARCHWIN_WAIT_HTML = '';//「検索中」表示HTML	※シングルクォーテーションは含めないで下さい		add 2015/11/19 Y.Matsukawa


// 拠点系 --------------------------------------------------
//拠点アイコン情報
if(!isset($D_ICON_MSGOFFSETX)) $D_ICON_MSGOFFSETX = 0;
if(!isset($D_ICON_MSGOFFSETY)) $D_ICON_MSGOFFSETY = -8;
//拠点アイコンと拠点位置の関係	add 2016/03/22 N.Wada
if(!isset($D_ICON_ANCHOR_CENTER_BOTTOM)) $D_ICON_ANCHOR_CENTER_BOTTOM = 0;	// アイコンの中央下が拠点の位置を指す
//デフォルト拠点アイコン情報
if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_SHOP_W)) $D_ICON_SHOP_W = 11;
if(!isset($D_ICON_SHOP_H)) $D_ICON_SHOP_H = 11;
//拠点アイコン情報-NEW
if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE_G."img/new.gif";
if(!isset($D_ICON_NEW_W)) $D_ICON_NEW_W = 23;
if(!isset($D_ICON_NEW_H)) $D_ICON_NEW_H = 10;
//カーソルアイコン情報
if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE_G."img/icon_cursor/0000.gif";
if(!isset($D_ICON_CURSOR_W)) $D_ICON_CURSOR_W = 51;
if(!isset($D_ICON_CURSOR_H)) $D_ICON_CURSOR_H = 50;
//フォーカスアイコン情報
if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE_G."img/icon_cursor/0003.gif";
if(!isset($D_ICON_FOCUS_W)) $D_ICON_FOCUS_W = 51;
if(!isset($D_ICON_FOCUS_H)) $D_ICON_FOCUS_H = 50;
//透明アイコン情報		add 2012/10/01 Y.Matsukawa
if(!isset($D_ICON_TP_IMG)) $D_ICON_TP_IMG = $D_DIR_BASE_G."img/tp11.gif";
if(!isset($D_ICON_TP_W)) $D_ICON_TP_W = 11;
if(!isset($D_ICON_TP_H)) $D_ICON_TP_H = 11;
//最寄駅検索
if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE_G."img/icon_eki/0000.gif";
if(!isset($D_ICON_EKI_W)) $D_ICON_EKI_W = 19;
if(!isset($D_ICON_EKI_H)) $D_ICON_EKI_H = 24;
if(!isset($D_ICON_EKI_OFFSET_X)) $D_ICON_EKI_OFFSET_X = -10;
if(!isset($D_ICON_EKI_OFFSET_Y)) $D_ICON_EKI_OFFSET_Y = -12;
//最寄施設検索
if(!isset($D_ICON_POI_IMAGE_DIR)) $D_ICON_POI_IMAGE_DIR = $D_DIR_BASE_G."img/icon_poi/";
if(!isset($D_ICON_POI_W)) $D_ICON_POI_W = 16;
if(!isset($D_ICON_POI_H)) $D_ICON_POI_H = 16;
if(!isset($D_ICON_POI_OFFSET_X)) $D_ICON_POI_OFFSET_X = -8;
if(!isset($D_ICON_POI_OFFSET_Y)) $D_ICON_POI_OFFSET_Y = -8;
//数字アイコン（クリック地図版用）
if(!isset($D_ICON_NUM_POINT_IMAGE)) $D_ICON_NUM_POINT_IMAGE = $D_DIR_BASE."img/icon_num/mi%02d.gif";	//ポイント
if(!isset($D_ICON_NUM_CUBE_IMAGE)) $D_ICON_NUM_CUBE_IMAGE = $D_DIR_BASE."img/icon_num/li%02d.gif";	//四角
if(!isset($D_ICON_NUM_POINT_OFFSET_X)) $D_ICON_NUM_POINT_OFFSET_X = 0;
if(!isset($D_ICON_NUM_POINT_OFFSET_Y)) $D_ICON_NUM_POINT_OFFSET_Y = -14;
// icn省略時のデフォルトアイコン（☆）0：表示しない、1：表示する
if(!isset($D_DEFAULT_ICN)) $D_DEFAULT_ICN = 0;
// 連番アイコン定義		add 2014/10/06 Y.Matsukawa
if(!isset($D_SEQ_ICON_INFO)) $D_SEQ_ICON_INFO = null;
if(!isset($D_SEQ_ICON_COL)) $D_SEQ_ICON_COL = null;
// 一覧頭出し背景色		add 2014/11/28 Y.Matsukawa
if(!isset($D_NLIST_POP_COLOR)) $D_NLIST_POP_COLOR = '';
// 拠点アイコンに重ねる連番アイコン		add 2015/03/18 N.Wada
if(!isset($D_LAYER_SEQ_ICON)) $D_LAYER_SEQ_ICON = 0;	// 0：表示しない、1：表示する
if(!isset($D_LAYER_SEQ_ICON_NAME)) $D_LAYER_SEQ_ICON_NAME = "";
if(!isset($D_LAYER_SEQ_ICON_EXT)) $D_LAYER_SEQ_ICON_EXT = "";
if(!isset($D_LAYER_SEQ_ICON_W)) $D_LAYER_SEQ_ICON_W = 0;
if(!isset($D_LAYER_SEQ_ICON_H)) $D_LAYER_SEQ_ICON_H = 0;
if(!isset($D_LAYER_SEQ_ICON_OX)) $D_LAYER_SEQ_ICON_OX = 0;
if(!isset($D_LAYER_SEQ_ICON_OY)) $D_LAYER_SEQ_ICON_OY = 0;
if(!isset($D_LAYER_SEQ_SAMEPOINT_CLUSTER)) $D_LAYER_SEQ_SAMEPOINT_CLUSTER = 0;	// 同一地点店舗の連番をまとめる		add 2016/02/24 Y.Matsukawa
// Google Maps版MarkerClustererアイコンのスタイル設定（要markerclustere.js）	add 2015/10/20 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES)) $D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES  = "";


//TIPS表示 -------------------------------------------------
if(!isset($D_TIPS_OFFSET_X)) $D_TIPS_OFFSET_X    = 15;
if(!isset($D_TIPS_OFFSET_Y)) $D_TIPS_OFFSET_Y    = 15;
if(!isset($D_TIPS_FONT)) $D_TIPS_FONT        = "10pt serif";
if(!isset($D_TIPS_BGCOLOR)) $D_TIPS_BGCOLOR     = "white";
if(!isset($D_TIPS_BORDERWIDTH)) $D_TIPS_BORDERWIDTH = 1;
if(!isset($D_TIPS_SHADOWFLG)) $D_TIPS_SHADOWFLG = "true";
if(!isset($D_TIPS_SHADOWX)) $D_TIPS_SHADOWX = 3;
if(!isset($D_TIPS_SHADOWY)) $D_TIPS_SHADOWY = 3;
if(!isset($D_TIPS_OPACITY)) $D_TIPS_OPACITY = 30;


// ルート探索系 --------------------------------------------
if(!isset($D_ROUTE_CAR_WIDTH)) $D_ROUTE_CAR_WIDTH   = "5";// 幅
if(!isset($D_ROUTE_CAR_OPACITY)) $D_ROUTE_CAR_OPACITY = "0.5";// 透明度
if(!isset($D_ROUTE_CAR_COLOR)) $D_ROUTE_CAR_COLOR   = "#0000ff";//色
if(!isset($D_ROUTE_WALK_WIDTH)) $D_ROUTE_WALK_WIDTH   = "5";// 幅
if(!isset($D_ROUTE_WALK_OPACITY)) $D_ROUTE_WALK_OPACITY = "0.5";// 透明度
if(!isset($D_ROUTE_WALK_COLOR)) $D_ROUTE_WALK_COLOR   = "#0000ff";//色
if(!isset($D_ROUTE_TRAIN_WIDTH)) $D_ROUTE_TRAIN_WIDTH   = "5";// 幅（電車用）	add 2017/02/23 N.Wada
if(!isset($D_ROUTE_TRAIN_OPACITY)) $D_ROUTE_TRAIN_OPACITY = "0.5";// 透明度（電車用）	add 2017/02/23 N.Wada
if(!isset($D_ROUTE_TRAIN_COLOR)) $D_ROUTE_TRAIN_COLOR   = "#0000ff";//色（電車用）	add 2017/02/23 N.Wada
//スタート地点アイコン
if(!isset($D_ROUTE_START_IMAGE)) $D_ROUTE_START_IMAGE = $D_DIR_BASE_G."img/route/RouteStart.png";
if(!isset($D_ROUTE_START_GIF)) $D_ROUTE_START_GIF = $D_DIR_BASE_G."img/route/RouteStart.gif";
if(!isset($D_ROUTE_START_WIDTH)) $D_ROUTE_START_WIDTH = 54;		// 幅	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_START_HEIGHT)) $D_ROUTE_START_HEIGHT = 36;	// 高さ	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_START_OFFSET_X)) $D_ROUTE_START_OFFSET_X = -4;
if(!isset($D_ROUTE_START_OFFSET_Y)) $D_ROUTE_START_OFFSET_Y = -36;
//ゴール地点アイコン
if(!isset($D_ROUTE_GOAL_IMAGE)) $D_ROUTE_GOAL_IMAGE = $D_DIR_BASE_G."img/route/RouteEnd.png";
if(!isset($D_ROUTE_GOAL_GIF)) $D_ROUTE_GOAL_GIF = $D_DIR_BASE_G."img/route/RouteEnd.gif";
if(!isset($D_ROUTE_GOAL_WIDTH)) $D_ROUTE_GOAL_WIDTH = 54;		// 幅	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_GOAL_HEIGHT)) $D_ROUTE_GOAL_HEIGHT = 36;		// 高さ	add 2016/03/25 N.Wada
if(!isset($D_ROUTE_GOAL_OFFSET_X)) $D_ROUTE_GOAL_OFFSET_X = -4;
if(!isset($D_ROUTE_GOAL_OFFSET_Y)) $D_ROUTE_GOAL_OFFSET_Y = -36;


// 画面履歴 ------------------------------------------------
//区切り文字
if(!isset($D_HISTORY_SEP)) $D_HISTORY_SEP = "&nbsp;&gt;&nbsp;";
//TOP画面
if(!isset($D_HISTORY_TOP_NAME)) $D_HISTORY_TOP_NAME = $D_USER_DEFNAME."案内TOP";


// Maplink ------------------------------------------------
//住所文字列接続のマッチング住所を表示する
if(!isset($D_ADDR_MATCH_DISP)) $D_ADDR_MATCH_DISP = 0;
//住所文字列接続のマッチング住所 前方文章
if(!isset($D_ADDR_MATCH_HEAD)) $D_ADDR_MATCH_HEAD = '';
//住所文字列接続のマッチング住所 後方文章
if(!isset($D_ADDR_MATCH_TAIL)) $D_ADDR_MATCH_TAIL = '';
//住所文字列接続のマッチング住所 注意文言
if(!isset($D_ADDR_MATCH_EXP)) $D_ADDR_MATCH_EXP = '';

// add start 2016/08/15 H.Yasunaga	p_sとp_fの最大数をsmt側に合わせる [
//									smt側はp_sとp_fの最大数が別定義だがpcは１つのループで両方取得するため
//									最大数の定義は1つのみ
if (!isset($D_P_MAX)) $D_P_MAX = 100;
// add end ]
?>
