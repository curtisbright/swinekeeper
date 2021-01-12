/****************************************************************************
** Form implementation generated from reading ui file '../mineui_qt/scorenamedlg.ui'
**
** Created: Sat Jul 13 23:27:42 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "scorenamedlg.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a ScoreNameDlgBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ScoreNameDlgBase::ScoreNameDlgBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
    setName( "ScoreNameDlgBase" );
    resize( 240, 127 ); 
    setProperty( "sizePolicy", QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, sizePolicy().hasHeightForWidth() ) );
    setProperty( "caption", tr( "New High Score" ) );
    setProperty( "sizeGripEnabled", QVariant( TRUE, 0 ) );
    ScoreNameDlgBaseLayout = new QGridLayout( this ); 
    ScoreNameDlgBaseLayout->setSpacing( 6 );
    ScoreNameDlgBaseLayout->setMargin( 11 );

    Layout3 = new QVBoxLayout; 
    Layout3->setSpacing( 6 );
    Layout3->setMargin( 0 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout3->addItem( spacer );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setProperty( "text", tr( "You have reached a new high score. \nPlease enter your name." ) );
    TextLabel1->setProperty( "textFormat", (int)QLabel::AutoText );
    Layout3->addWidget( TextLabel1 );

    nameEdit = new QLineEdit( this, "nameEdit" );
    Layout3->addWidget( nameEdit );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout3->addItem( spacer_2 );

    Layout1 = new QHBoxLayout; 
    Layout1->setSpacing( 6 );
    Layout1->setMargin( 0 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer_3 );

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
    Layout3->addLayout( Layout1 );

    ScoreNameDlgBaseLayout->addLayout( Layout3, 0, 0 );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ScoreNameDlgBase::~ScoreNameDlgBase()
{
    // no need to delete child widgets, Qt does it all for us
}

