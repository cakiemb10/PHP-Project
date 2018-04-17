<?PHP
// ------------------------------------------------------------
// 汎用javasctipt 最寄拠点CGI読み込みインターフェイス
// 
// 開発履歴
// 2007/03/01 bando@D&I
//     新規開発
// 2009/02/06 Y.Matsukawa	拠点FWによる拠点絞り込み
// 2009/09/04 Y.Matsukawa	拠点縮尺
// 2009/10/13 Y.Matsukawa	最寄り拠点一覧に詳細拠点を出さない
// 2009/11/07 Y.Matsukawa	拠点項目拡張（50→200）
// 2011/07/07 H.Osamoto		マツキヨ用API2.0対応版
// ------------------------------------------------------------
include("d_serv_emap.inc");
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
	//var enc = ZDC_ENC;	mod 2011/07/07 H.osamoto
	var enc = "EUC";
	
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
	//prm += '&jkn='+encodeURI(opts.jkn);		mod 2009/02/06 Y.Matsukawa
	prm += '&jkn='+opts.jkn;
	prm += '&rad='+opts.radius;
	prm += '&knsu='+opts.limitCount;
	prm += '&exkid='+opts.exceptKid;		// add 2009/10/13 Y.Matsukawa
	prm += '&hour=1';		// add 2011/07/07 H.Osamoto
	var request_url = target_url+'?'+prm;
	
	this.httpReq = new ZdcEmapHttpRequest('EUC', 'EUC');
	this.httpReq.request(request_url, function(reference_text,status){
		var result = new ZdcNearShopResult(reference_text, status);
		result.type = owner.type;
		result.options = opts;
		owner.result = result;
		//ZdcEvent.trigger(owner, "end", result);	mod 2011/07/07 H.osamoto
		ZDC.trigger(owner, "end", result);
		if( callback != null ){
			callback(result);
		}
	}, opts.timeout);
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
	this.exceptKid = '';	//除外する拠点		add 2009/10/13 Y.Matsukawa
}
function ZdcNearShopResult(text_data, status){
	
	if( text_data == null ){
		ZdcSetErrorStatus.call(this, '', status);
		return;
	}
	
	//header
	var res = new Array();
	//res = text_data.split(ZDC_HTTP_DMT[ZDC_ENC]);
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
		if( cols[0] == '' ){ continue; }
		// add 2009/09/04 Y.Matsukawa [
		// 拠点縮尺（PC）
		lvl = cols[cols.length-2];
		if (!lvl || lvl < 1 || lvl >18) lvl = 0;
		// add 2009/09/04 Y.Matsukawa ]
		//var item = new ZdcNearShopItem(cols);		mod 2009/09/04 Y.Matsukawa
		var item = new ZdcNearShopItem(cols,lvl);
		this.items.push(item);
	}
}
//function ZdcNearShopItem(cols){		mod 2009/09/04 Y.Matsukawa
function ZdcNearShopItem(cols,lvl){
	this.id   = cols[0];
	this.lat  = cols[1];
	this.lon  = cols[2];
	this.icon = cols[3];
	this.dist = cols[4];
	this.nflg = cols[5];
	this.name = cols[6];
	this.col1 = cols[7];
	this.col2 = cols[8];
	this.col3 = cols[9];
	this.col4 = cols[10];
	this.col5 = cols[11];
	this.col6 = cols[12];
	this.col7 = cols[13];
	this.col8 = cols[14];
	this.col9 = cols[15];
	this.col10 = cols[16];
	this.col11 = cols[17];
	this.col12 = cols[18];
	this.col13 = cols[19];
	this.col14 = cols[20];
	this.col15 = cols[21];
	this.col16 = cols[22];
	this.col17 = cols[23];
	this.col18 = cols[24];
	this.col19 = cols[25];
	this.col20 = cols[16];
	this.col21 = cols[17];
	this.col22 = cols[18];
	this.col23 = cols[19];
	this.col24 = cols[20];
	this.col25 = cols[21];
	this.col26 = cols[22];
	this.col27 = cols[23];
	this.col28 = cols[24];
	this.col29 = cols[25];
	this.col30 = cols[26];
	this.col31 = cols[27];
	this.col32 = cols[28];
	this.col33 = cols[29];
	this.col34 = cols[30];
	this.col35 = cols[31];
	this.col36 = cols[32];
	this.col37 = cols[33];
	this.col38 = cols[34];
	this.col39 = cols[35];
	this.col40 = cols[36];
	this.col41 = cols[37];
	this.col42 = cols[38];
	this.col43 = cols[39];
	this.col44 = cols[40];
	this.col45 = cols[41];
	this.col46 = cols[42];
	this.col47 = cols[43];
	this.col48 = cols[44];
	this.col49 = cols[45];
	this.col50 = cols[46];
	// add 2009/11/07 Y.Matsukawa [
	this.col51 = cols[47];
	this.col52 = cols[48];
	this.col53 = cols[49];
	this.col54 = cols[50];
	this.col55 = cols[51];
	this.col56 = cols[52];
	this.col57 = cols[53];
	this.col58 = cols[54];
	this.col59 = cols[55];
	this.col60 = cols[56];
	this.col61 = cols[57];
	this.col62 = cols[58];
	this.col63 = cols[59];
	this.col64 = cols[60];
	this.col65 = cols[61];
	this.col66 = cols[62];
	this.col67 = cols[63];
	this.col68 = cols[64];
	this.col69 = cols[65];
	this.col70 = cols[66];
	this.col71 = cols[67];
	this.col72 = cols[68];
	this.col73 = cols[69];
	this.col74 = cols[70];
	this.col75 = cols[71];
	this.col76 = cols[72];
	this.col77 = cols[73];
	this.col78 = cols[74];
	this.col79 = cols[75];
	this.col80 = cols[76];
	this.col81 = cols[77];
	this.col82 = cols[78];
	this.col83 = cols[79];
	this.col84 = cols[80];
	this.col85 = cols[81];
	this.col86 = cols[82];
	this.col87 = cols[83];
	this.col88 = cols[84];
	this.col89 = cols[85];
	this.col90 = cols[86];
	this.col91 = cols[87];
	this.col92 = cols[88];
	this.col93 = cols[89];
	this.col94 = cols[90];
	this.col95 = cols[91];
	this.col96 = cols[92];
	this.col97 = cols[93];
	this.col98 = cols[94];
	this.col99 = cols[95];
	this.col100 = cols[96];
	this.col101 = cols[97];
	this.col102 = cols[98];
	this.col103 = cols[99];
	this.col104 = cols[100];
	this.col105 = cols[101];
	this.col106 = cols[102];
	this.col107 = cols[103];
	this.col108 = cols[104];
	this.col109 = cols[105];
	this.col110 = cols[106];
	this.col111 = cols[107];
	this.col112 = cols[108];
	this.col113 = cols[109];
	this.col114 = cols[110];
	this.col115 = cols[111];
	this.col116 = cols[112];
	this.col117 = cols[113];
	this.col118 = cols[114];
	this.col119 = cols[115];
	this.col120 = cols[116];
	this.col121 = cols[117];
	this.col122 = cols[118];
	this.col123 = cols[119];
	this.col124 = cols[120];
	this.col125 = cols[121];
	this.col126 = cols[122];
	this.col127 = cols[123];
	this.col128 = cols[124];
	this.col129 = cols[125];
	this.col130 = cols[126];
	this.col131 = cols[127];
	this.col132 = cols[128];
	this.col133 = cols[129];
	this.col134 = cols[130];
	this.col135 = cols[131];
	this.col136 = cols[132];
	this.col137 = cols[133];
	this.col138 = cols[134];
	this.col139 = cols[135];
	this.col140 = cols[136];
	this.col141 = cols[137];
	this.col142 = cols[138];
	this.col143 = cols[139];
	this.col144 = cols[140];
	this.col145 = cols[141];
	this.col146 = cols[142];
	this.col147 = cols[143];
	this.col148 = cols[144];
	this.col149 = cols[145];
	this.col150 = cols[146];
	this.col151 = cols[147];
	this.col152 = cols[148];
	this.col153 = cols[149];
	this.col154 = cols[150];
	this.col155 = cols[151];
	this.col156 = cols[152];
	this.col157 = cols[153];
	this.col158 = cols[154];
	this.col159 = cols[155];
	this.col160 = cols[156];
	this.col161 = cols[157];
	this.col162 = cols[158];
	this.col163 = cols[159];
	this.col164 = cols[160];
	this.col165 = cols[161];
	this.col166 = cols[162];
	this.col167 = cols[163];
	this.col168 = cols[164];
	this.col169 = cols[165];
	this.col170 = cols[166];
	this.col171 = cols[167];
	this.col172 = cols[168];
	this.col173 = cols[169];
	this.col174 = cols[170];
	this.col175 = cols[171];
	this.col176 = cols[172];
	this.col177 = cols[173];
	this.col178 = cols[174];
	this.col179 = cols[175];
	this.col180 = cols[176];
	this.col181 = cols[177];
	this.col182 = cols[178];
	this.col183 = cols[179];
	this.col184 = cols[180];
	this.col185 = cols[181];
	this.col186 = cols[182];
	this.col187 = cols[183];
	this.col188 = cols[184];
	this.col189 = cols[185];
	this.col190 = cols[186];
	this.col191 = cols[187];
	this.col192 = cols[188];
	this.col193 = cols[189];
	this.col194 = cols[190];
	this.col195 = cols[191];
	this.col196 = cols[192];
	this.col197 = cols[193];
	this.col198 = cols[194];
	this.col199 = cols[195];
	this.col200 = cols[196];
	// add 2009/11/07 Y.Matsukawa ]
	this.lvl = lvl;		// add 2009/09/04 Y.Matsukawa
}
