#ifndef GAMEDIMDLG_H
#define GAMEDIMDLG_H
#include "gamedimdlg.h"
#include <gamecontrol/GameMisc.h>

class GameDimDlg : public GameDimDlgBase
{ 
    Q_OBJECT

public:
    GameDimDlg( QWidget* parent = 0, const char* name = 0, bool modal = TRUE, WFlags fl = 0 );
    ~GameDimDlg();

   void setGameDim(const CGameDim &gameDim);
   CGameDim getGameDim() const;

private slots:
   void acceptWithValidate();
   void setPercentSlot();
private:
   CGameDim m_gameDim;

};

#endif // GAMEDIMDLG_H
