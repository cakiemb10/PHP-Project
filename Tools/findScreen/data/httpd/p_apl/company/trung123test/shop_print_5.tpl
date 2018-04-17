	<div id="topMargin"></div>
	<div id="buttonPrint">
		<a onkeypress="javascript:print();" href="javascript:print();"><img src="{rval D_DIR_COMPANY}images/print_btn_print.gif" alt="このページを印刷する" title="このページを印刷する"></a></div>
	<div id="printName">
		{rval name}
	</div>
	<table style="border:0;margin:0;padding:0;border-collapse: collapse;">
	<tr><td>
	<div id="printDtl">
		<table id="printDtlOuterTable">
			<tr>
				<td class="printDtlTdL">
					<table class="printDtlTable">
						<!--{def addr}-->
						<tr>
							<th>
								住所
							</th>
							<td>
								{rval addr}
							</td>
						</tr>
						<!--{/def}-->
						<!--[[[kyo_item _ltext]]]-->
					</table>
				</td>
				<td class="printDtlTdR" align="center">
					<table class="printQRTable">
						<tr>
							<td class="printQR">
								<img src="{rval qrimgurl}" alt="" width="82" height="82" class="qrCode" />
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</div>
	</td></tr>
	<tr><td>
	<div id="ZdcEmapMap" style="width:578px;height:550px;"></div>
	</td></tr>
	</table>
