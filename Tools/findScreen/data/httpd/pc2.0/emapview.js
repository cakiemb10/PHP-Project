<?PHP
// ------------------------------------------------------------
// �Ͽ�����javasctipt �ᥤ��
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2007/11/16 Y.Matsukawa	���ɽ�������Ͽ�API��ChangeLocation���٥�Ȥ�����ȯ�����뢪����˸��餹
// 2007/11/30 Y.Matsukawa	ZdcEmapInit��Ǥ�դν̼ܻ����ǽ��
// 2008/04/01 Y.Matsukawa	�Ͽ޾�Ǽꥫ������
// 2008/05/07 Y.Matsukawa	��IE6�Զ���б����Ͽ޲��̤Υꥹ�ȥܥå���������������ɥ��ξ�˽ФƤ���
// 2008/10/22 Y.Matsukawa	���Ѥ��ʤ�JS�ϥ��ɤ��ʤ�
// 2008/11/26 Y.Matsukawa	���Զ���б��۵������������Ʃ��GIF����Ѥ��Ƥ����硢IE�ǰ�������Ʃ�ᤷ�ʤ���
// 2009/02/16 Y.Matsukawa	���Զ������ۡ�FF�Τߡ˥�������ޥ�������ǿ᤭�Ф�ɽ���ξ�硧�Ͽ��濴�Υ��������˥ޥ������֤��Ƥ���ȡ��᤭�Ф���ɽ������ɽ���򷫤��֤�
//                          ��wait��å�������ɽ������ɽ�������ȡ������٤˥ޥ������󥤥٥�Ȥ�ȯ������褦�ʤΤǡ��᤭�Ф��Ǥ�wait��å������ϽФ��ʤ��褦�ˤ����
// 2009/03/04 Y.Matsukawa	���������ľ��������
// 2009/05/28 Y.Matsukawa	�Ͽ��濴�ޡ���ɽ��
// 2009/06/02 Y.Matsukawa	���Զ�罤���۵������ꥢ�����ǻ��Ѥ�����ܤ�HTML������<BR><B>�ˤ����Ϥ���ȡ�ư�ɽ������
// 2009/09/04 Y.Matsukawa	�����̼�
// 2009/10/14 Y.Matsukawa	�ޥ��������Ȥǿ᤭�Ф���ä�
// 2009/11/07 Y.Matsukawa	�������ܳ�ĥ��50��200��
// 2010/01/06 Y.Matsukawa	���Զ�罤���ۥ��󥰥륯��å����Ͽް�ư��̵���ˤʤäƤ���
// 2010/02/02 Y.Matsukawa	�����������󥤥٥��̵���ξ��ϥ��������ѹ����ʤ�
// 2010/03/23 Y.Matsukawa	�ѥ󤯤�ľ����ʣ���б�
// 2010/07/08 Y.Matsukawa	���Զ�罤���ۥѥ󤯤�TOP��󥯤�window.close()�ˤ��ơ��������򥭥�󥻥뤹��ȡ��ѥ󤯤������ꥢ����Ƥ��ޤ�
// 2010/07/14 Y.Matsukawa	�Ͽ����ػߥ⡼��
// 2010/07/23 Y.Matsukawa	�롼�ȵ�Υɽ��
// 2010/08/09 Y.Matsukawa	����ȥ������̤˾õ��ǽ�ˤ���
// 2011/02/10 Y.Matsukawa	��®��
// 2011/02/17 Y.Matsukawa	���Զ�罤���۹�®���ǽ̼ܤ򥳥󥹥ȥ饯���ǻ��ꤹ��褦�ˤ������Ͽ޽��ɽ�����˥��饤�������֤�������
// 2011/02/22 Y.Matsukawa	�嵭�Զ�罤���򸵤��᤹��API¦���б������١�
// 2011/05/26 K.Masuda		TOP�����ݡ����������Ϳ����
// 2011/06/15 K.Masuda		�ե�����ɽ����Ǥ�Ƹ����Ǥ���褦�ˤ���
// 2011/06/16 Y.Matsukawa	�ܺٹ�������JS�¹�
// 2011/07/07 H.Osamoto		�ޥĥ�����API2.0�б���
// 2011/10/03 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/10/06 H.Osamoto		���֥륯��å����������ذ�ư���륤�٥���ɲ�
// 2012/03/16 H.Osamoto		���Զ�罤���ۥ롼��õ��������ץȥ��顼����
// ------------------------------------------------------------
include("./inc/define.inc");  // ��������
include("./inc/define_get_icon.inc");  // ��������������
?>
<?php /* ��ɽ������ ?>
//-------------------------------------------------------------
//JSAPI��ư���ǧ
//-------------------------------------------------------------
// del 2011/07/07 H.osamoto [
//	if(parseInt(ZDC_RC) != 0) {
//		//location.href = '<?PHP echo $D_URL_JSAPIERROR; ?>';
//	}
// del 2011/07/07 H.osamoto ]
<?php ��ɽ����λ */ ?>

//-------------------------------------------------------------
//�������
//-------------------------------------------------------------
//�Ͽ�
var ZdcEmapMapObj = null;
var ZdcEmapMapUsrctl = null;
var ZdcEmapMapZoomctl = null;
//	var ZdcEmapMapSize = new ZdcWindow();	// del 2011/07/07 H.osamoto
//�桼�����쥤�䡼
//	var ZdcEmapMapUserLyr = new ZdcUserLayer();	// del 2011/07/07 H.osamoto
var ZdcEmapMapUserLyrId = null;
//�ޡ���������
var ZdcEmapMapShopMrkId = new Array(<?PHP echo $D_SHOP_MAX; ?>);
var ZdcEmapMapShopMrkCnt = null;
var ZdcEmapMapPoiMrkId = new Array(<?PHP echo $D_POI_MAX; ?>);
var ZdcEmapMapPoiMrkCnt = null;
var ZdcEmapMapShopDetailMrkId = null;
var ZdcEmapMapCurFocusMrkId = null;
//�᤭�Ф�
//	var ZdcEmapMsg = new ZdcUserMsgWindow();	// del 2011/07/07 H.osamoto
//����
var ZdcEmapListObj;
var ZdcEmapDetailObj;
var ZdcEmapCondObj;
var ZdcEmapSearchWindowObj;
var ZdcEmapIE6HideSelectObj;	// add 2008/05/07 Y.Matsukawa
//My���ꥢ�ɲ���ɽ�����ꥢ
var ZdcEmapMyareaWrapperObj;
//�ƥܥ���Υ��٥�ȴ���
var ZdcEmapSearchClickFlg = 0;
//�����������
var ZdcEmapIconImg = new Array();
var ZdcEmapIconW = new Array();
var ZdcEmapIconH = new Array();
var ZdcEmapIconOffsetX = new Array();
var ZdcEmapIconOffsetY = new Array();
// �Ͽް��ٷ��� add 2011/07/07 H.osamoto
var mappoint;
<?PHP
foreach( $D_ICON as $key=>$val) {
	printf("ZdcEmapIconImg['%s'] = '%s';",$key,$val["IMG"]);
	printf("ZdcEmapIconW['%s'] = %d;",$key,$val["W"]);
	printf("ZdcEmapIconH['%s'] = %d;",$key,$val["H"]);
	printf("ZdcEmapIconOffsetX['%s'] = %d;",$key,ceil($val["W"]/2)*-1);
	printf("ZdcEmapIconOffsetY['%s'] = %d;",$key,ceil($val["H"]/2)*-1);
}
?>
// add 2011/07/07 H.Osamoto [
var Zdc_smap_g_oMap     = null;
var Zdc_smap_g_oAjax    = null;
// add 2011/07/07 H.Osamoto ]

//����¾
<?php /* ��ɽ������ ?>
// del 2011/07/07 H.osamoto [
//	<?php //if($D_REQ_JSAPI["zdcmapgeometric"]){ ?>	// 2008/10/22 Y.Matsukawa add
//	var ZdcEmapGeometricObj = new ZdcGeometric();
//	<?php //} ?>
// del 2011/07/07 H.osamoto ]
<?php ��ɽ����λ */ ?>
var ZdcEmapSaveCond = new Array(<?PHP echo $D_SHOP_MAX; ?>);//�ʹ����
<?PHP //for($i = 0;$i < 50;$i ++) if($_VARS["cond".$i]) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]);		mod 2009/11/07 Y.Matsukawa ?>
<?PHP for($i = 1;$i <= 200;$i ++) if(isset($_VARS["cond".$i]) && $_VARS["cond".$i]) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]); // mod 2011/10/03 Y.Nakajima ?>

// add 2011/05/26 K.Masuda [
var QSTRING = location.search.replace(/^\?/, '');
// add 2011/05/26 K.Masuda ]

//������ؿ�
<?php /* ��ɽ������ ?>
//function ZdcEmapInit(){	2007/11/16 mod Y.Matsukawa
//function ZdcEmapInit(init_lat, init_lon){		2007/11/30 mod Y.Matsukawa
<?php ��ɽ����λ */ ?>
function ZdcEmapInit(init_lat, init_lon, init_lv){
	//�Ͽޤδ������� ----------------------------------------
	var svrurl = "<?PHP if (isset($D_JS_SVRURL)) echo $D_JS_SVRURL;  // mod 2011/10/03 Y.Nakajima ?>";
<?php	//ZdcEmapMapObj = new ZdcMap(document.getElementById("ZdcEmapMap"));	del 2011/02/10 Y.Matsukawa ?>
<?php // add 2011/02/10 Y.Matsukawa [ ?>
	//�������
	if (!init_lat || !init_lon) {
		init_lat = <?PHP echo $D_INIT_LAT; ?>;
		init_lon = <?PHP echo $D_INIT_LON; ?>;
	}
	if (!init_lv || init_lv == 0) {
		init_lv = <?PHP echo $D_INIT_LVL; ?>;
	}
	init_lv = init_lv - 1; // add 2011/07/07 H.Osamoto
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapMapObj = new ZdcMap(document.getElementById("ZdcEmapMap"), 
	//								new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>),
	//								init_lv,
	//								<?PHP echo $D_MAP_LAYER_KBN; ?>);
<?php ��ɽ����λ */ ?>
	ZdcEmapMapObj = new ZDC.Map(
						document.getElementById('ZdcEmapMap'),
						{
							latlon : new ZDC.LatLon(init_lat, init_lon),
							zoom : init_lv,
							mapType: ZDC.MAPTYPE_COLOR
						}
					);
	// add 2011/10/06 H.osamoto [
	/* �Ͽޤ���֥륯��å������Ȥ��Υ��٥�� */
	ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_DBLCLICK, moveDblClickLatLon);
	// add 2011/10/06 H.osamoto ]
	
	// mod 2011/07/07 H.osamoto ]
<?php // add 2011/02/10 Y.Matsukawa ] ?>
<?php /* ��ɽ������ ?>
	// del 2011/07/07 H.osamoto [
	//	ZdcEmapMapSize = ZdcEmapMapObj.getMapWindowSize();
	//	
	//		//�Ͽ��濴�ޡ��� ---------------------------------	add 2009/05/28 Y.Matsukawa
	//		<?php if ($D_MAPCENTER_MARK) { ?>
	//		ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK; ?>'));
	//		<?php } ?>
	//		//�桼��������ȥ��� ---------------------------------
	//		<?PHP echo //$D_JSCODE_MAPUSRCTL; ?>	del 2011/07/07 H.Osamoto
	//		<?PHP echo //$D_JSCODE_MAPZOOMCTL; ?>	del 2011/07/07 H.Osamoto
	//		
	//		//����¾�Ͽ޴ط� ---------------------------------------
	//		ZdcEmapMapObj.setMouseCursor("hand");	// 2008/04/01 add Y.Matsukawa
	//		ZdcEmapMapObj.CenterFirst = false;
	//		ZdcEmapMapObj.setScreenMode();
	//		//ZdcEmapMapObj.setMapType(<?PHP echo $D_MAP_LAYER_KBN; ?>);		del 2011/02/10 Y.Matsukawa
	//		ZdcEmapMapObj.reflashMap();
	//		if(<?PHP echo $D_MAP_SCALE_MAX; ?> > -1 && <?PHP echo $D_MAP_SCALE_MIN; ?> > -1)
	//			ZdcEmapMapObj.setMapZoomLimit(<?PHP echo $D_MAP_SCALE_MAX; ?>,<?PHP echo $D_MAP_SCALE_MIN; ?>);
	//		//ɸ�ॳ��ȥ���
	//		if(ZdcEmapMapUsrctl == null && ZdcEmapMapZoomctl == null && <?PHP echo $D_MAP_CONTROL; ?> > 0)
	//			ZdcEmapMapObj.addMapControl(new ZdcControl(<?PHP echo $D_MAP_CONTROL; ?>));
	//		//if (ZdcEmapMapZoomctl) ZdcEmapMapZoomctl.setSlitherPosition();		// add 2011/02/17 Y.Matsukawa	del 2011/02/22 Y.Matsukawa
	//		//ɸ�ॹ������С�
	//		if(<?PHP echo $D_MAP_SCALEBAR; ?> > 0) ZdcEmapMapObj.addMapScaleBar(new ZdcScaleBar(<?PHP echo $D_MAP_SCALEBAR; ?>));
	//		//ɸ���濴��������
	//		if(<?PHP echo $D_MAP_CENTER; ?> > 0) {
	//			var obj = new ZdcMapCenter(<?PHP echo $D_MAP_CENTER; ?>);
	//			obj.doc.zIndex=2999;//������������̤ˤ�äƤ���
	//			ZdcEmapMapObj.addMapCenter(obj);
	//		}
	//		//����ܥå���
	//		if(<?PHP echo $D_MAP_INFO; ?> > 0) ZdcEmapMapObj.addMapCenterInfoBox(new ZdcMapCenterInfoBox(<?PHP echo $D_MAP_INFO; ?>));
	//
	//		<?php // add 2010/08/09 Y.Matsukawa [ ?>
	//		<?php if($D_MAP_REMOVE_CONTROL) { ?>
	//		//����ȥ���õ�
	//		ZdcEmapMapObj.removeUserControl();
	//		ZdcEmapMapObj.removeMapControl();
	//		<?php } ?>
	//		<?php if($D_MAP_REMOVE_ZOOMCONTROL) { ?>
	//		//�����ॳ��ȥ���õ�
	//		ZdcEmapMapObj.removeUserZoomControl();
	//		<?php } ?>
	//		<?php if($D_MAP_DRAG_OFF) { ?>
	//		//�Ͽޥɥ�å��ػ�
	//		ZdcEmapMapObj.dragOff();
	//		<?php } ?>
	//		<?php // add 2010/08/09 Y.Matsukawa ] ?>
	//
	//		//
	//		ZdcEmapMapObj.ZdcMapRasterEngine = false;
	//	<?php // del 2011/02/10 Y.Matsukawa [ ?>
	//		//	//�������
	//		//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(<?PHP echo $D_INIT_LON; ?>,<?PHP echo $D_INIT_LAT; ?>,<?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);		2007/11/16 mod Y.Matsukawa
	//		//	if (!init_lat || !init_lon) {
	//		//		init_lat = <?PHP echo $D_INIT_LAT; ?>;
	//		//		init_lon = <?PHP echo $D_INIT_LON; ?>;
	//		//	}
	//		//	// 2007/11/30 add Y.Matsukawa ��
	//		//	//if (!init_lv) {		mod 2009/09/04 Y.Matsukawa
	//		//	if (!init_lv || init_lv == 0) {
	//		//		init_lv = <?PHP echo $D_INIT_LVL; ?>;
	//		//	}
	//		//	// 2007/11/30 add Y.Matsukawa ��
	//		//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);	2007/11/30 mod Y.Matsukawa
	//		//	ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), init_lv);
	//	<?php // del 2011/02/10 Y.Matsukawa ] ?>
	//		ZdcEmapMapObj.saveMapLocation();
	//		//����å�ư���ʬ
	//		if(<?PHP echo $D_MAP_CLICK_KBN; ?> == 2) {
	//			<?PHP // ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnodrag", function(e) {	mod 2010/01/06 Y.Matsukawa ?>
	//			ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnomove", function(e) {
	//				this.scrollToCenter(new ZdcPoint(this.MouseCLon,this.MouseCLat)); 
	//			});
	//		}
	//		//�ۥ����륺�����ʬ
	//		if(<?PHP echo $D_MAP_WHEEL_KBN; ?> == 0) {
	//			ZdcEmapMapObj.setWheelOff();
	//		} else {
	//			ZdcEmapMapObj.setWheelOn();
	//		}
	// del 2011/07/07 H.osamoto ]
<?php ��ɽ����λ */ ?>

	// add 2011/07/07 H.Osamoto [
	// �Ͽ޾�ǤΥۥ���������̵���ˤ���
	var ua = navigator.userAgent, we,
	map = document.getElementById('ZdcEmapMap'); //�Ͽޤ�ɽ������div����
	if (ua.match(/Gecko/) && ua.match(/(Firebird|Firefox)/)) {
		we  = 'DOMMouseScroll';
	} else {
		we = 'mousewheel';
	}
	ZDC.clearListeners(map.firstChild, we);
	// add 2011/07/07 H.Osamoto ]
	
	//��e-map�ѥ���ȥ��� --------------------------------
	//�ꥹ��ɽ����
	ZdcEmapListObj  = document.getElementById('ZdcEmapList');
	if(!ZdcEmapListObj) ZdcEmapListObj = document.createElement('DIV');//light�ѥ��ߡ�
	//�ܺ�ɽ����
	ZdcEmapDetailObj = document.getElementById('ZdcEmapDetail');
	if(!ZdcEmapDetailObj) ZdcEmapDetailObj = document.createElement('DIV');//light�ѥ��ߡ�
	//������������
	ZdcEmapCondObj = document.getElementById('ZdcEmapCond');
	if(!ZdcEmapCondObj) ZdcEmapCondObj = document.createElement('DIV');//light�ѥ��ߡ�
	//������
	ZdcEmapSearchWindowObj = document.getElementById('ZdcEmapSearchWindow');
	if(!ZdcEmapSearchWindowObj) ZdcEmapSearchWindowObj = document.createElement('DIV');//light�ѥ��ߡ�
	//��IE6�Զ���б����Ͽ޲��̤Υꥹ�ȥܥå���������������ɥ��ξ�˽ФƤ��Ƥ��ޤ��Τ򱣤������div	add 2008/05/07 Y.Matsukawa
	ZdcEmapIE6HideSelectObj = document.getElementById('ZdcEmapIE6HideSelect');
	//My���ꥢ�ɲ���ɽ�����ꥢ
	ZdcEmapMyareaWrapperObj = document.getElementById('myareaWrapper');

<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.osamoto [
	//		//����¾ -----------------------------------------------
	//		//�桼�����쥤�䡼
	//		ZdcEmapMapUserLyr.setLayerScale(<?PHP echo $D_VIEW_ICON_MAX; ?>,<?PHP echo $D_VIEW_ICON_MIN; ?>);
	//		ZdcEmapMapUserLyr.setLayerType('manual');
	//		ZdcEmapMapUserLyr.clearMarker();
	//		ZdcEmapMapUserLyrId = ZdcEmapMapObj.addUserLayer(ZdcEmapMapUserLyr); 
	//		//����������������
	//		ZdcEmapHistoryClear();
	//		//�����楢������
	//		ZdcEmapMapObj.addZdcWait(parseInt(parseInt(ZdcEmapMapSize.height) / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETY; ?>),
	//								 parseInt(parseInt(ZdcEmapMapSize.width)  / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETX; ?>),'<?PHP echo $D_MAP_WAIT_MSG; ?>');
<?php ��ɽ����λ */ ?>
	//����¾ -----------------------------------------------
	//��������С�
	widgetScaleBar = new ZDC.ScaleBar();
	ZdcEmapMapObj.addWidget(widgetScaleBar);
	//�桼������ȥ���
	createUserControl();
	
	//����������������
	ZdcEmapHistoryClear();
	// mod 2011/07/07 H.osamoto ]
}

// add 2011/10/06 H.osamoto [
/* ���֥륯��å����������ذ�ư���� */
function moveDblClickLatLon() {
	var latlon =  ZdcEmapMapObj.getClickLatLon();
	ZdcEmapMapObj.moveLatLon(latlon);
};
// add 2011/10/06 H.osamoto ]

// �桼������ȥ���	add 2011/07/07 H.osamoto
function createUserControl() {
	/* �桼������ȥ���˻��Ѥ������ */
	var imgurldir = '<?PHP echo $D_DIR_BASE; ?>img/usrcontrol/';
	
	var control = {
		/* �ۡ���ݥ������ذ�ư�ܥ��� */
		home:
		{
			/* ������URL */
			src: imgurldir + 'home.png',
			/* ���ְ��� */
			pos:{top: 28,right: 34},
			/* ������ɽ�������� */
			imgSize:{width: 22,height: 22}
		},
		north:
		{
			src: imgurldir + 'north.png',
			pos: {top: 10,right: 38},
			imgSize: {width: 16,height: 17}
		},
		east:
		{
			src: imgurldir + 'east.png',
			pos: {top: 30,right: 18},
			imgSize: {width: 16,height: 17}
		},
		south:
		{
			src: imgurldir + 'south.png',
			pos: {top: 50,right: 38},
			imgSize: {width: 16,height: 17}
		},
		west:
		{
			src: imgurldir + 'west.png',
			pos: {top: 30,right: 58},
			imgSize: {width: 16,height: 17}
		},
		bar:
		{
			src: imgurldir + 'bar.png',
			pos: {top: 91,right: 38},
			imgSize: {width: 17,height: 110}
		},
		btn:
		{
			src: imgurldir + 'btn.png',
			pos: {top: 0,right: 1},
			imgSize: {width: 15,height: 10}
		},
		minus:
		{
			src: imgurldir + 'minus.png',
			pos: {top: 206,right: 38},
			imgSize: {width: 16,height: 17}
		},
		plus:
		{
			src: imgurldir + 'plus.png',
			pos: {top: 72,right: 38},
			imgSize: {width: 16,height: 17}
		}
	};
	
	var options = {
		/* �Ĥޤߤξ�°���(�̼ܥ�٥��ѹ��С���top: -2px�ΰ���) */
		start: -2,
		/* �Ĥޤߤΰ�ư�� */
		interval: 6
	};
	
	/* �桼������ȥ������� */
	widget = new ZDC.UserControl(control, options);
	
	/* �桼������ȥ�����ɲ� */
	ZdcEmapMapObj.addWidget(widget);
};



//-------------------------------------------------------------
//�Ͽ�����
//-------------------------------------------------------------
//�Ͽ޾�˥�������ɽ��
var ZdcEmapMapCurMrkId = null;
function ZdcEmapMapCursorSet(lat, lon){
	//��������κ���
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.osamoto [
	//	var mrk = ZdcEmapMakeMrk(0,lat,lon,
	//							 ZdcEmapIconW['@SELB'],ZdcEmapIconH['@SELB'],0,0,
	//							 ZdcEmapIconOffsetX['@SELB'],ZdcEmapIconOffsetY['@SELB'],0,0,0,0,
	//							 ZdcEmapIconImg['@SELB'],'',
	//							 '','',0,null,null,null);
	//	if(ZdcEmapMapCurMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);
	//	ZdcEmapMapCurMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
<?php ��ɽ����λ */ ?>
	mrk = ZdcEmapMakeMrkApi2(0, lat, lon, 
							ZdcEmapIconW['@SELB'], ZdcEmapIconH['@SELB'],0,0,
							ZdcEmapIconOffsetX['@SELB'], ZdcEmapIconOffsetY['@SELB'],0,0,
							ZdcEmapIconImg['@SELB'], '',
							'', '', '', 0, null, null, null
						);
	if (ZdcEmapMapCurMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapCurMrkId);
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapCurMrkId = mrk;
	// mod 2011/07/07 H.osamoto ]
}
//�Ͽ޾�Υ������볰��
function ZdcEmapMapCursorRemove(){
	if (ZdcEmapMapCurMrkId != null) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);		mod 2011/07/07 H.Osamoto
		ZdcEmapMapObj.removeWidget(ZdcEmapMapCurMrkId);
		ZdcEmapMapCurMrkId = null;
	}
	//�ܺ�ɽ����
	ZdcEmapMapFrontShopDetail();//�ܺ٥�����������̤ˤ�äƤ���
<?php /* ��ɽ������ ?>
	// del 2011/07/07 H.Osamoto [
	//	// 2011/06/15 K.Masuda mod [
	//	//ZdcEmapShopMsgClose();//�᤭�Ф���ä�
	//	if( <?php if($D_HUKIDASHI_SEARCH){echo "false";}else{echo "true";} ?> ){
	//		ZdcEmapShopMsgClose();//�᤭�Ф���ä�
	//	}
	//	// 2011/06/15 K.Masuda mod ]
	// del 2011/07/07 H.Osamoto ]
<?php ��ɽ����λ */ ?>
}
//�Ͽް�ư
function ZdcEmapMapMove(lat, lon, lvl){
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.osamoto [
	//	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//	//�ޥåװ�ư
	//	//	if(lvl) ZdcEmapMapObj.setMapLocation(center,lvl);
	//	//		else ZdcEmapMapObj.setMapLocation(center);
	//	ZdcEmapMapObj.setMapLocation(center);
	//	if(lvl) ZdcEmapMapObj.setMapScale(lvl);
<?php ��ɽ����λ */ ?>
	var center = new ZDC.LatLon(Number(lat), Number(lon));
	ZdcEmapMapObj.moveLatLon(center);
	if(lvl) ZdcEmapMapObj.setZoom(lvl);
	// mod 2011/07/07 H.osamoto ]
}
function ZdcEmapMapScroll(lat, lon){
	// mod 2011/07/07 H.Osamoto [
<?php /* ��ɽ������ ?>
	//	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//	//�ޥåװ�ư
	//	ZdcEmapMapObj.scrollToCenter(center);
<?php ��ɽ����λ */ ?>
	var center = new ZDC.LatLon(lat, lon);
	//�ޥåװ�ư
	ZdcEmapMapObj.moveLatLon(center);
	// mod 2011/07/07 H.Osamoto ]
}
//�Ͽް�ư
function ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,pt,noin){
	var p1 = new ZdcPoint(minlon,minlat,<?PHP echo $D_PFLG; ?>);
	var p2 = new ZdcPoint(maxlon,maxlat,<?PHP echo $D_PFLG; ?>);
	var bx = new ZdcBox(p1,p2);
	if(pt != null) {
		var s = ZdcEmapMapObj.getMapBoxScale(bx,pt);
		ZdcEmapMapObj.setMapLocation(pt);
		if(noin != 1 || (noin == 1 && s < ZdcEmapMapObj.getMapScale())) ZdcEmapMapObj.setMapScale(s);
	} else {
		var s = ZdcEmapMapObj.getMapBoxScale(bx);
		ZdcEmapMapObj.setMapLocation(bx.getBoxCenter());
		if(noin != 1 || (noin == 1 && s < ZdcEmapMapObj.getMapScale())) ZdcEmapMapObj.setMapScale(s);
	}
}

//�Ͽް�ư(API2.0��)	add 2011/07/07 H.osamoto
function ZdcEmapMapMoveBoxApi2(minlat,minlon,maxlat,maxlon){
	
	var varlatlon_box = new Array();
	
	// �Ͽ�ɽ���̼ܼ����Ѳ���ɽ�����ꥢ
	varlatlon_box[0] = new ZDC.LatLon(minlat, minlon);
	varlatlon_box[1] = new ZDC.LatLon(maxlat, maxlon);
	var adjust = ZdcEmapMapObj.getAdjustZoom(varlatlon_box);
	
	// �Ͽް�ư���̼��ѹ�
	ZdcEmapMapObj.moveLatLon(adjust.latlon);
	ZdcEmapMapObj.setZoom(adjust.zoom);
}

//-------------------------------------------------------------
//������������ط�
//-------------------------------------------------------------
var ZdcEmapHistoryCnt;
var ZdcEmapHistoryCntSv;		// add 2010/07/08 Y.Matsukawa
var ZdcEmapHistoryCntSvB;
var ZdcEmapHistoryName = new Array(10);
var ZdcEmapHistoryLink = new Array(10);
var ZdcEmapHistorySaveCnt;
var ZdcEmapHistorySaveName = new Array(10);
var ZdcEmapHistorySaveLink = new Array(10);
var ZdcEmapHistoryClicked = 0;
//����å�����ư��
function ZdcEmapHistoryClick(cnt) {
	ZdcEmapHistoryCntSvB = cnt;
	if(ZdcEmapReadCheck()) return;//�ɤ߹������ư�����
	if(!ZdcEmapHistoryLink[cnt]) return ;
<?php	// add 2011/06/16 Y.Matsukawa [ ?>
<?php	// ��������ؿ����������Ƥ�����¹� ?>
	if (typeof ZdcEmapCFBeforeHistoryClick == 'function') {
		ZdcEmapCFBeforeHistoryClick();
	}
<?php	// add 2011/06/16 Y.Matsukawa ] ?>
	ZdcEmapHistoryCntSv = ZdcEmapHistoryCnt;		// add 2010/07/08 Y.Matsukawa
	ZdcEmapHistoryCnt = cnt - 1;
	ZdcEmapHistoryClicked = 1;
	eval(ZdcEmapHistoryLink[cnt]);
	ZdcEmapHistoryClicked = 0;
}
//��������Υ���å�ư�����󥻥뤵�줿���ˡ�����򸵤��᤹		add 2010/07/08 Y.Matsukawa
function ZdcEmapHistoryClickCancel() {
	ZdcEmapHistoryCnt = ZdcEmapHistoryCntSv;
}
//�ҤȤ����
function ZdcEmapHistoryBack() {
	ZdcEmapHistoryClick(ZdcEmapHistoryCnt - 1)
}
//�ɲ�
function ZdcEmapHistoryAdd(name,link) {
	ZdcEmapHistoryCnt ++;
	//���֤�ڡ�����������᤹�ʥڡ������ܤ����ܥ����Ѥ��б�)
	for(var i = 1;i < ZdcEmapHistoryCnt;i ++) {
		if(ZdcEmapHistoryLink[i] == link) {
			ZdcEmapHistoryCnt = i;
			break;
		}
	}
	//��Ͽ
	ZdcEmapHistorySet(ZdcEmapHistoryCnt,name,link);
}
//�ѹ�
function ZdcEmapHistoryChange(name,link) {
	ZdcEmapHistorySet(ZdcEmapHistoryCnt,name,link);
}
//���ꥢ
function ZdcEmapHistoryClear() {
	ZdcEmapHistoryCnt = 0;
<?php /* ��ɽ������ ?>
	// mod 2011/05/26 K.Masuda [
	//ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP //echo $D_HISTORY_TOP_NAME; ?>","<?PHP //echo $D_HISTORY_TOP_LINK; ?>");
<?php ��ɽ����λ */ ?>
	if( <?php if(isset($D_QUERY_STRING) && $D_QUERY_STRING){echo "true";}else{echo "false";}  // mod 2011/10/03 Y.Nakajima ?> ){
		ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP echo $D_HISTORY_TOP_NAME; ?>","<?PHP echo $D_HISTORY_TOP_LINK; ?>+QSTRING");
	} else {
		ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP echo $D_HISTORY_TOP_NAME; ?>","<?PHP echo $D_HISTORY_TOP_LINK; ?>");
	}
	// mod 2011/05/26 K.Masuda ]
}
//��Ͽ�ܽ���
function ZdcEmapHistorySet(cnt,name,link) {
	ZdcEmapHistoryName[cnt] = name;
	ZdcEmapHistoryLink[cnt] = link;
	ZdcEmapHistoryRefresh();
}
//������
function ZdcEmapHistoryRefresh() {
	var html = "",name= "",tmp = "";
	var html_last = "";		// add 2009/03/04 Y.Matsukawa
	var html_last_arr = new Array();		// add 2010/03/23 Y.Matsukawa
	for(var i = 0;i < ZdcEmapHistoryCnt+1;i ++) {
		//html����ƥ��ƥ�
		name = "";
		tmp = ZdcEmapHistoryName[i];
		// add 2009/06/02 Y.Matsukawa [
		// HTML�����ϥ��ڡ������ִ�����ɽ��
		tmp = tmp.replace(/<br>/ig, " ");
		tmp = tmp.replace(/<b>/ig, " ");
		tmp = tmp.replace(/<\/b>/ig, " ");
		// add 2009/06/02 Y.Matsukawa ]
		for (var j = 0; j < tmp.length; j++){
			var k = tmp.charAt(j);
			name += {'<':'&lt;', '>':'&gt;', '&':'&amp;', '"':'&quot;'}[k] || k;
		}
		//���̤��ɲ�
		if(html) html += "<?PHP echo $D_HISTORY_SEP; ?>";
		if(ZdcEmapHistoryLink[i] && i != ZdcEmapHistoryCnt) {
			html += '<a href="javascript:ZdcEmapHistoryClick('+i+');">'+name+'</a>';
			html_last = '<a href="javascript:ZdcEmapHistoryClick('+i+');"><?php if (isset($D_HISTORY_LAST_WORD)) echo $D_HISTORY_LAST_WORD; ?></a>';	// add 2009/03/04 Y.Matsukawa
<?php	// add 2010/03/23 Y.Matsukawa [
		for ($j = 1; $j <= 5; $j++) {
?>
			html_last_arr[<?php echo $j; ?>] = '<a href="javascript:ZdcEmapHistoryClick('+i+');"><?php if (isset($D_HISTORY_LAST_WORD_ARR[$j]) && $D_HISTORY_LAST_WORD_ARR[$j]) echo $D_HISTORY_LAST_WORD_ARR[$j]; // mod 2011/10/03 Y.Nakajima ?></a>';
<?php	}
		// add 2010/03/23 Y.Matsukawa ]
?>
		} else {
			html += name;
		}
	}

	var obj = document.getElementById('history');
	if(obj) obj.innerHTML = html;
	// add 2009/03/04 Y.Matsukawa [
	var obj_last = document.getElementById('historyLast');
	if(obj_last) obj_last.innerHTML = html_last;
	// add 2009/03/04 Y.Matsukawa ]
	// add 2010/03/23 Y.Matsukawa [
	for (var i = 1; i <= 5; i++) {
		obj_last = null;
		obj_last = document.getElementById('historyLast'+i);
		if(obj_last && html_last_arr[i]) obj_last.innerHTML = html_last_arr[i];
	}
	// add 2010/03/23 Y.Matsukawa ]
}
//����
function ZdcEmapHistorySave() {
	for(i = 0;i < ZdcEmapHistoryCnt+1;i ++) {
		ZdcEmapHistorySaveName[i] = ZdcEmapHistoryName[i];
		ZdcEmapHistorySaveLink[i] = ZdcEmapHistoryLink[i];
	}
	ZdcEmapHistorySaveCnt  = ZdcEmapHistoryCnt;
}
//�ɹ�
function ZdcEmapHistoryLoad() {
	if(!ZdcEmapHistorySaveChk()) return;
	for(i = 0;i < ZdcEmapHistorySaveCnt+1;i ++) {
		ZdcEmapHistoryName[i] = ZdcEmapHistorySaveName[i];
		ZdcEmapHistoryLink[i] = ZdcEmapHistorySaveLink[i];
	}
	ZdcEmapHistoryCnt  = ZdcEmapHistorySaveCnt;
	ZdcEmapHistoryRefresh();
}
//������̵ͭ�����å�
function ZdcEmapHistorySaveChk() {
	return ZdcEmapHistorySaveCnt;
}
//��������򲡤���ƤΥ�������󤫥����å�
function ZdcEmapHistoryClickChk() {
	return ZdcEmapHistoryClicked;
}



//-------------------------------------------------------------
//����������Ͽ
//-------------------------------------------------------------
function ZdcEmapMakeMrk(id,lat,lon,
						sizew,sizeh,shadowsizew,shadowsizeh,
						offsetx,offsety,shdoffsetx,shdoffsety,msgoffsetx,msgoffsety,
						image,shadowimage,
						data1,data2,nflg,
						mouseclickmarker,mouseovermarker,mouseoutmarker
						,lvl			// add 2009/09/04 Y.Matsukawa
						) {
	
	//mod 2011/10/03 Y.nakajima [
	//lvl�������Ǥʤ��Ȥ��ν������ɲ�
	if (isNaN(lvl) || !lvl || lvl < 1 || lvl >18) lvl = 0;
	//mod 2011/10/03 Y.nakajima ]

	var p,mrk,item;
	var icon = new ZdcIcon();
	
	//��������κ���
	icon.size      = new ZdcSize(sizew, sizeh);
	icon.offset    = new ZdcPixel(offsetx, offsety);
<?php /* ��ɽ������ ?>
	//icon.image    = image;	2008/11/26 Y.Matsukawa del
	// 2008/11/26 Y.Matsukawa add [
	// icon.image����������.gif�פǤʤ��ȡ�����Ū��GIF�ʳ��Ȥ��ƽ�������Ƥ��ޤ��Τǡ�������̵��������.gif�פˤ��Ƥ��ޤ���
	// GIF�ʳ��ǽ�������Ƥ��ޤ��ȡ�IE�ǰ�������Ʃ��GIF��Ʃ�ᤷ�ޤ���
	// �����ॹ������ͤ��ղä��Ƥ���Τϡ�����å��������Τ���Ǥ������줬�ʤ��ȡ�������������򺹤��ؤ����ݤ�ɽ��������뤳�Ȥ�����ޤ�����IE�Τߡ�
<?php ��ɽ����λ */ ?>
	if (image.substr(image.length-4, 4) == ".gif") {
		icon.image = image;
	} else {
		dd = new Date();
		ts = dd.getTime();
		if (image.indexOf('?') < 0) {
			icon.image = image+"?dummy="+ts+".gif";
		} else {
			icon.image = image+"&dummy="+ts+".gif";
		}
	}
	// 2008/11/26 Y.Matsukawa add ]
	if(shadowimage) {
		icon.shadowsize = new ZdcSize(shadowsizew, shadowsizeh);
		icon.shdoffset = new ZdcPixel(shdoffsetx,shdoffsety);
		icon.shadowimage   = shadowimage;
	}
	icon.msgoffset = new ZdcPixel(msgoffsetx,msgoffsety);
	//�ޡ������κ���
	p   = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	mrk = new ZdcMarker(p, icon);
	//�ޡ������δ��ܾ���
	mrk.id     = id;
	mrk.data1  = data1;
	mrk.data2  = data2;
	mrk.nflg   = nflg;
	if (lvl) mrk.lvl = lvl;			// add 2009/09/04 Y.Matsukawa
	mrk.Point  = p;
	mrk.mouseclickmarker = mouseclickmarker;
	mrk.mouseovermarker  = mouseovermarker;
	mrk.mouseoutmarker   = mouseoutmarker;
	//�ޡ���������å����Υ��٥����Ͽ
	if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
	if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
	if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
	// ���٥�Ȥʤ��λ��ϥޥ�������������ѹ����ʤ�		add 2010/02/02 Y.Matsukawa
	if (!mrk.mouseclickmarker && !mrk.mouseovermarker) mrk.setType('static');

	return mrk;
}

//-------------------------------------------------------------
//����������Ͽ(API2.0��)	add 2011/07/07 H.osamoto
//-------------------------------------------------------------
var rtnhtml;
function ZdcEmapMakeMrkApi2(id,lat,lon,
						sizew,sizeh,newsizew,newsizeh,
						offsetx,offsety,newoffsetx,newoffsety,
						image,newimage,
						data1,data2,message,nflg,
						mouseclickmarker,
						mouseovermarker,
						lvl
						) {
	var mrk;
	var w;
	var h;
	var latlon = new ZDC.LatLon(lat, lon);
	var iconimage
	
	// icon.image����������.gif�פǤʤ��ȡ�����Ū��GIF�ʳ��Ȥ��ƽ�������Ƥ��ޤ��Τǡ�������̵��������.gif�פˤ��Ƥ��ޤ���
	// GIF�ʳ��ǽ�������Ƥ��ޤ��ȡ�IE�ǰ�������Ʃ��GIF��Ʃ�ᤷ�ޤ���
	// �����ॹ������ͤ��ղä��Ƥ���Τϡ�����å��������Τ���Ǥ������줬�ʤ��ȡ�������������򺹤��ؤ����ݤ�ɽ��������뤳�Ȥ�����ޤ�����IE�Τߡ�
	if (image.substr(image.length-4, 4) == ".gif") {
		iconimage = image;
	} else {
		dd = new Date();
		ts = dd.getTime();
		if (image.indexOf('?') < 0) {
			iconimage = image+"?dummy="+ts+".gif";
		} else {
			iconimage = image+"&dummy="+ts+".gif";
		}
	}	
	
	if (newimage) {
		//��������κ�����new��������ͭ��ξ���
		mrk = new ZDC.Marker(latlon,{
			/* �ޡ����Υ������˹�碌�ư��֤�Ĵ������ */
			offset: new ZDC.Pixel(offsetx, offsety),
			contentOffset: new ZDC.Pixel(newoffsetx, newoffsety),
			custom: {
				base : {
					src: iconimage,
					imgSize: ZDC.WH(sizew, sizeh)
				},
				content : {
					src: newimage,
					imgSize: ZDC.WH(newsizew, newsizeh)
				}
			}
		});
	} else {
		//��������κ������̾��
		mrk = new ZDC.Marker(latlon,{
			/* �ޡ����Υ������˹�碌�ư��֤�Ĵ������ */
			offset: new ZDC.Pixel(offsetx, offsety),
			custom: {
				base : {
					src: iconimage,
					imgSize: ZDC.WH(sizew, sizeh)
				}
			}
		});
	}
	
	
	//�ޡ������δ��ܾ���
	mrk.id     = id;
	mrk.data1  = data1;
	mrk.data2  = data2;
	mrk.nflg   = nflg;
	mrk.lat     = lat;
	mrk.lon     = lon;
	if (lvl) mrk.lvl = lvl;			// add 2009/09/04 Y.Matsukawa
	
	//����å����Υ��٥����Ͽ
	if (mouseclickmarker) {
		//�᤭�Ф��ƥ������ѥ��󥫡����٥��
		ZDC.addListener(mrk, ZDC.MARKER_CLICK, mouseclickmarker);
	}

	//�ޥ��������С����Υ��٥����Ͽ
	if (mouseovermarker) {
		var center = ZdcEmapMapObj.getLatLon();
		var box = ZdcEmapMapObj.getLatLonBox();
		var maplatlen = box.getMax().lat - box.getMin().lat;
		var maplonlen = box.getMax().lon - box.getMin().lon;
		
		
		//ɽ�����֤�Ĵ��
		if (center.lat > lat) {
			//�Ͽ��濴��겼¦��ɽ��������
			var offsetycenter1 = 10;
			var offsetycenter2 = 90;
			var offsety = -40;
		} else {
			//�Ͽ��濴����¦��ɽ��������
			var offsetycenter1 = -10;
			var offsetycenter2 = -120;
			var offsety = 25;
		}
		if (center.lon > lon) {
			//�Ͽ��濴��꺸¦��ɽ��������
			var offsetxcenter1 = 10;
			var offsetxcenter2 = 102;
			var offsetx = 20;
		} else {
			//�Ͽ��濴��걦¦��ɽ��������
			var offsetxcenter1 = -10;
			var offsetxcenter2 = -120;
			var offsetx = -170;
		}
		
		
		var mes = message.split("(");
		var userwidgetmoverlabel =
		{
			html: '<div style="background-color: #FFFFFF; font-size:16px; text-align:center; border:1px solid;">'+mes[0]+'</div>',
			size: new ZDC.WH(150, 60),
			offset: new ZDC.Pixel(offsetx, offsety)
		};
		var latlonmover = new ZDC.LatLon(lat, lon);
		var userwidgetmover = new ZDC.UserWidget(latlonmover, userwidgetmoverlabel);
		
		//�᤭�Ф��ƥ����ȥ��٥��
		ZdcEmapMapObj.addWidget(userwidgetmover);
		//ZDC.addListener(mrk, ZDC.MARKER_MOUSEOVER, function(){userwidgetmover.open();});
		//ZDC.addListener(mrk, ZDC.MARKER_MOUSEOUT, function(){userwidgetmover.close();});
		
		//�᤭�Ф��ƥ������ѥ��󥫡����٥��
		//ZDC.addListener(mrk, ZDC.MARKER_MOUSEOVER, mouseovermarker);
		//�ޥ��������С����٥����Ͽ
		ZDC.addListener(mrk, ZDC.MARKER_MOUSEOVER, mouseovermarker);
	}
	
	return mrk;
}

//-------------------------------------------------------------
//�᤭�Ф��ѥ��󥫡�	add 2011/07/07 H.osamoto
//-------------------------------------------------------------
var ZdcEmapHukidasiAnchor = null;
function ZdcEmapAnchorDraw(id) {
	ZdcEmapTipsHideInfoInterval();
	//ư��Ƚ��
	if(id == null) id = this.id;
	
	//�إ��������ɸ����
	var icnlat = ZdcEmapMapPoiMrkId[id].lat;
	var icnlon = ZdcEmapMapPoiMrkId[id].lon;
	
	var center = ZdcEmapMapObj.getLatLon();
	var box = ZdcEmapMapObj.getLatLonBox();
	var maplatlen = box.getMax().lat - box.getMin().lat;
	var maplonlen = box.getMax().lon - box.getMin().lon;
	
	var s = ZdcEmapMapObj.getZoom();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//���֥������Ȥκ���
	ZdcEmapTipsMarker = ZdcEmapMapPoiMrkId[id];
	if(!ZdcEmapMapObj || !ZdcEmapTipsMarker) return;
	
	//ɽ�����֤�Ĵ��
	if (center.lat > icnlat) {
		//�Ͽ��濴��겼¦��ɽ��������
		var offsetycenter1 = 3;
		var offsetycenter2 = 22;
	} else {
		//�Ͽ��濴����¦��ɽ��������
		var offsetycenter1 = -3;
		var offsetycenter2 = -30;
	}
	if (center.lon > icnlon) {
		//�Ͽ��濴��꺸¦��ɽ��������
		var offsetxcenter1 = 3;
		var offsetxcenter2 = 25;
	} else {
		//�Ͽ��濴��걦¦��ɽ��������
		var offsetxcenter1 = -3;
		var offsetxcenter2 = -30;
	}
	
	var mrklat1 = ZdcEmapTipsMarker.lat + (offsetycenter1 * (maplatlen / 448));
	var mrklon1 = ZdcEmapTipsMarker.lon + (offsetxcenter1 * (maplonlen / 448));
	var mrklat2 = ZdcEmapTipsMarker.lat + (offsetycenter2 * (maplatlen / 448));
	var mrklon2 = ZdcEmapTipsMarker.lon + (offsetxcenter2 * (maplonlen / 448));
	
	var latlons = [];
	latlons[0] = new ZDC.LatLon(mrklat1, mrklon1);
	latlons[1] = new ZDC.LatLon(mrklat2, mrklon2);
	
	/* ������� */
	var pl = new ZDC.Polyline(latlons, 
	{
		strokeWeight: 1,
		fillColor: '#FF0000'
	});

	/* �����Ͽޤ��ɲ� */
	ZdcEmapMapObj.addWidget(pl);
	
	ZdcEmapHukidasiAnchor = pl;
	ZDC.addListener(ZdcEmapTipsMarker, ZDC.MARKER_MOUSEOUT, function(){pl.hidden();});
}


//-------------------------------------------------------------
//�롼��õ��
//-------------------------------------------------------------
var ZdcEmapRouteOptionsObj;
var ZdcEmapRouteSearchObj;
var ZdcEmapRoutePoint1 = null;
var ZdcEmapRoutePoint2 = null;
var ZdcEmapRouteName1  = null;
var ZdcEmapRouteName2  = null;
var ZdcEmapRouteFlagLayer;
var ZdcEmapRouteFlagIcon1;
var ZdcEmapRouteFlagIcon2;
var ZdcEmapRouteFlagStartMarker1;
var ZdcEmapRouteFlagStartMarker2;
//����ե�����Ǿ����Ѥ������Ѥ��ѿ������Ƥ���
var ZdcEmapRouteType              = <?PHP echo $D_ROUTE_TYPE; ?>;
var ZdcEmapRouteWalkPSC           = <?PHP echo $D_ROUTE_WALK_PSC; ?>;
var ZdcEmapRouteWalkFloorFlg      = <?PHP echo $D_ROUTE_WALK_FLOORFLG; ?>;
var ZdcEmapRouteWalkDepFloor      = <?PHP echo $D_ROUTE_WALK_DEP_FLOOR; ?>;
var ZdcEmapRouteWalkDepStationFlg = <?PHP echo $D_ROUTE_WALK_DEP_STATIONFLG; ?>;
var ZdcEmapRouteWalkArrFloorFlg   = <?PHP echo $D_ROUTE_WALK_ARR_FLOORFLG; ?>;
var ZdcEmapRouteWalkArrStationFlg = <?PHP echo $D_ROUTE_WALK_ARR_STATIONFLG; ?>;
var ZdcEmapRouteWalkArrFloor      = <?PHP echo $D_ROUTE_WALK_ARR_FLOOR; ?>;
//���������(API2.0��)	add 2011/07/07 H.osamoto
function ZdcEmapRouteSearchApi2(id) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapRouteType == 0) return;
	ZdcEmapPoiRouteClear();
	
	var stationpoint = ZdcEmapMapPoiMrkId[id];
	var shoppoint = ZdcEmapMapShopDetailMrkId;
	
	//�ѥ�᡼����������
	ZdcEmapRoutePoint1 = new ZDC.LatLon(stationpoint.lat, stationpoint.lon);
	ZdcEmapRoutePoint2 = new ZDC.LatLon(shoppoint.lat, shoppoint.lon);
	
	if(ZdcEmapRouteType == 1 || ZdcEmapRouteType == 3)
		ZdcEmapRouteSearchWalkApi2(stationpoint, shoppoint);

	//���̤ΰ�ư
	ZdcEmapMapMoveBoxApi2(stationpoint.lat,stationpoint.lon,shoppoint.lat,shoppoint.lon);
}
//���������
function ZdcEmapRouteSearch(name1,mx1,my1,name2,mx2,my2) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapRouteType == 0) return;
	ZdcEmapPoiRouteClear();
	
	//�ѥ�᡼����������
	ZdcEmapRouteName1 = name1;
	ZdcEmapRouteName2 = name2;
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.Osamoto [
	//	ZdcEmapRoutePoint1 = new ZdcPoint(mx1, my1, <?PHP echo $D_PFLG; ?>);
	//	ZdcEmapRoutePoint2 = new ZdcPoint(mx2, my2, <?PHP echo $D_PFLG; ?>);
<?php ��ɽ����λ */ ?>
	var stationpoint = new ZDC.LatLon(Number(my2), Number(mx2));
	var shoppoint = new ZDC.LatLon(Number(my1), Number(mx1));
	ZdcEmapRoutePoint1 = stationpoint;
	ZdcEmapRoutePoint2 = shoppoint;
	// mod 2011/07/07 H.Osamoto ]
	
	if(ZdcEmapRouteType == 1 || ZdcEmapRouteType == 3)
		//ZdcEmapRouteSearchWalk(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);	mod 2011/07/07 H.osamoto
		ZdcEmapRouteSearchWalkApi2(stationpoint, shoppoint);
<?php /* ��ɽ������ ?>
//	if(ZdcEmapRouteType == 2)
//		ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);		del 2011/07/07 H.osamoto
<?php ��ɽ����λ */ ?>

	//���̤ΰ�ư
	//ZdcEmapMapMoveBox(my1,mx1,my2,mx2);		mod 2011/07/07 H.osamoto
	ZdcEmapMapMoveBoxApi2(stationpoint.lat,stationpoint.lon,shoppoint.lat,shoppoint.lon);
}
// ��Լԥ롼�ȸ���(API2.0��)	add 2011/07/07 H.osamoto
function ZdcEmapRouteSearchWalkApi2(p1,p2) {
	ZdcEmapReadOn();
	
	/* �������������ΰ��ٷ��� */
	from = p1;
	/* �����������ΰ��ٷ��� */
	to   = p2;
	
	ZDC.Search.getRouteByWalk({
		from: from,
		to: to
	},function(status, res) {
		if (status.code == '000') {
			/* �������� */
			ZdcEmapwriteRoute(status, res, 1);
			ZdcEmapDispRouteDistance(res.route.distance);
		} else {
			/* �������� */
			if(ZdcEmapRouteType == 1) {
				//���Ԥ��ä���缫ư�֤ǺƸ�������
				ZdcEmapRouteSearchCarApi2(ZdcEmapRoutePoint1,ZdcEmapRoutePoint2);
			} else {
				alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + status.code + ']');
			}
			return;
		}
	});
}
// ��ư�֥롼�ȸ���(API2.0��)	add 2011/07/07 H.osamoto
function ZdcEmapRouteSearchCarApi2(p1,p2) {
	//ZdcEmapReadOn();
	
	/* �������������ΰ��ٷ��� */
	from = p1;
	/* �����������ΰ��ٷ��� */
	to   = p2;
	
	ZDC.Search.getRouteByDrive({
		from: from,
		to: to
	},function(status, res) {
		if (status.code == '000') {
			/* �������� */
			ZdcEmapwriteRoute(status, res, 2);
			ZdcEmapDispRouteDistance(res.route.distance);
		} else {
			/* �������� */
			alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + status.code + ']');
			// �롼�ȸ�����λ
			ZdcEmapReadOff();
		}
	});
}
// �롼������	add 2011/07/07 H.osamoto
var ZdcEmapRoutePolyline = [];
var ZdcEmapRouteStartFlag;
var ZdcEmapRouteEndFlag;
function ZdcEmapwriteRoute(status, res, stype) {
	
	var guyde_type = {
		'start': {
			custom: {
				base: {
					src: '<?PHP echo $D_ROUTE_START_IMAGE; ?>',
					imgSize: new ZDC.WH(35, 35),
					imgTL: new ZDC.TL(0, 0)
				}
			},
			offset: ZDC.Pixel(-5, -36)
		},
		'end': {
			custom: {
				base: {
					src: '<?PHP echo $D_ROUTE_GOAL_IMAGE; ?>',
					imgSize: new ZDC.WH(35, 35),
					imgTL: new ZDC.TL(0, 0)
				}
			},
			offset: ZDC.Pixel(-5, -36)
		}
	};
	
	var line_property = {
		//��Լ���
		'�̾���ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'������ƻ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'������ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��ƻ��': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'Ƨ������ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'Ϣ����ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��ʪ����ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��������ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'�费���': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��ϩ��': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'�������ߥ��': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		//��ư����
		'��®ƻϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'�ԻԹ�®ƻϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��ƻ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��������ƻ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'��ƻ�ܸ�ƻ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'����ƻϩ(����)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'����ƻϩ(����¾)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'Ƴ��ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'�ٳ�ϩ(����)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'�ٳ�ϩ(�ܺ�)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'�ե��꡼��ϩ': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'ƻϩ��': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'}
	};



	/* �������Ȥȥ�����Υ���������Ͽޤ˽ž����ޤ� */
	ZdcEmapRouteStartFlag = new ZDC.Marker(from,guyde_type['start']);
	ZdcEmapRouteEndFlag   = new ZDC.Marker(to,guyde_type['end']);
	/*
	�������Ȥȥ�����Υ������åȤ�¾�Υޡ�����
	���ˤʤ�ʤ��褦��z-index�����ꤷ�ޤ�
	*/
	ZdcEmapRouteStartFlag.setZindex(110);
	ZdcEmapRouteEndFlag.setZindex(110);

	ZdcEmapMapObj.addWidget(ZdcEmapRouteStartFlag);
	ZdcEmapMapObj.addWidget(ZdcEmapRouteEndFlag);

	var link = res.route.link;
	
	var latlons = [];
	for (var i=0, j=link.length; i<j; i++) {
		
		if (stype == 1) {
			var opt = line_property[link[i].type.replace(/^\s+|\s+$/g, "")];
		} else {
			var opt = line_property[link[i].roadType.replace(/^\s+|\s+$/g, "")];
		}
		var pl = new ZDC.Polyline([], opt);
		
		for (var k=0, l=link[i].line.length; k<l; k++) {
			pl.addPoint(link[i].line[k]); 
			
			latlons[i] = link[i].line[0];

			if(i == j-1 && k == 1) {
				latlons[i+1] = link[i].line[1];
			}
		}
		ZdcEmapMapObj.addWidget(pl);
		ZdcEmapRoutePolyline[i] = pl;
	}
	/* ����������ɽ���Ǥ���̼ܥ�٥����� */
	var adjust = ZdcEmapMapObj.getAdjustZoom(latlons);
	ZdcEmapMapObj.moveLatLon(adjust.latlon);
	ZdcEmapMapObj.setZoom(adjust.zoom);
	
	// �롼�ȸ�����λ
	ZdcEmapReadOff();

};

// �롼�ȵ�Υɽ��(API2.0��)	add 2011/07/07 H.osamoto
function ZdcEmapDispRouteDistance(dist) {
	
	//�롼�ȵ�Υɽ��
	var ZdcEmapRouteDistance = document.getElementById("ZdcEmapRouteDistance");
	if (ZdcEmapRouteDistance) {
		distance = dist;
		if (distance < 1000) {
			distance = distance+' m';
		} else {
			distance = distance / 100;
			distance = Math.round(distance);
			distance = distance / 10;
			distance += ' km';
		}
		ZdcEmapRouteDistance.innerHTML = distance;
	}
}

//��ԼԸ���
function ZdcEmapRouteSearchWalk(name1,p1,name2,p2) {
	ZdcEmapReadOn();
	//���֥������Ⱥ���
	ZdcEmapRouteOptionsObj = new ZdcPRouteSearchOptions();
	ZdcEmapRouteSearchObj = new ZdcPRouteSearch();
	ZdcEmapRouteOptionsObj.showMarker = false;
	ZdcEmapRouteOptionsObj.pointFlg = <?PHP echo $D_PFLG; ?>;
	ZdcEmapRouteSearchObj.timeout = <?PHP echo $D_ROUTE_TIMEOUT; ?>;
	ZdcEvent.addListener(ZdcEmapRouteSearchObj, 'end', ZdcEmapRouteSearchEndWalk);
	ZdcEmapMapObj.addPRouteSearch(ZdcEmapRouteSearchObj);
	
	//�ǥ��������
	ZdcEmapRouteSearchObj.routeWidth = <?PHP echo $D_ROUTE_WALK_WIDTH; ?>;
	ZdcEmapRouteSearchObj.routeOpacity = "<?PHP echo $D_ROUTE_WALK_OPACITY; ?>";
	ZdcEmapRouteSearchObj.routeColor = "<?PHP echo $D_ROUTE_WALK_COLOR; ?>";
	
	//���ֻ���
	ZdcEmapRouteOptionsObj.arrivalPoint.point = p1;
	ZdcEmapRouteOptionsObj.departurePoint.point = p2;
	
	//����������
	//����
	ZdcEmapRouteOptionsObj.psc = ZdcEmapRouteWalkPSC;
	ZdcEmapRouteOptionsObj.floorFlg = ZdcEmapRouteWalkFloorFlg;
	//������(��ȯ��)
	ZdcEmapRouteOptionsObj.arrivalPoint.name = name1;
	ZdcEmapRouteOptionsObj.arrivalPoint.floorFlg = ZdcEmapRouteWalkArrFloorFlg;
	ZdcEmapRouteOptionsObj.arrivalPoint.stationFlg = ZdcEmapRouteWalkArrStationFlg;
	ZdcEmapRouteOptionsObj.arrivalPoint.floor = ZdcEmapRouteWalkArrFloor;
	//��ȯ��(����)
	ZdcEmapRouteOptionsObj.departurePoint.name = name2;
	ZdcEmapRouteOptionsObj.departurePoint.stationFlg = ZdcEmapRouteWalkDepStationFlg;
	ZdcEmapRouteOptionsObj.departurePoint.floor = ZdcEmapRouteWalkDepFloor;
	//��������
	ZdcEmapRouteSearchObj.search(ZdcEmapRouteOptionsObj);
}
function ZdcEmapRouteSearchEndWalk() {
	ZdcEmapReadOff();
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		//���顼����
		if(ZdcEmapRouteType == 1) {
			//���Ԥ��ä���缫ư�֤ǺƸ�������
			ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);
		} else {
			alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + result.status + ']');
		}
		return;
	}
	//�������ȡ�������Υ������������
	ZdcEmapRouteFlag();
	//�롼�ȵ�Υɽ��		add 2010/07/23 Y.Matsukawa
	var ZdcEmapRouteDistance = document.getElementById("ZdcEmapRouteDistance");
	if (ZdcEmapRouteDistance) {
		distance = result.distance;
		if (distance < 1000) {
			distance = distance+' m';
		} else {
			distance = distance / 100;
			distance = Math.round(distance);
			distance = distance / 10;
			distance += ' km';
		}
		ZdcEmapRouteDistance.innerHTML = distance;
	}
}
//��ư�ָ���
function ZdcEmapRouteSearchCar(name1,p1,name2,p2) {
	ZdcEmapReadOn();
	//���֥������Ⱥ���
	ZdcEmapRouteOptionsObj = new ZdcRouteSearchOptions();
	ZdcEmapRouteSearchObj = new ZdcRouteSearch();
	ZdcEmapRouteOptionsObj.showMarker = false;
	ZdcEmapRouteOptionsObj.pointFlg = <?PHP echo $D_PFLG; ?>;
	ZdcEmapRouteSearchObj.timeout = <?PHP echo $D_ROUTE_TIMEOUT; ?>;
	ZdcEvent.addListener(ZdcEmapRouteSearchObj, 'end', ZdcEmapRouteSearchEndCar);
	ZdcEmapMapObj.addRouteSearch(ZdcEmapRouteSearchObj);
	
	//�ǥ��������
	ZdcEmapRouteSearchObj.routeWidth = <?PHP echo $D_ROUTE_CAR_WIDTH; ?>;
	ZdcEmapRouteSearchObj.routeOpacity = "<?PHP echo $D_ROUTE_CAR_OPACITY; ?>";
	ZdcEmapRouteSearchObj.routeColor = "<?PHP echo $D_ROUTE_CAR_COLOR; ?>";
	
	//���ֻ���
	ZdcEmapRouteOptionsObj.arrivalPoint = p1;
	ZdcEmapRouteOptionsObj.departurePoint = p2;

	//��������
	ZdcEmapRouteSearchObj.search(ZdcEmapRouteOptionsObj);
}
function ZdcEmapRouteSearchEndCar() {
	ZdcEmapReadOff();
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		//���顼����
		alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + result.status + ']');
		return;
	}
	//�������ȡ�������Υ������������
	ZdcEmapRouteFlag();
	//�롼�ȵ�Υɽ��		add 2010/07/23 Y.Matsukawa
	var ZdcEmapRouteDistance = document.getElementById("ZdcEmapRouteDistance");
	if (ZdcEmapRouteDistance) {
		distance = result.distance;
		if (distance < 1000) {
			distance = distance+' m';
		} else {
			distance = distance / 100;
			distance = Math.round(distance);
			distance = distance / 10;
			distance += ' km';
		}
		ZdcEmapRouteDistance.innerHTML = distance;
	}
}
//�롼�Ⱥ��
function ZdcEmapPoiRouteClear() {
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.Osamoto [
	//	if(!ZdcEmapRouteSearchObj) return;
	//	if(ZdcEmapRouteOptionsObj.departurePoint.point) {
	//		try{
	//			ZdcEmapMapObj.ClearPRouteLayer();//1.5�ޤ�
	//		} catch(e) {
	//			ZdcEmapRouteSearchObj.clearRoute();//1.6�ʹ�
	//		}
	//	} else {
	//		ZdcEmapMapObj.removeRouteSearch();
	//	}
	//	delete ZdcEmapRouteOptionsObj;
	//	delete ZdcEmapRouteSearchObj;
	//	//�������ȡ�������Υ쥤�䡼����
	//	if(ZdcEmapRouteFlagLayer) ZdcEmapRouteFlagLayer.clearMarker();
	//	ZdcEmapMapObj.removeUserLayer(ZdcEmapRouteFlagLayer);
	//	delete ZdcEmapRouteFlagIcon1;
	//	delete ZdcEmapRouteFlagIcon2;
<?php ��ɽ����λ */ ?>
	if(!ZdcEmapRoutePolyline.length) return;
	
	for (var i=0; i<ZdcEmapRoutePolyline.length; i++) {
		if (ZdcEmapRoutePolyline[i]) {		<?php // add 2012/03/16 H.Osamoto ?>
			ZdcEmapMapObj.removeWidget(ZdcEmapRoutePolyline[i]);
			delete ZdcEmapRoutePolyline[i];
		}
	}
	
	//�������ȡ�������Υ쥤�䡼����
	if(ZdcEmapRouteStartFlag){
		ZdcEmapMapObj.removeWidget(ZdcEmapRouteStartFlag);
		delete ZdcEmapRouteStartFlag;
	}
	if(ZdcEmapRouteEndFlag){
		ZdcEmapMapObj.removeWidget(ZdcEmapRouteEndFlag);
		delete ZdcEmapRouteEndFlag;
	}
	
	// mod 2011/07/07 H.Osamoto ]
}
//�롼�ȳ��ϡ���λ�����Υ������������
function ZdcEmapRouteFlag() {
	//�桼���쥤�䡼����
	ZdcEmapRouteFlagLayer = new ZdcUserLayer();
	ZdcEmapRouteFlagLayer.setLayerScale(1, 18);
	ZdcEmapRouteFlagLayer.setLayerType('manual');
	//�����������
	ZdcEmapRouteFlagIcon1 = new ZdcIcon();
	ZdcEmapRouteFlagIcon1.offset = new ZdcPixel(<?PHP echo $D_ROUTE_GOAL_OFFSET_X; ?>, <?PHP echo $D_ROUTE_GOAL_OFFSET_Y; ?>);
	ZdcEmapRouteFlagIcon1.image = '<?PHP echo $D_ROUTE_GOAL_IMAGE; ?>';
	ZdcEmapRouteFlagIcon2 = new ZdcIcon();
	ZdcEmapRouteFlagIcon2.offset = new ZdcPixel(<?PHP echo $D_ROUTE_START_OFFSET_X; ?>, <?PHP echo $D_ROUTE_START_OFFSET_Y; ?>);
	ZdcEmapRouteFlagIcon2.image = '<?PHP echo $D_ROUTE_START_IMAGE; ?>';
	//�桼���쥤�䡼���ɲ�
	if(ZdcEmapRoutePoint1) ZdcEmapRouteFlagLayer.addMarker(new ZdcMarker(ZdcEmapRoutePoint1, ZdcEmapRouteFlagIcon1));
	if(ZdcEmapRoutePoint2) ZdcEmapRouteFlagLayer.addMarker(new ZdcMarker(ZdcEmapRoutePoint2, ZdcEmapRouteFlagIcon2));
	//�Ͽޤ˥桼���쥤�䡼���ɲ�
	ZdcEmapMapObj.addUserLayer(ZdcEmapRouteFlagLayer);
	//�롼�ȥ쥤�䡼�ξ�˰�ư
	ZdcEmapRouteFlagLayer.doc.style.zIndex = "3999";
}



//-------------------------------------------------------------
//��ư�����Υ��٥�ȴ���
//-------------------------------------------------------------
var ZdcEmapSearchEventFlg  = 0;
var ZdcEmapSearchEventFunc = null;
var ZdcEmapSearchEventDragmapend;
var ZdcEmapSearchEventScrollmapend;
var ZdcEmapSearchEventChangezoomend;
//�����¹�
function ZdcEmapSearchEventAction() {
	if(!ZdcEmapSearchEventFlg) return;
	// 2011/06/15 K.Masuda mod [
	//if(ZdcEmapMapObj.getUserMsgOpenStatus()) return;//�ե�����ɽ����ϸ������ʤ�
	if( <?php if(isset($D_HUKIDASHI_SEARCH) && $D_HUKIDASHI_SEARCH){echo "false";}else{echo "true";} // mod 2011/10/03 Y.Nakajima ?> ){
		//	if(ZdcEmapMapObj.getUserMsgOpenStatus()) return;//�ե�����ɽ����ϸ������ʤ�	mod 2011/07/07 H.osamoto
		if(userwidgethukidasi) {
			if(userwidgethukidasi.kg) {
				return;//�ե�����ɽ����ϸ������ʤ�
			}
		}
	}
	// 2011/06/15 K.Masuda mod ]
	ZdcEmapSearchPoint = null;		// add 2011/07/07 H.osamoto
	eval(ZdcEmapSearchEventFunc);
}
//�������٥���ɲ�
function ZdcEmapSearchEventAdd(func) {
	ZdcEmapSearchEventDel();
	ZdcEmapSearchEventFunc = func;
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapSearchEventDragmapend    = ZdcEvent.addListener(ZdcEmapMapObj, "dragmapend"   , ZdcEmapSearchEventAction);
	//	ZdcEmapSearchEventScrollmapend  = ZdcEvent.addListener(ZdcEmapMapObj, "scrollmapend" , ZdcEmapSearchEventAction);
	//	ZdcEmapSearchEventChangezoomend = ZdcEvent.addListener(ZdcEmapMapObj, "changezoomend", ZdcEmapSearchEventAction);
<?php ��ɽ����λ */ ?>
	ZdcEmapSearchEventDragmapend    = ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_DRAG_END, ZdcEmapSearchEventAction);
	ZdcEmapSearchEventScrollmapend  = ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_SCROLL_END, ZdcEmapSearchEventAction);
	ZdcEmapSearchEventChangezoomend = ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_CHG_ZOOM, ZdcEmapSearchEventAction);
	// mod 2011/07/07 H.osamoto [
}
//�������٥�Ⱥ��
function ZdcEmapSearchEventDel() {
	ZdcEmapSearchEventStop();
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.osamoto [
	//	if(ZdcEmapSearchEventDragmapend)    ZdcEvent.removeListener(ZdcEmapSearchEventDragmapend);
	//	if(ZdcEmapSearchEventScrollmapend)  ZdcEvent.removeListener(ZdcEmapSearchEventScrollmapend);
	//	if(ZdcEmapSearchEventChangezoomend) ZdcEvent.removeListener(ZdcEmapSearchEventChangezoomend);
<?php ��ɽ����λ */ ?>
	if(ZdcEmapSearchEventDragmapend)    ZDC.removeListener(ZdcEmapSearchEventDragmapend);
	if(ZdcEmapSearchEventScrollmapend)  ZDC.removeListener(ZdcEmapSearchEventScrollmapend);
	if(ZdcEmapSearchEventChangezoomend) ZDC.removeListener(ZdcEmapSearchEventChangezoomend);
	// mod 2011/07/07 H.osamoto ]
	
	ZdcEmapSearchEventDragmapend = null;
	ZdcEmapSearchEventScrollmapend = null;
	ZdcEmapSearchEventChangezoomend = null;
	delete ZdcEmapSearchEventFunc;
}
//�������٥�ȳ���
function ZdcEmapSearchEventStart() {
	ZdcEmapSearchEventFlg = 1;
}
//�������٥�����
function ZdcEmapSearchEventStop() {
	ZdcEmapSearchEventFlg = 0;
}



//-------------------------------------------------------------
//�᤭�Ф�
//  Shape�쥤�䡼������ȥ���å����������ʤ������䤳���������򤷤Ƥ���
//  ��äȴ�ñ�˼����Ǥ���褦�ˤʤä�����ľ������
//-------------------------------------------------------------
var ZdcEmapTipsInterval = 5000;//�ʰ�ʮ�Ф�ɽ���ֳ�
var ZdcEmapTipsTimerID = null;//����Ū��ʮ�Ф���ä������ޡ�ID
var ZdcEmapTipsMarker = null;//ʮ�Ф�ɽ���Υޡ��������֥�������
var ZdcEmapTipsShapeLayer = null;//ʮ�Ф��쥤�䡼
var ZdcEmapTipsShape = null;//�ʰ�ʮ�Ф��������ץ��֥�������
var ZdcEmapTipsTopMarker = null;//�Ǿ��ɽ���Ѱ���ޡ������쥤�䡼
var ZdcEmapTipsTopMarkerLayer = null;//�Ǿ��ɽ���Ѱ���ޡ��������֥�������
//���ߥǡ����δʰ�ʮ�Ф�ɽ���᥽�å�
function ZdcEmapTipsClick(id) {
	ZdcEmapTipsHideInfoInterval();
	//ư��Ƚ��
	if(id == null) id = this.id;
	//	var s = ZdcEmapMapObj.getMapScale();	mod 2011/07/07 H.Osamoto
	var s = ZdcEmapMapObj.getZoom();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//���֥������Ȥκ���
	//	ZdcEmapTipsMarker = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapPoiMrkId[id]);	mod 2011/07/07 H.Osamoto
	ZdcEmapTipsMarker = ZdcEmapMapPoiMrkId[id];
	if(!ZdcEmapMapObj || !ZdcEmapTipsMarker) return;
<?php /* ��ɽ������ ?>
	// mod 2011/07/07 H.Osamoto [
	//	if(!ZdcEmapTipsShape) ZdcEmapTipsShape = new ZdcShape.Text();
	//	if(!ZdcEmapTipsShapeLayer) ZdcEmapTipsShapeLayer = new ZdcShape.Layer();
	//	ZdcEmapMapObj.addShapeLayer(ZdcEmapTipsShapeLayer);
	//	ZdcEmapTipsShapeLayer.setZIndex(4010);
	//	//�ƥ����Ȥ�����
	//	ZdcEmapTipsShape.textString = ZdcEmapTipsMarker.data1;
	//	ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	//	ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	//	ZdcEmapTipsShape.font = "<?PHP echo $D_TIPS_FONT; ?>";
	//	ZdcEmapTipsShape.borderWidth = <?PHP echo $D_TIPS_BORDERWIDTH; ?>;
	//	ZdcEmapTipsShape.bgColor = "<?PHP echo $D_TIPS_BGCOLOR; ?>";
	//	ZdcEmapTipsShape.shadowFlg = <?PHP echo $D_TIPS_SHADOWFLG; ?>;
	//	ZdcEmapTipsShape.shadowX = <?PHP echo $D_TIPS_SHADOWX; ?>;
	//	ZdcEmapTipsShape.shadowY = <?PHP echo $D_TIPS_SHADOWY; ?>;
	//	ZdcEmapTipsShape.opacity = <?PHP echo $D_TIPS_OPACITY; ?>;
	//	//ɽ�����֤�Ĵ��
	//	var box = ZdcEmapMapObj.getMapBoundBox();
	//	var point = new ZdcPoint(ZdcEmapTipsMarker.Point.mx, ZdcEmapTipsMarker.Point.my, <?PHP echo $D_PFLG; ?>);
	//	var x,y,v,h;
	//	if(Math.abs(box.minx - point.mx) < Math.abs(box.maxx - point.mx)){ 
	//		h = "left"; 
	//		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	//	}else{
	//		h = "right";
	//		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X*-1; ?>;
	//	}
	//	if(Math.abs(box.miny - point.my) < Math.abs(box.maxy - point.my)){
	//		v = "bottom";
	//		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y*-1; ?>;
	//	}else{
	//		v = "top";
	//		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	//	}
	//	ZdcEmapTipsShape.anchor = h + "-" + v;
	//	ZdcEmapTipsShape.setPoint(point);
	//	ZdcEmapTipsShapeLayer.addShape(ZdcEmapTipsShape);
	//	//�����濴���Ͽ��ϰϳ��ξ���ư����
	//	if(ZdcEmapTipsMarker.Point.mx < box.minx || ZdcEmapTipsMarker.Point.my < box.miny || ZdcEmapTipsMarker.Point.mx > box.maxx || ZdcEmapTipsMarker.Point.my > box.maxy)
	//		ZdcEmapMapObj.setMapLocation(ZdcEmapTipsMarker.Point);
	//	//����
	//	if(!ZdcEmapTipsTopMarkerLayer) ZdcEmapTipsTopMarkerLayer = new ZdcUserLayer();//�Ǿ�̥ޡ������쥤�䡼
	//	if(!ZdcEmapTipsTopMarker) ZdcEmapTipsTopMarker = new ZdcMarker(new ZdcPoint(ZdcEmapTipsMarker.getPoint().lon ,ZdcEmapTipsMarker.getPoint().lat), ZdcEmapTipsMarker.getIcon());
	//	ZdcEmapTipsTopMarkerLayer.addMarker(ZdcEmapTipsTopMarker);
	//	ZdcEmapMapObj.addUserLayer(ZdcEmapTipsTopMarkerLayer);
	//	ZdcEmapTipsTopMarkerLayer.doc.style.zIndex = 4011;
	//	ZdcEmapTipsTopMarker.mouseclickmarker = ZdcEmapTipsMarker.mouseclickmarker;
	//	//���٥�Ȥ�����
	//	if(ZdcEmapTipsTopMarker.mouseclickmarker) ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseclickmarker", ZdcEmapTipsTopMarker.mouseclickmarker);
	//	ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseoutmarker", ZdcEmapTipsHideInfo);
	//	ZdcEmapTipsTimerID = setTimeout(ZdcEmapTipsHideInfoInterval, ZdcEmapTipsInterval);
<?php ��ɽ����λ */ ?>
	
	var lat = ZdcEmapTipsMarker.lat;
	var lon = ZdcEmapTipsMarker.lon;
	var center = ZdcEmapMapObj.getLatLon();
	var box = ZdcEmapMapObj.getLatLonBox();
	var maplatlen = box.getMax().lat - box.getMin().lat;
	var maplonlen = box.getMax().lon - box.getMin().lon;
	
	
	//ɽ�����֤�Ĵ��
	if (center.lat > lat) {
		//�Ͽ��濴��겼¦��ɽ��������
		var offsetycenter1 = 10;
		var offsetycenter2 = 90;
		var offsety = -40;
	} else {
		//�Ͽ��濴����¦��ɽ��������
		var offsetycenter1 = -10;
		var offsetycenter2 = -120;
		var offsety = 25;
	}
	if (center.lon > lon) {
		//�Ͽ��濴��꺸¦��ɽ��������
		var offsetxcenter1 = 10;
		var offsetxcenter2 = 102;
		var offsetx = 20;
	} else {
		//�Ͽ��濴��걦¦��ɽ��������
		var offsetxcenter1 = -10;
		var offsetxcenter2 = -120;
		var offsetx = -170;
	}
	
	var message = ZdcEmapTipsMarker.message;
	var mes = message.split("(");
	var userwidgetmoverlabel =
	{
		html: '<div style="background-color: #FFFFFF; font-size:16px; text-align:center; padding-top: 3px; padding-bottom: 2px; border:1px solid;">'+mes[0]+'</div>',
		size: new ZDC.WH(150, 60),
		offset: new ZDC.Pixel(offsetx, offsety)
	};
	var latlonmover = new ZDC.LatLon(lat, lon);
	var userwidgetmover = new ZDC.UserWidget(latlonmover, userwidgetmoverlabel);
	
	
	//�᤭�Ф�ɽ��
	ZdcEmapMapObj.addWidget(userwidgetmover);
	ZDC.addListener(ZdcEmapTipsMarker, ZDC.MARKER_MOUSEOUT, function(){userwidgetmover.close();});
	ZdcEmapAnchorDraw(id);
	userwidgetmover.open();
	ZdcEmapTipsShapeLayer = userwidgetmover;
	ZdcEmapTipsTimerID = setTimeout(ZdcEmapTipsHideInfoInterval, ZdcEmapTipsInterval);
	
	// mod 2011/07/07 H.Osamoto ]
}
//�쥤�䡼���Ĥ���
function ZdcEmapTipsClose() {
	//�������ץ쥤�䡼���Ĥ���
	if(ZdcEmapTipsShapeLayer)
	{
		ZdcEmapTipsShapeLayer.close();
	}
	if(ZdcEmapHukidasiAnchor)
	{
		ZdcEmapMapObj.removeWidget(ZdcEmapHukidasiAnchor);
	}
	ZdcEmapTipsShapeLayer = null;
	ZdcEmapTipsShape = null;
	ZdcEmapHukidasiAnchor = null;
	//�Ǿ�̥ޡ������쥤�䡼���Ĥ���
	if(ZdcEmapTipsTopMarkerLayer)
	{
		ZdcEmapTipsTopMarkerLayer.clearMarker();
		ZdcEmapMapObj.removeUserLayer(ZdcEmapTipsTopMarkerLayer);
		ZdcEmapTipsTopMarker.mouseclickmarker = null;
	}
	ZdcEmapTipsTopMarker = null;
	ZdcEmapTipsTopMarkerLayer = null;
	//�����ޡ��Υ��ꥢ
	if(ZdcEmapTipsTimerID) clearTimeout(ZdcEmapTipsTimerID);
	ZdcEmapTipsTimerID = null;
}
//����Ū�˴ʰ�ʮ�Ф���ɽ���᥽�å�
function ZdcEmapTipsHideInfoInterval() {
	if(ZdcEmapTipsTimerID) clearTimeout(ZdcEmapTipsTimerID);
	ZdcEmapTipsTimerID = null;
	ZdcEmapTipsClose();
}
//�ʰ�ʮ�Ф���ɽ���᥽�å�
function ZdcEmapTipsHideInfo() {
	if(!ZdcEmapTipsIsMouseOutMarker()) return;
	ZdcEmapTipsClose();
}
//IE��mouseout���٥�Ȥ��ޡ��������֥������ȤλҥΡ��ɤδ֤�ȯ�����Ƥ��뤫�ɤ���
function ZdcEmapTipsIsMouseOutMarker() {
	if(!document.all) return true;
	if(!ZdcEmapTipsTopMarker) return true;
	if(!window.event || window.event.type != "mouseout") return false;
	var tmp = window.event.toElement;
	while(tmp) {
		if(tmp == ZdcEmapTipsTopMarker.doc) return false;
		tmp = tmp.parentElement;
	}
	return true;
}



//-------------------------------------------------------------
//����¾
//-------------------------------------------------------------
//HTML�ɤ߹�����ajax�̿��ؿ�
//function ZdcEmapHttpRequestHtml(url,func) {		mod 2009/02/16 Y.Matsukawa
function ZdcEmapHttpRequestHtml(url,func,nowaitmsg) {
	//ZdcEmapReadOn();//�ɤ߹�����ե饰on		mod 2009/02/16 Y.Matsukawa
	if(!nowaitmsg) ZdcEmapReadOn();//�ɤ߹�����ե饰on
	//�̿�����
	var ZdcEmapHttpRequestObj = new ZdcEmapHttpRequest('EUC', 'EUC');
	ZdcEmapHttpRequestObj.request(url, function(html,status) {
		if(status == 3) status = 0;//�����ॢ���Ȥ�̵�� Ϣ³�ƤӽФ�����ư����ꤷ�ʤ��Τ�
		if(status == 9) status = 0;//�ƥ�ץ졼�Ȥ�̵�������б�
		if(html == null) html = "";//null�ϽФ��ʤ�
		if(status == 0) {
			func(html,status);
		} else {
			//���顼����
			func(html,status);
		}
		ZdcEmapReadOff();//�ɤ߹�����ե饰off
	},<?PHP echo $D_AJAX_TIMEOUT; ?>);
}
//�ܥ��󲡲�����Ƚ��
function ZdcEmapButtonNG() {
	if(ZdcEmapReadCheck()) return 1;//�ɤ߹������ư�����
	if(ZdcEmapSearchWindowObj.innerHTML != "") return 1;//����������ɥ��������Ƥ���

	return 0;
}
//�ɤ߹�����ե饰
var ZdcEmapReading = 0;//�ɤ߹����桦������ե饰
function ZdcEmapReadOn() {
	ZdcEmapReading ++;
	//if(ZdcEmapReading == 1) ZdcEmapMapObj.visibleZdcWait();		del 2011/07/07 H.osamoto
}
function ZdcEmapReadOff() {
	if(ZdcEmapReading <= 0) return;
	ZdcEmapReading --;
	//if(ZdcEmapReading == 0) ZdcEmapMapObj.hiddenZdcWait();		del 2011/07/07 H.osamoto
}
function ZdcEmapReadCheck() {
	if(ZdcEmapReading > 0) return 1;//�ɤ߹������ư�����
	return 0;
}
//���ꤵ�줿�ء����ߥ�����������̤ˤ�äƤ���
function ZdcEmapMapFrontPoi(id){
	if(ZdcEmapMapPoiMrkId[id] != null) {
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapPoiMrkId[id]);
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[id]);
		ZdcEmapMapPoiMrkId[id] = ZdcEmapMapUserLyr.addMarker(mrk);
		//���٥�����Ƥʤ���
		if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
		if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
		if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
	}
}

<?php /* ��ɽ������ ?>
// del 2011/07/07 H.osamoto [
//	// ������������̤˰�ư��APIv1.10�Ǽ���ͽ��ε�ǽ����Ԥ��Ƽ�����		add 2009/10/14 Y.Matsukawa
//	//v110 add -- set top zindex for marker
//	ZdcMarker.prototype.setTopZIndex=function(idx){
//	//	if (this.parentLayer.addmapstatus){
//	//		for (var i=0; i<this.parentLayer.markers.length; i++){
//	//			if (this.parentLayer.markers[i]!=null){
//	//				this.parentLayer.markers[i].doc.style.zIndex = 3;
//	//			}
//	//		}
//	//	}
//		if (idx) {
//			this.doc.style.zIndex = idx;
//		} else {
//			this.doc.style.zIndex = 4;
//		}
//	}
//	//v110 add -- set defalut zindex for marker
//	ZdcMarker.prototype.setDefaultZIndex=function(){
//		//this.doc.style.zIndex = 0;
//		this.doc.style.zIndex = 3;
//	}
// del 2011/07/07 H.osamoto ]
<?php ��ɽ����λ */ ?>

// add 2011/07/07 H.osamoto [
//common func
ZdcSetErrorStatus = function(retcd, st){
	var status;
	if (st == undefined){
		var errPart = retcd.charAt(4);
		var errPartStr = retcd.slice(3, 5);
		if( errPart == '9' ){
			status = 1;		//�ѥ�᡼�����顼
		}else if( retcd.substr(4,4) == '1009' ){
			status = 5;		//�����ǡ����ʤ�
		}else if ( errPart == '2' ){
			status = 6;		//ǧ�ڥ��顼
		}else if ( errPart == '6' || errPart == '7' || errPart == '8' || errPartStr == '15'){
			status = 2;		//�����С����顼
		}else{
			status = 9;		//����¾���顼
		}
	}else{
		status = st;
	}
	this.retCode  = retcd || '';
	this.type = '';
	this.status = status;
	this.recCount    = 0;
	this.hitCount = 0;
	this.rest =   false;
	this.items = [];
}
// add 2011/07/07 H.osamoto ]


