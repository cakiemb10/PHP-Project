<?php
/**
* 電車乗換ルート探索IF
* @param string callback コールバック関数名
* @param string stlat 出発地（緯度）
* @param string stlon 出発地（経度）
* @param string edlat 目的地（緯度）
* @param string edlon 目的地（経度）
* @param integer [ms1] 経由駅コード１
* @param integer [ms2] 経由駅コード２
* @param integer [ms3] 経由駅コード３
* @param integer [ms4] 経由駅コード４
* @param integer [xdw] 曜日種別<br>0：平日<br>1：土曜<br>2：日曜
* @param integer [xrp] 優先条件<br>0：早い順<br>1：安い順<br>2：楽な順
* @param integer [xep] 特急利用<br>0：利用しない<br>1：利用する
* @param string [datum] 測地系
* @return string ルート探索結果JSONP
*/
require_once("./inc/define.php");
require_once("./inc/ZdcCommonFunc.inc");
require_once("./inc/Jsphon/Encoder.php");

$param_names = array(
	"callback",
	"stlat",
	"stlon",
	"edlat",
	"edlon",
	"ms1",
	"ms2",
	"ms3",
	"ms4",
	"xdw",
	"xrp",
	"xep",
	"datum",
);

$params = array();
foreach ($param_names as $name) {
	$params[$name] = get_req_param($name);
}

// パラメータチェック
$err_msg = "";
if (!is_valid_param($params, $err_msg)) {
	create_response(RETURN_CODE_ERROR_PARAMS, $err_msg);
}

// 出発地の最寄り駅検索
$conditions = array(
	"lat" => $params["stlat"],
	"lon" => $params["stlon"],
	"datum" => $params["datum"],
);
$sts_infos = search_near_station($conditions);
// 目的地の最寄り駅検索
$conditions = array(
	"lat" => $params["edlat"],
	"lon" => $params["edlon"],
	"datum" => $params["datum"],
);
$eds_infos = search_near_station($conditions);

// 電車ルート検索
$conditions = array(
	"ms1" => $params["ms1"],
	"ms2" => $params["ms2"],
	"ms3" => $params["ms3"],
	"ms4" => $params["ms4"],
	"xdw" => $params["xdw"],
	"xrp" => $params["xrp"],
	"xep" => $params["xep"],
	"datum" => $params["datum"],
);
for ($i=0; $i<count($sts_infos); $i++) {
	// 検索条件の乗車駅に、出発地の最寄り駅をセット
	$conditions["sts".($i+1)] = $sts_infos[$i]["ekitanStationCode"];
}
for ($i=0; $i<count($eds_infos); $i++) {
	// 検索条件の下車駅に、目的地の最寄り駅をセット
	$conditions["eds".($i+1)] = $eds_infos[$i]["ekitanStationCode"];
}
$train_routes = search_train_route($conditions);

// 歩行者ルート検索条件（出発地から乗車駅まで）
$conditions = array(
	"stx" => cnv_hour2dms($params["stlon"]),
	"sty" => cnv_hour2dms($params["stlat"]),
	"datum" => $params["datum"],
);
$result = array();
foreach ($sts_infos as $station_info) {
	// 検索条件の終点緯度経度に、乗車駅の緯度経度セット
	$conditions["edx"] = cnv_hour2dms($station_info["lon"]);
	$conditions["edy"] = cnv_hour2dms($station_info["lat"]);
	$result[$station_info["ekitanStationCode"]] = search_walk_route($conditions);
}
$walk_routes["first"] = $result;

// 歩行者ルート検索条件（下車駅から目的地まで）
$conditions = array(
	"edx" => cnv_hour2dms($params["edlon"]),
	"edy" => cnv_hour2dms($params["edlat"]),
	"datum" => $params["datum"],
);
$result = array();
foreach ($eds_infos as $station_info) {
	// 検索条件の始点緯度経度に、下車駅の緯度経度セット
	$conditions["stx"] = cnv_hour2dms($station_info["lon"]);
	$conditions["sty"] = cnv_hour2dms($station_info["lat"]);
	$result[$station_info["ekitanStationCode"]] = search_walk_route($conditions);
}
$walk_routes["last"] = $result;

// 電車ルートと歩行者ルートをマージする
$routes = merge_route($train_routes, $walk_routes);

create_response(RETURN_CODE_SUCCESS, "ok", $routes);

/*
 * JSONPレスポンス生成
 *
 * @param integer $code 処理結果コード
 * @param string $text 処理結果メッセージ
 * @param array $data 検索結果（省略時は""）
 * @return JSONPレスポンス
 *
 */
function create_response($code, $text, $data="")
{
	$status = array(
		"code" => $code,
		"text" => $text,
	);
	$result = array(
		"route" => $data,
	);
	$json = new Jsphon_Encoder();
	$sts_json = $json->encode($status);
	$res_json = $json->encode($result);
	
	// JSONP対応
	$callback = get_req_param("callback");
	header("Content-type: text/javascript; charset=utf-8");
	header("X-Content-Type-Options: nosniff");	// IE7以下では効果なし
	echo $callback."(".$sts_json.",".$res_json.")";
	exit;
}

/*
 * リクエストパラメータ取得
 * 優先度はPOST,GETの順とする
 *
 * @param string $name パラメータ名
 * @return リクエストパラメータ（なければnullを返す）
 *
 */
function get_req_param($name)
{
	return isset($_POST[$name]) ? $_POST[$name] : (isset($_GET[$name]) ? $_GET[$name] : null);
}

/**
* パラメータチェック
* @param array IN params パラメータ
* @param string OUT errmsg エラーメッセージ
* @return bool true:OK<br>false:NG
*/
function is_valid_param($params, &$err_msg)
{
	// 必須チェック
	if ($params["callback"] == "") {
		$err_msg = "コールバック関数名を指定してください。";
		return false;
	} elseif (! preg_match("/^[a-zA-Z0-9\[\]\.\_]+$/", $params["callback"])) {
		$err_msg = "コールバック関数名が不正です。";
		return false;
	} elseif (strlen($params["callback"]) > 64) {
		$err_msg = "コールバック関数名は64バイト以内にしてください。";
		return false;
	}
	if ($params["stlat"] == "" || $params["stlon"] == "") {
		$err_msg = "出発地を指定してください。";
		return false;
	}
	if ($params["edlat"] == "" || $params["edlon"] == "") {
		$err_msg = "目的地を指定してください。";
		return false;
	}
	// フォーマットチェック
	if (!is_numeric($params["stlat"]) || !is_numeric($params["stlon"])) {
		$err_msg = "出発地が不正です。";
		return false;
	}
	if (!is_numeric($params["edlat"]) || !is_numeric($params["edlon"])) {
		$err_msg = "出発地が不正です。";
		return false;
	}
	for ($i = 1; $i <= 4; $i++) {
		$key = "ms" . $i;
		if ($params[$key] != "") {
			if (!is_numeric($params[$key])) {
				$err_msg = "経由駅が不正です。";
				return false;
			}
		}
	}
	if ($params["xdw"] != "") {
		if (!is_numeric($params["xdw"]) || ($params["xdw"] < 0 || $params["xdw"] > 2)) {
			$err_msg = "曜日種別が不正です。";
			return false;
		}
	}
	if ($params["xrp"] != "") {
		if (!is_numeric($params["xrp"]) || ($params["xrp"] < 0 || $params["xrp"] > 2)) {
			$err_msg = "優先条件が不正です。";
			return false;
		}
	}
	if ($params["xep"] != "") {
		if (!is_numeric($params["xep"]) || ($params["xep"] < 0 || $params["xep"] > 1)) {
			$err_msg = "特急利用が不正です。";
			return false;
		}
	}
	
	return true;
}

/*
 * 最寄り駅検索
 *
 * @param array conditions 検索条件配列
 * @return array 検索結果
 */
function search_near_station($conditions)
{
	$querys = array(
		"key"	=> ITUMO_CGI_KEY,
		"enc"	=> ITUMO_CGI_ENC,
		"datum"	=> ITUMO_CGI_DATUM,
		"outf"	=> ITUMO_CGI_OUTF,
		"knsu"	=> ITUMO_CGI_NEAR_STATION_KNSU,
		"rad"	=> ITUMO_CGI_NEAR_STATION_RAD,
		"pflg"	=> ITUMO_CGI_NEAR_STATION_PFLAG,
	);
	foreach ($conditions as $key => $value) {
		if ($value) $querys[$key] = $value;
	}
	$url = ITUMO_CGI_API_SEARCH_NEAR_STATION.'?'.http_build_query($querys, '', '&');
	$xml = simplexml_load_file($url);

	$status = $xml->status;

	$rows = array();
	$returnCode = (int)$status->returnCode;
	if ($returnCode == 35200000) {
		foreach ($xml->result->item as $item) {
			$buf = array();
			foreach ($item->children() as $key => $value) {
				$buf[$key] = (string)$value;
			}
			$rows[] = $buf;
		}
		return $rows;
	} else {
		// エラー処理
		if ($returnCode == 35211009) {
			$text = "データなし";
		} elseif ($returnCode >= 35212000 && $returnCode <= 35212999) {
			$text = "認証エラー";
		} elseif ($returnCode >= 35218000 && $returnCode <= 35218999) {
			$text = "検索エンジンエラー";
		} elseif ($returnCode >= 35219000 && $returnCode <= 35219999) {
			$text = "入力パラメータエラー";
		} else {
			$text = "その他エラー";
		}
		create_response($returnCode, $text);
	}
}

/*
 * 電車ルート検索
 *
 * @param array conditions 検索条件配列
 * @return array 検索結果
 */
function search_train_route($conditions)
{
	$querys = array(
		"key"	=> ITUMO_CGI_KEY,
		"enc"	=> ITUMO_CGI_ENC,
		"datum"	=> ITUMO_CGI_DATUM,
		"knsu"	=> ITUMO_CGI_TRAIN_ROUTE_KNSU,
		"pathf"	=> ITUMO_CGI_TRAIN_ROUTE_PATHF,
	);
	foreach ($conditions as $key => $value) {
		if ($value) $querys[$key] = $value;
	}
	$url = ITUMO_CGI_API_SEARCH_TRAIN_ROUTE.'?'.http_build_query($querys, '', '&');

	$xml = simplexml_load_file($url);
	$status = $xml->status;

	$result = array();
	$returnCode = (int)$status->returnCode;
	if ($returnCode == 35000000) {
		foreach ($xml->result->item as $item) {
			$itemData = array();
			
			$itemData["time"]["hour"] = (int)$item->time->hour;
			$itemData["time"]["min"] = (int)$item->time->min;
			$itemData["fare"]["total"] = (int)$item->fare;
			$itemData["fare"]["basic"] = (int)$item->basicFare;
			$itemData["fare"]["charge"] = (int)$item->charge;
			
			$itemData["link"] = array();
			foreach ($item->lineList->line as $line) {
				$lineData = array();
				
				$lineData["name"] = (string)$line->lineName;
				$lineData["kind"] = (string)$line->kind;
				$lineData["railKind"] = (string)$line->railKind;
				
				$lineData["station"]["from"]["code"] = (string)$line->stationFrom->attributes()->code;
				$lineData["station"]["from"]["name"] = (string)$line->stationFrom->stationName;
				$lineData["station"]["from"]["time"]["hour"] = (int)$line->stationFrom->time->hour;
				$lineData["station"]["from"]["time"]["min"] = (int)$line->stationFrom->time->min;
				$lineData["station"]["from"]["latlon"]["lat"] = cnv_dms2hour((int)$line->stationFrom->lat);
				$lineData["station"]["from"]["latlon"]["lon"] = cnv_dms2hour((int)$line->stationFrom->lon);
				
				$lineData["station"]["to"]["code"] = (string)$line->stationTo->attributes()->code;
				$lineData["station"]["to"]["name"] = (string)$line->stationTo->stationName;
				$lineData["station"]["to"]["time"]["hour"] = (int)$line->stationTo->time->hour;
				$lineData["station"]["to"]["time"]["min"] = (int)$line->stationTo->time->min;
				$lineData["station"]["to"]["latlon"]["lat"] = cnv_dms2hour((int)$line->stationTo->lat);
				$lineData["station"]["to"]["latlon"]["lon"] = cnv_dms2hour((int)$line->stationTo->lon);
				
				$lineData["time"] = sub_time($lineData["station"]["to"]["time"], $lineData["station"]["from"]["time"]);
				
				$lineData["fare"]["total"] = (int)$line->fare;
				$lineData["fare"]["basic"] = (int)$line->basicFare;
				$lineData["fare"]["charge"] = 0;
				$lineData["fare"]["chargeInfo"] = array();
				if (isset($line->chargeInfoList->chargeInfo)) {
					foreach ($line->chargeInfoList->chargeInfo as $chargeInfo) {
					 	$default = $chargeInfo->attributes()->default == "true" ? true : false;
						if ($default) {
							$lineData["fare"]["charge"] = (int)$chargeInfo->charge;
						}
						$lineData["fare"]["chargeInfo"][] = array(
							"default"		=> $default,
							"chargeType"	=> (string)$chargeInfo->chargeType,
							"charge"		=> (int)$chargeInfo->charge,
						);
					}
				}
				
				$paths = explode(",", (string)$line->pathList->path);
				for ($i=0; $i<count($paths); $i+=2) {
					// 歩行者ルートと合わせて"line"に経路座標情報をセット
					$lineData["line"][] = array(
						"lat" => cnv_dms2hour($paths[$i+1]),
						"lon" => cnv_dms2hour($paths[$i])
					);
				}
				
				// 乗車駅から下車駅までリンク情報のラインがつながるように補完する
				if (($lineDataPrev = end($itemData["link"])) !== FALSE) {
					// １つ前のリンク情報と時間差があれば、リンク情報を補完する
					$sub_time = sub_time($lineData["station"]["from"]["time"], $lineDataPrev["station"]["to"]["time"]);
					if ($sub_time["hour"] != 0 || $sub_time["min"] != 0) {
						if ($lineDataPrev["name"] == "徒歩") {
							// １つ前のリンク情報が徒歩ならば、そちらに差分を追加する
							$idx_prev = key($itemData["link"]);
							$itemData["link"][$idx_prev]["time"] = add_time($lineDataPrev["time"], $sub_time);
							$itemData["link"][$idx_prev]["station"]["to"]["time"] = add_time($lineDataPrev["station"]["to"]["time"], $sub_time);
							$itemData["link"][$idx_prev]["line"][] = $lineData["line"][0];
						} else {
							// １つ前のリンク情報が徒歩でなければ、徒歩のリンク情報を新規作成する
							$lines = array(
								end($lineDataPrev["line"]),
								$lineData["line"][0],
							);
							$itemData["link"][] = get_cover_train_link($lineDataPrev["station"]["to"], $lineData["station"]["from"], $sub_time, $lines);
						}
					} else {
						// １つ前のリンク情報とラインがつながっていなければ、リンク情報を補完する
						$line_prev_end = end($lineDataPrev["line"]);
						if ($line_prev_end["lat"] != $lineData["line"][0]["lat"] || $line_prev_end["lon"] != $lineData["line"][0]["lon"]) {
							// 現在のリンク情報のラインの先頭に、１つ前のリンク情報のラインの最後を追加
							array_unshift($lineData["line"], $line_prev_end);
						}
					}
				}
				// 歩行者ルートと合わせて"link"に区間情報をセット
				$itemData["link"][] = $lineData;
			}
			
			$result[] = $itemData;
		}
		
		return $result;
	} else {
		// エラー処理
		if ($returnCode == 35011009) {
			$text = "データなし";
		} elseif ($returnCode >= 35012000 && $returnCode <= 35012999) {
			$text = "認証エラー";
		} elseif ($returnCode >= 35018000 && $returnCode <= 35018999) {
			$text = "検索エンジンエラー";
		} elseif ($returnCode >= 35019000 && $returnCode <= 35019999) {
			$text = "入力パラメータエラー";
		} else {
			$text = "その他エラー";
		}
		create_response($returnCode, $text);
	}
}

/*
 * 歩行者ルート検索
 *
 * @param array conditions 検索条件配列
 * @return array 検索結果
 */
function search_walk_route($conditions)
{
	$querys = array(
		"key"	=> ITUMO_CGI_KEY,
		"enc"	=> ITUMO_CGI_ENC,
		"datum"	=> ITUMO_CGI_DATUM,
		"stt"	=> ITUMO_CGI_WALK_ROUTE_TYPE,
		"edt"	=> ITUMO_CGI_WALK_ROUTE_TYPE,
		"psc"	=> ITUMO_CGI_WALK_ROUTE_PSC,
		"link"	=> ITUMO_CGI_WALK_ROUTE_LINK,
	);
	foreach ($conditions as $key => $value) {
		if ($value) $querys[$key] = $value;
	}
	$url = ITUMO_CGI_API_SEARCH_WALK_ROUTE.'?'.http_build_query($querys, '', '&');
	
	$xml = simplexml_load_file($url);
	$status = $xml->status;

	$result = array();
	$returnCode = (int)$status->error_code;
	if ($returnCode == 31600000) {
		$result["distance"] = (int)$status->distance;
		$result["time"] = calc_walk_time($result["distance"]);
		
		$result["link"] = array();
		foreach ($xml->links->link as $link) {
			$linkData = array();
			
			list($id, $typecd, $stypecd, $roof, $mflg, $distance) = explode(",", (string)$link->info);
			$linkData["type"] = (int)$typecd;
			$linkData["structureType"] = (int)$stypecd;
			$linkData["roof"] = (boolean)$roof;
			$linkData["mflg"] = (boolean)$mflg;
			$linkData["distance"] = (int)$distance;
			
			$linkData["line"] = array();
			$paths = explode(",", (string)$link->path);
			for ($i=0; $i<count($paths); $i+=2) {
				$linkData["line"][] = array(
					"lat"=>cnv_dms2hour($paths[$i+1]),
					"lon"=>cnv_dms2hour($paths[$i])
				);
			}
			$result["link"][] = $linkData;
		}
		
		return $result;
	} else {
		// エラー処理
		if ($returnCode == 35011009) {
			$text = "データなし";
		} elseif ($returnCode >= 31612000 && $returnCode <= 31612999) {
			$text = "認証エラー";
		} elseif ($returnCode == 31619100) {
			$text = "入力パラメータエラー";
		} elseif ($returnCode == 31619101) {
			$text = "ルート距離制限エラー";
		} elseif ($returnCode == 31611009) {
			$text = "ルート検索エンジンエラー";
		} elseif ($returnCode == 31613769) {
			$text = "始点・経由点・終点間の距離が近過ぎる";
		} elseif ($returnCode == 31613025) {
			$text = "始点・経由点・終点間の距離が遠過ぎる";
		} elseif ($returnCode == 31613274) {
			$text = "経路探索失敗エラー";
		} elseif ($returnCode == 31613035) {
			$text = "経路誘導失敗エラー";
		} elseif ($returnCode == 31613291) {
			$text = "始点経度パラメータ不正エラー";
		} elseif ($returnCode == 31613547) {
			$text = "始点緯度パラメータ不正エラー";
		} elseif ($returnCode == 31613803) {
			$text = "経由点経度パラメータ不正エラー";
		} elseif ($returnCode == 31613315) {
			$text = "経由点緯度パラメータ不正エラー";
		} elseif ($returnCode == 31613571) {
			$text = "終点経度パラメータ不正エラー";
		} elseif ($returnCode == 31613059) {
			$text = "終点緯度パラメータ不正エラー";
		} else {
			$text = "その他エラー";
		}
		create_response($returnCode, $text);
	}
}

/*
 * 電車ルートと歩行者ルートをマージ
 *
 * @param array train_routes 電車ルート
 * @param array walk_routes 歩行者ルート
 * @return array マージ結果
 */
function merge_route($train_routes, $walk_routes)
{
	$result = array();
	
	foreach ($train_routes as $idx => $train_route) {
		$route = array();
		
		$train_tm = $train_route["time"];
		
		$link = $train_route["link"];
		$st_cd_f = $link[0]["station"]["from"]["code"];
		$st_cd_l = $link[count($link) - 1]["station"]["to"]["code"];
		$walk_route_f = $walk_routes["first"][$st_cd_f];
		$walk_route_l = $walk_routes["last"][$st_cd_l];
		
		$walk_tm = add_time($walk_route_f["time"], $walk_route_l["time"]);
		
		$route["time"] = add_time($train_tm, $walk_tm);
		$route["fare"] = $train_route["fare"];
		$route["train"] = $train_route;
		$route["walk"]["first"] = $walk_route_f;
		$route["walk"]["last"] = $walk_route_l;

		// 歩行者ルートを補完する
		// 歩行者ルート（前半）の終点と電車ルートの始点を結ぶ、リンク情報追加
		$walk_link_end = end($route["walk"]["first"]["link"]);
		$lines = array(
			end($walk_link_end["line"]),
			$route["train"]["link"][0]["line"][0],
		);
		$route["walk"]["first"]["link"][] = get_cover_walk_link($lines);
		// 電車ルートの終点と歩行者ルート（後半）の始点を結ぶ、リンク情報追加
		$train_link_end = end($route["train"]["link"]);
		$lines = array(
			end($train_link_end["line"]),
			$route["walk"]["last"]["link"][0]["line"][0],
		);
		array_unshift($route["walk"]["last"]["link"], get_cover_walk_link($lines));
		
		// 順位付けのため保持
		$times[$idx] = $route["time"]["hour"] * 60 + $route["time"]["min"];
		$fares[$idx] = $route["fare"]["total"];
		$link_cnts[$idx] = count($route["train"]["link"]);
		
		$result[] = $route;
	}

	// 早い順/安い順/楽な順の順位付け
	$rank = array();
	$rank["fast"] = get_rank($times);
	$rank["cheap"] = get_rank($fares);
	$rank["easy"] = get_rank($link_cnts);
	foreach ($result as $idx => $route) {
		$result[$idx]["rank"]["fast"] = $rank["fast"][$idx];
		$result[$idx]["rank"]["cheap"] = $rank["cheap"][$idx];
		$result[$idx]["rank"]["easy"] = $rank["easy"][$idx];
	}
	
	return $result;
}

/*
 * 歩行時間を計算
 *
 * @param int distance 距離(m)
 * @return array 時間
 */
function calc_walk_time($distance)
{
	$min = ceil($distance / WALK_SPEED_METER_PER_MIN);
	
	return array(
		"hour" => floor($min / 60),
		"min"  => $min % 60,
	);
}

/*
 * 時間の加算
 *
 * @param array time1 時間１
 * @param array time2 時間２
 * @return array 時間
 */
function add_time($time1, $time2)
{
	$hour = $time1["hour"] + $time2["hour"];
	$min = $time1["min"] + $time2["min"];
	
	return array(
		"hour" => (int)($hour + floor($min / 60)),
		"min"  => (int)($min % 60),
	);
}

/*
 * 時間の減算
 *
 * @param array time1 時間１
 * @param array time2 時間２
 * @return array 時間
 */
function sub_time($time1, $time2)
{
	$min1 = $time1["hour"] * 60 + $time1["min"];
	$min2 = $time2["hour"] * 60 + $time2["min"];
	if ($min2 > $min1) $min1 += (24 * 60);
	$min = $min1 - $min2;
	
	return array(
		"hour" => (int)(floor($min / 60)),
		"min"  => (int)($min % 60),
	);
}

/*
 * 順位付け
 *
 * @param array array 配列
 * @return array 順位
 */
function get_rank($array)
{
	// 小さい順にソート
	asort($array);
	
	$rank = 1;
	$prev_value = reset($array);
	$result = array();
	foreach ($array as $idx => $value) {
		if ($value != $prev_value) $rank++;
		$result[$idx] = $rank;
	}
	return $result;
}

/*
 * 電車ルートの補完用リンク情報取得
 *
 * @param array from 乗車駅情報
 * @param array to 下車駅情報1
 * @param array time 時間情報1
 * @param array lines ライン情報
 * @return array リンク情報
 */
function get_cover_train_link($from, $to, $time, $lines)
{
	return array(
		"name"			=> "徒歩",
		"kind"			=> 0,
		"railKind"		=> "徒歩",
		"station"		=> array(
			"from"		=> $from,
			"to"		=> $to,
		),
		"time"			=> $time,
		"fare"		=> array(
			"total"		=> 0,
			"basic"		=> 0,
			"charge"	=> 0,
			"chargeInfo"=> array(),
		),
		"line"			=> $lines,
	);
}

/*
 * 歩行者ルートの補完用リンク情報取得
 *
 * @param array lines ライン情報
 * @return array リンク情報
 */
function get_cover_walk_link($lines)
{
	return array(
		"type"			=> 8,	// 乗換リンク
		"structureType"	=> 0,	// 通常 
		"roof"			=> false,
		"mflg"			=> false,
		"distance"		=> 0,
		"line"			=> $lines,
	);
}

?>
