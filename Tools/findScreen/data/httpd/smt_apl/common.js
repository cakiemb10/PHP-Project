<?PHP
// ------------------------------------------------------------
// javasctipt ���̴ؿ�
// 
// 2011/03/10 Y.Matsukawa	��������
// 2012/07/20 Y.Matsukawa	GPS���顼��å������򥫥����ޥ�����ǽ��
// 2012/09/10 Y.Matsukawa	���Զ�罤����Ǥ�եѥ�᡼���ˡ�&�פ�ޤ��������������Ѥ���ʤ���Ǥ�եѥ�᡼����Ⱦ�ѥ��ڡ������ꤹ��Ⱦä���
// 2015/02/10 Y.Matsukawa	Ź�ޥꥹ�ȸ���TOP
// 2015/05/27 Y.Matsukawa	cond�����ؿ���search.js����common.js�ذܿ����Ͽ޲��̤Ǥ�Ȥ������
// 2015/10/30 N.Wada		�᤭�Ф�ɽ���ݥåץ��å��ɲá��Ͽ޴ط��ʤ�ɽ�������
// 2016/03/09 Y.Matsukawa	Ⱦ�¤���Ѥˤ��롿BOX�ϰϻ�����ǽ�ˤ���
// 2016/03/18 Y.Matsukawa	Ĺ��URL�б��ʥ�ե��顼�����ղä��ʤ���
// 2016/09/28 Y.Matsukawa	POST����
// 2017/01/09 N.Wada		cond�����ؿ���饸���ܥ��󡦥��쥯�ȥܥå������б�
// ------------------------------------------------------------
require_once('/home/emap/src/smt/inc/define.inc');
?>

var ZdcEmapGPSErrMsg="<?php echo $D_MSG_GPS_ERRPRM; ?>";		<?php // add 2012/07/20 Y.Matsukawa ?>

//HTML�ɤ߹�����ajax�̿��ؿ�
<?php //function ZdcEmapHttpRequestHtml(url,func,nowaitmsg) {		mod 2012/09/10 Y.Matsukawa ?>
<?php //function ZdcEmapHttpRequestHtml(url, func, nowaitmsg, typ) {		mod 2016/03/18 Y.Matsukawa ?>
function ZdcEmapHttpRequestHtml(url, func, nowaitmsg, typ, noref) {
//	if(!nowaitmsg) ZdcEmapReadOn();//�ɤ߹�����ե饰on
	if(typ == undefined) typ = 1;		<?php // add 2012/09/10 Y.Matsukawa ?>
	//�̿�����
	var ZdcEmapHttpRequestObj = new ZdcEmapHttpRequest('UTF8', 'UTF8', 1);
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
//		ZdcEmapReadOff();//�ɤ߹�����ե饰off
	//},<?PHP echo $D_AJAX_TIMEOUT; ?>);		mod 2012/09/10 Y.Matsukawa
	<?php //},< ?PHP echo $D_AJAX_TIMEOUT; ? >,typ);		mod 2016/03/18 Y.Matsukawa ?>
	},<?PHP echo $D_AJAX_TIMEOUT; ?>,typ,noref);
}

<?php // add 2015/02/10 Y.Matsukawa ?>
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

<?php
// �ʤ���߾��������jkn��ʸ�����		add 2015/02/10 Y.Matsukawa
?>
function ZdcEmapCommGetCondJkn() {
	var jkn = '';
	var cond = null;
	var arr_cond = new Array();
<?php
if(isset($D_COND_GRP) && count($D_COND_GRP) > 0){
	$i = 0;
	foreach($D_COND_GRP as $gno => $cnolist) {
?>
		arr_cond[<?php echo $i; ?>] = "";
<?php
		foreach($cnolist as $cno) {
?>
	cond = document.getElementById("cond<?php echo $cno; ?>");
	if (cond && (
		(cond.type == "checkbox" && cond.checked) 
		|| (cond.type == "hidden" && cond.value != "")
		)
	) {
		if (arr_cond[<?php echo $i; ?>] != "")
			arr_cond[<?php echo $i; ?>] += " <?php echo $D_COND_ANDOR[$gno]; ?> ";
		arr_cond[<?php echo $i; ?>] += cond.value;
	}
<?php
		}
		$i++;
	}
}
?>
	if (arr_cond.length > 0) {
		for(var i=0; i < arr_cond.length; i++) {
			if (arr_cond[i] && arr_cond[i] != "") {
				if (jkn) jkn += " <?php echo $D_COND_GRP_ANDOR; ?> ";
				jkn += "("+arr_cond[i]+")";
			}
		}
	}
	return jkn;
}

<?php
// add 2015/05/27 Y.Matsukawa ��search.js����ܿ�
// formCond����ʤ���߾��ʥѥ�᡼��ʸ����ˤ����		add 2012/02/21 Y.Matsukawa
?>
<?php //function ZdcEmapGetCondParm() {		mod 2012/09/10 Y.Matsukawa ?>
function ZdcEmapGetCondParm(esc) {
	var form = document.formCond;
	if (!form) return '';
	var condparm = '';
	var chk = null;
<?php
	if($D_COND && count($D_COND) > 0){
		foreach($D_COND as $i => $condinf) {
			if ($condinf['type'] == 'CB') {
?>
	chk = form.cond<?php echo $i; ?>;
	//if (chk && chk.checked) condparm += "&cond<?php echo $i; ?>="+chk.value;		mod 2012/09/10 Y.Matsukawa
	<?php // add 2012/09/10 Y.Matsukawa [ ?>
	<?php //if (chk && chk.checked) {	del 2016/03/09 Y.Matsukawa ?>
	<?php // add 2016/03/09 Y.Matsukawa [ ?>
	if (chk) {
		if ((chk.type == "checkbox" && chk.checked) || (chk.type == "hidden" && chk.value != "")) {
	<?php // add 2016/03/09 Y.Matsukawa ] ?>
			condparm += "&cond<?php echo $i; ?>=";
			if (esc) {
				condparm += encodeURIComponent(chk.value);
			} else {
				condparm += chk.value;
			}
		}
	}
	<?php // add 2012/09/10 Y.Matsukawa ] ?>
	<?php // add 2017/01/09 N.Wada [ ?>
<?php
			} elseif ($condinf['type'] == 'SL') {
?>
	chk = form.cond<?php echo $i; ?>;
	if (chk) {
		if (chk.value != "") {
			condparm += "&cond<?php echo $i; ?>=";
			if (esc) {
				condparm += encodeURIComponent(chk.value);
			} else {
				condparm += chk.value;
			}
		}
	}
	<?php // add 2017/01/09 N.Wada ] ?>
<?php
			}
		}
	}
?>
	return condparm;
}

<?php
// add 2015/05/27 Y.Matsukawa ��search.js����ܿ�
// formCond����ʤ���߾���������ơ�Ǥ��form��hidden�˥��å�		add 2012/02/21 Y.Matsukawa
?>
function ZdcEmapCondGetForm(formTo) {
	var form = document.formCond;
	if (!form) return;
<?php
	if($D_COND && count($D_COND) > 0){
		foreach($D_COND as $i => $condinf) {
			if ($condinf['type'] == 'CB') {
?>
	chk = form.cond<?php echo $i; ?>;
	if (chk && chk.checked) {
		condto = formTo.cond<?php echo $i; ?>;
		if (!condto) {
			condto = document.createElement("input");
			condto.setAttribute("type", "hidden");
			condto.setAttribute("name", "cond<?php echo $i; ?>");
			formTo.appendChild(condto);
		}
		condto.value = chk.value;
	}
	<?php // add 2017/01/09 N.Wada [ ?>
<?php
			} elseif ($condinf['type'] == 'SL') {
?>
	chk = form.cond<?php echo $i; ?>;
	if (chk && chk.value) {
		condto = formTo.cond<?php echo $i; ?>;
		if (!condto) {
			condto = document.createElement("input");
			condto.setAttribute("type", "hidden");
			condto.setAttribute("name", "cond<?php echo $i; ?>");
			formTo.appendChild(condto);
		}
		condto.value = chk.value;
	}
	<?php // add 2017/01/09 N.Wada ] ?>
<?php
			}
		}
	}
?>
}

<?php
// add 2015/10/30 N.Wada
?>
//�ե�����ɽ���ݥåץ��å�
function ZdcEmapShopMsgPop(elm, kid, after_func) {
	var kidprm = "";
	var ary_flg = 0;
	if (Array.isArray(kid)) {
		for (var i=0; i<kid.length; i++) {
			kidprm += "&kid" + i + "=" + kid[i];
		}
		ary_flg = 1;
	} else {
		kidprm += '&kid=' + kid;
	}
	var url = "<?PHP echo $D_DIR_BASE_L; ?>shop_msg.htm?cid=<?PHP echo $cid; ?>"+kidprm;
	url += "<?php echo ($freeparms_enc?'&'.$freeparms_enc:''); ?>";
	<?php if($https_req){ ?>url += "&https_req=1";<?php } ?>
	<?php
	if($_SERVER['HTTP_HOST']){ echo 'url += "&PARENT_HTTP_HOST='.urlencode($_SERVER['HTTP_HOST']).'";'; }
	?>
	elm.innerHTML = "";
	if(ary_flg) ZdcEampVisibleWait();
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(ary_flg) ZdcEampHiddenWait();
		if(typeof after_func === "function") after_func();
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> msg["+status+"]";
		elm.innerHTML = html;
	}, false, 2);
}

<?php // �ǥХå����󥽡����ɤ�		add 2016/04/14 Y.Matsukawa ?>
function ZdcEmapConsole(str, ow) {
	var con = document.getElementById("DebugConsole");
	if (!con) return;
	if (ow) con.innerHTML = "";
	con.innerHTML += str+"<br>";
}

<?php // POST����		add 2016/09/28 Y.Matsukawa ?>
function ZdcEmapSubmitPOST(url) {
	var parms = new Array();
	var ue = url.split('?');
	if (ue[1]) {
		parms = ue[1].split('&');
	}
	var form = document.createElement('form');
	form.action = ue[0];
	form.method = 'POST';
	if (parms && parms.length > 0) {
		for (var i = 0; i < parms.length; i++) {
			if (parms[i]) {
				var kv = parms[i].split('=');
				var p = document.createElement('input');
				p.type = 'hidden';
				p.name = kv[0];
				p.value = kv[1];
				form.appendChild(p);
			}
		}
	}
	document.body.appendChild(form);
	form.submit();
}
