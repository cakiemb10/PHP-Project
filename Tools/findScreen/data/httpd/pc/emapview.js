<?PHP
// ------------------------------------------------------------
// 地図制御javasctipt メイン
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2007/11/16 Y.Matsukawa	初期表示時に地図APIのChangeLocationイベントが３回発生する→２回に減らす
// 2007/11/30 Y.Matsukawa	ZdcEmapInitに任意の縮尺指定可能に
// 2008/04/01 Y.Matsukawa	地図上で手カーソル
// 2008/05/07 Y.Matsukawa	【IE6不具合対応】地図画面のリストボックスが検索ウィンドウの上に出てくる
// 2008/10/22 Y.Matsukawa	使用しないJSはロードしない
// 2008/11/26 Y.Matsukawa	【不具合対応】拠点アイコンに透過GIFを使用している場合、IEで印刷時に透過しない。
// 2009/02/16 Y.Matsukawa	【不具合改修】（FFのみ）アイコンマウスインで吹き出し表示の場合：地図中心のアイコン上にマウスを置いていると、吹き出しが表示／非表示を繰り返す
//                          （waitメッセージが表示→非表示されると、その度にマウスインイベントが発生するようなので、吹き出しではwaitメッセージは出さないようにする）
// 2009/03/04 Y.Matsukawa	遷移履歴の直近へ戻るリンク
// 2009/05/28 Y.Matsukawa	地図中心マーク表示
// 2009/06/02 Y.Matsukawa	【不具合修正】拠点エリア検索で使用する項目にHTMLタグ（<BR><B>）を入力すると、動作・表示不正
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2009/10/14 Y.Matsukawa	マウスアウトで吹き出しを消す
// 2009/11/07 Y.Matsukawa	拠点項目拡張（50→200）
// 2010/01/06 Y.Matsukawa	【不具合修正】シングルクリックで地図移動が無効になっていた
// 2010/02/02 Y.Matsukawa	拠点アイコンイベント無しの場合はカーソル変更しない
// 2010/03/23 Y.Matsukawa	パンくず直近リンク複数対応
// 2010/07/08 Y.Matsukawa	【不具合修正】パンくずTOPリンクをwindow.close()にして、クローズをキャンセルすると、パンくずがクリアされてしまう
// 2010/07/14 Y.Matsukawa	地図操作禁止モード
// 2010/07/23 Y.Matsukawa	ルート距離表示
// 2010/08/09 Y.Matsukawa	コントローラを個別に消去可能にする
// 2011/02/10 Y.Matsukawa	高速化
// 2011/02/17 Y.Matsukawa	【不具合修正】高速化で縮尺をコンストラクタで指定するようにしたら地図初期表示時にスライダー位置が不正に
// 2011/02/22 Y.Matsukawa	上記不具合修正を元に戻す（API側が対応した為）
// 2011/05/26 K.Masuda		TOPに戻る際、クエリを付与する
// 2011/06/15 K.Masuda		フキダシ表示中でも再検索できるようにする
// 2011/06/16 Y.Matsukawa	詳細更新時にJS実行
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/11/25 Y.Matsukawa	ピーシーデポ対応（最寄りルート専用モード）
// 2012/05/28 K.Masuda		最初の中心点に戻るリンク追加
// 2015/03/23 K.Iwayoshi	三井住友銀行来店予約対応カスタマイズ
// 2016/11/15 K.Tani		地図操作時に再検索しないモード
// ------------------------------------------------------------
include("./inc/define.inc");  // 基本設定
include("./inc/define_get_icon.inc");  // アイコン情報取得
?>
//-------------------------------------------------------------
//JSAPIの動作確認
//-------------------------------------------------------------
if(parseInt(ZDC_RC) != 0) {
	//location.href = '<?PHP echo $D_URL_JSAPIERROR; ?>';
}

//-------------------------------------------------------------
//初期設定
//-------------------------------------------------------------
//地図
var ZdcEmapMapObj = null;
var ZdcEmapMapUsrctl = null;
var ZdcEmapMapZoomctl = null;
var ZdcEmapMapSize = new ZdcWindow();
//ユーザーレイヤー
var ZdcEmapMapUserLyr = new ZdcUserLayer();
var ZdcEmapMapUserLyrId = null;
//マーカー記憶
var ZdcEmapMapShopMrkId = new Array(<?PHP echo $D_SHOP_MAX; ?>);
var ZdcEmapMapShopMrkCnt = null;
var ZdcEmapMapPoiMrkId = new Array(<?PHP echo $D_POI_MAX; ?>);
var ZdcEmapMapPoiMrkCnt = null;
var ZdcEmapMapShopDetailMrkId = null;
var ZdcEmapMapCurFocusMrkId = null;
//吹き出し
var ZdcEmapMsg = new ZdcUserMsgWindow();
//小窓
var ZdcEmapListObj;
var ZdcEmapDetailObj;
var ZdcEmapCondObj;
var ZdcEmapSearchWindowObj;
var ZdcEmapIE6HideSelectObj;	// add 2008/05/07 Y.Matsukawa
//Myエリア追加用表示エリア
var ZdcEmapMyareaWrapperObj;
//各ボタンのイベント管理
var ZdcEmapSearchClickFlg = 0;
//ルート探索モード		<?php // add 2011/11/25 Y.Matsukawa ?>
var ZdcEmapRouteShopItems = null;
var ZdcEmapRouteShopItem = null;
var ZdcEmapRouteStartLat = null;
var ZdcEmapRouteStartLon = null;
//アイコン情報
var ZdcEmapIconImg = new Array();
var ZdcEmapIconW = new Array();
var ZdcEmapIconH = new Array();
var ZdcEmapIconOffsetX = new Array();
var ZdcEmapIconOffsetY = new Array();
<?PHP
foreach( $D_ICON as $key=>$val) {
	printf("ZdcEmapIconImg['%s'] = '%s';",$key,$val["IMG"]);
	printf("ZdcEmapIconW['%s'] = %d;",$key,$val["W"]);
	printf("ZdcEmapIconH['%s'] = %d;",$key,$val["H"]);
	printf("ZdcEmapIconOffsetX['%s'] = %d;",$key,ceil($val["W"]/2)*-1);
	printf("ZdcEmapIconOffsetY['%s'] = %d;",$key,ceil($val["H"]/2)*-1);
}
?>
//その他
<?php if(isset($D_REQ_JSAPI["zdcmapgeometric"]) && $D_REQ_JSAPI["zdcmapgeometric"]){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapGeometricObj = new ZdcGeometric();
<?php } ?>
var ZdcEmapSaveCond = new Array(<?PHP echo $D_SHOP_MAX; ?>);//絞込条件
<?PHP //for($i = 0;$i < 50;$i ++) if($_VARS["cond".$i]) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]);		mod 2009/11/07 Y.Matsukawa ?>
<?php //mod 2011/07/05 Y.Nakajima ?>
<?PHP for($i = 1;$i <= 200;$i ++) if(isset($_VARS["cond".$i])) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]); ?>

// add 2011/05/26 K.Masuda [
var QSTRING = location.search.replace(/^\?/, '');
// add 2011/05/26 K.Masuda ]
//初期化関数
//function ZdcEmapInit(){	2007/11/16 mod Y.Matsukawa
//function ZdcEmapInit(init_lat, init_lon){		2007/11/30 mod Y.Matsukawa
function ZdcEmapInit(init_lat, init_lon, init_lv){
	//地図の基本設定 ----------------------------------------
	var svrurl = "<?PHP echo $D_JS_SVRURL; ?>";
<?php	//ZdcEmapMapObj = new ZdcMap(document.getElementById("ZdcEmapMap"));	del 2011/02/10 Y.Matsukawa ?>
<?php // add 2011/02/10 Y.Matsukawa [ ?>
	//初期位置
	if (!init_lat || !init_lon) {
		init_lat = <?PHP echo $D_INIT_LAT; ?>;
		init_lon = <?PHP echo $D_INIT_LON; ?>;
	}
	if (!init_lv || init_lv == 0) {
		init_lv = <?PHP echo $D_INIT_LVL; ?>;
	}
	ZdcEmapMapObj = new ZdcMap(document.getElementById("ZdcEmapMap"), 
								new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>),
								init_lv,
								<?PHP echo $D_MAP_LAYER_KBN; ?>);
<?php // add 2011/02/10 Y.Matsukawa ] ?>
	ZdcEmapMapSize = ZdcEmapMapObj.getMapWindowSize();
	//地図中心マーク ---------------------------------	add 2009/05/28 Y.Matsukawa
	<?php if (isset($D_MAPCENTER_MARK) && $D_MAPCENTER_MARK != "" && $D_MAPCENTER_MARK > 0) { ?>
	ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK; ?>'));
	<?php } ?>
	//ユーザーコントロール ---------------------------------
	<?PHP echo $D_JSCODE_MAPUSRCTL; ?>
	<?PHP echo $D_JSCODE_MAPZOOMCTL; ?>
	
	//その他地図関係 ---------------------------------------
	ZdcEmapMapObj.setMouseCursor("hand");	// 2008/04/01 add Y.Matsukawa
	ZdcEmapMapObj.CenterFirst = false;
	ZdcEmapMapObj.setScreenMode();
	//ZdcEmapMapObj.setMapType(<?PHP echo $D_MAP_LAYER_KBN; ?>);		del 2011/02/10 Y.Matsukawa
	ZdcEmapMapObj.reflashMap();
	if(<?PHP echo $D_MAP_SCALE_MAX; ?> > -1 && <?PHP echo $D_MAP_SCALE_MIN; ?> > -1)
		ZdcEmapMapObj.setMapZoomLimit(<?PHP echo $D_MAP_SCALE_MAX; ?>,<?PHP echo $D_MAP_SCALE_MIN; ?>);
	//標準コントロール
	if(ZdcEmapMapUsrctl == null && ZdcEmapMapZoomctl == null && <?PHP echo $D_MAP_CONTROL; ?> > 0)
		ZdcEmapMapObj.addMapControl(new ZdcControl(<?PHP echo $D_MAP_CONTROL; ?>));
	//if (ZdcEmapMapZoomctl) ZdcEmapMapZoomctl.setSlitherPosition();		// add 2011/02/17 Y.Matsukawa	del 2011/02/22 Y.Matsukawa
	//標準スケールバー
	if(<?PHP echo $D_MAP_SCALEBAR; ?> > 0) ZdcEmapMapObj.addMapScaleBar(new ZdcScaleBar(<?PHP echo $D_MAP_SCALEBAR; ?>));
	//標準中心アイコン
	if(<?PHP echo $D_MAP_CENTER; ?> > 0) {
		var obj = new ZdcMapCenter(<?PHP echo $D_MAP_CENTER; ?>);
		obj.doc.zIndex=2999;//アイコンを背面にもっていく
		ZdcEmapMapObj.addMapCenter(obj);
	}
	//情報ボックス
	if(<?PHP echo $D_MAP_INFO; ?> > 0) ZdcEmapMapObj.addMapCenterInfoBox(new ZdcMapCenterInfoBox(<?PHP echo $D_MAP_INFO; ?>));

	<?php // add 2010/08/09 Y.Matsukawa [ ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($D_MAP_REMOVE_CONTROL) && $D_MAP_REMOVE_CONTROL != "") { ?>
	//コントロール消去
	ZdcEmapMapObj.removeUserControl();
	ZdcEmapMapObj.removeMapControl();
	<?php } ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($D_MAP_REMOVE_ZOOMCONTROL) && $D_MAP_REMOVE_ZOOMCONTROL != "") { ?>
	//ズームコントロール消去
	ZdcEmapMapObj.removeUserZoomControl();
	<?php } ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($D_MAP_DRAG_OFF) && $D_MAP_DRAG_OFF != "") { ?>
	//地図ドラッグ禁止
	ZdcEmapMapObj.dragOff();
	<?php } ?>
	<?php // add 2010/08/09 Y.Matsukawa ] ?>

	//
	ZdcEmapMapObj.ZdcMapRasterEngine = false;
<?php // del 2011/02/10 Y.Matsukawa [ ?>
	//	//初期位置
	//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(<?PHP echo $D_INIT_LON; ?>,<?PHP echo $D_INIT_LAT; ?>,<?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);		2007/11/16 mod Y.Matsukawa
	//	if (!init_lat || !init_lon) {
	//		init_lat = <?PHP echo $D_INIT_LAT; ?>;
	//		init_lon = <?PHP echo $D_INIT_LON; ?>;
	//	}
	//	// 2007/11/30 add Y.Matsukawa ↓
	//	//if (!init_lv) {		mod 2009/09/04 Y.Matsukawa
	//	if (!init_lv || init_lv == 0) {
	//		init_lv = <?PHP echo $D_INIT_LVL; ?>;
	//	}
	//	// 2007/11/30 add Y.Matsukawa ↑
	//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);	2007/11/30 mod Y.Matsukawa
	//	ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), init_lv);
<?php // del 2011/02/10 Y.Matsukawa ] ?>
	ZdcEmapMapObj.saveMapLocation();
	//クリック動作区分
	if(<?PHP echo $D_MAP_CLICK_KBN; ?> == 2) {
		<?PHP // ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnodrag", function(e) {	mod 2010/01/06 Y.Matsukawa ?>
		ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnomove", function(e) {
			this.scrollToCenter(new ZdcPoint(this.MouseCLon,this.MouseCLat)); 
		});
	}
	//ホイールズーム区分
	if(<?PHP echo $D_MAP_WHEEL_KBN; ?> == 0) {
		ZdcEmapMapObj.setWheelOff();
	} else {
		ZdcEmapMapObj.setWheelOn();
	}
	
	//各e-map用コントロール --------------------------------
	//リスト表示部
	ZdcEmapListObj  = document.getElementById('ZdcEmapList');
	if(!ZdcEmapListObj) ZdcEmapListObj = document.createElement('DIV');//light用ダミー
	//詳細表示部
	ZdcEmapDetailObj = document.getElementById('ZdcEmapDetail');
	if(!ZdcEmapDetailObj) ZdcEmapDetailObj = document.createElement('DIV');//light用ダミー
	//検索条件指定部
	ZdcEmapCondObj = document.getElementById('ZdcEmapCond');
	if(!ZdcEmapCondObj) ZdcEmapCondObj = document.createElement('DIV');//light用ダミー
	//検索窓
	ZdcEmapSearchWindowObj = document.getElementById('ZdcEmapSearchWindow');
	if(!ZdcEmapSearchWindowObj) ZdcEmapSearchWindowObj = document.createElement('DIV');//light用ダミー
	//【IE6不具合対応】地図画面のリストボックスが検索ウィンドウの上に出てきてしまうのを隠すためのdiv	add 2008/05/07 Y.Matsukawa
	ZdcEmapIE6HideSelectObj = document.getElementById('ZdcEmapIE6HideSelect');
	//Myエリア追加用表示エリア
	ZdcEmapMyareaWrapperObj = document.getElementById('myareaWrapper');

	
	//その他 -----------------------------------------------
	//ユーザーレイヤー
	ZdcEmapMapUserLyr.setLayerScale(<?PHP echo $D_VIEW_ICON_MAX; ?>,<?PHP echo $D_VIEW_ICON_MIN; ?>);
	ZdcEmapMapUserLyr.setLayerType('manual');
	ZdcEmapMapUserLyr.clearMarker();
	ZdcEmapMapUserLyrId = ZdcEmapMapObj.addUserLayer(ZdcEmapMapUserLyr); 
	//画面遷移履歴初期化
	ZdcEmapHistoryClear();
	//処理中アイコン
	ZdcEmapMapObj.addZdcWait(parseInt(parseInt(ZdcEmapMapSize.height) / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETY; ?>),
							 parseInt(parseInt(ZdcEmapMapSize.width)  / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETX; ?>),'<?PHP echo $D_MAP_WAIT_MSG; ?>');
}



//-------------------------------------------------------------
//地図制御
//-------------------------------------------------------------
//地図上にカーソル表示
var ZdcEmapMapCurMrkId = null;
function ZdcEmapMapCursorSet(lat, lon){
	//アイコンの作成
	var mrk = ZdcEmapMakeMrk(0,lat,lon,
							 ZdcEmapIconW['@SELB'],ZdcEmapIconH['@SELB'],0,0,
							 ZdcEmapIconOffsetX['@SELB'],ZdcEmapIconOffsetY['@SELB'],0,0,0,0,
							 ZdcEmapIconImg['@SELB'],'',
							 '','',0,null,null,null);
	if(ZdcEmapMapCurMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);
	ZdcEmapMapCurMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
}
//地図上のカーソル外す
function ZdcEmapMapCursorRemove(){
	if (ZdcEmapMapCurMrkId != null) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);
		ZdcEmapMapCurMrkId = null;
	}
	//詳細表示中
	ZdcEmapMapFrontShopDetail();//詳細アイコンを前面にもってくる
	// 2011/06/15 K.Masuda mod [
	//ZdcEmapShopMsgClose();//吹き出しを消す
	<?php //mod 2011/07/05 Y.Nakajima ?>
	if( <?php if(isset($D_HUKIDASHI_SEARCH)){echo "false";}else{echo "true";} ?> ){
		ZdcEmapShopMsgClose();//吹き出しを消す
	}
	// 2011/06/15 K.Masuda mod ]
}
//地図移動
function ZdcEmapMapMove(lat, lon, lvl){
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//マップ移動
	//	if(lvl) ZdcEmapMapObj.setMapLocation(center,lvl);
	//		else ZdcEmapMapObj.setMapLocation(center);
	ZdcEmapMapObj.setMapLocation(center);
	if(lvl) ZdcEmapMapObj.setMapScale(lvl);
}
function ZdcEmapMapScroll(lat, lon){
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//マップ移動
	ZdcEmapMapObj.scrollToCenter(center);
}
//地図移動
function ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,pt,noin){
	var p1 = new ZdcPoint(minlon,minlat,<?PHP echo $D_PFLG; ?>);
	var p2 = new ZdcPoint(maxlon,maxlat,<?PHP echo $D_PFLG; ?>);
	var bx = new ZdcBox(p1,p2);
	if(pt != null) {
		var s = ZdcEmapMapObj.getMapBoxScale(bx,pt);
		ZdcEmapMapObj.setMapLocation(pt);
		if(noin != 1 || (noin == 1 && s < ZdcEmapMapObj.getMapScale())) ZdcEmapMapObj.setMapScale(s);
	} else {
		var s = ZdcEmapMapObj.getMapBoxScale(bx);
		ZdcEmapMapObj.setMapLocation(bx.getBoxCenter());
		if(noin != 1 || (noin == 1 && s < ZdcEmapMapObj.getMapScale())) ZdcEmapMapObj.setMapScale(s);
	}
}


//-------------------------------------------------------------
//画面遷移履歴関係
//-------------------------------------------------------------
var ZdcEmapHistoryCnt;
var ZdcEmapHistoryCntSv;		// add 2010/07/08 Y.Matsukawa
var ZdcEmapHistoryCntSvB;
var ZdcEmapHistoryName = new Array(10);
var ZdcEmapHistoryLink = new Array(10);
var ZdcEmapHistorySaveCnt;
var ZdcEmapHistorySaveName = new Array(10);
var ZdcEmapHistorySaveLink = new Array(10);
var ZdcEmapHistoryClicked = 0;
//クリック時の動作
function ZdcEmapHistoryClick(cnt) {
	ZdcEmapHistoryCntSvB = cnt;
	if(ZdcEmapReadCheck()) return;//読み込み中の動作がある
	if(!ZdcEmapHistoryLink[cnt]) return ;
<?php	// add 2011/06/16 Y.Matsukawa [ ?>
<?php	// カスタム関数が定義されていたら実行 ?>
	if (typeof ZdcEmapCFBeforeHistoryClick == 'function') {
		ZdcEmapCFBeforeHistoryClick();
	}
<?php	// add 2011/06/16 Y.Matsukawa ] ?>
	ZdcEmapHistoryCntSv = ZdcEmapHistoryCnt;		// add 2010/07/08 Y.Matsukawa
	ZdcEmapHistoryCnt = cnt - 1;
	ZdcEmapHistoryClicked = 1;
	eval(ZdcEmapHistoryLink[cnt]);
	ZdcEmapHistoryClicked = 0;
	
	// add 2015/03/23 K.Iwayoshi [
	//相談ボタン表示処理 オプションでSMBC_DETAIL_BUTTON_SHOW_FLAGフラグに１をセットしないと動作しない 
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		
		//非表示処理
		// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する[ 
		//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		// mod 2015/4/22]
		for(var i = 0 ; i < eles.length ; i++){
			eles[i].style.display = "none";
			eles[i].removeAttribute("value");
		}
		
		//相談ボタン表示フラグ
		ShowListButtonFlag = false;
	}
	// add 2015/03/23 K.Iwayoshi]
}

//遷移履歴のクリック動作がキャンセルされた場合に、履歴を元に戻す		add 2010/07/08 Y.Matsukawa
function ZdcEmapHistoryClickCancel() {
	ZdcEmapHistoryCnt = ZdcEmapHistoryCntSv;
}
//ひとつ戻る
function ZdcEmapHistoryBack() {
	ZdcEmapHistoryClick(ZdcEmapHistoryCnt - 1)
	
	// add 2015/03/23 K.Iwayoshi [
	//相談ボタン表示処理 オプションでSMBC_DETAIL_BUTTON_SHOW_FLAGフラグに１をセットしないと動作しない
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する[
		//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
		// mod 2015/04/22]
		for(var i = 0 ; i < eles.length ; i++){
			eles[i].style.display = "none";
			eles[i].removeAttribute("value");
		}
		
		//相談ボタン表示フラグ
		ShowListButtonFlag = false;
		
	}
	// add 2015/03/23 K.Iwayoshi ]
}
//追加
function ZdcEmapHistoryAdd(name,link) {
	ZdcEmapHistoryCnt ++;
	//かぶるページがあれば戻す（ページ遷移や戻るボタン用の対応)
	for(var i = 1;i < ZdcEmapHistoryCnt;i ++) {
		if(ZdcEmapHistoryLink[i] == link) {
			ZdcEmapHistoryCnt = i;
			break;
		}
	}
	//登録
	ZdcEmapHistorySet(ZdcEmapHistoryCnt,name,link);
}
//変更
function ZdcEmapHistoryChange(name,link) {
	ZdcEmapHistorySet(ZdcEmapHistoryCnt,name,link);
}
//クリア
function ZdcEmapHistoryClear() {
	ZdcEmapHistoryCnt = 0;
	// mod 2011/05/26 K.Masuda [
	//ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP echo $D_HISTORY_TOP_NAME; ?>","<?PHP echo $D_HISTORY_TOP_LINK; ?>");
	<?php //mod 2011/07/05 Y.Nakajima ?>
	if( <?php if(isset($D_QUERY_STRING)){echo "true";}else{echo "false";} ?> ){
		ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP echo $D_HISTORY_TOP_NAME; ?>","<?PHP echo $D_HISTORY_TOP_LINK; ?>+QSTRING");
	} else {
		ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP echo $D_HISTORY_TOP_NAME; ?>","<?PHP echo $D_HISTORY_TOP_LINK; ?>");
	}
	// mod 2011/05/26 K.Masuda ]
}
//登録本処理
function ZdcEmapHistorySet(cnt,name,link) {
	ZdcEmapHistoryName[cnt] = name;
	ZdcEmapHistoryLink[cnt] = link;
	ZdcEmapHistoryRefresh();
}
//再描画
function ZdcEmapHistoryRefresh() {
	var html = "",name= "",tmp = "";
	var html_last = "";		// add 2009/03/04 Y.Matsukawa
	var html_last_arr = new Array();		// add 2010/03/23 Y.Matsukawa
	for(var i = 0;i < ZdcEmapHistoryCnt+1;i ++) {
		//htmlエンテイテイ
		name = "";
		tmp = ZdcEmapHistoryName[i];
		// add 2009/06/02 Y.Matsukawa [
		// HTMLタグはスペースに置換して表示
		tmp = tmp.replace(/<br>/ig, " ");
		tmp = tmp.replace(/<b>/ig, " ");
		tmp = tmp.replace(/<\/b>/ig, " ");
		// add 2009/06/02 Y.Matsukawa ]
		for (var j = 0; j < tmp.length; j++){
			var k = tmp.charAt(j);
			name += {'<':'&lt;', '>':'&gt;', '&':'&amp;', '"':'&quot;'}[k] || k;
		}
		//画面に追加
		if(html) html += "<?PHP echo $D_HISTORY_SEP; ?>";
		if(ZdcEmapHistoryLink[i] && i != ZdcEmapHistoryCnt) {
			html += '<a href="javascript:ZdcEmapHistoryClick('+i+');">'+name+'</a>';
			html_last = '<a href="javascript:ZdcEmapHistoryClick('+i+');">';
			<?php //mod 2011/07/05 Y.Nakajima ?>
			html_last += '<?php if (isset($D_HISTORY_LAST_WORD)) echo $D_HISTORY_LAST_WORD; ?>';
			html_last += '</a>';	// add 2009/03/04 Y.Matsukawa
<?php	// add 2010/03/23 Y.Matsukawa [
		for ($j = 1; $j <= 5; $j++) {
?>
<?php		// mod 2011/7/5 Y.Nakajima ?>
			html_last_arr[<?php echo $j; ?>] = '<a href="javascript:ZdcEmapHistoryClick('+i+');"><?php if (isset($D_HISTORY_LAST_WORD_ARR[$j])) echo $D_HISTORY_LAST_WORD_ARR[$j]; ?></a>';
<?php	}
		// add 2010/03/23 Y.Matsukawa ]
?>
		} else {
			html += name;
		}
	}

	var obj = document.getElementById('history');
	if(obj) obj.innerHTML = html;
	// add 2009/03/04 Y.Matsukawa [
	var obj_last = document.getElementById('historyLast');
	if(obj_last) obj_last.innerHTML = html_last;
	// add 2009/03/04 Y.Matsukawa ]
	// add 2010/03/23 Y.Matsukawa [
	for (var i = 1; i <= 5; i++) {
		obj_last = null;
		obj_last = document.getElementById('historyLast'+i);
		if(obj_last && html_last_arr[i]) obj_last.innerHTML = html_last_arr[i];
	}
	// add 2010/03/23 Y.Matsukawa ]
}
//記憶
function ZdcEmapHistorySave() {
	for(i = 0;i < ZdcEmapHistoryCnt+1;i ++) {
		ZdcEmapHistorySaveName[i] = ZdcEmapHistoryName[i];
		ZdcEmapHistorySaveLink[i] = ZdcEmapHistoryLink[i];
	}
	ZdcEmapHistorySaveCnt  = ZdcEmapHistoryCnt;
}
//読込
function ZdcEmapHistoryLoad() {
	if(!ZdcEmapHistorySaveChk()) return;
	for(i = 0;i < ZdcEmapHistorySaveCnt+1;i ++) {
		ZdcEmapHistoryName[i] = ZdcEmapHistorySaveName[i];
		ZdcEmapHistoryLink[i] = ZdcEmapHistorySaveLink[i];
	}
	ZdcEmapHistoryCnt  = ZdcEmapHistorySaveCnt;
	ZdcEmapHistoryRefresh();
}
//記憶の有無チェック
function ZdcEmapHistorySaveChk() {
	return ZdcEmapHistorySaveCnt;
}
//画面履歴を押されてのアクションかチェック
function ZdcEmapHistoryClickChk() {
	return ZdcEmapHistoryClicked;
}



//-------------------------------------------------------------
//アイコン登録
//-------------------------------------------------------------
function ZdcEmapMakeMrk(id,lat,lon,
						sizew,sizeh,shadowsizew,shadowsizeh,
						offsetx,offsety,shdoffsetx,shdoffsety,msgoffsetx,msgoffsety,
						image,shadowimage,
						data1,data2,nflg,
						mouseclickmarker,mouseovermarker,mouseoutmarker
						,lvl			// add 2009/09/04 Y.Matsukawa
						) {
	//1,2,3
	//4,5,6,7
	//8,9,10,11,12,13
	//14(image),15
	//16,17,18
	//19,20,21
	//22

	//mod 2011/07/05 Y.nakajima [
	//lvlが数字でないときの処理を追加
	if (isNaN(lvl) || !lvl || lvl < 1 || lvl >18) lvl = 0;
	//mod 2011/07/05 Y.nakajima ]
	
	var p,mrk,item;
	var icon = new ZdcIcon();
	
	//アイコンの作成
	icon.size      = new ZdcSize(sizew, sizeh);
	icon.offset    = new ZdcPixel(offsetx, offsety);
	//icon.image    = image;	2008/11/26 Y.Matsukawa del
	// 2008/11/26 Y.Matsukawa add [
	// icon.imageの末尾が「.gif」でないと、内部的にGIF以外として処理されてしまうので、末尾を無理矢理「.gif」にしています。
	// GIF以外で処理されてしまうと、IEで印刷時に透過GIFが透過しません。
	// タイムスタンプ値を付加しているのは、キャッシュ抑制のためです。これがないと、アイコン画像を差し替えた際に表示が崩れることがあります。（IEのみ）
	if (image.substr(image.length-4, 4) == ".gif") {
		icon.image = image;
	} else {
		dd = new Date();
		ts = dd.getTime();
		if (image.indexOf('?') < 0) {
			icon.image = image+"?dummy="+ts+".gif";
		} else {
			icon.image = image+"&dummy="+ts+".gif";
		}
	}
	// 2008/11/26 Y.Matsukawa add ]
	if(shadowimage) {
		icon.shadowsize = new ZdcSize(shadowsizew, shadowsizeh);
		icon.shdoffset = new ZdcPixel(shdoffsetx,shdoffsety);
		icon.shadowimage   = shadowimage;
	}
	icon.msgoffset = new ZdcPixel(msgoffsetx,msgoffsety);
	//マーカーの作成
	p   = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	mrk = new ZdcMarker(p, icon);
	//マーカーの基本情報
	mrk.id     = id;
	mrk.data1  = data1;
	mrk.data2  = data2;
	mrk.nflg   = nflg;
	if (lvl) mrk.lvl = lvl;			// add 2009/09/04 Y.Matsukawa
	mrk.Point  = p;
	mrk.mouseclickmarker = mouseclickmarker;
	mrk.mouseovermarker  = mouseovermarker;
	mrk.mouseoutmarker   = mouseoutmarker;
	//マーカークリック時のイベント登録
	if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
	if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
	if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
	// イベントなしの時はマウスカーソルを変更しない		add 2010/02/02 Y.Matsukawa
	if (!mrk.mouseclickmarker && !mrk.mouseovermarker) mrk.setType('static');

	return mrk;
}



//-------------------------------------------------------------
//ルート探索
//-------------------------------------------------------------
var ZdcEmapRouteOptionsObj;
var ZdcEmapRouteSearchObj;
var ZdcEmapRoutePoint1 = null;
var ZdcEmapRoutePoint2 = null;
var ZdcEmapRouteName1  = null;
var ZdcEmapRouteName2  = null;
var ZdcEmapRouteFlagLayer;
var ZdcEmapRouteFlagIcon1;
var ZdcEmapRouteFlagIcon2;
var ZdcEmapRouteFlagStartMarker1;
var ZdcEmapRouteFlagStartMarker2;
//将来フォームで条件を変えられる用に変数化しておく
var ZdcEmapRouteType              = <?PHP echo $D_ROUTE_TYPE; ?>;
var ZdcEmapRouteWalkPSC           = <?PHP echo $D_ROUTE_WALK_PSC; ?>;
var ZdcEmapRouteWalkFloorFlg      = <?PHP echo $D_ROUTE_WALK_FLOORFLG; ?>;
var ZdcEmapRouteWalkDepFloor      = <?PHP echo $D_ROUTE_WALK_DEP_FLOOR; ?>;
var ZdcEmapRouteWalkDepStationFlg = <?PHP echo $D_ROUTE_WALK_DEP_STATIONFLG; ?>;
var ZdcEmapRouteWalkArrFloorFlg   = <?PHP echo $D_ROUTE_WALK_ARR_FLOORFLG; ?>;
var ZdcEmapRouteWalkArrStationFlg = <?PHP echo $D_ROUTE_WALK_ARR_STATIONFLG; ?>;
var ZdcEmapRouteWalkArrFloor      = <?PHP echo $D_ROUTE_WALK_ARR_FLOOR; ?>;
//検索入り口
function ZdcEmapRouteSearch(name1,mx1,my1,name2,mx2,my2) {
	<?php if (!isset($D_ROUTE_FIX_MODE) || !$D_ROUTE_FIX_MODE) {	// add 2011/11/25 Y.Matsukawa ?>
	if(ZdcEmapButtonNG()) return;
	<?php } ?>
	if(ZdcEmapRouteType == 0) return;
	ZdcEmapPoiRouteClear();
	
	//パラメーターの設定
	ZdcEmapRouteName1 = name1;
	ZdcEmapRouteName2 = name2;
	ZdcEmapRoutePoint1 = new ZdcPoint(mx1, my1, <?PHP echo $D_PFLG; ?>);
	ZdcEmapRoutePoint2 = new ZdcPoint(mx2, my2, <?PHP echo $D_PFLG; ?>);
	
	if(ZdcEmapRouteType == 1 || ZdcEmapRouteType == 3)
		ZdcEmapRouteSearchWalk(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);
	if(ZdcEmapRouteType == 2)
		ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);

	//画面の移動
	ZdcEmapMapMoveBox(my1,mx1,my2,mx2);
}
//歩行者検索
function ZdcEmapRouteSearchWalk(name1,p1,name2,p2) {
	ZdcEmapReadOn();
	//オブジェクト作成
	ZdcEmapRouteOptionsObj = new ZdcPRouteSearchOptions();
	ZdcEmapRouteSearchObj = new ZdcPRouteSearch();
	ZdcEmapRouteOptionsObj.showMarker = false;
	ZdcEmapRouteOptionsObj.pointFlg = <?PHP echo $D_PFLG; ?>;
	ZdcEmapRouteSearchObj.timeout = <?PHP echo $D_ROUTE_TIMEOUT; ?>;
	ZdcEvent.addListener(ZdcEmapRouteSearchObj, 'end', ZdcEmapRouteSearchEndWalk);
	ZdcEmapMapObj.addPRouteSearch(ZdcEmapRouteSearchObj);
	
	//デザイン指定
	ZdcEmapRouteSearchObj.routeWidth = <?PHP echo $D_ROUTE_WALK_WIDTH; ?>;
	ZdcEmapRouteSearchObj.routeOpacity = "<?PHP echo $D_ROUTE_WALK_OPACITY; ?>";
	ZdcEmapRouteSearchObj.routeColor = "<?PHP echo $D_ROUTE_WALK_COLOR; ?>";
	
	//位置指定
	ZdcEmapRouteOptionsObj.arrivalPoint.point = p1;
	ZdcEmapRouteOptionsObj.departurePoint.point = p2;
	
	//検索条件指定
	//共通
	ZdcEmapRouteOptionsObj.psc = ZdcEmapRouteWalkPSC;
	ZdcEmapRouteOptionsObj.floorFlg = ZdcEmapRouteWalkFloorFlg;
	//到着点(出発点)
	ZdcEmapRouteOptionsObj.arrivalPoint.name = name1;
	ZdcEmapRouteOptionsObj.arrivalPoint.floorFlg = ZdcEmapRouteWalkArrFloorFlg;
	ZdcEmapRouteOptionsObj.arrivalPoint.stationFlg = ZdcEmapRouteWalkArrStationFlg;
	ZdcEmapRouteOptionsObj.arrivalPoint.floor = ZdcEmapRouteWalkArrFloor;
	//出発点(拠点)
	ZdcEmapRouteOptionsObj.departurePoint.name = name2;
	ZdcEmapRouteOptionsObj.departurePoint.stationFlg = ZdcEmapRouteWalkDepStationFlg;
	ZdcEmapRouteOptionsObj.departurePoint.floor = ZdcEmapRouteWalkDepFloor;
	//検索開始
	ZdcEmapRouteSearchObj.search(ZdcEmapRouteOptionsObj);
}
function ZdcEmapRouteSearchEndWalk() {
	ZdcEmapReadOff();
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	ZdcEmapShopMsgClose();
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		//エラー処理
		if(ZdcEmapRouteType == 1) {
			//失敗だった場合自動車で再検索する
			ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);
		} else {
			<?php // add 2011/11/25 Y.Matsukawa [ ?>
			<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
			ZdcEmapRouteFlag();
			<?php } ?>
			<?php // add 2011/11/25 Y.Matsukawa ] ?>
			alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + result.status + ']');
		}
		return;
	}
	//スタート／ゴールのアイコンを描画
	ZdcEmapRouteFlag();
	//ルート距離表示		add 2010/07/23 Y.Matsukawa
	var ZdcEmapRouteDistance = document.getElementById("ZdcEmapRouteDistance");
	if (ZdcEmapRouteDistance) {
		distance = result.distance;
		if (distance < 1000) {
			distance = distance+' m';
		} else {
			distance = distance / 100;
			distance = Math.round(distance);
			distance = distance / 10;
			distance += ' km';
		}
		ZdcEmapRouteDistance.innerHTML = distance;
	}
	<?php //ルート完了時動作		add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapRouteSearchEndAction(result, "Walk");
}
//自動車検索
function ZdcEmapRouteSearchCar(name1,p1,name2,p2) {
	ZdcEmapReadOn();
	//オブジェクト作成
	ZdcEmapRouteOptionsObj = new ZdcRouteSearchOptions();
	ZdcEmapRouteSearchObj = new ZdcRouteSearch();
	ZdcEmapRouteOptionsObj.showMarker = false;
	ZdcEmapRouteOptionsObj.pointFlg = <?PHP echo $D_PFLG; ?>;
	ZdcEmapRouteSearchObj.timeout = <?PHP echo $D_ROUTE_TIMEOUT; ?>;
	ZdcEvent.addListener(ZdcEmapRouteSearchObj, 'end', ZdcEmapRouteSearchEndCar);
	ZdcEmapMapObj.addRouteSearch(ZdcEmapRouteSearchObj);
	
	//デザイン指定
	ZdcEmapRouteSearchObj.routeWidth = <?PHP echo $D_ROUTE_CAR_WIDTH; ?>;
	ZdcEmapRouteSearchObj.routeOpacity = "<?PHP echo $D_ROUTE_CAR_OPACITY; ?>";
	ZdcEmapRouteSearchObj.routeColor = "<?PHP echo $D_ROUTE_CAR_COLOR; ?>";
	
	//位置指定
	ZdcEmapRouteOptionsObj.arrivalPoint = p1;
	ZdcEmapRouteOptionsObj.departurePoint = p2;

	//検索開始
	ZdcEmapRouteSearchObj.search(ZdcEmapRouteOptionsObj);
}
function ZdcEmapRouteSearchEndCar() {
	ZdcEmapReadOff();
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	ZdcEmapShopMsgClose();
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		<?php // add 2011/11/25 Y.Matsukawa [ ?>
		<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
		ZdcEmapRouteFlag();
		<?php } ?>
		<?php // add 2011/11/25 Y.Matsukawa ] ?>
		//エラー処理
		alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + result.status + ']');
		return;
	}
	//スタート／ゴールのアイコンを描画
	ZdcEmapRouteFlag();
	//ルート距離表示		add 2010/07/23 Y.Matsukawa
	var ZdcEmapRouteDistance = document.getElementById("ZdcEmapRouteDistance");
	if (ZdcEmapRouteDistance) {
		distance = result.distance;
		if (distance < 1000) {
			distance = distance+' m';
		} else {
			distance = distance / 100;
			distance = Math.round(distance);
			distance = distance / 10;
			distance += ' km';
		}
		ZdcEmapRouteDistance.innerHTML = distance;
	}
	<?php //ルート完了時動作		add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapRouteSearchEndAction(result, "Car");
}
<?php //ルート完了時動作		add 2011/11/25 Y.Matsukawa ?>
function ZdcEmapRouteSearchEndAction(result, routeType) {
	var ele,wgs,dms,time=0,hh=0,mi=0;
	<?php //ルート情報を表示 ?>
	var time=0;
	if (routeType == "Walk") {
		mi = parseInt(result.distance / 4000 * 60);//分
		hh = parseInt(mi/60);//時間
		mi = (mi - hh*60);
	} else {
		var cnt = result.getLinkCount(0);
		var link = new Array();
		for(i=0; i < cnt; i++) {
			var rlink = result.getLink(i, 0);
			if(rlink.roadType == 0 || rlink.roadType == 1) {
				// 高速
				time += rlink.distance / (80*1000);
			} else {
				// 一般
				time += rlink.distance / (40*1000);
			}
		}
		if (time > 0) {
			mi = parseInt(time*10000/166);//分
			hh = parseInt(mi/60);//時間
			mi = (mi - hh*60);
		}
	}
	ele = document.getElementById("ZdcEmapRouteTimeH");
	if (ele) ele.innerHTML = hh;
	if (hh < 10) hh = "0"+hh;
	ele = document.getElementById("ZdcEmapRouteTimeHH");
	if (ele) ele.innerHTML = hh;
	ele = document.getElementById("ZdcEmapRouteTimeN");
	if (ele) ele.innerHTML = mi;
	if (mi < 10) mi = "0"+mi;
	ele = document.getElementById("ZdcEmapRouteTimeNN");
	if (ele) ele.innerHTML = mi;
}
//ルート削除
function ZdcEmapPoiRouteClear() {
	if(!ZdcEmapRouteSearchObj) return;
	if(ZdcEmapRouteOptionsObj.departurePoint.point) {
		try{
			ZdcEmapMapObj.ClearPRouteLayer();//1.5まで
		} catch(e) {
			ZdcEmapRouteSearchObj.clearRoute();//1.6以降
		}
	} else {
		ZdcEmapMapObj.removeRouteSearch();
	}
	delete ZdcEmapRouteOptionsObj;
	delete ZdcEmapRouteSearchObj;
	//スタート／ゴールのレイヤーを削除
	if(ZdcEmapRouteFlagLayer) ZdcEmapRouteFlagLayer.clearMarker();
	ZdcEmapMapObj.removeUserLayer(ZdcEmapRouteFlagLayer);
	delete ZdcEmapRouteFlagIcon1;
	delete ZdcEmapRouteFlagIcon2;
}
//ルート開始／終了地点のアイコンを描画
function ZdcEmapRouteFlag() {
	//ユーザレイヤー作成
	ZdcEmapRouteFlagLayer = new ZdcUserLayer();
	ZdcEmapRouteFlagLayer.setLayerScale(1, 18);
	ZdcEmapRouteFlagLayer.setLayerType('manual');
	//アイコン作成
	ZdcEmapRouteFlagIcon1 = new ZdcIcon();
	ZdcEmapRouteFlagIcon1.offset = new ZdcPixel(<?PHP echo $D_ROUTE_GOAL_OFFSET_X; ?>, <?PHP echo $D_ROUTE_GOAL_OFFSET_Y; ?>);
	ZdcEmapRouteFlagIcon1.image = '<?PHP echo $D_ROUTE_GOAL_IMAGE; ?>';
	ZdcEmapRouteFlagIcon2 = new ZdcIcon();
	ZdcEmapRouteFlagIcon2.offset = new ZdcPixel(<?PHP echo $D_ROUTE_START_OFFSET_X; ?>, <?PHP echo $D_ROUTE_START_OFFSET_Y; ?>);
	ZdcEmapRouteFlagIcon2.image = '<?PHP echo $D_ROUTE_START_IMAGE; ?>';
	//ユーザレイヤーに追加
	if(ZdcEmapRoutePoint1) ZdcEmapRouteFlagLayer.addMarker(new ZdcMarker(ZdcEmapRoutePoint1, ZdcEmapRouteFlagIcon1));
	if(ZdcEmapRoutePoint2) ZdcEmapRouteFlagLayer.addMarker(new ZdcMarker(ZdcEmapRoutePoint2, ZdcEmapRouteFlagIcon2));
	//地図にユーザレイヤーを追加
	ZdcEmapMapObj.addUserLayer(ZdcEmapRouteFlagLayer);
	//ルートレイヤーの上に移動
	ZdcEmapRouteFlagLayer.doc.style.zIndex = "3999";
}

// add 2011/11/25 Y.Matsukawa
//-------------------------------------------------------------
//ルート探索モード
//-------------------------------------------------------------
function ZdcEmapFixRouteSearch(shopItem) {
	ZdcEmapRouteShopItem = shopItem;
	<?php //目的地店舗の情報を表示 ?>
	if (ZdcEmapRouteShopItem) {
		for(prop in ZdcEmapRouteShopItem){
			ele = document.getElementById("ZdcEmapRouteShop_"+prop);
			if (ele) ele.innerHTML = eval("ZdcEmapRouteShopItem."+prop);
		}
	}
	ZdcEmapRouteSearch('<?PHP echo $D_USER_DEFNAME; ?>', ZdcEmapRouteShopItem.lon, ZdcEmapRouteShopItem.lat,
						'地図中心', ZdcEmapRouteStartLon, ZdcEmapRouteStartLat);
}
function ZdcEmapFixRouteSelectShop(id) {
	var shopItem = null;
	if (ZdcEmapRouteShopItems) {
		for(i=0; i<ZdcEmapRouteShopItems.length; i++) {
			if (ZdcEmapRouteShopItems[i].id == id) {
				shopItem = ZdcEmapRouteShopItems[i];
				break;
			}
		}
		if (shopItem) ZdcEmapFixRouteSearch(shopItem);
	}
}



//-------------------------------------------------------------
//自動検索のイベント管理
//-------------------------------------------------------------
var ZdcEmapSearchEventFlg  = 0;
var ZdcEmapSearchEventFunc = null;
var ZdcEmapSearchEventDragmapend;
var ZdcEmapSearchEventScrollmapend;
var ZdcEmapSearchEventChangezoomend;
//検索実行
function ZdcEmapSearchEventAction() {
	if(!ZdcEmapSearchEventFlg) return;
	// 2011/06/15 K.Masuda mod [
	//if(ZdcEmapMapObj.getUserMsgOpenStatus()) return;//フキダシ表示中は検索しない
	if( <?php if(isset($D_HUKIDASHI_SEARCH)){echo "false";}else{echo "true";} ?> ){
		if(ZdcEmapMapObj.getUserMsgOpenStatus()) return;//フキダシ表示中は検索しない
	}
	// 2011/06/15 K.Masuda mod ]
<?php	// add 2016/11/15 K.Tani [
		// 地図操作時に再検索しないモード
		if ($D_SHOP_NO_SEARCH_USER_ACT) { ?>
	return;
<?php	}
		// add 2016/11/15 K.Tani ] ?>
	
	
	eval(ZdcEmapSearchEventFunc);
}
//検索イベント追加
function ZdcEmapSearchEventAdd(func) {
	ZdcEmapSearchEventDel();
	ZdcEmapSearchEventFunc = func;
	ZdcEmapSearchEventDragmapend    = ZdcEvent.addListener(ZdcEmapMapObj, "dragmapend"   , ZdcEmapSearchEventAction);
	ZdcEmapSearchEventScrollmapend  = ZdcEvent.addListener(ZdcEmapMapObj, "scrollmapend" , ZdcEmapSearchEventAction);
	ZdcEmapSearchEventChangezoomend = ZdcEvent.addListener(ZdcEmapMapObj, "changezoomend", ZdcEmapSearchEventAction);
}
//検索イベント削除
function ZdcEmapSearchEventDel() {
	ZdcEmapSearchEventStop();
	if(ZdcEmapSearchEventDragmapend)    ZdcEvent.removeListener(ZdcEmapSearchEventDragmapend);
	if(ZdcEmapSearchEventScrollmapend)  ZdcEvent.removeListener(ZdcEmapSearchEventScrollmapend);
	if(ZdcEmapSearchEventChangezoomend) ZdcEvent.removeListener(ZdcEmapSearchEventChangezoomend);
	
	ZdcEmapSearchEventDragmapend = null;
	ZdcEmapSearchEventScrollmapend = null;
	ZdcEmapSearchEventChangezoomend = null;
	delete ZdcEmapSearchEventFunc;
}
//検索イベント開始
function ZdcEmapSearchEventStart() {
	ZdcEmapSearchEventFlg = 1;
}
//検索イベント停止
function ZdcEmapSearchEventStop() {
	ZdcEmapSearchEventFlg = 0;
}



//-------------------------------------------------------------
//吹き出し
//  Shapeレイヤーがあるとクリック等が効かないためややこしい処理をしている
//  もっと簡単に実装できるようになったら作り直すこと
//-------------------------------------------------------------
var ZdcEmapTipsInterval = 5000;//簡易噴出し表示間隔
var ZdcEmapTipsTimerID = null;//強制的に噴出しを消すタイマーID
var ZdcEmapTipsMarker = null;//噴出し表示のマーカーオブジェクト
var ZdcEmapTipsShapeLayer = null;//噴出しレイヤー
var ZdcEmapTipsShape = null;//簡易噴出しシェープオブジェクト
var ZdcEmapTipsTopMarker = null;//最上位表示用一時マーカーレイヤー
var ZdcEmapTipsTopMarkerLayer = null;//最上位表示用一時マーカーオブジェクト
//施設データの簡易噴出し表示メソッド
function ZdcEmapTipsClick(id) {
	ZdcEmapTipsHideInfoInterval();
	//動作判定
	if(id == null) id = this.id;
	var s = ZdcEmapMapObj.getMapScale();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//オブジェクトの作成
	ZdcEmapTipsMarker = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapPoiMrkId[id]);
	if(!ZdcEmapMapObj || !ZdcEmapTipsMarker) return;
	if(!ZdcEmapTipsShape) ZdcEmapTipsShape = new ZdcShape.Text();
	if(!ZdcEmapTipsShapeLayer) ZdcEmapTipsShapeLayer = new ZdcShape.Layer();
	ZdcEmapMapObj.addShapeLayer(ZdcEmapTipsShapeLayer);
	ZdcEmapTipsShapeLayer.setZIndex(4010);
	//テキストの設定
	ZdcEmapTipsShape.textString = ZdcEmapTipsMarker.data1;
	ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	ZdcEmapTipsShape.font = "<?PHP echo $D_TIPS_FONT; ?>";
	ZdcEmapTipsShape.borderWidth = <?PHP echo $D_TIPS_BORDERWIDTH; ?>;
	ZdcEmapTipsShape.bgColor = "<?PHP echo $D_TIPS_BGCOLOR; ?>";
	ZdcEmapTipsShape.shadowFlg = <?PHP echo $D_TIPS_SHADOWFLG; ?>;
	ZdcEmapTipsShape.shadowX = <?PHP echo $D_TIPS_SHADOWX; ?>;
	ZdcEmapTipsShape.shadowY = <?PHP echo $D_TIPS_SHADOWY; ?>;
	ZdcEmapTipsShape.opacity = <?PHP echo $D_TIPS_OPACITY; ?>;
	//表示位置の調整
	var box = ZdcEmapMapObj.getMapBoundBox();
	var point = new ZdcPoint(ZdcEmapTipsMarker.Point.mx, ZdcEmapTipsMarker.Point.my, <?PHP echo $D_PFLG; ?>);
	var x,y,v,h;
	if(Math.abs(box.minx - point.mx) < Math.abs(box.maxx - point.mx)){ 
		h = "left"; 
		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	}else{
		h = "right";
		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X*-1; ?>;
	}
	if(Math.abs(box.miny - point.my) < Math.abs(box.maxy - point.my)){
		v = "bottom";
		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y*-1; ?>;
	}else{
		v = "top";
		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	}
	ZdcEmapTipsShape.anchor = h + "-" + v;
	ZdcEmapTipsShape.setPoint(point);
	ZdcEmapTipsShapeLayer.addShape(ZdcEmapTipsShape);
	//描画中心が地図範囲外の場合移動する
	if(ZdcEmapTipsMarker.Point.mx < box.minx || ZdcEmapTipsMarker.Point.my < box.miny || ZdcEmapTipsMarker.Point.mx > box.maxx || ZdcEmapTipsMarker.Point.my > box.maxy)
		ZdcEmapMapObj.setMapLocation(ZdcEmapTipsMarker.Point);
	//描画
	if(!ZdcEmapTipsTopMarkerLayer) ZdcEmapTipsTopMarkerLayer = new ZdcUserLayer();//最上位マーカーレイヤー
	if(!ZdcEmapTipsTopMarker) ZdcEmapTipsTopMarker = new ZdcMarker(new ZdcPoint(ZdcEmapTipsMarker.getPoint().lon ,ZdcEmapTipsMarker.getPoint().lat), ZdcEmapTipsMarker.getIcon());
	ZdcEmapTipsTopMarkerLayer.addMarker(ZdcEmapTipsTopMarker);
	ZdcEmapMapObj.addUserLayer(ZdcEmapTipsTopMarkerLayer);
	ZdcEmapTipsTopMarkerLayer.doc.style.zIndex = 4011;
	ZdcEmapTipsTopMarker.mouseclickmarker = ZdcEmapTipsMarker.mouseclickmarker;
	//イベントの設定
	if(ZdcEmapTipsTopMarker.mouseclickmarker) ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseclickmarker", ZdcEmapTipsTopMarker.mouseclickmarker);
	ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseoutmarker", ZdcEmapTipsHideInfo);
	ZdcEmapTipsTimerID = setTimeout(ZdcEmapTipsHideInfoInterval, ZdcEmapTipsInterval);
}
//レイヤーを閉じる
function ZdcEmapTipsClose() {
	//シェイプレイヤーを閉じる
	if(ZdcEmapTipsShapeLayer)
	{
		ZdcEmapTipsShapeLayer.clearShape();
		ZdcEmapMapObj.removeShapeLayer(ZdcEmapTipsShapeLayer);
	}
	ZdcEmapTipsShapeLayer = null;
	ZdcEmapTipsShape = null;
	//最上位マーカーレイヤーを閉じる
	if(ZdcEmapTipsTopMarkerLayer)
	{
		ZdcEmapTipsTopMarkerLayer.clearMarker();
		ZdcEmapMapObj.removeUserLayer(ZdcEmapTipsTopMarkerLayer);
		ZdcEmapTipsTopMarker.mouseclickmarker = null;
	}
	ZdcEmapTipsTopMarker = null;
	ZdcEmapTipsTopMarkerLayer = null;
	//タイマーのクリア
	if(ZdcEmapTipsTimerID) clearTimeout(ZdcEmapTipsTimerID);
	ZdcEmapTipsTimerID = null;
}
//強制的に簡易噴出し非表示メソッド
function ZdcEmapTipsHideInfoInterval() {
	if(ZdcEmapTipsTimerID) clearTimeout(ZdcEmapTipsTimerID);
	ZdcEmapTipsTimerID = null;
	ZdcEmapTipsClose();
}
//簡易噴出し非表示メソッド
function ZdcEmapTipsHideInfo() {
	if(!ZdcEmapTipsIsMouseOutMarker()) return;
	ZdcEmapTipsClose();
}
//IEでmouseoutイベントがマーカーオブジェクトの子ノードの間で発生しているかどうか
function ZdcEmapTipsIsMouseOutMarker() {
	if(!document.all) return true;
	if(!ZdcEmapTipsTopMarker) return true;
	if(!window.event || window.event.type != "mouseout") return false;
	var tmp = window.event.toElement;
	while(tmp) {
		if(tmp == ZdcEmapTipsTopMarker.doc) return false;
		tmp = tmp.parentElement;
	}
	return true;
}



//-------------------------------------------------------------
//その他
//-------------------------------------------------------------
//HTML読み込み用ajax通信関数
//function ZdcEmapHttpRequestHtml(url,func) {		mod 2009/02/16 Y.Matsukawa
function ZdcEmapHttpRequestHtml(url,func,nowaitmsg) {
	//ZdcEmapReadOn();//読み込み中フラグon		mod 2009/02/16 Y.Matsukawa
	if(!nowaitmsg) ZdcEmapReadOn();//読み込み中フラグon
	//通信処理
	var ZdcEmapHttpRequestObj = new ZdcEmapHttpRequest('EUC', 'EUC');
	ZdcEmapHttpRequestObj.request(url, function(html,status) {
		if(status == 3) status = 0;//タイムアウトは無視 連続呼び出し時の動作が安定しないので
		if(status == 9) status = 0;//テンプレートが無い場合に対応
		if(html == null) html = "";//nullは出さない
		if(status == 0) {
			func(html,status);
		} else {
			//エラー処理
			func(html,status);
		}
		ZdcEmapReadOff();//読み込み中フラグoff
	},<?PHP echo $D_AJAX_TIMEOUT; ?>);
}
//ボタン押下拒否判定
function ZdcEmapButtonNG() {
	if(ZdcEmapReadCheck()) return 1;//読み込み中の動作がある
	if(ZdcEmapSearchWindowObj.innerHTML != "") return 1;//検索ウィンドウが開いている

	return 0;
}
//読み込み中フラグ
var ZdcEmapReading = 0;//読み込み中・処理中フラグ
function ZdcEmapReadOn() {
	ZdcEmapReading ++;
	if(ZdcEmapReading == 1) ZdcEmapMapObj.visibleZdcWait();
}
function ZdcEmapReadOff() {
	if(ZdcEmapReading <= 0) return;
	ZdcEmapReading --;
	if(ZdcEmapReading == 0) ZdcEmapMapObj.hiddenZdcWait();
}
function ZdcEmapReadCheck() {
	if(ZdcEmapReading > 0) return 1;//読み込み中の動作がある
	return 0;
}
//指定された駅・施設アイコンを前面にもってくる
function ZdcEmapMapFrontPoi(id){
	if(ZdcEmapMapPoiMrkId[id] != null) {
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapPoiMrkId[id]);
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[id]);
		ZdcEmapMapPoiMrkId[id] = ZdcEmapMapUserLyr.addMarker(mrk);
		//イベント当てなおし
		if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
		if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
		if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
	}
}

// アイコンを前面に移動（APIv1.10で実装予定の機能を先行して実装）		add 2009/10/14 Y.Matsukawa
//v110 add -- set top zindex for marker
ZdcMarker.prototype.setTopZIndex=function(idx){
//	if (this.parentLayer.addmapstatus){
//		for (var i=0; i<this.parentLayer.markers.length; i++){
//			if (this.parentLayer.markers[i]!=null){
//				this.parentLayer.markers[i].doc.style.zIndex = 3;
//			}
//		}
//	}
	if (idx) {
		this.doc.style.zIndex = idx;
	} else {
		this.doc.style.zIndex = 4;
	}
}
//v110 add -- set defalut zindex for marker
ZdcMarker.prototype.setDefaultZIndex=function(){
	//this.doc.style.zIndex = 0;
	this.doc.style.zIndex = 3;
}

<?php // マッチング結果住所文字列をJS変数にセット		add 2011/11/25 Y.Matsukawa ?>
var ZdcEmapAddrMatchString = null;
function ZdcEmapSetAddrMatchString(addr) {
	ZdcEmapAddrMatchString = addr;
}

<?php // 最初の中心点に戻るリンク		add 2012/05/28 K.Masuda ?>
function ZdcEmaprestoreCenter(){
	ZdcEmapMapObj.restoreMapLocation();
}

// add 2015/04/22 H.Yasunaga getElementByClassNameのIE下位互換用 [
function CompatiblegetElementsByClassName(targetClass){
    var foundElements = new Array();
    if (document.all){
        var allElements = document.all;
    }
    else {
       var allElements = document.getElementsByTagName("*");
    }
    for (i=0,j=0;i<allElements.length;i++) {
        if (allElements[i].className == targetClass) {
            foundElements[j] = allElements[i];
            j++;
        }
    }  
    return foundElements;
}
// add 2015/04/22 H.Yasunaga]