<?PHP
//微調整用
//$D_BASIC_AUTH['test'] = 0;	// debug

if (ereg('test', $cid)) {
	// 検証用
	
	// TサイトTOP
	$D_HP_URL = "http://stg.tsite.jp/";

	// クーポンURL
	$D_FREE_URL[] = 'https://stg.tsite.jp/coupon/index.pl';

	// iPadリダイレクト先URL
	$D_IPAD_REDIRECT = "https://stg.tsite.jp/t-map/index.pl";
} else {
	// 本番用

	// TサイトTOP
	$D_HP_URL = "http://tsite.jp/";

	// クーポンURL
	$D_FREE_URL[] = 'https://tsite.jp/coupon/index.pl';

	// iPadリダイレクト先URL
	$D_IPAD_REDIRECT = "https://tsite.jp/t-map/index.pl";
}

// 最寄り駅リストの検索TOPボタン表示設定
$D_NEKI_SEARCH_TOP_LINK = 1;

// 位置決定後TOPに戻らず一覧表示
$D_DIRECT_SEARCH = 1;

// クーポンアイコン設定情報
$D_TOOLTIP_W = 26;
$D_TOOLTIP_H = 26;
$D_TOOLTIP_OFFSET_X = -8;
$D_TOOLTIP_OFFSET_Y = -35;

// 地図以外表示領域（最寄り店舗地図）
$D_NMAP_ANY_DISP_PX = 65;

// 地図以外表示領域（店舗地図）
$D_MAP_ANY_DISP_PX = 31;

// クーポン有りアイコン
$D_ICON_NEW_IMG = "{$D_DIR_COMPANY}img/A-2a.gif";


//--------------------------------------------
// 絞り込み条件
//--------------------------------------------
$D_FILTER_VAL_LIST[] = '';
$D_FILTER_VAL_LIST[] = 'COL_87=1';  // アイフルホーム add 20160425
$D_FILTER_VAL_LIST[] = 'COL_12=1';  // 藍屋
$D_FILTER_VAL_LIST[] = 'COL_83=1';  // 青森銀行 add 20160318
$D_FILTER_VAL_LIST[] = 'COL_68=1';  // 旭屋書店 add 20151008
$D_FILTER_VAL_LIST[] = 'COL_104=1'; // 足利銀行 add 20161221
$D_FILTER_VAL_LIST[] = 'COL_106=1'; // アシックス add 20170117
$D_FILTER_VAL_LIST[] = 'COL_98=1';  // ALOOK add 20160701
$D_FILTER_VAL_LIST[] = 'COL_22=1';  // アルペン
$D_FILTER_VAL_LIST[] = 'COL_92=1';  // ERAジャパン add 20160526 
$D_FILTER_VAL_LIST[] = 'COL_56=1';  // 伊勢丹 add 20160512
$D_FILTER_VAL_LIST[] = 'COL_118=1';  // ISETAN MiRROR add 20170428
$D_FILTER_VAL_LIST[] = 'COL_58=1';  // 岩田屋 add 20160512
//$D_FILTER_VAL_LIST[] = 'COL_20=1'; del 20150821
//$D_FILTER_VAL_LIST[] = 'COL_58=1'; del 20160425
$D_FILTER_VAL_LIST[] = 'COL_28=1';  // ウエルシア
$D_FILTER_VAL_LIST[] = 'COL_38=1';  // エクセルシオール カフェ
$D_FILTER_VAL_LIST[] = 'COL_19=1';  // エディオン
$D_FILTER_VAL_LIST[] = 'COL_08=1';  // ENEOS
$D_FILTER_VAL_LIST[] = 'COL_72=1';  // 沖縄トヨペット add 20160205
$D_FILTER_VAL_LIST[] = 'COL_14=1';  // オートバックスグループ
$D_FILTER_VAL_LIST[] = 'COL_107=1'; // オニツカタイガー add 20170117
$D_FILTER_VAL_LIST[] = 'COL_75=1';  // 恩納マリンビューパレス add 20160318
$D_FILTER_VAL_LIST[] = 'COL_77=1';  // 鹿児島高牧カントリークラブ add 20160318
$D_FILTER_VAL_LIST[] = 'COL_09=1';  // ガスト/ステーキガスト mod 20150615
$D_FILTER_VAL_LIST[] = 'COL_103=1'; // かつ久 add 20161012
$D_FILTER_VAL_LIST[] = 'COL_59=1';  // 金光薬品
$D_FILTER_VAL_LIST[] = 'COL_121=1'; // カフェ レクセル add 20170601
$D_FILTER_VAL_LIST[] = 'COL_06=1';  // カメラのキタムラ
$D_FILTER_VAL_LIST[] = 'COL_78=1';  // 喜瀬カントリークラブ add 20160318
$D_FILTER_VAL_LIST[] = 'COL_76=1';  // 喜瀬ビーチパレス add 20160318
//$D_FILTER_VAL_LIST[] = 'COL_56=1'; del 20160425
$D_FILTER_VAL_LIST[] = 'COL_25=1';  // キャラジャ
$D_FILTER_VAL_LIST[] = 'COL_17=1';  // 牛角
$D_FILTER_VAL_LIST[] = 'COL_122=1'; // きらやか銀行 add 20170601
$D_FILTER_VAL_LIST[] = 'COL_101=1'; // クイーンズ伊勢丹/クイーンズ伊勢丹グランデ add 20160719
$D_FILTER_VAL_LIST[] = 'COL_13=1';  // グラッチェガーデンズ
$D_FILTER_VAL_LIST[] = 'COL_44=1';  // GREEN DOG
$D_FILTER_VAL_LIST[] = 'COL_120=1'; // 興能信用金庫 add 20170515
$D_FILTER_VAL_LIST[] = 'COL_23=1';  // ゴルフ5
$D_FILTER_VAL_LIST[] = 'COL_35=1';  // コンタクトのアイシティ
$D_FILTER_VAL_LIST[] = 'COL_69=1';  // コンタクトランド add 20160120
$D_FILTER_VAL_LIST[] = 'COL_55=1';  // THE SUIT COMPANY
$D_FILTER_VAL_LIST[] = 'COL_36=1';  // THANKS ON THE TABLE．
$D_FILTER_VAL_LIST[] = 'COL_89=1';  // GLホーム add 20160425
$D_FILTER_VAL_LIST[] = 'COL_85=1';  // 滋賀トヨペット add 20160406
$D_FILTER_VAL_LIST[] = 'COL_18=1';  // シャディ・サラダ館
$D_FILTER_VAL_LIST[] = 'COL_110=1'; // しゃぶ葉 add 20170117
$D_FILTER_VAL_LIST[] = 'COL_32=1';  // 上海エクスプレス
//$D_FILTER_VAL_LIST[] = 'COL_20=1';
$D_FILTER_VAL_LIST[] = 'COL_95=1';  // ジョイフル本田/ジョイフル2/アンティークショップ グローブ' add 20161018
$D_FILTER_VAL_LIST[] = 'COL_84=1';  // 常陽銀行 add 20160318
$D_FILTER_VAL_LIST[] = 'COL_24=1';  // ジョナサン
$D_FILTER_VAL_LIST[] = 'COL_86=1';  // 新生銀行 add 20160413
$D_FILTER_VAL_LIST[] = 'COL_94=1';  // 新星堂 add 20160624
//$D_FILTER_VAL_LIST[] = 'COL_53=1'; del 20160425
$D_FILTER_VAL_LIST[] = 'COL_31=1';  // スタイルデザイナー
$D_FILTER_VAL_LIST[] = 'COL_07=1';  // スタジオマリオ
$D_FILTER_VAL_LIST[] = 'COL_114=1'; // ステーキのどん add20170301
$D_FILTER_VAL_LIST[] = 'COL_21=1';  // スポーツデポ
$D_FILTER_VAL_LIST[] = 'COL_16=1';  // スリーエフ/gooz/q’s mart
$D_FILTER_VAL_LIST[] = 'COL_123=1'; // 仙台銀行 add 20170601
$D_FILTER_VAL_LIST[] = 'COL_71=1';  // そば処吉野家 add 20160205
$D_FILTER_VAL_LIST[] = 'COL_61=1';  // ソフトバンク add 20150615
$D_FILTER_VAL_LIST[] = 'COL_49=1';  // だいわ
$D_FILTER_VAL_LIST[] = 'COL_79=1';  // タウンプラザかねひで add 20160318
//$D_FILTER_VAL_LIST[] = 'COL_57=1'; // del 20160425
$D_FILTER_VAL_LIST[] = 'COL_125=1';  // 但馬銀行 add 20170613
$D_FILTER_VAL_LIST[] = 'COL_04=1';  // TSUTAYA/ビデオ100
$D_FILTER_VAL_LIST[] = 'COL_90=1';  // T-SITE店舗 add 20160512
$D_FILTER_VAL_LIST[] = 'COL_64=1';  // デパートリウボウ add 20150421
$D_FILTER_VAL_LIST[] = 'COL_33=1';  // 東急ホテルズ
$D_FILTER_VAL_LIST[] = 'COL_20=1';  // 東武ストア/フエンテ add 20150908
$D_FILTER_VAL_LIST[] = 'COL_37=1';  // ドトールコーヒーショップ
$D_FILTER_VAL_LIST[] = 'COL_27=1';  // ドラッグイレブン
$D_FILTER_VAL_LIST[] = 'COL_42=1';  // ドラッグストアmac
$D_FILTER_VAL_LIST[] = 'COL_39=1';  // ドラッグユタカ/ユタカ調剤薬局
$D_FILTER_VAL_LIST[] = 'COL_102=1'; // とんから亭 add 20161012
$D_FILTER_VAL_LIST[] = 'COL_117=1'; // donイタリアーノ/パスタリアーノ add 20170301
$D_FILTER_VAL_LIST[] = 'COL_115=1'; // どん亭 add 20170301
$D_FILTER_VAL_LIST[] = 'COL_66=1';  // トーンモバイル add 20150514
$D_FILTER_VAL_LIST[] = 'COL_26=1';  // ニッポンレンタカー
$D_FILTER_VAL_LIST[] = 'COL_60=1';  // NEXT BLUE
//$D_FILTER_VAL_LIST[] = 'COL_19=1';
$D_FILTER_VAL_LIST[] = 'COL_51=1';  // パシフィックゴルフマネージメント
$D_FILTER_VAL_LIST[] = 'COL_73=1';  // ハックドラッグ add 20160218
$D_FILTER_VAL_LIST[] = 'COL_65=1';  // ハピナハ add 20150421
$D_FILTER_VAL_LIST[] = 'COL_10=1';  // バーミヤン
//$D_FILTER_VAL_LIST[] = 'COL_30=1';
$D_FILTER_VAL_LIST[] = 'COL_46=1';  // 日立チェーンストール
$D_FILTER_VAL_LIST[] = 'COL_91=1';  // B.B.ON add 20160526 
$D_FILTER_VAL_LIST[] = 'COL_112=1'; // ファミリア add 20170117
$D_FILTER_VAL_LIST[] = 'COL_03=1';  // ファミリーマート
$D_FILTER_VAL_LIST[] = 'COL_88=1';  // フィアスホーム add 20160425
$D_FILTER_VAL_LIST[] = 'COL_116=1'; // フォルクス add 20170301
$D_FILTER_VAL_LIST[] = 'COL_15=1';  // 富士シティオ
$D_FILTER_VAL_LIST[] = 'COL_50=1';  // プラッセだいわ
$D_FILTER_VAL_LIST[] = 'COL_108=1'; // ホグロフス add 20170117
$D_FILTER_VAL_LIST[] = 'COL_96=1';  // Polo Ralph Lauren Factory Store add 20160624
$D_FILTER_VAL_LIST[] = 'COL_74=1';  // WHITE THE SUIT COMPANY add 20160218
$D_FILTER_VAL_LIST[] = 'COL_63=1';  // Honya Club With
$D_FILTER_VAL_LIST[] = 'COL_67=1';  // MADOショップ/MADOショップパートナー add 20150514
$D_FILTER_VAL_LIST[] = 'COL_62=1';  // マミーマート
$D_FILTER_VAL_LIST[] = 'COL_57=1';  // 丸井今井 add 20160512
$D_FILTER_VAL_LIST[] = 'COL_48=1';  // マルエツ/マルエツ プチ/リンコス/魚悦
$D_FILTER_VAL_LIST[] = 'COL_109=1'; // マルエドラッグ/マルエ薬局 add 20170117
//$D_FILTER_VAL_LIST[] = 'COL_43=1'; del 20150821
$D_FILTER_VAL_LIST[] = 'COL_40=1';  // 三井のリパーク
$D_FILTER_VAL_LIST[] = 'COL_53=1';  // 三越 add 20160512
$D_FILTER_VAL_LIST[] = 'COL_41=1';  // ミニミニ
$D_FILTER_VAL_LIST[] = 'COL_43=1';  // ミフト add 20150924
$D_FILTER_VAL_LIST[] = 'COL_105=1'; // 宮崎太陽銀行 add 20161221
$D_FILTER_VAL_LIST[] = 'COL_111=1'; // むさしの森珈琲 add 20170117
$D_FILTER_VAL_LIST[] = 'COL_97=1';  // 眼鏡市場 add 20160701
$D_FILTER_VAL_LIST[] = 'COL_47=1';  // ヤオマサ/クイーンズマート/新鮮館
$D_FILTER_VAL_LIST[] = 'COL_11=1';  // 夢庵/ゆめあん食堂
$D_FILTER_VAL_LIST[] = 'COL_119=1'; // ゆめタウン/ゆめマート/LECT add 20170428
$D_FILTER_VAL_LIST[] = 'COL_54=1';  // 洋服の青山
$D_FILTER_VAL_LIST[] = 'COL_70=1';  // 吉野家 add 20160205
$D_FILTER_VAL_LIST[] = 'COL_124=1';  // ラ　オハナ add 20170613
$D_FILTER_VAL_LIST[] = 'COL_30=1';  // リウボウストア add 20150421
$D_FILTER_VAL_LIST[] = 'COL_80=1';  // LIXILショールーム add 20160318
$D_FILTER_VAL_LIST[] = 'COL_81=1';  // LIXILリフォームショップ add 20160318
$D_FILTER_VAL_LIST[] = 'COL_82=1';  // LIXILリフォームネット add 20160318
$D_FILTER_VAL_LIST[] = 'COL_29=1';  // 琉球銀行
$D_FILTER_VAL_LIST[] = 'COL_45=1';  // レッドキャベツ
$D_FILTER_VAL_LIST[] = 'COL_99=1';  // レンズスタイル add 20160701
$D_FILTER_VAL_LIST[] = 'COL_100=1'; // レンズダイレクト add 20160701
$D_FILTER_VAL_LIST[] = 'COL_34=1';  // ロッテリア
$D_FILTER_VAL_LIST[] = 'COL_93=1';  // WonderGOO add 20160624
$D_FILTER_VAL_LIST[] = 'COL_05=1';  // 街のお店




$D_FILTER_NAME_LIST[] = $D_FILTER_LIST_FIRST;
$D_FILTER_NAME_LIST[] = 'アイフルホーム'; // add 20160425
$D_FILTER_NAME_LIST[] = '藍屋';
$D_FILTER_NAME_LIST[] = '青森銀行'; // add 20160318
$D_FILTER_NAME_LIST[] = '旭屋書店'; // add 20151008
$D_FILTER_NAME_LIST[] = '足利銀行'; // add 20161221
$D_FILTER_NAME_LIST[] = 'アシックス'; // add 20170117
$D_FILTER_NAME_LIST[] = 'ALOOK'; // add 20160701
$D_FILTER_NAME_LIST[] = 'アルペン';
$D_FILTER_NAME_LIST[] = 'ERAジャパン'; // add 20160526
$D_FILTER_NAME_LIST[] = '伊勢丹'; // add 20160512
$D_FILTER_NAME_LIST[] = 'ISETAN MiRROR'; // add 20170428
$D_FILTER_NAME_LIST[] = '岩田屋'; // add 20160512
//$D_FILTER_NAME_LIST[] = 'いろどり和菜 三○三'; del 20150821
//$D_FILTER_NAME_LIST[] = 'WinBe'; del 20160425
$D_FILTER_NAME_LIST[] = 'ウエルシア';
$D_FILTER_NAME_LIST[] = 'エクセルシオール カフェ';
$D_FILTER_NAME_LIST[] = 'エディオン';
$D_FILTER_NAME_LIST[] = 'ENEOS';
$D_FILTER_NAME_LIST[] = '沖縄トヨペット'; // add 20160205
$D_FILTER_NAME_LIST[] = 'オートバックスグループ';
$D_FILTER_NAME_LIST[] = 'オニツカタイガー';
$D_FILTER_NAME_LIST[] = '恩納マリンビューパレス'; // add 20160318
$D_FILTER_NAME_LIST[] = '鹿児島高牧カントリークラブ'; // add 20160318
$D_FILTER_NAME_LIST[] = 'ガスト/ステーキガスト'; // mod 20150615
$D_FILTER_NAME_LIST[] = 'かつ久'; // add 20161012
$D_FILTER_NAME_LIST[] = '金光薬品';
$D_FILTER_NAME_LIST[] = 'カフェ レクセル'; // add 20170601
$D_FILTER_NAME_LIST[] = 'カメラのキタムラ';
$D_FILTER_NAME_LIST[] = '喜瀬カントリークラブ'; // add 20160318
$D_FILTER_NAME_LIST[] = '喜瀬ビーチパレス'; // add 20160318
//$D_FILTER_NAME_LIST[] = 'キッズデュオ'; del 20160425
$D_FILTER_NAME_LIST[] = 'キャラジャ';
$D_FILTER_NAME_LIST[] = '牛角';
$D_FILTER_NAME_LIST[] = 'きらやか銀行'; // add 20170601
$D_FILTER_NAME_LIST[] = 'クイーンズ伊勢丹/クイーンズ伊勢丹グランデ'; // add 20160719
$D_FILTER_NAME_LIST[] = 'グラッチェガーデンズ';
$D_FILTER_NAME_LIST[] = 'GREEN DOG';
$D_FILTER_NAME_LIST[] = '興能信用金庫'; // add 20170515
$D_FILTER_NAME_LIST[] = 'ゴルフ5';
$D_FILTER_NAME_LIST[] = 'コンタクトのアイシティ';
$D_FILTER_NAME_LIST[] = 'コンタクトランド'; // add 20160120
$D_FILTER_NAME_LIST[] = 'THE SUIT COMPANY';
$D_FILTER_NAME_LIST[] = 'THANKS ON THE TABLE．';
$D_FILTER_NAME_LIST[] = 'GLホーム'; // add 20160425
$D_FILTER_NAME_LIST[] = '滋賀トヨペット'; // add 20160406
$D_FILTER_NAME_LIST[] = 'シャディ・サラダ館';
$D_FILTER_NAME_LIST[] = 'しゃぶ葉'; // add 20170117
$D_FILTER_NAME_LIST[] = '上海エクスプレス';
//$D_FILTER_NAME_LIST[] = 'SHOO・LA・RUE';
$D_FILTER_NAME_LIST[] = 'ジョイフル本田/ジョイフル2/アンティークショップ グローブ'; // mod 20161018
$D_FILTER_NAME_LIST[] = '常陽銀行'; // add 20160318
$D_FILTER_NAME_LIST[] = 'ジョナサン';
$D_FILTER_NAME_LIST[] = '新生銀行'; // add 20160413
$D_FILTER_NAME_LIST[] = '新星堂'; // add 20160624
//$D_FILTER_NAME_LIST[] = 'スクールIE'; del 20160425
$D_FILTER_NAME_LIST[] = 'スタイルデザイナー';
$D_FILTER_NAME_LIST[] = 'スタジオマリオ';
$D_FILTER_NAME_LIST[] = 'ステーキのどん'; //add 20170301
$D_FILTER_NAME_LIST[] = 'スポーツデポ';
$D_FILTER_NAME_LIST[] = 'スリーエフ/gooz/q’s mart';
$D_FILTER_NAME_LIST[] = '仙台銀行'; // add 20170601
$D_FILTER_NAME_LIST[] = 'そば処吉野家'; // add 20160205
$D_FILTER_NAME_LIST[] = 'ソフトバンク'; // mod 20150615
$D_FILTER_NAME_LIST[] = 'だいわ';
$D_FILTER_NAME_LIST[] = 'タウンプラザかねひで'; // add 20160318
//$D_FILTER_NAME_LIST[] = 'チャイルドアイズ'; del 20160425
$D_FILTER_NAME_LIST[] = '但馬銀行';            // add 20170613
$D_FILTER_NAME_LIST[] = 'TSUTAYA/ビデオ100';
$D_FILTER_NAME_LIST[] = 'T-SITE店舗'; // add 20160512
$D_FILTER_NAME_LIST[] = 'デパートリウボウ'; // add 20150421
$D_FILTER_NAME_LIST[] = '東急ホテルズ';
$D_FILTER_NAME_LIST[] = '東武ストア/フエンテ'; // add 20150908
$D_FILTER_NAME_LIST[] = 'ドトールコーヒーショップ';
$D_FILTER_NAME_LIST[] = 'ドラッグイレブン';
$D_FILTER_NAME_LIST[] = 'ドラッグストアmac';
$D_FILTER_NAME_LIST[] = 'ドラッグユタカ/ユタカ調剤薬局';
$D_FILTER_NAME_LIST[] = 'とんから亭'; // add 20161012
$D_FILTER_NAME_LIST[] = 'donイタリアーノ/パスタリアーノ'; // add 20170301
$D_FILTER_NAME_LIST[] = 'どん亭'; // add 20170301
$D_FILTER_NAME_LIST[] = 'トーンモバイル'; // add 20150514
$D_FILTER_NAME_LIST[] = 'ニッポンレンタカー';
$D_FILTER_NAME_LIST[] = 'NEXT BLUE';
//$D_FILTER_NAME_LIST[] = 'HusHusH';
$D_FILTER_NAME_LIST[] = 'パシフィックゴルフマネージメント';
$D_FILTER_NAME_LIST[] = 'ハックドラッグ'; // add 20160218
$D_FILTER_NAME_LIST[] = 'ハピナハ'; // add 20150421
$D_FILTER_NAME_LIST[] = 'バーミヤン';
//$D_FILTER_NAME_LIST[] = '阪急阪神第一ホテルグループ';
$D_FILTER_NAME_LIST[] = '日立チェーンストール';
$D_FILTER_NAME_LIST[] = 'B.B.ON'; // add 20160526
$D_FILTER_NAME_LIST[] = 'ファミリア'; // add 20170117
$D_FILTER_NAME_LIST[] = 'ファミリーマート';
$D_FILTER_NAME_LIST[] = 'フィアスホーム'; // add 20160425
$D_FILTER_NAME_LIST[] = 'フォルクス'; // add 20170301
$D_FILTER_NAME_LIST[] = '富士シティオ';
$D_FILTER_NAME_LIST[] = 'プラッセだいわ';
$D_FILTER_NAME_LIST[] = 'ホグロフス'; // add 20170117
$D_FILTER_NAME_LIST[] = 'Polo Ralph Lauren Factory Store'; // add 20160624
$D_FILTER_NAME_LIST[] = 'WHITE THE SUIT COMPANY'; // add 20160218
$D_FILTER_NAME_LIST[] = 'Honya Club With';
$D_FILTER_NAME_LIST[] = 'MADOショップ/MADOショップパートナー'; // add 20150514
$D_FILTER_NAME_LIST[] = 'マミーマート';
$D_FILTER_NAME_LIST[] = '丸井今井'; // add 20160512
$D_FILTER_NAME_LIST[] = 'マルエツ/マルエツ プチ/リンコス/魚悦';
$D_FILTER_NAME_LIST[] = 'マルエドラッグ/マルエ薬局'; //add 20170117
//$D_FILTER_NAME_LIST[] = '三井ガーデンホテルズ'; del 20150821
$D_FILTER_NAME_LIST[] = '三井のリパーク';
$D_FILTER_NAME_LIST[] = '三越'; // add 20160512
$D_FILTER_NAME_LIST[] = 'ミニミニ';
$D_FILTER_NAME_LIST[] = 'ミフト'; // add 20150924
$D_FILTER_NAME_LIST[] = '宮崎太陽銀行'; // add 20161221
$D_FILTER_NAME_LIST[] = 'むさしの森珈琲'; // add 20170117
$D_FILTER_NAME_LIST[] = '眼鏡市場'; // add 20160701
$D_FILTER_NAME_LIST[] = 'ヤオマサ/クイーンズマート/新鮮館';
$D_FILTER_NAME_LIST[] = '夢庵/ゆめあん食堂'; // mod 20150924
$D_FILTER_NAME_LIST[] = 'ゆめタウン/ゆめマート/LECT'; // add 20170428
$D_FILTER_NAME_LIST[] = '洋服の青山';
$D_FILTER_NAME_LIST[] = '吉野家'; // add 20160205
$D_FILTER_NAME_LIST[] = 'ラ　オハナ'; // add 20170613
$D_FILTER_NAME_LIST[] = 'リウボウストア'; // add 20150421
$D_FILTER_NAME_LIST[] = 'LIXILショールーム'; // add 20160318
$D_FILTER_NAME_LIST[] = 'LIXILリフォームショップ'; // add 20160318
$D_FILTER_NAME_LIST[] = 'LIXILリフォームネット'; // add 20160318
$D_FILTER_NAME_LIST[] = '琉球銀行';
$D_FILTER_NAME_LIST[] = 'レッドキャベツ';
$D_FILTER_NAME_LIST[] = 'レンズスタイル'; // add 20160701
$D_FILTER_NAME_LIST[] = 'レンズダイレクト'; // add 20160701
$D_FILTER_NAME_LIST[] = 'ロッテリア';
$D_FILTER_NAME_LIST[] = 'WonderGOO'; // add 20160624
$D_FILTER_NAME_LIST[] = '街のお店';


// 拠点吹き出し
if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
	ZdcEmapMsg.setImage('{$D_DIR_BASE_G}img/msg/0002.png',new ZdcSize(242,95),
	                    '{$D_DIR_BASE_G}img/msg/0002-t.png',new ZdcSize(194,67),
	                    '{$D_DIR_BASE_G}img/msg/0003-x.gif',new ZdcSize(13,20),
	                    '{$D_DIR_BASE_G}img/msg/0002-s.png',new ZdcSize(13,13),
	                    null);
	ZdcEmapMsg.setDocPosition(0,0,4,8,11,214,55,0);
	ZdcEmapMsg.setDocOffset(-110,-90);
	ZdcEmapMsg.setTextClass('UserMsgWindowTextStyle');
EOF;

?>