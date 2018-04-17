{rval midashi}<!--{def page}-->({rval now_page}/{rval max_page})<!--{/def}--><BR>
{rval head_sparater}
<!--{def list_midashi}-->{rval list_midashi}<br><!--{/def}-->
<!--{def SEARCH_TITLE}-->{rval SEARCH_TITLE}<br><!--{/def}-->
<!--{def errmsg}-->{rval errmsg}<br><!--{/def}-->
<!--{def nearlink}--><a href="{rval nearlink}">{rval nearname}</a><br><!--{/def}-->
<!--{def filter}-->{rval filter}
<!--{ndef P_STRING_10}-->※店舗名は複数のキーワードをスペース（空白）で区切って検索することができます。<br><br><!--{/ndef}-->
<!--{/def}-->
<!--{def page}-->{rval icon_pre}<A href = "{rval pre_link}">{rval pre_name}</a><!--{/def}-->
<!--{def page}-->{rval separator}<!--{/def}-->
<!--{def page}-->{rval icon_next}<A href = "{rval next_link}">{rval next_name}</a><!--{/def}-->
<!--{def page}--><BR><!--{/def}-->
<!--{each listdata/data}-->
{rval listdata/data/icon_no}<!--{def listdata/data/COL_02}--><a href="{rval listdata/data/url}" {rval listdata/data/access_key}>{rval listdata/data/COL_02}<br></a>&nbsp;&nbsp;<!--{/def}-->
<a href="{rval listdata/data/url}" {rval listdata/data/access_key}>{rval listdata/data/name}</a><!--{def listdata/data/rosen}-->{rval listdata/data/rosen}<!--{/def}--><br>
<!--{def showcolonlist}-->
<!--{def listdata/data/COL_02}-->{rval listdata/data/COL_02}<BR><!--{/def}-->
<!--{def listdata/data/ADDR}-->{rval listdata/data/ADDR}<BR><!--{/def}-->
<!--{def listdata/data/COL_01}-->{rval listdata/data/COL_01}<BR><!--{/def}-->
<!--{def listdata/data/COL_01}-->{rval listdata/data/COL_01}<BR><!--{/def}-->
<!--{/def}-->
<!--{/each}-->
<!--{def page}-->{rval icon_pre}<A href = "{rval pre_link}">{rval pre_name}</a><!--{/def}-->
<!--{def page}-->{rval separator}<!--{/def}-->
<!--{def page}-->{rval icon_next}<A href = "{rval next_link}">{rval next_name}</a><!--{/def}-->
<!--{def page}--><BR><!--{/def}-->
<!--{def WARNING_TITLE}-->{rval WARNING_TITLE}<BR><!--{/def}-->
{rval foot_sparater}
