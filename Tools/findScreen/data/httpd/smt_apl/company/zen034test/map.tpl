<!-- //���֥��顼 -->
<!--{ndef col_04l8}-->

<script type="text/JavaScript">
<!--
//-->
</script>
<center>
<br><br>
<font color="black"><b>
���ꤵ�줿Ź�ޤ�¸�ߤ��ޤ���
</b></font>
<br><br>
<a href="javascript:window.history.back();" style="text-decoration:underline;color:#0000ee;">���</a>
</center>


<!--{/ndef}-->


<!-- //������ե饰 -->
<!--{def col_04l8}-->
<!--{ndef col_02b}-->

<script type="text/JavaScript">
<!--
//-->
</script>
<center>
<br><br>
<font color="black"><b>
���ꤵ�줿Ź�ޤ�¸�ߤ��ޤ���
</b></font>
<br><br>
<a href="javascript:window.history.back();" style="text-decoration:underline;color:#0000ee;">���</a>
</center>

<!--{/ndef}-->
<!--{/def}-->


<!--{def col_04l8}-->
<!--{def col_02b}-->


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

<!--{def D_LOC_ROUTE_TYPE}-->
<form action="javascript:{rval _jsLocRoute}" class="z_map_btn_locroute">
	<input type="submit" value="�����Ϥ���롼�Ȱ���">
</form>
<!--{/def}-->
<!--{def D_SEARCH_ROUTE_TYPE}-->
<form action="{rval _urlSearchRoute}" class="z_map_btn_searchroute" method="get">
	<input type="hidden" name="kid" value="{rval kid}">
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<input type="submit" value="��ȯ�ϻ��ꤷ�ƥ롼�Ȱ���">
</form>
<!--{/def}-->
<!--{def D_SRCH_NPOI}-->
<form action="{rval _urlNpoi}" class="z_map_btn_npoi" method="get">
	<input type="hidden" name="kid" value="{rval kid}">
	<input type="hidden" name="lat" value="{rval lat}">
	<input type="hidden" name="lon" value="{rval lon}">
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<input type="submit" value="�Ǵ�����">
</form>
<!--{/def}-->
<!--{def D_SRCH_NEKI}-->
<form action="{rval _urlNeki}" class="z_map_btn_neki" method="get">
	<input type="hidden" name="kid" value="{rval kid}">
	<input type="hidden" name="lat" value="{rval lat}">
	<input type="hidden" name="lon" value="{rval lon}">
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<input type="submit" value="�Ǵ���">
</form>
<!--{/def}-->
<form action="{rval D_URL_SEARCH_TOP}" class="z_map_btn_top">
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<input type="submit" value="����TOP��">
</form>
<form action="javascript:{rval _jsResetMapLocation}" class="z_map_btn_reset">
	<input type="submit" value="���ΰ��֤�">
</form>
<form action="{rval _urlShopInf}" method="get" class="z_map_btn_inf">
	<!--{def freeparms}-->
	<!--{each freeparms}-->
	<input type="hidden" name="{rval freeparms/name}"	value="{rval freeparms/val}" />
	<!--{/each}-->
	<!--{/def}-->
	<input type="submit" value="Ź�ޤξ���">
</form>
<div id="ZdcEmapMap" class="map"></div>

<!--{/def}-->
<!--{/def}-->
