<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="ja">

<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta http-equiv="Content-Style-Type" content="text/css">
<meta http-equiv="Content-Script-Type" content="Text/javascript">
<meta http-equiv="Imagetoolbar" content="no">
<meta name="viewport" content="width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;">
<meta name="keywords" content="{rval D_TITLE},店舗案内,案内,Android,iPhone,iPad">
<meta name="description" content="{rval D_TITLE}">

<title>{rval D_TITLE}</title>
<!--{each css}-->
<link href="{rval css/src}" type="text/css" rel="stylesheet" media="all">
<!--{/each}-->
<link href="{rval D_DIR_COMPANY}css/reset.css"  rel="stylesheet" type="text/css" />
<link href="{rval D_DIR_COMPANY}css/smart.css"  rel="stylesheet" type="text/css" />
<link href="{rval D_DIR_COMPANY}css/map.css"    rel="stylesheet" type="text/css" />
<link href="{rval D_DIR_COMPANY}css/custom.css" rel="stylesheet" type="text/css" />
<!--{each js}-->
<script charset="{rval js/charset}" type="text/javascript" src="{rval js/src}"></script>
<!--{/each}-->
<!--{def _jsLocCallback}-->
<script type="text/JavaScript">
<!--
{rval _jsLocCallback}
//-->
</script>
<!--{/def}-->
<script charset="EUC-JP" type="text/javascript" src="{rval D_DIR_COMPANY}js/custom.js"></script>
</head>
<body class="z_map_body" onload="{rval _jsInit};">
<div style="padding-top: 2px; padding-bottom: 2px;">
	<table>
		<tr>
			<td style="padding-left: 5px; padding-right: 5px;">
				<img src="{rval D_DIR_COMPANY}img/A-1_C-4.gif">
			</td>
			<td style="vertical-align: middle;">
				お得なクーポンがある店舗です
			</td>
		</tr>
	</table>
</div>
