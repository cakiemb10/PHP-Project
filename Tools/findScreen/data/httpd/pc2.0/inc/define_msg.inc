<?php
// ------------------------------------------------------------
// ����ե����� �Ƽ��å�����
// 
// ��ȯ����
// 2007/03/01 bando@D&I
//     ������ȯ
// 2009/08/24 Y.Matsukawa	IP����
// 2010/07/20 Y.Matsukawa	SSL�б�
// 2011/06/16 H.osamoto		�ե꡼���ʣ�縡����å������ɲ�
// ------------------------------------------------------------
//��������³ -----------------------------------------------
if(!isset($D_MSG_EMAPVIEW_NOKID)) $D_MSG_EMAPVIEW_NOKID = "���ꤵ�줿".$D_USER_DEFNAME."��¸�ߤ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOSEARVICE)) $D_MSG_EMAPVIEW_NOSEARVICE = "���ꤵ�줿�ڡ�����ɽ�����Ǥ��ޤ���Ǥ�����<br>�ʥ����ӥ����Ѵ��֤��᤮�Ƥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOCID)) $D_MSG_EMAPVIEW_NOCID = "���ꤵ�줿�ڡ�����ɽ�����Ǥ��ޤ���Ǥ�����<br>��cid����Ͽ����Ƥ��ޤ����";
if(!isset($D_MSG_EMAPVIEW_NOREFERER)) $D_MSG_EMAPVIEW_NOREFERER  = "�������������Ĥ���Ƥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOPRM)) $D_MSG_EMAPVIEW_NOPRM      = "�ѥ�᡼���������Ǥ�";
if(!isset($D_MSG_EMAPVIEW_ERRPRM)) $D_MSG_EMAPVIEW_ERRPRM     = "�ѥ�᡼���������Ǥ�";
if(!isset($D_MSG_EMAPVIEW_NGBROWSER)) $D_MSG_EMAPVIEW_NGBROWSER = "����������ޤ��󤬡����Ȥ��Υ֥饦���Ǥϡ��ڡ�����ɽ�����뤳�Ȥ��Ǥ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_INVALIDIP)) $D_MSG_EMAPVIEW_INVALIDIP  = "�������������Ĥ���Ƥ��ޤ���";		// add 2009/08/24 Y.Matsukawa
if(!isset($D_MSG_EMAPVIEW_HTTPS)) $D_MSG_EMAPVIEW_HTTPS = "�������������Ĥ���Ƥ��ޤ���";		// add 2010/07/20 Y.Matsukawa
if(!isset($D_MSG_EMAPVIEW_HTTP)) $D_MSG_EMAPVIEW_HTTP = "�������������Ĥ���Ƥ��ޤ���";			// add 2010/07/20 Y.Matsukawa


//���ָ��� -------------------------------------------------
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
//͹���ֹ�ե꡼���
if(!isset($D_MSG_SEARCH_NODATA["ZipW"])) $D_MSG_SEARCH_NODATA["ZipW"] = "��������͹���ֹ椬����ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["ZipW"])) $D_MSG_SEARCH_NULL["ZipW"] = "͹���ֹ�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_LENGTH["ZipW"])) $D_MSG_SEARCH_LENGTH["ZipW"] = "͹���ֹ�򣷷�����Ϥ��Ʋ�������";
//�����ե꡼���
if(!isset($D_MSG_SEARCH_NODATA["ShopW"])) $D_MSG_SEARCH_NODATA["ShopW"] = "��������".$D_USER_DEFNAME."̾������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopW"])) $D_MSG_SEARCH_NULL["ShopW"] = $D_USER_DEFNAME."̾�����Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopW"])) $D_MSG_SEARCH_MAXPAGE["ShopW"] = "��������".$D_USER_DEFNAME."̾��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
// add 2011/06/16 H.osamoto [
//�ե꡼���ʣ�縡��
if(!isset($D_MSG_SEARCH_NULL["Comb"])) $D_MSG_SEARCH_NULL["Comb"] = "�ե꡼��ɤ����Ϥ��Ƥ���������";
// add 2011/06/16 H.osamoto ]
//����ꥹ��
if(!isset($D_MSG_SEARCH_NODATA["AddrL"])) $D_MSG_SEARCH_NODATA["AddrL"] = "����������󤬤���ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//�إꥹ��
if(!isset($D_MSG_SEARCH_NODATA["StL"])) $D_MSG_SEARCH_NODATA["StL"] = "����������󤬤���ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//���ߥꥹ��
if(!isset($D_MSG_SEARCH_NODATA["PoiL"])) $D_MSG_SEARCH_NODATA["PoiL"] = "����������󤬤���ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//�����ꥹ��
if(!isset($D_MSG_SEARCH_NODATA["ShopA"])) $D_MSG_SEARCH_NODATA["ShopA"] = "����������󤬤���ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//����¾
if(!isset($D_MSG_SEARCH_ERRPRM)) $D_MSG_SEARCH_ERRPRM    = "�ѥ�᡼���������Ǥ�";


//�Ͽ޲��� -------------------------------------------------
//�Ǵ����
if(!isset($D_MSG_NKYOTEN_NOLIST)) $D_MSG_NKYOTEN_NOLIST = "�Ǵ�".$D_USER_DEFNAME."������ޤ���Ǥ���";
if(!isset($D_MSG_NPOI_NOLIST)) $D_MSG_NPOI_NOLIST = "�Ͽ���˳������ߤ�����ޤ���Ǥ���";
if(!isset($D_MSG_NEKI_NOLIST)) $D_MSG_NEKI_NOLIST = "�Ǵ�ؤ�����ޤ���Ǥ���";



//����¾ ---------------------------------------------------
if(!isset($D_MSG_ERR)) $D_MSG_ERR            = "ͽ�����ʤ����顼��ȯ�����ޤ���";
if(!isset($D_MSG_ERR_JS_REQUEST)) $D_MSG_ERR_JS_REQUEST = "����������ޤ����������Ѻ��߹�äƤ���ޤ���TOP�ڡ�������ꤷ�Ф餯���֤��֤��Ƥ��餴���Ѥ�������";
if(!isset($D_MSG_ERR_JS_RESULT)) $D_MSG_ERR_JS_RESULT  = "�����˼��Ԥ��ޤ���";
if(!isset($D_MSG_ERR_JS_ROUTE)) $D_MSG_ERR_JS_ROUTE   = "��Υ��Ĺ�����뤫õ���˼��Ԥ��ޤ�����";
?>