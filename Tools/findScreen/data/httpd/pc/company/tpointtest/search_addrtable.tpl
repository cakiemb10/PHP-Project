<table border="0" cellpadding="0" cellspacing="0" width="100%">
	<tr>
		<td align="center">
			<table id="searchAddrTableTitle">
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
			<table id="searchAddrTableExp">
				<tr>
					<td>
						{rval selname}������Ǥ�������
					</td>
				</tr>
			</table>
			<!--{/def}-->
			<!--{def area}-->
			<!-- ���ꥢɽ�� -->
			<table class="searchAddrTableData">
				<tr>
					<td colspan="3">
						<a href = "javascript:{rval _jsAreaLink}">{rval area}&nbsp;&nbsp;�ն���Ͽޤ�ɽ�����ޤ�</a>
					</td>
				</tr>
			</table>
			<!-- ���ꥢɽ�������ޤ� -->
			<!--{/def}-->
			<!--{def kana}-->
			<!-- ����ɽ�� -->
			<table class="searchAddrTableData">
				<tr>
					<!--{each kana}--> 
					<td><a href="javascript:{val kana/_jsLink}">{rval kana/on}</a></td>
					<!--{/each}-->
				</tr>
			</table>
			<!-- ����ɽ�������ޤ� -->
			<!--{/def}-->
			<table class="searchAddrTableData">
		<!--{each list}--> 
			<!--{def list/lf}-->
				</tr>
				<tr>
			<!--{/def}-->
			<!--{def list/name}--> 
				<td width="33%"><a href="javascript:{val list/_jsNameLink}">{rval list/name}</a></td>
			<!--{/def}-->
			<!--{def list/null}-->
				<td width="188" align="left"><br></td>
			<!--{/def}-->
		<!--{/each}-->
			</table>
			<table id="searchAddrTablePage">
				<tr>
					<td>
		<!--{def _jsPrev}-->
						<a href="javascript:{rval _jsPrev};">����</a>&nbsp;��&nbsp;
		<!--{/def}-->
						{rval start}-{rval end}��/{rval max}����
		<!--{def _jsNext}-->
						&nbsp;��&nbsp;<a href="javascript:{rval _jsNext};">����</a>
		<!--{/def}-->
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<p class="scroll_com"><img src="{rval D_DIR_COMPANY}images/caution_1.gif"></p>