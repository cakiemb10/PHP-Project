<?php
/**********************************************************************
// 更新履歴：
// 2010/01/08 Y.Matsukawa	新規作成
// 2010/01/25 Y.Matsukawa	出力項目追加（created,modified,comment_count）
/*********************************************************************/
//-----------------------------------------------------------
// JSON出力クラス
//-----------------------------------------------------------
class KyotenCgiOutputJSON extends KyotenCgiOutput {
	var $TagType = '';
	//-------------------------------------------
	// コンストラクタ
	//-------------------------------------------
	function KyotenCgiOutputJSON($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $type) {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, 'JSON');
		$this->TagType = $type;
	}
	//-------------------------------------------
	// output
	// 出力
	//-------------------------------------------
	function output() {
		global $SEKAI_UID;
		global $SEKAI_IMGURL;
		global $SEKAI_EMAPURL;
		global $SEKAI_PROFILE_NAME;
		KyotenCgiOutput::output_header();
		KyotenCgiOutput::output_body_start();
		KyotenCgiOutput::output_status();
		if (is_array($this->ResultSet) && count($this->ResultSet)) {
			switch ($this->TagType) {
				// エアタグ
				case SEKAI_AIRTAG:
					echo ',';
					echo '"tag_list":[';
					foreach ($this->ResultSet as $i => $data) {
						$uid = $SEKAI_UID[$data['CORP_ID']];
						$id = kyotenId2sekaiId($uid, $data['KYOTEN_ID']);
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
						$altitude = '0';
						// add 2010/01/25 Y.Matsukawa [
						$w_ymd = $data['INS_DT_YMD'];
						$w_tim = $data['INS_DT_TIM'];
						$created = $w_ymd[0].' '.$w_ymd[1].'/'.$w_ymd[2].' '.$w_tim[0].':'.$w_tim[1].':'.$w_tim[2];
						$w_ymd = $data['UPD_DT_YMD'];
						$w_tim = $data['UPD_DT_TIM'];
						$modified = $w_ymd[0].' '.$w_ymd[1].'/'.$w_ymd[2].' '.$w_tim[0].':'.$w_tim[1].':'.$w_tim[2];
						$comments_count = '1';
						// add 2010/01/25 Y.Matsukawa ]
						if ($i > 0) echo ',';
						echo '{';
						echo '"user_id":"'.$uid.'"';
						echo ',';
						echo '"id":"'.$id.'"';
						echo ',';
						echo '"content":""';
						echo ',';
						echo '"lat":"'.$lat.'"';
						echo ',';
						echo '"lon":"'.$lon.'"';
						echo ',';
						echo '"altitude":"'.$altitude.'"';
						echo ',';
						echo '"attribute":"200"';
						// add 2010/01/25 Y.Matsukawa [
						echo ',';
						echo '"created":"'.$created.'"';
						echo ',';
						echo '"modified":"'.$modified.'"';
						echo ',';
						echo '"comments_count":"'.$comments_count.'"';
						// add 2010/01/25 Y.Matsukawa ]
						echo ',';
						echo '"icon_id":""';
						echo ',';
						echo '"thumbnail":"'.$SEKAI_IMGURL[$uid]['TMB'].'"';
						echo '}';
					}
					echo ']';
					break;
				// 詳細タグ
				case SEKAI_DTLTAG:
					echo ',';
					echo '"has_allowed_comment":"'.SEKAI_ALLOW_CMMT.'"';
					echo ',';
					echo '"tag_list":[';
					foreach ($this->ResultSet as $i => $data) {
						$uid = $SEKAI_UID[$data['CORP_ID']];
						$id = kyotenId2sekaiId($uid, $data['KYOTEN_ID']);
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
						$altitude = '0';
						$w_ymd = $data['INS_DT_YMD'];
						$w_tim = $data['INS_DT_TIM'];
						$created = $w_ymd[0].' '.$w_ymd[1].'/'.$w_ymd[2].' '.$w_tim[0].':'.$w_tim[1].':'.$w_tim[2];
						$w_ymd = $data['UPD_DT_YMD'];
						$w_tim = $data['UPD_DT_TIM'];
						$modified = $w_ymd[0].' '.$w_ymd[1].'/'.$w_ymd[2].' '.$w_tim[0].':'.$w_tim[1].':'.$w_tim[2];
						$text = $data['NAME'];
						for ($c = 0; $c < 201; $c++) {
							if (!isset($data["C$c"])) break;
							$text .= $this->LineSepEsc.$data["C$c"];
						}
						$text .= $this->LineSepEsc.$SEKAI_EMAPURL[$uid].$data['KYOTEN_ID'];
						if ($i > 0) echo ',';
						// 詳細タグ１（画像）
						echo '{';
						echo '"user_id":"'.$uid.'"';
						echo ',';
						echo '"id":"'.$id.'"';
						echo ',';
						echo '"content":"'.$SEKAI_IMGURL[$uid]['DTL'].'"';
						echo ',';
						echo '"lat":"'.$lat.'"';
						echo ',';
						echo '"lon":"'.$lon.'"';
						echo ',';
						echo '"altitude":"'.$altitude.'"';
						echo ',';
						echo '"attribute":"200"';
						echo ',';
						echo '"created":"'.$created.'"';
						echo ',';
						echo '"modified":"'.$modified.'"';
						echo ',';
						echo '"profile_name":"'.f_enc_convert($this->escapeJSON($SEKAI_PROFILE_NAME[$uid])).'"';
						echo ',';
						echo '"profile_image_url":"'.$SEKAI_IMGURL[$uid]['PRF'].'"';
						echo '}';
						// 詳細タグ２（テキスト情報）
						echo ',';
						echo '{';
						echo '"user_id":"'.$uid.'"';
						echo ',';
						echo '"id":"'.$id.'"';
						echo ',';
						echo '"content":"'.f_enc_convert($this->escapeJSON($text)).'"';
						echo ',';
						echo '"lat":"'.$lat.'"';
						echo ',';
						echo '"lon":"'.$lon.'"';
						echo ',';
						echo '"altitude":"'.$altitude.'"';
						echo ',';
						echo '"attribute":"100"';
						echo ',';
						echo '"created":"'.$created.'"';
						echo ',';
						echo '"modified":"'.$modified.'"';
						echo ',';
						echo '"profile_name":"'.f_enc_convert($this->escapeJSON($SEKAI_PROFILE_NAME[$uid])).'"';
						echo ',';
						echo '"profile_image_url":"'.$SEKAI_IMGURL[$uid]['PRF'].'"';
						echo '}';
					}
					echo ']';
					break;
			}
		}
		KyotenCgiOutput::output_body_end();
	}
}

?>
