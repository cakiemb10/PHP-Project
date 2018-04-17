<?php
/*========================================================*/
// ファイル名：proc_optcheck.inc
// 処理名：
//
// 更新履歴
// 2011/07/05 Y.Nakajima	VM化に伴うapache,phpVerUP対応改修
// 2014/12/04 Y.Matsukawa	チェックボックスに自由な条件指定を可能にする
/*========================================================*/

$opt_link_prm = "";
$re = "";
$opt_where = "";
if( isset($SETTING["checkboxopt"]) && $SETTING["checkboxopt"] == "1" ){
	for($i =0 ; $i<count($OPTION)-1;$i++){
		foreach($OPTION[$i] as $norah => $jones ){
			$pr= $jones["name"];
			// mod 2011/07/05 Y.Nakajima
			if( isset($$pr) && $$pr){ 
				if(!$re && $opt_where)$opt_where .= " ".$OPTION["attribu"]." ";
				// add 2014/12/04 Y.Matsukawa [
				if (isset($jones["jkn"]) && $jones["jkn"]) {
					$re .= ($re ? " ".$OPTION[$i]["attribu"]." " : "")."(".$jones["jkn"].")";
				} else {
				// add 2014/12/04 Y.Matsukawa ]
					$re .= ($re ? " ".$OPTION[$i]["attribu"]." " : "").$jones["column"].":'".$jones["value"]."'"; 
				}
				$opt_link_prm .= ($opt_link_prm ?"&":"").$jones["name"]."=".$jones["value"];
			}//if( $$pr)
		}//foreach
		if($re)$opt_where .= "(".$re.")";
		$re = "";
	}//for	
}//if

?>