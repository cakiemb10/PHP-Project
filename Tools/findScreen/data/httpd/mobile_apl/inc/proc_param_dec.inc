<?PHP
//==============================================================================
// �ѥ�᡼�����־��������J-PHONE2���ʤ�.HTM������Ȥ���ǧ�����ʤ�ü���б���
// �嵭��������ξ�硢URL��http://SERVER/mi.htm/pos=xxxxxxx/a.png�Ȥʤ뤿�ᡢ
// �ޤ������־�����������Ƥ�����⡢�嵭�Σգң̤Ȥ��Ƥ��롣
// htm/�ʹߤ�ѥ�᡼���Ȥ��Ƽ�������
//
// 2009/03/17 Y.Matsukawa	���Զ�罤���۰�������Ǹ����ϼ�������ȡ�nm�ѥ�᡼����������礬����
//                           ��nm�ѥ�᡼����EUC���Ϥ��Ƥ����Τ�SJIS���Ϥ��褦����
//                           ����&�ס�?�ס�/�פ��ޤޤ�Ƥ���Ȥ��ΰ��֤��ڤ�Ƥ��ޤ��Τǡ�������ɡ�_A_�ס�_Q_�ס�_S_�פ��ִ�����
// 2009/06/15 Y.Matsukawa	opt�ѥ�᡼���򤺤äȰ����Ѥ�
// 2011/07/05 Y.Nakajima	VM����ȼ��apache,phpVerUP�б�����
// 2011/08/11 H.Osamoto		���Զ�罤����au�Ǹ����ϼ�������ȡ�nm�ѥ�᡼����������礬����
//                           ���� �ס�Ⱦ�ѥ��ڡ����ˤ��ޤޤ�Ƥ���Ȥ��ΰ��֤��ڤ�Ƥ��ޤ��Τǡ�������ɡ�_B_�פ��ִ�����
// 2015/06/12 Y.Matsukawa	au�θ����ϼ����塢setting_option��ǥѥ�᡼���������Ǥ��ʤ�
//==============================================================================
$REQUEST_URI = (isset($_SERVER['REQUEST_URI'])?$_SERVER['REQUEST_URI']:"");		// add 2015/06/12 Y.Matsukawa
if(strpos($REQUEST_URI,".htm/") > -1){
	//dbl("REQUEST[$REQUEST_URI]");		del 2015/06/12 Y.Matsukawa
	$prm = substr($REQUEST_URI, strpos($REQUEST_URI,".htm/")+5, strlen($REQUEST_URI));
	// mod 2011/07/05 Y.Nakajima
	//$wk = split("(&|\/|\?)", $prm);
	$wk = preg_split("/[\&\/\?]+/", $prm);

	foreach($wk as $value){
		// mod 2011/07/05 Y.Nakajima
		//$prm = split("=", $value);
		$prm = explode("=", $value);
		if(count($prm) == 2){
			if($prm[0] == "pos"){
				if(strpos($prm[1], ".") > -1){
					$pos_ll = $prm[1];
				} else {
					$pos_enc = $prm[1];
				}
			}
			// add 2009/03/17 Y.Matsukawa [
			//if($prm[0] == "nm"){		mod 2009/07/15 Y.Matsukawa
			if($prm[0] == "nm" || $prm[0] == "nm2" || $prm[0] == "tel" || $prm[0] == "cm" || $prm[0] == "t" || $prm[0] == "a"){
				if(strpos($prm[1], '_A_') > -1){
					$prm[1] = str_replace('_A_', '%26', $prm[1]);
				}
				if(strpos($prm[1], '_Q_') > -1){
					$prm[1] = str_replace('_Q_', '%3F', $prm[1]);
				}
				if(strpos($prm[1], '_S_') > -1){
					$prm[1] = str_replace('_S_', '%2F', $prm[1]);
				}
				// add 2011/08/11 H.osamoto [
				if(strpos($prm[1], '_B_') > -1){
					$prm[1] = str_replace('_B_', '%20', $prm[1]);
				}
				// add 2011/08/11 H.osamoto ]
			}
			// add 2009/03/17 Y.Matsukawa ]
			$$prm[0] = $prm[1];
			$_GET[$prm[0]] = $prm[1];
		// add 2009/06/15 Y.Matsukawa [
		// opt�ѥ�᡼�����б�
		// ��opt=COL_01=02�ס�opt=COL_01=02@COL_02=1��
		} else if (count($prm) > 2) {
			if ($prm[0] == "opt") {
				array_shift(&$prm);
				$prm = implode('=', $prm);
				$opt = $prm;
			}
		// add 2009/06/15 Y.Matsukawa ]
		}
	}
// add 2009/03/17 Y.Matsukawa [
} else {
	// mod 2011/07/05 Y.Nakajima [
	//$wk = split("(&|\/|\?)", $prm);
	if (isset($prm) && $prm != "") {
		$wk = explode($prm, "(&|\/|\?)");
	// mod 2011/07/05 Y.Nakajima ]

	foreach($wk as $value){
		// mod 2011/07/05 Y.Nakajima
		//$prm = split("=", $value);
		$prm = explode("=", $value);
		if(count($prm) == 2){
			//if($prm[0] == "nm"){		mod 2009/07/15 Y.Matsukawa
			if($prm[0] == "nm" || $prm[0] == "nm2" || $prm[0] == "tel" || $prm[0] == "cm" || $prm[0] == "t" || $prm[0] == "a"){
				if(strpos($prm[1], '_A_') > -1){
					$prm[1] = str_replace('_A_', '%26', $prm[1]);
				}
				if(strpos($prm[1], '_Q_') > -1){
					$prm[1] = str_replace('_Q_', '%3F', $prm[1]);
				}
				if(strpos($prm[1], '_S_') > -1){
					$prm[1] = str_replace('_S_', '%2F', $prm[1]);
				}
				// add 2011/08/11 H.osamoto [
				if(strpos($prm[1], '_B_') > -1){
					$prm[1] = str_replace('_B_', '%20', $prm[1]);
				}
				// add 2011/08/11 H.osamoto ]
				$$prm[0] = $prm[1];
				$_GET[$prm[0]] = $prm[1];
			}
		// add 2009/06/15 Y.Matsukawa [
		// opt�ѥ�᡼�����б�
		// ��opt=COL_01=02�ס�opt=COL_01=02@COL_02=1��
		} else if (count($prm) > 2) {
			if ($prm[0] == "opt") {
				array_shift(&$prm);
				$prm = implode('=', $prm);
				$opt = $prm;
			}
		// add 2009/06/15 Y.Matsukawa ]
		}
	}
	// mod 2011/07/05 Y.Nakajima [
	} else {
		
	}
	// mod 2011/07/05 Y.Nakajima ]

// add 2009/03/17 Y.Matsukawa ]
}
?>