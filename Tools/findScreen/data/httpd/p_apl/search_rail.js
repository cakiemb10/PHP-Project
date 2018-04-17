<?PHP
// ------------------------------------------------------------
// 路線図
// 
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2014/02/05 Y.Matsukawa	クロスサイトスクリプティング対策
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>
//路線図表示
var ZdcEmapRail;
function ZdcEmapSearchRailwayDisp(mapNo,x,y,prm){
	ZdcEmapRail = new ZDC.RailwayMap(
				{
					mapNo: mapNo,
					callback: ZdcEmapSearchRailClick,
					mainMap: document.getElementById('ZdcEmapSearchRailwayMain'),
					subMap: document.getElementById('ZdcEmapSearchRailwaySub')
				}
	);
}
//路線図クリック時に動作
var ZdcEmapSearchRailClick = function(rtn) {
	// 路線図をクリックした位置を取得して地図を移動
	location.href = "<?php echo $D_DIR_BASE_G; ?>nmap.htm?lat="+rtn.latlon.lat+"&lon="+rtn.latlon.lon
					+"<?php echo ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:''); ?>"
					//+"<?php echo ($condprm?'&'.$condprm:''); ?>"		mod 2014/02/05 Y.Matsukawa
					+"<?php echo ($condprm_enc?'&'.$condprm_enc:''); ?>"
					+"<?php echo ($his?'&his='.urlencode($his):''); ?>";
}
