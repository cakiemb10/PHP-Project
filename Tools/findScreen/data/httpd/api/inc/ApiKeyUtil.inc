<?php
// ------------------------------------------------------------
// アクセスキー関連処理
// 
// 2016/06/14 H.Yasunaga	新規作成
// ------------------------------------------------------------
require_once(dirname(__FILE__) . "/define.inc");
require_once(dirname(__FILE__) . "/CommonUtil.inc");

	class ApiKeyUtil{
		
		/* 
		* 	機能	APIキー存在チェック
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$apiAccessKey:確認するAPIアクセスキー文字列
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true=APIキーが存在する false=APIキーが存在しない
		*/
		public static function ExistsApiKey($db, $apiAccessKey, &$internalErrorFlg, &$errorMsg) {
			$ret = false;
			$sql = "select COUNT(*) as CNT from " . API_KEY_TABLE . " where APIACCESSKEY=:apikey";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":apikey", $apiAccessKey, -1) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->getRecInto($stid, $data, OCI_ASSOC) ) {
				if ($data['CNT'] == '1') {
					$ret = true;
				}
			} else {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	機能	メールアドレスをキーにデータ取得
		*/
		public static function getDataByMail($db, $mail, &$internalErrorFlg, &$errorMsg) {
			$sql =  " select USERNAME, MAIL, APIACCESSKEY, to_char(DATEOFISSUE,  'YYYY/MM/DD HH24:MI:SS') AS DATEOFISSUE, VALID, IPADDRESS, NOTE, to_char(UPDATE_DATE,  'YYYY/MM/DD HH24:MI:SS') as UPDATE_DATE  from " . API_KEY_TABLE;
			$sql .= " where MAIL = :mail";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":mail", $mail, -1) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->getRecInto($stid, $data, OCI_ASSOC) ) {
				$ret = $data;
			}else {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	機能	全データ取得
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時:配列
		*			失敗時:false
		*/
		public static function getAllData($db, &$internalErrorFlg, &$errorMsg) {
			$sql = " select USERNAME, MAIL, APIACCESSKEY, to_char(DATEOFISSUE,  'YYYY/MM/DD HH24:MI') AS DATEOFISSUE, VALID, IPADDRESS, NOTE, to_char(UPDATE_DATE,  'YYYY/MM/DD HH24:MI') as UPDATE_DATE  from " . API_KEY_TABLE . " order by DATEOFISSUE asc";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			
			$ret = array();
			if ($db->execute($stid)) {
				while($db->getRecInto($stid, $data, OCI_ASSOC)) {
					$ret[] = $data;
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	機能	APIアクセスキー一覧の取得
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 配列 keyは0〜xxx valueはAPIアクセスキー
		*			失敗時 false
		*/
		public static function getApiKeys($db, &$internalErrorFlg, &$errorMsg) {
			$sql = "select APIACCESSKEY from " . API_KEY_TABLE;
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			$ret = array();
			if ($db->execute($stid)) {
				while($db->getRecInto($stid, $data, OCI_ASSOC)) {
					$ret[] = $data['APIACCESSKEY'];
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$db->free($stid);
			return $ret;
		}
		
		/*
		* 	機能	APIアクセスキー有効チェック
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$apiAccessKey:確認するAPIアクセスキー文字列
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true=APIアクセスキーが有効 false:APIアクセスキーが無効
		*/ 
		public static function apiKeyValidation($db, $apiAccessKey, &$internalErrorFlg, &$errorMsg) {
			$ret = false;
			$sql = " select VALID from " . API_KEY_TABLE . " where APIACCESSKEY=:apikey";
			
			$stid = $db->parse($sql);
			if ($stid === false) {
				$errorMsg = $db->getError($db->conn);
				$internalErrorFlg = true;
				return false;
			}
			if ($db->bindByName($stid, ":apikey", $apiAccessKey, -1) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->getRecInto($stid, $data, OCI_ASSOC) ) {
				if ($data['VALID'] == '1') {
					$ret = true;
				}
			} else {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			
			$internalErrorFlg = false;
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	機能	APIアクセスキーに紐づいているIPアドレスのチェック
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$apiAccessKey:APIアクセスキー文字列
		*			$ipAddress:接続元IPアドレス(チェック対象)
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true=登録されているIPアドレスと一致 false=登録されているIPアドレスと不一致
		*/
		public static function checkIpAddress($db, $apiAccessKey, $ipAddress, &$internalErrorFlg, &$errorMsg) {
			$ret = false;
			$sql = "select IPADDRESS from " . API_KEY_TABLE . " where APIACCESSKEY=:apikey";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$errorMsg = $db->getError($db->conn);
				$internalErrorFlg = true;
				return false;
			}
			if ($db->bindByName($stid, ":apikey", $apiAccessKey, -1) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false) {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			if ($db->getRecInto($stid, $data, OCI_ASSOC) ) {
				// DBに登録されているカンマ区切りIPアドレスを配列に
				// ex.) 192.168.1.1,192.168.1.2→ [0]=192.168.1.1;[1]=192.168.1.2
				$ipaddressAry = explode(",", $data['IPADDRESS']);
				for($i = 0; $i < count($ipaddressAry); $i++) {
					if ($ipaddressAry[$i] == "*") {
						// '*'のみは全許可
						$ret = true;
						break;
					}
					else if ($ipaddressAry[$i] === $ipAddress) {
						// アスターなしで一致
						$ret = true;
						break;
					} else {
						// アスターの位置
						$asterpos = mb_strpos($ipaddressAry[$i], "*");
						// アスターを含んだIPアドレスの文字列長
						$paternlen = mb_strlen($ipaddressAry[$i]);
						// 引数のIPアドレスの文字列長
						$iplen = mb_strlen($ipAddress);
						/* 確認用
						error_log("ipaddress:[" . $ipAddress ."]");
						error_log("patern:[" . $ipaddressAry[$i] . "]");
						error_log("asterpos:[" . $asterpos . "]");
						error_log("patertnlen:[" . $paternlen . "]");
						error_log("iplen:[" . $iplen . "]");
						*/
						
						// アスターが含まれかつアスターが末尾であるかつ文字列長がおなじであるか？
						if ($asterpos !== false && $asterpos == ($paternlen - 1) && $iplen == $paternlen) {
							// アスターの前までを取り出し
							$preaster = mb_substr($ipaddressAry[$i], 0, $asterpos);
							// アスターの前までの文字列が引数のIPアドレスに先頭から一致するか？
							if (mb_strpos($ipAddress, $preaster) === 0) {
								// 先頭から*前まで同じ
								$ret = true;
								break;
							}
						}
					}
				}
			}else {
				$errorMsg = $db->getError($stid);
				$internalErrorFlg = true;
				$db->free($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	機能	ランダムなAPIアクセスキーの生成（既存APIアクセスキーとのチェック有）
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			&$internalErrorFlg:true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*			$length:APIアクセスキー文字列の長さ(デフォルト30)
		*	戻り値	生成したAPIアクセスキー
		*/
		public static function createApiKey($db, &$internalErrorFlg, &$errorMsg, $length=30) {
			do{
				$apiKey = substr(str_shuffle(str_repeat('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ', $length)), 0, $length);
				if (ApiKeyUtil::ExistsApiKey($db, $apiKey, &$inError, &$errMsg) === false)
				{
					$errorMsg = $errMsg;
					$internalErrorFlg = $inError;
					break;
				}
			}while(true);
			return $apiKey;
		}
		
		/*
		*	機能	APIアクセスキーの形式チェック
		*	引数	$target:確認するAPIアクセスキー文字列
		*	戻り値	正しい:true 不正:false
		*/
		public static function isApiKey($target) {
			return mb_ereg_match("^[a-zA-Z]{30}$", $target);
		}
		
		/* 
		* 	機能	APIキー存在チェック
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$mail:確認するMAIL文字列
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true=APIキーが存在する false=APIキーが存在しない
		*/
		public static function existsEmail($db, $mail, &$internalErrorFlg, &$errorMsg) {
			$ret = false;
			$sql = "select count(*) as CNT from " . API_KEY_TABLE . " where MAIL=:mail";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":mail", $mail, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if ($db->getRecInto($stid, $data, OCI_ASSOC) ) {
				if ($data['CNT'] == '1') {
					$ret = true;
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	機能	APIアクセスキーの有効無効切り替え
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$newvalid:変更するするVALIDの値
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*/
		public static function changeValid($db, $mail, $newvalid, &$internalErrorFlg, &$errorMsg) {
			$sql = " update " . API_KEY_TABLE . " set VALID=:valid where MAIL=:mail";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			
			if ($db->bindByName($stid, ":valid", $newvalid, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if ($db->bindByName($stid, ":mail", $mail, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$ret = false;
			if ($db->execute($stid)) {
				if ($db->getRowCount($stid) > 0) {
					$ret = true;
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$db->free($stid);
			$internalErrorFlg = false;
			return $ret;
		}
		
		/*
		*	機能	APIアクセスキーテーブルにレコードを追加する
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$username:USERNAMEカラムに登録する文字列
		*			$mail:MAILカラムに登録する文字列
		*			$apiAccessKey:APIACCESSKEYカラムに登録する文字列
		*			$valid:VALIDカラムに登録する文字
		*			$ipAddress:IPADDRESSカラムに登録する文字列
		*			$note:NOTEカラムに登録する文字列
		*			&$internalErrorFlg:true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true:成功 false:失敗
		*/
		public static function insertApiAccessKey($db,$username, $mail,  $apiAccessKey, $valid, $ipAddress, $note, &$internalErrorFlg, &$errorMsg) {
			if (!empty($note)) {
				$sql = "insert into " . API_KEY_TABLE . " (USERNAME, MAIL, APIACCESSKEY, DATEOFISSUE, VALID, IPADDRESS, NOTE) " .
						" values (:username, :mail, :apiaccesskey, SYSDATE, :valid, :ipaddress, :note)";
			} else {
				$sql = "insert into " . API_KEY_TABLE . " (USERNAME, MAIL, APIACCESSKEY, DATEOFISSUE, VALID, IPADDRESS) " .
						" values (:username, :mail, :apiaccesskey, SYSDATE, :valid, :ipaddress)";
			}
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":username", $username, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":mail", $mail, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":apiaccesskey", $apiAccessKey, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":valid", $valid, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if (is_array($ipAddress) == true) {
				for($i = 0; $i < count($ipAddress); $i++) {
					if (empty($ipAddress[$i])) {
						unset($ipAddress[$i]);
					}
				}
				$ipAddress = implode(",", $ipAddress);
			}
			
			if ($db->bindByName($stid, ":ipAddress", $ipAddress, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if (!empty($note)) {
				if ($db->bindByName($stid, ":note", $note, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
			}
			
			if ($db->execute($stid) === false) {
				error_log("execute error");
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			$db->free($stid);
			$internalErrorFlg = false;
			return true;
		}
		
		/*
		*	機能	APIアクセスキーテーブルのレコードを変更する
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$username:USERNAMEカラムに登録する文字列
		*			$oldmail:変更前のMAILカラム（レコード検索用）
		*			$newmail:MAILカラムに登録する文字列
		*			$apiAccessKey:APIACCESSKEYカラムに登録する文字列
		*			$valid:VALIDカラムに登録する文字
		*			$ipAddress:IPADDRESSカラムに登録する文字列
		*			$note:NOTEカラムに登録する文字列
		*			&$internalErrorFlg:true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true:成功 false:失敗
		*/
		public static function updateApiAccessKey($db, $username,$oldmail, $newmail, $apiAccessKey, $valid, $ipAddress, $note, &$internalErrorFlg, &$errorMsg) {
			$sql = "select * from " . API_KEY_TABLE . " where MAIL=:mail for update wait 30";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":mail", $oldmail, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if ($db->getRecInto($stid, $data, OCI_ASSOC)) {
				$db->free($stid);
				
				if ($data['MAIL'] != $oldmail) {
					return false;
				}
				
				$sql = "update " . API_KEY_TABLE . " set USERNAME=:username, MAIL=:newmail, APIACCESSKEY=:apikey, VALID=:valid, IPADDRESS=:ipaddress, NOTE=:note, UPDATE_DATE=SYSDATE" .
						" where MAIL=:oldmail";
				$stid = $db->parse($sql);
				if ($stid === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($db->conn);
					return false;
				}
				
				if ($db->bindByName($stid, ":username", $username, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				
				if ($db->bindByName($stid, ":newmail", $newmail, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				
				if ($db->bindByName($stid, ":oldmail", $oldmail, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				
				if ($db->bindByName($stid, ":apikey", $apiAccessKey, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				if ($db->bindByName($stid, ":valid", $valid, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				if (is_array($ipAddress) == true) {
					for($i = 0; $i < count($ipAddress); $i++) {
						if (empty($ipAddress[$i])) {
							unset($ipAddress[$i]);
						}
					}
					$ipAddress = implode(",", $ipAddress);
				}
				if ($db->bindByName($stid, ":ipaddress", $ipAddress, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				
				if (empty($note) ) {
					$note = NULL;
				}
				
				if ($db->bindByName($stid, ":note", $note, -1) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
				if ($db->execute($stid) === false) {
					$internalErrorFlg = true;
					$errorMsg = $db->getError($stid);
					$db->free($stid);
					return false;
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return true;
		}
		
		/*
		*	機能	APIアクセスキーテーブルのレコードを削除する
		*	引数	$db:oraDBAccessクラスオブジェクト
		*			$mail:削除対象レコードのMAIL
		*			&$internalErrorFlg:true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	true:成功 false:失敗
		*/
		public static function deleteApiAccessKey($db, $mail, &$internalErrorFlg, &$errorMsg) {
			$sql = "delete from " . API_KEY_TABLE . " where MAIL=:mail";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":mail", $mail, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			if ($db->execute($stid) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return true;
		}
	}
?>