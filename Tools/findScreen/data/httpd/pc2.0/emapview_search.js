<?PHP
// ------------------------------------------------------------
// �Ͽ�����javasctipt ��˵����ʳ��θ����˴ؤ�����
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2007/11/16 Y.Matsukawa	���ɽ�������Ͽ�API��ChangeLocation���٥�Ȥ�����ȯ�����뢪����˸��餹
// 2008/04/21 Y.Matsukawa	����TOP������ɥ��˹ʤ���߾������
// 2008/05/07 Y.Matsukawa	��IE6�Զ���б����Ͽ޲��̤Υꥹ�ȥܥå���������������ɥ��ξ�˽ФƤ���
// 2008/08/22 Y.Matsukawa	�ѻ��б�
// 2008/10/22 Y.Matsukawa	���Ѥ��ʤ�JS�ϥ��ɤ��ʤ�
// 2009/03/10 Y.Matsukawa	������̲��̤ؼ�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/03/26 Y.Matsukawa	�ʹ��߲��̤ؼ�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/09/03 Y.Matsukawa	����TOP������ٷ�����³����condȿ��
// 2009/11/07 Y.Matsukawa	�������ܳ�ĥ��50��200��
// 2009/12/22 Y.Matsukawa	����TOP��cond���Ϥ�
// 2010/01/27 Y.Matsukawa	�ʤ���ߥƥ�ץ졼�Ȥ���ƻ�ܸ������ɤ��Ϥ�
// 2010/03/09 Y.Matsukawa	����FW������������ꥹ�ȡ��Ͽޤʤ��ˤ�����
// 2010/05/11 Y.Matsukawa	���������˥����å��ܥå���
// 2010/05/19 Y.Matsukawa	ϩ���ޥƥ�ץ졼�Ȥ�Ǥ�եѥ�᡼�����Ϥ�
// 2010/06/16 Y.Matsukawa	��ȯ�Ϥ���ꤷ�ƥ롼��õ��
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2010/11/03 K.Masuda		���ꥢ����ʣ���б�
// 2011/02/09 Y.Matsukawa	��������������ɥᥤ�󤫤�����IP���ѹ�
// 2011/02/16 Y.Matsukawa	������̽�����������򤷤�����򡢽�ȯ�ϻ���롼�Ȥ����Ͻ���ͤˤ���
// 2011/04/14 H.Osamoto		My���ꥢ�б�
// 2011/06/02 H.Osamoto		�ե꡼���ʣ�縡���б�
// 2011/06/16 Y.Matsukawa	�ܺٹ�������JS�¹�
// 2011/07/07 H.Osamoto		�ޥĥ�����API2.0�б���
// 2011/10/03 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/10/06 H.Osamoto               �ϰ�ޤ���Ƹ��������ݤ˵����ꥹ�Ȥ���������ʤ��Զ�����
// ------------------------------------------------------------
include("./inc/define.inc");  // ��������
include("./unicode.js");  // �����¸ʸ�������å��ѤΥ�����ɽ
?>
//-------------------------------------------------------------
//���ָ����ط�
//-------------------------------------------------------------
var ZdcEmapRailMainObj;
var ZdcEmapRailSubObj;
var ZdcEmapAreaObj;
var ZdcEmapNearShop = new ZdcNearShop();
// add 2011/06/16 Y.Matsukawa [
var ZdcEmapKyotenId = null;
if (typeof ZdcKyotenId == 'function') {
	ZdcEmapKyotenId = new ZdcKyotenId();
}
// add 2011/06/16 Y.Matsukawa ]
// del 2011/07/07 H.Osamoto [
//	<?php //if($D_REQ_JSAPI["searchrailway"]){ ?>	// 2008/10/22 Y.Matsukawa add
//	var ZdcEmapRailway = new ZdcSearchRailwayMap();
//	<?php //} ?>
//	<?php //if($D_REQ_JSAPI["searchmap"]){ ?>	// 2008/10/22 Y.Matsukawa add
//	var ZdcEmapArea    = new ZdcSearchMap();
//	<?php //} ?>
// del 2011/07/07 H.Osamoto ]
var ZdcEmapArea;	// add 2011/07/07 H.Osamoto
//�����ܥ���β���
function ZdcEmapSearchClick() {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchOpen("","","")
}
//��������³���󥿡��ե�����
function ZdcEmapSearchOpenFirst(type,prm,name) {
	//	var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>&";
	//	for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "cond"+i+"="+ZdcEmapSaveCond[i]+"&";//�ʹ����
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
	//for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//�ʹ����		mod 2009/11/07 Y.Matsukawa
	for(i = 1;i <= 200;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//�ʹ����
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
	<?php // add 2010/01/27 Y.Matsukawa [ ?>
	<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
	<?php // add 2010/01/27 Y.Matsukawa ] ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapCondObj.innerHTML = html;
		//�ʹ��߾���Ȥ�Ω��
		var cond = ZdcEmapGetCond();
		prm += "&cond=" + cond;
		//�����볫��
		ZdcEmapSearchChange(type,prm,name);
	});
	ZdcEmapCondObj.mode = "cond";
	ZdcEmapCondObj.style.visibility = "visible";
}
//����������ɥ��������³				add 2008/04/21 Y.Matsukawa
function ZdcEmapSearchOpenFromSrchWin(type,prm,name) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
	url = url + "&" + prm;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
	<?php // add 2010/01/27 Y.Matsukawa [ ?>
	<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
	<?php // add 2010/01/27 Y.Matsukawa ] ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapCondObj.innerHTML = html;
		//�ʹ��߾���Ȥ�Ω��
		var cond = ZdcEmapGetCond();
		prm += "&cond=" + cond;
		//�����볫��
		ZdcEmapSearchChange(type,prm,name);
	});
	ZdcEmapCondObj.mode = "cond";
	ZdcEmapCondObj.style.visibility = "visible";
}
//������򳫤�
function ZdcEmapSearchOpen(type,prm,name) {
	//���������
	ZdcEmapSearchEventStop();
	ZdcEmapSearchClear();
	//�������ɤ߹���
	ZdcEmapSearchChange(type,prm,name);
}
//��񤭴���
function ZdcEmapSearchChange(type,prm,name) {
	//�ѥ�᡼�����Ȥ�Ω��
	//prm = "&type="+type+"&"+prm;		mod 2009/03/10 Y.Matsukawa
	prm = "&type="+type+"&"+prm+"&<?php echo $P_FREEPARAMS; ?>";
	//�������򹹿�
	switch(type) {
		case "AddrW"://����ե꡼���
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["AddrW"]; ?>("+name+")","ZdcEmapSearchOpen('AddrW','"+prm+"','"+name+"');");
			break;
		case "StW"://�إե꡼���
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["StW"]; ?>("+name+")","ZdcEmapSearchOpen('StW','"+prm+"','"+name+"');");
			break;
		case "PoiW"://���ߥե꡼���
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["PoiW"]; ?>("+name+")","ZdcEmapSearchOpen('PoiW','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('PoiW','"+prm+"','"+name+"');");
			}
			break;
		case "ZipW"://͹���ֹ�ե꡼���
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["ZipW"]; ?>("+name+")","ZdcEmapSearchOpen('ZipW','"+prm+"','"+name+"');");
			break;
		case "AddrL"://����ꥹ��
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["AddrL"]; ?>("+name+")","ZdcEmapSearchOpen('AddrL','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('AddrL','"+prm+"','"+name+"');");
			}
			break;
		case "StL"://�إꥹ��
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["StL"]; ?>("+name+")","ZdcEmapSearchOpen('StL','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('StL','"+prm+"','"+name+"');");
			}
			break;
		case "PoiL"://���ߥꥹ��
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["PoiL"]; ?>("+name+")","ZdcEmapSearchOpen('PoiL','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('PoiL','"+prm+"','"+name+"');");
			}
			break;
		case "ShopW"://�����ե꡼���
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["ShopW"]; ?>("+name+")","ZdcEmapSearchOpen('ShopW','"+prm+"','"+name+"');");
			break;
		case "ShopA"://�������ꥢ
			if(name.charAt(0) != ":") {
				// add 2010/11/03 K.Masuda [
				var ptnw1,ptnw2,history_name,hn1,hn2,hn3,hn4,hn5;
				if(prm){
					ptnw1 = prm.match(/areaptn=[0-9]*/);
					if(ptnw1){
						ptnw2 = ptnw1[0].match(/[0-9]+/);
					} else {
						ptnw2 = "99";	
					}
				} else {
					ptnw2 = "99";	
				}
				if( ptnw2 == 1) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA"]; ?>";
				} else if( ptnw2 == 2) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_2"]; ?>";
				} else if( ptnw2 == 3) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_3"]; ?>";
				} else if( ptnw2 == 4) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_4"]; ?>";
				} else if( ptnw2 == 5) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_5"]; ?>";
				} else {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA"]; ?>";
				}
				// add 2010/11/03 K.Masuda ]
				//ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["ShopA"]; ?>","ZdcEmapSearchOpen('ShopA','"+prm+"','"+name+"');");	mod 2010/11/03 K.Masuda
				ZdcEmapHistoryAdd(history_name,"ZdcEmapSearchOpen('ShopA','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('ShopA','"+prm+"','"+name+"');");
			}
			break;
		// add 2010/03/09 Y.Matsukawa [
		case "Nshop"://�Ǵ��������Ͽޤʤ���
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Nshop"]; ?>","ZdcEmapSearchOpen('Nshop','"+prm+"','"+name+"');");
			break;
		// add 2010/03/09 Y.Matsukawa ]
		// add 2010/06/02 H.osamoto [
		case "Comb"://�ե꡼���ʣ�縡��
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Comb"]; ?>("+name+")","ZdcEmapSearchOpen('Comb','"+prm+"','"+name+"');");
			break;
		// add 2010/06/02 H.osamoto ]
		default:
			ZdcEmapSetFRouteInit('');		// add 2011/02/16 Y.Matsukawa
			ZdcEmapHistoryClear();
			break;
	}
<?php
	// add 2009/12/22 Y.Matsukawa
	//-------------------
	// cond����ƥ�ץ졼�Ȥ��Ϥ�
	//-------------------
	$cond_prm = "";
	for($i = 1; $i <= 200; $i++) {
		$cond = "cond".$i;
		// mod 2011/10/03 Y.Nakajima
		if(isset($_VARS[$cond]) && $_VARS[$cond]) {
			$cond_prm = "&cond".$i."=".$_VARS[$cond];
		}
	}
?>
	//���̽񤭴���
<?php /* ?>
	//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm);		mod 2009/12/22 Y.Matsukawa
	//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>");	mod 2010/07/20 Y.Matsukawa
	//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>"<?php if($https_req){ ?>+"&https_req=1"<?php } ?>);	mod 2011/02/09 Y.Matsukawa
	//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>"<?php if(isset($https_req) && $https_req){ ?>+"&https_req=1"<?php } // mod 2011/10/03 Y.Nakajima  ?>);
<?php */ ?>
	url = "<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>"<?php if(isset($https_req) && $https_req){ ?>+"&https_req=1"<?php } // mod 2011/10/03 Y.Nakajima  ?>;
	ZdcEmapSearchRequest(url);
}
function ZdcEmapSearchRequest(url) {
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		<?PHP if (isset($D_SEARCHLIST_SCOND) && $D_SEARCHLIST_SCOND) { ?>ZdcEmapCond2SearchTopCond();<?PHP }	// add 2010/05/11 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	});
}
//���Ĥ���
function ZdcEmapSearchClose() {
	if(ZdcEmapSearchWindowObj.style.visibility == "hidden") return;
	//���̤�DIV���Ĥ���
	ZdcEmapSearchRailwayRemove();
	ZdcEmapSearchAreaRemove();
	//
	ZdcEmapSearchWindowObj.innerHTML = "";
	ZdcEmapSearchWindowObj.style.visibility = "hidden";
	if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "hidden";// add 2008/05/07 Y.Matsukawa
	ZdcEmapSearchEventStart();
}
//��񤭴�������
function ZdcEmapSearchClear() {
	if(ZdcEmapSearchWindowObj.style.visibility == "hidden") return;
	//���̤�DIV���Ĥ���
	ZdcEmapSearchRailwayRemove();
	ZdcEmapSearchAreaRemove();
}
//����󥻥�
function ZdcEmapSearchCancel() {
	//���̤�DIV���Ĥ���
	ZdcEmapSearchRailwayRemove();
	ZdcEmapSearchAreaRemove();
	//���̤�����
	if(ZdcEmapHistorySaveChk()) {
		ZdcEmapHistoryLoad();
		ZdcEmapSearchClose();
	} else {
		ZdcEmapHistoryClick(0);
	}
}
//��������
//function ZdcEmapSearchSet(lat,lon) {		2007/11/16 mod Y.Matsukawa
function ZdcEmapSearchSet(lat,lon,notmove) {
	ZdcEmapShopDetailClose();
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["List"]; ?>","ZdcEmapSearchSet('"+lat+"','"+lon+"');");
	ZdcEmapHistorySave();
	//�ޥåװ�ư
	ZdcEmapSearchEventStop();
	//var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);		mod 2011/07/07 H.osamoto
	var center = new ZDC.LatLon(Number(lat), Number(lon));
	var latlon = ZdcEmapMapObj.getLatLon();
	//ZdcEmapMapObj.setMapLocation(center);		2007/11/16 mod Y.Matsukawa
	// mod 2011/07/07 H.Osamoto [
	//	if (!notmove) ZdcEmapMapObj.setMapLocation(center);
	//	if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
	if (!notmove) ZdcEmapMapObj.moveLatLon(center);
	if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
	// mod 2011/07/07 H.Osamoto ]
	//��������
	ZdcEmapSearchFirst = 1;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	mappoint = center;	// add 2011/10/06 H.osamoto
	ZdcEmapSearchShopStart();
	//ZdcEmapMapObj.saveMapLocation();		mod 2011/07/07 H.osamoto
	ZdcEmapMapObj.setHome(center);
}
//  add 2011/04/14 H.Osamoto
//��������(My���ꥢ��)
function ZdcEmapSearchSetMyarea(lat,lon,notmove) {
	ZdcEmapShopDetailClose();
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyArea"]; ?>","ZdcEmapSearchSet('"+lat+"','"+lon+"');");
	ZdcEmapHistorySave();
	//�ޥåװ�ư
	ZdcEmapSearchEventStop();
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//ZdcEmapMapObj.setMapLocation(center);		2007/11/16 mod Y.Matsukawa
	if (!notmove) ZdcEmapMapObj.setMapLocation(center);
	if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
	//��������
	ZdcEmapSearchFirst = 1;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	ZdcEmapSearchShopStart();
	ZdcEmapMapObj.saveMapLocation();
}

// add 2009/09/03 Y.Matsukawa
function ZdcEmapSearchSetFromWin(lat,lon,notmove,prm) {
	//����������ɥ�����ξ�硢�ʤ���߾���ȿ��
	if(prm != undefined) {
<?php /* ?>
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
<?php */ ?>
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		if (prm) url = url + "&" + prm;
		url += "&<?php echo $P_FREEPARAMS; ?>";
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php if(isset($area) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapCondObj.mode = "cond";
			ZdcEmapCondObj.style.visibility = "visible";
			//
			ZdcEmapShopDetailClose();
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["List"]; ?>","ZdcEmapSearchSet('"+lat+"','"+lon+"');");
			ZdcEmapHistorySave();
			//�ޥåװ�ư
			ZdcEmapSearchEventStop();
			var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
			if (!notmove) ZdcEmapMapObj.setMapLocation(center);
			if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
			//��������
			ZdcEmapSearchFirst = 1;
			ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
			ZdcEmapSearchShopStart();
			ZdcEmapMapObj.saveMapLocation();
		});
	}
}
//ϩ����ɽ��
//function ZdcEmapSearchRailwayDisp(mapNo,name,x,y){	mod 2008/04/21 Y.Matsukawa
function ZdcEmapSearchRailwayDisp(mapNo,name,x,y,prm){
	var tmp = "";
	if(name) tmp = "("+name+")";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Rail"]; ?>"+tmp,
	                  "ZdcEmapSearchRailwayDisp('"+mapNo+"','"+name+"',"+x+","+y+");");
	//ϩ���ޤ��Ѥ��ʤ����¹Ԥ��ʤ� ������Ϣ���к�
	if(ZdcEmapRailMainObj) if(ZdcEmapRailMainObj.mapNo == mapNo) return;
	
	//����������ɥ�����ξ�硢�ʤ���߾���ȿ��		add 2008/04/21 Y.Matsukawa
	if(prm != undefined) {
<?php /* ?>
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
<?php */ ?>
		if (prm) url = url + "&" + prm;
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } // mod 2011/10/03 Y.Nakajima ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapCondObj.mode = "cond";
			ZdcEmapCondObj.style.visibility = "visible";
		});
	}

	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	//var url = "<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Rail&area="+mapNo;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Rail&area="+mapNo;
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		
		ZdcEmapRailMainObj = document.getElementById('ZdcEmapSearchRailwayMain');
		ZdcEmapRailSubObj = document.getElementById('ZdcEmapSearchRailwaySub');
		//
		var opts = new ZdcSearchRailwayMapOptions();
		//ϩ���ޤΥѥ�᡼��������
		if (mapNo != undefined){
			opts.mapNo = parseInt(mapNo);
		}
		opts.x = x;
		opts.y = y;
		opts.callback = function(result) {
			//������Хå��ؿ�
			if( result.status == 0 ){
				//�Ͽް�ư
				var lat;
				var lon;
				if (result.items[0].point != null){
					lat = result.items[0].point.my;
					lon = result.items[0].point.mx;
				} else {
					lat = result.items[0].lat;
					lon = result.items[0].lon;
				}
				ZdcEmapSearchSet(lat,lon);
			}
		}
		//ϩ���ޥᥤ���ɽ������
		if(ZdcEmapRailMainObj) {
			ZdcEmapRailway.addMainMap(ZdcEmapRailMainObj,opts);
			ZdcEmapRailMainObj.mapNo = mapNo;
			//ϩ���ޥ��֤�ɽ������
			if(ZdcEmapRailSubObj) {
				ZdcEmapRailway.addSubMap(ZdcEmapRailSubObj);
			}
		}
	});
}
//ϩ�����Ĥ���
function ZdcEmapSearchRailwayRemove(){
	if(!ZdcEmapRailMainObj) return;
	//ϩ���ޤ򱣤�
	ZdcEmapRailway.removeMainMap();
	delete ZdcEmapRailMainObj;
	ZdcEmapRailMainObj = null;
	ZdcEmapRailway.removeSubMap();
	if(ZdcEmapRailSubObj) {
		delete ZdcEmapRailSubObj;
		ZdcEmapRailSubObj = null;
	}
}
//�ϰ��ɽ��
//function ZdcEmapSearchAreaDisp(todCode,name){	mod 2008/04/21 Y.Matsukawa
function ZdcEmapSearchAreaDisp(todCode,name,prm){
	var tmp = "";
	if(name) tmp = "("+name+")";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Area"]; ?>"+tmp,
	                  "ZdcEmapSearchAreaDisp('"+todCode+"','"+name+"');");
	//��ƻ�ܸ����Ѥ��ʤ����¹Ԥ��ʤ� ������Ϣ���к�
	if(ZdcEmapAreaObj) if(ZdcEmapAreaObj.todCode == todCode) return;

	//����������ɥ�����ξ�硢�ʤ���߾���ȿ��		add 2008/04/21 Y.Matsukawa
	if(prm != undefined) {
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		if (prm) url = url + "&" + prm;
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php }  // mod 2011/10/03 Y.Nakajima ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php }  // mod 2011/10/03 Y.Nakajima ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapCondObj.mode = "cond";
			ZdcEmapCondObj.style.visibility = "visible";
		});
	}
	
	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	//var url = "<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Area&area="+todCode;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Area&area="+todCode;
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		
<?php /* ��ɽ������ ?>
		// mod 2011/07/07 H.osamoto [
		//	var opts = new ZdcSearchMapOptions();
		//
		//	//�ϰ�ޤΥѥ�᡼��������
		//	if (todCode != undefined){
		//		opts.todCode = todCode;
		//	}
		//	opts.callback = function(result) {
		//		//������Хå��ؿ�
		//		if( result.status == 0 ){
		//			//�Ͽް�ư
		//			var lat;
		//			var lon;
		//			if (result.items[0].point != null){
		//				lat = result.items[0].point.my;
		//				lon = result.items[0].point.mx;
		//			} else {
		//				lat = result.items[0].lat;
		//				lon = result.items[0].lon;
		//			}
		//			ZdcEmapSearchSet(lat,lon);
		//		}
		//	}
		//	
		//	//�ϰ�ޤ�ɽ������
		//	ZdcEmapAreaObj = document.getElementById('ZdcEmapSearchArea')
		//	if(ZdcEmapAreaObj) {
		//		ZdcEmapAreaObj.style.visibility = "visible";
		//		//ZdcEmapArea.addMap(ZdcEmapAreaObj,opts);		del 2011/07/07 H.osamoto
		//		ZdcEmapAreaObj.style.zIndex = 99998;//�����̤ˤ�äƤ���
		//		ZdcEmapAreaObj.todCode = todCode;
		//	}
<?php ��ɽ����λ */ ?>
		ZdcEmapArea = new ZDC.AreaMap(
					{
						todCode: todCode,
						callback: showSearchMap,
						areaMap: document.getElementById('ZdcEmapSearchArea')
					}
		);
		ZDC._callback = function(){};
		// mod 2011/07/07 H.osamoto ]
	});
}
//�ϰ���Ĥ���
function ZdcEmapSearchAreaRemove(){
	if(!ZdcEmapAreaObj) return;
	//�ϰ�ޤ򱣤�
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapArea.removeMap();
	ZdcEmapArea.remove();
	// mod 2011/07/07 H.osamoto ]
	ZdcEmapAreaObj.style.visibility = "hidden";
	delete ZdcEmapAreaObj;
	ZdcEmapAreaObj = null;
}
// add 2011/07/07 H.osamoto
//�ϰ�ޥ���å�����ư��
var showSearchMap = function(rtn) {
	
	ZdcEmapShopDetailClose();
<?php /* ��ɽ������ ?>
	//	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["List"]; ?>","ZdcEmapMapObj.moveLatLon('"+rtn.latlon+"');");		mod 2011/07/07 H.osamoto
<?php ��ɽ����λ */ ?>
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["List"]; ?>","ZdcEmapSearchSet('"+rtn.latlon.lat+"','"+rtn.latlon.lon+"');");
	ZdcEmapSearchSet
	ZdcEmapHistorySave();
	
	// �ϰ�ޤ򥯥�å��������֤���������Ͽޤ��ư
	ZdcEmapMapObj.moveLatLon(rtn.latlon);
	mappoint = rtn.latlon;	// add 2011/10/06 H.osamoto
	
	//��������
	ZdcEmapSearchFirst = 1;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	ZdcEmapSearchShopStart();
	//ZdcEmapMapObj.saveMapLocation();		mod 2011/07/07 H.osamoto
	ZdcEmapMapObj.setHome(rtn.latlon);
	
};

// add 2011/04/14 H.Osamoto
//My���ꥢ����ѹ�
function ZdcEmapMyAreaSetGlobal(prm1, prm2, prm3, prm4, prm5){
	MYAREA_SEL1 = prm1;
	MYAREA_SEL2 = prm2;
	MYAREA_SEL3 = prm3;
	MYAREA_SEL4 = prm4;
	MYAREA_SEL5 = prm5;
}

// add 2011/04/14 H.Osamoto
//���ߡ��ѥ�᡼���ѥ����ॹ����׼���
function getTimestamp(){
	var d = new Date();

	var ye = d.getUTCFullYear();
	var mo = zeroPlus(d.getUTCMonth() + 1);
	var da = zeroPlus(d.getUTCDate());
	var ho = zeroPlus(d.getUTCHours());
	var mi = zeroPlus(d.getUTCMinutes());
	var se = zeroPlus(d.getUTCSeconds());

	return ye + mo + da + ho + mi + se;
}

// add 2011/04/14 H.Osamoto
function zeroPlus(value){
	return ("0" + value).slice(-2);
}

// add 2011/04/14 H.Osamoto
// �Ͽ��濴���ٷ��ټ���
function ZdcEmapGetMapCenter(){
	window.alert(aZdcPoint.my);
	window.alert(aZdcPoint.mx);
}

// add 2011/04/14 H.Osamoto
//My���ꥢ�ɲò���ɽ��
function ZdcEmapMyAreaAddDisp(p_s2, myar, lm){
	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaAddDisp&corp_id="+"<?php echo $cid; ?>&user_id="+p_s2+"&myar="+myar+"&lm="+lm;
	// ���ߡ��ѥ�᡼��
	damprm = getTimestamp();
	url += "&damprm="+damprm;
	
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapMyareaWrapperObj.innerHTML = html;
		ZdcEmapMyareaWrapperObj.style.visibility = "visible";
		ZdcEmapMyareaWrapperObj.style.zIndex = 9995;
		ZdcEmapMyareaWrapperObj.style.display = "block";
		document.frmMyareaAdd.myarea_name_add.focus();
	});
}

// add 2011/04/14 H.Osamoto
//My���ꥢ�ɲ�
function ZdcEmapMyAreaAdd(p_s2, myarea_name, myar, lm, cnt){
	myarea_name = document.getElementById('myarea_name_add').value;
	if (myarea_name == "") {
		window.alert('My���ꥢ̾�Τ�̤���Ϥΰ١���Ͽ�Ǥ��ޤ���');
		ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
	} else if (myarea_name.length > 50) {
		window.alert('My���ꥢ̾�Τ�ʸ������\n50ʸ����Ķ���Ƥ���١���Ͽ�Ǥ��ޤ���');
		ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
	} else if (!checkKeyword(myarea_name)) {
		window.alert('�����¸ʸ�����ޤޤ�Ƥ���١���Ͽ�Ǥ��ޤ���');
		ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
	} else {
		ret = window.confirm("��"+myarea_name+"�פ���Ͽ���ޤ�����");
		if (ret != true) {
			ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
		} else {
			var encstr = EscapeEUCJP(myarea_name);
			var aZdcPoint = ZdcEmapMapObj.getMapLocation();
			lat = aZdcPoint.my;
			lon = aZdcPoint.mx;
			
			//�ǥ������ɤ߹���
			ZdcEmapSearchClear();
			var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaAdd&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&myarea_name="+encstr+"&lat="+lat+"&lon="+lon+"&myar="+myar+"&lm="+lm;
			// ���ߡ��ѥ�᡼��
			damprm = getTimestamp();
			url += "&damprm="+damprm;

			<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
			<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
			ZdcEmapHttpRequestHtml(url, function(html,status){
				if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
				var tmp = html.split(",");
				if (tmp[0] == "ERR") {
					window.alert(tmp[1]);
				}
				ZdcEmapMyareaWrapperObj.style.zIndex = -1;
				if (html == "��Ͽ����λ�פ��ޤ�����"){
					var disp_url = "../../pc/index.htm?cid=<?php echo $cid; ?>&myar=e&p_s2="+p_s2+"&lm="+lm+"&myardisp=1&lat="+lat+"&lon="+lon+"&area_no="+cnt;
					comitMyareaAdd("<?PHP echo $D_DIR_BASE_G; ?>company/<?php echo $cid; ?>/", 1, disp_url);
				} else {
					comitMyareaAdd("<?PHP echo $D_DIR_BASE_G; ?>company/<?php echo $cid; ?>/", 0, "");
				}
			});
		}
	}
}

// add 2011/04/14 H.Osamoto
//My���ꥢ�Խ�����ɽ��
function ZdcEmapMyAreaEditDisp(p_s2, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaEditDisp('"+"<?PHP echo $cid; ?>"+"','"+p_s2+"');");
	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaSel&corp_id="+"<?php echo $cid; ?>&user_id="+p_s2+"&myar="+myar+"&lm="+lm;
	// ���ߡ��ѥ�᡼��
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
	});
}

// add 2011/04/14 H.Osamoto
//My���ꥢ̾���ѹ�
function ZdcEmapMyAreaNameUpdt(myarea_id, p_s2, myarea_name, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaNameUpdt('"+"<?PHP echo $cid; ?>"+"','"+myarea_id+"','"+myarea_name+"');");
	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaNameUpdt&myarea_id="+myarea_id+"&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&myarea_name="+myarea_name+"&myar="+myar+"&lm="+lm;
	// ���ߡ��ѥ�᡼��
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		
		var tmp = html.split(",");
		if (tmp[0] == "ERR") {
			window.alert(tmp[1]);
			ZdcEmapMyAreaEditDisp(p_s2, myar, lm);
		} else {
			ZdcEmapSearchWindowObj.innerHTML = html;
			ZdcEmapSearchWindowObj.style.visibility = "visible";
			if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		}
	});
}

// add 2011/04/14 H.Osamoto
//My���ꥢɽ������ѹ�
function ZdcEmapMyAreaOrderUpdt(myarea_id, corp_id, p_s2, disp_order, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaNameUpdt('"+"<?PHP echo $cid; ?>"+"','"+myarea_id+"','"+corp_id+"','"+disp_order+"');");
	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaOrderUpdt&myarea_id="+myarea_id+"&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&disp_order="+disp_order+"&myar="+myar+"&lm="+lm;
	// ���ߡ��ѥ�᡼��
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
	});
}

// add 2011/04/14 H.Osamoto
//My���ꥢ���
function ZdcEmapMyAreaDelete(myarea_id, corp_id, p_s2, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaDelete('"+"<?PHP echo $cid; ?>"+"','"+myarea_id+"','"+corp_id+"','"+p_s2+"');");
	//�ǥ������ɤ߹���
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaDel&myarea_id="+myarea_id+"&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&myar="+myar+"&lm="+lm;
	// ���ߡ��ѥ�᡼��
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
	});
}

// add 2011/04/14 H.Osamoto
//My���ꥢ̾�Υ��顼��������ɽ���ʵ����¸ʸ����
function ZdcEmapMyAreaShowErrDialog(message){
	window.alert(message);
}

//-------------------------------------------------------------
//���ո����ط�
//-------------------------------------------------------------
// del 2011/07/07 H.Osamoto [
//	<?php //if($D_REQ_JSAPI["npoi"]){ ?>	// 2008/10/22 Y.Matsukawa add
//	var ZdcEmapNpoi = new ZdcNearPoi();
//	ZdcEvent.addListener(ZdcEmapNpoi, "end", ZdcEmapPoiResult);
//	<?php //} ?>
// del 2011/07/07 H.Osamoto ]
//����å����٥��
function ZdcEmapPoiClick(mode) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapPoiRouteClear();
	ZdcEmapSearchEventStop();
	ZdcEmapShopMsgClose();
	//���̤��ڤ��ؤ���
	if(ZdcEmapCondObj.mode != "jnr") {
		ZdcEmapSearchShopClose();
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_jnr.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_jnr.htm?cid=<?PHP echo $cid; ?>";
		<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> jnr["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapSearchNpoi(mode);
		});
		//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Npoi"]; ?>","");		mod 2010/06/16 Y.Matsukawa
		if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Npoi"]; ?>","");
			else ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Npoi"]; ?>","");
		ZdcEmapHistorySave();
		ZdcEmapCondObj.mode = "jnr";
		ZdcEmapCondObj.style.visibility = "visible";
	} else {
		ZdcEmapSearchNpoi(mode);
	}
}
//��������
function ZdcEmapSearchNpoi(mode) {
	ZdcEmapReadOn();
	
	var p   = new ZdcPoint();
	p = ZdcEmapMapObj.getMapLocation();
	
	//����������
	var code="";
	if(document.ZdcEmapJnrForm) {
		var obj,jnr=new Array(),jnrcnt=0;
		for(var i = 0;i < document.ZdcEmapJnrForm.elements.length;i ++) {
			obj = document.ZdcEmapJnrForm.elements[i];
			if(!obj) break;
			switch(obj.type) {
				case "checkbox":
					if(obj.checked == true) {
						jnr[jnrcnt] = obj.value;
						jnrcnt ++;
					}
					break;
				case "select-one":
					if(obj.options[obj.selectedIndex].value) {
						jnr[jnrcnt] = obj.options[obj.selectedIndex].value;
						jnrcnt ++;
					}
					break;
				case "radio":
					if(obj.checked == true && obj.value) {
						jnr[jnrcnt] = obj.value;
						jnrcnt ++;
					}
					break;
				default:
					if(obj.value) {
						jnr[jnrcnt] = obj.value;
						jnrcnt ++;
					}
					break;
			}
		}
		for(var i = 0;i < jnrcnt;i ++) {
			if(code) code += ",";
			code += jnr[i];
		}
	}
	if(!code) code = '<?PHP echo $D_POI_JNRMN; ?>';//�ǥե���ȥ�����
	//�����ϰϤη׻�
	var rad = 0;
	if(mode == 0) {
		//�Ͽ��⸡��
		var box = ZdcEmapMapObj.getMapBoundBox();
		if((box.maxx - box.minx) > (box.maxy - box.miny)) {
			//������Ȥ�
			var p1 = new ZdcPoint(box.maxx,box.maxy,<?PHP echo $D_PFLG; ?>);
			var p2 = new ZdcPoint(box.minx,box.maxy,<?PHP echo $D_PFLG; ?>);
		} else {
			//������Ȥ�
			var p1 = new ZdcPoint(box.maxx,box.maxy,<?PHP echo $D_PFLG; ?>);
			var p2 = new ZdcPoint(box.maxx,box.miny,<?PHP echo $D_PFLG; ?>);
		}
		rad = parseInt(ZdcEmapGeometricObj.getPoint2PointDistance(p1,p2) / 2.1);//�Ͽ��ϰϥ��ꥮ����оݤȤ��ʤ��褦2.1�Ⱦ����ݤ��
	} else {
		//�Ǵ󸡺�
		rad = <?PHP echo $D_POI_RAD; ?>;
	}
	if (rad > <?PHP echo $API_RAD_MAX; ?>) rad = <?PHP echo $API_RAD_MAX; ?>;//�Ǵ�긡��API��Ⱦ�»������ͤ�Ķ���Ƥ�����Ͼ���ͤǸ���
	//
	var opts = new ZdcNearPoiOptions();
	opts.startPos = 1;
	opts.maxCount =  <?PHP if (isset($D_POI_MAX)) echo $D_POI_MAX; ?>;
	opts.genreMenuCode = code;
	opts.genreCode = '<?PHP if (isset($D_POI_JNR)) echo $D_POI_JNR; ?>';
	opts.lat = p.my;
	opts.lon = p.mx;
	opts.limitCount = <?PHP if (isset($D_POI_MAX)) echo $D_POI_MAX; ?>;
	opts.radius = rad;
	opts.pointFlg = <?PHP echo $D_PFLG; ?>;
	opts.lang = '<?PHP echo $D_POI_LANG; ?>';	// add 2008/08/22 Y.Matsukawa
	ZdcEmapNpoi.opts = opts;
	
	if(opts.genreMenuCode) {
		//������λ��꤬���ä����Τ߸���������
		ZdcEmapPoiList(0);
		ZdcEmapNpoi.search(opts);
	}
	
}
//��������
function ZdcEmapPoiResult(result) {
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//���顼����
	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> poires["+result.status+"]");
		ZdcEmapListObj.innerHTML = "";
		ZdcEmapReadOff();
		return;
	}
	//�Ͽޤ��֤�
	var i,p,mrk,titlelink,title,item,maxlat=0,maxlon=0,minlat=999999999,minlon=999999999;;
	var icon = new ZdcIcon();
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//�ޡ��������
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapMapPoiMrkCnt = 0;
	for( i in result.items ){
		item = result.items[i];
		//��������κ���
		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
		                     <?PHP echo $D_ICON_POI_W; ?>,<?PHP echo $D_ICON_POI_H; ?>,0,0,
		                     <?PHP echo $D_ICON_POI_OFFSET_X; ?>,<?PHP echo $D_ICON_POI_OFFSET_Y; ?>,0,0,0,0,
		                     '<?PHP echo $D_ICON_POI_IMAGE_DIR; ?>'+item.genreMenuCode+'.gif',item.icons,
		                     item.poiName,"",0,
		                     null,function() { ZdcEmapTipsClick(this.id); },null);
		if (ZdcEmapMapPoiMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//ǰ�Τ���
		ZdcEmapMapPoiMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);
		//����Ǿ����ٷ��ټ���
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		ZdcEmapMapPoiMrkCnt ++;
	}
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	//��ư�̼��ѹ�
	ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,ZdcEmapMapObj.getMapLocation());
	ZdcEmapReadOff();
}
//�ꥹ��ɽ��
function ZdcEmapPoiListClick(page) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapPoiList(page)
}
function ZdcEmapPoiList(page) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_npoi.htm?cid=<?PHP echo $cid; ?>"+		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_npoi.htm?cid=<?PHP echo $cid; ?>"+
		      "&jnrmn="+ZdcEmapNpoi.opts.genreMenuCode+"&jnr="+ZdcEmapNpoi.opts.genreCode+
		      "&lat="+ZdcEmapNpoi.opts.lat+"&lon="+ZdcEmapNpoi.opts.lon+"&radius="+ZdcEmapNpoi.opts.radius+"&page="+page;
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> poi["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}

// add 2008/04/21 Y.Matsukawa
//-------------------------------------------------------------
// ����������ɥ���
//-------------------------------------------------------------
function ZdcEmapGetSearchTopCond(prefix, suffix) {
	var condStr = '';
	if (!prefix) prefix = '';
	if (!suffix) suffix = '';
	//for(i = 1;i <= 50;i ++) {		mod 2009/11/07 Y.Matsukawa
	for(i = 1;i <= 200;i ++) {
		var cond = document.getElementById("scond"+i);
		if (cond) {
			v = '';
			if (cond.type == "checkbox") {
				if (cond.checked == true) {
					v = '1';
				}
			} else if (cond.type == "select-one") {
				if (cond.options[cond.selectedIndex].value) {
					v = cond.options[cond.selectedIndex].value;
				}
			} else if (cond.type == "radio") {
				if (cond.checked == true) {
					v = cond.value;
				}
			// add 2009/03/13 Y.Matsukawa [
			} else if (cond.type == "hidden") {
				v = cond.value;
			// add 2009/03/13 Y.Matsukawa ]
			}
			if (v) {
				if (condStr) condStr += "&";
				condStr += "cond"+i+"="+v;
			}
		}
	}
	if (condStr) condStr = prefix+condStr+suffix;
	return condStr;
}

// add 2010/05/11 Y.Matsukawa
//-------------------------------------------------------------
// �Ͽ޲��̤�cond�򸡺�������ɥ�cond��ȿ��
//-------------------------------------------------------------
function ZdcEmapCond2SearchTopCond() {
	if(document.ZdcEmapCondForm) {
		var obj,scond,idx;
		for(var i = 0;i < document.ZdcEmapCondForm.elements.length;i ++) {
			obj = document.ZdcEmapCondForm.elements[i];
			if (obj) {
				idx = obj.name.replace("cond","");
				scond = document.getElementById("scond"+idx);
				if(scond) {
					switch(obj.type) {
						case "checkbox":
							if (scond.type == "checkbox") scond.checked = obj.checked;
							break;
						case "select-one":
							//
							break;
						case "radio":
							//
							break;
						case "text":
							//
							break;
						case "hidden":
							if (scond.type == "checkbox") {
								if(obj.value) scond.checked = true;
								else scond.checked = false;
							}
							break;
						default:
							break;
					}
				}
			}
		}
	}
}

// add 2010/05/11 Y.Matsukawa
//-------------------------------------------------------------
// cond�񤭴���
//-------------------------------------------------------------
function ZdcEmapChangeCond(prm) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
	if (prm) url = url + "&" + prm;
	url += "&<?php echo $P_FREEPARAMS; ?>";
	<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php }  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php }  // mod 2011/10/03 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa  // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapCondObj.innerHTML = html;
	});
}

// add 2010/05/11 Y.Matsukawa
//-------------------------------------------------------------
// ����������ɥ�cond���Ͽ޲��̤�cond��ȿ��
//-------------------------------------------------------------
function ZdcEmapSearchTopCond2Cond() {
	// ����������ɥ�cond�������
	var prm = ZdcEmapGetSearchTopCond();
	// �ѥ�᡼�����Ϥ��줿cond�����
	var p_cond = "";
<?php
	for($i = 1;$i <= 200;$i ++) {
		// mod 2011/10/03 Y.Nakajima
		if(isset($_VARS["cond".$i]) && $_VARS["cond".$i]) {
?>
			if (prm.indexOf("<?php echo 'cond'.$i.'='; ?>") < 0) {
				if(p_cond) p_cond += "&";
				p_cond += "<?php echo 'cond'.$i.'='.$_VARS['cond'.$i]; ?>";
			}
<?php
		}
	}
?>
	if (prm && p_cond) p_cond += "&";
	ZdcEmapChangeCond(p_cond + prm);
}

// add 2011/02/16 Y.Matsukawa
//-------------------------------------------------------------
// ��ȯ�ϻ���롼�Ȥ����Ͻ���ͤ򥻥å�
//-------------------------------------------------------------
var ZdcEmapFRouteInitStr = null;
function ZdcEmapSetFRouteInit(str) {
	ZdcEmapFRouteInitStr = str;
}

// add 2011/04/14 H.Osamoto
//-------------------------------------------------------------
// �����¸ʸ�������å�
//-------------------------------------------------------------
function checkKeyword(str){
	var str_length = str.length;
	var code, scode;

	for (var i = 0; i < str_length; i++) {
		code = str.charCodeAt(i);
		code = code.toString(16);
		
		//4��ʲ��ʤ���Ƭ��0���ɲ�
		if(code.length < 4){
			var figure = 4 - code.length;
			var rcode = "";
			for(var fi = 0; fi < figure; fi++){
				rcode += "0";
				if(rcode.length > figure){
					rcode = rcode.slice(0,figure);
					break;
				}
			}
			code = rcode + code;
		}

		//�ϰϥ����å������ԥ����ɤȥ��֥����ɥ����å�
		if(!(0x20 <= "0x"+code && 0x7e >= "0x"+code) && 
			code != "000a" && code != "000d" && code != "0009"){
			if(code.charAt(0) == "0" || ( code.charAt(0) >= "2" && 
				code.charAt(0) <= "9" ) || code.charAt(0) == "f"){
				scode = code.substring(1,4);
				if(eval("u"+code.charAt(0)+"a").indexOf(":"+scode) == -1){
					return false;
				}
			}else{
				return false;
			}
		}
	}
	return true;
}
