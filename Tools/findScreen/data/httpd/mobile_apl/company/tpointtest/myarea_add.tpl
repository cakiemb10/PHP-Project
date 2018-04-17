{rval head_sparater}
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">Myエリア</span>
</div>
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">

<!--{def myarea_err_msg}-->
<span style="font-size:120%; color:ff0000;">{rval myarea_err_msg}</span>
<!--{/def}-->

<!--{def add/step1}-->
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="lat" value="{rval add/lat}">
<input type="hidden" name="lon" value="{rval add/lon}">
<input type="hidden" name="myarea_mode" value="myarea_add">
<input type="hidden" name="cntnext" value="{rval add/cntnext}">
<input type="hidden" name="step" value="2">
登録名を入力してください。
<br>
<div align="left">
<input type="text" name="myarea_name" size="40">
</div>
<div align="center">
※入力必須、50文字以内
</div>
<br>
<div align="center">
<input type="submit" value="&nbsp;&nbsp;次へ&nbsp;&nbsp;">
</div>
</form>
<br>
<form action="../../mobile/{rval corp_id}/s.htm">
<input type="hidden" name="p" value="nm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="lat" value="{rval add/lat}">
<input type="hidden" name="lon" value="{rval add/lon}">
<div align="center">
<input type="submit" value="&nbsp;&nbsp;戻る&nbsp;&nbsp;">
</div>
</form>
<!--{/def}-->

<!--{def add/step2}-->
登録してよろしいですか？
<br>
<div align="center">
<span style="font-size:120%;">
Myｴﾘｱ名称：{rval add/myarea_name_disp}
</span>
</div>
<br>
<div align="center">
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="myarea_mode" value="myarea_add">
<input type="hidden" name="myarea_id" value="{rval add/myarea_id}">
<input type="hidden" name="myarea_name" value="{rval add/myarea_name}">
<input type="hidden" name="lat" value="{rval add/lat}">
<input type="hidden" name="lon" value="{rval add/lon}">
<input type="hidden" name="cntnext" value="{rval add/cntnext}">
<input type="hidden" name="step" value="3">
<input type="submit" value="登録完了">
</form>
<br>
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="myarea_mode" value="myarea_add">
<input type="hidden" name="myarea_id" value="{rval add/myarea_id}">
<input type="hidden" name="lat" value="{rval add/lat}">
<input type="hidden" name="lon" value="{rval add/lon}">
<input type="hidden" name="disp_order" value="{rval add/disp_order}">
<input type="hidden" name="step" value="1">
<input type="submit" value="&nbsp;&nbsp;戻る&nbsp;&nbsp;">
</form>
</div>
<!--{/def}-->

<!--{ndef myarea_err_msg}-->
<!--{def add/step3}-->
登録完了致しました。
<br>
<div align="center">
<span style="font-size:120%;">
<a href="../../mobile/{rval corp_id}/s.htm?p=nm&p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myardisp=1&lat={rval add/lat}&lon={rval add/lon}&area_no={rval add/cntnext}">Myｴﾘｱの地図を見る</a>
</span>
</div>

<!--{/def}-->
<!--{/ndef}-->
</span>

{rval foot_sparater}
