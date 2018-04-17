<!--{ndef scale_type}-->
	<!--{def map_lvl}-->
	<select id="ZdcEmapLvlSelect" class="z_map_lvl_select" onChange="{rval _jsLvlSelectChanged};">
	<!--{each map_lvl}-->
	<option value="{rval map_lvl/lvl}">{rval map_lvl/txt}</option>
	<!--{/each}-->
	</select>
	<!--{/def}-->
<!--{/ndef}-->
<!--{def scale_type}-->
	<select id="ZdcEmapLvlSelect" class="z_map_lvl_select" style="display:none;"></select>
	<a href="javascript:{rval _jsLvlScaleChangedPls};">
		<img src="{rval D_DIR_COMPANY}img/btn_plus_def.png" name="btn_plus" class="z_map_lvl_scaleP" id="ZdcEmapLvlBtnP" />
	</a>
	<a href="javascript:{rval _jsLvlScaleChangedMin};">
		<img src="{rval D_DIR_COMPANY}img/btn_minus_def.png" name="btn_minus" class="z_map_lvl_scaleM" id="ZdcEmapLvlBtnM" />
	</a>
<!--{/def}-->

<form action="{rval D_URL_SEARCH_TOP}" class="z_map_btn_top">
<input type="hidden" name="pltype"		value="{rval html_pltype}" />
<input type="hidden" name="plname"		value="{rval html_plname}" />
<input type="hidden" name="lat"			value="{rval html_lat}" />
<input type="hidden" name="lon"			value="{rval html_lon}" />
<input type="hidden" name="plfilter"	value="{rval html_plfilter}" />
<input type="submit" value="検索TOPへ">
</form>

<form action="javascript:{rval _jsResetMapLocation}" class="z_map_btn_reset">
<input type="submit" value="元の位置へ">
</form>

<form action="{rval _urlNearShop}" method="get" class="z_map_btn_nlist">
<input type="hidden" name="pltype"		value="{rval html_pltype}" />
<input type="hidden" name="plname"		value="{rval html_plname}" />
<input type="hidden" name="lat"			value="{rval html_lat}" />
<input type="hidden" name="lon"			value="{rval html_lon}" />
<input type="hidden" name="plfilter"	value="{rval html_plfilter}" />
<input type="submit" value="{rval D_SHOP_NAME}一覧">
</form>

<div id="ZdcEmapWait">
	<div style="position:relative;">
		<img id="ZdcEmapWait-bgimg" src="{rval D_DIR_BASE}img/load-back.png" />
		<img id="ZdcEmapWait-animg" src="{rval D_DIR_BASE}img/load.gif" />
		<div id="ZdcEmapWait-text">{rval D_WAIT_MSG}</div>
	</div>
</div>

<div id="ZdcEmapMap" class="map"></div>

<div align="right" id="ZdcEmapCond">
	<select id="ZdcEmapCondSelect" class="z_map_cond_select" onChange="javascript:ZdcEmapCondChange();" style="font-size:75%;width:100%;">
	<!--{each filter_list}-->
	<option value="{rval filter_list/val}" <!--{def filter_list/pl_selected}-->selected<!--{/def}-->>{rval filter_list/name}</option>
	<!--{/each}-->
	</select>
</div>
