<?PHP
// ------------------------------------------------------------
// ���Ѷ���javascript�⥸�塼��
// 
// ��ȯ����
// 2015/10/20 N.Wada	��������
// 2016/02/03 N.Wada	�����ϼ������顼��å�����
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
?>

var ZdcEmapGPSErrMsg="<?php echo $D_MSG_GPS_ERRPRM; ?>";		<?php // add 2016/02/03 N.Wada ?>

//HTML�ɤ߹�����ajax�̿��ؿ�
function ZdcEmapCmnHttpRequestHtmlAjax(url, func, nowaitmsg, typ) {
	if(typ == undefined) typ = 1;
	//�̿�����
	var ZdcEmapHttpRequestObj = new ZdcEmapHttpRequest('EUC', 'EUC');
	ZdcEmapHttpRequestObj.request(url, function(html,status) {
		if(status == 3) status = 0;//�����ॢ���Ȥ�̵�� Ϣ³�ƤӽФ�����ư����ꤷ�ʤ��Τ�
		if(status == 9) status = 0;//�ƥ�ץ졼�Ȥ�̵�������б�
		if(html == null) html = "";//null�ϽФ��ʤ�
		if(status == 0) {
			func(html,status);
		} else {
			//���顼����
			func(html,status);
		}
	},<?PHP echo $D_AJAX_TIMEOUT; ?>,typ);
}

