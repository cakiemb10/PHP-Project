/**
 * DmapClassRouteSearchオブジェクトを生成します。
 * @class ルート検索の操作を制御します。
 * @param {String} dlg_id ダイアログID
 * @constructor
 */
var DmapClassRouteSearch = function (dlg_id) {
	if (!dlg_id) return;
	if (!dlg_id.match(/_dlg$/)) return;
	/**
	 * 要素名のプレフィックスを保持します。
	 * @type String
	 */
	this.pref_id = dlg_id.replace("dlg", "");
	/**
	 * ダイアログIDを保持します。
	 * @type String
	 */
	this.dlg_id = dlg_id;
	/**
	 * ダイアログ要素を保持します。
	 * @type Object
	 */
	this.dlg_elm = document.getElementById(dlg_id);
	this.drag = null;
	/**
	 * ルートモードを保持します。（walk：歩行者／car：車／train：電車）
	 * @type String
	 */
	this.mode = null;
	this.action = null;
	/**
	 * 出発地と目的地のDmapClassRoutePointオブジェクトを保持します。
	 * @type Array
	 */
	this.point = {
		'start': new DmapClassRoutePoint('start'),
		'end':   new DmapClassRoutePoint('end')
	};
	/**
	 * 地点指定時に使用される変数です。
	 * @type Array
	 */
	this.point_type = null;
	/**
	 * ルート設定を保持します。
	 * @type Array
	 */
	this.cond = new Array();
	/**
	 * ルート描画時に使用される変数です。
	 * @type Array
	 */
	this.pls = new Array();
	/**
	 * 地点指定ボタンの状態管理に使用される変数です。
	 * @type Object
	 */
	this.btn_elm_on = null;
	/**
	 * ルート描画時に使用される変数です。
	 * @type Array
	 */
	this.zoom_latlon = new Array();
	/**
	 * ルート描画時に使用される変数です。
	 * @type Object
	 */
	this.route = new Object();
	/**
	 * ルート描画設定を保持します。
	 * @type Array
	 */
	this.line_opt = {
		'walk' : {strokeColor: '#00FFFF', strokeWeight: 7, lineOpacity: 0.75, lineStyle: 'solid'},
		'car'  : {strokeColor: '#0000FF', strokeWeight: 7, lineOpacity: 0.65, lineStyle: 'solid'},
		'train': {strokeColor: '#0000FF', strokeWeight: 7, lineOpacity: 0.65, lineStyle: 'solid'}
	};
}

/**
 * ルート探索ダイアログの要素を取得します。
 * @param {String} id 要素ID
 * @return {Object} 要素
 */
DmapClassRouteSearch.prototype.getElmByID = function(id) {
	return document.getElementById(this.pref_id+id);
}

/**
 * ルート探索ダイアログを開きます。
 * @return {void}
 */
DmapClassRouteSearch.prototype.openDialog = function() {
	var elm;
	/* 初期表示時は歩行者ルート */
	if (!this.mode) {
		this.changeMode("walk");
	}
	/* フォームリセット */
	/* 出発地 */
	elm = this.getElmByID("start_addr");
	elm.tagName == "INPUT" ? elm.value = "出発地ボタンを押してください" : elm.innerText = "";
	/* 目的地 */
	elm = this.getElmByID("end_addr");
	elm.tagName == "INPUT" ? elm.value = "目的地ボタンを押してください" : elm.innerText = "";
	this.getElmByID("searchtype1")[0].selected = true;	/* 歩行者ルート：ルート設定 */
	this.getElmByID("searchtype2")[0].selected = true;	/* 車ルート：ルート設定 */
	this.getElmByID("toll").checked = false;			/* 車ルート：有料道路 */
	this.getElmByID("xdw")[0].selected = true;			/* 電車ルート：曜日 */
	this.getElmByID("xrp")[0].selected = true;			/* 電車ルート：表示順 */
	this.getElmByID("xep").checked  = false;			/* 電車ルート：特急利用 */
	/* ダイアログを表示 */
	this.dlg_elm.style.display = 'block';
	/* ダイアログのドラッグを可能にする */
	DmapDlgDragStart(this.dlg_elm);
}

/**
 * ルート探索ダイアログを閉じます。
 * @return {void}
 */
DmapClassRouteSearch.prototype.closeDialog = function() {
	/* ダイアログを隠す */
	this.dlg_elm.style.display = 'none';
	DmapDlgDragEnd();
	DmapRightClickMode = 1;
	/* メッセージ削除 */
	this.removeMessage();
	/* ボタンの色をOFFにする */
	this.setButtonColorOff();
}

/**
 * ルートモードを切り替えます。
 * @param {String} mode ルートモード（walk：歩行者／car：車／train：電車）
 * @return {void}
 */
DmapClassRouteSearch.prototype.changeMode = function(mode) {
	this.mode = mode;
	DmapRightClickMode = 0;
	/* メッセージ削除 */
	this.removeMessage();
	/* ボタンの色をOFFにする */
	this.setButtonColorOff();
	/* 画像を切替 */
	var mode_elm = this.getElmByID("mode");
	var img_elm = mode_elm.getElementsByTagName("img");
	for (var i=0, len=img_elm.length; i<len; i++) {
		var classNmae = img_elm[i].className;
		if (hasClass(img_elm[i], mode)) {
			img_elm[i].setAttribute("src", img_elm[i].getAttribute("src").replace("_off.", "_on."));
		} else {
			img_elm[i].setAttribute("src", img_elm[i].getAttribute("src").replace("_on.", "_off."));
		}
	}
	/* 条件を切替 */
	var cnd_lst_elm = this.getElmByID("cond_list");
	var li_elm = cnd_lst_elm.getElementsByTagName("li");
	for (var i=0, len=li_elm.length; i<len; i++) {
		if (hasClass(li_elm[i], mode)) {
			li_elm[i].style.display = 'block';
		} else {
			li_elm[i].style.display = 'none';
		}
	}
}

/**
 * 地点をセットします。
 * @param {String} type 地点のタイプ（start：出発地／end：目的地）
 * @param {Object} latlon 緯度経度オブジェクト
 * @param {String} name 場所名
 * @return {void}
 */
DmapClassRouteSearch.prototype.setPoint = function(type, latlon, name) {
	var point = this.point[type];
	point.latlon = latlon;
	point.addr = name;
	point.addr_elm = this.getElmByID(type+"_addr");
	point.addr_elm.innerText = name;
	point.plotMarker();
}

/**
 * 地点指定モードを開始します。
 * @param {String} type 地点のタイプ（start：出発地／end：目的地）
 * @return {void}
 */
DmapClassRouteSearch.prototype.searchPoint = function(type) {
	this.point_type = type;
	var type_elm = this.getElmByID(type);
	var label = type_elm.innerText;
	/* 右クリックをルート検索モードに */
	DmapRightClickMode = 2;
	/* メッセージ表示 */
	this.showMessage(label+'点を地図上で長押ししてください。');
	/* ボタンの色をOFFにする */
	this.setButtonColorOff();
	/* 押されたボタンの色をONにする */
	this.setButtonColorOn(type_elm);
}

/**
 * 地点を指定します。
 * @return {void}
 */
DmapClassRouteSearch.prototype.entryPoint = function() {
	var point = this.point[this.point_type];
	/* マーカーを削除 */
	point.removeMarker();
	/* 右クリックした位置の緯度経度取得 */
	point.latlon = DmapMap.getPointerPosition();
	/* マーカーをプロット */
	point.plotMarker();
	/* その緯度経度の住所を取得 */
	point.addr_elm = this.getElmByID(this.point_type+"_addr");
	point.getAddr();
	/* メッセージ削除 */
	this.removeMessage();
	/* ボタンの色をOFFに戻す */
	this.setButtonColorOff();
	/* 右クリック無効化 */
	DmapRightClickMode = 0;
}

/**
 * ルート検索を実行します。
 * @param {Function} callback コールバック関数
 * @return {void}
 */
DmapClassRouteSearch.prototype.execSearch = function (callback) {
	if (!callback) callback = function() {};
	var elm;
	/* 出発地の緯度経度を取得 */
	var from = this.point['start'].latlon;
	if (!from) {
		alert('出発地を指定してください。');
		return;
	}
	/* 目的地の緯度経度を取得 */
	var to = this.point['end'].latlon;
	if (!to) {
		alert('目的地を指定してください。');
		return;
	}
	/* 利用状況ログ */
	if (this.dlg_id == 'rv_dlg') {
		DmapLogCount(2);
	}
	if (this.dlg_id == 'rs_dlg') {
		DmapLogCount(10);
	}
	this.cond = new Array();
	var rsObj = this;
	if ( this.mode == "walk" ) {
		/* 歩行ルート検索 */
		/* ルート設定を取得 */
		elm = this.getElmByID("searchtype1");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var searchtype = elm.value;
		ZDC.Search.getRouteByWalk({
			from: from,
			to: to,
			datum: 'TOKYO',
			searchtype: searchtype,
			maxdist: WALK_MAX_DIST
		}, function(status, res) {
			if (status.code == "000") {
				rsObj.showRoute(rsObj.mode, res.route.link);
				rsObj.adjustZoom();
				rsObj.showProfile(res.route.distance, Math.ceil(res.route.distance / WALK_SPEED));
				rsObj.showRouteDetail();
				callback();
			} else if (status.code == "102") {
				alert(MSG_ERR_ROUTE_FAIL);
			} else {
				alert(MSG_ERR_SEARCH_FAIL);
			}
		});
	} else if ( this.mode == "car" ) {
		/* 自動車ルート検索 */
		/* ルート設定を取得 */
		elm = this.getElmByID("searchtype2");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var searchtype = elm.value;
		/* 有料道路を取得 */
		elm = this.getElmByID("toll");
		if (elm.checked) this.cond.push("有料道路利用");
		var toll = elm.checked;
		ZDC.Search.getRouteByDrive({
			from: from,
			to: to,
			datum: 'TOKYO',
			searchtype: searchtype,
			toll: toll
		}, function(status, res) {
			if (status.code == "000") {
				rsObj.showRoute(rsObj.mode, res.route.link);
				rsObj.adjustZoom();
				rsObj.showProfile(res.route.distance, res.route.time);
				rsObj.showRouteDetail(res.route);
				callback();
			} else if (status.code == "102") {
				alert(MSG_ERR_ROUTE_FAIL);
			} else {
				alert(MSG_ERR_SEARCH_FAIL);
			}
		});
	} else if ( this.mode == "train" ) {
		/* 電車ルート検索 */
		/* 曜日を取得 */
		elm = this.getElmByID("xdw");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var xdw = elm.value;
		/* 表示順を取得 */
		elm = this.getElmByID("xrp");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var xrp = elm.value;
		/* 特急利用を取得 */
		elm = this.getElmByID("xep");
		if (elm.checked) this.cond.push("特急利用");
		var xep = elm.checked ? 1 : 0;
		DmapJSONP.get('http://'+EMAPCGI_DOMAIN+'/dmap_cgi/search_route_train.php', {
			stlat: from.lat,
			stlon: from.lon,
			edlat: to.lat,
			edlon: to.lon,
			datum: 'TOKYO',
			xdw: xdw,
			xrp: xrp,
			xep: xep
		}, function(status, res) {
			if (status.code == "000") {
				rsObj.showProfile();
				rsObj.showRouteDetail(res.route);
				rsObj.route = res.route;
				rsObj.changeResult(0);
				callback();
			} else if (status.code == "31613769") {
				alert(MSG_ERR_TRAIN_WALK_SHORT);
			} else if (status.code == "31619101" || status.code == "31613025" || status.code == "35211009") {
				alert(MSG_ERR_TRAIN_WALK_LONG);
			} else if (String(status.code).substr(0,5) == "35018" || status.code == "31611009" || status.code == "31613274" || status.code == "31613035") {
				alert(MSG_ERR_ROUTE_FAIL);
			} else {
				alert(MSG_ERR_SEARCH_FAIL);
			}
		});
	}
}

/**
 * メッセージを表示します。
 * @param {String} msg メッセージ
 * @return {void}
 */
DmapClassRouteSearch.prototype.showMessage = function(msg) {
	var msg_elm = this.getElmByID("message");
	msg_elm.innerText = msg;
}

/**
 * メッセージを消去します。
 * @return {void}
 */
DmapClassRouteSearch.prototype.removeMessage = function() {
	this.showMessage("");
}

/**
 * ボタンの色をONにします。
 * @param {Object} btn_ele ボタン要素
 * @return {void}
 */
DmapClassRouteSearch.prototype.setButtonColorOn = function(btn_elm) {
	/* ONにしたボタン要素を記憶 */
	this.btn_elm_on = btn_elm;
	addClass(this.btn_elm_on, "on");
}

/**
 * ボタンの色をOFFにします。
 * @return {void}
 */
DmapClassRouteSearch.prototype.setButtonColorOff = function() {
	/* ONのままのボタン要素があれば、デフォルト色に戻す */
	if (this.btn_elm_on) {
		removeClass(this.btn_elm_on, "on");
	}
}

/**
 * ルートを表示します。
 * @param {String} mode ルートモード（walk：歩行者／car：車／train：電車）
 * @param {Object} link 緯度経度オブジェクト
 * @return {void}
 */
DmapClassRouteSearch.prototype.showRoute = function(mode, link) {
	for (var i=0, link_len=link.length; i<link_len; i++) {
		var pllatlons = new Array();
		for (var j=0, line_len=link[i].line.length; j<line_len; j++) {
			pllatlons.push(link[i].line[j]);
			this.zoom_latlon.push(link[i].line[0]);
			if(i == link_len-1 && j == 1) {
				this.zoom_latlon.push(link[i].line[1]);
			}
		}
		var pl = new ZDC.Polyline(pllatlons, this.line_opt[mode]);
		DmapMap.addWidget(pl);
		this.pls.push(pl);
	}
}

/**
 * ルートを消去します。
 * @return {void}
 */
DmapClassRouteSearch.prototype.removeRoute = function() {
	var len = this.pls.length;
	if (len > 0) {
		for (var i=0; i<len; i++) {
			DmapMap.removeWidget(this.pls[i]);
		}
		this.pls = new Array();
	}
}

/**
 * ルート全体を表示できるようズーム調整します。
 * @return {void}
 */
DmapClassRouteSearch.prototype.adjustZoom = function() {
	var adjust = DmapMap.getAdjustZoom(this.zoom_latlon);
	if (adjust) {
		DmapMap.moveLatLon(adjust.latlon);
		DmapMap.setZoom(adjust.zoom);
	} else {
		DmapMap.setZoom(0);
	}
	this.zoom_latlon = new Array();
}

/**
 * ルートプロフィールを表示します。
 * @param {Number} dist 距離（m）
 * @param {Number} time 所要時間（分）
 * @return {void}
 */
DmapClassRouteSearch.prototype.showProfile = function (dist, time) {
	var profile = new Array();
	
	/* 出発地 */
	profile.push('出発地　' + this.point.start.addr);
	/* 目的地 */
	profile.push('目的地　' + this.point.end.addr);
	profile.push('');
	/* 検索条件 */
	profile.push(this.cond.join('<br />'));
	profile.push('');
	/* 距離 */
	if (dist) {
		/* mからKmに変換（10m以下切り上げ） */
		dist = Math.ceil(dist / 10) / 100 + 'Km';
		profile.push(dist);
	}
	/* 時間 */
	if (time) {
		time = '約' + time + '分';
		profile.push(time);
	}
	
	document.getElementById("rs_prf_body").innerHTML = profile.join('<br />');
}

/**
 * ルート詳細を表示します。
 * @param {Object} route ルートオブジェクト
 * @return {void}
 */
DmapClassRouteSearch.prototype.showRouteDetail = function (route) {
	var dtl_elm = document.getElementById("rs_detail");
	var head_elm = document.getElementById("rs_dtl_hd");
	var body_elm = document.getElementById("rs_dtl_body");
	var head_html = body_html = '';
	
	/* ルート詳細を隠す */
	dtl_elm.style.display = 'none';
	/* 車ルート */
	if ( this.mode == 'car' ) {
		/* 詳細用のHTMLを取得する関数 */
		function getListHtmlCar(lat, lon, type, place) {
			return '<tr class="click" onClick="DmapMoveLatlon('+lat+', '+lon+');"><td class="img"><div class="'+type+'">　</div></td><td class="text">'+place+'</td></tr>';
		}
		/* ヘッダー */
		head_html = 'ルート詳細';
		/* 内容 */
		var link = route.link;
		body_html += getListHtmlCar(this.point.start.latlon.lat, this.point.start.latlon.lon, 'start', this.point.start.addr);
		for (var i=0, len=link.length, idx=0; i<len; i++) {
			guidance = link[i].guidance;
			if (guidance) {
				if (guidance.straightFlag === false) {
					body_html += getListHtmlCar(link[i].line[0].lat, link[i].line[0].lon, 'arrow', (guidance.crossName ? guidance.crossName : '交差点'));
				}
			}
		}
		body_html += getListHtmlCar(this.point.end.latlon.lat, this.point.end.latlon.lon, 'end', this.point.end.addr);
		body_html = '<table class="rs_dtl_list"><tbody>' + body_html + '</tbody></table>';
	/* 電車ルート */
	} else if ( this.mode == 'train' ) {
		function getListHtmlTrain(transfer, rosen, from, to, hour, min, fare) {
			var text = '';
			text += from + '～' + to + (rosen ? '（' + rosen + '）' : '') + '<br />';
			text += (hour ? hour + '時間' : '') + min + '分' + (fare ? '　' + fare + '円' : '');
			return '<tr><td class="img"><div class="'+transfer+'">　</div></td><td class="text">'+text+'</td></tr>';
		}
		/* ヘッダー */
		var temp_html, temp_html2;
		var hour, min, rosen, fare, fast, cheap, easy;
		temp_html = temp_html2 = '';
		for (var i=0, route_len=route.length; i<route_len; i++) {
			hour = route[i].time.hour;
			min = route[i].time.min;
			fare = route[i].fare.total;
			fast = route[i].rank.fast;
			cheap = route[i].rank.cheap;
			easy = route[i].rank.easy;
			temp_html += '<span>候補' + (i+1) + '（' + (hour ? hour + '時間' : '') + min + '分' + '）</span>'
			var rank_html = '';
			rank_html += (fast==1)  ? '<span class="fast">　</span>'  : '';
			rank_html += (cheap==1) ? '<span class="cheap">　</span>' : '';
			rank_html += (easy==1)  ? '<span class="easy">　</span>'  : '';
			var time_str = (hour ? hour + '時間' : '') + min + '分';
			var fare_str = (fare ? fare + '円' : '');
			var td_class = (i==route_len-1) ? " no_border" : "";
			temp_html2 += '<tr class="click" onclick="DmapOnClickRouteListRow('+i+')">';
			temp_html2 += '<td class="img'+td_class+'"><div id="rs_rte_list_chk'+i+'">　</div></td>';
			temp_html2 += '<td class="no'+td_class+'"><span id="rs_rte_list_no'+i+'">'+(i+1)+'.</span></td>';
			temp_html2 += '<td class="text'+td_class+'"><span id="rs_rte_list_text'+i+'">'+time_str+'<br />'+fare_str+'</span></td>';
			temp_html2 += '<td class="rank'+td_class+'">'+rank_html+'</td>';
			temp_html2 += '</tr>';
		}
		head_html += '<span id="rs_rte_title">'+temp_html+'</span><a href="javascript:void(0);" id="rs_rte_select" onclick="DmapOnClickRouteSelect();">　</a>';
		head_html += '<table id="rs_rte_list" class="hidden"><tbody>' + temp_html2 + '</tbody></table>';
		/* 内容 */
		var link, transfer, rosen, from, to, hour, min, fare;
		for (var i=0, route_len=route.length; i<route_len; i++) {
			temp_html = '';
			/* 出発地から乗車駅までの歩行者ルート */
			link = route[i].train.link[0];
			transfer = "walk";
			rosen = "";
			from = this.point.start.addr;
			to = link.station.from.name;
			hour = route[i].walk.first.time.hour;
			min = route[i].walk.first.time.min;
			temp_html += getListHtmlTrain(transfer, rosen, from, to, hour, min);
			/* 乗車駅から下車駅までの電車ルート */
			for (var j=0, link_len=route[i].train.link.length; j<link_len; j++) {
				link = route[i].train.link[j];
				transfer = (link.railKind == "徒歩" ? "walk" : "train");
				rosen = (link.railKind == "徒歩" ? "" : link.name);
				from = link.station.from.name;
				to = link.station.to.name;
				hour = link.time.hour;
				min = link.time.min;
				fare = link.fare.total;
				temp_html += getListHtmlTrain(transfer, rosen, from, to, hour, min, fare);
			}
			/* 下車駅から目的地までの歩行者ルート */
			link = route[i].train.link[link_len-1];
			transfer = "walk";
			from = link.station.to.name;
			to = this.point.end.addr;
			hour = route[i].walk.last.time.hour;
			min = route[i].walk.last.time.min;
			temp_html += getListHtmlTrain(transfer, rosen, from, to, hour, min);
			body_html += '<table class="rs_dtl_list"><tbody>' + temp_html + '</tbody></table>';
		}
	}
	
	/* HTMLを挿入 */
	head_elm.innerHTML = head_html;
	body_elm.innerHTML = body_html;
	body_elm.scrollTop = 0;
	if (head_html || body_html) {
		/* ルート詳細を表示する */
		dtl_elm.style.display = 'block';
	}
}

/**
 * 検索結果リストの表示／非表示を切り替えます。
 * @return {void}
 */
DmapClassRouteSearch.prototype.toggleResultList = function () {
	var elm = document.getElementById("rs_rte_list");
	hasClass(elm, "hidden") ? elm.style.display = 'block' : elm.style.display = 'none';
}

/**
 * 検索結果を切り替えます。
 * @param {Number} idx 候補番号
 * @return {void}
 */
DmapClassRouteSearch.prototype.changeResult = function (idx) {
	if (this.mode == "train") {
		/* ルート削除 */
		this.removeRoute();
		/* ルート表示 */
		this.showRoute("train", this.route[idx].train.link);
		this.showRoute("walk",  this.route[idx].walk.first.link);
		this.showRoute("walk",  this.route[idx].walk.last.link);
		this.adjustZoom();
		/* ヘッダー切り替え */
		var title_elm = document.getElementById("rs_rte_title");
		var span_elm = title_elm.getElementsByTagName("span");
		for (var i=0, len=span_elm.length; i<len; i++) {
			var chk_elm = document.getElementById("rs_rte_list_chk"+i);
			var no_elm = document.getElementById("rs_rte_list_no"+i);
			var text_elm = document.getElementById("rs_rte_list_text"+i);
			if (idx == i) {
				span_elm[i].style.display = 'block';
				addClass(chk_elm, "chk");
				removeClass(chk_elm, "chk_no");
				addClass(no_elm, "weight");
				addClass(text_elm, "weight");
			} else {
				span_elm[i].style.display = 'none';
				addClass(chk_elm, "chk_no");
				removeClass(chk_elm, "chk");
				removeClass(no_elm, "weight");
				removeClass(text_elm, "weight");
			}
		}
		/* ルート詳細切り替え */
		var body_elm = document.getElementById("rs_dtl_body");
		var tbl_elm = body_elm.getElementsByTagName("table");
		for (var i=0, len=tbl_elm.length; i<len; i++) {
			if (idx == i) {
				tbl_elm[i].style.display = 'block';
			} else {
				tbl_elm[i].style.display = 'none';
			}
		}
		/* ルート候補リストを消去 */
		document.getElementById("rs_rte_list").style.display = 'none';
	}
}

/**
 * ルートとマーカーを全て消去します。
 * @return {void}
 */
DmapClassRouteSearch.prototype.removeAllWidget = function () {
	/* ルート削除 */
	this.removeRoute();
	/* マーカー削除 */
	this.point.start.removeMarker();
	this.point.end.removeMarker();
}
