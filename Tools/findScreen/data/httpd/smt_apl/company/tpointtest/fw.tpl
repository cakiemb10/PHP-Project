<form name="formFw" method="get" action="fw.htm" onSubmit="{rval _jsFWSubmit}">
	<div class="z_litem_freeword">
		<div class="z_litem_freeword_inner">
			<!--{def filter_list}-->
			<p class="z_srch_fw_list">{rval D_FILTER_TITLE}</p>
			<select name="filter" class="z_sb1">
				<!--{each filter_list}-->
				<option value="{rval filter_list/val}" <!--{def filter_list/selected}-->selected<!--{/def}-->>{rval filter_list/name}</option>
				<!--{/each}-->
			</select>
			<span class="z_down_arrow"></span>
			<!--{/def}-->
			<div class="z_freeword_btn_float">
				<div class="z_freeword_btn_div">
					<button type="submit">検索</button>
				</div>
			</div>
			<div class="z_freeword_div">
				<!--{def html_keyword}-->
				<input type="text" class="freewordBox freewordBox-ent" name="keyword" value="{rval html_keyword}"
					onFocus="{rval _jsFWIn}" onBlur="{rval _jsFWOut}" />
				<!--{/def}-->
				<!--{ndef html_keyword}-->
				<input type="text" class="freewordBox" name="keyword" value="{rval html_FWInit}"
					onFocus="{rval _jsFWIn}" onBlur="{rval _jsFWOut}" />
				<!--{/ndef}-->
				<input type="hidden" name="enc" value="UTF8" />
			</div>
			<div>
				<br><p class="z_filter_title">※複数のキーワードをスペース（空白）で区切って検索することができます。<br>（例：TSUTAYA 渋谷）</p>
			</div>
		</div>
	</div>
</form>

<section>
<div class="z_fw_keyword clearfix">
	<div class="fl">
		<ul>
		<li><img src="{rval D_DIR_COMPANY}img/label-search.png" alt=""><span class="t-result mL10">{rval html_keyword}</span></li>
		</ul>
	</div>
</div>
<div>
	<div id="ZdcEmapSearchShopFwList"></div>
</div>
</section>
