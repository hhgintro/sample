#pragma once

namespace HisUtil
{
	//����(Directrory) ����-�������� ����
	//DeleteFolder(_T("C:\\Documents and Settings\\Ȳ�λ�\\���� ȭ��\\Sample.2009.09.30\\�纻 - HisLib"))
	void DeleteFolder(char* szDirectory);// ���� ������ '\\'���� �����Ѵ�('/'�νľ��� : "C:\\"-- O, "C:/" -- X)
	void DeleteFolder(const TCHAR* lpFolder);


	//�������丮 �����Ͽ� ���丮�� �����Ѵ�
	//���� dirpath�� c:\123\456\789��� c:\, c:\123, c:\123\456, c:\123\456\789 ������ �����Ѵ�
	BOOL CreateSubDir(const TCHAR* dirpath);

	// 0 : ���丮�� 0 ��ȯ
	// 1 : ����
	// -1 : ���� �Ǵ� ���丮�� ������ -1 ��ȯ
	int isFileOrDir(TCHAR* path);

};//..namespace HisUtil
