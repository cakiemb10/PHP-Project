<?PHP
$D_DATA_CID = 'zen000';
$D_ICON_CID = 'zen000';

//--------------------------------------------
// SSL接続（httpsアクセス）
//--------------------------------------------

// 「http」→「https」へリダイレクト
if (empty($_SERVER['HTTPS'])) {
	if (strpos($script_name, '.htm') && ($_SERVER['HTTP_HOST'] !== '127.0.0.1')) {
		$https_url = "https://" . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
		header("Location: $https_url");
		exit;
	}
}

// $D_AREA_SORT_LPAD[パターン番号1-5][階層番号1-2]['len' or 'char']
$D_AREA_SORT_LPAD[1][1]['len'] = 2;		// 桁数
$D_AREA_SORT_LPAD[1][1]['char'] = "0";	// 埋め込み文字

// 第一階層（都道府県）地図リンク
$D_AREA_LVL1_NMAP_LINK = 1;

//--------------------------------------------
// 絞り込み条件（複数cond）
//--------------------------------------------
$D_COND = array();
$D_COND_GRP = array();
$D_COND_ANDOR = array();

$D_COND_GRP_ANDOR = 'AND';

$D_COND[1] = array('type'=>'CB', 'val'=>'COL_02:1');//公開フラグ
$D_COND[2] = array('type'=>'CB', 'val'=>'COL_04:11');//サイト区分（はま寿司）
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
$D_COND[22] = array('type'=>'CB', 'val'=>'COL_72:1');//ZENSHO CooCa取扱店
$D_COND[23] = array('type'=>'CB', 'val'=>'COL_57:1');//QUICPay利用可
$D_COND[24] = array('type'=>'CB', 'val'=>'COL_58:1');//iD利用可
$D_COND[25] = array('type'=>'CB', 'val'=>'COL_74:1');//交通系電子マネー
$D_COND[26] = array('type'=>'CB', 'val'=>'COL_78:1');//Edy利用可


$D_COND_GRP[0] = array(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26);
$D_COND_ANDOR[0] = 'AND';

$D_COND[41] = array('type'=>'CB', 'val'=>'COL_41:2');//禁煙
$D_COND[42] = array('type'=>'CB', 'val'=>'COL_41:1');//分煙
$D_COND[43] = array('type'=>'CB', 'val'=>'COL_41:3');//完全分煙

$D_COND_GRP[1] = array(41,42,43);
$D_COND_ANDOR[1] = 'OR';

// 公開／非公開フラグ
$cond1 = $D_COND[1]['val'];
// サイト区分
$cond2 = $D_COND[2]['val'];

/* 強制的にURL最後尾に条件付与 */
$_VARS['cond1']=1; // 公開／非公開フラグ
$_VARS['cond2']=1; // サイト区分

$D_SHOP_NAME_COL = '道路名';
$D_SHOP_FW_INIT_COL = '道路名';

// フキダシ（デフォルトサイズ／×ボタン付き）
if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
	ZdcEmapMsg.setImage('{$D_DIR_BASE_G}img/msg/0002.png',new ZdcSize(242,95),
	                    '{$D_DIR_BASE_G}img/msg/0002-t.png',new ZdcSize(194,67),
	                    '{$D_DIR_BASE_G}img/msg/0001-x.png',new ZdcSize(13,13),
	                    '{$D_DIR_BASE_G}img/msg/0002-s.png',new ZdcSize(13,13),
	                    null);
	ZdcEmapMsg.setDocPosition(0,0,4,8,11,214,55,0);
	ZdcEmapMsg.setDocOffset(-110,-90);
	ZdcEmapMsg.setTextClass('UserMsgWindowTextStyle');
EOF;

// 検索位置にマーカー表示
$D_SEARCH_MAP_ICON = 1;
$D_ICON_SHOP_IMG = $D_DIR_COMPANY.'img/MapCenter3.png';
$D_ICON_SHOP_W = 25;
$D_ICON_SHOP_H = 25;
?>
