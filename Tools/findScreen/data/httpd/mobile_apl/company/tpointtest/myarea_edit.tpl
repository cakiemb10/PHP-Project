{rval head_sparater}
<div align="center" style="background-color:eaeaea; margin-top:5px; margin-bottom:5px; padding-top:3px;">
<span style="font-size:110%; color:0f228c; font-weight:bold;">Myエリアの編集・削除</span>
</div>
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">

<!--{def myarea_err_msg}-->
<span style="font-size:120%; color:ff0000;">{rval myarea_err_msg}</span>
<!--{/def}-->

<span style="padding-left:3px;">■登録済みMyｴﾘｱの名称変更と削除</span>
<!--{each myarea_list/data}-->
<div style="padding-top:5px; padding-left:5px;">
<span style="font-size:115%; color:d8adf0;">◇</span>
{rval myarea_list/data/myarea_name}
<a href="../../mobile/{rval corp_id}/s.htm?p=nm&p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myardisp=1&lat={rval myarea_list/data/lat}&lon={rval myarea_list/data/lon}&area_no={rval myarea_list/data/disp_order}">（地図表示）</a>
<BR>
&nbsp;<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=myarea_name&myarea_id={rval myarea_list/data/myarea_id}&lat={rval myarea_list/data/lat}&lon={rval myarea_list/data/lon}&disp_order={rval myarea_list/data/disp_order}&step=1">変更</a>｜
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=myarea_del&myarea_id={rval myarea_list/data/myarea_id}&myarea_name={rval myarea_list/data/myarea_name_enc}&step=1">削除</a>&nbsp;
順序変更【
<!--{def myarea_list/data/disp_order_prev}-->
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=disp_order&myarea_id={rval myarea_list/data/myarea_id}&disp_order={rval myarea_list/data/disp_order_prev}">↑</a>
<!--{/def}-->
<!--{ndef myarea_list/data/disp_order_prev}-->
↑
<!--{/ndef}-->
<!--{def myarea_list/data/disp_order_next}-->
<a href="../../mobile/{rval corp_id}/myarea.htm?p_s2={rval user_id}&p_s3={rval p_s3}&lm={rval lm}&myarea_mode=disp_order&myarea_id={rval myarea_list/data/myarea_id}&disp_order={rval myarea_list/data/disp_order_next}">↓</a>
<!--{/def}-->
<!--{ndef myarea_list/data/disp_order_next}-->
↓
<!--{/ndef}-->
】
</div>
<!--{/each}-->
</span>
<div style="padding-top:10px; padding-left:5px; padding-right:5px;">
<span style="font-size:75%; font-weight:bold; font-family:sans-serif;">
※登録済みMyｴﾘｱの位置を変更したい場合は、該当ｴﾘｱを一度削除してください。
その後、「<u>検索から探す</u>」より地図を表示させ、新たにMyｴﾘｱを追加してください。
<BR>※Myｴﾘｱを新たに追加したい場合は「<u>検索から探す</u>」より登録したい地図を表示させ、追加してください。<BR>
</span>
</div>

{rval foot_sparater}
