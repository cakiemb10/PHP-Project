<?php
// ------------------------------------------------------------
// APIレスポンスXML作成
// 
// 2016/06/14 H.Yasunaga	新規作成
// 2016/06/15 H.Yasunaga	htmlspecialchars引数のフラグ修正
// 2016/06/27 H.Yasunaga	出力するXMLをフォーマットする修正
// 2016/12/16 H.Yasunaga	出力するデータの補正処理追加
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/ResponseTag.inc");
	// add 2016/12/16 H.Yasunaga 出力データの補正 [
	require_once(dirname(__FILE__) . "/Value_Correction.inc");
	// add 2016/12/16 H.Yasunaga]
	
	// エラーNo1 検索リクエスト項目の値が入っていないか、不正な値
	define("DEF_RESPONSE_ERROR_TEXT_1", "invalid_parameter_value");
	// エラーNo2 アクセスキーの値が入っていないか不正な値
	define("DEF_RESPONSE_ERROR_TEXT_2", "invalid_key_value");
	// エラーNo3 IPアドレスの値がアクセスキーに紐づいた値ではないか、不正な値
	define("DEF_RESPONSE_ERROR_TEXT_3", "invalid_ipaddress_value");
	// エラーNo4 該当するデータが1件もない
	define("DEF_RESPONSE_ERROR_TEXT_4", "item_not_found");
	// エラーNo5 上記以外のエラー(処理が完了できない場合)
	define("DEF_RESPONSE_ERROR_TEXT_5", "internal_server_error");
	
	class ResponseXML{
		// 店舗情報(DBからのデータ)
		private $dbDatas;
		// 検索結果件数
		private $totalNum;
		// 返却結果件数
		private $returnNum;
		// 返却結果開始位置
		private $startPotision;
		
		function __construct() {
			$this->dbDatas = array();
			$this->totalNum = NULL;
			$this->returnNum = NULL;
			$this->startPotision = NULL;
		}
		
		public function addData($data) {
			$this->dbDatas = $data;
		}
		
		public function setTotalNum($num) {
			$this->totalNum = $num;
		}
		
		public function setReturnNum($num) {
			$this->returnNum = $num;
		}
		
		public function setStartPosition($num) {
			$this->startPotision = $num;
		}
		
		public function createXML() {
			if (empty($this->dbDatas) == true) {
				throw new Exception("shop data is empty");
			}
			if (mb_strlen($this->totalNum) == 0) {
				throw new Exception("totalnum is empty");
			} 
			if (mb_strlen($this->returnNum) == 0) {
				throw new Exception("returnnum is empty");
			}
			if (mb_strlen($this->startPotision) == 0) {
				throw new Exception("startpotision is empty");
			}
			
			global $TAG_ORDER;
			global $TAG_TO_COL;
			// add 2016/12/16 H.Yasunaga 出力データの補正 [
			// 半角化処理対象
			global $VALUE_TO_HALF;
			// 数字およびカタカナの全角化
			global $VALUE_TO_FULL;
			// ハイフンの除去(郵便番号)
			global $VALUE_TRIM_HYPHEN;
			// 0落ち項目補正
			global $VALUE_ZERO_CORRECT;
			// 時刻項目補正 hh:mm:ss の ssが無い場合に「00」を追加する
			global $VALUE_TIME_CORRECT;
			// add 2016/12/16 H.Yasunaga ]
			
			try{
				$xmlstr = '<?xml version="1.0" encoding="UTF-8"?><result></result>';
				// ルートのresultエレメント
				$rootElement = simplexml_load_string($xmlstr);
				// レスポンスの情報エレメント
				$resultPropertyElement = $rootElement->addChild("result_property");
				$resultPropertyElement->addChild("result_totalnum", 		$this->totalNum);
				$resultPropertyElement->addChild("result_returnnum", 		$this->returnNum);
				$resultPropertyElement->addChild("result_startposition",	$this->startPotision);
				
				// item_listエレメント
				$itemListElement = $rootElement->addChild("item_list");
				for($i = 0; $i < count($this->dbDatas); $i++) {
					$itemElement = $itemListElement->addChild("item");
					for($j = 0; $j < count($TAG_ORDER); $j++) {
						$tagValue = "";
						$tagName = $TAG_ORDER[$j];
						if (is_array($TAG_TO_COL[$tagName]) == false) {
							$tagValue = isset($this->dbDatas[$i][$TAG_TO_COL[$tagName]]) ? $this->dbDatas[$i][$TAG_TO_COL[$tagName]] : "";
						} else {
							// 併設店フラグ(タグ名:juxtaposition_flag カラム：COL_05・COL_06・COL_07・COL_08）用の処理
							for($k = 0; $k < count($TAG_TO_COL[$tagName]); $k++) {
								// mod 2016/12/16 H.Yasunaga 出力データの補正 [
								// $tagValue .= $this->dbDatas[$i][ $TAG_TO_COL[$tagName][$k] ];
								$tagValue .= $this->trimSpace( $this->dbDatas[$i][ $TAG_TO_COL[$tagName][$k] ] );
								// mod 2016/12/16 H.Yasunaga ]
							}
						}
						// add 2016/12/16 H.Yasunaga 出力データの補正 [
						// 値末尾のスペース除去
						$tagValue = $this->trimSpace($tagValue);
						
						// 半角化
						if (array_key_exists($tagName,  $VALUE_TO_HALF) == true && $VALUE_TO_HALF[$tagName] == true) {
							$tagValue = $this->toHalf($tagValue);
						}
						// 数字およびカタカナの全角化
						if (array_key_exists($tagName, $VALUE_TO_FULL) == true && $VALUE_TO_FULL[$tagName] == true) {
							$tagValue = $this->toFull($tagValue);
						}
						// ハイフンの除去
						if (array_key_exists($tagName, $VALUE_TRIM_HYPHEN) == true && $VALUE_TRIM_HYPHEN[$tagName] == true) {
							$tagValue = $this->trimHyphen($tagValue);
						}
						// 0落ち項目補正
						if (array_key_exists($tagName, $VALUE_ZERO_CORRECT) == true && $VALUE_ZERO_CORRECT[$tagName] > 0) {
							$tagValue = $this->zeroCorrect($tagValue, $VALUE_ZERO_CORRECT[$tagName]);
						}
						// 時刻項目補正 hh:mm:ss の ssが無い場合に「00」を追加する
						if (array_key_exists($tagName, $VALUE_TIME_CORRECT) == true && $VALUE_TIME_CORRECT[$tagName] == true) {
							$tagValue = $this->timeCorrect($tagValue);
						}
						
						// add 2016/12/16 H.Yasunaga ]
						$tagValue = mb_convert_encoding($tagValue, "UTF-8", "EUC-JP");
						// mod start 2016/06/15 H.Yasunaga ENT_HTML401がphp5.4以降の為 [
						// $tagValue = htmlspecialchars($tagValue, ENT_COMPAT | ENT_HTML401 , "UTF-8");
						$tagValue = htmlspecialchars($tagValue, ENT_QUOTES  , "UTF-8");
						// mod end ]
						$tagName = mb_convert_encoding($tagName, "UTF-8", "EUC-JP");
						$itemElement->addChild($tagName, $tagValue);
					}
				}
				// add start 2016/06/27 H.Yasunaga XMLの出力時のフォーマット整形を行うようにする[
				//return $rootElement->asXML();
				$xmlstring = $rootElement->asXML();
				$xmlstring = $this->cleanUpXML($xmlstring);
				return $xmlstring;
				// add end ]
			
			}catch(Exception $exp) {
				return $this->createErrorResponse(5);
			}
		}
		
		public function createErrorResponse($errorNum) {
			$xmlstr = '<?xml version="1.0" encoding="UTF-8"?><error></error>';
			$errorElement = simplexml_load_string($xmlstr);
			$message;
			switch($errorNum) {
				case 1:{
					$message = DEF_RESPONSE_ERROR_TEXT_1;
					break;
				}
				case 2:{
					$message = DEF_RESPONSE_ERROR_TEXT_2;
					break;
				}
				case 3:{
					$message = DEF_RESPONSE_ERROR_TEXT_3;
					break;
				}
				case 4:{
					$message = DEF_RESPONSE_ERROR_TEXT_4;
					break;
				}
				case 5:
				default:{
					$message = DEF_RESPONSE_ERROR_TEXT_5;
				}
			}
			$errorElement->addChild("message" ,$message);
			// add start 2016/06/27 H.Yasunaga XMLの出力時のフォーマット整形を行うようにする[
			//return $errorElement->asXML();
			$xmlstring = $errorElement->asXML();
			$xmlstring = $this->cleanUpXML($xmlstring);
			return $xmlstring;
			// add end ]
		}
		
		// add start 2016/06/27 H.Yasunaga 出力するXMLをフォーマットする [
		// 参考ページ：http://qiita.com/suin/items/6d0032fe7ecc140395d8
		public function cleanUpXML($string) {
		 	$string = preg_replace("/>\s*</", ">\n<", $string);
			$lines	= explode("\n", $string);
			$string = '';
			$indent = 0;
			
			$lines2 = array();
			for($i = 0; $i < count($lines); $i++) {
				if (isset($lines[$i]) == true && isset($lines[$i + 1]) == true) {
					// $i と $i + 1 があるからif文へ
					if (mb_strpos($lines[$i],     "<",  0, "UTF-8") === 0 && 
						mb_strpos($lines[$i],     ">",  0, "UTF-8") === (mb_strlen($lines[$i], "UTF-8") -1 ) &&
						mb_strpos($lines[$i],     "/>", 0, "UTF-8") === false &&
						mb_strpos($lines[$i],     "</", 0, "UTF-8") === false &&
						mb_strpos($lines[$i + 1], "</", 0, "UTF-8") === 0 &&
						mb_strpos($lines[$i + 1], ">",  0, "UTF-8") === (mb_strlen($lines[$i + 1], "UTF-8") -1 ) &&
						mb_strpos($lines[$i + 1], "/>", 0, "UTF-8") === false
					) {
						$lines2[] = $lines[$i] . $lines[$i + 1];
						$i++;
					} else {
						$lines2[] = $lines[$i];
					}
				} else if (isset($lines[$i]) == true && isset($lines[$i + 1]) == false) {
					// +1 がないから単純に追加
					if (empty($lines[$i]) === false) {
						$lines2[] = $lines[$i];
					}
				}
			}

			//foreach ( $lines as $line )
			foreach ( $lines2 as $line )
			{
				$increment = false;
				$decrement = false;

				if ( preg_match('#<\?xml.+\?>#', $line) == true )
				{
					// <?xml … 
				}
				elseif ( preg_match('#<[^/].+>.*</.+>#', $line) == true )
				{
					// Open Tag & Close Tag
				}
				elseif ( preg_match('#<.+/>#', $line) == true )
				{
					// Self-closing Tag
				}
				elseif ( preg_match('#<!.*>#', $line) == true )
				{
					// Comments and CDATA
				}
				elseif ( preg_match('#<[^/].+>#', $line) == true )
				{
					// Open Tag
					$increment = true;
				}
				elseif ( preg_match('#</.+>#', $line) == true )
				{
					// Close Tag
					$decrement = true;
				}
				else
				{
					// Others
				}

				if ( $decrement === true )
				{
					$indent -= 1;
				}

				$string .= str_repeat("\t", $indent).$line."\n";

				if ( $increment === true )
				{
					$indent += 1;
				}
			}

			return $string;
		}
		// add end ]
		
		// add 2016/12/16 H.Yasunaga 出力項目の補正処理の追加 [
		// 末尾スペース(半角/全角)除去
		function trimSpace($target) {
			// preg_replace('/[ 　]+$/', '', $target);
			// preg_replaceを使うと末尾が'院'の字だと欠落がおきる為マルチバイト対応の関数を使う
			return mb_ereg_replace("[ 　]+$", '', $target);
		}
		
		// ハイフン除去
		function trimHyphen($target) {
			$reprace = array('‐', '-');
			return str_replace($reprace, '', $target);
		}
		
		// 0埋め桁数補正
		function zeroCorrect($target, $digits) {
			return str_pad($target, $digits, 0, STR_PAD_LEFT);
		}
		
		// 時刻補正 hh:mm:ssのssが無い場合
		function timeCorrect($target) {
			// hh:mm:ss 形式であるか確認
			if (preg_match('/^[0-9]{2}:[0-9]{2}:[0-9]{2}$/', $target) === 1) {
				// 時刻のフォーマット正しい
				return $target;
			} else {
				// hh:mm:ss形式でない
				if (strlen($target) == 5) {
					// hh:mm
					$splited = explode(':', $target);
					if (count($splited) > 1) {
						return $splited[0] . ":" . $splited[1] . ":00";
					} else {
						return $target;
					}
				}else {
					return $target;
				}
			}
		}
		
		// 数字と「：」の半角化
		function toHalf($target) {
			return mb_convert_kana($target, "a");
		}
		
		// 数字とカタカナの全角化
		function toFull($target) {
			return mb_convert_kana($target, "NKV");
		}
		// add 2016/12/16 H.Yasunaga ]
	}
?>