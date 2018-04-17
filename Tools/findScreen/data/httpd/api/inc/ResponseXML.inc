<?php
// ------------------------------------------------------------
// API�쥹�ݥ�XML����
// 
// 2016/06/14 H.Yasunaga	��������
// 2016/06/15 H.Yasunaga	htmlspecialchars�����Υե饰����
// 2016/06/27 H.Yasunaga	���Ϥ���XML��ե����ޥåȤ��뽤��
// 2016/12/16 H.Yasunaga	���Ϥ���ǡ��������������ɲ�
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/ResponseTag.inc");
	// add 2016/12/16 H.Yasunaga ���ϥǡ��������� [
	require_once(dirname(__FILE__) . "/Value_Correction.inc");
	// add 2016/12/16 H.Yasunaga]
	
	// ���顼No1 �����ꥯ�����ȹ��ܤ��ͤ����äƤ��ʤ�������������
	define("DEF_RESPONSE_ERROR_TEXT_1", "invalid_parameter_value");
	// ���顼No2 ���������������ͤ����äƤ��ʤ�����������
	define("DEF_RESPONSE_ERROR_TEXT_2", "invalid_key_value");
	// ���顼No3 IP���ɥ쥹���ͤ���������������ɳ�Ť����ͤǤϤʤ�������������
	define("DEF_RESPONSE_ERROR_TEXT_3", "invalid_ipaddress_value");
	// ���顼No4 ��������ǡ�����1���ʤ�
	define("DEF_RESPONSE_ERROR_TEXT_4", "item_not_found");
	// ���顼No5 �嵭�ʳ��Υ��顼(��������λ�Ǥ��ʤ����)
	define("DEF_RESPONSE_ERROR_TEXT_5", "internal_server_error");
	
	class ResponseXML{
		// Ź�޾���(DB����Υǡ���)
		private $dbDatas;
		// ������̷��
		private $totalNum;
		// �ֵѷ�̷��
		private $returnNum;
		// �ֵѷ�̳��ϰ���
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
			// add 2016/12/16 H.Yasunaga ���ϥǡ��������� [
			// Ⱦ�Ѳ������о�
			global $VALUE_TO_HALF;
			// ��������ӥ������ʤ����Ѳ�
			global $VALUE_TO_FULL;
			// �ϥ��ե�ν���(͹���ֹ�)
			global $VALUE_TRIM_HYPHEN;
			// 0�����������
			global $VALUE_ZERO_CORRECT;
			// ����������� hh:mm:ss �� ss��̵�����ˡ�00�פ��ɲä���
			global $VALUE_TIME_CORRECT;
			// add 2016/12/16 H.Yasunaga ]
			
			try{
				$xmlstr = '<?xml version="1.0" encoding="UTF-8"?><result></result>';
				// �롼�Ȥ�result�������
				$rootElement = simplexml_load_string($xmlstr);
				// �쥹�ݥ󥹤ξ��󥨥����
				$resultPropertyElement = $rootElement->addChild("result_property");
				$resultPropertyElement->addChild("result_totalnum", 		$this->totalNum);
				$resultPropertyElement->addChild("result_returnnum", 		$this->returnNum);
				$resultPropertyElement->addChild("result_startposition",	$this->startPotision);
				
				// item_list�������
				$itemListElement = $rootElement->addChild("item_list");
				for($i = 0; $i < count($this->dbDatas); $i++) {
					$itemElement = $itemListElement->addChild("item");
					for($j = 0; $j < count($TAG_ORDER); $j++) {
						$tagValue = "";
						$tagName = $TAG_ORDER[$j];
						if (is_array($TAG_TO_COL[$tagName]) == false) {
							$tagValue = isset($this->dbDatas[$i][$TAG_TO_COL[$tagName]]) ? $this->dbDatas[$i][$TAG_TO_COL[$tagName]] : "";
						} else {
							// ʻ��Ź�ե饰(����̾:juxtaposition_flag ����ࡧCOL_05��COL_06��COL_07��COL_08���Ѥν���
							for($k = 0; $k < count($TAG_TO_COL[$tagName]); $k++) {
								// mod 2016/12/16 H.Yasunaga ���ϥǡ��������� [
								// $tagValue .= $this->dbDatas[$i][ $TAG_TO_COL[$tagName][$k] ];
								$tagValue .= $this->trimSpace( $this->dbDatas[$i][ $TAG_TO_COL[$tagName][$k] ] );
								// mod 2016/12/16 H.Yasunaga ]
							}
						}
						// add 2016/12/16 H.Yasunaga ���ϥǡ��������� [
						// �������Υ��ڡ�������
						$tagValue = $this->trimSpace($tagValue);
						
						// Ⱦ�Ѳ�
						if (array_key_exists($tagName,  $VALUE_TO_HALF) == true && $VALUE_TO_HALF[$tagName] == true) {
							$tagValue = $this->toHalf($tagValue);
						}
						// ��������ӥ������ʤ����Ѳ�
						if (array_key_exists($tagName, $VALUE_TO_FULL) == true && $VALUE_TO_FULL[$tagName] == true) {
							$tagValue = $this->toFull($tagValue);
						}
						// �ϥ��ե�ν���
						if (array_key_exists($tagName, $VALUE_TRIM_HYPHEN) == true && $VALUE_TRIM_HYPHEN[$tagName] == true) {
							$tagValue = $this->trimHyphen($tagValue);
						}
						// 0�����������
						if (array_key_exists($tagName, $VALUE_ZERO_CORRECT) == true && $VALUE_ZERO_CORRECT[$tagName] > 0) {
							$tagValue = $this->zeroCorrect($tagValue, $VALUE_ZERO_CORRECT[$tagName]);
						}
						// ����������� hh:mm:ss �� ss��̵�����ˡ�00�פ��ɲä���
						if (array_key_exists($tagName, $VALUE_TIME_CORRECT) == true && $VALUE_TIME_CORRECT[$tagName] == true) {
							$tagValue = $this->timeCorrect($tagValue);
						}
						
						// add 2016/12/16 H.Yasunaga ]
						$tagValue = mb_convert_encoding($tagValue, "UTF-8", "EUC-JP");
						// mod start 2016/06/15 H.Yasunaga ENT_HTML401��php5.4�ʹߤΰ� [
						// $tagValue = htmlspecialchars($tagValue, ENT_COMPAT | ENT_HTML401 , "UTF-8");
						$tagValue = htmlspecialchars($tagValue, ENT_QUOTES  , "UTF-8");
						// mod end ]
						$tagName = mb_convert_encoding($tagName, "UTF-8", "EUC-JP");
						$itemElement->addChild($tagName, $tagValue);
					}
				}
				// add start 2016/06/27 H.Yasunaga XML�ν��ϻ��Υե����ޥå�������Ԥ��褦�ˤ���[
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
			// add start 2016/06/27 H.Yasunaga XML�ν��ϻ��Υե����ޥå�������Ԥ��褦�ˤ���[
			//return $errorElement->asXML();
			$xmlstring = $errorElement->asXML();
			$xmlstring = $this->cleanUpXML($xmlstring);
			return $xmlstring;
			// add end ]
		}
		
		// add start 2016/06/27 H.Yasunaga ���Ϥ���XML��ե����ޥåȤ��� [
		// ���ͥڡ�����http://qiita.com/suin/items/6d0032fe7ecc140395d8
		public function cleanUpXML($string) {
		 	$string = preg_replace("/>\s*</", ">\n<", $string);
			$lines	= explode("\n", $string);
			$string = '';
			$indent = 0;
			
			$lines2 = array();
			for($i = 0; $i < count($lines); $i++) {
				if (isset($lines[$i]) == true && isset($lines[$i + 1]) == true) {
					// $i �� $i + 1 �����뤫��ifʸ��
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
					// +1 ���ʤ�����ñ����ɲ�
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
					// <?xml �� 
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
		
		// add 2016/12/16 H.Yasunaga ���Ϲ��ܤ������������ɲ� [
		// �������ڡ���(Ⱦ��/����)����
		function trimSpace($target) {
			// preg_replace('/[ ��]+$/', '', $target);
			// preg_replace��Ȥ���������'��'�λ����ȷ��������٥ޥ���Х����б��δؿ���Ȥ�
			return mb_ereg_replace("[ ��]+$", '', $target);
		}
		
		// �ϥ��ե����
		function trimHyphen($target) {
			$reprace = array('��', '-');
			return str_replace($reprace, '', $target);
		}
		
		// 0���������
		function zeroCorrect($target, $digits) {
			return str_pad($target, $digits, 0, STR_PAD_LEFT);
		}
		
		// �������� hh:mm:ss��ss��̵�����
		function timeCorrect($target) {
			// hh:mm:ss �����Ǥ��뤫��ǧ
			if (preg_match('/^[0-9]{2}:[0-9]{2}:[0-9]{2}$/', $target) === 1) {
				// ����Υե����ޥå�������
				return $target;
			} else {
				// hh:mm:ss�����Ǥʤ�
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
		
		// �����ȡ֡��פ�Ⱦ�Ѳ�
		function toHalf($target) {
			return mb_convert_kana($target, "a");
		}
		
		// �����ȥ������ʤ����Ѳ�
		function toFull($target) {
			return mb_convert_kana($target, "NKV");
		}
		// add 2016/12/16 H.Yasunaga ]
	}
?>