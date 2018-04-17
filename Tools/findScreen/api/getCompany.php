<?php
$result = array(
			'status'		=> 	0,   // 0:NG, 1:OK
			'company'		=>  array()
			);
		
?>

<?php

function encoding_convert( $str)
{
	$str = mb_convert_encoding($str, "UTF-8", "EUC-JP");
	return $str;
}

function push_to_list($dir_list, $list ){
	
	foreach( $list as $key=> $value ){
		if(($value == ".") || ( $value == "..")){
			continue;
		} 
		if(!isset($dir_list[$value])){
			$dir_list[$value] = true;
		}		
	}	
	return $dir_list;
}



function scandirectory(){
	$dir_list = array();
	$pc_dir = "../data/httpd/p_apl/company/";
	$mobile_dir = "../data/httpd/mobile_apl/company/";
	$smt_dir = "../data/httpd/smt_apl/company/";
	if(file_exists($pc_dir)){
		$dir = scandir($pc_dir);
		if( sizeof( $dir) > 0 ){
			$dir_list = push_to_list( $dir_list, $dir );
		}
	}
	
	if(file_exists($mobile_dir)){
		$dir = scandir($mobile_dir);
		if( sizeof( $dir) > 0 ){
			$dir_list = push_to_list( $dir_list, $dir );
		}
	}
	
	if(file_exists($smt_dir )){
		$dir = scandir($smt_dir );
		if( sizeof( $dir) > 0 ){
			$dir_list = push_to_list( $dir_list, $dir );
		}
	}
	$result = array();
	foreach( $dir_list as $key=> $value ){
		array_push($result, $key);
	}
	return 	$result;
}
?>

<?php
	
	$company = scandirectory();	
	$result["company"] = $company;
	$result["status"]  = 1;
	echo json_encode( $result );
	
?>
