<?php
// ------------------------------------------------------------
// API�쥹�ݥ󥹤�XML�������
// 
// 2016/06/14 H.Yasunaga	��������
// 2016/06/24 H.Yasunaga	������̤ΰ��ٷ��٤ν��֤ν���
//							���ٷ��٤λ���ߥ��ν���
// ------------------------------------------------------------
	$TAG_ORDER;
	$TAG_TO_COL;
	

	$TAG_ORDER = array();
	//���ִ�����ˡ���������
	$TAG_ORDER[0] = "office_id";
	//�ɽꥳ����
	$TAG_ORDER[1] = "post_code";
	//�谷Ź�ֹ�
	$TAG_ORDER[2] = "dealer_no";
	//�ǽ�����ǯ����
	$TAG_ORDER[3] = "last_update_date";
	//ʻ��Ź�ե饰
	$TAG_ORDER[4] = "juxtaposition_flag";
	//ATM̵ͭ
	$TAG_ORDER[5] = "atm_flag";
	//����
	$TAG_ORDER[6] = "nl";
	//����
	$TAG_ORDER[7] = "el";
	//͹���ֹ�
	$TAG_ORDER[8] = "zip_code";
	//����
	$TAG_ORDER[9] = "address";
	//JIS��ƻ�ܸ�������
	$TAG_ORDER[10] = "pref_code";
	//JIS�Զ�Į¼������
	$TAG_ORDER[11] = "city_code";
	//JIS�Զ�Į¼̾
	$TAG_ORDER[12] = "city_name";
	//��־�
	$TAG_ORDER[13] = "parking";
	//��־�����
	$TAG_ORDER[14] = "parking_note";
	//Ź�޵���
	$TAG_ORDER[15] = "store_scale";
	//��°���ꥢ
	$TAG_ORDER[16] = "area";
	//͹�ضɲ�ҥ�ˡ���������
	$TAG_ORDER[17] = "jp_network_code";
	//͹�ض�̾
	$TAG_ORDER[18] = "jp_network_name";
	//͹�ض�̾(���Ѥ��ʻ�)
	$TAG_ORDER[19] = "jp_network_kana";
	//͹�ضɶ�ʬ
	$TAG_ORDER[20] = "jp_network_class";
	//��������ֹ�
	$TAG_ORDER[21] = "jp_network_tel1";
	//��̳�����ֹ�
	$TAG_ORDER[22] = "jp_network_tel2";
	//��礻FAX
	$TAG_ORDER[23] = "jp_network_fax";
	//��礻����
	$TAG_ORDER[24] = "jp_network_note";
	//�椦�椦�����ˡ���������
	$TAG_ORDER[25] = "jp_post_code";
	//��ͭ͹���ֹ�
	$TAG_ORDER[26] = "jp_post_zip";
	//͹�ػ�Ź̾
	$TAG_ORDER[27] = "jp_post_name";
	//͹�ػ�Ź̾(���Ѥ��ʻ�) 
	$TAG_ORDER[28] = "jp_post_kana";
	//͹�ػ�Ź��ʬ
	$TAG_ORDER[29] = "jp_post_class";
	//͹�ػ�Ź�谷����(����) 
	$TAG_ORDER[30] = "jp_post_handling_note";
	//��ɽ�����ֹ�
	$TAG_ORDER[31] = "jp_post_tel1";
	//���������ֹ�
	$TAG_ORDER[32] = "jp_post_tel2";
	//��礻����
	$TAG_ORDER[33] = "jp_post_note";
	//�椦����Ź��ˡ���������
	$TAG_ORDER[34] = "jp_bank_code";
	//���ľ��Ź̾
	$TAG_ORDER[35] = "jp_bank_name";
	//���ľ��Ź̾(���Ѥ��ʻ�) 
	$TAG_ORDER[36] = "jp_bank_kana";
	//���ľ��Ź����̾
	$TAG_ORDER[37] = "jp_bank_official_name";
	//��ʬ(ľ��Ź��ATM��ĥ��) 
	$TAG_ORDER[38] = "jp_bank_class";
	//�����ֹ�
	$TAG_ORDER[39] = "jp_bank_tel";
	//��礻����
	$TAG_ORDER[40] = "jp_bank_note";
	//����ݥ�ˡ���������
	$TAG_ORDER[41] = "jp_insurance_code";
	//����ݻ�Ź̾
	$TAG_ORDER[42] = "jp_insurance_name";
	//����ݻ�Ź̾(���Ѥ��ʻ�) 
	$TAG_ORDER[43] = "jp_insurance_kana";
	//����ݻ�Ź��ʬ
	$TAG_ORDER[44] = "jp_insurance_class";
	//��ŹURL 
	$TAG_ORDER[45] = "jp_insurance_url";
	//�����ֹ棱 
	$TAG_ORDER[46] = "jp_insurance_tel1";
	//�����ֹ棲 
	$TAG_ORDER[47] = "jp_insurance_tel2";
	//��礻����
	$TAG_ORDER[48] = "jp_insurance_note";
	//͹�����
	$TAG_ORDER[49] = "post_window";
	//�������ꤵ�Ф�
	$TAG_ORDER[50] = "stamp_sale";
	//����ʪή���Ȥ˷������
	$TAG_ORDER[51] = "home_window";
	//����ɤ椦�ѥå�
	$TAG_ORDER[52] = "chilled_yu_pack";
	//���ƾ���
	$TAG_ORDER[53] = "contents_certified";
	//�輡�������ӥ�
	$TAG_ORDER[54] = "agency_service";
	//�̾�����
	$TAG_ORDER[55] = "regular_savings";
	//�̾���������
	$TAG_ORDER[56] = "money_market_account";
	//�������
	$TAG_ORDER[57] = "fixed_deposit";
	//��ư��Ω�������
	$TAG_ORDER[58] = "auto_fixed_deposit";
	//�������
	$TAG_ORDER[59] = "time_deposit";
	//��ư��Ω�������
	$TAG_ORDER[60] = "auto_time_deposit";
	//���������跿�������
	$TAG_ORDER[61] = "expiration_time_deposit";
	//�˥塼ʡ���������
	$TAG_ORDER[62] = "welfare_time_deposit";
	//����������
	$TAG_ORDER[63] = "asset_building_savings";
	//�⻺���������������
	$TAG_ORDER[64] = "asset_building_savings_housing";
	//�⻺����ǯ���������
	$TAG_ORDER[65] = "asset_building_savings_pension";
	//���̰���
	$TAG_ORDER[66] = "normal_exchange";
	//��۾�����
	$TAG_ORDER[67] = "fixed_exchange";
	//ATM�ˤ���̾�ʧ����
	$TAG_ORDER[68] = "atm_payment";
	//����ʧ����
	$TAG_ORDER[69] = "public_payment";
	//�̾�ʧ����
	$TAG_ORDER[70] = "normal_payment";
	//�ſ�ʧ����
	$TAG_ORDER[71] = "telegraphic_payment";
	//�ſ�����
	$TAG_ORDER[72] = "telegraphic_transfer";
	//�������
	$TAG_ORDER[73] = "mutual_transfer";
	//��ưʧ����
	$TAG_ORDER[74] = "auto_payment";
	//��ư����
	$TAG_ORDER[75] = "auto_transfer";
	//���⾮�ڼ�ο���
	$TAG_ORDER[76] = "cheque";
	//��ưʧ������
	$TAG_ORDER[77] = "auto_deposit";
	//�ʰ�ʧ��(���ѿ����ߡ�ʧ�Ф�������) 
	$TAG_ORDER[78] = "simple_payment_request";
	//�ʰ�ʧ��(ʧ���Ϥ�) 
	$TAG_ORDER[79] = "simple_payment_transfer";
	//�̾︽��ʧ
	$TAG_ORDER[80] = "normal_cash_payment";
	//�ſ�����ʧ(���ʧ) 
	$TAG_ORDER[81] = "telegraphic_cash_payment";
	//��Ϳ����
	$TAG_ORDER[82] = "salary_deposit";
	//�������
	$TAG_ORDER[83] = "international_transfer";
	//����ξ��/�ȥ�٥顼�������å�
	$TAG_ORDER[84] = "foreign_currency";
	//��̱ǯ��
	$TAG_ORDER[85] = "national_pension";
	//ȿ§��
	$TAG_ORDER[86] = "penalty";
	//��̱ǯ�⡦ȿ§��ʳ��κ�����
	$TAG_ORDER[87] = "revenue";
	//�нж�
	$TAG_ORDER[88] = "expenditure";
	//̵��̾���(���) 
	$TAG_ORDER[89] = "government_bonds";
	//�����
	$TAG_ORDER[90] = "investment_trust";
	//�ѳ�ǯ���ݸ�
	$TAG_ORDER[91] = "variable_pension";
	//������ǯ��
	$TAG_ORDER[92] = "defined_contribution";
	//��������󡦥ե꡼������
	$TAG_ORDER[93] = "suruga_loan";
	//�������̿�ݸ��罸
	$TAG_ORDER[94] = "jp_insurance_recruit";
	//�Ҳ�����Ź
	$TAG_ORDER[95] = "introduction_agency";
	//�������̿�ݸ��ݻ�������̳
	$TAG_ORDER[96] = "jp_insurance_maintenance";
	//�ʰ���̿�ݸ�������̳
	$TAG_ORDER[97] = "kampo_maintenance";
	//�������̿�ʳ�����̿�ݸ��罸
	$TAG_ORDER[98] = "except_jp_insurance_recruit";
	//��ư���ݸ��罸
	$TAG_ORDER[99] = "automobile_insurance";
	//�������ݸ��罸
	$TAG_ORDER[100] = "liability_insurance";
	//�����ݸ��罸
	$TAG_ORDER[101] = "cancer_insurance";
	//���������·������ݸ�
	$TAG_ORDER[102] = "condition_medical_insurance";
	//�����������λ�̳
	$TAG_ORDER[103] = "local_public_entity";
	//��������ջ�̳
	$TAG_ORDER[104] = "certificate_grant";
	//��������ջ�̳������
	$TAG_ORDER[105] = "breakdown_certificate_grant";
	//���������̳(���������̳) 
	$TAG_ORDER[106] = "trust_sale";
	//���������̳(���������̳)������
	$TAG_ORDER[107] = "trust_sale_contents";
	//���������̳(�������ջ�̳) 
	$TAG_ORDER[108] = "trust_grant";
	//���������̳(�������ջ�̳)������
	$TAG_ORDER[109] = "trust_grant_contents";
	//����¾�������������λ�̳
	$TAG_ORDER[110] = "other_local_public";
	//����¾�������������λ�̳������
	$TAG_ORDER[111] = "other_local_public_contents";
	//������
	$TAG_ORDER[112] = "lottery";
	//������������
	$TAG_ORDER[113] = "catalog_sale";
	//͹��ʿ�����ϻ���
	$TAG_ORDER[114] = "jp_network_start";
	//͹��ʿ����λ����
	$TAG_ORDER[115] = "jp_network_end";
	//͹�����˳��ϻ���
	$TAG_ORDER[116] = "jp_network_sat_start";
	//͹�����˽�λ����
	$TAG_ORDER[117] = "jp_network_sat_end";
	//͹�����ˡ��������ϻ���
	$TAG_ORDER[118] = "jp_network_sun_start";
	//͹�����ˡ�������λ����
	$TAG_ORDER[119] = "jp_network_sun_end";
	//͹����������
	$TAG_ORDER[120] = "jp_network_win_closed";
	//͹���������
	$TAG_ORDER[121] = "jp_network_win_note";
	//����ʿ�����ϻ���
	$TAG_ORDER[122] = "jp_bank_start";
	//����ʿ����λ����
	$TAG_ORDER[123] = "jp_bank_end";
	//�������˳��ϻ���
	$TAG_ORDER[124] = "jp_bank_sat_start";
	//�������˽�λ����
	$TAG_ORDER[125] = "jp_bank_sat_end";
	//�������ˡ��������ϻ���
	$TAG_ORDER[126] = "jp_bank_sun_start";
	//�������ˡ�������λ����
	$TAG_ORDER[127] = "jp_bank_sun_end";
	//�����������
	$TAG_ORDER[128] = "jp_bank_win_closed";
	//����������
	$TAG_ORDER[129] = "jp_bank_win_note";
	//ATMʿ�����ϻ���
	$TAG_ORDER[130] = "atm_start";
	//ATMʿ����λ����
	$TAG_ORDER[131] = "atm_end";
	//ATM���˳��ϻ���
	$TAG_ORDER[132] = "atm_sat_start";
	//ATM���˽�λ����
	$TAG_ORDER[133] = "atm_sat_end";
	//ATM���ˡ��������ϻ���
	$TAG_ORDER[134] = "atm_sun_start";
	//ATM���ˡ�������λ����
	$TAG_ORDER[135] = "atm_sun_end";
	//ATM�����
	$TAG_ORDER[136] = "atm_closed";
	//ATM����
	$TAG_ORDER[137] = "atm_note";
	//�ݸ�ʿ�����ϻ���
	$TAG_ORDER[138] = "jp_network_insurance_start";
	//�ݸ�ʿ����λ����
	$TAG_ORDER[139] = "jp_network_insurance_end";
	//�ݸ����˳��ϻ���
	$TAG_ORDER[140] = "jp_network_insurance_sat_start";
	//�ݸ����˽�λ����
	$TAG_ORDER[141] = "jp_network_insurance_sat_end";
	//�ݸ����ˡ��������ϻ���
	$TAG_ORDER[142] = "jp_network_insurance_sun_start";
	//�ݸ����ˡ�������λ����
	$TAG_ORDER[143] = "jp_network_insurance_sun_end";
	//�ݸ���������
	$TAG_ORDER[144] = "jp_network_insurance_win_closed";
	//�ݸ��������
	$TAG_ORDER[145] = "jp_network_insurance_win_note";
	//�椦�椦ʿ�����ϻ���
	$TAG_ORDER[146] = "jp_post_start";
	//�椦�椦ʿ����λ����
	$TAG_ORDER[147] = "jp_post_end";
	//�椦�椦���˳��ϻ���
	$TAG_ORDER[148] = "jp_post_sat_start";
	//�椦�椦���˽�λ����
	$TAG_ORDER[149] = "jp_post_sat_end";
	//�椦�椦���ˡ��������ϻ���
	$TAG_ORDER[150] = "jp_post_sun_start";
	//�椦�椦���ˡ�������λ����
	$TAG_ORDER[151] = "jp_post_sun_end";
	//�椦�椦��������
	$TAG_ORDER[152] = "jp_post_win_closed";
	//�椦�椦�������
	$TAG_ORDER[153] = "jp_post_win_note";
	//�����ʿ�����ϻ���
	$TAG_ORDER[154] = "jp_insurance_start";
	//�����ʿ����λ����
	$TAG_ORDER[155] = "jp_insurance_end";
	//��������˳��ϻ���
	$TAG_ORDER[156] = "jp_insurance_sat_start";
	//��������˽�λ����
	$TAG_ORDER[157] = "jp_insurance_sat_end";
	//��������ˡ��������ϻ���
	$TAG_ORDER[158] = "jp_insurance_sun_start";
	//��������ˡ�������λ����
	$TAG_ORDER[159] = "jp_insurance_sun_end";
	//�������������
	$TAG_ORDER[160] = "jp_insurance_win_closed";
	//������������
	$TAG_ORDER[161] = "jp_insurance_win_note";
	//���ڼ�ʧ��
	$TAG_ORDER[162] = "reserve_flag1";
	//�����ɥ�����
	$TAG_ORDER[163] = "reserve_flag2";
	//ȿ������
	$TAG_ORDER[164] = "reflect_date";

	$TAG_TO_COL = array();
	//���ִ�����ˡ���������
	$TAG_TO_COL['office_id'] = "KYOTEN_ID";
	//�ɽꥳ����
	$TAG_TO_COL['post_code'] = "COL_02";
	//�谷Ź�ֹ�
	$TAG_TO_COL['dealer_no'] = "COL_03";
	//�ǽ�����ǯ����
	$TAG_TO_COL['last_update_date'] = "UPD_DT";
	//ʻ��Ź�ե饰
	$TAG_TO_COL['juxtaposition_flag'] = array("COL_05", "COL_06", "COL_07", "COL_08");
	//ATM̵ͭ
	$TAG_TO_COL['atm_flag'] = "COL_09";
	//����
	$TAG_TO_COL['el'] = "LON";
	//����
	$TAG_TO_COL['nl'] = "LAT";
	//͹���ֹ�
	$TAG_TO_COL['zip_code'] = "COL_10";
	//����
	$TAG_TO_COL['address'] = "ADDR";
	//JIS��ƻ�ܸ�������
	$TAG_TO_COL['pref_code'] = "COL_11";
	//JIS�Զ�Į¼������
	$TAG_TO_COL['city_code'] = "COL_12";
	//JIS�Զ�Į¼̾
	$TAG_TO_COL['city_name'] = "COL_13";
	//��־�
	$TAG_TO_COL['parking'] = "COL_14";
	//��־�����
	$TAG_TO_COL['parking_note'] = "COL_15";
	//Ź�޵���
	$TAG_TO_COL['store_scale'] = "COL_16";
	//��°���ꥢ
	$TAG_TO_COL['area'] = "COL_18";
	//͹�ضɲ�ҥ�ˡ���������
	$TAG_TO_COL['jp_network_code'] = "COL_19";
	//͹�ض�̾
	$TAG_TO_COL['jp_network_name'] = "COL_20";
	//͹�ض�̾(���Ѥ��ʻ�)
	$TAG_TO_COL['jp_network_kana'] = "COL_21";
	//͹�ضɶ�ʬ
	$TAG_TO_COL['jp_network_class'] = "COL_22";
	//��������ֹ�
	$TAG_TO_COL['jp_network_tel1'] = "COL_23";
	//��̳�����ֹ�
	$TAG_TO_COL['jp_network_tel2'] = "COL_24";
	//��礻FAX
	$TAG_TO_COL['jp_network_fax'] = "COL_25";
	//��礻����
	$TAG_TO_COL['jp_network_note'] = "COL_26";
	//�椦�椦�����ˡ���������
	$TAG_TO_COL['jp_post_code'] = "COL_27";
	//��ͭ͹���ֹ�
	$TAG_TO_COL['jp_post_zip'] = "COL_28";
	//͹�ػ�Ź̾
	$TAG_TO_COL['jp_post_name'] = "COL_29";
	//͹�ػ�Ź̾(���Ѥ��ʻ�) 
	$TAG_TO_COL['jp_post_kana'] = "COL_30";
	//͹�ػ�Ź��ʬ
	$TAG_TO_COL['jp_post_class'] = "COL_31";
	//͹�ػ�Ź�谷����(����) 
	$TAG_TO_COL['jp_post_handling_note'] = "COL_32";
	//��ɽ�����ֹ�
	$TAG_TO_COL['jp_post_tel1'] = "COL_33";
	//���������ֹ�
	$TAG_TO_COL['jp_post_tel2'] = "COL_34";
	//��礻����
	$TAG_TO_COL['jp_post_note'] = "COL_35";
	//�椦����Ź��ˡ���������
	$TAG_TO_COL['jp_bank_code'] = "COL_36";
	//���ľ��Ź̾
	$TAG_TO_COL['jp_bank_name'] = "COL_37";
	//���ľ��Ź̾(���Ѥ��ʻ�) 
	$TAG_TO_COL['jp_bank_kana'] = "COL_38";
	//���ľ��Ź����̾
	$TAG_TO_COL['jp_bank_official_name'] = "COL_39";
	//��ʬ(ľ��Ź��ATM��ĥ��) 
	$TAG_TO_COL['jp_bank_class'] = "COL_40";
	//�����ֹ�
	$TAG_TO_COL['jp_bank_tel'] = "COL_41";
	//��礻����
	$TAG_TO_COL['jp_bank_note'] = "COL_42";
	//����ݥ�ˡ���������
	$TAG_TO_COL['jp_insurance_code'] = "COL_43";
	//����ݻ�Ź̾
	$TAG_TO_COL['jp_insurance_name'] = "COL_44";
	//����ݻ�Ź̾(���Ѥ��ʻ�) 
	$TAG_TO_COL['jp_insurance_kana'] = "COL_45";
	//����ݻ�Ź��ʬ
	$TAG_TO_COL['jp_insurance_class'] = "COL_46";
	//��ŹURL 
	$TAG_TO_COL['jp_insurance_url'] = "COL_47";
	//�����ֹ棱 
	$TAG_TO_COL['jp_insurance_tel1'] = "COL_48";
	//�����ֹ棲 
	$TAG_TO_COL['jp_insurance_tel2'] = "COL_49";
	//��礻����
	$TAG_TO_COL['jp_insurance_note'] = "COL_50";
	//͹�����
	$TAG_TO_COL['post_window'] = "COL_51";
	//�������ꤵ�Ф�
	$TAG_TO_COL['stamp_sale'] = "COL_52";
	//����ʪή���Ȥ˷������
	$TAG_TO_COL['home_window'] = "COL_53";
	//����ɤ椦�ѥå�
	$TAG_TO_COL['chilled_yu_pack'] = "COL_54";
	//���ƾ���
	$TAG_TO_COL['contents_certified'] = "COL_55";
	//�輡�������ӥ�
	$TAG_TO_COL['agency_service'] = "COL_56";
	//�̾�����
	$TAG_TO_COL['regular_savings'] = "COL_57";
	//�̾���������
	$TAG_TO_COL['money_market_account'] = "COL_58";
	//�������
	$TAG_TO_COL['fixed_deposit'] = "COL_59";
	//��ư��Ω�������
	$TAG_TO_COL['auto_fixed_deposit'] = "COL_60";
	//�������
	$TAG_TO_COL['time_deposit'] = "COL_61";
	//��ư��Ω�������
	$TAG_TO_COL['auto_time_deposit'] = "COL_62";
	//���������跿�������
	$TAG_TO_COL['expiration_time_deposit'] = "COL_63";
	//�˥塼ʡ���������
	$TAG_TO_COL['welfare_time_deposit'] = "COL_64";
	//����������
	$TAG_TO_COL['asset_building_savings'] = "COL_65";
	//�⻺���������������
	$TAG_TO_COL['asset_building_savings_housing'] = "COL_66";
	//�⻺����ǯ���������
	$TAG_TO_COL['asset_building_savings_pension'] = "COL_67";
	//���̰���
	$TAG_TO_COL['normal_exchange'] = "COL_68";
	//��۾�����
	$TAG_TO_COL['fixed_exchange'] = "COL_69";
	//ATM�ˤ���̾�ʧ����
	$TAG_TO_COL['atm_payment'] = "COL_70";
	//����ʧ����
	$TAG_TO_COL['public_payment'] = "COL_71";
	//�̾�ʧ����
	$TAG_TO_COL['normal_payment'] = "COL_72";
	//�ſ�ʧ����
	$TAG_TO_COL['telegraphic_payment'] = "COL_73";
	//�ſ�����
	$TAG_TO_COL['telegraphic_transfer'] = "COL_74";
	//�������
	$TAG_TO_COL['mutual_transfer'] = "COL_75";
	//��ưʧ����
	$TAG_TO_COL['auto_payment'] = "COL_76";
	//��ư����
	$TAG_TO_COL['auto_transfer'] = "COL_77";
	//���⾮�ڼ�ο���
	$TAG_TO_COL['cheque'] = "COL_78";
	//��ưʧ������
	$TAG_TO_COL['auto_deposit'] = "COL_79";
	//�ʰ�ʧ��(���ѿ����ߡ�ʧ�Ф�������) 
	$TAG_TO_COL['simple_payment_request'] = "COL_80";
	//�ʰ�ʧ��(ʧ���Ϥ�) 
	$TAG_TO_COL['simple_payment_transfer'] = "COL_81";
	//�̾︽��ʧ
	$TAG_TO_COL['normal_cash_payment'] = "COL_82";
	//�ſ�����ʧ(���ʧ) 
	$TAG_TO_COL['telegraphic_cash_payment'] = "COL_83";
	//��Ϳ����
	$TAG_TO_COL['salary_deposit'] = "COL_84";
	//�������
	$TAG_TO_COL['international_transfer'] = "COL_85";
	//����ξ��/�ȥ�٥顼�������å�
	$TAG_TO_COL['foreign_currency'] = "COL_86";
	//��̱ǯ��
	$TAG_TO_COL['national_pension'] = "COL_87";
	//ȿ§��
	$TAG_TO_COL['penalty'] = "COL_88";
	//��̱ǯ�⡦ȿ§��ʳ��κ�����
	$TAG_TO_COL['revenue'] = "COL_89";
	//�нж�
	$TAG_TO_COL['expenditure'] = "COL_90";
	//̵��̾���(���) 
	$TAG_TO_COL['government_bonds'] = "COL_91";
	//�����
	$TAG_TO_COL['investment_trust'] = "COL_92";
	//�ѳ�ǯ���ݸ�
	$TAG_TO_COL['variable_pension'] = "COL_93";
	//������ǯ��
	$TAG_TO_COL['defined_contribution'] = "COL_94";
	//��������󡦥ե꡼������
	$TAG_TO_COL['suruga_loan'] = "COL_95";
	//�������̿�ݸ��罸
	$TAG_TO_COL['jp_insurance_recruit'] = "COL_96";
	//�Ҳ�����Ź
	$TAG_TO_COL['introduction_agency'] = "COL_97";
	//�������̿�ݸ��ݻ�������̳
	$TAG_TO_COL['jp_insurance_maintenance'] = "COL_98";
	//�ʰ���̿�ݸ�������̳
	$TAG_TO_COL['kampo_maintenance'] = "COL_99";
	//�������̿�ʳ�����̿�ݸ��罸
	$TAG_TO_COL['except_jp_insurance_recruit'] = "COL_100";
	//��ư���ݸ��罸
	$TAG_TO_COL['automobile_insurance'] = "COL_101";
	//�������ݸ��罸
	$TAG_TO_COL['liability_insurance'] = "COL_102";
	//�����ݸ��罸
	$TAG_TO_COL['cancer_insurance'] = "COL_103";
	//���������·������ݸ�
	$TAG_TO_COL['condition_medical_insurance'] = "COL_104";
	//�����������λ�̳
	$TAG_TO_COL['local_public_entity'] = "COL_105";
	//��������ջ�̳
	$TAG_TO_COL['certificate_grant'] = "COL_106";
	//��������ջ�̳������
	$TAG_TO_COL['breakdown_certificate_grant'] = "COL_107";
	//���������̳(���������̳) 
	$TAG_TO_COL['trust_sale'] = "COL_108";
	//���������̳(���������̳)������
	$TAG_TO_COL['trust_sale_contents'] = "COL_109";
	//���������̳(�������ջ�̳) 
	$TAG_TO_COL['trust_grant'] = "COL_110";
	//���������̳(�������ջ�̳)������
	$TAG_TO_COL['trust_grant_contents'] = "COL_111";
	//����¾�������������λ�̳
	$TAG_TO_COL['other_local_public'] = "COL_112";
	//����¾�������������λ�̳������
	$TAG_TO_COL['other_local_public_contents'] = "COL_113";
	//������
	$TAG_TO_COL['lottery'] = "COL_114";
	//������������
	$TAG_TO_COL['catalog_sale'] = "COL_115";
	//͹��ʿ�����ϻ���
	$TAG_TO_COL['jp_network_start'] = "COL_119";
	//͹��ʿ����λ����
	$TAG_TO_COL['jp_network_end'] = "COL_120";
	//͹�����˳��ϻ���
	$TAG_TO_COL['jp_network_sat_start'] = "COL_121";
	//͹�����˽�λ����
	$TAG_TO_COL['jp_network_sat_end'] = "COL_122";
	//͹�����ˡ��������ϻ���
	$TAG_TO_COL['jp_network_sun_start'] = "COL_123";
	//͹�����ˡ�������λ����
	$TAG_TO_COL['jp_network_sun_end'] = "COL_124";
	//͹����������
	$TAG_TO_COL['jp_network_win_closed'] = "COL_125";
	//͹���������
	$TAG_TO_COL['jp_network_win_note'] = "COL_126";
	//����ʿ�����ϻ���
	$TAG_TO_COL['jp_bank_start'] = "COL_127";
	//����ʿ����λ����
	$TAG_TO_COL['jp_bank_end'] = "COL_128";
	//�������˳��ϻ���
	$TAG_TO_COL['jp_bank_sat_start'] = "COL_129";
	//�������˽�λ����
	$TAG_TO_COL['jp_bank_sat_end'] = "COL_130";
	//�������ˡ��������ϻ���
	$TAG_TO_COL['jp_bank_sun_start'] = "COL_131";
	//�������ˡ�������λ����
	$TAG_TO_COL['jp_bank_sun_end'] = "COL_132";
	//�����������
	$TAG_TO_COL['jp_bank_win_closed'] = "COL_133";
	//����������
	$TAG_TO_COL['jp_bank_win_note'] = "COL_134";
	//ATMʿ�����ϻ���
	$TAG_TO_COL['atm_start'] = "COL_135";
	//ATMʿ����λ����
	$TAG_TO_COL['atm_end'] = "COL_136";
	//ATM���˳��ϻ���
	$TAG_TO_COL['atm_sat_start'] = "COL_137";
	//ATM���˽�λ����
	$TAG_TO_COL['atm_sat_end'] = "COL_138";
	//ATM���ˡ��������ϻ���
	$TAG_TO_COL['atm_sun_start'] = "COL_139";
	//ATM���ˡ�������λ����
	$TAG_TO_COL['atm_sun_end'] = "COL_140";
	//ATM�����
	$TAG_TO_COL['atm_closed'] = "COL_141";
	//ATM����
	$TAG_TO_COL['atm_note'] = "COL_142";
	//�ݸ�ʿ�����ϻ���
	$TAG_TO_COL['jp_network_insurance_start'] = "COL_143";
	//�ݸ�ʿ����λ����
	$TAG_TO_COL['jp_network_insurance_end'] = "COL_144";
	//�ݸ����˳��ϻ���
	$TAG_TO_COL['jp_network_insurance_sat_start'] = "COL_145";
	//�ݸ����˽�λ����
	$TAG_TO_COL['jp_network_insurance_sat_end'] = "COL_146";
	//�ݸ����ˡ��������ϻ���
	$TAG_TO_COL['jp_network_insurance_sun_start'] = "COL_147";
	//�ݸ����ˡ�������λ����
	$TAG_TO_COL['jp_network_insurance_sun_end'] = "COL_148";
	//�ݸ���������
	$TAG_TO_COL['jp_network_insurance_win_closed'] = "COL_149";
	//�ݸ��������
	$TAG_TO_COL['jp_network_insurance_win_note'] = "COL_150";
	//�椦�椦ʿ�����ϻ���
	$TAG_TO_COL['jp_post_start'] = "COL_151";
	//�椦�椦ʿ����λ����
	$TAG_TO_COL['jp_post_end'] = "COL_152";
	//�椦�椦���˳��ϻ���
	$TAG_TO_COL['jp_post_sat_start'] = "COL_153";
	//�椦�椦���˽�λ����
	$TAG_TO_COL['jp_post_sat_end'] = "COL_154";
	//�椦�椦���ˡ��������ϻ���
	$TAG_TO_COL['jp_post_sun_start'] = "COL_155";
	//�椦�椦���ˡ�������λ����
	$TAG_TO_COL['jp_post_sun_end'] = "COL_156";
	//�椦�椦��������
	$TAG_TO_COL['jp_post_win_closed'] = "COL_157";
	//�椦�椦�������
	$TAG_TO_COL['jp_post_win_note'] = "COL_158";
	//�����ʿ�����ϻ���
	$TAG_TO_COL['jp_insurance_start'] = "COL_159";
	//�����ʿ����λ����
	$TAG_TO_COL['jp_insurance_end'] = "COL_160";
	//��������˳��ϻ���
	$TAG_TO_COL['jp_insurance_sat_start'] = "COL_161";
	//��������˽�λ����
	$TAG_TO_COL['jp_insurance_sat_end'] = "COL_162";
	//��������ˡ��������ϻ���
	$TAG_TO_COL['jp_insurance_sun_start'] = "COL_163";
	//��������ˡ�������λ����
	$TAG_TO_COL['jp_insurance_sun_end'] = "COL_164";
	//�������������
	$TAG_TO_COL['jp_insurance_win_closed'] = "COL_165";
	//������������
	$TAG_TO_COL['jp_insurance_win_note'] = "COL_166";
	//���ڼ�ʧ��
	$TAG_TO_COL['reserve_flag1'] = "COL_167";
	//�����ɥ�����
	$TAG_TO_COL['reserve_flag2'] = "COL_168";
	//ȿ������
	$TAG_TO_COL['reflect_date'] = "PUB_S_DATE";
	
?>