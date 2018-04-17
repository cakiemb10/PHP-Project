<?php
$hostname = trim(`hostname`);
//**********************************************************
//* 環境により設定内容を切替
//2011/09/02 VMサーバリリース時は、host名が変更になるが、本番機に繋ぐので、検証機のcaseを追加はしない
//**********************************************************

switch( $hostname ){
//----- 開発機 -----
case "devemapweb":
case "dev-storenaviweb01":       // add 2011/09/8 Y.Nakajima VM検証新開発機
    define( "ORA_TNS", "mst");
    define( "ORA_USER", "emap");
    define( "ORA_PASS", "emap");
    define( "ORA_TNS_MST", "mst");	// add 2011/04/25 H.Osamoto
    break;
//----- 検証機 -----
case "emapweb00":
case "emapweb06":		// 暫定機			add 2011/02/09 Y.Matsukawa
case "storenaviweb-v01":       // add 2011/08/08 Y.Nakajima VM検証機 ServerReName
case "storenaviweb-v02":       // add 2011/09/08 Y.Nakajima VM検証機新
    define( "ORA_TNS", "mst");
    define( "ORA_USER", "emap");
    define( "ORA_PASS", "emap");
    define( "ORA_TNS_MST", "mst");	// add 2011/04/25 H.Osamoto
    break;
//----- 本番機 -----
//case "storenaviweb-v01":       // add 2011/09/16 Y.Nakajima VM検証機 ServerReName
default:
    define( "ORA_TNS", "pub");	//mod 2011/11/04 Y.Matsukawa
    //define( "ORA_TNS", "mst");	mod 2011/11/18 Y.Nakajima
    define( "ORA_USER", "emap");
    define( "ORA_PASS", "emap");
    define( "ORA_TNS_MST", "mst");	// add 2011/04/25 H.Osamoto
	break;
}
?>
