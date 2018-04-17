<?php
/*=========================================================*/
// �ե�����̾��function_LAWSONCAMPAIGN.inc
//
// �������󥭥��ڡ����б��ڣ��������ۥ������ޥ����ؿ�
// 
// ��������
// 2017/04/12 H.Yasunaga	��������
/*=========================================================*/

	// �������󥭥��ڡ���Υ����ڡ���ID��¸�ߥ����å�
	function exist_campaignid(&$dba, $campaignid) {
		$sql = "SELECT count(*) as CNT FROM LAWSON_CAMPAIGN_TBL where CPNID = '" . escapeOra($campaignid) . "'";
		$stmt = null;
		if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
			$dba->free($stmt);
			return null;   //sqlExecute()���顼
		}
		$retdata = 0;
		while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
			$retdata = $data['CNT'];
		}
		
		$dba->free($stmt);
		
		if (intval($retdata) > 0) {
			// �����ڡ���ID��¸�ߤ���
			return true;
		} else {
			// �����ڡ���ID��¸�ߤ��ʤ�
			return false;
		}
	}
	
	// �����������ξ��˥����ڡ���ID��ɳ�Ť�Ź��ID���оݤˤ���
	function edit_jkn_campaign($edit_jkn, $campaignid) {
		
		$ret = "";
		if (strlen($edit_jkn) > 0) {
			$ret = $edit_jkn;
			$ret .= " AND ";
		}
		$ret .= "( kyoten_id in (select STOREID from LAWSON_CAMPAIGN_TBL where CPNID = '" . escapeOra($campaignid) . "') )";
		return $ret;
	}
?>