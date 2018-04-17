<?php
/*========================================================*/
// prd_select_name.cgi
// 商品名から商品検索
//
// 更新履歴
// 2015/05/01 Y.Uesugi	新規作成
/*========================================================*/
	header( 'Content-Type: Text/html; charset=euc-jp' );

	require_once('d_serv_cgi.inc');
	require_once('ZdcCommonFunc.inc');
	require_once('d_serv_ora.inc');
	require_once('inc/oraDBAccess.inc');
	require_once('log.inc');
	require_once('crypt.inc');
	require_once('function.inc');
	require_once("chk.inc");

	// ログ出力開始
	include('logs/inc/com_log_open.inc');

	$CGICD = 'p01';
	$enc = 'EUC';

	// 入力パラメータ取得
	$_REQ = ${'_'.$_SERVER['REQUEST_METHOD']};
	$key = (isset($_REQ['key']) ? $_REQ['key'] : '');
	$cid = (isset($_REQ['cid']) ? $_REQ['cid'] : '');
	$pnm = (isset($_REQ['pnm']) ? $_REQ['pnm'] : '');
	$opt = (isset($_REQ['opt']) ? $_REQ['opt'] : '');
	$z2h = (isset($_REQ['z2h']) ? $_REQ['z2h'] : '');

	/*==============================================*/
	// APIキーデコード	※ログ出力で使用するだけなので、認証は行っていません。
	/*==============================================*/
	$KEY = f_decrypt_api_key($key);
	// デコード後の文字列が壊れている場合はログに出力しない
	if (!chk_sb_anmb($KEY)){
		$KEY = '';
	}

	// LOG出力用にパラメータ値を結合
	if (isset($pnm)) {
		$parms = $pnm;
	} else {
		$parms = '';
	}

	//入力パラメータチェック
	if ($cid == '') {
		print $CGICD."19100\t0\t0\n";
		put_log($CGICD."19100", $KEY, $opt, $parms);
		exit;
	}
	if ($pnm == '') {
		print $CGICD."19100\t0\t0\n";
		put_log($CGICD."19100", $KEY, $opt, $parms);
		exit;
	}
	
	// SQL
	$sql = "select PRD_ID, PRD_NAME, OPT_01, OPT_02, OPT_03, OPT_04, OPT_05, OPT_06, OPT_07, OPT_08, OPT_09, OPT_10";
	$sql .= " from PRD_MST";
	$sql .= " where CORP_ID = '$cid'";
	$sql .= " and PRD_NAME like '%".$pnm."%'";

	// DB接続
	$dba = new oraDBAccess();
	if (!$dba->open()) {
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17900", $KEY, $opt, $parms);
		exit;
	}

	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."17900\t0\t0\n";
		put_log($CGICD."17999", $KEY, $opt, $parms);
		exit;
	}
	$arr_retdata = array();
	while($dba->getRecInto($stmt, $retdata, OCI_ASSOC)) {
		$arr_retdata[] = $retdata;
	}
	if (empty($arr_retdata)) {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."11009\t0\t0\n";
		put_log($CGICD."11009", $KEY, $opt, $parms);
		exit;
	}
	$dba->free($stmt);

	$dba->close();

	$reccount = count($arr_retdata);
	print $CGICD."00000\t$reccount\t$reccount\n";
	put_log($CGICD."00000", $KEY, $opt, $parms);

	$buf = '';

	foreach($arr_retdata as $rowdata){
		$buf .= $rowdata["PRD_ID"]."\t";
		$buf .= $rowdata["PRD_NAME"]."\t";
		$buf .= $rowdata["OPT_01"]."\t";
		$buf .= $rowdata["OPT_02"]."\t";
		$buf .= $rowdata["OPT_03"]."\t";
		$buf .= $rowdata["OPT_04"]."\t";
		$buf .= $rowdata["OPT_05"]."\t";
		$buf .= $rowdata["OPT_06"]."\t";
		$buf .= $rowdata["OPT_07"]."\t";
		$buf .= $rowdata["OPT_08"]."\t";
		$buf .= $rowdata["OPT_09"]."\t";
		$buf .= $rowdata["OPT_10"]."\t";
		$buf .= "\n";
	}
	$buf = ZdcConvZ2H($buf, $z2h);
	if ($enc == "EUC") {
		$buf = mb_convert_encoding($buf, 'eucJP-win', 'eucJP-win');
	} else {
		$buf = mb_convert_encoding($buf, $enc);
	}
	print $buf;
?>
