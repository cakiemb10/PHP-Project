<!--<center><font color="red">{rval MAIN_TITLE}</font></center>-->
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">Myエリア</span>
</div>
<!--{def user_id}-->
<?php //ログイン状態 [ ?>

<!--{def myarea_list}-->
<?php //ログイン状態 Myエリアデータ有り [ ?>
<div align="left">
<!--{each myarea_list/data}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">
<a href="../../mobile/{rval corp_id}/s.htm?p=nm&p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myardisp=1&lat={rval myarea_list/data/lat}&lon={rval myarea_list/data/lon}&area_no={rval myarea_list/data/disp_order}">{rval myarea_list/data/myarea_name}</a>
<!--{vdef myarea_list/data/continue_flg}-->
｜
<!--{/vdef}-->
</span>
<!--{/each}-->
</div>
<div align="left" style="padding-top:5px; padding-bottom:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}">#PENCIL#Myエリアの編集・削除</a></span>
</div>
<?php //ログイン状態 Myエリアデータ有り ] ?>
<!--{/def}-->

<!--{ndef myarea_list}-->
<?php //ログイン状態 Myエリアデータ無し [ ?>
<div style="padding-left:5px; padding-right:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">Myｴﾘｱはまだ登録されていません。<br>下の「検索で探す」から、Myｴﾘｱに登録したい場所を検索し、登録いただけます。</span>
</div>
<div align="right" style="padding-top:5px; padding-bottom:5px; padding-right:5px;">
<!--{def test_flg}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="https://stg.tsite.jp/mb/r/map/index.pl?tcm_l={rval p_s3}">Myエリアとは？</a></span>
<!--{/def}-->
<!--{ndef test_flg}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="https://tsite.jp/mb/r/map/index.pl?tcm_l={rval p_s3}">Myエリアとは？</a></span>
<!--{/ndef}-->
</div>
<?php //ログイン状態 Myエリアデータ無し ] ?>
<!--{/ndef}-->

<?php //ログイン状態 ] ?>
<!--{/def}-->

<!--{ndef user_id}-->
<?php //未ログイン状態 [ ?>
<div style="padding-left:5px; padding-right:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">自宅近く、会社・学校の近くなど、最大５か所のｴﾘｱを登録することができます。<br>すでに登録済みの方は、ﾛｸﾞｲﾝしてMyｴﾘｱを表示してください。</span>
</div>
<div align="center" style="padding-top:5px; padding-bottom:5px;">
<!--{def test_flg}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="https://stg.tsite.jp/tm/mb/login/STKIm0003001.do?ST_SITE_ID=4009&MOVE_ID=003">ログイン</a></span>
<!--{/def}-->
<!--{ndef test_flg}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="https://tsite.jp/tm/mb/login/STKIm0003001.do?ST_SITE_ID=4009&MOVE_ID=003">ログイン</a></span>
<!--{/ndef}-->
</div>
<?php //未ログイン状態 ] ?>
<!--{/ndef}-->

<hr>
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">検索で探す</span>
</div>
{rval LOCATE_TITLE}</a>
<!--{def locationopt}-->
<br>
<form method="get" action="{rval ima_form_action}" {rval ima_opt}>
<input type="hidden" name="lm" value="{rval lm_dec}">
<!--{each ima_form/data}-->
<input type="hidden" name="{rval ima_form/data/name}" value="{rval ima_form/data/val}">
<!--{/each}-->
{rval SELECT_TITLE}<br>
<select name="arg1">
<!--{each opt/where}-->
<option value="{rval opt/where/val}">{rval opt/where/name}</option>
<!--{/each}-->
</select><br>
<input type="hidden" name="arg2" value="p=ibf">
<!--{def P_STRING_1}--><input type="hidden" name="p_s1" value="{rval P_STRING_1}"><!--{/def}-->
<!--{def P_STRING_2}--><input type="hidden" name="p_s2" value="{rval P_STRING_2}"><!--{/def}-->
<!--{def P_STRING_3}--><input type="hidden" name="p_s3" value="{rval P_STRING_3}"><!--{/def}-->
<!--{def P_STRING_4}--><input type="hidden" name="p_s4" value="{rval P_STRING_4}"><!--{/def}-->
<!--{def P_STRING_5}--><input type="hidden" name="p_s5" value="{rval P_STRING_5}"><!--{/def}-->
<!--{def P_FLG_1}--><input type="hidden" name="p_f1" value="{rval P_FLG_1}"><!--{/def}-->
<!--{def P_FLG_2}--><input type="hidden" name="p_f2" value="{rval P_FLG_2}"><!--{/def}-->
<!--{def P_FLG_3}--><input type="hidden" name="p_f3" value="{rval P_FLG_3}"><!--{/def}-->
<!--{def P_FLG_4}--><input type="hidden" name="p_f4" value="{rval P_FLG_4}"><!--{/def}-->
<!--{def P_FLG_5}--><input type="hidden" name="p_f5" value="{rval P_FLG_5}"><!--{/def}-->
<input type="submit" name="ok" value="検 索">
</form><BR>
<!--{/def}-->
<!--{def freeword}-->
<a name="keyword"></a>{rval KEYWD_TITLE}<br>
<form method="get" action="{rval form_action}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<!--{def eki-free}--><input type="radio" name="p" value="ef" checked>{rval STFW_TITLE}<br><!--{/def}-->
<!--{def cpn-free}--><input type="radio" name="p" value="cf">{rval CPFW_TITLE}<br><!--{/def}-->
<!--{def add-free}--><input type="radio" name="p" value="af">{rval ADFW_TITLE}<br><!--{/def}-->
<!--{def zip-free}--><input type="radio" name="p" value="zf">{rval ZPFW_TITLE}<br><!--{/def}-->
<input type="text"  name="key" size="20"><br>
※店舗名は複数のキーワードをスペース（空白）で区切って検索することができます。<br>
<!--{def opt}-->
{rval SELECT_TITLE}<br>
<select name="opt">
<!--{each opt/where}-->
<option value="{rval opt/where/val}">{rval opt/where/name}</option>
<!--{/each}-->
</select><br>
<!--{/def}-->
<!--{def P_STRING_1}--><input type="hidden" name="p_s1" value="{rval P_STRING_1}"><!--{/def}-->
<!--{def P_STRING_2}--><input type="hidden" name="p_s2" value="{rval P_STRING_2}"><!--{/def}-->
<!--{def P_STRING_3}--><input type="hidden" name="p_s3" value="{rval P_STRING_3}"><!--{/def}-->
<!--{def P_STRING_4}--><input type="hidden" name="p_s4" value="{rval P_STRING_4}"><!--{/def}-->
<!--{def P_STRING_5}--><input type="hidden" name="p_s5" value="{rval P_STRING_5}"><!--{/def}-->
<!--{def P_FLG_1}--><input type="hidden" name="p_f1" value="{rval P_FLG_1}"><!--{/def}-->
<!--{def P_FLG_2}--><input type="hidden" name="p_f2" value="{rval P_FLG_2}"><!--{/def}-->
<!--{def P_FLG_3}--><input type="hidden" name="p_f3" value="{rval P_FLG_3}"><!--{/def}-->
<!--{def P_FLG_4}--><input type="hidden" name="p_f4" value="{rval P_FLG_4}"><!--{/def}-->
<!--{def P_FLG_5}--><input type="hidden" name="p_f5" value="{rval P_FLG_5}"><!--{/def}-->
<input type="submit" value="検　索">
<!--{/def}-->
</form>
