<?PHP
// ------------------------------------------------------------
// ������͹���۵�URL����Υ�����쥯����
// 
// 2016/06/20 Y.Matsukawa	��������
// ------------------------------------------------------------

// ����͹���ɥᥤ��ʳ���404
if ($_SERVER["HTTP_HOST"] != 'map.japanpost.jp') {
	header("HTTP/1.0 404 Not Found");
	exit;
}

// Ź�޾ܺ٤إ�����쥯��
$url = 'http://map.japanpost.jp/mobile/search/d.htm?ksid=' . $_GET['id'];
header('Location: '.$url);
exit;

?>
