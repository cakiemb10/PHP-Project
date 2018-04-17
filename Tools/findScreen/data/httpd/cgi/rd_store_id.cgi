<?php
/*========================================================*/
// �ե�����̾��rd_store_id.cgi
// ����̾��Ź�޻���ꥢ�륿����ǡ�������
//
// ��������
// 2013/02/20 Y.Matsukawa	��������
/*========================================================*/
/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = 'y11';

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));

/*==============================================*/
// �꥿���󥳡������
/*==============================================*/
define( 'DEF_RETCD_DE',   '00000' );       //���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
define( 'DEF_RETCD_DEND', '00001' );       //���˸��礦�ǡ�������ʸ�³�ǡ��������
define( 'DEF_RETCD_DNE',  '11009' );       //���˸��礦�ǡ����ʤ�
define( 'DEF_RETCD_AERR', '12009' );       //ǧ�ڥ��顼
define( 'DEF_RETCD_DERR1','17900' );       //�ǡ����١��������������顼
define( 'DEF_RETCD_DERR2','17002' );       //�ǡ����١��������������顼
define( 'DEF_RETCD_DERR3','17999' );       //�ǡ����١��������������顼
define( 'DEF_RETCD_PERR1','19100' );       //���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
define( 'DEF_RETCD_PERR2','19200' );       //���ϥѥ�᡼�����顼(��ʸ���顼)
define( 'DEF_RETCD_PERR3','19200' );       //���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)

/*==============================================*/
// ����ե�����
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
// �����
/*==============================================*/
// ���ơ�����(�꥿���󥳡���)
if (!isset($status)){
	 $status = '00000';
}

/*==============================================*/
//�����ϳ���
/*==============================================*/
include('logs/inc/com_log_open.inc');

/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$CID	= getCgiParameter('cid', '');		// ���ID
$KID	= getCgiParameter('kid', '');		// ����ID��ʣ����
$KID	= str_replace(' ', '', $KID);
$GRP	= getCgiParameter('grp', '');		// ���롼���ֹ��ʣ����
$GRP	= str_replace(' ', '', $GRP);
$ENC	= getCgiParameter('enc', 'UTF8');	// ʸ��������
$OUTF	= getCgiParameter('outf','JSON');	// ���Ϸ���
$INTID	= getCgiParameter('intid', '');		// �������ѻ��Υ��ץ�ID

// ���ϥ����å��Ѥˡ�$ENC�򥳥ԡ�(store_enc.inc��Ƥ֤Ⱦ�����ѹ�����뤿��)
$INPUT_ENC = $ENC ;

$OPTION_CD = ($INTID ? $INTID : $CID);

// ���Ϸ���
if ($OUTF != 'JSON' && $OUTF != 'XML') {
	$OUTF = 'JSON';
}

include('store_enc.inc');			// ʸ���������Ѵ�

/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
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
// ���ϥ��饹
/*==============================================*/
$CgiOut = new RdStoreCgiOutput($CGICD, $CGINM, $ENC, $OUTF);

/*==============================================*/
// �ѥ�᡼�������å�
/*==============================================*/
// ���ID
if ($CID == '') {
	$status = DEF_RETCD_PERR1;//���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}
// ����ID
if ($KID == '') {
	$status = DEF_RETCD_PERR1;//���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}
// ʣ�������¡�1000
$arr_kid = explode(',', $KID);
$k_count = count($arr_kid);
if ($k_count > 1000) {
	$status = DEF_RETCD_PERR2;//���ϥѥ�᡼�����顼(��ʸ���顼)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}
// ���롼��ID
$arr_grp = array();
if ($GRP != '') {
	$arr_tmp = explode(',', $GRP);
	$grp_count = count($arr_tmp);
	// ʣ�������¡�20
	if ($grp_count > 20) {
		$status = DEF_RETCD_PERR2;//���ϥѥ�᡼�����顼(��ʸ���顼)
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		exit;
	}
	// �������ͤ����
	foreach ($arr_tmp as $grp_no) {
		if (ctype_digit($grp_no) && strlen($grp_no) <= 5) {
			$arr_grp[] = $grp_no;
		}
	}
}
// �������ѻ���ID
if ($INTID != '') {
	if (!in_array($INTID, $D_INTID)) {
		$status = DEF_RETCD_AERR;//ǧ�ڥ��顼
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("INTID����");
		exit;
	}
}
// ʸ��������
if ($INPUT_ENC != 'SJIS' && $INPUT_ENC != 'EUC' && $INPUT_ENC != 'UTF8') {
	$status = DEF_RETCD_PERR2;//���ϥѥ�᡼�����顼(��ʸ���顼)
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}

/*==============================================*/
// DB��³�����ץ�
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
	// �����ӥ�����
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
		dbl("�����ӥ����ֳ�");
		exit;
	}

	/*==============================================*/
	// CGI���ѵ���
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
		dbl("CGI���ѵ��� ��������");
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
			dbl("CGI���ѵ��� ̵��");
			exit;
		}
	} else {
		$dba->free($stmt);
		$dba->close();
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("CGI���ѵ��� ̵��");
		exit;
	}
	$dba->free($stmt);

	/*==============================================*/
	// SSLǧ�ڡ�IP�����å�����ե�������å�
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
		dbl("EMAP_CGI_CONF_TBL��������");
		exit;
	}
	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		/* SSL��³���� */
		if (isset($data['SSL_ACCESS'])) {
			switch($data['SSL_ACCESS']) {
				// SSL��³�Ե���
				case '0' :
					if($_SERVER['HTTPS'] == 'on') {
						$dba->free($stmt);
						$dba->close();
						$status = DEF_RETCD_AERR;
						$CgiOut->set_status($status);
						$CgiOut->err_output();
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
						dbl("SSL�Ե���");
						exit;
					}
					break;
				// SSL��³����
				case '1' :
					break;
				// SSL��³ɬ��
				case '2' :
					if($_SERVER['HTTPS'] != 'on') {
						$dba->free($stmt);
						$dba->close();
						$status = DEF_RETCD_AERR;
						$CgiOut->set_status($status);
						$CgiOut->err_output();
						put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
						dbl("SSLɬ��");
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

		/* IP�����å� */
		if (!ip_check($D_IP_LIST, $_SERVER['REMOTE_ADDR'])) {
			if (!ip_check2($data['ALLOW_IP'], $_SERVER['REMOTE_ADDR'], ';')) {
				/* ��ե�������å� */
				if (!referer_check(&$referer_list, $_SERVER['HTTP_REFERER'])) {
					$dba->free($stmt);
					$dba->close();
					$status = DEF_RETCD_AERR;
					$CgiOut->set_status($status);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
					dbl("IP/��ե�������å� ���顼");
					exit;
				}
			}
		}
	} else {
		$status = DEF_RETCD_AERR;
		$CgiOut->set_status($status);
		$CgiOut->err_output();
		put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
		dbl("EMAP_CGI_CONF_TBL��������");
		exit;
	}
	$dba->free($stmt);
}

/*==============================================*/
// RD��������
/*==============================================*/
if (!isRDAvailable($dba, $CID)) {
	$dba->close();
	$status = DEF_RETCD_AERR;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	dbl("RD���ѵ��� ̵��");
	exit;
}

/*==============================================*/
// RD�ǡ�������
/*==============================================*/
$arr_kyoten = selectRDData($dba, $CID, $arr_kid, $arr_grp);
if ($arr_kyoten === false) {
	$dba->close();
	$status = DEF_RETCD_DERR3;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	dbl("�ǡ�����������");
	exit;
}

$dba->close();

$kyoten_count = count($arr_kyoten);
if (!$kyoten_count) {
	// �����ǡ���̵��
	$status = DEF_RETCD_DNE;
	$CgiOut->set_status($status);
	$CgiOut->err_output();
	put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
	exit;
}

// �����ǡ�������
$status = DEF_RETCD_DE;

/*==============================================*/
// ����(����)
/*==============================================*/
$CgiOut->set_status($status);
$CgiOut->output($CID, $arr_kyoten);
put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
?>
