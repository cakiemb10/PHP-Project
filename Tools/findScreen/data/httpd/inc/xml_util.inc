<?php
// ------------------------------------------------------------
// XML �Υѡ���
//
// 2016/10/19 Y.Matsukawa	����������p/inc����ܿ���
// ------------------------------------------------------------
function LoadXML(&$xml_str) {
	$xml_parser = xml_parser_create();
	if (!$xml_parser) return null;
	// CASE_FOLDING ������
	xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, false);
	// �ѡ�������ʿó�������
	//$StrBufEuc = mb_convert_encoding(join($arr_str), "EUC-JP", "auto");
	//xml_parse_into_struct($xml_parser, $StrBufEuc, $arr_vals);
	xml_parse_into_struct($xml_parser, $xml_str, $arr_vals);
	// �꥽�����γ���
	xml_parser_free($xml_parser);
	// ���顼
	if (!$arr_vals) return null;
	if (count($arr_vals) == 0) return null;
	// ���ߥǡ����ν���
	foreach($arr_vals as $key => $node) {
		if ($node["type"] == "cdata") {
			unset($arr_vals[$key]);
		}
	}
	// ������

	//php5���ȡ�xml_parse_into_struct��¹Ԥ����ݤˡ�UTF-8���ᤷ�Ƥ��ޤ��ͤʤΤǡ����Ѵ����ɲ�
	mb_convert_variables("EUC-JP", "UTF-8", $arr_vals);

	$arr_vals = array_values($arr_vals);
	return $arr_vals;
}

//
// �Ρ��ɤ��������
//
function GetXMLNode(&$arrXML, $key, $num = 0) {
	$count = 0;
	$flg = false;
	$sIdx = 0;
	$eIdx = 0;
	foreach ($arrXML as $idx => $node) {
		// Node �γ��ϰ��֤�õ��
		if ($flg == false && $node["tag"] == $key && $node["type"] == "open") {
			if ($count == $num){
				$sIdx = $idx;
				$flg = true;
			} else {
				$count++;
			}
		}
		// Node �ν�λ���֤�õ��
		if ($flg && $node["tag"] == $key && $node["type"] == "close") {
			$eIdx = $idx;
			break;
		}
	}
	if ($flg && $eIdx > 0) {
		// ���ϰ��֤��齪λ���֤ޤǤ����
		return array_slice($arrXML, $sIdx, $eIdx - $sIdx + 1);
	} else {
		return null;
	}
}

//
// �꡼�դ��������
//
function GetXMLVal(&$arrXML, $key) {
	foreach($arrXML as $idx => $node) {
		// $key �����פ���꡼�դ�õ��
		if ($node["tag"] == $key && $node["type"] == "complete") {
			return $node["value"];
		}
	}
	return null;
}

//
// °�����������
//
function GetXMLAttr(&$arrXML, $key, $attr) {
	foreach($arrXML as $idx => $node) {
		// $key �����פ��륿����õ��
		if ( $node["tag"] == $key ) {
			$arrAttr = $node["attributes"];
			return  $arrAttr[$attr];
		}
	}
	return null;
}

?>