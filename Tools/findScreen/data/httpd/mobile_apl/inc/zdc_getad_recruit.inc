<?php
// ------------------------------------------------------------
// 2009/07/15 Y.Matsukawa	����������AD Maplink�б���
// 2009/10/08 Y.Matsukawa	�ꥯ�롼�ȹ���API ��³���ѹ�
// 2009/12/22 Y.Matsukawa	�ꥯ�롼�ȹ���API�ѹ�
// ------------------------------------------------------------
include_once('xml.php');		// add 2009/07/15 Y.Matsukawa
//------------------------------------------------
// ��� ���Ȥ�d_serv���˽Ф�
//------------------------------------------------
// del 2009/10/08 Y.Matsukawa [
//define("AD_RECRUIT_PATH","http://match.doko.jp/haishin/a?");//match.doko.jp
////define("AD_RECRUIT_PATH_AREA","http://area.doko.jp/haishin/a?");//match.doko.jp
////define("AD_RECRUIT_PATH_AREA","http://addemo.doko.jp/haishin/a?");//match.doko.jp
//define("AD_RECRUIT_PATH_AREA","http://match.doko.jp/haishin/m?");//����
// del 2009/10/08 Y.Matsukawa ]
// add 2009/10/08 Y.Matsukawa [
define("AD_RECRUIT_HOST","202.221.186.140");	//nw.ads.doko.jp
//define("AD_RECRUIT_PATH_AREA","/haishin/m?");	//nw.ads.doko.jp	mod 2009/12/22 Y.Matsukawa
define("AD_RECRUIT_PATH_AREA","/haishin/a?");	//nw.ads.doko.jp
// add 2009/10/08 Y.Matsukawa ]

//----------------------------------------------------------
// �ե�����̾��zdc_getad_recruit_delax.inc
// ����̾���ꥯ�롼�ȹ���API(�ǥ�å���)��ƤӽФ�
//
// ��������2007/10/26
// �����ԡ�Bando@D&I
//
// ���⡧�ꥯ�롼�ȹ���API��Ƥ�����ѷ������Ѵ������֤�
//
// ��������
//   ��2007/10/26 Bando@D&I        ��������
//----------------------------------------------------------
function zdc_getad_recruit(&$list,$opts) {
	global $carrier;		// add 2009/07/15 Y.Matsukawa
	$id = $opts["id"];
	$pass = $opts["pass"];
	// ����ꥢȽ��
	// del 2009/07/15 Y.Matsukawa [
	//	$ret = f_get_mobile_info($opts["ua"], &$retHash, &$err_msg);
	//	if(isset($retHash)) {
	//		$tmp = array("1"=>"d","2"=>"a","3"=>"s");
	//		$mode = $tmp[$retHash["CARRIER"]];
	//	} else {
	//		$mode = "p";
	//	}
	// del 2009/07/15 Y.Matsukawa ]
	// add 2009/07/15 Y.Matsukawa [
	$tmp = array(D_DOCOMO=>"d",D_KDDI=>"a",D_SOFTBANK=>"s");
	$mode = $tmp[$carrier->G_AGENT_TYPE];
	if (!$mode) $mode = "p";
	// add 2009/07/15 Y.Matsukawa ]

	// prm�β���
	$ar = explode("&",$opts["prm"]);
	$cnt = count($ar);
	for($i = 0;$i < $cnt;$i ++) {
		$tmp = explode("=",$ar[$i]);
		if($tmp[0] == "pg") {
			$tmp2 = explode(",",$tmp[1]);
			$pg1 = $tmp2[0];
			$pg2 = $tmp2[1];
		} else {
			$prm .= sprintf("&%s=%s",$tmp[0],urlencode($tmp[1]));
		}
		$p[$tmp[0]] = $tmp[1];
	}
	$opts["prm"] = $prm;
	// ���ϥ����å�
	// del 2009/07/15 Y.Matsukawa [
	//	$pg1 = "Premium_ad";//pg�ͤϸ���ˤ���
	//	$pg2 = "Area_ad";
	//	if(!isset($pg1) || !isset($pg2)) return false;
	//	if(strlen($pg1) > 20 || strlen($pg2) > 20) return false;
	// del 2009/07/15 Y.Matsukawa ]
	if(isset($p["rc"]) && (!is_numeric($p["rc"]) || $p["rc"] < 0 || $p["rc"] > 10)) return false;
	//
	$ret = true;
	//if($opts["cnt_p"]>0 && $ret) $ret = zdc_getad_recruit_delax($list["premiere"],$opts,$id,$pass,$pg1,$mode);	del 2009/07/15 Y.Matsukawa
	if($opts["cnt_a"]>0 && $ret) $ret = zdc_getad_recruit_area($list["area"],$opts,$id,$pass,$pg2,$mode);
	if(!$ret) unset($list);
	
	return $ret;
}

//----------------------------------------------------------
// �ե�����̾��zdc_getad_recruit_delax.inc
// ����̾���ꥯ�롼�ȹ���API(�ǥ�å���)��ƤӽФ�
//
// ��������2007/10/26
// �����ԡ�Bando@D&I
//
// ���⡧�ꥯ�롼�ȹ���API��Ƥ�����ѷ������Ѵ������֤�
//
// ��������
//   ��2007/10/26 Bando@D&I        ��������
//----------------------------------------------------------
function zdc_getad_recruit_delax(&$list,$opts,$id,$pass,$page,$mode) {
	//ɬ�פʥѥ�᡼����ȴ���Ф�
	$lat   = $opts["lat"];
	$lon   = $opts["lon"];
	$llat   = $opts["lat1"];
	$llon   = $opts["lon1"];
	$rlat   = $opts["lat2"];
	$rlon   = $opts["lon2"];
	$cnt_p = $opts["cnt_p"];
	$prm   = $opts["prm"];
	$agent = $opts["ua"];
	$datum = $opts["datum"];
	$ip    = "";
	
	//CGI�ѥ�᡼��������
	$path = AD_RECRUIT_PATH_AREA;
	// �ǥ�å����������ʬ�Фʤ� $prm  = sprintf("i=%s&a=%s&d=d&g=j&r=2&im=a&",$id,md5(date("Ymd").$pass)).
//	$prm  = sprintf("i=%s&a=%s&d=a&g=j&r=2&im=a&",$id,md5(date("Ymd").$pass)).
//	$prm  = sprintf("i=%s&a=%s&d=a&g=%s&r=2&im=a&",$id,md5(date("Ymd").$pass),$datum).
//	        sprintf("x=%s&y=%s&c=%s&u=%s&ip=%s&m=%s&pg=%s",$lon,$lat,$cnt_p,urlencode($agent),$ip,$mode,$page).$prm;
	//$prm  = sprintf("i=%s&a=%s&ip=%s&u=%s&m=%s&d=a&gk=6&g=%s&lx=%s&ly=%s&rx=%s&ry=%s&c=%s&r=2&im=a&is=a&pg=%s",$id,md5(date("Ymd").$pass),$ip,urlencode($agent),$mode,$datum,$llon,$llat,$rlon,$rlat,$cnt_p,$page).$prm;		mod 2009/10/08 Y.Matsukawa
	$prm  = sprintf("i=%s&a=%s&ip=%s&u=%s&m=%s&d=a&g=%s&lx=%s&ly=%s&rx=%s&ry=%s&c=%s&r=2&im=a&is=a&pg=%s",$id,md5(date("Ymd").$pass),$ip,urlencode($agent),$mode,$datum,$llon,$llat,$rlon,$rlat,$cnt_p,$page).$prm;
	
	//CGI�ƤӽФ�
	$url = $path."&".$prm;
//error_log($url,3,"/var/tmp/tmptest.log");	
    //print_r("\r\n recurl: ".$url."\r\n");
	
	$dat = ZdcHttpReadAD(AD_RECRUIT_HOST, $url,$status);
	if($status == 404) return false;//id,pass�δְ㤤
	if($status == "timeout") return true;
	if(!$dat) return true;
	
	$cnt = count($dat);
	
	if($cnt) {
		for($i = 0;$i < $cnt;$i ++) $xml .= $dat[$i];
		//XML�Υѡ���
		$xml = XML_unserialize($xml);
		//���ơ�����
		$cnt = $xml["dokoad"]["result attr"]["adLength"];
		if($cnt == 1) {
			//���
			$tlist["0"]      = $xml["dokoad"]["ad"];
			$tlist["0 attr"] = $xml["dokoad"]["ad attr"];
		} else if($cnt > 1) {
			//ʣ����
			$tlist = $xml["dokoad"]["ad"];
		} else {
			//����
		}
		//�ǡ����ù�
		if($cnt > $cnt_p) $cnt = $cnt_p;
		if($cnt > 0) {
			$list = "";
			for($i = 0;$i < $cnt;$i ++) {
				$j = $i." attr";
				$list[$i]["name"] = mb_convert_encoding($tlist[$j]["adTitle"],"eucjp-win","utf-8");
				$list[$i]["copy"] = mb_convert_encoding($tlist[$j]["adText1"],"eucjp-win","utf-8")
			                   	.mb_convert_encoding($tlist[$j]["adText2"],"eucjp-win","utf-8");
				$list[$i]["url"]  = $tlist[$j]["adUrl"];
				$list[$i]["imgurl"] = $tlist[$j]["picUrl"];
				if(isset($tlist[$i]["geo attr"]["positionY"])) {
					$list[$i]["lat"]  = $tlist[$i]["geo attr"]["positionY"];
					$list[$i]["lon"]  = $tlist[$i]["geo attr"]["positionX"];
				} else {
					//���ٷ��٤�̵�����
					$list[$i]["lat"]  = $lat;
					$list[$i]["lon"]  = $lon;
				}
			}
		}
	}
	
	return true;
}


//----------------------------------------------------------
// �ե�����̾��zdc_getad_recruit_area.inc
// ����̾���ꥯ�롼�ȹ���API(���ꥢ)��ƤӽФ�
//
// ��������2007/10/26
// �����ԡ�Bando@D&I
//
// ���⡧�ꥯ�롼�ȹ���API��Ƥ�����ѷ������Ѵ������֤�
//
// ��������
//   ��2007/10/26 Bando@D&I        ��������
//----------------------------------------------------------
function zdc_getad_recruit_area(&$list,$opts,$id,$pass,$page,$mode) {
	//ɬ�פʥѥ�᡼����ȴ���Ф�
	$lat   = $opts["lat"];
	$lon   = $opts["lon"];
	$llat   = $opts["lat1"];
	$llon   = $opts["lon1"];
	$rlat   = $opts["lat2"];
	$rlon   = $opts["lon2"];
	$cnt_a = $opts["cnt_a"];
	$prm   = $opts["prm"];
	$agent = $opts["ua"];
	$datum = $opts["datum"];
	$ip    = "";
	
	//CGI�ѥ�᡼��������
	//$path = AD_RECRUIT_PATH;
	$path = AD_RECRUIT_PATH_AREA;
//	$prm  = sprintf("i=%s&a=%s&d=n&g=j&r=2&im=a&",$id,md5(date("Ymd").$pass)).
	//$prm  = sprintf("i=%s&a=%s&d=n&g=%s&r=2&im=a&",$id,md5(date("Ymd").$pass),$datum).
	//        sprintf("x=%s&y=%s&c=%s&u=%s&ip=%s&m=%s&pg=%s",$lon,$lat,$cnt_a,urlencode($agent),$ip,$mode,$page).$prm;
	$prm = "";		// add 2009/07/15 Y.Matsukawa
	//$prm  = sprintf("i=%s&a=%s&ip=%s&u=%s&m=%s&d=n&gk=6&g=%s&lx=%s&ly=%s&rx=%s&ry=%s&c=%s&r=2&im=n&is=a&pg=%s",$id,md5(date("Ymd").$pass),$ip,urlencode($agent),$mode,$datum,$llon,$llat,$rlon,$rlat,$cnt_a,$page).$prm;		mod 2009/10/08 Y.Matsukawa
	//$prm  = sprintf("i=%s&a=%s&ip=%s&u=%s&m=%s&d=n&g=%s&lx=%s&ly=%s&rx=%s&ry=%s&c=%s&r=2&im=n&is=a&pg=%s",$id,md5(date("Ymd").$pass),$ip,urlencode($agent),$mode,$datum,$llon,$llat,$rlon,$rlat,$cnt_a,$page).$prm;		mod 2009/12/22 Y.Matsukawa
	$prm  = sprintf("i=%s&a=%s&ip=%s&u=%s&m=%s&d=n&g=%s&x=%s&y=%s&c=%s&r=2&im=n&is=a&pg=%s",$id,md5(date("Ymd").$pass),$ip,urlencode($agent),$mode,$datum,$lon,$lat,$cnt_a,$page).$prm;
	
	//CGI�ƤӽФ�
	$url = $path."&".$prm;
//error_log(AD_RECRUIT_HOST."\n", 3, D_DEBUG_AD_LOG_FILE);
//error_log($url."\n", 3, D_DEBUG_AD_LOG_FILE);

	$dat = ZdcHttpReadAD(AD_RECRUIT_HOST, $url,$status);
//error_log($status."\n", 3, D_DEBUG_AD_LOG_FILE);
	if($status == 404) return false;//id,pass�δְ㤤
	if($status == "timeout") return true;
	if(!$dat) return true;
	
	$cnt = count($dat);
	if($cnt) {
		for($i = 0;$i < $cnt;$i ++) $xml .= $dat[$i];
		//XML�Υѡ���
		$xml = XML_unserialize($xml);
		//���ơ�����
		$cnt = $xml["dokoad"]["result attr"]["adLength"];
		if($cnt == 1) {
			//���
			$tlist["0"]      = $xml["dokoad"]["ad"];
			$tlist["0 attr"] = $xml["dokoad"]["ad attr"];
		} else if($cnt > 1) {
			//ʣ����
			$tlist = $xml["dokoad"]["ad"];
		} else {
			//����
		}
		//�ǡ����ù�
		if($cnt > $cnt_a) $cnt = $cnt_a;
		if($cnt > 0) {
			$list = "";
			for($i = 0;$i < $cnt;$i ++) {
				$j = $i." attr";
				$list[$i]["name"] = mb_convert_encoding($tlist[$j]["adTitle"],"eucjp-win","utf-8");
				$list[$i]["copy"] = mb_convert_encoding($tlist[$j]["adText1"],"eucjp-win","utf-8")
				                   .mb_convert_encoding($tlist[$j]["adText2"],"eucjp-win","utf-8");
				$list[$i]["url"]  = $tlist[$j]["adUrl"];
				$list[$i]["imgurl"] = $tlist[$j]["picUrl"];
				if(isset($tlist[$i]["geo attr"]["positionY"])) {
					$list[$i]["lat"]  = $tlist[$i]["geo attr"]["positionY"];
					$list[$i]["lon"]  = $tlist[$i]["geo attr"]["positionX"];
				} else {
					// add 2009/07/15 Y.Matsukawa [
					//					//���ٷ��٤�̵�����
					//					$list[$i]["lat"]  = $lat;
					//					$list[$i]["lon"]  = $lon;
					// add 2009/07/15 Y.Matsukawa ]
				}
			}
		}
	}
	
	return true;
}
?>