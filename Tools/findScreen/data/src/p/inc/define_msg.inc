<?php
// ------------------------------------------------------------
// ����ե����� �Ƽ��å�����
// 
// ��ȯ����
// 2011/10/15 Y.Matsukawa	��������
// 2012/02/27 Y.Matsukawa	Ź������ꥹ�Ȳ���
// 2013/09/24 Y.Matsukawa	�����ե꡼��ɡʴ������ס˸���
// 2014/12/11 Y.Matsukawa	��������ʵ����˰�������
// 2015/04/09 F.Yokoi		�롼�ȸ��� ��ԼԢ���ư�֤ؤ����ؤ򥢥顼��ɽ������ݤ�ʸ�����ѿ����ɲ�
// 2016/02/03 N.Wada		GPS���顼��å������򥫥����ޥ�����ǽ��
// ------------------------------------------------------------
//��������³ -----------------------------------------------
if(!isset($D_MSG_EMAPVIEW_NOKID)) $D_MSG_EMAPVIEW_NOKID = "���ꤵ�줿".$D_USER_DEFNAME."��¸�ߤ��ޤ���";
if(!isset($D_MSG_EMAPVIEW_NOSERVICE)) $D_MSG_EMAPVIEW_NOSERVICE = "���ꤵ�줿�ڡ�����ɽ�����Ǥ��ޤ���Ǥ�����<br>�ʥ����ӥ����Ѵ��֤��᤮�Ƥ��ޤ���";
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
//�����ե꡼��ɡʴ������ס�		add 2013/09/24 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["ShopM"])) $D_MSG_SEARCH_NODATA["ShopM"] = "��������".$D_USER_DEFNAME."������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
if(!isset($D_MSG_SEARCH_NULL["ShopM"])) $D_MSG_SEARCH_NULL["ShopM"] = "�����������Ϥ��Ƥ���������";
if(!isset($D_MSG_SEARCH_MAXPAGE["ShopM"])) $D_MSG_SEARCH_MAXPAGE["ShopM"] = "��������".$D_USER_DEFNAME."��¿������<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
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
//��������ꥹ��		add 2012/02/27 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["KL"])) $D_MSG_SEARCH_NODATA["KL"] = "��������".$D_SHOP_NAME."������ޤ���Ǥ�����<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";
//��������ꥹ��		add 2014/12/11 Y.Matsukawa
if(!isset($D_MSG_SEARCH_NODATA["KLCK"])) $D_MSG_SEARCH_NODATA["KLCK"] = "��¸����Ƥ����������Ϥ���ޤ���";
//����¾
if(!isset($D_MSG_SEARCH_ERRPRM)) $D_MSG_SEARCH_ERRPRM    = "�ѥ�᡼���������Ǥ�";
//GPS����		add 2016/02/03 N.Wada
if(!isset($D_MSG_GPS_ERRPRM)) $D_MSG_GPS_ERRPRM = "�����Ϥμ����˼��Ԥ��ޤ���";


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
if(!isset($D_MSG_ERR_SEARCH_WALK_ALERT)) $D_MSG_ERR_SEARCH_WALK_ALERT = ""; // add 2015/04/09 F.Yokoi
?>