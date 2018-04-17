<?php
/*********************************************************************/
// ��������
// 2011/12/16 H.Nakamura	��������
// 2013/03/11 Y.Matsukawa	�ꥢ�륿����ǡ���
// 2014/10/29 H.Osamoto		�������������Զ�罤��
// 2016/01/28 T.Yoshino		����������ʣ���ξ��ι�θ���ɲ�
// 2016/04/28 T.Yoshino		���Ϲ��ܤ��ɲ�
// 2016/10/19 Y.Matsukawa	��ޥȱ�͢����ŹƬ����API��ytc_store_nearsearch.cgi���б�
// 2016/12/12 H.Yasunaga	��ޥȥ��å����б� �쥹�ݥ󥹤Υ������ɲ�
/*********************************************************************/
//-----------------------------------------------------------
// XML���ϥ��饹
//-----------------------------------------------------------

class StoreKyotenCgiOutput extends KyotenCgiOutput {

	/*==============================================*/
	// ���󥹥ȥ饯��
	/*==============================================*/
	
	// mod 2016/04/28 T.Yoshino [
	function StoreKyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf, $cust="") {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf, $cust);
	}
	// mod 2016/04/28 T.Yoshino ]
	
//	function StoreKyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf) {
//		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf);
//	}

	/*==============================================*/
	// ����
	/*==============================================*/
	//function output($cid, $id, $pflg, $arr_item, $arr_kyoten, $arr_item_val) {					// mod 2016/01/28 T.Yoshino
	//function output($cid, $id, $pflg, $arr_item, $arr_kyoten, $arr_item_val, $arr_img="") {		// mod 2016/04/28 T.Yoshino
	function output($cid, $id, $pflg, $arr_item, $arr_kyoten, $arr_item_val, $arr_img="", $arr_opt_flg="" ) {
		global $D_RD_CGI;			// add 2013/03/11 Y.Matsukawa
		global $D_RD_VAL_KBN;		// add 2013/03/11 Y.Matsukawa

		// d_serv_emap.inc�ˤƾ�񤭤���ʤ��褦����
		$tmp_cid = $cid;		// add 2013/12/20 H.Osamoto

		/*==============================================*/
		// ����ե�����
		/*==============================================*/
		include('d_serv_emap.inc');
	
		// ��񤭤��줿���ID�򸵤��᤹
		$cid = $tmp_cid;		// add 2013/12/20 H.Osamoto

		/*==============================================*/
		// ���ơ������� ����
		/*==============================================*/
		KyotenCgiOutput::output_header();
		KyotenCgiOutput::output_body_start();
		KyotenCgiOutput::output_status();

		/*==============================================*/
		// �����ǡ�����  ����
		/*==============================================*/
		if (is_array($arr_kyoten) && count($arr_kyoten)) {

			/* store_list �����γ��� */
			$this->set_store_list_start();
			foreach ($arr_kyoten as $i => $data) {
				
				/* store_list�� �������ƥ������γ���  */
				$this->set_store_item_start($i);
				
				/* ����ID������  */
				if(isset($id)) {
					$kyotenid = $id;
				} else {
					$kyotenid = $data['KYOTEN_ID'];
				}

				/* item �����γ��� */
				$this->set_item_start($i);

				/* store id */
				$this->set_store_id($kyotenid);

				/* lat lon */
				$this->set_lat_lon($pflg, $data);
				
				/* distance */
				$this->set_distance($data);

				/* new */
				if ($arr_opt_flg['cust'] != 'YAMATO03') {		// add 2016/10/19 Y.Matsukawa
					$this->set_new($data);
				}

				/* icon_url */
				$this->set_icon_url($cid, $data, $D_SSAPI);
				
				/* img_url */
				if ($arr_opt_flg['cust'] != 'YAMATO03') {		// add 2016/10/19 Y.Matsukawa
					$this->set_img_url($cid, $kyotenid, $data, $D_SSAPI);
				}
				
				// add 2016/04/28 T.Yoshino [
				if ( $arr_opt_flg['pc_map'] == 1 ) {
					/* pc_map_url */
					$this->set_pc_map_url($cid, $kyotenid, $D_DOMAIN_G);
				}
				if ( $arr_opt_flg['smt_map'] == 1 ) {
					/* smt_map_url */
					$this->set_smt_map_url($cid, $kyotenid, $D_DOMAIN_G);
				}
				// add 2016/04/28 T.Yoshino ]

				// add 2016/01/28 T.Yoshino[
				/* img_url 1 to 5 */
				if( $arr_img['CNT'] != "" && $arr_img['CNT'] != 0 ){
					$this->set_img_url_multi($cid, $kyotenid, $arr_img, $D_SSAPI);
				}
				if ( $arr_opt_flg['cust'] == "YAMATO01" ) {
					/* site_id */
					$this->set_site_id($arr_opt_flg['site_id']);
					
					/* f */
					if( $data['COL_01'] == '2' || $data['COL_01'] == '02' ){
						$f = '7';
					} else {
						$f = '6';
					};
					$this->set_f_tag($f);
				}
				// add 2016/01/28 T.Yoshino]
				// add 2016/10/19 Y.Matsukawa [
				// ��ޥȱ�͢ŹƬ����API
				if ($arr_opt_flg['cust'] == 'YAMATO03') {
					echo $this->make_element('rcv_date', $data['YAMATO03_DYMD']);
					echo $this->make_element('keep_date', $data['YAMATO03_KYMD']);
				}
				// add 2016/10/19 Y.Matsukawa ]

				// add start 2016/12/12 H.Yasunaga ���å����б� [
				if ($arr_opt_flg['cust'] == 'YAMATO01') {
					// �����ǽ�����в������ݴɴ��¤�xml or json�ǽ���
					// ���å����ʳ���Ź�ޤξ����ͤ϶�ʸ��
					// mod 2016/12/20 H.Yasunaga ���å���API���顼�����б� ���å���API�����顼�ξ��϶�ʸ���ǽ��� [
					// ���å���API�����顼�ξ��� $date['YAMATO01_��'] �����'error'�����ꤵ��Ƥ���
					//$ymt01_rcv_date = isset($data['YAMATO01_UKETORIKANODATE']) ? $data['YAMATO01_UKETORIKANODATE'] : "";
					//$ymt01_ship_date = isset($data['YAMATO01_SHUKKADATE']) ? $data['YAMATO01_SHUKKADATE'] : "";
					//$ymt01_keep_date = isset($data['YAMATO01_HOKANKIGEN']) ? $data['YAMATO01_HOKANKIGEN'] : "";
					$ymt01_rcv_date = isset($data['YAMATO01_UKETORIKANODATE']) && $data['YAMATO01_UKETORIKANODATE'] != 'error' ? $data['YAMATO01_UKETORIKANODATE'] : "";
					$ymt01_ship_date = isset($data['YAMATO01_SHUKKADATE']) && $data['YAMATO01_SHUKKADATE'] != 'error' ? $data['YAMATO01_SHUKKADATE'] : "";
					$ymt01_keep_date = isset($data['YAMATO01_HOKANKIGEN']) && $data['YAMATO01_HOKANKIGEN'] != 'error' ? $data['YAMATO01_HOKANKIGEN'] : "";
					// mod 2016/12/20 H.Yasunaga ]

					echo $this->make_element('rcv_date', $ymt01_rcv_date);		// �����ǽ��
					echo $this->make_element('ship_date', $ymt01_ship_date);	// �в���
					echo $this->make_element('keep_date', $ymt01_keep_date);	// �ݴɴ���
				}
				// add end]
	
				/* <content> �����γ��� */
				$this->set_content_start();
				foreach ($arr_item as $j => $item) {

					/* col �����γ��� */
					$this->set_col_start($i, $item);

					/* name */
					$this->set_name($item);

					/* type */
					$this->set_type($item, $data, $arr_item_val);

					/* col �����ν�λ */
					if ($j != count($arr_item)-1) {
						$this->set_col_end();
					} else {
						$this->set_last_col_end();
					}
					
				}

				/* <content> �����ν�λ */
				$this->set_content_end();

				// �ꥢ�륿����ǡ���		add 2013/03/11 Y.Matsukawa
				if (isset($data['RD']) && is_array($data['RD'])) {
					// rd�����γ���
					$this->output_sep();
					$this->output_hash_start_with_name('rd');
					// group_count
					$arr_group = $data['RD']['GROUP_LIST'];
					$this->output_hash_item('group_count', count($arr_group));
					// group_list����
					$this->output_sep();
					$this->output_list_start('group_list');
					$g = 0;
					foreach ($arr_group as $gid=>$arr_rd_item) {
						$g++;
						if ($g > 1) $this->output_sep();
						// group����
						$this->output_hash_start('group', $g);
						// group_id
						$this->output_hash_item('group_id', $gid);
						// item_count
						$this->output_sep();
						$this->output_hash_item('item_count', count($arr_rd_item));
						// item_list����
						$this->output_sep();
						$this->output_list_start('item_list');
						$m = 0;
						foreach ($arr_rd_item as $iid=>$rd_item) {
							$m++;
							if ($m > 1) $this->output_sep();
							// item����
							$this->output_hash_start('item', $m);
							// item_id
							$this->output_hash_item('item_id', $iid);
							// type
							$val_kbn = $rd_item['VAL_KBN'];
							$this->output_sep();
							$this->output_hash_item('type', $D_RD_VAL_KBN[$val_kbn]);
							switch ($val_kbn) {
								// �ƥ����ȹ��ܤξ��
								case 'T':
									$this->output_sep();
									$this->output_hash_item('text', $rd_item['TXT_DATA']);
									break;
								// �������ܤξ��
								case 'I':
									// URL
									$img_url = $D_RD_CGI['rd_img'].'?cid='.$cid.'&kid='.$kyotenid.'&grp='.$gid.'&itm='.$iid;
									$this->output_sep();
									$this->output_hash_item('img_url', $img_url);
									// ������
									$this->output_sep();
									$this->output_hash_item('img_w', $rd_item['IMG_W']);
									// �����⤵
									$this->output_sep();
									$this->output_hash_item('img_h', $rd_item['IMG_H']);
									break;
								// �ե饰���ܤξ��
								case 'F':
									// �ե饰��
									$flag = ($rd_item['FLG_DATA']?$rd_item['FLG_DATA']:'0');
									$this->output_sep();
									$this->output_hash_item('flag', $flag);
									// �ƥ����ȡʹ���̾��
									$text = ($flag?$rd_item['ITEM_NAME']:'');
									$this->output_sep();
									$this->output_hash_item('text', $text);
									break;
							}
							// item��λ
							$this->output_hash_end('item');
						}
						// item_list��λ
						$this->output_list_end('item_list');
						// group��λ
						$this->output_hash_end('group');
					}
					// group_list��λ
					$this->output_list_end('group_list');
					// rd�����ν�λ
					$this->output_hash_end('rd');
				}

				/* item �����ν�λ */
				$this->set_item_end();
				
				/* store_list�� �������ƥ������ν�λ  */
				$this->set_store_item_end();

			}

			/* store_list �����ν�λ */
			$this->set_store_list_end();
		}

		KyotenCgiOutput::output_body_end();
		
		return;
	}

	/*==============================================*/
	// ���顼������
	/*==============================================*/
	function err_output() {

		KyotenCgiOutput::output_header();
		KyotenCgiOutput::output_body_start();
		KyotenCgiOutput::output_status();
		
		KyotenCgiOutput::output_body_end();
	}


	/*==============================================*/
	// �����Ǥ����
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
	// �����Ǥ����(�Ǹ�����Ǥξ��)
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
	// "store_list"�γ��� ��������������
	/*==============================================*/
	function set_store_list_start() {

		if ($this->Outf == 'XML') {
			echo '<store_list>'.$this->LineSep;
		} else {
			echo ',"store_list":';
			echo '[';
		}

		return;
	}

	/*==============================================*/
	// "store_list"�ν�λ ��������������
	/*==============================================*/
	function set_store_list_end() {

		if ($this->Outf == 'XML') {
			echo '</store_list>'.$this->LineSep;
		} else {
			echo ']';
		}

		return;
	}
	
	/*==============================================*/
	// store_list�� �������ƥ������γ���
	/*==============================================*/
	function set_store_item_start($i) {
		
		if ($this->Outf == 'JSON') {
			
			if($i == 0) {
				echo '{';
			} else {
				echo ',{';
			}
		}
	}
	
	/*==============================================*/
	// store_list�� �������ƥ������ν�λ
	/*==============================================*/
	function set_store_item_end() {
		
		if ($this->Outf == 'JSON') {
			echo '}';
		}
	}


	/*==============================================*/
	// "item"�γ��� ��������������
	/*==============================================*/
	function set_item_start($i) {
		if ($this->Outf == 'XML') {
			echo sprintf('<item id="%d">', $i+1).$this->LineSep;
		}

		return;
	}

	/*==============================================*/
	// "item"�ν�λ ��������������
	/*==============================================*/
	function set_item_end() {
		if ($this->Outf == 'XML') {
			echo '</item>'.$this->LineSep;
		}

		return;
	}

	
	/*==============================================*/
	// "store id" ��������������
	/*==============================================*/
	function set_store_id($id) {
		echo $this->make_element('store_id', $id);
		return;
	}

	/*==============================================*/
	// "lat" �� "lon" ��������������
	/*==============================================*/
	function set_lat_lon($pflg, $data) {
		
		$lat;
		$lon;
				
		switch ($pflg)  {
			
			/* ���ʰ��ٷ���ɽ�� */
			case '1':
				$lat = cnv_dms2hour($data['LAT']);
				$lon = cnv_dms2hour($data['LON']);
				break;

			/* �ߥ��ð��ٷ���ɽ�� */
			case '2':
				$lat = $data['LAT'];
				$lon = $data['LON'];
				break;

			/* ��ʬ�ð��ٷ���ɽ�� */
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
	// "distance" ��������������
	/*==============================================*/
	function set_distance($data) {
	
		if(isset($data['KYORI'])) {
			echo $this->make_element('distance', $data['KYORI']);
		}
		return;
	}

	/*==============================================*/
	// "new" ��������������
	/*==============================================*/
	function set_new($data) {
		echo $this->make_element('new', $data['BFLG']);

		return;
	}

	/*==============================================*/
	// "icon_url" ��������������
	/*==============================================*/
	function set_icon_url($cid, $data, $D_SSAPI) {

		$icon_url = sprintf("%s?cid=%s&icon_id=%s", $D_SSAPI["icon_select_g"], $cid, $data['ICON_ID']);
		echo $this->make_element('icon_url', $icon_url);

		return;
	}

	/*==============================================*/
	// "img_url" ��������������
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
	// "pc_map_url" �������������� add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_pc_map_url($cid, $kyotenid, $D_DOMAIN_G) {

		global $D_EMAP_ENV;

		if ($D_EMAP_ENV == "test") {
			$set_d_url = "http://" . $D_DOMAIN_G;

		} else {
			$set_d_url = "https://" . $D_DOMAIN_G;

		}

		$pc_map_url = sprintf("%s/p/%s/dtl/%s/", $set_d_url, $cid, $kyotenid);
		echo $this->make_element('pc_map_url', $pc_map_url);

		return;
	}

	/*==============================================*/
	// "smt_map_url" �������������� add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_smt_map_url($cid, $kyotenid, $D_DOMAIN_G) {

		global $D_EMAP_ENV;

		if ($D_EMAP_ENV == "test") {
			$set_d_url = "http://" . $D_DOMAIN_G;

		} else {
			$set_d_url = "https://" . $D_DOMAIN_G;

		}

		$smt_map_url = sprintf("%s/smt/%s/map/%s/", $set_d_url, $cid, $kyotenid);
		echo $this->make_element('smt_map_url', $smt_map_url);

		return;
	}

	/*==============================================*/
	// "img_url1"��"img_url5" �������������� add 2016/01/28  T.Yoshino
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
	// "site_id" �������������� add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_site_id($site_id) {
		echo $this->make_element('site_id', $site_id);

		return;
	}

	/*==============================================*/
	// "f" �������������� add 2016/04/28  T.Yoshino
	/*==============================================*/
	function set_f_tag($f) {
		echo $this->make_element('f', $f);

		return;
	}
	
	/*==============================================*/
	// "content"�γ��� ��������������
	/*==============================================*/
	function set_content_start() {
		if ($this->Outf == 'XML') {
			echo '<content>'.$this->LineSep;
		} else {
			echo '"content":';
			echo '[';
		}

		return;
	}
	
	/*==============================================*/
	// "content"�ν�λ ��������������
	/*==============================================*/
	function set_content_end() {
		if ($this->Outf == 'XML') {
			echo '</content>'.$this->LineSep;
		} else {
			echo ']';
		}

		return;
	}

	/*==============================================*/
	// "col"�γ��� ��������������
	/*==============================================*/
	function set_col_start($i, $item) {
		if ($this->Outf == 'XML') {
			echo sprintf('<col id="item%d_%s">', $i+1, f_enc_convert($this->escapeXML($item['COL_NAME'])));
		} else {
			
			/* 2�����ܤ���ϡ������Ǥ������� ',' ���դ��� */
			if($j != 0) {
				echo ',';
			}
			
			echo '{';
			echo $this->make_element('col', f_enc_convert($this->escapeJSON($item['COL_NAME'])));
		}

		return;
	}
	
	/*==============================================*/
	// "col"�ν�λ ��������������
	/*==============================================*/
	function set_col_end() {
		if ($this->Outf == 'XML') {
			echo '</col>'.$this->LineSep;
		} else {
			echo '},';
		}

		return;
	}

	/*==============================================*/
	// "col"�ν�λ ��������������(�Ǹ�����Ǥξ��)
	/*==============================================*/
	function set_last_col_end() {
		if ($this->Outf == 'XML') {
			echo '</col>'.$this->LineSep;
		} else {
			echo '}';
		}

		return;
	}
	

	/*==============================================*/
	// "name" ��������������
	/*==============================================*/
	function set_name($item) {
		echo $this->make_element('name', $item['ITEM_NAME']);

		return;
	}
	
	/*==============================================*/
	// "type" �̤ˡ��ƥ���(text, code, flg)����������
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