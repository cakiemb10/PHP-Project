<?PHP
// ------------------------------------------------------------
// Google Maps�� ��������
//
// 2013/10/02 Y.Matsukawa	��������
// 2016/08/16 Y.Matsukawa	����¬�Ϸ��ݻ�
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>

<?php //function ZdcEmapPrintInit(lat,lon,icnno,nflg,lvl)		mod 2016/08/16 Y.Matsukawa ?>
function ZdcEmapPrintInit(lat, lon, icnno, nflg, lvl, wgs)
{
	if (!ZdcEmapMapObj) return;
	
	//�Ͽޤ�����⡼�ɤˤ���
	ZdcEmapMapObj.ZdcEmapMode = "print";

	//����̼��ѹ�
	if (lvl && lvl != 0) {
		ZdcEmapMapObj.setZoom(lvl + ZdcEmapZoomOffset);
	} else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) {
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_PRINT; ?> + ZdcEmapZoomOffset);
	}
	
	//�����������������
	<?php //ZdcEmapShopIcon(lat,lon,icnno,nflg);		mod 2016/08/16 Y.Matsukawa ?>
	ZdcEmapShopIcon(lat, lon, icnno, nflg, false, wgs);

//	//�Ǵ�����򸡺����뤫�ɤ����Υե饰
//	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//�Ǵ󸡺��򤹤�
}
