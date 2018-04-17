<?PHP
// ------------------------------------------------------------
// 汎用javasctipt 拠点ID CGI読み込みインターフェイス
// 
// 開発履歴
// 2011/06/16 Y.Matsukawa	新規作成
// 2011/07/07 H.Osamoto		マツキヨ用API2.0対応版
// ------------------------------------------------------------
//include("d_serv_emap.inc");		del 2011/06/16 Y.Matsukawa
include("./inc/define.inc");		// add 2011/06/16 Y.Matsukawa
?>
function ZdcKyotenId(){
	this.type = 'ZdcKyotenId';
	this.result = false;
	this.text_data = null;
}
ZdcKyotenId.prototype.getResult = function(){
	return this.result;
}
ZdcKyotenId.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcKyotenId.prototype.search = function(opts, callback){
	var owner = this;
	//var enc = ZDC_ENC;	mod 2011/07/07 H.osamoto
	var enc = "EUC";
	
	var target_url = "";
	if (opts.nolog) {
		target_url = "<?PHP echo $D_SSAPI["kyotenid_nolog"]; ?>";
	} else {
		target_url = "<?PHP echo $D_SSAPI["kyotenid"]; ?>";
	}
	var prm = '';
	prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
	prm += '&cid='+opts.cid;
	prm += '&kid='+opts.kid;
	prm += '&type=1';
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&enc='+enc;
	var request_url = target_url+'?'+prm;
	
	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text,status){
		var result = new ZdcKyotenIdResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		ZdcEvent.trigger(owner, "end", result);
		if( callback != null ){
			callback(result);
		}
	}, opts.timeout);
}
function ZdcKyotenIdOptions(){
	//default値
	this.cid = '99999999';
	this.kid = '';
	this.timeout = 60000;
	this.nolog = true;		// ログ出力抑制
}
function ZdcKyotenIdResult(text_data, status){
	
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
	if( retcd.charAt(3) == '1' ){
		ZdcSetErrorStatus.call(this, retcd);
		return;
	}
	//record
	this.retCode  = retcd;
	this.type = '';
	this.status = status;
	this.recCount    = cnt;
	this.hitCount = hitcnt;
	if (cnt > 0) {
		cols = res[0].split('\t');
		// 拠点縮尺（PC）
		lvl = cols[cols.length-2];
		if (!lvl || lvl < 1 || lvl >18) lvl = 0;
		this.item = new ZdcKyotenIdItem(cols,lvl);
	}
}
function ZdcKyotenIdItem(cols,lvl){
	this.lat  = cols[0];
	this.lon  = cols[1];
	this.icon = cols[2];
	this.gif  = cols[3];
	this.nflg = cols[4];
<?php	$i = 4;
		if ($D_KYO_COL_NAME[1] && count($D_KYO_COL_NAME[1])) {
			foreach ($D_KYO_COL_NAME[1] as $col_name) {
				$i++;
?>
	this.<?php echo $col_name; ?> = cols[<?php echo $i; ?>];
<?php		}
		}
?>
	this.lvl = lvl;
}
