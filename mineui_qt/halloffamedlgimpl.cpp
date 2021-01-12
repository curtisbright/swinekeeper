#include "StdAfx.h"
#include "halloffamedlgimpl.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <mineui_common/CLevelMgr.h>
#include <qmessagebox.h> 


/* 
 *  Constructs a HallOfFameDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HallOfFameDlg::HallOfFameDlg( QWidget* parent, CLevelMgr *pLevelMgr)
    : HallOfFameDlgBase( parent, /*name=*/ NULL, /*modal=*/ TRUE, 0 ),
       m_pLevelMgr(pLevelMgr)
{
   updateEntries(); 

   QObject::connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
   QObject::connect(buttonClearScoreTable, SIGNAL(clicked()), this, SLOT(clearScoreTable()));

   setFixedSize(size());
   setCaption("Hall of Fame");
}



/*  
 *  Destroys the object and frees any allocated resources
 */
HallOfFameDlg::~HallOfFameDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void HallOfFameDlg::updateEntries()
{
   CScoreTable scoreTable; 
   m_pLevelMgr->getScoreTable(scoreTable); 

   nameBeginner->setText(scoreTable.m_scoreTable[0].m_name.c_str());
   nameAdvanced->setText(scoreTable.m_scoreTable[1].m_name.c_str());
   nameExpert->setText(scoreTable.m_scoreTable[2].m_name.c_str());

   timeBeginner->setText(QString().setNum(scoreTable.m_scoreTable[0].m_nTime));
   timeAdvanced->setText(QString().setNum(scoreTable.m_scoreTable[1].m_nTime));
   timeExpert->setText(QString().setNum(scoreTable.m_scoreTable[2].m_nTime));
}

void HallOfFameDlg::clearScoreTable()
{
   if (QMessageBox::warning(
         this, "", 
         "Do you really want to clear the high score table?", 
         QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) 
   {
      m_pLevelMgr->clearScoreTable(); 
      updateEntries(); 
   }
}

