<?php
/*=========================================================*/
// ファイル名：auth.inc
//
// 共通関数
//
// 作成日：2010/01/08
// 作成者：Y.Matsukawa
//
// 解説：APIキー簡易認証
//
// 更新履歴
// 2010/01/08 Y.Matsukawa	新規作成
// 2010/12/10 Y.Matsukawa	ローソン向けCGI対応
// 2011/11/04 Y.Matsukawa	店舗案内CGI汎用版に対応
// 2014/01/06 H.Osamoto		許可リファラ「null」機能追加
/*=========================================================*/

function api_key_check( $api_key ) {
	if ( $api_key == "" ) return "2002";
	if ( strlen ( $api_key ) > 130 ) return "2002";
	$ORG_API_KEY = $api_key;

	$KEY_IP = substr($ORG_API_KEY, 30);
	$SVR_IP = $_SERVER["REMOTE_ADDR"];
	if ( ip_check( $KEY_IP, $SVR_IP ) === false ) {
		return  "1001";
	}

	return "0000";
}

// 配列フィルタリング
function ipfilter( $var ) {
	if ( strpos( $var , "*" ) === false ) {
		return false;
	} else {
		return true;
	}
}

// IP正規化
function ipnorm( $var ) {
	$wpos = strpos( $var , "*" );
	//  3桁を超えていて、4桁目以降が * になっていない場合は不正データ
	if ( strlen( $var ) > 3 && strlen(str_replace( "*", "", substr( $var, 3 ) ) ) > 0 ) {
		return "xxx";
	} elseif ( $wpos === false ) {
		return substr( str_pad( $var , 3 , "-" , STR_PAD_LEFT), 0, 3 );
	} elseif ( $wpos > 0 ) {
		return substr( str_pad( $var , 3 , "*" , STR_PAD_RIGHT), 0, 3 );
	} else {
		return substr( str_pad( $var , 3 , "*" , STR_PAD_LEFT), 0, 3 );
	}
} 

// チェック
function check( $keyip , $ip) {
	//  旧IPチェックロジックとの互換性のため、*出現位置までの文字列完全一致を行う
	if ( strpos( $keyip, "*" ) !== false ) {
		if ( strlen( substr( $keyip, strpos( $keyip, "*" ) ) ) <= 1 ) {
			if ( strpos( $ip, substr( $keyip, 0, strpos( $keyip, "*" ) ) ) !== false && 
			strpos( $ip, substr( $keyip, 0, strpos( $keyip, "*" ) ) ) == 0 ) {
				return true;
			}
		}
	}

	if ( strrpos( $keyip, "." ) === strlen( $keyip ) -1 ) {
		$wkkeyip = substr( $keyip, 0, strpos( $keyip, ".", strlen( $keyip ) -1 ) );
	} else {
		$wkkeyip = $keyip;
	}
    
	if ( strpos( $wkkeyip , "." ) === false ) {
		$ipaddr = array( $wkkeyip );
	} else {
		$ipaddr = explode( "." , $wkkeyip);
	}

	$splitip = explode( "." , $ip);

	$ipaddr = array_map( "ipnorm" , $ipaddr );
	$splitip = array_map( "ipnorm" , $splitip );

	//  最終文字がワイルドカード指定なら、追加要素もワイルドカードで埋める
	if ( substr( $wkkeyip, strlen( $wkkeyip ) - 1, 1 ) === "*" ) {
		$wkvalue = "***";
	} else {
		$wkvalue = "---";
	}

	//  要素数を合わせる
	$ipaddr_len = count($ipaddr);
	$splitip_len = count($splitip);

	for ( $i = 0 ; $i < ( 4 - $ipaddr_len ) ; $i++ ) {
		$ipaddr[] = $wkvalue;
	}

	for ( $i = 0 ; $i < ( 4 - $splitip_len ) ; $i++ ) {
		$splitip[] = "---";
	}

	for ( $i = 0 ; $i < count($ipaddr) ; $i++) {
		//  桁合わせ用データは無視
		if ( $ipaddr[$i] === "---" && $splitip[$i] !== "---" ) {
			$ret = false;
			break;
		} elseif ( $ipaddr[$i] !== "---" && $splitip[$i] === "---" ) {
			$ret = false;
			break;
		//  どこかしら * 指定があるなら
		} elseif ( strpos( $ipaddr[$i] , "*" ) !== false ) {
			for ( $ii = 0 ; $ii < 3 ; $ii++ ) {
				if ( substr($ipaddr[$i],$ii,1) == "*" ) {
					$ret = true;
				} elseif ( substr($ipaddr[$i],$ii,1) == "-" ) {
				} elseif ( substr($ipaddr[$i],$ii,1) == substr($splitip[$i],$ii,1) ) {
					$ret = true;
				} else { 
					$ret = false;
					break 2;
				}
			}
		} elseif ( $ipaddr[$i] == $splitip[$i] ) {
			$ret = true;
		} else {
			$ret = false;
			break;
		}
	}

	return $ret;
}

// IPアドレスリストチェック
function ip_check ($iplist, $ip) {
	$ret = false;
	if ( strpos( $iplist , ":" ) > 0 ) {
		$ipaddr = explode( ":" , $iplist);
		// 配列中を検索
		if ( in_array( $ip , $ipaddr ) ) {
			$ret = true;
		} else {
			//  *指定IPをチェック
			foreach ( array_filter( $ipaddr , "ipfilter") as $ipaddr_v ) {
				if ( check( $ipaddr_v , $ip ) ) {
					$ret = true;
					break;
				}
			}
		}
	} elseif ( check( $iplist , $ip ) ) {
		$ret = true;
	}
	return $ret;
}

// IPアドレスリストチェック（セパレータ指定）		add 2011/11/04 Y.Matsukawa
function ip_check2 ($iplist, $ip, $sep=";") {
	$ret = false;
	if ( strpos( $iplist , $sep ) > 0 ) {
		$ipaddr = explode( $sep , $iplist);
		// 配列中を検索
		if ( in_array( $ip , $ipaddr ) ) {
			$ret = true;
		} else {
			//  *指定IPをチェック
			foreach ( array_filter( $ipaddr , "ipfilter") as $ipaddr_v ) {
				if ( check( $ipaddr_v , $ip ) ) {
					$ret = true;
					break;
				}
			}
		}
	} elseif ( check( $iplist , $ip ) ) {
		$ret = true;
	}
	return $ret;
}

// リファラーチェック		add 2010/12/10 Y.Matsukawa
function referer_check(&$reflist, $ref) {
	if (!is_array($reflist) || !count($reflist)) return false;
	foreach ($reflist as $referer) {
		if (strpos(" ".$ref, $referer) == 1) return true;
	}
	return false;
}

// リファラーnullチェック		add 2014/01/06 H.Osamoto
function referer_null_check($null_flg, $ref) {
	// null許可設定フラグ（1：許可、0：不許可）
	if ($null_flg == "1") {
		// リファラ
		if ($ref == "") {
			return true;
		}
	}
	return false;
}
?>
