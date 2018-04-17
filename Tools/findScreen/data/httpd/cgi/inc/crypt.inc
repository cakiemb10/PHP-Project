<?php
/**********************************************************************
 *	ファイル：	crypt.inc
 *---------------------------------------------------------------------
 *	機  能  ：  AIDの暗号/復号化
 *				エリアコードの暗号/復号化を行う
 *---------------------------------------------------------------------
 *	概  要  ：	認証IDについては、
 *				「認証承認ID暗号化仕様V0001.doc」に則る
 *				エリアコードの暗号化については、
 *				「CMDN_エリアコード暗号化仕様V0006.doc」に則る。
 *---------------------------------------------------------------------
 *	作成者  ： N.Fujiwara
 *	作成日  ： 2005/07/xx
 *	修正者  ：
 *	修正日  ：
 *	備  考  ：
// 更新履歴
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
 *********************************************************************/


define	( "D_ACODE_CNT_WIDTH", 2 );
define	( "D_ENCODE", 1 );
define	( "D_DECODE", 2 );

/**
* 関数名	：	make_seed()
* 概  要	：	乱数ジェネレータの初期化で使用する seed を生成する
* 引  数	：	なし
* 戻り値	：	srand() で使用する seed を返す
**/
function make_seed(){
        list($usec, $sec) = explode(' ', microtime());
        return (float) $sec + ((float) $usec * 100000);
}

/**
* 関数名	：	f_transChars()
* 概  要	：	「認証承認ID暗号化仕様V0001.doc」に基く文字変換処理を実行する
* 引  数	：	$p_strsrc	-> 文字変換を行う文字列
*				$code		-> D_ENCODE(暗号) または D_DECODE(復号) をセットする
* 戻り値	：	文字変換処理後の文字列
**/
function f_transChars( $p_strsrc, $code ) {
	$strbuf	= null;
	if ( strlen( $p_strsrc ) == 0 ) 	return	null;
	if ( $code == D_ENCODE ) {
		for( $i = 0; $i < strlen( $p_strsrc ); $i++ ){
			$chr	= ord( $p_strsrc[$i] );
			if( $chr >= 48 && $chr <= 53 ){
				$strbuf	.= chr ( $chr + 4 );
				continue;	
			} else if ( $chr >= 54 && $chr <= 57 ) {
				$strbuf	.= chr ( $chr - 6 );
				continue;	
			} else if ( ( $chr >= 65 && $chr <= 90 ) || ( $chr >= 97 && $chr <= 122 ) ){
				$strbuf	.= chr ( 187 - $chr );
				continue;	
			} else {
				return	null;
			}
		}
	} else if ( $code  == D_DECODE ) {
		for( $i = 0; $i < strlen( $p_strsrc ); $i++ ){
			$chr	= ord( $p_strsrc[$i] );
			if( $chr >= 48 && $chr <= 51 ){
				$strbuf	.= chr ( $chr + 6 );
				continue;	
			} else if ( $chr >= 52 && $chr <= 57 ) {
				$strbuf	.= chr ( $chr - 4 );
				continue;	
			} else if ( ( $chr >= 65 && $chr <= 90 ) || ( $chr >= 97 && $chr <= 122 ) ){
				$strbuf	.= chr ( 187 - $chr );
				continue;	
			} else {
				return	null;
			}
		}
	} else {
		return	null;
	}
	return	$strbuf;
}

function f_encrypt_api_key( $p_org_key ) {
	$dict = array(	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
					"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
					"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
					"U", "V", "W", "X", "Y", "Z",
					"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
					"k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
					"u", "v", "w", "x", "y", "z" );
	$dict_len	= count( $dict );
	if ( strlen( $p_org_key ) == 0 )	return	null;
	if ( ! ctype_print( $p_org_key ) )	return	null;
	$com_key	= null;
	$org_len	= strlen( $p_org_key );
	switch( strlen( $p_org_key ) % 3 ){
	case 1: $pad_len = 2;
			break;
	case 2: $pad_len = 1;
			break;
	case 0: $pad_len = 0;
			break;
	default: $pad_len = 0;
			break;
	}
	$new_len	=	strlen( $p_org_key ) + $pad_len;
	$strbuf	= str_pad( $p_org_key , $new_len );
	$strbuf	= base64_encode( $strbuf );
	$strbuf	= f_transChars( $strbuf, D_ENCODE );
	if ( $strbuf == null ){
		return	null;
	}
    srand(make_seed());
	for( $i = 0; $i < strlen( $strbuf ); $i++ ){
		$com_key	.= $strbuf[$i];
		if ( $i % 2 ) {
			$com_key	.=	$dict[ rand( 0, $dict_len - 1 ) ] ;
		}
	}
	return	(string)$org_len . $com_key;
}


function f_decrypt_api_key( $p_com_key ) {
	if ( strlen( $p_com_key ) == 0 )		return	null;
	if ( ! ctype_alnum( $p_com_key ) )		return	null;
	$code_cnt	= (int)substr( $p_com_key, 0, D_ACODE_CNT_WIDTH );
	$strbuf	= null;
	$j = 0;
	for ( $i = 0 ; $i < strlen( $p_com_key ); $i++ ){
		$idx	= $i + $j + D_ACODE_CNT_WIDTH;
		// mod 2011/07/05 Y.Nakajima [
		if (isset($p_com_key[$idx])) {
		$strbuf	.= $p_com_key[$idx];
		}
		if ( $i % 2 )	$j++;
	}
	$org_keyd	= f_transChars( $strbuf, D_DECODE );
	return	trim( base64_decode( $org_keyd ) );
}

?>
