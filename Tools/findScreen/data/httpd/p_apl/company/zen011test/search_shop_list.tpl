<table border="0" cellpadding="0" cellspacing="0" width="100%">
	<tr>
		<td align="center">
			<table id="searchShopListTitle">
				<tr>
					<td id="searchShopListTitleNm">
					<!--{def keyword}-->
						{rval title}:&nbsp;{rval keyword}
					<!--{/def}-->
					<!--{ndef keyword}-->
						{rval title}
					<!--{/def}-->
					</td>
				</tr>
			</table>
			<!--{def selname}-->
			<table id="searchShopListExp">
				<tr>
					<td>
						{rval selname}������Ǥ�������
					</td>
				</tr>
			</table>
			<!--{/def}-->
			<table id="searchShopListData">
			<!--{each list}-->
				<tr>
					<td class="searchShopListDataNm">
						<img src="{rval list/_cgiIconimg}{rval list/icon}" />
						&nbsp;
						<a href="{rval list/_urlNameLink}">
							{rval list/name}</a>
					</td>
					<td class="searchShopListDataDt">
						<table class="searchShopListDtTable">
							<tr>
								<td>
								<!--{def list/col_07}-->
								��{rval list/col_07}&nbsp;
								<!--{/def}-->
								{rval list/addr}
								</td>
							</tr>
							<tr>
								<td>
									<!--{def list/col_26b}-->
									<img src="{rval _cgiSysIconimg}026" alt="�ɥ��" title="�ɥ��">
									<!--{/def}-->
									<!--{def list/col_28b}-->
									<img src="{rval _cgiSysIconimg}028" alt="�ǥ�����" title="�ǥ�����">
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
									<!--{def list/col_42l1}-->
									<img src="{rval _cgiSysIconimg}0421" alt="�ơ��֥��ʤ���" title="�ơ��֥��ʤ���">
									<!--{/def}-->
									<!--{def list/col_43b}-->
									<img src="{rval _cgiSysIconimg}043" alt="�٥ӡ�������" title="�٥ӡ�������">
									<!--{/def}-->
									<!--{def list/col_44b}-->
									<img src="{rval _cgiSysIconimg}044" alt="¿��Ū�ȥ���" title="¿��Ū�ȥ���">
									<!--{/def}-->
									<!--{def list/col_45b}-->
									<img src="{rval _cgiSysIconimg}045" alt="�������ס�����١�����" title="�������ס�����١�����">
									<!--{/def}-->
									<!--{def list/col_48b}-->
									<img src="{rval _cgiSysIconimg}048" alt="��־�" title="��־�">
									<!--{/def}-->
									<!--{def list/col_49b}-->
									<img src="{rval _cgiSysIconimg}049" alt="�ɥ饤�֥��롼" title="�ɥ饤�֥��롼">
									<!--{/def}-->
									<!--{def list/col_50b}-->
									<img src="{rval _cgiSysIconimg}050" alt="���쥸�åȥ��������Ѳ�" title="���쥸�åȥ��������Ѳ�">
									<!--{/def}-->
									<!--{def list/col_74b}-->
									<img src="{rval _cgiSysIconimg}050" alt="���̷��Żҥޥ͡�" title="���̷��Żҥޥ͡�">
									<!--{/def}-->									
									<!--{def list/col_78b}-->
									<img src="{rval _cgiSysIconimg}050" alt="Edy���Ѳ�" title="Edy���Ѳ�">
									<!--{/def}-->									
									<!--{def list/col_58b}-->
									<img src="{rval _cgiSysIconimg}050" alt="iD���Ѳ�" title="iD���Ѳ�">
									<!--{/def}-->								
									<!--{def list/col_57b}-->
									<img src="{rval _cgiSysIconimg}050" alt="QUICPay���Ѳ�" title="QUICPay���Ѳ�">
									<!--{/def}-->
									<!--{def list/col_72b}-->
									<img src="{rval _cgiSysIconimg}072" alt="ZENSHO CooCa�谷Ź" title="ZENSHO CooCa�谷Ź">
									<!--{/def}-->
								</td>
							</tr>
						</table>
					</td>
				</tr>
			<!--{/each}--> 
			</table>
			<table id="searchShopListPage">
				<tr>
					<td>
		<!--{def _urlPrev}-->
						<a href="{rval _urlPrev}">����</a>&nbsp;��&nbsp;
		<!--{/def}-->
						{rval start}-{rval end}��/{rval max}����
		<!--{def _urlNext}-->
						&nbsp;��&nbsp;<a href="{rval _urlNext}">����</a>
		<!--{/def}-->
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>