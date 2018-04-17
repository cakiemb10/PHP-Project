{rval head_sparater}
<center><form action="{rval zoomaction}" method=get>
<!--{def kyoten_list}-->
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

<!--{def myarea_list/data/disp_flg}-->
<span style="color:ff5555;">{rval myarea_list/data/myarea_name}</span>
<!--{/def}-->
<!--{ndef myarea_list/data/disp_flg}-->
<a href="../../mobile/{rval corp_id}/s.htm?p=nm&p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myardisp=1&lat={rval myarea_list/data/lat}&lon={rval myarea_list/data/lon}&area_no={rval myarea_list/data/disp_order}">{rval myarea_list/data/myarea_name}</a>
<!--{/ndef}-->

<!--{vdef myarea_list/data/continue_flg}-->
｜
<!--{/vdef}-->
</span>
<!--{/each}-->
</div>
<div align="left" style="padding-top:5px; padding-bottom:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&lm={rval lm}&p_s3={rval p_s3}">#PENCIL#Myエリアの編集・削除</a>
<!--{ndef myardisp}-->
<!--{ndef cntmax}-->
<BR>
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&lat={rval pos/lat}&lon={rval pos/lon}&myarea_mode=myarea_add&cntnext={rval cntnext}&step=1">#FACE_SMILE#検索結果をMyエリアに追加</a></span>
<!--{/ndef}-->
<!--{/ndef}-->
</div>
<?php //ログイン状態 Myエリアデータ有り ] ?>
<!--{/def}-->

<!--{ndef myarea_list}-->
<?php //ログイン状態 Myエリアデータ無し [ ?>
<div align="left" style="padding-top:5px; padding-bottom:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">Myｴﾘｱはまだ登録されていません。
<!--{ndef myardisp}-->
<BR>
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&lat={rval pos/lat}&lon={rval pos/lon}&myarea_mode=myarea_add&step=1">#FACE_SMILE#検索結果をMyエリアに追加</a></span>
<!--{/ndef}-->
</span>
</div>
<?php //ログイン状態 Myエリアデータ無し ] ?>
<!--{/ndef}-->

<?php //ログイン状態 ] ?>
<!--{/def}-->

<!--{ndef user_id}-->
<?php //未ログイン状態 [ ?>
<div align="left" style="padding-top:5px; padding-bottom:5px;">
<!--{def test_flg}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="https://stg.tsite.jp/tm/mb/login/STKIm0003001.do?ST_SITE_ID=4009&MOVE_ID=004&DYNAMIC_URL={rval pos/enc_latlon}">#FACE_SMILE#検索結果をMyエリアに追加</a></span>
<!--{/def}-->
<!--{ndef test_flg}-->
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;"><a href="https://tsite.jp/tm/mb/login/STKIm0003001.do?ST_SITE_ID=4009&MOVE_ID=004&DYNAMIC_URL={rval pos/enc_latlon}">#FACE_SMILE#検索結果をMyエリアに追加</a></span>
<!--{/ndef}-->
</div>
<?php //未ログイン状態 ] ?>
<!--{/ndef}-->
<hr>
<!--{/def}-->

<!--{def listdata}--><!--{def list_midashi}-->{rval list_midashi}<br><!--{/def}--><!--{def errmsg}-->{rval errmsg}<br><!--{/def}--><!--{/def}--><!--{def MAP_DTL_TITLE}-->{rval MAP_DTL_TITLE}<BR><!--{/def}-->
<img src="{rval mapurl}" alt="地図"><BR>
<!--{def mapzoom}-->
<input type=hidden name=p value=zoom>
<input type=hidden name=id value={rval id}>
<!--{def nm}--><input type=hidden name=nm value="{rval nm}"><!--{/def}-->
<!--{def bl}--><input type=hidden name=bl value={rval bl}><!--{/def}-->
<!--{def ssr}--><input type=hidden name=ssr value={rval ssr}><!--{/def}-->
<!--{def spos}--><input type=hidden name=spos value={rval spos}><!--{/def}-->
<!--{def srch_opt}--><input type=hidden name=opt value="{rval srch_opt}"><!--{/def}-->
<!--{def P_STRING_1}--><input type=hidden name=p_s1 value="{rval P_STRING_1}"><!--{/def}-->
<!--{def P_STRING_2}--><input type=hidden name=p_s2 value="{rval P_STRING_2}"><!--{/def}-->
<!--{def P_STRING_3}--><input type=hidden name=p_s3 value="{rval P_STRING_3}"><!--{/def}-->
<!--{def P_STRING_4}--><input type=hidden name=p_s4 value="{rval P_STRING_4}"><!--{/def}-->
<!--{def P_STRING_5}--><input type=hidden name=p_s5 value="{rval P_STRING_5}"><!--{/def}-->
<!--{def P_FLG_1}--><input type=hidden name=p_f1 value="{rval P_FLG_1}"><!--{/def}-->
<!--{def P_FLG_2}--><input type=hidden name=p_f2 value="{rval P_FLG_2}"><!--{/def}-->
<!--{def P_FLG_3}--><input type=hidden name=p_f3 value="{rval P_FLG_3}"><!--{/def}-->
<!--{def P_FLG_4}--><input type=hidden name=p_f4 value="{rval P_FLG_4}"><!--{/def}-->
<!--{def P_FLG_5}--><input type=hidden name=p_f5 value="{rval P_FLG_5}"><!--{/def}-->
<!--{def lm}--><input type=hidden name=lm value="{rval lm}"><!--{/def}-->
<select name=pos>
<!--{each mapzoom/data}-->
<option value="{rval mapzoom/data/val}"{rval mapzoom/data/sel}>{rval mapzoom/data/name}</option>
<!--{/each}-->
</select>
<input type=submit value="変更">
<!--{def maddr}-->
<br><!--{def maddr_head}-->{rval maddr_head} <!--{/def}-->{rval maddr}<!--{def maddr_tail}--> {rval maddr_tail}<!--{/def}--><input type=hidden name=maddr value={rval maddr}>
<!--{def maddr_ex}-->
<br>{rval maddr_ex}
<!--{/def}-->
<!--{/def}-->
<!--{def addrstr}-->
<br>{rval addrstr}
<!--{/def}-->
<HR>
<!--{/def}-->
<!--{def routemode}-->
<a href="{rval zoomstart}">{rval ZOOM_S_TITLE}</a><BR>
<a href="{rval zoomgoal}">{rval ZOOM_E_TITLE}</a><BR>
<a href="{rval zoomall}">{rval ZOOM_A_TITLE}</a><BR>
<!--{/def}-->
<!--{def function}-->
<!--{def detailurl}--><a href="{rval detailurl}">{rval DETAIL_TITLE}</a><BR><!--{/def}-->
<!--{def nstation}--><a href="{rval nstation}">{rval NEAR_TITLE}</a><BR><!--{/def}-->
<!--{def nstationr}--><a href="{rval nstationr}" {rval ima_opt}>{rval NSROUTE_TITLE}</a><br><!--{/def}-->
<!--{def routesearch}--><a href="{rval routesearch}" {rval ima_opt}>{rval ROUTE_TITLE}</a><br><!--{/def}-->
<!--{def ssroutesearch}--><a href="{rval ssroutesearch}">{rval SSROUTE_TITLE}</a><br><!--{/def}-->
<BR>
<!--{def detailpos}--><a href="{rval detailpos}">{rval DETAIL_POS_TITLE}</a><br><!--{/def}-->
#NO5#<!--{def tobigacc}--><a href="{rval tobig}" {rval tobigacc}><!--{/def}-->{rval ZOOMIN_TITLE}<!--{def tobigacc}--></a><!--{/def}-->／#NO0#<!--{def tosmallacc}--><a href="{rval tosmall}" {rval tosmallacc}><!--{/def}-->{rval ZOOMOUT_TITLE}<!--{def tosmallacc}--></a><!--{/def}--><BR>
<a href="{rval move1}" {rval move1acc}>#NO1#</a><a href="{rval move2}" {rval move2acc}>#NO2#</a><a href="{rval move3}" {rval move3acc}>#NO3#</a><BR>
<a href="{rval move4}" {rval move4acc}>#NO4#</a>{rval centerimg}<a href="{rval move6}" {rval move6acc}>#NO6#</a><BR>
<a href="{rval move7}" {rval move7acc}>#NO7#</a><a href="{rval move8}" {rval move8acc}>#NO8#</a><a href="{rval move9}" {rval move9acc}>#NO9#</a><BR>
<!--{def HELP_TITLE}--><a href="{rval movehelp}">{rval HELP_TITLE}</a><BR><!--{/def}-->
<!--{/def}-->
</center>
<!--{def listdata}-->
<!--{each listdata/data}-->
{rval listdata/data/icon_no}<!--{def listdata/data/COL_02}--><a href="{rval listdata/data/url}" {rval listdata/data/access_key}>{rval listdata/data/COL_02}<br></a>&nbsp;&nbsp;<!--{/def}-->
<a href="{rval listdata/data/url}" {rval listdata/data/access_key}>{rval listdata/data/name}</a><!--{def listdata/data/rosen}-->{rval listdata/data/rosen}<!--{/def}--><br>
<!--{def listdata/data/new}-->
<!--{def test_flg}-->
&nbsp;&nbsp;<a href="https://stg.tsite.jp/mb/coupon/index.pl?xpg=MBCP0101&tcm_l={rval p_s3}">#TICKET#ｸｰﾎﾟﾝを見る</a><BR>
<!--{/def}-->
<!--{ndef test_flg}-->
&nbsp;&nbsp;<a href="https://tsite.jp/mb/coupon/index.pl?xpg=MBCP0101&tcm_l={rval p_s3}">#TICKET#ｸｰﾎﾟﾝを見る</a><BR>
<!--{/ndef}-->
<!--{/def}-->
<!--{def showcolonmapl}-->
<!--{def listdata/data/COL_02}-->{rval listdata/data/COL_02}<BR><!--{/def}-->
<!--{def listdata/data/ADDR}-->{rval listdata/data/ADDR}<BR><!--{/def}-->
<!--{def listdata/data/COL_01}-->{rval listdata/data/COL_01}<BR><!--{/def}-->
<!--{def listdata/data/COL_04}-->{rval listdata/data/COL_04}<BR><!--{/def}-->
<!--{/def}-->
<!--{/each}-->
<!--{def page}-->{rval icon_pre}<A href = "{rval pre_link}">{rval pre_name}</a><!--{/def}-->
<!--{def page}-->{rval separator}<!--{/def}-->
<!--{def page}-->{rval icon_next}<A href = "{rval next_link}">{rval next_name}</a><!--{/def}-->
<!--{/def}-->
<BR>
<!--{def mailurl}-->
<a href='mailto:?subject=T-SITE MOBILE&body={rval mailurl}'>#MAIL_TO#この地図をﾒｰﾙで送る</a>
<!--{/def}-->
{rval foot_sparater}</form>
