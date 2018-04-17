/**
 * �y�[�W���[�h���̏����B
 * @return {void}
 */
function DmapOnLoad() {
	/* Cookie����hidden�ɃZ�b�g */
	RestoreCookieLog();
	/* �����\���t���O */
	var isfirst = (DmapGetValueById('ISFIRST') == '1' ? true : false);
	/* ����Ҍ����ɂ��\������ */
	DmapUser = new DmapClassUser();
	DmapRefreshByAuth();
	/* �����x�Јʒu */
	var syzloc = DmapGetSyozokuLatLon();
	/* �����[�h���̌��ݒn */
	var nowlat = DmapGetValueById('NOWLAT');
	var nowlon = DmapGetValueById('NOWLON');
	/* �����[�h���̒n�}�ʒu */
	var clat = DmapGetValueById('CLAT');
	var clon = DmapGetValueById('CLON');
	var scale = DmapGetValueById('SCALE');
	var hid;
	hid = document.getElementById('CLAT');if (hid) hid.value = '';
	hid = document.getElementById('CLON');if (hid) hid.value = '';
	hid = document.getElementById('SCALE');if (hid) hid.value = '';
	/* �����\���܂��́A�����[�h�����S�ʒu���Ȃ��ꍇ */
	if (isfirst || !clat || !clon) {
		/* ���ݒn���擾 */
		var loc = DmapGetLocation();
		if (loc.ret == 0) {
			/* ���ݒn�𒆐S�Ƃ��� */
			DmapMapOpt.latlon = loc.latlon;
		} else {
			/* ���ݒn���擾�ł��Ȃ������珊���x�Ђ𒆐S�Ƃ��� */
			DmapMapOpt.latlon = syzloc;
		}
	/* �����[�h���i���S�ʒu����j */
	} else {
		/* �����[�h���̌��ݒn�𒆐S�Ƃ��� */
		DmapMapOpt.latlon = new ZDC.LatLon(clat, clon);
	}
	/* �n�}�𐶐� */
	DmapMap = new ZDC.Map(document.getElementById('map'), DmapMapOpt);
	/* �X�P�[���o�[��\�� */
	var sbar = new ZDC.ScaleBar({bottom:40,left:10});
	DmapMap.addWidget(sbar);
	/* �n�}�R���g���[����\�� */
	var control = new ZDC.Control(DmapMapControl);
	DmapMap.addWidget(control);
	/* �����\���܂��́A�����[�h�����S�ʒu���Ȃ��ꍇ */
	if (isfirst || !clat || !clon) {
		/* ���ݒn�Ƀ}�[�J�[��\������ */
		if (loc && loc.latlon) {
			DmapPlotLocationMarker(loc.latlon);
		}
	/* �����[�h���i���S�ʒu����j */
	} else {
		/* �����[�h���̏k�� */
		if (scale != '') {
			DmapMapReloadScale = parseInt(scale);
		}
		/* �����[�h���̌��ݒn�Ƀ}�[�J�[��\������ */
		if (nowlat && nowlon) {
			DmapPlotLocationMarker(new ZDC.LatLon(nowlat, nowlon));
		}
	}
	/* �x�Ѓs���\�� */
	if (syzloc) {
		DmapPlotSyozokuPin(syzloc);
	}
	/* �n�}�ɃC�x���g��ǉ� */
	ZDC.addListener(DmapMap, ZDC.MAP_MOUSEMOVE, DmapOnMouseMove);
	ZDC.addListener(DmapMap, ZDC.MAP_MOUSEUP, DmapOnMouseUp);
	ZDC.addListener(DmapMap, ZDC.MAP_DBLCLICK, DmapOnDblClick);
	ZDC.addListener(DmapMap, ZDC.MAP_RIGHTCLICK, DmapOnRightClick);
	ZDC.addListener(DmapMap, ZDC.MAP_CLICK, DmapOnClick);
	/* document�ɃC�x���g��ǉ� */
	ZDC.addDomListener(document, 'mouseup', DmapOnMouseUp);
	/* �n�}�ȊO�̃z�C�[���C�x���g�𖳌��� */
	var area;
	area = document.getElementById('area_top');
	DmapAddEvent(area, 'mousewheel', DmapOnMouseWheel);
	area = document.getElementById('area_right');
	DmapAddEvent(area, 'mousewheel', DmapOnMouseWheel);
	area = document.getElementById('area_bottom');
	DmapAddEvent(area, 'mousewheel', DmapOnMouseWheel);
	/* �K���s���\�� */
	DmapRefreshPins();
	/* �ړ������\�� */
	var kyori = DmapShowIdoKyori();
	/* ON/OFF�{�^���\������ */
	if (DmapIsShowPointNameOn()) {
		DmapSetShowPointNameOnOff(true);
	}
	if (DmapIsShowGyosyuOn()) {
		DmapSetShowGyosyuOnOff(true);
	}
	if (kyori) {
		/* ���p�󋵃��O */
		DmapLogCount(12);
	} else {
		if (isfirst) {
			/* ���p�󋵃��O */
			DmapLogCount(1);
		}
	}
}

/**
 * �O���[�v�ɑ�����s���̃I�u�W�F�N�g��z��ŕԋp���܂��B
 * @param {String} gid �O���[�vID
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
 * �K���s�����擾���Ēn�}��ɕ\�����܂��B
 * @return {void}
 */
function DmapRefreshPins() {
	/* �s�������� */
	DmapRemovePins();
	/* �s���̏���hidden����擾 */
	DmapPinList = new DmapClassPinList();
	/* �s����n�}��ɔz�u */
	DmapPlotPins();
	/* �ڍ׏���\�� */
	DmapRefreshPinList();
}

/**
 * �K���s����n�}��ɕ\�����܂��B
 * @return {void}
 */
function DmapPlotPins() {
	var latlons = new Array();
	/* �x�Ѓs�� */
	var syz = DmapGetSyozokuLatLon();
	if (syz) {
		latlons.push(syz);
		/* �����offset */
		syz = new ZDC.LatLon(parseFloat(syz.lat)+PIN_OFFSET_LAT, syz.lon);
		latlons.push(syz);
	}
	/* �K���s�� */
	var len = DmapPinList.Pins.length;
	if (len > 0) {
		for (var i = len-1; i >= 0; i--) {
			if (DmapPinList.Pins[i].plot) {
				DmapPinList.Pins[i].newWidget();
				latlons.push(DmapPinList.Pins[i].latlon);
				/* �����offset */
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
	/* �����[�h���̏k�� */
	if (DmapMapReloadScale >= 0) {
		DmapMap.setZoom(DmapMapReloadScale);
		DmapMapReloadScale = -1;
	}
}

/**
 * �n�}��̃s����S�ď������܂��B
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
 * �K���ڍ׏��i�ꗗ�j�̕\���؂�ւ��{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickSwitchPinList() {
	DmapPinListSimple = (!DmapPinListSimple);
	DmapRefreshPinList();
}

/**
 * �K���ڍ׏��i�ꗗ�j��\�����܂��B
 * @return {void}
 */
function DmapRefreshPinList() {
	var len = DmapPinList.Pins.length;
	var div = document.getElementById("list_div");
	if (!div) return;
	/* div�����N���A */	
	DmapClearListDiv();
	/* �w�b�_�\�� */
	var hd = document.createElement('div');
	hd.id = 'dtl_hd';
	if (len == 0) {
		hd.innerHTML = '�ڍ׏��';
	} else {
		hd.innerHTML = '�ڍ׏��'
			+ '<a href="javascript:void(0);" id="dtl_sw" onClick="DmapOnClickSwitchPinList();" onFocus="this.blur();">�@</a>'
		;
	}
	div.appendChild(hd);
	/* �ꗗ�\�� */
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
				+ '�@</a>'
				+ '<div class="dtl_name">'
				+ '<a href="javascript:void(0);" onClick="DmapMoveCenterToPin('+p.seq+');" onFocus="this.blur();">'
				+ p.num_on_list+'.'+p.name
				+ '</a>'
				+ '</div>'
			;
			if (!DmapPinListSimple) {
				if (p.adrk) html += '<div class="dtl_adrk">'+ p.adrk + '</div>';
				if (p.tel) html += '<div class="dtl_tel">'+ p.tel + '</div>';
				if (p.formatAtr()) html += '<div class="dtl_atr">�y'+ p.formatAtr() + '�z</div>';
			}
			td.innerHTML = html;
		}
		body.appendChild(tbl);
	} else {
	}
	div.appendChild(body);
}

/**
 * �ꗗ���N���A���܂��B
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
 * �K���ڍ׏��i�ꗗ�j���A�w��s���̈ʒu�܂ŃX�N���[�����܂��B
 * @param {Number} seq �s���̘A��
 * @return {void}
 */
function DmapPinListScrollTo(seq) {
	var a = document.getElementById('dtl_i_'+seq);
	if (a) a.focus();
}

/**
 * GPS���ݒn�擾�֐����猻�ݒn���擾���A�}�[�J�[��\�����܂��B
 * @param {Boolean} alt true�F���ݒn�擾���s���ɃA���[�g�\������B
 * @return {Array} ret�F���ʃR�[�h�Alatlon�FZDC.LatLon�I�u�W�F�N�g
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
 * �����x�Ђ̈ܓx�o�x��ԋp���܂��B
 * @return {Object} ZDC.LatLon�I�u�W�F�N�g
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
 * �s���̈ʒu�֒n�}���ړ������܂��B
 * @param {Number} seq �s���̘A��
 * @return {void}
 */
function DmapMoveCenterToPin(seq) {
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	DmapMap.moveLatLon(p.latlon);
	p.moveTop();
}

/**
 * �s���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickPin() {
	/* �n�}���������͉������Ȃ� */
	if (!DmapMapEventEnable) return;
	/* �\���ʒu�C�����[�h�̎��͉������Ȃ� */
	if (DmapMovePinMode) return;
	/* �\���ς݂̃����`���[������ */
	DmapRemoveLauncher();
	/* �\���ς݂̃s���ꗗ������ */
	DmapRemovePinSelect();
	/* �Y���s���𒆐S�� */
	DmapMoveCenterToPin(this.seq);
//	/* �s�������擾 */
//	var p = DmapPinList.Pins[seq];
//	if (!p || !p.latlon) return;
	/* �O���[�v�̏ꍇ�̓s���ꗗ��\������ */
	if (this.inGroup()) {
		DmapShowPinSelect(this.seq, 'DmapOnClickPinSelect', 'DmapRemovePinSelect');
	/* �P�Ƃ̏ꍇ�̓|�C���g�����`���[��\������ */
	} else {
		DmapShowLauncher(this.seq);
	}
}

/**
 * �ui�v�N���b�N���̏����B
 * @param {Number} seq �s���̘A��
 * @return {void}
 */
function DmapOnClickInfo(seq) {
	/* �\���ʒu�C�����[�h�̎��͉������Ȃ� */
	if (DmapMovePinMode) return;
	/* �\���ς݂̃����`���[������ */
	DmapRemoveLauncher();
	/* �\���ς݂̃s���ꗗ������ */
	DmapRemovePinSelect();
	/* �Y���s���𒆐S�� */
	DmapMoveCenterToPin(seq);
	/* �s�������擾 */
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	/* �|�C���g�����`���[��\������ */
	DmapShowLauncher(seq);
}

/**
 * �O���[�v�̃s���ꗗ��\�����܂��B
 * @param {Number} seq �s���̘A��
 * @param {Function} func �����N�N���b�N���ɌĂяo���֐���
 * @param {String} close ���鎞�ɌĂяo���֐���
 * @return {void}
 */
function DmapShowPinSelect(seq, func, close) {
	/* �s�������擾 */
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	if (!p.inGroup()) return;
	/* �O���[�v�̃s���i�����j���擾 */
	var plist = DmapGetGroupPinList(p.gid);
	/* �ꗗ�𐶐� */
	var html = '';
	html += '<div id="p_select_hd">';
	html += '<a id="p_select_close" href="javascript:void(0);" onClick="'+close+'();">�@</a>';
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
	/* �\���ʒu�i�ܓx�o�x�j�����߂� */
	var ll = p.latlon;
	/* offset�����߂� */
	var listsize = DmapGetHTMLSize(html);
	/* �ꗗ��\�� */
	DmapPinSelect = new ZDC.MsgInfo(p.latlon, {
		html: html,
		offset: new ZDC.Pixel(0, -25),
		closeBtn: false
	});
	DmapMap.addWidget(DmapPinSelect);
	DmapPinSelect.open();
	/* �t�L�_�V�ȊO�𖳌��� */
	DmapDisableTop();
	DmapDisableRight();
	DmapDisableBottom();
	DmapDisableMapEvent();
}

/**
 * �O���[�v�s���ꗗ���������܂��B
 * @return {void}
 */
function DmapRemovePinSelect() {
	if (DmapPinSelect) {
		DmapMap.removeWidget(DmapPinSelect);
		DmapPinSelect = null;
	}
	/* �����������ɖ߂� */
	DmapEnableTop();
	DmapEnableRight();
	DmapEnableBottom();
	DmapEnableMapEvent();
}

/**
 * �O���[�v�s���ꗗ�̃N���b�N���̏����B
 * @param {Number} seq �s���̘A��
 * @return {void}
 */
function DmapOnClickPinSelect(seq) {
	/* �\���ς݂̃����`���[������ */
	DmapRemoveLauncher();
	/* �\���ς݂̃s���ꗗ������ */
	DmapRemovePinSelect();
	/* �Y���s���𒆐S�� */
	DmapMoveCenterToPin(seq);
	/* �|�C���g�����`���[�\�� */
	DmapShowLauncher(seq);
}

/**
 * �|�C���g�����`���[��\�����܂��B
 * @param {Number} seq �s���̘A��
 * @return {void}
 */
function DmapShowLauncher(seq) {
	var cnt,cond,i;
	/* �s�������擾 */
	var p = DmapPinList.Pins[seq];
	if (!p || !p.latlon) return;
	/* �ڍ׏�񓪏o�� */
	DmapPinListScrollTo(p.seq);
	/* �|�C���g�����`���[���� */
	var html = '';
	/* ���� */
	html += '<div id="pl_name">'+p.name+'</div>';
	/* �����A�C�R�� */
	var atr_idx = new Array();
	for (i = 0; i < PIN_ATR_COUNT; i++) {
		if (p.atr[i] == COND_ENABLE || p.atr[i] == COND_DISABLE) atr_idx.push(i);
	}
	cnt = atr_idx.length;
	if (cnt > 0) {
		html += '<div id="pl_atr">';
		for (i = 0; i < cnt; i++) {
			cond = p.atr[atr_idx[i]];
			html += '<span class="pl_atr'+atr_idx[i]+'_'+cond+'">�@</span>';
		}
		html += '</div>';
	}
	html += '</td></tr>';
	/* �@�\���j���[ */
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
						+' onClick="DmapClickMenu('+p.seq+','+icon_idx[i]+');" onFocus="this.blur();">�@</a>';
			} else {
				html += '<span class="pl_menu'+icon_idx[i]+'_'+cond+'">�@</span>';
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
	/* �|�C���g�����`���[�\�� */
	html = '<div id="pl_div">'+html+'</div>';
	DmapLauncher = new ZDC.MsgInfo(p.latlon, {
		html: html,
		offset: new ZDC.Pixel(0, -25)
	});
	DmapMap.addWidget(DmapLauncher);
	DmapLauncher.open();
	/* �Г���񌟍����ׂ���� */
	DmapSrchPointDtlOff();
	/* �|�C���g�\���ύX�_�C�A���O����� */
	DmapCloseSelPoint();
}
/**
 * �|�C���g�����`���[���������܂��B
 * @return {void}
 */
function DmapRemoveLauncher() {
	if (DmapLauncher) {
		DmapMap.removeWidget(DmapLauncher);
		DmapLauncher = null;
	}
}

/**
 * �|�C���g�����`���[�@�\�{�^�����N���b�N���ꂽ���̏����B
 * @param {Number} seq �s���̘A��
 * @param {Number} idx �@�\�ԍ�
 * @return {void}
 */
function DmapClickMenu(seq, idx) {
	var e,s,btn;
	var p = DmapPinList.Pins[seq];if(!p) return;
	/* ���[�g�\�� */
	if (idx == 9) {
		/* ���[�g�\���_�C�A���O���J�� */
		DmapStartPinRoute(seq);
		return;
	}
	switch (idx) {
		/* ���q���܏�� */
		case 0:
			btn = 'BTNKYAKU';
			/* �E���R�[�h */
			e = document.getElementById('HIIE5001');
			e.value = p.syoku;
			/* ���ރR�[�h */
			e = document.getElementById('HIIF0111');
			e.value = p.buncd;
			/* �����q�ԍ� */
			e = document.getElementById('HIIF0551');
			e.value = p.mkno;
			/* �ڋq�ԍ� */
			e = document.getElementById('HICYA');
			e.value = p.cya;
			/* �S���t���O */
			e = document.getElementById('HIISTAN');
			e.value = p.istan;
			/* ���p�󋵃��O */
			DmapLogCount(15);
			break;
		/* �ŗ��m��� */
		case 1:
			btn = 'BTNZEIRI';
			/* �ŗ��m�o�^�ԍ� */
			e = document.getElementById('HIIE6001');
			e.value = p.zno;
			/* ���p�󋵃��O */
			DmapLogCount(17);
			break;
		/* �f������ */
		case 2:
			btn = 'BTNSNSAI';
			/* �f����R�[�h */
			e = document.getElementById('HIM10091');
			e.value = p.scd;
			/* ���p�󋵃��O */
			DmapLogCount(19);
			break;
		/* ���q���ܖK�� */
		case 3:
			btn = 'BTNHOMON_dummy';
			/* �ڍ׏��s�ԍ� */
			e = document.getElementById('SYOROW');
			e.value = p.seq;
			/* ���p�󋵃��O */
			DmapLogCount(16);
			/* �t���O���Z�b�g */
			resetAllFlg();
			break;
		/* �㗝�X�|�[�^�� */
		case 4:
			btn = 'BTNDAIPO';
			/* �㗝�X�R�[�h */
			e = document.getElementById('HIIK0011');
			e.value = p.dcd;
			/* �E���R�[�h */
			e = document.getElementById('HIIE5001');
			e.value = p.syoku;
			/* ���p�󋵃��O */
			DmapLogCount(18);
			break;
		/* �z�[���y�[�W */
		case 5:
			btn = 'BTNHP';
			/* ���� */
			e = document.getElementById('HINAME');
			e.value = p.name;
			/* �Z�� */
			e = document.getElementById('HIADD');
			e.value = p.adrk;
			/* URL */
			e = document.getElementById('HIURL');
			e.value = p.url;
			/* ���p�󋵃��O */
			DmapLogCount(20);
			break;
		/* �X�P�W���[�� */
		case 6:
			btn = 'BTNSCHED';
			/* �����q�ԍ� */
			e = document.getElementById('HIIF0551');
			e.value = p.mkno;
			/* �@�l�l�敪 */
			e = document.getElementById('HIIF0506');
			e.value = p.hkkbn;
			/* �����q���� */
			e = document.getElementById('HINAME');
			e.value = p.name;
			/* ���p�󋵃��O */
			DmapLogCount(13);
			break;
		/* �}�C�E�m�[�g */
		case 7:
			btn = 'BTNMN';
			/* �����q�ԍ� */
			e = document.getElementById('HIIF0551');
			e.value = p.mkno;
			/* ���p�󋵃��O */
			DmapLogCount(14);
			break;
		/* �����K�C�h �������� */
		case 8:
			/* ���p�󋵃��O */
			DmapLogCount(21);
			break;
	}
	/* �B���{�^���C�x���g���� */
	if (btn) {
		var b = document.getElementById(btn);
		if (b) {
			b.click();
			return;
		}
	}
}

/**
 * ����Ҍ����Ɋ�Â��Ă��{�^������\�����䂵�܂��B
 * @return {void}
 */
function DmapRefreshByAuth() {
	/* ���͗� */
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
	/* �E�G���A�̃{�^�� */
	var rb_div = document.getElementById('rb_div');
	rb_div.innertHTML = '';
	var html = '';
	if (DmapUser.isProper()) {
		html += '<a href="javascript:void(0);" id="rb_selp_dlg" onClick="DmapOnClickSelPoint();" onFocus="this.blur();">�@</a>';
		html += '<a href="javascript:void(0);" id="rb_visit" onClick="DmapOnClickVisitPlan();" onFocus="this.blur();">�@</a>';
		html += '<a href="javascript:void(0);" id="rb_rt" onClick="DmapOnClickRouteSearch();" onFocus="this.blur();">�@</a>';
	} else if (DmapUser.isAgent()) {
		html += '<a href="javascript:void(0);" id="rb_visit" onClick="DmapOnClickVisitPlan();" onFocus="this.blur();">�@</a>';
		html += '<a href="javascript:void(0);" id="rb_selp_ki" onClick="DmapOnClickSpAgent(1);" onFocus="this.blur();">�@</a>';
		html += '<a href="javascript:void(0);" id="rb_selp_zei" onClick="DmapOnClickSpAgent(2);" onFocus="this.blur();">�@</a>';
		html += '<a href="javascript:void(0);" id="rb_selp_sin" onClick="DmapOnClickSpAgent(3);" onFocus="this.blur();">�@</a>';
		html += '<a href="javascript:void(0);" id="rb_rt" onClick="DmapOnClickRouteSearch();" onFocus="this.blur();">�@</a>';
	}
	rb_div.innerHTML = html;
}

/**
 * �u�|�C���g�\���ύX�v�{�^���������̏����B
 * @return {void}
 */
function DmapOnClickSelPoint() {
	/* �_�C�A���O */
	var dlg = document.getElementById('sp_dlg');
	/* �{�^�������� */
	for (var i = 1; i <= 7; i++) {
		/* �����P */
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
		/* �����P���� */
		btn = document.getElementById('sp_cond1d_'+i);
		if (btn) {
			/* ���_��(��ۂ̂�)�͔񊈐��ɂ��� */
			if (i == 3) {
				DmapSPCondBtnCtrl('1d', i, 'dis');
			/* ����ȊO�͊��� */
			} else {
				DmapSPCondBtnCtrl('1d', i, 'ena');
			}
		}
		/* �����Q */
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
	/* ���ה�\�� */
	DmapCloseSPCond1Dtl();
	/* �����Q�i�G�[�W�F���g��p�j */
	var cond2ex = document.getElementById('sp_dlg_cond2ex');
	if (cond2ex) {
		if (DmapUser.getSPCondPattern() == 3) {
			cond2ex.style.display = 'block';
		} else {
			cond2ex.style.display = 'none';
		}
	}
	/* �_�C�A���O�\�� */
	dlg.style.display = 'block';
}

/**
 * �|�C���g�\���ύX�_�C�A���O�����B
 * @return {void}
 */
function DmapCloseSelPoint() {
	var dlg = document.getElementById('sp_dlg');
	dlg.style.display = 'none';
}

/**
 * �|�C���g�\���ύX�����P���ׂ��J���B
 * @return {void}
 */
function DmapOpenSPCond1Dtl() {
	var div = document.getElementById('sp_dlg_cond1_dtl');
	/* ���ׂ̏�Ԃ����t���b�V�� */
	DmapSPCond1DtlRefresh();
	/* ���ו\�� */
	div.style.display = 'block';
}

/**
 * �|�C���g�\���ύX�����P���ׂ̏�Ԃ��A�����P�I����Ԃɉ����Đ��䂷��B
 * @return {void}
 */
function DmapSPCond1DtlRefresh() {
	/* �u�^�[�Q�b�g��Ɓv���I������Ă�����A�u���_��(��ۂ̂�)�v�������ɂ��� */
	var c1 = document.getElementById('sp_cond1_1');
	var d3 = document.getElementById('sp_cond1d_3');
	if (c1 && d3) {
		/* �u�^�[�Q�b�g��Ɓv�I�� */
		if (c1.className == 'sp_cond_sel') {
			if (d3.className == 'sp_cond_dis') {
				DmapSPCondBtnCtrl('1d', 3, 'ena');
			}
		/* �u�^�[�Q�b�g��Ɓv���I�� */
		} else {
			//			if (d3.className == 'sp_cond_sel') {
			//				DmapSPCondBtnCtrl('1d', 1, 'sel');
			//			}
			DmapSPCondBtnCtrl('1d', 3, 'dis');
		}
	}
}

/**
 * �|�C���g�\���ύX�����P���ׂ����B
 * @return {void}
 */
function DmapCloseSPCond1Dtl() {
	var div = document.getElementById('sp_dlg_cond1_dtl');
	div.style.display = 'none';
	/* �I����Ԃ����������� */
	for (var i = 1; i <= 4; i++) {
		DmapSPCondBtnCtrl('1d', i, 'ena');
	}
}

/**
 * �|�C���g�\���ύX�����{�^���̐���B
 * @param {String} cond ������ʁi1�F�����P�^1d�F�����P���ׁ^2�F�����Q�j
 * @param {Number} idx �{�^���ԍ�(1�`6)
 * @param {String} status �{�^���̏�ԁiena�F�����^sel�F�I���^dis�F�񊈐��j
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
 * �|�C���g�\���ύX�����P�̑I�𐔂�ԋp���܂��B
 * @return {Number} �I������Ă��錏��
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
 * �|�C���g�\���ύX�����Q�̑I�𐔂�ԋp���܂��B
 * @return {Number} �I������Ă��錏��
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
 * �|�C���g�\���ύX�����P��S�đI���������܂��B
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
 * �|�C���g�\���ύX�����Q��S�đI���������܂��B
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
 * �|�C���g�\���ύX�����P�{�^���N���b�N���̏����B
 * @param {Number} idx �{�^���ԍ�(1�`6)
 * @return {void}
 */
function DmapOnClickSpCond1(idx) {
	var btn = document.getElementById('sp_cond1_'+idx);
	if (!btn) return;
	if (btn.className == 'sp_cond_dis') return;
	/* �I���ς݂̏ꍇ */
	if (btn.className == 'sp_cond_sel') {
		/* �I������ */
		DmapSPCondBtnCtrl('1', idx, 'ena');
		/* �I�𐔂��O�ɂȂ����疾�ׂ���� */
		if (DmapSPCond1SelectedCount() == 0) {
			DmapCloseSPCond1Dtl();
		}
	/* ���I���̏ꍇ */
	} else {
		/* �u���Z�O�v�u���Z��v */
		if (DmapSPCond1KessanConf(idx)) {
		/* �Q�܂őI���� */
		} else if (DmapSPCond1SelectedCount() < 2) {
			/* �I�� */
			DmapSPCondBtnCtrl('1', idx, 'sel');
			/* ���ו\�� */
			DmapOpenSPCond1Dtl();
			/* �����Q���N���A */
			DmapNonSelectSPCond2();
		} else {
			alert(MSG_ALERT_SPCOND_LIMIT);
		}
	}
	/* ���ׂ̏�Ԃ����t���b�V�� */
	DmapSPCond1DtlRefresh();
}

/**
 * �|�C���g�\���ύX�����P�{�^���u���Z�O�v�u���Z��v�����I��s�̏����B
 * @param {Number} idx �{�^���ԍ�(1�`6)
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
 * �|�C���g�\���ύX�����P���׃{�^���N���b�N���̏����B
 * @param {Number} idx �{�^���ԍ�(1�`4)
 * @return {void}
 */
function DmapOnClickSpCond1Dtl(idx) {
	var btn = document.getElementById('sp_cond1d_'+idx);
	if (!btn) return;
	if (btn.className == 'sp_cond_dis') return;
	/* �I���ς݂̏ꍇ */
	if (btn.className == 'sp_cond_sel') {
	/* ���I���̏ꍇ */
	} else {
		/* �I�� */
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
 * �|�C���g�\���ύX�����Q�{�^���N���b�N���̏����B
 * @param {Number} idx �{�^���ԍ�(1�`7)
 * @return {void}
 */
function DmapOnClickSpCond2(idx) {
	var btn = document.getElementById('sp_cond2_'+idx);
	if (!btn) return;
	if (btn.className == 'sp_cond_dis') return;
	/* �I���ς݂̏ꍇ */
	if (btn.className == 'sp_cond_sel') {
	/* ���I���̏ꍇ */
	} else {
		/* �I�� */
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
		/* �����P���N���A */
		DmapNonSelectSPCond1();
	}
}

/**
 * �|�C���g�\���ύX�u�\���v�N���b�N���̏����B
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
	/* �����P�̑I����Ԃ��擾 */
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
	/* �����P���ׂ̑I����Ԃ��擾 */
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
	/* �����Q�̑I����Ԃ��擾 */
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
	/* ����I������Ă��Ȃ�������G���[ */
	if (!sel_1 && !sel_2) {
		alert(MSG_ERR_SELECT_POINT_NOSEL);
		return;
	}
	if (sel_1 && !sel_d1) {
		alert(MSG_ERR_SELECT_POINT_NODTL);
		return;
	}
	/* �k�ڃ`�F�b�N */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_SELECT_POINT.min && z <= NGZOOM_SELECT_POINT.max) {
		alert(MSG_ERR_SELECT_POINT_NGZOOM);
		return;
	}
	/* ���̓`�F�b�N */
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
	/* �n�}�\���͈͂��擾 */
	var box = DmapMap.getLatLonBox();
	var ltlat = DmapDegFormat(box.getMax().lat);
	var ltlon = DmapDegFormat(box.getMin().lon);
	var rblat = DmapDegFormat(box.getMin().lat);
	var rblon = DmapDegFormat(box.getMax().lon);
	/* hidden�ɏ������� */
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
	/* ���p�󋵃��O */
	DmapLogCount(8);
	/* �t���O���Z�b�g */
	resetAllFlg();
	/* �B���{�^���C�x���g���� */
	var b = document.getElementById('BTNPCHG_dummy');
	if (b) {
		b.click();
	}
}

/**
 * �|�C���g�\���ύX�i�G�[�W�F���g�j�u���_��v�u�ŗ��m�v�u�f����v�N���b�N���̏����B
 * @param {Number} idx �{�^���ԍ��i1�F���_��A2�F�ŗ��m�A3�F�f����j
 * @return {void}
 */
function DmapOnClickSpAgent(idx) {
	var val;
	/* �k�ڃ`�F�b�N */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_SELECT_POINT.min && z <= NGZOOM_SELECT_POINT.max) {
		alert(MSG_ERR_SELECT_POINT_NGZOOM);
		return;
	}
	/* ���̓`�F�b�N */
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
	/* �n�}�\���͈͂��擾 */
	var box = DmapMap.getLatLonBox();
	var ltlat = DmapDegFormat(box.getMax().lat);
	var ltlon = DmapDegFormat(box.getMin().lon);
	var rblat = DmapDegFormat(box.getMin().lat);
	var rblon = DmapDegFormat(box.getMax().lon);
	/* hidden�ɏ������� */
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
	/* ���p�󋵃��O */
	DmapLogCount(8);
	/* �t���O���Z�b�g */
	resetAllFlg();
	/* �B���{�^���C�x���g���� */
	var b = document.getElementById('BTNPCHG_dummy');
	if (b) {
		b.click();
	}
}

/**
 * �u�K���v�{�^���������̏����B
 * @return {void}
 */
function DmapOnClickVisitPlan() {
	/* �E���R�[�h���͕K�{ */
	if (DmapGetValueById('IE50012_disp') == '') {
		alert(MSG_ERR_STAFFCD_EMPTY);
		return;
	}
	/* �_�C�A���O�\�� */
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
 * �u�K���v�_�C�A���O����܂��B
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
 * �u�K���v�_�C�A���O�uOK�v�������̏����B
 * @return {void}
 */
function DmapSubmitVisitPlan() {
	/* hidden�ɒl���Z�b�g */
	var sitei = document.getElementById('SITEI');
	if (!sitei) return;
	sitei.value = DmapCheckVisitPlanYmd();
	if (!sitei.value) {
		alert('���������t����͂��Ă��������B');
		return;
	}
	/* ���p�󋵃��O */
	DmapLogCount(9);
	/* �t���O���Z�b�g */
	resetAllFlg();
	/* �B���{�^��Click�C�x���g */
	var btn = document.getElementById('BTNVISP_dummy');
	if (btn) {
		btn.click();
	}
	/* �K���_�C�A���O������ */
	DmapCloseVisitPlan();
}
/**
 * �u�K���v�_�C�A���O���t���͒l���`�F�b�N���Đ�������Βl��ԋp���܂��B
 * @return {String} ���͂��ꂽ���t������iyyyymmdd�j
 */
function DmapCheckVisitPlanYmd() {
	var dt = document.getElementById('vp_dlg_date');
	if (dt) {
		return DmapFormatYmd(dt.value);
	}
	return '';
}

/**
 * �J�����_�[��\�����܂��B
 * @param {Number} year �N
 * @param {Number} month ��
 * @return {void}
 */
function DmapShowCal(year, month){
	/* ���� */
	var today = new Date();
	/* �\������N�� */
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
	var f_text = f_year + '�N' + f_month + '��';
	/* �j�� */
	var week = new Array('��','��','��','��','��','��','�y');
	/* �J�����_�[�̍ŏ��̃R�}�i�ŏ��̓��j���j */
	var startday = fst - (fst.getDay() * 1000 * 60 * 60 * 24);
	startday = new Date(startday);
	/* �O���^���� */
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
	/* �N���i�w�b�_�j */
	html += '<tr><th colspan="7">';
	html += '<button class="cal_pg" onClick="DmapShowCal('+prev.getFullYear()+','+prev.getMonth()+');">&lt;</button>';
	html += '�@'+f_text+'�@';
	html += '<button class="cal_pg" onClick="DmapShowCal('+next.getFullYear()+','+next.getMonth()+');">&gt;</button>';
	html += '</th></tr>';

	/* �j�� */
	html += '<tr>';
	for (i = 0; i < 7; i++){
		html += '<td class="cal_yobi">' + week[i] + '</td>';
	}
	html += '</tr>';
	/* ���t */
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
				html += '<td class="cal_none">�@';
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
 * �J�����_�[�őI�����ꂽ���t���e�L�X�g���͂ɃZ�b�g���܂��B
 * @param {String} id �e�L�X�g���͂�id
 * @param {String} ymd ���t������
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
 * �u�\���ʒu�C���v�{�^���������̏����B
 * @return {void}
 */
function DmapOnClickBtnMove() {
	/* �\���ʒu�C�����[�h�� */
	if (DmapMovePinMode) {
		/* �\���ʒu�C�����[�h���I�� */
		DmapStopMovePinMode();
	/* �\���ʒu�C�����[�h�ł͂Ȃ� */
	} else {
		/* �\���ʒu�C�����[�h���J�n */
		DmapStartMovePinMode();
	}
}

/**
 * �\���ʒu�C�����[�h���J�n���܂��B
 * @return {void}
 */
function DmapStartMovePinMode() {
	DmapMovePinMode = true;
	/* �u�\���ʒu�C���v�{�^���摜�ؑ� */
	var btn = document.getElementById('f_btn_move');
	btn.className = 'f_btn_move_on';
	/* �\���ς݂̃����`���[������ */
	DmapRemoveLauncher();
	/* �\���ς݂̃s���ꗗ������ */
	DmapRemovePinSelect();
	/* �Г���񌟍����ׂ���� */
	DmapSrchPointDtlOff();
	/* �|�C���g�\���ύX�_�C�A���O����� */
	DmapCloseSelPoint();
	/* ���b�Z�[�W�\�� */
	DmapShowHeaderMsg('�I�\���ʒu���C������|�C���g���h���b�O���Ă��������B');
}

/**
 * �\���ʒu�C�����[�h���I�����܂��B
 * @return {void}
 */
function DmapStopMovePinMode() {
	DmapMovePinMode = false;
	var btn = document.getElementById('f_btn_move');
	btn.className = 'f_btn_move_off';
	/* ���b�Z�[�W��\�� */
	DmapHideHeaderMsg();
}

/**
 * MouseDown�C�x���g���X�i�[
 * @return {void}
 */
function DmapOnMouseDown() {
	/* �\���ʒu�C�����[�h�ȊO�̎��͉������Ȃ� */
	if (!DmapMovePinMode) return;
	/* �n�}���������͉������Ȃ� */
	if (!DmapMapEventEnable) return;
	/* �h���b�O�J�n */
	DmapPinDragging = true;
	/* �h���b�O���̃s�� */
	DmapMovePin = this;
	/* �}�E�X�_�E���ʒu�ƃs���ʒu�̍��� */
	var cLatLon = DmapMap.getPointerPosition();
	DmapMovePin.dragDifLat = cLatLon.lat - DmapMovePin.latlon.lat;
	DmapMovePin.dragDifLon = cLatLon.lon - DmapMovePin.latlon.lon;
}

/**
 * MouseMove�C�x���g���X�i�[
 * @return {void}
 */
function DmapOnMouseMove() {
	/* �\���ʒu�C�����[�h�ȊO�̎��͉������Ȃ� */
	if (!DmapMovePinMode) return;
	/* �n�}���������͉������Ȃ� */
	if (!DmapMapEventEnable) return;
	/* �h���b�O���łȂ���Ή������Ȃ� */
	if (!DmapPinDragging) return;
	/* �h���b�O���̃s�����s���̎��͉������Ȃ� */
	if (!DmapMovePin) return;
	/* �}�E�X�ʒu */
	var latlon = DmapMap.getPointerPosition();
	/* �s�����ړ� */
	var newlat = latlon.lat - DmapMovePin.dragDifLat;
	var newlon = latlon.lon - DmapMovePin.dragDifLon;
	DmapMovePin.moveLatLon(newlat, newlon);
}

/**
 * MouseUp�C�x���g���X�i�[
 * @return {void}
 */
function DmapOnMouseUp() {
	/* �h���b�O���łȂ��ꍇ�͉������Ȃ� */
	if (!DmapPinDragging) return;
	/* �n�}���������͉������Ȃ� */
	if (!DmapMapEventEnable) return;
	/* �h���b�O�I�� */
	DmapPinDragging = false;
	/* �h���b�O���̃s�����s���̎��͉������Ȃ� */
	if (!DmapMovePin) return;
	/* �O���[�v�̏ꍇ�͑I�����X�g��\�� */
	if (DmapMovePin.inGroup()) {
		DmapShowPinSelect(DmapMovePin.seq, 'DmapDragPinEnd', 'DmapDragPinSelectClose');
	/* �P�Ƃ̏ꍇ�͕\���ʒu�C�����s */
	} else {
		DmapDragPinEnd(DmapMovePin.seq);
	}
}

/**
 * Click�C�x���g���X�i�[
 * @return {void}
 */
function DmapOnClick() {
	/* �|�C���g�����`���[���� */
	DmapRemoveLauncher();
	/* �\���ς݂̃s���ꗗ������ */
	DmapRemovePinSelect();
}

/**
 * DblClick�C�x���g���X�i�[
 * @return {void}
 */
function DmapOnDblClick() {
	var zoom = DmapMap.getZoom();
	DmapMap.setZoom(zoom+1);
	var latlon = DmapMap.getClickLatLon();
	DmapMap.moveLatLon(latlon);
}

/**
 * RightClick�C�x���g���X�i�[
 * @return {void}
 */
function DmapOnRightClick() {
	/* �\���ʒu�C�����[�h�̎��͉������Ȃ� */
	if (DmapMovePinMode) return;
	/* �����q�o�^ */
	if (DmapRightClickMode == 1 && DmapMapEventEnable) {
		DmapShowMikomiKyaku();
	/* ���[�g���� */
	} else if (DmapRightClickMode == 2 && DmapRouteSearch) {
		DmapRouteSearch.entryPoint();
	}
}

/**
 * �s���̃h���b�O�������̏����B
 * @param {Number} seq �s���A�ԁi0�`99�j
 * @return {void}
 */
function DmapDragPinEnd(seq) {
	/* �s���I�����X�g������ */
	DmapRemovePinSelect();
	/* �Y���s���i�P�ƁF�h���b�O�����s���^�O���[�v�F���X�g����I�����ꂽ�s���j */
	var p = DmapPinList.Pins[seq];
	if (!p) return;
	/* �Y���s�����őO�ʂ� */
	p.moveTop();
	/* �Y���s���ƃh���b�O�����s�����قȂ�ꍇ */
	if (p.seq != DmapMovePin.seq) {
		/* �Y���s�����h���b�O�ʒu�ֈړ������� */
		p.moveLatLon(DmapMovePin.lat, DmapMovePin.lon);
		/* �h���b�O�����s�������̈ʒu�ɖ߂� */
		DmapMovePin.moveOrgLatLon();
	}
	/* �Y���s����ێ� */
	DmapMovePin = p;
	/* �������s */
	DmapSubmitChangePoint();
}

/**
 * �h���b�O���̃s���ꗗ��������̏����B
 * @return {void}
 */
function DmapDragPinSelectClose() {
	/* �s���I�����X�g������ */
	DmapRemovePinSelect();
	/* �\���ʒu�ύX���L�����Z�� */
	DmapCancelChangePoint();
}

/**
 * �\���ʒu�C���̎��s�����B
 * @return {void}
 */
function DmapSubmitChangePoint() {
	var e;
	/* �ړ��s�̏ꍇ�̓G���[ */
	if (!DmapMovePin.isMovable(DmapUser)) {
		alert(MSG_ERR_CHGP_NG);
		DmapCancelChangePoint();
		return;
	}
	/* �m�F�_�C�A���O */
	if (confirm(MSG_CONF_CHGP)) {
		/* ���p�󋵃��O */
		DmapLogCount(5);
		/* hidden�ɒl���Z�b�g */
		e = document.getElementById('CLAT');if (e) e.value = DmapDegFormat(DmapMap.getLatLon().lat);
		e = document.getElementById('CLON');if (e) e.value = DmapDegFormat(DmapMap.getLatLon().lon);
		e = document.getElementById('SCALE');if (e) e.value = DmapMap.getZoom();
		e = document.getElementById('SYOROW');if (e) e.value = DmapMovePin.seq;
		e = document.getElementById('SYULAT');if (e) e.value = DmapDegFormat(DmapMovePin.lat);
		e = document.getElementById('SYULON');if (e) e.value = DmapDegFormat(DmapMovePin.lon);
		/* �t���O���Z�b�g */
		resetAllFlg();
		/* �B���{�^��Click�C�x���g */
		var btn = document.getElementById('BTNPOSI_dummy');
		if (btn) {
			btn.click();
		}
	/* �L�����Z�� */
	} else {
		DmapCancelChangePoint();
	}
}

/**
 * �\���ʒu�C�����L�����Z�����܂��B
 * @return {void}
 */
function DmapCancelChangePoint() {
	/* ���̈ʒu�ɖ߂� */
	DmapMovePin.moveOrgLatLon();
	/* �\���ʒu�C�����[�h�I�� */
	DmapStopMovePinMode();
}

/**
 * �z�C�[���C�x���g�𖳌������܂��B
 * @param {Object} �C�x���g
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
 * �u�Г���񌟍��v�{�^���N���b�N���̏����B
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
 * �u�Г���񌟍��v���ׂ�\�����܂��B
 * @return {void}
 */
function DmapSrchPointDtlOn() {
	/* �t���[���[�h�����_�C�A���O������ */
	DmapSrchFWEnd();
	/* �u�Г���񌟍��v���ׂ�\�� */
	var div = document.getElementById('srch_p_dtl');
	div.style.display = 'block';
	var btn = document.getElementById('srch_p_btn');
	if (btn) btn.className = 'srch_p_btn_on';
	DmapSrchPointOn = true;
}

/**
 * �u�Г���񌟍��v���ׂ��������܂��B
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
 * �u�Г���񌟍��v���׃N���b�N���̏����B
 * @param {Number} idx ���הԍ�
 * @return {void}
 */
function DmapOnClickSrchPointDtl(idx) {
	var e;
	var val;
	/* �n�}�k�� */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_SRCH_POINT.min && z <= NGZOOM_SRCH_POINT.max) {
		alert(MSG_ERR_SRCH_POINT_NGZOOM);
		return;
	}
	/* �������[�h */
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
	/* ���p�󋵃��O */
	DmapLogCount(7);
	/* �n�}�͈̔͂��擾 */
	var box = DmapMap.getLatLonBox();
	hid = document.getElementById('CLAT');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lat);
	hid = document.getElementById('CLON');
	if (hid) hid.value = DmapDegFormat(DmapMap.getLatLon().lon);
	hid = document.getElementById('SCALE');
	if (hid) hid.value = DmapMap.getZoom();
	/* ����ܓx */
	e = document.getElementById('LTLAT');
	e.value = DmapDegFormat(box.getMax().lat);
	/* ����o�x */
	e = document.getElementById('LTLON');
	e.value = DmapDegFormat(box.getMin().lon);
	/* �E���ܓx */
	e = document.getElementById('RBLAT');
	e.value = DmapDegFormat(box.getMin().lat);
	/* �E���o�x */
	e = document.getElementById('RBLON');
	e.value = DmapDegFormat(box.getMax().lon);
	/* ���בI�� */
	e = document.getElementById('BNAME');
	e.value = idx;
	/* �t���O���Z�b�g */
	resetAllFlg();
	/* �B���{�^��Click�C�x���g */
	var btn = document.getElementById('BTNCOINF_dummy');
	if (btn) {
		btn.click();
	}
}

/**
 * �u�t���[���[�h�����v�{�^���N���b�N���̏����B
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
 * �u�t���[���[�h�����v���J�n���܂��B
 * @return {void}
 */
function DmapSrchFWStart() {
	/* �u�t���[���[�h�����v�_�C�A���O������ */
	DmapSrchFWEnd();
	/* �u�Г����������v���ׂ����� */
	DmapSrchPointDtlOff();
	/* �ܓx�o�x�������s */
	if (DmapSrchFWLatLon()) {
		return;
	}
	/* �w�b�_�[�ȊO�𖳌������� */
	if (DmapDisableMode != 'AllForRouteDlg' && DmapDisableMode != 'AllForRouteResult') {
		DmapDisableRight();
		DmapDisableBottom();
		DmapDisableMapEvent();
	}
	/* �t���[���[�h�����_�C�A���O�\�� */
	var btn = document.getElementById('srch_fw_btn');
	if (btn) btn.className = 'srch_fw_btn_on';
	DmapSrchFWOn = true;
	var dlg = document.getElementById('srch_fw_dlg');
	if (dlg) dlg.style.display = 'block';
}

/**
 * �u�t���[���[�h�����v�_�C�A���O���������܂��B
 * @return {void}
 */
function DmapSrchFWEnd() {
	/* �ꗗ�N���A */
	var div = document.getElementById('srch_fw_list_div');
	if (div) div.innerHTML = '';
	DmapSrchFWPoiResult = null;
	/* �_�C�A���O���� */
	var dlg = document.getElementById('srch_fw_dlg');
	if (dlg) dlg.style.display = 'none';
	/* �u�t���[���[�h�����v�{�^�� */
	var btn = document.getElementById('srch_fw_btn');
	if (btn) btn.className = 'srch_fw_btn_off';
	DmapSrchFWOn = false;
	/* �w�b�_�[�ȊO�����ɖ߂� */
	if (DmapDisableMode != 'AllForRouteDlg' && DmapDisableMode != 'AllForRouteResult') {
		DmapEnableRight();
		DmapEnableBottom();
		DmapEnableMapEvent();
	}
}

/**
 * �t���[���[�h�����̍ŏI���ʑI�����̏����B
 * @param {Number} lat �ܓx
 * @param {Number} lon �o�x
 * @return {void}
 */
function DmapSelectFWResult(lat, lon) {
	/* �t���[���[�h�����_�C�A���O���� */
	DmapSrchFWEnd();
	/* �}�[�J�[�\�����Ēn�}�ړ� */
	var loc = new ZDC.LatLon(lat, lon);
	DmapPlotSearchMarker(loc);
	DmapMap.moveLatLon(loc);
}

/**
 * �t���[���[�h�����؂�ւ��{�^���N���b�N���̏����B
 * @param {Number} idx ������ށi1�F�Z���A2�F�s���{���A3�F���Ӂj
 * @return {void}
 */
function DmapOnClickFW(idx) {
	/* �n�}�k�� */
	if (idx == 3) {
		var z = DmapMap.getZoom();
		if (z >= NGZOOM_SRCH_NPOI.min && z <= NGZOOM_SRCH_NPOI.max) {
			alert(MSG_ERR_SRCH_NPOI_NGZOOM);
			return;
		}
	}
	/* �ꗗ�N���A */
	var div = document.getElementById('srch_fw_list_div');
	if (div) div.innerHTML = '';
	DmapSrchFWPoiResult = null;
	/* �������[�h�擾 */
	var word = DmapGetValueById('MEISYO').trim();
	/* ���͕K�{ */
	if (word == '') {
		alert(MSG_ERR_WORD_EMPTY);
		return;
	}
	/* �؂�ւ��{�^������ */
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
	/* ���p�󋵃��O */
	DmapLogCount(6);
	switch (idx) {
		/* �Z���t���[���[�h���� */
		case 1:
			div.innerHTML = MSG_INF_SEARCH_PROCESSING;
			ZDC.Search.getAddrByWord({
				word: word,
				limit: '0,'+SRCH_ADDR_ROWS
			}, DmapAddrByWordCallback);
			break;
		/* POI�t���[���[�h���� */
		case 2:
			div.innerHTML = MSG_INF_SEARCH_PROCESSING;
			ZDC.Search.getPoiByWord({
				word: word,
				limit: '0,'+SRCH_POI_LIMIT
			}, DmapPoiByWordCallback);
			break;
		/* ����POI���� */
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
 * �Z���t���[���[�h�����̃R�[���o�b�N�֐��B
 * @param {Object} status �X�e�[�^�X�I�u�W�F�N�g
 * @param {Object} result ���ʃI�u�W�F�N�g
 * @return {void}
 */
function DmapAddrByWordCallback(status, result) {
	var html = '';
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	/* ���s���G���[ */
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
	/* 0�� */
	if (result.info.hit == 0) {
		html += '<span class="fw_msg">'+MSG_ALERT_NODATA+'</span>';
	/* �f�[�^���� */
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
 * POI�t���[���[�h�����̃R�[���o�b�N�֐��B
 * @param {Object} status �X�e�[�^�X�I�u�W�F�N�g
 * @param {Object} result ���ʃI�u�W�F�N�g
 * @return {void}
 */
function DmapPoiByWordCallback(status, result) {
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	/* ���s���G���[ */
	if (status.code != '000') {
		div.innerHTML = '';
		alert(MSG_ERR_FW_SEARCH_FAIL);
		return;
	}
	/* 0�� */
	if (result.info.hit == 0) {
		DmapPoiByWordListNoData();
	/* �f�[�^���� */
	} else {
		/* ���ʃI�u�W�F�N�g��ێ� */
		DmapSrchFWPoiResult = result;
		if (result.info.hit > SRCH_POI_EXT) {
			/* �s���{���ꗗ */
			DmapPoiByWordListTod();
		} else {
			/* POI�ꗗ */
			DmapPoiByWordListPoi();
		}
	}
}

/**
 * ����POI�����̃R�[���o�b�N�֐��B
 * @param {Object} status �X�e�[�^�X�I�u�W�F�N�g
 * @param {Object} result ���ʃI�u�W�F�N�g
 * @return {void}
 */
function DmapPoiByLatLonCallback(status, result) {
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	/* ���s���G���[ */
	if (status.code != '000') {
		div.innerHTML = '';
		alert(MSG_ERR_FW_SEARCH_FAIL);
		return;
	}
	/* 0�� */
	if (result.info.hit == 0) {
		DmapPoiByLatLonListNoData();
	/* �f�[�^���� */
	} else {
		/* ���ʃI�u�W�F�N�g��ێ� */
		DmapSrchFWPoiResult = result;
		if (result.info.hit > SRCH_NEARPOI_EXT) {
			/* �s���{���ꗗ */
			DmapPoiByLatLonListGenre();
		} else {
			/* POI�ꗗ */
			DmapPoiByLatLonListPoi();
		}
	}
}

/**
 * POI�t���[���[�h�����̓s���{���N���b�N�������B
 * @param {String} tod �s���{���R�[�h
 * @param {Number} cnt �s���{���ɊY�����錏��
 * @return {void}
 */
function DmapOnClickPoiTod(tod, cnt) {
	if (!DmapSrchFWPoiResult) return;
	if (cnt > SRCH_POI_EXT) {
		/* ��W�������ꗗ */
		DmapPoiByWordListGenre(tod);
	} else {
		/* POI�ꗗ */
		DmapPoiByWordListPoi(tod);
	}
}

/**
 * POI�t���[���[�h�����̑�W�������N���b�N�������B
 * @param {String} tod �s���{���R�[�h
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @param {Number} cnt �s���{���{��W�������ɊY�����錏��
 * @return {void}
 */
function DmapOnClickPoiGenre(tod, genre, genrenm, cnt) {
	if (!DmapSrchFWPoiResult) return;
	if (cnt > SRCH_POI_EXT) {
		/* ���W�������ꗗ */
		DmapPoiByWordListSubGenre(tod, genre, genrenm);
	} else {
		/* POI�ꗗ */
		DmapPoiByWordListPoi(tod, genre, genrenm);
	}
}

/**
 * POI�t���[���[�h�����̏��W�������N���b�N�������B
 * @param {String} tod �s���{���R�[�h
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @param {String} sub ���W�������R�[�h
 * @param {String} subnm ���W����������
 * @return {void}
 */
function DmapOnClickPoiSubGenre(tod, genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* POI�ꗗ */
	DmapPoiByWordListPoi(tod, genre, genrenm, sub, subnm);
}

/**
 * ����POI�����̑�W�������N���b�N�������B
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @param {Number} cnt ��W�������ɊY�����錏��
 * @return {void}
 */
function DmapOnClickNearPoiGenre(genre, genrenm, cnt) {
	if (!DmapSrchFWPoiResult) return;
	if (cnt > SRCH_NEARPOI_EXT) {
		/* ���W�������ꗗ */
		DmapPoiByLatLonListSubGenre(genre, genrenm);
	} else {
		/* POI�ꗗ */
		DmapPoiByLatLonListPoi(genre, genrenm);
	}
}

/**
 * ����POI�����̏��W�������N���b�N�������B
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @param {String} sub ���W�������R�[�h
 * @param {String} subnm ���W����������
 * @return {void}
 */
function DmapOnClickNearPoiSubGenre(genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* POI�ꗗ */
	DmapPoiByLatLonListPoi(genre, genrenm, sub, subnm);
}

/**
 * POI�t���[���[�h�����̂O�����b�Z�[�W�\���B
 * @return {void}
 */
function DmapPoiByWordListNoData() {
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	var html = '';
	html += '<span class="fw_msg">'+MSG_ALERT_NODATA+'</span>';
	html = '<table id="srch_fw_list">'+html+'</table>';
	div.innerHTML = html;
}

/**
 * POI�t���[���[�h�����̓s���{���ꗗ�\���B
 * @return {void}
 */
function DmapPoiByWordListTod() {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
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
 * POI�t���[���[�h�����̑�W�������ꗗ�\���B
 * @param {String} tod �s���{���R�[�h
 * @return {void}
 */
function DmapPoiByWordListGenre(tod) {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	/* �s���{���R�[�h�ő�W���������i���� */
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
	/* ��W�������ꗗ�\�� */
	var html = '';
	html += '<div id="srch_fw_title">�X�|�b�g�i'+TOD_NAME[tod]+'�j</div>';
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
 * POI�t���[���[�h�����̏��W�������ꗗ�\���B
 * @param {String} tod �s���{���R�[�h
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @return {void}
 */
function DmapPoiByWordListSubGenre(tod, genre, genrenm) {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	/* �s���{���R�[�h�{��W�������ŏ��W���������i���� */
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
	/* ���W�������ꗗ�\�� */
	var html = '';
	html += '<div id="srch_fw_title">�X�|�b�g�i'+TOD_NAME[tod]+' - '+genrenm+'�j</div>';
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
 * POI�t���[���[�h������POI�ꗗ�\���B
 * @param {String} tod �s���{���R�[�h
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @param {String} sub ���W�������R�[�h
 * @param {String} subnm ���W����������
 * @return {void}
 */
function DmapPoiByWordListPoi(tod, genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	var arrpoi = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		/* �s���{���w�� */
		if (tod) {
			if (itm.addressText.indexOf(TOD_NAME[tod]) >= 0) {
				/* ��W�������w�� */
				if (genre) {
					/* ���W�������w�� */
					if (sub) {
						if (itm.genre.code == genre+sub) {
							arrpoi.push(itm);
						}
					/* ���W�������w��Ȃ� */
					} else {
						if (itm.genre.code.substr(0,5) == genre) {
							arrpoi.push(itm);
						}
					}
				/* ��W�������w��Ȃ� */
				} else {
					arrpoi.push(itm);
				}
			}
		/* �s���{���w��Ȃ� */
		} else {
			arrpoi.push(itm);
		}
	}
	DmapSrchFWPoiResult = null;
	var html = '';
	if (tod) {
		html += '<div id="srch_fw_title">�X�|�b�g�i'+TOD_NAME[tod];
		if (genrenm) html += ' - ' + genrenm;
		if (subnm) html += ' - ' + subnm;
		html += '�j</div>';
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
 * ����POI�����̂O�����b�Z�[�W�\���B
 * @return {void}
 */
function DmapPoiByLatLonListNoData() {
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	var html = '';
	html += '<span class="fw_msg">'+MSG_ALERT_NODATA+'</span>';
	html = '<table id="srch_fw_list">'+html+'</table>';
	div.innerHTML = html;
}

/**
 * ����POI�����̑�W�������ꗗ�\���B
 * @return {void}
 */
function DmapPoiByLatLonListGenre() {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
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
 * ����POI�����̏��W�������ꗗ�\���B
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @return {void}
 */
function DmapPoiByLatLonListSubGenre(genre, genrenm) {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	/* �s���{���R�[�h�{��W�������ŏ��W���������i���� */
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
	/* ���W�������ꗗ�\�� */
	var html = '';
	html += '<div id="srch_fw_title">�X�|�b�g�i'+genrenm+'�j</div>';
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
 * ����POI������POI�ꗗ�\���B
 * @param {String} genre ��W�������R�[�h
 * @param {String} genrenm ��W����������
 * @param {String} sub ���W�������R�[�h
 * @param {String} subnm ���W����������
 * @return {void}
 */
function DmapPoiByLatLonListPoi(genre, genrenm, sub, subnm) {
	if (!DmapSrchFWPoiResult) return;
	/* �ꗗ */
	var div = document.getElementById('srch_fw_list_div');
	var arrpoi = new Array();
	var item = DmapSrchFWPoiResult.item;
	var len = item.length;
	for (var i = 0; i < len; i++) {
		var itm = item[i];
		/* ��W�������w�� */
		if (genre) {
			/* ���W�������w�� */
			if (sub) {
				if (itm.poi.genre.code == genre+sub) {
					arrpoi.push(itm);
				}
			/* ���W�������w��Ȃ� */
			} else {
				if (itm.poi.genre.code.substr(0,5) == genre) {
					arrpoi.push(itm);
				}
			}
		/* ��W�������w��Ȃ� */
		} else {
			arrpoi.push(itm);
		}
	}
	DmapSrchFWPoiResult = null;
	var html = '';
	if (genrenm) {
		html += '<div id="srch_fw_title">�X�|�b�g�i' + genrenm;
		if (subnm) html += ' - ' + subnm;
		html += '�j</div>';
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
 * �u�t���[���[�h�����v�ܓx�o�x���������s���܂��B
 * @return {Boolean} true�F�ܓx�o�x�������s�^false�F�ܓx�o�x�ɍ��v���Ȃ��̂Ŏ������֑J�ڂ���B
 */
function DmapSrchFWLatLon() {
	/* �������[�h�擾 */
	var word = DmapGetValueById('MEISYO').trim();
	/* ���͕K�{ */
	if (word == '') {
		alert(MSG_ERR_WORD_EMPTY);
		return true;
	}
	/* �ܓx�o�x�t�H�[�}�b�g�ɍ��v���邩 */
	var latlon = new Array();
	var dms;
	var ll = word.split(',');
	if (ll[0]) ll[0] = ll[0].trim();
	if (ll[1]) ll[1] = ll[1].trim();
	if (ll[0] && ll[1]) {
		for (var i = 0; i <= 1; i++) {
			/* �x���b */
			if (ll[i].match(LL_REG_DMS)) {
				dms = ll[i].split('.');
				latlon[i] = ZDC.dmsTodeg(parseInt(dms[0]), parseInt(dms[1]), parseInt(dms[2])+'.'+parseInt(dms[3]));
			/* �~���b */
			} else if (ll[i].match(LL_REG_MS)) {
				latlon[i] = ZDC.msTodeg(ll[i]);
			/* 10�i */
			} else if (ll[i].match(LL_REG_DEG)) {
				latlon[i] = ll[i];
			} else {
				break;
			}
		}
		if (latlon[0] && latlon[1]) {
			/* ���{�̓y�����ǂ����`�F�b�N */
			if (latlon[0] >= JPNAREA.minlat && latlon[0] <= JPNAREA.maxlat && latlon[1] >= JPNAREA.minlon && latlon[1] <= JPNAREA.maxlon) {
			} else {
				alert(MSG_ERR_LL_OUT);
				return true;
			}
			/* �ܓx�o�x�ʒu�ֈړ� */
			var loc = new ZDC.LatLon(latlon[0], latlon[1]);
			DmapMap.moveLatLon(loc);
			/* �}�[�J�[�\�� */
			DmapPlotSearchMarker(loc);
			return true;
		}
	}
	return false;
}

/**
 * �����ʒu�}�[�J�[��\�����܂��B
 * @param {Object} latlon �ܓx�o�x�I�u�W�F�N�g
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
 * �E�G���A����{�^���N���b�N���̏����B
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
 * �E�G���A�J���{�^���N���b�N���̏����B
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
 * ���ݒn�}�[�J�[��\�����܂��B
 * @param {Object} latlon �ܓx�o�x�I�u�W�F�N�g
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
 * �����x�Ѓs����\�����܂��B
 * @param {Object} latlon �ܓx�o�x�I�u�W�F�N�g
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
 * �����x�Ѓs���Ɏx�Ж���\�����܂��B
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
 * �u���ݒn��\���v�{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickLoc() {
	/* ���p�󋵃��O */
	DmapLogCount(3);
	/* ���ݒn�擾 */
	var res = DmapGetLocation(true);
	if (res.ret == 0) {
		DmapPlotLocationMarker(res.latlon);
		DmapMap.moveLatLon(res.latlon);
	}
}

/**
 * �u�x�Ђ�\���v�{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickSyozoku() {
	/* ���p�󋵃��O */
	DmapLogCount(4);
	var loc = DmapGetSyozokuLatLon();
	if (loc) {
		DmapMap.moveLatLon(loc);
	}
	/* �����x�Ж���\�� */
	DmapShowSyozokuPinNm();
}

/**
 * �|�C���g���\�������ǂ����̏�Ԃ��擾���܂��B
 * @return {Boolean} true�F�|�C���g���\����
 */
function DmapIsShowPointNameOn() {
	return (DmapGetValueById('BTNCOND').substr(0,1) == "1");
}

/**
 * �|�C���g���\�������ǂ����̏�Ԃ�؂�ւ��܂��B
 * @param {Boolean} on true�F�|�C���g���\����
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
 * �Ǝ햼�\�������ǂ����̏�Ԃ��擾���܂��B
 * @return {Boolean} true�F�Ǝ햼�\����
 */
function DmapIsShowGyosyuOn() {
	return (DmapGetValueById('BTNCOND').substr(1,1) == "1");
}

/**
 * �Ǝ햼�\�������ǂ����̏�Ԃ�؂�ւ��܂��B
 * @param {Boolean} on true�F�Ǝ햼�\����
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
 * �u�|�C���g���\���v�{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickShowPointName() {
	/* �\���� */
	if (DmapIsShowPointNameOn()) {
		/* �������� */
		DmapSetShowPointNameOnOff(false);
		DmapPinList.removePointName();
	/* �\�����łȂ� */
	} else {
		/* �\������ */
		DmapSetShowPointNameOnOff(true);
		DmapPinList.showPointName();
	}
}

/**
 * �u�Ǝ햼�\���v�{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickShowGyosyu() {
	/* �\���� */
	if (DmapIsShowGyosyuOn()) {
		/* �������� */
		DmapSetShowGyosyuOnOff(false);
		DmapPinList.removeGyosyu();
	/* �\�����łȂ� */
	} else {
		/* �\������ */
		DmapSetShowGyosyuOnOff(true);
		DmapPinList.showGyosyu();
	}
}

/**
 * �w�b�_�[�G���A�𖳌������܂��B
 * @return {void}
 */
function DmapDisableTop() {
	var div = document.getElementById('disable_top');
	if (div) {
		div.style.display = 'block';
	}
	/* �Г���񌟍����ׂ���� */
	DmapSrchPointDtlOff();
}
/**
 * �w�b�_�[�G���A��L�������܂��B
 * @return {void}
 */
function DmapEnableTop() {
	var div = document.getElementById('disable_top');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * �u�Г���񌟍��v�{�^���𖳌������܂��B
 * @return {void}
 */
function DmapDisableSrchP() {
	var div = document.getElementById('disable_srchp');
	if (div) {
		div.style.display = 'block';
	}
	/* �Г���񌟍����ׂ���� */
	DmapSrchPointDtlOff();
}
/**
 * �u�Г���񌟍��v�{�^����L�������܂��B
 * @return {void}
 */
function DmapEnableSrchP() {
	var div = document.getElementById('disable_srchp');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * �E�G���A�𖳌������܂��B
 * @return {void}
 */
function DmapDisableRight() {
	var div = document.getElementById('disable_right');
	if (div) {
		div.style.display = 'block';
	}
	/* �|�C���g�\���ύX�_�C�A���O����� */
	DmapCloseSelPoint();
}
/**
 * �E�G���A��L�������܂��B
 * @return {void}
 */
function DmapEnableRight() {
	var div = document.getElementById('disable_right');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * �t�b�^�[�G���A�𖳌������܂��B
 * @return {void}
 */
function DmapDisableBottom() {
	var div = document.getElementById('disable_bottom');
	if (div) {
		div.style.display = 'block';
	}
}
/**
 * �t�b�^�[�G���A��L�������܂��B
 * @return {void}
 */
function DmapEnableBottom() {
	var div = document.getElementById('disable_bottom');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * �n�}�G���A�𖳌������܂��B
 * @return {void}
 */
function DmapDisableMapArea() {
	var div = document.getElementById('disable_map');
	if (div) {
		div.style.display = 'block';
	}
}
/**
 * �n�}�G���A��L�������܂��B
 * @return {void}
 */
function DmapEnableMapArea() {
	var div = document.getElementById('disable_map');
	if (div) {
		div.style.display = 'none';
	}
}

/**
 * �n�}�̃C�x���g�𖳌������܂��B
 * @return {void}
 */
function DmapDisableMapEvent() {
	DmapMapEventEnable = false;
}
/**
 * �n�}�̃C�x���g��L�������܂��B
 * @return {void}
 */
function DmapEnableMapEvent() {
	DmapMapEventEnable = true;
}

/**
 * �S�ẴG���A�ƒn�}�𖳌������܂��B
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
 * �����ɂ����S�ẴG���A�ƒn�}�����ɖ߂��܂��B
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
 * �S�ẴG���A�ƒn�}�C�x���g�𖳌������܂��B
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
 * �����ɂ����S�ẴG���A�ƒn�}�C�x���g�����ɖ߂��܂��B
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
 * �Г���񌟍��A�E�G���A�A���G���A�A�n�}�C�x���g�𖳌������܂��B
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
 * �����ɂ����Г���񌟍��A�E�G���A�A���G���A�A�n�}�C�x���g�����ɖ߂��܂��B
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
 * �Г���񌟍��A���G���A�A�n�}�C�x���g�𖳌������܂��B
 * @return {void}
 */
function DmapDisableAllForRouteResult() {
	DmapDisableMode = 'AllForRouteResult';
	DmapDisableSrchP();
	DmapDisableBottom();
	DmapDisableMapEvent();
}
/**
 * �����ɂ����Г���񌟍��A���G���A�A�n�}�C�x���g�����ɖ߂��܂��B
 * @return {void}
 */
function DmapEnableAllForRouteResult() {
	DmapDisableMode = '';
	DmapEnableSrchP();
	DmapEnableBottom();
	DmapEnableMapEvent();
}

/**
 * �ړ�������\�����܂��B
 * @return {Boolean} true�F�ړ�������\���^false�F�ړ�������\�����Ȃ�
 */
function DmapShowIdoKyori() {
	/* �ړ������\���t���O�擾 */
	var iskyori = DmapGetValueById("ISKYORI");
	if (!iskyori) return false;
	/* �ړ������\���t���O��1��9�Ȃ�΁A�ړ������\�����s�� */
	if (iskyori == 1 || iskyori == 9) {
		if (DmapPinList.Pins.length > 0) {
			/* �����x�Ђ̈ܓx�o�x�擾 */
			var slatlon = DmapGetSyozokuLatLon();
			if (slatlon === null) return false;
			var latlons = new Array();
			/* �n�_�͏����x�Ђ̈ܓx�o�x */
			latlons.push(slatlon); 
			/* ���p�_�͖K���̈ܓx�o�x */
			for (var i=0, len=DmapPinList.Pins.length; i<len; i++) {
				latlons.push(DmapPinList.Pins[i].latlon);
			}
			/* �I�_�������x�Ђ̈ܓx�o�x */
			latlons.push(slatlon);
			/* �n�_����I�_�܂ł���łȂ��ŕ`�� */
			DmapIdoKyori = new ZDC.Polyline(latlons, {
				strokeColor: '#0000FF',
				strokeWeight: 5,
				lineOpacity: 0.5,
				lineStyle: 'solid'
			});
			DmapMap.addWidget(DmapIdoKyori);
		}
		/* �ړ��������擾 */
		var kyori = DmapGetValueById("KYORI");
		/* �_�C�A���O�\�� */
		var elm = document.getElementById("kyori_dlg_txt");
		elm.innerText = ISKYORI_MESSAGE[iskyori].replace('{kyori}', kyori);
		DmapOpenIdoKyori();
		return true;
	}
	return false;
}

/**
 * �ړ��������������܂��B
 * @return {void}
 */
function DmapRemoveIdoKyori() {
	if (DmapIdoKyori) {
		DmapMap.removeWidget(DmapIdoKyori);
		DmapIdoKyori = null;
	}
}

/**
 * �u�ړ������v�_�C�A���O���J���܂��B
 * @return {void}
 */
function DmapOpenIdoKyori() {
	var dlg = document.getElementById('kyori_dlg');
	if (dlg) {
		dlg.style.display = 'block';
		/* �w�ʂ�G��Ȃ����� */
		DmapDisableAllArea();
	}
}
/**
 * �u�ړ������v�_�C�A���O����܂��B
 * @return {void}
 */
function DmapCloseIdoKyori() {
	var dlg = document.getElementById('kyori_dlg');
	if (dlg) {
		dlg.style.display = 'none';
	}
	/* �w�ʂ����ɖ߂� */
	DmapEnableAllArea();
}

/**
 * �u�����q�o�^�v�t�L�_�V��\�����܂��B
 * @return {void}
 */
function DmapShowMikomiKyaku() {
	/* �t�L�_�V������ */
	DmapRemoveMikomiKyaku();
	/* �n�}�k�� */
	var z = DmapMap.getZoom();
	if (z >= NGZOOM_PSPECT_CUST.min && z <= NGZOOM_PSPECT_CUST.max) {
		alert(MSG_ERR_MIKOMI_NGZOOM);
		return;
	}
	/* �E�N���b�N�n�_�̍��W�擾 */
	var latlon = DmapMap.getPointerPosition();
	DmapRightClickMode = 0;
	/* �ܓx�o�x����Z�������� */
	ZDC.Search.getAddrByLatLon({
		latlons: [latlon],
		datum: 'TOKYO'
	}, function(status, res) {
		if (status.code == '000' && res[0] && res[0].address) {
			/* �������ʂ���Z�����擾 */
			var addr = res[0].address.text;
			/* �ܓx�o�x�A�Z����HIDDEN�^�O�ɖ��ߍ��� */
			var hilat = document.getElementById('HILAT');
			if (!hilat) return;
			var hilon = document.getElementById('HILON');
			if (!hilon) return;
			var hiadd = document.getElementById('HIADD');
			if (!hiadd) return;
			/* �ܓx�o�x�̏����_8���ȍ~�͐؂�̂� */
			hilat.value = Math.floor(latlon.lat * 10000000) / 10000000;
			hilon.value = Math.floor(latlon.lon * 10000000) / 10000000;
			hiadd.value = addr;
			/* �t�L�_�V��\�� */
			var html;
			html =  '<div id="rp_div">';
			html += '<div id="mik_dlg_txt">'+addr+'</div>';
			html += '<div id="mik_dlg_btn">';
			html += '<button type="button" class="dlg_btn_ok" onclick="DmapSubmitMikomiKyaku();">�����q�o�^</button>';
			html += '<button type="button" class="dlg_btn_ok" onclick="DmapRemoveMikomiKyaku();">�L�����Z��</button>';
			html += '</div>';
			html += '</div>';
			DmapMikomiKyaku = new ZDC.MsgInfo(latlon, {html: html, closeBtn: false});
			DmapMap.addWidget(DmapMikomiKyaku);
			DmapMikomiKyaku.open();
			/* �w�ʂ𖳌������� */
			DmapDisableAllEvent();
		} else {
			alert(MSG_ERR_MIKOMI_ADDR);
		}
		DmapRightClickMode = 1;
	});
}

/**
 * �u�����q�o�^�v�t�L�_�V���������܂��B
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
 * �����q�o�^�����s���܂��B
 * @return {void}
 */
function DmapSubmitMikomiKyaku() {
	var btn = document.getElementById('BTNCUST');
	if (btn) {
		/* ���p�󋵃��O */
		DmapLogCount(11);
		btn.click();
	}
	/* �u�����q�o�^�v�t�L�_�V������ */
	DmapRemoveMikomiKyaku();
}

/**
 * �u���[�g�����v�{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickRouteSearch() {
	/* �|�C���g�����`���[������ */
	DmapRemoveLauncher();
	/* �_�C�A���O�\�� */
	DmapShowRouteSearchDlg("rs_dlg");
}

/**
 * ���[�g�\���@�\���J�n���܂��B
 * @param {Number} seq �s���̘A��
 * @return {void}
 */
function DmapStartPinRoute(seq) {
	var latlon, place;
	/* ���ݒn���擾 */
	var res = DmapGetLocation();
	if (res.ret == 0) {
		latlon = res.latlon;
		place = "���ݒn";
		DmapPlotLocationMarker(latlon);
	} else {
		/* ���ݒn���擾�ł��Ȃ������珊���x�Ђ̈ܓx�o�x�擾 */
		latlon = DmapGetSyozokuLatLon();
		place = "�����x��";
	}
	/* �_�C�A���O�\�� */
	DmapShowRouteSearchDlg("rv_dlg");
	/* �o���n��ݒ� */
	DmapRouteSearch.setPoint('start', latlon, place);
	/* �ړI�n��ݒ� */
	latlon = DmapPinList.Pins[seq].latlon;
	place = DmapPinList.Pins[seq].name;
	DmapRouteSearch.setPoint('end', latlon, place);
}

/**
 * ���[�g�����_�C�A���O��\�����܂��B
 * @param {String} dlg_id �_�C�A���OID
 * @return {void}
 */
function DmapShowRouteSearchDlg(dlg_id) {
	/* �O���[�v�s���ꗗ������ */
	DmapRemovePinSelect();
	/* �u�����q�o�^�v�t�L�_�V������ */
	DmapRemoveMikomiKyaku();
	/* ���łɃ_�C�A���O���J���Ă���ꍇ�̓L�����Z������ */
	if (DmapRouteSearch) DmapRouteSearchCancel();
	/* DmapRouteSearch�I�u�W�F�N�g���� */
	DmapRouteSearch = new DmapClassRouteSearch(dlg_id);
	/* �_�C�A���O���J�� */
	DmapRouteSearch.openDialog();
	/* �w�ʂ𖳌��� */
	DmapDisableAllForRouteDlg();
	DmapRightClickMode = 0;
}

/**
 * ���[�g�����_�C�A���O����܂��B
 * @return {void}
 */
function DmapCloseRouteSearchDlg() {
	/* �_�C�A���O����� */
	DmapRouteSearch.closeDialog();
	DmapRightClickMode = 1;
}

/**
 * ���[�g�����_�C�A���O�̃��[�h�؂�ւ��{�^���N���b�N���̏����B
 * @param {String} mode ���[�g���[�h�iwalk�F���s�ҁ^car�F�ԁ^train�F�d�ԁj
 * @return {void}
 */
function DmapOnClickRouteMode(mode) {
	DmapRouteSearch.changeMode(mode);
}

/**
 * ���[�g�����_�C�A���O�́u�o���n�v�u�ړI�n�v�{�^���N���b�N���̏����B
 * @param {String} type �n�_�̃^�C�v�istart�F�o���n�^end�F�ړI�n�j
 * @return {void}
 */
function DmapOnClickRoutePoint(type) {
	DmapRouteSearch.searchPoint(type);
}

/**
 * ���[�g���������s���܂��B
 * @return {void}
 */
function DmapRouteSearchExecute() {
	/* ���[�g�������s */
	DmapRouteSearch.execSearch(function () {
		/* ���[�g�����_�C�A���O����� */
		DmapCloseRouteSearchDlg();
		/* �\���ς݂̃����`���[������ */
		DmapRemoveLauncher();
		/* �ړ������\�����폜 */
		DmapRemoveIdoKyori();
		/* �E�G���A�����[�g�������ʕ\���ɐ؂�ւ� */
		DmapChangeScreen('rs_result');
	});
}

/**
 * ���[�g�����_�C�A���O�̌������L�����Z���B
 * @return {void}
 */
function DmapRouteSearchCancel() {
	/* ���[�g�����̃E�B�W�F�b�g�����ׂč폜 */
	DmapRouteSearch.removeAllWidget();
	/* ���[�g�����_�C�A���O����� */
	DmapCloseRouteSearchDlg();
	/* ���[�g�����I�u�W�F�N�g���J�� */
	DmapRouteSearch = null;
	/* �w�ʂ̖����������ɖ߂� */
	DmapEnableAllForRouteDlg();
}

/**
 * ���[�g�������ʂ̌��\���{�^���N���b�N���̏����B
 * @return {void}
 */
function DmapOnClickRouteSelect() {
	DmapRouteSearch.toggleResultList();
}

/**
 * ���[�g�������ʂ̌�⃊�X�g�N���b�N���̏����B
 * @param {Number} idx ���ԍ�
 * @return {void}
 */
function DmapOnClickRouteListRow(idx) {
	DmapRouteSearch.changeResult(idx);
}

/**
 * ���[�g�������ʂ���܂��B
 * @return {void}
 */
function DmapRouteSearchResultClose() {
	/* ���[�g�����̃E�B�W�F�b�g�����ׂč폜 */
	DmapRouteSearch.removeAllWidget();
	/* �E�G���A���f�t�H���g�\���ɐ؂�ւ� */
	DmapChangeScreen();
	/* ���[�g�����I�u�W�F�N�g���J�� */
	DmapRouteSearch = null;
	DmapRightClickMode = 1;
}

/**
 * ��ʂ̕\�����e��؂�ւ��܂��B
 * @param {String} mode �\�����[�h�irs_result�F���[�g�������ʕ\���^�ȗ����̓f�t�H���g�\���j
 * @return {void}
 */
function DmapChangeScreen(mode) {
	var div_def = document.getElementById("default_view");
	var div_rs = document.getElementById("rs_result_view");
	if (mode == 'rs_result') {
		/* �E�G���A�̕\�������[�g�������ʂɐ؂�ւ� */
		if (div_def) div_def.style.display = 'none';
		if (div_rs) div_rs.style.display = 'block';
		DmapEnableAllEvent();
		DmapDisableAllForRouteResult();
	} else {
		/* �E�G���A�̕\�����f�t�H���g�ɐ؂�ւ� */
		if (div_def) div_def.style.display = 'block';
		if (div_rs) div_rs.style.display = 'none';
		DmapEnableAllForRouteResult();
	}
}

/**
 * �n�}�̒��S���w�肵���ܓx�o�x�Ɉړ�����
 * @param {Number} lat �ܓx
 * @param {Number} lon �o�x
 * @return {void}
 */
function DmapMoveLatlon(lat, lon) {
	DmapMap.moveLatLon(new ZDC.LatLon(lat, lon));
}

/* ���[�h���̏��������s */
if (window.attachEvent) {
	window.attachEvent('onload', DmapOnLoad);
} else {
	window.onload = function(){
		DmapOnLoad();
	}
}
