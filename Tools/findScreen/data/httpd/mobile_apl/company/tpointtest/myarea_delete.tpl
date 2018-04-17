{rval head_sparater}
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">Myエリア</span>
</div>
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">

<!--{def myarea_err_msg}-->
<span style="font-size:120%; color:ff0000;">{rval myarea_err_msg}</span>
<!--{/def}-->

<!--{def del/step1}-->
削除してよろしいですか？
<br>
<div align="center">
<span style="font-size:120%;">
Myｴﾘｱ名称：{rval del/myarea_name}
</span>
</div>
<br>
<div align="center">
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="myarea_id" value="{rval del/myarea_id}">
<input type="hidden" name="myarea_name" value="{rval del/myarea_name}">
<input type="hidden" name="myarea_mode" value="myarea_del">
<input type="hidden" name="step" value="2">
<input type="submit" value="削除する">
</form>
<br>
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="submit" value="&nbsp;ｷｬﾝｾﾙ&nbsp;">
</form>
</div>
<!--{/def}-->

<!--{ndef myarea_err_msg}-->
<!--{def del/step2}-->
削除完了しました。
<br>
<div align="center">
<span style="font-size:120%;">
<a href="{rval search_top}&bkl=1">お店検索ﾄｯﾌﾟに戻る</a>
</span>
</div>

<!--{/def}-->
<!--{/ndef}-->

{rval foot_sparater}
