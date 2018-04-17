<?PHP
// ------------------------------------------------------------
// 2016/02/03 N.Wada		����������SMT��carrier.inc�򥳥ԡ���
// 2016/02/05 N.Wada		�����ϼ������Ի��ˤϻ��ꤷ��URL�˥�����쥯�Ȳ�ǽ��
// 							���Զ���handleError�ؿ�̾�����ʤ��褦���ե��å�����Ĥ���
// 2016/03/24 N.Wada		���־�������ѤΥ�����Хå��ؿ����ֵѡ����ѥС������)�ɲ�
// 2016/06/17 N.Wada		�����OS��Ƚ��˥��ޥ�Ƚ����ɲ�
// ------------------------------------------------------------
// USER_AGENTȽ������ɽ�����
define("D_REG_PC"   , "Mozilla");

// CARRIERȽ��ʸ�������
define("D_IPHONE"   , "iPhone");
define("D_IPAD"     , "iPad");
define("D_ANDROID"  , "Android");
define("D_ANDROID_1", "Android_1");
define("D_ANDROID_2", "Android_2");
define("D_PC"       , "PC");

class CARRIER {
	var $G_USER_AGENT;
	var $G_AGENT_TYPE;

	//---------------------------------------------------------------
	// ���󥹥ȥ饯��
	//---------------------------------------------------------------
	function CARRIER($P_USER_AGENT = ""){
		// �����������Ԥ�
		$this->initialize($P_USER_AGENT);
	}

	//---------------------------------------------------------------
	// ���������
	//---------------------------------------------------------------
	function initialize($P_USER_AGENT){
		if($P_USER_AGENT){
			$this->G_USER_AGENT = $P_USER_AGENT;
			// ü������ޥ��������������������ѿ�����
			$ret = $this->getMobileInfo($P_USER_AGENT);
		}
	}

	//---------------------------------------------------------------
	// ü������ޥ������鵡���OS��Ƚ��
	//---------------------------------------------------------------
	function getMobileInfo($P_USER_AGENT){
		// �������ν����
		$ret = Array("CARRIER"=>"","HEIGHT"=>"","WIDTH"=>"");

		// add 2016/06/17 N.Wada [
		// iPhone
		if (strpos($P_USER_AGENT, D_IPHONE) || strpos($P_USER_AGENT, D_IPAD)) {
			$ret = Array(
				"CARRIER"=>D_IPHONE,
				"HEIGHT"=>320,
				"WIDTH"=>240
			);
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
		// Android 1.x
		} else if (strpos($P_USER_AGENT, D_ANDROID.' 1.')) {
			$ret = Array(
				"CARRIER"=>D_ANDROID_1,
				"HEIGHT"=>320,
				"WIDTH"=>260
			);
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
		// Android 2.x�ʹ�
		} else if (strpos($P_USER_AGENT, D_ANDROID)) {
			$ret = Array(
				"CARRIER"=>D_ANDROID_2,
				"HEIGHT"=>320,
				"WIDTH"=>260
			);
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
		}
		// add 2016/06/17 N.Wada ]

		switch($ret["CARRIER"]){
		// add 2016/06/17 N.Wada [
		// iPhone
		case D_IPHONE:
			$this->G_AGENT_TYPE = D_IPHONE;
			break;
		// Android 1.x
		case D_ANDROID_1:
			$this->G_AGENT_TYPE = D_ANDROID_1;
			break;
		// Android 2.x�ʹ�
		case D_ANDROID_2:
			$this->G_AGENT_TYPE = D_ANDROID_2;
			// add 2014/09/11 Y.Matsukawa [
			if (strpos($P_USER_AGENT, 'Android 2.1')) {
				$this->G_ANDROID_2_1 = true;
			}
			// add 2014/09/11 Y.Matsukawa ]
			break;
		// add 2016/06/17 N.Wada ]
		default:
			// �ʲ��Уä�Ƚ������ʤ�
			if( preg_match("/".D_REG_PC."/", $P_USER_AGENT, $matches) !== false){
				$this->G_AGENT_TYPE = D_PC;
			} else {
				// ���顼����ɽ��
				header("Content-Type: text/html;charset=UTF-8");
				echo mb_convert_encoding("���������Ǥ��ޤ���", "UTF-8","EUC-JP");
				exit;
			}
		}
		return $ret;
	}

	//---------------------------------------------------------------
	// ���־�������ѤΣգң̤��ֵѡʣ������ѡ�
	//---------------------------------------------------------------
	function MakeLocationSearchUrl(){
		$url = "javascript:";
		$url .= "ZdcEmapLocProgress();";
		switch($this->G_AGENT_TYPE){
		default:
			$url .= "navigator.geolocation.getCurrentPosition(locupdate, handleError);";
			return $url;
		}
	}

	// add 2011/07/13 Y.Matsukawa
	//---------------------------------------------------------------
	// ���־�������ѤΥ�����ץȤ��ֵ�
	//---------------------------------------------------------------
	//function MakeLocationSearchScript(){		mod 2012/02/27 Y.Matsukawa
	function MakeLocationSearchScript($callback_suffix=''){
		switch($this->G_AGENT_TYPE){
		default:
			$url = "navigator.geolocation.getCurrentPosition(locupdate$callback_suffix, handleError$callback_suffix);";
			return $url;
		}
	}

	//---------------------------------------------------------------
	// ���־�������ѤΥ�����Хå��ؿ����ֵ�
	//---------------------------------------------------------------
	//function MakeLocationCallbackFunc($url, $callback_suffix=''){		mod 2016/02/05 N.Wada
	function MakeLocationCallbackFunc($url, $callback_suffix='', $error_url=''){
		switch($this->G_AGENT_TYPE){
		default:
			$func = '';
			$func .= "function locupdate$callback_suffix(pos){";
			$func .= 'var lat=pos.coords.latitude;var lon = pos.coords.longitude;';
			$func .= 'var url="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			$func .= 'if(flt!="") url+="&plfilter="+flt;';
			$func .= 'if(ZdcEmapGPSCondParams!="") url+=ZdcEmapGPSCondParams;';
			$func .= 'window.location.href=url;';
			$func .= '}';
			//$func .= 'function handleError(err) {';	mod 2016/02/05 N.Wada
			$func .= "function handleError$callback_suffix(err) {";
			$func .= 'ZdcEmapLocFinish();';
			$func .= 'alert(ZdcEmapGPSErrMsg);';
			if($error_url) $func .= 'window.location.href="'.$error_url.'";';	// add 2016/02/05 N.Wada
			$func .= '}';
			return $func;
		}
	}

	// add 2011/07/13 Y.Matsukawa
	//---------------------------------------------------------------
	// ���־�������ѤΥ�����Хå��ؿ����ֵѡʴؿ��ذ��Ϥ���
	//---------------------------------------------------------------
	function MakeLocationCallbackFuncCall($callback_func, $error_func, $shop_lat, $shop_lon){
		switch($this->G_AGENT_TYPE){
		default:
			$func = '';
			$func .= 'function locupdate(pos){';
			$func .= 'var lat=pos.coords.latitude;var lon = pos.coords.longitude;';
			$func .= $callback_func.'(lat,lon,'.$shop_lat.','.$shop_lon.');';
			$func .= '}';
			$func .= 'function handleError(err) {';
			if($error_func) $func .= $error_func.'();';
			$func .= 'alert(ZdcEmapGPSErrMsg);';
			$func .= '}';
			return $func;
		}
	}

	// add 2016/03/24 N.Wada
	//---------------------------------------------------------------
	// ���־�������ѤΥ�����Хå��ؿ����ֵѡ����ѥС������)
	//---------------------------------------------------------------
	function MakeLocationCallbackFuncCallGeneric($callback_stmt, $error_stmt, $callback_suffix=''){
		switch($this->G_AGENT_TYPE){
		default:
			$func = '';
			$func .= "function locupdate$callback_suffix(pos){";
			$func .= '  var lat = pos.coords.latitude;';
			$func .= '  var lon = pos.coords.longitude;';
			$func .= '  (function(){';
			$func .= '    '.$callback_stmt;
			$func .= '  }());';
			$func .= '}';
			$func .= "function handleError$callback_suffix(err){";
			if($error_stmt) {
			$func .= '  (function(){';
			$func .= '    '.$error_stmt;
			$func .= '  }());';
			}
			$func .= '  alert(ZdcEmapGPSErrMsg);';
			$func .= '}';
			return $func;
		}
	}


	//---------------------------------------------------------------
	// Getter
	//---------------------------------------------------------------
	function isPC()			{ return ($this->G_AGENT_TYPE == D_PC      ) ? true : false; }
	function isIPHONE()		{ return ($this->G_AGENT_TYPE == D_IPHONE  ) ? true : false; }
	function isANDROID()	{ return ($this->G_AGENT_TYPE == D_ANDROID_1 ||  $this->G_AGENT_TYPE == D_ANDROID_2) ? true : false; }
	function isANDROID_1()	{ return ($this->G_AGENT_TYPE == D_ANDROID_1) ? true : false; }
	function isANDROID_2()	{ return ($this->G_AGENT_TYPE == D_ANDROID_2) ? true : false; }
	function isSmartPhone()	{ return ($this->isIPHONE() || $this->isANDROID()) ? true : false; }

}
?>