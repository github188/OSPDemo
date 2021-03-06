# Microsoft Developer Studio Project File - Name="prj_win32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=prj_win32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client.mak" CFG="prj_win32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "prj_win32 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "prj_win32 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "prj_win32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 OspDll.lib /nologo /subsystem:console /machine:I386 /libpath:"../../lib"

!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Version.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "prj_win32 - Win32 Release"
# Name "prj_win32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\common\callback.cpp
# End Source File
# Begin Source File

SOURCE=..\source\fileapp\clientfileinstance.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgapp\clientinstance.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\interface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\logprintf.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\main.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\osphelpc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\outputtoconsole.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\client.h
# End Source File
# Begin Source File

SOURCE=..\..\include\cscommon.h
# End Source File
# Begin Source File

SOURCE=..\include\interface.h
# End Source File
# Begin Source File

SOURCE=..\include\uccommand.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\kdvdef.h
# End Source File
# Begin Source File

SOURCE=.\kdvtype.h
# End Source File
# Begin Source File

SOURCE=.\osp.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# End Group
# Begin Group "CMD Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\user\connectservercmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\interruptconnectcmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\requserlistcmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\sendfilecmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\user\sendmsgcmd.cpp
# End Source File
# End Group
# Begin Group "Instance Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\msgapp\daemonconnectagain.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgapp\daemonconnectcmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgapp\daemonsendmsgcmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\fileapp\fileinsreadfilecmd.cpp
# End Source File
# Begin Source File

SOURCE=..\source\fileapp\fileinstreadnextbuf.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgapp\instancebufnotify.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgapp\instancesendfilecontent.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgapp\instsendfileinfo.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\OspDll.dll
# End Source File
# Begin Source File

SOURCE=.\OspDll.lib
# End Source File
# End Target
# End Project
