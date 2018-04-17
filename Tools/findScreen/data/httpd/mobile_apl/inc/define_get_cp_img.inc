<?php
// ------------------------------------------------------------
// 企業画像定義をCGIから取得する
// 
// 変更履歴
// 2012/02/13 Y.Matsukawa	新規作成
// ------------------------------------------------------------
$D_CP_IMG = array();
if (isset($D_USE_CP_IMG) && $D_USE_CP_IMG) {
	$url = sprintf("%s?cid=%s&kbn=%s", $D_SSAPI["cp_img_inf"], $D_DATA_CID, 'M');
	$dat = ZdcHttpRead($url, 0, D_SOCKET_TIMEOUT);
	if(isset($dat)) {
		$status = explode("\t", $dat[0]);
		if(substr($status[0], 3) == "00000") {
			$cnt = $status[1];
			for($i = 0; $i < $cnt; $i++) {
				$rec = explode("\t", $dat[$i+1]);
				$D_CP_IMG[$i]["NO"]    = $rec[0];
				$D_CP_IMG[$i]["IMG"]   = sprintf("%s?cid=%s&kbn=%s&n=%s", $D_SSAPI["cp_img"],   $D_DATA_CID, 'M', $rec[0]);
				$D_CP_IMG[$i]["IMG_G"] = sprintf("%s?cid=%s&kbn=%s&n=%s", $D_SSAPI["cp_img_g"], $D_DATA_CID, 'M', $rec[0]);
				$D_CP_IMG[$i]["W"]     = $rec[2];
				$D_CP_IMG[$i]["H"]     = $rec[3];
				$D_CP_IMG[$i]["URL"]   = $rec[4];
			}
		}
	}
}
?>
