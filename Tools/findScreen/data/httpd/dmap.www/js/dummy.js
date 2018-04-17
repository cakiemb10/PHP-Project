/**
 * GPS�ʒu���擾�i�_�~�[�j
 * @return {boolean}
 */
function getCurrentPosition(waitTime, expire, datum) {
	var ret = [
		[0,35.6728422,139.7729583],
		[0,35.6871553,139.7046786],
		[0,35.6731869,139.7655047],
		[0,35.6603781,139.7830203],
		[0,35.6402572,139.7380039]
	];
	var i = Math.floor( Math.random() * 5 );
	/* �_�~�[���� */
//	return ret[i];
	return ret[0];
//	return ret[2];
}

/**
 * �t���O���Z�b�g�i�_�~�[�j
 * @return {void}
 */
function resetAllFlg() {
	alert('resetAllFlg');
}

/**
 * �f�o�b�O�p�F�B���{�^���C�x���g�����̃_�~�[�ihidden�̒l����alert���܂��j
 * @param {String} bid �B���{�^��ID
 * @return {boolean}
 */
function debugSubmit(btn) {
	var e;
	var msg = "id["+btn.id+"]\n"+"name["+btn.name+"]\n"
	switch (btn.id) {
		/* ���q���܏�� */
		case 'BTNKYAKU':
			e = document.getElementById('HIIE5001');if (e) msg += "HIIE5001="+e.value+"\n";
			e = document.getElementById('HIIF0111');if (e) msg += "HIIF0111="+e.value+"\n";
			e = document.getElementById('HIIF0551');if (e) msg += "HIIF0551="+e.value+"\n";
			e = document.getElementById('HICYA');if (e) msg += "HICYA="+e.value+"\n";
			e = document.getElementById('HIISTAN');if (e) msg += "HIISTAN="+e.value+"\n";
			break;
		/* �ŗ��m��� */
		case 'BTNZEIRI':
			e = document.getElementById('HIIE6001');if (e) msg += "HIIE6001="+e.value+"\n";
			break;
		/* �㗝�X��� */
		case 'BTNDAIRI':
			e = document.getElementById('HIIK0011');if (e) msg += "HIIK0011="+e.value+"\n";
			break;
		/* �f������ */
		case 'BTNSNSAI':
			e = document.getElementById('HIM10091');if (e) msg += "HIM10091="+e.value+"\n";
			break;
		/* ���q���ܖK�� */
		case 'BTNHOMON_dummy':
			e = document.getElementById('SYOROW');if (e) msg += "SYOROW="+e.value+"\n";
			break;
		/* �z�[���y�[�W */
		case 'BTNHP':
			e = document.getElementById('HINAME');if (e) msg += "HINAME="+e.value+"\n";
			e = document.getElementById('HIADD');if (e) msg += "HIADD="+e.value+"\n";
			e = document.getElementById('HIURL');if (e) msg += "HIURL="+e.value+"\n";
			break;
		/* �X�P�W���[�� */
		case 'BTNSCHED':
			e = document.getElementById('HIIF0551');if (e) msg += "HIIF0551="+e.value+"\n";
			e = document.getElementById('HIIF0506');if (e) msg += "HIIF0506="+e.value+"\n";
			e = document.getElementById('HINAME');if (e) msg += "HINAME="+e.value+"\n";
			break;
		/* �}�C�E�m�[�g */
		case 'BTNMN':
			e = document.getElementById('HIIF0551');if (e) msg += "HIIF0551="+e.value+"\n";
			e = document.getElementById('IG4041');if (e) msg += "IG4041="+e.value+"\n";
			break;
		/* �㗝�X�|�[�^�� */
		case 'BTNDAIPO':
			e = document.getElementById('HIIK0011');if (e) msg += "HIIK0011="+e.value+"\n";
			e = document.getElementById('HIIE5001');if (e) msg += "HIIE5001="+e.value+"\n";
			break;
		/* �K��� */
		case 'BTNVISP_dummy':
			e = document.getElementById('SITEI');if (e) msg += "SITEI="+e.value+"\n";
			break;
		/* �\���ʒu�C�� */
		case 'BTNPOSI_dummy':
			e = document.getElementById('CLAT');if (e) msg += "CLAT="+e.value+"\n";
			e = document.getElementById('CLON');if (e) msg += "CLON="+e.value+"\n";
			e = document.getElementById('SCALE');if (e) msg += "SCALE="+e.value+"\n";
			e = document.getElementById('SYOROW');if (e) msg += "SYOROW="+e.value+"\n";
			e = document.getElementById('SYULAT');if (e) msg += "SYULAT="+e.value+"\n";
			e = document.getElementById('SYULON');if (e) msg += "SYULON="+e.value+"\n";
			break;
		/* �Г���񌟍� */
		case 'BTNCOINF_dummy':
			e = document.getElementById('CLAT');if (e) msg += "CLAT="+e.value+"\n";
			e = document.getElementById('CLON');if (e) msg += "CLON="+e.value+"\n";
			e = document.getElementById('SCALE');if (e) msg += "SCALE="+e.value+"\n";
			e = document.getElementById('LTLAT');if (e) msg += "LTLAT="+e.value+"\n";
			e = document.getElementById('LTLON');if (e) msg += "LTLON="+e.value+"\n";
			e = document.getElementById('RBLAT');if (e) msg += "RBLAT="+e.value+"\n";
			e = document.getElementById('RBLON');if (e) msg += "RBLON="+e.value+"\n";
			e = document.getElementById('MEISYO');if (e) msg += "MEISYO="+e.value+"\n";
			e = document.getElementById('BNAME');if (e) msg += "BNAME="+e.value+"\n";
			break;
		/* �|�C���g�\���ύX */
		case 'BTNPCHG_dummy':
			e = document.getElementById('CLAT');if (e) msg += "CLAT="+e.value+"\n";
			e = document.getElementById('CLON');if (e) msg += "CLON="+e.value+"\n";
			e = document.getElementById('SCALE');if (e) msg += "SCALE="+e.value+"\n";
			e = document.getElementById('LTLAT');if (e) msg += "LTLAT="+e.value+"\n";
			e = document.getElementById('LTLON');if (e) msg += "LTLON="+e.value+"\n";
			e = document.getElementById('RBLAT');if (e) msg += "RBLAT="+e.value+"\n";
			e = document.getElementById('RBLON');if (e) msg += "RBLON="+e.value+"\n";
			e = document.getElementById('JOKEN11');if (e) msg += "JOKEN11="+e.value+"\n";
			e = document.getElementById('JOKEN12');if (e) msg += "JOKEN12="+e.value+"\n";
			e = document.getElementById('JOKEN2');if (e) msg += "JOKEN2="+e.value+"\n";
			break;
		/* �����q�o�^ */
		case 'BTNCUST':
			e = document.getElementById('HILAT');if (e) msg += "HILAT="+e.value+"\n";
			e = document.getElementById('HILON');if (e) msg += "HILON="+e.value+"\n";
			e = document.getElementById('HIADD');if (e) msg += "HIADD="+e.value+"\n";
			break;
	}
	alert(msg);
}
