<?PHP
// ------------------------------------------------------------
// ��������
//
// ��ȯ����
// 2012/11/06 H.Osamoto		��������
// 2015/03/30 N.Wada		�Ǵ���̰������˺ǽ�θ����ΰ������ɤ����Ǹ����ϰϤ��ڤ��ؤ���
// 							�Ǵ���̤ȺǴ�������̤θ����Ͽ��ϰϤ�Ʊ���ˤ���
// 							�Ǵ���̤ȺǴ�������̤θ�����̷����Ʊ���ˤ���
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
	ZdcEmapMapObj.removeWidget(widget2);	// add 2012/04/02 K.Masuda
	<?php } ?>
	<?php if (isset($D_MAPCENTER_MARK_P) && $D_MAPCENTER_MARK_P) { ?>
	widget3 = new ZDC.MapCenter();
	ZdcEmapMapObj.addWidget(widget3);
	<?php } ?>

	//�̼��ѹ�
	if (lvl && lvl != 0) {
		ZdcEmapMapObj.setZoom(lvl);
	} else if(<?PHP echo $D_INIT_LVL_PRINT; ?> > 0) {
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_PRINT; ?>);
	}
	
	<?php // add 2015/03/30 N.Wada [ ?>
	<?php if (isset($D_NMAP_PRINT_CNT_FIX) && $D_NMAP_PRINT_CNT_FIX && isset($first_print) && $first_print) { ?>
	// �ǽ�θ����ΰ����ξ���Ⱦ�¤ǺƸ���
	ZdcEmapSearchFirst = 1;
	<?php } else { ?>
	// Ⱦ�¤ǤϤʤ�ɽ���Ͽޤν̼ܤǺƸ���
	ZdcEmapSearchFirst = 0;
	<?php } ?>
	<?php // add 2015/03/30 N.Wada ] ?>

	//�Ǵ�����򸡺����뤫�ɤ����Υե饰
	if(<?PHP echo $D_SHOP_PRINT_SEARCH; ?>) ZdcEmapSearchShopStart();//�Ǵ󸡺��򤹤�
}
