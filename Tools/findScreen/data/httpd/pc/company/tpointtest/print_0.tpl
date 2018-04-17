<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<meta http-equiv="content-type" content="text/html;charset=EUC-JP">
	<meta http-equiv="Content-Style-Type" content="text/css">
	<meta http-equiv="Content-Script-Type" content="text/javascript">
	<title>{rval D_USER_DEFNAME}のご案内</title>
	<link href="{rval D_DIR_COMPANY}css/print_page.css" rel="stylesheet" type="text/css" media="screen,print">
	<link href="{rval D_DIR_COMPANY}css/print.css"      rel="stylesheet" type="text/css" media="print">
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
