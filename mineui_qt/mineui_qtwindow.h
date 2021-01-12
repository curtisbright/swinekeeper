#include <qmainwindow.h>
#include <mineui_common/CLevelMgr.h>

class MineUIView;
class QPopupMenu; 
class CPersistentDictionary; 

class MineUI_QtWindow : public QMainWindow
{
   Q_OBJECT
public:
   MineUI_QtWindow(CPersistentDictionary *pDict, QWidget* parent = 0, const char* name = 0, WFlags f = WType_TopLevel );

public slots: 
   void game_newGame();
   void game_setGameLevelSlot(int nGameLevel); 
   void game_toggleMarker();
   void game_showHallOfFame();
   void game_quit();
   void view_solve();
   void view_reset();
   void view_prev();
   void view_next();
   void help_about();
   

private: 
   MineUIView *m_pView;       
   CLevelMgr m_levelMgr;
   QPopupMenu *m_pGameMenu; 
   QMenuBar *m_pMenu; 
   int m_nMarkerMenuId; 

   enum GameLevelIDs {
      FILE_MENU_BEGINNER=20,
      FILE_MENU_ADVANCED,
      FILE_MENU_EXPERT,
      FILE_MENU_USERDEFINED
   };

private:    
   void adjustToClientSize();
   void updateMenuState();
   void updateMarkerMenu(); 
};

