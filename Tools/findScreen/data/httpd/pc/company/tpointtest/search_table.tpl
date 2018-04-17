<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tbody>
	<tr>
		<td align="center">
			<table id="searchTableTitle">
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
			<table id="searchTableExp">
				<tr>
					<td>
						{rval selname}を選んでください
					</td>
				</tr>
			</table>
			<!--{/def}-->
			<!--{def kana}-->
			<!-- カナ表示 -->
			<table class="searchTableData">
				<tr>
					<!--{each kana}--> 
					<td><a href="javascript:{val kana/_jsLink}">{rval kana/on}</a></td>
					<!--{/each}-->
				</tr>
			</table>
			<!-- カナ表示ここまで -->
			<!--{/def}-->
			<table class="searchTableData">
		<!--{each list}--> 
			<!--{def list/lf}-->
				</tr>
				<tr>
			<!--{/def}-->
			<!--{def list/name}--> 
					<td width="200">
						<div><a href="javascript:{val list/_jsNameLink};">{rval list/name}</a></div>
					<!--{def list/name2}--> 
						<div class="searchTableRosenNm">{rval list/name2}</div>
					<!--{/def}-->
					</td>
			<!--{/def}-->
			<!--{def list/null}-->
					<td width="200"><br></td>
			<!--{/def}-->
		<!--{/each}-->
			</table>
			<table id="searchTablePage">
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