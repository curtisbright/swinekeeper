#ifndef SCORENAMEDLG_H
#define SCORENAMEDLG_H
#include "scorenamedlg.h"

class ScoreNameDlg : public ScoreNameDlgBase
{ 
    Q_OBJECT

public:
    ScoreNameDlg(QWidget* parent = 0, const char* name = 0, bool modal = TRUE, WFlags fl = 0 );
    ~ScoreNameDlg();

   void setDefaultName(const QString &defaultName); 

   QString   getName() const;    

};

#endif // SCORENAMEDLG_H
