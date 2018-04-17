<section>
<!--{def pltype1}-->
	<div class="z_litem">
		<a href="{rval _urlLocation}"><span class="z_litem_name">現在地取得(GPS)</span>
			<span id="ZdcEmapLocCmmt" class="z_pl_loc_msg">&nbsp;現在地を取得するには<br>&nbsp;&nbsp;こちらをタップしてください。</span><span class="z_icon_blank"></span>
		</a>
	</div>
<!--{/def}-->
<!--{def pltype2}-->
	<div class="z_litem">
		<a href="{rval _urlAddrL}"><span class="z_litem_name">住所リストから選択</span>
			<span class="z_icon_arrow"></span>
		</a>
	</div>
	<!--{def D_SEARCH_AVAILABLE}-->
	<form name="formFw" method="get" action="{rval _urlFw}" onSubmit="{rval _jsFWSubmit}">
	<input type="hidden" name="enc"			value="UTF8" />
	<input type="hidden" name="pltype"		value="{rval html_pltype}" />
	<input type="hidden" name="plname"		value="{rval html_plname}" />
	<input type="hidden" name="lat"			value="{rval html_lat}" />
	<input type="hidden" name="lon"			value="{rval html_lon}" />
	<input type="hidden" name="plfilter"	value="{rval html_plfilter}" />
	<p class="z_pl_fw_title">フリーワードで探す<br>（駅名・住所・郵便番号）</p>
	<div class="z_litem_freeword">
		<div class="z_litem_freeword_inner">
			<div class="z_freeword_btn_float"><div class="z_freeword_btn_div"><button type="submit">検索</button></div></div>
			<div class="z_freeword_div">
				<input type="text" name="keyword" class="freewordBox" value="{rval html_FWInit}"
					onFocus="{rval _jsFWIn}" onBlur="{rval _jsFWOut}" />
			</div>
		</div>
	</div>
	</form>
	<!--{/def}-->
<!--{/def}-->
</section>
