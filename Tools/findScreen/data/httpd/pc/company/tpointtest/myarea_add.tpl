<!-- ���� content ���� --> 
<form name="frmMyareaAdd">
<input type="text" style="position:absolute;visibility:hidden">
<table class="MyAreaAddBox" cellspacing="0">
	<tr>
		<td class="MyAreaAddBox_ttl">
		<img src="{rval D_DIR_COMPANY}images/arrow_orange.gif">
		My���ꥢ���ɲä���
		</td>
	</tr>
	<tr>
		<td class="MyAreaAddBox_msg">My���ꥢ��Ͽ̾</td>
	</tr>
	<tr>
		<td class="MyAreaAddBox_txtb">
			<input type="text" size="33" name="myarea_name_add" id="myarea_name_add" value="" onKeyPress="key_press_myarea_add(event, '{rval prm/p_s2}', '{rval prm/myar}', '{rval prm/lm}', '{rval add_cnt}')">
		</td>
	</tr>
	<tr>
		<td class="MyAreaAddBox_msg">
		������ɬ�ܡ�50ʸ�����⡣
		</td>
	</tr>
	<tr>
		<td class="MyAreaAddBox_btn">
			<input type="button" value="����󥻥�" onClick='cancelMyareaAdd("{rval D_DIR_COMPANY}")'>
			&nbsp;&nbsp;&nbsp;
			<input type="button" value="&nbsp;&nbsp;&nbsp;��Ͽ&nbsp;&nbsp;&nbsp;" onClick="javascript:{rval _jsMyAreaAdd}"><BR>
		</td>
	</tr>
</table>
</form>
<!-- ���� content end ���� -->
