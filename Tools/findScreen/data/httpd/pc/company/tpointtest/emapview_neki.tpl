<div id="nekiList">
<!--{def msg}-->
	<div id="nekiListErrMsg">{rval msg}</div>
<!--{/def}-->
<!--{def list}-->
	<div id="nekiListHd">
		<table id="nekiListHeader">
			<tr>
				<td class="nekiListTitle">�Ǵ���</td>
				<td class="nekiListPage">
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
	<div id="nekiListDt">
		<table id="nekiListTable">
			<!--{each list}-->
			<tr>
				<td class="nekiListName">
					<a href="javascript:{rval list/_jsMsg};" onMouseOver="{rval list/_jsCurSet}" onMouseOut="{rval list/_jsCurRemove};">{rval list/name}</a>
				</td>
			</tr>
			<!--{/each}-->
		</table>
	</div>
<!--{/def}-->
</div>
