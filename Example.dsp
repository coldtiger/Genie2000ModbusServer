# Microsoft Developer Studio Project File - Name="Example" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Example - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Example.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Example - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp2 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Example - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp2 /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Example - Win32 Release"
# Name "Example - Win32 Debug"
# Begin Group "Project Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ComData.cpp
# End Source File
# Begin Source File

SOURCE=.\Example.rc
# End Source File
# Begin Source File

SOURCE=.\MAINDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinGAA.cpp
# End Source File
# End Group
# Begin Group "All Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\AcqSetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\adjustcontrol.h
# End Source File
# Begin Source File

SOURCE=.\AdjustDlg.h
# End Source File
# Begin Source File

SOURCE=.\analysiseditor.h
# End Source File
# Begin Source File

SOURCE=.\Calibration.h
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\ComData.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\MAINDlg.h
# End Source File
# Begin Source File

SOURCE=.\mvc.h
# End Source File
# Begin Source File

SOURCE=.\Preference.h
# End Source File
# Begin Source File

SOURCE=.\reportviewer.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SampleInfo.h
# End Source File
# Begin Source File

SOURCE=.\SeqAnalyzer.h
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinGAA.h
# End Source File
# End Group
# Begin Group "Project Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Example.ico
# End Source File
# Begin Source File

SOURCE=.\res\Example.rc2
# End Source File
# End Group
# Begin Group "Menu Functions"

# PROP Default_Filter ""
# Begin Group "File Menu Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FileFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMenu.cpp
# End Source File
# End Group
# Begin Group "MCA Menu Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AcqSetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdjustDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MCAMenu.cpp
# End Source File
# End Group
# Begin Group "Display Menu Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DisplayFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\DisplayMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\Preference.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefFunctions.cpp
# End Source File
# End Group
# Begin Group "Analysis & Reporting Menu Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnalzerMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\SeqAnalyzer.cpp
# End Source File
# End Group
# Begin Group "Datasource Menu Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DatasourceMenu.cpp
# End Source File
# End Group
# Begin Group "Edit Menu Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Calibration.cpp
# End Source File
# Begin Source File

SOURCE=.\EditMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleInfo.cpp
# End Source File
# End Group
# End Group
# Begin Group "Interface Implementation Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\adjustcontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\analysiseditor.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\mvc.cpp
# End Source File
# Begin Source File

SOURCE=.\reportviewer.cpp
# End Source File
# End Group
# End Target
# End Project
# Section Example : {5EC32872-BCAC-11D1-AB1E-0020AF302738}
# 	2:21:DefaultSinkHeaderFile:reportviewer.h
# 	2:16:DefaultSinkClass:CReportViewer
# End Section
# Section Example : {A22D386E-6CDA-11D2-B236-00104B9E586E}
# 	2:21:DefaultSinkHeaderFile:adjustcontrol.h
# 	2:16:DefaultSinkClass:CAdjustControl
# End Section
# Section Example : {5EC32871-BCAC-11D1-AB1E-0020AF302738}
# 	2:5:Class:CReportViewer
# 	2:10:HeaderFile:reportviewer.h
# 	2:8:ImplFile:reportviewer.cpp
# End Section
# Section Example : {A22D386D-6CDA-11D2-B236-00104B9E586E}
# 	2:5:Class:CAdjustControl
# 	2:10:HeaderFile:adjustcontrol.h
# 	2:8:ImplFile:adjustcontrol.cpp
# End Section
# Section Example : {816CAE23-D460-11D1-84A8-00A0248C8E7B}
# 	2:21:DefaultSinkHeaderFile:analysiseditor.h
# 	2:16:DefaultSinkClass:CAnalysisEditor
# End Section
# Section Example : {D8B91C41-6FB5-11D5-B7D3-0050DAB52E6E}
# 	2:21:DefaultSinkHeaderFile:mvcstatusinfo.h
# 	2:16:DefaultSinkClass:CMVCStatusInfo
# End Section
# Section Example : {78559301-09D8-11D2-85D3-204C4F4F5020}
# 	2:21:DefaultSinkHeaderFile:mvc.h
# 	2:16:DefaultSinkClass:CMvc
# End Section
# Section Example : {D8B91C40-6FB5-11D5-B7D3-0050DAB52E6E}
# 	2:5:Class:CMVCStatusInfo
# 	2:10:HeaderFile:mvcstatusinfo.h
# 	2:8:ImplFile:mvcstatusinfo.cpp
# End Section
# Section Example : {816CAE22-D460-11D1-84A8-00A0248C8E7B}
# 	2:5:Class:CAnalysisEditor
# 	2:10:HeaderFile:analysiseditor.h
# 	2:8:ImplFile:analysiseditor.cpp
# End Section
# Section Example : {78559300-09D8-11D2-85D3-204C4F4F5020}
# 	2:5:Class:CMvc
# 	2:10:HeaderFile:mvc.h
# 	2:8:ImplFile:mvc.cpp
# End Section
# Section Example : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
