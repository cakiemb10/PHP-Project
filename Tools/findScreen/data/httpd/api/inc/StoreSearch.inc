<?php
// ------------------------------------------------------------
// API検索処理
// store_search.cgiの検索部分
// 
// 2016/06/14 H.Yasunaga	新規作成
// 2016/06/15 H.Yasunaga	反映日時条件対応
// 2016/08/24 H.Yasunaga	座標種別[coord]パラメータ追加
// 2016/12/16 H.Yasunaga	座標種別[coord]パラメータの値に"W"を追加、レスポンスの緯度経度を世界測地系にする
// ------------------------------------------------------------
	require_once(dirname(__FILE__) . "/define.inc");
	require_once(dirname(__FILE__) . "/function.inc");
	require_once(dirname(__FILE__) . "/ZdcCommonFunc.inc");
	require_once(dirname(__FILE__) . "/store_enc.inc");
	require_once(dirname(__FILE__) . "/jkn.inc");
	
	// 店舗検索
	class StoreSearch{
		
		/*
		*	機能	店舗検索
		*	引数	$dba:oraDBAccessクラスオブジェクト
		*			$CID:企業ID
		*			$FILTER:絞り込み条件(ex. COL_01:xxx AND COL_02:FW:yyy)
		*			$REFLECTDATE:反映日時(MAX10文字 2016061512)
		*			$COORD:座標種別(Z:ゼンリン座標 M:Mapion座標[デフォルト] W:世界測地系)
		*			$POS:取得開始位置
		*			$CNT:取得件数
		*			&$REC_NUM:結果件数
		*			&$HIT_NUM:検索結果件数
		*			&$ARR_KYOTEN:検索結果配列
		*	戻り値	define定義のリターンコード
		*			00000  条件に見合うデータあり（後続データなし）
		*			00001  条件に見合うデータあり（後続データあり）
		*			11009  条件に見合うデータなし
		*			12009  認証エラー
		*			17900  データベースアクセスエラー
		*			17002  データベースアクセスエラー
		*			17999  データベースアクセスエラー
		*			19100  入力パラメータエラー(必須項目NULL)
		*			19200  入力パラメータエラー(構文エラー)
		*			19200  入力パラメータエラー(組み合わせエラー)
		*/
		// mod start 2016/06/15 H.Yasunaga 反映日時条件対応 [
		// public static function Search($dba, $CID, $FILTER, $POS, $CNT, &$REC_NUM, &$HIT_NUM, &$ARR_KYOTEN ) {
		// mod start 2016/08/24 H.Yasunaga 座標種別[coord]追加 [
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
			// 絞り込み条件
			/*==============================================*/
			$FILTER_sql = '';
			//$FILTER = f_dec_convert($FILTER);	// add 2014/12/03 H.Osamoto
			edit_jkn($FILTER, &$FILTER_sql, &$arr_log_jkn, 'K.');
			$log_frewd = f_dec_convert($FREWD);
			$log_frewd = mb_ereg_replace(' ', '_', $log_frewd);
			$log_frewd = mb_ereg_replace('　', '_', $log_frewd);
			$arr_log_jkn[53] = mb_strimwidth($log_frewd, 0, 128, '...');
			$log_jkn = implode(' ', $arr_log_jkn);
			
			// add start 2016/06/15 H.Yasunaga 反映日時条件対応 [
			// 反映日時の絞り込み条件
			if (empty($REFLECTDATE) != true) {
				if (empty($FILTER_sql) != true) {
					$FILTER_sql .= " AND ";
				}
				// 先頭一致で含まれているか
				//$FILTER_sql .= "instr(to_char(PUB_S_DATE, 'YYYYMMDDHH24'), '". $REFLECTDATE . "') = 1";
				$FILTER_sql .= " to_char(PUB_S_DATE, 'YYYYMMDDHH24') >= '" . $REFLECTDATE . "' ";
			}
			// add end 2016/06/15 ]
			
			/*==============================================*/
			// カラム名リスト取得
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
				$CgiOut->set_debug('DB検索', __LINE__);
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
			// 区分項目の名称取得
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
							$CgiOut->set_debug('DB検索', __LINE__);
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
			// 拠点条件検索
			/*==============================================*/
			$sql  = " SELECT";
			// add start 2016/08/24 H.Yasunaga 座標種別[coord]追加 [
			// mod start 2016/12/16 H.Yasunaga 座標種別に"W"追加
			//if ($COORD == DEF_COORD_ZENRIN) {
			if ($COORD == DEF_COORD_ZENRIN || $COORD == DEF_COORD_WORLD) {
			// mod end 2016/12/16 H.Yasunaga ]
			// ゼンリン座標
			// add end 2016/08/24 ]
				$sql .= "    CORP_ID, KYOTEN_ID, LAT, LON, ICON_ID,to_char(UPD_DT,  'YYYY-MM-DD HH24:MI:SS') AS UPD_DT, to_char(PUB_S_DATE, 'YYYY-MM-DD HH24:MI:SS') AS PUB_S_DATE,";
			// add start 2016/08/24 H.Yasunaga 座標種別[coord]追加 [
			} else {
				// Mapion座標
				// COL_194（Mapion緯度）
				// COL_195（Mapion経度）
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
				$FREWD = mb_ereg_replace('　',' ',$FREWD);
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
			// ソートオーダー
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

			// ヒット件数取得
			$hit_num = 0;
			$stmt = null;
			$sql_count = "SELECT COUNT(*) HITCNT FROM (".$sql.")";
			if (!$dba->sqlExecute($sql_count, $stmt)) {
				$dba->free($stmt);
				//$dba->close();
				$status = DEF_RETCD_DERR3;
				return $status;
				/*
				$CgiOut->set_debug('DB検索', __LINE__);
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

			// データ取得
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
					$CgiOut->set_debug('DB検索', __LINE__);
					$CgiOut->set_status($status, 0, 0);
					$CgiOut->err_output();
					put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
					exit;
					*/
				}
				while ($dba->getRecInto($stmt, $data, OCI_ASSOC)) {
					// mod start 2016/12/16 H.Yasunaga 座標種別[coord]が"W"指定の場合は世界測地系緯度経度を返す [
					//if ($DATUM == DATUM_WGS84) {
					if ($COORD == DEF_COORD_WORLD) {
					// mod end 2016/12/16 H.Yasunaga ]
						// 測地系の変換（TOKYO=>WGS84）
						$res = cnv_transDatum($data['LAT'], $data['LON'], TKY_TO_WGS84, $w_lat, $w_lon);
						if ($res) {
							$data['LAT'] = $w_lat;
							$data['LON'] = $w_lon;
						}
					}
					
					// 緯度経度表記変換
					// mod start 2016/08/24 H.Yasunaga Mapion座標がNULLの場合にLATとLONを空にする [
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
					
					// 区分項目の名称をセット
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
				// 該当データ無し
				$status = DEF_RETCD_DNE;
				return $status;
				/*
				$CgiOut->set_debug('DB検索', __LINE__);
				$CgiOut->set_status($status, 0, 0);
				$CgiOut->err_output();
				put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
				exit;
				*/
			}
			if (($POS+$rec_num-1) < $hit_num) {
				// 後続データ有り
				$status = DEF_RETCD_DEND;
			} else {
				// 後続データ無し
				$status = DEF_RETCD_DE;
			}

			$HIT_NUM = $hit_num;
			$REC_NUM = $rec_num;
			$ARR_KYOTEN = $arr_kyoten;
			return $status;
			/*==============================================*/
			// 出力(正常)
			/*==============================================*/
			/*
			$CgiOut->set_status($status, $rec_num, $hit_num);
			$CgiOut->output($CID, $ID, $PFLG, $arr_item, $arr_kyoten, $arr_item_val);

			// ログ出力
			put_log($CGICD.$status, D_LOG_CGIKEY, $OPTION_CD, $parms);
			*/
		}
	}
?>