<?php
// ------------------------------------------------------------
// 2009/07/15 Y.Matsukawa	新規作成（AD Maplink対応）
// 2009/10/08 Y.Matsukawa	リクルート広告API 接続先変更
// ------------------------------------------------------------
//------------------------------------------------
// 定数 あとでd_serv等に出す
//------------------------------------------------
define("D_AD_SOCKETOPEN_TIMEOUT",5);//接続時(秒)
define("D_AD_SOCKET_TIMEOUT",5);//読込時(秒)

//事業者ごとの設定ファイル
//require_once("zdc_getad_recruit.inc");


//----------------------------------------------------------
// ファイル名：zdc_getad.inc
// 処理名：広告APIを読み込んだ結果を返す
//
// 作成日：2007/10/26
// 作成者：Bando@D&I
//
// 解説：リクルート広告APIを呼んで汎用形式に変換して返す
//
// 更新履歴
//   ・2007/10/26 Bando@D&I        新規作成
//----------------------------------------------------------
function zdc_getad(&$list,$opts){
	$ret = false;
	$list = "";
	
	//読み込みパターン
	switch($opts["ad"]) {
		case "rt001"://リクルート広告
			require_once("zdc_getad_recruit.inc");
			$ret = zdc_getad_recruit($list,$opts);
			break;
		// del 2009/07/15 Y.Matsukawa [
		//		case "ot002"://*ueda OPT広告
		//			require_once("zdc_getad_opt.inc");
		//			$ret = zdc_getad_opt($list,$opts);
		//			break;
		// del 2009/07/15 Y.Matsukawa ]
	}
	
	//戻り値
	return $ret;
}



//----------------------------------------------------------
// 処理名：広告API読み込み用ソケット通信
//
// 作成日：2007/10/26
// 作成者：Bando@D&I
//
// 解説：リクルート広告APIを呼んで汎用形式に変換して返す
//
// 更新履歴
//   ・2007/10/26 Bando@D&I        新規作成
//----------------------------------------------------------
//function ZdcHttpReadAD($url, &$status, $binary = 0, $timeout = D_AD_SOCKET_TIMEOUT){		mod 2009/10/08 Y.Matsukawa
function ZdcHttpReadAD($host, $url, &$status, $binary = 0, $timeout = D_AD_SOCKET_TIMEOUT){
	$status = 0;
	//$url_array = parse_url($url);		del 2009/10/08 Y.Matsukawa
	
	// ソケット作成
	//echo $url."<br>\n";
	//if(!$fp = fsockopen($url_array["host"], "80", $errno, $errstr, D_AD_SOCKETOPEN_TIMEOUT)){		mod 2009/10/08 Y.Matsukawa
	if(!$fp = fsockopen($host, "80", $errno, $errstr, D_AD_SOCKETOPEN_TIMEOUT)){
		$status = "timeout";
		return false;
	}
	socket_set_timeout($fp, $timeout);
	
	// 取得
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
	
	// HTTPヘッダ以降を取得
	// mod 2011/07/05 Y.Nakajima
	//$ret = split("\r\n\r\n",$line);
	$ret = explode("\r\n\r\n",$line);
	
	// 戻り値処理
	if(is_array($ret)){
		$out = "";
		
		// インデックスはHTTPヘッダ以降の１から始まるので注意
		$j = 0;
		for($i = 1 ; $i < count($ret) ; $i++){
			$out .= $ret[$i].($binary == true ? "" : "\n");
		}

		if($binary == true){
			return $out;
		} else { 
			// 取得したHTMLを出力
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
