<?php
// ------------------------------------------------------------
// ����ե����� ���Ѥ���JS����������ɤ���
// 
// ��ȯ����
// 2008/10/22 Y.Matsukawa	��������
// 2009/07/22 Y.Matsukawa	���б��֥饦���Ǥ�ư��
// 2011/07/07 H.Osamoto		�ޥĥ�����API2.0�б���
// 2011/10/03 Y.nakajima	VM����ȼ��apache,phpVerUP�б�����  
// ------------------------------------------------------------

//mod 2011/10/03 Y.Nakajima
if (!isset($D_SEVICE_TYPE)) $D_SEVICE_TYPE = "";
switch ($D_SEVICE_TYPE) {
	//Light
	case 'L':
		//���Ȥ�ʤ���Τϥ����ȥ�����
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				��ɬ��
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				��ɬ��
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		�롼��õ��
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		�롼��õ��
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				�Ǵ�ء��Ǵ���ߤǻ���
		//		//$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			�Ǵ���ߤǻ���
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		�Ǵ��
		//		//$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			�Ǵ����
		//		//$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	ϩ����
		//		//$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			�ϰ��
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				��ɬ��
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				��ɬ��
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		�롼��õ��
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		�롼��õ��
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				�Ǵ�ء��Ǵ���ߤǻ���
		//$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			�Ǵ���ߤǻ���
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		�Ǵ��
		//$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			�Ǵ����
		//$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	ϩ����
		//$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			�ϰ��
		// add 2011/02/10 Y.Matsukawa ]
		break;
	//Maplink
	case 'N':
		//���Ȥ�ʤ���Τϥ����ȥ�����
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				��ɬ��
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				��ɬ��
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		�롼��õ��
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		�롼��õ��
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				�Ǵ�ء��Ǵ���ߤǻ���
		//		$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			�Ǵ���ߤǻ���
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		�Ǵ��
		//		$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			�Ǵ����
		//		//$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	ϩ����
		//		//$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			�ϰ��
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				��ɬ��
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				��ɬ��
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		�롼��õ��
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		�롼��õ��
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				�Ǵ�ء��Ǵ���ߤǻ���
		$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			�Ǵ���ߤǻ���
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		�Ǵ��
		$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			�Ǵ����
		//$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	ϩ����
		//$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			�ϰ��
		// add 2011/02/10 Y.Matsukawa ]
		break;
	//Standard
	default:
		//���Ȥ�ʤ���Τϥ����ȥ�����
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				��ɬ��
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				��ɬ��
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		�롼��õ��
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		�롼��õ��
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				�Ǵ�ء��Ǵ���ߤǻ���
		//		$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			�Ǵ���ߤǻ���
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		�Ǵ��
		//		$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			�Ǵ����
		//		$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	ϩ����
		//		$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			�ϰ��
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				��ɬ��
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				��ɬ��
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		�롼��õ��
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		�롼��õ��
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				�Ǵ�ء��Ǵ���ߤǻ���
		$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			�Ǵ���ߤǻ���
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		�Ǵ��
		$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			�Ǵ����
		$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	ϩ����
		$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			�ϰ��
		// add 2011/02/10 Y.Matsukawa ]
		// add 2011/07/07 H.Osamoto [
		$D_REQ_JSAPI_V2["zdcmap"]          = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI_V2["shape"]           = 'shape.js';			//ZDC.Polyline			�롼������
		$D_REQ_JSAPI_V2["geo"]             = 'geo.js';				//������ȥ�å�
		$D_REQ_JSAPI_V2["submap"]          = 'submap.js';			//ZDC.Submap			���֥ޥå�
		$D_REQ_JSAPI_V2["control"]         = 'control.js';			//ZDC.Control			�Ͽޥ���ȥ�����
		$D_REQ_JSAPI_V2["usercontrol"]     = 'usercontrol.js';		//ZDC.UserControl		�桼������ȥ��������
		$D_REQ_JSAPI_V2["userwidget"]      = 'userwidget.js';		//ZDC.UserWidget		�桼���������åȺ���
		$D_REQ_JSAPI_V2["search"]          = 'search.js';			//ZDC.Search			�����ʽ��긡����POI���������ٷ��ٸ������롼��õ��������¾��
		$D_REQ_JSAPI_V2["areamap"]         = 'areamap.js';			//ZDC.AreaMap			�ϰ��
		$D_REQ_JSAPI_V2["railwaymap"]      = 'railwaymap.js';		//ZDC.RailwayMap		ϩ����
		// add 2011/07/07 H.Osamoto ]
}
//�Ȥ�ʤ�JS�����
//��PHP4�ˤ�array_intersect_key��̵���ΤǼ�ʬ�Ǽ���
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

//$D_JSAPI["zdccommon"] .= implode(',', $D_REQ_JSAPI);		// add 2011/02/10 Y.Matsukawa	// del 2011/07/07 H.osamoto

// mod 2011/10/03 Y.Nakajima [
if (isset($D_REQ_JSAPI_V2) && $D_REQ_JSAPI_V2 != "") {
	$D_JSAPI_v2["zdccommon"] .= implode(',', $D_REQ_JSAPI_V2);		// add 2011/07/07 H.osamoto
}
// mod 2011/10/03 Y.Nakajima ]

// ���б��֥饦���Ǥ�ư��		add 2009/07/22 Y.Matsukawa
// mod 2011/10/03 Y.Nakajima
if (!isset($D_NA_UNSUPPORTED_BROWSER) || (isset($D_NA_UNSUPPORTED_BROWSER) && !$D_NA_UNSUPPORTED_BROWSER)) {
	//	foreach ($D_JSAPI as $key1=>$value1) {
	//		$D_JSAPI[$key1] = $value1."&force=1";
	//	}
	//	$D_JSAPI_UA_CHECK_CGI .= "&force=1";
	foreach ($D_JSAPI_v2 as $key1=>$value1) {
		$D_JSAPI_v2[$key1] = $value1."&force=1";
	}
	// mod 2011/07/07 H.Osamoto ]
}

?>