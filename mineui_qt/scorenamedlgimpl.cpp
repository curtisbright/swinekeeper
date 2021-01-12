#include "StdAfx.h"
#include "scorenamedlgimpl.h"
#include <qlineedit.h>

/* 
 *  Constructs a ScoreNameDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ScoreNameDlg::ScoreNameDlg(QWidget* parent,  const char* name, bool modal, WFlags fl )
    : ScoreNameDlgBase( parent, name, modal, fl )
{
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ScoreNameDlg::~ScoreNameDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

QString    ScoreNameDlg::getName() const
{
     return nameEdit->text();
}

void ScoreNameDlg::setDefaultName(const QString &defaultName)
{
   nameEdit->setText(defaultName); 
}
