@echo off


rem bin\hisutil
xcopy %cd%\server\bin\hisutil\* %cd%\..\telepresence\server\bin\hisutil\. /Y /S
xcopy %cd%\server\bin\hisutil\* %cd%\..\kid_traffic\server\bin\hisutil\. /Y /S

rem bin/netcore
xcopy %cd%\server\bin\netcore\* %cd%\..\telepresence\server\bin\netcore\. /Y /S
xcopy %cd%\server\bin\netcore\* %cd%\..\kid_traffic\server\bin\netcore\. /Y /S

rem util\hisutil
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | xcopy %cd%\server\util\hisutil\*.h %cd%\..\telepresence\server\util\hisutil\. /Y /S
echo d | xcopy %cd%\server\util\hisutil\*.h %cd%\..\kid_traffic\server\util\hisutil\. /Y /S

rem bin/netcore
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | xcopy %cd%\server\util\netcore\*.h %cd%\..\telepresence\server\util\netcore\. /Y /S
echo d | xcopy %cd%\server\util\netcore\*.h %cd%\..\kid_traffic\server\util\netcore\. /Y /S

rem bin/netcore
rem echo �ɼ� : d(���丮), f(����) ==> Xcopy ��(��) ����� ���� �̸��Դϱ� �ƴϸ� ���丮 �̸��Դϱ�?
echo d | xcopy %cd%\server\util\tinyxml\*.h %cd%\..\telepresence\server\util\tinyxml\. /Y /S
echo d | xcopy %cd%\server\util\tinyxml\*.h %cd%\..\kid_traffic\server\util\tinyxml\. /Y /S

pause