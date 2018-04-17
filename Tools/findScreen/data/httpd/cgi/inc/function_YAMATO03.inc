<?php
/*=========================================================*/
// ファイル名：function_YAMATO03.inc
//
// ヤマト運輸店頭受取API【YAMATO03】カスタマイズ関数
//
// 更新履歴
// 2016/10/19 Y.Matsukawa	新規作成
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
		//$this->DYMD_SYS_FULL = '201611101700';//※※Debug※※
		$this->DYMD_SYS['YMD'] = substr($this->DYMD_SYS_FULL, 0, 8);
		$this->DYMD_SYS['HM'] = substr($this->DYMD_SYS_FULL, 8, 4);
		$this->DYMD_YMD_FULL = $ymd;
		if ($this->DYMD_YMD_FULL != '') {
			$this->DYMD_YMD_FULL = $this->YMD;
			$this->DYMD_YMD['YMD'] = substr($this->DYMD_YMD_FULL, 0, 8);
			$this->DYMD_YMD['HM'] = substr($this->DYMD_YMD_FULL, 8, 4);
		}
		//----------------------------------------------------------
		// 受取可能日時
		//----------------------------------------------------------
		//------------------
		// エリア内
		//------------------
		// YMD指定あり
		if ($this->YMD != '') {
			// システム日時 < YMD当日07:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'0700') {
				// １便エリア
				if ($this->DLV == '1' || $this->DLV == '') {
					$this->DYMD_INNER = $this->DYMD_YMD['YMD'].'14';// YMD当日14時以降
				// １便エリア以外
				} else {
					$this->DYMD_INNER = $this->DYMD_YMD['YMD'].'19';// YMD当日19時以降
				}
			// システム日時 < YMD当日14:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'1400') {
				$this->DYMD_INNER = $this->DYMD_YMD['YMD'].'19';// YMD当日19時以降
			// システム日時 < YMD当日24:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'2400') {
				$this->DYMD_INNER = self::dayPlus($this->DYMD_YMD['YMD']).'14';// YMD翌日14時以降
			// システム日時 < システム日付当日07:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'0700') {
				$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'14';// システム日付当日14時以降
			// システム日時 < システム日付当日14:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1400') {
				$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'19';// システム日付当日19時以降
			// システム日時 < システム日付当日24:00
			} else {
				$this->DYMD_INNER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// システム日付翌日14時以降
			}
		// YMD指定なし
		} else {
			// システム日時 < システム日付当日07:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'0700') {
				// １便エリア
				if ($this->DLV == '1' || $this->DLV == '') {
					$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'14';// システム日付当日14時以降
				// １便エリア以外
				} else {
					$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'19';// システム日付当日19時以降
				}
			// システム日時 < システム日付当日14:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1400') {
				$this->DYMD_INNER = $this->DYMD_SYS['YMD'].'19';// システム日付当日19時以降
			// システム日時 < システム日付当日24:00
			} else {
				$this->DYMD_INNER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// システム日付翌日14時以降
			}
		}
		//------------------
		// エリア外
		//------------------
		// YMD指定あり
		if ($this->YMD != '') {
			// システム日時 < YMD当日17:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'1700') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_YMD['YMD']).'14';// YMD翌日14時以降
			// システム日時 < YMD当日24:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_YMD['YMD'].'2400') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_YMD['YMD'], 2).'14';// YMD翌々日14時以降
			// システム日時 < システム日付当日17:00
			} else if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1700') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// システム日付翌日14時以降
			// システム日時 < システム日付当日24:00
			} else {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD'], 2).'14';// システム日付翌々日14時以降
			}
		// YMD指定なし
		} else {
			// システム日時 < システム日付当日17:00
			if ($this->DYMD_SYS_FULL < $this->DYMD_SYS['YMD'].'1700') {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD']).'14';// システム日付翌日14時以降
			// システム日時 < システム日付当日24:00
			} else {
				$this->DYMD_OUTER = self::dayPlus($this->DYMD_SYS['YMD'], 2).'14';// システム日付翌々日14時以降
			}
		}
		//----------------------------------------------------------
		// 保管期限日
		//----------------------------------------------------------
		$inner_ymd = substr($this->DYMD_INNER, 0, 8);
		$outer_ymd = substr($this->DYMD_OUTER, 0, 8);
		// 直営店（クール便）
		if ($this->SKBN == '1') {
			$this->YTC_KYMD_INNER = self::dayPlus($this->DYMD_YMD['YMD'], 2);
			$this->YTC_KYMD_OUTER = self::dayPlus($this->DYMD_YMD['YMD'], 2);
		// 直営店（クール便以外）
		}else {
			$this->YTC_KYMD_INNER = self::dayPlus($inner_ymd, 6);
			$this->YTC_KYMD_OUTER = self::dayPlus($outer_ymd, 6);
		}
		// 取扱店
		$this->SHP_KYMD_INNER = self::dayPlus($inner_ymd, 2);
		$this->SHP_KYMD_OUTER = self::dayPlus($outer_ymd, 2);
	}

	// 受取可能日時算出
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

	// 保管期限日算出
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

	// 日数加算
	static function dayPlus($ymd, $plus=1) {
		$y = substr($ymd, 0, 4);
		$m = substr($ymd, 4, 2);
		$d = substr($ymd, 6, 2);
		return date('Ymd', mktime(0, 0, 0, $m, $d+$plus, $y));
	}
}
?>
