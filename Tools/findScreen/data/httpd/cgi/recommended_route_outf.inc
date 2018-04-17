<?php
/*********************************************************************/
// 更新履歴：
// 2016/01/20 T.Yoshino	新規作成
/*********************************************************************/
//-----------------------------------------------------------
// XML出力クラス
//-----------------------------------------------------------

class ReccRouteCgiOutput extends KyotenCgiOutput {

	/*==============================================*/
	// コンストラクタ
	/*==============================================*/
	function StoreKyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf) {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf);
	}

	/*==============================================*/
	// 出力
	/*==============================================*/
	function output($cid, $id, $pflg, $arr_item, $arr_kyoten, $arr_item_val) {
		global $D_RD_CGI;			// add 2013/03/11 Y.Matsukawa
		global $D_RD_VAL_KBN;		// add 2013/03/11 Y.Matsukawa

		// d_serv_emap.incにて上書きされないよう退避
		$tmp_cid = $cid;		// add 2013/12/20 H.Osamoto

		/*==============================================*/
		// 定義ファイル
		/*==============================================*/
		include('d_serv_emap.inc');
	
		// 上書きされた企業IDを元に戻す
		$cid = $tmp_cid;		// add 2013/12/20 H.Osamoto

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
				
				/* store_listの １アイテムの設定の開始  */
				$this->set_store_item_start($i);
				
				/* 拠点IDの設定  */
				if(isset($id)) {
					$kyotenid = $id;
				} else {
					$kyotenid = $data['KYOTEN_ID'];
				}

				/* item タグの開始 */
				$this->set_item_start($i);

				/* lat lon */
				$this->set_lat_lon($pflg, $data);
				
				/* distance */
				$this->set_distance($data);

				/* item タグの終了 */
				$this->set_item_end();
				
				/* item_listの １アイテムの設定の終了  */
				$this->set_store_item_end();

			}

			/* item_list タグの終了 */
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
		switch ($this->Outf) {
			case 'XML':
				if(strlen($element) > 0) {
					$format = '<%s>%s</%s>'.$this->LineSep;
					$lineString = sprintf($format, $tag, f_enc_convert($this->escapeXML($element)), $tag);

				} else {
					$format = '<%s />' .$this->LineSep;
					$lineString = sprintf($format, $tag);
				}
				break;
			case 'JSON':
				$format = '"%s":"%s",';
				$lineString = sprintf($format, $tag, f_enc_convert($this->escapeJSON($element)));
				break;
			default:
				break;
		}
		return  $lineString;
	}


	/*==============================================*/
	// １要素を作成(最後の要素の場合)
	/*==============================================*/
	function make_last_element($tag, $element) {
		
		$lineString = '';

		switch ($this->Outf) {
			case 'XML':
				if(strlen($element) > 0) {
					$format = '<%s>%s</%s>'.$this->LineSep;
					$lineString = sprintf($format, $tag, f_enc_convert($this->escapeXML($element)), $tag);
				} else {
					$format = '<%s />';
					$lineString = sprintf($format, $tag);
				}
				break;
			case 'JSON':
				$format = '"%s":"%s"';
				$lineString = sprintf($format, $tag, f_enc_convert($this->escapeJSON($element)));
				break;
			default:
				break;
		}
		return  $lineString;
	}


	/*==============================================*/
	// "item_list"の開始 タグを生成する
	/*==============================================*/
	function set_store_list_start() {

		if ($this->Outf == 'XML') {
			echo '<item_list>'.$this->LineSep;
		} else {
			echo ',"item_list":';
			echo '[';
		}

		return;
	}

	/*==============================================*/
	// "item_list"の終了 タグを生成する
	/*==============================================*/
	function set_store_list_end() {

		if ($this->Outf == 'XML') {
			echo '</item_list>'.$this->LineSep;
		} else {
			echo ']';
		}

		return;
	}
	
	/*==============================================*/
	// store_listの １アイテムの設定の開始
	/*==============================================*/
	function set_store_item_start($i) {
		
		if ($this->Outf == 'JSON') {
			
			if($i == 1) {
				echo '{';
			} else {
				echo ',{';
			}
		}
	}
	
	/*==============================================*/
	// store_listの １アイテムの設定の終了
	/*==============================================*/
	function set_store_item_end() {
		
		if ($this->Outf == 'JSON') {
			echo '}';
		}
	}


	/*==============================================*/
	// "item"の開始 タグを生成する
	/*==============================================*/
	function set_item_start($i) {
		if ($this->Outf == 'XML') {
			echo sprintf('<item id="%d">', $i).$this->LineSep;
		}

		return;
	}

	/*==============================================*/
	// "item"の終了 タグを生成する
	/*==============================================*/
	function set_item_end() {
		if ($this->Outf == 'XML') {
			echo '</item>'.$this->LineSep;
		}

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

}

?>
