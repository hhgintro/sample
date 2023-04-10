@echo off

:1
timeout -t 10 /nobreak

rem time( 10:08:31.51 )
rem 시:분:초.51 --> 시분초.51
SET CURTIME_SEC=%time::=%
echo %CURTIME_SEC%

rem 시분초만 가져옵니다.(소수점 제거)
SET CURTIME=%CURTIME_SEC:~0,6%

robocopy /mir d:/Araxis d:/Araxis_%date%_%CURTIME%
goto 1

rem pause