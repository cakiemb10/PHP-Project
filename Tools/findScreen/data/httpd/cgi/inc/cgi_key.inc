<?php
// ---------------------------------------------------------
// 定義ファイル APIキー
// ---------------------------------------------------------
$hostname = trim(`hostname`);
//**********************************************************
//* 環境により設定内容を切替
//2011/09/02 VMサーバリリース時は、host名が変更になるが、本番機に繋ぐので、検証機のcaseを追加はしない
//	2012/03/08	H.Osamoto		検証cgiwebのVIP切り替え
//								開発環境のcgiweb向き先変更「devapiweb(10.47.50.15)⇒dev-cgiweb(10.47.50.33)」
//	2012/04/11	H.Osamoto		本番cgiweb切り替え ドメイン(GIP)⇒VIP
//**********************************************************
switch( $hostname ){//----- 開発機 -----
//	case "devemapweb":	mod 2012/03/08 H.Osamoto
case "dev-storenaviweb01":

	// mod 2012/03/08 H.Osamoto [
	//	$API_SSAPI_SRV  = "10.47.50.15";
	//	$D_CGI_KEY = '41nQPzCfng0vBlngcPBsnALf9AmglPBbjgrzDcngvynnnQGyvHng3b52mQrn7xngxzF0mwfXFQmgczF3nQKbT1';
	$API_SSAPI_SRV  = "10.47.50.33";
	$D_CGI_KEY = '41nQXzCDnQpvBvngxPBcnAgf9dmgqPBjjgjzDIngWynQnQ4yv5ngeb5hmQyn7angVzFQmwnXFkmgfzFxmAKPTz';
	// mod 2012/03/08 H.Osamoto ]
    break;

//----- 検証機 -----
case "emapweb00":

	$API_SSAPI_SRV  = "test.api.e-map.ne.jp";
	#$D_CGI_KEY = '45nQzzCgnQuzCkngezB7nAlf90mg4PBQjgMzDBngPudpnQMypMngXPAmnwkf7rnQ9vD7oQDvAjnBd8CAnwuPFFngdj4D'; 
	$D_CGI_KEY = '45nQ6zCYnQPzCUnggzB2nAIf9NmgfPBbjgDzD6nghudQnQSypwng6PAznw2f7wnQ8vDfoQ1vAmnBu8CDnwSnFUngpbBd';
	break;

//----- VM検証機 -----
case "storenaviweb-v01":

	//	$API_SSAPI_SRV  = "172.16.164.10";	mod 2012/03/08 H.Osamoto
	$API_SSAPI_SRV  = "172.28.0.156";
	//$D_CGI_KEY = '45nQ6zCYnQPzCUnggzB2nAIf9NmgfPBbjgDzD6nghudQnQSypwng6PAznw2f7wnQ8vDfoQ1vAmnBu8CDnwSnFUngpbBd';
	$D_CGI_KEY = "40nQmP9ClggvBQnATvBJnAJf9Pmg9PBFjgdzDgngHudhnQxypRng1PAHnwJf7UngTXBToQ5r9NoQdzFFpR6zT8";
	break;

//----- 本番機 -----
default:

	// mod 2012/04/11 H.osamoto [
	//	$API_SSAPI_SRV  = "api.e-map.ne.jp";
	//	$D_CGI_KEY = '45nQ6zCYnQPzCUnggzB2nAIf9NmgfPBbjgDzD6nghudQnQSypwng6PAznw2f7wnQ8vDfoQ1vAmnBu8CDnwSnFUngpbBd';
	$API_SSAPI_SRV  = "172.28.0.56";
	$D_CGI_KEY = '40nQbP9LlgqvBanA3vB5nARf9XmgsPBmjgezDSngBudtnQ5ypvngHPALnwxf7dngmXB7oQBr8SoQszFwpRnzTg';
	// mod 2012/04/11 H.osamoto ]
}

?>
