<?php
// ------------------------------------------------------------
// ����ե����� �Ƽ��å�����
// 
// 2011/03/10 Y.Matsukawa	��������
// 2011/07/13 Y.Matsukawa	��ǽ�ɲáʥ롼��õ�����Ǵ�ء�
// 2011/08/08 Y.Matsukawa	��ǽ�ɲáʹʤ���߳�ĥ���������ꥢ�������إꥹ�ȸ�����
// 2011/08/15 K.Masuda 		����FW������������Υ�å������ɲ�
// 2012/02/23 Y.Matsukawa	Ź������ꥹ�Ȳ���
// 2012/07/18 Y.Matsukawa	�Ǵ����
// 2012/07/20 Y.Matsukawa	GPS���顼��å������򥫥����ޥ�����ǽ��
// 2017/04/21 N.Wada		ϩ���ե꡼��ɤΥ�å������ɲ�
// ------------------------------------------------------------
//��������³ -----------------------------------------------
if(!isset($D_MSG_EMAPVIEW_NOKID)) $D_MSG_EMAPVIEW_NOKID = "���ꤵ�줿".$D_SHOP_NAME."��¸�ߤ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOSERVICE)) $D_MSG_EMAPVIEW_NOSERVICE = "���ꤵ�줿�ڡ�����ɽ�����Ǥ��ޤ���Ǥ�����<br>�ʥ����ӥ����Ѵ��֤��᤮�Ƥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOCID)) $D_MSG_EMAPVIEW_NOCID = "���ꤵ�줿�ڡ�����ɽ�����Ǥ��ޤ���Ǥ�����<br>��cid����Ͽ����Ƥ��ޤ����";
if(!isset($D_MSG_EMAPVIEW_NOREFERER)) $D_MSG_EMAPVIEW_NOREFERER  = "�������������Ĥ���Ƥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOPRM)) $D_MSG_EMAPVIEW_NOPRM      = "�ѥ�᡼���������Ǥ�";
if(!isset($D_MSG_EMAPVIEW_ERRPRM)) $D_MSG_EMAPVIEW_ERRPRM     = "�ѥ�᡼���������Ǥ�";
if(!isset($D_MSG_EMAPVIEW_NGBROWSER)) $D_MSG_EMAPVIEW_NGBROWSER = "����������ޤ��󤬡����Ȥ��Υ֥饦���Ǥϡ��ڡ�����ɽ�����뤳�Ȥ��Ǥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_INVALIDIP)) $D_MSG_EMAPVIEW_INVALIDIP  = "�������������Ĥ���Ƥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_HTTPS)) $D_MSG_EMAPVIEW_HTTPS = "�������������Ĥ���Ƥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_HTTP)) $D_MSG_EMAPVIEW_HTTP = "�������������Ĥ���Ƥ��ޤ���";	


//���ָ��� -------------------------------------------------
if(!isset($D_MSG_SEARCH_NULL["FW"])) $D_MSG_SEARCH_NULL["FW"] = "��̾�����ꡦ����̾�����Ϥ��ƺ��ٸ������Ƥ���������";
//����ե꡼���
if(!isset($D_MSG_SEARCH_NODATA["AddrW"])) $D_MSG_SEARCH_NODATA["AddrW"] = "�������뽻�꤬����ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["AddrW"])) $D_MSG_SEARCH_NULL["AddrW"] = "��������Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["AddrW"])) $D_MSG_SEARCH_MAXPAGE["AddrW"] = "�������뽻�꤬¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//�إե꡼���
if(!isset($D_MSG_SEARCH_NODATA["StW"])) $D_MSG_SEARCH_NODATA["StW"] = "���������̾������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["StW"])) $D_MSG_SEARCH_NULL["StW"] = "��̾�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["StW"])) $D_MSG_SEARCH_MAXPAGE["StW"] = "���������̾��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//���ߥե꡼���
if(!isset($D_MSG_SEARCH_NODATA["PoiW"])) $D_MSG_SEARCH_NODATA["PoiW"] = "�����������̾������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["PoiW"])) $D_MSG_SEARCH_NULL["PoiW"] = "����̾�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["PoiW"])) $D_MSG_SEARCH_MAXPAGE["PoiW"] = "�����������̾��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//�����ե꡼���
if(!isset($D_MSG_SEARCH_NODATA["ShopW"])) $D_MSG_SEARCH_NODATA["ShopW"] = "��������".$D_SHOP_NAME."̾������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopW"])) $D_MSG_SEARCH_NULL["ShopW"] = $D_SHOP_NAME."̾�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopW"])) $D_MSG_SEARCH_MAXPAGE["ShopW"] = "��������".$D_SHOP_NAME."̾��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
// add 2011/08/15 K.Masuda [
if(!isset($D_MSG_SEARCH_NODATA["ShopW_col"])) $D_MSG_SEARCH_NODATA["ShopW_col"] = "��������".$D_SHOP_NAME_COL."������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopW_col"])) $D_MSG_SEARCH_NULL["ShopW_col"] = $D_SHOP_NAME_COL."�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopW_col"])) $D_MSG_SEARCH_MAXPAGE["ShopW_col"] = "��������".$D_SHOP_NAME_COL."��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
// add 2011/08/15 K.Masuda ]
//ϩ���ե꡼���	add 2017/04/21 N.Wada
if(!isset($D_MSG_SEARCH_NODATA["RoW"])) $D_MSG_SEARCH_NODATA["RoW"] = "��������ϩ��̾������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["RoW"])) $D_MSG_SEARCH_NULL["RoW"] = "ϩ��̾�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["RoW"])) $D_MSG_SEARCH_MAXPAGE["RoW"] = "��������ϩ��̾��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//�����ꥹ��		add 2011/08/08 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["ShopA"])) $D_MSG_SEARCH_NODATA["ShopA"] = "��������".$D_SHOP_NAME."������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//��������ꥹ��		add 2012/02/23 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["KL"])) $D_MSG_SEARCH_NODATA["KL"] = "��������".$D_SHOP_NAME."������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//����ꥹ��
if(!isset($D_MSG_SEARCH_NODATA["AddrL"])) $D_MSG_SEARCH_NODATA["AddrL"] = "����������󤬤���ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//�إꥹ��		add 2011/08/08 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["StL"])) $D_MSG_SEARCH_NODATA["StL"] = "����������󤬤���ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//����¾
if(!isset($D_MSG_SEARCH_ERRPRM)) $D_MSG_SEARCH_ERRPRM    = "�ѥ�᡼���������Ǥ�";
//GPS����		add 2012/07/20 Y.Matsukawa
if(!isset($D_MSG_GPS_ERRPRM)) $D_MSG_GPS_ERRPRM = "�����Ϥμ����˼��Ԥ��ޤ���";

//�Ǵ��		add 2011/07/13 Y.Matsukawa
if(!isset($D_MSG_NEKI_NOLIST)) $D_MSG_NEKI_NOLIST = "�Ǵ��ؤ�����ޤ���Ǥ���";
if(!isset($D_MSG_NEKI_MSG)) $D_MSG_NEKI_MSG = $D_SHOP_NAME."�κǴ��ؤ�ᤤ���ɽ�����Ƥ��ޤ���";
if(!isset($D_MSG_NEKI_COUNT)) $D_MSG_NEKI_COUNT = "��ҥå�";

//�Ǵ����		add 2012/07/18 Y.Matsukawa
if(!isset($D_MSG_NPOI_NOLIST)) $D_MSG_NPOI_NOLIST = "�Ǵ����ߤ�����ޤ���Ǥ���";
if(!isset($D_MSG_NPOI_MSG)) $D_MSG_NPOI_MSG = $D_SHOP_NAME."�κǴ����ߤ�ᤤ���ɽ�����Ƥ��ޤ���";
if(!isset($D_MSG_NPOI_COUNT)) $D_MSG_NPOI_COUNT = "��ҥå�";

//�Ͽ޲��� -------------------------------------------------
//�Ǵ����
if(!isset($D_MSG_NKYOTEN_NOLIST)) $D_MSG_NKYOTEN_NOLIST = "�Ǵ��".$D_SHOP_NAME."������ޤ���Ǥ���";
if(!isset($D_MSG_NKYOTEN_MSG)) $D_MSG_NKYOTEN_MSG = "�κǴ��".$D_SHOP_NAME."��ᤤ���ɽ�����Ƥ��ޤ���";
if(!isset($D_MSG_NKYOTEN_COUNT)) $D_MSG_NKYOTEN_COUNT = "��ҥå�";

// add 2011/07/13 Y.Matsukawa
//�롼�� -------------------------------------------------
if(!isset($D_MSG_ERR_JS_ROUTE)) $D_MSG_ERR_JS_ROUTE   = "�롼��õ���˼��Ԥ��ޤ�����";

//����¾ ---------------------------------------------------
if(!isset($D_MSG_ERR)) $D_MSG_ERR            = "ͽ�����ʤ����顼��ȯ�����ޤ���";
if(!isset($D_MSG_ERR_JS_REQUEST)) $D_MSG_ERR_JS_REQUEST = "����������ޤ����������Ѻ��߹�äƤ���ޤ���TOP�ڡ�������ꤷ�Ф餯���֤��֤��Ƥ��餴���Ѥ�������";
if(!isset($D_MSG_ERR_JS_RESULT)) $D_MSG_ERR_JS_RESULT  = "�����˼��Ԥ��ޤ���";

?>