# Microsoft Developer Studio Project File - Name="mineuibase" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mineuibase - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mineuibase.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mineuibase.mak" CFG="mineuibase - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mineuibase - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mineuibase - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mineuibase - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\lib\Release"
# PROP Intermediate_Dir "..\obj_msvc\mineuibase\Release"
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

!ELSEIF  "$(CFG)" == "mineuibase - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\lib\Debug"
# PROP Intermediate_Dir "..\obj_msvc\mineuibase\Debug"
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

# Name "mineuibase - Win32 Release"
# Name "mineuibase - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\mineuibase\CUIMineFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\minetest\MinePropRegTest.cpp
# End Source File
# Begin Source File

SOURCE=..\mineuibase\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIAux.cpp
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIBitmapUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIDrawContext.cpp
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIMisc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\mineuibase\CUIMineFrame.h
# End Source File
# Begin Source File

SOURCE=..\mineuibase\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIAux.h
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIBitmapUtil.h
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIDrawContext.h
# End Source File
# Begin Source File

SOURCE=..\mineuibase\UIMisc.h
# End Source File
# End Group
# End Target
# End Project
