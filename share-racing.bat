@echo off
rem echo 옵션 : d(디렉토리), f(파일) ==> Xcopy 은(는) 대상의 파일 이름입니까 아니면 디렉토리 이름입니까?


echo d | xcopy %cd%\server\util\netcore\pidl\cs\NetC2S*.cs %cd%\FreeNet_v0.1\FreeNet\cs\. /Y /S


echo | call %cd%\rebuild_hisutil.bat
echo | call %cd%\rebuild_netcore.bat
echo | call %cd%\rebuild_tinyxml.bat
echo | call %cd%\rebuild_FreeNet.bat


rem hisutil
echo d | xcopy %cd%\server\util\hisutil\*.h %cd%\..\HorseRacing\source\server\util\hisutil\. /Y /S
echo d | xcopy %cd%\server\util\hisutil\*.inl %cd%\..\HorseRacing\source\server\util\hisutil\. /Y /S
echo d | xcopy %cd%\server\bin\hisutil\*.lib %cd%\..\HorseRacing\source\server\bin\hisutil\. /Y /S

rem tinyxml
echo d | xcopy %cd%\server\util\tinyxml\*.h %cd%\..\HorseRacing\source\server\util\tinyxml\. /Y /S
echo d | xcopy %cd%\server\bin\tinyxml\*.lib %cd%\..\HorseRacing\source\server\bin\tinyxml\. /Y /S

rem netcore
echo d | xcopy %cd%\server\util\netcore\*.h %cd%\..\HorseRacing\source\server\util\netcore\. /Y /S
echo d | xcopy %cd%\server\bin\netcore\*.lib %cd%\..\HorseRacing\source\server\bin\netcore\. /Y /S

rem util
rem echo d | xcopy %cd%\server\bin\util\config\*.* %cd%\..\HorseRacing\source\server\bin\util\config\. /Y /S
echo d | xcopy %cd%\server\bin\util\*.exe %cd%\..\HorseRacing\source\server\bin\util\. /Y /S

rem FreeNet
echo d | xcopy %cd%\FreeNet_v0.1\FreeNet\bin\Release\*.dll %cd%\..\HorseRacing\source\Client\RaceGame_Unity\Assets\Plugins\V2FreeNet\. /Y /S
echo d | xcopy %cd%\FreeNet_v0.1\FreeNet\bin\Release\*.dll %cd%\..\HorseRacing\source\AdminTool\AdminTool\Assets\FreeNet\. /Y /S

rem pause