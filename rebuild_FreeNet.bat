rem $(ProjectName)$(Configuration)$(PlatformTarget)

set VS_PATH="C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe"
set SOLUTION_NAME="%cd%\FreeNet_v0.1\FreeNet.sln"

rem %VS_PATH% %SOLUTION_NAME% /Clean "Debug"
%VS_PATH% %SOLUTION_NAME% /Clean "Release"
rem pause

rem %VS_PATH% %SOLUTION_NAME% /Build "Debug|Any CPU"
%VS_PATH% %SOLUTION_NAME% /Build "Release|Any CPU"
rem pause
