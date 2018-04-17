<?php
// ------------------------------------------------------------
// ÄêµÁ¥Õ¥¡¥¤¥ë »ÈÍÑ¤¹¤ëJS¤À¤±¤ò¥í¡¼¥É¤¹¤ë
// 
// ³«È¯ÍúÎò
// 2008/10/22 Y.Matsukawa	¿·µ¬ºîÀ®
// 2009/07/22 Y.Matsukawa	ÈóÂÐ±þ¥Ö¥é¥¦¥¶¤Ç¤âÆ°ºî
// 2011/07/05 Y.Nakajima	VM²½¤ËÈ¼¤¦apache,phpVerUPÂÐ±þ²þ½¤
// ------------------------------------------------------------

//mod 2011/07/05 Y.Nakajima
if (!isset($D_SEVICE_TYPE)) $D_SEVICE_TYPE = "";
switch ($D_SEVICE_TYPE) {
	//Light
	case 'L':
		//¢¨»È¤ï¤Ê¤¤¤â¤Î¤Ï¥³¥á¥ó¥È¥¢¥¦¥È
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				¢¨É¬¿Ü
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				¢¨É¬¿Ü
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		¥ë¡¼¥ÈÃµº÷
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		¥ë¡¼¥ÈÃµº÷
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				ºÇ´ó±Ø¡¢ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//		//$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		ºÇ´ó±Ø
		//		//$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			ºÇ´ó»ÜÀß
		//		//$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	Ï©Àþ¿Þ
		//		//$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			ÃÏ°è¿Þ
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				¢¨É¬¿Ü
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				¢¨É¬¿Ü
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		¥ë¡¼¥ÈÃµº÷
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		¥ë¡¼¥ÈÃµº÷
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				ºÇ´ó±Ø¡¢ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		ºÇ´ó±Ø
		//$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			ºÇ´ó»ÜÀß
		//$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	Ï©Àþ¿Þ
		//$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			ÃÏ°è¿Þ
		// add 2011/02/10 Y.Matsukawa ]
		break;
	//Maplink
	case 'N':
		//¢¨»È¤ï¤Ê¤¤¤â¤Î¤Ï¥³¥á¥ó¥È¥¢¥¦¥È
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				¢¨É¬¿Ü
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				¢¨É¬¿Ü
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		¥ë¡¼¥ÈÃµº÷
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		¥ë¡¼¥ÈÃµº÷
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				ºÇ´ó±Ø¡¢ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//		$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		ºÇ´ó±Ø
		//		$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			ºÇ´ó»ÜÀß
		//		//$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	Ï©Àþ¿Þ
		//		//$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			ÃÏ°è¿Þ
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				¢¨É¬¿Ü
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				¢¨É¬¿Ü
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		¥ë¡¼¥ÈÃµº÷
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		¥ë¡¼¥ÈÃµº÷
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				ºÇ´ó±Ø¡¢ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		ºÇ´ó±Ø
		$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			ºÇ´ó»ÜÀß
		//$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	Ï©Àþ¿Þ
		//$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			ÃÏ°è¿Þ
		// add 2011/02/10 Y.Matsukawa ]
		break;
	//Standard
	default:
		//¢¨»È¤ï¤Ê¤¤¤â¤Î¤Ï¥³¥á¥ó¥È¥¢¥¦¥È
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				¢¨É¬¿Ü
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				¢¨É¬¿Ü
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		¥ë¡¼¥ÈÃµº÷
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		¥ë¡¼¥ÈÃµº÷
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				ºÇ´ó±Ø¡¢ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//		$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		ºÇ´ó±Ø
		//		$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			ºÇ´ó»ÜÀß
		//		$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	Ï©Àþ¿Þ
		//		$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			ÃÏ°è¿Þ
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				¢¨É¬¿Ü
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				¢¨É¬¿Ü
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		¥ë¡¼¥ÈÃµº÷
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		¥ë¡¼¥ÈÃµº÷
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				ºÇ´ó±Ø¡¢ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			ºÇ´ó»ÜÀß¤Ç»ÈÍÑ
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		ºÇ´ó±Ø
		$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			ºÇ´ó»ÜÀß
		$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	Ï©Àþ¿Þ
		$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			ÃÏ°è¿Þ
		// add 2011/02/10 Y.Matsukawa ]
}
//»È¤ï¤Ê¤¤JS¤ò½üµî
//¢¨PHP4¤Ë¤Ïarray_intersect_key¤¬Ìµ¤¤¤Î¤Ç¼«Ê¬¤Ç¼ÂÁõ
function zdc_array_intersect_key(&$array1, &$array2) {
	$array0 = array();
	foreach ($array1 as $key1=>$value1) {
		if (isset($array2[$key1])) {
			$array0[$key1] = $value1;
		}
	}
	return $array0;
}
//$D_JSAPI = zdc_array_intersect_key($D_JSAPI, $D_REQ_JSAPI);		del 2011/02/10 Y.Matsukawa

$D_JSAPI["zdccommon"] .= implode(',', $D_REQ_JSAPI);		// add 2011/02/10 Y.Matsukawa

// ÈóÂÐ±þ¥Ö¥é¥¦¥¶¤Ç¤âÆ°ºî		add 2009/07/22 Y.Matsukawa
if (!isset($D_NA_UNSUPPORTED_BROWSER)) {
	foreach ($D_JSAPI as $key1=>$value1) {
		$D_JSAPI[$key1] = $value1."&force=1";
	}
	$D_JSAPI_UA_CHECK_CGI .= "&force=1";
}

?>
