#include <Window.h>
#include <Application.h>

#include <MenuItem.h>
#include <MenuBar.h>
#include <Menu.h>
#include <Bitmap.h>
#include <TranslationUtils.h>
#include <cassert>
#include <map>
#include <be/interface/Alert.h> 

#include <gamecontrol/CGameManager.h>
#include <gamecontrol/CGlobalResourceSet.h>
#include <gamecontrol/InputDevices.h>
#include <mineui_common/CLevelMgr.h>
#include <mineui_common/GameConstants.h>
#include <cstdio>
#include "UIDrawContextBEOS.h" 

class MinesweeperGameView : public BView
{
public: 
    MinesweeperGameView(int nYOffset); 
    void init();
    void resize(const CGameDim &gameDim); 
    void Draw(BRect); 
    void SelectiveRepaint(); 
    void MouseDown(BPoint where); 
    void MouseUp(BPoint where); 
    void MouseMoved(BPoint where, uint32 code, const BMessage *a_message); 
    void GetPreferredSize(float *width, float *height); 
    void Pulse(void); 
    void showSolution(); 
private: 
    CGameManager m_gameMgr; 
    CMouseInputDevice m_mouse;  
    bool m_bIsValid; 

    CMouseInputDevice::MouseButton getActiveMouseButton(); 
}; 

MinesweeperGameView::MinesweeperGameView(int nYOffset) : 
    BView(BRect(0,nYOffset,10,10), "MinesweeperGameView", B_FOLLOW_NONE, B_WILL_DRAW | B_PULSE_NEEDED), 
    m_bIsValid(false)
{
}

void MinesweeperGameView::init()
{
   m_gameMgr.init(&m_mouse);     
}

void MinesweeperGameView::resize(const CGameDim &gameDim)
{
   m_gameMgr.resize(gameDim);
   ResizeToPreferred(); 
   m_bIsValid = true;
}


void MinesweeperGameView::Draw(BRect)
{
    if (m_bIsValid) 
    {
        CUIDrawContextBeOS ctx(this); 
        m_gameMgr.draw(&ctx, true); 
        Window()->Sync(); 
    }
}

void MinesweeperGameView::SelectiveRepaint()
{
    if (m_bIsValid) 
    {
        CUIDrawContextBeOS ctx(this); 
        m_gameMgr.draw(&ctx, false); 
        Window()->Sync(); 
    }
}

CMouseInputDevice::MouseButton MinesweeperGameView::getActiveMouseButton()
{
    BPoint where; 
    uint32 nButtons(0); 
    
    GetMouse(&where, &nButtons); 
    bool bLeft = (nButtons & B_PRIMARY_MOUSE_BUTTON)!=0; 
    bool bMiddle = (nButtons & B_TERTIARY_MOUSE_BUTTON)!=0; 
    bool bRight = (nButtons & B_SECONDARY_MOUSE_BUTTON)!=0; 
    printf("mouse %d\n", (int)nButtons); 
    
    CMouseInputDevice::MouseButton nActiveMouseButton = CMouseInputDevice::BUTTON_NONE;
    if (bLeft && bRight) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_MIDDLE; 
    else if (bLeft) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_LEFT; 
    else if (bMiddle) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_MIDDLE; 
    else if (bRight) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_RIGHT;  

    return nActiveMouseButton; 
}

void  MinesweeperGameView::MouseDown(BPoint where)
{
    CMouseInputDevice::MouseButton nActiveMouseButton = getActiveMouseButton(); 
    
    if (nActiveMouseButton != CMouseInputDevice::BUTTON_NONE) 
    {           
           m_mouse.onPushButton(toUI(where), nActiveMouseButton);
           SelectiveRepaint(); 
       }
}

void  MinesweeperGameView::MouseUp(BPoint where)
{    
    m_mouse.onReleaseButton(toUI(where)); 
    SelectiveRepaint();     
}

void  MinesweeperGameView::MouseMoved(BPoint where, uint32 code, const BMessage *)
{    
    m_mouse.onMoveMouse(toUI(where)); 
       SelectiveRepaint();        
}

void MinesweeperGameView::GetPreferredSize(float *pWidth, float *pHeight) 
{
   CUISize size(m_gameMgr.getClientWindowSize()); 
   *pWidth = float(size.x()-1); 
   *pHeight = float(size.y()-1); 
}

void MinesweeperGameView::Pulse(void)
{
       SelectiveRepaint();        
}

void MinesweeperGameView::showSolution()
{
    m_gameMgr.showSolution(); 
    SelectiveRepaint();   
}


class CPersistentDictBeOS : public CPersistentDictionary 
{
public: 
   virtual bool getString(const char *szKey, std::string &val) const; 
   virtual bool setString(const char *szKey, const std::string &val);
private:
    typedef std::map<std::string, std::string> StringStringMap; 
    StringStringMap m_dict;  
}; 

bool CPersistentDictBeOS::getString(const char *szKey, std::string &val) const
{
    StringStringMap::const_iterator keyPos = m_dict.find(std::string(szKey)); 
    if (keyPos == m_dict.end())
        return false; 
    val = (*keyPos).second; 
    return true; 
}

bool CPersistentDictBeOS::setString(const char *szKey, const std::string &val) 
{
    m_dict[std::string(szKey)] = val; 
    return true; 
}


class MineUIWindow : public BWindow 
{
    static const int MENU_BAR_HEIGHT = 18; 
    static const int MENU_GAME_NEW_MSG = 'GNEW'; 
    static const int MENU_LEVEL_BEGINNER_MSG = 'LBEG'; 
    static const int MENU_LEVEL_INTERMEDIATE_MSG = 'LINT'; 
    static const int MENU_LEVEL_EXPERT_MSG = 'LEXP'; 
    static const int MENU_LEVEL_USER_MSG = 'LUSR'; 
    static const int MENU_SHOW_HALL_OF_FAME_MSG = 'SHOF'; 
    static const int MENU_GAME_END_MSG = 'GEND'; 
    static const int MENU_SHOW_SOLUTION_MSG = 'SSOL'; 
    static const int MENU_SHOW_ABOUT_MSG = 'SABO'; 
public: 
    MineUIWindow(BRect frame); 
    void init(); 
    virtual bool QuitRequested(); 
    virtual void MessageReceived(BMessage *message); 
private: 
    MinesweeperGameView *m_pGameView; 
    BMenuBar *m_pMenuBar; 
    CLevelMgr m_levelMgr; 
    struct MenuMapEntry {
        MenuMapEntry(const char *pszMenuText, unsigned int nMsg, GameConstant::GameLevel nLevel) : 
            m_pszMenuText(pszMenuText), m_pItem(NULL), m_nMsg(nMsg), m_nLevel(nLevel) 
        {}
        const char *m_pszMenuText; 
        BMenuItem *m_pItem;
        unsigned int m_nMsg; 
        GameConstant::GameLevel m_nLevel;     
        BMenuItem *initMenuItem(); 
    }; 
    static const int m_nLevelCount = 4; 
    static MenuMapEntry m_levels[]; 
private: 
    void resize(const CGameDim &gameDim); 
    void updateMenuState(); 
}; 

MineUIWindow::MenuMapEntry MineUIWindow::m_levels[] =  
{
    MineUIWindow::MenuMapEntry("Beginner", MENU_LEVEL_BEGINNER_MSG, GameConstant::LEVEL_BEGINNER),
    MineUIWindow::MenuMapEntry("Intermediate", MENU_LEVEL_INTERMEDIATE_MSG, GameConstant::LEVEL_INTERMEDIATE), 
    MineUIWindow::MenuMapEntry("Expert", MENU_LEVEL_EXPERT_MSG, GameConstant::LEVEL_EXPERT), 
    MineUIWindow::MenuMapEntry("User defined", MENU_LEVEL_USER_MSG, GameConstant::LEVEL_USER_DEFINED), 
}; 


BMenuItem *MineUIWindow::MenuMapEntry::initMenuItem()
{
    m_pItem = new BMenuItem(m_pszMenuText, new BMessage(m_nMsg)); 
    return m_pItem; 
}

MineUIWindow::MineUIWindow(BRect frame)
                : BWindow(frame, "Truffle-Swine Keeper", B_TITLED_WINDOW,  
                            B_NOT_RESIZABLE 
                          | B_NOT_ZOOMABLE 
                          | B_WILL_ACCEPT_FIRST_CLICK 
                          | B_OUTLINE_RESIZE),
                  m_pGameView(NULL) 
{
    m_levelMgr.init(new CPersistentDictBeOS()); 

    m_pMenuBar = new BMenuBar(BRect(0,0,10000, MENU_BAR_HEIGHT), "MenuBar"); 
    AddChild(m_pMenuBar); 
    
    BMenu *pGameMenu = new BMenu("Game"); 
    m_pMenuBar->AddItem(pGameMenu); 
    pGameMenu->AddItem(new BMenuItem("New", new BMessage(MENU_GAME_NEW_MSG))); 
    pGameMenu->AddSeparatorItem(); 
    for(int i=0;i<m_nLevelCount;i++) 
        pGameMenu->AddItem(m_levels[i].initMenuItem()); 
    pGameMenu->AddSeparatorItem(); 
    pGameMenu->AddItem(new BMenuItem("Hall of Fame", new BMessage(MENU_SHOW_HALL_OF_FAME_MSG))); 
    pGameMenu->AddSeparatorItem(); 
    pGameMenu->AddItem(new BMenuItem("Quit", new BMessage(MENU_GAME_END_MSG))); 
    
    BMenu *pHelpMenu = new BMenu("Help"); 
    m_pMenuBar->AddItem(pHelpMenu); 
    pHelpMenu->AddItem(new BMenuItem("Solve", new BMessage(MENU_SHOW_SOLUTION_MSG))); 
    pHelpMenu->AddItem(new BMenuItem("About", new BMessage(MENU_SHOW_ABOUT_MSG))); 
    updateMenuState(); 
}

void MineUIWindow::updateMenuState()
{
    GameConstant::GameLevel nLevel = m_levelMgr.getLevel(); 
    for(int i=0;i<m_nLevelCount;i++) 
    {
        m_levels[i].m_pItem->SetMarked(nLevel == m_levels[i].m_nLevel); 
    }
}

void MineUIWindow::init()
{
    if (Lock()) {
        assert(!m_pGameView); 
        m_pGameView = new MinesweeperGameView(MENU_BAR_HEIGHT+1); 
        assert(m_pGameView); 
        AddChild(m_pGameView); 
        m_pGameView->init();
        resize(m_levelMgr.getGameDim()); 
        Unlock();
    }     
}

bool MineUIWindow::QuitRequested()
{
    be_app->PostMessage(B_QUIT_REQUESTED);
    return(true);
}

void MineUIWindow::MessageReceived(BMessage *message)
{
    for(int i=0;i<m_nLevelCount;i++) 
    {
        if (m_levels[i].m_nMsg == message->what) 
        {
            GameConstant::GameLevel nNewLevel = m_levels[i].m_nLevel; 
            if (nNewLevel == GameConstant::LEVEL_USER_DEFINED) 
            {
            }
            else 
            {
                m_levelMgr.setLevel(nNewLevel); 
            }    
            resize(m_levelMgr.getGameDim()); 
            updateMenuState(); 
            return; 
        }
    }
    
    switch(message->what) 
    {
        case MENU_GAME_NEW_MSG: 
            resize(m_levelMgr.getGameDim()); 
            break; 
        case MENU_GAME_END_MSG: 
            be_app->PostMessage(B_QUIT_REQUESTED);
            break;
        case MENU_SHOW_SOLUTION_MSG: 
            m_pGameView->showSolution();     
            break; 
        case MENU_SHOW_HALL_OF_FAME_MSG: 
            break; 
        case MENU_SHOW_ABOUT_MSG:
        { 
            BAlert *pAlert = new BAlert(
                "Truffle-Swine Keeper", 
                   "Truffle-Swine Keeper\n"
                   "A Minesweeper Clone by Hans Kopp\n"
                   "Published under the GNU General Public License\n"
                   "XXX still not fully implemented XXX",
                   "OK"); 
            pAlert->Go();     
             
            break; 
        }
        default: 
            break;  
    }
}


void MineUIWindow::resize(const CGameDim &gameDim)
{
    m_pGameView->resize(gameDim); 
    float dWidth(0), dHeight(0); 
    m_pGameView->GetPreferredSize(&dWidth, &dHeight); 
    ResizeTo(dWidth, dHeight+MENU_BAR_HEIGHT);     
    m_pMenuBar->ResizeTo(dWidth, MENU_BAR_HEIGHT); 
    m_pGameView->Invalidate(); 
}


// Application 
class MineUI_BEOS : public BApplication 
{
public:
    MineUI_BEOS();
};

MineUI_BEOS::MineUI_BEOS()
                    : BApplication("application/x-vnd.Kopp-MineUI_BEOS")
{
}


int main(int, char**)
{    
    MineUI_BEOS    application;

   if (CUISystemBeOS::instance() == NULL) 
   {
      CUISystemBeOS *pSysBeOS = NULL;    
      pSysBeOS = new CUISystemBeOS; 
      CUISystemBeOS::setInstance(pSysBeOS); 
   }

   if (CGlobalResourceSet::instance() == NULL) 
   {
      CUISystemBeOS *pSysBeOS = static_cast<CUISystemBeOS*>(CUISystemBeOS::instance()); 
      CGlobalResourceSet *pRes = new CGlobalResourceSet; 
      #define BMPPATH "/boot/home/src/minesweeper/resources/"
      std::auto_ptr<CIconSetBase> pSmilies(pSysBeOS->loadIconSet(BMPPATH"Smilies.bmp", IconType::SMILIE_COUNT, 1)); 
      pRes->m_pSmilies = pSmilies; 
      std::auto_ptr<CIconSetBase> pDigits(pSysBeOS->loadIconSet(BMPPATH"Digits.bmp", IconType::DIGIT_COUNT, 1)); 
      pRes->m_pDigits = pDigits; 
      std::auto_ptr<CIconSetBase> pFieldIcons(pSysBeOS->loadIconSet(BMPPATH"FieldIcons.bmp", IconType::FIELD_COUNT, 1)); 
      pRes->m_pFieldIcons = pFieldIcons;
      std::auto_ptr<CIconSetBase> pFieldInfos(pSysBeOS->loadIconSet(BMPPATH"FieldInfos.bmp", IconType::FIELDINFO_COUNT, 1)); 
      pRes->m_pFieldInfoIcons = pFieldInfos; 
      if (!pRes->isValid()) 
      {
         fprintf(stderr, "Unable to load bitmaps expected location : %s\n", BMPPATH); 
         return 2; 
      }

      CGlobalResourceSet::setInstance(pRes); 
   }

    // set up a rectangle and instantiate a new window
    BRect            aRect(100, 80, 260, 120);
    MineUIWindow    *aWindow = new MineUIWindow(aRect);
    
    aWindow->init();         
    // make window visible
    aWindow->Show();

    application.Run();

    return(0);
}
