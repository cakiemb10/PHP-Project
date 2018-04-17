<?php
// ------------------------------------------------------------
// 定義ファイル javascriptのコードが主なもの
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2010/07/20 Y.Matsukawa	SSL対応
// ------------------------------------------------------------
// 地図のユーザーコントロール ------------------------------
//カーソル
if(!isset($D_JSCODE_MAPUSRCTL)) $D_JSCODE_MAPUSRCTL = <<< EOF
	ZdcEmapMapUsrctl = new ZdcUserControl();
	var ZdcEmapMapUsrctl_imgurl = svrurl + "/usrimg/emapControl-move.png";
	var ZdcEmapMapUsrctl_shdurl = svrurl + "/usrimg/emapControl-move-shadow.png";
	var ZdcEmapMapUsrctl_size = new ZdcSize(54,54);
	var ZdcEmapMapUsrctl_shdsize = new ZdcSize(60,60);
	ZdcEmapMapUsrctl.setImage(ZdcEmapMapUsrctl_imgurl,ZdcEmapMapUsrctl_size,ZdcEmapMapUsrctl_shdurl,ZdcEmapMapUsrctl_shdsize);
	ZdcEmapMapUsrctl.setDocPosition(0,0,0,0);   //img position shd position
	ZdcEmapMapUsrctl.setAction(1,19,0,35,16);    //actionid,pixel area
	ZdcEmapMapUsrctl.setAction(2,0,19,16,35);
	ZdcEmapMapUsrctl.setAction(3,38,19,54,35);
	ZdcEmapMapUsrctl.setAction(4,19,38,35,54);
	ZdcEmapMapUsrctl.setAction(5,19,19,35,35);
	ZdcEvent.addListener(ZdcEmapMapUsrctl,"clickend",function(){
		var tmpx = parseInt(parseInt(ZdcEmapMapSize.width) * 3 / 5);
		var tmpy = parseInt(parseInt(ZdcEmapMapSize.height) * 3 / 5);
		switch(this.actionid){
			case 0:
				break;
			case 1:
				ZdcEmapMapObj.scrollMap(0,tmpy);
				break;
			case 2:
				ZdcEmapMapObj.scrollMap(tmpx,0);
				break;
			case 3:
				ZdcEmapMapObj.scrollMap(tmpx*-1,0);
				break;
			case 4:
				ZdcEmapMapObj.scrollMap(0,tmpy*-1);
				break;
			case 5:
				ZdcEmapMapObj.restoreMapLocation();
				break;
		}
	});
	ZdcEmapMapObj.addUserControl(ZdcEmapMapUsrctl,10,ZdcEmapMapObj.ZdcMapWpx - 75);
EOF;
//ズーム
if(!isset($D_JSCODE_MAPZOOMCTL)) $D_JSCODE_MAPZOOMCTL = <<< EOF
	ZdcEmapMapZoomctl = new ZdcUserZoomControl();
	var ZdcEmapMapZoomctl_imgurl = svrurl + "/usrimg/emapControl-scale.png";
	var ZdcEmapMapZoomctl_shdurl = svrurl + "/usrimg/emapControl-scale-shadow.png";
	var ZdcEmapMapZoomctl_grdurl = svrurl + "/usrimg/emapControl-scale-grid.png";
	var ZdcEmapMapZoomctl_size = new ZdcSize(16,148);
	var ZdcEmapMapZoomctl_shdsize = new ZdcSize(22,154);
	var ZdcEmapMapZoomctl_grdsize = new ZdcSize(16,6);
	ZdcEmapMapZoomctl.setImage(ZdcEmapMapZoomctl_imgurl,ZdcEmapMapZoomctl_size,ZdcEmapMapZoomctl_grdurl,ZdcEmapMapZoomctl_grdsize,ZdcEmapMapZoomctl_shdurl,ZdcEmapMapZoomctl_shdsize);
	ZdcEmapMapZoomctl.setDocPosition(0,0,0,0,-1,0); //basedoc shadowdoc griddoc
	ZdcEmapMapZoomctl.setAction('zoomOut',0,0,16,16);      //- action id,pixel area
	ZdcEmapMapZoomctl.setAction('zoomIn',0,132,16,148);   //+
	ZdcEmapMapZoomctl.setAction('slither',0,18,16,126,6);  //action id,pixel area slitherweight
	ZdcEmapMapZoomctl.setAction('setzoom',0,18,16,126);    //action id,pixel area
	if({$D_MAP_SCALE_MAX} > -1 && {$D_MAP_SCALE_MIN} > -1)
		ZdcEmapMapZoomctl.setZoomLimit( {$D_MAP_SCALE_MAX}, {$D_MAP_SCALE_MIN} );
	ZdcEvent.addListener(ZdcEmapMapZoomctl,"clickend",function(){
		switch(this.actionid){
			case 'none': 
				break; 
			case 'zoomOut': 
				ZdcEmapMapObj.mapZoomOut();
				this.setSlitherPosition();
				break;
			case 'zoomIn': 
				ZdcEmapMapObj.mapZoomIn();
				this.setSlitherPosition();
				break;
			case 'setzoom': 
				var s = this.getZoom();
				ZdcEmapMapObj.setMapScale(s);
				this.setSlitherPosition();
			break;
		}
	});
	ZdcEvent.addListener(ZdcEmapMapZoomctl,"mousedowngrid",function(){
		if(this.actionid=='slither'){
			this.dragstart(1);
			return false;
		}
	});
	ZdcEvent.addListener(ZdcEmapMapZoomctl,"mouseup",function(){
		if(this.actionid=='slither'){
			this.dragend();
		}
	});
	ZdcEmapMapObj.addUserZoomControl(ZdcEmapMapZoomctl,78,ZdcEmapMapObj.ZdcMapWpx - 55);   //(doc,top,left);	
EOF;
// メッセージウィンドウ関係 --------------------------------
// 拠点吹き出し
if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
	ZdcEmapMsg.setImage('{$D_DIR_BASE_G}img/msg/0000.png',new ZdcSize(253,239),
	                    '{$D_DIR_BASE_G}img/msg/0000-t.png',new ZdcSize(224,180),
	                    '{$D_DIR_BASE_G}img/msg/0000-x.png',new ZdcSize(13,13),
	                    '{$D_DIR_BASE_G}img/msg/0000-s.png',new ZdcSize(325,144),
	                    '{$D_DIR_BASE_G}img/msg/0000-p.gif');
	ZdcEmapMsg.setDocPosition(0,0,11,8,11,233,95,0);
	ZdcEmapMsg.setDocOffset(0,-239);
	ZdcEmapMsg.setTextClass("UserMsgWindowTextStyle");
EOF;
?>
