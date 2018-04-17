<?php
/*=========================================================*/
// �ե�����̾��auth.inc
//
// ���̴ؿ�
//
// ��������2010/01/08
// �����ԡ�Y.Matsukawa
//
// ���⡧API�����ʰ�ǧ��
//
// ��������
// 2010/01/08 Y.Matsukawa	��������
// 2010/12/10 Y.Matsukawa	�����������CGI�б�
// 2011/11/04 Y.Matsukawa	Ź�ް���CGI�����Ǥ��б�
// 2014/01/06 H.Osamoto		���ĥ�ե����null�׵�ǽ�ɲ�
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

// ����ե��륿���
function ipfilter( $var ) {
	if ( strpos( $var , "*" ) === false ) {
		return false;
	} else {
		return true;
	}
}

// IP������
function ipnorm( $var ) {
	$wpos = strpos( $var , "*" );
	//  3���Ķ���Ƥ��ơ�4���ܰʹߤ� * �ˤʤäƤ��ʤ����������ǡ���
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

// �����å�
function check( $keyip , $ip) {
	//  ��IP�����å������å��Ȥθߴ����Τ��ᡢ*�и����֤ޤǤ�ʸ���������פ�Ԥ�
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

	//  �ǽ�ʸ�����磻��ɥ����ɻ���ʤ顢�ɲ����Ǥ�磻��ɥ����ɤ�����
	if ( substr( $wkkeyip, strlen( $wkkeyip ) - 1, 1 ) === "*" ) {
		$wkvalue = "***";
	} else {
		$wkvalue = "---";
	}

	//  ���ǿ����碌��
	$ipaddr_len = count($ipaddr);
	$splitip_len = count($splitip);

	for ( $i = 0 ; $i < ( 4 - $ipaddr_len ) ; $i++ ) {
		$ipaddr[] = $wkvalue;
	}

	for ( $i = 0 ; $i < ( 4 - $splitip_len ) ; $i++ ) {
		$splitip[] = "---";
	}

	for ( $i = 0 ; $i < count($ipaddr) ; $i++) {
		//  ���碌�ѥǡ�����̵��
		if ( $ipaddr[$i] === "---" && $splitip[$i] !== "---" ) {
			$ret = false;
			break;
		} elseif ( $ipaddr[$i] !== "---" && $splitip[$i] === "---" ) {
			$ret = false;
			break;
		//  �ɤ������� * ���꤬����ʤ�
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

// IP���ɥ쥹�ꥹ�ȥ����å�
function ip_check ($iplist, $ip) {
	$ret = false;
	if ( strpos( $iplist , ":" ) > 0 ) {
		$ipaddr = explode( ":" , $iplist);
		// ������򸡺�
		if ( in_array( $ip , $ipaddr ) ) {
			$ret = true;
		} else {
			//  *����IP������å�
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

// IP���ɥ쥹�ꥹ�ȥ����å��ʥ��ѥ졼�������		add 2011/11/04 Y.Matsukawa
function ip_check2 ($iplist, $ip, $sep=";") {
	$ret = false;
	if ( strpos( $iplist , $sep ) > 0 ) {
		$ipaddr = explode( $sep , $iplist);
		// ������򸡺�
		if ( in_array( $ip , $ipaddr ) ) {
			$ret = true;
		} else {
			//  *����IP������å�
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

// ��ե��顼�����å�		add 2010/12/10 Y.Matsukawa
function referer_check(&$reflist, $ref) {
	if (!is_array($reflist) || !count($reflist)) return false;
	foreach ($reflist as $referer) {
		if (strpos(" ".$ref, $referer) == 1) return true;
	}
	return false;
}

// ��ե��顼null�����å�		add 2014/01/06 H.Osamoto
function referer_null_check($null_flg, $ref) {
	// null��������ե饰��1�����ġ�0���Ե��ġ�
	if ($null_flg == "1") {
		// ��ե���
		if ($ref == "") {
			return true;
		}
	}
	return false;
}
?>