<div id="kyotenHd">
	<table id="custKyotenHdTable">
		<tr>
			<th>
				<img src="{rval iconimg}">
			</th>
			<td>
				<a href="javascript:{rval _jsScroll}">
				<!--{def col_02}-->
				{rval col_02}<br>
				<!--{/def}-->
				{rval name}
				</a>
			</td>
		</tr>
	</table>
</div>
<div id="kyotenDtl">
	<table id="kyotenDtlTable">
		<!--{def gifflg}-->
		<tr>
			<td colspan="2" class="kyotenDtlImgTd">
				<img src="{rval gifimg}" alt="{rval name}" id="kyotenDtlImg"/></td>
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
		<!--{def col_01}-->
		<tr>
			<th>�����ֹ�</th>
			<td class="kyotenDtlData">
				{rval col_01}
			</td>
		</tr>
		<!--{/def}-->
		<!--{vdef new}-->
		<tr>
			<td colspan="2" class="kyotenDtlCouponData">
				<!--{def test_flg}-->
				<a href="javascript:CouponSite('https://stg.tsite.jp/coupon/index.pl?xpg=PCCP0101');" OnMouseOver="CouponImgChangeMouseOver();" OnMouseOut="CouponImgChangeMouseOut();"><img src="https://tsite.jp/pc/img/map/b_coupon.jpg" name="couponImg"></a>
				<!--{/def}-->
				<!--{ndef test_flg}-->
				<a href="javascript:CouponSite('https://tsite.jp/coupon/index.pl?xpg=PCCP0101');" OnMouseOver="CouponImgChangeMouseOver();" OnMouseOut="CouponImgChangeMouseOut();"><img src="https://tsite.jp/pc/img/map/b_coupon.jpg" name="couponImg"></a>
				<!--{/def}-->
			</td>
		</tr>
		<!--{/vdef}-->

		
		
		<tr>
			<td colspan="2" class="kyotenDtlFunc">
				<a href="javascript:{rval _jsNeki};">
					<img src="{rval D_DIR_COMPANY}images/btn_neki.gif" alt="�Ǵ��ؤ�ɽ��" title="�Ǵ��ؤ�ɽ��" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>�Ǵ���</a>
				&nbsp;
				<a href="{rval _urlPrint}" target="_new">
					<img src="{rval D_DIR_COMPANY}images/btn_print.gif" alt="����{rval D_USER_DEFNAME}��������" title="����{rval D_USER_DEFNAME}��������" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>����</a>
			</td>
		</tr>
	</table>
</div>