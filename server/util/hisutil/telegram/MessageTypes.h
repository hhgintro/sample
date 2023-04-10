#pragma once


enum message_type
{
	notmessage

	, ePlay_Ani_Finished	//애니메이션이 끝났다.
	, eStart_Battle		//전투가 시작되었습니다.
	, eChase_Target		//타켓을 추격하라.
	, eAlert_Tartget	//타겟을 경계하라.
	, eLost_Target		//target 해제
	, eDie_Disappear		//사망후 사라짐
	, eDie_Avartar_Revival		//avatar 회생 처리
	, eDie_Revival		//회생 처리
	, eNo_Rival			//무적

	, eReset_Battle_Zone	//인던 완료후 재갱신(reset)

	, eSkill_UseSkill		//스킬 사용
	, eSkill_ComboAttack	//스킬 공격시작
	, eSkill_Progress_Complete	//스킬시전 종료(이제 다른 스킬 시전 가능)

	, eBattle_Object_Move_For_Attack	//공격을 위한 이동
	, eBattle_Object_Move_Completed		//이동 종료
	, eBattle_Object_Attack_Completed	//공격 종료(턴종료)

	, eTrade_Auto_Cancel				//일정시간 응답이 없다면 자동 취소됨

	, eParty_Auto_Leave					//일정시간 동안 재접속하지 않으면 탈퇴처리된다.
	, eParty_Close						//파티를 닫는다.

	, eAuction_Success_Time				//낙찰시간

	//, eItem_Remove_Zone_Item			//맵에 떨어뜨린 아이템 삭제
	//, eItem_Remove_Single_Zone_Item		//싱글맵에 떨어뜨린 아이템 삭제

	, eDungeon_Zone_Release				//zone을 삭제한다(던전)


	//이곳에 추가가 필요한 경우 저에게 noti해 주세요(황현기)
	//..





	//HG[2013.08.27]추가는 이 위쪽에서 해주면 좋겠습니다.(권장)
	, eAccount_Disconnect	//유저 접속 종료처리
	, eAccount_Remove		//유저 정보 메모리 정리
	, eMax_Message_Type				//최대값.
};
