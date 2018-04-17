<?PHP
// ------------------------------------------------------------
// 拠点エリアCGI読み込みインターフェイス
// 
// 2015/02/03 Y.Matsukawa	新規作成
// ------------------------------------------------------------
require_once('/home/emap/src/smt/inc/define.inc');
?>
function ZdcSearchShopArea(){
	this.type = "ZdcSearchShopArea";
	this.result = false;
	this.text_data = null;
}
ZdcSearchShopArea.prototype.getResult = function(){
	return this.result;
}
ZdcSearchShopArea.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcSearchShopArea.prototype.search = function(opts, callback){
	var owner = this;
	var target_url = "<?PHP echo $D_SSAPI['kyotenarea']; ?>";
	var prm = "";
	prm += "&key=<?PHP echo $D_SSAPI_KEY; ?>";
	prm += "&cid="+opts.cid;
	prm += "&opt=<?PHP echo $cid; ?>";
	prm += "&pos="+opts.startPos;
	prm += "&cnt="+opts.maxCount;
	prm += "&areaptn="+opts.areaptn;
	if (opts.area1 != "") prm += "&area="+opts.area1;
	if (opts.sortlpad != "") prm += "&sortlpad="+opts.sortlpad;
	prm += "&jkn="+opts.jkn;
	var request_url = target_url+"?"+prm;
	this.httpReq = new ZdcEmapHttpRequest("EUC", "EUC");
	this.httpReq.request(request_url, function(reference_text,status){
		var result = new ZdcSearchShopAreaResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		if( callback != null ){
			callback(result);
		}
	}, opts.timeout);
}
function ZdcSearchShopAreaOptions(frewd){
	this.cid = "";
	this.startPos = 1;
	this.maxCount = 30;
	this.areaptn = "1";
	this.area1 = "";
	this.jkn = "";
	this.sortlpad = "";
	this.timeout = 60000;
}
function ZdcSearchShopAreaResult(text_data, status){
	if( text_data == null ){
		ZdcSetErrorStatus.call(this, "", status);
		return;
	}
	var res = new Array();
	res = text_data.split("\n");
	var header = res.shift();
	var cols   = header.split("\t");
	var retcd  = cols[0];
	var cnt    = parseInt(cols[1]);
	var hitcnt = parseInt(cols[2]);
	this.rest = ( retcd.charAt(3) == "0" && retcd.charAt(7) == "1" )? true : false;
	if( retcd.charAt(3) == "1" ){
		ZdcSetErrorStatus.call(this, retcd);
		return;
	}
	this.retCode  = retcd;
	this.type = "";
	this.status = status;
	//this.recCount = cnt;
	this.hitCount = hitcnt;
	this.items = [];
	this.recCount = 0;
	for(var i = 1; i <= cnt; i++){
		cols = res[i].split("\t");
		if( cols[0] == "" ){ continue; }
		this.recCount++;
		var item = new ZdcSearchShopAreaItem(cols);
		this.items.push(item);
	}
}
function ZdcSearchShopAreaItem(cols){
	this.value = cols[0];
	this.name = cols[1];
	this.count= cols[2];
}
var ZdcEmapSearchShopArea = new ZdcSearchShopArea();
