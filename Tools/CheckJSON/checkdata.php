<!DOCTYPE html>
<html>
<head>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<link href="../css/default.css" rel="stylesheet" type="text/css">
<link href="css/checkdata.css" rel="stylesheet" type="text/css">
<script type="text/javascript">
	var _DONE 	= 1;
	var _FAILED = 0;
	
$(document).ready(function(){		
	var _target_data = [];
    $("#get_json").click(function(){
        
		// read text file
		_target_data = [];
		var text_filename = $("#target_filename").val();
		readText(text_filename, onreadTextResult);
		
		// Read JSON
		var json_filename = $("#json_filename").val();
		getJSON(json_filename, onReadSucessFunc, onReadFailedFunc );				
		console.log("DONE");
		
    });	
	
	function onreadTextResult( result, data )
	{
		switch(result){
			case _DONE:
				console.log( "DONE" );	
				_target_data = data.split("\n");
				console.log( _target_data );
				break;
			case _FAILED:
				console.log( "_FAILED" );	
				break;
			default:
				break;			
		}
	}
	
	function readText(filename, callbackFunc ){		
		var result = 0;
		var jqxhr = $.get( filename, function(data) {
		  console.log( "text success" );
		})
		  .done(function(data) {
			// console.log(data);
			result = _DONE;
		  })
		  .fail(function(data) {
			//console.log( "error" );
			result = _FAILED;
		  })
		  .always(function(data) {
			//console.log( "finished" );
		  });		 

		jqxhr.always(function(data) {				
		  callbackFunc( result,data);
		});		
	}	
	
	
	function onReadSucessFunc(json)
	{	
		var coldata = json.store_list;		
		var msg = "Result<br>";		
		if ( _target_data.length <=  0 ){
			msg = "<br>Text file is empty or can not read text file";
		}else{
		
			if( (json.store_list !== undefined ) && (coldata !== null ) ){		
				
				for ( var j = 0; j < _target_data.length; j++ ){
					var key = _target_data[j].trim();					
					for(var i = 0; i < coldata.length; i++ ){
						var content = coldata[i].content;
						if( findKeyInJSON(key, content )){
							msg = msg+"<br>"+key+" = Existed";
							break;
						}
					}
					if( i == coldata.length){
							msg = msg+"<br> "+key+" = Not Existed";
					}		
				}
			}else{
				msg = "<br>JSON format is not match with current's processing";
			}		
		}
	// set text for result
		$("#result").html(msg);
	}
	
	function findKeyInJSON( key, jsondata )
	{
		for( var i = 0; i< jsondata.length; i++ )
		{
			if( jsondata[i].col == key )
				return true;			
		}
	return false;
		
	}
	
	function onReadFailedFunc(json,filename )
	{
		//console.log( json );
		_result = _FAILED;
		var msg = "<br> Can not find JSON file: "+filename;
		$("#result").html(msg);		
	}
	
	function getJSON(filename, onSuccess, onFailed )
	{
		$.getJSON( filename, function(json) {
		console.log( "success" );	
		})
		  .done(function(json) {
			console.log( "second success" );
			onSuccess(json);			
		  })
		  .fail(function(json) {
			console.log( "error" );
			onFailed(json, filename);	
		  })
		  .always(function(json) {
			console.log( "always " );					
		  });					  
	}		
});

//JavaScript
window.onload = function(){
    $("#target_filename").val("target.txt");
	$("#json_filename").val("test_data.json");
}

</script>

</head>
<body >
<a class ="back_button" href="../"> 
	Go Home
</a>
<div class="checkdata_content">
	Target filename
	<input type ="text"  id = "target_filename" /> <br>
	JSON File name 
	<input type ="text"  id = "json_filename" /> <br>
	<button id = "get_json"> GetJSON</button>
	<p id ="result" ></p>
</div>	

</body>
</html>
