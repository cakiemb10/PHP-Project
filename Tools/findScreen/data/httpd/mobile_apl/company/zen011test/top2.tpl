<hr>
<!--{def main}-->
	<!--{def location}--><a {rval acc_key_location} href="{rval tp_ima_href}" {rval tp_ima_opt}>{rval icn_location}{rval LOCATE_TITLE}</a><br><!--{/def}-->
	<!--{def arealist}--><a {rval acc_key_arealist} href="{rval tp_cpnt_href}">{rval icn_arealist}{rval AREA_TITLE}</a><br><!--{/def}-->
	<!--{def addrlist}--><a {rval acc_key_addrlist} href="{rval tp_addr_href}">{rval icn_addrlist}{rval ADRLST_TITLE}</a><br><!--{/def}-->
	<!--{def freeword}--><a {rval acc_key_freeword} href="{rval tp_key_href}">{rval icn_freeword}{rval KEYWD_TITLE}</a><br><!--{/def}-->
<!--{/def}-->

<!--{def TP5}--><!-- �����ϸ��� -->
<form method="get" action="{rval tp_n_action}" name="form_npos">
	<a name="cpnt"></a>{rval icn_location}{rval LOCATE_TITLE}<br><br>
	<input type="hidden" name="pos" value="{rval tp_n_pos}">
<!--{/def}-->
<!--{def TP2}--><!-- �������ꥢ���� -->
<form method="get" action="{rval cpnt_href}">
	<a name="cpnt"></a>{rval icn_arealist}{rval AREA_TITLE}<br>
	<input type="hidden" name="p" value="cl">
<!--{/def}-->
<!--{def TP3}--><!-- ����ꥹ�ȸ��� -->
<form method="get" action="{rval addr_href}">
	<a name="addr"></a>{rval icn_addrlist}{rval ADRLST_TITLE}<br>
	<input type="hidden" name="p" value="al">
<!--{/def}-->
<!--{def TP4}--><!-- ������ɸ��� -->
<form method="get" action="{rval form_action}">
	<a name="keyword"></a>{rval icn_freeword}{rval KEYWD_TITLE}<br>
	<!--{def cpn-free}--><input type="radio" name="p" value="cf" checked>{rval CPFW_TITLE}<br><!--{/def}-->
	<!--{def add-free}--><input type="radio" name="p" value="af">{rval ADFW_TITLE}<br><!--{/def}-->
	<!--{def eki-free}--><input type="radio" name="p" value="ef">{rval STFW_TITLE}<br><!--{/def}-->
	<!--{def zip-free}--><input type="radio" name="p" value="zf">{rval ZPFW_TITLE}<br><!--{/def}-->
	<input type="text"  name="key" size="16"><br>
	<input type="hidden" name="col" value="col_113">
<!--{/def}-->
<!--{ndef main}-->
	<input type="submit" value="������"><br>
	<!--{def checkboxopt}-->
		<br>
		&lt;�����ˎގ���õ��&gt;<br>
		<input type="checkbox" name="K1" value="1">�Ďގ؎ݎ�<br>
		<input type="checkbox" name="K3" value="1">�Îގ��ގ���<br>
		<input type="submit" value="������"><hr>
		<input type="checkbox" name="M1" value="1">�ر�<br>
		<input type="checkbox" name="M2" value="1">ʬ��<br>
		<input type="checkbox" name="M3" value="1">����ʬ��<br>
		<input type="checkbox" name="K12" value="1">�Î��̎ގ��ʤ���<br>
		<input type="checkbox" name="K13" value="1">�͎ގˎގ�������<br>
		<input type="checkbox" name="K14" value="1">¿��Ū�Ď���<br>
		<input type="checkbox" name="K15" value="1">���ێ��̎�/���ڎ͎ގ�����<br>
		<input type="checkbox" name="K17" value="1">��־�<br>
		<input type="checkbox" name="K18" value="1">�Ďގ׎��̎ގ��َ�<br>
		<input type="checkbox" name="K19" value="1">���ڎ��ގ��Ď����Ď����Ѳ�<br>
		<input type="checkbox" name="K21" value="1">���̷��Żҥޥ͡�<br>
		<input type="checkbox" name="K22" value="1">Edy���Ѳ�<br>
		<input type="checkbox" name="K23" value="1">iD���Ѳ�<br>
		<input type="checkbox" name="K24" value="1">QUICPay���Ѳ�<br>
		<input type="checkbox" name="K20" value="1">ZENSHO CooCa�谷Ź<br>
		<input type="submit" value="������"><br>
	<!--{/def}-->
</form>
<!--{/ndef}-->
