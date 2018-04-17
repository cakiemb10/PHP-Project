<?php
/*========================================================*/
// �ե�����̾��search_reachable.cgi
// ����̾����ã��ݥꥴ�����CGI�ʼ�ư�֥롼�ȡ�
//
// ��������
// 2014/01/28 H.Osamoto		��������
// 2014/10/09 H.Osamoto		�롼�ȵ�Υ���л���ͭ��ƻϩ�����Ѥ��ʤ��褦�ѹ�
/*========================================================*/

	// ���顼���Ϥ�����Ū��OFF
	error_reporting(0);
	//error_reporting(E_ALL ^ E_NOTICE);

	/*==============================================*/
	// �饤�֥��
	/*==============================================*/
	include('d_serv_emap.inc');
	include('ZdcCommonFuncAPI.inc');	// ���̴ؿ�
	
	// geos�饤�֥��
	if (!extension_loaded('geos')) {
		if (!dl('geos.so')) {
			echo "system error";
			exit;
		}
	}

	/*==============================================*/
	// �������
	/*==============================================*/
	// �����
	$base_lat = 128380190;
	$base_lon = 503147440;
	
	// ������Ǥ�1km�ΰ��ٷ��ٺ�
	$base_lat_dist = 32365;
	$base_lon_dist = 39835;
	$base_lat_dist_m = $base_lat_dist/1000;
	$base_lon_dist_m = $base_lon_dist/1000;
	
	// ���٤�������Ѵ�����
	$lon2lat = $base_lat_dist / $base_lon_dist;
	
	// ʬ��ʸ��
	$delimiter = ";";
	
	/*==============================================*/
	// �ե��󥯥����
	/*==============================================*/
	// ���ٷ��٤˳�����Ϳ
	function point_rotate($r, $angle){
		$angle = deg2rad($angle);
		$x = round($r * cos($angle));
		$y = round($r * sin($angle));
		return array($x, $y);
	}
	
	// ���ٷ��٤����Υ�򻻽�
	function getDistFromLatLon($p_latM, $p_lonM, $p_latS, $p_lonS, $p_latE, $p_lonE){
		$tmp_lat = abs($p_latS - $p_latE);
		$tmp_lon = abs($p_lonS - $p_lonE);
		
		$dist_lat_m = $tmp_lat / $p_latM;
		$dist_lon_m = $tmp_lon / $p_lonM;
		
		$ret = sqrt(pow($dist_lat_m, 2) + pow($dist_lon_m, 2));
		
		return $ret;
	}
	
	// ��������
	function getConvexHull($p_poly_str, $p_delimiter=",") {
		$reader = new GEOSWKTReader();
		$writer = new GEOSWKTWriter();
		$writer->setRoundingPrecision(0);

		$g = $reader->read('POLYGON(('.$p_poly_str.'))');
		$retConvexHull = $g->convexHull();
		$retConvexHull_str = $writer->write($retConvexHull);

		// ����ʸ�������
		$retConvexHull_str = str_replace('))', '', str_replace('POLYGON ((', '', $retConvexHull_str));
		$retConvexHull_str = str_replace(')', '', str_replace('LINESTRING (', '', $retConvexHull_str));

		$tmp_arr = explode(",", $retConvexHull_str);

		foreach($tmp_arr as $tmp_point){
			$tmp_latlon = explode(" ", trim($tmp_point));
			
			$ret_arr[] = $tmp_latlon[0].$p_delimiter.$tmp_latlon[1];
		}
		return $ret_arr;
	}
	
	// �⳰Ƚ��
	function checkContains($p_poly_str, $p_check_lat, $p_check_lon) {
		$reader = new GEOSWKTReader();
		$writer = new GEOSWKTWriter();
		$writer->setRoundingPrecision(0);
		
		$g1 = $reader->read('POLYGON(('.$p_poly_str.'))');
		$g2 = $reader->read('POINT('.$p_check_lon.' '.$p_check_lat.')');
		
		// Ƚ��
		$retAssert = $g1->contains($g2);
		
		if ($retAssert == "") {
			return false;
		} else {
			return true;
		}
	}

	/*==============================================*/
	// �ѥ�᡼������
	/*==============================================*/
	$LAT   = $_GET['lat'];
	$LON   = $_GET['lon'];
	$DIST  = $_GET['dist'];
	$PART  = $_GET['part'];
	$LVL  = $_GET['lvl'];
	if (isset($_GET['datum']) && strlen($_GET['datum'])>0) {
		$DATUM = $_GET['datum'];
	} else {
		$DATUM = DEF_PRM_DATUM_TOKYO;
	}

	/*==============================================*/
	// �ѥ�᡼�������å�
	/*==============================================*/
	// ����
	if (!$LAT) {
		echo "parameter error LAT[$LAT]";
		exit;
	}
	// ����
	if (!$LON) {
		echo "parameter error LON[$LON]";
		exit;
	}
	// �����ϰ�
	if (!$DIST) {
		echo "parameter error DIST[$DIST]";
		exit;
	}
	// ĺ����
	if (!$PART) {
		echo "parameter error PART[$PART]";
		exit;
	}
	// ɽ���̼�
	if (!$LVL) {
		$LVL = 9;
	}
	/* ¬�Ϸ� */
	if ($DATUM != DEF_PRM_DATUM_TOKYO && $DATUM != DEF_PRM_DATUM_WGS84) {
		echo "parameter error DATUM[$DATUM]";
		exit;
	}

	// ���ٷ����Ѵ�
	$res = cnv_ll2lldms($LAT, $LON, $DATUM, $LAT_MS, $LON_MS);
	if (!$res) {
		// ���ٷ�������
		echo "parameter error LAT[$LAT] LON[$LON]";
		exit;
	}

	// ʬ��ԥå�
	$dist_pitch = $DIST / 10;

	/*==============================================*/
	// �ᥤ�����
	/*==============================================*/
	for ($k = $DIST; $k > 0; $k-=$dist_pitch) {
		
		// ��Υ(���ٷ��ٴ����Ǥο���)
		$r = $base_lon_dist * ($k / 1000);
		
		// ĺ���֤γ���
		$angle_base = 360 / $PART;
		
		for($i = 0; $i < $PART; $i++) {
			$angle = $angle_base * $i;
			// ����ʬ��ư�����ݤκ�ɸ
			list($x, $y) = point_rotate($r, $angle);
			
			// ���ٷ��٤���Ψ���θ������ɸ�ΰ��ٷ��٤򻻽�
			$LAT_MS_D = round($LAT_MS - ($y * $lon2lat));
			$LON_MS_D = round($LON_MS + $x);
			
			// 2���ܰʹߤ˽������ά���뤫�����å�
			if ($k < $DIST) {
				// �����å���geos�ݥꥴ��ʸ����
				$check_poly_str = implode(", ", $dest_point);
				$check_poly_str .= ", ".$dest_point[0];
			
				// �����å��ѥݥꥴ�����������
				$checkConvexHull_arr = getConvexHull($check_poly_str, " ");
				
				// �ݥꥴ��Ȥ�����Ω���Ƥ����硢�������֤��⳰Ƚ��
				if (count($checkConvexHull_arr) > 2) {
					$check_poly_str = implode(", ", $checkConvexHull_arr);
					if(checkContains($check_poly_str, $LAT_MS_D, $LON_MS_D)) {
						// �������ޤǤΥݥꥴ������񤵤����Ͼ�ά����
						continue;
					}
				}
			}
			
			// �롼�ȸ���
			//	$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $LAT_MS, $LON_MS, $LAT_MS_D, $LON_MS_D);	mod 2014/10/09 H.Osamoto
			$url = sprintf("%s?key=%s&enc=%s&sty=%s&stx=%s&edy=%s&edx=%s&chg=%s",$D_SSAPI["searchroute"], $D_SSAPI_KEY, "EUC", $LAT_MS, $LON_MS, $LAT_MS_D, $LON_MS_D, 0);
			$xml = file_get_contents($url);
			$dat = simplexml_load_string($xml);
			
			if(!$dat) {
				// �롼��õ�����顼
				echo "searchroute error";
				exit;
			}
			
			// �롼�Ȳ���
			// distance��û���DIST��ã������ٷ��٤򻻽�
			$route_dist = 0;
			foreach ($dat->links->link as $route_array) {
				$route_dist += $route_array->info->distance;
				if ($route_dist > $k) {
					// �����Υ��Ķ������硢�롼�Ȥ�ʬ�䤷�Ƶ�Υ����
					$route_dist -= $route_array->info->distance;
					
					// $k�ޤǤλĵ�Υ
					$rest_dist = $k - $route_dist;
					
					// �롼�Ȥΰ��ٷ������������˳�Ǽ
					$point_array = explode(",", $route_array->path);
					
					for ($j = 2; $j < count($point_array); $j+=2) {
						
						$latS = $point_array[$j-1];		// �롼�ȳ��ϰ���
						$lonS = $point_array[$j-2];		// �롼�ȳ��Ϸ���
						$latE = $point_array[$j+1];		// �롼�Ƚ�λ����
						$lonE = $point_array[$j];		// �롼�Ƚ�λ����
						
						// ���ٷ������֤ε�Υ�򻻽�
						$tmp_dist = getDistFromLatLon($base_lat_dist_m, $base_lon_dist_m, $latS, $lonS, $latE, $lonE);
						
						// �롼�ȵ�Υ�˲û�
						$route_dist += $tmp_dist;
						
						if (($route_dist > $k) || ($j == count($point_array) - 2)) {
							// �����Υ��Ķ������硢�롼�Ȥΰ��ٷ��ٴ֤ˤ�DIST�Ȥʤ�ݥ���Ȥ򻻽�
							$route_dist -= $tmp_dist;
							
							// $k�ޤǤλĵ�Υ
							$rest_dist = $k - $route_dist;
							
							// ƻ�Τ��$k�ΰ��ٷ���
							$route_lat = round($latS + (($latE - $latS) * ($rest_dist / $tmp_dist)));
							$route_lon = round($lonS + (($lonE - $lonS) * ($rest_dist / $tmp_dist)));
							
							// ��ã������ǡ���������˳�Ǽ
							$dest_point[] = $route_lon." ".$route_lat;
							break;
						}
					}
					break;
				}
			}
		}
	}


	// geos�ѥݥꥴ��ʸ����
	$geos_poly_str = implode(", ", $dest_point);
	$geos_poly_str .= ", ".$dest_point[0];

	// ��������
	$convexHull_arr = getConvexHull($geos_poly_str, ",");

	$retStr = "";
	
	// ������ʸ��������
	foreach($convexHull_arr as $point) {
		$latlon = explode(",", $point);
		if($retStr) {
			$retStr .= $delimiter;
		}
		$retStr .= $latlon[1]." ".$latlon[0];
	}

	// ��̽���
	echo $retStr;

?>
