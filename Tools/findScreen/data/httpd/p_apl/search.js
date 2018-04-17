<?PHP
// ------------------------------------------------------------
// javasctipt ��˸����˴ط�������
// 
// 2011/10/15 Y.Matsukawa	��������
// 2012/03/01 Y.Matsukawa	���Զ�罤���ۥե꡼��ɡ�ɽ��ʸ�������б�
// 2014/02/05 Y.Matsukawa	���������ȥ�����ץƥ����к�
// 2015/02/16 F.Yokoi		input type=text���ͤ�ʤ���߾������ꤹ��������ɲ�
// 2015/03/18 Y.Matsukawa	nmap�ե꡼��ɸ����б�
// 2015/09/25 H.Yasunaga	cond��糧�åȻ��˰�ö����ѤΥ�������
// 2015/10/20 N.Wada		������̤�ajax��ɽ��
// 2015/11/19 Y.Matsukawa	����������ɥ��ˡָ������ɽ��
// 2016/02/03 N.Wada		�����ϼ������������������
// 2016/02/03 N.Wada		TOP�����ϼ����ιʤ���߾�����
// 2016/06/28 Y.Uesugi		SEO�к� ưŪURL����ŪURL��
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');		// add 2014/02/05 Y.Matsukawa
?>

var ZdcEmapGPSCondParams="";		<?php // add 2012/05/23 Y.Matsukawa ?>

// ����TOP��cond��糧�å�
<?php //function ZdcEmapSetCond(frm, frm_c) { ?>
function ZdcEmapSetCond(frm, frm_c, htm) {
	if(!frm) return;
	if(!frm_c) return;
	var condfr, condto;
<?php
	if (isset($D_COND) && count($D_COND)) {
		foreach ($D_COND as $i => $condinfo) {
?>
	<?php //condfr = frm_c.scond< ?php echo $i; ? >;		del 2015/03/18 Y.Matsukawa ?>
	<?php // add 2015/03/18 Y.Matsukawa [ ?>
	if (htm=="nmap") {
		condfr = frm_c.cond<?php echo $i; ?>;
	} else {
		condfr = frm_c.scond<?php echo $i; ?>;
	}
	<?php // add 2015/03/18 Y.Matsukawa ] ?>
	condto = frm.cond<?php echo $i; ?>;
	if (condfr) {
		var cond_val = "";
		switch (condfr.type) {
			case "checkbox":
				if(condfr.checked == true) {
					cond_val = condfr.value;
				}
				break;
			case "select-one":
				cond_val = condfr.options[condfr.selectedIndex].value;
				break;
			case "radio":
				if(condfr.checked == true && condfr.value) {
					cond_val = condfr.value;
				}
				break;
			case "hidden":
				cond_val = condfr.value;
				break;
<?php // add 20150216 F.Yokoi [ ?>;
			case "text":
				if(condfr.value != '') {
					cond_val = condfr.value;
				}
				break;
<?php // add 20150216 F.Yokoi ] ?>;
		}
<?php	// add 20150925 H.Yasunaga [ ?>;
		if (condto) {
			frm.removeChild(condto);
			condto = null;
		}
<?php	// add 20150925 H.Yasunaga ] ?>;
		
		if (cond_val != "") {
			if (!condto) {
				condto = document.createElement("input");
				condto.setAttribute("type", "hidden");
				condto.setAttribute("name", "cond<?php echo $i; ?>");
				frm.appendChild(condto);
			}
			condto.value = cond_val;
		}
	}
<?php
		}
	}
?>
}

// Ǥ�եѥ�᡼�����å�
function ZdcEmapSetFreeParams(frm) {
	var hid;
<?php	for ($i=1; $i<=50; $i++) {
			if (isset(${'p_s'.$i})) { ?>
	hid = document.createElement("input");
	hid.setAttribute("type", "hidden");
	hid.setAttribute("name", "p_s<?php echo $i; ?>");
	//hid.setAttribute("value", "<?php echo ${'p_s'.$i}; ?>");		mod 2014/02/05 Y.Matsukawa
	hid.setAttribute("value", "<?php echo ${'p_s'.$i.'_js'}; ?>");
	frm.appendChild(hid);
<?php		} ?>
<?php		if (isset(${'p_f'.$i})) { ?>
	hid = document.createElement("input");
	hid.setAttribute("type", "hidden");
	hid.setAttribute("name", "p_f<?php echo $i; ?>");
	//hid.setAttribute("value", "<?php echo ${'p_f'.$i}; ?>");		mod 2014/02/05 Y.Matsukawa
	hid.setAttribute("value", "<?php echo ${'p_f'.$i.'_js'}; ?>");
	frm.appendChild(hid);
<?php		}
		}
?>
}

// ����TOP���ϰ�޸����¹�
function ZdcEmapSubmitArea(frm, area, frm_c) {
	if(!frm) return;
	if(!area) return;
	frm.area.value = area;
	if (frm_c) ZdcEmapSetCond(frm, frm_c);
	ZdcEmapSetFreeParams(frm);
	frm.submit();
}

<?php // add 20160628 Y.Uesugi [ ?>;
// ����TOP���ϰ�޸����¹�
function ZdcEmapSubmitAreaSEO(frm, area, frm_c) {
	if(!frm) return;
	if(!area) return;
	if (frm_c) ZdcEmapSetCond(frm, frm_c);
	ZdcEmapSetFreeParams(frm);
	var url = "<?PHP echo $D_DIR_BASE_L; ?>"+area+"/";
	frm.action=url;
	frm.submit();
}
<?php // add 20160628 Y.Uesugi ] ?>;

// ����TOP��ϩ���޸����¹�
function ZdcEmapSubmitRail(frm, area, frm_c) {
	if(!frm) return;
	if(!area) return;
	frm.area.value = area;
	if (frm_c) ZdcEmapSetCond(frm, frm_c);
	ZdcEmapSetFreeParams(frm);
	frm.submit();
}

<?php	// add 2012/03/01 Y.Matsukawa
// keyword����������
// ����ɽ��ʸ�������ɻߤΤ��ᡢ�������ѥ��ڡ������ղ�
?>
function ZdcEmapEscapeKeyword(form) {
	if (form.keyword) {
		var kw = form.keyword.value;
		if (kw.substr(kw.length-1) == '��') return;
		form.keyword.value = kw+'��';
	}
}

<?php // add 2015/10/20 N.Wada ?>
//�������ajaxɽ��
var ZdcEmapSearchTopPopObj;
function ZdcEmapSearchTopResultAjax(form) {
	ZdcEmapSearchTopPopObj = document.getElementById('ZdcEmapSearchTopPop');
	if(!ZdcEmapSearchTopPopObj) ZdcEmapSearchTopPopObj = document.createElement('DIV');//light�ѥ��ߡ�

	<?php //ZdcEmapSearchTopPopObj.innerHTML = "";		mod 2015/11/19 Y.Matsukawa ?>
	ZdcEmapSearchTopPopObj.innerHTML = '<?php echo $D_SEARCHWIN_WAIT_HTML; ?>';

	//�������
	var type = form.type.value;
	var keyword, col, area, adcd, page;
	var cond_col = cond_val = cond_param = "";
	switch (type) {
		case "ShopW":
			col = form.col.value;
			keyword = form.keyword.value;
			break;
		case "AddrW":
		case "StW":
		case "ZipW":
		case "Comb":
			keyword = form.keyword.value;
			break;
		case "AddrL":
			area = form.area.value;
			adcd = form.adcd.value;
			break;
		default:
			break;
	}
	if (form.page) page = form.page.value;
	for (var no=1; no<=200; no++) {
		cond_col = "cond"+no;
		if (form[cond_col]) {
			cond_val = form[cond_col].value;
			if (cond_val) cond_param += "&"+cond_col+"="+cond_val;
		}
	}
	var url = "<?PHP echo $D_DIR_BASE_L; ?>search.htm?type="+type;
	if (keyword) url+= "&keyword="+keyword;
	if (col) url+= "&col="+col;
	if (area) url+= "&area="+area;
	if (adcd) url+= "&adcd="+adcd;
	if (page) url+= "&page="+page;
	if (cond_param) url+= cond_param;
	ZdcEmapCmnHttpRequestHtmlAjax(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapSearchTopPopObj.innerHTML = html;
	});
}

<?php // add 2016/02/03 N.Wada [ ?>
function ZdcEmapLocProgress() {
	var c=document.getElementById("ZdcEmapLocCmmt");
	if(c){
		c.innerHTML = "�����Ϥ������...";
	}
}
function ZdcEmapLocFinish() {
	var c=document.getElementById("ZdcEmapLocCmmt");
	if(c){
		c.innerHTML = "";
	}
}
var flt = "";
function GetFilter(){
	if( document.getElementById("gpsfilter").value ){
		flt = document.getElementById("gpsfilter").value;
	} else {
		flt = "";
	}
}
<?php // add 2016/02/03 N.Wada ] ?>

<?php
// TOP�����ϼ����ιʤ���߾�����		add 2016/02/03 N.Wada
?>
function ZdcEmapMakeGPSCondParams(frm) {
	ZdcEmapGPSCondParams = "";
	if (frm.plfilter) {
		if (frm.plfilter.value) {
			ZdcEmapGPSCondParams += "&plfilter="+frm.plfilter.value;
		}
	}
	if (ZdcEmapCond.length > 0) {
		for(var i=0; i < ZdcEmapCond.length; i++) {
			cond = eval("frm.cond"+ZdcEmapCond[i]);
			if (cond) {
				if (cond.value) {
					ZdcEmapGPSCondParams += "&cond"+ZdcEmapCond[i]+"="+cond.value;
				}
			}
		}
	}
}
