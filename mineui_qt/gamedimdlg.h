/****************************************************************************
** Form interface generated from reading ui file '../mineui_qt/gamedimdlg.ui'
**
** Created: Sat Jul 13 23:24:39 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef GAMEDIMDLGBASE_H
#define GAMEDIMDLGBASE_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class GameDimDlgBase : public QDialog
{ 
    Q_OBJECT

public:
    GameDimDlgBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GameDimDlgBase();

    QLineEdit* minesEdit;
    QLineEdit* widthEdit;
    QLabel* TextLabel1;
    QLabel* TextLabel3;
    QLineEdit* heightEdit;
    QLabel* TextLabel2;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

protected:
    QGridLayout* GameDimDlgBaseLayout;
    QVBoxLayout* Layout4;
    QGridLayout* Layout3;
    QHBoxLayout* Layout1;
};

#endif // GAMEDIMDLGBASE_H
