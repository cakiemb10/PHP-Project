<?PHP
// ------------------------------------------------------------
// 最寄拠点CGI読み込みインターフェイス
// 
// 2011/03/10 Y.Matsukawa	新規作成
// 2011/07/05 Y.nakajima	VM化に伴うapache,phpVerUP対応改修
// 2012/10/15 H.Osamoto		検索範囲の指定を実距離で指定可能に変更
// 2012/11/15 Y.Matsukawa	JCN満空情報取得
// 2013/05/22 H.Osamoto		最寄検索結果が0件の場合再検索で取得する件数指定機能追加
// 2014/03/07 H.Osamoto		ポリゴン内外判定追加
// 2014/03/12 Y.Matsukawa	任意地点から任意範囲外の拠点を除外
// 2014/10/13 Le Dang Son	define function for API2.0
// 2015/06/08 Y.Matsukawa	スクリプトエラー回避
// 2016/01/26 H.Yasunaga	検索結果が再検索か否かを判別する機能追加（ZdcNearShopResult.researched)
// 2016/01/28 H.Yasunaga	711mapニッセン向けカスタマイズ
// 2016/02/16 H.Osamoto		API2.0 最寄検索時指定企業ID不具合修正
// 2016/03/05 N.Wada		最寄検索結果が0件の場合再検索機能の件数指定不具合修正
// 2016/03/06 N.Wada		最寄検索結果が指定した最小件数未満の場合、再検索
// 2016/03/10 Y.Matsukawa	円検索フラグ
// 2017/04/21 H.Yasunaga	ローソンキャンペーン対応カスタマイズ
// ------------------------------------------------------------
require_once('/home/emap/src/smt/inc/define.inc');

// アイコン情報取得
include("/home/emap/src/smt/inc/define_get_icon.inc");
?>
function ZdcNearShop(){
	this.type = 'ZdcNearShop';
	this.result = false;
	this.text_data = null;
}
ZdcNearShop.prototype.getResult = function(){
	return this.result;
}
ZdcNearShop.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}
ZdcNearShop.prototype.search = function(opts, callback){
	var owner = this;
	<?php //var enc = ZDC_ENC;		mod 2015/06/08 Y.Matsukawa ?>
	var enc = "";
	
	var target_url = "<?PHP echo $D_SSAPI["nkyoten"]; ?>";
	var prm = '';
	prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
	prm += '&cid='+opts.cid;
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&pos='+opts.startPos;
	prm += '&cnt='+opts.maxCount;
	prm += '&enc='+enc;
	prm += '&lat='+opts.lat;
	prm += '&lon='+opts.lon;
	prm += '&latlon='+opts.latlon;
	prm += '&jkn='+opts.jkn;
	prm += '&rad='+opts.radius;
	prm += '&knsu='+opts.limitCount;
	prm += '&exkid='+opts.exceptKid;
	<?php
	// add 2012/10/15 H.Osamoto [
	if (isset($D_ABS_DIST) && $D_ABS_DIST) {
	?>
	prm += '&absdist='+<?php echo ($D_ABS_DIST); ?>;
	<?php
	}
	// add 2012/10/15 H.Osamoto ]
	?>
	<?php
	// add 2016/03/10 Y.Matsukawa [
	if ($D_NKYOTEN_CIRCLE) {
	?>
	prm += '&circle=1';
	<?php
	}
	// add 2016/03/10 Y.Matsukawa ]
	?>
	
	<?php
	// add 2017/04/21 H.Yasunaga ローソンキャンペーン [
	if ($D_LOWSON_CAM_CUST) {
	?>
	prm +=  '&campaignid=<?php echo $p_s2; ?>';
	<?php
	}
	// add 2017/04/21 H.Yasunaga ]
	?>
	
	prm += '&cust='+opts.cust;		<?php // add 2012/11/15 Y.Matsukawa ?>
	prm += '&polycol='+opts.polycol;		<?php // add 2014/03/07 H.Osamoto ?>
	prm += '&exarea='+opts.exarea;		<?php // add 2014/03/12 Y.Matsukawa ?>
	var request_url = target_url+'?'+prm;

	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text,status){
		var result = new ZdcNearShopResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		ZdcEvent.trigger(owner, "end", result);
		if( callback != null ){
			// mod 2013/05/22 H.Osamoto [
			//	callback(result);
			if (result.hitCount == 0) {
				if (opts.researchCount != "") {
					var target_url = "<?PHP echo $D_SSAPI["nkyoten"]; ?>";
					var prm = '';
					prm += '&key=<?PHP echo $D_SSAPI_KEY; ?>';
					prm += '&cid='+opts.cid;
					prm += '&opt=<?PHP echo $cid; ?>';
					prm += '&pos='+opts.startPos;
					prm += '&cnt='+opts.researchCount;
					prm += '&enc='+enc;
					prm += '&lat='+opts.lat;
					prm += '&lon='+opts.lon;
					<?php
					// mod 2016/01/28 H.Yasunaga 711mapニッセンカスタマイズ [
					if ($D_711NISSEN_FIX_ZOOM) { ?>
						//prm += '&latlon=20.0,123.0,45.0,154.0';
						prm += '&latlon=72000000,442800000,162000000,554400000';
					<?php
					} else { ?>
						prm += '&latlon='+opts.latlon;
					<?php
					} 
					
					// mod 2016/01/28 H.Yasunaga ]?>
					prm += '&jkn='+opts.jkn;
					prm += '&rad=1000000';
					prm += '&knsu=1';
					prm += '&exkid='+opts.exceptKid;		// add 2009/10/13 Y.Matsukawa
					<?php
					// add 2016/03/10 Y.Matsukawa [
					if ($D_NKYOTEN_CIRCLE) {
					?>
					prm += '&circle=1';
					<?php
					}
					// add 2016/03/10 Y.Matsukawa ]
					?>
					
					<?php
					// add 2017/04/21 H.Yasunaga ローソンキャンペーン [
					if ($D_LOWSON_CAM_CUST) {
					?>
					prm +=  '&campaignid=<?php echo $p_s2; ?>';
					<?php
					}
					// add 2017/04/21 H.Yasunaga ]
					?>
					
					prm += '&cust='+opts.cust;				<?php // add 2014/03/07 H.Osamoto ?>
					prm += '&polycol='+opts.polycol;		<?php // add 2014/03/07 H.Osamoto ?>
					prm += '&exarea='+opts.exarea;		<?php // add 2014/03/12 Y.Matsukawa ?>
					var request_url = target_url+'?'+prm;
					
					this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
					this.httpReq.request(request_url, function(reference_text,status){
						var result = new ZdcNearShopResult(reference_text, status);
						result.type = owner.type;
						result.options = opts;
						// add 2016/01/26 H.Yasunaga search時の再検索のフラグ追加 [
						result.researched = "1";
						// add 2016/01/26 H.Yasunaga ]
						owner.result = result;
						ZdcEvent.trigger(owner, "end", result);
						if( callback != null ){
							callback(result);
						}
					}, opts.timeout);
				} else {
					callback(result);
				}
			} else {
				callback(result);
			}
			// mod 2013/05/22 H.Osamoto ]
		}
	<?php //}, opts.timeout);	mod 2016/03/18 Y.Matsukawa ?>
	}, opts.timeout, 1, 1);
}
function ZdcNearShopOptions(frewd){
	//default値
	this.cid = '99999999';
	this.startPos = 1;
	this.maxCount = 30;
	this.lat = '';
	this.lon = '';
	this.latlon = '';
	this.jkn = '';
	this.limitCount = 100;    //指定件数
	this.radius  = 50000; //半径
	this.timeout = 60000;
	this.pointFlg = '2'; //暫定対応： default: 2 (ZDC ms)
	this.exceptKid = '';	//除外する拠点
	this.cust = '';		<?php // カスタマイズフラグ		add 2012/11/13 Y.Matsukawa ?>
	this.researchCount = '';	//再検索時取得件数		add 2013/05/22 H.Osamoto
	this.polycol = '';	<?php // add 2014/03/07 H.Osamoto ?>
	this.exarea = '';	<?php // add 2014/03/12 Y.Matsukawa ?>
}
function ZdcNearShopResult(text_data, status){
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
	var rest = ( retcd.charAt(3) == '0' && retcd.charAt(7) == '1' )? true : false;
	
	//Parameter Error Check
	if( retcd.charAt(3) == '1' ){
		ZdcSetErrorStatus.call(this, retcd);
		return;
	}
	//record
	// add 2016/01/26 H.Yasunaga search時の再検索のフラグ追加 再検索した場合は"1"を設定 [
	this.researched = "";
	// add 2016/01/26 ]
	this.retCode  = retcd;
	this.type = '';
	this.status = status;
	this.recCount    = cnt;
	this.hitCount = hitcnt;
	this.rest = rest;
	this.items = [];
	for(var i=0; i<cnt; i++){
		cols = res[i].split('\t');
		if( cols[0] == '' ){ continue; }
		// 拠点縮尺（PC）
		lvl = cols[cols.length-2];
		// mod 2011/07/05 Y.Nakajima
		//if (!lvl || lvl < 1 || lvl >18) lvl = 0;
		if (isNaN(lvl) || !lvl || lvl < 1 || lvl >18) lvl = 0;
		var item = new ZdcNearShopItem(cols,lvl);
		this.items.push(item);
	}
}
function ZdcNearShopItem(cols,lvl){
	this.id   = cols[0];
	this.lat  = cols[1];
	this.lon  = cols[2];
	this.icon = cols[3];
	this.dist = cols[4];
	this.nflg = cols[5];
<?php
	// del 2012/10/10 H.Osamoto [
	//	this.name = cols[6];
	//	this.col1 = cols[7];
	//	this.col2 = cols[8];
	//	this.col3 = cols[9];
	//	this.col4 = cols[10];
	//	this.col5 = cols[11];
	//	this.col6 = cols[12];
	//	this.col7 = cols[13];
	//	this.col8 = cols[14];
	//	this.col9 = cols[15];
	//	this.col10 = cols[16];
	//	this.col11 = cols[17];
	//	this.col12 = cols[18];
	//	this.col13 = cols[19];
	//	this.col14 = cols[20];
	//	this.col15 = cols[21];
	//	this.col16 = cols[22];
	//	this.col17 = cols[23];
	//	this.col18 = cols[24];
	//	this.col19 = cols[25];
	//	this.col20 = cols[16];
	//	this.col21 = cols[17];
	//	this.col22 = cols[18];
	//	this.col23 = cols[19];
	//	this.col24 = cols[20];
	//	this.col25 = cols[21];
	//	this.col26 = cols[22];
	//	this.col27 = cols[23];
	//	this.col28 = cols[24];
	//	this.col29 = cols[25];
	//	this.col30 = cols[26];
	//	this.col31 = cols[27];
	//	this.col32 = cols[28];
	//	this.col33 = cols[29];
	//	this.col34 = cols[30];
	//	this.col35 = cols[31];
	//	this.col36 = cols[32];
	//	this.col37 = cols[33];
	//	this.col38 = cols[34];
	//	this.col39 = cols[35];
	//	this.col40 = cols[36];
	//	this.col41 = cols[37];
	//	this.col42 = cols[38];
	//	this.col43 = cols[39];
	//	this.col44 = cols[40];
	//	this.col45 = cols[41];
	//	this.col46 = cols[42];
	//	this.col47 = cols[43];
	//	this.col48 = cols[44];
	//	this.col49 = cols[45];
	//	this.col50 = cols[46];
	//	this.col51 = cols[47];
	//	this.col52 = cols[48];
	//	this.col53 = cols[49];
	//	this.col54 = cols[50];
	//	this.col55 = cols[51];
	//	this.col56 = cols[52];
	//	this.col57 = cols[53];
	//	this.col58 = cols[54];
	//	this.col59 = cols[55];
	//	this.col60 = cols[56];
	//	this.col61 = cols[57];
	//	this.col62 = cols[58];
	//	this.col63 = cols[59];
	//	this.col64 = cols[60];
	//	this.col65 = cols[61];
	//	this.col66 = cols[62];
	//	this.col67 = cols[63];
	//	this.col68 = cols[64];
	//	this.col69 = cols[65];
	//	this.col70 = cols[66];
	//	this.col71 = cols[67];
	//	this.col72 = cols[68];
	//	this.col73 = cols[69];
	//	this.col74 = cols[70];
	//	this.col75 = cols[71];
	//	this.col76 = cols[72];
	//	this.col77 = cols[73];
	//	this.col78 = cols[74];
	//	this.col79 = cols[75];
	//	this.col80 = cols[76];
	//	this.col81 = cols[77];
	//	this.col82 = cols[78];
	//	this.col83 = cols[79];
	//	this.col84 = cols[80];
	//	this.col85 = cols[81];
	//	this.col86 = cols[82];
	//	this.col87 = cols[83];
	//	this.col88 = cols[84];
	//	this.col89 = cols[85];
	//	this.col90 = cols[86];
	//	this.col91 = cols[87];
	//	this.col92 = cols[88];
	//	this.col93 = cols[89];
	//	this.col94 = cols[90];
	//	this.col95 = cols[91];
	//	this.col96 = cols[92];
	//	this.col97 = cols[93];
	//	this.col98 = cols[94];
	//	this.col99 = cols[95];
	//	this.col100 = cols[96];
	//	this.col101 = cols[97];
	//	this.col102 = cols[98];
	//	this.col103 = cols[99];
	//	this.col104 = cols[100];
	//	this.col105 = cols[101];
	//	this.col106 = cols[102];
	//	this.col107 = cols[103];
	//	this.col108 = cols[104];
	//	this.col109 = cols[105];
	//	this.col110 = cols[106];
	//	this.col111 = cols[107];
	//	this.col112 = cols[108];
	//	this.col113 = cols[109];
	//	this.col114 = cols[110];
	//	this.col115 = cols[111];
	//	this.col116 = cols[112];
	//	this.col117 = cols[113];
	//	this.col118 = cols[114];
	//	this.col119 = cols[115];
	//	this.col120 = cols[116];
	//	this.col121 = cols[117];
	//	this.col122 = cols[118];
	//	this.col123 = cols[119];
	//	this.col124 = cols[120];
	//	this.col125 = cols[121];
	//	this.col126 = cols[122];
	//	this.col127 = cols[123];
	//	this.col128 = cols[124];
	//	this.col129 = cols[125];
	//	this.col130 = cols[126];
	//	this.col131 = cols[127];
	//	this.col132 = cols[128];
	//	this.col133 = cols[129];
	//	this.col134 = cols[130];
	//	this.col135 = cols[131];
	//	this.col136 = cols[132];
	//	this.col137 = cols[133];
	//	this.col138 = cols[134];
	//	this.col139 = cols[135];
	//	this.col140 = cols[136];
	//	this.col141 = cols[137];
	//	this.col142 = cols[138];
	//	this.col143 = cols[139];
	//	this.col144 = cols[140];
	//	this.col145 = cols[141];
	//	this.col146 = cols[142];
	//	this.col147 = cols[143];
	//	this.col148 = cols[144];
	//	this.col149 = cols[145];
	//	this.col150 = cols[146];
	//	this.col151 = cols[147];
	//	this.col152 = cols[148];
	//	this.col153 = cols[149];
	//	this.col154 = cols[150];
	//	this.col155 = cols[151];
	//	this.col156 = cols[152];
	//	this.col157 = cols[153];
	//	this.col158 = cols[154];
	//	this.col159 = cols[155];
	//	this.col160 = cols[156];
	//	this.col161 = cols[157];
	//	this.col162 = cols[158];
	//	this.col163 = cols[159];
	//	this.col164 = cols[160];
	//	this.col165 = cols[161];
	//	this.col166 = cols[162];
	//	this.col167 = cols[163];
	//	this.col168 = cols[164];
	//	this.col169 = cols[165];
	//	this.col170 = cols[166];
	//	this.col171 = cols[167];
	//	this.col172 = cols[168];
	//	this.col173 = cols[169];
	//	this.col174 = cols[170];
	//	this.col175 = cols[171];
	//	this.col176 = cols[172];
	//	this.col177 = cols[173];
	//	this.col178 = cols[174];
	//	this.col179 = cols[175];
	//	this.col180 = cols[176];
	//	this.col181 = cols[177];
	//	this.col182 = cols[178];
	//	this.col183 = cols[179];
	//	this.col184 = cols[180];
	//	this.col185 = cols[181];
	//	this.col186 = cols[182];
	//	this.col187 = cols[183];
	//	this.col188 = cols[184];
	//	this.col189 = cols[185];
	//	this.col190 = cols[186];
	//	this.col191 = cols[187];
	//	this.col192 = cols[188];
	//	this.col193 = cols[189];
	//	this.col194 = cols[190];
	//	this.col195 = cols[191];
	//	this.col196 = cols[192];
	//	this.col197 = cols[193];
	//	this.col198 = cols[194];
	//	this.col199 = cols[195];
	//	this.col200 = cols[196];
	// del 2012/10/10 H.Osamoto ]
?>
<?php
// add 2012/10/10 H.Osamoto [
if ($D_KYO_COL_NAME[0] && count($D_KYO_COL_NAME[0])) {
	foreach ($D_KYO_COL_NAME[0] as $i=>$colnm) {
		if ($colnm) {
?>
	this.<?php echo $colnm; ?> = cols[<?php echo ($i + 6); ?>];
<?php
		}
	}
	if ($D_ICONID_COL) {
?>
	if (this.<?php echo $D_ICONID_COL; ?> && ZdcEmapIconImg[this.<?php echo $D_ICONID_COL; ?>])
		this.icon = this.<?php echo $D_ICONID_COL; ?>;
<?php
	}
}
// add 2012/10/10 H.Osamoto ]
?>
	this.lvl = lvl;
}

var ZdcEmapNearShop = new ZdcNearShop();

// add 2014/10/13 Le Dang Son [
/**
 * Change status error
 */
if(typeof ZdcSetErrorStatus == 'undefined'){
	ZdcSetErrorStatus = function (_165,st){var _167;if(st==undefined){var _168=_165.charAt(4);var _169=_165.slice(3,5);if(_168=="9"){_167=1;}else{if(_165.substr(4,4)=="1009"){_167=5;}else{if(_168=="2"){_167=6;}else{if(_168=="6"||_168=="7"||_168=="8"||_169=="15"){_167=2;}else{_167=9;}}}}}else{_167=st;}this.retCode=_165||"";this.type="";this.status=_167;this.recCount=0;this.hitCount=0;this.rest=false;this.items=[];}
}

/**
 * NearShop Object
 */
function ZdcNearShop2(){
	this.type = 'ZdcNearShop2';
	this.result = false;
	this.text_data = null;
}

/**
 * NearShop get result search
 */
ZdcNearShop2.prototype.getResult = function(){
	return this.result;
}

/**
 * Destroy search
 */
ZdcNearShop2.prototype.abort = function(){
	if( this.httpReq ){
		this.httpReq.abort();
	}
}

/**
 * Search near shop
 */
ZdcNearShop2.prototype.search = function(opts, callback){
	var owner = this;
	var enc = 'UTF-8';//ZDC_ENC
	
	//var target_url = "http://127.0.0.1/cgi/nkyoten.cgi";		mod 2015/02/27 Y.Matsukawa
	var target_url = "<?PHP echo $D_SSAPI["nkyoten"]; ?>";
	var prm = '';
	prm += '&key=41nQhzBGnwsvBynAXvBlnAof9MmgYPBlidC5SaXurmA7fB6zTbrxmzTZrxDzTzngjzFtmwIXFnmgrzFhmAbPTo';
	prm += '&cid='+opts.cid;
	//	prm += '&opt=chpracttest';	mod 2016/02/16 H.Osamoto
	prm += '&opt=<?PHP echo $cid; ?>';
	prm += '&pos='+opts.startPos;
	prm += '&cnt='+opts.maxCount;
	prm += '&enc='+enc;
	prm += '&lat='+opts.lat;
	prm += '&lon='+opts.lon;
	prm += '&latlon='+opts.latlon;
	prm += '&jkn='+opts.jkn;
	prm += '&rad='+opts.radius;
	prm += '&knsu='+opts.limitCount;
	prm += '&exkid='+opts.exceptKid;
	<?php
	// add 2016/03/10 Y.Matsukawa [
	if ($D_NKYOTEN_CIRCLE) {
	?>
	prm += '&circle=1';
	<?php
	}
	// add 2016/03/10 Y.Matsukawa ]
	?>
	prm += '&cust='+opts.cust;
	prm += '&polycol='+opts.polycol;
	prm += '&exarea='+opts.exarea;
	var request_url = target_url+'?'+prm;

	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text,status){
		var result = new ZdcNearShopResult2(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		ZDC.trigger(owner, 'end', result)
		if( callback != null ){
			// mod 2013/05/22 H.Osamoto [
			//	callback(result);
			<?php //if (result.hitCount == 0) {	mod 2016/03/06 N.Wada ?>
			if (result.hitCount == 0 || result.hitCount < opts.minCount) {
				if (opts.researchCount != "") {
					//var target_url = "http://127.0.0.1/cgi/nkyoten.cgi";		mod 2015/02/27 Y.Matsukawa
					var target_url = "<?PHP echo $D_SSAPI["nkyoten"]; ?>";
					var prm = '';
					prm += '&key=41nQhzBGnwsvBynAXvBlnAof9MmgYPBlidC5SaXurmA7fB6zTbrxmzTZrxDzTzngjzFtmwIXFnmgrzFhmAbPTo';
					prm += '&cid='+opts.cid;
					//	prm += '&opt=chpracttest';	mod 2016/02/16 H.Osamoto
					prm += '&opt=<?PHP echo $cid; ?>';
					prm += '&pos='+opts.startPos;
					prm += '&cnt='+opts.researchCount;
					prm += '&enc='+enc;
					prm += '&lat='+opts.lat;
					prm += '&lon='+opts.lon;
					prm += '&latlon='+opts.latlon;
					prm += '&jkn='+opts.jkn;
					prm += '&rad=1000000';
					<?php //prm += '&knsu=1';	mod 2016/03/05 N.Wada ?>
					prm += '&knsu='+opts.researchCount;
					prm += '&exkid='+opts.exceptKid;		// add 2009/10/13 Y.Matsukawa
					<?php
					// add 2016/03/10 Y.Matsukawa [
					if ($D_NKYOTEN_CIRCLE) {
					?>
					prm += '&circle=1';
					<?php
					}
					// add 2016/03/10 Y.Matsukawa ]
					?>
					prm += '&cust='+opts.cust;
					prm += '&polycol='+opts.polycol;
					prm += '&exarea='+opts.exarea;
					var request_url = target_url+'?'+prm;
					
					this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
					this.httpReq.request(request_url, function(reference_text,status){
						var result = new ZdcNearShopResult2(reference_text, status);
						result.type = owner.type;
						result.options = opts;
						owner.result = result;
						ZDC.trigger(owner, 'end', result)
						if( callback != null ){
							callback(result);
						}
					}, opts.timeout);
				} else {
					callback(result);
				}
			} else {
				callback(result);
			}
		// mod 2013/05/22 H.Osamoto ]
		}
	<?php //}, opts.timeout);	mod 2016/03/18 Y.Matsukawa ?>
	}, opts.timeout, 1, 1);
}
function ZdcNearShopOptions2(frewd){
	this.cid = '99999999';
	this.startPos = 1;
	this.maxCount = 30;
	this.lat = '';
	this.lon = '';
	this.latlon = '';
	this.jkn = '';
	this.limitCount = 100;
	this.radius  = 50000;
	this.timeout = 60000;
	this.pointFlg = '2';
	this.exceptKid = '';
	this.cust = '';
	this.researchCount = '';
	this.polycol = '';
	this.exarea = '';
}
function ZdcNearShopResult2(text_data, status){
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
	var rest = ( retcd.charAt(3) == '0' && retcd.charAt(7) == '1' )? true : false;
	
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
	this.rest = rest;
	this.items = [];
	for(var i=0; i<cnt; i++){
		cols = res[i].split('\t');
		if( cols[0] == '' ){
			continue;
		}
		lvl = cols[cols.length-2];
		if (isNaN(lvl) || !lvl || lvl < 1 || lvl >18) lvl = 0;
		var item = new ZdcNearShopItem2(cols,lvl);
		this.items.push(item);
	}
}
function ZdcNearShopItem2(cols, lvl){
	this.id   = cols[0];
	this.lat  = cols[1];
	this.lon  = cols[2];
	this.icon = cols[3];
	this.dist = cols[4];
	this.nflg = cols[5];
	this.name = cols[6];
	this.addr = cols[7];
	this.col_04 = cols[8];
	this.col_05 = cols[9];
	this.col_06 = cols[10];
	this.col_07 = cols[11];
	this.col_08 = cols[12];
	this.col_09 = cols[13];
	this.col_10 = cols[14];
	this.col_11 = cols[15];
	this.col_12 = cols[16];
	this.col_13 = cols[17];
	this.col_14 = cols[18];
	this.col_16 = cols[19];
	this.col_17 = cols[20];
	this.lvl = lvl;
}

var ZdcEmapNearShop2 = new ZdcNearShop2();
// add 2014/10/13 Le Dang Son ]
