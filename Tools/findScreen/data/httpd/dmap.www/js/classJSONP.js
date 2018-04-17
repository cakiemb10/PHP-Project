/**
 * DmapJSONPオブジェクトを生成します。
 * @class JSONP通信を制御します。
 * @constructor
 */
var DmapJSONP = {
	callback: {},
	/**
	 * クエリ文字列を含めたURLを生成します。
	 * @param {String} base ベースURL
	 * @param {Array} args パラメータ
	 * @return {String} URL
	 */
	serialize: function (base, args) {
		var query = [];
		for (var key in args) {
			query.push(
				encodeURIComponent(key) + '=' +
				encodeURIComponent(args[key])
			);
		}
		return base + '?' + query.join('&');
	},
	/**
	 * JSONPでデータを取得します。
	 * @param {String} url URL
	 * @param {Array} params パラメータ
	 * @param {Function} callback コールバック関数
	 * @return {void}
	 */
	get: function (url, params, callback) {
		/* パラメータ名に'callback'が使われている場合は、重複するのでエラー */
		if (params["callback"]) return;
		/* ID生成 */
		do {
			var id = Math.floor(Math.random() * 1E10);
		} while(DmapJSONP.callback[id]);
		/* レスポンスハンドラを登録 */
		DmapJSONP.callback[id] = callback;
		/* パラメータにハンドラ名を追加 */
		params["callback"] = 'DmapJSONP.callback['+id+']';
		/* scriptタグ生成 */
		var req = document.createElement('script');
		/* JSONの読み込み完了した場合 */
		req.onload = req.onreadystatechange = function () {
			if (!this.readyState ||
				this.readyState === "loaded" ||
				this.readyState === "complete") {
				this.onreadystatechange = null;
				/* タイムアウト処理を消去 */
				clearTimeout(timer_id);
				/* 追加したscriptタグを削除 */
				if (req && req.parentNode) document.body.removeChild(req);
				/* 登録したレスポンスハンドラを削除 */
				delete DmapJSONP.callback[id];
			}
		};
		/* JSONの読み込みがエラーの場合 */
		req.onerror = function() {
			/* タイムアウト処理を消去 */
			clearTimeout(timer_id);
			/* 追加したscriptタグを削除 */
			if (req && req.parentNode) document.body.removeChild(req);
			/* レスポンスハンドラにエラーレスポンスを渡す */
			DmapJSONP.callback[id]({code: "102",text: "timeout"}, null);
			/* 登録したレスポンスハンドラを削除 */
			delete DmapJSONP.callback[id];
		};
		/* タイムアウト処理を設定（15秒） */
		var timer_id = setTimeout(function() {
			try {
				/* 追加したscriptタグを削除 */
				if (req && req.parentNode) document.body.removeChild(req);
				/* レスポンスハンドラにエラーレスポンスを渡す */
				DmapJSONP.callback[id]({code: "102",text: "timeout"}, null);
				/* レスポンスハンドラを空のfunctionに変更 */
				DmapJSONP.callback[id] = function () {};
			} catch (d) {
			}
		}, 15000);
		/* 生成したscriptタグにURL等を追加して、bodyタグに追加 */
		req.async = true;
		req.type = 'text/javascript';
		req.src = DmapJSONP.serialize(url, params);
		document.body.appendChild(req);
	}
}
