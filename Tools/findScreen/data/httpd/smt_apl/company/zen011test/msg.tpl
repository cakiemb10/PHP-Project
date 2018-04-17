<!--{def fukilist}-->
<div id="z_map_msg">
	<!--{each fukilist}-->
	<div id="z_map_msg_name">
		<a href="{rval fukilist/_urlShopInf}">
			<b>
			¡¦{rval fukilist/name}
			</b>
		</a>
	</div>
	<!--{/each}-->
</div>
<!--{/def}-->
<!--{ndef fukilist}-->
<div id="z_map_msg">
	<table style="border-collapse: collapse;width:100%;">
	<tr>
		<td style="vertical-align:middle;">
			<img src="{rval iconimg}" style="vertical-align:middle;" />&nbsp;
		</td>
	<tr>
	</tr>
		<td style="vertical-align:middle;padding-top:4px;">
			<!--{def link}-->
			<a href="{rval _urlShopInf}">
			<!--{/def}-->
			<b>
			{rval name}
			</b>
			<!--{def link}-->
			</a>
			<!--{/def}-->
		</td>
	</tr>
	</table>
	</div>
</div>
<!--{/ndef}-->