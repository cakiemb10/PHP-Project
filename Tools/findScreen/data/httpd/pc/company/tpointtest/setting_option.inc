<?PHP
//��Ĵ����

$D_MSG_SEARCH_MAXPAGE["ShopW"] = "������̤� 100 ���Ķ�������ɽ�����Ǥ��ޤ���Τǡ�<br>�������Ƥ��Ѥ��ƺ��ٸ������Ƥ���������<br>";

// �ѥ󤯤��ѥȥåץ��
$D_HISTORY_TOP_LINK = "location.href='../asp/$cid/?myar=e&p_s2=".urlencode(str_replace(" ", "+", $p_s2))."&lm=".urlencode(str_replace(" ", "+", $lm))."';";

// My���ꥢ���ѥե饰
$D_MYAREA_USE = 1;

// ������쥯����URL
if (ereg('test', $cid)) {
	$D_REDIRECT_TOP_URL = "https://stg.tsite.jp/t-map/index.pl";
} else {
	$D_REDIRECT_TOP_URL = "https://tsite.jp/t-map/index.pl";
}

// New��������Ƚ�ꥫ���
// ������ˡ��col��NAME������ꥹ�Ȥ�ɽ��������ܤι��֡�
//$D_NEW_ICON_COL = "col4";

//�ѥ󤯤�TOP���
$D_HISTORY_TOP_NAME = "��Ź����TOP";

// �����ݥ�ͭ�ꥢ������
$D_ICON_NEW_IMG = "{$D_DIR_COMPANY}images/coupon-02.gif";

// My���ꥢɽ����ե饰
$D_SELECTED_MYAREA_ID = 0;

//--------------------------------------------
// �Ͽ޽̼�
//--------------------------------------------
//���ָ��������
//��-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
$D_INIT_LVL_SEARCH = -1;
//�ܺ������
//��-1�����ɽ������$D_INIT_LVL�˽स����ɽ�����ϸ��̼ܤΤޤޡ�
$D_INIT_LVL_DETAIL = -1;
//��������
//��-1��$D_INIT_LVL�˽स���
$D_INIT_LVL_PRINT  = -1;

//--------------------------------------------
//��������
//--------------------------------------------
//�������̤ǺǴ��������������ɽ�����뤫��0��ɽ�����ʤ���1��ɽ�������
$D_SHOP_PRINT_SEARCH = 1;

//--------------------------------------------
//�������
//--------------------------------------------
//����ꥹ�ȡ��إꥹ�Ȥǥ��ʹʤ���ߤ���ѡ�0�����Ѥ��ʤ���1�����Ѥ����
$D_SEARCH_KANA = 1;

//--------------------------------------------
//������̡ʥơ��֥�����ˤΥ쥤�����Ⱦ���
//--------------------------------------------
//���
//������������ѹ�������硢search_table.tpl��search_addrtable.tpl��HTML��Ĵ������ɬ�פ�����ޤ���
$D_SEARCH_TABLE_COLS = 3;
//�Կ�
$D_SEARCH_TABLE_ROWS = 8;
//���ڡ�����ɽ������ʢ��Խ��Բġ�
$D_SEARCH_TABLE_PAGE = $D_SEARCH_TABLE_COLS * $D_SEARCH_TABLE_ROWS;

//--------------------------------------------
// �᤭�Ф�
//--------------------------------------------
// �᤭�Ф�������0001�ʾ���
// ��������0000����ˤˤ�����ϡ������ιԤ����EOF;�פιԤޤǤ򥳥��ȥ����Ȥ��Ƥ�������
//if(!isset($D_JSCODE_MSGSHOP)) $D_JSCODE_MSGSHOP = <<< EOF
//	ZdcEmapMsg.setImage('{$D_DIR_BASE}img/msg/0001.png',new ZdcSize(223,125),
//	                    '{$D_DIR_BASE}img/msg/0001-t.png',new ZdcSize(194,67),
//	                    '{$D_DIR_BASE}img/msg/0001-x.png',new ZdcSize(13,13),
//	                    '{$D_DIR_BASE}img/msg/0001-s.png',new ZdcSize(295,144),
//	                    '{$D_DIR_BASE}img/msg/0001-p.gif');
//	ZdcEmapMsg.setDocPosition(0,0,11,8,11,205,55,0);
//	ZdcEmapMsg.setDocOffset(0,-125);
//	ZdcEmapMsg.setTextClass("UserMsgWindowTextStyle");
//EOF;

?>