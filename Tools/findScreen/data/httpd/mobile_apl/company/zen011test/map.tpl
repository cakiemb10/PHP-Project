{rval midashi}
{rval head_sparater}
<center><form action="{rval zoomaction}" method=get>
<!--{def listdata}--><!--{def list_midashi}-->{rval list_midashi}<br><!--{/def}--><!--{def errmsg}-->{rval errmsg}<br><!--{/def}--><!--{/def}--><!--{def MAP_DTL_TITLE}-->{rval MAP_DTL_TITLE}<BR><!--{/def}-->
<img src="{rval mapurl}" alt="ÃÏ¿Þ"><BR>
<!--{def mapzoom}-->
<input type=hidden name=p value=zoom>
<input type=hidden name=id value={rval id}>
<!--{def nm}--><input type=hidden name=nm value="{rval nm}"><!--{/def}-->
<!--{def bl}--><input type=hidden name=bl value={rval bl}><!--{/def}-->
<!--{def ssr}--><input type=hidden name=ssr value={rval ssr}><!--{/def}-->
<!--{def spos}--><input type=hidden name=spos value={rval spos}><!--{/def}-->
<!--{def srch_opt}--><input type=hidden name=opt value="{rval srch_opt}"><!--{/def}-->
<!--{def optcd}--><input type="hidden" name="optcd" value="{rval optcd}"><!--{/def}-->
<!--{def P_STRING_1}--><input type=hidden name=p_s1 value="{rval P_STRING_1}"><!--{/def}-->
<!--{def P_STRING_2}--><input type=hidden name=p_s2 value="{rval P_STRING_2}"><!--{/def}-->
<!--{def P_STRING_3}--><input type=hidden name=p_s3 value="{rval P_STRING_3}"><!--{/def}-->
<!--{def P_STRING_4}--><input type=hidden name=p_s4 value="{rval P_STRING_4}"><!--{/def}-->
<!--{def P_STRING_5}--><input type=hidden name=p_s5 value="{rval P_STRING_5}"><!--{/def}-->
<!--{def P_STRING_6}--><input type=hidden name=p_s6 value="{rval P_STRING_6}"><!--{/def}-->
<!--{def P_STRING_7}--><input type=hidden name=p_s7 value="{rval P_STRING_7}"><!--{/def}-->
<!--{def P_STRING_8}--><input type=hidden name=p_s8 value="{rval P_STRING_8}"><!--{/def}-->
<!--{def P_STRING_9}--><input type=hidden name=p_s9 value="{rval P_STRING_9}"><!--{/def}-->
<!--{def P_STRING_10}--><input type=hidden name=p_s10 value="{rval P_STRING_10}"><!--{/def}-->
<!--{def P_FLG_1}--><input type=hidden name=p_f1 value="{rval P_FLG_1}"><!--{/def}-->
<!--{def P_FLG_2}--><input type=hidden name=p_f2 value="{rval P_FLG_2}"><!--{/def}-->
<!--{def P_FLG_3}--><input type=hidden name=p_f3 value="{rval P_FLG_3}"><!--{/def}-->
<!--{def P_FLG_4}--><input type=hidden name=p_f4 value="{rval P_FLG_4}"><!--{/def}-->
<!--{def P_FLG_5}--><input type=hidden name=p_f5 value="{rval P_FLG_5}"><!--{/def}-->
<!--{def P_FLG_6}--><input type=hidden name=p_f6 value="{rval P_FLG_6}"><!--{/def}-->
<!--{def P_FLG_7}--><input type=hidden name=p_f7 value="{rval P_FLG_7}"><!--{/def}-->
<!--{def P_FLG_8}--><input type=hidden name=p_f8 value="{rval P_FLG_8}"><!--{/def}-->
<!--{def P_FLG_9}--><input type=hidden name=p_f9 value="{rval P_FLG_9}"><!--{/def}-->
<!--{def P_FLG_10}--><input type=hidden name=p_f10 value="{rval P_FLG_10}"><!--{/def}-->
<select name=pos>
<!--{each mapzoom/data}-->
<option value="{rval mapzoom/data/val}"{rval mapzoom/data/sel}>{rval mapzoom/data/name}</option>
<!--{/each}-->
</select>
<input type=submit value="ÊÑ¹¹">
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
<a href="{rval zoomstart}">{rval ZOOM_S_TITLE}</a><BR><!--{def SmartPhone}--><BR><!--{/def}-->
<a href="{rval zoomgoal}">{rval ZOOM_E_TITLE}</a><BR><!--{def SmartPhone}--><BR><!--{/def}-->
<a href="{rval zoomall}">{rval ZOOM_A_TITLE}</a><BR><!--{def SmartPhone}--><BR><!--{/def}-->
<!--{/def}-->
<!--{def function}-->
<!--{def detailurl}--><a href="{rval detailurl}">{rval DETAIL_TITLE}</a><BR><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def nstation}--><a href="{rval nstation}">{rval NEAR_TITLE}</a><BR><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def nstationr}--><a href="{rval nstationr}">{rval NSROUTE_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def routesearch}--><a href="{rval routesearch}" {rval ima_opt}>{rval ROUTE_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def ssroutesearch}--><a href="{rval ssroutesearch}">{rval SSROUTE_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<BR>
<!--{def detailpos}--><a href="{rval detailpos}">{rval DETAIL_POS_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{ndef SmartPhone}-->
<!--{def tobigacc}-->#NO5#<a href="{rval tobig}" {rval tobigacc}><!--{/def}-->{rval ZOOMIN_TITLE}<!--{def tobigacc}--></a><!--{/def}--><!--{def tosmallacc}-->¡¿#NO0#<a href="{rval tosmall}" {rval tosmallacc}><!--{/def}-->{rval ZOOMOUT_TITLE}<!--{def tosmallacc}--></a><!--{/def}--><BR>
<a href="{rval move1}" {rval move1acc}>#NO1#</a><a href="{rval move2}" {rval move2acc}>#NO2#</a><a href="{rval move3}" {rval move3acc}>#NO3#</a><BR>
<a href="{rval move4}" {rval move4acc}>#NO4#</a>{rval centerimg}<a href="{rval move6}" {rval move6acc}>#NO6#</a><BR>
<a href="{rval move7}" {rval move7acc}>#NO7#</a><a href="{rval move8}" {rval move8acc}>#NO8#</a><a href="{rval move9}" {rval move9acc}>#NO9#</a><BR>
<!--{/ndef}-->
<!--{def SmartPhone}-->
<!--{def tobigacc}--><a href="{rval tobig}" {rval tobigacc}><!--{/def}-->{rval ZOOMIN_TITLE}<!--{def tobigacc}--></a><!--{/def}--><!--{def tosmallacc}-->¡¿<a href="{rval tosmall}" {rval tosmallacc}><!--{/def}-->{rval ZOOMOUT_TITLE}<!--{def tosmallacc}--></a><!--{/def}--><BR>
<BR>
<a href="{rval move1}" {rval move1acc}>#NO1#</a>¡¡<a href="{rval move2}" {rval move2acc}>¢¬</a>¡¡<a href="{rval move3}" {rval move3acc}>#NO3#</a><BR>
<BR>
<a href="{rval move4}" {rval move4acc}>¢«</a>¡¡{rval centerimg}¡¡<a href="{rval move6}" {rval move6acc}>¢ª</a><BR>
<BR>
<a href="{rval move7}" {rval move7acc}>#NO7#</a>¡¡<a href="{rval move8}" {rval move8acc}>¢­</a>¡¡<a href="{rval move9}" {rval move9acc}>#NO9#</a><BR>
<BR>
<!--{/def}-->
<!--{def HELP_TITLE}--><a href="{rval movehelp}">{rval HELP_TITLE}</a><BR><!--{/def}-->
<!--{/def}-->
</center>
<!--{def listdata}-->
<!--{def SmartPhone}--><BR><!--{/def}-->
<!--{each listdata/data}-->
<!--{ndef SmartPhone}-->{rval listdata/data/icon_no}<!--{/ndef}-->
<!--{def SmartPhone}-->{rval listdata/data/no}&nbsp;<!--{/def}-->
<a href="{rval listdata/data/url}" {rval listdata/data/access_key}>{rval listdata/data/name}</a><!--{def listdata/data/rosen}-->{rval listdata/data/rosen}<!--{/def}--><br>
<!--{def SmartPhone}--><BR><!--{/def}-->
<!--{/each}-->
<!--{def page}-->{rval icon_pre}<A href = "{rval pre_link}">{rval pre_name}</a><!--{/def}-->
<!--{def page}-->{rval separator}<!--{/def}-->
<!--{def page}-->{rval icon_next}<A href = "{rval next_link}">{rval next_name}</a><!--{/def}-->
<!--{/def}-->
{rval foot_sparater}</form>
