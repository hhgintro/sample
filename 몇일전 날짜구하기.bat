@echo off

set CURRENT_PATH=%cd%

echo %CURRENT_PATH%

rem ���ó��� ���ϱ�
set toyear=%date:~-10,4%
set tomons=%date:~-5,2%
set today=%date:~-2,2%

SET yyyymmdd=%toyear%%tomons%%today%
ECHO %yyyymmdd%

powershell "(get-date).adddays(-5).ToString('yyyyMMdd')"



@echo off

rem �ۼ��ѳ� http://blog.naver.com/mokomoji/130117861406
setlocal

rem ī��Ʈdday - 40
set countday=40

 

rem ���ó��� ���ϱ�
set toyear=%date:~-10,4%
set tomons=%date:~-5,2%
set today=%date:~-2,2%
 

rem �̹��� 10���� ������ 0�� ���� 10�� ���� �޼� ����ȭ - ����������� ������ ���� �Ǿ� ����

if %tomons% lss 10 set tomons=%tomons:0=%

rem �̹��� 10���� ������ 0�� ���� 10�� ���� ���� ����ȭ - ����������� ������ ���� �Ǿ� ����

if %today% lss 10 set today=%today:0=%
rem ���� ��¥ ��� d-day ȭ�鿡 ���

echo %toyear% %tomons% %today% - %countday%

rem ���ó�¥�� d-day ���� ũ�� lssday ȣ���ϰ� ���� 

if %today% gtr %countday% call :lssday&&goto :end

rem ���ó�¥�� d-day ������ equday ȣ���ϰ� ���� 
if %today% equ %countday% call :equday&&goto :end

rem �׿ܰ���� gtrday�� ȣ��
call :gtrday

rem ������� 3

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

rem �������1
echo %toyear% %tomons% %countday%
goto :eof

 


:equday
 set /a tomons=%tomons%-1
if %tomons% equ 0 set tomons=12&set /a toyear=%toyear%-1
call :mons%tomons%

rem �������2
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

rem ���� ���
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
