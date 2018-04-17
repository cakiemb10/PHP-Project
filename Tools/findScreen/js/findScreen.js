

var _SUCCESS = 1;
var _FAILED  = 0;
var _filename_list = [];
var _target_filetype = [".tpl", ".inc" ];
var _SCname_list  = [];
var _company_list = [];

	function loadCompany()
	{
		var company_url = "http://localhost/Tools/findScreen/api/getCompany.php";	
		loadAPI(company_url , waitforCompany , "mobile"  );
	}
	function waitforCompany(jsonData, result , device ){
		switch(result){
			case _SUCCESS:
					//console.log(jsonData["company"]);
					_company_list = [];
					_company_list = jsonData["company"];
					createCompanyList("company");
				break;
			case _FAILED:
				break;
			default:
				break;	
		}
	}

	function createCompanyList( id ){		
		if( _company_list.length > 0 ){
			var selector = document.getElementById(id);		
			for( var i = 0; i < _company_list.length; i++){
			    var element = document.createElement("option");
			    element.text = _company_list[i];
			    element.value = _company_list[i];
			    selector.add(element);
		    }
		}
	}

	function loadAPI( api_url ,callback, device)
	{
		$.ajax({
		  type: 'GET',
		  url: api_url,
		  data: { 'patientID' : 1 },
		  dataType: 'json',
		  success: function(jsonData) {	    
		   // console.log("SC");
		    callback( jsonData, _SUCCESS , device );

		  },
		  error: function(jsonData) {
		    console.log("error");
		    callback( jsonData, _FAILED );

		  },
		  always:function(jsonData){
		  	console.log("always");
		  }

		});

	}

	function getCompany( pasteStr ){
		var style = ["/company/", "\\company\\"];
		style["/company/"] = "/";
		style["\\company\\"] = "\\";
		var companynm = "";	

		for( var i = 0; i < style.length; i ++ ){
			var searchStr = style[i];
			var slash     = style[style[i]];
			var pos = pasteStr.indexOf(searchStr);
			var substr;
			if( pos > 0 )
			{
				substr = pasteStr.substring(pos+ searchStr.length );
				var sub_pos = substr.indexOf(slash);
				if( sub_pos > 0 )	{
					companynm = substr.substring(0, sub_pos );	
				}
				else{
					continue;
				}
			}
		}

		return companynm;
	}

$(document).ready(function(){	

	$("#file_name").bind("paste",function(e){
		resetmark("pc");
		resetmark("mobile");
		resetmark("smt");
		var pastedData = e.originalEvent.clipboardData.getData('text');
		//console.log(pastedData);
		_filename_list = []; 
		getFileName(  pastedData );

		var pastedCompany = getCompany(pastedData);
		var company = $("#company option:selected").val();
		
		resetselector("company");
		if( "" != pastedCompany )
		{
			if(( company != pastedCompany ) && ( _company_list.includes(pastedCompany))){
			 	_SCname_list["pc"] = [];   
				_SCname_list["mobile"] = [];
				_SCname_list["smt"] = [];
				removeTable("pc");
				removeTable("mobile");
				removeTable("smt");
				setCompany("company", pastedCompany );	
			}			
		}

//		console.log( pastedCompany );
		company = $("#company option:selected").val();
		var nm      = "";	
		var dvc     = ["p", "mobile","smt"];
		var pc_url  = "";
		var m_url   = "";

		var smt_url = "";
		for ( var i = 0; i< _filename_list.length; i++ ){
			nm = _filename_list[i];
			pc_url = "http://localhost/Tools/findScreen/api/getSCfromNm.php?nm="+nm+"&dvc="+dvc[0]+"&cmp="+company;	
			
			loadAPI(pc_url , waiResult , "pc" );

			m_url = "http://localhost/Tools/findScreen/api/getSCfromNm.php?nm="+nm+"&dvc="+dvc[1]+"&cmp="+company;	
			loadAPI(m_url , waiResult , "mobile"  );
			
			smt_url = "http://localhost/Tools/findScreen/api/getSCfromNm.php?nm="+nm+"&dvc="+dvc[2]+"&cmp="+company;	
			loadAPI(smt_url , waiResult , "smt"  );
		}
	});	

	function removeTable(id){
		var table = document.getElementById(id);
		var rows = table.getElementsByTagName('tr');

		while( table.getElementsByTagName('tr').length > 1  )
		{			
			var test  = document.getElementById(id);
    		test.deleteRow(1);
		}	
	}

	function resetselector(id){
		var selector = document.getElementById(id);		
		selector.removeAttribute('class','notmark');
	}

	function setCompany( id , comnstr ){
		var selector = document.getElementById(id);		
		var ele      = null;

		for( var i = 0; i < selector.length; i++)
		{
			ele = selector[i];
			if( ele.text == comnstr){
				selector.options[selector.selectedIndex].removeAttribute("selected");
				ele.setAttribute('selected','true');
				selector.setAttribute('class','mark');
			}
		}

		console.log(selector);
	}

	function getFileName( filename_str ){

		//var filename_str = $("#file_name").val();
		var list = filename_str.split("\n");
		var result = [];
		//console.log(list);
		for( var i = 0; i< list.length; i++){		
			for( var k = 0; k < _target_filetype.length; k++ ){	
				extractFileName(list[i].trim() ,_target_filetype[k]);			
			}
		}	
		//console.log( _filename_list );
	}

	function extractFileName( rowsData , split ){	
		var file_list = [];	
		if( -1 != rowsData.indexOf(split)){
			file_list = rowsData.split(split);	
			for( var i = 0;  i < file_list.length; i++ ){
				var last_sl = file_list[i].lastIndexOf("/");	
				var last_fl = file_list[i].lastIndexOf("\\");
				if(( -1 != last_sl ) || ( -1 != last_fl )){
					last_sl = last_sl > last_fl? last_sl: last_fl;
						if ( !_filename_list.includes( file_list[i].substring(last_sl+1)+split ) ){
							_filename_list.push( file_list[i].substring(last_sl+1)+split );	
						}						
				}
				else{
					if( "" != file_list[i]){
						if ( !_filename_list.includes( (file_list[i]+split).trim() ) ){
							_filename_list.push( (file_list[i]+split).trim());								
						}	
					}
				}			
			}		
		}

	}

	function waiResult( jsonData, result , device){
		//console.log( device+"--"+result );
		switch( result )
		{
			case _SUCCESS:
				//console.log(jsonData);				
				var filename = jsonData['param']['nm'];
				var SCname = jsonData['screen_name'];				
				//resetmark(device);		
				
				if( _SCname_list[device] == undefined || !_SCname_list[device].includes(filename)){			
					if( "" !=  SCname.trim() ){
						addRowtoTable( device, filename, SCname);	
						_SCname_list[device].push(filename);
						_SCname_list[device][filename] = gettotal(device)-1;
						//_SCname_list[device][filename] = SCname;
						
					}
				}
				else if ( _SCname_list[device][filename]!= undefined ){
					var pos = gettotal(device) - _SCname_list[device][filename];
					setmark(device, pos );
				}

				//console.log( _SCname_list);

			 break;
			case _FAILED:
				resetmark(device);			
				console.log("failed");

			 break;

			 default:
			 break;
		}
	}

	function gettotal(id){
		var table = document.getElementById(id);
		var rows = table.getElementsByTagName('tr');
		if( rows != undefined){
			return rows.length;
		}
		return 0;	
	}

	function resetmark(id){
		var table = document.getElementById(id);
		var rows = table.getElementsByTagName('tr');
		for( var i = 0; i < rows.length; i++ ){
			if( rows[i].hasAttribute('class')){
				rows[i].removeAttribute('class');
			}
		}		
	}

	function setmark(id , rownum){
		var table = document.getElementById(id);
		var rows = table.getElementsByTagName('tr');
		if( rows[rownum] != undefined ){
			rows[rownum].setAttribute('class','mark');
		}
	}

	function addRowtoTable( id , data0, data1 ){
		var table = document.getElementById(id);		
	    var row = table.insertRow(1);	    
	    setmark(id,1);
	    var cell1 = row.insertCell(0);
	    var cell2 = row.insertCell(1);
	    cell1.innerHTML = data0;
	    cell2.innerHTML = data1;
	}



});


//JavaScript
window.onload = function(){
 	_SCname_list["pc"] = [];   
	_SCname_list["mobile"] = [];
	_SCname_list["smt"] = [];
	loadCompany();
}