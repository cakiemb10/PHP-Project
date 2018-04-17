<?PHP
/*========================================================*/
// 更新履歴
// 2015/02/10 F.Yokoi		edit_jknから新規作成
// 2015/03/23 F.Yokoi		リアルタイムデータでの絞り込み有無を確認するcheck_jkn_rd()を追加及び、jkn.incの修正内容の反映
/*========================================================*/

/**
* 関数名 ：  edit_jkn_rd
* 概  要 ：  検索条件パラメータ（jkn）を編集し、SQL文字列とログ出力用配列を生成
* 引  数 ：  $jkn       - 検索条件パラメータ
*            &$jkn_sql  - SQL文字列         （返却用引数）
*            &$jkn_arr  - ログ出力用配列    （返却用引数）
* 戻り値 ：  なし
**/
function edit_jkn_rd($jkn, &$jkn_sql, &$jkn_arr, $label="", $rad="", $cid="") {
	$jkn_sql = "";
	$jkn_arr = array_fill(1, 204, "");
	if (strlen($rad)) $jkn_arr[54] = $rad;		// Ver2.02 add
	
	if ($jkn != "") {
		// リテラル中の半角スペースをタブに置換
		$jkn = replace_blank_in_value($jkn, 0, "\t");
		// 半角スペースで分割
		$arr_buf = explode(" ", $jkn);

		$jkn_sql = "( ";
		foreach($arr_buf as $word) {
			// add 2011/07/05 Y.Nakajima [
			// HTMLタグ（<BR><B>）がエンティティ化されてしまうので、元に戻す
			//他に影響は無いと思うが
			$word = mb_ereg_replace("&lt;", "<", $word);
			$word = mb_ereg_replace("&gt;", ">", $word);
			$word = mb_ereg_replace("&amp;", "&", $word);	// add 2015/03/23 F.Yokoi
			//$word = mb_ereg_replace("&quot;", "\"", $word);
			// add 2011/07/05 Y.Nakajima ]
			// タブを半角スペースに戻す
			$word = str_replace("\t", " ", $word);
			//------------------------------------------------------------------
			// AND / OR
			//------------------------------------------------------------------
			if ($word == "AND" || $word == "OR" || $word == "and" || $word == "or") {
				$jkn_sql .= $word;
			//------------------------------------------------------------------
			// フリーワード（部分一致）条件
			// ex. "COL_03:FW:'あああ'"
			//------------------------------------------------------------------
			} else if (strpos($word, ":FW:") !== false) {
				list($colnm, $fw, $val) = explode(":", $word);
				//$val = mb_substr($val, 1, mb_strlen($val)-2);	// クォート除去 del 2015/03/24 F.Yokoi
				// add 2015/03/23 F.Yokoi [
				$prefix = ''; $suffix = '';
				$p = strpos($colnm, "COL_");
				if ($p === false) $p = strpos($colnm, "NAME");
				if ($p === false) $p = strpos($colnm, "ADDR");
				if ($p === false) $p = strpos($colnm, "FREE_SRCH");
				if ($p > 0) {
					$prefix = substr($colnm, 0, $p);
					$colnm = substr($colnm, $p);
				}
				$p1 = strpos($val, "'");
				if ($p1 !== false) {
					$val = substr($val, $p1+1);
					$p2 = strrpos($val, "'");
					if ($p2 > 0) {
						$suffix = substr($val, $p2+1);
						$val = substr($val, 0, $p2);
					}
				}
				// add 2015/03/23 F.Yokoi ]
				$val = trim($val);
				$val = mb_ereg_replace("　", " ", $val);		// 全角スペース→半角スペース
				$val = mb_ereg_replace("'", "", $val);		// シングルクォーテーション除去		add 2015/03/23 F.Yokoi
				$vals = explode(" ", $val);
				if (count($vals) > 0) {
					$jkn_fws = array();
					foreach ($vals as $v) {
						if (mb_strlen($v)) {
							if($colnm == 'FREE_SRCH') $v = fw_normalize($v);
							$jkn_fws[] = "INSTR(" . $label . $colnm . ", '" . $v . "') <> 0";
						}
					}
					if (count($jkn_fws)) {
						$jkn_sql .= $prefix;		// add 2015/03/23 F.Yokoi
						$jkn_sql .= "(";
						$jkn_sql .= implode(" and ", $jkn_fws);
						$jkn_sql .= ")";
						$jkn_sql .= $suffix;		// add 2015/03/23 F.Yokoi
					}
				}
				// ログ出力順：NAME,ADDR,COL01〜COL_50,FREE_SRCH,半径,COL_51〜COL_200
				switch ($colnm) {
					case "NAME":
						$idx = 1;
						break;
					case "ADDR":
						$idx = 2;
						break;
					case "FREE_SRCH":
						$idx = 53;
						break;
					default:
						$p = strpos($colnm, "COL_");
						if ($p > 0) $colnm = substr($colnm, $p);
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				$jkn_arr[$idx] = jkn_exclude($val);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');		// Ver2.05 add
			// add Ver2.07 H.osamoto [
			//------------------------------------------------------------------
			// 日付項目条件
			// ex. "COL_03:DT:LT:YYYYMMDDHHMI"
			// ptn（パターン）説明 LT:<, LTE:<=, GT:>, GTE:>=
			//------------------------------------------------------------------
			} else if (strpos($word, ":DT:") !== false) {
				list($colnm, $dt, $ptn, $date) = explode(":", $word);
				$p = strpos($colnm, "COL_");
				if ($p > 0) $jkn_sql .= substr($colnm, 0, $p);
				if ($p > 0) $colnm = substr($colnm, $p);
				switch ($ptn) {
					case LT:		// 比較演算子パターン：<
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							$jkn_sql .= "NVL( ".$colnm.", '0') < to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '0') < '".$date."' ";
						}
						break;
					case LTE:		// 比較演算子パターン：<=
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							$jkn_sql .= "NVL( ".$colnm.", '0') <= to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '0') <= '".$date."' ";
						}
						break;
					case GT:		// 比較演算子パターン：>
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') > to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') > '".$date."' ";
						}
						break;
					case GTE:		// 比較演算子パターン：>=
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') >= to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') >= '".$date."' ";
						}
						break;
					default:
				}
				// ")"がある時は追加する
				$p = strpos($date, ")");
				if ($p > 0) {
					$jkn_sql .= substr($date, $p);
				}

				// ログ出力順：NAME,ADDR,COL01〜COL_50,FREE_SRCH,半径,COL_51〜COL_200
				switch ($colnm) {
					case "NAME":
						$idx = 1;
						break;
					case "ADDR":
						$idx = 2;
						break;
					case "FREE_SRCH":
						$idx = 53;
						break;
					default:
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $ptn."_".$date);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
			//------------------------------------------------------------------
			// 大小比較条件
			// ex. "COL_03:COMP:LT:1000"
			// ptn（パターン）説明 LT:<, LTE:<=, GT:>, GTE:>=
			//------------------------------------------------------------------
			} else if (strpos($word, ":COMP:") !== false) {
				list($colnm, $t, $ptn, $val) = explode(":", $word);
				$prefix = ''; $suffix = '';
				$p = strpos($colnm, "COL_");
				if ($p > 0) {
					$prefix = substr($colnm, 0, $p);
					$colnm = substr($colnm, $p);
				}
				$p = strpos($val, ")");
				if ($p > 0) {
					$suffix = substr($val, $p);
					$val = substr($val, 0, $p);
				}
				switch ($ptn) {
					case LT:
						$jkn_sql .= $prefix.$colnm." <  '".escapeOra($val)."' ".$suffix;
						break;
					case LTE:
						$jkn_sql .= $prefix.$colnm." <= '".escapeOra($val)."' ".$suffix;
						break;
					case GT:
						$jkn_sql .= $prefix.$colnm." >  '".escapeOra($val)."' ".$suffix;
						break;
					case GTE:
						$jkn_sql .= $prefix.$colnm." >= '".escapeOra($val)."' ".$suffix;
						break;
					default:
				}
				// ログ出力順：NAME,ADDR,COL01〜COL_50,FREE_SRCH,半径,COL_51〜COL_200
				switch ($colnm) {
					case "NAME":
						$idx = 1;
						break;
					case "ADDR":
						$idx = 2;
						break;
					case "FREE_SRCH":
						$idx = 53;
						break;
					default:
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $ptn."_".$val);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
			//------------------------------------------------------------------
			// 数値の大小比較条件
			// ex. "COL_03:NUMB:LT:1000"
			// ptn（パターン）説明 LT:<, LTE:<=, GT:>, GTE:>=
			//------------------------------------------------------------------
			} else if (strpos($word, ":NUMB:") !== false) {
				list($colnm, $t, $ptn, $val) = explode(":", $word);
				$prefix = ''; $suffix = '';
				$p = strpos($colnm, "COL_");
				if ($p > 0) {
					$prefix = substr($colnm, 0, $p);
					$colnm = substr($colnm, $p);
				}
				$p = strpos($val, ")");
				if ($p > 0) {
					$suffix = substr($val, $p);
					$val = substr($val, 0, $p);
				}
				switch ($ptn) {
					case LT:
						$jkn_sql .= $prefix."to_number(".$colnm.") <  ".escapeOra($val)." ".$suffix;
						break;
					case LTE:
						$jkn_sql .= $prefix."to_number(".$colnm.") <= ".escapeOra($val)." ".$suffix;
						break;
					case GT:
						$jkn_sql .= $prefix."to_number(".$colnm.") >  ".escapeOra($val)." ".$suffix;
						break;
					case GTE:
						$jkn_sql .= $prefix."to_number(".$colnm.") >= ".escapeOra($val)." ".$suffix;
						break;
					default:
				}
				// ログ出力順：NAME,ADDR,COL01〜COL_50,FREE_SRCH,半径,COL_51〜COL_200
				switch ($colnm) {
					case "NAME":
						$idx = 1;
						break;
					case "ADDR":
						$idx = 2;
						break;
					case "FREE_SRCH":
						$idx = 53;
						break;
					default:
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $ptn."_".$val);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
			//------------------------------------------------------------------
			// 商品マスタで絞り込み
			//------------------------------------------------------------------
			} else if (strpos($word, "PRD_ID:") !== false) {
				list($colnm, $val) = explode(":", $word);
				$val = mb_ereg_replace("'|\(|\)", "", $val);
				$tmp = $label."KYOTEN_ID in (";
				$tmp .= "select KYOTEN_ID from KYOTEN_PRD_TBL";
				$tmp .= " where CORP_ID = '$cid'";
				$tmp .= " and PRD_ID = '$val')";
				$jkn_sql .= mb_ereg_replace("PRD_ID:$val", $tmp, $word);
				
				$idx = 206;
				$jkn_arr[$idx] = jkn_exclude($val);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
			//------------------------------------------------------------------
			// リアルタイムデータ項目比較条件
			// ex. RD:2_1:A
			//     RD:2_1:LT:1234
			// ptn（パターン）説明 項目無し:完全一致, LT:<, LTE:<=, GT:>, GTE:>=
			//------------------------------------------------------------------
			} else if (strpos($word, "RD:") !== false) {
				$p = strpos($word, "RD:");
				// "("がある時は追加する
				if ($p > 0) $jkn_sql .= substr($word, 0, $p);

				list($rd_flg, $colnm, $ptn, $value) = explode(":", $word);
				$number = mb_ereg_replace("\(|\)", '', $value);
				// 該当カラムが「null」の場合HITしない
				switch ($ptn) {
					case LT:		// 比較演算子パターン：<
						$jkn_sql .= " to_number(NVL(RT".$colnm.".RDATA, '')) < to_number('".$number."') ";
						break;
					case LTE:		// 比較演算子パターン：<=
						$jkn_sql .= " to_number(NVL(RT".$colnm.".RDATA, '')) <= to_number('".$number."') ";
						break;
					case GT:		// 比較演算子パターン：>
						$jkn_sql .= " to_number(NVL(RT".$colnm.".RDATA, '')) > to_number('".$number."') ";
						break;
					case GTE:		// 比較演算子パターン：>=
						$jkn_sql .= " to_number(NVL(RT".$colnm.".RDATA, '')) >= to_number('".$number."') ";
						break;
					default:
						$jkn_sql .= " NVL(RT".$colnm.".RDATA, '') = '".$ptn."' ";
						$ptn = "";
						break;
				}

				// ")"がある時は追加する
				if ($value != "") {
					$p = strpos($value, ")");
					if ($p > 0) {
						$jkn_sql .= substr($value, $p);
					}
				}
				else {
					$p = strpos($ptn, ")");
					if ($p > 0) {
						$jkn_sql .= substr($ptn, $p);
					}
				}

				// ログ出力順は無し
			//------------------------------------------------------------------
			// 不一致条件
			// ex. "COL_03!:001"
			//------------------------------------------------------------------
			} else if (strpos($word, "!:") !== false) {
				list($colnm, $val) = explode("!:", $word);
				$val_trim = mb_ereg_replace("'|\(|\)", "", $val);
				if (strpos($word, "!:".$val_trim) !== false) {
					$jkn_sql .= mb_ereg_replace("!:".$val_trim, "!='".$val_trim."'", $word);
				} else {
					$jkn_sql .= mb_ereg_replace("!:", "!=", $word);
				}
				// ログ出力順：NAME,ADDR,COL01〜COL_50,FREE_SRCH,半径,COL_51〜COL_200
				switch ($colnm) {
					case "NAME":
						$idx = 1;
						break;
					case "ADDR":
						$idx = 2;
						break;
					case "FREE_SRCH":
						$idx = 53;
						break;
					default:
						$p = strpos($colnm, "COL_");
						if ($p > 0) $colnm = substr($colnm, $p);
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				$jkn_arr[$idx] = 'NOT:'.jkn_exclude($val_trim);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
			//------------------------------------------------------------------
			// 完全一致条件
			// ex. "COL_01:'1'"
			//------------------------------------------------------------------
			} else {
				//「:」が有る時、無い時で、処理分岐
				if (preg_match("/:/", $word, $matches)) {
					list($colnm, $val) = explode(":", $word);
					$val_trim = mb_ereg_replace("'|\(|\)", "", $val);
					if (strpos($word, ":".$val_trim) !== false) {
						$jkn_sql .= mb_ereg_replace(":".$val_trim, "='".$val_trim."'", $word);
					} else {
						$jkn_sql .= mb_ereg_replace(":", "=", $word);
					}
				} else {
					//パラメータが複数無いので、そのままパラメータをSQL条件に入れる
					$jkn_sql .= $word;
					$colnm    = $word;
				}
				// ログ出力順：NAME,ADDR,COL01〜COL_50,FREE_SRCH,半径,COL_51〜COL_200
				switch ($colnm) {
					case "NAME":
						$idx = 1;
						break;
					case "ADDR":
						$idx = 2;
						break;
					case "FREE_SRCH":
						$idx = 53;
						break;
					case "KYOTEN_ID":
						$idx = 205;
						break;
					default:
						$p = strpos($colnm, "COL_");
						if ($p > 0) $colnm = substr($colnm, $p);
						//$idx = intval(substr($colnm, 4, 2)) + 2;		Ver2.02 mod
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				if (isset($val) && $val != "") {
					$jkn_arr[$idx] = jkn_exclude($val);
					$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
				} else {
					$jkn_arr[$idx] = jkn_exclude($word);
					$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');
				}				// add 2011/07/05 Y.Nakajima ]
			}
			$jkn_sql .= " ";
		}
		$jkn_sql .= ")";
	}
}

/**
* 関数名 ：  check_jkn_rd
* 概  要 ：  検索条件パラメータ（jkn）をチェックして、リアルタイムデータでの絞り込みが含まれているか確認する
* 引  数 ：  $jkn       - 検索条件パラメータ
* 戻り値 ：  1:絞込み有り、0:絞込み無し
**/
function check_jkn_rd($jkn) {
	$rd_flg = 0;
	if ($jkn != "") {
		// リテラル中の半角スペースをタブに置換
		$jkn = replace_blank_in_value($jkn, 0, "\t");
		// 半角スペースで分割
		$arr_buf = explode(" ", $jkn);

		foreach($arr_buf as $word) {
			if (strpos($word, "RD:") !== false) {
				$rd_flg = 1;
			}
		}
	}

	return $rd_flg;
}

?>
