<?php
/*========================================================*/
// ファイル名：tpl_get_maplayer.cgi
// 処理名：地図レイヤー取得
//
// 作成日：2008/10/27
// 作成者：Y.Matsukawa
//
// 解説：生成済みのテンプレートから地図レイヤー番号を取得
//       ※PCテンプレートがある場合はPC優先
//
// 更新履歴
// 2008/10/27 Y.Matsukawa	新規作成
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
	
	// 入力パラメータチェック
	if ($cid == "") {
		print $cgi_kind . "19100" . "\n";
		exit;
	}
	
	// PCテンプレートのsetting.incを読み込み
	@include(PC_COMPANY_DIR.$cid.'/setting.inc');
	@include(PC_COMPANY_DIR.$cid.'/setting_option.inc');
	if (!$D_MAP_LAYER_KBN) {
		// 携帯テンプレートのsetting.incを読み込み
		@include(MB_COMPANY_DIR.$cid.'/setting.inc');
		@include(MB_COMPANY_DIR.$cid.'/setting_option.inc');
		if ($D_MAP_LANG == 'eng') {
			$D_MAP_LAYER_KBN = 5;
		} else {
			$D_MAP_LAYER_KBN = 4;	// デフォルト（日本語glaf）
		}
	}

	print $cgi_kind . "00000" . "\n";
	print $D_MAP_LAYER_KBN . "\n";

?>
