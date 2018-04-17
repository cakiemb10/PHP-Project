<section>
<span class="z_cond_panel_btn_icon_cache"></span>
	<div class="z_litem">
		<a href="javascript:{rval _jsLocNList}" style="padding-left:0;"><span class="z_litem_name" style="padding-left:14px;">現在地取得(GPS)</span>
			<span id="ZdcEmapLocCmmt" class="z_pl_loc_msg"></span><span class="z_icon_blank"></span>
		</a>
	</div>

<!--{def D_SEARCH_AVAILABLE}-->
<form name="formPl" method="get" action="{rval _urlPlFw}" onSubmit="{rval _jsPlFWSubmit}">
	<input type="hidden" name="enc" value="UTF8" />
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<p class="z_pl_fw_title">キーワードから検索</p>
	<div class="z_litem_freeword">
		<div class="z_litem_freeword_inner_top">
			<div class="z_freeword_btn_float">
				<div class="z_freeword_btn_div">
					<button type="submit">検索</button>
				</div>
			</div>
			<div class="z_freeword_div">
				<input type="text" name="keyword" class="freewordBox"
					<!--{ndef Android_2_1}-->placeholder="{rval html_PlFWInit}"<!--{/ndef}--> /> 
			</div>
		</div>
	</div>
</form>
<!--{/def}-->

<form name="formFw" method="get" action="fw.htm" onSubmit="{rval _jsFWSubmit}">
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<p class="z_pl_fw_title">店舗名から検索</p>
	<div class="z_litem_freeword">
		<div class="z_litem_freeword_inner_top">
			<div class="z_freeword_btn_float">
				<div class="z_freeword_btn_div">
					<button type="submit">検索</button>
				</div>
			</div>
			<div class="z_freeword_div">
				<input type="text" class="freewordBox" name="keyword1"
					<!--{ndef Android_2_1}-->placeholder="{rval html_FWInit}"<!--{/ndef}--> /> 
				<input type="hidden" name="enc" value="UTF8" />
			</div>
		</div>
	</div>
</form>

<form name="formL1" method="get" action="{rval _urlShopList}">
	<input type="hidden" name="ltype" value="1" />
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<div class="cust_item_area">
		<div class="z_litem_freeword_inner_top">
			<div class="z_freeword_btn_float">
				<div class="z_freeword_btn_div">
					<button type="submit">検索</button>
				</div>
			</div>
			<p class="cust_area_title">都道府県から探す</p>
		</div>
	</div>
</form>
</section>
