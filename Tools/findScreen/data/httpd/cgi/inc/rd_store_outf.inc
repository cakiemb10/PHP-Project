<?php
/*========================================================*/
// 更新履歴：
// 2013/02/20 Y.Matsukawa	新規作成
/*========================================================*/
//-----------------------------------------------------------
// XML出力クラス
//-----------------------------------------------------------

class RdStoreCgiOutput extends RdCgiOutput {

	/*==============================================*/
	// コンストラクタ
	/*==============================================*/
	function RdStoreCgiOutput($cgicd, $cginm, $enc, $outf) {
		RdCgiOutput::RdCgiOutput($cgicd, $cginm, $enc, $outf);
	}

	/*==============================================*/
	// 出力
	/*==============================================*/
	function output($cid, &$arr_kyoten) {
		global $D_RD_CGI;
		global $D_RD_VAL_KBN;

		/*==============================================*/
		// 定義ファイル
		/*==============================================*/
		include('d_serv_emap.inc');

		/*==============================================*/
		// ステータス部 出力
		/*==============================================*/
		RdCgiOutput::output_header();
		RdCgiOutput::output_body_start();
		RdCgiOutput::output_status();

		/*==============================================*/
		// 検索データ部  出力
		/*==============================================*/
		if (is_array($arr_kyoten) && count($arr_kyoten)) {
			// store_count
			$this->output_sep();
			$this->output_hash_item('store_count', count($arr_kyoten));
			// store_list開始
			$this->output_sep();
			$this->output_list_start('store_list');
			$k = 0;
			foreach ($arr_kyoten as $kid=>$kyoten) {
				$k++;
				if ($k > 1) $this->output_sep();
				// store開始
				$this->output_hash_start('store', $k);
				// store_id
				//$kid = $kyoten['KYOTEN_ID'];
				$this->output_hash_item('store_id', $kid);
				// group_count
				$arr_group = $kyoten['GROUP_LIST'];
				$this->output_sep();
				$this->output_hash_item('group_count', count($arr_group));
				// group_list開始
				$this->output_sep();
				$this->output_list_start('group_list');
				$g = 0;
				foreach ($arr_group as $gid=>$arr_item) {
					$g++;
					if ($g > 1) $this->output_sep();
					// group開始
					$this->output_hash_start('group', $g);
					// group_id
					//$gid = $group['GROUP_NO'];
					$this->output_hash_item('group_id', $gid);
					// item_count
					//$arr_item = $group['ITEM_LIST'];
					$this->output_sep();
					$this->output_hash_item('item_count', count($arr_item));
					// item_list開始
					$this->output_sep();
					$this->output_list_start('item_list');
					$i = 0;
					foreach ($arr_item as $iid=>$item) {
						$i++;
						if ($i > 1) $this->output_sep();
						// item開始
						$this->output_hash_start('item', $i);
						// item_id
						//$iid = $group['ITEM_NO'];
						$this->output_hash_item('item_id', $iid);
						// type
						$val_kbn = $item['VAL_KBN'];
						$this->output_sep();
						$this->output_hash_item('type', $D_RD_VAL_KBN[$val_kbn]);
						switch ($val_kbn) {
							// テキスト項目の場合
							case 'T':
								$this->output_sep();
								$this->output_hash_item('text', $item['TXT_DATA']);
								break;
							// 画像項目の場合
							case 'I':
								// URL
								$img_url = $D_RD_CGI['rd_img'].'?cid='.$cid.'&kid='.$kid.'&grp='.$gid.'&itm='.$iid;
								$this->output_sep();
								$this->output_hash_item('img_url', $img_url);
								// 画像幅
								$this->output_sep();
								$this->output_hash_item('img_w', $item['IMG_W']);
								// 画像高さ
								$this->output_sep();
								$this->output_hash_item('img_h', $item['IMG_H']);
								break;
							// フラグ項目の場合
							case 'F':
								// フラグ値
								$flag = ($item['FLG_DATA']?$item['FLG_DATA']:'0');
								$this->output_sep();
								$this->output_hash_item('flag', $flag);
								// テキスト（項目名）
								$text = ($flag?$item['ITEM_NAME']:'');
								$this->output_sep();
								$this->output_hash_item('text', $text);
								break;
						}
						// item終了
						$this->output_hash_end('item');
					}
					// item_list終了
					$this->output_list_end('item_list');
					// group終了
					$this->output_hash_end('group');
				}
				// group_list終了
				$this->output_list_end('group_list');
				// store終了
				$this->output_hash_end('store');
			}
			// store_list終了
			$this->output_list_end('store_list');
		}

		RdCgiOutput::output_body_end();

		return;
	}

	/*==============================================*/
	// エラー時出力
	/*==============================================*/
	function err_output() {

		RdCgiOutput::output_header();
		RdCgiOutput::output_body_start();
		RdCgiOutput::output_status();

		RdCgiOutput::output_body_end();
	}

}

?>
