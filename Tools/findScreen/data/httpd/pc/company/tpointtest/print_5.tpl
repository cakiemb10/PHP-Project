	<div id="topMargin"></div>
	<div id="buttonPrint">
		<a onkeypress="javascript:print();" href="javascript:print();"><img src="{rval D_DIR_COMPANY}images/print_btn_print.gif" alt="このページを印刷する" title="このページを印刷する"></a></div>
	<div id="printName">
		<table id="custPrintNameTable">
			<tr>
				<th>
					<img src="{rval iconimg}">
				</th>
				<td>
					<!--{def col_02}-->
					{rval col_02}<br>
					<!--{/def}-->
					{rval name}
				</td>
			</tr>
		</table>
	</div>
	<div id="printDtl">
		<table id="printDtlOuterTable">
			<tr>
				<td class="printDtlTdL">
					<table class="printDtlTable">
						<!--[[[kyo_item _ltext]]]-->
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
						<!--{def col_01}-->
						<tr>
							<th>
								電話番号
							</th>
							<td>
								{rval col_01}
							</td>
						</tr>
						<!--{/def}-->
						<!--[[[kyo_item _ltext]]]-->
					</table>
				</td>
			</tr>
		</table>
	</div>
	<div id="ZdcEmapMap"></div>
