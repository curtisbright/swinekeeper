#include "StdAfx.h"
#include "mineui_qtwindow.h"

#include <qmenubar.h>
#include <qpopupmenu.h>
#include "mineuiview.h"
#include "halloffamedlgimpl.h"
#include "qmessagebox.h" 
#include <qapplication.h>
#include "gamedimdlgimpl.h"

MineUI_QtWindow::MineUI_QtWindow(CPersistentDictionary *pDict, QWidget* parent, const char* name, WFlags f )
    : QMainWindow( parent, name, f)
{
    setCaption("Truffle-Swine Keeper");

    m_levelMgr.init(pDict);         

    m_pView = new MineUIView(this);
    m_pView->setLevelMgr(&m_levelMgr);
    setCentralWidget(m_pView);

    QPopupMenu *pGameMenu = new QPopupMenu; 
    pGameMenu->insertItem("&New", this, SLOT(game_newGame()), Key_F2); 
    pGameMenu->insertItem("&Beginner", FILE_MENU_BEGINNER);
    pGameMenu->insertItem("&Intermediate", FILE_MENU_ADVANCED);
    pGameMenu->insertItem("&Expert", FILE_MENU_EXPERT);
    pGameMenu->insertItem("&User defined ...", FILE_MENU_USERDEFINED);
    pGameMenu->insertSeparator(); 
    m_nMarkerMenuId = pGameMenu->insertItem("&Marker (?)", this, SLOT(game_toggleMarker())); 
    pGameMenu->insertSeparator(); 
    pGameMenu->insertItem("&Hall of Fame", this, SLOT(game_showHallOfFame())); 
    pGameMenu->insertItem("&End", this, SLOT(game_quit())); 
    m_pGameMenu = pGameMenu; 

    QObject::connect(pGameMenu, SIGNAL(activated(int)), this, SLOT(game_setGameLevelSlot(int)));

    QPopupMenu *pViewMenu = new QPopupMenu; 
    pViewMenu->insertItem("&Solve", this, SLOT(view_solve()), Key_F3); 
    pViewMenu->insertItem("&Reset", this, SLOT(view_reset()), Key_F4); 
    pViewMenu->insertItem("&Prev", this, SLOT(view_prev()), Key_F5); 
    pViewMenu->insertItem("&Next", this, SLOT(view_next()), Key_F6); 
           
    QPopupMenu *pHelpMenu = new QPopupMenu; 
    pHelpMenu->insertItem("&About Truffle-Swine Keeper", this, SLOT(help_about())); 

    QMenuBar *pMenuBar = new QMenuBar(this); 
    pMenuBar->insertItem("&Game", pGameMenu); 
    pMenuBar->insertItem("&View", pViewMenu); 
    pMenuBar->insertItem("&Help", pHelpMenu); 
    m_pMenu = pMenuBar; 

    updateMenuState();     
    m_pView->setGameDim(m_levelMgr.getGameDim());        
    adjustToClientSize();
    updateMarkerMenu(); 
}

void MineUI_QtWindow::updateMenuState()
{
    m_pGameMenu->setItemChecked(FILE_MENU_BEGINNER, false);
    m_pGameMenu->setItemChecked(FILE_MENU_ADVANCED, false);
    m_pGameMenu->setItemChecked(FILE_MENU_EXPERT, false);
    m_pGameMenu->setItemChecked(FILE_MENU_USERDEFINED, false);
    switch(m_levelMgr.getLevel()) 
    {
    case GameConstant::LEVEL_BEGINNER:
        m_pGameMenu->setItemChecked(FILE_MENU_BEGINNER, true);
        break;
    case GameConstant::LEVEL_INTERMEDIATE:
        m_pGameMenu->setItemChecked(FILE_MENU_ADVANCED, true);
        break;
    case GameConstant::LEVEL_USER_DEFINED:
        m_pGameMenu->setItemChecked(FILE_MENU_USERDEFINED, true);
        break;
    case GameConstant::LEVEL_EXPERT:
    default:
        m_pGameMenu->setItemChecked(FILE_MENU_EXPERT, true);
        break;
    }
}

void MineUI_QtWindow::adjustToClientSize()
{
    QSize size = m_pView->getClientSize();    
    QSize parentSize(size.width(), size.height() + m_pMenu->height());
    setFixedSize(parentSize);
    m_pView->setFixedSize(size);
    m_pMenu->resize(size.width(), m_pMenu->height());
}


void MineUI_QtWindow::game_newGame()
{
    m_pView->reset();
}

void MineUI_QtWindow::game_setGameLevelSlot(int nGameLevel)
{
    switch(nGameLevel)
    {
    case FILE_MENU_BEGINNER :
        m_levelMgr.setLevel(GameConstant::LEVEL_BEGINNER);
        break;
    case FILE_MENU_ADVANCED :
        m_levelMgr.setLevel(GameConstant::LEVEL_INTERMEDIATE);
        break;
    case FILE_MENU_EXPERT :
        m_levelMgr.setLevel(GameConstant::LEVEL_EXPERT);
        break;
    case FILE_MENU_USERDEFINED :
    {
        GameDimDlg *pDlg = new GameDimDlg(this);
        pDlg->setGameDim(m_pView->getGameDim());    
        if (pDlg->exec() == GameDimDlg::Accepted) 
        {
        m_levelMgr.setUserDefinedLevel(pDlg->getGameDim());
        }
    } 
    break;
    default:
        return;
    }
    
    updateMenuState();     
    m_pView->setGameDim(m_levelMgr.getGameDim());            
    adjustToClientSize();
}


void MineUI_QtWindow::game_toggleMarker()
{
    m_pView->toggleMarker(); 
    updateMarkerMenu(); 
}

void MineUI_QtWindow::updateMarkerMenu()
{
    m_pGameMenu->setItemChecked(m_nMarkerMenuId, m_pView->isMarkerEnabled()); 
} 

void MineUI_QtWindow::game_showHallOfFame()
{
    HallOfFameDlg *pDlg = new HallOfFameDlg(this, &m_levelMgr);
    pDlg->exec();
    delete pDlg;
}

void MineUI_QtWindow::game_quit()
{
    QApplication::exit( 0 );
}

void MineUI_QtWindow::view_solve()
{
    m_pView->solveSlot(); 
}

void MineUI_QtWindow::view_reset()
{
    m_pView->resetSolveSlot(); 
}

void MineUI_QtWindow::view_prev()
{
    m_pView->prevSlot(); 
}

void MineUI_QtWindow::view_next()
{
    m_pView->nextSlot(); 
}

void MineUI_QtWindow::help_about()
{
    QMessageBox::information(this, ("About Truffle-Swine Keeper"), ("Truffle-Swine Keeper\nA Minesweeper clone by Hans Kopp\nPublished under GPL"));
}

