/**
 * 定数<br>いつもNAVI CGIラッパーの参照先ドメイン<br>※開発環境と本番環境で参照先が異なるので、書き替えが必要です。
 * @type String
 */
//var EMAPCGI_DOMAIN = 'test.e-map.ne.jp';	/* 開発環境 */
var EMAPCGI_DOMAIN = 'www.e-map.ne.jp';	/* 本番環境 */

/**
 * 定数<br>Cookie保存期間（日数）
 * @type Number
 */
var COOKIE_EXPIRES = 30;

/**
 * 定数<br>状態：非表示
 * @type Number
 */
var COND_INVISIBLE = 0;

/**
 * 定数<br>状態：表示（活性）
 * @type Number
 */
var COND_ENABLE = 1;

/**
 * 定数<br>状態：表示（非活性）
 * @type Number
 */
var COND_DISABLE = 2;

/**
 * 定数<br>ピン区分：企業
 * @type String
 */
var VLIST_TYPE_CORP = "1";

/**
 * 定数<br>ピン区分：個人
 * @type String
 */
var VLIST_TYPE_IND = "2";

/**
 * 定数<br>ピン区分：税理士
 * @type String
 */
var VLIST_TYPE_ZEI = "3";

/**
 * 定数<br>ピン区分：代理店
 * @type String
 */
var VLIST_TYPE_AGENT = "4";

/**
 * 定数<br>ピン区分：診査医
 * @type String
 */
var VLIST_TYPE_DR = "5";

/**
 * 定数<br>ピン属性の数
 * @type Number
 */
var PIN_ATR_COUNT = 10;

/**
 * 定数<br>ピンアイコン区分の数
 * @type Number
 */
var PIN_ICON_COUNT = 10;

/**
 * 定数<br>ピンアイコンのoffset（x方向）
 * @type Number
 */
var PIN_ICON_OFFSET_X = -16;

/**
 * 定数<br>ピンアイコンのoffset（y方向）
 * @type Number
 */
var PIN_ICON_OFFSET_Y = -50;

/**
 * 定数<br>ポイント名or業種名のoffset（x方向）
 * @type Number
 */
var PIN_NAME_OFFSET_X = -23;

/**
 * 定数<br>ポイント名or業種名のoffset（y方向）
 * @type Number
 */
var PIN_NAME_OFFSET_Y = -65;

/**
 * 定数<br>所属支社名のoffset（x方向）
 * @type Number
 */
var SYZ_NAME_OFFSET_X = -33;

/**
 * 定数<br>所属支社名のoffset（y方向）
 * @type Number
 */
var SYZ_NAME_OFFSET_Y = -65;

/**
 * 定数<br>住所フリーワード検索の表示件数
 * @type Number
 */
var SRCH_ADDR_ROWS = 100;

/**
 * 定数<br>POIフリーワード検索の取得件数
* @type Number
 */
var SRCH_POI_LIMIT = 10000;

/**
 * 定数<br>POIフリーワード検索の表示件数
* @type Number
 */
var SRCH_POI_ROWS = 100;

/**
 * 定数<br>POIフリーワード検索で絞込みを行う閾値件数
* @type Number
 */
var SRCH_POI_EXT = 50;

/**
 * 定数<br>周辺POI検索の取得件数
* @type Number
 */
var SRCH_NEARPOI_LIMIT = 10000;

/**
 * 定数<br>周辺POI検索の表示件数
* @type Number
 */
var SRCH_NEARPOI_ROWS = 100;

/**
 * 定数<br>周辺POI検索で絞込みを行う閾値件数
* @type Number
 */
var SRCH_NEARPOI_EXT = 50;

/**
 * 定数<br>デフォルト縮尺（ピン０本の時の縮尺）
 * @type Number
 */
var DEF_ZOOM = 10;

/**
 * 定数<br>社内情報検索を許可しない縮尺範囲
* @type Array
 */
var NGZOOM_SRCH_POINT = {min:0, max:5};

/**
 * 定数<br>社内情報検索の検索ワード最大文字数
 * @type Number
 */
var SP_WORD_MAXLEN = 40;

/**
 * 定数<br>周辺POI検索を許可しない縮尺範囲
* @type Array
 */
var NGZOOM_SRCH_NPOI = {min:0, max:5};

/**
 * 定数<br>ポイント表示変更を許可しない縮尺範囲
* @type Array
 */
var NGZOOM_SELECT_POINT = {min:0, max:5};

/**
 * 定数<br>ポイント表示変更条件１「決算前」ボタン番号
 * @type Number
 */
var SP_IDX_KESSANMAE = 3;

/**
 * 定数<br>ポイント表示変更条件１「決算後」ボタン番号
 * @type Number
 */
var SP_IDX_KESSANGO = 4;

/**
 * 定数<br>緯度経度（度分秒）書式チェック用の正規表現パターン
 * @type String
 */
var LL_REG_DMS = /^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/;

/**
 * 定数<br>緯度経度（10進）書式チェック用の正規表現パターン
 * @type String
 */
var LL_REG_DEG = /^([0-9]{2,3}\.[0-9]{1,})$/;

/**
 * 定数<br>緯度経度（ミリ秒）書式チェック用の正規表現パターン
 * @type String
 */
var LL_REG_MS = /^[0-9]{8,9}$/;

/**
 * 定数<br>都道府県名称
 * @type Array
 */
var TOD_NAME = {
'01':'北海道',
'02':'青森県',
'03':'岩手県',
'04':'宮城県',
'05':'秋田県',
'06':'山形県',
'07':'福島県',
'08':'茨城県',
'09':'栃木県',
'10':'群馬県',
'11':'埼玉県',
'12':'千葉県',
'13':'東京都',
'14':'神奈川県',
'15':'新潟県',
'16':'富山県',
'17':'石川県',
'18':'福井県',
'19':'山梨県',
'20':'長野県',
'21':'岐阜県',
'22':'静岡県',
'23':'愛知県',
'24':'三重県',
'25':'滋賀県',
'26':'京都府',
'27':'大阪府',
'28':'兵庫県',
'29':'奈良県',
'30':'和歌山県',
'31':'鳥取県',
'32':'島根県',
'33':'岡山県',
'34':'広島県',
'35':'山口県',
'36':'徳島県',
'37':'香川県',
'38':'愛媛県',
'39':'高知県',
'40':'福岡県',
'41':'佐賀県',
'42':'長崎県',
'43':'熊本県',
'44':'大分県',
'45':'宮崎県',
'46':'鹿児島県',
'47':'沖縄県'
};

/**
 * 定数<br>ピン画像Offset(y)
 * @type Array
 */
var PIN_IMG_OFFSET_Y = {
'2':45,
'3':90,
'4':135,
'5':180,
'6':225,
'7':270,
'8':315,
'9':360,
'10':405,
'11':450
};

/**
 * 定数<br>日本領土範囲
 * @type Array
 */
var JPNAREA = {
minlat: 20.4205556,
minlon: 122.9330556,
maxlat: 45.5552778,
maxlon: 153.9902778
};

/**
 * 定数<br>現在地取得関数のパラメータ値
 * @type Array
 */
var GPS_PARAM = {
waitTime: 0,
expire: 30,
datum: 1
};

/**
 * 定数<br>歩行速度（m/min）
 * @type Number
 */
var WALK_SPEED = (4.8 * 1000 / 60);

/**
 * 定数<br>地点マーカーのZindex値
 * @type Number
 */
var POINT_MARKER_ZINDEX = 100;

/**
 * 定数<br>地点マーカーのoffset（x方向）
 * @type Number
 */
var POINT_MARKER_OFFSET_X = -1;

/**
 * 定数<br>地点マーカーのoffset（y方向）
 * @type Number
 */
var POINT_MARKER_OFFSET_Y = -35;

/**
 * 定数<br>歩行者ルート検索距離の上限(5 or 10)
 * @type Number
 */
var WALK_MAX_DIST = 10;

/**
 * 定数<br>見込客登録を許可しない縮尺範囲
* @type Array
 */
var NGZOOM_PSPECT_CUST = {min:0, max:12};

/**
 * 定数<br>ピンアイコン上方向のOffset（地図縮尺決定で使用）
* @type Number
 */
var PIN_OFFSET_LAT = 0.0065505;

/**
 * メッセージ：職員コード未入力
 * @type String
 */
var MSG_ERR_STAFFCD_EMPTY = "職員コードを入力してください。";

/**
 * メッセージ：検索ワード未入力
 * @type String
 */
var MSG_ERR_WORD_EMPTY = "検索ワードを入力してください。";

/**
 * メッセージ：社内情報検索の検索ワード文字数エラー
 * @type String
 */
var MSG_ERR_WORD_LEN = "検索ワードが長すぎます。\n40文字以内で入力してください。";

/**
 * メッセージ：社内情報検索の検索ワード文字種エラー（全角以外）
 * @type String
 */
var MSG_ERR_WORD_MB = "検索ワードに半角文字が含まれています。\n全角で入力してください。";

/**
 * メッセージ：日本領土外
 * @type String
 */
var MSG_ERR_LL_OUT = "入力された緯度経度が日本領土の範囲内ではありません。\n日本領土内の緯度経度を入力してください。";

/**
 * メッセージ：社内情報検索を許可しない縮尺
 * @type String
 */
var MSG_ERR_SRCH_POINT_NGZOOM = "現在の縮尺では、社内情報検索は利用できません。\n地図をズームインさせてからご利用ください。";

/**
 * メッセージ：周辺POI検索を許可しない縮尺
 * @type String
 */
var MSG_ERR_SRCH_NPOI_NGZOOM = "現在の縮尺では、周辺からの検索は利用できません。\n地図をズームインさせてからご利用ください。";

/**
 * メッセージ：ポイント表示変更を許可しない縮尺
 * @type String
 */
var MSG_ERR_SELECT_POINT_NGZOOM = "現在の縮尺では、ポイント表示変更は利用できません。\n地図をズームインさせてからご利用ください。";

/**
 * メッセージ：ポイント表示変更で条件を選択していない
 * @type String
 */
var MSG_ERR_SELECT_POINT_NOSEL = "条件を選択してください。";

/**
 * メッセージ：ポイント表示変更で条件１明細を選択していない
 * @type String
 */
var MSG_ERR_SELECT_POINT_NODTL = "「全件」「既契約」「企保のみ」「未加入」のいずれかを選択してください。";

/**
 * メッセージ：表示位置修正の実行確認
 * @type String
 */
var MSG_CONF_CHGP = "該当ポイントの表示位置を修正します。\nよろしいですか？";

/**
 * メッセージ：表示位置修正不可
 * @type String
 */
var MSG_ERR_CHGP_NG = "このピンの表示位置は変更できません。";

/**
 * メッセージ：検索中
 * @type String
 */
var MSG_INF_SEARCH_PROCESSING = "検索中...";

/**
 * メッセージ：フリーワード検索の結果が０件
 * @type String
 */
var MSG_ALERT_NODATA = "該当データがありません。";

/**
 * メッセージ：ポイント表示変更条件１を３つ以上選択しようとした
 * @type String
 */
var MSG_ALERT_SPCOND_LIMIT = "選択できる項目は２つまでです。";

/**
 * メッセージ：支社コード未入力
 * @type String
 */
var MSG_ERR_SISYA_EMPTY = "支社コードを入力してください。";

/**
 * メッセージ：機関コード未入力
 * @type String
 */
var MSG_ERR_KA_EMPTY = "機関コードを入力してください。";

/**
 * メッセージ：職員コード未入力
 * @type String
 */
var MSG_ERR_SYOKUIN_EMPTY = "職員コードを入力してください。";

/**
 * メッセージ：見込客登録を許可しない縮尺
 * @type String
 */
var MSG_ERR_MIKOMI_NGZOOM = "現在の縮尺では、見込客登録は利用できません。\n地図をズームインさせてからご利用ください。";

/**
 * メッセージ：見込客登録：住所取得エラー
 * @type String
 */
var MSG_ERR_MIKOMI_ADDR = "この地点の住所は取得できません。";

/**
 * メッセージ：現在地取得失敗
 * @type String
 */
var MSG_ERR_LOC_NG = "GPSから現在地が取得できませんでした。\n時間を空けるか、場所を移動して再度実施してください。";

/**
 * メッセージ：現在地取得エラー
 * @type String
 */
var MSG_ERR_LOC_FAIL = "GPSの取得処理でシステムエラーが発生しました。\n照会窓口に連絡してください。";

/**
 * メッセージ：検索失敗
 * @type String
 */
var MSG_ERR_SEARCH_FAIL = "検索実行時にエラーが発生しました。\n照会窓口に連絡してください。";

/**
 * メッセージ：フリーワード検索タイムアウト
 * @type String
 */
var MSG_ERR_FW_SEARCH_FAIL = "検索ワードに該当する件数が多すぎるため、検索条件を変更してください。";

/**
 * メッセージ：ルート検索エラー
 * @type String
 */
var MSG_ERR_ROUTE_FAIL = "ルート検索に失敗しました。\n以下の原因が考えられます。検索条件を変更してください。\n　・出発地と目的地の距離が遠すぎる（歩行者ルートは10Km以内）\n　・通行できない地点が指定されている（例：川の上など）";

/**
 * メッセージ：電車ルート：歩行者ルートが短すぎる場合のエラー
 * @type String
 */
var MSG_ERR_TRAIN_WALK_SHORT = "出発地または目的地から駅までの距離が近すぎます。\n出発地または目的地を変更し、再度検索を行ってください。";

/**
 * メッセージ：電車ルート：歩行者ルートが長すぎる場合のエラー
 * @type String
 */
var MSG_ERR_TRAIN_WALK_LONG = "出発地または目的地から駅までの距離が遠すぎます。\n出発地または目的地を変更し、再度検索を行ってください。";

/**
 * メッセージ：移動距離表示
 * @type Array
 */
var ISKYORI_MESSAGE = {
	1: "移動距離（直線距離）は{kyori}kmです。\r\n※所属支社を始点、終点として計算しています。",
	9: "移動距離（直線距離）は1,000km以上です。\r\n※所属支社を始点、終点として計算しています。"
};

/**
 * 地図オブジェクトを保持します。
 * @type Object
 */
var DmapMap = null;

/**
 * ポイントランチャーのMsgInfoオブジェクトを保持します。
 * @type Object
 */
var DmapLauncher = null;

/**
 * 地図のプロパティを定義します。
 * @type Array
 */
var DmapMapOpt = {
	mapType: ZDC.MAPTYPE_MOBILE
}

/**
 * 地図コントロールのプロパティを定義します。
 * @type Array
 */
var DmapMapControl = {
	pos: {top: 50, left: 10},
	type: ZDC.CTRL_TYPE_NORMAL
}

/**
 * DmapClassUserオブジェクトを保持します。
 * @type Object
 */
var DmapUser;

/**
 * ピンのz-index最大値を保持します。
 * @type Number
 */
var DmapZindexMax = 100;

/**
 * DmapClassPinListオブジェクトを保持します。
 * @type Object
 */
var DmapPinList;

/**
 * 詳細情報一覧の状態（通常／簡易）を保持します。
 * @type Boolean
 */
var DmapPinListSimple = false;

/**
 * グループピン一覧ウィジェットのオブジェクトを保持します。
 * @type Object
 */
var DmapPinSelect;

/**
 * 表示位置修正モードかどうかの状態を保持します。
 * @type Boolean
 */
var DmapMovePinMode = false;

/**
 * ピンをドラッグ中かどうかの状態を保持します。
 * @type Boolean
 */
var DmapPinDragging = false;

/**
 * 表示位置修正でドラッグ中のPinオブジェクトを保持します。
 * @type Object
 */
var DmapMovePin = null;

/**
 * 右クリックモードを保持します。（1：見込客登録、2：ルート検索）
 * @type Number 
 */
var DmapRightClickMode = 1;

/**
 * 「社内情報検索」の状態を保持します。
 * @type Boolean
 */
var DmapSrchPointOn = false;

/**
 * 「フリーワード検索」の状態を保持します。
 * @type Boolean
 */
var DmapSrchFWOn = false;

/**
 * POI検索の結果オブジェクトを保持します。
 * @type Object
 */
var DmapSrchFWPoiResult = null;

/**
 * 検索位置マーカーを保持します。
 * @type Object
 */
var DmapSearchMarker = null;

/**
 * 現在地マーカーを保持します。
 * @type Object
 */
var DmapLocationMarker = null;

/**
 * 所属支社ピンを保持します。
 * @type Object
 */
var DmapSyozokuPin = null;

/**
 * 所属支社ピン名称を保持します。
 * @type Object
 */
var DmapSyozokuPinNm = null;

/**
 * 地図イベント有効フラグを保持します。
 * @type Boolean
 */
var DmapMapEventEnable = true;

/**
 * 無効化モードを保持します。
 * @type String
 */
var DmapDisableMode = '';

/**
 * 「見込客登録」吹き出しウィジェットのオブジェクトを保持します。
 * @type Object
 */
var DmapMikomiKyaku = null;

/**
 * ルート検索オブジェクトを保持します。
 * @type Object
 */
var DmapRouteSearch = null;

/**
 * 移動距離表示のPolylineオブジェクトを保持します。
 * @type Object
 */
var DmapIdoKyori = null;

/**
 * ダイアログドラッグ用の情報を保持します。
 * @type Array
 */
var DmapDlgDrag = {
	elm: null,
	flag: false,
	x: 0,
	y: 0
};

/**
 * リロード時の縮尺を保持します。
 * @type Number
 */
var DmapMapReloadScale = -1;

