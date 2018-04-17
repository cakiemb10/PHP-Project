<?PHP
// ------------------------------------------------------------
// Google Maps版 印刷画面
//
// 2013/10/02 Y.Matsukawa	新規作成
// 2016/08/16 Y.Matsukawa	世界測地系保持
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>

<?php //function ZdcEmapPrintInit(lat,lon,icnno,nflg,lvl)		mod 2016/08/16 Y.Matsukawa ?>
function ZdcEmapPrintInit(lat, lon, icnno, nflg, lvl, wgs)
{
	if (!ZdcEmapMapObj) return;
	
	//地図を印刷モードにする
	ZdcEmapMapObj.ZdcEmapMode = "print";

	//初期縮尺変更
	if (lvl && lvl != 0) {
		ZdcEmapMapObj.setZoom(lvl + ZdcEmapZoomOffset);
	} else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) {
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_PRINT; ?> + ZdcEmapZoomOffset);
	}
	
	//拠点アイコンの描画
	<?php //ZdcEmapShopIcon(lat,lon,icnno,nflg);		mod 2016/08/16 Y.Matsukawa ?>
	ZdcEmapShopIcon(lat, lon, icnno, nflg, false, wgs);

//	//最寄拠点を検索するかどうかのフラグ
//	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//最寄検索をする
}
