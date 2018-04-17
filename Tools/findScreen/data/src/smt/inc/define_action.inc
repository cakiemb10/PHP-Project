<?php
// ------------------------------------------------------------
// 定義ファイル 動作に関する項目
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/05/23 Y.Matsukawa	テンプレート生成対応
// 2011/07/13 Y.Matsukawa	機能追加（ルート探索、最寄駅）
// 2011/08/08 Y.Matsukawa	機能追加（絞り込み拡張、拠点エリア検索、駅リスト検索）
// 2012/01/10 N.Wada		地図操作時に再検索しないモード
// 2012/01/10 N.Wada		テンプレート設定ファイル内でエラーメッセージがセットされたらエラー画面表示
// 2012/01/10 N.Wada		リファラチェック時、https/httpを区別しないモード
// 2012/01/10 N.Wada		Standard住所接続
// 2012/01/24 Y.Matsukawa	任意パラメータを引き継がないモード
// 2012/03/23 SKC			Maplink住所接続対応
// 2012/04/24 Y.Matsukawa	施設リスト検索
// 2012/05/14 Y.Matsukawa	全件一覧ページング
// 2012/05/23 Y.Matsukawa	機能追加：位置検索後、最寄一覧ではなく、最寄地図へ遷移するモード
// 2012/07/18 Y.Matsukawa	最寄施設
// 2012/10/10 H.Osamoto		任意カラムのアイコンIDを使用
// 2012/11/15 Y.Matsukawa	JCN満空情報取得
// 2012/12/03 Y.Matsukawa	場所検索からTOPへ戻る際にアンカー移動
// 2012/12/17 H.Osamoto		神奈川電通広告向けカスタマイズ
// 2013/01/31 H.Osamoto		距離表示変換機能追加
// 2013/04/15 H.Osamoto		最寄検索結果が0件の場合再検索で取得する件数指定機能追加
// 2013/05/30 Y.Matsukawa	住所リスト：adcd複数都道府県指定
// 2013/07/10 Y.Matsukawa	ヤマト運輸向けカスタマイズ（CGI呼び出し）
// 2013/07/19 Y.Matsukawa	住所リストの最下位階層を指定可能にする
// 2013/07/29 Y.Matsukawa	ヒット件数が多い場合エラーにする
// 2014/03/07 H.Osamoto		ポリゴン内外判定カラム追加
// 2014/07/08 Y.Matsukawa	郵便番号検索：一覧スキップ（最寄り一覧へ直接遷移）
// 2014/08/18 AnPham		SiteIconOverlapping
// 2014/08/26 AnPham		BrowsingHistoryDisplay
// 2014/12/18 Y.Matsukawa	【ヤマト運輸】【特定機種不具合対応】外部から地図ページを開くと画面サイズ取得に失敗する
// 2015/01/13 Y.Matsukawa	路線リスト検索 前へ戻るリンク
// 2015/01/26 Y.Matsukawa	ソート項目の桁あわせ
// 2015/02/02 Y.Matsukawa	jQueryの読み込み停止
// 2015/03/17 Y.Matsukawa	店舗ありの場合にnmapへリダイレクト
// 2015/04/03 H.Osamoto		最寄地図表示時のディレイ設定を追加
// 2015/09/29 H.Osamoto		地図表示時のディレイ設定の初期値を変更(0⇒500) iOS9対応
// 2015/10/30 N.Wada		Google Maps版対応
//							Google Maps版POIアイコン制御追加
//							Google Maps版マーカークラスター制御追加
//							拠点FW検索結果一覧の遷移先制御追加
//							【ドコモiD】地図サイズ設定を別jsで行うので無効化
// 							再検索時に初期絞込条件を使わないようにする機能の追加
// 2015/11/18 Xuan Chien	GPSログ出力対応
// 2015/11/26 N.Wada		Google Maps版マーカークラスターのクラスタリングする範囲追加
// 2016/01/20 N.Wada		現在地取得（接続I/F用画面）で最寄り画面へ遷移するモード
// 2016/01/26 H.Osamoto		711mapニッセン向けカスタマイズ
// 2016/02/15 N.Wada		拠点詳細地図表示の拠点データ取得時に拠点ログを出力する
// 2016/02/22 Y.Matsukawa	最寄地図に最寄一覧表示
// 2016/03/03 Y.Matsukawa	最寄一覧：任意カラムでグルーピング
// 2016/03/03 N.Wada		検索位置にマーカー表示
// 2016/03/06 N.Wada		店舗検索最小件数追加
// 2016/03/15 Y.Matsukawa	現在地取得エラー時の遷移先指定
// 2016/04/08 Y.Matsukawa	最寄り一覧と地図の最大件数を個別指定
// 2016/04/26 N.Wada		現在地取得エラー時の遷移先に任意パラメータ(freeparms)を引継ぐ
// 2016/06/22 Y.Matsukawa	グルーピング2ページ目以降の件数を別設定
// 2016/09/28 Y.Matsukawa	POST遷移
// 2016/11/10 Y.Uesugi		Google Maps APIキー設定
// 2016/11/21 T.Yoshino		グラクソ発毛様特注機能追加(香川県対応)
// 2017/01/17 N.Wada		ルート検索時のFW検索に店舗詳細情報取得＆一覧のリンク先を複合ルート検索に切り替える
// 2017/01/18 N.Wada		出発地指定複合ルートの移動手段にバス利用有無
// 2017/01/19 N.Wada		世界測地系保持
// 2017/02/02 K.Tani		711apl用カスタマイズ 800m、5km、1件あるまで対応
// 2017/02/03 K.Tani		711apl用カスタマイズ 初期表示の地図範囲を保持
//							地図スクロール時に最寄りリストを更新しない
// 2017/03/14 K.Tani		画面サイズ変更時の地図リサイズを行わない
// 2017/04/14 H.Yasunaga	日本郵便向けカスタマイズ
// 2017/04/14 N.Wada		最寄り一覧・拠点フリーワード検索に独自パラメータ追加
// 2017/04/21 N.Wada		路線名FW検索の１ページ当たりの件数、最大件数追加
// 2017/04/21 H.Yasunaga	ローソンキャンペーン対応カスタマイズ
// 2017/04/27 Y.Matsukawa	Google POI（お店）表示
// 2017/05/14 Y.Matsukawa	XSS対策
// 2017/05/11 H.Yasunaga	ヤマトロッカーセキュリティコード対応
// ------------------------------------------------------------
// 初期動作/サイト接続 -------------------------------------
//サービス内容
if(!isset($D_SERVICE_TYPE)) $D_SERVICE_TYPE ="S";//S:standard L:light N:maplink

//レスポンスヘッダcharset出力		add 2017/05/14 Y.Matsukawa
if(!isset($D_RESPONSE_CHARSET)) $D_RESPONSE_CHARSET = 0;

// POST遷移		add 2016/09/28 Y.Matsukawa
if(!isset($D_POST_MODE)) $D_POST_MODE = 0;

//Google Maps版		add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS)) $D_GOOGLEMAPS = 0;	// Google Maps版
if(!isset($D_GOOGLEMAPS_CID)) $D_GOOGLEMAPS_CID = 0;	// クライアントID
if(!isset($D_GOOGLEMAPS_JS)) $D_GOOGLEMAPS_JS = '';		// jsパス
if(!isset($D_GOOGLEMAPS_ICON_CUSTOM)) $D_GOOGLEMAPS_ICON_CUSTOM = 0;	// 0：Googleデフォルトマーカー／1：拠点アイコン
if(!isset($D_GOOGLEMAPS_WIN_SIZE_SET_DISABLE)) $D_GOOGLEMAPS_WIN_SIZE_SET_DISABLE = 0;		// 地図サイズの設定無効化

// add 2016/11/10 Y.Uesugi [
if(!isset($D_GOOGLEMAPS_API_KEY)) $D_GOOGLEMAPS_API_KEY = '';	// Google Maps API Key
if(!isset($D_GOOGLEMAPS_API_KEY_JS)) $D_GOOGLEMAPS_API_KEY_JS = '';		// jsパス
// add 2016/11/10 Y.Uesugi ]

//Google Maps版POIアイコン	add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS_POI_INVISIBLE)) $D_GOOGLEMAPS_POI_INVISIBLE = 0;	// POIアイコン非表示
if(!isset($D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE)) $D_GOOGLEMAPS_POI_CLICK_INFOWINDOW_DISABLE = 0;	// クリック時に吹き出しを表示しない
if(!isset($D_GOOGLEMAPS_POI_BUSINESS)) $D_GOOGLEMAPS_POI_BUSINESS = 0;	// POI（お店）表示

//Google Maps版マーカークラスター（要markerclustere.js）	add 2015/10/30 N.Wada
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER)) $D_GOOGLEMAPS_MARKER_CLUSTERER = 0;
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_ZOOM_FALSE = 0;	// クリック時のズーム無効
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG)) $D_GOOGLEMAPS_MARKER_CLUSTERER_CLICK_OPEN_MSG = 0;		// クリック時に吹き出しを表示
if(!isset($D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE)) $D_GOOGLEMAPS_MARKER_CLUSTERER_GLID_SIZE = 0;	// クラスタリングする範囲	add 2015/11/26 N.Wada

//カスタムエラー（設定ファイル内でこの変数にエラーメッセージがセットされると、エラー画面へ遷移します）	add 2012/01/10 N.Wada
if(!isset($D_CUST_ERRMSG)) $D_CUST_ERRMSG = '';

//許可リファラー
if(!isset($D_ALLOW_REFERER)) $D_ALLOW_REFERER  = "*";
if(!isset($D_ALLOW_REFERER_NULL)) $D_ALLOW_REFERER_NULL  = 1;//空を許可するか否か 0:不可 1:許可
if(!isset($D_ALLOW_REFERER_PROTOCOL)) $D_ALLOW_REFERER_PROTOCOL = 1;//プロトコル（https/http） 0:区別しない 1:区別する		add 2012/01/10 N.Wada

//Basic認証
if(!isset($D_BASIC_AUTH["dev"])) $D_BASIC_AUTH["dev"] = 0;  //開発環境のBasic認証On/Off
if(!isset($D_BASIC_AUTH["test"])) $D_BASIC_AUTH["test"] = 0;//検証環境のBasic認証On/Off
if(!isset($D_BASIC_AUTH["www"])) $D_BASIC_AUTH["www"] = 0;  //本番環境のBasic認証On/Off

//Standard住所接続	add 2012/01/10 N.Wada
if(!isset($D_STANDARD_ADDR_IF)) $D_STANDARD_ADDR_IF = 0;

//Maplink住所接続	add 2012/03/23 SKC
if(!isset($D_MAPLINK_ADDR_IF)) $D_MAPLINK_ADDR_IF = 0;

//初期ズーム
if(!isset($D_INIT_LVL)) $D_INIT_LVL = 7;//初期表示
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH =  7;//分布地図
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = 14;//店舗地図

//最大最小縮尺			add 2011/05/23 Y.Matsukawa
if(!isset($D_MAX_LVL)) $D_MAX_LVL = 1;
if(!isset($D_MIN_LVL)) $D_MIN_LVL = 15;

//地図表示ディレイ		add 2014/12/18 Y.Matsukawa
//	if(!isset($D_MAPINIT_DELAY_MS)) $D_MAPINIT_DELAY_MS = 0;//ミリ秒	mod 2015/09/29 H.Osamoto
if(!isset($D_MAPINIT_DELAY_MS)) $D_MAPINIT_DELAY_MS = 500;//ミリ秒

//最寄地図表示ディレイ		add 2015/04/03 H.Osamoto
//	if(!isset($D_NMAPINIT_DELAY_MS)) $D_NMAPINIT_DELAY_MS = 0;//ミリ秒	mod 2015/09/29 H.Osamoto
if(!isset($D_NMAPINIT_DELAY_MS)) $D_NMAPINIT_DELAY_MS = 500;//ミリ秒

//地図リサイズ時ディレイ		add 2016/03/28 Y.Matsukawa
if(!isset($D_MAP_RESIZE_DELAY_MS)) $D_MAP_RESIZE_DELAY_MS = 500;//ミリ秒

//画面サイズ変更時に地図リサイズしない		add 2017/03/14 K.Tani
if(!isset($D_MAP_NO_ORIENTATION_RESIZE_ANDROID)) $D_MAP_NO_ORIENTATION_RESIZE_ANDROID = 0;

//最寄地図(nmap.htm)に最寄一覧を表示		add 2016/02/22 Y.Matsukawa
if(!isset($D_NMAP_AND_NLIST)) $D_NMAP_AND_NLIST = 0;

// 拠点が保持する世界測地系緯度経度を使用		2017/01/19 N.Wada
if(!isset($D_KYOTEN_WGS_COL)) $D_KYOTEN_WGS_COL = null;

// 位置検索系 ----------------------------------------------
//フリーワード検索利用（1：駅、2：住所、3：施設）
if(!isset($D_SEARCH_AVAILABLE)) $D_SEARCH_AVAILABLE = '1|2|3';

//住所リストをどの階層まで掘り下げるか（1：都道府県、2：市区町村、3：大字、4：字丁目、5：街区、7：（最下層）※2.0
if(!isset($D_ADDRL_BOTTOM_LVL)) $D_ADDRL_BOTTOM_LVL = 7;

//場所決定後、TOPに戻らず最寄一覧を表示する		add 2012/04/24 Y.Matsukawa
if(!isset($D_DIRECT_SEARCH)) $D_DIRECT_SEARCH = 0;
if(!isset($D_DIRECT_SEARCH_NOTPL)) $D_DIRECT_SEARCH_NOTPL = 0;		//除外指定（現在地）
if(!isset($D_DIRECT_SEARCH_NOTADDR)) $D_DIRECT_SEARCH_NOTADDR = 0;	//除外指定（住所リスト）
if(!isset($D_DIRECT_SEARCH_NOTEKI)) $D_DIRECT_SEARCH_NOTEKI = 0;	//除外指定（駅リスト）
if(!isset($D_DIRECT_SEARCH_NOTPOI)) $D_DIRECT_SEARCH_NOTPOI = 0;	//除外指定（施設リスト）
if(!isset($D_DIRECT_SEARCH_NOTFW)) $D_DIRECT_SEARCH_NOTFW = 0;		//除外指定（フリーワード）
if(!isset($D_DIRECT_SEARCH_NOTROSEN)) $D_DIRECT_SEARCH_NOTROSEN = 0;	//除外指定（路線）		add 2014/03/12 Y.Matsukawa

//場所決定後、最寄一覧ではなく最寄地図へ遷移する		add 2012/05/23 Y.Matsukawa
if(!isset($D_LOCGPS_NMAP)) $D_LOCGPS_NMAP = 0;		//現在地取得（接続I/F用画面）	add 2016/01/20 N.Wada
if(!isset($D_TOPGPS_NMAP)) $D_TOPGPS_NMAP = 0;		//TOP現在地取得
if(!isset($D_PLGPS_NMAP)) $D_PLGPS_NMAP = 0;		//場所指定TOP現在地取得
if(!isset($D_TOPPL_NMAP)) $D_TOPPL_NMAP = 0;		//場所指定検索
if(!isset($D_ADDRL_NMAP)) $D_ADDRL_NMAP = 0;		//住所リスト検索
if(!isset($D_EKIL_NMAP)) $D_EKIL_NMAP = 0;			//駅リスト検索
if(!isset($D_POIL_NMAP)) $D_POIL_NMAP = 0;			//施設リスト検索
if(!isset($D_NLIST_NMAP)) $D_NLIST_NMAP = 0;		//フリーワード検索

// 現在検索エラー時の遷移先		add 2016/03/15 Y.Matsukawa
if(!isset($D_LOC_ERR_URL)) $D_LOC_ERR_URL = '';	// loc.htm
// 現在検索エラー時の遷移先に任意パラメータ追加	add 2016/04/26 N.Wada
if(!isset($D_LOC_ERR_FREE_PRM)) $D_LOC_ERR_FREE_PRM = 0;

//１ページ当たりの件数
if(!isset($D_SEARCH_EKIL_PAGE)) $D_SEARCH_EKIL_PAGE = 20;//駅リスト		add 2011/08/08 Y.Matsukawa
if(!isset($D_SEARCH_ADDRL_PAGE)) $D_SEARCH_ADDRL_PAGE = 10;//住所リスト
if(!isset($D_SEARCH_POIL_PAGE)) $D_SEARCH_POIL_PAGE = 20;//施設リスト		add 2012/04/24 Y.Matsukawa
if(!isset($D_SEARCH_EKIW_PAGE)) $D_SEARCH_EKIW_PAGE = 10;//駅フリーワード
if(!isset($D_SEARCH_ADDRW_PAGE)) $D_SEARCH_ADDRW_PAGE = 10;//住所フリーワード
if(!isset($D_SEARCH_POIW_PAGE)) $D_SEARCH_POIW_PAGE = 10;//施設フリーワード
if(!isset($D_SEARCH_ROSENL_PAGE)) $D_SEARCH_ROSENL_PAGE = 10;//路線リスト		add 2014/03/12 Y.Matsukawa
if(!isset($D_SEARCH_ROSEN_EKIL_PAGE)) $D_SEARCH_ROSEN_EKIL_PAGE = 20;//路線駅リスト		add 2014/03/12 Y.Matsukawa
if(!isset($D_SEARCH_ROSENW_PAGE)) $D_SEARCH_ROSENW_PAGE = 10;//路線フリーワード		add 2017/04/21 N.Wada

//最大件数		add 2013/07/29 Y.Matsukawa
if(!isset($D_SEARCH_EKIW_MAXCOUNT))  $D_SEARCH_EKIW_MAXCOUNT  = 10000;
if(!isset($D_SEARCH_ADDRW_MAXCOUNT)) $D_SEARCH_ADDRW_MAXCOUNT = 10000;
if(!isset($D_SEARCH_POIW_MAXCOUNT))  $D_SEARCH_POIW_MAXCOUNT  = 10000;
if(!isset($D_SEARCH_ROSENW_MAXCOUNT))$D_SEARCH_ROSENW_MAXCOUNT= 10000;	// add 2017/04/21 N.Wada

if(!isset($D_SELECT_TODS)) $D_SELECT_TODS = '';//都道府県限定（|区切りで列挙）		add 2013/05/30 Y.Matsukawa
if(!isset($D_ADDRLIST_AREA_SKIP)) $D_ADDRLIST_AREA_SKIP = 0;// 住所リスト検索：地方リスト非表示		add 2013/05/30 Y.Matsukawa

//郵便番号検索一覧スキップ（最寄り地図へ直接遷移）		add 2014/07/08 Y.Matsukawa
if(!isset($D_ZIPW_SKIP_LIST)) $D_ZIPW_SKIP_LIST = 0;

//施設検索
//企業ID CORPID
if(!isset($D_SEARCH_CORPID)) $D_SEARCH_CORPID = 'ZDC';
//サービスID SRVSID
if(!isset($D_SRARCH_SRVSID)) $D_SRARCH_SRVSID = 'API001';

// 路線リスト検索
if(!isset($D_ROSENLIST_TOP)) $D_ROSENLIST_TOP = 'AREA';// AREA：地方一覧／TOP：検索TOP		add 2015/01/13 Y.Matsukawa

//検索位置にマーカー表示		add 2016/03/03 N.Wada
if(!isset($D_SEARCH_MAP_ICON))      $D_SEARCH_MAP_ICON = 0;			// 最寄り地図に検索位置マーカーを表示
if(!isset($D_SEARCH_MAP_ICON_IMG))  $D_SEARCH_MAP_ICON_IMG = '';	// マーカー画像URL
if(!isset($D_SEARCH_MAP_ICON_W))    $D_SEARCH_MAP_ICON_W = 0;		// マーカー画像width
if(!isset($D_SEARCH_MAP_ICON_H))    $D_SEARCH_MAP_ICON_H = 0;		// マーカー画像height
if(!isset($D_SEARCH_MAP_ICON_OFX))  $D_SEARCH_MAP_ICON_OFX = 0;		// マーカー画像横offset
if(!isset($D_SEARCH_MAP_ICON_OFY))  $D_SEARCH_MAP_ICON_OFY = 0;		// マーカー画像縦offset

// 拠点検索系 ----------------------------------------------
// 拠点フリーワード検索 -------------------
//１ページ当たりの件数
if(!isset($D_SEARCH_LIST_PAGE)) $D_SEARCH_LIST_PAGE = 10;
// 拠点リスト検索 -------------------		add 2011/08/08 Y.Matsukawa
//１ページ当たりの件数
if(!isset($D_SEARCH_SHOPLIST_PAGE)) $D_SEARCH_SHOPLIST_PAGE = 10;
//最寄拠点 -------------------
//１ページ当たりの件数
if(!isset($D_NSHOP_LIST_PAGE)) $D_NSHOP_LIST_PAGE = 10;
//最小件数
if(!isset($D_SHOP_MIN)) $D_SHOP_MIN= 1;	//add 2016/03/06 N.Wada
//最大件数
if(!isset($D_SHOP_MAX)) $D_SHOP_MAX= 30;
if(!isset($D_SHOP_MAP_MAX)) $D_SHOP_MAP_MAX = $D_SHOP_MAX;		// 地図件数		add 2016/04/08 Y.Matsukawa
if(!isset($D_SHOP_LIST_MAX)) $D_SHOP_LIST_MAX = $D_SHOP_MAX;	// 一覧件数		add 2016/04/08 Y.Matsukawa
//指定ピクセル以上移動したときのみ検索 -1の場合再検索しない
if(!isset($D_SHOP_SEARCHPIX)) $D_SHOP_SEARCHPIX = 15;
//位置決定後の検索範囲(m)  0だと画面範囲全部
if(!isset($D_SHOP_RAD)) $D_SHOP_RAD = 50000;
if(!isset($D_SHOP_RAD_RE)) $D_SHOP_RAD_RE = 50000;
//地図操作で最寄り再検索しない		add 2012/01/10 N.Wada
if(!isset($D_SHOP_NO_SEARCH_USER_ACT)) $D_SHOP_NO_SEARCH_USER_ACT = 0;
//地図操作で最寄りリストを更新しない		add 2017/02/03 K.Tani
if(!isset($D_SHOP_NO_UPDATE_LIST_USER_ACT)) $D_SHOP_NO_UPDATE_LIST_USER_ACT = 0;
//分布地図の初期表示時、ヒットした拠点が入りきる縮尺に変更する		add 2012/10/24 Y.Matsukawa
if(!isset($D_SHOP_SCALE_OPT)) $D_SHOP_SCALE_OPT = 1;
//分布地図（縮尺固定）の初期表示時、地図範囲に拠点０だった場合、指定半径で再検索する	add 2012/10/24 Y.Matsukawa
if(!isset($D_SHOP_SEARCH_RETRY)) $D_SHOP_SEARCH_RETRY = 0;
//分布地図再検索後、最初のn件が入りきる縮尺に変更する		add 2012/10/24 Y.Matsukawa
if(!isset($D_SHOP_SEARCH_RETRY_VCNT)) $D_SHOP_SEARCH_RETRY_VCNT = 0;
//エリア検索のソート桁あわせ		add // 2015/01/26 Y.Matsukawa	ソート時に０埋めして桁あわせ
if(!isset($D_AREA_SORT_LPAD)) $D_AREA_SORT_LPAD = array();
//最寄り店舗ありの場合に地図へ遷移		add 2015/03/17 Y.Matsukawa
if(!isset($D_N_0_GOTO_NMAP)) $D_N_0_GOTO_NMAP = 0;
//エリア検索NULLの場合の表示文言		add 2015/05/07 Y.Matsukawa
if(!isset($D_SEARCH_SHOPA_DISPNM_NULL)) $D_SEARCH_SHOPA_DISPNM_NULL = "(その他)";
//店舗一覧ソート順指定		add 2015/05/08 Y.Matsukawa
if(!isset($D_SHOPW_KYOTEN_SORT)) $D_SHOPW_KYOTEN_SORT = "";//店舗フリーワード検索
if(!isset($D_SHOPA_KYOTEN_SORT)) $D_SHOPA_KYOTEN_SORT = "";//エリア検索
if(!isset($D_NLIST_KYOTEN_SORT)) $D_NLIST_KYOTEN_SORT = "";//最寄一覧		add 2016/03/03 Y.Matsukawa
//店舗一覧グルーピング指定		add 2016/03/03 Y.Matsukawa
if(!isset($D_NLIST_KYOTEN_GRP_COL)) $D_NLIST_KYOTEN_GRP_COL = "";//最寄一覧
//店舗一覧グループ名称（配列）		add 2016/03/03 Y.Matsukawa
if(!isset($D_NLIST_KYOTEN_GRP_NM)) $D_NLIST_KYOTEN_GRP_NM = null;//最寄一覧
//店舗一覧グループ毎のページ件数		add 2016/05/23 Y.Matsukawa
if(!isset($D_NLIST_KYOTEN_GRP_CNT_PP)) $D_NLIST_KYOTEN_GRP_CNT_PP = 0;//最寄一覧（1ページ目）
if(!isset($D_NLIST_KYOTEN_GRP_NEXT_CNT_PP)) $D_NLIST_KYOTEN_GRP_NEXT_CNT_PP = $D_NLIST_KYOTEN_GRP_CNT_PP;//最寄一覧（2ページ目以降）		add 2016/06/22 Y.Matsukawa
//再検索時に初期絞込条件を使わない		add 2015/10/30 N.Wada
if(!isset($D_RESARCH_INIT_COND_UNUSED)) $D_RESARCH_INIT_COND_UNUSED = 0;
//最寄り検索にだけ適用するcond		add 2016/02/18 Y.Matsukawa
if(!isset($D_N_COND)) $D_N_COND = "";
//最寄拠点を円検索		add 2016/03/10 Y.Matsukawa
if(!isset($D_NKYOTEN_CIRCLE)) $D_NKYOTEN_CIRCLE = 0;// 1：指定した半径(rad)を円を検索範囲とする、0：指定した半径(rad)の円を内包する矩形を検索範囲とする
//画面遷移時にcondを引き継がない（長尺URL対応）		add 2016/03/18 Y.Matsukawa
if(!isset($D_NO_COND_PRM)) $D_NO_COND_PRM = 0;
//店舗一覧独自パラメータ文字列		add 2017/04/14 N.Wada
if(!isset($D_NLIST_PRM_STR)) $D_NLIST_PRM_STR = "";		//最寄一覧
if(!isset($D_FWLIST_PRM_STR)) $D_FWLIST_PRM_STR = "";	//店舗フリーワード検索

// 最寄駅		add 2011/07/13 Y.Matsukawa
if(!isset($D_SRCH_NEKI)) $D_SRCH_NEKI = 0;
if(!isset($D_NEKI_RAD)) $D_NEKI_RAD = 5000;//検索範囲
if(!isset($D_NEKI_ROWS)) $D_NEKI_ROWS = 10;//１ページ件数
if(!isset($D_NEKI_MAX)) $D_NEKI_MAX = 10;//最大件数

// 最寄施設		add 2012/07/18 Y.Matsukawa
if(!isset($D_SRCH_NPOI)) $D_SRCH_NPOI = 0;
if(!isset($D_NPOI_RAD)) $D_NPOI_RAD = 5000;//検索範囲
if(!isset($D_NPOI_ROWS)) $D_NPOI_ROWS = 10;//１ページ件数
if(!isset($D_NPOI_MAX)) $D_NPOI_MAX = 10;//最大件数
//ジャンル未選択時に検索対象とするコード
if(!isset($D_NPOI_JNRMN)) $D_NPOI_JNRMN = "00160,00250,00140,00170,00220,00240,00130,00110,00120";


// 拠点一覧 ----------------------------------------------
// 拠点一覧からの遷移先
if(!isset($D_SHOP_LIST_DIST)) $D_SHOP_LIST_DIST = 'inf';
//全件一覧
if(!isset($D_KLIST_PAGE)) $D_KLIST_PAGE = 10;		//１ページ行数		2012/05/14 Y.Matsukawa

// 絞り込み条件 ----------------------------------------------
// filter複数項目指定（COL_xx=1@COL_xx=1）の連結指定
if (!isset($D_FILTER_U_COND)) $D_FILTER_U_COND = "AND";
// filter複数項目指定にAND固定で連結する項目
if (!isset($D_FILTER_EX_AND_COND)) $D_FILTER_EX_AND_COND = array();
// リストボックス定義
if (!isset($D_FILTER_VAL_LIST)) $D_FILTER_VAL_LIST = array();
if (!isset($D_FILTER_NAME_LIST)) $D_FILTER_NAME_LIST = array();

// add 2011/07/13 Y.Matsukawa
// ルート探索 ----------------------------------------------
if(!isset($D_LOC_ROUTE_TYPE)) $D_LOC_ROUTE_TYPE = 0;//現在地からルート（0：なし、1：歩行者、2：自動車）
if(!isset($D_NEKI_ROUTE_TYPE)) $D_NEKI_ROUTE_TYPE = 0;//最寄駅からルート（0：なし、1：歩行者、2：自動車）
if(!isset($D_NPOI_ROUTE_TYPE)) $D_NPOI_ROUTE_TYPE = 0;//最寄施設からルート（0：なし、1：歩行者、2：自動車）		add 2012/07/18 Y.Matsukawa
if(!isset($D_SEARCH_ROUTE_TYPE)) $D_SEARCH_ROUTE_TYPE = 0;//出発地指定ルート（0：なし、1：歩行者、2：自動車）
if(!isset($D_ROUTE_TIMEOUT)) $D_ROUTE_TIMEOUT = 5000;// タイムアウト時間
if(!isset($D_ROUTE_WALK_PSC)) $D_ROUTE_WALK_PSC = 0;//検索条件（0：距離優先、1：時間優先、3：楽な道優先、5：屋根のある道優先）
if(!isset($D_ROUTE_WALK_FLOORFLG)) $D_ROUTE_WALK_FLOORFLG = 0;//階層フラグ
if(!isset($D_ROUTE_WALK_DEP_FLOOR)) $D_ROUTE_WALK_DEP_FLOOR = 0;//出発：階層フラグ
if(!isset($D_ROUTE_WALK_DEP_STATIONFLG)) $D_ROUTE_WALK_DEP_STATIONFLG = 0;//出発：駅フラグ
if(!isset($D_ROUTE_WALK_ARR_FLOORFLG)) $D_ROUTE_WALK_ARR_FLOORFLG = 0;//到着：階層フラグ
if(!isset($D_ROUTE_WALK_ARR_STATIONFLG)) $D_ROUTE_WALK_ARR_STATIONFLG = 0;//到着：駅フラグ
if(!isset($D_ROUTE_WALK_ARR_FLOOR)) $D_ROUTE_WALK_ARR_FLOOR = 0;//到着：階層
if(!isset($D_SEARCH_COMB_ROUTE_USE_BUS)) $D_SEARCH_COMB_ROUTE_USE_BUS = 0;//出発地指定複合ルート（0：バスを使わない、1：バスを使う）	add 2017/01/18 N.Wada

// 任意パラメータ ----------------------------------------------
if(!isset($D_NOT_TRANSFER_FREEPARMS)) $D_NOT_TRANSFER_FREEPARMS = 0;//画面間引継ぎ（0：引き継ぐ、1：引き継がない）		add 2012/01/24 Y.Matsukawa

// 任意カラムのアイコンIDを使用		add 2012/10/10 H.Osamoto
if(!isset($D_ICONID_COL)) $D_ICONID_COL = '';	// アイコンIDを格納しているカラム名（例）'col_01' ※カラム定義で「リスト表示」「スマホ詳細」選択が必要です

// 専用区分定義		add 2012/10/10 H.Osamoto
if(!isset($D_ORG_KBN_COL)) $D_ORG_KBN_COL = '';
if(!isset($D_ORG_KBN_NAME_LIST)) $D_ORG_KBN_NAME_LIST = array();

// 拠点データ取得時のカスタマイズ仕様		add 2012/11/15 Y.Matsukawa
if(!isset($D_NKYOTEN_CUST)) $D_NKYOTEN_CUST = '';			// 最寄拠点
if(!isset($D_KYOTENID_CUST)) $D_KYOTENID_CUST = '';			// 拠点ID
if(!isset($D_KYOTENLIST_CUST)) $D_KYOTENLIST_CUST = '';		// 拠点検索

// JCN様向けカスタマイズ（運休情報表示）		add 2012/11/15 Y.Matsukawa
if(!isset($D_JCN_UNKYU_TOP)) $D_JCN_UNKYU_TOP = 0;			// 運休情報表示
if(!isset($D_JCN_UNKYU_JKN)) $D_JCN_UNKYU_JKN = '';			// 運休情報表示条件

// 場所検索からTOPへ戻った時のアンカー		add 2012/12/03 Y.Matsukawa
if(!isset($D_PL_RETURN_HASH)) $D_PL_RETURN_HASH = '';
if(!isset($D_PL_GPS_RETURN_HASH)) $D_PL_GPS_RETURN_HASH = '';		// 現在地の場合だけ別アンカー指定

// 神奈川電通広告向けカスタマイズ		add 2012/12/17 H.Osamoto
if(!isset($D_KANA_DEN)) $D_KANA_DEN = '';			// 神奈川電通広告フラグ

// 距離表示変換		add 2013/01/31 H.Osamoto
if(!isset($D_DIST_DISP_VARIABLE)) $D_DIST_DISP_VARIABLE = '';

//再検索
if(!isset($D_RESEARCH_CNT)) $D_RESEARCH_CNT = 0;	//最寄検索結果が0件の場合再検索で取得する件数指定		add 2013/04/15 H.Osamoto

// 拠点FW検索結果一覧の遷移先を最寄り地図にする		add 2015/10/30 N.Wada
if(!isset($D_SHOP_FW_TO_NMAP)) $D_SHOP_FW_TO_NMAP = 0;

// ヤマト運輸 営業所検索利用		add 2013/07/10 Y.Matsukawa
if(!isset($D_YTC_GET_JIGYOCD['INF'])) $D_YTC_GET_JIGYOCD['INF'] = 0;//詳細画面

// ポリゴン内外判定カラム		add 2014/03/07 H.Osamoto
if(!isset($D_POLY_COL)) $D_POLY_COL = '';

// For SiteIconOverLapping
if(!isset($D_KYO_ICON_OVERLAP)) $D_KYO_ICON_OVERLAP ="";// add 2014/08/18 AnPham

// add 2014/08/26 AnPham [
if(!isset($D_COOKIE_SHOPDTL_MAX)) $D_COOKIE_SHOPDTL_MAX = 0;
if(!isset($D_COOKIE_SHOPDTL_EXPIRE)) $D_COOKIE_SHOPDTL_EXPIRE = 365;
if(!isset($D_COOKIE_SHOPDTL_CGI)) $D_COOKIE_SHOPDTL_CGI = '';
// add 2014/08/26 AnPham ]

// jQuery読み込み停止		add 2015/02/02 Y.Matsukawa
if(!isset($D_DISABLE_JQUERY)) $D_DISABLE_JQUERY = 0;

// セブン&アイOMNI用ロジック		add 2015/05/01 Y.Matsukawa
if(!isset($D_711OMNI_INIT_JKN)) $D_711OMNI_INIT_JKN = "";	// 最寄り初期検索の条件
if(!isset($D_711OMNI_INIT_RAD)) $D_711OMNI_INIT_RAD = 0;	// 最寄り初期検索の範囲(m)
if(!isset($D_711OMNI_ALT_RAD)) $D_711OMNI_ALT_RAD = 0;		// 最寄り既定検索範囲(m)

// セブン&アイ 711apl用ロジック		add 2017/02/02 K.Tani
if(!isset($D_711APL_INIT_RAD)) $D_711APL_INIT_RAD = 0;	// 最寄り初期検索の範囲(m)
if(!isset($D_711APL_ALT_RAD)) $D_711APL_ALT_RAD = 0;	// 最寄り第二段階検索の範囲(m)

// GPSログ出力 add 2015/11/18 Xuan Chien
if(!isset($D_SGPS_LOG)) $D_SGPS_LOG = '';

// 拠点詳細地図表示の拠点データ取得時に拠点ログを出力する		add 2016/02/15 N.Wada
if(!isset($D_SHOPDTL_MAP_LOG)) $D_SHOPDTL_MAP_LOG = 0;

// 711mapニッセン向けロジック		add 2016/01/26 H.Osamoto
if(!isset($D_711NISSEN_FIX_ZOOM)) $D_711NISSEN_FIX_ZOOM = "";

// 住所リスト緯度経度指定	add 2016/11/21 T.Yoshino
if(!isset($D_LIST_ADDR_CUST))	 $D_LIST_ADDR_CUST	 = array();

// ルート検索時のFW検索時に店舗詳細情報取得	add 2017/01/17 N.Wada
if(!isset($D_SRCH_FW_GET_SHOPINFO)) $D_SRCH_FW_GET_SHOPINFO = 0;
// ルート検索時のFW結果一覧のリンク先を複合ルート検索に切り替える	add 2017/01/17 N.Wada
if(!isset($D_SRCH_FWLIST_TO_SRCH_ROUTE_COMB)) $D_SRCH_FWLIST_TO_SRCH_ROUTE_COMB = 0;

// 現在地ルート探索を世界測地系で実行		add 2017/01/20 N.Wada
if(!isset($D_ROUTE_SEARCH_MYLOC_WGS)) $D_ROUTE_SEARCH_MYLOC_WGS = 0;

// add 2017/04/14 H.Yasunaga 日本郵便向けカスタマイズ [
// jppost15日本郵便向けカスタマイズ
if (!isset($D_JPOST_CUSTOM_ENCODE)) $D_JPOST_CUSTOM_ENCODE = 0;
// add 2017/04/14 H.Yasunaga ]

// ローソンキャンペーン対応カスタマイズ	add 2017/04/21 H.Yasunaga
if (!isset($D_LOWSON_CAM_CUST))	$D_LOWSON_CAM_CUST = 0;

// ヤマト ロッカーセキュリティコード対応 add 2017/05/11 H.Yasunaga
if (!isset($D_YTC_SECURITY_CODE)) $D_YTC_SECURITY_CODE = 0;

?>