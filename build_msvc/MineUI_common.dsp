# Microsoft Developer Studio Project File - Name="MineUI_common" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MineUI_common - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_common.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_common.mak" CFG="MineUI_common - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MineUI_common - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MineUI_common - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MineUI_common - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\mineui_common\Release"
# PROP Intermediate_Dir "..\obj_msvc\mineui_common\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "MineUI_common - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MineUI_common___Win32_Debug"
# PROP BASE Intermediate_Dir "MineUI_common___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\mineui_common\Debug"
# PROP Intermediate_Dir "..\obj_msvc\mineui_common\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "MineUI_common - Win32 Release"
# Name "MineUI_common - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\mineui_common\CLevelMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_common\CPersistentDictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_common\CPersistentState.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_common\GameConstants.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_common\GameOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_common\RCFileDictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\mineui_common\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=..\mineui_common\TransientDictionary.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\mineui_common\CLevelMgr.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\CPersistentDictionary.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\CPersistentState.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\GameConstants.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\GameOptions.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\RCFileDictionary.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\mineui_common\TransientDictionary.h
# End Source File
# End Group
# End Target
# End Project
