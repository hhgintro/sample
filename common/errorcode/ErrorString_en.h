#pragma once
#include <map>


namespace GameResult_en {
	std::map<int, std::wstring> GameResultCodeString;

	static void LoadGameResultString()
	{
		GameResultCodeString.insert(std::pair<int, std::wstring>(0, L"(0) Success"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(1, L"(1) DB Exception발생"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(2, L"(2) DB 확인되지 않은 오류입니다."));
		GameResultCodeString.insert(std::pair<int, std::wstring>(3, L"(3) DB 확인되지 않은 오류입니다."));
		GameResultCodeString.insert(std::pair<int, std::wstring>(10, L"(10) 계정정보를 확인할 수 없습니다."));
		GameResultCodeString.insert(std::pair<int, std::wstring>(11, L"(11) 계정정보가 이미 존재합니다."));
		GameResultCodeString.insert(std::pair<int, std::wstring>(12, L"(12) 추천인을 확인할 수 없습니다."));
		GameResultCodeString.insert(std::pair<int, std::wstring>(100, L"(100) differ protocol version"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(101, L"(101) hole punching exceed ther count limit"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(200, L"(200) differ protocol version"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(201, L"(201) proud1"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(202, L"(202) proud1"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(203, L"(203) proud1"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(204, L"(204) proud1"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(205, L"(205) proud1"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(206, L"(206) proud2"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(207, L"(207) proud2"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(208, L"(208) proud1"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(209, L"(209) Please wait until the next game"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(210, L"(210) Please wait until the next game"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(211, L"(211) Please wait until the next game"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(212, L"(212) proud3"));
		GameResultCodeString.insert(std::pair<int, std::wstring>(213, L"(213) MAX_GAME_RESULT"));
	}

	static const WCHAR* GetGameResultString(int result) {
		if (0 == GameResultCodeString.size())
			LoadGameResultString();

		std::map<int, std::wstring>::iterator it = GameResultCodeString.find(result);
		if (it != GameResultCodeString.end())
			return (*it).second.c_str();
		return L"";
	}
} //namespace GameResult {