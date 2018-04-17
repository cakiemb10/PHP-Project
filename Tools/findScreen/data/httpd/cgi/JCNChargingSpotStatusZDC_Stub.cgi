<?php
/*========================================================*/
// ファイル名：JCNChargingSpotStatusZDC_Stub.cgi
// 処理名：充電設備情報配信CGI（スタブ）
//
// 更新履歴
// 2012/11/13 Y.Matsukawa	新規作成
/*========================================================*/
require_once('/home/emap/src/Jsphon/Encoder.php');
$json = new Jsphon_Encoder();

define('D_MAX_LENGTH', 2000);
define('D_MAX_COUNT', 100);

$DUMMY_STATUS['1'] = array(0,'100','0,1,1,0,0,8');
$DUMMY_STATUS['10'] = array(1,'101','0,1,1,1,1');
$DUMMY_STATUS['11'] = array(2,'102','1,1,1,1');
$DUMMY_STATUS['12'] = array(0,'100','0,0');
$DUMMY_STATUS['13'] = array(1,'101','1,0');
$DUMMY_STATUS['15'] = array(2,'102','1,1,1,1,1');
$DUMMY_STATUS['17'] = array(0,'100','0,0,0,0,9,9');
$DUMMY_STATUS['19'] = array(1,'101','1,1,0,9,1');
$DUMMY_STATUS['20'] = array(2,'102','1,1,8,9,1');
$DUMMY_STATUS['21'] = array(8,'108','8,8,8');
//$DUMMY_STATUS['22'] = array(9,'109','');
$DUMMY_STATUS['23'] = array(0,'100','8,0,0,0,0');
$DUMMY_STATUS['24'] = array(1,'101','1,1,0,1');
$DUMMY_STATUS['27'] = array(2,'102','1');
$DUMMY_STATUS['29'] = array(0,'100','0');
$DUMMY_STATUS['32'] = array(1,'101','0,0,1,1,1,8,1');
$DUMMY_STATUS['36'] = array(2,'102','8,8,9');
$DUMMY_STATUS['39'] = array(0,'100','0,0,8,0,0,0,0,0');
$DUMMY_STATUS['40'] = array(1,'101','0,0,1,1,1');
$DUMMY_STATUS['43'] = array(2,'102','9,1,1');
$DUMMY_STATUS['44'] = array(8,'108','8,8');
$DUMMY_STATUS['45'] = array(9,'109','9');
$DUMMY_STATUS['46'] = array(0,'100','0,1,1,0,0,8');
$DUMMY_STATUS['47'] = array(1,'101','0,1,1,1,1');
$DUMMY_STATUS['48'] = array(2,'102','1,1,1,1');
//$DUMMY_STATUS['49'] = array(0,'000','0,0');
$DUMMY_STATUS['5'] = array(1,'101','1,0');
$DUMMY_STATUS['50'] = array(2,'002','1,1,1,1,1');
$DUMMY_STATUS['51'] = array(0,'000','0,0,0,0,9,9');
$DUMMY_STATUS['52'] = array(1,'001','1,1,0,9,1');
$DUMMY_STATUS['53'] = array(2,'002','1,1,8,9,1');
$DUMMY_STATUS['54'] = array(8,'008','8,8,8');
$DUMMY_STATUS['55'] = array(9,'009','');
$DUMMY_STATUS['56'] = array(0,'000','8,0,0,0,0');
$DUMMY_STATUS['57'] = array(1,'001','1,1,0,1');
$DUMMY_STATUS['58'] = array(2,'002','1');
$DUMMY_STATUS['59'] = array(0,'000','0');
$DUMMY_STATUS['6'] = array(1,'101','0,0,1,1,1,8,1');
$DUMMY_STATUS['60'] = array(2,'002','8,8,9');
$DUMMY_STATUS['61'] = array(0,'000x','0,0,8,0,0,0,0,0');
$DUMMY_STATUS['62'] = array(1,'001','0,0,1,1,1');
$DUMMY_STATUS['63'] = array(2,'002','9,1,1');
$DUMMY_STATUS['64'] = array(8,'008','8,8');
$DUMMY_STATUS['7'] = array(9,'109','9');
$DUMMY_STATUS['9'] = array(0,'100','0,0,8,0,0,0,0,0');



header('Content-Type: application/json; charset=utf-8');

$RET = array();
$RET['retCode'] = 0;

$spotId = $_GET['spotId'];
if ($spotId == '') err_ret(5001);
if (strlen($spotId) > D_MAX_LENGTH) err_ret(5002);

$arr_spotId = explode(',', $spotId);
if (count($arr_spotId) > D_MAX_COUNT) err_ret(5003);

$RET['spotList'] = array();
foreach ($arr_spotId as $spid) {
	if (isset($DUMMY_STATUS[$spid])) {
		$sp = array();
		$sp['spotId'] = $spid;
		$sp['spotStatus'] = $DUMMY_STATUS[$spid][0];
		$sp['spotStatusIcon'] = $DUMMY_STATUS[$spid][1];
		$chargerStatusList = $DUMMY_STATUS[$spid][2];
		if ($chargerStatusList != '') $chargerStatusList = explode(',', $chargerStatusList);
		foreach ($chargerStatusList as $status) {
			$sp['chargerList'][] = array('chargerType'=>substr($DUMMY_STATUS[$spid][1], 1, 1), 'chargerStatus'=>$status);
		}
		$RET['spotList'][] = $sp;
	}
}

if (!count($RET['spotList'])) err_ret(1001);

echo $json->encode($RET);
exit;

function err_ret($retCode) {
	$RET = array('retCode'=>$retCode);
	echo $json->encode($RET);
	exit;
}

?>
