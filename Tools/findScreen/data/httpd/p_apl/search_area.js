<?PHP
// ------------------------------------------------------------
// 地域図
// 
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2014/02/05 Y.Matsukawa	クロスサイトスクリプティング対策
// 2016/08/05 Y.Uesugi		市区町村を地図画面に渡す処理を追加
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>
//地域図表示
var ZdcEmapArea;
function ZdcEmapSearchAreaDisp(todCode,name,prm){
	ZdcEmapArea = new ZDC.AreaMap(
				{
					todCode: todCode,
					callback: ZdcEmapSearchAreaClick,
					areaMap: document.getElementById('ZdcEmapSearchArea')
				}
	);
	ZDC._callback = function(){};
}
//地域図クリック時に動作
var ZdcEmapSearchAreaClick = function(rtn) {
	// 地域図をクリックした位置を取得して地図を移動
	location.href = "<?php echo $D_DIR_BASE_G; ?>nmap.htm?lat="+rtn.latlon.lat+"&lon="+rtn.latlon.lon
					<?php if (isset($D_SEARCH_AREA_CITY) && $D_SEARCH_AREA_CITY) { ?> +"&city="+rtn.cityName <?php } ?>			// add 2016/08/05 Y.Uesugi
					+"<?php echo ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:''); ?>"
					//+"<?php echo ($condprm?'&'.$condprm:''); ?>"		mod 2014/02/05 Y.Matsukawa
					+"<?php echo ($condprm_enc?'&'.$condprm_enc:''); ?>"
					+"<?php echo ($his?'&his='.urlencode($his):''); ?>";
}
