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
		<a href="{rval _urlDetail}">
		{rval name}
		</a>
	</div>
	<!--{def addr}-->
	<div id="fukidashi-data">
		{rval addr}
	</div>
	<!--{/def}-->
<!--{/ndef}-->
</div>
