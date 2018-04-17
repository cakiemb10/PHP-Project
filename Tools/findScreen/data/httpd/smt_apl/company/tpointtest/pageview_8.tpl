<!-- ここにフッタを記述してください -->
<div class="z_footer">
<p>
<table width="100%">
	<tr>
		<td id="footerLeftTd">
			<!--{def D_HP_URL}-->
			<a href="{rval D_HP_URL}">{rval D_HP_LINK_NAME}</a>
			<!--{/def}-->
		</td>
		
		<td id="footerRightTd">
			<a href="http://tsite.jp/smp/r/service/map/info.html">サービスについて</a>
		</td>
	</tr>
	<tr>
		<td id="footerLeftTd">
			<!--{ndef search_top}-->
			<a href="{rval D_URL_SEARCH_TOP}">検索TOPへ</a>
			<!--{/ndef}-->
		</td>
		
		<td id="footerRightTd">
			<a href="http://tsite.jp/smp/r/service/map/agreement.html">免責事項</a>
		</td>
	</tr>
</table>
</p>
<p id="copyright">
<!--{def D_COPYRIGHT}-->{rval D_COPYRIGHT}<!--{/def}-->
</p>
</div>
