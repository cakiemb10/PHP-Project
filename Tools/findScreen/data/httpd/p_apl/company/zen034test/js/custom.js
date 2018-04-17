function chgTopCondTab(n) {
	for (i=1; i<=3; i++) {
		var cond = document.getElementById('searchTopCondTable'+i);
		if (cond) {
			if (i == n) {
				cond.style.display = 'block';
			} else {
				cond.style.display = 'none';
			}
		}
		var tab = document.getElementById('searchTopCondTab'+i);
		if (tab) {
			if (i == n) {
				tab.className = 'searchTopCondTabOn';
			} else {
				tab.className = 'searchTopCondTabOff';
			}
		}
	}
	popMapReset(n);
}
function popMapReset(n) {
//	var popOffset = {1:170, 2:50, 3:210, 4:340};
//	var popTop = [
//		["mapLargeHokaido",75],
//		["mapLargeTohoku",80],
//		["mapLargeKanto",250],
//		["mapLargeChubu",200],
//		["mapLargeKinki",260],
//		["mapLargeChugoku",230],
//		["mapLargeShikoku",300],
//		["mapLargeKyushu",220],
//		["mapLargeKyushu",220]
//	];
//	for (i=0; i<popTop.length; i++) {
//		var pop = document.getElementById(popTop[i][0]);
//		if (pop) {
//			var top = popOffset[n] + popTop[i][1];
//			pop.style.top = top+'px';
//		}
//	}
}

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
