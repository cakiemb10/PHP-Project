{rval head_sparater}
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">My���ꥢ���Խ������</span>
</div>
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">

<!--{def myarea_err_msg}-->
<span style="font-size:120%; color:ff0000;">{rval myarea_err_msg}</span>
<!--{/def}-->

<span style="padding-left:3px;">����Ͽ�Ѥ�My���؎���̾���ѹ��Ⱥ��</span>
<!--{each myarea_list/data}-->
<div style="padding-top:5px; padding-left:5px;">
<span style="font-size:115%; color:d8adf0;">��</span>
{rval myarea_list/data/myarea_name}
<a href="../../mobile/{rval corp_id}/s.htm?p=nm&p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myardisp=1&lat={rval myarea_list/data/lat}&lon={rval myarea_list/data/lon}&area_no={rval myarea_list/data/disp_order}">���Ͽ�ɽ����</a>
<BR>
&nbsp;<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=myarea_name&myarea_id={rval myarea_list/data/myarea_id}&lat={rval myarea_list/data/lat}&lon={rval myarea_list/data/lon}&disp_order={rval myarea_list/data/disp_order}&step=1">�ѹ�</a>��
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=myarea_del&myarea_id={rval myarea_list/data/myarea_id}&myarea_name={rval myarea_list/data/myarea_name_enc}&step=1">���</a>&nbsp;
����ѹ���
<!--{def myarea_list/data/disp_order_prev}-->
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=disp_order&myarea_id={rval myarea_list/data/myarea_id}&disp_order={rval myarea_list/data/disp_order_prev}">��</a>
<!--{/def}-->
<!--{ndef myarea_list/data/disp_order_prev}-->
��
<!--{/ndef}-->
<!--{def myarea_list/data/disp_order_next}-->
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=disp_order&myarea_id={rval myarea_list/data/myarea_id}&disp_order={rval myarea_list/data/disp_order_next}">��</a>
<!--{/def}-->
<!--{ndef myarea_list/data/disp_order_next}-->
��
<!--{/ndef}-->
��
</div>
<!--{/each}-->
</span>
<div style="padding-top:10px; padding-left:5px; padding-right:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">
����Ͽ�Ѥ�My���؎��ΰ��֤��ѹ����������ϡ��������؎�����ٺ�����Ƥ���������
���θ塢��<u>��������õ��</u>�פ���Ͽޤ�ɽ��������������My���؎����ɲä��Ƥ���������
<BR>��My���؎��򿷤����ɲä��������ϡ�<u>��������õ��</u>�פ����Ͽ�������Ͽޤ�ɽ���������ɲä��Ƥ���������<BR>
</span>
</div>

{rval foot_sparater}
