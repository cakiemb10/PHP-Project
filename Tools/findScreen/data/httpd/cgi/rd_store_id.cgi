<?php
/*========================================================*/
// ファイル名：rd_store_id.cgi
// 処理名：店舗指定リアルタイムデータ検索
//
// 更新履歴
// 2013/02/20 Y.Matsukawa	新規作成
/*========================================================*/
/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = 'y11';

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// リターンコード定義
/*==============================================*/
define( 'DEF_RETCD_DE',   '00000' );       //条件に見合うデータあり（後続データなし）
define( 'DEF_RETCD_DEND', '00001' );       //条件に見合うデータあり（後続データあり）
define( 'DEF_RETCD_DNE',  '11009' );       //条件に見合うデータなし
define( 'DEF_RETCD_AERR', '12009' );       //認証エラー
define( 'DEF_RETCD_DERR1','17900' );       //データベースアクセスエラー
define( 'DEF_RETCD_DERR2','17002' );       //データベースアクセスエラー
define( 'DEF_RETCD_DERR3','17999' );       //データベースアクセスエラー
define( 'DEF_RETCD_PERR1','19100' );       //入力パラメータエラー(必須項目NULL)
define( 'DEF_RETCD_PERR2','19200' );       //入力パラメータエラー(構文エラー)
define( 'DEF_RETCD_PERR3','19200' );       //入力パラメータエラー(組み合わせエラー)

/*==============================================*/
// 定義ファイル
/*==============================================*/
include('d_serv_emap.inc');
include('ZdcCommonFuncAPI.inc');
include('function.inc');
include('d_serv_ora.inc');
include('oraDBAccess.inc');
include('chk.inc');
include('log.inc');
include('auth.inc');
include("jkn.inc");

include('store_def.inc');
include('rd_outf.inc');
include('rd_store_outf.inc');
include('rd_sql.inc');


if ($D_DEBUG) ini_set('display_errors', '1');

/*==============================================*/
// 初期化
/*==============================================*/
// ステータス(リターンコード)
if (!isset($status)){
	 $status = '00000';
}

/*==============================================*/
//ログ出力開始
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// パラメータ取得
/*==============================================*/
$CID	= getCgiParameter('cid', '');		// 企業ID
$KID	= getCgiParameter('kid', '');		// 拠点ID（複数）
$KID	= str_replace(' ', '', $KID);
$GRP	= getCgiParameter('grp', '');		// グループ番号（複数）
$GRP	= str_replace(' ', '', $GRP);
$ENC	= getCgiParameter('enc', 'UTF8');	// 文字コード
$OUTF	= getCgiParameter('outf','JSON');	// 出力形式
$INTID	= getCgiParameter('intid', '');		// 内部利用時のアプリID

// 入力チェック用に、$ENCをコピー(store_enc.incを呼ぶと勝手に変更されるため)
$INPUT_ENC = $ENC ;

$OPTION_CD = ($INTID ? $INTID : $CID);

// 出力形式
if ($OUTF != 'JSON' && $OUTF != 'XML') {
	$OUTF = 'JSON';
}

include('store_enc.inc');			// 文字コード変換

/*==============================================*/
// LOG出力用にパラメータ値を結合
/*==============================================*/
$parms  = $CID;
$parms .= ' '.mb_strimwidth($KID, 0, 255, '...');
$parms .= ' '.mb_strimwidth($GRP, 0, 255, '...');
$parms .= ' ';
$parms .= ' ';
$parms .= ' ';
$parms .= ' ';
$parms .= ' ';

/*==============================================*/
// 出力クラス
/*==============================================*/
$CgiOut = new RdStoreCgiOutput($CGICD, $CGINM, $ENC, $OUTF);

/*==============================================*/
// パラメータチェック
/*==============================================*/
// 企業ID
if ($CID == '') {
	$status = DEF_RETCD_PERR1;//入力パラメータエラー(必須項目NULL)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}
// 拠点ID
if ($KID == '') {
	$status = DEF_RETCD_PERR1;//入力パラメータエラー(必須項目NULL)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}
// 複数指定上限：1000
$arr_kid = explode(',', $KID);
$k_count = count($arr_kid);
if ($k_count > 1000) {
	$status = DEF_RETCD_PERR2;//入力パラメータエラー(構文エラー)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}
// グループID
$arr_grp = array();
if ($GRP != '') {
	$arr_tmp = explode(',', $GRP);
	$grp_count = count($arr_tmp);
	// 複数指定上限：20
	if ($grp_count > 20) {
		$status = DEF_RETCD_PERR2;//入力パラメータエラー(構文エラー)
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	// 不正な値を除去
	foreach ($arr_tmp as $grp_no) {
		if (ctype_digit($grp_no) && strlen($grp_no) <= 5) {
			$arr_grp[] = $grp_no;
		}
	}
}
// 内部利用時のID
if ($INTID != '') {
	if (!in_array($INTID, $D_INTID)) {
		$status = DEF_RETCD_AERR;//認証エラー
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("INTID不正");
		exit;
	}
}
// 文字コード
if ($INPUT_ENC != 'SJIS' && $INPUT_ENC != 'EUC' && $INPUT_ENC != 'UTF8') {
	$status = DEF_RETCD_PERR2;//入力パラメータエラー(構文エラー)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// DB接続オープン
/*==============================================*/
$dba = new oraDBAccess();
if (!$dba->open()) {
	$dba->close();
	$status = DEF_RETCD_DERR1;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}

if ($INTID == '') {
	/*==============================================*/
	// サービス期間
	/*==============================================*/
	$url = sprintf("%s?cid=%s&opt=%s",$D_SSAPI["getsdate"], $D_CID, $CID);
	$dat = ZdcHttpRead($url,0,$D_SOCKET_TIMEOUT);
	$service = explode("\t",$dat[0]);
	if($service[0] == "89000000") {
		$rec = explode("\t",$dat[1]);
		$flg = intval($rec[0]);
	}
	if(!isset($flg) || (isset($flg) && $flg == 0)) {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("サービス期間外");
		exit;
	}

	/*==============================================*/
	// CGI利用許可
	/*==============================================*/
	$sql  = " SELECT";
	$sql .= "    VALUE";
	$sql .= " FROM";
	$sql .= "    EMAP_PARM_TBL";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
	$sql .= " AND KBN  = 'C_EMAP_KBN'";
	$sql .= " AND VALUE  = 'S'";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("CGI利用許可 取得失敗");
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		if($data['VALUE'] == '0') {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_AERR;
			$CgiOut->set_status($status);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			dbl("CGI利用許可 無効");
			exit;
		}
	} else {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("CGI利用許可 無効");
		exit;
	}
	$dba->free($stmt);

	/*==============================================*/
	// SSL認証、IPチェック、リファラチェック
	/*==============================================*/
	$sql  = " SELECT";
	$sql .= "    SSL_ACCESS, ALLOW_IP, ALLOW_REFERER";
	$sql .= " FROM";
	$sql .= "    EMAP_CGI_CONF_TBL";
	$sql .= " WHERE";
	$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_DERR3;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("EMAP_CGI_CONF_TBL取得失敗");
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		/* SSL接続許可 */
		if (isset($data['SSL_ACCESS'])) {
			switch($data['SSL_ACCESS']) {
				// SSL接続不許可
				case '0' :
					if($_SERVER['HTTPS'] == 'on') {
						$dba->free($stmt);
						$dba->close();
						$status = DEF_RETCD_AERR;
						$CgiOut->set_status($status);
						$CgiOut->err_output();
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
						dbl("SSL不許可");
						exit;
					}
					break;
				// SSL接続許可
				case '1' :
					break;
				// SSL接続必須
				case '2' :
					if($_SERVER['HTTPS'] != 'on') {
						$dba->free($stmt);
						$dba->close();
						$status = DEF_RETCD_AERR;
						$CgiOut->set_status($status);
						$CgiOut->err_output();
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
						dbl("SSL必須");
						exit;
					}
					break;
				defailt:
					brak;
			}
		} else {
			$dba->free($stmt);
			$dba->close();
			$status = DEF_RETCD_AERR;
			$CgiOut->set_status($status);
			$CgiOut->err_output();
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			exit;
		}

		$referer_list = explode(";",  $data['ALLOW_REFERER']);

		/* IPチェック */
		if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
			if (!ip_check2($data['ALLOW_IP'], $_SERVER['REMOTE_ADDR'], ';')) {
				/* リファラチェック */
				if (!referer_check(&$referer_list, $_SERVER['HTTP_REFERER'])) {
					$dba->free($stmt);
					$dba->close();
					$status = DEF_RETCD_AERR;
					$CgiOut->set_status($status);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
					dbl("IP/リファラチェック エラー");
					exit;
				}
			}
		}
	} else {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("EMAP_CGI_CONF_TBL取得失敗");
		exit;
	}
	$dba->free($stmt);
}

/*==============================================*/
// RD利用設定
/*==============================================*/
if (!isRDAvailable($dba, $CID)) {
	$dba->close();
	$status = DEF_RETCD_AERR;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	dbl("RD利用許可 無効");
	exit;
}

/*==============================================*/
// RDデータ検索
/*==============================================*/
$arr_kyoten = selectRDData($dba, $CID, $arr_kid, $arr_grp);
if ($arr_kyoten === false) {
	$dba->close();
	$status = DEF_RETCD_DERR3;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	dbl("データ取得失敗");
	exit;
}

$dba->close();

$kyoten_count = count($arr_kyoten);
if (!$kyoten_count) {
	// 該当データ無し
	$status = DEF_RETCD_DNE;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}

// 該当データあり
$status = DEF_RETCD_DE;

/*==============================================*/
// 出力(正常)
/*==============================================*/
$CgiOut->set_status($status);
$CgiOut->output($CID, $arr_kyoten);
put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
?>
