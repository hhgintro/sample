@echo off


rem bin\hisutil
rem echo 옵션 : d(디렉토리), f(파일) ==> Xcopy 은(는) 대상의 파일 이름입니까 아니면 디렉토리 이름입니까?
echo d | xcopy %cd%\server\bin\hisutil\* %cd%\..\LogSystem\bin\hisutil\. /Y /S

rem bin/netcore
rem echo 옵션 : d(디렉토리), f(파일) ==> Xcopy 은(는) 대상의 파일 이름입니까 아니면 디렉토리 이름입니까?
echo d | rem xcopy %cd%\server\bin\netcore\* %cd%\..\LogSystem\bin\netcore\. /Y /S



rem util\hisutil
rem echo 옵션 : d(디렉토리), f(파일) ==> Xcopy 은(는) 대상의 파일 이름입니까 아니면 디렉토리 이름입니까?
echo d | xcopy %cd%\server\util\hisutil\*.h %cd%\..\LogSystem\LogSystem\util\hisutil\. /Y /S

rem util/netcore
rem echo 옵션 : d(디렉토리), f(파일) ==> Xcopy 은(는) 대상의 파일 이름입니까 아니면 디렉토리 이름입니까?
rem echo d | xcopy %cd%\server\util\netcore\*.h %cd%\..\LogSystem\LogSystem\util\netcore\. /Y /S

rem util/tinyxml
rem tinyxml은 cpp, h 를 모두 전달한다.(단 하위폴더는 안보내기 위해 /S 옵션을 제거함)
rem echo 옵션 : d(디렉토리), f(파일) ==> Xcopy 은(는) 대상의 파일 이름입니까 아니면 디렉토리 이름입니까?
echo d | xcopy %cd%\server\util\tinyxml\*.* %cd%\..\LogSystem\LogSystem\util\tinyxml\. /Y

pause