#pragma once

namespace HisUtil
{
	//폴더(Directrory) 삭제-하위폴더 포함
	//DeleteFolder(_T("C:\\Documents and Settings\\황인상\\바탕 화면\\Sample.2009.09.30\\사본 - HisLib"))
	void DeleteFolder(char* szDirectory);// 하위 폴더는 '\\'으로 적용한다('/'인식안함 : "C:\\"-- O, "C:/" -- X)
	void DeleteFolder(const TCHAR* lpFolder);


	//하위디렉토리 포함하여 디렉토리를 생성한다
	//가령 dirpath가 c:\123\456\789라면 c:\, c:\123, c:\123\456, c:\123\456\789 폴더를 생성한다
	BOOL CreateSubDir(const TCHAR* dirpath);

	// 0 : 디렉토리면 0 반환
	// 1 : 파일
	// -1 : 파일 또는 디렉토리가 없으면 -1 반환
	int isFileOrDir(TCHAR* path);

};//..namespace HisUtil
