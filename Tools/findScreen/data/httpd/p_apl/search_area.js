<?PHP
// ------------------------------------------------------------
// �n��}
// 
// �J������
// 2011/10/15 Y.Matsukawa	�V�K�쐬
// 2014/02/05 Y.Matsukawa	�N���X�T�C�g�X�N���v�e�B���O�΍�
// 2016/08/05 Y.Uesugi		�s�撬����n�}��ʂɓn��������ǉ�
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>
//�n��}�\��
var ZdcEmapArea;
function ZdcEmapSearchAreaDisp(todCode,name,prm){
	ZdcEmapArea = new ZDC.AreaMap(
				{
					todCode: todCode,
					callback: ZdcEmapSearchAreaClick,
					areaMap: document.getElementById('ZdcEmapSearchArea')
				}
	);
	ZDC._callback = function(){};
}
//�n��}�N���b�N���ɓ���
var ZdcEmapSearchAreaClick = function(rtn) {
	// �n��}���N���b�N�����ʒu���擾���Ēn�}���ړ�
	location.href = "<?php echo $D_DIR_BASE_G; ?>nmap.htm?lat="+rtn.latlon.lat+"&lon="+rtn.latlon.lon
					<?php if (isset($D_SEARCH_AREA_CITY) && $D_SEARCH_AREA_CITY) { ?> +"&city="+rtn.cityName <?php } ?>			// add 2016/08/05 Y.Uesugi
					+"<?php echo ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:''); ?>"
					//+"<?php echo ($condprm?'&'.$condprm:''); ?>"		mod 2014/02/05 Y.Matsukawa
					+"<?php echo ($condprm_enc?'&'.$condprm_enc:''); ?>"
					+"<?php echo ($his?'&his='.urlencode($his):''); ?>";
}
