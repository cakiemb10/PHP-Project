<?php
/*********************************************************************/
// 更新履歴：
// 2016/07/19 T.Yoshino		新規作成
/*********************************************************************/
//-----------------------------------------------------------
// XML出力クラス
//-----------------------------------------------------------

class StoreKyotenCgiOutput extends KyotenCgiOutput {

	/*==============================================*/
	// コンストラクタ
	/*==============================================*/
	
	function StoreKyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf, $cust="") {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf, $cust);
	}

	/*==============================================*/
	// 出力
	/*==============================================*/
	function output($cid, $id, $pflg, $arr_item, $arr_kyoten, $arr_item_val, $arr_img="", $arr_opt_flg="" ) {
		global $D_RD_CGI;			// add 2013/03/11 Y.Matsukawa
		global $D_RD_VAL_KBN;		// add 2013/03/11 Y.Matsukawa

		// d_serv_emap.incにて上書きされないよう退避
		$tmp_cid = $cid;		// add 2013/12/20 H.Osamoto

		/*==============================================*/
		// 定義ファイル
		/*==============================================*/
		include('d_serv_emap.inc');
	
		// 上書きされた企業IDを元に戻す
		$cid = $tmp_cid;

		/*==============================================*/
		// ステータス部 出力
		/*==============================================*/
		KyotenCgiOutput::output_header();
		KyotenCgiOutput::output_body_start();
		KyotenCgiOutput::output_status();

		/*==============================================*/
		// 検索データ部  出力
		/*==============================================*/
		if (is_array($arr_kyoten) && count($arr_kyoten)) {

			/* store_list タグの開始 */
			$this->set_store_list_start();
			foreach ($arr_kyoten as $i => $data) {
				
				/* store id */
				$this->set_store_id($data['COL_55']);

			}

			/* store_list タグの終了 */
			$this->set_store_list_end();
		}

		KyotenCgiOutput::output_body_end();
		
		return;
	}

	/*==============================================*/
	// エラー時出力
	/*==============================================*/
	function err_output() {

		KyotenCgiOutput::output_header();
		KyotenCgiOutput::output_body_start();
		KyotenCgiOutput::output_status();
		
		KyotenCgiOutput::output_body_end();
	}


	/*==============================================*/
	// １要素を作成
	/*==============================================*/
	function make_element($tag, $element) {
		$lineString = '';
		if(strlen($element) > 0) {
			$format = '<%s>%s</%s>'.$this->LineSep;
			$lineString = sprintf($format, $tag, f_enc_convert($this->escapeXML($element)), $tag);

		} else {
			$format = '<%s />' .$this->LineSep;
			$lineString = sprintf($format, $tag);
		}

		return  $lineString;
	}


	/*==============================================*/
	// １要素を作成(最後の要素の場合)
	/*==============================================*/
	function make_last_element($tag, $element) {
		
		$lineString = '';

		if(strlen($element) > 0) {
			$format = '<%s>%s</%s>'.$this->LineSep;
			$lineString = sprintf($format, $tag, f_enc_convert($this->escapeXML($element)), $tag);
		} else {
			$format = '<%s />';
			$lineString = sprintf($format, $tag);
		}

		return  $lineString;
	}


	/*==============================================*/
	// "store_list"の開始 タグを生成する
	/*==============================================*/
	function set_store_list_start() {

		echo '<store_list>'.$this->LineSep;

		return;
	}

	/*==============================================*/
	// "store_list"の終了 タグを生成する
	/*==============================================*/
	function set_store_list_end() {

		echo '</store_list>'.$this->LineSep;

		return;
	}
	
	
	/*==============================================*/
	// "item"の開始 タグを生成する
	/*==============================================*/
	function set_item_start($i) {
		echo sprintf('<item id="%d">', $i+1).$this->LineSep;

		return;
	}

	/*==============================================*/
	// "item"の終了 タグを生成する
	/*==============================================*/
	function set_item_end() {
		echo '</item>'.$this->LineSep;

		return;
	}

	
	/*==============================================*/
	// "store id" タグを生成する
	/*==============================================*/
	function set_store_id($id) {
		echo $this->make_element('store_id', $id);
		return;
	}

	/*==============================================*/
	// "lat" と "lon" タグを生成する
	/*==============================================*/
	function set_lat_lon($pflg, $data) {
		
		$lat;
		$lon;
				
		switch ($pflg)  {
			
			/* 十進緯度経度表記 */
			case '1':
				$lat = cnv_dms2hour($data['LAT']);
				$lon = cnv_dms2hour($data['LON']);
				break;

			/* ミリ秒緯度経度表記 */
			case '2':
				$lat = $data['LAT'];
				$lon = $data['LON'];
				break;

			/* 度分秒緯度経度表記 */
			case '3':				
				$lat = cnv_dms2deg($data['LAT']);
				$lon = cnv_dms2deg($data['LON']);
				break;

			default:
				brak;
		}

		echo $this->make_element('lat', $lat);
		echo $this->make_element('lon', $lon);
		
		return;
	}

	/*==============================================*/
	// "distance" タグを生成する
	/*==============================================*/
	function set_distance($data) {
	
		if(isset($data['KYORI'])) {
			echo $this->make_element('distance', $data['KYORI']);
		}
		return;
	}

	/*==============================================*/
	// "new" タグを生成する
	/*==============================================*/
	function set_new($data) {
		echo $this->make_element('new', $data['BFLG']);

		return;
	}

	/*==============================================*/
	// "icon_url" タグを生成する
	/*==============================================*/
	function set_icon_url($cid, $data, $D_SSAPI) {

		$icon_url = sprintf("%s?cid=%s&icon_id=%s", $D_SSAPI["icon_select_g"], $cid, $data['ICON_ID']);
		echo $this->make_element('icon_url', $icon_url);

		return;
	}

	/*==============================================*/
	// "img_url" タグを生成する
	/*==============================================*/
	function set_img_url($cid, $id, $data, $D_SSAPI) {
		// mod 2014/10/29 H.Osamoto [
		//	$img_url = sprintf("%s?cid=%s&kid=%s", $D_SSAPI["gif_select"], $cid, $id);
		if($data['K_GIF_NUM'] == "1") {
			$img_url = sprintf("%s?cid=%s&kid=%s", $D_SSAPI["gif_select"], $cid, $id);
		} else {
			$img_url = "";
		}
		// mod 2014/10/29 H.Osamoto ]
		echo $this->make_element('img_url', $img_url);

		return;
	}

	/*==============================================*/
	// "pc_map_url" タグを生成する add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_pc_map_url($cid, $kyotenid, $D_DOMAIN_G) {

		$set_d_url = (empty($_SERVER["HTTPS"]) ? "http://" : "https://") . $D_DOMAIN_G;
		$pc_map_url = sprintf("%s/p/%s/dtl/%s/", $set_d_url, $cid, $kyotenid);
		echo $this->make_element('pc_map_url', $pc_map_url);

		return;
	}

	/*==============================================*/
	// "smt_map_url" タグを生成する add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_smt_map_url($cid, $kyotenid, $D_DOMAIN_G) {

		$set_d_url = (empty($_SERVER["HTTPS"]) ? "http://" : "https://") . $D_DOMAIN_G;
		$smt_map_url = sprintf("%s/smt/%s/map/%s/", $set_d_url, $cid, $kyotenid);
		echo $this->make_element('smt_map_url', $smt_map_url);

		return;
	}

	/*==============================================*/
	// "img_url1"〜"img_url5" タグを生成する add 2016/01/28  T.Yoshino
	/*==============================================*/
	function set_img_url_multi($cid, $id, $data, $D_SSAPI) {

		for ( $i=1; $i <= $data['CNT']; $i++ ) {
			$img_tag = sprintf("img_url%s", $i);
			if($data[$i]['IMG_NO'] == $i) {
				$img_url = sprintf("%s?cid=%s&kid=%s&no=%s", $D_SSAPI['img_select'], $cid, $id, $data[$i]['IMG_NO']);
			} else {
				$img_url = "";
			}

			echo $this->make_element($img_tag, $img_url);
		}
		
		return;
	}


	/*==============================================*/
	// "site_id" タグを生成する add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_site_id($site_id) {
		echo $this->make_element('site_id', $site_id);

		return;
	}

	/*==============================================*/
	// "f" タグを生成する add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_f_tag($f) {
		echo $this->make_element('f', $f);

		return;
	}
	
	/*==============================================*/
	// "content"の開始 タグを生成する
	/*==============================================*/
	function set_content_start() {
		echo '<content>'.$this->LineSep;

		return;
	}
	
	/*==============================================*/
	// "content"の終了 タグを生成する
	/*==============================================*/
	function set_content_end() {
		echo '</content>'.$this->LineSep;

		return;
	}

	/*==============================================*/
	// "col"の開始 タグを生成する
	/*==============================================*/
	function set_col_start($i, $item) {
		echo sprintf('<col id="item%d_%s">', $i+1, f_enc_convert($this->escapeXML($item['COL_NAME'])));

		return;
	}
	
	/*==============================================*/
	// "col"の終了 タグを生成する
	/*==============================================*/
	function set_col_end() {
		echo '</col>'.$this->LineSep;

		return;
	}

	/*==============================================*/
	// "col"の終了 タグを生成する(最後の要素の場合)
	/*==============================================*/
	function set_last_col_end() {
		echo '</col>'.$this->LineSep;
	
		return;
	}
	

	/*==============================================*/
	// "match_rank" タグを生成する
	/*==============================================*/
	function set_name($item) {
		echo $this->make_element('match_rank', $item['M_LEVEL']);

		return;
	}
	
	
	/*==============================================*/
	// "type" 別に、各タグ(text, code, flg)を生成する
	/*==============================================*/
	function set_type($item, $data, $arr_item_val) {
	
		/* type */
		switch ($item['VAL_KBN'])  {
			
			/* type = TEXT */
			case 'C':
				echo $this->make_element('type', 'TEXT');
				echo $this->make_last_element('text', $data[$item['COL_NAME']]);
				break;
				
			/* type = CODE */
			case 'L':
				echo $this->make_element('type', 'CODE');
				echo $this->make_element('code', $data[$item['COL_NAME']]);

				$text = $arr_item_val[$item['COL_NAME']];
				echo $this->make_last_element('text', $text[$data[$item['COL_NAME']]][ITEM_VAL_NAME]);
				break;
				
			/* type = FLAG */
			case 'B':
				echo $this->make_element('type', 'FLAG');
				echo $this->make_element('flag', $data[$item['COL_NAME']]);
				
				if($data[$item['COL_NAME']] == '1') {
					echo $this->make_last_element('text', $item['ITEM_NAME']);
				} else {
					echo $this->make_last_element('text', '');
				}
				break;

			default:
				break;
		}
		return;
	}
}

?>
