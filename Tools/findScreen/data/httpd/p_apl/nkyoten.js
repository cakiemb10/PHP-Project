<?PHP
// ------------------------------------------------------------
// �Ǵ����CGI�ɤ߹��ߥ��󥿡��ե�����
// 
// ��ȯ����
// 2011/10/15 Y.Matsukawa	��������
// 2011/12/27 H.osamoto		���֥�ߡ����̳�ٱ��ѽ����ɲ�
// 2012/10/15 H.Osamoto		�����ϰϤλ����µ�Υ�ǻ����ǽ���ѹ�
// 2012/11/13 Y.Matsukawa	JCN�����������
// 2013/05/22 H.Osamoto		�Ǵ󸡺���̤�0��ξ��Ƹ����Ǽ������������굡ǽ�ɲ�
// 2013/08/02 Y.Matsukawa	Ǥ����������Ǥ���ϰϳ��ε��������
// 2014/02/21 H.Osamoto		�ݥꥴ���⳰Ƚ���ɲ�
// 2014/10/27 H.Osamoto		�Ǵ󸡺���̤�0��ξ��Ƹ�����ǽ�η�������Զ�罤��
// 2015/09/30 Y.Uesugi		�Ǵ󸡺���̤����ꤷ���Ǿ�����ʲ��ξ�硢�Ƹ���
// 2016/01/27 H.Yasunaga	������̤��Ƹ������ݤ���Ƚ�̤��뵡ǽ�ɲá�ZdcNearShopResult.researched)
// 2016/01/28 H.Yasunaga	711map�˥å��󥫥����ޥ����Ƹ��������ϰϻ���
// 2016/12/12 H.Yasunaga	��ޥȥ�å����б� �в�ͽ������ȯ��͹���ֹ桦�ܥå�����������ʬ�ѥ�᡼������Ϳ
// 2017/04/21 H.Yasunaga	�����󥭥��ڡ����б��������ޥ���
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
?>
function ZdcNearShop(){
	this.type = 'ZdcNearShop';
	this.result = false;
	this.text_data = null;
}
ZdcNearShop.prototype.getResult = function(){
	return this.result;
}
ZdcNearShop.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcNearShop.prototype.search = function(opts, callback){
	var owner = this;
	//var enc = ZDC_ENC;
	var enc = "EUC";
	
	var target_url = "<?PHP echo $D_SSAPI["nkyoten"]; ?>";
	var prm = '';
	prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
	prm += '&cid='+opts.cid;
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&pos='+opts.startPos;
	prm += '&cnt='+opts.maxCount;
	prm += '&enc='+enc;
	prm += '&lat='+opts.lat;
	prm += '&lon='+opts.lon;
	prm += '&latlon='+opts.latlon;
	prm += '&jkn='+opts.jkn;
<?php
	// add 2012/01/10 H.osamoto [
	if ($D_OPENDAY_FLG) {
?>
	prm += "<?PHP echo '+AND+'.$D_OPENDAY_COL.':DT:LTE:SYSDATE' ?>";			// �����ץ���Ź�ޤ����
<?php
	}
	// add 2012/01/10 H.osamoto ]
?>
	prm += '&rad='+opts.radius;
	prm += '&knsu='+opts.limitCount;
	prm += '&exkid='+opts.exceptKid;
	prm += '&hour=1';
	<?php
	// add 2012/10/15 H.Osamoto [
	if (isset($D_ABS_DIST) && $D_ABS_DIST) {
	?>
	prm += '&absdist='+<?php echo ($D_ABS_DIST); ?>;
	<?php
	}
	// add 2012/10/15 H.Osamoto ]
	?>
	prm += '&cust='+opts.cust;		<?php // add 2012/11/13 Y.Matsukawa ?>
	prm += '&exarea='+opts.exarea;		<?php // add 2013/08/02 Y.Matsukawa ?>
	prm += '&polycol='+opts.polycol;		<?php // add 2014/02/21 H.Osamoto ?>

	<?php // add 2016/12/12 H.Yasunaga ��ޥȥ�å����б�[ ?>
	<?php
	// ��å����Υե饰���� �в�ͽ������ȯ��͹���ֹ桦�ܥå�����������ʬ�����ꤵ��Ƥ���
	if (isset($D_YTC_LOCKER) && $D_YTC_LOCKER &&
		isset($p_s9, $p_s10, $p_s11) && strlen($p_s9) > 0 && strlen($p_s10) > 0 && strlen($p_s11) > 0) {
	?>
	prm += '&SDATE='+<?php echo ($p_s9); ?>;	// �в�ͽ����
	prm += '&HZIP='+<?php echo ($p_s10); ?>;	// ȯ��͹���ֹ�
	prm += '&BSKBN='+<?php echo ($p_s11); ?>;	// �ܥå�����������ʬ
	<?php
	}
	?>
	<?php // add 2016/12/12 H.Yasunaga ] ?>
	
	<?php // add 2017/04/21 H.Yasunaga �����󥭥��ڡ���ڡ����б� [ ?>
	<?php
	if ($D_LOWSON_CAM_CUST) {
	?>
	prm += '&campaignid=<?php echo $p_s1; ?>';
	<?php
	}
	?>
	<?php // add 2017/04/21 H.Yasunaga ] ?>

	var request_url = target_url+'?'+prm;

	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text,status){
		var result = new ZdcNearShopResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		ZDC.trigger(owner, "end", result);
		if( callback != null ){
			// mod 2013/04/15 H.Osamoto [
			//	callback(result);

			// mod 2015/09/30 Y.Uesugi [
			if (result.hitCount == 0 || result.hitCount < opts.minCount) {
			//if (result.hitCount == 0) {
			// mod 2015/09/30 Y.Uesugi [
				if (opts.researchCount != "") {
					var target_url = "<?PHP echo $D_SSAPI["nkyoten"]; ?>";
					var prm = '';
					prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
					prm += '&cid='+opts.cid;
					prm += '&opt=<?PHP echo $cid; ?>';
					prm += '&pos='+opts.startPos;
					prm += '&cnt='+opts.researchCount;
					prm += '&enc='+enc;
					prm += '&lat='+opts.lat;
					prm += '&lon='+opts.lon;
					
					<?php
					// mod 2016/01/28 H.Yasunaga 711map�˥å��󥫥����ޥ��� [
					if ($D_711NISSEN_FIX_ZOOM) { ?>
						prm += '&latlon=20.0,123.0,45.0,154.0';
					<?php
					} else { ?>
						prm += '&latlon='+opts.latlon;
					<?php
					} 
					
					// mod 2016/01/28 H.Yasunaga ]?>
					prm += '&jkn='+opts.jkn;
					<?php
						if ($D_OPENDAY_FLG) {
					?>
						prm += "<?PHP echo '+AND+'.$D_OPENDAY_COL.':DT:LTE:SYSDATE' ?>";			// �����ץ���Ź�ޤ����
					<?php
						}
					?>
					prm += '&rad=10000000';
					<?php //	prm += '&knsu=1';	// mod 2014/10/27 H.Osamoto ?>
					prm += '&knsu='+opts.researchCount;
					prm += '&exkid='+opts.exceptKid;
					prm += '&hour=1';
					<?php
					if (isset($D_ABS_DIST) && $D_ABS_DIST) {
					?>
					prm += '&absdist='+<?php echo ($D_ABS_DIST); ?>;
					<?php
					}
					?>
					prm += '&cust='+opts.cust;
					prm += '&exarea='+opts.exarea;		<?php // add 2013/08/02 Y.Matsukawa ?>
					prm += '&polycol='+opts.polycol;		<?php // add 2014/02/21 H.Osamoto ?>

					<?php // add 2016/12/12 H.Yasunaga ��ޥȥ�å����б�[ ?>
					<?php
					// ��å����Υե饰���� �в�ͽ������ȯ��͹���ֹ桦�ܥå�����������ʬ�����ꤵ��Ƥ���
					if (isset($D_YTC_LOCKER) && $D_YTC_LOCKER && 
						isset($p_s9, $p_s10, $p_s11) && strlen($p_s9) > 0 && strlen($p_s10) > 0 && strlen($p_s11) > 0) {
					?>
					prm += '&SDATE='+<?php echo ($p_s9); ?>;	// �в�ͽ����
					prm += '&HZIP='+<?php echo ($p_s10); ?>;	// ȯ��͹���ֹ�
					prm += '&BSKBN='+<?php echo ($p_s11); ?>;	// �ܥå�����������ʬ
					<?php
					}
					?>
					<?php // add 2016/12/12 H.Yasunaga ] ?>
					
					<?php // add 2017/04/21 H.Yasunaga �����󥭥��ڡ���ڡ����б� [ ?>
					<?php
					if ($D_LOWSON_CAM_CUST) {
					?>
					prm += '&campaignid=<?php echo $p_s1; ?>';
					<?php
					}
					?>
					<?php // add 2017/04/21 H.Yasunaga ] ?>
					
					var request_url = target_url+'?'+prm;
					
					this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
					this.httpReq.request(request_url, function(reference_text,status){
						var result = new ZdcNearShopResult(reference_text, status);
						result.type = owner.type;
						result.options = opts;
						// add 2016/01/27 H.Yasunaga search���κƸ����Υե饰�ɲ� [
						result.researched = "1";
						// add 2016/01/27 H.Yasunaga ]
						owner.result = result;
						ZDC.trigger(owner, "end", result);
						if( callback != null ){
							callback(result);
						}
					}, opts.timeout);
				} else {
					callback(result);
				}
			} else {
				callback(result);
			}
			// mod 2013/04/15 H.Osamoto ]
		}
	}, opts.timeout);
}
function ZdcNearShopOptions(frewd){
	//default��
	this.cid = '99999999';
	this.startPos = 1;
	this.minCount = 0;	<?php // mod 2015/09/30 Y.Uesugi ?>
	this.maxCount = 30;
	this.lat = '';
	this.lon = '';
	this.latlon = '';
	this.jkn = '';
	this.limitCount = 100;    //������
	this.radius  = 50000; //Ⱦ��
	this.timeout = 60000;
	this.pointFlg = '2'; //�����б��� default: 2 (ZDC ms)
	this.exceptKid = '';	//�����������
	this.cust = '';		<?php // �������ޥ����ե饰		add 2012/11/13 Y.Matsukawa ?>
	this.researchCount = '';	<?php //�Ƹ������������		add 2013/05/22 H.Osamoto ?>
	this.exarea = '';	<?php // add 2013/08/02 Y.Matsukawa ?>
	this.polycol = '';	<?php // add 2014/02/21 H.Osamoto ?>
}
function ZdcNearShopResult(text_data, status){
	
	if( text_data == null ){
		ZdcSetErrorStatus.call(this, '', status);
		return;
	}
	
	//header
	var res = new Array();
	//res = text_data.split(ZDC_HTTP_DMT[ZDC_ENC]);
	res = text_data.split('\n');
	var header = res.shift();
	var cols = header.split('\t');
	var retcd  = cols[0];
	var cnt    = parseFloat(cols[1]);
	var hitcnt = parseFloat(cols[2]);
	var rest = ( retcd.charAt(3) == '0' && retcd.charAt(7) == '1' )? true : false;
	
	//Parameter Error Check
	if( retcd.charAt(3) == '1' ){
		ZdcSetErrorStatus.call(this, retcd);
		return;
	}
	//record
	// add 2016/01/27 H.Yasunaga search���κƸ����Υե饰�ɲ� �Ƹ�����������"1"������ [
	this.researched = "";
	// add 2016/01/27 ]
	this.retCode  = retcd;
	this.type = '';
	this.status = status;
	this.recCount    = cnt;
	this.hitCount = hitcnt;
	this.rest = rest;
	this.items = [];
	for(var i=0; i<cnt; i++){
		cols = res[i].split('\t');
		if( cols[0] == '' ){ continue; }
		// �����̼ܡ�PC��
		lvl = cols[cols.length-2];
		if (!lvl || lvl < 1 || lvl >18) lvl = 0;
		var item = new ZdcNearShopItem(cols,lvl);
		this.items.push(item);
	}
}
function ZdcNearShopItem(cols,lvl){
	this.id   = cols[0];
	this.lat  = cols[1];
	this.lon  = cols[2];
	this.icon = cols[3];
	this.dist = cols[4];
	this.nflg = cols[5];
<?php
if ($D_KYO_COL_NAME[0] && count($D_KYO_COL_NAME[0])) {
	foreach ($D_KYO_COL_NAME[0] as $i=>$colnm) {
		if ($colnm) {
?>
	this.<?php echo $colnm; ?> = cols[<?php echo ($i + 6); ?>];
<?php
		}
	}
	if ($D_ICONID_COL) {
?>
	if (this.<?php echo $D_ICONID_COL; ?> && ZdcEmapIconImg[this.<?php echo $D_ICONID_COL; ?>])
		this.icon = this.<?php echo $D_ICONID_COL; ?>;
<?php
	}
}
?>
	this.lvl = lvl;
}
