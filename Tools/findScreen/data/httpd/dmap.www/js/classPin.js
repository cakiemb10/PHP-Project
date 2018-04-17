/**
 * hidden��������擾����DmapClassPin�I�u�W�F�N�g�𐶐����܂��B
 * @class �s���̏���ێ����܂��B
 * @param {Number} seq �A�ԁi0�`99�j
 * @constructor
 */
var DmapClassPin = function(seq) {
	/**
	 * �s���摜�̃I�u�W�F�N�g�iZDC.UserWidget�j��ێ����܂��B
	 * @type Object
	 */
	this.widgetPin = null;
	/**
	 * �s����z-index�l��ێ����܂��B
	 * @type Number
	 */
	this.zindex = 0;
	/**
	 * �|�C���g���^�Ǝ햼�v���[�g�̃I�u�W�F�N�g�iZDC.UserWidget�j��ێ����܂��B
	 * @type Object
	 */
	this.widgetNm = null;
	/**
	 * �A�ԁi0�`99�j��ێ����܂��B
	 * @type Number
	 */
	this.seq = seq;
	/**
	 * �O���[�vID��ێ����܂��B
	 * @type String
	 */
	this.gid = DmapGetValueById('VLIST_GID_'+seq);
	/**
	 * �\���A�ԁi1�`50�j��ێ����܂��B
	 * @type String
	 */
	this.num = '';
	/**
	 * �ꗗ�\���A�ԁi1�`50�j�i�O���[�v�̏ꍇ�A1-1,1-2�̂悤�ȕ\�L�j��ێ��܂��B
	 * @type String
	 */
	this.num_on_list = '';
	this.setNum(this.gid);
	/**
	 * �n�}��Ƀs����\�����邩�ǂ�����ێ����܂��B
	 * @type Boolean
	 */
	this.plot = true;
	/**
	 * �E���R�[�h��ێ����܂��B
	 * @type String
	 */
	this.syoku = DmapGetValueById('VLIST_IE5001_'+seq);
	/**
	 * �����q�ԍ���ێ����܂��B
	 * @type String
	 */
	this.mkno = DmapGetValueById('VLIST_IF0551_'+seq);
	/**
	 * �ڋq�ԍ���ێ����܂��B
	 * @type String
	 */
	this.cya = DmapGetValueById('VLIST_CYA_'+seq);
	this.cya000 = this.cya.substr(0, 12);
	this.cya001 = this.cya.substr(-4);
	/**
	 * �ŗ��m�o�^�ԍ���ێ����܂��B
	 * @type String
	 */
	this.zno = DmapGetValueById('VLIST_IE6001_'+seq);
	/**
	 * �㗝�X�R�[�h��ێ����܂��B
	 * @type String
	 */
	this.dcd = DmapGetValueById('VLIST_IK0011_'+seq);
	/**
	 * �f����R�[�h��ێ����܂��B
	 * @type String
	 */
	this.scd = DmapGetValueById('VLIST_M10091_'+seq);
	/**
	 * ���ރR�[�h��ێ����܂��B
	 * @type String
	 */
	this.buncd = DmapGetValueById('VLIST_IF0111_'+seq);
	/**
	 * ���̂�ێ����܂��B
	 * @type String
	 */
	this.name = DmapGetValueById('VLIST_NAME_'+seq);
	/**
	 * �ܓx��ێ����܂��B
	 * @type String
	 */
	this.lat = DmapGetValueById('VLIST_LAT_'+seq);
	/**
	 * �o�x��ێ����܂��B
	 * @type String
	 */
	this.lon = DmapGetValueById('VLIST_LON_'+seq);
	if (this.lat && this.lon) {
		this.latlon = new ZDC.LatLon(this.lat, this.lon);	/* �ܓx�o�x�I�u�W�F�N�g */
		this.org_latlon = this.latlon;
	}
	/**
	 * �h���b�O���̃s���ړ��Ɏg�p�����ϐ��ł��B
	 * @type Number
	 */
	this.dragDifLat = null;
	/**
	 * �h���b�O���̃s���ړ��Ɏg�p�����ϐ��ł��B
	 * @type Number
	 */
	this.dragDifLon = null;
	/**
	 * �F��ێ����܂��B
	 * @type String
	 */
	this.color = DmapGetValueById('VLIST_COLOR_'+seq);
	/**
	 * �敪��ێ����܂��B
	 * @type String
	 */
	this.type = DmapGetValueById('VLIST_TYPE_'+seq);
	/**
	 * �Ǝ��ێ����܂��B
	 * @type String
	 */
	this.gyosyu  = DmapGetValueById('VLIST_CLASS_'+seq);
	if (this.gyosyu == "") this.gyosyu = "0";
	var atr_str = DmapGetValueById('VLIST_ATR_'+seq);
	/**
	 * ������ێ����܂��B
	 * @type Array
	 */
	this.atr = new Array();
	for (var i = 0; i < PIN_ATR_COUNT; i++) {
		if (atr_str.length > i) {
			switch (atr_str.substr(i, 1)) {
				case "1":
					this.atr[i] = COND_ENABLE;
					break;
				case "2":
					this.atr[i] = COND_DISABLE;
					break;
				default:
					this.atr[i] = COND_INVISIBLE;
			}
		}
	}
	/**
	 * �����q���i�J�i�j��ێ����܂��B
	 * @type String
	 */
	this.kana   = DmapGetValueById('VLIST_IF0701_'+seq);
	/**
	 * �@�l�l�敪��ێ����܂��B
	 * @type String
	 */
	this.hkkbn  = DmapGetValueById('VLIST_IF0506_'+seq);
	/**
	 * ���ʂ�ێ����܂��B
	 * @type String
	 */
	this.sex    = DmapGetValueById('VLIST_IF2031_'+seq);
	/**
	 * ���N������ێ����܂��B
	 * @type String
	 */
	this.bday   = DmapGetValueById('VLIST_IF2032_'+seq);
	/**
	 * �Z����ێ����܂��B
	 * @type String
	 */
	this.adrk   = DmapGetValueById('VLIST_ADRK_'+seq);
	/**
	 * TEL��ێ����܂��B
	 * @type String
	 */
	this.tel    = DmapGetValueById('VLIST_TEL_'+seq);
	/**
	 * �z�[���y�[�WURL��ێ����܂��B
	 * @type String
	 */
	this.url    = DmapGetValueById('VLIST_URL_'+seq);
	/**
	 * �S���t���O��ێ����܂��B
	 * @type String
	 */
	this.istan  = DmapGetValueById('VLIST_ISTAN_'+seq);
	var icon_str= DmapGetValueById('VLIST_ICON_'+seq);
	/**
	 * �A�C�R���敪��ێ����܂��B
	 * @type Array
	 */
	this.icon   = new Array();
	for (var i = 0; i < PIN_ICON_COUNT; i++) {
		if (icon_str.length > i) {
			switch (icon_str.substr(i, 1)) {
				case "1":
					this.icon[i] = COND_ENABLE;
					break;
				case "2":
					this.icon[i] = COND_DISABLE;
					break;
				default:
					this.icon[i] = COND_INVISIBLE;
			}
		}
	}
	/**
	 * �萔�F�A�C�R���敪����
	 * @type Array
	 */
	this.icon_lbl = {
		0:'���q���܏��',
		1:'�ŗ��m���',
		2:'�f������',
		3:'���q���ܖK��',
		4:'�㗝�X�߰��',
		5:'�z�[���y�[�W',
		6:'�X�P�W���[��',
		7:'�}�C�E�m�[�g',
		8:'�����K�C�h',
		9:'���[�g�\��'
	};
}

/**
 * �s���̕\���A�Ԃ��Z�b�g���܂��B
 * @param {Number} num �\���A�ԁi1�`50�j
 * @return {void}
 */
DmapClassPin.prototype.setNum = function(num) {
	this.num = num;
	this.num_len = (new String(this.num)).length;		/* num�̌��� */
	this.num_on_list = this.num;	/* �ꗗ�\���A�ԁi1�`50�j�i�O���[�v�̏ꍇ�A1-1,1-2�̂悤�ȕ\�L�j */
}

/**
 * �s�����O���[�v�ɑ����Ă��邩�ǂ�����ԋp���܂��B
 * @return {Boolean} true�F�O���[�v�ɑ����Ă���^false�F�����Ă��Ȃ�
 */
DmapClassPin.prototype.inGroup = function() {
	return this.group;
}

/**
 * �s���̑������ڍו\���t�H�[�}�b�g�ɕϊ����ĕԋp���܂��B
 * @return {String} �t�H�[�}�b�g����������
 */
DmapClassPin.prototype.formatAtr = function() {
	var str = '';
	for (var i = 0; i < PIN_ATR_COUNT; i++) {
		if (this.atr[i] == COND_ENABLE) {
			if (str.length > 0) str += '�E';
			switch (i) {
				case 0:
					str += '���Z�O';
					break;
				case 1:
					str += '���Z��';
					break;
				case 2:
					str += '����';
					break;
				case 3:
					str += '�V��';
					break;
				case 4:
					str += '���';
					break;
				case 5:
					str += '���͎�';
					break;
				case 6:
					str += '���_��';
					break;
				case 7:
					str += '������';
					break;
				case 8:
					str += '�^�[�Q�b�g';
					break;
				case 9:
					str += '���Ҏ戵���';
					break;
			}
		}
	}
	return str;
}

/**
 * �s���̋Ǝ햼��ԋp���܂��B
 * @return {String} �Ǝ햼
 */
DmapClassPin.prototype.gyosyuName = function() {
	var str = '';
	switch (this.gyosyu) {
		case '1':
			str = '������';
			break;
		case '2':
			str = '���݋�';
			break;
		case '3':
			str = '���E������';
			break;
		case '4':
			str = '�T�[�r�X��';
			break;
		case '5':
			str = '�ʐM�E�^�A';
			break;
		case '6':
			str = '�s���Y';
			break;
		case '7':
			str = '���Z�E�ی���';
			break;
		case '8':
			str = '�d�C�E�K�X';
			break;
		case '9':
			str = '�_��';
			break;
		case '10':
			str = '�ы�';
			break;
		case '11':
			str = '����';
			break;
		case '12':
			str = '�z��';
			break;
		case '13':
			str = '�����E���̑�';
			break;
	}
	return str;
}

/**
 * �s�����őO�ʂɈړ������܂��B
 * @return {void}
 */
DmapClassPin.prototype.moveTop = function() {
	/* �\���ς݃s���̏ꍇ�͍őO�ʂɈړ� */
	if (this.widgetPin) {
		DmapZindexMax++;
		this.chgZindex(DmapZindexMax);
	/* ���\���̃s���̏ꍇ�͐V�K�������ĕ\�� */
	} else {
		this.newWidget();
	}
	DmapPinList.removeGroupOtherPins(this);
}

/**
 * �s���摜�I�u�W�F�N�g�𐶐����A�n�}��ɕ\�����܂��B
 * @return {void}
 */
DmapClassPin.prototype.newWidget = function() {
	/* �s�� */
	var html = '';
	html += '<div class="pin pin'+this.color+'">';
	html += '<div class="pin_num pin_num'+this.num+'">�@</div>';
	html += '</div>';
	this.widgetPin = new ZDC.UserWidget(this.latlon, {
		html: html,
		offset: new ZDC.Pixel(PIN_ICON_OFFSET_X, PIN_ICON_OFFSET_Y),
		propagation: false
	});
	/* �n�}��ɕ\�� */
	DmapMap.addWidget(this.widgetPin);
	this.widgetPin.open();
	/* z-index�w�� */
	DmapZindexMax++;
	this.chgZindex(DmapZindexMax);
	/* �N���b�N�C�x���g */
	ZDC.bind(this.widgetPin, ZDC.USERWIDGET_CLICK, this, DmapOnClickPin);
	/* �h���b�O�p�̃C�x���g */
	ZDC.addListener(this.widgetPin, ZDC.USERWIDGET_MOUSEMOVE, DmapOnMouseMove);
	ZDC.bind(this.widgetPin, ZDC.USERWIDGET_MOUSEDOWN, this, DmapOnMouseDown);
	ZDC.addListener(this.widgetPin, ZDC.USERWIDGET_MOUSEUP, DmapOnMouseUp);
	/* ���̕\�� */
	if (DmapIsShowPointNameOn()) {
		this.showPointName();
	}
	if (DmapIsShowGyosyuOn()) {
		this.showGyosyu();
	}
}

/**
 * �s���摜�I�u�W�F�N�g���������܂��B
 * @return {void}
 */
DmapClassPin.prototype.removeWidget = function() {
	if (this.widgetPin) {
		DmapMap.removeWidget(this.widgetPin);
		this.widgetPin = null;
	}
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
}

/**
 * �s����z-index��ύX���܂��B
 * @param {Number} zindex z-index�l
 * @return {void}
 */
DmapClassPin.prototype.chgZindex = function(zindex) {
	this.zindex = zindex;
	this.widgetPin.setZindex(this.zindex);
	if (this.widgetNm) this.widgetNm.setZindex(this.zindex);
}

/**
 * �s�����w��̈ܓx�o�x�ֈړ������܂��B
 * @param {Number} lat �ܓx
 * @param {Number} lon �o�x
 * @return {void}
 */
DmapClassPin.prototype.moveLatLon = function(lat, lon) {
	this.lat = lat;
	this.lon = lon;
	this.latlon = new ZDC.LatLon(lat, lon);
	if (this.latlon && this.widgetPin) {
		this.widgetPin.moveLatLon(this.latlon);
		if (this.widgetNm) this.widgetNm.moveLatLon(this.latlon);
	}
}

/**
 * �s�������̈ܓx�o�x�ֈړ������܂��B
 * @return {void}
 */
DmapClassPin.prototype.moveOrgLatLon = function() {
	this.lat = this.org_latlon.lat;
	this.lon = this.org_latlon.lon;
	this.latlon = new ZDC.LatLon(this.lat, this.lon);
	if (this.latlon && this.widgetPin) {
		this.widgetPin.moveLatLon(this.latlon);
		if (this.widgetNm) this.widgetNm.moveLatLon(this.latlon);
	}
}

/**
 * �s������Ƀ|�C���g����\�����܂��B
 * @return {void}
 */
DmapClassPin.prototype.showPointName = function() {
	if (!this.widgetPin) return;
	var offsety = PIN_NAME_OFFSET_Y;
	var html = '';
	/* �Ǝ햼�\���� */
	if (DmapIsShowGyosyuOn() && this.gyosyuName() != '') {
		var gyosyu_html = this.gyosyuName();
		if (this.group) {
			gyosyu_html += '(��������)';
		}
		html += '<div class="pointname">'+gyosyu_html+'</div>';
		offsety = offsety - 18;
	}
	/* �|�C���g����\�� */
	var name_html = this.name;
	if (this.group) {
		name_html += '(��������)';
	}
	html += '<div><div class="pointname">'+name_html+'</div></div>';
	/* ��U���� */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* Widget��V�K���� */
	this.widgetNm = new ZDC.UserWidget(this.latlon, {
		html: html,
		offset: new ZDC.Pixel(PIN_NAME_OFFSET_X, offsety),
		propagation: false
	});
	/* �n�}��ɕ\�� */
	DmapMap.addWidget(this.widgetNm);
	this.widgetNm.open();
	this.widgetNm.setZindex(this.zindex);
}

/**
 * �s������̃|�C���g�����������܂��B
 * @return {void}
 */
DmapClassPin.prototype.removePointName = function() {
	if (!this.widgetPin) return;
	/* Widget������ */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* �Ǝ햼�\���� */
	if (DmapIsShowGyosyuOn()) {
		this.showGyosyu();
	}
}

/**
 * �s������ɋƎ햼��\�����܂��B
 * @return {void}
 */
DmapClassPin.prototype.showGyosyu = function() {
	if (!this.widgetPin) return;
	if (this.gyosyuName() == '') return;
	var offsety = PIN_NAME_OFFSET_Y;
	var html = '';
	/* �Ǝ햼��\�� */
	var gyosyu_html = this.gyosyuName();
	if (this.group) {
		gyosyu_html += '(��������)';
	}
	html += '<div class="pointname">'+gyosyu_html+'</div>';
	/* �|�C���g���\���� */
	if (DmapIsShowPointNameOn()) {
		var name_html = this.name;
		if (this.group) {
			name_html += '(��������)';
		}
		html += '<div><div class="pointname">'+name_html+'</div></div>';
		offsety = offsety - 18;
	}
	/* ��U���� */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* Widget��V�K���� */
	this.widgetNm = new ZDC.UserWidget(this.latlon, {
		html: html,
		offset: new ZDC.Pixel(PIN_NAME_OFFSET_X, offsety),
		propagation: false
	});
	/* �n�}��ɕ\�� */
	DmapMap.addWidget(this.widgetNm);
	this.widgetNm.open();
	this.widgetNm.setZindex(this.zindex);
}

/**
 * �s������̋Ǝ햼���������܂��B
 * @return {void}
 */
DmapClassPin.prototype.removeGyosyu = function() {
	if (!this.widgetPin) return;
	/* Widget������ */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* �|�C���g���\���� */
	if (DmapIsShowPointNameOn()) {
		this.showPointName();
	}
}

/**
 * �u���_��v���ǂ�����ԋp���܂��B
 * @return {Boolean} true�F���_��^false�F���_��ł͂Ȃ�
 */
DmapClassPin.prototype.isKikeiyaku = function() {
	return (this.atr[6] == COND_ENABLE);
}

/**
 * �u�������v���ǂ�����ԋp���܂��B
 * @return {Boolean} true�F�������^false�F�������ł͂Ȃ�
 */
DmapClassPin.prototype.isMikanyu = function() {
	return (this.atr[7] == COND_ENABLE);
}

/**
 * �ړ��\�ȃs�����ǂ�����ԋp���܂��B
 * @param {Object} user DmapUser�I�u�W�F�N�g
 * @return {Boolean} true�F�ړ��\�^false�F�ړ��s��
 */
DmapClassPin.prototype.isMovable = function(user) {
	if (this.type == VLIST_TYPE_DR) {
		return false;
	}
	if (user.auth != '12') {
		if (this.isKikeiyaku() && this.mkno == '000000000000000') {
			return false;
		}
		if (this.isMikanyu() && this.mkno == '000000000000000') {
			return false;
		}
		if (this.type == VLIST_TYPE_ZEI) {
			return false;
		}
		if (this.type == VLIST_TYPE_AGENT) {
			return false;
		}
	}
	var s = DmapGetValueById('TIE50012');
	if (DmapUser.syokuin != s) {
		//if (parseInt(this.mkno) > 0) {
		if (this.mkno != '000000000000000') {
			return false;
		}
	}
	return true;
}
