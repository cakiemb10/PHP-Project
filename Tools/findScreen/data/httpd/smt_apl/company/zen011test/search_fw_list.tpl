<!--{def list}-->
<!--{each list}-->
<div class="z_litem">
	<a href="{rval list/url}">
		<span class="z_litem_name">{rval list/name}<!--{ndef Pinpoint}-->&nbsp;周辺<!--{/ndef}--></span><span class="z_iconmiddle"><span class="z_icon_arrow"></span></span>
	</a>
</div>
<!--{/each}-->
<!--{/def}-->

<!--{def next}-->
<div id="ZdcEmapSearchNext{rval search_target}" class="z_litem_nextPage">
	<a href="{rval next_url}">さらに読み込む　<span class="font-9">{rval next_pos}件〜</span></a>
</div>
<!--{/def}-->
