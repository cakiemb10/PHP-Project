<?php
/*========================================================*/
// prd_select.cgi
// 商品ID検索
//
// 更新履歴
// 2014/05/13 Y.Matsukawa	新規作成
// 2014/07/18 Y.Matsukawa	「〜」文字化け回避
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
	$pid = (isset($_REQ['pid']) ? $_REQ['pid'] : '');
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
	if (isset($pid)) {
		$parms = $pid;
	} else {
		$parms = '';
	}

	//入力パラメータチェック
	if ($cid == '') {
		print $CGICD."19100\t0\t0\n";
		put_log($CGICD."19100", $KEY, $opt, $parms);
		exit;
	}
	if ($pid == '') {
		print $CGICD."19100\t0\t0\n";
		put_log($CGICD."19100", $KEY, $opt, $parms);
		exit;
	}
	
	// SQL
	$sql = "select PRD_ID, PRD_NAME, OPT_01, OPT_02, OPT_03, OPT_04, OPT_05, OPT_06, OPT_07, OPT_08, OPT_09, OPT_10";
	$sql .= " from PRD_MST";
	$sql .= " where CORP_ID = '$cid'";
	$sql .= " and PRD_ID = '$pid'";

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
	$dba->getRecInto($stmt, $retdata, OCI_ASSOC);
	if ($retdata == "") {
		$dba->free($stmt);
		$dba->close();
		print $CGICD."11009\t0\t0\n";
		put_log($CGICD."11009", $KEY, $opt, $parms);
		exit;
	}
	$dba->free($stmt);

	$dba->close();

	print $CGICD."00000\t1\t1\n";
	put_log($CGICD."00000", $KEY, $opt, $parms);

	$buf = '';
	$buf .= $retdata["PRD_ID"]."\t";
	$buf .= $retdata["PRD_NAME"]."\t";
	$buf .= $retdata["OPT_01"]."\t";
	$buf .= $retdata["OPT_02"]."\t";
	$buf .= $retdata["OPT_03"]."\t";
	$buf .= $retdata["OPT_04"]."\t";
	$buf .= $retdata["OPT_05"]."\t";
	$buf .= $retdata["OPT_06"]."\t";
	$buf .= $retdata["OPT_07"]."\t";
	$buf .= $retdata["OPT_08"]."\t";
	$buf .= $retdata["OPT_09"]."\t";
	$buf .= $retdata["OPT_10"]."\t";
	$buf .= "\n";
	$buf = ZdcConvZ2H($buf, $z2h);
	//if ($enc != "EUC") {		del 2014/07/18 Y.Matsukawa
	// add 2014/07/18 Y.Matsukawa [
	if ($enc == "EUC") {
		$buf = mb_convert_encoding($buf, 'eucJP-win', 'eucJP-win');
	} else {
	// add 2014/07/18 Y.Matsukawa ]
		$buf = mb_convert_encoding($buf, $enc);
	}
	print $buf;
?>
