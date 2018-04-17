<?php
// ------------------------------------------------------------
// 定義ファイル 動作に関する項目
// 
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2011/12/20 Y.Matsukawa	地図操作時に再検索しないモード
// 2011/12/20 Y.Matsukawa	テンプレート設定ファイル内でエラーメッセージがセットされたらエラー画面表示
// 2011/12/21 Y.Matsukawa	リファラチェック時、https/httpを区別しないモード
// 2012/01/06 Y.Matsukawa	携帯URLに任意パラメータ文字列を付加
// 2012/01/10 Y.Matsukawa	詳細店舗を最寄り一覧に出さないのを固定仕様とする
// 2012/02/27 Y.Matsukawa	拠点IDをCookie保存（任意グルーピング）
// 2012/03/08 Y.Matsukawa	店舗詳細取得時にcond絞り込みを有効にする
// 2012/03/12 Y.Matsukawa	スマホリダイレクト（各種接続I/F対応）
// 2012/04/16 Y.Matsukawa	任意カラムのアイコンIDを使用
// 2012/08/17 Y.Matsukawa	ルート探索駅出口考慮なしをデフォルト化
// 2012/11/13 Y.Matsukawa	JCN満空情報取得
// 2012/11/27 Y.Matsukawa	拠点縮尺項目未設定の場合は縮尺設定を採用しない
// 2013/04/19 H.Osamoto		数字アイコンを企業毎に設定できるよう変更
// 2013/05/14 H.Osamoto		初期表示縮尺を設定できるよう変更
// 2013/05/22 H.Osamoto		最寄検索結果が0件の場合再検索で取得する件数指定機能追加
// 2013/06/13 Y.Matsukawa	Google Maps版
// 2013/07/22 Y.Matsukawa	【ヤマト運輸向けカスタマイズ】郵便番号検索0件の場合、検索TOPへ遷移
// 2013/08/09 Y.Matsukawa	郵便番号検索：任意の列数で表示
// 2013/09/19 H.Osamoto		住所FW検索結果一覧の遷移先を住所リスト検索にする
//							住所FW検索結果が1件だった場合に一覧画面をスキップする
// 2013/09/24 Y.Matsukawa	拠点フリーワード（完全一致）検索
// 2014/02/21 H.Osamoto		ポリゴン内外判定カラム追加
// 2014/05/16 Y.Matsukawa	商品マスタ対応
// 2014/06/06 Y.Matsukawa	再検索時、地図表示範囲外も検索対象とする。（最寄り店舗一覧）
// 2014/07/07 Y.Matsukawa	郵便番号検索：一覧スキップ（最寄り地図へ直接遷移）
// 2014/08/18 Q.Dai			SiteIconOverlapping
// 2014/08/29 Q.Dai 		BrowsingHistoryDisplay
// 2014/09/08 H.Osamoto		地図表示縮尺範囲制限機能追加
// 2014/10/08 Y.Matsukawa	最寄り駅からの任意距離の円表示
// 2014/11/28 Y.Matsukawa	検索位置にマーカー表示
// 2014/12/09 Y.Matsukawa	拠点閲覧履歴の自動保存をフラグで制御
// 2014/12/11 Y.Matsukawa	最寄り地図に住所文字列接続した際のパンくずを緯度経度接続に変換したURLにする
// 2015/01/26 Y.Matsukawa	ソート項目の桁あわせ
// 2015/03/18 N.Wada		拠点アイコンが重なった時の差し替え用重複アイコンID
// 2015/04/09 F.Yokoi		ルート探索 地図上への移動距離・時間表示関係設定用変数の追加
// 2015/05/01 Y.Matsukawa	セブン&アイOMNI専用最寄り検索
// 2015/05/07 Y.Matsukawa	エリア検索第２階層NULL対応
// 2015/05/08 Y.Matsukawa	店舗一覧ソート順指定
// 2015/05/14 Y.Matsukawa	condをnmap/shop_dtlに直接記述（cond.htm未使用）モード
// 2015/06/08 N.Wada		Google版デモ用機能追加
// 2015/08/17 Y.Matsukawa	iPadリダイレクト対応
// 2015/08/25 Y.Matsukawa	スマホリダイレクト（top.location変更）
// 2015/09/30 Y.Uesugi		店舗検索最小件数追加
// 2015/10/20 N.Wada		Google Maps版の店舗検索開始のイベント切り替えを追加
//							Google Maps版POIアイコン制御追加
//							Google Maps版マーカークラスター制御追加
//							拠点FW検索結果一覧の遷移先制御追加
//							住所リスト検索（エリア検索、全検出力、かな行別・２３区行追加）
//							検索エラーのテンプレートのみ表示に対応
// 2015/10/23 Y.Uesugi		ヤマト運輸 営業所検索利用
// 2015/11/11 Y.Matsukawa	ヘッダーでcharset出力
// 2015/11/26 N.Wada		Google Maps版マーカークラスターのクラスタリングする範囲追加
// 2016/01/08 Y.Uesugi		地図中心マークの画像の変更機能追加
// 2016/01/22 H.Yasunaga	711mapニッセン向けカスタマイズ
// 2016/03/10 Y.Matsukawa	英語版対応（住所フリーワード検索）
// 2016/03/14 Y.Matsukawa	吹き出し（複数リスト）に連番表示
// 2016/03/17 H.Osamoto		最寄再検索不具合対応
// 2016/04/21 H.Osamoto		縮尺によるアイコン表示制御を削除
// 2016/04/26 N.Wada		現在地取得エラー時の遷移先指定
// 2016/05/13 N.Wada		閲覧履歴（複数）Cookieのキーに任意の文字列を追加
//							パンくずCookieのキーに任意の文字列を追加
// 2016/06/14 Y.Matsukawa	日本郵政用郵便番号検索
// 2016/06/30 N.Wada		詳細エラー時のリダイレクト先URL追加
// 2016/08/16 Y.Matsukawa	世界測地系保持
// 2016/08/25 Y.Uesugi		ルートにマーカ表示を追加
// 2016/09/29 Y.Uesugi		住所リンクSEO対策
// 2016/11/10 N.Wada		施設ジャンルメニューが複数指定してある場合は、ジャンルメニュー選択画面を表示
// 2016/11/14 Y.Uesugi		複合フリーワード検索 住所カナ検索対応
// 2016/11/21 T.Yoshino		グラクソ発毛様特注機能追加(香川県対応)
// 2017/03/13 K.Tani		地図中心マーク画像offset指定
// 2017/02/23 N.Wada		出発地指定複合ルートの移動手段にバス利用有無
// 2017/03/06 N.Wada		出発地複合検索用パラメータを追加
// 2017/04/14 Y.Matsukawa	Google POI（お店）表示
// 2017/04/21 H.Yasunaga	ローソンキャンペーン対応カスタマイズ
// 2017/05/11 H.Yasunaga	ヤマトロッカーセキュリティコード対応
// 2017/05/30 H.Yasunaga	ヤマトロッカーセキュリティコード対応
// 2017/06/06 Y.Matsukawa	Google POI（お店）詳細カテゴリー設定
// ------------------------------------------------------------

//言語切り替え		add 2016/03/10 Y.Matsukawa
if(!isset($D_LANG)) $D_LANG = '';

//レスポンスヘッダcharset出力		add 2015/11/11 Y.Matsukawa
if(!isset($D_RESPONSE_CHARSET)) $D_RESPONSE_CHARSET = 0;

//サービス内容
if(!isset($D_SERVICE_TYPE)) $D_SERVICE_TYPE ="S";//S:standard L:light N:maplink

//Google Maps版		add 2013/06/13 Y.Matsukawa
if(!isset($D_GOOGLEMAPS)) $D_GOOGLEMAPS = 0;	// Google Maps版
if(!isset($D_GOOGLEMAPS_ICON_CUSTOM)) $D_GOOGLEMAPS_ICON_CUSTOM = 0;	// 0：Googleデフォルトマーカー／1：拠点アイコン		add 2015/06/08 N.Wada
if(!isset($D_GOOGLEMAPS_SEARCH_EVENT_IDLE)) $D_GOOGLEMAPS_SEARCH_EVENT_IDLE = 0;	// 0：center_changedとzoom_changedイベント／1：idleイベント		add 2015/10/20 N.Wada

//Google Maps版POIアイコン	add 2015/10/20 N.Wada
if(!isset($D_GOOGLEMAPS_POI_INVISIBLE)) $D_GOOGLEMAPS_POI_INVISIBLE = 0;	// POIアイコン非表示
if(!isset($D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE)) $D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE = 0;	// クリック時に吹き出しを表示しない
if(!isset($D_GOOGLEMAPS_POI_BUSINESS)) $D_GOOGLEMAPS_POI_BUSINESS = 0;	// POI（お店）表示
if(!isset($D_GOOGLEMAPS_POI_BUSINESS_DETAILS)) $D_GOOGLEMAPS_POI_BUSINESS_DETAILS = null;	// POI（お店）詳細カテゴリー設定
if(!isset($D_GOOGLEMAPS_POI_EXCLUDE_BUSINESS)) $D_GOOGLEMAPS_POI_EXCLUDE_BUSINESS = 0;	// POI（BUSINESS以外）表示

//Google Maps版マーカークラスター（要markerclustere.js）	add 2015/10/20 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER)) $D_GOOGLEMAPS_MARKER_CLUSTERER = 0;
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE = 0;	// クリック時のズーム無効
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG = 0;		// クリック時に吹き出しを表示
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE = 0;	// クラスタリングする範囲	add 2015/11/26 N.Wada

// 拠点が保持する世界測地系緯度経度を使用		add 2016/08/16 Y.Matsukawa
if(!isset($D_KYOTEN_WGS_COL)) $D_KYOTEN_WGS_COL = null;

//TOPページ
if(!isset($D_TOP_PAGE_KBN)) $D_TOP_PAGE_KBN = 0;/*2.0*/
if(!isset($D_HISTORY_TOP_LINK)) $D_HISTORY_TOP_LINK = $D_DIR_BASE_G;/*2.0*/

//カスタムエラー（設定ファイル内でこの変数にエラーメッセージがセットされると、エラー画面へ遷移します）	add 2011/12/20 Y.Matsukawa
if(!isset($D_CUST_ERRMSG)) $D_CUST_ERRMSG = '';

//JSAPIのロードなどでエラーが発生した場合の飛び先
if(!isset($D_URL_JSAPIERROR)) $D_URL_JSAPIERROR = "http://".$EMAP_SSAPI_SRV."/error/jsapierror.html";

//許可リファラー
if(!isset($D_ALLOW_REFERER)) $D_ALLOW_REFERER  = "*";
if(!isset($D_ALLOW_REFERER_NULL)) $D_ALLOW_REFERER_NULL  = 1;//空を許可するか否か 0:不可 1:許可
if(!isset($D_ALLOW_REFERER_PROTOCOL)) $D_ALLOW_REFERER_PROTOCOL = 1;//プロトコル（https/http） 0:区別しない 1:区別する		add 2011/12/21 Y.Matsukawa

//Basic認証
if(!isset($D_BASIC_AUTH["dev"])) $D_BASIC_AUTH["dev"] = 0;  //開発環境のBasic認証On/Off
if(!isset($D_BASIC_AUTH["test"])) $D_BASIC_AUTH["test"] = 0;//検証環境のBasic認証On/Off
if(!isset($D_BASIC_AUTH["www"])) $D_BASIC_AUTH["www"] = 0;  //本番環境のBasic認証On/Off

//Maplink住所接続
if(!isset($D_MAPLINK_ADDR_IF)) $D_MAPLINK_ADDR_IF = 0;

//Standard住所接続
if(!isset($D_STANDARD_ADDR_IF)) $D_STANDARD_ADDR_IF = 0;

//地図の初期位置
if(!isset($D_INIT_LAT)) $D_INIT_LAT = 128456476;
if(!isset($D_INIT_LON)) $D_INIT_LON = 503030954;

//初期ズーム
if(!isset($D_INIT_LVL)) $D_INIT_LVL        = 1;//初期表示
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH = -1;//位置検索決定後（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = -1;//詳細選択後（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
if(!isset($D_INIT_LVL_PRINT)) $D_INIT_LVL_PRINT   = -1;//印刷画面（-1：$D_INIT_LVLに準じる）

// del 2016/04/21 H.Osamoto [
//	//アイコンを表示する最大最小縮尺
//	if(!isset($D_VIEW_ICON_MAX)) $D_VIEW_ICON_MAX = 4;
//	if(!isset($D_VIEW_ICON_MIN)) $D_VIEW_ICON_MIN = 18;
// del 2016/04/21 H.Osamoto ]

//最大最小縮尺
if(!isset($D_MAP_SCALE_MAX)) $D_MAP_SCALE_MAX = 0;
if(!isset($D_MAP_SCALE_MIN)) $D_MAP_SCALE_MIN = 18;

//表示縮尺範囲	add 2014/09/08 H.Osamoto
if(!isset($D_MAP_ZOOM_RANGE)) $D_MAP_ZOOM_RANGE = '';

//指定拠点以外非表示区分
if(!isset($D_DSP_OTHER_KBN)) $D_DSP_OTHER_KBN = 0;

//地図移動方法 シングルクリックとかダブルクリックとか？
if(!isset($D_MAP_CLICK_KBN)) $D_MAP_CLICK_KBN = 0;

//ホイールスクロールによるズーム 0:無し 1:有り
if(!isset($D_MAP_WHEEL_KBN)) $D_MAP_WHEEL_KBN = 0;


//拠点アイコン上での動作
if(!isset($D_KYO_ICON_MO)) $D_KYO_ICON_MO = 0;
if(!isset($D_KYO_ICON_CLK)) $D_KYO_ICON_CLK = 1;
if(!isset($D_KYO_ICON_MOUT)) $D_KYO_ICON_MOUT = 0;	// マウスアウト（1：吹き出しを消す）



// 位置検索系 ----------------------------------------------
//住所リスト・駅リストでのかな絞込みの有無 0:無し 1:有り
if(!isset($D_SEARCH_KANA)) $D_SEARCH_KANA = 0;

//住所リストをどの階層まで掘り下げるか（1：都道府県、2：市区町村、3：大字、4：字丁目、5：街区、7：（最下層）※2.0
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 7;

//住所リスト検索
if(!isset($D_SEARCH_ADDR_LIST_AREA)) $D_SEARCH_ADDR_LIST_AREA = 0;											// エリア検索 add 2015/10/20 N.Wada
if(!isset($D_SEARCH_ADDR_LIST_OUTPUT_ALL)) $D_SEARCH_ADDR_LIST_OUTPUT_ALL = 0;								// 全件表示 add 2015/10/20 N.Wada
if(!isset($D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP)) $D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP = 0;				// かな行別出力 add 2015/10/20 N.Wada
if(!isset($D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP_ADD_23)) $D_SEARCH_ADDR_LIST_OUTPUT_KANA_GROUP_ADD_23 = 0;	// かな行別に23区行を追加 add 2015/10/20 N.Wada

//住所リスト検索(SEO対策)
if(!isset($D_SEARCH_ADDR_LIST_SEO)) $D_SEARCH_ADDR_LIST_SEO = 0;											// エリア検索 add 2016/0928 Y.Uesugi

//最大検索ページ数
if(!isset($D_SEARCH_MAXPAGE["AddrW"])) $D_SEARCH_MAXPAGE["AddrW"] = 9;
if(!isset($D_SEARCH_MAXPAGE["StW"])) $D_SEARCH_MAXPAGE["StW"]   = 9;
if(!isset($D_SEARCH_MAXPAGE["ShopW"])) $D_SEARCH_MAXPAGE["ShopW"] = 9;
if(!isset($D_SEARCH_MAXPAGE["ShopM"])) $D_SEARCH_MAXPAGE["ShopM"] = 9;		// add 2013/09/24 Y.Matsukawa

//フリーワードでの全文・部分一致
if(!isset($D_SEARCH_SRCHMODE_STW)) $D_SEARCH_SRCHMODE_STW = 0;

//複合検索※2.0
if(!isset($D_COMB_FW_ZIP))  $D_COMB_FW_ZIP  = 1;	//郵便番号フリーワード
if(!isset($D_COMB_FW_ADDR)) $D_COMB_FW_ADDR = 1;	//住所フリーワード
if(!isset($D_COMB_FW_ADDR_KANA)) $D_COMB_FW_ADDR_KANA = 0;	//住所フリーワード(カナ)	add 2016/11/14 Y.Uesugi
if(!isset($D_COMB_FW_ST))   $D_COMB_FW_ST   = 1;	//駅フリーワード
if(!isset($D_COMB_FW_POI))  $D_COMB_FW_POI  = 0;	//施設フリーワード
if(!isset($D_COMB_FW_SHOP)) $D_COMB_FW_SHOP = 1;	//拠点フリーワード
//複合検索表示件数
if(!isset($D_COMB_FW_ZIP_MAX))  $D_COMB_FW_ZIP_MAX  = 5;	//郵便番号フリーワード
if(!isset($D_COMB_FW_ADDR_MAX)) $D_COMB_FW_ADDR_MAX = 5;	//住所フリーワード
if(!isset($D_COMB_FW_ST_MAX))   $D_COMB_FW_ST_MAX   = 5;	//駅フリーワード
if(!isset($D_COMB_FW_POI_MAX))  $D_COMB_FW_POI_MAX  = 5;	//施設フリーワード
if(!isset($D_COMB_FW_SHOP_MAX)) $D_COMB_FW_SHOP_MAX = 5;	//拠点フリーワード

//出発地複合検索※2.0		add 2017/03/06 N.Wada
if(!isset($D_DEPT_FW_ZIP))  $D_DEPT_FW_ZIP  = 1;	//郵便番号フリーワード
if(!isset($D_DEPT_FW_ADDR)) $D_DEPT_FW_ADDR = 1;	//住所フリーワード
if(!isset($D_DEPT_FW_ST))   $D_DEPT_FW_ST   = 1;	//駅フリーワード
if(!isset($D_DEPT_FW_POI))  $D_DEPT_FW_POI  = 0;	//施設フリーワード
if(!isset($D_DEPT_FW_SHOP)) $D_DEPT_FW_SHOP = 1;	//拠点フリーワード
//出発地複合検索表示件数	add 2017/03/06 N.Wada
if(!isset($D_DEPT_FW_ZIP_MAX))  $D_DEPT_FW_ZIP_MAX  = 5;	//郵便番号フリーワード
if(!isset($D_DEPT_FW_ADDR_MAX)) $D_DEPT_FW_ADDR_MAX = 5;	//住所フリーワード
if(!isset($D_DEPT_FW_ST_MAX))   $D_DEPT_FW_ST_MAX   = 5;	//駅フリーワード
if(!isset($D_DEPT_FW_POI_MAX))  $D_DEPT_FW_POI_MAX  = 5;	//施設フリーワード
if(!isset($D_DEPT_FW_SHOP_MAX)) $D_DEPT_FW_SHOP_MAX = 5;	//拠点フリーワード

//住所あいまい検索 あいまい検索しない:F
if(!isset($D_COMB_FW_ADDR_KANA_AMB)) $D_COMB_FW_ADDR_KANA_AMB = 'T';	//住所フリーワード(カナ)	add 2016/11/14 Y.Uesugi

// 郵便番号検索0件時に検索TOP遷移（ヤマト運輸カスタマイズ）		add 2013/07/22 Y.Matsukawa
if(!isset($D_ZIPW0_GOTO_PAGE)) $D_ZIPW0_GOTO_PAGE = '';

// 任意の列数で一覧表示		add 2013/08/09 Y.Matsukawa
if(!isset($D_LIST_COLS['ZipW'])) $D_LIST_COLS['ZipW'] = 1;

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
//施設フリーワード・施設リストでジャンルメニューを選択
if(!isset($D_SEARCH_POI_JNRMN_SELECT)) $D_SEARCH_POI_JNRMN_SELECT = 0;	// add 2016/11/14 N.Wada

//検索位置にマーカー表示		add 2014/11/28 Y.Matsukawa
if(!isset($D_SEARCH_MAP_ICON))      $D_SEARCH_MAP_ICON = 0;			// 最寄り地図に検索位置マーカーを表示
if(!isset($D_SEARCH_MAP_ICON_DTL))  $D_SEARCH_MAP_ICON_DTL = 0;		// 店舗地図に検索位置マーカーを表示
if(!isset($D_SEARCH_MAP_CENTER))    $D_SEARCH_MAP_CENTER = 0;		// 店舗地図を検索位置中心で表示
if(!isset($D_SEARCH_MAP_ICON_IMG))  $D_SEARCH_MAP_ICON_IMG = '';	// マーカー画像URL
if(!isset($D_SEARCH_MAP_ICON_W))    $D_SEARCH_MAP_ICON_W = 0;		// マーカー画像width
if(!isset($D_SEARCH_MAP_ICON_H))    $D_SEARCH_MAP_ICON_H = 0;		// マーカー画像height
if(!isset($D_SEARCH_MAP_ICON_OFX))  $D_SEARCH_MAP_ICON_OFX = 0;		// マーカー画像横offset
if(!isset($D_SEARCH_MAP_ICON_OFY))  $D_SEARCH_MAP_ICON_OFY = 0;		// マーカー画像縦offset

//地図中心マーク		add 2016/01/08 Y.Uesugi
if(!isset($D_MAPCENTER_MARK_IMG))  $D_MAPCENTER_MARK_IMG = '';		// 中心マーク画像URL

//地図中心マーク画像offset	add 2017/03/13 K.Tani
if(!isset($D_MAPCENTER_MARK_IMG_OFX))  $D_MAPCENTER_MARK_IMG_OFX = 0;		// 地図中心マーク画像 横offset
if(!isset($D_MAPCENTER_MARK_IMG_OFY))  $D_MAPCENTER_MARK_IMG_OFY = 0;		// 地図中心マーク画像 縦offset

// 拠点検索系 ----------------------------------------------
//最寄拠点 -------------------
//１ページの量
if(!isset($D_SHOP_PAGE)) $D_SHOP_PAGE = 10;//リストのみ
if(!isset($D_SHOP_PAGE_DETAIL)) $D_SHOP_PAGE_DETAIL = 3;//詳細表示時
if(!isset($D_NSHOPLIST_EXT)) $D_NSHOPLIST_EXT = 0;//再検索時、地図表示範囲外も検索対象とする		add 2014/06/06 Y.Matsukawa
//最小件数
//	if(!isset($D_SHOP_MIN)) $D_SHOP_MIN= 0;	//add 2015/09/30 Y.Uesugi	// mod 2016/03/17 H.Osamoto
if(!isset($D_SHOP_MIN)) $D_SHOP_MIN= 1;
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
//if(!isset($D_SHOP_LIST_NO_DTLSHOP)) $D_SHOP_LIST_NO_DTLSHOP = 0;		del 2012/01/10 Y.Matsukawa
//地図操作で最寄り再検索しない		add 2011/12/20 Y.Matsukawa
if(!isset($D_SHOP_NO_SEARCH_USER_ACT)) $D_SHOP_NO_SEARCH_USER_ACT = 0;
//店舗詳細取得時にcond絞り込みを有効にする		add 2012/03/08 Y.Matsukawa
if(!isset($D_USE_COND_DETAIL)) $D_USE_COND_DETAIL = 0;
//全件一覧
if(!isset($D_KLIST_PAGING)) $D_KLIST_PAGING = 0;	//ページング有無	add 2012/05/11 Y.Matsukawa
if(!isset($D_KLIST_PAGE)) $D_KLIST_PAGE = 10;		//１ページ行数		add 2012/05/11 Y.Matsukawa
//エリア検索のソート桁あわせ		add // 2015/01/26 Y.Matsukawa	ソート時に０埋めして桁あわせ
if(!isset($D_AREA_SORT_LPAD)) $D_AREA_SORT_LPAD = array();
//エリア検索NULLの場合の表示文言		add 2015/05/07 Y.Matsukawa
if(!isset($D_SEARCH_SHOPA_DISPNM_NULL)) $D_SEARCH_SHOPA_DISPNM_NULL = "(その他)";
//店舗一覧ソート順指定		add 2015/05/08 Y.Matsukawa
if(!isset($D_SHOPW_KYOTEN_SORT)) $D_SHOPW_KYOTEN_SORT = "";//店舗フリーワード検索
if(!isset($D_SHOPA_KYOTEN_SORT)) $D_SHOPA_KYOTEN_SORT = "";//エリア検索
//condをnmap/shop_dtlに直接記述（cond.htm未使用）		add 2015/05/14 Y.Matsukawa
if(!isset($D_COND_STATIC)) $D_COND_STATIC = 0;
// 最寄り検索後、１番目の店舗のフキダシを表示する		add 2015/06/08 N.Wada
if(!isset($D_SEARCH_FINISHED_MSG_SHOW)) $D_SEARCH_FINISHED_MSG_SHOW = 0;
// フキダシ表示中に再検索した際、検索後にフキダシを出し直す		add 2016/03/14 Y.Matsukawa
if(!isset($D_REFRESH_FUKIDASHI_SEARCH_COMPLETE)) $D_REFRESH_FUKIDASHI_SEARCH_COMPLETE = 0;

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
//周辺駅からの円描画半径		add 2014/10/08 Y.Matsukawa
if(!isset($D_STT_CIRCLE_RAD)) $D_STT_CIRCLE_RAD = 1000;	//半径
if(!isset($D_STT_CIRCLE_INFO['strokeColor'])) $D_STT_CIRCLE_INFO['strokeColor'] = '#3366FF';	//線の色
if(!isset($D_STT_CIRCLE_INFO['strokeWeight'])) $D_STT_CIRCLE_INFO['strokeWeight'] = 1;	//線の太さ
if(!isset($D_STT_CIRCLE_INFO['fillColor'])) $D_STT_CIRCLE_INFO['fillColor'] = '#D4E7FB';	//塗りつぶしの色
if(!isset($D_STT_CIRCLE_INFO['fillOpacity'])) $D_STT_CIRCLE_INFO['fillOpacity'] = 0.5;	//塗りつぶしの透過度
if(!isset($D_STT_CIRCLE_INFO['lineStyle'])) $D_STT_CIRCLE_INFO['lineStyle'] = 'solid';	//線の種類
if(!isset($D_STT_CIRCLE_INFO['lineOpacity'])) $D_STT_CIRCLE_INFO['lineOpacity'] = 1.0;	//線の透過度


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
if(!isset($D_ROUTE_EKI_EXIT)) $D_ROUTE_EKI_EXIT = 0;//駅出口考慮		add 2012/08/17 Y.Matsukawa
if(!isset($D_ROUTE_DISTANCE_DSP_MAP)) $D_ROUTE_DISTANCE_DSP_MAP = '';// 地図上への移動距離・時間表示フラグ		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_LINE_TOLL_FALSE)) $D_ROUTE_LINE_TOLL_FALSE = 0;	//有料道路をルート検索対象外とする		add 2016/08/25 Y.Uesugi
if(!isset($D_ROUTE_LINE_PROPERTY_DSP_MAP_WALK)) $D_ROUTE_LINE_PROPERTY_DSP_MAP_WALK = 0;	//マーカを表示（徒歩）		add 2016/08/25 Y.Uesugi
if(!isset($D_ROUTE_LINE_PROPERTY_DSP_MAP_DRIVE)) $D_ROUTE_LINE_PROPERTY_DSP_MAP_DRIVE = 0;	//マーカを表示（自動車）		add 2016/08/25 Y.Uesugi
if(!isset($D_ROUTE_DISTANCE_DSP_STYLE)) $D_ROUTE_DISTANCE_DSP_STYLE = '';// 地図上への移動距離・時間表示用スタイル設定		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_W)) $D_ROUTE_DISTANCE_DSP_W = '';// 地図上への移動距離・時間の表示サイズ（幅）		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_H)) $D_ROUTE_DISTANCE_DSP_H = '';// 地図上への移動距離・時間の表示サイズ（高さ）	add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_X)) $D_ROUTE_DISTANCE_DSP_X = '';// 地図上への移動距離・時間の表示位置（X方向）		add 2015/04/09 F.Yokoi
if(!isset($D_ROUTE_DISTANCE_DSP_Y)) $D_ROUTE_DISTANCE_DSP_Y = '';// 地図上への移動距離・時間の表示位置（Y方向）		add 2015/04/09 F.Yokoi
if(!isset($D_SEARCH_COMB_ROUTE_USE_BUS)) $D_SEARCH_COMB_ROUTE_USE_BUS = 0;//出発地指定複合ルート（0：バスを使わない、1：バスを使う）	add 2017/02/23 N.Wada


//Cookie保存 ----------------------------------------------
// 閲覧履歴（複数）を保存）
if(!isset($D_COOKIE_SHOPDTL_AUTOSAVE)) $D_COOKIE_SHOPDTL_AUTOSAVE = 0;		//拠点詳細表示時に自動保存		add 2014/12/09 Y.Matsukawa
if(!isset($D_COOKIE_SHOPDTL_MAX)) $D_COOKIE_SHOPDTL_MAX = 0;		//拠点詳細保存件数
if(!isset($D_COOKIE_SHOPDTL_EXPIRE)) $D_COOKIE_SHOPDTL_EXPIRE = 365;	//拠点詳細保存期限（日数）
if(!isset($D_COOKIE_SHOPDTL_CGI)) $D_COOKIE_SHOPDTL_CGI = '';
if(!isset($D_COOKIE_SHOPDTL_KEY_ADD)) $D_COOKIE_SHOPDTL_KEY_ADD = '';	//拠点詳細保存キーに任意の文字列追加	add 2016/05/13 N.Wada
// add 2012/02/27 Y.Matsukawa [
// 最後に閲覧した１拠点を保存
if(!isset($D_COOKIE_KID)) $D_COOKIE_KID = 0;					//拠点ID保存
if(!isset($D_COOKIE_KID_DIR)) $D_COOKIE_KID_DIR = "/p/";		//拠点ID保存ディレクトリ
if(!isset($D_COOKIE_KID_KEY)) $D_COOKIE_KID_KEY = "";			//拠点ID保存キー文字列
if(!isset($D_COOKIE_KID_EXPIRE)) $D_COOKIE_KID_EXPIRE = 365;	//拠点ID保存期限（日数）
if(!isset($D_COOKIE_KID_REDIRECT)) $D_COOKIE_KID_REDIRECT = 0;	//拠点ID保存時に詳細へリダイレクト
// add 2012/02/27 Y.Matsukawa ]
// パンくずを保存
if(!isset($D_COOKIE_HISTORY_KEY_ADD)) $D_COOKIE_HISTORY_KEY_ADD = '';	//パンくず保存キーに任意の文字列追加	add 2016/05/13 N.Wada
$D_P3P_HEADER = 'NOI CUR OUR';			// P3Pコンパクトポリシー	add 2012/06/20 N.Wada
// ===IEで別ドメインのiframeを読み込んでも、そのiframe内のcookieが有効になる=== 

//拠点ID不正の場合にTOPへリダイレクト		add 2012/02/27 Y.Matsukawa
if(!isset($D_KID_NF_REDIRECT)) $D_KID_NF_REDIRECT = 0;

//郵便番号検索へリダイレクト		add 2012/02/29 Y.Matsukawa
if(!isset($D_REDIRECT_TO_ZIPW)) $D_REDIRECT_TO_ZIPW = 0;
if(!isset($REDIRECT_ZIPW_KW)) $REDIRECT_ZIPW_KW = '';

//郵便番号検索一覧スキップ（最寄り地図へ直接遷移）		add 2014/07/07 Y.Matsukawa
if(!isset($D_ZIPW_SKIP_LIST)) $D_ZIPW_SKIP_LIST = 0;

//スマホリダイレクト		add 2012/03/12 Y.Matsukawa
if(!isset($D_REDIRECT_SMT_KID)) $D_REDIRECT_SMT_KID = '';			// 拠点ID接続 'inf' or 'map'
if(!isset($D_REDIRECT_SMT_ADDR_FW)) $D_REDIRECT_SMT_ADDR_FW = 0;	// 住所フリーワード接続
if(!isset($D_REDIRECT_SMT_EKI_FW)) $D_REDIRECT_SMT_EKI_FW = 0;		// 駅フリーワード接続
if(!isset($D_REDIRECT_SMT_ZIP_FW)) $D_REDIRECT_SMT_ZIP_FW = 0;		// 郵便番号接続

//スマホリダイレクト（top.location変更）		add 2015/08/25 Y.Matsukawa
if(!isset($CUST_JUMP_LOCATION)) $CUST_JUMP_LOCATION = '';		// 遷移先URL


//携帯URL ----------------------------------------------
if(!isset($D_MBURL_EX)) $D_MBURL_EX = '';		//携帯URLに付加するURLパラメータ文字列		add 2012/01/06 Y.Matsukawa

// 任意カラムのアイコンIDを使用		add 2012/04/16 Y.Matsukawa
if(!isset($D_ICONID_COL)) $D_ICONID_COL = '';	// アイコンIDを格納しているカラム名（例）'col_01' ※カラム定義で「リスト表示」「PC詳細」「印刷画面」選択が必要です

// 拠点データ取得時のカスタマイズ仕様		add 2012/11/13 Y.Matsukawa
if(!isset($D_NKYOTEN_CUST)) $D_NKYOTEN_CUST = '';			// 最寄拠点
if(!isset($D_KYOTENID_CUST)) $D_KYOTENID_CUST = '';			// 拠点ID
if(!isset($D_KYOTENLIST_CUST)) $D_KYOTENLIST_CUST = '';		// 拠点検索

// JCN様向けカスタマイズ（運休情報表示）		add 2012/11/13 Y.Matsukawa
if(!isset($D_JCN_UNKYU_TOP)) $D_JCN_UNKYU_TOP = 0;			// 運休情報表示
if(!isset($D_JCN_UNKYU_JKN)) $D_JCN_UNKYU_JKN = '';			// 運休情報表示条件

// 拠点縮尺カラム		add 2012/11/27 Y.Matsukawa
if(!isset($D_KYOTENLVL_COL_P)) $D_KYOTENLVL_COL_P = '';

// 数字アイコン		add 2013/04/19 H.Osamoto
if(!isset($D_NUM_ICON_GIF)) $D_NUM_ICON_GIF = $D_DIR_BASE_G.'img/icon_num/icon_num_';

// 初期表示縮尺		add 2013/05/14 H.Osamoto
if(!isset($D_INIT_LVL_CSTM)) $D_INIT_LVL_CSTM = 0;

//再検索
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;	//最寄検索結果が0件の場合再検索で取得する件数指定		add 2013/05/22 H.Osamoto

// ヤマト運輸 営業所検索利用		add 2015/10/23 Y.Uesugi
if(!isset($D_YTC_GET_JIGYOCD['INF'])) $D_YTC_GET_JIGYOCD['INF'] = 0;//詳細画面

// 住所FW検索結果一覧の遷移先を住所リスト検索にする		add 2013/09/19 H.Osamoto
if(!isset($D_ADDR_FW_TO_LIST)) $D_ADDR_FW_TO_LIST = 0;

// 住所FW検索結果が1件だった場合に一覧画面をスキップする		add 2013/09/19 H.Osamoto
if(!isset($D_ADDR_FW_MONO_RESULT_REDIRECT)) $D_ADDR_FW_MONO_RESULT_REDIRECT = 0;

// 拠点FW検索結果一覧の遷移先を最寄り地図にする		add 2015/10/20 N.Wada
if(!isset($D_SHOP_FW_TO_NMAP)) $D_SHOP_FW_TO_NMAP = 0;

// ポリゴン内外判定カラム		add 2014/02/21 H.Osamoto
if(!isset($D_POLY_COL)) $D_POLY_COL = '';

// 商品マスタ使用		add 2014/05/16 Y.Matsukawa
if(!isset($D_PRD)) $D_PRD = 0;

//add 2014/08/18 Q.Dai
if(!isset($D_KYO_ICON_OVERLAP)) $D_KYO_ICON_OVERLAP = ''; //Variable set icon on map overlapped.
//add 2014/08/29 Q.Dai
if(!isset($D_KYO_ICON_OVERLAP_ICON_ID)) $D_KYO_ICON_OVERLAP_ICON_ID = ''; // 重複アイコンID		add 2015/03/18 N.Wada

// 最寄り地図に住所文字列接続した際のパンくずを緯度経度接続に変換したURLにする		add 2014/12/11 Y.Matsukawa
if(!isset($D_HIS_NMAP_ADDRIF2LLIF)) $D_HIS_NMAP_ADDRIF2LLIF = 0;
// 最寄り地図に住所文字列接続した際のパンくずに住所文字列を表示する		add 2015/01/26 Y.Matsukawa
if(!isset($D_HIS_NMAP_ADDRIF_SHOWADDR)) $D_HIS_NMAP_ADDRIF_SHOWADDR = 0;

// セブン&アイOMNI用ロジック		add 2015/05/01 Y.Matsukawa
if(!isset($D_711OMNI_INIT_JKN)) $D_711OMNI_INIT_JKN = "";	// 最寄り初期検索の条件
if(!isset($D_711OMNI_INIT_RAD)) $D_711OMNI_INIT_RAD = 0;	// 最寄り初期検索の範囲(m)
if(!isset($D_711OMNI_ALT_RAD)) $D_711OMNI_ALT_RAD = 0;		// 最寄り既定検索範囲(m)

// Ajax化		add 2015/06/08 N.Wada
if(!isset($D_SEARCH_RESULT_AJAX)) $D_SEARCH_RESULT_AJAX = 0;	// 検索一覧（search.htm）をAjax表示する
if(!isset($D_SEARCH_RESULT_TEMPLATE_ONLY)) $D_SEARCH_RESULT_TEMPLATE_ONLY = 0;	// 検索一覧（search.htm）テンプレートをHTMLの一部分として表示（Ajax表示対応）
if(!isset($D_SEARCH_ERROR_TEMPLATE_ONLY)) $D_SEARCH_ERROR_TEMPLATE_ONLY = 0;	// 検索エラー（search_error.htm）テンプレートをHTMLの一部分として表示（Ajax表示対応）	add 2015/10/20 N.Wada
if(!isset($D_DETAIL_AJAX)) $D_DETAIL_AJAX = 0;	// 拠点詳細（shop_dtl.htm）をAjax表示する
if(!isset($D_DETAIL_TEMPLATE_ONLY)) $D_DETAIL_TEMPLATE_ONLY = 0;	// 拠点詳細（shop_dtl.htm）テンプレートをHTMLの一部分として表示（Ajax表示対応）

// リダイレクト		add 2015/08/17 Y.Matsukawa
if(!isset($D_IPHONE_REDIRECT_SMT))  $D_IPHONE_REDIRECT_SMT = 0;
if(!isset($D_IPAD_REDIRECT_SMT))    $D_IPAD_REDIRECT_SMT = 0;
if(!isset($D_ANDROID_REDIRECT_SMT)) $D_ANDROID_REDIRECT_SMT = 0;

// 711mapニッセン向けロジック		add 2016/01/26 H.Osamoto
if(!isset($D_711NISSEN_FIX_ZOOM)) $D_711NISSEN_FIX_ZOOM = "";

// 現在検索エラー時の遷移先		add 2016/04/26 N.Wada
if(!isset($D_LOC_ERR_URL)) $D_LOC_ERR_URL = '';	// loc.htm

// 日本郵政版郵便番号検索		add 2016/06/14 Y.Matsukawa
if(!isset($D_JPPOST_SEARCH_ZIP)) $D_JPPOST_SEARCH_ZIP = 0;

// 詳細エラー時のリダイレクト先URL		add 2016/06/30 N.Wada
if(!isset($D_KID_NOTFOUND_REDIRECT_URL)) $D_KID_NOTFOUND_REDIRECT_URL = "";

// 住所リスト緯度経度指定	add 2016/11/21 T.Yoshino
if(!isset($D_LIST_ADDR_CODE))	 $D_LIST_ADDR_CODE	 = array();
if(!isset($D_LIST_ADDR_NAME))	 $D_LIST_ADDR_NAME	 = array();
if(!isset($D_LIST_ADDR_LAT))	 $D_LIST_ADDR_LAT	 = array();
if(!isset($D_LIST_ADDR_LON))	 $D_LIST_ADDR_LON	 = array();

// 住所リスト緯度経度指定(FW検索)	add 2016/11/21 T.Yoshino
if(!isset($D_LIST_ADDR_CUST))	 $D_LIST_ADDR_CUST	 = array();

// ローソンキャンペーン対応カスタマイズ	add 2017/04/21 H.Yasunaga
if (!isset($D_LOWSON_CAM_CUST))	$D_LOWSON_CAM_CUST = 0;

// ヤマト ロッカーセキュリティコード対応 add 2017/05/11 H.Yasunaga
if (!isset($D_YTC_SECURITY_CODE)) $D_YTC_SECURITY_CODE = 0;

// ヤマト ロッカーセキュリティコード対応 直接詳細画面に遷移しない add 2017/05/30 H.Yasunaga
if (!isset($D_YTC_SECURITY_CODE_NO_DIRECT_DTL)) $D_YTC_SECURITY_CODE_NO_DIRECT_DTL = 0;
?>
