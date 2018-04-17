<?PHP
/*========================================================*/
// 更新履歴
// Ver2.00 2009/02/05 Y.Matsukawa	フリーワード正規化
// Ver2.01 2009/03/30 Y.Matsukawa	【速度劣化対応】フリーワード正規化をクエリの外へ
// Ver2.02 2009/11/07 Y.Matsukawa	拠点項目拡張（50→200）
// Ver2.03 2009/11/24 Y.Matsukawa	【不具合修正】区分項目コードに数値以外を使うと絞り込みされない
// Ver2.04 2010/01/18 Y.Matsukawa	【不具合修正】フリーワードにスペースが含まれている場合、半角スペース混在のままログ出力されてしまい、ログ項目区切りが不正になる
// Ver2.05 2010/02/10 Y.Matsukawa	ログ出力：フリーワード128バイト丸め
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// Ver2.07 2011/12/02 H.Osamoto		日付比較機能追加(:DT:)
// Ver2.08 2012/01/31 H.Osamoto		日付比較機能修正（YYYYMMDDHH⇒YYYYMMDDHHMI）
// Ver2.09 2012/02/24 Y.Matsukawa	【不具合修正】日付指定時に括弧を使うとSQLエラーになる
// Ver2.10 2012/08/07 H.Osamoto		【不具合修正】ログ出力時にゴミが含まれていたので除外「COL_01=2」「1))」など
// Ver2.11 2013/07/24 Y.Matsukawa	!=対応
// 2013/10/31 Y.Matsukawa	拠点ID検索条件をログ出力
// 2014/05/13 Y.Matsukawa	商品で絞り込み
/*========================================================*/

/**
* 関数名 ：  edit_jkn
* 概  要 ：  検索条件パラメータ（jkn）を編集し、SQL文字列とログ出力用配列を生成
* 引  数 ：  $jkn       - 検索条件パラメータ
*            &$jkn_sql  - SQL文字列         （返却用引数）
*            &$jkn_arr  - ログ出力用配列    （返却用引数）
* 戻り値 ：  なし
**/
//function edit_jkn($jkn, &$jkn_sql, &$jkn_arr, $label="") {		Ver2.02 mod
//function edit_jkn($jkn, &$jkn_sql, &$jkn_arr, $label="", $rad="") {		mod 2014/05/13 Y.Matsukawa
function edit_jkn($jkn, &$jkn_sql, &$jkn_arr, $label="", $rad="", $cid="") {
	$jkn_sql = "";
	//$jkn_arr = array_fill(1, 53, "");		Ver2.02 mod
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
				$val = mb_substr($val, 1, mb_strlen($val)-2);	// クォート除去
				$val = trim($val);
				$val = mb_ereg_replace("　", " ", $val);		// 全角スペース→半角スペース
				$vals = explode(" ", $val);
				if (count($vals) > 0) {
					$jkn_fws = array();
					foreach ($vals as $v) {
						if (mb_strlen($v)) {
							//$jkn_fws[] = "INSTR(" . $label . $colnm . ", '" . $v . "') <> 0";
							//$jkn_fws[] = "INSTR(func_normalize(" . $label . $colnm . "), func_normalize('" . $v . "')) <> 0";		Ver2.01 del
							// Ver2.01 add [
							if($colnm == 'FREE_SRCH') $v = fw_normalize($v);
							$jkn_fws[] = "INSTR(" . $label . $colnm . ", '" . $v . "') <> 0";
							// Ver2.01 add ]
						}
					}
					if (count($jkn_fws)) {
						$jkn_sql .= "(";
						$jkn_sql .= implode(" and ", $jkn_fws);
						$jkn_sql .= ")";
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
						//$idx = intval(substr($colnm, 4, 2)) + 2;		Ver2.02 mod
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				//$jkn_arr[$idx] = $val;			Ver2.04 mod
				//$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $val);		2012/08/07 H.osamoto mod
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
				// add Ver2.09 2012/02/24 Y.Matsukawa [
				$p = strpos($colnm, "COL_");
				if ($p > 0) $jkn_sql .= substr($colnm, 0, $p);
				if ($p > 0) $colnm = substr($colnm, $p);
				// add Ver2.09 2012/02/24 Y.Matsukawa ]
				// 該当カラムが「null」の場合必ずHITする
				switch ($ptn) {
					case LT:		// 比較演算子パターン：<
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '0') < to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '0') < to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '0') < '".$date."' ";
						}
						break;
					case LTE:		// 比較演算子パターン：<=
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '0') <= to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '0') <= to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '0') <= '".$date."' ";
						}
						break;
					case GT:		// 比較演算子パターン：>
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '9999999999') > to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') > to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') > '".$date."' ";
						}
						break;
					case GTE:		// 比較演算子パターン：>=
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '9999999999') >= to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') >= to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							//$jkn_sql .= "NVL( ".$colnm.", '999999999999')) >= '".$date."' ";
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') >= '".$date."' ";
						}
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
						// del Ver2.09 2012/02/24 Y.Matsukawa [
						//						$p = strpos($colnm, "COL_");
						//						if ($p > 0) $colnm = substr($colnm, $p);
						// del Ver2.09 2012/02/24 Y.Matsukawa ]
						//$idx = intval(substr($colnm, 4, 2)) + 2;		Ver2.02 mod
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				//$jkn_arr[$idx] = $val;			Ver2.04 mod
				$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $ptn."_".$date);
				$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');		// Ver2.05 add
			// add Ver2.07 H.osamoto ]
			// add 2014/05/13 Y.Matsukawa
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
			// add Ver2.11 2013/07/24 Y.Matsukawa [
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
			// add Ver2.11 2013/07/24 Y.Matsukawa ]
			//------------------------------------------------------------------
			// 完全一致条件
			// ex. "COL_01:'1'"
			//------------------------------------------------------------------
			} else {
				// add 2011/07/05 Y.Nakajima
				//「:」が有る時、無い時で、処理分岐
				if (preg_match("/:/", $word, $matches)) {
					list($colnm, $val) = explode(":", $word);
					//$jkn_sql .= str_replace(":", "=", $word);		Ver2.03 del
				// Ver2.03 add [
					$val_trim = mb_ereg_replace("'|\(|\)", "", $val);
					if (strpos($word, ":".$val_trim) !== false) {
						$jkn_sql .= mb_ereg_replace(":".$val_trim, "='".$val_trim."'", $word);
					} else {
						$jkn_sql .= mb_ereg_replace(":", "=", $word);
					}
				// add 2011/07/05 Y.Nakajima [
				} else {
					//パラメータが複数無いので、そのままパラメータをSQL条件に入れる
					$jkn_sql .= $word;
					$colnm    = $word;
				}
				// add 2011/07/05 Y.Nakajima ]
				// Ver2.03 add ]
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
					// add 2013/10/31 Y.Matsukawa [
					case "KYOTEN_ID":
						$idx = 205;
						break;
					// add 2013/10/31 Y.Matsukawa ]
					default:
						$p = strpos($colnm, "COL_");
						if ($p > 0) $colnm = substr($colnm, $p);
						//$idx = intval(substr($colnm, 4, 2)) + 2;		Ver2.02 mod
						$idx = intval(substr($colnm, 4));
						if ($idx <= 50) $idx += 2; else $idx += 4;
				}
				// add 2011/07/05 Y.Nakajima [
				//「:」が有る時、無い時で、処理分岐
				if (isset($val) && $val != "") {
					//「:」が有る時
				// add 2011/07/05 Y.Nakajima ]
					//$jkn_arr[$idx] = $val;			Ver2.04 mod
					//$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $val);		2012/08/07 H.Osamoto mod
					$jkn_arr[$idx] = jkn_exclude($val);
					$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');		// Ver2.05 add
				// add 2011/07/05 Y.Nakajima [
				} else {
					//「:」が無い時
					//	$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $word);		2012/08/07 H.Osamoto mod
					$jkn_arr[$idx] = jkn_exclude($word);
					$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');		// Ver2.05 add
				}				// add 2011/07/05 Y.Nakajima ]
			}
			$jkn_sql .= " ";
		}
		$jkn_sql .= ")";
	}
}

// 2007/05/31 add Y.Matsukawa
/**
* 関数名 ：  replace_blank_in_value
* 概  要 ：  検索条件パラメータ（jkn）文字列中の値指定部分（シングルクォートで囲まれたリテラル）の中に含まれる
*            半角スペースを、指定文字に置換します
* 引  数 ：  $jkn       - 検索条件パラメータ
*            $spos      - 開始位置（デフォルト0）
*            $chg       - 置換文字（デフォルト\t）
* 戻り値 ：  半角スペース置換後の検索条件パラメータ文字列
**/
function replace_blank_in_value($jkn, $spos=0, $chg="\t") {
	$quot_st = strpos($jkn, "'", $spos);
	if ($quot_st === false) return $jkn;
	$quot_ed = strpos($jkn, "'", $quot_st+1);
	if ($quot_ed === false) return $jkn;
	
	$h = substr($jkn, 0, $quot_st);
	$b = substr($jkn, $quot_st, $quot_ed - $quot_st + 1);
	$t = substr($jkn, $quot_ed + 1);
	$jkn = $h . str_replace(" ", $chg, $b) . $t;
	
	return replace_blank_in_value($jkn, $quot_ed + 1, $chg);
}

// Ver2.01 add
/**
* 関数名 ：  fw_normalize
* 概  要 ：  フリーワード正規化（オラクル関数func_normalizeと同一の正規化ロジックを実装）
* 引  数 ：  $str       - フリーワード文字列（EUC-JP）
* 戻り値 ：  正規化後のフリーワード文字列
**/
function fw_normalize($str) {
	$str = mb_convert_kana( $str, "KVC");		// 半角カナ→全角カナ、ひらがな→全角カナ、濁音を１文字に
	$str = mb_convert_kana( $str, "rn"  );		// 全角英字→半角英字、全角数字→半角数字
	$str = strtoupper($str);					// 英小文字→英大文字
	$str = mb_ereg_replace( "　", "", $str );	// 全角スペース除去
	$str = mb_ereg_replace( " ",  "", $str );	// 半角スペース除去
	$str = mb_ereg_replace( "ウ゛", "ヴ", $str );
	$str = mb_ereg_replace( "ァ", "ア", $str );
	$str = mb_ereg_replace( "ィ", "イ", $str );
	$str = mb_ereg_replace( "ゥ", "ウ", $str );
	$str = mb_ereg_replace( "ェ", "エ", $str );
	$str = mb_ereg_replace( "ォ", "オ", $str );
	$str = mb_ereg_replace( "ッ", "ツ", $str );
	$str = mb_ereg_replace( "ャ", "ヤ", $str );
	$str = mb_ereg_replace( "ュ", "ユ", $str );
	$str = mb_ereg_replace( "ョ", "ヨ", $str );
	$str = mb_ereg_replace( "ヮ", "ワ", $str );
	$str = mb_ereg_replace( "ヵ", "カ", $str );
	$str = mb_ereg_replace( "ヶ", "ケ", $str );
	$str = mb_ereg_replace( "ー", "−", $str );
	$str = mb_ereg_replace( "-",  "−", $str );
	$str = mb_ereg_replace( "ﾞ",  "゛", $str );
	$str = mb_ereg_replace( "／",  "/", $str );
	$str = mb_ereg_replace( "＊",  "*", $str );
	$str = mb_ereg_replace( "%",  "％", $str );
	$str = mb_ereg_replace( "&",  "＆", $str );
	$str = mb_ereg_replace( "\|",  "｜", $str );
	$str = mb_ereg_replace( "#",  "＃", $str );
	$str = mb_ereg_replace( "\+",  "＋", $str );
	$str = mb_ereg_replace( "[（）\(\)\[\]＠@'’・･〜]",  "", $str );
	return $str;
}

// Ver2.10 add
/**
* 関数名 ：  jkn_exclude
* 概  要 ：  下記ログ出力時のゴミを除外
* 引  数 ：  $str
* 戻り値 ：  不要文字列除外後の文字列
**/
function jkn_exclude($str) {

	$str = mb_ereg_replace(' ', '_', $str);		// 半角スペースを置換
	$str = preg_replace('/COL_[0-9]{2,3}?\=/', '', $str);		// 「COL_XX=」を除外
	$str = mb_ereg_replace( "[（）\(\)\[\]＠@'’・･〜]",  "", $str );		// 不要記号除外
	return $str;
}

?>
