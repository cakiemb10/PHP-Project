<?PHP
// ------------------------------------------------------------
// ��������
//
// ��ȯ����
// 2011/10/15 Y.Matsukawa	��������
// 2012/04/02 K.Masuda		�Ͽ��濴�ޡ��������ɲ�
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>

function ZdcEmapPrintInit(lat,lon,icnno,nflg,lvl)
{
	//�Ͽޤ�����⡼�ɤˤ���
	ZdcEmapMapObj.ZdcEmapMode = "print";

	//�Ͽ��濴�ޡ��� ---------------------------------
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

	//����̼��ѹ�
	if (lvl && lvl != 0) {
		//ZdcEmapMapObj.setMapScale(lvl);
		ZdcEmapMapObj.setZoom(lvl-1);
	} else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) {
		//ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_PRINT; ?>);
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_PRINT; ?>-1);
	}
	
	//�����������������
	ZdcEmapShopIcon(lat,lon,icnno,nflg);

	//�Ǵ�����򸡺����뤫�ɤ����Υե饰
	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//�Ǵ󸡺��򤹤�
}
