<?php
include_once('css_func.inc');
/*==========================================================================

��ư�׻�����

============================================================================*/
/*--------------------------------------------------------*/
/* �����Τ�����#wrapper�� */
/* ����;��ʬ�򺹤������ޤ� */
$CSS_VAL['MAIN_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['MAIN_PAD_L']
	.","
	."-".$CSS_VAL['MAIN_PAD_R']
);
/*--------------------------------------------------------*/
/* ����������ʥѥ󤯤��� */
/* �� */
/* ���Ρ�#wrapper�ˤ����˹�碌�ޤ��� */
$CSS_VAL['HIS_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['HIS_WAKU_L_W']
	.","
	."-".$CSS_VAL['HIS_WAKU_R_W']
	.","
	."-".$CSS_VAL['HIS_PAD_L']
	.","
	."-".$CSS_VAL['HIS_PAD_R']
);
/*--------------------------------------------------------*/
/* �������ꥢ���� */
/* �Ͽޤ����˹�碌�ޤ��� */
$CSS_VAL['LEFT_W'] = css_add_sizeval(
	$CSS_VAL['ZDCMAP_W'],
	$CSS_VAL['ZDCMAP_WAKU_L_W']
	.","
	.$CSS_VAL['ZDCMAP_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* �������ꥢ���� */
/* �����������Ͽޤ�����;�����������ޤ� */
$CSS_VAL['RIGHT_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['ZDCMAP_W']
	.","
	."-".$CSS_VAL['ZDCMAP_WAKU_L_W']
	.","
	."-".$CSS_VAL['ZDCMAP_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* ���Ͽޱ��������󥯤Υ��ꥢ */
/* �� */
/* �Ͽޤ����˹�碌�ޤ��� */
$CSS_VAL['MAPRULE_W'] = css_add_sizeval(
	$CSS_VAL['ZDCMAP_W'],
	$CSS_VAL['ZDCMAP_WAKU_L_W']
	.","
	.$CSS_VAL['ZDCMAP_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* �������ʤ���߾�� */
/* �� */
/* �Ͽޤ����˹�碌�ޤ��� */
$CSS_VAL['COND_W'] = css_add_sizeval(
	$CSS_VAL['ZDCMAP_W'],
	$CSS_VAL['ZDCMAP_WAKU_L_W']
	.","
	.$CSS_VAL['ZDCMAP_WAKU_R_W']
	.","
	."-".$CSS_VAL['COND_WAKU_L_W']
	.","
	."-".$CSS_VAL['COND_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* �����ջ��߹ʤ���߾�� */
/* �� */
/* �Ͽޤ����˹�碌�ޤ��� */
$CSS_VAL['JNR_W'] = css_add_sizeval(
	$CSS_VAL['ZDCMAP_W'],
	$CSS_VAL['ZDCMAP_WAKU_L_W']
	.","
	.$CSS_VAL['ZDCMAP_WAKU_R_W']
	.","
	."-".$CSS_VAL['JNR_WAKU_L_W']
	.","
	."-".$CSS_VAL['JNR_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* �������ܺ١ʵ���̾ɽ������ */
/* �� */
/* �����������Ͽޤ�����;�����������ޤ� */
$CSS_VAL['KYODTL_NM_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['ZDCMAP_W']
	.","
	."-".$CSS_VAL['ZDCMAP_WAKU_L_W']
	.","
	."-".$CSS_VAL['ZDCMAP_WAKU_R_W']
	.","
	."-".$CSS_VAL['MAR_MAP_KYODTL']
	.","
	."-".$CSS_VAL['KYODTL_NM_PAD_L']
	.","
	."-".$CSS_VAL['KYODTL_NM_PAD_R']
	.","
	."-".$CSS_VAL['KYODTL_NM_WAKU_L_W']
	.","
	."-".$CSS_VAL['KYODTL_NM_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* �������ܺ٥ǡ����� */
/* �� */
/* ����̾�֥��å������˹�碌�ޤ��� */
$CSS_VAL['KYODTL_DT_W'] = css_add_sizeval(
	$CSS_VAL['KYODTL_NM_W'],
	$CSS_VAL['KYODTL_NM_WAKU_L_W']
	.","
	.$CSS_VAL['KYODTL_NM_WAKU_R_W']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_L']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_R']
	.","
	."-".$CSS_VAL['KYODTL_DT_WAKU_L_W']
	.","
	."-".$CSS_VAL['KYODTL_DT_WAKU_R_W']
);
/* �������ܺ١ʷ���URL�ƥ����ȥܥå����� */
/* �� */
$CSS_VAL['KYODTL_DT_MURL_W'] = css_add_sizeval(
	$CSS_VAL['KYODTL_DT_W'],
	"-".$CSS_VAL['KYODTL_DT_INM_W']
	.","
	."-".$CSS_VAL['KYODTL_DT_PAD_L']
	.","
	."-".$CSS_VAL['KYODTL_DT_PAD_R']
);
/*--------------------------------------------------------*/
/* ��������̰����ڱإꥹ�ȡ����ߥꥹ�ȡ� */
/* ��Safari��margin�ʲ��� */
$CSS_VAL['SAF_SRCH_TBL_MAR_B'] = css_add_sizeval(
	$CSS_VAL['SRCH_TBL_WAKU_W'],
	"2px"
);
/*--------------------------------------------------------*/
/* ���Ǵ��������� */
/* �� */
/* �����ܺ٤����˹�碌�ޤ��� */
$CSS_VAL['KYOLIST_W'] = css_add_sizeval(
	$CSS_VAL['KYODTL_NM_W'],
	$CSS_VAL['KYODTL_NM_WAKU_L_W']
	.","
	.$CSS_VAL['KYODTL_NM_WAKU_R_W']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_L']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_R']
	.","
	."-".$CSS_VAL['KYOLIST_WAKU_L_W']
	.","
	."-".$CSS_VAL['KYOLIST_WAKU_R_W']
);
/* �����ʲ������� */
/* �����ʲ��ˤ����ٹԷ�������蘆�ä������ʤäƤ��ޤ��Τǡ����������򸺻����ޤ�����IE,FF�� */
/* â����Safari�Ǥϼ�ưĴ�������פʤ��ᡢ���ѿ������򤷤Ƥ����ޤ��� */
$CSS_VAL['SAF_KYOLIST_WAKU_B_W'] = $CSS_VAL['KYOLIST_WAKU_B_W'];
$CSS_VAL['KYOLIST_WAKU_B_W'] = css_add_sizeval(
	$CSS_VAL['KYOLIST_WAKU_B_W'],
	"-".$CSS_VAL['KYOLIST_D_KEI_W']
);
/*--------------------------------------------------------*/
/* ���Ǵ��ذ��� */
/* �� */
/* �����ܺ٤����˹�碌�ޤ��� */
$CSS_VAL['NEKI_W'] = css_add_sizeval(
	$CSS_VAL['KYODTL_NM_W'],
	$CSS_VAL['KYODTL_NM_WAKU_L_W']
	.","
	.$CSS_VAL['KYODTL_NM_WAKU_R_W']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_L']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_R']
	.","
	."-".$CSS_VAL['NEKI_WAKU_L_W']
	.","
	."-".$CSS_VAL['NEKI_WAKU_R_W']
);
/* �����ʲ������� */
/* �����ʲ��ˤ����ٹԷ�������蘆�ä������ʤäƤ��ޤ��Τǡ����������򸺻����ޤ�����IE,FF�� */
/* â����Safari�Ǥϼ�ưĴ�������פʤ��ᡢ���ѿ������򤷤Ƥ����ޤ��� */
$CSS_VAL['SAF_NEKI_WAKU_B_W'] = $CSS_VAL['NEKI_WAKU_B_W'];
$CSS_VAL['NEKI_WAKU_B_W'] = css_add_sizeval(
	$CSS_VAL['NEKI_WAKU_B_W'],
	"-".$CSS_VAL['NEKI_D_KEI_W']
);
/*--------------------------------------------------------*/
/* �����ջ��߰��� */
/* �� */
/* �����ܺ٤����˹�碌�ޤ��� */
$CSS_VAL['NPOI_W'] = css_add_sizeval(
	$CSS_VAL['KYODTL_NM_W'],
	$CSS_VAL['KYODTL_NM_WAKU_L_W']
	.","
	.$CSS_VAL['KYODTL_NM_WAKU_R_W']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_L']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_R']
	.","
	."-".$CSS_VAL['NPOI_WAKU_L_W']
	.","
	."-".$CSS_VAL['NPOI_WAKU_R_W']
);
/* �����ʲ������� */
/* �����ʲ��ˤ����ٹԷ�������蘆�ä������ʤäƤ��ޤ��Τǡ����������򸺻����ޤ�����IE,FF�� */
/* â����Safari�Ǥϼ�ưĴ�������פʤ��ᡢ���ѿ������򤷤Ƥ����ޤ��� */
$CSS_VAL['SAF_NPOI_WAKU_B_W'] = $CSS_VAL['NPOI_WAKU_B_W'];
$CSS_VAL['NPOI_WAKU_B_W'] = css_add_sizeval(
	$CSS_VAL['NPOI_WAKU_B_W'],
	"-".$CSS_VAL['NPOI_D_KEI_W']
);
/* ��Υ���������� */
$CSS_VAL['NPOI_EXP_W'] = css_add_sizeval(
	$CSS_VAL['NPOI_W'],
	$CSS_VAL['NPOI_WAKU_L_W']
	.","
	.$CSS_VAL['NPOI_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* ����ȯ�Ϥ���ꤷ�ƥ롼��õ�� */
/* �� */
/* �����ܺ٤����˹�碌�ޤ��� */
$CSS_VAL['FROUTE_W'] = css_add_sizeval(
	$CSS_VAL['KYODTL_NM_W'],
	$CSS_VAL['KYODTL_NM_WAKU_L_W']
	.","
	.$CSS_VAL['KYODTL_NM_WAKU_R_W']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_L']
	.","
	.$CSS_VAL['KYODTL_NM_PAD_R']
	.","
	."-".$CSS_VAL['FROUTE_WAKU_L_W']
	.","
	."-".$CSS_VAL['FROUTE_WAKU_R_W']
);
/* �����ʲ������� */
/* �����ʲ��ˤ����ٹԷ�������蘆�ä������ʤäƤ��ޤ��Τǡ����������򸺻����ޤ�����IE,FF�� */
/* â����Safari�Ǥϼ�ưĴ�������פʤ��ᡢ���ѿ������򤷤Ƥ����ޤ��� */
//$CSS_VAL['SAF_FROUTE_WAKU_B_W'] = $CSS_VAL['FROUTE_WAKU_B_W'];
//$CSS_VAL['FROUTE_WAKU_B_W'] = css_add_sizeval(
//	$CSS_VAL['FROUTE_WAKU_B_W'],
//	"-".$CSS_VAL['FROUTE_D_KEI_W']
//);
/* �������ϥܥå������� */
$CSS_VAL['FROUTE_SRCH_ENT_TXT_W'] = css_add_sizeval(
	$CSS_VAL['FROUTE_W'],
	"-".$CSS_VAL['FROUTE_SRCH_PAD_L']
	.","
	."-".$CSS_VAL['FROUTE_SRCH_PAD_R']
	.","
	."-60px"
);
/*--------------------------------------------------------*/
/* ���������̡ʵ���̾�� */
/* �� */
$CSS_VAL['PR_NM_W'] = css_add_sizeval(
	$CSS_VAL['PR_W'],
	"-".$CSS_VAL['PR_NM_WAKU_L_W']
	.","
	."-".$CSS_VAL['PR_NM_WAKU_R_W']
	.","
	."-".$CSS_VAL['PR_NM_PAD_L']
	.","
	."-".$CSS_VAL['PR_NM_PAD_R']
);
/*--------------------------------------------------------*/
/* ���������� ���٤������ʲ��� */
/* �����ʲ��ˤ����ٹԷ�������蘆�ä������ʤäƤ��ޤ��Τǡ����������򸺻����ޤ�����IE,FF�� */
/* â����Safari�Ǥϼ�ưĴ�������פʤ��ᡢ���ѿ������򤷤Ƥ����ޤ��� */
$CSS_VAL['SAF_PR_DTL_WAKU_B_W'] = $CSS_VAL['PR_DTL_WAKU_B_W'];
$CSS_VAL['PR_DTL_WAKU_B_W'] = css_add_sizeval(
	$CSS_VAL['PR_DTL_WAKU_B_W'],
	"-".$CSS_VAL['PR_DTL_KEI_W']
);
/*--------------------------------------------------------*/
/* ���������� ���٤��� */
$CSS_VAL['PR_DTL_W'] = css_add_sizeval(
	$CSS_VAL['PR_W'],
	"-".$CSS_VAL['PR_DTL_WAKU_L_W']
	.","
	."-".$CSS_VAL['PR_DTL_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* ���������� �Ͽޤ��� */
$CSS_VAL['PR_MAP_W'] = css_add_sizeval(
	$CSS_VAL['PR_W'],
	"-".$CSS_VAL['PR_MAP_WAKU_L_W']
	.","
	."-".$CSS_VAL['PR_MAP_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* ���������̤ι⤵ */
if ($CSS_VAL['MAIN_H']) {
	$CSS_VAL['SRCH_WIN_H'] = '100%';
} else {
	$CSS_VAL['SRCH_WIN_H'] = '9999px';
}
/*--------------------------------------------------------*/
/* ���������� �����ȥ�ʡֵ��������סˤ��� */
$CSS_VAL['SRCH_TTL_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['SRCH_TTL_WAKU_L_W']
	.","
	."-".$CSS_VAL['SRCH_TTL_WAKU_R_W']
	.","
	."-".$CSS_VAL['SRCH_TTL_PAD_L']
	.","
	."-".$CSS_VAL['SRCH_TTL_PAD_R']
);
/*--------------------------------------------------------*/
/* ���������� �����Ͽ޲��� */
	/* �� */
	$CSS_VAL['SRCH_JMAP_W'] =			'355px';
	/* �⤵ */
	$CSS_VAL['SRCH_JMAP_H'] =			'304px';
/*--------------------------------------------------------*/
/* ���������� ��¦���� */
$CSS_VAL['SRCH_LEFT_W'] = css_add_sizeval(
	$CSS_VAL['SRCH_JMAP_W'],
	$CSS_VAL['SRCH_JMAP_WAKU_W']
	.","
	.$CSS_VAL['SRCH_JMAP_WAKU_W']
);
/* ���������� ���롼�ץ����ȥ�ʺ�¦�ˤ��� */
$CSS_VAL['SRCH_GRPTTL_L_W'] = css_add_sizeval(
	$CSS_VAL['SRCH_LEFT_W'],
	"-".$CSS_VAL['SRCH_GRPTTL_WAKU_L_W']
	.","
	."-".$CSS_VAL['SRCH_GRPTTL_WAKU_R_W']
	.","
	."-".$CSS_VAL['SRCH_GRPTTL_PAD_L']
	.","
	."-".$CSS_VAL['SRCH_GRPTTL_PAD_R']
);
/* ���������� ��¦���� */
$CSS_VAL['SRCH_RIGHT_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['SRCH_LEFT_W']
	.","
	."-".$CSS_VAL['SRCH_MAR_CENTER']
);
/* ���������� ���롼�ץ����ȥ�ʱ�¦�ˤ��� */
$CSS_VAL['SRCH_GRPTTL_R_W'] = css_add_sizeval(
	$CSS_VAL['SRCH_RIGHT_W'],
	"-".$CSS_VAL['SRCH_GRPTTL_WAKU_L_W']
	.","
	."-".$CSS_VAL['SRCH_GRPTTL_WAKU_R_W']
	.","
	."-".$CSS_VAL['SRCH_GRPTTL_PAD_L']
	.","
	."-".$CSS_VAL['SRCH_GRPTTL_PAD_R']
);
/* ���������� �ʤ���߾����� */
$CSS_VAL['SRCH_COND_W'] = css_add_sizeval(
	$CSS_VAL['MAIN_W'],
	"-".$CSS_VAL['COND_WAKU_L_W']
	.","
	."-".$CSS_VAL['COND_WAKU_R_W']
);
/*--------------------------------------------------------*/
/* ���ʤ���߾������å��ܥå���������˱�����TD�� */
$CSS_VAL['COND_CB_TD_W'] = "33%";
if ($oDEmapConf->OPT_10_10) {
	$CSS_VAL['COND_CB_TD_W'] = floor(100 / $oDEmapConf->OPT_10_10)."%";
}
/* ���ʤ���߾��ꥹ�ȥܥå���������˱�����TD�� */
$CSS_VAL['COND_LB_TD_W'] = "100%";
if ($oDEmapConf->OPT_10_12) {
	$CSS_VAL['COND_LB_TD_W'] = floor(100 / $oDEmapConf->OPT_10_12)."%";
}
/*--------------------------------------------------------*/
/* ���ʤ���߾������å��ܥå���������˱�����TD�� */
$CSS_VAL['SRCH_COND_CB_TD_W'] = "20%";
if ($oDEmapConf->OPT_10_11) {
	$CSS_VAL['SRCH_COND_CB_TD_W'] = floor(100 / $oDEmapConf->OPT_10_11)."%";
}
/* ���ʤ���߾��ꥹ�ȥܥå���������˱�����TD�� */
$CSS_VAL['SRCH_COND_LB_TD_W'] = "33%";
if ($oDEmapConf->OPT_10_13) {
	$CSS_VAL['SRCH_COND_LB_TD_W'] = floor(100 / $oDEmapConf->OPT_10_13)."%";
}

?>