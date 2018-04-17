<?php
/*=========================================================*/
// �ե�����̾��function_ytc.inc
//
// ��ޥȱ�͢�������ޥ����ؿ�
//
// ��������
// 2016/10/19 Y.Matsukawa	��������
/*=========================================================*/
class YTC {
	// ------------------------------------------------------------
	// ATOKENǧ��
	// ------------------------------------------------------------
	static function authToken($atoken) {
		global $D_EMAP_ENV;
		global $D_YTC_AUTH_URL;
		// ����
		if ($D_EMAP_ENV == 'test' || $D_EMAP_ENV == 'dev') {
			global $D_APIPROXY;
			$host = $D_APIPROXY['HOST'].':'.$D_APIPROXY['PORT'];
			$headers = array(
				'Authorization: Bearer '.$atoken,   //ǧ������
			); 
			$options = array('http' => array(
				'method' => 'POST',
				'header' => implode("\r\n", $headers),
				'ignore_errors' => true,
				'proxy' => "tcp://$host",
				'request_fulluri' => true,
			));
			$contents = file_get_contents($D_YTC_AUTH_URL, false, stream_context_create($options));
			$dat = explode("\r\n\r\n",$contents);
		//����
		} else {
			$cmd = 'wget -O - --post-data="" --header="Authorization: Bearer '.$atoken.'" '.$D_YTC_AUTH_URL;
			exec($cmd, $dat);
		}
		if ($dat && is_array($dat)) {
			$xml_arr = LoadXML(&$dat[0]);
			$MSG_ID = GetXMLVal($xml_arr, "MSG_ID");
			return $MSG_ID;
		}
		return null;
	}
}

?>