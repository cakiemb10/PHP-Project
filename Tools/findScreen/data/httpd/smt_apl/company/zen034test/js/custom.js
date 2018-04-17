function chgCondTab(n) {
	for (i=1; i<=3; i++) {
		var cond = document.getElementById('custCondTable'+i);
		if (cond) {
			if (i == n) {
				cond.style.display = 'block';
			} else {
				cond.style.display = 'none';
			}
		}
		var tab = document.getElementById('searchCondTab'+i);
		if (tab) {
			if (i == n) {
				tab.className = 'searchCondTabOn';
			} else {
				tab.className = 'searchCondTabOff';
			}
		}
	}
}
