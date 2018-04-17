<?php
/*=========================================================*/
// �ե�����̾��myarea_func.inc
//
// My���ꥢ�Ѷ��̴ؿ�
//
// ��������2011/04/11
// �����ԡ�H.Osamoto
//
// ���⡧My���ꥢ�Ѷ��̴ؿ�
//
// ��������
// 2011/04/11 H.Osamoto	��������
/*=========================================================*/

/*==============================================*/
// My���ꥢ�ǡ�������
/*==============================================*/
function select_myarea($dba, $corp_id, $user_id, &$hit_num, &$retdata){
    $sql = "SELECT * ";
    $sql .= "FROM MYAREA_TBL ";
    $sql .= "WHERE CORP_ID = '".$corp_id."' ";
    $sql .= "AND USER_ID = '".$user_id."'";
    $sql .= "ORDER BY DISP_ORDER";

    $stmt = null;

    if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
        $dba->free($stmt);
        return 9;   //sqlExecute()���顼
    }
    $retdata_all = array();
    while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
        $retdata_all[] = $data;
    }
    $hit_num = count ($retdata_all);
    if ( $hit_num <= 0 ) {
        $dba->free($stmt);
        return 1;   //������̥ǡ����ʤ�
    }
    $dba->free($stmt);

    $retdata = $retdata_all;

    return  0;
}

/*==============================================*/
// My���ꥢ�ǡ����ɲ�
/*==============================================*/
function myarea_add($dba, $corp_id, $user_id, $myarea_name, $lat, $lon, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_ADD( ";
	$spstr  .=  ":i_corp_id, :i_user_id, :i_myarea_name, :i_lat, :i_lon, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";

	$stmt = OCIParse($dba->conn, $spstr);

	if (!OCIBindByName($stmt, ':i_corp_id', $corp_id, 15)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_user_id', $user_id, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_myarea_name', $myarea_name, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_lat', $lat, 9)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_lon', $lon, 9)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}

	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

/*==============================================*/
// My���ꥢ̾����
/*==============================================*/
function myarea_name_update($dba, $myarea_id, $myarea_name, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_NAME_UPDT( ";
	$spstr  .=  ":i_myarea_id, :i_myarea_name, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";


	$stmt = OCIParse($dba->conn, $spstr);
	
	if (!OCIBindByName($stmt, ':i_myarea_id', $myarea_id, 8)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_myarea_name', $myarea_name, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}
	
	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

/*==============================================*/
// My���ꥢɽ���繹��
/*==============================================*/
function myarea_order_update($dba, $myarea_id, $corp_id, $user_id, $disp_order, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_ORDER_UPDT( ";
	$spstr  .=  ":i_myarea_id, :i_corp_id, :i_user_id, :i_disp_order, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";

	$stmt = OCIParse($dba->conn, $spstr);

	if (!OCIBindByName($stmt, ':i_myarea_id', $myarea_id, 8)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_corp_id', $corp_id, 15)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_user_id', $user_id, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_disp_order', $disp_order, 3)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}
	
	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

/*==============================================*/
// My���ꥢ���
/*==============================================*/
function myarea_del($dba, $myarea_id, $corp_id, $user_id, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_DEL( ";
	$spstr  .=  ":i_myarea_id, :i_corp_id, :i_user_id, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";

	$stmt = OCIParse($dba->conn, $spstr);

	if (!OCIBindByName($stmt, ':i_myarea_id', $myarea_id, 8)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_corp_id', $corp_id, 15)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_user_id', $user_id, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}

	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

// ------------------------------------------------------------
// �����¸ʸ�������å�
// (EUC-JP������ࡢ������Τߵ���)
// ------------------------------------------------------------
function IzonSearch( $str ) {

	// ���Х���ʸ����JIS X 212 ��������ˤ��ޤޤ�Ƥ����饨�顼
	// ��������������Τޤ���������Ƥ������ϡ������ǥեå�����ޤ�
	// ��IE�ʳ��Υ֥饦������������䡢CSV�ե����륢�åץ���������
	if (preg_match('/(\x8F[\xA1-\xFE][\xA1-\xFE])/', $str)) {
		return false;
	}

	// �ѡ�����ȥ��󥳡��ɤ��줿���Х���ʸ����JIS X 212 ��������ˤ��ޤޤ�Ƥ����饨�顼
	// ��IE�ʤɤ��顢������������󥳡��ɤ������������Ƥ������ϡ������ǥեå�����ޤ�
	// ����ˡ�&#28583;�ס�&AElig;��
	if (preg_match('/(&#[0-9]{1,};|&[a-zA-Z]{1,};)/', $str)) {
		return false;
	}

	// Ⱦ�ѥ��ʤ����ѥ��ʤ��Ѵ���Ⱦ�ѥ��ʤ����ߤ��Ƥ���ȡ�����ʸ��ȴ���Ф��˼��Ԥ��뤿��� 2007/08/13 add Y.Matsukawa
	$w_str = mb_convert_kana($str, 'K');

	// ����ʸ����ȴ���Ф�
	preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $w_str, $matchword );

	for ( $i=0; $i < count( $matchword[0] ) ; $i++) {
		if ( $matchword[0][$i] ) {
			// EUC-JP  ����ࡢ�������ʸ�������å�
			if ( ! preg_match( '/^(([\xA1-\xA8]|[\xB0-\xF4])[\xA1-\xFE])*$/', $matchword[0][$i]) ) {
				return false;
			}
		}
	}
	return true;
}

?>