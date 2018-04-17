<?PHP
//微調整用

$D_MSG_SEARCH_MAXPAGE["ShopW"] = "検索結果が 100 件を超える場合は表示ができませんので、<br>入力内容を変えて再度検索してください。<br>";

// パンくず用トップリンク
$D_HISTORY_TOP_LINK = "location.href='../asp/$cid/?myar=e&p_s2=".urlencode(str_replace(" ", "+", $p_s2))."&lm=".urlencode(str_replace(" ", "+", $lm))."';";

// Myエリア使用フラグ
$D_MYAREA_USE = 1;

// リダイレクト先URL
if (ereg('test', $cid)) {
	$D_REDIRECT_TOP_URL = "https://stg.tsite.jp/t-map/index.pl";
} else {
	$D_REDIRECT_TOP_URL = "https://tsite.jp/t-map/index.pl";
}

// Newアイコン判定カラム
// 指定方法：col（NAMEを除くリストに表示する項目の項番）
//$D_NEW_ICON_COL = "col4";

//パンくずTOPリンク
$D_HISTORY_TOP_NAME = "お店検索TOP";

// クーポン有りアイコン
$D_ICON_NEW_IMG = "{$D_DIR_COMPANY}images/coupon-02.gif";

// Myエリア表示中フラグ
$D_SELECTED_MYAREA_ID = 0;

//--------------------------------------------
// 地図縮尺
//--------------------------------------------
//位置検索決定後
//（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
$D_INIT_LVL_SEARCH = -1;
//詳細選択後
//（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
$D_INIT_LVL_DETAIL = -1;
//印刷画面
//（-1：$D_INIT_LVLに準じる）
$D_INIT_LVL_PRINT  = -1;

//--------------------------------------------
//印刷画面
//--------------------------------------------
//印刷画面で最寄り拠点アイコンを表示するか（0：表示しない、1：表示する）
$D_SHOP_PRINT_SEARCH = 1;

//--------------------------------------------
//検索結果
//--------------------------------------------
//住所リスト／駅リストでカナ絞り込みを使用（0：使用しない、1：使用する）
$D_SEARCH_KANA = 1;

//--------------------------------------------
//検索結果（テーブル形式）のレイアウト情報
//--------------------------------------------
//列数
//※この設定を変更した場合、search_table.tplとsearch_addrtable.tplのHTMLを調整する必要があります。
$D_SEARCH_TABLE_COLS = 3;
//行数
$D_SEARCH_TABLE_ROWS = 8;
//１ページの表示件数（※編集不可）
$D_SEARCH_TABLE_PAGE = $D_SEARCH_TABLE_COLS * $D_SEARCH_TABLE_ROWS;

//--------------------------------------------
// 吹き出し
//--------------------------------------------
// 吹き出しタイプ0001（小）
// ※タイプ0000（大）にする場合は、↓この行から「EOF;」の行までをコメントアウトしてください
//if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
//	ZdcEmapMsg.setImage('{$D_DIR_BASE}img/msg/0001.png',new ZdcSize(223,125),
//	                    '{$D_DIR_BASE}img/msg/0001-t.png',new ZdcSize(194,67),
//	                    '{$D_DIR_BASE}img/msg/0001-x.png',new ZdcSize(13,13),
//	                    '{$D_DIR_BASE}img/msg/0001-s.png',new ZdcSize(295,144),
//	                    '{$D_DIR_BASE}img/msg/0001-p.gif');
//	ZdcEmapMsg.setDocPosition(0,0,11,8,11,205,55,0);
//	ZdcEmapMsg.setDocOffset(0,-125);
//	ZdcEmapMsg.setTextClass("UserMsgWindowTextStyle");
//EOF;

?>
