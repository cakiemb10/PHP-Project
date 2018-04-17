<?php
// ---------------------------------------------------------
// �ڥ�ޥȱ�͢�����������ޥ�����return_code���
//
// 2016/04/25 T.Yoshino		yamatoCGI��	store_nearserch�ѥ꥿���󥳡���
// 2016/12/12 H.Yasunaga	��ޥȥ��å����б��Ѥ�status���ɲ�
// 2017/01/17 H.Yasunaga	ytc_ret_def.inc�ե������ʸ�������ɤ�UTF-8����EUC���ѹ�
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
			$RetMsg = "���������ȡ�����ͭ�������ڤ�Ǥ���";
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
			
		// add 2016/12/12 H.Yasunaga ���å����б� [
		case "09011";
			// K�ѥ�᡼��(17�Х�����)��"1"�ξ��˽в�ͽ������ɬ�ܤˤʤꡢ�в�ͽ�����ѥ�᡼����̵��or����
			$RetMsg = "�в�ͽ�����������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
		case "09012";
			// K�ѥ�᡼��(17�Х�����)��"1"�ξ���ȯ��͹���ֹ椬ɬ�ܤˤʤꡢȯ��͹���ֹ�ѥ�᡼����̵��or����
			$RetMsg = "ȯ��͹���ֹ椬�����⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
		case "09013";
			// K�ѥ�᡼��(17�Х�����)��"1"�ξ��˥ܥå�����������ʬ��ɬ�ܤˤʤꡢ�ܥå�����������ʬ�ѥ�᡼����̵��or����
			$RetMsg = "�ܥå�����������ʬ�������⤷�����������ͤǤ���";
			$RetMsgID = "INVALID_PARAMETER";
			$RetCd = "3";
			break;
		// add ]
			
	}
	
	return array($RetMsg,$RetMsgID,$RetCd);

}
?>