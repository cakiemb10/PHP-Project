<?php
// ------------------------------------------------------------
// アイコン定義をcgiから取得する
// 
// 開発履歴
// 2007/06/12 bando@D&I
//     新規開発
// 2008/12/18 Y.Matsukawa	Maplinkのデフォルトアイコン（☆）を追加
// 2010/07/20 Y.Matsukawa	SSL対応
// 2011/10/03 Y.nakajima	VM化に伴うapache,phpVerUP対応改修  
// ------------------------------------------------------------
//-------------------
// アイコン情報
//-------------------
$url = sprintf("%s?cid=%s",$D_SSAPI["get_icon_info"],$D_CID);
$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
//echo $url;print_r($dat);
if($dat) {
	//デフォルト値
	$D_ICON["@SHOP"]["IMG"] = $D_ICON_SHOP_IMG;		// add 2008/12/18 Y.Matsukawa
	$D_ICON["@SHOP"]["W"] = $D_ICON_SHOP_W;			// add 2008/12/18 Y.Matsukawa
	$D_ICON["@SHOP"]["H"] = $D_ICON_SHOP_H;			// add 2008/12/18 Y.Matsukawa
	$D_ICON["@NEW"]["IMG"] = $D_ICON_NEW_IMG;
	$D_ICON["@NEW"]["W"] = $D_ICON_NEW_W;
	$D_ICON["@NEW"]["H"] = $D_ICON_NEW_H;
	$D_ICON["@SEL"]["IMG"] = $D_ICON_FOCUS_IMG;
	$D_ICON["@SEL"]["W"] = $D_ICON_FOCUS_W;
	$D_ICON["@SEL"]["H"] = $D_ICON_FOCUS_H;
	$D_ICON["@SELB"]["IMG"] = $D_ICON_CURSOR_IMG;
	$D_ICON["@SELB"]["W"] = $D_ICON_CURSOR_W;
	$D_ICON["@SELB"]["H"] = $D_ICON_CURSOR_H;
	//アイコン情報を書き換え
	//$cgi = $D_SSAPI["icon_select"];		mod 2010/07/20 Y.Matsukawa
	$cgi = $D_SSAPI["icon_select_g"];
	$status = explode("\t",$dat[0]);
	$cnt = $status[1];
	for($i = 0;$i < $cnt;$i ++) {
		$rec = explode("\t",$dat[$i+1]);
		//mod 2011/10/03 Y.Nakajima [ 
		if (isset($rec[1])) {
			$tmp = $rec[1];
		} else {
			$tmp = "";
		}
		//mod 2011/10/03 Y.Nakajima ] 
		$D_ICON[$tmp]["IMG"] = sprintf("%s?cid=%s&icon_id=%s",$cgi,$D_CID,$tmp);
		//mod 2011/10/03 Y.Nakajima [
		if(isset($rec[0]) && $rec[0] != 0) $D_ICON[$tmp]["IMG"] .= ".gif";//「.gif」を付けないとAPIがGIFと判断しないため ※拠点は除外
		if (isset($rec[2]) && $rec[2] != "") {
			$D_ICON[$tmp]["W"]   = $rec[2];
		} else {
			$D_ICON[$tmp]["W"]   = "";
		}
		if (isset($rec[3]) && $rec[3] != "") {
			$D_ICON[$tmp]["H"]   = $rec[3];
		} else {
			$D_ICON[$tmp]["H"]   = "";
		}
		//mod 2011/10/03 Y.Nakajima ] 
		//旧データに対応するため無理やりデフォルト値をつっこむ そのうち消す事
		if(!intval($D_ICON[$tmp]["W"])) $D_ICON[$tmp]["W"]   = 28;
		if(!intval($D_ICON[$tmp]["H"])) $D_ICON[$tmp]["H"]   = 28;
	}
}
?>
