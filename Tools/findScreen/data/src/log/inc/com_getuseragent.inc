<?php
// ------------------------------------------------------------
// 2011/10/06 Y.Nakajima	FireFox,safari 判定追加
// ------------------------------------------------------------

function com_getuseragent($user_agent) {
    $agent ='none';
	// ie
	if(strpos($user_agent, 'MSIE 8')) {
		$agent ='MSIE8';
	}
	if(strpos($user_agent, 'MSIE 7')) {
		$agent ='MSIE7';
	}
	if(strpos($user_agent ,'MSIE 6')) {
		$agent ='MSIE6';
	}

	// firefox
	if(strpos($user_agent ,'Firefox/7.0')) {
		$agent ='FFOX70';
	}
	if(strpos($user_agent ,'Firefox/6.0')) {
		$agent ='FFOX60';
	}
	if(strpos($user_agent ,'Firefox/5.0')) {
		$agent ='FFOX50';
	}
	if(strpos($user_agent ,'Firefox/4.0')) {
		$agent ='FFOX40';
	}
	if(strpos($user_agent ,'Firefox/3.6')) {
		$agent ='FFOX36';
	}
	if(strpos($user_agent ,'Firefox/3.5')) {
		$agent ='FFOX30';
	}
	if(strpos($user_agent ,'Firefox/3.0')) {
		$agent ='FFOX30';
	}
	if(strpos($user_agent ,'Firefox/2.0')) {
		$agent ='FFOX20';
	}
	if(strpos($user_agent ,'Firefox/1.5')) {
		$agent ='FFOX15';
	}

	// safari
	if(strpos($user_agent ,'AppleWebKit/5') && strpos($user_agent ,'Version/5')) {
		$agent ='SAFA5';
	} else if(strpos($user_agent ,'AppleWebKit/5') && strpos($user_agent ,'Version/4')) {
		$agent ='SAFA4';
	} else if(strpos($user_agent ,'AppleWebKit/5') && strpos($user_agent ,'Version/3')) {
		$agent ='SAFA3';
	} else if(strpos($user_agent ,'AppleWebKit/41')) {
		$agent ='SAFA2';
	}

	// chrome
	if(strpos($user_agent ,'AppleWebKit/5') && strpos($user_agent ,'Chrome')) {
		$agent ='CHROME';
	}

	// Netscape
	if(strpos($user_agent ,'Netscape/7.01')) {
		$agent ='NS701';
	}
	if(strpos($user_agent ,'Netscape/7.1')) {
		$agent ='NS71';
	}
	return $agent;
}
?>
