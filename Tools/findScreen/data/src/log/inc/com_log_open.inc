<?php
// ------------------------------------------------------------
// 2010/04/19 Y.Matsukawa	�Ǝ㐫�΍�ilog�f�B���N�g���ړ��j
// 2011/03/10 Y.Matsukawa	�X�}�[�g�t�H���Łismt�j�ǉ�
// 2011/11/08 Y.Matsukawa	PC2.0�Ή�
// ------------------------------------------------------------
switch($LOG_MODE) {
	case 'PC2':		// add 2011/11/08 Y.Matsukawa
		include ('/home/emap/src/log/inc/com_log_open.inc.pc2');
		break;
	// add 2011/03/10 Y.Matsukawa [
	case 'SMT':
		include ('/home/emap/src/log/inc/com_log_open.inc.smt');
		break;
	// add 2011/03/10 Y.Matsukawa ]
	case "MOBILE":
		//include ('/home/emap/httpd/log/inc/com_log_open.inc.mobile');		mod 2010/04/19 Y.Matsukawa
		include ('/home/emap/src/log/inc/com_log_open.inc.mobile');
		break;
	case "PC":
	default:
		//include ('/home/emap/httpd/log/inc/com_log_open.inc.pc');		mod 2010/04/19 Y.Matsukawa
		include ('/home/emap/src/log/inc/com_log_open.inc.pc');
		break;
	case "ASP":
		//include ('/home/emap/httpd/log/inc/com_log_open.inc.asp');		mod 2010/04/19 Y.Matsukawa
		include ('/home/emap/src/log/inc/com_log_open.inc.asp');
		break;
}
?>