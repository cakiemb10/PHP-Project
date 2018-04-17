<?php
// ------------------------------------------------------------
// 定義ファイル 動作に関する項目
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2009/10/13 Y.Matsukawa	最寄り拠点一覧に詳細拠点を出さない
// 2009/10/14 Y.Matsukawa	マウスアウトで吹き出しを消す
// 2010/06/16 Y.Matsukawa	Standard住所接続I/F
// 2010/09/13 Y.Matsukawa	拠点詳細表示時に拠点IDをCookie保存
// 2011/07/06 K.masuda		吹き出し表示時、地図内に収まらないとき地図移動するか
// 2011/08/23 Y.Matsukawa	地図非表示拠点
// 2012/06/19 Y.Matsukawa	店舗詳細Cookie保存機能追加（任意タイミングの保存、クリア、取得関数）
// 2012/07/25 H.Osamoto		PC2.0リダイレクト時のパラメータ
// 2013/04/15 H.Osamoto		最寄検索結果が0件の場合再検索で取得する件数指定機能追加
// 2014/02/07 F.Yokoi		QRコードのURL(qrimgurl)を携帯URL→任意カラム値(col_**)に変更する処理を追加
// 2016/02/18 Y.Matsukawa	最寄り検索にだけ適用するcond／拠点エリア検索にだけ適用するcond
// 2016/11/15 K.Tani		地図操作時に再検索しないモード
// ------------------------------------------------------------
// 初期動作/サイト接続 -------------------------------------
//サービス内容
if(!isset($D_SEVICE_TYPE)) $D_SEVICE_TYPE ="S";//S:standard L:light N:maplink

//TOPページ
if(!isset($D_HISTORY_TOP_LINK)) $D_HISTORY_TOP_LINK = "ZdcEmapSearchOpen('','','');";

//JSAPIのロードなどでエラーが発生した場合の飛び先
if(!isset($D_URL_JSAPIERROR)) $D_URL_JSAPIERROR = "http://".$EMAP_SSAPI_SRV."/error/jsapierror.html";

//許可リファラー
if(!isset($D_ALLOW_REFERER)) $D_ALLOW_REFERER  = "*";
if(!isset($D_ALLOW_REFERER_NULL)) $D_ALLOW_REFERER_NULL  = 1;//空を許可するか否か 0:不可 1:許可

//Basic認証
if(!isset($D_BASIC_AUTH["dev"])) $D_BASIC_AUTH["dev"] = 0;  //開発環境のBasic認証On/Off
if(!isset($D_BASIC_AUTH["test"])) $D_BASIC_AUTH["test"] = 0;//検証環境のBasic認証On/Off
if(!isset($D_BASIC_AUTH["www"])) $D_BASIC_AUTH["www"] = 0;  //本番環境のBasic認証On/Off

//Maplink住所接続
if(!isset($D_MAPLINK_ADDR_IF)) $D_MAPLINK_ADDR_IF = 0;

//Standard住所接続			add 2010/06/16 Y.Matsukawa
if(!isset($D_STANDARD_ADDR_IF)) $D_STANDARD_ADDR_IF = 0;

//地図の初期位置
if(!isset($D_INIT_LAT)) $D_INIT_LAT = 128456476;
if(!isset($D_INIT_LON)) $D_INIT_LON = 503030954;

//初期ズーム
if(!isset($D_INIT_LVL)) $D_INIT_LVL        = 1;//初期表示
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH = -1;//位置検索決定後（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = -1;//詳細選択後（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
if(!isset($D_INIT_LVL_PRINT)) $D_INIT_LVL_PRINT   = -1;//印刷画面（-1：$D_INIT_LVLに準じる）

//アイコンを表示する最大最小縮尺
if(!isset($D_VIEW_ICON_MAX)) $D_VIEW_ICON_MAX = 4;
if(!isset($D_VIEW_ICON_MIN)) $D_VIEW_ICON_MIN = 18;

//最大最小縮尺
if(!isset($D_MAP_SCALE_MAX)) $D_MAP_SCALE_MAX = 0;
if(!isset($D_MAP_SCALE_MIN)) $D_MAP_SCALE_MIN = 18;

//指定拠点以外非表示区分
if(!isset($D_DSP_OTHER_KBN)) $D_DSP_OTHER_KBN = 0;

//地図移動方法 シングルクリックとかダブルクリックとか？
if(!isset($D_MAP_CLICK_KBN)) $D_MAP_CLICK_KBN = 0;

//ホイールスクロールによるズーム 0:無し 1:有り
if(!isset($D_MAP_WHEEL_KBN)) $D_MAP_WHEEL_KBN = 0;


//拠点アイコン上での動作
if(!isset($D_KYO_ICON_MO)) $D_KYO_ICON_MO = 0;
if(!isset($D_KYO_ICON_CLK)) $D_KYO_ICON_CLK = 1;
if(!isset($D_KYO_ICON_MOUT)) $D_KYO_ICON_MOUT = 0;	// マウスアウト（1：吹き出しを消す）		add 2009/10/14 Y.Matsukawa

//吹き出し表示時、地図内に収まらないとき地図移動するか（1：する、3：しない）
if(!isset($D_FUKIDASHI_MOVE)) $D_FUKIDASHI_MOVE = 1;	// add 2011/07/06 K.Masuda

//PC2.0リダイレクト時のトップページURL
if(!isset($D_REDIRECT_TOP_URL)) $D_REDIRECT_TOP_URL = "";	// add 2012/07/25 H.Osamoto
//PC2.0リダイレクト時のパラメータ
if(!isset($D_REDIRECT_PRM)) $D_REDIRECT_PRM = "";	// add 2012/07/25 H.Osamoto

// 位置検索系 ----------------------------------------------
//住所リスト・駅リストでのかな絞込みの有無 0:無し 1:有り
if(!isset($D_SEARCH_KANA)) $D_SEARCH_KANA = 0;

//住所リストをどの階層まで掘り下げるか（1：都道府県、2：市区町村、3：大字、4：字丁目、5：街区、6：地番（枝番）
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 6;

//最大検索ページ数
if(!isset($D_SEARCH_MAXPAGE["AddrW"])) $D_SEARCH_MAXPAGE["AddrW"] = 9;
if(!isset($D_SEARCH_MAXPAGE["StW"])) $D_SEARCH_MAXPAGE["StW"]   = 9;
//不要 if(!isset($D_SEARCH_MAXPAGE["PoiW"])) $D_SEARCH_MAXPAGE["PoiW"]  = 9;
//不要 if(!isset($D_SEARCH_MAXPAGE["ZipW"])) $D_SEARCH_MAXPAGE["ZipW"]  = 9;
if(!isset($D_SEARCH_MAXPAGE["ShopW"])) $D_SEARCH_MAXPAGE["ShopW"] = 9;
//不要 if(!isset($D_SEARCH_MAXPAGE["AddrL"])) $D_SEARCH_MAXPAGE["AddrL"] = 9;
//不要 if(!isset($D_SEARCH_MAXPAGE["StL"])) $D_SEARCH_MAXPAGE["StL"]   = 9;
//不要 if(!isset($D_SEARCH_MAXPAGE["PoiL"])) $D_SEARCH_MAXPAGE["PoiL"]  = 9;
//不要 if(!isset($D_SEARCH_MAXPAGE["ShopA"])) $D_SEARCH_MAXPAGE["ShopA"] = 9;

//フリーワードでの全文・部分一致
if(!isset($D_SEARCH_SRCHMODE_STW)) $D_SEARCH_SRCHMODE_STW = 0;

//施設検索 -------------------
//企業ID CORPID
if(!isset($D_SEARCH_CORPID)) $D_SEARCH_CORPID = 'ZDC';
//サービスID SRVSID
if(!isset($D_SRARCH_SRVSID)) $D_SRARCH_SRVSID = 'API001';
//絞込み発生件数
if(!isset($D_SEARCH_POI_SCNT)) $D_SEARCH_POI_SCNT = $D_SEARCH_TABLE_PAGE * 10;
//施設フリーワード・施設リストで除外するジャンルコード ※CGIが未対応のため動作しない
if(!isset($D_SEARCH_POI_JNRMN_NG)) $D_SEARCH_POI_JNRMN_NG = "";//形式  "00140,00160,00270,00280";
if(!isset($D_SEARCH_POI_JNR_NG)) $D_SEARCH_POI_JNR_NG   = "";//形式  "00290:00010,00290:00080,00290:00090,00290:00100";



// 拠点検索系 ----------------------------------------------
//拠点詳細地図なし		add 2011/08/23 Y.Matsukawa
if(!isset($D_NOMAP_KYOTEN_COND)) $D_NOMAP_KYOTEN_COND = null;
//最寄拠点 -------------------
//１ページの量
if(!isset($D_SHOP_PAGE)) $D_SHOP_PAGE = 10;//リストのみ
if(!isset($D_SHOP_PAGE_DETAIL)) $D_SHOP_PAGE_DETAIL = 3;//詳細表示時
//最大件数
if(!isset($D_SHOP_MAX)) $D_SHOP_MAX= 30;
//検索条件(チェックボックス同士)
if(!isset($D_SHOP_COND)) $D_SHOP_COND = "OR";
//検索条件(カラム同士)
if(!isset($D_SHOP_COND_COL)) $D_SHOP_COND_COL = "AND";
//詳細表示したらリスト消すか
if(!isset($D_SHOP_CLOSELIST)) $D_SHOP_CLOSELIST = 0;
//印刷画面で最寄り拠点を検索するか
if(!isset($D_SHOP_PRINT_SEARCH)) $D_SHOP_PRINT_SEARCH = 1;
//指定ピクセル以上移動したときのみ検索 -1の場合再検索しない
if(!isset($D_SHOP_SEARCHPIX)) $D_SHOP_SEARCHPIX = 5;
//位置決定後の検索範囲(m)  0だと画面範囲全部
if(!isset($D_SHOP_RAD)) $D_SHOP_RAD = 50000;
//再検索時の検索範囲(m) 0だと画面範囲全部
if(!isset($D_SHOP_RAD_RE)) $D_SHOP_RAD_RE = 0;
//最寄り拠点一覧に詳細拠点を表示しない		add 2009/10/13 Y.Matsukawa
if(!isset($D_SHOP_LIST_NO_DTLSHOP)) $D_SHOP_LIST_NO_DTLSHOP = 0;
//地図操作で最寄り再検索しない		add 2016/11/15 K.Tani
if(!isset($D_SHOP_NO_SEARCH_USER_ACT)) $D_SHOP_NO_SEARCH_USER_ACT = 0;
//最寄り検索にだけ適用するcond		add 2016/02/18 Y.Matsukawa
if(!isset($D_N_COND)) $D_N_COND = "";
//拠点エリア検索にだけ適用するcond		add 2016/02/18 Y.Matsukawa
if(!isset($D_SHOPA_COND)) $D_SHOPA_COND = "";
//パンくずで戻る際にcondを保持する		add 2016/02/20 Y.Matsukawa
if(!isset($D_KEEP_COND_ON_HISTORY)) $D_KEEP_COND_ON_HISTORY = "";

//最寄施設 -------------------
//検索範囲(拠点からの最寄検索時)
if(!isset($D_POI_RAD)) $D_POI_RAD = 10000;
//１ページの量
if(!isset($D_POI_PAGE)) $D_POI_PAGE = 5;
//最大件数
if(!isset($D_POI_MAX)) $D_POI_MAX = 50;
//ジャンル未選択時に検索対象とするコード
if(!isset($D_POI_JNRMN)) $D_POI_JNRMN = "00160,00250,00140,00170,00220,00240,00130,00110,00120";


//最寄駅  -------------------
//検索範囲
if(!isset($D_ST_RAD)) $D_ST_RAD = 10000;
//１ページの量
if(!isset($D_ST_PAGE)) $D_ST_PAGE = 5;
//最大件数
if(!isset($D_ST_MAX)) $D_ST_MAX = 5;
//リスト非表示
if(!isset($D_HIDE_NEKI_LIST)) $D_HIDE_NEKI_LIST = 1;



// ルート探索系 --------------------------------------------
if(!isset($D_ROUTE_TIMEOUT)) $D_ROUTE_TIMEOUT = 5000;// タイムアウト時間
if(!isset($D_ROUTE_TYPE)) $D_ROUTE_TYPE = 1;// 0:未使用 1:歩行者+自動車 2:自動車 3:歩行者
if(!isset($D_ROUTE_WALK_PSC)) $D_ROUTE_WALK_PSC = 0;//検索条件
if(!isset($D_ROUTE_WALK_FLOORFLG)) $D_ROUTE_WALK_FLOORFLG = 0;//階層フラグ
if(!isset($D_ROUTE_WALK_DEP_FLOOR)) $D_ROUTE_WALK_DEP_FLOOR = 0;//出発：階層フラグ
if(!isset($D_ROUTE_WALK_DEP_STATIONFLG)) $D_ROUTE_WALK_DEP_STATIONFLG = 0;//出発：駅フラグ
if(!isset($D_ROUTE_WALK_ARR_FLOORFLG)) $D_ROUTE_WALK_ARR_FLOORFLG = 0;//到着：階層フラグ
if(!isset($D_ROUTE_WALK_ARR_STATIONFLG)) $D_ROUTE_WALK_ARR_STATIONFLG = 0;//到着：駅フラグ
if(!isset($D_ROUTE_WALK_ARR_FLOOR)) $D_ROUTE_WALK_ARR_FLOOR = 0;//到着：階層


//クリック地図版用設定 ----------------------------------------------
//周辺拠点
if(!isset($D_CLK_SHOP_MAX)) $D_CLK_SHOP_MAX = 50;	//最大数 ※あまり件数が多いと、アイコン重畳処理でエラーになったり、IEで地図が表示されなくなったりします。
//最寄駅
if(!isset($D_CLK_ST_PAGE)) $D_CLK_ST_PAGE = 5;		//１ページ件数
if(!isset($D_CLK_ST_MAX)) $D_CLK_ST_MAX = 5;		//最大数
//最寄施設
if(!isset($D_CLK_POI_PAGE)) $D_CLK_POI_PAGE = 5;	//１ページ件数
if(!isset($D_CLK_POI_MAX)) $D_CLK_POI_MAX = 100;	//最大数
if(!isset($D_CLK_NPOI_DARKICON_MAX)) $D_CLK_NPOI_DARKICON_MAX = 100;		//グレーアイコン最大数（あまり多いと画像が壊れる）
if(!isset($D_CLK_NPOI_DARKICON_MIN_LV)) $D_CLK_NPOI_DARKICON_MIN_LV = 10;	//グレーアイコンを表示する最小縮尺（この縮尺よりズームアウトすると、グレーアイコンは表示されません）


//Cookie保存 ----------------------------------------------		add 2010/09/13 Y.Matsukawa
if(!isset($D_COOKIE_SHOPDTL_MAX)) $D_COOKIE_SHOPDTL_MAX = 0;		//拠点詳細保存件数
if(!isset($D_COOKIE_SHOPDTL_EXPIRE)) $D_COOKIE_SHOPDTL_EXPIRE = 365;	//拠点詳細保存期限（日数）
if(!isset($D_COOKIE_SHOPDTL_AUTO)) $D_COOKIE_SHOPDTL_AUTO = 1;	//拠点詳細自動保存（詳細画面表示と同時に保存）		add 2012/06/19 Y.Matsukawa

//再検索
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;	//最寄検索結果が0件の場合再検索で取得する件数指定		add 2013/04/15 H.Osamoto

// QRコードURL ----------------------------------------------
if(!isset($D_QRIMG_URL_CUST)) $D_QRIMG_URL_CUST = '';		//QRコード用URLを携帯URL→任意カラム値(col_**)に変更するパラメータ文字列		add 2014/02/07 F.Yokoi
if(!isset($D_QRIMG_URL_EX)) $D_QRIMG_URL_EX = '';			//QRコード用URLを任意カラム値(col_**)に変更した時のURL追加パラメータ文字列		add 2014/02/07 F.Yokoi

?>
