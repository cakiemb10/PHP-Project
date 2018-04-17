<?php
// ------------------------------------------------------------
// アクセスキーログ関連処理
// 
// 2016/06/14 H.Yasunaga	新規作成
// ------------------------------------------------------------
require_once(dirname(__FILE__) . "/define.inc");
require_once(dirname(__FILE__) . "/../oracle/ora_def.inc");
require_once(dirname(__FILE__) . "/oraDBAccess.inc");
require_once(dirname(__FILE__) . "/CommonUtil.inc");

	class ApiLogUtil {
	
		/*
		*	機能	API用ログをテーブルに挿入
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$apiAccessKey:APIアクセスキー文字列
		*			$remoteAddress:接続元IPアドレス文字列
		*			$requestParameter:リクエストパラメータ文字列
		*	戻り値	なし
		*/
		public static function putLog($db, $apiAccessKey, $remoteAddress, $requestParameter) {
			if (is_null($db)) {
				return;
			}
			
			// del start 2016/06/23 H.Yasunaga 不要なため削除[
			// define.incに定義した許可APIアクセスキーとIPアドレスの場合はログに残さない
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
		*	機能	指定年月の日別のログ
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$targetYear:ログ取得対象年
		*			$targetMonth:ログ取得対象月
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 配列 keyは日付(0パディング2桁) valueは回数
		*			失敗時 false
		*/ 
		public static function getLogByMonth($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			
			$sql = "select to_char(LOGDATE, 'dd') as LOGDATE, count(*) as CNT from " . API_LOG_TABLE . " where LOGDATE between TO_DATE(:firstday) and TO_DATE(:lastday) group by to_char(LOGDATE, 'dd')";
			
			// 指定年月の月初日の取得
			$firstday = date("Y/m/d", strtotime("first day of " . $targetYear . "-" . $targetMonth));
			// 指定年月の月末日の取得
			$lastday = date("Y/m/d", strtotime("last day of " . $targetYear . "-" . $targetMonth));
			
			// 戻り値の配列指定年月の日付をキーにした配列を先に用意(1件もない日も0で戻せる)
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
		*	機能	指定年月のアクセスキー毎のカウント
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$targetYear:ログ取得対象年
		*			$targetMonth:ログ取得対象月
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 配列 keyはAPIアクセスキー valueは回数
		*			失敗時 false
		*/
		public static function getLogByAccessKey($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
		
			$ret = array();		// keyにアクセスキー valueが回数
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
		*	機能	指定年月の指定アクセスキーの日別ログカウント
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$accessKey:ログ取得対象APIアクセスキー
		*			$targetYear:ログ取得対象年
		*			$targetMonth:ログ取得対象月
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 配列 keyは日付(0パディング2桁) valueは回数
		*			失敗時 false
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
					$errorMsg['message'] = "該当APIアクセスキーが存在しません。";
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
			
			// 指定年月の月初日の取得
			$firstday = date("Y/m/d", strtotime("first day of " . $targetYear . "-" . $targetMonth));
			// 指定年月の月末日の取得
			$lastday = date("Y/m/d", strtotime("last day of " . $targetYear . "-" . $targetMonth));
			
			// 戻り値の配列指定年月の日付をキーにした配列を先に用意(1件もない日も0で戻せる)
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
		*	機能	CSV形式の指定年月のアクセスキー毎のアクセス数
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$targetYear:ログ取得対象年
		*			$targetMonth:ログ取得対象月
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 文字列
		*			失敗時 false
		*/
		public static function logToCsvByAccessKey($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$dat = ApiLogUtil::getLogByAccessKey($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg);
			if ($dat === false) {
				return false;
			}
			
			$ret = "APIアクセスキー, アクセス数\n";
			foreach ($dat as $key => $value) {
				$ret .= $key ."," . $value ."\n";
			}
			$str = mb_convert_encoding($ret, "SJIS");
			return $str;
		}
		
		/*
		*	機能	CSV形式の指定年月の日毎のアクセス数
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$targetYear:ログ取得対象年
		*			$targetMonth:ログ取得対象月
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 文字列
		*			失敗時 false
		*/
		public static function logToCsvByMonth($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$dat = ApiLogUtil::getLogByMonth($db, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg);
			if ($dat === false) {
				return false;
			}
			
			$ret = "日付, アクセス数\n";
			foreach($dat as $key => $value) {
				$ret .= $targetMonth . "月" . $key . "日" . "," . $value . "\n";
			}
			
			$str = mb_convert_encoding($ret, "SJIS", "EUC-jp");
			return $str;
		}
		
		/*
		*	機能	CSV形式の指定年月・APIアクセスキーの日別アクセス数
		*	引数	$db:oraDBAccessクラスのオブジェクト
		*			$accessKey:ログ取得対象APIアクセスキー
		*			$targetYear:ログ取得対象年
		*			$targetMonth:ログ取得対象月
		*			&$internalErrorFlg: true=内部エラーあり false=内部エラーなし
		*			&$errorMsg:エラーメッセージ配列 'code'・'message'・'offset'・'sqltext'
		*	戻り値	成功時 文字列
		*			失敗時 false
		*/
		public static function logToCsvByAccessKeyDaily($db, $accessKey, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg) {
			$dat = ApiLogUtil::getLogByAccessKeyDaily($db, $accessKey, $targetYear, $targetMonth, &$internalErrorFlg, &$errorMsg);
			if ($dat === false) {
				return false;
			}
			
			$ret = "日付, アクセス数\n";
			foreach($dat as $key => $value) {
				$ret .= $targetMonth . "月" . $key . "日" . "," . $value . "\n";
			}
			
			$str = mb_convert_encoding($ret, "SJIS", "EUC-jp");
			
			return $str;
		}
	}
?>