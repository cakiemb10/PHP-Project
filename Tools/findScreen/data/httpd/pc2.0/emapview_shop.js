<?PHP
// ------------------------------------------------------------
// �Ͽ�����javasctipt ��˵��������˴ط�������
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2007/11/16 Y.Matsukawa	���ɽ�������Ͽ�API��ChangeLocation���٥�Ȥ�����ȯ�����뢪����˸��餹
// 2007/11/28 Y.Matsukawa	�᤭�Ф���ɽ���������֤ǺǴ�ظ�����¹Ԥ���ȡ��롼�Ȥ�ɽ������ʤ��ʤ��Զ�����
// 2008/08/22 Y.Matsukawa	�ѻ��б�
// 2008/10/15 Y.Matsukawa	���Զ������ۼ��յ�����ɽ������ʤΤˡ��᤭�Ф�����̾����å��Ǿܺ�ɽ���塢�Ͽް�ư����ȼ��յ�����ɽ������Ƥ��ޤ�
//                          ���Զ������ۼ��յ�����ɽ������ξ�硢�Ǵ��ɽ������ѥ󤯤��Ǿܺ�ɽ������ä������إ������󤬾ä��ʤ��ʺǴ���ߤ�Ʊ�͡�
// 2008/10/22 Y.Matsukawa	���Ѥ��ʤ�JS�ϥ��ɤ��ʤ�
// 2009/02/06 Y.Matsukawa	����FW�ˤ������ʤ����
// 2009/02/16 Y.Matsukawa	���Զ������ۡ�FF�Τߡ˥�������ޥ�������ǿ᤭�Ф�ɽ���ξ�硧�Ͽ��濴�Υ��������˥ޥ������֤��Ƥ���ȡ��᤭�Ф���ɽ������ɽ���򷫤��֤�
//                          ��wait��å�������ɽ������ɽ�������ȡ������٤˥ޥ������󥤥٥�Ȥ�ȯ������褦�ʤΤǡ��᤭�Ф��Ǥ�wait��å������ϽФ��ʤ��褦�ˤ����
// 2009/02/23 Y.Matsukawa	�����ܺ٤˼�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/03/06 Y.Matsukawa	�����ꥹ�Ȥ˼�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/03/17 Y.Matsukawa	�᤭�Ф��˼�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/03/26 Y.Matsukawa	�ʹ��߲��̤ؼ�ͳ���ܥѥ�᡼��������Ϥ�
// 2009/08/18 Y.Matsukawa	������������ץ�åȽ���ѹ��ʶᤤ��Τ��ˡ�
// 2009/09/04 Y.Matsukawa	�����̼�
// 2009/09/28 Y.Matsukawa	�����ܺ٥ƥ�ץ졼�����<script>������¹�
// 2009/10/13 Y.Matsukawa	�Ǵ����������˾ܺٵ�����Ф��ʤ�
// 2009/11/07 Y.Matsukawa	�������ܳ�ĥ��50��200��
// 2009/12/10 Y.Matsukawa	�ܺ٥ƥ�ץ졼�Ȥ�cond���Ϥ�
// 2010/01/27 Y.Matsukawa	�ʤ���ߥƥ�ץ졼�Ȥ���ƻ�ܸ������ɤ��Ϥ�
// 2010/04/23 Y.Matsukawa	���Զ�罤���ۺǴ��������������ɽ�����ʤ�����ξ�硢�Ǵ�������������ܺ�ɽ�������ݤ����ǥե졼�ब�ä��ʤ��ʤ�
// 2010/05/21 Y.Matsukawa	���Զ�罤���۾ܺٵ�����Ǵ��˽Ф��ʤ�����λ����ܺ�ɽ�����˺Ǵ�ꥼ����Ƚ̼ܤ������Ƥ��ޤ�
// 2010/06/16 Y.Matsukawa	��ȯ�Ϥ���ꤷ�ƥ롼��õ��
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2010/09/07 Y.Matsukawa	��ȯ�Ϥ���ꤷ�ƥ롼��õ����Light��Maplink��
// 2010/09/13 Y.Matsukawa	�����ܺ�ɽ�����˵���ID��Cookie��¸
// 2010/11/15 Y.Matsukawa	cond���롼�ԥ�
// 2011/02/09 Y.Matsukawa	��������������ɥᥤ�󤫤�����IP���ѹ�
// 2011/02/16 Y.Matsukawa	������̽�����������򤷤�����򡢽�ȯ�ϻ���롼�Ȥ����Ͻ���ͤˤ���
// 2011/04/27 H.Osamoto		New��������Ƚ�ꥫ�����ɲ�
// 2011/05/26 K.Masuda		cond����ι���
// 2011/06/15 K.Masuda		�ե�����ɽ����Ǥ�Ƹ����Ǥ���褦�ˤ���
// 2011/06/16 Y.Matsukawa	�ܺٹ�������JS�¹�
// 2011/06/27 H.osamoto		�Ǵ�ء��롼��õ�����˼¹Ԥ������������ɲ�
// 2011/06/29 K.Masuda		initlat��initlon���Ͽޤ�ɽ��������֤�����ʥ�������������Ͽް�ư���ʤ���
// 2011/07/07 H.Osamoto		�ޥĥ�����API2.0�б���
// 2011/10/06 H.Osamoto		�ϰ�ޤ���Ƹ��������ݤ˵����ꥹ�Ȥ���������ʤ��Զ�����
// 2012/03/16 H.Osamoto		���Զ�罤���ۥ롼��õ��������ץȥ��顼����
// ------------------------------------------------------------
include("./inc/define.inc");  // ��������
?>
<?php
// add 2010/11/15 Y.Matsukawa [
//-------------------------------------------------------------
// cond���롼�ԥ����
// ZdcEmapCondGroup[cond�ֹ�] = ���롼���ֹ�(1��n);
//-------------------------------------------------------------
?>
var ZdcEmapCondGroup = new Array();
var ZdcEmapCondAndOr = new Array();
<?php
// mod 2011/10/03 Y.Nakajima
if (isset($D_COND_GRP) && is_array($D_COND_GRP) && count($D_COND_GRP)) {
	foreach ($D_COND_GRP as $g => $grp) {
?>
ZdcEmapCondAndOr[<?php echo $g ?>] = '<?php echo $D_COND_ANDOR[$g] ?>';
<?php
		foreach ($grp as $cnd) {
?>
ZdcEmapCondGroup[<?php echo $cnd ?>] = <?php echo $g ?>;
<?php
		}
	}
}
// add 2010/11/15 Y.Matsukawa ]
?>
//-------------------------------------------------------------
//���������ط�
//-------------------------------------------------------------
var ZdcEmapSearchPoint = null;//�����������֤��ݻ�
var ZdcEmapSearchScale = null;//���������̼ܤ��ݻ�
var ZdcEmapSearchFirst = null;//���ַ����κǽ�θ������ݤ�
//��������
function ZdcEmapSearchShopClick() {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	ZdcEmapSearchShop();
}
function ZdcEmapSearchShopStart() {
	if(ZdcEmapMapObj.ZdcEmapMode != "print") ZdcEmapSearchClickFlg = 1;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	//
	ZdcEmapSearchEventAdd("ZdcEmapSearchShop()");
	ZdcEmapSearchEventStart();
	//�����ʳ��Υ�������򥯥ꥢ
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);	mod 2011/07/07 H.osamoto
		if (ZdcEmapMapPoiMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
			ZdcEmapMapObj.removeWidget(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
	}
	ZdcEmapMapPoiMrkCnt = 0;
	//���̤��ڤ��ؤ���
	if(ZdcEmapCondObj.mode != "cond") {
		ZdcEmapSearchShopClose();//�����ʳ��Υꥹ�Ȥ�ä�
		if (mappoint) mappoint = "";	// add 2011/10/06 H.osamoto
		//		var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>&";
		//		for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "cond"+i+"="+ZdcEmapSaveCond[i]+"&";//�ʹ����
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		//for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//�ʹ����		mod 2009/11/07 Y.Matsukawa
		for(i = 1;i <= 200;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//�ʹ����
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } // mod 2011/10/03 Y.Nakajima?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } // mod 2011/10/03 Y.Nakajima?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php if(isset($https_req) && $https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa // mod 2011/10/03 Y.Nakajima ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapSearchShop();//�������ɽ������Ƥ��鸡������
		});
		ZdcEmapCondObj.mode = "cond";
		ZdcEmapCondObj.style.visibility = "visible";
	} else {
		ZdcEmapSearchShop();
	}
}
//�����ᥤ�����
function ZdcEmapSearchShop() {
	ZdcEmapReadOn();
	//���֡��ϰϼ���
	// mod 2011/07/07 H.osamoto [
	//	var p   = new ZdcPoint();
	//	p = ZdcEmapMapObj.getMapLocation();
	//	var box = ZdcEmapMapObj.getMapBoundBox();
	var latlon = ZdcEmapMapObj.getLatLon();
	var p = ZdcEmapMapObj.getLatLon();
	// add 2011/10/06 H.osamoto [
	if (mappoint) {
		p = mappoint;	// ���ֻ�����ϰ�ư��ΰ��ٷ��٤����
		mappoint = "";
	}
	// add 2011/10/06 H.osamoto ]
	if (mappoint) {
		p = mappoint;	// ���ֻ�����ϰ�ư��ΰ��ٷ��٤����
		mappoint = "";
	}
	// add 2011/10/06 H.osamoto ]
	var box = ZdcEmapMapObj.getLatLonBox();
	// mod 2011/07/07 H.osamoto ]
	// del 2011/07/07 H.osamoto [
	//	//�������뤫�ݤ���Ƚ��
	//	if(ZdcEmapSearchPoint != null) {
	//		var pix1 = ZdcEmapMapObj.convertPoint2Pixel( ZdcEmapSearchPoint, 2 );
	//		var pix2 = ZdcEmapMapObj.convertPoint2Pixel( p, 2 );
	//		if(Math.abs(pix1.x-pix2.x) < <?PHP echo $D_SHOP_SEARCHPIX; ?> && 
	//		   Math.abs(pix1.y-pix2.y) < <?PHP echo $D_SHOP_SEARCHPIX; ?> &&
	//		   ZdcEmapSearchScale == ZdcEmapMapObj.getMapScale()) {
	//			ZdcEmapReadOff();
	//			return;
	//		}
	//	}
	// del 2011/07/07 H.osamoto ]
	if(ZdcEmapSearchPoint != null && <?PHP echo $D_SHOP_SEARCHPIX; ?> == -1) {
		//��ư�Ƹ������ʤ�
		ZdcEmapReadOff();
		return;
	}
	//��ư�������٥�����
	ZdcEmapSearchEventStop();
	// del 2011/07/07 H.Osamoto [
	//	// 2011/06/15 K.Masuda mod [
	//	//ZdcEmapShopMsgClose();
	//	if( <?php //if($D_HUKIDASHI_SEARCH){echo "false";}else{echo "true";} ?> ){
	//		ZdcEmapShopMsgClose();
	//	}
	//	// 2011/06/15 K.Masuda mod ]
	// del 2011/07/07 H.Osamoto ]
	//�ʤ���߾�����
	cond = ZdcEmapGetCond();
	//
	var opts = new ZdcNearShopOptions();
	opts.cid='<?PHP echo $D_CID; ?>'
	opts.lat = p.lat;
	opts.lon = p.lon;
	if(ZdcEmapSearchFirst != 1) {
		//opts.latlon = box.miny+","+box.minx+","+box.maxy+","+box.maxx;	mod 2011/07/07 H.osamoto
		opts.latlon = box.min.lat+","+box.min.lon+","+box.max.lat+","+box.max.lon;
		opts.radius = <?PHP echo $D_SHOP_RAD_RE; ?>;
	} else {
		ZdcEmapSearchFirst = 0;
		opts.radius = <?PHP echo $D_SHOP_RAD; ?>;
	}
	opts.jkn = cond;
	opts.pos = 1;
	opts.maxCount = <?PHP echo $D_SHOP_MAX; ?>;
	opts.limitCount = <?PHP echo $D_SHOP_MAX; ?>;
	opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
	// add 2009/10/13 Y.Matsukawa [
	<?PHP if ($D_SHOP_LIST_NO_DTLSHOP) { ?>
	if (ZdcEmapMapShopDetailMrkId != null) {
		// �ܺ�ɽ����ε���ID
		// mod 2011/07/07 H.Osamoto [
		//	var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		//	if (mrk && mrk.data1) opts.exceptKid = mrk.data1;
		var mrk = ZdcEmapMapShopDetailMrkId;
		if (mrk && mrk.data1) opts.exceptKid = mrk.data1;
		// mod 2011/07/07 H.Osamoto ]
	}
	<?PHP } ?>
	// add 2009/10/13 Y.Matsukawa ]
	ZdcEmapNearShop.opts = opts;
	
	//�ꥹ�Ȥ�ɽ������
	ZdcEmapSearchShopList(0);
	//���������ɽ������
	ZdcEmapNearShop.search(opts,ZdcEmapSearchShopResult);
}
//�ʤ꺮�߾���Ȥ�Ω��
function ZdcEmapGetCond() {
	var cond="";
	var condArr=new Array();	<?php // add 2010/11/15 Y.Matsukawa ?>
	if(document.ZdcEmapCondForm) {
		//var obj,chk=new Array(),chkcnt=0,col=new Array(),colcnt=0;	mod 2009/02/06 Y.Matsukawa
		var obj,chk=new Array(),chkcnt=0,col=new Array(),colcnt=0,fw=new Array(),fwcnt=0;
		var all=new Array(),allcnt=0,allcondno=new Array(),condno='';	<?php // add 2010/11/15 Y.Matsukawa ?>
		for(var i = 0;i < document.ZdcEmapCondForm.elements.length;i ++) {
			obj = document.ZdcEmapCondForm.elements[i];
			if(!obj) break;
			condno = obj.name.replace('cond','');	<?php // add 2010/11/15 Y.Matsukawa ?>
			switch(obj.type) {
				case "checkbox":
					if(obj.checked == true) {
						chk[chkcnt] = obj.value;
						all[allcnt] = chk[chkcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						chkcnt ++;
					}
					break;
				case "select-one":
					if(obj.options[obj.selectedIndex].value) {
						col[colcnt] = obj.options[obj.selectedIndex].value;
						all[allcnt] = col[colcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						colcnt ++;
					}
					break;
				case "radio":
					if(obj.checked == true && obj.value) {
						col[colcnt] = obj.value;
						all[allcnt] = col[colcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						colcnt ++;
					}
					break;
				// add 2009/02/06 Y.Matsukawa [
				case "text":
					if(obj.value) {
						//fw[fwcnt] = "FREE_SRCH:FW:"+"'"+urlencode(obj.value)+"'";
						fw[fwcnt] = "FREE_SRCH:FW:"+"'"+obj.value+"'";
						all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						fwcnt ++;
					}
					break;
				case "button":
					break;
				// add 2009/02/06 Y.Matsukawa ]
				default:
					if(obj.value) {
						col[colcnt] = obj.value;
						all[allcnt] = col[colcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						colcnt ++;
					}
					break;
			}
		}

		<?php // add 2011/05/26 K.Mausda [ ?>
		var cno,newcond = "",newqs = "";
		var qstr = QSTRING.split('&');
		for(var i=0; i<allcnt; i++) {
			cno = allcondno[i];
			newcond += "cond"+cno+"=1&";
		}
		for(var q=0; q<qstr.length; q++) {
			if( qstr[q] == '' ) continue;
			if( qstr[q].substr(0,4) != 'cond' ){
				newqs += qstr[q]+"&";
			}
		}
		QSTRING = newqs + newcond;
		<?php // add 2011/05/26 K.Mausda ] ?>

		<?php // add 2010/11/15 Y.Matsukawa [ ?>
		// ���롼�ԥ����ꤵ��Ƥ�����
		if (ZdcEmapCondGroup.length > 0) {
			for(var i = 0;i < allcnt;i ++) {
				cn = allcondno[i];
				gr = ZdcEmapCondGroup[cn];
				if (gr != undefined) {
					if(!condArr[gr]) condArr[gr] = '';
					if(condArr[gr]) condArr[gr] += ' '+ZdcEmapCondAndOr[gr]+' ';
					condArr[gr] += all[i];
				}
			}
			if(condArr.length > 0) {
<?php
// mod 2011/10/03 Y.Nakajima
if (isset($D_COND_GRP) && is_array($D_COND_GRP) && count($D_COND_GRP)) {
	foreach ($D_COND_GRP as $g => $grp) {
?>
				if(condArr[<?php echo $g ?>]) {
					if(cond) cond += ' <?PHP echo $D_COND_GRP_ANDOR; ?> ';
					cond += '('+condArr[<?php echo $g ?>]+')';
				}
<?php
	}
}
?>
			}
		// ���롼�ԥ�����ʤ��ʴ�¸ư���
		} else {
		<?php // add 2010/11/15 Y.Matsukawa ] ?>
			// checkbox
			for(var i = 0;i < chkcnt;i ++) {
				if(cond) cond += " <?PHP echo $D_SHOP_COND; ?> ";
				cond += chk[i];
			}
			if(cond) cond = "("+cond+")";
			// select-one,radio,����¾
			for(var j = 0;j < colcnt;j ++) {
				if(cond) cond += " <?PHP echo $D_SHOP_COND_COL; ?> ";
				cond += "("+col[j]+")";
			}
			// add 2009/02/06 Y.Matsukawa [
			// text
			for(var k = 0;k < fwcnt;k ++) {
				if(cond) cond += " <?PHP echo $D_SHOP_COND_COL; ?> ";
				cond += fw[k];
			}
			// add 2009/02/06 Y.Matsukawa ]
		}
	}
	return cond;
}
//�ʤ꺮�߾��ѥ�᡼������		add 2009/12/10 Y.Matsukawa
function ZdcEmapGetCondParm() {
	var cond="";
	if(document.ZdcEmapCondForm) {
		var obj,arrcond=new Array(),condcnt=0;
		for(var i = 0;i < document.ZdcEmapCondForm.elements.length;i ++) {
			obj = document.ZdcEmapCondForm.elements[i];
			if(!obj) break;
			switch(obj.type) {
				case "checkbox":
					if(obj.checked == true) {
						arrcond[condcnt] = obj.name+'=1';
						condcnt ++;
					}
					break;
				case "select-one":
					if(obj.options[obj.selectedIndex].value) {
						val = obj.options[obj.selectedIndex].value.split(':');
						arrcond[condcnt] = obj.name+'='+val[1];
						condcnt ++;
					}
					break;
				case "radio":
					if(obj.checked == true && obj.value) {
						val = obj.value.split(':');
						arrcond[condcnt] = obj.name+'='+val[1];
						condcnt ++;
					}
					break;
				case "text":
					break;
				case "button":
					break;
				default:
					if(obj.value) {
						val = obj.value.split(':');
						arrcond[condcnt] = obj.name+'='+val[1];
						condcnt ++;
					}
					break;
			}
		}
		//cond�ѥ�᡼�����Ȥ�Ω��
		for(var i = 0;i < condcnt;i ++) {
			if(cond) cond += '&';
			cond += arrcond[i];
		}
	}
	return cond;
}
//������̤ν���
function ZdcEmapSearchShopResult(result) {
	var i,item,mrk,tmp,icnt,maxlat=0,maxlon=0,minlat=999999999,minlon=999999999;
	// add 2011/07/07 H.osamoto [
	function setLatLon(lat, lon){
		this.lat  = lat;
		this.lon = lon;
	}
	latlons = new Array();
	// add 2011/07/07 H.osamoto ]
	
	//�ޡ��������
	if(ZdcEmapMapShopMrkCnt != null) {
		for( i = 0;i < ZdcEmapMapShopMrkCnt;i ++) {
			//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);	mod 2011/07/07 H.osamoto
			if (ZdcEmapMapShopMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
				ZdcEmapMapObj.removeWidget(ZdcEmapMapShopMrkId[i]);
				ZdcEmapMapShopMrkId[i] = null;
			}
		}
	}
	ZdcEmapMapShopMrkCnt = 0;
	//���顼����
	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> listres["+result.status+"]");
		ZdcEmapSearchEventStart();
		ZdcEmapSearchShopClose();
		ZdcEmapReadOff();
		return;
	}
	//�Ͽޤ��֤�
	//for( i in result.items ){		mod 2009/08/18 Y.Matsukawa
	icnt = result.items.length;

	for (i=icnt-1; i>=0; i--) {
		item = result.items[i];
		if(!item.icon) break;
		if(item.nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
			else tmp = "";
		// add 2011/04/27 H.Osamoto [
		<?php 
		// mod 2011/10/03 Y.Nakajima
		if (isset($D_NEW_ICON_COL) && $D_NEW_ICON_COL) { 
		?>
		if(item.<?PHP echo $D_NEW_ICON_COL; ?> == 1) tmp = ZdcEmapIconImg["@NEW"];
		<?php 
		}
		?>
		// add 2011/04/27 H.Osamoto ]
		// del 2011/07/07 H.Osamoto [
		//	mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
		//						ZdcEmapIconW[item.icon],ZdcEmapIconH[item.icon],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
		//						ZdcEmapIconOffsetX[item.icon],ZdcEmapIconOffsetY[item.icon],ZdcEmapIconW[item.icon]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[item.icon],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
		//						ZdcEmapIconImg[item.icon],tmp,
		//						item.id,item.icon,item.nflg,
		//						<?PHP
		//							// ����å�
		//							if($D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(this.id); }"; 
		//								//else if($D_KYO_ICON_CLK == 2) echo "function() { ZdcEmapShopDetailKidClick(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg); }"; 		mod 2009/09/04 Y.Matsukawa
		//								else if($D_KYO_ICON_CLK == 2) echo "function() { ZdcEmapShopDetailKidClick(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg,this.lvl); }";
		//								else echo "null"; 
		//						?>,
		//						<?PHP
		//							// �ޥ��������С�
		//							if(!$D_KYO_ICON_MO) echo "null"; 
		//							if($D_KYO_ICON_MO) echo "function() { ZdcEmapShopMsg(this.id); }"; 
		//						?>,
		//						//null		mod 2009/10/14 Y.Matsukawa
		//						<?PHP
		//							// �ޥ���������
		//							if($D_KYO_ICON_MOUT == 1) echo "function() { ZdcEmapShopMsgClose(); }";
		//							else echo "null"; 
		//						?>
		//						,item.lvl		// add 2009/09/04 Y.Matsukawa
		//						);
		//	if (ZdcEmapMapShopMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);//ǰ�Τ���
		//	ZdcEmapMapShopMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);
		// del 2011/07/07 H.Osamoto ]
		//����Ǿ����ٷ��ټ���
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		
		// mod 2011/07/07 H.osamoto [
		//	latlons[ZdcEmapMapShopMrkCnt] = new setLatLon( item.lat, item.lon );
		latlons[ZdcEmapMapShopMrkCnt] = new ZDC.LatLon(item.lat, item.lon);
		mrk = ZdcEmapMakeMrkApi2(i, item.lat, item.lon, 
								ZdcEmapIconW[item.icon], ZdcEmapIconH[item.icon],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
								ZdcEmapIconOffsetX[item.icon], ZdcEmapIconOffsetY[item.icon],ZdcEmapIconW[item.icon]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[item.icon],
								ZdcEmapIconImg[item.icon],tmp,
								item.id, item.icon, '', item.nflg,
								<?PHP
									// ����å�
									if($D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(this.id); }"; 
										else echo "null"; 
								?>
								, null
								,item.lvl
							);
		if (ZdcEmapMapShopMrkId[i] != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapShopMrkId[i]);//ǰ�Τ���
		ZdcEmapMapObj.addWidget(mrk);
		ZdcEmapMapShopMrkId[i] = mrk;
		// modd 2011/07/07 H.Osamoto ]
		ZdcEmapMapShopMrkCnt ++;
	}
	if(ZdcEmapSearchClickFlg) {
		ZdcEmapSearchClickFlg = 0;
		//����������ϲ��̰�ư
		if (ZdcEmapMapShopMrkCnt > 0) {
			//���������ޤ��ϰϤ˰�ư
			// mod 2011/07/07 H.Osamoto [
			//ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,ZdcEmapMapObj.getMapLocation(),1);
			if (!ZdcEmapMapShopDetailMrkId) {
				var center_latlon = ZdcEmapMapObj.getLatLon();
				
				var latdist;
				var londist;
				var varminlat;
				var varminlon;
				var varmaxlat;
				var varmaxlon;
				var varlatlon_box = new Array();
				
				// �Ǥ�Υ�줿lat�κ�ʬ
				var minlatdist = Math.abs(minlat - center_latlon.lat);
				var maxlatdist = Math.abs(maxlat - center_latlon.lat);
				if (minlatdist > maxlatdist) {
					latdist = minlatdist;
				} else {
					latdist = maxlatdist;
				}
				
				// �Ǥ�Υ�줿lon�κ�ʬ
				var minlondist = Math.abs(minlon - center_latlon.lon);
				var maxlondist = Math.abs(maxlon - center_latlon.lon);
				if (minlondist > maxlondist) {
					londist = minlondist;
				} else {
					londist = maxlondist;
				}
				
				varminlat = center_latlon.lat - latdist;
				varminlon = center_latlon.lon - londist;
				varmaxlat = center_latlon.lat + latdist;
				varmaxlon = center_latlon.lon + londist;
				
				// �Ͽ�ɽ���̼ܼ����Ѳ��۵���
				varlatlon_box[0] = new ZDC.LatLon(varminlat, varminlon);
				varlatlon_box[1] = new ZDC.LatLon(varmaxlat, varmaxlon);
				
				var adjust = ZdcEmapMapObj.getAdjustZoom(varlatlon_box);
				ZdcEmapMapObj.setZoom(adjust.zoom);
			}
			// mod 2011/07/07 H.Osamoto ]
		//} else {		mod 2010/05/21 Y.Matsukawa
		} else if (!result.options.exceptKid) {
			//����Ⱦ�¤ν̼ܤ˰�ư  �����֤ˤ�ä�getPoint2PointDistance���ͤ��Ѥ�뤿�����׻����Ƥ���
			// mod 2011/07/07 H.Osamoto [
			//	var p = new ZdcPoint();
			//	p = ZdcEmapMapObj.getMapLocation();
			//	//var px = new ZdcPoint();
			//	//var py = new ZdcPoint();
			//	//px = new ZdcPoint(p.mx+1000,p.my,<?PHP echo $D_PFLG; ?>);//+1000�ʤΤ��ͤ���������NaN�ˤʤ뤿��
			//	//py = new ZdcPoint(p.mx,p.my+1000,<?PHP echo $D_PFLG; ?>);
			//	//var mx = ZdcEmapGeometricObj.getPoint2PointDistance(p,px);//����1000�ߥ��ä��Ȥε�Υ
			//	//var my = ZdcEmapGeometricObj.getPoint2PointDistance(p,py);//����1000�ߥ��ä��Ȥε�Υ
			//	//mx = 1000 / mx;//1m���Ȥη���
			//	//my = 1000 / my;//1m���Ȥΰ���
			//	//var rx = parseInt(mx * <?PHP echo $D_SHOP_RAD; ?>);//���٤��ϰ�
			//	//var ry = parseInt(my * <?PHP echo $D_SHOP_RAD; ?>);//���٤��ϰ�
			//	var rx = parseInt((450000 / (11 * 1000)) * <?PHP echo $D_SHOP_RAD; ?>);//CGI�ȷ׻��򤢤碌��
			//	var ry = parseInt((300000 / (9 * 1000)) * <?PHP echo $D_SHOP_RAD; ?>);//��
			//	var p1 = new ZdcPoint(p.mx - rx,p.my - ry,<?PHP echo $D_PFLG; ?>);
			//	var p2 = new ZdcPoint(p.mx + rx,p.my + ry,<?PHP echo $D_PFLG; ?>);
			//	var bx = new ZdcBox(p1,p2);
			//	var lv = ZdcEmapMapObj.getMapBoxScale( bx, p );
			//	if(lv < 18) lv = lv + 1;//���ĥ����।��
			//	ZdcEmapMapObj.setMapScale(lv);
			// mod 2011/07/07 H.Osamoto ]
		}
	}
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	ZdcEmapSearchEventStart();
	//�����Ĥ���
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//�������֤��ݻ�
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapSearchPoint = ZdcEmapMapObj.getMapLocation();
	//	ZdcEmapSearchScale = ZdcEmapMapObj.getMapScale();
	ZdcEmapSearchPoint = ZdcEmapMapObj.getLatLon();
	ZdcEmapSearchScale = ZdcEmapMapObj.getZoom();
	// mod 2011/07/07 H.osamoto ]
	ZdcEmapReadOff();
}

//�ꥹ��ɽ��
function ZdcEmapSearchShopListClick(page) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchShopList(page)
}
function ZdcEmapSearchShopList(page) {
	//�ꥹ�Ȥ�ɽ��������
	if(<?PHP echo $D_SHOP_CLOSELIST; ?> && ZdcEmapMapShopDetailMrkId != null) {
		//�ꥹ����ɽ���⡼�ɤǾܺ�ɽ������ȽФ��ʤ�
		ZdcEmapListObj.innerHTML = "";
		return;
	}
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_shop_list.htm?cid=<?PHP echo $cid; ?>"+		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_shop_list.htm?cid=<?PHP echo $cid; ?>"+
			  "&lat="+ZdcEmapNearShop.opts.lat+"&lon="+ZdcEmapNearShop.opts.lon+"&latlon="+ZdcEmapNearShop.opts.latlon+
			  "&radius="+ZdcEmapNearShop.opts.radius+"&jkn="+ZdcEmapNearShop.opts.jkn+"&page="+page;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/06 Y.Matsukawa
	//if(ZdcEmapMapShopDetailMrkId != null) url = url + "&detail=1";//�ܺ�ɽ���ե饰		del 2009/10/13 Y.Matsukawa
	// add 2009/10/13 Y.Matsukawa [
	// �ܺ�ɽ����
	if (ZdcEmapMapShopDetailMrkId != null) {
		// �ܺ�ɽ���ե饰
		url += "&detail=1";
		// �ܺ�ɽ����ε���ID
		// mod 2011/07/07 H.osamoto [
		//	var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		//	if (mrk && mrk.data1) url += "&dkid="+mrk.data1;
		var mrk = ZdcEmapMapShopDetailMrkId;
		if (mrk && mrk.data1) url += "&dkid="+mrk.data1;
		// mod 2011/07/07 H.osamoto ]
	}
	// add 2009/10/13 Y.Matsukawa [
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> list["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
//�ꥹ�Ȥ�������
function ZdcEmapShopClick(id) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	//var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);	mod 2011/07/07 H.osamoto
	var mrk = ZdcEmapMapShopMrkId[id];
	// add 2011/07/07 H.osamoto [
	if (ZdcEmapMapShopMrkId[id].lvl) {
		lvl = ZdcEmapMapShopMrkId[id].lvl;
	} else {
		lvl = "";
	}
	var latlons_id = eval(latlons.length) - eval(id) - 1;
	// add 2011/07/07 H.osamoto ]
	//ɽ������
	//ZdcEmapShopDetailKidClick(mrk.data1,mrk.Point.my,mrk.Point.mx,mrk.data2,mrk.nflg);		mod 2009/09/04 Y.Matsukawa
	//ZdcEmapShopDetailKidClick(ZdcEmapMapShopMrkId[id].id,ZdcEmapMapShopMrkId[id].lat,ZdcEmapMapShopMrkId[id].lon,ZdcEmapMapShopMrkId[id].icon,ZdcEmapMapShopMrkId[id].nflg,ZdcEmapMapShopMrkId[id].lvl);		mod 2011/07/07 H.osamoto
	ZdcEmapShopDetailKidClick(ZdcEmapMapShopMrkId[id].data1,latlons[latlons_id].lat,latlons[latlons_id].lon,ZdcEmapMapShopMrkId[id].data2,ZdcEmapMapShopMrkId[id].nflg,lvl);
}
//�Ǵ󸡺��򱣤�
function ZdcEmapSearchShopClose() {
	ZdcEmapCondObj.innerHTML = "";
	ZdcEmapCondObj.mode = "";
	ZdcEmapListObj.innerHTML = "";
	for( i = 0;i < ZdcEmapMapShopMrkCnt;i ++) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);//�ޡ��������		mod 2011/07/07 H.osamoto
		if (ZdcEmapMapShopMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
			ZdcEmapMapObj.removeWidget(ZdcEmapMapShopMrkId[i]);
			ZdcEmapMapShopMrkId[i] = null;
		}
	}
	ZdcEmapMapShopMrkCnt = 0;
}
var ZdcEmapMapFrontShopMrkId = null;		// add 2009/10/14 Y.Matsukawa
//���ꤵ�줿������������̤ˤ�äƤ���
function ZdcEmapMapFrontShopMrk(id){
	if(ZdcEmapMapShopMrkId[id] != null) {
		//var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);	mod 2011/07/07 H.osamoto
		var mrk = ZdcEmapMapShopMrkId[id];
		// del 2009/10/14 Y.Matsukawa [
		//		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[id]);
		//		ZdcEmapMapShopMrkId[id] = ZdcEmapMapUserLyr.addMarker(mrk);
		//		//���٥�����Ƥʤ���
		//		if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
		//		if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
		//		if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
		// del 2009/10/14 Y.Matsukawa ]
		// add 2009/10/14 Y.Matsukawa [
		ZdcEmapMapFrontShopReset();
		//mrk.setTopZIndex();	mod 2011/07/07 H.Osamoto
		mrk.setZindex(101);
		ZdcEmapMapFrontShopMrkId = ZdcEmapMapShopMrkId[id];
		// add 2009/10/14 Y.Matsukawa ]
	}
}
//�ܺ٥�����������̤ˤ�äƤ���
function ZdcEmapMapFrontShopDetail(){
	var mrk;
	if(ZdcEmapMapShopDetailMrkId != null) {
		//�ե�������
		// del 2009/10/14 Y.Matsukawa [
		//		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapCurFocusMrkId);
		//		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
		//		ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
		//		//��������
		//		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		//		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
		//		ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
		//		//���٥�����Ƥʤ���
		//		if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
		//		if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
		//		if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
		// del 2009/10/14 Y.Matsukawa ]
		// add 2009/10/14 Y.Matsukawa [
		ZdcEmapMapFrontShopReset();
		// mod 2011/07/07 H.osamoto [
		//	mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapCurFocusMrkId);
		//	mrk.setTopZIndex(5);
		//	mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		//	mrk.setTopZIndex();
		mrk = ZdcEmapMapCurFocusMrkId;
		mrk.setZindex(102);
		mrk = ZdcEmapMapShopDetailMrkId;
		mrk.setZindex(101);
		ZdcEmapMapFrontShopMrkId = ZdcEmapMapShopDetailMrkId;
//		ZdcEmapMapFrontShopMrkId = ZdcEmapMapCurFocusMrkId;
		// add 2009/10/14 Y.Matsukawa ]
	}
}
//���̤˻��äƤ�����������򸵤��᤹		add 2009/10/14 Y.Matsukawa
function ZdcEmapMapFrontShopReset() {
	if (ZdcEmapMapFrontShopMrkId != null) {
		// mod 2011/07/07 H.Osamoto [
		//	var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapFrontShopMrkId);
		//	if (mrk) mrk.setDefaultZIndex();
		var mrk = ZdcEmapMapFrontShopMrkId;
		if (mrk && mrk.b) mrk.setZindex(100);
		// mod 2011/07/07 H.Osamoto ]
		ZdcEmapMapFrontShopMrkId = null;
	}
}

//-------------------------------------------------------------
//�ƾܺ�
//-------------------------------------------------------------
//�ܺ�ɽ��(��������) ������³��
//function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg) {		2007/11/16 mod Y.Matsukawa
//function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove,lvl) {
	ZdcEmapSearchClickFlg = 1;
	if (!lvl) lvl = 0;		// add 2009/09/04 Y.Matsukawa
	//������������
	
	//var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapMove('"+lat+"','"+lon+"','"+ZdcEmapMapObj.getMapScale()+"');"	// mod 2011/07/07 H.Osamoto
	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapMove('"+lat+"','"+lon+"','"+ZdcEmapMapObj.getZoom()+"');"
			//+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa
			+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	ZdcEmapHistorySave();
	//
	//ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg);		2007/11/16 mod Y.Matsukawa
	//ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,nomove);		mod 2009/09/04 Y.Matsukawa
	ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,nomove,lvl);
	if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
	// 2008/10/15 Y.Matsukawa add [
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//�����ʳ��Υ�������򥯥ꥢ
		for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
			//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);	mod 2011/07/07 H.osamoto
			if (ZdcEmapMapPoiMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
				ZdcEmapMapObj.removeWidget(ZdcEmapMapPoiMrkId[i]);
				ZdcEmapMapPoiMrkId[i] = null;
			}
		}
	}
	// 2008/10/15 Y.Matsukawa add ]
}
//�ܺ�ɽ��(��������)
//function ZdcEmapShopDetailKidClick(kid,lat,lon,icnno,nflg) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKidClick(kid,lat,lon,icnno,nflg,lvl) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//�����⡼�ɻ��ϾܺٽФ��ʤ�
	if (!lvl) lvl = 0;		// add 2009/09/04 Y.Matsukawa
	//������������
	// mod 2011/07/07 H.osamoto [
	//	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapObj.setMapScale("+ZdcEmapMapObj.getMapScale()+");"
	//			//+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa
	//			+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapObj.setZoom("+ZdcEmapMapObj.getZoom()+");"
			//+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa
			+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
	// mod 2011/07/07 H.osamoto ]
	if(ZdcEmapDetailObj.innerHTML == "" || ZdcEmapHistoryClickChk()) ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	  else ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	ZdcEmapHistorySave();
	//
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	//ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg);		mod 2009/09/04 Y.Matsukawa
	ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,false,lvl);
	if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
	// 2008/10/15 Y.Matsukawa add [
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//�����ʳ��Υ�������򥯥ꥢ
		for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
			//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);	mod 2011/07/07 H.Osamoto
			if (ZdcEmapMapPoiMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
				ZdcEmapMapObj.removeWidget(ZdcEmapMapPoiMrkId[i]);
				ZdcEmapMapPoiMrkId[i] = null;
			}
		}
		// �Ͽ޾�Υ������볰��		2010/04/23 Y.Matsukawa
		ZdcEmapMapCursorRemove();
	}
	// 2008/10/15 Y.Matsukawa add ]
}
//function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg) {	2007/11/16 mod Y.Matsukawa
//function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,notmove) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,notmove,lvl) {
	var mrk,tmp;
	ZdcEmapSearchEventStop();
	//if(<?PHP echo $D_INIT_LVL_DETAIL; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_DETAIL; ?>);//�̼��ѹ�		del 2009/09/04 Y.Matsukawa
	// add 2009/09/04 Y.Matsukawa [
	if (lvl && lvl != 0) {
		//ZdcEmapMapObj.setMapScale(lvl);	mod 2011/07/07 H.osamoto
		ZdcEmapMapObj.setZoom(lvl);
	} else if(<?PHP echo $D_INIT_LVL_DETAIL; ?> > 0) {
		//ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_DETAIL; ?>);		mod 2011/07/07 H.osamoto
		ZdcEmapMapObj.setZoom(<?PHP echo $D_INIT_LVL_DETAIL; ?> - 1);
	}
	// add 2009/09/04 Y.Matsukawa ]
	//�ܺ٤�ɽ��������
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_shop_detail.htm?cid=<?PHP echo $cid; ?>&kid="+kid;	mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_shop_detail.htm?cid=<?PHP echo $cid; ?>&kid="+kid;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/02/23 Y.Matsukawa
	// add 2009/12/10 Y.Matsukawa [
	//�ʤ���߾��
	cond = ZdcEmapGetCondParm();
	if(cond) url = url + '&'+cond;
	// add 2009/12/10 Y.Matsukawa ]
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> detail["+status+"]";
		ZdcEmapDetailObj.innerHTML = html;
		// add 2009/09/28 Y.Matsukawa [
		var dtl_script = null;
		for(i=1; i<=5; i++) {
			dtl_script = document.getElementById("dtl_script"+i);
			if (dtl_script && dtl_script.innerHTML) eval(dtl_script.innerHTML);
		}
		// add 2009/09/28 Y.Matsukawa ]
<?php	// add 2010/09/13 Y.Matsukawa [
		// �����ܺ�ɽ��������Cookie�˽񤭽Ф�
		if ($D_COOKIE_SHOPDTL_MAX > 0) {
?>
		var knmenc_obj = document.getElementById("ZdcEmapShopNameEnc");
		var knmenc = "";
		if (knmenc_obj) knmenc = knmenc_obj.value;
		ZdcEmapCookieWriteShopDetail('<?PHP echo $cid; ?>', kid, knmenc);
<?php	}
		// add 2010/09/13 Y.Matsukawa ]
?>
<?php	// add 2011/06/16 Y.Matsukawa [ ?>
<?php	// ��������ؿ����������Ƥ�����¹� ?>
		if (typeof ZdcEmapCFAfterShopDetail == 'function') {
			var opts = new ZdcKyotenIdOptions();
			opts.cid = '<?PHP echo $D_CID; ?>'
			opts.kid = kid;
			opts.nolog = true;
			opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
			ZdcEmapKyotenId.opts = opts;
			ZdcEmapKyotenId.search(opts, ZdcEmapCFAfterShopDetailEx);
		}
<?php	// add 2011/06/16 Y.Matsukawa ] ?>
	});
	// mod 2011/07/07 H.osamoto [
	//	//�ե����������������ɽ������
	//	mrk = ZdcEmapMakeMrk(0,lat,lon,
	//						 ZdcEmapIconW['@SEL'],ZdcEmapIconH['@SEL'],0,0,
	//						 ZdcEmapIconOffsetX['@SEL'],ZdcEmapIconOffsetY['@SEL'],0,0,0,0,
	//						 ZdcEmapIconImg['@SEL'],'',
	//						 '','',0,null,null,null);
	//	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
	//	ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	//	mrk.setTopZIndex(3);		// add 2009/10/14 Y.Matsukawa
	//	//�ܺ٥��������ɽ������
	//	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
	//		else tmp = "";
	//	mrk = ZdcEmapMakeMrk(0,lat,lon,
	//						ZdcEmapIconW[icnno],ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
	//						ZdcEmapIconOffsetX[icnno],ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
	//						ZdcEmapIconImg[icnno],tmp,
	//						kid,icnno,nflg,
	//						<?PHP
	//							if($D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(null); }"; 
	//								else echo "null"; 
	//						?>,
	//						<?PHP
	//							if(!$D_KYO_ICON_MO) echo "null"; 
	//							if($D_KYO_ICON_MO) echo "function() { ZdcEmapShopMsg(null); }"; 
	//						?>,
	//						//null		mod 2009/10/14 Y.Matsukawa
	//						<?PHP
	//							// �ޥ���������
	//							if($D_KYO_ICON_MOUT == 1) echo "function() { ZdcEmapShopMsgClose(); }";
	//							else echo "null"; 
	//						?>
	//						);
	//	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
	//	ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	//�ե����������������ɽ������
	mrk = ZdcEmapMakeMrkApi2(0, lat, lon, 
							ZdcEmapIconW['@SEL'], ZdcEmapIconH['@SEL'],0,0,
							ZdcEmapIconOffsetX['@SEL'], ZdcEmapIconOffsetY['@SEL'],0,0,
							ZdcEmapIconImg['@SEL'],'',
							'', '', '', 0, null, null, null
						);
	if(ZdcEmapMapCurMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapCurMrkId);
	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapCurFocusMrkId);
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapCurFocusMrkId = mrk;
	mrk.setZindex(101);
	
	//�ܺ٥��������ɽ������
	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
		else tmp = "";
	mrk = ZdcEmapMakeMrkApi2(0, lat, lon, 
							ZdcEmapIconW[icnno], ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
							ZdcEmapIconOffsetX[icnno], ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],
							ZdcEmapIconImg[icnno],tmp,
							kid, icnno, '', nflg, null, null, lvl
						);
	
	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapShopDetailMrkId = mrk;
	ZdcEmapMapShopDetailMrkId.data1 = kid;
	ZdcEmapMapShopDetailMrkId.lat = lat;
	ZdcEmapMapShopDetailMrkId.lon = lon;
	// mod 2011/07/07 H.osamoto ]
	//ư��⡼�ɤ��ڤ��ؤ�
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//�����ٰܺʳ�����ɽ��
		ZdcEmapSearchEventStop();
		ZdcEmapSearchShopClose();
	} else {
		//�Ǵ����ɽ��
		ZdcEmapSearchEventStart();
	}
	//ZdcEmapMapMove(lat, lon);		2007/11/16 mod Y.Matsukawa
	if (!notmove) ZdcEmapMapMove(lat, lon);
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapMapObj.saveMapLocation();
	var center = new ZDC.LatLon(Number(lat), Number(lon));
	ZdcEmapMapObj.setHome(center);
	// mod 2011/07/07 H.osamoto ]
	//¾�ξ�����Ĥ���
	ZdcEmapShopMsgClose();
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
}
//�����ܺ٤򱣤�
function ZdcEmapShopDetailClose() {
	ZdcEmapDetailObj.innerHTML = "";
	
	if(ZdcEmapMapShopDetailMrkId != null) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);	mod 2011/07/07 H.osamoto
		ZdcEmapMapObj.removeWidget(ZdcEmapMapShopDetailMrkId);
		ZdcEmapMapShopDetailMrkId = null;
	}
	if(ZdcEmapMapCurFocusMrkId != null) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);	mod 2011/07/07 H.osamoto
		ZdcEmapMapObj.removeWidget(ZdcEmapMapCurFocusMrkId);
		ZdcEmapMapCurFocusMrkId = null;
	}
}
//�ܺ�ɽ��(��������Τ�ɽ��)
//function ZdcEmapShopIcon(lat,lon,icnno,nflg) {	// 2011/06/29 mod K.Masuda
function ZdcEmapShopIcon(lat,lon,icnno,nflg,NotMoveFlag) {
	//��Ͽ����Ƥ��ʤ���������ID�ξ��Ͻ������ʤ�
	if (!ZdcEmapIconImg[icnno]) return;
	var mrk;
	//�Ͽް�ư
	// 2011/06/29 mod K.Masuda [
	//ZdcEmapMapMove(lat, lon);
	if( NotMoveFlag == undefined || NotMoveFlag != 1 ){
		ZdcEmapMapMove(lat, lon);
	}
	// 2011/06/29 mod K.Masuda ]
	// 	mod 2011/07/07 H.Osamoto [
	//	ZdcEmapMapObj.saveMapLocation();
	//�ե����������������ɽ������
	//mrk = ZdcEmapMakeMrk(0,lat,lon,
	//					ZdcEmapIconW['@SEL'],ZdcEmapIconH['@SEL'],0,0,
	//					ZdcEmapIconOffsetX['@SEL'],ZdcEmapIconOffsetY['@SEL'],0,0,0,0,
	//					ZdcEmapIconImg['@SEL'],'',
	//					'','',0,null,null,null);
	//if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
	//ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	//mrk.setTopZIndex(3);		// add 2009/10/14 Y.Matsukawa
	////���������ɽ������
	//if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
	//	else tmp = "";
	//mrk = ZdcEmapMakeMrk(0,lat,lon,
	//					ZdcEmapIconW[icnno],ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
	//					ZdcEmapIconOffsetX[icnno],ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
	//					ZdcEmapIconImg[icnno],tmp,
	//					0,icnno,nflg,
	//					null, null,null);
	//if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
	//ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	var center = new ZDC.LatLon(Number(lat), Number(lon));
	ZdcEmapMapObj.setHome(center);
	
	//�ե����������������ɽ������
	mrk = ZdcEmapMakeMrkApi2(0, lat, lon, 
							ZdcEmapIconW['@SEL'], ZdcEmapIconH['@SEL'],0,0,
							ZdcEmapIconOffsetX['@SEL'], ZdcEmapIconOffsetY['@SEL'],0,0,
							ZdcEmapIconImg['@SEL'],'',
							'', '', '', 0, null, null, null
						);
	if(ZdcEmapMapCurMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapCurMrkId);
	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapCurFocusMrkId);
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapCurFocusMrkId = mrk;
	mrk.setZindex(101);
	
	//�ܺ٥��������ɽ������
	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
		else tmp = "";
	mrk = ZdcEmapMakeMrkApi2(0, lat, lon, 
							ZdcEmapIconW[icnno], ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
							ZdcEmapIconOffsetX[icnno], ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],
							ZdcEmapIconImg[icnno],tmp,
							'', icnno, '', nflg, null, null, null
						);
	if (ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapShopDetailMrkId);//ǰ�Τ���
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapShopDetailMrkId = mrk;
		
	latlons = new ZDC.LatLon(lat, lon);
	mrk = new ZDC.Marker(latlons,{
		/* �ޡ����Υ������˹�碌�ư��֤�Ĵ������ */
		offset: new ZDC.Pixel(ZdcEmapIconOffsetX[icnno], ZdcEmapIconOffsetY[icnno]),
		custom: {
			base : {
				src: ZdcEmapIconImg[icnno],
				imgSize: ZDC.WH(ZdcEmapIconW[icnno], ZdcEmapIconH[icnno])
			}
		}
	});
	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapShopDetailMrkId = mrk;
	ZdcEmapMapShopDetailMrkId.lat = lat;
	ZdcEmapMapShopDetailMrkId.lon = lon;
	
	// 	mod 2011/07/07 H.Osamoto ]
}

//function debug1(s) {
//var d = document.getElementById("mapRuleLink");
//d.innerHTML += s;
//}

//�ե�����ɽ��
var userwidgethukidasi;
function ZdcEmapShopMsg(id) {
	if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//�����⡼�ɻ��Ͽ᤭�Ф��Ф��ʤ�
	if(ZdcEmapButtonNG()) return;
	//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") return;//�Ǵ�ؤ���ߤ�Ф��Ƥ���ϽФ��ʤ�	mod 2010/06/16 Y.Matsukawa
	if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") return;//�Ǵ�ؤ���ߤ�Ф��Ƥ���ϽФ��ʤ�
	ZdcEmapShopMsgClose();
	//�̼ܤ��ϰϳ��ʤ�ɽ�����ʤ�
	//	var s = ZdcEmapMapObj.getMapScale();	mod 2011/07/07 H.Osamoto
	var s = ZdcEmapMapObj.getZoom();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//������������̤˽Ф�
	if(id != null) ZdcEmapMapFrontShopMrk(id);
	else ZdcEmapMapFrontShopDetail();
	//�ǥ�����
	// mod 2011/07/07 H.Osamoto [
	<?PHP //echo $D_JSCODE_MSGSHOP; ?>
	
	//	if(id != null) var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
	//	else var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	if(id != null) var obj = ZdcEmapMapShopMrkId[id];
	else var obj = ZdcEmapMapShopDetailMrkId;
	// mod 2011/07/07 H.Osamoto ]
	
	//�ե�������ɽ��������
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>&id="+i+"&kid="+obj.data1;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>&id="+i+"&kid="+obj.data1;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/17 Y.Matsukawa
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> msg["+status+"]";
		// mod 2011/07/07 H.Osamoto [
		//	var node = document.createElement('DIV');
		//	node.innerHTML = html;
		//	obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,1);
		var userwidgethukidasilabel =
		{
			html: html,
			offset: new ZDC.Pixel(0, 0)
		};
		var hukidasilatlon = new ZDC.LatLon(Number(obj.lat), Number(obj.lon));
		userwidgethukidasi = new ZDC.MsgInfo(hukidasilatlon, userwidgethukidasilabel);
		
		ZdcEmapMapObj.addWidget(userwidgethukidasi);
		userwidgethukidasi.open();
		// mod 2011/07/07 H.Osamoto ]
	//});		mod 2009/02/16 Y.Matsukawa
	}, true);
}
//�Ĥ���
function ZdcEmapShopMsgClose() {
	// mod 2011/07/07 H.osamoto [
	//	if (ZdcEmapMapObj.getUserMsgOpenStatus()) {
	//		//ZdcEmapSearchEventStart();		del 2008/10/15 Y.Matsukawa
	//		ZdcEmapMapObj.closeUserMsgWindow();
	//	}
	if (userwidgethukidasi) {
		userwidgethukidasi.close();
		userwidgethukidasi = null;
	}
	// mod 2011/07/07 H.osamoto ]
	ZdcEmapMapFrontShopReset();		// add 2009/10/14 Y.Matsukawa
	ZdcEmapTipsClose();//TIPS��Ĥ��Ǥ��Ĥ���
}

//�������̳���
function ZdcEmapShopPrintClick(id) {
	if(ZdcEmapButtonNG()) return;
	//window.open = "<?PHP echo $D_DIR_BASE; ?>print.htm?cid=<?PHP echo $cid; ?>&kid="+id;		mod 2010/07/20 Y.Matsukawa
	window.open = "<?PHP echo $D_DIR_BASE_G; ?>print.htm?cid=<?PHP echo $cid; ?>&kid="+id;
}
//�ܺ٤κǴ���߸���
function ZdcEmapShopDetailNpoiClick() {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapMapShopDetailMrkId == null) return;
	//�Ǵ�������������
	ZdcEmapSearchEventStop();
	//�ܺ٤˰�ư
	var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapMove(obj.Point.my, obj.Point.mx);
	//�Ǵ���߸���
	ZdcEmapPoiClick(1);
}

// add 2011/06/16 Y.Matsukawa
function ZdcEmapCFAfterShopDetailEx(result) {
	if (typeof ZdcEmapCFAfterShopDetail == 'function') {
		ZdcEmapCFAfterShopDetail(result.item);
	}
}

//-------------------------------------------------------------
//�Ǵ�ظ���
//-------------------------------------------------------------
// mod 2011/07/07 H.Osamoto [
//	<?php if($D_REQ_JSAPI["neki"]){ ?>	// 2008/10/22 Y.Matsukawa add
//	var ZdcEmapNeki = new ZdcNearStation();
//	ZdcEvent.addListener(ZdcEmapNeki, "end", ZdcEmapStationResult);
//	<?php } ?>
<?php if(isset($D_REQ_JSAPI_V20["search"]) && $D_REQ_JSAPI_V20["search"]){ // mod 2011/10/03 Y.Nakajima?>
var ZdcEmapNekiLat;
var ZdcEmapNekiLon;

<?php } ?>
// mod 2011/07/07 H.Osamoto ]
//�ظ�������
function ZdcEmapStationClick(lat,lon) {
	if(ZdcEmapButtonNG()) return;
	<?php	// add 2011/06/27 H.osamoto [ ?>
	<?php	// ��������ؿ����������Ƥ�����¹� ?>
		if (typeof ZdcEmapCFBeforeStationClick == 'function') {
			ZdcEmapCFBeforeStationClick();
		}
	<?php	// add 2011/06/27 H.osamoto ] ?>
	ZdcEmapPoiRouteClear();
	// 2007/11/28 mod Y.Matsukawa ��ZdcEmapShopMsgClose�����SearchEventStart���Ƥ��ޤäƤ���Τǡ����������ؤ��ޤ���
	//	ZdcEmapSearchEventStop();
	//	ZdcEmapShopMsgClose();
	ZdcEmapShopMsgClose();
	ZdcEmapSearchEventStop();
	//
	ZdcEmapStation(lat,lon);
	//���̤��ڤ��ؤ���
	if(ZdcEmapCondObj.mode != "eki") {
		ZdcEmapSearchShopClose();
		ZdcEmapCondObj.innerHTML = "";
		//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");	mod 2010/06/16 Y.Matsukawa
		if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");
			else ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");
		ZdcEmapHistorySave();
		ZdcEmapCondObj.mode = "eki";
		ZdcEmapCondObj.style.visibility = "hidden";
	}
}
//�ظ����ᥤ�����
function ZdcEmapStation(lat,lon) {
	ZdcEmapReadOn();
	//
	
	// mod 2011/07/07 H.osamoto [
	//	opts = new ZdcNearStationOptions(opts);
	//	opts.startPos = 1;
	//	opts.maxCount =  <?PHP echo $D_ST_MAX; ?>;
	//	if(lat && lon) {
	//		opts.lat = lat;
	//		opts.lon = lon;
	//	} else {
	//		var p   = new ZdcPoint();
	//		p = ZdcEmapMapObj.getMapLocation();
	//		opts.lat = p.my;
	//		opts.lon = p.mx;
	//		opts.lat = p.my;
	//		opts.lon = p.mx;
	//	}
	//	opts.limitCount = <?PHP echo $D_ST_MAX; ?>;
	//	opts.radius = <?PHP echo $D_ST_RAD; ?>;
	//	opts.pointFlg = <?PHP echo $D_PFLG; ?>;
	//	opts.lang = '<?PHP echo $D_EKI_LANG; ?>';	// add 2008/08/22 Y.Matsukawa
	//	
	//	ZdcEmapNeki.opts = opts;
	//
	//	//�ꥹ�Ȥ�ɽ������
	//	ZdcEmapStationList(0);
	//	//����������������
	//	ZdcEmapNeki.search(opts);
	var result;
	
	if (lat && lon){
		tmplatlon = new ZDC.LatLon(Number(lat), Number(lon));
	} else {
		tmplatlon = ZdcEmapMapObj.getLatLon();
	}
	
	ZdcEmapNekiLat = tmplatlon.lat;
	ZdcEmapNekiLon = tmplatlon.lon;
	
	var ival = {
		latlon: tmplatlon,
		radius: <?PHP echo $D_ST_RAD; ?>,
		datum: "<?PHP echo $D_DATUM; ?>",
		limit: "0"+","+"<?PHP echo $D_ST_MAX; ?>"
	};
	
	ZDC.Search.getStationByLatLon(ival, function(stt, res){
		ZdcGetNearStationResult(stt, res);
	});
	// mod 2011/07/07 H.osamoto ]
}

function ZdcGetNearStationResult(stt, res) {

	//�ꥹ�Ȥ�ɽ������
	ZdcEmapStationList(0);
	
	//����������������
	ZdcEmapStationResult(stt, res);
}

//��������
//function ZdcEmapStationResult(result) {		mod 2011/07/07 H.Osamoto
function ZdcEmapStationResult(status, result) {
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//���顼����
	// mod 2011/07/07 H.osamoto [
	//	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
	//		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> ekires["+result.status+"]");
	//		ZdcEmapSearchEventStart();
	//		ZdcEmapListObj.innerHTML = "";
	//		ZdcEmapReadOff();
	//		return;
	//	}
	if(status.code != "000" || status.text != "ok") {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> ekires["+status.code+","+status.text+"]");
		ZdcEmapSearchEventStart();
		ZdcEmapListObj.innerHTML = "";
		ZdcEmapReadOff();
		return;
	}
	// mod 2011/07/07 H.osamoto ]
	//�Ͽޤ��֤�
	//var i,item,mrk,maxlat=ZdcEmapNeki.opts.lat,maxlon=ZdcEmapNeki.opts.lon,minlat=maxlat,minlon=maxlon;	mod 2011/07/07 H.osamoto
	var i,item,mrk,maxlat=ZdcEmapNekiLat,maxlon=ZdcEmapNekiLon,minlat=maxlat,minlon=maxlon;
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//�ޡ��������		mod 2011/07/07 H.Osamoto
		if (ZdcEmapMapPoiMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
			ZdcEmapMapObj.removeWidget(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
	}
	ZdcEmapMapPoiMrkCnt = 0;
	// mod 2011/07/07 H.osamoto [
	//	for( i in result.items ){
	//		item = result.items[i];
	//		//��������κ���
	//		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
	//							<?PHP echo $D_ICON_EKI_W; ?>,<?PHP echo $D_ICON_EKI_H; ?>,0,0,
	//							<?PHP echo $D_ICON_EKI_OFFSET_X; ?>,<?PHP echo $D_ICON_EKI_OFFSET_Y; ?>,0,0,0,0,
	//							'<?PHP echo $D_ICON_EKI_IMAGE; ?>',item.icons,
	//							item.stationName,"",0,
	//							function() { ZdcEmapRouteSearch('<?PHP echo $D_USER_DEFNAME; ?>',ZdcEmapNeki.opts.lon,ZdcEmapNeki.opts.lat,this.data,this.Point.mx,this.Point.my) },
	//							function() { ZdcEmapTipsClick(this.id); },null);
	//		if (ZdcEmapMapPoiMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//ǰ�Τ���
	//		ZdcEmapMapPoiMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);
	//		//����Ǿ����ٷ��ټ���
	//		if(item.lat > maxlat) maxlat = item.lat;
	//		if(item.lon > maxlon) maxlon = item.lon;
	//		if(item.lat < minlat) minlat = item.lat;
	//		if(item.lon < minlon) minlon = item.lon;
	//		ZdcEmapMapPoiMrkCnt ++;
	//	}
	//	if (ZdcEmapMapPoiMrkCnt > 0) {
	//		ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,new ZdcPoint(ZdcEmapNeki.opts.lon, ZdcEmapNeki.opts.lat, <?PHP echo $D_PFLG; ?>));
	//	}
	for( i in result.item ){
		item = result.item[i];
		//��������κ���
		mrk = ZdcEmapMakeMrkApi2(i,item.poi.latlon.lat,item.poi.latlon.lon,
							<?PHP echo $D_ICON_EKI_W; ?>,<?PHP echo $D_ICON_EKI_H; ?>,0,0,
							<?PHP echo $D_ICON_EKI_OFFSET_X; ?>,<?PHP echo $D_ICON_EKI_OFFSET_Y; ?>,0,0,
							'<?PHP echo $D_ICON_EKI_IMAGE; ?>','',
							item.icons, '', item.poi.text, 0,
							function() { ZdcEmapRouteSearchApi2(this.id) },
							function() { ZdcEmapTipsClick(this.id); },null);
		if (ZdcEmapMapPoiMrkId[i] != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapPoiMrkId[i]);//ǰ�Τ���
		ZdcEmapMapObj.addWidget(mrk);
		ZdcEmapMapPoiMrkId[i] = mrk;
		ZdcEmapMapPoiMrkId[i].lat = item.poi.latlon.lat;
		ZdcEmapMapPoiMrkId[i].lon = item.poi.latlon.lon;
		ZdcEmapMapPoiMrkId[i].message = item.poi.text;
		//����Ǿ����ٷ��ټ���
		if(item.poi.latlon.lat > maxlat) maxlat = item.poi.latlon.lat;
		if(item.poi.latlon.lon > maxlon) maxlon = item.poi.latlon.lon;
		if(item.poi.latlon.lat < minlat) minlat = item.poi.latlon.lat;
		if(item.poi.latlon.lon < minlon) minlon = item.poi.latlon.lon;
		ZdcEmapMapPoiMrkCnt ++;
	}
	if (ZdcEmapMapPoiMrkCnt > 0) {
		var center_latlon = new ZDC.LatLon(Number(ZdcEmapMapShopDetailMrkId.lat), Number(ZdcEmapMapShopDetailMrkId.lon));
		
		var latdist;
		var londist;
		var varminlat;
		var varminlon;
		var varmaxlat;
		var varmaxlon;
		var varlatlon_box = new Array();
		
		// �Ǥ�Υ�줿lat�κ�ʬ
		var minlatdist = Math.abs(minlat - center_latlon.lat);
		var maxlatdist = Math.abs(maxlat - center_latlon.lat);
		if (minlatdist > maxlatdist) {
			latdist = minlatdist;
		} else {
			latdist = maxlatdist;
		}
		
		// �Ǥ�Υ�줿lon�κ�ʬ
		var minlondist = Math.abs(minlon - center_latlon.lon);
		var maxlondist = Math.abs(maxlon - center_latlon.lon);
		if (minlondist > maxlondist) {
			londist = minlondist;
		} else {
			londist = maxlondist;
		}
		
		varminlat = center_latlon.lat - latdist;
		varminlon = center_latlon.lon - londist;
		varmaxlat = center_latlon.lat + latdist;
		varmaxlon = center_latlon.lon + londist;
		
		// �Ͽ�ɽ���̼ܼ����Ѳ���ɽ�����ꥢ
		varlatlon_box[0] = new ZDC.LatLon(varminlat, varminlon);
		varlatlon_box[1] = new ZDC.LatLon(varmaxlat, varmaxlon);
		
		var adjust = ZdcEmapMapObj.getAdjustZoom(varlatlon_box);
		
		ZdcEmapMapObj.moveLatLon(center_latlon)
		ZdcEmapMapObj.setZoom(adjust.zoom);
	}
	// mod 2011/07/07 H.osamoto ]
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	ZdcEmapReadOff();
}
//�ꥹ��ɽ��
function ZdcEmapStationListClick(page) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapStationList(page)
}
function ZdcEmapStationList(page) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_neki.htm?cid=<?PHP echo $cid; ?>"+		mod 2011/02/09 Y.Matsukawa
	// mod 2011/07/07 H.osamoto [
	//	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_neki.htm?cid=<?PHP echo $cid; ?>"+
	//			  "&lat="+ZdcEmapNeki.opts.lat+"&lon="+ZdcEmapNeki.opts.lon+"&page="+page;
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_neki.htm?cid=<?PHP echo $cid; ?>"+
			  "&lat="+ZdcEmapNekiLat+"&lon="+ZdcEmapNekiLon+"&page="+page;
	// mod 2011/07/07 H.osamoto ]
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> eki["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}

<?php
// add 2010/06/16 Y.Matsukawa
//-------------------------------------------------------------
// ��ȯ�Ϥ���ꤷ�ƥ롼��õ��
//-------------------------------------------------------------
?>
// ��ȯ�Ϥ���ꤷ�ƥ롼��õ���⡼�ɳ���
function ZdcEmapFreeRouteClick(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	<?php	// add 2011/06/27 H.osamoto [ ?>
	<?php	// ��������ؿ����������Ƥ�����¹� ?>
		if (typeof ZdcEmapCFBeforeRouteClick == 'function') {
			ZdcEmapCFBeforeRouteClick();
		}
	<?php	// add 2011/06/27 H.osamoto ] ?>
	//�����ʳ��Υ�������򥯥ꥢ
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);	mod 2011/07/07 H.Osamoto
		if (ZdcEmapMapPoiMrkId[i]) {		<?php // add 2012/03/16 H.Osamoto ?>  
			ZdcEmapMapObj.removeWidget(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
	}
	ZdcEmapPoiRouteClear();		// �롼�ȥ��ꥢ
	ZdcEmapShopMsgClose();		// �᤭�Ф��õ�
	ZdcEmapSearchEventStop();	// �������٥�����
	// ���̤��ڤ��ؤ���
	if(ZdcEmapCondObj.mode != "froute") {
		ZdcEmapSearchShopClose();
		ZdcEmapCondObj.innerHTML = "";
		if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");
		else ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["FRoute"] ?>","");
		ZdcEmapHistorySave();
		ZdcEmapCondObj.mode = "froute";
		ZdcEmapCondObj.style.visibility = "hidden";
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
				+"&lat="+lat+"&lon="+lon+"&mode=init"
				+"&<?php echo $P_FREEPARAMS; ?>"
		;
		<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		if (ZdcEmapFRouteInitStr) url += "&frouteinit="+ZdcEmapFRouteInitStr;	<?php // add 2011/02/16 Y.Matsukawa ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
			ZdcEmapListObj.innerHTML = html;
		});
	}
}
// ��ȯ�Ϥ���ꤷ�ƥ롼��õ���⡼�ɳ��ϡ�Light��Maplink��		add 2010/09/07 Y.Matsukawa
function ZdcEmapFreeRouteClickLight(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	//�����ʳ��Υ�������򥯥ꥢ
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapPoiRouteClear();		// �롼�ȥ��ꥢ
	ZdcEmapShopMsgClose();		// �᤭�Ф��õ�
	ZdcEmapSearchEventStop();	// �������٥�����
	// ���̤��ڤ��ؤ���
	ZdcEmapSearchShopClose();
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
			+"&lat="+lat+"&lon="+lon+"&mode=init"
			+"&<?php echo $P_FREEPARAMS; ?>"
	;
	<?php if($https_req){ ?>url += "&https_req=1";<?php } ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// �롼��ɽ��
function ZdcEmapFreeRouteDraw(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	// �Ͽ��濴���֤����
	// mod 2011/07/07 H.osamoto [
	//	var center = ZdcEmapMapObj.getMapLocation();
	//	var mx = center.mx;
	//	var my = center.my;
	var center = ZdcEmapMapObj.getLatLon();
	var mx = center.lon;
	var my = center.lat;
	// mod 2011/07/07 H.osamoto ]
	
	// �롼������
	ZdcEmapRouteSearch("<?php echo $D_USER_DEFNAME; ?>", lon, lat, "�Ͽ��濴", mx, my);
	<?php // add 2010/09/07 Y.Matsukawa [ ?>
	<?php if (isset($D_FROUTE_CLOSE) && $D_FROUTE_CLOSE) { // mod 2011/10/03 Y.Nakajima ?>
	ZdcEmapFreeRouteClose();
	<?php } ?>
	<?php // add 2010/09/07 Y.Matsukawa ] ?>
}
<?php // add 2010/09/07 Y.Matsukawa [ ?>
// ��ȯ�ϻ���롼��õ�����Ĥ���
function ZdcEmapFreeRouteClose() {
	ZdcEmapListObj.innerHTML = '';
}
<?php // add 2010/09/07 Y.Matsukawa ] ?>
// �ե꡼��ɸ���
function ZdcEmapFreeRouteSearch(lat, lon) {
	var txt = document.getElementById("freeRouteSearchEntText");
	if (!txt || !txt.value) return;
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
			+"&lat="+lat+"&lon="+lon+"&mode=srch"
			+"&keyword="+txt.value
			+"&<?php echo $P_FREEPARAMS; ?>"
	;
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// �ե꡼��ɸ����ʥڡ��������
function ZdcEmapFreeRoutePage(lat, lon, page, type, keyword) {
	if (!page) page = 0;
	if (!type) type = "";
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
			+"&lat="+lat+"&lon="+lon+"&mode=srch&page="+page+"&type="+type
			+"&keyword="+keyword
			+"&<?php echo $P_FREEPARAMS; ?>"
	;
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// �����ܺ�ɽ��������Cookie�˽񤭽Ф�		add 2010/09/13 Y.Matsukawa
function ZdcEmapCookieWriteShopDetail(cid, kid, knmenc) {
	var save_value = "";
	var new_value = kid+","+knmenc;
	var pc_shopdtl = "";
	var key = "PC_SHOPDTL_"+cid;
	if (!navigator.cookieEnabled) return;
	// Cookie�ɤ߹���
	var ck = document.cookie;
	if (ck != "") {
		cookies = ck.split(";");
		for (i = 0; i < cookies.length; i++) {
			kv = cookies[i].split("=");
			if (kv[0].replace(/^\s+|\s+$/g, "") == key) {
				pc_shopdtl = kv[1].replace(/^\s+|\s+$/g, "");
				break;
			}
		}
		if (pc_shopdtl != "") {
			vals = pc_shopdtl.split(",");
			var max = Math.floor(vals.length/2);
			if (max > <?php echo $D_COOKIE_SHOPDTL_MAX-1; ?>) max = <?php echo $D_COOKIE_SHOPDTL_MAX-1; ?>;
			var oc = 0;
			for (i = 0; i < max*2; i++) {
				if (vals[i*2] != undefined) {
					if (vals[i*2+1] == undefined) vals[i*2+1] = '';
					old_value = vals[i*2]+","+vals[i*2+1];
					if (old_value != new_value) {
						save_value += ","+old_value;
						oc++;
						if (oc >= max) break;
					}
				}
			}
		}
	}
	save_value = new_value + save_value;
	// Cookie�񤭽Ф�
	ZdcEmapWriteCookie(key, save_value, <?php echo $D_COOKIE_SHOPDTL_EXPIRE; ?>);
}
// Cookie�񤭽Ф�
function ZdcEmapWriteCookie(key, value_esc, days) {
	var str = key + "=" + value_esc + ";";
	if (days != 0) {
		var dt = new Date();
		dt.setDate(dt.getDate() + days);
		str += "expires=" + dt.toGMTString() + ";";
	}
	str += "path=/;";
	document.cookie = str;
}

