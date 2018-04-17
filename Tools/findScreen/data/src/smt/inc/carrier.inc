<?PHP
// ------------------------------------------------------------
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/10/04 K.Masuda		検索TOPから現在地取得(GPS)利用可能にする
// 2012/05/23 Y.Matsukawa	formN.plfilterがhiddenの場合に対応
// 2012/07/20 Y.Matsukawa	GPSエラーメッセージをカスタマイズ可能に
// 2014/09/11 Y.Matsukawa	Android2.1判定
// 2016/03/24 N.Wada		位置情報取得用のコールバック関数を返却（汎用バージョン)追加
// 2016/04/27 H.Osamoto		ユーザエージェント判定ロジック不備修正
// 2016/09/28 Y.Matsukawa	POST遷移
// 2016/11/25 K.Tani		getCurrentPosition修正漏れ対応
// ------------------------------------------------------------
// USER_AGENT判定正規表現定義
define("D_REG_PC"   , "Mozilla");

// CARRIER判別文字列定義
define("D_IPHONE"   , "iPhone");
define("D_IPAD"     , "iPad");
define("D_ANDROID"  , "Android");
define("D_ANDROID_1", "Android_1");
define("D_ANDROID_2", "Android_2");
define("D_PC"       , "PC");

class CARRIER {
	var $G_USER_AGENT;
	var $G_AGENT_TYPE;
	var $G_ANDROID_2_1 = false;		// add 2014/09/11 Y.Matsukawa

	//---------------------------------------------------------------
	// コンストラクタ
	//---------------------------------------------------------------
	function CARRIER($P_USER_AGENT = ""){
		// 初期化処理を行う
		$this->initialize($P_USER_AGENT);
	}

	//---------------------------------------------------------------
	// 初期化処理
	//---------------------------------------------------------------
	function initialize($P_USER_AGENT){
		if($P_USER_AGENT){
			$this->G_USER_AGENT = $P_USER_AGENT;
			// 端末情報マスタから情報取得＆メンバ変数設定
			$ret = $this->getMobileInfo($P_USER_AGENT);
		}
	}

	//---------------------------------------------------------------
	// 端末情報マスタから機種（OS）判定
	//---------------------------------------------------------------
	function getMobileInfo($P_USER_AGENT){
		// 戻り配列の初期化
		$ret = Array("CARRIER"=>"","HEIGHT"=>"","WIDTH"=>"");

		// iPhone
		// mod 2011/07/05 Y.Nakajima
		//if (ereg(D_IPHONE, $P_USER_AGENT) || ereg(D_IPAD, $P_USER_AGENT)) {
		//	if (strpos($P_USER_AGENT, D_IPHONE) || strpos($P_USER_AGENT, D_IPAD)) {		mod 2016/04/27 H.Osamoto
		if ((strpos($P_USER_AGENT, D_IPHONE) !== false ) || (strpos($P_USER_AGENT, D_IPAD) !== false)) {
			$ret = Array(
				"CARRIER"=>D_IPHONE,
				"HEIGHT"=>320,
				"WIDTH"=>240
			);
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
		// Android 1.x
		// mod 2011/07/05 Y.Nakajima
		//} else if (ereg(D_ANDROID.' 1.', $P_USER_AGENT)) {
		//	} else if (strpos($P_USER_AGENT, D_ANDROID.' 1.')) {	mod 2016/04/27 H.Osamoto
		} else if (strpos($P_USER_AGENT, D_ANDROID.' 1.') !== false) {
			$ret = Array(
				"CARRIER"=>D_ANDROID_1,
				"HEIGHT"=>320,
				"WIDTH"=>260
			);
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
		// Android 2.x以降
		// mod 2011/07/05 Y.Nakajima
		//} else if (ereg(D_ANDROID, $P_USER_AGENT)) {
		//	} else if (strpos($P_USER_AGENT, D_ANDROID)) {	mod 2016/04/27 H.Osamoto
		} else if (strpos($P_USER_AGENT, D_ANDROID) !== false) {
			$ret = Array(
				"CARRIER"=>D_ANDROID_2,
				"HEIGHT"=>320,
				"WIDTH"=>260
			);
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
		} else {
			erl("非対応機種 USER_AGENT=[$P_USER_AGENT]");
		}

		switch($ret["CARRIER"]){
		// iPhone
		case D_IPHONE:
			$this->G_AGENT_TYPE = D_IPHONE;
			break;
		// Android 1.x
		case D_ANDROID_1:
			$this->G_AGENT_TYPE = D_ANDROID_1;
			break;
		// Android 2.x以降
		case D_ANDROID_2:
			$this->G_AGENT_TYPE = D_ANDROID_2;
			// add 2014/09/11 Y.Matsukawa [
			//	if (strpos($P_USER_AGENT, 'Android 2.1')) {	mod 2016/04/27 H.Osamoto
			if (strpos($P_USER_AGENT, 'Android 2.1') !== false) {
				$this->G_ANDROID_2_1 = true;
			}
			// add 2014/09/11 Y.Matsukawa ]
			break;
		default:
			// 以下ＰＣの判定処理など
			// mod 2011/07/05 Y.Nakajima
			//if( ereg(D_REG_PC, $P_USER_AGENT) ){
			if( preg_match("/".D_REG_PC."/", $P_USER_AGENT, $matches) !== false){
				$this->G_AGENT_TYPE = D_PC;
			} else {
				// エラー画面表示
				header("Content-Type: text/html;charset=UTF-8");
				echo mb_convert_encoding("アクセスできません。", "UTF-8","EUC-JP");
				exit;
			}
		}
		return $ret;
	}

	//---------------------------------------------------------------
	// 位置情報取得用のＵＲＬを返却（Ａタグ用）
	//---------------------------------------------------------------
	function MakeLocationSearchUrl(){
		$url = "javascript:";
		$url .= "ZdcEmapLocProgress();";
		switch($this->G_AGENT_TYPE){
		// iPhone
		case D_IPHONE:
			//$url .= "navigator.geolocation.watchPosition(locupdate, handleError);";		mod 2016/11/25 K.Tani
			$url .= "navigator.geolocation.getCurrentPosition(locupdate, handleError);";
			return $url;
			break;
		// Android 1.x
		case D_ANDROID_1:
			$url .= "geo.getCurrentPosition(locupdate, handleError);";
			return $url;
			break;
		// Android 2.x以降
		case D_ANDROID_2:
			//$url .= "navigator.geolocation.watchPosition(locupdate, handleError);";
			//$url .= "navigator.geolocation.watchPosition(locupdate, handleError, {enableHighAccuracy:true,gearsLocationProviderUrls:[]});";
			//$url .= "navigator.geolocation.watchPosition(locupdate, handleError, {enableHighAccuracy:true});";		mod 2016/11/25 K.Tani
			$url .= "navigator.geolocation.getCurrentPosition(locupdate, handleError, {enableHighAccuracy:true});";
			return $url;
			break;
		default:
			return "#";
		}
	}

	// add 2011/07/13 Y.Matsukawa
	//---------------------------------------------------------------
	// 位置情報取得用のスクリプトを返却
	//---------------------------------------------------------------
	//function MakeLocationSearchScript(){		mod 2012/02/27 Y.Matsukawa
	function MakeLocationSearchScript($callback_suffix=''){
		switch($this->G_AGENT_TYPE){
		// iPhone
		case D_IPHONE:
			//$url = "watchId=navigator.geolocation.watchPosition(locupdate, handleError);";		mod 2012/02/27 Y.Matsukawa
			//$url = "watchId=navigator.geolocation.watchPosition(locupdate$callback_suffix, handleError);";		mod 2016/03/15 Y.Matsukawa
			//$url = "watchId=navigator.geolocation.watchPosition(locupdate$callback_suffix, handleError$callback_suffix);";		mod 2016/09/28 Y.Matsukawa
			$url = "watchId=navigator.geolocation.getCurrentPosition(locupdate$callback_suffix, handleError$callback_suffix);";
			return $url;
			break;
		// Android 1.x
		case D_ANDROID_1:
			//$url = "geo.getCurrentPosition(locupdate, handleError);";		mod 2012/02/27 Y.Matsukawa
			//$url = "geo.getCurrentPosition(locupdate$callback_suffix, handleError);";		mod 2016/03/15 Y.Matsukawa
			$url = "geo.getCurrentPosition(locupdate$callback_suffix, handleError$callback_suffix);";
			return $url;
			break;
		// Android 2.x以降
		case D_ANDROID_2:
			//$url = "navigator.geolocation.watchPosition(locupdate, handleError);";
			//$url = "navigator.geolocation.watchPosition(locupdate, handleError, {enableHighAccuracy:true,gearsLocationProviderUrls:[]});";
			//$url = "watchId=navigator.geolocation.watchPosition(locupdate, handleError, {enableHighAccuracy:true});";		mod 2012/02/27 Y.Matsukawa
			//$url = "watchId=navigator.geolocation.watchPosition(locupdate$callback_suffix, handleError, {enableHighAccuracy:true});";		mod 2016/03/15 Y.Matsukawa
			//$url = "watchId=navigator.geolocation.watchPosition(locupdate$callback_suffix, handleError$callback_suffix, {enableHighAccuracy:true});";		mod 2016/09/28 Y.Matsukawa
			$url = "watchId=navigator.geolocation.getCurrentPosition(locupdate$callback_suffix, handleError$callback_suffix, {enableHighAccuracy:true});";
			return $url;
			break;
		default:
			return "";
		}
	}

	//---------------------------------------------------------------
	// 位置情報取得用のコールバック関数を返却
	//---------------------------------------------------------------
	//function MakeLocationCallbackFunc($url){		mod 2012/02/27 Y.Matsukawa
	//function MakeLocationCallbackFunc($url, $callback_suffix=''){		mod 2016/03/15 Y.Matsukawa
	//function MakeLocationCallbackFunc($url, $callback_suffix='', $err_url=''){		mod 2016/09/28 Y.Matsukawa
	function MakeLocationCallbackFunc($url, $callback_suffix='', $err_url='', $post=0){
		switch($this->G_AGENT_TYPE){
		// iPhone
		case D_IPHONE:
		// Android 2.x以降
		case D_ANDROID_2:
			$func = '';
			//$func .= 'function locupdate(pos){';		mod 2012/02/27 Y.Matsukawa
			$func .= "function locupdate$callback_suffix(pos){";
			$func .= 'var lat=pos.coords.latitude;var lon = pos.coords.longitude;';
			// del 2012/05/23 Y.Matsukawa [
			//			// mod 2011/10/04 K.Masuda [
			//			//$func .= 'window.location.href="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			//			$func .= '  if(flt!=""){';
			//			$func .= '    window.location.href="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1&plfilter="+flt;';
			//			$func .= '  } else {';
			//			$func .= '    window.location.href="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			//			$func .= '  }';
			//			// mod 2011/10/04 K.Masuda ]
			// del 2012/05/23 Y.Matsukawa ]
			// add 2012/05/23 Y.Matsukawa [
			$func .= 'var url="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			$func .= 'if(flt!="") url+="&plfilter="+flt;';
			$func .= 'if(ZdcEmapGPSCondParams!="") url+=ZdcEmapGPSCondParams;';
			//$func .= 'window.location.href=url;';		del 2016/09/28 Y.Matsukawa
			// add 2012/05/23 Y.Matsukawa ]
			// add 2016/09/28 Y.Matsukawa [
			if ($post) {
				$func .= 'ZdcEmapSubmitPOST(url);';
			} else {
				$func .= 'window.location.href=url;';
			}
			// add 2016/09/28 Y.Matsukawa ]
			$func .= '}';
			//$func .= 'function handleError(err) {';		mod 2016/03/15 Y.Matsukawa
			$func .= "function handleError$callback_suffix(err) {";
			$func .= 'ZdcEmapLocFinish();';
			//$func .= 'alert("現在地の取得に失敗しました");';		mod 2012/07/20 Y.Matsukawa
			$func .= 'alert(ZdcEmapGPSErrMsg);';
			//if ($err_url) $func .= 'window.location.href="'.$err_url.'";';		// del 2016/03/15 Y.Matsukawa	del 2016/09/28 Y.Matsukawa
			// add 2016/09/28 Y.Matsukawa [
			if ($err_url) {
				if ($post) {
					$func .= 'ZdcEmapSubmitPOST("'.$err_url.'");';
				} else {
					$func .= 'window.location.href="'.$err_url.'";';
				}
			}
			// add 2016/09/28 Y.Matsukawa ]
			$func .= '}';
			return $func;
			break;
		// Android 1.x
		case D_ANDROID_1:
			$func = '';
			$func .= 'var geo = google.gears.factory.create("beta.geolocation");';
			//$func .= 'function locupdate(pos) {';		mod 2012/02/27 Y.Matsukawa
			$func .= "function locupdate$callback_suffix(pos) {";
			$func .= 'var lat = pos.latitude; var lon = pos.longitude;';
			// del 2012/05/23 Y.Matsukawa [
			//			// mod 2011/10/04 K.Masuda [
			//			//$func .= 'window.location.href = "'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			//			$func .= '  if(flt!=""){';
			//			$func .= '    window.location.href="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1&plfilter="+flt;';
			//			$func .= '  } else {';
			//			$func .= '    window.location.href="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			//			$func .= '  }';
			//			// mod 2011/10/04 K.Masuda ]
			// del 2012/05/23 Y.Matsukawa ]
			// add 2012/05/23 Y.Matsukawa [
			$func .= 'var url="'.$url.'"+"&lat="+lat+"&lon="+lon+"&datum=WGS84&loc=1";';
			$func .= 'if(flt!="") url+="&plfilter="+flt;';
			$func .= 'if(ZdcEmapGPSCondParams!="") url+=ZdcEmapGPSCondParams;';
			$func .= 'window.location.href=url;';
			// add 2012/05/23 Y.Matsukawa ]
			$func .= '}';
			//$func .= 'function handleError(err) {';		mod 2016/03/15 Y.Matsukawa
			$func .= "function handleError$callback_suffix(err) {";
			$func .= 'ZdcEmapLocFinish();';
			//$func .= 'alert("現在地の取得に失敗しました");';		mod 2012/07/20 Y.Matsukawa
			$func .= 'alert(ZdcEmapGPSErrMsg);';
			if ($err_url) $func .= 'window.location.href="'.$err_url.'";';		// add 2016/03/15 Y.Matsukawa
			$func .= '}';
			return $func;
			break;
		default:
			return '';
		}
	}

	// add 2011/07/13 Y.Matsukawa
	//---------------------------------------------------------------
	// 位置情報取得用のコールバック関数を返却（関数へ引渡し）
	//---------------------------------------------------------------
	function MakeLocationCallbackFuncCall($callback_func, $error_func, $shop_lat, $shop_lon){
		switch($this->G_AGENT_TYPE){
		// iPhone
		case D_IPHONE:
		// Android 2.x以降
		case D_ANDROID_2:
			$func = '';
			$func .= 'var watchId;';
			$func .= 'function locupdate(pos){';
			$func .= 'var lat=pos.coords.latitude;var lon = pos.coords.longitude;';
			$func .= 'if(watchId>0) navigator.geolocation.clearWatch(watchId);';
			$func .= $callback_func.'(lat,lon,'.$shop_lat.','.$shop_lon.');';
			$func .= '}';
			$func .= 'function handleError(err) {';
			$func .= 'if(watchId>0) navigator.geolocation.clearWatch(watchId);';
			if($error_func) $func .= $error_func.'();';
			//$func .= 'alert("現在地の取得に失敗しました");';		mod 2012/07/20 Y.Matsukawa
			$func .= 'alert(ZdcEmapGPSErrMsg);';
			$func .= '}';
			return $func;
			break;
		// Android 1.x
		case D_ANDROID_1:
			$func = '';
			$func .= 'var geo = google.gears.factory.create("beta.geolocation");';
			$func .= 'function locupdate(pos) {';
			$func .= 'var lat = pos.latitude; var lon = pos.longitude;';
			$func .= $callback_func.'(lat,lon,'.$shop_lat.','.$shop_lon.');';
			$func .= '}';
			$func .= 'function handleError(err) {';
			if($error_func) $func .= $error_func.'();';
			//$func .= 'alert("現在地の取得に失敗しました");';		mod 2012/07/20 Y.Matsukawa
			$func .= 'alert(ZdcEmapGPSErrMsg);';
			$func .= '}';
			return $func;
			break;
		default:
			return '';
		}
	}

	// add 2016/03/24 N.Wada
	//---------------------------------------------------------------
	// 位置情報取得用のコールバック関数を返却（汎用バージョン)
	//---------------------------------------------------------------
	function MakeLocationCallbackFuncCallGeneric($callback_stmt, $error_stmt, $callback_suffix=''){
		switch($this->G_AGENT_TYPE){
		// iPhone
		case D_IPHONE:
		// Android 2.x以降
		case D_ANDROID_2:
			$func = '';
			$func .= "function locupdate$callback_suffix(pos){";
			$func .= '  if(watchId>0) navigator.geolocation.clearWatch(watchId);';
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
			break;
		default:
			return '';
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
