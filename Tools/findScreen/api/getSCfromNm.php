<?php
$result = array(
			'param'			=>	array(),
			'status'		=> 	0,   // 0:NG, 1:OK
			'screen_name'	=>  ""
			);
?>

<?php

function encoding_convert( $str)
{
	$str = mb_convert_encoding($str, "UTF-8", "EUC-JP");
	return $str;
}

?>

<?php

	$cmp = "";
	$dvc = "";
	if( isset($_GET["cmp"]) &&
	    isset($_GET["dvc"]) 	){
		$cmp = $_GET["cmp"];
		$dvc = $_GET["dvc"];
		$result['param']['cmp'] = $cmp;
		$result['param']['dvc'] = $dvc;
	}
	$include_path = "../data/httpd/".$dvc."_apl/company/".$cmp."/_tpl_inf.inc";
	
	//var_dump(file_exists($include_path));
	//echo $include_path;
	
	if(file_exists($include_path)){
		require_once($include_path);			
	}else{
		$result['status'] = -1;
	}

	if( isset($_GET["nm"])){
		$nm = $_GET["nm"];	
		$result['param']['nm'] = $nm;
		if( isset($TPL_FILE_DEF[$nm]['NM'])){
			$result['screen_name']  = encoding_convert($TPL_FILE_DEF[$nm]['NM']);
			
			$result['status'] 	    = 1;
		}
		else{
			$result['status'] 	    = -2;			
		}
	}
	else{
		$result['status'] 	    = -3;
	}
	echo json_encode( $result );
	
?>
