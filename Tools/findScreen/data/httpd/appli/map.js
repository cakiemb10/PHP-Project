// マップ
var map, lat = 35.6778614, lon = 139.7703167;
// Marker
var widgets = [];
// 吹き出し
var msgs = [];
// ルートの線
var route = [];
// 表示中の吹き出し
var msgInfo;
// 吹き出し表示フラグ
var dispFlag = false;
// 前回位置
var oldPos;
// 中心点画像
var centerMarker = {};
// ルートの始点画像
var routeStartMarker = {};
// ルートの終点画像
var routeEndMarker = {};

// 地図を表示する
function dispMap(opts) {
	// 画像先読み
	var img1 = new Image();
	img1.src = "img/route.png";
	var img2 = new Image();
	img2.src = "img/store.png";

	opts.options.latlon = convertLatLon(opts.options.latlon)
	map = new ZDC.Map(document.getElementById('ZMap'), opts.options);

	// クリック時の処理
	ZDC.addListener(map, ZDC.MAP_MOUSEDOWN, getOldPosition);
	ZDC.addListener(map, ZDC.MAP_MOUSEUP, removeMsgInfo2);

	var latlon = map.getPointerPosition();
	if(latlon != undefined) {
		oldPos = map.latLonToTL(latlon);
	}
	alert("dispMap:");
}

// ボタン押下時の位置取得
function getOldPosition() {
	var latlon = map.getPointerPosition();
	oldPos = map.latLonToTL(latlon);
	dispFlag = true;
}

// ミリ秒 -> 10進変換
function convertLatLon(src) {
	var dest = {};
	dest.lat = ZDC.msTodeg(src.lat);
	dest.lon = ZDC.msTodeg(src.lon);
	return dest;
}

// 10進 -> ミリ秒変換
function convertLatLonToMS(src) {
	var dest = {};
	dest.lat = ZDC.degToms(src.lat);
	dest.lon = ZDC.degToms(src.lon);
	return dest;
}

// 世界測地系10進 -> 日本測地系ミリ秒変換
function convertRawLatLonToMS(src) {
	var latlon = new ZDC.wgsTotky(src);
	var dest = convertLatLonToMS(latlon)
	alert("convertRawLatLonToMS:" + JSON.stringify(dest));
	return JSON.stringify(dest);
}

// ルート検索
function getRouteByWalk(src) {
	var route = new ZDC.Search.getRouteByWalk(
	{
		from: convertLatLon(src.from),
		to:   convertLatLon(src.to)
	},function(status, res){
        if (status.code == '000') {
            // 取得成功
            writeRoute(status, res);
			alert("getRouteByWalk:" + res.route.distance);
        } else {
            // 取得失敗
			alert("getRouteByWalk:(Error)" + status.text);
        }
	}
	);
}

// ルート検索(世界測地系)
function getRouteByWalkRaw(src) {
	var route = new ZDC.Search.getRouteByWalk(
	{
		from: convertLatLon(src.from),
		to: new ZDC.wgsTotky(src.to)
	},function(status, res){
        if (status.code == '000') {
            // 取得成功
            writeRoute(status, res);
			alert("getRouteByWalkRaw:" + res.route.distance);
        } else {
            // 取得失敗
			alert("getRouteByWalkRaw:(Error)" + status.code + ":" + status.text);
        }
	}
	);
}

// ルート検索(自動車)
function getRouteByDrive(src) {
	var route = new ZDC.Search.getRouteByDrive(
	{
		from: convertLatLon(src.from),
		to:   convertLatLon(src.to)
	},function(status, res){
        if (status.code == '000') {
            // 取得成功
            writeRoute(status, res);
			alert("getRouteByDrive:" + res.route.distance + "," + res.route.time);
        } else {
            // 取得失敗
			alert("getRouteByDrive:(Error)" + status.text);
        }
	}
	);
}

// ルート検索(自動車)(世界測地系)
function getRouteByDriveRaw(src) {
	var route = new ZDC.Search.getRouteByDrive(
	{
		from: convertLatLon(src.from),
		to: new ZDC.wgsTotky(src.to)
	},function(status, res){
        if (status.code == '000') {
            // 取得成功
            writeRoute(status, res);
			alert("getRouteByDriveRaw:" + res.route.distance + "," + res.route.time);
        } else {
            // 取得失敗
			alert("getRouteByDriveRaw:(Error)" + status.code + ":" + status.text);
        }
	}
	);
}

// ルート検索の結果で線を描く
function writeRoute(status, res) {
	// いったん全部消す
	removeRoute();

    var link = res.route.link;

	var options = {
		strokeColor: '#3000ff',
		strokeWeight: 4
	};
    for (var i = 0; i < link.length; i++) {
        var latlons = [];
        for (var j = 0; j < link[i].line.length; j++) {
            latlons.push(link[i].line[j]);
        }
        route[i] = new ZDC.Polyline(latlons, options);
        map.addWidget(route[i]);
    }
};

// ルート削除
function removeRoute() {
	for(i = 0; i < route.length; i++) {
		map.removeWidget(route[i]);
	}
	route = [];
}

// 地図のレベルを返す
function getZoom() {
	alert("getZoom:" + map.options.zoom);
	return map.options.zoom;
}

// 地図の中心点の緯度経度を取得します。
function getLatLon() {
	var latlon = convertLatLonToMS(map.getLatLon());
	var result = JSON.stringify(latlon);
	alert("getLatLon:" + result);
	return result;
}

// 指定した緯度経度を地図の中心にします。
function moveLatLon(lat, lon) {
	var latlon = {
		lat: ZDC.msTodeg(lat),
		lon: ZDC.msTodeg(lon)
	};
	map.moveLatLon(latlon);
}

// 指定した緯度経度を地図の中心にします。
function moveLatLonRaw(lat, lon) {
	var latlon = {
		lat:lat,
		lon:lon
	};
	map.moveLatLon(new ZDC.wgsTotky(latlon));
}

// 地図領域の左上端をtop=0,left=0として指定されたZDC.TLをZDC.LatLonに変換します。
function tlToLatLon(x, y) {
	var tl = {
		x: x,
		y: y
	};
	var latlon = map.tlToLatLon(tl);
	var result = JSON.stringify(latlon);
	alert("tlToLatLon:" + result);
	return result;
}

// 地図領域の左上端をtop=0,left=0として指定されたZDC.LatLonをZDC.TLに変換します。
function latLonToTL(lat, lon) {
	var latlon = {
		lat: lat,
		lon: lon
	};
	var tl = map.latLonToTL(latlon);
	var result = JSON.stringify(tl);
	alert("latLonToTL:" + result);
	return result;
}

// 2点間の距離をメートル単位で返却します。
function getLatLonToLatLonDistance(fromLat, fromLon, toLat, toLon) {
	var from = {
		lat: fromLat,
		lon: fromLon
	};
	var to = {
		lat: toLat,
		lon: toLon
	};
	var result = map.getLatLonToLatLonDistance(from, to);
	alert("getLatLonToLatLonDistance:" + result);
	return result;
}

// 地図の表示レベルを設定する。
function setMapTileLevel(level) {
	map.options.zoom = level;
}

// ビューの中央を中心にしてズームインする。
function centerZoomIn() {
	map.zoomIn();
}

// ビューの中央を中心にしてズームアウトする。
function centerZoomOut() {
	map.zoomOut();
}

// Markerと吹き出しを追加する
function addMarkerAndMsgInfo(markerStr, msgInfoStr, canDispLButton, storeID, lat, lon, storeName, address, openFlag) {
	var marker = new ZDC.Marker(convertLatLon(markerStr.latlon), markerStr.options);
	widgets.push(marker);
	map.addWidget(marker);

	var img = new Image();
	img.src = "img/store.png";
	img.onload = function() {
		var html = "<table border=0><tr>";
		if (canDispLButton) {
			html = html + "<td rowspan=2><img src=\"img/route.png\" ";
			html = html + " onClick=\"lButtonClicked('" + storeID + "','" + lat + "','" + lon + "')\"/></td>";
		}
		html = html + "<td nowrap><span style=\"font-size:small\">" + storeName + "</span></td>";
		html = html + "<td rowspan=2><img src=\"" + this.src + "\" onclick=\"rButtonClicked(" + storeID + ");\" /></td></tr>";
		html = html + "<tr><td nowrap><span style=\"font-size:x-small\">" + address + "</span></td></tr>";
		html = html + "</table>";
		msgInfoStr.content.html = html;
		msg = new ZDC.MsgInfo(convertLatLon(msgInfoStr.latlon), msgInfoStr.content);
		msgs.push(msg);
		map.addWidget(msg);
		if(openFlag) {
			msg.open();
		}
		msgInfo = msg;
		ZDC.bind(marker, ZDC.MARKER_MOUSEDOWN, {info: msg}, openMsgInfo);
	};
}

// 中心点画像を追加する
function addCenterMarker(latlon) {
	removeCenterMarker();
	centerMarker = new ZDC.Marker(convertLatLon(latlon), {
		offset: new ZDC.Pixel(-14,-14),
		custom: {
			base:{
				src: 'img/location.png'
			}
		}
	});
	map.addWidget(centerMarker);
	centerMarker.setZindex(999);
}

// 中心点画像を描画する(世界測地系)
function addCenterMarkerRaw(latlon) {
	removeCenterMarker();

	centerMarker = new ZDC.Marker(ZDC.wgsTotky(latlon), {
		offset: new ZDC.Pixel(-14,-14),
		custom: {
			base:{
				src: 'img/location.png'
			}
		}
	});
	map.addWidget(centerMarker);
	centerMarker.setZindex(999);
}

// 全Markerを削除する
function removeAllMarker() {
	for(i = 0; i < widgets.length; i++) {
		widgets[i].hidden();
	}
	for(i = 0; i < widgets.length; i++) {
		map.removeWidget(widgets[i]);
	}
	for(i = 0; i < msgs.length; i++) {
		map.removeWidget(msgs[i]);
	}
	widgets = [];
	msgs = [];
}

// 中心点画像を削除する
function removeCenterMarker() {
	if(Object.keys(centerMarker).length > 0) {
		map.removeWidget(centerMarker);
	}
}

// ルートの始点画像を追加する(世界測地系)
function addRouteStartMarkerRaw(latlon) {
	removeRouteStartMarker();
	routeStartMarker = new ZDC.Marker(ZDC.wgsTotky(latlon), {
		offset: new ZDC.Pixel(0,-36),
		custom: {
			base:{
				src: 'img/RouteStart.png'
			}
		}
	});
	map.addWidget(routeStartMarker);
	routeStartMarker.setZindex(999);
}

// ルートの始点画像を追加する(ミリ秒)
function addRouteStartMarker(latlon) {
	removeRouteStartMarker();
	routeStartMarker = new ZDC.Marker(convertLatLon(latlon), {
		offset: new ZDC.Pixel(0,-36),
		custom: {
			base:{
				src: 'img/RouteStart.png'
			}
		}
	});
	map.addWidget(routeStartMarker);
	routeStartMarker.setZindex(999);
}

// ルートの始点画像を削除する
function removeRouteStartMarker() {
	if(Object.keys(routeStartMarker).length > 0) {
		map.removeWidget(routeStartMarker);
	}
}

// ルートの終点画像を追加する(世界測地系)
function addRouteEndMarkerRaw(latlon) {
	removeRouteEndMarker();
	routeEndMarker = new ZDC.Marker(ZDC.wgsTotky(latlon), {
		offset: new ZDC.Pixel(0,-36),
		custom: {
			base:{
				src: 'img/RouteEnd.png'
			}
		}
	});
	map.addWidget(routeEndMarker);
	routeEndMarker.setZindex(999);
}

// ルートの終点画像を追加する(ミリ秒)
function addRouteEndMarker(latlon) {
	removeRouteEndMarker();
	routeEndMarker = new ZDC.Marker(convertLatLon(latlon), {
		offset: new ZDC.Pixel(0,-36),
		custom: {
			base:{
				src: 'img/RouteEnd.png'
			}
		}
	});
	map.addWidget(routeEndMarker);
	routeEndMarker.setZindex(999);
}

// ルートの始点画像を削除する
function removeRouteEndMarker() {
	if(Object.keys(routeEndMarker).length > 0) {
		map.removeWidget(routeEndMarker);
	}
}

// 吹き出しを削除する
function removeMsgInfo() {
	if(msgInfo != undefined){
		msgInfo.close();
	}
	for(i = 0; i < msgs.length; i++) {
		msgs[i].close();
	}
}

// MOUSEDOWN時に吹き出しを削除する
function removeMsgInfo2() {
	var newPos = map.latLonToTL(map.getPointerPosition());
	if(Math.abs(oldPos.top - newPos.top) > 5) {
		dispFlag = false;
	}
	if(Math.abs(oldPos.left - newPos.left) > 5) {
		dispFlag = false;
	}
	if(dispFlag) {
		for(i = 0; i < msgs.length; i++) {
			msgs[i].close();
		}
	}
}

// 吹き出しを表示する。
function dispMsgInfo(storeID) {
	// 最後に表示したMarkerの吹き出しを表示する
	var index = msgs.length -1;
	msgs[index].open();
	msgInfo = msgs[index];
}

// 吹き出しを表示する。
function openMsgInfo() {
	if(msgInfo != undefined && Object.keys(msgInfo).length > 0 ) {
		msgInfo.close();
	}
	removeMsgInfo();
	this.info.open();
	msgInfo = this.info;
}

// 左ボタン押下時の処理
function lButtonClicked(id, lat, lon) {
	bridge.msgInfoLButtonClicked(id, lat, lon);
}

// 右ボタン押下時の処理
function rButtonClicked(param) {
	bridge.msgInfoRButtonClicked(param);
}

// 地図領域の左下、右上の緯度経度を取得する
function getLatLonBox() {
	var result = {};
	var llBox = map.getLatLonBox();
	result.max = convertLatLonToMS(llBox.getMax());
	result.min = convertLatLonToMS(llBox.getMin());
	alert("getLatLonBox:" + JSON.stringify(result));
	return JSON.stringify(result);
}

// マップ情報を取得する
// 中心から右上までの距離(メートル)
// LatLonBoxの縦(メートル)
// LatLonBoxの横(メートル)
function getLatLon3Results() {
	var result = {};
	var param1, param2, param3;
	while(true) {
		var center = map.getLatLon();
		var llBox = map.getLatLonBox();
		param1 = ZDC.getLatLonToLatLonDistance(llBox.getMax(), center);
		var p1 = new ZDC.LatLon(llBox.getMax().lat, llBox.getMin().lon);
		param2 = ZDC.getLatLonToLatLonDistance(llBox.getMax(), p1);
		var p2 = new ZDC.LatLon(llBox.getMin().lat, llBox.getMax().lon);
		param3 = ZDC.getLatLonToLatLonDistance(llBox.getMax(), p2);
		if(param1 != 0 || param2 != 0 || param3 != 0 ) {
			break;
		}
	}
	result.param1 = param1;
	result.param2 = param2;
	result.param3 = param3;
	alert("getLatLon3Results:" + JSON.stringify(result));
	return JSON.stringify(result);
}

// 終了通知用
function notifyEnd() {
	alert("notifyEnd:");
}

document.addEventListener("touchstart", this.touchHandler, false);
document.addEventListener("touchmove", this.touchHandler, false);
document.addEventListener("touchend", this.touchHandler, false);
document.addEventListener("touchcancel", this.touchHandler, false);
function touchHandler(event) {
	event.preventDefault();
}
