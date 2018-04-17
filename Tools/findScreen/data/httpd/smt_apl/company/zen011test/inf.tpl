<!-- //業態エラー -->
<!--{ndef col_04l11}-->

<script type="text/JavaScript">
<!--
document.getElementById("header").style.display="none";
//-->
</script>
<center>
<br><br>
<font color="black"><b>
指定された店舗は存在しません
</b></font>
<br><br>
<a href="javascript:window.history.back();" style="text-decoration:underline;color:#0000ee;">戻る</a>
</center>


<!--{/ndef}-->


<!-- //非公開フラグ -->
<!--{def col_04l11}-->
<!--{ndef col_02b}-->

<script type="text/JavaScript">
<!--
document.getElementById("header").style.display="none";
//-->
</script>
<center>
<br><br>
<font color="black"><b>
指定された店舗は存在しません
</b></font>
<br><br>
<a href="javascript:window.history.back();" style="text-decoration:underline;color:#0000ee;">戻る</a>
</center>

<!--{/ndef}-->
<!--{/def}-->


<!--{def col_04l11}-->
<!--{def col_02b}-->

<section>

<div class="z_inf_name">
<ul>
<li><span class="t-result font-4">
	{rval name}</span></li>
</ul>
</div>
<!--{def addr}-->
<div class="z_litem"><a href="{rval _jsShopMap}"><span class="z_inf_col_title">住所</span>
	<span class="z_litem_comment"><!--{def col_07}-->〒{rval col_07}&nbsp;<!--{/def}-->{rval addr}</span><span class="cust_map_link">地図で表示</span></a></div>
<!--{/def}-->
<!--{def col_08}-->
<div class="z_litem"><a href="tel:{rval col_08}"><span class="z_inf_col_title">電話番号</span><span class="z_litem_comment">{rval col_08}</span><span class="z_litem_phone"><span class="z_icon_phone"></span></span></a></div>
<!--{/def}-->
<!--{def col_09}-->
<div class="z_litem"><p><span class="z_inf_col_title">URL</span><span class="z_litem_comment"><a href="{rval col_09}" style="border:0;font-size:100%;text-decoration:underline;" target="_blank">{rval col_09}</a></span></p></div>
<!--{/def}-->
<div class="z_litem"><p><span class="z_litem_comment">
	<!--{def col_26b}-->
	<img src="{rval _cgiSysIconimg}026" alt="ドリンク" title="ドリンク">
	<!--{/def}-->
	<!--{def col_28b}-->
	<img src="{rval _cgiSysIconimg}028" alt="デザート" title="デザート">
	<!--{/def}-->
	<br>
	<!--{def col_41l2}-->
	<img src="{rval _cgiSysIconimg}0412" alt="禁煙" title="禁煙">
	<!--{/def}-->
	<!--{def col_41l1}-->
	<img src="{rval _cgiSysIconimg}0411" alt="分煙" title="分煙">
	<!--{/def}-->
	<!--{def col_41l3}-->
	<img src="{rval _cgiSysIconimg}0413" alt="完全分煙" title="完全分煙">
	<!--{/def}-->
	<!--{def col_42l1}-->
	<img src="{rval _cgiSysIconimg}0421" alt="テーブル席あり" title="テーブル席あり">
	<!--{/def}-->
	<!--{def col_43b}-->
	<img src="{rval _cgiSysIconimg}043" alt="ベビーシート" title="ベビーシート">
	<!--{/def}-->
	<!--{def col_44b}-->
	<img src="{rval _cgiSysIconimg}044" alt="多目的トイレ" title="多目的トイレ">
	<!--{/def}-->
	<!--{def col_45b}-->
	<img src="{rval _cgiSysIconimg}045" alt="スロープ／エレベーター" title="スロープ／エレベーター">
	<!--{/def}-->
	<!--{def col_48b}-->
	<img src="{rval _cgiSysIconimg}048" alt="駐車場" title="駐車場">
	<!--{/def}-->
	<!--{def col_49b}-->
	<img src="{rval _cgiSysIconimg}049" alt="ドライブスルー" title="ドライブスルー">
	<!--{/def}-->
	<!--{def col_50b}-->
	<img src="{rval _cgiSysIconimg}050" alt="クレジットカード利用可" title="クレジットカード利用可">
	<!--{/def}-->
	<!--{def col_74b}-->
	<img src="{rval _cgiSysIconimg}074" alt="交通系電子マネー" title="交通系電子マネー">
	<!--{/def}-->	
	<!--{def col_78b}-->
	<img src="{rval _cgiSysIconimg}078" alt="Edy利用可" title="Edy利用可">
	<!--{/def}-->	
	<!--{def col_58b}-->
	<img src="{rval _cgiSysIconimg}058" alt="iD利用可" title="iD利用可">
	<!--{/def}-->	
	<!--{def col_57b}-->
	<img src="{rval _cgiSysIconimg}057" alt="QUICPay利用可" title="QUICPay利用可">
	<!--{/def}-->	
	<!--{def col_72b}-->
	<img src="{rval _cgiSysIconimg}072" alt="ZENSHO CooCa取扱店" title="ZENSHO CooCa取扱店">
	<!--{/def}-->


</span></p></div>

<!--{def col_108l1}-->
<div class="z_litem"><p><span class="z_inf_col_title">災害時営業状況</span>
	<span class="z_litem_comment">
		通常どおり営業中
	</span>
</p></div>
<!--{/def}-->
<!--{def col_108l2}-->
<div class="z_litem"><p><span class="z_inf_col_title">災害時営業状況</span>
	<span class="z_litem_comment">
		メニューや営業時間を限定して営業中
	</span>
</p></div>
<!--{/def}-->
<!--{def col_108l3}-->
<div class="z_litem"><p><span class="z_inf_col_title">災害時営業状況</span>
	<span class="z_litem_comment">
		一時営業停止しています。復旧次第お知らせします。
	</span>
</p></div>
<!--{/def}-->
<!--{def col_108l4}-->
<div class="z_litem"><p><span class="z_inf_col_title">災害時営業状況</span>
	<span class="z_litem_comment">
		お問い合わせください。
	</span>
</p></div>
<!--{/def}-->
<!--{def col_113}-->
<div class="z_litem"><p><span class="z_inf_col_title">最寄国道県道主要道</span><span class="z_litem_comment">{rval col_113}</span></p></div>
<!--{/def}-->

<!--{def col_114}-->
<div class="z_litem"><p><span class="z_inf_col_title">営業時間</span>
	<span class="z_litem_comment">
		{rval col_114}
		<!--{def col_115}--><br>{rval col_115}<!--{/def}-->
		<!--{def col_116}--><br>{rval col_116}<!--{/def}-->
	</span>
</p></div>
<!--{/def}-->
<!--{def col_117}-->
<div class="z_litem"><p><span class="z_inf_col_title">営業時間備考</span>
	<span class="z_litem_comment">
		{rval col_117}
		<!--{def col_118}--><br>{rval col_118}<!--{/def}-->
	</span>
</p></div>
<!--{/def}-->
<!--{def col_124}-->
<div class="z_litem"><p><span class="z_inf_col_title">定休日</span><span class="z_litem_comment">{rval col_124}</span></p></div>
<!--{/def}-->
<!--{def col_125}-->
<div class="z_litem"><p><span class="z_inf_col_title">禁煙時間帯</span><span class="z_litem_comment">{rval col_125}</span></p></div>
<!--{/def}-->

<!--{def col_126}-->
<div class="z_litem"><p><span class="z_inf_col_title">アクセス</span>
	<span class="z_litem_comment">
		{rval col_126}
		<!--{def col_127}--><br>{rval col_127}<!--{/def}-->
	</span>
</p></div>
<!--{/def}-->
<!--{def col_128}-->
<div class="z_litem"><p><span class="z_inf_col_title">店舗紹介コメント</span><span class="z_litem_comment">{rval col_128}</span></p></div>
<!--{/def}-->
<!--{def col_129}-->
<!-- 店舗写真 -->
<div class="z_litem"><p><span class="z_litem_comment"><img src="{rval col_129}" /></span></p></div>
<!--{/def}-->
<!--{def col_130}-->
<div class="z_litem"><p><span class="z_inf_col_title">支払方法</span><span class="z_litem_comment">{rval col_130}</span></p></div>
<!--{/def}-->
<!--{def col_131}-->
<div class="z_litem"><p><span class="z_inf_col_title">座席または予約時最大席数</span><span class="z_litem_comment">{rval col_131}</span></p></div>
<!--{/def}-->
<!--{def col_132}-->
<!-- お知らせバナー１ -->
<div class="z_litem"><p>
	<span class="z_litem_comment">
	<!--{def col_133}--><a href="{rval col_133}" target="_blank" style="border:0;"><!--{/def}--><img src="{rval col_132}" /><!--{def col_133}--></a><!--{/def}-->
	<!--{def col_134}--><br>{rval col_134}<!--{/def}-->
	</span>
</p></div>
<!--{/def}-->
<!--{def col_135}-->
<!-- お知らせバナー２ -->
<div class="z_litem"><p>
	<span class="z_litem_comment">
	<!--{def col_136}--><a href="{rval col_136}" target="_blank" style="border:0;"><!--{/def}--><img src="{rval col_135}" /><!--{def col_136}--></a><!--{/def}-->
	</span>
</p></div>
<!--{/def}-->
<!--{def col_137}-->
<div class="z_litem"><p><span class="z_inf_col_title">お知らせ</span><span class="z_litem_comment">{rval col_137}</span></p></div>
<!--{/def}-->
<!--{def col_140}-->
<div class="z_litem"><p><span class="z_inf_col_title">駐車場台数</span><span class="z_litem_comment">{rval col_140}</span></p></div>
<!--{/def}-->
<!--{def col_141}-->
<div class="z_litem"><p><span class="z_inf_col_title">備考</span><span class="z_litem_comment">{rval col_141}</span></p></div>
<!--{/def}-->
<!--{def col_142}-->
<div class="z_litem"><p><span class="z_inf_col_title">店舗タイプ</span><span class="z_litem_comment">{rval col_142}</span></p></div>
<!--{/def}-->

</section>

<!--{/def}-->
<!--{/def}-->

