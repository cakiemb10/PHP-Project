<?PHP
/*========================================================*/
// ��������
// Ver2.00 2009/02/05 Y.Matsukawa	�ե꡼���������
// Ver2.01 2009/03/30 Y.Matsukawa	��®�������б��ۥե꡼����������򥯥���γ���
// Ver2.02 2009/11/07 Y.Matsukawa	�������ܳ�ĥ��50��200��
// Ver2.03 2009/11/24 Y.Matsukawa	���Զ�罤���۶�ʬ���ܥ����ɤ˿��Ͱʳ���Ȥ��ȹʤ���ߤ���ʤ�
// Ver2.04 2010/01/18 Y.Matsukawa	���Զ�罤���ۥե꡼��ɤ˥��ڡ������ޤޤ�Ƥ����硢Ⱦ�ѥ��ڡ������ߤΤޤޥ������Ϥ���Ƥ��ޤ����������ܶ��ڤ꤬�����ˤʤ�
// Ver2.05 2010/02/10 Y.Matsukawa	�������ϡ��ե꡼���128�Х��ȴݤ�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// Ver2.07 2011/12/02 H.Osamoto		������ӵ�ǽ�ɲ�(:DT:)
// Ver2.08 2012/01/31 H.Osamoto		������ӵ�ǽ������YYYYMMDDHH��YYYYMMDDHHMI��
// Ver2.09 2012/02/24 Y.Matsukawa	���Զ�罤�������ջ�����˳�̤�Ȥ���SQL���顼�ˤʤ�
// Ver2.10 2012/08/07 H.Osamoto		���Զ�罤���ۥ������ϻ��˥��ߤ��ޤޤ�Ƥ����Τǽ�����COL_01=2�ס�1))�פʤ�
// Ver2.11 2013/07/24 Y.Matsukawa	!=�б�
// 2013/10/31 Y.Matsukawa	����ID���������������
// 2014/05/13 Y.Matsukawa	���ʤǹʤ����
/*========================================================*/

/**
* �ؿ�̾ ��  edit_jkn
* ��  �� ��  �������ѥ�᡼����jkn�ˤ��Խ�����SQLʸ����ȥ������������������
* ��  �� ��  $jkn       - �������ѥ�᡼��
*            &$jkn_sql  - SQLʸ����         ���ֵ��Ѱ�����
*            &$jkn_arr  - ��������������    ���ֵ��Ѱ�����
* ����� ��  �ʤ�
**/
//function edit_jkn($jkn, &$jkn_sql, &$jkn_arr, $label="") {		Ver2.02 mod
//function edit_jkn($jkn, &$jkn_sql, &$jkn_arr, $label="", $rad="") {		mod 2014/05/13 Y.Matsukawa
function edit_jkn($jkn, &$jkn_sql, &$jkn_arr, $label="", $rad="", $cid="") {
	$jkn_sql = "";
	//$jkn_arr = array_fill(1, 53, "");		Ver2.02 mod
	$jkn_arr = array_fill(1, 204, "");
	if (strlen($rad)) $jkn_arr[54] = $rad;		// Ver2.02 add
	
	if ($jkn != "") {
		// ��ƥ�����Ⱦ�ѥ��ڡ����򥿥֤��ִ�
		$jkn = replace_blank_in_value($jkn, 0, "\t");
		// Ⱦ�ѥ��ڡ�����ʬ��
		$arr_buf = explode(" ", $jkn);

		$jkn_sql = "( ";
		foreach($arr_buf as $word) {
			// add 2011/07/05 Y.Nakajima [
			// HTML������<BR><B>�ˤ�����ƥ��ƥ�������Ƥ��ޤ��Τǡ������᤹
			//¾�˱ƶ���̵���Ȼפ���
			$word = mb_ereg_replace("&lt;", "<", $word);
			$word = mb_ereg_replace("&gt;", ">", $word);
			//$word = mb_ereg_replace("&quot;", "\"", $word);
			// add 2011/07/05 Y.Nakajima ]
			// ���֤�Ⱦ�ѥ��ڡ������᤹
			$word = str_replace("\t", " ", $word);
			//------------------------------------------------------------------
			// AND / OR
			//------------------------------------------------------------------
			if ($word == "AND" || $word == "OR" || $word == "and" || $word == "or") {
				$jkn_sql .= $word;
			//------------------------------------------------------------------
			// �ե꡼��ɡ���ʬ���ס˾��
			// ex. "COL_03:FW:'������'"
			//------------------------------------------------------------------
			} else if (strpos($word, ":FW:") !== false) {
				list($colnm, $fw, $val) = explode(":", $word);
				$val = mb_substr($val, 1, mb_strlen($val)-2);	// �������Ƚ���
				$val = trim($val);
				$val = mb_ereg_replace("��", " ", $val);		// ���ѥ��ڡ�����Ⱦ�ѥ��ڡ���
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
				// �������Ͻ硧NAME,ADDR,COL01��COL_50,FREE_SRCH,Ⱦ��,COL_51��COL_200
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
			// ���չ��ܾ��
			// ex. "COL_03:DT:LT:YYYYMMDDHHMI"
			// ptn�ʥѥ���������� LT:<, LTE:<=, GT:>, GTE:>=
			//------------------------------------------------------------------
			} else if (strpos($word, ":DT:") !== false) {
				list($colnm, $dt, $ptn, $date) = explode(":", $word);
				// add Ver2.09 2012/02/24 Y.Matsukawa [
				$p = strpos($colnm, "COL_");
				if ($p > 0) $jkn_sql .= substr($colnm, 0, $p);
				if ($p > 0) $colnm = substr($colnm, $p);
				// add Ver2.09 2012/02/24 Y.Matsukawa ]
				// ��������ब��null�פξ��ɬ��HIT����
				switch ($ptn) {
					case LT:		// ��ӱ黻�ҥѥ�����<
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '0') < to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '0') < to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '0') < '".$date."' ";
						}
						break;
					case LTE:		// ��ӱ黻�ҥѥ�����<=
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '0') <= to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '0') <= to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '0') <= '".$date."' ";
						}
						break;
					case GT:		// ��ӱ黻�ҥѥ�����>
						if ($date == 'SYSDATE' || $date == 'sysdate') {
							//	$jkn_sql .= "NVL( ".$colnm.", '9999999999') > to_char(SYSDATE,'yyyymmddhh24') ";		mod Ver2.08 H.osamoto
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') > to_char(SYSDATE,'yyyymmddhh24mi') ";
						} else {
							$jkn_sql .= "NVL( ".$colnm.", '999999999999') > '".$date."' ";
						}
						break;
					case GTE:		// ��ӱ黻�ҥѥ�����>=
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
				// �������Ͻ硧NAME,ADDR,COL01��COL_50,FREE_SRCH,Ⱦ��,COL_51��COL_200
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
			// ���ʥޥ����ǹʤ����
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
			// �԰��׾��
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
				// �������Ͻ硧NAME,ADDR,COL01��COL_50,FREE_SRCH,Ⱦ��,COL_51��COL_200
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
			// �������׾��
			// ex. "COL_01:'1'"
			//------------------------------------------------------------------
			} else {
				// add 2011/07/05 Y.Nakajima
				//��:�פ�ͭ�����̵�����ǡ�����ʬ��
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
					//�ѥ�᡼����ʣ��̵���Τǡ����Τޤޥѥ�᡼����SQL���������
					$jkn_sql .= $word;
					$colnm    = $word;
				}
				// add 2011/07/05 Y.Nakajima ]
				// Ver2.03 add ]
				// �������Ͻ硧NAME,ADDR,COL01��COL_50,FREE_SRCH,Ⱦ��,COL_51��COL_200
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
				//��:�פ�ͭ�����̵�����ǡ�����ʬ��
				if (isset($val) && $val != "") {
					//��:�פ�ͭ���
				// add 2011/07/05 Y.Nakajima ]
					//$jkn_arr[$idx] = $val;			Ver2.04 mod
					//$jkn_arr[$idx] = mb_ereg_replace(' ', '_', $val);		2012/08/07 H.Osamoto mod
					$jkn_arr[$idx] = jkn_exclude($val);
					$jkn_arr[$idx] = mb_strimwidth($jkn_arr[$idx], 0, 128, '...');		// Ver2.05 add
				// add 2011/07/05 Y.Nakajima [
				} else {
					//��:�פ�̵����
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
* �ؿ�̾ ��  replace_blank_in_value
* ��  �� ��  �������ѥ�᡼����jkn��ʸ��������ͻ�����ʬ�ʥ��󥰥륯�����ȤǰϤޤ줿��ƥ��ˤ���˴ޤޤ��
*            Ⱦ�ѥ��ڡ����򡢻���ʸ�����ִ����ޤ�
* ��  �� ��  $jkn       - �������ѥ�᡼��
*            $spos      - ���ϰ��֡ʥǥե����0��
*            $chg       - �ִ�ʸ���ʥǥե����\t��
* ����� ��  Ⱦ�ѥ��ڡ����ִ���θ������ѥ�᡼��ʸ����
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
* �ؿ�̾ ��  fw_normalize
* ��  �� ��  �ե꡼����������ʥ��饯��ؿ�func_normalize��Ʊ��������������å��������
* ��  �� ��  $str       - �ե꡼���ʸ�����EUC-JP��
* ����� ��  ��������Υե꡼���ʸ����
**/
function fw_normalize($str) {
	$str = mb_convert_kana( $str, "KVC");		// Ⱦ�ѥ��ʢ����ѥ��ʡ��Ҥ餬�ʢ����ѥ��ʡ�������ʸ����
	$str = mb_convert_kana( $str, "rn"  );		// ���ѱѻ���Ⱦ�ѱѻ������ѿ�����Ⱦ�ѿ���
	$str = strtoupper($str);					// �Ѿ�ʸ��������ʸ��
	$str = mb_ereg_replace( "��", "", $str );	// ���ѥ��ڡ�������
	$str = mb_ereg_replace( " ",  "", $str );	// Ⱦ�ѥ��ڡ�������
	$str = mb_ereg_replace( "����", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "��", "��", $str );
	$str = mb_ereg_replace( "-",  "��", $str );
	$str = mb_ereg_replace( "��",  "��", $str );
	$str = mb_ereg_replace( "��",  "/", $str );
	$str = mb_ereg_replace( "��",  "*", $str );
	$str = mb_ereg_replace( "%",  "��", $str );
	$str = mb_ereg_replace( "&",  "��", $str );
	$str = mb_ereg_replace( "\|",  "��", $str );
	$str = mb_ereg_replace( "#",  "��", $str );
	$str = mb_ereg_replace( "\+",  "��", $str );
	$str = mb_ereg_replace( "[�ʡ�\(\)\[\]��@'�ǡ�����]",  "", $str );
	return $str;
}

// Ver2.10 add
/**
* �ؿ�̾ ��  jkn_exclude
* ��  �� ��  �����������ϻ��Υ��ߤ����
* ��  �� ��  $str
* ����� ��  ����ʸ����������ʸ����
**/
function jkn_exclude($str) {

	$str = mb_ereg_replace(' ', '_', $str);		// Ⱦ�ѥ��ڡ������ִ�
	$str = preg_replace('/COL_[0-9]{2,3}?\=/', '', $str);		// ��COL_XX=�פ����
	$str = mb_ereg_replace( "[�ʡ�\(\)\[\]��@'�ǡ�����]",  "", $str );		// ���׵������
	return $str;
}

?>