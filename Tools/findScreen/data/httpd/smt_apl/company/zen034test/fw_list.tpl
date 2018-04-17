<!--{def list}-->
<!--{each list}-->
<div class="z_litem">
	<a href="{rval list/url}">
		<span class="z_litem_name">
			<table style="border-collapse: collapse;width:100%;">
			<tr>
				<td style="vertical-align:middle;width:32px;">
					<img src="{rval list/iconimg}" />
				</td>
				<td style="vertical-align:middle;padding-left:4px;">
					<!--{def list/icon_id_80}-->²Ú²°Í¿Ê¼±Ò&nbsp;<!--{/def}-->
					<!--{def list/icon_id_90}-->ÏÂ¿©¤è¤Ø¤¤&nbsp;<!--{/def}-->
					{rval list/name}
				</td>
				<td style="vertical-align:middle;text-align:right;">
					<span class="z_icon_arrow"></span>
				</td>
			</tr>
			</table>
		</span>
	</a>
</div>
<!--{/each}-->
<!--{/def}-->

<!--{def next}-->
<div id="ZdcEmapSearchNext" class="z_litem_nextPage">
	<a href="{rval next_url}">¤µ¤é¤ËÆÉ¤ß¹þ¤à¡¡<span class="font-9">{rval next_pos}·ï¡Á</span></a>
</div>
<!--{/def}-->
