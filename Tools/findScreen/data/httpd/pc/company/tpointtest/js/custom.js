/* カスタマイズ用のJavaScriptコードをここに記述してください */


/* Myエリアデータ操作系 */
function MyAreaNameUpdt(frm) {
	if (frm.myarea_name.value == "") {
		window.alert('Myエリア名称が未入力の為、登録できません。');
	} else if (frm.myarea_name.value.length > 50) {
		window.alert('Myエリア名称の文字数が\n50文字を超えている為、登録できません。');
	} else if (!checkKeyword(frm.myarea_name.value)) {
		window.alert('機種依存文字が含まれている為、登録できません。');
	} else {
		ret = window.confirm("名称を「"+frm.myarea_name.value+"」に変更しますか？");
		if (ret == true) {
			frm.type.value = "MyAreaNameUpdt";
			frm.submit();
		}
	}
}
function ChangeDispOrderUp(frm) {
	frm.type.value = "MyAreaOrderUpdtUp";
	frm.submit();
}
function ChangeDispOrderDown(frm) {
	frm.type.value = "MyAreaOrderUpdtDown";
	frm.submit();
}
function DeleteMyarea(frm, myarea_name) {
	if(window.confirm('「' + frm.myarea_name.value + '」を本当に削除しますか？')){
		frm.type.value = "MyAreaDelete";
		frm.submit();
	} else {
		window.alert('キャンセルされました。');
	}
}

function key_press(event, frm){
	if(event.keyCode == 13){
		MyAreaNameUpdt(frm);
	}
}
function key_press_myarea_add(event, p_s2, myar, lm, add_cnt){
	if(event.keyCode == 13){
		ZdcEmapMyAreaAdd(p_s2, "", myar, lm, add_cnt);
	}
}

/* 表示画像切り替え（Myエリアに追加） */
function ImgChangeMouseOver(cr_dir){
	var nochange_flg = false;
	var img_url = document.MyAreaAdd.src;
	var w_array = img_url.split("/");
	for (i=0; i < w_array.length; i++){
		if (w_array[i] == "b_registering.jpg"){
			nochange_flg = true;
		}
	}
	if (nochange_flg == false){
		document.MyAreaAdd.src = cr_dir+"images/b_add_o.jpg";
	}
}
function ImgChangeMouseOut(cr_dir){
	var nochange_flg = false;
	var img_url = document.MyAreaAdd.src;
	var w_array = img_url.split("/");
	for (i=0; i < w_array.length; i++){
		if (w_array[i] == "b_registering.jpg"){
			nochange_flg = true;
		}
	}
	if (nochange_flg == false){
		document.MyAreaAdd.src = cr_dir+"images/b_add.jpg";
	}
}

/* 表示画像切り替え（クーポン） */
function CouponImgChangeMouseOver(){
	document.couponImg.src = "https://tsite.jp/pc/img/map/b_coupon_o.jpg";
}

function CouponImgChangeMouseOut(){
	document.couponImg.src = "https://tsite.jp/pc/img/map/b_coupon.jpg";
}

/* 表示画像切り替え（Myエリア編集） */
function AddImgChangeMouseOver(cr_dir){
	document.MyAreaAddEdit.src = cr_dir+"images/b_add-search_o.jpg";
}

function AddImgChangeMouseOut(cr_dir){
	document.MyAreaAddEdit.src = cr_dir+"images/b_add-search.jpg";
}

/* Myエリア追加画面表示切替 */
function changeScreen(color, cr_dir) {
	document.getElementById('myareaWrapper').style.display = "block";

	document.MyAreaAdd.src = cr_dir+"images/b_registering.jpg";
	timerID = setInterval("setForIE6('" + cr_dir + "')",1);
	document.getElementById("ZdcEmapSearchWindow").style.backgroundColor = color;
}
function setForIE6(cr_dir) {
	document.MyAreaAdd.src = cr_dir+"images/b_registering.jpg";
	clearInterval(timerID);
}
function cancelMyareaAdd(cr_dir) {
	document.getElementById('myareaWrapper').style.display = "none";
	document.MyAreaAdd.src = cr_dir+"images/b_add.jpg";
	
	obj = document.getElementById('myareaWrapper');
	obj.style.zIndex = -1;
	document.getElementById("ZdcEmapSearchWindow").style.backgroundColor = "#ffffff";
	ZdcEmapSearchCancel();
}
function comitMyareaAdd(cr_dir, status, url) {
	document.getElementById("ZdcEmapSearchWindow").style.backgroundColor = "#ffffff";
	if (status == 1) {
		document.MyAreaAdd.src = cr_dir+"images/b_registered.jpg";
	} else {
		document.MyAreaAdd.src = cr_dir+"images/b_add.jpg";
	}
	document.getElementById('myareaWrapper').style.display = "none";
	location.href = url;
}

/* Myエリア追加（Tサイト遷移用）*/
function goTsite(flg){
	var aZdcPoint = ZdcEmapMapObj.getMapLocation();
	lat = aZdcPoint.my;
	lon = aZdcPoint.mx;
	var loc = encodeURIComponent("&lat="+lat+"&lon="+lon);
	if (flg == "1") {
		var url = "https://stg.tsite.jp/tm/pc/login/STKIp0003001.do?ST_SITE_ID=4009&MOVE_ID=002&DYNAMIC_URL="+loc;
	} else {
		var url = "https://tsite.jp/tm/pc/login/STKIp0003001.do?ST_SITE_ID=4009&MOVE_ID=002&DYNAMIC_URL="+loc;
	}

	parent.location.href = url;
}
/* クーポンサイト遷移*/
function CouponSite(url){
	parent.location.href = url;
}

function myareaLinkDisp(){
	linkObj1 = document.getElementById('area_name_link1');
	linkObj2 = document.getElementById('area_name_link2');
	linkObj3 = document.getElementById('area_name_link3');
	linkObj4 = document.getElementById('area_name_link4');
	linkObj5 = document.getElementById('area_name_link5');

	textObj1 = document.getElementById('area_name_text1');
	textObj2 = document.getElementById('area_name_text2');
	textObj3 = document.getElementById('area_name_text3');
	textObj4 = document.getElementById('area_name_text4');
	textObj5 = document.getElementById('area_name_text5');

	if (linkObj1 && textObj1) {
		if (MYAREA_SEL1 == 1) {
			linkObj1.style.display= "none";
			textObj1.style.display= "";
		} else {
			linkObj1.style.display= "";
			textObj1.style.display= "none";
		}
	}

	if (linkObj2 && textObj2) {
		if (MYAREA_SEL2 == 1) {
			linkObj2.style.display= "none";
			textObj2.style.display= "";
		} else {
			linkObj2.style.display= "";
			textObj2.style.display= "none";
		}
	}

	if (linkObj3 && textObj3) {
		if (MYAREA_SEL3 == 1) {
			linkObj3.style.display= "none";
			textObj3.style.display= "";
		} else {
			linkObj3.style.display= "";
			textObj3.style.display= "none";
		}
	}

	if (linkObj4 && textObj4) {
		if (MYAREA_SEL4 == 1) {
			linkObj4.style.display= "none";
			textObj4.style.display= "";
		} else {
			linkObj4.style.display= "";
			textObj4.style.display= "none";
		}
	}

	if (linkObj5 && textObj5) {
		if (MYAREA_SEL5 == 1) {
			linkObj5.style.display= "none";
			textObj5.style.display= "";
		} else {
			linkObj5.style.display= "";
			textObj5.style.display= "none";
		}
	}
}

/* 機種依存文字チェック */
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

