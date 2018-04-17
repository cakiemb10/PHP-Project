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
			<th>住所</th>
			<td class="kyotenDtlData">
				{rval addr}
			</td>
		</tr>
		<!--{/def}-->
		<!--{def col_01}-->
		<tr>
			<th>電話番号</th>
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
					<img src="{rval D_DIR_COMPANY}images/btn_neki.gif" alt="最寄り駅を表示" title="最寄り駅を表示" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>最寄り駅</a>
				&nbsp;
				<a href="{rval _urlPrint}" target="_new">
					<img src="{rval D_DIR_COMPANY}images/btn_print.gif" alt="この{rval D_USER_DEFNAME}情報を印刷" title="この{rval D_USER_DEFNAME}情報を印刷" align="middle" height="30" width="33" class="kyotenDtlFuncIcon"/>印刷</a>
			</td>
		</tr>
	</table>
</div>