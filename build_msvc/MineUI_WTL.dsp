# Microsoft Developer Studio Project File - Name="MineUI_WTL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MineUI_WTL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_WTL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_WTL.mak" CFG="MineUI_WTL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MineUI_WTL - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MineUI_WTL - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MineUI_WTL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\mineui_wtl\Release"
# PROP Intermediate_Dir "..\obj_msvc\mineui_wtl\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "..\AppWiz\Include" /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\AppWiz\Include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Dinput.lib Dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"..\bin_msvc\Release/MineUI_WTL.exe" /OPT:REF
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MineUI_WTL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\mineui_wtl\Debug"
# PROP Intermediate_Dir "..\obj_msvc\mineui_wtl\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\AppWiz\Include" /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\AppWiz\Include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Dinput.lib Dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcd.lib" /out:"..\bin_msvc\Debug/MineUI_WTL.exe"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "MineUI_WTL - Win32 Release"
# Name "MineUI_WTL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\mineui_wtl\CMainFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CMineUIView.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CPersistentDictWin.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\MineUI_WTL.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\MineUI_WTL.rc
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\UIDrawContextWTL.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\mineui_wtl\CAboutDlg.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CArrayDimDlg.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CHallOfFameDlg.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CMainFrame.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CMineUIView.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CPersistentDictWin.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\CScoreNameDlg.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\resource.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\UIDrawContextWTL.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\mineui_wtl\Digits.bmp
# End Source File
# Begin Source File

SOURCE=..\resources\Digits.bmp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\FieldIcons.bmp
# End Source File
# Begin Source File

SOURCE=..\resources\FieldIcons.bmp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\FieldInfos.bmp
# End Source File
# Begin Source File

SOURCE=..\resources\FieldInfos.bmp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\idr_main.ico
# End Source File
# Begin Source File

SOURCE=..\resources\MineIcon.ico
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\MineUI_WTL.ico
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\Smilies.bmp
# End Source File
# Begin Source File

SOURCE=..\resources\Smilies.bmp
# End Source File
# Begin Source File

SOURCE=..\mineui_wtl\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
