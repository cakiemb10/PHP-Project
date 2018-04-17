<?php
/*========================================================*/
// ファイル名：getsdate.cgi
// 処理名：EMAP(拠点案内サービス)のサービス期間を取得する
//
// 作成日：2007/02/19
// 作成者：N.Fujiwara(Fuzzy Eng.)
//
// 解説：EMAP(拠点案内サービス)のサービス期間(開始日、終了日、サービス期間フラグ)を取得する
//
// 更新履歴
//   ・2007/01/12 N.Fujiwara(Fuzzy Eng.)	新規作成
//   ・2007/02/14 ogawa(ZDC)				戻り値の並び順を変更
//   ・2012/07/25 H.Osamoto					戻り値にPCバージョンを追加
//   ・2013/05/30 H.Osamoto					契約種別を判定する
/*========================================================*/
	header( "Content-Type: Text/html; charset=euc-jp" );
	include( "d_serv_ora.inc" );
	include( "inc/oraDBAccess.inc" );
	include( "inc/sql_collection_getsdate.inc" );
	include( "inc/sql_collection_get_pc_version.inc" );
	include( "inc/sql_collection_emap_conf.inc" );	// add 2012/12/26 K.Masuda


	//define
	$cgi_kind = "890";	//CGI種別
	$enc = "EUC";		//出力文字コード

	//入力パラメータ取得
    if ( $_SERVER['REQUEST_METHOD'] == "GET" ) {
        $cid = urldecode( $_GET['cid'] );	//企業ID
        $sys = urldecode( $_GET['sys'] );	// add 2012/12/26 K.Masuda
    } else if ( $_SERVER['REQUEST_METHOD'] == "POST" ) {
        $cid = urldecode( $_POST['cid'] );
        $sys = urldecode( $_POST['sys'] );	// add 2012/12/26 K.Masuda
    }
    //入力パラメータチェック
    if ( $cid == "" ) {
        print   $cgi_kind . "19100\n";
        exit;
    }

    $dba = new oraDBAccess();
    if ( ! $dba->open() ) {
        $dba->close();
        print   $cgi_kind . "17900\n";
        exit;
    }

    //カラム名リスト取得
	$arr_col_name = Array();
    $retcd = select_serv_date( &$dba, $cid, &$arr_col, &$err_msg );
    if ( $retcd != 0 ) {
        $dba->close();
        if ( $retcd == 1 ) {
            print   $cgi_kind . "11009\n";    //検索結果データなし
        } else {    //9
            print   $cgi_kind . "17999\n";    //その他DBエラー
        }
        exit;
    }

	// add 2012/07/25 H.osamoto [
    $retcd_pc_ver = select_pc_version(&$dba, $cid, &$arr_col_pc_ver, &$err_msg);
	if ($retcd_pc_ver == 0) {
		$pc_ver = $arr_col_pc_ver["VALUE"];
	} else {
		$pc_ver = "1";
	}
	// add 2012/07/25 H.osamoto ]

	// add 2013/05/30 H.Osamoto [
	// 契約種別判定
	$arr_emap_corp_mst = array();
	$retcd = select_emap_corp_mst(&$dba, $cid, &$arr_emap_corp_mst);
	if ($retcd != 0) {
		$dba->close();
		if ($retcd == 1) {
			print   $cgi_kind . "11009\n";    //検索結果データなし
		} else {    //9
			print   $cgi_kind . "17999\n";    //その他DBエラー
		}
		exit;
	}
	$kbnret = 0;
	if( ($sys == "P") && ($arr_emap_corp_mst['EMAP_KBN'] == '0') ) {
		$kbnret = 1;
	} else if ( ($sys == "M") && ($arr_emap_corp_mst['M_EMAP_KBN'] == '0') ) {
		$kbnret = 1;
	} else if ( ($sys == "S") && ($arr_emap_corp_mst['S_EMAP_KBN'] == '0') ) {
		$kbnret = 1;
	} else if ( ($sys == "Q") && ($arr_emap_corp_mst['EMAP_KBN'] == '0') ) {
		$kbnret = 1;
	}
	if ( $kbnret == 1 ) {
		print   $cgi_kind . "11009\n";    //検索結果データなし
		exit;
	}
	// add 2013/05/30 H.Osamoto ]

    $dba->close();

    print   $cgi_kind . "00000\n";
    $buf =  $arr_col["SFLG"]           . "\t" .
    $buf =  $arr_col["S_DATE"]         . "\t" .
	// mod 2012/07/25 H.Osamoto [
    //        $arr_col["E_DATE"];
            $arr_col["E_DATE"]         . "\t" .
            $pc_ver;
	// mod 2012/07/25 H.Osamoto ]
    $buf .= "\n";
    if ( $enc != "EUC" ) {
        $buf    = mb_convert_encoding( $buf, $enc );
    }

    print $buf;


?>
