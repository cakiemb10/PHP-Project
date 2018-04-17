function loadimg(ptn) {
	var img_id = "img"+ptn;
	var img = document.getElementById(img_id);
	img.src = "http://test.e-map.ne.jp/pdev/devstamptest/mi.htm?ptn="+ptn;
	img.onload = function() {
		if (ptn <= 3) {
			ptn++;
			//loadimg();
			loadimg(ptn);
    	} else {
			return;
		}
	}
}

