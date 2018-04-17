<?php
// ------------------------------------------------------------
// ��������������Ϣ����
// 
// 2016/06/14 H.Yasunaga	��������
// ------------------------------------------------------------
require_once(dirname(__FILE__) . "/define.inc");
require_once(dirname(__FILE__) . "/CommonUtil.inc");

	class ApiKeyUtil{
		
		/* 
		* 	��ǽ	API����¸�ߥ����å�
		*	����	$db:oraDBAccess���饹���֥�������
		*			$apiAccessKey:��ǧ����API������������ʸ����
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true=API������¸�ߤ��� false=API������¸�ߤ��ʤ�
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
		*	��ǽ	�᡼�륢�ɥ쥹�򥭡��˥ǡ�������
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
		*	��ǽ	���ǡ�������
		*	����	$db:oraDBAccess���饹���֥�������
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������:����
		*			���Ի�:false
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
		*	��ǽ	API�����������������μ���
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ���� key��0��xxx value��API������������
		*			���Ի� false
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
		* 	��ǽ	API������������ͭ�������å�
		*	����	$db:oraDBAccess���饹���֥�������
		*			$apiAccessKey:��ǧ����API������������ʸ����
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true=API��������������ͭ�� false:API��������������̵��
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
		*	��ǽ	API��������������ɳ�Ť��Ƥ���IP���ɥ쥹�Υ����å�
		*	����	$db:oraDBAccess���饹���֥�������
		*			$apiAccessKey:API������������ʸ����
		*			$ipAddress:��³��IP���ɥ쥹(�����å��о�)
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true=��Ͽ����Ƥ���IP���ɥ쥹�Ȱ��� false=��Ͽ����Ƥ���IP���ɥ쥹���԰���
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
				// DB����Ͽ����Ƥ��륫��޶��ڤ�IP���ɥ쥹�������
				// ex.) 192.168.1.1,192.168.1.2�� [0]=192.168.1.1;[1]=192.168.1.2
				$ipaddressAry = explode(",", $data['IPADDRESS']);
				for($i = 0; $i < count($ipaddressAry); $i++) {
					if ($ipaddressAry[$i] == "*") {
						// '*'�Τߤ�������
						$ret = true;
						break;
					}
					else if ($ipaddressAry[$i] === $ipAddress) {
						// ���������ʤ��ǰ���
						$ret = true;
						break;
					} else {
						// ���������ΰ���
						$asterpos = mb_strpos($ipaddressAry[$i], "*");
						// ����������ޤ��IP���ɥ쥹��ʸ����Ĺ
						$paternlen = mb_strlen($ipaddressAry[$i]);
						// ������IP���ɥ쥹��ʸ����Ĺ
						$iplen = mb_strlen($ipAddress);
						/* ��ǧ��
						error_log("ipaddress:[" . $ipAddress ."]");
						error_log("patern:[" . $ipaddressAry[$i] . "]");
						error_log("asterpos:[" . $asterpos . "]");
						error_log("patertnlen:[" . $paternlen . "]");
						error_log("iplen:[" . $iplen . "]");
						*/
						
						// �����������ޤޤ줫�ĥ��������������Ǥ��뤫��ʸ����Ĺ�����ʤ��Ǥ��뤫��
						if ($asterpos !== false && $asterpos == ($paternlen - 1) && $iplen == $paternlen) {
							// �������������ޤǤ���Ф�
							$preaster = mb_substr($ipaddressAry[$i], 0, $asterpos);
							// �������������ޤǤ�ʸ���󤬰�����IP���ɥ쥹����Ƭ������פ��뤫��
							if (mb_strpos($ipAddress, $preaster) === 0) {
								// ��Ƭ����*���ޤ�Ʊ��
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
		*	��ǽ	�������API�������������������ʴ�¸API�������������ȤΥ����å�ͭ��
		*	����	$db:oraDBAccess���饹���֥�������
		*			&$internalErrorFlg:true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*			$length:API������������ʸ�����Ĺ��(�ǥե����30)
		*	�����	��������API������������
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
		*	��ǽ	API�������������η��������å�
		*	����	$target:��ǧ����API������������ʸ����
		*	�����	������:true ����:false
		*/
		public static function isApiKey($target) {
			return mb_ereg_match("^[a-zA-Z]{30}$", $target);
		}
		
		/* 
		* 	��ǽ	API����¸�ߥ����å�
		*	����	$db:oraDBAccess���饹���֥�������
		*			$mail:��ǧ����MAILʸ����
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true=API������¸�ߤ��� false=API������¸�ߤ��ʤ�
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
		*	��ǽ	API��������������ͭ��̵���ڤ��ؤ�
		*	����	$db:oraDBAccess���饹���֥�������
		*			$newvalid:�ѹ����뤹��VALID����
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
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
		*	��ǽ	API�������������ơ��֥�˥쥳���ɤ��ɲä���
		*	����	$db:oraDBAccess���饹���֥�������
		*			$username:USERNAME��������Ͽ����ʸ����
		*			$mail:MAIL��������Ͽ����ʸ����
		*			$apiAccessKey:APIACCESSKEY��������Ͽ����ʸ����
		*			$valid:VALID��������Ͽ����ʸ��
		*			$ipAddress:IPADDRESS��������Ͽ����ʸ����
		*			$note:NOTE��������Ͽ����ʸ����
		*			&$internalErrorFlg:true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true:���� false:����
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
		*	��ǽ	API�������������ơ��֥�Υ쥳���ɤ��ѹ�����
		*	����	$db:oraDBAccess���饹���֥�������
		*			$username:USERNAME��������Ͽ����ʸ����
		*			$oldmail:�ѹ�����MAIL�����ʥ쥳���ɸ����ѡ�
		*			$newmail:MAIL��������Ͽ����ʸ����
		*			$apiAccessKey:APIACCESSKEY��������Ͽ����ʸ����
		*			$valid:VALID��������Ͽ����ʸ��
		*			$ipAddress:IPADDRESS��������Ͽ����ʸ����
		*			$note:NOTE��������Ͽ����ʸ����
		*			&$internalErrorFlg:true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true:���� false:����
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
		*	��ǽ	API�������������ơ��֥�Υ쥳���ɤ�������
		*	����	$db:oraDBAccess���饹���֥�������
		*			$mail:����оݥ쥳���ɤ�MAIL
		*			&$internalErrorFlg:true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	true:���� false:����
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