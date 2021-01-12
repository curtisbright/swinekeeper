#ifndef MINEUIVIEW_H
#define MINEUIVIEW_H

#include <qwidget.h>
#include <gamecontrol/CGameManager.h>
#include <gamecontrol/CGlobalResourceSet.h>
#include <gamecontrol/InputDevices.h>
#include <gamecontrol/GameMisc.h>
#include <mineui_common/GameConstants.h>
#include <mineui_common/CLevelMgr.h>

class QSize;
class QTimer;

class MineUIView : public QWidget {
   Q_OBJECT
   
public:    
   MineUIView(QWidget *parent=0, const char *name=0);
   ~MineUIView();

   void setLevelMgr(CLevelMgr *pLevelMgr);
   QSize getClientSize() ;
   QSize sizeHint();
   void reset();
   // void setGameDim(int nX, int nY, int nBombs);
   void setGameDim(const CGameDim &gameDim);
   CGameDim getGameDim() const;
   void toggleMarker(); 
   bool isMarkerEnabled() const; 

public slots:
   void solveSlot();       
   void resetSolveSlot();
   void prevSlot();
   void nextSlot();
protected:
   void paintEvent( QPaintEvent * );
   void mousePressEvent(QMouseEvent *);
   void mouseReleaseEvent(QMouseEvent *);
   void mouseMoveEvent(QMouseEvent *);
private:
   CGameManager m_gameMgr;
   CMouseInputDevice m_mouse;
   bool m_vbPressedButtons[4];
   bool m_bFullUpdate;
   QTimer *m_pTimer;     
   // bool m_bUserMayEnterHallOfFame;
   CLevelMgr *m_pLevelMgr;    

   CMouseInputDevice::MouseButton cnvMouseButton(int nQtMouseButton);
   void repaintChanges();
   GameConstant::GameLevel getCurrentGameLevel();
   void checkGameResult();    
private slots:
   void updateTimeSlot();                 

};

#endif
