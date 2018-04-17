<?php
// ------------------------------------------------------------
// API��������
// store_search.cgi�θ�����ʬ
// 
// 2016/06/14 H.Yasunaga	��������
// 2016/06/15 H.Yasunaga	ȿ����������б�
// 2016/08/24 H.Yasunaga	��ɸ����[coord]�ѥ�᡼���ɲ�
// 2016/12/16 H.Yasunaga	��ɸ����[coord]�ѥ�᡼�����ͤ�"W"���ɲá��쥹�ݥ󥹤ΰ��ٷ��٤�����¬�ϷϤˤ���
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/define.inc");
	require_once(dirname(__FILE__) . "/function.inc");
	require_once(dirname(__FILE__) . "/ZdcCommonFunc.inc");
	require_once(dirname(__FILE__) . "/store_enc.inc");
	require_once(dirname(__FILE__) . "/jkn.inc");
	
	// Ź�޸���
	class StoreSearch{
		
		/*
		*	��ǽ	Ź�޸���
		*	����	$dba:oraDBAccess���饹���֥�������
		*			$CID:���ID
		*			$FILTER:�ʤ���߾��(ex. COL_01:xxx AND COL_02:FW:yyy)
		*			$REFLECTDATE:ȿ������(MAX10ʸ�� 2016061512)
		*			$COORD:��ɸ����(Z:�������ɸ M:Mapion��ɸ[�ǥե����] W:����¬�Ϸ�)
		*			$POS:�������ϰ���
		*			$CNT:�������
		*			&$REC_NUM:��̷��
		*			&$HIT_NUM:������̷��
		*			&$ARR_KYOTEN:�����������
		*	�����	define����Υ꥿���󥳡���
		*			00000  ���˸��礦�ǡ�������ʸ�³�ǡ����ʤ���
		*			00001  ���˸��礦�ǡ�������ʸ�³�ǡ��������
		*			11009  ���˸��礦�ǡ����ʤ�
		*			12009  ǧ�ڥ��顼
		*			17900  �ǡ����١��������������顼
		*			17002  �ǡ����١��������������顼
		*			17999  �ǡ����١��������������顼
		*			19100  ���ϥѥ�᡼�����顼(ɬ�ܹ���NULL)
		*			19200  ���ϥѥ�᡼�����顼(��ʸ���顼)
		*			19200  ���ϥѥ�᡼�����顼(�Ȥ߹�碌���顼)
		*/
		// mod start 2016/06/15 H.Yasunaga ȿ����������б� [
		// public static function Search($dba, $CID, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		// mod start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
		//public static function Search($dba, $CID, $FILTER, $REFLECTDATE, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		public static function Search($dba, $CID, $FILTER, $REFLECTDATE, $COORD, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		// mod end 2016/08/24 ]
		// mod end 2016/06/15 ]
			$DATUM = 'TOKYO';
			$PFLG = '1';
			$ENC = 'EUC-JP';
			$OUTF = 'XML';
			$FREWD = '';
			$SORT = '';
		
			/*==============================================*/
			// �ʤ���߾��
			/*==============================================*/
			$FILTER_sql = '';
			//$FILTER = f_dec_convert($FILTER);	// add 2014/12/03 H.Osamoto
			edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
			$log_frewd = f_dec_convert($FREWD);
			$log_frewd = mb_ereg_replace(' ', '_', $log_frewd);
			$log_frewd = mb_ereg_replace('��', '_', $log_frewd);
			$arr_log_jkn[53] = mb_strimwidth($log_frewd, 0, 128, '...');
			$log_jkn = implode(' ', $arr_log_jkn);
			
			// add start 2016/06/15 H.Yasunaga ȿ����������б� [
			// ȿ�������ιʤ���߾��
			if (empty($REFLECTDATE) != true) {
				if (empty($FILTER_sql) != true) {
					$FILTER_sql .= " AND ";
				}
				// ��Ƭ���פǴޤޤ�Ƥ��뤫
				//$FILTER_sql .= "instr(to_char(PUB_S_DATE, 'YYYYMMDDHH24'), '". $REFLECTDATE . "') = 1";
				$FILTER_sql .= " to_char(PUB_S_DATE, 'YYYYMMDDHH24') >= '" . $REFLECTDATE . "' ";
			}
			// add end 2016/06/15 ]
			
			/*==============================================*/
			// �����̾�ꥹ�ȼ���
			/*==============================================*/
			$arr_item = array();
			$sql  = " SELECT";
			$sql .= "    COL_NAME,ITEM_NAME,VAL_KBN";
			$sql .= " FROM";
			$sql .= "    KYOTEN_ITEM_TBL";
			$sql .= " WHERE"; 
			$sql .= "    CORP_ID = '".escapeOra($CID)."'";
			//$sql .= " AND LIST_KBN = 1";
			$sql .= " ORDER BY DISP_NUM";
			$stmt = null;
			if (!$dba->sqlExecute($sql, $stmt)) {
				$dba->free($stmt);
				//$dba->close();
				$status = DEF_RETCD_DERR3;
				return $status;
				/*
				$CgiOut->set_debug('DB����', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
				exit;
				*/
			}
			$arr_item = array();
			while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$arr_item[] = $data;
			}
			$dba->free($stmt);

			/*==============================================*/
			// ��ʬ���ܤ�̾�μ���
			/*==============================================*/
			$arr_kbn = array();
			//$arr_item_val[$item['COL_NAME']] = array();
			if (count($arr_item) > 0) {
				foreach ($arr_item as $item) {
					if ($item['VAL_KBN'] == 'L') {
						$sql_kbn  = " SELECT";
						$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
						$sql_kbn .= " FROM";
						$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
						$sql_kbn .= " WHERE";
						$sql_kbn .= "    CORP_ID = '".escapeOra($CID)."'";
						$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
						$sql_kbn .= " ORDER BY ITEM_VAL";
						if (!$dba->sqlExecute($sql_kbn, $stmt)) {
							$dba->free($stmt);
							//$dba->close();
							$status = DEF_RETCD_DERR3;
							return $status;
							/*
							$CgiOut->set_debug('DB����', __LINE__);
							$CgiOut->set_status($status, 0, 0);
							$CgiOut->err_output();
							put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
							exit;
							*/
						}
						$arr_kbn[$item['COL_NAME']] = array();
						while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
							$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = $data['ITEM_VAL_NAME'];
							$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
						}
						$dba->free($stmt);
					}
				}
			}

			/*==============================================*/
			// ������︡��
			/*==============================================*/
			$sql  = " SELECT";
			// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
			// mod start 2016/12/16 H.Yasunaga ��ɸ���̤�"W"�ɲ�
			//if ($COORD == DEF_COORD_ZENRIN) {
			if ($COORD == DEF_COORD_ZENRIN || $COORD == DEF_COORD_WORLD) {
			// mod end 2016/12/16 H.Yasunaga ]
			// �������ɸ
			// add end 2016/08/24 ]
				$sql .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID,to_char(UPD_DT,  'YYYY-MM-DD HH24:MI:SS') AS UPD_DT, to_char(PUB_S_DATE, 'YYYY-MM-DD HH24:MI:SS') AS PUB_S_DATE,";
			// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
			} else {
				// Mapion��ɸ
				// COL_194��Mapion���١�
				// COL_195��Mapion���١�
				$sql .= "    CORP_ID, KYOTEN_ID, to_number(COL_194) as LAT, to_number(COL_195) as LON, ICON_ID,to_char(UPD_DT,  'YYYY-MM-DD HH24:MI:SS') AS UPD_DT, to_char(PUB_S_DATE, 'YYYY-MM-DD HH24:MI:SS') AS PUB_S_DATE,";
			}
			// add end 2016/08/24 ]
			$sql .= " CASE";
			$sql .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
			$sql .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
			$sql .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
			$sql .= "         THEN '1'";
			$sql .= "         ELSE '0'";
			$sql .= " END AS BFLG ";
			if (count($arr_item) > 0) {
				foreach ($arr_item as $item) {
					$sql .= ", ".$item['COL_NAME'];
				}
			}
			$sql .= " FROM";
			$sql .= "    KYOTEN_TBL K";
			$sql .= " WHERE";
			$sql .= "    CORP_ID = '".escapeOra($CID)."'";
			$sql .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
			if ($FREWD != '') {
				$frewd_sql = array();
				$FREWD = f_dec_convert($FREWD);
				$FREWD = mb_ereg_replace('��',' ',$FREWD);
				$words = explode(' ', $FREWD);
				foreach ($words as $w) {
					if ($w != '') {
						$frewd_sql[] = "INSTR(FREE_SRCH, '" . fw_normalize($w) . "') <> 0";
					}
				}
				if (count($frewd_sql)) {
					$sql .= " AND (".implode(' AND ', $frewd_sql).")";
				}
			}
			if ($FILTER_sql != '') {
				$sql .= " AND ".$FILTER_sql;
			}
			$FILTER_sql = f_dec_convert($FILTER_sql);
			// �����ȥ�������
			$sql_order = '';
			if ($SORT != '') {
				$sql_order .= $SORT;
			}
			if ($SORT != '') {
				 $sql_order .= ',';
			}
			$sql_order .= 'KYOTEN_ID';
			$sql .= " ORDER BY ".$sql_order;
			$sql = "SELECT S.*, rownum rn FROM (".$sql.") s";

			// �ҥåȷ������
			$hit_num = 0;
			$stmt = null;
			$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql.")";
			if (!$dba->sqlExecute($sql_count, $stmt)) {
				$dba->free($stmt);
				//$dba->close();
				$status = DEF_RETCD_DERR3;
				return $status;
				/*
				$CgiOut->set_debug('DB����', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
				exit;
				*/
			}
			if ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
				$hit_num = $data['HITCNT'];
			}
			$dba->free($stmt);

			// �ǡ�������
			$rec_num = 0;
			$arr_kid = array();		// add 2013/03/11 Y.Matsukawa
			$arr_kyoten = array();
			if ($hit_num > 0) {
				$sql_data = " SELECT";
				$sql_data .= "       *";
				$sql_data .= " FROM (".$sql.")";
				$sql_data .= " where rn >= ".$POS;
				$to = $POS+$CNT-1;
				$sql_data .= " AND rn <= ".$to;
				$stmt = null;
				if (!$dba->sqlExecute($sql_data, $stmt)) {
					$dba->free($stmt);
					//$dba->close();
					$status = DEF_RETCD_DERR3;
					return $status;
					/*
					$CgiOut->set_debug('DB����', __LINE__);
					$CgiOut->set_status($status, 0, 0);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
					exit;
					*/
				}
				while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
					// mod start 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"����ξ�������¬�Ϸϰ��ٷ��٤��֤� [
					//if ($DATUM == DATUM_WGS84) {
					if ($COORD == DEF_COORD_WORLD) {
					// mod end 2016/12/16 H.Yasunaga ]
						// ¬�ϷϤ��Ѵ���TOKYO=>WGS84��
						$res = cnv_transDatum($data['LAT'], $data['LON'], TKY_TO_WGS84, $w_lat, $w_lon);
						if ($res) {
							$data['LAT'] = $w_lat;
							$data['LON'] = $w_lon;
						}
					}
					
					// ���ٷ���ɽ���Ѵ�
					// mod start 2016/08/24 H.Yasunaga Mapion��ɸ��NULL�ξ���LAT��LON����ˤ��� [
					//$data['LAT'] = cnv_dms2hour($data['LAT']);
					//$data['LON'] = cnv_dms2hour($data['LON']);
					if ($COORD == DEF_COORD_MAPION && empty($data['LAT']) && empty($data['LON'])) {
						$data['LAT'] = "";
						$data['LON'] = "";
					} else {
						$data['LAT'] = cnv_dms2hour($data['LAT']);
						$data['LON'] = cnv_dms2hour($data['LON']);
					}
					// mod end ]
					
					// ��ʬ���ܤ�̾�Τ򥻥å�
					if (count($arr_item) > 0) {
						foreach ($arr_item as $item) {
							if ($item['VAL_KBN'] == 'L') {
								$colnm = $item['COL_NAME'];
								if (isset($data[$colnm])) {
									$val = $data[$colnm];
									if ($val != '') {
										if ($arr_kbn[$colnm][$val] != '') {
											$data[$colnm.'_name'] = $arr_kbn[$colnm][$val];
										}
									}
								}
							}
						}
					}
					$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
					$arr_kyoten[] = $data;
				}
				$dba->free($stmt);
				$rec_num = count($arr_kyoten);
			}

			//$dba->close();

			if (!$rec_num) {
				// �����ǡ���̵��
				$status = DEF_RETCD_DNE;
				return $status;
				/*
				$CgiOut->set_debug('DB����', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
				exit;
				*/
			}
			if (($POS+$rec_num-1) < $hit_num) {
				// ��³�ǡ���ͭ��
				$status = DEF_RETCD_DEND;
			} else {
				// ��³�ǡ���̵��
				$status = DEF_RETCD_DE;
			}

			$HIT_NUM = $hit_num;
			$REC_NUM = $rec_num;
			$ARR_KYOTEN = $arr_kyoten;
			return $status;
			/*==============================================*/
			// ����(����)
			/*==============================================*/
			/*
			$CgiOut->set_status($status, $rec_num, $hit_num);
			$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);

			// ��������
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			*/
		}
	}
?>