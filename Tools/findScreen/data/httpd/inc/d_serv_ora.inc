<?php
$hostname = trim(`hostname`);
//**********************************************************
//* �Ķ��ˤ���������Ƥ�����
//2011/09/02 VM�����Х�꡼�����ϡ�host̾���ѹ��ˤʤ뤬�����ֵ��˷Ҥ��Τǡ����ڵ���case���ɲäϤ��ʤ�
//**********************************************************

switch( $hostname ){
//----- ��ȯ�� -----
case "devemapweb":
case "dev-storenaviweb01":       // add 2011/09/8 Y.Nakajima VM���ڿ���ȯ��
    define( "ORA_TNS", "mst");
    define( "ORA_USER", "emap");
    define( "ORA_PASS", "emap");
    define( "ORA_TNS_MST", "mst");	// add 2011/04/25 H.Osamoto
    break;
//----- ���ڵ� -----
case "emapweb00":
case "emapweb06":		// ���굡			add 2011/02/09 Y.Matsukawa
case "storenaviweb-v01":       // add 2011/08/08 Y.Nakajima VM���ڵ� ServerReName
case "storenaviweb-v02":       // add 2011/09/08 Y.Nakajima VM���ڵ���
    define( "ORA_TNS", "mst");
    define( "ORA_USER", "emap");
    define( "ORA_PASS", "emap");
    define( "ORA_TNS_MST", "mst");	// add 2011/04/25 H.Osamoto
    break;
//----- ���ֵ� -----
//case "storenaviweb-v01":       // add 2011/09/16 Y.Nakajima VM���ڵ� ServerReName
default:
    define( "ORA_TNS", "pub");	//mod 2011/11/04 Y.Matsukawa
    //define( "ORA_TNS", "mst");	mod 2011/11/18 Y.Nakajima
    define( "ORA_USER", "emap");
    define( "ORA_PASS", "emap");
    define( "ORA_TNS_MST", "mst");	// add 2011/04/25 H.Osamoto
	break;
}
?>