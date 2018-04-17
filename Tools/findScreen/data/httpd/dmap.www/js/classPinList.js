/**
 * DmapClassPinListオブジェクトを生成します。
 * @class 複数のPinオブジェクトを保持します。
 * @constructor
 */
var DmapClassPinList = function() {
	/**
	 * DmapClassPinオブジェクトを配列で保持します。
	 * @type Array
	 */
	this.Pins = new Array();
	/**
	 * グループの情報を配列で保持します。
	 * @type Array
	 */
	this.Groups = new Array();
	var arr_groups = new Array();
	var arr_gid = new Array();
	for (var i = 0; i < 100; i++) {
		var pin = new DmapClassPin(i);
		if (!pin.latlon) break;
		/* グルーピング */
		if (!arr_groups[pin.gid]) {
			/* グループの先頭 */
			arr_groups[pin.gid] = new Array();
			arr_groups[pin.gid][0] = pin.seq;
		} else {
			/* グループの後続 */
			arr_groups[pin.gid].push(pin.seq);
			pin.plot = false;
			/* グルーピング対象のGIDを保持 */
			arr_gid.push(pin.gid);
		}
		/* ピンを保持 */
		this.Pins[i] = pin;
	}
	var len = arr_gid.length;
	for (i = 0; i < len; i++) {
		var gid = arr_gid[i];
		/* 表示連番 */
		var cnt = arr_groups[gid].length;
		for (var s = 0; s < cnt; s++) {
			var seq = arr_groups[gid][s];
			this.Pins[seq].group = true;
			var n = s + 1;
			this.Pins[seq].num_on_list = gid + '-' + n;
		}
		/* グルーピング情報を保持 */
		this.Groups[gid] = arr_groups[gid];
	}
}

/**
 * 全てのピンのポイント名を表示します。
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
 * 全てのピンのポイント名を消去します。
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
 * 全てのピンの業種名を表示します。
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
 * 全てのピンの業種名を消去します。
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
 * 同グループの他のピンを全て非表示にします。
 * @param {Object} pin DmapClassPinオブジェクト
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
