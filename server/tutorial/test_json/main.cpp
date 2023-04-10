// server.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void test()
{
	{
		/*
		char test[] = {
			"{\"pid\":1000,\"data\":[{\"ip\":\"127.0.0.1\",\"svc\":[{\"name\":\"telnet\",\"patch\":0,\"running\":1,\"mem\":0,\"cpu\":0},{\"name\":\"chrome\",\"patch\":0,\"running\":1,\"mem\":0,\"cpu\":0},{\"name\":\"V3Lite\",\"patch\":0,\"running\":1,\"mem\":0,\"cpu\":0},{\"name\":\"TestServer\",\"patch\":0,\"running\":0,\"mem\":0,\"cpu\":0}]}]}",
		};
		*/
		char test[] = {
			"{\"pid\":1000,\"data\":[{\"ip\":\"127.0.0.1\",\"svc\":[{\"name\":\"telnet\",\"patch\":0,\"running\":1,\"mem\":0,\"cpu\":0},{\"name\":\"chrome\",\"patch\":0,\"running\":1,\"mem\":0,\"cpu\":0},{\"name\":\"V3Lite\",\"patch\":0,\"running\":1,\"mem\":0,\"cpu\":0},{\"name\":\"TestServer\",\"patch\":0,\"running\":0,\"mem\":0,\"cpu\":0}]}]}",
		};
		Json::Reader reader;
		Json::Value root;
		bool parsingRet = reader.parse(test, root);

		if (!parsingRet)
		{
			printf("Failed to parse Json : %s\n", reader.getFormattedErrorMessages().c_str());
			return;
		}

		//pid
		printf("=================pid:%d\n", root["pid"].asInt());

		//data
		const Json::Value datas = root["data"];
		for (int i = 0; i < (int)datas.size(); i++)
		{
			if (datas[i].isObject())
			{
				//std::cout << datas[i].asString() << std::endl;

			//data
				printf("ip:%s\n", datas[i]["ip"].asString().c_str());
				Json::Value svc = datas[i]["svc"];
				for (int cnt = 0; cnt < (int)svc.size(); cnt++)
				{
					if (svc[cnt].isObject())
					{
						//std::cout << (*it)["name"].asString() << " : " << (*it)["age"].asInt() << std::endl;
						printf("\t%s(%d)", svc[cnt]["name"].asString().c_str(), svc[cnt]["running"].asInt());
					}
				}
				printf("\n");
			}

		}
		printf("\n");




	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	system("pause");
	return 0;

	char str[] = "{"
		"\"age\" : 19,"
		"\"friends\" : [{\"age\" : 21,\"name\" : \"Tom\"},{\"age\" : 23,\"name\" : \"jane\"}],"
		"\"hasCar\" : false,"
		"\"id\" : \"Luna\","
		"\"items\" : [\"nootbook\", \"ipadmini2\", \"iphone5s\"],"
		"\"name\" : \"Silver\""
		"}";

	//printf("%s\n", str);


	Json::Reader reader;
	Json::Value root;
	bool parsingRet = reader.parse(str, root);

	if (!parsingRet)
	{
		std::cout << "Failed to parse Json : " << reader.getFormattedErrorMessages();
		return 0;
	}

	std::cout << "has a car : " << root["hasCar"].asBool() << " / age : " << root["age"].asInt() << std::endl << std::endl;

	//items
	const Json::Value items = root["items"];
	for (int i = 0; i < (int)items.size(); i++)
	{
		std::cout << items[i].asString() << std::endl;
	}
	std::cout << std::endl;

	//keyword
	auto member = root.getMemberNames();
	for (std::string s : member)
	{
		std::cout << s << std::endl;
	}
	std::cout << std::endl;

	for (std::string s : member)
	{
		if (root[s].isString())
		{
			std::cout << root[s].asString() << std::endl;
		}
	}
	std::cout << std::endl;

	//friends
	Json::Value friends = root["friends"];
	for (auto it = friends.begin(); it != friends.end(); it++)
	{
		if (it->isObject())
		{
			std::cout << (*it)["name"].asString() << " : " << (*it)["age"].asInt() << std::endl;
		}
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}
