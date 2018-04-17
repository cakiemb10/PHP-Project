<?PHP
//==============================================================================
// パラメータ位置情報取得（J-PHONE2型など.HTMを画像として認識しない端末対応）
// 上記該当機種の場合、URLがhttp://SERVER/mi.htm/pos=xxxxxxx/a.pngとなるため、
// また、位置情報を送信してくる場合も、上記のＵＲＬとしている。
// htm/以降をパラメータとして取得する
//
// 2009/03/17 Y.Matsukawa	【不具合修正】一部機種で現在地取得すると、nmパラメータが壊れる場合がある
//                           →nmパラメータをEUCで渡していたのを、SJISで渡すよう修正
//                           →「&」「?」「/」が含まれているとその位置で切れてしまうので、キーワード「_A_」「_Q_」「_S_」に置換する
// 2009/06/15 Y.Matsukawa	optパラメータをずっと引き継ぐ
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/11 H.Osamoto		【不具合修正】auで現在地取得すると、nmパラメータが壊れる場合がある
//                           →「 」（半角スペース）が含まれているとその位置で切れてしまうので、キーワード「_B_」に置換する
// 2015/06/12 Y.Matsukawa	auの現在地取得後、setting_option内でパラメータが取得できない
//==============================================================================
$REQUEST_URI = (isset($_SERVER['REQUEST_URI'])?$_SERVER['REQUEST_URI']:"");		// add 2015/06/12 Y.Matsukawa
if(strpos($REQUEST_URI,".htm/") > -1){
	//dbl("REQUEST[$REQUEST_URI]");		del 2015/06/12 Y.Matsukawa
	$prm = substr($REQUEST_URI, strpos($REQUEST_URI,".htm/")+5, strlen($REQUEST_URI));
	// mod 2011/07/05 Y.Nakajima
	//$wk = split("(&|\/|\?)", $prm);
	$wk = preg_split("/[\&\/\?]+/", $prm);

	foreach($wk as $value){
		// mod 2011/07/05 Y.Nakajima
		//$prm = split("=", $value);
		$prm = explode("=", $value);
		if(count($prm) == 2){
			if($prm[0] == "pos"){
				if(strpos($prm[1], ".") > -1){
					$pos_ll = $prm[1];
				} else {
					$pos_enc = $prm[1];
				}
			}
			// add 2009/03/17 Y.Matsukawa [
			//if($prm[0] == "nm"){		mod 2009/07/15 Y.Matsukawa
			if($prm[0] == "nm" || $prm[0] == "nm2" || $prm[0] == "tel" || $prm[0] == "cm" || $prm[0] == "t" || $prm[0] == "a"){
				if(strpos($prm[1], '_A_') > -1){
					$prm[1] = str_replace('_A_', '%26', $prm[1]);
				}
				if(strpos($prm[1], '_Q_') > -1){
					$prm[1] = str_replace('_Q_', '%3F', $prm[1]);
				}
				if(strpos($prm[1], '_S_') > -1){
					$prm[1] = str_replace('_S_', '%2F', $prm[1]);
				}
				// add 2011/08/11 H.osamoto [
				if(strpos($prm[1], '_B_') > -1){
					$prm[1] = str_replace('_B_', '%20', $prm[1]);
				}
				// add 2011/08/11 H.osamoto ]
			}
			// add 2009/03/17 Y.Matsukawa ]
			$$prm[0] = $prm[1];
			$_GET[$prm[0]] = $prm[1];
		// add 2009/06/15 Y.Matsukawa [
		// optパラメータに対応
		// 「opt=COL_01=02」「opt=COL_01=02@COL_02=1」
		} else if (count($prm) > 2) {
			if ($prm[0] == "opt") {
				array_shift(&$prm);
				$prm = implode('=', $prm);
				$opt = $prm;
			}
		// add 2009/06/15 Y.Matsukawa ]
		}
	}
// add 2009/03/17 Y.Matsukawa [
} else {
	// mod 2011/07/05 Y.Nakajima [
	//$wk = split("(&|\/|\?)", $prm);
	if (isset($prm) && $prm != "") {
		$wk = explode($prm, "(&|\/|\?)");
	// mod 2011/07/05 Y.Nakajima ]

	foreach($wk as $value){
		// mod 2011/07/05 Y.Nakajima
		//$prm = split("=", $value);
		$prm = explode("=", $value);
		if(count($prm) == 2){
			//if($prm[0] == "nm"){		mod 2009/07/15 Y.Matsukawa
			if($prm[0] == "nm" || $prm[0] == "nm2" || $prm[0] == "tel" || $prm[0] == "cm" || $prm[0] == "t" || $prm[0] == "a"){
				if(strpos($prm[1], '_A_') > -1){
					$prm[1] = str_replace('_A_', '%26', $prm[1]);
				}
				if(strpos($prm[1], '_Q_') > -1){
					$prm[1] = str_replace('_Q_', '%3F', $prm[1]);
				}
				if(strpos($prm[1], '_S_') > -1){
					$prm[1] = str_replace('_S_', '%2F', $prm[1]);
				}
				// add 2011/08/11 H.osamoto [
				if(strpos($prm[1], '_B_') > -1){
					$prm[1] = str_replace('_B_', '%20', $prm[1]);
				}
				// add 2011/08/11 H.osamoto ]
				$$prm[0] = $prm[1];
				$_GET[$prm[0]] = $prm[1];
			}
		// add 2009/06/15 Y.Matsukawa [
		// optパラメータに対応
		// 「opt=COL_01=02」「opt=COL_01=02@COL_02=1」
		} else if (count($prm) > 2) {
			if ($prm[0] == "opt") {
				array_shift(&$prm);
				$prm = implode('=', $prm);
				$opt = $prm;
			}
		// add 2009/06/15 Y.Matsukawa ]
		}
	}
	// mod 2011/07/05 Y.Nakajima [
	} else {
		
	}
	// mod 2011/07/05 Y.Nakajima ]

// add 2009/03/17 Y.Matsukawa ]
}
?>
