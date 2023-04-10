@echo on

rem 예를 들어 다음과 같은 Path(D:/test/abcd/..)에 .svn 이라는 이름으로 된 폴더들(하위 파일 포함)
rem 을 한 번에 제거하고 싶다면 cmd 창에서 아래와 같은 명령어를 사용하면 된다.
rem
rem "FOR /F %I in ('DIR /S /B /A:D \test\abcd\*.svn') DO RD /S /Q %I"
rem
rem 단, 주의할 점은 삭제 대상 폴더가 있는 드라이브 경로로 먼저 이동한 후 명령어를 실행해야 정상적으로 삭제된다.
rem 그렇지 않으면 해당 디렉토리을 찾을 수 없다는 메시지만 출력한다.


rem ===============
rem current path
rem ===============
set CURRENT_PATH=%cd%

rem ===============
rem directory delete
rem ===============

FOR /F %%I in ('DIR /S /B /A:D .vs') DO RD /S /Q %%I
FOR /F %%I in ('DIR /S /B /A:D ipch') DO RD /S /Q %%I
FOR /F %%I in ('DIR /S /B /A:D x64') DO RD /S /Q %%I
FOR /F %%I in ('DIR /S /B /A:D Debug') DO RD /S /Q %%I
FOR /F %%I in ('DIR /S /B /A:D Release') DO RD /S /Q %%I
FOR /F %%I in ('DIR /S /B /A:D Log') DO RD /S /Q %%I



rem ===============
rem file delete
rem ===============

rem del %CURRENT_PATH%\server\bin\*.exe

pause