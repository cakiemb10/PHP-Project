<div id="kyotenList">
<!--{def msg}-->
	<div id="kyotenListErrMsg">{rval msg}</div>
<!--{/def}-->
<!--{def list}-->
	<div id="kyotenListHd">
		<table id="kyotenListHeader">
			<tr>
				<td class="kyotenListTitle">最寄り{rval D_USER_DEFNAME}一覧</td>
			</tr>
		</table>
	</div>
	<div id="kyotenListDt">
		<table id="kyotenListTable">
			<!--{each list}-->
			<tr>
				<td>
					<div class="kyotenListName">
						<img src="{rval list/_cgiIconimg}{rval list/icon}" />
						&nbsp;
						<a href="{rval list/_urlDetail}"
						onMouseOver="{rval list/_jsCurSet};" onMouseOut="{rval list/_jsCurRemove};"
						>
						{rval list/name}
						</a>
						
					</div>
					<!--{def list/addr}-->
					<div class="kyotenListData">
						<!--{def list/col_07}-->
						〒{rval list/col_07}&nbsp;
						<!--{/def}-->
						{rval list/addr}
					</div>
					<!--{/def}-->
					<div class="kyotenListData">
						<!--{def list/col_26b}-->
						<img src="{rval _cgiSysIconimg}026" alt="ドリンク" title="ドリンク">
						<!--{/def}-->
						<!--{def list/col_28b}-->
						<img src="{rval _cgiSysIconimg}028" alt="デザート" title="デザート">
						<!--{/def}-->
						<br>
						<!--{def list/col_41l2}-->
						<img src="{rval _cgiSysIconimg}0412" alt="禁煙" title="禁煙">
						<!--{/def}-->
						<!--{def list/col_41l1}-->
						<img src="{rval _cgiSysIconimg}0411" alt="分煙" title="分煙">
						<!--{/def}-->
						<!--{def list/col_41l3}-->
						<img src="{rval _cgiSysIconimg}0413" alt="完全分煙" title="完全分煙">
						<!--{/def}-->
						<!--{def list/col_42l1}-->
						<img src="{rval _cgiSysIconimg}0421" alt="テーブル席あり" title="テーブル席あり">
						<!--{/def}-->
						<!--{def list/col_43b}-->
						<img src="{rval _cgiSysIconimg}043" alt="ベビーシート" title="ベビーシート">
						<!--{/def}-->
						<!--{def list/col_44b}-->
						<img src="{rval _cgiSysIconimg}044" alt="多目的トイレ" title="多目的トイレ">
						<!--{/def}-->
						<!--{def list/col_45b}-->
						<img src="{rval _cgiSysIconimg}045" alt="スロープ／エレベーター" title="スロープ／エレベーター">
						<!--{/def}-->
						<!--{def list/col_48b}-->
						<img src="{rval _cgiSysIconimg}048" alt="駐車場" title="駐車場">
						<!--{/def}-->
						<!--{def list/col_49b}-->
						<img src="{rval _cgiSysIconimg}049" alt="ドライブスルー" title="ドライブスルー">
						<!--{/def}-->
						<!--{def list/col_50b}-->
						<img src="{rval _cgiSysIconimg}050" alt="クレジットカード利用可" title="クレジットカード利用可">
						<!--{/def}-->
						<!--{def list/col_74b}-->
						<img src="{rval _cgiSysIconimg}050" alt="交通系電子マネー" title="交通系電子マネー">
						<!--{/def}-->						
						<!--{def list/col_78b}-->
						<img src="{rval _cgiSysIconimg}050" alt="Edy利用可" title="Edy利用可">
						<!--{/def}-->						
						<!--{def list/col_58b}-->
						<img src="{rval _cgiSysIconimg}050" alt="iD利用可" title="iD利用可">
						<!--{/def}-->						
						<!--{def list/col_57b}-->
						<img src="{rval _cgiSysIconimg}050" alt="QUICPay利用可" title="QUICPay利用可">
						<!--{/def}-->
						<!--{def list/col_72b}-->
						<img src="{rval _cgiSysIconimg}072" alt="ZENSHO CooCa取扱店" title="ZENSHO CooCa取扱店">
						<!--{/def}-->
					</div>
				</td>
			</tr>
		<!--{/each}-->
		</table>
	</div>
	<div class="custKyotenListHd">
		<table class="custKyotenListHeader">
			<tr>
				<td class="custKyotenListPage">
					<!--{def _jsPrev}-->
					<input type="button" class="custPageButton" onClick="{rval _jsPrev}" value="前へ" />&nbsp;
					<!--{/def}-->
					{rval start}-{rval end}件/{rval max}件中
					<!--{def _jsNext}-->
					&nbsp;<input type="button" class="custPageButton" onClick="{rval _jsNext}" value="次へ" />
					<!--{/def}-->
				</td>
			</tr>
		</table>
	</div>
<!--{/def}-->
</div>
