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
		, eClient	//받드시 있어야 하는 값.
		, eMAX
	};
};
