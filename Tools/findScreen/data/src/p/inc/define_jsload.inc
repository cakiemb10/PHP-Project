<?php
// ------------------------------------------------------------
// 定義ファイル 使用するJSだけをロードする
// 
// 開発履歴
// 2011/10/15 Y.Matsukawa	新規作成
// 2012/10/01 Y.Matsukawa	Maplink対応
// 2012/11/06 H.Osamoto		分布地図印刷画面対応
// 2013/10/02 Y.Matsukawa	Google Maps版
// 2014/10/08 Y.Matsukawa	最寄り駅からの任意距離の円表示
// 2015/10/20 N.Wada		詳細画面でjsを2重で読み込んでしまう不具合修正
// 2016/05/02 N.Wada		Google Maps APIの読み込みをhttpsに対応
// 2016/05/16 Y.Matsukawa	Google Maps API channel指定
// 2016/08/15 Y.Matsukawa	Google版 測地系変換高精度
// 2016/10/03 Y.Uesugi		VICS対応 地図重畳
// 2016/11/10 Y.Uesugi		Google Maps APIキー設定
// 2017/02/23 N.Wada		複合ルート検索js定義追加
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
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'areamap.js';			//ZDC.AreaMap			地域図
		break;
	case 'search_rail.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'railwaymap.js';		//ZDC.RailwayMap		路線図
		break;
	case 'nmap.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'shape.js';			//ZDC.Oval							add 2014/10/08 Y.Matsukawa
		$D_REQ_JSAPI[] = 'geo.js';				//ジオメトリック
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			地図コントロール
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		ユーザコントロール作成
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		ユーザウィジット作成
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			検索		add 2014/10/08 Y.Matsukawa
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/11/06 H.Osamoto [
	case 'nmap_print.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'geo.js';				//ジオメトリック
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			地図コントロール
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		ユーザコントロール作成
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		ユーザウィジット作成
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/11/06 H.Osamoto ]
	case 'shop_dtl.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'shape.js';			//ZDC.Polyline			ルート描画
		$D_REQ_JSAPI[] = 'geo.js';				//ジオメトリック
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			地図コントロール
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		ユーザコントロール作成
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		ユーザウィジット作成
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			検索（住所検索、POI検索、緯度経度検索、ルート探索、その他）
		$D_REQ_JSAPI[] = 'searchcombroute.js';	//ZDC.Search			検索（複合ルート探索）	add 2017/02/23 N.Wada
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;	// add 2015/10/20 N.Wada
	case 'shop_print.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'geo.js';				//ジオメトリック
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			地図コントロール
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		ユーザコントロール作成
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		ユーザウィジット作成
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			検索（住所検索、POI検索、緯度経度検索、ルート探索、その他）		add 2016/08/15 Y.Matsukawa
		$D_REQ_JSAPI[] = 'searchcombroute.js';	//ZDC.Search			検索（複合ルート探索）	add 2017/02/23 N.Wada
		if ($D_GOOGLEMAPS && !$D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_JS;		// Google Maps		add 2013/10/02 Y.Matsukawa	mod 2016/11/10 Y.Uesugi
		if (isset($D_GOOGLEMAPS_API_KEY) && $D_GOOGLEMAPS_API_KEY) $D_JS[] = $D_GOOGLEMAPS_API_KEY_JS;		// Google Maps Key		add 2016/11/10 Y.Uesugi
		break;
	// add 2012/10/01 Y.Matsukawa [
	case 'maplink.htm':
		$D_REQ_JSAPI[] = 'zdcmap.js';			//ZDC.Map				※必須
		$D_REQ_JSAPI[] = 'shape.js';			//ZDC.Polyline			ルート描画
		$D_REQ_JSAPI[] = 'geo.js';				//ジオメトリック
		$D_REQ_JSAPI[] = 'control.js';			//ZDC.Control			地図コントロール
		$D_REQ_JSAPI[] = 'usercontrol.js';		//ZDC.UserControl		ユーザコントロール作成
		$D_REQ_JSAPI[] = 'userwidget.js';		//ZDC.UserWidget		ユーザウィジット作成
		$D_REQ_JSAPI[] = 'search.js';			//ZDC.Search			検索（住所検索、POI検索、緯度経度検索、ルート探索、その他）
		// add 2016/10/03 Y.Uesugi VICS向けカスタマイズ [
		if (isset($D_CUST_VICS) && $D_CUST_VICS == 1) {
			$D_REQ_JSAPI[] = 'imglayer.js';		//ZDC.ImageLayer		任意の画像取得インターフェースで取得した画像を重畳
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
