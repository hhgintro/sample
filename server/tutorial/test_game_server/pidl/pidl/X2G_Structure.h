#pragma once



//로그인 요청
//	account : 계정명
//	password : 인증키(password)
//	version : 프로토콜 버전
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


//로그인 요청에 대한 응답
//	result : 응답 결과값
//	accountpk : 계정 식별번호
struct stX2G_AC_LOGIN_ACK
{
	stX2G_AC_LOGIN_ACK()
		: result(0), accountpk(0)
	{
	}

	RESULT_T result;
	ACCOUNTPK accountpk;
};


//장착 정보 요청
struct stX2G_IN_EQUIP_LOAD_REQ
{
	stX2G_IN_EQUIP_LOAD_REQ()
	{
	}

};


//장착 정보 요청에 대한 응답
//	inven : 장착및 인벤정보
//	gender : 성별
//	myhair : hair
//	myhead : head
//	mycloth : cloth
//	myskincolor : skin color
//	myclothcolor : cloth color
//	hashairtype : 소유한 hair
//	hasheadtype : 소유한 head
//	hasclothtype : 소유한 cloth
struct stX2G_IN_EQUIP_LOAD_ACK
{
	stX2G_IN_EQUIP_LOAD_ACK()
	{
	}

	stInven inven;
};


//장착 정보 변경 요청
//	inven : 장착및 인벤정보
//	gender : 성별
//	myhair : hair
//	myhead : head
//	mycloth : cloth
//	myskincolor : skin color
//	myclothcolor : cloth color
//	hashairtype : 소유한 hair
//	hasheadtype : 소유한 head
//	hasclothtype : 소유한 cloth
struct stX2G_IN_EQUIP_UPDATE_REQ
{
	stX2G_IN_EQUIP_UPDATE_REQ()
	{
	}

	stInven inven;
};


//장착 정보 변경 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_IN_EQUIP_UPDATE_ACK
{
	stX2G_IN_EQUIP_UPDATE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//광장 입장 요청(기숙사-->광장 이동)
struct stX2G_RM_ENTER_SQUARE_REQ
{
	stX2G_RM_ENTER_SQUARE_REQ()
	{
	}

};


//방 입장 요청(파티장 권한)(광장-->탁구장등 이동)
struct stX2G_RM_ENTER_ROOM_REQ
{
	stX2G_RM_ENTER_ROOM_REQ()
	{
	}

};


//방(광장) 입장 요청에 대한 응답
//	result : 응답 결과값
//	players : 방에 있는 player정보
struct stX2G_RM_ENTER_ROOM_ACK
{
	stX2G_RM_ENTER_ROOM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	std::vector<stRoomPlayer> players;
};


//방(광장) 입장 통보
//	player : 입장한 player정보
struct stX2G_RM_ENTER_ROOM_NTF
{
	stX2G_RM_ENTER_ROOM_NTF()
	{
	}

	stRoomPlayer player;
};


//광장 퇴장 요청(광장-->기숙사 이동)
struct stX2G_RM_LEAVE_SQUARE_REQ
{
	stX2G_RM_LEAVE_SQUARE_REQ()
	{
	}

};


//방 퇴장 요청(탁구장등-->광장 이동)
struct stX2G_RM_LEAVE_ROOM_REQ
{
	stX2G_RM_LEAVE_ROOM_REQ()
	{
	}

};


//방(광장) 퇴장 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_RM_LEAVE_ROOM_ACK
{
	stX2G_RM_LEAVE_ROOM_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//방(광장) 퇴장 통보
//	accountpk : 퇴장한 player정보
struct stX2G_RM_LEAVE_ROOM_NTF
{
	stX2G_RM_LEAVE_ROOM_NTF()
		: accountpk(0)
	{
	}

	ACCOUNTPK accountpk;
};


//party 리스트 요청
//	type : 방타입(0:모두, 1:체력단련실, 2:회의실, 3:교육실)
//	page : 0~(해당 page)
//	cnt : page당 리스트개수
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


//party 리스트 요청에 대한 응답
//	parties : 파티정보
struct stX2G_RM_PARTY_LIST_ACK
{
	stX2G_RM_PARTY_LIST_ACK()
	{
	}

	std::vector<stPartyInfo> parties;
};


//party 생성 요청
//	type : 방타입(0:광장, 1:체력단련실, 2:회의실, 3:교육실)
//	maxplayer : 방최대 인원
struct stX2G_RM_CREATE_PARTY_REQ
{
	stX2G_RM_CREATE_PARTY_REQ()
		: type(0), maxplayer(0)
	{
	}

	UINT8 type;
	UINT8 maxplayer;
};


//party 생성 요청에 대한 응답
//	result : 응답 결과값
//	info : party 정보
struct stX2G_RM_CREATE_PARTY_ACK
{
	stX2G_RM_CREATE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	stPartyInfo info;
};


//party 입장 요청
//	index : 방번호
struct stX2G_RM_ENTER_PARTY_REQ
{
	stX2G_RM_ENTER_PARTY_REQ()
		: index(0)
	{
	}

	PARTYINDEX index;
};


//party 입장 요청에 대한 응답
//	result : 응답 결과값
//	info : party 정보
//	players : party에 있는 player정보
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


//party 입장 통보
//	player : 입장한 player정보
struct stX2G_RM_ENTER_PARTY_NTF
{
	stX2G_RM_ENTER_PARTY_NTF()
	{
	}

	stPartyPlayer player;
};


//party 퇴장 요청(파티-->광장 이동)
struct stX2G_RM_LEAVE_PARTY_REQ
{
	stX2G_RM_LEAVE_PARTY_REQ()
	{
	}

};


//party 퇴장 요청에 대한 응답
//	result : 응답 결과값
struct stX2G_RM_LEAVE_PARTY_ACK
{
	stX2G_RM_LEAVE_PARTY_ACK()
		: result(0)
	{
	}

	RESULT_T result;
};


//party 퇴장 통보
//	accountpk : 퇴장한 player정보
struct stX2G_RM_LEAVE_PARTY_NTF
{
	stX2G_RM_LEAVE_PARTY_NTF()
		: accountpk(0)
	{
	}

	ACCOUNTPK accountpk;
};


//party 폐쇄 통보(파티장 퇴장시 자동 폐쇄)
struct stX2G_RM_CLOSED_PARTY_NTF
{
	stX2G_RM_CLOSED_PARTY_NTF()
	{
	}

};


//이동 요청
//	pos : 위치정보
struct stX2G_RM_MOVE_REQ
{
	stX2G_RM_MOVE_REQ()
	{
	}

	stPlayerPos pos;
};


//이동 요청에 대한 응답
//	result : 응답 결과값
//	pos : 위치정보
struct stX2G_RM_MOVE_ACK
{
	stX2G_RM_MOVE_ACK()
		: result(0)
	{
	}

	RESULT_T result;
	stPlayerPos pos;
};


//이동 통보
//	accountpk :  이동한 player정보
//	pos : 위치정보
struct stX2G_RM_MOVE_NTF
{
	stX2G_RM_MOVE_NTF()
		: accountpk(0)
	{
	}

	ACCOUNTPK accountpk;
	stPlayerPos pos;
};
