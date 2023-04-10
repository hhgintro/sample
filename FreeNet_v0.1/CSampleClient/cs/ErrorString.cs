
using System.Collections.Generic;

namespace CSampleClient {
	static public class GameResult
	{
		static Dictionary<int, string> GameResultCodeString = new Dictionary<int, string>();

		static void LoadGameResultString()
		{
			GameResultCodeString.Add(0, "Success");
			GameResultCodeString.Add(1, "differ protocol version");
			GameResultCodeString.Add(2, "hole punching exceed ther count limit");
			GameResultCodeString.Add(100, "DB Exception occurred");
			GameResultCodeString.Add(101, "DB open failed.");
			GameResultCodeString.Add(102, "DB is not verified error.");
			GameResultCodeString.Add(103, "I can't check my account information.");
			GameResultCodeString.Add(104, "Account information already exists.");
			GameResultCodeString.Add(105, "I can't check who recommended it.");
			GameResultCodeString.Add(106, "The amount of money the manager has is insufficient.");
			GameResultCodeString.Add(107, "The amount of bonus the manager has is insufficient.");
			GameResultCodeString.Add(108, "You cannot set it higher than your dividend rate.");
			GameResultCodeString.Add(109, "We can't identify the target.");
			GameResultCodeString.Add(110, "Nickname is too short.");
			GameResultCodeString.Add(111, "The password is too short.");
			GameResultCodeString.Add(112, "You can't change the same password.");
			GameResultCodeString.Add(200, "I can't check the race information.");
			GameResultCodeString.Add(300, "We don't have enough betting money.");
			GameResultCodeString.Add(301, "I don't have enough money for the gift certificate.");
			GameResultCodeString.Add(700, "I can't check the deposit and withdrawal request information.");
			GameResultCodeString.Add(701, "Deposit and withdrawal processing has been deleted.");
			GameResultCodeString.Add(702, "The deposit and withdrawal process has been completed.");
			GameResultCodeString.Add(703, "The withdrawal amount is insufficient..");
			GameResultCodeString.Add(1000, "differ protocol version");
			GameResultCodeString.Add(1001, "I can't check the account server");
			GameResultCodeString.Add(1002, "I can't check the game server");
			GameResultCodeString.Add(1003, "proud1");
			GameResultCodeString.Add(1004, "The connection has been confirmed with the same account and terminates (connection termination)");
			GameResultCodeString.Add(1005, "There is no account information registered on the server");
			GameResultCodeString.Add(1006, "You can't use this account.");
			GameResultCodeString.Add(1007, "Account information is not verified on the account server");
			GameResultCodeString.Add(1008, "Authentication failed on the account server");
			GameResultCodeString.Add(1009, "There is no account information registered on the game server");
			GameResultCodeString.Add(1010, "The game server is closed. Please use it later");
			GameResultCodeString.Add(1011, "I can't check the track server");
			GameResultCodeString.Add(1012, "It's time to check.");
			GameResultCodeString.Add(1013, "I can't check the horse racing information");
			GameResultCodeString.Add(1014, "Please wait until the next game");
			GameResultCodeString.Add(1015, "Please wait until the bet is closed");
			GameResultCodeString.Add(1016, "Please enter the game");
			GameResultCodeString.Add(1017, "The total number of bets doesn't match.");
			GameResultCodeString.Add(2000, "Account information is not verified on the account server");
			GameResultCodeString.Add(2001, "Please check the authority");
			GameResultCodeString.Add(2002, "There's no search result");
			GameResultCodeString.Add(2003, "The password doesn't match.");
			GameResultCodeString.Add(2004, "Agent is not running it");
			GameResultCodeString.Add(2005, "Service start failed");
			GameResultCodeString.Add(2006, "Failed to stop the service");
			GameResultCodeString.Add(2007, "Service GM cannot be stopped (immediate restart)");
			GameResultCodeString.Add(3000, "I can't check the data.");
			GameResultCodeString.Add(3001, "MAX_GAME_RESULT");
		}		

		static public string GetGameResultString(int result) {
			if (0 == GameResultCodeString.Count)
				LoadGameResultString();

			if (GameResultCodeString.ContainsKey(result))
				return "(" + result.ToString() + ")" + GameResultCodeString[result];
			return "";
		}
	}
}