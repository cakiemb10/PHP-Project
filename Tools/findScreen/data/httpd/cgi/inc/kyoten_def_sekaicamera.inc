<?php
/**********************************************************************
// ��������
// 2010/01/08 Y.Matsukawa   ��������
/*********************************************************************/
//-----------------------------------------------
// ���ID����
//-----------------------------------------------
// �ޥĥ�ȥ��襷
define("SEKAI_UID_MATUKIYO", "102");			// �����������ID
$EMAP_CID[SEKAI_UID_MATUKIYO] = "matukiyo";		// ���Ѵ��ơ��֥�ۥ����������ID��e-map���ID

//// �ɥ���ID		��������
//define("SEKAI_UID_DOCOMOID", "docomo_test");	// �����������ID
//$EMAP_CID[SEKAI_UID_DOCOMOID] = "docomoid";		// ���Ѵ��ơ��֥�ۥ����������ID��e-map���ID

// ���Ѵ��ơ��֥��e-amp���ID�������������ID
$SEKAI_UID = array_flip($EMAP_CID);

//-----------------------------------------------
// ������о��������BO���꤫����������
//-----------------------------------------------
// �ޥĥ�ȥ��襷
$KYOTEN_FILTER["matukiyo"]		= "COL_51 = '1'";
//// �ɥ���ID		��������
//$KYOTEN_FILTER["docomoid"]		= "COL_02 = '1'";

//-----------------------------------------------
// ���Ϲ�������������BO���꤫����������
//-----------------------------------------------
// �ޥĥ�ȥ��襷
$KYOTEN_ITEM["matukiyo"] = array(
array("COL_NAME"=>"ADDR", "COL_NAME_LBL"=>"ADDR C0"),
array("COL_NAME"=>"COL_06", "COL_NAME_LBL"=>"COL_06 C1"),
);
//// �ɥ���ID		��������
//$KYOTEN_ITEM["docomoid"] = array(
//array("COL_NAME"=>"COL_06", "COL_NAME_LBL"=>"COL_06 C0"),
//array("COL_NAME"=>"ADDR", "COL_NAME_LBL"=>"ADDR C1"),
//array("COL_NAME"=>"COL_12", "COL_NAME_LBL"=>"COL_12 C2"),
//);

//-----------------------------------------------
// ���̾�ʥ����������ɽ����
//-----------------------------------------------
// �ޥĥ�ȥ��襷
$SEKAI_PROFILE_NAME[SEKAI_UID_MATUKIYO] = "�ޥĥ�ȥ��襷";
//// �ɥ���ID		��������
//$SEKAI_PROFILE_NAME[SEKAI_UID_DOCOMOID] = "iD���Ȥ��뤪Ź";

//-----------------------------------------------
// ����URL
//-----------------------------------------------
// �ޥĥ�ȥ��襷
$SEKAI_IMGURL[SEKAI_UID_MATUKIYO]["TMB"] = "http://webservice-upload-files.s3.amazonaws.com/users/102.jpg";
$SEKAI_IMGURL[SEKAI_UID_MATUKIYO]["PRF"] = "http://webservice-upload-files.s3.amazonaws.com/users/102.jpg";
$SEKAI_IMGURL[SEKAI_UID_MATUKIYO]["DTL"] = "http://webservice-upload-files.s3.amazonaws.com/ex/102/matsukiyo_logo_288_216.jpg";
//// �ɥ���ID		��������
//$SEKAI_IMGURL[SEKAI_UID_DOCOMOID]["TMB"] = "http://dummy/docomoid/thumb.png";
//$SEKAI_IMGURL[SEKAI_UID_DOCOMOID]["PRF"] = "http://dummy/docomoid/prof.png";
//$SEKAI_IMGURL[SEKAI_UID_DOCOMOID]["DTL"] = "http://dummy/docomoid/detail.png";

//-----------------------------------------------
// e-map URL
//-----------------------------------------------
// �ޥĥ�ȥ��襷
$SEKAI_EMAPURL[SEKAI_UID_MATUKIYO] = "http://www.e-map.ne.jp/pc/print.htm?cid=matukiyo&kid=";
//// �ɥ���ID		��������
//$SEKAI_EMAPURL[SEKAI_UID_DOCOMOID] = "http://www.e-map.ne.jp/pc/print.htm?cid=docomoid&kid=";

//-----------------------------------------------
// ���ϥ���������
//-----------------------------------------------
define("SEKAI_AIRTAG", 1);		// ��������
define("SEKAI_DTLTAG", 2);		// �ܺ٥���

//-----------------------------------------------
// �����ȵ���
//-----------------------------------------------
define("SEKAI_ALLOW_CMMT", "0");	// 1�����ġ�0���Ե���

//-------------------------------------------
// e-map����ID�������������ID �Ѵ�
//-------------------------------------------
function kyotenId2sekaiId($uid, $kyoten_id) {
	return "emap_".$uid."_".$kyoten_id;
}
//-------------------------------------------
// �����������ID��e-map����ID �Ѵ�
//-------------------------------------------
function sekaiId2KyotenId($uid, $id) {
	$pattern = '/^(emap_'.$uid.'_)(.+)/';
	if (preg_match($pattern, $id, $match)) {
		return $match[2];
	}
	return "";
}

?>