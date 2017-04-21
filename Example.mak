# Microsoft Developer Studio Generated NMAKE File, Based on Example.dsp
!IF "$(CFG)" == ""
CFG=Example - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Example - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Example - Win32 Release" && "$(CFG)" != "Example - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Example.mak" CFG="Example - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Example - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Example - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Example - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Example.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AcqSetupDlg.obj"
	-@erase "$(INTDIR)\adjustcontrol.obj"
	-@erase "$(INTDIR)\AdjustDlg.obj"
	-@erase "$(INTDIR)\analysiseditor.obj"
	-@erase "$(INTDIR)\AnalzerMenu.obj"
	-@erase "$(INTDIR)\Calibration.obj"
	-@erase "$(INTDIR)\DatasourceMenu.obj"
	-@erase "$(INTDIR)\DisplayFunctions.obj"
	-@erase "$(INTDIR)\DisplayMenu.obj"
	-@erase "$(INTDIR)\EditMenu.obj"
	-@erase "$(INTDIR)\Example.pch"
	-@erase "$(INTDIR)\Example.res"
	-@erase "$(INTDIR)\FileFunctions.obj"
	-@erase "$(INTDIR)\FileMenu.obj"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\MAINDlg.obj"
	-@erase "$(INTDIR)\MCAMenu.obj"
	-@erase "$(INTDIR)\mvc.obj"
	-@erase "$(INTDIR)\Preference.obj"
	-@erase "$(INTDIR)\PrefFunctions.obj"
	-@erase "$(INTDIR)\reportviewer.obj"
	-@erase "$(INTDIR)\SampleInfo.obj"
	-@erase "$(INTDIR)\SeqAnalyzer.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinGAA.obj"
	-@erase "$(OUTDIR)\Example.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp2 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Example.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Example.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Example.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Example.pdb" /machine:I386 /out:"$(OUTDIR)\Example.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\MAINDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WinGAA.obj" \
	"$(INTDIR)\FileFunctions.obj" \
	"$(INTDIR)\FileMenu.obj" \
	"$(INTDIR)\AcqSetupDlg.obj" \
	"$(INTDIR)\adjustcontrol.obj" \
	"$(INTDIR)\AdjustDlg.obj" \
	"$(INTDIR)\MCAMenu.obj" \
	"$(INTDIR)\DisplayFunctions.obj" \
	"$(INTDIR)\DisplayMenu.obj" \
	"$(INTDIR)\Preference.obj" \
	"$(INTDIR)\PrefFunctions.obj" \
	"$(INTDIR)\AnalzerMenu.obj" \
	"$(INTDIR)\SeqAnalyzer.obj" \
	"$(INTDIR)\DatasourceMenu.obj" \
	"$(INTDIR)\Calibration.obj" \
	"$(INTDIR)\EditMenu.obj" \
	"$(INTDIR)\SampleInfo.obj" \
	"$(INTDIR)\analysiseditor.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\mvc.obj" \
	"$(INTDIR)\reportviewer.obj" \
	"$(INTDIR)\Example.res"

"$(OUTDIR)\Example.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Example - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Example.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AcqSetupDlg.obj"
	-@erase "$(INTDIR)\adjustcontrol.obj"
	-@erase "$(INTDIR)\AdjustDlg.obj"
	-@erase "$(INTDIR)\analysiseditor.obj"
	-@erase "$(INTDIR)\AnalzerMenu.obj"
	-@erase "$(INTDIR)\Calibration.obj"
	-@erase "$(INTDIR)\DatasourceMenu.obj"
	-@erase "$(INTDIR)\DisplayFunctions.obj"
	-@erase "$(INTDIR)\DisplayMenu.obj"
	-@erase "$(INTDIR)\EditMenu.obj"
	-@erase "$(INTDIR)\Example.pch"
	-@erase "$(INTDIR)\Example.res"
	-@erase "$(INTDIR)\FileFunctions.obj"
	-@erase "$(INTDIR)\FileMenu.obj"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\MAINDlg.obj"
	-@erase "$(INTDIR)\MCAMenu.obj"
	-@erase "$(INTDIR)\mvc.obj"
	-@erase "$(INTDIR)\Preference.obj"
	-@erase "$(INTDIR)\PrefFunctions.obj"
	-@erase "$(INTDIR)\reportviewer.obj"
	-@erase "$(INTDIR)\SampleInfo.obj"
	-@erase "$(INTDIR)\SeqAnalyzer.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WinGAA.obj"
	-@erase "$(OUTDIR)\Example.exe"
	-@erase "$(OUTDIR)\Example.ilk"
	-@erase "$(OUTDIR)\Example.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp2 /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Example.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Example.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Example.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Example.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Example.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\MAINDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WinGAA.obj" \
	"$(INTDIR)\FileFunctions.obj" \
	"$(INTDIR)\FileMenu.obj" \
	"$(INTDIR)\AcqSetupDlg.obj" \
	"$(INTDIR)\adjustcontrol.obj" \
	"$(INTDIR)\AdjustDlg.obj" \
	"$(INTDIR)\MCAMenu.obj" \
	"$(INTDIR)\DisplayFunctions.obj" \
	"$(INTDIR)\DisplayMenu.obj" \
	"$(INTDIR)\Preference.obj" \
	"$(INTDIR)\PrefFunctions.obj" \
	"$(INTDIR)\AnalzerMenu.obj" \
	"$(INTDIR)\SeqAnalyzer.obj" \
	"$(INTDIR)\DatasourceMenu.obj" \
	"$(INTDIR)\Calibration.obj" \
	"$(INTDIR)\EditMenu.obj" \
	"$(INTDIR)\SampleInfo.obj" \
	"$(INTDIR)\analysiseditor.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\mvc.obj" \
	"$(INTDIR)\reportviewer.obj" \
	"$(INTDIR)\Example.res"

"$(OUTDIR)\Example.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Example.dep")
!INCLUDE "Example.dep"
!ELSE 
!MESSAGE Warning: cannot find "Example.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Example - Win32 Release" || "$(CFG)" == "Example - Win32 Debug"
SOURCE=.\AboutDlg.cpp

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\Example.rc

"$(INTDIR)\Example.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MAINDlg.cpp

"$(INTDIR)\MAINDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Example - Win32 Release"

CPP_SWITCHES=/nologo /Zp2 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Example.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Example.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Example - Win32 Debug"

CPP_SWITCHES=/nologo /Zp2 /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Example.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Example.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WinGAA.cpp

"$(INTDIR)\WinGAA.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\FileFunctions.cpp

"$(INTDIR)\FileFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\FileMenu.cpp

"$(INTDIR)\FileMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\AcqSetupDlg.cpp

"$(INTDIR)\AcqSetupDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\AdjustDlg.cpp

"$(INTDIR)\AdjustDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\MCAMenu.cpp

"$(INTDIR)\MCAMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\DisplayFunctions.cpp

"$(INTDIR)\DisplayFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\DisplayMenu.cpp

"$(INTDIR)\DisplayMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\Preference.cpp

"$(INTDIR)\Preference.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\PrefFunctions.cpp

"$(INTDIR)\PrefFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\AnalzerMenu.cpp

"$(INTDIR)\AnalzerMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\SeqAnalyzer.cpp

"$(INTDIR)\SeqAnalyzer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\DatasourceMenu.cpp

"$(INTDIR)\DatasourceMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\Calibration.cpp

"$(INTDIR)\Calibration.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\EditMenu.cpp

"$(INTDIR)\EditMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\SampleInfo.cpp

"$(INTDIR)\SampleInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\adjustcontrol.cpp

"$(INTDIR)\adjustcontrol.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\analysiseditor.cpp

"$(INTDIR)\analysiseditor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\font.cpp

"$(INTDIR)\font.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\mvc.cpp

"$(INTDIR)\mvc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"


SOURCE=.\reportviewer.cpp

"$(INTDIR)\reportviewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Example.pch"



!ENDIF 

