/****************************************************************************
** Form implementation generated from reading ui file '../mineui_qt/gamedimdlg.ui'
**
** Created: Sat Jul 13 23:27:33 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "gamedimdlg.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a GameDimDlgBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
GameDimDlgBase::GameDimDlgBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
    setName( "GameDimDlgBase" );
    resize( 199, 146 ); 
    setProperty( "caption", tr( "GameDimDlg" ) );
    setProperty( "sizeGripEnabled", QVariant( TRUE, 0 ) );
    GameDimDlgBaseLayout = new QGridLayout( this ); 
    GameDimDlgBaseLayout->setSpacing( 6 );
    GameDimDlgBaseLayout->setMargin( 11 );

    Layout4 = new QVBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );

    Layout3 = new QGridLayout; 
    Layout3->setSpacing( 6 );
    Layout3->setMargin( 0 );

    minesEdit = new QLineEdit( this, "minesEdit" );

    Layout3->addWidget( minesEdit, 2, 2 );

    widthEdit = new QLineEdit( this, "widthEdit" );

    Layout3->addWidget( widthEdit, 0, 2 );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setProperty( "text", tr( "Width:" ) );

    Layout3->addWidget( TextLabel1, 0, 0 );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setProperty( "text", tr( "Mines:" ) );

    Layout3->addWidget( TextLabel3, 2, 0 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout3->addItem( spacer, 1, 1 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout3->addItem( spacer_2, 0, 1 );

    heightEdit = new QLineEdit( this, "heightEdit" );

    Layout3->addWidget( heightEdit, 1, 2 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout3->addItem( spacer_3, 2, 1 );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setProperty( "text", tr( "Height:" ) );

    Layout3->addWidget( TextLabel2, 1, 0 );
    Layout4->addLayout( Layout3 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout4->addItem( spacer_4 );

    Layout1 = new QHBoxLayout; 
    Layout1->setSpacing( 6 );
    Layout1->setMargin( 0 );
    QSpacerItem* spacer_5 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer_5 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setProperty( "caption", tr( "" ) );
    buttonOk->setProperty( "text", tr( "&OK" ) );
    buttonOk->setProperty( "autoDefault", QVariant( TRUE, 0 ) );
    buttonOk->setProperty( "default", QVariant( TRUE, 0 ) );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setProperty( "text", tr( "&Cancel" ) );
    buttonCancel->setProperty( "autoDefault", QVariant( TRUE, 0 ) );
    Layout1->addWidget( buttonCancel );
    Layout4->addLayout( Layout1 );

    GameDimDlgBaseLayout->addLayout( Layout4, 0, 0 );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
GameDimDlgBase::~GameDimDlgBase()
{
    // no need to delete child widgets, Qt does it all for us
}

