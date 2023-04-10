#pragma once

namespace NetCore {

#define MAKEINT64(a, b)		((((INT64)(a)) & 0xffffffff) << 32 | (((INT32)(b)) & 0xffffffff))

	//udp reliabel / unreilable
	const PACKET_CONTEXT UNRELIABLE = 0;
	const PACKET_CONTEXT RELIABLE = 1;

	const WORD CORE_UDP_RELAY_SERVER_TO_PEER_NTF = 0xFFD1;
	//const WORD CORE_UDP_HOLE_PUNCHING_PEER_REQ			= 0xFFD2;
	//const WORD CORE_UDP_HOLE_PUNCHING_PEER_ACK			= 0xFFD3;

	const TIME_T HEART_BEAT_REQUEST_TICK = TIME_SEC(10);//heart beat를 요청하는 주기
														//const TIME_T HEART_BEAT_PERMIT_TICK		= TIME_SEC(30);//heart beat를 허용 체크 시간 ==> 시간조절이 가능하게 함수로 처리함.
	const int HEART_BEAT_AVERAGE_COUNT = 10;//Heart Beat 평균을 최근 n 개를 가지고 계산한다.

	const int HOLE_PUNCHING_ATTEMPT_COUNT = 5;
	const TIME_T UDP_RE_SEND_DELAY_TICK = TIME_MSEC(500);
	//프로토콜 버전(netcore)
	//const PROTOCOL_T PT_VERSION = 104;
	const int PACKET_NUM_VALID_RANGE = 5;

	const WORD UDP_ACK = 0xD1E2;


	//server전용 : TCP, UDP 혼용
#define ON_RECEIVE_FROM_CLIENT(a)		case a: { On##a(session, msgRecv);				/*LOGEVENT("Session_Packet_Timer", _T("TIMER %s takes %I64d ms"), HisUtil::String(#a).w_str(), HisUtil::GetUniversalTime()-timeTakes);*/	} break;	//recv : client --> server
	//#define ON_RECEIVE_FROM_CLIENT(a)		case a: { On##a(session, msgRecv);				LOGEVENT("Session_Packet_Timer", _T("TIMER 0x%04x takes %I64d ms"), a, ::GetTickCount64()-timeTakes);	} break;	//recv : client --> server

	//ip/port로 remote를 등록하는 시점이므로 ip/port가 전달되어야 한다.
	//NetC2S_CORE_UDP_HOLE_PUNCHING_SERVER_REQ 에서만 사용한다.
#define ON_RECEIVE_FROM_CLIENT_UDP(a)	case a: { On##a(msgRecv, remoteIP, remotePort);	/*LOGEVENT("Session_Packet_Timer", _T("TIMER %s takes %I64d ms"), HisUtil::String(#a).w_str(), HisUtil::GetUniversalTime()-timeTakes);*/	} break;	//recv : client --> server
	//#define ON_RECEIVE_FROM_CLIENT_UDP(a)	case a: { On##a(msgRecv, remoteIP, remotePort);	LOGEVENT("Session_Packet_Timer", _T("TIMER 0x%04x takes %I64d ms"), a, ::GetTickCount64()-timeTakes);	} break;	//recv : client --> server

	//client전용 : TCP, UDP 혼용
#define ON_RECEIVE_ON_CLIENT(a)			case a: { On##a(msgRecv); } break;
#define ON_RECEIVE_ON_CLIENT_UDP(a)		case a: { On##a(msgRecv, remoteIP, remotePort); } break;

	//server, client 공용
	//#define READ_PACKET(protocol)			st##protocol st;	RECV_##protocol(msgRecv, st);
	//server 용
#define READ_PACKET_SERVER(protocol)	st##protocol st;	try {RECV_##protocol(msgRecv, st);}catch(HisUtil::PacketID id){LOGEVENT("Session_Base_Error",_T("protocol:0x%x 버퍼초과"),id);ProcessDisconnect(session);}
	//client 용
#define READ_PACKET_CLIENT(protocol)	st##protocol st;	RECV_##protocol(msgRecv, st);


#define __HEART_BEAT__		1	//주기적으로 heart beat를 체크합니다.(다수의 grouping에서는 연결종료되는 현상 확인됨)
};//..namespace NetCore {