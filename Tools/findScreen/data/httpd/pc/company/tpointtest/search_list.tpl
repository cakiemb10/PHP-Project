<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tbody>
	<tr>
		<td align="center">
			<table id="searchListTitle">
				<tr>
					<td>
					<!--{def keyword}-->
						{rval title}:&nbsp;{rval keyword}
					<!--{/def}-->
					<!--{ndef keyword}-->
						{rval title}
					<!--{/def}-->
					</td>
				</tr>
			</table>
			<!--{def selname}-->
			<table id="searchListExp">
				<tr>
					<td>
						{rval selname}を選んでください
					</td>
				</tr>
			</table>
			<!--{/def}-->
			<table id="searchListData">
			<!--{each list}-->
				<tr>
					<td><a href="javascript:{rval list/_jsNameLink};">{rval list/name}</a></td>
				</tr>
			<!--{/each}-->
			</table>
			<table id="searchListPage">
				<tr>
					<td>
					<!--{def _jsPrev}-->
						<a href="javascript:{rval _jsPrev};">前へ</a>&nbsp;←&nbsp;
					<!--{/def}-->
						{rval start}-{rval end}件/{rval max}件中
					<!--{def _jsNext}-->
						&nbsp;→&nbsp;<a href="javascript:{rval _jsNext};">次へ</a>
					<!--{/def}-->
					</td>
				</tr>
			</table>
		</td>
	</tr>
</tbody>
</table>
<p class="scroll_com"><img src="{rval D_DIR_COMPANY}images/caution_1.gif"></p>