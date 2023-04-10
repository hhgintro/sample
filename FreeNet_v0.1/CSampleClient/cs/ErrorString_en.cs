
using System.Collections.Generic;

namespace CSampleClient {
	static public class GameResult_en
	{
		static Dictionary<int, string> GameResultCodeString = new Dictionary<int, string>();

		static void LoadGameResultString()
		{
			GameResultCodeString.Add(0, "(0) Success");
			GameResultCodeString.Add(1, "(1) differ protocol version");
			GameResultCodeString.Add(2, "(2) hole punching exceed ther count limit");
			GameResultCodeString.Add(100, "(100) DB Exception occurred");
			GameResultCodeString.Add(101, "(101) DB open failed.");
			GameResultCodeString.Add(102, "(102) DB is not verified error.");
			GameResultCodeString.Add(103, "(103) I can't check my account information.");
			GameResultCodeString.Add(104, "(104) Account information already exists.");
			GameResultCodeString.Add(105, "(105) I can't check who recommended it.");
			GameResultCodeString.Add(106, "(106) The amount of money the manager has is insufficient.");
			GameResultCodeString.Add(107, "(107) The amount of bonus the manager has is insufficient.");
			GameResultCodeString.Add(108, "(108) You cannot set it higher than your dividend share rate.");
			GameResultCodeString.Add(109, "(109) You cannot set it higher than your dividend rolling rate.");
			GameResultCodeString.Add(110, "(110) We can't identify the target.");
			GameResultCodeString.Add(111, "(111) Nickname is too short.");
			GameResultCodeString.Add(112, "(112) The password is too short.");
			GameResultCodeString.Add(113, "(113) You can't change the same password.");
			GameResultCodeString.Add(200, "(200) I can't check the race information.");
			GameResultCodeString.Add(300, "(300) We don't have enough betting money.");
			GameResultCodeString.Add(301, "(301) I don't have enough money for the gift certificate.");
			GameResultCodeString.Add(700, "(700) I can't check the deposit and withdrawal request information.");
			GameResultCodeString.Add(701, "(701) Deposit and withdrawal processing has been deleted.");
			GameResultCodeString.Add(702, "(702) The deposit and withdrawal process has been completed.");
			GameResultCodeString.Add(703, "(703) The withdrawal amount is insufficient.");
			GameResultCodeString.Add(704, "(704) We don't have enough money.");
			GameResultCodeString.Add(705, "(705) Deposit and withdrawal cannot be processed.");
			GameResultCodeString.Add(900, "(900) Last week's settlement was completed.");
			GameResultCodeString.Add(901, "(901) Already received dividends.");
			GameResultCodeString.Add(902, "(902) Dividend receipt information cannot be checked.");
			GameResultCodeString.Add(903, "(903) There is no rolling dividend available.");
			GameResultCodeString.Add(904, "(904) We don't have enough money to deposit at our headquarters.");
			GameResultCodeString.Add(1000, "(1000) differ protocol version");
			GameResultCodeString.Add(1001, "(1001) I can't check the account server");
			GameResultCodeString.Add(1002, "(1002) I can't check the game server");
			GameResultCodeString.Add(1003, "(1003) proud1");
			GameResultCodeString.Add(1004, "(1004) The connection has been confirmed with the same account and terminates (connection termination)");
			GameResultCodeString.Add(1005, "(1005) There is no account information registered on the server");
			GameResultCodeString.Add(1006, "(1006) You can't use this account.");
			GameResultCodeString.Add(1007, "(1007) Account information is not verified on the account server");
			GameResultCodeString.Add(1008, "(1008) Authentication failed on the account server");
			GameResultCodeString.Add(1009, "(1009) There is no account information registered on the game server");
			GameResultCodeString.Add(1010, "(1010) The game server is closed. Please use it later");
			GameResultCodeString.Add(1011, "(1011) I can't check the track server");
			GameResultCodeString.Add(1012, "(1012) It's time to check.");
			GameResultCodeString.Add(1013, "(1013) I can't check the horse racing information");
			GameResultCodeString.Add(1014, "(1014) Please wait until the next game");
			GameResultCodeString.Add(1015, "(1015) Please wait until the bet is closed");
			GameResultCodeString.Add(1016, "(1016) Please enter the game");
			GameResultCodeString.Add(1017, "(1017) The total number of bets doesn't match.");
			GameResultCodeString.Add(2000, "(2000) Account information is not verified on the account server");
			GameResultCodeString.Add(2001, "(2001) Please check the authority");
			GameResultCodeString.Add(2002, "(2002) There's no search result");
			GameResultCodeString.Add(2003, "(2003) The password doesn't match.");
			GameResultCodeString.Add(2004, "(2004) Agent is not running it");
			GameResultCodeString.Add(2005, "(2005) Service start failed");
			GameResultCodeString.Add(2006, "(2006) Failed to stop the service");
			GameResultCodeString.Add(2007, "(2007) Service GM cannot be stopped (immediate restart)");
			GameResultCodeString.Add(3000, "(3000) I can't check the data.");
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