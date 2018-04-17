/**
 * DmapJSONP�I�u�W�F�N�g�𐶐����܂��B
 * @class JSONP�ʐM�𐧌䂵�܂��B
 * @constructor
 */
var DmapJSONP = {
	callback: {},
	/**
	 * �N�G����������܂߂�URL�𐶐����܂��B
	 * @param {String} base �x�[�XURL
	 * @param {Array} args �p�����[�^
	 * @return {String} URL
	 */
	serialize: function (base, args) {
		var query = [];
		for (var key in args) {
			query.push(
				encodeURIComponent(key) + '=' +
				encodeURIComponent(args[key])
			);
		}
		return base + '?' + query.join('&');
	},
	/**
	 * JSONP�Ńf�[�^���擾���܂��B
	 * @param {String} url URL
	 * @param {Array} params �p�����[�^
	 * @param {Function} callback �R�[���o�b�N�֐�
	 * @return {void}
	 */
	get: function (url, params, callback) {
		/* �p�����[�^����'callback'���g���Ă���ꍇ�́A�d������̂ŃG���[ */
		if (params["callback"]) return;
		/* ID���� */
		do {
			var id = Math.floor(Math.random() * 1E10);
		} while(DmapJSONP.callback[id]);
		/* ���X�|���X�n���h����o�^ */
		DmapJSONP.callback[id] = callback;
		/* �p�����[�^�Ƀn���h������ǉ� */
		params["callback"] = 'DmapJSONP.callback['+id+']';
		/* script�^�O���� */
		var req = document.createElement('script');
		/* JSON�̓ǂݍ��݊��������ꍇ */
		req.onload = req.onreadystatechange = function () {
			if (!this.readyState ||
				this.readyState === "loaded" ||
				this.readyState === "complete") {
				this.onreadystatechange = null;
				/* �^�C���A�E�g���������� */
				clearTimeout(timer_id);
				/* �ǉ�����script�^�O���폜 */
				if (req && req.parentNode) document.body.removeChild(req);
				/* �o�^�������X�|���X�n���h�����폜 */
				delete DmapJSONP.callback[id];
			}
		};
		/* JSON�̓ǂݍ��݂��G���[�̏ꍇ */
		req.onerror = function() {
			/* �^�C���A�E�g���������� */
			clearTimeout(timer_id);
			/* �ǉ�����script�^�O���폜 */
			if (req && req.parentNode) document.body.removeChild(req);
			/* ���X�|���X�n���h���ɃG���[���X�|���X��n�� */
			DmapJSONP.callback[id]({code: "102",text: "timeout"}, null);
			/* �o�^�������X�|���X�n���h�����폜 */
			delete DmapJSONP.callback[id];
		};
		/* �^�C���A�E�g������ݒ�i15�b�j */
		var timer_id = setTimeout(function() {
			try {
				/* �ǉ�����script�^�O���폜 */
				if (req && req.parentNode) document.body.removeChild(req);
				/* ���X�|���X�n���h���ɃG���[���X�|���X��n�� */
				DmapJSONP.callback[id]({code: "102",text: "timeout"}, null);
				/* ���X�|���X�n���h�������function�ɕύX */
				DmapJSONP.callback[id] = function () {};
			} catch (d) {
			}
		}, 15000);
		/* ��������script�^�O��URL����ǉ����āAbody�^�O�ɒǉ� */
		req.async = true;
		req.type = 'text/javascript';
		req.src = DmapJSONP.serialize(url, params);
		document.body.appendChild(req);
	}
}
