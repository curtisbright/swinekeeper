# Microsoft Developer Studio Project File - Name="MineUI_Qt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MineUI_Qt - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_Qt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MineUI_Qt.mak" CFG="MineUI_Qt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MineUI_Qt - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MineUI_Qt - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\obj_msvc\mineui_qt\Release"
# PROP Intermediate_Dir "..\obj_msvc\mineui_qt\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin_msvc\Release/minesweeper_qt.exe"

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\obj_msvc\mineui_qt\Debug"
# PROP Intermediate_Dir "..\obj_msvc\mineui_qt\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin_msvc\Debug/minesweeper_qt.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MineUI_Qt - Win32 Release"
# Name "MineUI_Qt - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\MineUI_Qt\gamedimdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\gamedimdlgimpl.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\halloffamedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\halloffamedlgimpl.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\main.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\minefieldtooltip.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\mineui_qtwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\mineuiview.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_gamedimdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_gamedimdlgimpl.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_halloffamedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_halloffamedlgimpl.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_mineui_qtwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_mineuiview.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_scorenamedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\moc_scorenamedlgimpl.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\scorenamedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\scorenamedlgimpl.cpp
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\uidrawcontextqt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\MineUI_Qt\gamedimdlg.h
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\gamedimdlgimpl.h

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\gamedimdlgimpl.h
InputName=gamedimdlgimpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\gamedimdlgimpl.h
InputName=gamedimdlgimpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\halloffamedlg.h
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\halloffamedlgimpl.h

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\halloffamedlgimpl.h
InputName=halloffamedlgimpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\halloffamedlgimpl.h
InputName=halloffamedlgimpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\minefieldtooltip.h
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\mineui_qtwindow.h

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\mineui_qtwindow.h
InputName=mineui_qtwindow

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\mineui_qtwindow.h
InputName=mineui_qtwindow

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\mineuiview.h

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\mineuiview.h
InputName=mineuiview

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\scorenamedlg.h
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\scorenamedlgimpl.h

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\scorenamedlgimpl.h
InputName=scorenamedlgimpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\scorenamedlgimpl.h
InputName=scorenamedlgimpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\uidrawcontextqt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\MineUI_Qt\gamedimdlg.ui

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\gamedimdlg.ui
InputName=gamedimdlg

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\gamedimdlg.ui
InputName=gamedimdlg

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\halloffamedlg.ui

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\halloffamedlg.ui
InputName=halloffamedlg

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\halloffamedlg.ui
InputName=halloffamedlg

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\mineui_qtwindow.moc

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).cpp ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\mineui_qtwindow.moc
InputName=mineui_qtwindow

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).cpp ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\mineui_qtwindow.moc
InputName=mineui_qtwindow

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\mineuiview.moc

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).cpp ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\mineuiview.moc
InputName=mineuiview

"$(InputDir)\$(InputName).moc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).cpp -o $(InputDir)\$(InputName).moc

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\readme.txt
# End Source File
# Begin Source File

SOURCE=..\MineUI_Qt\scorenamedlg.ui

!IF  "$(CFG)" == "MineUI_Qt - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\scorenamedlg.ui
InputName=scorenamedlg

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MineUI_Qt - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=\kopp\src\minesweeper\MineUI_Qt
InputPath=..\MineUI_Qt\scorenamedlg.ui
InputName=scorenamedlg

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
