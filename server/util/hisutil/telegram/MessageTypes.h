#pragma once


enum message_type
{
	notmessage

	, ePlay_Ani_Finished	//�ִϸ��̼��� ������.
	, eStart_Battle		//������ ���۵Ǿ����ϴ�.
	, eChase_Target		//Ÿ���� �߰��϶�.
	, eAlert_Tartget	//Ÿ���� ����϶�.
	, eLost_Target		//target ����
	, eDie_Disappear		//����� �����
	, eDie_Avartar_Revival		//avatar ȸ�� ó��
	, eDie_Revival		//ȸ�� ó��
	, eNo_Rival			//����

	, eReset_Battle_Zone	//�δ� �Ϸ��� �簻��(reset)

	, eSkill_UseSkill		//��ų ���
	, eSkill_ComboAttack	//��ų ���ݽ���
	, eSkill_Progress_Complete	//��ų���� ����(���� �ٸ� ��ų ���� ����)

	, eBattle_Object_Move_For_Attack	//������ ���� �̵�
	, eBattle_Object_Move_Completed		//�̵� ����
	, eBattle_Object_Attack_Completed	//���� ����(������)

	, eTrade_Auto_Cancel				//�����ð� ������ ���ٸ� �ڵ� ��ҵ�

	, eParty_Auto_Leave					//�����ð� ���� ���������� ������ Ż��ó���ȴ�.
	, eParty_Close						//��Ƽ�� �ݴ´�.

	, eAuction_Success_Time				//�����ð�

	//, eItem_Remove_Zone_Item			//�ʿ� ����߸� ������ ����
	//, eItem_Remove_Single_Zone_Item		//�̱۸ʿ� ����߸� ������ ����

	, eDungeon_Zone_Release				//zone�� �����Ѵ�(����)


	//�̰��� �߰��� �ʿ��� ��� ������ noti�� �ּ���(Ȳ����)
	//..





	//HG[2013.08.27]�߰��� �� ���ʿ��� ���ָ� ���ڽ��ϴ�.(����)
	, eAccount_Disconnect	//���� ���� ����ó��
	, eAccount_Remove		//���� ���� �޸� ����
	, eMax_Message_Type				//�ִ밪.
};
