/**
 * DmapClassRoutePointオブジェクトを生成します。
 * @class ルートの地点情報を保持します。
 * @param {String} type 地点タイプ（start：出発地／end：目的地）
 * @constructor
 */
var DmapClassRoutePoint = function (type) {
	/**
	 * 地点タイプを保持します。（start：出発地／end：目的地）
	 * @type String
	 */
	this.type = type;
	/**
	 * ZDC.LatLonオブジェクトを保持します。
	 * @type Object
	 */
	this.latlon = null;
	/**
	 * 住所を保持します。
	 * @type String
	 */
	this.addr = null;
	/**
	 * 住所を表示する要素を保持します。
	 * @type Object
	 */
	this.addr_elm = null;
	/**
	 * 地点マーカーのオブジェクトを保持します。
	 * @type Object
	 */
	this.mrk = null;
};

/**
 * 地点マーカーを地図上に表示します。
 * @return {void}
 */
DmapClassRoutePoint.prototype.plotMarker = function() {
	if (this.latlon) {
		this.mrk = new ZDC.UserWidget(this.latlon, {
			html: '<div class="route_flag_'+this.type+'">　</div>',
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
 * 地図上の地点マーカーを消去します。
 * @return {void}
 */
DmapClassRoutePoint.prototype.removeMarker = function() {
	if (this.mrk) {
		DmapMap.removeWidget(this.mrk);
		this.mrk = null;
	}
}

/**
 * 地点の住所を取得します。
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
				point.addr = '（住所不明）';
				point.addr_elm.value = point.addr;
			}
		});
	}
}
