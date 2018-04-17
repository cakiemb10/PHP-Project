/**
 * DmapClassPinList�I�u�W�F�N�g�𐶐����܂��B
 * @class ������Pin�I�u�W�F�N�g��ێ����܂��B
 * @constructor
 */
var DmapClassPinList = function() {
	/**
	 * DmapClassPin�I�u�W�F�N�g��z��ŕێ����܂��B
	 * @type Array
	 */
	this.Pins = new Array();
	/**
	 * �O���[�v�̏���z��ŕێ����܂��B
	 * @type Array
	 */
	this.Groups = new Array();
	var arr_groups = new Array();
	var arr_gid = new Array();
	for (var i = 0; i < 100; i++) {
		var pin = new DmapClassPin(i);
		if (!pin.latlon) break;
		/* �O���[�s���O */
		if (!arr_groups[pin.gid]) {
			/* �O���[�v�̐擪 */
			arr_groups[pin.gid] = new Array();
			arr_groups[pin.gid][0] = pin.seq;
		} else {
			/* �O���[�v�̌㑱 */
			arr_groups[pin.gid].push(pin.seq);
			pin.plot = false;
			/* �O���[�s���O�Ώۂ�GID��ێ� */
			arr_gid.push(pin.gid);
		}
		/* �s����ێ� */
		this.Pins[i] = pin;
	}
	var len = arr_gid.length;
	for (i = 0; i < len; i++) {
		var gid = arr_gid[i];
		/* �\���A�� */
		var cnt = arr_groups[gid].length;
		for (var s = 0; s < cnt; s++) {
			var seq = arr_groups[gid][s];
			this.Pins[seq].group = true;
			var n = s + 1;
			this.Pins[seq].num_on_list = gid + '-' + n;
		}
		/* �O���[�s���O����ێ� */
		this.Groups[gid] = arr_groups[gid];
	}
}

/**
 * �S�Ẵs���̃|�C���g����\�����܂��B
 * @return {void}
 */
DmapClassPinList.prototype.showPointName = function() {
	var len = this.Pins.length;
	if (len == 0) return;
	for (var i = 0; i < len; i++) {
		var p = this.Pins[i];
		p.showPointName();
	}
}

/**
 * �S�Ẵs���̃|�C���g�����������܂��B
 * @return {void}
 */
DmapClassPinList.prototype.removePointName = function() {
	var len = this.Pins.length;
	if (len == 0) return;
	for (var i = 0; i < len; i++) {
		var p = this.Pins[i];
		p.removePointName();
	}
}

/**
 * �S�Ẵs���̋Ǝ햼��\�����܂��B
 * @return {void}
 */
DmapClassPinList.prototype.showGyosyu = function() {
	var len = this.Pins.length;
	if (len == 0) return;
	for (var i = 0; i < len; i++) {
		var p = this.Pins[i];
		p.showGyosyu();
	}
}

/**
 * �S�Ẵs���̋Ǝ햼���������܂��B
 * @return {void}
 */
DmapClassPinList.prototype.removeGyosyu = function() {
	var len = this.Pins.length;
	if (len == 0) return;
	for (var i = 0; i < len; i++) {
		var p = this.Pins[i];
		p.removeGyosyu();
	}
}

/**
 * ���O���[�v�̑��̃s����S�Ĕ�\���ɂ��܂��B
 * @param {Object} pin DmapClassPin�I�u�W�F�N�g
 * @return {void}
 */
DmapClassPinList.prototype.removeGroupOtherPins = function(pin) {
	var len = this.Pins.length;
	if (len == 0) return;
	for (var i = 0; i < len; i++) {
		var p = this.Pins[i];
		if (p.gid == pin.gid && p.seq != pin.seq && p.widgetPin) {
			p.removeWidget();
		}
	}
}
