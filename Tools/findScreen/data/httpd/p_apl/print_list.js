<?PHP
// ------------------------------------------------------------
// 印刷画面
//
// 開発履歴
// 2012/11/06 H.Osamoto		新規作成
// 2015/03/30 N.Wada		最寄画面印刷時に最初の検索の印刷かどうかで検索範囲を切り替える
// 							最寄画面と最寄印刷画面の検索地図範囲を同じにする
// 							最寄画面と最寄印刷画面の検索結果件数を同じにする
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
	ZdcEmapMapObj.removeWidget(widget2);	// add 2012/04/02 K.Masuda
	<?php } ?>
	<?php if (isset($D_MAPCENTER_MARK_P) && $D_MAPCENTER_MARK_P) { ?>
	widget3 = new ZDC.MapCenter();
	ZdcEmapMapObj.addWidget(widget3);
	<?php } ?>

	//縮尺変更
	if (lvl && lvl != 0) {
		ZdcEmapMapObj.setZoom(lvl);
	} else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) {
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_PRINT; ?>);
	}
	
	<?php // add 2015/03/30 N.Wada [ ?>
	<?php if (isset($D_NMAP_PRINT_CNT_FIX) && $D_NMAP_PRINT_CNT_FIX && isset($first_print) && $first_print) { ?>
	// 最初の検索の印刷の場合は半径で再検索
	ZdcEmapSearchFirst = 1;
	<?php } else { ?>
	// 半径ではなく表示地図の縮尺で再検索
	ZdcEmapSearchFirst = 0;
	<?php } ?>
	<?php // add 2015/03/30 N.Wada ] ?>

	//最寄拠点を検索するかどうかのフラグ
	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//最寄検索をする
}
