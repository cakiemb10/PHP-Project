<?php
/*========================================================*/
// ファイル名：tpl_get_setting.cgi
// 処理名：テンプレート設定取得
//
// 作成日：2009/08/28
// 作成者：Y.Matsukawa
//
// 解説：生成済みのテンプレートから、指定された変数の設定を取得
//
// 更新履歴
// 2009/08/28 Y.Matsukawa	新規作成
// 2012/10/16 Y.Matsukawa	error_reporting()削除
/*========================================================*/
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	header( "Content-Type: Text/html; charset=euc-jp" );

	define("PC_COMPANY_DIR", "../pc/company/");
	define("MB_COMPANY_DIR", "../mobile_apl/company/");

	// CGI種別
	$cgi_kind = "812";

	// パラメータ取得
	$cid = ${'_'.$_SERVER['REQUEST_METHOD']}['cid'];
	$pm = ${'_'.$_SERVER['REQUEST_METHOD']}['pm'];
	$v = ${'_'.$_SERVER['REQUEST_METHOD']}['v'];
	
	// 入力パラメータチェック
	if ($cid == "" || $pm == "" || $v == "") {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	
	// PCテンプレートのsetting.incを読み込み
	if ($pm == 'P') {
		@include(PC_COMPANY_DIR.$cid.'/setting.inc');
		@include(PC_COMPANY_DIR.$cid.'/setting_option.inc');
	} else if ($pm == 'M') {
		// 携帯テンプレートのsetting.incを読み込み
		@include(MB_COMPANY_DIR.$cid.'/setting.inc');
		@include(MB_COMPANY_DIR.$cid.'/setting_option.inc');
	}

	print $cgi_kind . "00000" . "\n";
	print $$v . "\n";

?>
