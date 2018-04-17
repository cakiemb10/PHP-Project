<?php
/*========================================================*/
// 拠点CSVアップロード（分割処理）CSVファイル読込
//
// 更新履歴
// 2012/05/31 H.osamoto	データ管理CGIを元に作成
/*========================================================*/

if ($DEBUG) print "hsearch_read_csv start<br>";
if ($DEBUG) print "data[$data]<br>";

	// アップロードファイルOPEN
	$csv_fp = fopen($data , 'r');
	
	// 読込
	$cnt = 0;
	$arr_data_line = array();
	$header_diff = false;
	while (!feof($csv_fp)){
		$cnt++;
		$line = mb_convert_encoding(zdc_convert_sjis_ibmex(fgets($csv_fp)), 'EUC-JP', 'SJIS');
		$arr_data_line[$cnt] = mb_ereg_replace("\t", "", $line);	// タブ除去
	}

	// ファイルCLOSE
	fclose($csv_fp);

	// 末尾の空白行を除去
	if ($cnt) {
		for ($i=$cnt; $i>0; $i--) {
			if (!strlen($arr_data_line[$i])) {
				array_pop($arr_data_line);
			} else {
				break;
			}
		}
	}
	
	$all_csv_cnt = count($arr_data_line);

	// 処理単位毎に分割
	$arr_data_line_chunk = array_chunk($arr_data_line, 10, true);
	unset($arr_data_line);
?>
