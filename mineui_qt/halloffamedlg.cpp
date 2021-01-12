/****************************************************************************
** Form implementation generated from reading ui file '../mineui_qt/halloffamedlg.ui'
**
** Created: Sat Jul 13 23:27:37 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "halloffamedlg.h"

#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a HallOfFameDlgBase which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
HallOfFameDlgBase::HallOfFameDlgBase( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
    setName( "HallOfFameDlgBase" );
    resize( 212, 125 ); 
    setProperty( "caption", tr( "Hall of Fame" ) );
    setProperty( "sizeGripEnabled", QVariant( TRUE, 0 ) );
    HallOfFameDlgBaseLayout = new QGridLayout( this ); 
    HallOfFameDlgBaseLayout->setSpacing( 6 );
    HallOfFameDlgBaseLayout->setMargin( 11 );

    Layout5 = new QVBoxLayout; 
    Layout5->setSpacing( 6 );
    Layout5->setMargin( 0 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout5->addItem( spacer );

    Layout7 = new QGridLayout; 
    Layout7->setSpacing( 6 );
    Layout7->setMargin( 0 );

    timeBeginner = new QLabel( this, "timeBeginner" );
    timeBeginner->setProperty( "text", tr( "999" ) );

    Layout7->addWidget( timeBeginner, 0, 2 );

    TextLabel3 = new QLabel( this, "TextLabel3" );
    TextLabel3->setProperty( "text", tr( "Expert:" ) );

    Layout7->addWidget( TextLabel3, 2, 0 );

    nameExpert = new QLabel( this, "nameExpert" );
    nameExpert->setProperty( "text", tr( "unknown" ) );

    Layout7->addWidget( nameExpert, 2, 1 );

    nameAdvanced = new QLabel( this, "nameAdvanced" );
    nameAdvanced->setProperty( "text", tr( "unknown" ) );

    Layout7->addWidget( nameAdvanced, 1, 1 );

    nameBeginner = new QLabel( this, "nameBeginner" );
    nameBeginner->setProperty( "text", tr( "unknown" ) );

    Layout7->addWidget( nameBeginner, 0, 1 );

    TextLabel1 = new QLabel( this, "TextLabel1" );
    TextLabel1->setProperty( "text", tr( "Beginner:" ) );

    Layout7->addWidget( TextLabel1, 0, 0 );

    timeExpert = new QLabel( this, "timeExpert" );
    timeExpert->setProperty( "text", tr( "999" ) );

    Layout7->addWidget( timeExpert, 2, 2 );

    TextLabel2 = new QLabel( this, "TextLabel2" );
    TextLabel2->setProperty( "text", tr( "Advanced:" ) );

    Layout7->addWidget( TextLabel2, 1, 0 );

    timeAdvanced = new QLabel( this, "timeAdvanced" );
    timeAdvanced->setProperty( "text", tr( "999" ) );

    Layout7->addWidget( timeAdvanced, 1, 2 );
    Layout5->addLayout( Layout7 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    Layout5->addItem( spacer_2 );

    Layout4 = new QHBoxLayout; 
    Layout4->setSpacing( 6 );
    Layout4->setMargin( 0 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout4->addItem( spacer_3 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setProperty( "caption", tr( "" ) );
    buttonOk->setProperty( "text", tr( "&OK" ) );
    buttonOk->setProperty( "autoDefault", QVariant( TRUE, 0 ) );
    buttonOk->setProperty( "default", QVariant( TRUE, 0 ) );
    Layout4->addWidget( buttonOk );

    buttonClearScoreTable = new QPushButton( this, "buttonClearScoreTable" );
    buttonClearScoreTable->setProperty( "text", tr( "Clear" ) );
    Layout4->addWidget( buttonClearScoreTable );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout4->addItem( spacer_4 );
    Layout5->addLayout( Layout4 );

    HallOfFameDlgBaseLayout->addLayout( Layout5, 0, 0 );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
HallOfFameDlgBase::~HallOfFameDlgBase()
{
    // no need to delete child widgets, Qt does it all for us
}

