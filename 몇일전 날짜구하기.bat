@echo off

set CURRENT_PATH=%cd%

echo %CURRENT_PATH%

rem 오늘날자 구하기
set toyear=%date:~-10,4%
set tomons=%date:~-5,2%
set today=%date:~-2,2%

SET yyyymmdd=%toyear%%tomons%%today%
ECHO %yyyymmdd%

powershell "(get-date).adddays(-5).ToString('yyyyMMdd')"



@echo off

rem 작성한놈 http://blog.naver.com/mokomoji/130117861406
setlocal

rem 카운트dday - 40
set countday=40

 

rem 오늘날자 구하기
set toyear=%date:~-10,4%
set tomons=%date:~-5,2%
set today=%date:~-2,2%
 

rem 이번달 10보다 작으면 0을 제거 10월 이하 달수 정수화 - 하지않을경우 진수로 변이 되어 에러

if %tomons% lss 10 set tomons=%tomons:0=%

rem 이번일 10보다 작으면 0을 제거 10일 이하 날자 정수화 - 하지않을경우 진수로 변이 되어 에러

if %today% lss 10 set today=%today:0=%
rem 오늘 날짜 찍고 d-day 화면에 출력

echo %toyear% %tomons% %today% - %countday%

rem 오늘날짜가 d-day 보다 크면 lssday 호출하고 끝냄 

if %today% gtr %countday% call :lssday&&goto :end

rem 오늘날짜가 d-day 같으면 equday 호출하고 끝냄 
if %today% equ %countday% call :equday&&goto :end

rem 그외계산은 gtrday를 호출
call :gtrday

rem 최종출력 3

echo %toyear% %tomons% %countday%
goto :end

 

:gtrday
set /a countday=%countday% - %today%
:loop
set /a tomons=%tomons%-1
if %tomons% equ 0 set tomons=12&set /a toyear=%toyear%-1
call :mons%tomons%
if %today% gtr %countday% set /a countday=%today% - %countday% &goto :eof
set /a countday=%countday% - %today%
goto :loop
goto :eof

 


:lssday
set /a countday=%today%-%countday%

rem 최종출력1
echo %toyear% %tomons% %countday%
goto :eof

 


:equday
 set /a tomons=%tomons%-1
if %tomons% equ 0 set tomons=12&set /a toyear=%toyear%-1
call :mons%tomons%

rem 최종출력2
echo %toyear% %tomons% %today%
goto :eof

 


:mons1
:mons3
:mons5
:mons7
:mons8
:mons10
:mons12
set today=31
goto :eof
:mons2

rem 윤년 계산
set today=28
set /a yunz1=%toyear% %%4
if %yunz1% equ 0 set today=29
set /a yunz2=%toyear% %%100
if %yunz2% equ 0 set today=28
set /a yunz3=%toyear% %%400
if %yunz3% equ 0 set today=29
goto :eof
:mons4
:mons6
:mons9
:mons11
set today=30
goto :eof
:end

endlocal
pause
