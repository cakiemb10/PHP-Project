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
// XML出力クラス
//-----------------------------------------------------------
class KyotenCgiOutputXML extends KyotenCgiOutput {
	//-------------------------------------------
	// コンストラクタ
	//-------------------------------------------
	function KyotenCgiOutputXML($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg) {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, 'XML');
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
			echo '<shopList>'.$this->LineSep;
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
				$item_id = $i + 1;
				// 拠点データ
				echo '<item id="'.$item_id.'">'.$this->LineSep;
				echo '<kyotenId>'.$data['KYOTEN_ID'].'</kyotenId>'.$this->LineSep;
				echo '<lat>'.$lat.'</lat>'.$this->LineSep;
				echo '<lon>'.$lon.'</lon>'.$this->LineSep;
				if ($this->CgiNm == 'lw_nearkyoten')
					echo '<distance>'.$data['KYORI'].'</distance>'.$this->LineSep;
				// mod 2011/09/29 Y.Nakajima [
				if (isset($data['NAME'])) {
					echo '<name>'.f_enc_convert($this->escapeXML($data['NAME'])).'</name>'.$this->LineSep;
				} else {
					echo '<name>'.''.'</name>'.$this->LineSep;
				}
				if (isset($data['ADDR'])) {
					echo '<address>'.f_enc_convert($this->escapeXML($data['ADDR'])).'</address>'.$this->LineSep;
				} else {
					echo '<address>'.''.'</address>'.$this->LineSep;
				}
				if (isset($data['COL_29'])) {
					echo '<col_29>'.f_enc_convert($this->escapeXML($data['COL_29'])).'</col_29>'.$this->LineSep;
				} else {
					echo '<col_29>'.''.'</col_29>'.$this->LineSep;
				}
				if (isset($data['COL_30'])) {
					echo '<col_30>'.f_enc_convert($this->escapeXML($data['COL_30'])).'</col_30>'.$this->LineSep;
				} else {
					echo '<col_30>'.''.'</col_30>'.$this->LineSep;
				}
				if (isset($data['COL_01'])) {
					echo '<col_01>'.$data['COL_01'].'</col_01>'.$this->LineSep;
				} else {
					echo '<col_01>'.''.'</col_01>'.$this->LineSep;
				}
				if (isset($data['COL_01_name'])) {
					echo '<col_01_name>'.f_enc_convert($this->escapeXML($data['COL_01_name'])).'</col_01_name>'.$this->LineSep;
				} else {
					echo '<col_01_name>'.''.'</col_01_name>'.$this->LineSep;
				}
				if (isset($data['COL_02'])) {
					echo '<col_02>'.f_enc_convert($this->escapeXML($data['COL_02'])).'</col_02>'.$this->LineSep;
				} else {
					echo '<col_02>'.''.'</col_02>'.$this->LineSep;
				}
				if (isset($data['COL_03'])) {
					echo '<col_03>'.f_enc_convert($this->escapeXML($data['COL_03'])).'</col_03>'.$this->LineSep;
				} else {
					echo '<col_03>'.''.'</col_03>'.$this->LineSep;
				}
				if (isset($data['COL_04'])) {
					echo '<col_04>'.f_enc_convert($this->escapeXML($data['COL_04'])).'</col_04>'.$this->LineSep;
				} else {
					echo '<col_04>'.''.'</col_04>'.$this->LineSep;
				}
				if (isset($data['COL_05'])) {
					echo '<col_05>'.f_enc_convert($this->escapeXML($data['COL_05'])).'</col_05>'.$this->LineSep;
				} else {
					echo '<col_05>'.''.'</col_05>'.$this->LineSep;
				}
				if (isset($data['COL_06'])) {
					echo '<col_06>'.$data['COL_06'].'</col_06>'.$this->LineSep;
				} else {
					echo '<col_06>'.''.'</col_06>'.$this->LineSep;
				}
				if (isset($data['COL_06_name'])) {
					echo '<col_06_name>'.f_enc_convert($this->escapeXML($data['COL_06_name'])).'</col_06_name>'.$this->LineSep;
				} else {
					echo '<col_06_name>'.''.'</col_06_name>'.$this->LineSep;
				}
				if (isset($data['COL_07'])) {
					echo '<col_07>'.$data['COL_07'].'</col_07>'.$this->LineSep;
				} else {
					echo '<col_07>'.''.'</col_07>'.$this->LineSep;
				}
				if (isset($data['COL_08'])) {
					echo '<col_08>'.f_enc_convert($this->escapeXML($data['COL_08'])).'</col_08>'.$this->LineSep;
				} else {
					echo '<col_08>'.''.'</col_08>'.$this->LineSep;
				}
				if (isset($data['COL_09'])) {
					echo '<col_09>'.f_enc_convert($this->escapeXML($data['COL_09'])).'</col_09>'.$this->LineSep;
				} else {
					echo '<col_09>'.''.'</col_09>'.$this->LineSep;
				}
				if (isset($data['COL_25'])) {
					echo '<col_25>'.f_enc_convert($this->escapeXML($data['COL_25'])).'</col_25>'.$this->LineSep;
				} else {
					echo '<col_25>'.''.'</col_25>'.$this->LineSep;
				}
				if (isset($data['COL_10'])) {
					echo '<col_10>'.$data['COL_10'].'</col_10>'.$this->LineSep;
				} else {
					echo '<col_10>'.''.'</col_10>'.$this->LineSep;
				}
				if (isset($data['COL_11'])) {
					echo '<col_11>'.$data['COL_11'].'</col_11>'.$this->LineSep;
				} else {
					echo '<col_11>'.''.'</col_11>'.$this->LineSep;
				}
				if (isset($data['COL_12'])) {
					echo '<col_12>'.$data['COL_12'].'</col_12>'.$this->LineSep;
				} else {
					echo '<col_12>'.''.'</col_12>'.$this->LineSep;
				}
				if (isset($data['COL_13'])) {
					echo '<col_13>'.$data['COL_13'].'</col_13>'.$this->LineSep;
				} else {
					echo '<col_13>'.''.'</col_13>'.$this->LineSep;
				}
				if (isset($data['COL_14'])) {
					echo '<col_14>'.$data['COL_14'].'</col_14>'.$this->LineSep;
				} else {
					echo '<col_14>'.''.'</col_14>'.$this->LineSep;
				}
				if (isset($data['COL_31'])) {
					echo '<col_31>'.f_enc_convert($this->escapeXML($data['COL_31'])).'</col_31>'.$this->LineSep;
				} else {
					echo '<col_31>'.''.'</col_31>'.$this->LineSep;
				}
				if (isset($data['COL_15'])) {
					echo '<col_15>'.$data['COL_15'].'</col_15>'.$this->LineSep;
				} else {
					echo '<col_15>'.''.'</col_15>'.$this->LineSep;
				}
				if (isset($data['COL_26'])) {
					echo '<col_26>'.$data['COL_26'].'</col_26>'.$this->LineSep;
				} else {
					echo '<col_26>'.''.'</col_26>'.$this->LineSep;
				}
				if (isset($data['COL_27'])) {
					echo '<col_27>'.$data['COL_27'].'</col_27>'.$this->LineSep;
				} else {
					echo '<col_27>'.''.'</col_27>'.$this->LineSep;
				}
				if (isset($data['COL_28'])) {
					echo '<col_28>'.$data['COL_28'].'</col_28>'.$this->LineSep;
				} else {
					echo '<col_28>'.''.'</col_28>'.$this->LineSep;
				}
				if (isset($data['COL_32'])) {
					echo '<col_32>'.$data['COL_32'].'</col_32>'.$this->LineSep;
				} else {
					echo '<col_32>'.''.'</col_32>'.$this->LineSep;
				}
				if (isset($data['COL_16'])) {
					echo '<col_16>'.$data['COL_16'].'</col_16>'.$this->LineSep;
				} else {
					echo '<col_16>'.''.'</col_16>'.$this->LineSep;
				}
				if (isset($data['COL_17'])) {
					echo '<col_17>'.$data['COL_17'].'</col_17>'.$this->LineSep;
				} else {
					echo '<col_17>'.''.'</col_17>'.$this->LineSep;
				}
				if (isset($data['COL_18'])) {
					echo '<col_18>'.$data['COL_18'].'</col_18>'.$this->LineSep;
				} else {
					echo '<col_18>'.''.'</col_18>'.$this->LineSep;
				}
				if (isset($data['COL_19'])) {
					echo '<col_19>'.$data['COL_19'].'</col_19>'.$this->LineSep;
				} else {
					echo '<col_19>'.''.'</col_19>'.$this->LineSep;
				}
				if (isset($data['COL_20'])) {
					echo '<col_20>'.$data['COL_20'].'</col_20>'.$this->LineSep;
				} else {
					echo '<col_20>'.''.'</col_20>'.$this->LineSep;
				}
				if (isset($data['COL_21'])) {
					echo '<col_21>'.$data['COL_21'].'</col_21>'.$this->LineSep;
				} else {
					echo '<col_21>'.''.'</col_21>'.$this->LineSep;
				}
				if (isset($data['COL_22'])) {
					echo '<col_22>'.$data['COL_22'].'</col_22>'.$this->LineSep;
				} else {
					echo '<col_22>'.''.'</col_22>'.$this->LineSep;
				}
				if (isset($data['COL_23'])) {
					echo '<col_23>'.$data['COL_23'].'</col_23>'.$this->LineSep;
				} else {
					echo '<col_23>'.''.'</col_23>'.$this->LineSep;
				}
				if (isset($data['COL_24'])) {
					echo '<col_24>'.f_enc_convert($this->escapeXML($data['COL_24'])).'</col_24>'.$this->LineSep;
				} else {
					echo '<col_24>'.''.'</col_24>'.$this->LineSep;
				}
				if (isset($data['COL_34'])) {
					echo '<col_34>'.f_enc_convert($this->escapeXML($data['COL_34'])).'</col_34>'.$this->LineSep;
				} else {
					echo '<col_34>'.''.'</col_34>'.$this->LineSep;
				}
				if (isset($data['COL_33'])) {
					echo '<col_33>'.$data['COL_33'].'</col_33>'.$this->LineSep;
				} else {
					echo '<col_33>'.''.'</col_33>'.$this->LineSep;
				}
				if (isset($data['COL_35'])) {
					echo '<col_35>'.f_enc_convert($this->escapeXML($data['COL_35'])).'</col_35>'.$this->LineSep;
				} else {
					echo '<col_35>'.''.'</col_35>'.$this->LineSep;
				}
				if (isset($data['COL_36'])) {
					echo '<col_36>'.$data['COL_36'].'</col_36>'.$this->LineSep;
				} else {
					echo '<col_36>'.''.'</col_36>'.$this->LineSep;
				}
				if (isset($data['COL_37'])) {
					echo '<col_37>'.f_enc_convert($this->escapeXML($data['COL_37'])).'</col_37>'.$this->LineSep;
				} else {
					echo '<col_37>'.''.'</col_37>'.$this->LineSep;
				}
				if (isset($data['COL_38'])) {
					echo '<col_38>'.f_enc_convert($this->escapeXML($data['COL_38'])).'</col_38>'.$this->LineSep;
				} else {
					echo '<col_38>'.''.'</col_38>'.$this->LineSep;
				}
				if (isset($data['COL_39'])) {
					echo '<col_39>'.f_enc_convert($this->escapeXML($data['COL_39'])).'</col_39>'.$this->LineSep;
				} else {
					echo '<col_39>'.''.'</col_39>'.$this->LineSep;
				}
				if (isset($data['COL_40'])) {
					echo '<col_40>'.f_enc_convert($this->escapeXML($data['COL_40'])).'</col_40>'.$this->LineSep;
				} else {
					echo '<col_40>'.''.'</col_40>'.$this->LineSep;
				}
				if (isset($data['COL_41'])) {
					echo '<col_41>'.f_enc_convert($this->escapeXML($data['COL_41'])).'</col_41>'.$this->LineSep;
				} else {
					echo '<col_41>'.''.'</col_41>'.$this->LineSep;
				}
				if (isset($data['COL_42'])) {
					echo '<col_42>'.f_enc_convert($this->escapeXML($data['COL_42'])).'</col_42>'.$this->LineSep;
				} else {
					echo '<col_42>'.''.'</col_42>'.$this->LineSep;
				}
				if (isset($data['COL_43'])) {
					echo '<col_43>'.f_enc_convert($this->escapeXML($data['COL_43'])).'</col_43>'.$this->LineSep;
				} else {
					echo '<col_43>'.''.'</col_43>'.$this->LineSep;
				}
				if (isset($data['COL_44'])) {
					echo '<col_44>'.f_enc_convert($this->escapeXML($data['COL_44'])).'</col_44>'.$this->LineSep;
				} else {
					echo '<col_44>'.''.'</col_44>'.$this->LineSep;
				}
				if (isset($data['COL_45'])) {
					echo '<col_45>'.$data['COL_45'].'</col_45>'.$this->LineSep;
				} else {
					echo '<col_45>'.''.'</col_45>'.$this->LineSep;
				}
				if (isset($data['COL_46'])) {
					echo '<col_46>'.$data['COL_46'].'</col_46>'.$this->LineSep;
				} else {
					echo '<col_46>'.''.'</col_46>'.$this->LineSep;
				}
				if (isset($data['COL_47'])) {
					echo '<col_47>'.$data['COL_47'].'</col_47>'.$this->LineSep;
				} else {
					echo '<col_47>'.''.'</col_47>'.$this->LineSep;
				}
				if (isset($data['COL_48'])) {
					echo '<col_48>'.$data['COL_48'].'</col_48>'.$this->LineSep;
				} else {
					echo '<col_48>'.''.'</col_48>'.$this->LineSep;
				}
				if (isset($data['COL_49'])) {
					echo '<col_49>'.$data['COL_49'].'</col_49>'.$this->LineSep;
				} else {
					echo '<col_49>'.''.'</col_49>'.$this->LineSep;
				}
				if (isset($data['COL_50'])) {
					echo '<col_50>'.$data['COL_50'].'</col_50>'.$this->LineSep;
				} else {
					echo '<col_50>'.''.'</col_50>'.$this->LineSep;
				}
				if (isset($data['COL_51'])) {
					echo '<col_51>'.$data['COL_51'].'</col_51>'.$this->LineSep;
				} else {
					echo '<col_51>'.''.'</col_51>'.$this->LineSep;
				}
				if (isset($data['COL_52'])) {
					echo '<col_52>'.$data['COL_52'].'</col_52>'.$this->LineSep;
				} else {
					echo '<col_52>'.''.'</col_52>'.$this->LineSep;
				}
				// mod 2011/09/29 Y.Nakajima ]
				// add 2012/10/27 K.Masuda [
				if (isset($data['COL_53'])) {
					echo '<col_53>'.$data['COL_53'].'</col_53>'.$this->LineSep;
				} else {
					echo '<col_53>'.''.'</col_53>'.$this->LineSep;
				}
				if (isset($data['COL_54'])) {
					echo '<col_54>'.$data['COL_54'].'</col_54>'.$this->LineSep;
				} else {
					echo '<col_54>'.''.'</col_54>'.$this->LineSep;
				}
				if (isset($data['COL_55'])) {
					echo '<col_55>'.$data['COL_55'].'</col_55>'.$this->LineSep;
				} else {
					echo '<col_55>'.''.'</col_55>'.$this->LineSep;
				}
				if (isset($data['COL_56'])) {
					echo '<col_56>'.$data['COL_56'].'</col_56>'.$this->LineSep;
				} else {
					echo '<col_56>'.''.'</col_56>'.$this->LineSep;
				}
				if (isset($data['COL_57'])) {
					echo '<col_57>'.$data['COL_57'].'</col_57>'.$this->LineSep;
				} else {
					echo '<col_57>'.''.'</col_57>'.$this->LineSep;
				}
				if (isset($data['COL_58'])) {
					echo '<col_58>'.$data['COL_58'].'</col_58>'.$this->LineSep;
				} else {
					echo '<col_58>'.''.'</col_58>'.$this->LineSep;
				}
				// add 2012/10/27 K.Masuda ]
				// add 2012/01/26 K.Masuda [
				if (isset($data['DISP_NEW_S_DATE'])) {
					echo '<disp_new_s_date>'.$data['DISP_NEW_S_DATE'].'</disp_new_s_date>'.$this->LineSep;
				} else {
					echo '<disp_new_s_date>'.''.'</disp_new_s_date>'.$this->LineSep;
				}
				if (isset($data['DISP_NEW_E_DATE'])) {
					echo '<disp_new_e_date>'.$data['DISP_NEW_E_DATE'].'</disp_new_e_date>'.$this->LineSep;
				} else {
					echo '<disp_new_e_date>'.''.'</disp_new_e_date>'.$this->LineSep;
				}
				// add 2012/01/26 K.Masuda ]
/*
				echo '<name>'.f_enc_convert($this->escapeXML($data['NAME'])).'</name>'.$this->LineSep;
				echo '<address>'.f_enc_convert($this->escapeXML($data['ADDR'])).'</address>'.$this->LineSep;
				echo '<col_29>'.f_enc_convert($this->escapeXML($data['COL_29'])).'</col_29>'.$this->LineSep;
				echo '<col_30>'.f_enc_convert($this->escapeXML($data['COL_30'])).'</col_30>'.$this->LineSep;
				echo '<col_01>'.$data['COL_01'].'</col_01>'.$this->LineSep;
				echo '<col_01_name>'.f_enc_convert($this->escapeXML($data['COL_01_name'])).'</col_01_name>'.$this->LineSep;
				echo '<col_02>'.f_enc_convert($this->escapeXML($data['COL_02'])).'</col_02>'.$this->LineSep;
				echo '<col_03>'.f_enc_convert($this->escapeXML($data['COL_03'])).'</col_03>'.$this->LineSep;
				echo '<col_04>'.f_enc_convert($this->escapeXML($data['COL_04'])).'</col_04>'.$this->LineSep;
				echo '<col_05>'.f_enc_convert($this->escapeXML($data['COL_05'])).'</col_05>'.$this->LineSep;
				echo '<col_06>'.$data['COL_06'].'</col_06>'.$this->LineSep;
				echo '<col_06_name>'.f_enc_convert($this->escapeXML($data['COL_06_name'])).'</col_06_name>'.$this->LineSep;
				echo '<col_07>'.$data['COL_07'].'</col_07>'.$this->LineSep;
				echo '<col_08>'.f_enc_convert($this->escapeXML($data['COL_08'])).'</col_08>'.$this->LineSep;
				echo '<col_09>'.f_enc_convert($this->escapeXML($data['COL_09'])).'</col_09>'.$this->LineSep;
				echo '<col_25>'.f_enc_convert($this->escapeXML($data['COL_25'])).'</col_25>'.$this->LineSep;
				echo '<col_10>'.$data['COL_10'].'</col_10>'.$this->LineSep;
				echo '<col_11>'.$data['COL_11'].'</col_11>'.$this->LineSep;
				echo '<col_12>'.$data['COL_12'].'</col_12>'.$this->LineSep;
				echo '<col_13>'.$data['COL_13'].'</col_13>'.$this->LineSep;
				echo '<col_14>'.$data['COL_14'].'</col_14>'.$this->LineSep;
				echo '<col_31>'.f_enc_convert($this->escapeXML($data['COL_31'])).'</col_31>'.$this->LineSep;
				echo '<col_15>'.$data['COL_15'].'</col_15>'.$this->LineSep;
				echo '<col_26>'.$data['COL_26'].'</col_26>'.$this->LineSep;
				echo '<col_27>'.$data['COL_27'].'</col_27>'.$this->LineSep;
				echo '<col_28>'.$data['COL_28'].'</col_28>'.$this->LineSep;
				echo '<col_32>'.$data['COL_32'].'</col_32>'.$this->LineSep;
				echo '<col_16>'.$data['COL_16'].'</col_16>'.$this->LineSep;
				echo '<col_17>'.$data['COL_17'].'</col_17>'.$this->LineSep;
				echo '<col_18>'.$data['COL_18'].'</col_18>'.$this->LineSep;
				echo '<col_19>'.$data['COL_19'].'</col_19>'.$this->LineSep;
				echo '<col_20>'.$data['COL_20'].'</col_20>'.$this->LineSep;
				echo '<col_21>'.$data['COL_21'].'</col_21>'.$this->LineSep;
				echo '<col_22>'.$data['COL_22'].'</col_22>'.$this->LineSep;
				echo '<col_23>'.$data['COL_23'].'</col_23>'.$this->LineSep;
				echo '<col_24>'.f_enc_convert($this->escapeXML($data['COL_24'])).'</col_24>'.$this->LineSep;
// add 2011/01/13 K.Masuda [
				echo '<col_34>'.f_enc_convert($this->escapeXML($data['COL_34'])).'</col_34>'.$this->LineSep;
				echo '<col_33>'.$data['COL_33'].'</col_33>'.$this->LineSep;
				echo '<col_35>'.f_enc_convert($this->escapeXML($data['COL_35'])).'</col_35>'.$this->LineSep;
// add 2011/01/13 K.Masuda ]
// add 2011/03/30 K.Masuda [
				//echo '<col_36>'.f_enc_convert($this->escapeXML($data['COL_36'])).'</col_36>'.$this->LineSep;	mod 2011/09/09 K.Masuda
				echo '<col_36>'.$data['COL_36'].'</col_36>'.$this->LineSep;
// add 2011/03/30 K.Masuda ]
// add 2011/09/09 K.Masuda [
				echo '<col_37>'.f_enc_convert($this->escapeXML($data['COL_37'])).'</col_37>'.$this->LineSep;
				echo '<col_38>'.f_enc_convert($this->escapeXML($data['COL_38'])).'</col_38>'.$this->LineSep;
				echo '<col_39>'.f_enc_convert($this->escapeXML($data['COL_39'])).'</col_39>'.$this->LineSep;
				echo '<col_40>'.f_enc_convert($this->escapeXML($data['COL_40'])).'</col_40>'.$this->LineSep;
				echo '<col_41>'.f_enc_convert($this->escapeXML($data['COL_41'])).'</col_41>'.$this->LineSep;
				echo '<col_42>'.f_enc_convert($this->escapeXML($data['COL_42'])).'</col_42>'.$this->LineSep;
				echo '<col_43>'.f_enc_convert($this->escapeXML($data['COL_43'])).'</col_43>'.$this->LineSep;
				echo '<col_44>'.f_enc_convert($this->escapeXML($data['COL_44'])).'</col_44>'.$this->LineSep;
				echo '<col_45>'.$data['COL_45'].'</col_45>'.$this->LineSep;
				echo '<col_46>'.$data['COL_46'].'</col_46>'.$this->LineSep;
				echo '<col_47>'.$data['COL_47'].'</col_47>'.$this->LineSep;
				echo '<col_48>'.$data['COL_48'].'</col_48>'.$this->LineSep;
				echo '<col_49>'.$data['COL_49'].'</col_49>'.$this->LineSep;
				echo '<col_50>'.$data['COL_50'].'</col_50>'.$this->LineSep;
				echo '<col_51>'.$data['COL_51'].'</col_51>'.$this->LineSep;
				echo '<col_52>'.$data['COL_52'].'</col_52>'.$this->LineSep;
// add 2011/09/09 K.Masuda ]
*/
				echo '</item>'.$this->LineSep;
			}
			echo '</shopList>'.$this->LineSep;
		}
		KyotenCgiOutput::output_body_end();
	}
}

?>
