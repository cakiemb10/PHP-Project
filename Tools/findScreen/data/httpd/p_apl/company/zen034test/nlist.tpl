<div id="kyotenList">
<!--{def msg}-->
	<div id="kyotenListErrMsg">{rval msg}</div>
<!--{/def}-->
<!--{def list}-->
	<div id="kyotenListHd">
		<table id="kyotenListHeader">
			<tr>
				<td class="kyotenListTitle">�Ǵ��{rval D_USER_DEFNAME}����</td>
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
						<!--{def list/icon_80}-->�ڲ�Ϳʼ��&nbsp;<!--{/def}-->
						<!--{def list/icon_90}-->�¿���ؤ�&nbsp;<!--{/def}-->
						{rval list/name}
						</a>
						
					</div>
					<!--{def list/addr}-->
					<div class="kyotenListData">
						<!--{def list/col_07}-->
						��{rval list/col_07}&nbsp;
						<!--{/def}-->
						{rval list/addr}
					</div>
					<!--{/def}-->
					<div class="kyotenListData">
						<!--{def list/col_30l1}-->
						<img src="{rval _cgiSysIconimg}030" alt="ī���Х�����" title="ī���Х�����">
						<!--{/def}-->
						<!--{def list/col_30l2}-->
						<img src="{rval _cgiSysIconimg}030" alt="ī���Х�����" title="ī���Х�����">
						<!--{/def}-->
						<!--{def list/col_31b}-->
						<img src="{rval _cgiSysIconimg}031" alt="��������" title="��������">
						<!--{/def}-->
						<!--{def list/col_33b}-->
						<img src="{rval _cgiSysIconimg}033" alt="�ɥ�󥯥С�" title="�ɥ�󥯥С�">
						<!--{/def}-->
						<br>
						<!--{def list/col_41l2}-->
						<img src="{rval _cgiSysIconimg}0412" alt="�ر�" title="�ر�">
						<!--{/def}-->
						<!--{def list/col_41l1}-->
						<img src="{rval _cgiSysIconimg}0411" alt="ʬ��" title="ʬ��">
						<!--{/def}-->
						<!--{def list/col_41l3}-->
						<img src="{rval _cgiSysIconimg}0413" alt="����ʬ��" title="����ʬ��">
						<!--{/def}-->
						<!--{def list/col_43b}-->
						<img src="{rval _cgiSysIconimg}043" alt="�٥ӡ�������" title="�٥ӡ�������">
						<!--{/def}-->
						<!--{def list/col_44b}-->
						<img src="{rval _cgiSysIconimg}044" alt="¿��Ū�ȥ���" title="¿��Ū�ȥ���">
						<!--{/def}-->
						<!--{def list/col_45b}-->
						<img src="{rval _cgiSysIconimg}045" alt="�����ס�����١�����" title="�����ס�����١�����">
						<!--{/def}-->
						<!--{def list/col_46l1}-->
						<img src="{rval _cgiSysIconimg}0461" alt="Ź�ޥե�1F" title="Ź�ޥե�1F">
						<!--{/def}-->
						<!--{def list/col_48b}-->
						<img src="{rval _cgiSysIconimg}048" alt="��־�" title="��־�">
						<!--{/def}-->
						<!--{def list/col_50b}-->
						<img src="{rval _cgiSysIconimg}050" alt="���쥸�åȥ��������Ѳ�" title="���쥸�åȥ��������Ѳ�">
						<!--{/def}-->
						<!--{def list/col_74b}-->
						<img src="{rval _cgiSysIconimg}074" alt="���̷��Żҥޥ͡�" title="���̷��Żҥޥ͡�">
						<!--{/def}-->
						<!--{def list/col_78b}-->
						<img src="{rval _cgiSysIconimg}078"  alt="Edy���Ѳ�" title="Edy���Ѳ�">
						<!--{/def}-->
						<!--{def list/col_58b}-->
						<img src="{rval _cgiSysIconimg}058" alt="iD���Ѳ�" title="iD���Ѳ�">
						<!--{/def}-->
						<!--{def list/col_57b}-->
						<img src="{rval _cgiSysIconimg}057" alt="QUICPay���Ѳ�" title="QUICPay���Ѳ�">
						<!--{/def}-->
						<!--{def list/col_72b}-->
						<img src="{rval _cgiSysIconimg}072" alt="ZENSHO CooCa�谷Ź" title="ZENSHO CooCa�谷Ź">
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
					<input type="button" class="custPageButton" onClick="{rval _jsPrev}" value="����" />&nbsp;
					<!--{/def}-->
					{rval start}-{rval end}��/{rval max}����
					<!--{def _jsNext}-->
					&nbsp;<input type="button" class="custPageButton" onClick="{rval _jsNext}" value="����" />
					<!--{/def}-->
				</td>
			</tr>
		</table>
	</div>
<!--{/def}-->
</div>
