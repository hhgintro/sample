#pragma once

namespace HisUtil {
	//로그인
	//로그아웃
	//FTP서버에 연결되어있으면 TRUE, 아니면 FALSE
	//파일만 다운로드
	//하위 디렉토리까지 포함하여 다운로드
	//파일만 업로드
	//하위디렉토리포함 업로드
	//FTP서버에 디렉토리를 생성(서버에 없는 디렉토리는 생성한다. 가령 strRemoteDir이 /123/456/789인 경우 /123, /123/456 디렉토리가 없다면 생성한다)
	//FTP서버 파일 또는 디렉토리 이름변경
	//FTP서버의 하위디렉토리 포함 삭제
	//FTP서버의 파일 삭제
	//FTP서버 현재 디렉토리 변경
	//FTP서버의 현재 디렉토리 경로를 구함
	//FTP서버의 파일 크기를 구함(성공 TRUE, 실패 FALSE)
	//FTP서버에 특정 디렉토리가 있는지 확인. FTP서버에 디렉토리가 존재하면 1, 오류인경우 -1, 없으면 0
	//FTP서버에 특정 파일이 있는지 확인. FTP서버에 파일이 존재하면 존재하면 1, 오류인경우 -1, 없으면 0
	//하위 디렉토리 포함한 파일목록(디렉토리+파일)을 구함
	//FTP의 디렉토리 파일목록(디렉토리+파일)을 구함. 하위디렉토리 미포함

	BOOL sendFtp(const TCHAR* ftp, unsigned short port, const TCHAR* user, const TCHAR* pass, const TCHAR* localFullPath, TCHAR* remoteDir, TCHAR* remoteFile);
	BOOL recvFtp(const TCHAR* ftp, unsigned short port, const TCHAR* user, const TCHAR* pass, TCHAR* remoteFullPath, const TCHAR* localFullPath);
};