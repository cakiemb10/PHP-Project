<!-- //業態エラー -->
<!--{ndef col_04l11}-->

<script type="text/JavaScript">
<!--
document.body.style.background="white";
//-->
</script>

<div  style="font-size: 16px;">
<center>
<br><br>
<font color="black"><b>
指定された店舗は存在しません
</b></font>
<br><br>
<a href="javascript:window.history.back();" style="text-decoration:underline;color:#0000ee;">戻る</a>
</center>
</div>

<!--{/ndef}-->


<!-- //非公開フラグ -->
<!--{def col_04l11}-->
<!--{ndef col_02b}-->

<script type="text/JavaScript">
<!--
document.getElementById("header_wrap").style.display="none";
document.getElementById("history").style.display="none";
document.body.style.background="white";
//-->
</script>

<div  style="font-size: 16px;">
<center>
<br><br>
<font color="black"><b>
指定された店舗は存在しません
</b></font>
<br><br>
<a href="javascript:window.history.back();" style="text-decoration:underline;color:#0000ee;">戻る</a>
</center>
</div>

<!--{/ndef}-->
<!--{/def}-->

<!--{def col_04l11}-->
<!--{def col_02b}-->

	<div id="topMargin"></div>
	<div id="buttonPrint">
		<a onkeypress="javascript:print();" href="javascript:print();"><img src="{rval D_DIR_COMPANY}images/print_btn_print.gif" alt="このページを印刷する" title="このページを印刷する"></a></div>
	<div id="printName">
		<img src="{rval _cgiIconimg}{rval icon}" style="vertical-align:middle;" />
		&nbsp;
		{rval name}
	</div>
	<table style="border:0;margin:0;padding:0;border-collapse: collapse;">
	<tr><td>
	<div id="printDtl">
		<table id="printDtlOuterTable">
			<tr>
				<td class="printDtlTdL">
					<table class="printDtlTable">
						<!--{def addr}-->
						<tr>
							<th>住所</th>
							<td>
								<!--{def col_07}-->
								〒{rval col_07}&nbsp;
								<!--{/def}-->
								{rval addr}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_08}-->
						<tr>
							<th>電話番号</th>
							<td>
								{rval col_08}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_147}-->
						<tr>
							<th>IP電話</th>
							<td>
								{rval col_147}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_09}-->
						<tr>
							<th>URL</th>
							<td>
								<a href="{rval col_09}" target="_blank">{rval col_09}</a>
							</td>
						</tr>
						<!--{/def}-->
						<tr>
							<td class="kyotenDtlData dtlspan2" colspan="2">
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
								<img src="{rval _cgiSysIconimg}050" alt="交通系電子マネー" title="交通系電子マネー">
								<!--{/def}-->								
								<!--{def col_78b}-->
								<img src="{rval _cgiSysIconimg}050" alt="Edy利用可" title="Edy利用可">
								<!--{/def}-->								
								<!--{def col_58b}-->
								<img src="{rval _cgiSysIconimg}050" alt="iD利用可" title="iD利用可">
								<!--{/def}-->								
								<!--{def col_57b}-->
								<img src="{rval _cgiSysIconimg}050" alt="QUICPay利用可" title="QUICPay利用可">
								<!--{/def}-->
								<!--{def col_72b}-->
								<img src="{rval _cgiSysIconimg}072" alt="ZENSHO CooCa取扱店" title="ZENSHO CooCa取扱店">
								<!--{/def}-->
							</td>
						</tr>
						<!--{def col_108l1}-->
						<tr>
							<th>災害時営業状況</th>
							<td>
								通常どおり営業中
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_108l2}-->
						<tr>
							<th>災害時営業状況</th>
							<td>
								メニューや営業時間を限定して営業中
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_108l3}-->
						<tr>
							<th>災害時営業状況</th>
							<td>
								一時営業停止しています。復旧次第お知らせします。
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_108l4}-->
						<tr>
							<th>災害時営業状況</th>
							<td>
								お問い合わせください。
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_113}-->
						<tr>
							<th>最寄国道県道主要道</th>
							<td>
								{rval col_113}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_114}-->
						<tr>
							<th>営業時間</th>
							<td>
								{rval col_114}
								<!--{def col_115}--><br>{rval col_115}<!--{/def}-->
								<!--{def col_116}--><br>{rval col_116}<!--{/def}-->
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_117}-->
						<tr>
							<th>営業時間備考</th>
							<td>
								{rval col_117}
								<!--{def col_118}--><br>{rval col_118}<!--{/def}-->
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_124}-->
						<tr>
							<th>定休日</th>
							<td>
								{rval col_124}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_125}-->
						<tr>
							<th>禁煙時間帯</th>
							<td>
								{rval col_125}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_126}-->
						<tr>
							<th>アクセス</th>
							<td>
								{rval col_126}
								<!--{def col_127}--><br>{rval col_127}<!--{/def}-->
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_128}-->
						<tr>
							<th>店舗紹介コメント</th>
							<td>
								{rval col_128}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_129}-->
						<!-- 店舗写真 -->
						<tr>
							<td class="kyotenDtlData dtlspan2 kyotenDtlImgTd" colspan="2">
								<img src="{rval col_129}" />
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_130}-->
						<tr>
							<th>支払方法</th>
							<td>
								{rval col_130}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_131}-->
						<tr>
							<th>座席または予約時最大席数</th>
							<td>
								{rval col_131}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_132}-->
						<!-- お知らせバナー１ -->
						<tr>
							<td class="kyotenDtlData dtlspan2 kyotenDtlImgTd" colspan="2">
								<!--{def col_133}--><a href="{rval col_133}" target="_blank"><!--{/def}--><img src="{rval col_132}" /><!--{def col_133}--></a><!--{/def}-->
								<!--{def col_134}--><br>{rval col_134}<!--{/def}-->
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_135}-->
						<!-- お知らせバナー２ -->
						<tr>
							<td class="kyotenDtlData dtlspan2 kyotenDtlImgTd" colspan="2">
								<!--{def col_136}--><a href="{rval col_136}" target="_blank"><!--{/def}--><img src="{rval col_135}" /><!--{def col_136}--></a><!--{/def}-->
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_137}-->
						<tr>
							<th>お知らせ</th>
							<td>
								{rval col_137}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_140}-->
						<tr>
							<th>駐車場台数</th>
							<td>
								{rval col_140}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_141}-->
						<tr>
							<th>備考</th>
							<td>
								{rval col_141}
							</td>
						</tr>
						<!--{/def}-->
						<!--{def col_142}-->
						<tr>
							<th>店舗タイプ</th>
							<td>
								{rval col_142}
							</td>
						</tr>
						<!--{/def}-->
					</table>
				</td>
			</tr>
		</table>
	</div>
	</td></tr>
	<tr><td>
	<div id="ZdcEmapMap" style="width:578px;height:550px;"></div>
	</td></tr>
	</table>

<!--{/def}-->
<!--{/def}-->

