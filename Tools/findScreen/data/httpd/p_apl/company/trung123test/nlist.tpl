<div id="kyotenList">
<!--{def msg}-->
	<div id="kyotenListErrMsg">{rval msg}</div>
<!--{/def}-->
<!--{def list}-->

	<div id="kyotenListHd">
		<table id="kyotenListHeader">
			<tr>
				<td class="kyotenListTitle">�Ǵ��ed{rval D_USER_DEFNAME}����</td>
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
		<table id="kyotenListTable">
			<!--{each list}-->
			<tr>
				<td id="nlist_row_{rval list/kid}">
					<div class="kyotenListName">
						<a href="{rval list/_urlDetail}" id="nlist_anc_up_{rval list/kid}"
						onMouseOver="{rval list/_jsCurSet};" onMouseOut="{rval list/_jsCurRemove};"
						>
						{rval list/name}
						</a>
						
					</div>
					<!--{def list/addr}-->
					<div class="kyotenListData">
						{rval list/addr}
					</div>
					<!--{/def}-->
					<a href="javascript:void(0);" id="nlist_anc_dw_{rval list/kid}" onFocus="this.blur();"></a>
				</td>
			</tr>
		<!--{/each}-->
		</table>
	</div>

<!--{/def}-->
</div>