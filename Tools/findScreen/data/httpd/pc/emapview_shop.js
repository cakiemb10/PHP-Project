<?PHP
// ------------------------------------------------------------
// 地図制御javasctipt 主に拠点検索に関係するもの
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2007/11/16 Y.Matsukawa	初期表示時に地図APIのChangeLocationイベントが３回発生する→２回に減らす
// 2007/11/28 Y.Matsukawa	吹き出しを表示した状態で最寄駅検索を実行すると、ルートが表示されなくなる不具合を修正
// 2008/08/22 Y.Matsukawa	英字対応
// 2008/10/15 Y.Matsukawa	【不具合改修】周辺拠点非表示設定なのに、吹き出し拠点名クリックで詳細表示後、地図移動すると周辺拠点が表示されてしまう
//                          【不具合改修】周辺拠点非表示設定の場合、最寄駅表示からパンくずで詳細表示へ戻った時、駅アイコンが消えない（最寄施設も同様）
// 2008/10/22 Y.Matsukawa	使用しないJSはロードしない
// 2009/02/06 Y.Matsukawa	拠点FWによる拠点絞り込み
// 2009/02/16 Y.Matsukawa	【不具合改修】（FFのみ）アイコンマウスインで吹き出し表示の場合：地図中心のアイコン上にマウスを置いていると、吹き出しが表示／非表示を繰り返す
//                          （waitメッセージが表示→非表示されると、その度にマウスインイベントが発生するようなので、吹き出しではwaitメッセージは出さないようにする）
// 2009/02/23 Y.Matsukawa	拠点詳細に自由項目パラメータを引き渡す
// 2009/03/06 Y.Matsukawa	拠点リストに自由項目パラメータを引き渡す
// 2009/03/17 Y.Matsukawa	吹き出しに自由項目パラメータを引き渡す
// 2009/03/26 Y.Matsukawa	絞込み画面へ自由項目パラメータを引き渡す
// 2009/08/18 Y.Matsukawa	拠点アイコンプロット順を変更（近いものを上に）
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2009/09/28 Y.Matsukawa	拠点詳細テンプレート内の<script>タグを実行
// 2009/10/13 Y.Matsukawa	最寄り拠点一覧に詳細拠点を出さない
// 2009/11/07 Y.Matsukawa	拠点項目拡張（50→200）
// 2009/12/10 Y.Matsukawa	詳細テンプレートにcondを渡す
// 2010/01/27 Y.Matsukawa	絞り込みテンプレートに都道府県コードを渡す
// 2010/04/23 Y.Matsukawa	【不具合修正】最寄り拠点アイコンを表示しない設定の場合、最寄り拠点一覧から詳細表示した際に点滅フレームが消えなくなる
// 2010/05/21 Y.Matsukawa	【不具合修正】詳細拠点を最寄りに出さない設定の時、詳細表示時に最寄りゼロだと縮尺が引いてしまう
// 2010/06/16 Y.Matsukawa	出発地を指定してルート探索
// 2010/07/20 Y.Matsukawa	SSL対応
// 2010/09/07 Y.Matsukawa	出発地を指定してルート探索（Light、Maplink）
// 2010/09/13 Y.Matsukawa	拠点詳細表示時に拠点IDをCookie保存
// 2010/11/15 Y.Matsukawa	condグルーピング
// 2011/02/09 Y.Matsukawa	内部アクセスをドメインから内部IPに変更
// 2011/02/16 Y.Matsukawa	検索結果住所一覧で選択した住所を、出発地指定ルートの入力初期値にする
// 2011/04/27 H.Osamoto		Newアイコン判定カラムの追加
// 2011/05/26 K.Masuda		cond情報の更新
// 2011/06/15 K.Masuda		フキダシ表示中でも再検索できるようにする
// 2011/06/16 Y.Matsukawa	詳細更新時にJS実行
// 2011/06/27 H.osamoto		最寄駅、ルート探索時に実行する前処理を追加
// 2011/06/29 K.Masuda		initlat、initlonで地図の表示初期位置を設定（アイコン設定時地図移動しない）
// 2011/07/06 K.Masuda		吹き出し表示時、地図内に収まらないとき地図移動するか
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2011/07/19 K.Masuda		重なりアイコンの処理を追加
// 2011/08/23 Y.Matsukawa	地図非表示拠点
// 2011/11/25 Y.Matsukawa	ピーシーデポ対応（最寄りルート専用モード）
// 2012/06/19 Y.Matsukawa	店舗詳細Cookie保存機能追加（任意タイミングの保存、クリア、取得関数）
// 2012/06/22 Y.Matsukawa	【不具合修正】Cookieクリア後の保存でスクリプトエラー
// 2012/10/09 Y.Matsukawa	店舗詳細遷移時のカスタマイズ関数実行
// 2013/03/10 K.Masuda		condがtype=textの場合、FREE_SRCH以外の指定を可能にする
// 2013/04/15 H.Osamoto		最寄検索結果が0件の場合再検索で取得する件数指定機能追加
// 2015/03/23 K.Iwayoshi	三井住友銀行来店予約対応カスタマイズ
// 2016/02/15 Y.Uesugi		三井住友銀行来店予約対応カスタマイズ（詳細画面で絞り込み非表示）
// 2016/02/18 Y.Matsukawa	最寄り検索にだけ適用するcond／拠点エリア検索にだけ適用するcond
// ------------------------------------------------------------
include("./inc/define.inc");  // 基本設定
?>
<?php
// add 2010/11/15 Y.Matsukawa [
//-------------------------------------------------------------
// condグルーピング定義
// ZdcEmapCondGroup[cond番号] = グループ番号(1〜n);
//-------------------------------------------------------------
?>
var ZdcEmapCondGroup = new Array();
var ZdcEmapCondAndOr = new Array();
<?php
// mod 2011/07/05 Y.Nakajima
if (isset($D_COND_GRP) && is_array($D_COND_GRP) && count($D_COND_GRP)) {
	foreach ($D_COND_GRP as $g => $grp) {
?>
ZdcEmapCondAndOr[<?php echo $g ?>] = '<?php echo $D_COND_ANDOR[$g] ?>';
<?php
		foreach ($grp as $cnd) {
?>
ZdcEmapCondGroup[<?php echo $cnd ?>] = <?php echo $g ?>;
<?php
		}
	}
}
// add 2010/11/15 Y.Matsukawa ]
?>
//-------------------------------------------------------------
//拠点検索関係
//-------------------------------------------------------------
var ZdcEmapSearchPoint = null;//検索した位置を保持
var ZdcEmapSearchScale = null;//検索した縮尺を保持
var ZdcEmapSearchFirst = null;//位置決定後の最初の検索か否か
var ZdcEmapIconDt = new Array();	// add 2011/07/19 K.Masuda
var ZdcEmapNearbyShopItem = null;	<?php //最寄り店舗情報	add 2011/11/25 Y.Matsukawa ?>
var ZdcEmapSearchFirstCstm = null;	<?php //最初の検索か否かカスタマイズ用フラグ	// add 2013/04/15 H.osamoto ?>
//検索開始
function ZdcEmapSearchShopClick() {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchPoint = null;//必ず再検索させるため
	ZdcEmapSearchShop();
}
<?php // ルート探索モード時の最寄り店舗再検索		add 2011/11/25 Y.Matsukawa ?>
function ZdcEmapFixRouteSearchShopClick() {
	ZdcEmapSearchSet(ZdcEmapRouteStartLat, ZdcEmapRouteStartLon);
}
function ZdcEmapSearchShopStart() {
	if(ZdcEmapMapObj.ZdcEmapMode != "print") ZdcEmapSearchClickFlg = 1;
	ZdcEmapSearchPoint = null;//必ず再検索させるため
	//
	<?php if (!isset($D_ROUTE_FIX_MODE) || !$D_ROUTE_FIX_MODE) {	// add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapSearchEventAdd("ZdcEmapSearchShop()");
	<?php } ?>
	ZdcEmapSearchEventStart();
	//拠点以外のアイコンをクリア
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapMapPoiMrkCnt = 0;

	//画面を切り替える
	if(ZdcEmapCondObj.mode != "cond") {
		ZdcEmapSearchShopClose();//拠点以外のリストを消す
		//		var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>&";
		//		for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "cond"+i+"="+ZdcEmapSaveCond[i]+"&";//絞込条件
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_cond.htm?cid=<?PHP echo $cid; ?>";
		//for(i = 0;i < 50;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//絞込条件		mod 2009/11/07 Y.Matsukawa
		for(i = 1;i <= 200;i ++) if(ZdcEmapSaveCond[i]) url = url + "&cond"+i+"="+ZdcEmapSaveCond[i];//絞込条件
		url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/26 Y.Matsukawa
		<?php // add 2010/01/27 Y.Matsukawa [ ?>
		<?php //mod 2011/07/05 Y.Nakajima [ ?>
		<?php if(isset($adcd) && $adcd!=""){ ?>url += "&adcd=<?php echo $adcd; ?>";<?php } ?>
		<?php if(isset($area) && $area!=""){ ?>url += "&area=<?php echo $area; ?>";<?php } ?>
		<?php // add 2010/01/27 Y.Matsukawa ] ?>
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		<?php //mod 2011/07/05 Y.Nakajima ] ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> cond["+status+"]";
			ZdcEmapCondObj.innerHTML = html;
			ZdcEmapSearchShop();//条件部が表示されてから検索開始
		});
		ZdcEmapCondObj.mode = "cond";
		ZdcEmapCondObj.style.visibility = "visible";
	} else {
		ZdcEmapSearchShop();
	}
}
//検索メイン処理
function ZdcEmapSearchShop() {
	ZdcEmapReadOn();
	//位置・範囲取得
	var p   = new ZdcPoint();
	p = ZdcEmapMapObj.getMapLocation();
	var box = ZdcEmapMapObj.getMapBoundBox();
	//検索するか否かの判断
	if(ZdcEmapSearchPoint != null) {
		var pix1 = ZdcEmapMapObj.convertPoint2Pixel( ZdcEmapSearchPoint, 2 );
		var pix2 = ZdcEmapMapObj.convertPoint2Pixel( p, 2 );
		if(Math.abs(pix1.x-pix2.x) < <?PHP echo $D_SHOP_SEARCHPIX; ?> && 
		   Math.abs(pix1.y-pix2.y) < <?PHP echo $D_SHOP_SEARCHPIX; ?> &&
		   ZdcEmapSearchScale == ZdcEmapMapObj.getMapScale()) {
			ZdcEmapReadOff();
			return;
		}
	}
	if(ZdcEmapSearchPoint != null && <?PHP echo $D_SHOP_SEARCHPIX; ?> == -1) {
		//自動再検索しない
		ZdcEmapReadOff();
		return;
	}
	//自動検索イベント停止
	ZdcEmapSearchEventStop();
	// 2011/06/15 K.Masuda mod [
	//ZdcEmapShopMsgClose();
	<?php //mod 2011/07/05 Y.Nakajima ?>
	if( <?php if(isset($D_HUKIDASHI_SEARCH)){echo "false";}else{echo "true";} ?> ){
		ZdcEmapShopMsgClose();
	}
	// 2011/06/15 K.Masuda mod ]
	//絞り込み条件取得
	cond = ZdcEmapGetCond();
	//
	var opts = new ZdcNearShopOptions();
	<?php //mod 2011/07/05 Y.Nakajima ] ?>
	opts.cid='<?PHP echo $D_CID; ?>';
	opts.lat = p.my;
	opts.lon = p.mx;
	if(ZdcEmapSearchFirst != 1) {
		opts.latlon = box.miny+","+box.minx+","+box.maxy+","+box.maxx;
		opts.radius = <?PHP echo $D_SHOP_RAD_RE; ?>;
	} else {
		ZdcEmapSearchFirst = 0;
	<?php // add 2013/04/15 H.Osamoto [ ?>
	<?php if (isset($D_RESEARCH_CNT) && $D_RESEARCH_CNT) { ?>
	ZdcEmapSearchFirstCstm = 1;
	opts.researchCount = <?PHP echo $D_RESEARCH_CNT; ?>;
	<?php } ?>
	<?php // add 2013/04/15 H.Osamoto ] ?>
		opts.radius = <?PHP echo $D_SHOP_RAD; ?>;
	}
	<?php
	// add 2016/02/18 Y.Matsukawa [
	if ($D_N_COND != "") { ?>
	if (cond) {
		cond = "("+cond+") AND <?php echo $D_N_COND; ?>";
	} else {
		cond = "<?php echo $D_N_COND; ?>";
	}
	<?php
	}
	// add 2016/02/18 Y.Matsukawa ] ?>
	opts.jkn = cond;
	opts.pos = 1;
	opts.maxCount = <?PHP echo $D_SHOP_MAX; ?>;
	opts.limitCount = <?PHP echo $D_SHOP_MAX; ?>;
	opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
	// add 2009/10/13 Y.Matsukawa [
	<?PHP if ($D_SHOP_LIST_NO_DTLSHOP) { ?>
	if (ZdcEmapMapShopDetailMrkId != null) {
		// 詳細表示中の拠点ID
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		if (mrk && mrk.data1) opts.exceptKid = mrk.data1;
	}
	<?PHP } ?>
	// add 2009/10/13 Y.Matsukawa ]
	ZdcEmapNearShop.opts = opts;
	
	//リストを表示する
	ZdcEmapSearchShopList(0);

	//アイコンを表示する
	ZdcEmapNearShop.search(opts,ZdcEmapSearchShopResult);
}
//絞り混み条件組み立て
function ZdcEmapGetCond() {
	var cond="";
	var condArr=new Array();	<?php // add 2010/11/15 Y.Matsukawa ?>
	if(document.ZdcEmapCondForm) {
		//var obj,chk=new Array(),chkcnt=0,col=new Array(),colcnt=0;	mod 2009/02/06 Y.Matsukawa
		var obj,chk=new Array(),chkcnt=0,col=new Array(),colcnt=0,fw=new Array(),fwcnt=0;
		var all=new Array(),allcnt=0,allcondno=new Array(),condno='';	<?php // add 2010/11/15 Y.Matsukawa ?>
		for(var i = 0;i < document.ZdcEmapCondForm.elements.length;i ++) {
			obj = document.ZdcEmapCondForm.elements[i];
			if(!obj) break;
			condno = obj.name.replace('cond','');	<?php // add 2010/11/15 Y.Matsukawa ?>
			switch(obj.type) {
				case "checkbox":
					if(obj.checked == true) {
						chk[chkcnt] = obj.value;
						all[allcnt] = chk[chkcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						chkcnt ++;
					}
					break;
				case "select-one":
					if(obj.options[obj.selectedIndex].value) {
						col[colcnt] = obj.options[obj.selectedIndex].value;
						all[allcnt] = col[colcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						colcnt ++;
					}
					break;
				case "radio":
					if(obj.checked == true && obj.value) {
						col[colcnt] = obj.value;
						all[allcnt] = col[colcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						colcnt ++;
					}
					break;
				// add 2009/02/06 Y.Matsukawa [
				case "text":
					if(obj.value) {
						//fw[fwcnt] = "FREE_SRCH:FW:"+"'"+urlencode(obj.value)+"'";
						// mod 2013/03/10 K.Masuda [
						//fw[fwcnt] = "FREE_SRCH:FW:"+"'"+obj.value+"'";
						//all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						//fwcnt ++;
						<?php if(isset($D_COND_TEXT) && $D_COND_TEXT){ ?>
						<?php   for($cnt=0;$cnt<count($D_COND_TEXT);$cnt++){ ?>
									if(condno == <?php echo $D_COND_TEXT[$cnt][0]; ?>){
										fw[fwcnt] = <?php echo $D_COND_TEXT[$cnt][1]; ?>;
										all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
										fwcnt ++;
									}
						<?php   } ?>
						<?php } else { ?>
								fw[fwcnt] = "FREE_SRCH:FW:"+"'"+obj.value+"'";
								all[allcnt] = fw[fwcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
								fwcnt ++;
						<?php } ?>
						// mod 2013/03/10 K.Masuda ]
					}
					break;
				case "button":
					break;
				// add 2009/02/06 Y.Matsukawa ]
				default:
					if(obj.value) {
						col[colcnt] = obj.value;
						all[allcnt] = col[colcnt]; allcondno[allcnt] = condno; allcnt++;	<?php // add 2010/11/15 Y.Matsukawa ?>
						colcnt ++;
					}
					break;
			}
		}

		<?php // add 2011/05/26 K.Mausda [ ?>
		var cno,newcond = "",newqs = "";
		var qstr = QSTRING.split('&');
		for(var i=0; i<allcnt; i++) {
			cno = allcondno[i];
			newcond += "cond"+cno+"=1&";
		}
		for(var q=0; q<qstr.length; q++) {
			if( qstr[q] == '' ) continue;
			if( qstr[q].substr(0,4) != 'cond' ){
				newqs += qstr[q]+"&";
			}
		}
		QSTRING = newqs + newcond;
		<?php // add 2011/05/26 K.Mausda ] ?>

		<?php // add 2010/11/15 Y.Matsukawa [ ?>
		// グルーピング設定されている場合
		if (ZdcEmapCondGroup.length > 0) {
			for(var i = 0;i < allcnt;i ++) {
				cn = allcondno[i];
				gr = ZdcEmapCondGroup[cn];
				if (gr != undefined) {
					if(!condArr[gr]) condArr[gr] = '';
					if(condArr[gr]) condArr[gr] += ' '+ZdcEmapCondAndOr[gr]+' ';
					condArr[gr] += all[i];
				}
			}
			if(condArr.length > 0) {
<?php
//mod 2011/07/05 Y.Nakajima
if (isset($D_COND_GRP) && is_array($D_COND_GRP) && count($D_COND_GRP)) {
	foreach ($D_COND_GRP as $g => $grp) {
?>
				if(condArr[<?php echo $g ?>]) {
					if(cond) cond += ' <?PHP echo $D_COND_GRP_ANDOR; ?> ';
					cond += '('+condArr[<?php echo $g ?>]+')';
				}
<?php
	}
}
?>
			}
		// グルーピング設定なし（既存動作）
		} else {
		<?php // add 2010/11/15 Y.Matsukawa ] ?>
			// checkbox
			for(var i = 0;i < chkcnt;i ++) {
				if(cond) cond += " <?PHP echo $D_SHOP_COND; ?> ";
				cond += chk[i];
			}
			if(cond) cond = "("+cond+")";
			// select-one,radio,その他
			for(var j = 0;j < colcnt;j ++) {
				if(cond) cond += " <?PHP echo $D_SHOP_COND_COL; ?> ";
				cond += "("+col[j]+")";
			}
			// add 2009/02/06 Y.Matsukawa [
			// text
			for(var k = 0;k < fwcnt;k ++) {
				if(cond) cond += " <?PHP echo $D_SHOP_COND_COL; ?> ";
				cond += fw[k];
			}
			// add 2009/02/06 Y.Matsukawa ]
		}
	}
	return cond;
}
//絞り混み条件パラメータ取得		add 2009/12/10 Y.Matsukawa
function ZdcEmapGetCondParm() {
	var cond="";
	if(document.ZdcEmapCondForm) {
		var obj,arrcond=new Array(),condcnt=0;
		for(var i = 0;i < document.ZdcEmapCondForm.elements.length;i ++) {
			obj = document.ZdcEmapCondForm.elements[i];
			if(!obj) break;
			switch(obj.type) {
				case "checkbox":
					if(obj.checked == true) {
						arrcond[condcnt] = obj.name+'=1';
						condcnt ++;
					}
					break;
				case "select-one":
					if(obj.options[obj.selectedIndex].value) {
						val = obj.options[obj.selectedIndex].value.split(':');
						arrcond[condcnt] = obj.name+'='+val[1];
						condcnt ++;
					}
					break;
				case "radio":
					if(obj.checked == true && obj.value) {
						val = obj.value.split(':');
						arrcond[condcnt] = obj.name+'='+val[1];
						condcnt ++;
					}
					break;
				case "text":
					break;
				case "button":
					break;
				default:
					if(obj.value) {
						val = obj.value.split(':');
						arrcond[condcnt] = obj.name+'='+val[1];
						condcnt ++;
					}
					break;
			}
		}
		//condパラメータの組み立て
		for(var i = 0;i < condcnt;i ++) {
			if(cond) cond += '&';
			cond += arrcond[i];
		}
	}
	return cond;
}
//検索結果の処理
function ZdcEmapSearchShopResult(result) {
	var i,item,mrk,tmp,icnt,maxlat=0,maxlon=0,minlat=999999999,minlon=999999999;
	// 最寄り店舗		<?php // add 2011/11/25 Y.Matsukawa ?>
	ZdcEmapNearbyShopItem = null;
	//マーカー削除
	if(ZdcEmapMapShopMrkCnt != null) {
		for( i = 0;i < ZdcEmapMapShopMrkCnt;i ++) {
			ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);
			ZdcEmapMapShopMrkId[i] = null;
		}
	}
	ZdcEmapMapShopMrkCnt = 0;
	//エラー処理
	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> listres["+result.status+"]");
		ZdcEmapSearchEventStart();
		ZdcEmapSearchShopClose();
		ZdcEmapReadOff();
		return;
	}
	<?php // add 2011/11/25 Y.Matsukawa [ ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	ZdcEmapRouteShopItems = result.items;
	<?php } ?>
	<?php // add 2011/11/25 Y.Matsukawa ] ?>
	ZdcEmapSearchFirstCstm = 0;	<?php //add 2013/04/15 H.osamoto ?>
	//地図に置く
	//for( i in result.items ){		mod 2009/08/18 Y.Matsukawa
	icnt = result.items.length;
	for (i=icnt-1; i>=0; i--) {
		item = result.items[i];
		ZdcEmapNearbyShopItem = item;		<?php // add 2011/11/25 Y.Matsukawa ?>
		if(!item.icon) break;
		if(item.nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
			else tmp = "";
		// add 2011/04/27 H.Osamoto [
		<?php 
		//mod 2011/07/05 Y.Nakajima
		//if ($D_NEW_ICON_COL) { 
		if (isset($D_NEW_ICON_COL) && $D_NEW_ICON_COL != "") { 
		?>
		if(item.<?PHP echo $D_NEW_ICON_COL; ?> == 1) tmp = ZdcEmapIconImg["@NEW"];
		<?php 
		}
		?>
		// add 2011/04/27 H.Osamoto ]
		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
							ZdcEmapIconW[item.icon],ZdcEmapIconH[item.icon],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
							ZdcEmapIconOffsetX[item.icon],ZdcEmapIconOffsetY[item.icon],ZdcEmapIconW[item.icon]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[item.icon],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
							ZdcEmapIconImg[item.icon],tmp,
							item.id,item.icon,item.nflg,
							<?PHP
								// クリック
								if($D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(this.id); }"; 
									//else if($D_KYO_ICON_CLK == 2) echo "function() { ZdcEmapShopDetailKidClick(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg); }"; 		mod 2009/09/04 Y.Matsukawa
									else if($D_KYO_ICON_CLK == 2) echo "function() { ZdcEmapShopDetailKidClick(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg,this.lvl); }";
									else if($D_KYO_ICON_CLK == 3) echo "function() { ZdcEmapShopMsgOrDetail(this.data1,this.Point.my,this.Point.mx,this.data2,this.nflg,this.lvl,this.id); }";	// add 2011/07/19 K.Masuda
									else echo "null"; 
							?>,
							<?PHP
								// マウスオーバー
								if(!$D_KYO_ICON_MO) echo "null"; 
								if($D_KYO_ICON_MO) echo "function() { ZdcEmapShopMsg(this.id); }"; 
							?>,
							//null		mod 2009/10/14 Y.Matsukawa
							<?PHP
								// マウスアウト
								if($D_KYO_ICON_MOUT == 1) echo "function() { ZdcEmapShopMsgClose(); }";
								else echo "null"; 
							?>
							,item.lvl		// add 2009/09/04 Y.Matsukawa
							);
		if (ZdcEmapMapShopMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);//念のため
		ZdcEmapMapShopMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);

		//最大最小緯度経度取得
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		ZdcEmapMapShopMrkCnt ++;
		ZdcEmapIconDt[i] = item.lat + ":" + item.lon + ":" + ZdcEmapIconW[item.icon] + ":" + ZdcEmapIconH[item.icon];	// add 2011/07/19 K.Masuda
	}
	if(ZdcEmapSearchClickFlg) {
		ZdcEmapSearchClickFlg = 0;
		//初期検索時は画面移動
		if (ZdcEmapMapShopMrkCnt > 0) {
			//拠点が収まる範囲に移動
			ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,ZdcEmapMapObj.getMapLocation(),1);
		//} else {		mod 2010/05/21 Y.Matsukawa
		} else if (!result.options.exceptKid) {
			//検索半径の縮尺に移動  ※位置によってgetPoint2PointDistanceの値が変わるため毎回計算している
			var p = new ZdcPoint();
			p = ZdcEmapMapObj.getMapLocation();
			//var px = new ZdcPoint();
			//var py = new ZdcPoint();
			//px = new ZdcPoint(p.mx+1000,p.my,<?PHP echo $D_PFLG; ?>);//+1000なのは値が小さいとNaNになるため
			//py = new ZdcPoint(p.mx,p.my+1000,<?PHP echo $D_PFLG; ?>);
			//var mx = ZdcEmapGeometricObj.getPoint2PointDistance(p,px);//経度1000ミリ秒ごとの距離
			//var my = ZdcEmapGeometricObj.getPoint2PointDistance(p,py);//緯度1000ミリ秒ごとの距離
			//mx = 1000 / mx;//1mごとの経度
			//my = 1000 / my;//1mごとの緯度
			//var rx = parseInt(mx * <?PHP echo $D_SHOP_RAD; ?>);//経度の範囲
			//var ry = parseInt(my * <?PHP echo $D_SHOP_RAD; ?>);//経度の範囲
			var rx = parseInt((450000 / (11 * 1000)) * <?PHP echo $D_SHOP_RAD; ?>);//CGIと計算をあわせる
			var ry = parseInt((300000 / (9 * 1000)) * <?PHP echo $D_SHOP_RAD; ?>);//〃
			var p1 = new ZdcPoint(p.mx - rx,p.my - ry,<?PHP echo $D_PFLG; ?>);
			var p2 = new ZdcPoint(p.mx + rx,p.my + ry,<?PHP echo $D_PFLG; ?>);
			var bx = new ZdcBox(p1,p2);
			var lv = ZdcEmapMapObj.getMapBoxScale( bx, p );
			if(lv < 18) lv = lv + 1;//１つズームイン
			ZdcEmapMapObj.setMapScale(lv);
		}
	}
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	ZdcEmapSearchEventStart();
	//色々閉じる
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//検索位置を保持
	ZdcEmapSearchPoint = ZdcEmapMapObj.getMapLocation();
	ZdcEmapSearchScale = ZdcEmapMapObj.getMapScale();
	ZdcEmapReadOff();

	// 重なりアイコン判定
	<?php if($D_KYO_ICON_CLK == 3){ ?>
	ZdcEmapIconOverlap(icnt,ZdcEmapSearchScale);	// add 2011/07/19 K.Masuda
	<?php } ?>

	<?php // ルート探索モード		// add 2011/11/25 Y.Matsukawa ?>
	<?php if (isset($D_ROUTE_FIX_MODE) && $D_ROUTE_FIX_MODE) { ?>
	if (ZdcEmapNearbyShopItem) {
		// ルート描画
		ZdcEmapFixRouteSearch(ZdcEmapNearbyShopItem);
	}
	<?php } ?>
}

//リスト表示
function ZdcEmapSearchShopListClick(page) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchShopList(page)
}
function ZdcEmapSearchShopList(page) {
	//リストを表示させる
	if(<?PHP echo $D_SHOP_CLOSELIST; ?> && ZdcEmapMapShopDetailMrkId != null) {
		//リスト非表示モードで詳細表示中だと出さない
		ZdcEmapListObj.innerHTML = "";
		return;
	}
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_shop_list.htm?cid=<?PHP echo $cid; ?>"+		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_shop_list.htm?cid=<?PHP echo $cid; ?>"+
			  "&lat="+ZdcEmapNearShop.opts.lat+"&lon="+ZdcEmapNearShop.opts.lon+"&latlon="+ZdcEmapNearShop.opts.latlon+
			  "&radius="+ZdcEmapNearShop.opts.radius+"&jkn="+ZdcEmapNearShop.opts.jkn+"&page="+page;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/06 Y.Matsukawa
	<?php // add 2013/04/15 H.Osamoto [ ?>
	if(ZdcEmapSearchFirstCstm == 1) {
		url += "&first_search=1";
	}
	<?php // add 2013/04/15 H.Osamoto ] ?>
	//if(ZdcEmapMapShopDetailMrkId != null) url = url + "&detail=1";//詳細表示フラグ		del 2009/10/13 Y.Matsukawa
	// add 2009/10/13 Y.Matsukawa [
	// 詳細表示中
	if (ZdcEmapMapShopDetailMrkId != null) {
		// 詳細表示フラグ
		url += "&detail=1";
		// 詳細表示中の拠点ID
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		if (mrk && mrk.data1) url += "&dkid="+mrk.data1;
	}
	// add 2009/10/13 Y.Matsukawa [
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> list["+status+"]";
		ZdcEmapListObj.innerHTML = html;
		
		// add 2015/03/23 K.Iwayoshi [
		// 相談ボタン用 
		SMBC_DetailButtonShow(ZdcEmapMapShopDetailMrkId);
		//add 2015/03/23 K.Iwayoshi ]
	});
}
//リストから選択
function ZdcEmapShopClick(id) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapSearchPoint = null;//必ず再検索させるため
	var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
	//表示する
	//ZdcEmapShopDetailKidClick(mrk.data1,mrk.Point.my,mrk.Point.mx,mrk.data2,mrk.nflg);		mod 2009/09/04 Y.Matsukawa
	ZdcEmapShopDetailKidClick(mrk.data1,mrk.Point.my,mrk.Point.mx,mrk.data2,mrk.nflg,mrk.lvl);
	
	//add 2015/03/23 K.Iwayoshi [
	// 相談ボタン用 
	SMBC_DetailButtonShow(id);
	//add 2015/03/23 K.Iwayoshi ]	

	//add 2015/03/23 K.Iwayoshi [
	// 非表示処理 フラグを立てる 
	ShowListButtonFlag = true;
	//add 2015/03/23 K.Iwayoshi ]
}

//add 2015/03/23 K.Iwayoshi [
// 三井住友用 相談ボタン表示処理 
ShowListButtonFlag = false;

//三井住友用 相談ボタン表示処理
function SMBC_DetailButtonShow(kid){
	//相談ボタン表示処理 オプションでSMBC_DETAIL_BUTTON_SHOW_FLAGフラグに１をセットしないと動作しない
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		
		//相談ボタンフラグの取得
		var id = document.getElementById(kid + "_SHOWFLAG");

		//フラグチェック 1の場合は表示
		if(id != null && id.getAttribute("flagValue") == 1){
			//表示処理
			// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する
			//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "";
				eles[i].setAttribute("value" , kid);
			}
		}else if(id != null && id.getAttribute("flagValue") != 1){
			//表示処理
			// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する
			//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "none";
				eles[i].setAttribute("value" , kid);
			}
		}
		
		//表示処理
		if(ShowListButtonFlag){
			// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する[
			//var eles = document.getElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "none";
			}
		}else{
			// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する[
			//var eles = document.getElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_LIST_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "";
			}
		}
	}
}
//add 2015/03/23 K.Iwayoshi ]

//最寄検索を隠す
function ZdcEmapSearchShopClose() {
	ZdcEmapCondObj.innerHTML = "";
	ZdcEmapCondObj.mode = "";
	ZdcEmapListObj.innerHTML = "";
	for( i = 0;i < ZdcEmapMapShopMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[i]);//マーカー削除
		ZdcEmapMapShopMrkId[i] = null;
	}
	ZdcEmapMapShopMrkCnt = 0;
}
var ZdcEmapMapFrontShopMrkId = null;		// add 2009/10/14 Y.Matsukawa
//指定されたアイコンを前面にもってくる
function ZdcEmapMapFrontShopMrk(id){
	if(ZdcEmapMapShopMrkId[id] != null) {
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
		// del 2009/10/14 Y.Matsukawa [
		//		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopMrkId[id]);
		//		ZdcEmapMapShopMrkId[id] = ZdcEmapMapUserLyr.addMarker(mrk);
		//		//イベント当てなおし
		//		if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
		//		if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
		//		if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
		// del 2009/10/14 Y.Matsukawa ]
		// add 2009/10/14 Y.Matsukawa [
		ZdcEmapMapFrontShopReset();
		mrk.setTopZIndex();
		ZdcEmapMapFrontShopMrkId = ZdcEmapMapShopMrkId[id];
		// add 2009/10/14 Y.Matsukawa ]
	}
}
//詳細アイコンを前面にもってくる
function ZdcEmapMapFrontShopDetail(){
	var mrk;
	if(ZdcEmapMapShopDetailMrkId != null) {
		//フォーカス
		// del 2009/10/14 Y.Matsukawa [
		//		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapCurFocusMrkId);
		//		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
		//		ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
		//		//アイコン
		//		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		//		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
		//		ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
		//		//イベント当てなおし
		//		if(mrk.mouseclickmarker) ZdcEvent.addListener(mrk, "mouseclickmarker", mrk.mouseclickmarker);
		//		if(mrk.mouseovermarker)  ZdcEvent.addListener(mrk, "mouseovermarker" , mrk.mouseovermarker);
		//		if(mrk.mouseoutmarker)   ZdcEvent.addListener(mrk, "mouseoutmarker"  , mrk.mouseoutmarker);
		// del 2009/10/14 Y.Matsukawa ]
		// add 2009/10/14 Y.Matsukawa [
		ZdcEmapMapFrontShopReset();
		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapCurFocusMrkId);
		mrk.setTopZIndex(5);
		mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
		mrk.setTopZIndex();
		ZdcEmapMapFrontShopMrkId = ZdcEmapMapShopDetailMrkId;
//		ZdcEmapMapFrontShopMrkId = ZdcEmapMapCurFocusMrkId;
		// add 2009/10/14 Y.Matsukawa ]
	}
}
//前面に持ってきたアイコンを元に戻す		add 2009/10/14 Y.Matsukawa
function ZdcEmapMapFrontShopReset() {
	if (ZdcEmapMapFrontShopMrkId != null) {
		var mrk = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapFrontShopMrkId);
		if (mrk) mrk.setDefaultZIndex();
		ZdcEmapMapFrontShopMrkId = null;
	}
}

// アイコンの重なり判定		add 2011/07/19 K.Masuda [
var D_ZOOM = new Array();
var D_ZOOM2PXMS_LAT = new Array();
var D_ZOOM2PXMS_LON = new Array();
D_ZOOM["1"]=89; D_ZOOM2PXMS_LAT["89"]=128836.6013; D_ZOOM2PXMS_LON["89"]=158117.6471;
D_ZOOM["2"]=87; D_ZOOM2PXMS_LAT["87"]=64418.30065; D_ZOOM2PXMS_LON["87"]=79058.82353;
D_ZOOM["3"]=85; D_ZOOM2PXMS_LAT["85"]=28183.00654; D_ZOOM2PXMS_LON["85"]=34588.23529;
D_ZOOM["4"]=82; D_ZOOM2PXMS_LAT["82"]=14954.24837; D_ZOOM2PXMS_LON["82"]=18352.94118;
D_ZOOM["5"]=81; D_ZOOM2PXMS_LAT["81"]=10352.94118; D_ZOOM2PXMS_LON["81"]=12705.88235;
D_ZOOM["6"]=77; D_ZOOM2PXMS_LAT["77"]=5751.633987; D_ZOOM2PXMS_LON["77"]=7058.823529;
D_ZOOM["7"]=72; D_ZOOM2PXMS_LAT["72"]=2588.235294; D_ZOOM2PXMS_LON["72"]=3176.470588;
D_ZOOM["8"]=70; D_ZOOM2PXMS_LAT["70"]=1581.699346; D_ZOOM2PXMS_LON["70"]=1941.176471;
D_ZOOM["9"]=67; D_ZOOM2PXMS_LAT["67"]=1150.326797; D_ZOOM2PXMS_LON["67"]=1411.764706;
D_ZOOM["10"]=62; D_ZOOM2PXMS_LAT["62"]=539.2156863; D_ZOOM2PXMS_LON["62"]=661.7647059;
D_ZOOM["11"]=56; D_ZOOM2PXMS_LAT["56"]=206.6993464; D_ZOOM2PXMS_LON["56"]=253.6764706;
D_ZOOM["12"]=55; D_ZOOM2PXMS_LAT["55"]=152.7777778; D_ZOOM2PXMS_LON["55"]=187.5000000;
D_ZOOM["13"]=52; D_ZOOM2PXMS_LAT["52"]=98.85620915; D_ZOOM2PXMS_LON["52"]=121.3235294;
D_ZOOM["14"]=50; D_ZOOM2PXMS_LAT["50"]=74.14215686; D_ZOOM2PXMS_LON["50"]=90.99264706;
D_ZOOM["15"]=46; D_ZOOM2PXMS_LAT["46"]=47.18137255; D_ZOOM2PXMS_LON["46"]=57.90441176;
D_ZOOM["16"]=44; D_ZOOM2PXMS_LAT["44"]=33.70098039; D_ZOOM2PXMS_LON["44"]=41.36029412;
D_ZOOM["17"]=42; D_ZOOM2PXMS_LAT["42"]=26.96078431; D_ZOOM2PXMS_LON["42"]=33.08823529;
D_ZOOM["18"]=39; D_ZOOM2PXMS_LAT["39"]=15.72712418; D_ZOOM2PXMS_LON["39"]=19.30147059;
var IconGrp = new Array();
function ZdcEmapIconOverlap(icnt,lvl){
	var icdt,ic,tmpic,p1,p2,c1,c2,c3,c4,obj;
	var nlatmin = new Array();
	var nlatmax = new Array();
	var nlonmin = new Array();
	var nlonmax = new Array();
	var ZGobj = new ZdcGeometric();

	for(ic=icnt-1; ic>=0; ic--){
		icdt = ZdcEmapIconDt[ic].split(":");
		// icdt[0] lat:緯度
		// icdt[1] lon:経度
		// icdt[2] w:アイコン幅
		// icdt[3] h:アイコン高
		nlatmin[ic] = Math.round(parseInt(icdt[0]) + (D_ZOOM2PXMS_LAT[D_ZOOM[lvl]] * (parseInt(icdt[2]) / 2)));	// 右上緯度
		nlonmin[ic] = Math.round(parseInt(icdt[1]) + (D_ZOOM2PXMS_LON[D_ZOOM[lvl]] * (parseInt(icdt[3]) / 2)));	// 右上経度
		nlatmax[ic] = Math.round(parseInt(icdt[0]) - (D_ZOOM2PXMS_LAT[D_ZOOM[lvl]] * (parseInt(icdt[2]) / 2)));	// 左下緯度
		nlonmax[ic] = Math.round(parseInt(icdt[1]) - (D_ZOOM2PXMS_LON[D_ZOOM[lvl]] * (parseInt(icdt[3]) / 2)));	// 左下経度
	}
	for(ic=icnt-1; ic>=0; ic--){
		// id->kid変換
		obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[ic]);
		IconGrp[ic] = obj.data1;
		// 重なり判定
		for(tmpic=icnt-1; tmpic>=0; tmpic--){
			if( tmpic == ic){ continue; }	// 自分自身は除外
			// id->kid変換
			obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[tmpic]);
			// 矩形緯度経度
			p1 = new ZdcPoint(nlonmin[ic],nlatmin[ic],<?PHP echo $D_PFLG; ?>);
			p2 = new ZdcPoint(nlonmax[ic],nlatmax[ic],<?PHP echo $D_PFLG; ?>);
			// 線分緯度経度
			c1 = new ZdcPoint(nlonmin[tmpic],nlatmin[tmpic],<?PHP echo $D_PFLG; ?>);	// 右上緯度経度
			c2 = new ZdcPoint(nlonmax[tmpic],nlatmin[tmpic],<?PHP echo $D_PFLG; ?>);	// 左上緯度経度
			c3 = new ZdcPoint(nlonmax[tmpic],nlatmax[tmpic],<?PHP echo $D_PFLG; ?>);	// 左下緯度経度
			c4 = new ZdcPoint(nlonmin[tmpic],nlatmax[tmpic],<?PHP echo $D_PFLG; ?>);	// 右下緯度経度
			// 矩形に線分が交差するか？
			if( ZGobj.isLineCrossRect(c1,c2,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
			if( ZGobj.isLineCrossRect(c2,c3,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
			if( ZGobj.isLineCrossRect(c3,c4,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
			if( ZGobj.isLineCrossRect(c4,c1,p1,p2) ){ IconGrp[ic] += "," + obj.data1; continue; }
		}
	}
}
// add 2011/07/19 K.Masuda ]

//-------------------------------------------------------------
//各詳細
//-------------------------------------------------------------
//詳細表示(拠点指定) 拠点接続用
<?php //function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg) {		2007/11/16 mod Y.Matsukawa ?>
<?php //function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove) {		mod 2009/09/04 Y.Matsukawa ?>
<?php //function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove,lvl) {		mod 2011/08/23 Y.Matsukawa ?>
function ZdcEmapShopDetailKidFirst(kid,lat,lon,icnno,nflg,nomove,lvl,nomap) {

	//add 2015/03/23 K.Iwayoshi [
	// 相談ボタンフラグの取得 
	var id = document.getElementById(kid + "_SHOWFLAG");
	//add 2015/03/23 K.Iwayoshi ]	

	//add 2015/03/23 K.Iwayoshi [
	// 非表示処理 フラグを立てる 
	ShowListButtonFlag = true;
	//add 2015/03/23 K.Iwayoshi ]

	ZdcEmapSearchClickFlg = 1;
	if (!lvl) lvl = 0;		<?php // add 2009/09/04 Y.Matsukawa ?>
	if (!nomap) nomap = 0;	<?php // add 2011/08/23 Y.Matsukawa ?>
	//画面遷移履歴
	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapMove('"+lat+"','"+lon+"','"+ZdcEmapMapObj.getMapScale()+"');"
			<?php //+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa ?>
			<?php //+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";		mod 2011/08/23 Y.Matsukawa ?>
			+ "ZdcEmapShopDetailKidFirst('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"','"+nomap+"');";
	ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	ZdcEmapHistorySave();
	<?php // add 2012/10/09 Y.Matsukawa [ ?>
	<?php // カスタム関数が定義されていたら実行 ?>
	if (typeof ZdcEmapCFShopDetailKidFirst == 'function') {
		ZdcEmapCFShopDetailKidFirst(kid);
	}
	<?php // add 2012/10/09 Y.Matsukawa ] ?>
	//
	<?php //ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg);		2007/11/16 mod Y.Matsukawa ?>
	<?php //ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,nomove);		mod 2009/09/04 Y.Matsukawa ?>
	<?php // add 2011/08/23 Y.Matsukawa [ ?>
	if (nomap == 1) {
		ZdcEmapShopDetailKidNoMap(kid);
		return;
	} else {
	<?php // add 2011/08/23 Y.Matsukawa ] ?>
		ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,nomove,lvl);
	}
	if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
	// 2008/10/15 Y.Matsukawa add [
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//拠点以外のアイコンをクリア
		for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
			ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
	}
	// 2008/10/15 Y.Matsukawa add ]
	
	// add 2015/03/23  K.Iwayoshi [
	//相談ボタン表示処理 オプションでSMBC_DETAIL_BUTTON_SHOW_FLAGフラグに１をセットしないと動作しない
	if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
		
		//フラグチェック 1の場合は表示
		if(id != null && id.getAttribute("flagValue") == 1){
			//表示処理
			// mod 2015/04/22 H.Yasunaga 下位互換用関数にてクラス名指定でエレメントを取得する[
			//var eles = document.getElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			var eles = CompatiblegetElementsByClassName("<?php echo $SMBC_DETAIL_BUTTON_SHOW_CLASSNAME ?>");
			// mod 2015/04/22]
			for(var i = 0 ; i < eles.length ; i++){
				eles[i].style.display = "";
				
				eles[i].setAttribute("value" , kid);
			}
		}
	}
	// add 2015/03/23 K.Iwayoshi ]

	// add 2016/02/15 Y.Uesugi [
	<?php if (isset($D_SHOP_CLOSECOND_DTL) || $D_SHOP_CLOSECOND_DTL != "") { ?>
		//絞込み非表示モードだと非表示とする
		ZdcEmapCondObj.mode = "";
		ZdcEmapCondObj.style.visibility = "hidden";
		ZdcEmapCondObj.innerHTML = "";
	<?php } ?>
	// add 2016/02/15 Y.Uesugi ]
}

//詳細表示(拠点指定)
//function ZdcEmapShopDetailKidClick(kid,lat,lon,icnno,nflg) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKidClick(kid,lat,lon,icnno,nflg,lvl) {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//印刷モード時は詳細出さない
	if (!lvl) lvl = 0;		// add 2009/09/04 Y.Matsukawa
	//画面遷移履歴
	var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapObj.setMapScale("+ZdcEmapMapObj.getMapScale()+");"
			//+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"');";		mod 2009/09/04 Y.Matsukawa
			+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
	if(ZdcEmapDetailObj.innerHTML == "" || ZdcEmapHistoryClickChk()) ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	  else ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
	ZdcEmapHistorySave();
	//
	ZdcEmapSearchPoint = null;//必ず再検索させるため
	//ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg);		mod 2009/09/04 Y.Matsukawa
	ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,false,lvl);
	if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
	// 2008/10/15 Y.Matsukawa add [
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//拠点以外のアイコンをクリア
		for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
			ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
			ZdcEmapMapPoiMrkId[i] = null;
		}
		// 地図上のカーソル外す		2010/04/23 Y.Matsukawa
		ZdcEmapMapCursorRemove();
	}
	// 2008/10/15 Y.Matsukawa add ]
	
	//add 2015/03/23 K.Iwayoshi[
	// 相談ボタン用 
	SMBC_DetailButtonShow(kid);
	//add 2015/03/23 K.Iwayoshi ]
	
	//add 2015/03/23 K.Iwayoshi [
	// 非表示処理 フラグを立てる
	ShowListButtonFlag = true;
	//add 2015/03/23 K.Iwayoshi]

	// add 2016/02/15 Y.Uesugi [
	<?php if (isset($D_SHOP_CLOSECOND_DTL) || $D_SHOP_CLOSECOND_DTL != "") { ?>
		//絞込み非表示モードだと非表示とする
		ZdcEmapCondObj.mode = "";
		ZdcEmapCondObj.style.visibility = "hidden";
		ZdcEmapCondObj.innerHTML = "";
	<?php } ?>
	// add 2016/02/15 Y.Uesugi ]
}

// add 2011/07/19 K.Masuda [
function ZdcEmapShopMsgOrDetail(kid,lat,lon,icnno,nflg,lvl,id) {
	for(var j=0; j<IconGrp.length; j++){
		if( IconGrp[j].indexOf(kid) == 0 ){
			var n = IconGrp[j].split(",").length - 1;
			if(n < 1 ){
				// 拠点詳細へ
				if(ZdcEmapButtonNG()) return;
				if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//印刷モード時は詳細出さない
				if (!lvl) lvl = 0;
				//画面遷移履歴
				var tmp = "ZdcEmapSearchEventStop();ZdcEmapMapObj.setMapScale("+ZdcEmapMapObj.getMapScale()+");"
						+ "ZdcEmapShopDetailKidClick('"+kid+"','"+lat+"','"+lon+"','"+icnno+"','"+nflg+"','"+lvl+"');";
				if(ZdcEmapDetailObj.innerHTML == "" || ZdcEmapHistoryClickChk()) ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
				  else ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Detail"]; ?>",tmp);
			ZdcEmapHistorySave();
				//
				ZdcEmapSearchPoint = null;//必ず再検索させるため
				ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,false,lvl);
				if(<?php echo $D_DSP_OTHER_KBN; ?> == 0) ZdcEmapSearchShopStart();
				if(<?php echo $D_DSP_OTHER_KBN; ?>) {
				//拠点以外のアイコンをクリア
					for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
						ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
						ZdcEmapMapPoiMrkId[i] = null;
					}
					// 地図上のカーソル外す
					ZdcEmapMapCursorRemove();
				}
			} else{
				// 吹き出し表示へ
				if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//印刷モード時は吹き出し出さない
				if(ZdcEmapButtonNG()) return;
				if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") return;//最寄駅や施設を出してる時は出さない
				ZdcEmapShopMsgClose();
				//縮尺が範囲外なら表示しない
				var s = ZdcEmapMapObj.getMapScale();
				if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
				//アイコンを前面に出す
				if(id != null) ZdcEmapMapFrontShopMrk(id);
				else ZdcEmapMapFrontShopDetail();
				//デザイン
				<?PHP echo $D_JSCODE_MSGSHOP; ?>

				// 複数ある場合、全てのkidを渡す
				var kidkosu = IconGrp[j].split(",");
				var kidprm = "";
				for( var k=0; k<kidkosu.length; k++ ){
					if( kidkosu[k] == ""){ continue; }
					kidprm += "&kid" + k + "=" + kidkosu[k];
				}

				if(id != null) var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
				else var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	
				//フキダシを表示させる
				var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>"+kidprm;

				url += "&<?php echo $P_FREEPARAMS; ?>";
				<?php if($https_req){ ?>url += "&https_req=1";<?php } ?>
				ZdcEmapHttpRequestHtml(url, function(html,status){
					if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> msg["+status+"]";
					var node = document.createElement('DIV');
					node.innerHTML = html;
					obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,<?PHP echo $D_FUKIDASHI_MOVE; ?>);
				}, true);
			}
			break;
		} else {
			continue;
		}
	}
}
// add 2011/07/19 K.Masuda ]
//function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg) {	2007/11/16 mod Y.Matsukawa
//function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,notmove) {		mod 2009/09/04 Y.Matsukawa
function ZdcEmapShopDetailKid(kid,lat,lon,icnno,nflg,notmove,lvl) {
	var mrk,tmp;
	ZdcEmapSearchEventStop();
	//if(<?PHP echo $D_INIT_LVL_DETAIL; ?> > 0) ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_DETAIL; ?>);//縮尺変更		del 2009/09/04 Y.Matsukawa
	// add 2009/09/04 Y.Matsukawa [
	if (lvl && lvl != 0) {
		ZdcEmapMapObj.setMapScale(lvl);
	} else if(<?PHP echo $D_INIT_LVL_DETAIL; ?> > 0) {
		ZdcEmapMapObj.setMapScale(<?PHP echo $D_INIT_LVL_DETAIL; ?>);
	}
	// add 2009/09/04 Y.Matsukawa ]
	//詳細を表示させる
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_shop_detail.htm?cid=<?PHP echo $cid; ?>&kid="+kid;	mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_shop_detail.htm?cid=<?PHP echo $cid; ?>&kid="+kid;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/02/23 Y.Matsukawa
	// add 2009/12/10 Y.Matsukawa [
	//絞り込み条件
	cond = ZdcEmapGetCondParm();
	if(cond) url = url + '&'+cond;
	// add 2009/12/10 Y.Matsukawa ]
	<?php // mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> detail["+status+"]";
		ZdcEmapDetailObj.innerHTML = html;
		// add 2009/09/28 Y.Matsukawa [
		var dtl_script = null;
		for(i=1; i<=5; i++) {
			dtl_script = document.getElementById("dtl_script"+i);
			if (dtl_script && dtl_script.innerHTML) eval(dtl_script.innerHTML);
		}
		// add 2009/09/28 Y.Matsukawa ]
<?php	// add 2010/09/13 Y.Matsukawa [
		// 拠点詳細表示拠点をCookieに書き出し
		//if ($D_COOKIE_SHOPDTL_MAX > 0) {		mod 2012/06/19 Y.Matsukawa
		if ($D_COOKIE_SHOPDTL_AUTO && $D_COOKIE_SHOPDTL_MAX > 0) {
?>
		var knmenc_obj = document.getElementById("ZdcEmapShopNameEnc");
		var knmenc = "";
		if (knmenc_obj) knmenc = knmenc_obj.value;
		ZdcEmapCookieWriteShopDetail('<?PHP echo $cid; ?>', kid, knmenc);
<?php	}
		// add 2010/09/13 Y.Matsukawa ]
?>
<?php	// add 2011/06/16 Y.Matsukawa [ ?>
<?php	// カスタム関数が定義されていたら実行 ?>
		if (typeof ZdcEmapCFAfterShopDetail == 'function') {
			var opts = new ZdcKyotenIdOptions();
			opts.cid = '<?PHP echo $D_CID; ?>'
			opts.kid = kid;
			opts.nolog = true;
			opts.timeout = <?PHP echo $D_AJAX_TIMEOUT; ?>;
			ZdcEmapKyotenId.opts = opts;
			ZdcEmapKyotenId.search(opts, ZdcEmapCFAfterShopDetailEx);
		}
		
		//add 20150323 K.Iwayoshi [
		// 相談ボタン用 
		SMBC_DetailButtonShow(kid);
		//add 20150323 K.Iwayoshi ]		

		//add 2015/03/23 K.Iwayoshi [
		//店舗詳細画面単体表示時の各種ボタンの非表示処理 
		if(<?php 
			if(isset($SMBC_DETAIL_BUTTON_SHOW_FLAG)){
				echo $SMBC_DETAIL_BUTTON_SHOW_FLAG;
			}else{
				echo "0";
			}
		?> == 1) {
			var data_detail = document.getElementById("SMBC_DETAIL_RUN_FLUG");
			//フラグチェック 1の場合は非表示
			if(data_detail != null && data_detail.getAttribute("flagValue") == "1"){
				var table_inner = document.getElementById("custDtlInnerTable");
				table_inner.style.display = "none";
			}
		}
		//add 2015/03/23 K.Iwayoshi ]
		
<?php	// add 2011/06/16 Y.Matsukawa ] ?>
	});
	//フォーカスカーソルを表示する
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						 ZdcEmapIconW['@SEL'],ZdcEmapIconH['@SEL'],0,0,
						 ZdcEmapIconOffsetX['@SEL'],ZdcEmapIconOffsetY['@SEL'],0,0,0,0,
						 ZdcEmapIconImg['@SEL'],'',
						 '','',0,null,null,null);
	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
	ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	mrk.setTopZIndex(3);		// add 2009/10/14 Y.Matsukawa
	//詳細アイコンを表示する
	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
		else tmp = "";
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						ZdcEmapIconW[icnno],ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
						ZdcEmapIconOffsetX[icnno],ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
						ZdcEmapIconImg[icnno],tmp,
						kid,icnno,nflg,
						<?PHP
							// mod 2011/07/05 Y.Nakajima
							if(isset($D_KYO_ICON_CLK) && $D_KYO_ICON_CLK == 1) echo "function() { ZdcEmapShopMsg(null); }"; 
								else echo "null"; 
						?>,
						<?PHP
							if(!$D_KYO_ICON_MO) echo "null"; 
							// mod 2011/07/05 Y.Nakajima
							if($D_KYO_ICON_MO != "") echo "function() { ZdcEmapShopMsg(null); }"; 
						?>,
						//null		mod 2009/10/14 Y.Matsukawa
						<?PHP
							// マウスアウト
							if($D_KYO_ICON_MOUT == 1) echo "function() { ZdcEmapShopMsgClose(); }";
							else echo "null"; 
						?>
						);
	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	//動作モードの切り替え
	if(<?php echo $D_DSP_OTHER_KBN; ?>) {
		//拠点詳細以外は非表示
		ZdcEmapSearchEventStop();
		ZdcEmapSearchShopClose();
	} else {
		//最寄拠点表示
		ZdcEmapSearchEventStart();
	}
	//ZdcEmapMapMove(lat, lon);		2007/11/16 mod Y.Matsukawa
	if (!notmove) ZdcEmapMapMove(lat, lon);
	ZdcEmapMapObj.saveMapLocation();
	//他の情報を閉じる
	ZdcEmapShopMsgClose();
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();

}
<?php // add 2011/08/23 Y.Matsukawa ?>
<?php // 拠点詳細表示（地図非表示）※検索ウィンドウを利用 ?>
function ZdcEmapShopDetailKidNoMap(kid) {
	// 詳細を表示させる
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_shop_detail.htm?cid=<?PHP echo $cid; ?>&kid="+kid+"&nomap=1";
	url += "&<?php echo $P_FREEPARAMS; ?>";
	// 絞り込み条件
	cond = ZdcEmapGetCondParm();
	if(cond) url = url + '&'+cond;
	<?php if($https_req){ ?>url += "&https_req=1";<?php } ?>
	ZdcEmapSearchRequest(url);
}
//拠点詳細を隠す
function ZdcEmapShopDetailClose() {
	ZdcEmapDetailObj.innerHTML = "";
	
	if(ZdcEmapMapShopDetailMrkId != null) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
		ZdcEmapMapShopDetailMrkId = null;
	}
	if(ZdcEmapMapCurFocusMrkId != null) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
		ZdcEmapMapCurFocusMrkId = null;
	}
}
//詳細表示(アイコンのみ表示)
//function ZdcEmapShopIcon(lat,lon,icnno,nflg) {	// 2011/06/29 mod K.Masuda
function ZdcEmapShopIcon(lat,lon,icnno,nflg,NotMoveFlag) {
	//登録されていないアイコンIDの場合は処理しない
	if (!ZdcEmapIconImg[icnno]) return;
	var mrk;
	//地図移動
	// 2011/06/29 mod K.Masuda [
	//ZdcEmapMapMove(lat, lon);
	if( NotMoveFlag == undefined || NotMoveFlag != 1 ){
		ZdcEmapMapMove(lat, lon);
	}
	// 2011/06/29 mod K.Masuda ]
	ZdcEmapMapObj.saveMapLocation();
	//フォーカスカーソルを表示する
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						ZdcEmapIconW['@SEL'],ZdcEmapIconH['@SEL'],0,0,
						ZdcEmapIconOffsetX['@SEL'],ZdcEmapIconOffsetY['@SEL'],0,0,0,0,
						ZdcEmapIconImg['@SEL'],'',
						'','',0,null,null,null);
	if(ZdcEmapMapCurFocusMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapCurFocusMrkId);
	ZdcEmapMapCurFocusMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
	mrk.setTopZIndex(3);		// add 2009/10/14 Y.Matsukawa
	//アイコンを表示する
	if(nflg == 1) tmp = ZdcEmapIconImg["@NEW"];
		else tmp = "";
	mrk = ZdcEmapMakeMrk(0,lat,lon,
						ZdcEmapIconW[icnno],ZdcEmapIconH[icnno],ZdcEmapIconW['@NEW'],ZdcEmapIconH['@NEW'],
						ZdcEmapIconOffsetX[icnno],ZdcEmapIconOffsetY[icnno],ZdcEmapIconW[icnno]-ZdcEmapIconW['@NEW'],ZdcEmapIconH[icnno],<?PHP echo $D_ICON_MSGOFFSETX; ?>,<?PHP echo $D_ICON_MSGOFFSETY; ?>,
						ZdcEmapIconImg[icnno],tmp,
						0,icnno,nflg,
						null, null,null);
	if(ZdcEmapMapShopDetailMrkId != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapShopDetailMrkId = ZdcEmapMapUserLyr.addMarker(mrk);
}

//function debug1(s) {
//var d = document.getElementById("mapRuleLink");
//d.innerHTML += s;
//}

//フキダシ表示
function ZdcEmapShopMsg(id) {
	if(ZdcEmapMapObj.ZdcEmapMode == "print") return;//印刷モード時は吹き出し出さない
	if(ZdcEmapButtonNG()) return;
	//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") return;//最寄駅や施設を出してる時は出さない	mod 2010/06/16 Y.Matsukawa
	if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") return;//最寄駅や施設を出してる時は出さない
	ZdcEmapShopMsgClose();
	//縮尺が範囲外なら表示しない
	var s = ZdcEmapMapObj.getMapScale();
	if(s < <?PHP echo $D_VIEW_ICON_MAX; ?> || s > <?PHP echo $D_VIEW_ICON_MIN; ?>) return;
	//アイコンを前面に出す
	if(id != null) ZdcEmapMapFrontShopMrk(id);
	else ZdcEmapMapFrontShopDetail();
	//デザイン
	<?PHP echo $D_JSCODE_MSGSHOP; ?>
	
	if(id != null) var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopMrkId[id]);
	else var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	
	//フキダシを表示させる
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>&id="+i+"&kid="+obj.data1;		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_msg.htm?cid=<?PHP echo $cid; ?>&id="+i+"&kid="+obj.data1;
	url += "&<?php echo $P_FREEPARAMS; ?>";		// add 2009/03/17 Y.Matsukawa
	<!-- // mod 2011/07/05 Y.Nakajima -->
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> msg["+status+"]";
		var node = document.createElement('DIV');
		node.innerHTML = html;
		//obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,1);	// mod 2011/07/06 K.Masuda
		<?PHP //add 2011/07/05 Y.Nakajima 
		if (!isset($D_FUKIDASHI_MOVE)) $D_FUKIDASHI_MOVE = 0; ?>
		obj.openUserMsgWindow(ZdcEmapMsg,obj.Point,node,<?PHP echo $D_FUKIDASHI_MOVE; ?>);
	//});		mod 2009/02/16 Y.Matsukawa
	}, true);
}
//閉じる
function ZdcEmapShopMsgClose() {
	if (ZdcEmapMapObj.getUserMsgOpenStatus()) {
		//ZdcEmapSearchEventStart();		del 2008/10/15 Y.Matsukawa
		ZdcEmapMapObj.closeUserMsgWindow();
	}
	ZdcEmapMapFrontShopReset();		// add 2009/10/14 Y.Matsukawa
	ZdcEmapTipsClose();//TIPSもついでに閉じる
}

//印刷画面開く
function ZdcEmapShopPrintClick(id) {
	if(ZdcEmapButtonNG()) return;
	//window.open = "<?PHP echo $D_DIR_BASE; ?>print.htm?cid=<?PHP echo $cid; ?>&kid="+id;		mod 2010/07/20 Y.Matsukawa
	window.open = "<?PHP echo $D_DIR_BASE_G; ?>print.htm?cid=<?PHP echo $cid; ?>&kid="+id;
}
//詳細の最寄施設検索
function ZdcEmapShopDetailNpoiClick() {
	if(ZdcEmapButtonNG()) return;
	if(ZdcEmapMapShopDetailMrkId == null) return;
	//最寄拠点検索を停止
	ZdcEmapSearchEventStop();
	//詳細に移動
	var obj = ZdcEmapMapUserLyr.getMarkerById(ZdcEmapMapShopDetailMrkId);
	ZdcEmapMapMove(obj.Point.my, obj.Point.mx);
	//最寄施設検索
	ZdcEmapPoiClick(1);
}

// add 2011/06/16 Y.Matsukawa
function ZdcEmapCFAfterShopDetailEx(result) {
	if (typeof ZdcEmapCFAfterShopDetail == 'function') {
		ZdcEmapCFAfterShopDetail(result.item);
	}
}

//-------------------------------------------------------------
//最寄駅検索
//-------------------------------------------------------------

<?php if(isset($D_REQ_JSAPI["neki"]) && $D_REQ_JSAPI["neki"] != ""){ ?>	// 2008/10/22 Y.Matsukawa add
var ZdcEmapNeki = new ZdcNearStation();
ZdcEvent.addListener(ZdcEmapNeki, "end", ZdcEmapStationResult);
<?php } ?>
//駅検索開始
function ZdcEmapStationClick(lat,lon) {
	if(ZdcEmapButtonNG()) return;
	<?php	// add 2011/06/27 H.osamoto [ ?>
	<?php	// カスタム関数が定義されていたら実行 ?>
		if (typeof ZdcEmapCFBeforeStationClick == 'function') {
			ZdcEmapCFBeforeStationClick();
		}
	<?php	// add 2011/06/27 H.osamoto ] ?>
	ZdcEmapPoiRouteClear();
	// 2007/11/28 mod Y.Matsukawa ※ZdcEmapShopMsgCloseの中でSearchEventStartしてしまっているので、順番入れ替えました
	//	ZdcEmapSearchEventStop();
	//	ZdcEmapShopMsgClose();
	ZdcEmapShopMsgClose();
	ZdcEmapSearchEventStop();
	//
	ZdcEmapStation(lat,lon);
	//画面を切り替える
	if(ZdcEmapCondObj.mode != "eki") {
		ZdcEmapSearchShopClose();
		ZdcEmapCondObj.innerHTML = "";
		//if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");	mod 2010/06/16 Y.Matsukawa
		if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");
			else ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");
		ZdcEmapHistorySave();
		ZdcEmapCondObj.mode = "eki";
		ZdcEmapCondObj.style.visibility = "hidden";
	}
}
//駅検索メイン処理
function ZdcEmapStation(lat,lon) {
	ZdcEmapReadOn();
	//
	var opts = new ZdcNearStationOptions();
	opts.startPos = 1;
	opts.maxCount =  <?PHP echo $D_ST_MAX; ?>;
	if(lat && lon) {
		opts.lat = lat;
		opts.lon = lon;
	} else {
		var p   = new ZdcPoint();
		p = ZdcEmapMapObj.getMapLocation();
		opts.lat = p.my;
		opts.lon = p.mx;
	}
	opts.limitCount = <?PHP echo $D_ST_MAX; ?>;
	opts.radius = <?PHP echo $D_ST_RAD; ?>;
	opts.pointFlg = <?PHP echo $D_PFLG; ?>;
	opts.lang = '<?PHP echo $D_EKI_LANG; ?>';	// add 2008/08/22 Y.Matsukawa
	ZdcEmapNeki.opts = opts;
	//リストを表示する
	ZdcEmapStationList(0);
	//アイコンを取得する
	ZdcEmapNeki.search(opts);
}
//検索処理
function ZdcEmapStationResult(result) {
	ZdcEmapSearchClose();
	ZdcEmapPoiRouteClear();
	//エラー処理
	if(result.status != 0 && result.status != 3 && result.status != 5 && result.status != 9) {
		alert("<?PHP echo $D_MSG_ERR_JS_RESULT; ?> ekires["+result.status+"]");
		ZdcEmapSearchEventStart();
		ZdcEmapListObj.innerHTML = "";
		ZdcEmapReadOff();
		return;
	}
	//地図に置く
	var i,item,mrk,maxlat=ZdcEmapNeki.opts.lat,maxlon=ZdcEmapNeki.opts.lon,minlat=maxlat,minlon=maxlon;
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//マーカー削除
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapMapPoiMrkCnt = 0;
	for( i in result.items ){
		item = result.items[i];
		//アイコンの作成
		mrk = ZdcEmapMakeMrk(i,item.lat,item.lon,
							<?PHP echo $D_ICON_EKI_W; ?>,<?PHP echo $D_ICON_EKI_H; ?>,0,0,
							<?PHP echo $D_ICON_EKI_OFFSET_X; ?>,<?PHP echo $D_ICON_EKI_OFFSET_Y; ?>,0,0,0,0,
							'<?PHP echo $D_ICON_EKI_IMAGE; ?>',item.icons,
							item.stationName,"",0,
							function() { ZdcEmapRouteSearch('<?PHP echo $D_USER_DEFNAME; ?>',ZdcEmapNeki.opts.lon,ZdcEmapNeki.opts.lat,this.data,this.Point.mx,this.Point.my) },
							function() { ZdcEmapTipsClick(this.id); },null);
		if (ZdcEmapMapPoiMrkId[i] != null) ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);//念のため
		ZdcEmapMapPoiMrkId[i] = ZdcEmapMapUserLyr.addMarker(mrk);
		//最大最小緯度経度取得
		if(item.lat > maxlat) maxlat = item.lat;
		if(item.lon > maxlon) maxlon = item.lon;
		if(item.lat < minlat) minlat = item.lat;
		if(item.lon < minlon) minlon = item.lon;
		ZdcEmapMapPoiMrkCnt ++;
	}
	if (ZdcEmapMapPoiMrkCnt > 0) {
		ZdcEmapMapMoveBox(minlat,minlon,maxlat,maxlon,new ZdcPoint(ZdcEmapNeki.opts.lon, ZdcEmapNeki.opts.lat, <?PHP echo $D_PFLG; ?>));
	}
	ZdcEmapMapFrontShopDetail();
	ZdcEmapMapCursorRemove();
	ZdcEmapReadOff();
}
//リスト表示
function ZdcEmapStationListClick(page) {
	if(ZdcEmapButtonNG()) return;
	ZdcEmapStationList(page)
}
function ZdcEmapStationList(page) {
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_neki.htm?cid=<?PHP echo $cid; ?>"+		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_neki.htm?cid=<?PHP echo $cid; ?>"+
			  "&lat="+ZdcEmapNeki.opts.lat+"&lon="+ZdcEmapNeki.opts.lon+"&page="+page;
	<!-- // mod 2011/07/05 Y.Nakajima -->
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> eki["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}

<?php
// add 2010/06/16 Y.Matsukawa
//-------------------------------------------------------------
// 出発地を指定してルート探索
//-------------------------------------------------------------
?>
// 出発地を指定してルート探索モード開始
function ZdcEmapFreeRouteClick(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	<?php	// add 2011/06/27 H.osamoto [ ?>
	<?php	// カスタム関数が定義されていたら実行 ?>
		if (typeof ZdcEmapCFBeforeRouteClick == 'function') {
			ZdcEmapCFBeforeRouteClick();
		}
	<?php	// add 2011/06/27 H.osamoto ] ?>
	//拠点以外のアイコンをクリア
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapPoiRouteClear();		// ルートクリア
	ZdcEmapShopMsgClose();		// 吹き出し消去
	ZdcEmapSearchEventStop();	// 検索イベント停止
	// 画面を切り替える
	if(ZdcEmapCondObj.mode != "froute") {
		ZdcEmapSearchShopClose();
		ZdcEmapCondObj.innerHTML = "";
		if(ZdcEmapCondObj.mode == "eki" || ZdcEmapCondObj.mode == "jnr" || ZdcEmapCondObj.mode == "froute") ZdcEmapHistoryChange("<?PHP echo $D_HISTORY_NAME["Neki"] ?>","");
		else ZdcEmapHistoryAdd("<?PHP echo $D_HISTORY_NAME["FRoute"] ?>","");
		ZdcEmapHistorySave();
		ZdcEmapCondObj.mode = "froute";
		ZdcEmapCondObj.style.visibility = "hidden";
		//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
		var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
				+"&lat="+lat+"&lon="+lon+"&mode=init"
				+"&<?php echo $P_FREEPARAMS; ?>"
		;
		<!-- // mod 2011/07/05 Y.Nakajima -->
		<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
		if (ZdcEmapFRouteInitStr) url += "&frouteinit="+ZdcEmapFRouteInitStr;	<?php // add 2011/02/16 Y.Matsukawa ?>
		ZdcEmapHttpRequestHtml(url, function(html,status){
			if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
			ZdcEmapListObj.innerHTML = html;
		});
	}
}
// 出発地を指定してルート探索モード開始（Light／Maplink）		add 2010/09/07 Y.Matsukawa
function ZdcEmapFreeRouteClickLight(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	//拠点以外のアイコンをクリア
	for( i = 0;i < ZdcEmapMapPoiMrkCnt;i ++) {
		ZdcEmapMapUserLyr.removeMarkerById(ZdcEmapMapPoiMrkId[i]);
		ZdcEmapMapPoiMrkId[i] = null;
	}
	ZdcEmapPoiRouteClear();		// ルートクリア
	ZdcEmapShopMsgClose();		// 吹き出し消去
	ZdcEmapSearchEventStop();	// 検索イベント停止
	// 画面を切り替える
	ZdcEmapSearchShopClose();
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
			+"&lat="+lat+"&lon="+lon+"&mode=init"
			+"&<?php echo $P_FREEPARAMS; ?>"
	;
	<!-- // mod 2011/07/05 Y.Nakajima -->
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php } ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// ルート表示
function ZdcEmapFreeRouteDraw(lat, lon) {
	if(ZdcEmapButtonNG()) return;
	// 地図中心位置を取得
	var center = ZdcEmapMapObj.getMapLocation();
	var mx = center.mx;
	var my = center.my;
	// ルート描画
	ZdcEmapRouteSearch("<?php echo $D_USER_DEFNAME; ?>", lon, lat, "地図中心", mx, my);
	<?php // add 2010/09/07 Y.Matsukawa [ ?>
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if (isset($D_FROUTE_CLOSE)) { ?>
	ZdcEmapFreeRouteClose();
	<?php } ?>
	<?php // add 2010/09/07 Y.Matsukawa ] ?>
}
<?php // add 2010/09/07 Y.Matsukawa [ ?>
// 出発地指定ルート探索を閉じる
function ZdcEmapFreeRouteClose() {
	ZdcEmapListObj.innerHTML = '';
}
<?php // add 2010/09/07 Y.Matsukawa ] ?>
// フリーワード検索
function ZdcEmapFreeRouteSearch(lat, lon) {
	var txt = document.getElementById("freeRouteSearchEntText");
	if (!txt || !txt.value) return;
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
			+"&lat="+lat+"&lon="+lon+"&mode=srch"
			+"&keyword="+txt.value
			+"&<?php echo $P_FREEPARAMS; ?>"
	;
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// フリーワード検索（ページ送り）
function ZdcEmapFreeRoutePage(lat, lon, page, type, keyword) {
	if (!page) page = 0;
	if (!type) type = "";
	//var url = "<?PHP echo $D_DIR_BASE; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"		mod 2011/02/09 Y.Matsukawa
	var url = "<?PHP echo $D_DIR_BASE_L; ?>emapview_froute.htm?cid=<?PHP echo $cid; ?>"
			+"&lat="+lat+"&lon="+lon+"&mode=srch&page="+page+"&type="+type
			+"&keyword="+keyword
			+"&<?php echo $P_FREEPARAMS; ?>"
	;
	<?php //mod 2011/07/05 Y.Nakajima ?>
	<?php if(isset($https_req) && $https_req != ""){ ?>url += "&https_req=1";<?php }	// add 2010/07/20 Y.Matsukawa ?>
	ZdcEmapHttpRequestHtml(url, function(html,status){
		if(status) html = "<?PHP echo $D_MSG_ERR_JS_REQUEST; ?> froute["+status+"]";
		ZdcEmapListObj.innerHTML = html;
	});
}
// 拠点詳細表示拠点をCookieに書き出し		add 2010/09/13 Y.Matsukawa
function ZdcEmapCookieWriteShopDetail(cid, kid, knmenc) {
	var save_value = "";
	var new_value = kid+","+knmenc;
	var pc_shopdtl = "";
	var key = "PC_SHOPDTL_"+cid;
	if (!navigator.cookieEnabled) return;
	// Cookie読み込み
	var ck = document.cookie;
	if (ck != "") {
		cookies = ck.split(";");
		for (i = 0; i < cookies.length; i++) {
			kv = cookies[i].split("=");
			if (kv[0].replace(/^\s+|\s+$/g, "") == key) {
				//pc_shopdtl = kv[1].replace(/^\s+|\s+$/g, "");		mod 2012/06/22 Y.Matsukawa
				if (kv[1]) pc_shopdtl = kv[1].replace(/^\s+|\s+$/g, "");
				break;
			}
		}
		if (pc_shopdtl != "") {
			vals = pc_shopdtl.split(",");
			var max = Math.floor(vals.length/2);
			if (max > <?php echo $D_COOKIE_SHOPDTL_MAX-1; ?>) max = <?php echo $D_COOKIE_SHOPDTL_MAX-1; ?>;
			var oc = 0;
			for (i = 0; i < max*2; i++) {
				if (vals[i*2] != undefined) {
					if (vals[i*2+1] == undefined) vals[i*2+1] = '';
					old_value = vals[i*2]+","+vals[i*2+1];
					if (old_value != new_value) {
						save_value += ","+old_value;
						oc++;
						if (oc >= max) break;
					}
				}
			}
		}
	}
	save_value = new_value + save_value;
	// Cookie書き出し
	ZdcEmapWriteCookie(key, save_value, <?php echo $D_COOKIE_SHOPDTL_EXPIRE; ?>);
}
<?php // 店舗情報をCookie保存		add 2012/06/19 Y.Matsukawa ?>
function ZdcEmapCookieSaveShopDetail(kid) {
<?php	// 拠点詳細表示拠点をCookieに書き出し
		if ($D_COOKIE_SHOPDTL_MAX > 0) { ?>
	var knmenc_obj = document.getElementById("ZdcEmapShopNameEnc");
	var knmenc = "";
	if (knmenc_obj) knmenc = knmenc_obj.value;
	ZdcEmapCookieWriteShopDetail('<?PHP echo $cid; ?>', kid, knmenc);
<?php	} ?>
}
<?php // Cookie保存された店舗情報をクリア		add 2012/06/19 Y.Matsukawa ?>
function ZdcEmapCookieClearShopDetail() {
	var key = "PC_SHOPDTL_<?PHP echo $cid; ?>";
	var str = key + "=;";
	str += "path=/;";
	document.cookie = str;
}
// Cookie書き出し
function ZdcEmapWriteCookie(key, value_esc, days) {
	var str = key + "=" + value_esc + ";";
	if (days != 0) {
		var dt = new Date();
		dt.setDate(dt.getDate() + days);
		str += "expires=" + dt.toGMTString() + ";";
	}
	str += "path=/;";
	document.cookie = str;
}

