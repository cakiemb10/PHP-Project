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
// 2011/07/06 K.Masuda		�᤭�Ф�ɽ�������Ͽ���˼��ޤ�ʤ��Ȥ��Ͽް�ư���뤫
// 2011/07/05 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/07/19 K.Masuda		�Ťʤꥢ������ν������ɲ�
// 2011/08/23 Y.Matsukawa	�Ͽ���ɽ������
// 2011/11/25 Y.Matsukawa	�ԡ������ǥ��б��ʺǴ��롼�����ѥ⡼�ɡ�
// 2012/06/19 Y.Matsukawa	Ź�޾ܺ�Cookie��¸��ǽ�ɲá�Ǥ�ե����ߥ󥰤���¸�����ꥢ�������ؿ���
// 2012/06/22 Y.Matsukawa	���Զ�罤����Cookie���ꥢ�����¸�ǥ�����ץȥ��顼
// 2012/10/09 Y.Matsukawa	Ź�޾ܺ����ܻ��Υ������ޥ����ؿ��¹�
// 2013/03/10 K.Masuda		cond��type=text�ξ�硢FREE_SRCH�ʳ��λ�����ǽ�ˤ���
// 2013/04/15 H.Osamoto		�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ������������굡ǽ�ɲ�
// 2015/03/23 K.Iwayoshi	���潻ͧ�����Źͽ���б��������ޥ���
// 2016/02/15 Y.Uesugi		���潻ͧ�����Źͽ���б��������ޥ����ʾܺٲ��̤ǹʤ������ɽ����
// 2016/02/18 Y.Matsukawa	�Ǵ�긡���ˤ���Ŭ�Ѥ���cond���������ꥢ�����ˤ���Ŭ�Ѥ���cond
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
// mod 2011/07/05 Y.Nakajima
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
var ZdcEmapIconDt = new Array();	// add 2011/07/19 K.Masuda
var ZdcEmapNearbyShopItem = null;	<?php //�Ǵ��Ź�޾���	add 2011/11/25 Y.Matsukawa ?>
var ZdcEmapSearchFirstCstm = null;	<?php //�ǽ�θ������ݤ��������ޥ����ѥե饰	// add 2013/04/15 H.osamoto ?>
//��������
function ZdcEmapSearchShopClick() {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	ZdcEmapSearchShop();
}
<?php // �롼��õ���⡼�ɻ��κǴ��Ź�޺Ƹ���		add 2011/11/25 Y.Matsukawa ?>
function ZdcEmapFixRouteSearchShopClick() {
	ZdcEmapSearchSet(ZdcEmapRouteStartLat, ZdcEmapRouteStartLon);
}
function ZdcEmapSearchShopStart() {
	if(ZdcEmapMapObj.ZdcEmapMode != "print") ZdcEmapSearchClickFlg = 1;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	//
	<?php if (!isset($D_ROUTE_FIX_MODE) || !$D_ROUTE_FIX_MODE) {	// add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapSearchEventAdd("ZdcEmapSearchShop()");
	<?php } ?>
	ZdcEmapSearchEventStart();
	//�����ʳ��Υ�������򥯥ꥢ
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapMapPoiMrkCnt = 0;

	//���̤��ڤ��ؤ���
	if(ZdcEmapCondObj.mode != "cond") {
		ZdcEmapSearchShopClose();//�����ʳ��Υꥹ�Ȥ�ä�
		//		var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>&";
		//		for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "cond"+i+"="+ZdcEmapSaveCond[i]+"&";//�ʹ����
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		//for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//�ʹ����		mod 2009/11/07 Y.Matsukawa
		for(i = 1;i <= 200;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//�ʹ����
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php //mod 2011/07/05 Y.Nakajima [ ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		<?php //mod 2011/07/05 Y.Nakajima ] ?>
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
	var p   = new ZdcPoint();
	p = ZdcEmapMapObj.getMapLocation();
	var box = ZdcEmapMapObj.getMapBoundBox();
	//�������뤫�ݤ���Ƚ��
	if(ZdcEmapSearchPoint != null) {
		var pix1 = ZdcEmapMapObj.convertPoint2Pixel( ZdcEmapSearchPoint, 2 );
		var pix2 = ZdcEmapMapObj.convertPoint2Pixel( p, 2 );
		if(Math.abs(pix1.x-pix2.x) < <?PHP echo $D_SHOP_SEARCHPIX; ?> && 
		   Math.abs(pix1.y-pix2.y) < <?PHP echo $D_SHOP_SEARCHPIX; ?> &&
		   ZdcEmapSearchScale == ZdcEmapMapObj.getMapScale()) {
			ZdcEmapReadOff();
			return;
		}
	}
	if(ZdcEmapSearchPoint != null && <?PHP echo $D_SHOP_SEARCHPIX; ?> == -1) {
		//��ư�Ƹ������ʤ�
		ZdcEmapReadOff();
		return;
	}
	//��ư�������٥�����
	ZdcEmapSearchEventStop();
	// 2011/06/15 K.Masuda mod [
	//ZdcEmapShopMsgClose();
	<?php //mod 2011/07/05 Y.Nakajima ?>
	if( <?php if(isset($D_HUKIDASHI_SEARCH)){echo "false";}else{echo "true";} ?> ){
		ZdcEmapShopMsgClose();
	}
	// 2011/06/15 K.Masuda mod ]
	//�ʤ���߾�����
	cond = ZdcEmapGetCond();
	//
	var opts = new ZdcNearShopOptions();
	<?php //mod 2011/07/05 Y.Nakajima ] ?>
	opts.cid='<?PHP echo $D_CID; ?>';
	opts.lat = p.my;
	opts.lon = p.mx;
	if(ZdcEmapSearchFirst != 1) {
		opts.latlon = box.miny+","+box.minx+","+box.maxy+","+box.maxx;
		opts.radius = <?PHP echo $D_SHOP_RAD_RE; ?>;
	} else {
		ZdcEmapSearchFirst = 0;
	<?php // add 2013/04/15 H.Osamoto [ ?>
	<?php if (isset($D_RESEARCH_CNT) && $D_RESEARCH_CNT) { ?>
	ZdcEmapSearchFirstCstm = 1;
	opts.researchCount = <?PHP echo $D_RESEARCH_CNT; ?>;
	<?php } ?>
	<?php // add 2013/04/15 H.Osamoto ] ?>
		opts.radius = <?PHP echo $D_SHOP_RAD; ?>;
	}
	<?php
	// add 2016/02/18 Y.Matsukawa [
	if ($D_N_COND != "") { ?>
	if (cond) {
		cond = "("+cond+") AND <?php echo $D_N_COND; ?>";
	} else {
		cond = "<?php echo $D_N_COND; ?>";
	}
	<?php
	}
	// add 2016/02/18 Y.Matsukawa ] ?>
	opts.jkn = cond;
	opts.pos = 1;
	opts.maxCount = <?PHP echo $D_SHOP_MAX; ?>;
	opts.limitCount = <?PHP echo $D_SHOP_MAX; ?>;
	opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
	// add 2009/10/13 Y.Matsukawa [
	<?PHP if ($D_SHOP_LIST_NO_DTLSHOP) { ?>
	if (ZdcEmapMapShopDetailMrkId != null) {
		// �ܺ�ɽ����ε���ID
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		if (mrk && mrk.data1) opts.exceptKid = mrk.data1;
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
						// mod 2013/03/10 K.Masuda [
						//fw[fwcnt] = "FREE_SRCH:FW:"+"'"+obj.value+"'";
						//all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						//fwcnt ++;
						<?php if(isset($D_COND_TEXT) && $D_COND_TEXT){ ?>
						<?php   for($cnt=0;$cnt<count($D_COND_TEXT);$cnt++){ ?>
									if(condno == <?php echo $D_COND_TEXT[$cnt][0]; ?>){
										fw[fwcnt] = <?php echo $D_COND_TEXT[$cnt][1]; ?>;
										all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
										fwcnt ++;
									}
						<?php   } ?>
						<?php } else { ?>
								fw[fwcnt] = "FREE_SRCH:FW:"+"'"+obj.value+"'";
								all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
								fwcnt ++;
						<?php } ?>
						// mod 2013/03/10 K.Masuda ]
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
//mod 2011/07/05 Y.Nakajima
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
	// �Ǵ��Ź��		<?php // add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapNearbyShopItem = null;
	//�ޡ��������
	if(ZdcEmapMapShopMrkCnt != null) {
		for( i = 0;i < ZdcEmapMapShopMrkCnt;i ++) {
			ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);
			ZdcEmapMapShopMrkId[i] = null;
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
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	ZdcEmapRouteShopItems = result.items;
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	ZdcEmapSearchFirstCstm = 0;	<?php //add 2013/04/15 H.osamoto ?>
	//�Ͽޤ��֤�
	//for( i in result.items ){		mod 2009/08/18 Y.Matsukawa
	icnt = result.items.length;
	for (i=icnt-1; i>=0; i--) {
		item = result.items[i];
		ZdcEmapNearbyShopItem = item;		<?php // add 2011/11/25 Y.Matsukawa ?>
		if(!item.icon) break;
		if(item.nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
			else tmp = "";
		// add 2011/04/27 H.Osamoto [
		<?php 
		//mod 2011/07/05 Y.Nakajima
		//if ($D_NEW_ICON_COL) { 
		if (isset($D_NEW_ICON_COL) && $D_NEW_ICON_COL != "") { 
		?>
		if(item.<?PHP echo $D_NEW_ICON_COL; ?> == 1) tmp = ZdcEmapIconImg["@NEW"];
		<?php 
		}
		?>
		// add 2011/04/27 H.Osamoto ]
		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
							ZdcEmapIconW[item.icon],ZdcEmapIconH[item.icon],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
							ZdcEmapIconOffsetX[item.icon],ZdcEmapIconOffsetY[item.icon],ZdcEmapIconW[item.icon]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[item.icon],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
							ZdcEmapIconImg[item.icon],tmp,
							item.id,item.icon,item.nflg,
							<?PHP
								// ����å�
								if($D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(this.id); }"; 
									//else if($D_KYO_ICON_CLK == 2) echo "function() { ZdcEmapShopDetailKidClick(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg); }"; 		mod 2009/09/04 Y.Matsukawa
									else if($D_KYO_ICON_CLK == 2) echo "function() { ZdcEmapShopDetailKidClick(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg,this.lvl); }";
									else if($D_KYO_ICON_CLK == 3) echo "function() { ZdcEmapShopMsgOrDetail(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg,this.lvl,this.id); }";	// add 2011/07/19 K.Masuda
									else echo "null"; 
							?>,
							<?PHP
								// �ޥ��������С�
								if(!$D_KYO_ICON_MO) echo "null"; 
								if($D_KYO_ICON_MO) echo "function() { ZdcEmapShopMsg(this.id); }"; 
							?>,
							//null		mod 2009/10/14 Y.Matsukawa
							<?PHP
								// �ޥ���������
								if($D_KYO_ICON_MOUT == 1) echo "function() { ZdcEmapShopMsgClose(); }";
								else echo "null"; 
							?>
							,item.lvl		// add 2009/09/04 Y.Matsukawa
							);
		if (ZdcEmapMapShopMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);//ǰ�Τ���
		ZdcEmapMapShopMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);

		//����Ǿ����ٷ��ټ���
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		ZdcEmapMapShopMrkCnt ++;
		ZdcEmapIconDt[i] = item.lat + ":" + item.lon + ":" + ZdcEmapIconW[item.icon] + ":" + ZdcEmapIconH[item.icon];	// add 2011/07/19 K.Masuda
	}
	if(ZdcEmapSearchClickFlg) {
		ZdcEmapSearchClickFlg = 0;
		//����������ϲ��̰�ư
		if (ZdcEmapMapShopMrkCnt > 0) {
			//���������ޤ��ϰϤ˰�ư
			ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,ZdcEmapMapObj.getMapLocation(),1);
		//} else {		mod 2010/05/21 Y.Matsukawa
		} else if (!result.options.exceptKid) {
			//����Ⱦ�¤ν̼ܤ˰�ư  �����֤ˤ�ä�getPoint2PointDistance���ͤ��Ѥ�뤿�����׻����Ƥ���
			var p = new ZdcPoint();
			p = ZdcEmapMapObj.getMapLocation();
			//var px = new ZdcPoint();
			//var py = new ZdcPoint();
			//px = new ZdcPoint(p.mx+1000,p.my,<?PHP echo $D_PFLG; ?>);//+1000�ʤΤ��ͤ���������NaN�ˤʤ뤿��
			//py = new ZdcPoint(p.mx,p.my+1000,<?PHP echo $D_PFLG; ?>);
			//var mx = ZdcEmapGeometricObj.getPoint2PointDistance(p,px);//����1000�ߥ��ä��Ȥε�Υ
			//var my = ZdcEmapGeometricObj.getPoint2PointDistance(p,py);//����1000�ߥ��ä��Ȥε�Υ
			//mx = 1000 / mx;//1m���Ȥη���
			//my = 1000 / my;//1m���Ȥΰ���
			//var rx = parseInt(mx * <?PHP echo $D_SHOP_RAD; ?>);//���٤��ϰ�
			//var ry = parseInt(my * <?PHP echo $D_SHOP_RAD; ?>);//���٤��ϰ�
			var rx = parseInt((450000 / (11 * 1000)) * <?PHP echo $D_SHOP_RAD; ?>);//CGI�ȷ׻��򤢤碌��
			var ry = parseInt((300000 / (9 * 1000)) * <?PHP echo $D_SHOP_RAD; ?>);//��
			var p1 = new ZdcPoint(p.mx - rx,p.my - ry,<?PHP echo $D_PFLG; ?>);
			var p2 = new ZdcPoint(p.mx + rx,p.my + ry,<?PHP echo $D_PFLG; ?>);
			var bx = new ZdcBox(p1,p2);
			var lv = ZdcEmapMapObj.getMapBoxScale( bx, p );
			if(lv < 18) lv = lv + 1;//���ĥ����।��
			ZdcEmapMapObj.setMapScale(lv);
		}
	}
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	ZdcEmapSearchEventStart();
	//�����Ĥ���
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//�������֤��ݻ�
	ZdcEmapSearchPoint = ZdcEmapMapObj.getMapLocation();
	ZdcEmapSearchScale = ZdcEmapMapObj.getMapScale();
	ZdcEmapReadOff();

	// �Ťʤꥢ������Ƚ��
	<?php if($D_KYO_ICON_CLK == 3){ ?>
	ZdcEmapIconOverlap(icnt,ZdcEmapSearchScale);	// add 2011/07/19 K.Masuda
	<?php } ?>

	<?php // �롼��õ���⡼��		// add 2011/11/25 Y.Matsukawa ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	if (ZdcEmapNearbyShopItem) {
		// �롼������
		ZdcEmapFixRouteSearch(ZdcEmapNearbyShopItem);
	}
	<?php } ?>
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
	<?php // add 2013/04/15 H.Osamoto [ ?>
	if(ZdcEmapSearchFirstCstm == 1) {
		url += "&first_search=1";
	}
	<?php // add 2013/04/15 H.Osamoto ] ?>
	//if(ZdcEmapMapShopDetailMrkId != null) url = url + "&detail=1";//�ܺ�ɽ���ե饰		del 2009/10/13 Y.Matsukawa
	// add 2009/10/13 Y.Matsukawa [
	// �ܺ�ɽ����
	if (ZdcEmapMapShopDetailMrkId != null) {
		// �ܺ�ɽ���ե饰
		url += "&detail=1";
		// �ܺ�ɽ����ε���ID
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		if (mrk && mrk.data1) url += "&dkid="+mrk.data1;
	}
	// add 2009/10/13 Y.Matsukawa [
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> list["+status+"]";
		ZdcEmapListObj.innerHTML = html;
		
		// add 2015/03/23 K.Iwayoshi [
		// ���̥ܥ����� 
		SMBC_DetailButtonShow(ZdcEmapMapShopDetailMrkId);
		//add 2015/03/23 K.Iwayoshi ]
	});
}
//�ꥹ�Ȥ�������
function ZdcEmapShopClick(id) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
	var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
	//ɽ������
	//ZdcEmapShopDetailKidClick(mrk.data1,mrk.Point.my,mrk.Point.mx,mrk.data2,mrk.nflg);		mod 2009/09/04 Y.Matsukawa
	ZdcEmapShopDetailKidClick(mrk.data1,mrk.Point.my,mrk.Point.mx,mrk.data2,mrk.nflg,mrk.lvl);
	
	//add 2015/03/23 K.Iwayoshi [
	// ���̥ܥ����� 
	SMBC_DetailButtonShow(id);
	//add 2015/03/23 K.Iwayoshi ]	

	//add 2015/03/23 K.Iwayoshi [
	// ��ɽ������ �ե饰��Ω�Ƥ� 
	ShowListButtonFlag = true;
	//add 2015/03/23 K.Iwayoshi ]
}

//add 2015/03/23 K.Iwayoshi [
// ���潻ͧ�� ���̥ܥ���ɽ������ 
ShowListButtonFlag = false;

//���潻ͧ�� ���̥ܥ���ɽ������
function SMBC_DetailButtonShow(kid){
	//���̥ܥ���ɽ������ ���ץ�����SMBC_DETAIL_BUTTON_SHOW_FLAG�ե饰�ˣ��򥻥åȤ��ʤ���ư��ʤ�
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		
		//���̥ܥ���ե饰�μ���
		var id = document.getElementById(kid + "_SHOWFLAG");

		//�ե饰�����å� 1�ξ���ɽ��
		if(id != null && id.getAttribute("flagValue") == 1){
			//ɽ������
			// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������
			//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "";
				eles[i].setAttribute("value" , kid);
			}
		}else if(id != null && id.getAttribute("flagValue") != 1){
			//ɽ������
			// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������
			//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "none";
				eles[i].setAttribute("value" , kid);
			}
		}
		
		//ɽ������
		if(ShowListButtonFlag){
			// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������[
			//var eles = document.getElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "none";
			}
		}else{
			// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������[
			//var eles = document.getElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "";
			}
		}
	}
}
//add 2015/03/23 K.Iwayoshi ]

//�Ǵ󸡺��򱣤�
function ZdcEmapSearchShopClose() {
	ZdcEmapCondObj.innerHTML = "";
	ZdcEmapCondObj.mode = "";
	ZdcEmapListObj.innerHTML = "";
	for( i = 0;i < ZdcEmapMapShopMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);//�ޡ��������
		ZdcEmapMapShopMrkId[i] = null;
	}
	ZdcEmapMapShopMrkCnt = 0;
}
var ZdcEmapMapFrontShopMrkId = null;		// add 2009/10/14 Y.Matsukawa
//���ꤵ�줿������������̤ˤ�äƤ���
function ZdcEmapMapFrontShopMrk(id){
	if(ZdcEmapMapShopMrkId[id] != null) {
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
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
		mrk.setTopZIndex();
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
		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapCurFocusMrkId);
		mrk.setTopZIndex(5);
		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		mrk.setTopZIndex();
		ZdcEmapMapFrontShopMrkId = ZdcEmapMapShopDetailMrkId;
//		ZdcEmapMapFrontShopMrkId = ZdcEmapMapCurFocusMrkId;
		// add 2009/10/14 Y.Matsukawa ]
	}
}
//���̤˻��äƤ�����������򸵤��᤹		add 2009/10/14 Y.Matsukawa
function ZdcEmapMapFrontShopReset() {
	if (ZdcEmapMapFrontShopMrkId != null) {
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapFrontShopMrkId);
		if (mrk) mrk.setDefaultZIndex();
		ZdcEmapMapFrontShopMrkId = null;
	}
}

// ��������νŤʤ�Ƚ��		add 2011/07/19 K.Masuda [
var D_ZOOM = new Array();
var D_ZOOM2PXMS_LAT = new Array();
var D_ZOOM2PXMS_LON = new Array();
D_ZOOM["1"]=89; D_ZOOM2PXMS_LAT["89"]=128836.6013; D_ZOOM2PXMS_LON["89"]=158117.6471;
D_ZOOM["2"]=87; D_ZOOM2PXMS_LAT["87"]=64418.30065; D_ZOOM2PXMS_LON["87"]=79058.82353;
D_ZOOM["3"]=85; D_ZOOM2PXMS_LAT["85"]=28183.00654; D_ZOOM2PXMS_LON["85"]=34588.23529;
D_ZOOM["4"]=82; D_ZOOM2PXMS_LAT["82"]=14954.24837; D_ZOOM2PXMS_LON["82"]=18352.94118;
D_ZOOM["5"]=81; D_ZOOM2PXMS_LAT["81"]=10352.94118; D_ZOOM2PXMS_LON["81"]=12705.88235;
D_ZOOM["6"]=77; D_ZOOM2PXMS_LAT["77"]=5751.633987; D_ZOOM2PXMS_LON["77"]=7058.823529;
D_ZOOM["7"]=72; D_ZOOM2PXMS_LAT["72"]=2588.235294; D_ZOOM2PXMS_LON["72"]=3176.470588;
D_ZOOM["8"]=70; D_ZOOM2PXMS_LAT["70"]=1581.699346; D_ZOOM2PXMS_LON["70"]=1941.176471;
D_ZOOM["9"]=67; D_ZOOM2PXMS_LAT["67"]=1150.326797; D_ZOOM2PXMS_LON["67"]=1411.764706;
D_ZOOM["10"]=62; D_ZOOM2PXMS_LAT["62"]=539.2156863; D_ZOOM2PXMS_LON["62"]=661.7647059;
D_ZOOM["11"]=56; D_ZOOM2PXMS_LAT["56"]=206.6993464; D_ZOOM2PXMS_LON["56"]=253.6764706;
D_ZOOM["12"]=55; D_ZOOM2PXMS_LAT["55"]=152.7777778; D_ZOOM2PXMS_LON["55"]=187.5000000;
D_ZOOM["13"]=52; D_ZOOM2PXMS_LAT["52"]=98.85620915; D_ZOOM2PXMS_LON["52"]=121.3235294;
D_ZOOM["14"]=50; D_ZOOM2PXMS_LAT["50"]=74.14215686; D_ZOOM2PXMS_LON["50"]=90.99264706;
D_ZOOM["15"]=46; D_ZOOM2PXMS_LAT["46"]=47.18137255; D_ZOOM2PXMS_LON["46"]=57.90441176;
D_ZOOM["16"]=44; D_ZOOM2PXMS_LAT["44"]=33.70098039; D_ZOOM2PXMS_LON["44"]=41.36029412;
D_ZOOM["17"]=42; D_ZOOM2PXMS_LAT["42"]=26.96078431; D_ZOOM2PXMS_LON["42"]=33.08823529;
D_ZOOM["18"]=39; D_ZOOM2PXMS_LAT["39"]=15.72712418; D_ZOOM2PXMS_LON["39"]=19.30147059;
var IconGrp = new Array();
function ZdcEmapIconOverlap(icnt,lvl){
	var icdt,ic,tmpic,p1,p2,c1,c2,c3,c4,obj;
	var nlatmin = new Array();
	var nlatmax = new Array();
	var nlonmin = new Array();
	var nlonmax = new Array();
	var ZGobj = new ZdcGeometric();

	for(ic=icnt-1; ic>=0; ic--){
		icdt = ZdcEmapIconDt[ic].split(":");
		// icdt[0] lat:����
		// icdt[1] lon:����
		// icdt[2] w:����������
		// icdt[3] h:���������
		nlatmin[ic] = Math.round(parseInt(icdt[0]) + (D_ZOOM2PXMS_LAT[D_ZOOM[lvl]] * (parseInt(icdt[2]) / 2)));	// �������
		nlonmin[ic] = Math.round(parseInt(icdt[1]) + (D_ZOOM2PXMS_LON[D_ZOOM[lvl]] * (parseInt(icdt[3]) / 2)));	// �������
		nlatmax[ic] = Math.round(parseInt(icdt[0]) - (D_ZOOM2PXMS_LAT[D_ZOOM[lvl]] * (parseInt(icdt[2]) / 2)));	// ��������
		nlonmax[ic] = Math.round(parseInt(icdt[1]) - (D_ZOOM2PXMS_LON[D_ZOOM[lvl]] * (parseInt(icdt[3]) / 2)));	// ��������
	}
	for(ic=icnt-1; ic>=0; ic--){
		// id->kid�Ѵ�
		obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[ic]);
		IconGrp[ic] = obj.data1;
		// �Ťʤ�Ƚ��
		for(tmpic=icnt-1; tmpic>=0; tmpic--){
			if( tmpic == ic){ continue; }	// ��ʬ���ȤϽ���
			// id->kid�Ѵ�
			obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[tmpic]);
			// ������ٷ���
			p1 = new ZdcPoint(nlonmin[ic],nlatmin[ic],<?PHP echo $D_PFLG; ?>);
			p2 = new ZdcPoint(nlonmax[ic],nlatmax[ic],<?PHP echo $D_PFLG; ?>);
			// ��ʬ���ٷ���
			c1 = new ZdcPoint(nlonmin[tmpic],nlatmin[tmpic],<?PHP echo $D_PFLG; ?>);	// ������ٷ���
			c2 = new ZdcPoint(nlonmax[tmpic],nlatmin[tmpic],<?PHP echo $D_PFLG; ?>);	// ������ٷ���
			c3 = new ZdcPoint(nlonmax[tmpic],nlatmax[tmpic],<?PHP echo $D_PFLG; ?>);	// �������ٷ���
			c4 = new ZdcPoint(nlonmin[tmpic],nlatmax[tmpic],<?PHP echo $D_PFLG; ?>);	// �������ٷ���
			// �������ʬ���򺹤��뤫��
			if( ZGobj.isLineCrossRect(c1,c2,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
			if( ZGobj.isLineCrossRect(c2,c3,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
			if( ZGobj.isLineCrossRect(c3,c4,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
			if( ZGobj.isLineCrossRect(c4,c1,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
		}
	}
}
// add 2011/07/19 K.Masuda ]

//-------------------------------------------------------------
//�ƾܺ�
//-------------------------------------------------------------
//�ܺ�ɽ��(��������) ������³��
<?php //function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg) {		2007/11/16 mod Y.Matsukawa ?>
<?php //function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove) {		mod 2009/09/04 Y.Matsukawa ?>
<?php //function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove,lvl) {		mod 2011/08/23 Y.Matsukawa ?>
function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove,lvl,nomap) {

	//add 2015/03/23 K.Iwayoshi [
	// ���̥ܥ���ե饰�μ��� 
	var id = document.getElementById(kid + "_SHOWFLAG");
	//add 2015/03/23 K.Iwayoshi ]	

	//add 2015/03/23 K.Iwayoshi [
	// ��ɽ������ �ե饰��Ω�Ƥ� 
	ShowListButtonFlag = true;
	//add 2015/03/23 K.Iwayoshi ]

	ZdcEmapSearchClickFlg = 1;
	if (!lvl) lvl = 0;		<?php // add 2009/09/04 Y.Matsukawa ?>
	if (!nomap) nomap = 0;	<?php // add 2011/08/23 Y.Matsukawa ?>
	//������������
	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapMove('"+lat+"','"+lon+"','"+ZdcEmapMapObj.getMapScale()+"');"
			<?php //+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa ?>
			<?php //+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";		mod 2011/08/23 Y.Matsukawa ?>
			+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"','"+nomap+"');";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	ZdcEmapHistorySave();
	<?php // add 2012/10/09 Y.Matsukawa [ ?>
	<?php // ��������ؿ����������Ƥ�����¹� ?>
	if (typeof ZdcEmapCFShopDetailKidFirst == 'function') {
		ZdcEmapCFShopDetailKidFirst(kid);
	}
	<?php // add 2012/10/09 Y.Matsukawa ] ?>
	//
	<?php //ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg);		2007/11/16 mod Y.Matsukawa ?>
	<?php //ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,nomove);		mod 2009/09/04 Y.Matsukawa ?>
	<?php // add 2011/08/23 Y.Matsukawa [ ?>
	if (nomap == 1) {
		ZdcEmapShopDetailKidNoMap(kid);
		return;
	} else {
	<?php // add 2011/08/23 Y.Matsukawa ] ?>
		ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,nomove,lvl);
	}
	if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
	// 2008/10/15 Y.Matsukawa add [
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//�����ʳ��Υ�������򥯥ꥢ
		for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
			ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
	}
	// 2008/10/15 Y.Matsukawa add ]
	
	// add 2015/03/23  K.Iwayoshi [
	//���̥ܥ���ɽ������ ���ץ�����SMBC_DETAIL_BUTTON_SHOW_FLAG�ե饰�ˣ��򥻥åȤ��ʤ���ư��ʤ�
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		
		//�ե饰�����å� 1�ξ���ɽ��
		if(id != null && id.getAttribute("flagValue") == 1){
			//ɽ������
			// mod 2015/04/22 H.Yasunaga ���̸ߴ��Ѵؿ��ˤƥ��饹̾����ǥ�����Ȥ��������[
			//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "";
				
				eles[i].setAttribute("value" , kid);
			}
		}
	}
	// add 2015/03/23 K.Iwayoshi ]

	// add 2016/02/15 Y.Uesugi [
	<?php if (isset($D_SHOP_CLOSECOND_DTL) || $D_SHOP_CLOSECOND_DTL != "") { ?>
		//�ʹ�����ɽ���⡼�ɤ�����ɽ���Ȥ���
		ZdcEmapCondObj.mode = "";
		ZdcEmapCondObj.style.visibility = "hidden";
		ZdcEmapCondObj.innerHTML = "";
	<?php } ?>
	// add 2016/02/15 Y.Uesugi ]
}

//�ܺ�ɽ��(��������)
//function ZdcEmapShopDetailKidClick(kid,lat,lon,icnno,nflg) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKidClick(kid,lat,lon,icnno,nflg,lvl) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//�����⡼�ɻ��ϾܺٽФ��ʤ�
	if (!lvl) lvl = 0;		// add 2009/09/04 Y.Matsukawa
	//������������
	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapObj.setMapScale("+ZdcEmapMapObj.getMapScale()+");"
			//+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa
			+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
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
			ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
		// �Ͽ޾�Υ������볰��		2010/04/23 Y.Matsukawa
		ZdcEmapMapCursorRemove();
	}
	// 2008/10/15 Y.Matsukawa add ]
	
	//add 2015/03/23 K.Iwayoshi[
	// ���̥ܥ����� 
	SMBC_DetailButtonShow(kid);
	//add 2015/03/23 K.Iwayoshi ]
	
	//add 2015/03/23 K.Iwayoshi [
	// ��ɽ������ �ե饰��Ω�Ƥ�
	ShowListButtonFlag = true;
	//add 2015/03/23 K.Iwayoshi]

	// add 2016/02/15 Y.Uesugi [
	<?php if (isset($D_SHOP_CLOSECOND_DTL) || $D_SHOP_CLOSECOND_DTL != "") { ?>
		//�ʹ�����ɽ���⡼�ɤ�����ɽ���Ȥ���
		ZdcEmapCondObj.mode = "";
		ZdcEmapCondObj.style.visibility = "hidden";
		ZdcEmapCondObj.innerHTML = "";
	<?php } ?>
	// add 2016/02/15 Y.Uesugi ]
}

// add 2011/07/19 K.Masuda [
function ZdcEmapShopMsgOrDetail(kid,lat,lon,icnno,nflg,lvl,id) {
	for(var j=0; j<IconGrp.length; j++){
		if( IconGrp[j].indexOf(kid) == 0 ){
			var n = IconGrp[j].split(",").length - 1;
			if(n < 1 ){
				// �����ܺ٤�
				if(ZdcEmapButtonNG()) return;
				if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//�����⡼�ɻ��ϾܺٽФ��ʤ�
				if (!lvl) lvl = 0;
				//������������
				var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapObj.setMapScale("+ZdcEmapMapObj.getMapScale()+");"
						+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
				if(ZdcEmapDetailObj.innerHTML == "" || ZdcEmapHistoryClickChk()) ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
				  else ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
			ZdcEmapHistorySave();
				//
				ZdcEmapSearchPoint = null;//ɬ���Ƹ��������뤿��
				ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,false,lvl);
				if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
				if(<?php echo $D_DSP_OTHER_KBN; ?>) {
				//�����ʳ��Υ�������򥯥ꥢ
					for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
						ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
						ZdcEmapMapPoiMrkId[i] = null;
					}
					// �Ͽ޾�Υ������볰��
					ZdcEmapMapCursorRemove();
				}
			} else{
				// �᤭�Ф�ɽ����
				if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//�����⡼�ɻ��Ͽ᤭�Ф��Ф��ʤ�
				if(ZdcEmapButtonNG()) return;
				if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") return;//�Ǵ�ؤ���ߤ�Ф��Ƥ���ϽФ��ʤ�
				ZdcEmapShopMsgClose();
				//�̼ܤ��ϰϳ��ʤ�ɽ�����ʤ�
				var s = ZdcEmapMapObj.getMapScale();
				if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
				//������������̤˽Ф�
				if(id != null) ZdcEmapMapFrontShopMrk(id);
				else ZdcEmapMapFrontShopDetail();
				//�ǥ�����
				<?PHP echo $D_JSCODE_MSGSHOP; ?>

				// ʣ�������硢���Ƥ�kid���Ϥ�
				var kidkosu = IconGrp[j].split(",");
				var kidprm = "";
				for( var k=0; k<kidkosu.length; k++ ){
					if( kidkosu[k] == ""){ continue; }
					kidprm += "&kid" + k + "=" + kidkosu[k];
				}

				if(id != null) var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
				else var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	
				//�ե�������ɽ��������
				var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>"+kidprm;

				url += "&<?php echo $P_FREEPARAMS; ?>";
				<?php if($https_req){ ?>url += "&https_req=1";<?php } ?>
				ZdcEmapHttpRequestHtml(url, function(html,status){
					if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> msg["+status+"]";
					var node = document.createElement('DIV');
					node.innerHTML = html;
					obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,<?PHP echo $D_FUKIDASHI_MOVE; ?>);
				}, true);
			}
			break;
		} else {
			continue;
		}
	}
}
// add 2011/07/19 K.Masuda ]
//function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg) {	2007/11/16 mod Y.Matsukawa
//function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,notmove) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,notmove,lvl) {
	var mrk,tmp;
	ZdcEmapSearchEventStop();
	//if(<?PHP echo $D_INIT_LVL_DETAIL; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_DETAIL; ?>);//�̼��ѹ�		del 2009/09/04 Y.Matsukawa
	// add 2009/09/04 Y.Matsukawa [
	if (lvl && lvl != 0) {
		ZdcEmapMapObj.setMapScale(lvl);
	} else if(<?PHP echo $D_INIT_LVL_DETAIL; ?> > 0) {
		ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_DETAIL; ?>);
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
	<?php // mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
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
		//if ($D_COOKIE_SHOPDTL_MAX > 0) {		mod 2012/06/19 Y.Matsukawa
		if ($D_COOKIE_SHOPDTL_AUTO && $D_COOKIE_SHOPDTL_MAX > 0) {
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
		
		//add 20150323 K.Iwayoshi [
		// ���̥ܥ����� 
		SMBC_DetailButtonShow(kid);
		//add 20150323 K.Iwayoshi ]		

		//add 2015/03/23 K.Iwayoshi [
		//Ź�޾ܺٲ���ñ��ɽ�����γƼ�ܥ������ɽ������ 
		if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
			var data_detail = document.getElementById("SMBC_DETAIL_RUN_FLUG");
			//�ե饰�����å� 1�ξ�����ɽ��
			if(data_detail != null && data_detail.getAttribute("flagValue") == "1"){
				var table_inner = document.getElementById("custDtlInnerTable");
				table_inner.style.display = "none";
			}
		}
		//add 2015/03/23 K.Iwayoshi ]
		
<?php	// add 2011/06/16 Y.Matsukawa ] ?>
	});
	//�ե����������������ɽ������
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						 ZdcEmapIconW['@SEL'],ZdcEmapIconH['@SEL'],0,0,
						 ZdcEmapIconOffsetX['@SEL'],ZdcEmapIconOffsetY['@SEL'],0,0,0,0,
						 ZdcEmapIconImg['@SEL'],'',
						 '','',0,null,null,null);
	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
	ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	mrk.setTopZIndex(3);		// add 2009/10/14 Y.Matsukawa
	//�ܺ٥��������ɽ������
	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
		else tmp = "";
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						ZdcEmapIconW[icnno],ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
						ZdcEmapIconOffsetX[icnno],ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
						ZdcEmapIconImg[icnno],tmp,
						kid,icnno,nflg,
						<?PHP
							// mod 2011/07/05 Y.Nakajima
							if(isset($D_KYO_ICON_CLK) && $D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(null); }"; 
								else echo "null"; 
						?>,
						<?PHP
							if(!$D_KYO_ICON_MO) echo "null"; 
							// mod 2011/07/05 Y.Nakajima
							if($D_KYO_ICON_MO != "") echo "function() { ZdcEmapShopMsg(null); }"; 
						?>,
						//null		mod 2009/10/14 Y.Matsukawa
						<?PHP
							// �ޥ���������
							if($D_KYO_ICON_MOUT == 1) echo "function() { ZdcEmapShopMsgClose(); }";
							else echo "null"; 
						?>
						);
	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
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
	ZdcEmapMapObj.saveMapLocation();
	//¾�ξ�����Ĥ���
	ZdcEmapShopMsgClose();
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();

}
<?php // add 2011/08/23 Y.Matsukawa ?>
<?php // �����ܺ�ɽ�����Ͽ���ɽ���ˢ�����������ɥ������� ?>
function ZdcEmapShopDetailKidNoMap(kid) {
	// �ܺ٤�ɽ��������
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_shop_detail.htm?cid=<?PHP echo $cid; ?>&kid="+kid+"&nomap=1";
	url += "&<?php echo $P_FREEPARAMS; ?>";
	// �ʤ���߾��
	cond = ZdcEmapGetCondParm();
	if(cond) url = url + '&'+cond;
	<?php if($https_req){ ?>url += "&https_req=1";<?php } ?>
	ZdcEmapSearchRequest(url);
}
//�����ܺ٤򱣤�
function ZdcEmapShopDetailClose() {
	ZdcEmapDetailObj.innerHTML = "";
	
	if(ZdcEmapMapShopDetailMrkId != null) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
		ZdcEmapMapShopDetailMrkId = null;
	}
	if(ZdcEmapMapCurFocusMrkId != null) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
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
	ZdcEmapMapObj.saveMapLocation();
	//�ե����������������ɽ������
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						ZdcEmapIconW['@SEL'],ZdcEmapIconH['@SEL'],0,0,
						ZdcEmapIconOffsetX['@SEL'],ZdcEmapIconOffsetY['@SEL'],0,0,0,0,
						ZdcEmapIconImg['@SEL'],'',
						'','',0,null,null,null);
	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
	ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	mrk.setTopZIndex(3);		// add 2009/10/14 Y.Matsukawa
	//���������ɽ������
	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
		else tmp = "";
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						ZdcEmapIconW[icnno],ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
						ZdcEmapIconOffsetX[icnno],ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
						ZdcEmapIconImg[icnno],tmp,
						0,icnno,nflg,
						null, null,null);
	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
}

//function debug1(s) {
//var d = document.getElementById("mapRuleLink");
//d.innerHTML += s;
//}

//�ե�����ɽ��
function ZdcEmapShopMsg(id) {
	if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//�����⡼�ɻ��Ͽ᤭�Ф��Ф��ʤ�
	if(ZdcEmapButtonNG()) return;
	//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") return;//�Ǵ�ؤ���ߤ�Ф��Ƥ���ϽФ��ʤ�	mod 2010/06/16 Y.Matsukawa
	if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") return;//�Ǵ�ؤ���ߤ�Ф��Ƥ���ϽФ��ʤ�
	ZdcEmapShopMsgClose();
	//�̼ܤ��ϰϳ��ʤ�ɽ�����ʤ�
	var s = ZdcEmapMapObj.getMapScale();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//������������̤˽Ф�
	if(id != null) ZdcEmapMapFrontShopMrk(id);
	else ZdcEmapMapFrontShopDetail();
	//�ǥ�����
	<?PHP echo $D_JSCODE_MSGSHOP; ?>
	
	if(id != null) var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
	else var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	
	//�ե�������ɽ��������
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>&id="+i+"&kid="+obj.data1;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>&id="+i+"&kid="+obj.data1;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/17 Y.Matsukawa
	<!-- // mod 2011/07/05 Y.Nakajima -->
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> msg["+status+"]";
		var node = document.createElement('DIV');
		node.innerHTML = html;
		//obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,1);	// mod 2011/07/06 K.Masuda
		<?PHP //add 2011/07/05 Y.Nakajima 
		if (!isset($D_FUKIDASHI_MOVE)) $D_FUKIDASHI_MOVE = 0; ?>
		obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,<?PHP echo $D_FUKIDASHI_MOVE; ?>);
	//});		mod 2009/02/16 Y.Matsukawa
	}, true);
}
//�Ĥ���
function ZdcEmapShopMsgClose() {
	if (ZdcEmapMapObj.getUserMsgOpenStatus()) {
		//ZdcEmapSearchEventStart();		del 2008/10/15 Y.Matsukawa
		ZdcEmapMapObj.closeUserMsgWindow();
	}
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

<?php if(isset($D_REQ_JSAPI["neki"]) && $D_REQ_JSAPI["neki"] != ""){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapNeki = new ZdcNearStation();
ZdcEvent.addListener(ZdcEmapNeki, "end", ZdcEmapStationResult);
<?php } ?>
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
	var opts = new ZdcNearStationOptions();
	opts.startPos = 1;
	opts.maxCount =  <?PHP echo $D_ST_MAX; ?>;
	if(lat && lon) {
		opts.lat = lat;
		opts.lon = lon;
	} else {
		var p   = new ZdcPoint();
		p = ZdcEmapMapObj.getMapLocation();
		opts.lat = p.my;
		opts.lon = p.mx;
	}
	opts.limitCount = <?PHP echo $D_ST_MAX; ?>;
	opts.radius = <?PHP echo $D_ST_RAD; ?>;
	opts.pointFlg = <?PHP echo $D_PFLG; ?>;
	opts.lang = '<?PHP echo $D_EKI_LANG; ?>';	// add 2008/08/22 Y.Matsukawa
	ZdcEmapNeki.opts = opts;
	//�ꥹ�Ȥ�ɽ������
	ZdcEmapStationList(0);
	//����������������
	ZdcEmapNeki.search(opts);
}
//��������
function ZdcEmapStationResult(result) {
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//���顼����
	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> ekires["+result.status+"]");
		ZdcEmapSearchEventStart();
		ZdcEmapListObj.innerHTML = "";
		ZdcEmapReadOff();
		return;
	}
	//�Ͽޤ��֤�
	var i,item,mrk,maxlat=ZdcEmapNeki.opts.lat,maxlon=ZdcEmapNeki.opts.lon,minlat=maxlat,minlon=maxlon;
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//�ޡ��������
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapMapPoiMrkCnt = 0;
	for( i in result.items ){
		item = result.items[i];
		//��������κ���
		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
							<?PHP echo $D_ICON_EKI_W; ?>,<?PHP echo $D_ICON_EKI_H; ?>,0,0,
							<?PHP echo $D_ICON_EKI_OFFSET_X; ?>,<?PHP echo $D_ICON_EKI_OFFSET_Y; ?>,0,0,0,0,
							'<?PHP echo $D_ICON_EKI_IMAGE; ?>',item.icons,
							item.stationName,"",0,
							function() { ZdcEmapRouteSearch('<?PHP echo $D_USER_DEFNAME; ?>',ZdcEmapNeki.opts.lon,ZdcEmapNeki.opts.lat,this.data,this.Point.mx,this.Point.my) },
							function() { ZdcEmapTipsClick(this.id); },null);
		if (ZdcEmapMapPoiMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//ǰ�Τ���
		ZdcEmapMapPoiMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);
		//����Ǿ����ٷ��ټ���
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		ZdcEmapMapPoiMrkCnt ++;
	}
	if (ZdcEmapMapPoiMrkCnt > 0) {
		ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,new ZdcPoint(ZdcEmapNeki.opts.lon, ZdcEmapNeki.opts.lat, <?PHP echo $D_PFLG; ?>));
	}
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
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_neki.htm?cid=<?PHP echo $cid; ?>"+
			  "&lat="+ZdcEmapNeki.opts.lat+"&lon="+ZdcEmapNeki.opts.lon+"&page="+page;
	<!-- // mod 2011/07/05 Y.Nakajima -->
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
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
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
		ZdcEmapMapPoiMrkId[i] = null;
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
		<!-- // mod 2011/07/05 Y.Nakajima -->
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
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
	<!-- // mod 2011/07/05 Y.Nakajima -->
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php } ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// �롼��ɽ��
function ZdcEmapFreeRouteDraw(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	// �Ͽ��濴���֤����
	var center = ZdcEmapMapObj.getMapLocation();
	var mx = center.mx;
	var my = center.my;
	// �롼������
	ZdcEmapRouteSearch("<?php echo $D_USER_DEFNAME; ?>", lon, lat, "�Ͽ��濴", mx, my);
	<?php // add 2010/09/07 Y.Matsukawa [ ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if (isset($D_FROUTE_CLOSE)) { ?>
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
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
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
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
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
				//pc_shopdtl = kv[1].replace(/^\s+|\s+$/g, "");		mod 2012/06/22 Y.Matsukawa
				if (kv[1]) pc_shopdtl = kv[1].replace(/^\s+|\s+$/g, "");
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
<?php // Ź�޾����Cookie��¸		add 2012/06/19 Y.Matsukawa ?>
function ZdcEmapCookieSaveShopDetail(kid) {
<?php	// �����ܺ�ɽ��������Cookie�˽񤭽Ф�
		if ($D_COOKIE_SHOPDTL_MAX > 0) { ?>
	var knmenc_obj = document.getElementById("ZdcEmapShopNameEnc");
	var knmenc = "";
	if (knmenc_obj) knmenc = knmenc_obj.value;
	ZdcEmapCookieWriteShopDetail('<?PHP echo $cid; ?>', kid, knmenc);
<?php	} ?>
}
<?php // Cookie��¸���줿Ź�޾���򥯥ꥢ		add 2012/06/19 Y.Matsukawa ?>
function ZdcEmapCookieClearShopDetail() {
	var key = "PC_SHOPDTL_<?PHP echo $cid; ?>";
	var str = key + "=;";
	str += "path=/;";
	document.cookie = str;
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

