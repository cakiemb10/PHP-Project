<?PHP
// ------------------------------------------------------------
// 印刷画面javasctipt
//
// 開発履歴
// 2007/03/01 bando@D&I
//     新規作成
// 2007/11/16 Y.Matsukawa	初期表示時に地図APIのChangeLocationイベントが３回発生する→２回に減らす
// 2009/05/28 Y.Matsukawa	地図中心マーク表示
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// ------------------------------------------------------------
include("./inc/define.inc");  // 基本設定
?>
//-------------------------------------------------------------
//印刷画面用関数
//-------------------------------------------------------------
//function ZdcEmapPrintInit(lat,lon,icnno,nflg)		mod 2009/09/04 Y.Matsukawa
function ZdcEmapPrintInit(lat,lon,icnno,nflg,lvl)
{
	//地図を印刷モードにする
	ZdcEmapMapObj.setPrintMode();
	ZdcEmapMapObj.ZdcEmapMode = "print";

	//地図中心マーク ---------------------------------	add 2009/05/28 Y.Matsukawa
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if (isset($D_MAPCENTER_MARK) && $D_MAPCENTER_MARK) { ?>
	ZdcEmapMapObj.removeMapCenter();
	<?php } ?>
	<?php if (isset($D_MAPCENTER_MARK_P) && $D_MAPCENTER_MARK_P) { ?>
	ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK_P; ?>'));
	<?php } ?>

	// 2007/11/16 del Y.Matsukawa
	//	//拠点の位置へ移動
	//	ZdcEmapMapMove(lat, lon);

	//初期縮尺変更
	//if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_PRINT; ?>);		mod 2009/09/04 Y.Matsukawa
	if (lvl && lvl != 0)
		ZdcEmapMapObj.setMapScale(lvl);
	else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0)
		ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_PRINT; ?>);

	//拠点アイコンの描画
	ZdcEmapShopIcon(lat,lon,icnno,nflg);

	//最寄拠点を検索するかどうかのフラグ
	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//最寄検索をする
}
