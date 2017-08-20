# Microsoft Developer Studio Generated NMAKE File, Based on server.dsp
!IF "$(CFG)" == ""
CFG=server - Win32 Debug
!MESSAGE No configuration specified. Defaulting to server - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "server - Win32 Release" && "$(CFG)" != "server - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "server.mak" CFG="server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "server - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "server - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "server - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\server.exe"


CLEAN :
	-@erase "$(INTDIR)\broadcastmsg.obj"
	-@erase "$(INTDIR)\callback.obj"
	-@erase "$(INTDIR)\logprintf.obj"
	-@erase "$(INTDIR)\outputtoconsole.obj"
	-@erase "$(INTDIR)\procconnectreq.obj"
	-@erase "$(INTDIR)\procsendfilemsgreq.obj"
	-@erase "$(INTDIR)\procsendmsgnotify.obj"
	-@erase "$(INTDIR)\procsendmsgreq.obj"
	-@erase "$(INTDIR)\recvfilecontcmd.obj"
	-@erase "$(INTDIR)\recvfileinforeq.obj"
	-@erase "$(INTDIR)\requserlist.obj"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\serverfileinstance.obj"
	-@erase "$(INTDIR)\servermain.obj"
	-@erase "$(INTDIR)\servermsginstance.obj"
	-@erase "$(INTDIR)\telnethelp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\server.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\server.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Script1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\server.pdb" /machine:I386 /out:"$(OUTDIR)\server.exe" 
LINK32_OBJS= \
	"$(INTDIR)\callback.obj" \
	"$(INTDIR)\logprintf.obj" \
	"$(INTDIR)\outputtoconsole.obj" \
	"$(INTDIR)\serverfileinstance.obj" \
	"$(INTDIR)\servermain.obj" \
	"$(INTDIR)\servermsginstance.obj" \
	"$(INTDIR)\telnethelp.obj" \
	"$(INTDIR)\broadcastmsg.obj" \
	"$(INTDIR)\procconnectreq.obj" \
	"$(INTDIR)\procsendfilemsgreq.obj" \
	"$(INTDIR)\procsendmsgnotify.obj" \
	"$(INTDIR)\procsendmsgreq.obj" \
	"$(INTDIR)\recvfilecontcmd.obj" \
	"$(INTDIR)\recvfileinforeq.obj" \
	"$(INTDIR)\requserlist.obj" \
	"$(INTDIR)\Script1.res" \
	"..\..\lib\OspDll.lib" \
	"..\..\lib\OspLib.lib"

"$(OUTDIR)\server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "server - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\server.exe" "$(OUTDIR)\server.bsc"


CLEAN :
	-@erase "$(INTDIR)\broadcastmsg.obj"
	-@erase "$(INTDIR)\broadcastmsg.sbr"
	-@erase "$(INTDIR)\callback.obj"
	-@erase "$(INTDIR)\callback.sbr"
	-@erase "$(INTDIR)\logprintf.obj"
	-@erase "$(INTDIR)\logprintf.sbr"
	-@erase "$(INTDIR)\outputtoconsole.obj"
	-@erase "$(INTDIR)\outputtoconsole.sbr"
	-@erase "$(INTDIR)\procconnectreq.obj"
	-@erase "$(INTDIR)\procconnectreq.sbr"
	-@erase "$(INTDIR)\procsendfilemsgreq.obj"
	-@erase "$(INTDIR)\procsendfilemsgreq.sbr"
	-@erase "$(INTDIR)\procsendmsgnotify.obj"
	-@erase "$(INTDIR)\procsendmsgnotify.sbr"
	-@erase "$(INTDIR)\procsendmsgreq.obj"
	-@erase "$(INTDIR)\procsendmsgreq.sbr"
	-@erase "$(INTDIR)\recvfilecontcmd.obj"
	-@erase "$(INTDIR)\recvfilecontcmd.sbr"
	-@erase "$(INTDIR)\recvfileinforeq.obj"
	-@erase "$(INTDIR)\recvfileinforeq.sbr"
	-@erase "$(INTDIR)\requserlist.obj"
	-@erase "$(INTDIR)\requserlist.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\serverfileinstance.obj"
	-@erase "$(INTDIR)\serverfileinstance.sbr"
	-@erase "$(INTDIR)\servermain.obj"
	-@erase "$(INTDIR)\servermain.sbr"
	-@erase "$(INTDIR)\servermsginstance.obj"
	-@erase "$(INTDIR)\servermsginstance.sbr"
	-@erase "$(INTDIR)\telnethelp.obj"
	-@erase "$(INTDIR)\telnethelp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\server.bsc"
	-@erase "$(OUTDIR)\server.exe"
	-@erase "$(OUTDIR)\server.ilk"
	-@erase "$(OUTDIR)\server.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\server.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Script1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\server.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\callback.sbr" \
	"$(INTDIR)\logprintf.sbr" \
	"$(INTDIR)\outputtoconsole.sbr" \
	"$(INTDIR)\serverfileinstance.sbr" \
	"$(INTDIR)\servermain.sbr" \
	"$(INTDIR)\servermsginstance.sbr" \
	"$(INTDIR)\telnethelp.sbr" \
	"$(INTDIR)\broadcastmsg.sbr" \
	"$(INTDIR)\procconnectreq.sbr" \
	"$(INTDIR)\procsendfilemsgreq.sbr" \
	"$(INTDIR)\procsendmsgnotify.sbr" \
	"$(INTDIR)\procsendmsgreq.sbr" \
	"$(INTDIR)\recvfilecontcmd.sbr" \
	"$(INTDIR)\recvfileinforeq.sbr" \
	"$(INTDIR)\requserlist.sbr"

"$(OUTDIR)\server.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\server.pdb" /debug /machine:I386 /out:"$(OUTDIR)\server.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\callback.obj" \
	"$(INTDIR)\logprintf.obj" \
	"$(INTDIR)\outputtoconsole.obj" \
	"$(INTDIR)\serverfileinstance.obj" \
	"$(INTDIR)\servermain.obj" \
	"$(INTDIR)\servermsginstance.obj" \
	"$(INTDIR)\telnethelp.obj" \
	"$(INTDIR)\broadcastmsg.obj" \
	"$(INTDIR)\procconnectreq.obj" \
	"$(INTDIR)\procsendfilemsgreq.obj" \
	"$(INTDIR)\procsendmsgnotify.obj" \
	"$(INTDIR)\procsendmsgreq.obj" \
	"$(INTDIR)\recvfilecontcmd.obj" \
	"$(INTDIR)\recvfileinforeq.obj" \
	"$(INTDIR)\requserlist.obj" \
	"$(INTDIR)\Script1.res" \
	"..\..\lib\OspDll.lib" \
	"..\..\lib\OspLib.lib"

"$(OUTDIR)\server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("server.dep")
!INCLUDE "server.dep"
!ELSE 
!MESSAGE Warning: cannot find "server.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "server - Win32 Release" || "$(CFG)" == "server - Win32 Debug"
SOURCE=..\..\common\callback.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\callback.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\callback.obj"	"$(INTDIR)\callback.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\logprintf.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\logprintf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\logprintf.obj"	"$(INTDIR)\logprintf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\common\outputtoconsole.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\outputtoconsole.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\outputtoconsole.obj"	"$(INTDIR)\outputtoconsole.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\serverfileinstance.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\serverfileinstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\serverfileinstance.obj"	"$(INTDIR)\serverfileinstance.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\servermain.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\servermain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\servermain.obj"	"$(INTDIR)\servermain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\servermsginstance.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\servermsginstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\servermsginstance.obj"	"$(INTDIR)\servermsginstance.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\telnethelp.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\telnethelp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\telnethelp.obj"	"$(INTDIR)\telnethelp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Script1.rc

"$(INTDIR)\Script1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\source\broadcastmsg.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\broadcastmsg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\broadcastmsg.obj"	"$(INTDIR)\broadcastmsg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\procconnectreq.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\procconnectreq.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\procconnectreq.obj"	"$(INTDIR)\procconnectreq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\procsendfilemsgreq.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\procsendfilemsgreq.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\procsendfilemsgreq.obj"	"$(INTDIR)\procsendfilemsgreq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\procsendmsgnotify.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\procsendmsgnotify.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\procsendmsgnotify.obj"	"$(INTDIR)\procsendmsgnotify.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\procsendmsgreq.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\procsendmsgreq.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\procsendmsgreq.obj"	"$(INTDIR)\procsendmsgreq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\recvfilecontcmd.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\recvfilecontcmd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\recvfilecontcmd.obj"	"$(INTDIR)\recvfilecontcmd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\recvfileinforeq.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\recvfileinforeq.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\recvfileinforeq.obj"	"$(INTDIR)\recvfileinforeq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\requserlist.cpp

!IF  "$(CFG)" == "server - Win32 Release"


"$(INTDIR)\requserlist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "server - Win32 Debug"


"$(INTDIR)\requserlist.obj"	"$(INTDIR)\requserlist.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

