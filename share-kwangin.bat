@echo off


rem bin\hisutil
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | xcopy %cd%\server\bin\hisutil\* %cd%\..\LogSystem\bin\hisutil\. /Y /S

rem bin/netcore
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | rem xcopy %cd%\server\bin\netcore\* %cd%\..\LogSystem\bin\netcore\. /Y /S



rem util\hisutil
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | xcopy %cd%\server\util\hisutil\*.h %cd%\..\LogSystem\LogSystem\util\hisutil\. /Y /S

rem util/netcore
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
rem echo d | xcopy %cd%\server\util\netcore\*.h %cd%\..\LogSystem\LogSystem\util\netcore\. /Y /S

rem util/tinyxml
rem tinyxml�� cpp, h �� ��� �����Ѵ�.(�� ���������� �Ⱥ����� ���� /S �ɼ��� ������)
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | xcopy %cd%\server\util\tinyxml\*.* %cd%\..\LogSystem\LogSystem\util\tinyxml\. /Y

pause