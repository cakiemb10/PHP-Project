<?PHP
// ------------------------------------------------------------
// ��������javasctipt
//
// ��ȯ����
// 2007/03/01 bando@D&I
//     ��������
// 2007/11/16 Y.Matsukawa	���ɽ�������Ͽ�API��ChangeLocation���٥�Ȥ�����ȯ�����뢪����˸��餹
// 2009/05/28 Y.Matsukawa	�Ͽ��濴�ޡ���ɽ��
// 2009/09/04 Y.Matsukawa	�����̼�
// 2011/07/07 H.Osamoto		�ޥĥ�����API2.0�б���
// 2011/10/03 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// ------------------------------------------------------------
include("./inc/define.inc");  // ��������
?>
//-------------------------------------------------------------
//���������Ѵؿ�
//-------------------------------------------------------------
//function ZdcEmapPrintInit(lat,lon,icnno,nflg)		mod 2009/09/04 Y.Matsukawa
function ZdcEmapPrintInit(lat,lon,icnno,nflg,lvl)
{
	//�Ͽޤ�����⡼�ɤˤ���
	//	ZdcEmapMapObj.setPrintMode();	mod 2011/07/07 H.osamoto
//	ZdcEmapMapObj.setPrintModeOn()
	ZdcEmapMapObj.ZdcEmapMode = "print";

	//�Ͽ��濴�ޡ��� ---------------------------------	add 2009/05/28 Y.Matsukawa
	<?php if (isset($D_MAPCENTER_MARK) && $D_MAPCENTER_MARK) { // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapMapObj.removeMapCenter();
	<?php } ?>
	<?php if (isset($D_MAPCENTER_MARK_P) && $D_MAPCENTER_MARK_P) { // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK_P; ?>'));
	<?php } ?>

	// 2007/11/16 del Y.Matsukawa
	//	//�����ΰ��֤ذ�ư
	//	ZdcEmapMapMove(lat, lon);

	//����̼��ѹ�
	//if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_PRINT; ?>);		mod 2009/09/04 Y.Matsukawa
	if (lvl && lvl != 0)
		ZdcEmapMapObj.setMapScale(lvl);
	else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0)
		ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_PRINT; ?>);

	//�����������������
	ZdcEmapShopIcon(lat,lon,icnno,nflg);

	//�Ǵ�����򸡺����뤫�ɤ����Υե饰
	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//�Ǵ󸡺��򤹤�
}
