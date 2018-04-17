<?PHP
$D_DATA_CID = 'zen000';
$D_ICON_CID = 'zen000';

$D_Z2H_OPTION = "rnsk";

$D_CAPTION["s.htm"]["AREA_TITLE"]   = "#HOME#都道府県から探す";

$optcd = 1;
$D_OPTCD_USE_DETAIL = 1;
$D_OPTCD_USE_SHOP_AREA = 1;
$D_OPTCD_USE_SHOP_WORD = 1;
$D_OPTCD_DEF[1] = " COL_02:1 AND COL_04:11 ";//公開フラグ＆サイト区分

$SETTING["checkboxopt"] = 1;
$SETTING["tplptn"] = 2;
$OPTION = array(
	0=>array(
		0=>array('name'=>'K1','value'=>'1','jkn'=>'COL_26:1','title'=>'ﾄﾞﾘﾝｸ'),
		1=>array('name'=>'K2','value'=>'1','jkn'=>'COL_27:1','title'=>'お子様ﾒﾆｭｰ'),
		2=>array('name'=>'K3','value'=>'1','jkn'=>'COL_28:1','title'=>'ﾃﾞｻﾞｰﾄ'),
		3=>array('name'=>'K4','value'=>'1','jkn'=>'COL_29:1','title'=>'朝食'),
		4=>array('name'=>'K5','value'=>'1','jkn'=>'COL_33:1','title'=>'ﾄﾞﾘﾝｸﾊﾞｰ'),
		5=>array('name'=>'K6','value'=>'1','jkn'=>'COL_34:1','title'=>'ｻﾗﾀﾞﾊﾞｰ'),
		6=>array('name'=>'K7','value'=>'1','jkn'=>'COL_35:1','title'=>'ﾗﾝﾁﾒﾆｭｰ'),
		7=>array('name'=>'K8','value'=>'1','jkn'=>'COL_36:1','title'=>'定食'),
		8=>array('name'=>'K9','value'=>'1','jkn'=>'COL_37:2','title'=>'しゃぶしゃぶ'),
		9=>array('name'=>'K10','value'=>'1','jkn'=>'COL_38:2','title'=>'焼肉'),
		10=>array('name'=>'K11','value'=>'1','jkn'=>'COL_39:1','title'=>'24時間営業'),
		11=>array('name'=>'K12','value'=>'1','jkn'=>'COL_42:1','title'=>'ﾃｰﾌﾞﾙ席あり'),
		12=>array('name'=>'K13','value'=>'1','jkn'=>'COL_43:1','title'=>'ﾍﾞﾋﾞｰｼｰﾄ'),
		13=>array('name'=>'K14','value'=>'1','jkn'=>'COL_44:1','title'=>'多目的ﾄｲﾚ'),
		14=>array('name'=>'K15','value'=>'1','jkn'=>'COL_45:1','title'=>'ｽﾛｰﾌﾟ/ｴﾚﾍﾞｰﾀｰ'),
		15=>array('name'=>'K16','value'=>'1','jkn'=>'COL_46:1','title'=>'店舗ﾌﾛｱ1F'),
		16=>array('name'=>'K17','value'=>'1','jkn'=>'COL_48:1','title'=>'駐車場'),
		17=>array('name'=>'K18','value'=>'1','jkn'=>'COL_49:1','title'=>'ﾄﾞﾗｲﾌﾞｽﾙｰ'),
		18=>array('name'=>'K19','value'=>'1','jkn'=>'COL_50:1','title'=>'ｸﾚｼﾞｯﾄｶｰﾄﾞ利用可'),
		19=>array('name'=>'K20','value'=>'1','jkn'=>'COL_72:1','title'=>'ZENSHO CooCa取扱店'),
		20=>array('name'=>'K21','value'=>'1','jkn'=>'COL_74:1','title'=>'交通系電子マネー'),
		21=>array('name'=>'K22','value'=>'1','jkn'=>'COL_78:1','title'=>'Edy利用可'),
		22=>array('name'=>'K23','value'=>'1','jkn'=>'COL_58:1','title'=>'iD利用可'),
		23=>array('name'=>'K24','value'=>'1','jkn'=>'COL_57:1','title'=>'QUICPay利用可'),
		'attribu'=>'AND'
	),
	1=>array(
		0=>array('name'=>'M1','value'=>'1','jkn'=>'COL_41:2','title'=>'禁煙'),
		1=>array('name'=>'M2','value'=>'1','jkn'=>'COL_41:1','title'=>'分煙'),
		2=>array('name'=>'M3','value'=>'1','jkn'=>'COL_41:3','title'=>'完全分煙'),
		'attribu'=>'OR'
	),
	'attribu'=>'AND'
);
$SETTING["loc_optcheck"] = 1;

$D_TOP_TXT="検索ﾄｯﾌﾟへ戻る";
$D_CAPTION["s.htm"]["KEYWD_TITLE"]  = "#SEARCH#ｷｰﾜｰﾄﾞで探す";
$D_CAPTION["s.htm"]["LOCATIONMSG"]  = "位置情報を取得するため以下のﾘﾝｸをｸﾘｯｸして下さい｡";
$D_CAPTION["cl.htm"]["WARNING_TITLE"]= "<font color=\"red\">※ﾘｽﾄにない場合､その地区に@WORD@がございません｡</font>";
$D_AREA_TITLE = "ｴﾘｱ一覧";
$D_FILTER_TITLE="ｷｰﾜｰﾄﾞ変更";
$D_PAGE_AFTER="次ﾍﾟｰｼﾞ";
$D_PAGE_BEFORE="前ﾍﾟｰｼﾞ";

$AREA_INFO[0]["tod"] = '1|2|3|4|5|6|7';
$AREA_INFO[1]["tod"] = '13|14|11|12|10|9|8';
$AREA_INFO[2]["tod"] = '15|16|17|18';
$AREA_INFO[3]["tod"] = '23|19|22|20|21';
$AREA_INFO[4]["tod"] = '27|26|28|25|29|30|24';
$AREA_INFO[5]["tod"] = '34|33|35|31|32';
$AREA_INFO[6]["tod"] = '37|36|38|39';
$AREA_INFO[7]["tod"] = '40|41|42|43|44|45|46|47';
?>
