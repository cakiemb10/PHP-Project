<center><font color="red">{rval SSROUTE_TITLE}</font></center>
<hr>
<!--{def freeword}-->
{rval SSROUTE_KEYWD_TITLE}<br>
<form method="get" action="{rval form_action}">
<!--{def add-free}--><input type="radio" name="p" value="af" checked>{rval ADFW_TITLE}<br><!--{/def}-->
<!--{def zip-free}--><input type="radio" name="p" value="zf">{rval ZPFW_TITLE}<br><!--{/def}-->
<input type="text"  name="key" size="10"><br>
<input type="hidden" name="ssr" value="{rval ssr}">
<input type="hidden" name="spos" value="{rval spos}">
<input type="hidden" name="id" value="{rval id}">
<!--{def srch_opt}--><input type=hidden name=opt value="{rval srch_opt}"><!--{/def}-->
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
<input type="submit" value="¸¡¡¡º÷">
<!--{/def}-->
</form>
