{rval head_sparater}
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">My���ꥢ</span>
</div>
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">

<!--{def myarea_err_msg}-->
<span style="font-size:120%; color:ff0000;">{rval myarea_err_msg}</span>
<!--{/def}-->

<!--{def name/step1}-->
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="myarea_id" value="{rval name/myarea_id}">
<input type="hidden" name="lat" value="{rval name/lat}">
<input type="hidden" name="lon" value="{rval name/lon}">
<input type="hidden" name="disp_order" value="{rval name/disp_order}">
<input type="hidden" name="myarea_mode" value="myarea_name">
<input type="hidden" name="step" value="2">
������My���؎�̾�����Ϥ��Ƥ���������
<br>
<div align="left">
<input type="text" name="myarea_name" size="40">
</div>
<div align="center">
������ɬ�ܡ�50ʸ������
</div>
<br>
<div align="center">
<input type="submit" value="&nbsp;&nbsp;����&nbsp;&nbsp;">
</div>
</form>
<br>
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<div align="center">
<input type="submit" value="&nbsp;&nbsp;���&nbsp;&nbsp;">
</div>
</form>
<!--{/def}-->

<!--{def name/step2}-->
��Ͽ���Ƥ�����Ǥ�����
<br>
<div align="center">
<span style="font-size:120%;">
My���؎�̾�Ρ�{rval name/myarea_name_disp}
</span>
</div>
<br>
<div align="center">
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="myarea_mode" value="myarea_name">
<input type="hidden" name="myarea_id" value="{rval name/myarea_id}">
<input type="hidden" name="myarea_name" value="{rval name/myarea_name}">
<input type="hidden" name="lat" value="{rval name/lat}">
<input type="hidden" name="lon" value="{rval name/lon}">
<input type="hidden" name="disp_order" value="{rval name/disp_order}">
<input type="hidden" name="step" value="3">
<input type="submit" value="��Ͽ��λ">
</form>
<br>
<form action="../../mobile/{rval corp_id}/myarea.htm">
<input type="hidden" name="p_s2" value="{rval user_id_dec}">
<input type="hidden" name="p_s3" value="{rval p_s3_dec}">
<input type="hidden" name="lm" value="{rval lm_dec}">
<input type="hidden" name="myarea_mode" value="myarea_name">
<input type="hidden" name="myarea_id" value="{rval name/myarea_id}">
<input type="hidden" name="lat" value="{rval name/lat}">
<input type="hidden" name="lon" value="{rval name/lon}">
<input type="hidden" name="disp_order" value="{rval name/disp_order}">
<input type="hidden" name="step" value="1">
<input type="submit" value="&nbsp;&nbsp;���&nbsp;&nbsp;">
</form>
</div>
<!--{/def}-->

<!--{ndef myarea_err_msg}-->
<!--{def name/step3}-->
��Ͽ��λ�פ��ޤ�����
<br>
<div align="center">
<span style="font-size:120%;">
<a href="../../mobile/{rval corp_id}/s.htm?p=nm&p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myardisp=1&lat={rval name/lat}&lon={rval name/lon}&area_no={rval name/disp_order}">My���؎����Ͽޤ򸫤�</a>
</span>
</div>

<!--{/def}-->
<!--{/ndef}-->
</span>

{rval foot_sparater}
