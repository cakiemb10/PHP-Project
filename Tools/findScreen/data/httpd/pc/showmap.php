<?PHP
// ------------------------------------------------------------
// 【日本郵政】旧URLからのリダイレクト用
// 
// 2016/06/20 Y.Matsukawa	新規作成
// ------------------------------------------------------------

// 日本郵政ドメイン以外は404
if ($_SERVER["HTTP_HOST"] != 'map.japanpost.jp') {
	header("HTTP/1.0 404 Not Found");
	exit;
}

// 店舗詳細へリダイレクト
$url = 'http://map.japanpost.jp/p/search2/shop_dtl.htm?dtlkey=43&id=' . $_GET['id'];
header('Location: '.$url);
exit;

?>
