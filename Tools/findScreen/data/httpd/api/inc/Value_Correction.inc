<?php
// ------------------------------------------------------------
// API�쥹�ݥ󥹤������������
// 
// 2016/12/16 H.Yasunaga	��������
// 2017/01/25 H.Yasunaga	���ִ�����ˡ���������(����ID)��0������������򳰤�
// ------------------------------------------------------------
require_once(dirname(__FILE__) . "/ResponseTag.inc");

	// Ⱦ�Ѳ������о�
	$VALUE_TO_HALF;
	// ��������ӥ������ʤ����Ѳ�
	$VALUE_TO_FULL;
	// �ϥ��ե�ν���(͹���ֹ�)
	$VALUE_TRIM_HYPHEN;
	// 0�����������
	$VALUE_ZERO_CORRECT;
	// ����������� hh:mm:ss �� ss��̵�����ˡ�00�פ��ɲä���
	$VALUE_TIME_CORRECT;

// Ⱦ�Ѳ�	
	$VALUE_TO_HALF = array();
	// ����1:���ִ�����ˡ���������
	$VALUE_TO_HALF[$TAG_ORDER[0]] = true;
	// ����2:�ɽꥳ����
	$VALUE_TO_HALF[$TAG_ORDER[1]] = true;
	// ����3:�谷Ź�ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[2]] = true;
	// ����9:͹���ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[8]] = true;
	// ����12:JIS�Զ�Į¼������
	$VALUE_TO_HALF[$TAG_ORDER[11]] = true;
	// ����14:��־�
	$VALUE_TO_HALF[$TAG_ORDER[13]] = true;
	// ����18:͹�ضɲ�ҥ�ˡ���������
	$VALUE_TO_HALF[$TAG_ORDER[17]] = true;
	// ����22:��������ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[21]] = true;
	// ����23:��̳�����ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[22]] = true;
	// ����24:�䤤��碌FAX
	$VALUE_TO_HALF[$TAG_ORDER[23]] = true;
	// ����26:�椦�椦�����ˡ���������
	$VALUE_TO_HALF[$TAG_ORDER[25]] = true;
	// ����27:��ͭ͹���ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[26]] = true;
	// ����32:��ɽ�����ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[31]] = true;
	// ����33:���������ֹ�
	$VALUE_TO_HALF[$TAG_ORDER[32]] = true;
	// ����42:����ݥ�ˡ���������
	$VALUE_TO_HALF[$TAG_ORDER[41]] = true;
	// ����47:�����ֹ棱
	$VALUE_TO_HALF[$TAG_ORDER[46]] = true;
	// ����48:�����ֹ棲
	$VALUE_TO_HALF[$TAG_ORDER[47]] = true;
	// ����115:͹��ʿ�����ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[114]] = true;
	// ����116:͹��ʿ����λ����
	$VALUE_TO_HALF[$TAG_ORDER[115]] = true;
	// ����117:͹�����˳��ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[116]] = true;
	// ����118:͹�����˽�λ����
	$VALUE_TO_HALF[$TAG_ORDER[117]] = true;
	// ����119:͹�����ˡ��������ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[118]] = true;
	// ����120:͹�����ˡ�������λ����
	$VALUE_TO_HALF[$TAG_ORDER[119]] = true;
	// ����121:͹����������
	$VALUE_TO_HALF[$TAG_ORDER[120]] = true;
	// ����123:����ʿ�����ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[122]] = true;
	// ����124:����ʿ����λ����
	$VALUE_TO_HALF[$TAG_ORDER[123]] = true;
	// ����125:�������˳��ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[124]] = true;
	// ����126:�������˽�λ����
	$VALUE_TO_HALF[$TAG_ORDER[125]] = true;
	// ����127:�������ˡ��������ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[126]] = true;
	// ����128:�������ˡ�������λ����
	$VALUE_TO_HALF[$TAG_ORDER[127]] = true;
	// ����129:�����������
	$VALUE_TO_HALF[$TAG_ORDER[128]] = true;
	// ����131:ATMʿ�����ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[130]] = true;
	// ����132:ATMʿ����λ����
	$VALUE_TO_HALF[$TAG_ORDER[131]] = true;
	// ����133:ATM���˳��ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[132]] = true;
	// ����134:ATM���˽�λ����
	$VALUE_TO_HALF[$TAG_ORDER[133]] = true;
	// ����135:ATM���ˡ��������ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[134]] = true;
	// ����136:ATM���ˡ�������λ����
	$VALUE_TO_HALF[$TAG_ORDER[135]] = true;
	// ����137:ATM�����
	$VALUE_TO_HALF[$TAG_ORDER[136]] = true;
	// ����139:�ݸ�ʿ�����ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[138]] = true;
	// ����140:�ݸ�ʿ����λ����
	$VALUE_TO_HALF[$TAG_ORDER[139]] = true;
	// ����141:�ݸ����˳��ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[140]] = true;
	// ����142:�ݸ����˽�λ����
	$VALUE_TO_HALF[$TAG_ORDER[141]] = true;
	// ����143:�ݸ����ˡ��������ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[142]] = true;
	// ����144:�ݸ����ˡ�������λ����
	$VALUE_TO_HALF[$TAG_ORDER[143]] = true;
	// ����145:�ݸ���������
	$VALUE_TO_HALF[$TAG_ORDER[144]] = true;
	// ����147:�椦�椦ʿ�����ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[146]] = true;
	// ����148:�椦�椦ʿ����λ����
	$VALUE_TO_HALF[$TAG_ORDER[147]] = true;
	// ����149:�椦�椦���˳��ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[148]] = true;
	// ����150:�椦�椦���˽�λ����
	$VALUE_TO_HALF[$TAG_ORDER[149]] = true;
	// ����151:�椦�椦���ˡ��������ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[150]] = true;
	// ����152:�椦�椦���ˡ�������λ����
	$VALUE_TO_HALF[$TAG_ORDER[151]] = true;
	// ����153:�椦�椦��������
	$VALUE_TO_HALF[$TAG_ORDER[152]] = true;
	// ����155:�����ʿ�����ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[154]] = true;
	// ����156:�����ʿ����λ����
	$VALUE_TO_HALF[$TAG_ORDER[155]] = true;
	// ����157:��������˳��ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[156]] = true;
	// ����158:��������˽�λ����
	$VALUE_TO_HALF[$TAG_ORDER[157]] = true;
	// ����159:��������ˡ��������ϻ���
	$VALUE_TO_HALF[$TAG_ORDER[158]] = true;
	// ����160:��������ˡ�������λ����
	$VALUE_TO_HALF[$TAG_ORDER[159]] = true;
	// ����161:�������������
	$VALUE_TO_HALF[$TAG_ORDER[160]] = true;

// ���Ѳ�
	$VALUE_TO_FULL = array();
	// ����10:����
	$VALUE_TO_FULL[$TAG_ORDER[9]] = true;

// �ϥ��ե����(͹���ֹ�)
	$VALUE_TRIM_HYPHEN = array();
	// ����9:͹���ֹ�
	$VALUE_TRIM_HYPHEN[$TAG_ORDER[8]] = true;
	// ����27:��ͭ͹���ֹ�
	$VALUE_TRIM_HYPHEN[$TAG_ORDER[26]] = true;

// 0�����������
	$VALUE_ZERO_CORRECT = array();
	// del start 2017/01/25 H.Yasunaga ���ִ�����ˡ���������(����ID)��0������������򳰤� [
	// ����1:���ִ�����ˡ���������
	//$VALUE_ZERO_CORRECT[$TAG_ORDER[0]] = 12;
	// del end 2017/01/25 ]
	// ����2:�ɽꥳ����
	$VALUE_ZERO_CORRECT[$TAG_ORDER[1]] = 6;
	// ����3:�谷Ź�ֹ�
	$VALUE_ZERO_CORRECT[$TAG_ORDER[2]] = 6;
	// ����5:ʻ��Ź�ե饰
	$VALUE_ZERO_CORRECT[$TAG_ORDER[4]] = 4;
	// ����11:JIS��ƻ�ܸ�������
	$VALUE_ZERO_CORRECT[$TAG_ORDER[10]] = 2;
	// ����12:JIS�Զ�Į¼������
	$VALUE_ZERO_CORRECT[$TAG_ORDER[11]] = 5;
	// ����21:͹�ضɶ�ʬ
	$VALUE_ZERO_CORRECT[$TAG_ORDER[20]] = 2;
	// ����30:͹�ػ�Ź��ʬ
	$VALUE_ZERO_CORRECT[$TAG_ORDER[29]] = 2;
	
// ����������� hh:mm:ss �� ss��̵�����ˡ�00�פ��ɲä���
	$VALUE_TIME_CORRECT = array();
	// ����115:͹��ʿ�����ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[114]] = true;
	// ����116:͹��ʿ����λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[115]] = true;
	// ����117:͹�����˳��ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[116]] = true;
	// ����118:͹�����˽�λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[117]] = true;
	// ����119:͹�����ˡ��������ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[118]] = true;
	// ����120:͹�����ˡ�������λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[119]] = true;
	// ����123:����ʿ�����ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[122]] = true;
	// ����124:����ʿ����λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[123]] = true;
	// ����125:�������˳��ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[124]] = true;
	// ����126:�������˽�λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[125]] = true;
	// ����127:�������ˡ��������ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[126]] = true;
	// ����128:�������ˡ�������λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[127]] = true;
	// ����131:ATMʿ�����ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[130]] = true;
	// ����132:ATMʿ����λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[131]] = true;
	// ����133:ATM���˳��ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[132]] = true;
	// ����134:ATM���˽�λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[133]] = true;
	// ����135:ATM���ˡ��������ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[134]] = true;
	// ����136:ATM���ˡ�������λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[135]] = true;
	// ����139:�ݸ�ʿ�����ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[138]] = true;
	// ����140:�ݸ�ʿ����λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[139]] = true;
	// ����141:�ݸ����˳��ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[140]] = true;
	// ����142:�ݸ����˽�λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[141]] = true;
	// ����143:�ݸ����ˡ��������ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[142]] = true;
	// ����144:�ݸ����ˡ�������λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[143]] = true;
	// ����147:�椦�椦ʿ�����ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[146]] = true;
	// ����148:�椦�椦ʿ����λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[147]] = true;
	// ����149:�椦�椦���˳��ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[148]] = true;
	// ����150:�椦�椦���˽�λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[149]] = true;
	// ����151:�椦�椦���ˡ��������ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[150]] = true;
	// ����152:�椦�椦���ˡ�������λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[151]] = true;
	// ����155:�����ʿ�����ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[154]] = true;
	// ����156:�����ʿ����λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[155]] = true;
	// ����157:��������˳��ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[156]] = true;
	// ����158:��������˽�λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[157]] = true;
	// ����159:��������ˡ��������ϻ���
	$VALUE_TIME_CORRECT[$TAG_ORDER[158]] = true;
	// ����160:��������ˡ�������λ����
	$VALUE_TIME_CORRECT[$TAG_ORDER[159]] = true;
?>