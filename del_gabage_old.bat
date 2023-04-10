#@echo off


rem ===============
rem current path
rem ===============
set currentpath=%cd%



rem ===============
rem directory delete
rem ===============


rem ===============================================

rmdir %cd%\server\bin\Log /S /Q
rmdir %cd%\server\bin\util\Log /S /Q



rem ===============================================

rmdir %cd%\server\util\Pidl\Debug /S /Q
rmdir %cd%\server\util\Pidl\Release /S /Q
rmdir %cd%\server\util\Pidl\x64 /S /Q
rmdir %cd%\server\util\Pidl\ipch /S /Q

rmdir %cd%\server\util\errorexport\Debug /S /Q
rmdir %cd%\server\util\errorexport\Release /S /Q
rmdir %cd%\server\util\errorexport\x64 /S /Q
rmdir %cd%\server\util\errorexport\ipch /S /Q

rmdir %cd%\server\util\HiRedis\Debug /S /Q
rmdir %cd%\server\util\HiRedis\Release /S /Q
rmdir %cd%\server\util\HiRedis\x64 /S /Q
rmdir %cd%\server\util\HiRedis\ipch /S /Q

rmdir %cd%\server\util\hisutil\Debug /S /Q
rmdir %cd%\server\util\hisutil\Release /S /Q
rmdir %cd%\server\util\hisutil\x64 /S /Q
rmdir %cd%\server\util\hisutil\ipch /S /Q

rmdir %cd%\server\util\md5\Debug /S /Q
rmdir %cd%\server\util\md5\Release /S /Q
rmdir %cd%\server\util\md5\x64 /S /Q
rmdir %cd%\server\util\md5\ipch /S /Q

rmdir %cd%\server\util\Json\Debug /S /Q
rmdir %cd%\server\util\Json\Release /S /Q
rmdir %cd%\server\util\Json\x64 /S /Q
rmdir %cd%\server\util\Json\ipch /S /Q

rmdir %cd%\server\util\netcore\Debug /S /Q
rmdir %cd%\server\util\netcore\Release /S /Q
rmdir %cd%\server\util\netcore\ipch /S /Q
rmdir %cd%\server\util\netcore\source\Debug /S /Q
rmdir %cd%\server\util\netcore\source\Release /S /Q
rmdir %cd%\server\util\netcore\source\ipch /S /Q
rmdir %cd%\server\util\netcore\source\pidl\Debug /S /Q
rmdir %cd%\server\util\netcore\source\pidl\Release /S /Q
rmdir %cd%\server\util\netcore\source\pidl\x64 /S /Q
rmdir %cd%\server\util\netcore\source\netcore\Debug /S /Q
rmdir %cd%\server\util\netcore\source\netcore\Release /S /Q
rmdir %cd%\server\util\netcore\source\netcore\x64 /S /Q

rmdir %cd%\server\util\PacketGenerator\Debug /S /Q
rmdir %cd%\server\util\PacketGenerator\Release /S /Q
rmdir %cd%\server\util\PacketGenerator\x64 /S /Q
rmdir %cd%\server\util\PacketGenerator\ipch /S /Q

rmdir %cd%\server\util\tinyxml\source\Debug /S /Q
rmdir %cd%\server\util\tinyxml\source\Release /S /Q
rmdir %cd%\server\util\tinyxml\source\x64 /S /Q
rmdir %cd%\server\util\tinyxml\source\ipch /S /Q




rem ===============================================

rmdir %cd%\server\source\Debug /S /Q
rmdir %cd%\server\source\Release /S /Q
rmdir %cd%\server\source\ipch /S /Q
rmdir %cd%\server\source\client\Debug /S /Q
rmdir %cd%\server\source\client\Release /S /Q
rmdir %cd%\server\source\client\x64 /S /Q
rmdir %cd%\server\source\GameServer\Debug /S /Q
rmdir %cd%\server\source\GameServer\Release /S /Q
rmdir %cd%\server\source\GameServer\x64 /S /Q
rmdir %cd%\server\source\LobbyServer\Debug /S /Q
rmdir %cd%\server\source\LobbyServer\Release /S /Q
rmdir %cd%\server\source\LobbyServer\x64 /S /Q
rmdir %cd%\server\source\MasterServer\Debug /S /Q
rmdir %cd%\server\source\MasterServer\Release /S /Q
rmdir %cd%\server\source\MasterServer\x64 /S /Q
rmdir %cd%\server\source\pidl\Debug /S /Q
rmdir %cd%\server\source\pidl\Release /S /Q
rmdir %cd%\server\source\pidl\x64 /S /Q




rem ===============================================

rmdir %cd%\server\sample\bin\log /S /Q

rmdir %cd%\server\sample\test_crypt_rsa\ipch /S /Q
rmdir %cd%\server\sample\test_crypt_rsa\x64 /S /Q
rmdir %cd%\server\sample\test_crypt_rsa\Debug /S /Q
rmdir %cd%\server\sample\test_crypt_rsa\Release /S /Q

rmdir %cd%\server\sample\test_crypt_rsa_prime\ipch /S /Q
rmdir %cd%\server\sample\test_crypt_rsa_prime\x64 /S /Q
rmdir %cd%\server\sample\test_crypt_rsa_prime\Debug /S /Q
rmdir %cd%\server\sample\test_crypt_rsa_prime\Release /S /Q

rmdir %cd%\server\sample\test_crypt_rsa_class\ipch /S /Q
rmdir %cd%\server\sample\test_crypt_rsa_class\x64 /S /Q
rmdir %cd%\server\sample\test_crypt_rsa_class\Debug /S /Q
rmdir %cd%\server\sample\test_crypt_rsa_class\Release /S /Q

rmdir %cd%\server\sample\test_game_server\bin\Log /S /Q
rmdir %cd%\server\sample\test_game_server\Debug /S /Q
rmdir %cd%\server\sample\test_game_server\Release /S /Q
rmdir %cd%\server\sample\test_game_server\ipch /S /Q
rmdir %cd%\server\sample\test_game_server\x64 /S /Q
rmdir %cd%\server\sample\test_game_server\server\Debug/S /Q
rmdir %cd%\server\sample\test_game_server\server\Release/S /Q
rmdir %cd%\server\sample\test_game_server\server\x64 /S /Q
rmdir %cd%\server\sample\test_game_server\client\Debug /S /Q
rmdir %cd%\server\sample\test_game_server\client\Release /S /Q
rmdir %cd%\server\sample\test_game_server\client\x64 /S /Q

rmdir %cd%\server\sample\test_hisutil_critical\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_critical\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_critical\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_critical\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_db\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_db\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_db\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_db\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_directory\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_directory\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_directory\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_directory\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_iocp\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\Release /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\client\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\client\Release /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\client\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\client\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\server\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\server\Release /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\server\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_iocp\server\x64 /S /Q

rmdir %cd%\server\sample\test_hisutil_log\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_log\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_log\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_log\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_module\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_module\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_module\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_module\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_msg\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_msg\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_msg\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_msg\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_packetbuffer\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_packetbuffer\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_packetbuffer\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_packetbuffer\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_pool\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_pool\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_pool\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_pool\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_thread\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_thread\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_thread\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_thread\Release /S /Q

rmdir %cd%\server\sample\test_hisutil_time\ipch /S /Q
rmdir %cd%\server\sample\test_hisutil_time\x64 /S /Q
rmdir %cd%\server\sample\test_hisutil_time\Debug /S /Q
rmdir %cd%\server\sample\test_hisutil_time\Release /S /Q

rmdir %cd%\server\sample\test_json\ipch /S /Q
rmdir %cd%\server\sample\test_json\x64 /S /Q
rmdir %cd%\server\sample\test_json\Debug /S /Q
rmdir %cd%\server\sample\test_json\Release /S /Q

rmdir %cd%\server\sample\test_md5\ipch /S /Q
rmdir %cd%\server\sample\test_md5\x64 /S /Q
rmdir %cd%\server\sample\test_md5\Debug /S /Q
rmdir %cd%\server\sample\test_md5\Release /S /Q




rem ===============
rem file delete
rem ===============

del %cd%\server\bin\*.exe

rem ***** util폴더에는 exe만 있으면 된다. *****
del %cd%\server\bin\util\*.pdb /S
del %cd%\server\bin\util\*.map /S



del %cd%\*.bsc /S
del %cd%\*.ilk /S
del %cd%\*.opensdf /S /A:H
del %cd%\*.suo /S /F /A:H
del %cd%\*.sdf /S
del %cd%\*.db /S
del %cd%\*.bak /S
del %cd%\*.iobj /S
del %cd%\*.ipdb /S


del %cd%\server\bin\*.pdb /S
del %cd%\server\bin\*.map /S


del %cd%\server\sample\*.exe /S
del %cd%\server\sample\*.pdb /S
del %cd%\server\sample\*.map /S

pause