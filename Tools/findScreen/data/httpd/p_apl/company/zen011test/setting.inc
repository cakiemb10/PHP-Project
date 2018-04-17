<?PHP
//--------------------------------------------
// E-MAP区分（S：スタンダード、L：ライト、N：マップリンク）
//--------------------------------------------
$D_SERVICE_TYPE = "S";

//--------------------------------------------
//リファラー認証
//--------------------------------------------
//許可リファラー
$D_ALLOW_REFERER  = "*";
//NULL許可
$D_ALLOW_REFERER_NULL = 1;

//--------------------------------------------
// アクセス元IP認証
//--------------------------------------------
//許可IP
//$D_ALLOW_IP = "";

//--------------------------------------------
//BASIC認証
//--------------------------------------------
$D_BASIC_AUTH["dev"]  = 1;
$D_BASIC_AUTH["test"] = 1;
$D_BASIC_AUTH["www"]  = 0;

//--------------------------------------------
// SSL接続（httpsアクセス）
//--------------------------------------------
$D_SSL_ACCESS = 0;

//--------------------------------------------
// iPhoneからのアクセスを携帯へリダイレクト
//--------------------------------------------
$D_IPHONE_REDIRECT = 0;
//--------------------------------------------
// Androidからのアクセスを携帯へリダイレクト
//--------------------------------------------
$D_ANDROID_REDIRECT = 0;

//--------------------------------------------
// iPhoneからのアクセスをスマホへリダイレクト
//--------------------------------------------
$D_IPHONE_REDIRECT_SMT = 1;
//--------------------------------------------
// iPadからのアクセスをスマホへリダイレクト
//--------------------------------------------
//$D_IPAD_REDIRECT_SMT = ;
//--------------------------------------------
// Androidからのアクセスをスマホへリダイレクト
//--------------------------------------------
$D_ANDROID_REDIRECT_SMT = 1;

//--------------------------------------------
// 携帯URLをhttpsで表示
//--------------------------------------------
//$D_MBURL_HTTPS = ;

//--------------------------------------------
// TOPページ区分
//--------------------------------------------
$D_TOP_PAGE_KBN = '0';// 0：標準TOP、1：客先TOP、2：ZDC預り（asp）

//--------------------------------------------
// TOPページのリンク
//--------------------------------------------
//$D_HISTORY_TOP_LINK = "javascript:parent.location.href='';";

//--------------------------------------------
//表示
//--------------------------------------------
//拠点名表示文字列
$D_USER_DEFNAME = "店舗";
//フラグ項目表示欄
$D_USER_SERVICENAME = "サービス";

//--------------------------------------------
//地図表示
//--------------------------------------------
//初期地図表示位置(緯度)
$D_INIT_LAT = 128440300;
//初期地図表示位置(経度)
$D_INIT_LON = 503173140;

//初期表示縮尺
$D_INIT_LVL = 16;
//位置検索決定後
//（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
$D_INIT_LVL_SEARCH = 16;
//詳細選択後
//（-1：初期表示時は$D_INIT_LVLに準じ、再表示時は現縮尺のまま）
$D_INIT_LVL_DETAIL = 16;
//印刷画面
//（-1：$D_INIT_LVLに準じる）
$D_INIT_LVL_PRINT  = 16;

//拠点表示最小縮尺
$D_VIEW_ICON_MAX = 1;
//指定拠点以外非表示区分
$D_DSP_OTHER_KBN = 1;
//レイヤー区分
$D_MAP_LAYER_KBN = 2;
//地図中心マーク
$D_MAPCENTER_MARK = "1";
//地図中心マーク（印刷画面）
$D_MAPCENTER_MARK_P = "0";

//--------------------------------------------
//拠点検索
//--------------------------------------------
//検索条件(AND,OR)
$D_SHOP_COND = "AND";
//拠点リスト行数
$D_SHOP_PAGE = 5;
//最大件数
$D_SHOP_MAX  = 10;
//詳細表示したらリスト消すか（0:消さない、1:消す）
$D_SHOP_CLOSELIST = "1";


//--------------------------------------------
//検索窓
//--------------------------------------------
//各リスト行数
$D_SEARCH_SHOPLIST_PAGE = 5;
//住所リストをどの階層まで掘り下げるか（1：都道府県、2：市区町村、3：大字、4：字丁目、5：街区、6：地番（枝番）
$D_ADDRL_BOTTOM_LVL = 6;

//--------------------------------------------
//拠点エリア検索の表示名称
//--------------------------------------------
// エリア検索
$D_HISTORY_NAME["ShopA"]   = "店舗リスト";	// 名称
$D_SEARCH_SHOPA_DISPNM[1]  = "住所";	// 第1階層
$D_SEARCH_SHOPA_DISPNM[2]  = "住所";	// 第2階層
// エリア検索２
$D_HISTORY_NAME["ShopA_2"] = "店舗リスト";	// 名称
$D_SEARCH_SHOPA_DISPNM[3]  = "住所";	// 第1階層
$D_SEARCH_SHOPA_DISPNM[4]  = "住所";	// 第2階層
// エリア検索３
$D_HISTORY_NAME["ShopA_3"] = "店舗リスト";	// 名称
$D_SEARCH_SHOPA_DISPNM[5]  = "住所";	// 第1階層
$D_SEARCH_SHOPA_DISPNM[6]  = "住所";	// 第2階層
// エリア検索４
$D_HISTORY_NAME["ShopA_4"] = "店舗リスト";	// 名称
$D_SEARCH_SHOPA_DISPNM[7]  = "住所";	// 第1階層
$D_SEARCH_SHOPA_DISPNM[8]  = "住所";	// 第2階層
// エリア検索５
$D_HISTORY_NAME["ShopA_5"] = "店舗リスト";	// 名称
$D_SEARCH_SHOPA_DISPNM[9]  = "住所";	// 第1階層
$D_SEARCH_SHOPA_DISPNM[10] = "住所";	// 第2階層

//--------------------------------------------
//最寄駅検索
//--------------------------------------------
$D_ST_RAD = 5000;

//--------------------------------------------
//最寄施設検索
//--------------------------------------------
//最大件数
$D_POI_MAX = 50;
//ジャンル可変
$arr_D_POI_JNRMN = array();
$arr_D_POI_JNRMN[] = '00160';
$arr_D_POI_JNRMN[] = '00250';
$arr_D_POI_JNRMN[] = '00140';
$arr_D_POI_JNRMN[] = '00170';
$arr_D_POI_JNRMN[] = '00220';
$arr_D_POI_JNRMN[] = '00240';
$arr_D_POI_JNRMN[] = '00130';
$arr_D_POI_JNRMN[] = '00110';
$arr_D_POI_JNRMN[] = '00120';
if (count($arr_D_POI_JNRMN)) $D_POI_JNRMN = implode(',', $arr_D_POI_JNRMN);

//--------------------------------------------
//動作
//--------------------------------------------
//ルート検索
$D_ROUTE_TYPE	 = 1;
//拠点アイコンクリック
$D_KYO_ICON_CLK  = 1;
// 拠点アイコン重なり時に吹き出しにまとめて表示
$D_KYO_ICON_OVERLAP = 0;

//--------------------------------------------
//接続I/F
//--------------------------------------------
//Standard住所接続I/F
$D_STANDARD_ADDR_IF = 0;

//--------------------------------------------
//項目名
//--------------------------------------------
//拠点一覧
$D_KYO_COL_NAME[0][0] = "col_01";
$D_KYO_COL_NAME[0][1] = "col_02";
$D_KYO_COL_NAME[0][2] = "col_03";
$D_KYO_COL_NAME[0][3] = "col_04";
$D_KYO_COL_NAME[0][4] = "name";
$D_KYO_COL_NAME[0][5] = "col_07";
$D_KYO_COL_NAME[0][6] = "addr";
$D_KYO_COL_NAME[0][7] = "col_08";
$D_KYO_COL_NAME[0][8] = "col_09";
$D_KYO_COL_NAME[0][9] = "col_10";
$D_KYO_COL_NAME[0][10] = "col_12";
$D_KYO_COL_NAME[0][11] = "col_13";
$D_KYO_COL_NAME[0][12] = "col_14";
$D_KYO_COL_NAME[0][13] = "col_15";
$D_KYO_COL_NAME[0][14] = "col_16";
$D_KYO_COL_NAME[0][15] = "col_17";
$D_KYO_COL_NAME[0][16] = "col_18";
$D_KYO_COL_NAME[0][17] = "col_19";
$D_KYO_COL_NAME[0][18] = "col_20";
$D_KYO_COL_NAME[0][19] = "col_21";
$D_KYO_COL_NAME[0][20] = "col_22";
$D_KYO_COL_NAME[0][21] = "col_23";
$D_KYO_COL_NAME[0][22] = "col_24";
$D_KYO_COL_NAME[0][23] = "col_25";
$D_KYO_COL_NAME[0][24] = "col_26";
$D_KYO_COL_NAME[0][25] = "col_27";
$D_KYO_COL_NAME[0][26] = "col_28";
$D_KYO_COL_NAME[0][27] = "col_29";
$D_KYO_COL_NAME[0][28] = "col_30";
$D_KYO_COL_NAME[0][29] = "col_31";
$D_KYO_COL_NAME[0][30] = "col_32";
$D_KYO_COL_NAME[0][31] = "col_33";
$D_KYO_COL_NAME[0][32] = "col_34";
$D_KYO_COL_NAME[0][33] = "col_35";
$D_KYO_COL_NAME[0][34] = "col_36";
$D_KYO_COL_NAME[0][35] = "col_37";
$D_KYO_COL_NAME[0][36] = "col_38";
$D_KYO_COL_NAME[0][37] = "col_39";
$D_KYO_COL_NAME[0][38] = "col_40";
$D_KYO_COL_NAME[0][39] = "col_41";
$D_KYO_COL_NAME[0][40] = "col_42";
$D_KYO_COL_NAME[0][41] = "col_43";
$D_KYO_COL_NAME[0][42] = "col_44";
$D_KYO_COL_NAME[0][43] = "col_45";
$D_KYO_COL_NAME[0][44] = "col_46";
$D_KYO_COL_NAME[0][45] = "col_47";
$D_KYO_COL_NAME[0][46] = "col_48";
$D_KYO_COL_NAME[0][47] = "col_49";
$D_KYO_COL_NAME[0][48] = "col_50";
$D_KYO_COL_NAME[0][49] = "col_51";
$D_KYO_COL_NAME[0][50] = "col_52";
$D_KYO_COL_NAME[0][51] = "col_53";
$D_KYO_COL_NAME[0][52] = "col_54";
$D_KYO_COL_NAME[0][53] = "col_55";
$D_KYO_COL_NAME[0][54] = "col_56";
$D_KYO_COL_NAME[0][55] = "col_57";
$D_KYO_COL_NAME[0][56] = "col_58";
$D_KYO_COL_NAME[0][57] = "col_59";
$D_KYO_COL_NAME[0][58] = "col_60";
$D_KYO_COL_NAME[0][59] = "col_61";
$D_KYO_COL_NAME[0][60] = "col_62";
$D_KYO_COL_NAME[0][61] = "col_63";
$D_KYO_COL_NAME[0][62] = "col_64";
$D_KYO_COL_NAME[0][63] = "col_65";
$D_KYO_COL_NAME[0][64] = "col_66";
$D_KYO_COL_NAME[0][65] = "col_67";
$D_KYO_COL_NAME[0][66] = "col_68";
$D_KYO_COL_NAME[0][67] = "col_69";
$D_KYO_COL_NAME[0][68] = "col_70";
$D_KYO_COL_NAME[0][69] = "col_71";
$D_KYO_COL_NAME[0][70] = "col_72";
$D_KYO_COL_NAME[0][71] = "col_73";
$D_KYO_COL_NAME[0][72] = "col_74";
$D_KYO_COL_NAME[0][73] = "col_75";
$D_KYO_COL_NAME[0][74] = "col_76";
$D_KYO_COL_NAME[0][75] = "col_77";
$D_KYO_COL_NAME[0][76] = "col_78";
$D_KYO_COL_NAME[0][77] = "col_79";
$D_KYO_COL_NAME[0][78] = "col_80";
$D_KYO_COL_NAME[0][79] = "col_81";
$D_KYO_COL_NAME[0][80] = "col_82";
$D_KYO_COL_NAME[0][81] = "col_83";
$D_KYO_COL_NAME[0][82] = "col_84";
$D_KYO_COL_NAME[0][83] = "col_85";
$D_KYO_COL_NAME[0][84] = "col_86";
$D_KYO_COL_NAME[0][85] = "col_87";
$D_KYO_COL_NAME[0][86] = "col_88";
$D_KYO_COL_NAME[0][87] = "col_89";
$D_KYO_COL_NAME[0][88] = "col_90";
$D_KYO_COL_NAME[0][89] = "col_91";
$D_KYO_COL_NAME[0][90] = "col_92";
$D_KYO_COL_NAME[0][91] = "col_93";
$D_KYO_COL_NAME[0][92] = "col_94";
$D_KYO_COL_NAME[0][93] = "col_95";
$D_KYO_COL_NAME[0][94] = "col_96";
$D_KYO_COL_NAME[0][95] = "col_97";
$D_KYO_COL_NAME[0][96] = "col_98";
$D_KYO_COL_NAME[0][97] = "col_99";
$D_KYO_COL_NAME[0][98] = "col_100";
$D_KYO_COL_NAME[0][99] = "col_101";
$D_KYO_COL_NAME[0][100] = "col_102";
$D_KYO_COL_NAME[0][101] = "col_103";
$D_KYO_COL_NAME[0][102] = "col_104";
$D_KYO_COL_NAME[0][103] = "col_105";
$D_KYO_COL_NAME[0][104] = "col_106";
$D_KYO_COL_NAME[0][105] = "col_107";
$D_KYO_COL_NAME[0][106] = "col_108";
$D_KYO_COL_NAME[0][107] = "col_144";
//吹き出し
$D_KYO_COL_NAME[3][0] = "col_01";
$D_KYO_COL_NAME[3][1] = "col_02";
$D_KYO_COL_NAME[3][2] = "col_03";
$D_KYO_COL_NAME[3][3] = "col_04";
$D_KYO_COL_NAME[3][4] = "name";
$D_KYO_COL_NAME[3][5] = "col_07";
$D_KYO_COL_NAME[3][6] = "addr";
$D_KYO_COL_NAME[3][7] = "col_08";
$D_KYO_COL_NAME[3][8] = "col_09";
$D_KYO_COL_NAME[3][9] = "col_10";
$D_KYO_COL_NAME[3][10] = "col_12";
$D_KYO_COL_NAME[3][11] = "col_13";
$D_KYO_COL_NAME[3][12] = "col_14";
$D_KYO_COL_NAME[3][13] = "col_15";
$D_KYO_COL_NAME[3][14] = "col_16";
$D_KYO_COL_NAME[3][15] = "col_17";
$D_KYO_COL_NAME[3][16] = "col_18";
$D_KYO_COL_NAME[3][17] = "col_19";
$D_KYO_COL_NAME[3][18] = "col_20";
$D_KYO_COL_NAME[3][19] = "col_21";
$D_KYO_COL_NAME[3][20] = "col_22";
$D_KYO_COL_NAME[3][21] = "col_23";
$D_KYO_COL_NAME[3][22] = "col_24";
$D_KYO_COL_NAME[3][23] = "col_25";
$D_KYO_COL_NAME[3][24] = "col_26";
$D_KYO_COL_NAME[3][25] = "col_27";
$D_KYO_COL_NAME[3][26] = "col_28";
$D_KYO_COL_NAME[3][27] = "col_29";
$D_KYO_COL_NAME[3][28] = "col_30";
$D_KYO_COL_NAME[3][29] = "col_31";
$D_KYO_COL_NAME[3][30] = "col_32";
$D_KYO_COL_NAME[3][31] = "col_33";
$D_KYO_COL_NAME[3][32] = "col_34";
$D_KYO_COL_NAME[3][33] = "col_35";
$D_KYO_COL_NAME[3][34] = "col_36";
$D_KYO_COL_NAME[3][35] = "col_37";
$D_KYO_COL_NAME[3][36] = "col_38";
$D_KYO_COL_NAME[3][37] = "col_39";
$D_KYO_COL_NAME[3][38] = "col_40";
$D_KYO_COL_NAME[3][39] = "col_41";
$D_KYO_COL_NAME[3][40] = "col_42";
$D_KYO_COL_NAME[3][41] = "col_43";
$D_KYO_COL_NAME[3][42] = "col_44";
$D_KYO_COL_NAME[3][43] = "col_45";
$D_KYO_COL_NAME[3][44] = "col_46";
$D_KYO_COL_NAME[3][45] = "col_47";
$D_KYO_COL_NAME[3][46] = "col_48";
$D_KYO_COL_NAME[3][47] = "col_49";
$D_KYO_COL_NAME[3][48] = "col_50";
$D_KYO_COL_NAME[3][49] = "col_51";
$D_KYO_COL_NAME[3][50] = "col_52";
$D_KYO_COL_NAME[3][51] = "col_53";
$D_KYO_COL_NAME[3][52] = "col_54";
$D_KYO_COL_NAME[3][53] = "col_55";
$D_KYO_COL_NAME[3][54] = "col_56";
$D_KYO_COL_NAME[3][55] = "col_57";
$D_KYO_COL_NAME[3][56] = "col_58";
$D_KYO_COL_NAME[3][57] = "col_59";
$D_KYO_COL_NAME[3][58] = "col_60";
$D_KYO_COL_NAME[3][59] = "col_61";
$D_KYO_COL_NAME[3][60] = "col_62";
$D_KYO_COL_NAME[3][61] = "col_63";
$D_KYO_COL_NAME[3][62] = "col_64";
$D_KYO_COL_NAME[3][63] = "col_65";
$D_KYO_COL_NAME[3][64] = "col_66";
$D_KYO_COL_NAME[3][65] = "col_67";
$D_KYO_COL_NAME[3][66] = "col_68";
$D_KYO_COL_NAME[3][67] = "col_69";
$D_KYO_COL_NAME[3][68] = "col_70";
$D_KYO_COL_NAME[3][69] = "col_71";
$D_KYO_COL_NAME[3][70] = "col_72";
$D_KYO_COL_NAME[3][71] = "col_73";
$D_KYO_COL_NAME[3][72] = "col_74";
$D_KYO_COL_NAME[3][73] = "col_75";
$D_KYO_COL_NAME[3][74] = "col_76";
$D_KYO_COL_NAME[3][75] = "col_77";
$D_KYO_COL_NAME[3][76] = "col_78";
$D_KYO_COL_NAME[3][77] = "col_79";
$D_KYO_COL_NAME[3][78] = "col_80";
$D_KYO_COL_NAME[3][79] = "col_81";
$D_KYO_COL_NAME[3][80] = "col_82";
$D_KYO_COL_NAME[3][81] = "col_83";
$D_KYO_COL_NAME[3][82] = "col_84";
$D_KYO_COL_NAME[3][83] = "col_85";
$D_KYO_COL_NAME[3][84] = "col_86";
$D_KYO_COL_NAME[3][85] = "col_87";
$D_KYO_COL_NAME[3][86] = "col_88";
$D_KYO_COL_NAME[3][87] = "col_89";
$D_KYO_COL_NAME[3][88] = "col_90";
$D_KYO_COL_NAME[3][89] = "col_91";
$D_KYO_COL_NAME[3][90] = "col_92";
$D_KYO_COL_NAME[3][91] = "col_93";
$D_KYO_COL_NAME[3][92] = "col_94";
$D_KYO_COL_NAME[3][93] = "col_95";
$D_KYO_COL_NAME[3][94] = "col_96";
$D_KYO_COL_NAME[3][95] = "col_97";
$D_KYO_COL_NAME[3][96] = "col_98";
$D_KYO_COL_NAME[3][97] = "col_99";
$D_KYO_COL_NAME[3][98] = "col_100";
$D_KYO_COL_NAME[3][99] = "col_101";
$D_KYO_COL_NAME[3][100] = "col_102";
$D_KYO_COL_NAME[3][101] = "col_103";
$D_KYO_COL_NAME[3][102] = "col_104";
$D_KYO_COL_NAME[3][103] = "col_105";
$D_KYO_COL_NAME[3][104] = "col_106";
$D_KYO_COL_NAME[3][105] = "col_107";
$D_KYO_COL_NAME[3][106] = "col_108";
$D_KYO_COL_NAME[3][107] = "col_109";
$D_KYO_COL_NAME[3][108] = "col_110";
$D_KYO_COL_NAME[3][109] = "col_111";
$D_KYO_COL_NAME[3][110] = "col_112";
$D_KYO_COL_NAME[3][111] = "col_113";
$D_KYO_COL_NAME[3][112] = "col_114";
$D_KYO_COL_NAME[3][113] = "col_115";
$D_KYO_COL_NAME[3][114] = "col_116";
$D_KYO_COL_NAME[3][115] = "col_117";
$D_KYO_COL_NAME[3][116] = "col_118";
$D_KYO_COL_NAME[3][117] = "col_119";
$D_KYO_COL_NAME[3][118] = "col_120";
$D_KYO_COL_NAME[3][119] = "col_121";
$D_KYO_COL_NAME[3][120] = "col_122";
$D_KYO_COL_NAME[3][121] = "col_123";
$D_KYO_COL_NAME[3][122] = "col_124";
$D_KYO_COL_NAME[3][123] = "col_125";
$D_KYO_COL_NAME[3][124] = "col_126";
$D_KYO_COL_NAME[3][125] = "col_127";
$D_KYO_COL_NAME[3][126] = "col_128";
$D_KYO_COL_NAME[3][127] = "col_129";
$D_KYO_COL_NAME[3][128] = "col_130";
$D_KYO_COL_NAME[3][129] = "col_131";
$D_KYO_COL_NAME[3][130] = "col_132";
$D_KYO_COL_NAME[3][131] = "col_133";
$D_KYO_COL_NAME[3][132] = "col_134";
$D_KYO_COL_NAME[3][133] = "col_135";
$D_KYO_COL_NAME[3][134] = "col_136";
$D_KYO_COL_NAME[3][135] = "col_137";
$D_KYO_COL_NAME[3][136] = "col_138";
$D_KYO_COL_NAME[3][137] = "col_139";
$D_KYO_COL_NAME[3][138] = "col_140";
$D_KYO_COL_NAME[3][139] = "col_141";
$D_KYO_COL_NAME[3][140] = "col_142";
$D_KYO_COL_NAME[3][141] = "col_143";
$D_KYO_COL_NAME[3][142] = "col_144";
$D_KYO_COL_NAME[3][143] = "col_145";
$D_KYO_COL_NAME[3][144] = "col_146";
$D_KYO_COL_NAME[3][145] = "col_147";
$D_KYO_COL_NAME[3][146] = "col_148";
$D_KYO_COL_NAME[3][147] = "col_149";
$D_KYO_COL_NAME[3][148] = "col_150";
$D_KYO_COL_NAME[3][149] = "col_151";
$D_KYO_COL_NAME[3][150] = "col_152";
$D_KYO_COL_NAME[3][151] = "col_153";
$D_KYO_COL_NAME[3][152] = "col_154";
$D_KYO_COL_NAME[3][153] = "col_155";
$D_KYO_COL_NAME[3][154] = "col_156";
$D_KYO_COL_NAME[3][155] = "col_157";
$D_KYO_COL_NAME[3][156] = "col_158";
//拠点詳細
$D_KYO_COL_NAME[1][0] = "col_01";
$D_KYO_COL_NAME[1][1] = "col_02";
$D_KYO_COL_NAME[1][2] = "col_03";
$D_KYO_COL_NAME[1][3] = "col_04";
$D_KYO_COL_NAME[1][4] = "name";
$D_KYO_COL_NAME[1][5] = "col_07";
$D_KYO_COL_NAME[1][6] = "addr";
$D_KYO_COL_NAME[1][7] = "col_08";
$D_KYO_COL_NAME[1][8] = "col_09";
$D_KYO_COL_NAME[1][9] = "col_10";
$D_KYO_COL_NAME[1][10] = "col_12";
$D_KYO_COL_NAME[1][11] = "col_13";
$D_KYO_COL_NAME[1][12] = "col_14";
$D_KYO_COL_NAME[1][13] = "col_15";
$D_KYO_COL_NAME[1][14] = "col_16";
$D_KYO_COL_NAME[1][15] = "col_17";
$D_KYO_COL_NAME[1][16] = "col_18";
$D_KYO_COL_NAME[1][17] = "col_19";
$D_KYO_COL_NAME[1][18] = "col_20";
$D_KYO_COL_NAME[1][19] = "col_21";
$D_KYO_COL_NAME[1][20] = "col_22";
$D_KYO_COL_NAME[1][21] = "col_23";
$D_KYO_COL_NAME[1][22] = "col_24";
$D_KYO_COL_NAME[1][23] = "col_25";
$D_KYO_COL_NAME[1][24] = "col_26";
$D_KYO_COL_NAME[1][25] = "col_27";
$D_KYO_COL_NAME[1][26] = "col_28";
$D_KYO_COL_NAME[1][27] = "col_29";
$D_KYO_COL_NAME[1][28] = "col_30";
$D_KYO_COL_NAME[1][29] = "col_31";
$D_KYO_COL_NAME[1][30] = "col_32";
$D_KYO_COL_NAME[1][31] = "col_33";
$D_KYO_COL_NAME[1][32] = "col_34";
$D_KYO_COL_NAME[1][33] = "col_35";
$D_KYO_COL_NAME[1][34] = "col_36";
$D_KYO_COL_NAME[1][35] = "col_37";
$D_KYO_COL_NAME[1][36] = "col_38";
$D_KYO_COL_NAME[1][37] = "col_39";
$D_KYO_COL_NAME[1][38] = "col_40";
$D_KYO_COL_NAME[1][39] = "col_41";
$D_KYO_COL_NAME[1][40] = "col_42";
$D_KYO_COL_NAME[1][41] = "col_43";
$D_KYO_COL_NAME[1][42] = "col_44";
$D_KYO_COL_NAME[1][43] = "col_45";
$D_KYO_COL_NAME[1][44] = "col_46";
$D_KYO_COL_NAME[1][45] = "col_47";
$D_KYO_COL_NAME[1][46] = "col_48";
$D_KYO_COL_NAME[1][47] = "col_49";
$D_KYO_COL_NAME[1][48] = "col_50";
$D_KYO_COL_NAME[1][49] = "col_51";
$D_KYO_COL_NAME[1][50] = "col_52";
$D_KYO_COL_NAME[1][51] = "col_53";
$D_KYO_COL_NAME[1][52] = "col_54";
$D_KYO_COL_NAME[1][53] = "col_55";
$D_KYO_COL_NAME[1][54] = "col_56";
$D_KYO_COL_NAME[1][55] = "col_57";
$D_KYO_COL_NAME[1][56] = "col_58";
$D_KYO_COL_NAME[1][57] = "col_59";
$D_KYO_COL_NAME[1][58] = "col_60";
$D_KYO_COL_NAME[1][59] = "col_61";
$D_KYO_COL_NAME[1][60] = "col_62";
$D_KYO_COL_NAME[1][61] = "col_63";
$D_KYO_COL_NAME[1][62] = "col_64";
$D_KYO_COL_NAME[1][63] = "col_65";
$D_KYO_COL_NAME[1][64] = "col_66";
$D_KYO_COL_NAME[1][65] = "col_67";
$D_KYO_COL_NAME[1][66] = "col_68";
$D_KYO_COL_NAME[1][67] = "col_69";
$D_KYO_COL_NAME[1][68] = "col_70";
$D_KYO_COL_NAME[1][69] = "col_71";
$D_KYO_COL_NAME[1][70] = "col_72";
$D_KYO_COL_NAME[1][71] = "col_73";
$D_KYO_COL_NAME[1][72] = "col_74";
$D_KYO_COL_NAME[1][73] = "col_75";
$D_KYO_COL_NAME[1][74] = "col_76";
$D_KYO_COL_NAME[1][75] = "col_77";
$D_KYO_COL_NAME[1][76] = "col_78";
$D_KYO_COL_NAME[1][77] = "col_79";
$D_KYO_COL_NAME[1][78] = "col_80";
$D_KYO_COL_NAME[1][79] = "col_81";
$D_KYO_COL_NAME[1][80] = "col_82";
$D_KYO_COL_NAME[1][81] = "col_83";
$D_KYO_COL_NAME[1][82] = "col_84";
$D_KYO_COL_NAME[1][83] = "col_85";
$D_KYO_COL_NAME[1][84] = "col_86";
$D_KYO_COL_NAME[1][85] = "col_87";
$D_KYO_COL_NAME[1][86] = "col_88";
$D_KYO_COL_NAME[1][87] = "col_89";
$D_KYO_COL_NAME[1][88] = "col_90";
$D_KYO_COL_NAME[1][89] = "col_91";
$D_KYO_COL_NAME[1][90] = "col_92";
$D_KYO_COL_NAME[1][91] = "col_93";
$D_KYO_COL_NAME[1][92] = "col_94";
$D_KYO_COL_NAME[1][93] = "col_95";
$D_KYO_COL_NAME[1][94] = "col_96";
$D_KYO_COL_NAME[1][95] = "col_97";
$D_KYO_COL_NAME[1][96] = "col_98";
$D_KYO_COL_NAME[1][97] = "col_99";
$D_KYO_COL_NAME[1][98] = "col_100";
$D_KYO_COL_NAME[1][99] = "col_101";
$D_KYO_COL_NAME[1][100] = "col_102";
$D_KYO_COL_NAME[1][101] = "col_103";
$D_KYO_COL_NAME[1][102] = "col_104";
$D_KYO_COL_NAME[1][103] = "col_105";
$D_KYO_COL_NAME[1][104] = "col_106";
$D_KYO_COL_NAME[1][105] = "col_107";
$D_KYO_COL_NAME[1][106] = "col_108";
$D_KYO_COL_NAME[1][107] = "col_109";
$D_KYO_COL_NAME[1][108] = "col_110";
$D_KYO_COL_NAME[1][109] = "col_111";
$D_KYO_COL_NAME[1][110] = "col_112";
$D_KYO_COL_NAME[1][111] = "col_113";
$D_KYO_COL_NAME[1][112] = "col_114";
$D_KYO_COL_NAME[1][113] = "col_115";
$D_KYO_COL_NAME[1][114] = "col_116";
$D_KYO_COL_NAME[1][115] = "col_117";
$D_KYO_COL_NAME[1][116] = "col_118";
$D_KYO_COL_NAME[1][117] = "col_119";
$D_KYO_COL_NAME[1][118] = "col_120";
$D_KYO_COL_NAME[1][119] = "col_121";
$D_KYO_COL_NAME[1][120] = "col_122";
$D_KYO_COL_NAME[1][121] = "col_123";
$D_KYO_COL_NAME[1][122] = "col_124";
$D_KYO_COL_NAME[1][123] = "col_125";
$D_KYO_COL_NAME[1][124] = "col_126";
$D_KYO_COL_NAME[1][125] = "col_127";
$D_KYO_COL_NAME[1][126] = "col_128";
$D_KYO_COL_NAME[1][127] = "col_129";
$D_KYO_COL_NAME[1][128] = "col_130";
$D_KYO_COL_NAME[1][129] = "col_131";
$D_KYO_COL_NAME[1][130] = "col_132";
$D_KYO_COL_NAME[1][131] = "col_133";
$D_KYO_COL_NAME[1][132] = "col_134";
$D_KYO_COL_NAME[1][133] = "col_135";
$D_KYO_COL_NAME[1][134] = "col_136";
$D_KYO_COL_NAME[1][135] = "col_137";
$D_KYO_COL_NAME[1][136] = "col_138";
$D_KYO_COL_NAME[1][137] = "col_139";
$D_KYO_COL_NAME[1][138] = "col_140";
$D_KYO_COL_NAME[1][139] = "col_141";
$D_KYO_COL_NAME[1][140] = "col_142";
$D_KYO_COL_NAME[1][141] = "col_143";
$D_KYO_COL_NAME[1][142] = "col_144";
$D_KYO_COL_NAME[1][143] = "col_145";
$D_KYO_COL_NAME[1][144] = "col_146";
$D_KYO_COL_NAME[1][145] = "col_147";
$D_KYO_COL_NAME[1][146] = "col_148";
$D_KYO_COL_NAME[1][147] = "col_149";
$D_KYO_COL_NAME[1][148] = "col_150";
$D_KYO_COL_NAME[1][149] = "col_151";
$D_KYO_COL_NAME[1][150] = "col_152";
$D_KYO_COL_NAME[1][151] = "col_153";
$D_KYO_COL_NAME[1][152] = "col_154";
$D_KYO_COL_NAME[1][153] = "col_155";
$D_KYO_COL_NAME[1][154] = "col_156";
$D_KYO_COL_NAME[1][155] = "col_157";
$D_KYO_COL_NAME[1][156] = "col_158";
//印刷
$D_KYO_COL_NAME[2][0] = "col_01";
$D_KYO_COL_NAME[2][1] = "col_02";
$D_KYO_COL_NAME[2][2] = "col_03";
$D_KYO_COL_NAME[2][3] = "col_04";
$D_KYO_COL_NAME[2][4] = "name";
$D_KYO_COL_NAME[2][5] = "col_07";
$D_KYO_COL_NAME[2][6] = "addr";
$D_KYO_COL_NAME[2][7] = "col_08";
$D_KYO_COL_NAME[2][8] = "col_09";
$D_KYO_COL_NAME[2][9] = "col_10";
$D_KYO_COL_NAME[2][10] = "col_12";
$D_KYO_COL_NAME[2][11] = "col_13";
$D_KYO_COL_NAME[2][12] = "col_14";
$D_KYO_COL_NAME[2][13] = "col_15";
$D_KYO_COL_NAME[2][14] = "col_16";
$D_KYO_COL_NAME[2][15] = "col_17";
$D_KYO_COL_NAME[2][16] = "col_18";
$D_KYO_COL_NAME[2][17] = "col_19";
$D_KYO_COL_NAME[2][18] = "col_20";
$D_KYO_COL_NAME[2][19] = "col_21";
$D_KYO_COL_NAME[2][20] = "col_22";
$D_KYO_COL_NAME[2][21] = "col_23";
$D_KYO_COL_NAME[2][22] = "col_24";
$D_KYO_COL_NAME[2][23] = "col_25";
$D_KYO_COL_NAME[2][24] = "col_26";
$D_KYO_COL_NAME[2][25] = "col_27";
$D_KYO_COL_NAME[2][26] = "col_28";
$D_KYO_COL_NAME[2][27] = "col_29";
$D_KYO_COL_NAME[2][28] = "col_30";
$D_KYO_COL_NAME[2][29] = "col_31";
$D_KYO_COL_NAME[2][30] = "col_32";
$D_KYO_COL_NAME[2][31] = "col_33";
$D_KYO_COL_NAME[2][32] = "col_34";
$D_KYO_COL_NAME[2][33] = "col_35";
$D_KYO_COL_NAME[2][34] = "col_36";
$D_KYO_COL_NAME[2][35] = "col_37";
$D_KYO_COL_NAME[2][36] = "col_38";
$D_KYO_COL_NAME[2][37] = "col_39";
$D_KYO_COL_NAME[2][38] = "col_40";
$D_KYO_COL_NAME[2][39] = "col_41";
$D_KYO_COL_NAME[2][40] = "col_42";
$D_KYO_COL_NAME[2][41] = "col_43";
$D_KYO_COL_NAME[2][42] = "col_44";
$D_KYO_COL_NAME[2][43] = "col_45";
$D_KYO_COL_NAME[2][44] = "col_46";
$D_KYO_COL_NAME[2][45] = "col_47";
$D_KYO_COL_NAME[2][46] = "col_48";
$D_KYO_COL_NAME[2][47] = "col_49";
$D_KYO_COL_NAME[2][48] = "col_50";
$D_KYO_COL_NAME[2][49] = "col_51";
$D_KYO_COL_NAME[2][50] = "col_52";
$D_KYO_COL_NAME[2][51] = "col_53";
$D_KYO_COL_NAME[2][52] = "col_54";
$D_KYO_COL_NAME[2][53] = "col_55";
$D_KYO_COL_NAME[2][54] = "col_56";
$D_KYO_COL_NAME[2][55] = "col_57";
$D_KYO_COL_NAME[2][56] = "col_58";
$D_KYO_COL_NAME[2][57] = "col_59";
$D_KYO_COL_NAME[2][58] = "col_60";
$D_KYO_COL_NAME[2][59] = "col_61";
$D_KYO_COL_NAME[2][60] = "col_62";
$D_KYO_COL_NAME[2][61] = "col_63";
$D_KYO_COL_NAME[2][62] = "col_64";
$D_KYO_COL_NAME[2][63] = "col_65";
$D_KYO_COL_NAME[2][64] = "col_66";
$D_KYO_COL_NAME[2][65] = "col_67";
$D_KYO_COL_NAME[2][66] = "col_68";
$D_KYO_COL_NAME[2][67] = "col_69";
$D_KYO_COL_NAME[2][68] = "col_70";
$D_KYO_COL_NAME[2][69] = "col_71";
$D_KYO_COL_NAME[2][70] = "col_72";
$D_KYO_COL_NAME[2][71] = "col_73";
$D_KYO_COL_NAME[2][72] = "col_74";
$D_KYO_COL_NAME[2][73] = "col_75";
$D_KYO_COL_NAME[2][74] = "col_76";
$D_KYO_COL_NAME[2][75] = "col_77";
$D_KYO_COL_NAME[2][76] = "col_78";
$D_KYO_COL_NAME[2][77] = "col_79";
$D_KYO_COL_NAME[2][78] = "col_80";
$D_KYO_COL_NAME[2][79] = "col_81";
$D_KYO_COL_NAME[2][80] = "col_82";
$D_KYO_COL_NAME[2][81] = "col_83";
$D_KYO_COL_NAME[2][82] = "col_84";
$D_KYO_COL_NAME[2][83] = "col_85";
$D_KYO_COL_NAME[2][84] = "col_86";
$D_KYO_COL_NAME[2][85] = "col_87";
$D_KYO_COL_NAME[2][86] = "col_88";
$D_KYO_COL_NAME[2][87] = "col_89";
$D_KYO_COL_NAME[2][88] = "col_90";
$D_KYO_COL_NAME[2][89] = "col_91";
$D_KYO_COL_NAME[2][90] = "col_92";
$D_KYO_COL_NAME[2][91] = "col_93";
$D_KYO_COL_NAME[2][92] = "col_94";
$D_KYO_COL_NAME[2][93] = "col_95";
$D_KYO_COL_NAME[2][94] = "col_96";
$D_KYO_COL_NAME[2][95] = "col_97";
$D_KYO_COL_NAME[2][96] = "col_98";
$D_KYO_COL_NAME[2][97] = "col_99";
$D_KYO_COL_NAME[2][98] = "col_100";
$D_KYO_COL_NAME[2][99] = "col_101";
$D_KYO_COL_NAME[2][100] = "col_102";
$D_KYO_COL_NAME[2][101] = "col_103";
$D_KYO_COL_NAME[2][102] = "col_104";
$D_KYO_COL_NAME[2][103] = "col_105";
$D_KYO_COL_NAME[2][104] = "col_106";
$D_KYO_COL_NAME[2][105] = "col_107";
$D_KYO_COL_NAME[2][106] = "col_108";
$D_KYO_COL_NAME[2][107] = "col_109";
$D_KYO_COL_NAME[2][108] = "col_110";
$D_KYO_COL_NAME[2][109] = "col_111";
$D_KYO_COL_NAME[2][110] = "col_112";
$D_KYO_COL_NAME[2][111] = "col_113";
$D_KYO_COL_NAME[2][112] = "col_114";
$D_KYO_COL_NAME[2][113] = "col_115";
$D_KYO_COL_NAME[2][114] = "col_116";
$D_KYO_COL_NAME[2][115] = "col_117";
$D_KYO_COL_NAME[2][116] = "col_118";
$D_KYO_COL_NAME[2][117] = "col_119";
$D_KYO_COL_NAME[2][118] = "col_120";
$D_KYO_COL_NAME[2][119] = "col_121";
$D_KYO_COL_NAME[2][120] = "col_122";
$D_KYO_COL_NAME[2][121] = "col_123";
$D_KYO_COL_NAME[2][122] = "col_124";
$D_KYO_COL_NAME[2][123] = "col_125";
$D_KYO_COL_NAME[2][124] = "col_126";
$D_KYO_COL_NAME[2][125] = "col_127";
$D_KYO_COL_NAME[2][126] = "col_128";
$D_KYO_COL_NAME[2][127] = "col_129";
$D_KYO_COL_NAME[2][128] = "col_130";
$D_KYO_COL_NAME[2][129] = "col_131";
$D_KYO_COL_NAME[2][130] = "col_132";
$D_KYO_COL_NAME[2][131] = "col_133";
$D_KYO_COL_NAME[2][132] = "col_134";
$D_KYO_COL_NAME[2][133] = "col_135";
$D_KYO_COL_NAME[2][134] = "col_136";
$D_KYO_COL_NAME[2][135] = "col_137";
$D_KYO_COL_NAME[2][136] = "col_138";
$D_KYO_COL_NAME[2][137] = "col_139";
$D_KYO_COL_NAME[2][138] = "col_140";
$D_KYO_COL_NAME[2][139] = "col_141";
$D_KYO_COL_NAME[2][140] = "col_142";
$D_KYO_COL_NAME[2][141] = "col_143";
$D_KYO_COL_NAME[2][142] = "col_144";
$D_KYO_COL_NAME[2][143] = "col_145";
$D_KYO_COL_NAME[2][144] = "col_146";
$D_KYO_COL_NAME[2][145] = "col_147";
$D_KYO_COL_NAME[2][146] = "col_148";
$D_KYO_COL_NAME[2][147] = "col_149";
$D_KYO_COL_NAME[2][148] = "col_150";
$D_KYO_COL_NAME[2][149] = "col_151";
$D_KYO_COL_NAME[2][150] = "col_152";
$D_KYO_COL_NAME[2][151] = "col_153";
$D_KYO_COL_NAME[2][152] = "col_154";
$D_KYO_COL_NAME[2][153] = "col_155";
$D_KYO_COL_NAME[2][154] = "col_156";
$D_KYO_COL_NAME[2][155] = "col_157";
$D_KYO_COL_NAME[2][156] = "col_158";
//拠点詳細(携帯用）
$D_KYO_COL_NAME[4][0] = "col_01";
$D_KYO_COL_NAME[4][1] = "col_02";
$D_KYO_COL_NAME[4][2] = "col_03";
$D_KYO_COL_NAME[4][3] = "col_04";
$D_KYO_COL_NAME[4][4] = "name";
$D_KYO_COL_NAME[4][5] = "col_07";
$D_KYO_COL_NAME[4][6] = "addr";
$D_KYO_COL_NAME[4][7] = "col_08";
$D_KYO_COL_NAME[4][8] = "col_09";
$D_KYO_COL_NAME[4][9] = "col_10";
$D_KYO_COL_NAME[4][10] = "col_12";
$D_KYO_COL_NAME[4][11] = "col_13";
$D_KYO_COL_NAME[4][12] = "col_14";
$D_KYO_COL_NAME[4][13] = "col_15";
$D_KYO_COL_NAME[4][14] = "col_16";
$D_KYO_COL_NAME[4][15] = "col_17";
$D_KYO_COL_NAME[4][16] = "col_18";
$D_KYO_COL_NAME[4][17] = "col_19";
$D_KYO_COL_NAME[4][18] = "col_20";
$D_KYO_COL_NAME[4][19] = "col_21";
$D_KYO_COL_NAME[4][20] = "col_22";
$D_KYO_COL_NAME[4][21] = "col_23";
$D_KYO_COL_NAME[4][22] = "col_24";
$D_KYO_COL_NAME[4][23] = "col_25";
$D_KYO_COL_NAME[4][24] = "col_26";
$D_KYO_COL_NAME[4][25] = "col_27";
$D_KYO_COL_NAME[4][26] = "col_28";
$D_KYO_COL_NAME[4][27] = "col_29";
$D_KYO_COL_NAME[4][28] = "col_30";
$D_KYO_COL_NAME[4][29] = "col_31";
$D_KYO_COL_NAME[4][30] = "col_32";
$D_KYO_COL_NAME[4][31] = "col_33";
$D_KYO_COL_NAME[4][32] = "col_34";
$D_KYO_COL_NAME[4][33] = "col_35";
$D_KYO_COL_NAME[4][34] = "col_36";
$D_KYO_COL_NAME[4][35] = "col_37";
$D_KYO_COL_NAME[4][36] = "col_38";
$D_KYO_COL_NAME[4][37] = "col_39";
$D_KYO_COL_NAME[4][38] = "col_40";
$D_KYO_COL_NAME[4][39] = "col_41";
$D_KYO_COL_NAME[4][40] = "col_42";
$D_KYO_COL_NAME[4][41] = "col_43";
$D_KYO_COL_NAME[4][42] = "col_44";
$D_KYO_COL_NAME[4][43] = "col_45";
$D_KYO_COL_NAME[4][44] = "col_46";
$D_KYO_COL_NAME[4][45] = "col_47";
$D_KYO_COL_NAME[4][46] = "col_48";
$D_KYO_COL_NAME[4][47] = "col_49";
$D_KYO_COL_NAME[4][48] = "col_50";
$D_KYO_COL_NAME[4][49] = "col_51";
$D_KYO_COL_NAME[4][50] = "col_52";
$D_KYO_COL_NAME[4][51] = "col_53";
$D_KYO_COL_NAME[4][52] = "col_54";
$D_KYO_COL_NAME[4][53] = "col_55";
$D_KYO_COL_NAME[4][54] = "col_56";
$D_KYO_COL_NAME[4][55] = "col_57";
$D_KYO_COL_NAME[4][56] = "col_58";
$D_KYO_COL_NAME[4][57] = "col_59";
$D_KYO_COL_NAME[4][58] = "col_60";
$D_KYO_COL_NAME[4][59] = "col_61";
$D_KYO_COL_NAME[4][60] = "col_62";
$D_KYO_COL_NAME[4][61] = "col_63";
$D_KYO_COL_NAME[4][62] = "col_64";
$D_KYO_COL_NAME[4][63] = "col_65";
$D_KYO_COL_NAME[4][64] = "col_66";
$D_KYO_COL_NAME[4][65] = "col_67";
$D_KYO_COL_NAME[4][66] = "col_68";
$D_KYO_COL_NAME[4][67] = "col_69";
$D_KYO_COL_NAME[4][68] = "col_70";
$D_KYO_COL_NAME[4][69] = "col_71";
$D_KYO_COL_NAME[4][70] = "col_72";
$D_KYO_COL_NAME[4][71] = "col_73";
$D_KYO_COL_NAME[4][72] = "col_74";
$D_KYO_COL_NAME[4][73] = "col_75";
$D_KYO_COL_NAME[4][74] = "col_76";
$D_KYO_COL_NAME[4][75] = "col_77";
$D_KYO_COL_NAME[4][76] = "col_78";
$D_KYO_COL_NAME[4][77] = "col_79";
$D_KYO_COL_NAME[4][78] = "col_80";
$D_KYO_COL_NAME[4][79] = "col_81";
$D_KYO_COL_NAME[4][80] = "col_82";
$D_KYO_COL_NAME[4][81] = "col_83";
$D_KYO_COL_NAME[4][82] = "col_84";
$D_KYO_COL_NAME[4][83] = "col_85";
$D_KYO_COL_NAME[4][84] = "col_86";
$D_KYO_COL_NAME[4][85] = "col_87";
$D_KYO_COL_NAME[4][86] = "col_88";
$D_KYO_COL_NAME[4][87] = "col_89";
$D_KYO_COL_NAME[4][88] = "col_90";
$D_KYO_COL_NAME[4][89] = "col_91";
$D_KYO_COL_NAME[4][90] = "col_92";
$D_KYO_COL_NAME[4][91] = "col_93";
$D_KYO_COL_NAME[4][92] = "col_94";
$D_KYO_COL_NAME[4][93] = "col_95";
$D_KYO_COL_NAME[4][94] = "col_96";
$D_KYO_COL_NAME[4][95] = "col_97";
$D_KYO_COL_NAME[4][96] = "col_98";
$D_KYO_COL_NAME[4][97] = "col_99";
$D_KYO_COL_NAME[4][98] = "col_100";
$D_KYO_COL_NAME[4][99] = "col_101";
$D_KYO_COL_NAME[4][100] = "col_102";
$D_KYO_COL_NAME[4][101] = "col_103";
$D_KYO_COL_NAME[4][102] = "col_104";
$D_KYO_COL_NAME[4][103] = "col_105";
$D_KYO_COL_NAME[4][104] = "col_106";
$D_KYO_COL_NAME[4][105] = "col_107";
$D_KYO_COL_NAME[4][106] = "col_108";
$D_KYO_COL_NAME[4][107] = "col_109";
$D_KYO_COL_NAME[4][108] = "col_110";
$D_KYO_COL_NAME[4][109] = "col_111";
$D_KYO_COL_NAME[4][110] = "col_112";
$D_KYO_COL_NAME[4][111] = "col_113";
$D_KYO_COL_NAME[4][112] = "col_114";
$D_KYO_COL_NAME[4][113] = "col_115";
$D_KYO_COL_NAME[4][114] = "col_116";
$D_KYO_COL_NAME[4][115] = "col_117";
$D_KYO_COL_NAME[4][116] = "col_118";
$D_KYO_COL_NAME[4][117] = "col_119";
$D_KYO_COL_NAME[4][118] = "col_120";
$D_KYO_COL_NAME[4][119] = "col_121";
$D_KYO_COL_NAME[4][120] = "col_122";
$D_KYO_COL_NAME[4][121] = "col_123";
$D_KYO_COL_NAME[4][122] = "col_124";
$D_KYO_COL_NAME[4][123] = "col_125";
$D_KYO_COL_NAME[4][124] = "col_126";
$D_KYO_COL_NAME[4][125] = "col_127";
$D_KYO_COL_NAME[4][126] = "col_128";
$D_KYO_COL_NAME[4][127] = "col_129";
$D_KYO_COL_NAME[4][128] = "col_130";
$D_KYO_COL_NAME[4][129] = "col_131";
$D_KYO_COL_NAME[4][130] = "col_132";
$D_KYO_COL_NAME[4][131] = "col_133";
$D_KYO_COL_NAME[4][132] = "col_134";
$D_KYO_COL_NAME[4][133] = "col_135";
$D_KYO_COL_NAME[4][134] = "col_136";
$D_KYO_COL_NAME[4][135] = "col_137";
$D_KYO_COL_NAME[4][136] = "col_138";
$D_KYO_COL_NAME[4][137] = "col_139";
$D_KYO_COL_NAME[4][138] = "col_140";
$D_KYO_COL_NAME[4][139] = "col_141";
$D_KYO_COL_NAME[4][140] = "col_142";
$D_KYO_COL_NAME[4][141] = "col_143";
$D_KYO_COL_NAME[4][142] = "col_144";
$D_KYO_COL_NAME[4][143] = "col_145";
$D_KYO_COL_NAME[4][144] = "col_146";
$D_KYO_COL_NAME[4][145] = "col_147";
$D_KYO_COL_NAME[4][146] = "col_148";
$D_KYO_COL_NAME[4][147] = "col_149";
$D_KYO_COL_NAME[4][148] = "col_150";
$D_KYO_COL_NAME[4][149] = "col_151";
$D_KYO_COL_NAME[4][150] = "col_152";
$D_KYO_COL_NAME[4][151] = "col_153";
$D_KYO_COL_NAME[4][152] = "col_154";
$D_KYO_COL_NAME[4][153] = "col_155";
$D_KYO_COL_NAME[4][154] = "col_156";
$D_KYO_COL_NAME[4][155] = "col_157";
$D_KYO_COL_NAME[4][156] = "col_158";
//拠点詳細(スマートフォン用）
$D_KYO_COL_NAME[5][0] = "col_01";
$D_KYO_COL_NAME[5][1] = "col_02";
$D_KYO_COL_NAME[5][2] = "col_03";
$D_KYO_COL_NAME[5][3] = "col_04";
$D_KYO_COL_NAME[5][4] = "name";
$D_KYO_COL_NAME[5][5] = "col_07";
$D_KYO_COL_NAME[5][6] = "addr";
$D_KYO_COL_NAME[5][7] = "col_08";
$D_KYO_COL_NAME[5][8] = "col_09";
$D_KYO_COL_NAME[5][9] = "col_10";
$D_KYO_COL_NAME[5][10] = "col_12";
$D_KYO_COL_NAME[5][11] = "col_13";
$D_KYO_COL_NAME[5][12] = "col_14";
$D_KYO_COL_NAME[5][13] = "col_15";
$D_KYO_COL_NAME[5][14] = "col_16";
$D_KYO_COL_NAME[5][15] = "col_17";
$D_KYO_COL_NAME[5][16] = "col_18";
$D_KYO_COL_NAME[5][17] = "col_19";
$D_KYO_COL_NAME[5][18] = "col_20";
$D_KYO_COL_NAME[5][19] = "col_21";
$D_KYO_COL_NAME[5][20] = "col_22";
$D_KYO_COL_NAME[5][21] = "col_23";
$D_KYO_COL_NAME[5][22] = "col_24";
$D_KYO_COL_NAME[5][23] = "col_25";
$D_KYO_COL_NAME[5][24] = "col_26";
$D_KYO_COL_NAME[5][25] = "col_27";
$D_KYO_COL_NAME[5][26] = "col_28";
$D_KYO_COL_NAME[5][27] = "col_29";
$D_KYO_COL_NAME[5][28] = "col_30";
$D_KYO_COL_NAME[5][29] = "col_31";
$D_KYO_COL_NAME[5][30] = "col_32";
$D_KYO_COL_NAME[5][31] = "col_33";
$D_KYO_COL_NAME[5][32] = "col_34";
$D_KYO_COL_NAME[5][33] = "col_35";
$D_KYO_COL_NAME[5][34] = "col_36";
$D_KYO_COL_NAME[5][35] = "col_37";
$D_KYO_COL_NAME[5][36] = "col_38";
$D_KYO_COL_NAME[5][37] = "col_39";
$D_KYO_COL_NAME[5][38] = "col_40";
$D_KYO_COL_NAME[5][39] = "col_41";
$D_KYO_COL_NAME[5][40] = "col_42";
$D_KYO_COL_NAME[5][41] = "col_43";
$D_KYO_COL_NAME[5][42] = "col_44";
$D_KYO_COL_NAME[5][43] = "col_45";
$D_KYO_COL_NAME[5][44] = "col_46";
$D_KYO_COL_NAME[5][45] = "col_47";
$D_KYO_COL_NAME[5][46] = "col_48";
$D_KYO_COL_NAME[5][47] = "col_49";
$D_KYO_COL_NAME[5][48] = "col_50";
$D_KYO_COL_NAME[5][49] = "col_51";
$D_KYO_COL_NAME[5][50] = "col_52";
$D_KYO_COL_NAME[5][51] = "col_53";
$D_KYO_COL_NAME[5][52] = "col_54";
$D_KYO_COL_NAME[5][53] = "col_55";
$D_KYO_COL_NAME[5][54] = "col_56";
$D_KYO_COL_NAME[5][55] = "col_57";
$D_KYO_COL_NAME[5][56] = "col_58";
$D_KYO_COL_NAME[5][57] = "col_59";
$D_KYO_COL_NAME[5][58] = "col_60";
$D_KYO_COL_NAME[5][59] = "col_61";
$D_KYO_COL_NAME[5][60] = "col_62";
$D_KYO_COL_NAME[5][61] = "col_63";
$D_KYO_COL_NAME[5][62] = "col_64";
$D_KYO_COL_NAME[5][63] = "col_65";
$D_KYO_COL_NAME[5][64] = "col_66";
$D_KYO_COL_NAME[5][65] = "col_67";
$D_KYO_COL_NAME[5][66] = "col_68";
$D_KYO_COL_NAME[5][67] = "col_69";
$D_KYO_COL_NAME[5][68] = "col_70";
$D_KYO_COL_NAME[5][69] = "col_71";
$D_KYO_COL_NAME[5][70] = "col_72";
$D_KYO_COL_NAME[5][71] = "col_73";
$D_KYO_COL_NAME[5][72] = "col_74";
$D_KYO_COL_NAME[5][73] = "col_75";
$D_KYO_COL_NAME[5][74] = "col_76";
$D_KYO_COL_NAME[5][75] = "col_77";
$D_KYO_COL_NAME[5][76] = "col_78";
$D_KYO_COL_NAME[5][77] = "col_79";
$D_KYO_COL_NAME[5][78] = "col_80";
$D_KYO_COL_NAME[5][79] = "col_81";
$D_KYO_COL_NAME[5][80] = "col_82";
$D_KYO_COL_NAME[5][81] = "col_83";
$D_KYO_COL_NAME[5][82] = "col_84";
$D_KYO_COL_NAME[5][83] = "col_85";
$D_KYO_COL_NAME[5][84] = "col_86";
$D_KYO_COL_NAME[5][85] = "col_87";
$D_KYO_COL_NAME[5][86] = "col_88";
$D_KYO_COL_NAME[5][87] = "col_89";
$D_KYO_COL_NAME[5][88] = "col_90";
$D_KYO_COL_NAME[5][89] = "col_91";
$D_KYO_COL_NAME[5][90] = "col_92";
$D_KYO_COL_NAME[5][91] = "col_93";
$D_KYO_COL_NAME[5][92] = "col_94";
$D_KYO_COL_NAME[5][93] = "col_95";
$D_KYO_COL_NAME[5][94] = "col_96";
$D_KYO_COL_NAME[5][95] = "col_97";
$D_KYO_COL_NAME[5][96] = "col_98";
$D_KYO_COL_NAME[5][97] = "col_99";
$D_KYO_COL_NAME[5][98] = "col_100";
$D_KYO_COL_NAME[5][99] = "col_101";
$D_KYO_COL_NAME[5][100] = "col_102";
$D_KYO_COL_NAME[5][101] = "col_103";
$D_KYO_COL_NAME[5][102] = "col_104";
$D_KYO_COL_NAME[5][103] = "col_105";
$D_KYO_COL_NAME[5][104] = "col_106";
$D_KYO_COL_NAME[5][105] = "col_107";
$D_KYO_COL_NAME[5][106] = "col_108";
$D_KYO_COL_NAME[5][107] = "col_109";
$D_KYO_COL_NAME[5][108] = "col_110";
$D_KYO_COL_NAME[5][109] = "col_111";
$D_KYO_COL_NAME[5][110] = "col_112";
$D_KYO_COL_NAME[5][111] = "col_113";
$D_KYO_COL_NAME[5][112] = "col_114";
$D_KYO_COL_NAME[5][113] = "col_115";
$D_KYO_COL_NAME[5][114] = "col_116";
$D_KYO_COL_NAME[5][115] = "col_117";
$D_KYO_COL_NAME[5][116] = "col_118";
$D_KYO_COL_NAME[5][117] = "col_119";
$D_KYO_COL_NAME[5][118] = "col_120";
$D_KYO_COL_NAME[5][119] = "col_121";
$D_KYO_COL_NAME[5][120] = "col_122";
$D_KYO_COL_NAME[5][121] = "col_123";
$D_KYO_COL_NAME[5][122] = "col_124";
$D_KYO_COL_NAME[5][123] = "col_125";
$D_KYO_COL_NAME[5][124] = "col_126";
$D_KYO_COL_NAME[5][125] = "col_127";
$D_KYO_COL_NAME[5][126] = "col_128";
$D_KYO_COL_NAME[5][127] = "col_129";
$D_KYO_COL_NAME[5][128] = "col_130";
$D_KYO_COL_NAME[5][129] = "col_131";
$D_KYO_COL_NAME[5][130] = "col_132";
$D_KYO_COL_NAME[5][131] = "col_133";
$D_KYO_COL_NAME[5][132] = "col_134";
$D_KYO_COL_NAME[5][133] = "col_135";
$D_KYO_COL_NAME[5][134] = "col_136";
$D_KYO_COL_NAME[5][135] = "col_137";
$D_KYO_COL_NAME[5][136] = "col_138";
$D_KYO_COL_NAME[5][137] = "col_139";
$D_KYO_COL_NAME[5][138] = "col_140";
$D_KYO_COL_NAME[5][139] = "col_141";
$D_KYO_COL_NAME[5][140] = "col_142";
$D_KYO_COL_NAME[5][141] = "col_143";
$D_KYO_COL_NAME[5][142] = "col_144";
$D_KYO_COL_NAME[5][143] = "col_145";
$D_KYO_COL_NAME[5][144] = "col_146";
$D_KYO_COL_NAME[5][145] = "col_147";
$D_KYO_COL_NAME[5][146] = "col_148";
$D_KYO_COL_NAME[5][147] = "col_149";
$D_KYO_COL_NAME[5][148] = "col_150";
$D_KYO_COL_NAME[5][149] = "col_151";
$D_KYO_COL_NAME[5][150] = "col_152";
$D_KYO_COL_NAME[5][151] = "col_153";
$D_KYO_COL_NAME[5][152] = "col_154";
$D_KYO_COL_NAME[5][153] = "col_155";
$D_KYO_COL_NAME[5][154] = "col_156";
$D_KYO_COL_NAME[5][155] = "col_157";
$D_KYO_COL_NAME[5][156] = "col_158";
$D_KYOTENLVL_COL_P = "col_11";

//--------------------------------------------
//区分項目名称
//--------------------------------------------
//区分項目名称リスト
$D_KBN_ITEM_NAME["COL_03"]["1"] = "すき家";
$D_KBN_ITEM_NAME["COL_03"]["10"] = "エルトリート";
$D_KBN_ITEM_NAME["COL_03"]["11"] = "伝丸";
$D_KBN_ITEM_NAME["COL_03"]["12"] = "壱鵠堂";
$D_KBN_ITEM_NAME["COL_03"]["13"] = "その他ラーメン";
$D_KBN_ITEM_NAME["COL_03"]["14"] = "伝蔵";
$D_KBN_ITEM_NAME["COL_03"]["15"] = "名称未定（ラーメン）";
$D_KBN_ITEM_NAME["COL_03"]["16"] = "はま寿司";
$D_KBN_ITEM_NAME["COL_03"]["17"] = "牛庵";
$D_KBN_ITEM_NAME["COL_03"]["18"] = "いちばん";
$D_KBN_ITEM_NAME["COL_03"]["19"] = "モリバコーヒー";
$D_KBN_ITEM_NAME["COL_03"]["2"] = "ココス";
$D_KBN_ITEM_NAME["COL_03"]["20"] = "カフェミラノ";
$D_KBN_ITEM_NAME["COL_03"]["21"] = "久兵衛屋";
$D_KBN_ITEM_NAME["COL_03"]["22"] = "瀬戸うどん";
$D_KBN_ITEM_NAME["COL_03"]["23"] = "たもん庵　＋　讃岐美人";
$D_KBN_ITEM_NAME["COL_03"]["24"] = "オリーブの丘";
$D_KBN_ITEM_NAME["COL_03"]["25"] = "天下一";
$D_KBN_ITEM_NAME["COL_03"]["26"] = "マルヤ";
$D_KBN_ITEM_NAME["COL_03"]["27"] = "ヤマグチ";
$D_KBN_ITEM_NAME["COL_03"]["28"] = "ジョイフーズ";
$D_KBN_ITEM_NAME["COL_03"]["29"] = "マルエイ";
$D_KBN_ITEM_NAME["COL_03"]["3"] = "宝島";
$D_KBN_ITEM_NAME["COL_03"]["30"] = "尾張屋";
$D_KBN_ITEM_NAME["COL_03"]["31"] = "ユナイテッドベジーズ";
$D_KBN_ITEM_NAME["COL_03"]["32"] = "ダウンタウン";
$D_KBN_ITEM_NAME["COL_03"]["33"] = "輝";
$D_KBN_ITEM_NAME["COL_03"]["4"] = "ジョリーパスタ　＋　ジョリーオックス";
$D_KBN_ITEM_NAME["COL_03"]["5"] = "なか卯";
$D_KBN_ITEM_NAME["COL_03"]["6"] = "BigBoy";
$D_KBN_ITEM_NAME["COL_03"]["7"] = "ヴィクトリアステーション";
$D_KBN_ITEM_NAME["COL_03"]["8"] = "華屋与兵衛";
$D_KBN_ITEM_NAME["COL_03"]["9"] = "和食よへい";
$D_KBN_ITEM_NAME["COL_04"]["1"] = "ゼンショーグループ全体";
$D_KBN_ITEM_NAME["COL_04"]["10"] = "ＧＭ事業部";
$D_KBN_ITEM_NAME["COL_04"]["11"] = "はま寿司";
$D_KBN_ITEM_NAME["COL_04"]["12"] = "牛庵　＋　いちばん";
$D_KBN_ITEM_NAME["COL_04"]["13"] = "モリバコーヒー";
$D_KBN_ITEM_NAME["COL_04"]["14"] = "久兵衛屋　＋　瀬戸うどん　＋　たもん庵";
$D_KBN_ITEM_NAME["COL_04"]["15"] = "マルヤ";
$D_KBN_ITEM_NAME["COL_04"]["16"] = "ヤマグチ";
$D_KBN_ITEM_NAME["COL_04"]["17"] = "ジョイフーズ";
$D_KBN_ITEM_NAME["COL_04"]["18"] = "マルエイ";
$D_KBN_ITEM_NAME["COL_04"]["19"] = "尾張屋";
$D_KBN_ITEM_NAME["COL_04"]["2"] = "すき家";
$D_KBN_ITEM_NAME["COL_04"]["20"] = "ユナイテッドベジーズ";
$D_KBN_ITEM_NAME["COL_04"]["21"] = "輝";
$D_KBN_ITEM_NAME["COL_04"]["22"] = "トレーニング会社";
$D_KBN_ITEM_NAME["COL_04"]["23"] = "地域会社・事務所";
$D_KBN_ITEM_NAME["COL_04"]["3"] = "ココス";
$D_KBN_ITEM_NAME["COL_04"]["4"] = "宝島";
$D_KBN_ITEM_NAME["COL_04"]["5"] = "ジョリーパスタ　＋　ジョリーオックス";
$D_KBN_ITEM_NAME["COL_04"]["6"] = "なか卯";
$D_KBN_ITEM_NAME["COL_04"]["7"] = "BigBoy　＋　ヴィクトリアステーション";
$D_KBN_ITEM_NAME["COL_04"]["8"] = "華屋与兵衛　＋　和食よへい";
$D_KBN_ITEM_NAME["COL_04"]["9"] = "エルトリート";
$D_KBN_ITEM_NAME["COL_05"]["1"] = "北海道";
$D_KBN_ITEM_NAME["COL_05"]["10"] = "群馬県";
$D_KBN_ITEM_NAME["COL_05"]["11"] = "埼玉県";
$D_KBN_ITEM_NAME["COL_05"]["12"] = "千葉県";
$D_KBN_ITEM_NAME["COL_05"]["13"] = "東京都";
$D_KBN_ITEM_NAME["COL_05"]["14"] = "神奈川県";
$D_KBN_ITEM_NAME["COL_05"]["15"] = "新潟県";
$D_KBN_ITEM_NAME["COL_05"]["16"] = "富山県";
$D_KBN_ITEM_NAME["COL_05"]["17"] = "石川県";
$D_KBN_ITEM_NAME["COL_05"]["18"] = "福井県";
$D_KBN_ITEM_NAME["COL_05"]["19"] = "山梨県";
$D_KBN_ITEM_NAME["COL_05"]["2"] = "青森県";
$D_KBN_ITEM_NAME["COL_05"]["20"] = "長野県";
$D_KBN_ITEM_NAME["COL_05"]["21"] = "岐阜県";
$D_KBN_ITEM_NAME["COL_05"]["22"] = "静岡県";
$D_KBN_ITEM_NAME["COL_05"]["23"] = "愛知県";
$D_KBN_ITEM_NAME["COL_05"]["24"] = "三重県";
$D_KBN_ITEM_NAME["COL_05"]["25"] = "滋賀県";
$D_KBN_ITEM_NAME["COL_05"]["26"] = "京都府";
$D_KBN_ITEM_NAME["COL_05"]["27"] = "大阪府";
$D_KBN_ITEM_NAME["COL_05"]["28"] = "兵庫県";
$D_KBN_ITEM_NAME["COL_05"]["29"] = "奈良県";
$D_KBN_ITEM_NAME["COL_05"]["3"] = "岩手県";
$D_KBN_ITEM_NAME["COL_05"]["30"] = "和歌山県";
$D_KBN_ITEM_NAME["COL_05"]["31"] = "鳥取県";
$D_KBN_ITEM_NAME["COL_05"]["32"] = "島根県";
$D_KBN_ITEM_NAME["COL_05"]["33"] = "岡山県";
$D_KBN_ITEM_NAME["COL_05"]["34"] = "広島県";
$D_KBN_ITEM_NAME["COL_05"]["35"] = "山口県";
$D_KBN_ITEM_NAME["COL_05"]["36"] = "徳島県";
$D_KBN_ITEM_NAME["COL_05"]["37"] = "香川県";
$D_KBN_ITEM_NAME["COL_05"]["38"] = "愛媛県";
$D_KBN_ITEM_NAME["COL_05"]["39"] = "高知県";
$D_KBN_ITEM_NAME["COL_05"]["4"] = "宮城県";
$D_KBN_ITEM_NAME["COL_05"]["40"] = "福岡県";
$D_KBN_ITEM_NAME["COL_05"]["41"] = "佐賀県";
$D_KBN_ITEM_NAME["COL_05"]["42"] = "長崎県";
$D_KBN_ITEM_NAME["COL_05"]["43"] = "熊本県";
$D_KBN_ITEM_NAME["COL_05"]["44"] = "大分県";
$D_KBN_ITEM_NAME["COL_05"]["45"] = "宮崎県";
$D_KBN_ITEM_NAME["COL_05"]["46"] = "鹿児島県";
$D_KBN_ITEM_NAME["COL_05"]["47"] = "沖縄県";
$D_KBN_ITEM_NAME["COL_05"]["5"] = "秋田県";
$D_KBN_ITEM_NAME["COL_05"]["6"] = "山形県";
$D_KBN_ITEM_NAME["COL_05"]["7"] = "福島県";
$D_KBN_ITEM_NAME["COL_05"]["8"] = "茨城県";
$D_KBN_ITEM_NAME["COL_05"]["9"] = "栃木県";
$D_KBN_ITEM_NAME["COL_20"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_20"]["1"] = "ラーメンあり";
$D_KBN_ITEM_NAME["COL_20"]["2"] = "中華あり";
$D_KBN_ITEM_NAME["COL_30"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_30"]["1"] = "毎日";
$D_KBN_ITEM_NAME["COL_30"]["2"] = "土日祝";
$D_KBN_ITEM_NAME["COL_32"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_32"]["1"] = "朝食バイキング（毎日）";
$D_KBN_ITEM_NAME["COL_32"]["2"] = "食べ放題";
$D_KBN_ITEM_NAME["COL_32"]["3"] = "朝食バイキング（土日祝）";
$D_KBN_ITEM_NAME["COL_34"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_34"]["1"] = "サラダバー";
$D_KBN_ITEM_NAME["COL_34"]["2"] = "カツカレー";
$D_KBN_ITEM_NAME["COL_34"]["3"] = "じゃがスティック";
$D_KBN_ITEM_NAME["COL_37"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_37"]["1"] = "とんこつスープ";
$D_KBN_ITEM_NAME["COL_37"]["2"] = "しゃぶしゃぶ";
$D_KBN_ITEM_NAME["COL_38"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_38"]["1"] = "鶏がらスープ";
$D_KBN_ITEM_NAME["COL_38"]["2"] = "焼肉";
$D_KBN_ITEM_NAME["COL_41"]["0"] = "喫煙可";
$D_KBN_ITEM_NAME["COL_41"]["1"] = "分煙";
$D_KBN_ITEM_NAME["COL_41"]["2"] = "禁煙";
$D_KBN_ITEM_NAME["COL_41"]["3"] = "完全分煙";
$D_KBN_ITEM_NAME["COL_42"]["0"] = "通常";
$D_KBN_ITEM_NAME["COL_42"]["1"] = "テーブル席あり";
$D_KBN_ITEM_NAME["COL_42"]["2"] = "座敷あり";
$D_KBN_ITEM_NAME["COL_42"]["3"] = "パーティールームあり";
$D_KBN_ITEM_NAME["COL_42"]["4"] = "宴会受付可";
$D_KBN_ITEM_NAME["COL_42"]["5"] = "団体様受付可";
$D_KBN_ITEM_NAME["COL_46"]["0"] = "−";
$D_KBN_ITEM_NAME["COL_46"]["1"] = "1F";
$D_KBN_ITEM_NAME["COL_46"]["2"] = "2F";
$D_KBN_ITEM_NAME["COL_47"]["0"] = "なし(受付不可)";
$D_KBN_ITEM_NAME["COL_47"]["1"] = "テーブル席あり";
$D_KBN_ITEM_NAME["COL_47"]["2"] = "座敷あり";
$D_KBN_ITEM_NAME["COL_47"]["3"] = "パーティールームあり";
$D_KBN_ITEM_NAME["COL_47"]["4"] = "宴会受付可";
$D_KBN_ITEM_NAME["COL_47"]["5"] = "受付可";
$D_KBN_ITEM_NAME["COL_97"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_97"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_97"]["2"] = "営業時間中ご提供";
$D_KBN_ITEM_NAME["COL_97"]["3"] = "14：00〜翌5：00の営業時間中ご提供";
$D_KBN_ITEM_NAME["COL_98"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_98"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_99"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_99"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_100"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_100"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_101"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_101"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_102"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_102"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_103"]["0"] = "なし";
$D_KBN_ITEM_NAME["COL_103"]["1"] = "あり";
$D_KBN_ITEM_NAME["COL_108"]["0"] = "(なし)";
$D_KBN_ITEM_NAME["COL_108"]["1"] = "通常どおり営業中";
$D_KBN_ITEM_NAME["COL_108"]["2"] = "メニューや営業時間を限定して営業中";
$D_KBN_ITEM_NAME["COL_108"]["3"] = "一時営業停止しています。復旧次第お知らせします。";
$D_KBN_ITEM_NAME["COL_108"]["4"] = "お問い合わせください。";
$D_KBN_ITEM_NAME["COL_111"]["0"] = "ダミー";
$D_KBN_ITEM_NAME["COL_112"]["0"] = "ダミー";

//--------------------------------------------
// 絞り込み条件（チェックボックス、リストボックス）
//--------------------------------------------
$D_COND_GRP_ANDOR = 'AND';
$cond_g_cnt = -1;
$cond_g_cnt++;
$D_COND_ANDOR[$cond_g_cnt] = 'AND';
$D_COND[1] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_04:1','ゼンショーグループ全体')
	,'3'=>array('COL_04:10','ＧＭ事業部')
	,'4'=>array('COL_04:11','はま寿司')
	,'5'=>array('COL_04:12','牛庵　＋　いちばん')
	,'6'=>array('COL_04:13','モリバコーヒー')
	,'7'=>array('COL_04:14','久兵衛屋　＋　瀬戸うどん　＋　たもん庵')
	,'8'=>array('COL_04:15','マルヤ')
	,'9'=>array('COL_04:16','ヤマグチ')
	,'10'=>array('COL_04:17','ジョイフーズ')
	,'11'=>array('COL_04:18','マルエイ')
	,'12'=>array('COL_04:19','尾張屋')
	,'13'=>array('COL_04:2','すき家')
	,'14'=>array('COL_04:20','ユナイテッドベジーズ')
	,'15'=>array('COL_04:21','輝')
	,'16'=>array('COL_04:22','トレーニング会社')
	,'17'=>array('COL_04:23','地域会社・事務所')
	,'18'=>array('COL_04:3','ココス')
	,'19'=>array('COL_04:4','宝島')
	,'20'=>array('COL_04:5','ジョリーパスタ　＋　ジョリーオックス')
	,'21'=>array('COL_04:6','なか卯')
	,'22'=>array('COL_04:7','BigBoy　＋　ヴィクトリアステーション')
	,'23'=>array('COL_04:8','華屋与兵衛　＋　和食よへい')
	,'24'=>array('COL_04:9','エルトリート')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '1';
$D_COND[2] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_20:0','なし')
	,'3'=>array('COL_20:1','ラーメンあり')
	,'4'=>array('COL_20:2','中華あり')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '2';
$D_COND[3] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_30:0','なし')
	,'3'=>array('COL_30:1','毎日')
	,'4'=>array('COL_30:2','土日祝')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '3';
$D_COND[4] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_34:0','なし')
	,'3'=>array('COL_34:1','サラダバー')
	,'4'=>array('COL_34:2','カツカレー')
	,'5'=>array('COL_34:3','じゃがスティック')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '4';
$D_COND[5] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_41:0','喫煙可')
	,'3'=>array('COL_41:1','分煙')
	,'4'=>array('COL_41:2','禁煙')
	,'5'=>array('COL_41:3','完全分煙')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '5';
$D_COND[6] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_42:0','通常')
	,'3'=>array('COL_42:1','テーブル席あり')
	,'4'=>array('COL_42:2','座敷あり')
	,'5'=>array('COL_42:3','パーティールームあり')
	,'6'=>array('COL_42:4','宴会受付可')
	,'7'=>array('COL_42:5','団体様受付可')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '6';
$D_COND[7] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_46:0','−')
	,'3'=>array('COL_46:1','1F')
	,'4'=>array('COL_46:2','2F')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '7';
$D_COND[8] = array(
'type'=>'SL'
,'opts'=>array(
	 '1'=>array('', '')
	,'2'=>array('COL_47:0','なし(受付不可)')
	,'3'=>array('COL_47:1','テーブル席あり')
	,'4'=>array('COL_47:2','座敷あり')
	,'5'=>array('COL_47:3','パーティールームあり')
	,'6'=>array('COL_47:4','宴会受付可')
	,'7'=>array('COL_47:5','受付可')
	)
);
$D_COND_GRP[$cond_g_cnt][] = '8';

$cond_g_cnt++;
$D_COND_ANDOR[$cond_g_cnt] = 'AND';
$D_COND[9] = array('type'=>'CB', 'val'=>'COL_02:1');
$D_COND_GRP[$cond_g_cnt][] = '9';
$D_COND[10] = array('type'=>'CB', 'val'=>'COL_12:1');
$D_COND_GRP[$cond_g_cnt][] = '10';
$D_COND[11] = array('type'=>'CB', 'val'=>'COL_13:1');
$D_COND_GRP[$cond_g_cnt][] = '11';
$D_COND[12] = array('type'=>'CB', 'val'=>'COL_15:1');
$D_COND_GRP[$cond_g_cnt][] = '12';
$D_COND[13] = array('type'=>'CB', 'val'=>'COL_16:1');
$D_COND_GRP[$cond_g_cnt][] = '13';
$D_COND[14] = array('type'=>'CB', 'val'=>'COL_17:1');
$D_COND_GRP[$cond_g_cnt][] = '14';
$D_COND[15] = array('type'=>'CB', 'val'=>'COL_18:1');
$D_COND_GRP[$cond_g_cnt][] = '15';
$D_COND[16] = array('type'=>'CB', 'val'=>'COL_19:1');
$D_COND_GRP[$cond_g_cnt][] = '16';
$D_COND[17] = array('type'=>'CB', 'val'=>'COL_21:1');
$D_COND_GRP[$cond_g_cnt][] = '17';
$D_COND[18] = array('type'=>'CB', 'val'=>'COL_22:1');
$D_COND_GRP[$cond_g_cnt][] = '18';
$D_COND[19] = array('type'=>'CB', 'val'=>'COL_27:1');
$D_COND_GRP[$cond_g_cnt][] = '19';
$D_COND[20] = array('type'=>'CB', 'val'=>'COL_28:1');
$D_COND_GRP[$cond_g_cnt][] = '20';
$D_COND[21] = array('type'=>'CB', 'val'=>'COL_29:1');
$D_COND_GRP[$cond_g_cnt][] = '21';
$D_COND[22] = array('type'=>'CB', 'val'=>'COL_31:1');
$D_COND_GRP[$cond_g_cnt][] = '22';
$D_COND[23] = array('type'=>'CB', 'val'=>'COL_33:1');
$D_COND_GRP[$cond_g_cnt][] = '23';
$D_COND[24] = array('type'=>'CB', 'val'=>'COL_39:1');
$D_COND_GRP[$cond_g_cnt][] = '24';
$D_COND[25] = array('type'=>'CB', 'val'=>'COL_43:1');
$D_COND_GRP[$cond_g_cnt][] = '25';
$D_COND[26] = array('type'=>'CB', 'val'=>'COL_44:1');
$D_COND_GRP[$cond_g_cnt][] = '26';
$D_COND[27] = array('type'=>'CB', 'val'=>'COL_45:1');
$D_COND_GRP[$cond_g_cnt][] = '27';
$D_COND[28] = array('type'=>'CB', 'val'=>'COL_48:1');
$D_COND_GRP[$cond_g_cnt][] = '28';
$D_COND[29] = array('type'=>'CB', 'val'=>'COL_49:1');
$D_COND_GRP[$cond_g_cnt][] = '29';
$D_COND[30] = array('type'=>'CB', 'val'=>'COL_50:1');
$D_COND_GRP[$cond_g_cnt][] = '30';
$D_COND[31] = array('type'=>'CB', 'val'=>'COL_57:1');
$D_COND_GRP[$cond_g_cnt][] = '31';
$D_COND[32] = array('type'=>'CB', 'val'=>'COL_58:1');
$D_COND_GRP[$cond_g_cnt][] = '32';
$D_COND[33] = array('type'=>'CB', 'val'=>'COL_59:1');
$D_COND_GRP[$cond_g_cnt][] = '33';
$D_COND[34] = array('type'=>'CB', 'val'=>'COL_72:1');
$D_COND_GRP[$cond_g_cnt][] = '34';
$D_COND[35] = array('type'=>'CB', 'val'=>'COL_74:1');
$D_COND_GRP[$cond_g_cnt][] = '35';
$D_COND[36] = array('type'=>'CB', 'val'=>'COL_77:1');
$D_COND_GRP[$cond_g_cnt][] = '36';
$D_COND[37] = array('type'=>'CB', 'val'=>'COL_78:1');
$D_COND_GRP[$cond_g_cnt][] = '37';
$D_COND[38] = array('type'=>'CB', 'val'=>'COL_80:1');
$D_COND_GRP[$cond_g_cnt][] = '38';
$D_COND[39] = array('type'=>'CB', 'val'=>'COL_81:1');
$D_COND_GRP[$cond_g_cnt][] = '39';
$D_COND[40] = array('type'=>'CB', 'val'=>'COL_82:1');
$D_COND_GRP[$cond_g_cnt][] = '40';
$D_COND[41] = array('type'=>'CB', 'val'=>'COL_83:1');
$D_COND_GRP[$cond_g_cnt][] = '41';
$D_COND[42] = array('type'=>'CB', 'val'=>'COL_84:1');
$D_COND_GRP[$cond_g_cnt][] = '42';
$D_COND[43] = array('type'=>'CB', 'val'=>'COL_85:1');
$D_COND_GRP[$cond_g_cnt][] = '43';
$D_COND[44] = array('type'=>'CB', 'val'=>'COL_86:1');
$D_COND_GRP[$cond_g_cnt][] = '44';
$D_COND[45] = array('type'=>'CB', 'val'=>'COL_87:1');
$D_COND_GRP[$cond_g_cnt][] = '45';
$D_COND[46] = array('type'=>'CB', 'val'=>'COL_88:1');
$D_COND_GRP[$cond_g_cnt][] = '46';
$D_COND[47] = array('type'=>'CB', 'val'=>'COL_89:1');
$D_COND_GRP[$cond_g_cnt][] = '47';
$D_COND[48] = array('type'=>'CB', 'val'=>'COL_90:1');
$D_COND_GRP[$cond_g_cnt][] = '48';
$D_COND[49] = array('type'=>'CB', 'val'=>'COL_91:1');
$D_COND_GRP[$cond_g_cnt][] = '49';
$D_COND[50] = array('type'=>'CB', 'val'=>'COL_92:1');
$D_COND_GRP[$cond_g_cnt][] = '50';
$D_COND[51] = array('type'=>'CB', 'val'=>'COL_93:1');
$D_COND_GRP[$cond_g_cnt][] = '51';
$D_COND[52] = array('type'=>'CB', 'val'=>'COL_94:1');
$D_COND_GRP[$cond_g_cnt][] = '52';
$D_COND[53] = array('type'=>'CB', 'val'=>'COL_95:1');
$D_COND_GRP[$cond_g_cnt][] = '53';
$D_COND[54] = array('type'=>'CB', 'val'=>'COL_96:1');
$D_COND_GRP[$cond_g_cnt][] = '54';

//--------------------------------------------
//拠点（複数）画像定義リスト
//--------------------------------------------

//--------------------------------------------
//店舗閲覧履歴のCookie保存
//--------------------------------------------
$D_COOKIE_SHOPDTL_MAX = 0; //拠点詳細保存件数

?>
