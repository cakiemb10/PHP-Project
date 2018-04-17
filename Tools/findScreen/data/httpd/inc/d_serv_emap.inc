<?php
// ---------------------------------------------------------
// 定義ファイル サーバー設定
// 
// 新規作成 : ogawa 
// 2009/11/10 Y.Matsukawa	開発機VM化
// 2009/11/26 Y.Matsukawa	アクセス集中対応
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/08/10 Y.Matsukawa	開発機から検証機APIを使用するよう変更
// 2011/02/10 Y.Matsukawa	高速化
// 2011/03/10 Y.Matsukawa	スマートフォン版対応
// 2011/04/13 H.Osamoto		Myエリア対応
// 2011/07/07 H.Osamoto		マツキヨ用API2.0対応版
// 2011/07/13 Y.Matsukawa	スマホ機能追加（ルート探索、最寄駅）
// 2011/07/04 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/09/14 K.Masuda		スマホURL追加  
// 2011/10/26 Y.Matsukawa	PC2.0（画面遷移版）対応
// 2011/11/02 Y.Matsukawa	店舗案内CGI汎用版対応
// 2011/12/26 H.Osamoto		セブンミール業務支援用に「mselectaddr」の定義を追加
// 2012/02/13 Y.Matsukawa	企業画像（CORP_IMG_TBL）対応
// 2012/03/08 H.Osamoto		検証cgiwebのVIP切り替え
//							開発環境のcgiweb向き先変更「cgiweb-p01_VIP(172.28.0.156)⇒dev-cgiweb(10.47.50.33)」
// 2012/03/15 N.Wada		ドコモプレミア専用GIPに対応
// 2012/04/09 H.Osamoto		本番cgiwebのVIP切り替え
// 2012/07/25 H.Osamoto		PC2.0URL追加
// 2013/03/26 H.Iijima      URL追加(rd_store_id.cgi)
// 2013/05/23 H.Osamoto		開発環境のapiweb&cgiweb向き先変更「開発⇒検証」
//							「EMAP_SSAPI_SRV」の設定をlocalhost(127.0.0.1)に変更
// 2013/07/10 Y.Matsukawa	ヤマト運輸向けカスタマイズ（CGI呼び出し）
// 2013/08/01 Y.Matsukawa	機能追加：路線検索
// 2014/01/16 H.Osamoto		ルート探索CGI追加
// 2014/01/27 F.Yokoi		ドコモプレミア専用GIP→ドメインへ変更
// 2014/02/19 H.Osamoto		車ルート探索CGI追加
// 2014/05/16 Y.Matsukawa	商品マスタ対応
// 2014/05/22 H.Osamoto		マツキヨ用サブドメイン、損保ジャパン用ドメイン設定
// 2014/07/04 Y.Matsukawa	デイリーヤマザキ アクセス増対応（専用ドメイン）
// 2014/08/13 F.Yokoi		損保ジャパン用 PC1.0対応及びスマホ用APIキー変更
// 2014/10/09 H.Osamoto		スマホAPI2.0用の定義を追加
// 2015/01/09 Y.Matsukawa	ゼンショー用ドメイン対応（検証用）
// 2015/01/21 Y.Matsukawa	ゼンショー用ドメイン対応
// 2015/02/03 H.Osamoto		スマホAPI2.0用の定義を変更
// 2015/02/25 Y.Matsukawa	定義追加：D_DOMAIN_L
// 2015/04/03 H.Osamoto		PC2.0損保ジャパン用ドメイン対応
// 2015/04/28 Y.Uesugi		ピジョン社内向け検索対応
// 2015/05/13 N.Wada		日本設備工業用に「nsnet01_syainnm」の定義を追加
// 2015/06/29 H.Osamoto		ゼンショー用ドメインにエルトリート(zen012)を「maps.eltorito.jp」を追加
// 2015/09/14 Y.Matsukawa	スマホ2.0：未サポートブラウザでもロード
// 2015/10/19 F.Yokoi		ドコモプレミア用設定を企業ID dpointでも有効とする
//							ドコモプレミアのスマホAPI2.0の設定を有効にする
// 2015/11/13 Y.Matsukawa	ドコモiD用ドメイン対応
// 2015/11/18 H.Osamoto		GPSログ集計用出力cgi定義追加
// 2015/12/15 Y.Uesugi		ヤマト用 祝日取得cgi定義追加
// 2016/02/15 F.Yokoi		JTB用ドメイン対応
// 2016/03/10 Y.Matsukawa	英語版対応（住所フリーワード検索）
// 2016/03/31 F.Yokoi		英語版対応
// 2016/05/06 N.Wada		スマホサイトURLのHTTP,HTTPS両対応
// 2016/05/19 T.Yoshino         ゼンショー用ドメイン追加(zen099)
// 2016/06/06 H.Osamoto		柏iDC移行対応
// 2016/06/13 Y.Matsukawa	日本郵政用郵便番号検索
// 2016/06/20 Y.Matsukawa	日本郵政専用ドメイン対応
// 2016/07/27 Y.Uesugi		SSL許可時のアイコンCGI SSL対応
// 2016/08/15 Y.Matsukawa	Google版 測地系変換高精度
// 2016/11/14 Y.Uesugi		複合フリーワード検索 住所カナ検索対応
// 2016/11/16 Y.Matsukawa	日本郵政向けマップタイプ対応
// 2016/11/21 T.Yoshino		吉野家ドメイン対応
// 2016/12/20 Y.Uesugi		ファイザー（すぐ禁煙）ドメイン対応
// 2017/03/21 Y.Uesugi		佐川急便 住所分割対応に「selectaddr_kyoto.cgi」の定義を追加
// 2017/04/17 Y.Uesugi		ゼンショー（zen000）SSL対応
// 2017/04/28 Y.Uesugi		ゼンショー SSL対応
// 2017/05/01 Y.Uesugi		ゼンショー SSL対応(zen071)
// ---------------------------------------------------------

// ゼンショー用ドメインかどうか判定		add 2015/01/09 Y.Matsukawa
// ※事前検証用に社内検証cid（9999999R）も許可しています。
function ZenshoDomain($domain, $cid) {
	switch ($domain) {
		// ホールディングス（zen000）
		case 'maps.zensho.co.jp':
			if (!in_array($cid, array('zen000','zen000test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			//return array('domain'=>$domain, 'apikey'=>'41nfUeGJbc7yplX5lnTprxizTCrx4zTDrtxS40WsVz0poBj3GkbcpyA7oMDKOoYMFmL0YBl9QSYBK9JGXxQLT4');
			return array('domain'=>$domain, 'apikey'=>'42nfweGXbc2ypFX5anTCrxrzTcrx3zTXrtGS4eWsqyAOlR62E6YdYuD7XBq90uadD9AnZt02Feb6Q2FLZM2zJ8');		//add 2017/04/17 Y.Uesugi
			break;
		// すき家（zen004）
		case 'maps.sukiya.jp':
			if (!in_array($cid, array('zen004','zen004test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'39nfJeG7bc0yp2X5MnT9rxCzTYrxtzTIrtAS49WsEyAIlRV2EGYdtuDAXBk9AUWdyGKdVdyvFZZM1zJJ');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'38nf5eGdbcgypuX5tnTkrxDzTxrxozT9rtNS4cWsmz0ZoB43G7bcQyALoMFm5MZ6PO9TbhC9JLXxbLTJ');
			}
			break;
		// ココス（zen010）
		case 'maps.cocos-jpn.co.jp':
			if (!in_array($cid, array('zen010','zen010test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'44nf8eGHbcjypLX5TnTXrxGzTarxFzTjrt8S4EWsiz0coB73GnbcUyARoNamEUb6d3AOodjKDJYRS9QrYBf9JKXxBLT3');
			break;
		// 宝島（zen013）
		case 'maps.takarajima.co.jp':
			if (!in_array($cid, array('zen013','zen013test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'46nf9eGlbcAypsX5TnT2rxvzTlrxczTkrtkS4SWsByAxlRQ2EeYdLuD2XBo94dbdNGS5XNsuJyZd65ShoNPmEFoNDKDVpRPzTL');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'45nfBeGObcwypsX5rnTJrxEzTErxvzT4rtIS4bWsHz0koBx3GLbczyAhoMKiSgZ6buBSbdfKK7YdovFab6f2FjZMBzJJ');
			}
			break;
		// ジョリーパスタ（zen001）
		case 'maps.jolly-pasta.co.jp':
			if (!in_array($cid, array('zen001','zen001test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'47nfMeGZbc1yp6X5wnTurxszTkrxqzTdrtFS48WsyyATlRj2ENYdquDrXBz9JJY6WCHMVhL5DIbcrm4Ibhz9Q1YBd9JjXxELTz');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'46nfTeGYbcGypuX5SnT2rxuzTTrxFzTNrtTS4tWs9z0IoBR3GubcDyAboNcKEMYtqC9cocRySnX75iSXoN2mEhoN0KD6pRxzTc');
			}
			break;
		// なか卯（zen009）
		case 'maps.nakau.co.jp':
			if (!in_array($cid, array('zen009','zen009test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'41nfgeGQbc6ypcX5mnTfrxxzTsrxczTtrtlS4EWsqyAZlRw2EAYdxuDMXB49FibdgGSIWhi9QtYB39JxXxcLT0');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'40nfBeGCbc6ypbX5unTlrxazTOrxJzTYrtRS4sWs0z0uoBz3GJbcIyACoN99SCZ6ou5OoNGmEjoNuKDwpRVzTj');
			}
			break;
		// ビッグボーイ（zen018）
		case 'maps.bigboyjapan.co.jp':
			if (!in_array($cid, array('zen018','zen018test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'47nfJeGNbcpypCX5snTKrx0zTkrx4zTprt0S4TWs6yA1lRq2EAYdiuDQXBE9R1ZdFWRUY7zOJbbc6yS0YRU9QLYBl9JlXxHLT6');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'46nf0eGdbclypJX5UnTXrxHzTZrxhzTFrt9S4cWsZz0boBw3GIbc9yA9oN2qKJa62qEdVdxKSCXtquFHoN0mEHoNDKDXpR8zTM');
			}
			break;
		// 華屋与兵衛（zen034）
		case 'maps.hanayayohei.co.jp':
			if (!in_array($cid, array('zen034','zen034test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'47nfGeGLbcSypVX5xnTorxIzTvrxRzTmrtlS4zWsVyAnlRI2EFYd0uD5XBx9Lvbdg9SwVdAu90Y6iSOKZhN9QcYBs9J6XxjLT0');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'46nfieGRbcPypPX5znTSrxQzT2rxkzTjrtKS4UWsVz0qoBW3GFbciyA5oNmSS3YNQu98bclOEzZtweKNoNEmEboNtKD6pR1zTb');
			}
			break;
		// エルトリート、牛庵（zen012、zen002）
		case 'maps.gyuan.jp':
			if (!in_array($cid, array('zen012','zen012test','zen002','zen002test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'38nf4eGzbcByplX5CnT8rxjzTsrxqzTnrtTS4WWsLyA3lRV2EzYdHuDqXB89MIVc7eSMYRV9JqXxBLTh');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'37nf4eG1bcdypYX5InT4rxxzTArxxzTWrtiS4fWsuz0BoBK3Grbc5yAaoNQW9TWdwuF1oNrKDYpRlzTg');
			}
			break;
		// 2015/06/29 H.Osamoto add [
		// エルトリート（zen012）
		case 'maps.eltorito.jp':
			if (!in_array($cid, array('zen012','zen012test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'40nfUeGGbcNypLX57nTarxdzTirxgzTirtaS4mWsHz0JoB93GIbcgyA5oNHeHlWt73BvZcXiEtoNcKDOpRpzTu');
			break;
		// 2015/06/29 H.Osamoto add ]
		// GM事業部（zen071）
		case 'maps.gmfoods.co.jp':
			if (!in_array($cid, array('zen071','zen071test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'43nfZeGxbcsypEX5CnTjrxRzTQrxnzT4rtuS4mWsQyAwlRZ2EuYdmuDGXBS9MvYdsaERY6ziA4oNvmEsoNoKD2pRUzTX');		//add 2017/05/01 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'42nfoeGCbcjypUX5BnT5rxuzTfrxBzT0rtJS4uWstz0GoBR3GEbcZyAaoNPWGPaNJ3ECasznF6b6x2FUZMAzJq');
			}
			break;
		// はま寿司（zen011）
		case 'maps.hamazushi.com':
			if (!in_array($cid, array('zen011','zen011test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'43nfAeGvbcSypkX5ynTOrxPzT1rxazTdrt4S45WsIyAylRm2EAYdpuDMXBQ9L4bd75SdVMReA1ZtGPFTb6i3GMpR3zTr');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'42nfqeGwbcJypPX5inT7rxYzTqrxQzTGrtrS4CWswz0qoBw3Gsbc1yAEoNUSSiYdDu0GWcgmL3Zhu9Q8Y6p4J1');
			}
			break;
		// モリバコーヒー（zen036）
		case 'maps.morivacoffee.com':
			if (!in_array($cid, array('zen036','zen036test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'46nfreGFbc3ypHX5AnT9rxPzTgrxmzTirtvS4dWs5yALlRD2EIYdLuDxXBs9GZY7lqK5WNuuQGY6ZaNnadMfFnb633GrpRfzTt');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'45nfAeGtbcqypZX55nTVrxszTdrxVzTgrt8S46WsIz0goBB3GpbcVyAHoNr5E9XNSO6RbdwmEtaNnaOWah69QPY6Z4Jr');
			}
			break;
		// 久兵衛屋（zen005）
		case 'maps.kyubeiya.jp':
			if (!in_array($cid, array('zen005','zen005test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'40nfweGQbc0ypCX5KnTVrxfzThrx0zTqrtTS41WsDz0eoBV3GkbcYyA1oN9G9ZWdsqOTZcTOSXoN4KDYpRtzTM');
			break;
		// 瀬戸うどん（zen033）
		case 'maps.seto-udon.jp':
			if (!in_array($cid, array('zen033','zen033test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'41nfKeGAbcDypVX5RnTvrxWzTbrxazTJrtxS4bWsMz0noBy3GNbc2yAvoMymO8WtK2G2WdYiEBYRR9JXXxgLTF');
			break;
		// たもん庵（zen037）
		case 'maps.tamon-an.jp':
			if (!in_array($cid, array('zen037','zen037test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'40nfzeGabcCyp5X5inTCrxOzTvrx4zTMrt7S4TWsQz0eoB93GfbcayAioMCiSDYdS3FdodOuFEoNMKD7pRczTa');
			break;
		// マルヤ（zen040）
		case 'maps.maruya-group.co.jp':
			if (!in_array($cid, array('zen040','zen040test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'47nfIeGjbcBypaX50nTyrxpzTcrx5zTIrtCS4KWsxz02oBI3G2bcUyAKoNK5SoXMKe9BbhF5MHXNj35WXxM9QDYBF9JLXxCLTY');
			break;
		// マルエイ（zen045）
		case 'maps.maruei.info':
			if (!in_array($cid, array('zen045','zen045test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'40nf1eGLbclypwX5rnTirxazT4rxjzT8rtvS4mWslz0OoB63GUbcQyAloNX5SmXMLeOEZhk9KyYN7aEppR6zTv');
			break;
		// 尾張屋（zen047）
		case 'maps.very-foods.co.jp':
			if (!in_array($cid, array('zen047','zen047test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'45nfEeGQbcKyp0X5onTIrxHzTqrx0zTyrtiS4FWsxz01oBP3GHbcEyAfoMnaOsXM9PGBaN43EEasTnFMb6d2FwZMHzJt');
			break;
		// ユナイテッドベジーズ（zen039）
		case 'maps.uvc.jp':
			if (!in_array($cid, array('zen039','zen039test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'35nfIeGKbcXyp6X53nTRrxwzTArxezTBrtSS4MWsxz0IoBv3GxbcQyAToMFe6UbB69JSXxwLTv');
			break;
		// 輝（zen046）
		case 'maps.kaigo-kagayaki.jp':
			if (!in_array($cid, array('zen046','zen046test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain, 'apikey'=>'46nfSeGwbcHyphX5KnTNrxlzTirxLzT4rt4S4AWsmz0VoBF3Ghbc2yA9oNHGSgZdZWE8odWGSLa6Gu9jbdCGK3oNMKDVpR1zTp');
			break;
		// 2016/05/19 T.Yoshino add [
		// CooCa（zen099）
			case 'maps.coo-ca.jp':
			if (!in_array($cid, array('zen099','zen099test','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			if (isset($_SERVER['HTTPS'])) {
				return array('domain'=>$domain, 'apikey'=>'39nfieGIbcsypTX5qnTprxfzTprxlzTyrteS4SWs3yAvlRo2E1YdcuDoXBZ9QbY6n2GDb6GvF8ZM4zJB');		//add 2017/04/28 Y.Uesugi
			}else {
				return array('domain'=>$domain, 'apikey'=>'38nf8eGxbcMypcX5enTjrxyzTWrxazTprtIS4fWswz0GoBi3GFbcjyA6oNHmEBYBv5QYbh79JbXxsLTm');
			}
			break;
		// 2016/05/19 T.Yoshino add ]
		default:
			return null;
	}
}

// ドコモiD用ドメインかどうか判定		add 2015/11/13 Y.Matsukawa
// ※事前検証用に社内検証cid（dcmidDEV、9999999R）も許可しています。
function docomoidDomain($domain, $cid) {
	switch ($domain) {
		case 'idmap.id-credit.com':
			if (!in_array($cid, array('docomoid','docomoidtest','dcmidDEV','dcmidDEVtest','9999999R','9999999Rtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain);
			break;
		default:
			return null;
	}
}

// JTB用ドメインかどうか判定		add 2016/02/15 F.Yokoi [
function jtbDomain($domain, $cid) {
	switch ($domain) {
		case 'tabipricasp.jtb.co.jp':
			if (!in_array($cid, array('jtbtabip'))) return array('err'=>'NGCID');
			return array('domain'=>$domain);
			break;
		default:
			return null;
	}
}
// add 2016/02/15 F.Yokoi ]

// その他の専用ドメインかどうか判定		add 2016/06/20 Y.Matsukawa
function orgDomain($domain, $cid) {
	switch ($domain) {
		// 日本郵政
		case 'map.japanpost.jp':
			if (!in_array($cid, array('search','searchtest','search1','search1test','search2','search2test','searchD','searchDtest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain);
			break;
		// 2016/11/21 T.Yoshino [
		// 吉野家
		case 'map.yoshinoya.com':
			if (!in_array($cid, array('shopmap','shopmaptest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain);
			break;
		// 2016/11/21 T.Yoshino ]
		// 2016/12/20 Y.Uesugi [
		// ファイザー（すぐ禁煙）
		case 'map.sugu-kinen.jp':
			if (!in_array($cid, array('kinenmap','kinenmaptest'))) return array('err'=>'NGCID');
			return array('domain'=>$domain);
			break;
		// 2016/12/20 Y.Uesugi ]
		default:
			return null;
	}
}


$hostname = trim(`hostname`);

// mod 2011/07/05 Y.Nakajima [
if (!isset($https_req)) {
	if (isset($_SERVER['HTTPS'])) {
		$https_req = $_SERVER['HTTPS'];
	} else {
		$https_req = "";
	}
}
if (isset($https_req) && $https_req != "") {
// mod 2011/07/05 Y.Nakajima ]
	$protocol = 'https';
} else {
	$protocol = 'http';
}

// mod 2011/07/05 Y.Nakajima [
//defineを使用しないファイルからの読み込み時用にパラメータ取得処理を入れる
//SCRIPT_NAME
if (isset($_SERVER['SCRIPT_NAME']) && $_SERVER['SCRIPT_NAME'] != "") {
	$SCRIPT_NAME = $_SERVER['SCRIPT_NAME'];
}
if (isset($_GET['cid']) && $_GET['cid'] != "") {
	$cid = $_GET['cid'];
} else if (isset($_POST['cid']) && $_POST['cid'] != "") {
	$cid = $_POST['cid'];
} else {
	$cid = "";
}

// 企業 コード ---------------------------------------------
if(isset($cid)) $D_CID = $cid;
	else $D_CID = "00000000";

if (isset($_GET['d']) && $_GET['d'] != "") {
	$d = $_GET['d'];
} else if (isset($_POST['d']) && $_POST['d'] != "") {
	$d = $_POST['d'];
} else {
	$d = "";
}

if (isset($_SERVER['D_QRIMG_E']) && $_SERVER['D_QRIMG_E'] != "") {
	$D_QRIMG_E = $_SERVER['D_QRIMG_E'];
} else {
	$D_QRIMG_E = "";
}
if (isset($_SERVER['D_QRIMG_V']) && $_SERVER['D_QRIMG_V'] != "") {
	$D_QRIMG_V = $_SERVER['D_QRIMG_V'];
} else {
	$D_QRIMG_V = "";
}
if (isset($_SERVER['D_QRIMG_S']) && $_SERVER['D_QRIMG_S'] != "") {
	$D_QRIMG_S = $_SERVER['D_QRIMG_S'];
} else {
	$D_QRIMG_S = "";
}
// mod 2011/07/05 Y.Nakajima ]

// ※アクセス集中対応
//	$temp_gip_access = ($_SERVER['HTTP_HOST'] == "157.101.252.117" ? true : false);	del 2016/06/06 H.Osamoto

// ドメイン判定		add 2015/01/09 Y.Matsukawa
if (!isset($PARENT_HTTP_HOST)) $PARENT_HTTP_HOST = ${'_'.$_SERVER['REQUEST_METHOD']}['PARENT_HTTP_HOST'];
$D_HTTP_HOST = ($PARENT_HTTP_HOST ? $PARENT_HTTP_HOST : $_SERVER['HTTP_HOST']);
// ゼンショー用ドメイン判定		add 2015/01/09 Y.Matsukawa
$D_ZENSHO_DOMAIN = ZenshoDomain($D_HTTP_HOST, $D_CID);
if ($D_ZENSHO_DOMAIN) {
	// 不正アクセス時は404
	if (isset($D_ZENSHO_DOMAIN['err'])) {
		header("HTTP/1.0 404 Not Found");
		exit;
	}
}
// ドコモiD用ドメイン判定		add 2015/11/13 Y.Matsukawa
$D_DOCOMOID_DOMAIN = docomoidDomain($D_HTTP_HOST, $D_CID);
if ($D_DOCOMOID_DOMAIN) {
	// 不正アクセス時は404
	if (isset($D_DOCOMOID_DOMAIN['err'])) {
		header("HTTP/1.0 404 Not Found");
		exit;
	}
}
// JTB用ドメイン判定		add 2016/02/15 F.Yokoi [
$D_JTB_DOMAIN = jtbDomain($D_HTTP_HOST, $D_CID);
if ($D_JTB_DOMAIN) {
	// 不正アクセス時は404
	if (isset($D_JTB_DOMAIN['err'])) {
		header("HTTP/1.0 404 Not Found");
		exit;
	}
}
// add 2016/02/15 F.Yokoi ]
// その他の専用ドメイン判定		add 2016/06/20 Y.Matsukawa
$D_ORG_DOMAIN = orgDomain($D_HTTP_HOST, $D_CID);
if ($D_ORG_DOMAIN) {
	// 不正アクセス時は404
	if (isset($D_ORG_DOMAIN['err'])) {
		header("HTTP/1.0 404 Not Found");
		exit;
	}
}

//**********************************************************
//* 環境により設定内容を切替
//**********************************************************
switch( $hostname ){
//-----------------------------------------------------------------------------
//
// 開発
//
//-----------------------------------------------------------------------------
case "dev-storenaviweb01":
	$D_EMAP_ENV = "dev";
	$D_DOMAIN_G = '218.225.89.139';
	$D_DOMAIN_L = '127.0.0.1';
	// 携帯
	if(isset($D_MOBILE) && $D_MOBILE){
		$API_SSAPI_SRV  = "172.28.0.156";
		$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
	// スマートフォン
	} else if (isset($D_SMT) && $D_SMT) {
		$API_SSAPI_SRV  = "172.28.0.156";
		$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
	// PC
	} else {
		$API_SSAPI_SRV  = "172.28.0.156";
		$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
	}
	$API_SSAPI_JPOSTMAP_SRV = '172.29.0.17';		// add 2016/11/16 Y.Matsukawa
	$EMAP_SSAPI_SRV_G = "218.225.89.139";
	## SSAPI KEY & KYOTEN-CGI KEY
	// 携帯
	if(isset($D_MOBILE) && $D_MOBILE){
		// EmapSsM        10.47.50.79
		$D_SSAPI_KEY = "41nQ7P9HlgmvBonARvBFnAJf9ImgcPBDidZ5SaXu6mAjghFzTVrxKzTlrxkzTYngYzFvmwyXFNmgqzFumAsPTu";
	// スマートフォン
	} else if (isset($D_SMT) && $D_SMT) {
		// EmapSsS        10.47.50.79
		$D_SSAPI_KEY = "41nQhzBGnwsvBynAXvBlnAof9MmgYPBlidC5SaXurmA7fB6zTbrxmzTZrxDzTzngjzFtmwIXFnmgrzFhmAbPTo";
	// PC2（画面遷移版）
	} else if (isset($D_PC2) && $D_PC2) {
		// EmapSsQ        10.47.50.79
		$D_SSAPI_KEY = "41nQVzCKnQKvBjngSvBZnA3f92mggPBdid45S4XudmADfhEzT4rxNzT3rxXzTvngpzF2mwkXFomgpzFmmAaPTX";
	// PC
	} else {
		// EmapSsP        10.47.50.79
		$D_SSAPI_KEY = "41nQNP97lgOvBSnAvvBsnAif9Ymg6PBcidU5SCXuimAEfxNzTRrxyzTerxTzTUng9zFkmwNXF9mgfzF0mAePTs";
	}
	## JSAPI KEY
	if (isset($https_req) && $https_req) {
		// EmapJsP     https://218.225.89.139*
		$D_JSAPI_KEY = "39nfyeGibc2ypwX5zzTRrxszTBrxszTlrtwS4hWslyAPlRb2EanQ6v8soQ9rBUmht88Olhn8CgnA6PJT";    //dev-storenaviweb01
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		// EmapJsS        https://218.225.89.139*
		$D_JSAPI_SMT_KEY = "39nfReGnbcKypcX5RnTvrxIzTOrx9zTirtOS4AWsNyANlRN2ERnQmv8CoQ8rB1mh088AlhL8CjnAvPJu";   //dev-storenaviweb01
	} else {
		// EmapJsP     http://218.225.89.139*
		$D_JSAPI_KEY = "38nfieGwbcZypbX5azTmrxozTprxlzTcrtoS4CWsEz0KoBm2BxngVTFBnQwr5goQZT9joQgvAhlhMLTJ";    //dev-storenaviweb01
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		// EmapJsS        http://218.225.89.139*
		$D_JSAPI_SMT_KEY = "38nf6eG7bc2ypYX55nThrx7zTPrxSzT1rt0S43WsHz0NoBB2BfngTTF2nQBr52oQsT91oQ6vAZlhCLTS";    //dev-storenaviweb01
	}
	$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
	## Mobile URL
	$D_MOBILE_URL = "http://10.47.50.79/mobile/".$D_CID."/d.htm";
	// 携帯地図アプリ
	define("D_GET_CHIZU_APP_URL_CGI", "http://it.i.zenrin.co.jp/zi/menu/getChizuAppUrl?ua=");
	define("D_GET_CHIZU_APP_DL", "http://it.i.zenrin.co.jp/zi/member/mad?uid=NULLGWDOCOMO");
	$D_SMT_URL = "http://218.225.89.139/smt/".$D_CID."/";
	$D_SMT_URL_PRCL = $protocol."://218.225.89.139/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
	$D_PC2_URL = $protocol."://218.225.89.139/p/".$D_CID."/";
	// apiproxy
	$D_APIPROXY['HOST'] = '10.253.0.8';
	$D_APIPROXY['PORT'] = '3128';
	// ヤマト運輸CGI
	$D_YTC_API_URL['JGCD'] = "http://sneko2api.kuronekoyamato.co.jp/sneko2api/Api?SystemID=JGCD&ID=ZNRN&JC=@@KYOTEN_ID@@";
	//--------------------------------
	// CORE I/F
	//--------------------------------
	//$CORE_IF_SRV = '10.47.50.34';					// del 2016/11/14 Y.Uesugi
	$CORE_IF_SRV = 'apicore.ver.aws.zdc.local';		// add 2016/11/14 Y.Uesugi
	$CORE_IF_V3_SRV = 'test.core.its-mo.com';		// add add 2017/01/18 N.Wada

	break;

//-----------------------------------------------------------------------------
//
// 検証
//
//-----------------------------------------------------------------------------
case "storenaviweb-v01":
case "storenaviweb-v02":
	$D_DOMAIN_L = '127.0.0.1';
	// ----------------------------------------------------------
	// ドコモプレミアでスマートフォンからのアクセス
	// ----------------------------------------------------------
	if( ($D_CID == "premier" || $D_CID == "premiertest" || $D_CID == "premiertest_prev" || $D_CID == "dpoint" || $D_CID == "dpointtest" || $D_CID == "dpointtest_prev") // mod 2015/10/19 F.Yokoi
																&& (isset($D_SMT) && $D_SMT) ) {
		$D_EMAP_ENV = "test";
        if ($_SERVER['HTTP_HOST'] == "157.101.254.73") {
    		$D_DOMAIN_G = '157.101.254.73';
        } else {
    		$D_DOMAIN_G = 'test.dcm.e-map.ne.jp';
        }
		// スマートフォン
		$API_SSAPI_SRV  = "172.28.0.156";
        if ($_SERVER['HTTP_HOST'] == "157.101.254.73") {
    		$API_JSAPI_SRV  = "157.101.254.73/proapi";
    		$API_JSAPI_SRV_API_FOR_PATCH  = "157.101.254.73/proapi";
    		$API_JSAPI_SRV_MAP_FOR_PATCH  = "157.101.254.73/promap";
        } else {
    		$API_JSAPI_SRV  = "test.dcm.e-map.ne.jp/proapi";
    		$API_JSAPI_SRV_API_FOR_PATCH  = "test.dcm.e-map.ne.jp/proapi";
    		$API_JSAPI_SRV_MAP_FOR_PATCH  = "test.dcm.e-map.ne.jp/promap";
        }
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com"; // mod 2015/10/19 F.Yokoi
		$EMAP_SSAPI_SRV = "127.0.0.1";
        if ($_SERVER['HTTP_HOST'] == "157.101.254.73") {
		    $EMAP_SSAPI_SRV_G = "157.101.254.73";
        } else {
    		$EMAP_SSAPI_SRV_G = "test.dcm.e-map.ne.jp";
        }
		## SSAPI KEY & KYOTEN-CGI KEY
		// EmapSsS        172.29.0.*
		$D_SSAPI_KEY = "40nQcP9tlgAvBxnAZvBznAnf9imgkPBBidE5SKXuomACfBGzTjrxKzTNrxwzTzngTXBEoQtr9DoQyzFapRfzTA";
		## JSAPI KEY
		// EmapJsS        http://210.133.99.11*
        if ($_SERVER['HTTP_HOST'] == "157.101.254.73") {
		    $D_JSAPI_SMT_KEY = "37nfVeGCbccyp8X5hnTMrxWzT5rxAzTHrtwS4EWsgz0HoBF2BDng2zFWngfnAuoQhP9qoQTvCUpRWzTs";
		    $D_SMT_URL = "http://157.101.254.73/smt/".$D_CID."/";
		    $D_SMT_URL_PRCL = $protocol."://157.101.254.73/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		    $D_PC2_URL = $protocol."://157.101.254.73/p/".$D_CID."/";
        } else {
    		$D_JSAPI_SMT_KEY = "44nfNeGQbcuypSX5WnTnrxtzTOrxOzTKrtES4dWsZz0soBL34VacGm4BoNeiQYYhh9OxodP5S3Xx59FZahO9JsXxHLTe";
    		$D_SMT_URL = "http://test.dcm.e-map.ne.jp/smt/".$D_CID."/";
    		$D_SMT_URL_PRCL = $protocol."://test.dcm.e-map.ne.jp/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
    		$D_PC2_URL = $protocol."://test.dcm.e-map.ne.jp/p/".$D_CID."/";
        }
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
	// ----------------------------------------------------------
	// ゼンショー用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_ZENSHO_DOMAIN) {
		$D_EMAP_ENV = "test";
		$D_DOMAIN_G = $D_ZENSHO_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.156";
		$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_ZENSHO_DOMAIN['domain'];
		// スマートフォン
		if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.29.0.*
			$D_SSAPI_KEY = "40nQcP9tlgAvBxnAZvBznAnf9imgkPBBidE5SKXuomACfBGzTjrxKzTNrxwzTzngTXBEoQtr9DoQyzFapRfzTA";
		// PC2.0
		} else {
			// EmapSsQ        172.29.0.*
			$D_SSAPI_KEY = "40nQ6P99lgMvBGnAPvBqnAEf9cmgoPBKid55SJXu5mAFfhVzThrxmzTQrxPzTcngSXBjoQXr9xoQYzFGpRdzTq";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_KEY = $D_ZENSHO_DOMAIN['apikey'];
		// URL
		$D_MOBILE_URL = "http://".$D_ZENSHO_DOMAIN['domain']."/mobile/".$D_CID."/d.htm";
		$D_SMT_URL = "http://".$D_ZENSHO_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_ZENSHO_DOMAIN['domain']."/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		$D_PC2_URL = "http://".$D_ZENSHO_DOMAIN['domain']."/p/".$D_CID."/";
	// ----------------------------------------------------------
	// ドコモiD用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_DOCOMOID_DOMAIN) {
		$D_EMAP_ENV = "test";
		$D_DOMAIN_G = $D_DOCOMOID_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.156";
		$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_DOCOMOID_DOMAIN['domain'];
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			// EmapSsM        172.29.0.*
			$D_SSAPI_KEY = "40nQVP9blgkvBYnAHvBSnAuf9cmgGPBeida5SrXukmAdghYzT8rxSzTZrxEzTcnglXB2oQXr9boQuzFNpR3zTa";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.29.0.*
			$D_SSAPI_KEY = "40nQcP9tlgAvBxnAZvBznAnf9imgkPBBidE5SKXuomACfBGzTjrxKzTNrxwzTzngTXBEoQtr9DoQyzFapRfzTA";
		// PC2.0
		} else {
			// EmapSsQ        172.29.0.*
			$D_SSAPI_KEY = "40nQ6P99lgMvBGnAPvBqnAEf9cmgoPBKid55SJXu5mAFfhVzThrxmzTQrxPzTcngSXBjoQXr9xoQYzFGpRdzTq";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		// URL
		$D_MOBILE_URL = "http://".$D_DOCOMOID_DOMAIN['domain']."/mobile/".$D_CID."/d.htm";
		$D_SMT_URL = "http://".$D_DOCOMOID_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_DOCOMOID_DOMAIN['domain']."/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		$D_PC2_URL = "http://".$D_DOCOMOID_DOMAIN['domain']."/p/".$D_CID."/";
	// add 2016/06/20 Y.Matsukawa
	// ----------------------------------------------------------
	// その他の専用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_ORG_DOMAIN) {
		$D_EMAP_ENV = "test";
		$D_DOMAIN_G = $D_ORG_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.156";
		$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_ORG_DOMAIN['domain'];
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			// EmapSsM        172.29.0.*
			$D_SSAPI_KEY = "40nQVP9blgkvBYnAHvBSnAuf9cmgGPBeida5SrXukmAdghYzT8rxSzTZrxEzTcnglXB2oQXr9boQuzFNpR3zTa";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.29.0.*
			$D_SSAPI_KEY = "40nQcP9tlgAvBxnAZvBznAnf9imgkPBBidE5SKXuomACfBGzTjrxKzTNrxwzTzngTXBEoQtr9DoQyzFapRfzTA";
		// PC2.0
		} else {
			// EmapSsQ        172.29.0.*
			$D_SSAPI_KEY = "40nQ6P99lgMvBGnAPvBqnAEf9cmgoPBKid55SJXu5mAFfhVzThrxmzTQrxPzTcngSXBjoQXr9xoQYzFGpRdzTq";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		// URL
		$D_MOBILE_URL = "http://".$D_ORG_DOMAIN['domain']."/mobile/".$D_CID."/d.htm";
		$D_SMT_URL = "http://".$D_ORG_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_ORG_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_PC2_URL = "http://".$D_ORG_DOMAIN['domain']."/p/".$D_CID."/";
	// ----------------------------------------------------------
	// 通常時
	// ----------------------------------------------------------
	} else {
		$D_EMAP_ENV = "test";
		$D_DOMAIN_G = 'test.e-map.ne.jp';
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			$API_SSAPI_SRV  = "172.28.0.156";
			$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
			$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
			$EMAP_SSAPI_SRV = "127.0.0.1";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			$API_SSAPI_SRV  = "172.28.0.156";
			$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
			$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
			$EMAP_SSAPI_SRV = "127.0.0.1";
		// PC
		} else {
			$API_SSAPI_SRV  = "172.28.0.156";
			$API_JSAPI_SRV  = "test.api.e-map.ne.jp";
			$API_JSAPI_SRV_V2  = "test.api.its-mo.com";
			$EMAP_SSAPI_SRV = "127.0.0.1";
		}
		$EMAP_SSAPI_SRV_G = "test.e-map.ne.jp";
		## SSAPI KEY & KYOTEN-CGI KEY
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			// EmapSsM        172.29.0.* mod 2016/04/13
			$D_SSAPI_KEY = "40nQVP9blgkvBYnAHvBSnAuf9cmgGPBeida5SrXukmAdghYzT8rxSzTZrxEzTcnglXB2oQXr9boQuzFNpR3zTa";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.29.0.* mod 2016/04/13
			$D_SSAPI_KEY = "40nQcP9tlgAvBxnAZvBznAnf9imgkPBBidE5SKXuomACfBGzTjrxKzTNrxwzTzngTXBEoQtr9DoQyzFapRfzTA";
		// PC2（画面遷移版）
		} else if (isset($D_PC2) && $D_PC2) {
			// EmapSsQ        172.29.0.* mod 2016/04/13
			$D_SSAPI_KEY = "40nQ6P99lgMvBGnAPvBqnAEf9cmgoPBKid55SJXu5mAFfhVzThrxmzTQrxPzTcngSXBjoQXr9xoQYzFGpRdzTq";
		// PC
		} else {
			// EmapSsP        172.29.0.* mod 2016/04/13
			$D_SSAPI_KEY = "40nQdP9vlg3vBQnASvB7nAhf96mg3PBWidP5SgXuMmAdfxNzT9rxvzT5rxIzTOngsXBnoQZr9coQVzFupRszTy";
		}
		## JSAPI KEY
		if (isset($https_req) && $https_req) {
			// EmapJsP        https://test.e-map.ne.jp*
			$D_JSAPI_KEY = "41nfHeG7bcDypiX5GzT2rx5zTirxdzTFrthS4tWsFyAPlRh2EkWtFeAxWxA9OuodX5SlXx29FDahj9JYXxkLTC";
			$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
			// EmapJsS        https://test.e-map.ne.jp*
			$D_JSAPI_SMT_KEY = "41nfqeGybctyptX5YnTOrxpzTfrxkzTlrtpS41WsJyAilRZ2EoWtLeAfWxw9OTodF5ScXxR9FDahA9JFXxdLTm";
		} else {
			// EmapJsP        http://test.e-map.ne.jp*
			$D_JSAPI_KEY = "40nfDeGJbcIyp6X5qzT3rxJzTgrxBzTXrtuS4LWscz0ooBN34nacOm4voNdfGoYdvuDJoNX9OroNvKDxpRfzTi";
			$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
			// EmapJsS        http://test.e-map.ne.jp*
			$D_JSAPI_SMT_KEY = "40nfxeGNbcFypHX5HnTPrxNzTmrxpzTIrtuS4RWs6z00oBg34macFm4OoNKfGkYdSuDJoNk9O5oNOKDnpREzTe";    // mod 2011/07/05 Y.Nakajima
		}
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		## Mobile URL
		$D_MOBILE_URL = "http://test.e-map.ne.jp/mobile/".$D_CID."/d.htm";
		//携帯地図アプリ
		define("D_GET_CHIZU_APP_URL_CGI", "http://it.i.zenrin.co.jp/zi/menu/getChizuAppUrl?ua=");
		define("D_GET_CHIZU_APP_DL", "http://it.i.zenrin.co.jp/zi/member/mad?uid=NULLGWDOCOMO");
		$D_SMT_URL = "http://test.e-map.ne.jp/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://test.e-map.ne.jp/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		$D_PC2_URL = $protocol."://test.e-map.ne.jp/p/".$D_CID."/";
	}
	$API_SSAPI_JPOSTMAP_SRV = $API_SSAPI_SRV;		// add 2016/11/16 Y.Matsukawa
	// apiproxy		add 2013/07/10 Y.Matsukawa
	$D_APIPROXY['HOST'] = '172.28.0.3';
	$D_APIPROXY['PORT'] = '3128';
	// ヤマト運輸CGI		add 2013/07/10 Y.Matsukawa
	$D_YTC_API_URL['JGCD'] = "http://sneko2api.kuronekoyamato.co.jp/sneko2api/Api?SystemID=JGCD&ID=ZNRN&JC=@@KYOTEN_ID@@";
	//--------------------------------
	// CORE I/F
	//--------------------------------
	$CORE_IF_SRV = 'apicore.stg.aws.zdc.local';
	$CORE_IF_V3_SRV = 'test.core.its-mo.com';		// add add 2017/01/18 N.Wada

	break;
	
//-----------------------------------------------------------------------------
//
// 本番
//
//-----------------------------------------------------------------------------
default:
	$D_DOMAIN_L = '127.0.0.1';
	// ----------------------------------------------------------
	// ドコモプレミアでスマートフォンからのアクセス
	// ----------------------------------------------------------
	if( ($D_CID == "premier" || $D_CID == "premiertest" || $D_CID == "premiertest_prev" || $D_CID == "dpoint" || $D_CID == "dpointtest" || $D_CID == "dpointtest_prev") 
																&& (isset($D_SMT) && $D_SMT) ) {
		$D_EMAP_ENV = "www";
        if ($_SERVER['HTTP_HOST'] == "157.101.252.119") {
    		$D_DOMAIN_G = '157.101.252.119';
        } else {
    		$D_DOMAIN_G = 'dcm.e-map.ne.jp';
        }
		// スマートフォン
		$API_SSAPI_SRV  = "172.28.0.56";
        if ($_SERVER['HTTP_HOST'] == "157.101.252.119") {
    		$API_JSAPI_SRV  = "157.101.252.119/proapi";
    		$API_JSAPI_SRV_API_FOR_PATCH  = "157.101.252.119/proapi";
    		$API_JSAPI_SRV_MAP_FOR_PATCH  = "157.101.252.119/promap";
        } else {
    		$API_JSAPI_SRV  = "dcm.e-map.ne.jp/proapi";
    		$API_JSAPI_SRV_API_FOR_PATCH  = "dcm.e-map.ne.jp/proapi";
    		$API_JSAPI_SRV_MAP_FOR_PATCH  = "dcm.e-map.ne.jp/promap";
        }
		$API_JSAPI_SRV_V2  = "api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
        if ($_SERVER['HTTP_HOST'] == "157.101.252.119") {
		    $EMAP_SSAPI_SRV_G = "157.101.252.119";
        } else {
    		$EMAP_SSAPI_SRV_G = "dcm.e-map.ne.jp";
        }
		## SSAPI KEY & KYOTEN-CGI KEY
		// EmapSsS        172.28.0.*
		$D_SSAPI_KEY = "40nQoP9xlgJvBTnAevBenA2f9hmgMPBYidI5S1XuJmAOfBKzTrrx0zT4rxbzTrngmXBsoQer8SoQJzF4pRBzTc";
		## JSAPI KEY
		// EmapJsS        http://210.133.99.11*
        if ($_SERVER['HTTP_HOST'] == "157.101.252.119") {
    		$D_JSAPI_SMT_KEY = "37nfVeGCbccyp8X5hnTMrxWzT5rxAzTHrtwS4EWsgz0HoBF2BDng2zFWngfnAuoQhP9qoQTvCUpRWzTs";
    		$D_SMT_URL = "http://157.101.252.119/smt/".$D_CID."/";
    		$D_SMT_URL_PRCL = $protocol."://157.101.252.119/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
    		$D_PC2_URL = $protocol."://157.101.252.119/p/".$D_CID."/";
        } else {
		    $D_JSAPI_SMT_KEY = "39nfQeG7bcTypJX5XnTUrxozT7rxWzTerteS4pWsbz0UoBl3PEb6H4FBahu5GkbcczF8YNHfFzZMpzJx";
		    $D_SMT_URL = "http://dcm.e-map.ne.jp/smt/".$D_CID."/";
		    $D_SMT_URL_PRCL = $protocol."://dcm.e-map.ne.jp/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		    $D_PC2_URL = $protocol."://dcm.e-map.ne.jp/p/".$D_CID."/";
        }
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
	// ----------------------------------------------------------
	// ゼンショー用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_ZENSHO_DOMAIN) {
		$D_EMAP_ENV = "www";
		$D_DOMAIN_G = $D_ZENSHO_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.56";
		$API_JSAPI_SRV  = "api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_ZENSHO_DOMAIN['domain'];
		// スマートフォン
		if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.28.0.*
			$D_SSAPI_KEY = "40nQoP9xlgJvBTnAevBenA2f9hmgMPBYidI5S1XuJmAOfBKzTrrx0zT4rxbzTrngmXBsoQer8SoQJzF4pRBzTc";
		// PC2.0
		} else {
			// EmapSsQ        172.28.0.*
			$D_SSAPI_KEY = "40nQHP9HlgMvBBnAWvB9nA6f9xmgLPBjidg5SFXudmAvfhJzTarxCzTKrxIzTsngEXBLoQJr8AoQQzFbpR1zTs";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_KEY = $D_ZENSHO_DOMAIN['apikey'];
		// URL
		$D_MOBILE_URL = "http://".$D_ZENSHO_DOMAIN['domain']."/mobile/".$D_CID."/d.htm";
		$D_SMT_URL = "http://".$D_ZENSHO_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_ZENSHO_DOMAIN['domain']."/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		$D_PC2_URL = "http://".$D_ZENSHO_DOMAIN['domain']."/p/".$D_CID."/";
	// ----------------------------------------------------------
	// ドコモiD用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_DOCOMOID_DOMAIN) {
		$D_EMAP_ENV = "www";
		$D_DOMAIN_G = $D_DOCOMOID_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.56";
		$API_JSAPI_SRV  = "api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_DOCOMOID_DOMAIN['domain'];
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			// EmapSsM        172.28.0.*
			$D_SSAPI_KEY = "40nQnP95lgCvBcnA0vB2nAVf96mg5PBcidQ5SPXufmAAghwzT5rxxzTgrx3zT6ng8XB9oQxr88oQtzFCpRDzTc";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.28.0.*
			$D_SSAPI_KEY = "40nQoP9xlgJvBTnAevBenA2f9hmgMPBYidI5S1XuJmAOfBKzTrrx0zT4rxbzTrngmXBsoQer8SoQJzF4pRBzTc";
		// PC2.0
		} else {
			// EmapSsQ        172.28.0.*
			$D_SSAPI_KEY = "40nQHP9HlgMvBBnAWvB9nA6f9xmgLPBjidg5SFXudmAvfhJzTarxCzTKrxIzTsngEXBLoQJr8AoQQzFbpR1zTs";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		// URL
		$D_MOBILE_URL = "http://".$D_DOCOMOID_DOMAIN['domain']."/mobile/".$D_CID."/d.htm";
		$D_SMT_URL = "http://".$D_DOCOMOID_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_DOCOMOID_DOMAIN['domain']."/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		$D_PC2_URL = "http://".$D_DOCOMOID_DOMAIN['domain']."/p/".$D_CID."/";
	// ----------------------------------------------------------
	// JTB用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_JTB_DOMAIN) {
		$D_EMAP_ENV = "www";
		$D_DOMAIN_G = $D_JTB_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.56";
		$API_JSAPI_SRV  = "api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_JTB_DOMAIN['domain'];
		// スマートフォン
		if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.28.0.*
			$D_SSAPI_KEY = "40nQoP9xlgJvBTnAevBenA2f9hmgMPBYidI5S1XuJmAOfBKzTrrx0zT4rxbzTrngmXBsoQer8SoQJzF4pRBzTc";
		// PC2.0
		} else {
			// EmapSsQ        172.28.0.*
			$D_SSAPI_KEY = "40nQHP9HlgMvBBnAWvB9nA6f9xmgLPBjidg5SFXudmAvfhJzTarxCzTKrxIzTsngEXBLoQJr8AoQQzFbpR1zTs";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		// URL
		$D_SMT_URL = "http://".$D_JTB_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_JTB_DOMAIN['domain']."/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
		$D_PC2_URL = "http://".$D_JTB_DOMAIN['domain']."/p/".$D_CID."/";
	// add 2016/06/20 Y.Matsukawa
	// ----------------------------------------------------------
	// その他の専用ドメインの場合
	// ----------------------------------------------------------
	} else if ($D_ORG_DOMAIN) {
		$D_EMAP_ENV = "www";
		$D_DOMAIN_G = $D_ORG_DOMAIN['domain'];
		$API_SSAPI_SRV  = "172.28.0.56";
		$API_JSAPI_SRV  = "api.e-map.ne.jp";
		$API_JSAPI_SRV_V2  = "api.its-mo.com";
		$EMAP_SSAPI_SRV = "127.0.0.1";
		$EMAP_SSAPI_SRV_G = $D_ORG_DOMAIN['domain'];
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			// EmapSsM        172.28.0.*
			$D_SSAPI_KEY = "40nQnP95lgCvBcnA0vB2nAVf96mg5PBcidQ5SPXufmAAghwzT5rxxzTgrx3zT6ng8XB9oQxr88oQtzFCpRDzTc";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			// EmapSsS        172.28.0.*
			$D_SSAPI_KEY = "40nQoP9xlgJvBTnAevBenA2f9hmgMPBYidI5S1XuJmAOfBKzTrrx0zT4rxbzTrngmXBsoQer8SoQJzF4pRBzTc";
		// PC2.0
		} else {
			// EmapSsQ        172.28.0.*
			$D_SSAPI_KEY = "40nQHP9HlgMvBBnAWvB9nA6f9xmgLPBjidg5SFXudmAvfhJzTarxCzTKrxIzTsngEXBLoQJr8AoQQzFbpR1zTs";
		}
		$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		// URL
		$D_MOBILE_URL = "http://".$D_ORG_DOMAIN['domain']."/mobile/".$D_CID."/d.htm";
		$D_SMT_URL = "http://".$D_ORG_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_SMT_URL_PRCL = $protocol."://".$D_ORG_DOMAIN['domain']."/smt/".$D_CID."/";
		$D_PC2_URL = "http://".$D_ORG_DOMAIN['domain']."/p/".$D_CID."/";
	// ----------------------------------------------------------
	// 通常時
	// ----------------------------------------------------------
	} else {
		$D_EMAP_ENV = "www";
		// デイリーヤマザキ専用ドメインへのアクセス判定
		$dyemap_access = false;
		$dyemap_domain = 'yamazaki.e-map.ne.jp';
		if ($_SERVER['HTTP_HOST'] == $dyemap_domain) {
			$dyemap_access = true;
		} else if (isset($D_CID) && $D_CID == 'dyemap' && isset($_REQUEST['p_f9']) && $_REQUEST['p_f9']) {
			$dyemap_access = true;
		}
		if ($_SERVER['HTTP_HOST'] == "matsukiyo.e-map.ne.jp") {
			$D_DOMAIN_G = 'matsukiyo.e-map.ne.jp';
		} else if ($D_HTTP_HOST == "map.sjnk.jp") {
			$D_DOMAIN_G = 'map.sjnk.jp';
		} else if ($dyemap_access) {	// デイリーヤマザキ
			$D_DOMAIN_G = $dyemap_domain;
		} else {
			$D_DOMAIN_G = 'www.e-map.ne.jp';
		}
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			$API_SSAPI_SRV  = "172.28.0.56";
			$API_JSAPI_SRV  = "api.e-map.ne.jp";
			$API_JSAPI_SRV_V2  = "api.its-mo.com";
			$EMAP_SSAPI_SRV = "127.0.0.1";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			$API_SSAPI_SRV  = "172.28.0.56";
			$API_JSAPI_SRV  = "api.e-map.ne.jp";
			$API_JSAPI_SRV_V2  = "api.its-mo.com";
			$EMAP_SSAPI_SRV = "127.0.0.1";
		// PC
		} else {
			$API_SSAPI_SRV  = "172.28.0.56";
			$API_JSAPI_SRV  = "api.e-map.ne.jp";
			$API_JSAPI_SRV_V2  = "api.its-mo.com";
			$EMAP_SSAPI_SRV = "127.0.0.1";
		}
		//	if ($temp_gip_access) $EMAP_SSAPI_SRV = "157.101.252.117";	del 2016/06/06 H.Osamoto
		$EMAP_SSAPI_SRV_G = "www.e-map.ne.jp";
		if ($dyemap_access) {	// デイリーヤマザキ
			$EMAP_SSAPI_SRV_G = $dyemap_domain;
		}
		## SSAPI KEY & KYOTEN-CGI KEY
		// 携帯
		if(isset($D_MOBILE) && $D_MOBILE){
			// EmapSsM        172.28.0.*  mod 2016/04/13
			$D_SSAPI_KEY = "40nQnP95lgCvBcnA0vB2nAVf96mg5PBcidQ5SPXufmAAghwzT5rxxzTgrx3zT6ng8XB9oQxr88oQtzFCpRDzTc";
		// スマートフォン
		} else if (isset($D_SMT) && $D_SMT) {
			// EmapSsS       172.28.0.*  mod 2016/04/13
			$D_SSAPI_KEY = "40nQoP9xlgJvBTnAevBenA2f9hmgMPBYidI5S1XuJmAOfBKzTrrx0zT4rxbzTrngmXBsoQer8SoQJzF4pRBzTc";
		// PC2（画面遷移版）
		} else if (isset($D_PC2) && $D_PC2) {
			// EmapSsQ        172.28.0.*  mod 2016/04/13
			$D_SSAPI_KEY = "40nQHP9HlgMvBBnAWvB9nA6f9xmgLPBjidg5SFXudmAvfhJzTarxCzTKrxIzTsngEXBLoQJr8AoQQzFbpR1zTs";
		// PC
		} else {
			// EmapSsP        172.28.0.*  mod 2016/04/13
			$D_SSAPI_KEY = "40nQYP9mlgMvBXnA8vBtnAWf9bmgPPBTidC5SOXunmABfxxzTfrxEzTQrxgzTAngvXBloQ4r8eoQYzFJpRZzT9";
		}
		## JSAPI KEY
		if (isset($https_req) && $https_req) {
			if ($_SERVER['HTTP_HOST'] == "matsukiyo.e-map.ne.jp") {
				// マツキヨ用サブドメイン
				// EmapJsP        https://matsukiyo.e-map.ne.jp*
				$D_JSAPI_KEY = "46nfSeGhbcgypgX5HzTrrxgzThrxmzTgrtGS4WWsMyAglRy2EpYdLu4eX7yeI3ZcTOE9oNyfGdYdFuDyoNC9OmoN5KDopRVzTX";
				//	if ($temp_gip_access) $D_JSAPI_KEY = "40nfHeGEbchypJX5KzTqrxlzTarxOzTErtDS4SWstyAIlRO2EWnQvvDJoQJvA6nBo8CPnwbPFNngVj9tpRgzT5";	del 2016/06/06 H.Osamoto
				$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
				// EmapJsS        https://matsukiyo.e-map.ne.jp*
				$D_JSAPI_SMT_KEY = "46nfneG5bctypTX5LnT4rxizT7rx6zTHrt8S49WsnyAPlR32E5YdTu4KX7neIyZc7OEIoNZfGgYdXuDsoNB9OBoNbKDppRtzTP";
			} else if ($_SERVER['HTTP_HOST'] == "map.sjnk.jp") {
				// 損保ジャパン用ドメイン
				// EmapJsP        https://map.sjnk.jp*
				$D_JSAPI_KEY = "36nfoeG6bcJypHX53zTMrxMzTarxqzTmrtlS4bWsAyAilRj2E0YdRuDToM5mJ7YN0HFQZMAzJG";
				//	if ($temp_gip_access) $D_JSAPI_KEY = "40nfHeGEbchypJX5KzTqrxlzTarxOzTErtDS4SWstyAIlRO2EWnQvvDJoQJvA6nBo8CPnwbPFNngVj9tpRgzT5";	del 2016/06/06 H.Osamoto
				$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
				// EmapJsS        https://map.sjnk.jp*
				$D_JSAPI_SMT_KEY = "36nfEeGMbcGyp6X5MnTgrxFzTdrxnzTTrtQS4TWshyAIlRj2EaYdxuDaoM5mJHYNjHFYZMkzJE";
			} else {
				// EmapJsP        https://www.e-map.ne.jp*
				$D_JSAPI_KEY = "40nf5eGcbcFypGX5KzTWrxgzTfrxOzTdrt5S4rWsRyAGlRb2E0W7lW7HoNafGcYdDuDJoNS9OnoN7KDSpRgzTI";
				//	if ($temp_gip_access) $D_JSAPI_KEY = "40nfHeGEbchypJX5KzTqrxlzTarxOzTErtDS4SWstyAIlRO2EWnQvvDJoQJvA6nBo8CPnwbPFNngVj9tpRgzT5";	del 2016/06/06 H.Osamoto
				$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
				// EmapJsS        https://www.e-map.ne.jp*
				$D_JSAPI_SMT_KEY = "40nfYeGdbcQypPX5DnTerxPzTYrxhzTHrt1S41Ws2yA4lRN2EbW7WW7toNFfGBYdduD7oN69OroNwKDjpRMzTa";
			}
			if ($PC_HTTP_HOST_ORG == "map.sjnk.jp") {	// 損保ジャパン PC1.0用
				$D_JSAPI_KEY = "36nfoeG6bcJypHX53zTMrxMzTarxqzTmrtlS4bWsAyAilRj2E0YdRuDToM5mJ7YN0HFQZMAzJG";
			}
		} else {
			if ($_SERVER['HTTP_HOST'] == "matsukiyo.e-map.ne.jp") {
				// マツキヨ用サブドメイン
				// EmapJsP        http://matsukiyo.e-map.ne.jp*
				$D_JSAPI_KEY = "45nfpeGTbcXyp6X5nzTOrxyzT4rxMzTfrt6S4NWsRz0LoBy3GDbcGiAtWduGKTVdW2FlahL5G7bcNzFFYNAfFNZM0zJy";
				//	if ($temp_gip_access) $D_JSAPI_KEY = "40nfHeGEbchypJX5KzTqrxlzTarxOzTErtDS4SWstyAIlRO2EWnQvvDJoQJvA6nBo8CPnwbPFNngVj9tpRgzT5";	del 2016/06/06 H.Osamoto
				$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
				// EmapJsS        http://matsukiyo.e-map.ne.jp*
				$D_JSAPI_SMT_KEY = "45nfgeG3bcRyp9X5bnTrrxozTfrxozTLrtES4zWsjz0WoB53GabcNiAUWd5GK2VdN2Flahv5Gkbc2zFTYN0fFvZMozJS";
			} else if ($_SERVER['HTTP_HOST'] == "map.sjnk.jp") {
				// 損保ジャパン用ドメイン
				// EmapJsP        http://map.sjnk.jp*
				$D_JSAPI_KEY = "35nfpeGhbcOyp8X5MzTxrxgzTIrxPzTjrtDS4KWsTz0QoB33GGbcKzF1X6wKFrZB79JJXxlLTT";
				//	if ($temp_gip_access) $D_JSAPI_KEY = "40nfHeGEbchypJX5KzTqrxlzTarxOzTErtDS4SWstyAIlRO2EWnQvvDJoQJvA6nBo8CPnwbPFNngVj9tpRgzT5";	del 2016/06/06 H.Osamoto
				$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
				// EmapJsS        http://map.sjnk.jp*
				$D_JSAPI_SMT_KEY = "35nfOeGEbcDypsX5vnT0rxMzTXrxyzTertoS4lWsqz0VoBn3G9bcOzFzX6ZKF5ZBX9JDXxYLTP";
			} else {
				// EmapJsP        http://www.e-map.ne.jp*
				$D_JSAPI_KEY = "39nfneGfbcPyp9X5bzTsrxUzTvrxRzTvrtKS46WsFz0joBS37xW7gXFVahs5GqbcIzFmYNffFUZM9zJp";
				//	if ($temp_gip_access) $D_JSAPI_KEY = "39nfJeGnbcAypsX5FzT6rxFzTZrxjzT1rtgS4zWs1z0koBm2B1nghzFengdnAtoQQvDSlh08CHmwqPJR";		// add 2009/11/26 Y.Matsukawa	del 2016/06/06 H.Osamoto
				$D_JSAPI_V2_KEY = "JSZ989f008c73d4";
				// EmapJsS        http://www.e-map.ne.jp*
				$D_JSAPI_SMT_KEY = "39nfYeGpbcFypnX5HnTcrxKzTFrxezT1rtnS4rWsKz0AoBF37yW7rXF9ahh5GfbcUzFJYNvfFfZM8zJq";
			}
			if ($dyemap_access) {	// デイリーヤマザキ
				$D_JSAPI_KEY = '44nfEeGzbcUypFX5lzTFrxYzTlrxhzTbrthS4PWsez0voB839XbdB5S9VNXuIzZhE9O0odW5SUXxq9F4ahh9J9XxSLT2';
			}
			if ($PC_HTTP_HOST_ORG == "map.sjnk.jp") {	// 損保ジャパン PC1.0用
				$D_JSAPI_KEY = "35nfpeGhbcOyp8X5MzTxrxgzTIrxPzTjrtDS4KWsTz0QoB33GGbcKzF1X6wKFrZB79JJXxlLTT";
			}
		}
		$D_JSAPI_SMT_V2_KEY = "JSZ7efdfea9bb8d";
		//携帯地図アプリ
		define("D_GET_CHIZU_APP_URL_CGI", "http://i.i.zenrin.co.jp/zi/menu/getChizuAppUrl?ua=");
		define("D_GET_CHIZU_APP_DL", "http://i.i.zenrin.co.jp/zi/member/mad?uid=NULLGWDOCOMO");
		if ($_SERVER['HTTP_HOST'] == "matsukiyo.e-map.ne.jp") {
			// マツキヨ用サブドメイン
			## Mobile URL
			$D_MOBILE_URL = "http://matsukiyo.e-map.ne.jp/mobile/".$D_CID."/d.htm";
			$D_SMT_URL = "http://matsukiyo.e-map.ne.jp/smt/".$D_CID."/";
			$D_SMT_URL_PRCL = $protocol."://matsukiyo.e-map.ne.jp/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
			$D_PC2_URL = $protocol."://matsukiyo.e-map.ne.jp/p/".$D_CID."/";
		} else if ($_SERVER['HTTP_HOST'] == "map.sjnk.jp") {
			// 損保ジャパン用ドメイン
			## Mobile URL
			$D_MOBILE_URL = "http://map.sjnk.jp/mobile/".$D_CID."/d.htm";
			$D_SMT_URL = "http://map.sjnk.jp/smt/".$D_CID."/";
			$D_SMT_URL_PRCL = $protocol."://map.sjnk.jp/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
			$D_PC2_URL = $protocol."://map.sjnk.jp/p/".$D_CID."/";
		} else {
			## Mobile URL
			$D_MOBILE_URL = "http://www.e-map.ne.jp/mobile/".$D_CID."/d.htm";
			$D_SMT_URL = "http://www.e-map.ne.jp/smt/".$D_CID."/";
			$D_SMT_URL_PRCL = $protocol."://www.e-map.ne.jp/smt/".$D_CID."/";	// add 2016/05/06 N.Wada
			$D_PC2_URL = $protocol."://www.e-map.ne.jp/p/".$D_CID."/";		// add 2012/07/25 H.osamoto
		}
	}
	$API_SSAPI_JPOSTMAP_SRV = $API_SSAPI_SRV;		// add 2016/11/16 Y.Matsukawa
	// apiproxy
	$D_APIPROXY['HOST'] = '172.28.0.3';
	$D_APIPROXY['PORT'] = '3128';
	// ヤマト運輸CGI
	$D_YTC_API_URL['JGCD'] = "http://sneko2api.kuronekoyamato.co.jp/sneko2api/Api?SystemID=JGCD&ID=ZNRN&JC=@@KYOTEN_ID@@";
	//--------------------------------
	// CORE I/F
	//--------------------------------
	$CORE_IF_SRV = 'apicore.pro.aws.zdc.local';
	$CORE_IF_V3_SRV = 'core.its-mo.com';

	break;
}

// SSAPI ---------------------------------------------------
$D_SSAPI["icon_select"]     = "http://".$EMAP_SSAPI_SRV."/cgi/icon_select.cgi";
$D_SSAPI["icon_select_g"]   = "$protocol://".$EMAP_SSAPI_SRV_G."/cgi/icon_select.cgi";
$D_SSAPI["sys_icon_select"] = "$protocol://".$EMAP_SSAPI_SRV_G."/cgi/sys_icon_select.cgi";
$D_SSAPI["sys_icon_select_ssl"] = "https://".$EMAP_SSAPI_SRV_G."/cgi/sys_icon_select.cgi";	//add 2016/07/27 Y.Uesugi
$D_SSAPI["gif_select_l"]    = "http://".$EMAP_SSAPI_SRV_G."/cgi/gif_select.cgi";
$D_SSAPI["gif_select"]      = "$protocol://".$EMAP_SSAPI_SRV_G."/cgi/gif_select.cgi";
$D_SSAPI["img_select_l"]    = "http://".$EMAP_SSAPI_SRV_G."/cgi/img_select.cgi";
$D_SSAPI["img_select"]      = "$protocol://".$EMAP_SSAPI_SRV_G."/cgi/img_select.cgi";
$D_SSAPI["cp_img"]        = "http://".$EMAP_SSAPI_SRV.       "/cgi/cp_img.cgi";
$D_SSAPI["cp_img_g"]      = "$protocol://".$EMAP_SSAPI_SRV_G."/cgi/cp_img.cgi";
$D_SSAPI["cp_img_inf"]    = "http://".$EMAP_SSAPI_SRV.       "/cgi/cp_img_inf.cgi";
$D_SSAPI["nkyoten"]       = "http://".$EMAP_SSAPI_SRV."/cgi/nkyoten.cgi";
$D_SSAPI["kyotenlist"]    = "http://".$EMAP_SSAPI_SRV."/cgi/kyotenlist.cgi";
$D_SSAPI["kyotenid"]      = "http://".$EMAP_SSAPI_SRV."/cgi/kyotenid.cgi";
$D_SSAPI["kyotenid_nolog"]= "http://".$EMAP_SSAPI_SRV."/cgi/kyotenid_nolog.cgi";
$D_SSAPI["kyotenarea"]    = "http://".$EMAP_SSAPI_SRV."/cgi/kyotenarea.cgi";
$D_SSAPI["icon_select"]   = "http://".$EMAP_SSAPI_SRV."/cgi/icon_select.cgi";
$D_SSAPI["getsdate"]      = "http://".$EMAP_SSAPI_SRV."/cgi/getsdate.cgi";
$D_SSAPI["get_icon_info"] = "http://".$EMAP_SSAPI_SRV."/cgi/get_icon_info.cgi";
$D_SSAPI["get_corp_pw"]   = "http://".$EMAP_SSAPI_SRV."/cgi/get_corp_pw.cgi";
$D_SSAPI["get_basic_pw"]  = "http://".$EMAP_SSAPI_SRV."/cgi/get_basic_pw.cgi";
$D_SSAPI["myarea_select"] = "http://".$EMAP_SSAPI_SRV."/cgi/myarea_select.cgi";
$D_SSAPI["myarea_add"]    = "http://".$EMAP_SSAPI_SRV."/cgi/myarea_add.cgi";
$D_SSAPI["myarea_name_updt"] = "http://".$EMAP_SSAPI_SRV."/cgi/myarea_name_updt.cgi";
$D_SSAPI["myarea_order_updt"]= "http://".$EMAP_SSAPI_SRV."/cgi/myarea_order_updt.cgi";
$D_SSAPI["myarea_del"]    = "http://".$EMAP_SSAPI_SRV."/cgi/myarea_del.cgi";
$D_SSAPI["event_log"]     = "http://".$EMAP_SSAPI_SRV."/cgi2/event_log.cgi";
$D_SSAPI["gps_log"]     = "http://".$EMAP_SSAPI_SRV."/cgi2/gps_log.cgi";
$D_SSAPI["rd_store_id"]   = "http://".$EMAP_SSAPI_SRV."/cgi/rd_store_id.cgi";
$D_SSAPI["prd_select"]    = "http://".$EMAP_SSAPI_SRV."/cgi/prd_select.cgi";
$D_SSAPI["prd_select_jan"]    = "http://".$EMAP_SSAPI_SRV."/cgi/prd_select_jan.cgi";
$D_SSAPI["prd_select_pnm"]    = "http://".$EMAP_SSAPI_SRV."/cgi/prd_select_pnm.cgi";
$D_SSAPI["nsnet01_syainnm"] = "http://".$EMAP_SSAPI_SRV."/cgi/nsnet01_syainnm.cgi";
$D_SSAPI["ytc_get_holiday"] = "http://".$EMAP_SSAPI_SRV."/cgi/ytc_get_holiday.cgi";
$D_SSAPI["get_holiday"] = "http://".$EMAP_SSAPI_SRV."/cgi/get_holiday.cgi";		// add 2016/11/08 Y.Matsukawa

// API基盤SSAPI
$D_SSAPI["selectadcd"]    = "http://".$API_SSAPI_SRV."/ssapi/selectadcd.cgi";
$D_SSAPI["selectaddr"]    = "http://".$API_SSAPI_SRV."/ssapi/selectaddr.cgi";
$D_SSAPI["mselectaddr"]   = "http://".$API_SSAPI_SRV."/ssapi/mselectaddr.cgi";
$D_SSAPI["selectaddr_kyoto"] = "http://".$API_SSAPI_SRV."/ssapi/selectaddr_kyoto.cgi";	// add 2017/03/21 Y.Uesugi
$D_SSAPI["searchaddr"]    = "http://".$API_SSAPI_SRV."/ssapi/searchaddr.cgi";
$D_SSAPI["ml_searchaddr"] = "http://".$API_SSAPI_SRV."/ssapi/ml_searchaddr.cgi";	// add 2016/03/10 Y.Matsukawa
$D_SSAPI["searcheki"]     = "http://".$API_SSAPI_SRV."/ssapi/searcheki.cgi";
$D_SSAPI["searchekikana"] = "http://".$API_SSAPI_SRV."/ssapi/searchekikana.cgi";
$D_SSAPI["searchline"]    = "http://".$API_SSAPI_SRV."/ssapi/searchline.cgi";
$D_SSAPI["searchpoi"]     = "http://".$API_SSAPI_SRV."/ssapi/searchpoi.cgi";
$D_SSAPI["searchpoijnr"]  = "http://".$API_SSAPI_SRV."/ssapi/searchpoijnr.cgi";
$D_SSAPI["searchpoiarea"] = "http://".$API_SSAPI_SRV."/ssapi/searchpoiarea.cgi";
$D_SSAPI["searchzip"]     = "http://".$API_SSAPI_SRV."/ssapi/searchzip.cgi";
$D_SSAPI["searchjapanpost"] = "http://".$API_SSAPI_SRV."/ssapi/searchjapanpost.cgi";	// add 2016/06/13 Y.Matsukawa
$D_SSAPI["listadcd"]      = "http://".$API_SSAPI_SRV."/ssapi/listadcd.cgi";
$D_SSAPI["ml_listadcd"]      = "http://".$API_SSAPI_SRV."/ssapi/ml_listadcd.cgi";	// add 2016/03/31 F.Yokoi
$D_SSAPI["getadstr"]      = "http://".$API_SSAPI_SRV."/ssapi/getadstr.cgi";
$D_SSAPI["npoi"]          = "http://".$API_SSAPI_SRV."/ssapi/npoi.cgi";
$D_SSAPI["npoijnr"]       = "http://".$API_SSAPI_SRV."/ssapi/npoijnr.cgi";
$D_SSAPI["neki"]          = "http://".$API_SSAPI_SRV."/ssapi/neki.cgi";
$D_SSAPI["qr_img"]        = "http://".$API_SSAPI_SRV."/ssapi/qr_img.cgi";
$D_SSAPI["searchroute"]   = "http://".$API_SSAPI_SRV."/ssapi/route/search_route.cgi";

// 地図取得
$D_SSAPI["getmap"]        = "http://".$API_SSAPI_SRV."/ssapi/getmap.cgi";
$D_SSAPI["getmap_jpost"]  = "http://".$API_SSAPI_JPOSTMAP_SRV."/ssapi/getmap.cgi";		// add 2016/11/16 Y.Matsukawa
$D_SSAPI["getmapinfo"]    = "http://".$API_SSAPI_SRV."/ssapi/getmapinfo.cgi";
$D_SSAPI["getmobileinfo"] = "http://".$API_SSAPI_SRV."/ssapi/mobile_info.cgi";
$D_SSAPI["cvtxy2ll"]      = "http://".$API_SSAPI_SRV."/ssapi/cvtxy2ll.cgi";
$D_SSAPI["cvtll2xy"]      = "http://".$API_SSAPI_SRV."/ssapi/cvtll2xy.cgi";
$D_SSAPI["getroutemap"]   = "http://".$API_SSAPI_SRV."/ssapi/getroutemap.cgi";
$D_SSAPI["cvtdatum"]      = "http://".$API_SSAPI_SRV."/ssapi/cvtdatum.cgi";		// add 2016/08/15 Y.Matsukawa

// 車ルート探索
$D_SSAPI["searchroute"]  = "http://".$API_SSAPI_SRV."/ssapi/route/search_route.cgi";

// 携帯用ルート探索
$D_SSAPI["searchrout_m"]  = "http://".$API_SSAPI_SRV."/ssapi/route/emap_mobile_route.cgi";

// CORE I/F
$D_SSAPI["station/word"]  = "http://".$CORE_IF_SRV."/core/v1_0/station/word";
$D_SSAPI["address/word"]  = "http://".$CORE_IF_SRV."/core/v1_0/address/word";	// add 2016/11/14 Y.Uesugi
$D_SSAPI["comb_route/searchlist"]  = "http://".$CORE_IF_V3_SRV."/zmaps/api/apicore/core/v1_0/comb_route/searchlist";	// add 2017/01/18 N.Wada

// JSAPI ---------------------------------------------------
$D_JSAPI_charset="euc-jp";

$D_JSAPI_VER="1.11";

$D_JSAPI["zdccommon"] = "$protocol://".$API_JSAPI_SRV."/jsapi.cgi?key=$D_JSAPI_KEY&ver=$D_JSAPI_VER&enc=EUC&noalert=1&api=";
$D_JSAPI_v2["zdccommon"] = "$protocol://".$API_JSAPI_SRV_V2."/cgi/loader.cgi?key=$D_JSAPI_V2_KEY&ver=2.0&enc=EUC&force=0&noalert=1&api=";		// add 2011/07/07 H.osamoto  

// JSAPI（スマートフォン版） ---------------------------------------------------
$D_JSAPI_SMT_charset = 'UTF-8';
$D_JSAPI_SMT_VER = 'S1.0';
$D_JSAPI_SMT["map"] = "$protocol://".$API_JSAPI_SRV."/jsapi.cgi?key=$D_JSAPI_SMT_KEY&ver=$D_JSAPI_SMT_VER&enc=UTF8&noalert=1&force=1&api=";
$D_JSAPI_SMT["map"] .= "zdccommon.js,zdcmap.js,zdcshape.js";

// JSAPI（スマートフォン版） ---------------------------------------------------
$D_JSAPI_SMT_V2_charset = 'UTF-8';
//$D_JSAPI_SMT_V2["map"] = "$protocol://".$API_JSAPI_SRV_V2."/cgi/loader.cgi?key=$D_JSAPI_SMT_V2_KEY&ver=2.0&enc=EUC&force=0&noalert=1&api=";		mod 2015/09/14 Y.Matsukawa
$D_JSAPI_SMT_V2["map"] = "$protocol://".$API_JSAPI_SRV_V2."/cgi/loader.cgi?key=$D_JSAPI_SMT_V2_KEY&ver=2.0&enc=EUC&force=1&noalert=1&api=";
//	$D_JSAPI_SMT_V2["map"] .= "zdcmap.js,shape.js,geo.js,control.js,usercontrol.js,userwidget.js";	// mod 2015/02/03 H.Osamoto
//$D_JSAPI_SMT_V2["map"] .= "zdcmap.js,search.js,shape.js,geo.js,control.js,usercontrol.js,userwidget.js";		mod 2017/01/18 N.Wada
$D_JSAPI_SMT_V2["map"] .= "zdcmap.js,search.js,searchcombroute.js,shape.js,geo.js,control.js,usercontrol.js,userwidget.js";


// CSS -----------------------------------------------------
//$D_JSCSS["zdcmap"] = "";

// その他 --------------------------------------------------
//地図API用
$D_JS_SVRURL   = "$protocol://".$API_JSAPI_SRV."/mapapi/";

//許可リファラー
$D_ALLOW_REFERER  = "*";

//デフォルト許可IP
$D_DEFAULT_ALLOW_IP[] = '218.225.89.15';//ZDC社内
$D_DEFAULT_ALLOW_IP[] = '218.225.89.53';//VPN
$D_DEFAULT_ALLOW_IP[] = '10.0.0.0/8';//社内

//JSAPI対応ブラウザ判定
$D_JSAPI_UA_CHECK_CGI = "http://".$API_SSAPI_SRV."/jsapi.cgi?key=$D_JSAPI_KEY&ver=$D_JSAPI_VER&enc=EUC&noalert=1&api=zdccommon.js";

//PUB DB接続エラー時のリトライ回数
$D_PUBDB_RETRY_COUNT = 3;

?>
