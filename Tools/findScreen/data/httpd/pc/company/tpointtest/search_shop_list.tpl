<table border="0" cellpadding="0" cellspacing="0" width="100%">
	<tr>
		<td align="center">
			<table id="searchShopListTitle">
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
			<table id="searchShopListExp">
				<tr>
					<td>
						{rval selname}を選んでください
					</td>
				</tr>
			</table>
			<!--{/def}-->
			<table id="searchShopListData">
			<!--{each list}-->
				<tr>
					<td class="custSearchShopListDataIcon">
						<img src="{rval list/iconimg}">
					</td>
					<td class="searchShopListDataNm">
						<a href="javascript:{rval list/_jsNameLink};">
							<!--{def list/col_02}-->
							{rval list/col_02}<br>
							<!--{/def}-->
							{rval list/name}
						</a>
					</td>
					<td class="searchShopListDataDt">
						<table class="searchShopListDtTable">
								<!--{def list/addr}-->
							<tr>
								<td>
									{rval list/addr}
								</td>
							</tr>
								<!--{/def}-->
								<!--{def list/col_01}-->
							<tr>
								<td>
									{rval list/col_01}
								</td>
							</tr>
								<!--{/def}-->
						</table>
					</td>
				</tr>
			<!--{/each}--> 
			</table>
			<table id="searchShopListPage">
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
</table>
<p class="scroll_com"><img src="{rval D_DIR_COMPANY}images/caution_1.gif"></p>
