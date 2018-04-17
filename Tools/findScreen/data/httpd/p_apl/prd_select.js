<?PHP
// ------------------------------------------------------------
// 商品ID検索CGI読み込みインターフェイス
// 
// 開発履歴
// 2014/05/16 Y.Matsukawa	新規作成
// 2015/04/28 Y.Uesugi		ピジョン社内向け検索対応
// ------------------------------------------------------------
require_once('/home/emap/src/p/inc/define.inc');
?>
function ZdcPrdSelect(){
	this.type = 'ZdcPrdSelect';
	this.result = false;
	this.text_data = null;
}
ZdcPrdSelect.prototype.getResult = function(){
	return this.result;
}
ZdcPrdSelect.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcPrdSelect.prototype.search = function(opts, callback){
	var owner = this;
	var enc = "EUC";
	var target_url = "<?PHP echo $D_SSAPI['prd_select']; ?>";
	var prm = '';
	prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
	prm += '&cid='+opts.cid;
	prm += '&pid='+opts.pid;
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&enc='+enc;
	var request_url = target_url+'?'+prm;
	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text, status){
		var result = new ZdcPrdSelectResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		//ZDC.trigger(owner, "end", result);
		if( callback != null ){
			callback(result);
		}
	}, opts.timeout);
}
function ZdcPrdSelectOptions(frewd){
	//default値
	this.cid = '';
	this.pid = '';
	this.timeout = 60000;
}
function ZdcPrdSelectResult(text_data, status){
	if( text_data == null ){
		ZdcSetErrorStatus.call(this, '', status);
		return;
	}
	//header
	var res = new Array();
	res = text_data.split('\n');
	var header = res.shift();
	var cols = header.split('\t');
	var retcd  = cols[0];
	var cnt    = parseFloat(cols[1]);
	var hitcnt = parseFloat(cols[2]);
	//Parameter Error Check
//	if( retcd.charAt(3) == '1' ){
//		ZdcSetErrorStatus.call(this, retcd);
//		return;
//	}
	//record
	this.retCode  = retcd;
	this.type = '';
	this.status = status;
	this.recCount = cnt;
	this.hitCount = hitcnt;
	this.items = [];
	for(var i=0; i<cnt; i++){
		cols = res[i].split('\t');
		if( cols[0] == '' ){ continue; }
		var item = new ZdcPrdSelectItem(cols);
		this.items.push(item);
	}
}
function ZdcPrdSelectItem(cols,lvl){
	this.pid = cols[0];
	this.pnm = cols[1];
}

var ZdcPrdSelectObj = new ZdcPrdSelect();
function ZdcGetPrd(cid, pid, callback) {
	 var opts = new ZdcPrdSelectOptions();
	 opts.cid = cid;
	 opts.pid = pid;
	 opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
	 ZdcPrdSelectObj.opts = opts;
	 ZdcPrdSelectObj.search(opts, callback);
}

// add 2015/04/28 Y.Uesugi JANコードから検索 [
function ZdcPrdSelectJan(){
	this.type = 'ZdcPrdSelectJan';
	this.result = false;
	this.text_data = null;
}
ZdcPrdSelectJan.prototype.getResult = function(){
	return this.result;
}
ZdcPrdSelectJan.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcPrdSelectJan.prototype.search = function(opts, callback){
	var owner = this;
	var enc = "EUC";
	var target_url = "<?PHP echo $D_SSAPI['prd_select_jan']; ?>";
	var prm = '';
	prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
	prm += '&cid='+opts.cid;
	prm += '&jan='+opts.jan;
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&enc='+enc;
	var request_url = target_url+'?'+prm;
	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text, status){
		var result = new ZdcPrdSelectJanResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		//ZDC.trigger(owner, "end", result);
		if( callback != null ){
			callback(result);
		}
	}, opts.timeout);
}
function ZdcPrdSelectJanOptions(frewd){
	//default値
	this.cid = '';
	this.pid = '';
	this.jan = '';
	this.timeout = 60000;
}
function ZdcPrdSelectJanResult(text_data, status){
	if( text_data == null ){
		ZdcSetErrorStatus.call(this, status);
		return;
	}
	//header
	var res = new Array();
	res = text_data.split('\n');
	var header = res.shift();
	var cols = header.split('\t');
	var retcd  = cols[0];
	var cnt    = parseFloat(cols[1]);
	var hitcnt = parseFloat(cols[2]);

	//record
	this.retCode  = retcd;
	this.type = '';
	this.status = status;
	this.recCount = cnt;
	this.hitCount = hitcnt;
	this.items = [];
	for(var i=0; i<cnt; i++){
		cols = res[i].split('\t');
		if( cols[0] == '' ){ continue; }
		var item = new ZdcPrdSelectJanItem(cols);
		this.items.push(item);
	}
}
function ZdcPrdSelectJanItem(cols,lvl){
	this.pid = cols[0];
	this.pnm = cols[1];
}

var ZdcPrdSelectJanObj = new ZdcPrdSelectJan();
function ZdcGetPrdJan(cid, jan, callback) {
	 var opts = new ZdcPrdSelectJanOptions();
	 opts.cid = cid;
	 opts.jan = jan;
	 opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
	 ZdcPrdSelectJanObj.opts = opts;
	 ZdcPrdSelectJanObj.search(opts, callback);
}
// add 2015/04/28 Y.Uesugi JANコードから検索 ]


// add 2015/04/28 Y.Uesugi 商品名から検索 [
function ZdcPrdSelectPnm(){
	this.type = 'ZdcPrdSelectPnm';
	this.result = false;
	this.text_data = null;
}
ZdcPrdSelectPnm.prototype.getResult = function(){
	return this.result;
}
ZdcPrdSelectPnm.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcPrdSelectPnm.prototype.search = function(opts, callback){
	var owner = this;
	var enc = "EUC";
	var target_url = "<?PHP echo $D_SSAPI['prd_select_pnm']; ?>";
	var prm = '';
	prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
	prm += '&cid='+opts.cid;
	prm += '&pnm='+opts.pnm;
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&enc='+enc;
	var request_url = target_url+'?'+prm;
	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text, status){
		var result = new ZdcPrdSelectPnmResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		//ZDC.trigger(owner, "end", result);
		if( callback != null ){
			callback(result);
		}
	}, opts.timeout);
}
function ZdcPrdSelectPnmOptions(frewd){
	//default値
	this.cid = '';
	this.pid = '';
	this.pnm = '';
	this.timeout = 60000;
}
function ZdcPrdSelectPnmResult(text_data, status){
	if( text_data == null ){
		ZdcSetErrorStatus.call(this, status);
		return;
	}
	//header
	var res = new Array();
	res = text_data.split('\n');
	var header = res.shift();
	var cols = header.split('\t');
	var retcd  = cols[0];
	var cnt    = parseFloat(cols[1]);
	var hitcnt = parseFloat(cols[2]);

	//record
	this.retCode  = retcd;
	this.type = '';
	this.status = status;
	this.recCount = cnt;
	this.hitCount = hitcnt;
	this.items = [];
	for(var i=0; i<cnt; i++){
		cols = res[i].split('\t');
		if( cols[0] == '' ){ continue; }
		var item = new ZdcPrdSelectPnmItem(cols);
		this.items.push(item);
	}
}
function ZdcPrdSelectPnmItem(cols,lvl){
	this.pid = cols[0];
	this.pnm = cols[1];
}

var ZdcPrdSelectPnmObj = new ZdcPrdSelectPnm();
function ZdcGetPrdPnm(cid, pnm, callback) {
	 var opts = new ZdcPrdSelectPnmOptions();
	 opts.cid = cid;
	 opts.pnm = pnm;
	 opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
	 ZdcPrdSelectPnmObj.opts = opts;
	 ZdcPrdSelectPnmObj.search(opts, callback);
}
// add 2015/04/28 Y.Uesugi 商品名から検索 ]


