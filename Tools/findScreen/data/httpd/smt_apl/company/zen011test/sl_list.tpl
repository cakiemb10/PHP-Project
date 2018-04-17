<!--{def pg1}-->
<!--{def html_sl_upper}-->
<div class="z_sl_upper clearfix">
	<div class="fl">
		<!--{def _urlUpperTodMapLink}-->
		<a href="{rval _urlUpperTodMapLink}" class="z_btn_map_a" style="margin-top:3px;"><span class="z_icon_japan"></span>地図を表示</a>
		<!--{/def}-->
		<ul>
		<li>
			<img src="{rval D_DIR_COMPANY}img/label-search.png" alt=""><span class="t-result mL10">{rval html_sl_upper}</span>
		</li>
		</ul>
	</div>
</div>
<!--{/def}-->
<!--{/def}-->
<!--{def list}-->
<!--{each list}-->
<div class="z_litem">
	<a href="{rval list/url}">
		<!--{ndef list/kyoten_id}-->
		<span class="z_litem_name">{rval list/name}({rval list/count})</span><span class="z_iconmiddle"><span class="z_icon_arrow"></span></span>
		<!--{/ndef}-->
		<!--{def list/kyoten_id}-->
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
		<!--{/def}-->
	</a>
</div>
<!--{/each}-->
<!--{/def}-->

<!--{def next}-->
<div id="ZdcEmapSearchNext" class="z_litem_nextPage">
	<a href="{rval next_url}">さらに読み込む　<span class="font-9">{rval next_pos}件〜</span></a>
</div>
<!--{/def}-->
