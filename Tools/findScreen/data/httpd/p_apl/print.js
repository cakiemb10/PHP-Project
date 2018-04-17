<?PHP
// ------------------------------------------------------------
// 印刷画面
//
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2012/04/02 K.Masuda		地図中心マーク処理追加
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>

function ZdcEmapPrintInit(lat,lon,icnno,nflg,lvl)
{
	//地図を印刷モードにする
	ZdcEmapMapObj.ZdcEmapMode = "print";

	//地図中心マーク ---------------------------------
	<?php if (isset($D_MAPCENTER_MARK) && $D_MAPCENTER_MARK) { ?>
//	ZdcEmapMapObj.removeMapCenter();
	ZdcEmapMapObj.removeWidget(widget2);	// add 2012/04/02 K.Masuda
	<?php } ?>
	<?php if (isset($D_MAPCENTER_MARK_P) && $D_MAPCENTER_MARK_P) { ?>
//	ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK_P; ?>'));
	// add 2012/04/02 K.Masuda [
	widget3 = new ZDC.MapCenter();
	ZdcEmapMapObj.addWidget(widget3);
	// add 2012/04/02 K.Masuda ]
	<?php } ?>

	//初期縮尺変更
	if (lvl && lvl != 0) {
		//ZdcEmapMapObj.setMapScale(lvl);
		ZdcEmapMapObj.setZoom(lvl-1);
	} else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) {
		//ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_PRINT; ?>);
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_PRINT; ?>-1);
	}
	
	//拠点アイコンの描画
	ZdcEmapShopIcon(lat,lon,icnno,nflg);

	//最寄拠点を検索するかどうかのフラグ
	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//最寄検索をする
}
