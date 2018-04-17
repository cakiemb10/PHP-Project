<?PHP
// ------------------------------------------------------------
// 2009/05/11 Y.Matsukawa	au GPS対応
// 2009/05/18 Y.Matsukawa	docomo絵文字記述方法を変更（SJISテキスト→Unicodeテキスト）
// 2009/06/18 Y.Matsukawa	携帯３キャリア以外でも本番を閲覧可能にする機能を追加
// 2009/06/29 Y.Matsukawa	任意パラメータ追加
// 2009/11/10 Y.Matsukawa	開発機VM化
// 2010/03/15 Y.Matsukawa	未サポート端末アクセス時のメール送信処理を削除
// 2010/03/17 Y.Matsukawa	オートGPSリマインド
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/08/12 Y.Matsukawa	iPhone対応
// 2010/10/20 Y.Matsukawa	Android対応
// 2011/04/21 c_hanajima	絵文字増量
// 2011/06/08 Y.Matsukawa	スマートフォン版対応
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2013/04/11 H.Osamoto		プレビュー機能を利用可能に修正
// 2016/07/05 N.Wada		PC、不明端末からのアクセス時のリダイレクト先URL追加
// ------------------------------------------------------------
// USER_AGENT判定正規表現定義
define("D_REG_WILL"    , "(DDIPOCKET|WILLCOM);");
define("D_REG_PC"      , "Mozilla");

// CARRIER判別文字列定義
define("D_DOCOMO"  , "DoCoMo");
define("D_SOFTBANK", "SOFTBANK");
define("D_KDDI"    , "KDDI");
define("D_HDML"    , "HDML");
define("D_WILL"    , "WILLCOM");
define("D_IPHONE"  , "iPhone");		// add 2010/08/12 Y.Matsukawa
define("D_ANDROID"  , "Android");	// add 2010/10/20 Y.Matsukawa
define("D_ANDROID_1", "Android_1");	// add 2010/10/20 Y.Matsukawa
define("D_ANDROID_2", "Android_2");	// add 2010/10/20 Y.Matsukawa
define("D_PC"      , "PC");

// PCからのアクセスを許可するサーバーＩＰ
// 通常検証環境までを許可にして、本番は許可させない。
// 但し、下記ドメインチェックを有効とした場合、無効となる。
//define("D_ALLOW_PC", "(^192\.168\.1\.11$|^10\.40\.3\.123$|^218\.225\.89\.29$|^172\.16\.162\.20$|^210\.133\.109\.144$|^test.e-map.ne.jp$)");	mod 2009/11/10 Y.Matsukawa
//define("D_ALLOW_PC", "(^10\.47\.50\.26$|^218\.225\.89\.139$|^192\.168\.1\.11$|^10\.40\.3\.123$|^218\.225\.89\.29$|^172\.16\.162\.20$|^210\.133\.109\.144$|^test.e-map.ne.jp$)");
//define("D_ALLOW_PC", "(^10\.47\.50\.79$|^210\.133\.109\.211$|^10\.47\.50\.26$|^218\.225\.89\.139$|^192\.168\.1\.11$|^10\.40\.3\.123$|^218\.225\.89\.29$|^172\.16\.162\.20$|^210\.133\.109\.144$|^test.e-map.ne.jp|^172\.16\.162\.19$)");	// mod 2011/07/05 Y.Nakajima	// mod 2013/04/11 H.Osamoto
define("D_ALLOW_PC", "(^10\.47\.50\.79$|^210\.133\.109\.211$|^10\.47\.50\.26$|^218\.225\.89\.139$|^192\.168\.1\.11$|^10\.40\.3\.123$|^218\.225\.89\.29$|^172\.16\.162\.20$|^210\.133\.109\.144$|^test.e-map.ne.jp|^172\.16\.162\.19|^172\.16\.162\.204$)");

// GPS携帯なのに、リンクが使えない機種・・・っておい
define("D_GPS_LINK_NS", "(F661i|F505iGPS)");

//******************************************
//* 携帯キャリア識別クラス
//******************************************
class CARRIER {
	var $G_USER_AGENT;
	var $G_AGENT_TYPE;
	var $G_DOMAIN;
	var $G_EMOJI = array();
	var $G_REPLACEWORD = array();
	var $G_REPLACEWORD_CNT = 0;
	var $G_SUPPORT_IMAGE_EXT;
	var $G_SUPPORT_CMDN_TYP;
	var $G_SUPPORT_LOCATION;
	var $G_DISPLAY_W = 0;
	var $G_DISPLAY_H = 0;
	var $G_DISPLAY_COL;
	var $G_AUTOGPS = 0;		// add 2010/03/17 Y.Matsukawa

	//---------------------------------------------------------------
	// コンストラクタ
	// 引数：USER_AGENT・・・指定した場合、絵文字など利用可能となる。
	//---------------------------------------------------------------
	function CARRIER($P_USER_AGENT = ""){
		// 初期化処理を行う
		$this->initialize($P_USER_AGENT);
	}

	//---------------------------------------------------------------
	// 初期化処理（コンストラクタにUSER_AGENTを指定した場合不要）
	//---------------------------------------------------------------
	function initialize($P_USER_AGENT){
		if($P_USER_AGENT){
			$this->G_USER_AGENT = $P_USER_AGENT;

			// 端末情報マスタから情報取得＆メンバ変数設定
			$ret = $this->getMobileInfo($P_USER_AGENT);

			// 判定結果を保持
//			$this->G_AGENT_TYPE = $this->getCarrierAgent( $P_USER_AGENT );

			// 絵文字初期化
			$this->setEmojiArray( $this->G_AGENT_TYPE );

			// 機種マスタから取得済みは何もしない
			if( $this->G_DISPLAY_W == 0 || $this->G_DISPLAY_H == 0){
				// 画面サイズ情報取得
				$this->setDisplayInfo( $this->G_AGENT_TYPE );
			}
		}
	}

	//---------------------------------------------------------------
	// 端末情報マスタからキャリア情報、画面情報取得
	//---------------------------------------------------------------
	function getMobileInfo($P_USER_AGENT){
/*
		print   $ARR['CARRIER'] . "\t";
		print   $ARR['GENERATION']  . "\t";
		print   $ARR['HEIGHT']  . "\t";
		print   $ARR['WIDTH']   . "\t";
		print   $ARR['IMAGE_TYPE']  . "\t";
		print   $ARR['GPS_FLG'] . "\t";
		print   $ARR['IR_FLG']  . "\t";
		print   $ARR['TEMPLATE_TYPE']   . "\t";
		print   $ARR['WEB_APP'] . "\t";
		print   $ARR['COLOR']   . "\n";
*/
		// 戻り配列の初期化
		$ret = Array("CARRIER"=>"","GENERATION"=>"","HEIGHT"=>"","WIDTH"=>"","IMAGE_TYPE"=>"","GPS_FLG"=>"","COLOR"=>"");

		global $D_SSAPI;
		global $D_OPEN_ACCESS;		// add 2009/06/18 Y.Matsukawa
		global $SETTING;			// add 2009/06/18 Y.Matsukawa
		global $D_IPHONE_ACCESS;	// add 2010/08/12 Y.Matsukawa
		global $D_ANDROID_ACCESS;	// add 2010/10/20 Y.Matsukawa
		global $D_UA_PC_REDIRECT_URL;		// add 2016/07/05 N.Wada
		global $D_UA_UNKOWN_REDIRECT_URL;	// add 2016/07/05 N.Wada

		// 端末情報取得ＣＧＩ
		$url = $D_SSAPI["getmobileinfo"]."?ua=".urlencode($P_USER_AGENT);

		$d = ZdcHttpRead($url,false,D_SOCKET_TIMEOUT);

		$status_str = array_shift($d);
		$status  = explode("\t", $status_str);

		// CGIの戻り値取得
		// del 2010/10/20 Y.Matsukawa [
		//		if($status == "79011009"){
		//			erl("端末情報未登録 USER_AGENT=[$P_USER_AGENT]");
		//			// add 2010/08/12 Y.Matsukawa [
		//			if ($D_IPHONE_ACCESS) {
		//				// iPhone
		//				if (ereg(D_IPHONE, $P_USER_AGENT)) {
		//					$ret = Array(
		//						"CARRIER"=>D_IPHONE,
		//						"HEIGHT"=>320,
		//						"WIDTH"=>240
		//					);
		//					$this->G_DISPLAY_W = $ret["WIDTH"];
		//					$this->G_DISPLAY_H = $ret["HEIGHT"];
		//				}
		//			}
		//			// add 2010/08/12 Y.Matsukawa ]
		//		} else if(!ereg("^790[0]+$",$status[0])){
		//			erl("USER_AGENT取得エラー[$url][$status_str][".$d[0]."]");
		//			// add 2010/08/12 Y.Matsukawa [
		//			if ($D_IPHONE_ACCESS) {
		//				// iPhone
		//				if (ereg(D_IPHONE, $P_USER_AGENT)) {
		//					$ret = Array(
		//						"CARRIER"=>D_IPHONE,
		//						"HEIGHT"=>320,
		//						"WIDTH"=>240
		//					);
		//					$this->G_DISPLAY_W = $ret["WIDTH"];
		//					$this->G_DISPLAY_H = $ret["HEIGHT"];
		//				}
		//			}
		//			// add 2010/08/12 Y.Matsukawa ]
		// del 2010/10/20 Y.Matsukawa [
		// add 2010/10/20 Y.Matsukawa [
		// mod 2011/07/05 Y.Nakajima
		//if($status == "79011009" || !ereg("^790[0]+$",$status[0])){
		if($status == "79011009" || !preg_match("/^790[0]+$/",$status[0], $matches)){
			// iPhone
			// mod 2011/07/05 Y.Nakajima
			//if ($D_IPHONE_ACCESS && ereg(D_IPHONE, $P_USER_AGENT)) {
			if ($D_IPHONE_ACCESS && strpos($P_USER_AGENT, D_IPHONE)) {
				$ret = Array(
					"CARRIER"=>D_IPHONE,
					"HEIGHT"=>320,
					"WIDTH"=>240
				);
				$this->G_DISPLAY_W = $ret["WIDTH"];
				$this->G_DISPLAY_H = $ret["HEIGHT"];
			// Android 1.x
			// mod 2011/07/05 Y.Nakajima
			//} else if ($D_ANDROID_ACCESS && ereg(D_ANDROID.' 1.', $P_USER_AGENT)) {
			} else if ($D_ANDROID_ACCESS && strpos($P_USER_AGENT, D_ANDROID.' 1.')) {
				$ret = Array(
					"CARRIER"=>D_ANDROID_1,
					"HEIGHT"=>320,
					"WIDTH"=>260
				);
				$this->G_DISPLAY_W = $ret["WIDTH"];
				$this->G_DISPLAY_H = $ret["HEIGHT"];
			// Android 2.x以降
			// mod 2011/07/05 Y.Nakajima
			//} else if ($D_ANDROID_ACCESS && ereg(D_ANDROID, $P_USER_AGENT)) {
			} else if ($D_ANDROID_ACCESS && strpos($P_USER_AGENT, D_ANDROID)) {
				$ret = Array(
					"CARRIER"=>D_ANDROID_2,
					"HEIGHT"=>320,
					"WIDTH"=>260
				);
				$this->G_DISPLAY_W = $ret["WIDTH"];
				$this->G_DISPLAY_H = $ret["HEIGHT"];
			} else {
				if($status == "79011009"){
					erl("端末情報未登録 USER_AGENT=[$P_USER_AGENT]");
				// mod 2011/07/05 Y.Nakajima [
				//} else if(!ereg("^790[0]+$",$status[0])){
				//	erl("USER_AGENT取得エラー[$url][$status_str][".$d[0]."]");
				} else if(preg_match("/^790[0]+$/",$status[0], $matches) !== true){
					erl("USER_AGENT取得エラー[$url][$status_str][".$d[0]."]");
				// mod 2011/07/05 Y.Nakajima ]
				}
			}
		// add 2010/10/20 Y.Matsukawa ]
		} else {
			$mobile_array = explode("\t", $d[0]);
			erl("CARRIER INFO [".$d[0]."]");
			$ret = Array(
				"CARRIER"=>$mobile_array[0],
				"GENERATION"=>$mobile_array[1],
				"HEIGHT"=>$mobile_array[2],
				"WIDTH"=>$mobile_array[3],
				"IMAGE_TYPE"=>$mobile_array[4],
				"GPS_FLG"=>$mobile_array[5],
				"COLOR"=>$mobile_array[9],
				"AUTOGPS"=>$mobile_array[19]		// add 2010/03/17 Y.Matsukawa
			);

			$this->G_SUPPORT_LOCATION  = $ret["GPS_FLG"];
			$this->G_DISPLAY_W = $ret["WIDTH"];
			$this->G_DISPLAY_H = $ret["HEIGHT"];
			$this->G_AUTOGPS = $ret["AUTOGPS"];		// add 2010/03/17 Y.Matsukawa
		}

		// 取得したキャリア毎の判定処理
		switch($ret["CARRIER"]){
		case "1":
			//DOCOMO
			$this->G_AGENT_TYPE = D_DOCOMO;
			if($SETTING["animation"]){
				$this->G_DISPLAY_W -= 20;
				$this->G_DISPLAY_H -= 50;
			}
			break;
		case "2":
			//AU
			$this->G_AGENT_TYPE = D_KDDI;
			break;
		case "3":
			//SOFTBANK
			$this->G_AGENT_TYPE = D_SOFTBANK;
				// mod 2011/07/05 Y.Nakajima
				//if(ereg("(Vodafone|^MOT-|SoftBank)", $this->G_USER_AGENT)){
				if(preg_match("/(Vodafone|^MOT-|SoftBank)/", $this->G_USER_AGENT, $matches)){
					$this->G_DISPLAY_W -= 10;
					$this->G_DISPLAY_H -= 50;
				// パケット機 (5.X 以外)
				// mod 2011/07/05 Y.Nakajima
				//} else if(ereg("4\.", $this->G_USER_AGENT)){
				} else if(strpos($this->G_USER_AGENT, "4\.")){
					if(( $this->G_DISPLAY_W + $this->G_DISPLAY_H) > 400){
						$this->G_DISPLAY_W = 160;
						$this->G_DISPLAY_H = 180;
					}
				//  パケット機以外
				// mod 2011/07/05 Y.Nakajima
				//} else if(!ereg("5\.", $this->G_USER_AGENT)){
				} else if(!strpos($this->G_USER_AGENT, "5\.")){
					if(( $this->G_DISPLAY_W + $this->G_DISPLAY_H) > 230){
						// 画面がでかいやつは固定サイズで
						$this->G_DISPLAY_W = 60;
						$this->G_DISPLAY_H = 60;
					} else {
						// 230 より小さいものはたいがい出るのでちょと小さくして出す
						$this->G_DISPLAY_W -= 25;
						$this->G_DISPLAY_H -= 35;
					}
				}
			break;
		// add 2010/08/12 Y.Matsukawa [
		case D_IPHONE:
			$this->G_AGENT_TYPE = D_IPHONE;
			break;
		// add 2010/08/12 Y.Matsukawa ]
		// add 2010/10/20 Y.Matsukawa [
		case D_ANDROID_1:
			$this->G_AGENT_TYPE = D_ANDROID_1;
			break;
		case D_ANDROID_2:
			$this->G_AGENT_TYPE = D_ANDROID_2;
			break;
		// add 2010/10/20 Y.Matsukawa ]
		default:
			// 以下ＰＣの判定処理など
			// mod 2011/07/05 Y.Nakajima
			//if( ereg(D_REG_WILL,$P_USER_AGENT) ){
			if( strpos($P_USER_AGENT, D_REG_WILL) !== false){
				$this->G_AGENT_TYPE = D_WILL;
			// mod 2011/07/05 Y.Nakajima
			//} else if( ereg(D_REG_PC,$P_USER_AGENT) ){
			} else if( strpos($P_USER_AGENT, D_REG_PC) !== false){
				// add 2009/06/18 Y.Matsukawa [
				// mod 2011/07/05 Y.Nakajima
				if (isset($D_OPEN_ACCESS) && $D_OPEN_ACCESS) {
					$SETTING["location"] = 0;
					$SETTING["routesearch"] = 0;
				}
				// add 2009/06/18 Y.Matsukawa ]
				// mod 2011/07/05 Y.Nakajima
				//if(ereg(D_ALLOW_PC, $_SERVER["HTTP_HOST"])){
				//判定条件結果1ならばブラウザからでも閲覧可能
				if(preg_match(D_ALLOW_PC,$_SERVER["HTTP_HOST"], $matches) == true){
					$this->G_AGENT_TYPE = D_PC;
				// add 2009/06/18 Y.Matsukawa [
				// 「未サポート端末でも閲覧可能」に設定されている場合は無条件でアクセス可
				} else if (isset($D_OPEN_ACCESS) && $D_OPEN_ACCESS) {
					$this->G_AGENT_TYPE = D_PC;
				// add 2009/06/18 Y.Matsukawa ]
				// add 2016/07/05 N.Wada [
				// UAがPCの場合は、指定URLへリダイレクト
				} else if (isset($D_UA_PC_REDIRECT_URL) && $D_UA_PC_REDIRECT_URL) {
					header('Location: '.$D_UA_PC_REDIRECT_URL);
					exit;
				// add 2016/07/05 N.Wada ]
				} else {
					header("Content-Type: text/html;charset=Shift_JIS");
					echo mb_convert_encoding("アクセスできません。(".$_SERVER["HTTP_HOST"].")", "SJIS-win","eucJP-win");
					exit;
				}
			} else {
				$allow_access = false;
				// add 2009/06/18 Y.Matsukawa [
				// mod 2011/07/05 Y.Nakajima
				if (isset($D_OPEN_ACCESS) && $D_OPEN_ACCESS) {
					$SETTING["location"] = 0;
					$SETTING["routesearch"] = 0;
				}
				// add 2009/06/18 Y.Matsukawa ]
				// 検証環境までの判定
				// mod 2011/07/05 Y.Nakajima
				//if(ereg(D_ALLOW_PC, $_SERVER["HTTP_HOST"])){
				if(strpos($_SERVER["HTTP_HOST"], D_ALLOW_PC)){
					// 以下検証環境まではエミュレータを許諾
					// mod 2011/07/05 Y.Nakajima
					//if(ereg("DoCoMo\/2\.0 ISIM", $P_USER_AGENT)){
					if(strpos($P_USER_AGENT, "DoCoMo\/2\.0 ISIM")){
						$this->G_AGENT_TYPE = D_DOCOMO;
						$allow_access = true;
					// mod 2011/07/05 Y.Nakajima
					//} else if(ereg("(^J-EMULATOR|^Vemulator|^MOTEMULATOR|^Semulator)")) {
					} else if(strpos($P_USER_AGENT, "(^J-EMULATOR|^Vemulator|^MOTEMULATOR|^Semulator)")) {
						$this->G_AGENT_TYPE = D_SOFTBANK;
						$allow_access = true;
					// add 2009/06/18 Y.Matsukawa [
					// 「未サポート端末でも閲覧可能」に設定されている場合は無条件でアクセス可
					// mod 2011/07/05 Y.Nakajima
					} else if (isset($D_OPEN_ACCESS) && $D_OPEN_ACCESS) {
						$this->G_AGENT_TYPE = D_PC;
						$allow_access = true;
					// add 2009/06/18 Y.Matsukawa ]
					}
				// add 2009/06/18 Y.Matsukawa [
				// 「未サポート端末でも閲覧可能」に設定されている場合は無条件でアクセス可
				// mod 2011/07/05 Y.Nakajima
				} else if (isset($D_OPEN_ACCESS) && $D_OPEN_ACCESS) {
					$this->G_AGENT_TYPE = D_PC;
					$allow_access = true;
				// add 2009/06/18 Y.Matsukawa ]
				}

				if(!$allow_access){
					// add 2016/07/05 N.Wada [
					// UAが不明端末の場合は、指定URLへリダイレクト
					if (isset($D_UA_UNKOWN_REDIRECT_URL) && $D_UA_UNKOWN_REDIRECT_URL) {
						header('Location: '.$D_UA_UNKOWN_REDIRECT_URL);
						exit;
					}
					// add 2016/07/05 N.Wada ]
					// エラー画面表示
					header("Content-Type: text/html;charset=Shift_JIS");
					echo mb_convert_encoding("申し訳ございませんが、<BR>ご利用の携帯ではご覧になれません。", "SJIS-win","eucJP-win");
					// del 2010/03/15 Y.Matsukawa [
					//					// ＰＣで見れないサーバー＝本番サーバーなので、未登録キャリアはメール送信する。
					//					$mail_body = "登録されていないUSER_AGENTからのアクセスがありました。\n";
					//					$mail_body.= "マスタに登録を行って下さい。\n";
					//					$mail_body.= "アクセス日時：".date("Y/m/d h:i:s")."\n\n";
					//					$mail_body.= "※自動配信メールです。このメールには返信しないで下さい。\n";
					//					$mail_body.= "--\n";
					//					$mail_body.= "アクセス元IP:".getenv("REMOTE_ADDR")."\n";
					//					$mail_body.= "USER_AGENT [".$P_USER_AGENT."]\n";
					//					$mail_body.= "HTTP_X_JPHONE_DISPLAY [".$HTTP_X_JPHONE_DISPLAY."]\n";
					//					$mail_body.= "HTTP_X_UP_SUBNO [".$HTTP_X_UP_SUBNO."]\n";
					//					$mail_body.= "HTTP_X_UP_DEVCAP_ISCOLOR [".$HTTP_X_UP_DEVCAP_ISCOLOR."]\n";
					//					$mail_body.= "HTTP_X_UP_DEVCAP_SCREENPIXELS [".$HTTP_X_UP_DEVCAP_SCREENPIXELS."]\n";
					//					$mail_body.= "HTTP_X_UP_DEVCAP_MULTIMEDIA [".$HTTP_X_UP_DEVCAP_MULTIMEDIA."]\n";
					//					$mail_body.= "--\n";
					//					$mail_body.= "SERVER:".trim(`hostname`)."\n";
					//					$mail_body.= "HOST:".$_SERVER["HTTP_HOST"]."\n";
					//					$mail_body.= "URI:".$_SERVER["REQUEST_URI"]."\n";
					//					// メール送信
					//					$this->another_mail(
					//						"172.16.45.232",
					//						"y_hayashida@zenrin-datacom.net", 
					//						"y_hayashida@zenrin-datacom.net;iwamoto@zenrin-datacom.net;minagawa@zenrin-datacom.net",
					//						"[未登録携帯情報] Mobile Mst Info", 
					//						"", 
					//						$mail_body
					//					);
					// del 2010/03/15 Y.Matsukawa [
					exit;
				}
			}
		}

		// add 2016/07/05 N.Wada [
		if (isset($D_UA_PC_REDIRECT_URL) && $D_UA_PC_REDIRECT_URL) {
			// たとえPCアクセスを許可していてもUAがPCの場合は、強制的に指定URLへリダイレクト
			if ($this->G_AGENT_TYPE == D_PC) {
				header('Location: '.$D_UA_PC_REDIRECT_URL);
				exit;
			}
		}
		// add 2016/07/05 N.Wada ]

		return $ret;
	}

	function another_mail($server, $from, $to, $subject, $headers, $message)
	{
		// mod 2011/07/05 Y.Nakajima
		//list($me,$mydomain) = split("@",$from);
		list($me,$mydomain) = explode("@",$from);

		// Open an SMTP connection
		$connection = fsockopen ($server, 25, &$errno, &$errstr, 1);
		if (!$connection){
			error_log("CONNECT ERROR:[$server]n",3,"/var/tmp/mobile.log");
		}

		while(true){
			$res=fgets($connection,256);
			if(substr($res,0,3) != "220"){
				error_log("SERVER STATUS ERROR:$res\n",3,"/var/tmp/mobile.log");
				break;
			}

			// Introduce ourselves
			fputs($connection, "HELO $mydomain\n");
			$res=fgets($connection,256);
			if(substr($res,0,3) != "250"){
				error_log("HELO ERROR:$res\n",3,"/var/tmp/mobile.log");
				break;
			}

			// Envelope from
			fputs($connection, "MAIL FROM: $from\n");
			$res=fgets($connection,256);
			if(substr($res,0,3) != "250"){
				error_log("MAIL FROM ERROR:$res\n",3,"/var/tmp/mobile.log");
				break;
			}

			if( strpos($to, ";") > -1 ){
				// mod 2011/07/05 Y.Nakajima
				//$to_list = split(";", $to);
				$to_list = explode(";", $to);
			} else {
				$to_list = Array();
				$to_list[] = $to;
			}

			for($i = 0 ; $i < count($to_list) ; $i++){
				// Envelope to
				fputs($connection, "RCPT TO: ".$to_list[$i]."\n");
				$res=fgets($connection,256);
				if(substr($res,0,3) != "250"){
					error_log("RCPT TO ERROR:$res\n",3,"/var/tmp/mobile.log");
					break;
				}
			}

			// The message
			fputs($connection, "DATA\n");
			$res=fgets($connection,256);
			if(substr($res,0,3) != "354"){
				error_log("DATA ERROR:$res\n",3,"/var/tmp/mobile.log");
				break;
			}

			$message = ereg_replace("(\r\n|\r|\n)","\r\n", $message);
			$to = str_replace(";", ",", $to);
			$subject= mb_convert_encoding($subject, "JIS", "eucJP-win");
			$message= mb_convert_encoding($message, "SJIS-win", "eucJP-win");
			$body = "To: $to\r\nFrom: $from\r\nSubject: $subject\r\n$message\r\n.\r\n";

			fputs($connection, $body);
			$res=fgets($connection,256);
			if(substr($res,0,3) != "250"){
				error_log("DATA PUT ERROR:$res\n",3,"/var/tmp/mobile.log");
				break;
			}

			// Say bye bye
			fputs($connection,"QUIT\n");
			$res=fgets($connection,256);
			if(substr($res,0,3) != "221"){
				error_log("QUIT ERROR:$res\n",3,"/var/tmp/mobile.log");
				break;
			}

			error_log("MAIL SEND OK : FROM[$from] TO[$to] SUBJECT[$subject]\n",3,"/var/tmp/mobile.log");
			break;
		}

		if($connection) {
			fclose ($connection);
		}
	}

	//---------------------------------------------------------------
	// 端末の画面サイズ情報設定（要initialize or コンストラクタにUSER_AGENT）
	//---------------------------------------------------------------
	function setDisplayInfo(){
		global $D_DEFAULT_W;
		global $D_DEFAULT_H;
		global $SETTING;
		// ＰＣの場合の画面サイズ（ＱＶＧＡにしとく）
		if($this->G_AGENT_TYPE == D_PC){
			$this->G_DISPLAY_W = 240;
			$this->G_DISPLAY_H = 320;
			$this->G_DISPLAY_COL = true;
			// add 2016/03/20 Winas Inc.
			if(isset($SETTING["jcomtvflg"]) == '1'){
				$this->G_DISPLAY_W = 365;
				$this->G_DISPLAY_H = 280;
			}
		} else {
			$this->G_DISPLAY_COL = true;

			$ez_screen      = $_SERVER['HTTP_X_UP_DEVCAP_SCREENPIXELS'];
			$jphone_display = $_SERVER['HTTP_X_JPHONE_DISPLAY'];

			if($ez_screen != ""){
				// mod 2011/07/05 Y.Nakajima
				//if (ereg('([0-9]+),([0-9]+)', $ez_screen, $r)) {
				if (preg_match('/([0-9]+),([0-9]+)/', $ez_screen, $r) !== false) {
					$this->G_DISPLAY_W = $r[1];
					$this->G_DISPLAY_H = $r[2];
					$this->G_DISPLAY_W-=5;
				}
			} else if($jphone_display != ""){
				// mod 2011/07/05 Y.Nakajima
				//if (ereg('([0-9]+)\*([0-9]+)', $jphone_display, $r)) {
				if (preg_match('/([0-9]+)\*([0-9]+)/', $jphone_display, $r) !== false) {
					$this->G_DISPLAY_W = $r[1];
					$this->G_DISPLAY_H = $r[2];
				}
				// 3G
				// mod 2011/07/05 Y.Nakajima
				//if(ereg("(Vodafone|^MOT-|SoftBank)", $this->G_USER_AGENT)){
				if(preg_match("/(Vodafone|^MOT-|SoftBank)/", $this->G_USER_AGENT, $r) !== false){
					$this->G_DISPLAY_W -= 10;
					$this->G_DISPLAY_H -= 50;
				// パケット機 (5.X 以外)
				// mod 2011/07/05 Y.Nakajima
				//} else if(ereg("4\.", $this->G_USER_AGENT)){
				} else if(strpos($this->G_USER_AGENT, "4\.")){
					if(( $this->G_DISPLAY_W + $this->G_DISPLAY_H) > 400){
						$this->G_DISPLAY_W = 160;
						$this->G_DISPLAY_H = 180;
					}
				//  パケット機以外
				// mod 2011/07/05 Y.Nakajima
				//} else if(!ereg("5\.", $this->G_USER_AGENT)){
				} else if(!strpos($this->G_USER_AGENT, "5\.")){
					if(( $this->G_DISPLAY_W + $this->G_DISPLAY_H) > 230){
						// 画面がでかいやつは固定サイズで
						$this->G_DISPLAY_W = 60;
						$this->G_DISPLAY_H = 60;
					} else {
						// 230 より小さいものはたいがい出るのでちょと小さくして出す
						$this->G_DISPLAY_W -= 25;
						$this->G_DISPLAY_H -= 35;
					}
				}
			} else {
				$this->G_DISPLAY_W = $D_DEFAULT_W;
				$this->G_DISPLAY_H = $D_DEFAULT_H;
			}
			if($this->G_DISPLAY_W <= 0 || $this->G_DISPLAY_H <= 0){
				$this->G_DISPLAY_W = $D_DEFAULT_W;
				$this->G_DISPLAY_H = $D_DEFAULT_H;
			}
		}
	}

	//---------------------------------------------------------------
	// 位置情報取得用のＵＲＬを返却（Ａタグ用）
	//---------------------------------------------------------------
	function MakeLocationSearchUrl($param){
		switch($this->G_AGENT_TYPE){
		case D_PC:
			return "#";
			break;
		case D_WILL:
			return "http://location.request/dummy.cgi?my=".str_replace("?", "&", $param)."&pos=\$location";
			break;
		case D_DOCOMO:
			// F661iは、リンクでのGPSからの位置情報を取得できないので、
			// i-areaに強制的に変換する。
			// mod 2011/07/05 Y.Nakajima
			//if($this->isGPS() && !ereg(D_GPS_LINK_NS, $this->G_USER_AGENT)){
			if($this->isGPS() && !strpos($this->G_USER_AGENT, D_GPS_LINK_NS)){
				// GPSの場合は、ＵＲＬはそのままでタグに埋め込みキーワードを指定するのでメイン側で
				return $param;
			} else {
				//return "http://w1m.docomo.ne.jp/cp/iarea?ecode=OPENAREACODE&msn=OPENAREAKEY&nl=".$param;		mod 2009/06/29 Y.Matsukawa
				return "http://w1m.docomo.ne.jp/cp/iarea?ecode=OPENAREACODE&msn=OPENAREAKEY&nl=".urlencode($param);
			}
			break;
		case D_SOFTBANK:
			// mod 2011/07/05 Y.Nakajima
			//if(ereg("(J-PHONE)",$this->G_USER_AGENT)){
			if(strpos($this->G_USER_AGENT, "(J-PHONE)")){
				return $param;
			} else {
				// なんだか?で区切りを入れるとエラーになるので、&で対応
				return "location:auto?url=".str_replace("?", "&", $param);
			}
			break;
		case D_KDDI:
			//return "device:location?url=".$param;
			//return "device:location?url=".str_replace("?", "/", $param)."/";		del 2009/05/11 Y.Matsukawa
			// add 2009/05/11 Y.Matsukawa [
			if($this->isGPS()) {
				//return "device:gpsone?url=".str_replace("?", "/", $param)."/"."&ver=1&datum=0&unit=0";	mod 2009/07/02 Y.Matsukawa
				//return "device:gpsone?url=".ereg_replace("(\?|&)", "/", $param)."/"."&ver=1&datum=0&unit=0";	// mod 2011/07/05 Y.Nakajima 
				return "device:gpsone?url=".preg_replace("/(\?|&)/", "/", $param)."/"."&ver=1&datum=0&unit=0";
			} else {
				//return "device:location?url=".str_replace("?", "/", $param)."/";		mod 2009/07/02 Y.Matsukawa
				//return "device:location?url=".ereg_replace("(\?|&)", "/", $param)."/";	// mod 2011/07/05 Y.Nakajima 
				return "device:location?url=".preg_replace("/(\?|&)/", "/", $param)."/";
			}
			// add 2009/05/11 Y.Matsukawa ]
			break;
		// add 2010/08/12 Y.Matsukawa [
		case D_IPHONE:
			return "javascript:navigator.geolocation.watchPosition(locupdate, handleError);";
			break;
		// add 2010/08/12 Y.Matsukawa ]
		// add 2010/10/20 Y.Matsukawa [
		case D_ANDROID_1:
			return "javascript:geo.getCurrentPosition(updatePosition, handleError);";
			break;
		case D_ANDROID_2:
			return "javascript:navigator.geolocation.watchPosition(locupdate, handleError);";
			break;
		// add 2010/10/20 Y.Matsukawa ]
		}
	}

	//---------------------------------------------------------------
	// 位置情報取得用のＵＲＬを返却（Ａタグ用）
	//---------------------------------------------------------------
	function MakeLocationSearchForm($param){
		$ret = array();

		// こちらからパラメータを送信しても返却してくれないキャリアは、
		// FORMのポスト先をs.htmにて、パラメータとして、p=ibsとパラメータ(COL_11=1など）を送る。
		// そうすると、間に自動的にリンクフォームが入る遷移になる。

		switch($this->G_AGENT_TYPE){
		case D_PC:
			return $ret;
			break;
		case D_WILL:
			$ret["FORM_ACTION"] = "s.htm";
			$ret["FORM_PARAM"][0]["name"] = "p";
			$ret["FORM_PARAM"][0]["val"] = "ibs";
			break;
		case D_DOCOMO:
			if($this->isGPS()){
				// GPSの場合は、ＵＲＬはそのままでタグに埋め込みキーワードを指定するのでメイン側で
				$ret["FORM_ACTION"] = "$param";
				return $ret;
			} else {
				$ret["FORM_ACTION"] = "http://w1m.docomo.ne.jp/cp/iarea";
				$ret["FORM_PARAM"][0]["name"] = "ecode";
				$ret["FORM_PARAM"][0]["val"] = "OPENAREACODE";
				$ret["FORM_PARAM"][1]["name"] = "msn";
				$ret["FORM_PARAM"][1]["val"] = "OPENAREAKEY";
				$ret["FORM_PARAM"][2]["name"] = "nl";
				$ret["FORM_PARAM"][2]["val"] = "$param";
			}
			break;
		case D_SOFTBANK:
			$ret["FORM_ACTION"] = "s.htm";
			$ret["FORM_PARAM"][0]["name"] = "p";
			$ret["FORM_PARAM"][0]["val"] = "ibs";
			break;
		case D_KDDI:
			$ret["FORM_ACTION"] = "s.htm";
			$ret["FORM_PARAM"][0]["name"] = "p";
			$ret["FORM_PARAM"][0]["val"] = "ibs";
			break;
		// add 2010/08/12 Y.Matsukawa [
		case D_IPHONE:
			$ret["FORM_ACTION"] = "s.htm";
			$ret["FORM_PARAM"][0]["name"] = "p";
			$ret["FORM_PARAM"][0]["val"] = "ibs";
			break;
		// add 2010/08/12 Y.Matsukawa ]
		// add 2010/10/20 Y.Matsukawa [
		case D_ANDROID_1:
		case D_ANDROID_2:
			$ret["FORM_ACTION"] = "s.htm";
			$ret["FORM_PARAM"][0]["name"] = "p";
			$ret["FORM_PARAM"][0]["val"] = "ibs";
			break;
		// add 2010/10/20 Y.Matsukawa ]
		}
		return $ret;
	}

	//---------------------------------------------------------------
	// キャリア毎の絵文字定義の設定
	//---------------------------------------------------------------
	function setEmojiArray($P_AGENT){
		global $SETTING;
		global $D_OPEN_ACCESS;		// add 2009/06/18 Y.Matsukawa
		switch($P_AGENT){
		case D_WILL:
		case D_DOCOMO:
			// del 2009/05/18 Y.Matsukawa [
			//			$this->G_EMOJI["#HINT#"]     = "&#63904;";
			//			$this->G_EMOJI["#DOWN#"]     = "&#63909;";
			//			$this->G_EMOJI["#EXC#"]      = "&#63911;";
			//			$this->G_EMOJI["#QUESTION#"] = "&#63912;";
			//			$this->G_EMOJI["#ANTENNA#"]  = "&#63875;";
			//			$this->G_EMOJI["#OK#"]       = "&#63920;";
			//			$this->G_EMOJI["#HEART#"]    = "&#63889;";
			//			$this->G_EMOJI["#SHOES#"]    = "&#63738;";
			//			$this->G_EMOJI["#MAIL#"]     = "&#63863;";
			//			$this->G_EMOJI["#YEN#"]      = "&#63866;";
			//			$this->G_EMOJI["#RETURN#"]   = "&#63870;";
			//			$this->G_EMOJI["#SEARCH#"]   = "&#63873;";
			//			$this->G_EMOJI["#NEW#"]      = "&#63874;";
			//			$this->G_EMOJI["#TEL#"]      = "&#63720;";
			//			$this->G_EMOJI["#TRAIN#"]    = "&#63676;";
			//			$this->G_EMOJI["#CAR#"]      = "&#63679;";
			//			$this->G_EMOJI["#BUS#"]      = "&#63681;";
			//			$this->G_EMOJI["#HOME#"]     = "&#63684;";
			//			$this->G_EMOJI["#BUILD#"]    = "&#63685;";
			//			$this->G_EMOJI["#POST#"]     = "&#63686;";
			//			$this->G_EMOJI["#HOSPITAL#"] = "&#63687;";
			//			$this->G_EMOJI["#BANK#"]     = "&#63688;";
			//			$this->G_EMOJI["#ATM#"]      = "&#63689;";
			//			$this->G_EMOJI["#HOTEL#"]    = "&#63690;";
			//			$this->G_EMOJI["#CVS#"]      = "&#63691;";
			//			$this->G_EMOJI["#GS#"]       = "&#63692;";
			//			$this->G_EMOJI["#PARK#"]     = "&#63693;";
			//			$this->G_EMOJI["#BEER#"]     = "&#63699;";
			//			$this->G_EMOJI["#BURGER#"]   = "&#63700;";
			//			$this->G_EMOJI["#SOCCER#"]   = "&#63671;";
			//			$this->G_EMOJI["#GOLF#"]     = "&#63669;";
			//			$this->G_EMOJI["#MOVIE#"]    = "&#63704;";
			//			$this->G_EMOJI["#NIGHT#"]    = "&#63831;";
			//			$this->G_EMOJI["#FREE#"]     = "&#63876;";
			//			$this->G_EMOJI["#TIME#"]     = "&#63838;";
			//			$this->G_EMOJI["#NO1#"]      = "&#63879;";
			//			$this->G_EMOJI["#NO2#"]      = "&#63880;";
			//			$this->G_EMOJI["#NO3#"]      = "&#63881;";
			//			$this->G_EMOJI["#NO4#"]      = "&#63882;";
			//			$this->G_EMOJI["#NO5#"]      = "&#63883;";
			//			$this->G_EMOJI["#NO6#"]      = "&#63884;";
			//			$this->G_EMOJI["#NO7#"]      = "&#63885;";
			//			$this->G_EMOJI["#NO8#"]      = "&#63886;";
			//			$this->G_EMOJI["#NO9#"]      = "&#63887;";
			//			$this->G_EMOJI["#NO0#"]      = "&#63888;";
			// del 2009/05/18 Y.Matsukawa ]
			// add 2009/05/18 Y.Matsukawa [
			$this->G_EMOJI["#SUN#"]             = "&#xE63E;";
			$this->G_EMOJI["#CLOUD#"]           = "&#xE63F;";
			$this->G_EMOJI["#RAIN#"]            = "&#xE640;";
			$this->G_EMOJI["#SNOW#"]            = "&#xE641;";
			$this->G_EMOJI["#THUNDER#"]         = "&#xE642;";
			$this->G_EMOJI["#TYPHOON#"]         = "&#xE643;";
			$this->G_EMOJI["#FOG#"]             = "&#xE644;";
			$this->G_EMOJI["#LIGHT_RAIN#"]      = "&#xE645;";
			$this->G_EMOJI["#RAM#"]             = "&#xE646;";
			$this->G_EMOJI["#BULL#"]            = "&#xE647;";
			$this->G_EMOJI["#TWINS#"]           = "&#xE648;";
			$this->G_EMOJI["#CRAB#"]            = "&#xE649;";
			$this->G_EMOJI["#LION#"]            = "&#xE64A;";
			$this->G_EMOJI["#VIRGIN#"]          = "&#xE64B;";
			$this->G_EMOJI["#BALANCE#"]         = "&#xE64C;";
			$this->G_EMOJI["#SCORPION#"]        = "&#xE64D;";
			$this->G_EMOJI["#ARCHER#"]          = "&#xE64E;";
			$this->G_EMOJI["#GOAT#"]            = "&#xE64F;";
			$this->G_EMOJI["#WATER_BEARER#"]    = "&#xE650;";
			$this->G_EMOJI["#FISHES#"]          = "&#xE651;";
			$this->G_EMOJI["#SPORTS#"]          = "&#xE652;";
			$this->G_EMOJI["#BASEBALL#"]        = "&#xE653;";
			$this->G_EMOJI["#GOLF#"]            = "&#xE654;";
			$this->G_EMOJI["#TENNIS#"]          = "&#xE655;";
			$this->G_EMOJI["#SOCCER#"]          = "&#xE656;";
			$this->G_EMOJI["#SKI#"]             = "&#xE657;";
			$this->G_EMOJI["#BASKETBALL#"]      = "&#xE658;";
			$this->G_EMOJI["#FLAG#"]            = "&#xE659;";
			$this->G_EMOJI["#POCKET_BELL#"]     = "&#xE65A;";
			$this->G_EMOJI["#TRAIN#"]           = "&#xE65B;";
			$this->G_EMOJI["#SUBWAY#"]          = "&#xE65C;";
			$this->G_EMOJI["#SHINKANSEN#"]      = "&#xE65D;";
			$this->G_EMOJI["#CAR#"]             = "&#xE65E;";
			$this->G_EMOJI["#CAR_2#"]           = "&#xE65F;";
			$this->G_EMOJI["#BUS#"]             = "&#xE660;";
			$this->G_EMOJI["#SHIP#"]            = "&#xE661;";
			$this->G_EMOJI["#AIRPLANE#"]        = "&#xE662;";
			$this->G_EMOJI["#HOME#"]            = "&#xE663;";
			$this->G_EMOJI["#BUILD#"]           = "&#xE664;";
			$this->G_EMOJI["#POST#"]            = "&#xE665;";
			$this->G_EMOJI["#HOSPITAL#"]        = "&#xE666;";
			$this->G_EMOJI["#BANK#"]            = "&#xE667;";
			$this->G_EMOJI["#ATM#"]             = "&#xE668;";
			$this->G_EMOJI["#HOTEL#"]           = "&#xE669;";
			$this->G_EMOJI["#CVS#"]             = "&#xE66A;";
			$this->G_EMOJI["#GS#"]              = "&#xE66B;";
			$this->G_EMOJI["#PARK#"]            = "&#xE66C;";
			$this->G_EMOJI["#SIGNAL#"]          = "&#xE66D;";
			$this->G_EMOJI["#TOILET#"]          = "&#xE66E;";
			$this->G_EMOJI["#RESTAURANT#"]      = "&#xE66F;";
			$this->G_EMOJI["#CAFE#"]            = "&#xE670;";
			$this->G_EMOJI["#BAR#"]             = "&#xE671;";
			$this->G_EMOJI["#BEER#"]            = "&#xE672;";
			$this->G_EMOJI["#BURGER#"]          = "&#xE673;";
			$this->G_EMOJI["#BOUTIQUE#"]        = "&#xE674;";
			$this->G_EMOJI["#BEAUTY_SALON#"]    = "&#xE675;";
			$this->G_EMOJI["#KARAOKE#"]         = "&#xE676;";
			$this->G_EMOJI["#MOVIE#"]           = "&#xE677;";
			$this->G_EMOJI["#RIGHT_UP#"]        = "&#xE678;";
			$this->G_EMOJI["#AMUSEMENT_PARK#"]  = "&#xE679;";
			$this->G_EMOJI["#MUSIC#"]           = "&#xE67A;";
			$this->G_EMOJI["#ART#"]             = "&#xE67B;";
			$this->G_EMOJI["#DRAMA#"]           = "&#xE67C;";
			$this->G_EMOJI["#EVENT#"]           = "&#xE67D;";
			$this->G_EMOJI["#TICKET#"]          = "&#xE67E;";
			$this->G_EMOJI["#SMOKING#"]         = "&#xE67F;";
			$this->G_EMOJI["#NO_SMOKING#"]      = "&#xE680;";
			$this->G_EMOJI["#CAMERA#"]          = "&#xE681;";
			$this->G_EMOJI["#BAG#"]             = "&#xE682;";
			$this->G_EMOJI["#BOOK#"]            = "&#xE683;";
			$this->G_EMOJI["#RIBBON#"]          = "&#xE684;";
			$this->G_EMOJI["#PRESENT#"]         = "&#xE685;";
			$this->G_EMOJI["#BIRTHDAY#"]        = "&#xE686;";
			$this->G_EMOJI["#TEL#"]             = "&#xE687;";
			$this->G_EMOJI["#MOBILE#"]          = "&#xE688;";
			$this->G_EMOJI["#MEMO#"]            = "&#xE689;";
			$this->G_EMOJI["#TV#"]              = "&#xE68A;";
			$this->G_EMOJI["#GAME#"]            = "&#xE68B;";
			$this->G_EMOJI["#CD#"]              = "&#xE68C;";
			$this->G_EMOJI["#HEART_TRUMP#"]     = "&#xE68D;";
			$this->G_EMOJI["#SPADE#"]           = "&#xE68E;";
			$this->G_EMOJI["#DIAMOND#"]         = "&#xE68F;";
			$this->G_EMOJI["#CLUBS#"]           = "&#xE690;";
			$this->G_EMOJI["#EYE#"]             = "&#xE691;";
			$this->G_EMOJI["#EAR#"]             = "&#xE692;";
			$this->G_EMOJI["#GOO#"]             = "&#xE693;";
			$this->G_EMOJI["#CHOKI#"]           = "&#xE694;";
			$this->G_EMOJI["#PAR#"]             = "&#xE695;";
			$this->G_EMOJI["#RIGHT_DOWN#"]      = "&#xE696;";
			$this->G_EMOJI["#LEFT_UP#"]         = "&#xE697;";
			$this->G_EMOJI["#FOOT#"]            = "&#xE698;";
			$this->G_EMOJI["#SHOES#"]           = "&#xE699;";
			$this->G_EMOJI["#GLASSES#"]         = "&#xE69A;";
			$this->G_EMOJI["#WHEELCHAIR#"]      = "&#xE69B;";
			$this->G_EMOJI["#NEW_MOON#"]        = "&#xE69C;";
			$this->G_EMOJI["#CHIP_MOON#"]       = "&#xE69D;";
			$this->G_EMOJI["#HALF_MOON#"]       = "&#xE69E;";
			$this->G_EMOJI["#CRESCENT_MOON#"]   = "&#xE69F;";
			$this->G_EMOJI["#FULL_MOON#"]       = "&#xE6A0;";
			$this->G_EMOJI["#DOG#"]             = "&#xE6A1;";
			$this->G_EMOJI["#CAT#"]             = "&#xE6A2;";
			$this->G_EMOJI["#RESORT#"]          = "&#xE6A3;";
			$this->G_EMOJI["#XMAS#"]            = "&#xE6A4;";
			$this->G_EMOJI["#LEFT_DOWN#"]       = "&#xE6A5;";
			$this->G_EMOJI["#PHONE_TO#"]        = "&#xE6CE;";
			$this->G_EMOJI["#MAIL_TO#"]         = "&#xE6CF;";
			$this->G_EMOJI["#FAX_TO#"]          = "&#xE6D0;";
			$this->G_EMOJI["#CARRIER#"]         = "&#xE6D1;";
			$this->G_EMOJI["#CARRIER_2#"]       = "&#xE6D2;";
			$this->G_EMOJI["#MAIL#"]            = "&#xE6D3;";
			$this->G_EMOJI["#OFFER#"]           = "&#xE6D4;";
			$this->G_EMOJI["#POINT#"]           = "&#xE6D5;";
			$this->G_EMOJI["#YEN#"]             = "&#xE6D6;";
			$this->G_EMOJI["#FREE_YEN#"]        = "&#xE6D7;";
			$this->G_EMOJI["#ID#"]              = "&#xE6D8;";
			$this->G_EMOJI["#PASSWORD#"]        = "&#xE6D9;";
			$this->G_EMOJI["#RETURN#"]          = "&#xE6DA;";
			$this->G_EMOJI["#CLEAR#"]           = "&#xE6DB;";
			$this->G_EMOJI["#SEARCH#"]          = "&#xE6DC;";
			$this->G_EMOJI["#NEW#"]             = "&#xE6DD;";
			$this->G_EMOJI["#ANTENNA#"]         = "&#xE6DE;";
			$this->G_EMOJI["#FREE#"]            = "&#xE6DF;";
			$this->G_EMOJI["#SHARP_DIAL#"]      = "&#xE6E0;";
			$this->G_EMOJI["#MOB_Q#"]           = "&#xE6E1;";
			$this->G_EMOJI["#NO1#"]             = "&#xE6E2;";
			$this->G_EMOJI["#NO2#"]             = "&#xE6E3;";
			$this->G_EMOJI["#NO3#"]             = "&#xE6E4;";
			$this->G_EMOJI["#NO4#"]             = "&#xE6E5;";
			$this->G_EMOJI["#NO5#"]             = "&#xE6E6;";
			$this->G_EMOJI["#NO6#"]             = "&#xE6E7;";
			$this->G_EMOJI["#NO7#"]             = "&#xE6E8;";
			$this->G_EMOJI["#NO8#"]             = "&#xE6E9;";
			$this->G_EMOJI["#NO9#"]             = "&#xE6EA;";
			$this->G_EMOJI["#NO0#"]             = "&#xE6EB;";
			$this->G_EMOJI["#OK#"]              = "&#xE70B;";
			$this->G_EMOJI["#HEART#"]           = "&#xE6EC;";
			$this->G_EMOJI["#HEART_WAVE#"]      = "&#xE6ED;";
			$this->G_EMOJI["#HEART_BREAK#"]     = "&#xE6EE;";
			$this->G_EMOJI["#HEARTS#"]          = "&#xE6EF;";
			$this->G_EMOJI["#FACE_SMILE#"]      = "&#xE6F0;";
			$this->G_EMOJI["#FACE_ANGRY#"]      = "&#xE6F1;";
			$this->G_EMOJI["#FACE_DEJECT#"]     = "&#xE6F2;";
			$this->G_EMOJI["#FACE_SAD#"]        = "&#xE6F3;";
			$this->G_EMOJI["#FACE_SWING#"]      = "&#xE6F4;";
			$this->G_EMOJI["#GOOD#"]            = "&#xE6F5;";
			$this->G_EMOJI["#CHEERFUL#"]        = "&#xE6F6;";
			$this->G_EMOJI["#FEEL_GOOD#"]       = "&#xE6F7;";
			$this->G_EMOJI["#CUTE#"]            = "&#xE6F8;";
			$this->G_EMOJI["#KISS#"]            = "&#xE6F9;";
			$this->G_EMOJI["#SHINE#"]           = "&#xE6FA;";
			$this->G_EMOJI["#HINT#"]            = "&#xE6FB;";
			$this->G_EMOJI["#ANGER#"]           = "&#xE6FC;";
			$this->G_EMOJI["#PUNCH#"]           = "&#xE6FD;";
			$this->G_EMOJI["#BOMB#"]            = "&#xE6FE;";
			$this->G_EMOJI["#MOOD#"]            = "&#xE6FF;";
			$this->G_EMOJI["#DOWN#"]            = "&#xE700;";
			$this->G_EMOJI["#SLEEP#"]           = "&#xE701;";
			$this->G_EMOJI["#EXC#"]             = "&#xE702;";
			$this->G_EMOJI["#QUESTION#"]        = "&#xE703;";
			$this->G_EMOJI["#EXC_2#"]           = "&#xE704;";
			$this->G_EMOJI["#SHOCK#"]           = "&#xE705;";
			$this->G_EMOJI["#SWEAT#"]           = "&#xE706;";
			$this->G_EMOJI["#SWEAT_2#"]         = "&#xE707;";
			$this->G_EMOJI["#DASH#"]            = "&#xE708;";
			$this->G_EMOJI["#LONG_VOWEL#"]      = "&#xE709;";
			$this->G_EMOJI["#LONG_VOWEL_2#"]    = "&#xE70A;";
			$this->G_EMOJI["#KACHINKO#"]        = "&#xE6AC;";
			$this->G_EMOJI["#POUCH#"]           = "&#xE6AD;";
			$this->G_EMOJI["#PEN#"]             = "&#xE6AE;";
			$this->G_EMOJI["#SHADOW#"]          = "&#xE6B1;";
			$this->G_EMOJI["#CHAIR#"]           = "&#xE6B2;";
			$this->G_EMOJI["#NIGHT#"]           = "&#xE6B3;";
			$this->G_EMOJI["#SOON#"]            = "&#xE6B7;";
			$this->G_EMOJI["#ON#"]              = "&#xE6B8;";
			$this->G_EMOJI["#END#"]             = "&#xE6B9;";
			$this->G_EMOJI["#TIME#"]            = "&#xE6BA;";
			$this->G_EMOJI["#APPLI#"]           = "&#xE70C;";
			$this->G_EMOJI["#APPLI_2#"]         = "&#xE70D;";
			$this->G_EMOJI["#SHIRTS#"]          = "&#xE70E;";
			$this->G_EMOJI["#WALLET#"]          = "&#xE70F;";
			$this->G_EMOJI["#MAKEUP#"]          = "&#xE710;";
			$this->G_EMOJI["#JEANS#"]           = "&#xE711;";
			$this->G_EMOJI["#SNOW_BOARD#"]      = "&#xE712;";
			$this->G_EMOJI["#CHAPEL#"]          = "&#xE713;";
			$this->G_EMOJI["#DOOR#"]            = "&#xE714;";
			$this->G_EMOJI["#DOLLAR#"]          = "&#xE715;";
			$this->G_EMOJI["#PC#"]              = "&#xE716;";
			$this->G_EMOJI["#LOVE_LETTER#"]     = "&#xE717;";
			$this->G_EMOJI["#WRENCH#"]          = "&#xE718;";
			$this->G_EMOJI["#PENCIL#"]          = "&#xE719;";
			$this->G_EMOJI["#CROWN#"]           = "&#xE71A;";
			$this->G_EMOJI["#RING#"]            = "&#xE71B;";
			$this->G_EMOJI["#SANDGLASS#"]       = "&#xE71C;";
			$this->G_EMOJI["#BICYCLE#"]         = "&#xE71D;";
			$this->G_EMOJI["#TEACUP#"]          = "&#xE71E;";
			$this->G_EMOJI["#WATCH#"]           = "&#xE71F;";
			$this->G_EMOJI["#FACE_THINK#"]      = "&#xE720;";
			$this->G_EMOJI["#FACE_PEACE#"]      = "&#xE721;";
			$this->G_EMOJI["#FACE_HURRY#"]      = "&#xE722;";
			$this->G_EMOJI["#FACE_HURRY_2#"]    = "&#xE723;";
			$this->G_EMOJI["#FACE_ANGRY_2#"]    = "&#xE724;";
			$this->G_EMOJI["#FACE_POKER#"]      = "&#xE725;";
			$this->G_EMOJI["#FACE_HEART#"]      = "&#xE726;";
			$this->G_EMOJI["#FINGER#"]          = "&#xE727;";
			$this->G_EMOJI["#FACE_JOKE#"]       = "&#xE728;";
			$this->G_EMOJI["#FACE_WINK#"]       = "&#xE729;";
			$this->G_EMOJI["#FACE_HAPPY#"]      = "&#xE72A;";
			$this->G_EMOJI["#FACE_PATIENCE#"]   = "&#xE72B;";
			$this->G_EMOJI["#CAT_2#"]           = "&#xE72C;";
			$this->G_EMOJI["#FACE_CRY#"]        = "&#xE72D;";
			$this->G_EMOJI["#TEAR#"]            = "&#xE72E;";
			$this->G_EMOJI["#NG#"]              = "&#xE72F;";
			$this->G_EMOJI["#CLIP#"]            = "&#xE730;";
			$this->G_EMOJI["#COPYRIGHT#"]       = "&#xE731;";
			$this->G_EMOJI["#TM#"]              = "&#xE732;";
			$this->G_EMOJI["#RUNNER#"]          = "&#xE733;";
			$this->G_EMOJI["#SECRET#"]          = "&#xE734;";
			$this->G_EMOJI["#RECYCLING#"]       = "&#xE735;";
			$this->G_EMOJI["#REGIST#"]          = "&#xE736;";
			$this->G_EMOJI["#WARNING#"]         = "&#xE737;";
			$this->G_EMOJI["#PROHIBITION#"]     = "&#xE738;";
			$this->G_EMOJI["#EMPTY#"]           = "&#xE739;";
			$this->G_EMOJI["#SUCCESS#"]         = "&#xE73A;";
			$this->G_EMOJI["#FULL#"]            = "&#xE73B;";
			$this->G_EMOJI["#RIGHT_LEFT#"]      = "&#xE73C;";
			$this->G_EMOJI["#UP_DOWN#"]         = "&#xE73D;";
			$this->G_EMOJI["#SCHOOL#"]          = "&#xE73E;";
			$this->G_EMOJI["#WAVE#"]            = "&#xE73F;";
			$this->G_EMOJI["#MOUNTAIN#"]        = "&#xE740;";
			$this->G_EMOJI["#CLOVER#"]          = "&#xE741;";
			$this->G_EMOJI["#CHERRY#"]          = "&#xE742;";
			$this->G_EMOJI["#TULIP#"]           = "&#xE743;";
			$this->G_EMOJI["#BANANA#"]          = "&#xE744;";
			$this->G_EMOJI["#APPLE#"]           = "&#xE745;";
			$this->G_EMOJI["#LEAF#"]            = "&#xE746;";
			$this->G_EMOJI["#MAPLE#"]           = "&#xE747;";
			$this->G_EMOJI["#CHERRY_BLOSSOM#"]  = "&#xE748;";
			$this->G_EMOJI["#RICE_BALL#"]       = "&#xE749;";
			$this->G_EMOJI["#CAKE#"]            = "&#xE74A;";
			$this->G_EMOJI["#SAKE#"]            = "&#xE74B;";
			$this->G_EMOJI["#BOWL#"]            = "&#xE74C;";
			$this->G_EMOJI["#PAN#"]             = "&#xE74D;";
			$this->G_EMOJI["#SNAIL#"]           = "&#xE74E;";
			$this->G_EMOJI["#BABY_BIRD#"]       = "&#xE74F;";
			$this->G_EMOJI["#PENGUIN#"]         = "&#xE750;";
			$this->G_EMOJI["#FISH#"]            = "&#xE751;";
			$this->G_EMOJI["#FACE_DELICIOUS#"]  = "&#xE752;";
			$this->G_EMOJI["#FACE_FOPPISH#"]    = "&#xE753;";
			$this->G_EMOJI["#HORSE#"]           = "&#xE754;";
			$this->G_EMOJI["#PIG#"]             = "&#xE755;";
			$this->G_EMOJI["#WINE#"]            = "&#xE756;";
			$this->G_EMOJI["#FACE_LET_DOWN#"]   = "&#xE757;";
			// add 2009/05/18 Y.Matsukawa ]
			$this->G_SUPPORT_IMAGE_EXT   = "GIF";
			$this->G_SUPPORT_CMDN_TYP    = 0;
			break;
		case D_SOFTBANK:
			// del 2010/07/20 Y.Matsukawa [
			//			$this->G_EMOJI["#HINT#"]     = pack("H10","1B24452F0F");
			//			$this->G_EMOJI["#DOWN#"]     = pack("H10","1B2446580F");
			//			$this->G_EMOJI["#EXC#"]      = pack("H10","1B2447410F");
			//			$this->G_EMOJI["#QUESTION#"] = pack("H10","1B2447400F");
			//			$this->G_EMOJI["#ANTENNA#"]  = pack("H10","1B24456B0F");
			//			$this->G_EMOJI["#OK#"]       = pack("H10","1B24466D0F");
			//			$this->G_EMOJI["#HEART#"]    = pack("H10","1B2447420F");
			//			$this->G_EMOJI["#SHOES#"]    = pack("H10","1B2447270F");
			//			$this->G_EMOJI["#MAIL#"]     = pack("H10","1B2445210F");
			//			$this->G_EMOJI["#YEN#"]      = pack("H10","1B24454F0F");
			//			$this->G_EMOJI["#RETURN#"]   = pack("H10","1B2446550F");
			//			$this->G_EMOJI["#SEARCH#"]   = pack("H10","1B2445340F");
			//			$this->G_EMOJI["#NEW#"]      = pack("H10","1B2446320F");
			//			$this->G_EMOJI["#TEL#"]      = pack("H10","1B2447290F");
			//			$this->G_EMOJI["#TRAIN#"]    = pack("H10","1B24473E0F");
			//			$this->G_EMOJI["#CAR#"]      = pack("H10","1B24457A0F");
			//			$this->G_EMOJI["#BUS#"]      = pack("H10","1B2445790F");
			//			$this->G_EMOJI["#HOME#"]     = pack("H10","1B2447560F");
			//			$this->G_EMOJI["#BUILD#"]    = pack("H10","1B2447580F");
			//			$this->G_EMOJI["#POST#"]     = pack("H10","1B2445730F");
			//			$this->G_EMOJI["#HOSPITAL#"] = pack("H10","1B2445750F");
			//			$this->G_EMOJI["#BANK#"]     = pack("H10","1B24456D0F");
			//			$this->G_EMOJI["#ATM#"]      = pack("H10","1B2445740F");
			//			$this->G_EMOJI["#HOTEL#"]    = pack("H10","1B2445780F");
			//			$this->G_EMOJI["#CVS#"]      = pack("H10","1B2445760F");
			//			$this->G_EMOJI["#GS#"]       = pack("H10","1B24475A0F");
			//			$this->G_EMOJI["#PARK#"]     = pack("H10","1B24456F0F");
			//			$this->G_EMOJI["#BEER#"]     = pack("H10","1B2447670F");
			//			$this->G_EMOJI["#BURGER#"]   = pack("H10","1B2445400F");
			//			$this->G_EMOJI["#SOCCER#"]   = pack("H10","1B2447380F");
			//			$this->G_EMOJI["#GOLF#"]     = pack("H10","1B2447340F");
			//			$this->G_EMOJI["#MOVIE#"]    = pack("H10","1B24475D0F");
			//			$this->G_EMOJI["#NIGHT#"]    = pack("H10","1B24476C0F");
			//			$this->G_EMOJI["#FREE#"]     = pack("H10","1B2446310F");
			//			$this->G_EMOJI["#TIME#"]     = pack("H10","1B2447450F");
			//			$this->G_EMOJI["#NO1#"]      = pack("H10","1B24463C0F");
			//			$this->G_EMOJI["#NO2#"]      = pack("H10","1B24463D0F");
			//			$this->G_EMOJI["#NO3#"]      = pack("H10","1B24463E0F");
			//			$this->G_EMOJI["#NO4#"]      = pack("H10","1B24463F0F");
			//			$this->G_EMOJI["#NO5#"]      = pack("H10","1B2446400F");
			//			$this->G_EMOJI["#NO6#"]      = pack("H10","1B2446410F");
			//			$this->G_EMOJI["#NO7#"]      = pack("H10","1B2446420F");
			//			$this->G_EMOJI["#NO8#"]      = pack("H10","1B2446430F");
			//			$this->G_EMOJI["#NO9#"]      = pack("H10","1B2446440F");
			//			$this->G_EMOJI["#NO0#"]      = pack("H10","1B2446450F");
			// del 2010/07/20 Y.Matsukawa ]
			// add 2010/07/20 Y.Matsukawa [
			// mod 2011/06/08 Y.Matsukawa ※末尾に「;」追加
			$this->G_EMOJI["#SUN#"]               = "&#xE04A;";
			$this->G_EMOJI["#CLOUD#"]             = "&#xE049;";
			$this->G_EMOJI["#RAIN#"]              = "&#xE04B;";
			$this->G_EMOJI["#SNOW#"]              = "&#xE048;";
			$this->G_EMOJI["#THUNDER#"]           = "&#xE13D;";
			$this->G_EMOJI["#TYPHOON#"]           = "&#xE443;";
			$this->G_EMOJI["#FOG#"]               = "&#xE049;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#LIGHT_RAIN#"]        = "&#xE43C;";
			$this->G_EMOJI["#RAM#"]               = "&#xE23F;";
			$this->G_EMOJI["#BULL#"]              = "&#xE240;";
			$this->G_EMOJI["#TWINS#"]             = "&#xE241;";
			$this->G_EMOJI["#CRAB#"]              = "&#xE242;";
			$this->G_EMOJI["#LION#"]              = "&#xE243;";
			$this->G_EMOJI["#VIRGIN#"]            = "&#xE244;";
			$this->G_EMOJI["#BALANCE#"]           = "&#xE245;";
			$this->G_EMOJI["#SCORPION#"]          = "&#xE246;";
			$this->G_EMOJI["#ARCHER#"]            = "&#xE247;";
			$this->G_EMOJI["#GOAT#"]              = "&#xE248;";
			$this->G_EMOJI["#WATER_BEARER#"]      = "&#xE249;";
			$this->G_EMOJI["#FISHES#"]            = "&#xE24A;";
			$this->G_EMOJI["#SPORTS#"]            = "&#xE006;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#BASEBALL#"]          = "&#xE016;";
			$this->G_EMOJI["#GOLF#"]              = "&#xE014;";
			$this->G_EMOJI["#TENNIS#"]            = "&#xE015;";
			$this->G_EMOJI["#SOCCER#"]            = "&#xE018;";
			$this->G_EMOJI["#SKI#"]               = "&#xE013;";
			$this->G_EMOJI["#BASKETBALL#"]        = "&#xE42A;";
			$this->G_EMOJI["#FLAG#"]              = "&#xE132;";
			$this->G_EMOJI["#POCKET_BELL#"]       = "&#xE00A;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#TRAIN#"]             = "&#xE01E;";
			$this->G_EMOJI["#SUBWAY#"]            = "&#xE434;";
			$this->G_EMOJI["#SHINKANSEN#"]        = "&#xE435;";
			$this->G_EMOJI["#CAR#"]               = "&#xE01B;";
			$this->G_EMOJI["#CAR_2#"]             = "&#xE42E;";
			$this->G_EMOJI["#BUS#"]               = "&#xE159;";
			$this->G_EMOJI["#SHIP#"]              = "&#xE202;";
			$this->G_EMOJI["#AIRPLANE#"]          = "&#xE01D;";
			$this->G_EMOJI["#HOME#"]              = "&#xE036;";
			$this->G_EMOJI["#BUILD#"]             = "&#xE038;";
			$this->G_EMOJI["#POST#"]              = "&#xE153;";
			$this->G_EMOJI["#HOSPITAL#"]          = "&#xE155;";
			$this->G_EMOJI["#BANK#"]              = "&#xE14D;";
			$this->G_EMOJI["#ATM#"]               = "&#xE154;";
			$this->G_EMOJI["#HOTEL#"]             = "&#xE158;";
			$this->G_EMOJI["#CVS#"]               = "&#xE156;";
			$this->G_EMOJI["#GS#"]                = "&#xE03A;";
			$this->G_EMOJI["#PARK#"]              = "&#xE14F;";
			$this->G_EMOJI["#SIGNAL#"]            = "&#xE14E;";
			$this->G_EMOJI["#TOILET#"]            = "&#xE151;";
			$this->G_EMOJI["#RESTAURANT#"]        = "&#xE043;";
			$this->G_EMOJI["#CAFE#"]              = "&#xE045;";
			$this->G_EMOJI["#BAR#"]               = "&#xE044;";
			$this->G_EMOJI["#BEER#"]              = "&#xE047;";
			$this->G_EMOJI["#BURGER#"]            = "&#xE120;";
			$this->G_EMOJI["#BOUTIQUE#"]          = "&#xE13E;";
			$this->G_EMOJI["#BEAUTY_SALON#"]      = "&#xE313;";
			$this->G_EMOJI["#KARAOKE#"]           = "&#xE03C;";
			$this->G_EMOJI["#MOVIE#"]             = "&#xE03D;";
			$this->G_EMOJI["#RIGHT_UP#"]          = "&#xE236;";
			$this->G_EMOJI["#AMUSEMENT_PARK#"]    = "&#xE124;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#MUSIC#"]             = "&#xE30A;";
			$this->G_EMOJI["#ART#"]               = "&#xE502;";
			$this->G_EMOJI["#DRAMA#"]             = "&#xE503;";
			$this->G_EMOJI["#EVENT#"]             = "&#xE117;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#TICKET#"]            = "&#xE125;";
			$this->G_EMOJI["#SMOKING#"]           = "&#xE30E;";
			$this->G_EMOJI["#NO_SMOKING#"]        = "&#xE208;";
			$this->G_EMOJI["#CAMERA#"]            = "&#xE008;";
			$this->G_EMOJI["#BAG#"]               = "&#xE323;";
			$this->G_EMOJI["#BOOK#"]              = "&#xE148;";
			$this->G_EMOJI["#RIBBON#"]            = "&#xE314;";
			$this->G_EMOJI["#PRESENT#"]           = "&#xE112;";
			$this->G_EMOJI["#BIRTHDAY#"]          = "&#xE34B;";
			$this->G_EMOJI["#TEL#"]               = "&#xE009;";
			$this->G_EMOJI["#MOBILE#"]            = "&#xE00A;";
			$this->G_EMOJI["#MEMO#"]              = "&#xE301;";
			$this->G_EMOJI["#TV#"]                = "&#xE12A;";
			$this->G_EMOJI["#GAME#"]              = "&#xE12B;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#CD#"]                = "&#xE126;";
			$this->G_EMOJI["#HEART_TRUMP#"]       = "&#xE20C;";
			$this->G_EMOJI["#SPADE#"]             = "&#xE20E;";
			$this->G_EMOJI["#DIAMOND#"]           = "&#xE20D;";
			$this->G_EMOJI["#CLUBS#"]             = "&#xE20F;";
			$this->G_EMOJI["#EYE#"]               = "&#xE419;";
			$this->G_EMOJI["#EAR#"]               = "&#xE41B;";
			$this->G_EMOJI["#GOO#"]               = "&#xE010;";
			$this->G_EMOJI["#CHOKI#"]             = "&#xE011;";
			$this->G_EMOJI["#PAR#"]               = "&#xE012;";
			$this->G_EMOJI["#RIGHT_DOWN#"]        = "&#xE238;";
			$this->G_EMOJI["#LEFT_UP#"]           = "&#xE237;";
			$this->G_EMOJI["#FOOT#"]              = "&#xE536;";
			$this->G_EMOJI["#SHOES#"]             = "&#xE007;";
			$this->G_EMOJI["#GLASSES#"]           = "&#xE114;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#WHEELCHAIR#"]        = "&#xE20A;";
			$this->G_EMOJI["#NEW_MOON#"]          = "&#xE04C;";
			$this->G_EMOJI["#CHIP_MOON#"]         = "&#xE04C;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#HALF_MOON#"]         = "&#xE04C;";
			$this->G_EMOJI["#CRESCENT_MOON#"]     = "&#xE04C;";
			$this->G_EMOJI["#FULL_MOON#"]         = "&#xE04C;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#DOG#"]               = "&#xE052;";
			$this->G_EMOJI["#CAT#"]               = "&#xE04F;";
			$this->G_EMOJI["#RESORT#"]            = "&#xE01C;";
			$this->G_EMOJI["#XMAS#"]              = "&#xE033;";
			$this->G_EMOJI["#LEFT_DOWN#"]         = "&#xE239;";
			$this->G_EMOJI["#PHONE_TO#"]          = "&#xE104;";
			$this->G_EMOJI["#MAIL_TO#"]           = "&#xE103;";
			$this->G_EMOJI["#FAX_TO#"]            = "&#xE00B;";
			$this->G_EMOJI["#CARRIER#"]           = "i";			// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#CARRIER_2#"]         = "i";			// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#MAIL#"]              = "&#xE101;";
			$this->G_EMOJI["#OFFER#"]             = "D";			// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#POINT#"]             = "D";			// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#YEN#"]               = "&#xE12F;";
			$this->G_EMOJI["#FREE_YEN#"]          = "&#xE216;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#ID#"]                = "&#xE229;";
			$this->G_EMOJI["#PASSWORD#"]          = "&#xE03F;";
			$this->G_EMOJI["#RETURN#"]            = "&#xE235;";
			$this->G_EMOJI["#CLEAR#"]             = "&#xE216;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#SEARCH#"]            = "&#xE114;";
			$this->G_EMOJI["#NEW#"]               = "&#xE212;";
			$this->G_EMOJI["#ANTENNA#"]           = "&#xE14B;";
			$this->G_EMOJI["#FREE#"]              = "&#xE211;";
			$this->G_EMOJI["#SHARP_DIAL#"]        = "&#xE210;";
			$this->G_EMOJI["#MOB_Q#"]             = "&#xE00A;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#NO1#"]               = "&#xE21C;";
			$this->G_EMOJI["#NO2#"]               = "&#xE21D;";
			$this->G_EMOJI["#NO3#"]               = "&#xE21E;";
			$this->G_EMOJI["#NO4#"]               = "&#xE21F;";
			$this->G_EMOJI["#NO5#"]               = "&#xE220;";
			$this->G_EMOJI["#NO6#"]               = "&#xE221;";
			$this->G_EMOJI["#NO7#"]               = "&#xE222;";
			$this->G_EMOJI["#NO8#"]               = "&#xE223;";
			$this->G_EMOJI["#NO9#"]               = "&#xE224;";
			$this->G_EMOJI["#NO0#"]               = "&#xE225;";
			$this->G_EMOJI["#OK#"]                = "&#xE24D;";
			$this->G_EMOJI["#HEART#"]             = "&#xE022;";
			$this->G_EMOJI["#HEART_WAVE#"]        = "&#xE327;";
			$this->G_EMOJI["#HEART_BREAK#"]       = "&#xE023;";
			$this->G_EMOJI["#HEARTS#"]            = "&#xE327;";
			$this->G_EMOJI["#FACE_SMILE#"]        = "&#xE057;";
			$this->G_EMOJI["#FACE_ANGRY#"]        = "&#xE059;";
			$this->G_EMOJI["#FACE_DEJECT#"]       = "&#xE058;";
			$this->G_EMOJI["#FACE_SAD#"]          = "&#xE407;";
			$this->G_EMOJI["#FACE_SWING#"]        = "&#xE406;";
			$this->G_EMOJI["#GOOD#"]              = "&#xE236;";
			$this->G_EMOJI["#CHEERFUL#"]          = "&#xE03E;";
			$this->G_EMOJI["#FEEL_GOOD#"]         = "&#xE123;";
			$this->G_EMOJI["#CUTE#"]              = "&#xE204;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#KISS#"]              = "&#xE003;";
			$this->G_EMOJI["#SHINE#"]             = "&#xE32E;";
			$this->G_EMOJI["#HINT#"]              = "&#xE10F;";
			$this->G_EMOJI["#ANGER#"]             = "&#xE334;";
			$this->G_EMOJI["#PUNCH#"]             = "&#xE00D;";
			$this->G_EMOJI["#BOMB#"]              = "&#xE311;";
			$this->G_EMOJI["#MOOD#"]              = "&#xE326;";
			$this->G_EMOJI["#DOWN#"]              = "&#xE233;";
			$this->G_EMOJI["#SLEEP#"]             = "&#xE13C;";
			$this->G_EMOJI["#EXC#"]               = "&#xE021;";
			$this->G_EMOJI["#QUESTION#"]          = "&#xE021;&#xE020;";
			$this->G_EMOJI["#EXC_2#"]             = "&#xE021;&#xE021;";
			$this->G_EMOJI["#SHOCK#"]             = "&#xE10D;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#SWEAT#"]             = "&#xE331;";
			$this->G_EMOJI["#SWEAT_2#"]           = "&#xE331;";
			$this->G_EMOJI["#DASH#"]              = "&#xE330;";
			$this->G_EMOJI["#LONG_VOWEL#"]        = "&#xE234;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#LONG_VOWEL_2#"]      = "&#xE211;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#KACHINKO#"]          = "&#xE324;";
			$this->G_EMOJI["#POUCH#"]             = "&#xE11E;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#PEN#"]               = "&#xE301;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#SHADOW#"]            = "&#xE138;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#CHAIR#"]             = "&#xE11F;";
			$this->G_EMOJI["#NIGHT#"]             = "&#xE04C;";
			$this->G_EMOJI["#SOON#"]              = "&#xE23C;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#ON#"]                = "&#xE213;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#END#"]               = "&#xE23D;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#TIME#"]              = "&#xE024;";
			$this->G_EMOJI["#APPLI#"]             = "";				// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#APPLI_2#"]           = "";				// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#SHIRTS#"]            = "&#xE006;";
			$this->G_EMOJI["#WALLET#"]            = "&#xE12F;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#MAKEUP#"]            = "&#xE31C;";
			$this->G_EMOJI["#JEANS#"]             = "&#xE319;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#SNOW_BOARD#"]        = "&#xE013;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#CHAPEL#"]            = "&#xE325;";
			$this->G_EMOJI["#DOOR#"]              = "&#xE036;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#DOLLAR#"]            = "&#xE12F;";
			$this->G_EMOJI["#PC#"]                = "&#xE00C;";
			$this->G_EMOJI["#LOVE_LETTER#"]       = "&#xE103;&#xE328;";
			$this->G_EMOJI["#WRENCH#"]            = "&#xE116;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#PENCIL#"]            = "&#xE301;";
			$this->G_EMOJI["#CROWN#"]             = "&#xE10E;";
			$this->G_EMOJI["#RING#"]              = "&#xE034;";
			$this->G_EMOJI["#SANDGLASS#"]         = "&#xE02F;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#BICYCLE#"]           = "&#xE136;";
			$this->G_EMOJI["#TEACUP#"]            = "&#xE338;";
			$this->G_EMOJI["#WATCH#"]             = "&#xE027;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#FACE_THINK#"]        = "&#xE403;";
			$this->G_EMOJI["#FACE_PEACE#"]        = "&#xE40A;";
			$this->G_EMOJI["#FACE_HURRY#"]        = "&#xE415;&#xE331;";
			$this->G_EMOJI["#FACE_HURRY_2#"]      = "&#xE108;";
			$this->G_EMOJI["#FACE_ANGRY_2#"]      = "&#xE416;";
			$this->G_EMOJI["#FACE_POKER#"]        = "&#xE40E;";
			$this->G_EMOJI["#FACE_HEART#"]        = "&#xE106;";
			$this->G_EMOJI["#FINGER#"]            = "&#xE00E;";
			$this->G_EMOJI["#FACE_JOKE#"]         = "&#xE105;";
			$this->G_EMOJI["#FACE_WINK#"]         = "&#xE405;";
			$this->G_EMOJI["#FACE_HAPPY#"]        = "&#xE40A;";
			$this->G_EMOJI["#FACE_PATIENCE#"]     = "&#xE406;";
			$this->G_EMOJI["#CAT_2#"]             = "&#xE402;";
			$this->G_EMOJI["#FACE_CRY#"]          = "&#xE411;";
			$this->G_EMOJI["#TEAR#"]              = "&#xE413;";
			$this->G_EMOJI["#NG#"]                = "NG";			// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#CLIP#"]              = "&#xE301;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#COPYRIGHT#"]         = "&#xE24E;";
			$this->G_EMOJI["#TM#"]                = "&#xE537;";
			$this->G_EMOJI["#RUNNER#"]            = "&#xE115;";
			$this->G_EMOJI["#SECRET#"]            = "&#xE315;";
			$this->G_EMOJI["#RECYCLING#"]         = "&#xE23C;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#REGIST#"]            = "&#xE24F;";
			$this->G_EMOJI["#WARNING#"]           = "&#xE252;";
			$this->G_EMOJI["#PROHIBITION#"]       = "";				// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#EMPTY#"]             = "&#xE22B;";
			$this->G_EMOJI["#SUCCESS#"]           = "&#xE00E;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#FULL#"]              = "&#xE22A;";
			$this->G_EMOJI["#RIGHT_LEFT#"]        = "&#xE235;&#xE234;";	// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#UP_DOWN#"]           = "&#xE232;&#xE233;";	// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#SCHOOL#"]            = "&#xE157;";
			$this->G_EMOJI["#WAVE#"]              = "&#xE43E;";
			$this->G_EMOJI["#MOUNTAIN#"]          = "&#xE03B;";
			$this->G_EMOJI["#CLOVER#"]            = "&#xE110;";
			$this->G_EMOJI["#CHERRY#"]            = "&#xE347;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#TULIP#"]             = "&#xE304;";
			$this->G_EMOJI["#BANANA#"]            = "&#xE346;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#APPLE#"]             = "&#xE345;";
			$this->G_EMOJI["#LEAF#"]              = "&#xE110;";
			$this->G_EMOJI["#MAPLE#"]             = "&#xE118;";
			$this->G_EMOJI["#CHERRY_BLOSSOM#"]    = "&#xE030;";
			$this->G_EMOJI["#RICE_BALL#"]         = "&#xE342;";
			$this->G_EMOJI["#CAKE#"]              = "&#xE046;";
			$this->G_EMOJI["#SAKE#"]              = "&#xE30B;";
			$this->G_EMOJI["#BOWL#"]              = "&#xE340;";
			$this->G_EMOJI["#PAN#"]               = "&#xE339;";
			$this->G_EMOJI["#SNAIL#"]             = "&#xE531;";		// 該当する絵文字がないため類似絵文字を表示
			$this->G_EMOJI["#BABY_BIRD#"]         = "&#xE523;";
			$this->G_EMOJI["#PENGUIN#"]           = "&#xE055;";
			$this->G_EMOJI["#FISH#"]              = "&#xE019;";
			$this->G_EMOJI["#FACE_DELICIOUS#"]    = "&#xE056;";
			$this->G_EMOJI["#FACE_FOPPISH#"]      = "&#xE404;";
			$this->G_EMOJI["#HORSE#"]             = "&#xE01A;";
			$this->G_EMOJI["#PIG#"]               = "&#xE10B;";
			$this->G_EMOJI["#WINE#"]              = "&#xE044;";
			$this->G_EMOJI["#FACE_LET_DOWN#"]     = "&#xE107;";
			// add 2010/07/20 Y.Matsukawa ]
			$this->G_SUPPORT_IMAGE_EXT   = "PNG";
			$this->G_SUPPORT_CMDN_TYP    = 1;
			break;
		case D_KDDI:
			$this->G_EMOJI["#SUN#"]               = "<IMG LOCALSRC=\"44\" ALT=\"SUN\">";
			$this->G_EMOJI["#CLOUD#"]             = "<IMG LOCALSRC=\"107\" ALT=\"CLOUD\">";
			$this->G_EMOJI["#RAIN#"]              = "<IMG LOCALSRC=\"95\" ALT=\"RAIN\">";
			$this->G_EMOJI["#SNOW#"]              = "<IMG LOCALSRC=\"191\" ALT=\"SNOW\">";
			$this->G_EMOJI["#THUNDER#"]           = "<IMG LOCALSRC=\"16\" ALT=\"THUNDER\">";
			$this->G_EMOJI["#TYPHOON#"]           = "<IMG LOCALSRC=\"190\" ALT=\"TYPHOON\">";
			$this->G_EMOJI["#FOG#"]               = "<IMG LOCALSRC=\"305\" ALT=\"FOG\">";
			$this->G_EMOJI["#LIGHT_RAIN#"]        = "<IMG LOCALSRC=\"481\" ALT=\"LIGHT_RAIN\">";
			$this->G_EMOJI["#RAM#"]               = "<IMG LOCALSRC=\"192\" ALT=\"RAM\">";
			$this->G_EMOJI["#BULL#"]              = "<IMG LOCALSRC=\"193\" ALT=\"BULL\">";
			$this->G_EMOJI["#TWINS#"]             = "<IMG LOCALSRC=\"194\" ALT=\"TWINS\">";
			$this->G_EMOJI["#CRAB#"]              = "<IMG LOCALSRC=\"195\" ALT=\"CRAB\">";
			$this->G_EMOJI["#LION#"]              = "<IMG LOCALSRC=\"196\" ALT=\"LION\">";
			$this->G_EMOJI["#VIRGIN#"]            = "<IMG LOCALSRC=\"197\" ALT=\"VIRGIN\">";
			$this->G_EMOJI["#BALANCE#"]           = "<IMG LOCALSRC=\"198\" ALT=\"BALANCE\">";
			$this->G_EMOJI["#SCORPION#"]          = "<IMG LOCALSRC=\"199\" ALT=\"SCORPION\">";
			$this->G_EMOJI["#ARCHER#"]            = "<IMG LOCALSRC=\"200\" ALT=\"ARCHER\">";
			$this->G_EMOJI["#GOAT#"]              = "<IMG LOCALSRC=\"201\" ALT=\"GOAT\">";
			$this->G_EMOJI["#WATER_BEARER#"]      = "<IMG LOCALSRC=\"202\" ALT=\"WATER_BEARER\">";
			$this->G_EMOJI["#FISHES#"]            = "<IMG LOCALSRC=\"203\" ALT=\"FISHES\">";
			$this->G_EMOJI["#SPORTS#"]            = "<IMG LOCALSRC=\"218\" ALT=\"SPORTS\">";
			$this->G_EMOJI["#BASEBALL#"]          = "<IMG LOCALSRC=\"45\" ALT=\"BASEBALL\">";
			$this->G_EMOJI["#GOLF#"]              = "<IMG LOCALSRC=\"306\" ALT=\"GOLF\">";
			$this->G_EMOJI["#TENNIS#"]            = "<IMG LOCALSRC=\"220\" ALT=\"TENNIS\">";
			$this->G_EMOJI["#SOCCER#"]            = "<IMG LOCALSRC=\"219\" ALT=\"SOCCER\">";
			$this->G_EMOJI["#SKI#"]               = "<IMG LOCALSRC=\"421\" ALT=\"SKI\">";
			$this->G_EMOJI["#BASKETBALL#"]        = "<IMG LOCALSRC=\"307\" ALT=\"BASKETBALL\">";
			$this->G_EMOJI["#FLAG#"]              = "<IMG LOCALSRC=\"222\" ALT=\"FLAG\">";
			$this->G_EMOJI["#POCKET_BELL#"]       = "<IMG LOCALSRC=\"308\" ALT=\"POCKET_BELL\">";
			$this->G_EMOJI["#TRAIN#"]             = "<IMG LOCALSRC=\"172\" ALT=\"TRAIN\">";
			$this->G_EMOJI["#SUBWAY#"]            = "<IMG LOCALSRC=\"341\" ALT=\"SUBWAY\">";
			$this->G_EMOJI["#SHINKANSEN#"]        = "<IMG LOCALSRC=\"217\" ALT=\"SHINKANSEN\">";
			$this->G_EMOJI["#CAR#"]               = "<IMG LOCALSRC=\"125\" ALT=\"CAR\">";
			$this->G_EMOJI["#CAR_2#"]             = "<IMG LOCALSRC=\"125\" ALT=\"CAR_2\">";
			$this->G_EMOJI["#BUS#"]               = "<IMG LOCALSRC=\"216\" ALT=\"BUS\">";
			$this->G_EMOJI["#SHIP#"]              = "<IMG LOCALSRC=\"379\" ALT=\"SHIP\">";
			$this->G_EMOJI["#AIRPLANE#"]          = "<IMG LOCALSRC=\"168\" ALT=\"AIRPLANE\">";
			$this->G_EMOJI["#HOME#"]              = "<IMG LOCALSRC=\"112\" ALT=\"HOME\">";
			$this->G_EMOJI["#BUILD#"]             = "<IMG LOCALSRC=\"156\" ALT=\"BUILD\">";
			$this->G_EMOJI["#POST#"]              = "<IMG LOCALSRC=\"375\" ALT=\"POST\">";
			$this->G_EMOJI["#HOSPITAL#"]          = "<IMG LOCALSRC=\"376\" ALT=\"HOSPITAL\">";
			$this->G_EMOJI["#BANK#"]              = "<IMG LOCALSRC=\"212\" ALT=\"BANK\">";
			$this->G_EMOJI["#ATM#"]               = "<IMG LOCALSRC=\"205\" ALT=\"ATM\">";
			$this->G_EMOJI["#HOTEL#"]             = "<IMG LOCALSRC=\"378\" ALT=\"HOTEL\">";
			$this->G_EMOJI["#CVS#"]               = "<IMG LOCALSRC=\"206\" ALT=\"CVS\">";
			$this->G_EMOJI["#GS#"]                = "<IMG LOCALSRC=\"213\" ALT=\"GS\">";
			$this->G_EMOJI["#PARK#"]              = "<IMG LOCALSRC=\"208\" ALT=\"PARK\">";
			$this->G_EMOJI["#SIGNAL#"]            = "<IMG LOCALSRC=\"99\" ALT=\"SIGNAL\">";
			$this->G_EMOJI["#TOILET#"]            = "<IMG LOCALSRC=\"207\" ALT=\"TOILET\">";
			$this->G_EMOJI["#RESTAURANT#"]        = "<IMG LOCALSRC=\"146\" ALT=\"RESTAURANT\">";
			$this->G_EMOJI["#CAFE#"]              = "<IMG LOCALSRC=\"93\" ALT=\"CAFE\">";
			$this->G_EMOJI["#BAR#"]               = "<IMG LOCALSRC=\"52\" ALT=\"BAR\">";
			$this->G_EMOJI["#BEER#"]              = "<IMG LOCALSRC=\"65\" ALT=\"BEER\">";
			$this->G_EMOJI["#BURGER#"]            = "<IMG LOCALSRC=\"245\" ALT=\"BURGER\">";
			$this->G_EMOJI["#BOUTIQUE#"]          = "<IMG LOCALSRC=\"124\" ALT=\"BOUTIQUE\">";
			$this->G_EMOJI["#BEAUTY_SALON#"]      = "<IMG LOCALSRC=\"104\" ALT=\"BEAUTY_SALON\">";
			$this->G_EMOJI["#KARAOKE#"]           = "<IMG LOCALSRC=\"289\" ALT=\"KARAOKE\">";
			$this->G_EMOJI["#MOVIE#"]             = "<IMG LOCALSRC=\"110\" ALT=\"MOVIE\">";
			$this->G_EMOJI["#RIGHT_UP#"]          = "<IMG LOCALSRC=\"70\" ALT=\"RIGHT_UP\">";
			$this->G_EMOJI["#AMUSEMENT_PARK#"]    = "<IMG LOCALSRC=\"223\" ALT=\"AMUSEMENT_PARK\">";
			$this->G_EMOJI["#MUSIC#"]             = "<IMG LOCALSRC=\"294\" ALT=\"MUSIC\">";
			$this->G_EMOJI["#ART#"]               = "<IMG LOCALSRC=\"309\" ALT=\"ART\">";
			$this->G_EMOJI["#DRAMA#"]             = "<IMG LOCALSRC=\"494\" ALT=\"DRAMA\">";
			$this->G_EMOJI["#EVENT#"]             = "<IMG LOCALSRC=\"311\" ALT=\"EVENT\">";
			$this->G_EMOJI["#TICKET#"]            = "<IMG LOCALSRC=\"106\" ALT=\"TICKET\">";
			$this->G_EMOJI["#SMOKING#"]           = "<IMG LOCALSRC=\"176\" ALT=\"SMOKING\">";
			$this->G_EMOJI["#NO_SMOKING#"]        = "<IMG LOCALSRC=\"177\" ALT=\"NO_SMOKING\">";
			$this->G_EMOJI["#CAMERA#"]            = "<IMG LOCALSRC=\"94\" ALT=\"CAMERA\">";
			$this->G_EMOJI["#BAG#"]               = "<IMG LOCALSRC=\"83\" ALT=\"BAG\">";
			$this->G_EMOJI["#BOOK#"]              = "<IMG LOCALSRC=\"122\" ALT=\"BOOK\">";
			$this->G_EMOJI["#RIBBON#"]            = "<IMG LOCALSRC=\"312\" ALT=\"RIBBON\">";
			$this->G_EMOJI["#PRESENT#"]           = "<IMG LOCALSRC=\"144\" ALT=\"PRESENT\">";
			$this->G_EMOJI["#BIRTHDAY#"]          = "<IMG LOCALSRC=\"313\" ALT=\"BIRTHDAY\">";
			$this->G_EMOJI["#TEL#"]               = "<IMG LOCALSRC=\"85\" ALT=\"TEL\">";
			$this->G_EMOJI["#MOBILE#"]            = "<IMG LOCALSRC=\"161\" ALT=\"MOBILE\">";
			$this->G_EMOJI["#MEMO#"]              = "<IMG LOCALSRC=\"56\" ALT=\"MEMO\">";
			$this->G_EMOJI["#TV#"]                = "<IMG LOCALSRC=\"288\" ALT=\"TV\">";
			$this->G_EMOJI["#GAME#"]              = "<IMG LOCALSRC=\"232\" ALT=\"GAME\">";
			$this->G_EMOJI["#CD#"]                = "<IMG LOCALSRC=\"300\" ALT=\"CD\">";
			$this->G_EMOJI["#HEART_TRUMP#"]       = "<IMG LOCALSRC=\"414\" ALT=\"HEART_TRUMP\">";
			$this->G_EMOJI["#SPADE#"]             = "<IMG LOCALSRC=\"314\" ALT=\"SPADE\">";
			$this->G_EMOJI["#DIAMOND#"]           = "<IMG LOCALSRC=\"315\" ALT=\"DIAMOND\">";
			$this->G_EMOJI["#CLUBS#"]             = "<IMG LOCALSRC=\"316\" ALT=\"CLUBS\">";
			$this->G_EMOJI["#EYE#"]               = "<IMG LOCALSRC=\"317\" ALT=\"EYE\">";
			$this->G_EMOJI["#EAR#"]               = "<IMG LOCALSRC=\"318\" ALT=\"EAR\">";
			$this->G_EMOJI["#GOO#"]               = "<IMG LOCALSRC=\"817\" ALT=\"GOO\">";
			$this->G_EMOJI["#CHOKI#"]             = "<IMG LOCALSRC=\"319\" ALT=\"CHOKI\">";
			$this->G_EMOJI["#PAR#"]               = "<IMG LOCALSRC=\"320\" ALT=\"PAR\">";
			$this->G_EMOJI["#RIGHT_DOWN#"]        = "<IMG LOCALSRC=\"43\" ALT=\"RIGHT_DOWN\">";
			$this->G_EMOJI["#LEFT_UP#"]           = "<IMG LOCALSRC=\"42\" ALT=\"LEFT_UP\">";
			$this->G_EMOJI["#FOOT#"]              = "<IMG LOCALSRC=\"728\" ALT=\"FOOT\">";
			$this->G_EMOJI["#SHOES#"]             = "<IMG LOCALSRC=\"336\" ALT=\"SHOES\">";
			$this->G_EMOJI["#GLASSES#"]           = "<IMG LOCALSRC=\"116\" ALT=\"GLASSES\">";
			$this->G_EMOJI["#WHEELCHAIR#"]        = "<IMG LOCALSRC=\"178\" ALT=\"WHEELCHAIR\">";
			$this->G_EMOJI["#NEW_MOON#"]          = "<IMG LOCALSRC=\"321\" ALT=\"NEW_MOON\">";
			$this->G_EMOJI["#CHIP_MOON#"]         = "<IMG LOCALSRC=\"322\" ALT=\"CHIP_MOON\">";
			$this->G_EMOJI["#HALF_MOON#"]         = "<IMG LOCALSRC=\"323\" ALT=\"HALF_MOON\">";
			$this->G_EMOJI["#CRESCENT_MOON#"]     = "<IMG LOCALSRC=\"15\" ALT=\"CRESCENT_MOON\">";
			$this->G_EMOJI["#FULL_MOON#"]         = "<IMG LOCALSRC=\"47\" ALT=\"FULL_MOON\">";
			$this->G_EMOJI["#DOG#"]               = "<IMG LOCALSRC=\"134\" ALT=\"DOG\">";
			$this->G_EMOJI["#CAT#"]               = "<IMG LOCALSRC=\"251\" ALT=\"CAT\">";
			$this->G_EMOJI["#RESORT#"]            = "<IMG LOCALSRC=\"169\" ALT=\"RESORT\">";
			$this->G_EMOJI["#XMAS#"]              = "<IMG LOCALSRC=\"234\" ALT=\"XMAS\">";
			$this->G_EMOJI["#LEFT_DOWN#"]         = "<IMG LOCALSRC=\"71\" ALT=\"LEFT_DOWN\">";
			$this->G_EMOJI["#PHONE_TO#"]          = "<IMG LOCALSRC=\"513\" ALT=\"PHONE_TO\">";
			$this->G_EMOJI["#MAIL_TO#"]           = "<IMG LOCALSRC=\"784\" ALT=\"MAIL_TO\">";
			$this->G_EMOJI["#FAX_TO#"]            = "<IMG LOCALSRC=\"166\" ALT=\"FAX_TO\">";
			$this->G_EMOJI["#CARRIER#"]           = "i";		// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#CARRIER_2#"]         = "i";		// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#MAIL#"]              = "<IMG LOCALSRC=\"108\" ALT=\"MAIL\">";
			$this->G_EMOJI["#OFFER#"]             = "D";		// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#POINT#"]             = "D";		// 該当する絵文字がないため文字に変換
			$this->G_EMOJI["#YEN#"]               = "<IMG LOCALSRC=\"109\" ALT=\"YEN\">";
			$this->G_EMOJI["#FREE_YEN#"]          = "<IMG LOCALSRC=\"299\" ALT=\"FREE_YEN\">";
			$this->G_EMOJI["#ID#"]                = "<IMG LOCALSRC=\"385\" ALT=\"ID\">";
			$this->G_EMOJI["#PASSWORD#"]          = "<IMG LOCALSRC=\"120\" ALT=\"PASSWORD\">";
			$this->G_EMOJI["#RETURN#"]            = "<IMG LOCALSRC=\"118\" ALT=\"RETURN\">";
			$this->G_EMOJI["#CLEAR#"]             = "<IMG LOCALSRC=\"324\" ALT=\"CLEAR\">";
			$this->G_EMOJI["#SEARCH#"]            = "<IMG LOCALSRC=\"119\" ALT=\"SEARCH\">";
			$this->G_EMOJI["#NEW#"]               = "<IMG LOCALSRC=\"334\" ALT=\"NEW\">";
			$this->G_EMOJI["#ANTENNA#"]           = "<IMG LOCALSRC=\"210\" ALT=\"ANTENNA\">";
			$this->G_EMOJI["#FREE#"]              = "<IMG LOCALSRC=\"85\" ALT=\"FREE\">";
			$this->G_EMOJI["#SHARP_DIAL#"]        = "<IMG LOCALSRC=\"818\" ALT=\"SHARP_DIAL\">";
			$this->G_EMOJI["#MOB_Q#"]             = "<IMG LOCALSRC=\"4\" ALT=\"MOB_Q\">";
			$this->G_EMOJI["#NO1#"]               = "<IMG LOCALSRC=\"180\" ALT=\"1\">";
			$this->G_EMOJI["#NO2#"]               = "<IMG LOCALSRC=\"181\" ALT=\"2\">";
			$this->G_EMOJI["#NO3#"]               = "<IMG LOCALSRC=\"182\" ALT=\"3\">";
			$this->G_EMOJI["#NO4#"]               = "<IMG LOCALSRC=\"183\" ALT=\"4\">";
			$this->G_EMOJI["#NO5#"]               = "<IMG LOCALSRC=\"184\" ALT=\"5\">";
			$this->G_EMOJI["#NO6#"]               = "<IMG LOCALSRC=\"185\" ALT=\"6\">";
			$this->G_EMOJI["#NO7#"]               = "<IMG LOCALSRC=\"186\" ALT=\"7\">";
			$this->G_EMOJI["#NO8#"]               = "<IMG LOCALSRC=\"187\" ALT=\"8\">";
			$this->G_EMOJI["#NO9#"]               = "<IMG LOCALSRC=\"188\" ALT=\"9\">";
			$this->G_EMOJI["#NO0#"]               = "<IMG LOCALSRC=\"325\" ALT=\"0\">";
			$this->G_EMOJI["#OK#"]                = "<IMG LOCALSRC=\"326\" ALT=\"OK\">";
			$this->G_EMOJI["#HEART#"]             = "<IMG LOCALSRC=\"414\" ALT=\"HEART\">";
			$this->G_EMOJI["#HEART_WAVE#"]        = "<IMG LOCALSRC=\"328\" ALT=\"HEART_WAVE\">";
			$this->G_EMOJI["#HEART_BREAK#"]       = "<IMG LOCALSRC=\"265\" ALT=\"HEART_BREAK\">";
			$this->G_EMOJI["#HEARTS#"]            = "<IMG LOCALSRC=\"266\" ALT=\"HEARTS\">";
			$this->G_EMOJI["#FACE_SMILE#"]        = "<IMG LOCALSRC=\"257\" ALT=\"FACE_SMILE\">";
			$this->G_EMOJI["#FACE_ANGRY#"]        = "<IMG LOCALSRC=\"258\" ALT=\"FACE_ANGRY\">";
			$this->G_EMOJI["#FACE_DEJECT#"]       = "<IMG LOCALSRC=\"260\" ALT=\"FACE_DEJECT\">";
			$this->G_EMOJI["#FACE_SAD#"]          = "<IMG LOCALSRC=\"259\" ALT=\"FACE_SAD\">";
			$this->G_EMOJI["#FACE_SWING#"]        = "<IMG LOCALSRC=\"327\" ALT=\"FACE_SWING\">";
			$this->G_EMOJI["#GOOD#"]              = "<IMG LOCALSRC=\"731\" ALT=\"GOOD\">";
			$this->G_EMOJI["#CHEERFUL#"]          = "<IMG LOCALSRC=\"343\" ALT=\"CHEERFUL\">";
			$this->G_EMOJI["#FEEL_GOOD#"]         = "<IMG LOCALSRC=\"224\" ALT=\"FEEL_GOOD\">";
			$this->G_EMOJI["#CUTE#"]              = "<IMG LOCALSRC=\"19\" ALT=\"CUTE\">";
			$this->G_EMOJI["#KISS#"]              = "<IMG LOCALSRC=\"273\" ALT=\"KISS\">";
			$this->G_EMOJI["#SHINE#"]             = "<IMG LOCALSRC=\"420\" ALT=\"SHINE\">";
			$this->G_EMOJI["#HINT#"]              = "<IMG LOCALSRC=\"77\" ALT=\"HINT\">";
			$this->G_EMOJI["#ANGER#"]             = "<IMG LOCALSRC=\"262\" ALT=\"ANGER\">";
			$this->G_EMOJI["#PUNCH#"]             = "<IMG LOCALSRC=\"281\" ALT=\"PUNCH\">";
			$this->G_EMOJI["#BOMB#"]              = "<IMG LOCALSRC=\"268\" ALT=\"BOMB\">";
			$this->G_EMOJI["#MOOD#"]              = "<IMG LOCALSRC=\"291\" ALT=\"MOOD\">";
			$this->G_EMOJI["#DOWN#"]              = "<IMG LOCALSRC=\"732\" ALT=\"DOWN\">";
			$this->G_EMOJI["#SLEEP#"]             = "<IMG LOCALSRC=\"261\" ALT=\"SLEEP\">";
			$this->G_EMOJI["#EXC#"]               = "<IMG LOCALSRC=\"2\" ALT=\"EXC\">";
			$this->G_EMOJI["#QUESTION#"]          = "<IMG LOCALSRC=\"733\" ALT=\"QUESTION\">";
			$this->G_EMOJI["#EXC_2#"]             = "<IMG LOCALSRC=\"734\" ALT=\"EXC_2\">";
			$this->G_EMOJI["#SHOCK#"]             = "<IMG LOCALSRC=\"329\" ALT=\"SHOCK\">";
			$this->G_EMOJI["#SWEAT#"]             = "<IMG LOCALSRC=\"330\" ALT=\"SWEAT\">";
			$this->G_EMOJI["#SWEAT_2#"]           = "<IMG LOCALSRC=\"263\" ALT=\"SWEAT_2\">";
			$this->G_EMOJI["#DASH#"]              = "<IMG LOCALSRC=\"282\" ALT=\"DASH\">";
			$this->G_EMOJI["#LONG_VOWEL#"]        = "<IMG LOCALSRC=\"810\" ALT=\"LONG_VOWEL\">";
			$this->G_EMOJI["#LONG_VOWEL_2#"]      = "<IMG LOCALSRC=\"735\" ALT=\"LONG_VOWEL_2\">";
			$this->G_EMOJI["#KACHINKO#"]          = "<IMG LOCALSRC=\"226\" ALT=\"KACHINKO\">";
			$this->G_EMOJI["#POUCH#"]             = "<IMG LOCALSRC=\"233\" ALT=\"POUCH\">";
			$this->G_EMOJI["#PEN#"]               = "<IMG LOCALSRC=\"508\" ALT=\"PEN\">";
			$this->G_EMOJI["#SHADOW#"]            = "<IMG LOCALSRC=\"80\" ALT=\"SHADOW\">";
			$this->G_EMOJI["#CHAIR#"]             = "";		// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#NIGHT#"]             = "<IMG LOCALSRC=\"15\" ALT=\"NIGHT\">";
			$this->G_EMOJI["#SOON#"]              = "<IMG LOCALSRC=\"63\" ALT=\"SOON\">";
			$this->G_EMOJI["#ON#"]                = "<IMG LOCALSRC=\"808\" ALT=\"ON\">";
			$this->G_EMOJI["#END#"]               = "<IMG LOCALSRC=\"64\" ALT=\"END\">";
			$this->G_EMOJI["#TIME#"]              = "<IMG LOCALSRC=\"46\" ALT=\"TIME\">";
			$this->G_EMOJI["#APPLI#"]             = "";		// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#APPLI_2#"]           = "";		// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#SHIRTS#"]            = "<IMG LOCALSRC=\"335\" ALT=\"SHIRTS\">";
			$this->G_EMOJI["#WALLET#"]            = "<IMG LOCALSRC=\"290\" ALT=\"WALLET\">";
			$this->G_EMOJI["#MAKEUP#"]            = "<IMG LOCALSRC=\"295\" ALT=\"MAKEUP\">";
			$this->G_EMOJI["#JEANS#"]             = "<IMG LOCALSRC=\"805\" ALT=\"JEANS\">";
			$this->G_EMOJI["#SNOW_BOARD#"]        = "<IMG LOCALSRC=\"221\" ALT=\"SNOW_BOARD\">";
			$this->G_EMOJI["#CHAPEL#"]            = "<IMG LOCALSRC=\"48\" ALT=\"CHAPEL\">";
			$this->G_EMOJI["#DOOR#"]              = "";		// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#DOLLAR#"]            = "<IMG LOCALSRC=\"233\" ALT=\"DOLLAR\">";
			$this->G_EMOJI["#PC#"]                = "<IMG LOCALSRC=\"337\" ALT=\"PC\">";
			$this->G_EMOJI["#LOVE_LETTER#"]       = "<IMG LOCALSRC=\"806\" ALT=\"LOVE_LETTER\">";
			$this->G_EMOJI["#WRENCH#"]            = "<IMG LOCALSRC=\"152\" ALT=\"WRENCH\">";
			$this->G_EMOJI["#PENCIL#"]            = "<IMG LOCALSRC=\"149\" ALT=\"PENCIL\">";
			$this->G_EMOJI["#CROWN#"]             = "<IMG LOCALSRC=\"354\" ALT=\"CROWN\">";
			$this->G_EMOJI["#RING#"]              = "<IMG LOCALSRC=\"72\" ALT=\"RING\">";
			$this->G_EMOJI["#SANDGLASS#"]         = "<IMG LOCALSRC=\"58\" ALT=\"SANDGLASS\">";
			$this->G_EMOJI["#BICYCLE#"]           = "<IMG LOCALSRC=\"215\" ALT=\"BICYCLE\">";
			$this->G_EMOJI["#TEACUP#"]            = "<IMG LOCALSRC=\"423\" ALT=\"TEACUP\">";
			$this->G_EMOJI["#WATCH#"]             = "<IMG LOCALSRC=\"25\" ALT=\"WATCH\">";
			$this->G_EMOJI["#FACE_THINK#"]        = "<IMG LOCALSRC=\"441\" ALT=\"FACE_THINK\">";
			$this->G_EMOJI["#FACE_PEACE#"]        = "<IMG LOCALSRC=\"446\" ALT=\"FACE_PEACE\">";
			$this->G_EMOJI["#FACE_HURRY#"]        = "<IMG LOCALSRC=\"257\" ALT=\"FACE_HURRY\"><IMG LOCALSRC=\"330\" ALT=\"FACE_HURRY\">";
			$this->G_EMOJI["#FACE_HURRY_2#"]      = "<IMG LOCALSRC=\"351\" ALT=\"FACE_HURRY_2\">";
			$this->G_EMOJI["#FACE_ANGRY_2#"]      = "<IMG LOCALSRC=\"779\" ALT=\"FACE_ANGRY_2\">";
			$this->G_EMOJI["#FACE_POKER#"]        = "<IMG LOCALSRC=\"450\" ALT=\"FACE_POKER\">";
			$this->G_EMOJI["#FACE_HEART#"]        = "<IMG LOCALSRC=\"349\" ALT=\"FACE_HEART\">";
			$this->G_EMOJI["#FINGER#"]            = "<IMG LOCALSRC=\"287\" ALT=\"FINGER\">";
			$this->G_EMOJI["#FACE_JOKE#"]         = "<IMG LOCALSRC=\"264\" ALT=\"FACE_JOKE\">";
			$this->G_EMOJI["#FACE_WINK#"]         = "<IMG LOCALSRC=\"348\" ALT=\"FACE_WINK\">";
			$this->G_EMOJI["#FACE_HAPPY#"]        = "<IMG LOCALSRC=\"446\" ALT=\"FACE_HAPPY\">";
			$this->G_EMOJI["#FACE_PATIENCE#"]     = "<IMG LOCALSRC=\"443\" ALT=\"FACE_PATIENCE\">";
			$this->G_EMOJI["#CAT_2#"]             = "<IMG LOCALSRC=\"440\" ALT=\"CAT_2\">";
			$this->G_EMOJI["#FACE_CRY#"]          = "<IMG LOCALSRC=\"259\" ALT=\"FACE_CRY\">";
			$this->G_EMOJI["#TEAR#"]              = "<IMG LOCALSRC=\"791\" ALT=\"TEAR\">";
			$this->G_EMOJI["#NG#"]                = "NG";		// 該当する絵文字がないため文字に変換;
			$this->G_EMOJI["#CLIP#"]              = "<IMG LOCALSRC=\"143\" ALT=\"CLIP\">";
			$this->G_EMOJI["#COPYRIGHT#"]         = "<IMG LOCALSRC=\"81\" ALT=\"COPYRIGHT\">";
			$this->G_EMOJI["#TM#"]                = "<IMG LOCALSRC=\"54\" ALT=\"TM\">";
			$this->G_EMOJI["#RUNNER#"]            = "<IMG LOCALSRC=\"218\" ALT=\"RUNNER\">";
			$this->G_EMOJI["#SECRET#"]            = "<IMG LOCALSRC=\"279\" ALT=\"SECRET\">";
			$this->G_EMOJI["#RECYCLING#"]         = "<IMG LOCALSRC=\"807\" ALT=\"RECYCLING\">";
			$this->G_EMOJI["#REGIST#"]            = "<IMG LOCALSRC=\"82\" ALT=\"REGIST\">";
			$this->G_EMOJI["#WARNING#"]           = "<IMG LOCALSRC=\"1\" ALT=\"WARNING\">";
			$this->G_EMOJI["#PROHIBITION#"]       = "";		// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#EMPTY#"]             = "<IMG LOCALSRC=\"387\" ALT=\"EMPTY\">";
			$this->G_EMOJI["#SUCCESS#"]           = "";		// 該当する絵文字がないため空白文字に変換
			$this->G_EMOJI["#FULL#"]              = "<IMG LOCALSRC=\"386\" ALT=\"FULL\">";
			$this->G_EMOJI["#RIGHT_LEFT#"]        = "<IMG LOCALSRC=\"808\" ALT=\"RIGHT_LEFT\">";
			$this->G_EMOJI["#UP_DOWN#"]           = "<IMG LOCALSRC=\"809\" ALT=\"UP_DOWN\">";
			$this->G_EMOJI["#SCHOOL#"]            = "<IMG LOCALSRC=\"377\" ALT=\"SCHOOL\">";
			$this->G_EMOJI["#WAVE#"]              = "<IMG LOCALSRC=\"810\" ALT=\"WAVE\">";
			$this->G_EMOJI["#MOUNTAIN#"]          = "<IMG LOCALSRC=\"342\" ALT=\"MOUNTAIN\">";
			$this->G_EMOJI["#CLOVER#"]            = "<IMG LOCALSRC=\"53\" ALT=\"CLOVER\">";
			$this->G_EMOJI["#CHERRY#"]            = "<IMG LOCALSRC=\"241\" ALT=\"CHERRY\">";
			$this->G_EMOJI["#TULIP#"]             = "<IMG LOCALSRC=\"113\" ALT=\"TULIP\">";
			$this->G_EMOJI["#BANANA#"]            = "<IMG LOCALSRC=\"739\" ALT=\"BANANA\">";
			$this->G_EMOJI["#APPLE#"]             = "<IMG LOCALSRC=\"434\" ALT=\"APPLE\">";
			$this->G_EMOJI["#LEAF#"]              = "<IMG LOCALSRC=\"811\" ALT=\"LEAF\">";
			$this->G_EMOJI["#MAPLE#"]             = "<IMG LOCALSRC=\"133\" ALT=\"MAPLE\">";
			$this->G_EMOJI["#CHERRY_BLOSSOM#"]    = "<IMG LOCALSRC=\"235\" ALT=\"CHERRY_BLOSSOM\">";
			$this->G_EMOJI["#RICE_BALL#"]         = "<IMG LOCALSRC=\"244\" ALT=\"RICE_BALL\">";
			$this->G_EMOJI["#CAKE#"]              = "<IMG LOCALSRC=\"239\" ALT=\"CAKE\">";
			$this->G_EMOJI["#SAKE#"]              = "<IMG LOCALSRC=\"400\" ALT=\"SAKE\">";
			$this->G_EMOJI["#BOWL#"]              = "<IMG LOCALSRC=\"333\" ALT=\"BOWL\">";
			$this->G_EMOJI["#PAN#"]               = "<IMG LOCALSRC=\"424\" ALT=\"PAN\">";
			$this->G_EMOJI["#SNAIL#"]             = "<IMG LOCALSRC=\"812\" ALT=\"SNAIL\">";
			$this->G_EMOJI["#BABY_BIRD#"]         = "<IMG LOCALSRC=\"78\" ALT=\"BABY_BIRD\">";
			$this->G_EMOJI["#PENGUIN#"]           = "<IMG LOCALSRC=\"252\" ALT=\"PENGUIN\">";
			$this->G_EMOJI["#FISH#"]              = "<IMG LOCALSRC=\"203\" ALT=\"FISH\">";
			$this->G_EMOJI["#FACE_DELICIOUS#"]    = "<IMG LOCALSRC=\"454\" ALT=\"FACE_DELICIOUS\">";
			$this->G_EMOJI["#FACE_FOPPISH#"]      = "<IMG LOCALSRC=\"814\" ALT=\"FACE_FOPPISH\">";
			$this->G_EMOJI["#HORSE#"]             = "<IMG LOCALSRC=\"248\" ALT=\"HORSE\">";
			$this->G_EMOJI["#PIG#"]               = "<IMG LOCALSRC=\"254\" ALT=\"PIG\">";
			$this->G_EMOJI["#WINE#"]              = "<IMG LOCALSRC=\"12\" ALT=\"WINE\">";
			$this->G_EMOJI["#FACE_LET_DOWN#"]     = "<IMG LOCALSRC=\"350\" ALT=\"FACE_LET_DOWN\">";
			$this->G_SUPPORT_IMAGE_EXT   = "GIF";
			$this->G_SUPPORT_CMDN_TYP    = 0;
			$SETTING["animation"]=false;
			break;
		case D_PC:
			if (!$D_OPEN_ACCESS) {		// add 2009/06/18 Y.Matsukawa
				$this->G_EMOJI["#SUN#"]               = "<IMG src=\"img/emoji_i_001.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CLOUD#"]             = "<IMG src=\"img/emoji_i_002.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RAIN#"]              = "<IMG src=\"img/emoji_i_003.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SNOW#"]              = "<IMG src=\"img/emoji_i_004.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#THUNDER#"]           = "<IMG src=\"img/emoji_i_005.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TYPHOON#"]           = "<IMG src=\"img/emoji_i_006.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FOG#"]               = "<IMG src=\"img/emoji_i_007.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#LIGHT_RAIN#"]        = "<IMG src=\"img/emoji_i_008.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RAM#"]               = "<IMG src=\"img/emoji_i_009.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BULL#"]              = "<IMG src=\"img/emoji_i_010.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TWINS#"]             = "<IMG src=\"img/emoji_i_011.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CRAB#"]              = "<IMG src=\"img/emoji_i_012.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#LION#"]              = "<IMG src=\"img/emoji_i_013.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#VIRGIN#"]            = "<IMG src=\"img/emoji_i_014.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BALANCE#"]           = "<IMG src=\"img/emoji_i_015.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SCORPION#"]          = "<IMG src=\"img/emoji_i_016.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ARCHER#"]            = "<IMG src=\"img/emoji_i_017.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GOAT#"]              = "<IMG src=\"img/emoji_i_018.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#WATER_BEARER#"]      = "<IMG src=\"img/emoji_i_019.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FISHES#"]            = "<IMG src=\"img/emoji_i_020.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SPORTS#"]            = "<IMG src=\"img/emoji_i_021.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BASEBALL#"]          = "<IMG src=\"img/emoji_i_022.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GOLF#"]              = "<IMG src=\"img/emoji_i_023.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TENNIS#"]            = "<IMG src=\"img/emoji_i_024.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SOCCER#"]            = "<IMG src=\"img/emoji_i_025.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SKI#"]               = "<IMG src=\"img/emoji_i_026.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BASKETBALL#"]        = "<IMG src=\"img/emoji_i_027.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FLAG#"]              = "<IMG src=\"img/emoji_i_028.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#POCKET_BELL#"]       = "<IMG src=\"img/emoji_i_029.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TRAIN#"]             = "<IMG src=\"img/emoji_i_030.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SUBWAY#"]            = "<IMG src=\"img/emoji_i_031.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHINKANSEN#"]        = "<IMG src=\"img/emoji_i_032.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CAR#"]               = "<IMG src=\"img/emoji_i_033.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CAR_2#"]             = "<IMG src=\"img/emoji_i_034.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BUS#"]               = "<IMG src=\"img/emoji_i_035.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHIP#"]              = "<IMG src=\"img/emoji_i_036.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#AIRPLANE#"]          = "<IMG src=\"img/emoji_i_037.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HOME#"]              = "<IMG src=\"img/emoji_i_038.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BUILD#"]             = "<IMG src=\"img/emoji_i_039.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#POST#"]              = "<IMG src=\"img/emoji_i_040.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HOSPITAL#"]          = "<IMG src=\"img/emoji_i_041.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BANK#"]              = "<IMG src=\"img/emoji_i_042.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ATM#"]               = "<IMG src=\"img/emoji_i_043.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HOTEL#"]             = "<IMG src=\"img/emoji_i_044.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CVS#"]               = "<IMG src=\"img/emoji_i_045.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GS#"]                = "<IMG src=\"img/emoji_i_046.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PARK#"]              = "<IMG src=\"img/emoji_i_047.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SIGNAL#"]            = "<IMG src=\"img/emoji_i_048.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TOILET#"]            = "<IMG src=\"img/emoji_i_049.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RESTAURANT#"]        = "<IMG src=\"img/emoji_i_050.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CAFE#"]              = "<IMG src=\"img/emoji_i_051.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BAR#"]               = "<IMG src=\"img/emoji_i_052.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BEER#"]              = "<IMG src=\"img/emoji_i_053.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BURGER#"]            = "<IMG src=\"img/emoji_i_054.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BOUTIQUE#"]          = "<IMG src=\"img/emoji_i_055.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BEAUTY_SALON#"]      = "<IMG src=\"img/emoji_i_056.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#KARAOKE#"]           = "<IMG src=\"img/emoji_i_057.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MOVIE#"]             = "<IMG src=\"img/emoji_i_058.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RIGHT_UP#"]          = "<IMG src=\"img/emoji_i_059.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#AMUSEMENT_PARK#"]    = "<IMG src=\"img/emoji_i_060.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MUSIC#"]             = "<IMG src=\"img/emoji_i_061.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ART#"]               = "<IMG src=\"img/emoji_i_062.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#DRAMA#"]             = "<IMG src=\"img/emoji_i_063.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#EVENT#"]             = "<IMG src=\"img/emoji_i_064.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TICKET#"]            = "<IMG src=\"img/emoji_i_065.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SMOKING#"]           = "<IMG src=\"img/emoji_i_066.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO_SMOKING#"]        = "<IMG src=\"img/emoji_i_067.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CAMERA#"]            = "<IMG src=\"img/emoji_i_068.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BAG#"]               = "<IMG src=\"img/emoji_i_069.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BOOK#"]              = "<IMG src=\"img/emoji_i_070.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RIBBON#"]            = "<IMG src=\"img/emoji_i_071.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PRESENT#"]           = "<IMG src=\"img/emoji_i_072.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BIRTHDAY#"]          = "<IMG src=\"img/emoji_i_073.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TEL#"]               = "<IMG src=\"img/emoji_i_074.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MOBILE#"]            = "<IMG src=\"img/emoji_i_075.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MEMO#"]              = "<IMG src=\"img/emoji_i_076.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TV#"]                = "<IMG src=\"img/emoji_i_077.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GAME#"]              = "<IMG src=\"img/emoji_i_078.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CD#"]                = "<IMG src=\"img/emoji_i_079.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HEART_TRUMP#"]       = "<IMG src=\"img/emoji_i_080.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SPADE#"]             = "<IMG src=\"img/emoji_i_081.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#DIAMOND#"]           = "<IMG src=\"img/emoji_i_082.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CLUBS#"]             = "<IMG src=\"img/emoji_i_083.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#EYE#"]               = "<IMG src=\"img/emoji_i_084.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#EAR#"]               = "<IMG src=\"img/emoji_i_085.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GOO#"]               = "<IMG src=\"img/emoji_i_086.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CHOKI#"]             = "<IMG src=\"img/emoji_i_087.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PAR#"]               = "<IMG src=\"img/emoji_i_088.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RIGHT_DOWN#"]        = "<IMG src=\"img/emoji_i_089.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#LEFT_UP#"]           = "<IMG src=\"img/emoji_i_090.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FOOT#"]              = "<IMG src=\"img/emoji_i_091.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHOES#"]             = "<IMG src=\"img/emoji_i_092.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GLASSES#"]           = "<IMG src=\"img/emoji_i_093.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#WHEELCHAIR#"]        = "<IMG src=\"img/emoji_i_094.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NEW_MOON#"]          = "<IMG src=\"img/emoji_i_095.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CHIP_MOON#"]         = "<IMG src=\"img/emoji_i_096.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HALF_MOON#"]         = "<IMG src=\"img/emoji_i_097.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CRESCENT_MOON#"]     = "<IMG src=\"img/emoji_i_098.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FULL_MOON#"]         = "<IMG src=\"img/emoji_i_099.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#DOG#"]               = "<IMG src=\"img/emoji_i_100.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CAT#"]               = "<IMG src=\"img/emoji_i_101.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RESORT#"]            = "<IMG src=\"img/emoji_i_102.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#XMAS#"]              = "<IMG src=\"img/emoji_i_103.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#LEFT_DOWN#"]         = "<IMG src=\"img/emoji_i_104.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PHONE_TO#"]          = "<IMG src=\"img/emoji_i_105.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MAIL_TO#"]           = "<IMG src=\"img/emoji_i_106.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FAX_TO#"]            = "<IMG src=\"img/emoji_i_107.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CARRIER#"]           = "<IMG src=\"img/emoji_i_108.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CARRIER_2#"]         = "<IMG src=\"img/emoji_i_109.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MAIL#"]              = "<IMG src=\"img/emoji_i_110.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#OFFER#"]             = "<IMG src=\"img/emoji_i_111.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#POINT#"]             = "<IMG src=\"img/emoji_i_112.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#YEN#"]               = "<IMG src=\"img/emoji_i_113.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FREE_YEN#"]          = "<IMG src=\"img/emoji_i_114.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ID#"]                = "<IMG src=\"img/emoji_i_115.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PASSWORD#"]          = "<IMG src=\"img/emoji_i_116.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#RETURN#"]            = "<IMG src=\"img/emoji_i_117.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CLEAR#"]             = "<IMG src=\"img/emoji_i_118.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SEARCH#"]            = "<IMG src=\"img/emoji_i_119.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NEW#"]               = "<IMG src=\"img/emoji_i_120.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ANTENNA#"]           = "<IMG src=\"img/emoji_i_121.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FREE#"]              = "<IMG src=\"img/emoji_i_122.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHARP_DIAL#"]        = "<IMG src=\"img/emoji_i_123.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MOB_Q#"]             = "<IMG src=\"img/emoji_i_124.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO1#"]               = "<IMG src=\"img/emoji_i_125.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO2#"]               = "<IMG src=\"img/emoji_i_126.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO3#"]               = "<IMG src=\"img/emoji_i_127.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO4#"]               = "<IMG src=\"img/emoji_i_128.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO5#"]               = "<IMG src=\"img/emoji_i_129.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO6#"]               = "<IMG src=\"img/emoji_i_130.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO7#"]               = "<IMG src=\"img/emoji_i_131.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO8#"]               = "<IMG src=\"img/emoji_i_132.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO9#"]               = "<IMG src=\"img/emoji_i_133.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NO0#"]               = "<IMG src=\"img/emoji_i_134.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#OK#"]                = "<IMG src=\"img/emoji_i_135.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HEART#"]             = "<IMG src=\"img/emoji_i_136.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HEART_WAVE#"]        = "<IMG src=\"img/emoji_i_137.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HEART_BREAK#"]       = "<IMG src=\"img/emoji_i_138.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HEARTS#"]            = "<IMG src=\"img/emoji_i_139.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FACE_SMILE#"]        = "<IMG src=\"img/emoji_i_140.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FACE_ANGRY#"]        = "<IMG src=\"img/emoji_i_141.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FACE_DEJECT#"]       = "<IMG src=\"img/emoji_i_142.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FACE_SAD#"]          = "<IMG src=\"img/emoji_i_143.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FACE_SWING#"]        = "<IMG src=\"img/emoji_i_144.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#GOOD#"]              = "<IMG src=\"img/emoji_i_145.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CHEERFUL#"]          = "<IMG src=\"img/emoji_i_146.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#FEEL_GOOD#"]         = "<IMG src=\"img/emoji_i_147.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CUTE#"]              = "<IMG src=\"img/emoji_i_148.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#KISS#"]              = "<IMG src=\"img/emoji_i_149.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHINE#"]             = "<IMG src=\"img/emoji_i_150.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#HINT#"]              = "<IMG src=\"img/emoji_i_151.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ANGER#"]             = "<IMG src=\"img/emoji_i_152.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PUNCH#"]             = "<IMG src=\"img/emoji_i_153.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#BOMB#"]              = "<IMG src=\"img/emoji_i_154.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#MOOD#"]              = "<IMG src=\"img/emoji_i_155.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#DOWN#"]              = "<IMG src=\"img/emoji_i_156.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SLEEP#"]             = "<IMG src=\"img/emoji_i_157.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#EXC#"]               = "<IMG src=\"img/emoji_i_158.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#QUESTION#"]          = "<IMG src=\"img/emoji_i_159.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#EXC_2#"]             = "<IMG src=\"img/emoji_i_160.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHOCK#"]             = "<IMG src=\"img/emoji_i_161.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SWEAT#"]             = "<IMG src=\"img/emoji_i_162.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SWEAT_2#"]           = "<IMG src=\"img/emoji_i_163.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#DASH#"]              = "<IMG src=\"img/emoji_i_164.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#LONG_VOWEL#"]        = "<IMG src=\"img/emoji_i_165.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#LONG_VOWEL_2#"]      = "<IMG src=\"img/emoji_i_166.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#KACHINKO#"]          = "<IMG src=\"img/emoji_i_167.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#POUCH#"]             = "<IMG src=\"img/emoji_i_168.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#PEN#"]               = "<IMG src=\"img/emoji_i_169.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SHADOW#"]            = "<IMG src=\"img/emoji_i_170.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#CHAIR#"]             = "<IMG src=\"img/emoji_i_171.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#NIGHT#"]             = "<IMG src=\"img/emoji_i_172.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#SOON#"]              = "<IMG src=\"img/emoji_i_173.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#ON#"]                = "<IMG src=\"img/emoji_i_174.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#END#"]               = "<IMG src=\"img/emoji_i_175.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#TIME#"]              = "<IMG src=\"img/emoji_i_176.gif\" width=16 height=16 border=0>";
				$this->G_EMOJI["#APPLI#"]             = "";
				$this->G_EMOJI["#APPLI_2#"]           = "";
				$this->G_EMOJI["#SHIRTS#"]            = "";
				$this->G_EMOJI["#WALLET#"]            = "";
				$this->G_EMOJI["#MAKEUP#"]            = "";
				$this->G_EMOJI["#JEANS#"]             = "";
				$this->G_EMOJI["#SNOW_BOARD#"]        = "";
				$this->G_EMOJI["#CHAPEL#"]            = "";
				$this->G_EMOJI["#DOOR#"]              = "";
				$this->G_EMOJI["#DOLLAR#"]            = "";
				$this->G_EMOJI["#PC#"]                = "";
				$this->G_EMOJI["#LOVE_LETTER#"]       = "";
				$this->G_EMOJI["#WRENCH#"]            = "";
				$this->G_EMOJI["#PENCIL#"]            = "";
				$this->G_EMOJI["#CROWN#"]             = "";
				$this->G_EMOJI["#RING#"]              = "";
				$this->G_EMOJI["#SANDGLASS#"]         = "";
				$this->G_EMOJI["#BICYCLE#"]           = "";
				$this->G_EMOJI["#TEACUP#"]            = "";
				$this->G_EMOJI["#WATCH#"]             = "";
				$this->G_EMOJI["#FACE_THINK#"]        = "";
				$this->G_EMOJI["#FACE_PEACE#"]        = "";
				$this->G_EMOJI["#FACE_HURRY#"]        = "";
				$this->G_EMOJI["#FACE_HURRY_2#"]      = "";
				$this->G_EMOJI["#FACE_ANGRY_2#"]      = "";
				$this->G_EMOJI["#FACE_POKER#"]        = "";
				$this->G_EMOJI["#FACE_HEART#"]        = "";
				$this->G_EMOJI["#FINGER#"]            = "";
				$this->G_EMOJI["#FACE_JOKE#"]         = "";
				$this->G_EMOJI["#FACE_WINK#"]         = "";
				$this->G_EMOJI["#FACE_HAPPY#"]        = "";
				$this->G_EMOJI["#FACE_PATIENCE#"]     = "";
				$this->G_EMOJI["#CAT_2#"]             = "";
				$this->G_EMOJI["#FACE_CRY#"]          = "";
				$this->G_EMOJI["#TEAR#"]              = "";
				$this->G_EMOJI["#NG#"]                = "";
				$this->G_EMOJI["#CLIP#"]              = "";
				$this->G_EMOJI["#COPYRIGHT#"]         = "";
				$this->G_EMOJI["#TM#"]                = "";
				$this->G_EMOJI["#RUNNER#"]            = "";
				$this->G_EMOJI["#SECRET#"]            = "";
				$this->G_EMOJI["#RECYCLING#"]         = "";
				$this->G_EMOJI["#REGIST#"]            = "";
				$this->G_EMOJI["#WARNING#"]           = "";
				$this->G_EMOJI["#PROHIBITION#"]       = "";
				$this->G_EMOJI["#EMPTY#"]             = "";
				$this->G_EMOJI["#SUCCESS#"]           = "";
				$this->G_EMOJI["#FULL#"]              = "";
				$this->G_EMOJI["#RIGHT_LEFT#"]        = "";
				$this->G_EMOJI["#UP_DOWN#"]           = "";
				$this->G_EMOJI["#SCHOOL#"]            = "";
				$this->G_EMOJI["#WAVE#"]              = "";
				$this->G_EMOJI["#MOUNTAIN#"]          = "";
				$this->G_EMOJI["#CLOVER#"]            = "";
				$this->G_EMOJI["#CHERRY#"]            = "";
				$this->G_EMOJI["#TULIP#"]             = "";
				$this->G_EMOJI["#BANANA#"]            = "";
				$this->G_EMOJI["#APPLE#"]             = "";
				$this->G_EMOJI["#LEAF#"]              = "";
				$this->G_EMOJI["#MAPLE#"]             = "";
				$this->G_EMOJI["#CHERRY_BLOSSOM#"]    = "";
				$this->G_EMOJI["#RICE_BALL#"]         = "";
				$this->G_EMOJI["#CAKE#"]              = "";
				$this->G_EMOJI["#SAKE#"]              = "";
				$this->G_EMOJI["#BOWL#"]              = "";
				$this->G_EMOJI["#PAN#"]               = "";
				$this->G_EMOJI["#SNAIL#"]             = "";
				$this->G_EMOJI["#BABY_BIRD#"]         = "";
				$this->G_EMOJI["#PENGUIN#"]           = "";
				$this->G_EMOJI["#FISH#"]              = "";
				$this->G_EMOJI["#FACE_DELICIOUS#"]    = "";
				$this->G_EMOJI["#FACE_FOPPISH#"]      = "";
				$this->G_EMOJI["#HORSE#"]             = "";
				$this->G_EMOJI["#PIG#"]               = "";
				$this->G_EMOJI["#WINE#"]              = "";
				$this->G_EMOJI["#FACE_LET_DOWN#"]     = "";
			// add 2009/06/18 Y.Matsukawa [
			} else {
				$this->G_EMOJI["#SUN#"]               = "";
				$this->G_EMOJI["#CLOUD#"]             = "";
				$this->G_EMOJI["#RAIN#"]              = "";
				$this->G_EMOJI["#SNOW#"]              = "";
				$this->G_EMOJI["#THUNDER#"]           = "";
				$this->G_EMOJI["#TYPHOON#"]           = "";
				$this->G_EMOJI["#FOG#"]               = "";
				$this->G_EMOJI["#LIGHT_RAIN#"]        = "";
				$this->G_EMOJI["#RAM#"]               = "";
				$this->G_EMOJI["#BULL#"]              = "";
				$this->G_EMOJI["#TWINS#"]             = "";
				$this->G_EMOJI["#CRAB#"]              = "";
				$this->G_EMOJI["#LION#"]              = "";
				$this->G_EMOJI["#VIRGIN#"]            = "";
				$this->G_EMOJI["#BALANCE#"]           = "";
				$this->G_EMOJI["#SCORPION#"]          = "";
				$this->G_EMOJI["#ARCHER#"]            = "";
				$this->G_EMOJI["#GOAT#"]              = "";
				$this->G_EMOJI["#WATER_BEARER#"]      = "";
				$this->G_EMOJI["#FISHES#"]            = "";
				$this->G_EMOJI["#SPORTS#"]            = "";
				$this->G_EMOJI["#BASEBALL#"]          = "";
				$this->G_EMOJI["#GOLF#"]              = "";
				$this->G_EMOJI["#TENNIS#"]            = "";
				$this->G_EMOJI["#SOCCER#"]            = "";
				$this->G_EMOJI["#SKI#"]               = "";
				$this->G_EMOJI["#BASKETBALL#"]        = "";
				$this->G_EMOJI["#FLAG#"]              = "";
				$this->G_EMOJI["#POCKET_BELL#"]       = "";
				$this->G_EMOJI["#TRAIN#"]             = "";
				$this->G_EMOJI["#SUBWAY#"]            = "";
				$this->G_EMOJI["#SHINKANSEN#"]        = "";
				$this->G_EMOJI["#CAR#"]               = "";
				$this->G_EMOJI["#CAR_2#"]             = "";
				$this->G_EMOJI["#BUS#"]               = "";
				$this->G_EMOJI["#SHIP#"]              = "";
				$this->G_EMOJI["#AIRPLANE#"]          = "";
				$this->G_EMOJI["#HOME#"]              = "";
				$this->G_EMOJI["#BUILD#"]             = "";
				$this->G_EMOJI["#POST#"]              = "";
				$this->G_EMOJI["#HOSPITAL#"]          = "";
				$this->G_EMOJI["#BANK#"]              = "";
				$this->G_EMOJI["#ATM#"]               = "";
				$this->G_EMOJI["#HOTEL#"]             = "";
				$this->G_EMOJI["#CVS#"]               = "";
				$this->G_EMOJI["#GS#"]                = "";
				$this->G_EMOJI["#PARK#"]              = "";
				$this->G_EMOJI["#SIGNAL#"]            = "";
				$this->G_EMOJI["#TOILET#"]            = "";
				$this->G_EMOJI["#RESTAURANT#"]        = "";
				$this->G_EMOJI["#CAFE#"]              = "";
				$this->G_EMOJI["#BAR#"]               = "";
				$this->G_EMOJI["#BEER#"]              = "";
				$this->G_EMOJI["#BURGER#"]            = "";
				$this->G_EMOJI["#BOUTIQUE#"]          = "";
				$this->G_EMOJI["#BEAUTY_SALON#"]      = "";
				$this->G_EMOJI["#KARAOKE#"]           = "";
				$this->G_EMOJI["#MOVIE#"]             = "";
				$this->G_EMOJI["#RIGHT_UP#"]          = "";
				$this->G_EMOJI["#AMUSEMENT_PARK#"]    = "";
				$this->G_EMOJI["#MUSIC#"]             = "";
				$this->G_EMOJI["#ART#"]               = "";
				$this->G_EMOJI["#DRAMA#"]             = "";
				$this->G_EMOJI["#EVENT#"]             = "";
				$this->G_EMOJI["#TICKET#"]            = "";
				$this->G_EMOJI["#SMOKING#"]           = "";
				$this->G_EMOJI["#NO_SMOKING#"]        = "";
				$this->G_EMOJI["#CAMERA#"]            = "";
				$this->G_EMOJI["#BAG#"]               = "";
				$this->G_EMOJI["#BOOK#"]              = "";
				$this->G_EMOJI["#RIBBON#"]            = "";
				$this->G_EMOJI["#PRESENT#"]           = "";
				$this->G_EMOJI["#BIRTHDAY#"]          = "";
				$this->G_EMOJI["#TEL#"]               = "";
				$this->G_EMOJI["#MOBILE#"]            = "";
				$this->G_EMOJI["#MEMO#"]              = "";
				$this->G_EMOJI["#TV#"]                = "";
				$this->G_EMOJI["#GAME#"]              = "";
				$this->G_EMOJI["#CD#"]                = "";
				$this->G_EMOJI["#HEART_TRUMP#"]       = "";
				$this->G_EMOJI["#SPADE#"]             = "";
				$this->G_EMOJI["#DIAMOND#"]           = "";
				$this->G_EMOJI["#CLUBS#"]             = "";
				$this->G_EMOJI["#EYE#"]               = "";
				$this->G_EMOJI["#EAR#"]               = "";
				$this->G_EMOJI["#GOO#"]               = "";
				$this->G_EMOJI["#CHOKI#"]             = "";
				$this->G_EMOJI["#PAR#"]               = "";
				$this->G_EMOJI["#RIGHT_DOWN#"]        = "";
				$this->G_EMOJI["#LEFT_UP#"]           = "";
				$this->G_EMOJI["#FOOT#"]              = "";
				$this->G_EMOJI["#SHOES#"]             = "";
				$this->G_EMOJI["#GLASSES#"]           = "";
				$this->G_EMOJI["#WHEELCHAIR#"]        = "";
				$this->G_EMOJI["#NEW_MOON#"]          = "";
				$this->G_EMOJI["#CHIP_MOON#"]         = "";
				$this->G_EMOJI["#HALF_MOON#"]         = "";
				$this->G_EMOJI["#CRESCENT_MOON#"]     = "";
				$this->G_EMOJI["#FULL_MOON#"]         = "";
				$this->G_EMOJI["#DOG#"]               = "";
				$this->G_EMOJI["#CAT#"]               = "";
				$this->G_EMOJI["#RESORT#"]            = "";
				$this->G_EMOJI["#XMAS#"]              = "";
				$this->G_EMOJI["#LEFT_DOWN#"]         = "";
				$this->G_EMOJI["#PHONE_TO#"]          = "";
				$this->G_EMOJI["#MAIL_TO#"]           = "";
				$this->G_EMOJI["#FAX_TO#"]            = "";
				$this->G_EMOJI["#CARRIER#"]           = "";
				$this->G_EMOJI["#CARRIER_2#"]         = "";
				$this->G_EMOJI["#MAIL#"]              = "";
				$this->G_EMOJI["#OFFER#"]             = "";
				$this->G_EMOJI["#POINT#"]             = "";
				$this->G_EMOJI["#YEN#"]               = "";
				$this->G_EMOJI["#FREE_YEN#"]          = "";
				$this->G_EMOJI["#ID#"]                = "";
				$this->G_EMOJI["#PASSWORD#"]          = "";
				$this->G_EMOJI["#RETURN#"]            = "";
				$this->G_EMOJI["#CLEAR#"]             = "";
				$this->G_EMOJI["#SEARCH#"]            = "";
				$this->G_EMOJI["#NEW#"]               = "";
				$this->G_EMOJI["#ANTENNA#"]           = "";
				$this->G_EMOJI["#FREE#"]              = "";
				$this->G_EMOJI["#SHARP_DIAL#"]        = "";
				$this->G_EMOJI["#MOB_Q#"]             = "";
				$this->G_EMOJI["#NO1#"]               = "・";
				$this->G_EMOJI["#NO2#"]               = "・";
				$this->G_EMOJI["#NO3#"]               = "・";
				$this->G_EMOJI["#NO4#"]               = "・";
				$this->G_EMOJI["#NO5#"]               = "・";
				$this->G_EMOJI["#NO6#"]               = "・";
				$this->G_EMOJI["#NO7#"]               = "・";
				$this->G_EMOJI["#NO8#"]               = "・";
				$this->G_EMOJI["#NO9#"]               = "・";
				$this->G_EMOJI["#NO0#"]               = "・";
				$this->G_EMOJI["#OK#"]                = "";
				$this->G_EMOJI["#HEART#"]             = "";
				$this->G_EMOJI["#HEART_WAVE#"]        = "";
				$this->G_EMOJI["#HEART_BREAK#"]       = "";
				$this->G_EMOJI["#HEARTS#"]            = "";
				$this->G_EMOJI["#FACE_SMILE#"]        = "";
				$this->G_EMOJI["#FACE_ANGRY#"]        = "";
				$this->G_EMOJI["#FACE_DEJECT#"]       = "";
				$this->G_EMOJI["#FACE_SAD#"]          = "";
				$this->G_EMOJI["#FACE_SWING#"]        = "";
				$this->G_EMOJI["#GOOD#"]              = "";
				$this->G_EMOJI["#CHEERFUL#"]          = "";
				$this->G_EMOJI["#FEEL_GOOD#"]         = "";
				$this->G_EMOJI["#CUTE#"]              = "";
				$this->G_EMOJI["#KISS#"]              = "";
				$this->G_EMOJI["#SHINE#"]             = "";
				$this->G_EMOJI["#HINT#"]              = "";
				$this->G_EMOJI["#ANGER#"]             = "";
				$this->G_EMOJI["#PUNCH#"]             = "";
				$this->G_EMOJI["#BOMB#"]              = "";
				$this->G_EMOJI["#MOOD#"]              = "";
				$this->G_EMOJI["#DOWN#"]              = "";
				$this->G_EMOJI["#SLEEP#"]             = "";
				$this->G_EMOJI["#EXC#"]               = "";
				$this->G_EMOJI["#QUESTION#"]          = "";
				$this->G_EMOJI["#EXC_2#"]             = "";
				$this->G_EMOJI["#SHOCK#"]             = "";
				$this->G_EMOJI["#SWEAT#"]             = "";
				$this->G_EMOJI["#SWEAT_2#"]           = "";
				$this->G_EMOJI["#DASH#"]              = "";
				$this->G_EMOJI["#LONG_VOWEL#"]        = "";
				$this->G_EMOJI["#LONG_VOWEL_2#"]      = "";
				$this->G_EMOJI["#KACHINKO#"]          = "";
				$this->G_EMOJI["#POUCH#"]             = "";
				$this->G_EMOJI["#PEN#"]               = "";
				$this->G_EMOJI["#SHADOW#"]            = "";
				$this->G_EMOJI["#CHAIR#"]             = "";
				$this->G_EMOJI["#NIGHT#"]             = "";
				$this->G_EMOJI["#SOON#"]              = "";
				$this->G_EMOJI["#ON#"]                = "";
				$this->G_EMOJI["#END#"]               = "";
				$this->G_EMOJI["#TIME#"]              = "";
				$this->G_EMOJI["#APPLI#"]             = "";
				$this->G_EMOJI["#APPLI_2#"]           = "";
				$this->G_EMOJI["#SHIRTS#"]            = "";
				$this->G_EMOJI["#WALLET#"]            = "";
				$this->G_EMOJI["#MAKEUP#"]            = "";
				$this->G_EMOJI["#JEANS#"]             = "";
				$this->G_EMOJI["#SNOW_BOARD#"]        = "";
				$this->G_EMOJI["#CHAPEL#"]            = "";
				$this->G_EMOJI["#DOOR#"]              = "";
				$this->G_EMOJI["#DOLLAR#"]            = "";
				$this->G_EMOJI["#PC#"]                = "";
				$this->G_EMOJI["#LOVE_LETTER#"]       = "";
				$this->G_EMOJI["#WRENCH#"]            = "";
				$this->G_EMOJI["#PENCIL#"]            = "";
				$this->G_EMOJI["#CROWN#"]             = "";
				$this->G_EMOJI["#RING#"]              = "";
				$this->G_EMOJI["#SANDGLASS#"]         = "";
				$this->G_EMOJI["#BICYCLE#"]           = "";
				$this->G_EMOJI["#TEACUP#"]            = "";
				$this->G_EMOJI["#WATCH#"]             = "";
				$this->G_EMOJI["#FACE_THINK#"]        = "";
				$this->G_EMOJI["#FACE_PEACE#"]        = "";
				$this->G_EMOJI["#FACE_HURRY#"]        = "";
				$this->G_EMOJI["#FACE_HURRY_2#"]      = "";
				$this->G_EMOJI["#FACE_ANGRY_2#"]      = "";
				$this->G_EMOJI["#FACE_POKER#"]        = "";
				$this->G_EMOJI["#FACE_HEART#"]        = "";
				$this->G_EMOJI["#FINGER#"]            = "";
				$this->G_EMOJI["#FACE_JOKE#"]         = "";
				$this->G_EMOJI["#FACE_WINK#"]         = "";
				$this->G_EMOJI["#FACE_HAPPY#"]        = "";
				$this->G_EMOJI["#FACE_PATIENCE#"]     = "";
				$this->G_EMOJI["#CAT_2#"]             = "";
				$this->G_EMOJI["#FACE_CRY#"]          = "";
				$this->G_EMOJI["#TEAR#"]              = "";
				$this->G_EMOJI["#NG#"]                = "";
				$this->G_EMOJI["#CLIP#"]              = "";
				$this->G_EMOJI["#COPYRIGHT#"]         = "";
				$this->G_EMOJI["#TM#"]                = "";
				$this->G_EMOJI["#RUNNER#"]            = "";
				$this->G_EMOJI["#SECRET#"]            = "";
				$this->G_EMOJI["#RECYCLING#"]         = "";
				$this->G_EMOJI["#REGIST#"]            = "";
				$this->G_EMOJI["#WARNING#"]           = "";
				$this->G_EMOJI["#PROHIBITION#"]       = "";
				$this->G_EMOJI["#EMPTY#"]             = "";
				$this->G_EMOJI["#SUCCESS#"]           = "";
				$this->G_EMOJI["#FULL#"]              = "";
				$this->G_EMOJI["#RIGHT_LEFT#"]        = "";
				$this->G_EMOJI["#UP_DOWN#"]           = "";
				$this->G_EMOJI["#SCHOOL#"]            = "";
				$this->G_EMOJI["#WAVE#"]              = "";
				$this->G_EMOJI["#MOUNTAIN#"]          = "";
				$this->G_EMOJI["#CLOVER#"]            = "";
				$this->G_EMOJI["#CHERRY#"]            = "";
				$this->G_EMOJI["#TULIP#"]             = "";
				$this->G_EMOJI["#BANANA#"]            = "";
				$this->G_EMOJI["#APPLE#"]             = "";
				$this->G_EMOJI["#LEAF#"]              = "";
				$this->G_EMOJI["#MAPLE#"]             = "";
				$this->G_EMOJI["#CHERRY_BLOSSOM#"]    = "";
				$this->G_EMOJI["#RICE_BALL#"]         = "";
				$this->G_EMOJI["#CAKE#"]              = "";
				$this->G_EMOJI["#SAKE#"]              = "";
				$this->G_EMOJI["#BOWL#"]              = "";
				$this->G_EMOJI["#PAN#"]               = "";
				$this->G_EMOJI["#SNAIL#"]             = "";
				$this->G_EMOJI["#BABY_BIRD#"]         = "";
				$this->G_EMOJI["#PENGUIN#"]           = "";
				$this->G_EMOJI["#FISH#"]              = "";
				$this->G_EMOJI["#FACE_DELICIOUS#"]    = "";
				$this->G_EMOJI["#FACE_FOPPISH#"]      = "";
				$this->G_EMOJI["#HORSE#"]             = "";
				$this->G_EMOJI["#PIG#"]               = "";
				$this->G_EMOJI["#WINE#"]              = "";
				$this->G_EMOJI["#FACE_LET_DOWN#"]     = "";
			}
			// add 2009/06/18 Y.Matsukawa ]
			$this->G_SUPPORT_IMAGE_EXT   = "PNG";
			$this->G_SUPPORT_CMDN_TYP    = 1;
			break;
		case D_HDML:
			$this->G_EMOJI["#SUN#"]               = "<IMG ICON=\"44\" ALT=\"SUN\">";
			$this->G_EMOJI["#CLOUD#"]             = "<IMG ICON=\"107\" ALT=\"CLOUD\">";
			$this->G_EMOJI["#RAIN#"]              = "<IMG ICON=\"95\" ALT=\"RAIN\">";
			$this->G_EMOJI["#SNOW#"]              = "<IMG ICON=\"191\" ALT=\"SNOW\">";
			$this->G_EMOJI["#THUNDER#"]           = "<IMG ICON=\"16\" ALT=\"THUNDER\">";
			$this->G_EMOJI["#TYPHOON#"]           = "<IMG ICON=\"190\" ALT=\"TYPHOON\">";
			$this->G_EMOJI["#FOG#"]               = "<IMG ICON=\"305\" ALT=\"FOG\">";
			$this->G_EMOJI["#LIGHT_RAIN#"]        = "<IMG ICON=\"481\" ALT=\"LIGHT_RAIN\">";
			$this->G_EMOJI["#RAM#"]               = "<IMG ICON=\"192\" ALT=\"RAM\">";
			$this->G_EMOJI["#BULL#"]              = "<IMG ICON=\"193\" ALT=\"BULL\">";
			$this->G_EMOJI["#TWINS#"]             = "<IMG ICON=\"194\" ALT=\"TWINS\">";
			$this->G_EMOJI["#CRAB#"]              = "<IMG ICON=\"195\" ALT=\"CRAB\">";
			$this->G_EMOJI["#LION#"]              = "<IMG ICON=\"196\" ALT=\"LION\">";
			$this->G_EMOJI["#VIRGIN#"]            = "<IMG ICON=\"197\" ALT=\"VIRGIN\">";
			$this->G_EMOJI["#BALANCE#"]           = "<IMG ICON=\"198\" ALT=\"BALANCE\">";
			$this->G_EMOJI["#SCORPION#"]          = "<IMG ICON=\"199\" ALT=\"SCORPION\">";
			$this->G_EMOJI["#ARCHER#"]            = "<IMG ICON=\"200\" ALT=\"ARCHER\">";
			$this->G_EMOJI["#GOAT#"]              = "<IMG ICON=\"201\" ALT=\"GOAT\">";
			$this->G_EMOJI["#WATER_BEARER#"]      = "<IMG ICON=\"202\" ALT=\"WATER_BEARER\">";
			$this->G_EMOJI["#FISHES#"]            = "<IMG ICON=\"203\" ALT=\"FISHES\">";
			$this->G_EMOJI["#SPORTS#"]            = "<IMG ICON=\"218\" ALT=\"SPORTS\">";
			$this->G_EMOJI["#BASEBALL#"]          = "<IMG ICON=\"45\" ALT=\"BASEBALL\">";
			$this->G_EMOJI["#GOLF#"]              = "<IMG ICON=\"306\" ALT=\"GOLF\">";
			$this->G_EMOJI["#TENNIS#"]            = "<IMG ICON=\"220\" ALT=\"TENNIS\">";
			$this->G_EMOJI["#SOCCER#"]            = "<IMG ICON=\"219\" ALT=\"SOCCER\">";
			$this->G_EMOJI["#SKI#"]               = "<IMG ICON=\"421\" ALT=\"SKI\">";
			$this->G_EMOJI["#BASKETBALL#"]        = "<IMG ICON=\"307\" ALT=\"BASKETBALL\">";
			$this->G_EMOJI["#FLAG#"]              = "<IMG ICON=\"222\" ALT=\"FLAG\">";
			$this->G_EMOJI["#POCKET_BELL#"]       = "<IMG ICON=\"308\" ALT=\"POCKET_BELL\">";
			$this->G_EMOJI["#TRAIN#"]             = "<IMG ICON=\"172\" ALT=\"TRAIN\">";
			$this->G_EMOJI["#SUBWAY#"]            = "<IMG ICON=\"341\" ALT=\"SUBWAY\">";
			$this->G_EMOJI["#SHINKANSEN#"]        = "<IMG ICON=\"217\" ALT=\"SHINKANSEN\">";
			$this->G_EMOJI["#CAR#"]               = "<IMG ICON=\"125\" ALT=\"CAR\">";
			$this->G_EMOJI["#CAR_2#"]             = "<IMG ICON=\"125\" ALT=\"CAR_2\">";
			$this->G_EMOJI["#BUS#"]               = "<IMG ICON=\"216\" ALT=\"BUS\">";
			$this->G_EMOJI["#SHIP#"]              = "<IMG ICON=\"379\" ALT=\"SHIP\">";
			$this->G_EMOJI["#AIRPLANE#"]          = "<IMG ICON=\"168\" ALT=\"AIRPLANE\">";
			$this->G_EMOJI["#HOME#"]              = "<IMG ICON=\"112\" ALT=\"HOME\">";
			$this->G_EMOJI["#BUILD#"]             = "<IMG ICON=\"156\" ALT=\"BUILD\">";
			$this->G_EMOJI["#POST#"]              = "<IMG ICON=\"375\" ALT=\"POST\">";
			$this->G_EMOJI["#HOSPITAL#"]          = "<IMG ICON=\"376\" ALT=\"HOSPITAL\">";
			$this->G_EMOJI["#BANK#"]              = "<IMG ICON=\"212\" ALT=\"BANK\">";
			$this->G_EMOJI["#ATM#"]               = "<IMG ICON=\"205\" ALT=\"ATM\">";
			$this->G_EMOJI["#HOTEL#"]             = "<IMG ICON=\"378\" ALT=\"HOTEL\">";
			$this->G_EMOJI["#CVS#"]               = "<IMG ICON=\"206\" ALT=\"CVS\">";
			$this->G_EMOJI["#GS#"]                = "<IMG ICON=\"213\" ALT=\"GS\">";
			$this->G_EMOJI["#PARK#"]              = "<IMG ICON=\"208\" ALT=\"PARK\">";
			$this->G_EMOJI["#SIGNAL#"]            = "<IMG ICON=\"99\" ALT=\"SIGNAL\">";
			$this->G_EMOJI["#TOILET#"]            = "<IMG ICON=\"207\" ALT=\"TOILET\">";
			$this->G_EMOJI["#RESTAURANT#"]        = "<IMG ICON=\"146\" ALT=\"RESTAURANT\">";
			$this->G_EMOJI["#CAFE#"]              = "<IMG ICON=\"93\" ALT=\"CAFE\">";
			$this->G_EMOJI["#BAR#"]               = "<IMG ICON=\"52\" ALT=\"BAR\">";
			$this->G_EMOJI["#BEER#"]              = "<IMG ICON=\"65\" ALT=\"BEER\">";
			$this->G_EMOJI["#BURGER#"]            = "<IMG ICON=\"245\" ALT=\"BURGER\">";
			$this->G_EMOJI["#BOUTIQUE#"]          = "<IMG ICON=\"124\" ALT=\"BOUTIQUE\">";
			$this->G_EMOJI["#BEAUTY_SALON#"]      = "<IMG ICON=\"104\" ALT=\"BEAUTY_SALON\">";
			$this->G_EMOJI["#KARAOKE#"]           = "<IMG ICON=\"289\" ALT=\"KARAOKE\">";
			$this->G_EMOJI["#MOVIE#"]             = "<IMG ICON=\"110\" ALT=\"MOVIE\">";
			$this->G_EMOJI["#RIGHT_UP#"]          = "<IMG ICON=\"70\" ALT=\"RIGHT_UP\">";
			$this->G_EMOJI["#AMUSEMENT_PARK#"]    = "<IMG ICON=\"223\" ALT=\"AMUSEMENT_PARK\">";
			$this->G_EMOJI["#MUSIC#"]             = "<IMG ICON=\"294\" ALT=\"MUSIC\">";
			$this->G_EMOJI["#ART#"]               = "<IMG ICON=\"309\" ALT=\"ART\">";
			$this->G_EMOJI["#DRAMA#"]             = "<IMG ICON=\"494\" ALT=\"DRAMA\">";
			$this->G_EMOJI["#EVENT#"]             = "<IMG ICON=\"311\" ALT=\"EVENT\">";
			$this->G_EMOJI["#TICKET#"]            = "<IMG ICON=\"106\" ALT=\"TICKET\">";
			$this->G_EMOJI["#SMOKING#"]           = "<IMG ICON=\"176\" ALT=\"SMOKING\">";
			$this->G_EMOJI["#NO_SMOKING#"]        = "<IMG ICON=\"177\" ALT=\"NO_SMOKING\">";
			$this->G_EMOJI["#CAMERA#"]            = "<IMG ICON=\"94\" ALT=\"CAMERA\">";
			$this->G_EMOJI["#BAG#"]               = "<IMG ICON=\"83\" ALT=\"BAG\">";
			$this->G_EMOJI["#BOOK#"]              = "<IMG ICON=\"122\" ALT=\"BOOK\">";
			$this->G_EMOJI["#RIBBON#"]            = "<IMG ICON=\"312\" ALT=\"RIBBON\">";
			$this->G_EMOJI["#PRESENT#"]           = "<IMG ICON=\"144\" ALT=\"PRESENT\">";
			$this->G_EMOJI["#BIRTHDAY#"]          = "<IMG ICON=\"313\" ALT=\"BIRTHDAY\">";
			$this->G_EMOJI["#TEL#"]               = "<IMG ICON=\"85\" ALT=\"TEL\">";
			$this->G_EMOJI["#MOBILE#"]            = "<IMG ICON=\"161\" ALT=\"MOBILE\">";
			$this->G_EMOJI["#MEMO#"]              = "<IMG ICON=\"56\" ALT=\"MEMO\">";
			$this->G_EMOJI["#TV#"]                = "<IMG ICON=\"288\" ALT=\"TV\">";
			$this->G_EMOJI["#GAME#"]              = "<IMG ICON=\"232\" ALT=\"GAME\">";
			$this->G_EMOJI["#CD#"]                = "<IMG ICON=\"300\" ALT=\"CD\">";
			$this->G_EMOJI["#HEART_TRUMP#"]       = "<IMG ICON=\"414\" ALT=\"HEART_TRUMP\">";
			$this->G_EMOJI["#SPADE#"]             = "<IMG ICON=\"314\" ALT=\"SPADE\">";
			$this->G_EMOJI["#DIAMOND#"]           = "<IMG ICON=\"315\" ALT=\"DIAMOND\">";
			$this->G_EMOJI["#CLUBS#"]             = "<IMG ICON=\"316\" ALT=\"CLUBS\">";
			$this->G_EMOJI["#EYE#"]               = "<IMG ICON=\"317\" ALT=\"EYE\">";
			$this->G_EMOJI["#EAR#"]               = "<IMG ICON=\"318\" ALT=\"EAR\">";
			$this->G_EMOJI["#GOO#"]               = "<IMG ICON=\"817\" ALT=\"GOO\">";
			$this->G_EMOJI["#CHOKI#"]             = "<IMG ICON=\"319\" ALT=\"CHOKI\">";
			$this->G_EMOJI["#PAR#"]               = "<IMG ICON=\"320\" ALT=\"PAR\">";
			$this->G_EMOJI["#RIGHT_DOWN#"]        = "<IMG ICON=\"43\" ALT=\"RIGHT_DOWN\">";
			$this->G_EMOJI["#LEFT_UP#"]           = "<IMG ICON=\"42\" ALT=\"LEFT_UP\">";
			$this->G_EMOJI["#FOOT#"]              = "<IMG ICON=\"728\" ALT=\"FOOT\">";
			$this->G_EMOJI["#SHOES#"]             = "<IMG ICON=\"336\" ALT=\"SHOES\">";
			$this->G_EMOJI["#GLASSES#"]           = "<IMG ICON=\"116\" ALT=\"GLASSES\">";
			$this->G_EMOJI["#WHEELCHAIR#"]        = "<IMG ICON=\"178\" ALT=\"WHEELCHAIR\">";
			$this->G_EMOJI["#NEW_MOON#"]          = "<IMG ICON=\"321\" ALT=\"NEW_MOON\">";
			$this->G_EMOJI["#CHIP_MOON#"]         = "<IMG ICON=\"322\" ALT=\"CHIP_MOON\">";
			$this->G_EMOJI["#HALF_MOON#"]         = "<IMG ICON=\"323\" ALT=\"HALF_MOON\">";
			$this->G_EMOJI["#CRESCENT_MOON#"]     = "<IMG ICON=\"15\" ALT=\"CRESCENT_MOON\">";
			$this->G_EMOJI["#FULL_MOON#"]         = "<IMG ICON=\"47\" ALT=\"FULL_MOON\">";
			$this->G_EMOJI["#DOG#"]               = "<IMG ICON=\"134\" ALT=\"DOG\">";
			$this->G_EMOJI["#CAT#"]               = "<IMG ICON=\"251\" ALT=\"CAT\">";
			$this->G_EMOJI["#RESORT#"]            = "<IMG ICON=\"169\" ALT=\"RESORT\">";
			$this->G_EMOJI["#XMAS#"]              = "<IMG ICON=\"234\" ALT=\"XMAS\">";
			$this->G_EMOJI["#LEFT_DOWN#"]         = "<IMG ICON=\"71\" ALT=\"LEFT_DOWN\">";
			$this->G_EMOJI["#PHONE_TO#"]          = "<IMG ICON=\"513\" ALT=\"PHONE_TO\">";
			$this->G_EMOJI["#MAIL_TO#"]           = "<IMG ICON=\"784\" ALT=\"MAIL_TO\">";
			$this->G_EMOJI["#FAX_TO#"]            = "<IMG ICON=\"166\" ALT=\"FAX_TO\">";
			$this->G_EMOJI["#CARRIER#"]           = "i";
			$this->G_EMOJI["#CARRIER_2#"]         = "i";
			$this->G_EMOJI["#MAIL#"]              = "<IMG ICON=\"108\" ALT=\"MAIL\">";
			$this->G_EMOJI["#OFFER#"]             = "D";
			$this->G_EMOJI["#POINT#"]             = "D";
			$this->G_EMOJI["#YEN#"]               = "<IMG ICON=\"109\" ALT=\"YEN\">";
			$this->G_EMOJI["#FREE_YEN#"]          = "<IMG ICON=\"299\" ALT=\"FREE_YEN\">";
			$this->G_EMOJI["#ID#"]                = "<IMG ICON=\"385\" ALT=\"ID\">";
			$this->G_EMOJI["#PASSWORD#"]          = "<IMG ICON=\"120\" ALT=\"PASSWORD\">";
			$this->G_EMOJI["#RETURN#"]            = "<IMG ICON=\"118\" ALT=\"RETURN\">";
			$this->G_EMOJI["#CLEAR#"]             = "<IMG ICON=\"324\" ALT=\"CLEAR\">";
			$this->G_EMOJI["#SEARCH#"]            = "<IMG ICON=\"119\" ALT=\"SEARCH\">";
			$this->G_EMOJI["#NEW#"]               = "<IMG ICON=\"334\" ALT=\"NEW\">";
			$this->G_EMOJI["#ANTENNA#"]           = "<IMG ICON=\"210\" ALT=\"ANTENNA\">";
			$this->G_EMOJI["#FREE#"]              = "<IMG ICON=\"85\" ALT=\"FREE\">";
			$this->G_EMOJI["#SHARP_DIAL#"]        = "<IMG ICON=\"818\" ALT=\"SHARP_DIAL\">";
			$this->G_EMOJI["#MOB_Q#"]             = "<IMG ICON=\"4\" ALT=\"MOB_Q\">";
			$this->G_EMOJI["#NO1#"]               = "<IMG ICON=\"180\" ALT=\"1\">";
			$this->G_EMOJI["#NO2#"]               = "<IMG ICON=\"181\" ALT=\"2\">";
			$this->G_EMOJI["#NO3#"]               = "<IMG ICON=\"182\" ALT=\"3\">";
			$this->G_EMOJI["#NO4#"]               = "<IMG ICON=\"183\" ALT=\"4\">";
			$this->G_EMOJI["#NO5#"]               = "<IMG ICON=\"184\" ALT=\"5\">";
			$this->G_EMOJI["#NO6#"]               = "<IMG ICON=\"185\" ALT=\"6\">";
			$this->G_EMOJI["#NO7#"]               = "<IMG ICON=\"186\" ALT=\"7\">";
			$this->G_EMOJI["#NO8#"]               = "<IMG ICON=\"187\" ALT=\"8\">";
			$this->G_EMOJI["#NO9#"]               = "<IMG ICON=\"188\" ALT=\"9\">";
			$this->G_EMOJI["#NO0#"]               = "<IMG ICON=\"325\" ALT=\"0\">";
			$this->G_EMOJI["#OK#"]                = "<IMG ICON=\"326\" ALT=\"OK\">";
			$this->G_EMOJI["#HEART#"]             = "<IMG ICON=\"414\" ALT=\"HEART\">";
			$this->G_EMOJI["#HEART_WAVE#"]        = "<IMG ICON=\"328\" ALT=\"HEART_WAVE\">";
			$this->G_EMOJI["#HEART_BREAK#"]       = "<IMG ICON=\"265\" ALT=\"HEART_BREAK\">";
			$this->G_EMOJI["#HEARTS#"]            = "<IMG ICON=\"266\" ALT=\"HEARTS\">";
			$this->G_EMOJI["#FACE_SMILE#"]        = "<IMG ICON=\"257\" ALT=\"FACE_SMILE\">";
			$this->G_EMOJI["#FACE_ANGRY#"]        = "<IMG ICON=\"258\" ALT=\"FACE_ANGRY\">";
			$this->G_EMOJI["#FACE_DEJECT#"]       = "<IMG ICON=\"260\" ALT=\"FACE_DEJECT\">";
			$this->G_EMOJI["#FACE_SAD#"]          = "<IMG ICON=\"259\" ALT=\"FACE_SAD\">";
			$this->G_EMOJI["#FACE_SWING#"]        = "<IMG ICON=\"327\" ALT=\"FACE_SWING\">";
			$this->G_EMOJI["#GOOD#"]              = "<IMG ICON=\"731\" ALT=\"GOOD\">";
			$this->G_EMOJI["#CHEERFUL#"]          = "<IMG ICON=\"343\" ALT=\"CHEERFUL\">";
			$this->G_EMOJI["#FEEL_GOOD#"]         = "<IMG ICON=\"224\" ALT=\"FEEL_GOOD\">";
			$this->G_EMOJI["#CUTE#"]              = "<IMG ICON=\"19\" ALT=\"CUTE\">";
			$this->G_EMOJI["#KISS#"]              = "<IMG ICON=\"273\" ALT=\"KISS\">";
			$this->G_EMOJI["#SHINE#"]             = "<IMG ICON=\"420\" ALT=\"SHINE\">";
			$this->G_EMOJI["#HINT#"]              = "<IMG ICON=\"77\" ALT=\"HINT\">";
			$this->G_EMOJI["#ANGER#"]             = "<IMG ICON=\"262\" ALT=\"ANGER\">";
			$this->G_EMOJI["#PUNCH#"]             = "<IMG ICON=\"281\" ALT=\"PUNCH\">";
			$this->G_EMOJI["#BOMB#"]              = "<IMG ICON=\"268\" ALT=\"BOMB\">";
			$this->G_EMOJI["#MOOD#"]              = "<IMG ICON=\"291\" ALT=\"MOOD\">";
			$this->G_EMOJI["#DOWN#"]              = "<IMG ICON=\"732\" ALT=\"DOWN\">";
			$this->G_EMOJI["#SLEEP#"]             = "<IMG ICON=\"261\" ALT=\"SLEEP\">";
			$this->G_EMOJI["#EXC#"]               = "<IMG ICON=\"2\" ALT=\"EXC\">";
			$this->G_EMOJI["#QUESTION#"]          = "<IMG ICON=\"733\" ALT=\"QUESTION\">";
			$this->G_EMOJI["#EXC_2#"]             = "<IMG ICON=\"734\" ALT=\"EXC_2\">";
			$this->G_EMOJI["#SHOCK#"]             = "<IMG ICON=\"329\" ALT=\"SHOCK\">";
			$this->G_EMOJI["#SWEAT#"]             = "<IMG ICON=\"330\" ALT=\"SWEAT\">";
			$this->G_EMOJI["#SWEAT_2#"]           = "<IMG ICON=\"263\" ALT=\"SWEAT_2\">";
			$this->G_EMOJI["#DASH#"]              = "<IMG ICON=\"282\" ALT=\"DASH\">";
			$this->G_EMOJI["#LONG_VOWEL#"]        = "<IMG ICON=\"810\" ALT=\"LONG_VOWEL\">";
			$this->G_EMOJI["#LONG_VOWEL_2#"]      = "<IMG ICON=\"735\" ALT=\"LONG_VOWEL_2\">";
			$this->G_EMOJI["#KACHINKO#"]          = "<IMG ICON=\"226\" ALT=\"KACHINKO\">";
			$this->G_EMOJI["#POUCH#"]             = "<IMG ICON=\"233\" ALT=\"POUCH\">";
			$this->G_EMOJI["#PEN#"]               = "<IMG ICON=\"508\" ALT=\"PEN\">";
			$this->G_EMOJI["#SHADOW#"]            = "<IMG ICON=\"80\" ALT=\"SHADOW\">";
			$this->G_EMOJI["#CHAIR#"]             = "";
			$this->G_EMOJI["#NIGHT#"]             = "<IMG ICON=\"15\" ALT=\"NIGHT\">";
			$this->G_EMOJI["#SOON#"]              = "<IMG ICON=\"63\" ALT=\"SOON\">";
			$this->G_EMOJI["#ON#"]                = "<IMG ICON=\"808\" ALT=\"ON\">";
			$this->G_EMOJI["#END#"]               = "<IMG ICON=\"64\" ALT=\"END\">";
			$this->G_EMOJI["#TIME#"]              = "<IMG ICON=\"46\" ALT=\"TIME\">";
			$this->G_EMOJI["#APPLI#"]             = "";
			$this->G_EMOJI["#APPLI_2#"]           = "";
			$this->G_EMOJI["#SHIRTS#"]            = "<IMG ICON=\"335\" ALT=\"SHIRTS\">";
			$this->G_EMOJI["#WALLET#"]            = "<IMG ICON=\"290\" ALT=\"WALLET\">";
			$this->G_EMOJI["#MAKEUP#"]            = "<IMG ICON=\"295\" ALT=\"MAKEUP\">";
			$this->G_EMOJI["#JEANS#"]             = "<IMG ICON=\"805\" ALT=\"JEANS\">";
			$this->G_EMOJI["#SNOW_BOARD#"]        = "<IMG ICON=\"221\" ALT=\"SNOW_BOARD\">";
			$this->G_EMOJI["#CHAPEL#"]            = "<IMG ICON=\"48\" ALT=\"CHAPEL\">";
			$this->G_EMOJI["#DOOR#"]              = "";
			$this->G_EMOJI["#DOLLAR#"]            = "<IMG ICON=\"233\" ALT=\"DOLLAR\">";
			$this->G_EMOJI["#PC#"]                = "<IMG ICON=\"337\" ALT=\"PC\">";
			$this->G_EMOJI["#LOVE_LETTER#"]       = "<IMG ICON=\"806\" ALT=\"LOVE_LETTER\">";
			$this->G_EMOJI["#WRENCH#"]            = "<IMG ICON=\"152\" ALT=\"WRENCH\">";
			$this->G_EMOJI["#PENCIL#"]            = "<IMG ICON=\"149\" ALT=\"PENCIL\">";
			$this->G_EMOJI["#CROWN#"]             = "<IMG ICON=\"354\" ALT=\"CROWN\">";
			$this->G_EMOJI["#RING#"]              = "<IMG ICON=\"72\" ALT=\"RING\">";
			$this->G_EMOJI["#SANDGLASS#"]         = "<IMG ICON=\"58\" ALT=\"SANDGLASS\">";
			$this->G_EMOJI["#BICYCLE#"]           = "<IMG ICON=\"215\" ALT=\"BICYCLE\">";
			$this->G_EMOJI["#TEACUP#"]            = "<IMG ICON=\"423\" ALT=\"TEACUP\">";
			$this->G_EMOJI["#WATCH#"]             = "<IMG ICON=\"25\" ALT=\"WATCH\">";
			$this->G_EMOJI["#FACE_THINK#"]        = "<IMG ICON=\"441\" ALT=\"FACE_THINK\">";
			$this->G_EMOJI["#FACE_PEACE#"]        = "<IMG ICON=\"446\" ALT=\"FACE_PEACE\">";
			$this->G_EMOJI["#FACE_HURRY#"]        = "<IMG ICON=\"257\" ALT=\"FACE_HURRY\"><IMG ICON=\"330\" ALT=\"FACE_HURRY\">";
			$this->G_EMOJI["#FACE_HURRY_2#"]      = "<IMG ICON=\"351\" ALT=\"FACE_HURRY_2\">";
			$this->G_EMOJI["#FACE_ANGRY_2#"]      = "<IMG ICON=\"779\" ALT=\"FACE_ANGRY_2\">";
			$this->G_EMOJI["#FACE_POKER#"]        = "<IMG ICON=\"450\" ALT=\"FACE_POKER\">";
			$this->G_EMOJI["#FACE_HEART#"]        = "<IMG ICON=\"349\" ALT=\"FACE_HEART\">";
			$this->G_EMOJI["#FINGER#"]            = "<IMG ICON=\"287\" ALT=\"FINGER\">";
			$this->G_EMOJI["#FACE_JOKE#"]         = "<IMG ICON=\"264\" ALT=\"FACE_JOKE\">";
			$this->G_EMOJI["#FACE_WINK#"]         = "<IMG ICON=\"348\" ALT=\"FACE_WINK\">";
			$this->G_EMOJI["#FACE_HAPPY#"]        = "<IMG ICON=\"446\" ALT=\"FACE_HAPPY\">";
			$this->G_EMOJI["#FACE_PATIENCE#"]     = "<IMG ICON=\"443\" ALT=\"FACE_PATIENCE\">";
			$this->G_EMOJI["#CAT_2#"]             = "<IMG ICON=\"440\" ALT=\"CAT_2\">";
			$this->G_EMOJI["#FACE_CRY#"]          = "<IMG ICON=\"259\" ALT=\"FACE_CRY\">";
			$this->G_EMOJI["#TEAR#"]              = "<IMG ICON=\"791\" ALT=\"TEAR\">";
			$this->G_EMOJI["#NG#"]                = "NG";
			$this->G_EMOJI["#CLIP#"]              = "<IMG ICON=\"143\" ALT=\"CLIP\">";
			$this->G_EMOJI["#COPYRIGHT#"]         = "<IMG ICON=\"81\" ALT=\"COPYRIGHT\">";
			$this->G_EMOJI["#TM#"]                = "<IMG ICON=\"54\" ALT=\"TM\">";
			$this->G_EMOJI["#RUNNER#"]            = "<IMG ICON=\"218\" ALT=\"RUNNER\">";
			$this->G_EMOJI["#SECRET#"]            = "<IMG ICON=\"279\" ALT=\"SECRET\">";
			$this->G_EMOJI["#RECYCLING#"]         = "<IMG ICON=\"807\" ALT=\"RECYCLING\">";
			$this->G_EMOJI["#REGIST#"]            = "<IMG ICON=\"82\" ALT=\"REGIST\">";
			$this->G_EMOJI["#WARNING#"]           = "<IMG ICON=\"1\" ALT=\"WARNING\">";
			$this->G_EMOJI["#PROHIBITION#"]       = "";
			$this->G_EMOJI["#EMPTY#"]             = "<IMG ICON=\"387\" ALT=\"EMPTY\">";
			$this->G_EMOJI["#SUCCESS#"]           = "";
			$this->G_EMOJI["#FULL#"]              = "<IMG ICON=\"386\" ALT=\"FULL\">";
			$this->G_EMOJI["#RIGHT_LEFT#"]        = "<IMG ICON=\"808\" ALT=\"RIGHT_LEFT\">";
			$this->G_EMOJI["#UP_DOWN#"]           = "<IMG ICON=\"809\" ALT=\"UP_DOWN\">";
			$this->G_EMOJI["#SCHOOL#"]            = "<IMG ICON=\"377\" ALT=\"SCHOOL\">";
			$this->G_EMOJI["#WAVE#"]              = "<IMG ICON=\"810\" ALT=\"WAVE\">";
			$this->G_EMOJI["#MOUNTAIN#"]          = "<IMG ICON=\"342\" ALT=\"MOUNTAIN\">";
			$this->G_EMOJI["#CLOVER#"]            = "<IMG ICON=\"53\" ALT=\"CLOVER\">";
			$this->G_EMOJI["#CHERRY#"]            = "<IMG ICON=\"241\" ALT=\"CHERRY\">";
			$this->G_EMOJI["#TULIP#"]             = "<IMG ICON=\"113\" ALT=\"TULIP\">";
			$this->G_EMOJI["#BANANA#"]            = "<IMG ICON=\"739\" ALT=\"BANANA\">";
			$this->G_EMOJI["#APPLE#"]             = "<IMG ICON=\"434\" ALT=\"APPLE\">";
			$this->G_EMOJI["#LEAF#"]              = "<IMG ICON=\"811\" ALT=\"LEAF\">";
			$this->G_EMOJI["#MAPLE#"]             = "<IMG ICON=\"133\" ALT=\"MAPLE\">";
			$this->G_EMOJI["#CHERRY_BLOSSOM#"]    = "<IMG ICON=\"235\" ALT=\"CHERRY_BLOSSOM\">";
			$this->G_EMOJI["#RICE_BALL#"]         = "<IMG ICON=\"244\" ALT=\"RICE_BALL\">";
			$this->G_EMOJI["#CAKE#"]              = "<IMG ICON=\"239\" ALT=\"CAKE\">";
			$this->G_EMOJI["#SAKE#"]              = "<IMG ICON=\"400\" ALT=\"SAKE\">";
			$this->G_EMOJI["#BOWL#"]              = "<IMG ICON=\"333\" ALT=\"BOWL\">";
			$this->G_EMOJI["#PAN#"]               = "<IMG ICON=\"424\" ALT=\"PAN\">";
			$this->G_EMOJI["#SNAIL#"]             = "<IMG ICON=\"812\" ALT=\"SNAIL\">";
			$this->G_EMOJI["#BABY_BIRD#"]         = "<IMG ICON=\"78\" ALT=\"BABY_BIRD\">";
			$this->G_EMOJI["#PENGUIN#"]           = "<IMG ICON=\"252\" ALT=\"PENGUIN\">";
			$this->G_EMOJI["#FISH#"]              = "<IMG ICON=\"203\" ALT=\"FISH\">";
			$this->G_EMOJI["#FACE_DELICIOUS#"]    = "<IMG ICON=\"454\" ALT=\"FACE_DELICIOUS\">";
			$this->G_EMOJI["#FACE_FOPPISH#"]      = "<IMG ICON=\"814\" ALT=\"FACE_FOPPISH\">";
			$this->G_EMOJI["#HORSE#"]             = "<IMG ICON=\"248\" ALT=\"HORSE\">";
			$this->G_EMOJI["#PIG#"]               = "<IMG ICON=\"254\" ALT=\"PIG\">";
			$this->G_EMOJI["#WINE#"]              = "<IMG ICON=\"12\" ALT=\"WINE\">";
			$this->G_EMOJI["#FACE_LET_DOWN#"]     = "<IMG ICON=\"350\" ALT=\"FACE_LET_DOWN\">";
			// mod 2011/07/05 Y.Nakajima
			//if(ereg("^1", $_SERVER["HTTP_X_UP_DEVCAP_ISCOLOR"])){
			if(strpos($_SERVER["HTTP_X_UP_DEVCAP_ISCOLOR"], "^1")){
				$this->G_SUPPORT_IMAGE_EXT   = "PNG";
				$this->G_SUPPORT_CMDN_TYP    = 1;
			} else {
				$this->G_SUPPORT_IMAGE_EXT   = "BMP";
				$this->G_SUPPORT_CMDN_TYP    = 3;
			}
			break;
		// add 2010/08/12 Y.Matsukawa [
		case D_IPHONE:
		case D_ANDROID_1:		// add 2010/10/20 Y.Matsukawa
		case D_ANDROID_2:		// add 2010/10/20 Y.Matsukawa
			$this->G_EMOJI["#SUN#"]               = "";
			$this->G_EMOJI["#CLOUD#"]             = "";
			$this->G_EMOJI["#RAIN#"]              = "";
			$this->G_EMOJI["#SNOW#"]              = "";
			$this->G_EMOJI["#THUNDER#"]           = "";
			$this->G_EMOJI["#TYPHOON#"]           = "";
			$this->G_EMOJI["#FOG#"]               = "";
			$this->G_EMOJI["#LIGHT_RAIN#"]        = "";
			$this->G_EMOJI["#RAM#"]               = "";
			$this->G_EMOJI["#BULL#"]              = "";
			$this->G_EMOJI["#TWINS#"]             = "";
			$this->G_EMOJI["#CRAB#"]              = "";
			$this->G_EMOJI["#LION#"]              = "";
			$this->G_EMOJI["#VIRGIN#"]            = "";
			$this->G_EMOJI["#BALANCE#"]           = "";
			$this->G_EMOJI["#SCORPION#"]          = "";
			$this->G_EMOJI["#ARCHER#"]            = "";
			$this->G_EMOJI["#GOAT#"]              = "";
			$this->G_EMOJI["#WATER_BEARER#"]      = "";
			$this->G_EMOJI["#FISHES#"]            = "";
			$this->G_EMOJI["#SPORTS#"]            = "";
			$this->G_EMOJI["#BASEBALL#"]          = "";
			$this->G_EMOJI["#GOLF#"]              = "";
			$this->G_EMOJI["#TENNIS#"]            = "";
			$this->G_EMOJI["#SOCCER#"]            = "";
			$this->G_EMOJI["#SKI#"]               = "";
			$this->G_EMOJI["#BASKETBALL#"]        = "";
			$this->G_EMOJI["#FLAG#"]              = "";
			$this->G_EMOJI["#POCKET_BELL#"]       = "";
			$this->G_EMOJI["#TRAIN#"]             = "";
			$this->G_EMOJI["#SUBWAY#"]            = "";
			$this->G_EMOJI["#SHINKANSEN#"]        = "";
			$this->G_EMOJI["#CAR#"]               = "";
			$this->G_EMOJI["#CAR_2#"]             = "";
			$this->G_EMOJI["#BUS#"]               = "";
			$this->G_EMOJI["#SHIP#"]              = "";
			$this->G_EMOJI["#AIRPLANE#"]          = "";
			$this->G_EMOJI["#HOME#"]              = "";
			$this->G_EMOJI["#BUILD#"]             = "";
			$this->G_EMOJI["#POST#"]              = "";
			$this->G_EMOJI["#HOSPITAL#"]          = "";
			$this->G_EMOJI["#BANK#"]              = "";
			$this->G_EMOJI["#ATM#"]               = "";
			$this->G_EMOJI["#HOTEL#"]             = "";
			$this->G_EMOJI["#CVS#"]               = "";
			$this->G_EMOJI["#GS#"]                = "";
			$this->G_EMOJI["#PARK#"]              = "";
			$this->G_EMOJI["#SIGNAL#"]            = "";
			$this->G_EMOJI["#TOILET#"]            = "";
			$this->G_EMOJI["#RESTAURANT#"]        = "";
			$this->G_EMOJI["#CAFE#"]              = "";
			$this->G_EMOJI["#BAR#"]               = "";
			$this->G_EMOJI["#BEER#"]              = "";
			$this->G_EMOJI["#BURGER#"]            = "";
			$this->G_EMOJI["#BOUTIQUE#"]          = "";
			$this->G_EMOJI["#BEAUTY_SALON#"]      = "";
			$this->G_EMOJI["#KARAOKE#"]           = "";
			$this->G_EMOJI["#MOVIE#"]             = "";
			$this->G_EMOJI["#RIGHT_UP#"]          = "";
			$this->G_EMOJI["#AMUSEMENT_PARK#"]    = "";
			$this->G_EMOJI["#MUSIC#"]             = "";
			$this->G_EMOJI["#ART#"]               = "";
			$this->G_EMOJI["#DRAMA#"]             = "";
			$this->G_EMOJI["#EVENT#"]             = "";
			$this->G_EMOJI["#TICKET#"]            = "";
			$this->G_EMOJI["#SMOKING#"]           = "";
			$this->G_EMOJI["#NO_SMOKING#"]        = "";
			$this->G_EMOJI["#CAMERA#"]            = "";
			$this->G_EMOJI["#BAG#"]               = "";
			$this->G_EMOJI["#BOOK#"]              = "";
			$this->G_EMOJI["#RIBBON#"]            = "";
			$this->G_EMOJI["#PRESENT#"]           = "";
			$this->G_EMOJI["#BIRTHDAY#"]          = "";
			$this->G_EMOJI["#TEL#"]               = "";
			$this->G_EMOJI["#MOBILE#"]            = "";
			$this->G_EMOJI["#MEMO#"]              = "";
			$this->G_EMOJI["#TV#"]                = "";
			$this->G_EMOJI["#GAME#"]              = "";
			$this->G_EMOJI["#CD#"]                = "";
			$this->G_EMOJI["#HEART_TRUMP#"]       = "";
			$this->G_EMOJI["#SPADE#"]             = "";
			$this->G_EMOJI["#DIAMOND#"]           = "";
			$this->G_EMOJI["#CLUBS#"]             = "";
			$this->G_EMOJI["#EYE#"]               = "";
			$this->G_EMOJI["#EAR#"]               = "";
			$this->G_EMOJI["#GOO#"]               = "";
			$this->G_EMOJI["#CHOKI#"]             = "";
			$this->G_EMOJI["#PAR#"]               = "";
			$this->G_EMOJI["#RIGHT_DOWN#"]        = "";
			$this->G_EMOJI["#LEFT_UP#"]           = "";
			$this->G_EMOJI["#FOOT#"]              = "";
			$this->G_EMOJI["#SHOES#"]             = "";
			$this->G_EMOJI["#GLASSES#"]           = "";
			$this->G_EMOJI["#WHEELCHAIR#"]        = "";
			$this->G_EMOJI["#NEW_MOON#"]          = "";
			$this->G_EMOJI["#CHIP_MOON#"]         = "";
			$this->G_EMOJI["#HALF_MOON#"]         = "";
			$this->G_EMOJI["#CRESCENT_MOON#"]     = "";
			$this->G_EMOJI["#FULL_MOON#"]         = "";
			$this->G_EMOJI["#DOG#"]               = "";
			$this->G_EMOJI["#CAT#"]               = "";
			$this->G_EMOJI["#RESORT#"]            = "";
			$this->G_EMOJI["#XMAS#"]              = "";
			$this->G_EMOJI["#LEFT_DOWN#"]         = "";
			$this->G_EMOJI["#PHONE_TO#"]          = "";
			$this->G_EMOJI["#MAIL_TO#"]           = "";
			$this->G_EMOJI["#FAX_TO#"]            = "";
			$this->G_EMOJI["#CARRIER#"]           = "";
			$this->G_EMOJI["#CARRIER_2#"]         = "";
			$this->G_EMOJI["#MAIL#"]              = "";
			$this->G_EMOJI["#OFFER#"]             = "";
			$this->G_EMOJI["#POINT#"]             = "";
			$this->G_EMOJI["#YEN#"]               = "";
			$this->G_EMOJI["#FREE_YEN#"]          = "";
			$this->G_EMOJI["#ID#"]                = "";
			$this->G_EMOJI["#PASSWORD#"]          = "";
			$this->G_EMOJI["#RETURN#"]            = "";
			$this->G_EMOJI["#CLEAR#"]             = "";
			$this->G_EMOJI["#SEARCH#"]            = "";
			$this->G_EMOJI["#NEW#"]               = "";
			$this->G_EMOJI["#ANTENNA#"]           = "";
			$this->G_EMOJI["#FREE#"]              = "";
			$this->G_EMOJI["#SHARP_DIAL#"]        = "";
			$this->G_EMOJI["#MOB_Q#"]             = "";
			$this->G_EMOJI["#NO1#"]               = "・";
			$this->G_EMOJI["#NO2#"]               = "・";
			$this->G_EMOJI["#NO3#"]               = "・";
			$this->G_EMOJI["#NO4#"]               = "・";
			$this->G_EMOJI["#NO5#"]               = "・";
			$this->G_EMOJI["#NO6#"]               = "・";
			$this->G_EMOJI["#NO7#"]               = "・";
			$this->G_EMOJI["#NO8#"]               = "・";
			$this->G_EMOJI["#NO9#"]               = "・";
			$this->G_EMOJI["#NO0#"]               = "・";
			$this->G_EMOJI["#OK#"]                = "";
			$this->G_EMOJI["#HEART#"]             = "";
			$this->G_EMOJI["#HEART_WAVE#"]        = "";
			$this->G_EMOJI["#HEART_BREAK#"]       = "";
			$this->G_EMOJI["#HEARTS#"]            = "";
			$this->G_EMOJI["#FACE_SMILE#"]        = "";
			$this->G_EMOJI["#FACE_ANGRY#"]        = "";
			$this->G_EMOJI["#FACE_DEJECT#"]       = "";
			$this->G_EMOJI["#FACE_SAD#"]          = "";
			$this->G_EMOJI["#FACE_SWING#"]        = "";
			$this->G_EMOJI["#GOOD#"]              = "";
			$this->G_EMOJI["#CHEERFUL#"]          = "";
			$this->G_EMOJI["#FEEL_GOOD#"]         = "";
			$this->G_EMOJI["#CUTE#"]              = "";
			$this->G_EMOJI["#KISS#"]              = "";
			$this->G_EMOJI["#SHINE#"]             = "";
			$this->G_EMOJI["#HINT#"]              = "";
			$this->G_EMOJI["#ANGER#"]             = "";
			$this->G_EMOJI["#PUNCH#"]             = "";
			$this->G_EMOJI["#BOMB#"]              = "";
			$this->G_EMOJI["#MOOD#"]              = "";
			$this->G_EMOJI["#DOWN#"]              = "";
			$this->G_EMOJI["#SLEEP#"]             = "";
			$this->G_EMOJI["#EXC#"]               = "";
			$this->G_EMOJI["#QUESTION#"]          = "";
			$this->G_EMOJI["#EXC_2#"]             = "";
			$this->G_EMOJI["#SHOCK#"]             = "";
			$this->G_EMOJI["#SWEAT#"]             = "";
			$this->G_EMOJI["#SWEAT_2#"]           = "";
			$this->G_EMOJI["#DASH#"]              = "";
			$this->G_EMOJI["#LONG_VOWEL#"]        = "";
			$this->G_EMOJI["#LONG_VOWEL_2#"]      = "";
			$this->G_EMOJI["#KACHINKO#"]          = "";
			$this->G_EMOJI["#POUCH#"]             = "";
			$this->G_EMOJI["#PEN#"]               = "";
			$this->G_EMOJI["#SHADOW#"]            = "";
			$this->G_EMOJI["#CHAIR#"]             = "";
			$this->G_EMOJI["#NIGHT#"]             = "";
			$this->G_EMOJI["#SOON#"]              = "";
			$this->G_EMOJI["#ON#"]                = "";
			$this->G_EMOJI["#END#"]               = "";
			$this->G_EMOJI["#TIME#"]              = "";
			$this->G_EMOJI["#APPLI#"]             = "";
			$this->G_EMOJI["#APPLI_2#"]           = "";
			$this->G_EMOJI["#SHIRTS#"]            = "";
			$this->G_EMOJI["#WALLET#"]            = "";
			$this->G_EMOJI["#MAKEUP#"]            = "";
			$this->G_EMOJI["#JEANS#"]             = "";
			$this->G_EMOJI["#SNOW_BOARD#"]        = "";
			$this->G_EMOJI["#CHAPEL#"]            = "";
			$this->G_EMOJI["#DOOR#"]              = "";
			$this->G_EMOJI["#DOLLAR#"]            = "";
			$this->G_EMOJI["#PC#"]                = "";
			$this->G_EMOJI["#LOVE_LETTER#"]       = "";
			$this->G_EMOJI["#WRENCH#"]            = "";
			$this->G_EMOJI["#PENCIL#"]            = "";
			$this->G_EMOJI["#CROWN#"]             = "";
			$this->G_EMOJI["#RING#"]              = "";
			$this->G_EMOJI["#SANDGLASS#"]         = "";
			$this->G_EMOJI["#BICYCLE#"]           = "";
			$this->G_EMOJI["#TEACUP#"]            = "";
			$this->G_EMOJI["#WATCH#"]             = "";
			$this->G_EMOJI["#FACE_THINK#"]        = "";
			$this->G_EMOJI["#FACE_PEACE#"]        = "";
			$this->G_EMOJI["#FACE_HURRY#"]        = "";
			$this->G_EMOJI["#FACE_HURRY_2#"]      = "";
			$this->G_EMOJI["#FACE_ANGRY_2#"]      = "";
			$this->G_EMOJI["#FACE_POKER#"]        = "";
			$this->G_EMOJI["#FACE_HEART#"]        = "";
			$this->G_EMOJI["#FINGER#"]            = "";
			$this->G_EMOJI["#FACE_JOKE#"]         = "";
			$this->G_EMOJI["#FACE_WINK#"]         = "";
			$this->G_EMOJI["#FACE_HAPPY#"]        = "";
			$this->G_EMOJI["#FACE_PATIENCE#"]     = "";
			$this->G_EMOJI["#CAT_2#"]             = "";
			$this->G_EMOJI["#FACE_CRY#"]          = "";
			$this->G_EMOJI["#TEAR#"]              = "";
			$this->G_EMOJI["#NG#"]                = "";
			$this->G_EMOJI["#CLIP#"]              = "";
			$this->G_EMOJI["#COPYRIGHT#"]         = "";
			$this->G_EMOJI["#TM#"]                = "";
			$this->G_EMOJI["#RUNNER#"]            = "";
			$this->G_EMOJI["#SECRET#"]            = "";
			$this->G_EMOJI["#RECYCLING#"]         = "";
			$this->G_EMOJI["#REGIST#"]            = "";
			$this->G_EMOJI["#WARNING#"]           = "";
			$this->G_EMOJI["#PROHIBITION#"]       = "";
			$this->G_EMOJI["#EMPTY#"]             = "";
			$this->G_EMOJI["#SUCCESS#"]           = "";
			$this->G_EMOJI["#FULL#"]              = "";
			$this->G_EMOJI["#RIGHT_LEFT#"]        = "";
			$this->G_EMOJI["#UP_DOWN#"]           = "";
			$this->G_EMOJI["#SCHOOL#"]            = "";
			$this->G_EMOJI["#WAVE#"]              = "";
			$this->G_EMOJI["#MOUNTAIN#"]          = "";
			$this->G_EMOJI["#CLOVER#"]            = "";
			$this->G_EMOJI["#CHERRY#"]            = "";
			$this->G_EMOJI["#TULIP#"]             = "";
			$this->G_EMOJI["#BANANA#"]            = "";
			$this->G_EMOJI["#APPLE#"]             = "";
			$this->G_EMOJI["#LEAF#"]              = "";
			$this->G_EMOJI["#MAPLE#"]             = "";
			$this->G_EMOJI["#CHERRY_BLOSSOM#"]    = "";
			$this->G_EMOJI["#RICE_BALL#"]         = "";
			$this->G_EMOJI["#CAKE#"]              = "";
			$this->G_EMOJI["#SAKE#"]              = "";
			$this->G_EMOJI["#BOWL#"]              = "";
			$this->G_EMOJI["#PAN#"]               = "";
			$this->G_EMOJI["#SNAIL#"]             = "";
			$this->G_EMOJI["#BABY_BIRD#"]         = "";
			$this->G_EMOJI["#PENGUIN#"]           = "";
			$this->G_EMOJI["#FISH#"]              = "";
			$this->G_EMOJI["#FACE_DELICIOUS#"]    = "";
			$this->G_EMOJI["#FACE_FOPPISH#"]      = "";
			$this->G_EMOJI["#HORSE#"]             = "";
			$this->G_EMOJI["#PIG#"]               = "";
			$this->G_EMOJI["#WINE#"]              = "";
			$this->G_EMOJI["#FACE_LET_DOWN#"]     = "";
			$this->G_SUPPORT_IMAGE_EXT   = "PNG";
			$this->G_SUPPORT_CMDN_TYP    = 1;
			break;
		// add 2010/08/12 Y.Matsukawa ]
		default:
			$this->G_SUPPORT_IMAGE_EXT   = "BMP";
			$this->G_SUPPORT_CMDN_TYP    = 3;
			break;
		}
	}

	//---------------------------------------------------------------
	// USER_AGENTからキャリアを判定
	//---------------------------------------------------------------
	function getCarrierAgent($P_USER_AGENT){
		// キャリア判定
		// mod 2011/07/05 Y.Nakajima [
/*
		if( ereg(D_REG_SOFTBANK,$P_USER_AGENT) ){ return D_SOFTBANK; }
		if( ereg(D_REG_KDDI    ,$P_USER_AGENT) ){ return D_KDDI;     }
		if( ereg(D_REG_HDML    ,$P_USER_AGENT) ){ return D_HDML;     }
		if( ereg(D_REG_DOCOMO  ,$P_USER_AGENT) ){ return D_DOCOMO;   }
		if( ereg(D_REG_WILL    ,$P_USER_AGENT) ){ return D_WILL;     }
		if( ereg(D_REG_PC      ,$P_USER_AGENT) ){
			if(ereg(D_ALLOW_PC, $_SERVER["HTTP_HOST"])){
*/
		if( strpos($P_USER_AGENT, D_REG_SOFTBANK) ){ return D_SOFTBANK; }
		if( strpos($P_USER_AGENT, D_REG_KDDI    ) ){ return D_KDDI;     }
		if( strpos($P_USER_AGENT, D_REG_HDML    ) ){ return D_HDML;     }
		if( strpos($P_USER_AGENT, D_REG_DOCOMO  ) ){ return D_DOCOMO;   }
		if( strpos($P_USER_AGENT, D_REG_WILL    ) ){ return D_WILL;     }
		if( strpos($P_USER_AGENT, D_REG_PC      ) ){
			if(strpos($_SERVER["HTTP_HOST"], D_ALLOW_PC)){
		// mod 2011/07/05 Y.Nakajima ]
				return D_PC;
			} else {
				header("Content-Type: text/html;charset=Shift_JIS");
				echo mb_convert_encoding("アクセスできません。(".$_SERVER["HTTP_HOST"].")", "SJIS-win","eucJP-win");
				exit;
			}
		}
		return D_PC;
	}

	function getSupportImageExt(){
		return $this->G_SUPPORT_IMAGE_EXT;
	}

	//---------------------------------------------------------------
	// アクセス元ＩＰアドレスからキャリアを判定
	// 厳密チェックはできるが、DNS必須
	//---------------------------------------------------------------
	function getCarrierFromDomain(){
		$this->G_DOMAIN = gethostbyname(getenv("REMOTE_ADDR"));
		// mod 2011/07/05 Y.Nakajima
		//if (ereg("docomo\.ne\.jp$", $this->G_DOMAIN)) {
		if (preg_match("/docomo\.ne\.jp$/", $this->G_DOMAIN, $matches) === true) {
			return D_DOCOMO;
		// mod 2011/07/05 Y.Nakajima
		//} else if (ereg("(jp-[a-z]|vodafone|softbank)\.ne\.jp$", $this->G_DOMAIN)) {
		} else if (preg_match("/(jp-[a-z]|vodafone|softbank)\.ne\.jp$/", $this->G_DOMAIN, $matches) === true) {
			return D_SOFTBANK;
		// mod 2011/07/05 Y.Nakajima
		//} else if (ereg("(ido|ezweb)\.ne\.jp$", $this->G_DOMAIN)) {
		} else if (preg_match("/(ido|ezweb)\.ne\.jp$/", $this->G_DOMAIN, $matches) === true) {
			return D_KDDI;
		}
		return D_PC;
	}

	//---------------------------------------------------------------
	// Getter
	//---------------------------------------------------------------
	function isDoCoMo()  { return ($this->G_AGENT_TYPE == D_DOCOMO  ) ? true : false; }
	function isSoftBank(){ return ($this->G_AGENT_TYPE == D_SOFTBANK) ? true : false; }
	function isEdge()    { return ($this->G_AGENT_TYPE == D_WILL    ) ? true : false; }
	function isPC()      { return ($this->G_AGENT_TYPE == D_PC      ) ? true : false; }
	function isIPHONE()  { return ($this->G_AGENT_TYPE == D_IPHONE  ) ? true : false; }		// add 2010/08/12 Y.Matsukawa
	// add 2010/10/20 Y.Matsukawa [
	function isANDROID()  { return ($this->G_AGENT_TYPE == D_ANDROID_1 ||  $this->G_AGENT_TYPE == D_ANDROID_2) ? true : false; }
	function isANDROID_1()  { return ($this->G_AGENT_TYPE == D_ANDROID_1) ? true : false; }
	function isANDROID_2()  { return ($this->G_AGENT_TYPE == D_ANDROID_2) ? true : false; }
	function isSmartPhone()  { return ($this->G_AGENT_TYPE == D_IPHONE || $this->G_AGENT_TYPE == D_ANDROID_1 ||  $this->G_AGENT_TYPE == D_ANDROID_2) ? true : false; }
	// add 2010/10/20 Y.Matsukawa ]

	// XHTML対応か？
	function isXHTML(){ return false; }

	//---------------------------------------------------------------
	// エリア検索可能かどうかを返却
	//---------------------------------------------------------------
	function isLocation(){
		// mod 2011/07/05 Y.Nakajima
		if($this->G_AGENT_TYPE == D_PC){
			return true;
		// add 2010/08/12 Y.Matsukawa [
		} else if ($this->G_AGENT_TYPE == D_IPHONE){
			return true;
		// add 2010/08/12 Y.Matsukawa ]
		// add 2010/10/20 Y.Matsukawa [
		} else if ($this->G_AGENT_TYPE == D_ANDROID_1 || $this->G_AGENT_TYPE == D_ANDROID_2){
			return true;
		// add 2010/10/20 Y.Matsukawa ]
		} else {
			return ($this->G_SUPPORT_LOCATION == "1" || $this->G_SUPPORT_LOCATION == "2");
		}
	}

	//---------------------------------------------------------------
	// ＧＰＳ対応かどうかを返却
	//---------------------------------------------------------------
	function isGPS(){
		return $this->G_SUPPORT_LOCATION == "2";
	}

	//---------------------------------------------------------------
	// 各キャリア毎の絵文字返却
	//---------------------------------------------------------------
	function getEmoji($P_KEYWORD, $WORD = ""){
		if(! $this->G_EMOJI[$P_KEYWORD] && $WORD){
			return $WORD;
		} else {
			return $this->G_EMOJI[$P_KEYWORD];
		}
	}

	//---------------------------------------------------------------
	// 置き換え文字列の設定
	//---------------------------------------------------------------
	function SetReplaceWord($P_WORD_ARRAY){
		$this->G_REPLACEWORD = $P_WORD_ARRAY;
		$this->G_REPLACEWORD_CNT = $this->G_REPLACEWORD.Count;
	}

	//---------------------------------------------------------------
	// 置き換え文字列の定義
	//---------------------------------------------------------------
	function AddReplaceWord($P_KEY, $P_WORD){
		$this->G_REPLACEWORD[$P_KEY] = $P_WORD;
		$this->G_REPLACEWORD_CNT++;
	}

	//---------------------------------------------------------------
	// 置き換え文字列の定義
	//---------------------------------------------------------------
	function AddReplaceWordArray($P_ARRAY){
		$cnt = 0;
		foreach($P_ARRAY as $key => $val){
			$this->G_REPLACEWORD[$key] = $val;
			$this->G_REPLACEWORD_CNT++;
			$cnt++;
		}
		return $cnt;
	}

	//---------------------------------------------------------------
	// 置き換え文字列の削除
	//---------------------------------------------------------------
	function DeleteReplaceWord($P_KEY){
		unset($this->G_REPLACEWORD[$P_KEY]);
		$this->G_REPLACEWORD_CNT--;
	}

	//---------------------------------------------------------------
	// 置き換え文字列のクリア
	//---------------------------------------------------------------
	function ClearReplaceWord(){
		$this->G_REPLACEWORD = array();
		$this->G_REPLACEWORD_CNT = 0;
	}

	//---------------------------------------------------------------
	// 置き換え文字列のクリア
	//---------------------------------------------------------------
	function GetReplaceWord(){
		return $this->G_REPLACEWORD;
	}

	//---------------------------------------------------------------
	// HTMLの埋め込み文字列を全て絵文字化する。
	//---------------------------------------------------------------
	function ConvertPictString($html, $to_enc, $from_enc){
		$wk = $html;
		foreach ($this->G_EMOJI as $key => $value) {
			$wk = str_replace($key, $value, $wk);
		}
		foreach ($this->G_REPLACEWORD as $key => $value) {
			$wk = str_replace($key, $value, $wk);
			$wk = str_replace(strtolower($key), $value, $wk);
		}
		return mb_convert_encoding($wk, $to_enc, $from_enc);
	}

	//---------------------------------------------------------------
	// キャリア毎のイメージ画像（地図）ＵＲＬ生成処理
	// softbankの端末は、GPSで現在地を取得する時に、キャリアに飛ぶが
	// その時に通常のurl形式だと、パラメータが欠損してしまう
	// 対応策として、urlパラメータを、/で区切って、引き継ぐ処理にしている
	//---------------------------------------------------------------
	function makeImageUrl($url){
		if($this->G_AGENT_TYPE == D_SOFTBANK){
//			if(ereg("\/2\.0",$this->G_USER_AGENT)){
			// mod 2011/07/05 Y.Nakajima
			//if(ereg("\/2\.0",$this->G_USER_AGENT) || ereg("\/3\.0",$this->G_USER_AGENT)){
			if(preg_match("/\/2\.0/", $this->G_USER_AGENT) || preg_match("/\/3\.0/", $this->G_USER_AGENT)){
				return ereg_replace("(\?|\&)", "/", $url)."/m.png";
//				return str_replace("?","/",$url)."/m.png";
			} else {
				return $url;
			}
		} else {
			return $url;
		}
	}

	//---------------------------------------------------------------
	// キャリア毎のアクセスキータグの生成処理
	//---------------------------------------------------------------
	function makeAccessKeyTag($no){
		$tag = "accesskey=\"$no\"";
		// SOFTBANKはアクセスキーがDIRECTKEYなので変換
		// それでも3G携帯の一部は適用不可らしい
		if($this->G_AGENT_TYPE == D_SOFTBANK){
			// J-PHONEの2型はNONUMBERも未対応
			// mod 2011/07/05 Y.Nakajima
			//if(ereg("^J\-PHONE\/2\.0\/",$this->G_USER_AGENT)){
			if(preg_match("/^J\-PHONE\/2\.0\//", $this->G_USER_AGENT)){
				return "";
			} else {
				return $tag." NONUMBER";
			}
		// mod 2011/07/05 Y.Nakajima
		//} else if($this->G_AGENT_TYPE == D_REG_KDDI){
		} else if($this->G_AGENT_TYPE == D_KDDI){
			return $tag;
		} else {
			return $tag;
		}
	}
}
?>
