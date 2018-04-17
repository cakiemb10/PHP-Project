<?php
/*********************************************************************/
// ��������
// 2014/11/28 C.Eguchi		��������
/*********************************************************************/
    /*==============================================*/
    // JSON����
	//  * header���ȥǡ�������ʸ�������ɤ��Ѵ� *
    /*==============================================*/
    function output_json($enc,$ary_out_data) {

        // JSON�饤�֥���ɤ߹���
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

        header("Content-type: application/json; charset=$encStr");	// �إå�����
		mb_convert_variables($encCnv, 'EUC-JP', $ary_out_data);		// ʸ���������Ѵ�
        echo $json->encode($ary_out_data);
        exit;

    }

?>