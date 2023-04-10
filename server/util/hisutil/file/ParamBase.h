#pragma once

#include "IniLoader.h"


namespace HisUtil {

	class IParamBase
	{
	public:
		IParamBase()
		{
		}
		virtual ~IParamBase()
		{
			loader_.Close();
		}

		virtual int Open(LPCTSTR filename)
		{
			if (FALSE == loader_.Open(filename))
				return 0xFFFF;// SERVER_INI_OPEN_FAIL;//여기서 오류가 나면 0 이외의 값으로 리턴하세요.

			return Read();
		}

		//config 파일 정보를 가져온다.
		virtual int Read() = 0;

		//경우에 따라서는 config정보를 갱신할 필요도 있다(그때마다 구현한다.)
		//virtual BOOL Write();

	protected:
		int Read_DB(LPCTSTR keyName, ADO_DATABASE_INFO& dbinfo);
		int Read_Ftp(LPCTSTR keyName, FTP_SERVER_INFO& ftp);


	protected:
		CIniLoader loader_;

	};

};//..namespace HisUtil {


/* CParam sample
class CParam : public IParamBase
{
public:
	CParam() {}
	~CParam() {}


	BOOL Read() {}
};
*/