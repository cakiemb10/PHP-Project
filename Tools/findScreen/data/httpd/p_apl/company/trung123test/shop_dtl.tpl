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
					<th>����</th>
					<td class="kyotenDtlData">
						{rval addr}
					</td>
				</tr>
				<!--{/def}-->

				<tr>
					<th>
						������URL
					</th>
					<td align="left">
						<input value="{rval mobileurl}" id="kyotenDtlMobileUrl" type="text" readonly><br>
						<div class="kyotenDtlMobileLink">
							<a href="mailto:?body={rval mobileurl_encode}">
								<img src="{rval D_DIR_COMPANY}images/mailto_mobile_tp.gif" id="kyotenDtlMLinkIcon">
									���Ӥ�����</a>
						</div>
						<img class="kyotenDtlQR" src="{rval qrimgurl}" alt="" height="82" width="82">
					</td>
				</tr>
				
				
				
				<tr>
					<td colspan="2" class="kyotenDtlFunc">
						<a href="javascript:{rval _jsNeki};">
							<img src="{rval D_DIR_COMPANY}images/btn_neki.gif" alt="�Ǵ��ؤ�ɽ��" title="�Ǵ��ؤ�ɽ��" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>�Ǵ���</a>
						&nbsp;
						<a href="javascript:{rval _jsDetailNpoi}">
							<img src="{rval D_DIR_COMPANY}images/btn_npoi.gif" alt="���ջ��ߤ�ɽ��" width="33" height="30" title="���ջ��ߤ�ɽ��" class="kyotenDtlFuncIcon"/>���ջ���</a>
						&nbsp;
						<a href="{rval _urlPrint}" target="_new">
							<img src="{rval D_DIR_COMPANY}images/btn_print.gif" alt="����{rval D_USER_DEFNAME}��������" title="����{rval D_USER_DEFNAME}��������" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>����</a>
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
			�Ͽޱ�������</a>
	</div>
	<div id="ZdcEmapCond"></div>
</div>
