<?PHP
$D_DATA_CID = 'zen000';
$D_ICON_CID = 'zen000';

$D_SHOP_RAD = 10000;
//$D_SHOP_RAD_RE = 10000;
// 最寄り再検索時取得件数
$D_RESEARCH_CNT = 1;

// マウスオーバーでフキダシ
$D_KYO_ICON_MO = 1;

// $D_AREA_SORT_LPAD[パターン番号1-5][階層番号1-2]['len' or 'char']
$D_AREA_SORT_LPAD[1][1]['len'] = 2;		// 桁数
$D_AREA_SORT_LPAD[1][1]['char'] = "0";	// 埋め込み文字

// 第一階層（都道府県）地図リンク
$D_AREA_LVL1_NMAP_LINK = 1;

// スマホリダイレクト：店舗詳細→店舗地図
$D_REDIRECT_SMT_KYO_ID = 'map';

//--------------------------------------------
// 複数絞り込み条件（チェックボックス、リストボックス）
//--------------------------------------------
// ※setting.incの設定を上書きする場合は、必ず下記初期化を行なってから設定してください。
$D_COND = array();
$D_COND_GRP = array();
$D_COND_ANDOR = array();

$D_COND_GRP_ANDOR = 'AND';

$D_COND[1] = array('type'=>'CB', 'val'=>'COL_02:1');//公開フラグ
$D_COND[2] = array('type'=>'CB', 'val'=>'COL_04:8');//サイト区分（華屋与兵衛）
$D_COND[3] = array('type'=>'CB', 'val'=>'COL_26:1');//ドリンク
$D_COND[4] = array('type'=>'CB', 'val'=>'COL_27:1');//お子様メニュー
$D_COND[5] = array('type'=>'CB', 'val'=>'COL_28:1');//デザート
$D_COND[6] = array('type'=>'CB', 'val'=>'COL_29:1');//朝食
$D_COND[7] = array('type'=>'CB', 'val'=>'COL_33:1');//ドリンクバー
$D_COND[8] = array('type'=>'CB', 'val'=>'COL_34:1');//サラダバー
$D_COND[9] = array('type'=>'CB', 'val'=>'COL_35:1');//ランチメニュー
$D_COND[10] = array('type'=>'CB', 'val'=>'COL_36:1');//定食
$D_COND[11] = array('type'=>'CB', 'val'=>'COL_37:2');//しゃぶしゃぶ
$D_COND[12] = array('type'=>'CB', 'val'=>'COL_38:2');//焼肉
$D_COND[13] = array('type'=>'CB', 'val'=>'COL_39:1');//24時間営業
$D_COND[14] = array('type'=>'CB', 'val'=>'COL_42:1');//テーブル席あり
$D_COND[15] = array('type'=>'CB', 'val'=>'COL_43:1');//ベビーシート
$D_COND[16] = array('type'=>'CB', 'val'=>'COL_44:1');//多目的トイレ
$D_COND[17] = array('type'=>'CB', 'val'=>'COL_45:1');//スロープ／エレベーター
$D_COND[18] = array('type'=>'CB', 'val'=>'COL_46:1');//店舗フロア1F
$D_COND[19] = array('type'=>'CB', 'val'=>'COL_48:1');//駐車場
$D_COND[20] = array('type'=>'CB', 'val'=>'COL_49:1');//ドライブスルー
$D_COND[21] = array('type'=>'CB', 'val'=>'COL_50:1');//クレジットカード利用可
$D_COND[22] = array('type'=>'CB', 'val'=>'COL_25:1');//お酒
$D_COND[23] = array('type'=>'CB', 'val'=>'(COL_30:1 OR COL_30:2)');//朝食バイキング
$D_COND[24] = array('type'=>'CB', 'val'=>'COL_31:1');//食べ放題
$D_COND[25] = array('type'=>'CB', 'val'=>'COL_72:1');//ZENSHO CooCa取扱店
$D_COND[26] = array('type'=>'CB', 'val'=>'COL_74:1');//交通系電子マネー 
$D_COND[27] = array('type'=>'CB', 'val'=>'COL_78:1');//Edy
$D_COND[28] = array('type'=>'CB', 'val'=>'COL_58:1');//iD
$D_COND[29] = array('type'=>'CB', 'val'=>'COL_57:1');//QUICPay利用可


$D_COND_GRP[0] = array(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29);
$D_COND_ANDOR[0] = 'AND';

$D_COND[41] = array('type'=>'CB', 'val'=>'COL_41:2');//禁煙
$D_COND[42] = array('type'=>'CB', 'val'=>'COL_41:1');//分煙
$D_COND[43] = array('type'=>'CB', 'val'=>'COL_41:3');//完全分煙

$D_COND_GRP[1] = array(41,42,43);
$D_COND_ANDOR[1] = 'OR';

$D_COND[54] = array('type'=>'CB', 'val'=>'COL_03:8');//華屋与兵衛
$D_COND[55] = array('type'=>'CB', 'val'=>'COL_03:9');//和食よへい

$D_COND_GRP[2] = array(54,55);
$D_COND_ANDOR[2] = 'OR';

/* 強制的にURL最後尾に条件付与 */
$_VARS['cond1']=1; // 公開／非公開フラグ
$_VARS['cond2']=1; // サイト区分


//--------------------------------------------
//印刷画面
//--------------------------------------------
//印刷画面で最寄り拠点アイコンを表示するか（0：表示しない、1：表示する）
$D_SHOP_PRINT_SEARCH = 0;

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
// フリーワード検索
//--------------------------------------------
//フリーワード複合検索用フラグ
$D_COMB_FW_ZIP  = 1;	//郵便番号フリーワード
$D_COMB_FW_ADDR = 1;	//住所フリーワード
$D_COMB_FW_ST   = 1;	//駅フリーワード
$D_COMB_FW_POI  = 0;	//施設フリーワード
$D_COMB_FW_SHOP = 1;	//拠点フリーワード
//フリーワード複合検索出力件数
$D_COMB_FW_ZIP_MAX  = 5;	//郵便番号フリーワード
$D_COMB_FW_ADDR_MAX = 5;	//住所フリーワード
$D_COMB_FW_ST_MAX   = 5;	//駅フリーワード
$D_COMB_FW_POI_MAX  = 5;	//施設フリーワード
$D_COMB_FW_SHOP_MAX = 5;	//拠点フリーワード

?>
