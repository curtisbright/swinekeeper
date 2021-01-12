#ifndef HALLOFFAMEDLG_H
#define HALLOFFAMEDLG_H
#include "halloffamedlg.h"
#include <mineui_common/GameOptions.h>
class CLevelMgr ;

class HallOfFameDlg : public HallOfFameDlgBase
{ 
    Q_OBJECT

public:
    HallOfFameDlg( QWidget* parent, CLevelMgr *pLevelMgr);
    ~HallOfFameDlg();

private slots: 
   void clearScoreTable(); 

private:
   // CScoreTable m_scoreTable;
   CLevelMgr *m_pLevelMgr; 
   void updateEntries(); 
};

#endif // HALLOFFAMEDLG_H
