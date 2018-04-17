<br>
<center><font color="red">{rval MAIN_TITLE}</font></center>
<hr>
{rval SEARCH_TITLE}<br>
<!--{def location}-->{rval icn_location}<a {rval acc_key_location} href="{rval ima_href}" {rval ima_opt}>{rval LOCATE_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def arealist}-->{rval icn_arealist}<a {rval acc_key_arealist} href="{rval cpnt_href}">{rval AREA_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!-- エリア検索２〜５を使用する場合に有効にしてください（ここから）
<!--{def arealist_2}-->{rval icn_arealist_2}<a {rval acc_key_arealist_2} href="{rval cpnt_href}&areaptn=2">{rval AREA_TITLE_2}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def arealist_3}-->{rval icn_arealist_3}<a {rval acc_key_arealist_3} href="{rval cpnt_href}&areaptn=3">{rval AREA_TITLE_3}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def arealist_4}-->{rval icn_arealist_4}<a {rval acc_key_arealist_4} href="{rval cpnt_href}&areaptn=4">{rval AREA_TITLE_4}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def arealist_5}-->{rval icn_arealist_5}<a {rval acc_key_arealist_5} href="{rval cpnt_href}&areaptn=5">{rval AREA_TITLE_5}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
エリア検索２〜５を使用する場合に有効にしてください（ここまで） -->
<!--{def addrlist}-->{rval icn_addrlist}<a {rval acc_key_addrlist} href="{rval addr_href}">{rval ADRLST_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def freeword}-->{rval icn_freeword}<!--{def normal}--><a name="keyword"></a><!--{/def}--><a {rval acc_key_freeword} href="#keyword">{rval KEYWD_TITLE}</a><br><!--{def SmartPhone}--><BR><!--{/def}--><!--{/def}-->
<!--{def locationopt}-->
<br>
<form method="get" action="{rval ima_form_action}" {rval ima_opt}>
<!--{each ima_form/data}-->
<input type="hidden" name="{rval ima_form/data/name}" value="{rval ima_form/data/val}">
<!--{/each}-->
<a name="area"></a>{rval LOCATE_TITLE}<br>
{rval OPT_TITLE}<br>
<select name="arg1">
<!--{each opt/where}-->
<option value="{rval opt/where/val}">{rval opt/where/name}</option>
<!--{/each}-->
</select><br>
<input type="hidden" name="arg2" value="p=ibf">
<!--{def optcd}--><input type="hidden" name="optcd" value="{rval optcd}"><!--{/def}-->
<!--{def P_STRING_1}--><input type="hidden" name="p_s1" value="{rval P_STRING_1}"><!--{/def}-->
<!--{def P_STRING_10}--><input type="hidden" name="p_s10" value="{rval P_STRING_10}"><!--{/def}-->
<!--{def P_FLG_1}--><input type="hidden" name="p_f1" value="{rval P_FLG_1}"><!--{/def}-->
<input type="submit" name="ok" value="検 索">
</form><BR>
<!--{/def}-->
<!--{def freeword}-->
<a name="keyword"></a>{rval KEYWD_TITLE}<br>
<form method="get" action="{rval form_action}">
<!--{def eki-free}--><input type="radio" name="p" value="ef" checked>{rval STFW_TITLE}<br><!--{/def}-->
<!--{def cpn-free}--><input type="radio" name="p" value="cf">{rval CPFW_TITLE}<br><!--{/def}-->
<!--{def add-free}--><input type="radio" name="p" value="af">{rval ADFW_TITLE}<br><!--{/def}-->
<!--{def zip-free}--><input type="radio" name="p" value="zf">{rval ZPFW_TITLE}<br><!--{/def}-->
<input type="text"  name="key" size="10"><br>
<!--{def opt}-->
<select name="opt">
<!--{each opt/where}-->
<option value="{rval opt/where/val}">{rval opt/where/name}</option>
<!--{/each}--></select><br>
<!--{/def}-->
<!--{def optcd}--><input type="hidden" name="optcd" value="{rval optcd}"><!--{/def}-->
<!--{def P_STRING_1}--><input type="hidden" name="p_s1" value="{rval P_STRING_1}"><!--{/def}-->
<!--{def P_FLG_1}--><input type="hidden" name="p_f1" value="{rval P_FLG_1}"><!--{/def}-->
<input type="submit" value="検　索">
<!--{/def}-->
</form>
