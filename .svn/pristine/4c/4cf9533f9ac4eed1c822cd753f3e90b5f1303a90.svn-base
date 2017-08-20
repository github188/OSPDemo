@echo off

rem 编译Debug/Release版本
rem msdev client.dsp /MAKE "prj_win32 - Win32 Release" /REBUILD /NORECURSE /OUT ..\version\CompileInfo\ospclient_R.txt

echo client.exe build begin

@msdev client.dsp /MAKE "prj_win32 - Win32 Debug" /REBUILD /NORECURSE /OUT ..\version\CompileInfo\ospclient_D.txt
@msdev client.dsp /MAKE "prj_win32 - Win32 Release" /REBUILD /NORECURSE /OUT ..\version\CompileInfo\ospclient_R.txt

echo client.exe build over

copy /Y Debug\client.exe ..\version\debug\
copy /Y Release\client.exe ..\version\release\

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
del .\*.positions

pause

echo on
