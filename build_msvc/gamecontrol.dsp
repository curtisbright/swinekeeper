# Microsoft Developer Studio Project File - Name="gamecontrol" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gamecontrol - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gamecontrol.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gamecontrol.mak" CFG="gamecontrol - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gamecontrol - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gamecontrol - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gamecontrol - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\lib\Release"
# PROP Intermediate_Dir "..\obj_msvc\gamecontrol\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I ".." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "gamecontrol - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\lib\Debug"
# PROP Intermediate_Dir "..\obj_msvc\gamecontrol\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "gamecontrol - Win32 Release"
# Name "gamecontrol - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\gamecontrol\CActionRecorder.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CDocChangeObserver.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CDocHistory.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameDocumentBase.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameManager.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameView.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGlobalResourceSet.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CHistoryDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CJoystickInputDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CKeyboardInputDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CKeyboardInputDevice2.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CObserveableGameDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CSolutionFieldView.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CTerminatorEsc.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CUILayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\FieldViews.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\GameMisc.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\InputDevices.cpp
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\gamecontrol\CActionRecorder.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CDocChangeObserver.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CDocHistory.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameDocument.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameDocumentBase.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameManager.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameTimer.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGameView.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CGlobalResourceSet.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CHistoryDocument.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CJoystickInputDevice.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CKeyboardInputDevice.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CKeyboardInputDevice2.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CObserveableGameDocument.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CSolutionFieldView.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CTerminatorEsc.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\CUILayoutManager.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\FieldViews.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\GameMisc.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\InputDevices.h
# End Source File
# Begin Source File

SOURCE=..\gamecontrol\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
