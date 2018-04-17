<?php
/*********************************************************************/
// ��������
// 2016/01/20 T.Yoshino	��������
/*********************************************************************/
//-----------------------------------------------------------
// XML���ϥ��饹
//-----------------------------------------------------------

class ReccRouteCgiOutput extends KyotenCgiOutput {

	/*==============================================*/
	// ���󥹥ȥ饯��
	/*==============================================*/
	function StoreKyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf) {
		KyotenCgiOutput::KyotenCgiOutput($cgicd, $cginm, $enc, $retcd, $retcd_e, $pflg, $outf);
	}

	/*==============================================*/
	// ����
	/*==============================================*/
	function output($cid, $id, $pflg, $arr_item, $arr_kyoten, $arr_item_val) {
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

				/* lat lon */
				$this->set_lat_lon($pflg, $data);
				
				/* distance */
				$this->set_distance($data);

				/* item �����ν�λ */
				$this->set_item_end();
				
				/* item_list�� �������ƥ������ν�λ  */
				$this->set_store_item_end();

			}

			/* item_list �����ν�λ */
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
	// "item_list"�γ��� ��������������
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
	// "item_list"�ν�λ ��������������
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
	// store_list�� �������ƥ������γ���
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
			echo sprintf('<item id="%d">', $i).$this->LineSep;
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

}

?>