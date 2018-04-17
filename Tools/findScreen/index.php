
<link href="css/findscreen.css" rel="stylesheet" type="text/css">
<link href="../css/default.css" rel="stylesheet" type="text/css">

<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<script src="js/findScreen.js"></script>

<a class ="back_button" href="../"> 
	Go Home
</a>

<div class="findscreen_content">

	<b>Company</b><br><br>
	<select id="company" class="notmark" >
		
	</select>	

	<br><br>
	<b>Screen file name:</b><br><br>
	<textarea type="text"   id="file_name" >
		reen/data/httpd/p_apl/company/zen011test/shop_print_0.tpl
		shop_print_9.tpl
		/data/httpd/p_apl/company/zen034test/setting_option.inc
		msg.tpl
	</textarea>	
	<br>
	

	<div class = "result">
		<div class="device">
			<p class="title pc"> PC result</p>
			
			<div class="result_tbl">
			
				<table id="pc" width = "100%">
					<tr>
							<th width="30%"> File name</th>
							<th width="70%"> Screen name </th>
					</tr>	
	
				</table>		
			</div>	

		</div>	
		
		<div class="device">
			<p class="title mobile"> Mobile result</p>
			<div class="result_tbl">
				<table id="mobile"   width = "100%">
					<tr>
							<th width="30%"> File name</th>
							<th width="70%"> Screen name </th>
						</tr>	
				</table>
			</div>
		</div>			

		<div class="device">
			<p class="title smt"> SmartPhone result</p>
			<div class="result_tbl">
				<table id="smt"  width = "100%">
					<tr>
							<th width="30%"> File name</th>
							<th width="70%"> Screen name </th>
						</tr>	
				</table>

			</div>
		</div>
	</div>
</div>

	