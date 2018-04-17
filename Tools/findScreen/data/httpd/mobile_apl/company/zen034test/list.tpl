{rval midashi}<!--{def page}-->({rval now_page}/{rval max_page})<!--{/def}--><BR>
{rval head_sparater}
<!--{def list_midashi}-->{rval list_midashi}<br><!--{/def}-->
<!--{def SEARCH_TITLE}-->{rval SEARCH_TITLE}<br><!--{/def}-->
<!--{def errmsg}-->{rval errmsg}<br><!--{/def}-->
<!--{def nearlink}--><a href="{rval nearlink}">{rval nearname}</a><br><!--{/def}-->
<!--{def filter}-->{rval filter}<!--{/def}-->
<!--{def SmartPhone}--><BR><!--{/def}-->
<!--{each listdata/data}-->
<!--{ndef SmartPhone}-->{rval listdata/data/icon_no}<!--{/ndef}-->
<!--{def SmartPhone}-->{rval listdata/data/no}&nbsp;<!--{/def}-->
<a href="{rval listdata/data/url}" {rval listdata/data/access_key}>
	<!--{def listdata/data/icon_id_80}-->²Ú²°Í¿Ê¼±Ò&nbsp;<!--{/def}-->
	<!--{def listdata/data/icon_id_90}-->ÏÂ¿©¤è¤Ø¤¤&nbsp;<!--{/def}-->
	{rval listdata/data/name}</a><!--{def listdata/data/rosen}-->{rval listdata/data/rosen}<!--{/def}--><br>
<!--{def SmartPhone}--><BR><!--{/def}-->
<!--{/each}-->
<!--{def page}-->{rval icon_pre}<A href = "{rval pre_link}">{rval pre_name}</a><!--{/def}-->
<!--{def page}-->{rval separator}<!--{/def}-->
<!--{def page}-->{rval icon_next}<A href = "{rval next_link}">{rval next_name}</a><!--{/def}-->
<!--{def page}--><BR><!--{/def}-->
<!--{def WARNING_TITLE}-->{rval WARNING_TITLE}<BR><!--{/def}-->
{rval foot_sparater}
