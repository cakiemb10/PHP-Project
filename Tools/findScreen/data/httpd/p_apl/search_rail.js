<?PHP
// ------------------------------------------------------------
// �H���}
// 
// �J������
// 2011/10/15 Y.Matsukawa	�V�K�쐬
// 2014/02/05 Y.Matsukawa	�N���X�T�C�g�X�N���v�e�B���O�΍�
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
require_once('/home/emap/src/p/inc/act_get_parm.inc');
?>
//�H���}�\��
var ZdcEmapRail;
function ZdcEmapSearchRailwayDisp(mapNo,x,y,prm){
	ZdcEmapRail = new ZDC.RailwayMap(
				{
					mapNo: mapNo,
					callback: ZdcEmapSearchRailClick,
					mainMap: document.getElementById('ZdcEmapSearchRailwayMain'),
					subMap: document.getElementById('ZdcEmapSearchRailwaySub')
				}
	);
}
//�H���}�N���b�N���ɓ���
var ZdcEmapSearchRailClick = function(rtn) {
	// �H���}���N���b�N�����ʒu���擾���Ēn�}���ړ�
	location.href = "<?php echo $D_DIR_BASE_G; ?>nmap.htm?lat="+rtn.latlon.lat+"&lon="+rtn.latlon.lon
					+"<?php echo ($P_FREEPARAMS_ENC?'&'.$P_FREEPARAMS_ENC:''); ?>"
					//+"<?php echo ($condprm?'&'.$condprm:''); ?>"		mod 2014/02/05 Y.Matsukawa
					+"<?php echo ($condprm_enc?'&'.$condprm_enc:''); ?>"
					+"<?php echo ($his?'&his='.urlencode($his):''); ?>";
}
