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
// 2011/07/05 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/11/25 Y.Matsukawa	�ԡ������ǥ��б��ʺǴ��롼�����ѥ⡼�ɡ�
// 2012/05/28 K.Masuda		�ǽ���濴����������ɲ�
// 2015/03/23 K.Iwayoshi	���潻ͧ�����Źͽ���б��������ޥ���
// 2016/11/15 K.Tani		�Ͽ������˺Ƹ������ʤ��⡼��
// ------------------------------------------------------------
include("./inc/define.inc");  // ��������
include("./inc/define_get_icon.inc");  // ��������������
?>
//-------------------------------------------------------------
//JSAPI��ư���ǧ
//-------------------------------------------------------------
if(parseInt(ZDC_RC) != 0) {
	//location.href = '<?PHP echo $D_URL_JSAPIERROR; ?>';
}

//-------------------------------------------------------------
//�������
//-------------------------------------------------------------
//�Ͽ�
var ZdcEmapMapObj = null;
var ZdcEmapMapUsrctl = null;
var ZdcEmapMapZoomctl = null;
var ZdcEmapMapSize = new ZdcWindow();
//�桼�����쥤�䡼
var ZdcEmapMapUserLyr = new ZdcUserLayer();
var ZdcEmapMapUserLyrId = null;
//�ޡ���������
var ZdcEmapMapShopMrkId = new Array(<?PHP echo $D_SHOP_MAX; ?>);
var ZdcEmapMapShopMrkCnt = null;
var ZdcEmapMapPoiMrkId = new Array(<?PHP echo $D_POI_MAX; ?>);
var ZdcEmapMapPoiMrkCnt = null;
var ZdcEmapMapShopDetailMrkId = null;
var ZdcEmapMapCurFocusMrkId = null;
//�᤭�Ф�
var ZdcEmapMsg = new ZdcUserMsgWindow();
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
//�롼��õ���⡼��		<?php // add 2011/11/25 Y.Matsukawa ?>
var ZdcEmapRouteShopItems = null;
var ZdcEmapRouteShopItem = null;
var ZdcEmapRouteStartLat = null;
var ZdcEmapRouteStartLon = null;
//�����������
var ZdcEmapIconImg = new Array();
var ZdcEmapIconW = new Array();
var ZdcEmapIconH = new Array();
var ZdcEmapIconOffsetX = new Array();
var ZdcEmapIconOffsetY = new Array();
<?PHP
foreach( $D_ICON as $key=>$val) {
	printf("ZdcEmapIconImg['%s'] = '%s';",$key,$val["IMG"]);
	printf("ZdcEmapIconW['%s'] = %d;",$key,$val["W"]);
	printf("ZdcEmapIconH['%s'] = %d;",$key,$val["H"]);
	printf("ZdcEmapIconOffsetX['%s'] = %d;",$key,ceil($val["W"]/2)*-1);
	printf("ZdcEmapIconOffsetY['%s'] = %d;",$key,ceil($val["H"]/2)*-1);
}
?>
//����¾
<?php if(isset($D_REQ_JSAPI["zdcmapgeometric"]) && $D_REQ_JSAPI["zdcmapgeometric"]){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapGeometricObj = new ZdcGeometric();
<?php } ?>
var ZdcEmapSaveCond = new Array(<?PHP echo $D_SHOP_MAX; ?>);//�ʹ����
<?PHP //for($i = 0;$i < 50;$i ++) if($_VARS["cond".$i]) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]);		mod 2009/11/07 Y.Matsukawa ?>
<?php //mod 2011/07/05 Y.Nakajima ?>
<?PHP for($i = 1;$i <= 200;$i ++) if(isset($_VARS["cond".$i])) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]); ?>

// add 2011/05/26 K.Masuda [
var QSTRING = location.search.replace(/^\?/, '');
// add 2011/05/26 K.Masuda ]
//������ؿ�
//function ZdcEmapInit(){	2007/11/16 mod Y.Matsukawa
//function ZdcEmapInit(init_lat, init_lon){		2007/11/30 mod Y.Matsukawa
function ZdcEmapInit(init_lat, init_lon, init_lv){
	//�Ͽޤδ������� ----------------------------------------
	var svrurl = "<?PHP echo $D_JS_SVRURL; ?>";
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
	ZdcEmapMapObj = new ZdcMap(document.getElementById("ZdcEmapMap"), 
								new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>),
								init_lv,
								<?PHP echo $D_MAP_LAYER_KBN; ?>);
<?php // add 2011/02/10 Y.Matsukawa ] ?>
	ZdcEmapMapSize = ZdcEmapMapObj.getMapWindowSize();
	//�Ͽ��濴�ޡ��� ---------------------------------	add 2009/05/28 Y.Matsukawa
	<?php if (isset($D_MAPCENTER_MARK) && $D_MAPCENTER_MARK != "" && $D_MAPCENTER_MARK > 0) { ?>
	ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK; ?>'));
	<?php } ?>
	//�桼��������ȥ��� ---------------------------------
	<?PHP echo $D_JSCODE_MAPUSRCTL; ?>
	<?PHP echo $D_JSCODE_MAPZOOMCTL; ?>
	
	//����¾�Ͽ޴ط� ---------------------------------------
	ZdcEmapMapObj.setMouseCursor("hand");	// 2008/04/01 add Y.Matsukawa
	ZdcEmapMapObj.CenterFirst = false;
	ZdcEmapMapObj.setScreenMode();
	//ZdcEmapMapObj.setMapType(<?PHP echo $D_MAP_LAYER_KBN; ?>);		del 2011/02/10 Y.Matsukawa
	ZdcEmapMapObj.reflashMap();
	if(<?PHP echo $D_MAP_SCALE_MAX; ?> > -1 && <?PHP echo $D_MAP_SCALE_MIN; ?> > -1)
		ZdcEmapMapObj.setMapZoomLimit(<?PHP echo $D_MAP_SCALE_MAX; ?>,<?PHP echo $D_MAP_SCALE_MIN; ?>);
	//ɸ�ॳ��ȥ���
	if(ZdcEmapMapUsrctl == null && ZdcEmapMapZoomctl == null && <?PHP echo $D_MAP_CONTROL; ?> > 0)
		ZdcEmapMapObj.addMapControl(new ZdcControl(<?PHP echo $D_MAP_CONTROL; ?>));
	//if (ZdcEmapMapZoomctl) ZdcEmapMapZoomctl.setSlitherPosition();		// add 2011/02/17 Y.Matsukawa	del 2011/02/22 Y.Matsukawa
	//ɸ�ॹ������С�
	if(<?PHP echo $D_MAP_SCALEBAR; ?> > 0) ZdcEmapMapObj.addMapScaleBar(new ZdcScaleBar(<?PHP echo $D_MAP_SCALEBAR; ?>));
	//ɸ���濴��������
	if(<?PHP echo $D_MAP_CENTER; ?> > 0) {
		var obj = new ZdcMapCenter(<?PHP echo $D_MAP_CENTER; ?>);
		obj.doc.zIndex=2999;//������������̤ˤ�äƤ���
		ZdcEmapMapObj.addMapCenter(obj);
	}
	//����ܥå���
	if(<?PHP echo $D_MAP_INFO; ?> > 0) ZdcEmapMapObj.addMapCenterInfoBox(new ZdcMapCenterInfoBox(<?PHP echo $D_MAP_INFO; ?>));

	<?php // add 2010/08/09 Y.Matsukawa [ ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($D_MAP_REMOVE_CONTROL) && $D_MAP_REMOVE_CONTROL != "") { ?>
	//����ȥ���õ�
	ZdcEmapMapObj.removeUserControl();
	ZdcEmapMapObj.removeMapControl();
	<?php } ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($D_MAP_REMOVE_ZOOMCONTROL) && $D_MAP_REMOVE_ZOOMCONTROL != "") { ?>
	//�����ॳ��ȥ���õ�
	ZdcEmapMapObj.removeUserZoomControl();
	<?php } ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($D_MAP_DRAG_OFF) && $D_MAP_DRAG_OFF != "") { ?>
	//�Ͽޥɥ�å��ػ�
	ZdcEmapMapObj.dragOff();
	<?php } ?>
	<?php // add 2010/08/09 Y.Matsukawa ] ?>

	//
	ZdcEmapMapObj.ZdcMapRasterEngine = false;
<?php // del 2011/02/10 Y.Matsukawa [ ?>
	//	//�������
	//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(<?PHP echo $D_INIT_LON; ?>,<?PHP echo $D_INIT_LAT; ?>,<?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);		2007/11/16 mod Y.Matsukawa
	//	if (!init_lat || !init_lon) {
	//		init_lat = <?PHP echo $D_INIT_LAT; ?>;
	//		init_lon = <?PHP echo $D_INIT_LON; ?>;
	//	}
	//	// 2007/11/30 add Y.Matsukawa ��
	//	//if (!init_lv) {		mod 2009/09/04 Y.Matsukawa
	//	if (!init_lv || init_lv == 0) {
	//		init_lv = <?PHP echo $D_INIT_LVL; ?>;
	//	}
	//	// 2007/11/30 add Y.Matsukawa ��
	//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);	2007/11/30 mod Y.Matsukawa
	//	ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), init_lv);
<?php // del 2011/02/10 Y.Matsukawa ] ?>
	ZdcEmapMapObj.saveMapLocation();
	//����å�ư���ʬ
	if(<?PHP echo $D_MAP_CLICK_KBN; ?> == 2) {
		<?PHP // ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnodrag", function(e) {	mod 2010/01/06 Y.Matsukawa ?>
		ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnomove", function(e) {
			this.scrollToCenter(new ZdcPoint(this.MouseCLon,this.MouseCLat)); 
		});
	}
	//�ۥ����륺�����ʬ
	if(<?PHP echo $D_MAP_WHEEL_KBN; ?> == 0) {
		ZdcEmapMapObj.setWheelOff();
	} else {
		ZdcEmapMapObj.setWheelOn();
	}
	
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

	
	//����¾ -----------------------------------------------
	//�桼�����쥤�䡼
	ZdcEmapMapUserLyr.setLayerScale(<?PHP echo $D_VIEW_ICON_MAX; ?>,<?PHP echo $D_VIEW_ICON_MIN; ?>);
	ZdcEmapMapUserLyr.setLayerType('manual');
	ZdcEmapMapUserLyr.clearMarker();
	ZdcEmapMapUserLyrId = ZdcEmapMapObj.addUserLayer(ZdcEmapMapUserLyr); 
	//����������������
	ZdcEmapHistoryClear();
	//�����楢������
	ZdcEmapMapObj.addZdcWait(parseInt(parseInt(ZdcEmapMapSize.height) / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETY; ?>),
							 parseInt(parseInt(ZdcEmapMapSize.width)  / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETX; ?>),'<?PHP echo $D_MAP_WAIT_MSG; ?>');
}



//-------------------------------------------------------------
//�Ͽ�����
//-------------------------------------------------------------
//�Ͽ޾�˥�������ɽ��
var ZdcEmapMapCurMrkId = null;
function ZdcEmapMapCursorSet(lat, lon){
	//��������κ���
	var mrk = ZdcEmapMakeMrk(0,lat,lon,
							 ZdcEmapIconW['@SELB'],ZdcEmapIconH['@SELB'],0,0,
							 ZdcEmapIconOffsetX['@SELB'],ZdcEmapIconOffsetY['@SELB'],0,0,0,0,
							 ZdcEmapIconImg['@SELB'],'',
							 '','',0,null,null,null);
	if(ZdcEmapMapCurMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);
	ZdcEmapMapCurMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
}
//�Ͽ޾�Υ������볰��
function ZdcEmapMapCursorRemove(){
	if (ZdcEmapMapCurMrkId != null) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);
		ZdcEmapMapCurMrkId = null;
	}
	//�ܺ�ɽ����
	ZdcEmapMapFrontShopDetail();//�ܺ٥�����������̤ˤ�äƤ���
	// 2011/06/15 K.Masuda mod [
	//ZdcEmapShopMsgClose();//�᤭�Ф���ä�
	<?php //mod 2011/07/05 Y.Nakajima ?>
	if( <?php if(isset($D_HUKIDASHI_SEARCH)){echo "false";}else{echo "true";} ?> ){
		ZdcEmapShopMsgClose();//�᤭�Ф���ä�
	}
	// 2011/06/15 K.Masuda mod ]
}
//�Ͽް�ư
function ZdcEmapMapMove(lat, lon, lvl){
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//�ޥåװ�ư
	//	if(lvl) ZdcEmapMapObj.setMapLocation(center,lvl);
	//		else ZdcEmapMapObj.setMapLocation(center);
	ZdcEmapMapObj.setMapLocation(center);
	if(lvl) ZdcEmapMapObj.setMapScale(lvl);
}
function ZdcEmapMapScroll(lat, lon){
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//�ޥåװ�ư
	ZdcEmapMapObj.scrollToCenter(center);
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
	
	// add 2015/03/23 K.Iwayoshi [
	//���̥ܥ���ɽ������ ���ץ�����SMBC_DETAIL_BUTTON_SHOW_FLAG�ե饰�ˣ��򥻥åȤ��ʤ���ư��ʤ� 
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		
		//��ɽ������
		// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������[ 
		//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		// mod 2015/4/22]
		for(var i = 0 ; i < eles.length ; i++){
			eles[i].style.display = "none";
			eles[i].removeAttribute("value");
		}
		
		//���̥ܥ���ɽ���ե饰
		ShowListButtonFlag = false;
	}
	// add 2015/03/23 K.Iwayoshi]
}

//��������Υ���å�ư�����󥻥뤵�줿���ˡ�����򸵤��᤹		add 2010/07/08 Y.Matsukawa
function ZdcEmapHistoryClickCancel() {
	ZdcEmapHistoryCnt = ZdcEmapHistoryCntSv;
}
//�ҤȤ����
function ZdcEmapHistoryBack() {
	ZdcEmapHistoryClick(ZdcEmapHistoryCnt - 1)
	
	// add 2015/03/23 K.Iwayoshi [
	//���̥ܥ���ɽ������ ���ץ�����SMBC_DETAIL_BUTTON_SHOW_FLAG�ե饰�ˣ��򥻥åȤ��ʤ���ư��ʤ�
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������[
		//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		// mod 2015/04/22]
		for(var i = 0 ; i < eles.length ; i++){
			eles[i].style.display = "none";
			eles[i].removeAttribute("value");
		}
		
		//���̥ܥ���ɽ���ե饰
		ShowListButtonFlag = false;
		
	}
	// add 2015/03/23 K.Iwayoshi ]
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
	// mod 2011/05/26 K.Masuda [
	//ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP echo $D_HISTORY_TOP_NAME; ?>","<?PHP echo $D_HISTORY_TOP_LINK; ?>");
	<?php //mod 2011/07/05 Y.Nakajima ?>
	if( <?php if(isset($D_QUERY_STRING)){echo "true";}else{echo "false";} ?> ){
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
			html_last = '<a href="javascript:ZdcEmapHistoryClick('+i+');">';
			<?php //mod 2011/07/05 Y.Nakajima ?>
			html_last += '<?php if (isset($D_HISTORY_LAST_WORD)) echo $D_HISTORY_LAST_WORD; ?>';
			html_last += '</a>';	// add 2009/03/04 Y.Matsukawa
<?php	// add 2010/03/23 Y.Matsukawa [
		for ($j = 1; $j <= 5; $j++) {
?>
<?php		// mod 2011/7/5 Y.Nakajima ?>
			html_last_arr[<?php echo $j; ?>] = '<a href="javascript:ZdcEmapHistoryClick('+i+');"><?php if (isset($D_HISTORY_LAST_WORD_ARR[$j])) echo $D_HISTORY_LAST_WORD_ARR[$j]; ?></a>';
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
	//1,2,3
	//4,5,6,7
	//8,9,10,11,12,13
	//14(image),15
	//16,17,18
	//19,20,21
	//22

	//mod 2011/07/05 Y.nakajima [
	//lvl�������Ǥʤ��Ȥ��ν������ɲ�
	if (isNaN(lvl) || !lvl || lvl < 1 || lvl >18) lvl = 0;
	//mod 2011/07/05 Y.nakajima ]
	
	var p,mrk,item;
	var icon = new ZdcIcon();
	
	//��������κ���
	icon.size      = new ZdcSize(sizew, sizeh);
	icon.offset    = new ZdcPixel(offsetx, offsety);
	//icon.image    = image;	2008/11/26 Y.Matsukawa del
	// 2008/11/26 Y.Matsukawa add [
	// icon.image����������.gif�פǤʤ��ȡ�����Ū��GIF�ʳ��Ȥ��ƽ�������Ƥ��ޤ��Τǡ�������̵��������.gif�פˤ��Ƥ��ޤ���
	// GIF�ʳ��ǽ�������Ƥ��ޤ��ȡ�IE�ǰ�������Ʃ��GIF��Ʃ�ᤷ�ޤ���
	// �����ॹ������ͤ��ղä��Ƥ���Τϡ�����å��������Τ���Ǥ������줬�ʤ��ȡ�������������򺹤��ؤ����ݤ�ɽ��������뤳�Ȥ�����ޤ�����IE�Τߡ�
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
//���������
function ZdcEmapRouteSearch(name1,mx1,my1,name2,mx2,my2) {
	<?php if (!isset($D_ROUTE_FIX_MODE) || !$D_ROUTE_FIX_MODE) {	// add 2011/11/25 Y.Matsukawa ?>
	if(ZdcEmapButtonNG()) return;
	<?php } ?>
	if(ZdcEmapRouteType == 0) return;
	ZdcEmapPoiRouteClear();
	
	//�ѥ�᡼����������
	ZdcEmapRouteName1 = name1;
	ZdcEmapRouteName2 = name2;
	ZdcEmapRoutePoint1 = new ZdcPoint(mx1, my1, <?PHP echo $D_PFLG; ?>);
	ZdcEmapRoutePoint2 = new ZdcPoint(mx2, my2, <?PHP echo $D_PFLG; ?>);
	
	if(ZdcEmapRouteType == 1 || ZdcEmapRouteType == 3)
		ZdcEmapRouteSearchWalk(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);
	if(ZdcEmapRouteType == 2)
		ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);

	//���̤ΰ�ư
	ZdcEmapMapMoveBox(my1,mx1,my2,mx2);
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
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	ZdcEmapShopMsgClose();
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		//���顼����
		if(ZdcEmapRouteType == 1) {
			//���Ԥ��ä���缫ư�֤ǺƸ�������
			ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);
		} else {
			<?php // add 2011/11/25 Y.Matsukawa [ ?>
			<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
			ZdcEmapRouteFlag();
			<?php } ?>
			<?php // add 2011/11/25 Y.Matsukawa ] ?>
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
	<?php //�롼�ȴ�λ��ư��		add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapRouteSearchEndAction(result, "Walk");
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
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	ZdcEmapShopMsgClose();
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		<?php // add 2011/11/25 Y.Matsukawa [ ?>
		<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
		ZdcEmapRouteFlag();
		<?php } ?>
		<?php // add 2011/11/25 Y.Matsukawa ] ?>
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
	<?php //�롼�ȴ�λ��ư��		add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapRouteSearchEndAction(result, "Car");
}
<?php //�롼�ȴ�λ��ư��		add 2011/11/25 Y.Matsukawa ?>
function ZdcEmapRouteSearchEndAction(result, routeType) {
	var ele,wgs,dms,time=0,hh=0,mi=0;
	<?php //�롼�Ⱦ����ɽ�� ?>
	var time=0;
	if (routeType == "Walk") {
		mi = parseInt(result.distance / 4000 * 60);//ʬ
		hh = parseInt(mi/60);//����
		mi = (mi - hh*60);
	} else {
		var cnt = result.getLinkCount(0);
		var link = new Array();
		for(i=0; i < cnt; i++) {
			var rlink = result.getLink(i, 0);
			if(rlink.roadType == 0 || rlink.roadType == 1) {
				// ��®
				time += rlink.distance / (80*1000);
			} else {
				// ����
				time += rlink.distance / (40*1000);
			}
		}
		if (time > 0) {
			mi = parseInt(time*10000/166);//ʬ
			hh = parseInt(mi/60);//����
			mi = (mi - hh*60);
		}
	}
	ele = document.getElementById("ZdcEmapRouteTimeH");
	if (ele) ele.innerHTML = hh;
	if (hh < 10) hh = "0"+hh;
	ele = document.getElementById("ZdcEmapRouteTimeHH");
	if (ele) ele.innerHTML = hh;
	ele = document.getElementById("ZdcEmapRouteTimeN");
	if (ele) ele.innerHTML = mi;
	if (mi < 10) mi = "0"+mi;
	ele = document.getElementById("ZdcEmapRouteTimeNN");
	if (ele) ele.innerHTML = mi;
}
//�롼�Ⱥ��
function ZdcEmapPoiRouteClear() {
	if(!ZdcEmapRouteSearchObj) return;
	if(ZdcEmapRouteOptionsObj.departurePoint.point) {
		try{
			ZdcEmapMapObj.ClearPRouteLayer();//1.5�ޤ�
		} catch(e) {
			ZdcEmapRouteSearchObj.clearRoute();//1.6�ʹ�
		}
	} else {
		ZdcEmapMapObj.removeRouteSearch();
	}
	delete ZdcEmapRouteOptionsObj;
	delete ZdcEmapRouteSearchObj;
	//�������ȡ�������Υ쥤�䡼����
	if(ZdcEmapRouteFlagLayer) ZdcEmapRouteFlagLayer.clearMarker();
	ZdcEmapMapObj.removeUserLayer(ZdcEmapRouteFlagLayer);
	delete ZdcEmapRouteFlagIcon1;
	delete ZdcEmapRouteFlagIcon2;
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

// add 2011/11/25 Y.Matsukawa
//-------------------------------------------------------------
//�롼��õ���⡼��
//-------------------------------------------------------------
function ZdcEmapFixRouteSearch(shopItem) {
	ZdcEmapRouteShopItem = shopItem;
	<?php //��Ū��Ź�ޤξ����ɽ�� ?>
	if (ZdcEmapRouteShopItem) {
		for(prop in ZdcEmapRouteShopItem){
			ele = document.getElementById("ZdcEmapRouteShop_"+prop);
			if (ele) ele.innerHTML = eval("ZdcEmapRouteShopItem."+prop);
		}
	}
	ZdcEmapRouteSearch('<?PHP echo $D_USER_DEFNAME; ?>', ZdcEmapRouteShopItem.lon, ZdcEmapRouteShopItem.lat,
						'�Ͽ��濴', ZdcEmapRouteStartLon, ZdcEmapRouteStartLat);
}
function ZdcEmapFixRouteSelectShop(id) {
	var shopItem = null;
	if (ZdcEmapRouteShopItems) {
		for(i=0; i<ZdcEmapRouteShopItems.length; i++) {
			if (ZdcEmapRouteShopItems[i].id == id) {
				shopItem = ZdcEmapRouteShopItems[i];
				break;
			}
		}
		if (shopItem) ZdcEmapFixRouteSearch(shopItem);
	}
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
	if( <?php if(isset($D_HUKIDASHI_SEARCH)){echo "false";}else{echo "true";} ?> ){
		if(ZdcEmapMapObj.getUserMsgOpenStatus()) return;//�ե�����ɽ����ϸ������ʤ�
	}
	// 2011/06/15 K.Masuda mod ]
<?php	// add 2016/11/15 K.Tani [
		// �Ͽ������˺Ƹ������ʤ��⡼��
		if ($D_SHOP_NO_SEARCH_USER_ACT) { ?>
	return;
<?php	}
		// add 2016/11/15 K.Tani ] ?>
	
	
	eval(ZdcEmapSearchEventFunc);
}
//�������٥���ɲ�
function ZdcEmapSearchEventAdd(func) {
	ZdcEmapSearchEventDel();
	ZdcEmapSearchEventFunc = func;
	ZdcEmapSearchEventDragmapend    = ZdcEvent.addListener(ZdcEmapMapObj, "dragmapend"   , ZdcEmapSearchEventAction);
	ZdcEmapSearchEventScrollmapend  = ZdcEvent.addListener(ZdcEmapMapObj, "scrollmapend" , ZdcEmapSearchEventAction);
	ZdcEmapSearchEventChangezoomend = ZdcEvent.addListener(ZdcEmapMapObj, "changezoomend", ZdcEmapSearchEventAction);
}
//�������٥�Ⱥ��
function ZdcEmapSearchEventDel() {
	ZdcEmapSearchEventStop();
	if(ZdcEmapSearchEventDragmapend)    ZdcEvent.removeListener(ZdcEmapSearchEventDragmapend);
	if(ZdcEmapSearchEventScrollmapend)  ZdcEvent.removeListener(ZdcEmapSearchEventScrollmapend);
	if(ZdcEmapSearchEventChangezoomend) ZdcEvent.removeListener(ZdcEmapSearchEventChangezoomend);
	
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
	var s = ZdcEmapMapObj.getMapScale();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//���֥������Ȥκ���
	ZdcEmapTipsMarker = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapPoiMrkId[id]);
	if(!ZdcEmapMapObj || !ZdcEmapTipsMarker) return;
	if(!ZdcEmapTipsShape) ZdcEmapTipsShape = new ZdcShape.Text();
	if(!ZdcEmapTipsShapeLayer) ZdcEmapTipsShapeLayer = new ZdcShape.Layer();
	ZdcEmapMapObj.addShapeLayer(ZdcEmapTipsShapeLayer);
	ZdcEmapTipsShapeLayer.setZIndex(4010);
	//�ƥ����Ȥ�����
	ZdcEmapTipsShape.textString = ZdcEmapTipsMarker.data1;
	ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	ZdcEmapTipsShape.font = "<?PHP echo $D_TIPS_FONT; ?>";
	ZdcEmapTipsShape.borderWidth = <?PHP echo $D_TIPS_BORDERWIDTH; ?>;
	ZdcEmapTipsShape.bgColor = "<?PHP echo $D_TIPS_BGCOLOR; ?>";
	ZdcEmapTipsShape.shadowFlg = <?PHP echo $D_TIPS_SHADOWFLG; ?>;
	ZdcEmapTipsShape.shadowX = <?PHP echo $D_TIPS_SHADOWX; ?>;
	ZdcEmapTipsShape.shadowY = <?PHP echo $D_TIPS_SHADOWY; ?>;
	ZdcEmapTipsShape.opacity = <?PHP echo $D_TIPS_OPACITY; ?>;
	//ɽ�����֤�Ĵ��
	var box = ZdcEmapMapObj.getMapBoundBox();
	var point = new ZdcPoint(ZdcEmapTipsMarker.Point.mx, ZdcEmapTipsMarker.Point.my, <?PHP echo $D_PFLG; ?>);
	var x,y,v,h;
	if(Math.abs(box.minx - point.mx) < Math.abs(box.maxx - point.mx)){ 
		h = "left"; 
		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	}else{
		h = "right";
		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X*-1; ?>;
	}
	if(Math.abs(box.miny - point.my) < Math.abs(box.maxy - point.my)){
		v = "bottom";
		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y*-1; ?>;
	}else{
		v = "top";
		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	}
	ZdcEmapTipsShape.anchor = h + "-" + v;
	ZdcEmapTipsShape.setPoint(point);
	ZdcEmapTipsShapeLayer.addShape(ZdcEmapTipsShape);
	//�����濴���Ͽ��ϰϳ��ξ���ư����
	if(ZdcEmapTipsMarker.Point.mx < box.minx || ZdcEmapTipsMarker.Point.my < box.miny || ZdcEmapTipsMarker.Point.mx > box.maxx || ZdcEmapTipsMarker.Point.my > box.maxy)
		ZdcEmapMapObj.setMapLocation(ZdcEmapTipsMarker.Point);
	//����
	if(!ZdcEmapTipsTopMarkerLayer) ZdcEmapTipsTopMarkerLayer = new ZdcUserLayer();//�Ǿ�̥ޡ������쥤�䡼
	if(!ZdcEmapTipsTopMarker) ZdcEmapTipsTopMarker = new ZdcMarker(new ZdcPoint(ZdcEmapTipsMarker.getPoint().lon ,ZdcEmapTipsMarker.getPoint().lat), ZdcEmapTipsMarker.getIcon());
	ZdcEmapTipsTopMarkerLayer.addMarker(ZdcEmapTipsTopMarker);
	ZdcEmapMapObj.addUserLayer(ZdcEmapTipsTopMarkerLayer);
	ZdcEmapTipsTopMarkerLayer.doc.style.zIndex = 4011;
	ZdcEmapTipsTopMarker.mouseclickmarker = ZdcEmapTipsMarker.mouseclickmarker;
	//���٥�Ȥ�����
	if(ZdcEmapTipsTopMarker.mouseclickmarker) ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseclickmarker", ZdcEmapTipsTopMarker.mouseclickmarker);
	ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseoutmarker", ZdcEmapTipsHideInfo);
	ZdcEmapTipsTimerID = setTimeout(ZdcEmapTipsHideInfoInterval, ZdcEmapTipsInterval);
}
//�쥤�䡼���Ĥ���
function ZdcEmapTipsClose() {
	//�������ץ쥤�䡼���Ĥ���
	if(ZdcEmapTipsShapeLayer)
	{
		ZdcEmapTipsShapeLayer.clearShape();
		ZdcEmapMapObj.removeShapeLayer(ZdcEmapTipsShapeLayer);
	}
	ZdcEmapTipsShapeLayer = null;
	ZdcEmapTipsShape = null;
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
	if(ZdcEmapReading == 1) ZdcEmapMapObj.visibleZdcWait();
}
function ZdcEmapReadOff() {
	if(ZdcEmapReading <= 0) return;
	ZdcEmapReading --;
	if(ZdcEmapReading == 0) ZdcEmapMapObj.hiddenZdcWait();
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

// ������������̤˰�ư��APIv1.10�Ǽ���ͽ��ε�ǽ����Ԥ��Ƽ�����		add 2009/10/14 Y.Matsukawa
//v110 add -- set top zindex for marker
ZdcMarker.prototype.setTopZIndex=function(idx){
//	if (this.parentLayer.addmapstatus){
//		for (var i=0; i<this.parentLayer.markers.length; i++){
//			if (this.parentLayer.markers[i]!=null){
//				this.parentLayer.markers[i].doc.style.zIndex = 3;
//			}
//		}
//	}
	if (idx) {
		this.doc.style.zIndex = idx;
	} else {
		this.doc.style.zIndex = 4;
	}
}
//v110 add -- set defalut zindex for marker
ZdcMarker.prototype.setDefaultZIndex=function(){
	//this.doc.style.zIndex = 0;
	this.doc.style.zIndex = 3;
}

<?php // �ޥå��󥰷�̽���ʸ�����JS�ѿ��˥��å�		add 2011/11/25 Y.Matsukawa ?>
var ZdcEmapAddrMatchString = null;
function ZdcEmapSetAddrMatchString(addr) {
	ZdcEmapAddrMatchString = addr;
}

<?php // �ǽ���濴���������		add 2012/05/28 K.Masuda ?>
function ZdcEmaprestoreCenter(){
	ZdcEmapMapObj.restoreMapLocation();
}

// add 2015/04/22 H.Yasunaga getElementByClassName��IE���̸ߴ��� [
function CompatiblegetElementsByClassName(targetClass){
    var foundElements = new Array();
    if (document.all){
        var allElements = document.all;
    }
    else {
       var allElements = document.getElementsByTagName("*");
    }
    for (i=0,j=0;i<allElements.length;i++) {
        if (allElements[i].className == targetClass) {
            foundElements[j] = allElements[i];
            j++;
        }
    }  
    return foundElements;
}
// add 2015/04/22 H.Yasunaga]