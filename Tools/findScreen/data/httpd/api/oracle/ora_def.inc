<?php
/*========================================================*/
// 更新履歴
//   ・2007/08/03 Y.Matsukawa   LOGスキーマへの接続を追加
//   ・2016/06/27 H.Osamoto		店舗情報と認証データの参照先DBを分離
/*========================================================*/
switch( $hostname ){
case "dev-storenaviweb01":
case "storenaviweb-v01":
case "storenaviweb-v02":

	define( "ORA_TNS", "mst");
	define( "ORA_USER", "emap");
	define( "ORA_PASS", "emap");

	define( "ORA_TNS_AUTH", "mst");

	define( "ORA_TNS_LOG", "mst");
	define( "ORA_USER_LOG", "log");
	define( "ORA_PASS_LOG", "log");
	break;

default:

	define( "ORA_TNS", "pub");
	define( "ORA_USER", "emap");
	define( "ORA_PASS", "emap");

	define( "ORA_TNS_AUTH", "mst");

	define( "ORA_TNS_LOG", "pub");
	define( "ORA_USER_LOG", "log");
	define( "ORA_PASS_LOG", "log");
	break;
}
?>
