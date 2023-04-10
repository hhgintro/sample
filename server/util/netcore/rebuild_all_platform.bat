rem $(ProjectName)$(Configuration)$(PlatformTarget)

set VS_PATH="C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.exe"
set SOLUTION_NAME="%cd%\NetCore.sln"

rem %VS_PATH% %SOLUTION_NAME% /Clean "Debug|x86"
rem %VS_PATH% %SOLUTION_NAME% /Clean "Release|x86"
%VS_PATH% %SOLUTION_NAME% /Clean "Debug|x64"
%VS_PATH% %SOLUTION_NAME% /Clean "Release|x64"
rem pause

rem %VS_PATH% %SOLUTION_NAME% /Build "Debug|x86"
rem %VS_PATH% %SOLUTION_NAME% /Build "Release|x86"
%VS_PATH% %SOLUTION_NAME% /Build "Debug|x64"
%VS_PATH% %SOLUTION_NAME% /Build "Release|x64"
rem pause
