<?php
// ------------------------------------------------------------
// API・管理ツール共通処理
// 
// 2016/06/14 H.Yasunaga	新規作成
// 2017/01/24 H.Yasunaga	APIのログ出力のファイル名の末尾に日付を付与
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/define.inc");
	require_once(dirname(__FILE__) . "/htmltemplate.inc");

	class CommonUtil{
		/*
		*	機能	API利用時のDB登録外の許可されたIPアドレスまたは、APIアクセスキーかのチェック
		*	引数	$apiAccessKey:APIアクセスキー
		*			$ipaddress:IPアドレス
		*	戻り値	true:DB登録外許可に一致
		*			false:DB登録外許可に不一致
		*/
		// del start 2016/06/23 H.Yasunaga 不要なため削除 [
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
		*	機能	ログ出力(API側)
		*	引数	$message:出力文字列 or 配列
		*			$message2:出力文字列 or 配列
		*	戻り値	なし
		*/
		public static function api_log($message, $message2 = null) {
			$tmp = CommonUtil::formatMessage($message);
			if (is_null($message2) == false) {
				$tmp .= "\n" . CommonUtil::formatMessage($message2);
			}
			
			// mod start 2017/01/24 H.Yasunaga ログファイル名の末尾に"yyyymmdd(年月日)"を付与
			//error_log("[" . date("Y/m/d H:i:s") . "]" . " [" . $_SERVER['REMOTE_ADDR'] ."] " .  $tmp . "\n", 3, "/var/tmp/jppostapi-error_log");
			error_log("[" . date("Y/m/d H:i:s") . "]" . " [" . $_SERVER['REMOTE_ADDR'] ."] " .  $tmp . "\n", 3, "/var/tmp/jppostapi-error_log." . date("Ymd"));
			// mod end ]
		}
		
		/*
		*	機能	ログ出力(管理側)
		*	引数	$message:出力文字列 or 配列
		*			$message2:出力文字列 or 配列
		*	戻り値	なし
		*/
		public static function manage_log($message, $message2 = null) {
			$tmp = CommonUtil::formatMessage($message);
			if (is_null($message2) == false) {
				$tmp .= "\n" . CommonUtil::formatMessage($message2);
			}
			error_log("[" . date("Y/m/d H:i:s") . "]" . " [" . $_SERVER['REMOTE_ADDR'] ."] " .  $tmp . "\n", 3, "/var/tmp/jppostapimanage-error_log");
		}
		
		/*
		*	機能	ログ出力のフォーマット
		*			配列を展開する
		*	引数	$message:文字列 or 配列
		*	戻り値	文字列
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
					$ret['username'] = "USERNAMEが空です。";
				} else if (mb_strlen($username) > 30) {
					$ret['error'] = true;
					$ret['username'] = "USERNAMEは30文字以内。";
				}
			}
			
			if ($option & Validate_Option::OPTION_MAIL) {
				if (empty($mail)) {
					$ret['error'] = true;
					$ret['mail'] = "MAILが空です。";
				} else if (!filter_var($mail, FILTER_VALIDATE_EMAIL)) {
					$ret['error'] = true;
					$ret['mail'] = "形式が不正です。";
				}
			}
			
			if ($option & Validate_Option::OPTION_APIACCESSKEY) {
				if (empty($apiAccessKey)) {
					$ret['error'] = true;
					$ret['apiaccesskey'] = "APIACCESSKEYが空です";
				} else if (!mb_ereg_match("^[a-zA-Z]{30}$", $apiAccessKey)) {
					$ret['error'] = true;
					$ret['apiaccesskey'] = "APIACCESSKEYの形式が不正です。";
				}
			}
			
			if ($option & Validate_Option::OPTION_VALID) {
				if (empty($valid)) {
					$ret['error'] = true;
					$ret['valid'] = "VALIDが空です。";
				} else if ($valid !== "1" && $valid !== "0") {
					$ret['error'] = true;
					$ret['valid'] = "値が不正です。";
				}
			}
			
			if ($option & Validate_Option::OPTION_IPADDRESS) {
				if (empty($ipAddress)) {
					$ret['error'] = true;
					$ret['ipaddress'] = "IPADDRESSが空です。";
				} else if (!filter_var($ipAddress, FILTER_VALIDATE_IP)) {
					$ret['error'] = true;
					$ret['ipaddress'] = "IPADDRESSが不正です。";
				}
			}
			if ($option & Validate_Option::OPTION_NOTE) {
				if (mb_strlen($note) > 100) {
					$ret['error'] = true;
					$ret['note'] = "NOTEは100文字までです。";
				}
			}
			
			return $ret;
		}
		
		/*
		*	機能	IPADDRESSチェック
		*			192.168.1.1等の通常のIPアドレス（0〜255.0〜255.0〜255.0〜255)
		*			192.168.1.1*等の最後のオクテットの*表現
		*	引数	$str:チェック対象文字列 or 文字列配列
		*	戻り値	true:正常なIPアドレス false:異常
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
		*	機能	htmlのエスケープ処理（主にテンプレートに適用する変数をエスケープするのに使用)
		*			特殊文字+シングルクォート+ダブルクォートをエスケープ
		*	引数	$str:エスケープ処理対象文字列
		*	戻り値	エスケープ結果文字列
		*/
		public static function htmlEscape($str) {
			return htmlspecialchars($str, ENT_QUOTES, 'EUC-jp');
		}
		
		/*
		*	機能	htmltemplateを使ったhtml出力と送出ヘッダの設定
		*	引数	$templateFile:テンプレートファイルパス
		*			$tpl:テンプレートに適用する値の配列
		*	戻り値	なし
		*/
		public static function outputHtml($templateFile, $tpl) {
			header('X-Frame-Options:DENY');				// クリックジャッキング攻撃対策 外部のサイトからiframeを使って呼ばれる事を防ぐ。
			header('X-XSS-Protection:1; mode=block');	// XSSフィルタのON
			header("Content-Security-Policy: default-src 'self'");	// Content Security Policy XSS、クリックジャッキング対策。 インラインのjavascriptとスタイルシートが無効化される
			
			if (!is_file($templateFile)) return;
			$html = @HtmlTemplate::t_buffer($templateFile, $tpl);
			echo $html;
		}
	}
	
	class Validate_Option {
		
		// 全チェック
		const OPTION_ALL			= 0x111111;
		// USERNAMEチェック
		const OPTION_USERNAME		= 0x000001;
		// MAILチェック
		const OPTION_MAIL			= 0x000010;
		// APIACCESSKEYチェック
		const OPTION_APIACCESSKEY	= 0x000100;
		// VALIDチェック
		const OPTION_VALID			= 0x001000;
		// IPADDRESSチェック
		const OPTION_IPADDRESS		= 0x010000;
		// NOTEチェック
		const OPTION_NOTE			= 0x100000;
		
	}
?>