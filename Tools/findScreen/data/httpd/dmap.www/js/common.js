/* �f�o�b�O�p�Fconsole.log��IE�ŃG���[�ɂȂ�Ȃ����߂̋L�q�ł��i�폜�j */
(function () {
	if (typeof window.console === "undefined") {
		 window.console = {}
	}
	if (typeof window.console.log !== "function") {
		 window.console.log = function () {}
	}
})();

/* ���͕s�̃e�L�X�g�{�b�N�X��Ńo�b�N�X�y�[�X�L�[����������ƃy�[�W���߂��Ă��܂��̂�}�����Ă��܂��i���폜�s�j */
window.document.onkeydown = keydown;
function keydown(){
	if( window.event.keyCode == 8 && window.event.srcElement.readOnly == true){
		return false;
	}
}

if (!String.prototype.trim) {
/**
 * ������̑O��̋󔒂��������܂��B
 * @return {String} <br>�󔒂���������������
 */
String.prototype.trim = function() {
    return this.replace(/^[\s�@]+|[\s�@]+$/g, "");
}
}

/**
 * �v�fid���w�肵��value���擾���܂��B
 * @param {String} id �v�f��id
 * @return {String} �v�f��value�l
 */
function DmapGetValueById(id) {
	var e = document.getElementById(id);
	if (e) {
		return e.value;
	}
	return "";
}

/**
 * ���t�����������yyyymmdd�Ƀt�H�[�}�b�g���ĕԋp���܂��B
 * @param {String} ymd ���t������iyyyy/m/d�j
 * @return {String} ���t������iyyyymmdd�j
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
 * ���ݓ��t�𕶎���ŕԋp���܂��B
 * @param {Boolean} time true�F������t������iyyyy/mm/dd hh:nn:ss�j�^false�F������t�����Ȃ��iyyyy/mm/dd�j
 * @return {String} ���t������iyyyy/mm/dd�jor �iyyyy/mm/dd hh:nn:ss�j
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
 * �C�x���g���X�i�[��v�f�ɒǉ����܂��B
 * @param {Object} elem �v�f
 * @param {String} event �C�x���g��
 * @param {Function} func �C�x���g���X�i�[
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
 * �C�x���g���X�i�[��v�f����폜���܂��B
 * @param {Object} elem �v�f
 * @param {String} event �C�x���g��
 * @param {Function} func �C�x���g���X�i�[
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
 * Cookie���痘�p�󋵁i����񐔁j���擾���܂��B
 * @return {String} ���p�󋵕�����
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
 * Cookie�̗��p�󋵁i����񐔁j��hidden�ɃZ�b�g���܂��B
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
 * �@�\���̗��p�󋵁i����񐔁j���J�E���g�A�b�v���āACookie��hidden�Ɋi�[���܂��B
 * @param {Number} idx �@�\�ԍ�
 * @return {void}
 */
function DmapLogCount(idx) {
	/* �L������ */
	var dt = new Date();
	dt.setTime(dt.getTime() + COOKIE_EXPIRES*24*60*60*1000);
	var expires = dt.toGMTString();
	/* hidden���猻��̊i�[�l���擾 */
	var LgDMap = document.getElementById('LgDMap');
	var log = (LgDMap?LgDMap.value:'');
	if (log == '') log = '0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0_0';
	var arr_log = log.split('_');
	/* �J�E���g�A�b�v */
	arr_log[idx-1] = parseInt(arr_log[idx-1]) + 1;
	/* hidden�ɏ������� */
	log = arr_log.join('_');
	if (LgDMap) LgDMap.value = log;
	/* Cookie�ɏ������� */
	var cookie_log = DmapUser.syokuin+'_'+DmapUser.sisya+'_'+DmapUser.ka+'_'+DmapUser.auth+'_'+log;
	document.cookie = 'LgDMap='+cookie_log+';expires='+expires+';path=/';
}

/**
 * html�̃T�C�Y�iwidth,height�j��ԋp���܂��B
 * @param {String} html HTML������
 * @return {Array} width:���ipixel�j�^height�F�����ipixel�j
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
 * �ܓx�o�x�i�\�i�j�̏��������V���ɑ����܂��B
 * @param {String} �ܓx�܂��͌o�x�i�\�i�j
 * @return {String} �ܓx�܂��͌o�x�i�\�i�j�i�������V���j
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
 * �����񂪑S�p�݂̂��ǂ�����ԋp���܂��B
 * @param {String} str ������
 * @return {Boolean} true�F�S�p�̂݁^false�F���p���܂�
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
 * ������̃o�C�g����ԋp���܂��B
 * @param {String} str ������
 * @return {Number} �o�C�g��
 */
function getByteLength(str) {
	var HALF_SIZE_KANA = "����������������������������������������Ӭԭծ������ܦݰ��";
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
 * class�����v�f�̎w�肳��Ă��邩�ǂ�����ԋp���܂��B
 * @param {Object} elm �v�f
 * @param {String} class_name �N���X��
 * @return {Boolean} true:�w�肵��class���w�肳��Ă���^false�F�w�肳��Ă��Ȃ�
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
 * �v�f��class��ǉ��w�肵�܂��B
 * @param {Object} elm �v�f
 * @param {String} class_name �N���X��
 * @return {void}
 */
function addClass(elm, class_name) {
	if (!hasClass(elm, class_name)) {
		elm.className = (elm.className + " " + class_name).replace(/^ +| +$/g, "");
	}
}

/**
 * �v�f����class�w����폜���܂��B
 * @param {Object} elm �v�f
 * @param {String} class_name �N���X��
 * @return {void}
 */
function removeClass(elm, class_name) {
	if (hasClass(elm, class_name)) {
		elm.className = elm.className.replace(class_name, "").replace(/^ +| +$/g, "");
	}
}

/**
 * �_�C�A���O�̃h���b�O���J�n���܂��B
 * @param {Object} elm �v�f
 * @return {void}
 */
function DmapDlgDragStart(elm) {
	DmapDlgDrag.elm = elm;
	DmapAddEvent(DmapDlgDrag.elm, 'mousedown', DmapDlgDrapMouseDown);
	DmapAddEvent(document, 'mouseup', DmapDlgDrapMouseUp);
}

/**
 * �_�C�A���O�̃h���b�O���I�����܂��B
 * @return {void}
 */
function DmapDlgDragEnd() {
	DmapRemoveEvent(DmapDlgDrag.elm, 'mousedown', DmapDlgDrapMouseDown);
	DmapRemoveEvent(document, 'mouseup', DmapDlgDrapMouseUp);
}

/**
 * �_�C�A���O���MouseDown�C�x���g���X�i�[�B
 * @param {Object} evt �C�x���g
 * @return {void}
 */
function DmapDlgDrapMouseDown(evt) {
	evt = (evt) || window.event;
	var target = (event.target) || event.srcElement;
	if (hasClass(target, "drag_off")) {
		/* class������"drag_off"�����G�������g�̓h���b�O�s�� */
		if (evt.stopPropagation) {
			evt.stopPropagation();
		} else {
			evt.cancelBubble = true;
		}
	} else {
		/* �h���b�O�J�n�t���OON */
		DmapDlgDrag.flag = true;
		/* ���W���L�� */
		DmapDlgDrag.x = evt.clientY - DmapDlgDrag.elm.offsetTop;
		DmapDlgDrag.y = evt.clientX - DmapDlgDrag.elm.offsetLeft;
		/* �h���b�O���̃e�L�X�g�I������� */
		if (evt.preventDefault) {
			evt.preventDefault();
		} else {
			evt.returnValue = false;
		}
		/* �}�E�X�ړ����̃C�x���g�ǉ� */
		DmapAddEvent(document, "mousemove", DmapDlgDrapMouseMove);
	}
}

/**
 * �_�C�A���O���MouseUp�C�x���g���X�i�[�B
 * @param {Object} evt �C�x���g
 * @return {void}
 */
function DmapDlgDrapMouseUp(evt) {
	DmapDlgDrag.flag = false;
	DmapRemoveEvent(document, "mousemove", DmapDlgDrapMouseMove);
}

/**
 * �_�C�A���O���MouseMove�C�x���g���X�i�[�B
 * @param {Object} evt �C�x���g
 * @return {void}
 */
function DmapDlgDrapMouseMove(evt) {
	evt = (evt) || window.event;
	if (DmapDlgDrag.flag) {
		/* ���W���ړ� */
		DmapDlgDrag.elm.style.top = evt.clientY - DmapDlgDrag.x + "px";
		DmapDlgDrag.elm.style.left = evt.clientX - DmapDlgDrag.y + "px";
		/* �h���b�O���̃e�L�X�g�I������� */
		if (evt.preventDefault) {
			evt.preventDefault();
		} else {
			evt.returnValue = false;
		}
	}
}

/**
 * �w�b�_�̃��b�Z�[�W��\�����܂��B
 * @param {String} e ���b�Z�[�W����
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
 * �w�b�_�̃��b�Z�[�W���������܂��B
 * @return {void}
 */
function DmapHideHeaderMsg() {
	var e = document.getElementById('header_msg');
	if (e) {
		//e.innerHTML = '';
		e.style.visibility = 'hidden';
	}
}
