<section>
<div class="z_fw_keyword clearfix">
	<div class="fl">
		<ul>
		<li><img src="{rval D_DIR_COMPANY}img/label-search.png" alt=""><span class="t-result mL10">{rval html_keyword}</span></li>
		</ul>
	</div>
</div>
<div class="z_fw_tab_div">
	<ul id="z_fw_tab_ul">
		<li><a id="ZdcEmapSearchFWTab1" onClick="{rval _jsTabClick1}"
			<!--{def init_view1}-->class="on"<!--{/def}-->>±Ø<span>({rval count1}·ï)</span></a></li>
		<li><a id="ZdcEmapSearchFWTab2" onClick="{rval _jsTabClick2}"
			<!--{def init_view2}-->class="on"<!--{/def}-->>½»½ê<span>({rval count2}·ï)</span></a></li>
	</ul>
	<div style="position:relative;">
		<div id="ZdcEmapSearchFWList1" class="z_srch_fw_list"
			<!--{ndef init_view1}-->style="display:none;"<!--{/def}-->></div>
		<div id="ZdcEmapSearchFWList2" class="z_srch_fw_list"
			<!--{ndef init_view2}-->style="display:none;"<!--{/def}-->></div>
	</div>
</div>
</section>
