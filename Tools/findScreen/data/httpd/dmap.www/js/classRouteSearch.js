/**
 * DmapClassRouteSearch�I�u�W�F�N�g�𐶐����܂��B
 * @class ���[�g�����̑���𐧌䂵�܂��B
 * @param {String} dlg_id �_�C�A���OID
 * @constructor
 */
var DmapClassRouteSearch = function (dlg_id) {
	if (!dlg_id) return;
	if (!dlg_id.match(/_dlg$/)) return;
	/**
	 * �v�f���̃v���t�B�b�N�X��ێ����܂��B
	 * @type String
	 */
	this.pref_id = dlg_id.replace("dlg", "");
	/**
	 * �_�C�A���OID��ێ����܂��B
	 * @type String
	 */
	this.dlg_id = dlg_id;
	/**
	 * �_�C�A���O�v�f��ێ����܂��B
	 * @type Object
	 */
	this.dlg_elm = document.getElementById(dlg_id);
	this.drag = null;
	/**
	 * ���[�g���[�h��ێ����܂��B�iwalk�F���s�ҁ^car�F�ԁ^train�F�d�ԁj
	 * @type String
	 */
	this.mode = null;
	this.action = null;
	/**
	 * �o���n�ƖړI�n��DmapClassRoutePoint�I�u�W�F�N�g��ێ����܂��B
	 * @type Array
	 */
	this.point = {
		'start': new DmapClassRoutePoint('start'),
		'end':   new DmapClassRoutePoint('end')
	};
	/**
	 * �n�_�w�莞�Ɏg�p�����ϐ��ł��B
	 * @type Array
	 */
	this.point_type = null;
	/**
	 * ���[�g�ݒ��ێ����܂��B
	 * @type Array
	 */
	this.cond = new Array();
	/**
	 * ���[�g�`�掞�Ɏg�p�����ϐ��ł��B
	 * @type Array
	 */
	this.pls = new Array();
	/**
	 * �n�_�w��{�^���̏�ԊǗ��Ɏg�p�����ϐ��ł��B
	 * @type Object
	 */
	this.btn_elm_on = null;
	/**
	 * ���[�g�`�掞�Ɏg�p�����ϐ��ł��B
	 * @type Array
	 */
	this.zoom_latlon = new Array();
	/**
	 * ���[�g�`�掞�Ɏg�p�����ϐ��ł��B
	 * @type Object
	 */
	this.route = new Object();
	/**
	 * ���[�g�`��ݒ��ێ����܂��B
	 * @type Array
	 */
	this.line_opt = {
		'walk' : {strokeColor: '#00FFFF', strokeWeight: 7, lineOpacity: 0.75, lineStyle: 'solid'},
		'car'  : {strokeColor: '#0000FF', strokeWeight: 7, lineOpacity: 0.65, lineStyle: 'solid'},
		'train': {strokeColor: '#0000FF', strokeWeight: 7, lineOpacity: 0.65, lineStyle: 'solid'}
	};
}

/**
 * ���[�g�T���_�C�A���O�̗v�f���擾���܂��B
 * @param {String} id �v�fID
 * @return {Object} �v�f
 */
DmapClassRouteSearch.prototype.getElmByID = function(id) {
	return document.getElementById(this.pref_id+id);
}

/**
 * ���[�g�T���_�C�A���O���J���܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.openDialog = function() {
	var elm;
	/* �����\�����͕��s�҃��[�g */
	if (!this.mode) {
		this.changeMode("walk");
	}
	/* �t�H�[�����Z�b�g */
	/* �o���n */
	elm = this.getElmByID("start_addr");
	elm.tagName == "INPUT" ? elm.value = "�o���n�{�^���������Ă�������" : elm.innerText = "";
	/* �ړI�n */
	elm = this.getElmByID("end_addr");
	elm.tagName == "INPUT" ? elm.value = "�ړI�n�{�^���������Ă�������" : elm.innerText = "";
	this.getElmByID("searchtype1")[0].selected = true;	/* ���s�҃��[�g�F���[�g�ݒ� */
	this.getElmByID("searchtype2")[0].selected = true;	/* �ԃ��[�g�F���[�g�ݒ� */
	this.getElmByID("toll").checked = false;			/* �ԃ��[�g�F�L�����H */
	this.getElmByID("xdw")[0].selected = true;			/* �d�ԃ��[�g�F�j�� */
	this.getElmByID("xrp")[0].selected = true;			/* �d�ԃ��[�g�F�\���� */
	this.getElmByID("xep").checked  = false;			/* �d�ԃ��[�g�F���}���p */
	/* �_�C�A���O��\�� */
	this.dlg_elm.style.display = 'block';
	/* �_�C�A���O�̃h���b�O���\�ɂ��� */
	DmapDlgDragStart(this.dlg_elm);
}

/**
 * ���[�g�T���_�C�A���O����܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.closeDialog = function() {
	/* �_�C�A���O���B�� */
	this.dlg_elm.style.display = 'none';
	DmapDlgDragEnd();
	DmapRightClickMode = 1;
	/* ���b�Z�[�W�폜 */
	this.removeMessage();
	/* �{�^���̐F��OFF�ɂ��� */
	this.setButtonColorOff();
}

/**
 * ���[�g���[�h��؂�ւ��܂��B
 * @param {String} mode ���[�g���[�h�iwalk�F���s�ҁ^car�F�ԁ^train�F�d�ԁj
 * @return {void}
 */
DmapClassRouteSearch.prototype.changeMode = function(mode) {
	this.mode = mode;
	DmapRightClickMode = 0;
	/* ���b�Z�[�W�폜 */
	this.removeMessage();
	/* �{�^���̐F��OFF�ɂ��� */
	this.setButtonColorOff();
	/* �摜��ؑ� */
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
	/* ������ؑ� */
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
 * �n�_���Z�b�g���܂��B
 * @param {String} type �n�_�̃^�C�v�istart�F�o���n�^end�F�ړI�n�j
 * @param {Object} latlon �ܓx�o�x�I�u�W�F�N�g
 * @param {String} name �ꏊ��
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
 * �n�_�w�胂�[�h���J�n���܂��B
 * @param {String} type �n�_�̃^�C�v�istart�F�o���n�^end�F�ړI�n�j
 * @return {void}
 */
DmapClassRouteSearch.prototype.searchPoint = function(type) {
	this.point_type = type;
	var type_elm = this.getElmByID(type);
	var label = type_elm.innerText;
	/* �E�N���b�N�����[�g�������[�h�� */
	DmapRightClickMode = 2;
	/* ���b�Z�[�W�\�� */
	this.showMessage(label+'�_��n�}��Œ��������Ă��������B');
	/* �{�^���̐F��OFF�ɂ��� */
	this.setButtonColorOff();
	/* �����ꂽ�{�^���̐F��ON�ɂ��� */
	this.setButtonColorOn(type_elm);
}

/**
 * �n�_���w�肵�܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.entryPoint = function() {
	var point = this.point[this.point_type];
	/* �}�[�J�[���폜 */
	point.removeMarker();
	/* �E�N���b�N�����ʒu�̈ܓx�o�x�擾 */
	point.latlon = DmapMap.getPointerPosition();
	/* �}�[�J�[���v���b�g */
	point.plotMarker();
	/* ���̈ܓx�o�x�̏Z�����擾 */
	point.addr_elm = this.getElmByID(this.point_type+"_addr");
	point.getAddr();
	/* ���b�Z�[�W�폜 */
	this.removeMessage();
	/* �{�^���̐F��OFF�ɖ߂� */
	this.setButtonColorOff();
	/* �E�N���b�N������ */
	DmapRightClickMode = 0;
}

/**
 * ���[�g���������s���܂��B
 * @param {Function} callback �R�[���o�b�N�֐�
 * @return {void}
 */
DmapClassRouteSearch.prototype.execSearch = function (callback) {
	if (!callback) callback = function() {};
	var elm;
	/* �o���n�̈ܓx�o�x���擾 */
	var from = this.point['start'].latlon;
	if (!from) {
		alert('�o���n���w�肵�Ă��������B');
		return;
	}
	/* �ړI�n�̈ܓx�o�x���擾 */
	var to = this.point['end'].latlon;
	if (!to) {
		alert('�ړI�n���w�肵�Ă��������B');
		return;
	}
	/* ���p�󋵃��O */
	if (this.dlg_id == 'rv_dlg') {
		DmapLogCount(2);
	}
	if (this.dlg_id == 'rs_dlg') {
		DmapLogCount(10);
	}
	this.cond = new Array();
	var rsObj = this;
	if ( this.mode == "walk" ) {
		/* ���s���[�g���� */
		/* ���[�g�ݒ���擾 */
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
		/* �����ԃ��[�g���� */
		/* ���[�g�ݒ���擾 */
		elm = this.getElmByID("searchtype2");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var searchtype = elm.value;
		/* �L�����H���擾 */
		elm = this.getElmByID("toll");
		if (elm.checked) this.cond.push("�L�����H���p");
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
		/* �d�ԃ��[�g���� */
		/* �j�����擾 */
		elm = this.getElmByID("xdw");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var xdw = elm.value;
		/* �\�������擾 */
		elm = this.getElmByID("xrp");
		this.cond.push(elm[elm.selectedIndex].innerText);
		var xrp = elm.value;
		/* ���}���p���擾 */
		elm = this.getElmByID("xep");
		if (elm.checked) this.cond.push("���}���p");
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
 * ���b�Z�[�W��\�����܂��B
 * @param {String} msg ���b�Z�[�W
 * @return {void}
 */
DmapClassRouteSearch.prototype.showMessage = function(msg) {
	var msg_elm = this.getElmByID("message");
	msg_elm.innerText = msg;
}

/**
 * ���b�Z�[�W���������܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.removeMessage = function() {
	this.showMessage("");
}

/**
 * �{�^���̐F��ON�ɂ��܂��B
 * @param {Object} btn_ele �{�^���v�f
 * @return {void}
 */
DmapClassRouteSearch.prototype.setButtonColorOn = function(btn_elm) {
	/* ON�ɂ����{�^���v�f���L�� */
	this.btn_elm_on = btn_elm;
	addClass(this.btn_elm_on, "on");
}

/**
 * �{�^���̐F��OFF�ɂ��܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.setButtonColorOff = function() {
	/* ON�̂܂܂̃{�^���v�f������΁A�f�t�H���g�F�ɖ߂� */
	if (this.btn_elm_on) {
		removeClass(this.btn_elm_on, "on");
	}
}

/**
 * ���[�g��\�����܂��B
 * @param {String} mode ���[�g���[�h�iwalk�F���s�ҁ^car�F�ԁ^train�F�d�ԁj
 * @param {Object} link �ܓx�o�x�I�u�W�F�N�g
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
 * ���[�g���������܂��B
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
 * ���[�g�S�̂�\���ł���悤�Y�[���������܂��B
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
 * ���[�g�v���t�B�[����\�����܂��B
 * @param {Number} dist �����im�j
 * @param {Number} time ���v���ԁi���j
 * @return {void}
 */
DmapClassRouteSearch.prototype.showProfile = function (dist, time) {
	var profile = new Array();
	
	/* �o���n */
	profile.push('�o���n�@' + this.point.start.addr);
	/* �ړI�n */
	profile.push('�ړI�n�@' + this.point.end.addr);
	profile.push('');
	/* �������� */
	profile.push(this.cond.join('<br />'));
	profile.push('');
	/* ���� */
	if (dist) {
		/* m����Km�ɕϊ��i10m�ȉ��؂�グ�j */
		dist = Math.ceil(dist / 10) / 100 + 'Km';
		profile.push(dist);
	}
	/* ���� */
	if (time) {
		time = '��' + time + '��';
		profile.push(time);
	}
	
	document.getElementById("rs_prf_body").innerHTML = profile.join('<br />');
}

/**
 * ���[�g�ڍׂ�\�����܂��B
 * @param {Object} route ���[�g�I�u�W�F�N�g
 * @return {void}
 */
DmapClassRouteSearch.prototype.showRouteDetail = function (route) {
	var dtl_elm = document.getElementById("rs_detail");
	var head_elm = document.getElementById("rs_dtl_hd");
	var body_elm = document.getElementById("rs_dtl_body");
	var head_html = body_html = '';
	
	/* ���[�g�ڍׂ��B�� */
	dtl_elm.style.display = 'none';
	/* �ԃ��[�g */
	if ( this.mode == 'car' ) {
		/* �ڍחp��HTML���擾����֐� */
		function getListHtmlCar(lat, lon, type, place) {
			return '<tr class="click" onClick="DmapMoveLatlon('+lat+', '+lon+');"><td class="img"><div class="'+type+'">�@</div></td><td class="text">'+place+'</td></tr>';
		}
		/* �w�b�_�[ */
		head_html = '���[�g�ڍ�';
		/* ���e */
		var link = route.link;
		body_html += getListHtmlCar(this.point.start.latlon.lat, this.point.start.latlon.lon, 'start', this.point.start.addr);
		for (var i=0, len=link.length, idx=0; i<len; i++) {
			guidance = link[i].guidance;
			if (guidance) {
				if (guidance.straightFlag === false) {
					body_html += getListHtmlCar(link[i].line[0].lat, link[i].line[0].lon, 'arrow', (guidance.crossName ? guidance.crossName : '�����_'));
				}
			}
		}
		body_html += getListHtmlCar(this.point.end.latlon.lat, this.point.end.latlon.lon, 'end', this.point.end.addr);
		body_html = '<table class="rs_dtl_list"><tbody>' + body_html + '</tbody></table>';
	/* �d�ԃ��[�g */
	} else if ( this.mode == 'train' ) {
		function getListHtmlTrain(transfer, rosen, from, to, hour, min, fare) {
			var text = '';
			text += from + '�`' + to + (rosen ? '�i' + rosen + '�j' : '') + '<br />';
			text += (hour ? hour + '����' : '') + min + '��' + (fare ? '�@' + fare + '�~' : '');
			return '<tr><td class="img"><div class="'+transfer+'">�@</div></td><td class="text">'+text+'</td></tr>';
		}
		/* �w�b�_�[ */
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
			temp_html += '<span>���' + (i+1) + '�i' + (hour ? hour + '����' : '') + min + '��' + '�j</span>'
			var rank_html = '';
			rank_html += (fast==1)  ? '<span class="fast">�@</span>'  : '';
			rank_html += (cheap==1) ? '<span class="cheap">�@</span>' : '';
			rank_html += (easy==1)  ? '<span class="easy">�@</span>'  : '';
			var time_str = (hour ? hour + '����' : '') + min + '��';
			var fare_str = (fare ? fare + '�~' : '');
			var td_class = (i==route_len-1) ? " no_border" : "";
			temp_html2 += '<tr class="click" onclick="DmapOnClickRouteListRow('+i+')">';
			temp_html2 += '<td class="img'+td_class+'"><div id="rs_rte_list_chk'+i+'">�@</div></td>';
			temp_html2 += '<td class="no'+td_class+'"><span id="rs_rte_list_no'+i+'">'+(i+1)+'.</span></td>';
			temp_html2 += '<td class="text'+td_class+'"><span id="rs_rte_list_text'+i+'">'+time_str+'<br />'+fare_str+'</span></td>';
			temp_html2 += '<td class="rank'+td_class+'">'+rank_html+'</td>';
			temp_html2 += '</tr>';
		}
		head_html += '<span id="rs_rte_title">'+temp_html+'</span><a href="javascript:void(0);" id="rs_rte_select" onclick="DmapOnClickRouteSelect();">�@</a>';
		head_html += '<table id="rs_rte_list" class="hidden"><tbody>' + temp_html2 + '</tbody></table>';
		/* ���e */
		var link, transfer, rosen, from, to, hour, min, fare;
		for (var i=0, route_len=route.length; i<route_len; i++) {
			temp_html = '';
			/* �o���n�����ԉw�܂ł̕��s�҃��[�g */
			link = route[i].train.link[0];
			transfer = "walk";
			rosen = "";
			from = this.point.start.addr;
			to = link.station.from.name;
			hour = route[i].walk.first.time.hour;
			min = route[i].walk.first.time.min;
			temp_html += getListHtmlTrain(transfer, rosen, from, to, hour, min);
			/* ��ԉw���牺�ԉw�܂ł̓d�ԃ��[�g */
			for (var j=0, link_len=route[i].train.link.length; j<link_len; j++) {
				link = route[i].train.link[j];
				transfer = (link.railKind == "�k��" ? "walk" : "train");
				rosen = (link.railKind == "�k��" ? "" : link.name);
				from = link.station.from.name;
				to = link.station.to.name;
				hour = link.time.hour;
				min = link.time.min;
				fare = link.fare.total;
				temp_html += getListHtmlTrain(transfer, rosen, from, to, hour, min, fare);
			}
			/* ���ԉw����ړI�n�܂ł̕��s�҃��[�g */
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
	
	/* HTML��}�� */
	head_elm.innerHTML = head_html;
	body_elm.innerHTML = body_html;
	body_elm.scrollTop = 0;
	if (head_html || body_html) {
		/* ���[�g�ڍׂ�\������ */
		dtl_elm.style.display = 'block';
	}
}

/**
 * �������ʃ��X�g�̕\���^��\����؂�ւ��܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.toggleResultList = function () {
	var elm = document.getElementById("rs_rte_list");
	hasClass(elm, "hidden") ? elm.style.display = 'block' : elm.style.display = 'none';
}

/**
 * �������ʂ�؂�ւ��܂��B
 * @param {Number} idx ���ԍ�
 * @return {void}
 */
DmapClassRouteSearch.prototype.changeResult = function (idx) {
	if (this.mode == "train") {
		/* ���[�g�폜 */
		this.removeRoute();
		/* ���[�g�\�� */
		this.showRoute("train", this.route[idx].train.link);
		this.showRoute("walk",  this.route[idx].walk.first.link);
		this.showRoute("walk",  this.route[idx].walk.last.link);
		this.adjustZoom();
		/* �w�b�_�[�؂�ւ� */
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
		/* ���[�g�ڍא؂�ւ� */
		var body_elm = document.getElementById("rs_dtl_body");
		var tbl_elm = body_elm.getElementsByTagName("table");
		for (var i=0, len=tbl_elm.length; i<len; i++) {
			if (idx == i) {
				tbl_elm[i].style.display = 'block';
			} else {
				tbl_elm[i].style.display = 'none';
			}
		}
		/* ���[�g��⃊�X�g������ */
		document.getElementById("rs_rte_list").style.display = 'none';
	}
}

/**
 * ���[�g�ƃ}�[�J�[��S�ď������܂��B
 * @return {void}
 */
DmapClassRouteSearch.prototype.removeAllWidget = function () {
	/* ���[�g�폜 */
	this.removeRoute();
	/* �}�[�J�[�폜 */
	this.point.start.removeMarker();
	this.point.end.removeMarker();
}
