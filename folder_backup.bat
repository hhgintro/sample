@echo off

:1
timeout -t 10 /nobreak

rem time( 10:08:31.51 )
rem ��:��:��.51 --> �ú���.51
SET CURTIME_SEC=%time::=%
echo %CURTIME_SEC%

rem �ú��ʸ� �����ɴϴ�.(�Ҽ��� ����)
SET CURTIME=%CURTIME_SEC:~0,6%

robocopy /mir d:/Araxis d:/Araxis_%date%_%CURTIME%
goto 1

rem pause