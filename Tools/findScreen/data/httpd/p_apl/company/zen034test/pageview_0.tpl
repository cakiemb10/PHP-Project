<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
	<meta http-equiv="content-type" content="text/html;charset=EUC-JP">
	<meta http-equiv="Content-Style-Type" content="text/css">
	<meta http-equiv="Content-Script-Type" content="text/javascript">
	<title>店舗案内</title>
	<link href="{rval D_DIR_COMPANY}css/default.css" rel="stylesheet" type="text/css">
	<link href="{rval D_DIR_COMPANY}css/layout.css"  rel="stylesheet" type="text/css" media="screen,print">
	<link href="{rval D_DIR_COMPANY}css/base.css"    rel="stylesheet" type="text/css" media="screen,print">
	<link href="{rval D_DIR_COMPANY}css/print.css"   rel="stylesheet" type="text/css" media="print">
<link href="{rval D_DIR_COMPANY}common/css/reset.css"  rel="stylesheet" type="text/css" media="screen,print">
<link href="{rval D_DIR_COMPANY}common/css/cmn.css"  rel="stylesheet" type="text/css" media="screen,print">
	<link href="{rval D_DIR_COMPANY}css/custom.css"  rel="stylesheet" type="text/css" media="screen,print">
	<!--{each css}-->
	<link href="{rval css/src}" type="text/css" rel="stylesheet" media="all">
	<!--{/each}-->
	<!--{each js}-->
	<script charset="{rval js/charset}" type="text/javascript" src="{rval js/src}"></script>
	<!--{/each}-->
<script type="text/JavaScript">
<!--
function MM_findObj(n, d) { //v4.01
var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
if(!x && d.getElementById) x=d.getElementById(n); return x;
}

function MM_showHideLayers() { //v6.0
var i,p,v,obj,args=MM_showHideLayers.arguments;
for (i=0; i<(args.length-2); i+=3) if ((obj=MM_findObj(args[i]))!=null) { v=args[i+2];
if (obj.style) { obj=obj.style; v=(v=='show')?'visible':(v=='hide')?'hidden':v; }
obj.visibility=v; }
}

//-->
</script>
<script charset="EUC-JP" type="text/javascript" src="{rval D_DIR_COMPANY}js/custom.js"></script>
</head>
<body onload="{rval _jsInit}">

<a name="top" id="top"></a>

<div id="bg_all">
<div id="bg_top">
<div id="bg_lb"><img src="{rval D_DIR_COMPANY}common/img/bg_top_lb.png" width="300" height="305" alt="" /></div>
<div id="bg_rb"><img src="{rval D_DIR_COMPANY}common/img/bg_top_rb.png" width="200" height="201" alt="" /></div>
<div id="wrap">

	<div id="custrightarea">
		<div id="logo">
		<p><a href="http://www.hanayayohei.co.jp/index.html"><img src="{rval D_DIR_COMPANY}common/img/logo_hanaya.gif" width="160" height="74" alt="華屋与兵衛" /></a></p>
		</div><!-- logo end -->
		<div id="headnav">
		<ul>
		<li class="line"><a href="{rval D_DIR_BASE}"><img src="{rval D_DIR_COMPANY}common/img/headnav01.gif" width="124" height="50" alt="店舗一覧" class="Hover01" /></a></li>
		<li class="line"><a href="http://jobs.hanayayohei.co.jp" target="_blank"><img src="{rval D_DIR_COMPANY}common/img/headnav02.gif" width="152" height="50" alt="スタッフ募集" class="Hover01" /></a></li>
		<li class="line"><a href="http://www.hanayayohei.co.jp/recruit/site/index.html" target="_blank"><img src="{rval D_DIR_COMPANY}common/img/headnav03.gif" width="129" height="50" alt="採用情報" class="Hover01" /></a></li>
		<li><a href="http://www.hanayayohei.co.jp/shokuzai/index.html"><img src="{rval D_DIR_COMPANY}common/img/headnav04.gif" width="180" height="50" alt="食材こだわり情報" class="Hover01" /></a></li>
		</ul>
		</div><!-- headnav end -->

		<div class="main"><!-- InstanceBeginEditable name="コンテンツエリア" -->

			<div id="wrapper">
