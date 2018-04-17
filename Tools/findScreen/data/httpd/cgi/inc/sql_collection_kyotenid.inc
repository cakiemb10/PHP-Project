<?php
/*========================================================*/
// 更新履歴
// 2007/07/11 Y.Matsukawa	検索結果なしの時にリソース解放していなかった
// 2009/08/27 Y.Matsukawa	拠点縮尺設定
// 2011/03/10 Y.Matsukawa	スマートフォン版対応
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/26 Y.Matsukawa	スマホ用拠点縮尺カラム対応
// 2012/01/27 K.Masuda		指定拠点情報取得に公開/NEW表示日時を追加
// 2012/02/16 Y.Matsukawa	jkn対応
// 2013/07/19 T.Sasaki		拠点（複数）画像対応
// 2013/08/05 N.Wada		即時反映対象企業対応
// 2015/05/22 H.osamoto		拠点縮尺にキーワードを付与し誤作動を防ぐ
/*========================================================*/

function select_col_name( &$dba, $cid, $type, &$retdata, &$err_msg ){
	//CORP_IDをキーにKYOTEN_ITEM_TBLからCOL_NAMEをselectする

	// del 2009/08/27 Y.Matsukawa [
	//	$sql = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	//	$sql .= "WHERE CORP_ID = '$cid' AND ";
	// del 2009/08/27 Y.Matsukawa ]
	// add 2009/08/27 Y.Matsukawa [
	$sql0 = "SELECT COL_NAME FROM KYOTEN_ITEM_TBL ";
	$sql0 .= "WHERE CORP_ID = '$cid' ";
	// add 2009/08/27 Y.Matsukawa ]

	switch ( $type ) {
		// PC詳細
		case "1":
			$buf = "SYOUSAI_KBN";
			break;
		// 印刷
		case "2":
			$buf = "INSATSU_KBN";
			break;
		// フキダシ
		case "3":
			$buf = "FUKIDASI_KBN";
			break;
		// 携帯詳細
		//default:		mod 2011/03/10 Y.Matsukawa
		case "4":
			$buf = "M_SYOUSAI_KBN";
			break;
		// add 2011/03/10 Y.Matsukawa [
		// スマートフォン詳細
		case "5":
			$buf = "OPT_06";
			break;
		// add 2011/03/10 Y.Matsukawa ]
	}
	
	// 表示項目
	//$sql .= "$buf = '1' ";		mod 2009/08/27 Y.Matsukawa
	$sql = $sql0." AND $buf = '1' ";
	$sql .= "ORDER BY DISP_NUM ";
	$stmt = null;
	if (!$dba->sqlExecute($sql, $stmt)) {
		$dba->free($stmt);
		return 9;
	}
	$retdata = array();
	while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
		$retdata[] = $data;
	}
	$dba->free($stmt);

	// add 2009/08/27 Y.Matsukawa [
	if ($type == 1 || $type == 2 || $type == 3) {		// PC詳細／印刷／吹き出し
		//PC縮尺カラム
		$sql = $sql0." AND OPT_03 = 'P'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			return 9;
		}
		// mod 2015/05/22 H.Osamoto [
		//	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		//		$retdata[] = $data;
		//	else
		//		$retdata[] = null;
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			$data["COL_NAME"] = "'@@KYOTEN_LEVEL@@:'||A.".$data["COL_NAME"];
			$retdata[] = $data;
		} else {
			$retdata[] = null;
		}
		// mod 2015/05/22 H.Osamoto ]
		$dba->free($stmt);
	}

	//携帯縮尺カラム
	if ($type == 4) {		// 携帯詳細
		$sql = $sql0." AND OPT_03 = 'M'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			return 9;
		}
		// mod 2015/05/22 H.Osamoto [
		//	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		//		$retdata[] = $data;
		//	else
		//		$retdata[] = null;
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			$data["COL_NAME"] = "'@@KYOTEN_LEVEL@@:'||A.".$data["COL_NAME"];
			$retdata[] = $data;
		} else {
			$retdata[] = null;
		}
		// mod 2015/05/22 H.Osamoto ]
		$dba->free($stmt);
	}
	// add 2009/08/27 Y.Matsukawa ]

	//スマホ縮尺カラム		add 2011/08/26 Y.Matsukawa
	if ($type == 5) {		// スマホ詳細
		$sql = $sql0." AND OPT_03 = 'S'";
		$stmt = null;
		if (!$dba->sqlExecute($sql, $stmt)) {
			$dba->free($stmt);
			return 9;
		}
		// mod 2015/05/22 H.Osamoto [
		//	if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) 
		//		$retdata[] = $data;
		//	else
		//		$retdata[] = null;
		if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
			$data["COL_NAME"] = "'@@KYOTEN_LEVEL@@:'||A.".$data["COL_NAME"];
			$retdata[] = $data;
		} else {
			$retdata[] = null;
		}
		// mod 2015/05/22 H.Osamoto ]
		$dba->free($stmt);
	}

	$result = count($retdata);
	if ($result <= 0) {
		//$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa	del 2009/08/27 Y.Matsukawa
		return 1;	//検索結果データなし(入力のCIDにマッチするデータがない場合 or 入力のCIDにマッチするデータはあるが入力のタイプにチェックが入っていない場合)
	}
	//$dba->free($stmt);		del 2009/08/27 Y.Matsukawa
	return 0;
}

//function select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, &$retdata, &$err_msg ){		mod 2012/02/16 Y.Matsukawa
//function select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, &$retdata, &$err_msg, $jkn='' ){	mod 2013/08/05 N.Wada
function select_kyoten_tbl_kid( &$dba, $cid, $kid, $arr_col_name, &$retdata, &$err_msg, $jkn='', $immref=false ){
	//指定拠点情報を取得する。
	//CORP_ID、KYOTEN_IDをキーに、
	//KYOTEN_TBLからLAT、LON、ICON_ID、$arr_col_name(「拠点名、住所、汎用項目」)を
	//KYOTEN_GIF_TBLから拠点画像テーブルの件数（K_GIF_NUM）、本日がNEWアイコン表示日であるかを
	//返す。
	//$arr_col_nameが空の場合は、「拠点名、住所、汎用項目」は返さない。

	$sql  = "SELECT A.LAT, A.LON, A.ICON_ID, DECODE(B.INS_DT, NULL, '0', '1') AS K_GIF_NUM, ";

	//NEWアイコン表示フラグ
	//  開始日、終了日共にNULLの場合：'0'
	//  SYSDATEが開始日から終了日に入っている場合：'1'
	//  SYSDATEが開始日から終了日に入っていない場合：'0'
	//  ※但し、例えばSYSDATEが20070306で、開始日がNULL、終了日が20070305の場合は、'0'。
	$sql .= "CASE ";
	$sql .= "WHEN A.DISP_NEW_S_DATE IS NULL AND A.DISP_NEW_E_DATE IS NULL THEN '0' ";
	$sql .= "WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
	$sql .= "NVL(DISP_NEW_E_DATE, SYSDATE) THEN '1' ";
	$sql .= "ELSE '0' ";
	$sql .= "END AS BFLG ";

	if ( count($arr_col_name) > 0 ) {	//空ではない場合
		$first_flg = 0;
		foreach( $arr_col_name as $rowdata ) {
			if (is_array($rowdata)) {			// add 2009/08/27 Y.Matsukawa
				if ( $first_flg == 0 ) {
					// mod 2011/07/05 Y.Nakajima
					$sql .= ", A." . $rowdata['COL_NAME'];
					$first_flg = 1;
				} else {
					// mod 2011/07/05 Y.Nakajima
					// mod 2015/05/22 H.Osamoto [
					//	$sql .= "," .  " A." . $rowdata['COL_NAME'];
					if (preg_match('/@@KYOTEN_LEVEL@@/', $rowdata['COL_NAME'])) {
						$sql .= "," . $rowdata['COL_NAME'];
					} else {
						$sql .= "," .  " A." . $rowdata['COL_NAME'];
					}
					// mod 2015/05/22 H.Osamoto ]
				}
			// add 2009/08/27 Y.Matsukawa [
			} else {
				$sql .= ",null";
			// add 2009/08/27 Y.Matsukawa ]
			}
		}
		$sql .= " ";
	}

	// add 2012/01/27 K.Masuda [
	// 【注意】この4項目は最後に追加するものとする！（順変更不可）
	$sql .= ",TO_CHAR(A.PUB_S_DATE,'yyyymmddhh24') AS PUB_S_DATE ";
	$sql .= ",TO_CHAR(A.PUB_E_DATE,'yyyymmddhh24') AS PUB_E_DATE ";
	$sql .= ",TO_CHAR(A.DISP_NEW_S_DATE,'yyyymmddhh24') AS DISP_NEW_S_DATE ";
	$sql .= ",TO_CHAR(A.DISP_NEW_E_DATE,'yyyymmddhh24') AS DISP_NEW_E_DATE ";
	// add 2012/01/27 K.Masuda ]
	//$sql .= "FROM KYOTEN_TBL A, KYOTEN_GIF_TBL B ";	mod 2013/08/05 N.Wada [
	if ( $immref ) {
		$sql .= "FROM IM_KYOTEN_TBL A, IM_KYOTEN_GIF_TBL B ";
	} else {
		$sql .= "FROM KYOTEN_TBL A, KYOTEN_GIF_TBL B ";
	}
	// mod 2013/08/05 N.Wada ]
	$sql .= "WHERE A.CORP_ID = B.CORP_ID(+) AND A.KYOTEN_ID = B.KYOTEN_ID(+) AND ";
	$sql .= "A.CORP_ID = '$cid' AND A.KYOTEN_ID = '$kid' ";
	$sql .= "AND NVL( A.PUB_E_DATE, SYSDATE ) >= SYSDATE";
	// add 2012/02/16 Y.Matsukawa [
	if ($jkn != "") {
		$sql .= " AND $jkn ";
	}
	// add 2012/02/16 Y.Matsukawa ]
	$stmt   = null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;   //sqlExecute()エラー
	}
	$dba->getRecInto( $stmt,$retdata,OCI_ASSOC);
	if ( $retdata == "" ) {
		$dba->free($stmt);		// 2007/07/11 add Y.Matsukawa
		return 1;   //検索結果データなし
	}
	$dba->free($stmt);
	return	0;
}

// 拠点画像（複数）テーブルデータ取得
//function select_kyoten_img_tbl( &$dba , $cid , $kid , &$retdata , &$err_msg ) {	mod 2013/08/05 N.Wada
function select_kyoten_img_tbl( &$dba , $cid , $kid ,  &$retdata , &$err_msg , $immref=false ) {

	// add 2013/08/05 N.Wada [
	if ( $immref ) {
		$from = " FROM IM_KYOTEN_TBL A, IM_KYOTEN_IMG_TBL B ";
	} else {
		$from = " FROM KYOTEN_TBL A, KYOTEN_IMG_TBL B ";
	}
	// add 2013/08/05 N.Wada ]

	$sql = " SELECT B.IMG_NO "
		//.  " FROM KYOTEN_TBL A, "		mod 2013/08/05 N.Wada
		//.  " KYOTEN_IMG_TBL B "
		.  $from
		.  " WHERE A.CORP_ID = '$cid' "
		.  " AND A.KYOTEN_ID = '$kid' "
		.  " AND NVL(A.PUB_E_DATE, SYSDATE) >= SYSDATE "
		.  " AND A.CORP_ID = B.CORP_ID "
		.  " AND A.KYOTEN_ID = B.KYOTEN_ID "
		.  " AND B.GIF_DATA IS NOT NULL "
		.  " ORDER BY B.IMG_NO";
	$stmt	= null;
	if ( ! $dba->sqlExecute( $sql, $stmt ) ) {
		$dba->free($stmt);
		return 9;	//sqlExecute()エラー
	}
	$retdata = array();
	while ( $dba->getRecInto( $stmt , $data , OCI_ASSOC ) ) {
		$retdata[] = $data;
	}
	if ( count( $retdata ) <= 0 ) {
		$dba->free($stmt);
		return 1;	//検索結果データなし
	}
	$dba->free($stmt);
	return	0;
}
?>
