/**
 * ページロード時の処理。
 * @return {void}
 */
function DmapOnLoad() {
	/* Cookie情報をhiddenにセット */
	RestoreCookieLog();
	/* 初期表示フラグ */
	var isfirst = (DmapGetValueById('ISFIRST') == '1' ? true : false);
	/* 操作者権限による表示制御 */
	DmapUser = new DmapClassUser();
	DmapRefreshByAuth();
	/* 所属支社位置 */
	var syzloc = DmapGetSyozokuLatLon();
	/* リロード時の現在地 */
	var nowlat = DmapGetValueById('NOWLAT');
	var nowlon = DmapGetValueById('NOWLON');
	/* リロード時の地図位置 */
	var clat = DmapGetValueById('CLAT');
	var clon = DmapGetValueById('CLON');
	var scale = DmapGetValueById('SCALE');
	var hid;
	hid = document.getElementById('CLAT');if (hid) hid.value = '';
	hid = document.getElementById('CLON');if (hid) hid.value = '';
	hid = document.getElementById('SCALE');if (hid) hid.value = '';
	/* 初期表示または、リロード時中心位置がない場合 */
	if (isfirst || !clat || !clon) {
		/* 現在地を取得 */
		var loc = DmapGetLocation();
		if (loc.ret == 0) {
			/* 現在地を中心とする */
			DmapMapOpt.latlon = loc.latlon;
		} else {
			/* 現在地を取得できなかったら所属支社を中心とする */
			DmapMapOpt.latlon = syzloc;
		}
	/* リロード時（中心位置あり） */
	} else {
		/* リロード時の現在地を中心とする */
		DmapMapOpt.latlon = new ZDC.LatLon(clat, clon);
	}
	/* 地図を生成 */
	DmapMap = new ZDC.Map(document.getElementById('map'), DmapMapOpt);
	/* スケールバーを表示 */
	var sbar = new ZDC.ScaleBar({bottom:40,left:10});
	DmapMap.addWidget(sbar);
	/* 地図コントロールを表示 */
	var control = new ZDC.Control(DmapMapControl);
	DmapMap.addWidget(control);
	/* 初期表示または、リロード時中心位置がない場合 */
	if (isfirst || !clat || !clon) {
		/* 現在地にマーカーを表示する */
		if (loc && loc.latlon) {
			DmapPlotLocationMarker(loc.latlon);
		}
	/* リロード時（中心位置あり） */
	} else {
		/* リロード時の縮尺 */
		if (scale != '') {
			DmapMapReloadScale = parseInt(scale);
		}
		/* リロード時の現在地にマーカーを表示する */
		if (nowlat && nowlon) {
			DmapPlotLocationMarker(new ZDC.LatLon(nowlat, nowlon));
		}
	}
	/* 支社ピン表示 */
	if (syzloc) {
		DmapPlotSyozokuPin(syzloc);
	}
	/* 地図にイベントを追加 */
	ZDC.addListener(DmapMap, ZDC.MAP_MOUSEMOVE, DmapOnMouseMove);
	ZDC.addListener(DmapMap, ZDC.MAP_MOUSEUP, DmapOnMouseUp);
	ZDC.addListener(DmapMap, ZDC.MAP_DBLCLICK, DmapOnDblClick);
	ZDC.addListener(DmapMap, ZDC.MAP_RIGHTCLICK, DmapOnRightClick);
	ZDC.addListener(DmapMap, ZDC.MAP_CLICK, DmapOnClick);
	/* documentにイベントを追加 */
	ZDC.addDomListener(document, 'mouseup', DmapOnMouseUp);
	/* 地図以外のホイールイベントを無効化 */
	var area;
	area = document.getElementById('area_top');
	DmapAddEvent(area, 'mousewheel', DmapOnMouseWheel);
	area = document.getElementById('area_right');
	DmapAddEvent(area, 'mousewheel', DmapOnMouseWheel);
	area = document.getElementById('area_bottom');
	DmapAddEvent(area, 'mousewheel', DmapOnMouseWheel);
	/* 訪問先ピン表示 */
	DmapRefreshPins();
	/* 移動距離表示 */
	var kyori = DmapShowIdoKyori();
	/* ON/OFFボタン表示制御 */
	if (DmapIsShowPointNameOn()) {
		DmapSetShowPointNameOnOff(true);
	}
	if (DmapIsShowGyosyuOn()) {
		DmapSetShowGyosyuOnOff(true);
	}
	if (kyori) {
		/* 利用状況ログ */
		DmapLogCount(12);
	} else {
		if (isfirst) {
			/* 利用状況ログ */
			DmapLogCount(1);
		}
	}
}

/**
 * グループに属するピンのオブジェクトを配列で返却します。
 * @param {String} gid グループID
 * @return {Array}
 */
function DmapGetGroupPinList(gid) {
	var ar = new Array();
	var len = DmapPinList.Pins.length;
	if (len) {
		var n = 0;
		for (var i = 0; i < len; i++) {
			if (DmapPinList.Pins[i].inGroup() && DmapPinList.Pins[i].gid == gid) {
				ar[n] = DmapPinList.Pins[i];
				n++;
			}
		}
	}
	return ar;
}

/**
 * 訪問先ピンを取得して地図上に表示します。
 * @return {void}
 */
function DmapRefreshPins() {
	/* ピンを消去 */
	DmapRemovePins();
	/* ピンの情報をhiddenから取得 */
	DmapPinList = new DmapClassPinList();
	/* ピンを地図上に配置 */
	DmapPlotPins();
	/* 詳細情報を表示 */
	DmapRefreshPinList();
}

/**
 * 訪問先ピンを地図上に表示します。
 * @return {void}
 */
function DmapPlotPins() {
	var latlons = new Array();
	/* 支社ピン */
	var syz = DmapGetSyozokuLatLon();
	if (syz) {
		latlons.push(syz);
		/* 上方向offset */
		syz = new ZDC.LatLon(parseFloat(syz.lat)+PIN_OFFSET_LAT, syz.lon);
		latlons.push(syz);
	}
	/* 訪問先ピン */
	var len = DmapPinList.Pins.length;
	if (len > 0) {
		for (var i = len-1; i >= 0; i--) {
			if (DmapPinList.Pins[i].plot) {
				DmapPinList.Pins[i].newWidget();
				latlons.push(DmapPinList.Pins[i].latlon);
				/* 上方向offset */
				var ll = new ZDC.LatLon(parseFloat(DmapPinList.Pins[i].latlon.lat)+PIN_OFFSET_LAT, DmapPinList.Pins[i].latlon.lon);
				latlons.push(ll);
			}
		}
		if (DmapSyozokuPin) latlons.push(DmapSyozokuPin.getLatLon());
		var result = DmapMap.getAdjustZoom(latlons, {fix:true});
		if (result) {
			DmapMap.setZoom(result.zoom);
		} else {
			DmapMap.setZoom(0);
		}
	} else {
		DmapMap.setZoom(DEF_ZOOM);
	}
	/* リロード時の縮尺 */
	if (DmapMapReloadScale >= 0) {
		DmapMap.setZoom(DmapMapReloadScale);
		DmapMapReloadScale = -1;
	}
}

/**
 * 地図上のピンを全て消去します。
 * @return {void}
 */
function DmapRemovePins() {
	if (!DmapPinList || !DmapPinList.Pins || !DmapPinList.Pins.length) return;
	for (var i = 0; i < DmapPinList.Pins.length; i++) {
		if (DmapPinList.Pins[i].widgetPin) {
			DmapMap.removeWidget(DmapPinList.Pins[i].widgetPin);
			DmapPinList.Pins[i].widgetPin = null;
		}
	}
}

/**
 * 訪問先詳細情報（一覧）の表示切り替えボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickSwitchPinList() {
	DmapPinListSimple = (!DmapPinListSimple);
	DmapRefreshPinList();
}

/**
 * 訪問先詳細情報（一覧）を表示します。
 * @return {void}
 */
function DmapRefreshPinList() {
	var len = DmapPinList.Pins.length;
	var div = document.getElementById("list_div");
	if (!div) return;
	/* div内をクリア */	
	DmapClearListDiv();
	/* ヘッダ表示 */
	var hd = document.createElement('div');
	hd.id = 'dtl_hd';
	if (len == 0) {
		hd.innerHTML = '詳細情報';
	} else {
		hd.innerHTML = '詳細情報'
			+ '<a href="javascript:void(0);" id="dtl_sw" onClick="DmapOnClickSwitchPinList();" onFocus="this.blur();">　</a>'
		;
	}
	div.appendChild(hd);
	/* 一覧表示 */
	var body = document.createElement('div');
	body.id = 'dtl_body';
	if (len) {
		var tbl = document.createElement("table");
		tbl.id = "dtl_list";
		for (var i = 0; i < len; i++) {
			var p = DmapPinList.Pins[i];
			var tr = tbl.insertRow();
			var td = tr.insertCell();
			var html = '';
			html += ''
				+ '<a href="javascript:void(0);" id="dtl_i_'+p.seq+'" class="dtl_i" onClick="DmapOnClickInfo('+p.seq+');" onFocus="this.blur();">'
				+ '　</a>'
				+ '<div class="dtl_name">'
				+ '<a href="javascript:void(0);" onClick="DmapMoveCenterToPin('+p.seq+');" onFocus="this.blur();">'
				+ p.num_on_list+'.'+p.name
				+ '</a>'
				+ '</div>'
			;
			if (!DmapPinListSimple) {
				if (p.adrk) html += '<div class="dtl_adrk">'+ p.adrk + '</div>';
				if (p.tel) html += '<div class="dtl_tel">'+ p.tel + '</div>';
				if (p.formatAtr()) html += '<div class="dtl_atr">【'+ p.formatAtr() + '】</div>';
			}
			td.innerHTML = html;
		}
		body.appendChild(tbl);
	} else {
	}
	div.appendChild(body);
}

/**
 * 一覧をクリアします。
 * @return {void}
 */
function DmapClearListDiv() {
	var div = document.getElementById("list_div");
	if (!div) return;
	for (var i = div.childNodes.length-1; i >= 0; i--) {
		div.removeChild(div.childNodes[i]);
	}
}

/**
 * 訪問先詳細情報（一覧）を、指定ピンの位置までスクロールします。
 * @param {Number} seq ピンの連番
 * @return {void}
 */
function DmapPinListScrollTo(seq) {
	var a = document.getElementById('dtl_i_'+seq);
	if (a) a.focus();
}

/**
 * GPS現在地取得関数から現在地を取得し、マーカーを表示します。
 * @param {Boolean} alt true：現在地取得失敗時にアラート表示する。
 * @return {Array} ret：結果コード、latlon：ZDC.LatLonオブジェクト
 */
function DmapGetLocation(alt) {
	var result = getCurrentPosition(GPS_PARAM.waitTime, GPS_PARAM.expire, GPS_PARAM.datum);
	if (result[0] == 0) {
		var lat = result[1];
		var lon = result[2];
		var loc = new ZDC.LatLon(lat,lon);
		if (lat && lon) {
			var hid;
			hid = document.getElementById('NOWLAT');
			if (hid) hid.value = lat;
			hid = document.getElementById('NOWLON');
			if (hid) hid.value = lon;
			return {ret:0, latlon:loc};
		}
		DmapPlotLocationMarker(loc);
		return {ret:1};
	} else if (result[0] == 1 && alt) {
		alert(MSG_ERR_LOC_NG);
	} else if (result[0] == 2) {
		alert(MSG_ERR_LOC_FAIL);
	}
	return {ret:parseInt(result[0])};
}

/**
 * 所属支社の緯度経度を返却します。
 * @return {Object} ZDC.LatLonオブジェクト
 */
function DmapGetSyozokuLatLon() {
	var lat = DmapGetValueById('SLAT');
	var lon = DmapGetValueById('SLON');
	if (lat && lon) {
		return new ZDC.LatLon(lat,lon);
	} else {
		return null;
	}
}

/**
 * ピンの位置へ地図を移動させます。
 * @param {Number} seq ピンの連番
 * @return {void}
 */
function DmapMoveCenterToPin(seq) {
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	DmapMap.moveLatLon(p.latlon);
	p.moveTop();
}

/**
 * ピンクリック時の処理。
 * @return {void}
 */
function DmapOnClickPin() {
	/* 地図無効化中は何もしない */
	if (!DmapMapEventEnable) return;
	/* 表示位置修正モードの時は何もしない */
	if (DmapMovePinMode) return;
	/* 表示済みのランチャーを消去 */
	DmapRemoveLauncher();
	/* 表示済みのピン一覧を消去 */
	DmapRemovePinSelect();
	/* 該当ピンを中心に */
	DmapMoveCenterToPin(this.seq);
//	/* ピン情報を取得 */
//	var p = DmapPinList.Pins[seq];
//	if (!p || !p.latlon) return;
	/* グループの場合はピン一覧を表示する */
	if (this.inGroup()) {
		DmapShowPinSelect(this.seq, 'DmapOnClickPinSelect', 'DmapRemovePinSelect');
	/* 単独の場合はポイントランチャーを表示する */
	} else {
		DmapShowLauncher(this.seq);
	}
}

/**
 * 「i」クリック時の処理。
 * @param {Number} seq ピンの連番
 * @return {void}
 */
function DmapOnClickInfo(seq) {
	/* 表示位置修正モードの時は何もしない */
	if (DmapMovePinMode) return;
	/* 表示済みのランチャーを消去 */
	DmapRemoveLauncher();
	/* 表示済みのピン一覧を消去 */
	DmapRemovePinSelect();
	/* 該当ピンを中心に */
	DmapMoveCenterToPin(seq);
	/* ピン情報を取得 */
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	/* ポイントランチャーを表示する */
	DmapShowLauncher(seq);
}

/**
 * グループのピン一覧を表示します。
 * @param {Number} seq ピンの連番
 * @param {Function} func リンククリック時に呼び出す関数名
 * @param {String} close 閉じる時に呼び出す関数名
 * @return {void}
 */
function DmapShowPinSelect(seq, func, close) {
	/* ピン情報を取得 */
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	if (!p.inGroup()) return;
	/* グループのピン（複数）を取得 */
	var plist = DmapGetGroupPinList(p.gid);
	/* 一覧を生成 */
	var html = '';
	html += '<div id="p_select_hd">';
	html += '<a id="p_select_close" href="javascript:void(0);" onClick="'+close+'();">　</a>';
	html += '</div>';
	html += '<div id="p_select">';
	html += '<table id="p_select_tbl">';
	for (var i = 0; i < plist.length; i++) {
		html += '<tr>';
		html += '<td class="p_select_cell">';
		html += '<a href="javascript:void(0);" class="p_select_a" onClick="'+func+'('+plist[i].seq+');" onFocus="this.blur();">';
		html += plist[i].name;
		html += '</a>';
		html += '</td>';
		html += '</tr>';
	}
	html += '</table>';
	html += '</div>';
	/* 表示位置（緯度経度）を求める */
	var ll = p.latlon;
	/* offsetを求める */
	var listsize = DmapGetHTMLSize(html);
	/* 一覧を表示 */
	DmapPinSelect = new ZDC.MsgInfo(p.latlon, {
		html: html,
		offset: new ZDC.Pixel(0, -25),
		closeBtn: false
	});
	DmapMap.addWidget(DmapPinSelect);
	DmapPinSelect.open();
	/* フキダシ以外を無効化 */
	DmapDisableTop();
	DmapDisableRight();
	DmapDisableBottom();
	DmapDisableMapEvent();
}

/**
 * グループピン一覧を消去します。
 * @return {void}
 */
function DmapRemovePinSelect() {
	if (DmapPinSelect) {
		DmapMap.removeWidget(DmapPinSelect);
		DmapPinSelect = null;
	}
	/* 無効化を元に戻す */
	DmapEnableTop();
	DmapEnableRight();
	DmapEnableBottom();
	DmapEnableMapEvent();
}

/**
 * グループピン一覧のクリック時の処理。
 * @param {Number} seq ピンの連番
 * @return {void}
 */
function DmapOnClickPinSelect(seq) {
	/* 表示済みのランチャーを消去 */
	DmapRemoveLauncher();
	/* 表示済みのピン一覧を消去 */
	DmapRemovePinSelect();
	/* 該当ピンを中心に */
	DmapMoveCenterToPin(seq);
	/* ポイントランチャー表示 */
	DmapShowLauncher(seq);
}

/**
 * ポイントランチャーを表示します。
 * @param {Number} seq ピンの連番
 * @return {void}
 */
function DmapShowLauncher(seq) {
	var cnt,cond,i;
	/* ピン情報を取得 */
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	/* 詳細情報頭出し */
	DmapPinListScrollTo(p.seq);
	/* ポイントランチャー生成 */
	var html = '';
	/* 名称 */
	html += '<div id="pl_name">'+p.name+'</div>';
	/* 属性アイコン */
	var atr_idx = new Array();
	for (i = 0; i < PIN_ATR_COUNT; i++) {
		if (p.atr[i] == COND_ENABLE || p.atr[i] == COND_DISABLE) atr_idx.push(i);
	}
	cnt = atr_idx.length;
	if (cnt > 0) {
		html += '<div id="pl_atr">';
		for (i = 0; i < cnt; i++) {
			cond = p.atr[atr_idx[i]];
			html += '<span class="pl_atr'+atr_idx[i]+'_'+cond+'">　</span>';
		}
		html += '</div>';
	}
	html += '</td></tr>';
	/* 機能メニュー */
	html += '<tr><td>';
	var icon_idx = new Array();
	for (i = 0; i < PIN_ICON_COUNT; i++) {
		if (p.icon[i] == COND_ENABLE || p.icon[i] == COND_DISABLE) icon_idx.push(i);
	}
	cnt = icon_idx.length;
	if (cnt > 0) {
		html += '<table id="pl_menu">';
		html += '<tr>';
		for (i = 0; i < cnt; i++) {
			cond = p.icon[icon_idx[i]];
			html += '<td>';
			if (cond == COND_ENABLE) {
				html += '<a href="javascript:void(0);" class="pl_menu'+icon_idx[i]+'_'+cond+'"'
						+' onClick="DmapClickMenu('+p.seq+','+icon_idx[i]+');" onFocus="this.blur();">　</a>';
			} else {
				html += '<span class="pl_menu'+icon_idx[i]+'_'+cond+'">　</span>';
			}
			html += '</td>';
		}
		html += '</tr>';
		html += '<tr>';
		for (i = 0; i < cnt; i++) {
			html += '<th>'+p.icon_lbl[icon_idx[i]]+'</th>';
		}
		html += '</tr>';
		html += '</table>';
	}
	html += '</td></tr>';
	html += '</table>';
	/* ポイントランチャー表示 */
	html = '<div id="pl_div">'+html+'</div>';
	DmapLauncher = new ZDC.MsgInfo(p.latlon, {
		html: html,
		offset: new ZDC.Pixel(0, -25)
	});
	DmapMap.addWidget(DmapLauncher);
	DmapLauncher.open();
	/* 社内情報検索明細を閉じる */
	DmapSrchPointDtlOff();
	/* ポイント表示変更ダイアログを閉じる */
	DmapCloseSelPoint();
}
/**
 * ポイントランチャーを消去します。
 * @return {void}
 */
function DmapRemoveLauncher() {
	if (DmapLauncher) {
		DmapMap.removeWidget(DmapLauncher);
		DmapLauncher = null;
	}
}

/**
 * ポイントランチャー機能ボタンがクリックされた時の処理。
 * @param {Number} seq ピンの連番
 * @param {Number} idx 機能番号
 * @return {void}
 */
function DmapClickMenu(seq, idx) {
	var e,s,btn;
	var p = DmapPinList.Pins[seq];if(!p) return;
	/* ルート表示 */
	if (idx == 9) {
		/* ルート表示ダイアログを開く */
		DmapStartPinRoute(seq);
		return;
	}
	switch (idx) {
		/* お客さま情報 */
		case 0:
			btn = 'BTNKYAKU';
			/* 職員コード */
			e = document.getElementById('HIIE5001');
			e.value = p.syoku;
			/* 分類コード */
			e = document.getElementById('HIIF0111');
			e.value = p.buncd;
			/* 見込客番号 */
			e = document.getElementById('HIIF0551');
			e.value = p.mkno;
			/* 顧客番号 */
			e = document.getElementById('HICYA');
			e.value = p.cya;
			/* 担当フラグ */
			e = document.getElementById('HIISTAN');
			e.value = p.istan;
			/* 利用状況ログ */
			DmapLogCount(15);
			break;
		/* 税理士情報 */
		case 1:
			btn = 'BTNZEIRI';
			/* 税理士登録番号 */
			e = document.getElementById('HIIE6001');
			e.value = p.zno;
			/* 利用状況ログ */
			DmapLogCount(17);
			break;
		/* 診査医情報 */
		case 2:
			btn = 'BTNSNSAI';
			/* 診査医コード */
			e = document.getElementById('HIM10091');
			e.value = p.scd;
			/* 利用状況ログ */
			DmapLogCount(19);
			break;
		/* お客さま訪問 */
		case 3:
			btn = 'BTNHOMON_dummy';
			/* 詳細情報行番号 */
			e = document.getElementById('SYOROW');
			e.value = p.seq;
			/* 利用状況ログ */
			DmapLogCount(16);
			/* フラグリセット */
			resetAllFlg();
			break;
		/* 代理店ポータル */
		case 4:
			btn = 'BTNDAIPO';
			/* 代理店コード */
			e = document.getElementById('HIIK0011');
			e.value = p.dcd;
			/* 職員コード */
			e = document.getElementById('HIIE5001');
			e.value = p.syoku;
			/* 利用状況ログ */
			DmapLogCount(18);
			break;
		/* ホームページ */
		case 5:
			btn = 'BTNHP';
			/* 名称 */
			e = document.getElementById('HINAME');
			e.value = p.name;
			/* 住所 */
			e = document.getElementById('HIADD');
			e.value = p.adrk;
			/* URL */
			e = document.getElementById('HIURL');
			e.value = p.url;
			/* 利用状況ログ */
			DmapLogCount(20);
			break;
		/* スケジュール */
		case 6:
			btn = 'BTNSCHED';
			/* 見込客番号 */
			e = document.getElementById('HIIF0551');
			e.value = p.mkno;
			/* 法人個人区分 */
			e = document.getElementById('HIIF0506');
			e.value = p.hkkbn;
			/* 見込客名称 */
			e = document.getElementById('HINAME');
			e.value = p.name;
			/* 利用状況ログ */
			DmapLogCount(13);
			break;
		/* マイ・ノート */
		case 7:
			btn = 'BTNMN';
			/* 見込客番号 */
			e = document.getElementById('HIIF0551');
			e.value = p.mkno;
			/* 利用状況ログ */
			DmapLogCount(14);
			break;
		/* 活動ガイド ※未実装 */
		case 8:
			/* 利用状況ログ */
			DmapLogCount(21);
			break;
	}
	/* 隠しボタンイベント発生 */
	if (btn) {
		var b = document.getElementById(btn);
		if (b) {
			b.click();
			return;
		}
	}
}

/**
 * 操作者権限に基づいてをボタン等を表示制御します。
 * @return {void}
 */
function DmapRefreshByAuth() {
	/* 入力欄 */
	var inp = document.getElementById('IE5002_disp');
	if (!DmapUser.isSisyaEnable()) {
		inp.readOnly = true;
		inp.className = 'inp_readonly';
	}
	inp = document.getElementById('IE5003_disp');
	if (!DmapUser.isKaEnable()) {
		inp.readOnly = true;
		inp.className = 'inp_readonly';
	}
	inp = document.getElementById('IE50012_disp');
	if (!DmapUser.isSyokuinEnable()) {
		inp.readOnly = true;
		inp.className = 'inp_readonly';
	}
	/* 右エリアのボタン */
	var rb_div = document.getElementById('rb_div');
	rb_div.innertHTML = '';
	var html = '';
	if (DmapUser.isProper()) {
		html += '<a href="javascript:void(0);" id="rb_selp_dlg" onClick="DmapOnClickSelPoint();" onFocus="this.blur();">　</a>';
		html += '<a href="javascript:void(0);" id="rb_visit" onClick="DmapOnClickVisitPlan();" onFocus="this.blur();">　</a>';
		html += '<a href="javascript:void(0);" id="rb_rt" onClick="DmapOnClickRouteSearch();" onFocus="this.blur();">　</a>';
	} else if (DmapUser.isAgent()) {
		html += '<a href="javascript:void(0);" id="rb_visit" onClick="DmapOnClickVisitPlan();" onFocus="this.blur();">　</a>';
		html += '<a href="javascript:void(0);" id="rb_selp_ki" onClick="DmapOnClickSpAgent(1);" onFocus="this.blur();">　</a>';
		html += '<a href="javascript:void(0);" id="rb_selp_zei" onClick="DmapOnClickSpAgent(2);" onFocus="this.blur();">　</a>';
		html += '<a href="javascript:void(0);" id="rb_selp_sin" onClick="DmapOnClickSpAgent(3);" onFocus="this.blur();">　</a>';
		html += '<a href="javascript:void(0);" id="rb_rt" onClick="DmapOnClickRouteSearch();" onFocus="this.blur();">　</a>';
	}
	rb_div.innerHTML = html;
}

/**
 * 「ポイント表示変更」ボタン押下時の処理。
 * @return {void}
 */
function DmapOnClickSelPoint() {
	/* ダイアログ */
	var dlg = document.getElementById('sp_dlg');
	/* ボタン初期化 */
	for (var i = 1; i <= 7; i++) {
		/* 条件１ */
		var btn = document.getElementById('sp_cond1_'+i);
		if (btn) {
			switch (i) {
				case 1:
					if (DmapUser.getSPCondPattern() == 2) {
						DmapSPCondBtnCtrl('1', i, 'dis');
					} else {
						DmapSPCondBtnCtrl('1', i, 'ena');
					}
					break;
				default:
					DmapSPCondBtnCtrl('1', i, 'ena');
			}
		}
		/* 条件１明細 */
		btn = document.getElementById('sp_cond1d_'+i);
		if (btn) {
			/* 既契約(企保のみ)は非活性にする */
			if (i == 3) {
				DmapSPCondBtnCtrl('1d', i, 'dis');
			/* それ以外は活性 */
			} else {
				DmapSPCondBtnCtrl('1d', i, 'ena');
			}
		}
		/* 条件２ */
		btn = document.getElementById('sp_cond2_'+i);
		if (btn) {
			switch (i) {
				case 2:
				case 5:
					if (DmapUser.getSPCondPattern() == 2) {
						DmapSPCondBtnCtrl('2', i, 'dis');
					} else {
						DmapSPCondBtnCtrl('2', i, 'ena');
					}
					break;
				default:
					DmapSPCondBtnCtrl('2', i, 'ena');
			}
		}
	}
	/* 明細非表示 */
	DmapCloseSPCond1Dtl();
	/* 条件２（エージェント専用） */
	var cond2ex = document.getElementById('sp_dlg_cond2ex');
	if (cond2ex) {
		if (DmapUser.getSPCondPattern() == 3) {
			cond2ex.style.display = 'block';
		} else {
			cond2ex.style.display = 'none';
		}
	}
	/* ダイアログ表示 */
	dlg.style.display = 'block';
}

/**
 * ポイント表示変更ダイアログを閉じる。
 * @return {void}
 */
function DmapCloseSelPoint() {
	var dlg = document.getElementById('sp_dlg');
	dlg.style.display = 'none';
}

/**
 * ポイント表示変更条件１明細を開く。
 * @return {void}
 */
function DmapOpenSPCond1Dtl() {
	var div = document.getElementById('sp_dlg_cond1_dtl');
	/* 明細の状態をリフレッシュ */
	DmapSPCond1DtlRefresh();
	/* 明細表示 */
	div.style.display = 'block';
}

/**
 * ポイント表示変更条件１明細の状態を、条件１選択状態に応じて制御する。
 * @return {void}
 */
function DmapSPCond1DtlRefresh() {
	/* 「ターゲット企業」が選択されていたら、「既契約(企保のみ)」を活性にする */
	var c1 = document.getElementById('sp_cond1_1');
	var d3 = document.getElementById('sp_cond1d_3');
	if (c1 && d3) {
		/* 「ターゲット企業」選択中 */
		if (c1.className == 'sp_cond_sel') {
			if (d3.className == 'sp_cond_dis') {
				DmapSPCondBtnCtrl('1d', 3, 'ena');
			}
		/* 「ターゲット企業」未選択 */
		} else {
			//			if (d3.className == 'sp_cond_sel') {
			//				DmapSPCondBtnCtrl('1d', 1, 'sel');
			//			}
			DmapSPCondBtnCtrl('1d', 3, 'dis');
		}
	}
}

/**
 * ポイント表示変更条件１明細を閉じる。
 * @return {void}
 */
function DmapCloseSPCond1Dtl() {
	var div = document.getElementById('sp_dlg_cond1_dtl');
	div.style.display = 'none';
	/* 選択状態を初期化する */
	for (var i = 1; i <= 4; i++) {
		DmapSPCondBtnCtrl('1d', i, 'ena');
	}
}

/**
 * ポイント表示変更条件ボタンの制御。
 * @param {String} cond 条件種別（1：条件１／1d：条件１明細／2：条件２）
 * @param {Number} idx ボタン番号(1～6)
 * @param {String} status ボタンの状態（ena：活性／sel：選択／dis：非活性）
 * @return {void}
 */
function DmapSPCondBtnCtrl(cond, idx, status) {
	var func, btn;
	switch (cond) {
		case '1':
			btn = document.getElementById('sp_cond1_'+idx);
			break;
		case '1d':
			btn = document.getElementById('sp_cond1d_'+idx);
			break;
		case '2':
			btn = document.getElementById('sp_cond2_'+idx);
			break;
	}
	if (!btn) return;
	switch (status) {
		case 'ena':
			btn.className = 'sp_cond_ena';
			btn.style.cursor = 'pointer';
			break;
		case 'sel':
			btn.className = 'sp_cond_sel';
			btn.style.cursor = 'pointer';
			break;
		case 'dis':
			btn.className = 'sp_cond_dis';
			btn.style.cursor = 'default';
			break;
	}
}

/**
 * ポイント表示変更条件１の選択数を返却します。
 * @return {Number} 選択されている件数
 */
function DmapSPCond1SelectedCount() {
	var count = 0;
	for (var i = 1; i <= 6; i++) {
		var btn = document.getElementById('sp_cond1_'+i);
		if (!btn) break;
		if (btn.className == 'sp_cond_sel') {
			count++;
		}
	}
	return count;
}

/**
 * ポイント表示変更条件２の選択数を返却します。
 * @return {Number} 選択されている件数
 */
function DmapSPCond2SelectedCount() {
	var count = 0;
	for (var i = 1; i <= 7; i++) {
		var btn = document.getElementById('sp_cond2_'+i);
		if (!btn) break;
		if (btn.className == 'sp_cond_sel') {
			count++;
		}
	}
	return count;
}

/**
 * ポイント表示変更条件１を全て選択解除します。
 * @return {void}
 */
function DmapNonSelectSPCond1() {
	for (var i = 1; i <= 6; i++) {
		var btn = document.getElementById('sp_cond1_'+i);
		if (btn) {
			if (btn.className == 'sp_cond_sel') {
				DmapSPCondBtnCtrl('1', i, 'ena');
			}
		}
	}
	DmapCloseSPCond1Dtl();
}

/**
 * ポイント表示変更条件２を全て選択解除します。
 * @return {void}
 */
function DmapNonSelectSPCond2() {
	for (var i = 1; i <= 7; i++) {
		var btn = document.getElementById('sp_cond2_'+i);
		if (btn) {
			if (btn.className == 'sp_cond_sel') {
				DmapSPCondBtnCtrl('2', i, 'ena');
			}
		}
	}
}

/**
 * ポイント表示変更条件１ボタンクリック時の処理。
 * @param {Number} idx ボタン番号(1～6)
 * @return {void}
 */
function DmapOnClickSpCond1(idx) {
	var btn = document.getElementById('sp_cond1_'+idx);
	if (!btn) return;
	if (btn.className == 'sp_cond_dis') return;
	/* 選択済みの場合 */
	if (btn.className == 'sp_cond_sel') {
		/* 選択解除 */
		DmapSPCondBtnCtrl('1', idx, 'ena');
		/* 選択数が０になったら明細を閉じる */
		if (DmapSPCond1SelectedCount() == 0) {
			DmapCloseSPCond1Dtl();
		}
	/* 未選択の場合 */
	} else {
		/* 「決算前」「決算後」 */
		if (DmapSPCond1KessanConf(idx)) {
		/* ２つまで選択可 */
		} else if (DmapSPCond1SelectedCount() < 2) {
			/* 選択 */
			DmapSPCondBtnCtrl('1', idx, 'sel');
			/* 明細表示 */
			DmapOpenSPCond1Dtl();
			/* 条件２をクリア */
			DmapNonSelectSPCond2();
		} else {
			alert(MSG_ALERT_SPCOND_LIMIT);
		}
	}
	/* 明細の状態をリフレッシュ */
	DmapSPCond1DtlRefresh();
}

/**
 * ポイント表示変更条件１ボタン「決算前」「決算後」同時選択不可の処理。
 * @param {Number} idx ボタン番号(1～6)
 * @return {void}
 */
function DmapSPCond1KessanConf(idx) {
	if (idx == SP_IDX_KESSANMAE || idx == SP_IDX_KESSANGO) {
		var at = (idx == SP_IDX_KESSANMAE ? SP_IDX_KESSANGO : SP_IDX_KESSANMAE);
		var btn = document.getElementById('sp_cond1_'+at);
		if (btn.className == 'sp_cond_sel') {
			DmapSPCondBtnCtrl('1', at, 'ena');
			DmapSPCondBtnCtrl('1', idx, 'sel');
			return true;
		}
	}
	return false;
}

/**
 * ポイント表示変更条件１明細ボタンクリック時の処理。
 * @param {Number} idx ボタン番号(1～4)
 * @return {void}
 */
function DmapOnClickSpCond1Dtl(idx) {
	var btn = document.getElementById('sp_cond1d_'+idx);
	if (!btn) return;
	if (btn.className == 'sp_cond_dis') return;
	/* 選択済みの場合 */
	if (btn.className == 'sp_cond_sel') {
	/* 未選択の場合 */
	} else {
		/* 選択 */
		for (var i = 1; i <= 4; i++) {
			var c = document.getElementById('sp_cond1d_'+i);
			if (!c) return;
			if (i == idx) {
				DmapSPCondBtnCtrl('1d', i, 'sel');
			} else {
				if (c.className == 'sp_cond_sel') {
					DmapSPCondBtnCtrl('1d', i, 'ena');
				}
			}
		}
	}
}

/**
 * ポイント表示変更条件２ボタンクリック時の処理。
 * @param {Number} idx ボタン番号(1～7)
 * @return {void}
 */
function DmapOnClickSpCond2(idx) {
	var btn = document.getElementById('sp_cond2_'+idx);
	if (!btn) return;
	if (btn.className == 'sp_cond_dis') return;
	/* 選択済みの場合 */
	if (btn.className == 'sp_cond_sel') {
	/* 未選択の場合 */
	} else {
		/* 選択 */
		for (var i = 1; i <= 7; i++) {
			var c = document.getElementById('sp_cond2_'+i);
			if (!c) return;
			if (i == idx) {
				DmapSPCondBtnCtrl('2', i, 'sel');
			} else {
				if (c.className == 'sp_cond_sel') {
					DmapSPCondBtnCtrl('2', i, 'ena');
				}
			}
		}
		/* 条件１をクリア */
		DmapNonSelectSPCond1();
	}
}

/**
 * ポイント表示変更「表示」クリック時の処理。
 * @return {void}
 */
function DmapOnClickSpOK() {
	var sel_1 = false;
	var sel_2 = false;
	var sel_d1 = false;
	var joken11 = new Array();
	var joken12 = new Array();
	var joken2 = new Array();
	var val;
	/* 条件１の選択状態を取得 */
	for (var i = 1; i <= 6; i++) {
		var cond = document.getElementById('sp_cond1_'+i);
		if (cond) {
			if (cond.className == 'sp_cond_sel') {
				sel_1 = true;
				joken11[i-1] = '1';
			} else {
				joken11[i-1] = '0';
			}
		}
	}
	/* 条件１明細の選択状態を取得 */
	for (var i = 1; i <= 4; i++) {
		var cond = document.getElementById('sp_cond1d_'+i);
		if (cond) {
			if (cond.className == 'sp_cond_sel') {
				sel_d1 = true;
				joken12[i-1] = '1';
			} else {
				joken12[i-1] = '0';
			}
		}
	}
	/* 条件２の選択状態を取得 */
	for (var i = 1; i <= 7; i++) {
		var cond = document.getElementById('sp_cond2_'+i);
		if (cond) {
			if (cond.className == 'sp_cond_sel') {
				sel_2 = true;
				joken2[i-1] = '1';
			} else {
				joken2[i-1] = '0';
			}
		}
	}
	/* 一つも選択されていなかったらエラー */
	if (!sel_1 && !sel_2) {
		alert(MSG_ERR_SELECT_POINT_NOSEL);
		return;
	}
	if (sel_1 && !sel_d1) {
		alert(MSG_ERR_SELECT_POINT_NODTL);
		return;
	}
	/* 縮尺チェック */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_SELECT_POINT.min && z <= NGZOOM_SELECT_POINT.max) {
		alert(MSG_ERR_SELECT_POINT_NGZOOM);
		return;
	}
	/* 入力チェック */
	val = DmapGetValueById('IE5002_disp');
	if (val.trim() == '') {
		alert(MSG_ERR_SISYA_EMPTY);
		return;
	}
	val = DmapGetValueById('IE5003_disp');
	if (val.trim() == '') {
		alert(MSG_ERR_KA_EMPTY);
		return;
	}
	if (joken2[4] == '1' || joken2[6] == '1') {
		val = DmapGetValueById('IE50012_disp');
		if (val.trim() == '') {
			alert(MSG_ERR_SYOKUIN_EMPTY);
			return;
		}
	}
	/* 地図表示範囲を取得 */
	var box = DmapMap.getLatLonBox();
	var ltlat = DmapDegFormat(box.getMax().lat);
	var ltlon = DmapDegFormat(box.getMin().lon);
	var rblat = DmapDegFormat(box.getMin().lat);
	var rblon = DmapDegFormat(box.getMax().lon);
	/* hiddenに書き込み */
	var hid;
	hid = document.getElementById('CLAT');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lat);
	hid = document.getElementById('CLON');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lon);
	hid = document.getElementById('SCALE');
	if (hid) hid.value = DmapMap.getZoom();
	hid = document.getElementById('LTLAT');
	if (hid) hid.value = ltlat;
	hid = document.getElementById('LTLON');
	if (hid) hid.value = ltlon;
	hid = document.getElementById('RBLAT');
	if (hid) hid.value = rblat;
	hid = document.getElementById('RBLON');
	if (hid) hid.value = rblon;
	hid = document.getElementById('JOKEN11');
	if (hid) hid.value = joken11.join('');
	hid = document.getElementById('JOKEN12');
	if (hid) hid.value = joken12.join('');
	hid = document.getElementById('JOKEN2');
	if (hid) hid.value = joken2.join('');
	/* 利用状況ログ */
	DmapLogCount(8);
	/* フラグリセット */
	resetAllFlg();
	/* 隠しボタンイベント発生 */
	var b = document.getElementById('BTNPCHG_dummy');
	if (b) {
		b.click();
	}
}

/**
 * ポイント表示変更（エージェント）「既契約」「税理士」「診査医」クリック時の処理。
 * @param {Number} idx ボタン番号（1：既契約、2：税理士、3：診査医）
 * @return {void}
 */
function DmapOnClickSpAgent(idx) {
	var val;
	/* 縮尺チェック */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_SELECT_POINT.min && z <= NGZOOM_SELECT_POINT.max) {
		alert(MSG_ERR_SELECT_POINT_NGZOOM);
		return;
	}
	/* 入力チェック */
	val = DmapGetValueById('IE5002_disp');
	if (val.trim() == '') {
		alert(MSG_ERR_SISYA_EMPTY);
		return;
	}
	val = DmapGetValueById('IE5003_disp');
	if (val.trim() == '') {
		alert(MSG_ERR_KA_EMPTY);
		return;
	}
	if (idx == 1) {
		val = DmapGetValueById('IE50012_disp');
		if (val.trim() == '') {
			alert(MSG_ERR_SYOKUIN_EMPTY);
			return;
		}
	}
	joken11 = '000000';
	joken12 = '0000';
	switch (idx) {
		case 1:
			joken2 = '0000001';
			break;
		case 2:
			joken2 = '0001000';
			break;
		case 3:
			joken2 = '0000010';
			break;
	}
	/* 地図表示範囲を取得 */
	var box = DmapMap.getLatLonBox();
	var ltlat = DmapDegFormat(box.getMax().lat);
	var ltlon = DmapDegFormat(box.getMin().lon);
	var rblat = DmapDegFormat(box.getMin().lat);
	var rblon = DmapDegFormat(box.getMax().lon);
	/* hiddenに書き込み */
	var hid;
	hid = document.getElementById('CLAT');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lat);
	hid = document.getElementById('CLON');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lon);
	hid = document.getElementById('SCALE');
	if (hid) hid.value = DmapMap.getZoom();
	hid = document.getElementById('LTLAT');
	if (hid) hid.value = ltlat;
	hid = document.getElementById('LTLON');
	if (hid) hid.value = ltlon;
	hid = document.getElementById('RBLAT');
	if (hid) hid.value = rblat;
	hid = document.getElementById('RBLON');
	if (hid) hid.value = rblon;
	hid = document.getElementById('JOKEN11');
	if (hid) hid.value = joken11;
	hid = document.getElementById('JOKEN12');
	if (hid) hid.value = joken12;
	hid = document.getElementById('JOKEN2');
	if (hid) hid.value = joken2;
	/* 利用状況ログ */
	DmapLogCount(8);
	/* フラグリセット */
	resetAllFlg();
	/* 隠しボタンイベント発生 */
	var b = document.getElementById('BTNPCHG_dummy');
	if (b) {
		b.click();
	}
}

/**
 * 「訪問先」ボタン押下時の処理。
 * @return {void}
 */
function DmapOnClickVisitPlan() {
	/* 職員コード入力必須 */
	if (DmapGetValueById('IE50012_disp') == '') {
		alert(MSG_ERR_STAFFCD_EMPTY);
		return;
	}
	/* ダイアログ表示 */
	var dlg = document.getElementById('vp_dlg');
	if (dlg) {
		var btn = document.getElementById('rb_v');
		if (DmapUser.isProper()) {
			dlg.style.top = '110px';
		} else {
			dlg.style.top = '80px';
		}
		var inp = document.getElementById('vp_dlg_date');
		//inp.value = DmapGetDate();
		var rdt = DmapGetValueById('IG4041');
		if (rdt != '') inp.value = rdt.substr(0,4)+'/'+rdt.substr(4,2)+'/'+rdt.substr(6,2)
		dlg.style.display = 'block';
		DmapDisableAllArea();
	}
}
/**
 * 「訪問先」ダイアログを閉じます。
 * @return {void}
 */
function DmapCloseVisitPlan() {
	var dlg = document.getElementById('vp_dlg');
	if (dlg) {
		dlg.style.display = 'none';
	}
	DmapEnableAllArea();
}
/**
 * 「訪問先」ダイアログ「OK」押下時の処理。
 * @return {void}
 */
function DmapSubmitVisitPlan() {
	/* hiddenに値をセット */
	var sitei = document.getElementById('SITEI');
	if (!sitei) return;
	sitei.value = DmapCheckVisitPlanYmd();
	if (!sitei.value) {
		alert('正しい日付を入力してください。');
		return;
	}
	/* 利用状況ログ */
	DmapLogCount(9);
	/* フラグリセット */
	resetAllFlg();
	/* 隠しボタンClickイベント */
	var btn = document.getElementById('BTNVISP_dummy');
	if (btn) {
		btn.click();
	}
	/* 訪問先ダイアログを消去 */
	DmapCloseVisitPlan();
}
/**
 * 「訪問先」ダイアログ日付入力値をチェックして正しければ値を返却します。
 * @return {String} 入力された日付文字列（yyyymmdd）
 */
function DmapCheckVisitPlanYmd() {
	var dt = document.getElementById('vp_dlg_date');
	if (dt) {
		return DmapFormatYmd(dt.value);
	}
	return '';
}

/**
 * カレンダーを表示します。
 * @param {Number} year 年
 * @param {Number} month 月
 * @return {void}
 */
function DmapShowCal(year, month){
	/* 今日 */
	var today = new Date();
	/* 表示する年月 */
	if (year == 0) {
		year = today.getFullYear();
		month = today.getMonth();
	}
	var fst = new Date(year, month, 1);
	var f_month = fst.getMonth();
	var f_year  = fst.getFullYear();
	var f_yyyymm = f_year * 100 + f_month;
	f_month = f_month + 1;
	if (f_month < 10) f_month = '0' + f_month
	var f_text = f_year + '年' + f_month + '月';
	/* 曜日 */
	var week = new Array('日','月','火','水','木','金','土');
	/* カレンダーの最初のコマ（最初の日曜日） */
	var startday = fst - (fst.getDay() * 1000 * 60 * 60 * 24);
	startday = new Date(startday);
	/* 前月／次月 */
	var prev, next;
	if (month == 0) {
		prev = new Date(year-1, 11, 1);
		next = new Date(year, month+1, 1);
	} else if (month == 11) {
		prev = new Date(year, month-1, 1);
		next = new Date(year+1, 0, 1);
	} else {
		prev = new Date(year, month-1, 1);
		next = new Date(year, month+1, 1);
	}

	var html = '';
	html += '<table id="cal_tbl">';
	/* 年月（ヘッダ） */
	html += '<tr><th colspan="7">';
	html += '<button class="cal_pg" onClick="DmapShowCal('+prev.getFullYear()+','+prev.getMonth()+');">&lt;</button>';
	html += '　'+f_text+'　';
	html += '<button class="cal_pg" onClick="DmapShowCal('+next.getFullYear()+','+next.getMonth()+');">&gt;</button>';
	html += '</th></tr>';

	/* 曜日 */
	html += '<tr>';
	for (i = 0; i < 7; i++){
		html += '<td class="cal_yobi">' + week[i] + '</td>';
	}
	html += '</tr>';
	/* 日付 */
	for(j = 0; j < 6; j++){
		html += '<tr>';
		for(i = 0; i < 7; i++){
			var nextday = startday.getTime() + (i * 1000 * 60 * 60 * 24);
			var crr_day = new Date(nextday);
			var crr_d   = crr_day.getDate();
			var crr_dd  = crr_d;   if (crr_dd < 10) crr_dd = '0' + crr_dd;
			var crr_m   = crr_day.getMonth();
			var crr_mm  = crr_m+1; if (crr_mm < 10) crr_mm = '0' + crr_mm;
			var crr_y   = crr_day.getFullYear();
			var crr_yyyymm = crr_y * 100 + crr_m;
			var crr_res = crr_y+'/'+crr_mm+'/'+crr_dd;
			var crr_html = '<a href="javascript:void(0);" onClick="DmapSelDate(\'vp_dlg_date\',\''+crr_res+'\');" onFocus="this.blur();">';
			crr_html += crr_d;
			crr_html += '</a>';
			if(crr_yyyymm != f_yyyymm){
				html += '<td class="cal_none">　';
			} else if(crr_d == today.getDate() && crr_m == today.getMonth() && crr_y == today.getFullYear()) {
				html += '<td class="cal_today">';
				html += crr_html;
			} else {
				html += '<td class="cal_day">';
				html += crr_html;
			}
			html += '</td>';
		}
		html += '</tr>';
		startday = new Date(nextday);
		startday = startday.getTime() + (1000 * 60 * 60 * 24);
		startday = new Date(startday);
	}
	html += '</table>';
	var cal = document.getElementById('vp_cal');
	if (cal) {
		if (DmapUser.isProper()) {
			cal.style.top = '145px';
		} else {
			cal.style.top = '115px';
		}
		cal.innerHTML = html;
		cal.style.display = 'block';
	}
}

/**
 * カレンダーで選択された日付をテキスト入力にセットします。
 * @param {String} id テキスト入力のid
 * @param {String} ymd 日付文字列
 * @return {void}
 */
function DmapSelDate(id, ymd) {
	var txt = document.getElementById(id);
	if (!txt) return;
	txt.value = ymd;
	var cal = document.getElementById('vp_cal');
	if (cal) {
		cal.style.display = 'none';
		cal.innerHTML = '';
	}
}

/**
 * 「表示位置修正」ボタン押下時の処理。
 * @return {void}
 */
function DmapOnClickBtnMove() {
	/* 表示位置修正モード中 */
	if (DmapMovePinMode) {
		/* 表示位置修正モードを終了 */
		DmapStopMovePinMode();
	/* 表示位置修正モードではない */
	} else {
		/* 表示位置修正モードを開始 */
		DmapStartMovePinMode();
	}
}

/**
 * 表示位置修正モードを開始します。
 * @return {void}
 */
function DmapStartMovePinMode() {
	DmapMovePinMode = true;
	/* 「表示位置修正」ボタン画像切替 */
	var btn = document.getElementById('f_btn_move');
	btn.className = 'f_btn_move_on';
	/* 表示済みのランチャーを消去 */
	DmapRemoveLauncher();
	/* 表示済みのピン一覧を消去 */
	DmapRemovePinSelect();
	/* 社内情報検索明細を閉じる */
	DmapSrchPointDtlOff();
	/* ポイント表示変更ダイアログを閉じる */
	DmapCloseSelPoint();
	/* メッセージ表示 */
	DmapShowHeaderMsg('！表示位置を修正するポイントをドラッグしてください。');
}

/**
 * 表示位置修正モードを終了します。
 * @return {void}
 */
function DmapStopMovePinMode() {
	DmapMovePinMode = false;
	var btn = document.getElementById('f_btn_move');
	btn.className = 'f_btn_move_off';
	/* メッセージ非表示 */
	DmapHideHeaderMsg();
}

/**
 * MouseDownイベントリスナー
 * @return {void}
 */
function DmapOnMouseDown() {
	/* 表示位置修正モード以外の時は何もしない */
	if (!DmapMovePinMode) return;
	/* 地図無効化中は何もしない */
	if (!DmapMapEventEnable) return;
	/* ドラッグ開始 */
	DmapPinDragging = true;
	/* ドラッグ中のピン */
	DmapMovePin = this;
	/* マウスダウン位置とピン位置の差分 */
	var cLatLon = DmapMap.getPointerPosition();
	DmapMovePin.dragDifLat = cLatLon.lat - DmapMovePin.latlon.lat;
	DmapMovePin.dragDifLon = cLatLon.lon - DmapMovePin.latlon.lon;
}

/**
 * MouseMoveイベントリスナー
 * @return {void}
 */
function DmapOnMouseMove() {
	/* 表示位置修正モード以外の時は何もしない */
	if (!DmapMovePinMode) return;
	/* 地図無効化中は何もしない */
	if (!DmapMapEventEnable) return;
	/* ドラッグ中でなければ何もしない */
	if (!DmapPinDragging) return;
	/* ドラッグ中のピンが不明の時は何もしない */
	if (!DmapMovePin) return;
	/* マウス位置 */
	var latlon = DmapMap.getPointerPosition();
	/* ピンを移動 */
	var newlat = latlon.lat - DmapMovePin.dragDifLat;
	var newlon = latlon.lon - DmapMovePin.dragDifLon;
	DmapMovePin.moveLatLon(newlat, newlon);
}

/**
 * MouseUpイベントリスナー
 * @return {void}
 */
function DmapOnMouseUp() {
	/* ドラッグ中でない場合は何もしない */
	if (!DmapPinDragging) return;
	/* 地図無効化中は何もしない */
	if (!DmapMapEventEnable) return;
	/* ドラッグ終了 */
	DmapPinDragging = false;
	/* ドラッグ中のピンが不明の時は何もしない */
	if (!DmapMovePin) return;
	/* グループの場合は選択リストを表示 */
	if (DmapMovePin.inGroup()) {
		DmapShowPinSelect(DmapMovePin.seq, 'DmapDragPinEnd', 'DmapDragPinSelectClose');
	/* 単独の場合は表示位置修正実行 */
	} else {
		DmapDragPinEnd(DmapMovePin.seq);
	}
}

/**
 * Clickイベントリスナー
 * @return {void}
 */
function DmapOnClick() {
	/* ポイントランチャー消去 */
	DmapRemoveLauncher();
	/* 表示済みのピン一覧を消去 */
	DmapRemovePinSelect();
}

/**
 * DblClickイベントリスナー
 * @return {void}
 */
function DmapOnDblClick() {
	var zoom = DmapMap.getZoom();
	DmapMap.setZoom(zoom+1);
	var latlon = DmapMap.getClickLatLon();
	DmapMap.moveLatLon(latlon);
}

/**
 * RightClickイベントリスナー
 * @return {void}
 */
function DmapOnRightClick() {
	/* 表示位置修正モードの時は何もしない */
	if (DmapMovePinMode) return;
	/* 見込客登録 */
	if (DmapRightClickMode == 1 && DmapMapEventEnable) {
		DmapShowMikomiKyaku();
	/* ルート検索 */
	} else if (DmapRightClickMode == 2 && DmapRouteSearch) {
		DmapRouteSearch.entryPoint();
	}
}

/**
 * ピンのドラッグ完了時の処理。
 * @param {Number} seq ピン連番（0～99）
 * @return {void}
 */
function DmapDragPinEnd(seq) {
	/* ピン選択リストを消去 */
	DmapRemovePinSelect();
	/* 該当ピン（単独：ドラッグしたピン／グループ：リストから選択されたピン） */
	var p = DmapPinList.Pins[seq];
	if (!p) return;
	/* 該当ピンを最前面に */
	p.moveTop();
	/* 該当ピンとドラッグしたピンが異なる場合 */
	if (p.seq != DmapMovePin.seq) {
		/* 該当ピンをドラッグ位置へ移動させる */
		p.moveLatLon(DmapMovePin.lat, DmapMovePin.lon);
		/* ドラッグしたピンを元の位置に戻す */
		DmapMovePin.moveOrgLatLon();
	}
	/* 該当ピンを保持 */
	DmapMovePin = p;
	/* 処理実行 */
	DmapSubmitChangePoint();
}

/**
 * ドラッグ時のピン一覧を閉じた時の処理。
 * @return {void}
 */
function DmapDragPinSelectClose() {
	/* ピン選択リストを消去 */
	DmapRemovePinSelect();
	/* 表示位置変更をキャンセル */
	DmapCancelChangePoint();
}

/**
 * 表示位置修正の実行処理。
 * @return {void}
 */
function DmapSubmitChangePoint() {
	var e;
	/* 移動不可の場合はエラー */
	if (!DmapMovePin.isMovable(DmapUser)) {
		alert(MSG_ERR_CHGP_NG);
		DmapCancelChangePoint();
		return;
	}
	/* 確認ダイアログ */
	if (confirm(MSG_CONF_CHGP)) {
		/* 利用状況ログ */
		DmapLogCount(5);
		/* hiddenに値をセット */
		e = document.getElementById('CLAT');if (e) e.value = DmapDegFormat(DmapMap.getLatLon().lat);
		e = document.getElementById('CLON');if (e) e.value = DmapDegFormat(DmapMap.getLatLon().lon);
		e = document.getElementById('SCALE');if (e) e.value = DmapMap.getZoom();
		e = document.getElementById('SYOROW');if (e) e.value = DmapMovePin.seq;
		e = document.getElementById('SYULAT');if (e) e.value = DmapDegFormat(DmapMovePin.lat);
		e = document.getElementById('SYULON');if (e) e.value = DmapDegFormat(DmapMovePin.lon);
		/* フラグリセット */
		resetAllFlg();
		/* 隠しボタンClickイベント */
		var btn = document.getElementById('BTNPOSI_dummy');
		if (btn) {
			btn.click();
		}
	/* キャンセル */
	} else {
		DmapCancelChangePoint();
	}
}

/**
 * 表示位置修正をキャンセルします。
 * @return {void}
 */
function DmapCancelChangePoint() {
	/* 元の位置に戻す */
	DmapMovePin.moveOrgLatLon();
	/* 表示位置修正モード終了 */
	DmapStopMovePinMode();
}

/**
 * ホイールイベントを無効化します。
 * @param {Object} イベント
 * @return {void}
 */
function DmapOnMouseWheel(evt) {
	if (evt.stopPropagation) {
		evt.stopPropagation();	//for not IE
	} else {
		window.event.cancelBubble = true;	//for IE
	}
	if (evt.preventDefault) {
		evt.preventDefault();
	}
	evt.returnValue = false;
}

/**
 * 「社内情報検索」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickBtnSrchPoint() {
	if (DmapSrchPointOn) {
		DmapSrchPointDtlOff();
	} else {
		DmapSrchPointDtlOn();
	}
}

/**
 * 「社内情報検索」明細を表示します。
 * @return {void}
 */
function DmapSrchPointDtlOn() {
	/* フリーワード検索ダイアログを消去 */
	DmapSrchFWEnd();
	/* 「社内情報検索」明細を表示 */
	var div = document.getElementById('srch_p_dtl');
	div.style.display = 'block';
	var btn = document.getElementById('srch_p_btn');
	if (btn) btn.className = 'srch_p_btn_on';
	DmapSrchPointOn = true;
}

/**
 * 「社内情報検索」明細を消去します。
 * @return {void}
 */
function DmapSrchPointDtlOff() {
	var div = document.getElementById('srch_p_dtl');
	div.style.display = 'none';
	var btn = document.getElementById('srch_p_btn');
	if (btn) btn.className = 'srch_p_btn_off';
	DmapSrchPointOn = false;
}

/**
 * 「社内情報検索」明細クリック時の処理。
 * @param {Number} idx 明細番号
 * @return {void}
 */
function DmapOnClickSrchPointDtl(idx) {
	var e;
	var val;
	/* 地図縮尺 */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_SRCH_POINT.min && z <= NGZOOM_SRCH_POINT.max) {
		alert(MSG_ERR_SRCH_POINT_NGZOOM);
		return;
	}
	/* 検索ワード */
	val = DmapGetValueById('MEISYO');
	if (val == '') {
		alert(MSG_ERR_WORD_EMPTY);
		return;
	}
	if (!DmapIsMbString(val)) {
		alert(MSG_ERR_WORD_MB);
		return;
	}
	if (val.length > SP_WORD_MAXLEN) {
		alert(MSG_ERR_WORD_LEN);
		return;
	}
	/* 利用状況ログ */
	DmapLogCount(7);
	/* 地図の範囲を取得 */
	var box = DmapMap.getLatLonBox();
	hid = document.getElementById('CLAT');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lat);
	hid = document.getElementById('CLON');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lon);
	hid = document.getElementById('SCALE');
	if (hid) hid.value = DmapMap.getZoom();
	/* 左上緯度 */
	e = document.getElementById('LTLAT');
	e.value = DmapDegFormat(box.getMax().lat);
	/* 左上経度 */
	e = document.getElementById('LTLON');
	e.value = DmapDegFormat(box.getMin().lon);
	/* 右下緯度 */
	e = document.getElementById('RBLAT');
	e.value = DmapDegFormat(box.getMin().lat);
	/* 右下経度 */
	e = document.getElementById('RBLON');
	e.value = DmapDegFormat(box.getMax().lon);
	/* 明細選択 */
	e = document.getElementById('BNAME');
	e.value = idx;
	/* フラグリセット */
	resetAllFlg();
	/* 隠しボタンClickイベント */
	var btn = document.getElementById('BTNCOINF_dummy');
	if (btn) {
		btn.click();
	}
}

/**
 * 「フリーワード検索」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickBtnSrchFW() {
	if (DmapSrchFWOn) {
		DmapSrchFWEnd();
	} else {
		DmapSrchFWStart();
	}
}

/**
 * 「フリーワード検索」を開始します。
 * @return {void}
 */
function DmapSrchFWStart() {
	/* 「フリーワード検索」ダイアログを消去 */
	DmapSrchFWEnd();
	/* 「社内条件検索」明細を消去 */
	DmapSrchPointDtlOff();
	/* 緯度経度検索実行 */
	if (DmapSrchFWLatLon()) {
		return;
	}
	/* ヘッダー以外を無効化する */
	if (DmapDisableMode != 'AllForRouteDlg' && DmapDisableMode != 'AllForRouteResult') {
		DmapDisableRight();
		DmapDisableBottom();
		DmapDisableMapEvent();
	}
	/* フリーワード検索ダイアログ表示 */
	var btn = document.getElementById('srch_fw_btn');
	if (btn) btn.className = 'srch_fw_btn_on';
	DmapSrchFWOn = true;
	var dlg = document.getElementById('srch_fw_dlg');
	if (dlg) dlg.style.display = 'block';
}

/**
 * 「フリーワード検索」ダイアログを消去します。
 * @return {void}
 */
function DmapSrchFWEnd() {
	/* 一覧クリア */
	var div = document.getElementById('srch_fw_list_div');
	if (div) div.innerHTML = '';
	DmapSrchFWPoiResult = null;
	/* ダイアログ消去 */
	var dlg = document.getElementById('srch_fw_dlg');
	if (dlg) dlg.style.display = 'none';
	/* 「フリーワード検索」ボタン */
	var btn = document.getElementById('srch_fw_btn');
	if (btn) btn.className = 'srch_fw_btn_off';
	DmapSrchFWOn = false;
	/* ヘッダー以外を元に戻す */
	if (DmapDisableMode != 'AllForRouteDlg' && DmapDisableMode != 'AllForRouteResult') {
		DmapEnableRight();
		DmapEnableBottom();
		DmapEnableMapEvent();
	}
}

/**
 * フリーワード検索の最終結果選択時の処理。
 * @param {Number} lat 緯度
 * @param {Number} lon 経度
 * @return {void}
 */
function DmapSelectFWResult(lat, lon) {
	/* フリーワード検索ダイアログ消去 */
	DmapSrchFWEnd();
	/* マーカー表示して地図移動 */
	var loc = new ZDC.LatLon(lat, lon);
	DmapPlotSearchMarker(loc);
	DmapMap.moveLatLon(loc);
}

/**
 * フリーワード検索切り替えボタンクリック時の処理。
 * @param {Number} idx 検索種類（1：住所、2：都道府県、3：周辺）
 * @return {void}
 */
function DmapOnClickFW(idx) {
	/* 地図縮尺 */
	if (idx == 3) {
		var z = DmapMap.getZoom();
		if (z >= NGZOOM_SRCH_NPOI.min && z <= NGZOOM_SRCH_NPOI.max) {
			alert(MSG_ERR_SRCH_NPOI_NGZOOM);
			return;
		}
	}
	/* 一覧クリア */
	var div = document.getElementById('srch_fw_list_div');
	if (div) div.innerHTML = '';
	DmapSrchFWPoiResult = null;
	/* 検索ワード取得 */
	var word = DmapGetValueById('MEISYO').trim();
	/* 入力必須 */
	if (word == '') {
		alert(MSG_ERR_WORD_EMPTY);
		return;
	}
	/* 切り替えボタン制御 */
	for (var i = 1; i <= 3; i++) {
		var btn = document.getElementById('srch_fw_type'+i);
		if (btn) {
			if (i == idx) {
				btn.className = 'srch_fw_type_sel';
			} else {
				btn.className = '';
			}
		}
	}
	/* 利用状況ログ */
	DmapLogCount(6);
	switch (idx) {
		/* 住所フリーワード検索 */
		case 1:
			div.innerHTML = MSG_INF_SEARCH_PROCESSING;
			ZDC.Search.getAddrByWord({
				word: word,
				limit: '0,'+SRCH_ADDR_ROWS
			}, DmapAddrByWordCallback);
			break;
		/* POIフリーワード検索 */
		case 2:
			div.innerHTML = MSG_INF_SEARCH_PROCESSING;
			ZDC.Search.getPoiByWord({
				word: word,
				limit: '0,'+SRCH_POI_LIMIT
			}, DmapPoiByWordCallback);
			break;
		/* 周辺POI検索 */
		case 3:
			div.innerHTML = MSG_INF_SEARCH_PROCESSING;
			var center = DmapMap.getLatLon();
			var box = DmapMap.getLatLonBox();
			var minlat = box.getMin().lat;
			var maxlat = box.getMax().lat;
			var dist = ZDC.getLatLonToLatLonDistance(new ZDC.LatLon(minlat, center.lon), new ZDC.LatLon(maxlat, center.lon));
			ZDC.Search.getPoiByLatLon({
				latlon: center,
				radius: Math.floor(dist/2),
				word: word,
				limit: '0,'+SRCH_NEARPOI_LIMIT
			}, DmapPoiByLatLonCallback);
			break;
	}
}

/**
 * 住所フリーワード検索のコールバック関数。
 * @param {Object} status ステータスオブジェクト
 * @param {Object} result 結果オブジェクト
 * @return {void}
 */
function DmapAddrByWordCallback(status, result) {
	var html = '';
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	/* 実行時エラー */
	if (status.code != '000') {
		div.innerHTML = '';
		if (status.code == '102') {
			alert(MSG_ERR_FW_SEARCH_FAIL);
			return;
		} else {
			alert(MSG_ERR_SEARCH_FAIL);
			return;
		}
	}
	/* 0件 */
	if (result.info.hit == 0) {
		html += '<span class="fw_msg">'+MSG_ALERT_NODATA+'</span>';
	/* データあり */
	} else {
		var len = result.item.length;
		for (var i = 0; i < len; i++) {
			var itm = result.item[i];
			html += '<tr><td>';
			html += '<a href="javascript:void(0);" onClick="DmapSelectFWResult('+itm.latlon.lat+','+itm.latlon.lon+');" onFocus="this.blur();">'+itm.text+'</a>';
			html += '</td></tr>';
		}
		html = '<table id="srch_fw_list">'+html+'</table>';
	}
	div.innerHTML = html;
}

/**
 * POIフリーワード検索のコールバック関数。
 * @param {Object} status ステータスオブジェクト
 * @param {Object} result 結果オブジェクト
 * @return {void}
 */
function DmapPoiByWordCallback(status, result) {
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	/* 実行時エラー */
	if (status.code != '000') {
		div.innerHTML = '';
		alert(MSG_ERR_FW_SEARCH_FAIL);
		return;
	}
	/* 0件 */
	if (result.info.hit == 0) {
		DmapPoiByWordListNoData();
	/* データあり */
	} else {
		/* 結果オブジェクトを保持 */
		DmapSrchFWPoiResult = result;
		if (result.info.hit > SRCH_POI_EXT) {
			/* 都道府県一覧 */
			DmapPoiByWordListTod();
		} else {
			/* POI一覧 */
			DmapPoiByWordListPoi();
		}
	}
}

/**
 * 周辺POI検索のコールバック関数。
 * @param {Object} status ステータスオブジェクト
 * @param {Object} result 結果オブジェクト
 * @return {void}
 */
function DmapPoiByLatLonCallback(status, result) {
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	/* 実行時エラー */
	if (status.code != '000') {
		div.innerHTML = '';
		alert(MSG_ERR_FW_SEARCH_FAIL);
		return;
	}
	/* 0件 */
	if (result.info.hit == 0) {
		DmapPoiByLatLonListNoData();
	/* データあり */
	} else {
		/* 結果オブジェクトを保持 */
		DmapSrchFWPoiResult = result;
		if (result.info.hit > SRCH_NEARPOI_EXT) {
			/* 都道府県一覧 */
			DmapPoiByLatLonListGenre();
		} else {
			/* POI一覧 */
			DmapPoiByLatLonListPoi();
		}
	}
}

/**
 * POIフリーワード検索の都道府県クリック時処理。
 * @param {String} tod 都道府県コード
 * @param {Number} cnt 都道府県に該当する件数
 * @return {void}
 */
function DmapOnClickPoiTod(tod, cnt) {
	if (!DmapSrchFWPoiResult) return;
	if (cnt > SRCH_POI_EXT) {
		/* 大ジャンル一覧 */
		DmapPoiByWordListGenre(tod);
	} else {
		/* POI一覧 */
		DmapPoiByWordListPoi(tod);
	}
}

/**
 * POIフリーワード検索の大ジャンルクリック時処理。
 * @param {String} tod 都道府県コード
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @param {Number} cnt 都道府県＋大ジャンルに該当する件数
 * @return {void}
 */
function DmapOnClickPoiGenre(tod, genre, genrenm, cnt) {
	if (!DmapSrchFWPoiResult) return;
	if (cnt > SRCH_POI_EXT) {
		/* 小ジャンル一覧 */
		DmapPoiByWordListSubGenre(tod, genre, genrenm);
	} else {
		/* POI一覧 */
		DmapPoiByWordListPoi(tod, genre, genrenm);
	}
}

/**
 * POIフリーワード検索の小ジャンルクリック時処理。
 * @param {String} tod 都道府県コード
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @param {String} sub 小ジャンルコード
 * @param {String} subnm 小ジャンル名称
 * @return {void}
 */
function DmapOnClickPoiSubGenre(tod, genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* POI一覧 */
	DmapPoiByWordListPoi(tod, genre, genrenm, sub, subnm);
}

/**
 * 周辺POI検索の大ジャンルクリック時処理。
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @param {Number} cnt 大ジャンルに該当する件数
 * @return {void}
 */
function DmapOnClickNearPoiGenre(genre, genrenm, cnt) {
	if (!DmapSrchFWPoiResult) return;
	if (cnt > SRCH_NEARPOI_EXT) {
		/* 小ジャンル一覧 */
		DmapPoiByLatLonListSubGenre(genre, genrenm);
	} else {
		/* POI一覧 */
		DmapPoiByLatLonListPoi(genre, genrenm);
	}
}

/**
 * 周辺POI検索の小ジャンルクリック時処理。
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @param {String} sub 小ジャンルコード
 * @param {String} subnm 小ジャンル名称
 * @return {void}
 */
function DmapOnClickNearPoiSubGenre(genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* POI一覧 */
	DmapPoiByLatLonListPoi(genre, genrenm, sub, subnm);
}

/**
 * POIフリーワード検索の０件メッセージ表示。
 * @return {void}
 */
function DmapPoiByWordListNoData() {
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	var html = '';
	html += '<span class="fw_msg">'+MSG_ALERT_NODATA+'</span>';
	html = '<table id="srch_fw_list">'+html+'</table>';
	div.innerHTML = html;
}

/**
 * POIフリーワード検索の都道府県一覧表示。
 * @return {void}
 */
function DmapPoiByWordListTod() {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	var html = '';
	html += '<table id="srch_fw_list">';
	var tod = DmapSrchFWPoiResult.info.facet.tod;
	for (var t in tod) {
		var nm = TOD_NAME[t];
		var cnt = tod[t];
		if (nm) {
			html += '<tr><td>';
			html += '<a href="javascript:void(0);" onClick="DmapOnClickPoiTod(\''+t+'\','+cnt+');" onFocus="this.blur();">'+nm+'('+cnt+')'+'</a>';
			html += '</td></tr>';
		}
	}
	html += '</table>';
	div.innerHTML = html;
}

/**
 * POIフリーワード検索の大ジャンル一覧表示。
 * @param {String} tod 都道府県コード
 * @return {void}
 */
function DmapPoiByWordListGenre(tod) {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	/* 都道府県コードで大ジャンルを絞込み */
	var arrgenre = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		if (itm.addressText.indexOf(TOD_NAME[tod]) >= 0) {
			var code = itm.genre.code.substr(0,5);
			if (!arrgenre[code]) {
				arrgenre[code] = {cnt:0, name:''};
			}
			arrgenre[code].cnt++;
			arrgenre[code].name = itm.genre.text.split('/')[0];
		}
	}
	/* 大ジャンル一覧表示 */
	var html = '';
	html += '<div id="srch_fw_title">スポット（'+TOD_NAME[tod]+'）</div>';
	html += '<table id="srch_fw_list">';
	for (var gr in arrgenre) {
		var cnt = arrgenre[gr].cnt;
		var nm = arrgenre[gr].name;
		html += '<tr><td>';
		html += '<a href="javascript:void(0);" onClick="DmapOnClickPoiGenre(\''+tod+'\',\''+gr+'\',\''+nm+'\','+cnt+');" onFocus="this.blur();">'+nm+'('+cnt+')'+'</a>';
		html += '</td></tr>';
	}
	html += '</table>';
	div.innerHTML = html;
	arrgenre = null;
}

/**
 * POIフリーワード検索の小ジャンル一覧表示。
 * @param {String} tod 都道府県コード
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @return {void}
 */
function DmapPoiByWordListSubGenre(tod, genre, genrenm) {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	/* 都道府県コード＋大ジャンルで小ジャンルを絞込み */
	var arrsub = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		if (itm.addressText.indexOf(TOD_NAME[tod]) >= 0) {
			if (itm.genre.code.substr(0,5) == genre) {
				var code = itm.genre.code.substr(5);
				if (!arrsub[code]) {
					arrsub[code] = {cnt:0, name:''};
				}
				arrsub[code].cnt++;
				arrsub[code].name = itm.genre.text.split('/')[1];
			}
		}
	}
	/* 小ジャンル一覧表示 */
	var html = '';
	html += '<div id="srch_fw_title">スポット（'+TOD_NAME[tod]+' - '+genrenm+'）</div>';
	html += '<table id="srch_fw_list">';
	for (var sub in arrsub) {
		var nm = arrsub[sub].name;
		html += '<tr><td>';
		html += '<a href="javascript:void(0);" onClick="DmapOnClickPoiSubGenre(\''+tod+'\',\''+genre+'\',\''+genrenm+'\',\''+sub+'\',\''+nm+'\');" onFocus="this.blur();">'+nm+'</a>';
		html += '</td></tr>';
	}
	html += '</table>';
	div.innerHTML = html;
	arrsub = null;
}

/**
 * POIフリーワード検索のPOI一覧表示。
 * @param {String} tod 都道府県コード
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @param {String} sub 小ジャンルコード
 * @param {String} subnm 小ジャンル名称
 * @return {void}
 */
function DmapPoiByWordListPoi(tod, genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	var arrpoi = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		/* 都道府県指定 */
		if (tod) {
			if (itm.addressText.indexOf(TOD_NAME[tod]) >= 0) {
				/* 大ジャンル指定 */
				if (genre) {
					/* 小ジャンル指定 */
					if (sub) {
						if (itm.genre.code == genre+sub) {
							arrpoi.push(itm);
						}
					/* 小ジャンル指定なし */
					} else {
						if (itm.genre.code.substr(0,5) == genre) {
							arrpoi.push(itm);
						}
					}
				/* 大ジャンル指定なし */
				} else {
					arrpoi.push(itm);
				}
			}
		/* 都道府県指定なし */
		} else {
			arrpoi.push(itm);
		}
	}
	DmapSrchFWPoiResult = null;
	var html = '';
	if (tod) {
		html += '<div id="srch_fw_title">スポット（'+TOD_NAME[tod];
		if (genrenm) html += ' - ' + genrenm;
		if (subnm) html += ' - ' + subnm;
		html += '）</div>';
	}
	len = arrpoi.length;
	if (len > 0) {
		html += '<table id="srch_fw_list">';
		if (len > SRCH_POI_ROWS) len = SRCH_POI_ROWS;
		for (var i = 0; i < len; i++) {
			itm = arrpoi[i];
			html += '<tr><td>';
			html += '<a href="javascript:void(0);" onClick="DmapSelectFWResult('+itm.latlon.lat+','+itm.latlon.lon+');" onFocus="this.blur();">'+itm.text+'</a>';
			html += '</td></tr>';
		}
		html += '</table>';
		div.innerHTML = html;
	}
	arrpoi = null;
}

/**
 * 周辺POI検索の０件メッセージ表示。
 * @return {void}
 */
function DmapPoiByLatLonListNoData() {
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	var html = '';
	html += '<span class="fw_msg">'+MSG_ALERT_NODATA+'</span>';
	html = '<table id="srch_fw_list">'+html+'</table>';
	div.innerHTML = html;
}

/**
 * 周辺POI検索の大ジャンル一覧表示。
 * @return {void}
 */
function DmapPoiByLatLonListGenre() {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	var html = '';
	var arrgenre = new Array();
	var genre = DmapSrchFWPoiResult.info.facet.genre;
	for (var g in genre) {
		var code = g.substr(0,5);
		if (!arrgenre[code]) {
			arrgenre[code] = {cnt:0, name:''};
		}
		arrgenre[code].cnt += parseInt(genre[g].count);
		arrgenre[code].name = genre[g].text.split('/')[0];
	}
	html += '<table id="srch_fw_list">';
	for (var g in arrgenre) {
		var nm = arrgenre[g].name.split('/')[0];
		var cnt = arrgenre[g].cnt;
		if (nm) {
			html += '<tr><td>';
			html += '<a href="javascript:void(0);" onClick="DmapOnClickNearPoiGenre(\''+g+'\',\''+nm+'\','+cnt+');" onFocus="this.blur();">'+nm+'('+cnt+')'+'</a>';
			html += '</td></tr>';
		}
	}
	html += '</table>';
	div.innerHTML = html;
}

/**
 * 周辺POI検索の小ジャンル一覧表示。
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @return {void}
 */
function DmapPoiByLatLonListSubGenre(genre, genrenm) {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	/* 都道府県コード＋大ジャンルで小ジャンルを絞込み */
	var arrsub = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		if (itm.poi.genre.code.substr(0,5) == genre) {
			var code = itm.poi.genre.code.substr(5);
			if (!arrsub[code]) {
				arrsub[code] = {cnt:0, name:''};
			}
			arrsub[code].cnt++;
			arrsub[code].name = itm.poi.genre.text.split('/')[1];
		}
	}
	/* 小ジャンル一覧表示 */
	var html = '';
	html += '<div id="srch_fw_title">スポット（'+genrenm+'）</div>';
	html += '<table id="srch_fw_list">';
	for (var sub in arrsub) {
		var nm = arrsub[sub].name;
		html += '<tr><td>';
		html += '<a href="javascript:void(0);" onClick="DmapOnClickNearPoiSubGenre(\''+genre+'\',\''+genrenm+'\',\''+sub+'\',\''+nm+'\');" onFocus="this.blur();">'+nm+'</a>';
		html += '</td></tr>';
	}
	html += '</table>';
	div.innerHTML = html;
	arrsub = null;
}

/**
 * 周辺POI検索のPOI一覧表示。
 * @param {String} genre 大ジャンルコード
 * @param {String} genrenm 大ジャンル名称
 * @param {String} sub 小ジャンルコード
 * @param {String} subnm 小ジャンル名称
 * @return {void}
 */
function DmapPoiByLatLonListPoi(genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* 一覧 */
	var div = document.getElementById('srch_fw_list_div');
	var arrpoi = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		/* 大ジャンル指定 */
		if (genre) {
			/* 小ジャンル指定 */
			if (sub) {
				if (itm.poi.genre.code == genre+sub) {
					arrpoi.push(itm);
				}
			/* 小ジャンル指定なし */
			} else {
				if (itm.poi.genre.code.substr(0,5) == genre) {
					arrpoi.push(itm);
				}
			}
		/* 大ジャンル指定なし */
		} else {
			arrpoi.push(itm);
		}
	}
	DmapSrchFWPoiResult = null;
	var html = '';
	if (genrenm) {
		html += '<div id="srch_fw_title">スポット（' + genrenm;
		if (subnm) html += ' - ' + subnm;
		html += '）</div>';
	}
	len = arrpoi.length;
	if (len > 0) {
		html += '<table id="srch_fw_list">';
		if (len > SRCH_NEARPOI_ROWS) len = SRCH_NEARPOI_ROWS;
		for (var i = 0; i < len; i++) {
			itm = arrpoi[i];
			html += '<tr><td>';
			html += '<a href="javascript:void(0);" onClick="DmapSelectFWResult('+itm.poi.latlon.lat+','+itm.poi.latlon.lon+');" onFocus="this.blur();">'+itm.poi.text+'</a>';
			html += '</td></tr>';
		}
		html += '</table>';
		div.innerHTML = html;
	}
	arrpoi = null;
}

/**
 * 「フリーワード検索」緯度経度検索を実行します。
 * @return {Boolean} true：緯度経度検索実行／false：緯度経度に合致しないので次処理へ遷移する。
 */
function DmapSrchFWLatLon() {
	/* 検索ワード取得 */
	var word = DmapGetValueById('MEISYO').trim();
	/* 入力必須 */
	if (word == '') {
		alert(MSG_ERR_WORD_EMPTY);
		return true;
	}
	/* 緯度経度フォーマットに合致するか */
	var latlon = new Array();
	var dms;
	var ll = word.split(',');
	if (ll[0]) ll[0] = ll[0].trim();
	if (ll[1]) ll[1] = ll[1].trim();
	if (ll[0] && ll[1]) {
		for (var i = 0; i <= 1; i++) {
			/* 度分秒 */
			if (ll[i].match(LL_REG_DMS)) {
				dms = ll[i].split('.');
				latlon[i] = ZDC.dmsTodeg(parseInt(dms[0]), parseInt(dms[1]), parseInt(dms[2])+'.'+parseInt(dms[3]));
			/* ミリ秒 */
			} else if (ll[i].match(LL_REG_MS)) {
				latlon[i] = ZDC.msTodeg(ll[i]);
			/* 10進 */
			} else if (ll[i].match(LL_REG_DEG)) {
				latlon[i] = ll[i];
			} else {
				break;
			}
		}
		if (latlon[0] && latlon[1]) {
			/* 日本領土内かどうかチェック */
			if (latlon[0] >= JPNAREA.minlat && latlon[0] <= JPNAREA.maxlat && latlon[1] >= JPNAREA.minlon && latlon[1] <= JPNAREA.maxlon) {
			} else {
				alert(MSG_ERR_LL_OUT);
				return true;
			}
			/* 緯度経度位置へ移動 */
			var loc = new ZDC.LatLon(latlon[0], latlon[1]);
			DmapMap.moveLatLon(loc);
			/* マーカー表示 */
			DmapPlotSearchMarker(loc);
			return true;
		}
	}
	return false;
}

/**
 * 検索位置マーカーを表示します。
 * @param {Object} latlon 緯度経度オブジェクト
 * @return {void}
 */
function DmapPlotSearchMarker(latlon) {
	if (DmapSearchMarker) DmapMap.removeWidget(DmapSearchMarker);
	DmapSearchMarker = new ZDC.Marker(latlon, {
		offset: new ZDC.Pixel(-18, -18),
		custom: {
			base: {src: './img/item.png', imgSize: new ZDC.WH(36, 34), imgTL: new ZDC.TL(0, 80)}
		},
		propagation: true
	});
	DmapMap.addWidget(DmapSearchMarker);
}

/**
 * 右エリア閉じるボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickRClose() {
	var n = document.getElementById('area_right');
	var m = document.getElementById('area_right_min');
	if (n && m) {
		//n.style.display = 'none';
		//n.style.visibility = 'hidden';
		n.style.top = '-9999px';
		m.style.display = 'block';
	}
	var t = document.getElementById('area_top');
	if (t) t.style.visibility = 'hidden';
	var b = document.getElementById('area_bottom');
	if (b) b.style.visibility = 'hidden';
}

/**
 * 右エリア開くボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickROpen() {
	var n = document.getElementById('area_right');
	var m = document.getElementById('area_right_min');
	if (n && m) {
		m.style.display = 'none';
		//n.style.display = 'block';
		//n.style.visibility = 'visible';
		n.style.top = m.style.top;
	}
	var t = document.getElementById('area_top');
	if (t) t.style.visibility = 'visible';
	var b = document.getElementById('area_bottom');
	if (b) b.style.visibility = 'visible';
}

/**
 * 現在地マーカーを表示します。
 * @param {Object} latlon 緯度経度オブジェクト
 * @return {void}
 */
function DmapPlotLocationMarker(latlon) {
	if (DmapLocationMarker) DmapMap.removeWidget(DmapLocationMarker);
	DmapLocationMarker = new ZDC.Marker(latlon, {
		offset: new ZDC.Pixel(-34, -34),
		custom: {
			base: {src: './img/item.png', imgSize: new ZDC.WH(68, 68), imgTL: new ZDC.TL(0, 0)}
		},
		propagation: true
	});
	DmapMap.addWidget(DmapLocationMarker);
}

/**
 * 所属支社ピンを表示します。
 * @param {Object} latlon 緯度経度オブジェクト
 * @return {void}
 */
function DmapPlotSyozokuPin(latlon) {
	if (DmapSyozokuPin) DmapMap.removeWidget(DmapSyozokuPin);
	DmapSyozokuPin = new ZDC.Marker(latlon, {
		offset: new ZDC.Pixel(-22, -47),
		custom: {
			base: {src: './img/pin.png', imgSize: new ZDC.WH(45, 47)}
		}
	});
	DmapMap.addWidget(DmapSyozokuPin);
}

/**
 * 所属支社ピンに支社名を表示します。
 * @return {void}
 */
function DmapShowSyozokuPinNm() {
	if (DmapSyozokuPin && !DmapSyozokuPinNm) {
		var nm = DmapGetValueById('IGP021');
		var html = '<div><div class="pointname">'+nm+'</div></div>';
		DmapSyozokuPinNm = new ZDC.UserWidget(DmapSyozokuPin.getLatLon(), {
			html: html,
			offset: new ZDC.Pixel(SYZ_NAME_OFFSET_X, SYZ_NAME_OFFSET_Y),
			propagation: false
		});
		DmapMap.addWidget(DmapSyozokuPinNm);
		DmapSyozokuPinNm.open();
	}
}

/**
 * 「現在地を表示」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickLoc() {
	/* 利用状況ログ */
	DmapLogCount(3);
	/* 現在地取得 */
	var res = DmapGetLocation(true);
	if (res.ret == 0) {
		DmapPlotLocationMarker(res.latlon);
		DmapMap.moveLatLon(res.latlon);
	}
}

/**
 * 「支社を表示」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickSyozoku() {
	/* 利用状況ログ */
	DmapLogCount(4);
	var loc = DmapGetSyozokuLatLon();
	if (loc) {
		DmapMap.moveLatLon(loc);
	}
	/* 所属支社名を表示 */
	DmapShowSyozokuPinNm();
}

/**
 * ポイント名表示中かどうかの状態を取得します。
 * @return {Boolean} true：ポイント名表示中
 */
function DmapIsShowPointNameOn() {
	return (DmapGetValueById('BTNCOND').substr(0,1) == "1");
}

/**
 * ポイント名表示中かどうかの状態を切り替えます。
 * @param {Boolean} on true：ポイント名表示中
 * @return {void}
 */
function DmapSetShowPointNameOnOff(on) {
	var e = document.getElementById('BTNCOND');
	e.value = (on?'1':'0')+e.value.substr(1,1);
	var btn = document.getElementById('f_btn_pv');
	if (btn) {
		btn.className = 'f_btn_pv_'+(on?'on':'off');
	}
}

/**
 * 業種名表示中かどうかの状態を取得します。
 * @return {Boolean} true：業種名表示中
 */
function DmapIsShowGyosyuOn() {
	return (DmapGetValueById('BTNCOND').substr(1,1) == "1");
}

/**
 * 業種名表示中かどうかの状態を切り替えます。
 * @param {Boolean} on true：業種名表示中
 * @return {void}
 */
function DmapSetShowGyosyuOnOff(on) {
	var e = document.getElementById('BTNCOND');
	e.value = e.value.substr(0,1)+(on?'1':'0');
	var btn = document.getElementById('f_btn_gyo');
	if (btn) {
		btn.className = 'f_btn_gyo_'+(on?'on':'off');
	}
}

/**
 * 「ポイント名表示」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickShowPointName() {
	/* 表示中 */
	if (DmapIsShowPointNameOn()) {
		/* 消去する */
		DmapSetShowPointNameOnOff(false);
		DmapPinList.removePointName();
	/* 表示中でない */
	} else {
		/* 表示する */
		DmapSetShowPointNameOnOff(true);
		DmapPinList.showPointName();
	}
}

/**
 * 「業種名表示」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickShowGyosyu() {
	/* 表示中 */
	if (DmapIsShowGyosyuOn()) {
		/* 消去する */
		DmapSetShowGyosyuOnOff(false);
		DmapPinList.removeGyosyu();
	/* 表示中でない */
	} else {
		/* 表示する */
		DmapSetShowGyosyuOnOff(true);
		DmapPinList.showGyosyu();
	}
}

/**
 * ヘッダーエリアを無効化します。
 * @return {void}
 */
function DmapDisableTop() {
	var div = document.getElementById('disable_top');
	if (div) {
		div.style.display = 'block';
	}
	/* 社内情報検索明細を閉じる */
	DmapSrchPointDtlOff();
}
/**
 * ヘッダーエリアを有効化します。
 * @return {void}
 */
function DmapEnableTop() {
	var div = document.getElementById('disable_top');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * 「社内情報検索」ボタンを無効化します。
 * @return {void}
 */
function DmapDisableSrchP() {
	var div = document.getElementById('disable_srchp');
	if (div) {
		div.style.display = 'block';
	}
	/* 社内情報検索明細を閉じる */
	DmapSrchPointDtlOff();
}
/**
 * 「社内情報検索」ボタンを有効化します。
 * @return {void}
 */
function DmapEnableSrchP() {
	var div = document.getElementById('disable_srchp');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * 右エリアを無効化します。
 * @return {void}
 */
function DmapDisableRight() {
	var div = document.getElementById('disable_right');
	if (div) {
		div.style.display = 'block';
	}
	/* ポイント表示変更ダイアログを閉じる */
	DmapCloseSelPoint();
}
/**
 * 右エリアを有効化します。
 * @return {void}
 */
function DmapEnableRight() {
	var div = document.getElementById('disable_right');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * フッターエリアを無効化します。
 * @return {void}
 */
function DmapDisableBottom() {
	var div = document.getElementById('disable_bottom');
	if (div) {
		div.style.display = 'block';
	}
}
/**
 * フッターエリアを有効化します。
 * @return {void}
 */
function DmapEnableBottom() {
	var div = document.getElementById('disable_bottom');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * 地図エリアを無効化します。
 * @return {void}
 */
function DmapDisableMapArea() {
	var div = document.getElementById('disable_map');
	if (div) {
		div.style.display = 'block';
	}
}
/**
 * 地図エリアを有効化します。
 * @return {void}
 */
function DmapEnableMapArea() {
	var div = document.getElementById('disable_map');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * 地図のイベントを無効化します。
 * @return {void}
 */
function DmapDisableMapEvent() {
	DmapMapEventEnable = false;
}
/**
 * 地図のイベントを有効化します。
 * @return {void}
 */
function DmapEnableMapEvent() {
	DmapMapEventEnable = true;
}

/**
 * 全てのエリアと地図を無効化します。
 * @return {void}
 */
function DmapDisableAllArea() {
	DmapDisableMode = 'AllArea';
	DmapDisableTop();
	DmapDisableRight();
	DmapDisableBottom();
	DmapDisableMapArea();
}
/**
 * 無効にした全てのエリアと地図を元に戻します。
 * @return {void}
 */
function DmapEnableAllArea() {
	DmapDisableMode = '';
	DmapEnableTop();
	DmapEnableRight();
	DmapEnableBottom();
	DmapEnableMapArea();
}

/**
 * 全てのエリアと地図イベントを無効化します。
 * @return {void}
 */
function DmapDisableAllEvent() {
	DmapDisableMode = 'AllEvent';
	DmapDisableTop();
	DmapDisableRight();
	DmapDisableBottom();
	DmapDisableMapEvent();
}
/**
 * 無効にした全てのエリアと地図イベントを元に戻します。
 * @return {void}
 */
function DmapEnableAllEvent() {
	DmapDisableMode = '';
	DmapEnableTop();
	DmapEnableRight();
	DmapEnableBottom();
	DmapEnableMapEvent();
}

/**
 * 社内情報検索、右エリア、下エリア、地図イベントを無効化します。
 * @return {void}
 */
function DmapDisableAllForRouteDlg() {
	DmapDisableMode = 'AllForRouteDlg';
	DmapDisableSrchP();
	DmapDisableRight();
	DmapDisableBottom();
	DmapDisableMapEvent();
}
/**
 * 無効にした社内情報検索、右エリア、下エリア、地図イベントを元に戻します。
 * @return {void}
 */
function DmapEnableAllForRouteDlg() {
	DmapDisableMode = '';
	DmapEnableSrchP();
	DmapEnableRight();
	DmapEnableBottom();
	DmapEnableMapEvent();
}

/**
 * 社内情報検索、下エリア、地図イベントを無効化します。
 * @return {void}
 */
function DmapDisableAllForRouteResult() {
	DmapDisableMode = 'AllForRouteResult';
	DmapDisableSrchP();
	DmapDisableBottom();
	DmapDisableMapEvent();
}
/**
 * 無効にした社内情報検索、下エリア、地図イベントを元に戻します。
 * @return {void}
 */
function DmapEnableAllForRouteResult() {
	DmapDisableMode = '';
	DmapEnableSrchP();
	DmapEnableBottom();
	DmapEnableMapEvent();
}

/**
 * 移動距離を表示します。
 * @return {Boolean} true：移動距離を表示／false：移動距離を表示しない
 */
function DmapShowIdoKyori() {
	/* 移動距離表示フラグ取得 */
	var iskyori = DmapGetValueById("ISKYORI");
	if (!iskyori) return false;
	/* 移動距離表示フラグが1か9ならば、移動距離表示を行う */
	if (iskyori == 1 || iskyori == 9) {
		if (DmapPinList.Pins.length > 0) {
			/* 所属支社の緯度経度取得 */
			var slatlon = DmapGetSyozokuLatLon();
			if (slatlon === null) return false;
			var latlons = new Array();
			/* 始点は所属支社の緯度経度 */
			latlons.push(slatlon); 
			/* 中継点は訪問先の緯度経度 */
			for (var i=0, len=DmapPinList.Pins.length; i<len; i++) {
				latlons.push(DmapPinList.Pins[i].latlon);
			}
			/* 終点も所属支社の緯度経度 */
			latlons.push(slatlon);
			/* 始点から終点までを線でつないで描画 */
			DmapIdoKyori = new ZDC.Polyline(latlons, {
				strokeColor: '#0000FF',
				strokeWeight: 5,
				lineOpacity: 0.5,
				lineStyle: 'solid'
			});
			DmapMap.addWidget(DmapIdoKyori);
		}
		/* 移動距離を取得 */
		var kyori = DmapGetValueById("KYORI");
		/* ダイアログ表示 */
		var elm = document.getElementById("kyori_dlg_txt");
		elm.innerText = ISKYORI_MESSAGE[iskyori].replace('{kyori}', kyori);
		DmapOpenIdoKyori();
		return true;
	}
	return false;
}

/**
 * 移動距離を消去します。
 * @return {void}
 */
function DmapRemoveIdoKyori() {
	if (DmapIdoKyori) {
		DmapMap.removeWidget(DmapIdoKyori);
		DmapIdoKyori = null;
	}
}

/**
 * 「移動距離」ダイアログを開きます。
 * @return {void}
 */
function DmapOpenIdoKyori() {
	var dlg = document.getElementById('kyori_dlg');
	if (dlg) {
		dlg.style.display = 'block';
		/* 背面を触れなくする */
		DmapDisableAllArea();
	}
}
/**
 * 「移動距離」ダイアログを閉じます。
 * @return {void}
 */
function DmapCloseIdoKyori() {
	var dlg = document.getElementById('kyori_dlg');
	if (dlg) {
		dlg.style.display = 'none';
	}
	/* 背面を元に戻す */
	DmapEnableAllArea();
}

/**
 * 「見込客登録」フキダシを表示します。
 * @return {void}
 */
function DmapShowMikomiKyaku() {
	/* フキダシを消去 */
	DmapRemoveMikomiKyaku();
	/* 地図縮尺 */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_PSPECT_CUST.min && z <= NGZOOM_PSPECT_CUST.max) {
		alert(MSG_ERR_MIKOMI_NGZOOM);
		return;
	}
	/* 右クリック地点の座標取得 */
	var latlon = DmapMap.getPointerPosition();
	DmapRightClickMode = 0;
	/* 緯度経度から住所を検索 */
	ZDC.Search.getAddrByLatLon({
		latlons: [latlon],
		datum: 'TOKYO'
	}, function(status, res) {
		if (status.code == '000' && res[0] && res[0].address) {
			/* 検索結果から住所を取得 */
			var addr = res[0].address.text;
			/* 緯度経度、住所をHIDDENタグに埋め込む */
			var hilat = document.getElementById('HILAT');
			if (!hilat) return;
			var hilon = document.getElementById('HILON');
			if (!hilon) return;
			var hiadd = document.getElementById('HIADD');
			if (!hiadd) return;
			/* 緯度経度の小数点8桁以降は切り捨て */
			hilat.value = Math.floor(latlon.lat * 10000000) / 10000000;
			hilon.value = Math.floor(latlon.lon * 10000000) / 10000000;
			hiadd.value = addr;
			/* フキダシを表示 */
			var html;
			html =  '<div id="rp_div">';
			html += '<div id="mik_dlg_txt">'+addr+'</div>';
			html += '<div id="mik_dlg_btn">';
			html += '<button type="button" class="dlg_btn_ok" onclick="DmapSubmitMikomiKyaku();">見込客登録</button>';
			html += '<button type="button" class="dlg_btn_ok" onclick="DmapRemoveMikomiKyaku();">キャンセル</button>';
			html += '</div>';
			html += '</div>';
			DmapMikomiKyaku = new ZDC.MsgInfo(latlon, {html: html, closeBtn: false});
			DmapMap.addWidget(DmapMikomiKyaku);
			DmapMikomiKyaku.open();
			/* 背面を無効化する */
			DmapDisableAllEvent();
		} else {
			alert(MSG_ERR_MIKOMI_ADDR);
		}
		DmapRightClickMode = 1;
	});
}

/**
 * 「見込客登録」フキダシを消去します。
 * @return {void}
 */
function DmapRemoveMikomiKyaku() {
	if (DmapMikomiKyaku) {
		DmapMap.removeWidget(DmapMikomiKyaku);
		DmapMikomiKyaku = null;
	}
	DmapEnableAllEvent();
}

/**
 * 見込客登録を実行します。
 * @return {void}
 */
function DmapSubmitMikomiKyaku() {
	var btn = document.getElementById('BTNCUST');
	if (btn) {
		/* 利用状況ログ */
		DmapLogCount(11);
		btn.click();
	}
	/* 「見込客登録」フキダシを消去 */
	DmapRemoveMikomiKyaku();
}

/**
 * 「ルート検索」ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickRouteSearch() {
	/* ポイントランチャーを消去 */
	DmapRemoveLauncher();
	/* ダイアログ表示 */
	DmapShowRouteSearchDlg("rs_dlg");
}

/**
 * ルート表示機能を開始します。
 * @param {Number} seq ピンの連番
 * @return {void}
 */
function DmapStartPinRoute(seq) {
	var latlon, place;
	/* 現在地を取得 */
	var res = DmapGetLocation();
	if (res.ret == 0) {
		latlon = res.latlon;
		place = "現在地";
		DmapPlotLocationMarker(latlon);
	} else {
		/* 現在地を取得できなかったら所属支社の緯度経度取得 */
		latlon = DmapGetSyozokuLatLon();
		place = "所属支社";
	}
	/* ダイアログ表示 */
	DmapShowRouteSearchDlg("rv_dlg");
	/* 出発地を設定 */
	DmapRouteSearch.setPoint('start', latlon, place);
	/* 目的地を設定 */
	latlon = DmapPinList.Pins[seq].latlon;
	place = DmapPinList.Pins[seq].name;
	DmapRouteSearch.setPoint('end', latlon, place);
}

/**
 * ルート検索ダイアログを表示します。
 * @param {String} dlg_id ダイアログID
 * @return {void}
 */
function DmapShowRouteSearchDlg(dlg_id) {
	/* グループピン一覧を消去 */
	DmapRemovePinSelect();
	/* 「見込客登録」フキダシを消去 */
	DmapRemoveMikomiKyaku();
	/* すでにダイアログが開いている場合はキャンセルする */
	if (DmapRouteSearch) DmapRouteSearchCancel();
	/* DmapRouteSearchオブジェクト生成 */
	DmapRouteSearch = new DmapClassRouteSearch(dlg_id);
	/* ダイアログを開く */
	DmapRouteSearch.openDialog();
	/* 背面を無効化 */
	DmapDisableAllForRouteDlg();
	DmapRightClickMode = 0;
}

/**
 * ルート検索ダイアログを閉じます。
 * @return {void}
 */
function DmapCloseRouteSearchDlg() {
	/* ダイアログを閉じる */
	DmapRouteSearch.closeDialog();
	DmapRightClickMode = 1;
}

/**
 * ルート検索ダイアログのモード切り替えボタンクリック時の処理。
 * @param {String} mode ルートモード（walk：歩行者／car：車／train：電車）
 * @return {void}
 */
function DmapOnClickRouteMode(mode) {
	DmapRouteSearch.changeMode(mode);
}

/**
 * ルート検索ダイアログの「出発地」「目的地」ボタンクリック時の処理。
 * @param {String} type 地点のタイプ（start：出発地／end：目的地）
 * @return {void}
 */
function DmapOnClickRoutePoint(type) {
	DmapRouteSearch.searchPoint(type);
}

/**
 * ルート検索を実行します。
 * @return {void}
 */
function DmapRouteSearchExecute() {
	/* ルート検索実行 */
	DmapRouteSearch.execSearch(function () {
		/* ルート検索ダイアログを閉じる */
		DmapCloseRouteSearchDlg();
		/* 表示済みのランチャーを消去 */
		DmapRemoveLauncher();
		/* 移動距離表示を削除 */
		DmapRemoveIdoKyori();
		/* 右エリアをルート検索結果表示に切り替え */
		DmapChangeScreen('rs_result');
	});
}

/**
 * ルート検索ダイアログの検索をキャンセル。
 * @return {void}
 */
function DmapRouteSearchCancel() {
	/* ルート検索のウィジェットをすべて削除 */
	DmapRouteSearch.removeAllWidget();
	/* ルート検索ダイアログを閉じる */
	DmapCloseRouteSearchDlg();
	/* ルート検索オブジェクトを開放 */
	DmapRouteSearch = null;
	/* 背面の無効化を元に戻す */
	DmapEnableAllForRouteDlg();
}

/**
 * ルート検索結果の候補表示ボタンクリック時の処理。
 * @return {void}
 */
function DmapOnClickRouteSelect() {
	DmapRouteSearch.toggleResultList();
}

/**
 * ルート検索結果の候補リストクリック時の処理。
 * @param {Number} idx 候補番号
 * @return {void}
 */
function DmapOnClickRouteListRow(idx) {
	DmapRouteSearch.changeResult(idx);
}

/**
 * ルート検索結果を閉じます。
 * @return {void}
 */
function DmapRouteSearchResultClose() {
	/* ルート検索のウィジェットをすべて削除 */
	DmapRouteSearch.removeAllWidget();
	/* 右エリアをデフォルト表示に切り替え */
	DmapChangeScreen();
	/* ルート検索オブジェクトを開放 */
	DmapRouteSearch = null;
	DmapRightClickMode = 1;
}

/**
 * 画面の表示内容を切り替えます。
 * @param {String} mode 表示モード（rs_result：ルート検索結果表示／省略時はデフォルト表示）
 * @return {void}
 */
function DmapChangeScreen(mode) {
	var div_def = document.getElementById("default_view");
	var div_rs = document.getElementById("rs_result_view");
	if (mode == 'rs_result') {
		/* 右エリアの表示をルート検索結果に切り替え */
		if (div_def) div_def.style.display = 'none';
		if (div_rs) div_rs.style.display = 'block';
		DmapEnableAllEvent();
		DmapDisableAllForRouteResult();
	} else {
		/* 右エリアの表示をデフォルトに切り替え */
		if (div_def) div_def.style.display = 'block';
		if (div_rs) div_rs.style.display = 'none';
		DmapEnableAllForRouteResult();
	}
}

/**
 * 地図の中心を指定した緯度経度に移動する
 * @param {Number} lat 緯度
 * @param {Number} lon 経度
 * @return {void}
 */
function DmapMoveLatlon(lat, lon) {
	DmapMap.moveLatLon(new ZDC.LatLon(lat, lon));
}

/* ロード時の処理を実行 */
if (window.attachEvent) {
	window.attachEvent('onload', DmapOnLoad);
} else {
	window.onload = function(){
		DmapOnLoad();
	}
}
