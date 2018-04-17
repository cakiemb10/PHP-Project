<?PHP
// ------------------------------------------------------------
// javasctipt 共通関数
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2012/07/20 Y.Matsukawa	GPSエラーメッセージをカスタマイズ可能に
// 2012/09/10 Y.Matsukawa	【不具合修正】任意パラメータに「&」を含めると正しく引き継がれない、任意パラメータに半角スペース指定すると消える
// 2015/02/10 Y.Matsukawa	店舗リスト検索TOP
// 2015/05/27 Y.Matsukawa	cond取得関数をsearch.jsからcommon.jsへ移植（地図画面でも使うため）
// 2015/10/30 N.Wada		吹き出し表示ポップアップ追加（地図関係なく表示する）
// 2016/03/09 Y.Matsukawa	半径を可変にする／BOX範囲指定を可能にする
// 2016/03/18 Y.Matsukawa	長尺URL対応（リファラー等を付加しない）
// 2016/09/28 Y.Matsukawa	POST遷移
// 2017/01/09 N.Wada		cond取得関数をラジオボタン・セレクトボックスに対応
// ------------------------------------------------------------
require_once('/home/emap/src/smt/inc/define.inc');
?>

var ZdcEmapGPSErrMsg="<?php echo $D_MSG_GPS_ERRPRM; ?>";		<?php // add 2012/07/20 Y.Matsukawa ?>

//HTML読み込み用ajax通信関数
<?php //function ZdcEmapHttpRequestHtml(url,func,nowaitmsg) {		mod 2012/09/10 Y.Matsukawa ?>
<?php //function ZdcEmapHttpRequestHtml(url, func, nowaitmsg, typ) {		mod 2016/03/18 Y.Matsukawa ?>
function ZdcEmapHttpRequestHtml(url, func, nowaitmsg, typ, noref) {
//	if(!nowaitmsg) ZdcEmapReadOn();//読み込み中フラグon
	if(typ == undefined) typ = 1;		<?php // add 2012/09/10 Y.Matsukawa ?>
	//通信処理
	var ZdcEmapHttpRequestObj = new ZdcEmapHttpRequest('UTF8', 'UTF8', 1);
	ZdcEmapHttpRequestObj.request(url, function(html,status) {
		if(status == 3) status = 0;//タイムアウトは無視 連続呼び出し時の動作が安定しないので
		if(status == 9) status = 0;//テンプレートが無い場合に対応
		if(html == null) html = "";//nullは出さない
		if(status == 0) {
			func(html,status);
		} else {
			//エラー処理
			func(html,status);
		}
//		ZdcEmapReadOff();//読み込み中フラグoff
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
			status = 1;		//パラメータエラー
		}else if( retcd.substr(4,4) == '1009' ){
			status = 5;		//該当データなし
		}else if ( errPart == '2' ){
			status = 6;		//認証エラー
		}else if ( errPart == '6' || errPart == '7' || errPart == '8' || errPartStr == '15'){
			status = 2;		//サーバーエラー
		}else{
			status = 9;		//その他エラー
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
// 絞り込み条件を取得（jkn式文字列）		add 2015/02/10 Y.Matsukawa
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
// add 2015/05/27 Y.Matsukawa ※search.jsから移植
// formCondから絞り込み条件（パラメータ文字列）を取得		add 2012/02/21 Y.Matsukawa
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
// add 2015/05/27 Y.Matsukawa ※search.jsから移植
// formCondから絞り込み条件を取得して、任意formのhiddenにセット		add 2012/02/21 Y.Matsukawa
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
//フキダシ表示ポップアップ
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

<?php // デバッグコンソールもどき		add 2016/04/14 Y.Matsukawa ?>
function ZdcEmapConsole(str, ow) {
	var con = document.getElementById("DebugConsole");
	if (!con) return;
	if (ow) con.innerHTML = "";
	con.innerHTML += str+"<br>";
}

<?php // POST送信		add 2016/09/28 Y.Matsukawa ?>
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
