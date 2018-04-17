<?php
//========================================================
// マスタテンプレートID
//========================================================
$MST_ID	= "EasyDesign01";
//========================================================
// サービス種別
//		"S"：スタンダード、"L"：ライト、"N"：拠点なし（マップリンク）
//========================================================
$PC_EMAP_KBN = "S";
//========================================================
// テンプレートファイル定義
//		key:テンプレートファイル名
//		val(array):
//			"NM"=>Template Customizer 表示名
//			"CR"=>Template Engine 制御コード有無("N"：制御コードなし)
//			"ED"=>Template Customizer アクセス制限("W"：編集可、"R"：参照のみ)
//			"GP"=>Template Engine 生成グループ("S"：設定ファイルのみ、"D"：デザイン設定反映)
//========================================================
$TPL_FILE_DEF = array(
 "emapview_0.tpl"			=> array("NM"=>"基本レイアウト(TOP)",		"CR"=>"N",	"ED"=>"W")
,"emapview_1.tpl"			=> array("NM"=>"基本レイアウト(ヘッダ)",	"CR"=>"N",	"ED"=>"W")
,"emapview_5.tpl"			=> array("NM"=>"基本レイアウト",						"ED"=>"W")
,"emapview_8.tpl"			=> array("NM"=>"基本レイアウト(フッタ)",	"CR"=>"N",	"ED"=>"W")
,"emapview_9.tpl"			=> array("NM"=>"基本レイアウト(BOTTOM)",	"CR"=>"N",	"ED"=>"W")
,"emapview_shop_detail.tpl"	=> array("NM"=>"拠点詳細",								"ED"=>"W")
,"emapview_shop_detail_nomap.tpl"	=> array("NM"=>"拠点詳細（地図なし）",			"ED"=>"W")
,"emapview_shop_list.tpl"	=> array("NM"=>"拠点リスト",							"ED"=>"W")
,"emapview_msg.tpl"			=> array("NM"=>"拠点吹出",								"ED"=>"W")
,"emapview_cond.tpl"		=> array("NM"=>"拠点絞込条件",							"ED"=>"W")
,"emapview_npoi_list.tpl"	=> array("NM"=>"周辺施設リスト",			"CR"=>"N",	"ED"=>"W")
,"emapview_jnr.tpl"			=> array("NM"=>"施設ジャンル条件",						"ED"=>"W")
,"emapview_neki.tpl"		=> array("NM"=>"最寄駅リスト",							"ED"=>"W")
,"emapview_froute.tpl"		=> array("NM"=>"出発地指定ルート探索",					"ED"=>"W")
,"emapview_error.tpl"		=> array("NM"=>"エラー画面",							"ED"=>"W")
,"print_0.tpl"				=> array("NM"=>"印刷画面(TOP)",				"CR"=>"N",	"ED"=>"W")
,"print_1.tpl"				=> array("NM"=>"印刷画面(ヘッダ)",			"CR"=>"N",	"ED"=>"W")
,"print_5.tpl"				=> array("NM"=>"印刷画面",								"ED"=>"W")
,"print_8.tpl"				=> array("NM"=>"印刷画面(フッタ)",			"CR"=>"N",	"ED"=>"W")
,"print_9.tpl"				=> array("NM"=>"印刷画面(BOTTOM)",			"CR"=>"N",	"ED"=>"W")
,"search_shop_list_print.tpl"=> array("NM"=>"拠点リスト印刷画面",					"ED"=>"W")
,"search_top.tpl"			=> array("NM"=>"検索画面",								"ED"=>"W")
,"search_rail.tpl"			=> array("NM"=>"路線図検索",				"CR"=>"N",	"ED"=>"W")
,"search_area.tpl"			=> array("NM"=>"地域図検索",				"CR"=>"N",	"ED"=>"W")
,"search_shop_list.tpl"		=> array("NM"=>"検索結果拠点一覧",						"ED"=>"W")
,"search_list.tpl"			=> array("NM"=>"検索結果項目一覧",			"CR"=>"N",	"ED"=>"W")
,"search_table.tpl"			=> array("NM"=>"検索結果分類表",			"CR"=>"N",	"ED"=>"W")
,"search_addrtable.tpl"		=> array("NM"=>"検索結果都道府県表",		"CR"=>"N",	"ED"=>"W")
,"search_error.tpl"			=> array("NM"=>"検索エラー画面",			"CR"=>"N",	"ED"=>"W")
,"setting.inc"				=> array("NM"=>"設定ファイル",							"ED"=>"R", "GP"=>"S")
,"setting_option.inc"		=> array("NM"=>"オプション設定ファイル",	"CR"=>"N",	"ED"=>"W")
,"css/default.css"			=> array("NM"=>"default.css",				"CR"=>"N",	"ED"=>"W")
,"css/layout.css"			=> array("NM"=>"layout.css",							"ED"=>"W", "GP"=>"D")
,"css/base.css"				=> array("NM"=>"base.css",								"ED"=>"W", "GP"=>"D")
,"css/print_page.css"		=> array("NM"=>"print_page.css",						"ED"=>"W", "GP"=>"D")
,"css/print.css"			=> array("NM"=>"print.css",					"CR"=>"N",	"ED"=>"W")
,"css/print2.css"			=> array("NM"=>"print2.css",				"CR"=>"N",	"ED"=>"W")
,"css/print_list.css"		=> array("NM"=>"print_list.css",						"ED"=>"W", "GP"=>"D")
,"css/custom.css"			=> array("NM"=>"custom.css",				"CR"=>"N",	"ED"=>"W")
,"js/custom.js"				=> array("NM"=>"custom.js",					"CR"=>"N",	"ED"=>"W")
);
?>
