<?php
// ------------------------------------------------------------
// ����ե����� ���Ѥ���JS����������ɤ���
// 
// ��ȯ����
// 2008/10/22 Y.Matsukawa	��������
// 2009/07/22 Y.Matsukawa	���б��֥饦���Ǥ�ư��
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// ------------------------------------------------------------

//mod 2011/07/05 Y.Nakajima
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

$D_JSAPI["zdccommon"] .= implode(',', $D_REQ_JSAPI);		// add 2011/02/10 Y.Matsukawa

// ���б��֥饦���Ǥ�ư��		add 2009/07/22 Y.Matsukawa
if (!isset($D_NA_UNSUPPORTED_BROWSER)) {
	foreach ($D_JSAPI as $key1=>$value1) {
		$D_JSAPI[$key1] = $value1."&force=1";
	}
	$D_JSAPI_UA_CHECK_CGI .= "&force=1";
}

?>