<section>
	<div class="z_litem">
		<a href="{rval _urlAddrL}"><span class="z_litem_name">住所リストから選択</span>
			<span class="z_icon_arrow"></span>
		</a>
	</div>
<!--{def D_SEARCH_AVAILABLE}-->
	<form name="formFw" method="get" action="{rval _urlFw}" onSubmit="{rval _jsFWSubmit}">
		<input type="hidden" name="enc"			value="UTF8" />
		<input type="hidden" name="mode"		value="{rval mode}" />
		<input type="hidden" name="kid"			value="{rval kid}" />
		<input type="hidden" name="klat"		value="{rval klat}" />
		<input type="hidden" name="klon"		value="{rval klon}" />
		<!--{def freeparms}-->
		<!--{each freeparms}-->
		<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
		<!--{/each}-->
		<!--{/def}-->
		<p class="z_pl_fw_title">フリーワードで探す</p>
		<div class="z_litem_freeword">
			<div class="z_litem_freeword_inner">
				<div class="z_freeword_btn_float"><div class="z_freeword_btn_div"><button type="submit">検索</button></div></div>
				<div class="z_freeword_div">
					<input type="text" name="keyword" class="freewordBox" value=""
						<!--{ndef Android_2_1}-->placeholder="{rval D_PL_FW_INIT}"<!--{/ndef}--> />
				</div>
			</div>
		</div>
	</form>
<!--{/def}-->
</section>
