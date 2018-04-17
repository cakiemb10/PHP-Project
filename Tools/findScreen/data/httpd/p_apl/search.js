<?PHP
// ------------------------------------------------------------
// javasctipt 主に検索に関係するもの
// 
// 2011/10/15 Y.Matsukawa	新規作成
// 2012/03/01 Y.Matsukawa	【不具合修正】フリーワード「表」文字化け対応
// 2014/02/05 Y.Matsukawa	クロスサイトスクリプティング対策
// 2015/02/16 F.Yokoi		input type=textの値を絞り込み条件に設定する処理の追加
// 2015/03/18 Y.Matsukawa	nmapフリーワード検索対応
// 2015/09/25 H.Yasunaga	cond条件セット時に一旦条件用のタグを削除
// 2015/10/20 N.Wada		検索結果をajaxで表示
// 2015/11/19 Y.Matsukawa	検索ウィンドウに「検索中」表示
// 2016/02/03 N.Wada		現在地取得の前処理、後処理
// 2016/02/03 N.Wada		TOP現在地取得の絞り込み条件取得
// 2016/06/28 Y.Uesugi		SEO対策 動的URLを静的URLへ
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');		// add 2014/02/05 Y.Matsukawa
?>

var ZdcEmapGPSCondParams="";		<?php // add 2012/05/23 Y.Matsukawa ?>

// 検索TOP：cond条件セット
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

// 任意パラメータセット
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

// 検索TOP：地域図検索実行
function ZdcEmapSubmitArea(frm, area, frm_c) {
	if(!frm) return;
	if(!area) return;
	frm.area.value = area;
	if (frm_c) ZdcEmapSetCond(frm, frm_c);
	ZdcEmapSetFreeParams(frm);
	frm.submit();
}

<?php // add 20160628 Y.Uesugi [ ?>;
// 検索TOP：地域図検索実行
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

// 検索TOP：路線図検索実行
function ZdcEmapSubmitRail(frm, area, frm_c) {
	if(!frm) return;
	if(!area) return;
	frm.area.value = area;
	if (frm_c) ZdcEmapSetCond(frm, frm_c);
	ZdcEmapSetFreeParams(frm);
	frm.submit();
}

<?php	// add 2012/03/01 Y.Matsukawa
// keywordエスケープ
// ※「表」文字化け防止のため、後ろに全角スペースを付加
?>
function ZdcEmapEscapeKeyword(form) {
	if (form.keyword) {
		var kw = form.keyword.value;
		if (kw.substr(kw.length-1) == '　') return;
		form.keyword.value = kw+'　';
	}
}

<?php // add 2015/10/20 N.Wada ?>
//検索結果ajax表示
var ZdcEmapSearchTopPopObj;
function ZdcEmapSearchTopResultAjax(form) {
	ZdcEmapSearchTopPopObj = document.getElementById('ZdcEmapSearchTopPop');
	if(!ZdcEmapSearchTopPopObj) ZdcEmapSearchTopPopObj = document.createElement('DIV');//light用ダミー

	<?php //ZdcEmapSearchTopPopObj.innerHTML = "";		mod 2015/11/19 Y.Matsukawa ?>
	ZdcEmapSearchTopPopObj.innerHTML = '<?php echo $D_SEARCHWIN_WAIT_HTML; ?>';

	//検索条件
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
		c.innerHTML = "現在地を取得中...";
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
// TOP現在地取得の絞り込み条件取得		add 2016/02/03 N.Wada
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
