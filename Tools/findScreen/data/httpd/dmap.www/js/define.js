/**
 * �萔<br>����NAVI CGI���b�p�[�̎Q�Ɛ�h���C��<br>���J�����Ɩ{�Ԋ��ŎQ�Ɛ悪�قȂ�̂ŁA�����ւ����K�v�ł��B
 * @type String
 */
//var EMAPCGI_DOMAIN = 'test.e-map.ne.jp';	/* �J���� */
var EMAPCGI_DOMAIN = 'www.e-map.ne.jp';	/* �{�Ԋ� */

/**
 * �萔<br>Cookie�ۑ����ԁi�����j
 * @type Number
 */
var COOKIE_EXPIRES = 30;

/**
 * �萔<br>��ԁF��\��
 * @type Number
 */
var COND_INVISIBLE = 0;

/**
 * �萔<br>��ԁF�\���i�����j
 * @type Number
 */
var COND_ENABLE = 1;

/**
 * �萔<br>��ԁF�\���i�񊈐��j
 * @type Number
 */
var COND_DISABLE = 2;

/**
 * �萔<br>�s���敪�F���
 * @type String
 */
var VLIST_TYPE_CORP = "1";

/**
 * �萔<br>�s���敪�F�l
 * @type String
 */
var VLIST_TYPE_IND = "2";

/**
 * �萔<br>�s���敪�F�ŗ��m
 * @type String
 */
var VLIST_TYPE_ZEI = "3";

/**
 * �萔<br>�s���敪�F�㗝�X
 * @type String
 */
var VLIST_TYPE_AGENT = "4";

/**
 * �萔<br>�s���敪�F�f����
 * @type String
 */
var VLIST_TYPE_DR = "5";

/**
 * �萔<br>�s�������̐�
 * @type Number
 */
var PIN_ATR_COUNT = 10;

/**
 * �萔<br>�s���A�C�R���敪�̐�
 * @type Number
 */
var PIN_ICON_COUNT = 10;

/**
 * �萔<br>�s���A�C�R����offset�ix�����j
 * @type Number
 */
var PIN_ICON_OFFSET_X = -16;

/**
 * �萔<br>�s���A�C�R����offset�iy�����j
 * @type Number
 */
var PIN_ICON_OFFSET_Y = -50;

/**
 * �萔<br>�|�C���g��or�Ǝ햼��offset�ix�����j
 * @type Number
 */
var PIN_NAME_OFFSET_X = -23;

/**
 * �萔<br>�|�C���g��or�Ǝ햼��offset�iy�����j
 * @type Number
 */
var PIN_NAME_OFFSET_Y = -65;

/**
 * �萔<br>�����x�Ж���offset�ix�����j
 * @type Number
 */
var SYZ_NAME_OFFSET_X = -33;

/**
 * �萔<br>�����x�Ж���offset�iy�����j
 * @type Number
 */
var SYZ_NAME_OFFSET_Y = -65;

/**
 * �萔<br>�Z���t���[���[�h�����̕\������
 * @type Number
 */
var SRCH_ADDR_ROWS = 100;

/**
 * �萔<br>POI�t���[���[�h�����̎擾����
* @type Number
 */
var SRCH_POI_LIMIT = 10000;

/**
 * �萔<br>POI�t���[���[�h�����̕\������
* @type Number
 */
var SRCH_POI_ROWS = 100;

/**
 * �萔<br>POI�t���[���[�h�����ōi���݂��s��臒l����
* @type Number
 */
var SRCH_POI_EXT = 50;

/**
 * �萔<br>����POI�����̎擾����
* @type Number
 */
var SRCH_NEARPOI_LIMIT = 10000;

/**
 * �萔<br>����POI�����̕\������
* @type Number
 */
var SRCH_NEARPOI_ROWS = 100;

/**
 * �萔<br>����POI�����ōi���݂��s��臒l����
* @type Number
 */
var SRCH_NEARPOI_EXT = 50;

/**
 * �萔<br>�f�t�H���g�k�ځi�s���O�{�̎��̏k�ځj
 * @type Number
 */
var DEF_ZOOM = 10;

/**
 * �萔<br>�Г���񌟍��������Ȃ��k�ڔ͈�
* @type Array
 */
var NGZOOM_SRCH_POINT = {min:0, max:5};

/**
 * �萔<br>�Г���񌟍��̌������[�h�ő啶����
 * @type Number
 */
var SP_WORD_MAXLEN = 40;

/**
 * �萔<br>����POI�����������Ȃ��k�ڔ͈�
* @type Array
 */
var NGZOOM_SRCH_NPOI = {min:0, max:5};

/**
 * �萔<br>�|�C���g�\���ύX�������Ȃ��k�ڔ͈�
* @type Array
 */
var NGZOOM_SELECT_POINT = {min:0, max:5};

/**
 * �萔<br>�|�C���g�\���ύX�����P�u���Z�O�v�{�^���ԍ�
 * @type Number
 */
var SP_IDX_KESSANMAE = 3;

/**
 * �萔<br>�|�C���g�\���ύX�����P�u���Z��v�{�^���ԍ�
 * @type Number
 */
var SP_IDX_KESSANGO = 4;

/**
 * �萔<br>�ܓx�o�x�i�x���b�j�����`�F�b�N�p�̐��K�\���p�^�[��
 * @type String
 */
var LL_REG_DMS = /^([0-9]{2,3})\.([0-9]{1,2})\.([0-9]{1,2}\.[0-9]{1,3})$/;

/**
 * �萔<br>�ܓx�o�x�i10�i�j�����`�F�b�N�p�̐��K�\���p�^�[��
 * @type String
 */
var LL_REG_DEG = /^([0-9]{2,3}\.[0-9]{1,})$/;

/**
 * �萔<br>�ܓx�o�x�i�~���b�j�����`�F�b�N�p�̐��K�\���p�^�[��
 * @type String
 */
var LL_REG_MS = /^[0-9]{8,9}$/;

/**
 * �萔<br>�s���{������
 * @type Array
 */
var TOD_NAME = {
'01':'�k�C��',
'02':'�X��',
'03':'��茧',
'04':'�{�錧',
'05':'�H�c��',
'06':'�R�`��',
'07':'������',
'08':'��錧',
'09':'�Ȗ،�',
'10':'�Q�n��',
'11':'��ʌ�',
'12':'��t��',
'13':'�����s',
'14':'�_�ސ쌧',
'15':'�V����',
'16':'�x�R��',
'17':'�ΐ쌧',
'18':'���䌧',
'19':'�R����',
'20':'���쌧',
'21':'�򕌌�',
'22':'�É���',
'23':'���m��',
'24':'�O�d��',
'25':'���ꌧ',
'26':'���s�{',
'27':'���{',
'28':'���Ɍ�',
'29':'�ޗǌ�',
'30':'�a�̎R��',
'31':'���挧',
'32':'������',
'33':'���R��',
'34':'�L����',
'35':'�R����',
'36':'������',
'37':'���쌧',
'38':'���Q��',
'39':'���m��',
'40':'������',
'41':'���ꌧ',
'42':'���茧',
'43':'�F�{��',
'44':'�啪��',
'45':'�{�茧',
'46':'��������',
'47':'���ꌧ'
};

/**
 * �萔<br>�s���摜Offset(y)
 * @type Array
 */
var PIN_IMG_OFFSET_Y = {
'2':45,
'3':90,
'4':135,
'5':180,
'6':225,
'7':270,
'8':315,
'9':360,
'10':405,
'11':450
};

/**
 * �萔<br>���{�̓y�͈�
 * @type Array
 */
var JPNAREA = {
minlat: 20.4205556,
minlon: 122.9330556,
maxlat: 45.5552778,
maxlon: 153.9902778
};

/**
 * �萔<br>���ݒn�擾�֐��̃p�����[�^�l
 * @type Array
 */
var GPS_PARAM = {
waitTime: 0,
expire: 30,
datum: 1
};

/**
 * �萔<br>���s���x�im/min�j
 * @type Number
 */
var WALK_SPEED = (4.8 * 1000 / 60);

/**
 * �萔<br>�n�_�}�[�J�[��Zindex�l
 * @type Number
 */
var POINT_MARKER_ZINDEX = 100;

/**
 * �萔<br>�n�_�}�[�J�[��offset�ix�����j
 * @type Number
 */
var POINT_MARKER_OFFSET_X = -1;

/**
 * �萔<br>�n�_�}�[�J�[��offset�iy�����j
 * @type Number
 */
var POINT_MARKER_OFFSET_Y = -35;

/**
 * �萔<br>���s�҃��[�g���������̏��(5 or 10)
 * @type Number
 */
var WALK_MAX_DIST = 10;

/**
 * �萔<br>�����q�o�^�������Ȃ��k�ڔ͈�
* @type Array
 */
var NGZOOM_PSPECT_CUST = {min:0, max:12};

/**
 * �萔<br>�s���A�C�R���������Offset�i�n�}�k�ڌ���Ŏg�p�j
* @type Number
 */
var PIN_OFFSET_LAT = 0.0065505;

/**
 * ���b�Z�[�W�F�E���R�[�h������
 * @type String
 */
var MSG_ERR_STAFFCD_EMPTY = "�E���R�[�h����͂��Ă��������B";

/**
 * ���b�Z�[�W�F�������[�h������
 * @type String
 */
var MSG_ERR_WORD_EMPTY = "�������[�h����͂��Ă��������B";

/**
 * ���b�Z�[�W�F�Г���񌟍��̌������[�h�������G���[
 * @type String
 */
var MSG_ERR_WORD_LEN = "�������[�h���������܂��B\n40�����ȓ��œ��͂��Ă��������B";

/**
 * ���b�Z�[�W�F�Г���񌟍��̌������[�h������G���[�i�S�p�ȊO�j
 * @type String
 */
var MSG_ERR_WORD_MB = "�������[�h�ɔ��p�������܂܂�Ă��܂��B\n�S�p�œ��͂��Ă��������B";

/**
 * ���b�Z�[�W�F���{�̓y�O
 * @type String
 */
var MSG_ERR_LL_OUT = "���͂��ꂽ�ܓx�o�x�����{�̓y�͈͓̔��ł͂���܂���B\n���{�̓y���̈ܓx�o�x����͂��Ă��������B";

/**
 * ���b�Z�[�W�F�Г���񌟍��������Ȃ��k��
 * @type String
 */
var MSG_ERR_SRCH_POINT_NGZOOM = "���݂̏k�ڂł́A�Г���񌟍��͗��p�ł��܂���B\n�n�}���Y�[���C�������Ă��炲���p���������B";

/**
 * ���b�Z�[�W�F����POI�����������Ȃ��k��
 * @type String
 */
var MSG_ERR_SRCH_NPOI_NGZOOM = "���݂̏k�ڂł́A���ӂ���̌����͗��p�ł��܂���B\n�n�}���Y�[���C�������Ă��炲���p���������B";

/**
 * ���b�Z�[�W�F�|�C���g�\���ύX�������Ȃ��k��
 * @type String
 */
var MSG_ERR_SELECT_POINT_NGZOOM = "���݂̏k�ڂł́A�|�C���g�\���ύX�͗��p�ł��܂���B\n�n�}���Y�[���C�������Ă��炲���p���������B";

/**
 * ���b�Z�[�W�F�|�C���g�\���ύX�ŏ�����I�����Ă��Ȃ�
 * @type String
 */
var MSG_ERR_SELECT_POINT_NOSEL = "������I�����Ă��������B";

/**
 * ���b�Z�[�W�F�|�C���g�\���ύX�ŏ����P���ׂ�I�����Ă��Ȃ�
 * @type String
 */
var MSG_ERR_SELECT_POINT_NODTL = "�u�S���v�u���_��v�u��ۂ̂݁v�u�������v�̂����ꂩ��I�����Ă��������B";

/**
 * ���b�Z�[�W�F�\���ʒu�C���̎��s�m�F
 * @type String
 */
var MSG_CONF_CHGP = "�Y���|�C���g�̕\���ʒu���C�����܂��B\n��낵���ł����H";

/**
 * ���b�Z�[�W�F�\���ʒu�C���s��
 * @type String
 */
var MSG_ERR_CHGP_NG = "���̃s���̕\���ʒu�͕ύX�ł��܂���B";

/**
 * ���b�Z�[�W�F������
 * @type String
 */
var MSG_INF_SEARCH_PROCESSING = "������...";

/**
 * ���b�Z�[�W�F�t���[���[�h�����̌��ʂ��O��
 * @type String
 */
var MSG_ALERT_NODATA = "�Y���f�[�^������܂���B";

/**
 * ���b�Z�[�W�F�|�C���g�\���ύX�����P���R�ȏ�I�����悤�Ƃ���
 * @type String
 */
var MSG_ALERT_SPCOND_LIMIT = "�I���ł��鍀�ڂ͂Q�܂łł��B";

/**
 * ���b�Z�[�W�F�x�ЃR�[�h������
 * @type String
 */
var MSG_ERR_SISYA_EMPTY = "�x�ЃR�[�h����͂��Ă��������B";

/**
 * ���b�Z�[�W�F�@�փR�[�h������
 * @type String
 */
var MSG_ERR_KA_EMPTY = "�@�փR�[�h����͂��Ă��������B";

/**
 * ���b�Z�[�W�F�E���R�[�h������
 * @type String
 */
var MSG_ERR_SYOKUIN_EMPTY = "�E���R�[�h����͂��Ă��������B";

/**
 * ���b�Z�[�W�F�����q�o�^�������Ȃ��k��
 * @type String
 */
var MSG_ERR_MIKOMI_NGZOOM = "���݂̏k�ڂł́A�����q�o�^�͗��p�ł��܂���B\n�n�}���Y�[���C�������Ă��炲���p���������B";

/**
 * ���b�Z�[�W�F�����q�o�^�F�Z���擾�G���[
 * @type String
 */
var MSG_ERR_MIKOMI_ADDR = "���̒n�_�̏Z���͎擾�ł��܂���B";

/**
 * ���b�Z�[�W�F���ݒn�擾���s
 * @type String
 */
var MSG_ERR_LOC_NG = "GPS���猻�ݒn���擾�ł��܂���ł����B\n���Ԃ��󂯂邩�A�ꏊ���ړ����čēx���{���Ă��������B";

/**
 * ���b�Z�[�W�F���ݒn�擾�G���[
 * @type String
 */
var MSG_ERR_LOC_FAIL = "GPS�̎擾�����ŃV�X�e���G���[���������܂����B\n�Ɖ���ɘA�����Ă��������B";

/**
 * ���b�Z�[�W�F�������s
 * @type String
 */
var MSG_ERR_SEARCH_FAIL = "�������s���ɃG���[���������܂����B\n�Ɖ���ɘA�����Ă��������B";

/**
 * ���b�Z�[�W�F�t���[���[�h�����^�C���A�E�g
 * @type String
 */
var MSG_ERR_FW_SEARCH_FAIL = "�������[�h�ɊY�����錏�����������邽�߁A����������ύX���Ă��������B";

/**
 * ���b�Z�[�W�F���[�g�����G���[
 * @type String
 */
var MSG_ERR_ROUTE_FAIL = "���[�g�����Ɏ��s���܂����B\n�ȉ��̌������l�����܂��B����������ύX���Ă��������B\n�@�E�o���n�ƖړI�n�̋�������������i���s�҃��[�g��10Km�ȓ��j\n�@�E�ʍs�ł��Ȃ��n�_���w�肳��Ă���i��F��̏�Ȃǁj";

/**
 * ���b�Z�[�W�F�d�ԃ��[�g�F���s�҃��[�g���Z������ꍇ�̃G���[
 * @type String
 */
var MSG_ERR_TRAIN_WALK_SHORT = "�o���n�܂��͖ړI�n����w�܂ł̋������߂����܂��B\n�o���n�܂��͖ړI�n��ύX���A�ēx�������s���Ă��������B";

/**
 * ���b�Z�[�W�F�d�ԃ��[�g�F���s�҃��[�g����������ꍇ�̃G���[
 * @type String
 */
var MSG_ERR_TRAIN_WALK_LONG = "�o���n�܂��͖ړI�n����w�܂ł̋������������܂��B\n�o���n�܂��͖ړI�n��ύX���A�ēx�������s���Ă��������B";

/**
 * ���b�Z�[�W�F�ړ������\��
 * @type Array
 */
var ISKYORI_MESSAGE = {
	1: "�ړ������i���������j��{kyori}km�ł��B\r\n�������x�Ђ��n�_�A�I�_�Ƃ��Čv�Z���Ă��܂��B",
	9: "�ړ������i���������j��1,000km�ȏ�ł��B\r\n�������x�Ђ��n�_�A�I�_�Ƃ��Čv�Z���Ă��܂��B"
};

/**
 * �n�}�I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapMap = null;

/**
 * �|�C���g�����`���[��MsgInfo�I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapLauncher = null;

/**
 * �n�}�̃v���p�e�B���`���܂��B
 * @type Array
 */
var DmapMapOpt = {
	mapType: ZDC.MAPTYPE_MOBILE
}

/**
 * �n�}�R���g���[���̃v���p�e�B���`���܂��B
 * @type Array
 */
var DmapMapControl = {
	pos: {top: 50, left: 10},
	type: ZDC.CTRL_TYPE_NORMAL
}

/**
 * DmapClassUser�I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapUser;

/**
 * �s����z-index�ő�l��ێ����܂��B
 * @type Number
 */
var DmapZindexMax = 100;

/**
 * DmapClassPinList�I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapPinList;

/**
 * �ڍ׏��ꗗ�̏�ԁi�ʏ�^�ȈՁj��ێ����܂��B
 * @type Boolean
 */
var DmapPinListSimple = false;

/**
 * �O���[�v�s���ꗗ�E�B�W�F�b�g�̃I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapPinSelect;

/**
 * �\���ʒu�C�����[�h���ǂ����̏�Ԃ�ێ����܂��B
 * @type Boolean
 */
var DmapMovePinMode = false;

/**
 * �s�����h���b�O�����ǂ����̏�Ԃ�ێ����܂��B
 * @type Boolean
 */
var DmapPinDragging = false;

/**
 * �\���ʒu�C���Ńh���b�O����Pin�I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapMovePin = null;

/**
 * �E�N���b�N���[�h��ێ����܂��B�i1�F�����q�o�^�A2�F���[�g�����j
 * @type Number 
 */
var DmapRightClickMode = 1;

/**
 * �u�Г���񌟍��v�̏�Ԃ�ێ����܂��B
 * @type Boolean
 */
var DmapSrchPointOn = false;

/**
 * �u�t���[���[�h�����v�̏�Ԃ�ێ����܂��B
 * @type Boolean
 */
var DmapSrchFWOn = false;

/**
 * POI�����̌��ʃI�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapSrchFWPoiResult = null;

/**
 * �����ʒu�}�[�J�[��ێ����܂��B
 * @type Object
 */
var DmapSearchMarker = null;

/**
 * ���ݒn�}�[�J�[��ێ����܂��B
 * @type Object
 */
var DmapLocationMarker = null;

/**
 * �����x�Ѓs����ێ����܂��B
 * @type Object
 */
var DmapSyozokuPin = null;

/**
 * �����x�Ѓs�����̂�ێ����܂��B
 * @type Object
 */
var DmapSyozokuPinNm = null;

/**
 * �n�}�C�x���g�L���t���O��ێ����܂��B
 * @type Boolean
 */
var DmapMapEventEnable = true;

/**
 * ���������[�h��ێ����܂��B
 * @type String
 */
var DmapDisableMode = '';

/**
 * �u�����q�o�^�v�����o���E�B�W�F�b�g�̃I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapMikomiKyaku = null;

/**
 * ���[�g�����I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapRouteSearch = null;

/**
 * �ړ������\����Polyline�I�u�W�F�N�g��ێ����܂��B
 * @type Object
 */
var DmapIdoKyori = null;

/**
 * �_�C�A���O�h���b�O�p�̏���ێ����܂��B
 * @type Array
 */
var DmapDlgDrag = {
	elm: null,
	flag: false,
	x: 0,
	y: 0
};

/**
 * �����[�h���̏k�ڂ�ێ����܂��B
 * @type Number
 */
var DmapMapReloadScale = -1;

