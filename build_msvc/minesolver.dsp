# Microsoft Developer Studio Project File - Name="minesolver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=minesolver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "minesolver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "minesolver.mak" CFG="minesolver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "minesolver - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "minesolver - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "minesolver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\lib\Release"
# PROP Intermediate_Dir "..\obj_msvc\minesolver\Release"
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

!ELSEIF  "$(CFG)" == "minesolver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\lib\Debug"
# PROP Intermediate_Dir "..\obj_msvc\minesolver\Debug"
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

# Name "minesolver - Win32 Release"
# Name "minesolver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\minesolver\CFieldValue.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CInputField.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CInstanceCount.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CMineArray.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CompProbabilities.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CompWinProp.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CResultField.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\CTerminator.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\MineMath.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\MineSolver.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\SolutionEnumerator.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\SolutionIter.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\SolutionUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\minesolver\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\minesolver\CFieldValue.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CInputField.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CInstanceCount.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CMineArray.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CompProbabilities.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CompWinProp.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CResultField.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\CTerminator.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\MineMath.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\MineSolver.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\SolutionEnumerator.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\SolutionIter.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\SolutionUtil.h
# End Source File
# Begin Source File

SOURCE=..\minesolver\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
