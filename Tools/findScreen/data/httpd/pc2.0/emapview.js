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
// 2011/07/07 H.Osamoto		マツキヨ用API2.0対応版
// 2011/10/03 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/10/06 H.Osamoto		ダブルクリックした地点へ移動するイベント追加
// 2012/03/16 H.Osamoto		【不具合修正】ルート探索スクリプトエラー修正
// ------------------------------------------------------------
include("./inc/define.inc");  // 基本設定
include("./inc/define_get_icon.inc");  // アイコン情報取得
?>
<?php /* 非表示開始 ?>
//-------------------------------------------------------------
//JSAPIの動作確認
//-------------------------------------------------------------
// del 2011/07/07 H.osamoto [
//	if(parseInt(ZDC_RC) != 0) {
//		//location.href = '<?PHP echo $D_URL_JSAPIERROR; ?>';
//	}
// del 2011/07/07 H.osamoto ]
<?php 非表示終了 */ ?>

//-------------------------------------------------------------
//初期設定
//-------------------------------------------------------------
//地図
var ZdcEmapMapObj = null;
var ZdcEmapMapUsrctl = null;
var ZdcEmapMapZoomctl = null;
//	var ZdcEmapMapSize = new ZdcWindow();	// del 2011/07/07 H.osamoto
//ユーザーレイヤー
//	var ZdcEmapMapUserLyr = new ZdcUserLayer();	// del 2011/07/07 H.osamoto
var ZdcEmapMapUserLyrId = null;
//マーカー記憶
var ZdcEmapMapShopMrkId = new Array(<?PHP echo $D_SHOP_MAX; ?>);
var ZdcEmapMapShopMrkCnt = null;
var ZdcEmapMapPoiMrkId = new Array(<?PHP echo $D_POI_MAX; ?>);
var ZdcEmapMapPoiMrkCnt = null;
var ZdcEmapMapShopDetailMrkId = null;
var ZdcEmapMapCurFocusMrkId = null;
//吹き出し
//	var ZdcEmapMsg = new ZdcUserMsgWindow();	// del 2011/07/07 H.osamoto
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
//アイコン情報
var ZdcEmapIconImg = new Array();
var ZdcEmapIconW = new Array();
var ZdcEmapIconH = new Array();
var ZdcEmapIconOffsetX = new Array();
var ZdcEmapIconOffsetY = new Array();
// 地図緯度経度 add 2011/07/07 H.osamoto
var mappoint;
<?PHP
foreach( $D_ICON as $key=>$val) {
	printf("ZdcEmapIconImg['%s'] = '%s';",$key,$val["IMG"]);
	printf("ZdcEmapIconW['%s'] = %d;",$key,$val["W"]);
	printf("ZdcEmapIconH['%s'] = %d;",$key,$val["H"]);
	printf("ZdcEmapIconOffsetX['%s'] = %d;",$key,ceil($val["W"]/2)*-1);
	printf("ZdcEmapIconOffsetY['%s'] = %d;",$key,ceil($val["H"]/2)*-1);
}
?>
// add 2011/07/07 H.Osamoto [
var Zdc_smap_g_oMap     = null;
var Zdc_smap_g_oAjax    = null;
// add 2011/07/07 H.Osamoto ]

//その他
<?php /* 非表示開始 ?>
// del 2011/07/07 H.osamoto [
//	<?php //if($D_REQ_JSAPI["zdcmapgeometric"]){ ?>	// 2008/10/22 Y.Matsukawa add
//	var ZdcEmapGeometricObj = new ZdcGeometric();
//	<?php //} ?>
// del 2011/07/07 H.osamoto ]
<?php 非表示終了 */ ?>
var ZdcEmapSaveCond = new Array(<?PHP echo $D_SHOP_MAX; ?>);//絞込条件
<?PHP //for($i = 0;$i < 50;$i ++) if($_VARS["cond".$i]) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]);		mod 2009/11/07 Y.Matsukawa ?>
<?PHP for($i = 1;$i <= 200;$i ++) if(isset($_VARS["cond".$i]) && $_VARS["cond".$i]) printf("ZdcEmapSaveCond[%d] = '%s';",$i,$_VARS["cond".$i]); // mod 2011/10/03 Y.Nakajima ?>

// add 2011/05/26 K.Masuda [
var QSTRING = location.search.replace(/^\?/, '');
// add 2011/05/26 K.Masuda ]

//初期化関数
<?php /* 非表示開始 ?>
//function ZdcEmapInit(){	2007/11/16 mod Y.Matsukawa
//function ZdcEmapInit(init_lat, init_lon){		2007/11/30 mod Y.Matsukawa
<?php 非表示終了 */ ?>
function ZdcEmapInit(init_lat, init_lon, init_lv){
	//地図の基本設定 ----------------------------------------
	var svrurl = "<?PHP if (isset($D_JS_SVRURL)) echo $D_JS_SVRURL;  // mod 2011/10/03 Y.Nakajima ?>";
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
	init_lv = init_lv - 1; // add 2011/07/07 H.Osamoto
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapMapObj = new ZdcMap(document.getElementById("ZdcEmapMap"), 
	//								new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>),
	//								init_lv,
	//								<?PHP echo $D_MAP_LAYER_KBN; ?>);
<?php 非表示終了 */ ?>
	ZdcEmapMapObj = new ZDC.Map(
						document.getElementById('ZdcEmapMap'),
						{
							latlon : new ZDC.LatLon(init_lat, init_lon),
							zoom : init_lv,
							mapType: ZDC.MAPTYPE_COLOR
						}
					);
	// add 2011/10/06 H.osamoto [
	/* 地図をダブルクリックしたときのイベント */
	ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_DBLCLICK, moveDblClickLatLon);
	// add 2011/10/06 H.osamoto ]
	
	// mod 2011/07/07 H.osamoto ]
<?php // add 2011/02/10 Y.Matsukawa ] ?>
<?php /* 非表示開始 ?>
	// del 2011/07/07 H.osamoto [
	//	ZdcEmapMapSize = ZdcEmapMapObj.getMapWindowSize();
	//	
	//		//地図中心マーク ---------------------------------	add 2009/05/28 Y.Matsukawa
	//		<?php if ($D_MAPCENTER_MARK) { ?>
	//		ZdcEmapMapObj.addMapCenter(new ZdcMapCenter('<?php echo $D_MAPCENTER_MARK; ?>'));
	//		<?php } ?>
	//		//ユーザーコントロール ---------------------------------
	//		<?PHP echo //$D_JSCODE_MAPUSRCTL; ?>	del 2011/07/07 H.Osamoto
	//		<?PHP echo //$D_JSCODE_MAPZOOMCTL; ?>	del 2011/07/07 H.Osamoto
	//		
	//		//その他地図関係 ---------------------------------------
	//		ZdcEmapMapObj.setMouseCursor("hand");	// 2008/04/01 add Y.Matsukawa
	//		ZdcEmapMapObj.CenterFirst = false;
	//		ZdcEmapMapObj.setScreenMode();
	//		//ZdcEmapMapObj.setMapType(<?PHP echo $D_MAP_LAYER_KBN; ?>);		del 2011/02/10 Y.Matsukawa
	//		ZdcEmapMapObj.reflashMap();
	//		if(<?PHP echo $D_MAP_SCALE_MAX; ?> > -1 && <?PHP echo $D_MAP_SCALE_MIN; ?> > -1)
	//			ZdcEmapMapObj.setMapZoomLimit(<?PHP echo $D_MAP_SCALE_MAX; ?>,<?PHP echo $D_MAP_SCALE_MIN; ?>);
	//		//標準コントロール
	//		if(ZdcEmapMapUsrctl == null && ZdcEmapMapZoomctl == null && <?PHP echo $D_MAP_CONTROL; ?> > 0)
	//			ZdcEmapMapObj.addMapControl(new ZdcControl(<?PHP echo $D_MAP_CONTROL; ?>));
	//		//if (ZdcEmapMapZoomctl) ZdcEmapMapZoomctl.setSlitherPosition();		// add 2011/02/17 Y.Matsukawa	del 2011/02/22 Y.Matsukawa
	//		//標準スケールバー
	//		if(<?PHP echo $D_MAP_SCALEBAR; ?> > 0) ZdcEmapMapObj.addMapScaleBar(new ZdcScaleBar(<?PHP echo $D_MAP_SCALEBAR; ?>));
	//		//標準中心アイコン
	//		if(<?PHP echo $D_MAP_CENTER; ?> > 0) {
	//			var obj = new ZdcMapCenter(<?PHP echo $D_MAP_CENTER; ?>);
	//			obj.doc.zIndex=2999;//アイコンを背面にもっていく
	//			ZdcEmapMapObj.addMapCenter(obj);
	//		}
	//		//情報ボックス
	//		if(<?PHP echo $D_MAP_INFO; ?> > 0) ZdcEmapMapObj.addMapCenterInfoBox(new ZdcMapCenterInfoBox(<?PHP echo $D_MAP_INFO; ?>));
	//
	//		<?php // add 2010/08/09 Y.Matsukawa [ ?>
	//		<?php if($D_MAP_REMOVE_CONTROL) { ?>
	//		//コントロール消去
	//		ZdcEmapMapObj.removeUserControl();
	//		ZdcEmapMapObj.removeMapControl();
	//		<?php } ?>
	//		<?php if($D_MAP_REMOVE_ZOOMCONTROL) { ?>
	//		//ズームコントロール消去
	//		ZdcEmapMapObj.removeUserZoomControl();
	//		<?php } ?>
	//		<?php if($D_MAP_DRAG_OFF) { ?>
	//		//地図ドラッグ禁止
	//		ZdcEmapMapObj.dragOff();
	//		<?php } ?>
	//		<?php // add 2010/08/09 Y.Matsukawa ] ?>
	//
	//		//
	//		ZdcEmapMapObj.ZdcMapRasterEngine = false;
	//	<?php // del 2011/02/10 Y.Matsukawa [ ?>
	//		//	//初期位置
	//		//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(<?PHP echo $D_INIT_LON; ?>,<?PHP echo $D_INIT_LAT; ?>,<?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);		2007/11/16 mod Y.Matsukawa
	//		//	if (!init_lat || !init_lon) {
	//		//		init_lat = <?PHP echo $D_INIT_LAT; ?>;
	//		//		init_lon = <?PHP echo $D_INIT_LON; ?>;
	//		//	}
	//		//	// 2007/11/30 add Y.Matsukawa ↓
	//		//	//if (!init_lv) {		mod 2009/09/04 Y.Matsukawa
	//		//	if (!init_lv || init_lv == 0) {
	//		//		init_lv = <?PHP echo $D_INIT_LVL; ?>;
	//		//	}
	//		//	// 2007/11/30 add Y.Matsukawa ↑
	//		//	//ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), <?PHP echo $D_INIT_LVL; ?>);	2007/11/30 mod Y.Matsukawa
	//		//	ZdcEmapMapObj.setMapLocation(new ZdcPoint(init_lon, init_lat, <?PHP echo $D_PFLG; ?>), init_lv);
	//	<?php // del 2011/02/10 Y.Matsukawa ] ?>
	//		ZdcEmapMapObj.saveMapLocation();
	//		//クリック動作区分
	//		if(<?PHP echo $D_MAP_CLICK_KBN; ?> == 2) {
	//			<?PHP // ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnodrag", function(e) {	mod 2010/01/06 Y.Matsukawa ?>
	//			ZdcEvent.addListener(ZdcEmapMapObj, "clickmapnomove", function(e) {
	//				this.scrollToCenter(new ZdcPoint(this.MouseCLon,this.MouseCLat)); 
	//			});
	//		}
	//		//ホイールズーム区分
	//		if(<?PHP echo $D_MAP_WHEEL_KBN; ?> == 0) {
	//			ZdcEmapMapObj.setWheelOff();
	//		} else {
	//			ZdcEmapMapObj.setWheelOn();
	//		}
	// del 2011/07/07 H.osamoto ]
<?php 非表示終了 */ ?>

	// add 2011/07/07 H.Osamoto [
	// 地図上でのホイール操作を無効にする
	var ua = navigator.userAgent, we,
	map = document.getElementById('ZdcEmapMap'); //地図を表示するdiv要素
	if (ua.match(/Gecko/) && ua.match(/(Firebird|Firefox)/)) {
		we  = 'DOMMouseScroll';
	} else {
		we = 'mousewheel';
	}
	ZDC.clearListeners(map.firstChild, we);
	// add 2011/07/07 H.Osamoto ]
	
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

<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.osamoto [
	//		//その他 -----------------------------------------------
	//		//ユーザーレイヤー
	//		ZdcEmapMapUserLyr.setLayerScale(<?PHP echo $D_VIEW_ICON_MAX; ?>,<?PHP echo $D_VIEW_ICON_MIN; ?>);
	//		ZdcEmapMapUserLyr.setLayerType('manual');
	//		ZdcEmapMapUserLyr.clearMarker();
	//		ZdcEmapMapUserLyrId = ZdcEmapMapObj.addUserLayer(ZdcEmapMapUserLyr); 
	//		//画面遷移履歴初期化
	//		ZdcEmapHistoryClear();
	//		//処理中アイコン
	//		ZdcEmapMapObj.addZdcWait(parseInt(parseInt(ZdcEmapMapSize.height) / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETY; ?>),
	//								 parseInt(parseInt(ZdcEmapMapSize.width)  / 2) + (<?PHP echo $D_MAP_WAIT_OFFSETX; ?>),'<?PHP echo $D_MAP_WAIT_MSG; ?>');
<?php 非表示終了 */ ?>
	//その他 -----------------------------------------------
	//スケールバー
	widgetScaleBar = new ZDC.ScaleBar();
	ZdcEmapMapObj.addWidget(widgetScaleBar);
	//ユーザコントロール
	createUserControl();
	
	//画面遷移履歴初期化
	ZdcEmapHistoryClear();
	// mod 2011/07/07 H.osamoto ]
}

// add 2011/10/06 H.osamoto [
/* ダブルクリックした地点へ移動する */
function moveDblClickLatLon() {
	var latlon =  ZdcEmapMapObj.getClickLatLon();
	ZdcEmapMapObj.moveLatLon(latlon);
};
// add 2011/10/06 H.osamoto ]

// ユーザコントロール	add 2011/07/07 H.osamoto
function createUserControl() {
	/* ユーザコントロールに使用する画像 */
	var imgurldir = '<?PHP echo $D_DIR_BASE; ?>img/usrcontrol/';
	
	var control = {
		/* ホームポジションへ移動ボタン */
		home:
		{
			/* 画像のURL */
			src: imgurldir + 'home.png',
			/* 配置位置 */
			pos:{top: 28,right: 34},
			/* 画像の表示サイズ */
			imgSize:{width: 22,height: 22}
		},
		north:
		{
			src: imgurldir + 'north.png',
			pos: {top: 10,right: 38},
			imgSize: {width: 16,height: 17}
		},
		east:
		{
			src: imgurldir + 'east.png',
			pos: {top: 30,right: 18},
			imgSize: {width: 16,height: 17}
		},
		south:
		{
			src: imgurldir + 'south.png',
			pos: {top: 50,right: 38},
			imgSize: {width: 16,height: 17}
		},
		west:
		{
			src: imgurldir + 'west.png',
			pos: {top: 30,right: 58},
			imgSize: {width: 16,height: 17}
		},
		bar:
		{
			src: imgurldir + 'bar.png',
			pos: {top: 91,right: 38},
			imgSize: {width: 17,height: 110}
		},
		btn:
		{
			src: imgurldir + 'btn.png',
			pos: {top: 0,right: 1},
			imgSize: {width: 15,height: 10}
		},
		minus:
		{
			src: imgurldir + 'minus.png',
			pos: {top: 206,right: 38},
			imgSize: {width: 16,height: 17}
		},
		plus:
		{
			src: imgurldir + 'plus.png',
			pos: {top: 72,right: 38},
			imgSize: {width: 16,height: 17}
		}
	};
	
	var options = {
		/* つまみの上限位置(縮尺レベル変更バーのtop: -2pxの位置) */
		start: -2,
		/* つまみの移動量 */
		interval: 6
	};
	
	/* ユーザコントロールを作成 */
	widget = new ZDC.UserControl(control, options);
	
	/* ユーザコントロールを追加 */
	ZdcEmapMapObj.addWidget(widget);
};



//-------------------------------------------------------------
//地図制御
//-------------------------------------------------------------
//地図上にカーソル表示
var ZdcEmapMapCurMrkId = null;
function ZdcEmapMapCursorSet(lat, lon){
	//アイコンの作成
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.osamoto [
	//	var mrk = ZdcEmapMakeMrk(0,lat,lon,
	//							 ZdcEmapIconW['@SELB'],ZdcEmapIconH['@SELB'],0,0,
	//							 ZdcEmapIconOffsetX['@SELB'],ZdcEmapIconOffsetY['@SELB'],0,0,0,0,
	//							 ZdcEmapIconImg['@SELB'],'',
	//							 '','',0,null,null,null);
	//	if(ZdcEmapMapCurMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);
	//	ZdcEmapMapCurMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
<?php 非表示終了 */ ?>
	mrk = ZdcEmapMakeMrkApi2(0, lat, lon, 
							ZdcEmapIconW['@SELB'], ZdcEmapIconH['@SELB'],0,0,
							ZdcEmapIconOffsetX['@SELB'], ZdcEmapIconOffsetY['@SELB'],0,0,
							ZdcEmapIconImg['@SELB'], '',
							'', '', '', 0, null, null, null
						);
	if (ZdcEmapMapCurMrkId != null) ZdcEmapMapObj.removeWidget(ZdcEmapMapCurMrkId);
	ZdcEmapMapObj.addWidget(mrk);
	ZdcEmapMapCurMrkId = mrk;
	// mod 2011/07/07 H.osamoto ]
}
//地図上のカーソル外す
function ZdcEmapMapCursorRemove(){
	if (ZdcEmapMapCurMrkId != null) {
		//ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurMrkId);		mod 2011/07/07 H.Osamoto
		ZdcEmapMapObj.removeWidget(ZdcEmapMapCurMrkId);
		ZdcEmapMapCurMrkId = null;
	}
	//詳細表示中
	ZdcEmapMapFrontShopDetail();//詳細アイコンを前面にもってくる
<?php /* 非表示開始 ?>
	// del 2011/07/07 H.Osamoto [
	//	// 2011/06/15 K.Masuda mod [
	//	//ZdcEmapShopMsgClose();//吹き出しを消す
	//	if( <?php if($D_HUKIDASHI_SEARCH){echo "false";}else{echo "true";} ?> ){
	//		ZdcEmapShopMsgClose();//吹き出しを消す
	//	}
	//	// 2011/06/15 K.Masuda mod ]
	// del 2011/07/07 H.Osamoto ]
<?php 非表示終了 */ ?>
}
//地図移動
function ZdcEmapMapMove(lat, lon, lvl){
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.osamoto [
	//	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//	//マップ移動
	//	//	if(lvl) ZdcEmapMapObj.setMapLocation(center,lvl);
	//	//		else ZdcEmapMapObj.setMapLocation(center);
	//	ZdcEmapMapObj.setMapLocation(center);
	//	if(lvl) ZdcEmapMapObj.setMapScale(lvl);
<?php 非表示終了 */ ?>
	var center = new ZDC.LatLon(Number(lat), Number(lon));
	ZdcEmapMapObj.moveLatLon(center);
	if(lvl) ZdcEmapMapObj.setZoom(lvl);
	// mod 2011/07/07 H.osamoto ]
}
function ZdcEmapMapScroll(lat, lon){
	// mod 2011/07/07 H.Osamoto [
<?php /* 非表示開始 ?>
	//	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//	//マップ移動
	//	ZdcEmapMapObj.scrollToCenter(center);
<?php 非表示終了 */ ?>
	var center = new ZDC.LatLon(lat, lon);
	//マップ移動
	ZdcEmapMapObj.moveLatLon(center);
	// mod 2011/07/07 H.Osamoto ]
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

//地図移動(API2.0用)	add 2011/07/07 H.osamoto
function ZdcEmapMapMoveBoxApi2(minlat,minlon,maxlat,maxlon){
	
	var varlatlon_box = new Array();
	
	// 地図表示縮尺取得用仮想表示エリア
	varlatlon_box[0] = new ZDC.LatLon(minlat, minlon);
	varlatlon_box[1] = new ZDC.LatLon(maxlat, maxlon);
	var adjust = ZdcEmapMapObj.getAdjustZoom(varlatlon_box);
	
	// 地図移動＆縮尺変更
	ZdcEmapMapObj.moveLatLon(adjust.latlon);
	ZdcEmapMapObj.setZoom(adjust.zoom);
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
}
//遷移履歴のクリック動作がキャンセルされた場合に、履歴を元に戻す		add 2010/07/08 Y.Matsukawa
function ZdcEmapHistoryClickCancel() {
	ZdcEmapHistoryCnt = ZdcEmapHistoryCntSv;
}
//ひとつ戻る
function ZdcEmapHistoryBack() {
	ZdcEmapHistoryClick(ZdcEmapHistoryCnt - 1)
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
<?php /* 非表示開始 ?>
	// mod 2011/05/26 K.Masuda [
	//ZdcEmapHistorySet(ZdcEmapHistoryCnt,"<?PHP //echo $D_HISTORY_TOP_NAME; ?>","<?PHP //echo $D_HISTORY_TOP_LINK; ?>");
<?php 非表示終了 */ ?>
	if( <?php if(isset($D_QUERY_STRING) && $D_QUERY_STRING){echo "true";}else{echo "false";}  // mod 2011/10/03 Y.Nakajima ?> ){
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
			html_last = '<a href="javascript:ZdcEmapHistoryClick('+i+');"><?php if (isset($D_HISTORY_LAST_WORD)) echo $D_HISTORY_LAST_WORD; ?></a>';	// add 2009/03/04 Y.Matsukawa
<?php	// add 2010/03/23 Y.Matsukawa [
		for ($j = 1; $j <= 5; $j++) {
?>
			html_last_arr[<?php echo $j; ?>] = '<a href="javascript:ZdcEmapHistoryClick('+i+');"><?php if (isset($D_HISTORY_LAST_WORD_ARR[$j]) && $D_HISTORY_LAST_WORD_ARR[$j]) echo $D_HISTORY_LAST_WORD_ARR[$j]; // mod 2011/10/03 Y.Nakajima ?></a>';
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
	
	//mod 2011/10/03 Y.nakajima [
	//lvlが数字でないときの処理を追加
	if (isNaN(lvl) || !lvl || lvl < 1 || lvl >18) lvl = 0;
	//mod 2011/10/03 Y.nakajima ]

	var p,mrk,item;
	var icon = new ZdcIcon();
	
	//アイコンの作成
	icon.size      = new ZdcSize(sizew, sizeh);
	icon.offset    = new ZdcPixel(offsetx, offsety);
<?php /* 非表示開始 ?>
	//icon.image    = image;	2008/11/26 Y.Matsukawa del
	// 2008/11/26 Y.Matsukawa add [
	// icon.imageの末尾が「.gif」でないと、内部的にGIF以外として処理されてしまうので、末尾を無理矢理「.gif」にしています。
	// GIF以外で処理されてしまうと、IEで印刷時に透過GIFが透過しません。
	// タイムスタンプ値を付加しているのは、キャッシュ抑制のためです。これがないと、アイコン画像を差し替えた際に表示が崩れることがあります。（IEのみ）
<?php 非表示終了 */ ?>
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
//アイコン登録(API2.0用)	add 2011/07/07 H.osamoto
//-------------------------------------------------------------
var rtnhtml;
function ZdcEmapMakeMrkApi2(id,lat,lon,
						sizew,sizeh,newsizew,newsizeh,
						offsetx,offsety,newoffsetx,newoffsety,
						image,newimage,
						data1,data2,message,nflg,
						mouseclickmarker,
						mouseovermarker,
						lvl
						) {
	var mrk;
	var w;
	var h;
	var latlon = new ZDC.LatLon(lat, lon);
	var iconimage
	
	// icon.imageの末尾が「.gif」でないと、内部的にGIF以外として処理されてしまうので、末尾を無理矢理「.gif」にしています。
	// GIF以外で処理されてしまうと、IEで印刷時に透過GIFが透過しません。
	// タイムスタンプ値を付加しているのは、キャッシュ抑制のためです。これがないと、アイコン画像を差し替えた際に表示が崩れることがあります。（IEのみ）
	if (image.substr(image.length-4, 4) == ".gif") {
		iconimage = image;
	} else {
		dd = new Date();
		ts = dd.getTime();
		if (image.indexOf('?') < 0) {
			iconimage = image+"?dummy="+ts+".gif";
		} else {
			iconimage = image+"&dummy="+ts+".gif";
		}
	}	
	
	if (newimage) {
		//アイコンの作成（newアイコン有りの場合）
		mrk = new ZDC.Marker(latlon,{
			/* マーカのサイズに合わせて位置を調整する */
			offset: new ZDC.Pixel(offsetx, offsety),
			contentOffset: new ZDC.Pixel(newoffsetx, newoffsety),
			custom: {
				base : {
					src: iconimage,
					imgSize: ZDC.WH(sizew, sizeh)
				},
				content : {
					src: newimage,
					imgSize: ZDC.WH(newsizew, newsizeh)
				}
			}
		});
	} else {
		//アイコンの作成（通常）
		mrk = new ZDC.Marker(latlon,{
			/* マーカのサイズに合わせて位置を調整する */
			offset: new ZDC.Pixel(offsetx, offsety),
			custom: {
				base : {
					src: iconimage,
					imgSize: ZDC.WH(sizew, sizeh)
				}
			}
		});
	}
	
	
	//マーカーの基本情報
	mrk.id     = id;
	mrk.data1  = data1;
	mrk.data2  = data2;
	mrk.nflg   = nflg;
	mrk.lat     = lat;
	mrk.lon     = lon;
	if (lvl) mrk.lvl = lvl;			// add 2009/09/04 Y.Matsukawa
	
	//クリック時のイベント登録
	if (mouseclickmarker) {
		//吹き出しテキスト用アンカーイベント
		ZDC.addListener(mrk, ZDC.MARKER_CLICK, mouseclickmarker);
	}

	//マウスオーバー時のイベント登録
	if (mouseovermarker) {
		var center = ZdcEmapMapObj.getLatLon();
		var box = ZdcEmapMapObj.getLatLonBox();
		var maplatlen = box.getMax().lat - box.getMin().lat;
		var maplonlen = box.getMax().lon - box.getMin().lon;
		
		
		//表示位置の調整
		if (center.lat > lat) {
			//地図中心より下側に表示する場合
			var offsetycenter1 = 10;
			var offsetycenter2 = 90;
			var offsety = -40;
		} else {
			//地図中心より上側に表示する場合
			var offsetycenter1 = -10;
			var offsetycenter2 = -120;
			var offsety = 25;
		}
		if (center.lon > lon) {
			//地図中心より左側に表示する場合
			var offsetxcenter1 = 10;
			var offsetxcenter2 = 102;
			var offsetx = 20;
		} else {
			//地図中心より右側に表示する場合
			var offsetxcenter1 = -10;
			var offsetxcenter2 = -120;
			var offsetx = -170;
		}
		
		
		var mes = message.split("(");
		var userwidgetmoverlabel =
		{
			html: '<div style="background-color: #FFFFFF; font-size:16px; text-align:center; border:1px solid;">'+mes[0]+'</div>',
			size: new ZDC.WH(150, 60),
			offset: new ZDC.Pixel(offsetx, offsety)
		};
		var latlonmover = new ZDC.LatLon(lat, lon);
		var userwidgetmover = new ZDC.UserWidget(latlonmover, userwidgetmoverlabel);
		
		//吹き出しテキストイベント
		ZdcEmapMapObj.addWidget(userwidgetmover);
		//ZDC.addListener(mrk, ZDC.MARKER_MOUSEOVER, function(){userwidgetmover.open();});
		//ZDC.addListener(mrk, ZDC.MARKER_MOUSEOUT, function(){userwidgetmover.close();});
		
		//吹き出しテキスト用アンカーイベント
		//ZDC.addListener(mrk, ZDC.MARKER_MOUSEOVER, mouseovermarker);
		//マウスオーバーイベント登録
		ZDC.addListener(mrk, ZDC.MARKER_MOUSEOVER, mouseovermarker);
	}
	
	return mrk;
}

//-------------------------------------------------------------
//吹き出し用アンカー	add 2011/07/07 H.osamoto
//-------------------------------------------------------------
var ZdcEmapHukidasiAnchor = null;
function ZdcEmapAnchorDraw(id) {
	ZdcEmapTipsHideInfoInterval();
	//動作判定
	if(id == null) id = this.id;
	
	//駅アイコン座標取得
	var icnlat = ZdcEmapMapPoiMrkId[id].lat;
	var icnlon = ZdcEmapMapPoiMrkId[id].lon;
	
	var center = ZdcEmapMapObj.getLatLon();
	var box = ZdcEmapMapObj.getLatLonBox();
	var maplatlen = box.getMax().lat - box.getMin().lat;
	var maplonlen = box.getMax().lon - box.getMin().lon;
	
	var s = ZdcEmapMapObj.getZoom();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//オブジェクトの作成
	ZdcEmapTipsMarker = ZdcEmapMapPoiMrkId[id];
	if(!ZdcEmapMapObj || !ZdcEmapTipsMarker) return;
	
	//表示位置の調整
	if (center.lat > icnlat) {
		//地図中心より下側に表示する場合
		var offsetycenter1 = 3;
		var offsetycenter2 = 22;
	} else {
		//地図中心より上側に表示する場合
		var offsetycenter1 = -3;
		var offsetycenter2 = -30;
	}
	if (center.lon > icnlon) {
		//地図中心より左側に表示する場合
		var offsetxcenter1 = 3;
		var offsetxcenter2 = 25;
	} else {
		//地図中心より右側に表示する場合
		var offsetxcenter1 = -3;
		var offsetxcenter2 = -30;
	}
	
	var mrklat1 = ZdcEmapTipsMarker.lat + (offsetycenter1 * (maplatlen / 448));
	var mrklon1 = ZdcEmapTipsMarker.lon + (offsetxcenter1 * (maplonlen / 448));
	var mrklat2 = ZdcEmapTipsMarker.lat + (offsetycenter2 * (maplatlen / 448));
	var mrklon2 = ZdcEmapTipsMarker.lon + (offsetxcenter2 * (maplonlen / 448));
	
	var latlons = [];
	latlons[0] = new ZDC.LatLon(mrklat1, mrklon1);
	latlons[1] = new ZDC.LatLon(mrklat2, mrklon2);
	
	/* 線を作成 */
	var pl = new ZDC.Polyline(latlons, 
	{
		strokeWeight: 1,
		fillColor: '#FF0000'
	});

	/* 線を地図に追加 */
	ZdcEmapMapObj.addWidget(pl);
	
	ZdcEmapHukidasiAnchor = pl;
	ZDC.addListener(ZdcEmapTipsMarker, ZDC.MARKER_MOUSEOUT, function(){pl.hidden();});
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
//検索入り口(API2.0用)	add 2011/07/07 H.osamoto
function ZdcEmapRouteSearchApi2(id) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapRouteType == 0) return;
	ZdcEmapPoiRouteClear();
	
	var stationpoint = ZdcEmapMapPoiMrkId[id];
	var shoppoint = ZdcEmapMapShopDetailMrkId;
	
	//パラメーターの設定
	ZdcEmapRoutePoint1 = new ZDC.LatLon(stationpoint.lat, stationpoint.lon);
	ZdcEmapRoutePoint2 = new ZDC.LatLon(shoppoint.lat, shoppoint.lon);
	
	if(ZdcEmapRouteType == 1 || ZdcEmapRouteType == 3)
		ZdcEmapRouteSearchWalkApi2(stationpoint, shoppoint);

	//画面の移動
	ZdcEmapMapMoveBoxApi2(stationpoint.lat,stationpoint.lon,shoppoint.lat,shoppoint.lon);
}
//検索入り口
function ZdcEmapRouteSearch(name1,mx1,my1,name2,mx2,my2) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapRouteType == 0) return;
	ZdcEmapPoiRouteClear();
	
	//パラメーターの設定
	ZdcEmapRouteName1 = name1;
	ZdcEmapRouteName2 = name2;
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.Osamoto [
	//	ZdcEmapRoutePoint1 = new ZdcPoint(mx1, my1, <?PHP echo $D_PFLG; ?>);
	//	ZdcEmapRoutePoint2 = new ZdcPoint(mx2, my2, <?PHP echo $D_PFLG; ?>);
<?php 非表示終了 */ ?>
	var stationpoint = new ZDC.LatLon(Number(my2), Number(mx2));
	var shoppoint = new ZDC.LatLon(Number(my1), Number(mx1));
	ZdcEmapRoutePoint1 = stationpoint;
	ZdcEmapRoutePoint2 = shoppoint;
	// mod 2011/07/07 H.Osamoto ]
	
	if(ZdcEmapRouteType == 1 || ZdcEmapRouteType == 3)
		//ZdcEmapRouteSearchWalk(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);	mod 2011/07/07 H.osamoto
		ZdcEmapRouteSearchWalkApi2(stationpoint, shoppoint);
<?php /* 非表示開始 ?>
//	if(ZdcEmapRouteType == 2)
//		ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);		del 2011/07/07 H.osamoto
<?php 非表示終了 */ ?>

	//画面の移動
	//ZdcEmapMapMoveBox(my1,mx1,my2,mx2);		mod 2011/07/07 H.osamoto
	ZdcEmapMapMoveBoxApi2(stationpoint.lat,stationpoint.lon,shoppoint.lat,shoppoint.lon);
}
// 歩行者ルート検索(API2.0用)	add 2011/07/07 H.osamoto
function ZdcEmapRouteSearchWalkApi2(p1,p2) {
	ZdcEmapReadOn();
	
	/* スタート地点の緯度経度 */
	from = p1;
	/* ゴール地点の緯度経度 */
	to   = p2;
	
	ZDC.Search.getRouteByWalk({
		from: from,
		to: to
	},function(status, res) {
		if (status.code == '000') {
			/* 取得成功 */
			ZdcEmapwriteRoute(status, res, 1);
			ZdcEmapDispRouteDistance(res.route.distance);
		} else {
			/* 取得失敗 */
			if(ZdcEmapRouteType == 1) {
				//失敗だった場合自動車で再検索する
				ZdcEmapRouteSearchCarApi2(ZdcEmapRoutePoint1,ZdcEmapRoutePoint2);
			} else {
				alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + status.code + ']');
			}
			return;
		}
	});
}
// 自動車ルート検索(API2.0用)	add 2011/07/07 H.osamoto
function ZdcEmapRouteSearchCarApi2(p1,p2) {
	//ZdcEmapReadOn();
	
	/* スタート地点の緯度経度 */
	from = p1;
	/* ゴール地点の緯度経度 */
	to   = p2;
	
	ZDC.Search.getRouteByDrive({
		from: from,
		to: to
	},function(status, res) {
		if (status.code == '000') {
			/* 取得成功 */
			ZdcEmapwriteRoute(status, res, 2);
			ZdcEmapDispRouteDistance(res.route.distance);
		} else {
			/* 取得失敗 */
			alert('<?PHP echo $D_MSG_ERR_JS_ROUTE; ?> [' + status.code + ']');
			// ルート検索終了
			ZdcEmapReadOff();
		}
	});
}
// ルート描画	add 2011/07/07 H.osamoto
var ZdcEmapRoutePolyline = [];
var ZdcEmapRouteStartFlag;
var ZdcEmapRouteEndFlag;
function ZdcEmapwriteRoute(status, res, stype) {
	
	var guyde_type = {
		'start': {
			custom: {
				base: {
					src: '<?PHP echo $D_ROUTE_START_IMAGE; ?>',
					imgSize: new ZDC.WH(35, 35),
					imgTL: new ZDC.TL(0, 0)
				}
			},
			offset: ZDC.Pixel(-5, -36)
		},
		'end': {
			custom: {
				base: {
					src: '<?PHP echo $D_ROUTE_GOAL_IMAGE; ?>',
					imgSize: new ZDC.WH(35, 35),
					imgTL: new ZDC.TL(0, 0)
				}
			},
			offset: ZDC.Pixel(-5, -36)
		}
	};
	
	var line_property = {
		//歩行者用
		'通常通路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'横断歩道': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'横断通路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'歩道橋': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'踏切内通路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'連絡通路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'建物内通路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'敷地内通路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'乗換リンク': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'通路外': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'引き込みリンク': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		//自動車用
		'高速道路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'都市高速道路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'国道': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'主要地方道': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'都道府県道': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'一般道路(幹線)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'一般道路(その他)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'導入路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'細街路(主要)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'細街路(詳細)': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'フェリー航路': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'},
		'道路外': {strokeColor: '#3000ff', strokeWeight: 5, lineOpacity: 0.6, lineStyle: 'solid'}
	};



	/* スタートとゴールのアイコンを地図に重畳します */
	ZdcEmapRouteStartFlag = new ZDC.Marker(from,guyde_type['start']);
	ZdcEmapRouteEndFlag   = new ZDC.Marker(to,guyde_type['end']);
	/*
	スタートとゴールのウィジットが他のマーカの
	下にならないようにz-indexを設定します
	*/
	ZdcEmapRouteStartFlag.setZindex(110);
	ZdcEmapRouteEndFlag.setZindex(110);

	ZdcEmapMapObj.addWidget(ZdcEmapRouteStartFlag);
	ZdcEmapMapObj.addWidget(ZdcEmapRouteEndFlag);

	var link = res.route.link;
	
	var latlons = [];
	for (var i=0, j=link.length; i<j; i++) {
		
		if (stype == 1) {
			var opt = line_property[link[i].type.replace(/^\s+|\s+$/g, "")];
		} else {
			var opt = line_property[link[i].roadType.replace(/^\s+|\s+$/g, "")];
		}
		var pl = new ZDC.Polyline([], opt);
		
		for (var k=0, l=link[i].line.length; k<l; k++) {
			pl.addPoint(link[i].line[k]); 
			
			latlons[i] = link[i].line[0];

			if(i == j-1 && k == 1) {
				latlons[i+1] = link[i].line[1];
			}
		}
		ZdcEmapMapObj.addWidget(pl);
		ZdcEmapRoutePolyline[i] = pl;
	}
	/* 地点が全て表示できる縮尺レベルを取得 */
	var adjust = ZdcEmapMapObj.getAdjustZoom(latlons);
	ZdcEmapMapObj.moveLatLon(adjust.latlon);
	ZdcEmapMapObj.setZoom(adjust.zoom);
	
	// ルート検索終了
	ZdcEmapReadOff();

};

// ルート距離表示(API2.0用)	add 2011/07/07 H.osamoto
function ZdcEmapDispRouteDistance(dist) {
	
	//ルート距離表示
	var ZdcEmapRouteDistance = document.getElementById("ZdcEmapRouteDistance");
	if (ZdcEmapRouteDistance) {
		distance = dist;
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
	var result = this.getResult();
	if(result && (result.status !== 0)) {
		//エラー処理
		if(ZdcEmapRouteType == 1) {
			//失敗だった場合自動車で再検索する
			ZdcEmapRouteSearchCar(ZdcEmapRouteName1,ZdcEmapRoutePoint1,ZdcEmapRouteName2,ZdcEmapRoutePoint2);
		} else {
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
	var result = this.getResult();
	if(result && (result.status !== 0)) {
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
}
//ルート削除
function ZdcEmapPoiRouteClear() {
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.Osamoto [
	//	if(!ZdcEmapRouteSearchObj) return;
	//	if(ZdcEmapRouteOptionsObj.departurePoint.point) {
	//		try{
	//			ZdcEmapMapObj.ClearPRouteLayer();//1.5まで
	//		} catch(e) {
	//			ZdcEmapRouteSearchObj.clearRoute();//1.6以降
	//		}
	//	} else {
	//		ZdcEmapMapObj.removeRouteSearch();
	//	}
	//	delete ZdcEmapRouteOptionsObj;
	//	delete ZdcEmapRouteSearchObj;
	//	//スタート／ゴールのレイヤーを削除
	//	if(ZdcEmapRouteFlagLayer) ZdcEmapRouteFlagLayer.clearMarker();
	//	ZdcEmapMapObj.removeUserLayer(ZdcEmapRouteFlagLayer);
	//	delete ZdcEmapRouteFlagIcon1;
	//	delete ZdcEmapRouteFlagIcon2;
<?php 非表示終了 */ ?>
	if(!ZdcEmapRoutePolyline.length) return;
	
	for (var i=0; i<ZdcEmapRoutePolyline.length; i++) {
		if (ZdcEmapRoutePolyline[i]) {		<?php // add 2012/03/16 H.Osamoto ?>
			ZdcEmapMapObj.removeWidget(ZdcEmapRoutePolyline[i]);
			delete ZdcEmapRoutePolyline[i];
		}
	}
	
	//スタート／ゴールのレイヤーを削除
	if(ZdcEmapRouteStartFlag){
		ZdcEmapMapObj.removeWidget(ZdcEmapRouteStartFlag);
		delete ZdcEmapRouteStartFlag;
	}
	if(ZdcEmapRouteEndFlag){
		ZdcEmapMapObj.removeWidget(ZdcEmapRouteEndFlag);
		delete ZdcEmapRouteEndFlag;
	}
	
	// mod 2011/07/07 H.Osamoto ]
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
	if( <?php if(isset($D_HUKIDASHI_SEARCH) && $D_HUKIDASHI_SEARCH){echo "false";}else{echo "true";} // mod 2011/10/03 Y.Nakajima ?> ){
		//	if(ZdcEmapMapObj.getUserMsgOpenStatus()) return;//フキダシ表示中は検索しない	mod 2011/07/07 H.osamoto
		if(userwidgethukidasi) {
			if(userwidgethukidasi.kg) {
				return;//フキダシ表示中は検索しない
			}
		}
	}
	// 2011/06/15 K.Masuda mod ]
	ZdcEmapSearchPoint = null;		// add 2011/07/07 H.osamoto
	eval(ZdcEmapSearchEventFunc);
}
//検索イベント追加
function ZdcEmapSearchEventAdd(func) {
	ZdcEmapSearchEventDel();
	ZdcEmapSearchEventFunc = func;
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.osamoto [
	//	ZdcEmapSearchEventDragmapend    = ZdcEvent.addListener(ZdcEmapMapObj, "dragmapend"   , ZdcEmapSearchEventAction);
	//	ZdcEmapSearchEventScrollmapend  = ZdcEvent.addListener(ZdcEmapMapObj, "scrollmapend" , ZdcEmapSearchEventAction);
	//	ZdcEmapSearchEventChangezoomend = ZdcEvent.addListener(ZdcEmapMapObj, "changezoomend", ZdcEmapSearchEventAction);
<?php 非表示終了 */ ?>
	ZdcEmapSearchEventDragmapend    = ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_DRAG_END, ZdcEmapSearchEventAction);
	ZdcEmapSearchEventScrollmapend  = ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_SCROLL_END, ZdcEmapSearchEventAction);
	ZdcEmapSearchEventChangezoomend = ZDC.addListener(ZdcEmapMapObj, ZDC.MAP_CHG_ZOOM, ZdcEmapSearchEventAction);
	// mod 2011/07/07 H.osamoto [
}
//検索イベント削除
function ZdcEmapSearchEventDel() {
	ZdcEmapSearchEventStop();
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.osamoto [
	//	if(ZdcEmapSearchEventDragmapend)    ZdcEvent.removeListener(ZdcEmapSearchEventDragmapend);
	//	if(ZdcEmapSearchEventScrollmapend)  ZdcEvent.removeListener(ZdcEmapSearchEventScrollmapend);
	//	if(ZdcEmapSearchEventChangezoomend) ZdcEvent.removeListener(ZdcEmapSearchEventChangezoomend);
<?php 非表示終了 */ ?>
	if(ZdcEmapSearchEventDragmapend)    ZDC.removeListener(ZdcEmapSearchEventDragmapend);
	if(ZdcEmapSearchEventScrollmapend)  ZDC.removeListener(ZdcEmapSearchEventScrollmapend);
	if(ZdcEmapSearchEventChangezoomend) ZDC.removeListener(ZdcEmapSearchEventChangezoomend);
	// mod 2011/07/07 H.osamoto ]
	
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
	//	var s = ZdcEmapMapObj.getMapScale();	mod 2011/07/07 H.Osamoto
	var s = ZdcEmapMapObj.getZoom();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//オブジェクトの作成
	//	ZdcEmapTipsMarker = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapPoiMrkId[id]);	mod 2011/07/07 H.Osamoto
	ZdcEmapTipsMarker = ZdcEmapMapPoiMrkId[id];
	if(!ZdcEmapMapObj || !ZdcEmapTipsMarker) return;
<?php /* 非表示開始 ?>
	// mod 2011/07/07 H.Osamoto [
	//	if(!ZdcEmapTipsShape) ZdcEmapTipsShape = new ZdcShape.Text();
	//	if(!ZdcEmapTipsShapeLayer) ZdcEmapTipsShapeLayer = new ZdcShape.Layer();
	//	ZdcEmapMapObj.addShapeLayer(ZdcEmapTipsShapeLayer);
	//	ZdcEmapTipsShapeLayer.setZIndex(4010);
	//	//テキストの設定
	//	ZdcEmapTipsShape.textString = ZdcEmapTipsMarker.data1;
	//	ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	//	ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	//	ZdcEmapTipsShape.font = "<?PHP echo $D_TIPS_FONT; ?>";
	//	ZdcEmapTipsShape.borderWidth = <?PHP echo $D_TIPS_BORDERWIDTH; ?>;
	//	ZdcEmapTipsShape.bgColor = "<?PHP echo $D_TIPS_BGCOLOR; ?>";
	//	ZdcEmapTipsShape.shadowFlg = <?PHP echo $D_TIPS_SHADOWFLG; ?>;
	//	ZdcEmapTipsShape.shadowX = <?PHP echo $D_TIPS_SHADOWX; ?>;
	//	ZdcEmapTipsShape.shadowY = <?PHP echo $D_TIPS_SHADOWY; ?>;
	//	ZdcEmapTipsShape.opacity = <?PHP echo $D_TIPS_OPACITY; ?>;
	//	//表示位置の調整
	//	var box = ZdcEmapMapObj.getMapBoundBox();
	//	var point = new ZdcPoint(ZdcEmapTipsMarker.Point.mx, ZdcEmapTipsMarker.Point.my, <?PHP echo $D_PFLG; ?>);
	//	var x,y,v,h;
	//	if(Math.abs(box.minx - point.mx) < Math.abs(box.maxx - point.mx)){ 
	//		h = "left"; 
	//		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X; ?>;
	//	}else{
	//		h = "right";
	//		ZdcEmapTipsShape.offsetx = <?PHP echo $D_TIPS_OFFSET_X*-1; ?>;
	//	}
	//	if(Math.abs(box.miny - point.my) < Math.abs(box.maxy - point.my)){
	//		v = "bottom";
	//		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y*-1; ?>;
	//	}else{
	//		v = "top";
	//		ZdcEmapTipsShape.offsety = <?PHP echo $D_TIPS_OFFSET_Y; ?>;
	//	}
	//	ZdcEmapTipsShape.anchor = h + "-" + v;
	//	ZdcEmapTipsShape.setPoint(point);
	//	ZdcEmapTipsShapeLayer.addShape(ZdcEmapTipsShape);
	//	//描画中心が地図範囲外の場合移動する
	//	if(ZdcEmapTipsMarker.Point.mx < box.minx || ZdcEmapTipsMarker.Point.my < box.miny || ZdcEmapTipsMarker.Point.mx > box.maxx || ZdcEmapTipsMarker.Point.my > box.maxy)
	//		ZdcEmapMapObj.setMapLocation(ZdcEmapTipsMarker.Point);
	//	//描画
	//	if(!ZdcEmapTipsTopMarkerLayer) ZdcEmapTipsTopMarkerLayer = new ZdcUserLayer();//最上位マーカーレイヤー
	//	if(!ZdcEmapTipsTopMarker) ZdcEmapTipsTopMarker = new ZdcMarker(new ZdcPoint(ZdcEmapTipsMarker.getPoint().lon ,ZdcEmapTipsMarker.getPoint().lat), ZdcEmapTipsMarker.getIcon());
	//	ZdcEmapTipsTopMarkerLayer.addMarker(ZdcEmapTipsTopMarker);
	//	ZdcEmapMapObj.addUserLayer(ZdcEmapTipsTopMarkerLayer);
	//	ZdcEmapTipsTopMarkerLayer.doc.style.zIndex = 4011;
	//	ZdcEmapTipsTopMarker.mouseclickmarker = ZdcEmapTipsMarker.mouseclickmarker;
	//	//イベントの設定
	//	if(ZdcEmapTipsTopMarker.mouseclickmarker) ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseclickmarker", ZdcEmapTipsTopMarker.mouseclickmarker);
	//	ZdcEvent.addListener(ZdcEmapTipsTopMarker, "mouseoutmarker", ZdcEmapTipsHideInfo);
	//	ZdcEmapTipsTimerID = setTimeout(ZdcEmapTipsHideInfoInterval, ZdcEmapTipsInterval);
<?php 非表示終了 */ ?>
	
	var lat = ZdcEmapTipsMarker.lat;
	var lon = ZdcEmapTipsMarker.lon;
	var center = ZdcEmapMapObj.getLatLon();
	var box = ZdcEmapMapObj.getLatLonBox();
	var maplatlen = box.getMax().lat - box.getMin().lat;
	var maplonlen = box.getMax().lon - box.getMin().lon;
	
	
	//表示位置の調整
	if (center.lat > lat) {
		//地図中心より下側に表示する場合
		var offsetycenter1 = 10;
		var offsetycenter2 = 90;
		var offsety = -40;
	} else {
		//地図中心より上側に表示する場合
		var offsetycenter1 = -10;
		var offsetycenter2 = -120;
		var offsety = 25;
	}
	if (center.lon > lon) {
		//地図中心より左側に表示する場合
		var offsetxcenter1 = 10;
		var offsetxcenter2 = 102;
		var offsetx = 20;
	} else {
		//地図中心より右側に表示する場合
		var offsetxcenter1 = -10;
		var offsetxcenter2 = -120;
		var offsetx = -170;
	}
	
	var message = ZdcEmapTipsMarker.message;
	var mes = message.split("(");
	var userwidgetmoverlabel =
	{
		html: '<div style="background-color: #FFFFFF; font-size:16px; text-align:center; padding-top: 3px; padding-bottom: 2px; border:1px solid;">'+mes[0]+'</div>',
		size: new ZDC.WH(150, 60),
		offset: new ZDC.Pixel(offsetx, offsety)
	};
	var latlonmover = new ZDC.LatLon(lat, lon);
	var userwidgetmover = new ZDC.UserWidget(latlonmover, userwidgetmoverlabel);
	
	
	//吹き出し表示
	ZdcEmapMapObj.addWidget(userwidgetmover);
	ZDC.addListener(ZdcEmapTipsMarker, ZDC.MARKER_MOUSEOUT, function(){userwidgetmover.close();});
	ZdcEmapAnchorDraw(id);
	userwidgetmover.open();
	ZdcEmapTipsShapeLayer = userwidgetmover;
	ZdcEmapTipsTimerID = setTimeout(ZdcEmapTipsHideInfoInterval, ZdcEmapTipsInterval);
	
	// mod 2011/07/07 H.Osamoto ]
}
//レイヤーを閉じる
function ZdcEmapTipsClose() {
	//シェイプレイヤーを閉じる
	if(ZdcEmapTipsShapeLayer)
	{
		ZdcEmapTipsShapeLayer.close();
	}
	if(ZdcEmapHukidasiAnchor)
	{
		ZdcEmapMapObj.removeWidget(ZdcEmapHukidasiAnchor);
	}
	ZdcEmapTipsShapeLayer = null;
	ZdcEmapTipsShape = null;
	ZdcEmapHukidasiAnchor = null;
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
	//if(ZdcEmapReading == 1) ZdcEmapMapObj.visibleZdcWait();		del 2011/07/07 H.osamoto
}
function ZdcEmapReadOff() {
	if(ZdcEmapReading <= 0) return;
	ZdcEmapReading --;
	//if(ZdcEmapReading == 0) ZdcEmapMapObj.hiddenZdcWait();		del 2011/07/07 H.osamoto
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

<?php /* 非表示開始 ?>
// del 2011/07/07 H.osamoto [
//	// アイコンを前面に移動（APIv1.10で実装予定の機能を先行して実装）		add 2009/10/14 Y.Matsukawa
//	//v110 add -- set top zindex for marker
//	ZdcMarker.prototype.setTopZIndex=function(idx){
//	//	if (this.parentLayer.addmapstatus){
//	//		for (var i=0; i<this.parentLayer.markers.length; i++){
//	//			if (this.parentLayer.markers[i]!=null){
//	//				this.parentLayer.markers[i].doc.style.zIndex = 3;
//	//			}
//	//		}
//	//	}
//		if (idx) {
//			this.doc.style.zIndex = idx;
//		} else {
//			this.doc.style.zIndex = 4;
//		}
//	}
//	//v110 add -- set defalut zindex for marker
//	ZdcMarker.prototype.setDefaultZIndex=function(){
//		//this.doc.style.zIndex = 0;
//		this.doc.style.zIndex = 3;
//	}
// del 2011/07/07 H.osamoto ]
<?php 非表示終了 */ ?>

// add 2011/07/07 H.osamoto [
//common func
ZdcSetErrorStatus = function(retcd, st){
	var status;
	if (st == undefined){
		var errPart = retcd.charAt(4);
		var errPartStr = retcd.slice(3, 5);
		if( errPart == '9' ){
			status = 1;		//パラメータエラー
		}else if( retcd.substr(4,4) == '1009' ){
			status = 5;		//該当データなし
		}else if ( errPart == '2' ){
			status = 6;		//認証エラー
		}else if ( errPart == '6' || errPart == '7' || errPart == '8' || errPartStr == '15'){
			status = 2;		//サーバーエラー
		}else{
			status = 9;		//その他エラー
		}
	}else{
		status = st;
	}
	this.retCode  = retcd || '';
	this.type = '';
	this.status = status;
	this.recCount    = 0;
	this.hitCount = 0;
	this.rest =   false;
	this.items = [];
}
// add 2011/07/07 H.osamoto ]


