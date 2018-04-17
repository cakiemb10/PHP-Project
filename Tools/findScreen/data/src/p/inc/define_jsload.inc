<?php
// ------------------------------------------------------------
// ����ե����� ���Ѥ���JS����������ɤ���
// 
// ��ȯ����
// 2011/10/15 Y.Matsukawa	��������
// 2012/10/01 Y.Matsukawa	Maplink�б�
// 2012/11/06 H.Osamoto		ʬ���Ͽް��������б�
// 2013/10/02 Y.Matsukawa	Google Maps��
// 2014/10/08 Y.Matsukawa	�Ǵ��ؤ����Ǥ�յ�Υ�α�ɽ��
// 2015/10/20 N.Wada		�ܺٲ��̤�js��2�Ť��ɤ߹���Ǥ��ޤ��Զ�罤��
// 2016/05/02 N.Wada		Google Maps API���ɤ߹��ߤ�https���б�
// 2016/05/16 Y.Matsukawa	Google Maps API channel����
// 2016/08/15 Y.Matsukawa	Google�� ¬�Ϸ��Ѵ�������
// 2016/10/03 Y.Uesugi		VICS�б� �Ͽ޽ž�
// 2016/11/10 Y.Uesugi		Google Maps API��������
// 2017/02/23 N.Wada		ʣ��롼�ȸ���js����ɲ�
// ------------------------------------------------------------
$D_JS = array();
$D_REQ_JSAPI = array();
$D_REQ_JS = array();
// add 2013/10/02 Y.Matsukawa [
if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) {
	//$D_GOOGLEMAPS_JS = 'http://maps.google.com/maps/api/js?v=3&sensor=false';	mod 2016/05/02 N.Wada
	//$D_GOOGLEMAPS_JS = $protocol.'://maps.google.com/maps/api/js?v=3&sensor=false';		mod 2016/05/16 Y.Matsukawa
	$D_GOOGLEMAPS_JS = $protocol.'://maps.google.com/maps/api/js?v=3';
	if (isset($D_GOOGLEMAPS_CID) && $D_GOOGLEMAPS_CID)
		$D_GOOGLEMAPS_JS .= '&client='.$D_GOOGLEMAPS_CID;
	// add 2016/05/16 Y.Matsukawa [
	if (isset($D_GOOGLEMAPS_CHANNEL) && $D_GOOGLEMAPS_CHANNEL)
		$D_GOOGLEMAPS_JS .= '&channel='.$D_GOOGLEMAPS_CHANNEL;
	// add 2016/05/16 Y.Matsukawa ]
}
// add 2013/10/02 Y.Matsukawa ]

// add 2016/11/10 Y.Uesugi [
if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) {
	$D_GOOGLEMAPS_API_KEY_JS = $protocol.'://maps.googleapis.com/maps/api/js?key=';
	$D_GOOGLEMAPS_API_KEY_JS .= $D_GOOGLEMAPS_API_KEY;
}
// add 2016/11/10 Y.Uesugi ]

switch ($script_name) {
	default:
		break;
	case 'index.htm':
	case 'top.htm':
		break;
	case 'search_area.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'areamap.js';			//ZDC.AreaMap			�ϰ��
		break;
	case 'search_rail.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'railwaymap.js';		//ZDC.RailwayMap		ϩ����
		break;
	case 'nmap.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'shape.js';			//ZDC.Oval							add 2014/10/08 Y.Matsukawa
		$D_REQ_JSAPI[] = 'geo.js';				//������ȥ�å�
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			�Ͽޥ���ȥ�����
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		�桼������ȥ��������
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		�桼���������åȺ���
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			����		add 2014/10/08 Y.Matsukawa
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/11/06 H.Osamoto [
	case 'nmap_print.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'geo.js';				//������ȥ�å�
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			�Ͽޥ���ȥ�����
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		�桼������ȥ��������
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		�桼���������åȺ���
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/11/06 H.Osamoto ]
	case 'shop_dtl.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'shape.js';			//ZDC.Polyline			�롼������
		$D_REQ_JSAPI[] = 'geo.js';				//������ȥ�å�
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			�Ͽޥ���ȥ�����
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		�桼������ȥ��������
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		�桼���������åȺ���
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			�����ʽ��긡����POI���������ٷ��ٸ������롼��õ��������¾��
		$D_REQ_JSAPI[] = 'searchcombroute.js';	//ZDC.Search			������ʣ��롼��õ����	add 2017/02/23 N.Wada
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;	// add 2015/10/20 N.Wada
	case 'shop_print.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'geo.js';				//������ȥ�å�
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			�Ͽޥ���ȥ�����
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		�桼������ȥ��������
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		�桼���������åȺ���
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			�����ʽ��긡����POI���������ٷ��ٸ������롼��õ��������¾��		add 2016/08/15 Y.Matsukawa
		$D_REQ_JSAPI[] = 'searchcombroute.js';	//ZDC.Search			������ʣ��롼��õ����	add 2017/02/23 N.Wada
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/10/01 Y.Matsukawa [
	case 'maplink.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				��ɬ��
		$D_REQ_JSAPI[] = 'shape.js';			//ZDC.Polyline			�롼������
		$D_REQ_JSAPI[] = 'geo.js';				//������ȥ�å�
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			�Ͽޥ���ȥ�����
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		�桼������ȥ��������
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		�桼���������åȺ���
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			�����ʽ��긡����POI���������ٷ��ٸ������롼��õ��������¾��
		// add 2016/10/03 Y.Uesugi VICS�����������ޥ��� [
		if (isset($D_CUST_VICS) && $D_CUST_VICS == 1) {
			$D_REQ_JSAPI[] = 'imglayer.js';		//ZDC.ImageLayer		Ǥ�դβ����������󥿡��ե������Ǽ�������������ž�
		}
		// add 2016/10/03 Y.Uesugi ]
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/10/01 Y.Matsukawa ]
}
if (count($D_REQ_JSAPI)) {
	$D_JS[] = $D_JSAPI_v2['zdccommon'].implode(',', $D_REQ_JSAPI).'&force=1'.'&opt='.$cid;
}

?>