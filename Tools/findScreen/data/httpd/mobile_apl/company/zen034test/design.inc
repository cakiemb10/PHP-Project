<?PHP
//********* テンプレートカスタマイザ制御項目 *********
// 全画面で表示するタイプ指定
$D_USR_DEFNAME="店舗";

// ヘッダタイトル
$D_HEADER_TITLE="店舗検索";

// 「検索TOPへ戻る」リンク
$D_TOP_TXT="検索トップへ戻る";

// 「出発地を選択してルート案内」TOPへ戻るリンク
$D_SSRTOP_TXT = "出発地を選択しなおす";

// コピーライト(ダブルクォーテーションが入るのでシングルで囲う)
//$D_COPYRIGHT_TXT='';

// フラグ項目のタイトル文字列
$D_FLGITEM_TITLE="サービス";
if ($D_FLGITEM_TITLE=="") $D_FLGITEM_TITLE="その他";
// ※以前は「その他」固定だったので、下位互換性を保つため、未設定の場合のデフォルト値を「その他」としています。
// ※（既存案件でテンプレートを再生成した際、テンプレート内容が変わらないための措置です）

// 最寄検索で地図表示をするかしないか
$D_CAPTION["n.htm"]["NEAR_TITLE"]   = "#ANTENNA#地図で場所を表示";

// 検索トップメインタイトル
$D_CAPTION["s.htm"]["MAIN_TITLE"]   = "#SEARCH#@WORD@の検索";

// 検索トップ文言
$D_CAPTION["s.htm"]["SEARCH_TITLE"] = "#SEARCH#検索方法を指定";

// 今いる場所検索文言
$D_CAPTION["s.htm"]["LOCATE_TITLE"] = "#ANTENNA#今いる場所から";

// エリア検索文言
$D_CAPTION["s.htm"]["AREA_TITLE"]   = "#HOME#@WORD@のあるエリアから";
$D_CAPTION["s.htm"]["AREA_TITLE_2"] = "#HOME#@WORD@のあるエリアから2";
$D_CAPTION["s.htm"]["AREA_TITLE_3"] = "#HOME#@WORD@のあるエリアから3";
$D_CAPTION["s.htm"]["AREA_TITLE_4"] = "#HOME#@WORD@のあるエリアから4";
$D_CAPTION["s.htm"]["AREA_TITLE_5"] = "#HOME#@WORD@のあるエリアから5";

// 住所リスト文言
$D_CAPTION["s.htm"]["ADRLST_TITLE"] = "#SEARCH#住所の一覧から";

// フリーワード検索タイトル
$D_CAPTION["s.htm"]["KEYWD_TITLE"]  = "#SEARCH#キーワードで探す";

// オプション検索時のタイトル
$D_CAPTION["s.htm"]["OPT_TITLE"]    = "条件を選択して下さい";

// 駅フリーワード文言
$D_CAPTION["s.htm"]["STFW_TITLE"]   = "#TRAIN#駅の名称";

// 拠点フリーワード文言
$D_CAPTION["s.htm"]["CPFW_TITLE"]   = "#HOME#@WORD@名の一部";

// 住所フリーワード文言
$D_CAPTION["s.htm"]["ADFW_TITLE"]   = "#HOME#住所の一部";

// 〒番号検索文言
$D_CAPTION["s.htm"]["ZPFW_TITLE"]   = "#POST#郵便番号";

// 位置情報取得時のページ文言（DoCoMo以外)
$D_CAPTION["s.htm"]["LOCATIONMSG"]  = "位置情報を取得するため以下のリンクをクリックして下さい。";

// オプション検索時の検索ボタン
$D_CAPTION["s.htm"]["LOCATIONGO"]   = "検索";

// 出発地を選択してルート案内のヘッダタイトル
$D_CAPTION["s.htm"]["SSROUTE_TITLE"]   = "#SEARCH#出発地を選択してﾙｰﾄ案内";

// 出発地を選択してルート案内のキーワード検索
$D_CAPTION["s.htm"]["SSROUTE_KEYWD_TITLE"]   = "#SEARCH#出発地を入力してください";

// 地図表示ページの拡大文言（レベルダウン）
$D_CAPTION["m.htm"]["ZOOMIN_TITLE"] = "拡大";

// 地図表示ページの縮小文言（レベルアップ）
$D_CAPTION["m.htm"]["ZOOMOUT_TITLE"]= "縮小";

// 詳細へ戻るリンクの文言
$D_CAPTION["m.htm"]["DETAIL_TITLE"] = "@WORD@詳細を表示";

// 拠点詳細が地図画面の場合の出力項目指定
$D_CAPTION["m.htm"]["MAP_DTL_TITLE"]="#HOME#@NAME@";

// サイト接続時のタイトル表記方法
//$D_CAPTION["m.htm"]["MAP_DTL_TITLE" ]="■@WORD@詳細<BR><FONT COLOR=#FF0000>@NAME@</FONT>";

//地図移動後に店舗の地図に戻るリンクのタイトル文言
$D_CAPTION["m.htm"]["DETAIL_POS_TITLE"]="@WORD@の位置に戻る";

// 最寄駅検索文言
$D_CAPTION["m.htm"]["NEAR_TITLE"]   = "#TRAIN#近くの駅を表示";

// 現在地から店舗までのルート検索文言
$D_CAPTION["m.htm"]["ROUTE_TITLE"]  = "#ANTENNA#現在地からﾙｰﾄ案内";

// 出発地を選択してルート検索文言
$D_CAPTION["m.htm"]["SSROUTE_TITLE"]  = "#SEARCH#出発地を選択してﾙｰﾄ案内";

// 地図移動ヘルプリンクの文言
$D_CAPTION["m.htm"]["HELP_TITLE"]   = "#EXC#移動するには";

// ルート探索時の現在地点拡大リンク文言
$D_CAPTION["m.htm"]["ZOOM_S_TITLE"] = "#SEARCH#出発地を拡大";

// ルート探索時の目的（店舗）地点拡大リンク文言
$D_CAPTION["m.htm"]["ZOOM_E_TITLE"] = "#SEARCH#目的地を拡大";

// ルート探索時の全体が入るレベル表示の文言
$D_CAPTION["m.htm"]["ZOOM_A_TITLE"] = "全体を表示する";

// 最寄駅へのルート探索文言
$D_CAPTION["m.htm"]["NSROUTE_TITLE"]= "#TRAIN#駅から@WORD@の道案内";

// エリア検索での注意書き文言
$D_CAPTION["cl.htm"]["WARNING_TITLE"]= "<font color=\"red\">※リストにない場合、その地区に@WORD@がございません。</font>";

// 拠点フリーワード結果タイトル
$D_CAPTION["c.htm"]["SEARCH_TITLE"]= "[@FREEWD@]での検索結果";

// 住所フリーワード結果タイトル
$D_CAPTION["a.htm"]["SEARCH_TITLE"]= "[@FREEWD@]での検索結果";

// 駅フリーワード結果タイトル
$D_CAPTION["e.htm"]["SEARCH_TITLE"]= "[@FREEWD@]での検索結果";

// 〒番号検索結果タイトル
$D_CAPTION["z.htm"]["SEARCH_TITLE"]= "[@FREEWD@]での検索結果";

// 検索トップ画面項目順序（リンクでアクセスキーを使う部分のみ）
$D_TOPLINK_ORDER=array(
	'location'   => 1,
	'arealist'   => 2,
//	'arealist_2' => 3,		// エリア検索を使用する場合に有効にしてください。
//	'arealist_3' => 4,		// エリア検索を使用する場合に有効にしてください。
//	'arealist_4' => 5,		// エリア検索を使用する場合に有効にしてください。
//	'arealist_5' => 6,		// エリア検索を使用する場合に有効にしてください。
	'addrlist'   => 3,
	'freeword'   => 4
);

// 拠点詳細に表示する見出し定義
$D_DETAIL_TITLE=array(
	'TITLE_1' => '<b>@WORD@詳細</b>',
	'TITLE_2' => '#HINT#@WORD@名称',
	'TITLE_3' => '#HOME#住所',
	'TITLE_4' => '#TIME#営業時間',
	'TOMAPNAME' => '地図を表示'
);

//********* 修正の必要があまりない項目 *********
$D_AREA_TITLE = "エリア一覧";// エリア表示時のタイトル
$D_TOD_TITLE  = "都道府県一覧";// 都道府県リスト表示時のタイトル
$D_SHK_TITLE  = "市区町村一覧";// 市区町村リスト表示時のタイトル
$D_CPN_TITLE  = "@WORD@一覧";// 店舗一覧表示時のタイトル

// フリーワード結果が多い場合のフィルタフォームタイトル
$D_FILTER_TITLE="キーワード変更";

//**********************************************
// ページング
//**********************************************
// リストページでの次ページ文言
$D_PAGE_AFTER="次ページ";

// リストページでの前ページ文言
$D_PAGE_BEFORE="前ページ";

// リストページでの次ページと前ページの間
$D_PAGE_SEPARATOR="／";

//**********************************************
// アイコン画像
//**********************************************
$D_IMAGE_BASE="/home/emap/httpd/img/";
// 各種アイコンイメージ（ＧＩＦ限定）
$D_COMPASS_IMAGE=$D_IMAGE_BASE."999999.gif";
$D_STAR_IMAGE   =$D_IMAGE_BASE."000000.gif";
$D_EKI_IMAGE    =$D_IMAGE_BASE."100000.gif";
$D_CENTER_IMAGE =$D_IMAGE_BASE."200000.gif";
$D_START_IMAGE  =$D_IMAGE_BASE."600001.gif";
$D_END_IMAGE    =$D_IMAGE_BASE."600002.gif";

// 歩行者補助アイコンイメージ（ＧＩＦ限定）
$D_LAD_IMAGE = $D_IMAGE_BASE."p1.gif";
$D_ESC_IMAGE = $D_IMAGE_BASE."p2.gif";
$D_ELV_IMAGE = $D_IMAGE_BASE."p3.gif";
$D_MVR_IMAGE = $D_IMAGE_BASE."p4.gif";

// ルート描写ブラシ（PNG限定）
$D_R_NORM_IMAGE = $D_IMAGE_BASE."brushr11.png";
$D_R_HODO_IMAGE = $D_IMAGE_BASE."brushr21.png";
$D_R_BRID_IMAGE = $D_IMAGE_BASE."brushr31.png";
$D_R_UNDG_IMAGE = $D_IMAGE_BASE."brushr41.png";

$D_NUM_IMAGE_BASE=300000;

// 拠点アイコン
$D_CPNT_ICON_NO = "";
$D_CPNT_DB_ICON = true;

// 枠アイコン
$D_WAKU_IMAGE=$D_IMAGE_BASE."400000.gif";

// 以下枠を出力するケースをパイプ区切りで設定する。
// 1:拠点詳細
// 2:最寄駅
// 3:地図最寄（数字アイコン）
// ※アニメーションさせる設定の場合は、無条件に枠は表示されます。
//   また、アニメーション設定の方が、優先度は上です。
$D_WAKU_MODE = "1|2";

// 枠を出力するかしないかの設定
$D_WAKU_PLOT = true;

//**********************************************
// 以下将来対応用
//**********************************************
/*
// 最寄地図モードで移動を有効にするかどうか
// BACKOFFICEの設定の方がもちろん優先
$D_NM_MOVE=true;
*/
?>
