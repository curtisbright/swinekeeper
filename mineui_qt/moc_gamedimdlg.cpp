/****************************************************************************
** GameDimDlgBase meta object code from reading C++ file 'gamedimdlg.h'
**
** Created: Sat Jul 13 23:28:05 2002
**      by: The Qt MOC ($Id: moc_gamedimdlg.cpp,v 1.3 2002-07-14 00:54:30+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "gamedimdlg.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *GameDimDlgBase::className() const
{
    return "GameDimDlgBase";
}

QMetaObject *GameDimDlgBase::metaObj = 0;

void GameDimDlgBase::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
    badSuperclassWarning("GameDimDlgBase","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString GameDimDlgBase::tr(const char* s)
{
    return qApp->translate( "GameDimDlgBase", s, 0 );
}

QString GameDimDlgBase::tr(const char* s, const char * c)
{
    return qApp->translate( "GameDimDlgBase", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* GameDimDlgBase::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
    "GameDimDlgBase", "QDialog",
    0, 0,
    0, 0,
#ifndef QT_NO_PROPERTIES
    0, 0,
    0, 0,
#endif // QT_NO_PROPERTIES
    0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
