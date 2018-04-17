<?php
// ------------------------------------------------------------
// 定義ファイル デザインに関する項目
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/05/12 Y.Matsukawa	テンプレート生成対応
// 2011/05/23 Y.Matsukawa	テンプレート生成対応
// 2011/07/13 Y.Matsukawa	機能追加（ルート探索、最寄駅）
// 2011/08/08 Y.Matsukawa	機能追加（絞り込み拡張、拠点エリア検索、駅リスト検索）
// 2011/08/11 H.Osamoto		地図以外表示領域初期値設定
// 2011/12/26 K.Masuda 		地図以外表示領域初期値設定（横サイズ）
// 2012/03/04 K.Masuda		p_f、p_sパラメータ最大数設定追加
// 2012/07/18 Y.Matsukawa	最寄施設
// 2012/11/15 Y.Matsukawa	JCN満空情報取得
// 2012/12/17 H.Osamoto		神奈川電通広告向けカスタマイズ
// 2014/09/11 Y.Matsukawa	縮尺ボタン（小サイズ）
// 2015/02/10 Y.Matsukawa	店舗リスト検索TOP
// 2015/10/30 N.Wada		吹き出しカスタマイズ
//							MarkerClustererアイコンのスタイル設定
//							Google Maps版コントローラの非表示
// 2016/03/03 Y.Matsukawa	地図サイズを％指定
// 2016/03/22 N.Wada		拠点アイコンの中央下が拠点位置を指すパターン追加
// 2016/03/23 N.Wada		Google Maps版拠点案内用の独自UI追加
// 2016/03/25 N.Wada		スタート地点、ゴール地点アイコンの幅・高さ追加
// 2016/12/19 N.Wada		Google Maps版標準ズームボタンの位置追加
// 2017/01/21 N.Wada		ルート描画時の電車用の線の設定追加
// ------------------------------------------------------------

//「店舗」の標準の呼び方
//if(!isset($D_USER_DEFNAME)) $D_USER_DEFNAME = '店舗';		mod 2011/05/23 Y.Matsukawa
if(!isset($D_SHOP_NAME)) $D_SHOP_NAME = '店舗';

// HTMLタイトル
//if(!isset($D_TITLE)) $D_TITLE = $D_USER_DEFNAME.'検索';	mod 2011/05/23 Y.Matsukawa
if(!isset($D_TITLE)) $D_TITLE = $D_SHOP_NAME.'検索';

// 店舗フリーワード入力ガイド表示
if(!isset($D_SHOP_FW_INIT)) $D_SHOP_FW_INIT = '店舗名';
// 位置検索フリーワード入力ガイド表示
if(!isset($D_PL_FW_INIT)) $D_PL_FW_INIT = '駅・住所・施設';

// 「場所を指定」ボタン表記		add 2011/05/12 Y.Matsukawa
if(!isset($D_PLBTN_TXT)) $D_PLBTN_TXT = '場所を指定する';

// 絞り込み条件タイトル
if(!isset($D_FILTER_TITLE)) $D_FILTER_TITLE = 'カテゴリを指定する';
if(!isset($D_COND_BTN))    $D_COND_BTN = '絞り込み条件を指定する';		// add 2011/08/08 Y.Matsukawa
if(!isset($D_COND_BTN_ON)) $D_COND_BTN_ON = '絞り込み条件 指定済み';	// add 2011/08/08 Y.Matsukawa

// 地図 ----------------------------------------------
// 地図タイプ		add 2011/05/23 Y.Matsukawa
if(!isset($D_MAP_TYPE)) $D_MAP_TYPE = 9;
// 地図以外表示領域（最寄り店舗地図）	add 2011/08/11 H.osamoto
if(!isset($D_NMAP_ANY_DISP_PX)) $D_NMAP_ANY_DISP_PX = 0;
if(!isset($D_NMAP_ANY_DISP_PY)) $D_NMAP_ANY_DISP_PY = 0;	// add 2011/12/26 K.Masuda
// 地図以外表示領域（店舗地図）	add 2011/08/11 H.osamoto
if(!isset($D_MAP_ANY_DISP_PX)) $D_MAP_ANY_DISP_PX = 0;
if(!isset($D_MAP_ANY_DISP_PY)) $D_MAP_ANY_DISP_PY = 0;	// add 2011/12/26 K.Masuda
// 地図サイズ％指定（小数で指定）		add 2016/03/03 Y.Matsukawa
if(!isset($D_NMAP_SIZE_PER_H)) $D_NMAP_SIZE_PER_H = 0.0;
// 縮尺ボタンサイズ		add 2014/09/11 Y.Matsukawa
if(!isset($D_LVL_BTN_SIZE)) $D_LVL_BTN_SIZE = '';
//Google Maps版拠点案内用の独自UI	add 2016/03/23 N.Wada
if(!isset($D_GOOGLEMAPS_EMAP_ORIGINAL_UI)) $D_GOOGLEMAPS_EMAP_ORIGINAL_UI = 0;	//0:使わない、1:使う
//Google Maps版コントローラの非表示	add 2015/10/30
if(!isset($D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_MAP_TYPE_CONTROL_INVISIBLE = 0;	//マップタイプ切り替えコントローラ
if(!isset($D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_NAVIGATION_CONTROL_INVISIBLE = 0;	//ナビゲーションコントローラ
if(!isset($D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_SCALE_CONTROL_INVISIBLE = 0;	//スケールコントローラ
if(!isset($D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_ZOOM_CONTROL_INVISIBLE = 0;	//ズームコントローラ
if(!isset($D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE)) $D_GOOGLEMAPS_PAN_CONTROL_INVISIBLE = 0;	//パンコントローラ
if(!isset($D_GOOGLEMAPS_ZOOM_CONTROL_POSITION)) $D_GOOGLEMAPS_ZOOM_CONTROL_POSITION = '';	//ズームコントローラ位置 add 2016/12/19 N.Wada
//吹き出しカスタマイズ（要infobox.js）	add 2015/10/30
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM)) $D_GOOGLEMAPS_MSG_CUSTOM = 0;
if(!isset($D_GOOGLEMAPS_MSG_CUSTOM_OPTION)) $D_GOOGLEMAPS_MSG_CUSTOM_OPTION  = "";

// 位置検索系 ----------------------------------------------
// １ページの量
if(!isset($D_SEARCH_LIST_PAGE)) $D_SEARCH_LIST_PAGE  = 10;//リスト形式

// add 2011/07/13 Y.Matsukawa
// ルート探索系 --------------------------------------------
if(!isset($D_ROUTE_CAR_WIDTH)) $D_ROUTE_CAR_WIDTH   = "5";// 幅
if(!isset($D_ROUTE_CAR_OPACITY)) $D_ROUTE_CAR_OPACITY = "0.5";// 透明度
if(!isset($D_ROUTE_CAR_COLOR)) $D_ROUTE_CAR_COLOR   = "#0000ff";//色
if(!isset($D_ROUTE_WALK_WIDTH)) $D_ROUTE_WALK_WIDTH   = "5";// 幅
if(!isset($D_ROUTE_WALK_OPACITY)) $D_ROUTE_WALK_OPACITY = "0.5";// 透明度
if(!isset($D_ROUTE_WALK_COLOR)) $D_ROUTE_WALK_COLOR   = "#0000ff";//色
if(!isset($D_ROUTE_TRAIN_WIDTH)) $D_ROUTE_TRAIN_WIDTH   = "5";// 幅（電車用）	add 2017/01/21 N.Wada
if(!isset($D_ROUTE_TRAIN_OPACITY)) $D_ROUTE_TRAIN_OPACITY = "0.5";// 透明度（電車用）	add 2017/01/21 N.Wada
if(!isset($D_ROUTE_TRAIN_COLOR)) $D_ROUTE_TRAIN_COLOR   = "#0000ff";//色（電車用）	add 2017/01/21 N.Wada
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

// 拠点系 --------------------------------------------------
// 拠点アイコン情報
if(!isset($D_ICON_MSGOFFSETX)) $D_ICON_MSGOFFSETX = 0;
if(!isset($D_ICON_MSGOFFSETY)) $D_ICON_MSGOFFSETY = -8;
//拠点アイコンと拠点位置の関係	add 2016/03/22 N.Wada
if(!isset($D_ICON_ANCHOR_CENTER_BOTTOM)) $D_ICON_ANCHOR_CENTER_BOTTOM = 0;	// アイコンの中央下が拠点の位置を指す
// デフォルト拠点アイコン情報
if(!isset($D_ICON_SHOP_IMG)) $D_ICON_SHOP_IMG = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_SHOP_W)) $D_ICON_SHOP_W = 11;
if(!isset($D_ICON_SHOP_H)) $D_ICON_SHOP_H = 11;
// 拠点アイコン情報-NEW
if(!isset($D_ICON_NEW_IMG)) $D_ICON_NEW_IMG = $D_DIR_BASE_G."img/new.gif";
if(!isset($D_ICON_NEW_W)) $D_ICON_NEW_W = 23;
if(!isset($D_ICON_NEW_H)) $D_ICON_NEW_H = 10;
// カーソルアイコン情報
if(!isset($D_ICON_CURSOR_IMG)) $D_ICON_CURSOR_IMG = $D_DIR_BASE_G."img/icon_cursor/0000.gif";
if(!isset($D_ICON_CURSOR_W)) $D_ICON_CURSOR_W = 51;
if(!isset($D_ICON_CURSOR_H)) $D_ICON_CURSOR_H = 50;
// フォーカスアイコン情報
if(!isset($D_ICON_FOCUS_IMG)) $D_ICON_FOCUS_IMG = $D_DIR_BASE_G."img/icon_cursor/0003.gif";
if(!isset($D_ICON_FOCUS_W)) $D_ICON_FOCUS_W = 51;
if(!isset($D_ICON_FOCUS_H)) $D_ICON_FOCUS_H = 50;
//透明アイコン情報		add 2012/11/15 Y.Matsukawa
if(!isset($D_ICON_TP_IMG)) $D_ICON_TP_IMG = $D_DIR_BASE_G."img/tp11.gif";
if(!isset($D_ICON_TP_W)) $D_ICON_TP_W = 11;
if(!isset($D_ICON_TP_H)) $D_ICON_TP_H = 11;
// 拠点リスト検索		add 2015/02/10 Y.Matsukawa
if(!isset($D_SHOPA_DISPNM[1])) {
	$D_SHOPA_DISPNM[1][1] = '都道府県';
	$D_SHOPA_DISPNM[1][2] = '市区町村';
}
if(!isset($D_SHOPA_DISPNM[2])) {
	$D_SHOPA_DISPNM[2][1] = '';
	$D_SHOPA_DISPNM[2][2] = '';
}
if(!isset($D_SHOPA_DISPNM[3])) {
	$D_SHOPA_DISPNM[3][1] = '';
	$D_SHOPA_DISPNM[3][2] = '';
}
if(!isset($D_SHOPA_DISPNM[4])) {
	$D_SHOPA_DISPNM[4][1] = '';
	$D_SHOPA_DISPNM[4][2] = '';
}
if(!isset($D_SHOPA_DISPNM[5])) {
	$D_SHOPA_DISPNM[5][1] = '';
	$D_SHOPA_DISPNM[5][2] = '';
}

//最寄駅検索		add 2011/07/13 Y.Matsukawa
if(!isset($D_ICON_EKI_IMAGE)) $D_ICON_EKI_IMAGE = $D_DIR_BASE_G."img/icon_eki/0000.gif";
if(!isset($D_ICON_EKI_W)) $D_ICON_EKI_W = 19;
if(!isset($D_ICON_EKI_H)) $D_ICON_EKI_H = 24;
if(!isset($D_ICON_EKI_OFFSET_X)) $D_ICON_EKI_OFFSET_X = -10;
if(!isset($D_ICON_EKI_OFFSET_Y)) $D_ICON_EKI_OFFSET_Y = -12;

//最寄施設検索		add 2012/07/18 Y.Matsukawa
if(!isset($D_ICON_POI_IMAGE_DIR)) $D_ICON_POI_IMAGE_DIR = $D_DIR_BASE_G."img/icon_poi/";
if(!isset($D_ICON_POI_W)) $D_ICON_POI_W = 16;
if(!isset($D_ICON_POI_H)) $D_ICON_POI_H = 16;
if(!isset($D_ICON_POI_OFFSET_X)) $D_ICON_POI_OFFSET_X = -8;
if(!isset($D_ICON_POI_OFFSET_Y)) $D_ICON_POI_OFFSET_Y = -8;

//神奈川電通広告用現在地アイコン	add 2012/12/17 H.Osamoto
if(!isset($D_ICON_NOW_IMAGE)) $D_ICON_NOW_IMAGE = $D_DIR_BASE_G."img/000000.gif";
if(!isset($D_ICON_NOW_W)) $D_ICON_NOW_W = 11;
if(!isset($D_ICON_NOW_H)) $D_ICON_NOW_H = 11;
if(!isset($D_ICON_NOW_OFFSET_X)) $D_ICON_NOW_OFFSET_X = 0;
if(!isset($D_ICON_NOW_OFFSET_Y)) $D_ICON_NOW_OFFSET_Y = 0;

// 読み込み中メッセージ
if(!isset($D_WAIT_MSG)) $D_WAIT_MSG = "読み込み中です";

// MarkerClustererアイコンのスタイル設定（要markerclustere.js）	add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES)) $D_GOOGLEMAPS_MARKER_CLUSTERER_STYLES  = "";

// メッセージウィンドウ関係 --------------------------------
// 拠点吹き出し
if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
	ZdcEmapMsg.setImage('{$D_DIR_BASE_G}img/msg/0002.png',new ZdcSize(242,95),
	                    '{$D_DIR_BASE_G}img/msg/0002-t.png',new ZdcSize(194,67),
	                    '{$D_DIR_BASE_G}img/msg/0002-x.png',new ZdcSize(13,13),
	                    '{$D_DIR_BASE_G}img/msg/0002-s.png',new ZdcSize(13,13),
	                    null);
	ZdcEmapMsg.setDocPosition(0,0,11,8,11,224,55,0);
	ZdcEmapMsg.setDocOffset(-110,-90);
	ZdcEmapMsg.setTextClass('UserMsgWindowTextStyle');
EOF;

// add 2012/03/04 K.Masuda [
if (!isset($D_P_F_MAX)) $D_P_F_MAX = 100;
if (!isset($D_P_S_MAX)) $D_P_S_MAX = 100;
// add 2012/03/04 K.Masuda ]
?>
