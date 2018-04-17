<?PHP
// ------------------------------------------------------------
// 地図制御javasctipt 主に拠点以外の検索に関するもの
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2007/11/16 Y.Matsukawa	初期表示時に地図APIのChangeLocationイベントが３回発生する→２回に減らす
// 2008/04/21 Y.Matsukawa	検索TOPウィンドウに絞り込み条件を実装
// 2008/05/07 Y.Matsukawa	【IE6不具合対応】地図画面のリストボックスが検索ウィンドウの上に出てくる
// 2008/08/22 Y.Matsukawa	英字対応
// 2008/10/22 Y.Matsukawa	使用しないJSはロードしない
// 2009/03/10 Y.Matsukawa	検索結果画面へ自由項目パラメータを引き渡す
// 2009/03/26 Y.Matsukawa	絞込み画面へ自由項目パラメータを引き渡す
// 2009/09/03 Y.Matsukawa	検索TOPから緯度経度接続時にcond反映
// 2009/11/07 Y.Matsukawa	拠点項目拡張（50→200）
// 2009/12/22 Y.Matsukawa	検索TOPにcondを渡す
// 2010/01/27 Y.Matsukawa	絞り込みテンプレートに都道府県コードを渡す
// 2010/03/09 Y.Matsukawa	住所FW検索から拠点リスト（地図なし）へ遷移
// 2010/05/11 Y.Matsukawa	検索一覧にチェックボックス
// 2010/05/19 Y.Matsukawa	路線図テンプレートに任意パラメータを渡す
// 2010/06/16 Y.Matsukawa	出発地を指定してルート探索
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/11/03 K.Masuda		エリア検索複数対応
// 2011/02/09 Y.Matsukawa	内部アクセスをドメインから内部IPに変更
// 2011/02/16 Y.Matsukawa	検索結果住所一覧で選択した住所を、出発地指定ルートの入力初期値にする
// 2011/04/14 H.Osamoto		Myエリア対応
// 2011/06/02 H.Osamoto		フリーワード複合検索対応
// 2011/06/16 Y.Matsukawa	詳細更新時にJS実行
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/08/10 K.Masuda		地図なし拠点リストで絞り込みによる再検索を行う
// 2011/11/25 Y.Matsukawa	ピーシーデポ対応（最寄りルート専用モード）
// 2012/03/19 K.Masuda		検索地点にアイコン表示機能追加
// ------------------------------------------------------------
include("./inc/define.inc");  // 基本設定
include("./unicode.js");  // 機種依存文字チェック用のコード表
?>
//-------------------------------------------------------------
//位置検索関係
//-------------------------------------------------------------
var ZdcEmapRailMainObj;
var ZdcEmapRailSubObj;
var ZdcEmapAreaObj;
var ZdcEmapNearShop = new ZdcNearShop();
// add 2011/08/10 K.Masuda [
var ReSearchFlg;
var SrchWin_type,SrchWin_prm,SrchWin_name;
// add 2011/08/10 K.Masuda ]
// add 2011/06/16 Y.Matsukawa [
var ZdcEmapKyotenId = null;
if (typeof ZdcKyotenId == 'function') {
	ZdcEmapKyotenId = new ZdcKyotenId();
}
// add 2011/06/16 Y.Matsukawa ]
<?php if(isset($D_REQ_JSAPI["searchrailway"]) && $D_REQ_JSAPI["searchrailway"]){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapRailway = new ZdcSearchRailwayMap();
<?php } ?>
<?php if(isset($D_REQ_JSAPI["searchmap"]) && $D_REQ_JSAPI["searchmap"]){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapArea    = new ZdcSearchMap();
<?php } ?>

//検索ボタンの押下
function ZdcEmapSearchClick() {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchOpen("","","")
}
//検索の接続インターフェイス
function ZdcEmapSearchOpenFirst(type,prm,name) {
	//	var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>&";
	//	for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "cond"+i+"="+ZdcEmapSaveCond[i]+"&";//絞込条件
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
	//for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//絞込条件		mod 2009/11/07 Y.Matsukawa
	for(i = 1;i <= 200;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//絞込条件
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
	<?php // add 2010/01/27 Y.Matsukawa [ ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
	<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
	<?php //mod 2011/07/05 Y.Nakajima ] ?>
	<?php // add 2010/01/27 Y.Matsukawa ] ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapCondObj.innerHTML = html;
		//絞込み条件組み立て
		var cond = ZdcEmapGetCond();
		prm += "&cond=" + cond;
		//検索窓開く
		ZdcEmapSearchChange(type,prm,name);
	});
	ZdcEmapCondObj.mode = "cond";
	ZdcEmapCondObj.style.visibility = "visible";
}
//検索ウィンドウからの接続				add 2008/04/21 Y.Matsukawa
function ZdcEmapSearchOpenFromSrchWin(type,prm,name) {
	// add 2011/08/10 K.Masuda [
	SrchWin_type = type;
	SrchWin_prm  = prm;
	SrchWin_name = name;
	// add 2011/08/10 K.Masuda ]
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
	url = url + "&" + prm;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
	<?php // add 2010/01/27 Y.Matsukawa [ ?>
	<?php //mod 2011/07/05 Y.Nakajima [ ?>
	<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
	<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
	<?php //mod 2011/07/05 Y.Nakajima ] ?>
	<?php // add 2010/01/27 Y.Matsukawa ] ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) &&  $https_req !=""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapCondObj.innerHTML = html;
		//絞込み条件組み立て
		var cond = ZdcEmapGetCond();
		prm += "&cond=" + cond;
		//検索窓開く
		ZdcEmapSearchChange(type,prm,name);
	});
	ZdcEmapCondObj.mode = "cond";
	ZdcEmapCondObj.style.visibility = "visible";
}
//検索窓を開く
function ZdcEmapSearchOpen(type,prm,name) {
	//色々初期化
	ZdcEmapSearchEventStop();
	ZdcEmapSearchClear();
	//検索窓読み込み
	ZdcEmapSearchChange(type,prm,name);
}
//窓書き換え
function ZdcEmapSearchChange(type,prm,name) {
	// add 2011/08/10 K.Masuda [
	SrchWin_type = type;
	SrchWin_prm  = prm;
	SrchWin_name = name;
	// add 2011/08/10 K.Masuda ]
	//パラメーター組み立て
	//prm = "&type="+type+"&"+prm;		mod 2009/03/10 Y.Matsukawa
	prm = "&type="+type+"&"+prm+"&<?php echo $P_FREEPARAMS; ?>";
	//画面履歴更新
	switch(type) {
		case "AddrW"://住所フリーワード
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["AddrW"]; ?>("+name+")","ZdcEmapSearchOpen('AddrW','"+prm+"','"+name+"');");
			break;
		case "StW"://駅フリーワード
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["StW"]; ?>("+name+")","ZdcEmapSearchOpen('StW','"+prm+"','"+name+"');");
			break;
		case "PoiW"://施設フリーワード
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["PoiW"]; ?>("+name+")","ZdcEmapSearchOpen('PoiW','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('PoiW','"+prm+"','"+name+"');");
			}
			break;
		case "ZipW"://郵便番号フリーワード
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["ZipW"]; ?>("+name+")","ZdcEmapSearchOpen('ZipW','"+prm+"','"+name+"');");
			break;
		case "AddrL"://住所リスト
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["AddrL"]; ?>("+name+")","ZdcEmapSearchOpen('AddrL','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('AddrL','"+prm+"','"+name+"');");
			}
			break;
		case "StL"://駅リスト
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["StL"]; ?>("+name+")","ZdcEmapSearchOpen('StL','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('StL','"+prm+"','"+name+"');");
			}
			break;
		case "PoiL"://施設リスト
			if(name.charAt(0) != ":") {
				ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["PoiL"]; ?>("+name+")","ZdcEmapSearchOpen('PoiL','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('PoiL','"+prm+"','"+name+"');");
			}
			break;
		case "ShopW"://拠点フリーワード
			if(ReSearchFlg != 1){ 	// add 2011/08/10 K.Masuda
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["ShopW"]; ?>("+name+")","ZdcEmapSearchOpen('ShopW','"+prm+"','"+name+"');");
			// add 2011/07/12 K.Masuda [
			<?php //mod 2011/09/09 Y.nakajima ?>
			if(<?PHP if(isset($D_FREE_SRCH_COL)){echo $D_FREE_SRCH_COL;}else{echo "false";} ?>){
				var freesrch = 0;
				sep_prm = prm.split("&");
				for( var scnt=0; scnt<sep_prm.length; scnt++){
					if(sep_prm[scnt].match(/col=FREE_SRCH/)){
						freesrch = 1;
						break;
					}
				}
				if( freesrch == 0 ){
					<?php //mod 2011/09/09 Y.nakajima ?>
					ZdcEmapHistoryAdd("<?PHP if (isset($D_HISTORY_NAME["ShopW_COL"])) echo $D_HISTORY_NAME["ShopW_COL"]; ?>("+name+")","ZdcEmapSearchOpen('ShopW','"+prm+"','"+name+"');");
				}
			}
			}
			ReSearchFlg = "";	// add 2011/08/10 K.Masuda
			// add 2011/07/12 K.Masuda ]
			break;
		case "ShopA"://拠点エリア
			if(ReSearchFlg != 1){	// add 2011/08/10 K.Masuda 
			if(name.charAt(0) != ":") {
				// add 2010/11/03 K.Masuda [
				var ptnw1,ptnw2,history_name,hn1,hn2,hn3,hn4,hn5;
				if(prm){
					ptnw1 = prm.match(/areaptn=[0-9]*/);
					if(ptnw1){
						ptnw2 = ptnw1[0].match(/[0-9]+/);
					} else {
						ptnw2 = "99";	
					}
				} else {
					ptnw2 = "99";	
				}
				if( ptnw2 == 1) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA"]; ?>";
				} else if( ptnw2 == 2) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_2"]; ?>";
				} else if( ptnw2 == 3) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_3"]; ?>";
				} else if( ptnw2 == 4) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_4"]; ?>";
				} else if( ptnw2 == 5) {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA_5"]; ?>";
				} else {
					history_name = "<?PHP echo $D_HISTORY_NAME["ShopA"]; ?>";
				}
				// add 2010/11/03 K.Masuda ]
				//ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["ShopA"]; ?>","ZdcEmapSearchOpen('ShopA','"+prm+"','"+name+"');");	mod 2010/11/03 K.Masuda
				ZdcEmapHistoryAdd(history_name,"ZdcEmapSearchOpen('ShopA','"+prm+"','"+name+"');");
			} else {
				ZdcEmapHistoryAdd(name.substring(1,name.length),"ZdcEmapSearchOpen('ShopA','"+prm+"','"+name+"');");
			}
			}
			ReSearchFlg = "";	// add 2011/08/10 K.Masuda
			break;
		// add 2010/03/09 Y.Matsukawa [
		case "Nshop"://最寄り拠点（地図なし）
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Nshop"]; ?>","ZdcEmapSearchOpen('Nshop','"+prm+"','"+name+"');");
			break;
		// add 2010/03/09 Y.Matsukawa ]
		// add 2010/06/02 H.osamoto [
		case "Comb"://フリーワード複合検索
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Comb"]; ?>("+name+")","ZdcEmapSearchOpen('Comb','"+prm+"','"+name+"');");
			break;
		// add 2010/06/02 H.osamoto ]
		default:
			ZdcEmapSetFRouteInit('');		// add 2011/02/16 Y.Matsukawa
			ZdcEmapHistoryClear();
			break;
	}
<?php
	// add 2009/12/22 Y.Matsukawa
	//-------------------
	// cond条件をテンプレートに渡す
	//-------------------
	$cond_prm = "";
	for($i = 1; $i <= 200; $i++) {
		$cond = "cond".$i;
		//mod 2011/07/05 Y.Nakajima
		if(isset($_VARS[$cond]) ) {
			//$cond_prm = "&cond".$i."=".$_VARS[$cond];	mod 2011/08/10 K.Masuda
			$cond_prm .= "&cond".$i."=".$_VARS[$cond];
		}
		//mod 2011/09/09 Y.Nakajima
		if(isset(${"scond".$i}) && isset($_VARS[${"scond".$i}]) ) {
			$cond_prm .= "&scond".$i."=".$_VARS[${"scond".$i}];	// add 2011/08/10 K.Masuda
		}
	}
?>
	//画面書き換え
<?php // add 2016/02/20 Y.Matsukawa [ ?>
	var cond = ZdcEmapGetSearchTopCond();
	if (<?php echo ($D_KEEP_COND_ON_HISTORY ? 'true' : 'false'); ?> && cond) {
//alert("(1) "+cond);
		ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"&"+cond<?php if($https_req){ ?>+"&https_req=1"<?php } ?>);
	} else {
//alert("(2) <?php echo $cond_prm; ?>");
<?php // add 2016/02/20 Y.Matsukawa ] ?>
		//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm);		mod 2009/12/22 Y.Matsukawa
		//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>");	mod 2010/07/20 Y.Matsukawa
		//ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>"<?php if($https_req){ ?>+"&https_req=1"<?php } ?>);	mod 2011/02/09 Y.Matsukawa
		ZdcEmapSearchRequest("<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>"+prm+"<?php echo $cond_prm; ?>"<?php if($https_req){ ?>+"&https_req=1"<?php } ?>);
	}
}
function ZdcEmapSearchRequest(url) {
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";

		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?PHP if (isset($D_SEARCHLIST_SCOND) && $D_SEARCHLIST_SCOND != "") { ?>ZdcEmapCond2SearchTopCond();<?PHP }	// add 2010/05/11 Y.Matsukawa ?>
		<?PHP //if ($D_SEARCHLIST_SCOND) { ?>ZdcEmapCond2SearchTopCond();<?PHP //}	// add 2010/05/11 Y.Matsukawa ?>
		<?php // 住所マッチング結果がある場合は表示する		add 2011/11/25 Y.Matsukawa ?>
		var ele = document.getElementById("ZdcEmapAddrMatchStringAtTop");
		if (ele) {
			if (ZdcEmapAddrMatchString) {
				ele.innerHTML = ZdcEmapAddrMatchString;
				ZdcEmapAddrMatchString = null;
			} else {
				ele.innerHTML = "";
			}
		}
	});
}
//窓閉じる
function ZdcEmapSearchClose() {
	if(ZdcEmapSearchWindowObj.style.visibility == "hidden") return;
	//特別なDIVを閉じる
	ZdcEmapSearchRailwayRemove();
	ZdcEmapSearchAreaRemove();
	//
	ZdcEmapSearchWindowObj.innerHTML = "";
	ZdcEmapSearchWindowObj.style.visibility = "hidden";
	if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "hidden";// add 2008/05/07 Y.Matsukawa
	ZdcEmapSearchEventStart();
}
//窓書き換え準備
function ZdcEmapSearchClear() {
	if(ZdcEmapSearchWindowObj.style.visibility == "hidden") return;
	//特別なDIVを閉じる
	ZdcEmapSearchRailwayRemove();
	ZdcEmapSearchAreaRemove();
}
//キャンセル
function ZdcEmapSearchCancel() {
	//特別なDIVを閉じる
	ZdcEmapSearchRailwayRemove();
	ZdcEmapSearchAreaRemove();
	//画面の遷移
	if(ZdcEmapHistorySaveChk()) {
		ZdcEmapHistoryLoad();
		ZdcEmapSearchClose();
	} else {
		ZdcEmapHistoryClick(0);
	}
}
//検索決定
//function ZdcEmapSearchSet(lat,lon) {		2007/11/16 mod Y.Matsukawa
function ZdcEmapSearchSet(lat,lon,notmove) {
	ZdcEmapShopDetailClose();
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["List"]; ?>","ZdcEmapSearchSet('"+lat+"','"+lon+"');");
	ZdcEmapHistorySave();
	//マップ移動
	ZdcEmapSearchEventStop();
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//ZdcEmapMapObj.setMapLocation(center);		2007/11/16 mod Y.Matsukawa
	if (!notmove) ZdcEmapMapObj.setMapLocation(center);
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	<?php //ルート時間表示を初期化 ?>
	ele = document.getElementById("ZdcEmapRouteTimeH");
	if (ele) ele.innerHTML = "0";
	ele = document.getElementById("ZdcEmapRouteTimeHH");
	if (ele) ele.innerHTML = "00";
	ele = document.getElementById("ZdcEmapRouteTimeN");
	if (ele) ele.innerHTML = "0";
	ele = document.getElementById("ZdcEmapRouteTimeNN");
	if (ele) ele.innerHTML = "00";
	<?php //出発地の緯度経度を表示 ?>
	ZdcEmapRouteStartLat = lat;
	ZdcEmapRouteStartLon = lon;
	if (ZdcEmapRouteStartLat && ZdcEmapRouteStartLon) {
		<?php //日本測地系 ?>
		<?php //緯度（ミリ秒） ?>
		ele = document.getElementById("ZdcEmapRouteStartLat_TKY_MS");
		if (ele) ele.innerHTML = ZdcEmapRouteStartLat;
		<?php //経度（ミリ秒） ?>
		ele = document.getElementById("ZdcEmapRouteStartLon_TKY_MS");
		if (ele) ele.innerHTML = ZdcEmapRouteStartLon;
		<?php //緯度（十進） ?>
		ele = document.getElementById("ZdcEmapRouteStartLat_TKY_DEG");
		if (ele) ele.innerHTML = ZdcCommon.MS2DEG(ZdcEmapRouteStartLat);
		<?php //経度（十進） ?>
		ele = document.getElementById("ZdcEmapRouteStartLon_TKY_DEG");
		if (ele) ele.innerHTML = ZdcCommon.MS2DEG(ZdcEmapRouteStartLon);
		<?php //緯度（度分秒） ?>
		dms = ZdcCommon.MS2DMS(ZdcEmapRouteStartLat);
		ele = document.getElementById("ZdcEmapRouteStartLat_TKY_DMS");
		if (ele) ele.innerHTML = dms.deg+"."+dms.min+"."+dms.sec;
		<?php //経度（度分秒） ?>
		dms = ZdcCommon.MS2DMS(ZdcEmapRouteStartLon);
		ele = document.getElementById("ZdcEmapRouteStartLon_TKY_DMS");
		if (ele) ele.innerHTML = dms.deg+"."+dms.min+"."+dms.sec;
		<?php //世界測地系 ?>
		wgs = ZdcCommon.TKY2WGS(ZdcCommon.MS2DEG(ZdcEmapRouteStartLon), ZdcCommon.MS2DEG(ZdcEmapRouteStartLat));
		<?php //緯度（ミリ秒） ?>
		ele = document.getElementById("ZdcEmapRouteStartLat_WGS_MS");
		if (ele) ele.innerHTML = DEG2MS(wgs.lat);
		<?php //経度（ミリ秒） ?>
		ele = document.getElementById("ZdcEmapRouteStartLon_WGS_MS");
		if (ele) ele.innerHTML = DEG2MS(wgs.lon);
		<?php //緯度（十進） ?>
		ele = document.getElementById("ZdcEmapRouteStartLat_WGS_DEG");
		if (ele) ele.innerHTML = wgs.lat;
		<?php //経度（十進） ?>
		ele = document.getElementById("ZdcEmapRouteStartLon_WGS_DEG");
		if (ele) ele.innerHTML = wgs.lon;
		<?php //緯度（度分秒） ?>
		dms = ZdcCommon.DEG2DMS(wgs.lat);
		ele = document.getElementById("ZdcEmapRouteStartLat_WGS_DMS");
		if (ele) ele.innerHTML = dms.deg+"."+dms.min+"."+dms.sec;
		<?php //経度（度分秒） ?>
		dms = ZdcCommon.DEG2DMS(wgs.lon);
		ele = document.getElementById("ZdcEmapRouteStartLon_WGS_DMS");
		if (ele) ele.innerHTML = dms.deg+"."+dms.min+"."+dms.sec;
	}
	<?php // 住所マッチング結果がある場合は表示する ?>
	ele = document.getElementById("ZdcEmapAddrMatchStringAtMap");
	if (ele) {
		if (ZdcEmapAddrMatchString) {
			ele.innerHTML = ZdcEmapAddrMatchString;
			ZdcEmapAddrMatchString = null;
		} else {
			ele.innerHTML = "";
		}
	}
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
	<?php // add 2012/03/19 K.Masuda [
	if($D_SEARCH_MAP_ICON){ ?>
	ZdcEmapSearchMapIcon();
	<?php
	}
	// add 2012/03/19 K.Masuda ] ?>
	//拠点検索
	ZdcEmapSearchFirst = 1;
	ZdcEmapSearchPoint = null;//必ず再検索させるため
	ZdcEmapSearchShopStart();
	ZdcEmapMapObj.saveMapLocation();
}
//  add 2011/04/14 H.Osamoto
//検索決定(Myエリア用)
function ZdcEmapSearchSetMyarea(lat,lon,notmove) {
	ZdcEmapShopDetailClose();
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyArea"]; ?>","ZdcEmapSearchSet('"+lat+"','"+lon+"');");
	ZdcEmapHistorySave();
	//マップ移動
	ZdcEmapSearchEventStop();
	var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
	//ZdcEmapMapObj.setMapLocation(center);		2007/11/16 mod Y.Matsukawa
	if (!notmove) ZdcEmapMapObj.setMapLocation(center);
	if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
	//拠点検索
	ZdcEmapSearchFirst = 1;
	ZdcEmapSearchPoint = null;//必ず再検索させるため
	ZdcEmapSearchShopStart();
	ZdcEmapMapObj.saveMapLocation();
}

// add 2009/09/03 Y.Matsukawa
function ZdcEmapSearchSetFromWin(lat,lon,notmove,prm) {
	//検索ウィンドウからの場合、絞り込み条件を反映
	if(prm != undefined) {
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		if (prm) url = url + "&" + prm;
		url += "&<?php echo $P_FREEPARAMS; ?>";
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapCondObj.mode = "cond";
			ZdcEmapCondObj.style.visibility = "visible";
			//
			ZdcEmapShopDetailClose();
			ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["List"]; ?>","ZdcEmapSearchSet('"+lat+"','"+lon+"');");
			ZdcEmapHistorySave();
			//マップ移動
			ZdcEmapSearchEventStop();
			var center = new ZdcPoint(lon, lat, <?PHP echo $D_PFLG; ?>);
			if (!notmove) ZdcEmapMapObj.setMapLocation(center);
			if(<?PHP echo $D_INIT_LVL_SEARCH; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_SEARCH; ?>);
			//拠点検索
			ZdcEmapSearchFirst = 1;
			ZdcEmapSearchPoint = null;//必ず再検索させるため
			ZdcEmapSearchShopStart();
			ZdcEmapMapObj.saveMapLocation();
		});
	}
}
//路線図表示
//function ZdcEmapSearchRailwayDisp(mapNo,name,x,y){	mod 2008/04/21 Y.Matsukawa
function ZdcEmapSearchRailwayDisp(mapNo,name,x,y,prm){
	var tmp = "";
	if(name) tmp = "("+name+")";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Rail"]; ?>"+tmp,
	                  "ZdcEmapSearchRailwayDisp('"+mapNo+"','"+name+"',"+x+","+y+");");
	//路線図が変わらない場合実行しない ※履歴連打対策
	if(ZdcEmapRailMainObj) if(ZdcEmapRailMainObj.mapNo == mapNo) return;
	
	//検索ウィンドウからの場合、絞り込み条件を反映		add 2008/04/21 Y.Matsukawa
	if(prm != undefined) {
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		if (prm) url = url + "&" + prm;
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($https_req) && $https_req !=""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapCondObj.mode = "cond";
			ZdcEmapCondObj.style.visibility = "visible";
		});
	}

	//デザイン読み込み
	ZdcEmapSearchClear();
	//var url = "<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Rail&area="+mapNo;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Rail&area="+mapNo;
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if($P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req !=""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		
		ZdcEmapRailMainObj = document.getElementById('ZdcEmapSearchRailwayMain');
		ZdcEmapRailSubObj = document.getElementById('ZdcEmapSearchRailwaySub');
		//
		var opts = new ZdcSearchRailwayMapOptions();
		//路線図のパラメーター設定
		if (mapNo != undefined){
			opts.mapNo = parseInt(mapNo);
		}
		opts.x = x;
		opts.y = y;
		opts.callback = function(result) {
			//コールバック関数
			if( result.status == 0 ){
				//地図移動
				var lat;
				var lon;
				if (result.items[0].point != null){
					lat = result.items[0].point.my;
					lon = result.items[0].point.mx;
				} else {
					lat = result.items[0].lat;
					lon = result.items[0].lon;
				}
				ZdcEmapSearchSet(lat,lon);
			}
		}
		//路線図メインの表示設定
		if(ZdcEmapRailMainObj) {
			ZdcEmapRailway.addMainMap(ZdcEmapRailMainObj,opts);
			ZdcEmapRailMainObj.mapNo = mapNo;
			//路線図サブの表示設定
			if(ZdcEmapRailSubObj) {
				ZdcEmapRailway.addSubMap(ZdcEmapRailSubObj);
			}
		}
	});
}
//路線図閉じる
function ZdcEmapSearchRailwayRemove(){
	if(!ZdcEmapRailMainObj) return;
	//路線図を隠す
	ZdcEmapRailway.removeMainMap();
	delete ZdcEmapRailMainObj;
	ZdcEmapRailMainObj = null;
	ZdcEmapRailway.removeSubMap();
	if(ZdcEmapRailSubObj) {
		delete ZdcEmapRailSubObj;
		ZdcEmapRailSubObj = null;
	}
}
//地域図表示
//function ZdcEmapSearchAreaDisp(todCode,name){	mod 2008/04/21 Y.Matsukawa
function ZdcEmapSearchAreaDisp(todCode,name,prm){
	var tmp = "";
	if(name) tmp = "("+name+")";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Area"]; ?>"+tmp,
	                  "ZdcEmapSearchAreaDisp('"+todCode+"','"+name+"');");
	//都道府県が変わらない場合実行しない ※履歴連打対策
	if(ZdcEmapAreaObj) if(ZdcEmapAreaObj.todCode == todCode) return;

	//検索ウィンドウからの場合、絞り込み条件を反映		add 2008/04/21 Y.Matsukawa
	if(prm != undefined) {
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		if (prm) url = url + "&" + prm;
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapCondObj.mode = "cond";
			ZdcEmapCondObj.style.visibility = "visible";
		});
	}
	
	//デザイン読み込み
	ZdcEmapSearchClear();
	//var url = "<?PHP echo $D_DIR_BASE; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Area&area="+todCode;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>search.htm?cid=<?PHP echo $cid; ?>&type=Area&area="+todCode;
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if($P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		//
		var opts = new ZdcSearchMapOptions();
		//地域図のパラメーター設定
		if (todCode != undefined){
			opts.todCode = todCode;
		}
		opts.callback = function(result) {
			//コールバック関数
			if( result.status == 0 ){
				//地図移動
				var lat;
				var lon;
				if (result.items[0].point != null){
					lat = result.items[0].point.my;
					lon = result.items[0].point.mx;
				} else {
					lat = result.items[0].lat;
					lon = result.items[0].lon;
				}
				ZdcEmapSearchSet(lat,lon);
			}
		}
		//地域図の表示設定
		ZdcEmapAreaObj = document.getElementById('ZdcEmapSearchArea')
		if(ZdcEmapAreaObj) {
			ZdcEmapAreaObj.style.visibility = "visible";
			ZdcEmapArea.addMap(ZdcEmapAreaObj,opts);
			ZdcEmapAreaObj.style.zIndex = 99998;//最前面にもってくる
			ZdcEmapAreaObj.todCode = todCode;
		}
	});
}
//地域図閉じる
function ZdcEmapSearchAreaRemove(){
	if(!ZdcEmapAreaObj) return;
	//地域図を隠す
	ZdcEmapArea.removeMap();
	ZdcEmapAreaObj.style.visibility = "hidden";
	delete ZdcEmapAreaObj;
	ZdcEmapAreaObj = null;
}

// add 2011/04/14 H.Osamoto
//Myエリアリンク変更
function ZdcEmapMyAreaSetGlobal(prm1, prm2, prm3, prm4, prm5){
	MYAREA_SEL1 = prm1;
	MYAREA_SEL2 = prm2;
	MYAREA_SEL3 = prm3;
	MYAREA_SEL4 = prm4;
	MYAREA_SEL5 = prm5;
}

// add 2011/04/14 H.Osamoto
//ダミーパラメータ用タイムスタンプ取得
function getTimestamp(){
	var d = new Date();

	var ye = d.getUTCFullYear();
	var mo = zeroPlus(d.getUTCMonth() + 1);
	var da = zeroPlus(d.getUTCDate());
	var ho = zeroPlus(d.getUTCHours());
	var mi = zeroPlus(d.getUTCMinutes());
	var se = zeroPlus(d.getUTCSeconds());

	return ye + mo + da + ho + mi + se;
}

// add 2011/04/14 H.Osamoto
function zeroPlus(value){
	return ("0" + value).slice(-2);
}

// add 2011/04/14 H.Osamoto
// 地図中心緯度経度取得
function ZdcEmapGetMapCenter(){
	window.alert(aZdcPoint.my);
	window.alert(aZdcPoint.mx);
}

// add 2011/04/14 H.Osamoto
//Myエリア追加画面表示
function ZdcEmapMyAreaAddDisp(p_s2, myar, lm){
	//デザイン読み込み
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaAddDisp&corp_id="+"<?php echo $cid; ?>&user_id="+p_s2+"&myar="+myar+"&lm="+lm;
	// ダミーパラメータ
	damprm = getTimestamp();
	url += "&damprm="+damprm;
	
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if($P_FREEPARAMS) { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapMyareaWrapperObj.innerHTML = html;
		ZdcEmapMyareaWrapperObj.style.visibility = "visible";
		ZdcEmapMyareaWrapperObj.style.zIndex = 9995;
		ZdcEmapMyareaWrapperObj.style.display = "block";
		document.frmMyareaAdd.myarea_name_add.focus();
	});
}

// add 2011/04/14 H.Osamoto
//Myエリア追加
function ZdcEmapMyAreaAdd(p_s2, myarea_name, myar, lm, cnt){
	myarea_name = document.getElementById('myarea_name_add').value;
	if (myarea_name == "") {
		window.alert('Myエリア名称が未入力の為、登録できません。');
		ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
	} else if (myarea_name.length > 50) {
		window.alert('Myエリア名称の文字数が\n50文字を超えている為、登録できません。');
		ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
	} else if (!checkKeyword(myarea_name)) {
		window.alert('機種依存文字が含まれている為、登録できません。');
		ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
	} else {
		ret = window.confirm("「"+myarea_name+"」を登録しますか？");
		if (ret != true) {
			ZdcEmapMyAreaAddDisp(p_s2, myar, lm);
		} else {
			var encstr = EscapeEUCJP(myarea_name);
			var aZdcPoint = ZdcEmapMapObj.getMapLocation();
			lat = aZdcPoint.my;
			lon = aZdcPoint.mx;
			
			//デザイン読み込み
			ZdcEmapSearchClear();
			var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaAdd&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&myarea_name="+encstr+"&lat="+lat+"&lon="+lon+"&myar="+myar+"&lm="+lm;
			// ダミーパラメータ
			damprm = getTimestamp();
			url += "&damprm="+damprm;

			<?php //mod 2011/07/05 Y.Nakajima ?>
			<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS != "") { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
			<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
			ZdcEmapHttpRequestHtml(url, function(html,status){
				if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
				var tmp = html.split(",");
				if (tmp[0] == "ERR") {
					window.alert(tmp[1]);
				}
				ZdcEmapMyareaWrapperObj.style.zIndex = -1;
				if (html == "登録が完了致しました。"){
					var disp_url = "../../pc/index.htm?cid=<?php echo $cid; ?>&myar=e&p_s2="+p_s2+"&lm="+lm+"&myardisp=1&lat="+lat+"&lon="+lon+"&area_no="+cnt;
					comitMyareaAdd("<?PHP echo $D_DIR_BASE_G; ?>company/<?php echo $cid; ?>/", 1, disp_url);
				} else {
					comitMyareaAdd("<?PHP echo $D_DIR_BASE_G; ?>company/<?php echo $cid; ?>/", 0, "");
				}
			});
		}
	}
}

// add 2011/04/14 H.Osamoto
//Myエリア編集画面表示
function ZdcEmapMyAreaEditDisp(p_s2, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaEditDisp('"+"<?PHP echo $cid; ?>"+"','"+p_s2+"');");
	//デザイン読み込み
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaSel&corp_id="+"<?php echo $cid; ?>&user_id="+p_s2+"&myar="+myar+"&lm="+lm;
	// ダミーパラメータ
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS != "") { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
	});
}

// add 2011/04/14 H.Osamoto
//Myエリア名称変更
function ZdcEmapMyAreaNameUpdt(myarea_id, p_s2, myarea_name, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaNameUpdt('"+"<?PHP echo $cid; ?>"+"','"+myarea_id+"','"+myarea_name+"');");
	//デザイン読み込み
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaNameUpdt&myarea_id="+myarea_id+"&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&myarea_name="+myarea_name+"&myar="+myar+"&lm="+lm;
	// ダミーパラメータ
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS != "") { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		
		var tmp = html.split(",");
		if (tmp[0] == "ERR") {
			window.alert(tmp[1]);
			ZdcEmapMyAreaEditDisp(p_s2, myar, lm);
		} else {
			ZdcEmapSearchWindowObj.innerHTML = html;
			ZdcEmapSearchWindowObj.style.visibility = "visible";
			if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
		}
	});
}

// add 2011/04/14 H.Osamoto
//Myエリア表示順序変更
function ZdcEmapMyAreaOrderUpdt(myarea_id, corp_id, p_s2, disp_order, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaNameUpdt('"+"<?PHP echo $cid; ?>"+"','"+myarea_id+"','"+corp_id+"','"+disp_order+"');");
	//デザイン読み込み
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaOrderUpdt&myarea_id="+myarea_id+"&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&disp_order="+disp_order+"&myar="+myar+"&lm="+lm;
	// ダミーパラメータ
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS != "") { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
	});
}

// add 2011/04/14 H.Osamoto
//Myエリア削除
function ZdcEmapMyAreaDelete(myarea_id, corp_id, p_s2, myar, lm){
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["MyAreaEdit"]; ?>",
	                  "ZdcEmapMyAreaDelete('"+"<?PHP echo $cid; ?>"+"','"+myarea_id+"','"+corp_id+"','"+p_s2+"');");
	//デザイン読み込み
	ZdcEmapSearchClear();
	var url = "<?PHP echo $D_DIR_BASE_L; ?>myarea.htm?cid=<?PHP echo $cid; ?>&type=MyAreaDel&myarea_id="+myarea_id+"&corp_id=<?php echo $cid; ?>&user_id="+p_s2+"&myar="+myar+"&lm="+lm;
	// ダミーパラメータ
	damprm = getTimestamp();
	url += "&damprm="+damprm;

	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($P_FREEPARAMS) && $P_FREEPARAMS != "") { ?>url += "&<?php echo $P_FREEPARAMS; ?>";<?php } 		// add 2010/05/19 Y.Matsukawa ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> search["+status+"]";
		ZdcEmapSearchWindowObj.innerHTML = html;
		ZdcEmapSearchWindowObj.style.visibility = "visible";
		if(ZdcEmapIE6HideSelectObj) ZdcEmapIE6HideSelectObj.style.visibility = "visible";// add 2008/05/07 Y.Matsukawa
	});
}

// add 2011/04/14 H.Osamoto
//Myエリア名称エラーダイアログ表示（機種依存文字）
function ZdcEmapMyAreaShowErrDialog(message){
	window.alert(message);
}

//-------------------------------------------------------------
//周辺検索関係
//-------------------------------------------------------------
<?php if(isset($D_REQ_JSAPI["npoi"]) && $D_REQ_JSAPI["npoi"]){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapNpoi = new ZdcNearPoi();
ZdcEvent.addListener(ZdcEmapNpoi, "end", ZdcEmapPoiResult);
<?php } ?>
//クリックイベント
function ZdcEmapPoiClick(mode) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapPoiRouteClear();
	ZdcEmapSearchEventStop();
	ZdcEmapShopMsgClose();
	//画面を切り替える
	if(ZdcEmapCondObj.mode != "jnr") {
		ZdcEmapSearchShopClose();
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_jnr.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_jnr.htm?cid=<?PHP echo $cid; ?>";
		<?php //mod 2011/07/05 Y.Nakajima ?>
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> jnr["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapSearchNpoi(mode);
		});
		//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Npoi"]; ?>","");		mod 2010/06/16 Y.Matsukawa
		if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Npoi"]; ?>","");
			else ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Npoi"]; ?>","");
		ZdcEmapHistorySave();
		ZdcEmapCondObj.mode = "jnr";
		ZdcEmapCondObj.style.visibility = "visible";
	} else {
		ZdcEmapSearchNpoi(mode);
	}
}
//検索開始
function ZdcEmapSearchNpoi(mode) {
	ZdcEmapReadOn();
	
	var p   = new ZdcPoint();
	p = ZdcEmapMapObj.getMapLocation();
	
	//検索条件取得
	var code="";
	if(document.ZdcEmapJnrForm) {
		var obj,jnr=new Array(),jnrcnt=0;
		for(var i = 0;i < document.ZdcEmapJnrForm.elements.length;i ++) {
			obj = document.ZdcEmapJnrForm.elements[i];
			if(!obj) break;
			switch(obj.type) {
				case "checkbox":
					if(obj.checked == true) {
						jnr[jnrcnt] = obj.value;
						jnrcnt ++;
					}
					break;
				case "select-one":
					if(obj.options[obj.selectedIndex].value) {
						jnr[jnrcnt] = obj.options[obj.selectedIndex].value;
						jnrcnt ++;
					}
					break;
				case "radio":
					if(obj.checked == true && obj.value) {
						jnr[jnrcnt] = obj.value;
						jnrcnt ++;
					}
					break;
				default:
					if(obj.value) {
						jnr[jnrcnt] = obj.value;
						jnrcnt ++;
					}
					break;
			}
		}
		for(var i = 0;i < jnrcnt;i ++) {
			if(code) code += ",";
			code += jnr[i];
		}
	}
	if(!code) code = '<?PHP echo $D_POI_JNRMN; ?>';//デフォルトジャンル
	//検索範囲の計算
	var rad = 0;
	if(mode == 0) {
		//地図内検索
		var box = ZdcEmapMapObj.getMapBoundBox();
		if((box.maxx - box.minx) > (box.maxy - box.miny)) {
			//横幅をとる
			var p1 = new ZdcPoint(box.maxx,box.maxy,<?PHP echo $D_PFLG; ?>);
			var p2 = new ZdcPoint(box.minx,box.maxy,<?PHP echo $D_PFLG; ?>);
		} else {
			//縦幅をとる
			var p1 = new ZdcPoint(box.maxx,box.maxy,<?PHP echo $D_PFLG; ?>);
			var p2 = new ZdcPoint(box.maxx,box.miny,<?PHP echo $D_PFLG; ?>);
		}
		rad = parseInt(ZdcEmapGeometricObj.getPoint2PointDistance(p1,p2) / 2.1);//地図範囲ギリギリを対象としないよう2.1と少し丸める
	} else {
		//最寄検索
		rad = <?PHP echo $D_POI_RAD; ?>;
	}
	if (rad > <?PHP echo $API_RAD_MAX; ?>) rad = <?PHP echo $API_RAD_MAX; ?>;//最寄り検索APIの半径指定上限値を超えている場合は上限値で検索
	//
	var opts = new ZdcNearPoiOptions();
	opts.startPos = 1;
	opts.maxCount =  <?PHP echo $D_POI_MAX; ?>;
	opts.genreMenuCode = code;
	<?php //mod 2011/07/05 Y.Nakajima ?>
	opts.genreCode = '<?PHP if (isset($D_POI_JNR)) echo $D_POI_JNR;?>';
	opts.lat = p.my;
	opts.lon = p.mx;
	opts.limitCount = <?PHP echo $D_POI_MAX; ?>;
	opts.radius = rad;
	opts.pointFlg = <?PHP echo $D_PFLG; ?>;
	opts.lang = '<?PHP echo $D_POI_LANG; ?>';	// add 2008/08/22 Y.Matsukawa
	ZdcEmapNpoi.opts = opts;
	
	if(opts.genreMenuCode) {
		//ジャンルの指定があった時のみ検索させる
		ZdcEmapPoiList(0);
		ZdcEmapNpoi.search(opts);
	}
	
}
//検索処理
function ZdcEmapPoiResult(result) {
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//エラー処理
	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> poires["+result.status+"]");
		ZdcEmapListObj.innerHTML = "";
		ZdcEmapReadOff();
		return;
	}
	//地図に置く
	var i,p,mrk,titlelink,title,item,maxlat=0,maxlon=0,minlat=999999999,minlon=999999999;;
	var icon = new ZdcIcon();
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//マーカー削除
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapMapPoiMrkCnt = 0;
	for( i in result.items ){
		item = result.items[i];
		//アイコンの作成
		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
		                     <?PHP echo $D_ICON_POI_W; ?>,<?PHP echo $D_ICON_POI_H; ?>,0,0,
		                     <?PHP echo $D_ICON_POI_OFFSET_X; ?>,<?PHP echo $D_ICON_POI_OFFSET_Y; ?>,0,0,0,0,
		                     '<?PHP echo $D_ICON_POI_IMAGE_DIR; ?>'+item.genreMenuCode+'.gif',item.icons,
		                     item.poiName,"",0,
		                     null,function() { ZdcEmapTipsClick(this.id); },null);
		if (ZdcEmapMapPoiMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//念のため
		ZdcEmapMapPoiMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);
		//最大最小緯度経度取得
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		ZdcEmapMapPoiMrkCnt ++;
	}
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	//自動縮尺変更
	ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,ZdcEmapMapObj.getMapLocation());
	ZdcEmapReadOff();
}
//リスト表示
function ZdcEmapPoiListClick(page) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapPoiList(page)
}
function ZdcEmapPoiList(page) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_npoi.htm?cid=<?PHP echo $cid; ?>"+		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_npoi.htm?cid=<?PHP echo $cid; ?>"+
		      "&jnrmn="+ZdcEmapNpoi.opts.genreMenuCode+"&jnr="+ZdcEmapNpoi.opts.genreCode+
		      "&lat="+ZdcEmapNpoi.opts.lat+"&lon="+ZdcEmapNpoi.opts.lon+"&radius="+ZdcEmapNpoi.opts.radius+"&page="+page;
	<?php if($https_req){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> poi["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}

// add 2008/04/21 Y.Matsukawa
//-------------------------------------------------------------
// 検索ウィンドウ用
//-------------------------------------------------------------
<?php //function ZdcEmapGetSearchTopCond(prefix, suffix) {		mod 2016/02/20 Y.Matsukawa ?>
function ZdcEmapGetSearchTopCond(prefix, suffix, ids) {
	var condStr = '';
	if (!prefix) prefix = '';
	if (!suffix) suffix = '';
	if (!ids) ids = "scond";	<?php // add 2016/02/20 Y.Matsukawa ?>
	//for(i = 1;i <= 50;i ++) {		mod 2009/11/07 Y.Matsukawa
	for(i = 1;i <= 200;i ++) {
		<?php //var cond = document.getElementById("scond"+i);	mod 2016/02/20 Y.Matsukawa ?>
		var cond = document.getElementById(ids+i);
		if (cond) {
			v = '';
			if (cond.type == "checkbox") {
				if (cond.checked == true) {
					v = '1';
				}
			} else if (cond.type == "select-one") {
				if (cond.options[cond.selectedIndex].value) {
					v = cond.options[cond.selectedIndex].value;
				}
			} else if (cond.type == "radio") {
				if (cond.checked == true) {
					v = cond.value;
				}
			// add 2009/03/13 Y.Matsukawa [
			} else if (cond.type == "hidden") {
				v = cond.value;
			// add 2009/03/13 Y.Matsukawa ]
			}
			if (v) {
				if (condStr) condStr += "&";
				condStr += "cond"+i+"="+v;
			}
		}
	}
	if (condStr) condStr = prefix+condStr+suffix;
	return condStr;
}

// add 2010/05/11 Y.Matsukawa
//-------------------------------------------------------------
// 地図画面のcondを検索ウィンドウcondに反映
//-------------------------------------------------------------
function ZdcEmapCond2SearchTopCond() {
	if(document.ZdcEmapCondForm) {
		var obj,scond,idx;
		for(var i = 0;i < document.ZdcEmapCondForm.elements.length;i ++) {
			obj = document.ZdcEmapCondForm.elements[i];
			if (obj) {
				idx = obj.name.replace("cond","");
				scond = document.getElementById("scond"+idx);
				if(scond) {
					switch(obj.type) {
						case "checkbox":
							if (scond.type == "checkbox") scond.checked = obj.checked;
							break;
						case "select-one":
							//
							break;
						case "radio":
							//
							break;
						case "text":
							//
							break;
						case "hidden":
							if (scond.type == "checkbox") {
								if(obj.value) scond.checked = true;
								else scond.checked = false;
							}
							break;
						default:
							break;
					}
				}
			}
		}
	}
}

// add 2010/05/11 Y.Matsukawa
//-------------------------------------------------------------
// cond書き換え
//-------------------------------------------------------------
function ZdcEmapChangeCond(prm) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
	if (prm) url = url + "&" + prm;
	url += "&<?php echo $P_FREEPARAMS; ?>";
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
	<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
		ZdcEmapCondObj.innerHTML = html;
	});
}

// add 2010/05/11 Y.Matsukawa
//-------------------------------------------------------------
// 検索ウィンドウcondを地図画面のcondに反映
//-------------------------------------------------------------
function ZdcEmapSearchTopCond2Cond() {
	// 検索ウィンドウcondから取得
	var prm = ZdcEmapGetSearchTopCond();
	// パラメータで渡されたcondを取得
	var p_cond = "";
<?php
	for($i = 1;$i <= 200;$i ++) {
		//mod 2011/07/05 Y.Nakajima
		if(isset($_VARS["cond".$i])) {
?>
			if (prm.indexOf("<?php echo 'cond'.$i.'='; ?>") < 0) {
				if(p_cond) p_cond += "&";
				p_cond += "<?php echo 'cond'.$i.'='.$_VARS['cond'.$i]; ?>";
			}
<?php
		}
	}
?>
	if (prm && p_cond) p_cond += "&";
	ZdcEmapChangeCond(p_cond + prm);
}

// add 2011/08/10 K.masuda [
//-------------------------------------------------------------
// 地図なし拠点リストから再検索
//-------------------------------------------------------------
<?php //function ZdcEmapReSearchCondList(){		mod 2016/02/20 Y.Matsukawa ?>
function ZdcEmapReSearchCondList(ids){
    <?php //var prm = ZdcEmapGetSearchTopCond();		mod 2016/02/20 Y.Matsukawa ?>
    var prm = ZdcEmapGetSearchTopCond("", "", ids);
	var nprm = "";
	var inprm = SrchWin_prm.split("&");
	for(var j=0;j<inprm.length;j++){
		if( inprm[j].indexOf("cond") != 0){
			nprm += inprm[j] + "&";
		}
	}
	nprm += prm;
	nprm = nprm.replace(/&+$/g, "");	// 末尾の&を取る
	ReSearchFlg = 1;	// 再検索フラグON（パンくずを更新しないため）
	ZdcEmapSearchOpenFromSrchWin(SrchWin_type,nprm+"&reflg=1",SrchWin_name);
}
// add 2011/08/10 K.masuda ]

// add 2011/02/16 Y.Matsukawa
//-------------------------------------------------------------
// 出発地指定ルートの入力初期値をセット
//-------------------------------------------------------------
var ZdcEmapFRouteInitStr = null;
function ZdcEmapSetFRouteInit(str) {
	ZdcEmapFRouteInitStr = str;
}

// add 2011/04/14 H.Osamoto
//-------------------------------------------------------------
// 機種依存文字チェック
//-------------------------------------------------------------
function checkKeyword(str){
	var str_length = str.length;
	var code, scode;

	for (var i = 0; i < str_length; i++) {
		code = str.charCodeAt(i);
		code = code.toString(16);
		
		//4桁以下なら先頭に0を追加
		if(code.length < 4){
			var figure = 4 - code.length;
			var rcode = "";
			for(var fi = 0; fi < figure; fi++){
				rcode += "0";
				if(rcode.length > figure){
					rcode = rcode.slice(0,figure);
					break;
				}
			}
			code = rcode + code;
		}

		//範囲チェック＆改行コードとタブコードチェック
		if(!(0x20 <= "0x"+code && 0x7e >= "0x"+code) && 
			code != "000a" && code != "000d" && code != "0009"){
			if(code.charAt(0) == "0" || ( code.charAt(0) >= "2" && 
				code.charAt(0) <= "9" ) || code.charAt(0) == "f"){
				scode = code.substring(1,4);
				if(eval("u"+code.charAt(0)+"a").indexOf(":"+scode) == -1){
					return false;
				}
			}else{
				return false;
			}
		}
	}
	return true;
}

// add 2012/03/19 K.Masuda [
//-------------------------------------------------------------
// 検索位置にアイコン表示
//-------------------------------------------------------------
var	ZdcEmapIconLayer;
function ZdcEmapSearchMapIcon() {
	// 古いアイコン削除
	if(ZdcEmapIconLayer){ZdcEmapMapObj.removeUserLayer(ZdcEmapIconLayer);}
	//アイコン表示位置設定
	var p = new ZdcPoint();
	p = ZdcEmapMapObj.getMapLocation();
	ZdcEmapIconPoint = new ZdcPoint(p.mx, p.my, 2);
	//ユーザレイヤー作成
	ZdcEmapIconLayer = new ZdcUserLayer();
	ZdcEmapIconLayer.setLayerScale(1, 18);
	//アイコン作成
	ZdcEmapIcon1 = new ZdcIcon();
	ZdcEmapIcon1.offset = new ZdcPixel(<?PHP echo ceil(- $D_ICON_SHOP_W / 2); ?>, <?PHP echo ceil(- $D_ICON_SHOP_H / 2); ?>);
	ZdcEmapIcon1.image = '<?PHP echo $D_ICON_SHOP_IMG; ?>';
	//ユーザレイヤーに追加
	ZdcEmapIconLayer.addMarker(new ZdcMarker(ZdcEmapIconPoint, ZdcEmapIcon1));
	//地図にユーザレイヤーを追加
	ZdcEmapMapObj.addUserLayer(ZdcEmapIconLayer);
}
// add 2012/03/19 K.Masuda ]

