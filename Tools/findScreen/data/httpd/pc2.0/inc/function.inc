<?PHP
// ------------------------------------------------------------
// 汎用関数php
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2009/02/23 Y.Matsukawa	拠点詳細に自由項目パラメータを引き渡す
// 2009/06/17 Y.Matsukawa	携帯URL（詳細画面）を追加
// 2009/08/24 Y.Matsukawa	IP制限
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2009/09/08 Y.Matsukawa	ログ出力256バイト丸め
// 2009/09/14 Y.Matsukawa	ログ集計が256バイトでもまだエラーになるので128バイトに変更
// 2009/11/07 Y.Matsukawa	拠点項目拡張（50→200）
// 2010/01/18 Y.Matsukawa	【不具合修正】フリーワードにスペースが含まれている場合、半角スペース混在のままログ出力されてしまい、ログ項目区切りが不正になる
// 2010/02/10 Y.Matsukawa	ログ出力：フリーワード128バイト丸め
// 2010/04/08 Y.Matsukawa	脆弱性対策（クロスサイトスクリプティング）
// 2010/04/19 Y.Matsukawa	脆弱性対策（logディレクトリ移動）
// 2010/05/17 Y.Matsukawa	function.inc単体でincludeしてもエラーにならないよう、$D_REMOVE_QUOTE_PARAMS初期化
// 2010/06/16 Y.Matsukawa	出発地を指定してルート探索
// 2010/07/06 Y.Matsukawa	【812SH不具合対応】812SHにURL送信すると、末尾に=が付いてしまうので、URL末尾を&で終わらせるように改修
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/09/07 Y.Matsukawa	出発地を指定してルート探索（Light、Maplink）
// 2010/09/13 Y.Matsukawa	拠点詳細表示時に拠点IDをCookie保存
// 2010/10/01 Y.Matsukawa	ログ出力時、全てのパラメータのスペース置換と桁数揃えを実施（不正アクセス対応）
// 2011/02/22 Y.Matsukawa	【不具合修正】不正アクセスでGETパラメータに配列指定された場合に不正なログが出力される
// 2011/04/18 H.Osamoto		機種依存文字チェック(IzonSearch)を追加
// 2011/05/23 K.Masuda		自由項目拡張（p_f,p_sを50まで）
// 2011/06/21 Y.Matsukawa	企業IDをテンプレートに引渡し
// 2011/07/07 H.Osamoto		マツキヨ用API2.0対応版
// 2011/10/03 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/08/03 H.osamoto		禁則文字緩和対応(「'」「"」「>」「\」「`」（バッククォート）)を許可
// 2013/02/07 H.osamoto		禁則文字緩和の不具合対応
// ------------------------------------------------------------
// ------------------------------------------------------------
//
// グローバルで必ず実行するもの
//
// ------------------------------------------------------------
// 設定値の矛盾を解決 -----------------------------------------
// 各縮尺が最大・最小を超えてしまっている場合
// mod 2011/10/03 Y.Nakajima [
//define_action.incの内容をコピー
if(!isset($D_INIT_LVL))        $D_INIT_LVL        = 1;//初期表示
if(!isset($D_INIT_LVL_SEARCH)) $D_INIT_LVL_SEARCH = -1;//位置検索決定後（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
if(!isset($D_INIT_LVL_DETAIL)) $D_INIT_LVL_DETAIL = -1;//詳細選択後（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
if(!isset($D_INIT_LVL_PRINT))  $D_INIT_LVL_PRINT   = -1;//印刷画面（-1：$D_INIT_LVLに準じる）

if (isset($D_MAP_SCALE_MAX)) {
if($D_INIT_LVL < $D_MAP_SCALE_MAX)                                    $D_INIT_LVL = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_SEARCH != -1 && $D_INIT_LVL_SEARCH < $D_MAP_SCALE_MAX) $D_INIT_LVL_SEARCH = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_DETAIL != -1 && $D_INIT_LVL_DETAIL < $D_MAP_SCALE_MAX) $D_INIT_LVL_DETAIL = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_PRINT != -1 && $D_INIT_LVL_PRINT < $D_MAP_SCALE_MAX)   $D_INIT_LVL_PRINT = $D_MAP_SCALE_MAX;
}
if (isset($D_MAP_SCALE_MIN)) {
if($D_INIT_LVL > $D_MAP_SCALE_MIN)                                    $D_INIT_LVL = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_SEARCH != -1 && $D_INIT_LVL_SEARCH > $D_MAP_SCALE_MIN) $D_INIT_LVL_SEARCH = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_DETAIL != -1 && $D_INIT_LVL_DETAIL > $D_MAP_SCALE_MIN) $D_INIT_LVL_DETAIL = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_PRINT != -1 && $D_INIT_LVL_PRINT > $D_MAP_SCALE_MIN)   $D_INIT_LVL_PRINT = $D_MAP_SCALE_MIN;
}

/*
if($D_INIT_LVL < $D_MAP_SCALE_MAX) $D_INIT_LVL = $D_MAP_SCALE_MAX;
if($D_INIT_LVL > $D_MAP_SCALE_MIN) $D_INIT_LVL = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_SEARCH != -1 && $D_INIT_LVL_SEARCH < $D_MAP_SCALE_MAX) $D_INIT_LVL_SEARCH = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_SEARCH != -1 && $D_INIT_LVL_SEARCH > $D_MAP_SCALE_MIN) $D_INIT_LVL_SEARCH = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_DETAIL != -1 && $D_INIT_LVL_DETAIL < $D_MAP_SCALE_MAX) $D_INIT_LVL_DETAIL = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_DETAIL != -1 && $D_INIT_LVL_DETAIL > $D_MAP_SCALE_MIN) $D_INIT_LVL_DETAIL = $D_MAP_SCALE_MIN;
if($D_INIT_LVL_PRINT != -1 && $D_INIT_LVL_PRINT < $D_MAP_SCALE_MAX) $D_INIT_LVL_PRINT = $D_MAP_SCALE_MAX;
if($D_INIT_LVL_PRINT != -1 && $D_INIT_LVL_PRINT > $D_MAP_SCALE_MIN) $D_INIT_LVL_PRINT = $D_MAP_SCALE_MIN;
*/
// mod 2011/10/03 Y.Nakajima ]

if (!isset($D_REMOVE_QUOTE_PARAMS)) $D_REMOVE_QUOTE_PARAMS = array();		// add 2010/05/17 Y.Matsukawa
// パラメータの基本整形 ------------------------------------
foreach( $_POST as $key=>$val) {
	if (is_string($key) && is_string($val)) {		// add 2011/02/22 Y.Matsukawa
		$val = htmlspecialchars($val);
		//$val = addslashes($val);
		if($key!="") {
			// add 2010/04/08 Y.Matsukawa [
			// シングルクォート除去
			if ($val != "" && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
				//error_log("remove quote [$key][$val]", 3, "/var/tmp/php_debug.log");
				$val = mb_ereg_replace("'", "", $val);
				//error_log("->[$val] (".$_SERVER["SCRIPT_FILENAME"].")\n", 3, "/var/tmp/php_debug.log");
			}
			// add 2010/04/08 Y.Matsukawa ]
			${$key} = $val;
			$_POST[$key] = $val;
			$_VARS[$key] = $val;
		}
	}
}
foreach( $_GET as $key=>$val) {
	if (is_string($key) && is_string($val)) {		// add 2011/02/22 Y.Matsukawa
		$val = htmlspecialchars($val);
		//$val = addslashes($val);
		if($key!="") {
			// add 2010/04/08 Y.Matsukawa [
			// シングルクォート除去
			if ($val != "" && in_array($key, $D_REMOVE_QUOTE_PARAMS)) {
				//error_log("remove quote [$key][$val]", 3, "/var/tmp/php_debug.log");
				$val = mb_ereg_replace("'", "", $val);
				//error_log("->[$val] (".$_SERVER["SCRIPT_FILENAME"].")\n", 3, "/var/tmp/php_debug.log");
			}
			// add 2010/04/08 Y.Matsukawa ]
			${$key} = $val;
			$_GET[$key] = $val;
			$_VARS[$key] = $val;
		}
	}
}
if (isset($_VARS) && is_array($_VARS)) {
	$_VARS = array_merge($_VARS,$_SERVER);
} else {
	$_VARS = $_SERVER;
}

// テンプレート初期化 --------------------------------------
//asp/のファイルから呼ばれたときは、define.incをcallしていないので定義が無い
//asp/のファイルを全て修正するのは、手間なので、こちらで対応
// mod 2011/10/03 Y.Nakajima [
if (isset($D_CID)) {
$tpl["D_CID"] = $D_CID;		// add 2011/06/21 Y.Matsukawa
} else {
$tpl["D_CID"] = "";
}
if (isset($D_USER_DEFNAME)) {
$tpl["D_USER_DEFNAME"]      = $D_USER_DEFNAME;
} else {
$tpl["D_USER_DEFNAME"]      = "";
}
if (isset($D_USER_SERVICENAME)) {
$tpl["D_USER_SERVICENAME"]  = $D_USER_SERVICENAME;
} else {
$tpl["D_USER_SERVICENAME"]  = "";
}
// mod 2011/10/03 Y.Nakajima ]
//$tpl["D_DIR_BASE"]          = $D_DIR_BASE;		mod 2010/07/20 Y.Matsukawa
// mod 2011/10/03 Y.Nakajima [
if (isset($D_DIR_BASE_G)) {
$tpl["D_DIR_BASE"]          = $D_DIR_BASE_G;
} else {
$tpl["D_DIR_BASE"]          = "";
}
if (isset($D_DIR_COMPANY)) {
$tpl["D_DIR_COMPANY"]       = $D_DIR_COMPANY;
} else {
$tpl["D_DIR_COMPANY"]       = "";
}
if (isset($D_HISTORY_TOP_LINK)) {
$tpl["D_HISTORY_TOP_LINK"]  = $D_HISTORY_TOP_LINK;
} else {
$tpl["D_HISTORY_TOP_LINK"]  = "";
}
// mod 2011/10/03 Y.Nakajima ]
$tpl["_jsSearchWindow"]     = "ZdcEmapSearchClick()";
//自由項目(引数に指定して使う)
// mod 2011/05/23 K.Masuda [
//$tpl["P_STRING_1"]  = $p_s1;
//$tpl["P_STRING_2"]  = $p_s2;
//$tpl["P_STRING_3"]  = $p_s3;
//$tpl["P_STRING_4"]  = $p_s4;
//$tpl["P_STRING_5"]  = $p_s5;
//$tpl["P_STRING_6"]  = $p_s6;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_7"]  = $p_s7;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_8"]  = $p_s8;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_9"]  = $p_s9;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_STRING_10"] = $p_s10;		// add 2010/05/11 Y.Matsukawa
for($pcnt=1;$pcnt<=50;$pcnt++){
	// mod 2011/10/03 Y.Nakajima [
	if (isset(${"p_s".$pcnt})) {
		$tpl["P_STRING_".$pcnt]  = ${"p_s".$pcnt};
	} else {
		$tpl["P_STRING_".$pcnt]  = "";
	}
	// mod 2011/10/03 Y.Nakajima ]
}
//$tpl["P_FLG_1"]  = $p_f1;
//$tpl["P_FLG_2"]  = $p_f2;
//$tpl["P_FLG_3"]  = $p_f3;
//$tpl["P_FLG_4"]  = $p_f4;
//$tpl["P_FLG_5"]  = $p_f5;
//$tpl["P_FLG_6"]  = $p_f6;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_7"]  = $p_f7;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_8"]  = $p_f8;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_9"]  = $p_f9;		// add 2010/05/11 Y.Matsukawa
//$tpl["P_FLG_10"] = $p_f10;		// add 2010/05/11 Y.Matsukawa
for($pcnt=1;$pcnt<=50;$pcnt++){
	// mod 2011/10/03 Y.Nakajima [
	if (isset(${"p_f".$pcnt})) {
		$tpl["P_FLG_".$pcnt]  = ${"p_f".$pcnt};
	}else {
		$tpl["P_FLG_".$pcnt]  = "";
	}
	// mod 2011/10/03 Y.Nakajima ]
}
// mod 2011/05/23 K.Masuda ]
//自由項目（引き渡し用）		add 2009/02/23 Y.Matsukawa
//add 2011/10/03 Y.Nakajima [
if (!isset($p_s1)) $p_s1 = "";
if (!isset($p_s2)) $p_s2 = "";
if (!isset($p_s3)) $p_s3 = "";
if (!isset($p_s4)) $p_s4 = "";
if (!isset($p_s5)) $p_s5 = "";
if (!isset($p_f1)) $p_f1 = "";
if (!isset($p_f2)) $p_f2 = "";
if (!isset($p_f3)) $p_f3 = "";
if (!isset($p_f4)) $p_f4 = "";
if (!isset($p_f5)) $p_f5 = "";
//add 2011/10/03 Y.Nakajima ]

$P_FREEPARAMS = sprintf("p_s1=%s&p_s2=%s&p_s3=%s&p_s4=%s&p_s5=%s&p_f1=%s&p_f2=%s&p_f3=%s&p_f4=%s&p_f5=%s"
,urldecode(ZdcConvertEncoding($p_s1))
,urldecode(ZdcConvertEncoding($p_s2))
,urldecode(ZdcConvertEncoding($p_s3))
,urldecode(ZdcConvertEncoding($p_s4))
,urldecode(ZdcConvertEncoding($p_s5))
,urldecode(ZdcConvertEncoding($p_f1))
,urldecode(ZdcConvertEncoding($p_f2))
,urldecode(ZdcConvertEncoding($p_f3))
,urldecode(ZdcConvertEncoding($p_f4))
,urldecode(ZdcConvertEncoding($p_f5))
);
// mod 2011/05/23 K.Masuda [
//// add 2010/05/11 Y.Matsukawa [
//if($p_s6)  $P_FREEPARAMS .= "&p_s6=". urldecode(ZdcConvertEncoding($p_s6));
//if($p_s7)  $P_FREEPARAMS .= "&p_s7=". urldecode(ZdcConvertEncoding($p_s7));
//if($p_s8)  $P_FREEPARAMS .= "&p_s8=". urldecode(ZdcConvertEncoding($p_s8));
//if($p_s9)  $P_FREEPARAMS .= "&p_s9=". urldecode(ZdcConvertEncoding($p_s9));
//if($p_s10) $P_FREEPARAMS .= "&p_s10=".urldecode(ZdcConvertEncoding($p_s10));
for($pcnt=6;$pcnt<=50;$pcnt++){
	// mod 2011/10/03 Y.Nakajima
	//if(${p_s.$pcnt}) $P_FREEPARAMS .= "&p_s".$pcnt."=".urldecode(ZdcConvertEncoding(${p_s.$pcnt}));
	if(isset(${"p_s".$pcnt})) $P_FREEPARAMS .= "&p_s".$pcnt."=".urldecode(ZdcConvertEncoding(${"p_s".$pcnt}));
}
//if($p_f6)  $P_FREEPARAMS .= "&p_f6=". urldecode(ZdcConvertEncoding($p_f6));
//if($p_f7)  $P_FREEPARAMS .= "&p_f7=". urldecode(ZdcConvertEncoding($p_f7));
//if($p_f8)  $P_FREEPARAMS .= "&p_f8=". urldecode(ZdcConvertEncoding($p_f8));
//if($p_f9)  $P_FREEPARAMS .= "&p_f9=". urldecode(ZdcConvertEncoding($p_f9));
//if($p_f10) $P_FREEPARAMS .= "&p_f10=".urldecode(ZdcConvertEncoding($p_f10));
for($pcnt=6;$pcnt<=50;$pcnt++){
	// mod 2011/10/03 Y.Nakajima
	//if(${p_f.$pcnt}) $P_FREEPARAMS .= "&p_f".$pcnt."=".urldecode(ZdcConvertEncoding(${p_f.$pcnt}));
	if(isset(${"p_f".$pcnt})) $P_FREEPARAMS .= "&p_f".$pcnt."=".urldecode(ZdcConvertEncoding(${"p_f".$pcnt}));
}
// mod 2011/05/23 K.Masuda ]
// mod 2011/10/03 Y.Nakajima
if(isset($lm) && $lm && isset($D_MYAREA_USE) && $D_MYAREA_USE)    $P_FREEPARAMS .= "&lm=".urldecode(ZdcConvertEncoding($lm));	// add 2011/04/18 H.osamoto
// add 2010/05/11 Y.Matsukawa ]
// add 2010/05/13 Y.Matsukawa [
$wk_freeparams = array();
// mod 2011/05/23 K.Masuda [
//if($p_s1)  $wk_freeparams[] = "p_s1=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s1),'SJIS','EUC-JP'));
//if($p_s2)  $wk_freeparams[] = "p_s2=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s2),'SJIS','EUC-JP'));
//if($p_s3)  $wk_freeparams[] = "p_s3=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s3),'SJIS','EUC-JP'));
//if($p_s4)  $wk_freeparams[] = "p_s4=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s4),'SJIS','EUC-JP'));
//if($p_s5)  $wk_freeparams[] = "p_s5=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s5),'SJIS','EUC-JP'));
//if($p_s6)  $wk_freeparams[] = "p_s6=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s6),'SJIS','EUC-JP'));
//if($p_s7)  $wk_freeparams[] = "p_s7=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s7),'SJIS','EUC-JP'));
//if($p_s8)  $wk_freeparams[] = "p_s8=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s8),'SJIS','EUC-JP'));
//if($p_s9)  $wk_freeparams[] = "p_s9=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s9),'SJIS','EUC-JP'));
//if($p_s10) $wk_freeparams[] = "p_s10=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_s10),'SJIS','EUC-JP'));
for($pcnt=1;$pcnt<=50;$pcnt++){
	// mod 2011/10/03 Y.Nakajima
	//if(${p_s.$pcnt}) $wk_freeparams[] = "p_s".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${p_s.$pcnt}),'SJIS','EUC-JP'));
	if(isset(${"p_s".$pcnt})) $wk_freeparams[] = "p_s".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${"p_s".$pcnt}),'SJIS','eucJP-win'));
}
//if($p_f1)  $wk_freeparams[] = "p_f1=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f1),'SJIS','EUC-JP'));
//if($p_f2)  $wk_freeparams[] = "p_f2=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f2),'SJIS','EUC-JP'));
//if($p_f3)  $wk_freeparams[] = "p_f3=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f3),'SJIS','EUC-JP'));
//if($p_f4)  $wk_freeparams[] = "p_f4=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f4),'SJIS','EUC-JP'));
//if($p_f5)  $wk_freeparams[] = "p_f5=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f5),'SJIS','EUC-JP'));
//if($p_f6)  $wk_freeparams[] = "p_f6=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f6),'SJIS','EUC-JP'));
//if($p_f7)  $wk_freeparams[] = "p_f7=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f7),'SJIS','EUC-JP'));
//if($p_f8)  $wk_freeparams[] = "p_f8=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f8),'SJIS','EUC-JP'));
//if($p_f9)  $wk_freeparams[] = "p_f9=". rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f9),'SJIS','EUC-JP'));
//if($p_f10) $wk_freeparams[] = "p_f10=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding($p_f10),'SJIS','EUC-JP'));
for($pcnt=1;$pcnt<=50;$pcnt++){
	// mod 2011/10/03 Y.Nakajima
	//if(${p_f.$pcnt}) $wk_freeparams[] = "p_f".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${p_f.$pcnt}),'SJIS','EUC-JP'));
	if(isset(${"p_f".$pcnt})) $wk_freeparams[] = "p_f".$pcnt."=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding(${"p_f".$pcnt}),'SJIS','eucJP-win'));
}
// mod 2011/05/23 K.Masuda ]
// mod 2011/10/03 Y.Nakajima
if(isset($lm) && $lm && isset($D_MYAREA_USE) && $D_MYAREA_USE) $wk_freeparams[] = "lm=".rawurlencode(mb_convert_encoding(ZdcConvertEncoding($lm),'SJIS','eucJP-win'));	// add 2011/04/18 H.osamoto
$P_FREEPARAMS_SJIS = '';
if (count($wk_freeparams)) $P_FREEPARAMS_SJIS = implode("&", $wk_freeparams);
unset($wk_freeparams);
// add 2010/05/13 Y.Matsukawa ]

// ------------------------------------------------------------
//
// 拠点関係
//
// ------------------------------------------------------------
//詳細表示用データの取得
function ZdcSearchCgiKyotenid($kid,$type = 1,$putLog = true){
	GLOBAL $cid,$D_CID,$D_SSAPI,$D_SSAPI_KEY,$D_MOBILE_URL,$D_QRIMG_URL,$D_QRIMG_E,$D_QRIMG_V,$D_QRIMG_S,$D_KYO_COL_NAME,$D_SOCKET_TIMEOUT;
	global $P_FREEPARAMS_SJIS, $D_FREEPARAMS_TO_MBURL;		// 2010/05/13 Y.Matsukawa
	
	//CGIへアクセス
	if ($putLog) {
		$cgi = $D_SSAPI["kyotenid"];
	} else {
		$cgi = $D_SSAPI["kyotenid_nolog"];
	}
	$url = sprintf("%s?key=%s&cid=%s&opt=%s&kid=%s&type=%s",$cgi,$D_SSAPI_KEY,$D_CID,$cid,$kid,$type);
	$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
	//戻り値の解釈
	$cnt = count($dat);
	if($cnt < 2) return false;//エラー
	$rec = ZdcConvertEncoding($dat[1]);
	$rec = explode("\t",$rec);
	//値の作成
	$tpl["kid"]  = $kid;
	$tpl["lat"]  = $rec[0];
	$tpl["lon"]  = $rec[1];
	$tpl["icon"] = $rec[2];
	// mod 2011/10/03 Y.Nakajima [
	if(isset($rec[3]) && intval($rec[3])) {
		$tpl["gifflg"]= "1";
	} else {
		$tpl["gifflg"]= "";
	}
	if(isset($rec[4]) && intval($rec[4])) {
		$tpl["new"] = "1";
	} else {
		$tpl["new"] = "";
	}
	// mod 2011/10/03 Y.Nakajima ]
	//for($i = 0;$i < 52;$i ++) {		mod 2010/03/09 Y.Matsukawa
	for($i = 0;$i < 202;$i ++) {
		// add 2011/10/03 Y.Nakajima [
		if (isset($D_KYO_COL_NAME[$type][$i])) {
		// add 2011/10/03 Y.Nakajima ]
		$col = $D_KYO_COL_NAME[$type][$i];
		// mod 2011/10/03 Y.Nakajima [
		if (isset($rec[5+$i])) {
			$d = $rec[5+$i];
		} else {
			$d = "";
		}
		// mod 2011/10/03 Y.Nakajima ]
		if ($col != '') {		// add 2009/09/04 Y.Matsukawa
			// del 2011/10/03 Y.Nakajima
			//$d = $rec[5+$i];
			$tpl[$col] = $d;
			if($d) $tpl[$col."l".$d] = "1";
			if(intval($d) == 1) $tpl[$col."b"] = "1";
			if($col == 'name') $tpl['name_enc'] = urlencode($d);		// add 2010/09/13 Y.Matsukawa
		// add 2009/09/04 Y.Matsukawa [
		} else {
			// del 2011/10/03 Y.Nakajima
			//$d = $rec[5+$i];
			if (ctype_digit($d) && 1 <= $d && $d <= 18) {
				$tpl['kyoten_lvl'] = $d;
				if($d) $tpl['kyoten_lvl'.$d] = "1";
			}
			break;
		}
		// add 2011/10/03 Y.Nakajima [
		}
		// add 2011/10/03 Y.Nakajima ]
		// add 2009/09/04 Y.Matsukawa ]
	}
	// add 2011/10/03 Y.Nakajima
	if (!isset($tpl['kyoten_lvl'])) $tpl['kyoten_lvl'] = "";
	
	
	//$tpl["iconimg"]   = sprintf("%s?cid=%s&icon_id=%s",$D_SSAPI["icon_select"],$D_CID,$tpl["icon"]);		mod 2010/07/20 Y.Matsukawa
	$tpl["iconimg"]   = sprintf("%s?cid=%s&icon_id=%s",$D_SSAPI["icon_select_g"],$D_CID,$tpl["icon"]);
	$tpl["gifimg"]    = sprintf("%s?cid=%s&kid=%s",$D_SSAPI["gif_select"],$D_CID,$kid);
	//$tpl["mobileurl"] = sprintf("%s?kid=%s",$D_MOBILE_URL,$kid);		mod 2010/07/06 Y.Matsukawa
	$tpl["mobileurl"] = sprintf("%s?kid=%s&",$D_MOBILE_URL,$kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobileurl"] .= "&".$P_FREEPARAMS_SJIS;		// add 2010/05/13 Y.Matsukawa
	$tpl["mobileurl_encode"] = urlencode($tpl["mobileurl"]);
	//$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode($tpl["mobileurl"]));		mod 2010/05/13 Y.Matsukawa
	$tpl["qrimgurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode(urlencode($tpl["mobileurl"])));
	// add 2009/06/17 Y.Matsukawa [
	$tpl["mobiledtlurl"] = sprintf("%s?ksid=%s",$D_MOBILE_URL,$kid);
	if ($D_FREEPARAMS_TO_MBURL && $P_FREEPARAMS_SJIS) $tpl["mobiledtlurl"] .= "&".$P_FREEPARAMS_SJIS;		// add 2010/05/13 Y.Matsukawa
	$tpl["mobiledtlurl_encode"] = urlencode($tpl["mobiledtlurl"]);
	//$tpl["qrimgdtlurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode($tpl["mobiledtlurl"]));		mod 2010/05/13 Y.Matsukawa
	$tpl["qrimgdtlurl"]  = sprintf("%s?cid=%s&d=%s",$D_QRIMG_URL,$D_CID,urlencode(urlencode($tpl["mobiledtlurl"])));
	// add 2009/06/17 Y.Matsukawa ]
	//$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["icon_select"],$D_CID);		mod 2010/07/20 Y.Matsukawa
	$tpl["_cgiIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["icon_select_g"],$D_CID);
	$tpl["_cgiSysIconimg"] = sprintf("%s?cid=%s&icon_id=",$D_SSAPI["sys_icon_select"],$D_CID);
	$tpl["_cgiGifimg"]  = sprintf("%s?cid=%s&kid=",$D_SSAPI["gif_select"],$D_CID);
	$tpl["_jsMsg"]    = sprintf("ZdcEmapShopMsg(null)",$kid);
	$tpl["_jsMove"]   = sprintf("ZdcEmapMapMove('%s','%s')",$rec[0],$rec[1]);
	//	$tpl["_jsScroll"] = sprintf("ZdcEmapMapScroll('%s','%s')",$rec[0],$rec[1]);		mod 2011/07/07 H.osamoto
	$tpl["_jsScroll"] = sprintf("ZdcEmapMapScroll('%s','%s')",cnv_dms2hour($rec[0]),cnv_dms2hour($rec[1]));
	//$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s');",$kid,$rec[0],$rec[1],$rec[2],$tpl["new"]);		mod 2009/09/04 Y.Matsukawa
	//$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s','%s');",$kid,$rec[0],$rec[1],$rec[2],$tpl["new"],$tpl['kyoten_lvl']);		mod 2011/07/07 H.osamoto
	$tpl["_jsDetail"] = sprintf("ZdcEmapShopDetailKidClick('%s','%s','%s','%s','%s','%s');",$kid,cnv_dms2hour($rec[0]),cnv_dms2hour($rec[1]),$rec[2],$tpl["new"],$tpl['kyoten_lvl']);
	//$tpl["_jsNeki"]   = sprintf("ZdcEmapStationClick('%s','%s')",$rec[0],$rec[1]);	mod 2011/07/07 H.osamoto
	$tpl["_jsNeki"]   = sprintf("ZdcEmapStationClick('%s','%s')",cnv_dms2hour($rec[0]),cnv_dms2hour($rec[1]));
	//$tpl["_jsFreeRoute"] = sprintf("ZdcEmapFreeRouteClick('%s','%s')",$rec[0],$rec[1]);		// add 2010/06/16 Y.Matsukawa	mod 2011/07/07 H.Osamoto
	$tpl["_jsFreeRoute"] = sprintf("ZdcEmapFreeRouteClick('%s','%s')",cnv_dms2hour($rec[0]),cnv_dms2hour($rec[1]));
	$tpl["_jsFreeRouteLight"] = sprintf("ZdcEmapFreeRouteClickLight('%s','%s')",$rec[0],$rec[1]);		// add 2010/09/07 Y.Matsukawa
	$tpl["_jsPrint"]  = sprintf("ZdcEmapShopPrintClick('%s')",$kid);
	$tpl["_urlPrint"] = sprintf("./print.htm?cid=%s&kid=%s",$cid,$kid);
	$tpl["_jsSearch"] = "ZdcEmapSearchNpoi()";
	$tpl["_jsDetailNpoi"]   = "ZdcEmapShopDetailNpoiClick()";
	
	return $tpl;
}


// ------------------------------------------------------------
//
// 文字コード変換 
//  mb_convert_encodingにバグがあったら拡張していく
//
// ------------------------------------------------------------
function ZdcConvertEncoding($text) {
	GLOBAL $enc;

	// mod 2011/10/03 Y.Nakajima [
	// 〜が~に置き換えられる
	//if($enc) $tmp = $enc;
	//	else $tmp = "EUC-JP,UTF-8,SJIS,auto";
	//return mb_convert_encoding($text,"EUC",$tmp);
	if(isset($enc) && $enc != "") $tmp = $enc;
		else $tmp = "eucJP-win,UTF-8,SJIS-win,auto";
	if ($tmp == "EUC" || $tmp == "euc" || $tmp == "EUC-JP") $tmp ="eucJP-win";
	return mb_convert_encoding($text,"eucJP-win",$tmp);
	// mod 2011/10/03 Y.Nakajima ]
}

// ------------------------------------------------------------
//
// 特殊なHTMLエンティティを文字に戻す
//  htmlspecialchars_decode(PHP5)の代替
//  クォートには非対応
//
// ------------------------------------------------------------
function zdc_htmlspecialchars_decode($text) {
	$ret = $text;
	$ret = str_replace("&amp;", "&", $ret);
	$ret = str_replace("&lt;",  "<", $ret);
	$ret = str_replace("&gt;",  ">", $ret);
	return $ret;
}

// ------------------------------------------------------------
//
// JavaScriptのリテラル値用エスケープ処理
//
// ------------------------------------------------------------
function zdc_js_encode($text) {
	$ret = $text;
	$ret = str_replace("\\", "\\\\", $ret);
	$ret = str_replace("'",  "\\'",  $ret);
	$ret = str_replace('"',  '\\"',  $ret);
	return $ret;
}

// ------------------------------------------------------------
//
// 住所フリーワード検索結果ソート関数
//
//
// ------------------------------------------------------------
function GEOAccess_cmp_sflg($a,$b){
	// full比較 1:完全一致が優先
	if( $a["full"] > $b["full"] ) return -1;
	if( $a["full"] < $b["full"] ) return 1;

	// adid文字列長比較
	// adidにはAB等の16進符号が使用されているのでまず文字列長の比較を行う
	if( strlen($a["adid"]) > strlen($b["adid"]) )		return 1;
	if( strlen($a["adid"]) < strlen($b["adid"]) )		return -1;

	// adid内容比較
	// adidを文字列として扱い比較をする為 strcmp を使用して比較
	// 比較結果はそのままreturn
	return strcmp( $a['adid'], $b['adid'] );
}

// ------------------------------------------------------------
//
// ログ関係
// 出力内容
//  1.基本
//    script cid opt refferer status service
//  2.emapview
//    kid lat lon type keyword adcd area col nm no cond
//  3.search
//    page jnrmn jnr jkn 
//
// ------------------------------------------------------------
function ZdcLogPut($status) {
	GLOBAL $_VARS,$LOG_MODE;
	//include_once("/home/emap/httpd/log/inc/com_log_open.inc");		mod 2010/04/19 Y.Matsukawa
	include_once("/home/emap/src/log/inc/com_log_open.inc");
	// add 2011/10/03 Y.Nakajima
	if (!isset($cond)) $cond = "";
	
	//絞込み条件の加工
	//for($i = 0;$i < 50;$i ++) {		mod 2009/11/07 Y.Matsukawa
	for($i = 1;$i <= 200;$i ++) {
		// mod 2011/10/03 Y.Nakajima
		if(isset($_VARS["cond".$i]) && $_VARS["cond".$i]) {
			// mod 2011/10/03 Y.Nakajima
			if($cond != "") $cond .= ",";
			$cond .= sprintf("cond%d=%s",$i,$_VARS["cond".$i]);
		}
	}
	//128バイトに丸める
	//$cond = mb_strimwidth($cond, 0, 256, '...');		// add 2009/09/08 Y.Matsukawa	mod 2009/09/14 Y.Matsukawa
	$cond = mb_strimwidth($cond, 0, 128, '...');
	$cond = mb_ereg_replace(' ','_',$cond);			// add 2010/10/01 Y.Matsukawa
	//ログ内容
	//$prm  = sprintf("%s %s %s %s %s ",$status,$_VARS["kid"],$_VARS["lat"],$_VARS["lon"],$_VARS["zpoint"]);	mod 2010/10/01 Y.Matsukawa
	// add 2011/10/03 Y.Nakajima [
	if (!isset($_VARS["kid"]))     $_VARS["kid"] = "";
	if (!isset($_VARS["lat"]))     $_VARS["lat"] = "";
	if (!isset($_VARS["lon"]))     $_VARS["lon"] = "";
	if (!isset($_VARS["zpoint"]))  $_VARS["zpoint"] = "";
	if (!isset($_VARS["type"]))    $_VARS["type"] = "";
	if (!isset($_VARS["keyword"])) $_VARS["keyword"] = "";
	if (!isset($_VARS["adcd"]))    $_VARS["adcd"] = "";
	if (!isset($_VARS["area"]))    $_VARS["area"] = "";
	if (!isset($_VARS["col"]))     $_VARS["col"] = "";
	if (!isset($_VARS["nm"]))      $_VARS["nm"] = "";
	if (!isset($_VARS["icn"]))     $_VARS["icn"] = "";
	if (!isset($_VARS["page"]))    $_VARS["page"] = "";
	if (!isset($_VARS["slogflg"])) $_VARS["slogflg"] = "";
	// add 2011/10/03 Y.Nakajima ]
	$prm  = sprintf("%s %s %s %s %s "
					,$status
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["kid"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["lat"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["lon"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["zpoint"]), 0, 128, '...')
	);
	// del 2010/01/18 Y.Matsukawa [
	//	$prm .= sprintf("%s %s %s %s %s ",$_VARS["type"],$_VARS["keyword"],$_VARS["adcd"],$_VARS["area"],$_VARS["col"]);
	//	//$prm .= sprintf("%s %s %s %s %s ",$_VARS["nm"],$_VARS["icn"],$cond,$_VARS["page"],"");
	//	$prm .= sprintf("%s %s %s %s %s ",$_VARS["nm"],$_VARS["icn"],$cond,$_VARS["page"],$_VARS["slogflg"]);
	// del 2010/01/18 Y.Matsukawa ]
	// del 2010/10/01 Y.Matsukawa [
	//	// add 2010/01/18 Y.Matsukawa ]
	//	$prm .= sprintf("%s %s %s %s %s "
	//					,$_VARS["type"]
	//					//,mb_ereg_replace(' ','_',$_VARS["keyword"])		mod 2010/02/10 Y.Matsukawa
	//					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["keyword"]), 0, 128, '...')
	//					,$_VARS["adcd"]
	//					,$_VARS["area"]
	//					,$_VARS["col"]
	//	);
	//	$prm .= sprintf("%s %s %s %s %s "
	//					//,mb_ereg_replace(' ','_',$_VARS["nm"])		mod 2010/02/10 Y.Matsukawa
	//					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["nm"]), 0, 128, '...')
	//					,$_VARS["icn"]
	//					,$cond
	//					,$_VARS["page"]
	//					,$_VARS["slogflg"]
	//	);
	//	// add 2010/01/18 Y.Matsukawa ]
	// del 2010/10/01 Y.Matsukawa ]
	// add 2010/10/01 Y.Matsukawa [
	$prm .= sprintf("%s %s %s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["type"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["keyword"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["adcd"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["area"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["col"]), 0, 128, '...')
	);
	$prm .= sprintf("%s %s %s %s %s "
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["nm"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["icn"]), 0, 128, '...')
					,$cond
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["page"]), 0, 128, '...')
					,mb_strimwidth(mb_ereg_replace(' ','_',$_VARS["slogflg"]), 0, 128, '...')
	);
	// add 2010/10/01 Y.Matsukawa ]
	$prm = str_replace("\n","",$prm);
	$prm = str_replace("\r","",$prm);
	
	// ログ出力
	// mod 2011/10/03 Y.Nakajima [
	if (isset($log_pc)) {
		$log_pc->info($prm);
	}
	// mod 2011/10/03 Y.Nakajima ]
	
	//include_once("/home/emap/httpd/log/inc/com_log_close.inc");		mod 2010/04/19 Y.Matsukawa
	include_once("/home/emap/src/log/inc/com_log_close.inc");
}

// add 2009/08/24 Y.Matsukawa
// ------------------------------------------------------------
// IPチェック
// ------------------------------------------------------------
function ip_check() {
	global $D_ALLOW_IP;
	global $D_DEFAULT_ALLOW_IP;
	
	if ($D_ALLOW_IP == '') return true;
	
	$REMOTE_ADDR = $_SERVER['REMOTE_ADDR'];
	
	$ip_list = array_merge(explode(';', $D_ALLOW_IP), $D_DEFAULT_ALLOW_IP);

	foreach ($ip_list as $i=>$ip) {
		// IPアドレス指定（xxx.xxx.xxx.xxx）
		if (preg_match("/^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$/", $ip)) {
			if (strcmp($REMOTE_ADDR, $ip) == 0) return true;
		// IPアドレス＆サブネットマスク指定（xxx.xxx.xxx.xxx/xx）
		} else if (preg_match("/^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\/([0-9]{1,2})$/", $ip)) {
			// mod 2011/07/05 Y.Nakajima
			//$res = split('[/.]', $ip);
			$res = explode('[/.]', $ip);
			$w_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			$mask = intval($res[4]);
			$shift = 32 - $mask;
			// mod 2011/07/05 Y.Nakajima
			//$res = split('[/.]', $REMOTE_ADDR);
			$res = explode('[/.]', $REMOTE_ADDR);
			$r_ip = (intval($res[0]) << 24 ) + (intval($res[1]) << 16 ) + (intval($res[2]) << 8 ) + intval($res[3]);
			if (($w_ip >> $shift) == ($r_ip >> $shift)) return true;
		}
	}

	return false;
}
// add 2011/04/18 H.Osamoto
// ------------------------------------------------------------
// 機種依存文字チェック
// (EUC-JP：第一水準、第二水準のみ許容)
// ------------------------------------------------------------
function IzonSearch( $str ) {

	// ３バイト文字（JIS X 212 補助漢字）が含まれていたらエラー
	// ※補助漢字がそのまま送信されてきた場合は、ここでフックされます
	// （IE以外のブラウザからの送信や、CSVファイルアップロード等）
	if (preg_match('/(\x8F[\xA1-\xFE][\xA1-\xFE])/', $str)) {
		return false;
	}

	// パーセントエンコードされた３バイト文字（JIS X 212 補助漢字）が含まれていたらエラー
	// ※IEなどから、補助漢字がエンコードされて送信されてきた場合は、ここでフックされます
	// （例）「&#28583;」「&AElig;」
	if (preg_match('/(&#[0-9]{1,};|&[a-zA-Z]{1,};)/', $str)) {
		return false;
	}

	// 半角カナを全角カナに変換（半角カナが混在していると、全角文字抜き出しに失敗するため） 2007/08/13 add Y.Matsukawa
	$w_str = mb_convert_kana($str, 'K');

	// 全角文字の抜き出し
	preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $w_str, $matchword );

	for ( $i=0; $i < count( $matchword[0] ) ; $i++) {
		if ( $matchword[0][$i] ) {
			// EUC-JP  第一水準、第二水準の文字チェック
			if ( ! preg_match( '/^(([\xA1-\xA8]|[\xB0-\xF4])[\xA1-\xFE])*$/', $matchword[0][$i]) ) {
				return false;
			}
		}
	}
	return true;
}

// add 2012/08/03 H.Osamoto
// ------------------------------------------------------------
// HTML表示用変換処理
// ------------------------------------------------------------
function zdcHtmlspecialchars_arr($obj) {
	
	foreach($obj as $key => $val) {
		if (preg_match('/^name$|^addr$/', $key)) {
			$obj[$key] = zdcHtmlspecialchars_nameaddr($val);
		} else if (preg_match('/^col_[0-9][0-9]+$/', $key)) {
			$obj[$key] = zdcHtmlspecialchars_col($val);
		} else {
			$obj[$key] = $val;
		}
	}
	
	return $obj;
}

function zdcHtmlspecialchars($target, $col_name) {
	
	if (preg_match('/^name$|^addr$/', $col_name)) {
		$ret = zdcHtmlspecialchars_nameaddr($target);
	} else if (preg_match('/^col_[0-9][0-9]+$/', $col_name)) {
		$ret = zdcHtmlspecialchars_col($target);
	} else {
		$ret = $target;
	}
	
	return $ret;
}

function zdcHtmlspecialchars_nameaddr($target) {
	
	$ret = htmlreplace($target);
	
	return $ret;
}

function zdcHtmlspecialchars_col($target) {
	
	$tag_list = array('<a ', '<img ', '</a>', '<br>', '<br/>', '<b>', '</b>');	// 許可タグリスト
	$arr_rep = array();
	$rep_cnt = 0;
	
	$target;
	
	foreach ($tag_list as $key => $tag) {
		$start = 0;
		$stop = 0;
		while(1) {
			if (strpos($target, '<', $start) === false) break;	// 「<」が存在しない場合は処理しない
			
			// 許可タグチェック
			$start = strpos(strtolower($target), strtolower($tag), $start);
			
			if ($start !== false) {
				// 許可タグが存在する場合
				$stop = strpos(strtolower($target), ">", $start);
				$rep_cnt++;
				
				// 置換対象を一時的に配列に格納
				$arr_rep[$rep_cnt] = substr($target, $start, $stop - $start + 1);
				
				// 変換しない許可タグを一時的に置換
				$target = substr($target, 0, $start) . "@REP" . $rep_cnt . "@" . substr($target, $stop + 1);
				
				// 2013/02/07 H.osamoto mod [
				//	// 開始位置をずらして続きを実行
				//	$start = $stop;
				// 都度リセットして再実行
				$start = 0;
				// 2013/02/07 H.osamoto mod ]
			} else {
				// 許可タグが存在しない場合
				// 次のタグチェック
				break;
			}
		}
	}
	
	$target = htmlreplace($target);
	
	// 変換しておいた許可タグを元に戻す
	for ($i = 1; $i <= $rep_cnt; $i++) {
		$target = str_replace("@REP".$i."@", $arr_rep[$i], $target);
	}
	
	return $target;
}

function htmlreplace($target) {
	// HTML表示用に置換
	$search  = array('&', '"', '\'', '\\', '<', '>');	// 置換対象
	$replace = array('&amp;', '&quot;', '&#039;', '&yen;', '&lt;', '&gt;');	// 置換後文字列
	
	$target = str_replace($search, $replace, $target);
	
	return $target;
}

?>
