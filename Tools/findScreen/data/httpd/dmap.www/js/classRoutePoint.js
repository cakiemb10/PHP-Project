/**
 * DmapClassRoutePoint�I�u�W�F�N�g�𐶐����܂��B
 * @class ���[�g�̒n�_����ێ����܂��B
 * @param {String} type �n�_�^�C�v�istart�F�o���n�^end�F�ړI�n�j
 * @constructor
 */
var DmapClassRoutePoint = function (type) {
	/**
	 * �n�_�^�C�v��ێ����܂��B�istart�F�o���n�^end�F�ړI�n�j
	 * @type String
	 */
	this.type = type;
	/**
	 * ZDC.LatLon�I�u�W�F�N�g��ێ����܂��B
	 * @type Object
	 */
	this.latlon = null;
	/**
	 * �Z����ێ����܂��B
	 * @type String
	 */
	this.addr = null;
	/**
	 * �Z����\������v�f��ێ����܂��B
	 * @type Object
	 */
	this.addr_elm = null;
	/**
	 * �n�_�}�[�J�[�̃I�u�W�F�N�g��ێ����܂��B
	 * @type Object
	 */
	this.mrk = null;
};

/**
 * �n�_�}�[�J�[��n�}��ɕ\�����܂��B
 * @return {void}
 */
DmapClassRoutePoint.prototype.plotMarker = function() {
	if (this.latlon) {
		this.mrk = new ZDC.UserWidget(this.latlon, {
			html: '<div class="route_flag_'+this.type+'">�@</div>',
			offset: new ZDC.Pixel(POINT_MARKER_OFFSET_X, POINT_MARKER_OFFSET_Y),
			propagation: false
		});
		DmapMap.addWidget(this.mrk);
		this.mrk.open();
		DmapZindexMax++;
		this.mrk.setZindex(DmapZindexMax);
	}
}

/**
 * �n�}��̒n�_�}�[�J�[���������܂��B
 * @return {void}
 */
DmapClassRoutePoint.prototype.removeMarker = function() {
	if (this.mrk) {
		DmapMap.removeWidget(this.mrk);
		this.mrk = null;
	}
}

/**
 * �n�_�̏Z�����擾���܂��B
 * @return {void}
 */
DmapClassRoutePoint.prototype.getAddr = function() {
	if (this.latlon) {
		var point = this;
		ZDC.Search.getAddrByLatLon({
			latlons: [this.latlon]
		}, function(status, res) {
			if (status.code == '000' && res[0] && res[0].address) {
				point.addr = res[0].address.text;
				point.addr_elm.value = point.addr;
			} else {
				point.addr = '�i�Z���s���j';
				point.addr_elm.value = point.addr;
			}
		});
	}
}
