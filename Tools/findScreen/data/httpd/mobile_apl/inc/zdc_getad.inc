<?php
// ------------------------------------------------------------
// 2009/07/15 Y.Matsukawa	����������AD Maplink�б���
// 2009/10/08 Y.Matsukawa	�ꥯ�롼�ȹ���API ��³���ѹ�
// ------------------------------------------------------------
//------------------------------------------------
// ��� ���Ȥ�d_serv���˽Ф�
//------------------------------------------------
define("D_AD_SOCKETOPEN_TIMEOUT",5);//��³��(��)
define("D_AD_SOCKET_TIMEOUT",5);//�ɹ���(��)

//���ȼԤ��Ȥ�����ե�����
//require_once("zdc_getad_recruit.inc");


//----------------------------------------------------------
// �ե�����̾��zdc_getad.inc
// ����̾������API���ɤ߹������̤��֤�
//
// ��������2007/10/26
// �����ԡ�Bando@D&I
//
// ���⡧�ꥯ�롼�ȹ���API��Ƥ�����ѷ������Ѵ������֤�
//
// ��������
//   ��2007/10/26 Bando@D&I        ��������
//----------------------------------------------------------
function zdc_getad(&$list,$opts){
	$ret = false;
	$list = "";
	
	//�ɤ߹��ߥѥ�����
	switch($opts["ad"]) {
		case "rt001"://�ꥯ�롼�ȹ���
			require_once("zdc_getad_recruit.inc");
			$ret = zdc_getad_recruit($list,$opts);
			break;
		// del 2009/07/15 Y.Matsukawa [
		//		case "ot002"://*ueda OPT����
		//			require_once("zdc_getad_opt.inc");
		//			$ret = zdc_getad_opt($list,$opts);
		//			break;
		// del 2009/07/15 Y.Matsukawa ]
	}
	
	//�����
	return $ret;
}



//----------------------------------------------------------
// ����̾������API�ɤ߹����ѥ����å��̿�
//
// ��������2007/10/26
// �����ԡ�Bando@D&I
//
// ���⡧�ꥯ�롼�ȹ���API��Ƥ�����ѷ������Ѵ������֤�
//
// ��������
//   ��2007/10/26 Bando@D&I        ��������
//----------------------------------------------------------
//function ZdcHttpReadAD($url, &$status, $binary = 0, $timeout = D_AD_SOCKET_TIMEOUT){		mod 2009/10/08 Y.Matsukawa
function ZdcHttpReadAD($host, $url, &$status, $binary = 0, $timeout = D_AD_SOCKET_TIMEOUT){
	$status = 0;
	//$url_array = parse_url($url);		del 2009/10/08 Y.Matsukawa
	
	// �����åȺ���
	//echo $url."<br>\n";
	//if(!$fp = fsockopen($url_array["host"], "80", $errno, $errstr, D_AD_SOCKETOPEN_TIMEOUT)){		mod 2009/10/08 Y.Matsukawa
	if(!$fp = fsockopen($host, "80", $errno, $errstr, D_AD_SOCKETOPEN_TIMEOUT)){
		$status = "timeout";
		return false;
	}
	socket_set_timeout($fp, $timeout);
	
	// ����
	@fputs($fp, "GET $url HTTP/1.0\r\n\r\n");
	
	$line = "";
	$http_state = "";
	
	if($fp){
		while(!feof($fp)){
			$getline = @fgets($fp, 4000);
			if(!$getline) break;
			if(!$http_state) $http_state = $getline;
			$line .= $getline;
		}
	}
	@fclose($fp);
	
	// mod 2011/07/05 Y.Nakajima
	//$ret = split(" ",$http_state);
	$ret = explode(" ",$http_state);
	$status = $ret[1];
	if($status != "200"){
		//f_error_log("http_state ".$ret[1]." ".$url,__FILE__,__LINE__);
		return false;
	}
	
	// HTTP�إå��ʹߤ����
	// mod 2011/07/05 Y.Nakajima
	//$ret = split("\r\n\r\n",$line);
	$ret = explode("\r\n\r\n",$line);
	
	// ����ͽ���
	if(is_array($ret)){
		$out = "";
		
		// ����ǥå�����HTTP�إå��ʹߤΣ�����Ϥޤ�Τ�����
		$j = 0;
		for($i = 1 ; $i < count($ret) ; $i++){
			$out .= $ret[$i].($binary == true ? "" : "\n");
		}

		if($binary == true){
			return $out;
		} else { 
			// ��������HTML�����
			// mod 2011/07/05 Y.Nakajima
			//$ret = split("(\r|\r\n|\n)",$out);
			$ret = preg_split("/[\r|\r\n|\n]+/",$out);
			$dat = Array();
			$j = 0;
			for($i = 0;$i < count($ret); $i++) {
				if(!trim($ret[$i])) continue;
				$dat[$j] = $ret[$i];
				$j ++;
			}
			return $dat;
		}
	} else {
		//f_error_log("html ".$ret[1]." ".$url,__FILE__,__LINE__);
		return false;
	}
}
?>