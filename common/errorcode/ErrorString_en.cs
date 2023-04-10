
using System.Collections.Generic;

namespace CSampleClient {
	static public class GameResult_en
	{
		static Dictionary<int, string> GameResultCodeString = new Dictionary<int, string>();

		static void LoadGameResultString()
		{
			GameResultCodeString.Add(0, "(0) Success");
			GameResultCodeString.Add(1, "(1) DB Exception발생");
			GameResultCodeString.Add(2, "(2) DB 확인되지 않은 오류입니다.");
			GameResultCodeString.Add(3, "(3) DB 확인되지 않은 오류입니다.");
			GameResultCodeString.Add(10, "(10) 계정정보를 확인할 수 없습니다.");
			GameResultCodeString.Add(11, "(11) 계정정보가 이미 존재합니다.");
			GameResultCodeString.Add(12, "(12) 추천인을 확인할 수 없습니다.");
			GameResultCodeString.Add(100, "(100) differ protocol version");
			GameResultCodeString.Add(101, "(101) hole punching exceed ther count limit");
			GameResultCodeString.Add(200, "(200) differ protocol version");
			GameResultCodeString.Add(201, "(201) proud1");
			GameResultCodeString.Add(202, "(202) proud1");
			GameResultCodeString.Add(203, "(203) proud1");
			GameResultCodeString.Add(204, "(204) proud1");
			GameResultCodeString.Add(205, "(205) proud1");
			GameResultCodeString.Add(206, "(206) proud2");
			GameResultCodeString.Add(207, "(207) proud2");
			GameResultCodeString.Add(208, "(208) proud1");
			GameResultCodeString.Add(209, "(209) Please wait until the next game");
			GameResultCodeString.Add(210, "(210) Please wait until the next game");
			GameResultCodeString.Add(211, "(211) Please wait until the next game");
			GameResultCodeString.Add(212, "(212) proud3");
			GameResultCodeString.Add(213, "(213) MAX_GAME_RESULT");
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