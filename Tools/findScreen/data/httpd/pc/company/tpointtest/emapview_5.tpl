		<!-- ↑ヘッダ挿入位置 ここまで -->
	</div>
<!--HEADER[E]-->
<!--パンくずリスト開始-->
	<!-- ↓↓↓ e-map standard 制御コード ↓↓↓ -->
	<div id="history"></div>
	<!-- ↑↑↑ e-map standard 制御コード ↑↑↑ -->
<!--パンくずリスト終了-->
<!--CONTENTS[S]-->
	<div id="contents" class="contents-withhis"> 
		<div id="map-box">
			<!--{def user_id}-->
			<div class="map-ttl">
				<h2 class="map-hidden">Myエリア</h2>
				<!--{def test_flg}-->
				<p class="map-ttl_link"><a href="https://stg.tsite.jp/r/map/index.html" style="color:#ffffff" target="_blank">Myエリアとは？</a></p>
				<!--{/def}-->
				<!--{ndef test_flg}-->
				<p class="map-ttl_link"><a href="https://tsite.jp/r/map/index.html" style="color:#ffffff" target="_blank">Myエリアとは？</a></p>
				<!--{/def}-->
			</div>
			<div class="map-box_inner">
				<!--{ndef myardisp}-->
				<dl class="map-left search_list">
					<dt><h3 class="map-subttl">表示されている場所をMyエリアに追加する</h3></dt>
					<dd>自宅の近く、会社・学校の近くなど、<span class="map-txt_red">最大5か所のエリア</span>を登録することができます。<br />
					<span class="map-txt_red">よく行く場所を検索せずに表示</span>できるので、とっても便利！<br />もちろん、<span class="map-txt_red">現在表示されている場所を登録</span>することができます。</dd>
				</dl>
				<!--{def regist_flg}-->
				<div class="map-fright"><a href="javascript:{rval _jsMyAreaAddDisp}" onclick='changeScreen("transparent", "{rval D_DIR_COMPANY}");' OnMouseOver='ImgChangeMouseOver("{rval D_DIR_COMPANY}");' OnMouseOut='ImgChangeMouseOut("{rval D_DIR_COMPANY}");'><img src="{rval D_DIR_COMPANY}images/b_registering.jpg" name="MyAreaAdd" width="338" height="72" alt="Myエリアに追加" /></a></div>
				<!--{/def}-->
				<!--{ndef regist_flg}-->
				<div class="map-fright"><a href="javascript:{rval _jsMyAreaAddDisp}" onclick='changeScreen("transparent", "{rval D_DIR_COMPANY}");' OnMouseOver='ImgChangeMouseOver("{rval D_DIR_COMPANY}");' OnMouseOut='ImgChangeMouseOut("{rval D_DIR_COMPANY}");'><img src="{rval D_DIR_COMPANY}images/b_add.jpg" name="MyAreaAdd" width="338" height="72" alt="Myエリアに追加" /></a></div>
				<!--{/ndef}-->
				<div class="map-dotted"><hr /></div>
				<!--{/ndef}-->
				<div class="pl5">
					<span class="map-subttl">登録されているMyエリア</span>
					<span class="map-areaEdit"><a href="javascript:{rval _jsMyAreaEdit}">Myエリアの編集・削除</a></span>
				</div>

				<ul class="search_list">
				<!--{each myar_list}-->
				<li class="map-fleft">
					<!--{def myar_list/myarea_id}-->
					<a id="area_name_link{rval myar_list/disp_order}" style="color: #4f7eb9; font-size: 13px; font-weight: bold;" href="/pc/index.htm?cid={rval corp_id}&myar={rval myar}&p_s2={rval user_id}&lm={rval lm}&myardisp=1&user_id={rval user_id}&lat={rval myar_list/lat}&lon={rval myar_list/lon}&area_no={rval myar_list/disp_order}">{rval myar_list/myarea_name}</a>
					<span id="area_name_text{rval myar_list/disp_order}" style="color: #ff5555; font-size: 13px; font-weight: bold;">{rval myar_list/myarea_name}</span>
					<!--{/def}-->
					<!--{def myar_list/sep_flg}-->
					<span style="font-size: 13px;">｜&nbsp;</span>
					<!--{/def}-->
				</li>
				<!--{/each}-->
				</ul>
			</div>
			<!--{/def}-->
			<!--{ndef user_id}-->
			<div class="map-ttl">
				<h2 class="map-hidden">Myエリア</h2>
				<!--{def test_flg}-->
				<p class="map-ttl_link"><a href="https://stg.tsite.jp/r/map/index.html" style="color:#ffffff" target="_blank">Myエリアとは？</a></p>
				<!--{/def}-->
				<!--{ndef test_flg}-->
				<p class="map-ttl_link"><a href="https://tsite.jp/r/map/index.html" style="color:#ffffff" target="_blank">Myエリアとは？</a></p>
				<!--{/def}-->
			</div>
			<div class="map-box_inner">
				<dl class="map-left search_list">
					<dt><h3 class="map-subttl">表示されている場所をMyエリアに追加する</h3></dt>
					<dd>自宅の近く、会社・学校の近くなど、<span class="map-txt_red">最大5か所のエリア</span>を登録することができます。<br />
					<span class="map-txt_red">よく行く場所を検索せずに表示</span>できるので、とっても便利！<br />もちろん、<span class="map-txt_red">現在表示されている場所を登録</span>することができます。</dd>
				</dl>
				<div class="map-fright"><a href='javascript:goTsite("{rval test_flg}");' OnMouseOver='ImgChangeMouseOver("{rval D_DIR_COMPANY}");' OnMouseOut='ImgChangeMouseOut("{rval D_DIR_COMPANY}");'><img src="{rval D_DIR_COMPANY}images/b_add.jpg" name="MyAreaAdd" width="338" height="72" alt="Myエリアに追加" /></a></div>
			</div>
			<!--{/ndef}-->
		</div>
	<!--[if IE 6 ]>
	<div style="float:left;" id="minheight">&nbsp;</div>
	<div style="float:right;">
	<![endif]-->
		<!--LEFT[S]-->
		<div id="leftArea">
			<!-- ↓↓↓ e-map standard 制御コード ↓↓↓ -->
			<div id="ZdcEmapMap"></div>
			<!-- ↑↑↑ e-map standard 制御コード ↑↑↑ -->
			<!-- ↓↓↓ 地図閲覧規約 ↓↓↓ -->
			<div id="mapRuleLink">
				<a href="{rval D_DIR_BASE}kiyaku/map_rule.htm" target="_blank"
				onClick="window.open('{rval D_DIR_BASE}kiyaku/map_rule.htm', '',
				'width=600,height=600,resizable,scrollbars,menubar=no'); return false;">
					地図閲覧規約</a>
			</div>
			<!-- ↑↑↑ 地図閲覧規約 ↑↑↑ -->
		</div>
		<!--LEFT[E]-->
		<!--RIGHT[S]-->
		<div id="rightArea">
			<!-- ↓↓↓ e-map standard 制御コード ↓↓↓ -->
			<div id="ZdcEmapDetail"></div>
			<div id="ZdcEmapList"></div>
			<!-- ↑↑↑ e-map standard 制御コード ↑↑↑ -->
		</div>
		<!--RIGHT[E]-->
		<!-- ↓↓↓ e-map standard 制御コード ↓↓↓ -->
		<div id="ZdcEmapCond"></div>
		<!-- ↑↑↑ e-map standard 制御コード ↑↑↑ -->
		<!--RESEARCH_LAYER[S]-->
		<!-- ↓↓↓ e-map standard 制御コード ↓↓↓ -->
		<!--[if IE 6 ]>
		<div id="ZdcEmapIE6HideSelect"><iframe frameborder="0" width="100%" height="100%"></iframe></div>
		<![endif]-->
		<div id="ZdcEmapSearchWindow">&nbsp;</div>
		<!-- ↑↑↑ e-map standard 制御コード ↑↑↑ -->
		<!--RESEARCH_LAYER[E]-->
	<!--[if IE 6 ]>
	</div>
	<![endif]-->
	<div id="map-return-top">
		<!--{def myardisp}-->
		<a href="/asp/{rval corp_id}/?myar={rval myar}&p_s2={rval user_id}&lm={rval lm}" style="font-size:14px;">Myエリアに登録されている場所以外の地図を見る</a>
		<!--{/def}-->
		<!--{ndef myardisp}-->
		<a href="/asp/{rval corp_id}/?myar={rval myar}&p_s2={rval user_id}&lm={rval lm}" style="font-size:14px;">お店地図検索 トップに戻る</a>
		<!--{/ndef}-->
	</div>
	</div>
<!--CONTENTS[E]-->
<!--FOOTER[S]-->
	<div id="footer">
		<!-- ↓フッタ挿入位置 ここから -->
