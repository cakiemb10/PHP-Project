<?php
/*========================================================*/
// ����CSV���åץ����ɡ�ʬ�������CSV�ե������ɹ�
//
// ��������
// 2012/05/31 H.osamoto	�ǡ�������CGI�򸵤˺���
/*========================================================*/

if ($DEBUG) print "hsearch_read_csv start<br>";
if ($DEBUG) print "data[$data]<br>";

	// ���åץ����ɥե�����OPEN
	$csv_fp = fopen($data , 'r');
	
	// �ɹ�
	$cnt = 0;
	$arr_data_line = array();
	$header_diff = false;
	while (!feof($csv_fp)){
		$cnt++;
		$line = mb_convert_encoding(zdc_convert_sjis_ibmex(fgets($csv_fp)), 'EUC-JP', 'SJIS');
		$arr_data_line[$cnt] = mb_ereg_replace("\t", "", $line);	// ���ֽ���
	}

	// �ե�����CLOSE
	fclose($csv_fp);

	// �����ζ���Ԥ����
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

	// ����ñ�����ʬ��
	$arr_data_line_chunk = array_chunk($arr_data_line, 10, true);
	unset($arr_data_line);
?>