<table border="0" cellpadding="0" cellspacing="0" width="100%">
	<tr>
		<td align="center">
			<table id="searchShopListTitle">
				<tr>
					<td id="searchShopListTitleNm">
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
					<td class="searchShopListDataNm">
						<a href="{rval list/_urlNameLink}">{rval list/name}</a>
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
						</table>
					</td>
				</tr>
			<!--{/each}--> 
			</table>
			<table id="searchShopListPage">
				<tr>
					<td>
		<!--{def _urlPrev}-->
						<a href="{rval _urlPrev}">前へ</a>&nbsp;←&nbsp;
		<!--{/def}-->
						{rval start}-{rval end}件/{rval max}件中
		<!--{def _urlNext}-->
						&nbsp;→&nbsp;<a href="{rval _urlNext}">次へ</a>
		<!--{/def}-->
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
