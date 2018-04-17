/* デバッグ用：console.logがIEでエラーにならないための記述です（削除可） */
(function () {
	if (typeof window.console === "undefined") {
		 window.console = {}
	}
	if (typeof window.console.log !== "function") {
		 window.console.log = function () {}
	}
})();

/* 入力不可のテキストボックス上でバックスペースキーを押下するとページが戻ってしまうのを抑制しています（※削除不可） */
window.document.onkeydown = keydown;
function keydown(){
	if( window.event.keyCode == 8 && window.event.srcElement.readOnly == true){
		return false;
	}
}

if (!String.prototype.trim) {
/**
 * 文字列の前後の空白を除去します。
 * @return {String} <br>空白を除去した文字列
 */
String.prototype.trim = function() {
    return this.replace(/^[\s　]+|[\s　]+$/g, "");
}
}

/**
 * 要素idを指定してvalueを取得します。
 * @param {String} id 要素のid
 * @return {String} 要素のvalue値
 */
function DmapGetValueById(id) {
	var e = document.getElementById(id);
	if (e) {
		return e.value;
	}
	return "";
}

/**
 * 日付が正しければyyyymmddにフォーマットして返却します。
 * @param {String} ymd 日付文字列（yyyy/m/d）
 * @return {String} 日付文字列（yyyymmdd）
 */
function DmapFormatYmd(ymd){
	var ymd_a = ymd.split("/");
	if(ymd_a.length != 3){
		return '';
	}
	ymd_a[0] = ymd_a[0]*1;
	ymd_a[1] = ymd_a[1]*1;
	ymd_a[2] = ymd_a[2]*1;
	var date = new Date(ymd);
	if ((ymd_a[0]+'/'+ymd_a[1]+'/'+ymd_a[2]) == (date.getFullYear()+'/'+(date.getMonth()+1)+'/'+date.getDate())) {
		if (ymd_a[1] < 10) ymd_a[1] = '0'+ymd_a[1];
		if (ymd_a[2] < 10) ymd_a[2] = '0'+ymd_a[2];
		return ''+ymd_a[0]+ymd_a[1]+ymd_a[2];
	}else{
		return '';
	}
}

/**
 * 現在日付を文字列で返却します。
 * @param {Boolean} time true：時刻を付加する（yyyy/mm/dd hh:nn:ss）／false：時刻を付加しない（yyyy/mm/dd）
 * @return {String} 日付文字列（yyyy/mm/dd）or （yyyy/mm/dd hh:nn:ss）
 */
function DmapGetDate(time) {
	var now = new Date(); 
	var year = now.getFullYear();
	var month = now.getMonth()+1;
	month = ('00'+month).slice(-2);
	var week = now.getDay();
	var day = now.getDate();
	day = ('00'+day).slice(-2);
	var hour = now.getHours();
	hour = ('00'+hour).slice(-2);
	var minute = now.getMinutes();
	minute = ('00'+minute).slice(-2);
	var second = now.getSeconds();
	second = ('00'+second).slice(-2);
	var dt = year+'/'+month+'/'+day;
	if (time) {
		dt += ' '+hour+':'+minute+':'+second;
	}
	return dt;
}

/**
 * イベントリスナーを要素に追加します。
 * @param {Object} elem 要素
 * @param {String} event イベント名
 * @param {Function} func イベントリスナー
 * @return {void}
 */
function DmapAddEvent(elem, event, func) {
	if (!elem) return;
	if (elem.addEventListener) {
		elem.addEventListener(event, func);
	} else {
		elem.attachEvent('on'+event, func);
	}
}

/**
 * イベントリスナーを要素から削除します。
 * @param {Object} elem 要素
 * @param {String} event イベント名
 * @param {Function} func イベントリスナー
 * @return {void}
 */
function DmapRemoveEvent(elem, event, func) {
	if (!elem) return;
	if (elem.removeEventListener) {
		elem.removeEventListener(event, func);
	} else {
		elem.detachEvent('on'+event, func);
	}
}

/**
 * Cookieから利用状況（操作回数）を取得します。
 * @return {String} 利用状況文字列
 */
function DmapGetCookieLog() {
	var ck = document.cookie;
	if (!ck) return '';
	ck = ck.split('; ');
	for (var i = 0; i < ck.length; i++) {
		var kv = ck[i].split('=');
		if (kv[0] == 'LgDMap') {
			var log = kv[1].split('_');
			log = log.slice(4).join('_');
			return log;
		}
	}
	return '';
}

/**
 * Cookieの利用状況（操作回数）をhiddenにセットします。
 * @return {void}
 */
function RestoreCookieLog() {
	var log = DmapGetCookieLog();
	if (log != '') {
		var LgDMap = document.getElementById('LgDMap');
		if (LgDMap) LgDMap.value = log;
	}
}

/**
 * 機能毎の利用状況（操作回数）をカウントアップして、Cookieとhiddenに格納します。
 * @param {Number} idx 機能番号
 * @return {void}
 */
function DmapLogCount(idx) {
	/* 有効期限 */
	var dt = new Date();
	dt.setTime(dt.getTime() + COOKIE_EXPIRES*24*60*60*1000);
	var expires = dt.toGMTString();
	/* hiddenから現状の格納値を取得 */
	var LgDMap = document.getElementById('LgDMap');
	var log = (LgDMap?LgDMap.value:'');
	if (log == '') log = '0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0';
	var arr_log = log.split('_');
	/* カウントアップ */
	arr_log[idx-1] = parseInt(arr_log[idx-1]) + 1;
	/* hiddenに書き込み */
	log = arr_log.join('_');
	if (LgDMap) LgDMap.value = log;
	/* Cookieに書き込み */
	var cookie_log = DmapUser.syokuin+'_'+DmapUser.sisya+'_'+DmapUser.ka+'_'+DmapUser.auth+'_'+log;
	document.cookie = 'LgDMap='+cookie_log+';expires='+expires+';path=/';
}

/**
 * htmlのサイズ（width,height）を返却します。
 * @param {String} html HTML文字列
 * @return {Array} width:幅（pixel）／height：高さ（pixel）
 */
function DmapGetHTMLSize(html) {
	var div = document.createElement('div');
	div.innerHTML = html;
	div.style.position = 'absolute';
	div.style.visibility = 'hidden';
	document.body.appendChild(div);
	var w = div.offsetWidth;
	var h = div.offsetHeight;
	document.body.removeChild(div);
	return {width:w, height:h};
}

/**
 * 緯度経度（十進）の小数部を７桁に揃えます。
 * @param {String} 緯度または経度（十進）
 * @return {String} 緯度または経度（十進）（小数部７桁）
 */
function DmapDegFormat(latlon) {
	var deg = String(latlon);
	if (!deg || deg == '' || deg.indexOf('.') < 1) {
		return deg;
	}
	var ll = deg.split('.');
	var i = ll[0];
	var d = ll[1];
	if (d.length > 7) {
		d = d.substr(0,7);
	} else if (d.length < 7) {
		d = (d+'0000000').slice(0,6);
	}
	return i+'.'+d;
}

/**
 * 文字列が全角のみかどうかを返却します。
 * @param {String} str 文字列
 * @return {Boolean} true：全角のみ／false：半角を含む
 */
function DmapIsMbString(str) {
	var len = str.length * 2;
	if (len == getByteLength(str)) {
		return true;
	} else {
		return false;
	}
}

/**
 * 文字列のバイト数を返却します。
 * @param {String} str 文字列
 * @return {Number} バイト数
 */
function getByteLength(str) {
	var HALF_SIZE_KANA = "ｧｱｨｲｩｳｪｴｫｵｶｷｸｹｺｻｼｽｾｿﾀﾁｯﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓｬﾔｭﾕｮﾖﾗﾘﾙﾚﾛﾜｦﾝｰﾟﾞ";
	var i = 0;
	var count = 0;
	for (i = 0; i < str.length; i++) {
		if (0 <= HALF_SIZE_KANA.indexOf(str.charAt(i))) {
			count++;
		} else if (escape(str.charAt(i)).length >= 4) {
			count+=2;
		} else {
			count++;
		}
	}
	return count;
}

/**
 * class名が要素の指定されているかどうかを返却します。
 * @param {Object} elm 要素
 * @param {String} class_name クラス名
 * @return {Boolean} true:指定したclassが指定されている／false：指定されていない
 */
function hasClass(elm, class_name) {
	var elm_class = elm.className.split(" ");
	for (var i=0, len=elm_class.length; i<len; i++) {
		if (class_name == elm_class[i]) {
			return true;
		}
	}
	return false;
}

/**
 * 要素にclassを追加指定します。
 * @param {Object} elm 要素
 * @param {String} class_name クラス名
 * @return {void}
 */
function addClass(elm, class_name) {
	if (!hasClass(elm, class_name)) {
		elm.className = (elm.className + " " + class_name).replace(/^ +| +$/g, "");
	}
}

/**
 * 要素からclass指定を削除します。
 * @param {Object} elm 要素
 * @param {String} class_name クラス名
 * @return {void}
 */
function removeClass(elm, class_name) {
	if (hasClass(elm, class_name)) {
		elm.className = elm.className.replace(class_name, "").replace(/^ +| +$/g, "");
	}
}

/**
 * ダイアログのドラッグを開始します。
 * @param {Object} elm 要素
 * @return {void}
 */
function DmapDlgDragStart(elm) {
	DmapDlgDrag.elm = elm;
	DmapAddEvent(DmapDlgDrag.elm, 'mousedown', DmapDlgDrapMouseDown);
	DmapAddEvent(document, 'mouseup', DmapDlgDrapMouseUp);
}

/**
 * ダイアログのドラッグを終了します。
 * @return {void}
 */
function DmapDlgDragEnd() {
	DmapRemoveEvent(DmapDlgDrag.elm, 'mousedown', DmapDlgDrapMouseDown);
	DmapRemoveEvent(document, 'mouseup', DmapDlgDrapMouseUp);
}

/**
 * ダイアログ上のMouseDownイベントリスナー。
 * @param {Object} evt イベント
 * @return {void}
 */
function DmapDlgDrapMouseDown(evt) {
	evt = (evt) || window.event;
	var target = (event.target) || event.srcElement;
	if (hasClass(target, "drag_off")) {
		/* class属性に"drag_off"を持つエレメントはドラッグ不可 */
		if (evt.stopPropagation) {
			evt.stopPropagation();
		} else {
			evt.cancelBubble = true;
		}
	} else {
		/* ドラッグ開始フラグON */
		DmapDlgDrag.flag = true;
		/* 座標を記憶 */
		DmapDlgDrag.x = evt.clientY - DmapDlgDrag.elm.offsetTop;
		DmapDlgDrag.y = evt.clientX - DmapDlgDrag.elm.offsetLeft;
		/* ドラッグ中のテキスト選択を回避 */
		if (evt.preventDefault) {
			evt.preventDefault();
		} else {
			evt.returnValue = false;
		}
		/* マウス移動時のイベント追加 */
		DmapAddEvent(document, "mousemove", DmapDlgDrapMouseMove);
	}
}

/**
 * ダイアログ上のMouseUpイベントリスナー。
 * @param {Object} evt イベント
 * @return {void}
 */
function DmapDlgDrapMouseUp(evt) {
	DmapDlgDrag.flag = false;
	DmapRemoveEvent(document, "mousemove", DmapDlgDrapMouseMove);
}

/**
 * ダイアログ上のMouseMoveイベントリスナー。
 * @param {Object} evt イベント
 * @return {void}
 */
function DmapDlgDrapMouseMove(evt) {
	evt = (evt) || window.event;
	if (DmapDlgDrag.flag) {
		/* 座標を移動 */
		DmapDlgDrag.elm.style.top = evt.clientY - DmapDlgDrag.x + "px";
		DmapDlgDrag.elm.style.left = evt.clientX - DmapDlgDrag.y + "px";
		/* ドラッグ中のテキスト選択を回避 */
		if (evt.preventDefault) {
			evt.preventDefault();
		} else {
			evt.returnValue = false;
		}
	}
}

/**
 * ヘッダのメッセージを表示します。
 * @param {String} e メッセージ文言
 * @return {void}
 */
function DmapShowHeaderMsg(msg) {
	var e = document.getElementById('header_msg');
	if (e) {
		e.innerHTML = msg;
		e.style.visibility = 'visible';
	}
}
/**
 * ヘッダのメッセージを消去します。
 * @return {void}
 */
function DmapHideHeaderMsg() {
	var e = document.getElementById('header_msg');
	if (e) {
		//e.innerHTML = '';
		e.style.visibility = 'hidden';
	}
}
