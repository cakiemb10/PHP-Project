<?PHP
// ------------------------------------------------------------
// ����å��Ǵؿ�
// 
// ��ȯ����
//   2008/02/15 Y.Matsukawa ��������
//   2008/08/22 Y.Matsukawa �ѻ��б�
// ------------------------------------------------------------
//********************************************************************
//* �Ͽ޻Ͷ����ٷ��پ������
//********************************************************************
function getMapInfo($lat, $lon, $level, $width, $height){
	global $D_ZOOM2PXMS_LAT;
	global $D_ZOOM2PXMS_LON;

	$zoom = f_get_zoom($level);

	$pxlat = $D_ZOOM2PXMS_LAT["$zoom"];
	$pxlon = $D_ZOOM2PXMS_LON["$zoom"];

	$MAPHLAT = (($height * $pxlat)/2);
	$MAPHLON = (($width  * $pxlon)/2);

	return array(($lat-$MAPHLAT), ($lon-$MAPHLON), ($lat+$MAPHLAT), ($lon+$MAPHLON), $pxlat, $pxlon);
}

//********************************************************************
//* �Ͽޥ�٥뤫��CMDN�Υ��������
//********************************************************************
function f_get_zoom($level) {
	global $D_ZOOM;

	// ��������ϡ�cmdn.inc�ˤƵ��ҡʤ��������Ȼפä���functin.inc�������δؿ����ȡ�
	return $D_ZOOM[$level];
}

//********************************************************************
//* ���������������
//********************************************************************
function getUserIconImage($icon_no){
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;
	
	$cgi = sprintf("%s?cid=%s&icon_id=%s&opt=%s",$D_SSAPI["icon_select"],$D_CID,$icon_no,$D_LOG_CID);
	
	$img = ZdcHttpRead($cgi, true, $D_SOCKET_TIMEOUT);
	
	return $img;
}

//********************************************************************
//* �Ͽ޲�������
//********************************************************************
function getMapImage($lat, $lon, $level, $width, $height, $type, $layer = "", $marktyp = ""){
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;
	global $D_MAP_LAYER_KBN;	// add 2008/08/22 Y.Matsukawa

	$url = $D_SSAPI["getmap"]."?env=1&key=".$D_SSAPI_KEY;
	$url .= "&type=".$type;						// ���������� 0:GIF 7:PNG
	$url .= "&zoom=".f_get_zoom($level);		// �������٥�
	$url .= "&lat=".$lat;						// ����
	$url .= "&lon=".$lon;						// ����
	$url .= "&w=".$width;						// �Ͽ���
	$url .= "&h=".$height;						// �Ͽ޹⤵
	$url .= "&cpflg=1";							// ���ԡ��饤�ȡʤ����
	$url .= "&opt=".$D_CID;						// ��ȣɣ�
	if($layer != ""){							// �쥤�䡼���ץ����
		$url .= "&layer=$layer";
	}
	if($marktyp != ""){							// �ޡ��������� 1:���顼 2:���졼 3:�ʤ�
		$url .= "&mtype=$marktyp";
	}
	if ($D_MAP_LAYER_KBN == '5') {				// �ѻ�		add 2008/08/22 Y.Matsukawa
		$url .= "&lang=eng";
	}

	$img = ZdcHttpRead($url, true, $D_SOCKET_TIMEOUT);

	return $img;
}

//********************************************************************
//* �Ͽޥ롼�Ȳ�������
//********************************************************************
function getRouteMapImage($stlat, $stlon, $edlat, $edlon, $lat, $lon, $level, $width, $height, $type, $layer="", $marktyp="", $rtyp=3){
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;
	global $D_MAP_LAYER_KBN;	// add 2008/08/22 Y.Matsukawa

	$url = $D_SSAPI["getroutemap"]."?env=1&key=".$D_SSAPI_KEY;
	$url .= "&type=".$type;						// ���������� 0:GIF 7:PNG
	$url .= "&rtyp=".$rtyp;						// �롼�ȥ����� 2����ư�� 3����ưȽ��
	$url .= "&sty=".$stlat;						// ��������
	$url .= "&stx=".$stlon;						// ��������
	$url .= "&edy=".$edlat;						// ��������
	$url .= "&edx=".$edlon;						// ��������
	$url .= "&zoom=".f_get_zoom($level);		// �������٥�
	$url .= "&lat=".$lat;						// ����
	$url .= "&lon=".$lon;						// ����
	$url .= "&w=".$width;						// �Ͽ���
	$url .= "&h=".$height;						// �Ͽ޹⤵
	$url .= "&icprm=00";						// �����������ɽ����
	$url .= "&cpflg=1";							// ���ԡ��饤�ȡʤʤ���
	$url .= "&opt=".$D_CID;						// ��ȣɣ�
	if($layer != ""){							// �쥤�䡼���ץ����
		$url .= "&layer=$layer";
	}
	if($marktyp != ""){							// �ޡ��������� 1:���顼 2:���졼 3:�ʤ�
		$url .= "&mtype=$marktyp";
	}
	if ($D_MAP_LAYER_KBN == '5') {				// �ѻ�		add 2008/08/22 Y.Matsukawa
		$url .= "&lang=eng";
	}
	
	$img = ZdcHttpRead($url, true, $D_SOCKET_TIMEOUT);
	
	if (substr($img, 0, 3) == "404") {
		$img .= $url;
	}

	return $img;
}

//********************************************************************
//* �Ͽޥ���å����֤ΰ��ٷ��ټ���
//********************************************************************
function getMapClickLL($lat, $lon, $x, $y, $level, $width, $height) {
	global $D_SSAPI_KEY;
	global $D_SSAPI;
	global $D_CID;
	global $D_SOCKET_TIMEOUT;

	$url = $D_SSAPI["cvtxy2ll"]."?key=".$D_SSAPI_KEY;
	$url .= "&zoom=".f_get_zoom($level);		// �������٥�
	$url .= "&lat=".$lat;						// ����
	$url .= "&lon=".$lon;						// ����
	$url .= "&w=".$width;						// �Ͽ���
	$url .= "&h=".$height;						// �Ͽ޹⤵
	$url .= "&x=".$x;							// ����å����֡�x��
	$url .= "&y=".$y;							// ����å����֡�x��
	$url .= "&opt=".$D_CID;						// ��ȣɣ�

	$dat = ZdcHttpRead($url, 0, $D_SOCKET_TIMEOUT);
	$status = explode("\t", $dat[0]);
	if (substr($status, 3) == 0) {
		$d = explode("\t", $dat[1]);
		return array($d[0], $d[1]);		// array(����,����)
	}
	
	return null;
}

//********************************************************************
//* ����������ٷ��٤����濴��ɸ�Ⱥ�Ŭ��٥�����
//********************************************************************
function ZdcGetZoomLevel($mapw, $maph, $prm_lng, $prm_lat, &$cent_lng, &$cent_lat, &$level, $center=0, $route=0){

	// ���������
	$ret = false;

	$minlng = 9999999999;
	$minlat = 9999999999;
	$maxlng = 0;
	$maxlat = 0;

	for($i = 0 ; $i < count($prm_lng) ; $i++){
		if($minlng > $prm_lng[$i]) $minlng = $prm_lng[$i];
		if($minlat > $prm_lat[$i]) $minlat = $prm_lat[$i];
		if($maxlng < $prm_lng[$i]) $maxlng = $prm_lng[$i];
		if($maxlat < $prm_lat[$i]) $maxlat = $prm_lat[$i];
	}

	// ����κǸ夬�����濴�ΤϤ�
	if($center == 1){
		$now_cent_lng = $prm_lng[count($prm_lng)-1];
		$now_cent_lat = $prm_lat[count($prm_lat)-1];
	} else {
		$now_cent_lng = round(($maxlng + $minlng) / 2);
		$now_cent_lat = round(($maxlat + $minlat) / 2);
	}
	
	$diff_lng = $maxlng - $minlng;
	$diff_lat = $maxlat - $minlat;

	// �Ͽ��ϰϤ����꤭��ʤ������θ���ƺ��祺����򤢤餫���᥻�å�
	$level = 1;

	//	// ���ƤΥ���������濴�ʸ����濴��ޤ�Ǥ���Τǡ������濴���������Τˤ���Τ���������
	//	$cent_lng = round(($maxlng + $minlng) / 2);
	//	$cent_lat = round(($maxlat + $minlat) / 2);
	$cent_lng = $now_cent_lng;
	$cent_lat = $now_cent_lat;
	
	// �롼��õ���⡼�ɤξ�硢���ʤΤǺ��������ˤʤ�褦�˥��ե��åȤ�Ĵ��
	if($route){
		$topoffset_px = 30;
		$botoffset_px = 2;
	} else {
		$topoffset_px = 15;
		$botoffset_px = 15;
	}

	// ����Υ����फ�鸡��
	for($i = 18; $i >= 1 ;  $i--){
		// �����٥�κ���������ΰ��ٷ��ٵڤӣ��ԥ������դ�ΣͣӤ����
		list($LBL, $LBG, $RTL, $RTG, $px2ms_lat, $px2ms_lon) = getMapInfo($now_cent_lat, $now_cent_lng, $i, $mapw, $maph);

		$LBL = round($LBL);
		$LBG = round($LBG);
		$RTL = round($RTL);
		$RTG = round($RTG);

		// �������󥪥ե��å�ʬ�η׻�
		$topoffsetWidth = ($px2ms_lon * $topoffset_px);
		$topoffsetHeight= ($px2ms_lat * $topoffset_px);
		$botoffsetWidth = ($px2ms_lon * $botoffset_px);
		$botoffsetHeight= ($px2ms_lat * $botoffset_px);

		// �Ͽ��ϰϤ����뤫�ɤ���Ƚ��
		if( ($LBG + $botoffsetWidth  ) < $minlng &&
			($LBL + $botoffsetHeight ) < $minlat &&
			($RTG - $topoffsetWidth  ) > $maxlng &&
			($RTL - $topoffsetHeight ) > $maxlat ){

			// ���ä��̼ܤ��ֵ�
			$level = $i;
			$ret = true;
			break;
		}
	}

	return $ret;
}

//********************************************************************
//* �Ͽ޾�Υ��������ѥ���å��֥�ޥå׾�������
//********************************************************************
function ZdcGetMapIconCoords($lat, $lon, $lv, $mapw, $maph, $icon_type, &$icon_file, &$icon_lat, &$icon_lon, $xoffse=0, $yoffset=0) {
	
	$coords = null;
	
	list($LBL, $LBG, $RTL, $RTG) = getMapInfo($lat, $lon, intval($lv), $mapw, $maph);

	$px2ms_lon = ($RTG - $LBG) / $mapw;
	$px2ms_lat = ($RTL - $LBL) / $maph;

	// �Ͽޤ��濴�ȥ�٥뤫�飱�ԥ�����������ΣͣӤ򻻽�
	$px = ($mapw * $px2ms_lon);
	$py = ($maph * $px2ms_lat);

	// �Ͽ޺������ٷ��٤򻻽�
	$left_side = $lon - ($px / 2);
	$left_under= $lat - ($py / 2);
	
	for ($i = 0; $i < count($icon_lat); $i++) {
		if ($icon_type == "ID") {
			$icon_img = @ImageCreateFromString(getUserIconImage($icon_file[$i]));
		} if ($icon_type == "GIF") {
			$icon_img = @ImageCreateFromGif($icon_file[$i]);
		}
		if ($icon_img) {
			$x[0] = ($icon_lon[$i] - $left_side) / $px2ms_lon;
			$y[0] = $maph - (($icon_lat[$i] - $left_under) / $px2ms_lat);
			$x[0] = round($x[0] - (imagesx($icon_img)/2));
			$y[0] = round($y[0] - (imagesy($icon_img)/2));
			$x[1] = $x[0] + imagesx($icon_img);
			$y[1] = $y[0] + imagesy($icon_img);
			$x[0] += $xoffset;
			$y[0] += $yoffset;
			$x[1] += $xoffset;
			$y[1] += $yoffset;
			$coords[]["coords"] = $x[0].",".$y[0].",".$x[1].",".$y[1];
		}
	}
	
	return $coords;
}

?>