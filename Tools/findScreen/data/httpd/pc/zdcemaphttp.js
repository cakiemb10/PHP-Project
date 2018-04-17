<?PHP
// ------------------------------------------------------------
// 汎用javasctipt AJAX通信モジュール
// 
// 開発履歴
//   2007/03/01 bando@D&I
//     JSAPIのzdchttp.js(2007/02/23時点)をベースに新規作成
// ------------------------------------------------------------
//include("d_serv_js.inc");
?>

//ZdcEmapHttpRequest Namespace
(function()
{
	//common vars
	var ZDC_EMAP_CGI_INTERVAL = 50; 
	var ZDC_EMAP_CGI_AJAX = 'ZdcEmapAjax'; 
	var ZDC_EMAP_PROXY_CGI = './zdcemaphttp.cgi';

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

	ZdcEmapHttpRequest.prototype.request = function(target_url, funcitonReference, timeout){
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
		httpObj.src = ZDC_EMAP_PROXY_CGI+"?target="+encodeURIComponent(target_url)+"&zdccnt="+ZdcEmapHttpCnt+"&enc="+this.enc+"&encodeflg="+this.encodeflg;
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
