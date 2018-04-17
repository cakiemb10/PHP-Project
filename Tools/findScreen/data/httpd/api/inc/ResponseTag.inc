<?php
// ------------------------------------------------------------
// APIレスポンスのXMLタグ定義
// 
// 2016/06/14 H.Yasunaga	新規作成
// 2016/06/24 H.Yasunaga	検索結果の緯度経度の順番の修正
//							緯度経度の指定ミスの修正
// ------------------------------------------------------------
	$TAG_ORDER;
	$TAG_TO_COL;
	

	$TAG_ORDER = array();
	//位置管理ユニークコード
	$TAG_ORDER[0] = "office_id";
	//局所コード
	$TAG_ORDER[1] = "post_code";
	//取扱店番号
	$TAG_ORDER[2] = "dealer_no";
	//最終更新年月日
	$TAG_ORDER[3] = "last_update_date";
	//併設店フラグ
	$TAG_ORDER[4] = "juxtaposition_flag";
	//ATM有無
	$TAG_ORDER[5] = "atm_flag";
	//緯度
	$TAG_ORDER[6] = "nl";
	//経度
	$TAG_ORDER[7] = "el";
	//郵便番号
	$TAG_ORDER[8] = "zip_code";
	//住所
	$TAG_ORDER[9] = "address";
	//JIS都道府県コード
	$TAG_ORDER[10] = "pref_code";
	//JIS市区町村コード
	$TAG_ORDER[11] = "city_code";
	//JIS市区町村名
	$TAG_ORDER[12] = "city_name";
	//駐車場
	$TAG_ORDER[13] = "parking";
	//駐車場備考
	$TAG_ORDER[14] = "parking_note";
	//店舗規模
	$TAG_ORDER[15] = "store_scale";
	//所属エリア
	$TAG_ORDER[16] = "area";
	//郵便局会社ユニークコード
	$TAG_ORDER[17] = "jp_network_code";
	//郵便局名
	$TAG_ORDER[18] = "jp_network_name";
	//郵便局名(全角かな字)
	$TAG_ORDER[19] = "jp_network_kana";
	//郵便局区分
	$TAG_ORDER[20] = "jp_network_class";
	//窓口電話番号
	$TAG_ORDER[21] = "jp_network_tel1";
	//総務電話番号
	$TAG_ORDER[22] = "jp_network_tel2";
	//問合せFAX
	$TAG_ORDER[23] = "jp_network_fax";
	//問合せ備考
	$TAG_ORDER[24] = "jp_network_note";
	//ゆうゆう窓口ユニークコード
	$TAG_ORDER[25] = "jp_post_code";
	//固有郵便番号
	$TAG_ORDER[26] = "jp_post_zip";
	//郵便支店名
	$TAG_ORDER[27] = "jp_post_name";
	//郵便支店名(全角かな字) 
	$TAG_ORDER[28] = "jp_post_kana";
	//郵便支店区分
	$TAG_ORDER[29] = "jp_post_class";
	//郵便支店取扱内容(備考) 
	$TAG_ORDER[30] = "jp_post_handling_note";
	//代表電話番号
	$TAG_ORDER[31] = "jp_post_tel1";
	//集荷電話番号
	$TAG_ORDER[32] = "jp_post_tel2";
	//問合せ備考
	$TAG_ORDER[33] = "jp_post_note";
	//ゆうちょ店ユニークコード
	$TAG_ORDER[34] = "jp_bank_code";
	//銀行直営店名
	$TAG_ORDER[35] = "jp_bank_name";
	//銀行直営店名(全角かな字) 
	$TAG_ORDER[36] = "jp_bank_kana";
	//銀行直営店正式名
	$TAG_ORDER[37] = "jp_bank_official_name";
	//区分(直営店／ATM出張所) 
	$TAG_ORDER[38] = "jp_bank_class";
	//電話番号
	$TAG_ORDER[39] = "jp_bank_tel";
	//問合せ備考
	$TAG_ORDER[40] = "jp_bank_note";
	//かんぽユニークコード
	$TAG_ORDER[41] = "jp_insurance_code";
	//かんぽ支店名
	$TAG_ORDER[42] = "jp_insurance_name";
	//かんぽ支店名(全角かな字) 
	$TAG_ORDER[43] = "jp_insurance_kana";
	//かんぽ支店区分
	$TAG_ORDER[44] = "jp_insurance_class";
	//支店URL 
	$TAG_ORDER[45] = "jp_insurance_url";
	//電話番号１ 
	$TAG_ORDER[46] = "jp_insurance_tel1";
	//電話番号２ 
	$TAG_ORDER[47] = "jp_insurance_tel2";
	//問合せ備考
	$TAG_ORDER[48] = "jp_insurance_note";
	//郵便窓口
	$TAG_ORDER[49] = "post_window";
	//印紙の売りさばき
	$TAG_ORDER[50] = "stamp_sale";
	//国内物流事業に係る窓口
	$TAG_ORDER[51] = "home_window";
	//チルドゆうパック
	$TAG_ORDER[52] = "chilled_yu_pack";
	//内容証明
	$TAG_ORDER[53] = "contents_certified";
	//取次ぎサービス
	$TAG_ORDER[54] = "agency_service";
	//通常貯金
	$TAG_ORDER[55] = "regular_savings";
	//通常貯蓄貯金
	$TAG_ORDER[56] = "money_market_account";
	//定額貯金
	$TAG_ORDER[57] = "fixed_deposit";
	//自動積立定額貯金
	$TAG_ORDER[58] = "auto_fixed_deposit";
	//定期貯金
	$TAG_ORDER[59] = "time_deposit";
	//自動積立定期貯金
	$TAG_ORDER[60] = "auto_time_deposit";
	//満期一括受取型定期貯金
	$TAG_ORDER[61] = "expiration_time_deposit";
	//ニュー福祉定期貯金
	$TAG_ORDER[62] = "welfare_time_deposit";
	//財形定額貯金
	$TAG_ORDER[63] = "asset_building_savings";
	//財産形成住宅定期貯金
	$TAG_ORDER[64] = "asset_building_savings_housing";
	//財産形成年金定期貯金
	$TAG_ORDER[65] = "asset_building_savings_pension";
	//普通為替
	$TAG_ORDER[66] = "normal_exchange";
	//定額小為替
	$TAG_ORDER[67] = "fixed_exchange";
	//ATMによる通常払込み
	$TAG_ORDER[68] = "atm_payment";
	//公金払込み
	$TAG_ORDER[69] = "public_payment";
	//通常払込み
	$TAG_ORDER[70] = "normal_payment";
	//電信払込み
	$TAG_ORDER[71] = "telegraphic_payment";
	//電信振替
	$TAG_ORDER[72] = "telegraphic_transfer";
	//相互送金
	$TAG_ORDER[73] = "mutual_transfer";
	//自動払込み
	$TAG_ORDER[74] = "auto_payment";
	//自動送金
	$TAG_ORDER[75] = "auto_transfer";
	//貯金小切手の振出
	$TAG_ORDER[76] = "cheque";
	//自動払出預入
	$TAG_ORDER[77] = "auto_deposit";
	//簡易払い(利用申込み・払出しの請求) 
	$TAG_ORDER[78] = "simple_payment_request";
	//簡易払い(払い渡し) 
	$TAG_ORDER[79] = "simple_payment_transfer";
	//通常現金払
	$TAG_ORDER[80] = "normal_cash_payment";
	//電信現金払(窓口払) 
	$TAG_ORDER[81] = "telegraphic_cash_payment";
	//給与預入
	$TAG_ORDER[82] = "salary_deposit";
	//国際送金
	$TAG_ORDER[83] = "international_transfer";
	//外貨両替/トラベラーズチェック
	$TAG_ORDER[84] = "foreign_currency";
	//国民年金
	$TAG_ORDER[85] = "national_pension";
	//反則金
	$TAG_ORDER[86] = "penalty";
	//国民年金・反則金以外の歳入金
	$TAG_ORDER[87] = "revenue";
	//歳出金
	$TAG_ORDER[88] = "expenditure";
	//無記名国債(国債) 
	$TAG_ORDER[89] = "government_bonds";
	//投資信託
	$TAG_ORDER[90] = "investment_trust";
	//変額年金保険
	$TAG_ORDER[91] = "variable_pension";
	//確定拠出年金
	$TAG_ORDER[92] = "defined_contribution";
	//住宅ローン・フリーローン
	$TAG_ORDER[93] = "suruga_loan";
	//かんぽ生命保険募集
	$TAG_ORDER[94] = "jp_insurance_recruit";
	//紹介代理店
	$TAG_ORDER[95] = "introduction_agency";
	//かんぽ生命保険維持管理業務
	$TAG_ORDER[96] = "jp_insurance_maintenance";
	//簡易生命保険管理業務
	$TAG_ORDER[97] = "kampo_maintenance";
	//かんぽ生命以外の生命保険募集
	$TAG_ORDER[98] = "except_jp_insurance_recruit";
	//自動車保険募集
	$TAG_ORDER[99] = "automobile_insurance";
	//自賠責保険募集
	$TAG_ORDER[100] = "liability_insurance";
	//ガン保険募集
	$TAG_ORDER[101] = "cancer_insurance";
	//引受条件緩和型医療保険
	$TAG_ORDER[102] = "condition_medical_insurance";
	//地方公共団体事務
	$TAG_ORDER[103] = "local_public_entity";
	//証明書交付事務
	$TAG_ORDER[104] = "certificate_grant";
	//証明書交付事務の内訳
	$TAG_ORDER[105] = "breakdown_certificate_grant";
	//受託窓口事務(受託販売事務) 
	$TAG_ORDER[106] = "trust_sale";
	//受託窓口事務(受託販売事務)の内容
	$TAG_ORDER[107] = "trust_sale_contents";
	//受託窓口事務(受託交付事務) 
	$TAG_ORDER[108] = "trust_grant";
	//受託窓口事務(受託交付事務)の内容
	$TAG_ORDER[109] = "trust_grant_contents";
	//その他の地方公共団体事務
	$TAG_ORDER[110] = "other_local_public";
	//その他の地方公共団体事務の内容
	$TAG_ORDER[111] = "other_local_public_contents";
	//宝くじ
	$TAG_ORDER[112] = "lottery";
	//カタログ販売
	$TAG_ORDER[113] = "catalog_sale";
	//郵便平日開始時間
	$TAG_ORDER[114] = "jp_network_start";
	//郵便平日終了時間
	$TAG_ORDER[115] = "jp_network_end";
	//郵便土曜開始時間
	$TAG_ORDER[116] = "jp_network_sat_start";
	//郵便土曜終了時間
	$TAG_ORDER[117] = "jp_network_sat_end";
	//郵便日曜・休日開始時間
	$TAG_ORDER[118] = "jp_network_sun_start";
	//郵便日曜・休日終了時間
	$TAG_ORDER[119] = "jp_network_sun_end";
	//郵便窓口定休日
	$TAG_ORDER[120] = "jp_network_win_closed";
	//郵便窓口備考
	$TAG_ORDER[121] = "jp_network_win_note";
	//貯金平日開始時間
	$TAG_ORDER[122] = "jp_bank_start";
	//貯金平日終了時間
	$TAG_ORDER[123] = "jp_bank_end";
	//貯金土曜開始時間
	$TAG_ORDER[124] = "jp_bank_sat_start";
	//貯金土曜終了時間
	$TAG_ORDER[125] = "jp_bank_sat_end";
	//貯金日曜・休日開始時間
	$TAG_ORDER[126] = "jp_bank_sun_start";
	//貯金日曜・休日終了時間
	$TAG_ORDER[127] = "jp_bank_sun_end";
	//銀行窓口定休日
	$TAG_ORDER[128] = "jp_bank_win_closed";
	//銀行窓口備考
	$TAG_ORDER[129] = "jp_bank_win_note";
	//ATM平日開始時間
	$TAG_ORDER[130] = "atm_start";
	//ATM平日終了時間
	$TAG_ORDER[131] = "atm_end";
	//ATM土曜開始時間
	$TAG_ORDER[132] = "atm_sat_start";
	//ATM土曜終了時間
	$TAG_ORDER[133] = "atm_sat_end";
	//ATM日曜・休日開始時間
	$TAG_ORDER[134] = "atm_sun_start";
	//ATM日曜・休日終了時間
	$TAG_ORDER[135] = "atm_sun_end";
	//ATM定休日
	$TAG_ORDER[136] = "atm_closed";
	//ATM備考
	$TAG_ORDER[137] = "atm_note";
	//保険平日開始時間
	$TAG_ORDER[138] = "jp_network_insurance_start";
	//保険平日終了時間
	$TAG_ORDER[139] = "jp_network_insurance_end";
	//保険土曜開始時間
	$TAG_ORDER[140] = "jp_network_insurance_sat_start";
	//保険土曜終了時間
	$TAG_ORDER[141] = "jp_network_insurance_sat_end";
	//保険日曜・休日開始時間
	$TAG_ORDER[142] = "jp_network_insurance_sun_start";
	//保険日曜・休日終了時間
	$TAG_ORDER[143] = "jp_network_insurance_sun_end";
	//保険窓口定休日
	$TAG_ORDER[144] = "jp_network_insurance_win_closed";
	//保険窓口備考
	$TAG_ORDER[145] = "jp_network_insurance_win_note";
	//ゆうゆう平日開始時間
	$TAG_ORDER[146] = "jp_post_start";
	//ゆうゆう平日終了時間
	$TAG_ORDER[147] = "jp_post_end";
	//ゆうゆう土曜開始時間
	$TAG_ORDER[148] = "jp_post_sat_start";
	//ゆうゆう土曜終了時間
	$TAG_ORDER[149] = "jp_post_sat_end";
	//ゆうゆう日曜・休日開始時間
	$TAG_ORDER[150] = "jp_post_sun_start";
	//ゆうゆう日曜・休日終了時間
	$TAG_ORDER[151] = "jp_post_sun_end";
	//ゆうゆう窓口定休日
	$TAG_ORDER[152] = "jp_post_win_closed";
	//ゆうゆう窓口備考
	$TAG_ORDER[153] = "jp_post_win_note";
	//かんぽ平日開始時間
	$TAG_ORDER[154] = "jp_insurance_start";
	//かんぽ平日終了時間
	$TAG_ORDER[155] = "jp_insurance_end";
	//かんぽ土曜開始時間
	$TAG_ORDER[156] = "jp_insurance_sat_start";
	//かんぽ土曜終了時間
	$TAG_ORDER[157] = "jp_insurance_sat_end";
	//かんぽ日曜・休日開始時間
	$TAG_ORDER[158] = "jp_insurance_sun_start";
	//かんぽ日曜・休日終了時間
	$TAG_ORDER[159] = "jp_insurance_sun_end";
	//かんぽ窓口定休日
	$TAG_ORDER[160] = "jp_insurance_win_closed";
	//かんぽ窓口備考
	$TAG_ORDER[161] = "jp_insurance_win_note";
	//小切手払い
	$TAG_ORDER[162] = "reserve_flag1";
	//カードローン
	$TAG_ORDER[163] = "reserve_flag2";
	//反映日時
	$TAG_ORDER[164] = "reflect_date";

	$TAG_TO_COL = array();
	//位置管理ユニークコード
	$TAG_TO_COL['office_id'] = "KYOTEN_ID";
	//局所コード
	$TAG_TO_COL['post_code'] = "COL_02";
	//取扱店番号
	$TAG_TO_COL['dealer_no'] = "COL_03";
	//最終更新年月日
	$TAG_TO_COL['last_update_date'] = "UPD_DT";
	//併設店フラグ
	$TAG_TO_COL['juxtaposition_flag'] = array("COL_05", "COL_06", "COL_07", "COL_08");
	//ATM有無
	$TAG_TO_COL['atm_flag'] = "COL_09";
	//緯度
	$TAG_TO_COL['el'] = "LON";
	//経度
	$TAG_TO_COL['nl'] = "LAT";
	//郵便番号
	$TAG_TO_COL['zip_code'] = "COL_10";
	//住所
	$TAG_TO_COL['address'] = "ADDR";
	//JIS都道府県コード
	$TAG_TO_COL['pref_code'] = "COL_11";
	//JIS市区町村コード
	$TAG_TO_COL['city_code'] = "COL_12";
	//JIS市区町村名
	$TAG_TO_COL['city_name'] = "COL_13";
	//駐車場
	$TAG_TO_COL['parking'] = "COL_14";
	//駐車場備考
	$TAG_TO_COL['parking_note'] = "COL_15";
	//店舗規模
	$TAG_TO_COL['store_scale'] = "COL_16";
	//所属エリア
	$TAG_TO_COL['area'] = "COL_18";
	//郵便局会社ユニークコード
	$TAG_TO_COL['jp_network_code'] = "COL_19";
	//郵便局名
	$TAG_TO_COL['jp_network_name'] = "COL_20";
	//郵便局名(全角かな字)
	$TAG_TO_COL['jp_network_kana'] = "COL_21";
	//郵便局区分
	$TAG_TO_COL['jp_network_class'] = "COL_22";
	//窓口電話番号
	$TAG_TO_COL['jp_network_tel1'] = "COL_23";
	//総務電話番号
	$TAG_TO_COL['jp_network_tel2'] = "COL_24";
	//問合せFAX
	$TAG_TO_COL['jp_network_fax'] = "COL_25";
	//問合せ備考
	$TAG_TO_COL['jp_network_note'] = "COL_26";
	//ゆうゆう窓口ユニークコード
	$TAG_TO_COL['jp_post_code'] = "COL_27";
	//固有郵便番号
	$TAG_TO_COL['jp_post_zip'] = "COL_28";
	//郵便支店名
	$TAG_TO_COL['jp_post_name'] = "COL_29";
	//郵便支店名(全角かな字) 
	$TAG_TO_COL['jp_post_kana'] = "COL_30";
	//郵便支店区分
	$TAG_TO_COL['jp_post_class'] = "COL_31";
	//郵便支店取扱内容(備考) 
	$TAG_TO_COL['jp_post_handling_note'] = "COL_32";
	//代表電話番号
	$TAG_TO_COL['jp_post_tel1'] = "COL_33";
	//集荷電話番号
	$TAG_TO_COL['jp_post_tel2'] = "COL_34";
	//問合せ備考
	$TAG_TO_COL['jp_post_note'] = "COL_35";
	//ゆうちょ店ユニークコード
	$TAG_TO_COL['jp_bank_code'] = "COL_36";
	//銀行直営店名
	$TAG_TO_COL['jp_bank_name'] = "COL_37";
	//銀行直営店名(全角かな字) 
	$TAG_TO_COL['jp_bank_kana'] = "COL_38";
	//銀行直営店正式名
	$TAG_TO_COL['jp_bank_official_name'] = "COL_39";
	//区分(直営店／ATM出張所) 
	$TAG_TO_COL['jp_bank_class'] = "COL_40";
	//電話番号
	$TAG_TO_COL['jp_bank_tel'] = "COL_41";
	//問合せ備考
	$TAG_TO_COL['jp_bank_note'] = "COL_42";
	//かんぽユニークコード
	$TAG_TO_COL['jp_insurance_code'] = "COL_43";
	//かんぽ支店名
	$TAG_TO_COL['jp_insurance_name'] = "COL_44";
	//かんぽ支店名(全角かな字) 
	$TAG_TO_COL['jp_insurance_kana'] = "COL_45";
	//かんぽ支店区分
	$TAG_TO_COL['jp_insurance_class'] = "COL_46";
	//支店URL 
	$TAG_TO_COL['jp_insurance_url'] = "COL_47";
	//電話番号１ 
	$TAG_TO_COL['jp_insurance_tel1'] = "COL_48";
	//電話番号２ 
	$TAG_TO_COL['jp_insurance_tel2'] = "COL_49";
	//問合せ備考
	$TAG_TO_COL['jp_insurance_note'] = "COL_50";
	//郵便窓口
	$TAG_TO_COL['post_window'] = "COL_51";
	//印紙の売りさばき
	$TAG_TO_COL['stamp_sale'] = "COL_52";
	//国内物流事業に係る窓口
	$TAG_TO_COL['home_window'] = "COL_53";
	//チルドゆうパック
	$TAG_TO_COL['chilled_yu_pack'] = "COL_54";
	//内容証明
	$TAG_TO_COL['contents_certified'] = "COL_55";
	//取次ぎサービス
	$TAG_TO_COL['agency_service'] = "COL_56";
	//通常貯金
	$TAG_TO_COL['regular_savings'] = "COL_57";
	//通常貯蓄貯金
	$TAG_TO_COL['money_market_account'] = "COL_58";
	//定額貯金
	$TAG_TO_COL['fixed_deposit'] = "COL_59";
	//自動積立定額貯金
	$TAG_TO_COL['auto_fixed_deposit'] = "COL_60";
	//定期貯金
	$TAG_TO_COL['time_deposit'] = "COL_61";
	//自動積立定期貯金
	$TAG_TO_COL['auto_time_deposit'] = "COL_62";
	//満期一括受取型定期貯金
	$TAG_TO_COL['expiration_time_deposit'] = "COL_63";
	//ニュー福祉定期貯金
	$TAG_TO_COL['welfare_time_deposit'] = "COL_64";
	//財形定額貯金
	$TAG_TO_COL['asset_building_savings'] = "COL_65";
	//財産形成住宅定期貯金
	$TAG_TO_COL['asset_building_savings_housing'] = "COL_66";
	//財産形成年金定期貯金
	$TAG_TO_COL['asset_building_savings_pension'] = "COL_67";
	//普通為替
	$TAG_TO_COL['normal_exchange'] = "COL_68";
	//定額小為替
	$TAG_TO_COL['fixed_exchange'] = "COL_69";
	//ATMによる通常払込み
	$TAG_TO_COL['atm_payment'] = "COL_70";
	//公金払込み
	$TAG_TO_COL['public_payment'] = "COL_71";
	//通常払込み
	$TAG_TO_COL['normal_payment'] = "COL_72";
	//電信払込み
	$TAG_TO_COL['telegraphic_payment'] = "COL_73";
	//電信振替
	$TAG_TO_COL['telegraphic_transfer'] = "COL_74";
	//相互送金
	$TAG_TO_COL['mutual_transfer'] = "COL_75";
	//自動払込み
	$TAG_TO_COL['auto_payment'] = "COL_76";
	//自動送金
	$TAG_TO_COL['auto_transfer'] = "COL_77";
	//貯金小切手の振出
	$TAG_TO_COL['cheque'] = "COL_78";
	//自動払出預入
	$TAG_TO_COL['auto_deposit'] = "COL_79";
	//簡易払い(利用申込み・払出しの請求) 
	$TAG_TO_COL['simple_payment_request'] = "COL_80";
	//簡易払い(払い渡し) 
	$TAG_TO_COL['simple_payment_transfer'] = "COL_81";
	//通常現金払
	$TAG_TO_COL['normal_cash_payment'] = "COL_82";
	//電信現金払(窓口払) 
	$TAG_TO_COL['telegraphic_cash_payment'] = "COL_83";
	//給与預入
	$TAG_TO_COL['salary_deposit'] = "COL_84";
	//国際送金
	$TAG_TO_COL['international_transfer'] = "COL_85";
	//外貨両替/トラベラーズチェック
	$TAG_TO_COL['foreign_currency'] = "COL_86";
	//国民年金
	$TAG_TO_COL['national_pension'] = "COL_87";
	//反則金
	$TAG_TO_COL['penalty'] = "COL_88";
	//国民年金・反則金以外の歳入金
	$TAG_TO_COL['revenue'] = "COL_89";
	//歳出金
	$TAG_TO_COL['expenditure'] = "COL_90";
	//無記名国債(国債) 
	$TAG_TO_COL['government_bonds'] = "COL_91";
	//投資信託
	$TAG_TO_COL['investment_trust'] = "COL_92";
	//変額年金保険
	$TAG_TO_COL['variable_pension'] = "COL_93";
	//確定拠出年金
	$TAG_TO_COL['defined_contribution'] = "COL_94";
	//住宅ローン・フリーローン
	$TAG_TO_COL['suruga_loan'] = "COL_95";
	//かんぽ生命保険募集
	$TAG_TO_COL['jp_insurance_recruit'] = "COL_96";
	//紹介代理店
	$TAG_TO_COL['introduction_agency'] = "COL_97";
	//かんぽ生命保険維持管理業務
	$TAG_TO_COL['jp_insurance_maintenance'] = "COL_98";
	//簡易生命保険管理業務
	$TAG_TO_COL['kampo_maintenance'] = "COL_99";
	//かんぽ生命以外の生命保険募集
	$TAG_TO_COL['except_jp_insurance_recruit'] = "COL_100";
	//自動車保険募集
	$TAG_TO_COL['automobile_insurance'] = "COL_101";
	//自賠責保険募集
	$TAG_TO_COL['liability_insurance'] = "COL_102";
	//ガン保険募集
	$TAG_TO_COL['cancer_insurance'] = "COL_103";
	//引受条件緩和型医療保険
	$TAG_TO_COL['condition_medical_insurance'] = "COL_104";
	//地方公共団体事務
	$TAG_TO_COL['local_public_entity'] = "COL_105";
	//証明書交付事務
	$TAG_TO_COL['certificate_grant'] = "COL_106";
	//証明書交付事務の内訳
	$TAG_TO_COL['breakdown_certificate_grant'] = "COL_107";
	//受託窓口事務(受託販売事務) 
	$TAG_TO_COL['trust_sale'] = "COL_108";
	//受託窓口事務(受託販売事務)の内容
	$TAG_TO_COL['trust_sale_contents'] = "COL_109";
	//受託窓口事務(受託交付事務) 
	$TAG_TO_COL['trust_grant'] = "COL_110";
	//受託窓口事務(受託交付事務)の内容
	$TAG_TO_COL['trust_grant_contents'] = "COL_111";
	//その他の地方公共団体事務
	$TAG_TO_COL['other_local_public'] = "COL_112";
	//その他の地方公共団体事務の内容
	$TAG_TO_COL['other_local_public_contents'] = "COL_113";
	//宝くじ
	$TAG_TO_COL['lottery'] = "COL_114";
	//カタログ販売
	$TAG_TO_COL['catalog_sale'] = "COL_115";
	//郵便平日開始時間
	$TAG_TO_COL['jp_network_start'] = "COL_119";
	//郵便平日終了時間
	$TAG_TO_COL['jp_network_end'] = "COL_120";
	//郵便土曜開始時間
	$TAG_TO_COL['jp_network_sat_start'] = "COL_121";
	//郵便土曜終了時間
	$TAG_TO_COL['jp_network_sat_end'] = "COL_122";
	//郵便日曜・休日開始時間
	$TAG_TO_COL['jp_network_sun_start'] = "COL_123";
	//郵便日曜・休日終了時間
	$TAG_TO_COL['jp_network_sun_end'] = "COL_124";
	//郵便窓口定休日
	$TAG_TO_COL['jp_network_win_closed'] = "COL_125";
	//郵便窓口備考
	$TAG_TO_COL['jp_network_win_note'] = "COL_126";
	//貯金平日開始時間
	$TAG_TO_COL['jp_bank_start'] = "COL_127";
	//貯金平日終了時間
	$TAG_TO_COL['jp_bank_end'] = "COL_128";
	//貯金土曜開始時間
	$TAG_TO_COL['jp_bank_sat_start'] = "COL_129";
	//貯金土曜終了時間
	$TAG_TO_COL['jp_bank_sat_end'] = "COL_130";
	//貯金日曜・休日開始時間
	$TAG_TO_COL['jp_bank_sun_start'] = "COL_131";
	//貯金日曜・休日終了時間
	$TAG_TO_COL['jp_bank_sun_end'] = "COL_132";
	//銀行窓口定休日
	$TAG_TO_COL['jp_bank_win_closed'] = "COL_133";
	//銀行窓口備考
	$TAG_TO_COL['jp_bank_win_note'] = "COL_134";
	//ATM平日開始時間
	$TAG_TO_COL['atm_start'] = "COL_135";
	//ATM平日終了時間
	$TAG_TO_COL['atm_end'] = "COL_136";
	//ATM土曜開始時間
	$TAG_TO_COL['atm_sat_start'] = "COL_137";
	//ATM土曜終了時間
	$TAG_TO_COL['atm_sat_end'] = "COL_138";
	//ATM日曜・休日開始時間
	$TAG_TO_COL['atm_sun_start'] = "COL_139";
	//ATM日曜・休日終了時間
	$TAG_TO_COL['atm_sun_end'] = "COL_140";
	//ATM定休日
	$TAG_TO_COL['atm_closed'] = "COL_141";
	//ATM備考
	$TAG_TO_COL['atm_note'] = "COL_142";
	//保険平日開始時間
	$TAG_TO_COL['jp_network_insurance_start'] = "COL_143";
	//保険平日終了時間
	$TAG_TO_COL['jp_network_insurance_end'] = "COL_144";
	//保険土曜開始時間
	$TAG_TO_COL['jp_network_insurance_sat_start'] = "COL_145";
	//保険土曜終了時間
	$TAG_TO_COL['jp_network_insurance_sat_end'] = "COL_146";
	//保険日曜・休日開始時間
	$TAG_TO_COL['jp_network_insurance_sun_start'] = "COL_147";
	//保険日曜・休日終了時間
	$TAG_TO_COL['jp_network_insurance_sun_end'] = "COL_148";
	//保険窓口定休日
	$TAG_TO_COL['jp_network_insurance_win_closed'] = "COL_149";
	//保険窓口備考
	$TAG_TO_COL['jp_network_insurance_win_note'] = "COL_150";
	//ゆうゆう平日開始時間
	$TAG_TO_COL['jp_post_start'] = "COL_151";
	//ゆうゆう平日終了時間
	$TAG_TO_COL['jp_post_end'] = "COL_152";
	//ゆうゆう土曜開始時間
	$TAG_TO_COL['jp_post_sat_start'] = "COL_153";
	//ゆうゆう土曜終了時間
	$TAG_TO_COL['jp_post_sat_end'] = "COL_154";
	//ゆうゆう日曜・休日開始時間
	$TAG_TO_COL['jp_post_sun_start'] = "COL_155";
	//ゆうゆう日曜・休日終了時間
	$TAG_TO_COL['jp_post_sun_end'] = "COL_156";
	//ゆうゆう窓口定休日
	$TAG_TO_COL['jp_post_win_closed'] = "COL_157";
	//ゆうゆう窓口備考
	$TAG_TO_COL['jp_post_win_note'] = "COL_158";
	//かんぽ平日開始時間
	$TAG_TO_COL['jp_insurance_start'] = "COL_159";
	//かんぽ平日終了時間
	$TAG_TO_COL['jp_insurance_end'] = "COL_160";
	//かんぽ土曜開始時間
	$TAG_TO_COL['jp_insurance_sat_start'] = "COL_161";
	//かんぽ土曜終了時間
	$TAG_TO_COL['jp_insurance_sat_end'] = "COL_162";
	//かんぽ日曜・休日開始時間
	$TAG_TO_COL['jp_insurance_sun_start'] = "COL_163";
	//かんぽ日曜・休日終了時間
	$TAG_TO_COL['jp_insurance_sun_end'] = "COL_164";
	//かんぽ窓口定休日
	$TAG_TO_COL['jp_insurance_win_closed'] = "COL_165";
	//かんぽ窓口備考
	$TAG_TO_COL['jp_insurance_win_note'] = "COL_166";
	//小切手払い
	$TAG_TO_COL['reserve_flag1'] = "COL_167";
	//カードローン
	$TAG_TO_COL['reserve_flag2'] = "COL_168";
	//反映日時
	$TAG_TO_COL['reflect_date'] = "PUB_S_DATE";
	
?>