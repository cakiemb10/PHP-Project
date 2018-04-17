<?php
/*========================================================*/
// �ե�����̾��sql_collection_get_icon_info.inc
//
// ��������2007/06/11
// �����ԡ�Y.Matsukawa
//
// ��������
//   ��2007/06/11 Y.Matsukawa   ��������
//   ��2007/07/11 Y.Matsukawa   ������̤ʤ��λ��˥꥽�����������Ƥ��ʤ��ä�
//   ��2013/08/05 N.Wada        ¨��ȿ���оݴ���б�
/*========================================================*/

//function select_icon_info( &$dba, $cid, &$retdata, &$err_msg ){	mod 2013/08/05 N.Wada
function select_icon_info( &$dba, $cid, &$retdata, &$err_msg, $immref=false ){
	//CORP_ID�򥭡���ICON_TBL��select����

	$sql = "select decode(ICON_ID, '@SEL', 1, '@SELB', 2, '@NEW', 3, 0) KBN";
	$sql.= ", ICON_ID, nvl(ICON_W,0) ICON_W, nvl(ICON_H,0) ICON_H";
	//$sql.= " from ICON_TBL";	mod 2013/08/05 N.Wada [
	if ( $immref ) {
		$sql.= " from IM_ICON_TBL";
	} else {
		$sql.= " from ICON_TBL";
	}
	// mod 2013/08/05 N.Wada ]
	$sql.= " where CORP_ID = '$cid'";
	$sql.= " order by KBN,ICON_ID";

	$stmt   = null;

	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()���顼
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$result = count($retdata);
	if ($result <= 0) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //������̥ǡ����ʤ�
	}
	$dba->free($stmt);
	return  0;
}

?>