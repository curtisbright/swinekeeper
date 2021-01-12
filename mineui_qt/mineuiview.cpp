#include "StdAfx.h"
#include "mineuiview.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <qpainter.h>
#include <qtimer.h>
#include <gamecontrol/GameMisc.h>

#include "uidrawcontextqt.h"
#include "halloffamedlgimpl.h"
#include "scorenamedlgimpl.h"

#include "minefieldtooltip.h"

MineUIView::MineUIView(QWidget *parent, const char *name)
    : QWidget(parent, name),
      m_bFullUpdate(true)
{
    m_gameMgr.init(&m_mouse);
    for(int i=0;i<4;i++) m_vbPressedButtons[i] = false;

    setBackgroundMode(NoBackground);

    // XXX i need a timer event only when the game is running XXX
    m_pTimer = new QTimer(this);
    QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updateTimeSlot()));
    m_pTimer->start(500, false);
    
    // for tooltips
    setMouseTracking(true);
    new MineFieldToolTip(this, &m_gameMgr);
}

MineUIView::~MineUIView()
{
}

void MineUIView::setLevelMgr(CLevelMgr *pLevelMgr)
{
    m_pLevelMgr = pLevelMgr;
}

void MineUIView::solveSlot()
{
    /*
    QPainter p;
    p.begin( this );
    {
    CUIDrawContextQt drawCtx(&p);
    m_gameMgr.draw(&drawCtx, m_bFullUpdate, true);
    }
    p.end();
    */ 

    m_gameMgr.showSolution();
    repaintChanges();
}    

/**
 * If the view currently shows a solution, this function resets the view
 */
void MineUIView::resetSolveSlot()
{
    m_gameMgr.hideSolution();
    repaintChanges();
}

/**
 * Walk backwards in history. Works only if the game is finished
 */
void MineUIView::prevSlot()
{
    m_gameMgr.historyPrev();
    repaintChanges();
}

/**
 * Walks forwards in history.
 */
void MineUIView::nextSlot()
{
    m_gameMgr.historyNext();
    repaintChanges();
}

void MineUIView::paintEvent( QPaintEvent * )
{
    QPainter p;
    p.begin( this );

    {
    CUIDrawContextQt drawCtx(&p);
    m_gameMgr.draw(&drawCtx, m_bFullUpdate);
    }
    
    p.end();
    m_bFullUpdate = true;
}

void MineUIView::mousePressEvent(QMouseEvent *pEvt)
{
    assert(m_pLevelMgr);
    CMouseInputDevice::MouseButton nButton = cnvMouseButton(pEvt->button());
    if (nButton >= 0 && nButton < 4) m_vbPressedButtons[nButton] = true;

    // XXX todo: activate timer only if game is running
    //     (optimization) XXX

    // I'm using the mouse-button-enum as indices for array -> make sure that
    // the indices didn't change
    assert(CMouseInputDevice::BUTTON_RIGHT == 3);

    // if both left and right buttons are pushed, push the middle button instead
    if (m_vbPressedButtons[CMouseInputDevice::BUTTON_LEFT]
    && m_vbPressedButtons[CMouseInputDevice::BUTTON_RIGHT])
    m_mouse.onPushButton(toUI(pEvt->pos()), CMouseInputDevice::BUTTON_MIDDLE);
    else     
    m_mouse.onPushButton(toUI(pEvt->pos()), nButton);

    repaintChanges();
}

void MineUIView::mouseReleaseEvent(QMouseEvent *pEvt)
{
    CMouseInputDevice::MouseButton nButton = cnvMouseButton(pEvt->button());
    bool bIsRunningOld = m_gameMgr.isGameRunning();

    m_mouse.onReleaseButton(toUI(pEvt->pos()));
    repaintChanges();
        
    if (bIsRunningOld && m_gameMgr.isGameFinished())
    {
    m_gameMgr.activateRewind();

    if (m_gameMgr.isGameWon())
    {
        checkGameResult();
    }
    }
       
    if (nButton >= 0 && nButton < 4) m_vbPressedButtons[nButton] = false;
}

void MineUIView::mouseMoveEvent(QMouseEvent *pEvt)
{
    m_mouse.onMoveMouse(toUI(pEvt->pos()));
    repaintChanges();
}

CMouseInputDevice::MouseButton MineUIView::cnvMouseButton(int nQtMouseButton)
{
    switch (nQtMouseButton) {
    case LeftButton: return  CMouseInputDevice::BUTTON_LEFT;
    case RightButton: return CMouseInputDevice::BUTTON_RIGHT;
    case MidButton: return CMouseInputDevice::BUTTON_MIDDLE;
    case NoButton:
    default: return CMouseInputDevice::BUTTON_NONE;
    }    
}


QSize MineUIView::getClientSize()
{
    return toQt(m_gameMgr.getClientWindowSize());
}

// XXX don't know if needed ??? XXX
QSize MineUIView::sizeHint()
{
    return getClientSize();
}

void MineUIView::reset()
{
    m_gameMgr.resetGame();
    repaint();
}

void MineUIView::setGameDim(const CGameDim &gameDim)
{
    m_gameMgr.resize(gameDim);

}

CGameDim MineUIView::getGameDim() const
{
    return m_gameMgr.getGameDim();
}

void MineUIView::repaintChanges()
{
    m_bFullUpdate = false;
    repaint();
}

void MineUIView::updateTimeSlot()
{
    repaintChanges();
}

GameConstant::GameLevel MineUIView::getCurrentGameLevel()
{
    CGameDim gameDim = m_gameMgr.getGameDim();
    GameConstant::GameLevel nGameLevel(GameConstant::LEVEL_USER_DEFINED);

    if (gameDim == GameConstant::getGameDimOfLevel(GameConstant::LEVEL_BEGINNER))
    nGameLevel = GameConstant::LEVEL_BEGINNER;

    if (gameDim == GameConstant::getGameDimOfLevel(GameConstant::LEVEL_INTERMEDIATE))
    nGameLevel = GameConstant::LEVEL_INTERMEDIATE;

    if (gameDim == GameConstant::getGameDimOfLevel(GameConstant::LEVEL_EXPERT))
    nGameLevel = GameConstant::LEVEL_EXPERT;

    return nGameLevel;
}


void MineUIView::checkGameResult()
{
    int nTime = m_gameMgr.getTime();
    
    if (m_pLevelMgr->hasReachedNewHighScore(nTime) && m_gameMgr.userMayEnterHallOfFame())
    {

    ScoreNameDlg *pNameDlg = new ScoreNameDlg(this);
    
    std::string defaultName;
    if (m_pLevelMgr->getCurrentName(defaultName)) 
        pNameDlg->setDefaultName(defaultName.c_str()); 
    
    if (pNameDlg->exec() == ScoreNameDlg::Accepted)
    {
        m_pLevelMgr->enterHallOfFame(std::string(pNameDlg->getName()), nTime);
        HallOfFameDlg *pDlg = new HallOfFameDlg(this, m_pLevelMgr);
        pDlg->exec();
        delete pDlg;
    }
    
    delete pNameDlg;
    }
}

void MineUIView::toggleMarker()
{
    m_gameMgr.enableQMMarkers(!m_gameMgr.areQMMarkersEnabled()); 
}

bool MineUIView::isMarkerEnabled() const
{
    return m_gameMgr.areQMMarkersEnabled(); 
}






