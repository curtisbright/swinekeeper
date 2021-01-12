#include "StdAfx.h"
#include "gamedimdlgimpl.h"
#include <qvalidator.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qpushbutton.h>

/* 
 *  Constructs a GameDimDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
GameDimDlg::GameDimDlg( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : GameDimDlgBase( parent, name, modal, fl )
{
    QIntValidator *pValWidth = new QIntValidator(this);
    pValWidth->setRange(6,100);
    widthEdit->setValidator(pValWidth);
    QIntValidator *pValHeight = new QIntValidator(this);
    pValHeight->setRange(6,100);
    heightEdit->setValidator(pValHeight);
    
    QIntValidator *pValMines = new QIntValidator(this);
    pValMines->setRange(6,10000);
    minesEdit->setValidator(pValMines);
    
    setFixedSize(size());
    setCaption("Game Size");
    
    QObject::connect(buttonOk, SIGNAL(clicked()), this, SLOT(acceptWithValidate()));
    QObject::connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    // QObject::connect(m_pSetPercentButton, SIGNAL(clicked()), this, SLOT(setPercentSlot()));
}

/*  
 *  Destroys the object and frees any allocated resources
 */
GameDimDlg::~GameDimDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

void GameDimDlg::setGameDim(const CGameDim &gameDim) {
    m_gameDim = gameDim;
    
    widthEdit->setText(QString().setNum(m_gameDim.m_nSizeX));
    heightEdit->setText(QString().setNum(m_gameDim.m_nSizeY));
    minesEdit->setText(QString().setNum(m_gameDim.m_nMines));
}

CGameDim GameDimDlg::getGameDim() const
{
    return m_gameDim;
}

void GameDimDlg::setPercentSlot()
{
    int nFields = QString(widthEdit->text()).toUInt(NULL) * QString(heightEdit->text()).toUInt(NULL);
    minesEdit->setText(QString().setNum(int(nFields * .2 + .5)));
}

void GameDimDlg::acceptWithValidate()
{
    bool bValuesOK(true);
    
    bool bOk(false);
    QString strWidth(widthEdit->text());     
    int nWidth = strWidth.toUInt(&bOk);
    if (!bOk || nWidth <6 || nWidth > 100) bValuesOK = false;
    QString strHeight(heightEdit->text());     
    int nHeight = strHeight.toUInt(&bOk);
    if (!bOk || nHeight <6 || nHeight > 100) bValuesOK = false;
    QString strMines(minesEdit->text());     
    int nMines = strMines.toUInt(&bOk);
    if (!bOk || strMines <2 || nMines > nWidth*nHeight/2) bValuesOK = false;
        
    if (bValuesOK) {
        m_gameDim.m_nSizeX = nWidth;
        m_gameDim.m_nSizeY = nHeight;
        m_gameDim.m_nMines = nMines;
        accept();
    }
    else {
        QMessageBox::information(NULL, ("Error"), ("Invalid Parameters\n(Width<=100, Height<=100, Mines<=Width*Height/2)"));
    }
}

    