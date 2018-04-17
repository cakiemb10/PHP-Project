<?php
/*========================================================*/
// �ե�����̾��test_myarea_select.cgi
// ����̾����myarea_select.cgi�ƥ�����CGI��
//
// ��������
// 2011/04/08 H.Osamoto		��������
/*========================================================*/
header( "Content-Type: Text/html; charset=euc-jp" );

include("ZdcCommonFunc.inc");

$hostname = trim(`hostname`);
switch( $hostname ){
case 'devemapweb':
	$IP = "218.225.89.139";
	break;
case 'emapweb00':
case 'emapweb06':
	$IP = "test.e-map.ne.jp";
	break;
default:
	$IP = "www.e-map.ne.jp";

}
$url = "http://$IP/cgi/myarea_select.cgi?corp_id=$corp_id&user_id=$user_id";

$dat = ZdcHttpRead($url,0,30);
$cnt  = $dat[0];

//echo $url."<br>";
//echo"��dat<PRE>";print_r($dat);echo"<PRE>";

for($i = 0; $i < $cnt; $i++) {
	$rec = explode("\t",$dat[$i+1]);

	$lst[$i]["myarea_id"] = $rec[0];
	$lst[$i]["corp_id"] = $rec[1];
	$lst[$i]["user_id"] = $rec[2];
	$lst[$i]["myarea_name"] = $rec[3];
	$lst[$i]["lat"] = $rec[4];
	$lst[$i]["lon"] = $rec[5];
	$lst[$i]["disp_name"] = $rec[6];
}

for($i = 0; $i < $cnt; $i++) {
	$pcnt = $i+1;
	
	echo"<PRE>��lst[$i]<br>";print_r($lst[$i]);echo"<PRE><br>";
}

?>