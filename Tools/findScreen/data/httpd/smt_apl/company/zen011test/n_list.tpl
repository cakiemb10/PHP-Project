<!--{def head}-->
<div class="z_nlist_head clearfix">
<div class="fl">
	<p id="ZdcEmapSearchCount" class="z_nlist_count">{rval search_count_msg}</p>
	<a href="{rval _urlMap}" class="z_btn_map_a"><span class="z_icon_japan"></span>地図で表示</a>
</div>
</div>
<!--{/def}-->

<!--{def hit_count}-->
<input type="hidden" name="hit_count" value="{rval hit_count}" />
<!--{/def}-->
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
	<a href="{rval next_url}">さらに読み込む　<span class="font-9">{rval next_pos}件〜</span></a>
</div>
<!--{/def}-->
