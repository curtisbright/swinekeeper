# Automagically generated makefile 
include CompilerSettings.inc

default: debug

all: debug release copydata

clean: clean_debug clean_release

library: library_debug library_release

mineui_ptc: mineui_ptc_debug mineui_ptc_release

mineui_glut: mineui_glut_debug mineui_glut_release

minetest: minetest_debug minetest_release

mkdirs: mkdirs_debug mkdirs_release

copydata: copydata_debug copydata_release

debug:mkdirs_debug ../obj_cygwin/lib/debug/minesweeper.a ../bin_cygwin/debug/minetest ../bin_cygwin/debug/mineui_ptc

library_debug: ../obj_cygwin/lib/debug/minesweeper.a

../obj_cygwin/lib/debug/minesweeper.a:../obj_cygwin/gamecontrol/debug/CActionRecorder.o ../obj_cygwin/gamecontrol/debug/CDocChangeObserver.o ../obj_cygwin/gamecontrol/debug/CDocHistory.o ../obj_cygwin/gamecontrol/debug/CGameDocument.o ../obj_cygwin/gamecontrol/debug/CGameDocumentBase.o ../obj_cygwin/gamecontrol/debug/CGameManager.o ../obj_cygwin/gamecontrol/debug/CGameTimer.o ../obj_cygwin/gamecontrol/debug/CGameView.o ../obj_cygwin/gamecontrol/debug/CGlobalResourceSet.o ../obj_cygwin/gamecontrol/debug/CHistoryDocument.o ../obj_cygwin/gamecontrol/debug/CJoystickInputDevice.o ../obj_cygwin/gamecontrol/debug/CKeyboardInputDevice.o ../obj_cygwin/gamecontrol/debug/CKeyboardInputDevice2.o ../obj_cygwin/gamecontrol/debug/CObserveableGameDocument.o ../obj_cygwin/gamecontrol/debug/CSolutionFieldView.o ../obj_cygwin/gamecontrol/debug/CTerminatorEsc.o ../obj_cygwin/gamecontrol/debug/CUILayoutManager.o ../obj_cygwin/gamecontrol/debug/FieldViews.o ../obj_cygwin/gamecontrol/debug/GameMisc.o ../obj_cygwin/gamecontrol/debug/InputDevices.o ../obj_cygwin/gamecontrol/debug/StdAfx.o ../obj_cygwin/minebase/debug/MineBase.o ../obj_cygwin/minebase/debug/MineBaseSerialize.o ../obj_cygwin/minebase/debug/PlayArray.o ../obj_cygwin/minebase/debug/StdAfx.o ../obj_cygwin/minesolver/debug/CFieldValue.o ../obj_cygwin/minesolver/debug/CInputField.o ../obj_cygwin/minesolver/debug/CInstanceCount.o ../obj_cygwin/minesolver/debug/CMineArray.o ../obj_cygwin/minesolver/debug/CompProbabilities.o ../obj_cygwin/minesolver/debug/CompWinProp.o ../obj_cygwin/minesolver/debug/CResultField.o ../obj_cygwin/minesolver/debug/CTerminator.o ../obj_cygwin/minesolver/debug/MineMath.o ../obj_cygwin/minesolver/debug/MineSolver.o ../obj_cygwin/minesolver/debug/SolutionEnumerator.o ../obj_cygwin/minesolver/debug/SolutionIter.o ../obj_cygwin/minesolver/debug/SolutionUtil.o ../obj_cygwin/minesolver/debug/StdAfx.o ../obj_cygwin/mineuibase/debug/CUIMineFrame.o ../obj_cygwin/mineuibase/debug/StdAfx.o ../obj_cygwin/mineuibase/debug/UIAux.o ../obj_cygwin/mineuibase/debug/UIBitmapUtil.o ../obj_cygwin/mineuibase/debug/UIDrawContext.o ../obj_cygwin/mineuibase/debug/UIMisc.o ../obj_cygwin/mineui_common/debug/CLevelMgr.o ../obj_cygwin/mineui_common/debug/CPersistentDictionary.o ../obj_cygwin/mineui_common/debug/CPersistentState.o ../obj_cygwin/mineui_common/debug/GameConstants.o ../obj_cygwin/mineui_common/debug/GameOptions.o ../obj_cygwin/mineui_common/debug/RCFileDictionary.o ../obj_cygwin/mineui_common/debug/StdAfx.o ../obj_cygwin/mineui_common/debug/TransientDictionary.o ../obj_cygwin/storage/debug/CText.o ../obj_cygwin/storage/debug/Document.o ../obj_cygwin/storage/debug/Serializer.o ../obj_cygwin/storage/debug/StdAfx.o ../obj_cygwin/storage/debug/Tree.o
	echo "Creating library minesweeper.a"
	ar -r $@ $^

minetest_debug: ../bin_cygwin/debug/minetest

../bin_cygwin/debug/minetest:../obj_cygwin/minetest/debug/MineBaseTest.o ../obj_cygwin/minetest/debug/MinePropRegTest.o ../obj_cygwin/minetest/debug/minetest.o ../obj_cygwin/minetest/debug/RegressionTest.o ../obj_cygwin/minetest/debug/RegressionTestTest.o ../obj_cygwin/minetest/debug/SingleTest.o ../obj_cygwin/minetest/debug/SolverTest.o ../obj_cygwin/minetest/debug/StdAfx.o ../obj_cygwin/minetest/debug/TestFramework.o ../obj_cygwin/lib/debug/minesweeper.a
	echo "Creating executable minetest"
	$(CC) $(LINKFLAGS_DEBUG)  -o ../bin_cygwin/debug/minetest$(EXE_POSTFIX) $^ 

mineui_ptc_debug: ../bin_cygwin/debug/mineui_ptc

../bin_cygwin/debug/mineui_ptc:../obj_cygwin/mineui_ptc/debug/Application.o ../obj_cygwin/mineui_ptc/debug/StdAfx.o ../obj_cygwin/mineui_ptc/debug/UIDrawContextPTC.o ../obj_cygwin/lib/debug/minesweeper.a
	echo "Creating executable mineui_ptc"
	$(CC) $(LINKFLAGS_DEBUG) $(LINK_PTC_DEBUG) -o ../bin_cygwin/debug/mineui_ptc$(EXE_POSTFIX) $^ $(LIBRARIES_PTC_DEBUG)

mkdirs_debug:
	-mkdir -p ../obj_cygwin/gamecontrol/debug/
	-mkdir -p ../obj_cygwin/minebase/debug/
	-mkdir -p ../obj_cygwin/minesolver/debug/
	-mkdir -p ../obj_cygwin/minetest/debug/
	-mkdir -p ../obj_cygwin/mineuibase/debug/
	-mkdir -p ../obj_cygwin/mineui_common/debug/
	-mkdir -p ../obj_cygwin/mineui_ptc/debug/
	-mkdir -p ../obj_cygwin/storage/debug/
	-mkdir -p ../obj_cygwin/lib/debug/
	-mkdir -p ../bin_cygwin/debug/

../obj_cygwin/gamecontrol/debug/CActionRecorder.o:../gamecontrol/CActionRecorder.cpp  ../gamecontrol/CActionRecorder.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocument.h 
	echo "Compiling gamecontrol/CActionRecorder.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CDocChangeObserver.o:../gamecontrol/CDocChangeObserver.cpp  ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h 
	echo "Compiling gamecontrol/CDocChangeObserver.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CDocHistory.o:../gamecontrol/CDocHistory.cpp  ../gamecontrol/CDocHistory.h ../gamecontrol/CGameDocument.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h ../gamecontrol/CObserveableGameDocument.h 
	echo "Compiling gamecontrol/CDocHistory.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CGameDocument.o:../gamecontrol/CGameDocument.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameDocument.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling gamecontrol/CGameDocument.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CGameDocumentBase.o:../gamecontrol/CGameDocumentBase.cpp  ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h 
	echo "Compiling gamecontrol/CGameDocumentBase.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CGameManager.o:../gamecontrol/CGameManager.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameManager.h ../gamecontrol/CGameView.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIDrawContext.h ../minebase/MineBase.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGameDocument.h ../gamecontrol/CSolutionFieldView.h ../minesolver/CompProbabilities.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/SolutionEnumerator.h ../minesolver/MineSolver.h ../gamecontrol/InputDevices.h ../gamecontrol/CDocHistory.h ../gamecontrol/CObserveableGameDocument.h ../gamecontrol/CHistoryDocument.h 
	echo "Compiling gamecontrol/CGameManager.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CGameTimer.o:../gamecontrol/CGameTimer.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameTimer.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling gamecontrol/CGameTimer.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CGameView.o:../gamecontrol/CGameView.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameView.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIDrawContext.h ../minebase/MineBase.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGlobalResourceSet.h ../mineuibase/UIAux.h 
	echo "Compiling gamecontrol/CGameView.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CGlobalResourceSet.o:../gamecontrol/CGlobalResourceSet.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGlobalResourceSet.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling gamecontrol/CGlobalResourceSet.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CHistoryDocument.o:../gamecontrol/CHistoryDocument.cpp  ../gamecontrol/CHistoryDocument.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocument.h ../gamecontrol/CDocHistory.h ../gamecontrol/CObserveableGameDocument.h 
	echo "Compiling gamecontrol/CHistoryDocument.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CJoystickInputDevice.o:../gamecontrol/CJoystickInputDevice.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CJoystickInputDevice.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h 
	echo "Compiling gamecontrol/CJoystickInputDevice.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CKeyboardInputDevice.o:../gamecontrol/CKeyboardInputDevice.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CKeyboardInputDevice.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h 
	echo "Compiling gamecontrol/CKeyboardInputDevice.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CKeyboardInputDevice2.o:../gamecontrol/CKeyboardInputDevice2.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CKeyboardInputDevice2.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h 
	echo "Compiling gamecontrol/CKeyboardInputDevice2.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CObserveableGameDocument.o:../gamecontrol/CObserveableGameDocument.cpp  ../gamecontrol/CObserveableGameDocument.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocument.h 
	echo "Compiling gamecontrol/CObserveableGameDocument.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CSolutionFieldView.o:../gamecontrol/CSolutionFieldView.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CSolutionFieldView.h ../minesolver/CompProbabilities.h ../minebase/MineBase.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../gamecontrol/FieldViews.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../minesolver/SolutionEnumerator.h ../minesolver/MineSolver.h ../gamecontrol/CGlobalResourceSet.h ../minebase/PlayArray.h ../gamecontrol/CGameDocument.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h ../mineuibase/UIAux.h ../minesolver/SolutionUtil.h ../storage/Document.h ../storage/CText.h ../minebase/MineBaseSerialize.h 
	echo "Compiling gamecontrol/CSolutionFieldView.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CTerminatorEsc.o:../gamecontrol/CTerminatorEsc.cpp 
	echo "Compiling gamecontrol/CTerminatorEsc.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/CUILayoutManager.o:../gamecontrol/CUILayoutManager.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../mineuibase/UIDrawContext.h ../minebase/MineBase.h 
	echo "Compiling gamecontrol/CUILayoutManager.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/FieldViews.o:../gamecontrol/FieldViews.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/FieldViews.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../minebase/MineBase.h ../gamecontrol/CGlobalResourceSet.h ../minebase/PlayArray.h ../gamecontrol/CGameDocument.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h 
	echo "Compiling gamecontrol/FieldViews.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/GameMisc.o:../gamecontrol/GameMisc.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/GameMisc.h 
	echo "Compiling gamecontrol/GameMisc.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/InputDevices.o:../gamecontrol/InputDevices.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGlobalResourceSet.h 
	echo "Compiling gamecontrol/InputDevices.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/gamecontrol/debug/StdAfx.o:../gamecontrol/StdAfx.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling gamecontrol/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minebase/debug/MineBase.o:../minebase/MineBase.cpp  ../minebase/StdAfx.h ../minebase/ConfigAll.h ../minebase/MineBase.h 
	echo "Compiling minebase/MineBase.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minebase/debug/MineBaseSerialize.o:../minebase/MineBaseSerialize.cpp  ../minebase/MineBaseSerialize.h ../minebase/MineBase.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minebase/MineBaseSerialize.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minebase/debug/PlayArray.o:../minebase/PlayArray.cpp  ../minebase/StdAfx.h ../minebase/ConfigAll.h ../minebase/PlayArray.h ../minebase/MineBase.h ../storage/Document.h ../storage/CText.h ../minebase/MineBaseSerialize.h 
	echo "Compiling minebase/PlayArray.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minebase/debug/StdAfx.o:../minebase/StdAfx.cpp  ../minebase/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling minebase/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CFieldValue.o:../minesolver/CFieldValue.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CFieldValue.h 
	echo "Compiling minesolver/CFieldValue.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CInputField.o:../minesolver/CInputField.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CInputField.h ../minebase/MineBase.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h 
	echo "Compiling minesolver/CInputField.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CInstanceCount.o:../minesolver/CInstanceCount.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CInstanceCount.h ../minebase/MineBase.h ../minesolver/MineMath.h 
	echo "Compiling minesolver/CInstanceCount.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CMineArray.o:../minesolver/CMineArray.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minebase/MineBase.h 
	echo "Compiling minesolver/CMineArray.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CompProbabilities.o:../minesolver/CompProbabilities.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CompProbabilities.h ../minebase/MineBase.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/SolutionIter.h ../minesolver/CInstanceCount.h ../minesolver/MineMath.h ../minebase/MineStd.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minesolver/CompProbabilities.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CompWinProp.o:../minesolver/CompWinProp.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CompWinProp.h ../minebase/MineBase.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CompProbabilities.h ../minesolver/SolutionIter.h 
	echo "Compiling minesolver/CompWinProp.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CResultField.o:../minesolver/CResultField.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CResultField.h ../minebase/MineBase.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minesolver/CResultField.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/CTerminator.o:../minesolver/CTerminator.cpp 
	echo "Compiling minesolver/CTerminator.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/MineMath.o:../minesolver/MineMath.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/MineMath.h 
	echo "Compiling minesolver/MineMath.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/MineSolver.o:../minesolver/MineSolver.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minebase/MineBase.h ../minebase/MineStd.h ../minesolver/MineMath.h ../minesolver/CFieldValue.h ../minesolver/CMineArray.h ../minesolver/CInstanceCount.h ../minesolver/MineSolver.h ../minesolver/CInputField.h ../minesolver/CResultField.h ../minesolver/SolutionIter.h ../minesolver/CompProbabilities.h 
	echo "Compiling minesolver/MineSolver.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/SolutionEnumerator.o:../minesolver/SolutionEnumerator.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/SolutionEnumerator.h ../minebase/MineBase.h ../minesolver/MineSolver.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CResultField.h ../minesolver/SolutionIter.h ../minesolver/CompProbabilities.h 
	echo "Compiling minesolver/SolutionEnumerator.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/SolutionIter.o:../minesolver/SolutionIter.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/SolutionIter.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minebase/MineBase.h 
	echo "Compiling minesolver/SolutionIter.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/SolutionUtil.o:../minesolver/SolutionUtil.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/SolutionUtil.h ../minebase/PlayArray.h ../minebase/MineBase.h ../minesolver/MineSolver.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CResultField.h 
	echo "Compiling minesolver/SolutionUtil.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minesolver/debug/StdAfx.o:../minesolver/StdAfx.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling minesolver/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/MineBaseTest.o:../minetest/MineBaseTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/MineBaseTest.h ../minebase/MineBase.h ../minetest/TestFramework.h 
	echo "Compiling minetest/MineBaseTest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/MinePropRegTest.o:../minetest/MinePropRegTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/MinePropRegTest.h ../minetest/RegressionTest.h ../minetest/TestFramework.h ../storage/Document.h ../storage/CText.h ../minesolver/CInputField.h ../minebase/MineBase.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CResultField.h ../minebase/MineBaseSerialize.h ../minesolver/CompProbabilities.h 
	echo "Compiling minetest/MinePropRegTest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/minetest.o:../minetest/minetest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/MineBaseTest.h ../minetest/SolverTest.h ../minetest/TestFramework.h ../minetest/SingleTest.h ../minetest/RegressionTestTest.h ../minetest/MinePropRegTest.h 
	echo "Compiling minetest/minetest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/RegressionTest.o:../minetest/RegressionTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/RegressionTest.h ../minetest/TestFramework.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minetest/RegressionTest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/RegressionTestTest.o:../minetest/RegressionTestTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/RegressionTestTest.h ../minetest/RegressionTest.h ../minetest/TestFramework.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minetest/RegressionTestTest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/SingleTest.o:../minetest/SingleTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/SingleTest.h ../minetest/TestFramework.h ../minebase/PlayArray.h ../minebase/MineBase.h ../storage/Document.h ../storage/CText.h ../minebase/MineBaseSerialize.h ../minesolver/CompWinProp.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CompProbabilities.h 
	echo "Compiling minetest/SingleTest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/SolverTest.o:../minetest/SolverTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/SolverTest.h ../minetest/TestFramework.h ../minebase/PlayArray.h ../minebase/MineBase.h ../minesolver/SolutionUtil.h ../minesolver/CompProbabilities.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h 
	echo "Compiling minetest/SolverTest.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/StdAfx.o:../minetest/StdAfx.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling minetest/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/minetest/debug/TestFramework.o:../minetest/TestFramework.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/TestFramework.h 
	echo "Compiling minetest/TestFramework.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineuibase/debug/CUIMineFrame.o:../mineuibase/CUIMineFrame.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../mineuibase/UIDrawContext.h 
	echo "Compiling mineuibase/CUIMineFrame.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineuibase/debug/StdAfx.o:../mineuibase/StdAfx.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling mineuibase/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineuibase/debug/UIAux.o:../mineuibase/UIAux.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIAux.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling mineuibase/UIAux.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineuibase/debug/UIBitmapUtil.o:../mineuibase/UIBitmapUtil.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIBitmapUtil.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../mineuibase/UIDrawContext.h 
	echo "Compiling mineuibase/UIBitmapUtil.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineuibase/debug/UIDrawContext.o:../mineuibase/UIDrawContext.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling mineuibase/UIDrawContext.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineuibase/debug/UIMisc.o:../mineuibase/UIMisc.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling mineuibase/UIMisc.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/CLevelMgr.o:../mineui_common/CLevelMgr.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/CLevelMgr.h ../mineui_common/CPersistentDictionary.h ../gamecontrol/GameMisc.h ../mineui_common/GameConstants.h ../mineui_common/CPersistentState.h ../mineui_common/GameOptions.h 
	echo "Compiling mineui_common/CLevelMgr.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/CPersistentDictionary.o:../mineui_common/CPersistentDictionary.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/CPersistentDictionary.h 
	echo "Compiling mineui_common/CPersistentDictionary.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/CPersistentState.o:../mineui_common/CPersistentState.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/CPersistentState.h ../mineui_common/GameOptions.h ../mineui_common/GameConstants.h ../gamecontrol/GameMisc.h ../mineui_common/CPersistentDictionary.h 
	echo "Compiling mineui_common/CPersistentState.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/GameConstants.o:../mineui_common/GameConstants.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/GameConstants.h ../gamecontrol/GameMisc.h 
	echo "Compiling mineui_common/GameConstants.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/GameOptions.o:../mineui_common/GameOptions.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/GameOptions.h ../mineui_common/GameConstants.h ../gamecontrol/GameMisc.h 
	echo "Compiling mineui_common/GameOptions.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/RCFileDictionary.o:../mineui_common/RCFileDictionary.cpp 
	echo "Compiling mineui_common/RCFileDictionary.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/StdAfx.o:../mineui_common/StdAfx.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling mineui_common/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_common/debug/TransientDictionary.o:../mineui_common/TransientDictionary.cpp 
	echo "Compiling mineui_common/TransientDictionary.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/mineui_ptc/debug/Application.o:../mineui_ptc/Application.cpp 
	echo "Compiling mineui_ptc/Application.cpp"
	$(CC) $(CFLAGS_DEBUG) $(CFLAGS_PTC_DEBUG) -c $< -o $@

../obj_cygwin/mineui_ptc/debug/StdAfx.o:../mineui_ptc/StdAfx.cpp  ../mineui_ptc/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling mineui_ptc/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG) $(CFLAGS_PTC_DEBUG) -c $< -o $@

../obj_cygwin/mineui_ptc/debug/UIDrawContextPTC.o:../mineui_ptc/UIDrawContextPTC.cpp 
	echo "Compiling mineui_ptc/UIDrawContextPTC.cpp"
	$(CC) $(CFLAGS_DEBUG) $(CFLAGS_PTC_DEBUG) -c $< -o $@

../obj_cygwin/storage/debug/CText.o:../storage/CText.cpp  ../storage/StdAfx.h ../storage/CText.h 
	echo "Compiling storage/CText.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/storage/debug/Document.o:../storage/Document.cpp  ../storage/StdAfx.h ../storage/Document.h ../storage/CText.h ../storage/Tree.h ../storage/Serializer.h 
	echo "Compiling storage/Document.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/storage/debug/Serializer.o:../storage/Serializer.cpp  ../storage/StdAfx.h ../storage/Serializer.h ../storage/Tree.h ../storage/CText.h 
	echo "Compiling storage/Serializer.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/storage/debug/StdAfx.o:../storage/StdAfx.cpp  ../storage/StdAfx.h 
	echo "Compiling storage/StdAfx.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

../obj_cygwin/storage/debug/Tree.o:../storage/Tree.cpp  ../storage/StdAfx.h ../storage/Tree.h ../storage/CText.h 
	echo "Compiling storage/Tree.cpp"
	$(CC) $(CFLAGS_DEBUG)  -c $< -o $@

copydata_debug:
	cp ../resources/*.bmp ../bin_cygwin/debug/

clean_debug:
	-rm ../obj_cygwin/gamecontrol/debug/CActionRecorder.o
	-rm ../obj_cygwin/gamecontrol/debug/CDocChangeObserver.o
	-rm ../obj_cygwin/gamecontrol/debug/CDocHistory.o
	-rm ../obj_cygwin/gamecontrol/debug/CGameDocument.o
	-rm ../obj_cygwin/gamecontrol/debug/CGameDocumentBase.o
	-rm ../obj_cygwin/gamecontrol/debug/CGameManager.o
	-rm ../obj_cygwin/gamecontrol/debug/CGameTimer.o
	-rm ../obj_cygwin/gamecontrol/debug/CGameView.o
	-rm ../obj_cygwin/gamecontrol/debug/CGlobalResourceSet.o
	-rm ../obj_cygwin/gamecontrol/debug/CHistoryDocument.o
	-rm ../obj_cygwin/gamecontrol/debug/CJoystickInputDevice.o
	-rm ../obj_cygwin/gamecontrol/debug/CKeyboardInputDevice.o
	-rm ../obj_cygwin/gamecontrol/debug/CKeyboardInputDevice2.o
	-rm ../obj_cygwin/gamecontrol/debug/CObserveableGameDocument.o
	-rm ../obj_cygwin/gamecontrol/debug/CSolutionFieldView.o
	-rm ../obj_cygwin/gamecontrol/debug/CTerminatorEsc.o
	-rm ../obj_cygwin/gamecontrol/debug/CUILayoutManager.o
	-rm ../obj_cygwin/gamecontrol/debug/FieldViews.o
	-rm ../obj_cygwin/gamecontrol/debug/GameMisc.o
	-rm ../obj_cygwin/gamecontrol/debug/InputDevices.o
	-rm ../obj_cygwin/gamecontrol/debug/StdAfx.o
	-rm ../obj_cygwin/minebase/debug/MineBase.o
	-rm ../obj_cygwin/minebase/debug/MineBaseSerialize.o
	-rm ../obj_cygwin/minebase/debug/PlayArray.o
	-rm ../obj_cygwin/minebase/debug/StdAfx.o
	-rm ../obj_cygwin/minesolver/debug/CFieldValue.o
	-rm ../obj_cygwin/minesolver/debug/CInputField.o
	-rm ../obj_cygwin/minesolver/debug/CInstanceCount.o
	-rm ../obj_cygwin/minesolver/debug/CMineArray.o
	-rm ../obj_cygwin/minesolver/debug/CompProbabilities.o
	-rm ../obj_cygwin/minesolver/debug/CompWinProp.o
	-rm ../obj_cygwin/minesolver/debug/CResultField.o
	-rm ../obj_cygwin/minesolver/debug/CTerminator.o
	-rm ../obj_cygwin/minesolver/debug/MineMath.o
	-rm ../obj_cygwin/minesolver/debug/MineSolver.o
	-rm ../obj_cygwin/minesolver/debug/SolutionEnumerator.o
	-rm ../obj_cygwin/minesolver/debug/SolutionIter.o
	-rm ../obj_cygwin/minesolver/debug/SolutionUtil.o
	-rm ../obj_cygwin/minesolver/debug/StdAfx.o
	-rm ../obj_cygwin/minetest/debug/MineBaseTest.o
	-rm ../obj_cygwin/minetest/debug/MinePropRegTest.o
	-rm ../obj_cygwin/minetest/debug/minetest.o
	-rm ../obj_cygwin/minetest/debug/RegressionTest.o
	-rm ../obj_cygwin/minetest/debug/RegressionTestTest.o
	-rm ../obj_cygwin/minetest/debug/SingleTest.o
	-rm ../obj_cygwin/minetest/debug/SolverTest.o
	-rm ../obj_cygwin/minetest/debug/StdAfx.o
	-rm ../obj_cygwin/minetest/debug/TestFramework.o
	-rm ../obj_cygwin/mineuibase/debug/CUIMineFrame.o
	-rm ../obj_cygwin/mineuibase/debug/StdAfx.o
	-rm ../obj_cygwin/mineuibase/debug/UIAux.o
	-rm ../obj_cygwin/mineuibase/debug/UIBitmapUtil.o
	-rm ../obj_cygwin/mineuibase/debug/UIDrawContext.o
	-rm ../obj_cygwin/mineuibase/debug/UIMisc.o
	-rm ../obj_cygwin/mineui_common/debug/CLevelMgr.o
	-rm ../obj_cygwin/mineui_common/debug/CPersistentDictionary.o
	-rm ../obj_cygwin/mineui_common/debug/CPersistentState.o
	-rm ../obj_cygwin/mineui_common/debug/GameConstants.o
	-rm ../obj_cygwin/mineui_common/debug/GameOptions.o
	-rm ../obj_cygwin/mineui_common/debug/RCFileDictionary.o
	-rm ../obj_cygwin/mineui_common/debug/StdAfx.o
	-rm ../obj_cygwin/mineui_common/debug/TransientDictionary.o
	-rm ../obj_cygwin/mineui_ptc/debug/Application.o
	-rm ../obj_cygwin/mineui_ptc/debug/StdAfx.o
	-rm ../obj_cygwin/mineui_ptc/debug/UIDrawContextPTC.o
	-rm ../obj_cygwin/storage/debug/CText.o
	-rm ../obj_cygwin/storage/debug/Document.o
	-rm ../obj_cygwin/storage/debug/Serializer.o
	-rm ../obj_cygwin/storage/debug/StdAfx.o
	-rm ../obj_cygwin/storage/debug/Tree.o
	-rm ../obj_cygwin/lib/debug/minesweeper.a
	-rm ../bin_cygwin/debug/minetest
	-rm ../bin_cygwin/debug/mineui_ptc

release:mkdirs_release ../obj_cygwin/lib/release/minesweeper.a ../bin_cygwin/release/minetest ../bin_cygwin/release/mineui_ptc

library_release: ../obj_cygwin/lib/release/minesweeper.a

../obj_cygwin/lib/release/minesweeper.a:../obj_cygwin/gamecontrol/release/CActionRecorder.o ../obj_cygwin/gamecontrol/release/CDocChangeObserver.o ../obj_cygwin/gamecontrol/release/CDocHistory.o ../obj_cygwin/gamecontrol/release/CGameDocument.o ../obj_cygwin/gamecontrol/release/CGameDocumentBase.o ../obj_cygwin/gamecontrol/release/CGameManager.o ../obj_cygwin/gamecontrol/release/CGameTimer.o ../obj_cygwin/gamecontrol/release/CGameView.o ../obj_cygwin/gamecontrol/release/CGlobalResourceSet.o ../obj_cygwin/gamecontrol/release/CHistoryDocument.o ../obj_cygwin/gamecontrol/release/CJoystickInputDevice.o ../obj_cygwin/gamecontrol/release/CKeyboardInputDevice.o ../obj_cygwin/gamecontrol/release/CKeyboardInputDevice2.o ../obj_cygwin/gamecontrol/release/CObserveableGameDocument.o ../obj_cygwin/gamecontrol/release/CSolutionFieldView.o ../obj_cygwin/gamecontrol/release/CTerminatorEsc.o ../obj_cygwin/gamecontrol/release/CUILayoutManager.o ../obj_cygwin/gamecontrol/release/FieldViews.o ../obj_cygwin/gamecontrol/release/GameMisc.o ../obj_cygwin/gamecontrol/release/InputDevices.o ../obj_cygwin/gamecontrol/release/StdAfx.o ../obj_cygwin/minebase/release/MineBase.o ../obj_cygwin/minebase/release/MineBaseSerialize.o ../obj_cygwin/minebase/release/PlayArray.o ../obj_cygwin/minebase/release/StdAfx.o ../obj_cygwin/minesolver/release/CFieldValue.o ../obj_cygwin/minesolver/release/CInputField.o ../obj_cygwin/minesolver/release/CInstanceCount.o ../obj_cygwin/minesolver/release/CMineArray.o ../obj_cygwin/minesolver/release/CompProbabilities.o ../obj_cygwin/minesolver/release/CompWinProp.o ../obj_cygwin/minesolver/release/CResultField.o ../obj_cygwin/minesolver/release/CTerminator.o ../obj_cygwin/minesolver/release/MineMath.o ../obj_cygwin/minesolver/release/MineSolver.o ../obj_cygwin/minesolver/release/SolutionEnumerator.o ../obj_cygwin/minesolver/release/SolutionIter.o ../obj_cygwin/minesolver/release/SolutionUtil.o ../obj_cygwin/minesolver/release/StdAfx.o ../obj_cygwin/mineuibase/release/CUIMineFrame.o ../obj_cygwin/mineuibase/release/StdAfx.o ../obj_cygwin/mineuibase/release/UIAux.o ../obj_cygwin/mineuibase/release/UIBitmapUtil.o ../obj_cygwin/mineuibase/release/UIDrawContext.o ../obj_cygwin/mineuibase/release/UIMisc.o ../obj_cygwin/mineui_common/release/CLevelMgr.o ../obj_cygwin/mineui_common/release/CPersistentDictionary.o ../obj_cygwin/mineui_common/release/CPersistentState.o ../obj_cygwin/mineui_common/release/GameConstants.o ../obj_cygwin/mineui_common/release/GameOptions.o ../obj_cygwin/mineui_common/release/RCFileDictionary.o ../obj_cygwin/mineui_common/release/StdAfx.o ../obj_cygwin/mineui_common/release/TransientDictionary.o ../obj_cygwin/storage/release/CText.o ../obj_cygwin/storage/release/Document.o ../obj_cygwin/storage/release/Serializer.o ../obj_cygwin/storage/release/StdAfx.o ../obj_cygwin/storage/release/Tree.o
	echo "Creating library minesweeper.a"
	ar -r $@ $^

minetest_release: ../bin_cygwin/release/minetest

../bin_cygwin/release/minetest:../obj_cygwin/minetest/release/MineBaseTest.o ../obj_cygwin/minetest/release/MinePropRegTest.o ../obj_cygwin/minetest/release/minetest.o ../obj_cygwin/minetest/release/RegressionTest.o ../obj_cygwin/minetest/release/RegressionTestTest.o ../obj_cygwin/minetest/release/SingleTest.o ../obj_cygwin/minetest/release/SolverTest.o ../obj_cygwin/minetest/release/StdAfx.o ../obj_cygwin/minetest/release/TestFramework.o ../obj_cygwin/lib/release/minesweeper.a
	echo "Creating executable minetest"
	$(CC) $(LINKFLAGS_RELEASE)  -o ../bin_cygwin/release/minetest$(EXE_POSTFIX) $^ 

mineui_ptc_release: ../bin_cygwin/release/mineui_ptc

../bin_cygwin/release/mineui_ptc:../obj_cygwin/mineui_ptc/release/Application.o ../obj_cygwin/mineui_ptc/release/StdAfx.o ../obj_cygwin/mineui_ptc/release/UIDrawContextPTC.o ../obj_cygwin/lib/release/minesweeper.a
	echo "Creating executable mineui_ptc"
	$(CC) $(LINKFLAGS_RELEASE) $(LINK_PTC_RELEASE) -o ../bin_cygwin/release/mineui_ptc$(EXE_POSTFIX) $^ $(LIBRARIES_PTC_RELEASE)

mkdirs_release:
	-mkdir -p ../obj_cygwin/gamecontrol/release/
	-mkdir -p ../obj_cygwin/minebase/release/
	-mkdir -p ../obj_cygwin/minesolver/release/
	-mkdir -p ../obj_cygwin/minetest/release/
	-mkdir -p ../obj_cygwin/mineuibase/release/
	-mkdir -p ../obj_cygwin/mineui_common/release/
	-mkdir -p ../obj_cygwin/mineui_ptc/release/
	-mkdir -p ../obj_cygwin/storage/release/
	-mkdir -p ../obj_cygwin/lib/release/
	-mkdir -p ../bin_cygwin/release/

../obj_cygwin/gamecontrol/release/CActionRecorder.o:../gamecontrol/CActionRecorder.cpp  ../gamecontrol/CActionRecorder.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocument.h 
	echo "Compiling gamecontrol/CActionRecorder.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CDocChangeObserver.o:../gamecontrol/CDocChangeObserver.cpp  ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h 
	echo "Compiling gamecontrol/CDocChangeObserver.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CDocHistory.o:../gamecontrol/CDocHistory.cpp  ../gamecontrol/CDocHistory.h ../gamecontrol/CGameDocument.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h ../gamecontrol/CObserveableGameDocument.h 
	echo "Compiling gamecontrol/CDocHistory.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CGameDocument.o:../gamecontrol/CGameDocument.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameDocument.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling gamecontrol/CGameDocument.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CGameDocumentBase.o:../gamecontrol/CGameDocumentBase.cpp  ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h 
	echo "Compiling gamecontrol/CGameDocumentBase.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CGameManager.o:../gamecontrol/CGameManager.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameManager.h ../gamecontrol/CGameView.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIDrawContext.h ../minebase/MineBase.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGameDocument.h ../gamecontrol/CSolutionFieldView.h ../minesolver/CompProbabilities.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/SolutionEnumerator.h ../minesolver/MineSolver.h ../gamecontrol/InputDevices.h ../gamecontrol/CDocHistory.h ../gamecontrol/CObserveableGameDocument.h ../gamecontrol/CHistoryDocument.h 
	echo "Compiling gamecontrol/CGameManager.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CGameTimer.o:../gamecontrol/CGameTimer.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameTimer.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling gamecontrol/CGameTimer.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CGameView.o:../gamecontrol/CGameView.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGameView.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIDrawContext.h ../minebase/MineBase.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGlobalResourceSet.h ../mineuibase/UIAux.h 
	echo "Compiling gamecontrol/CGameView.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CGlobalResourceSet.o:../gamecontrol/CGlobalResourceSet.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CGlobalResourceSet.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling gamecontrol/CGlobalResourceSet.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CHistoryDocument.o:../gamecontrol/CHistoryDocument.cpp  ../gamecontrol/CHistoryDocument.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocument.h ../gamecontrol/CDocHistory.h ../gamecontrol/CObserveableGameDocument.h 
	echo "Compiling gamecontrol/CHistoryDocument.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CJoystickInputDevice.o:../gamecontrol/CJoystickInputDevice.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CJoystickInputDevice.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h 
	echo "Compiling gamecontrol/CJoystickInputDevice.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CKeyboardInputDevice.o:../gamecontrol/CKeyboardInputDevice.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CKeyboardInputDevice.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h 
	echo "Compiling gamecontrol/CKeyboardInputDevice.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CKeyboardInputDevice2.o:../gamecontrol/CKeyboardInputDevice2.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CKeyboardInputDevice2.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h 
	echo "Compiling gamecontrol/CKeyboardInputDevice2.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CObserveableGameDocument.o:../gamecontrol/CObserveableGameDocument.cpp  ../gamecontrol/CObserveableGameDocument.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../minebase/MineBase.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocument.h 
	echo "Compiling gamecontrol/CObserveableGameDocument.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CSolutionFieldView.o:../gamecontrol/CSolutionFieldView.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CSolutionFieldView.h ../minesolver/CompProbabilities.h ../minebase/MineBase.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../gamecontrol/FieldViews.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../minesolver/SolutionEnumerator.h ../minesolver/MineSolver.h ../gamecontrol/CGlobalResourceSet.h ../minebase/PlayArray.h ../gamecontrol/CGameDocument.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h ../mineuibase/UIAux.h ../minesolver/SolutionUtil.h ../storage/Document.h ../storage/CText.h ../minebase/MineBaseSerialize.h 
	echo "Compiling gamecontrol/CSolutionFieldView.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CTerminatorEsc.o:../gamecontrol/CTerminatorEsc.cpp 
	echo "Compiling gamecontrol/CTerminatorEsc.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/CUILayoutManager.o:../gamecontrol/CUILayoutManager.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../mineuibase/UIDrawContext.h ../minebase/MineBase.h 
	echo "Compiling gamecontrol/CUILayoutManager.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/FieldViews.o:../gamecontrol/FieldViews.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/FieldViews.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../minebase/MineBase.h ../gamecontrol/CGlobalResourceSet.h ../minebase/PlayArray.h ../gamecontrol/CGameDocument.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CGameDocumentBase.h 
	echo "Compiling gamecontrol/FieldViews.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/GameMisc.o:../gamecontrol/GameMisc.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/GameMisc.h 
	echo "Compiling gamecontrol/GameMisc.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/InputDevices.o:../gamecontrol/InputDevices.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h ../gamecontrol/InputDevices.h ../minebase/MineBase.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../gamecontrol/CGameView.h ../gamecontrol/CUILayoutManager.h ../mineuibase/CUIMineFrame.h ../gamecontrol/FieldViews.h ../gamecontrol/CGameDocumentBase.h ../minebase/PlayArray.h ../gamecontrol/CGameTimer.h ../gamecontrol/GameMisc.h ../gamecontrol/CDocChangeObserver.h ../gamecontrol/CGlobalResourceSet.h 
	echo "Compiling gamecontrol/InputDevices.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/gamecontrol/release/StdAfx.o:../gamecontrol/StdAfx.cpp  ../gamecontrol/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling gamecontrol/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minebase/release/MineBase.o:../minebase/MineBase.cpp  ../minebase/StdAfx.h ../minebase/ConfigAll.h ../minebase/MineBase.h 
	echo "Compiling minebase/MineBase.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minebase/release/MineBaseSerialize.o:../minebase/MineBaseSerialize.cpp  ../minebase/MineBaseSerialize.h ../minebase/MineBase.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minebase/MineBaseSerialize.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minebase/release/PlayArray.o:../minebase/PlayArray.cpp  ../minebase/StdAfx.h ../minebase/ConfigAll.h ../minebase/PlayArray.h ../minebase/MineBase.h ../storage/Document.h ../storage/CText.h ../minebase/MineBaseSerialize.h 
	echo "Compiling minebase/PlayArray.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minebase/release/StdAfx.o:../minebase/StdAfx.cpp  ../minebase/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling minebase/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CFieldValue.o:../minesolver/CFieldValue.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CFieldValue.h 
	echo "Compiling minesolver/CFieldValue.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CInputField.o:../minesolver/CInputField.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CInputField.h ../minebase/MineBase.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h 
	echo "Compiling minesolver/CInputField.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CInstanceCount.o:../minesolver/CInstanceCount.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CInstanceCount.h ../minebase/MineBase.h ../minesolver/MineMath.h 
	echo "Compiling minesolver/CInstanceCount.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CMineArray.o:../minesolver/CMineArray.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minebase/MineBase.h 
	echo "Compiling minesolver/CMineArray.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CompProbabilities.o:../minesolver/CompProbabilities.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CompProbabilities.h ../minebase/MineBase.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/SolutionIter.h ../minesolver/CInstanceCount.h ../minesolver/MineMath.h ../minebase/MineStd.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minesolver/CompProbabilities.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CompWinProp.o:../minesolver/CompWinProp.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CompWinProp.h ../minebase/MineBase.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CompProbabilities.h ../minesolver/SolutionIter.h 
	echo "Compiling minesolver/CompWinProp.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CResultField.o:../minesolver/CResultField.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/CResultField.h ../minebase/MineBase.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minesolver/CResultField.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/CTerminator.o:../minesolver/CTerminator.cpp 
	echo "Compiling minesolver/CTerminator.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/MineMath.o:../minesolver/MineMath.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/MineMath.h 
	echo "Compiling minesolver/MineMath.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/MineSolver.o:../minesolver/MineSolver.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minebase/MineBase.h ../minebase/MineStd.h ../minesolver/MineMath.h ../minesolver/CFieldValue.h ../minesolver/CMineArray.h ../minesolver/CInstanceCount.h ../minesolver/MineSolver.h ../minesolver/CInputField.h ../minesolver/CResultField.h ../minesolver/SolutionIter.h ../minesolver/CompProbabilities.h 
	echo "Compiling minesolver/MineSolver.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/SolutionEnumerator.o:../minesolver/SolutionEnumerator.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/SolutionEnumerator.h ../minebase/MineBase.h ../minesolver/MineSolver.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CResultField.h ../minesolver/SolutionIter.h ../minesolver/CompProbabilities.h 
	echo "Compiling minesolver/SolutionEnumerator.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/SolutionIter.o:../minesolver/SolutionIter.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/SolutionIter.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minebase/MineBase.h 
	echo "Compiling minesolver/SolutionIter.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/SolutionUtil.o:../minesolver/SolutionUtil.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h ../minesolver/SolutionUtil.h ../minebase/PlayArray.h ../minebase/MineBase.h ../minesolver/MineSolver.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CResultField.h 
	echo "Compiling minesolver/SolutionUtil.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minesolver/release/StdAfx.o:../minesolver/StdAfx.cpp  ../minesolver/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling minesolver/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/MineBaseTest.o:../minetest/MineBaseTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/MineBaseTest.h ../minebase/MineBase.h ../minetest/TestFramework.h 
	echo "Compiling minetest/MineBaseTest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/MinePropRegTest.o:../minetest/MinePropRegTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/MinePropRegTest.h ../minetest/RegressionTest.h ../minetest/TestFramework.h ../storage/Document.h ../storage/CText.h ../minesolver/CInputField.h ../minebase/MineBase.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CResultField.h ../minebase/MineBaseSerialize.h ../minesolver/CompProbabilities.h 
	echo "Compiling minetest/MinePropRegTest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/minetest.o:../minetest/minetest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/MineBaseTest.h ../minetest/SolverTest.h ../minetest/TestFramework.h ../minetest/SingleTest.h ../minetest/RegressionTestTest.h ../minetest/MinePropRegTest.h 
	echo "Compiling minetest/minetest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/RegressionTest.o:../minetest/RegressionTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/RegressionTest.h ../minetest/TestFramework.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minetest/RegressionTest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/RegressionTestTest.o:../minetest/RegressionTestTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/RegressionTestTest.h ../minetest/RegressionTest.h ../minetest/TestFramework.h ../storage/Document.h ../storage/CText.h 
	echo "Compiling minetest/RegressionTestTest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/SingleTest.o:../minetest/SingleTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/SingleTest.h ../minetest/TestFramework.h ../minebase/PlayArray.h ../minebase/MineBase.h ../storage/Document.h ../storage/CText.h ../minebase/MineBaseSerialize.h ../minesolver/CompWinProp.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h ../minesolver/CompProbabilities.h 
	echo "Compiling minetest/SingleTest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/SolverTest.o:../minetest/SolverTest.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/SolverTest.h ../minetest/TestFramework.h ../minebase/PlayArray.h ../minebase/MineBase.h ../minesolver/SolutionUtil.h ../minesolver/CompProbabilities.h ../minesolver/CResultField.h ../minesolver/CMineArray.h ../minesolver/CFieldValue.h ../minesolver/CInputField.h 
	echo "Compiling minetest/SolverTest.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/StdAfx.o:../minetest/StdAfx.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling minetest/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/minetest/release/TestFramework.o:../minetest/TestFramework.cpp  ../minetest/StdAfx.h ../minebase/ConfigAll.h ../minetest/TestFramework.h 
	echo "Compiling minetest/TestFramework.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineuibase/release/CUIMineFrame.o:../mineuibase/CUIMineFrame.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/CUIMineFrame.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../mineuibase/UIDrawContext.h 
	echo "Compiling mineuibase/CUIMineFrame.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineuibase/release/StdAfx.o:../mineuibase/StdAfx.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling mineuibase/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineuibase/release/UIAux.o:../mineuibase/UIAux.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIAux.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling mineuibase/UIAux.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineuibase/release/UIBitmapUtil.o:../mineuibase/UIBitmapUtil.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIBitmapUtil.h ../mineuibase/UIMisc.h ../minebase/MineStd.h ../mineuibase/UIDrawContext.h 
	echo "Compiling mineuibase/UIBitmapUtil.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineuibase/release/UIDrawContext.o:../mineuibase/UIDrawContext.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIDrawContext.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling mineuibase/UIDrawContext.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineuibase/release/UIMisc.o:../mineuibase/UIMisc.cpp  ../mineuibase/StdAfx.h ../minebase/ConfigAll.h ../mineuibase/UIMisc.h ../minebase/MineStd.h 
	echo "Compiling mineuibase/UIMisc.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/CLevelMgr.o:../mineui_common/CLevelMgr.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/CLevelMgr.h ../mineui_common/CPersistentDictionary.h ../gamecontrol/GameMisc.h ../mineui_common/GameConstants.h ../mineui_common/CPersistentState.h ../mineui_common/GameOptions.h 
	echo "Compiling mineui_common/CLevelMgr.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/CPersistentDictionary.o:../mineui_common/CPersistentDictionary.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/CPersistentDictionary.h 
	echo "Compiling mineui_common/CPersistentDictionary.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/CPersistentState.o:../mineui_common/CPersistentState.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/CPersistentState.h ../mineui_common/GameOptions.h ../mineui_common/GameConstants.h ../gamecontrol/GameMisc.h ../mineui_common/CPersistentDictionary.h 
	echo "Compiling mineui_common/CPersistentState.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/GameConstants.o:../mineui_common/GameConstants.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/GameConstants.h ../gamecontrol/GameMisc.h 
	echo "Compiling mineui_common/GameConstants.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/GameOptions.o:../mineui_common/GameOptions.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h ../mineui_common/GameOptions.h ../mineui_common/GameConstants.h ../gamecontrol/GameMisc.h 
	echo "Compiling mineui_common/GameOptions.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/RCFileDictionary.o:../mineui_common/RCFileDictionary.cpp 
	echo "Compiling mineui_common/RCFileDictionary.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/StdAfx.o:../mineui_common/StdAfx.cpp  ../mineui_common/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling mineui_common/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_common/release/TransientDictionary.o:../mineui_common/TransientDictionary.cpp 
	echo "Compiling mineui_common/TransientDictionary.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/mineui_ptc/release/Application.o:../mineui_ptc/Application.cpp 
	echo "Compiling mineui_ptc/Application.cpp"
	$(CC) $(CFLAGS_RELEASE) $(CFLAGS_PTC_RELEASE) -c $< -o $@

../obj_cygwin/mineui_ptc/release/StdAfx.o:../mineui_ptc/StdAfx.cpp  ../mineui_ptc/StdAfx.h ../minebase/ConfigAll.h 
	echo "Compiling mineui_ptc/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE) $(CFLAGS_PTC_RELEASE) -c $< -o $@

../obj_cygwin/mineui_ptc/release/UIDrawContextPTC.o:../mineui_ptc/UIDrawContextPTC.cpp 
	echo "Compiling mineui_ptc/UIDrawContextPTC.cpp"
	$(CC) $(CFLAGS_RELEASE) $(CFLAGS_PTC_RELEASE) -c $< -o $@

../obj_cygwin/storage/release/CText.o:../storage/CText.cpp  ../storage/StdAfx.h ../storage/CText.h 
	echo "Compiling storage/CText.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/storage/release/Document.o:../storage/Document.cpp  ../storage/StdAfx.h ../storage/Document.h ../storage/CText.h ../storage/Tree.h ../storage/Serializer.h 
	echo "Compiling storage/Document.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/storage/release/Serializer.o:../storage/Serializer.cpp  ../storage/StdAfx.h ../storage/Serializer.h ../storage/Tree.h ../storage/CText.h 
	echo "Compiling storage/Serializer.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/storage/release/StdAfx.o:../storage/StdAfx.cpp  ../storage/StdAfx.h 
	echo "Compiling storage/StdAfx.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

../obj_cygwin/storage/release/Tree.o:../storage/Tree.cpp  ../storage/StdAfx.h ../storage/Tree.h ../storage/CText.h 
	echo "Compiling storage/Tree.cpp"
	$(CC) $(CFLAGS_RELEASE)  -c $< -o $@

copydata_release:
	cp ../resources/*.bmp ../bin_cygwin/release/

clean_release:
	-rm ../obj_cygwin/gamecontrol/release/CActionRecorder.o
	-rm ../obj_cygwin/gamecontrol/release/CDocChangeObserver.o
	-rm ../obj_cygwin/gamecontrol/release/CDocHistory.o
	-rm ../obj_cygwin/gamecontrol/release/CGameDocument.o
	-rm ../obj_cygwin/gamecontrol/release/CGameDocumentBase.o
	-rm ../obj_cygwin/gamecontrol/release/CGameManager.o
	-rm ../obj_cygwin/gamecontrol/release/CGameTimer.o
	-rm ../obj_cygwin/gamecontrol/release/CGameView.o
	-rm ../obj_cygwin/gamecontrol/release/CGlobalResourceSet.o
	-rm ../obj_cygwin/gamecontrol/release/CHistoryDocument.o
	-rm ../obj_cygwin/gamecontrol/release/CJoystickInputDevice.o
	-rm ../obj_cygwin/gamecontrol/release/CKeyboardInputDevice.o
	-rm ../obj_cygwin/gamecontrol/release/CKeyboardInputDevice2.o
	-rm ../obj_cygwin/gamecontrol/release/CObserveableGameDocument.o
	-rm ../obj_cygwin/gamecontrol/release/CSolutionFieldView.o
	-rm ../obj_cygwin/gamecontrol/release/CTerminatorEsc.o
	-rm ../obj_cygwin/gamecontrol/release/CUILayoutManager.o
	-rm ../obj_cygwin/gamecontrol/release/FieldViews.o
	-rm ../obj_cygwin/gamecontrol/release/GameMisc.o
	-rm ../obj_cygwin/gamecontrol/release/InputDevices.o
	-rm ../obj_cygwin/gamecontrol/release/StdAfx.o
	-rm ../obj_cygwin/minebase/release/MineBase.o
	-rm ../obj_cygwin/minebase/release/MineBaseSerialize.o
	-rm ../obj_cygwin/minebase/release/PlayArray.o
	-rm ../obj_cygwin/minebase/release/StdAfx.o
	-rm ../obj_cygwin/minesolver/release/CFieldValue.o
	-rm ../obj_cygwin/minesolver/release/CInputField.o
	-rm ../obj_cygwin/minesolver/release/CInstanceCount.o
	-rm ../obj_cygwin/minesolver/release/CMineArray.o
	-rm ../obj_cygwin/minesolver/release/CompProbabilities.o
	-rm ../obj_cygwin/minesolver/release/CompWinProp.o
	-rm ../obj_cygwin/minesolver/release/CResultField.o
	-rm ../obj_cygwin/minesolver/release/CTerminator.o
	-rm ../obj_cygwin/minesolver/release/MineMath.o
	-rm ../obj_cygwin/minesolver/release/MineSolver.o
	-rm ../obj_cygwin/minesolver/release/SolutionEnumerator.o
	-rm ../obj_cygwin/minesolver/release/SolutionIter.o
	-rm ../obj_cygwin/minesolver/release/SolutionUtil.o
	-rm ../obj_cygwin/minesolver/release/StdAfx.o
	-rm ../obj_cygwin/minetest/release/MineBaseTest.o
	-rm ../obj_cygwin/minetest/release/MinePropRegTest.o
	-rm ../obj_cygwin/minetest/release/minetest.o
	-rm ../obj_cygwin/minetest/release/RegressionTest.o
	-rm ../obj_cygwin/minetest/release/RegressionTestTest.o
	-rm ../obj_cygwin/minetest/release/SingleTest.o
	-rm ../obj_cygwin/minetest/release/SolverTest.o
	-rm ../obj_cygwin/minetest/release/StdAfx.o
	-rm ../obj_cygwin/minetest/release/TestFramework.o
	-rm ../obj_cygwin/mineuibase/release/CUIMineFrame.o
	-rm ../obj_cygwin/mineuibase/release/StdAfx.o
	-rm ../obj_cygwin/mineuibase/release/UIAux.o
	-rm ../obj_cygwin/mineuibase/release/UIBitmapUtil.o
	-rm ../obj_cygwin/mineuibase/release/UIDrawContext.o
	-rm ../obj_cygwin/mineuibase/release/UIMisc.o
	-rm ../obj_cygwin/mineui_common/release/CLevelMgr.o
	-rm ../obj_cygwin/mineui_common/release/CPersistentDictionary.o
	-rm ../obj_cygwin/mineui_common/release/CPersistentState.o
	-rm ../obj_cygwin/mineui_common/release/GameConstants.o
	-rm ../obj_cygwin/mineui_common/release/GameOptions.o
	-rm ../obj_cygwin/mineui_common/release/RCFileDictionary.o
	-rm ../obj_cygwin/mineui_common/release/StdAfx.o
	-rm ../obj_cygwin/mineui_common/release/TransientDictionary.o
	-rm ../obj_cygwin/mineui_ptc/release/Application.o
	-rm ../obj_cygwin/mineui_ptc/release/StdAfx.o
	-rm ../obj_cygwin/mineui_ptc/release/UIDrawContextPTC.o
	-rm ../obj_cygwin/storage/release/CText.o
	-rm ../obj_cygwin/storage/release/Document.o
	-rm ../obj_cygwin/storage/release/Serializer.o
	-rm ../obj_cygwin/storage/release/StdAfx.o
	-rm ../obj_cygwin/storage/release/Tree.o
	-rm ../obj_cygwin/lib/release/minesweeper.a
	-rm ../bin_cygwin/release/minetest
	-rm ../bin_cygwin/release/mineui_ptc

depends:
	-rm depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CActionRecorder.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CActionRecorder" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CDocChangeObserver.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CDocChangeObserver" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CDocHistory.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CDocHistory" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CGameDocument.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CGameDocument" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CGameDocumentBase.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CGameDocumentBase" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CGameManager.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CGameManager" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CGameTimer.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CGameTimer" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CGameView.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CGameView" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CGlobalResourceSet.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CGlobalResourceSet" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CHistoryDocument.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CHistoryDocument" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CJoystickInputDevice.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CJoystickInputDevice" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CKeyboardInputDevice.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CKeyboardInputDevice" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CKeyboardInputDevice2.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CKeyboardInputDevice2" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CObserveableGameDocument.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CObserveableGameDocument" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CSolutionFieldView.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CSolutionFieldView" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CTerminatorEsc.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CTerminatorEsc" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/CUILayoutManager.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;CUILayoutManager" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/FieldViews.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;FieldViews" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/GameMisc.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;GameMisc" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/InputDevices.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;InputDevices" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../gamecontrol/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "gamecontrol;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minebase/MineBase.cpp -o dependstmp.txt
	perl addtodepend.pl "minebase;MineBase" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minebase/MineBaseSerialize.cpp -o dependstmp.txt
	perl addtodepend.pl "minebase;MineBaseSerialize" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minebase/PlayArray.cpp -o dependstmp.txt
	perl addtodepend.pl "minebase;PlayArray" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minebase/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "minebase;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CFieldValue.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CFieldValue" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CInputField.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CInputField" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CInstanceCount.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CInstanceCount" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CMineArray.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CMineArray" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CompProbabilities.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CompProbabilities" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CompWinProp.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CompWinProp" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CResultField.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CResultField" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/CTerminator.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;CTerminator" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/MineMath.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;MineMath" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/MineSolver.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;MineSolver" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/SolutionEnumerator.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;SolutionEnumerator" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/SolutionIter.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;SolutionIter" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/SolutionUtil.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;SolutionUtil" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minesolver/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "minesolver;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/MineBaseTest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;MineBaseTest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/MinePropRegTest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;MinePropRegTest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/minetest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;minetest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/RegressionTest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;RegressionTest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/RegressionTestTest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;RegressionTestTest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/SingleTest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;SingleTest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/SolverTest.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;SolverTest" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../minetest/TestFramework.cpp -o dependstmp.txt
	perl addtodepend.pl "minetest;TestFramework" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineuibase/CUIMineFrame.cpp -o dependstmp.txt
	perl addtodepend.pl "mineuibase;CUIMineFrame" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineuibase/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "mineuibase;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineuibase/UIAux.cpp -o dependstmp.txt
	perl addtodepend.pl "mineuibase;UIAux" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineuibase/UIBitmapUtil.cpp -o dependstmp.txt
	perl addtodepend.pl "mineuibase;UIBitmapUtil" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineuibase/UIDrawContext.cpp -o dependstmp.txt
	perl addtodepend.pl "mineuibase;UIDrawContext" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineuibase/UIMisc.cpp -o dependstmp.txt
	perl addtodepend.pl "mineuibase;UIMisc" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/CLevelMgr.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;CLevelMgr" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/CPersistentDictionary.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;CPersistentDictionary" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/CPersistentState.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;CPersistentState" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/GameConstants.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;GameConstants" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/GameOptions.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;GameOptions" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/RCFileDictionary.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;RCFileDictionary" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../mineui_common/TransientDictionary.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_common;TransientDictionary" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG) $(CFLAGS_PTC_DEBUG) -M -c ../mineui_ptc/Application.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_ptc;Application" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG) $(CFLAGS_PTC_DEBUG) -M -c ../mineui_ptc/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_ptc;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG) $(CFLAGS_PTC_DEBUG) -M -c ../mineui_ptc/UIDrawContextPTC.cpp -o dependstmp.txt
	perl addtodepend.pl "mineui_ptc;UIDrawContextPTC" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../storage/CText.cpp -o dependstmp.txt
	perl addtodepend.pl "storage;CText" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../storage/Document.cpp -o dependstmp.txt
	perl addtodepend.pl "storage;Document" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../storage/Serializer.cpp -o dependstmp.txt
	perl addtodepend.pl "storage;Serializer" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../storage/StdAfx.cpp -o dependstmp.txt
	perl addtodepend.pl "storage;StdAfx" dependstmp.txt depends.inc
	-$(CC) $(CFLAGS_DEBUG)  -M -c ../storage/Tree.cpp -o dependstmp.txt
	perl addtodepend.pl "storage;Tree" dependstmp.txt depends.inc
	-rm dependstmp.txt

