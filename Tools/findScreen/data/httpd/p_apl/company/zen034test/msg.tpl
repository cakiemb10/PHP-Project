<div id="fukidashi">
<!--{def fukilist}-->
	<!--{each fukilist}-->
	<div id="fukidashi-name">
		<a href="{rval fukilist/_urlDetail}">
		¡¦{rval fukilist/name}
		</a>
	</div>
	<!--{/each}-->
<!--{/def}-->
<!--{ndef fukilist}-->
	<div id="fukidashi-name">
		<table style="border-collapse: collapse;width:100%;">
		<tr>
			<td style="vertical-align:middle;width:36px;">
				<img src="{rval _cgiIconimg}{rval icon}" />
			</td>
			<td style="vertical-align:middle;padding-right:1px;padding-left:2px;text-align:left;">
				<a href="{rval _urlDetail}">
				<!--{def icon_80}-->²Ú²°Í¿Ê¼±Ò&nbsp;<!--{/def}-->
				<!--{def icon_90}-->ÏÂ¿©¤è¤Ø¤¤&nbsp;<!--{/def}-->
				{rval name}
				</a>
			</td>
		</tr>
		</table>
	</div>
	<!--{def addr}-->
	<div id="fukidashi-data">
		{rval addr}
	</div>
	<!--{/def}-->
<!--{/ndef}-->
</div>
