<?php
// ------------------------------------------------------------
// 2010/04/19 Y.Matsukawa	脆弱性対策（logディレクトリ移動）
// 2011/03/10 Y.Matsukawa	スマートフォン版（smt）追加
// 2011/11/08 Y.Matsukawa	PC2.0対応
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
