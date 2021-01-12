/****************************************************************************
** Form interface generated from reading ui file '../mineui_qt/halloffamedlg.ui'
**
** Created: Sat Jul 13 23:24:39 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef HALLOFFAMEDLGBASE_H
#define HALLOFFAMEDLGBASE_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QPushButton;

class HallOfFameDlgBase : public QDialog
{ 
    Q_OBJECT

public:
    HallOfFameDlgBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~HallOfFameDlgBase();

    QLabel* timeBeginner;
    QLabel* TextLabel3;
    QLabel* nameExpert;
    QLabel* nameAdvanced;
    QLabel* nameBeginner;
    QLabel* TextLabel1;
    QLabel* timeExpert;
    QLabel* TextLabel2;
    QLabel* timeAdvanced;
    QPushButton* buttonOk;
    QPushButton* buttonClearScoreTable;

protected:
    QGridLayout* HallOfFameDlgBaseLayout;
    QVBoxLayout* Layout5;
    QGridLayout* Layout7;
    QHBoxLayout* Layout4;
};

#endif // HALLOFFAMEDLGBASE_H
