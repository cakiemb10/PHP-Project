<?php
/*=========================================================*/
// ファイル名：myarea_func.inc
//
// Myエリア用共通関数
//
// 作成日：2011/04/11
// 作成者：H.Osamoto
//
// 解説：Myエリア用共通関数
//
// 更新履歴
// 2011/04/11 H.Osamoto	新規作成
/*=========================================================*/

/*==============================================*/
// Myエリアデータ取得
/*==============================================*/
function select_myarea($dba, $corp_id, $user_id, &$hit_num, &$retdata){
    $sql = "SELECT * ";
    $sql .= "FROM MYAREA_TBL ";
    $sql .= "WHERE CORP_ID = '".$corp_id."' ";
    $sql .= "AND USER_ID = '".$user_id."'";
    $sql .= "ORDER BY DISP_ORDER";

    $stmt = null;

    if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
        $dba->free($stmt);
        return 9;   //sqlExecute()エラー
    }
    $retdata_all = array();
    while( $dba->getRecInto( $stmt,$data,OCI_ASSOC) ) {
        $retdata_all[] = $data;
    }
    $hit_num = count ($retdata_all);
    if ( $hit_num <= 0 ) {
        $dba->free($stmt);
        return 1;   //検索結果データなし
    }
    $dba->free($stmt);

    $retdata = $retdata_all;

    return  0;
}

/*==============================================*/
// Myエリアデータ追加
/*==============================================*/
function myarea_add($dba, $corp_id, $user_id, $myarea_name, $lat, $lon, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_ADD( ";
	$spstr  .=  ":i_corp_id, :i_user_id, :i_myarea_name, :i_lat, :i_lon, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";

	$stmt = OCIParse($dba->conn, $spstr);

	if (!OCIBindByName($stmt, ':i_corp_id', $corp_id, 15)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_user_id', $user_id, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_myarea_name', $myarea_name, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_lat', $lat, 9)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_lon', $lon, 9)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}

	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

/*==============================================*/
// Myエリア名更新
/*==============================================*/
function myarea_name_update($dba, $myarea_id, $myarea_name, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_NAME_UPDT( ";
	$spstr  .=  ":i_myarea_id, :i_myarea_name, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";


	$stmt = OCIParse($dba->conn, $spstr);
	
	if (!OCIBindByName($stmt, ':i_myarea_id', $myarea_id, 8)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_myarea_name', $myarea_name, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}
	
	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

/*==============================================*/
// Myエリア表示順更新
/*==============================================*/
function myarea_order_update($dba, $myarea_id, $corp_id, $user_id, $disp_order, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_ORDER_UPDT( ";
	$spstr  .=  ":i_myarea_id, :i_corp_id, :i_user_id, :i_disp_order, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";

	$stmt = OCIParse($dba->conn, $spstr);

	if (!OCIBindByName($stmt, ':i_myarea_id', $myarea_id, 8)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_corp_id', $corp_id, 15)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_user_id', $user_id, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_disp_order', $disp_order, 3)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}
	
	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

/*==============================================*/
// Myエリア削除
/*==============================================*/
function myarea_del($dba, $myarea_id, $corp_id, $user_id, &$rtncd) {
	$spstr  =   "begin ";
	$spstr  .=  "P_MYAREA_DEL( ";
	$spstr  .=  ":i_myarea_id, :i_corp_id, :i_user_id, :o_rtncd";
	$spstr  .=  "); ";
	$spstr  .=  "end;";

	$stmt = OCIParse($dba->conn, $spstr);

	if (!OCIBindByName($stmt, ':i_myarea_id', $myarea_id, 8)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_corp_id', $corp_id, 15)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':i_user_id', $user_id, 1000)) {
		$dba->free($stmt);
		return false;
	}
	if (!OCIBindByName($stmt, ':o_rtncd', $rtncd, 4)) {
		$dba->free($stmt);
		return false;
	}

	if (!OCIExecute($stmt, OCI_DEFAULT)) {
		$dba->free($stmt);
		return false;
	}
	$dba->free($stmt);
	return true;
}

// ------------------------------------------------------------
// 機種依存文字チェック
// (EUC-JP：第一水準、第二水準のみ許容)
// ------------------------------------------------------------
function IzonSearch( $str ) {

	// ３バイト文字（JIS X 212 補助漢字）が含まれていたらエラー
	// ※補助漢字がそのまま送信されてきた場合は、ここでフックされます
	// （IE以外のブラウザからの送信や、CSVファイルアップロード等）
	if (preg_match('/(\x8F[\xA1-\xFE][\xA1-\xFE])/', $str)) {
		return false;
	}

	// パーセントエンコードされた３バイト文字（JIS X 212 補助漢字）が含まれていたらエラー
	// ※IEなどから、補助漢字がエンコードされて送信されてきた場合は、ここでフックされます
	// （例）「&#28583;」「&AElig;」
	if (preg_match('/(&#[0-9]{1,};|&[a-zA-Z]{1,};)/', $str)) {
		return false;
	}

	// 半角カナを全角カナに変換（半角カナが混在していると、全角文字抜き出しに失敗するため） 2007/08/13 add Y.Matsukawa
	$w_str = mb_convert_kana($str, 'K');

	// 全角文字の抜き出し
	preg_match_all( '/([\xA1-\xFE][\xA1-\xFE])*/', $w_str, $matchword );

	for ( $i=0; $i < count( $matchword[0] ) ; $i++) {
		if ( $matchword[0][$i] ) {
			// EUC-JP  第一水準、第二水準の文字チェック
			if ( ! preg_match( '/^(([\xA1-\xA8]|[\xB0-\xF4])[\xA1-\xFE])*$/', $matchword[0][$i]) ) {
				return false;
			}
		}
	}
	return true;
}

?>
