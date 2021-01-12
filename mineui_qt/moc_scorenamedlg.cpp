/****************************************************************************
** ScoreNameDlgBase meta object code from reading C++ file 'scorenamedlg.h'
**
** Created: Sat Jul 13 23:28:11 2002
**      by: The Qt MOC ($Id: moc_scorenamedlg.cpp,v 1.4 2002-07-14 00:54:31+02 hskopp Exp hskopp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "scorenamedlg.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *ScoreNameDlgBase::className() const
{
    return "ScoreNameDlgBase";
}

QMetaObject *ScoreNameDlgBase::metaObj = 0;

void ScoreNameDlgBase::initMetaObject()
{
    if ( metaObj )
    return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
    badSuperclassWarning("ScoreNameDlgBase","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ScoreNameDlgBase::tr(const char* s)
{
    return qApp->translate( "ScoreNameDlgBase", s, 0 );
}

QString ScoreNameDlgBase::tr(const char* s, const char * c)
{
    return qApp->translate( "ScoreNameDlgBase", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ScoreNameDlgBase::staticMetaObject()
{
    if ( metaObj )
    return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
    "ScoreNameDlgBase", "QDialog",
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
