<?php
// ---------------------------------------------------------
// �ڥ�ޥȱ�͢�����������ޥ�����return_code���
//
// 2016/04/25 T.Yoshino		yamatoCGI��	store_nearserch�ѥ꥿���󥳡���
// 2016/10/19 Y.Matsukawa	��ޥȱ�͢����ŹƬ����API��ytc_store_nearsearch.cgi���б�
// ---------------------------------------------------------

function getYamatoRetCd( $RetKey ){
	
	// YAMATO����status�Ѱ�
	switch ( $RetKey ) {
		case "10000";
			$RetMsg = "�׵ᤵ�줿API�ϸ��ߡ����ƥʥ���Ǥ���";
			$RetMsgID = "ERROR_MAINTENANCE";
			$RetCd = "1";
			break;
			
		case "10001";
			$RetMsg = "ǧ�ڥ�����ͭ�������ڤ�Ǥ���";
			$RetMsgID = "EXPIRY_ACCESS_TOKEN";
			$RetCd = "2";
			break;
			
		case "10002";
			$RetMsg = "���������ȡ����󤬶����⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_ACCESS_TOKEN";
			$RetCd = "3";
			break;
			
		case "10003";
			$RetMsg = "�׵ᤵ�줿API�ϸ��ߡ��۵ޥ��ƥʥ���Ǥ���";
			$RetMsgID = "URGENT_MAINTENANCE";
			$RetCd = "5";
			break;
			
		case "10004";
			$RetMsg = "�����оݥե饰�������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "00000";
			$RetMsg = "���˸��礦�ǡ���������ޤ�����";
			$RetMsgID = "SEARCH_RESULT";
			$RetCd = "0";
			break;
			
		case "00001";
			$RetMsg = "���˸��礦�ǡ����Ϥ���ޤ���Ǥ�����";
			$RetMsgID = "NO_SEARCH_RESULT";
			$RetCd = "0";
			break;
			
		case "01000";
			$RetMsg = "Ź�ޥǡ����١��������������顼�Ǥ���";
			$RetMsgID = "ERROR_TENPO_DB";
			$RetCd = "-1";
			break;
			
		case "01001";
			$RetMsg = "ǧ�ڥ��顼�Ǥ���";
			$RetMsgID = "ERROR_AUTH";
			$RetCd = "4";
			break;
			
		case "01002";
			$RetMsg = "�����оݥե饰�������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_SEARCH_KBN";
			$RetCd = "3";
			break;
			
		case "01003";
			$RetMsg = "����Ū��ͽ�����ʤ�����ˤ���׵�������������Ǥ��ޤ���Ǥ�����";
			$RetMsgID = "ERROR_SYSTEM";
			$RetCd = "-1";
			break;
			
		case "09000";
			$RetMsg = "����ɬ�ܹ��ܡ�͹���ֹ�ڤӰ��١����١ˤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09001";
			$RetMsg = "���ID�������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09002";
			$RetMsg = "����ɬ�ܹ��ܡ�͹���ֹ�ڤӰ��١����١ˤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09003";
			$RetMsg = "����ɬ�ܹ��ܡ�͹���ֹ�ڤӰ��١����١ˤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09004";
			$RetMsg = "͹���ֹ椬�����⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09005";
			$RetMsg = "����ʱ���˰��٤������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09006";
			$RetMsg = "����ʱ���˷��٤������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09007";
			$RetMsg = "�����ʺ����˰��٤������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09008";
			$RetMsg = "�����ʺ����˷��٤������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09009";
			$RetMsg = "������Υ�ʷ��١ˤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "09010";
			$RetMsg = " ���̵�Υ�ʰ��١ˤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		// add 2016/10/19 Y.Matsukawa [
		case "99001";
			$RetMsg = "��ãô��Ź��Ź�ޥ����ɤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99002";
			$RetMsg = "Ź�޼��̤������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99003";
			$RetMsg = "����Ƚ���ʬ�������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99004";
			$RetMsg = "�����ǽ�����ε������������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99005";
			$RetMsg = "�����ؿ��������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99006";
			$RetMsg = "��������������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99007";
			$RetMsg = "�����Ƚ礬�����⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99008";
			$RetMsg = "ʸ�������ɤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99009";
			$RetMsg = "�ݥ���ȥե饰�������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99010";
			$RetMsg = "¬�ϷϤ������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99011";
			$RetMsg = "���Ϸ����������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
			
		case "99012";
			$RetMsg = "�������ؤ��ݴɴ��¤�᤮�Ƥ��ޤ���";
			$RetMsgID = "EXPIRE_COOL";
			$RetCd = "3";
			break;
			
		// add 2016/10/19 Y.Matsukawa ]
	}
	
	return array($RetMsg,$RetMsgID,$RetCd);

}
?>