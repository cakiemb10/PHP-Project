<section>
<form name="formPl" method="get" action="{rval _urlPl}">
	<input type="hidden" name="enc"		value="UTF8" />
	<input type="hidden" name="pltype"	value="1" />
	<input type="hidden" name="plname"	value="{rval html_plname}" />
	<input type="hidden" name="lat"		value="{rval html_lat}" />
	<input type="hidden" name="lon"		value="{rval html_lon}" />
	<input type="hidden" name="datum"	value="{rval html_datum}" />
	<input type="hidden" name="plfilter"	value="{rval html_plfilter}" />
	<div class="z_srch_title_pad">
		<div class="z_srch_title_div">
		�����Ϥ���õ��
		</div>
	</div>
	<div class="z_top_pl">
		<!--{def filter_list}-->
		<p class="z_filter_title">{rval D_FILTER_TITLE}</p>
		<select name="plfilter" class="z_sb1">
			<!--{each filter_list}-->
			<option value="{rval filter_list/val}" <!--{def filter_list/pl_selected}-->selected<!--{/def}-->>{rval filter_list/name}</option>
			<!--{/each}-->
		</select>
		<span class="z_down_arrow"></span>
		<!--{/def}-->
	</div>
	<div class="z_top_btn_srch_pl">
		<button type="submit">�����ϼ�����GPS��</button>
	</div>
</form>
<form name="formN" method="get" action="{rval _urlPl}">
	<input type="hidden" name="enc"		value="UTF8" />
	<input type="hidden" name="pltype"	value="2" />
	<input type="hidden" name="plname"	value="{rval html_plname}" />
	<input type="hidden" name="lat"		value="{rval html_lat}" />
	<input type="hidden" name="lon"		value="{rval html_lon}" />
	<input type="hidden" name="datum"	value="{rval html_datum}" />
	<div class="z_srch_title_pad">
		<div class="z_srch_title_div">
		������ꤷ��õ��
		</div>
	</div>
	<div class="z_top_pl">
		<!--{def filter_list}-->
		<p class="z_filter_title">{rval D_FILTER_TITLE}</p>
		<select name="plfilter" class="z_sb1">
			<!--{each filter_list}-->
			<option value="{rval filter_list/val}" <!--{def filter_list/pl_selected}-->selected<!--{/def}-->>{rval filter_list/name}</option>
			<!--{/each}-->
		</select>
		<span class="z_down_arrow"></span>
		<!--{/def}-->
	</div>
	<div class="z_top_btn_srch_pl">
		<button type="submit">������ꤹ��</button>
	</div>
</form>
<form name="formFw" method="get" action="fw.htm" onSubmit="{rval _jsFWSubmit}">
	<div class="z_srch_title_pad">
		<div class="z_srch_title_div">
		Ź�޾��󤫤�õ��
		</div>
	</div>
	<div class="z_litem_freeword">
		<div class="z_litem_freeword_inner_top">
			<!--{def filter_list}-->
			<p class="z_filter_title">{rval D_FILTER_TITLE}</p>
			<select name="filter" class="z_sb1">
				<!--{each filter_list}-->
				<option value="{rval filter_list/val}">{rval filter_list/name}</option>
				<!--{/each}-->
			</select>
			<span class="z_down_arrow"></span>
			<!--{/def}-->
			<div class="z_freeword_btn_float">
				<div class="z_freeword_btn_div">
					<button type="submit">����</button>
				</div>
			</div>
			<div class="z_freeword_div">
				<input type="text" class="freewordBox" name="keyword" value="{rval html_FWInit}" onFocus="{rval _jsFWIn}" onBlur="{rval _jsFWOut}"/> 
				<input type="hidden" name="enc" value="UTF8" />
			</div>
			<div>
				<br><p class="z_filter_title">��ʣ���Υ�����ɤ򥹥ڡ����ʶ���ˤǶ��ڤäƸ������뤳�Ȥ��Ǥ��ޤ���<br>���㡧TSUTAYA ��ë��</p>
			</div>
		</div>
	</div>
</form>
</section>
