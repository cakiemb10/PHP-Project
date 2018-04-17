<hr>
<!--{def main}-->
	<!--{def location}--><a {rval acc_key_location} href="{rval tp_ima_href}" {rval tp_ima_opt}>{rval icn_location}{rval LOCATE_TITLE}</a><br><!--{/def}-->
	<!--{def arealist}--><a {rval acc_key_arealist} href="{rval tp_cpnt_href}">{rval icn_arealist}{rval AREA_TITLE}</a><br><!--{/def}-->
	<!--{def addrlist}--><a {rval acc_key_addrlist} href="{rval tp_addr_href}">{rval icn_addrlist}{rval ADRLST_TITLE}</a><br><!--{/def}-->
	<!--{def freeword}--><a {rval acc_key_freeword} href="{rval tp_key_href}">{rval icn_freeword}{rval KEYWD_TITLE}</a><br><!--{/def}-->
<!--{/def}-->

<!--{def TP5}--><!-- 現在地検索 -->
<form method="get" action="{rval tp_n_action}" name="form_npos">
	<a name="cpnt"></a>{rval icn_location}{rval LOCATE_TITLE}<br><br>
	<input type="hidden" name="pos" value="{rval tp_n_pos}">
<!--{/def}-->
<!--{def TP2}--><!-- 拠点エリア検索 -->
<form method="get" action="{rval cpnt_href}">
	<a name="cpnt"></a>{rval icn_arealist}{rval AREA_TITLE}<br>
	<input type="hidden" name="p" value="cl">
<!--{/def}-->
<!--{def TP3}--><!-- 住所リスト検索 -->
<form method="get" action="{rval addr_href}">
	<a name="addr"></a>{rval icn_addrlist}{rval ADRLST_TITLE}<br>
	<input type="hidden" name="p" value="al">
<!--{/def}-->
<!--{def TP4}--><!-- キーワード検索 -->
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
	<input type="submit" value="検　索"><br>
	<!--{def checkboxopt}-->
		<br>
		&lt;ｻｰﾋﾞｽで探す&gt;<br>
		<input type="checkbox" name="K1" value="1">ﾄﾞﾘﾝｸ<br>
		<input type="checkbox" name="K3" value="1">ﾃﾞｻﾞｰﾄ<br>
		<input type="submit" value="検　索"><hr>
		<input type="checkbox" name="M1" value="1">禁煙<br>
		<input type="checkbox" name="M2" value="1">分煙<br>
		<input type="checkbox" name="M3" value="1">完全分煙<br>
		<input type="checkbox" name="K12" value="1">ﾃｰﾌﾞﾙ席あり<br>
		<input type="checkbox" name="K13" value="1">ﾍﾞﾋﾞｰｼｰﾄ<br>
		<input type="checkbox" name="K14" value="1">多目的ﾄｲﾚ<br>
		<input type="checkbox" name="K15" value="1">ｽﾛｰﾌﾟ/ｴﾚﾍﾞｰﾀｰ<br>
		<input type="checkbox" name="K17" value="1">駐車場<br>
		<input type="checkbox" name="K18" value="1">ﾄﾞﾗｲﾌﾞｽﾙｰ<br>
		<input type="checkbox" name="K19" value="1">ｸﾚｼﾞｯﾄｶｰﾄﾞ利用可<br>
		<input type="checkbox" name="K21" value="1">交通系電子マネー<br>
		<input type="checkbox" name="K22" value="1">Edy利用可<br>
		<input type="checkbox" name="K23" value="1">iD利用可<br>
		<input type="checkbox" name="K24" value="1">QUICPay利用可<br>
		<input type="checkbox" name="K20" value="1">ZENSHO CooCa取扱店<br>
		<input type="submit" value="検　索"><br>
	<!--{/def}-->
</form>
<!--{/ndef}-->
