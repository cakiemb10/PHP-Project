{rval midashi}
{rval head_sparater}
<!--{def COL_02}-->
@COL_02@<BR>
<!--{/def}-->
@NAME@<BR>
<!--{def ADDR}-->
■住所<BR>
@ADDR@<BR>
<!--{/def}-->
<!--{def COL_01}-->
■電話番号<BR>
@COL_01@<BR>
<!--{/def}-->
<BR>
<!--{def new}-->
<hr>
<!--{def test_flg}-->
<a href="https://stg.tsite.jp/mb/coupon/index.pl?xpg=MBCP0101&tcm_l={rval p_s3}">#TICKET#ｸｰﾎﾟﾝを見る</a>
<!--{/def}-->
<!--{ndef test_flg}-->
<a href="https://tsite.jp/mb/coupon/index.pl?xpg=MBCP0101&tcm_l={rval p_s3}">#TICKET#ｸｰﾎﾟﾝを見る</a>
<!--{/ndef}-->
<hr>
<!--{/def}-->
<a href="{rval mapurl}">#EYE#{rval TOMAPNAME}</a>
<BR>
<a href='mailto:?subject=T-SITE MOBILE&body={rval mailurl}'>#MAIL_TO#この地図をﾒｰﾙで送る</a>
{rval foot_sparater}
