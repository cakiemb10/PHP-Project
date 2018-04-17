<?php
// ------------------------------------------------------------
// APIレスポンスの補正項目定義
// 
// 2016/12/16 H.Yasunaga	新規作成
// 2017/01/25 H.Yasunaga	位置管理ユニークコード(拠点ID)の0落ち項目補正を外す
// ------------------------------------------------------------
require_once(dirname(__FILE__) . "/ResponseTag.inc");

	// 半角化処理対象
	$VALUE_TO_HALF;
	// 数字およびカタカナの全角化
	$VALUE_TO_FULL;
	// ハイフンの除去(郵便番号)
	$VALUE_TRIM_HYPHEN;
	// 0落ち項目補正
	$VALUE_ZERO_CORRECT;
	// 時刻項目補正 hh:mm:ss の ssが無い場合に「00」を追加する
	$VALUE_TIME_CORRECT;

// 半角化	
	$VALUE_TO_HALF = array();
	// 項番1:位置管理ユニークコード
	$VALUE_TO_HALF[$TAG_ORDER[0]] = true;
	// 項番2:局所コード
	$VALUE_TO_HALF[$TAG_ORDER[1]] = true;
	// 項番3:取扱店番号
	$VALUE_TO_HALF[$TAG_ORDER[2]] = true;
	// 項番9:郵便番号
	$VALUE_TO_HALF[$TAG_ORDER[8]] = true;
	// 項番12:JIS市区町村コード
	$VALUE_TO_HALF[$TAG_ORDER[11]] = true;
	// 項番14:駐車場
	$VALUE_TO_HALF[$TAG_ORDER[13]] = true;
	// 項番18:郵便局会社ユニークコード
	$VALUE_TO_HALF[$TAG_ORDER[17]] = true;
	// 項番22:窓口電話番号
	$VALUE_TO_HALF[$TAG_ORDER[21]] = true;
	// 項番23:総務電話番号
	$VALUE_TO_HALF[$TAG_ORDER[22]] = true;
	// 項番24:問い合わせFAX
	$VALUE_TO_HALF[$TAG_ORDER[23]] = true;
	// 項番26:ゆうゆう窓口ユニークコード
	$VALUE_TO_HALF[$TAG_ORDER[25]] = true;
	// 項番27:固有郵便番号
	$VALUE_TO_HALF[$TAG_ORDER[26]] = true;
	// 項番32:代表電話番号
	$VALUE_TO_HALF[$TAG_ORDER[31]] = true;
	// 項番33:集荷電話番号
	$VALUE_TO_HALF[$TAG_ORDER[32]] = true;
	// 項番42:かんぽユニークコード
	$VALUE_TO_HALF[$TAG_ORDER[41]] = true;
	// 項番47:電話番号１
	$VALUE_TO_HALF[$TAG_ORDER[46]] = true;
	// 項番48:電話番号２
	$VALUE_TO_HALF[$TAG_ORDER[47]] = true;
	// 項番115:郵便平日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[114]] = true;
	// 項番116:郵便平日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[115]] = true;
	// 項番117:郵便土曜開始時間
	$VALUE_TO_HALF[$TAG_ORDER[116]] = true;
	// 項番118:郵便土曜終了時間
	$VALUE_TO_HALF[$TAG_ORDER[117]] = true;
	// 項番119:郵便日曜・休日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[118]] = true;
	// 項番120:郵便日曜・休日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[119]] = true;
	// 項番121:郵便窓口定休日
	$VALUE_TO_HALF[$TAG_ORDER[120]] = true;
	// 項番123:貯金平日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[122]] = true;
	// 項番124:貯金平日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[123]] = true;
	// 項番125:貯金土曜開始時間
	$VALUE_TO_HALF[$TAG_ORDER[124]] = true;
	// 項番126:貯金土曜終了時間
	$VALUE_TO_HALF[$TAG_ORDER[125]] = true;
	// 項番127:貯金日曜・休日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[126]] = true;
	// 項番128:貯金日曜・休日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[127]] = true;
	// 項番129:銀行窓口定休日
	$VALUE_TO_HALF[$TAG_ORDER[128]] = true;
	// 項番131:ATM平日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[130]] = true;
	// 項番132:ATM平日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[131]] = true;
	// 項番133:ATM土曜開始時間
	$VALUE_TO_HALF[$TAG_ORDER[132]] = true;
	// 項番134:ATM土曜終了時間
	$VALUE_TO_HALF[$TAG_ORDER[133]] = true;
	// 項番135:ATM日曜・休日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[134]] = true;
	// 項番136:ATM日曜・休日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[135]] = true;
	// 項番137:ATM定休日
	$VALUE_TO_HALF[$TAG_ORDER[136]] = true;
	// 項番139:保険平日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[138]] = true;
	// 項番140:保険平日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[139]] = true;
	// 項番141:保険土曜開始時間
	$VALUE_TO_HALF[$TAG_ORDER[140]] = true;
	// 項番142:保険土曜終了時間
	$VALUE_TO_HALF[$TAG_ORDER[141]] = true;
	// 項番143:保険日曜・休日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[142]] = true;
	// 項番144:保険日曜・休日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[143]] = true;
	// 項番145:保険窓口定休日
	$VALUE_TO_HALF[$TAG_ORDER[144]] = true;
	// 項番147:ゆうゆう平日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[146]] = true;
	// 項番148:ゆうゆう平日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[147]] = true;
	// 項番149:ゆうゆう土曜開始時間
	$VALUE_TO_HALF[$TAG_ORDER[148]] = true;
	// 項番150:ゆうゆう土曜終了時間
	$VALUE_TO_HALF[$TAG_ORDER[149]] = true;
	// 項番151:ゆうゆう日曜・休日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[150]] = true;
	// 項番152:ゆうゆう日曜・休日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[151]] = true;
	// 項番153:ゆうゆう窓口定休日
	$VALUE_TO_HALF[$TAG_ORDER[152]] = true;
	// 項番155:かんぽ平日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[154]] = true;
	// 項番156:かんぽ平日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[155]] = true;
	// 項番157:かんぽ土曜開始時間
	$VALUE_TO_HALF[$TAG_ORDER[156]] = true;
	// 項番158:かんぽ土曜終了時間
	$VALUE_TO_HALF[$TAG_ORDER[157]] = true;
	// 項番159:かんぽ日曜・休日開始時間
	$VALUE_TO_HALF[$TAG_ORDER[158]] = true;
	// 項番160:かんぽ日曜・休日終了時間
	$VALUE_TO_HALF[$TAG_ORDER[159]] = true;
	// 項番161:かんぽ窓口定休日
	$VALUE_TO_HALF[$TAG_ORDER[160]] = true;

// 全角化
	$VALUE_TO_FULL = array();
	// 項番10:住所
	$VALUE_TO_FULL[$TAG_ORDER[9]] = true;

// ハイフン除去(郵便番号)
	$VALUE_TRIM_HYPHEN = array();
	// 項番9:郵便番号
	$VALUE_TRIM_HYPHEN[$TAG_ORDER[8]] = true;
	// 項番27:固有郵便番号
	$VALUE_TRIM_HYPHEN[$TAG_ORDER[26]] = true;

// 0落ち項目補正
	$VALUE_ZERO_CORRECT = array();
	// del start 2017/01/25 H.Yasunaga 位置管理ユニークコード(拠点ID)の0落ち項目補正を外す [
	// 項番1:位置管理ユニークコード
	//$VALUE_ZERO_CORRECT[$TAG_ORDER[0]] = 12;
	// del end 2017/01/25 ]
	// 項番2:局所コード
	$VALUE_ZERO_CORRECT[$TAG_ORDER[1]] = 6;
	// 項番3:取扱店番号
	$VALUE_ZERO_CORRECT[$TAG_ORDER[2]] = 6;
	// 項番5:併設店フラグ
	$VALUE_ZERO_CORRECT[$TAG_ORDER[4]] = 4;
	// 項番11:JIS都道府県コード
	$VALUE_ZERO_CORRECT[$TAG_ORDER[10]] = 2;
	// 項番12:JIS市区町村コード
	$VALUE_ZERO_CORRECT[$TAG_ORDER[11]] = 5;
	// 項番21:郵便局区分
	$VALUE_ZERO_CORRECT[$TAG_ORDER[20]] = 2;
	// 項番30:郵便支店区分
	$VALUE_ZERO_CORRECT[$TAG_ORDER[29]] = 2;
	
// 時刻項目補正 hh:mm:ss の ssが無い場合に「00」を追加する
	$VALUE_TIME_CORRECT = array();
	// 項番115:郵便平日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[114]] = true;
	// 項番116:郵便平日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[115]] = true;
	// 項番117:郵便土曜開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[116]] = true;
	// 項番118:郵便土曜終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[117]] = true;
	// 項番119:郵便日曜・休日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[118]] = true;
	// 項番120:郵便日曜・休日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[119]] = true;
	// 項番123:貯金平日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[122]] = true;
	// 項番124:貯金平日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[123]] = true;
	// 項番125:貯金土曜開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[124]] = true;
	// 項番126:貯金土曜終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[125]] = true;
	// 項番127:貯金日曜・休日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[126]] = true;
	// 項番128:貯金日曜・休日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[127]] = true;
	// 項番131:ATM平日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[130]] = true;
	// 項番132:ATM平日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[131]] = true;
	// 項番133:ATM土曜開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[132]] = true;
	// 項番134:ATM土曜終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[133]] = true;
	// 項番135:ATM日曜・休日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[134]] = true;
	// 項番136:ATM日曜・休日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[135]] = true;
	// 項番139:保険平日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[138]] = true;
	// 項番140:保険平日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[139]] = true;
	// 項番141:保険土曜開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[140]] = true;
	// 項番142:保険土曜終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[141]] = true;
	// 項番143:保険日曜・休日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[142]] = true;
	// 項番144:保険日曜・休日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[143]] = true;
	// 項番147:ゆうゆう平日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[146]] = true;
	// 項番148:ゆうゆう平日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[147]] = true;
	// 項番149:ゆうゆう土曜開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[148]] = true;
	// 項番150:ゆうゆう土曜終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[149]] = true;
	// 項番151:ゆうゆう日曜・休日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[150]] = true;
	// 項番152:ゆうゆう日曜・休日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[151]] = true;
	// 項番155:かんぽ平日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[154]] = true;
	// 項番156:かんぽ平日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[155]] = true;
	// 項番157:かんぽ土曜開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[156]] = true;
	// 項番158:かんぽ土曜終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[157]] = true;
	// 項番159:かんぽ日曜・休日開始時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[158]] = true;
	// 項番160:かんぽ日曜・休日終了時間
	$VALUE_TIME_CORRECT[$TAG_ORDER[159]] = true;
?>