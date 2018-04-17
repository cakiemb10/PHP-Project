<?php
/*========================================================*/
// 更新履歴
// 2013/03/4 H.Iijima 新規作成
// 2013/04/5 H.Iijima テキストのバインド数を最大値に設定（spif_p_rd_data_updt）
// 2015/05/29 F.Yokoi テーブルリフレッシュ用プロシージャ追加（spif_p_rd_group_updt,spif_p_rd_data_updt）
/*========================================================*/
/* -----------------------------------------------------------------*/
//
//  企業テーブル - プロシージャ - インタフェース 
//
/* -----------------------------------------------------------------*/
function SpifPEmapCorpUpdt(&$dba, $i_kbn, $i_userid, &$arr_emap_corp, &$o_rtncd){
		$spstr = "begin " 
				. "P_EMAP_CORP_UPDT( " 
				. ":i_kbn, :i_uid, :i_corp_id, :i_passwd, :i_corp_name, "
				. ":i_cname_kana,  :i_addr, :i_post, :i_tel, :i_busyo,  "
				. ":i_tanto, :i_tanto_kana, :i_mail, :i_s_date, :i_e_date, "
				. ":i_servname, :i_agencyid, :i_emap_kbn, :i_m_emap_kbn, "
				. ":i_max_kyoten_cnt, :i_userid, :i_other_maddr, :i_front_login_dt, "
				. ":i_front_login_cnt, :i_map_login_dt, :i_map_login_cnt, "
				. ":i_end_flg, :o_end_dt, :o_ins_dt, :o_upd_dt, :o_rtncd"
				. "); "
				. "end;";
		$stmt = OCIParse($dba->conn, $spstr);
		if (!$stmt) {
			return false;
		}
		if (!OCIBindByName($stmt, ':i_kbn', $i_kbn, 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_uid', $i_userid, 5)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_corp_id', $arr_emap_corp['CORP_ID'], 15)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_passwd', $arr_emap_corp['PASSWD'], 10)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_corp_name', $arr_emap_corp['CORP_NAME'], 128)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_cname_kana', $arr_emap_corp['CNAME_KANA'], 128)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_addr', $arr_emap_corp['ADDR'], 128)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_post', $arr_emap_corp['POST'], 7)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_tel', $arr_emap_corp['TEL'], 15)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_busyo', $arr_emap_corp['BUSYO'], 128)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_tanto', $arr_emap_corp['TANTO'], 20)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_tanto_kana', $arr_emap_corp['TANTO_KANA'], 20)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_mail', $arr_emap_corp['MAIL'], 50)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_s_date', $arr_emap_corp['S_DATE'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_e_date', $arr_emap_corp['E_DATE'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_servname', $arr_emap_corp['SERVNAME'], 256)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_agencyid', $arr_emap_corp['AGENCYID'], 15)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_emap_kbn', $arr_emap_corp['EMAP_KBN'], 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_m_emap_kbn', $arr_emap_corp['M_EMAP_KBN'], 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_max_kyoten_cnt', $arr_emap_corp['MAX_KYOTEN_CNT'], 6)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_userid', $arr_emap_corp['USERID'], 5)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_other_maddr', $arr_emap_corp['OTHER_MADDR'], 1000)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_front_login_dt', $arr_emap_corp['FRONT_LOGIN_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_front_login_cnt', $arr_emap_corp['FRONT_LOGIN_CNT'], 3)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_map_login_dt', $arr_emap_corp['MAP_LOGIN_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_map_login_cnt', $arr_emap_corp['MAP_LOGIN_CNT' ], 3)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_end_flg', $arr_emap_corp['END_FLG'], 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_end_dt', $arr_emap_corp['END_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_ins_dt', $arr_emap_corp['INS_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_upd_dt', $arr_emap_corp['UPD_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_rtncd', $o_rtncd, 4)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		return true;
}



/* -----------------------------------------------------------------*/
//
//  操作ログ登録プロシージャ
//
/* -----------------------------------------------------------------*/
function spif_p_rd_operation_log_updt(&$dba, $i_kbn, $i_uid, $i_corp_id, $i_kyoten_id,  $i_func, $i_ope, $i_remote_addr, $i_user_agent, &$o_rtncd){
		$spstr = "begin"
			." P_RD_OPERATION_LOG_UPDT("
			.":i_kbn, :i_uid, :i_corp_id, :i_kyoten_id, :i_func, :i_ope, :i_remote_addr, :i_user_agent, :o_rtncd "
			.");"
			."end;";
		$stmt = OCIParse($dba->conn, $spstr);
		if(!$stmt){
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kbn', $i_kbn, 1)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_uid', $i_uid, 5)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_corp_id', $i_corp_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kyoten_id', $i_kyoten_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_func', $i_func, 100)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_ope', $i_ope, 100)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_remote_addr', $i_remote_addr, 20)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_user_agent', $i_user_agent, 4000)){
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_rtncd', $o_rtncd, 4)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		if(trim($o_rtncd) !== '0000'){
			return false;
		}
		return true;
}
/* -----------------------------------------------------------------*/
//
//  セッションテーブル登録プロシージャ
//
/* -----------------------------------------------------------------*/
function spif_p_rd_session_updt(&$dba,$i_kbn,$i_uid, $i_corp_id, $i_kyoten_id, $i_session_id, &$arr_opt, &$o_login_dt, &$o_acc_dt, &$o_rtncd){
		$spstr = "begin"
			." P_RD_SESSION_UPDT("
			.":i_kbn, :i_uid, :i_corp_id, :i_kyoten_id, :i_session_id, "
			.":i_opt_01, :i_opt_02, :i_opt_03, :i_opt_04, :i_opt_05, "
			.":i_opt_06, :i_opt_07, :i_opt_08, :i_opt_09, :i_opt_10, "
			.":o_login_dt, :o_acc_dt, :o_rtncd);"
			."end;";
		$stmt = OCIParse($dba->conn, $spstr);
		if(!$stmt){
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kbn', $i_kbn, 1)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_uid', $i_uid, 5)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_corp_id', $i_corp_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kyoten_id', $i_kyoten_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_session_id', $i_session_id, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_01', $arr_opt[OPT_01], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_02', $arr_opt[OPT_02], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_03', $arr_opt[OPT_03], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_04', $arr_opt[OPT_04], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_05', $arr_opt[OPT_05], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_06', $arr_opt[OPT_06], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_07', $arr_opt[OPT_07], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_08', $arr_opt[OPT_08], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_09', $arr_opt[OPT_09], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_10', $arr_opt[OPT_10], 4000)){
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_login_dt', $o_login_dt, 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_acc_dt', $o_acc_dt, 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_rtncd', $o_rtncd, 4)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		return true;
}

/* -----------------------------------------------------------------*/
//
//  リアルタイムデータ登録プロシージャ
//
/* -----------------------------------------------------------------*/
function spif_p_rd_data_updt(&$dba,$i_kbn,$i_commit_mode,$i_uid, $i_corp_id, $i_kyoten_id, $i_group_no,$i_item_no,$i_val_kbn,$i_txt_data,$i_flg_data,$i_img_w,$i_img_h,&$arr_opt, &$o_ins_dt, &$o_upd_dt, &$o_rtncd){
		$spstr = "begin"
			." p_rd_data_updt("
			.":i_kbn, :i_commit_mode,:i_uid, :i_corp_id, :i_kyoten_id, :i_group_no, :i_item_no,:i_val_kbn,:i_txt_data,:i_flg_data,:i_img_w,:i_img_h,"
			.":i_opt_01, :i_opt_02, :i_opt_03, :i_opt_04, :i_opt_05, "
			.":i_opt_06, :i_opt_07, :i_opt_08, :i_opt_09, :i_opt_10, "
			.":o_ins_dt, :o_upd_dt, :o_rtncd);"
			." p_rd_refresh('RD_DATA_TBL', :o_rtncd);" // add 20150529 F.Yokoi
			."end;";
		$stmt = OCIParse($dba->conn, $spstr);
		if(!$stmt){
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kbn', $i_kbn, 1)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_commit_mode', $i_commit_mode, 1)){
			$dba->free($stmt);
			return false;
		}

		if(!OCIBindByName($stmt, ':i_uid', $i_uid, 5)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_corp_id', $i_corp_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kyoten_id', $i_kyoten_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_group_no', $i_group_no, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_item_no', $i_item_no, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_val_kbn', $i_val_kbn, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_txt_data', $i_txt_data, 4000)){ // 文字数を最大にする 2013/04/05 H.Iijima
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_flg_data', $i_flg_data, 1)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_img_w', $i_img_w, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_img_h', $i_img_h, 128)){
			$dba->free($stmt);
			return false;
		}

		if(!OCIBindByName($stmt, ':i_opt_01', $arr_opt[OPT_01], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_02', $arr_opt[OPT_02], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_03', $arr_opt[OPT_03], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_04', $arr_opt[OPT_04], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_05', $arr_opt[OPT_05], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_06', $arr_opt[OPT_06], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_07', $arr_opt[OPT_07], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_08', $arr_opt[OPT_08], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_09', $arr_opt[OPT_09], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_10', $arr_opt[OPT_10], 4000)){
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_ins_dt', $o_ins_dt, 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_upd_dt', $o_upd_dt, 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_rtncd', $o_rtncd, 4)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		return true;
}

/* -----------------------------------------------------------------*/
//
//  グループデータ登録プロシージャ
//
/* -----------------------------------------------------------------*/
function spif_p_rd_group_updt(&$dba,$i_kbn,$i_commit_mode,$i_uid, $i_corp_id, $i_kyoten_id, $i_group_no,$i_status,$i_st_dt,$i_ed_dt,&$arr_opt, &$o_ins_dt, &$o_upd_dt, &$o_rtncd){
		$spstr = "begin"
			." p_rd_group_updt("
			.":i_kbn, :i_commit_mode,:i_uid, :i_corp_id, :i_kyoten_id, :i_group_no, :i_status,:i_st_dt,:i_ed_dt,"
			.":i_opt_01, :i_opt_02, :i_opt_03, :i_opt_04, :i_opt_05, "
			.":i_opt_06, :i_opt_07, :i_opt_08, :i_opt_09, :i_opt_10, "
			.":o_ins_dt, :o_upd_dt, :o_rtncd);"
			." p_rd_refresh('RD_GROUP_TBL', :o_rtncd);" // add 20150529 F.Yokoi
			."end;";
		$stmt = OCIParse($dba->conn, $spstr);
		if(!$stmt){
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kbn', $i_kbn, 1)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_commit_mode', $i_commit_mode, 1)){
			$dba->free($stmt);
			return false;
		}

		if(!OCIBindByName($stmt, ':i_uid', $i_uid, 5)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_corp_id', $i_corp_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_kyoten_id', $i_kyoten_id, 15)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_group_no', $i_group_no, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_status', $i_status, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_st_dt', $i_st_dt, 128)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_ed_dt', $i_ed_dt, 128)){
			$dba->free($stmt);
			return false;
		}

		if(!OCIBindByName($stmt, ':i_opt_01', $arr_opt[OPT_01], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_02', $arr_opt[OPT_02], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_03', $arr_opt[OPT_03], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_04', $arr_opt[OPT_04], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_05', $arr_opt[OPT_05], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_06', $arr_opt[OPT_06], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_07', $arr_opt[OPT_07], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_08', $arr_opt[OPT_08], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_09', $arr_opt[OPT_09], 4000)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':i_opt_10', $arr_opt[OPT_10], 4000)){
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_ins_dt', $o_ins_dt, 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_upd_dt', $o_upd_dt, 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_rtncd', $o_rtncd, 4)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		return true;
}


/* -----------------------------------------------------------------*/
//
//  リアルタイムデータリフレッシュ
//
/* -----------------------------------------------------------------*/
function spif_p_rd_refresh(&$dba,$i_mview,&$rtncd){
		$spstr = "begin"
			." p_rd_refresh(:i_mview, :rtncd ); "
			."end;";

		$stmt = OCIParse($dba->conn, $spstr);
		if(!$stmt){
			return false;
		}
		if(!OCIBindByName($stmt, ':i_mview', $i_mview, 50)){
			$dba->free($stmt);
			return false;
		}
		if(!OCIBindByName($stmt, ':rtncd', $rtncd, 4)){
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		return true;

}

/* -----------------------------------------------------------------*/
//
//  拠点テーブル - プロシージャ - インタフェース
//
/* -----------------------------------------------------------------*/
function SpifPKyotenUpdt(&$dba, $i_kbn, $i_userid, &$arr_kyoten, &$o_rtncd, $i_commit_mode = 0){
		$spstr = "begin " 
				. "P_KYOTEN_UPDT( " 
				. ":i_kbn, :i_commit_mode, :i_uid, :i_corp_id, :i_kyoten_id, "
				. ":i_lat, :i_lon, :i_icon_id, :i_pub_s_date, :i_pub_e_date, "
				. ":i_disp_new_s_date, :i_disp_new_e_date, :i_name, :i_addr, "
				. ":i_col_01, :i_col_02, :i_col_03, :i_col_04, :i_col_05, "
				. ":i_col_06, :i_col_07, :i_col_08, :i_col_09, :i_col_10, "
				. ":i_col_11, :i_col_12, :i_col_13, :i_col_14, :i_col_15, "
				. ":i_col_16, :i_col_17, :i_col_18, :i_col_19, :i_col_20, "
				. ":i_col_21, :i_col_22, :i_col_23, :i_col_24, :i_col_25, "
				. ":i_col_26, :i_col_27, :i_col_28, :i_col_29, :i_col_30, "
				. ":i_col_31, :i_col_32, :i_col_33, :i_col_34, :i_col_35, "
				. ":i_col_36, :i_col_37, :i_col_38, :i_col_39, :i_col_40, "
				. ":i_col_41, :i_col_42, :i_col_43, :i_col_44, :i_col_45, "
				. ":i_col_46, :i_col_47, :i_col_48, :i_col_49, :i_col_50, "
				// add 2009/10/15 Y.Matsukawa [
				. ":i_col_51,:i_col_52,:i_col_53,:i_col_54,:i_col_55,:i_col_56,:i_col_57,:i_col_58,:i_col_59,:i_col_60,"
				. ":i_col_61,:i_col_62,:i_col_63,:i_col_64,:i_col_65,:i_col_66,:i_col_67,:i_col_68,:i_col_69,:i_col_70,"
				. ":i_col_71,:i_col_72,:i_col_73,:i_col_74,:i_col_75,:i_col_76,:i_col_77,:i_col_78,:i_col_79,:i_col_80,"
				. ":i_col_81,:i_col_82,:i_col_83,:i_col_84,:i_col_85,:i_col_86,:i_col_87,:i_col_88,:i_col_89,:i_col_90,"
				. ":i_col_91,:i_col_92,:i_col_93,:i_col_94,:i_col_95,:i_col_96,:i_col_97,:i_col_98,:i_col_99,:i_col_100,"
				. ":i_col_101,:i_col_102,:i_col_103,:i_col_104,:i_col_105,:i_col_106,:i_col_107,:i_col_108,:i_col_109,:i_col_110,"
				. ":i_col_111,:i_col_112,:i_col_113,:i_col_114,:i_col_115,:i_col_116,:i_col_117,:i_col_118,:i_col_119,:i_col_120,"
				. ":i_col_121,:i_col_122,:i_col_123,:i_col_124,:i_col_125,:i_col_126,:i_col_127,:i_col_128,:i_col_129,:i_col_130,"
				. ":i_col_131,:i_col_132,:i_col_133,:i_col_134,:i_col_135,:i_col_136,:i_col_137,:i_col_138,:i_col_139,:i_col_140,"
				. ":i_col_141,:i_col_142,:i_col_143,:i_col_144,:i_col_145,:i_col_146,:i_col_147,:i_col_148,:i_col_149,:i_col_150,"
				. ":i_col_151,:i_col_152,:i_col_153,:i_col_154,:i_col_155,:i_col_156,:i_col_157,:i_col_158,:i_col_159,:i_col_160,"
				. ":i_col_161,:i_col_162,:i_col_163,:i_col_164,:i_col_165,:i_col_166,:i_col_167,:i_col_168,:i_col_169,:i_col_170,"
				. ":i_col_171,:i_col_172,:i_col_173,:i_col_174,:i_col_175,:i_col_176,:i_col_177,:i_col_178,:i_col_179,:i_col_180,"
				. ":i_col_181,:i_col_182,:i_col_183,:i_col_184,:i_col_185,:i_col_186,:i_col_187,:i_col_188,:i_col_189,:i_col_190,"
				. ":i_col_191,:i_col_192,:i_col_193,:i_col_194,:i_col_195,:i_col_196,:i_col_197,:i_col_198,:i_col_199,:i_col_200,"
				. ":i_refresh_flg,"
				// add 2009/10/15 Y.Matsukawa ]
				. ":i_url,    :i_m_url,  :i_m_level, :i_e_flg, "
				. ":o_ins_dt, :o_upd_dt, :o_rtncd "
				. "); "
				. "end;";

		$stmt = OCIParse($dba->conn, $spstr);
		if (!$stmt) {
			return false;
		}
		if (!OCIBindByName($stmt, ':i_kbn', $i_kbn, 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_commit_mode', $i_commit_mode, 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_uid', $i_userid, 5)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_corp_id', $arr_kyoten['CORP_ID'], 15)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_kyoten_id', $arr_kyoten['KYOTEN_ID'], 15)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_lat', $arr_kyoten['LAT'], 9)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_lon', $arr_kyoten['LON'], 9)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_icon_id', $arr_kyoten['ICON_ID'], 5)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_pub_s_date', $arr_kyoten['PUB_S_DATE'], 14)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_pub_e_date', $arr_kyoten['PUB_E_DATE'], 14)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_disp_new_s_date', $arr_kyoten['DISP_NEW_S_DATE'], 14)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_disp_new_e_date', $arr_kyoten['DISP_NEW_E_DATE'], 14)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_name', $arr_kyoten['NAME'], 128)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_addr', $arr_kyoten['ADDR'], 128)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_01', $arr_kyoten['COL_01'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_02', $arr_kyoten['COL_02'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_03', $arr_kyoten['COL_03'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_04', $arr_kyoten['COL_04'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_05', $arr_kyoten['COL_05'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_06', $arr_kyoten['COL_06'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_07', $arr_kyoten['COL_07'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_08', $arr_kyoten['COL_08'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_09', $arr_kyoten['COL_09'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_10', $arr_kyoten['COL_10'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_11', $arr_kyoten['COL_11'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_12', $arr_kyoten['COL_12'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_13', $arr_kyoten['COL_13'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_14', $arr_kyoten['COL_14'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_15', $arr_kyoten['COL_15'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_16', $arr_kyoten['COL_16'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_17', $arr_kyoten['COL_17'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_18', $arr_kyoten['COL_18'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_19', $arr_kyoten['COL_19'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_20', $arr_kyoten['COL_20'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_21', $arr_kyoten['COL_21'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_22', $arr_kyoten['COL_22'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_23', $arr_kyoten['COL_23'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_24', $arr_kyoten['COL_24'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_25', $arr_kyoten['COL_25'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_26', $arr_kyoten['COL_26'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_27', $arr_kyoten['COL_27'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_28', $arr_kyoten['COL_28'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_29', $arr_kyoten['COL_29'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_30', $arr_kyoten['COL_30'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_31', $arr_kyoten['COL_31'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_32', $arr_kyoten['COL_32'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_33', $arr_kyoten['COL_33'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_34', $arr_kyoten['COL_34'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_35', $arr_kyoten['COL_35'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_36', $arr_kyoten['COL_36'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_37', $arr_kyoten['COL_37'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_38', $arr_kyoten['COL_38'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_39', $arr_kyoten['COL_39'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_40', $arr_kyoten['COL_40'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_41', $arr_kyoten['COL_41'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_42', $arr_kyoten['COL_42'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_43', $arr_kyoten['COL_43'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_44', $arr_kyoten['COL_44'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_45', $arr_kyoten['COL_45'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_46', $arr_kyoten['COL_46'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_47', $arr_kyoten['COL_47'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_48', $arr_kyoten['COL_48'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_49', $arr_kyoten['COL_49'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_col_50', $arr_kyoten['COL_50'], 1000)) { 
			$dba->free($stmt);
			return false;
		}
		// add 2009/10/15 Y.Matsukawa [
		if(!OCIBindByName($stmt, ':i_col_51', $arr_kyoten['COL_51'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_52', $arr_kyoten['COL_52'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_53', $arr_kyoten['COL_53'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_54', $arr_kyoten['COL_54'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_55', $arr_kyoten['COL_55'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_56', $arr_kyoten['COL_56'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_57', $arr_kyoten['COL_57'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_58', $arr_kyoten['COL_58'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_59', $arr_kyoten['COL_59'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_60', $arr_kyoten['COL_60'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_61', $arr_kyoten['COL_61'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_62', $arr_kyoten['COL_62'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_63', $arr_kyoten['COL_63'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_64', $arr_kyoten['COL_64'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_65', $arr_kyoten['COL_65'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_66', $arr_kyoten['COL_66'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_67', $arr_kyoten['COL_67'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_68', $arr_kyoten['COL_68'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_69', $arr_kyoten['COL_69'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_70', $arr_kyoten['COL_70'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_71', $arr_kyoten['COL_71'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_72', $arr_kyoten['COL_72'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_73', $arr_kyoten['COL_73'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_74', $arr_kyoten['COL_74'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_75', $arr_kyoten['COL_75'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_76', $arr_kyoten['COL_76'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_77', $arr_kyoten['COL_77'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_78', $arr_kyoten['COL_78'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_79', $arr_kyoten['COL_79'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_80', $arr_kyoten['COL_80'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_81', $arr_kyoten['COL_81'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_82', $arr_kyoten['COL_82'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_83', $arr_kyoten['COL_83'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_84', $arr_kyoten['COL_84'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_85', $arr_kyoten['COL_85'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_86', $arr_kyoten['COL_86'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_87', $arr_kyoten['COL_87'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_88', $arr_kyoten['COL_88'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_89', $arr_kyoten['COL_89'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_90', $arr_kyoten['COL_90'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_91', $arr_kyoten['COL_91'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_92', $arr_kyoten['COL_92'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_93', $arr_kyoten['COL_93'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_94', $arr_kyoten['COL_94'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_95', $arr_kyoten['COL_95'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_96', $arr_kyoten['COL_96'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_97', $arr_kyoten['COL_97'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_98', $arr_kyoten['COL_98'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_99', $arr_kyoten['COL_99'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_100', $arr_kyoten['COL_100'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_101', $arr_kyoten['COL_101'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_102', $arr_kyoten['COL_102'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_103', $arr_kyoten['COL_103'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_104', $arr_kyoten['COL_104'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_105', $arr_kyoten['COL_105'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_106', $arr_kyoten['COL_106'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_107', $arr_kyoten['COL_107'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_108', $arr_kyoten['COL_108'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_109', $arr_kyoten['COL_109'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_110', $arr_kyoten['COL_110'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_111', $arr_kyoten['COL_111'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_112', $arr_kyoten['COL_112'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_113', $arr_kyoten['COL_113'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_114', $arr_kyoten['COL_114'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_115', $arr_kyoten['COL_115'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_116', $arr_kyoten['COL_116'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_117', $arr_kyoten['COL_117'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_118', $arr_kyoten['COL_118'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_119', $arr_kyoten['COL_119'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_120', $arr_kyoten['COL_120'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_121', $arr_kyoten['COL_121'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_122', $arr_kyoten['COL_122'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_123', $arr_kyoten['COL_123'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_124', $arr_kyoten['COL_124'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_125', $arr_kyoten['COL_125'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_126', $arr_kyoten['COL_126'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_127', $arr_kyoten['COL_127'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_128', $arr_kyoten['COL_128'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_129', $arr_kyoten['COL_129'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_130', $arr_kyoten['COL_130'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_131', $arr_kyoten['COL_131'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_132', $arr_kyoten['COL_132'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_133', $arr_kyoten['COL_133'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_134', $arr_kyoten['COL_134'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_135', $arr_kyoten['COL_135'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_136', $arr_kyoten['COL_136'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_137', $arr_kyoten['COL_137'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_138', $arr_kyoten['COL_138'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_139', $arr_kyoten['COL_139'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_140', $arr_kyoten['COL_140'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_141', $arr_kyoten['COL_141'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_142', $arr_kyoten['COL_142'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_143', $arr_kyoten['COL_143'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_144', $arr_kyoten['COL_144'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_145', $arr_kyoten['COL_145'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_146', $arr_kyoten['COL_146'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_147', $arr_kyoten['COL_147'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_148', $arr_kyoten['COL_148'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_149', $arr_kyoten['COL_149'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_150', $arr_kyoten['COL_150'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_151', $arr_kyoten['COL_151'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_152', $arr_kyoten['COL_152'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_153', $arr_kyoten['COL_153'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_154', $arr_kyoten['COL_154'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_155', $arr_kyoten['COL_155'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_156', $arr_kyoten['COL_156'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_157', $arr_kyoten['COL_157'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_158', $arr_kyoten['COL_158'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_159', $arr_kyoten['COL_159'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_160', $arr_kyoten['COL_160'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_161', $arr_kyoten['COL_161'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_162', $arr_kyoten['COL_162'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_163', $arr_kyoten['COL_163'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_164', $arr_kyoten['COL_164'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_165', $arr_kyoten['COL_165'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_166', $arr_kyoten['COL_166'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_167', $arr_kyoten['COL_167'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_168', $arr_kyoten['COL_168'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_169', $arr_kyoten['COL_169'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_170', $arr_kyoten['COL_170'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_171', $arr_kyoten['COL_171'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_172', $arr_kyoten['COL_172'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_173', $arr_kyoten['COL_173'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_174', $arr_kyoten['COL_174'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_175', $arr_kyoten['COL_175'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_176', $arr_kyoten['COL_176'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_177', $arr_kyoten['COL_177'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_178', $arr_kyoten['COL_178'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_179', $arr_kyoten['COL_179'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_180', $arr_kyoten['COL_180'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_181', $arr_kyoten['COL_181'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_182', $arr_kyoten['COL_182'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_183', $arr_kyoten['COL_183'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_184', $arr_kyoten['COL_184'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_185', $arr_kyoten['COL_185'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_186', $arr_kyoten['COL_186'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_187', $arr_kyoten['COL_187'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_188', $arr_kyoten['COL_188'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_189', $arr_kyoten['COL_189'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_190', $arr_kyoten['COL_190'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_191', $arr_kyoten['COL_191'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_192', $arr_kyoten['COL_192'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_193', $arr_kyoten['COL_193'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_194', $arr_kyoten['COL_194'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_195', $arr_kyoten['COL_195'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_196', $arr_kyoten['COL_196'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_197', $arr_kyoten['COL_197'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_198', $arr_kyoten['COL_198'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_199', $arr_kyoten['COL_199'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_col_200', $arr_kyoten['COL_200'], 1000)){ $dba->free($stmt); return false; }
		if(!OCIBindByName($stmt, ':i_refresh_flg', $arr_kyoten['REFRESH_FLG'], 1)){ $dba->free($stmt); return false; }
		// add 2009/10/15 Y.Matsukawa ]
		if (!OCIBindByName($stmt, ':i_url', $arr_kyoten['URL'], 1000)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_m_url', $arr_kyoten['M_URL'], 1000)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_m_level', $arr_kyoten['M_LEVEL'], 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':i_e_flg', $arr_kyoten['E_FLG'], 1)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_ins_dt', $arr_kyoten['INS_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_upd_dt', $arr_kyoten['UPD_DT'], 14)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIBindByName($stmt, ':o_rtncd', $o_rtncd, 4)) {
			$dba->free($stmt);
			return false;
		}
		if (!OCIExecute($stmt, OCI_DEFAULT)) {
			$dba->free($stmt);
			return false;
		}
		$dba->free($stmt);
		return true;
}


?>
