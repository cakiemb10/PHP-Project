<?php
//========================================================
// マスタテンプレートID
//========================================================
$MST_ID = "01";
//========================================================
// テンプレートファイル定義
//      key:テンプレートファイル名
//      val(array):
//          "NM"=>Template Customizer 表示名
//          "CR"=>Template Engine 制御コード有無("N"：制御コードなし)
//          "ED"=>Template Customizer アクセス制限("W"：編集可、"R"：参照のみ)
//          "GP"=>Template Engine 生成グループ("S"：設定ファイルのみ)
//          "MS"=>(携帯)サービス区分("S"：スタンダード、"L"：ライト、"N"：拠点なしライト)
//========================================================
$TPL_FILE_DEF = array(
 "top.tpl"              => array("NM"=>"TOP画面",              "CR"=>"N", "ED"=>"W",            "MS"=>"S|N")
,"top2.tpl"            => array("NM"=>"TOP画面2",             "CR"=>"N", "ED"=>"W",            "MS"=>"S|N")
,"header.tpl"           => array("NM"=>"ヘッダ",               "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"header_light.tpl"     => array("NM"=>"ヘッダ(Light)",        "CR"=>"N", "ED"=>"W",            "MS"=>"L|N")
,"footer.tpl"           => array("NM"=>"フッタ",               "CR"=>"N", "ED"=>"W",            "MS"=>"S|N")
,"footer_light.tpl"     => array("NM"=>"フッタ(Light)",        "CR"=>"N", "ED"=>"W",            "MS"=>"L|N")
,"list.tpl"             => array("NM"=>"一覧画面",                        "ED"=>"W",            "MS"=>"S|L|N")
,"dt.tpl"               => array("NM"=>"拠点詳細画面",                    "ED"=>"W",            "MS"=>"S|L|N")
,"map.tpl"              => array("NM"=>"地図画面",                        "ED"=>"W",            "MS"=>"S|L|N")
,"topssr.tpl"           => array("NM"=>"出発地選択ルート案内", "CR"=>"N", "ED"=>"W",            "MS"=>"S")
,"help.tpl"             => array("NM"=>"地図移動ヘルプ画面",   "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"err.tpl"              => array("NM"=>"エラー画面",           "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"loc.tpl"              => array("NM"=>"位置情報取得",         "CR"=>"N", "ED"=>"W",            "MS"=>"S")
,"copyright.tpl"        => array("NM"=>"著作権表示"   ,        "CR"=>"N", "ED"=>"R",            "MS"=>"S|L|N")
,"setting.inc"          => array("NM"=>"設定ファイル",                    "ED"=>"W", "GP"=>"S", "MS"=>"S|L|N")
,"setting_option.inc"   => array("NM"=>"オプション設定",       "CR"=>"N", "ED"=>"W",            "MS"=>"S|L|N")
,"design.inc"           => array("NM"=>"デザイン設定ファイル",            "ED"=>"W",            "MS"=>"S|L|N")
);
?>
