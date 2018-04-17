var map, smap, responseType, element,
lat = 35.6778614, lon = 139.7703167;

function loadMap(mapNo, resType) {
    
    /* URLのパラメータを解析する */
    param = getParams();

    /* レスポンスタイプを保存 */
    responseType = resType;
    
    /* 表示領域のサイズを設定する */
    element = document.getElementById('area');
    element.style.width = param["dispWidth"] + 'px';
    element.style.height = param["dispHeight"] + 'px';
    
    map = new ZDC.Map(
                      document.getElementById('ZMap'),
                      {
                        latlon: new ZDC.LatLon(lat, lon),
                        zoom: 10
                      }
                      );
    /* 路線図を表示 */
    var obj = {
    mapNo: mapNo,
    callback: showRailwayMap,
    mainMap: element,
    };
    smap = new ZDC.RailwayMap(obj);
};

function getParams() {
    if (1 < document.location.search.length) {
        // 最初の1文字 (?記号) を除いた文字列を取得する
        var query = document.location.search.substring(1);

        // クエリの区切り記号 (&) で文字列を配列に分割する
        var parameters = query.split('&');

        var result = new Object();
        for (var i = 0; i < parameters.length; i++) {
            // パラメータ名とパラメータ値に分割する
            var element = parameters[i].split('=');

            var paramName = decodeURIComponent(element[0]);
            var paramValue = decodeURIComponent(element[1]);

            // パラメータ名をキーとして連想配列に追加する
            result[paramName] = decodeURIComponent(paramValue);
        }
        return result;
    }
    return null;
}

/* 「路線図表示」ボタン押下時に動作 */
function addRailwayMap(mapNo, resType) {
    /* レスポンスタイプを保存 */
    responseType = resType;
    
    /* 再作成のために、路線図があれば消す */
    if (smap) {
        smap.removeMainMap();
    }
        
    /* 路線図を表示 */
    var obj = {
    mapNo: mapNo,
    callback: showRailwayMap,
    mainMap: element,
    };
    smap = new ZDC.RailwayMap(obj);
};

/* 路線図の駅クリック時に動作 */
var showRailwayMap = function(rtn) {
    /* JSON形式の緯度経度情報に変換 */
    var jsonResult = JSON.stringify({stationName: rtn.stationName,lat: ZDC.degToms(rtn.latlon.lat), lon: ZDC.degToms(rtn.latlon.lon)});
    if (responseType == 'link') {
        /* データをURLエンコード */
        jsonResult = encodeURI(jsonResult);
        
        /* 適当なschemeで情報を返す(link) */
        var iframe = document.createElement('iframe');
        iframe.setAttribute('src', 'showRailwayMap://' + jsonResult);
     
        document.documentElement.appendChild(iframe);
        iframe.parentNode.removeChild(iframe);
        iframe = null;
    } else if (responseType == 'alert') {
        /* アラートで情報を返す(alert) */
        alert('showRailwayMap://' + jsonResult);
    }
};
