<?php
/*========================================================*/
// ¹¹¿·ÍúÎò
// 2007/05/22 Y.Matsukawa	HTML¥¿¥°¥Á¥§¥Ã¥¯ÄÉ²Ã¡ÊValidHtmlTag¡Ë
// 2007/06/12 Y.Matsukawa	½èÍý¥Õ¥í¡¼ÊÑ¹¹¡Ê³ÎÇ§²èÌÌÄÉ²Ã¡Ë
// 2007/06/14 Y.Matsukawa	HTML_LNK_FLG¤òHTML_TAG_FLG¤ËÀÚ¤êÂØ¤¨¡Ê¥³¥á¥ó¥È½¤Àµ¤Î¤ß¡Ë
// 2007/08/13 Y.Matsukawa	IzonSearch¡§È¾³Ñ¥«¥Êº®¤¸¤ê¤Î¾ì¹ç¤Ë¥Á¥§¥Ã¥¯·ë²Ì¤¬ÉÔÀµ¤Ë¤Ê¤ë
// 2007/08/15 Y.Matsukawa	ValidKigou¡§¶Ø»ßµ­¹æ¤Ë¡Ö`¡×(¥Ð¥Ã¥¯¥¯¥©¡¼¥È)¤òÄÉ²Ã
// 2007/09/11 K.Masuda		ValidDate:Ç¯¤Î²¼¸Â¤ò2000->1970¤ËÊÑ¹¹¡Ê¥¨¥é¡¼¥á¥Ã¥»¡¼¥¸´Þ¤ß¡Ë
// 2009/04/15 Y.Matsukawa	mselectaddr.cgi¤Ç¥Ñ¥é¥á¡¼¥¿¥¨¥é¡¼¤Ë¤Ê¤ë½»½êÊ¸»úÎó¤ò»öÁ°¤Ë½ü³°
//							¡Êzdc_ctype_kigouÄÉ²Ã¡Ë
// 2009/04/24 Y.Matsukawa	¥Ñ¥Õ¥©¡¼¥Þ¥ó¥¹¥Á¥å¡¼¥Ë¥ó¥°
// 2009/08/11 Y.Matsukawa	IBM³ÈÄ¥Ê¸»ú¡Ê115¶è¡Á119¶è¡Ë¤¬´Þ¤Þ¤ì¤ë¤ÈEUCÊÑ´¹»þ¤ËÊ¸»ú²½¤±¤òµ¯¤³¤¹¤Î¤Ç¡¢»öÁ°¤ËÂ¾¶èÅÀ¤ØÊÑ´¹
// 2009/08/17 Y.Matsukawa	µ¡¼ï°ÍÂ¸Ê¸»úÊÑ´¹µ¡Ç½
// 2009/08/27 Y.Matsukawa	µòÅÀ½Ì¼ÜÀßÄê
/*========================================================*/

define( 'ERR_MAX' , 16 );  // CSV°ì³ç·Ï¥¨¥é¡¼MAX¿ô

// ÆþÎÏ²ÄÇ½¤ÊHTML¥¿¥°
// HTML_TAG_FLG = 0
$TAG_WHITELIST      = array('<br>', '<br/>', '<b>', '</b>');
// HTML_TAG_FLG = 1
$RICH_TAG_WHITELIST = array('<a ', '</a>', '<img ', '<br>', '<br/>', '<b>', '</b>');

// ¢¨Ëè²óÁ´Ê¸»úÃÖ´¹½èÍý¤ò¹Ô¤¦¤Î¤Ï½èÍý»þ´Ö¤¬¤«¤«¤ê¤¹¤®¤ë¤Î¤ÇNG
//// IBM³ÈÄ¥Ê¸»ú¡Ê115¡Á119¶è¡ËÊÑ´¹¥Æ¡¼¥Ö¥ë			add 2009/08/11 Y.Matsukawa
//$IBMEX_CONVERT_FR[] = "\xFA\x40";	$IBMEX_CONVERT_TO[] = "\xEE\xEF";	// i	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x41";	$IBMEX_CONVERT_TO[] = "\xEE\xF0";	// ii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x42";	$IBMEX_CONVERT_TO[] = "\xEE\xF1";	// iii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x43";	$IBMEX_CONVERT_TO[] = "\xEE\xF2";	// iv	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x44";	$IBMEX_CONVERT_TO[] = "\xEE\xF3";	// v	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x45";	$IBMEX_CONVERT_TO[] = "\xEE\xF4";	// vi	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x46";	$IBMEX_CONVERT_TO[] = "\xEE\xF5";	// vii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x47";	$IBMEX_CONVERT_TO[] = "\xEE\xF6";	// viii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x48";	$IBMEX_CONVERT_TO[] = "\xEE\xF7";	// ix	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x49";	$IBMEX_CONVERT_TO[] = "\xEE\xF8";	// x	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
//$IBMEX_CONVERT_FR[] = "\xFA\x4A";	$IBMEX_CONVERT_TO[] = "\x87\x54";	// ­µ
//$IBMEX_CONVERT_FR[] = "\xFA\x4B";	$IBMEX_CONVERT_TO[] = "\x87\x55";	// ­¶
//$IBMEX_CONVERT_FR[] = "\xFA\x4C";	$IBMEX_CONVERT_TO[] = "\x87\x56";	// ­·
//$IBMEX_CONVERT_FR[] = "\xFA\x4D";	$IBMEX_CONVERT_TO[] = "\x87\x57";	// ­¸
//$IBMEX_CONVERT_FR[] = "\xFA\x4E";	$IBMEX_CONVERT_TO[] = "\x87\x58";	// ­¹
//$IBMEX_CONVERT_FR[] = "\xFA\x4F";	$IBMEX_CONVERT_TO[] = "\x87\x59";	// ­º
//$IBMEX_CONVERT_FR[] = "\xFA\x50";	$IBMEX_CONVERT_TO[] = "\x87\x5A";	// ­»
//$IBMEX_CONVERT_FR[] = "\xFA\x51";	$IBMEX_CONVERT_TO[] = "\x87\x5B";	// ­¼
//$IBMEX_CONVERT_FR[] = "\xFA\x52";	$IBMEX_CONVERT_TO[] = "\x87\x5C";	// ­½
//$IBMEX_CONVERT_FR[] = "\xFA\x53";	$IBMEX_CONVERT_TO[] = "\x87\x5D";	// ­¾
//$IBMEX_CONVERT_FR[] = "\xFA\x54";	$IBMEX_CONVERT_TO[] = "\xEE\xF9";	// ¢Ì
//$IBMEX_CONVERT_FR[] = "\xFA\x55";	$IBMEX_CONVERT_TO[] = "\xEE\xFA";	// üü
//$IBMEX_CONVERT_FR[] = "\xFA\x56";	$IBMEX_CONVERT_TO[] = "\xEE\xFB";	// üý
//$IBMEX_CONVERT_FR[] = "\xFA\x57";	$IBMEX_CONVERT_TO[] = "\xEE\xFC";	// üþ
//$IBMEX_CONVERT_FR[] = "\xFA\x58";	$IBMEX_CONVERT_TO[] = "\x87\x8A";	// ­ê
//$IBMEX_CONVERT_FR[] = "\xFA\x59";	$IBMEX_CONVERT_TO[] = "\x87\x82";	// ­â
//$IBMEX_CONVERT_FR[] = "\xFA\x5A";	$IBMEX_CONVERT_TO[] = "\x87\x84";	// ­ä
//$IBMEX_CONVERT_FR[] = "\xFA\x5B";	$IBMEX_CONVERT_TO[] = "\x87\x9A";	// ¢è
//$IBMEX_CONVERT_FR[] = "\xFA\x5C";	$IBMEX_CONVERT_TO[] = "\xED\x40";	// ù¡
//$IBMEX_CONVERT_FR[] = "\xFA\x5D";	$IBMEX_CONVERT_TO[] = "\xED\x41";	// ù¢
//$IBMEX_CONVERT_FR[] = "\xFA\x5E";	$IBMEX_CONVERT_TO[] = "\xED\x42";	// ù£
//$IBMEX_CONVERT_FR[] = "\xFA\x5F";	$IBMEX_CONVERT_TO[] = "\xED\x43";	// ù¤
//$IBMEX_CONVERT_FR[] = "\xFA\x60";	$IBMEX_CONVERT_TO[] = "\xED\x44";	// ù¥
//$IBMEX_CONVERT_FR[] = "\xFA\x61";	$IBMEX_CONVERT_TO[] = "\xED\x45";	// ù¦
//$IBMEX_CONVERT_FR[] = "\xFA\x62";	$IBMEX_CONVERT_TO[] = "\xED\x46";	// ù§
//$IBMEX_CONVERT_FR[] = "\xFA\x63";	$IBMEX_CONVERT_TO[] = "\xED\x47";	// ù¨
//$IBMEX_CONVERT_FR[] = "\xFA\x64";	$IBMEX_CONVERT_TO[] = "\xED\x48";	// ù©
//$IBMEX_CONVERT_FR[] = "\xFA\x65";	$IBMEX_CONVERT_TO[] = "\xED\x49";	// ùª
//$IBMEX_CONVERT_FR[] = "\xFA\x66";	$IBMEX_CONVERT_TO[] = "\xED\x4A";	// ù«
//$IBMEX_CONVERT_FR[] = "\xFA\x67";	$IBMEX_CONVERT_TO[] = "\xED\x4B";	// ù¬
//$IBMEX_CONVERT_FR[] = "\xFA\x68";	$IBMEX_CONVERT_TO[] = "\xED\x4C";	// ù­
//$IBMEX_CONVERT_FR[] = "\xFA\x69";	$IBMEX_CONVERT_TO[] = "\xED\x4D";	// ù®
//$IBMEX_CONVERT_FR[] = "\xFA\x6A";	$IBMEX_CONVERT_TO[] = "\xED\x4E";	// ù¯
//$IBMEX_CONVERT_FR[] = "\xFA\x6B";	$IBMEX_CONVERT_TO[] = "\xED\x4F";	// ù°
//$IBMEX_CONVERT_FR[] = "\xFA\x6C";	$IBMEX_CONVERT_TO[] = "\xED\x50";	// ù±
//$IBMEX_CONVERT_FR[] = "\xFA\x6D";	$IBMEX_CONVERT_TO[] = "\xED\x51";	// ù²
//$IBMEX_CONVERT_FR[] = "\xFA\x6E";	$IBMEX_CONVERT_TO[] = "\xED\x52";	// ù³
//$IBMEX_CONVERT_FR[] = "\xFA\x6F";	$IBMEX_CONVERT_TO[] = "\xED\x53";	// ù´
//$IBMEX_CONVERT_FR[] = "\xFA\x70";	$IBMEX_CONVERT_TO[] = "\xED\x54";	// ùµ
//$IBMEX_CONVERT_FR[] = "\xFA\x71";	$IBMEX_CONVERT_TO[] = "\xED\x55";	// ù¶
//$IBMEX_CONVERT_FR[] = "\xFA\x72";	$IBMEX_CONVERT_TO[] = "\xED\x56";	// ù·
//$IBMEX_CONVERT_FR[] = "\xFA\x73";	$IBMEX_CONVERT_TO[] = "\xED\x57";	// ù¸
//$IBMEX_CONVERT_FR[] = "\xFA\x74";	$IBMEX_CONVERT_TO[] = "\xED\x58";	// ù¹
//$IBMEX_CONVERT_FR[] = "\xFA\x75";	$IBMEX_CONVERT_TO[] = "\xED\x59";	// ùº
//$IBMEX_CONVERT_FR[] = "\xFA\x76";	$IBMEX_CONVERT_TO[] = "\xED\x5A";	// ù»
//$IBMEX_CONVERT_FR[] = "\xFA\x77";	$IBMEX_CONVERT_TO[] = "\xED\x5B";	// ù¼
//$IBMEX_CONVERT_FR[] = "\xFA\x78";	$IBMEX_CONVERT_TO[] = "\xED\x5C";	// ù½
//$IBMEX_CONVERT_FR[] = "\xFA\x79";	$IBMEX_CONVERT_TO[] = "\xED\x5D";	// ù¾
//$IBMEX_CONVERT_FR[] = "\xFA\x7A";	$IBMEX_CONVERT_TO[] = "\xED\x5E";	// ù¿
//$IBMEX_CONVERT_FR[] = "\xFA\x7B";	$IBMEX_CONVERT_TO[] = "\xED\x5F";	// ùÀ
//$IBMEX_CONVERT_FR[] = "\xFA\x7C";	$IBMEX_CONVERT_TO[] = "\xED\x60";	// ùÁ
//$IBMEX_CONVERT_FR[] = "\xFA\x7D";	$IBMEX_CONVERT_TO[] = "\xED\x61";	// ùÂ
//$IBMEX_CONVERT_FR[] = "\xFA\x7E";	$IBMEX_CONVERT_TO[] = "\xED\x62";	// ùÃ
//$IBMEX_CONVERT_FR[] = "\xFA\x80";	$IBMEX_CONVERT_TO[] = "\xED\x63";	// ùÄ
//$IBMEX_CONVERT_FR[] = "\xFA\x81";	$IBMEX_CONVERT_TO[] = "\xED\x64";	// ùÅ
//$IBMEX_CONVERT_FR[] = "\xFA\x82";	$IBMEX_CONVERT_TO[] = "\xED\x65";	// ùÆ
//$IBMEX_CONVERT_FR[] = "\xFA\x83";	$IBMEX_CONVERT_TO[] = "\xED\x66";	// ùÇ
//$IBMEX_CONVERT_FR[] = "\xFA\x84";	$IBMEX_CONVERT_TO[] = "\xED\x67";	// ùÈ
//$IBMEX_CONVERT_FR[] = "\xFA\x85";	$IBMEX_CONVERT_TO[] = "\xED\x68";	// ùÉ
//$IBMEX_CONVERT_FR[] = "\xFA\x86";	$IBMEX_CONVERT_TO[] = "\xED\x69";	// ùÊ
//$IBMEX_CONVERT_FR[] = "\xFA\x87";	$IBMEX_CONVERT_TO[] = "\xED\x6A";	// ùË
//$IBMEX_CONVERT_FR[] = "\xFA\x88";	$IBMEX_CONVERT_TO[] = "\xED\x6B";	// ùÌ
//$IBMEX_CONVERT_FR[] = "\xFA\x89";	$IBMEX_CONVERT_TO[] = "\xED\x6C";	// ùÍ
//$IBMEX_CONVERT_FR[] = "\xFA\x8A";	$IBMEX_CONVERT_TO[] = "\xED\x6D";	// ùÎ
//$IBMEX_CONVERT_FR[] = "\xFA\x8B";	$IBMEX_CONVERT_TO[] = "\xED\x6E";	// ùÏ
//$IBMEX_CONVERT_FR[] = "\xFA\x8C";	$IBMEX_CONVERT_TO[] = "\xED\x6F";	// ùÐ
//$IBMEX_CONVERT_FR[] = "\xFA\x8D";	$IBMEX_CONVERT_TO[] = "\xED\x70";	// ùÑ
//$IBMEX_CONVERT_FR[] = "\xFA\x8E";	$IBMEX_CONVERT_TO[] = "\xED\x71";	// ùÒ
//$IBMEX_CONVERT_FR[] = "\xFA\x8F";	$IBMEX_CONVERT_TO[] = "\xED\x72";	// ùÓ
//$IBMEX_CONVERT_FR[] = "\xFA\x90";	$IBMEX_CONVERT_TO[] = "\xED\x73";	// ùÔ
//$IBMEX_CONVERT_FR[] = "\xFA\x91";	$IBMEX_CONVERT_TO[] = "\xED\x74";	// ùÕ
//$IBMEX_CONVERT_FR[] = "\xFA\x92";	$IBMEX_CONVERT_TO[] = "\xED\x75";	// ùÖ
//$IBMEX_CONVERT_FR[] = "\xFA\x93";	$IBMEX_CONVERT_TO[] = "\xED\x76";	// ù×
//$IBMEX_CONVERT_FR[] = "\xFA\x94";	$IBMEX_CONVERT_TO[] = "\xED\x77";	// ùØ
//$IBMEX_CONVERT_FR[] = "\xFA\x95";	$IBMEX_CONVERT_TO[] = "\xED\x78";	// ùÙ
//$IBMEX_CONVERT_FR[] = "\xFA\x96";	$IBMEX_CONVERT_TO[] = "\xED\x79";	// ùÚ
//$IBMEX_CONVERT_FR[] = "\xFA\x97";	$IBMEX_CONVERT_TO[] = "\xED\x7A";	// ùÛ
//$IBMEX_CONVERT_FR[] = "\xFA\x98";	$IBMEX_CONVERT_TO[] = "\xED\x7B";	// ùÜ
//$IBMEX_CONVERT_FR[] = "\xFA\x99";	$IBMEX_CONVERT_TO[] = "\xED\x7C";	// ùÝ
//$IBMEX_CONVERT_FR[] = "\xFA\x9A";	$IBMEX_CONVERT_TO[] = "\xED\x7D";	// ùÞ
//$IBMEX_CONVERT_FR[] = "\xFA\x9B";	$IBMEX_CONVERT_TO[] = "\xED\x7E";	// ùß
//$IBMEX_CONVERT_FR[] = "\xFA\x9C";	$IBMEX_CONVERT_TO[] = "\xED\x80";	// ùà
//$IBMEX_CONVERT_FR[] = "\xFA\x9D";	$IBMEX_CONVERT_TO[] = "\xED\x81";	// ùá
//$IBMEX_CONVERT_FR[] = "\xFA\x9E";	$IBMEX_CONVERT_TO[] = "\xED\x82";	// ùâ
//$IBMEX_CONVERT_FR[] = "\xFA\x9F";	$IBMEX_CONVERT_TO[] = "\xED\x83";	// ùã
//$IBMEX_CONVERT_FR[] = "\xFA\xA0";	$IBMEX_CONVERT_TO[] = "\xED\x84";	// ùä
//$IBMEX_CONVERT_FR[] = "\xFA\xA1";	$IBMEX_CONVERT_TO[] = "\xED\x85";	// ùå
//$IBMEX_CONVERT_FR[] = "\xFA\xA2";	$IBMEX_CONVERT_TO[] = "\xED\x86";	// ùæ
//$IBMEX_CONVERT_FR[] = "\xFA\xA3";	$IBMEX_CONVERT_TO[] = "\xED\x87";	// ùç
//$IBMEX_CONVERT_FR[] = "\xFA\xA4";	$IBMEX_CONVERT_TO[] = "\xED\x88";	// ùè
//$IBMEX_CONVERT_FR[] = "\xFA\xA5";	$IBMEX_CONVERT_TO[] = "\xED\x89";	// ùé
//$IBMEX_CONVERT_FR[] = "\xFA\xA6";	$IBMEX_CONVERT_TO[] = "\xED\x8A";	// ùê
//$IBMEX_CONVERT_FR[] = "\xFA\xA7";	$IBMEX_CONVERT_TO[] = "\xED\x8B";	// ùë
//$IBMEX_CONVERT_FR[] = "\xFA\xA8";	$IBMEX_CONVERT_TO[] = "\xED\x8C";	// ùì
//$IBMEX_CONVERT_FR[] = "\xFA\xA9";	$IBMEX_CONVERT_TO[] = "\xED\x8D";	// ùí
//$IBMEX_CONVERT_FR[] = "\xFA\xAA";	$IBMEX_CONVERT_TO[] = "\xED\x8E";	// ùî
//$IBMEX_CONVERT_FR[] = "\xFA\xAB";	$IBMEX_CONVERT_TO[] = "\xED\x8F";	// ùï
//$IBMEX_CONVERT_FR[] = "\xFA\xAC";	$IBMEX_CONVERT_TO[] = "\xED\x90";	// ùð
//$IBMEX_CONVERT_FR[] = "\xFA\xAD";	$IBMEX_CONVERT_TO[] = "\xED\x91";	// ùñ
//$IBMEX_CONVERT_FR[] = "\xFA\xAE";	$IBMEX_CONVERT_TO[] = "\xED\x92";	// ùò
//$IBMEX_CONVERT_FR[] = "\xFA\xAF";	$IBMEX_CONVERT_TO[] = "\xED\x93";	// ùó
//$IBMEX_CONVERT_FR[] = "\xFA\xB0";	$IBMEX_CONVERT_TO[] = "\xED\x94";	// ùô
//$IBMEX_CONVERT_FR[] = "\xFA\xB1";	$IBMEX_CONVERT_TO[] = "\xED\x95";	// ùõ
//$IBMEX_CONVERT_FR[] = "\xFA\xB2";	$IBMEX_CONVERT_TO[] = "\xED\x96";	// ùö
//$IBMEX_CONVERT_FR[] = "\xFA\xB3";	$IBMEX_CONVERT_TO[] = "\xED\x97";	// ù÷
//$IBMEX_CONVERT_FR[] = "\xFA\xB4";	$IBMEX_CONVERT_TO[] = "\xED\x98";	// ùø
//$IBMEX_CONVERT_FR[] = "\xFA\xB5";	$IBMEX_CONVERT_TO[] = "\xED\x99";	// ùù
//$IBMEX_CONVERT_FR[] = "\xFA\xB6";	$IBMEX_CONVERT_TO[] = "\xED\x9A";	// ùú
//$IBMEX_CONVERT_FR[] = "\xFA\xB7";	$IBMEX_CONVERT_TO[] = "\xED\x9B";	// ùû
//$IBMEX_CONVERT_FR[] = "\xFA\xB8";	$IBMEX_CONVERT_TO[] = "\xED\x9C";	// ùü
//$IBMEX_CONVERT_FR[] = "\xFA\xB9";	$IBMEX_CONVERT_TO[] = "\xED\x9D";	// ùý
//$IBMEX_CONVERT_FR[] = "\xFA\xBA";	$IBMEX_CONVERT_TO[] = "\xED\x9E";	// ùþ
//$IBMEX_CONVERT_FR[] = "\xFA\xBB";	$IBMEX_CONVERT_TO[] = "\xED\x9F";	// ú¡
//$IBMEX_CONVERT_FR[] = "\xFA\xBC";	$IBMEX_CONVERT_TO[] = "\xED\xA0";	// ú¢
//$IBMEX_CONVERT_FR[] = "\xFA\xBD";	$IBMEX_CONVERT_TO[] = "\xED\xA1";	// ú£
//$IBMEX_CONVERT_FR[] = "\xFA\xBE";	$IBMEX_CONVERT_TO[] = "\xED\xA2";	// ú¤
//$IBMEX_CONVERT_FR[] = "\xFA\xBF";	$IBMEX_CONVERT_TO[] = "\xED\xA3";	// ú¥
//$IBMEX_CONVERT_FR[] = "\xFA\xC0";	$IBMEX_CONVERT_TO[] = "\xED\xA4";	// ú¦
//$IBMEX_CONVERT_FR[] = "\xFA\xC1";	$IBMEX_CONVERT_TO[] = "\xED\xA5";	// ú§
//$IBMEX_CONVERT_FR[] = "\xFA\xC2";	$IBMEX_CONVERT_TO[] = "\xED\xA6";	// ú¨
//$IBMEX_CONVERT_FR[] = "\xFA\xC3";	$IBMEX_CONVERT_TO[] = "\xED\xA7";	// ú©
//$IBMEX_CONVERT_FR[] = "\xFA\xC4";	$IBMEX_CONVERT_TO[] = "\xED\xA8";	// úª
//$IBMEX_CONVERT_FR[] = "\xFA\xC5";	$IBMEX_CONVERT_TO[] = "\xED\xA9";	// ú«
//$IBMEX_CONVERT_FR[] = "\xFA\xC6";	$IBMEX_CONVERT_TO[] = "\xED\xAA";	// ú¬
//$IBMEX_CONVERT_FR[] = "\xFA\xC7";	$IBMEX_CONVERT_TO[] = "\xED\xAB";	// ú­
//$IBMEX_CONVERT_FR[] = "\xFA\xC8";	$IBMEX_CONVERT_TO[] = "\xED\xAC";	// ú®
//$IBMEX_CONVERT_FR[] = "\xFA\xC9";	$IBMEX_CONVERT_TO[] = "\xED\xAD";	// ú¯
//$IBMEX_CONVERT_FR[] = "\xFA\xCA";	$IBMEX_CONVERT_TO[] = "\xED\xAE";	// ú°
//$IBMEX_CONVERT_FR[] = "\xFA\xCB";	$IBMEX_CONVERT_TO[] = "\xED\xAF";	// ú±
//$IBMEX_CONVERT_FR[] = "\xFA\xCC";	$IBMEX_CONVERT_TO[] = "\xED\xB0";	// ú²
//$IBMEX_CONVERT_FR[] = "\xFA\xCD";	$IBMEX_CONVERT_TO[] = "\xED\xB1";	// ú³
//$IBMEX_CONVERT_FR[] = "\xFA\xCE";	$IBMEX_CONVERT_TO[] = "\xED\xB2";	// ú´
//$IBMEX_CONVERT_FR[] = "\xFA\xCF";	$IBMEX_CONVERT_TO[] = "\xED\xB3";	// úµ
//$IBMEX_CONVERT_FR[] = "\xFA\xD0";	$IBMEX_CONVERT_TO[] = "\xED\xB4";	// ú¶
//$IBMEX_CONVERT_FR[] = "\xFA\xD1";	$IBMEX_CONVERT_TO[] = "\xED\xB5";	// ú·
//$IBMEX_CONVERT_FR[] = "\xFA\xD2";	$IBMEX_CONVERT_TO[] = "\xED\xB6";	// ú¸
//$IBMEX_CONVERT_FR[] = "\xFA\xD3";	$IBMEX_CONVERT_TO[] = "\xED\xB7";	// ú¹
//$IBMEX_CONVERT_FR[] = "\xFA\xD4";	$IBMEX_CONVERT_TO[] = "\xED\xB8";	// úº
//$IBMEX_CONVERT_FR[] = "\xFA\xD5";	$IBMEX_CONVERT_TO[] = "\xED\xB9";	// ú»
//$IBMEX_CONVERT_FR[] = "\xFA\xD6";	$IBMEX_CONVERT_TO[] = "\xED\xBA";	// ú¼
//$IBMEX_CONVERT_FR[] = "\xFA\xD7";	$IBMEX_CONVERT_TO[] = "\xED\xBB";	// ú½
//$IBMEX_CONVERT_FR[] = "\xFA\xD8";	$IBMEX_CONVERT_TO[] = "\xED\xBC";	// ú¾
//$IBMEX_CONVERT_FR[] = "\xFA\xD9";	$IBMEX_CONVERT_TO[] = "\xED\xBD";	// ú¿
//$IBMEX_CONVERT_FR[] = "\xFA\xDA";	$IBMEX_CONVERT_TO[] = "\xED\xBE";	// úÀ
//$IBMEX_CONVERT_FR[] = "\xFA\xDB";	$IBMEX_CONVERT_TO[] = "\xED\xBF";	// úÁ
//$IBMEX_CONVERT_FR[] = "\xFA\xDC";	$IBMEX_CONVERT_TO[] = "\xED\xC0";	// úÂ
//$IBMEX_CONVERT_FR[] = "\xFA\xDD";	$IBMEX_CONVERT_TO[] = "\xED\xC1";	// úÃ
//$IBMEX_CONVERT_FR[] = "\xFA\xDE";	$IBMEX_CONVERT_TO[] = "\xED\xC2";	// úÄ
//$IBMEX_CONVERT_FR[] = "\xFA\xDF";	$IBMEX_CONVERT_TO[] = "\xED\xC3";	// úÅ
//$IBMEX_CONVERT_FR[] = "\xFA\xE0";	$IBMEX_CONVERT_TO[] = "\xED\xC4";	// úÆ
//$IBMEX_CONVERT_FR[] = "\xFA\xE1";	$IBMEX_CONVERT_TO[] = "\xED\xC5";	// úÇ
//$IBMEX_CONVERT_FR[] = "\xFA\xE2";	$IBMEX_CONVERT_TO[] = "\xED\xC6";	// úÈ
//$IBMEX_CONVERT_FR[] = "\xFA\xE3";	$IBMEX_CONVERT_TO[] = "\xED\xC7";	// úÉ
//$IBMEX_CONVERT_FR[] = "\xFA\xE4";	$IBMEX_CONVERT_TO[] = "\xED\xC8";	// úÊ
//$IBMEX_CONVERT_FR[] = "\xFA\xE5";	$IBMEX_CONVERT_TO[] = "\xED\xC9";	// úË
//$IBMEX_CONVERT_FR[] = "\xFA\xE6";	$IBMEX_CONVERT_TO[] = "\xED\xCA";	// úÌ
//$IBMEX_CONVERT_FR[] = "\xFA\xE7";	$IBMEX_CONVERT_TO[] = "\xED\xCB";	// úÍ
//$IBMEX_CONVERT_FR[] = "\xFA\xE8";	$IBMEX_CONVERT_TO[] = "\xED\xCC";	// úÎ
//$IBMEX_CONVERT_FR[] = "\xFA\xE9";	$IBMEX_CONVERT_TO[] = "\xED\xCD";	// úÏ
//$IBMEX_CONVERT_FR[] = "\xFA\xEA";	$IBMEX_CONVERT_TO[] = "\xED\xCE";	// úÐ
//$IBMEX_CONVERT_FR[] = "\xFA\xEB";	$IBMEX_CONVERT_TO[] = "\xED\xCF";	// úÑ
//$IBMEX_CONVERT_FR[] = "\xFA\xEC";	$IBMEX_CONVERT_TO[] = "\xED\xD0";	// úÒ
//$IBMEX_CONVERT_FR[] = "\xFA\xED";	$IBMEX_CONVERT_TO[] = "\xED\xD1";	// úÓ
//$IBMEX_CONVERT_FR[] = "\xFA\xEE";	$IBMEX_CONVERT_TO[] = "\xED\xD2";	// úÔ
//$IBMEX_CONVERT_FR[] = "\xFA\xEF";	$IBMEX_CONVERT_TO[] = "\xED\xD3";	// úÕ
//$IBMEX_CONVERT_FR[] = "\xFA\xF0";	$IBMEX_CONVERT_TO[] = "\xED\xD4";	// úÖ
//$IBMEX_CONVERT_FR[] = "\xFA\xF1";	$IBMEX_CONVERT_TO[] = "\xED\xD5";	// ú×
//$IBMEX_CONVERT_FR[] = "\xFA\xF2";	$IBMEX_CONVERT_TO[] = "\xED\xD6";	// úØ
//$IBMEX_CONVERT_FR[] = "\xFA\xF3";	$IBMEX_CONVERT_TO[] = "\xED\xD7";	// úÙ
//$IBMEX_CONVERT_FR[] = "\xFA\xF4";	$IBMEX_CONVERT_TO[] = "\xED\xD8";	// úÚ
//$IBMEX_CONVERT_FR[] = "\xFA\xF5";	$IBMEX_CONVERT_TO[] = "\xED\xD9";	// úÛ
//$IBMEX_CONVERT_FR[] = "\xFA\xF6";	$IBMEX_CONVERT_TO[] = "\xED\xDA";	// úÜ
//$IBMEX_CONVERT_FR[] = "\xFA\xF7";	$IBMEX_CONVERT_TO[] = "\xED\xDB";	// úÝ
//$IBMEX_CONVERT_FR[] = "\xFA\xF8";	$IBMEX_CONVERT_TO[] = "\xED\xDC";	// úÞ
//$IBMEX_CONVERT_FR[] = "\xFA\xF9";	$IBMEX_CONVERT_TO[] = "\xED\xDD";	// úß
//$IBMEX_CONVERT_FR[] = "\xFA\xFA";	$IBMEX_CONVERT_TO[] = "\xED\xDE";	// úà
//$IBMEX_CONVERT_FR[] = "\xFA\xFB";	$IBMEX_CONVERT_TO[] = "\xED\xDF";	// úá
//$IBMEX_CONVERT_FR[] = "\xFA\xFC";	$IBMEX_CONVERT_TO[] = "\xED\xE0";	// úâ
//$IBMEX_CONVERT_FR[] = "\xFB\x40";	$IBMEX_CONVERT_TO[] = "\xED\xE1";	// úã
//$IBMEX_CONVERT_FR[] = "\xFB\x41";	$IBMEX_CONVERT_TO[] = "\xED\xE2";	// úä
//$IBMEX_CONVERT_FR[] = "\xFB\x42";	$IBMEX_CONVERT_TO[] = "\xED\xE3";	// úå
//$IBMEX_CONVERT_FR[] = "\xFB\x43";	$IBMEX_CONVERT_TO[] = "\xED\xE4";	// úæ
//$IBMEX_CONVERT_FR[] = "\xFB\x44";	$IBMEX_CONVERT_TO[] = "\xED\xE5";	// úç
//$IBMEX_CONVERT_FR[] = "\xFB\x45";	$IBMEX_CONVERT_TO[] = "\xED\xE6";	// úè
//$IBMEX_CONVERT_FR[] = "\xFB\x46";	$IBMEX_CONVERT_TO[] = "\xED\xE7";	// úé
//$IBMEX_CONVERT_FR[] = "\xFB\x47";	$IBMEX_CONVERT_TO[] = "\xED\xE8";	// úê
//$IBMEX_CONVERT_FR[] = "\xFB\x48";	$IBMEX_CONVERT_TO[] = "\xED\xE9";	// úë
//$IBMEX_CONVERT_FR[] = "\xFB\x49";	$IBMEX_CONVERT_TO[] = "\xED\xEA";	// úì
//$IBMEX_CONVERT_FR[] = "\xFB\x4A";	$IBMEX_CONVERT_TO[] = "\xED\xEB";	// úí
//$IBMEX_CONVERT_FR[] = "\xFB\x4B";	$IBMEX_CONVERT_TO[] = "\xED\xEC";	// úî
//$IBMEX_CONVERT_FR[] = "\xFB\x4C";	$IBMEX_CONVERT_TO[] = "\xED\xED";	// úï
//$IBMEX_CONVERT_FR[] = "\xFB\x4D";	$IBMEX_CONVERT_TO[] = "\xED\xEE";	// úð
//$IBMEX_CONVERT_FR[] = "\xFB\x4E";	$IBMEX_CONVERT_TO[] = "\xED\xEF";	// úñ
//$IBMEX_CONVERT_FR[] = "\xFB\x4F";	$IBMEX_CONVERT_TO[] = "\xED\xF0";	// úò
//$IBMEX_CONVERT_FR[] = "\xFB\x50";	$IBMEX_CONVERT_TO[] = "\xED\xF1";	// úó
//$IBMEX_CONVERT_FR[] = "\xFB\x51";	$IBMEX_CONVERT_TO[] = "\xED\xF2";	// úô
//$IBMEX_CONVERT_FR[] = "\xFB\x52";	$IBMEX_CONVERT_TO[] = "\xED\xF3";	// úõ
//$IBMEX_CONVERT_FR[] = "\xFB\x53";	$IBMEX_CONVERT_TO[] = "\xED\xF4";	// úö
//$IBMEX_CONVERT_FR[] = "\xFB\x54";	$IBMEX_CONVERT_TO[] = "\xED\xF5";	// ú÷
//$IBMEX_CONVERT_FR[] = "\xFB\x55";	$IBMEX_CONVERT_TO[] = "\xED\xF6";	// úø
//$IBMEX_CONVERT_FR[] = "\xFB\x56";	$IBMEX_CONVERT_TO[] = "\xED\xF7";	// úù
//$IBMEX_CONVERT_FR[] = "\xFB\x57";	$IBMEX_CONVERT_TO[] = "\xED\xF8";	// úú
//$IBMEX_CONVERT_FR[] = "\xFB\x58";	$IBMEX_CONVERT_TO[] = "\xED\xF9";	// úû
//$IBMEX_CONVERT_FR[] = "\xFB\x59";	$IBMEX_CONVERT_TO[] = "\xED\xFA";	// úü
//$IBMEX_CONVERT_FR[] = "\xFB\x5A";	$IBMEX_CONVERT_TO[] = "\xED\xFB";	// úý
//$IBMEX_CONVERT_FR[] = "\xFB\x5B";	$IBMEX_CONVERT_TO[] = "\xED\xFC";	// úþ
//$IBMEX_CONVERT_FR[] = "\xFB\x5C";	$IBMEX_CONVERT_TO[] = "\xEE\x40";	// û¡
//$IBMEX_CONVERT_FR[] = "\xFB\x5D";	$IBMEX_CONVERT_TO[] = "\xEE\x41";	// û¢
//$IBMEX_CONVERT_FR[] = "\xFB\x5E";	$IBMEX_CONVERT_TO[] = "\xEE\x42";	// û£
//$IBMEX_CONVERT_FR[] = "\xFB\x5F";	$IBMEX_CONVERT_TO[] = "\xEE\x43";	// û¤
//$IBMEX_CONVERT_FR[] = "\xFB\x60";	$IBMEX_CONVERT_TO[] = "\xEE\x44";	// û¥
//$IBMEX_CONVERT_FR[] = "\xFB\x61";	$IBMEX_CONVERT_TO[] = "\xEE\x45";	// û¦
//$IBMEX_CONVERT_FR[] = "\xFB\x62";	$IBMEX_CONVERT_TO[] = "\xEE\x46";	// û§
//$IBMEX_CONVERT_FR[] = "\xFB\x63";	$IBMEX_CONVERT_TO[] = "\xEE\x47";	// û¨
//$IBMEX_CONVERT_FR[] = "\xFB\x64";	$IBMEX_CONVERT_TO[] = "\xEE\x48";	// û©
//$IBMEX_CONVERT_FR[] = "\xFB\x65";	$IBMEX_CONVERT_TO[] = "\xEE\x49";	// ûª
//$IBMEX_CONVERT_FR[] = "\xFB\x66";	$IBMEX_CONVERT_TO[] = "\xEE\x4A";	// û«
//$IBMEX_CONVERT_FR[] = "\xFB\x67";	$IBMEX_CONVERT_TO[] = "\xEE\x4B";	// û¬
//$IBMEX_CONVERT_FR[] = "\xFB\x68";	$IBMEX_CONVERT_TO[] = "\xEE\x4C";	// û­
//$IBMEX_CONVERT_FR[] = "\xFB\x69";	$IBMEX_CONVERT_TO[] = "\xEE\x4D";	// û®
//$IBMEX_CONVERT_FR[] = "\xFB\x6A";	$IBMEX_CONVERT_TO[] = "\xEE\x4E";	// û¯
//$IBMEX_CONVERT_FR[] = "\xFB\x6B";	$IBMEX_CONVERT_TO[] = "\xEE\x4F";	// û°
//$IBMEX_CONVERT_FR[] = "\xFB\x6C";	$IBMEX_CONVERT_TO[] = "\xEE\x50";	// û±
//$IBMEX_CONVERT_FR[] = "\xFB\x6D";	$IBMEX_CONVERT_TO[] = "\xEE\x51";	// û²
//$IBMEX_CONVERT_FR[] = "\xFB\x6E";	$IBMEX_CONVERT_TO[] = "\xEE\x52";	// û³
//$IBMEX_CONVERT_FR[] = "\xFB\x6F";	$IBMEX_CONVERT_TO[] = "\xEE\x53";	// û´
//$IBMEX_CONVERT_FR[] = "\xFB\x70";	$IBMEX_CONVERT_TO[] = "\xEE\x54";	// ûµ
//$IBMEX_CONVERT_FR[] = "\xFB\x71";	$IBMEX_CONVERT_TO[] = "\xEE\x55";	// û¶
//$IBMEX_CONVERT_FR[] = "\xFB\x72";	$IBMEX_CONVERT_TO[] = "\xEE\x56";	// û·
//$IBMEX_CONVERT_FR[] = "\xFB\x73";	$IBMEX_CONVERT_TO[] = "\xEE\x57";	// û¸
//$IBMEX_CONVERT_FR[] = "\xFB\x74";	$IBMEX_CONVERT_TO[] = "\xEE\x58";	// û¹
//$IBMEX_CONVERT_FR[] = "\xFB\x75";	$IBMEX_CONVERT_TO[] = "\xEE\x59";	// ûº
//$IBMEX_CONVERT_FR[] = "\xFB\x76";	$IBMEX_CONVERT_TO[] = "\xEE\x5A";	// û»
//$IBMEX_CONVERT_FR[] = "\xFB\x77";	$IBMEX_CONVERT_TO[] = "\xEE\x5B";	// û¼
//$IBMEX_CONVERT_FR[] = "\xFB\x78";	$IBMEX_CONVERT_TO[] = "\xEE\x5C";	// û½
//$IBMEX_CONVERT_FR[] = "\xFB\x79";	$IBMEX_CONVERT_TO[] = "\xEE\x5D";	// û¾
//$IBMEX_CONVERT_FR[] = "\xFB\x7A";	$IBMEX_CONVERT_TO[] = "\xEE\x5E";	// û¿
//$IBMEX_CONVERT_FR[] = "\xFB\x7B";	$IBMEX_CONVERT_TO[] = "\xEE\x5F";	// ûÀ
//$IBMEX_CONVERT_FR[] = "\xFB\x7C";	$IBMEX_CONVERT_TO[] = "\xEE\x60";	// ûÁ
//$IBMEX_CONVERT_FR[] = "\xFB\x7D";	$IBMEX_CONVERT_TO[] = "\xEE\x61";	// ûÂ
//$IBMEX_CONVERT_FR[] = "\xFB\x7E";	$IBMEX_CONVERT_TO[] = "\xEE\x62";	// ûÃ
//$IBMEX_CONVERT_FR[] = "\xFB\x80";	$IBMEX_CONVERT_TO[] = "\xEE\x63";	// ûÄ
//$IBMEX_CONVERT_FR[] = "\xFB\x81";	$IBMEX_CONVERT_TO[] = "\xEE\x64";	// ûÅ
//$IBMEX_CONVERT_FR[] = "\xFB\x82";	$IBMEX_CONVERT_TO[] = "\xEE\x65";	// ûÆ
//$IBMEX_CONVERT_FR[] = "\xFB\x83";	$IBMEX_CONVERT_TO[] = "\xEE\x66";	// ûÇ
//$IBMEX_CONVERT_FR[] = "\xFB\x84";	$IBMEX_CONVERT_TO[] = "\xEE\x67";	// ûÈ
//$IBMEX_CONVERT_FR[] = "\xFB\x85";	$IBMEX_CONVERT_TO[] = "\xEE\x68";	// ûÉ
//$IBMEX_CONVERT_FR[] = "\xFB\x86";	$IBMEX_CONVERT_TO[] = "\xEE\x69";	// ûÊ
//$IBMEX_CONVERT_FR[] = "\xFB\x87";	$IBMEX_CONVERT_TO[] = "\xEE\x6A";	// ûË
//$IBMEX_CONVERT_FR[] = "\xFB\x88";	$IBMEX_CONVERT_TO[] = "\xEE\x6B";	// ûÌ
//$IBMEX_CONVERT_FR[] = "\xFB\x89";	$IBMEX_CONVERT_TO[] = "\xEE\x6C";	// ûÍ
//$IBMEX_CONVERT_FR[] = "\xFB\x8A";	$IBMEX_CONVERT_TO[] = "\xEE\x6D";	// ûÎ
//$IBMEX_CONVERT_FR[] = "\xFB\x8B";	$IBMEX_CONVERT_TO[] = "\xEE\x6E";	// ûÏ
//$IBMEX_CONVERT_FR[] = "\xFB\x8C";	$IBMEX_CONVERT_TO[] = "\xEE\x6F";	// ûÐ
//$IBMEX_CONVERT_FR[] = "\xFB\x8D";	$IBMEX_CONVERT_TO[] = "\xEE\x70";	// ûÑ
//$IBMEX_CONVERT_FR[] = "\xFB\x8E";	$IBMEX_CONVERT_TO[] = "\xEE\x71";	// ûÒ
//$IBMEX_CONVERT_FR[] = "\xFB\x8F";	$IBMEX_CONVERT_TO[] = "\xEE\x72";	// ûÓ
//$IBMEX_CONVERT_FR[] = "\xFB\x90";	$IBMEX_CONVERT_TO[] = "\xEE\x73";	// ûÔ
//$IBMEX_CONVERT_FR[] = "\xFB\x91";	$IBMEX_CONVERT_TO[] = "\xEE\x74";	// ûÕ
//$IBMEX_CONVERT_FR[] = "\xFB\x92";	$IBMEX_CONVERT_TO[] = "\xEE\x75";	// ûÖ
//$IBMEX_CONVERT_FR[] = "\xFB\x93";	$IBMEX_CONVERT_TO[] = "\xEE\x76";	// û×
//$IBMEX_CONVERT_FR[] = "\xFB\x94";	$IBMEX_CONVERT_TO[] = "\xEE\x77";	// ûØ
//$IBMEX_CONVERT_FR[] = "\xFB\x95";	$IBMEX_CONVERT_TO[] = "\xEE\x78";	// ûÙ
//$IBMEX_CONVERT_FR[] = "\xFB\x96";	$IBMEX_CONVERT_TO[] = "\xEE\x79";	// ûÚ
//$IBMEX_CONVERT_FR[] = "\xFB\x97";	$IBMEX_CONVERT_TO[] = "\xEE\x7A";	// ûÛ
//$IBMEX_CONVERT_FR[] = "\xFB\x98";	$IBMEX_CONVERT_TO[] = "\xEE\x7B";	// ûÜ
//$IBMEX_CONVERT_FR[] = "\xFB\x99";	$IBMEX_CONVERT_TO[] = "\xEE\x7C";	// ûÝ
//$IBMEX_CONVERT_FR[] = "\xFB\x9A";	$IBMEX_CONVERT_TO[] = "\xEE\x7D";	// ûÞ
//$IBMEX_CONVERT_FR[] = "\xFB\x9B";	$IBMEX_CONVERT_TO[] = "\xEE\x7E";	// ûß
//$IBMEX_CONVERT_FR[] = "\xFB\x9C";	$IBMEX_CONVERT_TO[] = "\xEE\x80";	// ûà
//$IBMEX_CONVERT_FR[] = "\xFB\x9D";	$IBMEX_CONVERT_TO[] = "\xEE\x81";	// ûá
//$IBMEX_CONVERT_FR[] = "\xFB\x9E";	$IBMEX_CONVERT_TO[] = "\xEE\x82";	// ûâ
//$IBMEX_CONVERT_FR[] = "\xFB\x9F";	$IBMEX_CONVERT_TO[] = "\xEE\x83";	// ûã
//$IBMEX_CONVERT_FR[] = "\xFB\xA0";	$IBMEX_CONVERT_TO[] = "\xEE\x84";	// ûä
//$IBMEX_CONVERT_FR[] = "\xFB\xA1";	$IBMEX_CONVERT_TO[] = "\xEE\x85";	// ûå
//$IBMEX_CONVERT_FR[] = "\xFB\xA2";	$IBMEX_CONVERT_TO[] = "\xEE\x86";	// ûæ
//$IBMEX_CONVERT_FR[] = "\xFB\xA3";	$IBMEX_CONVERT_TO[] = "\xEE\x87";	// ûç
//$IBMEX_CONVERT_FR[] = "\xFB\xA4";	$IBMEX_CONVERT_TO[] = "\xEE\x88";	// ûè
//$IBMEX_CONVERT_FR[] = "\xFB\xA5";	$IBMEX_CONVERT_TO[] = "\xEE\x89";	// ûé
//$IBMEX_CONVERT_FR[] = "\xFB\xA6";	$IBMEX_CONVERT_TO[] = "\xEE\x8A";	// ûê
//$IBMEX_CONVERT_FR[] = "\xFB\xA7";	$IBMEX_CONVERT_TO[] = "\xEE\x8B";	// ûë
//$IBMEX_CONVERT_FR[] = "\xFB\xA8";	$IBMEX_CONVERT_TO[] = "\xEE\x8C";	// ûì
//$IBMEX_CONVERT_FR[] = "\xFB\xA9";	$IBMEX_CONVERT_TO[] = "\xEE\x8D";	// ûí
//$IBMEX_CONVERT_FR[] = "\xFB\xAA";	$IBMEX_CONVERT_TO[] = "\xEE\x8E";	// ûî
//$IBMEX_CONVERT_FR[] = "\xFB\xAB";	$IBMEX_CONVERT_TO[] = "\xEE\x8F";	// ûï
//$IBMEX_CONVERT_FR[] = "\xFB\xAC";	$IBMEX_CONVERT_TO[] = "\xEE\x90";	// ûð
//$IBMEX_CONVERT_FR[] = "\xFB\xAD";	$IBMEX_CONVERT_TO[] = "\xEE\x91";	// ûñ
//$IBMEX_CONVERT_FR[] = "\xFB\xAE";	$IBMEX_CONVERT_TO[] = "\xEE\x92";	// ûò
//$IBMEX_CONVERT_FR[] = "\xFB\xAF";	$IBMEX_CONVERT_TO[] = "\xEE\x93";	// ûó
//$IBMEX_CONVERT_FR[] = "\xFB\xB0";	$IBMEX_CONVERT_TO[] = "\xEE\x94";	// ûô
//$IBMEX_CONVERT_FR[] = "\xFB\xB1";	$IBMEX_CONVERT_TO[] = "\xEE\x95";	// ûõ
//$IBMEX_CONVERT_FR[] = "\xFB\xB2";	$IBMEX_CONVERT_TO[] = "\xEE\x96";	// ûö
//$IBMEX_CONVERT_FR[] = "\xFB\xB3";	$IBMEX_CONVERT_TO[] = "\xEE\x97";	// û÷
//$IBMEX_CONVERT_FR[] = "\xFB\xB4";	$IBMEX_CONVERT_TO[] = "\xEE\x98";	// ûø
//$IBMEX_CONVERT_FR[] = "\xFB\xB5";	$IBMEX_CONVERT_TO[] = "\xEE\x99";	// ûù
//$IBMEX_CONVERT_FR[] = "\xFB\xB6";	$IBMEX_CONVERT_TO[] = "\xEE\x9A";	// ûú
//$IBMEX_CONVERT_FR[] = "\xFB\xB7";	$IBMEX_CONVERT_TO[] = "\xEE\x9B";	// ûû
//$IBMEX_CONVERT_FR[] = "\xFB\xB8";	$IBMEX_CONVERT_TO[] = "\xEE\x9C";	// ûü
//$IBMEX_CONVERT_FR[] = "\xFB\xB9";	$IBMEX_CONVERT_TO[] = "\xEE\x9D";	// ûý
//$IBMEX_CONVERT_FR[] = "\xFB\xBA";	$IBMEX_CONVERT_TO[] = "\xEE\x9E";	// ûþ
//$IBMEX_CONVERT_FR[] = "\xFB\xBB";	$IBMEX_CONVERT_TO[] = "\xEE\x9F";	// ü¡
//$IBMEX_CONVERT_FR[] = "\xFB\xBC";	$IBMEX_CONVERT_TO[] = "\xEE\xA0";	// ü¢
//$IBMEX_CONVERT_FR[] = "\xFB\xBD";	$IBMEX_CONVERT_TO[] = "\xEE\xA1";	// ü£
//$IBMEX_CONVERT_FR[] = "\xFB\xBE";	$IBMEX_CONVERT_TO[] = "\xEE\xA2";	// ü¤
//$IBMEX_CONVERT_FR[] = "\xFB\xBF";	$IBMEX_CONVERT_TO[] = "\xEE\xA3";	// ü¥
//$IBMEX_CONVERT_FR[] = "\xFB\xC0";	$IBMEX_CONVERT_TO[] = "\xEE\xA4";	// ü¦
//$IBMEX_CONVERT_FR[] = "\xFB\xC1";	$IBMEX_CONVERT_TO[] = "\xEE\xA5";	// ü§
//$IBMEX_CONVERT_FR[] = "\xFB\xC2";	$IBMEX_CONVERT_TO[] = "\xEE\xA6";	// ü¨
//$IBMEX_CONVERT_FR[] = "\xFB\xC3";	$IBMEX_CONVERT_TO[] = "\xEE\xA7";	// ü©
//$IBMEX_CONVERT_FR[] = "\xFB\xC4";	$IBMEX_CONVERT_TO[] = "\xEE\xA8";	// üª
//$IBMEX_CONVERT_FR[] = "\xFB\xC5";	$IBMEX_CONVERT_TO[] = "\xEE\xA9";	// ü«
//$IBMEX_CONVERT_FR[] = "\xFB\xC6";	$IBMEX_CONVERT_TO[] = "\xEE\xAA";	// ü¬
//$IBMEX_CONVERT_FR[] = "\xFB\xC7";	$IBMEX_CONVERT_TO[] = "\xEE\xAB";	// ü­
//$IBMEX_CONVERT_FR[] = "\xFB\xC8";	$IBMEX_CONVERT_TO[] = "\xEE\xAC";	// ü®
//$IBMEX_CONVERT_FR[] = "\xFB\xC9";	$IBMEX_CONVERT_TO[] = "\xEE\xAD";	// ü¯
//$IBMEX_CONVERT_FR[] = "\xFB\xCA";	$IBMEX_CONVERT_TO[] = "\xEE\xAE";	// ü°
//$IBMEX_CONVERT_FR[] = "\xFB\xCB";	$IBMEX_CONVERT_TO[] = "\xEE\xAF";	// ü±
//$IBMEX_CONVERT_FR[] = "\xFB\xCC";	$IBMEX_CONVERT_TO[] = "\xEE\xB0";	// ü²
//$IBMEX_CONVERT_FR[] = "\xFB\xCD";	$IBMEX_CONVERT_TO[] = "\xEE\xB1";	// ü³
//$IBMEX_CONVERT_FR[] = "\xFB\xCE";	$IBMEX_CONVERT_TO[] = "\xEE\xB2";	// ü´
//$IBMEX_CONVERT_FR[] = "\xFB\xCF";	$IBMEX_CONVERT_TO[] = "\xEE\xB3";	// üµ
//$IBMEX_CONVERT_FR[] = "\xFB\xD0";	$IBMEX_CONVERT_TO[] = "\xEE\xB4";	// ü¶
//$IBMEX_CONVERT_FR[] = "\xFB\xD1";	$IBMEX_CONVERT_TO[] = "\xEE\xB5";	// ü·
//$IBMEX_CONVERT_FR[] = "\xFB\xD2";	$IBMEX_CONVERT_TO[] = "\xEE\xB6";	// ü¸
//$IBMEX_CONVERT_FR[] = "\xFB\xD3";	$IBMEX_CONVERT_TO[] = "\xEE\xB7";	// ü¹
//$IBMEX_CONVERT_FR[] = "\xFB\xD4";	$IBMEX_CONVERT_TO[] = "\xEE\xB8";	// üº
//$IBMEX_CONVERT_FR[] = "\xFB\xD5";	$IBMEX_CONVERT_TO[] = "\xEE\xB9";	// ü»
//$IBMEX_CONVERT_FR[] = "\xFB\xD6";	$IBMEX_CONVERT_TO[] = "\xEE\xBA";	// ü¼
//$IBMEX_CONVERT_FR[] = "\xFB\xD7";	$IBMEX_CONVERT_TO[] = "\xEE\xBB";	// ü½
//$IBMEX_CONVERT_FR[] = "\xFB\xD8";	$IBMEX_CONVERT_TO[] = "\xEE\xBC";	// ü¾
//$IBMEX_CONVERT_FR[] = "\xFB\xD9";	$IBMEX_CONVERT_TO[] = "\xEE\xBD";	// ü¿
//$IBMEX_CONVERT_FR[] = "\xFB\xDA";	$IBMEX_CONVERT_TO[] = "\xEE\xBE";	// üÀ
//$IBMEX_CONVERT_FR[] = "\xFB\xDB";	$IBMEX_CONVERT_TO[] = "\xEE\xBF";	// üÁ
//$IBMEX_CONVERT_FR[] = "\xFB\xE0";	$IBMEX_CONVERT_TO[] = "\xEE\xC4";	// üÆ
//$IBMEX_CONVERT_FR[] = "\xFB\xE1";	$IBMEX_CONVERT_TO[] = "\xEE\xC5";	// üÇ
//$IBMEX_CONVERT_FR[] = "\xFB\xE2";	$IBMEX_CONVERT_TO[] = "\xEE\xC6";	// üÈ
//$IBMEX_CONVERT_FR[] = "\xFB\xE3";	$IBMEX_CONVERT_TO[] = "\xEE\xC7";	// üÉ
//$IBMEX_CONVERT_FR[] = "\xFB\xE4";	$IBMEX_CONVERT_TO[] = "\xEE\xC8";	// üÊ
//$IBMEX_CONVERT_FR[] = "\xFB\xE5";	$IBMEX_CONVERT_TO[] = "\xEE\xC9";	// üË
//$IBMEX_CONVERT_FR[] = "\xFB\xE6";	$IBMEX_CONVERT_TO[] = "\xEE\xCA";	// üÌ
//$IBMEX_CONVERT_FR[] = "\xFB\xE7";	$IBMEX_CONVERT_TO[] = "\xEE\xCB";	// üÍ
//$IBMEX_CONVERT_FR[] = "\xFB\xE8";	$IBMEX_CONVERT_TO[] = "\xEE\xCC";	// üÎ
//$IBMEX_CONVERT_FR[] = "\xFB\xE9";	$IBMEX_CONVERT_TO[] = "\xEE\xCD";	// üÏ
//$IBMEX_CONVERT_FR[] = "\xFB\xEA";	$IBMEX_CONVERT_TO[] = "\xEE\xCE";	// üÐ
//$IBMEX_CONVERT_FR[] = "\xFB\xEB";	$IBMEX_CONVERT_TO[] = "\xEE\xCF";	// üÑ
//$IBMEX_CONVERT_FR[] = "\xFB\xEC";	$IBMEX_CONVERT_TO[] = "\xEE\xD0";	// üÒ
//$IBMEX_CONVERT_FR[] = "\xFB\xED";	$IBMEX_CONVERT_TO[] = "\xEE\xD1";	// üÓ
//$IBMEX_CONVERT_FR[] = "\xFB\xEE";	$IBMEX_CONVERT_TO[] = "\xEE\xD2";	// üÔ
//$IBMEX_CONVERT_FR[] = "\xFB\xEF";	$IBMEX_CONVERT_TO[] = "\xEE\xD3";	// üÕ
//$IBMEX_CONVERT_FR[] = "\xFB\xF0";	$IBMEX_CONVERT_TO[] = "\xEE\xD4";	// üÖ
//$IBMEX_CONVERT_FR[] = "\xFB\xF1";	$IBMEX_CONVERT_TO[] = "\xEE\xD5";	// ü×
//$IBMEX_CONVERT_FR[] = "\xFB\xF2";	$IBMEX_CONVERT_TO[] = "\xEE\xD6";	// üØ
//$IBMEX_CONVERT_FR[] = "\xFB\xF3";	$IBMEX_CONVERT_TO[] = "\xEE\xD7";	// üÙ
//$IBMEX_CONVERT_FR[] = "\xFB\xF4";	$IBMEX_CONVERT_TO[] = "\xEE\xD8";	// üÚ
//$IBMEX_CONVERT_FR[] = "\xFB\xF5";	$IBMEX_CONVERT_TO[] = "\xEE\xD9";	// üÛ
//$IBMEX_CONVERT_FR[] = "\xFB\xF6";	$IBMEX_CONVERT_TO[] = "\xEE\xDA";	// üÜ
//$IBMEX_CONVERT_FR[] = "\xFB\xF7";	$IBMEX_CONVERT_TO[] = "\xEE\xDB";	// üÝ
//$IBMEX_CONVERT_FR[] = "\xFB\xF8";	$IBMEX_CONVERT_TO[] = "\xEE\xDC";	// üÞ
//$IBMEX_CONVERT_FR[] = "\xFB\xF9";	$IBMEX_CONVERT_TO[] = "\xEE\xDD";	// üß
//$IBMEX_CONVERT_FR[] = "\xFB\xFA";	$IBMEX_CONVERT_TO[] = "\xEE\xDE";	// üà
//$IBMEX_CONVERT_FR[] = "\xFB\xFB";	$IBMEX_CONVERT_TO[] = "\xEE\xDF";	// üá
//$IBMEX_CONVERT_FR[] = "\xFB\xFC";	$IBMEX_CONVERT_TO[] = "\xEE\xE0";	// üâ
//$IBMEX_CONVERT_FR[] = "\xFC\x40";	$IBMEX_CONVERT_TO[] = "\xEE\xE1";	// üã
//$IBMEX_CONVERT_FR[] = "\xFC\x41";	$IBMEX_CONVERT_TO[] = "\xEE\xE2";	// üä
//$IBMEX_CONVERT_FR[] = "\xFC\x42";	$IBMEX_CONVERT_TO[] = "\xEE\xE3";	// üå
//$IBMEX_CONVERT_FR[] = "\xFC\x43";	$IBMEX_CONVERT_TO[] = "\xEE\xE4";	// üæ
//$IBMEX_CONVERT_FR[] = "\xFC\x44";	$IBMEX_CONVERT_TO[] = "\xEE\xE5";	// üç
//$IBMEX_CONVERT_FR[] = "\xFC\x45";	$IBMEX_CONVERT_TO[] = "\xEE\xE6";	// üè
//$IBMEX_CONVERT_FR[] = "\xFC\x46";	$IBMEX_CONVERT_TO[] = "\xEE\xE7";	// üé
//$IBMEX_CONVERT_FR[] = "\xFC\x47";	$IBMEX_CONVERT_TO[] = "\xEE\xE8";	// üê
//$IBMEX_CONVERT_FR[] = "\xFC\x48";	$IBMEX_CONVERT_TO[] = "\xEE\xE9";	// üë
//$IBMEX_CONVERT_FR[] = "\xFC\x49";	$IBMEX_CONVERT_TO[] = "\xEE\xEA";	// üì
//$IBMEX_CONVERT_FR[] = "\xFC\x4A";	$IBMEX_CONVERT_TO[] = "\xEE\xEB";	// üí
//$IBMEX_CONVERT_FR[] = "\xFC\x4B";	$IBMEX_CONVERT_TO[] = "\xEE\xEC";	// üî

// add 2009/08/11 Y.Matsukawa
//---------------------------------------------------------------------------------
// zdc_convert_sjis_ibmex
//
// SJIS¤ÎIBM³ÈÄ¥Ê¸»ú¡Ê115¡Á119¶è¡Ë¤ò´Þ¤àÊ¸»úÎó¤òmb_convert_encoding¤ÇEUC¤ËÊÑ´¹¤¹¤ë¤È
// Ê¸»úÎó¤¬²õ¤ì¤ë¤Î¤Ç¡¢ÊÌ¤Î¶èÅÀ¤ÎÊ¸»ú¤ËÊÑ´¹¤¹¤ë¡£
//---------------------------------------------------------------------------------
function zdc_convert_sjis_ibmex($sjis_str) {
	global $IBMEX_CONVERT_FR;
	global $IBMEX_CONVERT_TO;

	$enc = mb_regex_encoding();
	mb_regex_encoding("SJIS");

// ¢¨Ëè²óÁ´Ê¸»úÃÖ´¹½èÍý¤ò¹Ô¤¦¤Î¤Ï½èÍý»þ´Ö¤¬¤«¤«¤ê¤¹¤®¤ë¤Î¤ÇNG
//	foreach ($IBMEX_CONVERT_FR as $i=>$fr) {
//		$to = $IBMEX_CONVERT_TO[$i];
//		$sjis_str = mb_ereg_replace($fr, $to, $sjis_str);
//	}

// ¢¨preg_¤ÏSJIS¤ËÂÐ±þ¤·¤Æ¤Ê¤«¤Ã¤¿¤Î¤ÇNG
//	$sjis_str = preg_replace_callback('(\xFA[\x40-\x49])', "zdc_sjis_minus_0B51", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFA[\x4A-\x53])', "zdc_sjis_minus_72F6", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFA[\x54-\x57])', "zdc_sjis_minus_0B5B", $sjis_str);
//	$sjis_str = mb_ereg_replace('\xFA\x58', "\x87\x8A", $sjis_str);
//	$sjis_str = mb_ereg_replace('\xFA\x59', "\x87\x82", $sjis_str);
//	$sjis_str = mb_ereg_replace('\xFA\x5A', "\x87\x84", $sjis_str);
//	$sjis_str = mb_ereg_replace('\xFA\x5B', "\x87\x9A", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFA[\x5C-\x7E])', "zdc_sjis_minus_0D1C", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFA[\x80-\x9B])', "zdc_sjis_minus_0D1D", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFA[\x9C-\xFC])', "zdc_sjis_minus_0D1C", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFB[\x40-\x5B])', "zdc_sjis_minus_0D5F", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFB[\x5C-\x7E])', "zdc_sjis_minus_0D1C", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFB[\x80-\x9B])', "zdc_sjis_minus_0D1D", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFB[\x9C-\xDB])', "zdc_sjis_minus_0D1C", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFB[\xE0-\xFC])', "zdc_sjis_minus_0D1C", $sjis_str);
//	$sjis_str = preg_replace_callback('(\xFC[\x40-\x4B])', "zdc_sjis_minus_0D5F", $sjis_str);

	if (mb_ereg('.*\xFA[\x40-\x49]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x40", "\xEE\xEF", $sjis_str);	// i	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x41", "\xEE\xF0", $sjis_str);	// ii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x42", "\xEE\xF1", $sjis_str);	// iii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x43", "\xEE\xF2", $sjis_str);	// iv	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x44", "\xEE\xF3", $sjis_str);	// v	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x45", "\xEE\xF4", $sjis_str);	// vi	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x46", "\xEE\xF5", $sjis_str);	// vii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x47", "\xEE\xF6", $sjis_str);	// viii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x48", "\xEE\xF7", $sjis_str);	// ix	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
		$sjis_str = mb_ereg_replace("\xFA\x49", "\xEE\xF8", $sjis_str);	// x	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	}
	if (mb_ereg('.*\xFA[\x4A-\x53]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x4A", "\x87\x54", $sjis_str);	// ­µ
		$sjis_str = mb_ereg_replace("\xFA\x4B", "\x87\x55", $sjis_str);	// ­¶
		$sjis_str = mb_ereg_replace("\xFA\x4C", "\x87\x56", $sjis_str);	// ­·
		$sjis_str = mb_ereg_replace("\xFA\x4D", "\x87\x57", $sjis_str);	// ­¸
		$sjis_str = mb_ereg_replace("\xFA\x4E", "\x87\x58", $sjis_str);	// ­¹
		$sjis_str = mb_ereg_replace("\xFA\x4F", "\x87\x59", $sjis_str);	// ­º
		$sjis_str = mb_ereg_replace("\xFA\x50", "\x87\x5A", $sjis_str);	// ­»
		$sjis_str = mb_ereg_replace("\xFA\x51", "\x87\x5B", $sjis_str);	// ­¼
		$sjis_str = mb_ereg_replace("\xFA\x52", "\x87\x5C", $sjis_str);	// ­½
		$sjis_str = mb_ereg_replace("\xFA\x53", "\x87\x5D", $sjis_str);	// ­¾
	}
	if (mb_ereg('.*\xFA[\x54-\x57]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x54", "\xEE\xF9", $sjis_str);	// ¢Ì
		$sjis_str = mb_ereg_replace("\xFA\x55", "\xEE\xFA", $sjis_str);	// üü
		$sjis_str = mb_ereg_replace("\xFA\x56", "\xEE\xFB", $sjis_str);	// üý
		$sjis_str = mb_ereg_replace("\xFA\x57", "\xEE\xFC", $sjis_str);	// üþ
	}
	if (mb_ereg('.*\xFA[\x58-\x5B]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x58", "\x87\x8A", $sjis_str);	// ­ê
		$sjis_str = mb_ereg_replace("\xFA\x59", "\x87\x82", $sjis_str);	// ­â
		$sjis_str = mb_ereg_replace("\xFA\x5A", "\x87\x84", $sjis_str);	// ­ä
		$sjis_str = mb_ereg_replace("\xFA\x5B", "\x87\x9A", $sjis_str);	// ¢è
	}
	if (mb_ereg('.*\xFA[\x5C-\x7E]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x5C", "\xED\x40", $sjis_str);	// ù¡
		$sjis_str = mb_ereg_replace("\xFA\x5D", "\xED\x41", $sjis_str);	// ù¢
		$sjis_str = mb_ereg_replace("\xFA\x5E", "\xED\x42", $sjis_str);	// ù£
		$sjis_str = mb_ereg_replace("\xFA\x5F", "\xED\x43", $sjis_str);	// ù¤
		$sjis_str = mb_ereg_replace("\xFA\x60", "\xED\x44", $sjis_str);	// ù¥
		$sjis_str = mb_ereg_replace("\xFA\x61", "\xED\x45", $sjis_str);	// ù¦
		$sjis_str = mb_ereg_replace("\xFA\x62", "\xED\x46", $sjis_str);	// ù§
		$sjis_str = mb_ereg_replace("\xFA\x63", "\xED\x47", $sjis_str);	// ù¨
		$sjis_str = mb_ereg_replace("\xFA\x64", "\xED\x48", $sjis_str);	// ù©
		$sjis_str = mb_ereg_replace("\xFA\x65", "\xED\x49", $sjis_str);	// ùª
		$sjis_str = mb_ereg_replace("\xFA\x66", "\xED\x4A", $sjis_str);	// ù«
		$sjis_str = mb_ereg_replace("\xFA\x67", "\xED\x4B", $sjis_str);	// ù¬
		$sjis_str = mb_ereg_replace("\xFA\x68", "\xED\x4C", $sjis_str);	// ù­
		$sjis_str = mb_ereg_replace("\xFA\x69", "\xED\x4D", $sjis_str);	// ù®
		$sjis_str = mb_ereg_replace("\xFA\x6A", "\xED\x4E", $sjis_str);	// ù¯
		$sjis_str = mb_ereg_replace("\xFA\x6B", "\xED\x4F", $sjis_str);	// ù°
		$sjis_str = mb_ereg_replace("\xFA\x6C", "\xED\x50", $sjis_str);	// ù±
		$sjis_str = mb_ereg_replace("\xFA\x6D", "\xED\x51", $sjis_str);	// ù²
		$sjis_str = mb_ereg_replace("\xFA\x6E", "\xED\x52", $sjis_str);	// ù³
		$sjis_str = mb_ereg_replace("\xFA\x6F", "\xED\x53", $sjis_str);	// ù´
		$sjis_str = mb_ereg_replace("\xFA\x70", "\xED\x54", $sjis_str);	// ùµ
		$sjis_str = mb_ereg_replace("\xFA\x71", "\xED\x55", $sjis_str);	// ù¶
		$sjis_str = mb_ereg_replace("\xFA\x72", "\xED\x56", $sjis_str);	// ù·
		$sjis_str = mb_ereg_replace("\xFA\x73", "\xED\x57", $sjis_str);	// ù¸
		$sjis_str = mb_ereg_replace("\xFA\x74", "\xED\x58", $sjis_str);	// ù¹
		$sjis_str = mb_ereg_replace("\xFA\x75", "\xED\x59", $sjis_str);	// ùº
		$sjis_str = mb_ereg_replace("\xFA\x76", "\xED\x5A", $sjis_str);	// ù»
		$sjis_str = mb_ereg_replace("\xFA\x77", "\xED\x5B", $sjis_str);	// ù¼
		$sjis_str = mb_ereg_replace("\xFA\x78", "\xED\x5C", $sjis_str);	// ù½
		$sjis_str = mb_ereg_replace("\xFA\x79", "\xED\x5D", $sjis_str);	// ù¾
		$sjis_str = mb_ereg_replace("\xFA\x7A", "\xED\x5E", $sjis_str);	// ù¿
		$sjis_str = mb_ereg_replace("\xFA\x7B", "\xED\x5F", $sjis_str);	// ùÀ
		$sjis_str = mb_ereg_replace("\xFA\x7C", "\xED\x60", $sjis_str);	// ùÁ
		$sjis_str = mb_ereg_replace("\xFA\x7D", "\xED\x61", $sjis_str);	// ùÂ
		$sjis_str = mb_ereg_replace("\xFA\x7E", "\xED\x62", $sjis_str);	// ùÃ
	}
	if (mb_ereg('.*\xFA[\x80-\x9B]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x80", "\xED\x63", $sjis_str);	// ùÄ
		$sjis_str = mb_ereg_replace("\xFA\x81", "\xED\x64", $sjis_str);	// ùÅ
		$sjis_str = mb_ereg_replace("\xFA\x82", "\xED\x65", $sjis_str);	// ùÆ
		$sjis_str = mb_ereg_replace("\xFA\x83", "\xED\x66", $sjis_str);	// ùÇ
		$sjis_str = mb_ereg_replace("\xFA\x84", "\xED\x67", $sjis_str);	// ùÈ
		$sjis_str = mb_ereg_replace("\xFA\x85", "\xED\x68", $sjis_str);	// ùÉ
		$sjis_str = mb_ereg_replace("\xFA\x86", "\xED\x69", $sjis_str);	// ùÊ
		$sjis_str = mb_ereg_replace("\xFA\x87", "\xED\x6A", $sjis_str);	// ùË
		$sjis_str = mb_ereg_replace("\xFA\x88", "\xED\x6B", $sjis_str);	// ùÌ
		$sjis_str = mb_ereg_replace("\xFA\x89", "\xED\x6C", $sjis_str);	// ùÍ
		$sjis_str = mb_ereg_replace("\xFA\x8A", "\xED\x6D", $sjis_str);	// ùÎ
		$sjis_str = mb_ereg_replace("\xFA\x8B", "\xED\x6E", $sjis_str);	// ùÏ
		$sjis_str = mb_ereg_replace("\xFA\x8C", "\xED\x6F", $sjis_str);	// ùÐ
		$sjis_str = mb_ereg_replace("\xFA\x8D", "\xED\x70", $sjis_str);	// ùÑ
		$sjis_str = mb_ereg_replace("\xFA\x8E", "\xED\x71", $sjis_str);	// ùÒ
		$sjis_str = mb_ereg_replace("\xFA\x8F", "\xED\x72", $sjis_str);	// ùÓ
		$sjis_str = mb_ereg_replace("\xFA\x90", "\xED\x73", $sjis_str);	// ùÔ
		$sjis_str = mb_ereg_replace("\xFA\x91", "\xED\x74", $sjis_str);	// ùÕ
		$sjis_str = mb_ereg_replace("\xFA\x92", "\xED\x75", $sjis_str);	// ùÖ
		$sjis_str = mb_ereg_replace("\xFA\x93", "\xED\x76", $sjis_str);	// ù×
		$sjis_str = mb_ereg_replace("\xFA\x94", "\xED\x77", $sjis_str);	// ùØ
		$sjis_str = mb_ereg_replace("\xFA\x95", "\xED\x78", $sjis_str);	// ùÙ
		$sjis_str = mb_ereg_replace("\xFA\x96", "\xED\x79", $sjis_str);	// ùÚ
		$sjis_str = mb_ereg_replace("\xFA\x97", "\xED\x7A", $sjis_str);	// ùÛ
		$sjis_str = mb_ereg_replace("\xFA\x98", "\xED\x7B", $sjis_str);	// ùÜ
		$sjis_str = mb_ereg_replace("\xFA\x99", "\xED\x7C", $sjis_str);	// ùÝ
		$sjis_str = mb_ereg_replace("\xFA\x9A", "\xED\x7D", $sjis_str);	// ùÞ
		$sjis_str = mb_ereg_replace("\xFA\x9B", "\xED\x7E", $sjis_str);	// ùß
	}
	if (mb_ereg('.*\xFA[\x9C-\xFC]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFA\x9C", "\xED\x80", $sjis_str);	// ùà
		$sjis_str = mb_ereg_replace("\xFA\x9D", "\xED\x81", $sjis_str);	// ùá
		$sjis_str = mb_ereg_replace("\xFA\x9E", "\xED\x82", $sjis_str);	// ùâ
		$sjis_str = mb_ereg_replace("\xFA\x9F", "\xED\x83", $sjis_str);	// ùã
		$sjis_str = mb_ereg_replace("\xFA\xA0", "\xED\x84", $sjis_str);	// ùä
		$sjis_str = mb_ereg_replace("\xFA\xA1", "\xED\x85", $sjis_str);	// ùå
		$sjis_str = mb_ereg_replace("\xFA\xA2", "\xED\x86", $sjis_str);	// ùæ
		$sjis_str = mb_ereg_replace("\xFA\xA3", "\xED\x87", $sjis_str);	// ùç
		$sjis_str = mb_ereg_replace("\xFA\xA4", "\xED\x88", $sjis_str);	// ùè
		$sjis_str = mb_ereg_replace("\xFA\xA5", "\xED\x89", $sjis_str);	// ùé
		$sjis_str = mb_ereg_replace("\xFA\xA6", "\xED\x8A", $sjis_str);	// ùê
		$sjis_str = mb_ereg_replace("\xFA\xA7", "\xED\x8B", $sjis_str);	// ùë
		$sjis_str = mb_ereg_replace("\xFA\xA8", "\xED\x8C", $sjis_str);	// ùì
		$sjis_str = mb_ereg_replace("\xFA\xA9", "\xED\x8D", $sjis_str);	// ùí
		$sjis_str = mb_ereg_replace("\xFA\xAA", "\xED\x8E", $sjis_str);	// ùî
		$sjis_str = mb_ereg_replace("\xFA\xAB", "\xED\x8F", $sjis_str);	// ùï
		$sjis_str = mb_ereg_replace("\xFA\xAC", "\xED\x90", $sjis_str);	// ùð
		$sjis_str = mb_ereg_replace("\xFA\xAD", "\xED\x91", $sjis_str);	// ùñ
		$sjis_str = mb_ereg_replace("\xFA\xAE", "\xED\x92", $sjis_str);	// ùò
		$sjis_str = mb_ereg_replace("\xFA\xAF", "\xED\x93", $sjis_str);	// ùó
		$sjis_str = mb_ereg_replace("\xFA\xB0", "\xED\x94", $sjis_str);	// ùô
		$sjis_str = mb_ereg_replace("\xFA\xB1", "\xED\x95", $sjis_str);	// ùõ
		$sjis_str = mb_ereg_replace("\xFA\xB2", "\xED\x96", $sjis_str);	// ùö
		$sjis_str = mb_ereg_replace("\xFA\xB3", "\xED\x97", $sjis_str);	// ù÷
		$sjis_str = mb_ereg_replace("\xFA\xB4", "\xED\x98", $sjis_str);	// ùø
		$sjis_str = mb_ereg_replace("\xFA\xB5", "\xED\x99", $sjis_str);	// ùù
		$sjis_str = mb_ereg_replace("\xFA\xB6", "\xED\x9A", $sjis_str);	// ùú
		$sjis_str = mb_ereg_replace("\xFA\xB7", "\xED\x9B", $sjis_str);	// ùû
		$sjis_str = mb_ereg_replace("\xFA\xB8", "\xED\x9C", $sjis_str);	// ùü
		$sjis_str = mb_ereg_replace("\xFA\xB9", "\xED\x9D", $sjis_str);	// ùý
		$sjis_str = mb_ereg_replace("\xFA\xBA", "\xED\x9E", $sjis_str);	// ùþ
		$sjis_str = mb_ereg_replace("\xFA\xBB", "\xED\x9F", $sjis_str);	// ú¡
		$sjis_str = mb_ereg_replace("\xFA\xBC", "\xED\xA0", $sjis_str);	// ú¢
		$sjis_str = mb_ereg_replace("\xFA\xBD", "\xED\xA1", $sjis_str);	// ú£
		$sjis_str = mb_ereg_replace("\xFA\xBE", "\xED\xA2", $sjis_str);	// ú¤
		$sjis_str = mb_ereg_replace("\xFA\xBF", "\xED\xA3", $sjis_str);	// ú¥
		$sjis_str = mb_ereg_replace("\xFA\xC0", "\xED\xA4", $sjis_str);	// ú¦
		$sjis_str = mb_ereg_replace("\xFA\xC1", "\xED\xA5", $sjis_str);	// ú§
		$sjis_str = mb_ereg_replace("\xFA\xC2", "\xED\xA6", $sjis_str);	// ú¨
		$sjis_str = mb_ereg_replace("\xFA\xC3", "\xED\xA7", $sjis_str);	// ú©
		$sjis_str = mb_ereg_replace("\xFA\xC4", "\xED\xA8", $sjis_str);	// úª
		$sjis_str = mb_ereg_replace("\xFA\xC5", "\xED\xA9", $sjis_str);	// ú«
		$sjis_str = mb_ereg_replace("\xFA\xC6", "\xED\xAA", $sjis_str);	// ú¬
		$sjis_str = mb_ereg_replace("\xFA\xC7", "\xED\xAB", $sjis_str);	// ú­
		$sjis_str = mb_ereg_replace("\xFA\xC8", "\xED\xAC", $sjis_str);	// ú®
		$sjis_str = mb_ereg_replace("\xFA\xC9", "\xED\xAD", $sjis_str);	// ú¯
		$sjis_str = mb_ereg_replace("\xFA\xCA", "\xED\xAE", $sjis_str);	// ú°
		$sjis_str = mb_ereg_replace("\xFA\xCB", "\xED\xAF", $sjis_str);	// ú±
		$sjis_str = mb_ereg_replace("\xFA\xCC", "\xED\xB0", $sjis_str);	// ú²
		$sjis_str = mb_ereg_replace("\xFA\xCD", "\xED\xB1", $sjis_str);	// ú³
		$sjis_str = mb_ereg_replace("\xFA\xCE", "\xED\xB2", $sjis_str);	// ú´
		$sjis_str = mb_ereg_replace("\xFA\xCF", "\xED\xB3", $sjis_str);	// úµ
		$sjis_str = mb_ereg_replace("\xFA\xD0", "\xED\xB4", $sjis_str);	// ú¶
		$sjis_str = mb_ereg_replace("\xFA\xD1", "\xED\xB5", $sjis_str);	// ú·
		$sjis_str = mb_ereg_replace("\xFA\xD2", "\xED\xB6", $sjis_str);	// ú¸
		$sjis_str = mb_ereg_replace("\xFA\xD3", "\xED\xB7", $sjis_str);	// ú¹
		$sjis_str = mb_ereg_replace("\xFA\xD4", "\xED\xB8", $sjis_str);	// úº
		$sjis_str = mb_ereg_replace("\xFA\xD5", "\xED\xB9", $sjis_str);	// ú»
		$sjis_str = mb_ereg_replace("\xFA\xD6", "\xED\xBA", $sjis_str);	// ú¼
		$sjis_str = mb_ereg_replace("\xFA\xD7", "\xED\xBB", $sjis_str);	// ú½
		$sjis_str = mb_ereg_replace("\xFA\xD8", "\xED\xBC", $sjis_str);	// ú¾
		$sjis_str = mb_ereg_replace("\xFA\xD9", "\xED\xBD", $sjis_str);	// ú¿
		$sjis_str = mb_ereg_replace("\xFA\xDA", "\xED\xBE", $sjis_str);	// úÀ
		$sjis_str = mb_ereg_replace("\xFA\xDB", "\xED\xBF", $sjis_str);	// úÁ
		$sjis_str = mb_ereg_replace("\xFA\xDC", "\xED\xC0", $sjis_str);	// úÂ
		$sjis_str = mb_ereg_replace("\xFA\xDD", "\xED\xC1", $sjis_str);	// úÃ
		$sjis_str = mb_ereg_replace("\xFA\xDE", "\xED\xC2", $sjis_str);	// úÄ
		$sjis_str = mb_ereg_replace("\xFA\xDF", "\xED\xC3", $sjis_str);	// úÅ
		$sjis_str = mb_ereg_replace("\xFA\xE0", "\xED\xC4", $sjis_str);	// úÆ
		$sjis_str = mb_ereg_replace("\xFA\xE1", "\xED\xC5", $sjis_str);	// úÇ
		$sjis_str = mb_ereg_replace("\xFA\xE2", "\xED\xC6", $sjis_str);	// úÈ
		$sjis_str = mb_ereg_replace("\xFA\xE3", "\xED\xC7", $sjis_str);	// úÉ
		$sjis_str = mb_ereg_replace("\xFA\xE4", "\xED\xC8", $sjis_str);	// úÊ
		$sjis_str = mb_ereg_replace("\xFA\xE5", "\xED\xC9", $sjis_str);	// úË
		$sjis_str = mb_ereg_replace("\xFA\xE6", "\xED\xCA", $sjis_str);	// úÌ
		$sjis_str = mb_ereg_replace("\xFA\xE7", "\xED\xCB", $sjis_str);	// úÍ
		$sjis_str = mb_ereg_replace("\xFA\xE8", "\xED\xCC", $sjis_str);	// úÎ
		$sjis_str = mb_ereg_replace("\xFA\xE9", "\xED\xCD", $sjis_str);	// úÏ
		$sjis_str = mb_ereg_replace("\xFA\xEA", "\xED\xCE", $sjis_str);	// úÐ
		$sjis_str = mb_ereg_replace("\xFA\xEB", "\xED\xCF", $sjis_str);	// úÑ
		$sjis_str = mb_ereg_replace("\xFA\xEC", "\xED\xD0", $sjis_str);	// úÒ
		$sjis_str = mb_ereg_replace("\xFA\xED", "\xED\xD1", $sjis_str);	// úÓ
		$sjis_str = mb_ereg_replace("\xFA\xEE", "\xED\xD2", $sjis_str);	// úÔ
		$sjis_str = mb_ereg_replace("\xFA\xEF", "\xED\xD3", $sjis_str);	// úÕ
		$sjis_str = mb_ereg_replace("\xFA\xF0", "\xED\xD4", $sjis_str);	// úÖ
		$sjis_str = mb_ereg_replace("\xFA\xF1", "\xED\xD5", $sjis_str);	// ú×
		$sjis_str = mb_ereg_replace("\xFA\xF2", "\xED\xD6", $sjis_str);	// úØ
		$sjis_str = mb_ereg_replace("\xFA\xF3", "\xED\xD7", $sjis_str);	// úÙ
		$sjis_str = mb_ereg_replace("\xFA\xF4", "\xED\xD8", $sjis_str);	// úÚ
		$sjis_str = mb_ereg_replace("\xFA\xF5", "\xED\xD9", $sjis_str);	// úÛ
		$sjis_str = mb_ereg_replace("\xFA\xF6", "\xED\xDA", $sjis_str);	// úÜ
		$sjis_str = mb_ereg_replace("\xFA\xF7", "\xED\xDB", $sjis_str);	// úÝ
		$sjis_str = mb_ereg_replace("\xFA\xF8", "\xED\xDC", $sjis_str);	// úÞ
		$sjis_str = mb_ereg_replace("\xFA\xF9", "\xED\xDD", $sjis_str);	// úß
		$sjis_str = mb_ereg_replace("\xFA\xFA", "\xED\xDE", $sjis_str);	// úà
		$sjis_str = mb_ereg_replace("\xFA\xFB", "\xED\xDF", $sjis_str);	// úá
		$sjis_str = mb_ereg_replace("\xFA\xFC", "\xED\xE0", $sjis_str);	// úâ
	}
	if (mb_ereg('.*\xFB[\x40-\x5B]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFB\x40", "\xED\xE1", $sjis_str);	// úã
		$sjis_str = mb_ereg_replace("\xFB\x41", "\xED\xE2", $sjis_str);	// úä
		$sjis_str = mb_ereg_replace("\xFB\x42", "\xED\xE3", $sjis_str);	// úå
		$sjis_str = mb_ereg_replace("\xFB\x43", "\xED\xE4", $sjis_str);	// úæ
		$sjis_str = mb_ereg_replace("\xFB\x44", "\xED\xE5", $sjis_str);	// úç
		$sjis_str = mb_ereg_replace("\xFB\x45", "\xED\xE6", $sjis_str);	// úè
		$sjis_str = mb_ereg_replace("\xFB\x46", "\xED\xE7", $sjis_str);	// úé
		$sjis_str = mb_ereg_replace("\xFB\x47", "\xED\xE8", $sjis_str);	// úê
		$sjis_str = mb_ereg_replace("\xFB\x48", "\xED\xE9", $sjis_str);	// úë
		$sjis_str = mb_ereg_replace("\xFB\x49", "\xED\xEA", $sjis_str);	// úì
		$sjis_str = mb_ereg_replace("\xFB\x4A", "\xED\xEB", $sjis_str);	// úí
		$sjis_str = mb_ereg_replace("\xFB\x4B", "\xED\xEC", $sjis_str);	// úî
		$sjis_str = mb_ereg_replace("\xFB\x4C", "\xED\xED", $sjis_str);	// úï
		$sjis_str = mb_ereg_replace("\xFB\x4D", "\xED\xEE", $sjis_str);	// úð
		$sjis_str = mb_ereg_replace("\xFB\x4E", "\xED\xEF", $sjis_str);	// úñ
		$sjis_str = mb_ereg_replace("\xFB\x4F", "\xED\xF0", $sjis_str);	// úò
		$sjis_str = mb_ereg_replace("\xFB\x50", "\xED\xF1", $sjis_str);	// úó
		$sjis_str = mb_ereg_replace("\xFB\x51", "\xED\xF2", $sjis_str);	// úô
		$sjis_str = mb_ereg_replace("\xFB\x52", "\xED\xF3", $sjis_str);	// úõ
		$sjis_str = mb_ereg_replace("\xFB\x53", "\xED\xF4", $sjis_str);	// úö
		$sjis_str = mb_ereg_replace("\xFB\x54", "\xED\xF5", $sjis_str);	// ú÷
		$sjis_str = mb_ereg_replace("\xFB\x55", "\xED\xF6", $sjis_str);	// úø
		$sjis_str = mb_ereg_replace("\xFB\x56", "\xED\xF7", $sjis_str);	// úù
		$sjis_str = mb_ereg_replace("\xFB\x57", "\xED\xF8", $sjis_str);	// úú
		$sjis_str = mb_ereg_replace("\xFB\x58", "\xED\xF9", $sjis_str);	// úû
		$sjis_str = mb_ereg_replace("\xFB\x59", "\xED\xFA", $sjis_str);	// úü
		$sjis_str = mb_ereg_replace("\xFB\x5A", "\xED\xFB", $sjis_str);	// úý
		$sjis_str = mb_ereg_replace("\xFB\x5B", "\xED\xFC", $sjis_str);	// úþ
	}
	if (mb_ereg('.*\xFB[\x5C-\x7E]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFB\x5C", "\xEE\x40", $sjis_str);	// û¡
		$sjis_str = mb_ereg_replace("\xFB\x5D", "\xEE\x41", $sjis_str);	// û¢
		$sjis_str = mb_ereg_replace("\xFB\x5E", "\xEE\x42", $sjis_str);	// û£
		$sjis_str = mb_ereg_replace("\xFB\x5F", "\xEE\x43", $sjis_str);	// û¤
		$sjis_str = mb_ereg_replace("\xFB\x60", "\xEE\x44", $sjis_str);	// û¥
		$sjis_str = mb_ereg_replace("\xFB\x61", "\xEE\x45", $sjis_str);	// û¦
		$sjis_str = mb_ereg_replace("\xFB\x62", "\xEE\x46", $sjis_str);	// û§
		$sjis_str = mb_ereg_replace("\xFB\x63", "\xEE\x47", $sjis_str);	// û¨
		$sjis_str = mb_ereg_replace("\xFB\x64", "\xEE\x48", $sjis_str);	// û©
		$sjis_str = mb_ereg_replace("\xFB\x65", "\xEE\x49", $sjis_str);	// ûª
		$sjis_str = mb_ereg_replace("\xFB\x66", "\xEE\x4A", $sjis_str);	// û«
		$sjis_str = mb_ereg_replace("\xFB\x67", "\xEE\x4B", $sjis_str);	// û¬
		$sjis_str = mb_ereg_replace("\xFB\x68", "\xEE\x4C", $sjis_str);	// û­
		$sjis_str = mb_ereg_replace("\xFB\x69", "\xEE\x4D", $sjis_str);	// û®
		$sjis_str = mb_ereg_replace("\xFB\x6A", "\xEE\x4E", $sjis_str);	// û¯
		$sjis_str = mb_ereg_replace("\xFB\x6B", "\xEE\x4F", $sjis_str);	// û°
		$sjis_str = mb_ereg_replace("\xFB\x6C", "\xEE\x50", $sjis_str);	// û±
		$sjis_str = mb_ereg_replace("\xFB\x6D", "\xEE\x51", $sjis_str);	// û²
		$sjis_str = mb_ereg_replace("\xFB\x6E", "\xEE\x52", $sjis_str);	// û³
		$sjis_str = mb_ereg_replace("\xFB\x6F", "\xEE\x53", $sjis_str);	// û´
		$sjis_str = mb_ereg_replace("\xFB\x70", "\xEE\x54", $sjis_str);	// ûµ
		$sjis_str = mb_ereg_replace("\xFB\x71", "\xEE\x55", $sjis_str);	// û¶
		$sjis_str = mb_ereg_replace("\xFB\x72", "\xEE\x56", $sjis_str);	// û·
		$sjis_str = mb_ereg_replace("\xFB\x73", "\xEE\x57", $sjis_str);	// û¸
		$sjis_str = mb_ereg_replace("\xFB\x74", "\xEE\x58", $sjis_str);	// û¹
		$sjis_str = mb_ereg_replace("\xFB\x75", "\xEE\x59", $sjis_str);	// ûº
		$sjis_str = mb_ereg_replace("\xFB\x76", "\xEE\x5A", $sjis_str);	// û»
		$sjis_str = mb_ereg_replace("\xFB\x77", "\xEE\x5B", $sjis_str);	// û¼
		$sjis_str = mb_ereg_replace("\xFB\x78", "\xEE\x5C", $sjis_str);	// û½
		$sjis_str = mb_ereg_replace("\xFB\x79", "\xEE\x5D", $sjis_str);	// û¾
		$sjis_str = mb_ereg_replace("\xFB\x7A", "\xEE\x5E", $sjis_str);	// û¿
		$sjis_str = mb_ereg_replace("\xFB\x7B", "\xEE\x5F", $sjis_str);	// ûÀ
		$sjis_str = mb_ereg_replace("\xFB\x7C", "\xEE\x60", $sjis_str);	// ûÁ
		$sjis_str = mb_ereg_replace("\xFB\x7D", "\xEE\x61", $sjis_str);	// ûÂ
		$sjis_str = mb_ereg_replace("\xFB\x7E", "\xEE\x62", $sjis_str);	// ûÃ
	}
	if (mb_ereg('.*\xFB[\x80-\x9B]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFB\x80", "\xEE\x63", $sjis_str);	// ûÄ
		$sjis_str = mb_ereg_replace("\xFB\x81", "\xEE\x64", $sjis_str);	// ûÅ
		$sjis_str = mb_ereg_replace("\xFB\x82", "\xEE\x65", $sjis_str);	// ûÆ
		$sjis_str = mb_ereg_replace("\xFB\x83", "\xEE\x66", $sjis_str);	// ûÇ
		$sjis_str = mb_ereg_replace("\xFB\x84", "\xEE\x67", $sjis_str);	// ûÈ
		$sjis_str = mb_ereg_replace("\xFB\x85", "\xEE\x68", $sjis_str);	// ûÉ
		$sjis_str = mb_ereg_replace("\xFB\x86", "\xEE\x69", $sjis_str);	// ûÊ
		$sjis_str = mb_ereg_replace("\xFB\x87", "\xEE\x6A", $sjis_str);	// ûË
		$sjis_str = mb_ereg_replace("\xFB\x88", "\xEE\x6B", $sjis_str);	// ûÌ
		$sjis_str = mb_ereg_replace("\xFB\x89", "\xEE\x6C", $sjis_str);	// ûÍ
		$sjis_str = mb_ereg_replace("\xFB\x8A", "\xEE\x6D", $sjis_str);	// ûÎ
		$sjis_str = mb_ereg_replace("\xFB\x8B", "\xEE\x6E", $sjis_str);	// ûÏ
		$sjis_str = mb_ereg_replace("\xFB\x8C", "\xEE\x6F", $sjis_str);	// ûÐ
		$sjis_str = mb_ereg_replace("\xFB\x8D", "\xEE\x70", $sjis_str);	// ûÑ
		$sjis_str = mb_ereg_replace("\xFB\x8E", "\xEE\x71", $sjis_str);	// ûÒ
		$sjis_str = mb_ereg_replace("\xFB\x8F", "\xEE\x72", $sjis_str);	// ûÓ
		$sjis_str = mb_ereg_replace("\xFB\x90", "\xEE\x73", $sjis_str);	// ûÔ
		$sjis_str = mb_ereg_replace("\xFB\x91", "\xEE\x74", $sjis_str);	// ûÕ
		$sjis_str = mb_ereg_replace("\xFB\x92", "\xEE\x75", $sjis_str);	// ûÖ
		$sjis_str = mb_ereg_replace("\xFB\x93", "\xEE\x76", $sjis_str);	// û×
		$sjis_str = mb_ereg_replace("\xFB\x94", "\xEE\x77", $sjis_str);	// ûØ
		$sjis_str = mb_ereg_replace("\xFB\x95", "\xEE\x78", $sjis_str);	// ûÙ
		$sjis_str = mb_ereg_replace("\xFB\x96", "\xEE\x79", $sjis_str);	// ûÚ
		$sjis_str = mb_ereg_replace("\xFB\x97", "\xEE\x7A", $sjis_str);	// ûÛ
		$sjis_str = mb_ereg_replace("\xFB\x98", "\xEE\x7B", $sjis_str);	// ûÜ
		$sjis_str = mb_ereg_replace("\xFB\x99", "\xEE\x7C", $sjis_str);	// ûÝ
		$sjis_str = mb_ereg_replace("\xFB\x9A", "\xEE\x7D", $sjis_str);	// ûÞ
		$sjis_str = mb_ereg_replace("\xFB\x9B", "\xEE\x7E", $sjis_str);	// ûß
	}
	if (mb_ereg('.*\xFB[\x9C-\xDB]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFB\x9C", "\xEE\x80", $sjis_str);	// ûà
		$sjis_str = mb_ereg_replace("\xFB\x9D", "\xEE\x81", $sjis_str);	// ûá
		$sjis_str = mb_ereg_replace("\xFB\x9E", "\xEE\x82", $sjis_str);	// ûâ
		$sjis_str = mb_ereg_replace("\xFB\x9F", "\xEE\x83", $sjis_str);	// ûã
		$sjis_str = mb_ereg_replace("\xFB\xA0", "\xEE\x84", $sjis_str);	// ûä
		$sjis_str = mb_ereg_replace("\xFB\xA1", "\xEE\x85", $sjis_str);	// ûå
		$sjis_str = mb_ereg_replace("\xFB\xA2", "\xEE\x86", $sjis_str);	// ûæ
		$sjis_str = mb_ereg_replace("\xFB\xA3", "\xEE\x87", $sjis_str);	// ûç
		$sjis_str = mb_ereg_replace("\xFB\xA4", "\xEE\x88", $sjis_str);	// ûè
		$sjis_str = mb_ereg_replace("\xFB\xA5", "\xEE\x89", $sjis_str);	// ûé
		$sjis_str = mb_ereg_replace("\xFB\xA6", "\xEE\x8A", $sjis_str);	// ûê
		$sjis_str = mb_ereg_replace("\xFB\xA7", "\xEE\x8B", $sjis_str);	// ûë
		$sjis_str = mb_ereg_replace("\xFB\xA8", "\xEE\x8C", $sjis_str);	// ûì
		$sjis_str = mb_ereg_replace("\xFB\xA9", "\xEE\x8D", $sjis_str);	// ûí
		$sjis_str = mb_ereg_replace("\xFB\xAA", "\xEE\x8E", $sjis_str);	// ûî
		$sjis_str = mb_ereg_replace("\xFB\xAB", "\xEE\x8F", $sjis_str);	// ûï
		$sjis_str = mb_ereg_replace("\xFB\xAC", "\xEE\x90", $sjis_str);	// ûð
		$sjis_str = mb_ereg_replace("\xFB\xAD", "\xEE\x91", $sjis_str);	// ûñ
		$sjis_str = mb_ereg_replace("\xFB\xAE", "\xEE\x92", $sjis_str);	// ûò
		$sjis_str = mb_ereg_replace("\xFB\xAF", "\xEE\x93", $sjis_str);	// ûó
		$sjis_str = mb_ereg_replace("\xFB\xB0", "\xEE\x94", $sjis_str);	// ûô
		$sjis_str = mb_ereg_replace("\xFB\xB1", "\xEE\x95", $sjis_str);	// ûõ
		$sjis_str = mb_ereg_replace("\xFB\xB2", "\xEE\x96", $sjis_str);	// ûö
		$sjis_str = mb_ereg_replace("\xFB\xB3", "\xEE\x97", $sjis_str);	// û÷
		$sjis_str = mb_ereg_replace("\xFB\xB4", "\xEE\x98", $sjis_str);	// ûø
		$sjis_str = mb_ereg_replace("\xFB\xB5", "\xEE\x99", $sjis_str);	// ûù
		$sjis_str = mb_ereg_replace("\xFB\xB6", "\xEE\x9A", $sjis_str);	// ûú
		$sjis_str = mb_ereg_replace("\xFB\xB7", "\xEE\x9B", $sjis_str);	// ûû
		$sjis_str = mb_ereg_replace("\xFB\xB8", "\xEE\x9C", $sjis_str);	// ûü
		$sjis_str = mb_ereg_replace("\xFB\xB9", "\xEE\x9D", $sjis_str);	// ûý
		$sjis_str = mb_ereg_replace("\xFB\xBA", "\xEE\x9E", $sjis_str);	// ûþ
		$sjis_str = mb_ereg_replace("\xFB\xBB", "\xEE\x9F", $sjis_str);	// ü¡
		$sjis_str = mb_ereg_replace("\xFB\xBC", "\xEE\xA0", $sjis_str);	// ü¢
		$sjis_str = mb_ereg_replace("\xFB\xBD", "\xEE\xA1", $sjis_str);	// ü£
		$sjis_str = mb_ereg_replace("\xFB\xBE", "\xEE\xA2", $sjis_str);	// ü¤
		$sjis_str = mb_ereg_replace("\xFB\xBF", "\xEE\xA3", $sjis_str);	// ü¥
		$sjis_str = mb_ereg_replace("\xFB\xC0", "\xEE\xA4", $sjis_str);	// ü¦
		$sjis_str = mb_ereg_replace("\xFB\xC1", "\xEE\xA5", $sjis_str);	// ü§
		$sjis_str = mb_ereg_replace("\xFB\xC2", "\xEE\xA6", $sjis_str);	// ü¨
		$sjis_str = mb_ereg_replace("\xFB\xC3", "\xEE\xA7", $sjis_str);	// ü©
		$sjis_str = mb_ereg_replace("\xFB\xC4", "\xEE\xA8", $sjis_str);	// üª
		$sjis_str = mb_ereg_replace("\xFB\xC5", "\xEE\xA9", $sjis_str);	// ü«
		$sjis_str = mb_ereg_replace("\xFB\xC6", "\xEE\xAA", $sjis_str);	// ü¬
		$sjis_str = mb_ereg_replace("\xFB\xC7", "\xEE\xAB", $sjis_str);	// ü­
		$sjis_str = mb_ereg_replace("\xFB\xC8", "\xEE\xAC", $sjis_str);	// ü®
		$sjis_str = mb_ereg_replace("\xFB\xC9", "\xEE\xAD", $sjis_str);	// ü¯
		$sjis_str = mb_ereg_replace("\xFB\xCA", "\xEE\xAE", $sjis_str);	// ü°
		$sjis_str = mb_ereg_replace("\xFB\xCB", "\xEE\xAF", $sjis_str);	// ü±
		$sjis_str = mb_ereg_replace("\xFB\xCC", "\xEE\xB0", $sjis_str);	// ü²
		$sjis_str = mb_ereg_replace("\xFB\xCD", "\xEE\xB1", $sjis_str);	// ü³
		$sjis_str = mb_ereg_replace("\xFB\xCE", "\xEE\xB2", $sjis_str);	// ü´
		$sjis_str = mb_ereg_replace("\xFB\xCF", "\xEE\xB3", $sjis_str);	// üµ
		$sjis_str = mb_ereg_replace("\xFB\xD0", "\xEE\xB4", $sjis_str);	// ü¶
		$sjis_str = mb_ereg_replace("\xFB\xD1", "\xEE\xB5", $sjis_str);	// ü·
		$sjis_str = mb_ereg_replace("\xFB\xD2", "\xEE\xB6", $sjis_str);	// ü¸
		$sjis_str = mb_ereg_replace("\xFB\xD3", "\xEE\xB7", $sjis_str);	// ü¹
		$sjis_str = mb_ereg_replace("\xFB\xD4", "\xEE\xB8", $sjis_str);	// üº
		$sjis_str = mb_ereg_replace("\xFB\xD5", "\xEE\xB9", $sjis_str);	// ü»
		$sjis_str = mb_ereg_replace("\xFB\xD6", "\xEE\xBA", $sjis_str);	// ü¼
		$sjis_str = mb_ereg_replace("\xFB\xD7", "\xEE\xBB", $sjis_str);	// ü½
		$sjis_str = mb_ereg_replace("\xFB\xD8", "\xEE\xBC", $sjis_str);	// ü¾
		$sjis_str = mb_ereg_replace("\xFB\xD9", "\xEE\xBD", $sjis_str);	// ü¿
		$sjis_str = mb_ereg_replace("\xFB\xDA", "\xEE\xBE", $sjis_str);	// üÀ
		$sjis_str = mb_ereg_replace("\xFB\xDB", "\xEE\xBF", $sjis_str);	// üÁ
	}
	if (mb_ereg('.*\xFB[\xE0-\xFC]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFB\xE0", "\xEE\xC4", $sjis_str);	// üÆ
		$sjis_str = mb_ereg_replace("\xFB\xE1", "\xEE\xC5", $sjis_str);	// üÇ
		$sjis_str = mb_ereg_replace("\xFB\xE2", "\xEE\xC6", $sjis_str);	// üÈ
		$sjis_str = mb_ereg_replace("\xFB\xE3", "\xEE\xC7", $sjis_str);	// üÉ
		$sjis_str = mb_ereg_replace("\xFB\xE4", "\xEE\xC8", $sjis_str);	// üÊ
		$sjis_str = mb_ereg_replace("\xFB\xE5", "\xEE\xC9", $sjis_str);	// üË
		$sjis_str = mb_ereg_replace("\xFB\xE6", "\xEE\xCA", $sjis_str);	// üÌ
		$sjis_str = mb_ereg_replace("\xFB\xE7", "\xEE\xCB", $sjis_str);	// üÍ
		$sjis_str = mb_ereg_replace("\xFB\xE8", "\xEE\xCC", $sjis_str);	// üÎ
		$sjis_str = mb_ereg_replace("\xFB\xE9", "\xEE\xCD", $sjis_str);	// üÏ
		$sjis_str = mb_ereg_replace("\xFB\xEA", "\xEE\xCE", $sjis_str);	// üÐ
		$sjis_str = mb_ereg_replace("\xFB\xEB", "\xEE\xCF", $sjis_str);	// üÑ
		$sjis_str = mb_ereg_replace("\xFB\xEC", "\xEE\xD0", $sjis_str);	// üÒ
		$sjis_str = mb_ereg_replace("\xFB\xED", "\xEE\xD1", $sjis_str);	// üÓ
		$sjis_str = mb_ereg_replace("\xFB\xEE", "\xEE\xD2", $sjis_str);	// üÔ
		$sjis_str = mb_ereg_replace("\xFB\xEF", "\xEE\xD3", $sjis_str);	// üÕ
		$sjis_str = mb_ereg_replace("\xFB\xF0", "\xEE\xD4", $sjis_str);	// üÖ
		$sjis_str = mb_ereg_replace("\xFB\xF1", "\xEE\xD5", $sjis_str);	// ü×
		$sjis_str = mb_ereg_replace("\xFB\xF2", "\xEE\xD6", $sjis_str);	// üØ
		$sjis_str = mb_ereg_replace("\xFB\xF3", "\xEE\xD7", $sjis_str);	// üÙ
		$sjis_str = mb_ereg_replace("\xFB\xF4", "\xEE\xD8", $sjis_str);	// üÚ
		$sjis_str = mb_ereg_replace("\xFB\xF5", "\xEE\xD9", $sjis_str);	// üÛ
		$sjis_str = mb_ereg_replace("\xFB\xF6", "\xEE\xDA", $sjis_str);	// üÜ
		$sjis_str = mb_ereg_replace("\xFB\xF7", "\xEE\xDB", $sjis_str);	// üÝ
		$sjis_str = mb_ereg_replace("\xFB\xF8", "\xEE\xDC", $sjis_str);	// üÞ
		$sjis_str = mb_ereg_replace("\xFB\xF9", "\xEE\xDD", $sjis_str);	// üß
		$sjis_str = mb_ereg_replace("\xFB\xFA", "\xEE\xDE", $sjis_str);	// üà
		$sjis_str = mb_ereg_replace("\xFB\xFB", "\xEE\xDF", $sjis_str);	// üá
		$sjis_str = mb_ereg_replace("\xFB\xFC", "\xEE\xE0", $sjis_str);	// üâ
	}
	if (mb_ereg('.*\xFC[\x40-\x4B]', $sjis_str)) {
		$sjis_str = mb_ereg_replace("\xFC\x40", "\xEE\xE1", $sjis_str);	// üã
		$sjis_str = mb_ereg_replace("\xFC\x41", "\xEE\xE2", $sjis_str);	// üä
		$sjis_str = mb_ereg_replace("\xFC\x42", "\xEE\xE3", $sjis_str);	// üå
		$sjis_str = mb_ereg_replace("\xFC\x43", "\xEE\xE4", $sjis_str);	// üæ
		$sjis_str = mb_ereg_replace("\xFC\x44", "\xEE\xE5", $sjis_str);	// üç
		$sjis_str = mb_ereg_replace("\xFC\x45", "\xEE\xE6", $sjis_str);	// üè
		$sjis_str = mb_ereg_replace("\xFC\x46", "\xEE\xE7", $sjis_str);	// üé
		$sjis_str = mb_ereg_replace("\xFC\x47", "\xEE\xE8", $sjis_str);	// üê
		$sjis_str = mb_ereg_replace("\xFC\x48", "\xEE\xE9", $sjis_str);	// üë
		$sjis_str = mb_ereg_replace("\xFC\x49", "\xEE\xEA", $sjis_str);	// üì
		$sjis_str = mb_ereg_replace("\xFC\x4A", "\xEE\xEB", $sjis_str);	// üí
		$sjis_str = mb_ereg_replace("\xFC\x4B", "\xEE\xEC", $sjis_str);	// üî
	}

	mb_regex_encoding($enc);

	return $sjis_str;
}
function zdc_sjis_minus_0B51($matches) {
	return zdc_sjis_minus(&$matches, 0x0B51);
}
function zdc_sjis_minus_72F6($matches) {
	return zdc_sjis_minus(&$matches, 0x72F6);
}
function zdc_sjis_minus_0B5B($matches) {
	return zdc_sjis_minus(&$matches, 0x0B5B);
}
function zdc_sjis_minus_0D1C($matches) {
	return zdc_sjis_minus(&$matches, 0x0D1C);
}
function zdc_sjis_minus_0D1D($matches) {
	return zdc_sjis_minus(&$matches, 0x0D1D);
}
function zdc_sjis_minus_0D5F($matches) {
	return zdc_sjis_minus(&$matches, 0x0D5F);
}
function zdc_sjis_minus(&$matches, $diff) {
	$c = dechex(('0x'.bin2hex($matches[0])) - $diff);
	$c = substr('0'.$c, -4);
	eval('$r=pack("C*", '.'0x'.substr($c, 0, 2).', '.'0x'.substr($c, 2, 2).');');
	return $r;
}

// add 2009/08/17 Y.Matsukawa
//---------------------------------------------------------------------------------
// zdc_convert_izon
//
// EUCÊ¸»úÎóÃæ¤Îµ¡¼ï°ÍÂ¸Ê¸»ú¤ò¡¢ÅÐÏ¿²ÄÇ½¤ÊÂåÂØÊ¸»úÎó¤ËÊÑ´¹¤·¤Þ¤¹¡£
//---------------------------------------------------------------------------------
function zdc_convert_izon($str) {
	$cnv = $str;
	$cnv = mb_ereg_replace("\xAD\xA1", "(1)", $cnv);	// ­¡
	$cnv = mb_ereg_replace("\xAD\xA2", "(2)", $cnv);	// ­¢
	$cnv = mb_ereg_replace("\xAD\xA3", "(3)", $cnv);	// ­£
	$cnv = mb_ereg_replace("\xAD\xA4", "(4)", $cnv);	// ­¤
	$cnv = mb_ereg_replace("\xAD\xA5", "(5)", $cnv);	// ­¥
	$cnv = mb_ereg_replace("\xAD\xA6", "(6)", $cnv);	// ­¦
	$cnv = mb_ereg_replace("\xAD\xA7", "(7)", $cnv);	// ­§
	$cnv = mb_ereg_replace("\xAD\xA8", "(8)", $cnv);	// ­¨
	$cnv = mb_ereg_replace("\xAD\xA9", "(9)", $cnv);	// ­©
	$cnv = mb_ereg_replace("\xAD\xAA", "(10)", $cnv);	// ­ª
	$cnv = mb_ereg_replace("\xAD\xAB", "(11)", $cnv);	// ­«
	$cnv = mb_ereg_replace("\xAD\xAC", "(12)", $cnv);	// ­¬
	$cnv = mb_ereg_replace("\xAD\xAD", "(13)", $cnv);	// ­­
	$cnv = mb_ereg_replace("\xAD\xAE", "(14)", $cnv);	// ­®
	$cnv = mb_ereg_replace("\xAD\xAF", "(15)", $cnv);	// ­¯
	$cnv = mb_ereg_replace("\xAD\xB0", "(16)", $cnv);	// ­°
	$cnv = mb_ereg_replace("\xAD\xB1", "(17)", $cnv);	// ­±
	$cnv = mb_ereg_replace("\xAD\xB2", "(18)", $cnv);	// ­²
	$cnv = mb_ereg_replace("\xAD\xB3", "(19)", $cnv);	// ­³
	$cnv = mb_ereg_replace("\xAD\xB4", "(20)", $cnv);	// ­´
	$cnv = mb_ereg_replace("\xAD\xB5", "I", $cnv);		// ­µ
	$cnv = mb_ereg_replace("\xAD\xB6", "II", $cnv);		// ­¶
	$cnv = mb_ereg_replace("\xAD\xB7", "III", $cnv);	// ­·
	$cnv = mb_ereg_replace("\xAD\xB8", "IV", $cnv);		// ­¸
	$cnv = mb_ereg_replace("\xAD\xB9", "V", $cnv);		// ­¹
	$cnv = mb_ereg_replace("\xAD\xBA", "VI", $cnv);		// ­º
	$cnv = mb_ereg_replace("\xAD\xBB", "VII", $cnv);	// ­»
	$cnv = mb_ereg_replace("\xAD\xBC", "VIII", $cnv);	// ­¼
	$cnv = mb_ereg_replace("\xAD\xBD", "IX", $cnv);		// ­½
	$cnv = mb_ereg_replace("\xAD\xBE", "X", $cnv);		// ­¾
	$cnv = mb_ereg_replace("\xAD\xC0", "ŽÐŽØ", $cnv);		// ­À
	$cnv = mb_ereg_replace("\xAD\xC1", "Ž·ŽÛ", $cnv);		// ­Á
	$cnv = mb_ereg_replace("\xAD\xC2", "Ž¾ŽÝŽÁ", $cnv);	// ­Â
	$cnv = mb_ereg_replace("\xAD\xC3", "ŽÒŽ°ŽÄŽÙ", $cnv);	// ­Ã
	$cnv = mb_ereg_replace("\xAD\xC4", "Ž¸ŽÞŽ×ŽÑ", $cnv);	// ­Ä
	$cnv = mb_ereg_replace("\xAD\xC5", "ŽÄŽÝ", $cnv);		// ­Å
	$cnv = mb_ereg_replace("\xAD\xC6", "Ž±Ž°ŽÙ", $cnv);	// ­Æ
	$cnv = mb_ereg_replace("\xAD\xC7", "ŽÍŽ¸ŽÀŽ°ŽÙ", $cnv);	// ­Ç
	$cnv = mb_ereg_replace("\xAD\xC8", "ŽØŽ¯ŽÄŽÙ", $cnv);	// ­È
	$cnv = mb_ereg_replace("\xAD\xC9", "ŽÜŽ¯ŽÄ", $cnv);	// ­É
	$cnv = mb_ereg_replace("\xAD\xCA", "Ž¶ŽÛŽØŽ°", $cnv);	// ­Ê
	$cnv = mb_ereg_replace("\xAD\xCB", "ŽÄŽÞŽÙ", $cnv);	// ­Ë
	$cnv = mb_ereg_replace("\xAD\xCC", "Ž¾ŽÝŽÄ", $cnv);	// ­Ì
	$cnv = mb_ereg_replace("\xAD\xCD", "ŽÊŽßŽ°Ž¾ŽÝŽÄ", $cnv);	// ­Í
	$cnv = mb_ereg_replace("\xAD\xCE", "ŽÐŽØŽÊŽÞŽ°ŽÙ", $cnv);	// ­Î
	$cnv = mb_ereg_replace("\xAD\xCF", "ŽÍŽßŽ°Ž¼ŽÞ", $cnv);	// ­Ï
	$cnv = mb_ereg_replace("\xAD\xD0", "mm", $cnv);		// ­Ð
	$cnv = mb_ereg_replace("\xAD\xD1", "cm", $cnv);		// ­Ñ
	$cnv = mb_ereg_replace("\xAD\xD2", "km", $cnv);		// ­Ò
	$cnv = mb_ereg_replace("\xAD\xD3", "mg", $cnv);		// ­Ó
	$cnv = mb_ereg_replace("\xAD\xD4", "kg", $cnv);		// ­Ô
	$cnv = mb_ereg_replace("\xAD\xD5", "cc", $cnv);		// ­Õ
	$cnv = mb_ereg_replace("\xAD\xD6", "m&sup2;", $cnv);// ­Ö
	$cnv = mb_ereg_replace("\xAD\xDF", "Ê¿À®", $cnv);	// ­ß
	$cnv = mb_ereg_replace("\xAD\xE0", "¡É", $cnv);		// ­à
	$cnv = mb_ereg_replace("\xAD\xE1", "¡É", $cnv);		// ­á
	$cnv = mb_ereg_replace("\xAD\xE2", "No.", $cnv);	// ­â
	$cnv = mb_ereg_replace("\xAD\xE3", "K.K.", $cnv);	// ­ã
	$cnv = mb_ereg_replace("\xAD\xE4", "TEL", $cnv);	// ­ä
	$cnv = mb_ereg_replace("\xAD\xE5", "(¾å)", $cnv);	// ­å
	$cnv = mb_ereg_replace("\xAD\xE6", "(Ãæ)", $cnv);	// ­æ
	$cnv = mb_ereg_replace("\xAD\xE7", "(²¼)", $cnv);	// ­ç
	$cnv = mb_ereg_replace("\xAD\xE8", "(º¸)", $cnv);	// ­è
	$cnv = mb_ereg_replace("\xAD\xE9", "(±¦)", $cnv);	// ­é
	$cnv = mb_ereg_replace("\xAD\xEA", "(³ô)", $cnv);	// ­ê
	$cnv = mb_ereg_replace("\xAD\xEB", "(Í­)", $cnv);	// ­ë
	$cnv = mb_ereg_replace("\xAD\xEC", "(Âå)", $cnv);	// ­ì
	$cnv = mb_ereg_replace("\xAD\xED", "ÌÀ¼£", $cnv);	// ­í
	$cnv = mb_ereg_replace("\xAD\xEE", "ÂçÀµ", $cnv);	// ­î
	$cnv = mb_ereg_replace("\xAD\xEF", "¾¼ÏÂ", $cnv);	// ­ï
	$cnv = mb_ereg_replace("\xAD\xF0", "¢â", $cnv);		// ¢â
	$cnv = mb_ereg_replace("\xAD\xF1", "¢á", $cnv);		// ¢á
	$cnv = mb_ereg_replace("\xAD\xF2", "¢é", $cnv);		// ¢é
	$cnv = mb_ereg_replace("\xAD\xF3", "¢é", $cnv);		// ­ó
	$cnv = mb_ereg_replace("\xAD\xF4", "¦²", $cnv);		// ­ô
	$cnv = mb_ereg_replace("\xAD\xF5", "¢å", $cnv);		// ¢å
	$cnv = mb_ereg_replace("\xAD\xF6", "¢Ý", $cnv);		// ¢Ý
	$cnv = mb_ereg_replace("\xAD\xF7", "¢Ü", $cnv);		// ¢Ü
	$cnv = mb_ereg_replace("\xAD\xF8", "¨¦", $cnv);		// ­ø
	$cnv = mb_ereg_replace("\xAD\xF9", "¦¤", $cnv);		// ­ù
	$cnv = mb_ereg_replace("\xAD\xFA", "¢è", $cnv);		// ¢è
	$cnv = mb_ereg_replace("\xAD\xFB", "¢Á", $cnv);		// ¢Á
	$cnv = mb_ereg_replace("\xAD\xFC", "¢À", $cnv);		// ¢À
	$cnv = mb_ereg_replace("\xFC\xF1", "i", $cnv);		// i	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF2", "ii", $cnv);		// ii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF3", "iii", $cnv);	// iii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF4", "iv", $cnv);		// iv	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF5", "v", $cnv);		// v	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF6", "vi", $cnv);		// vi	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF7", "vii", $cnv);	// vii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF8", "viii", $cnv);	// viii	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xF9", "ix", $cnv);		// ix	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	$cnv = mb_ereg_replace("\xFC\xFA", "x", $cnv);		// x	¡Ê¥í¡¼¥Þ¿ô»ú¾®Ê¸»ú¡Ë
	return $cnv;
}

// ------------------------------------------------------------
// µ¡¼ï°ÍÂ¸Ê¸»ú¥Á¥§¥Ã¥¯
// (EUC-JP¡§Âè°ì¿å½à¡¢ÂèÆó¿å½à¤Î¤ßµöÍÆ)
// ------------------------------------------------------------
function IzonSearch( $str ) {

	// £³¥Ð¥¤¥ÈÊ¸»ú¡ÊJIS X 212 Êä½õ´Á»ú¡Ë¤¬´Þ¤Þ¤ì¤Æ¤¤¤¿¤é¥¨¥é¡¼
	// ¢¨Êä½õ´Á»ú¤¬¤½¤Î¤Þ¤ÞÁ÷¿®¤µ¤ì¤Æ¤­¤¿¾ì¹ç¤Ï¡¢¤³¤³¤Ç¥Õ¥Ã¥¯¤µ¤ì¤Þ¤¹
	// ¡ÊIE°Ê³°¤Î¥Ö¥é¥¦¥¶¤«¤é¤ÎÁ÷¿®¤ä¡¢CSV¥Õ¥¡¥¤¥ë¥¢¥Ã¥×¥í¡¼¥ÉÅù¡Ë
	if (preg_match('/(\x8F[\xA1-\xFE][\xA1-\xFE])/', $str)) {
		return false;
	}
	
	// ¥Ñ¡¼¥»¥ó¥È¥¨¥ó¥³¡¼¥É¤µ¤ì¤¿£³¥Ð¥¤¥ÈÊ¸»ú¡ÊJIS X 212 Êä½õ´Á»ú¡Ë¤¬´Þ¤Þ¤ì¤Æ¤¤¤¿¤é¥¨¥é¡¼
	// ¢¨IE¤Ê¤É¤«¤é¡¢Êä½õ´Á»ú¤¬¥¨¥ó¥³¡¼¥É¤µ¤ì¤ÆÁ÷¿®¤µ¤ì¤Æ¤­¤¿¾ì¹ç¤Ï¡¢¤³¤³¤Ç¥Õ¥Ã¥¯¤µ¤ì¤Þ¤¹
	// ¡ÊÎã¡Ë¡Ö&#28583;¡×¡Ö&AElig;¡×
	if (preg_match('/(&#[0-9]{1,};|&[a-zA-Z]{1,};)/', $str)) {
		return false;
	}

	// È¾³Ñ¥«¥Ê¤òÁ´³Ñ¥«¥Ê¤ËÊÑ´¹¡ÊÈ¾³Ñ¥«¥Ê¤¬º®ºß¤·¤Æ¤¤¤ë¤È¡¢Á´³ÑÊ¸»úÈ´¤­½Ð¤·¤Ë¼ºÇÔ¤¹¤ë¤¿¤á¡Ë	2007/08/13 add Y.Matsukawa
	$w_str = mb_convert_kana($str, 'K');

	// Á´³ÑÊ¸»ú¤ÎÈ´¤­½Ð¤·
	//preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $str, $matchword );	2007/08/13 mod Y.Matsukawa
	preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $w_str, $matchword );

	for ( $i=0; $i < count( $matchword[0] ) ; $i++) {
		if ( $matchword[0][$i] ) {
			// EUC-JP  Âè°ì¿å½à¡¢ÂèÆó¿å½à¤ÎÊ¸»ú¥Á¥§¥Ã¥¯
			if ( ! preg_match( '/^(([\xA1-\xA8]|[\xB0-\xF4])[\xA1-\xFE])*$/', $matchword[0][$i]) ) {
				return false;
			}
		}
	}
	return true;
}

// ------------------------------------------------------------
// »ÈÍÑÉÔ²Äµ­¹æ¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidKigou( $target ) {
	if ( $target ) {
		// ¡Ö"¡×¡Ö<¡×¡Ö>¡×¡Ö\¡×¡Ö,¡×¡Ö'¡×¡Ö`¡×
		//if ( preg_match( '/["<>\\\\,\']/', $target ) ) {	2007/08/15 mod Y.Matsukawa
		if ( preg_match( '/["<>\\\\,\'\`]/', $target ) ) {
			return false;
		}
	}
	return true;
}

// ------------------------------------------------------------
// µòÅÀID¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidKyotenid( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ){
		$err_msg  =  'Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( ! ctype_alnum( $target ) ) {
		$err_msg  =  '£±£µ·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( strlen( $target ) > 15 ) {
		$err_msg  =  '£±£µ·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	return true;
}

// ------------------------------------------------------------
// ¥¢¥¤¥³¥óID¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidIconid( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ){
		$err_msg  =  'Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( ! ctype_alnum( $target ) ) {
		$err_msg  =  '£µ·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( strlen( $target ) > 5 ) {
		$err_msg  =  '£µ·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	return true;
}

// ------------------------------------------------------------
// ¥¢¥¤¥³¥óÌ¾¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidIconName( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ) {
		$err_msg  =  'Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( strlen( $target ) > 100 ) {
		$err_msg  =  'Á´³Ñ£µ£°Ê¸»ú°ÊÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  'µ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	return true;
}

// ------------------------------------------------------------
// °ÞÅÙ·ÐÅÙ¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidLatlon( $target, &$err_msg, $latlon ) {
	$err_msg  =  null;
	if ( $target == '' ){  // null ¤Ç¤âOK
		return true;
	}
	if ( ! ctype_digit( $target ) ) {
		$err_msg  =  '£¸¡Á£¹·å¤ÎÈ¾³Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	/*
	 > ºÇËÌÃ¼
	 > 164203300,528910590
	 > ¡ÊE146¡ë55¡ì10.59¡íN45¡ë36¡ì43.30¡í¡Ë
	 >
	 > ºÇÆîÃ¼
	 >  86465690,442596310
	 > ¡ÊE122¡ë56¡ì36.31¡íN24¡ë01¡ì05.69¡í¡Ë
	 */
	if ( $latlon == 'LAT' ) {
		if ( $target < 86465690 || $target > 164203300 ) {
			$err_msg = '¡Ö86465690 (N24¡ë01¡ì05.69¡É) ¡Á'
					 . ' 164203300 (N45¡ë36¡ì43.30¡É)¡×'
					 . '¤ÎÈÏ°ÏÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
			return false;
		}
	} else if ( $latlon == 'LON' ) {
		if ( $target < 442596310 || $target > 528910590 ) {
			$err_msg = '¡Ö442596310 (E122¡ë56¡ì36.31¡É) ¡Á'
					 . ' 528910590 (E146¡ë55¡ì10.59¡É)¡×'
					 . '¤ÎÈÏ°ÏÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
			return false;
		}
	}
	return true;
}

// ------------------------------------------------------------
// NAME¡¿ADDR¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidAddrName( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ) {
		$err_msg  =  'Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( strlen( $target ) > 128 ) {
		$err_msg  =  'Á´³Ñ£¶£´Ê¸»ú°ÊÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  'µ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	return true;
}

// add 2009/08/27 Y.Matsukawa
// ------------------------------------------------------------
// ½Ì¼Ü¹àÌÜ
// ------------------------------------------------------------
function ValidLvlP($target, &$err_msg) {
	global $MAP_SCALE_P;
	$err_msg = null;
	if ($target == '') return true;
	if (!ctype_digit($target) || !isset($MAP_SCALE_P[$target])) {
		$err_msg = '1¡Á18¤ÎÈ¾³Ñ¿ô»ú¤òÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	return true;
}
function ValidLvlM($target, &$err_msg) {
	global $MAP_SCALE_M;
	$err_msg = null;
	if ($target == '') return true;
	if (!ctype_digit($target) || !isset($MAP_SCALE_M[$target])) {
		$err_msg = '1¡Á9¤ÎÈ¾³Ñ¿ô»ú¤òÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	return true;
}

// add 2009/03/05 Y.Matsukawa
////////////////////////////////////////////////////////////////////////
// ´ë¶È¥æ¡¼¥¶¡¼
////////////////////////////////////////////////////////////////////////
// ¥æ¡¼¥¶¡¼ID
function ValidCorpUserid( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼ID¤¬Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼ID¤Ëµ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼ID¤Ë»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! ctype_alnum( $target ) ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼ID¤Ï£¸·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( strlen( $target ) > 8 ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼ID¤Ï£¸·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	return true;
}
// ¥Ñ¥¹¥ï¡¼¥É
function ValidCorpUserPassword( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ) {
		$err_msg  =  '¥Ñ¥¹¥ï¡¼¥É¤¬Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  '¥Ñ¥¹¥ï¡¼¥É¤Ëµ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '¥Ñ¥¹¥ï¡¼¥É¤Ë»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! ctype_alnum( $target ) ) {
		$err_msg  =  '¥Ñ¥¹¥ï¡¼¥É¤Ï£¶·å¡Á£±£°·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( strlen( $target ) < 6 || strlen( $target ) > 10 ) {
		$err_msg  =  '¥Ñ¥¹¥ï¡¼¥É¤Ï£¶·å¡Á£±£°·å°ÊÆâ¤ÎÈ¾³Ñ±Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	return true;
}
// ¥æ¡¼¥¶¡¼Ì¾
function ValidCorpUserName( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼Ì¾¤¬Ì¤ÆþÎÏ¤Ç¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼Ì¾¤Ëµ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! ValidKigou( $target ) ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼Ì¾»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( strlen( $target ) > 100 ) {
		$err_msg  =  '¥æ¡¼¥¶¡¼Ì¾¤ÏÁ´³Ñ£µ£°Ê¸»ú°ÊÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	return true;
}

// ------------------------------------------------------------
// Ê¸»úÎó¹àÌÜ¥Á¥§¥Ã¥¯
// (VAL_KBN='C' , HTML_TAG_FLG='0')
// ------------------------------------------------------------
function ValidKbnChar( $target, &$err_msg ) {
	global $TAG_WHITELIST;
	$err_msg  =  null;
	if ( $target == '' ) return true;		// add 2009/04/24 Y.Matsukawa
	if ( strlen( $target ) > 1000 ) {
		$err_msg  =  'Á´³Ñ£µ£°£°Ê¸»ú°ÊÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	// ¡Ö,¡×(¥«¥ó¥Þ)ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , ','  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// ¡Ö'¡×(¥·¥ó¥°¥ë¥¯¥©¡¼¥Æ¡¼¥·¥ç¥ó)ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , "'"  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// ¡Ö\¡×ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , "\\"  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// ¡Ö`¡×ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , '`'  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// HTML¥¿¥°¥Á¥§¥Ã¥¯(br,b)
	if (ValidHtmlTag($target, $TAG_WHITELIST) == false) {
		$err_msg  =  '»ÈÍÑ½ÐÍè¤Ê¤¤¥¿¥°¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  'µ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	return true;
}

// ------------------------------------------------------------
// Ê¸»úÎó¹àÌÜ¥Á¥§¥Ã¥¯
// (VAL_KBN='C' , HTML_TAG_FLG='1')
// ------------------------------------------------------------
function ValidKbnChar2( $target, &$err_msg ) {
	global $RICH_TAG_WHITELIST;
	$err_msg  =  null;
	if ( $target == '' ) return true;		// add 2009/04/24 Y.Matsukawa
	if ( strlen( $target ) > 1000 ) {
		$err_msg  =  'Á´³Ñ£µ£°£°Ê¸»ú°ÊÆâ¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	// ¡Ö,¡×(¥«¥ó¥Þ)ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , ','  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// ¡Ö'¡×(¥·¥ó¥°¥ë¥¯¥©¡¼¥Æ¡¼¥·¥ç¥ó)ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , "'"  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// ¡Ö\¡×ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , "\\"  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// ¡Ö`¡×ÆþÎÏ¶Ø»ß
	if ( ! ( strpos( $target , '`'  ) === false ) ) {
		$err_msg  =  '»ÈÍÑÉÔ²Äµ­¹æ¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	// HTML¥¿¥°¥Á¥§¥Ã¥¯(a,img,br,b)
	if (ValidHtmlTag($target, $RICH_TAG_WHITELIST) == false) {
		$err_msg  =  '»ÈÍÑ½ÐÍè¤Ê¤¤¥¿¥°¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	if ( ! IzonSearch( $target ) ) {
		$err_msg  =  'µ¡¼ï°ÍÂ¸Ê¸»ú¤¬´Þ¤Þ¤ì¤Æ¤¤¤Þ¤¹';
		return false;
	}
	return true;
}


// ------------------------------------------------------------
// ÆüÉÕ¥Á¥§¥Ã¥¯
// ¡Ê³«»ÏÆüor½ªÎ»Æü¤Îº¹Ê¬¥Á¥§¥Ã¥¯¤Ç¡¢2038/01/19°Ê¹ß¤Ï
//  Àµ¾ï¤Ë¥Á¥§¥Ã¥¯¤¬½ÐÍè¤Ê¤¤¡Êmktime¤Ç¥Þ¥¤¥Ê¥¹¤Ë¤Ê¤ë¡Ë°Ù¡¢
//  ¤È¤ê¤¢¤¨¤º¡¢2037Ç¯¤ÇÂÇ¤Á»ß¤á¡Ë
// ------------------------------------------------------------
function ValidDate( $target_y, $target_m, $target_d, &$err_msg ) {
	$err_msg  =  null;
	if ( $target_y == null ) {
		if ( $target_m == null ) {
			if ( $target_d == null ) {
				$err_msg  = 'NODATE';
				return  false;
			}
			$err_msg  = 'ÉÔÀµ¤ÊÆüÉÕ¤Ç¤¹';
		}
	}
	if ( $target_m == '' ) {
		$err_msg  = 'ÉÔÀµ¤ÊÆüÉÕ¤Ç¤¹';
		return  false;
	}
	if ( $target_d == '' ) {
		$err_msg  = 'ÉÔÀµ¤ÊÆüÉÕ¤Ç¤¹';
		return  false;
	}
	// del 2009/04/24 Y.Matsukawa [
	//	if ( ! ValidKigou( $target_y ) ) {
	//		$err_msg  =  'Ç¯¤Ï£´·å¤ÎÈ¾³Ñ¿ô»ú(1970¡Á2037)¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
	//		return false;
	//	}
	// del 2009/04/24 Y.Matsukawa ]
	if ( ! ctype_digit( $target_y ) ) {
		$err_msg  =  'Ç¯¤Ï£´·å¤ÎÈ¾³Ñ¿ô»ú(1970¡Á2037)¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return  false;
	}
	if ( strlen( $target_y ) != 4 ) {
		$err_msg  =  'Ç¯¤Ï£´·å¤ÎÈ¾³Ñ¿ô»ú(1970¡Á2037)¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return  false;
	}
	//if ( $target_y > 2037 || $target_y < 2000 ) {
	if ( $target_y > 2037 || $target_y < 1970 ) {	// 2007/09/11 mod K.Masuda
		$err_msg  =  'Ç¯¤Ï1970¡Á2037¤Î´Ö¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return  false;
	}
	if ( ! checkdate( $target_m , $target_d , $target_y ) ) {
		$err_msg  =  'Â¸ºß¤·¤Ê¤¤ÆüÉÕ¤Ç¤¹';
		return  false;
	}
	return  true;
}

// ------------------------------------------------------------
// »þ¹ï¥Á¥§¥Ã¥¯
// ------------------------------------------------------------
function ValidHour( $target, &$err_msg ) {
	$err_msg  =  null;
	if ( $target == '' ){
		$err_msg  =  '»þ´Ö¤Ï¡Ö00¡Á23¡×¤ÎÈ¾³Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( ! ctype_digit( $target ) ) {
		$err_msg  =  '»þ´Ö¤Ï¡Ö00¡Á23¡×¤ÎÈ¾³Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	if ( $target < 0 || $target > 23 ) {
		$err_msg  =  '»þ´Ö¤Ï¡Ö00¡Á23¡×¤ÎÈ¾³Ñ¿ô»ú¤ÇÆþÎÏ¤·¤Æ¤¯¤À¤µ¤¤';
		return false;
	}
	return true;
}

// ------------------------------------------------------------
// »ÈÍÑÉÔ²ÄHTML¥¿¥°¥Á¥§¥Ã¥¯¡Ê¢¨ºÆµ¢´Ø¿ô¡Ë
// ------------------------------------------------------------
function ValidHtmlTag($target, &$tag_wlist) {
	$p = strpos($target, '<');
	if ($p === false) return true;
	$valid = false;
	foreach ($tag_wlist as $tag) {
		if (strcasecmp($tag, substr($target, $p, strlen($tag))) == 0) {
			$valid = true;
			break;
		}
	}
	if (!$valid) return false;
	$target_substr = substr($target, $p + 1);
	return ValidHtmlTag($target_substr, $tag_wlist, $errmsg);
}

// ------------------------------------------------------------
// ÆüÉÕÊÑ´¹¡ÊÉ½¼¨·Á¼°)
//   ¥Ñ¥é¥á¡¼¥¿ :  (IN   )  -- ÆüÉÕ('YYMMDDHHMMSS')
//                 (IN   )  -- Ê¬É½¼¨¥Õ¥é¥°
//   Ìá¤êÃÍ     :   DATE¥Ç¡¼¥¿('YYYYÇ¯MM·îDDÆüHH»þ')
//                    or 
//                  DATE¥Ç¡¼¥¿('YYYYÇ¯MM·îDDÆüHH»þSSÊ¬')
// ------------------------------------------------------------
function DateLabel( $date_org , $min_on ) {
	$str   =          substr( $date_org , 0 , 4 );
	$str  .=  'Ç¯ ' . substr( $date_org , 4 , 2 );
	$str  .=  '·î'  . substr( $date_org , 6 , 2 );
	$str  .=  'Æü ' . substr( $date_org , 8 , 2 );
	$str  .=  '»þ' ;
	if ( $min_on ) {
		$str  .=  substr( $date_org , 10 , 2 ) . 'Ê¬' ;
	}
	return $str;
}

// ------------------------------------------------------------
// ÆüÉÕÊÑ´¹2¡ÊÉ½¼¨·Á¼°)
//   ¥Ñ¥é¥á¡¼¥¿ :  (IN   )  -- ÆüÉÕ('YYMMDDHHMMSS')
//   Ìá¤êÃÍ     :   DATE¥Ç¡¼¥¿('YYYY/MM/DD')
// ------------------------------------------------------------
function DateLabel2( $date_org ) {
	$str   =        substr( $date_org , 0 , 4 );
	$str  .=  '/' . substr( $date_org , 4 , 2 );
	$str  .=  '/' . substr( $date_org , 6 , 2 );
	return $str;
}

// ------------------------------------------------------------
// ÆüÉÕÊÑ´¹¡ÊÇ¯¡¿·î¡¿Æü¤ËÊ¬²ò¡Ë
//   ¥Ñ¥é¥á¡¼¥¿ :  (IN   )  -- ÆüÉÕ('/'¤Ê¤·)
//                 (OUT  )  -- Ç¯
//                 (OUT  )  -- ·î
//                 (OUT  )  -- Æü
//                 (OUT  )  -- »þ
// ------------------------------------------------------------
function DateSplit( $date_org , &$date_y , &$date_m , &$date_d , &$date_h) {
	$date_y  =  substr( $date_org  , 0 , 4 );
	$date_m  =  substr( $date_org  , 4 , 2 );
	$date_d  =  substr( $date_org  , 6 , 2 );
	$date_h  =  substr( $date_org  , 8 , 2 );
	return;
}

// ------------------------------------------------------------
// ¥Þ¥Ã¥Á¥ó¥°¥ì¥Ù¥ëÊÑ´¹(¥Þ¥Ã¥Á¥ó¥°¥Õ¥é¥° ¢ª ¿ôÃÍ)
// ------------------------------------------------------------
function MlevelConv( $mlevel_kbn, &$mlevel_str ) {
	if ( $mlevel_kbn == 'KEN' ) {           // ÅÔÆ»ÉÜ¸©
		$buf  =  1;
		$mlevel_str  =  'ÅÔÆ»ÉÜ¸©¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'SHK' ) {    // »Ô¶èÄ®Â¼
		$buf  =  2;
		$mlevel_str  =  '»Ô¶èÄ®Â¼¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'OAZ' ) {    // Âç»ú
		$buf  =  3;
		$mlevel_str  =  'Âç»ú¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'AZC' ) {    // »úÃúÌÜ
		$buf  =  4;
		$mlevel_str  =  '»úÃúÌÜ¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'GIK' ) {    // ³¹¶è
		$buf  =  5;
		$mlevel_str  =  '³¹¶è¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'TBN' ) {    // ÃÏÈÖ
		$buf  =  6;
		$mlevel_str  =  'ÃÏÈÖ¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'EBN' ) {    // »ÞÈÖ
		$buf  =  7;
		$mlevel_str  =  '»ÞÈÖ¥ì¥Ù¥ë';
	} else if ( $mlevel_kbn == 'NO MATCH' ) {  // ¥Þ¥Ã¥Á¥ó¥°¼ºÇÔ
		$buf  =  9;
		$mlevel_str  =  '¥Þ¥Ã¥Á¥ó¥°¼ºÇÔ';
	} else {
		$buf  =  0;
		$mlevel_str  =  'ÊÔ½¸ºÑ';
	}
	return $buf ;
}

// ------------------------------------------------------------
// ¥Þ¥Ã¥Á¥ó¥°¥ì¥Ù¥ëÊÑ´¹
// (¥Þ¥Ã¥Á¥ó¥°¥ì¥Ù¥ë ¢ª ¥Þ¥Ã¥Á¥ó¥°¥Õ¥é¥°Ê¸»úÎó)
// ------------------------------------------------------------
function MlevelStrConv( $mlevel ) {
	if ( $mlevel == '0' ) {           // ÊÔ½¸ºÑ
		$buf  =  'ÊÔ½¸ºÑ';
	} else if ( $mlevel == '1' ) {    // ÅÔÆ»ÉÜ¸©
		$buf  =  'ÅÔÆ»ÉÜ¸©¥ì¥Ù¥ë';
	} else if ( $mlevel == '2' ) {    // »Ô¶èÄ®Â¼
		$buf  =  '»Ô¶èÄ®Â¼¥ì¥Ù¥ë';
	} else if ( $mlevel == '3' ) {    // Âç»ú
		$buf  =  'Âç»ú¥ì¥Ù¥ë';
	} else if ( $mlevel == '4' ) {    // »úÃúÌÜ
		$buf  =  '»úÃúÌÜ¥ì¥Ù¥ë';
	} else if ( $mlevel == '5' ) {    // ³¹¶è
		$buf  =  '³¹¶è¥ì¥Ù¥ë';
	} else if ( $mlevel == '6' ) {    // ÃÏÈÖ
		$buf  =  'ÃÏÈÖ¥ì¥Ù¥ë';
	} else if ( $mlevel == '7' ) {    // »ÞÈÖ
		$buf  =  '»ÞÈÖ¥ì¥Ù¥ë';
	} else if ( $mlevel == '9' ) {    // ¥Þ¥Ã¥Á¥ó¥°¼ºÇÔ
		$buf  =  '¥Þ¥Ã¥Á¥ó¥°¼ºÇÔ';
	} else {
		$buf  =  ' ';
	}
	return $buf ;
}

// ------------------------------------------------------------
//* Ê¸»úÎóÈ½Äê(µ­¹æ)
// ------------------------------------------------------------
function zdc_ctype_kigou( $string ){
	return	( preg_match( '/[\!-\/\:-\@\[-\`\{-\~]/',$string ) ) ? true : false;
}

?>
