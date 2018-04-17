<?php
/*========================================================*/
// ファイル名：add.cgi
// 処理名：チェックイン-チェックイン追加(ラッパーCGI）
//
// 更新履歴
// 2012/12/19 H.Iijima	新規作成
// 
// 
/*========================================================*/
//post
//extract($_POST);

/*==============================================*/
// CGI名
/*==============================================*/
$CGINM = strtolower(basename($_SERVER['SCRIPT_FILENAME'], '.cgi'));


$APICGINM = $CGINM;
/*==============================================*/
// エラーコード用CGI識別数 設定
/*==============================================*/
$CGICD = $CGINM;


/*==============================================*/
// 定義ファイル
/*==============================================*/
require_once('aplia_def.inc');			// 共通定義ファイル
require_once('function.inc');			// 共通関数
require_once('log.inc');				// ログ出力

/*==============================================*/
// エラー出力を明示的にOFF
/*==============================================*/
//error_reporting(E_ALL^E_NOTICE);
error_reporting(0);
//error_reporting(E_ALL);

/*==============================================*/
//ログ出力開始
/*==============================================*/
//include('logs/inc/com_log_open.inc');


/*==============================================*/
// パラメータ取得
/*==============================================*/
$SID		= getCgiParameter('sid','');		/* スキーマ名 */
$UID		= getCgiParameter('uid','');		/* UserID */
$POI_ID		= getCgiParameter('poi_id','');		/* POI ID */
$LATLON		= getCgiParameter('latlon','');		/* 緯度経度 */
$COMMENT	= getCgiParameter('comment','');	/* コメント */
$photo_flg = false;

if (is_uploaded_file($_FILES['photo']["tmp_name"])) {/* 写真 */
    $PHOTO = $_FILES['photo']['name'];
    $mimetype = $_FILES['photo']['type'];
    $photo_flg =true;
}



/*==============================================*/
// LOG出力用にパラメータ値を結合
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
// APLIA CGI 呼び出し
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
      //送信する
      $contents = "";
      $contents = file_get_contents($CGI, false, $context);

// ログ出力
//put_log($CGICD, $SID,$http_response_header[0]."(".$CGI.")", $log_parms);


header($http_response_header[0], FALSE);
Header("Content-type: application/json; charset=utf-8");
echo $contents;

exit;
?>
