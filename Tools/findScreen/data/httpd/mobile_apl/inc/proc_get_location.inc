<?PHP
//==============================================================================
// �ʲ����ӥ���ꥢ���������Ƥ�����־��󤫤�ߥ���ñ�̤ΰ��١����٤�������롣
//==============================================================================
// ------------------------------------------------------------
// 2009/05/11 Y.Matsukawa	au GPS�б�
// 2010/08/12 Y.Matsukawa	iPhone�б�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2012/04/25 H.osamoto		GPS�������Զ���б�
// ------------------------------------------------------------
// ���־���ȵ����ɣĤ���롼�ȸ����ڤӡ�POS�ѥ�᡼���κ���
// mod 2011/07/05 Y.Nakajima
if(($carrier->G_AGENT_TYPE == D_DOCOMO || $carrier->G_AGENT_TYPE == D_PC) && (!isset($lat) || (isset($lat) && $lat == "")) && (!isset($lon) || (isset($lon) && $lon == "")) && (isset($_POST['AREACODE']) && $_POST['AREACODE'])){
	//docomoü����PC���饢���������ơ����ġ���ɸ���󡢥��ꥢ�����¸�ߤ��ʤ����Ϥ�����
	dbl("DOCOMO OPEN IAREA");
	// mod 2011/07/05 Y.Nakajima
	//$a_info = split(",",file_get_contents("iarea/iarea".$_POST['AREACODE'].".txt"));
	$a_info = preg_split("/,/",file_get_contents("iarea/iarea".$_POST['AREACODE'].".txt"));
	$cx = intval(($a_info[3] + $a_info[5]) / 2);
	$cy = intval(($a_info[4] + $a_info[6]) / 2);
} else{
	dbl("GPS CARRIER");
	// �Ķ��ѿ��˰��ٷ��٤�������Ϥ����������
	// mod 2011/07/05 Y.Nakajima
	if(isset($_SERVER["HTTP_X_JPHONE_GEOCODE"]) && $_SERVER["HTTP_X_JPHONE_GEOCODE"] != ""){
		dbl("SOFTBANK GPS[".$_SERVER["HTTP_X_JPHONE_GEOCODE"]);
		// �Ķ��ѿ���HTTP_X_JPHONE_GEOCODE�פΰ��ٷ��٤�����¬�ϷϤʤΤǤ��Τޤ��ֵ�
		// mod 2011/07/05 Y.Nakajima
		//$wk = split("%1A", $_SERVER["HTTP_X_JPHONE_GEOCODE"]);
		$wk = preg_split("/%1A/", $_SERVER["HTTP_X_JPHONE_GEOCODE"]);
		$cy = intval(substr($wk[0],0,2)) * 3600000 + intval(substr($wk[0],2,2)) * 60000 + intval(substr($wk[0],4,2)) * 1000;
		$cx = intval(substr($wk[1],0,3)) * 3600000 + intval(substr($wk[1],3,2)) * 60000 + intval(substr($wk[1],5,2)) * 1000;
	} else {
		// ¬�Ϸϥ����å�
		// add 2011/07/05 Y.Nakajima [
		if (!isset($lat)) $lat = "";
		if (!isset($lon)) $lon = "";
		if (!isset($datum)) $datum = 0;
		if (!isset($pos)) $pos = "";
		// add 2011/07/05 Y.Nakajima [

		// add 2009/05/11 Y.Matsukawa [
		if (strcmp($datum, "0") === 0) $datum = "WGS84";
		if (strcmp($datum, "1") === 0) $datum = "TOKYO";
		// add 2009/05/11 Y.Matsukawa ]
		//$get = ($datum != "" && $geo == "" ? $datum : $geo);		mod 2009/05/11 Y.Matsukawa
		// mod 2011/07/05 Y.Nakajima
		//$geo = ($datum != "" && $geo == "" ? $datum : $geo);
		$geo = (isset($datum) && $datum != "" && ((isset($geo) && $geo == "") || !isset($geo)) ? $datum : $geo);
		if(isset($geo) && $geo  != ""){ $wgs84 = ($geo == "WGS84" || $geo == "wgs84" ? true : false); }

		dbl("OTHER GPS   lat=$lat, lon=$lon, pos=$pos, wgs84[$wgs84]");

		// + ����Ͻ���
		$lat = str_replace("%2B","",$lat);
		$lon = str_replace("%2B","",$lon);
		$lat = str_replace("%2b","",$lat);
		$lon = str_replace("%2b","",$lon);
		$lat = str_replace("+","",$lat);
		$lon = str_replace("+","",$lon);
		// add 2012/04/25 H.osamoto [
		$lat = str_replace(" ","",$lat);
		$lon = str_replace(" ","",$lon);
		// add 2012/04/25 H.osamoto ]

		if($lat != "" && $lon != ""){
			$pos = "E{$lon}N{$lat}";
		}

		// ���������ڤ���ʬ�ä���ߥ��ä��Ѵ��ʤ��η����Ϥʤ����ɡ��ƥ����Ѥˡ�
		// mod 2011/07/05 Y.Nakajima
		//if(ereg("E([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)N([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)", $pos, $r)){
		if(preg_match("/E([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)N([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)/", $pos, $r)){
			$lat = intval($r[4] * 3600000 + $r[5] * 60000 + $r[6] * 1000);
			$lon = intval($r[1] * 3600000 + $r[2] * 60000 + $r[3] * 1000);
		}

		// ���������ڤ���ʬ�ä���ߥ��ä��Ѵ�
		// mod 2011/07/05 Y.Nakajima
		//if(ereg("N([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)E([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)", $pos, $r)){
		if(preg_match("/N([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)E([0-9]+)\.([0-9]+)\.([0-9]+\.[0-9]+)/", $pos, $r)){
			$lat = intval($r[1] * 3600000 + $r[2] * 60000 + $r[3] * 1000);
			$lon = intval($r[4] * 3600000 + $r[5] * 60000 + $r[6] * 1000);
		}

		// ���������ڤ��٤���ߥ��ä��Ѵ�		add 2010/08/12 Y.Matsukawa
		// mod 2011/07/05 Y.Nakajima
		//if(ereg("E([0-9]{2,3}\.[0-9]{1,})N([0-9]{2,3}\.[0-9]{1,})$", $pos, $r)){
		if(preg_match("/E([0-9]{2,3}\.[0-9]{1,})N([0-9]{2,3}\.[0-9]{1,})$/", $pos, $r)){
			$lat = round($r[2] * 3600 * 1000);
			$lon = round($r[1] * 3600 * 1000);
		}

		// ¬�ϷϤ�����¬�ϷϤʤ餽�Τޤް��ٷ��٤�����
		// mod 2011/07/05 Y.Nakajima
		//if($wgs84 == false)){
		if((!isset($wgs84)) || (isset($wgs84) && $wgs84 == false)){
			$cx = $lon;
			$cy = $lat;
		} else if($lat != "" && $lon != ""){
			dbl("            lat=$lat, lon=$lon, pos=$pos");
			cnv_transDatum($lat, $lon, WGS84_TO_TKY, &$cy, &$cx);
		}
		dbl("TOKYO       lat=$cy, lon=$cx");
	}
}

?>