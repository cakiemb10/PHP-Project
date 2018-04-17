/**
 * hiddenから情報を取得してDmapClassUserオブジェクトを生成します。
 * @class 操作者の情報を保持します。
 * @constructor
 */
var DmapClassUser = function() {
	/**
	 * 職員コードを保持します。
	 * @type String
	 */
	this.syokuin = DmapGetValueById('IE5001');
	/**
	 * 支社コードを保持します。
	 * @type String
	 */
	this.sisya = DmapGetValueById('IE50021');
	/**
	 * 課コードを保持します。
	 * @type String
	 */
	this.ka = DmapGetValueById('IE50031');
	/**
	 * 権限コードを保持します。
	 * @type String
	 */
	this.auth = DmapGetValueById('IE5005');
	/**
	 * 職員タイプを保持します。
	 * @type String
	 */
	this.syoku = DmapGetValueById('SYOKU');
}

/**
 * 操作者が専業かどうかを返却します。
 * @return {Boolean} true：専業／false：専業ではない
 */
DmapClassUser.prototype.isProper = function() {
	return (this.syoku == "1");
}

/**
 * 操作者がエージェントかどうかを返却します。
 * @return {Boolean} true：エージェント／false：エージェントではない
 */
DmapClassUser.prototype.isAgent = function() {
	return (this.syoku == "2");
}

/**
 * ポイント表示変更の条件設定パターンを返却します。
 * @return {Number} 1～3
 */
DmapClassUser.prototype.getSPCondPattern = function() {
	switch (this.auth) {
		case '01':
		case '20':
		case '02':
		case '14':
		case '21':
		case '03':
		case '16':
			return 1;
		case '07':
		case '08':
			return 2;
		case '12':
		case '22':
			return 3;
	}
	return 0;
}

/**
 * 支社コード入力欄の入力可／不可を返却します。
 * @return {Boolean} true：入力可／false：入力不可
 */
DmapClassUser.prototype.isSisyaEnable = function() {
	switch (this.auth) {
		case '12':
		case '22':
			return true;
	}
	return false;
}

/**
 * 課コード入力欄の入力可／不可を返却します。
 * @return {Boolean} true：入力可／false：入力不可
 */
DmapClassUser.prototype.isKaEnable = function() {
	switch (this.auth) {
		case '03':
		case '16':
		case '12':
		case '22':
			return true;
	}
	return false;
}

/**
 * 職員コード入力欄の入力可／不可を返却します。
 * @return {Boolean} true：入力可／false：入力不可
 */
DmapClassUser.prototype.isSyokuinEnable = function() {
	switch (this.auth) {
		case '02':
		case '14':
		case '21':
		case '03':
		case '16':
		case '12':
		case '22':
		case '05':
		case '06':
			return true;
	}
	return false;
}
