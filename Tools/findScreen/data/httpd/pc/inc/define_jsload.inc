<?php
// ------------------------------------------------------------
// 定義ファイル 使用するJSだけをロードする
// 
// 開発履歴
// 2008/10/22 Y.Matsukawa	新規作成
// 2009/07/22 Y.Matsukawa	非対応ブラウザでも動作
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// ------------------------------------------------------------

//mod 2011/07/05 Y.Nakajima
if (!isset($D_SEVICE_TYPE)) $D_SEVICE_TYPE = "";
switch ($D_SEVICE_TYPE) {
	//Light
	case 'L':
		//※使わないものはコメントアウト
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				※必須
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				※必須
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		ルート探索
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		ルート探索
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				最寄駅、最寄施設で使用
		//		//$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			最寄施設で使用
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		最寄駅
		//		//$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			最寄施設
		//		//$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	路線図
		//		//$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			地域図
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				※必須
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				※必須
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		ルート探索
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		ルート探索
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				最寄駅、最寄施設で使用
		//$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			最寄施設で使用
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		最寄駅
		//$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			最寄施設
		//$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	路線図
		//$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			地域図
		// add 2011/02/10 Y.Matsukawa ]
		break;
	//Maplink
	case 'N':
		//※使わないものはコメントアウト
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				※必須
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				※必須
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		ルート探索
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		ルート探索
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				最寄駅、最寄施設で使用
		//		$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			最寄施設で使用
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		最寄駅
		//		$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			最寄施設
		//		//$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	路線図
		//		//$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			地域図
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				※必須
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				※必須
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		ルート探索
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		ルート探索
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				最寄駅、最寄施設で使用
		$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			最寄施設で使用
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		最寄駅
		$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			最寄施設
		//$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	路線図
		//$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			地域図
		// add 2011/02/10 Y.Matsukawa ]
		break;
	//Standard
	default:
		//※使わないものはコメントアウト
		// del 2011/02/10 Y.Matsukawa [
		//		$D_REQ_JSAPI["zdccommon"]       = 1;//ZdcCommon				※必須
		//		$D_REQ_JSAPI["zdcmap"]          = 1;//ZdcMap				※必須
		//		$D_REQ_JSAPI["zdcroute"]        = 1;//ZdcRouteSearch		ルート探索
		//		$D_REQ_JSAPI["zdcproute"]       = 1;//ZdcPRouteSearch		ルート探索
		//		$D_REQ_JSAPI["zdcshape"]        = 1;//ZdcShape				最寄駅、最寄施設で使用
		//		$D_REQ_JSAPI["zdcmapgeometric"] = 1;//ZdcGeometric			最寄施設で使用
		//		$D_REQ_JSAPI["neki"]            = 1;//ZdcNearStation		最寄駅
		//		$D_REQ_JSAPI["npoi"]            = 1;//ZdcNearPoi			最寄施設
		//		$D_REQ_JSAPI["searchrailway"]   = 1;//ZdcSearchRailwayMap	路線図
		//		$D_REQ_JSAPI["searchmap"]       = 1;//ZdcSearchMap			地域図
		// del 2011/02/10 Y.Matsukawa ]
		// add 2011/02/10 Y.Matsukawa [
		$D_REQ_JSAPI["zdccommon"]       = 'zdccommon.js';		//ZdcCommon				※必須
		$D_REQ_JSAPI["zdcmap"]          = 'zdcmap.js';			//ZdcMap				※必須
		$D_REQ_JSAPI["zdcroute"]        = 'zdcroute.js';		//ZdcRouteSearch		ルート探索
		$D_REQ_JSAPI["zdcproute"]       = 'zdcproute.js';		//ZdcPRouteSearch		ルート探索
		$D_REQ_JSAPI["zdcshape"]        = 'zdcshape.js';		//ZdcShape				最寄駅、最寄施設で使用
		$D_REQ_JSAPI["zdcmapgeometric"] = 'zdcmapgeometric.js';	//ZdcGeometric			最寄施設で使用
		$D_REQ_JSAPI["neki"]            = 'neki.js';			//ZdcNearStation		最寄駅
		$D_REQ_JSAPI["npoi"]            = 'npoi.js';			//ZdcNearPoi			最寄施設
		$D_REQ_JSAPI["searchrailway"]   = 'searchrosenzu.js';	//ZdcSearchRailwayMap	路線図
		$D_REQ_JSAPI["searchmap"]       = 'searchmap.js';		//ZdcSearchMap			地域図
		// add 2011/02/10 Y.Matsukawa ]
}
//使わないJSを除去
//※PHP4にはarray_intersect_keyが無いので自分で実装
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

// 非対応ブラウザでも動作		add 2009/07/22 Y.Matsukawa
if (!isset($D_NA_UNSUPPORTED_BROWSER)) {
	foreach ($D_JSAPI as $key1=>$value1) {
		$D_JSAPI[$key1] = $value1."&force=1";
	}
	$D_JSAPI_UA_CHECK_CGI .= "&force=1";
}

?>
