<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<meta http-equiv="content-type" content="text/html;charset=EUC-JP">
	<meta http-equiv="Content-Style-Type" content="text/css">
	<meta http-equiv="Content-Script-Type" content="text/javascript">
	<title>{rval D_USER_DEFNAME}のご案内</title>
	<link href="{rval D_DIR_COMPANY}css/print_list.css" rel="stylesheet" type="text/css" media="screen,print">
	<link href="{rval D_DIR_COMPANY}css/print2.css"      rel="stylesheet" type="text/css" media="print">
	<link href="{rval D_DIR_COMPANY}css/default.css"    rel="stylesheet" type="text/css">
	<link href="{rval D_DIR_COMPANY}css/custom.css"  rel="stylesheet" type="text/css" media="screen,print">
	<!-- ↓↓↓ e-map standard 制御コード ↓↓↓ -->
	<!--{each css}-->
	<link  href="{rval css/src}" type="text/css" rel="stylesheet" media="all">
		<!--{/each}-->
	<!--{each js}-->
	<script charset="{rval js/charset}" type="text/javascript" src="{rval js/src}"></script>
	<!--{/each}-->
	<!-- ↑↑↑ e-map standard 制御コード ↑↑↑ -->
</head>
<body onload="{rval _jsInit};">
<div id="wrapper">
<table border="0" cellpadding="0" cellspacing="0" width="100%">
	<tr>
		<td align="center">
			<table id="printShopListExp">
				<tr>
					<td>
						<div id="buttonPrintList" align="right">
							<a onkeypress="javascript:print();" href="javascript:print();"><img src="{rval D_DIR_COMPANY}images/print_btn_print.gif" alt="このページを印刷する" title="このページを印刷する"></a></div>
					</td>
				</tr>
			</table>
			<table id="printShopListTitle">
				<tr>
					<td>
					<!--{def keyword}-->
						{rval title}:&nbsp;{rval keyword}
					<!--{/def}-->
					<!--{ndef keyword}-->
						{rval title}
					<!--{/def}-->
					</td>
				</tr>
			</table>
			<table id="printShopListData">
			<!--{each list}-->
				<tr>
					<td class="printShopListDataNm">
						{rval list/name}
					</td>
					<td class="printShopListDataDt">
						<table class="printShopListDtTable">
								<!--{def list/col_02}-->
							<tr>
								<td>
									{rval list/col_02}
								</td>
							</tr>
								<!--{/def}-->
								<!--{def list/addr}-->
							<tr>
								<td>
									{rval list/addr}
								</td>
							</tr>
								<!--{/def}-->
								<!--{def list/col_01}-->
							<tr>
								<td>
									{rval list/col_01}
								</td>
							</tr>
								<!--{/def}-->
						</table>
					</td>
				</tr>
			<!--{/each}-->
			</table>
		</td>
	</tr>
</table>
<br>
</div>
</body>
</html>
