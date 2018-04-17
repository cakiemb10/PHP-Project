/**
 * hidden��������擾����DmapClassUser�I�u�W�F�N�g�𐶐����܂��B
 * @class ����҂̏���ێ����܂��B
 * @constructor
 */
var DmapClassUser = function() {
	/**
	 * �E���R�[�h��ێ����܂��B
	 * @type String
	 */
	this.syokuin = DmapGetValueById('IE5001');
	/**
	 * �x�ЃR�[�h��ێ����܂��B
	 * @type String
	 */
	this.sisya = DmapGetValueById('IE50021');
	/**
	 * �ۃR�[�h��ێ����܂��B
	 * @type String
	 */
	this.ka = DmapGetValueById('IE50031');
	/**
	 * �����R�[�h��ێ����܂��B
	 * @type String
	 */
	this.auth = DmapGetValueById('IE5005');
	/**
	 * �E���^�C�v��ێ����܂��B
	 * @type String
	 */
	this.syoku = DmapGetValueById('SYOKU');
}

/**
 * ����҂���Ƃ��ǂ�����ԋp���܂��B
 * @return {Boolean} true�F��Ɓ^false�F��Ƃł͂Ȃ�
 */
DmapClassUser.prototype.isProper = function() {
	return (this.syoku == "1");
}

/**
 * ����҂��G�[�W�F���g���ǂ�����ԋp���܂��B
 * @return {Boolean} true�F�G�[�W�F���g�^false�F�G�[�W�F���g�ł͂Ȃ�
 */
DmapClassUser.prototype.isAgent = function() {
	return (this.syoku == "2");
}

/**
 * �|�C���g�\���ύX�̏����ݒ�p�^�[����ԋp���܂��B
 * @return {Number} 1�`3
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
 * �x�ЃR�[�h���͗��̓��͉^�s��ԋp���܂��B
 * @return {Boolean} true�F���͉^false�F���͕s��
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
 * �ۃR�[�h���͗��̓��͉^�s��ԋp���܂��B
 * @return {Boolean} true�F���͉^false�F���͕s��
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
 * �E���R�[�h���͗��̓��͉^�s��ԋp���܂��B
 * @return {Boolean} true�F���͉^false�F���͕s��
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
