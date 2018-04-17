// ------------------------------------------------------------
// ドラッグ＆ドロップ制御
// 
// 開発履歴
//   2008/03/19 matsukawa   新規作成
// ------------------------------------------------------------
var ZdcEmapDraggableCounter = -1;
var ZdcEmapDraggableStartPos = new Array();
var ZdcEmapDraggableStartObjPos = new Array();
var ZdcEmapDraggableActiveObj = false;

var MSIEWIN = (navigator.userAgent.indexOf('MSIE')>=0 && navigator.userAgent.indexOf('Win')>=0 && navigator.userAgent.toLowerCase().indexOf('opera')<0)?true:false;
var opera = navigator.userAgent.toLowerCase().indexOf('opera')>=0?true:false;

function ZdcEmapDraggableCancelEvent()
{
	return (ZdcEmapDraggableCounter==-1)?true:false;
}

function ZdcEmapDraggableInit(e)
{
	if(document.all)e = event;
	ZdcEmapDraggableCounter = 0;
	ZdcEmapDraggableStartPos = [e.clientX,e.clientY];
	ZdcEmapDraggableStartObjPos = [ZdcEmapDraggableActiveObj.offsetLeft,ZdcEmapDraggableActiveObj.offsetTop];
	ZdcEmapDraggableStart();
	if(!MSIEWIN)return false;
}

function ZdcEmapDraggableStart()
{
	if(ZdcEmapDraggableCounter>=0 && ZdcEmapDraggableCounter<=10){
		ZdcEmapDraggableCounter++;
		setTimeout('ZdcEmapDraggableStart()',5);
	}
}

function ZdcEmapDraggableStop(e)
{
	if(document.all)e = event;
	ZdcEmapDraggableCounter=-1;
}

function ZdcEmapDraggableMove(e)
{
	if(document.all)e = event;
	if(ZdcEmapDraggableCounter>=10){
		ZdcEmapDraggableActiveObj.style.left = ZdcEmapDraggableStartObjPos[0] + e.clientX - ZdcEmapDraggableStartPos[0]  + 'px';
		ZdcEmapDraggableActiveObj.style.top = ZdcEmapDraggableStartObjPos[1] + e.clientY - ZdcEmapDraggableStartPos[1]  + 'px';
	}
	if(!document.all)return false;
}

function ZdcEmapDraggableById(id)
{
	var obj = document.getElementById(id);
	ZdcEmapDraggable(obj);
}

function ZdcEmapDraggable(obj)
{
	if (!obj) return;
	ZdcEmapDraggableActiveObj = obj;
	ZdcEmapDraggableActiveObj.onmousedown = ZdcEmapDraggableInit;
	document.documentElement.onmouseup = ZdcEmapDraggableStop;
	document.documentElement.onmousemove = ZdcEmapDraggableMove;
	document.documentElement.ondragstart = ZdcEmapDraggableCancelEvent;
	document.documentElement.onselectstart = ZdcEmapDraggableCancelEvent;
}
