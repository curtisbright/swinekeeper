TEMPLATE	= app
CONFIG		= qt warn_on release
HEADERS		= ../mineui_qt/StdAfx.h \
		  ../mineui_qt/gamedimdlgimpl.h \
		  ../mineui_qt/halloffamedlgimpl.h \
		  ../mineui_qt/minefieldtooltip.h \
		  ../mineui_qt/mineui_qtwindow.h \
		  ../mineui_qt/mineuiview.h \
		  ../mineui_qt/scorenamedlgimpl.h \
		  ../mineui_qt/uidrawcontextqt.h \
		  ../gamecontrol/CActionRecorder.h \
		  ../gamecontrol/CDocChangeObserver.h \
		  ../gamecontrol/CDocHistory.h \
		  ../gamecontrol/CGameDocument.h \
		  ../gamecontrol/CGameDocumentBase.h \
		  ../gamecontrol/CGameManager.h \
		  ../gamecontrol/CGameTimer.h \
		  ../gamecontrol/CGameView.h \
		  ../gamecontrol/CGlobalResourceSet.h \
		  ../gamecontrol/CHistoryDocument.h \
		  ../gamecontrol/CJoystickInputDevice.h \
		  ../gamecontrol/CKeyboardInputDevice.h \
		  ../gamecontrol/CKeyboardInputDevice2.h \
		  ../gamecontrol/CObserveableGameDocument.h \
		  ../gamecontrol/CSolutionFieldView.h \
		  ../gamecontrol/CTerminatorEsc.h \
		  ../gamecontrol/CUILayoutManager.h \
		  ../gamecontrol/FieldViews.h \
		  ../gamecontrol/GameMisc.h \
		  ../gamecontrol/InputDevices.h \
		  ../gamecontrol/StdAfx.h \
		  ../minebase/ConfigAll.h \
		  ../minebase/EnableMSVCWarnings.h \
		  ../minebase/MineBase.h \
		  ../minebase/MineBaseSerialize.h \
		  ../minebase/MineStd.h \
		  ../minebase/PlayArray.h \
		  ../minebase/StdAfx.h \
		  ../minesolver/CFieldValue.h \
		  ../minesolver/CInputField.h \
		  ../minesolver/CInstanceCount.h \
		  ../minesolver/CMineArray.h \
		  ../minesolver/CResultField.h \
		  ../minesolver/CTerminator.h \
		  ../minesolver/CompProbabilities.h \
		  ../minesolver/CompWinProp.h \
		  ../minesolver/MineMath.h \
		  ../minesolver/MineSolver.h \
		  ../minesolver/SolutionEnumerator.h \
		  ../minesolver/SolutionIter.h \
		  ../minesolver/SolutionSet.h \
		  ../minesolver/SolutionUtil.h \
		  ../minesolver/StdAfx.h \
		  ../mineui_common/CLevelMgr.h \
		  ../mineui_common/CPersistentDictionary.h \
		  ../mineui_common/CPersistentState.h \
		  ../mineui_common/GameConstants.h \
		  ../mineui_common/GameOptions.h \
		  ../mineui_common/RCFileDictionary.h \
		  ../mineui_common/StdAfx.h \
		  ../mineui_common/TransientDictionary.h \
		  ../mineuibase/CUIMineFrame.h \
		  ../mineuibase/StdAfx.h \
		  ../mineuibase/UIAux.h \
		  ../mineuibase/UIBitmapUtil.h \
		  ../mineuibase/UIDrawContext.h \
		  ../mineuibase/UIMisc.h \
		  ../storage/CText.h \
		  ../storage/Document.h \
		  ../storage/Serializer.h \
		  ../storage/StdAfx.h \
		  ../storage/Tree.h
SOURCES		= \
		  ../mineui_qt/gamedimdlgimpl.cpp \
		  ../mineui_qt/halloffamedlgimpl.cpp \
		  ../mineui_qt/main.cpp \
		  ../mineui_qt/minefieldtooltip.cpp \
		  ../mineui_qt/mineui_qtwindow.cpp \
		  ../mineui_qt/mineuiview.cpp \
		  ../mineui_qt/scorenamedlgimpl.cpp \
		  ../mineui_qt/uidrawcontextqt.cpp \
		  ../gamecontrol/CActionRecorder.cpp \
		  ../gamecontrol/CDocChangeObserver.cpp \
		  ../gamecontrol/CDocHistory.cpp \
		  ../gamecontrol/CGameDocument.cpp \
		  ../gamecontrol/CGameDocumentBase.cpp \
		  ../gamecontrol/CGameManager.cpp \
		  ../gamecontrol/CGameTimer.cpp \
		  ../gamecontrol/CGameView.cpp \
		  ../gamecontrol/CGlobalResourceSet.cpp \
		  ../gamecontrol/CHistoryDocument.cpp \
		  ../gamecontrol/CJoystickInputDevice.cpp \
		  ../gamecontrol/CKeyboardInputDevice.cpp \
		  ../gamecontrol/CKeyboardInputDevice2.cpp \
		  ../gamecontrol/CObserveableGameDocument.cpp \
		  ../gamecontrol/CSolutionFieldView.cpp \
		  ../gamecontrol/CTerminatorEsc.cpp \
		  ../gamecontrol/CUILayoutManager.cpp \
		  ../gamecontrol/FieldViews.cpp \
		  ../gamecontrol/GameMisc.cpp \
		  ../gamecontrol/InputDevices.cpp \
		  ../minebase/MineBase.cpp \
		  ../minebase/MineBaseSerialize.cpp \
		  ../minebase/PlayArray.cpp \
		  ../minesolver/CFieldValue.cpp \
		  ../minesolver/CInputField.cpp \
		  ../minesolver/CInstanceCount.cpp \
		  ../minesolver/CMineArray.cpp \
		  ../minesolver/CResultField.cpp \
		  ../minesolver/CTerminator.cpp \
		  ../minesolver/CompProbabilities.cpp \
		  ../minesolver/CompWinProp.cpp \
		  ../minesolver/MineMath.cpp \
		  ../minesolver/MineSolver.cpp \
		  ../minesolver/SolutionEnumerator.cpp \
		  ../minesolver/SolutionIter.cpp \
		  ../minesolver/SolutionUtil.cpp \
		  ../mineui_common/CLevelMgr.cpp \
		  ../mineui_common/CPersistentDictionary.cpp \
		  ../mineui_common/CPersistentState.cpp \
		  ../mineui_common/GameConstants.cpp \
		  ../mineui_common/GameOptions.cpp \
		  ../mineui_common/RCFileDictionary.cpp \
		  ../mineui_common/TransientDictionary.cpp \
		  ../mineuibase/CUIMineFrame.cpp \
		  ../mineuibase/UIAux.cpp \
		  ../mineuibase/UIBitmapUtil.cpp \
		  ../mineuibase/UIDrawContext.cpp \
		  ../mineuibase/UIMisc.cpp \
		  ../storage/CText.cpp \
		  ../storage/Document.cpp \
		  ../storage/Serializer.cpp \
		  ../storage/Tree.cpp
INTERFACES	= ../mineui_qt/gamedimdlg.ui \
		  ../mineui_qt/halloffamedlg.ui \
		  ../mineui_qt/scorenamedlg.ui
TARGET		= minesweeper
INCLUDEPATH = ..
OBJECTS_DIR = ../obj_tmake 
win32:DEFINES = QT_DLL QT_THREAD_SUPPORT
win32:TMAKE_CXXFLAGS = -GX
