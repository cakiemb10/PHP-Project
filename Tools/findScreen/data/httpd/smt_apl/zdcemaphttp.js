<?PHP
// ------------------------------------------------------------
// 汎用javasctipt AJAX通信モジュール
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2012/09/10 Y.Matsukawa	【不具合修正】任意パラメータに「&」を含めると正しく引き継がれない、任意パラメータに半角スペース指定すると消える
// 2015/02/27 Y.Matsukawa	コメントアウト変更（一部環境でスクリプトエラーになるため）
// 2016/03/18 Y.Matsukawa	長尺URL対応（リファラー等を付加しない）
// ------------------------------------------------------------
require_once('/home/emap/src/smt/inc/define.inc');
?>
//ZdcEmapHttpRequest Namespace
(function()
{
	//common vars
	var ZDC_EMAP_CGI_INTERVAL = 50; 
	var ZDC_EMAP_CGI_AJAX = 'ZdcEmapAjax'; 
	//var ZDC_EMAP_PROXY_CGI = './zdcemaphttp.cgi';
	var ZDC_EMAP_PROXY_CGI = '<?PHP echo $D_DIR_BASE_G; ?>zdcemaphttp.cgi';
	var ZDC_EMAP_PROXY_CGI_2 = '<?php echo $D_DIR_BASE_G; ?>zdcemaphttp2.cgi';		<?php // add 2012/09/10 Y.Matsukawa ?>

	var ZdcEmapHttpCnt = 0;
	var ZdcEmapHttpResult = new Array();
	var ZdcEmapHttpTimeoutCnt = new Array();
	var ZdcEmapHttpFunctionReference = new Array();
	var ZdcEmapHttpEncodeFlg = new Array();

	ZdcEmapHttpGetResult = function(cnt) {
		if(ZdcEmapHttpTimeoutCnt[cnt] == "domain error") {
			ZdcEmapHttpFunctionReference[cnt](null,9);
			ZdcEmapHttpClear(cnt);
			return;
		}
		if(ZdcEmapHttpTimeoutCnt[cnt] == "no file") {
			ZdcEmapHttpFunctionReference[cnt](null,9);
			ZdcEmapHttpClear(cnt);
			return;
		}
		if(ZdcEmapHttpTimeoutCnt[cnt] == "abort") {
			ZdcEmapHttpFunctionReference[cnt](null,4);
			ZdcEmapHttpClear(cnt);
			return;
		}
		ZdcEmapHttpTimeoutCnt[cnt] --;
		if(ZdcEmapHttpTimeoutCnt[cnt] < 0) {
			ZdcEmapHttpFunctionReference[cnt](null,3);
			ZdcEmapHttpClear(cnt);
			return;
		}
		if(!ZdcEmapHttpResult[cnt]) {
			setTimeout('ZdcEmapHttpGetResult('+cnt+')', ZDC_EMAP_CGI_INTERVAL);
			return;
		}
		if(ZdcEmapHttpEncodeFlg[cnt]) {
			ZdcEmapHttpFunctionReference[cnt](decodeURIComponent(ZdcEmapHttpResult[cnt]),0);
		}else{
			ZdcEmapHttpFunctionReference[cnt](ZdcEmapHttpResult[cnt],0);
		}

		ZdcEmapHttpClear(cnt);
	}

	ZdcEmapHttpClear  = function(cnt) {
		var elm = document.getElementById(ZDC_EMAP_CGI_AJAX+cnt);
		if(elm) document.body.removeChild(elm);
		delete elm;
		delete ZdcEmapHttpResult[cnt];
		delete ZdcEmapHttpFunctionReference[cnt];
		delete ZdcEmapHttpEncodeFlg[cnt];
	}

	ZdcEmapHttpRequest = function(charset, enc, encodeflg)
	{
		this.cnt = 0;
		this.aborted = false;
		this.charset = charset || "SJIS";
		this.enc = enc || '';
		this.encodeflg = (encodeflg==undefined) ? 0 : encodeflg;
	}

	<?php //ZdcEmapHttpRequest.prototype.request = function(target_url, funcitonReference, timeout){	mod 2012/09/10 Y.Matsukawa ?>
	<?php //ZdcEmapHttpRequest.prototype.request = function(target_url, funcitonReference, timeout, typ){	// mod 2016/03/18 Y.Matsukawa ?>
	ZdcEmapHttpRequest.prototype.request = function(target_url, funcitonReference, timeout, typ, noref){
		var httpObj;
		try {
			httpObj = document.createElement('script');
			switch (this.charset){
				case 'SJIS':  httpObj.charset = 'Shift_JIS'; break;
				case 'UTF8':  httpObj.charset = 'UTF-8'; break;
				case 'EUC':   httpObj.charset = 'EUC-JP'; break;
				default:      httpObj.charset = this.charset; break;
			}
		} catch(e) {
			httpObj = false;
		}
		if(! httpObj) {
			this.httpObjGenerateFail();
		}
		
		if( timeout == undefined ){ timeout = 5*1000; }

		ZdcEmapHttpCnt ++;
		httpObj.id = ZDC_EMAP_CGI_AJAX+ZdcEmapHttpCnt;
		httpObj.setAttribute("type","text/javascript");
		<?php //httpObj.src = ZDC_EMAP_PROXY_CGI+"?target="+encodeURIComponent(target_url)+"&zdccnt="+ZdcEmapHttpCnt+"&enc="+this.enc+"&encodeflg="+this.encodeflg;		mod 2012/09/10 Y.Matsukawa ?>
		<?php // add 2012/09/10 Y.Matsukawa [ ?>
		if (typ == 2) {
			httpObj.src = ZDC_EMAP_PROXY_CGI_2;
		} else {
			httpObj.src = ZDC_EMAP_PROXY_CGI;
		}
		httpObj.src += "?target="+encodeURIComponent(target_url)+"&zdccnt="+ZdcEmapHttpCnt+"&enc="+this.enc+"&encodeflg="+this.encodeflg;
		if (noref) httpObj.src += "&NOREF=1";	<?php // add 2016/03/18 Y.Matsukawa ?>
		<?php // add 2012/09/10 Y.Matsukawa ] ?>
		ZdcEmapHttpFunctionReference[ZdcEmapHttpCnt] = funcitonReference;
		ZdcEmapHttpTimeoutCnt[ZdcEmapHttpCnt] = timeout / ZDC_EMAP_CGI_INTERVAL;
		ZdcEmapHttpResult[ZdcEmapHttpCnt] = "";
		ZdcEmapHttpEncodeFlg[ZdcEmapHttpCnt] = this.encodeflg;
		document.body.appendChild(httpObj);
		setTimeout('ZdcEmapHttpGetResult('+ZdcEmapHttpCnt+')',ZDC_EMAP_CGI_INTERVAL);
		
		this.cnt = ZdcEmapHttpCnt;

		return;
	}

	ZdcEmapHttpRequest.prototype.httpObjGenerateFail = function() {
		alert('No Support on your Browser.');
		return false;
	}

	ZdcEmapHttpRequest.prototype.abort = function() {
		ZdcEmapHttpTimeoutCnt[this.cnt] = "abort";
	}

	ZdcEmapHttpRequest.prototype.setInterval = function(val) {
		ZDC_EMAP_CGI_INTERVAL = val;
	}

	var ZdcEmapStatusCode = {
		0 : 'Success',
		1 : 'Parameter Error',
		2 : 'Server Error',
		3 : 'Timeout',
		4 : 'Abort',
		5 : 'No Hit Data',
		6 : 'Auth Error',
		9 : 'Error'
	}

	window.ZdcEmapHttpTimeoutCnt = ZdcEmapHttpTimeoutCnt;
	window.ZdcEmapHttpRequest = ZdcEmapHttpRequest;
	window.ZdcEmapHttpResult = ZdcEmapHttpResult;
	window.ZdcEmapStatusCode = ZdcEmapStatusCode;

})();
