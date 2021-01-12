/****************************************************************************
** Form interface generated from reading ui file '../mineui_qt/scorenamedlg.ui'
**
** Created: Sat Jul 13 23:24:39 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef SCORENAMEDLGBASE_H
#define SCORENAMEDLGBASE_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class ScoreNameDlgBase : public QDialog
{ 
    Q_OBJECT

public:
    ScoreNameDlgBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ScoreNameDlgBase();

    QLabel* TextLabel1;
    QLineEdit* nameEdit;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

protected:
    QGridLayout* ScoreNameDlgBaseLayout;
    QVBoxLayout* Layout3;
    QHBoxLayout* Layout1;
};

#endif // SCORENAMEDLGBASE_H
