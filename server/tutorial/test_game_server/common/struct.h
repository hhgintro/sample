#pragma once



struct PARTY {
	enum STATUS {
		eReady			//광장
		, eRunning		//방생성 진행
		, eClosed		//방폐쇄
	};
};

struct ROOM {
	enum TYPE {
		eSquare			//광장
						//, eWaitingRoom	//대기방
		, eSports		//체력단련실(탁구,...)
		, eConference	//회의
		, eEducation	//교육
		, eMax
	};
};

struct stEquip
{
	int gender;		//성별
	int myhair;		//hair
	int myhead;		//head
	int mycloth;	//cloth
	int myskincolor;	//skin color
	int myclothcolor;	//cloth color

	stEquip() : gender(0), myhair(0), myhead(0), mycloth(0), myskincolor(0), myclothcolor(0)
	{}
	void Clear()
	{
		gender = 0;
		myhair = 0;
		myhead = 0;
		mycloth = 0;
		myskincolor = 0;
		myclothcolor = 0;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stEquip& equip)
	{
		equip.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stEquip& equip)
	{
		equip.UnpackInfo(msg);
		return msg;
	}

	stEquip& operator = (stEquip& rhs)
	{
		if (this == &rhs)
			return *this;
		gender = rhs.gender;
		myhair = rhs.myhair;
		myhead = rhs.myhead;
		mycloth = rhs.mycloth;
		myskincolor = rhs.myskincolor;
		myclothcolor = rhs.myclothcolor;
		return *this;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		msg << gender
			<< myhair
			<< myhead
			<< mycloth
			<< myskincolor
			<< myclothcolor;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		msg >> gender
			>> myhair
			>> myhead
			>> mycloth
			>> myskincolor
			>> myclothcolor;
	}
};

struct stInven// : public stEquip
{
	stEquip equip;

	int hashairtype;	//소유한 hair
	int hasheadtype;	//소유한 head
	int hasclothtype;	//소유한 cloth

	stInven() : hashairtype(0), hasheadtype(0), hasclothtype(0)
	{}
	void Clear()
	{
		equip.Clear();
		hashairtype = 0;
		hasheadtype = 0;
		hasclothtype = 0;
	}
	stInven& operator = (stInven& rhs)
	{
		if (this == &rhs)
			return *this;
		equip = rhs.equip;
		hashairtype = rhs.hashairtype;
		hasheadtype = rhs.hasheadtype;
		hasclothtype = rhs.hasclothtype;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stInven& inven)
	{
		inven.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stInven& inven)
	{
		inven.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		//equip.PackInfo(msg);

		msg << equip
			<< hashairtype
			<< hasheadtype
			<< hasclothtype;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		//equip.UnpackInfo(msg);

		msg >> equip
			>> hashairtype
			>> hasheadtype
			>> hasclothtype;
	}

};


struct stVector3
{
	float x, y, z;

	stVector3() : x(0), y(0), z(0)
	{}
	void Clear()
	{
		x = 0; y = 0; z = 0;
	}

	stVector3& operator = (stVector3& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stVector3& vec)
	{
		vec.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stVector3& vec)
	{
		vec.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		msg << x << y << z;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		msg >> x >> y >> z;
	}

};

struct stVector4
{
	float w, x, y, z;

	stVector4() : w(0), x(0), y(0), z(0)
	{}
	void Clear()
	{
		w = 0;  x = 0; y = 0; z = 0;
	}

	stVector4& operator = (stVector4& rhs)
	{
		if (this == &rhs)
			return *this;
		w = rhs.w;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stVector4& vec)
	{
		vec.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stVector4& vec)
	{
		vec.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		msg << w << x << y << z;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		msg >> w >> x >> y >> z;
	}

};

struct stPlayerPos
{
	stVector3 posPlayer;	//player 위치
	stVector3 posHmd;		//hmd 위치
	stVector4 rotHmd;		//hmd 쿼터니언
	stVector3 posCtrlR;		//R-controller 위치
	stVector4 rotCtrlR;		//R-controller 쿼터니언
	stVector3 posCtrlL;		//L-controller 위치
	stVector4 rotCtrlL;		//L-controller 쿼터니언

	stPlayerPos()
	{}
	void Clear()
	{
		posPlayer.Clear();
		posHmd.Clear();
		rotHmd.Clear();
		posCtrlR.Clear();
		rotCtrlR.Clear();
		posCtrlL.Clear();
		rotCtrlL.Clear();
	}

	stPlayerPos& operator = (stPlayerPos& rhs)
	{
		if (this == &rhs)
			return *this;
		posPlayer = rhs.posPlayer;
		posHmd = rhs.posHmd;
		rotHmd = rhs.rotHmd;
		posCtrlR = rhs.posCtrlR;
		rotCtrlR = rhs.rotCtrlR;
		posCtrlL = rhs.posCtrlL;
		rotCtrlL = rhs.rotCtrlL;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stPlayerPos& pos)
	{
		pos.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stPlayerPos& pos)
	{
		pos.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		msg << posPlayer
			<< posHmd
			<< rotHmd
			<< posCtrlR
			<< rotCtrlR
			<< posCtrlL
			<< rotCtrlL;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		msg >> posPlayer
			>> posHmd
			>> rotHmd
			>> posCtrlR
			>> rotCtrlR
			>> posCtrlL
			>> rotCtrlL;
	}

};

struct stPartyPlayer
{
	ACCOUNTPK accountpk;		//account pk
	std::wstring accountid;		//계정명
								//stEquip equip;
								//stPlayerPos pos;

	stPartyPlayer() : accountpk(0), accountid(L"")
	{}
	void Clear()
	{
		accountpk = 0;
		accountid = L"";
		//equip.Clear();
		//pos.Clear();
	}

	stPartyPlayer& operator = (stPartyPlayer& rhs)
	{
		if (this == &rhs)
			return *this;
		accountpk = rhs.accountpk;
		accountid = rhs.accountid;
		//equip = rhs.equip;
		//pos = rhs.pos;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stPartyPlayer& inven)
	{
		inven.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stPartyPlayer& inven)
	{
		inven.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		//equip.PackInfo(msg);

		msg << accountpk
			<< accountid;
		//<< equip
		//<< pos;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		//equip.UnpackInfo(msg);

		msg >> accountpk
			>> accountid;
		//>> equip
		//>> pos;
	}

};

struct stRoomPlayer
{
	ACCOUNTPK accountpk;		//account pk
	std::wstring accountid;		//계정명
	stEquip equip;				//장착정보
	stPlayerPos pos;			//위치정보

	stRoomPlayer() : accountpk(0), accountid(L"")
	{}
	void Clear()
	{
		accountpk = 0;
		accountid = L"";
		equip.Clear();
		pos.Clear();
	}

	stRoomPlayer& operator = (stRoomPlayer& rhs)
	{
		if (this == &rhs)
			return *this;
		accountpk = rhs.accountpk;
		accountid = rhs.accountid;
		equip = rhs.equip;
		pos = rhs.pos;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stRoomPlayer& inven)
	{
		inven.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stRoomPlayer& inven)
	{
		inven.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		//equip.PackInfo(msg);

		msg << accountpk
			<< accountid
			<< equip
			<< pos;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		//equip.UnpackInfo(msg);

		msg >> accountpk
			>> accountid
			>> equip
			>> pos;
	}

};

struct stPartyInfo
{
	PARTYINDEX index;	//party 번호
	UINT8 type;			//방타입(0:광장, 1:체력단련실, 2:회의실, 3:교육실)
	UINT8 curplayer;	//방현재 인원
	UINT8 maxplayer;	//방최대 인원
	std::wstring accountid;	//방장

	stPartyInfo() : index(0), type(0), curplayer(0), maxplayer(0), accountid(L"")
	{}
	void Clear()
	{
		index = 0;
		type = 0;
		curplayer = 0;
		maxplayer = 0;
		accountid = L"";
	}

	stPartyInfo& operator = (stPartyInfo& rhs)
	{
		if (this == &rhs)
			return *this;
		index = rhs.index;
		type = rhs.type;
		curplayer = rhs.curplayer;
		maxplayer = rhs.maxplayer;
		accountid = rhs.accountid;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stPartyInfo& inven)
	{
		inven.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stPartyInfo& inven)
	{
		inven.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		msg << index
			<< type
			<< curplayer
			<< maxplayer
			<< accountid;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		msg >> index
			>> type
			>> curplayer
			>> maxplayer
			>> accountid;
	}

};


struct stRoomInfo
{
	ACCOUNTPK accountpk;
	std::wstring accountid;
	stEquip equip;
	stPlayerPos pos;

	stRoomInfo() : accountpk(0), accountid(L"")
	{}
	void Clear()
	{
		accountpk = 0;
		accountid = L"";
		equip.Clear();
		pos.Clear();
	}

	stRoomInfo& operator = (stRoomInfo& rhs)
	{
		if (this == &rhs)
			return *this;
		accountpk = rhs.accountpk;
		accountid = rhs.accountid;
		equip = rhs.equip;
		pos = rhs.pos;
		return *this;
	}

	friend HisUtil::CMsg& operator << (HisUtil::CMsg& msg, stRoomInfo& inven)
	{
		inven.PackInfo(msg);
		return msg;
	}

	friend HisUtil::CMsg& operator >> (HisUtil::CMsg& msg, stRoomInfo& inven)
	{
		inven.UnpackInfo(msg);
		return msg;
	}

	void PackInfo(HisUtil::CMsg& msg)
	{
		//equip.PackInfo(msg);

		msg << accountpk
			<< accountid
			<< equip
			<< pos;
	}
	void UnpackInfo(HisUtil::CMsg& msg)
	{
		//equip.UnpackInfo(msg);

		msg >> accountpk
			>> accountid
			>> equip
			>> pos;
	}

};
