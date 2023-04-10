
using System.Collections.Generic;

namespace CSampleClient {
	static public class GameResult_kr
	{
		static Dictionary<int, string> GameResultCodeString = new Dictionary<int, string>();

		static void LoadGameResultString()
		{
			GameResultCodeString.Add(0, "(0) 성공");
			GameResultCodeString.Add(1, "(1) 프로토콜 버전이 다르다(core)");
			GameResultCodeString.Add(2, "(2) 홀펀칭 회수 초과");
			GameResultCodeString.Add(100, "(100) DB Exception발생");
			GameResultCodeString.Add(101, "(101) DB open 실패");
			GameResultCodeString.Add(102, "(102) DB 확인되지 않은 오류입니다.");
			GameResultCodeString.Add(103, "(103) 계정정보를 확인할 수 없습니다.");
			GameResultCodeString.Add(104, "(104) 계정정보가 이미 존재합니다.");
			GameResultCodeString.Add(105, "(105) 추천인을 확인할 수 없습니다.");
			GameResultCodeString.Add(106, "(106) 관리자 보유금액이 부족합니다.");
			GameResultCodeString.Add(107, "(107) 관리자 보유 보너스금액이 부족합니다.");
			GameResultCodeString.Add(108, "(108) 자신의 share율 보다 높게 설정할 수 없습니다.");
			GameResultCodeString.Add(109, "(109) 자신의 rolling율 보다 높게 설정할 수 없습니다.");
			GameResultCodeString.Add(110, "(110) 대상자를 확인할 수 없습니다.");
			GameResultCodeString.Add(111, "(111) 별명이 너무 짧다.");
			GameResultCodeString.Add(112, "(112) 비번이 너무 짧다.");
			GameResultCodeString.Add(113, "(113) 같은 비번은 변경할 수 없습니다.");
			GameResultCodeString.Add(200, "(200) 경주 정보를 확인할 수 없습니다.");
			GameResultCodeString.Add(300, "(300) 배팅금액이 부족합니다.");
			GameResultCodeString.Add(301, "(301) 상품권 금액이 부족합니다.");
			GameResultCodeString.Add(700, "(700) 입출금 요청정보를 확인할 수 없습니다.");
			GameResultCodeString.Add(701, "(701) 입출금 처리가 삭제되었습니다.");
			GameResultCodeString.Add(702, "(702) 입출금 처리가 완료되었습니다.");
			GameResultCodeString.Add(703, "(703) 출금 금액이 부족합니다.");
			GameResultCodeString.Add(704, "(704) 입금 금액이 부족합니다.");
			GameResultCodeString.Add(705, "(705) 입출금 처리가 불가합니다.");
			GameResultCodeString.Add(900, "(900) 지난주 정산이 완료되어서, 더 할일이 없다.");
			GameResultCodeString.Add(901, "(901) 배당금 이미 수령하다.");
			GameResultCodeString.Add(902, "(902) 배당금 수령 정보를 확인할 수 없습니다.");
			GameResultCodeString.Add(903, "(903) 수령가능한 롤링 배당금이 없습니다.");
			GameResultCodeString.Add(904, "(904) 본사의 예치금이 부족합니다.");
			GameResultCodeString.Add(1000, "(1000) 프로토콜 버전이 다르다");
			GameResultCodeString.Add(1001, "(1001) 계정서버를 확인할 수 없습니다.");
			GameResultCodeString.Add(1002, "(1002) 게임서버를 확인할 수 없습니다.");
			GameResultCodeString.Add(1003, "(1003) 동일 계정으로 접속이 확인되어 종료합니다(접속종료).");
			GameResultCodeString.Add(1004, "(1004) 동일 계정으로 접속이 확인되었습니다(확인용).");
			GameResultCodeString.Add(1005, "(1005) 등록된 계정정보가 없습니다.");
			GameResultCodeString.Add(1006, "(1006) 사용할 수 없는 계정입니다.");
			GameResultCodeString.Add(1007, "(1007) Account서버에 계정정보가 확인되지 않습니다.");
			GameResultCodeString.Add(1008, "(1008) Account서버에서 인증이 실패하였습니다.");
			GameResultCodeString.Add(1009, "(1009) Game서버에 등록된 계정정보가 없습니다.");
			GameResultCodeString.Add(1010, "(1010) 게임서버가 닫혀있습니다. 잠시후에 이용해 주세요.");
			GameResultCodeString.Add(1011, "(1011) 경마(track)서버를 확인할 수 없습니다.");
			GameResultCodeString.Add(1012, "(1012) 점검 시간입니다.");
			GameResultCodeString.Add(1013, "(1013) 경마정보를 확인할 수 없습니다.");
			GameResultCodeString.Add(1014, "(1014) 다음 경기까지 기다려 주세요");
			GameResultCodeString.Add(1015, "(1015) 배팅이 마감될때 까지 기다려 주세요.");
			GameResultCodeString.Add(1016, "(1016) 게임에 입장해 주세요");
			GameResultCodeString.Add(1017, "(1017) 배팅 총합이 일치하지 않는다.");
			GameResultCodeString.Add(2000, "(2000) Account서버에 계정정보가 확인되지 않습니다.");
			GameResultCodeString.Add(2001, "(2001) 권한을 확인하여 주세요.");
			GameResultCodeString.Add(2002, "(2002) 검색 결과가 없습니다.");
			GameResultCodeString.Add(2003, "(2003) 비번이 일치하지 않습니다.");
			GameResultCodeString.Add(2004, "(2004) Agent가 실행하고 있지 않습니다.");
			GameResultCodeString.Add(2005, "(2005) 서비스 시작실패.");
			GameResultCodeString.Add(2006, "(2006) 서비스 중지실패.");
			GameResultCodeString.Add(2007, "(2007) 서비스 GM 중지불가(즉시 재시작)");
			GameResultCodeString.Add(3000, "(3000) 데이타가 확인되지 않습니다.");
			GameResultCodeString.Add(3001, "(3001) MAX_GAME_RESULT");
		}		

		static public string GetGameResultString(int result) {
			if (0 == GameResultCodeString.Count)
				LoadGameResultString();

			if (GameResultCodeString.ContainsKey(result))
				return GameResultCodeString[result];
			return "";
		}
	}
}