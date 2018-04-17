<?PHP
// ------------------------------------------------------------
// 2016/02/03 N.Wada		新規作成（SMTのcarrier.incをコピー）
// 2016/02/05 N.Wada		現在地取得失敗時には指定したURLにリダイレクト可能に
// 							【不具合】handleError関数名が被らないようサフィックスをつける
// 2016/03/24 N.Wada		位置情報取得用のコールバック関数を返却（汎用バージョン)追加
// 2016/06/17 N.Wada		機種（OS）判定にスマホ判定を追加
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
		// Android 2.x以降
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
		// Android 2.x以降
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
			// 以下ＰＣの判定処理など
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
		default:
			$url .= "navigator.geolocation.getCurrentPosition(locupdate, handleError);";
			return $url;
		}
	}

	// add 2011/07/13 Y.Matsukawa
	//---------------------------------------------------------------
	// 位置情報取得用のスクリプトを返却
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
	// 位置情報取得用のコールバック関数を返却
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
	// 位置情報取得用のコールバック関数を返却（関数へ引渡し）
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
	// 位置情報取得用のコールバック関数を返却（汎用バージョン)
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
