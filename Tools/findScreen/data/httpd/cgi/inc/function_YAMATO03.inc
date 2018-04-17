<?php
/*=========================================================*/
// �ե�����̾��function_YAMATO03.inc
//
// ��ޥȱ�͢ŹƬ����API��YAMATO03�ۥ������ޥ����ؿ�
//
// ��������
// 2016/10/19 Y.Matsukawa	��������
/*=========================================================*/
class YAMATO03 {
	var $YTC = '';
	var $SKBN = '';
	var $YMD = '';
	var $DLV = '';
	var $DYMD_SYS_FULL = '';
	var $DYMD_SYS = array();
	var $DYMD_YMD_FULL = '';
	var $DYMD_YMD = array();
	var $YTC_KYMD_INNER = '';
	var $YTC_KYMD_OUTER = '';
	var $SHP_KYMD_INNER = '';
	var $SHP_KYMD_OUTER = '';

	function YAMATO03($ytc, $skbn, $ymd, $dlv) {
		$this->YTC = $ytc;
		$this->SKBN = $skbn;
		$this->YMD = $ymd;
		$this->DLV = $dlv;
		$this->DYMD_SYS_FULL = date('YmdHi');
		//$this->DYMD_SYS_FULL = '201611101700';//����Debug����
		$this->DYMD_SYS['YMD'] = substr($this->DYMD_SYS_FULL, 0, 8);
		$this->DYMD_SYS['HM'] = substr($this->DYMD_SYS_FULL, 8, 4);
		$this->DYMD_YMD_FULL = $ymd;
		if ($this->DYMD_YMD_FULL != '') {
			$this->DYMD_YMD_FULL = $this->YMD;
			$this->DYMD_YMD['YMD'] = substr($this->DYMD_YMD_FULL, 0, 8);
			$this->DYMD_YMD['HM'] = substr($this->DYMD_YMD_FULL, 8, 4);
		}
		//----------------------------------------------------------
		// �����ǽ����
		//----------------------------------------------------------
		//------------------
		// ���ꥢ��
		//------------------
		// YMD���ꤢ��
		if ($this->YMD != '') {
			// �����ƥ����� < YMD����07:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'0700') {
				// ���إ��ꥢ
				if ($this->DLV == '1' || $this->DLV == '') {
					$this->DYMD_INNER = $this->DYMD_YMD['YMD'].'14';// YMD����14���ʹ�
				// ���إ��ꥢ�ʳ�
				} else {
					$this->DYMD_INNER = $this->DYMD_YMD['YMD'].'19';// YMD����19���ʹ�
				}
			// �����ƥ����� < YMD����14:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'1400') {
				$this->DYMD_INNER = $this->DYMD_YMD['YMD'].'19';// YMD����19���ʹ�
			// �����ƥ����� < YMD����24:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'2400') {
				$this->DYMD_INNER = self::dayPlus($this->DYMD_YMD['YMD']).'14';// YMD����14���ʹ�
			// �����ƥ����� < �����ƥ���������07:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'0700') {
				$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'14';// �����ƥ���������14���ʹ�
			// �����ƥ����� < �����ƥ���������14:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1400') {
				$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'19';// �����ƥ���������19���ʹ�
			// �����ƥ����� < �����ƥ���������24:00
			} else {
				$this->DYMD_INNER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// �����ƥ���������14���ʹ�
			}
		// YMD����ʤ�
		} else {
			// �����ƥ����� < �����ƥ���������07:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'0700') {
				// ���إ��ꥢ
				if ($this->DLV == '1' || $this->DLV == '') {
					$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'14';// �����ƥ���������14���ʹ�
				// ���إ��ꥢ�ʳ�
				} else {
					$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'19';// �����ƥ���������19���ʹ�
				}
			// �����ƥ����� < �����ƥ���������14:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1400') {
				$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'19';// �����ƥ���������19���ʹ�
			// �����ƥ����� < �����ƥ���������24:00
			} else {
				$this->DYMD_INNER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// �����ƥ���������14���ʹ�
			}
		}
		//------------------
		// ���ꥢ��
		//------------------
		// YMD���ꤢ��
		if ($this->YMD != '') {
			// �����ƥ����� < YMD����17:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'1700') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_YMD['YMD']).'14';// YMD����14���ʹ�
			// �����ƥ����� < YMD����24:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'2400') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_YMD['YMD'], 2).'14';// YMD�⡹��14���ʹ�
			// �����ƥ����� < �����ƥ���������17:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1700') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// �����ƥ���������14���ʹ�
			// �����ƥ����� < �����ƥ���������24:00
			} else {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD'], 2).'14';// �����ƥ������⡹��14���ʹ�
			}
		// YMD����ʤ�
		} else {
			// �����ƥ����� < �����ƥ���������17:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1700') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// �����ƥ���������14���ʹ�
			// �����ƥ����� < �����ƥ���������24:00
			} else {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD'], 2).'14';// �����ƥ������⡹��14���ʹ�
			}
		}
		//----------------------------------------------------------
		// �ݴɴ�����
		//----------------------------------------------------------
		$inner_ymd = substr($this->DYMD_INNER, 0, 8);
		$outer_ymd = substr($this->DYMD_OUTER, 0, 8);
		// ľ��Ź�ʥ������ء�
		if ($this->SKBN == '1') {
			$this->YTC_KYMD_INNER = self::dayPlus($this->DYMD_YMD['YMD'], 2);
			$this->YTC_KYMD_OUTER = self::dayPlus($this->DYMD_YMD['YMD'], 2);
		// ľ��Ź�ʥ������ذʳ���
		}else {
			$this->YTC_KYMD_INNER = self::dayPlus($inner_ymd, 6);
			$this->YTC_KYMD_OUTER = self::dayPlus($outer_ymd, 6);
		}
		// �谷Ź
		$this->SHP_KYMD_INNER = self::dayPlus($inner_ymd, 2);
		$this->SHP_KYMD_OUTER = self::dayPlus($outer_ymd, 2);
	}

	// �����ǽ��������
	function getRcvDate(&$kyoten) {
		switch ($kyoten['COL_01']) {
			case '1':
				if ($kyoten['KYOTEN_ID'] === $this->YTC) {
					return $this->DYMD_INNER;
				} else {
					return $this->DYMD_OUTER;
				}
				break;
			case '2':
				if ($kyoten['COL_11'] === $this->YTC) {
					return $this->DYMD_INNER;
				} else {
					return $this->DYMD_OUTER;
				}
		}
		return '';
	}

	// �ݴɴ���������
	function getKeepDate(&$kyoten) {
		switch ($kyoten['COL_01']) {
			case '1':
				if ($kyoten['KYOTEN_ID'] === $this->YTC) {
					return $this->YTC_KYMD_INNER;
				} else {
					return $this->YTC_KYMD_OUTER;
				}
				break;
			case '2':
				if ($kyoten['COL_11'] === $this->YTC) {
					return $this->SHP_KYMD_INNER;
				} else {
					return $this->SHP_KYMD_OUTER;
				}
		}
		return '';
	}

	// �����û�
	static function dayPlus($ymd, $plus=1) {
		$y = substr($ymd, 0, 4);
		$m = substr($ymd, 4, 2);
		$d = substr($ymd, 6, 2);
		return date('Ymd', mktime(0, 0, 0, $m, $d+$plus, $y));
	}
}
?>