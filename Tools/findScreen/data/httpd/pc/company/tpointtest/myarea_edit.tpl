<?php
$myar = $_GET['myar'];
$p_s2 = $_GET['p_s2'];
$lm = $_GET['lm'];
?>
<!-- ▼▼ content ▼▼ --> 
<div id="ZdcEmapMyAreaEdit">
	<div id="map-box">
		<div class="map-ttl03">
			<h2 class="map-hidden">Myエリアに追加する</h2>
			<p class="map-ttl_link"><a href="http://stg.tsite.jp/r/map/index.html" style="color:fff;">Myエリアとは？</a></p>
		</div>
		<div class="map-box_inner">
			<dl class="map-left search_list">
				<dd>自宅の近く、会社・学校の近くなど、<span class="map-txt_red">最大5か所のエリア</span>を登録することができます。<br />
<span class="map-txt_red">よく行く場所を検索せずに表示</span>できるので、とっても便利！<br />
もちろん、<span class="map-txt_red">現在表示されている場所を登録</span>することができます。</dd>
			</dl>
			<div class="map-fright mb15"><a href="/asp/{rval cid}/?myar={rval prm/myar}&p_s2={rval prm/p_s2}&lm={rval prm/lm}" OnMouseOver='AddImgChangeMouseOver("{rval D_DIR_COMPANY}");' OnMouseOut='AddImgChangeMouseOut("{rval D_DIR_COMPANY}");'><img name="MyAreaAddEdit" src="{rval D_DIR_COMPANY}pc/image/map/b_add-search.jpg" width="338" height="72" alt="Myエリアに登録する場所を探す" class="imgover" /></a></div>

		</div>
	</div>
	<div id="map-box">
		<h2 class="map-ttl"><img src="{rval D_DIR_COMPANY}pc/image/map/ttl_edit.jpg" width="862" height="34" alt="Myエリアの編集と削除" /></h2>
		<div class="map-box_inner">
			<p class="map-txt01">名称の変更や、表示順位の変更ができます。<br />
登録されている場所を変更したい場合、一度削除し、新たにMyエリアを追加してください。</p>
				<table class="map-edit">
					<tr>
						<th width="484px">Myエリアの名称</th>
						<th width="112px">地図</th>
						<th width="84px">順序</th>
						<th width="114px">削除</th>
					</tr>
					<!--{each list}-->
					<!--{def list/myarea_id}-->
					<tr>
							<td style="padding:15px;">
								<form method="GET" name="frm_myarea{rval list/myarea_id}" id="frm_myarea{rval list/myarea_id}" action="/pc/index.htm">
									<input type="hidden" name="cid" value="{rval list/corp_id}">
									<input type="hidden" name="type" value="">
									<input type="hidden" name="myarea_id" value="{rval list/myarea_id}">
									<input type="hidden" name="corp_id" value="{rval list/corp_id}">
									<input type="hidden" name="myar" value="<?php echo $myar; ?>">
									<input type="hidden" name="p_s2" value="{rval prm/p_s2_dec}">
									<input type="hidden" name="lm" value="{rval prm/lm_dec}">
									<input type="hidden" name="disp_order_prev" value="{rval list/disp_order_prev}">
									<input type="hidden" name="disp_order_next" value="{rval list/disp_order_next}">
									<input type="text" style="position:absolute;visibility:hidden">
									<input type="text" name="myarea_name" id="myarea_name" class="map-input02" value="{rval list/myarea_name}" onKeyPress="key_press(event, document.frm_myarea{rval list/myarea_id})">
									<a href="javascript:MyAreaNameUpdt(frm_myarea{rval list/myarea_id});"><img src="{rval D_DIR_COMPANY}pc/image/map/b_setting.jpg" width="68" height="24" alt="設定する" align="middle"></a>
								</form>
							</td>
							<td align="center" style="padding:15px 0px;">
								<a href="/pc/index.htm?cid={rval list/corp_id}&myar=<?php echo $myar; ?>&p_s2=<?php echo $p_s2; ?>&lm=<?php echo $lm; ?>&myardisp=1&user_id=<?php echo $p_s2; ?>&lat={rval list/lat}&lon={rval list/lon}&area_no={rval list/disp_order}"><img src="{rval D_DIR_COMPANY}pc/image/map/b_display.gif" width="62" height="18" alt="表示する" /></a>
							</td>
							<td align="center" style="padding:15px 0px;">
							<!--{def list/disp_order_prev}-->
								<a href="javascript:ChangeDispOrderUp(document.frm_myarea{rval list/myarea_id});">
									<img src="{rval D_DIR_COMPANY}pc/image/map/b_up.gif" width="16" height="16" alt="" /></a>&nbsp;
							<!--{/def}-->
							<!--{ndef list/disp_order_prev}-->
									<img src="{rval D_DIR_COMPANY}pc/image/map/b_up.gif" width="16" height="16" alt="" />&nbsp;
							<!--{/ndef}-->
							<!--{def list/disp_order_next}-->
								<a href="javascript:ChangeDispOrderDown(document.frm_myarea{rval list/myarea_id});">
									<img src="{rval D_DIR_COMPANY}pc/image/map/b_down.gif" width="16" height="16" alt="" /></a>
							<!--{/def}-->
							<!--{ndef list/disp_order_next}-->
									<img src="{rval D_DIR_COMPANY}pc/image/map/b_down.gif" width="16" height="16" alt="" />
							<!--{/ndef}-->
							</td>
							<td align="center" class="rightBlock" style="padding:15px 0px;"><a href="javascript:DeleteMyarea(document.frm_myarea{rval list/myarea_id});"><img src="{rval D_DIR_COMPANY}pc/image/map/b_delate.gif" width="62" height="18" alt="削除する" /></a></td>
					</tr>
					<!--{/def}-->
					<!--{/each}-->
				</table>
		</div>
	</div>
	<p class="map-returnTop"><a href="/asp/{rval cid}/?myar={rval prm/myar}&p_s2={rval prm/p_s2}&lm={rval prm/lm}" style="font-size:14px;">お店地図検索 トップに戻る</a></p>
</div>
	<!-- ▲▲ content end ▲▲ -->
