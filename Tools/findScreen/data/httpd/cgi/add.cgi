<?php
/*========================================================*/
// �ե�����̾��add.cgi
// ����̾�������å�����-�����å������ɲ�(��åѡ�CGI��
//
// ��������
// 2012/12/19 H.Iijima	��������
// 
// 
/*========================================================*/
//post
//extract($_POST);

/*==============================================*/
// CGI̾
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));


$APICGINM = $CGINM;
/*==============================================*/
// ���顼��������CGI���̿� ����
/*==============================================*/
$CGICD = $CGINM;


/*==============================================*/
// ����ե�����
/*==============================================*/
require_once('aplia_def.inc');			// ��������ե�����
require_once('function.inc');			// ���̴ؿ�
require_once('log.inc');				// ������

/*==============================================*/
// ���顼���Ϥ�����Ū��OFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
error_reporting(0);
//error_reporting(E_ALL);

/*==============================================*/
//�����ϳ���
/*==============================================*/
//include('logs/inc/com_log_open.inc');


/*==============================================*/
// �ѥ�᡼������
/*==============================================*/
$SID		= getCgiParameter('sid','');		/* ��������̾ */
$UID		= getCgiParameter('uid','');		/* UserID */
$POI_ID		= getCgiParameter('poi_id','');		/* POI ID */
$LATLON		= getCgiParameter('latlon','');		/* ���ٷ��� */
$COMMENT	= getCgiParameter('comment','');	/* ������ */
$photo_flg = false;

if (is_uploaded_file($_FILES['photo']["tmp_name"])) {/* �̿� */
    $PHOTO = $_FILES['photo']['name'];
    $mimetype = $_FILES['photo']['type'];
    $photo_flg =true;
}



/*==============================================*/
// LOG�����Ѥ˥ѥ�᡼���ͤ���
/*==============================================*/
/*
$log_parms  = ' SID:'.$SID;
$log_parms .= ' UID:'.$UID;
$log_parms .= ' POI_ID:'.$POI_ID;
$log_parms .= ' LATLON:'.$LATLON;
$log_parms .= mb_strimwidth(' COMMENT:'.mb_convert_encoding($COMMENT,'EUC-JP','auto'), 0, 255, '...');
$log_parms .= ' PHOTO:'.$PHOTO. " MIME:".$mimetype;
*/
/*==============================================*/
// APLIA CGI �ƤӽФ�
/*==============================================*/

unset($contents);
$CGI = 'http://'.$API_APLIA_SRV.$API_APLIA_PATH.$APICGINM;
//$CGI = 'http://10.47.30.41/~suzuki/api2/v1_0/checkin/add';


$data = "";
$boundary = "---------------------".substr(md5(rand(0,32000)), 0, 10);
$postdata['sid'] =$SID;
$postdata['uid'] =$UID;
$postdata['poi_id'] =$POI_ID;
$postdata['latlon'] =$LATLON;
$postdata['comment'] =$COMMENT;

    foreach($postdata as $key => $val) {
        $data .= "--$boundary\n";
        $data .= "Content-Disposition: form-data;name=\"".$key."\"\n\n".$val."\n";
    }
    $data .= "--$boundary\n";

if($photo_flg){
    $fileContents = file_get_contents($_FILES['photo']['tmp_name']);
    $data .= "Content-Disposition: form-data;name='photo';filename=\"{$PHOTO}\"\n";
    $data .= "Content-Type: \"{$mimetype}\"\n";
    $data .= "Content-Transfer-Encoding: binary\n\n";
    $data .= $fileContents."\n";
    $data .= "--$boundary--\n";
}

$params = array('http' => array(
        'method' => 'POST',
        'header' =>'Content-Type: multipart/form-data; boundary='.$boundary,
        'content' => $data)
         );
      $context = stream_context_create($params);
      //��������
      $contents = "";
      $contents = file_get_contents($CGI, false, $context);

// ������
//put_log($CGICD, $SID,$http_response_header[0]."(".$CGI.")", $log_parms);


header($http_response_header[0], FALSE);
Header("Content-type: application/json; charset=utf-8");
echo $contents;

exit;
?>
