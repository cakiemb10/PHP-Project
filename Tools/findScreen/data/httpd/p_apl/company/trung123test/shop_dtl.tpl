<div id="rightArea">
	<div id="ZdcEmapDetail" style="line-height:0;">
		<div id="kyotenHd">
			<a href="javascript:{rval _jsScroll}">
			{rval name}
			</a>
		</div>
		<div id="kyotenDtl">
			<input type="hidden" name="ZdcEmapShopNameEnc" id="ZdcEmapShopNameEnc" value="{rval name_enc}">
			<table id="kyotenDtlTable">
				<!--{def gifflg}-->
				<tr>
					<td colspan="2" class="kyotenDtlImgTd">
						<img src="{rval gifimg}" alt="{rval name}" id="kyotenDtlImg"/></td>
				</tr>
				<!--{/def}-->
				<!--{def mltflg1}-->
				<tr>
					<td colspan="2" class="kyotenDtlImgTd">
						<img src="{rval mltimg1}" alt="{rval mltname1}" class="kyotenDtlImgMulti"/></td>
				</tr>
				<!--{/def}-->

				<!--{def addr}-->
				<tr>
					<th>交疥</th>
					<td class="kyotenDtlData">
						{rval addr}
					</td>
				</tr>
				<!--{/def}-->

				<tr>
					<th>
						啡掠脱URL
					</th>
					<td align="left">
						<input value="{rval mobileurl}" id="kyotenDtlMobileUrl" type="text" readonly><br>
						<div class="kyotenDtlMobileLink">
							<a href="mailto:?body={rval mobileurl_encode}">
								<img src="{rval D_DIR_COMPANY}images/mailto_mobile_tp.gif" id="kyotenDtlMLinkIcon">
									啡掠に流慨</a>
						</div>
						<img class="kyotenDtlQR" src="{rval qrimgurl}" alt="" height="82" width="82">
					</td>
				</tr>
				
				
				
				<tr>
					<td colspan="2" class="kyotenDtlFunc">
						<a href="javascript:{rval _jsNeki};">
							<img src="{rval D_DIR_COMPANY}images/btn_neki.gif" alt="呵大り必を山绩" title="呵大り必を山绩" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>呵大り必</a>
						&nbsp;
						<a href="javascript:{rval _jsDetailNpoi}">
							<img src="{rval D_DIR_COMPANY}images/btn_npoi.gif" alt="件收卉肋を山绩" width="33" height="30" title="件收卉肋を山绩" class="kyotenDtlFuncIcon"/>件收卉肋</a>
						&nbsp;
						<a href="{rval _urlPrint}" target="_new">
							<img src="{rval D_DIR_COMPANY}images/btn_print.gif" alt="この{rval D_USER_DEFNAME}攫鼠を磅湖" title="この{rval D_USER_DEFNAME}攫鼠を磅湖" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>磅湖</a>
					</td>
				</tr>
			</table>
		</div>
	</div>
	<div id="ZdcEmapList"></div>
</div>
<div id="leftArea">
	<div id="ZdcEmapMap" style="width:450px;height:450px;"></div>
	<div id="mapRuleLink">
		<a href="{rval D_DIR_BASE}kiyaku/map_rule.htm" target="_blank"
		onClick="window.open('{rval D_DIR_BASE}kiyaku/map_rule.htm', '',
		'width=600,height=600,resizable,scrollbars,menubar=no'); return false;">
			孟哭避枉惮腆</a>
	</div>
	<div id="ZdcEmapCond"></div>
</div>
