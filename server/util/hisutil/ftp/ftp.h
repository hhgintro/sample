#pragma once

namespace HisUtil {
	//�α���
	//�α׾ƿ�
	//FTP������ ����Ǿ������� TRUE, �ƴϸ� FALSE
	//���ϸ� �ٿ�ε�
	//���� ���丮���� �����Ͽ� �ٿ�ε�
	//���ϸ� ���ε�
	//�������丮���� ���ε�
	//FTP������ ���丮�� ����(������ ���� ���丮�� �����Ѵ�. ���� strRemoteDir�� /123/456/789�� ��� /123, /123/456 ���丮�� ���ٸ� �����Ѵ�)
	//FTP���� ���� �Ǵ� ���丮 �̸�����
	//FTP������ �������丮 ���� ����
	//FTP������ ���� ����
	//FTP���� ���� ���丮 ����
	//FTP������ ���� ���丮 ��θ� ����
	//FTP������ ���� ũ�⸦ ����(���� TRUE, ���� FALSE)
	//FTP������ Ư�� ���丮�� �ִ��� Ȯ��. FTP������ ���丮�� �����ϸ� 1, �����ΰ�� -1, ������ 0
	//FTP������ Ư�� ������ �ִ��� Ȯ��. FTP������ ������ �����ϸ� �����ϸ� 1, �����ΰ�� -1, ������ 0
	//���� ���丮 ������ ���ϸ��(���丮+����)�� ����
	//FTP�� ���丮 ���ϸ��(���丮+����)�� ����. �������丮 ������

	BOOL sendFtp(const TCHAR* ftp, unsigned short port, const TCHAR* user, const TCHAR* pass, const TCHAR* localFullPath, TCHAR* remoteDir, TCHAR* remoteFile);
	BOOL recvFtp(const TCHAR* ftp, unsigned short port, const TCHAR* user, const TCHAR* pass, TCHAR* remoteFullPath, const TCHAR* localFullPath);
};