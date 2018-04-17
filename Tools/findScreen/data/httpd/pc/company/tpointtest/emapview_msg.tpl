<div id="fukidashi">
	<div id="fukidashi-name">
		<a href="javascript:{rval _jsDetail};">
		<!--{def col_02}-->
		{rval col_02}<br>
		<!--{/def}-->
		{rval name}
		</a>
	</div>
	<div id="fukidashi-data">
		{rval addr}
	</div>
	<div id="fukidashi-data">
		{rval col_01}
	</div>
	<!--{vdef new}-->
	<div id="fukidashi-data">
		<!--{def test_flg}-->
		<a href="javascript:CouponSite('https://stg.tsite.jp/coupon/index.pl?xpg=PCCP0101');"><img src="https://tsite.jp/pc/img/map/a_coupon.gif"></a>
		<!--{/def}-->
		<!--{ndef test_flg}-->
		<a href="javascript:CouponSite('https://tsite.jp/coupon/index.pl?xpg=PCCP0101');"><img src="https://tsite.jp/pc/img/map/a_coupon.gif"></a>
		<!--{/def}-->
	</div>
	<!--{/vdef}-->
</div>
