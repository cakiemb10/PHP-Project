<?php
/**********************************************************************
// 更新履歴：
// 2010/12/10 Y.Matsukawa	新規作成
// 2011/01/13 K.Masuda		出力項目(COL_34,COL_33,COL_35)追加
// 2011/03/30 K.Masuda		出力項目(COL_36)追加
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/09/09 K.Masuda		出力項目(COL_37〜COL_52)追加、COL_36修正
// 2012/01/26 K.Masuda		出力項目(DISP_NEW_S_DATE,DISP_NEW_E_DATE)追加
// 2012/10/27 K.Masuda		出力項目(COL_53〜COL_58)追加
/*********************************************************************/
//-----------------------------------------------------------
// JSON出力クラス
//-----------------------------------------------------------
class KyotenCgiOutputJSON extends KyotenCgiOutput {
	//-------------------------------------------
	// コンストラクタ
	//-------------------------------------------
	function KyotenCgiOutputJSON($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg) {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, 'JSON');
	}
	//-------------------------------------------
	// output
	// 出力
	//-------------------------------------------
	function output() {
		KyotenCgiOutput::output_header();
		KyotenCgiOutput::output_body_start();
		KyotenCgiOutput::output_status();
		if (is_array($this->ResultSet) && count($this->ResultSet)) {
			echo ',';
			echo '"shopList":[';
			foreach ($this->ResultSet as $i => $data) {
				// 緯度経度
				$lat = $data['LAT'];
				$lon = $data['LON'];
				if ($this->Pflg == '1') {
					// ミリ秒⇒度
					$lat = cnv_dms2hour($lat);
					$lon = cnv_dms2hour($lon);
				} else if ($this->Pflg == '3') {
					// ミリ秒⇒度分秒
					$lat = cnv_dms2deg($lat);
					$lon = cnv_dms2deg($lon);
				}
				if ($i > 0) echo ',';
				// 拠点データ
				echo '{';
				echo '"kyotenId":"'.$data['KYOTEN_ID'].'"';
				echo ',';
				echo '"lat":"'.$lat.'"';
				echo ',';
				echo '"lon":"'.$lon.'"';
				echo ',';
				if ($this->CgiNm == 'lw_nearkyoten') {
					echo '"distance":"'.$data['KYORI'].'"';
					echo ',';
				}
				// mod 2011/09/29 Y.Nakajima [
				if (isset($data['NAME'])) {
					echo '"name":"'.f_enc_convert($this->escapeJSON($data['NAME'])).'"';
				} else {
					echo '"name":"'.''.'"';
				}
				echo ',';
				if (isset($data['ADDR'])) {
					echo '"address":"'.f_enc_convert($this->escapeJSON($data['ADDR'])).'"';
				} else {
					echo '"address":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_29'])) {
					echo '"col_29":"'.f_enc_convert($this->escapeJSON($data['COL_29'])).'"';
				} else {
					echo '"col_29":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_30'])) {
					echo '"col_30":"'.f_enc_convert($this->escapeJSON($data['COL_30'])).'"';
				} else {
					echo '"col_30":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_01'])) {
					echo '"col_01":"'.$data['COL_01'].'"';
				} else {
					echo '"col_01":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_01_name'])) {
					echo '"col_01_name":"'.f_enc_convert($this->escapeJSON($data['COL_01_name'])).'"';
				} else {
					echo '"col_01_name":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_02'])) {
					echo '"col_02":"'.f_enc_convert($this->escapeJSON($data['COL_02'])).'"';
				} else {
					echo '"col_02":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_03'])) {
					echo '"col_03":"'.f_enc_convert($this->escapeJSON($data['COL_03'])).'"';
				} else {
					echo '"col_03":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_04'])) {
					echo '"col_04":"'.f_enc_convert($this->escapeJSON($data['COL_04'])).'"';
				} else {
					echo '"col_04":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_05'])) {
					echo '"col_05":"'.f_enc_convert($this->escapeJSON($data['COL_05'])).'"';
				} else {
					echo '"col_05":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_06'])) {
					echo '"col_06":"'.$data['COL_06'].'"';
				} else {
					echo '"col_06":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_06_name'])) {
					echo '"col_06_name":"'.f_enc_convert($this->escapeJSON($data['COL_06_name'])).'"';
				} else {
					echo '"col_06_name":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_07'])) {
					echo '"col_07":"'.$data['COL_07'].'"';
				} else {
					echo '"col_07":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_08'])) {
					echo '"col_08":"'.f_enc_convert($this->escapeJSON($data['COL_08'])).'"';
				} else {
					echo '"col_08":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_09'])) {
					echo '"col_09":"'.f_enc_convert($this->escapeJSON($data['COL_09'])).'"';
				} else {
					echo '"col_09":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_25'])) {
					echo '"col_25":"'.f_enc_convert($this->escapeJSON($data['COL_25'])).'"';
				} else {
					echo '"col_25":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_10'])) {
					echo '"col_10":"'.$data['COL_10'].'"';
				} else {
					echo '"col_10":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_11'])) {
					echo '"col_11":"'.$data['COL_11'].'"';
				} else {
					echo '"col_11":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_12'])) {
					echo '"col_12":"'.$data['COL_12'].'"';
				} else {
					echo '"col_12":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_13'])) {
					echo '"col_13":"'.$data['COL_13'].'"';
				} else {
					echo '"col_13":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_14'])) {
					echo '"col_14":"'.$data['COL_14'].'"';
				} else {
					echo '"col_14":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_31'])) {
					echo '"col_31":"'.f_enc_convert($this->escapeJSON($data['COL_31'])).'"';
				} else {
					echo '"col_31":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_15'])) {
					echo '"col_15":"'.$data['COL_15'].'"';
				} else {
					echo '"col_15":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_26'])) {
					echo '"col_26":"'.$data['COL_26'].'"';
				} else {
					echo '"col_26":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_27'])) {
					echo '"col_27":"'.$data['COL_27'].'"';
				} else {
					echo '"col_27":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_28'])) {
					echo '"col_28":"'.$data['COL_28'].'"';
				} else {
					echo '"col_28":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_32'])) {
					echo '"col_32":"'.$data['COL_32'].'"';
				} else {
					echo '"col_32":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_16'])) {
					echo '"col_16":"'.$data['COL_16'].'"';
				} else {
					echo '"col_16":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_17'])) {
					echo '"col_17":"'.$data['COL_17'].'"';
				} else {
					echo '"col_17":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_18'])) {
					echo '"col_18":"'.$data['COL_18'].'"';
				} else {
					echo '"col_18":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_19'])) {
					echo '"col_19":"'.$data['COL_19'].'"';
				} else {
					echo '"col_19":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_20'])) {
					echo '"col_20":"'.$data['COL_20'].'"';
				} else {
					echo '"col_20":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_21'])) {
					echo '"col_21":"'.$data['COL_21'].'"';
				} else {
					echo '"col_21":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_22'])) {
					echo '"col_22":"'.$data['COL_22'].'"';
				} else {
					echo '"col_22":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_23'])) {
					echo '"col_23":"'.$data['COL_23'].'"';
				} else {
					echo '"col_23":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_24'])) {
					echo '"col_24":"'.f_enc_convert($this->escapeJSON($data['COL_24'])).'"';
				} else {
					echo '"col_24":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_34'])) {
					echo '"col_34":"'.f_enc_convert($this->escapeJSON($data['COL_34'])).'"';
				} else {
					echo '"col_34":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_33'])) {
					echo '"col_33":"'.$data['COL_33'].'"';
				} else {
					echo '"col_33":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_35'])) {
					echo '"col_35":"'.f_enc_convert($this->escapeJSON($data['COL_35'])).'"';
				} else {
					echo '"col_35":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_36'])) {
					echo '"col_36":"'.$data['COL_36'].'"';
				} else {
					echo '"col_36":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_37'])) {
					echo '"col_37":"'.f_enc_convert($this->escapeJSON($data['COL_37'])).'"';
				} else {
					echo '"col_37":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_38'])) {
					echo '"col_38":"'.f_enc_convert($this->escapeJSON($data['COL_38'])).'"';
				} else {
					echo '"col_38":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_39'])) {
					echo '"col_39":"'.f_enc_convert($this->escapeJSON($data['COL_39'])).'"';
				} else {
					echo '"col_39":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_40'])) {
					echo '"col_40":"'.f_enc_convert($this->escapeJSON($data['COL_40'])).'"';
				} else {
					echo '"col_40":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_41'])) {
					echo '"col_41":"'.f_enc_convert($this->escapeJSON($data['COL_41'])).'"';
				} else {
					echo '"col_41":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_42'])) {
					echo '"col_42":"'.f_enc_convert($this->escapeJSON($data['COL_42'])).'"';
				} else {
					echo '"col_42":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_43'])) {
					echo '"col_43":"'.f_enc_convert($this->escapeJSON($data['COL_43'])).'"';
				} else {
					echo '"col_43":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_44'])) {
					echo '"col_44":"'.f_enc_convert($this->escapeJSON($data['COL_44'])).'"';
				} else {
					echo '"col_44":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_45'])) {
					echo '"col_45":"'.$data['COL_45'].'"';
				} else {
					echo '"col_45":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_46'])) {
					echo '"col_46":"'.$data['COL_46'].'"';
				} else {
					echo '"col_46":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_47'])) {
					echo '"col_47":"'.$data['COL_47'].'"';
				} else {
					echo '"col_47":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_48'])) {
					echo '"col_48":"'.$data['COL_48'].'"';
				} else {
					echo '"col_48":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_49'])) {
					echo '"col_49":"'.$data['COL_49'].'"';
				} else {
					echo '"col_49":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_50'])) {
					echo '"col_50":"'.$data['COL_50'].'"';
				} else {
					echo '"col_50":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_51'])) {
					echo '"col_51":"'.$data['COL_51'].'"';
				} else {
					echo '"col_51":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_52'])) {
					echo '"col_52":"'.$data['COL_52'].'"';
				} else {
					echo '"col_52":"'.''.'"';
				}
				// add 2012/10/27 K.Masuda [
				echo ',';
				if (isset($data['COL_53'])) {
					echo '"col_53":"'.$data['COL_53'].'"';
				} else {
					echo '"col_53":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_54'])) {
					echo '"col_54":"'.$data['COL_54'].'"';
				} else {
					echo '"col_54":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_55'])) {
					echo '"col_55":"'.$data['COL_55'].'"';
				} else {
					echo '"col_55":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_56'])) {
					echo '"col_56":"'.$data['COL_56'].'"';
				} else {
					echo '"col_56":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_57'])) {
					echo '"col_57":"'.$data['COL_57'].'"';
				} else {
					echo '"col_57":"'.''.'"';
				}
				echo ',';
				if (isset($data['COL_58'])) {
					echo '"col_58":"'.$data['COL_58'].'"';
				} else {
					echo '"col_58":"'.''.'"';
				}
				// add 2012/10/27 K.Masuda ]
				// add 2012/01/26 K.Masuda [
				echo ',';
				if (isset($data['DISP_NEW_S_DATE'])) {
					echo '"disp_new_s_date":"'.$data['DISP_NEW_S_DATE'].'"';
				} else {
					echo '"disp_new_s_date":"'.''.'"';
				}
				echo ',';
				if (isset($data['DISP_NEW_E_DATE'])) {
					echo '"disp_new_e_date":"'.$data['DISP_NEW_E_DATE'].'"';
				} else {
					echo '"disp_new_e_date":"'.''.'"';
				}
				// add 2012/01/26 K.Masuda ]
/*
				echo '"name":"'.f_enc_convert($this->escapeJSON($data['NAME'])).'"';
				echo ',';
				echo '"address":"'.f_enc_convert($this->escapeJSON($data['ADDR'])).'"';
				echo ',';
				echo '"col_29":"'.f_enc_convert($this->escapeJSON($data['COL_29'])).'"';
				echo ',';
				echo '"col_30":"'.f_enc_convert($this->escapeJSON($data['COL_30'])).'"';
				echo ',';
				echo '"col_01":"'.$data['COL_01'].'"';
				echo ',';
				echo '"col_01_name":"'.f_enc_convert($this->escapeJSON($data['COL_01_name'])).'"';
				echo ',';
				echo '"col_02":"'.f_enc_convert($this->escapeJSON($data['COL_02'])).'"';
				echo ',';
				echo '"col_03":"'.f_enc_convert($this->escapeJSON($data['COL_03'])).'"';
				echo ',';
				echo '"col_04":"'.f_enc_convert($this->escapeJSON($data['COL_04'])).'"';
				echo ',';
				echo '"col_05":"'.f_enc_convert($this->escapeJSON($data['COL_05'])).'"';
				echo ',';
				echo '"col_06":"'.$data['COL_06'].'"';
				echo ',';
				echo '"col_06_name":"'.f_enc_convert($this->escapeJSON($data['COL_06_name'])).'"';
				echo ',';
				echo '"col_07":"'.$data['COL_07'].'"';
				echo ',';
				echo '"col_08":"'.f_enc_convert($this->escapeJSON($data['COL_08'])).'"';
				echo ',';
				echo '"col_09":"'.f_enc_convert($this->escapeJSON($data['COL_09'])).'"';
				echo ',';
				echo '"col_25":"'.f_enc_convert($this->escapeJSON($data['COL_25'])).'"';
				echo ',';
				echo '"col_10":"'.$data['COL_10'].'"';
				echo ',';
				echo '"col_11":"'.$data['COL_11'].'"';
				echo ',';
				echo '"col_12":"'.$data['COL_12'].'"';
				echo ',';
				echo '"col_13":"'.$data['COL_13'].'"';
				echo ',';
				echo '"col_14":"'.$data['COL_14'].'"';
				echo ',';
				echo '"col_31":"'.f_enc_convert($this->escapeJSON($data['COL_31'])).'"';
				echo ',';
				echo '"col_15":"'.$data['COL_15'].'"';
				echo ',';
				echo '"col_26":"'.$data['COL_26'].'"';
				echo ',';
				echo '"col_27":"'.$data['COL_27'].'"';
				echo ',';
				echo '"col_28":"'.$data['COL_28'].'"';
				echo ',';
				echo '"col_32":"'.$data['COL_32'].'"';
				echo ',';
				echo '"col_16":"'.$data['COL_16'].'"';
				echo ',';
				echo '"col_17":"'.$data['COL_17'].'"';
				echo ',';
				echo '"col_18":"'.$data['COL_18'].'"';
				echo ',';
				echo '"col_19":"'.$data['COL_19'].'"';
				echo ',';
				echo '"col_20":"'.$data['COL_20'].'"';
				echo ',';
				echo '"col_21":"'.$data['COL_21'].'"';
				echo ',';
				echo '"col_22":"'.$data['COL_22'].'"';
				echo ',';
				echo '"col_23":"'.$data['COL_23'].'"';
				echo ',';
				echo '"col_24":"'.f_enc_convert($this->escapeJSON($data['COL_24'])).'"';
// add 2011/01/13 K.Masuda [
				echo ',';
				echo '"col_34":"'.f_enc_convert($this->escapeJSON($data['COL_34'])).'"';
				echo ',';
				echo '"col_33":"'.$data['COL_33'].'"';
				echo ',';
				echo '"col_35":"'.f_enc_convert($this->escapeJSON($data['COL_35'])).'"';
// add 2011/01/13 K.Masuda ]
// add 2011/03/30 K.Masuda [
				echo ',';
				//echo '"col_36":"'.f_enc_convert($this->escapeJSON($data['COL_36'])).'"';	// mod 2011/09/09 K.Masuda
				echo '"col_36":"'.$data['COL_36'].'"';
// add 2011/03/30 K.Masuda ]
// add 2011/09/09 K.Masuda [
				echo ',';
				echo '"col_37":"'.f_enc_convert($this->escapeJSON($data['COL_37'])).'"';
				echo ',';
				echo '"col_38":"'.f_enc_convert($this->escapeJSON($data['COL_38'])).'"';
				echo ',';
				echo '"col_39":"'.f_enc_convert($this->escapeJSON($data['COL_39'])).'"';
				echo ',';
				echo '"col_40":"'.f_enc_convert($this->escapeJSON($data['COL_40'])).'"';
				echo ',';
				echo '"col_41":"'.f_enc_convert($this->escapeJSON($data['COL_41'])).'"';
				echo ',';
				echo '"col_42":"'.f_enc_convert($this->escapeJSON($data['COL_42'])).'"';
				echo ',';
				echo '"col_43":"'.f_enc_convert($this->escapeJSON($data['COL_43'])).'"';
				echo ',';
				echo '"col_44":"'.f_enc_convert($this->escapeJSON($data['COL_44'])).'"';
				echo ',';
				echo '"col_45":"'.$data['COL_45'].'"';
				echo ',';
				echo '"col_46":"'.$data['COL_46'].'"';
				echo ',';
				echo '"col_47":"'.$data['COL_47'].'"';
				echo ',';
				echo '"col_48":"'.$data['COL_48'].'"';
				echo ',';
				echo '"col_49":"'.$data['COL_49'].'"';
				echo ',';
				echo '"col_50":"'.$data['COL_50'].'"';
				echo ',';
				echo '"col_51":"'.$data['COL_51'].'"';
				echo ',';
				echo '"col_52":"'.$data['COL_52'].'"';
// add 2011/09/09 K.Masuda ]
*/
				// mod 2011/09/29 Y.Nakajima ]
				echo '}';
			}
			echo ']';
		}
		KyotenCgiOutput::output_body_end();
	}
}

?>
