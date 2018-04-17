/**
 * hiddenから情報を取得してDmapClassPinオブジェクトを生成します。
 * @class ピンの情報を保持します。
 * @param {Number} seq 連番（0～99）
 * @constructor
 */
var DmapClassPin = function(seq) {
	/**
	 * ピン画像のオブジェクト（ZDC.UserWidget）を保持します。
	 * @type Object
	 */
	this.widgetPin = null;
	/**
	 * ピンのz-index値を保持します。
	 * @type Number
	 */
	this.zindex = 0;
	/**
	 * ポイント名／業種名プレートのオブジェクト（ZDC.UserWidget）を保持します。
	 * @type Object
	 */
	this.widgetNm = null;
	/**
	 * 連番（0～99）を保持します。
	 * @type Number
	 */
	this.seq = seq;
	/**
	 * グループIDを保持します。
	 * @type String
	 */
	this.gid = DmapGetValueById('VLIST_GID_'+seq);
	/**
	 * 表示連番（1～50）を保持します。
	 * @type String
	 */
	this.num = '';
	/**
	 * 一覧表示連番（1～50）（グループの場合、1-1,1-2のような表記）を保持ます。
	 * @type String
	 */
	this.num_on_list = '';
	this.setNum(this.gid);
	/**
	 * 地図上にピンを表示するかどうかを保持します。
	 * @type Boolean
	 */
	this.plot = true;
	/**
	 * 職員コードを保持します。
	 * @type String
	 */
	this.syoku = DmapGetValueById('VLIST_IE5001_'+seq);
	/**
	 * 見込客番号を保持します。
	 * @type String
	 */
	this.mkno = DmapGetValueById('VLIST_IF0551_'+seq);
	/**
	 * 顧客番号を保持します。
	 * @type String
	 */
	this.cya = DmapGetValueById('VLIST_CYA_'+seq);
	this.cya000 = this.cya.substr(0, 12);
	this.cya001 = this.cya.substr(-4);
	/**
	 * 税理士登録番号を保持します。
	 * @type String
	 */
	this.zno = DmapGetValueById('VLIST_IE6001_'+seq);
	/**
	 * 代理店コードを保持します。
	 * @type String
	 */
	this.dcd = DmapGetValueById('VLIST_IK0011_'+seq);
	/**
	 * 診査医コードを保持します。
	 * @type String
	 */
	this.scd = DmapGetValueById('VLIST_M10091_'+seq);
	/**
	 * 分類コードを保持します。
	 * @type String
	 */
	this.buncd = DmapGetValueById('VLIST_IF0111_'+seq);
	/**
	 * 名称を保持します。
	 * @type String
	 */
	this.name = DmapGetValueById('VLIST_NAME_'+seq);
	/**
	 * 緯度を保持します。
	 * @type String
	 */
	this.lat = DmapGetValueById('VLIST_LAT_'+seq);
	/**
	 * 経度を保持します。
	 * @type String
	 */
	this.lon = DmapGetValueById('VLIST_LON_'+seq);
	if (this.lat && this.lon) {
		this.latlon = new ZDC.LatLon(this.lat, this.lon);	/* 緯度経度オブジェクト */
		this.org_latlon = this.latlon;
	}
	/**
	 * ドラッグ時のピン移動に使用される変数です。
	 * @type Number
	 */
	this.dragDifLat = null;
	/**
	 * ドラッグ時のピン移動に使用される変数です。
	 * @type Number
	 */
	this.dragDifLon = null;
	/**
	 * 色を保持します。
	 * @type String
	 */
	this.color = DmapGetValueById('VLIST_COLOR_'+seq);
	/**
	 * 区分を保持します。
	 * @type String
	 */
	this.type = DmapGetValueById('VLIST_TYPE_'+seq);
	/**
	 * 業種を保持します。
	 * @type String
	 */
	this.gyosyu  = DmapGetValueById('VLIST_CLASS_'+seq);
	if (this.gyosyu == "") this.gyosyu = "0";
	var atr_str = DmapGetValueById('VLIST_ATR_'+seq);
	/**
	 * 属性を保持します。
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
	 * 見込客名（カナ）を保持します。
	 * @type String
	 */
	this.kana   = DmapGetValueById('VLIST_IF0701_'+seq);
	/**
	 * 法人個人区分を保持します。
	 * @type String
	 */
	this.hkkbn  = DmapGetValueById('VLIST_IF0506_'+seq);
	/**
	 * 性別を保持します。
	 * @type String
	 */
	this.sex    = DmapGetValueById('VLIST_IF2031_'+seq);
	/**
	 * 生年月日を保持します。
	 * @type String
	 */
	this.bday   = DmapGetValueById('VLIST_IF2032_'+seq);
	/**
	 * 住所を保持します。
	 * @type String
	 */
	this.adrk   = DmapGetValueById('VLIST_ADRK_'+seq);
	/**
	 * TELを保持します。
	 * @type String
	 */
	this.tel    = DmapGetValueById('VLIST_TEL_'+seq);
	/**
	 * ホームページURLを保持します。
	 * @type String
	 */
	this.url    = DmapGetValueById('VLIST_URL_'+seq);
	/**
	 * 担当フラグを保持します。
	 * @type String
	 */
	this.istan  = DmapGetValueById('VLIST_ISTAN_'+seq);
	var icon_str= DmapGetValueById('VLIST_ICON_'+seq);
	/**
	 * アイコン区分を保持します。
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
	 * 定数：アイコン区分名称
	 * @type Array
	 */
	this.icon_lbl = {
		0:'お客さま情報',
		1:'税理士情報',
		2:'診査医情報',
		3:'お客さま訪問',
		4:'代理店ﾎﾟｰﾀﾙ',
		5:'ホームページ',
		6:'スケジュール',
		7:'マイ・ノート',
		8:'活動ガイド',
		9:'ルート表示'
	};
}

/**
 * ピンの表示連番をセットします。
 * @param {Number} num 表示連番（1～50）
 * @return {void}
 */
DmapClassPin.prototype.setNum = function(num) {
	this.num = num;
	this.num_len = (new String(this.num)).length;		/* numの桁数 */
	this.num_on_list = this.num;	/* 一覧表示連番（1～50）（グループの場合、1-1,1-2のような表記） */
}

/**
 * ピンがグループに属しているかどうかを返却します。
 * @return {Boolean} true：グループに属している／false：属していない
 */
DmapClassPin.prototype.inGroup = function() {
	return this.group;
}

/**
 * ピンの属性を詳細表示フォーマットに変換して返却します。
 * @return {String} フォーマットした文字列
 */
DmapClassPin.prototype.formatAtr = function() {
	var str = '';
	for (var i = 0; i < PIN_ATR_COUNT; i++) {
		if (this.atr[i] == COND_ENABLE) {
			if (str.length > 0) str += '・';
			switch (i) {
				case 0:
					str += '決算前';
					break;
				case 1:
					str += '決算後';
					break;
				case 2:
					str += '黒字';
					break;
				case 3:
					str += '新設';
					break;
				case 4:
					str += '会員';
					break;
				case 5:
					str += '協力者';
					break;
				case 6:
					str += '既契約';
					break;
				case 7:
					str += '未加入';
					break;
				case 8:
					str += 'ターゲット';
					break;
				case 9:
					str += '他者取扱企業';
					break;
			}
		}
	}
	return str;
}

/**
 * ピンの業種名を返却します。
 * @return {String} 業種名
 */
DmapClassPin.prototype.gyosyuName = function() {
	var str = '';
	switch (this.gyosyu) {
		case '1':
			str = '製造業';
			break;
		case '2':
			str = '建設業';
			break;
		case '3':
			str = '卸・小売業';
			break;
		case '4':
			str = 'サービス業';
			break;
		case '5':
			str = '通信・運輸';
			break;
		case '6':
			str = '不動産';
			break;
		case '7':
			str = '金融・保険業';
			break;
		case '8':
			str = '電気・ガス';
			break;
		case '9':
			str = '農業';
			break;
		case '10':
			str = '林業';
			break;
		case '11':
			str = '漁業';
			break;
		case '12':
			str = '鉱業';
			break;
		case '13':
			str = '公務・その他';
			break;
	}
	return str;
}

/**
 * ピンを最前面に移動させます。
 * @return {void}
 */
DmapClassPin.prototype.moveTop = function() {
	/* 表示済みピンの場合は最前面に移動 */
	if (this.widgetPin) {
		DmapZindexMax++;
		this.chgZindex(DmapZindexMax);
	/* 未表示のピンの場合は新規生成して表示 */
	} else {
		this.newWidget();
	}
	DmapPinList.removeGroupOtherPins(this);
}

/**
 * ピン画像オブジェクトを生成し、地図上に表示します。
 * @return {void}
 */
DmapClassPin.prototype.newWidget = function() {
	/* ピン */
	var html = '';
	html += '<div class="pin pin'+this.color+'">';
	html += '<div class="pin_num pin_num'+this.num+'">　</div>';
	html += '</div>';
	this.widgetPin = new ZDC.UserWidget(this.latlon, {
		html: html,
		offset: new ZDC.Pixel(PIN_ICON_OFFSET_X, PIN_ICON_OFFSET_Y),
		propagation: false
	});
	/* 地図上に表示 */
	DmapMap.addWidget(this.widgetPin);
	this.widgetPin.open();
	/* z-index指定 */
	DmapZindexMax++;
	this.chgZindex(DmapZindexMax);
	/* クリックイベント */
	ZDC.bind(this.widgetPin, ZDC.USERWIDGET_CLICK, this, DmapOnClickPin);
	/* ドラッグ用のイベント */
	ZDC.addListener(this.widgetPin, ZDC.USERWIDGET_MOUSEMOVE, DmapOnMouseMove);
	ZDC.bind(this.widgetPin, ZDC.USERWIDGET_MOUSEDOWN, this, DmapOnMouseDown);
	ZDC.addListener(this.widgetPin, ZDC.USERWIDGET_MOUSEUP, DmapOnMouseUp);
	/* 名称表示 */
	if (DmapIsShowPointNameOn()) {
		this.showPointName();
	}
	if (DmapIsShowGyosyuOn()) {
		this.showGyosyu();
	}
}

/**
 * ピン画像オブジェクトを消去します。
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
 * ピンのz-indexを変更します。
 * @param {Number} zindex z-index値
 * @return {void}
 */
DmapClassPin.prototype.chgZindex = function(zindex) {
	this.zindex = zindex;
	this.widgetPin.setZindex(this.zindex);
	if (this.widgetNm) this.widgetNm.setZindex(this.zindex);
}

/**
 * ピンを指定の緯度経度へ移動させます。
 * @param {Number} lat 緯度
 * @param {Number} lon 経度
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
 * ピンを元の緯度経度へ移動させます。
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
 * ピン上方にポイント名を表示します。
 * @return {void}
 */
DmapClassPin.prototype.showPointName = function() {
	if (!this.widgetPin) return;
	var offsety = PIN_NAME_OFFSET_Y;
	var html = '';
	/* 業種名表示中 */
	if (DmapIsShowGyosyuOn() && this.gyosyuName() != '') {
		var gyosyu_html = this.gyosyuName();
		if (this.group) {
			gyosyu_html += '(複数あり)';
		}
		html += '<div class="pointname">'+gyosyu_html+'</div>';
		offsety = offsety - 18;
	}
	/* ポイント名を表示 */
	var name_html = this.name;
	if (this.group) {
		name_html += '(複数あり)';
	}
	html += '<div><div class="pointname">'+name_html+'</div></div>';
	/* 一旦消す */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* Widgetを新規生成 */
	this.widgetNm = new ZDC.UserWidget(this.latlon, {
		html: html,
		offset: new ZDC.Pixel(PIN_NAME_OFFSET_X, offsety),
		propagation: false
	});
	/* 地図上に表示 */
	DmapMap.addWidget(this.widgetNm);
	this.widgetNm.open();
	this.widgetNm.setZindex(this.zindex);
}

/**
 * ピン上方のポイント名を消去します。
 * @return {void}
 */
DmapClassPin.prototype.removePointName = function() {
	if (!this.widgetPin) return;
	/* Widgetを消去 */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* 業種名表示中 */
	if (DmapIsShowGyosyuOn()) {
		this.showGyosyu();
	}
}

/**
 * ピン上方に業種名を表示します。
 * @return {void}
 */
DmapClassPin.prototype.showGyosyu = function() {
	if (!this.widgetPin) return;
	if (this.gyosyuName() == '') return;
	var offsety = PIN_NAME_OFFSET_Y;
	var html = '';
	/* 業種名を表示 */
	var gyosyu_html = this.gyosyuName();
	if (this.group) {
		gyosyu_html += '(複数あり)';
	}
	html += '<div class="pointname">'+gyosyu_html+'</div>';
	/* ポイント名表示中 */
	if (DmapIsShowPointNameOn()) {
		var name_html = this.name;
		if (this.group) {
			name_html += '(複数あり)';
		}
		html += '<div><div class="pointname">'+name_html+'</div></div>';
		offsety = offsety - 18;
	}
	/* 一旦消す */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* Widgetを新規生成 */
	this.widgetNm = new ZDC.UserWidget(this.latlon, {
		html: html,
		offset: new ZDC.Pixel(PIN_NAME_OFFSET_X, offsety),
		propagation: false
	});
	/* 地図上に表示 */
	DmapMap.addWidget(this.widgetNm);
	this.widgetNm.open();
	this.widgetNm.setZindex(this.zindex);
}

/**
 * ピン上方の業種名を消去します。
 * @return {void}
 */
DmapClassPin.prototype.removeGyosyu = function() {
	if (!this.widgetPin) return;
	/* Widgetを消去 */
	if (this.widgetNm) {
		DmapMap.removeWidget(this.widgetNm);
		this.widgetNm = null;
	}
	/* ポイント名表示中 */
	if (DmapIsShowPointNameOn()) {
		this.showPointName();
	}
}

/**
 * 「既契約」かどうかを返却します。
 * @return {Boolean} true：既契約／false：既契約ではない
 */
DmapClassPin.prototype.isKikeiyaku = function() {
	return (this.atr[6] == COND_ENABLE);
}

/**
 * 「未加入」かどうかを返却します。
 * @return {Boolean} true：未加入／false：未加入ではない
 */
DmapClassPin.prototype.isMikanyu = function() {
	return (this.atr[7] == COND_ENABLE);
}

/**
 * 移動可能なピンかどうかを返却します。
 * @param {Object} user DmapUserオブジェクト
 * @return {Boolean} true：移動可能／false：移動不可
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
