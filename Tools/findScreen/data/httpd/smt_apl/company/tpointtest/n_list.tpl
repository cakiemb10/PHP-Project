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
		<table width="100%">
			<tr>
				<td style="vertical-align: middle;">
					<table>
						<!--{def list/COL_02}-->
						<tr>
							<td>
								<span class="z_litem_name">{rval list/COL_02}</span>
							</td>
						</tr>
						<!--{/def}-->
						<tr>
							<td>
								<span class="z_litem_name">{rval list/name}<!--{def list/dist}-->({rval list/dist}m)<!--{/def}--></span>
							</td>
						</tr>
					</table>
				</td>
				<!--{vdef list/new}-->
				<td width="40px" style="vertical-align: middle;">
					<img src="{rval D_DIR_COMPANY}img/A-1_C-4.gif">
				</td>
				<!--{/vdef}-->
				<td width="40px" style="vertical-align: middle;">
					<span class="z_iconmiddle"><span class="z_icon_arrow"></span></span>
				</td>
			</tr>
		</table>
	</a>
</div>
<!--{/each}-->
<!--{/def}-->

<!--{def next}-->
<div id="ZdcEmapSearchNext" class="z_litem_nextPage">
	<a href="{rval next_url}">さらに読み込む　<span class="font-9">{rval next_pos}件〜</span></a>
</div>
<!--{/def}-->
