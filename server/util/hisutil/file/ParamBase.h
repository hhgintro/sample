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
				return 0xFFFF;// SERVER_INI_OPEN_FAIL;//���⼭ ������ ���� 0 �̿��� ������ �����ϼ���.

			return Read();
		}

		//config ���� ������ �����´�.
		virtual int Read() = 0;

		//��쿡 ���󼭴� config������ ������ �ʿ䵵 �ִ�(�׶����� �����Ѵ�.)
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