<HR>
<!--{def test_flg}-->
<a href="https://stg.tsite.jp/mb/tmap/info.pl?p_s2={rval p_s2}&p_s3={rval p_s3}&lm={rval lm}">#HINT#ｻｰﾋﾞｽについて</a>
<!--{/def}-->
<!--{ndef test_flg}-->
<a href="https://tsite.jp/mb/tmap/info.pl?p_s2={rval p_s2}&p_s3={rval p_s3}&lm={rval lm}">#HINT#ｻｰﾋﾞｽについて</a>
<!--{/ndef}-->
<br>
<!--{def test_flg}-->
<a href="https://stg.tsite.jp/mb/tmap/agreement.pl?p_s2={rval p_s2}&p_s3={rval p_s3}&lm={rval lm}">#EXC#免責事項</a>
<!--{/def}-->
<!--{ndef test_flg}-->
<a href="https://tsite.jp/mb/tmap/agreement.pl?p_s2={rval p_s2}&p_s3={rval p_s3}&lm={rval lm}">#EXC#免責事項</a>
<!--{/ndef}-->
<HR>
<!--{def ssr_top}--><!--{def SSRTOPTXT}-->#RETURN#<a href="{rval ssr_top}">{rval SSRTOPTXT}</a><br><!--{/def}--><!--{/def}-->
<!--{def search_top}--><!--{def TOPTXT}-->#RETURN#<a href="{rval search_top}&bkl=1">{rval TOPTXT}</a><br><!--{/def}--><!--{/def}-->
<!--{def test_flg}-->
<a href="https://stg.tsite.jp/tm/mb/login/STKIm0005001.do?TLSC={rval p_s2}&LM={rval lm}&ST_SITE_ID=4009">TOP</a><br>
<!--{/def}-->
<!--{ndef test_flg}-->
<a href="https://tsite.jp/tm/mb/login/STKIm0005001.do?TLSC={rval p_s2}&LM={rval lm}&ST_SITE_ID=4009">TOP</a><br>
<!--{/ndef}-->
<!--{def test_flg}-->
<a href="http://stg.m.my.tsite.jp/MyPage/MyPageSelf?tcm_l={rval p_s3}">ﾏｲﾍﾟｰｼﾞ</a><br>
<!--{/def}-->
<!--{ndef test_flg}-->
<a href="http://m.my.tsite.jp/MyPage/MyPageSelf?tcm_l={rval p_s3}">ﾏｲﾍﾟｰｼﾞ</a><br>
<!--{/ndef}-->
<!--{def COPYTXT}--><center>{rval COPYTXT}</center><br><!--{/def}-->
<!--{def ZDC_COPYRIGHT}--><a href="{rval ZDC_COPYRIGHT}">(C)ZenrinDataCom/Zenrin</a><!--{/def}-->
</body></html>
