<?php
// ------------------------------------------------------------
// ������������������Ϣ����
// 
// 2016/06/14 H.Yasunaga	��������
// ------------------------------------------------------------
require_once(dirname(__FILE__) . "/define.inc");
require_once(dirname(__FILE__) . "/../oracle/ora_def.inc");
require_once(dirname(__FILE__) . "/oraDBAccess.inc");
require_once(dirname(__FILE__) . "/CommonUtil.inc");

	class ApiLogUtil {
	
		/*
		*	��ǽ	API�ѥ�����ơ��֥������
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$apiAccessKey:API������������ʸ����
		*			$remoteAddress:��³��IP���ɥ쥹ʸ����
		*			$requestParameter:�ꥯ�����ȥѥ�᡼��ʸ����
		*	�����	�ʤ�
		*/
		public static function putLog($db, $apiAccessKey, $remoteAddress, $requestParameter) {
			if (is_null($db)) {
				return;
			}
			
			// del start 2016/06/23 H.Yasunaga ���פʤ�����[
			// define.inc�������������API��������������IP���ɥ쥹�ξ��ϥ����˻Ĥ��ʤ�
			//if (CommonUtil::checkSpecialPermission($apiAccessKey, $remoteAddress)) {
			//	return;
			//}
			// del end ]
			
			$sql = "insert into " . API_LOG_TABLE . " (APIACCESSKEY, REMOTEADDRESS, LOGDATE, REQUESTPARAMETER) values(:apikey, :address, SYSDATE, :param)";
			$stid = $db->parse($sql);
			$db->bindByName($stid, ":apikey", $apiAccessKey, -1);
			$db->bindByName($stid, ":address", $remoteAddress, -1);
			$db->bindByName($stid, ":param", $requestParameter, -1);
			$db->execute($stid);
			$db->free($stid);
		}

		/*
		*	��ǽ	����ǯ������̤Υ���
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$targetYear:���������о�ǯ
		*			$targetMonth:���������оݷ�
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ���� key������(0�ѥǥ���2��) value�ϲ��
		*			���Ի� false
		*/ 
		public static function getLogByMonth($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			
			$sql = "select to_char(LOGDATE, 'dd') as LOGDATE, count(*) as CNT from " . API_LOG_TABLE . " where LOGDATE between TO_DATE(:firstday) and TO_DATE(:lastday) group by to_char(LOGDATE, 'dd')";
			
			// ����ǯ��η�����μ���
			$firstday = date("Y/m/d", strtotime("first day of " . $targetYear . "-" . $targetMonth));
			// ����ǯ��η������μ���
			$lastday = date("Y/m/d", strtotime("last day of " . $targetYear . "-" . $targetMonth));
			
			// ����ͤ��������ǯ������դ򥭡��ˤ������������Ѱ�(1���ʤ�����0���᤻��)
			for($i = 0; $i < date("d", strtotime("last day of " . $targetYear . "-" . $targetMonth)); $i++) {
				$ret[sprintf("%02d",($i + 1))] = 0;
			}
			
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":firstday", $firstday, -1) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":lastday", $lastday, -1) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->execute($stid)) {
				while($db->getRecInto($stid, $data, OCI_ASSOC)) {
					$ret[$data['LOGDATE']] = $data['CNT'];
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
		*	��ǽ	����ǯ��Υ�������������Υ������
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$targetYear:���������о�ǯ
		*			$targetMonth:���������оݷ�
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ���� key��API������������ value�ϲ��
		*			���Ի� false
		*/
		public static function getLogByAccessKey($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
		
			$ret = array();		// key�˥����������� value�����
			$sql = "select USERNAME,APIACCESSKEY from " . API_KEY_TABLE . " order by DATEOFISSUE asc ";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->execute($stid)) {
				while($db->getRecInto($stid, $data, OCI_ASSOC)) {
					$ret[$data['APIACCESSKEY']]['cnt'] = 0;
					$ret[$data['APIACCESSKEY']]['username'] = $data['USERNAME'];
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			$db->free($stid);
		
			$sql = "select APIACCESSKEY, COUNT(*) as CNT from " . API_LOG_TABLE . " where LOGDATE between TO_DATE(:firstday) and TO_DATE(:lastday) group by APIACCESSKEY";
			
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			if ($db->bindByName($stid, ":firstday", date("Y/m/d", strtotime("first day of " . $targetYear . "-" . $targetMonth)), -1) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":lastday", date("Y/m/d", strtotime("last day of " . $targetYear . "-" . $targetMonth)), -1) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->execute($stid)) {
				while($db->getRecInto($stid, $data, OCI_ASSOC)) {
					$ret[$data['APIACCESSKEY']]['cnt'] = $data['CNT'];
				}
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				return false;
			}
			$internalErrorFlg = false;
			$db->free($stid);
			return $ret;
		}
		
		/*
		*	��ǽ	����ǯ��λ��ꥢ���������������̥����������
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$accessKey:���������о�API������������
		*			$targetYear:���������о�ǯ
		*			$targetMonth:���������оݷ�
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ���� key������(0�ѥǥ���2��) value�ϲ��
		*			���Ի� false
		*/
		public static function getLogByAccessKeyDaily($db, $accessKey, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$sql = "select count(*) as CNT from " . API_KEY_TABLE . " where APIACCESSKEY=:apikey";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			
			if ($db->bindByName($stid, ":apikey", $accessKey, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->execute($stid) ) {
				$db->getRecInto($stid, $data, OCI_ASSOC);
				if ($data['CNT'] == 0) {
					$internalErrorFlg = true;
					$errorMsg['message'] = "����API��������������¸�ߤ��ޤ���";
					$db->free($stid);
					return false;
				}
				$db->free($stid);
			} else {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			// ����ǯ��η�����μ���
			$firstday = date("Y/m/d", strtotime("first day of " . $targetYear . "-" . $targetMonth));
			// ����ǯ��η������μ���
			$lastday = date("Y/m/d", strtotime("last day of " . $targetYear . "-" . $targetMonth));
			
			// ����ͤ��������ǯ������դ򥭡��ˤ������������Ѱ�(1���ʤ�����0���᤻��)
			for($i = 0; $i < date("d", strtotime("last day of " . $targetYear . "-" . $targetMonth)); $i++) {
				$ret[sprintf("%02d",($i + 1))] = 0;
			}
			$sql = "select to_char(LOGDATE, 'dd') as LOGDATE, count(*) as CNT from " . API_LOG_TABLE . " where APIACCESSKEY=:apikey and LOGDATE between TO_DATE(:firstday) and TO_DATE(:lastday) group by to_char(LOGDATE, 'dd')";
			$stid = $db->parse($sql);
			if ($stid === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($db->conn);
				return false;
			}
			
			if ($db->bindByName($stid, ":apikey", $accessKey, -1) === false) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":firstday", $firstday, -1) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->bindByName($stid, ":lastday", $lastday, -1) === false ) {
				$internalErrorFlg = true;
				$errorMsg = $db->getError($stid);
				$db->free($stid);
				return false;
			}
			
			if ($db->execute($stid)) {
				while($db->getRecInto($stid, $data, OCI_ASSOC)) {
					$ret[$data['LOGDATE']] = $data['CNT'];
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
		*	��ǽ	CSV�����λ���ǯ��Υ�������������Υ���������
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$targetYear:���������о�ǯ
		*			$targetMonth:���������оݷ�
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ʸ����
		*			���Ի� false
		*/
		public static function logToCsvByAccessKey($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$dat = ApiLogUtil::getLogByAccessKey($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg);
			if ($dat === false) {
				return false;
			}
			
			$ret = "API������������, ����������\n";
			foreach ($dat as $key => $value) {
				$ret .= $key ."," . $value ."\n";
			}
			$str = mb_convert_encoding($ret, "SJIS");
			return $str;
		}
		
		/*
		*	��ǽ	CSV�����λ���ǯ�������Υ���������
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$targetYear:���������о�ǯ
		*			$targetMonth:���������оݷ�
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ʸ����
		*			���Ի� false
		*/
		public static function logToCsvByMonth($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$dat = ApiLogUtil::getLogByMonth($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg);
			if ($dat === false) {
				return false;
			}
			
			$ret = "����, ����������\n";
			foreach($dat as $key => $value) {
				$ret .= $targetMonth . "��" . $key . "��" . "," . $value . "\n";
			}
			
			$str = mb_convert_encoding($ret, "SJIS", "EUC-jp");
			return $str;
		}
		
		/*
		*	��ǽ	CSV�����λ���ǯ�API�����������������̥���������
		*	����	$db:oraDBAccess���饹�Υ��֥�������
		*			$accessKey:���������о�API������������
		*			$targetYear:���������о�ǯ
		*			$targetMonth:���������оݷ�
		*			&$internalErrorFlg: true=�������顼���� false=�������顼�ʤ�
		*			&$errorMsg:���顼��å��������� 'code'��'message'��'offset'��'sqltext'
		*	�����	������ ʸ����
		*			���Ի� false
		*/
		public static function logToCsvByAccessKeyDaily($db, $accessKey, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$dat = ApiLogUtil::getLogByAccessKeyDaily($db, $accessKey, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg);
			if ($dat === false) {
				return false;
			}
			
			$ret = "����, ����������\n";
			foreach($dat as $key => $value) {
				$ret .= $targetMonth . "��" . $key . "��" . "," . $value . "\n";
			}
			
			$str = mb_convert_encoding($ret, "SJIS", "EUC-jp");
			
			return $str;
		}
	}
?>