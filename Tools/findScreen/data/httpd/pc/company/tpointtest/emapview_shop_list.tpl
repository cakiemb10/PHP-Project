<div id="kyotenList">
<!--{def msg}-->
	<div id="kyotenListErrMsg">{rval msg}</div>
<!--{/def}-->

<!--{def list}-->
	<div id="kyotenListHd">
		<table id="kyotenListHeader">
			<tr>
				<td class="kyotenListTitle">�Ǵ���T�ݥ���������</td>
				<td class="kyotenListPage">
					<!--{def _jsPrev}-->
					<a href="javascript:{rval _jsPrev}">����</a>��
					<!--{/def}-->
					&nbsp;{rval start}-{rval end}��/{rval max}����
					<!--{def _jsNext}-->
					&nbsp;��<a href="javascript:{rval _jsNext}">����</a>
					<!--{/def}-->
				</td>
			</tr>
		</table>
	</div>
	<div id="kyotenListDt">
		<table class="custKyotenListTable">
			<!--{each list}-->
			<tr>
				<td>
					<table class="custKyotenlistName">
						<tr>
							<td width="40">
								<img src="{rval list/iconimg}">
							</td>
							<td>
								<div class="kyotenListName">
									<a href="javascript:{rval list/_jsDetail};{rval list/_jsCurSet};"
									onMouseOver="{rval list/_jsCurSet};" onMouseOut="{rval list/_jsCurRemove};"
									>
									<!--{def list/col_02}-->
									{rval list/col_02}<br>
									<!--{/def}-->
									{rval list/name}
									</a>
								</div>
							</td>
						</tr>
					</table>
					<!--{def list/addr}-->
					<div class="kyotenListData">
						{rval list/addr}
					</div>
					<!--{/def}-->
					<!--{def list/col_01}-->
					<div class="kyotenListData">
						{rval list/col_01}
					</div>
					<!--{/def}-->
				</div>
			</td>
		</tr>
		<!--{/each}-->
	</table>
<!--{/def}-->
</div>