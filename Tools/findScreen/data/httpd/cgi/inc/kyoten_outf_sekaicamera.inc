<?php
/**********************************************************************
// ��������
// 2010/01/08 Y.Matsukawa	��������
// 2010/01/25 Y.Matsukawa	���Ϲ����ɲá�created,modified,comment_count��
/*********************************************************************/
//-----------------------------------------------------------
// JSON���ϥ��饹
//-----------------------------------------------------------
class KyotenCgiOutputJSON extends KyotenCgiOutput {
	var $TagType = '';
	//-------------------------------------------
	// ���󥹥ȥ饯��
	//-------------------------------------------
	function KyotenCgiOutputJSON($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $type) {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, 'JSON');
		$this->TagType = $type;
	}
	//-------------------------------------------
	// output
	// ����
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
				// ��������
				case SEKAI_AIRTAG:
					echo ',';
					echo '"tag_list":[';
					foreach ($this->ResultSet as $i => $data) {
						$uid = $SEKAI_UID[$data['CORP_ID']];
						$id = kyotenId2sekaiId($uid, $data['KYOTEN_ID']);
						$lat = $data['LAT'];
						$lon = $data['LON'];
						if ($this->Pflg == '1') {
							// �ߥ��â���
							$lat = cnv_dms2hour($lat);
							$lon = cnv_dms2hour($lon);
						} else if ($this->Pflg == '3') {
							// �ߥ��â���ʬ��
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
				// �ܺ٥���
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
							// �ߥ��â���
							$lat = cnv_dms2hour($lat);
							$lon = cnv_dms2hour($lon);
						} else if ($this->Pflg == '3') {
							// �ߥ��â���ʬ��
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
						// �ܺ٥������ʲ�����
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
						// �ܺ٥������ʥƥ����Ⱦ����
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