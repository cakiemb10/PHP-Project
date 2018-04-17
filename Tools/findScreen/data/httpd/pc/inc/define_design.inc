<?php
// ------------------------------------------------------------
// 定義ファイル デザインに関する項目
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2008/09/02 Y.Matsukawa	Maplink住所文字列接続時に、ヒットした住所文字列を画面に表示
// 2008/12/18 Y.Matsukawa	Maplinkのデフォルトアイコン（☆）を追加
// 2010/03/09 Y.Matsukawa	住所FW検索から拠点リスト（地図なし）へ遷移
// 2010/06/16 Y.Matsukawa	出発地を指定してルート探索
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/11/03 K.Masuda		エリア検索複数対応
// 2011/04/14 H.Osamoto		Myエリア対応
// 2011/06/02 H.Osamoto		フリーワード複合検索対応
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/06/12 Y.Matsukawa	IE7互換モードを無効にできるようにする
// ------------------------------------------------------------

// IE7互換モード		add 2012/06/12 Y.Matsukawa
if(!isset($D_EMULATE_IE7_VIEW)) $D_EMULATE_IE7_VIEW = 1;
if(!isset($D_EMULATE_IE7_PRINT)) $D_EMULATE_IE7_PRINT = 1;

//「拠点」の標準の呼び方
if(!isset($D_USER_DEFNAME)) $D_USER_DEFNAME = "拠点";
//「サービス」の標準の呼び方
if(!isset($D_USER_SERVICENAME)) $D_USER_SERVICENAME = "サービス";


// 地図 ----------------------------------------------------
//通常モード or 印刷モード
if(!isset($D_MAP_PRINT_MODE)) $D_MAP_PRINT_MODE = 0;//0：通常モード、1：印刷モード
//ズームコントロール ユーザーコントロールが無い場合-1だと出さない
if(!isset($D_MAP_CONTROL)) $D_MAP_CONTROL = 3;
//中心アイコン種別 -1だと出さない
if(!isset($D_MAP_CENTER)) $D_MAP_CENTER = -1;
//スケールバー種別 -1だと出さない
if(!isset($D_MAP_SCALEBAR)) $D_MAP_SCALEBAR = 1;
//情報ボックス種別 -1だと出さない
if(!isset($D_MAP_INFO)) $D_MAP_INFO = -1;
//地図のレイヤー
if(!isset($D_MAP_LAYER_KBN)) $D_MAP_LAYER_KBN = 1;
//読み込み中の表示
if(!isset($D_MAP_WAIT_OFFSETX)) $D_MAP_WAIT_OFFSETX = -60;
if(!isset($D_MAP_WAIT_OFFSETY)) $D_MAP_WAIT_OFFSETY = -12;
if(!isset($D_MAP_WAIT_MSG)) $D_MAP_WAIT_MSG  = "読み込み中です";


// 位置検索系 ----------------------------------------------
//１ページの量
if(!isset($D_SEARCH_LIST_PAGE)) $D_SEARCH_LIST_PAGE  = 10;//リスト形式
if(!isset($D_SEARCH_TABLE_PAGE)) $D_SEARCH_TABLE_PAGE = 16;//テーブル形式
if(!isset($D_SEARCH_SHOPLIST_PAGE)) $D_SEARCH_SHOPLIST_PAGE  = 5;//拠点リスト
if(!isset($D_SEARCH_FROUTE_LIST_PAGE)) $D_SEARCH_FROUTE_LIST_PAGE  = 10;//出発地指定ルートの検索リスト		add 2010/06/16 Y.Matsukawa
//テーブル形式の１行の列数
if(!isset($D_SEARCH_TABLE_COLS)) $D_SEARCH_TABLE_COLS = 4;
//検索名
if(!isset($D_HISTORY_NAME["AddrW"])) $D_HISTORY_NAME["AddrW"] = "住所フリーワード";
if(!isset($D_HISTORY_NAME["StW"])) $D_HISTORY_NAME["StW"]   = "駅フリーワード";
if(!isset($D_HISTORY_NAME["PoiW"])) $D_HISTORY_NAME["PoiW"]  = "施設フリーワード";
if(!isset($D_HISTORY_NAME["ZipW"])) $D_HISTORY_NAME["ZipW"]  = "郵便番号フリーワード";
if(!isset($D_HISTORY_NAME["ShopW"])) $D_HISTORY_NAME["ShopW"] = $D_USER_DEFNAME."フリーワード";
if(!isset($D_HISTORY_NAME["AddrL"])) $D_HISTORY_NAME["AddrL"] = "住所リスト";
if(!isset($D_HISTORY_NAME["StL"])) $D_HISTORY_NAME["StL"]   = "駅リスト";
if(!isset($D_HISTORY_NAME["PoiL"])) $D_HISTORY_NAME["PoiL"]  = "施設リスト";
// mod 2010/11/03 K.Masuda [
if(!isset($D_HISTORY_NAME["ShopA"])) $D_HISTORY_NAME["ShopA"] = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_2"])) $D_HISTORY_NAME["ShopA_2"] = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_3"])) $D_HISTORY_NAME["ShopA_3"] = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_4"])) $D_HISTORY_NAME["ShopA_4"] = $D_USER_DEFNAME."エリア";
if(!isset($D_HISTORY_NAME["ShopA_5"])) $D_HISTORY_NAME["ShopA_5"] = $D_USER_DEFNAME."エリア";
// mod 2010/11/03 K.Masuda ]
if(!isset($D_HISTORY_NAME["Rail"])) $D_HISTORY_NAME["Rail"]  = "路線図検索";
if(!isset($D_HISTORY_NAME["Area"])) $D_HISTORY_NAME["Area"]  = "地域図検索";
if(!isset($D_HISTORY_NAME["List"])) $D_HISTORY_NAME["List"]  = "検索結果";
if(!isset($D_HISTORY_NAME["Detail"])) $D_HISTORY_NAME["Detail"] = "詳細表示";
if(!isset($D_HISTORY_NAME["Npoi"])) $D_HISTORY_NAME["Npoi"]  = "最寄施設検索";
if(!isset($D_HISTORY_NAME["Neki"])) $D_HISTORY_NAME["Neki"]  = "最寄駅検索";
if(!isset($D_HISTORY_NAME["Nshop"])) $D_HISTORY_NAME["Nshop"]  = $D_USER_DEFNAME."リスト";		// add 2010/03/09 Y.Matsukawa
if(!isset($D_HISTORY_NAME["FRoute"])) $D_HISTORY_NAME["FRoute"]  = "出発地指定ルート";		// add 2010/06/16 Y.Matsukawa
if(!isset($D_HISTORY_NAME["MyArea"])) $D_HISTORY_NAME["MyAreaEdit"]  = "Myエリアの編集・削除";		// add 2011/04/14 H.Osamoto
if(!isset($D_HISTORY_NAME["MyArea"])) $D_HISTORY_NAME["MyArea"]  = "Myエリア";		// add 2011/04/14 H.Osamoto
if(!isset($D_HISTORY_NAME["Comb"])) $D_HISTORY_NAME["Comb"]  = "フリーワード検索";		// add 2011/06/02 H.Osamoto
//項目名
if(!isset($D_SEL_NAME["AddrW"])) $D_SEL_NAME["AddrW"] = "住所";
if(!isset($D_SEL_NAME["StW"])) $D_SEL_NAME["StW"]   = "駅";
if(!isset($D_SEL_NAME["PoiW"])) $D_SEL_NAME["PoiW"]  = "施設";
if(!isset($D_SEL_NAME["ZipW"])) $D_SEL_NAME["ZipW"]  = "住所";
if(!isset($D_SEL_NAME["ShopW"])) $D_SEL_NAME["ShopW"] = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["AddrL"])) $D_SEL_NAME["AddrL"] = "住所";
if(!isset($D_SEL_NAME["StL"])) $D_SEL_NAME["StL"]   = "駅";
if(!isset($D_SEL_NAME["PoiL"])) $D_SEL_NAME["PoiL"]  = "施設";
if(!isset($D_SEL_NAME["ShopA"])) $D_SEL_NAME["ShopA"] = $D_USER_DEFNAME;
if(!isset($D_SEL_NAME["PoiJnr"])) $D_SEL_NAME["PoiJnr"]  = "ジャンル";
if(!isset($D_SEL_NAME["Nshop"])) $D_SEL_NAME["Nshop"] = $D_USER_DEFNAME;		// add 2010/03/09 Y.Matsukawa
if(!isset($D_SEL_NAME["Err"])) $D_SEL_NAME["Err"] = "エラー";		// add 2011/07/05 Y.Nakajima
//拠点エリア検索表示名称
if(!isset($D_SEARCH_SHOPA_DISPNM[1])) $D_SEARCH_SHOPA_DISPNM[1]  = $D_SEL_NAME["AddrL"];//第1階層
if(!isset($D_SEARCH_SHOPA_DISPNM[2])) $D_SEARCH_SHOPA_DISPNM[2]  = $D_SEL_NAME["AddrL"];//第2階層
// add 2010/11/03 K.Masuda [
// mod 2011/07/05 Y.Nakajima [
if(!isset($D_SEARCH_SHOPA_DISPNM[3])) $D_SEARCH_SHOPA_DISPNM[3]  = $D_SEL_NAME["AddrL"];//第1階層	エリア検索２
if(!isset($D_SEARCH_SHOPA_DISPNM[4])) $D_SEARCH_SHOPA_DISPNM[4]  = $D_SEL_NAME["AddrL"];//第2階層
if(!isset($D_SEARCH_SHOPA_DISPNM[5])) $D_SEARCH_SHOPA_DISPNM[5]  = $D_SEL_NAME["AddrL"];//第1階層	エリア検索３
if(!isset($D_SEARCH_SHOPA_DISPNM[6])) $D_SEARCH_SHOPA_DISPNM[6]  = $D_SEL_NAME["AddrL"];//第2階層
if(!isset($D_SEARCH_SHOPA_DISPNM[7])) $D_SEARCH_SHOPA_DISPNM[7]  = $D_SEL_NAME["AddrL"];//第1階層	エリア検索４
if(!isset($D_SEARCH_SHOPA_DISPNM[8])) $D_SEARCH_SHOPA_DISPNM[8]  = $D_SEL_NAME["AddrL"];//第2階層
if(!isset($D_SEARCH_SHOPA_DISPNM[9])) $D_SEARCH_SHOPA_DISPNM[9]  = $D_SEL_NAME["AddrL"];//第1階層	エリア検索５
if(!isset($D_SEARCH_SHOPA_DISPNM[10])) $D_SEARCH_SHOPA_DISPNM[10]  = $D_SEL_NAME["AddrL"];//第2階層
// mod 2011/07/05 Y.Nakajima ]
// add 2010/11/03 K.Masuda ]
//言語
if(!isset($D_EKI_LANG)) $D_EKI_LANG = '';//駅
if(!isset($D_POI_LANG)) $D_POI_LANG = '';//施設



// 拠点系 --------------------------------------------------
//拠点アイコン情報
if(!isset($D_ICON_MSGOFFSETX)) $D_ICON_MSGOFFSETX = 0;
if(!isset($D_ICON_MSGOFFSETY)) $D_ICON_MSGOFFSETY = -8;
//デフォルト拠点アイコン情報		add 2008/12/18 Y.Matsukawa
//if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE."img/000000.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_SHOP_W)) $D_ICON_SHOP_W = 11;
if(!isset($D_ICON_SHOP_H)) $D_ICON_SHOP_H = 11;
//拠点アイコン情報-NEW
//if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE."img/new.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE_G."img/new.gif";
if(!isset($D_ICON_NEW_W)) $D_ICON_NEW_W = 23;
if(!isset($D_ICON_NEW_H)) $D_ICON_NEW_H = 10;
//カーソルアイコン情報
//if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE."img/icon_cursor/0000.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE_G."img/icon_cursor/0000.gif";
if(!isset($D_ICON_CURSOR_W)) $D_ICON_CURSOR_W = 51;
if(!isset($D_ICON_CURSOR_H)) $D_ICON_CURSOR_H = 50;
//フォーカスアイコン情報
//if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE."img/icon_cursor/0003.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE_G."img/icon_cursor/0003.gif";
if(!isset($D_ICON_FOCUS_W)) $D_ICON_FOCUS_W = 51;
if(!isset($D_ICON_FOCUS_H)) $D_ICON_FOCUS_H = 50;
//最寄駅検索
//if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE."img/icon_eki/0000.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE_G."img/icon_eki/0000.gif";
if(!isset($D_ICON_EKI_W)) $D_ICON_EKI_W = 19;
if(!isset($D_ICON_EKI_H)) $D_ICON_EKI_H = 24;
if(!isset($D_ICON_EKI_OFFSET_X)) $D_ICON_EKI_OFFSET_X = -10;
if(!isset($D_ICON_EKI_OFFSET_Y)) $D_ICON_EKI_OFFSET_Y = -12;
//最寄施設検索
//if(!isset($D_ICON_POI_IMAGE_DIR)) $D_ICON_POI_IMAGE_DIR = $D_DIR_BASE."img/icon_poi/";		mod 2010/07/20 Y.Matsukawa
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
// icn省略時のデフォルトアイコン（☆）0：表示しない、1：表示する		add 2008/12/18 Y.Matsukawa
if(!isset($D_DEFAULT_ICN)) $D_DEFAULT_ICN = 0;
// 拠点データトリミング		add 2012/06/21 Y.Matsukawa
if(!isset($D_SHOPDATA_TRIM_WIDTH)) $D_SHOPDATA_TRIM_WIDTH = array();	// トリミング幅（バイト数）
if(!isset($D_SHOPDATA_TRIM_MARKER)) $D_SHOPDATA_TRIM_MARKER = array();	// トリミング後付与文字列
if(!isset($D_SHOPDATA_TRIM_TYPE)) $D_SHOPDATA_TRIM_TYPE = array();		// 1:マーカー含めて指定幅トリム、2：指定幅にトリム後マーカー付与


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
//スタート地点アイコン
//if(!isset($D_ROUTE_START_IMAGE)) $D_ROUTE_START_IMAGE = $D_DIR_BASE."img/route/RouteStart.png";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_START_IMAGE)) $D_ROUTE_START_IMAGE = $D_DIR_BASE_G."img/route/RouteStart.png";
//if(!isset($D_ROUTE_START_GIF)) $D_ROUTE_START_GIF = $D_DIR_BASE."img/route/RouteStart.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_START_GIF)) $D_ROUTE_START_GIF = $D_DIR_BASE_G."img/route/RouteStart.gif";
if(!isset($D_ROUTE_START_OFFSET_X)) $D_ROUTE_START_OFFSET_X = -4;
if(!isset($D_ROUTE_START_OFFSET_Y)) $D_ROUTE_START_OFFSET_Y = -36;
//ゴール地点アイコン
//if(!isset($D_ROUTE_GOAL_IMAGE)) $D_ROUTE_GOAL_IMAGE = $D_DIR_BASE."img/route/RouteEnd.png";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_GOAL_IMAGE)) $D_ROUTE_GOAL_IMAGE = $D_DIR_BASE_G."img/route/RouteEnd.png";
//if(!isset($D_ROUTE_GOAL_GIF)) $D_ROUTE_GOAL_GIF = $D_DIR_BASE."img/route/RouteEnd.gif";		mod 2010/07/20 Y.Matsukawa
if(!isset($D_ROUTE_GOAL_GIF)) $D_ROUTE_GOAL_GIF = $D_DIR_BASE_G."img/route/RouteEnd.gif";
if(!isset($D_ROUTE_GOAL_OFFSET_X)) $D_ROUTE_GOAL_OFFSET_X = -4;
if(!isset($D_ROUTE_GOAL_OFFSET_Y)) $D_ROUTE_GOAL_OFFSET_Y = -36;


// 画面履歴 ------------------------------------------------
//区切り文字
if(!isset($D_HISTORY_SEP)) $D_HISTORY_SEP = "&nbsp;&gt;&nbsp;";
//TOP画面
if(!isset($D_HISTORY_TOP_NAME)) $D_HISTORY_TOP_NAME = $D_USER_DEFNAME."案内TOP";


// Maplink ------------------------------------------------
//住所文字列接続のマッチング住所を表示する			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_DISP)) $D_ADDR_MATCH_DISP = 0;
//住所文字列接続のマッチング住所 前方文章			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_HEAD)) $D_ADDR_MATCH_HEAD = '';
//住所文字列接続のマッチング住所 後方文章			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_TAIL)) $D_ADDR_MATCH_TAIL = '';
//住所文字列接続のマッチング住所 注意文言			add 2008/09/02 Y.Matsukawa
if(!isset($D_ADDR_MATCH_EXP)) $D_ADDR_MATCH_EXP = '';

?>
