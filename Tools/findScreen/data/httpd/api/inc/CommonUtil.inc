<?php
// ------------------------------------------------------------
// API�������ġ��붦�̽���
// 
// 2016/06/14 H.Yasunaga	��������
// 2017/01/24 H.Yasunaga	API�Υ������ϤΥե�����̾�����������դ���Ϳ
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/define.inc");
	require_once(dirname(__FILE__) . "/htmltemplate.inc");

	class CommonUtil{
		/*
		*	��ǽ	API���ѻ���DB��Ͽ���ε��Ĥ��줿IP���ɥ쥹�ޤ��ϡ�API���������������Υ����å�
		*	����	$apiAccessKey:API������������
		*			$ipaddress:IP���ɥ쥹
		*	�����	true:DB��Ͽ�����Ĥ˰���
		*			false:DB��Ͽ�����Ĥ��԰���
		*/
		// del start 2016/06/23 H.Yasunaga ���פʤ����� [
		//public static function checkSpecialPermission($apiAccessKey, $ipaddress) {
		//	$ret = false;
		//	global $ALLOW_APIKEY_IP;
		//	if (array_key_exists($apiAccessKey, $ALLOW_APIKEY_IP)) {
		//		if ($ALLOW_APIKEY_IP[$apiAccessKey] == $ipaddress) {
		//			$ret = true;
		//		}
		//	}
		//	return $ret;
		//}
		// del end ]
		
		public static function checkAllowIp($remoteAddress) {
			global $ALLOW_MANAGE_IP;
			return in_array($remoteAddress, $ALLOW_MANAGE_IP);
		}
		
		/*
		*	��ǽ	��������(API¦)
		*	����	$message:����ʸ���� or ����
		*			$message2:����ʸ���� or ����
		*	�����	�ʤ�
		*/
		public static function api_log($message, $message2 = null) {
			$tmp = CommonUtil::formatMessage($message);
			if (is_null($message2) == false) {
				$tmp .= "\n" . CommonUtil::formatMessage($message2);
			}
			
			// mod start 2017/01/24 H.Yasunaga �����ե�����̾��������"yyyymmdd(ǯ����)"����Ϳ
			//error_log("[" . date("Y/m/d H:i:s") . "]" . " [" . $_SERVER['REMOTE_ADDR'] ."] " .  $tmp . "\n", 3, "/var/tmp/jppostapi-error_log");
			error_log("[" . date("Y/m/d H:i:s") . "]" . " [" . $_SERVER['REMOTE_ADDR'] ."] " .  $tmp . "\n", 3, "/var/tmp/jppostapi-error_log." . date("Ymd"));
			// mod end ]
		}
		
		/*
		*	��ǽ	��������(����¦)
		*	����	$message:����ʸ���� or ����
		*			$message2:����ʸ���� or ����
		*	�����	�ʤ�
		*/
		public static function manage_log($message, $message2 = null) {
			$tmp = CommonUtil::formatMessage($message);
			if (is_null($message2) == false) {
				$tmp .= "\n" . CommonUtil::formatMessage($message2);
			}
			error_log("[" . date("Y/m/d H:i:s") . "]" . " [" . $_SERVER['REMOTE_ADDR'] ."] " .  $tmp . "\n", 3, "/var/tmp/jppostapimanage-error_log");
		}
		
		/*
		*	��ǽ	�������ϤΥե����ޥå�
		*			�����Ÿ������
		*	����	$message:ʸ���� or ����
		*	�����	ʸ����
		*/
		protected static function formatMessage($message) {
			if (is_array($message) == false) {
				return $message;
			} else {
				$ret = "";
				foreach($message as $key=>$value) {
					$ret .= "[" . $key . "] = " . $value . "\n";
				}
				return $ret;
			}
		}
		
		public static function validate($username, $mail, $apiAccessKey, $valid, $ipAddress, $note, $option) {
			
			$ret = array(
						'error'			=> false,
						'username'		=> '',
						'mail'			=> '',
						'apiaccesskey'	=> '',
						'valid'			=> '',
						'ipaddress'		=> '',
						'note'			=> '',
			);
			
			if ($option & Validate_Option::OPTION_USERNAME) {
				if (empty($username)) {
					$ret['error'] = true;
					$ret['username'] = "USERNAME�����Ǥ���";
				} else if (mb_strlen($username) > 30) {
					$ret['error'] = true;
					$ret['username'] = "USERNAME��30ʸ�����⡣";
				}
			}
			
			if ($option & Validate_Option::OPTION_MAIL) {
				if (empty($mail)) {
					$ret['error'] = true;
					$ret['mail'] = "MAIL�����Ǥ���";
				} else if (!filter_var($mail, FILTER_VALIDATE_EMAIL)) {
					$ret['error'] = true;
					$ret['mail'] = "�����������Ǥ���";
				}
			}
			
			if ($option & Validate_Option::OPTION_APIACCESSKEY) {
				if (empty($apiAccessKey)) {
					$ret['error'] = true;
					$ret['apiaccesskey'] = "APIACCESSKEY�����Ǥ�";
				} else if (!mb_ereg_match("^[a-zA-Z]{30}$", $apiAccessKey)) {
					$ret['error'] = true;
					$ret['apiaccesskey'] = "APIACCESSKEY�η����������Ǥ���";
				}
			}
			
			if ($option & Validate_Option::OPTION_VALID) {
				if (empty($valid)) {
					$ret['error'] = true;
					$ret['valid'] = "VALID�����Ǥ���";
				} else if ($valid !== "1" && $valid !== "0") {
					$ret['error'] = true;
					$ret['valid'] = "�ͤ������Ǥ���";
				}
			}
			
			if ($option & Validate_Option::OPTION_IPADDRESS) {
				if (empty($ipAddress)) {
					$ret['error'] = true;
					$ret['ipaddress'] = "IPADDRESS�����Ǥ���";
				} else if (!filter_var($ipAddress, FILTER_VALIDATE_IP)) {
					$ret['error'] = true;
					$ret['ipaddress'] = "IPADDRESS�������Ǥ���";
				}
			}
			if ($option & Validate_Option::OPTION_NOTE) {
				if (mb_strlen($note) > 100) {
					$ret['error'] = true;
					$ret['note'] = "NOTE��100ʸ���ޤǤǤ���";
				}
			}
			
			return $ret;
		}
		
		/*
		*	��ǽ	IPADDRESS�����å�
		*			192.168.1.1�����̾��IP���ɥ쥹��0��255.0��255.0��255.0��255)
		*			192.168.1.1*���κǸ�Υ����ƥåȤ�*ɽ��
		*	����	$str:�����å��о�ʸ���� or ʸ��������
		*	�����	true:�����IP���ɥ쥹 false:�۾�
		*/
		public static function validateIpAddress($str) {
			if (is_array($str) == true) {
				$emptyCount = 0;
				$matchCount = 0;
				for($i = 0; $i < count($str); $i++) {
					if ($str[$i] == '*') {
						$matchCount++;
						continue;
					}
					if (empty($str[$i])) {
						$emptyCount++;
						continue;
					}
					if (preg_match("/^(([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([1-9]?[0-9*]|1[0-9][0-9*]|2[0-4][0-9*]|25[0-5*])$/", $str[$i]) !== 1) {
						return false;
					} else {
						$matchCount++;
					}
				}
				
				if (count($str) - $emptyCount == $matchCount) {
					return true;
				} else {
					return false;
				}
			} else {
				if ($str == '*') {
					return true;
				}
				
				if (preg_match("/^(([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]).){3}([1-9]?[0-9*]|1[0-9][0-9*]|2[0-4][0-9*]|25[0-5*])$/", $str) === 1) {
					return true;
				} else {
					return false;
				}
			}
		}
		
		/*
		*	��ǽ	html�Υ��������׽����ʼ�˥ƥ�ץ졼�Ȥ�Ŭ�Ѥ����ѿ��򥨥������פ���Τ˻���)
		*			�ü�ʸ��+���󥰥륯������+���֥륯�����Ȥ򥨥�������
		*	����	$str:���������׽����о�ʸ����
		*	�����	���������׷��ʸ����
		*/
		public static function htmlEscape($str) {
			return htmlspecialchars($str, ENT_QUOTES, 'EUC-jp');
		}
		
		/*
		*	��ǽ	htmltemplate��Ȥä�html���Ϥ����Хإå�������
		*	����	$templateFile:�ƥ�ץ졼�ȥե�����ѥ�
		*			$tpl:�ƥ�ץ졼�Ȥ�Ŭ�Ѥ����ͤ�����
		*	�����	�ʤ�
		*/
		public static function outputHtml($templateFile, $tpl) {
			header('X-Frame-Options:DENY');				// ����å�����å��󥰹����к� �����Υ����Ȥ���iframe��ȤäƸƤФ������ɤ���
			header('X-XSS-Protection:1; mode=block');	// XSS�ե��륿��ON
			header("Content-Security-Policy: default-src 'self'");	// Content Security Policy XSS������å�����å����к��� ����饤���javascript�ȥ������륷���Ȥ�̵���������
			
			if (!is_file($templateFile)) return;
			$html = @HtmlTemplate::t_buffer($templateFile, $tpl);
			echo $html;
		}
	}
	
	class Validate_Option {
		
		// �������å�
		const OPTION_ALL			= 0x111111;
		// USERNAME�����å�
		const OPTION_USERNAME		= 0x000001;
		// MAIL�����å�
		const OPTION_MAIL			= 0x000010;
		// APIACCESSKEY�����å�
		const OPTION_APIACCESSKEY	= 0x000100;
		// VALID�����å�
		const OPTION_VALID			= 0x001000;
		// IPADDRESS�����å�
		const OPTION_IPADDRESS		= 0x010000;
		// NOTE�����å�
		const OPTION_NOTE			= 0x100000;
		
	}
?>