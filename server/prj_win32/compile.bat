@echo off

rem 编译Debug/Release版本


echo server.exe build begin

@msdev server.dsp /MAKE "server - Win32 Debug" /REBUILD /NORECURSE /OUT ..\version\compileinfo\ospserver_D.txt
@msdev server.dsp /MAKE "server - Win32 Release" /REBUILD /NORECURSE /OUT ..\version\compileinfo\ospserver_R.txt

echo server.exe build over

copy /Y Debug\server.exe ..\version\debug\
copy /Y Release\server.exe ..\version\release\

copy /Y .\ospdll.dll ..\version\debug\
copy /Y .\ospdll.dll ..\version\release\

del  /f /s /q .\Debug
del  /f /s /q .\Release
del .\*.aps
del .\*.pdb
del .\*.ncb
del .\*.opt
del .\*.ncb
del .\*.plg
del .\*.dsw
del .\*.positions

pause
echo on
