<?PHP
//微調整用

//--------------------------------------------
// 複数絞り込み条件（チェックボックス、リストボックス）
//--------------------------------------------
// ※setting.incの設定を上書きする場合は、必ず下記初期化を行なってから設定してください。
//$D_COND = array();
//$D_COND_GRP = array();
//$D_COND_ANDOR = array();

//$D_COND[1] = array(
//'type'=>'SL'
//,'opts'=>array(
//	 '1'=>array('', '')
//	,'2'=>array('COL_20:01','直営店')
//	,'3'=>array('COL_20:02','フランチャイズ')
//	,'4'=>array('COL_20:03','臨時店舗')
//	,'5'=>array('COL_20:04','テナント')
//	)
//);
//$D_COND[2] = array(
//'type'=>'SL'
//,'opts'=>array(
//	 '1'=>array('', '')
//	,'2'=>array('COL_21:00','年中無休')
//	,'3'=>array('COL_21:01','土日祝')
//	,'4'=>array('COL_21:02','日祝')
//	)
//);
//$D_COND[3] = array('type'=>'CB', 'val'=>'COL_11:1');
//$D_COND[4] = array('type'=>'CB', 'val'=>'COL_12:1');
//$D_COND[5] = array('type'=>'CB', 'val'=>'COL_13:1');
//$D_COND[6] = array('type'=>'CB', 'val'=>'COL_14:1');
//$D_COND[7] = array('type'=>'CB', 'val'=>'COL_15:1');
//$D_COND[8] = array('type'=>'CB', 'val'=>'COL_16:1');
//$D_COND[9] = array('type'=>'CB', 'val'=>'COL_17:1');
//$D_COND[10] = array('type'=>'CB', 'val'=>'COL_18:1');
//$D_COND[11] = array('type'=>'CB', 'val'=>'COL_19:1');
//$D_COND[12] = array('type'=>'CB', 'val'=>'COL_18:1 OR COL_19:1');
//$D_COND_GRP_ANDOR = 'AND';
//$D_COND_GRP[0] = array(3,4,5,6,7,8,9,10,11);
//$D_COND_ANDOR[0] = 'AND';
//$D_COND_GRP[1] = array(1,2);
//$D_COND_ANDOR[1] = 'AND';
//$D_COND_GRP[2] = array(12);
//$D_COND_ANDOR[2] = 'AND';

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
