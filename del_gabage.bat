@echo on

rem ���� ��� ������ ���� Path(D:/test/abcd/..)�� .svn �̶�� �̸����� �� ������(���� ���� ����)
rem �� �� ���� �����ϰ� �ʹٸ� cmd â���� �Ʒ��� ���� ��ɾ ����ϸ� �ȴ�.
rem
rem "FOR /F %I in ('DIR /S /B /A:D \test\abcd\*.svn') DO RD /S /Q %I"
rem
rem ��, ������ ���� ���� ��� ������ �ִ� ����̺� ��η� ���� �̵��� �� ��ɾ �����ؾ� ���������� �����ȴ�.
rem �׷��� ������ �ش� ���丮�� ã�� �� ���ٴ� �޽����� ����Ѵ�.


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