<?php
// ------------------------------------------------------------
// XML のパース
//
// 2015/10/23 Y.Uesugi	新規作成
// ------------------------------------------------------------
function LoadXML(&$xml_str) {
	$xml_parser = xml_parser_create();
	if (!$xml_parser) return null;
	// CASE_FOLDING を抑制
	xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, false);
	// パースして平坦な配列に
	//$StrBufEuc = mb_convert_encoding(join($arr_str), "EUC-JP", "auto");
	//xml_parse_into_struct($xml_parser, $StrBufEuc, $arr_vals);
	xml_parse_into_struct($xml_parser, $xml_str, $arr_vals);
	// リソースの開放
	xml_parser_free($xml_parser);
	// エラー
	if (!$arr_vals) return null;
	if (count($arr_vals) == 0) return null;
	// ごみデータの除去
	foreach($arr_vals as $key => $node) {
		if ($node["type"] == "cdata") {
			unset($arr_vals[$key]);
		}
	}
	// 再配列

	//php5だと、xml_parse_into_structを実行した際に、UTF-8に戻してしまう様なので、再変換を追加
	mb_convert_variables("EUC-JP", "UTF-8", $arr_vals);

	$arr_vals = array_values($arr_vals);
	return $arr_vals;
}

//
// ノードを取得する
//
function GetXMLNode(&$arrXML, $key, $num = 0) {
	$count = 0;
	$flg = false;
	$sIdx = 0;
	$eIdx = 0;
	foreach ($arrXML as $idx => $node) {
		// Node の開始位置を探す
		if ($flg == false && $node["tag"] == $key && $node["type"] == "open") {
			if ($count == $num){
				$sIdx = $idx;
				$flg = true;
			} else {
				$count++;
			}
		}
		// Node の終了位置を探す
		if ($flg && $node["tag"] == $key && $node["type"] == "close") {
			$eIdx = $idx;
			break;
		}
	}
	if ($flg && $eIdx > 0) {
		// 開始位置から終了位置までを取得
		return array_slice($arrXML, $sIdx, $eIdx - $sIdx + 1);
	} else {
		return null;
	}
}

//
// リーフを取得する
//
function GetXMLVal(&$arrXML, $key) {
	foreach($arrXML as $idx => $node) {
		// $key が一致するリーフを探す
		if ($node["tag"] == $key && $node["type"] == "complete") {
			return $node["value"];
		}
	}
	return null;
}

//
// 属性を取得する
//
function GetXMLAttr(&$arrXML, $key, $attr) {
	foreach($arrXML as $idx => $node) {
		// $key が一致するタグを探す
		if ( $node["tag"] == $key ) {
			$arrAttr = $node["attributes"];
			return  $arrAttr[$attr];
		}
	}
	return null;
}

?>
