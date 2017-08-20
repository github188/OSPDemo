# Microsoft Developer Studio Generated NMAKE File, Based on client.dsp
!IF "$(CFG)" == ""
CFG=prj_win32 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to prj_win32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "prj_win32 - Win32 Release" && "$(CFG)" != "prj_win32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "prj_win32 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\client.exe"


CLEAN :
	-@erase "$(INTDIR)\callback.obj"
	-@erase "$(INTDIR)\clientfileinstance.obj"
	-@erase "$(INTDIR)\clientinstance.obj"
	-@erase "$(INTDIR)\connectservercmd.obj"
	-@erase "$(INTDIR)\interface.obj"
	-@erase "$(INTDIR)\interruptconnectcmd.obj"
	-@erase "$(INTDIR)\logprintf.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\osphelpc.obj"
	-@erase "$(INTDIR)\requserlistcmd.obj"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\sendfilecmd.obj"
	-@erase "$(INTDIR)\sendmsgcmd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\client.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Script1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=OspDll.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\client.pdb" /machine:I386 /out:"$(OUTDIR)\client.exe" /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\clientfileinstance.obj" \
	"$(INTDIR)\clientinstance.obj" \
	"$(INTDIR)\interface.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\connectservercmd.obj" \
	"$(INTDIR)\interruptconnectcmd.obj" \
	"$(INTDIR)\requserlistcmd.obj" \
	"$(INTDIR)\sendfilecmd.obj" \
	"$(INTDIR)\sendmsgcmd.obj" \
	"$(INTDIR)\Script1.res" \
	".\OspDll.lib" \
	"$(INTDIR)\callback.obj" \
	"$(INTDIR)\logprintf.obj" \
	"$(INTDIR)\osphelpc.obj"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\client.exe" "$(OUTDIR)\client.bsc"


CLEAN :
	-@erase "$(INTDIR)\callback.obj"
	-@erase "$(INTDIR)\callback.sbr"
	-@erase "$(INTDIR)\clientfileinstance.obj"
	-@erase "$(INTDIR)\clientfileinstance.sbr"
	-@erase "$(INTDIR)\clientinstance.obj"
	-@erase "$(INTDIR)\clientinstance.sbr"
	-@erase "$(INTDIR)\connectservercmd.obj"
	-@erase "$(INTDIR)\connectservercmd.sbr"
	-@erase "$(INTDIR)\interface.obj"
	-@erase "$(INTDIR)\interface.sbr"
	-@erase "$(INTDIR)\interruptconnectcmd.obj"
	-@erase "$(INTDIR)\interruptconnectcmd.sbr"
	-@erase "$(INTDIR)\logprintf.obj"
	-@erase "$(INTDIR)\logprintf.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\osphelpc.obj"
	-@erase "$(INTDIR)\osphelpc.sbr"
	-@erase "$(INTDIR)\requserlistcmd.obj"
	-@erase "$(INTDIR)\requserlistcmd.sbr"
	-@erase "$(INTDIR)\Script1.res"
	-@erase "$(INTDIR)\sendfilecmd.obj"
	-@erase "$(INTDIR)\sendfilecmd.sbr"
	-@erase "$(INTDIR)\sendmsgcmd.obj"
	-@erase "$(INTDIR)\sendmsgcmd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\client.bsc"
	-@erase "$(OUTDIR)\client.exe"
	-@erase "$(OUTDIR)\client.ilk"
	-@erase "$(OUTDIR)\client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\client.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Script1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\clientfileinstance.sbr" \
	"$(INTDIR)\clientinstance.sbr" \
	"$(INTDIR)\interface.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\connectservercmd.sbr" \
	"$(INTDIR)\interruptconnectcmd.sbr" \
	"$(INTDIR)\requserlistcmd.sbr" \
	"$(INTDIR)\sendfilecmd.sbr" \
	"$(INTDIR)\sendmsgcmd.sbr" \
	"$(INTDIR)\callback.sbr" \
	"$(INTDIR)\logprintf.sbr" \
	"$(INTDIR)\osphelpc.sbr"

"$(OUTDIR)\client.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=OspDll.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\client.pdb" /debug /machine:I386 /out:"$(OUTDIR)\client.exe" /pdbtype:sept /libpath:"./../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\clientfileinstance.obj" \
	"$(INTDIR)\clientinstance.obj" \
	"$(INTDIR)\interface.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\connectservercmd.obj" \
	"$(INTDIR)\interruptconnectcmd.obj" \
	"$(INTDIR)\requserlistcmd.obj" \
	"$(INTDIR)\sendfilecmd.obj" \
	"$(INTDIR)\sendmsgcmd.obj" \
	"$(INTDIR)\Script1.res" \
	".\OspDll.lib" \
	"$(INTDIR)\callback.obj" \
	"$(INTDIR)\logprintf.obj" \
	"$(INTDIR)\osphelpc.obj"

"$(OUTDIR)\client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("client.dep")
!INCLUDE "client.dep"
!ELSE 
!MESSAGE Warning: cannot find "client.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "prj_win32 - Win32 Release" || "$(CFG)" == "prj_win32 - Win32 Debug"
SOURCE=..\source\callback.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\callback.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\callback.obj"	"$(INTDIR)\callback.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\clientfileinstance.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\clientfileinstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\clientfileinstance.obj"	"$(INTDIR)\clientfileinstance.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\clientinstance.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\clientinstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\clientinstance.obj"	"$(INTDIR)\clientinstance.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\interface.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\interface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\interface.obj"	"$(INTDIR)\interface.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\logprintf.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\logprintf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\logprintf.obj"	"$(INTDIR)\logprintf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\main.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\osphelpc.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\osphelpc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\osphelpc.obj"	"$(INTDIR)\osphelpc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Script1.rc

"$(INTDIR)\Script1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\source\connectservercmd.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\connectservercmd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\connectservercmd.obj"	"$(INTDIR)\connectservercmd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\interruptconnectcmd.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\interruptconnectcmd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\interruptconnectcmd.obj"	"$(INTDIR)\interruptconnectcmd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\requserlistcmd.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\requserlistcmd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\requserlistcmd.obj"	"$(INTDIR)\requserlistcmd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\sendfilecmd.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\sendfilecmd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\sendfilecmd.obj"	"$(INTDIR)\sendfilecmd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\sendmsgcmd.cpp

!IF  "$(CFG)" == "prj_win32 - Win32 Release"


"$(INTDIR)\sendmsgcmd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "prj_win32 - Win32 Debug"


"$(INTDIR)\sendmsgcmd.obj"	"$(INTDIR)\sendmsgcmd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

