# Microsoft Developer Studio Project File - Name="MineUI_PTC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MineUI_PTC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_PTC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_PTC.mak" CFG="MineUI_PTC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MineUI_PTC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MineUI_PTC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MineUI_PTC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\mineui_ptc\Release"
# PROP Intermediate_Dir "..\obj_msvc\mineui_ptc\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I ".." /I "C:\home\src\OpenPTC\source" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ptc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /machine:I386 /out:"..\bin_msvc\Release/MineUI_PTC.exe" /libpath:"C:\home\src\OpenPTC\library\visual"
# Begin Special Build Tool
TargetDir=\MySrc\test\minesweeper20000826\bin_msvc\Release
SOURCE="$(InputPath)"
PostBuild_Desc=Copy Resources
PostBuild_Cmds=copy ..\resources\Smilies.bmp $(TargetDir)	copy ..\resources\Digits.bmp $(TargetDir)	copy ..\resources\FieldIcons.bmp $(TargetDir)	copy ..\resources\FieldInfos.bmp $(TargetDir)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MineUI_PTC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\mineui_ptc\Debug"
# PROP Intermediate_Dir "..\obj_msvc\mineui_ptc\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".." /I "C:\home\src\OpenPTC\source" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ptcdebug.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"mainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"..\bin_msvc\Debug/MineUI_PTC.exe" /libpath:"C:\home\src\OpenPTC\library\visual"
# Begin Special Build Tool
TargetDir=\MySrc\test\minesweeper20000826\bin_msvc\Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\resources\Smilies.bmp $(TargetDir)	copy ..\resources\Digits.bmp $(TargetDir)	copy ..\resources\FieldIcons.bmp $(TargetDir)	copy ..\resources\FieldInfos.bmp $(TargetDir)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MineUI_PTC - Win32 Release"
# Name "MineUI_PTC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\mineui_ptc\Application.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_ptc\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_ptc\UIDrawContextPTC.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\mineui_ptc\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\mineui_ptc\UIDrawContextPTC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
