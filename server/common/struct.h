#pragma once

const PROTOCOL_T PROTOCOL_VERION = 20171030;

struct REMOTE_ENTRY {
	enum {
		eNone
		, eControlServer
		, eMasterServer
		, eLobbyServer
		, eEntryServer
		, eGameServer
		, eServerMonitor
		, eClient	//�޵�� �־�� �ϴ� ��.
		, eMAX
	};
};
