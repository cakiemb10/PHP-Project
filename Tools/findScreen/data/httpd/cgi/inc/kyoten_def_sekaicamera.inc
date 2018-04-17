<?php
/**********************************************************************
// 更新履歴：
// 2010/01/08 Y.Matsukawa   新規作成
/*********************************************************************/
//-----------------------------------------------
// 企業ID設定
//-----------------------------------------------
// マツモトキヨシ
define("SEKAI_UID_MATUKIYO", "102");			// セカイカメラID
$EMAP_CID[SEKAI_UID_MATUKIYO] = "matukiyo";		// 【変換テーブル】セカイカメラID→e-map企業ID

//// ドコモID		※検証用
//define("SEKAI_UID_DOCOMOID", "docomo_test");	// セカイカメラID
//$EMAP_CID[SEKAI_UID_DOCOMOID] = "docomoid";		// 【変換テーブル】セカイカメラID→e-map企業ID

// 【変換テーブル】e-amp企業ID→セカイカメラID
$SEKAI_UID = array_flip($EMAP_CID);

//-----------------------------------------------
// 拠点抽出条件（本来はBO設定から取得する）
//-----------------------------------------------
// マツモトキヨシ
$KYOTEN_FILTER["matukiyo"]		= "COL_51 = '1'";
//// ドコモID		※検証用
//$KYOTEN_FILTER["docomoid"]		= "COL_02 = '1'";

//-----------------------------------------------
// 出力項目設定（本来はBO設定から取得する）
//-----------------------------------------------
// マツモトキヨシ
$KYOTEN_ITEM["matukiyo"] = array(
array("COL_NAME"=>"ADDR", "COL_NAME_LBL"=>"ADDR C0"),
array("COL_NAME"=>"COL_06", "COL_NAME_LBL"=>"COL_06 C1"),
);
//// ドコモID		※検証用
//$KYOTEN_ITEM["docomoid"] = array(
//array("COL_NAME"=>"COL_06", "COL_NAME_LBL"=>"COL_06 C0"),
//array("COL_NAME"=>"ADDR", "COL_NAME_LBL"=>"ADDR C1"),
//array("COL_NAME"=>"COL_12", "COL_NAME_LBL"=>"COL_12 C2"),
//);

//-----------------------------------------------
// 企業名（セカイカメラ表示）
//-----------------------------------------------
// マツモトキヨシ
$SEKAI_PROFILE_NAME[SEKAI_UID_MATUKIYO] = "マツモトキヨシ";
//// ドコモID		※検証用
//$SEKAI_PROFILE_NAME[SEKAI_UID_DOCOMOID] = "iDが使えるお店";

//-----------------------------------------------
// 画像URL
//-----------------------------------------------
// マツモトキヨシ
$SEKAI_IMGURL[SEKAI_UID_MATUKIYO]["TMB"] = "http://webservice-upload-files.s3.amazonaws.com/users/102.jpg";
$SEKAI_IMGURL[SEKAI_UID_MATUKIYO]["PRF"] = "http://webservice-upload-files.s3.amazonaws.com/users/102.jpg";
$SEKAI_IMGURL[SEKAI_UID_MATUKIYO]["DTL"] = "http://webservice-upload-files.s3.amazonaws.com/ex/102/matsukiyo_logo_288_216.jpg";
//// ドコモID		※検証用
//$SEKAI_IMGURL[SEKAI_UID_DOCOMOID]["TMB"] = "http://dummy/docomoid/thumb.png";
//$SEKAI_IMGURL[SEKAI_UID_DOCOMOID]["PRF"] = "http://dummy/docomoid/prof.png";
//$SEKAI_IMGURL[SEKAI_UID_DOCOMOID]["DTL"] = "http://dummy/docomoid/detail.png";

//-----------------------------------------------
// e-map URL
//-----------------------------------------------
// マツモトキヨシ
$SEKAI_EMAPURL[SEKAI_UID_MATUKIYO] = "http://www.e-map.ne.jp/pc/print.htm?cid=matukiyo&kid=";
//// ドコモID		※検証用
//$SEKAI_EMAPURL[SEKAI_UID_DOCOMOID] = "http://www.e-map.ne.jp/pc/print.htm?cid=docomoid&kid=";

//-----------------------------------------------
// 出力タグタイプ
//-----------------------------------------------
define("SEKAI_AIRTAG", 1);		// エアタグ
define("SEKAI_DTLTAG", 2);		// 詳細タグ

//-----------------------------------------------
// コメント許可
//-----------------------------------------------
define("SEKAI_ALLOW_CMMT", "0");	// 1：許可、0：不許可

//-------------------------------------------
// e-map拠点ID→セカイカメラID 変換
//-------------------------------------------
function kyotenId2sekaiId($uid, $kyoten_id) {
	return "emap_".$uid."_".$kyoten_id;
}
//-------------------------------------------
// セカイカメラID→e-map拠点ID 変換
//-------------------------------------------
function sekaiId2KyotenId($uid, $id) {
	$pattern = '/^(emap_'.$uid.'_)(.+)/';
	if (preg_match($pattern, $id, $match)) {
		return $match[2];
	}
	return "";
}

?>
