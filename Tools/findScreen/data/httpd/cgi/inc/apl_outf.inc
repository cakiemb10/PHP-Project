<?php
/*********************************************************************/
// 更新履歴：
// 2014/11/28 C.Eguchi		新規作成
/*********************************************************************/
    /*==============================================*/
    // JSON出力
	//  * header部とデータ部の文字コードを変換 *
    /*==============================================*/
    function output_json($enc,$ary_out_data) {

        // JSONライブラリ読み込み
        require_once('/home/emap/src/Jsphon/Encoder.php');
        $json = new Jsphon_Encoder(false);

        switch ($enc) {
            case "UTF8":
                $encCnv = "UTF-8";
                $encStr = "UTF-8";
                break;
            case "EUC":
                $encCnv = "EUC-JP";
                $encStr = "EUC-JP";
                break;
            default:
                $encCnv = "SJIS";
                $encStr = "Shift_JIS";
        }

        header("Content-type: application/json; charset=$encStr");	// ヘッダ設定
		mb_convert_variables($encCnv, 'EUC-JP', $ary_out_data);		// 文字コード変換
        echo $json->encode($ary_out_data);
        exit;

    }

?>
