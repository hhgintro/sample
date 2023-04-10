#pragma once



//�α��� ��û
//	account : ������
//	password : ����Ű(password)
//	version : �������� ����
struct stX2G_AC_LOGIN_REQ
{
	stX2G_AC_LOGIN_REQ()
		: protocol(0)
	{
	}

	std::wstring account;
	std::wstring password;
	PROTOCOL_T protocol;
};


//�α��� ��û�� ���� ����
//	result : ���� �����
//	accountpk : ���� �ĺ���ȣ
struct stX2G_AC_LOGIN_ACK
{
	stX2G_AC_LOGIN_ACK()
		: result(0), accountpk(0)
	{
	}

	RESULT_T result;
	ACCOUNTPK accountpk;
};


//���� ���� ��û
struct stX2G_IN_EQUIP_LOAD_REQ
{
	stX2G_IN_EQUIP_LOAD_REQ()
	{
	}

};


//���� ���� ��û�� ���� ����
//	inven : ������ �κ�����
//	gender : ����
//	myhair : hair
//	myhead : head
//	mycloth : cloth
//	myskincolor : skin color
//	myclothcolor : cloth color
//	hashairtype : ������ hair
//	hasheadtype : ������ head
//	hasclothtype : ������ cloth
struct stX2G_IN_EQUIP_LOAD_ACK
{
	stX2G_IN_EQUIP_LOAD_ACK()
	{
	}

	stInven inven;
};


//���� ���� ���� ��û
//	inven : ������ �κ�����
//	gender : ����
//	myhair : hair
//	myhead : head
//	mycloth : cloth
//	myskincolor : skin color
//	myclothcolor : cloth color
//	hashairtype : ������ hair
//	hasheadtype : ������ head
//	hasclothtype : ������ cloth
struct stX2G_IN_EQUIP_UPDATE_REQ
{
	stX2G_IN_EQUIP_UPDATE_REQ()
	{
	}

	stInven inven;
};


//���� ���� ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_IN_EQUIP_UPDATE_ACK
{
	stX2G_IN_EQUIP_UPDATE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//���� ���� ��û(�����-->���� �̵�)
struct stX2G_RM_ENTER_SQUARE_REQ
{
	stX2G_RM_ENTER_SQUARE_REQ()
	{
	}

};


//�� ���� ��û(��Ƽ�� ����)(����-->Ź����� �̵�)
struct stX2G_RM_ENTER_ROOM_REQ
{
	stX2G_RM_ENTER_ROOM_REQ()
	{
	}

};


//��(����) ���� ��û�� ���� ����
//	result : ���� �����
//	players : �濡 �ִ� player����
struct stX2G_RM_ENTER_ROOM_ACK
{
	stX2G_RM_ENTER_ROOM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<stRoomPlayer> players;
};


//��(����) ���� �뺸
//	player : ������ player����
struct stX2G_RM_ENTER_ROOM_NTF
{
	stX2G_RM_ENTER_ROOM_NTF()
	{
	}

	stRoomPlayer player;
};


//���� ���� ��û(����-->����� �̵�)
struct stX2G_RM_LEAVE_SQUARE_REQ
{
	stX2G_RM_LEAVE_SQUARE_REQ()
	{
	}

};


//�� ���� ��û(Ź�����-->���� �̵�)
struct stX2G_RM_LEAVE_ROOM_REQ
{
	stX2G_RM_LEAVE_ROOM_REQ()
	{
	}

};


//��(����) ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_RM_LEAVE_ROOM_ACK
{
	stX2G_RM_LEAVE_ROOM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//��(����) ���� �뺸
//	accountpk : ������ player����
struct stX2G_RM_LEAVE_ROOM_NTF
{
	stX2G_RM_LEAVE_ROOM_NTF()
		: accountpk(0)
	{
	}

	ACCOUNTPK accountpk;
};


//party ����Ʈ ��û
//	type : ��Ÿ��(0:���, 1:ü�´ܷý�, 2:ȸ�ǽ�, 3:������)
//	page : 0~(�ش� page)
//	cnt : page�� ����Ʈ����
struct stX2G_RM_PARTY_LIST_REQ
{
	stX2G_RM_PARTY_LIST_REQ()
		: type(0), page(0), cnt(0)
	{
	}

	UINT8 type;
	UINT8 page;
	UINT8 cnt;
};


//party ����Ʈ ��û�� ���� ����
//	parties : ��Ƽ����
struct stX2G_RM_PARTY_LIST_ACK
{
	stX2G_RM_PARTY_LIST_ACK()
	{
	}

	std::vector<stPartyInfo> parties;
};


//party ���� ��û
//	type : ��Ÿ��(0:����, 1:ü�´ܷý�, 2:ȸ�ǽ�, 3:������)
//	maxplayer : ���ִ� �ο�
struct stX2G_RM_CREATE_PARTY_REQ
{
	stX2G_RM_CREATE_PARTY_REQ()
		: type(0), maxplayer(0)
	{
	}

	UINT8 type;
	UINT8 maxplayer;
};


//party ���� ��û�� ���� ����
//	result : ���� �����
//	info : party ����
struct stX2G_RM_CREATE_PARTY_ACK
{
	stX2G_RM_CREATE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	stPartyInfo info;
};


//party ���� ��û
//	index : ���ȣ
struct stX2G_RM_ENTER_PARTY_REQ
{
	stX2G_RM_ENTER_PARTY_REQ()
		: index(0)
	{
	}

	PARTYINDEX index;
};


//party ���� ��û�� ���� ����
//	result : ���� �����
//	info : party ����
//	players : party�� �ִ� player����
struct stX2G_RM_ENTER_PARTY_ACK
{
	stX2G_RM_ENTER_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	stPartyInfo info;
	std::vector<stPartyPlayer> players;
};


//party ���� �뺸
//	player : ������ player����
struct stX2G_RM_ENTER_PARTY_NTF
{
	stX2G_RM_ENTER_PARTY_NTF()
	{
	}

	stPartyPlayer player;
};


//party ���� ��û(��Ƽ-->���� �̵�)
struct stX2G_RM_LEAVE_PARTY_REQ
{
	stX2G_RM_LEAVE_PARTY_REQ()
	{
	}

};


//party ���� ��û�� ���� ����
//	result : ���� �����
struct stX2G_RM_LEAVE_PARTY_ACK
{
	stX2G_RM_LEAVE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//party ���� �뺸
//	accountpk : ������ player����
struct stX2G_RM_LEAVE_PARTY_NTF
{
	stX2G_RM_LEAVE_PARTY_NTF()
		: accountpk(0)
	{
	}

	ACCOUNTPK accountpk;
};


//party ��� �뺸(��Ƽ�� ����� �ڵ� ���)
struct stX2G_RM_CLOSED_PARTY_NTF
{
	stX2G_RM_CLOSED_PARTY_NTF()
	{
	}

};


//�̵� ��û
//	pos : ��ġ����
struct stX2G_RM_MOVE_REQ
{
	stX2G_RM_MOVE_REQ()
	{
	}

	stPlayerPos pos;
};


//�̵� ��û�� ���� ����
//	result : ���� �����
//	pos : ��ġ����
struct stX2G_RM_MOVE_ACK
{
	stX2G_RM_MOVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	stPlayerPos pos;
};


//�̵� �뺸
//	accountpk :  �̵��� player����
//	pos : ��ġ����
struct stX2G_RM_MOVE_NTF
{
	stX2G_RM_MOVE_NTF()
		: accountpk(0)
	{
	}

	ACCOUNTPK accountpk;
	stPlayerPos pos;
};
