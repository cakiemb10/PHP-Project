<?php
// ------------------------------------------------------------
// API��������
// store_nearsearch.cgi�θ�����ʬ
// 
// 2016/06/14 H.Yasunaga	��������
// 2016/06/15 H.Yasunaga	ȿ����������б�
// 2016/06/24 H.Yasunaga	������̤Υ����Ƚ��KYOTEN_ID�˽���
// 2016/08/24 H.Yasunaga	��ɸ����[coord]�ɲ�
// 2016/12/16 H.Yasunaga	��ɸ����[coord]�ѥ�᡼�����ͤ�"W"���ɲá��쥹�ݥ󥹤ΰ��ٷ��٤�����¬�ϷϤˤ���
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/define.inc");
	require_once(dirname(__FILE__) . "/function.inc");
	require_once(dirname(__FILE__) . "/ZdcCommonFunc.inc");
	require_once(dirname(__FILE__) . "/store_enc.inc");
	require_once(dirname(__FILE__) . "/jkn.inc");
	
	// �Ǵ��Ź�޸���
	class StoreNearSearch{
		/*
		*	��ǽ	�Ǵ��Ź����
		*	����	$dba:oraDBAccess���饹�Υ��֥�������
		*			$CID:���ID
		*			$LAT:�濴����
		*			$LON:�濴����
		*			$NELAT:����(����)����
		*			$NELON:����(����)����
		*			$SWLAT:����(����)����
		*			$SWLON:����(����)����
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
		// public static function Search($dba, $CID, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		// mod start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
		//public static function Search($dba, $CID, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $REFLECTDATE, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		public static function Search($dba, $CID, $LAT, $LON, $NELAT, $NELON, $SWLAT, $SWLON, $FILTER, $REFLECTDATE, $COORD, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		// mod end 2016/08/24 H.Yasunaga ]
		// mod end 2016/06/15 H.Yasunaga ]
			$DATUM = 'TOKYO';
			$PFLG = '1';
			$ENC = 'EUC-JP';
			$OUTF = 'XML';
			$EWDIST = '';
			$SNDIST = '';
			
			/*==============================================*/
			// �ʤ���߾��
			/*==============================================*/
			$FILTER_sql = '';
			edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
			$log_jkn = implode(' ', $arr_log_jkn);

			// add start 2016/06/15 H.Yasunaga ȿ����������б� [
			// ȿ�������ιʤ���߾��
			if (empty($REFLECTDATE) != true) {
				if (empty($FILTER_sql) != true) {
					$FILTER_sql .= " AND ";
				}
				// ����ǯ�������ʹߤ�
				//$FILTER_sql .= "instr(to_char(PUB_S_DATE, 'YYYYMMDDHH24'), '". $REFLECTDATE . "') = 1";
				$FILTER_sql .= " to_char(PUB_S_DATE, 'YYYYMMDDHH24') >= '" . $REFLECTDATE . "' ";
			}
			// add end 2016/06/15 ]

			/*==============================================*/
			// ��ɸɽ�������ڤ�¬�ϷϤ��Ѵ�
			/*==============================================*/
			$LAT_DEC = $LAT;
			$LON_DEC = $LON;
			$LAT_MS;
			$LON_MS;
			$res = cnv_ll2lldms($LAT, $LON, $DATUM, &$LAT_MS, &$LON_MS);
			if (!$res) {
				// ���ٷ�������
				$status = DEF_RETCD_PERR2;
				return $status;
				/*
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->set_debug('���ٷ���', __LINE__);
				$CgiOut->err_output();
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
				exit;
				*/
			}
			if ($NELAT != '' && $NELON != '') {
				$res = cnv_ll2lldms($NELAT, $NELON, $DATUM, &$NELAT, &$NELON);
				if (!$res) {
					// ���ٷ�������
					$status = DEF_RETCD_PERR2;
					return $status;
					/*
					$CgiOut->set_debug('���ٷ���', __LINE__);
					$CgiOut->set_status($status, 0, 0);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
					exit;
					*/
				}
			}
			if ($SWLAT != '' && $SWLON != '') {
				$res = cnv_ll2lldms($SWLAT, $SWLON, $DATUM, &$SWLAT, &$SWLON);
				if (!$res) {
					// ���ٷ�������
					$status = DEF_RETCD_PERR2;
					return $status;
					/*
					$CgiOut->set_debug('���ٷ���', __LINE__);
					$CgiOut->set_status($status, 0, 0);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
					exit;
					*/
				}
			}

			/*==============================================*/
			// �����̾�ꥹ�ȼ��� 
			/*==============================================*/
			/* ���������� */
			$sql  = " SELECT"; 
			$sql .= "    COL_NAME, VAL_KBN, ITEM_NAME";
			$sql .= " FROM";
			$sql .= "    KYOTEN_ITEM_TBL";
			$sql .= " WHERE";
			$sql .= "    CORP_ID = '" .escapeOra($CID) ."'";
			$sql .= " ORDER BY DISP_NUM";
			/* ������ȯ�� */
			$stmt = null;
			if (!$dba->sqlExecute($sql, $stmt)) {
				$dba->free($stmt);
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
			/* ��̥��å��ݻ� */
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
					/* ���������� */
					$sql_kbn  = " SELECT";
					$sql_kbn .= "    ITEM_VAL, ITEM_VAL_NAME";
					$sql_kbn .= " FROM";
					$sql_kbn .= "    KYOTEN_ITEM_VAL_TBL";
					$sql_kbn .= " WHERE";
					$sql_kbn .= " CORP_ID = '".escapeOra($CID)."'";
					$sql_kbn .= " AND COL_NAME = '".$item['COL_NAME']."'";
					$sql_kbn .= " ORDER BY ITEM_VAL";
					/* ������ȯ�� */
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
					/* ��̥��åȳ�Ǽ */
					$arr_kbn[$item['COL_NAME']] = array();
					while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
						$arr_kbn[$item['COL_NAME']][$data['ITEM_VAL']] = isset($data['ITEM_VAL_NAME']) ? $data['ITEM_VAL_NAME'] : "";
						$arr_item_val[$item['COL_NAME']][$data['ITEM_VAL']] = $data;
					}
					$dba->free($stmt);
				}
			}

			$arr_kid = array();		// add 2013/03/11 Y.Matsukawa

			/*==============================================*/
			// �Ǵ��������
			/*==============================================*/
			/* ���֥��������� */
			$sql_sub_near  = " SELECT";
			// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
			// mod start 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"�ɲ�
			//if ($COORD == DEF_COORD_ZENRIN) {
			if ($COORD == DEF_COORD_ZENRIN || $COORD == DEF_COORD_WORLD) {
			// mod end 2016/12/16 H.Yasunaga ]
			// add end 2016/08/24 ]
				// �������ɸ
				$sql_sub_near .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID, to_char(UPD_DT,  'YYYY-MM-DD HH24:MI:SS') AS UPD_DT, to_char(PUB_S_DATE, 'YYYY-MM-DD HH24:MI:SS') AS PUB_S_DATE";
				$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( LAT - $LAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
				$sql_sub_near .= " + POWER( ABS( LON - $LON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
			// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
			} else {
				// Mapion��ɸ
				// COL_194��Mapion���١�
				// COL_195��Mapion���١�
				$sql_sub_near .= "    CORP_ID, KYOTEN_ID, to_number(COL_194) as LAT, to_number(COL_195) as LON, ICON_ID, to_char(UPD_DT,  'YYYY-MM-DD HH24:MI:SS') AS UPD_DT, to_char(PUB_S_DATE, 'YYYY-MM-DD HH24:MI:SS') AS PUB_S_DATE";
				$sql_sub_near .= ", FLOOR( SQRT( POWER( ABS( to_number(COL_194) - $LAT_MS ) * (  9 / 300000 * 1000 ), 2 )";
				$sql_sub_near .= " + POWER( ABS(to_number(COL_195) - $LON_MS ) * ( 11 / 450000 * 1000 ), 2 ) ) ) as KYORI,";
			}
			// add end 2016/08/24 ]
			/*  new ɽ���ե饰ʬ */
			$sql_sub_near .= " CASE";
			$sql_sub_near .= "     WHEN DISP_NEW_S_DATE IS NULL AND DISP_NEW_E_DATE IS NULL THEN '0'";
			$sql_sub_near .= "     WHEN SYSDATE BETWEEN NVL(DISP_NEW_S_DATE, SYSDATE) AND ";
			$sql_sub_near .= "         NVL(DISP_NEW_E_DATE, SYSDATE)";
			$sql_sub_near .= "         THEN '1'";
			$sql_sub_near .= "         ELSE '0'";
			$sql_sub_near .= " END AS BFLG";
			if (count($arr_item) > 0) {
				foreach ($arr_item as $item) {
					$sql_sub_near .= ", ".$item['COL_NAME'];
				}
			}
			$sql_sub_near .= " FROM";
			$sql_sub_near .= "    KYOTEN_TBL K";
			$sql_sub_near .= " WHERE";
			$sql_sub_near .= "    CORP_ID = '".escapeOra($CID)."'";
			// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
			// mod start 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"���ɲ�
			//if ($COORD == DEF_COORD_ZENRIN) {
			if ($COORD == DEF_COORD_ZENRIN || $COORD == DEF_COORD_WORLD) {
			// mod end 2016/12/16 H.Yasunaga ]
			// add end 2016/08/24 ]
				// �������ɸ
				if ($SWLAT) {
					$sql_sub_near .= " AND LAT >= ".$SWLAT;
					$sql_sub_near .= " AND LAT <= ".$NELAT;
					$sql_sub_near .= " AND LON >= ".$SWLON;
					$sql_sub_near .= " AND LON <= ".$NELON;
				} else {
					$sql_sub_near .= "AND LAT >= (".$LAT_MS." - ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
					$sql_sub_near .= "AND LAT <= (".$LAT_MS." + ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
					$sql_sub_near .= "AND LON >= (".$LON_MS." - ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
					$sql_sub_near .= "AND LON <= (".$LON_MS." + ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
				}
			// add start 2016/08/24 H.Yasunaga ��ɸ����[coord]�ɲ� [
			} else {
				// Mapion��ɸ
				// COL_194��Mapion���١�
				// COL_195��Mapion���١�
				if ($SWLAT) {
					$sql_sub_near .= " AND to_number(COL_194) >= ".$SWLAT;
					$sql_sub_near .= " AND to_number(COL_194) <= ".$NELAT;
					$sql_sub_near .= " AND to_number(COL_195) >= ".$SWLON;
					$sql_sub_near .= " AND to_number(COL_195) <= ".$NELON;
				} else {
					$sql_sub_near .= "AND to_number(COL_194) >= (".$LAT_MS." - ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
					$sql_sub_near .= "AND to_number(COL_194) <= (".$LAT_MS." + ((300000 / (9 * 1000)) * ".$SNDIST.")) ";
					$sql_sub_near .= "AND to_number(COL_195) >= (".$LON_MS." - ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
					$sql_sub_near .= "AND to_number(COL_195) <= (".$LON_MS." + ((450000 / (11 * 1000)) * ".$EWDIST.")) ";
				}
			}
			// add end 2016/08/24 ]
			$sql_sub_near .= " AND NVL(PUB_E_DATE, sysdate+1) >= sysdate";
			if ($FILTER_sql != '') {
				$sql_sub_near .= " AND ".$FILTER_sql;
			}
			$FILTER_sql = f_dec_convert($FILTER_sql);
			// mod start 2016/06/24 �����Ƚ�����ID�� [
			//$sql_sub_near .= " order by KYORI, KYOTEN_ID, CORP_ID";
			$sql_sub_near .= " order by  KYOTEN_ID, CORP_ID";
			// mod end ]
			$sql_near = "SELECT S.*, ROWNUM RN FROM (".$sql_sub_near.") s";
			// �ҥåȷ������
			$hit_num = 0;
			$stmt = null;
			$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql_near.")";
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
			$arr_kyoten = array();
			if ($hit_num > 0) {
				$sql_data = "SELECT * FROM (".$sql_near.")";
				$sql_data .= " where rn >= ".$POS;
				$to = $POS+$CNT-1;
				$sql_data .= " and rn <= ".$to;
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
					// mod start 2016/12/16 H.Yasunaga ��ɸ����[coord]��"W"����ξ�������¬�Ϸϰ��ٷ��٤��֤�[
					//if ($DATUM == DEF_PRM_DATUM_WGS84) {
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
					$data['LAT'] = cnv_dms2hour($data['LAT']);
					$data['LON'] = cnv_dms2hour($data['LON']);
					/*
					// ��ʬ���ܤ�̾�Τ򥻥å�
					if (count($arr_item) > 0) {
						foreach ($arr_item as $item) {
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
					}*/
					$arr_kid[] = $data['KYOTEN_ID'];		// add 2013/03/11 Y.Matsukawa
					$arr_kyoten[] = $data;
				}
				$dba->free($stmt);
				$rec_num = count($arr_kyoten);
			}

			if (!$rec_num) {
				// �����ǡ���̵��
				$status = DEF_RETCD_DNE;
				return $status;
				/*
				$CgiOut->set_debug('DB����', __LINE__);
				$CgiOut->set_status($status, 0, $hit_num);
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
			// ����
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