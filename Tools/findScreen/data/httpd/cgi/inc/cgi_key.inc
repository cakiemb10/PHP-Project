<?php
// ---------------------------------------------------------
// ����ե����� API����
// ---------------------------------------------------------
$hostname = trim(`hostname`);
//**********************************************************
//* �Ķ��ˤ���������Ƥ�����
//2011/09/02 VM�����Х�꡼�����ϡ�host̾���ѹ��ˤʤ뤬�����ֵ��˷Ҥ��Τǡ����ڵ���case���ɲäϤ��ʤ�
//	2012/03/08	H.Osamoto		����cgiweb��VIP�ڤ��ؤ�
//								��ȯ�Ķ���cgiweb�������ѹ���devapiweb(10.47.50.15)��dev-cgiweb(10.47.50.33)��
//	2012/04/11	H.Osamoto		����cgiweb�ڤ��ؤ� �ɥᥤ��(GIP)��VIP
//**********************************************************
switch( $hostname ){//----- ��ȯ�� -----
//	case "devemapweb":	mod 2012/03/08 H.Osamoto
case "dev-storenaviweb01":

	// mod 2012/03/08 H.Osamoto [
	//	$API_SSAPI_SRV  = "10.47.50.15";
	//	$D_CGI_KEY = '41nQPzCfng0vBlngcPBsnALf9AmglPBbjgrzDcngvynnnQGyvHng3b52mQrn7xngxzF0mwfXFQmgczF3nQKbT1';
	$API_SSAPI_SRV  = "10.47.50.33";
	$D_CGI_KEY = '41nQXzCDnQpvBvngxPBcnAgf9dmgqPBjjgjzDIngWynQnQ4yv5ngeb5hmQyn7angVzFQmwnXFkmgfzFxmAKPTz';
	// mod 2012/03/08 H.Osamoto ]
    break;

//----- ���ڵ� -----
case "emapweb00":

	$API_SSAPI_SRV  = "test.api.e-map.ne.jp";
	#$D_CGI_KEY = '45nQzzCgnQuzCkngezB7nAlf90mg4PBQjgMzDBngPudpnQMypMngXPAmnwkf7rnQ9vD7oQDvAjnBd8CAnwuPFFngdj4D'; 
	$D_CGI_KEY = '45nQ6zCYnQPzCUnggzB2nAIf9NmgfPBbjgDzD6nghudQnQSypwng6PAznw2f7wnQ8vDfoQ1vAmnBu8CDnwSnFUngpbBd';
	break;

//----- VM���ڵ� -----
case "storenaviweb-v01":

	//	$API_SSAPI_SRV  = "172.16.164.10";	mod 2012/03/08 H.Osamoto
	$API_SSAPI_SRV  = "172.28.0.156";
	//$D_CGI_KEY = '45nQ6zCYnQPzCUnggzB2nAIf9NmgfPBbjgDzD6nghudQnQSypwng6PAznw2f7wnQ8vDfoQ1vAmnBu8CDnwSnFUngpbBd';
	$D_CGI_KEY = "40nQmP9ClggvBQnATvBJnAJf9Pmg9PBFjgdzDgngHudhnQxypRng1PAHnwJf7UngTXBToQ5r9NoQdzFFpR6zT8";
	break;

//----- ���ֵ� -----
default:

	// mod 2012/04/11 H.osamoto [
	//	$API_SSAPI_SRV  = "api.e-map.ne.jp";
	//	$D_CGI_KEY = '45nQ6zCYnQPzCUnggzB2nAIf9NmgfPBbjgDzD6nghudQnQSypwng6PAznw2f7wnQ8vDfoQ1vAmnBu8CDnwSnFUngpbBd';
	$API_SSAPI_SRV  = "172.28.0.56";
	$D_CGI_KEY = '40nQbP9LlgqvBanA3vB5nARf9XmgsPBmjgezDSngBudtnQ5ypvngHPALnwxf7dngmXB7oQBr8SoQszFwpRnzTg';
	// mod 2012/04/11 H.osamoto ]
}

?>