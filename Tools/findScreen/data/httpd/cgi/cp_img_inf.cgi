<?php
/*========================================================*/
// ファイル名：cp_img_inf.cgi
// 処理名：企業画像情報を取得する
//
// 作成日：2012/02/13
// 作成者：Y.Matsukawa
//
// 解説：企業ID、媒体区分（PC／携帯／スマホ）に該当する画像情報を返す
//
// パラメータ：(IN)cid  -  企業ID
//             (IN)kbn  -  媒体区分（P：PC／M：携帯／S：スマホ）
// 更新履歴
// 2012/02/13 Y.Matsukawa	新規作成
// 2012/10/16 Y.Matsukawa	error_reporting()削除
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );

	include( "d_serv_ora.inc" );
	include( "inc/oraDBAccess.inc" );

	$cgi_kind = "810";	//CGI種別

	// エラー出力OFF
	//error_reporting(0);		del 2012/10/16 Y.Matsukawa

	// 入力パラメータ取得
	$_VARS = ${'_'.$_SERVER['REQUEST_METHOD']};
	if(isset($_VARS['cid']))		$cid = $_VARS['cid'];
	if(isset($_VARS['kbn']))		$kbn = $_VARS['kbn'];

	// 入力パラメータチェック
	if ( $cid == "" ) {
		print $cgi_kind . "19100\t0\t0\n";
		exit;
	}

	$dba = new oraDBAccess();
	if ( ! $dba->open() ) {
		$dba->close();
		print $cgi_kind . "17900\t0\t0\n";
		exit;
	}

	// アイコン情報取得
	$sql  = "select IMG_NO,IMG_NAME,IMG_W,IMG_H,URL"
			. " from CORP_IMG_TBL"
			. " where CORP_ID = '".$cid."'"
			. " and MEDIA_KBN = '". $kbn."'"
			. " and nvl(PUB_E_DATE, SYSDATE) >= SYSDATE "
			. " order by IMG_NO"
	;
	$stmt   = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		print $cgi_kind . "17999\t0\t0\n";		//その他DBエラー
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$reccount = count($retdata);
	if ($reccount <= 0) {
		$dba->free($stmt);
		print $cgi_kind . "11009\t0\t0\n";		//検索結果データなし
		exit;
	}
	$dba->free($stmt);
	$dba->close();

	print $cgi_kind . "00000\t$reccount\t$reccount\n";

	foreach($retdata as $rowdata){
		$buf = '';
		$buf .= $rowdata["IMG_NO"];
		$buf .= "\t";
		$buf .= $rowdata["IMG_NAME"];
		$buf .= "\t";
		$buf .= $rowdata["IMG_W"];
		$buf .= "\t";
		$buf .= $rowdata["IMG_H"];
		$buf .= "\t";
		$buf .= $rowdata["URL"];
		$buf .= "\n";
		print $buf;
	}
?>
